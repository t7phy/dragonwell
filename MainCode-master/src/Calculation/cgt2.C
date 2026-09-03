#include "Calculation/CalcDIS.h"
//
//-----------------------------------------------------------------------
// On the next-to-next-to-leading order QCD corrections     
// to heavy-quark production in deep-inelastic 
//    
// H. Kawamura, N. Lo Presti, S. Moch and A. Vogt
//-----------------------------------------------------------------------    
//
// The threshold approximations for the gluon coefficient function c_{2,g} 
// at two loops:
// cgt2 in Eq. (3.18)
//
//-----------------------------------------------------------------------
// ..The 2-loop threshold approximation to the gluon c_{2,g}^2 
//   see Eq. (3.18)
//   power ln(mu)^0
//
double CalcDIS::cgt2(double eta, double xi, int nf)
{
 if(!isDefineGmJSaFunctions) DefineFunctions_GmJSa();

 double pi = 3.14159265359;
 double beta = sqrt(eta/(1.0 + eta));
 double lnbeta = log(beta);

 double Value = (born_t(eta,xi)+born_l(eta,xi))/pow((4.0*pi), 4)*(
   + 3.607744112e+0/pow(beta, 2)
   + 2.894748951e+2/beta
   - 1.579136704e+2/beta*pow(lnbeta, 2)
   + 4.187651872e+1/beta*lnbeta
   + 6.149252757e-1/beta*nf
   - 4.386490844e+0/beta*nf*lnbeta
   + 1.152e+3*pow(lnbeta, 4)
   - 1.672966687e+3*pow(lnbeta, 3)
   - 3.328893061e+3*pow(lnbeta, 2)
   + 2.262291573e+3*lnbeta
   + 4.266666666e+1*nf*pow(lnbeta, 3)
   - 8.024907466e+1*nf*pow(lnbeta, 2)
   + 4.706482425e+1*nf*lnbeta
   - 3.289868133e+0*nlotconst(xi)/beta
   + 4.8e+1*nlotconst(xi)*pow(lnbeta, 2)
   - 2.018680599e+1*nlotconst(xi)*lnbeta
  );

 return Value;
}

//
//-----------------------------------------------------------------------
// ..The 2-loop threshold approximation to the gluon c_{2,g}^2 
//   see Eq. (3.18)
//   power ln(mu)^1
//
double CalcDIS::cgt2br1(double eta, double xi)
{
 if(!isDefineGmJSaFunctions) DefineFunctions_GmJSa();

 double pi = 3.14159265359;
 double beta = sqrt(eta/(1.0 + eta));
 double lnbeta = log(beta);

 double Value = (born_t(eta,xi)+born_l(eta,xi))/pow((4.0*pi), 4)*(
   + 4.934802200e+1/beta
   + 7.895683520e+1/beta*lnbeta
   - 1.152e+3*pow(lnbeta, 3)
   + 1.179777919e+2*pow(lnbeta, 2)
   + 2.222515190e+3*lnbeta
   - 2.4e+1*nlotconst(xi)*lnbeta
   - 3.289868133e+0*nlotbarconst(xi)/beta
   + 4.8e+1*nlotbarconst(xi)*pow(lnbeta, 2)
   - 2.018680599e+1*nlotbarconst(xi)*lnbeta
  );

 return Value;
}

//
//-----------------------------------------------------------------------
// ..The 2-loop threshold approximation to the gluon c_{2,g}^2 
//   see Eq. (3.18)
//   power ln(mu)^2
//
double CalcDIS::cgt2br2(double eta, double xi)
{
 if(!isDefineGmJSaFunctions) DefineFunctions_GmJSa();

 double pi = 3.14159265359;
 double beta = sqrt(eta/(1.0 + eta));
 double lnbeta = log(beta);

 double Value = (born_t(eta,xi)+born_l(eta,xi))/pow((4.0*pi), 4)*(
   + 2.88e+2*pow(lnbeta, 2)
   + 2.912527760e+2*lnbeta
   - 2.4e+1*nlotbarconst(xi)*lnbeta
  );

 return Value;
}

