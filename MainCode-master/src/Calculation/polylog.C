#include "Calculation/CTUtil.h"

CTUtil::CTUtil()
{

}

double CTUtil::xLi(int n, double x)
{
//                                                   -=-=- xli
//PN-------------------------------------------------------------------------
//     Polylogarithm function for real x,-1<x<1.For n=2 the precision is about
//     12 significant figures. For n>2 the precision is smaller, but still
//     better than 4 digits.
//     Dilogarithm part is the translation of Carl Schmidt's C code.
//
// jcp: Some double precision typing added.  But overall accuracy not checked.
// jcp: A faster version might be available from K.S. K"olbig, J.A. Mignaco and E. Remiddi, BIT 10 (1970) 38
// jcp: Or from CERNLIB dilog64.f, cgplg64.f

 double Value;

 int m3 = 8;

 map<int, double> c1 = {
   {2, 0.75},
   {3, -0.5833333333333333},
   {4, 0.4548611111111111},
   {5, -0.3680555555555555},
   {6, 0.3073611111111111},
   {7, -0.2630555555555555},
   {8, 0.2294880243764172}
 };

 map<int, double> c2 = {
   {2, -0.5},
   {3, 0.5},
   {4, -0.4583333333333333},
   {5, 0.416666666666666},
   {6, -0.3805555555555555},
   {7, 0.35},
   {8, -0.3241071428571428},
 };

 double zeta3 = 1.202056903159594285;
 double pi2by6 = 1.644934066848226436;

 int NCUT = 27;
 double L = 0.0;
 int i = 0;
 double r = 1.0;

//     Check if x lies in the correct range
 if(fabs(x) > r){
   cout<<"xLi: x out of range (-1,1) , x = "<<x<<endl;
   return 0.0;
 }

 if(n < 0){
   cout<<"The polylogarithm Li undefined for n = "<<n<<endl;
   return 0.0;
 }
 else if(n == 0){
  Value = x / (1.0 - x);
 }
 else if(n == 1){
  Value = -log(1.0 - x);
 }
 else if(n == 2){
          //Calculate dilogarithm
          //separately for x<0.5 and x>0.5
   if(x >= -0.5 && x <= 0.5){
     while(i <= NCUT){
       i = i + 1;
       r = r * x;

       L = L + r / (double)i / (double)i;
     }
     Value = L;
   }
   else if(x == 0){
     Value = 0.0;
   }
   else if(x > 0.5){ //n.eq.2,x>0.5
     double xt = 1.0 - x;
     L = pi2by6 - log(x) * log(xt);

     while(i <= NCUT){
       i = i + 1;
       r = r * xt;

       L = L - r / (double)i / (double)i;
     }
     Value = L;
   }
   else if (x < -0.5){
     double xt = -x / (1.0 - x);
     L = -0.5 * pow(log(1.0 - x), 2.0);

     while(i <= NCUT){
       i = i + 1;
       r = r * xt;

       L = L - r / (double)i / (double)i;
     }
     Value = L;
   }
 }
 else if (n == 3 && x >= 0.8){//use the expansion of Li3 near x=1
   L = zeta3 + pi2by6 * log(x);
   double xt = (1.0 - x);
   double xln1m = log(xt);

   for(int ii = 2; ii <= m3; ii++){
     L = L + (c1[ii] + c2[ii] * xln1m) * pow(xt, ii);
   }
   Value = L;
 }
 else{ //n>3 or x=3,x<0.8
   while(i <= NCUT){
     i = i + 1;
     r = r * x;

     L = L + r / pow((double)i, (double)n);
   }
   Value = L;
 }

 return Value;
}

double CTUtil::snp12(double x)
{
 double xnp_xx = x;
 auto snp12int = [&](double z){
   double dlxz = log(1.0 - xnp_xx * z);
   return dlxz * dlxz / z;
 };

 double AERR = 1e-16;
 double RERR = 1e-10;
 double ERREST;
 int IER;
 double Value = 0.5 * GausInt(snp12int, 0.0, 1.0, AERR, RERR, ERREST, IER);

 return Value;
}

double CTUtil::zbrnt(function<double(double)> func, double x1, double x2, double tolin, int &irt)
{
//                                                   -=-=- zbrnt
//
//                          Return code  IRT = 1 : limits do not bracket a root;
//                                             2 : function call exceeds maximum
// appears to be Wijngaarden-Dekker-Brent algorithm zbrent from Numerical Recipes.
//
// www.ulib.org/webRoot/Books/Numerical_Recipes/bookfpdf/f9-3.pdf 
 double Value;

 int ITMAX = 1000;
 double EPS = 3e-12;

 irt = 0;
 double tol = fabs(tolin);          //modified so it can't change input TOLIN (jcp 11/4/02)
 double a = x1;
 double b = x2;
 double fa = func(a);
 double fb = func(b);

 if(fb * fa > 0.0){
   cout<<"Root must be bracketed for ZBRNT. Set = 0"<<endl;
   cout<<"ZBRNT fatal error fa = "<<fa<<" fb = "<<fb<<endl;
   irt = 1;
   return 0.0;
 }

 double c = b;                       //Previously missing -- would matter if FC=0 -- (jcp 11/12/01)
 double fc = fb;

 double d, e;
 double tol1;
 double xm;
 double s, p, q, r;
 for(int iter = 1; iter <= ITMAX; iter++){
   if(fb * fc > 0.0){
     c = a;
     fc = fa;
     d = b - a;
     e = d;
   }

   if(fabs(fc) < fabs(fb)){
     a = b;
     b = c;
     c = a;
     fa = fb;
     fb = fc;
     fc = fa;
   }

   tol1 = 2.0 * EPS * fabs(b) + 0.5 * tol;
   xm = 0.5 * (c - b);
   if(fabs(xm) <= tol1 || fb == 0.0){
     Value = b;
     return Value;
   }

   if(fabs(e) >= tol1 && fabs(fa) > fabs(fb)){
     s = fb / fa;

     if(a == c){
       p = 2.0 * xm * s;
       q = 1.0 - s;
     }
     else{
       q = fa / fc;
       r = fb / fc;
       p = s * (2.0 * xm * q * (q - r) - (b - a) * (r - 1.0));
       q = (q - 1.0) * (r - 1.0) * (s - 1.0);
     }

     if(p > 0.0) q = q * (-1.0);
     p = fabs(p);
     double minValue = (3.0 * xm * q - fabs(tol1 * q)) < fabs(e * q) ? (3.0 * xm * q - fabs(tol1 * q)) : fabs(e * q);

     if((2.0 * p) < minValue){
       e = d;
       d = p / q;
     }
     else{
       d = xm;
       e = d;
     }
   }
   else{
     d = xm;
     e = d;
   }

   a = b;
   fa = fb;

   if(fabs(d) > tol1){
     b = b + d;
   }
   else{
     if(fabs(xm) < 1e-20) b = b + fabs(tol1);
     else b = b + fabs(tol1) * xm / fabs(xm);
   }

   fb = func(b);
 }

 cout<<"Warning: ZBRNT exceeding maximum iterations."<<endl;
 irt = 2;
 Value = b;

 return Value;
}

