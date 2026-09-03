#include "Calculation/CalcDIS.h"

double CalcDIS::xSecLh(int iLptn1, int iLptn2, int iHadn, double x, double Q, double y, int iFlv, int iXsc)
{
             // Common block to store heavy flavor S.F.s deleted.
             // Logic of the calculation of heavy flavor xSec drastically simplified by HLL.

//     ----------------------------
//     Reduced cross section dSig / dxdQ^2 for general lepton-hadron scattering.
//
//         First written 2006.02.09 by wkt: a part of the DisPac05;
//         revised by HLL for the reduced cross section, 2006.03;
//         Re-written again by wkt for general cross sections, according to
//         the tech note, DisPac05a.tex, 2006.03.20.
//
//         Formulas straight from the ACOT-I paper, in particular Eq.(14).
//         Use Helicity Structure Functions for definiteness (no ambiguity on defs)
//         and for their direct association with the group-theoretical kinematics.
//     ----------------------------
//
//                            /  iLptn2
//              iLptn1 ______/
//                           \  iBsn / iCmptn
//                            \ ______  iFlv
//                             |------  X
//                            /
//                     iHadn /
//
//     The process will be specified by:
//
//     iLptn1,2 : external lepton : (1) nu,      (2) e-/mu-,
//                                , (-1) nubar, (-2) e+/mu+
//
//     iFlv :   0   : total inclusive
//            -6:6  : semi-inclusive of flavor iFlv
//           11:16  : semi-inclusive (quark + anti-quark) of flavor 1:6
//
//     iXsc :   0   : DESY Reduced Cross sections
//              1   : My Effective xSec. defined in the DisPac05 tech note
//              2   : d Sig / dx dy
//              3   : d Sig / dx dQ^2
//              4   : .... add as you please!

 double hMass = 0.938;
 double Ssml = 1e-20;

 FortranArray1D<int> nPol{-2, 2};
 nPol(-2) = 2;
 nPol(-1) = 1;
 nPol(0) = 0;
 nPol(1) = 1;
 nPol(2) = 2;

 FortranArray1D<int> nSgn{-2, 2};
 nSgn(-2) = -1;
 nSgn(-1) = -1;
 nSgn(0) = 0;
 nSgn(1) = 1;
 nSgn(2) = 1;

 double Zeta;

 if(!DisSet) mSetDis();
                                          // Kinematical variables
 double Q2 = Q * Q;

 double chPsi = (2.0-y) /y /sqrt(1.0 + pow((2.0 * x * hMass / Q), 2.0));
 double chPsi2 = pow(chPsi, 2.0);
 double shPsi2 = chPsi2 - 1.0;

 FortranArray1D<double> SFn123{1, 3};
 FortranArray1D<double> SfnHel{-1, 1};

 double EfXsc = 0.0, rXsec = 0.0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 EffXsc = [&](int iCC){// Calculates the "Effective cross-section",
                            // defined in the DisPac05 Tech Note.
                            // iCompton : 1 - 5
                                     // Calculate the structure functions
   SfnGm(iHadn, iCC, iFlv, x, Q, SFn123, SfnHel);

                                // Calculate the "reduced cross-section"
   double Value = g2Lm(iLptn1, iCC) * (SfnHel(-1) - SfnHel(1)) * chPsi
                + g2Lp(iLptn1, iCC) * (SfnHel(0) * shPsi2 + (SfnHel(1) + SfnHel(-1)) * (1.0 + chPsi2) / 2.0);

   //cout<<"g2Lm("<<iLptn1<<", "<<iCC<<") = "<<g2Lm(iLptn1, iCC)<<" g2Lp("<<iLptn1<<", "<<iCC<<") = "<<g2Lp(iLptn1, iCC);
   //cout<<" SfnHel(-1) = "<<SfnHel(-1)<<" SfnHel(1) = "<<SfnHel(1)<<" SfnHel(0) = "<<SfnHel(0)<<endl;
   //cout<<"chPsi = "<<chPsi<<" shPsi2 = "<<shPsi2<<endl;

   return Value;
 };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 if(iLptn1 == iLptn2){                    // neutral current case
   EfXsc = EffXsc(1);                   // This is the gamma-gamma term

   Zeta = AlfEwk(4) / AlfEwk(1);          // ratio of gauge couplings

   Zeta = Zeta * Q2 / (Q2 + pow(vBnMas(4), 2.0));          // ratio of propagators

   EfXsc = EfXsc + 2.0 * Zeta * EffXsc(5) + pow(Zeta, 2.0) * EffXsc(4);

   rXsec = EfXsc * 4.0 * x / (1.0 + chPsi2);       // DESY Reduced xSec.

   if(iXsc > 0){                            // My Effective xSce. needed only
     EfXsc = EfXsc * pow((4.0 * Pi * AlfEwk(1)), 2.0);   // for iXsc > 0 calculations later
   }
 }
 else if(abs(iLptn1 - iLptn2) == 1){     // Charged Current
   if((iLptn1 - iLptn2) == -1){             // W+ exchange
     EfXsc = EffXsc(2);
   }
   else if(iLptn1-iLptn2 == 1){         // W- exchange
     EfXsc = EffXsc(3);
   }
   rXsec = EfXsc * x * pow(y, 2) / 2.0 / (double)nPol(iLptn1); // DESY-type Reduced xSec.

   if(iXsc > 0){                           // My Effective xSce. needed only
     double wMas2 = pow(vBnMas(2), 2.0);                         // for iXsc > 0 calculations later
     EfXsc = EfXsc * pow((wMas2 *Q2 *Gf /(Q2 +wMas2)), 2.0) /2.0;
   }

 }
 else{
   rXsec = 0;
   EfXsc = 0;

   cout<<"Warning: iLptn1,2 = "<<iLptn1<<"  "<<iLptn2<<endl;
   cout<<" illegal in xSecLh call!"<<endl;
 }

 double Value = 0.0;

 if(iXsc == 0){// DESY Reduced xSec
   Value = rXsec;
 }
 else if(iXsc == 1){// My Effective xSce.
   Value = EfXsc;
 }
 else if(iXsc == 2){// dSig/dx dy
   Value = EfXsc * y /(2.0*Pi*Q2*(double)nPol(iLptn1)) * XsGv2pb;
 }
 else if(iXsc == 3){// dSig/dx dQ^2
   Value = EfXsc * pow(y, 2.0) /(2.0*Pi*Q2*Q2*(double)nPol(iLptn1)) * XsGv2pb;
 }
 else if(iXsc == 4){// dSig/dE dcos
   cout<<"temporary stop in lhXsec: tem is not defined"<<endl;
   return 0.0;
 }
 else if(iXsc == 5){// H1 combined data
   Value = rXsec;
 }
 else{
   cout<<"iXsc = "<<iXsc<<"  illegal in xSecLh call!"<<endl;
   return 0.0;
 }

 //cout<<"iLptn1 = "<<iLptn1<<" iLptn2 = "<<iLptn2<<" iHadn = "<<iHadn<<" x = "<<x<<" Q = "<<Q<<" y = "<<y<<" iFlv = "<<iFlv<<" iXsc = "<<iXsc<<endl;


                                      // Avoid returning zero answer
 if(Value < Ssml) Value = Ssml;

 return Value;
}

