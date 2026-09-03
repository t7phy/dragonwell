#include "Calculation/CalcDIS.h"

double CalcDIS::StrFnGm(int iHadn, int iCmptn, double x, double Q, int iSfn, int iFlv)
{
//     ! Invokes SFnGm.f to get the full set of tensor and helicity S.F.s F_{1,2,3} and F_{-1,0,1};
//     ! Returns the relevant S.F. to the calling program, according to the argument iSfn:
//
//     ! iSfn : 1, 2, 3    ==> F_{1,2,3}/Prefactor
//     !       -1, 0, -2   ==> F_{left, longitudinal, right}/Prefactor  ("1" is used for F_1)
//     !
//     ! Prefactor is defined in CalculateDIS (2*x for F_L, x otherwise)
//
//     ! iFlv : 0   (total inclusive---sum over all active quark-parton flavors);
//     !       -6:6 (individual flavors);
//     !       11:16 (quark+antiquark).                            ! ---------------------!
//
//
// 2006.12.06:
//             ! New input argument iFlv introduced; common block to store heavy flavor S.F.s deleted.
//             ! Logic of the calculation of heavy flavor S.F.s drastically simplified by HLL.
//             ! New option for choice of factorization scale (iFscle=3) for HQ production added.
//
// 2005.12.25: original version.

 double Ssml = 1e-20;
 FortranArray1D<double> Sfn123{1, 3};
 FortranArray1D<double> SfnHel{-1, 1};

                          // ---------------------------
                                                      // Calculate the structure functions
 SfnGm(iHadn, iCmptn, iFlv, x,Q, Sfn123, SfnHel);
                                                // Assign the relevant SF to the function call

 double Value = 0.0;

 if(iSfn == 0){// Longitudinal Structure function
   Value = SfnHel(0);
 }
 else if(iSfn == -1){// F_Left
   Value = SfnHel(-1);
 }
 else if(iSfn == -2){// F_Right
   Value = SfnHel(1);
 }
 else if(iSfn == 4){// Ratio = sig_long/sig_trans = F_L / (2xF_1) = F_0/((F_+ F_-)/2)
   Value = SfnHel(0)/ ((SfnHel(1)+SfnHel(-1))/2.0);
 }
 else if(iSfn == 1 || iSfn == 2 || iSfn == 3){// Conventional F_1,2,3
   Value = Sfn123(iSfn);
 }
 else{
   cout<<"iSfn = "<<iSfn<<" is not allowed in StrFnGm!"<<endl;
 }

 if(fabs(Value) < Ssml) Value = Ssml;     // Avoid returning zero

 return Value;
}

double CalcDIS::StrFnGm_N3LO(int iHadn, int iCmptn, double x, double Q, int iSfn, int iFlv)
{
//     ! Invokes SFnGm.f to get the full set of tensor and helicity S.F.s F_{1,2,3} and F_{-1,0,1};
//     ! Returns the relevant S.F. to the calling program, according to the argument iSfn:
//
//     ! iSfn : 1, 2, 3    ==> F_{1,2,3}/Prefactor
//     !       -1, 0, -2   ==> F_{left, longitudinal, right}/Prefactor  ("1" is used for F_1)
//     !
//     ! Prefactor is defined in CalculateDIS (2*x for F_L, x otherwise)
//
//     ! iFlv : 0   (total inclusive---sum over all active quark-parton flavors);
//     !       -6:6 (individual flavors);
//     !       11:16 (quark+antiquark).                            ! ---------------------!
//
//
// 2006.12.06:
//             ! New input argument iFlv introduced; common block to store heavy flavor S.F.s deleted.
//             ! Logic of the calculation of heavy flavor S.F.s drastically simplified by HLL.
//             ! New option for choice of factorization scale (iFscle=3) for HQ production added.
//
// 2005.12.25: original version.

 double Ssml = 1e-20;
 FortranArray1D<double> Sfn123{1, 3};
 FortranArray1D<double> SfnHel{-1, 1};

                          // ---------------------------
                                                      // Calculate the structure functions
 if(!DisSet) mSetDis();
 if(!isInitializeHoppetSF) InitializeHoppetSF();

 SfnGm_N3LO(iHadn, iCmptn, iFlv, x,Q, Sfn123, SfnHel);
                                                // Assign the relevant SF to the function call

 double Value = 0.0;

 if(iSfn == 0){// Longitudinal Structure function
   Value = SfnHel(0);
 }
 else if(iSfn == -1){// F_Left
   Value = SfnHel(-1);
 }
 else if(iSfn == -2){// F_Right
   Value = SfnHel(1);
 }
 else if(iSfn == 4){// Ratio = sig_long/sig_trans = F_L / (2xF_1) = F_0/((F_+ F_-)/2)
   Value = SfnHel(0)/ ((SfnHel(1)+SfnHel(-1))/2.0);
 }
 else if(iSfn == 1 || iSfn == 2 || iSfn == 3){// Conventional F_1,2,3
   Value = Sfn123(iSfn);
 }
 else{
   cout<<"iSfn = "<<iSfn<<" is not allowed in StrFnGm!"<<endl;
 }

 if(fabs(Value) < Ssml) Value = Ssml;     // Avoid returning zero

 return Value;
}

