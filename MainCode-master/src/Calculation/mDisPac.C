#include "Calculation/mDisPac.h"

mDisPac::mDisPac()
{
 AA(1) = 1.0; AA(2) = 2.0; AA(3) = 3.0;
 AB(-1) = -1.0; AB(0) = 0.0; AB(1) = 1.0;

}

void mDisPac::mSetDis()
{
 FortranArray1D<double> gL{1, 2};
 FortranArray1D<double> gR{1, 2};

 int nFlv = 6;

 for(int iBn = 1; iBn <= 4; iBn++){
   g2Bn(iBn) = AlfEwk(iBn) * 4.0 * Pi;
 }
 g2Bn(-1) = g2Bn(2); // these are for W+/W- combos => the same gauge coupling
 g2Bn(0) = g2Bn(2);

 for(int jCmptn = 1; jCmptn <= 5; jCmptn++){// The forward Compton Amplitudes have 5 indep. combinations
                                            // of incoming and outgoing vector bosons:
   if(jCmptn <= 4){
     iBsn(1, jCmptn) = jCmptn;
     iBsn(2, jCmptn) = jCmptn;
   }
   else if(jCmptn == 5){
     iBsn(1, jCmptn) = 1;
     iBsn(2, jCmptn) = 4;
   }
 }

 FortranArray2D<int> iLptn2{1, 2, 1, 5};
 iLptn2(1, 1) = 1; // final-state lepton for iLptn1 = 1
 iLptn2(1, 2) = 2;
 iLptn2(1, 3) = 0;
 iLptn2(1, 4) = 1;
 iLptn2(1, 5) = 1;
 iLptn2(2, 1) = 2; // final-state lepton for iLptn1 = 2
 iLptn2(2, 2) = 0;
 iLptn2(2, 3) = 1;
 iLptn2(2, 4) = 2;
 iLptn2(2, 5) = 2;

 for(int iLep1 = 1; iLep1 <= 2; iLep1++){
   for(int jCmptn = 1; jCmptn <= 5; jCmptn++){
     int iLep2 = iLptn2(iLep1, jCmptn);
                                     // For the lepton vertex, the Boson is "outgoing".
                                     // In the EwkPac def., the boson is "incoming".
                                     // Therefore, we need to interchange W+/W- here:
     int j;
     if(jCmptn == 2) j = 3;
     else if(jCmptn == 3) j = 2;
     else j = jCmptn;

     if(iLep2 != 0){
       gL(1) = gEWlH(iLep1, iBsn(1, j), -1,  iLep2);
       gR(1) = gEWlH(iLep1, iBsn(1, j),  1,  iLep2);
       if(jCmptn == 5){
         gL(2)= gEWlH(iLep1, iBsn(2, j), -1,  iLep2);
         gR(2)= gEWlH(iLep1, iBsn(2, j),  1,  iLep2);
       }
       else{
         gL(2) = gL(1);
         gR(2) = gR(1);
       }
     }
     else{
       gL(1) = 0.0;
       gR(1) = 0.0;
       gL(2) = 0.0;
       gR(2) = 0.0;
     }

     g2Lp(iLep1, jCmptn) = (gL(1) * gL(2) + gR(1) * gR(2));  // parity conserving coupling combination
                                                             // g_V g_V + g_A g_A (1,2 labels omitted)
     g2Lm(iLep1, jCmptn) = (gL(1) * gL(2) - gR(1) * gR(2));  // parity violating  coupling combination
                                                             // g_V g_A + g_A g_V
     g2Lp(iLep2 * (-1), jCmptn) =  g2Lp(iLep1, jCmptn);
     g2Lm(iLep2 * (-1), jCmptn) =  g2Lm(iLep1, jCmptn) * (-1.0);
   }
 }

 for(int iPrtn1 = -nFlv; iPrtn1 <= nFlv; iPrtn1++){
   for(int iPrtn2 = -nFlv; iPrtn2 <= nFlv; iPrtn2++){
     for(int jCmptn = 1; jCmptn <= 5; jCmptn++){
       for(int k = 1; k <= 2; k++){
         if(iPrtn1 > 0 && iPrtn2 > 0){
           gL(k) = gEWqH(iPrtn1, iBsn(k,jCmptn), -1, iPrtn2);
           gR(k) = gEWqH(iPrtn1, iBsn(k,jCmptn),  1, iPrtn2);
         }
         else if(iPrtn1 < 0 && iPrtn2 < 0){
           gL(k) = gEWqH(iPrtn2 * (-1), iBsn(k,jCmptn),  1, iPrtn1 * (-1));
           gR(k) = gEWqH(iPrtn2 * (-1), iBsn(k,jCmptn), -1, iPrtn1 * (-1));
         }
         else{
           gL(k) = 0.0;
           gR(k) = 0.0;
         }
       }
//                                            Compute coupling combinations and store in mDisPac                                      
       g2p(iPrtn1, jCmptn, iPrtn2) = 2.0 * (gL(1) * gL(2) + gR(1) * gR(2));   // parity conserving coupling combination
                                                                              // g_V g_V + g_A g_A (1,2 labels omitted)
       g2m(iPrtn1, jCmptn, iPrtn2) = 2.0 * (gL(1) * gL(2) - gR(1) * gR(2));   // parity violating  coupling combination
                                                                              // g_V g_A + g_A g_V
       g2x(iPrtn1, jCmptn, iPrtn2) = 2.0 * (gL(1) * gR(2) + gR(1) * gL(2));   // chirality violating coupling combination
                                                                              // g_V g_V - g_A g_A (1,2 labels omitted)
       //cout<<iPrtn1<<"  "<<iPrtn2<<"  "<<gL(1)<<"  "<<gL(2)<<"  "<<gR(1)<<"  "<<gR(2)<<endl;

                      // ---- Combine them ------
       g2q(1, iPrtn1, jCmptn, iPrtn2) = g2p(iPrtn1, jCmptn, iPrtn2);
       g2q(2, iPrtn1, jCmptn, iPrtn2) = g2x(iPrtn1, jCmptn, iPrtn2);
       g2q(3, iPrtn1, jCmptn, iPrtn2) = g2m(iPrtn1, jCmptn, iPrtn2);
                      // convenient measure of the "strength" of the coupling
                      // (Useful as test for uncoupled channels.)
       g2q(0,iPrtn1,jCmptn,iPrtn2) = pow(g2p(iPrtn1,jCmptn,iPrtn2), 2.0)
                                               + pow(g2x(iPrtn1,jCmptn,iPrtn2), 2.0)
                                               + pow(g2m(iPrtn1,jCmptn,iPrtn2), 2.0);

     }
                // Form (W+ +/- W-) combinations, useful for some neutrino experiments
                // Notice that the parity-violating F_3 changes sign in these combinations
      g2q(1, iPrtn1, 0, iPrtn2) = 0.5 * (g2q(1, iPrtn1, 2, iPrtn2) + g2q(1, iPrtn1, 3, iPrtn2) * 1.0);
      g2q(2, iPrtn1, 0, iPrtn2) = 0.5 * (g2q(2, iPrtn1, 2, iPrtn2) + g2q(2, iPrtn1, 3, iPrtn2) * 1.0);
      g2q(3, iPrtn1, 0, iPrtn2) = 0.5 * (g2q(3, iPrtn1, 2, iPrtn2) + g2q(3, iPrtn1, 3, iPrtn2) * (-1.0));
      g2q(1, iPrtn1, -1, iPrtn2) = 0.5 * (g2q(1, iPrtn1, 2, iPrtn2) - g2q(1, iPrtn1, 3, iPrtn2) * 1.0);
      g2q(2, iPrtn1, -1, iPrtn2) = 0.5 * (g2q(2, iPrtn1, 2, iPrtn2) - g2q(2, iPrtn1, 3, iPrtn2) * 1.0);
      g2q(3, iPrtn1, -1, iPrtn2) = 0.5 * (g2q(3, iPrtn1, 2, iPrtn2) - g2q(3, iPrtn1, 3, iPrtn2) * (-1.0));

      g2q(0, iPrtn1, -1, iPrtn2) = pow(g2q(1, iPrtn1, -1, iPrtn2), 2.0)
                                 + pow(g2q(2, iPrtn1, -1, iPrtn2), 2.0)
                                 + pow(g2q(3, iPrtn1, -1, iPrtn2), 2.0);
      g2q(0, iPrtn1,  0, iPrtn2) = pow(g2q(1, iPrtn1,  0, iPrtn2), 2.0)
                                 + pow(g2q(2, iPrtn1,  0, iPrtn2), 2.0)
                                 + pow(g2q(3, iPrtn1,  0, iPrtn2), 2.0);

   }
 }

                    // Now compute the combination of EW couplings that enter the 
                    // DIS SF calculation for each contributing incoming parton

 for(int jCmptn = 1; jCmptn <= 5; jCmptn++){
   double g2Gpc_tmp = 0.0;
   double g2Gpv_tmp = 0.0;
   for(int iPrtn1 = 1; iPrtn1 <= nFlv; iPrtn1++){// For each flavor, fill the quark and
                                                 // and the anti-quark entries in parallel
     double g2Qpc_tmp1 = 0.0;
     double g2Qpv_tmp1 = 0.0;
     double g2Qpc_tmp2 = 0.0;
     double g2Qpv_tmp2 = 0.0;

     for(int iPrtn2 = 1; iPrtn2 <= nFlv; iPrtn2++){
                                   // make sure coefficients have the requisite symmetry
       if(fabs(g2p(iPrtn1, jCmptn, iPrtn2) - g2p(iPrtn2 * (-1), jCmptn, iPrtn1 * (-1))) > 1e-3
       || fabs(g2x(iPrtn1, jCmptn, iPrtn2) - g2x(iPrtn2 * (-1), jCmptn, iPrtn1 * (-1))) > 1e-3
       || fabs(g2m(iPrtn1, jCmptn, iPrtn2) + g2m(iPrtn2 * (-1), jCmptn, iPrtn1 * (-1))) > 1e-3){
         cout<<"Bomb: "<<iPrtn1<<"  "<<jCmptn<<"  "<<iPrtn2<<endl;
         cout<<g2p(iPrtn1, jCmptn, iPrtn2)<<"  "<<g2p(iPrtn2 * (-1), jCmptn, iPrtn1 * (-1))<<endl;
         cout<<g2x(iPrtn1, jCmptn, iPrtn2)<<"  "<<g2x(iPrtn2 * (-1), jCmptn, iPrtn1 * (-1))<<endl;
         cout<<g2m(iPrtn1, jCmptn, iPrtn2)<<"  "<<g2m(iPrtn2 * (-1), jCmptn, iPrtn1 * (-1))<<endl;
       }
                                   // Quarks: for each flavor, sum over the final state iPrtn2:
       g2Qpc_tmp1 = g2Qpc_tmp1 + g2p( iPrtn1, jCmptn, iPrtn2);
       g2Qpv_tmp1 = g2Qpv_tmp1 + g2m( iPrtn1, jCmptn, iPrtn2);
                                   //  - iPrtn1 case is obtained by CP symmetry, when needed       
       g2Qpc_tmp2 = g2Qpc_tmp2 + g2p( iPrtn1 * (-1), jCmptn, iPrtn2 * (-1));
       g2Qpv_tmp2 = g2Qpv_tmp2 + g2m( iPrtn1 * (-1), jCmptn, iPrtn2 * (-1));

       g2Qpc( iPrtn1, jCmptn, iPrtn2) = g2Qpc_tmp1;
       g2Qpv( iPrtn1, jCmptn, iPrtn2) = g2Qpv_tmp1;
       g2Qpc( iPrtn1 * (-1), jCmptn, iPrtn2) = g2Qpc_tmp2;          // Here iPrtn2 is the flavor #
       g2Qpv( iPrtn1 * (-1), jCmptn, iPrtn2) = g2Qpv_tmp2;          // It is always positive

                                // Gluon: for each flavor, sum over both quark and anti-quark
       g2Gpc_tmp = g2Gpc_tmp + g2p(  iPrtn1,  jCmptn,   iPrtn2);
       g2Gpv_tmp = g2Gpv_tmp + g2m(  iPrtn1,  jCmptn,   iPrtn2);

       g2Gpc_tmp = g2Gpc_tmp + g2p(  iPrtn1 * (-1),  jCmptn,  iPrtn2 * (-1));
       g2Gpv_tmp = g2Gpv_tmp + g2m(  iPrtn1 * (-1),  jCmptn,  iPrtn2 * (-1));

       g2Gpc( iPrtn1, jCmptn, iPrtn2) = g2Gpc_tmp;
       g2Gpv( iPrtn1, jCmptn, iPrtn2) = g2Gpv_tmp;

     }
   }
 }

 DisSet = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////

////////////////////
// QCD parameters //
////////////////////

////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////
// Electroweak parameters //
////////////////////////////

