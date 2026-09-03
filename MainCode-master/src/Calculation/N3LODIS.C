#include "Calculation/CalcDIS.h"

void CalcDIS::InitializeHoppetSF()
{
#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)

 int ihadron = 1;

 double mc = Amhat(4); 
 double mb = Amhat(5);
 double mt = Amhat(6);
  
 double Qmax   = 1e5;
 double Qmin   = 1.29;
 int order      = -6; 
 double dy      = 0.2;
 double dlnlnQ  = dy/4.0;
 int    nloop   = EvolveOrder;
 double xmuR   = 1.0;
 double xmuF   = 1.0;
 double minQval = min(xmuF*Qmin, Qmin);
 double maxQval = max(xmuF*Qmax, Qmax);
 double xmin = 1e-9;
 double ymax = log(1.0 / xmin) + 5.0;
 int factscheme = 1;

 hoppetSetDefaultConvolutionEps(1e-7);

 hoppetStartExtended(ymax, dy, minQval, maxQval, dlnlnQ, nloop, order, factscheme);
 hoppetSetPoleMassVFN(mc, mb, mt);

 int nflav = -5;
 int order_max = 4;
 int sc_choice = hoppet::scale_choice_Q;
 double zmass = 91.1876;
 double wmass = 80.377;
 bool param_coefs = true;

 hoppetStartStrFctExtended(order_max, nflav, sc_choice, zmass, param_coefs, wmass, zmass);
    
 double Q0 = 1.295;
 double AsQ0 = 0.118;
 double Q0_as = 91.19;
 double muR_Q    = 1.0;

 auto empty_pdf = [](const double &x, const double &Q, double *pdf){
   for(int i = -6; i <= 6; i++){
     pdf[i + 6] = 0.0;
   }
 };
 hoppetEvolve(AsQ0, Q0_as, nloop, muR_Q, empty_pdf, Q0);

 //hoppetInitStrFct(order_max, param_coefs, xmuR, xmuF);
 //hoppetSetDefaultConvolutionEps(1e-7);

 if(!isDefineFunctions_SFHQ) DefineFunctions_SFHQ();
 cout<<LOG_INFO<<"Initialize SFHQ Done."<<endl;

 if(!isDefineFunctions_OME) DefineFunctions_OME();
 cout<<LOG_INFO<<"Initialize OME Done."<<endl;

 if(!isDefineFunctions_HoppetSF) DefineFunctions_HoppetSF();

 cout<<LOG_INFO<<"Initialize Hoppet Done."<<endl;
 isInitializeHoppetSF = true;

/*
 Hoppet_C2LO = hoppet_get_C2LO_clone();
 Hoppet_CLLO = hoppet_get_CLLO_clone();
 Hoppet_C3LO = hoppet_get_C3LO_clone();

 Hoppet_C2NLO = split_mat_clone(hoppet_get_C2NLO_clone());
 Hoppet_CLNLO = split_mat_clone(hoppet_get_CLNLO_clone());
 Hoppet_C3NLO = split_mat_clone(hoppet_get_C3NLO_clone());

 Hoppet_C2NNLO = split_mat_clone(hoppet_get_C2NNLO_clone());
 Hoppet_CLNNLO = split_mat_clone(hoppet_get_CLNNLO_clone());
 Hoppet_C3NNLO = split_mat_clone(hoppet_get_C3NNLO_clone());

 Hoppet_C2N3LO = split_mat_clone(hoppet_get_C2N3LO_clone());
 Hoppet_CLN3LO = split_mat_clone(hoppet_get_CLN3LO_clone());
 Hoppet_C3N3LO = split_mat_clone(hoppet_get_C3N3LO_clone());

 Hoppet_C2N3LO_fl11 = split_mat_clone(hoppet_get_C2N3LO_fl11_clone());
 Hoppet_CLN3LO_fl11 = split_mat_clone(hoppet_get_CLN3LO_fl11_clone());

 Hoppet_P_LO = split_mat_clone(hoppet_get_P_LO_clone());
 Hoppet_P_NLO = split_mat_clone(hoppet_get_P_NLO_clone());

 if(nloop > 2){
   Hoppet_P_NNLO = split_mat_clone(hoppet_get_P_NNLO_clone());
 }

 if(nloop > 3){
   Hoppet_P_N3LO = split_mat_clone(hoppet_get_P_N3LO_clone());
 }

 Hoppet_grid = hoppet::grid_def(hoppet_cxx__grid_def__copy(Hoppet_C2NLO.grid().ptr()));

 Hoppet_xpdf = hoppet::grid_quant_2d(Hoppet_grid, 14);

 FillHoppetPDFTable(ihadron, 100.0);

 hoppet::grid_quant_2d f2NLO = Hoppet_C2NLO.ptr() * Hoppet_xpdf;
 hoppet::grid_quant_2d f2NNLO = Hoppet_C2NNLO.ptr() * Hoppet_xpdf;

 cout<<"u - ubar: "<<0.1 * (GetPDFP(1, 0.1, 100.0) - GetPDFP(-1, 0.1, 100.0))<<endl;
 cout<<"d - dbar: "<<0.1 * (GetPDFP(2, 0.1, 100.0) - GetPDFP(-2, 0.1, 100.0))<<endl;

 double f2NLO_EM = ((f2NLO[-6 + 6].at_x(0.1) + f2NLO[-4 + 6].at_x(0.1) + f2NLO[-2 + 6].at_x(0.1) + f2NLO[6 + 6].at_x(0.1) + f2NLO[4 + 6].at_x(0.1) + f2NLO[2 + 6].at_x(0.1)) * 4.0 / 9.0
                  + (f2NLO[-5 + 6].at_x(0.1) + f2NLO[-3 + 6].at_x(0.1) + f2NLO[-1 + 6].at_x(0.1) + f2NLO[5 + 6].at_x(0.1) + f2NLO[3 + 6].at_x(0.1) + f2NLO[1 + 6].at_x(0.1)) * 1.0 / 9.0)
                  * GetAlphaS(100.0) / 2.0 / TMath::Pi();

 double f2NNLO_EM = ((f2NNLO[-6 + 6].at_x(0.1) + f2NNLO[-4 + 6].at_x(0.1) + f2NNLO[-2 + 6].at_x(0.1) + f2NNLO[6 + 6].at_x(0.1) + f2NNLO[4 + 6].at_x(0.1) + f2NNLO[2 + 6].at_x(0.1)) * 4.0 / 9.0
                   + (f2NNLO[-5 + 6].at_x(0.1) + f2NNLO[-3 + 6].at_x(0.1) + f2NNLO[-1 + 6].at_x(0.1) + f2NNLO[5 + 6].at_x(0.1) + f2NNLO[3 + 6].at_x(0.1) + f2NNLO[1 + 6].at_x(0.1)) * 1.0 / 9.0)
                   * pow(GetAlphaS(100.0) / 2.0 / TMath::Pi(), 2);

 cout<<"f2 NLO EM = "<<f2NLO_EM<<endl;
 cout<<"f2 NNLO EM = "<<f2NNLO_EM<<endl;

 if(!isDefineFunctions_SFHQ) DefineFunctions_SFHQ();

 if(!isDefineFunctions_OME) DefineFunctions_OME();

 if(!isDefineFunctions_HoppetSF) DefineFunctions_HoppetSF();

 SetQQMuMQ(100.0, 100.0, 1.3, GetNfl(100.0), GetAlphaS(100.0) / 2.0 / Pi);

 isInitializeHoppetSF = true;
*/
/* xC2Hg0 = hoppet::grid_conv(Hoppet_grid, sf_C2Hg0);
 xCLHg0 = hoppet::grid_conv(Hoppet_grid, sf_CLHg0);
 xC2Hg = hoppet::grid_conv(Hoppet_grid, sf_C2Hg);
 xCLHg = hoppet::grid_conv(Hoppet_grid, sf_CLHg);
 xC2Hq = hoppet::grid_conv(Hoppet_grid, sf_C2Hq);
 xCLHq = hoppet::grid_conv(Hoppet_grid, sf_CLHq);

 xPqg    = hoppet::grid_conv(Hoppet_grid, sf_Pqg);
 xA1Hg   = hoppet::grid_conv(Hoppet_grid, sf_A1Hg);
 xA2HgL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL0);
 xA2HgL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL1);
 xA2HgL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL2);
 xA2HqL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL0);
 xA2HqL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL1);
 xA2HqL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL2);

 xA2Hg_vogt = hoppet::grid_conv(Hoppet_grid, sf_A2PShg_vogt);
 xA2Hg_hpt  = hoppet::grid_conv(Hoppet_grid, sf_A2PShg);
 xA2Hq_hpt  = hoppet::grid_conv(Hoppet_grid, sf_A2PShq);
 xA2Hg_CTEQ = hoppet::grid_conv(Hoppet_grid, sf_A2Hg_CTEQ);
 xA2Hq_CTEQ = hoppet::grid_conv(Hoppet_grid, sf_A2HqPS_CTEQ);
*/
#endif
}

