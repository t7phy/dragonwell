#include "Calculation/CalcDIS.h"

CalcDIS::CalcDIS()
{

}

void CalcDIS::SfnGm(int iHadn, int iCmptn, int iFlv, double x, double Q, FortranArray1D<double> &Sfn123, FortranArray1D<double> &SfnHel)
{
// ----------------------------------------------------------------------------------
//marco Returns arrays of structure functions Sfn123, SfnHel
// 2018.11.19, 2018.08.10 PMN Introduced iFscale=4 to use the fact. scale with
//             saturation in the NNLO DIS cross section and separate
//             scale for heavy-quark production
// 2018.08.10 PMN Introduced iFscale=4 to use the fact. scale with
//             saturation in the NNLO DIS cross section
// 2008.10.02:
//            ! ZM calculations (mSwtch = 0, 1) re-written.
//            !   mSwtch = 0 should now correspond to the "conventional ZM scheme":
//            !              same active partons, determined by initial state fac. scheme only;
//            !              ignore final-state phase space considerations all together.
//            !          = 1,8 corresponds to a possible version of "improved ZM scheme":
//            !              respects final-state phase-space restrictions, including using Acot-chi;
//            !              select partons according to gluon-fusion final-state, add corresponding
//            !              LO term by appropriate adjustment of scale (to be above the threshold).
// 2006.12.06:
//            ! New input argument iFlv introduced; common block to store heavy flavor S.F.s deleted.
//            ! Logic of the calculation of heavy flavor S.F.s drastically simplified by HLL.
//            ! New option for choice of factorization scale (iFscle=3) for HQ production added.
// 2006.03.13:
//            ! Transformed the HvFlvSf output to general "semi-inclusive" flavor SF's in /SiFlvSf/
// 2006.03.10:
//            ! Expanded to output heavy quark structure functions in common / HvFlvSf /
// 2006.01.24:
//             Expanded to include iCmptn = -1/0 for (w+ -/+ W-)/2
//
//                   ! ===== General Mass Hadron Structure Functions
// 2005.12.29:
//            ! -------This is the main program module to calculation S.F.'s--------!
//
//    Forward Compton Sc.:
//
//         iBsn(1) + iHadn --> iBsn(2) + iHadn  , with iFlv + X (summed) in the intermediate state.
//
//                   iBsn1 ________ __ __iFlv__ __ _____iBsn1
//                                 |\/|        |\/|
//                   iHadn ________|/\|________|/\|_____iHadn
//                                        X
//
//                         iCmptn =   1,     2,     3,     4,        5
//                   for iBsn(1,2)= (1,1), (2,2), (3,3), (4,4), (1,4)+(4,1)
//                                  photon   W+     W-      Z   photon-Z int.
//
//         iFlv : 0   (total inclusive---sum over all active quark-parton flavors);
//               -6:6 (individual flavors);
//               11:16 (quark+antiquark).
//
//                         ! -----------------------------------!
//
//         iOrdr: 0  :   LO : alpha_s^0
//                1  :  NLO : alpha_s^1
//                2  : NNLO : alpha_s^2
//
//         iSchm: 4-digit integer tkmn
//                n : factorization number scheme switch:
//                  0   : VFNS : # of flavors depends on the factorization scale;
//                  1-6 : FFNS : fixed flavor number = n;
//                m : mass-effect switch:  (Cf. ACOT-chi: Kretzer/Schmidt/Tung)
//                  0   : ZM (zero-mass) partons (kinematic limits neglected)
//                  1,8  : ZM - kinematic limits respected (klr.), for two possible
//                   definitions of "unsubtracted" one-loop gluon matrix element
//                   below the heavy-quark production threshold
//                  2   : GM1- klr. + Massive Wilson Coef. up to alphaS^1
//                             + ZM of alphaS^2 if required (SACOT + ACOT-chi)
//                  3   : GM2- klr. + Massive Wilson Coef. up to alphaS^2
//                             (SACOT + ACOT-chi)
//                k : factorization scale switch:
//                  0 : default : factorization scale aMu = Q ;
//                  1 : aMu = (Q**5 + Q0**5)**(1d0/5d0)  ;
//                  2 : aMu = ScalFc * Q    where ScalFc is supplied via Common/cDisCal/
//                  3 : aMu = sqrt (Q^2 + M1^2 + M2^2) for heavy flavor production.
//                  4 : special saturation scale at small x and
//                  independent scale for heavy-quark SIDIS, with
//                  parameters read from CP(2,1), .. CP(5,1)
//                  other options, not yet implemented;
//                t : switch for specific test/debug function: e.g.
//                  0 : default
//                  1 : print out comparison between SfZM05 and MVV-nlo
//                        ! ----------------------------------------- !
//    Outputs F_(1,2,3) as the 3-dim array        Sfn123( 1/2/3),
//    and the helicity SFs F(Left,Long.,Right) as SfnHel(-1/0/1).

 Sfn123.resize(1, 3);
 SfnHel.resize(-1, 1);

 double Smll = 1e-8, sml = 1e-5;
 bool SubAdd;
//     ------------------------------------- Initialization

 if(!DisSet) mSetDis();
                             // tag quark contribution channels (for subtraction purpose)
 for(int i = -6; i <= 6; i++){
   for(int j = -6; j <= 6; j++){
     Qpdf(i, j) = 0;
   }
 }

 if(iCmptn == -1 || iCmptn == 0 || iCmptn == 2 || iCmptn == 3) CC = true; // Charged Current process
 if(iCmptn == 1  || iCmptn == 4 || iCmptn == 5) CC = false;               // Neutral Current process

 iFschm = iSchm % 10;        // flavor # factorization scheme
 mSwtch = iSchm / 10 % 10;   // mass treatment switch
 iFscle = iSchm / 100 % 10;  // factorization scale switch


 int kFv = iFlv / 10;             // kFv = 1 for iFlv 14:16 ; 0 otherwise
 int iFv = iFlv % 10;         // iFv -6:6

// --------- Set factorization scale for inclusive DIS/light-parton channels

 double aMu;

 if(iFscle == 0 || iFscle == 3){
   aMu = Q;
 }
 else if(iFscle == 1){
   aMu = pow((pow(Q, 5.0) + pow(Q0, 5.0)), 0.2); // aMu is bounded below by Q0, for any Q
 }
 else if(iFscle == 2){
   aMu = ScalFc * Q;          // Simple example; could be any function of (x,Q), i.e. Sqrt(Q^2+M_c^2)
 }
 else if(iFscle == 4){        // add a constant saturation scale to slow down evolution in the small-x region
//pn18   CP(4,1) replaces ScalFc as an overall rescaling scale
   if(CP[make_tuple(4,1)] * Q > 1.0){  // pn18 sanity check -- the scale must be larger than 1 GeV
     aMu = CP[make_tuple(4,1)] * pow((pow(Q, 2.0) + CP[make_tuple(2,1)] / pow(x, CP[make_tuple(3,1)])), 0.5);
   }
   else{
     cout<<"CP(4,1) "<<CP[make_tuple(4, 1)]<<"  Q "<<Q<<" CP(4,1)*Q "<<CP[make_tuple(4, 1)] * Q<<endl;
     cout<<"SFnGm.F: amu < 1.0; check CP(4,1)"<<endl;
     return;
   }
 }
 else{
   cout<<"Stop: iFscle = "<<iFscle<<endl;
   cout<<"has not been implemented in SFnGm.f!"<<endl;
 }

// Redefine the fac scale for semi-inclusive HQ prod. Use the MSbar mass
// in the fact. scale for no deep reason
// pn2018      If (iFscle==3 .and. abs(iFv) >= nHeavy) 
//     >  aMu = Sqrt(Q**2 + ScalFc * aMass(1, abs(iFv))**2) 
 if(abs(iFv) >= nHeavy){
   if(iFscle == 3){
     aMu = sqrt(pow(Q, 2.0) + ScalFc * pow(aMass(1, abs(iFv)), 2.0));
   }
//pn18   CP(5,1) replaces ScalFc as an overall rescaling scale for heavy flavors  
   else if(iFscle == 4){
     if(CP[make_tuple(5,1)] * Q > 1.0){// pn18 sanity check -- the scale must be larger than 1 GeV
       aMu = CP[make_tuple(5,1)] * pow((pow(Q, 2.0) + CP[make_tuple(2,1)] / pow(x, CP[make_tuple(3,1)])), 0.5);
     }
     else{
       cout<<"SFnGm.F: amu < 1.0 for heavy flavors; check CP(5,1)"<<endl;
       return;
     }
   }
 }// abs(iFv) >= nHeavy

      // Define number of incoming quark-partons nPrtn1   ---  FFNS and VFNS switch
                                         // This is done with the FFNS label iSchm
 if(iFschm >= 1 && iFschm <= 6){
   nPrtn1 = iFschm;
 }
 else if(iFschm == 0){
   nPrtn1 = GetNfl(aMu);       //  VFNS: number of partons at the scale Q
 }

//      nPrtn2 = NflTot()     number of final state quark-flavors to be summed
//                            (default = 6)
 W = Q * sqrt(1.0/x -1.0);   // Used to determine available final state phase space
                                // Physically, this is really SQRT(W^2-M_N^2)
 ExamineMassThresholds();
 //cout<<"aMu = "<<aMu<<" nPrtn1 = "<<nPrtn1<<" mSwtch = "<<mSwtch<<endl;

                                             // -----------Start calculation
              // Part I : initial state QUARK-parton
 FortranArray1D<double> Q0a{1, 5};
 FortranArray1D<double> Q0b{1, 5};
 FortranArray1D<double> Q1a{1, 5};
 FortranArray1D<double> Q1b{1, 5};
 FortranArray1D<double> Qtem{1, 5};
 FortranArray1D<double> Gtem{1, 5};
 FortranArray1D<double> RG{1, 5};

 FortranArray1D<double> SfT2{1, 3};//(3)
 FortranArray1D<double> SfH2{-1, 1};//(-1:1)
 FortranArray1D<double> SfT0{1, 3};//(3)
 FortranArray1D<double> SfH0{-1, 1};//(-1:1)
 FortranArray1D<double> SfTs{1, 3};//(3)

 FortranArray1D<double> SfTq{1, 3};//(3)
 FortranArray1D<double> SfHq{-1, 1};//(-1:1)
 FortranArray1D<double> SfTg{1, 3};//(3)
 FortranArray1D<double> SfHg{-1, 1};//(-1:1)
 FortranArray1D<double> SfHs{-1, 1};//(-1:1)

 FortranArray1D<double> SfT3{1, 3};//(3)
 FortranArray1D<double> SfH3{-1, 1};//(-1:1)

 double bMu1, bMu2, FLo3, F2o3;

 SfT0.fill(0.0);
 SfH0.fill(0.0);
 SfTq.fill(0.0);
 SfHq.fill(0.0);

 for(int iPrtn1 = -nPrtn1; iPrtn1 <= nPrtn1; iPrtn1++){// Sum over initial state PARTONs only
   if(iPrtn1 == 0) continue;             // skip gluon (done separately later)

   int aPrtn1 = abs(iPrtn1);

                                // Store default ZM (zero-mass) results
   SfZm0Q(iHadn, iPrtn1, x, Q, aMu, Q0b); // ZM default

   if(iOrdr > 0) SfZm1Q(iHadn, iPrtn1, x, Q, aMu, Q1b); // ZM default

   for(int iPrtn2 = -nPrtn2; iPrtn2 <= nPrtn2; iPrtn2++){// Sum over final state FLAVORs (all)
     if(iPrtn2 == 0) continue;    // skip gluon

     if(iFlv != 0){        // semi-inclusive case : skip channels not needed.
       if(kFv == 0 && iPrtn2 != iFv) continue; // iFv is -6:6 in this case
       if(kFv == 1 && abs(iPrtn2) != iFv) continue; // iFv is  4:6 in this case
     }

     if(g2q(0,iPrtn1,iCmptn,iPrtn2) < Smll) continue; // skip uncoupled channels

     Qpdf(iPrtn1, iPrtn2) = 1; // tag channels with the LO quark included
     aPrtn2 = abs(iPrtn2);
     aM1 = aMass(0, aPrtn1);  //use pole masses in all DIS kinematics
     aM2 = aMass(0, aPrtn2);

     if(mSwtch == 1){       // set a special factorization 
                            // scale for some realizations of improved ZM
       bMu1 = (aMu > aM1) ? aMu : aM1;
     }
     else{
       bMu1 = aMu;
     }

                                 // LO  --------------
     Q0a.fill(0.0);// LO quark contribution = 0, unless explicitly computed
  // Treat the naive ZM scheme differently from other schemes: neglect threshold effects, do not
  // distinguish between the summation over initial- and final-state flavors, and use massless 
  // expressions for any x, Q
     if(mSwtch == 0){
       if(abs(iPrtn2) <= nPrtn1) Q0a = Q0b;
     }
     else{
       if(AboveThreshold(aPrtn1,aPrtn2)){// Above production threshold
         int MaxaPrtn = aPrtn1 > aPrtn2 ? aPrtn1 : aPrtn2;
         if(MaxaPrtn < nHeavy){// for both quarks light;
           Q0a = Q0b;  // Use ZM defaults
         }
         else{
           Zeta = fchi(x,Q,aM1,aM2); //X ! Rescaling variable (generalized chi)
           if(CC && (mSwtch == 2 || mSwtch == 3)){// GM scheme
             Acot0Q(iHadn, iPrtn1, 0.0, aM2, Zeta, Q, aMu, Q0a);
           }
           else{                // improved ZM; massless LO with zeta=chi variable
             SfZm0Q(iHadn, iPrtn1, Zeta, Q, bMu1, Q0a);
           }                    // CC
           //cout<<"Q0a = "<<Q0a(1)<<"  "<<Q0a(2)<<"  "<<Q0a(3)<<"  "<<Q0a(4)<<"  "<<Q0a(5)<<endl;
         }
       }
     }
                                    // --------- Assemble irreducible amplitudes,
         // ---- fold in EW coupling to produce contributing term to Structure Functions;
                                              // then, accumulate to Structure Functions

     FortranArray1D<double> g2chi_tem{1, 3};
     g2chi_tem(1) = g2q(1, iPrtn1, iCmptn, iPrtn2);
     g2chi_tem(2) = g2q(2, iPrtn1, iCmptn, iPrtn2);
     g2chi_tem(3) = g2q(3, iPrtn1, iCmptn, iPrtn2);
     //cout<<"g2chi: "<<g2chi_tem(1)<<"  "<<g2chi_tem(2)<<"  "<<g2chi_tem(3)<<endl;
     SFnConv(Q0a, g2chi_tem, SfT2, SfH2);
     for(int isf = 1; isf <= 3; isf++){
       SfT0(isf) = SfT0(isf) + SfT2(isf);
     }
     for(int isf = -1; isf <= 1; isf++){
       //cout<<SfH0(isf)<<"  "<<SfH2(isf)<<endl;
       SfH0(isf) = SfH0(isf) + SfH2(isf);
     }

        // NLO Quark term ---------------
     Q1a.fill(0.0);// NLO quark contribution = 0, unless explicitly computed
     if(iOrdr >= 1){
       if(mSwtch == 0){// Naive ZM; use massless expressions for
                       // active quark flavors regardless of kinematics
         if(abs(iPrtn2) <= nPrtn1) Q1a = Q1b;
       }
       else{
         if(AboveThreshold(aPrtn1, aPrtn2)){
           int MaxaPrtn = aPrtn1 > aPrtn2 ? aPrtn1 : aPrtn2;
           if(MaxaPrtn < nHeavy){// for both quarks light;
             Q1a = Q1b;         // Use ZM defaults
           }
           else{// at least one heavy quark
             Zeta = fchi(x, Q, aM1, aM2); // X ! Rescaling variable (generalized chi)
             //if(fabs(x - 0.21) < 1e-3 && fabs(Q - 3.49571) < 1e-5){
             //   cout<<"else? CC = "<<CC<<" mSwtch "<<mSwtch<<" Zeta = "<<Zeta<<endl;
             //}
             if(CC && (mSwtch == 2 || mSwtch == 3)){// GM scheme
               GotSK1Q(iHadn, iPrtn1, aM2, Zeta, Q, aMu, Q1a);
             }
             else{              // improved ZM; massless quark NLO with zeta=chi variable
               SfZm1Q(iHadn, iPrtn1, Zeta, Q, bMu1, Q1a);
             }                  // CC
           }
         }
       }

       for(int isf = 1; isf <= 5; isf++){

         //if(fabs(x - 0.21) < 1e-3 && fabs(Q - 3.49571) < 1e-5){
         //  cout<<"Q1a: "<<Q1a(isf)<<" aMu = "<<aMu<<" AlphaS = "<<GetAlphaS(aMu)<<endl;
         //}
         Q1a(isf) = Q1a(isf) * GetAlphaS(aMu) / Pi / 2.0; // multiply the alpi here
       }

       FortranArray1D<double> g2chi_o1_tem{1, 3};
       g2chi_o1_tem(1) = g2q(1, iPrtn1, iCmptn, iPrtn2);
       g2chi_o1_tem(2) = g2q(2, iPrtn1, iCmptn, iPrtn2);
       g2chi_o1_tem(3) = g2q(3, iPrtn1, iCmptn, iPrtn2);
       SFnConv(Q1a, g2chi_o1_tem, SfT2, SfH2);
       for(int isf = 1; isf <= 3; isf++){
         SfTq(isf) = SfTq(isf) + SfT2(isf);
       }
       for(int isf = -1; isf <= 1; isf++){
         SfHq(isf) = SfHq(isf) + SfH2(isf);
       }
     }// iOrdr
   }// nPrt2
 }// nPrt1

               // Part II : GLUON initial state  ---------------
 SfTg.fill(0.0);// gluon-fusion terms
 SfHg.fill(0.0);
 SfTs.fill(0.0);// subtraction terms
 SfHs.fill(0.0);

 if(iOrdr >= 1){   // (gluon does not contribute to L0)
                                // NC/CC processes are treated the same way; default
                                // Naive ZM result is independent of quark flavors, store as RG

   SfZm1G(iHadn, x, Q, aMu, RG);
   for(int isf = 1; isf <= 5; isf++){
     RG(isf) = RG(isf) * 2.0;
   }
        // Sum over distinct final state pairs
        // Calculated here is the t- and u-channel diagram contributions to
        //           vector-boson + gluon --> iPrtn1 + iPrtn2-bar
        // (The virtual exchanged quark lines are iPrtn2/iPrtn1-bar respectively.)
   for(int iPrtn1 = 1; iPrtn1 <= nPrtn2; iPrtn1++){   // quark in the final state     :  iPrtn1 // yfu: remind this place, fortran code is nPrtn2
     for(int iPrtn2 = 1; iPrtn2 <= nPrtn2; iPrtn2++){ // anti-quark in the final state: -iPrtn2

       if(iFlv != 0){      // semi-inclusive case : skip channels not needed.
         if(kFv == 0 && iPrtn1 != iFv && -iPrtn2 != iFv) continue;
         if(kFv == 1 && iPrtn1 != iFv && -iPrtn2 !=-iFv) continue;
       }

       if(g2q(0,iPrtn2,iCmptn,iPrtn1) < Smll) continue; // skip uncoupled channels

       aM1 = aMass(0, iPrtn1);  //use pole masses in all DIS kinematics
       aM2 = aMass(0, iPrtn2);

       if(mSwtch == 1){      // set a special factorization scale 
                             //for some realizations of improved ZM
         bMu1 = aMu > aM1 ? aMu : aM1;
         bMu2 = aMu > aM2 ? aMu : aM2;
       }
       else{
         bMu1 = aMu;
         bMu2 = aMu;
       }

       Q0a.fill(0.0);// (Use arrays Q0a, Q0b, Q1a,Q1b to store  )
       Q0b.fill(0.0);
       Q1a.fill(0.0);// (subtraction terms, if needed.)
       Q1b.fill(0.0);
       Gtem.fill(0.0);// NLO gluon and subtraction = 0, unless explicitly computed
       Qtem.fill(0.0);

       SubAdd = false;           // tag subtraction calculation (for gluon fusion processes)

       if(mSwtch == 0){// If naive ZM, use massless NLO expressions for 
                       // diagrams with active quarks regardless of kinematics
         if(iPrtn1 <= nPrtn1 && iPrtn2 <= nPrtn1) Gtem = RG;
       }
       else{           // implement threshold considerations
         if(AboveThreshold(iPrtn1,iPrtn2)){
           if(mSwtch == 1 || mSwtch == 8){ // improved ZM: honor kinematic limits (ACOT-chi)
                                           // Evaluate the ZM gluon contribution (with the g->q qbar collinear
                                           // term subtracted)
             int MaxiPrtn = iPrtn1 > iPrtn2 ? iPrtn1 : iPrtn2;
             if(MaxiPrtn < nHeavy){// For light flavors
               Gtem = RG;
             }
             else{
               Zeta = fchi(x,Q,aM1,aM2); //X !fchi(x,Q,am1,am2) // Rescaling variable (generalized chi)
               SfZm1G(iHadn, Zeta, Q, bMu1, Q0a);
               SfZm1G(iHadn, Zeta, Q, bMu2, Q0b);
               Gtem = Q0a;
               for(int isf = 1; isf <= 5; isf++){
                 Gtem(isf) = Gtem(isf) + Q0b(isf);
               }
                               //Restore the subtracted g->q qbar collinear term when the corresponding
                               //LO quark contribution does not exist (e.g., if mu < below the switching point mu_0
                               //for the incoming PDF flavor)

               if(!Qpdf(-iPrtn1,-iPrtn2)){
                 SubAdd = true;
                 if(mSwtch == 1){
                   SfZm0Q(iHadn,-iPrtn1,Zeta, Q, bMu1, Q1a);
                 }
                 else if(mSwtch == 8){
                   AcotSub(iHadn,-iPrtn1, aM1, 0.0, Zeta, Q, bMu1, Q1a);
                 }
                 Q1a(5) = -Q1a(5);
               }             // .not.Qpdf(-iPrtn1,-iprtn2)

               if(!Qpdf(iPrtn2,iPrtn1)){
                 SubAdd = true;
                 if(mSwtch == 1){
                   SfZm0Q(iHadn, iPrtn2, Zeta, Q, bMu2, Q1b);
                 }
                 else if(mSwtch == 8){
                   AcotSub(iHadn, iPrtn2, aM2, 0.0, Zeta, Q, bMu2, Q1b);
                 }
               }             // .not.Qpdf(iPrtn2,iprtn1)
               Qtem = Q1a;
               for(int isf = 1; isf <= 5; isf++){ // -sign to ADD rather than SUBTRACT
                 Qtem(isf) = Qtem(isf) * (-1.0) - Q1b(isf);
               }

             }// Heavy21
           }
           else if(mSwtch == 2 || mSwtch == 3){ // general-mass scheme
             int MaxiPrtn = iPrtn1 > iPrtn2 ? iPrtn1 : iPrtn2;
             if(MaxiPrtn < nHeavy){// For light flavors
               Gtem = RG;         // Use default (ZM) Wilson coef.                 
             }
             else{                // Include full mass effects in Wilson Coefficient
                                  // if either final quark is heavy
               Acot1G(iHadn, aM1, aM2, x, Q, aMu, Gtem);
                                  // Need mass subtraction to avoid double-counting if line-
                                  // reversed quark (-iPrtn1) is an initial-state parton
                                  // Quark contribution exists if Qpdf(-iPrtn1,-iprtn2)=.true.
               Zeta = fchi(x,Q,aM1,aM2);// !X !fchi(x,Q,am1,am2) ! Rescaling variable (generalized chi)
               if(iPrtn1 <= nPrtn1 && Qpdf(-iPrtn1,-iPrtn2)){
                 SubAdd = true;
                 if(!CC){         // Neutral Current case:
                   AcotSub(iHadn, -iPrtn1, aM1, 0.0, Zeta,Q,aMu,Q1a);  // Set mass=0, except for the log (m/mu) factor
//cout<<"Q1a = "<<Q1a(1)<<"  "<<Q1a(2)<<"  "<<Q1a(3)<<"  "<<Q1a(4)<<"  "<<Q1a(5)<<endl;
                 }
                 else{            // Charge Current case
                   AcotSub(iHadn, -iPrtn1, aM1, aM2, Zeta,Q,aMu,Q1a);  // Keep final-state mass to match LO term.
                 }                // iPrtn1 <= nPrtn1
                                  // in order to use the EW coupling below, need to reverse the
                                  // sign of the parity violating term for anti-quark -iPrtn1;
                                  // (CP symmetry ==> R<-->L)
                 Q1a(5) = -Q1a(5);
               }
                                // Likewise for the other (crossed) diagram
                                //  which corresponds to initial state parton iPrtn2
                                // Quark contribution exists if Qpdf(iPrtn2, iprtn1)=.true.
               if(iPrtn2 <= nPrtn1 && Qpdf(iPrtn2, iPrtn1)){
                 SubAdd = true;
                 if(!CC){        // Neutral Current case:
                   AcotSub(iHadn, iPrtn2, aM2, 0.0, Zeta, Q, aMu, Q1b);
//cout<<"Q1b = "<<Q1b(1)<<"  "<<Q1b(2)<<"  "<<Q1b(3)<<"  "<<Q1b(4)<<"  "<<Q1b(5)<<endl;
                 }
                 else{           // Charge Current case
                   AcotSub(iHadn, iPrtn2, aM2, aM1, Zeta, Q, aMu, Q1b);  // Keep final-state mass to match LO term.
                 }
               }                 //iPrtn2 <= nPrtn1
               Qtem = Q1a;
               for(int isf = 1; isf <= 5; isf++){ // Keep subtraction term in parallel with Gtem
                 Qtem(isf) = Qtem(isf) + Q1b(isf);
               }
             }// Heavy22
           }
         } // AboveThreshold 2
       }// NaiveZM2

                               // Accumulate gluon fusion term (always)
       for(int isf = 1; isf <= 5; isf++){
         Gtem(isf) = Gtem(isf) * GetAlphaS(aMu) / Pi / 2.0; // multiply the alpi here
       }

       FortranArray1D<double> g2chi_g1_tem{1, 3};
       g2chi_g1_tem(1) = g2q(1, iPrtn2, iCmptn, iPrtn1);
       g2chi_g1_tem(2) = g2q(2, iPrtn2, iCmptn, iPrtn1);
       g2chi_g1_tem(3) = g2q(3, iPrtn2, iCmptn, iPrtn1);
       //cout<<"g2q = "<<g2q(1, iPrtn2, iCmptn, iPrtn1)<<"  "<<g2q(2, iPrtn2, iCmptn, iPrtn1)<<"  "<<g2q(3, iPrtn2, iCmptn, iPrtn1)<<endl;
       SFnConv(Gtem, g2chi_g1_tem, SfT2, SfH2);
       for(int isf = 1; isf <= 3; isf++){
         SfTg(isf) = SfTg(isf) + SfT2(isf);
       }
       for(int isf = -1; isf <= 1; isf++){
         SfHg(isf) = SfHg(isf) + SfH2(isf);
       }
             // Accumulate subtraction term (when applicable)
       if(SubAdd){
         for(int isf = 1; isf <= 5; isf++){
           Qtem(isf) = Qtem(isf) * GetAlphaS(aMu) / Pi / 2.0; // multiply the alpi here
         }

         FortranArray1D<double> g2chi_g2_tem{1, 3};
         g2chi_g2_tem(1) = g2q(1, iPrtn2, iCmptn, iPrtn1);
         g2chi_g2_tem(2) = g2q(2, iPrtn2, iCmptn, iPrtn1);
         g2chi_g2_tem(3) = g2q(3, iPrtn2, iCmptn, iPrtn1);
         SFnConv(Qtem, g2chi_g2_tem, SfT2, SfH2);
         for(int isf = 1; isf <= 3; isf++){
           SfTs(isf) = SfTs(isf) + SfT2(isf);
         }
         for(int isf = -1; isf <= 1; isf++){
           SfHs(isf) = SfHs(isf) + SfH2(isf);
         }
         SubAdd = false;
       }
     }// PartG2
   }// PartG1
 }// Gluon

                                // NNLO calculation
 SfT3.fill(0.0);
 SfH3.fill(0.0);
 FLo3 = 0.0; F2o3 = 0.0;
 if(iOrdr > 1 && iCmptn == 1){  //start NNLO, neutral-current DIS
                                            // only
   for(int iPrtn2 = 1; iPrtn2 <= nPrtn2; iPrtn2++){
     if(iFlv != 0){    //for the semi-inclusive case
       if(iPrtn2 != abs(iFv)) continue; // skip channels not needed
       if(kFv != 1){    // only semi-inclusive q+qbar is implemented 
         cout<<"STOP: NNLO semi-incl. F2 is defined only for kFv=10"<<endl;
         cout<<"kFv "<<kFv<<endl;
         return;
       }
     } // iFlv != 0

// Skip uncoupled channels or contributions below the mass threshold
     aM1 = aMass(0, iPrtn2); // use pole masses in all DIS kinematics
     aM2 = aMass(0, iPrtn2);

     if(g2q(0,iPrtn2,iCmptn,iPrtn2) < Smll || !AboveThreshold(iPrtn2,iPrtn2)) continue;

     double F2tmp3 = 0.0;
     double FLtmp3 = 0.0;

     Fnxlo(iHadn, x, Q, aMu, iPrtn2, F2tmp3, FLtmp3);

     double e2 = (g2q(1, iPrtn2, iCmptn, iPrtn2) + g2q(2, iPrtn2, iCmptn, iPrtn2)) / 2.0;
     F2tmp3 = e2 * F2tmp3;
     FLtmp3 = e2 * FLtmp3;
     //cout<<"e2 = "<<iPrtn2<<"  "<<e2<<endl;

//  For the semi-inclusive structure function, add the real non-singlet 
//  contribution from quarks other than the tagged quark flavor.
//  This non-singlet piece contributes with the same factor both 
//  for abs(iFlv)=1...6 and ifLv=11...16

     if(iFlv != 0 && SemiInclusiveF2c){
       for(int iPrtn3 = 1; iPrtn3 <= nPrtn1; iPrtn3++){
         if(iPrtn3 == iPrtn2) continue;

         double e2 = (g2q(1, iPrtn3, iCmptn, iPrtn3) + g2q(2, iPrtn3, iCmptn, iPrtn3)) / 2.0;


         F2tmp3 = F2tmp3 + e2 * SiF2l(x, Q, aMu, aM1, iHadn, iPrtn3);
         FLtmp3 = FLtmp3 + e2 * SiFLl(x, Q, aMu, aM1, iHadn, iPrtn3);
       }
     }

     F2o3 = F2o3 + F2tmp3; FLo3 = FLo3 + FLtmp3;

   }// Part NNLO

   F2LConvNC(F2o3, FLo3, SfT3, SfH3);
 }// High Order

 //cout<<"F2o3 = "<<F2o3<<" FLo3 = "<<FLo3<<endl;

                            // Return cumulative structure functions
 Sfn123 = SfT0;
 SfnHel = SfH0;

 for(int isf = 1; isf <= 3; isf++){
   Sfn123(isf) = Sfn123(isf) + SfTq(isf) + SfTg(isf) - SfTs(isf) + SfT3(isf);
 }
 for(int isf = -1; isf <= 1; isf++){
   //if(fabs(x - 0.21) < 1e-3 && fabs(Q - 3.49571) < 1e-5){
   //  cout<<fixed<<setprecision(6)<<isf<<"  "<<SfnHel(isf)<<"  "<<SfHq(isf)<<"  "<<SfHg(isf)<<"  "<<SfHs(isf)<<"  "<<SfH3(isf)<<endl;
   //}
   //cout<<fixed<<setprecision(16)<<isf<<"  "<<SfnHel(isf)<<"  "<<SfHq(isf)<<"  "<<SfHg(isf)<<"  "<<SfHs(isf)<<"  "<<SfH3(isf)<<endl;
   SfnHel(isf) = SfnHel(isf) + SfHq(isf) + SfHg(isf) - SfHs(isf) + SfH3(isf);
 }
 //cout<<SfnHel(-1)<<"  "<<SfnHel(0)<<"  "<<SfnHel(1)<<endl;
// Sfn123 = (SfT0 + SfTq + SfTg - SfTs) + SfT3
// SfnHel = (SfH0 + SfHq + SfHg - SfHs) + SfH3

}

