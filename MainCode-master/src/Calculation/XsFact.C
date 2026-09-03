#include "Calculation/CalcVBP.h"

void CalcVBP::XsFact(int IXsec, int Ibsn, double &FAC0, double &FAC01, map<int, double> &FAC1, int N1)
{
//                 Returns the overall (kinematic-variable-independent) factors
//          factors for the various terms in the QCD-based parton model formula.
//
//          IXsec = 1  real vector boson production
//                  2  continuum lepton-pair production
//       
//           N1 is the # of different types of Next-to-Leading parton processes.
//                                     Ibsn is the ID for the Produced Particle.
//
//     VBP-Version                                       Vector-Boson Production
//                                                       -      -     -
//       N1 = 2  --- we have either the "Annihilation" or the "Compton" process.
//                                                       Ibsn is the VB code

 if(N1 != 2){
   cout<<"N1 .NE. 2 in XSFACT for VBP"<<endl;
 }

//                                                ------------------------------
//                                                           Coupling parameters
 double Alf = AlfEwk(Ibsn);
//                                                ------------------------------
//                                 Section on Zeroth order process:  a + b --> P
//                                                    Overall kinematic factor:
 double FK0 = Pi;
//                                                   pro-ind
//                                                   spin - color average - sum
 double FA0 = 1.0 / 2.0 / 2.0 / 3.0;
//                           kinematic-variable-indep factor from matrix elments
//                                       (e.g. coupling constants .. etc)
 double FM0 = Alf * 16.0 * Pi;
//
 FAC0 = FK0 * FA0 * FM0;
//                                                  ----------------------------
//                               For LPP, multiply by appropriate overall factor

 if(IXsec == 2) FAC0 = FAC0 * Alf / 3.0 / Pi;
//                                                  ----------------------------
//                                   We set FAC1=FAC0 since the formulas used in
//                                   the program proper are normalized this way.
  FAC1[1] = FAC0;
  FAC1[2] = FAC0;
//                        FAC01 is not used in this zero-mass subtraction scheme
}

void CalcVBP::KineLmt(double Rs, double p1m, double p2m, double &yMx, double &ptMx)
{
//                                                 Max. y1 occurs at p_t = 0:
 double CHYM = (Rs*Rs + p1m*p1m - p2m*p2m) / 2.0 / Rs / p1m;
 double SHYM = sqrt (CHYM * CHYM - 1.0);
 yMx = log (CHYM + SHYM);
//                                                                                 Max. p_t = Abs(3-mom):
 double ptMx2 = pow(((Rs*Rs +p1m*p1m -p2m*p2m) /2.0 /Rs), 2.0) - p1m*p1m;
 ptMx = sqrt(ptMx2);
}

