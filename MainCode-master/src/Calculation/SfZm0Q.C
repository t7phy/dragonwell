#include "Calculation/CalcDIS.h"

void CalcDIS::SfZm0Q(int iHadn, int iPrtn, double x, double Q, double aMu, FortranArray1D<double> &SfnG)
{
//-----------------------------------------------------------------------------
//      Computes ZM LO Hadron Structure Functions SfnG 
//          -- individual contribution from Iprtn in the initial state
//
//        (x, Q) are input kinematic variables;
//        aMu is the factorization scale, which does not have to be equal to Q.
//-----------------------------------------------------------------------------

 FortranArray1D<double> OmgLo{1, 5};
 OmgLo(1) = 0.5;
 OmgLo(2) = 0.0;
 OmgLo(3) = 0.0;
 OmgLo(4) = 0.0;
 OmgLo(5) = 0.5;

 for(int i = 1; i <= 5; i++){
   SfnG(i) = OmgLo(i) * GetPDF(iHadn, iPrtn, x, aMu);
 }
}

void CalcDIS::SfZm1G(int iHadn, double x, double Q, double vMu, FortranArray1D<double> &SfnG)
{
//  ****** contribution to SF due to initial state gluon-boson fusion diagrams,
//  without the EW coupling--hence this is for one particular quark-antiquark pair
//              (i.e. the result is flavor-independent);
//  Also not included is the overall \alpha_s / 2pi factor.
//
//          Formulas from Furmanski & Petronzio
//           ----------------------------------------------
 int IR = 0;
 double ER;
 double Smll = 1e-6;

 CSfZm1G_iHadn = iHadn;
 CSfZm1G_x = x;
 CSfZm1G_aMu = vMu;

 if(!isDefineGluonFunctions) DefineFunctions_gluon();

 double a5 = 1.0 - 0.00000000001*(1.0 - x);

//                                                            ! F2 integral
// xx      F2G1 = AdzInt(aC2G1,    x, 1d0, aErr, rErr, ER, IR, 2, 1)
 double F2G1 =
               SMPSNF(aC2G1,x + 0.00000000001*(a5-x),
                            x + 0.0000001*(a5-x),4, ER, IR)
             + SMPSNF(aC2G1,x + 0.0000001*(a5-x),
                            x + 0.000001*(a5-x),4, ER, IR)
             + SMPSNF(aC2G1,x + 0.000001*(a5-x),
                            x + 0.00001*(a5-x),4, ER, IR)
             + SMPSNF(aC2G1,x + 0.00001*(a5-x),
                            x + 0.0001*(a5-x),4, ER, IR)
             + SMPSNF(aC2G1,x + 0.0001*(a5-x),
                            x + 0.001*(a5-x),4, ER, IR)
             + SMPSNF(aC2G1,x + 0.001*(a5-x),
                            x + 0.01*(a5-x),4, ER, IR)
             + SMPSNF(aC2G1,x + 0.01*(a5-x),
                            x + 0.1*(a5-x),8, ER, IR)
             + SMPSNF(aC2G1,x + 0.1*(a5-x),
                            x + 0.9*(a5-x),16, ER, IR)
             + SMPSNF(aC2G1,x + 0.9*(a5-x),
                            x + 0.99*(a5-x),8, ER, IR)
             + SMPSNF(aC2G1,x + 0.99*(a5-x),
                            x + 0.999*(a5-x),4, ER, IR)
             + SMPSNF(aC2G1,x + 0.999*(a5-x),
                            x + 0.9999*(a5-x),4, ER, IR)
             + SMPSNF(aC2G1,x + 0.9999*(a5-x),
                            x + 0.99999*(a5-x),4, ER, IR)
             + SMPSNF(aC2G1,x + 0.99999*(a5-x),
                            x + 0.999999*(a5-x),4, ER, IR)
             + SMPSNF(aC2G1,x + 0.999999*(a5-x),a5,4, ER, IR);

//                                                            ! F2 - F1 integral
// xx      F2MF1G1 = AdzInt(aC2MC1G1, x, 1d0, aErr, rErr, ER, IR, 2, 1)
 a5 = 1.0 - 0.00000000001*(1.0 - x);
 double F2MF1G1 =
                  SMPSNF(aC2MC1G1,x + 0.00000000001*(a5-x),
                                  x + 0.0000001*(a5-x),4, ER, IR)
                + SMPSNF(aC2MC1G1,x + 0.0000001*(a5-x),
                                  x + 0.000001*(a5-x),4, ER, IR)
                + SMPSNF(aC2MC1G1,x + 0.000001*(a5-x),
                                  x + 0.00001*(a5-x),4, ER, IR)
                + SMPSNF(aC2MC1G1,x + 0.00001*(a5-x),
                                  x + 0.0001*(a5-x),4, ER, IR)
                + SMPSNF(aC2MC1G1,x + 0.0001*(a5-x),
                                  x + 0.001*(a5-x),4, ER, IR)
                + SMPSNF(aC2MC1G1,x + 0.001*(a5-x),
                                  x + 0.01*(a5-x),4, ER, IR)
                + SMPSNF(aC2MC1G1,x + 0.01*(a5-x),
                                  x + 0.1*(a5-x),8, ER, IR)
                + SMPSNF(aC2MC1G1,x + 0.1*(a5-x),
                                  x + 0.9*(a5-x),16, ER, IR)
                + SMPSNF(aC2MC1G1,x + 0.9*(a5-x),
                                  x + 0.99*(a5-x),8, ER, IR)
                + SMPSNF(aC2MC1G1,x + 0.99*(a5-x),
                                  x + 0.999*(a5-x),4, ER, IR)
                + SMPSNF(aC2MC1G1,x + 0.999*(a5-x),
                                  x + 0.9999*(a5-x),4, ER, IR)
                + SMPSNF(aC2MC1G1,x + 0.9999*(a5-x),
                                  x + 0.99999*(a5-x),4, ER, IR)
                + SMPSNF(aC2MC1G1,x + 0.99999*(a5-x),a5,4, ER, IR);

//                                         ! F_transv = (F_R + F_L)/2= F1 /2 
 SfnG(1) = (F2G1 - F2MF1G1) / 2.0;
//                                         ! F_long = (F2 - F1) / 2
 SfnG(3) = F2MF1G1 / 2.0;
//                                      
 SfnG(2) = 0.0;        // Zero-mass case has no chirality-mixing terms
 SfnG(4) = 0.0;        // Zero-mass case has no chirality-mixing terms
 SfnG(5) = 0.0;        // Gluon term does not have parity violating term

                                     // Log(Q/mu) term:
 if(fabs(Q / vMu - 1.0) > Smll){
// **      Qmu = AdzInt(aPgqFx, X, 1d0, aErr, rErr, ER, IR, 1, 1)
   a5 = 1.0 - 0.00000000001*(1.0-x);

   double Qmu =
                SMPSNF(aPgqFx,x + 0.00000000001*(a5-x),
                              x + 0.000001*(a5-x),4, ER, IR)
              + SMPSNF(aPgqFx,x + 0.000001*(a5-x),
                              x + 0.00001*(a5-x),4, ER, IR)
              + SMPSNF(aPgqFx,x + 0.00001*(a5-x),
                              x + 0.0001*(a5-x),4, ER, IR)
              + SMPSNF(aPgqFx,x + 0.0001*(a5-x),
                              x + 0.001*(a5-x),4, ER, IR)
              + SMPSNF(aPgqFx,x + 0.001*(a5-x),
                              x + 0.01*(a5-x),8, ER, IR)
              + SMPSNF(aPgqFx,x + 0.01*(a5-x),
                              x + 0.1*(a5-x),16, ER, IR)
              + SMPSNF(aPgqFx,x + 0.1*(a5-x),
                              x + 0.9*(a5-x),32, ER, IR)
              + SMPSNF(aPgqFx,x + 0.9*(a5-x),
                              x + 0.99*(a5-x),16, ER, IR)
              + SMPSNF(aPgqFx,x + 0.99*(a5-x),
                              x + 0.999*(a5-x),8, ER, IR)
              + SMPSNF(aPgqFx,x + 0.999*(a5-x),
                              x + 0.9999*(a5-x),4, ER, IR)
              + SMPSNF(aPgqFx,x + 0.9999*(a5-x),
                              x + 0.99999*(a5-x),4, ER, IR)
              + SMPSNF(aPgqFx,x + 0.99999*(a5-x),
                              x + 0.999999*(a5-x),4, ER, IR)
              + SMPSNF(aPgqFx,x + 0.999999*(a5-x),a5,4, ER, IR);

   FortranArray1D<double> OmgLo{1, 5};
   OmgLo(1) = 0.5;
   OmgLo(2) = 0.0;
   OmgLo(3) = 0.0;
   OmgLo(4) = 0.0;
   OmgLo(5) = 0.5;

   for(int i = 1; i <= 5; i++){
     SfnG(i) = SfnG(i) + 2.0 * OmgLo(i) * log(Q / vMu) * Qmu;
   }

 }

 for(int i = 1; i <= 5; i++){
   SfnG(i) = SfnG(i) * TR;// QCD color factor
 }
}