double CalcDIS::xSecLh_N3LO(int iLptn1, int iLptn2, int iHadn, double x, double Q, double y, int iFlv, int iXsc)
{
             // Common block to store heavy flavor S.F.s deleted.
             // Logic of the calculation of heavy flavor xSec drastically simplified by HLL.

//     ----------------------------
//     Reduced cross section dSig / dxdQ^2 for general lepton-hadron scattering.
//
//         First written 2006.02.09 by wkt: a part of the DisPac05;
//         revised by HLL for the reduced cross section, 2006.03;
//         Re-written again by wkt for general cross sections, according to
//         the tech note, DisPac05a.tex, 2006.03.20.
//
//         Formulas straight from the ACOT-I paper, in particular Eq.(14).
//         Use Helicity Structure Functions for definiteness (no ambiguity on defs)
//         and for their direct association with the group-theoretical kinematics.
//     ----------------------------
//
//                            /  iLptn2
//              iLptn1 ______/
//                           \  iBsn / iCmptn
//                            \ ______  iFlv
//                             |------  X
//                            /
//                     iHadn /
//
//     The process will be specified by:
//
//     iLptn1,2 : external lepton : (1) nu,      (2) e-/mu-,
//                                , (-1) nubar, (-2) e+/mu+
//
//     iFlv :   0   : total inclusive
//            -6:6  : semi-inclusive of flavor iFlv
//           11:16  : semi-inclusive (quark + anti-quark) of flavor 1:6
//
//     iXsc :   0   : DESY Reduced Cross sections
//              1   : My Effective xSec. defined in the DisPac05 tech note
//              2   : d Sig / dx dy
//              3   : d Sig / dx dQ^2
//              4   : .... add as you please!

 double hMass = 0.938;
 double Ssml = 1e-20;

 FortranArray1D<int> nPol{-2, 2};
 nPol(-2) = 2;
 nPol(-1) = 1;
 nPol(0) = 0;
 nPol(1) = 1;
 nPol(2) = 2;

 FortranArray1D<int> nSgn{-2, 2};
 nSgn(-2) = -1;
 nSgn(-1) = -1;
 nSgn(0) = 0;
 nSgn(1) = 1;
 nSgn(2) = 1;

 double Zeta;

 if(!DisSet) mSetDis();
 if(!isInitializeHoppetSF) InitializeHoppetSF();
                                          // Kinematical variables
 double Q2 = Q * Q;

 double chPsi = (2.0-y) /y /sqrt(1.0 + pow((2.0 * x * hMass / Q), 2.0));
 double chPsi2 = pow(chPsi, 2.0);
 double shPsi2 = chPsi2 - 1.0;

 FortranArray1D<double> SFn123{1, 3};
 FortranArray1D<double> SfnHel{-1, 1};

 double EfXsc = 0.0, rXsec = 0.0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 EffXsc = [&](int iCC){// Calculates the "Effective cross-section",
                            // defined in the DisPac05 Tech Note.
                            // iCompton : 1 - 5
                                     // Calculate the structure functions
   SfnGm_N3LO(iHadn, iCC, iFlv, x, Q, SFn123, SfnHel);

                                // Calculate the "reduced cross-section"
   double Value = g2Lm(iLptn1, iCC) * (SfnHel(-1) - SfnHel(1)) * chPsi
                + g2Lp(iLptn1, iCC) * (SfnHel(0) * shPsi2 + (SfnHel(1) + SfnHel(-1)) * (1.0 + chPsi2) / 2.0);

   //cout<<"g2Lm("<<iLptn1<<", "<<iCC<<") = "<<g2Lm(iLptn1, iCC)<<" g2Lp("<<iLptn1<<", "<<iCC<<") = "<<g2Lp(iLptn1, iCC);
   //cout<<" SfnHel(-1) = "<<SfnHel(-1)<<" SfnHel(1) = "<<SfnHel(1)<<" SfnHel(0) = "<<SfnHel(0)<<endl;
   //cout<<"chPsi = "<<chPsi<<" shPsi2 = "<<shPsi2<<endl;

   return Value;
 };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 if(iLptn1 == iLptn2){                    // neutral current case
   EfXsc = EffXsc(1);                   // This is the gamma-gamma term

   Zeta = AlfEwk(4) / AlfEwk(1);          // ratio of gauge couplings

   Zeta = Zeta * Q2 / (Q2 + pow(vBnMas(4), 2.0));          // ratio of propagators

   EfXsc = EfXsc + 2.0 * Zeta * EffXsc(5) + pow(Zeta, 2.0) * EffXsc(4);

   rXsec = EfXsc * 4.0 * x / (1.0 + chPsi2);       // DESY Reduced xSec.

   if(iXsc > 0){                            // My Effective xSce. needed only
     EfXsc = EfXsc * pow((4.0 * Pi * AlfEwk(1)), 2.0);   // for iXsc > 0 calculations later
   }
 }
 else if(abs(iLptn1 - iLptn2) == 1){     // Charged Current
   if((iLptn1 - iLptn2) == -1){             // W+ exchange
     EfXsc = EffXsc(2);
   }
   else if(iLptn1-iLptn2 == 1){         // W- exchange
     EfXsc = EffXsc(3);
   }
   rXsec = EfXsc * x * pow(y, 2) / 2.0 / (double)nPol(iLptn1); // DESY-type Reduced xSec.

   if(iXsc > 0){                           // My Effective xSce. needed only
     double wMas2 = pow(vBnMas(2), 2.0);                         // for iXsc > 0 calculations later
     EfXsc = EfXsc * pow((wMas2 *Q2 *Gf /(Q2 +wMas2)), 2.0) /2.0;
   }

 }
 else{
   rXsec = 0;
   EfXsc = 0;

   cout<<"Warning: iLptn1,2 = "<<iLptn1<<"  "<<iLptn2<<endl;
   cout<<" illegal in xSecLh call!"<<endl;
 }

 double Value = 0.0;

 if(iXsc == 0){// DESY Reduced xSec
   Value = rXsec;
 }
 else if(iXsc == 1){// My Effective xSce.
   Value = EfXsc;
 }
 else if(iXsc == 2){// dSig/dx dy
   Value = EfXsc * y /(2.0*Pi*Q2*(double)nPol(iLptn1)) * XsGv2pb;
 }
 else if(iXsc == 3){// dSig/dx dQ^2
   Value = EfXsc * pow(y, 2.0) /(2.0*Pi*Q2*Q2*(double)nPol(iLptn1)) * XsGv2pb;
 }
 else if(iXsc == 4){// dSig/dE dcos
   cout<<"temporary stop in lhXsec: tem is not defined"<<endl;
   return 0.0;
 }
 else if(iXsc == 5){// H1 combined data
   Value = rXsec;
 }
 else{
   cout<<"iXsc = "<<iXsc<<"  illegal in xSecLh call!"<<endl;
   return 0.0;
 }

 //cout<<"iLptn1 = "<<iLptn1<<" iLptn2 = "<<iLptn2<<" iHadn = "<<iHadn<<" x = "<<x<<" Q = "<<Q<<" y = "<<y<<" iFlv = "<<iFlv<<" iXsc = "<<iXsc<<endl;


                                      // Avoid returning zero answer
 if(Value < Ssml) Value = Ssml;

 return Value;
}