//
// ------------------------------------------------------------------------
// ..The exact expression for the constant term O(beta^0) of the 
//   gluon coefficient function at 1 loop
//   see Eq.(3.10)
//   power ln(mu)^0
//   extracted from:
//   E. Laenen, S. Riemersma, J. Smith, W.L. van Neerven, Nucl.Phys. B392 (1993) 162-228 
//
double CalcDIS::nlotconst(double xi)
{
 double z2 = 1.6449340668482264365;
 double pi = 3.14159265359;

 double ca = 3.0;
 double cf = 4.0/3.0;

 double ln2 = log(2.0);
 double YSQ = sqrt(1.0+4.0/xi);
 double LOGA = log(YSQ-1.0);
 double LOGB = log(xi);
 double LOGC = log(4.0+xi);
 double LOGD = log(2.0+xi);

 double inv2pxi = 1.0 / (2.0 + xi);
 double inv4pxi = 1.0 / (4.0 + xi);

 double consta = 56.0 - pow(pi, 2)
   + 12.0*LOGA*pow(YSQ, (-1))
   + 4.0*pow(LOGA, 2)
   + pow(LOGD, 2)
   + 4.0*LOGC
   - 4.0*pow(LOGC, 2)
   + 6.0*LOGB*pow(YSQ, (-1))
   + 4.0*LOGB*LOGA
   + pow(LOGB, 2)
   - 4.0*ln2
   - 12.0*ln2*pow(YSQ, (-1))
   - 8.0*ln2*LOGA
   - 2.0*ln2*LOGD
   + 8.0*ln2*LOGC
   - 4.0*ln2*LOGB
   + pow(ln2, 2)
   + 2.0*dilog( - 2.0*inv2pxi)
   + 36.0*inv2pxi
   - 6.0*inv2pxi*xi
   + 24.0*inv2pxi*LOGC
   - 4.0*inv2pxi*LOGC*xi
   - 24.0*inv2pxi*ln2
   + 4.0*inv2pxi*ln2*xi
   + 16.0*pow(inv2pxi, 2)*LOGC
   - 12.0*pow(inv2pxi, 2)*LOGC*xi
   + 6.0* pow(inv2pxi, 2)*LOGC*pow(xi, 2)
   - 16.0*pow(inv2pxi, 2)*ln2
   + 12.0*pow(inv2pxi, 2)*ln2*xi
   - 6.0*  pow(inv2pxi, 2)*ln2*pow(xi, 2)
   - 128.0*pow(inv2pxi, 2)*inv4pxi*LOGC
   + 128.0*pow(inv2pxi, 2)*inv4pxi*ln2
   - 160.0*inv2pxi*inv4pxi
   - 64.0*inv2pxi*inv4pxi*LOGC
   + 64.0*inv2pxi*inv4pxi*ln2
   + 128.0*inv2pxi*pow(inv4pxi, 2)
   - 48.0*inv4pxi
   - 2.0*inv4pxi*pow(pi, 2)
   - 8.0*inv4pxi*pow(LOGA, 2)
   - 8.0*inv4pxi*LOGB*LOGA
   - 2.0*inv4pxi*pow(LOGB, 2)
   + 16.0*inv4pxi*ln2*LOGA
   + 8.0*inv4pxi*ln2*LOGB
   - 8.0*inv4pxi*pow(ln2, 2)
   + 64.0*pow(inv4pxi, 2);

 double constf =        - 12.0
   - 4.0*z2
   - 24.0*LOGA*pow(YSQ, (-1))
   - 8.0*pow(LOGA, 2)
   + 2.0*pow(LOGD, 2)
   - 8.0*LOGC
   - 12.0*LOGB*pow(YSQ, (-1))
   - 8.0*LOGB*LOGA
   - 2.0*pow(LOGB, 2)
   + 8.0*ln2
   + 24.0*ln2*pow(YSQ, (-1))
   + 16.0*ln2*LOGA
   - 4.0*ln2*LOGD
   + 8.0*ln2*LOGB
   - 6.0*pow(ln2, 2)
   + 4.0*dilog( - 2.0*inv2pxi)
   - 60.0*inv2pxi
   - 6.0*inv2pxi*xi
   - 16.0*inv2pxi*LOGC
   - 12.0*inv2pxi*LOGC*xi
   + 16.0*inv2pxi*ln2
   + 12.0*inv2pxi*ln2*xi
   - 64.0* pow(inv2pxi, 2)*LOGC
   + 56.0* pow(inv2pxi, 2)*LOGC*xi
   + 14.0* pow(inv2pxi, 2)*LOGC*pow(xi, 2)
   + 64.0* pow(inv2pxi, 2)*ln2
   - 56.0* pow(inv2pxi, 2)*ln2*xi
   - 14.0* pow(inv2pxi, 2)*ln2*pow(xi, 2)
   + 256.0*pow(inv2pxi, 2)*inv4pxi*LOGC
   - 256.0*pow(inv2pxi, 2)*inv4pxi*ln2
   + 360.0*inv2pxi*inv4pxi
   + 128.0*inv2pxi*inv4pxi*LOGC
   - 128.0*inv2pxi*inv4pxi*ln2
   - 544.0*inv2pxi*pow(inv4pxi, 2)
   + 44.0*inv4pxi
   + 40.0*inv4pxi*z2
   + 48.0*inv4pxi*pow(LOGA, 2)
   - 8.0*inv4pxi*pow(LOGD, 2)
   + 48.0*inv4pxi*LOGB*LOGA
   + 12.0*inv4pxi*pow(LOGB, 2)
   - 96.0*inv4pxi*ln2*LOGA
   + 16.0*inv4pxi*ln2*LOGD
   - 48.0*inv4pxi*ln2*LOGB
   + 40.0*inv4pxi*pow(ln2, 2)
   - 16.0*inv4pxi*dilog( - 2.0*inv2pxi)
   - 272.0*pow(inv4pxi, 2);

 double Value = consta*ca+constf*cf;

 return Value;
}

//
// ------------------------------------------------------------------------
// ..The exact expression for the constant term O(beta^0) of the 
//   gluon coefficient function at 1 loop
//   see Eq.(3.11)
//   power ln(mu)^1
//   extracted from:
//   E. Laenen, S. Riemersma, J. Smith, W.L. van Neerven, Nucl.Phys. B392 (1993) 162-228 
//
double CalcDIS::nlotbarconst(double xi)
{
 double pi = 3.14159265359;

 double ca = 3.0;
 double tf = 0.5;

 double ln2 = log(2.0);
 double LOGC = log(4.0+xi);

 double Value = 4.0*ca*(2.0+LOGC-2.0*ln2);
 Value = Value - 4.0/3.0*tf;

 return Value;
}

//
// ------------------------------------------------------------------------
// ..The Pade estimate for the constant term O(beta^0) of the 
//   gluon coefficient function at 2 loops
//   power ln(mu)^0
//
double CalcDIS::cgt2pade(double eta, double xi)
{
 if(!isDefineGmJSaFunctions) DefineFunctions_GmJSa();

 double pi = 3.14159265359;
 double ca = 3.0;
 double ln2 = log(2.0);

 double Value = (born_t(eta,xi)+born_l(eta,xi))/pow((4.0*pi), 4)
              * pow((nlotconst(xi)+36.0*ca*pow(ln2, 2)-60.0*ca*ln2), 2);

 return Value;
}