void CalcDIS::SfZm1Q(int iHadn, int iPrtn, double x, double Q, double vMu, FortranArray1D<double> &SfnG)
{
//  ****** contribution to the general SfnG due to initial state quark parton iPrtn
//  without the EW coupling--the result is flavor-independent;
//  Also not included is the overall \alpha_s / 2pi factor.
//
//          Formulas from Furmanski & Petronzio
//           ----------------------------------------------
 int IR = 0;
 double ER;
 double Smll = 1e-6;

 CSfZm1Q_iHadn= iHadn;
 CSfZm1Q_iPartn = iPrtn;
 CSfZm1Q_x    = x;
 CSfZm1Q_aMu  = vMu;

 CSfZm1Q_Pdfnx = GetPDF(iHadn, iPrtn, x, vMu);
                                // For F2Q, this is the \delta(1-z) term               
                        // here we use the analytic result for the  
                        // integral of aC2Q1 to speed up the computation  
//marco11 Old implementation
//      F2Qa = AdzInt(aC2Q1, 0d0, x, aErr, rErr, ER, IR, 1, 0) 
//     >     * Pdfnx
 double AdzIntRes = (-2.0*pow(log(1.0 - x), 2.0) - log(1.0 - x)*(-6.0 + 2.0*x + pow(x, 2.0) -4.0*log(x)) + x*(7.0 + 2.0*x + (2.0 + x)*log(x))+ 4.0*xLi(2,x))/2.0;
 double F2Qa = AdzIntRes * CSfZm1Q_Pdfnx;

 if(!isDefineQuarkFunctions) DefineFunctions_quark();

 double a5 = 1.0 - 0.00000000001 * (1.0 - x);

 double F2Qb =
               SMPSNF(aF2Q1,x + 0.00000000001*(a5-x),
                            x + 0.00000001*(a5-x),4, ER, IR)
             + SMPSNF(aF2Q1,x + 0.00000001*(a5-x),
                            x + 0.0000001*(a5-x),4, ER, IR)
             + SMPSNF(aF2Q1,x + 0.0000001*(a5-x),
                            x + 0.000001*(a5-x),4, ER, IR)
             + SMPSNF(aF2Q1,x + 0.000001*(a5-x),
                            x + 0.00001*(a5-x),4, ER, IR)
             + SMPSNF(aF2Q1,x + 0.00001*(a5-x),
                            x + 0.0001*(a5-x),4, ER, IR)
             + SMPSNF(aF2Q1,x + 0.0001*(a5-x),
                            x + 0.001*(a5-x),4, ER, IR)
             + SMPSNF(aF2Q1,x + 0.001*(a5-x),
                            x + 0.01*(a5-x),4, ER, IR)
             + SMPSNF(aF2Q1,x + 0.01*(a5-x),
                            x + 0.1*(a5-x),8, ER, IR)
             + SMPSNF(aF2Q1,x + 0.1*(a5-x),
                            x + 0.9*(a5-x),16, ER, IR)
             + SMPSNF(aF2Q1,x + 0.9*(a5-x),
                            x + 0.99*(a5-x),8, ER, IR)
             + SMPSNF(aF2Q1,x + 0.99*(a5-x),
                            x + 0.999*(a5-x),4, ER, IR)
             + SMPSNF(aF2Q1,x + 0.999*(a5-x),
                            x + 0.9999*(a5-x),4, ER, IR)
             + SMPSNF(aF2Q1,x + 0.9999*(a5-x),
                            x + 0.99999*(a5-x),4, ER, IR)
             + SMPSNF(aF2Q1,x + 0.99999*(a5-x),
                            x + 0.999999*(a5-x),4, ER, IR)
             + SMPSNF(aF2Q1,x + 0.999999*(a5-x),
                            x + 0.9999999*(a5-x),4, ER, IR)
             + SMPSNF(aF2Q1,x + 0.9999999*(a5-x),a5,4, ER, IR);


                                     // The F2-F1 (2*Flong) term

// xx      F2m1Q = AdzInt(G2M1Q1, X, 1d0, aErr, rErr, ER, IR, 0, 0)

 double F2m1Q = SMPSNF(G2M1Q1,x,1.0,32, ER, IR);

// xx      F1m3Q = AdzInt(G1M3Q1, X, 1d0, aErr, rErr, ER, IR, 0, 0)

                                     // The F1-F3 (2*Fright) term
 a5 = 1.0 - 0.00000000001*(1.0-x);

 double F1m3Q =
                SMPSNF(G1M3Q1,x + 0.00000000001*(a5-x),
                              x + 0.00000001*(a5-x),4, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.00000001*(a5-x),
                              x + 0.0000001*(a5-x),4, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.0000001*(a5-x),
                              x + 0.000001*(a5-x),4, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.000001*(a5-x),
                              x + 0.00001*(a5-x),4, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.00001*(a5-x),
                              x + 0.0001*(a5-x),4, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.0001*(a5-x),
                              x + 0.001*(a5-x),4, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.001*(a5-x),
                              x + 0.01*(a5-x),4, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.01*(a5-x),
                              x + 0.1*(a5-x),8, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.1*(a5-x),
                              x + 0.9*(a5-x),16, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.9*(a5-x),
                              x + 0.99*(a5-x),8, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.99*(a5-x),
                              x + 0.999*(a5-x),4, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.999*(a5-x),
                              x + 0.9999*(a5-x),4, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.9999*(a5-x),
                              x + 0.99999*(a5-x),4, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.99999*(a5-x),
                              x + 0.999999*(a5-x),4, ER, IR)
              + SMPSNF(G1M3Q1,x + 0.999999*(a5-x),a5,4, ER, IR);

 double F2 = F2Qb - F2Qa;
 double F1 = F2 - F2m1Q;                // F1 = F2 - (F2-F1)
 SfnG(1) = F1 / 2.0;             // SfnG_1 = F1/2
 SfnG(3) = F2m1Q / 2.0;          // SfnG_3 = Flong = (F2-F1)/2
 SfnG(2) = 0.0;        // Zero-mass case has no chirality-mixing terms
 SfnG(4) = 0.0;        // Zero-mass case has no chirality-mixing terms
 double F3 =  F1 - F1m3Q;
 SfnG(5) = F3 / 2.0;             // SfnG_5 = F3/2 

                                     // Log(Q/mu) term:
 if (fabs(Q / vMu - 1.0) > Smll){
                         // delta(1-z) term
                        // here we use the analytic result for the  
                        // integral of aPqq to speed up the computation  
//marco11 Old implementation
//      Qmu1 =  AdzInt(aPqq,  0d0, x, aErr, rErr, ER, IR, 1, 0)    
//     >     * Pdfnx                                          
   double Qmu1 = (-0.5 * x * (2.0 + x) - 2.0 * log(1.0 - x)) * CSfZm1Q_Pdfnx; // delta(1-z) term

// **      Qmu2 = AdzInt(aPqqFx, X, 1d0, aErr, rErr, ER, IR, 1, 1)     ! regular term
   a5 = 1.0 - 0.00000000001 * (1.0 - x);

   double Qmu2 =
                 SMPSNF(aPqqFx,x + 0.00000000001*(a5-x),
                               x + 0.000001*(a5-x),4, ER, IR)
               + SMPSNF(aPqqFx,x + 0.000001*(a5-x),
                               x + 0.00001*(a5-x),4, ER, IR)
               + SMPSNF(aPqqFx,x + 0.00001*(a5-x),
                               x + 0.0001*(a5-x),4, ER, IR)
               + SMPSNF(aPqqFx,x + 0.0001*(a5-x),
                               x + 0.001*(a5-x),4, ER, IR)
               + SMPSNF(aPqqFx,x + 0.001*(a5-x),
                               x + 0.01*(a5-x),8, ER, IR)
               + SMPSNF(aPqqFx,x + 0.01*(a5-x),
                               x + 0.1*(a5-x),16, ER, IR)
               + SMPSNF(aPqqFx,x + 0.1*(a5-x),
                               x + 0.9*(a5-x),32, ER, IR)
               + SMPSNF(aPqqFx,x + 0.9*(a5-x),
                               x + 0.99*(a5-x),16, ER, IR)
               + SMPSNF(aPqqFx,x + 0.99*(a5-x),
                               x + 0.999*(a5-x),8, ER, IR)
               + SMPSNF(aPqqFx,x + 0.999*(a5-x),
                               x + 0.9999*(a5-x),4, ER, IR)
               + SMPSNF(aPqqFx,x + 0.9999*(a5-x),
                               x + 0.99999*(a5-x),4, ER, IR)
               + SMPSNF(aPqqFx,x + 0.99999*(a5-x),
                               x + 0.999999*(a5-x),4, ER, IR)
               + SMPSNF(aPqqFx,x + 0.999999*(a5-x),a5,4, ER, IR);

   FortranArray1D<double> OmgLo{1, 5};
   OmgLo(1) = 0.5;
   OmgLo(2) = 0.0;
   OmgLo(3) = 0.0;
   OmgLo(4) = 0.0;
   OmgLo(5) = 0.5;

   for(int i = 1; i <= 5; i++){
     SfnG(i) = SfnG(i) + 2.0 * OmgLo(i) * log(Q / vMu) * (Qmu2 - Qmu1);
   }
 }

 for(int i = 1; i <= 5; i++){
   SfnG(i) = SfnG(i) * CF;// QCD color factor
 }

}