void CalcDIS::SfnGm_N3LO(int iHadn, int iCmptn, int iFlv, double x, double Q, FortranArray1D<double> &Sfn123, FortranArray1D<double> &SfnHel)
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

 SfT3.fill(0.0);
 SfH3.fill(0.0);
 FLo3 = 0.0; F2o3 = 0.0;

 FortranArray1D<double> Qire{1, 5};
 Qire.fill(0.0);
 SfT2.fill(0.0);
 SfH2.fill(0.0);

 Sfn123 = SfT2;
 SfnHel = SfH2;

 Gtem.fill(0.0);

 //cout<<endl<<endl;
 //cout<<"Start loop: iHadn = "<<iHadn<<" iCmptn = "<<iCmptn<<"  iFlv = "<<iFlv<<"  x = "<<x<<" Q = "<<Q<<endl;
 for(int iPrtn1 = -nPrtn1; iPrtn1 <= nPrtn1; ++iPrtn1){
   //cout<<"Initial state parton: "<<iPrtn1<<endl;

   if(iPrtn1 == 0) continue;

   double F2LO = 0.0, F2NLO = 0.0, F2NNLO = 0.0, F2N3LO = 0.0;
   double FLLO = 0.0, FLNLO = 0.0, FLNNLO = 0.0, FLN3LO = 0.0;
   double F3LO = 0.0, F3NLO = 0.0, F3NNLO = 0.0, F3N3LO = 0.0;

   F2LO = GetHoppetF2LO(iHadn, iPrtn1, x, Q);
   FLLO = GetHoppetFLLO(iHadn, iPrtn1, x, Q);
   F3LO = GetHoppetF3LO(iHadn, iPrtn1, x, Q);

/*   if(iOrdr >= 1){
     F2NLO = GetHoppetF2NLO(iHadn, iPrtn1, x, Q);
     FLNLO = GetHoppetFLNLO(iHadn, iPrtn1, x, Q);
     F3NLO = GetHoppetF3NLO(iHadn, iPrtn1, x, Q);
   }

   if(iOrdr >= 2){
     F2NNLO = GetHoppetF2NNLO(iHadn, iPrtn1, x, Q);
     FLNNLO = GetHoppetFLNNLO(iHadn, iPrtn1, x, Q);
     F3NNLO = GetHoppetF3NNLO(iHadn, iPrtn1, x, Q);
   }

   if(iOrdr >= 3){
     F2N3LO = GetHoppetF2N3LO(iHadn, iPrtn1, x, Q);
     FLN3LO = GetHoppetFLN3LO(iHadn, iPrtn1, x, Q);
     F3N3LO = GetHoppetF3N3LO(iHadn, iPrtn1, x, Q);
   }
*/
   double F2 = F2LO + F2NLO + F2NNLO + F2N3LO;
   double FL = FLLO + FLNLO + FLNNLO + FLN3LO;
   double F3 = F3LO + F3NLO + F3NNLO + F3N3LO;

   double F2_over_x = F2 / x;
   double TransPC = 0.5 * (F2 - FL) / x;
   double TransPV = 0.5 * F3 / x;

   for(int iPrtn2 = -nPrtn2; iPrtn2 <= nPrtn2; ++iPrtn2){
     //cout<<"Final state parton: "<<iPrtn2<<endl;
     //cout<<"iCmptn = "<<iCmptn<<" iPrtn1 = "<<iPrtn1<<" iPrtn2 = "<<iPrtn2<<" g2q(0) = "<<g2q(0, iPrtn1, iCmptn, iPrtn2)<<endl;
     //cout<<"iCmptn = "<<iCmptn<<" iPrtn1 = "<<iPrtn1<<" iPrtn2 = "<<iPrtn2<<" g2q(1) = "<<g2q(1, iPrtn1, iCmptn, iPrtn2)<<endl;
     //cout<<"iCmptn = "<<iCmptn<<" iPrtn1 = "<<iPrtn1<<" iPrtn2 = "<<iPrtn2<<" g2q(2) = "<<g2q(2, iPrtn1, iCmptn, iPrtn2)<<endl;
     //cout<<"iCmptn = "<<iCmptn<<" iPrtn1 = "<<iPrtn1<<" iPrtn2 = "<<iPrtn2<<" g2q(3) = "<<g2q(3, iPrtn1, iCmptn, iPrtn2)<<endl;

     Qire.fill(0.0);
     SfT2.fill(0.0);
     SfH2.fill(0.0);

     if(iPrtn2 == 0) continue;
     if(iFlv != 0){
       if(kFv == 0 && iPrtn2 != iFv) continue;
       if(kFv == 1 && std::abs(iPrtn2) != iFv) continue;
     }

     if(g2q(0, iPrtn1, iCmptn, iPrtn2) < Smll) continue;

     Qpdf(iPrtn1, iPrtn2) = 1; // tag channels with the LO quark included

     FortranArray1D<double> g2chi{1, 3};
     g2chi(1) = g2q(1, iPrtn1, iCmptn, iPrtn2);
     g2chi(2) = g2q(2, iPrtn1, iCmptn, iPrtn2);
     g2chi(3) = g2q(3, iPrtn1, iCmptn, iPrtn2);

     //cout<<"iPrtn1 = "<<iPrtn1<<"  iPrtn2 = "<<iPrtn2<<"  g2q(1) = "<<g2q(1, iPrtn1, iCmptn, iPrtn2)<<endl;
     //cout<<"iPrtn1 = "<<iPrtn1<<"  iPrtn2 = "<<iPrtn2<<"  g2q(2) = "<<g2q(2, iPrtn1, iCmptn, iPrtn2)<<endl;
     //cout<<"iPrtn1 = "<<iPrtn1<<"  iPrtn2 = "<<iPrtn2<<"  g2q(3) = "<<g2q(3, iPrtn1, iCmptn, iPrtn2)<<endl;
     //cout<<"F2 = "<<F2_over_x<<"  TransPC = "<<TransPC<<"  TransPV = "<<TransPV<<"  FL = "<<FL<<"  F3 = "<<F3<<endl;
     //cout<<"iPrtn1 = "<<iPrtn1<<" x = "<<x<<" Q = "<<Q<<" PDF = "<<GetPDF(iHadn, iPrtn1, x, Q)<<" AlphaS/2pi = "<<GetAlphaS(Q) / 2.0 / Pi<<endl;

     if(abs(iPrtn2) <= nPrtn1){
       Qire(1) = 0.5 * (F2 - FL) / x;
       Qire(3) = 0.5 * FL / x;
       Qire(5) = 0.5 * F3 / x;
     }

     SFnConv(Qire, g2chi, SfT2, SfH2);

     for(int isf = 1; isf <= 3; isf++){
       Sfn123(isf) += SfT2(isf);
     }

     for(int isf = -1; isf<= 1; isf++){
       SfnHel(isf) += SfH2(isf);
     }

     //if(g2q(0,iPrtn1,iCmptn,iPrtn2) > Smll && abs(iPrtn1) <= nPrtn1 && abs(iPrtn2) <= nPrtn1){
     //  Gtem(1) = 0.5 * (F2NLO - FLNLO) / x;
     //  Gtem(3) = 0.5 * FLNLO / x;
     //  Gtem(5) = 0.5 * F3NLO / x;
     //  SFnConv(Gtem, g2chi, SfTg, SfHg);
     //  cout<<"iPrtn1 = "<<iPrtn1<<" iPrtn2 = "<<iPrtn2<<" g2q(1) = "<<scientific<<g2q(1,iPrtn1,iCmptn,iPrtn2)<<" Gtem(1) = "<<Gtem(1)<<" Gtem(3) = "<<Gtem(3)<<" SfTg(1) = "<<SfTg(1)<<" SfTg(2) = "<<SfTg(2)<<endl;
     //}

     //cout<<"Sfn123 = "<<Sfn123(1)<<"  "<<Sfn123(2)<<"  "<<Sfn123(3)<<endl;
     //cout<<"SfnHel = "<<SfnHel(-1)<<"  "<<SfnHel(0)<<"  "<<SfnHel(1)<<endl;
   }
 }

 double F2LOFE = 0.0;
 double F2NLOFE = 0.0, F2NLOFC = 0.0, F2NLOSub = 0.0;
 double FLNLOFE = 0.0, FLNLOFC = 0.0, FLNLOSub = 0.0;
 double F2NNLOFE = 0.0, F2NNLOFC = 0.0, F2NNLOSub = 0.0, F2NNLOZM = 0.0;
 double FLNNLOFE = 0.0, FLNNLOFC = 0.0, FLNNLOSub = 0.0, FLNNLOZM = 0.0;
 double F2lNNLO = 0.0, cNS = 0.0, cPS = 0.0, cG = 0.0;
 double F2N3LOFE = 0.0, F2N3LOFC = 0.0, F2N3LOSub = 0.0, F2N3LOZM = 0.0;
 double FLN3LOFE = 0.0, FLN3LOFC = 0.0, FLN3LOSub = 0.0, FLN3LOZM = 0.0;

 if(iOrdr >= 1 && iCmptn == 1){  //start NNLO, neutral-current DIS
                                            // only
   for(int iPrtn2 = 1; iPrtn2 <= nPrtn2; iPrtn2++){

     F2LOFE = 0.0;
     F2NLOFE = 0.0, F2NLOFC = 0.0, F2NLOSub = 0.0;
     FLNLOFE = 0.0, FLNLOFC = 0.0, FLNLOSub = 0.0;
     F2NNLOFE = 0.0, F2NNLOFC = 0.0, F2NNLOSub = 0.0, F2NNLOZM = 0.0;
     FLNNLOFE = 0.0, FLNNLOFC = 0.0, FLNNLOSub = 0.0, FLNNLOZM = 0.0;
     F2lNNLO = 0.0, cNS = 0.0, cPS = 0.0, cG = 0.0;
     F2N3LOFE = 0.0, F2N3LOFC = 0.0, F2N3LOSub = 0.0, F2N3LOZM = 0.0;
     FLN3LOFE = 0.0, FLN3LOFC = 0.0, FLN3LOSub = 0.0, FLN3LOZM = 0.0;

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

     // 1: GM
     // 2: ZM
     // 3: FFN
     // 4: IM
     // 5: N3LO only
     int SchemeOption = 5;

     if(iPrtn2 < nHeavy){// coefficient functions for F_l
       /*
       if(iOrdr >= 2){
         cNS = F2ZMNS2(x,Q,aMu,iHadn,iPrtn2,nHeavy-1);  //fNS_{l,l,light} with
                                                     // Nf=Nlight, in GmJS.f
         for(int iPrtn3 = nHeavy; iPrtn3 <= NFAboveThr; iPrtn3++){// Contributions of heavy states
           if(!AboveThreshold(iPrtn3, iPrtn3)) continue; //pn11: precaution, if quark masses
                                                                  //are not arranged in the ascending order
           double aM = aMass(0, iPrtn3); //use pole masses in all DIS kinematics
           Zeta = fchi(x,Q,aM,aM);

           cNS = cNS + F2LNS2(x,Q,aMu,aM,iHadn,iPrtn2)     // in GmJS.f, Eq. (25)
                     - F2lNSSub(x,Q,aMu,aM,iHadn,iPrtn2);  // conv. of A2NSll_heavy,in GmJS.f, GmJSa.f;
                                  //F2lNSsub pn must take X as the input (rescaling done inside)!
         }
         cPS = F2ZMPS2(x,Q,aMu,iHadn);
         cG  = F2ZMG2(x,Q,aMu,iHadn);

         double e2 = (g2q(1, iPrtn2, iCmptn, iPrtn2) + g2q(2, iPrtn2, iCmptn, iPrtn2)) / 2.0;
         F2lNNLO = F2lNNLO + (cNS + cPS + cG) * e2;
       }
       */
     }
     else{

       if(iPrtn2 == 5 || iPrtn2 == 6) continue; // yfu for test

       double Zeta = fchi(x,Q,aM2,aM2);

       if(iOrdr >= 0){

         if(SchemeOption == 1 || SchemeOption == 4){ // 1: GM, 4: IM
           F2LOFE = GetHoppetF2LO(iHadn, iPrtn2, Zeta, Q) / Zeta * 2.0;
         }
         else if(SchemeOption == 2){ // ZM
           F2LOFE = GetHoppetF2LO(iHadn, iPrtn2, x, Q) / x * 2.0; // ZM
         }

       }

       if(iOrdr >= 1){

         if(SchemeOption == 1){ // GM
           F2NLOFE = GetHoppetF2NLO_OnlyQuark(iHadn, iPrtn2, Zeta, Q) / Zeta * 2.0;

           if(Qpdf(-iPrtn2,-iPrtn2)) AcotSub(iHadn, -iPrtn2, aM2, 0.0, Zeta, Q, aMu, Q1a);

           if(Qpdf(iPrtn2, iPrtn2)) AcotSub(iHadn, iPrtn2, aM2, 0.0, Zeta, Q, aMu, Q1b);

           F2NLOSub = (Q1a(1) + Q1a(3) + Q1b(1) + Q1b(3)) * 2.0 * GetAlphaS(Q) / (2.0 * Pi);

           Acot1G(iHadn, aM2, aM2, x, Q, aMu, Gtem);
           F2NLOFC = (Gtem(1) + Gtem(3)) * 2.0 * GetAlphaS(Q) / (2.0 * Pi);
         }
         else if(SchemeOption == 2){ // ZM
           F2NLOFE = GetHoppetF2NLO(iHadn, iPrtn2, x, Q) / x * 2.0; // ZM
         }
         else if(SchemeOption == 3){ // FFN
           Acot1G(iHadn, aM2, aM2, x, Q, aMu, Gtem);
           F2NLOFC = (Gtem(1) + Gtem(3)) * 2.0 * GetAlphaS(Q) / (2.0 * Pi);
         }
         else if(SchemeOption == 4){ // IM
           F2NLOFE = GetHoppetF2NLO(iHadn, iPrtn2, Zeta, Q) / Zeta * 2.0;
         }

         //FLNLOFE = GetHoppetFLLO(iHadn, iPrtn2, Zeta, Q) / Zeta;
         //double tmp_F2NLOSub = GetSubtraction(1, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta;
         //FLNLOSub = GetSubtraction(1, 2, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta;

         //double tmp_F2NLOFC = GetxF2Hg0(iHadn, x, Q, Q, aM2) / x;

         //cout<<F2LOFE<<"  "<<F2NLOFE<<"  "<<F2NLOSub<<"  "<<F2NLOFC<<endl;
         

         //FLNLOFC = GetxFLHg0(iHadn, x, Q, Q, aM2) / x;
         //cout<<x<<"  "<<Zeta<<"  "<<Q<<"  "<<iPrtn2<<"  "<<F2N3LOFE<<"  "<<F2N3LOSub<<"  "<<F2N3LOFC<<endl;
       }

       if(iOrdr >= 2){

         if(SchemeOption == 1){ // GM
           F2NNLOFE = //GetHoppetF2NLO_OnlyQuark(iHadn, iPrtn2, Zeta, Q) / Zeta * 2.0
                    + GetxF2ZMNS2(iHadn, iPrtn2, Zeta, Q, Q, aM2, NFAboveThr) / Zeta * 2.0;
           F2NNLOSub = GetSubtraction(2, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0;
           F2NNLOFC = GetxF2Hg(iHadn, x, Q, Q, aM2) / x * 2.0
                    + GetxF2Hq(iHadn, x, Q, Q, aM2) / x * 2.0;
         }
         else if(SchemeOption == 2){ // ZM
           F2NNLOFE = GetHoppetF2NNLO(iHadn, iPrtn2, x, Q) / x * 2.0; // ZM
         }
         else if(SchemeOption == 3){ // FFN
           F2NNLOFC = GetxF2Hg(iHadn, x, Q, Q, aM2) / x * 2.0
                    + GetxF2Hq(iHadn, x, Q, Q, aM2) / x * 2.0;
         }
         else if(SchemeOption == 4){ // IM
           F2NNLOFE = GetHoppetF2NNLO(iHadn, iPrtn2, Zeta, Q) / Zeta * 2.0;
         }

         //FLNNLOFE = GetHoppetFLNLO(iHadn, iPrtn2, Zeta, Q) / Zeta;

         //FLNNLOSub = GetSubtraction(2, 2, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta;
         //F2NNLOSub = GetSubtractionXg(0, 2, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta;
                   //+ GetSubtractionXq(0, 2, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta;
         //          + GetSubtractionXg(1, 1, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta;
         //F2NNLOSub = F2HQSub2(x, Q, aMu, aM2, iHadn) / 2.0;

         //F2NNLOFC = //F2hlPS2(x,Q,aMu,aM2,iHadn) / 2.0;  //in GmJS.f
         //         + F2hg2  (x,Q,aMu,aM2,iHadn) / 2.0; //in GmJS.f

         //FLNNLOFC = GetxFLHg(iHadn, x, Q, Q, aM2) / x
         //         + GetxFLHq(iHadn, x, Q, Q, aM2) / x;
         //cout<<x<<"  "<<Zeta<<"  "<<Q<<"  "<<iPrtn2<<"  "<<F2NNLOFE<<"  "<<F2NNLOSub<<"  "<<F2NNLOFC<<endl;
         //cout<<GetSubtractionXg(0, 2, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta<<"  "<<GetSubtractionXq(0, 2, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta<<endl;
         //F2NNLOZM = GetHoppetF2NNLO(iHadn, iPrtn2, x, Q) / x * 2.0;
       }

       if(iOrdr >= 3){
         if(Q > 400.0) continue;
         //F2N3LOFE = GetHoppetF2NNLO(iHadn, iPrtn2, Zeta, Q) / Zeta * 2.0;
         //F2N3LOFE = GetHoppetF2N3LO(iHadn, iPrtn2, x, Q) / x * 2.0; // ZM

         FLN3LOFE = 0.0;

         if(SchemeOption == 1){ // GM
           F2N3LOSub = GetSubtraction(3, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0;

           //achi = 0.3;
           //double x_chi = fchi(x,Q,aM2,aM2);
           //achi = 0.0;

           F2N3LOFC = GetxF2Hg3A(iHadn, x, Q, Q, aM2) / x * 2.0
                    + GetxF2Hq3A(iHadn, x, Q, Q, aM2) / x * 2.0;
         }
         else if(SchemeOption == 2){ // ZM
           F2N3LOFE = GetHoppetF2N3LO(iHadn, iPrtn2, x, Q) / x * 2.0; // ZM
         }
         else if(SchemeOption == 3){ // FFN
           F2N3LOFC = GetxF2Hg3A(iHadn, x, Q, Q, aM2) / x * 2.0
                    + GetxF2Hq3A(iHadn, x, Q, Q, aM2) / x * 2.0;
         }
         else if(SchemeOption == 4){ // IM
           F2N3LOFE = GetHoppetF2N3LO(iHadn, iPrtn2, Zeta, Q) / Zeta * 2.0;
         }
         else if(SchemeOption == 5){ // N3LO only
           //F2N3LOFC = GetxF2Hg3A(iHadn, x, Q, Q, aM2) / x * 2.0;
           //Acot1G(iHadn, aM2, aM2, x, Q, aMu, Gtem);
           //F2N3LOFC = (Gtem(1) + Gtem(3)) * 2.0 * GetAlphaS(Q) / (2.0 * Pi);
           //F2N3LOFC = GetxF2Hg0(iHadn, x, Q, Q, aM2) / x * 2.0;
           F2N3LOFC = GetxF2Hg(iHadn, x, Q, Q, aM2) / x * 2.0;
           //F2N3LOFC = GetxF2Hq3A(iHadn, x, Q, Q, aM2) / x * 2.0;

           //F2N3LOFC = GetxF2Hg(iHadn, x, Q, Q, aM2) / x * 2.0;

           //F2N3LOFC = GetSubtractionXg(0, 2, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0
           //         + GetSubtractionXg(1, 1, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0;


           //F2N3LOSub = GetSubtractionXg(0, 3, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0
           //          + GetSubtractionXg(1, 2, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0
           //          + GetSubtractionXg(2, 1, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0;
           //F2N3LOSub = GetSubtractionXq(0, 3, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0
           //          + GetSubtractionXq(1, 2, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0;
           //F2N3LOSub = GetSubtractionPDF(0, 3, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0;
           //F2N3LOSub = F2N3LOSub * (-1.0);

           //F2N3LOFE = GetHoppetF2LO(iHadn, iPrtn2, Zeta, Q) / Zeta * 2.0;
         }

         //F2N3LOSub = GetSubtractionXg(0, 3, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0
         //          + GetSubtractionXg(1, 2, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0
         //          + GetSubtractionXg(2, 1, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0;
         //F2N3LOSub = GetSubtractionXq(0, 3, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0
         //          + GetSubtractionXq(1, 2, 1, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0;
         //FLN3LOSub = GetSubtraction(3, 2, iPrtn2, iHadn, Zeta, Q, Q, aM2) / Zeta * 2.0;
         FLN3LOSub = 0.0;


         FLN3LOFC = 0.0;
         cout<<LOG_INFO<<iPrtn2<<"  "<<x<<"  "<<Q<<"  "<<F2N3LOFC<<endl;
       }
     }

     double e2 = (g2q(1, iPrtn2, iCmptn, iPrtn2) + g2q(2, iPrtn2, iCmptn, iPrtn2)) / 2.0;

     if(SchemeOption == 1){ // GM
       F2tmp3 = e2 * (F2LOFE + F2NLOFE + F2NLOFC - F2NLOSub
                             + F2NNLOFE + F2NNLOFC - F2NNLOSub
                             + F2N3LOFE + F2N3LOFC - F2N3LOSub); // GM
     }
     else if(SchemeOption == 2 || SchemeOption == 4){ // 2: ZM, 4: IM
       F2tmp3 = e2 * (F2LOFE + F2NLOFE + F2NNLOFE + F2N3LOFE); // ZM
     }
     else if(SchemeOption == 3){ // FFN
       F2tmp3 = e2 * (F2NLOFC + F2NNLOFC + F2N3LOFC); // FFN
     }
     else if(SchemeOption == 5){ // N3LO only
       F2tmp3 = e2 * (F2N3LOFE + F2N3LOFC - F2N3LOSub);
     }

     //F2tmp3 = e2 * (cNS + cPS + cG + F2NNLOFE + F2NNLOFC - F2NNLOSub);
     //F2tmp3 = e2 * F2N3LOFC;
     FLtmp3 = e2 * (FLN3LOFE - FLN3LOSub) * 1000.0 * pow(x, 0.5);

     F2o3 = F2o3 + F2tmp3; FLo3 = FLo3 + FLtmp3;
   } // end loop iPrtn2

   F2LConvNC(F2o3, FLo3, SfT3, SfH3);

   Sfn123 = SfT3;
   SfnHel = SfH3;
 }








/* for(int iPrtn2 = 1; iPrtn2 <= nPrtn2; iPrtn2++){
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

   double F2tmp3 = GetHoppetF2LO(iHadn, iPrtn2, x, Q) + GetHoppetF2NLO(iHadn, iPrtn2, x, Q) + GetHoppetF2NNLO(iHadn, iPrtn2, x, Q) + GetHoppetF2N3LO(iHadn, iPrtn2, x, Q);
   double FLtmp3 = GetHoppetFLLO(iHadn, iPrtn2, x, Q) + GetHoppetFLNLO(iHadn, iPrtn2, x, Q) + GetHoppetFLNNLO(iHadn, iPrtn2, x, Q) + GetHoppetFLN3LO(iHadn, iPrtn2, x, Q);
   //double F2tmp3 = GetHoppetF2NLO(iHadn, iPrtn2, x, Q);
   //double FLtmp3 = 0.0;

   double e2 = (g2q(1, iPrtn2, iCmptn, iPrtn2) + g2q(2, iPrtn2, iCmptn, iPrtn2)) / 2.0;
   F2tmp3 = e2 * F2tmp3 / x;
   FLtmp3 = e2 * FLtmp3 / x;
   //cout<<"iPrtn2 = "<<iPrtn2<<" e2 = "<<e2<<endl;

   F2o3 = F2o3 + F2tmp3; FLo3 = FLo3 + FLtmp3;

 }// Part NNLO

 F2LConvNC(F2o3, FLo3, SfT3, SfH3);

 Sfn123 = SfT3;
 SfnHel = SfH3;
*/
}

void CalcDIS::CloneHoppetSF()
{
#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)

 Hoppet_C2LO = hoppet_get_C2LO_clone();
 Hoppet_CLLO = hoppet_get_CLLO_clone();
 Hoppet_C3LO = hoppet_get_C3LO_clone();

 Hoppet_C2NLO = split_mat_clone(hoppet_get_C2NLO_clone());
 Hoppet_CLNLO = split_mat_clone(hoppet_get_CLNLO_clone());
 Hoppet_C3NLO = split_mat_clone(hoppet_get_C3NLO_clone());

 Hoppet_C2NNLO = split_mat_clone(hoppet_get_C2NNLO_clone());
 Hoppet_CLNNLO = split_mat_clone(hoppet_get_CLNNLO_clone());
 Hoppet_C3NNLO = split_mat_clone(hoppet_get_C3NNLO_clone());

 Hoppet_C2N3LO = split_mat_clone(hoppet_get_C2N3LO_clone());
 Hoppet_CLN3LO = split_mat_clone(hoppet_get_CLN3LO_clone());
 Hoppet_C3N3LO = split_mat_clone(hoppet_get_C3N3LO_clone());

 Hoppet_C2N3LO_fl11 = split_mat_clone(hoppet_get_C2N3LO_fl11_clone());
 Hoppet_CLN3LO_fl11 = split_mat_clone(hoppet_get_CLN3LO_fl11_clone());

 Hoppet_grid = hoppet::grid_def(hoppet_cxx__grid_def__copy(Hoppet_C2NLO.grid().ptr()));
 Hoppet_xpdf = hoppet::grid_quant_2d(Hoppet_grid, 14);
 Hoppet_xpdf_onlyquark = hoppet::grid_quant_2d(Hoppet_grid, 14);
 Hoppet_xpdf_onlygluon = hoppet::grid_quant_2d(Hoppet_grid, 14);

#endif
}

double CalcDIS::GetHoppetF2LO(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 FillHoppetPDFTable(ihadron, Q);

 hoppet::grid_quant_2d f2LO = Hoppet_C2LO * Hoppet_xpdf;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = f2LO[iflv + 6].at_x(x);
#endif

 return Value;
}

double CalcDIS::GetHoppetFLLO(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 FillHoppetPDFTable(ihadron, Q);

 hoppet::grid_quant_2d fLLO = Hoppet_CLLO * Hoppet_xpdf;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = fLLO[iflv + 6].at_x(x);
#endif

 return Value;
}

double CalcDIS::GetHoppetF3LO(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 FillHoppetPDFTable(ihadron, Q);

 hoppet::grid_quant_2d f3LO = Hoppet_C3LO * Hoppet_xpdf;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = f3LO[iflv + 6].at_x(x);
#endif

 return Value;
}

double CalcDIS::GetHoppetF2NLO(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 //if(pthread_mutex_lock(&hoppet_mtx) != 0){
 //  cout<<"Error: lock failed"<<endl;
 //}
//std::cout << "ENTER tid=" << pthread_self() << " &hoppet_mtx=" << (void*)&hoppet_mtx << endl;

 FillHoppetPDFTable(ihadron, Q);

// Hoppet_C2NLO = split_mat_clone(hoppet_get_C2NLO_clone());
// cout<< "tid=" << pthread_self()<<"  "<<Hoppet_C2NLO.grid().ny()<<"  "<<Hoppet_xpdf.grid().ny()<<"  "<<Hoppet_xpdf.extras().size_dim0<<"  "<<Hoppet_xpdf.extras().size_dim1<<"  "<<this<<endl;

// std::cout
//  << "C2 ptr=" << Hoppet_C2NLO.ptr()
//  << " grid_ptr=" << Hoppet_C2NLO.grid().ptr()
//  << " xpdf_grid_ptr=" << Hoppet_xpdf.grid().ptr()
//  << "\n";

 hoppet::grid_quant_2d f2NLO = Hoppet_C2NLO.ptr() * Hoppet_xpdf;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = f2NLO[iflv + 6].at_x(x) * AlphaS2pi;

//std::cout << "EXIT tid=" << pthread_self() << " &hoppet_mtx=" << (void*)&hoppet_mtx << endl;

 //if(pthread_mutex_unlock(&hoppet_mtx) != 0){
 //  cout<<"Error: unlock failed"<<endl;
// }

#endif

 return Value;
}

double CalcDIS::GetHoppetF2NLO_OnlyQuark(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 hoppet::grid_quant_2d f2NLO = Hoppet_C2NLO.ptr() * Hoppet_xpdf_onlyquark;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = f2NLO[iflv + 6].at_x(x) * AlphaS2pi;

#endif

 return Value;
}

double CalcDIS::GetHoppetFLNLO(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 hoppet::grid_quant_2d fLNLO = Hoppet_CLNLO.ptr() * Hoppet_xpdf;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = fLNLO[iflv + 6].at_x(x) * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetHoppetF3NLO(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 hoppet::grid_quant_2d f3NLO = Hoppet_C3NLO.ptr() * Hoppet_xpdf;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = f3NLO[iflv + 6].at_x(x) * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetHoppetF2NNLO(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 hoppet::grid_quant_2d f2NNLO = Hoppet_C2NNLO.ptr() * Hoppet_xpdf;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = f2NNLO[iflv + 6].at_x(x) * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetHoppetFLNNLO(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 hoppet::grid_quant_2d fLNNLO = Hoppet_CLNNLO.ptr() * Hoppet_xpdf;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = fLNNLO[iflv + 6].at_x(x) * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetHoppetF3NNLO(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 hoppet::grid_quant_2d f3NNLO = Hoppet_C3NNLO.ptr() * Hoppet_xpdf;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = f3NNLO[iflv + 6].at_x(x) * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetHoppetF2N3LO(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 hoppet::grid_quant_2d f2N3LO = Hoppet_C2N3LO.ptr() * Hoppet_xpdf + Hoppet_C2N3LO_fl11.ptr() * Hoppet_xpdf;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = f2N3LO[iflv + 6].at_x(x) * AlphaS2pi * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetHoppetFLN3LO(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 hoppet::grid_quant_2d fLN3LO = Hoppet_CLN3LO.ptr() * Hoppet_xpdf + Hoppet_CLN3LO_fl11.ptr() * Hoppet_xpdf;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = fLN3LO[iflv + 6].at_x(x) * AlphaS2pi * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetHoppetF3N3LO(int ihadron, int iparton, double x, double Q)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 hoppet::grid_quant_2d f3N3LO = Hoppet_C3N3LO.ptr() * Hoppet_xpdf;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 Value = f3N3LO[iflv + 6].at_x(x) * AlphaS2pi * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

void CalcDIS::FillHoppetPDFTable(int ihadron, double Q)
{
#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 int Nfl = GetNfl(Q);

 for(int iflv = 0; iflv < Hoppet_xpdf.extras().size_dim0; iflv++){
   int parton = iflv - 6;
   if(iflv - 6 == 1) parton = 2;
   else if(iflv - 6 == 2) parton = 1;
   else if(iflv - 6 == -1) parton = -2;
   else if(iflv - 6 == -2) parton = -1;
   else parton = iflv - 6;

   vector<double> xvals = Hoppet_xpdf.grid().x_values();
   for(int iy = 0; iy < Hoppet_xpdf.extras().size_dim1; iy++){
     double x = xvals.at(iy);
     Hoppet_xpdf(iflv, iy) = (abs(parton) <= Nfl) ? x * GetPDF(ihadron, parton, x, Q) : 0.0;
     Hoppet_xpdf_onlyquark(iflv, iy) = (abs(parton) <= Nfl) ? x * GetPDF(ihadron, parton, x, Q) : 0.0;
     Hoppet_xpdf_onlygluon(iflv, iy) = (abs(parton) <= Nfl) ? x * GetPDF(ihadron, parton, x, Q) : 0.0;

     if(parton == 0) Hoppet_xpdf_onlyquark(iflv, iy) = 0.0;

     if(parton != 0) Hoppet_xpdf_onlygluon(iflv, iy) = 0.0;
   }
 }

 Hoppet_xgluon = hoppet::grid_quant(Hoppet_xpdf[0 + 6]);

 Hoppet_xquark = hoppet::grid_quant(Hoppet_xpdf[1 + 6]);
 vector<double> xvals = Hoppet_xpdf.grid().x_values();

 for(int iy = 0; iy < Hoppet_xquark.size(); iy++){
   double x = xvals.at(iy);
   Hoppet_xquark[iy] = x * GetPDF(ihadron, 20, x, Q);
 }

#endif
}

double CalcDIS::GetxF2Hg0(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xC2Hg0 = hoppet::grid_conv(Hoppet_grid, sf_C2Hg0);

 hoppet::grid_quant xF2Hg0 = xC2Hg0 * Hoppet_xgluon;

 Value = xF2Hg0.at_x(x) * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetxFLHg0(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xCLHg0 = hoppet::grid_conv(Hoppet_grid, sf_CLHg0);

 hoppet::grid_quant xFLHg0 = xCLHg0 * Hoppet_xgluon;

 Value = xFLHg0.at_x(x) * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetxF2Hg(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xC2Hg = hoppet::grid_conv(Hoppet_grid, sf_C2Hg);

 hoppet::grid_quant xF2Hg = xC2Hg * Hoppet_xgluon;

 Value = xF2Hg.at_x(x) * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetxFLHg(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xCLHg = hoppet::grid_conv(Hoppet_grid, sf_CLHg);

 hoppet::grid_quant xFLHg = xCLHg * Hoppet_xgluon;

 Value = xFLHg.at_x(x) * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetxF2Hq(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xC2Hq = hoppet::grid_conv(Hoppet_grid, sf_C2Hq);

 hoppet::grid_quant xF2Hq = xC2Hq * Hoppet_xquark;

 Value = xF2Hq.at_x(x) * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetxFLHq(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xCLHq = hoppet::grid_conv(Hoppet_grid, sf_CLHq);

 hoppet::grid_quant xFLHq = xCLHq * Hoppet_xquark;

 Value = xFLHq.at_x(x) * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetxF2Hg3A(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xC2Hg3 = hoppet::grid_conv(Hoppet_grid, sf_C2Hg3A);

 hoppet::grid_quant xF2Hg3 = xC2Hg3 * Hoppet_xgluon;

 Value = xF2Hg3.at_x(x) * AlphaS2pi * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetxF2Hg3B(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xC2Hg3 = hoppet::grid_conv(Hoppet_grid, sf_C2Hg3B);

 hoppet::grid_quant xF2Hg3 = xC2Hg3 * Hoppet_xgluon;

 Value = xF2Hg3.at_x(x) * AlphaS2pi * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetxF2Hq3A(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xC2Hq3 = hoppet::grid_conv(Hoppet_grid, sf_C2Hq3A);

 hoppet::grid_quant xF2Hq3 = xC2Hq3 * Hoppet_xquark;

 Value = xF2Hq3.at_x(x) * AlphaS2pi * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetxF2Hq3B(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xC2Hq3 = hoppet::grid_conv(Hoppet_grid, sf_C2Hq3B);

 hoppet::grid_quant xF2Hq3 = xC2Hq3 * Hoppet_xquark;

 Value = xF2Hq3.at_x(x) * AlphaS2pi * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetxA2HgL0Xg(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xA2HgL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL0);

 hoppet::grid_quant xA2HgL0Xg = xA2HgL0 * Hoppet_xgluon;

 Value = xA2HgL0Xg.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA2HgL1Xg(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xA2HgL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL1);

 hoppet::grid_quant xA2HgL1Xg = xA2HgL1 * Hoppet_xgluon;

 Value = xA2HgL1Xg.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA2HgL2Xg(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xA2HgL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL2);

 hoppet::grid_quant xA2HgL2Xg = xA2HgL2 * Hoppet_xgluon;

 Value = xA2HgL2Xg.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA3HgL0Xg(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xA3HgL0 = hoppet::grid_conv(Hoppet_grid, sf_A3HgL0);

 hoppet::grid_quant xA3HgL0Xg = xA3HgL0 * Hoppet_xgluon;

 Value = xA3HgL0Xg.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA3HgLLXg(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xA3HgLL = hoppet::grid_conv(Hoppet_grid, sf_A3HgLL);

 hoppet::grid_quant xA3HgLLXg = xA3HgLL * Hoppet_xgluon;

 Value = xA3HgLLXg.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA2HqL0Xq(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xA2HqL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL0);

 hoppet::grid_quant xA2HqL0Xq = xA2HqL0 * Hoppet_xquark;

 Value = xA2HqL0Xq.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA2HqL1Xq(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xA2HqL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL1);

 hoppet::grid_quant xA2HqL1Xq = xA2HqL1 * Hoppet_xquark;

 Value = xA2HqL1Xq.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA2HqL2Xq(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xA2HqL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL2);

 hoppet::grid_quant xA2HqL2Xq = xA2HqL2 * Hoppet_xquark;

 Value = xA2HqL2Xq.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA3HqL0Xq(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xA3HqL0 = hoppet::grid_conv(Hoppet_grid, sf_A3HqPSL0);

 hoppet::grid_quant xA3HqL0Xq = xA3HqL0 * Hoppet_xquark;

 Value = xA3HqL0Xq.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA3HqLLXq(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 xA3HqLL = hoppet::grid_conv(Hoppet_grid, sf_A3HqPSLL);

 hoppet::grid_quant xA3HqLLXq = xA3HqLL * Hoppet_xquark;

 Value = xA3HqLLXq.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA2HgXg_vogt(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 hoppet::grid_conv GridConv = hoppet::grid_conv(Hoppet_grid, sf_A2PShg_vogt);

 hoppet::grid_quant GridResult = GridConv * Hoppet_xgluon;

 Value = GridResult.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA2HgXg_hpt(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 hoppet::grid_conv GridConv = hoppet::grid_conv(Hoppet_grid, sf_A2PShg);

 hoppet::grid_quant GridResult = GridConv * Hoppet_xgluon;

 Value = GridResult.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA2HqXq_hpt(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 hoppet::grid_conv GridConv = hoppet::grid_conv(Hoppet_grid, sf_A2PShq);

 hoppet::grid_quant GridResult = GridConv * Hoppet_xquark;

 Value = GridResult.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA2HgXg_cteq(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 hoppet::grid_conv GridConv = hoppet::grid_conv(Hoppet_grid, sf_A2Hg_CTEQ);

 hoppet::grid_quant GridResult = GridConv * Hoppet_xgluon;

 Value = GridResult.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA2HqXq_cteq(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 hoppet::grid_conv GridConv = hoppet::grid_conv(Hoppet_grid, sf_A2HqPS_CTEQ);

 hoppet::grid_quant GridResult = GridConv * Hoppet_xquark;

 Value = GridResult.at_x(x);
#endif

 return Value;
}

double CalcDIS::GetxA2HgXg(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 double LL = SFHQ_LL;

 xA2HgL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL0);
 xA2HgL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL1);
 xA2HgL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL2);

 hoppet::grid_quant xA2HgL0Xg = xA2HgL0 * Hoppet_xgluon;
 hoppet::grid_quant xA2HgL1Xg = xA2HgL1 * Hoppet_xgluon;
 hoppet::grid_quant xA2HgL2Xg = xA2HgL2 * Hoppet_xgluon;

 Value = xA2HgL0Xg.at_x(x) + xA2HgL1Xg.at_x(x) * LL + xA2HgL2Xg.at_x(x) * LL * LL;
#endif

 return Value;
}

double CalcDIS::GetxA2HqXq(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 double LL = SFHQ_LL;

 xA2HqL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL0);
 xA2HqL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL1);
 xA2HqL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL2);

 hoppet::grid_quant xA2HqL0Xq = xA2HqL0 * Hoppet_xquark;
 hoppet::grid_quant xA2HqL1Xq = xA2HqL1 * Hoppet_xquark;
 hoppet::grid_quant xA2HqL2Xq = xA2HqL2 * Hoppet_xquark;

 Value = xA2HqL0Xq.at_x(x) + xA2HqL1Xq.at_x(x) * LL + xA2HqL2Xq.at_x(x) * LL * LL;
#endif

 return Value;
}

double CalcDIS::GetxF2ZMNS2(int ihadron, int iparton, double x, double Q, double QMu, double MQ, int nf)
{
 if(!isDefineNNLOFunctions) DefineFunctions_nnlo();

 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);
 SFHQ_nfl = nf;

 double LL = SFHQ_LL;

 hoppet::grid_conv xC2ZMNS2 = hoppet::grid_conv(Hoppet_grid, sf_C2ZMNS2);

 hoppet::grid_quant_2d xF2ZMNS2 = hoppet::grid_quant_2d(Hoppet_grid, 14);
 xF2ZMNS2 = 0.0;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 xF2ZMNS2[iflv + 6] = xC2ZMNS2 * Hoppet_xpdf[iflv + 6];
 Value = xF2ZMNS2[iflv + 6].at_x(x) * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetxFLZMNS2(int ihadron, int iparton, double x, double Q, double QMu, double MQ, int nf)
{
 if(!isDefineNNLOFunctions) DefineFunctions_nnlo();

 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);
 SFHQ_nfl = nf;

 double LL = SFHQ_LL;

 hoppet::grid_conv xCLZMNS2 = hoppet::grid_conv(Hoppet_grid, sf_CLZMNS2);

 hoppet::grid_quant_2d xFLZMNS2 = hoppet::grid_quant_2d(Hoppet_grid, 14);
 xFLZMNS2 = 0.0;

 int iflv = iparton;

 if(iparton == 1) iflv = 2;
 else if(iparton == 2) iflv = 1;
 else if(iparton == -1) iflv = -2;
 else if(iparton == -2) iflv = -1;
 else iflv = iparton;

 xFLZMNS2[iflv + 6] = xCLZMNS2 * Hoppet_xpdf[iflv + 6];
 Value = xFLZMNS2[iflv + 6].at_x(x) * AlphaS2pi * AlphaS2pi;
#endif

 return Value;
}

double CalcDIS::GetSubtraction(int order, int f2fl, int hflv, int ihadron, double x, double Q, double QMu, double MQ)
{
 if(!isDefineNNLOFunctions) DefineFunctions_nnlo();

 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 //cout<<LOG_INFO<<"Clone HoppetSF:"<<endl;
 CloneHoppetSF();

 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 //cout<<LOG_INFO<<"Fill Hoppet PDF table:"<<endl;
 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 hoppet::grid_quant_2d Hoppet_subpdf_gluon_1 = hoppet::grid_quant_2d(Hoppet_grid, 14);
 hoppet::grid_quant_2d Hoppet_subpdf_gluon_2 = hoppet::grid_quant_2d(Hoppet_grid, 14);
 hoppet::grid_quant_2d Hoppet_subpdf_gluon_3 = hoppet::grid_quant_2d(Hoppet_grid, 14);

 hoppet::grid_quant_2d Hoppet_subpdf_quark_2 = hoppet::grid_quant_2d(Hoppet_grid, 14);
 hoppet::grid_quant_2d Hoppet_subpdf_quark_3 = hoppet::grid_quant_2d(Hoppet_grid, 14);

 Hoppet_subpdf_gluon_1 = 0.0;
 Hoppet_subpdf_gluon_2 = 0.0;
 Hoppet_subpdf_gluon_3 = 0.0;
 Hoppet_subpdf_quark_2 = 0.0;
 Hoppet_subpdf_quark_3 = 0.0;

 hoppet::grid_quant_2d fsub = hoppet::grid_quant_2d(Hoppet_grid, 14);
 fsub = 0.0;

 double LL = SFHQ_LL;

 if(order == 1){
   // 01 gluon
   xA1Hg = hoppet::grid_conv(Hoppet_grid, sf_A1Hg);

   hoppet::grid_quant xA1HgL1Xg = xA1Hg * Hoppet_xgluon;

   Hoppet_subpdf_gluon_1[hflv + 6] = AlphaS2pi * xA1HgL1Xg * LL / 2.0;

   if(f2fl == 1) fsub = Hoppet_C2LO * Hoppet_subpdf_gluon_1;
   else          fsub = Hoppet_CLLO * Hoppet_subpdf_gluon_1;
 }
 else if(order == 2){
   // 02 gluon
   xA2HgL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL0);
   xA2HgL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL1);
   xA2HgL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL2);

   hoppet::grid_quant xA2HgL0Xg = xA2HgL0 * Hoppet_xgluon;
   hoppet::grid_quant xA2HgL1Xg = xA2HgL1 * Hoppet_xgluon;
   hoppet::grid_quant xA2HgL2Xg = xA2HgL2 * Hoppet_xgluon;

   Hoppet_subpdf_gluon_2[hflv + 6] = (xA2HgL0Xg + xA2HgL1Xg * LL + xA2HgL2Xg * LL * LL) * AlphaS2pi * AlphaS2pi / 2.0;

   // 02 quark
   xA2HqL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL0);
   xA2HqL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL1);
   xA2HqL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL2);

   hoppet::grid_quant xA2HqL0Xq = xA2HqL0 * Hoppet_xquark;
   hoppet::grid_quant xA2HqL1Xq = xA2HqL1 * Hoppet_xquark;
   hoppet::grid_quant xA2HqL2Xq = xA2HqL2 * Hoppet_xquark;

   Hoppet_subpdf_quark_2[hflv + 6] = (xA2HqL0Xq + xA2HqL1Xq * LL + xA2HqL2Xq * LL * LL) * AlphaS2pi * AlphaS2pi / 2.0;

   // 11 gluon
   xA1Hg = hoppet::grid_conv(Hoppet_grid, sf_A1Hg);

   hoppet::grid_quant xA1HgL1Xg = xA1Hg * Hoppet_xgluon;

   Hoppet_subpdf_gluon_1[hflv + 6] = AlphaS2pi * xA1HgL1Xg * LL / 2.0;

   if(f2fl == 1){
     hoppet::grid_conv xC1A1 = hoppet::grid_conv(Hoppet_grid, sf_AnalyticC1A1);
     hoppet::grid_quant xC1A1Xg = xC1A1 * Hoppet_xgluon / 2.0 * AlphaS2pi * AlphaS2pi;
     hoppet::grid_quant_2d fsub_tmp = hoppet::grid_quant_2d(Hoppet_grid, 14);
     fsub_tmp = 0.0;
     fsub_tmp[hflv + 6] = xC1A1Xg;

     fsub = Hoppet_C2LO * Hoppet_subpdf_gluon_2
          + fsub_tmp
          + Hoppet_C2LO * Hoppet_subpdf_quark_2;
   }
   else{
     fsub = Hoppet_CLLO * Hoppet_subpdf_gluon_2
          + Hoppet_CLNLO * Hoppet_subpdf_gluon_1 * AlphaS2pi
          + Hoppet_CLLO * Hoppet_subpdf_quark_2;
   }
 }
 else if(order == 3){
   // 03 gluon
   //xA3HgL0 = hoppet::grid_conv(Hoppet_grid, sf_A3HgL0);
   //xA3HgLL = hoppet::grid_conv(Hoppet_grid, sf_A3HgLL);

   //hoppet::grid_quant xA3HgL0Xg = xA3HgL0 * Hoppet_xgluon;
   //hoppet::grid_quant xA3HgLLXg = xA3HgLL * Hoppet_xgluon;

   //Hoppet_subpdf_gluon_3[hflv + 6] = (xA3HgL0Xg + xA3HgLLXg) / 2.0; // contains alphas

   hoppet::grid_conv xA3Hg = hoppet::grid_conv(Hoppet_grid, sf_A3Hg_ome);

   hoppet::grid_quant xA3HgXg = xA3Hg * Hoppet_xgluon;

   Hoppet_subpdf_gluon_3[hflv + 6] = xA3HgXg / 2.0; // contains alphas

   // 12 gluon
   xA2HgL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL0);
   xA2HgL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL1);
   xA2HgL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL2);

   hoppet::grid_quant xA2HgL0Xg = xA2HgL0 * Hoppet_xgluon;
   hoppet::grid_quant xA2HgL1Xg = xA2HgL1 * Hoppet_xgluon;
   hoppet::grid_quant xA2HgL2Xg = xA2HgL2 * Hoppet_xgluon;

   Hoppet_subpdf_gluon_2[hflv + 6] = (xA2HgL0Xg + xA2HgL1Xg * LL + xA2HgL2Xg * LL * LL) * AlphaS2pi * AlphaS2pi / 2.0;

   // 21 gluon
   xA1Hg = hoppet::grid_conv(Hoppet_grid, sf_A1Hg);

   hoppet::grid_quant xA1HgL1Xg = xA1Hg * Hoppet_xgluon;

   Hoppet_subpdf_gluon_1[hflv + 6] = AlphaS2pi * xA1HgL1Xg * LL / 2.0;

   // 03 quark
   //xA3HqL0 = hoppet::grid_conv(Hoppet_grid, sf_A3HqPSL0);
   //xA3HqLL = hoppet::grid_conv(Hoppet_grid, sf_A3HqPSLL);

   //hoppet::grid_quant xA3HqL0Xq = xA3HqL0 * Hoppet_xquark;
   //hoppet::grid_quant xA3HqLLXq = xA3HqLL * Hoppet_xquark;

   //Hoppet_subpdf_quark_3[hflv + 6] = (xA3HqL0Xq + xA3HqLLXq) / 2.0; // contains alphas

   hoppet::grid_conv xA3Hq = hoppet::grid_conv(Hoppet_grid, sf_A3HqPS_ome);

   hoppet::grid_quant xA3HqXq = xA3Hq * Hoppet_xquark;

   Hoppet_subpdf_quark_3[hflv + 6] = xA3HqXq / 2.0; // contains alphas

   // 12 quark
   xA2HqL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL0);
   xA2HqL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL1);
   xA2HqL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL2);

   hoppet::grid_quant xA2HqL0Xq = xA2HqL0 * Hoppet_xquark;
   hoppet::grid_quant xA2HqL1Xq = xA2HqL1 * Hoppet_xquark;
   hoppet::grid_quant xA2HqL2Xq = xA2HqL2 * Hoppet_xquark;

   Hoppet_subpdf_quark_2[hflv + 6] = AlphaS2pi * AlphaS2pi * (xA2HqL0Xq + xA2HqL1Xq * LL + xA2HqL2Xq * LL * LL) / 2.0;

   if(f2fl == 1){
     hoppet::grid_conv xC2ZMNS2 = hoppet::grid_conv(Hoppet_grid, sf_C2ZMNS2);
     hoppet::grid_quant_2d xF2ZMNS2 = hoppet::grid_quant_2d(Hoppet_grid, 14);
     xF2ZMNS2 = 0.0;
     xF2ZMNS2[hflv + 6] = xC2ZMNS2 * Hoppet_subpdf_gluon_1[hflv + 6] * AlphaS2pi * AlphaS2pi;

     fsub = Hoppet_C2LO * Hoppet_subpdf_gluon_3
          + Hoppet_C2NLO * Hoppet_subpdf_gluon_2 * AlphaS2pi
          + xF2ZMNS2
          + Hoppet_C2LO * Hoppet_subpdf_quark_3
          + Hoppet_C2NLO * Hoppet_subpdf_quark_2 * AlphaS2pi;
   }
   else{
     hoppet::grid_conv xCLZMNS2 = hoppet::grid_conv(Hoppet_grid, sf_CLZMNS2);
     hoppet::grid_quant_2d xFLZMNS2 = hoppet::grid_quant_2d(Hoppet_grid, 14);
     xFLZMNS2 = 0.0;
     xFLZMNS2[hflv + 6] = xCLZMNS2 * Hoppet_subpdf_gluon_1[hflv + 6] * AlphaS2pi * AlphaS2pi;

     fsub = Hoppet_CLLO * Hoppet_subpdf_gluon_3
          + Hoppet_CLNLO * Hoppet_subpdf_gluon_2 * AlphaS2pi
          + xFLZMNS2
          + Hoppet_CLLO * Hoppet_subpdf_quark_3
          + Hoppet_CLNLO * Hoppet_subpdf_quark_2 * AlphaS2pi;
   }
 }
 else{
   Value = 0.0;
 }

 Value = fsub[hflv + 6].at_x(x);
#endif

 return Value;
}

double CalcDIS::GetSubtractionXg(int order1, int order2, int f2fl, int hflv, int ihadron, double x, double Q, double QMu, double MQ)
{
 if(!isDefineNNLOFunctions) DefineFunctions_nnlo();

 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 CloneHoppetSF();

 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 hoppet::grid_quant_2d Hoppet_subpdf = hoppet::grid_quant_2d(Hoppet_grid, 14);

 Hoppet_subpdf = 0.0;

 double LL = SFHQ_LL;

 if(order2 == 1){
   xA1Hg = hoppet::grid_conv(Hoppet_grid, sf_A1Hg);
   hoppet::grid_quant xA1HgL1Xg = xA1Hg * Hoppet_xgluon;
   Hoppet_subpdf[hflv + 6] = AlphaS2pi * xA1HgL1Xg * LL / 2.0;   
 }
 else if(order2 == 2){
   xA2HgL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL0);
   xA2HgL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL1);
   xA2HgL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL2);

   hoppet::grid_quant xA2HgL0Xg = xA2HgL0 * Hoppet_xgluon;
   hoppet::grid_quant xA2HgL1Xg = xA2HgL1 * Hoppet_xgluon;
   hoppet::grid_quant xA2HgL2Xg = xA2HgL2 * Hoppet_xgluon;

   Hoppet_subpdf[hflv + 6] = AlphaS2pi * AlphaS2pi * (xA2HgL0Xg + xA2HgL1Xg * LL + xA2HgL2Xg * LL * LL) / 2.0;
 }
 else if(order2 == 3){
   //xA3HgL0 = hoppet::grid_conv(Hoppet_grid, sf_A3HgL0);
   //xA3HgLL = hoppet::grid_conv(Hoppet_grid, sf_A3HgLL);

   //hoppet::grid_quant xA3HgL0Xg = xA3HgL0 * Hoppet_xgluon;
   //hoppet::grid_quant xA3HgLLXg = xA3HgLL * Hoppet_xgluon;

   //Hoppet_subpdf[hflv + 6] = (xA3HgL0Xg + xA3HgLLXg) / 2.0; // contains alphas

   hoppet::grid_conv xA3Hg = hoppet::grid_conv(Hoppet_grid, sf_A3Hg_ome);

   hoppet::grid_quant xA3HgXg = xA3Hg * Hoppet_xgluon;

   Hoppet_subpdf[hflv + 6] = xA3HgXg / 2.0; // contains alphas
 }

 hoppet::grid_quant_2d fsub;

 if(order1 == 0){
   if(f2fl == 1) fsub = Hoppet_C2LO * Hoppet_subpdf;
   else          fsub = Hoppet_CLLO * Hoppet_subpdf;
 }
 else if(order1 == 1){
   if(f2fl == 1) fsub = Hoppet_C2NLO * Hoppet_subpdf * AlphaS2pi;
   else          fsub = Hoppet_CLNLO * Hoppet_subpdf * AlphaS2pi;
 }
 else if(order1 == 2){
   if(f2fl == 1){
     hoppet::grid_conv xC2ZMNS2 = hoppet::grid_conv(Hoppet_grid, sf_C2ZMNS2);
     hoppet::grid_quant_2d xF2ZMNS2 = hoppet::grid_quant_2d(Hoppet_grid, 14);
     xF2ZMNS2 = 0.0;
     xF2ZMNS2[hflv + 6] = xC2ZMNS2 * Hoppet_subpdf[hflv + 6] * AlphaS2pi * AlphaS2pi;

     fsub = xF2ZMNS2;
   }
   else{
     hoppet::grid_conv xCLZMNS2 = hoppet::grid_conv(Hoppet_grid, sf_CLZMNS2);
     hoppet::grid_quant_2d xFLZMNS2 = hoppet::grid_quant_2d(Hoppet_grid, 14);
     xFLZMNS2 = 0.0;
     xFLZMNS2[hflv + 6] = xCLZMNS2 * Hoppet_subpdf[hflv + 6] * AlphaS2pi * AlphaS2pi;

     fsub = xFLZMNS2;
   }
 }

 if(order1 == 1 && order2 == 1){
   hoppet::grid_conv xC1A1 = hoppet::grid_conv(Hoppet_grid, sf_AnalyticC1A1);
   hoppet::grid_quant xC1A1Xg = xC1A1 * Hoppet_xgluon / 2.0 * AlphaS2pi * AlphaS2pi;

   fsub[hflv + 6] = xC1A1Xg;
 }

 Value = fsub[hflv + 6].at_x(x);
#endif

 return Value;
}

double CalcDIS::GetSubtractionXq(int order1, int order2, int f2fl, int hflv, int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 CloneHoppetSF();

 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 hoppet::grid_quant_2d Hoppet_subpdf = hoppet::grid_quant_2d(Hoppet_grid, 14);

 Hoppet_subpdf = 0.0;

 double LL = SFHQ_LL;

 if(order2 == 1){
   Value = 0.0;
   return Value;
 }
 if(order2 == 2){
   xA2HqL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL0);
   xA2HqL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL1);
   xA2HqL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL2);

   hoppet::grid_quant xA2HqL0Xq = xA2HqL0 * Hoppet_xquark;
   hoppet::grid_quant xA2HqL1Xq = xA2HqL1 * Hoppet_xquark;
   hoppet::grid_quant xA2HqL2Xq = xA2HqL2 * Hoppet_xquark;

   Hoppet_subpdf[hflv + 6] = AlphaS2pi * AlphaS2pi * (xA2HqL0Xq + xA2HqL1Xq * LL + xA2HqL2Xq * LL * LL) / 2.0;
 }
 else if(order2 == 3){
   //xA3HqL0 = hoppet::grid_conv(Hoppet_grid, sf_A3HqPSL0);
   //xA3HqLL = hoppet::grid_conv(Hoppet_grid, sf_A3HqPSLL);

   //hoppet::grid_quant xA3HqL0Xq = xA3HqL0 * Hoppet_xquark;
   //hoppet::grid_quant xA3HqLLXq = xA3HqLL * Hoppet_xquark;

   //Hoppet_subpdf[hflv + 6] = (xA3HqL0Xq + xA3HqLLXq) / 2.0; // contains alphas

   hoppet::grid_conv xA3Hq = hoppet::grid_conv(Hoppet_grid, sf_A3HqPS_ome);

   hoppet::grid_quant xA3HqXq = xA3Hq * Hoppet_xquark;

   Hoppet_subpdf[hflv + 6] = xA3HqXq / 2.0; // contains alphas
 }

 hoppet::grid_quant_2d fsub;

 if(order1 == 0){
   if(f2fl == 1) fsub = Hoppet_C2LO * Hoppet_subpdf;
   else          fsub = Hoppet_CLLO * Hoppet_subpdf;
 }
 else if(order1 == 1){
   if(f2fl == 1) fsub = Hoppet_C2NLO * Hoppet_subpdf * AlphaS2pi;
   else          fsub = Hoppet_CLNLO * Hoppet_subpdf * AlphaS2pi;
 }
 else if(order1 == 2){
   if(f2fl == 1) fsub = Hoppet_C2NNLO * Hoppet_subpdf * AlphaS2pi * AlphaS2pi;
   else          fsub = Hoppet_CLNNLO * Hoppet_subpdf * AlphaS2pi * AlphaS2pi;
 }

 Value = fsub[hflv + 6].at_x(x);
#endif

 return Value;
}

double CalcDIS::GetSubtractionPDF(int order1, int order2, int f2fl, int hflv, int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 CloneHoppetSF();

 double AlphaS = GetAlphaS(Q);
 double AlphaS2pi = AlphaS / 2.0 / Pi;

 FillHoppetPDFTable(ihadron, Q);

 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), AlphaS2pi);

 hoppet::grid_quant_2d Hoppet_subpdf_gluon_1 = hoppet::grid_quant_2d(Hoppet_grid, 14);
 hoppet::grid_quant_2d Hoppet_subpdf_gluon_2 = hoppet::grid_quant_2d(Hoppet_grid, 14);
 hoppet::grid_quant_2d Hoppet_subpdf_gluon_3 = hoppet::grid_quant_2d(Hoppet_grid, 14);

 hoppet::grid_quant_2d Hoppet_subpdf_quark_2 = hoppet::grid_quant_2d(Hoppet_grid, 14);
 hoppet::grid_quant_2d Hoppet_subpdf_quark_3 = hoppet::grid_quant_2d(Hoppet_grid, 14);

 Hoppet_subpdf_gluon_1 = 0.0;
 Hoppet_subpdf_gluon_2 = 0.0;
 Hoppet_subpdf_gluon_3 = 0.0;
 Hoppet_subpdf_quark_2 = 0.0;
 Hoppet_subpdf_quark_3 = 0.0;

 hoppet::grid_quant_2d fsub = hoppet::grid_quant_2d(Hoppet_grid, 14);
 fsub = 0.0;

 double LL = SFHQ_LL;

 if(order2 == 2){
   // 12 gluon
   xA2HgL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL0);
   xA2HgL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL1);
   xA2HgL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL2);

   hoppet::grid_quant xA2HgL0Xg = xA2HgL0 * Hoppet_xgluon;
   hoppet::grid_quant xA2HgL1Xg = xA2HgL1 * Hoppet_xgluon;
   hoppet::grid_quant xA2HgL2Xg = xA2HgL2 * Hoppet_xgluon;

   Hoppet_subpdf_gluon_2[hflv + 6] = (xA2HgL0Xg + xA2HgL1Xg * LL + xA2HgL2Xg * LL * LL) * AlphaS2pi * AlphaS2pi / 2.0;

   // 21 gluon
   xA1Hg = hoppet::grid_conv(Hoppet_grid, sf_A1Hg);

   hoppet::grid_quant xA1HgL1Xg = xA1Hg * Hoppet_xgluon;

   Hoppet_subpdf_gluon_1[hflv + 6] = AlphaS2pi * xA1HgL1Xg * LL / 2.0;

   // 12 quark
   xA2HqL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL0);
   xA2HqL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL1);
   xA2HqL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL2);

   hoppet::grid_quant xA2HqL0Xq = xA2HqL0 * Hoppet_xquark;
   hoppet::grid_quant xA2HqL1Xq = xA2HqL1 * Hoppet_xquark;
   hoppet::grid_quant xA2HqL2Xq = xA2HqL2 * Hoppet_xquark;

   Hoppet_subpdf_quark_2[hflv + 6] = AlphaS2pi * AlphaS2pi * (xA2HqL0Xq + xA2HqL1Xq * LL + xA2HqL2Xq * LL * LL) / 2.0;

   if(f2fl == 1){
     if(order1 == 0){
       fsub = Hoppet_C2LO * Hoppet_subpdf_gluon_2
            + Hoppet_C2LO * Hoppet_subpdf_gluon_1
            + Hoppet_C2LO * Hoppet_subpdf_quark_2;
     }
     else if(order1 == 1){
       fsub = Hoppet_C2NLO * Hoppet_subpdf_gluon_2
            + Hoppet_C2NLO * Hoppet_subpdf_gluon_1
            + Hoppet_C2NLO * Hoppet_subpdf_quark_2;
     }
     else if(order1 == 2){
       fsub = Hoppet_C2NNLO * Hoppet_subpdf_gluon_2
            + Hoppet_C2NNLO * Hoppet_subpdf_gluon_1
            + Hoppet_C2NNLO * Hoppet_subpdf_quark_2;
     }
   }
   else{

   }
 }
 else if(order2 == 3){
   // 03 gluon
   xA3HgL0 = hoppet::grid_conv(Hoppet_grid, sf_A3HgL0);
   xA3HgLL = hoppet::grid_conv(Hoppet_grid, sf_A3HgLL);

   hoppet::grid_quant xA3HgL0Xg = xA3HgL0 * Hoppet_xgluon;
   hoppet::grid_quant xA3HgLLXg = xA3HgLL * Hoppet_xgluon;

   Hoppet_subpdf_gluon_3[hflv + 6] = (xA3HgL0Xg + xA3HgLLXg) / 2.0; // contains alphas

   // 12 gluon
   xA2HgL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL0);
   xA2HgL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL1);
   xA2HgL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HgL2);

   hoppet::grid_quant xA2HgL0Xg = xA2HgL0 * Hoppet_xgluon;
   hoppet::grid_quant xA2HgL1Xg = xA2HgL1 * Hoppet_xgluon;
   hoppet::grid_quant xA2HgL2Xg = xA2HgL2 * Hoppet_xgluon;

   Hoppet_subpdf_gluon_2[hflv + 6] = (xA2HgL0Xg + xA2HgL1Xg * LL + xA2HgL2Xg * LL * LL) * AlphaS2pi * AlphaS2pi / 2.0;

   // 21 gluon
   xA1Hg = hoppet::grid_conv(Hoppet_grid, sf_A1Hg);

   hoppet::grid_quant xA1HgL1Xg = xA1Hg * Hoppet_xgluon;

   Hoppet_subpdf_gluon_1[hflv + 6] = AlphaS2pi * xA1HgL1Xg * LL / 2.0;

   // 03 quark
   xA3HqL0 = hoppet::grid_conv(Hoppet_grid, sf_A3HqPSL0);
   xA3HqLL = hoppet::grid_conv(Hoppet_grid, sf_A3HqPSLL);

   hoppet::grid_quant xA3HqL0Xq = xA3HqL0 * Hoppet_xquark;
   hoppet::grid_quant xA3HqLLXq = xA3HqLL * Hoppet_xquark;

   Hoppet_subpdf_quark_3[hflv + 6] = (xA3HqL0Xq + xA3HqLLXq) / 2.0; // contains alphas

   // 12 quark
   xA2HqL0 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL0);
   xA2HqL1 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL1);
   xA2HqL2 = hoppet::grid_conv(Hoppet_grid, sf_A2HqPSL2);

   hoppet::grid_quant xA2HqL0Xq = xA2HqL0 * Hoppet_xquark;
   hoppet::grid_quant xA2HqL1Xq = xA2HqL1 * Hoppet_xquark;
   hoppet::grid_quant xA2HqL2Xq = xA2HqL2 * Hoppet_xquark;

   Hoppet_subpdf_quark_2[hflv + 6] = AlphaS2pi * AlphaS2pi * (xA2HqL0Xq + xA2HqL1Xq * LL + xA2HqL2Xq * LL * LL) / 2.0;

   if(f2fl == 1){
     if(order1 == 0){
       fsub = Hoppet_C2LO * Hoppet_subpdf_gluon_3
            + Hoppet_C2LO * Hoppet_subpdf_gluon_2
            + Hoppet_C2LO * Hoppet_subpdf_gluon_1
            + Hoppet_C2LO * Hoppet_subpdf_quark_3
            + Hoppet_C2LO * Hoppet_subpdf_quark_2;
     }
     else if(order1 == 1){
       fsub = Hoppet_C2NLO * Hoppet_subpdf_gluon_3
            + Hoppet_C2NLO * Hoppet_subpdf_gluon_2
            + Hoppet_C2NLO * Hoppet_subpdf_gluon_1
            + Hoppet_C2NLO * Hoppet_subpdf_quark_3
            + Hoppet_C2NLO * Hoppet_subpdf_quark_2;
     }
     else if(order1 == 2){
       fsub = Hoppet_C2NNLO * Hoppet_subpdf_gluon_3
            + Hoppet_C2NNLO * Hoppet_subpdf_gluon_2
            + Hoppet_C2NNLO * Hoppet_subpdf_gluon_1
            + Hoppet_C2NNLO * Hoppet_subpdf_quark_3
            + Hoppet_C2NNLO * Hoppet_subpdf_quark_2;
     }
   }
   else{
     if(order1 == 0){
       fsub = Hoppet_CLLO * Hoppet_subpdf_gluon_3
            + Hoppet_CLLO * Hoppet_subpdf_gluon_2
            + Hoppet_CLLO * Hoppet_subpdf_gluon_1
            + Hoppet_CLLO * Hoppet_subpdf_quark_3
            + Hoppet_CLLO * Hoppet_subpdf_quark_2;
     }
     else if(order1 == 1){
       fsub = Hoppet_CLNLO * Hoppet_subpdf_gluon_3
            + Hoppet_CLNLO * Hoppet_subpdf_gluon_2
            + Hoppet_CLNLO * Hoppet_subpdf_gluon_1
            + Hoppet_CLNLO * Hoppet_subpdf_quark_3
            + Hoppet_CLNLO * Hoppet_subpdf_quark_2;
     }
     else if(order1 == 2){
       fsub = Hoppet_CLNNLO * Hoppet_subpdf_gluon_3
            + Hoppet_CLNNLO * Hoppet_subpdf_gluon_2
            + Hoppet_CLNNLO * Hoppet_subpdf_gluon_1
            + Hoppet_CLNNLO * Hoppet_subpdf_quark_3
            + Hoppet_CLNNLO * Hoppet_subpdf_quark_2;
     }
   }
 }
 else{
   Value = 0.0;
 }

 Value = fsub[hflv + 6].at_x(x);
#endif

 return Value;
}

