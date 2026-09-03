#ifndef ElectroweakTheory_ResBosEW_h
#define ElectroweakTheory_ResBosEW_h

#include "RootCommon.h"
#include <iostream>

using namespace std;

class ResBosEW
{
 public:

 double sw2_eff = 0.2315;

 double mW = 80.385;
 double mZ = 91.1876;
 double gamW = 2.108;
 double gamZ = 2.498353;

 double sw = 0.2223;
 double GF = 1.16637E-5;

 double mB = 4.75;
 double mT = 173.5;
 double mH = 125;
 double gamT = 0.0;
 double gamH = 0.004;

 double sws, alpha0, alphaMz, alphaQ2, cw, cws;
 double acoupl, zcoupl_e, zcoupl_u, zcoupl_d, wcoupl;
 double alphaEM0 = 0.00729735;
 double alphaEMMz = 0.007763340902;
 int alphaEMOrder = 1;

 double gvu = 0.0;
 double gvd = 0.0;
 double gvl = 0.0;
 double gau = -1.0;
 double gad = 1.0;
 double gal = 1.0;

 double rho_e;
 double rho_u;
 double rho_d;

 double FAC_e;
 double FAC_u;
 double FAC_d;
 double FAC_A;

 double EL_Z;
 double ER_Z;

 double QL_Z1;
 double QR_Z1;
 double QL_Z2;
 double QR_Z2;

 double QL_A1;
 double QR_A1;
 double QL_A2;
 double QR_A2;
 double EL_A;
 double ER_A;

 double CAA_E[2];
 double CAA_O[2];
 double CZZ_E[2];
 double CZZ_O[2];
 double CZA_E[2];
 double CZA_O[2];

 double zzProp;
 double aaProp;
 double zaProp;

 double coeffEven;
 double coeffOdd;
 double total;

 double angularEven = 8.0 / 3.0;
 double angularOdd = 0.0;

 int iMode = 0;

 const std::array<double,5> Q2Step{{0.26e-6, 0.011, 0.25, 3.5, 90.}};
 std::array<double,5> betaEM{{0.1061, 0.2122, 0.460, 0.700, 0.725}};
 std::array<double,5> alphaEMStep;

 ResBosEW();
 virtual void InputStw(double stw);
 virtual void InitialPara();
 virtual void InitialPropagator(double Q);
 virtual double ZCrossSection(double mass, int iflag, TString Process);
 virtual double GetAlphaEM(double Q2);
 virtual void initAlpha();
 virtual double pyalem(double q2);
 virtual double alphas(double AMU);
};

#endif
