#include "Calculation/CalcDIS.h"

double CalcDIS::F2hg2(double x, double Q, double aMu, double aMs, int iHad)
{
//      Module GM-JS :  Interface to FFNS programs of Jack Smith etal.
//      Light quark initiated pieces 10/25/2010 by MG 
//      F77 built by HLL.  07.07 - 07.08
 double ErrEst;
 int Ier;

 double bms = aMs;
 double QQ = Q;
 double xx = x;
 double Xi = x * (1.0 + 4.0 * bms * bms / (Q * Q)); //chi; rescaling variable
 double zmax = x / Xi;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;

 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 F2HQgint = [&](double z){
   double Coef = HQcoef(2,z,QQ,bmu,bms);
   double gluon = GetPDFH(Ihadn, 0, xx/z, bmu);

   return gluon*Coef/z; //*XX the multiplication by XX is made outside in 4fit/chidis.f
 };

 double a5 = zmax - 0.00000000001*(zmax-xx);

 double F2g =
              SMPSNF(F2HQgint,xx + 0.00000000001*(a5-xx),
                              xx + 0.000001*(a5-xx),4, ErrEst, Ier)
            + SMPSNF(F2HQgint,xx + 0.000001*(a5-xx),
                              xx + 0.00001*(a5-xx),4, ErrEst, Ier)
            + SMPSNF(F2HQgint,xx + 0.00001*(a5-xx),
                              xx + 0.0001*(a5-xx),4, ErrEst, Ier)
            + SMPSNF(F2HQgint,xx + 0.0001*(a5-xx),
                              xx + 0.001*(a5-xx),4, ErrEst, Ier)
            + SMPSNF(F2HQgint,xx + 0.001*(a5-xx),
                              xx + 0.01*(a5-xx),4, ErrEst, Ier)
            + SMPSNF(F2HQgint,xx + 0.01*(a5-xx),
                              xx + 0.1*(a5-xx),8, ErrEst, Ier)
            + SMPSNF(F2HQgint,xx + 0.1*(a5-xx),
                              xx + 0.9*(a5-xx),16, ErrEst, Ier)
            + SMPSNF(F2HQgint,xx + 0.9*(a5-xx),
                              xx + 0.99*(a5-xx),8, ErrEst, Ier)
            + SMPSNF(F2HQgint,xx + 0.99*(a5-xx),
                              xx + 0.999*(a5-xx),4, ErrEst, Ier)
            + SMPSNF(F2HQgint,xx + 0.999*(a5-xx),
                              xx + 0.9999*(a5-xx),4, ErrEst, Ier)
            + SMPSNF(F2HQgint,xx + 0.9999*(a5-xx),
                              xx + 0.99999*(a5-xx),4, ErrEst, Ier)
            + SMPSNF(F2HQgint,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

 double Value = pow(als4pi, 2.0) * F2g;

 //cout<<"F2hg2 = "<<Value<<endl;
 return Value;
}

double CalcDIS::F2hlPS2(double x, double Q, double aMu, double aMs, int iHad)
{
//marco F2hlPS2: contributions prop. to the charge of heavy quarks////////////////////
 double ErrEst;
 int Ier;

 double bms = aMs;
 double QQ = Q;
 double xx = x;
 double Xi = x * (1.0 + 4.0 * bms * bms / (Q * Q)); //chi; rescaling variable
 double zmax = x / Xi;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;

 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 F2hint = [&](double z){//marco F2hint quark initiated -> photon-heavy qrk
   double Coef = HQhqlcoef(2,z,QQ,bmu,bms);
   double sum = GetPDF(Ihadn,20, xx/z, bmu); //(u+ub+d+db+s+sb+...)
                                             //Nf active flavor is 
                                             //read from subroutine ./flib/2prz/pdf.f
   //cout<<"F2hint: "<<sum<<"  "<<Coef<<endl;
   return sum*Coef/z; //*XX multiplication by XX is made outside in 4fit/chidis.f
 };

 double a5 = zmax - 0.00000000001*(zmax-xx);

 double tF2h =
               SMPSNF(F2hint,xx + 0.00000000001*(a5-xx),
                             xx + 0.000001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2hint,xx + 0.000001*(a5-xx),
                             xx + 0.00001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2hint,xx + 0.00001*(a5-xx),
                             xx + 0.0001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2hint,xx + 0.0001*(a5-xx),
                             xx + 0.001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2hint,xx + 0.001*(a5-xx),
                             xx + 0.01*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2hint,xx + 0.01*(a5-xx),
                             xx + 0.1*(a5-xx),8, ErrEst, Ier)
             + SMPSNF(F2hint,xx + 0.1*(a5-xx),
                             xx + 0.9*(a5-xx),16, ErrEst, Ier)
             + SMPSNF(F2hint,xx + 0.9*(a5-xx),
                             xx + 0.99*(a5-xx),8, ErrEst, Ier)
             + SMPSNF(F2hint,xx + 0.99*(a5-xx),
                             xx + 0.999*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2hint,xx + 0.999*(a5-xx),
                             xx + 0.9999*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2hint,xx + 0.9999*(a5-xx),
                             xx + 0.99999*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2hint,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

 double Value = pow(als4pi, 2.0) * tF2h;

 return Value;
}

double CalcDIS::SiF2l(double x, double Q, double aMu, double aMs, int iHad, int iPrtn)
{
//marco===================================================================
// Semi-inclusive F2l: contributions prop. to the charge of light quarks
// This corresponds to the d(eta,xi) terms in Eq 5 PLB 347 1995 Riemersma
//marco===================================================================

 double ErrEst;
 int Ier;

 int jPrtn = iPrtn;

 double bms = aMs;
 double QQ = Q;
 double xx = x;
 double Xi = x * (1.0 + 4.0 * bms * bms / (Q * Q)); //chi; rescaling variable
 double zmax = x / Xi;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;

 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 F2lint = [&](double z){//marco Semi-inclusive F2lint light quark initiated -> photon-light qrk
   double Coef= HQlqcoef(2,z,QQ,bmu,bms);

   double suml = GetPDF(Ihadn,jPrtn, xx/z, bmu) + GetPDF(Ihadn, -jPrtn, xx/z, bmu);

   return suml * Coef / z; //*XX the multiplication by XX is made outside in 4fit/chidis.f
 };

 double a5 = zmax - 0.00000000001 * (zmax - xx);

 double tF2l =
               SMPSNF(F2lint,xx + 0.00000000001*(a5-xx),
                             xx + 0.000001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2lint,xx + 0.000001*(a5-xx),
                             xx + 0.00001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2lint,xx + 0.00001*(a5-xx),
                             xx + 0.0001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2lint,xx + 0.0001*(a5-xx),
                             xx + 0.001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2lint,xx + 0.001*(a5-xx),
                             xx + 0.01*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2lint,xx + 0.01*(a5-xx),
                             xx + 0.1*(a5-xx),8, ErrEst, Ier)
             + SMPSNF(F2lint,xx + 0.1*(a5-xx),
                             xx + 0.9*(a5-xx),16, ErrEst, Ier)
             + SMPSNF(F2lint,xx + 0.9*(a5-xx),
                             xx + 0.99*(a5-xx),8, ErrEst, Ier)
             + SMPSNF(F2lint,xx + 0.99*(a5-xx),
                             xx + 0.999*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2lint,xx + 0.999*(a5-xx),
                             xx + 0.9999*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2lint,xx + 0.9999*(a5-xx),
                             xx + 0.99999*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(F2lint,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

 double Value = pow(als4pi, 2.0) * tF2l;

 return Value;
}

double CalcDIS::FLhlPS2(double x, double Q, double aMu, double aMs, int iHad)
{
//marco FLhlPS2 contributions prop. to the charge of heavy quarks////////////////////
//     NNLO singlet contribution to F_long=F_2/(2x)-F_1 (0 helicity S.F.),
//     as defined by CTEQ

 double ErrEst;
 int Ier;

 double bms = aMs;
 double QQ = Q;
 double xx = x;
 double Xi = x * (1.0 + 4.0 * bms * bms / (Q * Q)); //chi; rescaling variable
 double zmax = x / Xi;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;

 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 FLhint = [&](double z){// marco FLhint quark initiated -> photon-heavy qrk
   double Coef = HQhqlcoef(0,z,QQ,bmu,bms);
   double sum = GetPDF(Ihadn,20, xx/z, bmu); //(u+ub+d+db+s+sb+...)
                                             //Nf active flavor is 
                                             //read from subroutine ./flib/2prz/pdf.f
   return sum*Coef/z; //*XX multiplication by XX is made outside in 4fit/chidis.f
 };

 double a5 = zmax - 0.00000000001 * (zmax - xx);

 double tFLh =
               SMPSNF(FLhint,xx + 0.00000000001*(a5-xx),
                             xx + 0.000001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLhint,xx + 0.000001*(a5-xx),
                             xx + 0.00001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLhint,xx + 0.00001*(a5-xx),
                             xx + 0.0001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLhint,xx + 0.0001*(a5-xx),
                             xx + 0.001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLhint,xx + 0.001*(a5-xx),
                             xx + 0.01*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLhint,xx + 0.01*(a5-xx),
                             xx + 0.1*(a5-xx),8, ErrEst, Ier)
             + SMPSNF(FLhint,xx + 0.1*(a5-xx),
                             xx + 0.9*(a5-xx),16, ErrEst, Ier)
             + SMPSNF(FLhint,xx + 0.9*(a5-xx),
                             xx + 0.99*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLhint,xx + 0.99*(a5-xx),
                             xx + 0.999*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLhint,xx + 0.999*(a5-xx),
                             xx + 0.9999*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLhint,xx + 0.9999*(a5-xx),
                             xx + 0.99999*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLhint,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

 double Value = pow(als4pi, 2.0) * tFLh;

//marco Divide by 2, to match the normalization of CTEQ's F_{long}
 Value = Value / 2.0;

 return Value;
}



double CalcDIS::SiFLl(double x, double Q, double aMu, double aMs, int iHad, int iPrtn)
{
//marco================================================================
// Semi-inclusive FLl contributions prop. to the charge of light quarks
// NNLO singlet contribution to F_long=F_2/(2x)-F_1 (0 helicity S.F.),
// as defined by CTEQ
//marco================================================================

 double ErrEst;
 int Ier;

 int jPrtn = iPrtn;

 double bms = aMs;
 double QQ = Q;
 double xx = x;
 double Xi = x * (1.0 + 4.0 * bms * bms / (Q * Q)); //chi; rescaling variable
 double zmax = x / Xi;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;

 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 FLlint = [&](double z){// marco FLlint light quark initiated -> photon-light qrk
   double Coef = HQlqcoef(0,z,QQ,bmu,bms);
   double suml = GetPDF(Ihadn,jPrtn, xx/z, bmu) + GetPDF(Ihadn,-jPrtn, xx/z, bmu);

   return suml*Coef/z; //*XX the multiplication by XX is made outside in 4fit/chidis.f
 };

 double a5 = zmax - 0.00000000001*(zmax-xx);

 double tFLl =
               SMPSNF(FLlint,xx + 0.00000000001*(a5-xx),
                             xx + 0.000001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLlint,xx + 0.000001*(a5-xx),
                             xx + 0.00001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLlint,xx + 0.00001*(a5-xx),
                             xx + 0.0001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLlint,xx + 0.0001*(a5-xx),
                             xx + 0.001*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLlint,xx + 0.001*(a5-xx),
                             xx + 0.01*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLlint,xx + 0.01*(a5-xx),
                             xx + 0.1*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLlint,xx + 0.1*(a5-xx),
                             xx + 0.9*(a5-xx),8, ErrEst, Ier)
             + SMPSNF(FLlint,xx + 0.9*(a5-xx),
                             xx + 0.99*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLlint,xx + 0.99*(a5-xx),
                             xx + 0.999*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLlint,xx + 0.999*(a5-xx),
                             xx + 0.9999*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLlint,xx + 0.9999*(a5-xx),
                             xx + 0.99999*(a5-xx),4, ErrEst, Ier)
             + SMPSNF(FLlint,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

 double Value = pow(als4pi, 2.0) * tFLl;

//marco Divide by 2, to match the normalization of CTEQ's F_{long}
 Value = Value / 2.0;

 return Value;
}

double CalcDIS::F2lNSSub(double x, double Q, double aMu, double aMs, int iHad, int iPrtn)
{
//=======================================================
// New Subtraction term introduced in Eq 19 short paper
// Taken from Eq.B.4 of EPJC1 301 1998 Buza et al
// This is for F2 
//=======================================================

 double Zeta2 = 1.6449340668482264365;
 double Zeta3 = 1.2020569031595942854;

 double ErrEst;
 int Ier;

 int jPrtn = iPrtn;

 double bms = aMs;
 double QQ = Q;
 double xx = x;
 double Xi = fchi(x,Q,bms,bms);
 double zmax = x / Xi;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;

 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 double suml0 = GetPDF(Ihadn, jPrtn, xx, bmu) + GetPDF(Ihadn, -jPrtn, xx, bmu);

                                //Dirac delta contribution
 double Delta = CF*Tf*suml0*(2.0 * pow(log(eps), 2.0) + (16.0/3.0*Zeta2 + 2.0/3.0)*log(eps) + (-8.0/3.0*Zeta3 + 40.0/9.0*Zeta2 +73.0/18.0));

 // yfu: why the remain part doesn't use xi
 double Remn = CF*Tf*suml0*log(1.0 - xx)*(8.0/3.0* pow(log(eps), 2.0) + 80.0/9.0*log(eps) + 224.0/27.0); // This is the f(x)*log(1-x) after the Plus integral

 // For plus distribution:
 // []+ otimes f = Int_x^1 dz a(z) (1/z * f(x/z) - f(x))                   - f(x) * Int_0^x a(z) dz
 //              = Int_x^1 dz a(x/z) (1/z * f(z) - x/z^2 f(x))             - f(x) * Int_0^x a(z) dz
 // x -> xi, variable substitution u = x/z
 //              = Int_x^zmax dz a(z/zmax) (1/z * f(x/z) - 1/zmax * f(xi)) - f(x) * Int_0^x a(z) dz
 // For finite part:
 // a(z) otimes f = Int_x^1 dz a(x/z) * f(z) * (1/z)
 // x -> xi, variable substitution u = x/z
 //               = Int_x^x/xi dz a(z/zmax) * f(x/z) * (1/z)

 F2lNSSubint = [&](double z){
   double Sub1 = A2NSqqPlus(z/zmax,eps);
   double Sub2 = A2NSqqFinite(z/zmax,eps);

   double suml = GetPDF(Ihadn, jPrtn, xx/z, bmu) + GetPDF(Ihadn,-jPrtn, xx/z, bmu);

   double suml0 = GetPDF(Ihadn, jPrtn, xx/zmax, bmu) + GetPDF(Ihadn, -jPrtn, xx/zmax, bmu);

   return (suml/z - suml0/zmax)*Sub1+(suml*Sub2/z);
 };

 double a5 = zmax - 0.00000000001 * (zmax - xx);

 double tF2lNSSub =
                    SMPSNF(F2lNSSubint,xx + 0.00000000001*(a5-xx),
                                       xx + 0.000001*(a5-xx),4, ErrEst, Ier)
                  + SMPSNF(F2lNSSubint,xx + 0.000001*(a5-xx),
                                       xx + 0.00001*(a5-xx),4, ErrEst, Ier)
                  + SMPSNF(F2lNSSubint,xx + 0.00001*(a5-xx),
                                       xx + 0.0001*(a5-xx),4, ErrEst, Ier)
                  + SMPSNF(F2lNSSubint,xx + 0.0001*(a5-xx),
                                       xx + 0.001*(a5-xx),4, ErrEst, Ier)
                  + SMPSNF(F2lNSSubint,xx + 0.001*(a5-xx),
                                       xx + 0.01*(a5-xx),4, ErrEst, Ier)
                  + SMPSNF(F2lNSSubint,xx + 0.01*(a5-xx),
                                       xx + 0.1*(a5-xx),4, ErrEst, Ier)
                  + SMPSNF(F2lNSSubint,xx + 0.1*(a5-xx),
                                       xx + 0.9*(a5-xx),8, ErrEst, Ier)
                  + SMPSNF(F2lNSSubint,xx + 0.9*(a5-xx),
                                       xx + 0.99*(a5-xx),4, ErrEst, Ier)
                  + SMPSNF(F2lNSSubint,xx + 0.99*(a5-xx),
                                       xx + 0.999*(a5-xx),4, ErrEst, Ier)
                  + SMPSNF(F2lNSSubint,xx + 0.999*(a5-xx),
                                       xx + 0.9999*(a5-xx),4, ErrEst, Ier)
                  + SMPSNF(F2lNSSubint,xx + 0.9999*(a5-xx),
                                       xx + 0.99999*(a5-xx),4, ErrEst, Ier)
                  + SMPSNF(F2lNSSubint,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

 double Value = pow(als4pi, 2.0) * (tF2lNSSub + Delta + Remn);

 return Value;
}

double CalcDIS::F2HQSub2(double x, double Q, double aMu, double aMs, int iHad)
{
 double ErrEst;
 int Ier;

 double bms = aMs;
 double QQ = Q;
 double xx = x;

 double Xi = fchi(x,Q,bms,bms); // X*(1d0 + 4d0*bms*bms/(Q*Q)) !chi; rescaling variable // yfu remind this place
 double zmax = x / Xi;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;
 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 F2HQS1 = [&](double z){// A^1 (*) C^1 (*) g
   FortranArray1D<double> G1Q{1, 5};
   double A1Hgxz = A1Hg(xx/z,eps);
   SfZm1Q(Ihadn, 0, z/zmax, QQ, bmu, G1Q);
   double C1Hg=(G1Q(1)+G1Q(3))*4.0; // ~ F2 taken out x, charge, & als4pi factors

   return A1Hgxz*C1Hg/z;
 };

 AnalyticF2HQS1 = [&](double z){// A^1 (*) C^1 (*) g
//marco11**********************************************************
// Here we implemented analytic convolutions for A^1 (*) C^1 (*)
// to speed up the computation of A^1 (*) C^1 (*) g
//marco*********************************************************
   double Zeta2=1.6449340668482264365;

   double gluon = GetPDFH(Ihadn, 0, xx/z, bmu);
   double z1 = z / zmax;

   double ConvC1A1 = CF*Tf*(20.0 - 48.0*z1 + 64.0*z1*z1 + 24.0*Zeta2
       - 48.0*z1*Zeta2 + 64.0*z1*z1*Zeta2 + 28.0*log(1.0 - z1)
       - 64.0*z1*log(1.0 - z1)
       + 48.0*z1*z1*log(1.0 - z1) - 8.0*pow(log(1.0 - z1), 2.0)
       + 16.0*z1*pow(log(1.0 - z1), 2.0)
       - 16.0*z1*z1*pow(log(1.0 - z1), 2.0)
       + 4.0*log(z1) + 32.0*z1*log(z1)
       - 48.0*z1*z1*log(z1)- 4.0*pow(log(z1), 2.0) + 8.0*z1*pow(log(z1), 2.0)
       - 16.0*z1*z1*pow(log(z1), 2.0) - 16.0*xLi(2,1.0 - z1)
       + 32.0*z1*xLi(2,1.0 - z1) - 32.0*z1*z1*xLi(2,1.0 - z1)
       - 8.0*xLi(2,z1)+ 16.0*z1*xLi(2,z1) - 32.0*z1*z1*xLi(2,z1))
       *log(eps);

   if(QQ != bmu){
      ConvC1A1 = ConvC1A1 + CF*Tf*(4.0 - 16.0*z1 - 16.0*log(1.0 - z1)
         + 32.0*z1*log(1.0 - z1) - 32.0*z1*z1*log(1.0 - z1)
         + 8.0*log(z1) - 16.0*z1*log(z1)
         + 32.0*z1*z1*log(z1))*log(eps)*log(QQ*QQ/bmu/bmu);
   }

   return ConvC1A1*gluon/z;
 };

 F2HQS2 = [&](double z){// A^2 (*) C^0 (*)g
   double Sub2 = A2Hg(z/zmax,eps);
   double gluon = GetPDFH(Ihadn, 0, xx/z, bmu);

   return gluon*Sub2/z;
 };

 F2HQS3 = [&](double z){// substraction due to the difference of alpha_S from FFNS to VFNS
   double A1Hgz = A1Hg(z/zmax,eps);
   double Sub3= log(1.0/eps)*A1Hgz* 2.0 / 3.0;
   double gluon = GetPDFH(Ihadn, 0, xx/z, bmu);

   return gluon * Sub3 / z;
 };

 F2HQS4 = [&](double z){// A2PSHq (*) C^0 (*)(u+ub)+(d+db)+...
   double sum = GetPDF(Ihadn,20, xx/z, bmu); //(u+ub+d+db+s+sb+...)
   double Sub = A2PSHq(z/zmax,eps);

   return sum*Sub/z;
 };

 double a5 = zmax - 0.00000000001 * (zmax - xx);

 double F2gSub1 =
                  SMPSNF(AnalyticF2HQS1,xx + 0.00000000001*(a5-xx),
                                        xx + 0.000001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(AnalyticF2HQS1,xx + 0.000001*(a5-xx),
                                        xx + 0.00001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(AnalyticF2HQS1,xx + 0.00001*(a5-xx),
                                        xx + 0.0001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(AnalyticF2HQS1,xx + 0.0001*(a5-xx),
                                        xx + 0.001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(AnalyticF2HQS1,xx + 0.001*(a5-xx),
                                        xx + 0.01*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(AnalyticF2HQS1,xx + 0.01*(a5-xx),
                                        xx + 0.10*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(AnalyticF2HQS1,xx + 0.1*(a5-xx),
                                        xx + 0.9*(a5-xx),8, ErrEst, Ier)
                + SMPSNF(AnalyticF2HQS1,xx + 0.9*(a5-xx),
                                        xx + 0.99*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(AnalyticF2HQS1,xx + 0.99*(a5-xx),
                                        xx + 0.999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(AnalyticF2HQS1,xx + 0.999*(a5-xx),
                                        xx + 0.9999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(AnalyticF2HQS1,xx + 0.9999*(a5-xx),
                                        xx + 0.99999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(AnalyticF2HQS1,xx + 0.99999*(a5-xx),a5,4,ErrEst, Ier);

 a5 = zmax - 0.00000000001 * (zmax - xx);

 double F2gSub2 =
                  SMPSNF(F2HQS2,xx + 0.00000000001*(a5-xx),
                                xx + 0.000001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS2,xx + 0.000001*(a5-xx),
                                xx + 0.00001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS2,xx + 0.00001*(a5-xx),
                                xx + 0.0001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS2,xx + 0.0001*(a5-xx),
                                xx + 0.001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS2,xx + 0.001*(a5-xx),
                                xx + 0.01*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS2,xx + 0.01*(a5-xx),
                                xx + 0.1*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS2,xx + 0.1*(a5-xx),
                                xx + 0.9*(a5-xx),8, ErrEst, Ier)
                + SMPSNF(F2HQS2,xx + 0.9*(a5-xx),
                                xx + 0.99*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS2,xx + 0.99*(a5-xx),
                                xx + 0.999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS2,xx + 0.999*(a5-xx),
                                xx + 0.9999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS2,xx + 0.9999*(a5-xx),
                                xx + 0.99999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS2,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

//marco The condition for matching Nf alpha_s to (Nf-1) virtual
//marco corrections in J. Smith's code is included in SFnGm.f

 double F2gSub3 = 0.0;

 a5 = zmax - 0.00000000001 * (zmax - xx);

 double F2qSub4 =
                  SMPSNF(F2HQS4,xx + 0.00000000001*(a5-xx),
                                xx + 0.000001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS4,xx + 0.000001*(a5-xx),
                                xx + 0.00001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS4,xx + 0.00001*(a5-xx),
                                xx + 0.0001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS4,xx + 0.0001*(a5-xx),
                                xx + 0.001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS4,xx + 0.001*(a5-xx),
                                xx + 0.01*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS4,xx + 0.01*(a5-xx),
                                xx + 0.1*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS4,xx + 0.1*(a5-xx),
                                xx + 0.9*(a5-xx),8, ErrEst, Ier)
                + SMPSNF(F2HQS4,xx + 0.9*(a5-xx),
                                xx + 0.99*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS4,xx + 0.99*(a5-xx),
                                xx + 0.999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS4,xx + 0.999*(a5-xx),
                                xx + 0.9999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS4,xx + 0.9999*(a5-xx),
                                xx + 0.99999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(F2HQS4,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

 double Value = pow(als4pi, 2.0) *(F2gSub1 + F2gSub2 + F2gSub3 +F2qSub4);

 return Value;
}

double CalcDIS::F2HQg0(double x, double Q, double aMu, double aMs, int iHad, int Nptn)
{
 double ErrEst;
 int Ier;

 double bms = aMs;
 double QQ = Q;
 double xx = x;

 double Xi = x * (1.0 + 4.0 * bms * bms / (Q * Q)); //chi; rescaling variable
 double zmax = x / Xi;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;
 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

// ******************************************************************
// force an error to reexamine this -- so far, this code is not used.
// ******************************************************************
 if(QQ*QQ >= 0.0){
   cout<<"fatal error -- F2HQg0int not yet optimized"<<endl;
   return 0.0;
 }

 map<int, double> efac = {
   {1, 4.0},
   {2, 1.0},
   {3, 1.0},
   {4, 4.0},
   {5, 1.0},
   {6, 4.0}
 };

 F2HQg0int = [&](double z){
   double Coef = HQcoef0(2,z,QQ,bmu,bms);
   double gluon = GetPDFH(Ihadn, 0, xx/z, bmu);
//marco the multiplication by XX is made outside in 4fit/chidis.f

   return gluon*Coef/z; //*XX
 };

 int IACTA = 2;
 int IACTB = 2;

 double tmp = AdzInt(F2HQg0int, xx, zmax, aErr/1000.0,rErr/1000.0,ErrEst,Ier, IACTA, IACTB);

 double a5 = zmax - 0.00000000001 * (zmax - xx);

 double tmp1 =
               SMPSNF(F2HQg0int,xx + 0.00000000001*(a5-xx),
                     xx + 0.00000000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.00000000001*(a5-xx),
                     xx + 0.0000000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.0000000001*(a5-xx),
                     xx + 0.000000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.000000001*(a5-xx),
                     xx + 0.00000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.00000001*(a5-xx),
                     xx + 0.0000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.0000001*(a5-xx),
                     xx + 0.000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.000001*(a5-xx),
                     xx + 0.00001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.00001*(a5-xx),
                     xx + 0.0001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.0001*(a5-xx),
                             xx + 0.001*(a5-xx),128, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.001*(a5-xx),
                               xx + 0.01*(a5-xx),256, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.01*(a5-xx),
                               xx + 0.03*(a5-xx),256, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.03*(a5-xx),
                               xx + 0.1*(a5-xx),256, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.1*(a5-xx),
                               xx + 0.9*(a5-xx),4096, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.9*(a5-xx),
                         xx + 0.99*(a5-xx),1024, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.99*(a5-xx),
                         xx + 0.999*(a5-xx),256, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.999*(a5-xx),
                         xx + 0.9999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.9999*(a5-xx),
                         xx + 0.99999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.99999*(a5-xx),
                         xx + 0.999999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.999999*(a5-xx),
                         xx + 0.9999999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.9999999*(a5-xx),
                         xx + 0.99999999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.99999999*(a5-xx),
                         xx + 0.999999999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQg0int,xx + 0.999999999*(a5-xx),a5,32,ErrEst, Ier);

 cout<<"F2HQg0int tmp candidate 11"<<endl;
 cout<<100.0*fabs((tmp1 - tmp)/tmp)<<" percent "<<tmp<<endl;

 tmp = AdzInt(F2HQg0int, xx, zmax, aErr,rErr,ErrEst,Ier, IACTA, IACTB);

 double Value = als4pi * efac[Nptn] /9.0 * tmp;

 return Value;
}

double CalcDIS::F2HQSub0(double x, double Q, double aMu, double aMs, int iHad, int Nptn)
{
 double ErrEst;
 int Ier;

 double bms = aMs;
 double QQ = Q;
 double xx = x;

 double Xi = fchi(x,Q,bms,bms); //X*(1d0 + 4d0*bms*bms/(Q*Q)) chi; rescaling variable
 double zmax = x / Xi;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;
 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

// ******************************************************************
// force an error to reexamine this -- so far, this code is not used.
// ******************************************************************
 if(bmu*bmu >= 0.0){
   cout<<"fatal error -- F2HQS0int not yet optimized"<<endl;
   return 0.0;
 }

 map<int, double> efac = {
   {1, 4.0},
   {2, 1.0},
   {3, 1.0},
   {4, 4.0},
   {5, 1.0},
   {6, 4.0}
 };

 F2HQS0int = [&](double z){
   double Sub = A1Hg(z/zmax,eps);
   double gluon = GetPDFH(Ihadn, 0, xx/z, bmu);

   return gluon*Sub/z;
 };

 int IACTA = 2;
 int IACTB = 2;

 double tmp = AdzInt(F2HQS0int, xx, zmax, aErr/1000.0,rErr/1000.0, ErrEst,Ier, IACTA, IACTB);

 double a5 = zmax - 0.00000000001 * (zmax - xx);

 double tmp1 =
               SMPSNF(F2HQS0int,xx + 0.00000000001*(a5-xx),
                     xx + 0.00000000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.00000000001*(a5-xx),
                     xx + 0.0000000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.0000000001*(a5-xx),
                     xx + 0.000000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.000000001*(a5-xx),
                     xx + 0.00000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.00000001*(a5-xx),
                     xx + 0.0000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.0000001*(a5-xx),
                     xx + 0.000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.000001*(a5-xx),
                     xx + 0.00001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.00001*(a5-xx),
                     xx + 0.0001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.0001*(a5-xx),
                             xx + 0.001*(a5-xx),128, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.001*(a5-xx),
                               xx + 0.01*(a5-xx),256, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.01*(a5-xx),
                               xx + 0.03*(a5-xx),256, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.03*(a5-xx),
                               xx + 0.1*(a5-xx),256, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.1*(a5-xx),
                               xx + 0.9*(a5-xx),4096, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.9*(a5-xx),
                         xx + 0.99*(a5-xx),1024, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.99*(a5-xx),
                         xx + 0.999*(a5-xx),256, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.999*(a5-xx),
                         xx + 0.9999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.9999*(a5-xx),
                         xx + 0.99999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.99999*(a5-xx),
                         xx + 0.999999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.999999*(a5-xx),
                         xx + 0.9999999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.9999999*(a5-xx),
                         xx + 0.99999999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.99999999*(a5-xx),
                         xx + 0.999999999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(F2HQS0int,xx + 0.999999999*(a5-xx),a5,32,ErrEst, Ier);

 cout<<"F2HQS0int tmp candidate 11"<<endl;
 cout<<100.0*fabs((tmp1 - tmp)/tmp)<<" percent "<<tmp<<endl;

 tmp = AdzInt(F2HQS0int, xx, zmax, aErr,rErr,ErrEst,Ier, IACTA, IACTB);

 double Value = als4pi * efac[Nptn]/9.0 * tmp;

 return Value;
}

double CalcDIS::FLhg2(double x, double Q, double aMu, double aMs, int iHad)
{
 double ErrEst;
 int Ier;

 double bms = aMs;
 double QQ = Q;
 double xx = x;
 double Xi = x * (1.0 + 4.0 * bms * bms / (Q * Q)); //chi; rescaling variable
 double zmax = x / Xi;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;

 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 FLHQgint = [&](double z){
   double Coef = HQcoef(0,z,QQ,bmu,bms);
   double gluon = GetPDFH(Ihadn, 0, xx/z, bmu);

   return gluon*Coef/z; //XX the multiplication by XX is made outside in 4fit/chidis.f
 };

 double a5 = zmax - 0.00000000001 * (zmax - xx);

 double tFLhg2 =
                 SMPSNF(FLHQgint,xx + 0.00000000001*(a5-xx),
                                 xx + 0.000001*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(FLHQgint,xx + 0.000001*(a5-xx),
                                 xx + 0.00001*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(FLHQgint,xx + 0.00001*(a5-xx),
                                 xx + 0.0001*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(FLHQgint,xx + 0.0001*(a5-xx),
                                 xx + 0.001*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(FLHQgint,xx + 0.001*(a5-xx),
                                 xx + 0.01*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(FLHQgint,xx + 0.01*(a5-xx),
                                 xx + 0.1*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(FLHQgint,xx + 0.1*(a5-xx),
                                 xx + 0.9*(a5-xx),8, ErrEst, Ier)
               + SMPSNF(FLHQgint,xx + 0.9*(a5-xx),
                                 xx + 0.99*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(FLHQgint,xx + 0.99*(a5-xx),
                                 xx + 0.999*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(FLHQgint,xx + 0.999*(a5-xx),
                                 xx + 0.9999*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(FLHQgint,xx + 0.9999*(a5-xx),
                                 xx + 0.99999*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(FLHQgint,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

//marco Divide by 2, to match the normalization of CTEQ's F_{long}
 double Value = pow(als4pi, 2.0) * tFLhg2/2.0;

 return Value;
}

double CalcDIS::FLHQSub2(double x, double Q, double aMu, double aMs, int iHad)
{
 double ErrEst;
 int Ier;

 double bms = aMs;
 double QQ = Q;
 double xx = x;
 double Xi = fchi(x,Q,bms,bms);//X*(1d0 + 4d0*bms*bms/(Q*Q)) !chi; rescaling variable
 double zmax = x / Xi;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;

 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 double xz;

 clnp1a = [&](double y, int Nf){// LO non-singlet coefficient functions for F_L
   return 4.0 * CF * y;
 };

 FLsub1 = [&](double z){// A^1 (*) C^1
   return A1Hg(xz/z,eps)*clnp1a(z,0)/z;
 };

 FLHQSint = [&](double z){
   xz=z;

   double a5 = 1.0 - 0.00000000001*(1.0-z);

   double Sub = SMPSN2(FLsub1,z + 0.00000000001*(a5-z),a5,16, ErrEst, Ier);

   double gluon = GetPDFH(Ihadn, 0, xx/z, bmu);

   return gluon*Sub/z;
 };

 double a5 = zmax - 0.00000000001 * (zmax - xx);

 double tFLSub2 =
                  SMPSNF(FLHQSint,xx + 0.00000000001*(a5-xx),
                                  xx + 0.000001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLHQSint,xx + 0.000001*(a5-xx),
                                  xx + 0.00001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLHQSint,xx + 0.00001*(a5-xx),
                                  xx + 0.0001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLHQSint,xx + 0.0001*(a5-xx),
                                  xx + 0.001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLHQSint,xx + 0.001*(a5-xx),
                                  xx + 0.01*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLHQSint,xx + 0.01*(a5-xx),
                                  xx + 0.1*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLHQSint,xx + 0.1*(a5-xx),
                                  xx + 0.9*(a5-xx),8, ErrEst, Ier)
                + SMPSNF(FLHQSint,xx + 0.9*(a5-xx),
                                  xx + 0.99*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLHQSint,xx + 0.99*(a5-xx),
                                  xx + 0.999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLHQSint,xx + 0.999*(a5-xx),
                                  xx + 0.9999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLHQSint,xx + 0.9999*(a5-xx),
                                  xx + 0.99999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLHQSint,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

//marco Divide by 2, to match the normalization of CTEQ's F_{long}
 double Value = pow(als4pi, 2.0) * tFLSub2 / 2.0;

 return Value;
}

double CalcDIS::FLHQg0(double x, double Q, double aMu, double aMs, int iHad, int Nptn)
{
 double ErrEst;
 int Ier;

 double bms = aMs;
 double QQ = Q;
 double xx = x;

 double Xi = x * (1.0 + 4.0 * bms * bms / (Q * Q)); //chi; rescaling variable
 double zmax = x / Xi;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;
 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 map<int, double> efac = {
   {1, 4.0},
   {2, 1.0},
   {3, 1.0},
   {4, 4.0},
   {5, 1.0},
   {6, 4.0}
 };

 FLHQg0int = [&](double z){
   double Coef = HQcoef0(0,z,QQ,bmu,bms);
   double gluon = GetPDFH(Ihadn, 0, xx/z, bmu);
//marco the multiplication by XX is made outside in 4fit/chidis.f

   return gluon*Coef/z; //*XX
 };

 int IACTA = 1;
 int IACTB = 1;

 double tmp = AdzInt(FLHQg0int, xx,zmax, aErr/1000.0, rErr/1000.0, ErrEst,Ier, IACTA, IACTB);

 double a5 = zmax - 0.00000000001 * (zmax - xx);

 double tmp1 =
               SMPSNF(FLHQg0int,xx + 0.00000000001*(a5-xx),
                     xx + 0.00000000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.00000000001*(a5-xx),
                     xx + 0.0000000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.0000000001*(a5-xx),
                     xx + 0.000000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.000000001*(a5-xx),
                     xx + 0.00000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.00000001*(a5-xx),
                     xx + 0.0000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.0000001*(a5-xx),
                     xx + 0.000001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.000001*(a5-xx),
                     xx + 0.00001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.00001*(a5-xx),
                     xx + 0.0001*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.0001*(a5-xx),
                             xx + 0.001*(a5-xx),128, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.001*(a5-xx),
                               xx + 0.01*(a5-xx),256, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.01*(a5-xx),
                               xx + 0.03*(a5-xx),256, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.03*(a5-xx),
                               xx + 0.1*(a5-xx),256, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.1*(a5-xx),
                               xx + 0.9*(a5-xx),4096, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.9*(a5-xx),
                         xx + 0.99*(a5-xx),1024, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.99*(a5-xx),
                         xx + 0.999*(a5-xx),256, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.999*(a5-xx),
                         xx + 0.9999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.9999*(a5-xx),
                         xx + 0.99999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.99999*(a5-xx),
                         xx + 0.999999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.999999*(a5-xx),
                         xx + 0.9999999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.9999999*(a5-xx),
                         xx + 0.99999999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.99999999*(a5-xx),
                         xx + 0.999999999*(a5-xx),64, ErrEst, Ier)
             + SMPSNF(FLHQg0int,xx + 0.999999999*(a5-xx),a5,32,ErrEst, Ier);

 cout<<"F2HQg0int tmp candidate 11"<<endl;
 cout<<100.0*fabs((tmp1 - tmp)/tmp)<<" percent "<<tmp<<endl;

// force an error, to reexamine this if necessary
 if(tmp*tmp >= 0.0){
   cout<<"fatal error -- FLHQg0int not yet optimized"<<endl;
   return 0.0;
 }

 tmp = AdzInt(FLHQg0int, xx, zmax, aErr,rErr,ErrEst,Ier, IACTA, IACTB);

 double Value = als4pi * efac[Nptn]/9.0 * tmp;

 return Value;
}

double CalcDIS::FLLNS2(double x, double Q, double aMu, double aMs, int iHad, int iPrtn)
{
//marco=================================================================
// Implementation of Eq 23  for FL with no plus distrb. 
//marco=================================================================

 double ErrEst;
 int Ier;

 int jPrtn = iPrtn;

 double bms = aMs;
 double QQ = Q;
 double xx = x;
 double Xi = x * (1.0 + 4.0 * bms * bms / (Q * Q)); //chi; rescaling variable
 double zmax = x / Xi;
 double xxi = QQ*QQ/bms/bms;

 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;

 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 FLLNS2int = [&](double z){
   double xxi = QQ*QQ/bms/bms;
   double Coef = LLNSqr(z,xxi);
   double suml = GetPDF(Ihadn, jPrtn, xx/z, bmu) + GetPDF(Ihadn,-jPrtn, xx/z, bmu);

   return suml*Coef/z; //*XX the multiplication by XX is made outside in 4fit/chidis.f
 };

 FLLNS2int0 = [&](double z){// coming from the plus
   double xxi = QQ*QQ/bms/bms;
   double Coef = LLNSqr(z,xxi);
   double suml0 = GetPDF(Ihadn, jPrtn, xx, bmu) + GetPDF(Ihadn,-jPrtn, xx, bmu);

   return -suml0*Coef; //*XX the multiplication by XX is made outside in 4fit/chidis.f
 };

 cL1llint = [&](double z){
   double suml = GetPDF(Ihadn, jPrtn, xx/z, bmu) + GetPDF(Ihadn,-jPrtn, xx/z, bmu);

   return 4.0*CF*z*suml/z;
 };

 double a5 = zmax - 0.00000000001*(zmax-xx);

 double tFLLNS2 =
                  SMPSNF(FLLNS2int,xx + 0.00000000001*(a5-xx),
                                   xx + 0.000001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLLNS2int,xx + 0.000001*(a5-xx),
                                   xx + 0.00001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLLNS2int,xx + 0.00001*(a5-xx),
                                   xx + 0.0001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLLNS2int,xx + 0.0001*(a5-xx),
                                   xx + 0.001*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLLNS2int,xx + 0.001*(a5-xx),
                                   xx + 0.01*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLLNS2int,xx + 0.01*(a5-xx),
                                   xx + 0.1*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLLNS2int,xx + 0.1*(a5-xx),
                                   xx + 0.9*(a5-xx),8, ErrEst, Ier)
                + SMPSNF(FLLNS2int,xx + 0.9*(a5-xx),
                                   xx + 0.99*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLLNS2int,xx + 0.99*(a5-xx),
                                   xx + 0.999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLLNS2int,xx + 0.999*(a5-xx),
                                   xx + 0.9999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLLNS2int,xx + 0.9999*(a5-xx),
                                   xx + 0.99999*(a5-xx),4, ErrEst, Ier)
                + SMPSNF(FLLNS2int,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

 a5 = 1.0 - 0.00000000001 * (1.0 - xx);

 double tcL1ll =
                 SMPSNF(cL1llint,xx + 0.00000000001*(a5-xx),
                                 xx + 0.000001*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(cL1llint,xx + 0.000001*(a5-xx),
                                 xx + 0.00001*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(cL1llint,xx + 0.00001*(a5-xx),
                                 xx + 0.0001*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(cL1llint,xx + 0.0001*(a5-xx),
                                 xx + 0.001*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(cL1llint,xx + 0.001*(a5-xx),
                                 xx + 0.01*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(cL1llint,xx + 0.01*(a5-xx),
                                 xx + 0.1*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(cL1llint,xx + 0.1*(a5-xx),
                                 xx + 0.9*(a5-xx),8, ErrEst, Ier)
               + SMPSNF(cL1llint,xx + 0.9*(a5-xx),
                                 xx + 0.99*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(cL1llint,xx + 0.99*(a5-xx),
                                 xx + 0.999*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(cL1llint,xx + 0.999*(a5-xx),
                                 xx + 0.9999*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(cL1llint,xx + 0.9999*(a5-xx),
                                 xx + 0.99999*(a5-xx),4, ErrEst, Ier)
               + SMPSNF(cL1llint,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

 tcL1ll = Tf*2.0 * 2.0/3.0 * log(xxi) * tcL1ll; //the extra factor of 2 comes from
                                                       //our notebook computation

 double Value = pow(als4pi, 2.0) * (tFLLNS2 - tcL1ll);

 return Value;
}

double CalcDIS::F2LNS2(double x, double Q, double aMu, double aMs, int iHad, int iPrtn)
{
//marco=================================================================
// Implementation of the plus distributuion in Eq 23  for F2
//marco=================================================================
 double small = 1e-7;

 double ErrEst;
 int Ier;

 int jPrtn = iPrtn;

 double bms = aMs;
 double QQ = Q;
 double xx = x;
 double Xi = x * (1.0 + 4.0 * bms * bms / (Q * Q)); //chi; rescaling variable
 double zmax = x / Xi;
 double xxi = QQ*QQ/bms/bms;
 if(Xi >= 1.0){
   return 0.0;
 }
 int Ihadn = iHad;

 double bmu = aMu;
 double eps = pow((bms / bmu), 2.0); //m^2/mu^2

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 double suml0 = GetPDF(Ihadn, jPrtn, xx, bmu) + GetPDF(Ihadn,-jPrtn, xx, bmu);

 F2LNS2int = [&](double z){
   double xxi = QQ*QQ/bms/bms;

   double Coef = L2NSqr(z,xxi);

   double suml = GetPDF(Ihadn, jPrtn, xx/z, bmu) + GetPDF(Ihadn,-jPrtn, xx/z, bmu);
   double suml0 = GetPDF(Ihadn, jPrtn, xx, bmu) + GetPDF(Ihadn,-jPrtn, xx, bmu);

   return (suml/z - suml0)*Coef; //*XX the multiplication by XX is made outside in 4fit/chidis.f
 };

 F2LNS2int0 = [&](double z){
   double xxi = QQ*QQ/bms/bms;

   double Coef= L2NSqr0(z,xxi); //the logarithmic asympototic behavior
                                //is subtracted from L2NSqr0(z,xxi) in GmJSa.F ;    
                                //it is then added after analytic integration in F2LNS2.

   return -Coef; //*XX the multiplication by XX is made outside in 4fit/chidis.f
 };

 c1llint = [&](double z){ // Eq. (B.2) AlphaS^(1) term in Nulc.Phys.B 383 1992
   double suml = GetPDF(Ihadn, jPrtn, xx/z, bmu) + GetPDF(Ihadn,-jPrtn, xx/z, bmu);
   double suml0 = GetPDF(Ihadn, jPrtn, xx, bmu) + GetPDF(Ihadn,-jPrtn, xx, bmu);

   double P1 = 4.0*log(1.0-z)/(1.0-z)*(suml/z -suml0);
   double P2 = -3.0/(1.0-z)*(suml/z -suml0);
   double P3 = (-2.0*(1.0+z)*log(1.0-z) - 2.0*(1.0 + z*z)/(1.0 - z)*log(z) + 6.0 + 4.0*z)*suml/z;

   return CF*(P1+P2+P3);
 };

 double a5 = zmax - 0.00000000001 * (zmax - xx);

 double t0 =
             SMPSNF(F2LNS2int,xx + 0.00000000001*(a5-xx),
                              xx + 0.000001*(a5-xx),4, ErrEst, Ier)
           + SMPSNF(F2LNS2int,xx + 0.000001*(a5-xx),
                              xx + 0.00001*(a5-xx),4, ErrEst, Ier)
           + SMPSNF(F2LNS2int,xx + 0.00001*(a5-xx),
                              xx + 0.0001*(a5-xx),4, ErrEst, Ier)
           + SMPSNF(F2LNS2int,xx + 0.0001*(a5-xx),
                              xx + 0.001*(a5-xx),4, ErrEst, Ier)
           + SMPSNF(F2LNS2int,xx + 0.001*(a5-xx),
                              xx + 0.01*(a5-xx),4, ErrEst, Ier)
           + SMPSNF(F2LNS2int,xx + 0.01*(a5-xx),
                              xx + 0.1*(a5-xx),4, ErrEst, Ier)
           + SMPSNF(F2LNS2int,xx + 0.1*(a5-xx),
                              xx + 0.9*(a5-xx),8, ErrEst, Ier)
           + SMPSNF(F2LNS2int,xx + 0.9*(a5-xx),
                              xx + 0.99*(a5-xx),4, ErrEst, Ier)
           + SMPSNF(F2LNS2int,xx + 0.99*(a5-xx),
                              xx + 0.999*(a5-xx),4, ErrEst, Ier)
           + SMPSNF(F2LNS2int,xx + 0.999*(a5-xx),
                              xx + 0.9999*(a5-xx),4, ErrEst, Ier)
           + SMPSNF(F2LNS2int,xx + 0.9999*(a5-xx),
                              xx + 0.99999*(a5-xx),4, ErrEst, Ier)
           + SMPSNF(F2LNS2int,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

//marco An integral from 0 to x, coming from the plus distribution for L2NSq.
// To improve convergence of this integral, we subtract the Log(z) terms
// arising in the asymptotic limit z->0 and evaluate them analytically as
// t2

 a5 = xx - 0.00000000001 * (xx - small);
 double t1 = SMPSNF(F2LNS2int0, small, a5, 16, ErrEst, Ier);
 t1 = suml0 * t1;  //multiplication by the PDF(XX) is made outside of the subroutine F2LNS2int0

 double t2 = -suml0*(-4.0*xx*(-157.0 + 12.0*Pi*Pi - 54.0*pow(log(xx), 2.0) +
              6.0*log(xxi) - 18.0*pow(log(xxi), 2.0)
            + log(xx)*(-66.0 + 72.0*log(xxi))))/81.0;

//marco tc1ll + Finite -> contributions from alpha_s piece in Eq.B2 NPB383 1992 Van Neerven et. al.
// finite -> Analytic piece coming by tc1ll plus distrib.
 double Finite = CF*suml0*(2.0*pow(log(1.0-xx), 2.0) - 3.0*log(1.0-xx) - 9.0 -4.0*Pi*Pi/6.0);

 a5 = 1.0 - 0.00000000001 * (1.0 - xx);

 double tc1ll =
                SMPSNF(c1llint,xx + 0.00000000001*(a5-xx),
                               xx + 0.000001*(a5-xx),4, ErrEst, Ier)
              + SMPSNF(c1llint,xx + 0.000001*(a5-xx),
                               xx + 0.00001*(a5-xx),4, ErrEst, Ier)
              + SMPSNF(c1llint,xx + 0.00001*(a5-xx),
                               xx + 0.0001*(a5-xx),4, ErrEst, Ier)
              + SMPSNF(c1llint,xx + 0.0001*(a5-xx),
                               xx + 0.001*(a5-xx),4, ErrEst, Ier)
              + SMPSNF(c1llint,xx + 0.001*(a5-xx),
                               xx + 0.01*(a5-xx),4, ErrEst, Ier)
              + SMPSNF(c1llint,xx + 0.01*(a5-xx),
                               xx + 0.1*(a5-xx),4, ErrEst, Ier)
              + SMPSNF(c1llint,xx + 0.1*(a5-xx),
                               xx + 0.9*(a5-xx),8, ErrEst, Ier)
              + SMPSNF(c1llint,xx + 0.9*(a5-xx),
                               xx + 0.99*(a5-xx),4, ErrEst, Ier)
              + SMPSNF(c1llint,xx + 0.99*(a5-xx),
                               xx + 0.999*(a5-xx),4, ErrEst, Ier)
              + SMPSNF(c1llint,xx + 0.999*(a5-xx),
                               xx + 0.9999*(a5-xx),4, ErrEst, Ier)
              + SMPSNF(c1llint,xx + 0.9999*(a5-xx),
                               xx + 0.99999*(a5-xx),4, ErrEst, Ier)
              + SMPSNF(c1llint,xx + 0.99999*(a5-xx),a5,4, ErrEst, Ier);

 tc1ll = Tf*2.0/3.0*log(QQ*QQ/bms/bms)*(tc1ll + Finite)*2.0;  // the extra factor of 2 comes from
                                                              // (a2=4)/2 from our notebook computation

 double Value = pow(als4pi, 2.0) * (t0 + t1 + t2 - tc1ll);

 return Value;
}

