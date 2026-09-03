#include "CTEQHelper/HoppetInterface.h"

double HoppetInterface::zbrnt(function<double(double)> func, double x1, double x2, double tolin, int &irt)
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
   cout<<"Root must be bracketed for ZBRNT. Set = 0 fa = "<<fa<<" fb = "<<fb<<endl;
   cout<<"ZBRNT fatal error"<<endl;
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