void CalcDIS::DefineFunctions_gluon()
{
 aC2G1 = [&](double z){// Integrand for the F2_G integral
   double Pdfnxz = GetPDF(CSfZm1G_iHadn, 0, CSfZm1G_x / z, CSfZm1G_aMu);
   double C2G1A = ((pow(z, 2.0) + pow((1.0 - z), 2.0)) * log((1.0 - z) / z) - 1.0 + 8.0 * z * (1.0 - z));
   return C2G1A * Pdfnxz / z;
 };

 aC2MC1G1 = [&](double z){// Integrand for the gluon F2 - F1 integral
   double Pdfnxz = GetPDF(CSfZm1G_iHadn, 0, CSfZm1G_x / z, CSfZm1G_aMu);
   double C2MC1G1A = 4.0 * z * (1.0 - z);
   return C2MC1G1A * Pdfnxz / z;
 };

 aPgqFx = [&](double z){// Integrand for the gluon Log(Q/mu) integral
   double Pdfnxz = GetPDF(CSfZm1G_iHadn, 0, CSfZm1G_x / z, CSfZm1G_aMu);// The gluon PDF
   double SpltFn = (pow(z, 2.0) + pow((1.0 - z), 2.0)) / 2.0;//The gluon-->quark splitting fn
   return SpltFn * Pdfnxz / z;//The integrand
 };

 isDefineGluonFunctions = true;
}