void CalcDIS::Fnxlo(int iHadn, double x, double Q, double aMu, int iPrtn, double &F2out, double &FLout)
{
// Pavel's fix (11/16/2012) to previous bug.
 double cNS = 0.0, cPS = 0.0, cG = 0.0, cLNS = 0.0, cLPS = 0.0, cLG = 0.0;
 double aM, Zeta;

 if(Fnxlo_xold != x || Fnxlo_Qold != Q || Fnxlo_amuold != aMu || Fnxlo_iHadnOld != iHadn){
//pn11   Recycle ZM singlet contributions, all from ZmNNLO.f
   F2ZMPSsave = F2ZMPS2(x,Q,aMu,iHadn);
   F2ZMGsave  = F2ZMG2(x,Q,aMu,iHadn);
   FLZMPSsave = FLZMPS2(x,Q,aMu,iHadn);
   FLZMGsave  = FLZMG2(x,Q,aMu,iHadn);
   Fnxlo_xold = x;
   Fnxlo_Qold = Q;
   Fnxlo_amuold = aMu;
   Fnxlo_iHadnOld = iHadn;
 }                     //iFlv xold

 double Subtraction = 0.0;
 double SubtractionL = 0.0;

// choose the mass scheme
 if(mSwtch == 3){// GM scheme
   if(iPrtn < nHeavy){// coefficient functions for F_l
     cLNS = FLZMNS2(x,Q,aMu,iHadn,iPrtn,nHeavy-1); //fLNS_{l,l,light} with Nf=Nlight
     cNS = F2ZMNS2(x,Q,aMu,iHadn,iPrtn,nHeavy-1);  //fNS_{l,l,light} with
                                                   // Nf=Nlight, in GmJS.f
     for(int iPrtn3 = nHeavy; iPrtn3 <= NFAboveThr; iPrtn3++){// Contributions of heavy states
       if(!AboveThreshold(iPrtn3, iPrtn3)) continue; //pn11: precaution, if quark masses
                                                                //are not arranged in the ascending order
       aM = aMass(0, iPrtn3); //use pole masses in all DIS kinematics
       Zeta = fchi(x,Q,aM,aM);
       //cout<<fixed<<setprecision(16)<<"cNS = "<<cNS<<"  "<<F2LNS2(x,Q,aMu,aM,iHadn,iPrtn)<<"  "<<F2lNSSub(x,Q,aMu,aM,iHadn,iPrtn)<<endl;

       cNS = cNS + F2LNS2(x,Q,aMu,aM,iHadn,iPrtn)     // in GmJS.f, Eq. (25)
                 - F2lNSSub(x,Q,aMu,aM,iHadn,iPrtn);  // conv. of A2NSll_heavy,in GmJS.f, GmJSa.f;
                                //F2lNSsub pn must take X as the input (rescaling done inside)!

       cLNS = cLNS + FLLNS2(x,Q,aMu,aM,iHadn,iPrtn);  // in GmJS.f, Eq. (25)
                                                      // no subtraction c^(0)_L=0
     }// iPrtn3

     cPS = F2ZMPSsave;
     cG  = F2ZMGsave;
     cLPS = FLZMPSsave;
     cLG  = FLZMGsave;
   }
   else{// coefficient functions for F_h
     cPS = F2hlPS2(x,Q,aMu,aM2,iHadn); //in GmJS.f
     cG  = F2hg2  (x,Q,aMu,aM2,iHadn); //in GmJS.f

     cLPS = FLhlPS2(x,Q,aMu,aM2,iHadn); //in GmJS.f
     cLG  = FLhg2  (x,Q,aMu,aM2,iHadn); //in GmJS.f

     if(iPrtn <= nPrtn1){
       Zeta = fchi(x,Q,aM1,aM1); //X ! Rescaling variable (generalized chi)   
       cNS = F2ZMNS2(Zeta,Q,aMu, iHadn,iPrtn,NFAboveThr);
       cLNS = FLZMNS2(Zeta,Q,aMu,iHadn,iPrtn,NFAboveThr);
     } //iprtn <= Nprtn1

     //cout<<"Qpdf: "<<Qpdf(iPrtn, iPrtn)<<endl;
     if(Qpdf(iPrtn, iPrtn)){  // subtraction
                               // Zeta defined inside F2HQsub2
       Subtraction = F2HQSub2(x,Q,aMu,aM2,iHadn);
       SubtractionL = FLHQSub2(x,Q,aMu,aM2,iHadn);
     }
   }
 }
 else if(mSwtch == 0){// ZM scheme
   cPS = F2ZMPSsave;
   cG  = F2ZMGsave;
   cLPS = FLZMPSsave;
   cLG  = FLZMGsave;

   if(iPrtn <= nPrtn1){
     cNS = F2ZMNS2(x,Q,aMu,iHadn,iPrtn, NFAboveThr);
     cLNS = FLZMNS2(x,Q,aMu,iHadn,iPrtn,NFAboveThr);
   } // iprtn <= Nprtn1
 }
 else if(mSwtch == 1 || mSwtch == 2 || mSwtch == 8){// Improved ZM scheme
   if(iPrtn < nHeavy){// coefficient functions for F_l
     cNS = F2ZMNS2(x,Q,aMu,iHadn,iPrtn,nHeavy-1); //fNS_{l,l,light} with
     cLNS= FLZMNS2(x,Q,aMu,iHadn,iPrtn,nHeavy-1); // Nf=Nlight, now in GmJS.f

     for(int iPrtn3 = nHeavy; iPrtn3 <= nPrtn1; iPrtn3++){// Contributions of heavy states
       if(!AboveThreshold(iPrtn3,iPrtn3)) continue;
         aM = aMass(0, iPrtn3); //use pole masses in all DIS kinematics
         Zeta = fchi(x,Q,aM,aM);
         cNS = cNS + F2ZMNS2(Zeta,Q,aMu,iHadn,iPrtn,1);
         cLNS = cLNS + FLZMNS2(Zeta,Q,aMu,iHadn,iPrtn,1);
     }// iPrtn3

     cPS = F2ZMPSsave;
     cG  = F2ZMGsave;
     cLPS = FLZMPSsave;
     cLG  = FLZMGsave;
   }
   else{// coefficient functions for F_h
     Zeta = fchi(x,Q,aM1,aM1); //X ! Rescaling variable (generalized chi)

     cPS = F2ZMPS2(Zeta,Q,aMu,iHadn);
     cG  = F2ZMG2 (Zeta,Q,aMu,iHadn);
     cLPS = FLZMPS2(Zeta,Q,aMu,iHadn);
     cLG  = FLZMG2 (Zeta,Q,aMu,iHadn);

     if(iPrtn <= nPrtn1){
       cNS = F2ZMNS2(Zeta,Q,aMu,iHadn,iPrtn,nPrtn1);  //Nf=Nprtn1, now in GmJS.f
       cLNS = FLZMNS2(Zeta,Q,aMu,iHadn,iPrtn,nPrtn1); //Nf=Nprtn1, now in GmJS.f
     }// iprtn <= nPrtn1
   }
 }

 F2out = cNS + cPS + cG - Subtraction;
 FLout = cLNS + cLPS + cLG - SubtractionL;
 //cout<<"fnxlo iprtn = "<<iPrtn<<endl;
 //cout<<cNS<<"  "<<cPS<<"  "<<cG<<"  "<<Subtraction<<endl;
 //cout<<cLNS<<"  "<<cLPS<<"  "<<cLG<<"  "<<SubtractionL<<endl;

}