void CalcDIS::DefineFunctions_quark()
{
/* if(!isDefineGluonFunctions){
   cout<<"Define gluon functions at first."<<endl;
   DefineFunctions_gluon();
 }
*/

 aC2Q1 = [&](double z){// integrand for the \delta function term
   return ((1.0+ pow(z, 2.0)) *(log((1.0 - z) / z) - 3.0 / 4.0) / (1.0 - z)) + (9.0 + 5.0 * z) / 4.0;
 };

 aF2Q1 = [&](double z){// integrand for the F2 term
   double Pdfnxz = GetPDF(CSfZm1Q_iHadn, CSfZm1Q_iPartn, CSfZm1Q_x / z, CSfZm1Q_aMu);
   return aC2Q1(z) * (Pdfnxz / z - CSfZm1Q_Pdfnx);
 };

 G2M1Q1 = [&](double z){// integrand for the Flong term = (F2 - F1)/2
   double Pdfnxz = GetPDF(CSfZm1Q_iHadn, CSfZm1Q_iPartn, CSfZm1Q_x / z, CSfZm1Q_aMu);
   return 2.0 * z * Pdfnxz / z;
 };

 G1M3Q1 = [&](double z){// integrand for the Fright term = (F1 - F3)/2
   double Pdfnxz = GetPDF(CSfZm1Q_iHadn, CSfZm1Q_iPartn, CSfZm1Q_x / z, CSfZm1Q_aMu);
   return (1.0 - z) * Pdfnxz / z;
 };

 aPqq = [&](double z){
   return (1.0 + pow(z, 2.0)) / (1.0 - z);
 };

 aPqqFx = [&](double z){
   double Pdfnxz = GetPDF(CSfZm1Q_iHadn, CSfZm1Q_iPartn, CSfZm1Q_x / z, CSfZm1Q_aMu);
   return aPqq(z) * (Pdfnxz / z - CSfZm1Q_Pdfnx);
 };

 isDefineQuarkFunctions = true;
}