void CalcDIS::ExamineMassThresholds()
{
//pn11 1. Sets AboveThreshold(ip21,ip22)=.TRUE. for each pair of quark flavors
//   ip1 and ip2 that can be kinematically produced at the given energy W, 
//   i.e., W > aM(ip21) + aM(ip22). Computes the total number NFAboveThr
//   of quark-antiquark pairs (with the same flavor) that can be
//   physically produced from gluon splittings at this energy (needed for
//   the non-singlet NNLO contribution)

 NFAboveThr = 0;
 for(int ip21 = 1; ip21 <= nPrtn2; ip21++){
   for(int ip22 = 1; ip22 <= nPrtn2; ip22++){
     AboveThreshold(ip21, ip22) = (W > (aMass(0, ip21) + aMass(0, ip22)));
   }//ip22
   if(AboveThreshold(ip21, ip21)) NFAboveThr = NFAboveThr + 1;
 }//ip21

}

double CalcDIS::fchi(double x, double Q, double am1, double am2)
{
// For given x, Q, particle masses aM1 and M2, and shape parameter achi
// returns the rescaled light-cone variable chi. This function must be
// called only above the heavy-quark threshold
//
// Valid ranges of achi    Returned value 
// 0.0 :                   Original rescaling variable chi
// 0.0:1.0:       Generalized rescaling variable zeta(lambda) from 
//                arXiv:0903.2667 by Nadolsky and Tung
// 100:            zeta=x
// Other values:   abort with an error message 

 double sml = 1e-8, rerr = 1e-10;

 double Value = 0.0;

 cchi_akappa = pow((am1 + am2), 2.0) / pow(Q, 2.0);

 double chi0 = x * (1.0 + cchi_akappa);         //chi variable from hep-ph/0110247
                                                //by Tung, Kretzer, Schmidt

 if(chi0 >= 1.0){
   cout<<"STOP in fchi: chi0 > 1"<<endl;
   return 0.0;
 }

 cchi_ax = x;
 cchi_achi1 = achi;

 if(fabs(cchi_achi1) <= sml){
   Value = chi0;
   return Value;
 }
 else if(fabs(achi - 100.0) < sml){
   Value = x;
   return Value;
 }
 else if(cchi_achi1 > 0.0 && cchi_achi1 < 1.0){
//pn2009 Sanity check: the relation between chi and x is one-to-one for
//      chi<1 only if achi < 1 + 1/akappa
   if(achi >= (1.0 + 1.0 / cchi_akappa)){
     cout<<"STOP in fchi: x is not a single-value function"<<endl;
     cout<<" of chi in the region chi<1"<<endl;
     cout<<"achi, akappa = "<<achi<<"  "<<cchi_akappa<<endl;
     return 0.0;
   }
   double eps = x * rerr;

   zetadiff = [&](double zeta){
     return zeta - cchi_ax * (1.0 + cchi_akappa * pow(zeta, cchi_achi1));
   };

   int irt = 0;
   double xtmp = zbrnt(zetadiff, x, chi0, eps, irt);
   if(irt != 0){
     cout<<"Error in fchi: irt = "<<irt<<endl;
     cout<<"or x, Q, aM1, aM2 = "<<x<<"  "<<Q<<"  "<<am1<<"  "<<am2<<endl;
     return 0.0;
   }
   Value = xtmp;
 }

 return Value;
}

