#ifndef WZPol_FillHist_cxx
#define WZPol_FillHist_cxx

#include <iostream>
#include "WZPolarization/loopWZPolarization.h"

using namespace std;

void loopWZPolarization::FillHist(EventWZPolarization ProcessEvent)
{
   int MCType = ProcessEvent.MCType;

   bool isData = false;
   bool isSignal = false;
   bool isNLOSample = false;
   bool isWZ = false;

   if(MCType == -1) isData = true;
   if(MCType == 364253) isNLOSample = true;
   if(MCType == 500290 || MCType == 500291 || MCType == 500292 || MCType == 500293 || MCType == 500294 || MCType == 500295 || MCType == 500296 || MCType == 500297) isSignal = true;
   if(MCType == 501793 || MCType == 501794 || MCType == 501795 || MCType == 501796 || MCType == 501797 || MCType == 501798 || MCType == 501799 || MCType == 501800) isSignal = true;
   if(MCType == 507019 || MCType == 507020 || MCType == 507021 || MCType == 507022 || MCType == 507023 || MCType == 507024 || MCType == 507025 || MCType == 507026) isSignal = true;
   if(MCType == 507027 || MCType == 507028 || MCType == 507029 || MCType == 507030 || MCType == 507031 || MCType == 507032 || MCType == 507033 || MCType == 507034) isSignal = true;

   if(isNLOSample || isSignal) isWZ = true;


   ProcessEvent.WeightNormalized = ProcessEvent.WeightNormalizedNoKFactor;
   ProcessEvent.TotalWeight = ProcessEvent.TotalWeightNoKFactor;
   ProcessEvent.passWZInclusive = ProcessEvent.passHardWZInclusive;
   ProcessEvent.passWZInclusiveLoose = ProcessEvent.passHardWZInclusiveLoose;

   ProcessEvent.passWZInclusive = ProcessEvent.passWZInclusive * (ProcessEvent.Lep3Ambiguity <= 0);
   ProcessEvent.passWCondition = ProcessEvent.passWCondition * (ProcessEvent.Lep3Ambiguity <= 0);
   ProcessEvent.passTTT = ProcessEvent.passTTT * (ProcessEvent.Lep3Ambiguity <= 0);
   ProcessEvent.passTLT = ProcessEvent.passTLT * (ProcessEvent.Lep3Ambiguity <= 0);
   ProcessEvent.passLTT = ProcessEvent.passLTT * (ProcessEvent.Lep3Ambiguity <= 0);
   ProcessEvent.passLLT = ProcessEvent.passLLT * (ProcessEvent.Lep3Ambiguity <= 0);

   ProcessEvent.passTopEnrichCR = ProcessEvent.passWZInclusiveLoose * (ProcessEvent.NBjets == 0);
   ProcessEvent.passZjetEnrichCR = ProcessEvent.passWZInclusiveLoose * (ProcessEvent.DecayChannel == 1 || ProcessEvent.DecayChannel == 4);

   ProcessEvent.passSignalRegion = (ProcessEvent.Pt_WZ < 70) && (ProcessEvent.Pt_Z > 200);
   ProcessEvent.passHighPtWZCR = (ProcessEvent.Pt_WZ > 70) && (ProcessEvent.Pt_Z > 200);


//   ProcessEvent.passWZInclusive = ProcessEvent.passWZInclusive * (ProcessEvent.Lep1Ambiguity <= 0) * (ProcessEvent.Lep2Ambiguity <= 0) * (ProcessEvent.Lep3Ambiguity <= 0);
//   ProcessEvent.passWZInclusiveLoose = ProcessEvent.passWZInclusiveLoose * (ProcessEvent.Lep1Ambiguity <= 0) * (ProcessEvent.Lep2Ambiguity <= 0) * (ProcessEvent.Lep3Ambiguity <= 0);
//   ProcessEvent.passZFakeElCR = ProcessEvent.passZFakeElCR * (ProcessEvent.Lep1Ambiguity <= 0) * (ProcessEvent.Lep2Ambiguity <= 0) * (ProcessEvent.Lep3Ambiguity <= 0);
//   ProcessEvent.passZFakeMuCR = ProcessEvent.passZFakeMuCR * (ProcessEvent.Lep1Ambiguity <= 0) * (ProcessEvent.Lep2Ambiguity <= 0) * (ProcessEvent.Lep3Ambiguity <= 0);


//   ProcessEvent.passWZInclusive = ProcessEvent.passWZInclusive * (ProcessEvent.Lep1Pt > 20) * (ProcessEvent.Lep2Pt > 20);
//   ProcessEvent.passWZInclusiveLoose = ProcessEvent.passWZInclusiveLoose * (ProcessEvent.Lep1Pt > 20) * (ProcessEvent.Lep2Pt > 20);

//   ProcessEvent.passWZInclusive = ProcessEvent.passTTT;
//   ProcessEvent.passWZInclusiveLoose = 1;
//   ProcessEvent.passWZInclusive = ProcessEvent.passHardWZInclusive * (fabs(ProcessEvent.DeltaPhiZBosonLepW) > 2.8);
//   ProcessEvent.passWZInclusiveLoose = ProcessEvent.passHardWZInclusiveLoose * (fabs(ProcessEvent.DeltaPhiZBosonLepW) > 2.8);

//   ProcessEvent.passWZInclusive = ProcessEvent.passHardWZInclusive * ProcessEvent.Met > 30;
//   ProcessEvent.passWZInclusiveLoose = ProcessEvent.passHardWZInclusiveLoose * ProcessEvent.Met > 30;

/*   ProcessEvent.passWZInclusiveLoose = (ProcessEvent.passWZInclusiveNoMET)
                                    && (ProcessEvent.Lep3Pt > 20)
                                    && (ProcessEvent.passDeltaR);

   ProcessEvent.passWZInclusive = ProcessEvent.passWZInclusiveLoose * ProcessEvent.passTTT;
*/
/*   ProcessEvent.passZFakeElCR = (ProcessEvent.passWZInclusiveNoMET)
                             && (ProcessEvent.Lep3Pt > 20)
                             && (ProcessEvent.passIPID1 && ProcessEvent.passZCondition1 && ProcessEvent.passIPID2 && ProcessEvent.passZCondition2)
                             && (ProcessEvent.passIPID3)
                             && (ProcessEvent.Mt_W < 30)
                             && (ProcessEvent.DecayChannel == 2);

   ProcessEvent.passZFakeMuCR = (ProcessEvent.passWZInclusiveNoMET)
                             && (ProcessEvent.Lep3Pt > 20)
                             && (ProcessEvent.passIPID1 && ProcessEvent.passZCondition1 && ProcessEvent.passIPID2 && ProcessEvent.passZCondition2)
                             && (ProcessEvent.passIPID3 && ProcessEvent.passMediumID3)
                             && (ProcessEvent.Mt_W < 30)
                             && (ProcessEvent.DecayChannel == 3);

*/

//global selection cut should be applied after fake rate measurement.
/*   isCut = false;
   for(int icut = 0; icut < CutInfo.size(); icut++){
     CutForWZPolarization(CutInfo.at(icut), CutLeft.at(icut), CutRight.at(icut), isCut);
   }
   if(isCut) return;
*/

//   if(ProcessEvent.isTauEvent) return;

//   if(isSignal && ProcessEvent.Njets == 0) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * 1.03;
//   if(isSignal && ProcessEvent.Njets == 1) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * 0.84;
//   if(isSignal && ProcessEvent.Njets == 2) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * 0.93;
//   if(isSignal && ProcessEvent.Njets >= 3) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * 1.42;

//   if(isNLOSample && ProcessEvent.Njets >= 2) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * 0.83;

/////////////////////////////////////////////////////////////////////////

    //////////////////////////
    //  Test for all tight  //
    //////////////////////////
    /*
    ProcessEvent.passTTT = ProcessEvent.passWCondition1 * ProcessEvent.passWCondition2 * ProcessEvent.passWCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
    ProcessEvent.passTTL = ProcessEvent.passWCondition1 * ProcessEvent.passWCondition2 * (!ProcessEvent.passWCondition3) * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
    ProcessEvent.passTLT = ProcessEvent.passWCondition1 * (!ProcessEvent.passWCondition2) * ProcessEvent.passWCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
    ProcessEvent.passLTT = (!ProcessEvent.passWCondition1) * ProcessEvent.passWCondition2 * ProcessEvent.passWCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
    ProcessEvent.passTLL = ProcessEvent.passWCondition1 * (!ProcessEvent.passWCondition2) * (!ProcessEvent.passWCondition3) * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
    ProcessEvent.passLTL = (!ProcessEvent.passWCondition1) * ProcessEvent.passWCondition2 * (!ProcessEvent.passWCondition3) * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
    ProcessEvent.passLLT = (!ProcessEvent.passWCondition1) * (!ProcessEvent.passWCondition2) * ProcessEvent.passWCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;

    ProcessEvent.Lep1WeightZ = ProcessEvent.Lep1WeightW;
    ProcessEvent.Lep2WeightZ = ProcessEvent.Lep2WeightW;
    ProcessEvent.Lep3WeightZ = ProcessEvent.Lep3WeightW;
    ProcessEvent.TotalWeight = ProcessEvent.WeightNormalized * ProcessEvent.Lep1WeightZ * ProcessEvent.Lep2WeightZ * ProcessEvent.Lep3WeightW;

    ProcessEvent.passZCondition = ProcessEvent.passWCondition;
    ProcessEvent.passWZInclusive = ProcessEvent.passWZInclusiveLoose * ProcessEvent.passTTT;
    */

    //////////////////////////////////////////////////
    //  Test for Z muon loose isolation + tight ID  //
    //////////////////////////////////////////////////

    /*
    if(fabs(ProcessEvent.Lep1Flavor) == 13) ProcessEvent.passZCondition1 = ProcessEvent.passZCondition1 * ProcessEvent.passTightID1;
    if(fabs(ProcessEvent.Lep2Flavor) == 13) ProcessEvent.passZCondition2 = ProcessEvent.passZCondition2 * ProcessEvent.passTightID2;
    if(fabs(ProcessEvent.Lep3Flavor) == 13) ProcessEvent.passZCondition3 = ProcessEvent.passZCondition3 * ProcessEvent.passTightID3;

    ProcessEvent.passTTT = ProcessEvent.passZCondition1 * ProcessEvent.passZCondition2 * ProcessEvent.passWCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
    ProcessEvent.passTTL = ProcessEvent.passZCondition1 * ProcessEvent.passZCondition2 * (!ProcessEvent.passWCondition3) * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
    ProcessEvent.passTLT = ProcessEvent.passZCondition1 * (!ProcessEvent.passZCondition2) * ProcessEvent.passWCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
    ProcessEvent.passLTT = (!ProcessEvent.passZCondition1) * ProcessEvent.passZCondition2 * ProcessEvent.passWCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
    ProcessEvent.passTLL = ProcessEvent.passZCondition1 * (!ProcessEvent.passZCondition2) * (!ProcessEvent.passWCondition3) * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
    ProcessEvent.passLTL = (!ProcessEvent.passZCondition1) * ProcessEvent.passZCondition2 * (!ProcessEvent.passWCondition3) * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
    ProcessEvent.passLLT = (!ProcessEvent.passZCondition1) * (!ProcessEvent.passZCondition2) * ProcessEvent.passWCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;

    if(fabs(ProcessEvent.Lep1Flavor) == 13) ProcessEvent.Lep1WeightZ = ProcessEvent.Lep1TightIDWeight * ProcessEvent.Lep1MediumIsoWeight;
    if(fabs(ProcessEvent.Lep2Flavor) == 13) ProcessEvent.Lep2WeightZ = ProcessEvent.Lep2TightIDWeight * ProcessEvent.Lep2MediumIsoWeight;
    if(fabs(ProcessEvent.Lep3Flavor) == 13) ProcessEvent.Lep3WeightZ = ProcessEvent.Lep3TightIDWeight * ProcessEvent.Lep3MediumIsoWeight;
    ProcessEvent.TotalWeight = ProcessEvent.WeightNormalized * ProcessEvent.Lep1WeightZ * ProcessEvent.Lep2WeightZ * ProcessEvent.Lep3WeightW;

    if(fabs(ProcessEvent.Lep3Flavor) == 13) ProcessEvent.passZCondition = ProcessEvent.passZCondition * ProcessEvent.passTightID3;

    ProcessEvent.passWZInclusive = ProcessEvent.passWZInclusiveLoose * ProcessEvent.passTTT;
    */

//////////////////////////////////////////////////////////////////////////


   if(doRunPDFAndQCDUnc && isSignal){
     if(ErrorType == "PDF") ProcessEvent.TotalWeight = ProcessEvent.PDFWeights->at(ErrorSet);
     if(ErrorType == "QCD") ProcessEvent.TotalWeight = ProcessEvent.QCDWeights->at(ErrorSet);
   }


///////////////////////////////////////////////////////////////////////////

  ///////////////
  //  pre-run  //
  ///////////////

///////////////////////////////////////////////////////////////////////////


   if(isRunReweightingFactor){
     if(!isHaveReweightingFactor) myhists->Pt_WZ->Fill(iThread, ProcessEvent.Pt_WZ, ProcessEvent.TotalWeight, ProcessEvent);
   }

   if(doFakeRate){
     TotalWeight = ProcessEvent.TotalWeight;
     double TotalWeightZZZ = ProcessEvent.WeightNormalizedNoKFactor * ProcessEvent.Lep1WeightZ * ProcessEvent.Lep2WeightZ * ProcessEvent.Lep3WeightZ;
     double TotalWeightZZW = ProcessEvent.WeightNormalizedNoKFactor * ProcessEvent.Lep1WeightZ * ProcessEvent.Lep2WeightZ * ProcessEvent.Lep3WeightW;
     double TotalWeightZZ = ProcessEvent.WeightNormalizedNoKFactor * ProcessEvent.Lep1WeightZ * ProcessEvent.Lep2WeightZ;
     double TotalWeightLoose = ProcessEvent.WeightNormalizedNoKFactor;
     double TotalWeightZ1 = ProcessEvent.WeightNormalizedNoKFactor * ProcessEvent.Lep1WeightZ;
     double TotalWeightW1 = ProcessEvent.WeightNormalizedNoKFactor * ProcessEvent.Lep1WeightW;
     double TotalWeightZ2 = ProcessEvent.WeightNormalizedNoKFactor * ProcessEvent.Lep2WeightZ;
     double TotalWeightW2 = ProcessEvent.WeightNormalizedNoKFactor * ProcessEvent.Lep2WeightW;
     double TotalWeightZ3 = ProcessEvent.WeightNormalizedNoKFactor * ProcessEvent.Lep3WeightZ;
     double TotalWeightW3 = ProcessEvent.WeightNormalizedNoKFactor * ProcessEvent.Lep3WeightW;
     double TotalWeightZ1W3 = ProcessEvent.WeightNormalizedNoKFactor * ProcessEvent.Lep1WeightZ * ProcessEvent.Lep3WeightW;

     //NLO/LO KFactor
     myhists->PolarizedYield_bkg->HistPtr(iThread - 1)->Fill((double)ProcessEvent.DecayChannel, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive);
     myhists->PolarizedYield_ZZCR_bkg->HistPtr(iThread - 1)->Fill((double)ProcessEvent.DecayChannel, ProcessEvent.TotalWeight * ProcessEvent.passZZCR);
     myhists->PolarizedYield_HighPtZCR_bkg->HistPtr(iThread - 1)->Fill((double)ProcessEvent.DecayChannel, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200));
     myhists->PolarizedYield_Signal_bkg->HistPtr(iThread - 1)->Fill((double)ProcessEvent.DecayChannel, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 100) * (ProcessEvent.Pt_WZ < 70));
     myhists->PolarizedYield_SignalPtWZ_bkg->HistPtr(iThread - 1)->Fill((double)ProcessEvent.DecayChannel, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200) * (ProcessEvent.Pt_WZ < 70));
     myhists->PolarizedYield_HighPtWZCR_bkg->HistPtr(iThread - 1)->Fill((double)ProcessEvent.DecayChannel, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ > 70));
     myhists->PolarizedYield_LowPtWZCR_bkg->HistPtr(iThread - 1)->Fill((double)ProcessEvent.DecayChannel, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70));
     myhists->PolarizedYield_HighR21CR_bkg->HistPtr(iThread - 1)->Fill((double)ProcessEvent.DecayChannel, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive * (ProcessEvent.R21 > 0.8));
     myhists->PolarizedYield_LowR21CR_bkg->HistPtr(iThread - 1)->Fill((double)ProcessEvent.DecayChannel, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive * (ProcessEvent.R21 < 0.8));




     //Fake rate correction
     int unpassTruthMatch = (ProcessEvent.passTruthMatch1 && ProcessEvent.passTruthMatch2 && !ProcessEvent.passTruthMatch3);

     if(ProcessEvent.passWCondition){
       if(MCType == 361106 || MCType == 361107 || MCType == 361108){
         if(ProcessEvent.Mt_W > 30){
           if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_ZFakeEl_LargeMtW_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * unpassTruthMatch);
           if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_ZFakeMu_LargeMtW_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * unpassTruthMatch);
         }
         if(ProcessEvent.Mt_W < 30){
           if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_ZFakeEl_LowMtW_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * unpassTruthMatch);
           if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_ZFakeMu_LowMtW_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * unpassTruthMatch);
         }
       }
     }
     else{
       if(MCType == 361106 || MCType == 361107 || MCType == 361108){
         if(ProcessEvent.Mt_W > 30){
           if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_ZFakeEl_LargeMtW_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * unpassTruthMatch);
           if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_ZFakeMu_LargeMtW_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * unpassTruthMatch);
         }
         if(ProcessEvent.Mt_W < 30){
           if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_ZFakeEl_LowMtW_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * unpassTruthMatch);
           if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_ZFakeMu_LowMtW_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * unpassTruthMatch);
         }
       }
     }

     //Real Efficiency
     if(fabs(ProcessEvent.Lep1Flavor) == 11) myhists->Lep3Pt_RealEl_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep1Pt, TotalWeightLoose * ProcessEvent.passTruthMatch1);
     if(fabs(ProcessEvent.Lep1Flavor) == 13) myhists->Lep3Pt_RealMu_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep1Pt, TotalWeightLoose * ProcessEvent.passTruthMatch1);
     if(fabs(ProcessEvent.Lep2Flavor) == 11) myhists->Lep3Pt_RealEl_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightLoose * ProcessEvent.passTruthMatch2);
     if(fabs(ProcessEvent.Lep2Flavor) == 13) myhists->Lep3Pt_RealMu_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightLoose * ProcessEvent.passTruthMatch2);
     if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_RealEl_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightLoose * ProcessEvent.passTruthMatch3);
     if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_RealMu_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightLoose * ProcessEvent.passTruthMatch3);
     if(ProcessEvent.passZCondition1){
       if(fabs(ProcessEvent.Lep1Flavor) == 11) myhists->Lep3Pt_RealEl_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep1Pt, TotalWeightZ1 * ProcessEvent.passTruthMatch1);
       if(fabs(ProcessEvent.Lep1Flavor) == 13) myhists->Lep3Pt_RealMu_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep1Pt, TotalWeightZ1 * ProcessEvent.passTruthMatch1);
     }
     else{
       if(fabs(ProcessEvent.Lep1Flavor) == 11) myhists->Lep3Pt_RealEl_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep1Pt, TotalWeightZ1 * ProcessEvent.passTruthMatch1);
       if(fabs(ProcessEvent.Lep1Flavor) == 13) myhists->Lep3Pt_RealMu_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep1Pt, TotalWeightZ1 * ProcessEvent.passTruthMatch1);
     }

     if(ProcessEvent.passZCondition2){
       if(fabs(ProcessEvent.Lep2Flavor) == 11) myhists->Lep3Pt_RealEl_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightZ2 * ProcessEvent.passTruthMatch2);
       if(fabs(ProcessEvent.Lep2Flavor) == 13) myhists->Lep3Pt_RealMu_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightZ2 * ProcessEvent.passTruthMatch2);
     }
     else{
       if(fabs(ProcessEvent.Lep2Flavor) == 11) myhists->Lep3Pt_RealEl_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightZ2 * ProcessEvent.passTruthMatch2);
       if(fabs(ProcessEvent.Lep2Flavor) == 13) myhists->Lep3Pt_RealMu_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightZ2 * ProcessEvent.passTruthMatch2);
     }

     if(ProcessEvent.passZCondition3){
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_RealEl_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZ3 * ProcessEvent.passTruthMatch3);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_RealMu_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZ3 * ProcessEvent.passTruthMatch3);
     }
     else{
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_RealEl_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZ3 * ProcessEvent.passTruthMatch3);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_RealMu_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZ3 * ProcessEvent.passTruthMatch3);
     }

     if(ProcessEvent.passWCondition1){
       if(fabs(ProcessEvent.Lep1Flavor) == 11) myhists->Lep3Pt_RealEl_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep1Pt, TotalWeightW1 * ProcessEvent.passTruthMatch1);
       if(fabs(ProcessEvent.Lep1Flavor) == 13) myhists->Lep3Pt_RealMu_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep1Pt, TotalWeightW1 * ProcessEvent.passTruthMatch1);
     }
     else{
       if(fabs(ProcessEvent.Lep1Flavor) == 11) myhists->Lep3Pt_RealEl_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep1Pt, TotalWeightW1 * ProcessEvent.passTruthMatch1);
       if(fabs(ProcessEvent.Lep1Flavor) == 13) myhists->Lep3Pt_RealMu_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep1Pt, TotalWeightW1 * ProcessEvent.passTruthMatch1);
     }
       
     if(ProcessEvent.passWCondition2){
       if(fabs(ProcessEvent.Lep2Flavor) == 11) myhists->Lep3Pt_RealEl_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightW2 * ProcessEvent.passTruthMatch2);
       if(fabs(ProcessEvent.Lep2Flavor) == 13) myhists->Lep3Pt_RealMu_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightW2 * ProcessEvent.passTruthMatch2);
     }
     else{
       if(fabs(ProcessEvent.Lep2Flavor) == 11) myhists->Lep3Pt_RealEl_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightW2 * ProcessEvent.passTruthMatch2);
       if(fabs(ProcessEvent.Lep2Flavor) == 13) myhists->Lep3Pt_RealMu_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightW2 * ProcessEvent.passTruthMatch2);
     }
       
     if(ProcessEvent.passWCondition3){
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_RealEl_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightW3 * ProcessEvent.passTruthMatch3);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_RealMu_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightW3 * ProcessEvent.passTruthMatch3);
     }
     else{
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_RealEl_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightW3 * ProcessEvent.passTruthMatch3);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_RealMu_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightW3 * ProcessEvent.passTruthMatch3);
     }


     //Fake Rate and Fake Efficiency
     if(BkgShortName == "BkgWZQCD" || BkgShortName == "BkgWZEW" || BkgShortName == "BkgZZ" || BkgShortName == "BkgVVV" || BkgShortName == "BkgttbarV"){
       TotalWeight = TotalWeight * (-1);
       TotalWeightZZZ = TotalWeightZZZ * (-1);
       TotalWeightZZW = TotalWeightZZW * (-1);
       TotalWeightZZ = TotalWeightZZ * (-1);
     }
     else if(isData){
       TotalWeight = TotalWeight;
       TotalWeightZZZ = TotalWeightZZZ;
       TotalWeightZZW = TotalWeightZZW;
       TotalWeightZZ = TotalWeightZZ;
     }
     else{
       TotalWeight = 0.0;
       TotalWeightZZZ = 0.0;
       TotalWeightZZW = 0.0;
       TotalWeightZZ = 0.0;
     }

/*     if(ProcessEvent.passWZInclusive && ProcessEvent.passTTT && !ProcessEvent.passTruthMatch1 && !ProcessEvent.passTruthMatch2 && !ProcessEvent.passTruthMatch3){
//     if(ProcessEvent.passWZInclusive && ProcessEvent.passTTT){
       nFFF++;
       cout<<"No."<<nFFF<<" Reco: Flavor = "<<ProcessEvent.Lep1Flavor<<" Lep1Pt = "<<ProcessEvent.Lep1Pt<<" Lep1Eta = "<<ProcessEvent.Lep1Eta<<" Lep1Phi = "<<ProcessEvent.Lep1Phi<<endl;
       cout<<"No."<<nFFF<<" Truth: Flavor = "<<ProcessEvent.TruthLep1Flavor<<" Lep1Pt = "<<ProcessEvent.TruthLep1Pt<<" Lep1Eta = "<<ProcessEvent.TruthLep1Eta<<" Lep1Phi = "<<ProcessEvent.TruthLep1Phi<<endl;
       cout<<"No."<<nFFF<<" Reco: Flavor = "<<ProcessEvent.Lep2Flavor<<" Lep2Pt = "<<ProcessEvent.Lep2Pt<<" Lep2Eta = "<<ProcessEvent.Lep2Eta<<" Lep2Phi = "<<ProcessEvent.Lep2Phi<<endl;
       cout<<"No."<<nFFF<<" Truth: Flavor = "<<ProcessEvent.TruthLep2Flavor<<" Lep2Pt = "<<ProcessEvent.TruthLep2Pt<<" Lep2Eta = "<<ProcessEvent.TruthLep2Eta<<" Lep2Phi = "<<ProcessEvent.TruthLep2Phi<<endl;
       cout<<"No."<<nFFF<<" Reco: Flavor = "<<ProcessEvent.Lep3Flavor<<" Lep3Pt = "<<ProcessEvent.Lep3Pt<<" Lep3Eta = "<<ProcessEvent.Lep3Eta<<" Lep3Phi = "<<ProcessEvent.Lep3Phi<<endl;
       cout<<"No."<<nFFF<<" Truth: Flavor = "<<ProcessEvent.TruthLep3Flavor<<" Lep3Pt = "<<ProcessEvent.TruthLep3Pt<<" Lep3Eta = "<<ProcessEvent.TruthLep3Eta<<" Lep3Phi = "<<ProcessEvent.TruthLep3Phi<<endl;
     }
*/
//////////////////////////////////////////////////////////////////////
/*
       ////////////////////////
       //  for closure test  //
       ////////////////////////

//     int unpassTruthMatch = ProcessEvent.passWZInclusiveLoose * (ProcessEvent.passZCondition1 * ProcessEvent.passIPID1 * ProcessEvent.passZCondition2 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3) * (ProcessEvent.passTruthMatch1 && ProcessEvent.passTruthMatch2 && !ProcessEvent.passTruthMatch3);
//     int unpassTruthMatch2 = ProcessEvent.passWZInclusiveLoose * (ProcessEvent.passZCondition1 * ProcessEvent.passIPID1 * ProcessEvent.passWCondition3 * ProcessEvent.passIPID3 * ProcessEvent.passIPID2) * (ProcessEvent.passTruthMatch1 && !ProcessEvent.passTruthMatch2 && ProcessEvent.passTruthMatch3);

//     int passT1T2 = ProcessEvent.passZCondition1 * ProcessEvent.passIPID1 * ProcessEvent.passZCondition2 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
//     int passT1T3 = ProcessEvent.passZCondition1 * ProcessEvent.passIPID1 * ProcessEvent.passZCondition3 * ProcessEvent.passIPID3 * ProcessEvent.passIPID2;

     int passT1T2 = ProcessEvent.passZCondition1 * ProcessEvent.passIPID1 * ProcessEvent.passZCondition2 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
     int passT1T3 = ProcessEvent.passZCondition1 * ProcessEvent.passIPID1 * ProcessEvent.passZCondition3 * ProcessEvent.passIPID3 * ProcessEvent.passIPID2;

//     int unpassTruthMatch = (ProcessEvent.passTruthMatch1 && ProcessEvent.passTruthMatch2 && !ProcessEvent.passTruthMatch3);
     int unpassTruthMatch2 = (ProcessEvent.passTruthMatch1 && !ProcessEvent.passTruthMatch2 && ProcessEvent.passTruthMatch3);

     unpassTruthMatch = unpassTruthMatch * passT1T2;
     unpassTruthMatch2 = unpassTruthMatch2 * passT1T3;

//     unpassTruthMatch = unpassTruthMatch * (ProcessEvent.passZFakeElCR || ProcessEvent.passZFakeMuCR);
//     unpassTruthMatch = unpassTruthMatch * ProcessEvent.passWZInclusiveLoose;
//     unpassTruthMatch2 = unpassTruthMatch2 * ProcessEvent.passWZInclusiveLoose;

     int TopChannel = (fabs(ProcessEvent.Lep1Flavor) == 13 && fabs(ProcessEvent.Lep2Flavor) == 11 && fabs(ProcessEvent.Lep3Flavor) == 11)
                   || (fabs(ProcessEvent.Lep1Flavor) == 11 && fabs(ProcessEvent.Lep2Flavor) == 13 && fabs(ProcessEvent.Lep3Flavor) == 13);
//     int InclusiveChannel = (ProcessEvent.DecayChannel == 1 || ProcessEvent.DecayChannel == 2 || ProcessEvent.DecayChannel == 3 || ProcessEvent.DecayChannel == 4)
     int InclusiveChannel = (ProcessEvent.DecayChannel == 2 || ProcessEvent.DecayChannel == 3)
                         && (ProcessEvent.Mt_W > 30)
                         && (ProcessEvent.Lep3Pt > 20)
                         && (fabs(ProcessEvent.M_Z - ZPeakMass) < 10);

//     int FakeCR = (ProcessEvent.DecayChannel == 2 || ProcessEvent.DecayChannel == 3)
//               && (ProcessEvent.Mt_W < 30)
//               && (ProcessEvent.Lep3Pt > 20)
//               && (fabs(ProcessEvent.M_Z - ZPeakMass) < 10);


//     unpassTruthMatch = unpassTruthMatch * (InclusiveChannel);
//     unpassTruthMatch2 = unpassTruthMatch2 * (InclusiveChannel);

//     unpassTruthMatch = unpassTruthMatch * (FakeCR);
//     unpassTruthMatch2 = unpassTruthMatch2 * (FakeCR);

//     int unpassTruthMatch = InclusiveChannel * (ProcessEvent.passTruthMatch1 && ProcessEvent.passTruthMatch2 && !ProcessEvent.passTruthMatch3);
//     int unpassTruthMatch2 = InclusiveChannel * (ProcessEvent.passTruthMatch1 && !ProcessEvent.passTruthMatch2 && ProcessEvent.passTruthMatch3);

//     int unpassTruthMatchEl = ProcessEvent.passTopElCR * (ProcessEvent.passIPID3) * (ProcessEvent.passTruthMatch1 && ProcessEvent.passTruthMatch2 && !ProcessEvent.passTruthMatch3);
//     int unpassTruthMatchEl2 = ProcessEvent.passTopElCR * (ProcessEvent.passIPID2) * (ProcessEvent.passTruthMatch1 && !ProcessEvent.passTruthMatch2 && ProcessEvent.passTruthMatch3);
//     int unpassTruthMatchMu = ProcessEvent.passTopMuCR * (ProcessEvent.passIPID3) * (ProcessEvent.passTruthMatch1 && ProcessEvent.passTruthMatch2 && !ProcessEvent.passTruthMatch3);
//     int unpassTruthMatchMu2 = ProcessEvent.passTopMuCR * (ProcessEvent.passIPID2) * (ProcessEvent.passTruthMatch1 && !ProcessEvent.passTruthMatch2 && ProcessEvent.passTruthMatch3);

//     int unpassTruthMatch = ProcessEvent.passWZInclusiveLoose * (ProcessEvent.passTruthMatch1 && ProcessEvent.passTruthMatch2 && !ProcessEvent.passTruthMatch3);
//     int unpassTruthMatch2 = ProcessEvent.passWZInclusiveLoose * (ProcessEvent.passTruthMatch1 && !ProcessEvent.passTruthMatch2 && ProcessEvent.passTruthMatch3);
     if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_ZFakeEl_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * unpassTruthMatch);
     if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_ZFakeMu_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * unpassTruthMatch);
     if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_TopEl_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * unpassTruthMatch);
     if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_TopMu_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * unpassTruthMatch);
     if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->AverageLep3Pt_Lep3MET_ZFakeEl_Loose_numer->HistPtr(iThread - 1)->Fill(ProcessEvent.Mt_W, ProcessEvent.Lep3Pt * TotalWeightZZW * unpassTruthMatch);
     if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->AverageLep3Pt_Lep3MET_ZFakeMu_Loose_numer->HistPtr(iThread - 1)->Fill(ProcessEvent.Mt_W, ProcessEvent.Lep3Pt * TotalWeightZZW * unpassTruthMatch);
     if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->AverageLep3Pt_Lep3MET_ZFakeEl_Loose_denom->HistPtr(iThread - 1)->Fill(ProcessEvent.Mt_W, TotalWeightZZW * unpassTruthMatch);
     if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->AverageLep3Pt_Lep3MET_ZFakeMu_Loose_denom->HistPtr(iThread - 1)->Fill(ProcessEvent.Mt_W, TotalWeightZZW * unpassTruthMatch);

//     if(ProcessEvent.passZCondition3 && ProcessEvent.passIPID3){
     if(ProcessEvent.passZCondition3){
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_ZFakeEl_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZZ * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_ZFakeMu_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZZ * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_TopEl_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZZ * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_TopMu_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZZ * unpassTruthMatch);
     }
     else{
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_ZFakeEl_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_ZFakeMu_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_TopEl_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_TopMu_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * unpassTruthMatch);
     }

//     if(ProcessEvent.passWCondition3 && ProcessEvent.passIPID3){
     if(ProcessEvent.passWCondition){
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_ZFakeEl_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_ZFakeMu_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_TopEl_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_TopMu_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3MET_ZFakeEl_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Mt_W, TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3MET_ZFakeMu_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Mt_W, TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3PtMET_ZFakeEl_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, ProcessEvent.Mt_W, TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3PtMET_ZFakeMu_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, ProcessEvent.Mt_W, TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->AverageLep3Pt_Lep3MET_ZFakeEl_PassW_numer->HistPtr(iThread - 1)->Fill(ProcessEvent.Mt_W, ProcessEvent.Lep3Pt * TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->AverageLep3Pt_Lep3MET_ZFakeMu_PassW_numer->HistPtr(iThread - 1)->Fill(ProcessEvent.Mt_W, ProcessEvent.Lep3Pt * TotalWeightZZW * unpassTruthMatch);
     }
     else{
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_ZFakeEl_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_ZFakeMu_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3Pt_TopEl_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3Pt_TopMu_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3MET_ZFakeEl_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Mt_W, TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3MET_ZFakeMu_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Mt_W, TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->Lep3PtMET_ZFakeEl_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, ProcessEvent.Mt_W, TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->Lep3PtMET_ZFakeMu_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, ProcessEvent.Mt_W, TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 11) myhists->AverageLep3Pt_Lep3MET_ZFakeEl_UnPassW_numer->HistPtr(iThread - 1)->Fill(ProcessEvent.Mt_W, ProcessEvent.Lep3Pt * TotalWeightZZW * unpassTruthMatch);
       if(fabs(ProcessEvent.Lep3Flavor) == 13) myhists->AverageLep3Pt_Lep3MET_ZFakeMu_UnPassW_numer->HistPtr(iThread - 1)->Fill(ProcessEvent.Mt_W, ProcessEvent.Lep3Pt * TotalWeightZZW * unpassTruthMatch);
     }

//     if(ProcessEvent.passZCondition2 * ProcessEvent.passIPID2){
     if(ProcessEvent.passZCondition2){
       if(fabs(ProcessEvent.Lep2Flavor) == 11) myhists->Lep2Pt_ZFakeEl_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightZZW * unpassTruthMatch2);
       if(fabs(ProcessEvent.Lep2Flavor) == 13) myhists->Lep2Pt_ZFakeMu_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightZZW * unpassTruthMatch2);
       if(fabs(ProcessEvent.Lep2Flavor) == 11) myhists->Lep2Pt_TopEl_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightZZW * unpassTruthMatch2);
       if(fabs(ProcessEvent.Lep2Flavor) == 13) myhists->Lep2Pt_TopMu_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightZZW * unpassTruthMatch2);
     }
     else{
       if(fabs(ProcessEvent.Lep2Flavor) == 11) myhists->Lep2Pt_ZFakeEl_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightZZ * unpassTruthMatch2);
       if(fabs(ProcessEvent.Lep2Flavor) == 13) myhists->Lep2Pt_ZFakeMu_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightZZ * unpassTruthMatch2);
       if(fabs(ProcessEvent.Lep2Flavor) == 11) myhists->Lep2Pt_TopEl_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightZZ * unpassTruthMatch2);
       if(fabs(ProcessEvent.Lep2Flavor) == 13) myhists->Lep2Pt_TopMu_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep2Pt, TotalWeightZZ * unpassTruthMatch2);
     }
*/
////////////////////////////////////////////////////////////////////////

     //bool passMassWindow5 = (fabs(ProcessEvent.M_Z - ZPeakMass) < 5) && (ProcessEvent.Mt_W < 10);
     //ProcessEvent.passZFakeElCR = ProcessEvent.passZFakeElCR * ProcessEvent.passWCondition2 * passMassWindow5;
     //ProcessEvent.passZFakeMuCR = ProcessEvent.passZFakeMuCR * ProcessEvent.passWCondition2 * passMassWindow5;
     //ProcessEvent.passZFakeElCR = ProcessEvent.passZFakeElCR * ProcessEvent.passIPID3;
     //ProcessEvent.passZFakeMuCR = ProcessEvent.passZFakeMuCR * ProcessEvent.passIPID3 * ProcessEvent.passMediumID3;
     //ProcessEvent.passTopElCR = ProcessEvent.passTopElCR * ProcessEvent.passIPID3;
     //ProcessEvent.passTopMuCR = ProcessEvent.passTopMuCR * ProcessEvent.passIPID3;

     //ProcessEvent.passTopElCR = ProcessEvent.passTopElCR * (fabs(ProcessEvent.M_Z - ZPeakMass) < 10);
     //ProcessEvent.passTopMuCR = ProcessEvent.passTopMuCR * (fabs(ProcessEvent.M_Z - ZPeakMass) < 10);
     //ProcessEvent.passTopElCR = ProcessEvent.passTopElCR * (ProcessEvent.NBjets == 1);
     //ProcessEvent.passTopMuCR = ProcessEvent.passTopMuCR * (ProcessEvent.NBjets == 1);
     //ProcessEvent.passTopElCR = ProcessEvent.passTopElCR * (fabs(ProcessEvent.M_Z - ZPeakMass) < 10) * (ProcessEvent.NBjets == 1);
     //ProcessEvent.passTopMuCR = ProcessEvent.passTopMuCR * (fabs(ProcessEvent.M_Z - ZPeakMass) < 10) * (ProcessEvent.NBjets == 1);
     //if(ProcessEvent.DecayChannel != 2 && ProcessEvent.DecayChannel != 3) return;

     ////////////////////////////
     //  Fake rate systematic  //
     ////////////////////////////

     if(SystematicName == "nominal" || SystematicName == "FakeBkg_Stat__1up" || SystematicName == "FakeBkg_Stat__1down"){
       ProcessEvent.passZFakeElCR = ProcessEvent.passZFakeElCR * (ProcessEvent.Met < 30);
       ProcessEvent.passZFakeMuCR = ProcessEvent.passZFakeMuCR * (ProcessEvent.Met < 30);
       ProcessEvent.passTopElCR = ProcessEvent.passTopElCR * (ProcessEvent.Met > 25);
       ProcessEvent.passTopMuCR = ProcessEvent.passTopMuCR * (ProcessEvent.Met > 25);
     }
     else if(SystematicName == "FakeBkg_MetCut__1up"){
       ProcessEvent.passZFakeElCR = ProcessEvent.passZFakeElCR * (ProcessEvent.Met < 50);
       ProcessEvent.passZFakeMuCR = ProcessEvent.passZFakeMuCR * (ProcessEvent.Met < 50);
       ProcessEvent.passTopElCR = ProcessEvent.passTopElCR * (ProcessEvent.Met > 50);
       ProcessEvent.passTopMuCR = ProcessEvent.passTopMuCR * (ProcessEvent.Met > 50);
     }
     else if(SystematicName == "FakeBkg_MetCut__1down"){
       ProcessEvent.passZFakeElCR = ProcessEvent.passZFakeElCR * (ProcessEvent.Met < 20);
       ProcessEvent.passZFakeMuCR = ProcessEvent.passZFakeMuCR * (ProcessEvent.Met < 20);
       ProcessEvent.passTopElCR = ProcessEvent.passTopElCR * (ProcessEvent.Met > 20);
       ProcessEvent.passTopMuCR = ProcessEvent.passTopMuCR * (ProcessEvent.Met > 20);
     }
     else{
       ProcessEvent.passZFakeElCR = ProcessEvent.passZFakeElCR * (ProcessEvent.Met < 30);
       ProcessEvent.passZFakeMuCR = ProcessEvent.passZFakeMuCR * (ProcessEvent.Met < 30);
       ProcessEvent.passTopElCR = ProcessEvent.passTopElCR * (ProcessEvent.Met > 25);
       ProcessEvent.passTopMuCR = ProcessEvent.passTopMuCR * (ProcessEvent.Met > 25);
     }

     ///////////////////////////
     //  Fill Fake rate plot  //
     ///////////////////////////

     myhists->Lep3Pt_ZFakeEl_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passZFakeElCR);
     myhists->Lep3Pt_ZFakeEl_UpSys_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passZFakeElCR_UpSys);
     myhists->Lep3Pt_ZFakeEl_DownSys_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passZFakeElCR_DownSys);
     myhists->Lep3Pt_ZFakeMu_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passZFakeMuCR);
     myhists->Lep3Pt_TopEl_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passTopElCR);
     myhists->Lep3Pt_TopMu_Loose->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passTopMuCR);

     myhists->Lep3Pt_ZFakeEl_PassMedium->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.Lep3MediumIDWeight * ProcessEvent.passZFakeElCR * ProcessEvent.passMediumID3);
     myhists->Lep3Pt_ZFakeMu_PassMedium->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.Lep3MediumIDWeight * ProcessEvent.passZFakeMuCR * ProcessEvent.passMediumID3);
     myhists->Lep3Pt_TopEl_PassMedium->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.Lep3MediumIDWeight * ProcessEvent.passTopElCR * ProcessEvent.passMediumID3);
     myhists->Lep3Pt_TopMu_PassMedium->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.Lep3MediumIDWeight * ProcessEvent.passTopMuCR * ProcessEvent.passMediumID3);

     myhists->Lep3Pt_ZFakeEl_PassTight->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.Lep3TightIDWeight * ProcessEvent.passZFakeElCR * ProcessEvent.passTightID3);
     myhists->Lep3Pt_ZFakeMu_PassTight->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.Lep3TightIDWeight * ProcessEvent.passZFakeMuCR * ProcessEvent.passTightID3);
     myhists->Lep3Pt_TopEl_PassTight->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.Lep3TightIDWeight * ProcessEvent.passTopElCR * ProcessEvent.passTightID3);
     myhists->Lep3Pt_TopMu_PassTight->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.Lep3TightIDWeight * ProcessEvent.passTopMuCR * ProcessEvent.passTightID3);

     if(ProcessEvent.passZCondition){
       myhists->Lep3Pt_ZFakeEl_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZZ * ProcessEvent.passZFakeElCR);
       myhists->Lep3Pt_ZFakeEl_UpSys_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZZ * ProcessEvent.passZFakeElCR_UpSys);
       myhists->Lep3Pt_ZFakeEl_DownSys_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZZ * ProcessEvent.passZFakeElCR_DownSys);
       myhists->Lep3Pt_ZFakeMu_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZZ * ProcessEvent.passZFakeMuCR);
       myhists->Lep3Pt_TopEl_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZZ * ProcessEvent.passTopElCR);
       myhists->Lep3Pt_TopMu_PassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZZ * ProcessEvent.passTopMuCR);
     }
     else{
       myhists->Lep3Pt_ZFakeEl_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passZFakeElCR);
       myhists->Lep3Pt_ZFakeEl_UpSys_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passZFakeElCR_UpSys);
       myhists->Lep3Pt_ZFakeEl_DownSys_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passZFakeElCR_DownSys);
       myhists->Lep3Pt_ZFakeMu_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passZFakeMuCR);
       myhists->Lep3Pt_TopEl_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passTopElCR);
       myhists->Lep3Pt_TopMu_UnPassZ->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passTopMuCR);
     }

     if(ProcessEvent.passWCondition){
       myhists->Lep3Pt_ZFakeEl_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * ProcessEvent.passZFakeElCR);
       myhists->Lep3Pt_ZFakeEl_UpSys_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * ProcessEvent.passZFakeElCR_UpSys);
       myhists->Lep3Pt_ZFakeEl_DownSys_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * ProcessEvent.passZFakeElCR_DownSys);
       myhists->Lep3Pt_ZFakeMu_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * ProcessEvent.passZFakeMuCR);
       myhists->Lep3Pt_TopEl_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * ProcessEvent.passTopElCR);
       myhists->Lep3Pt_TopMu_PassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZW * ProcessEvent.passTopMuCR);
     }
     else{
       myhists->Lep3Pt_ZFakeEl_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passZFakeElCR);
       myhists->Lep3Pt_ZFakeEl_UpSys_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passZFakeElCR_UpSys);
       myhists->Lep3Pt_ZFakeEl_DownSys_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passZFakeElCR_DownSys);
       myhists->Lep3Pt_ZFakeMu_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passZFakeMuCR);
       myhists->Lep3Pt_TopEl_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passTopElCR);
       myhists->Lep3Pt_TopMu_UnPassW->HistPtr(iThread - 1)->Fill(ProcessEvent.Lep3Pt, TotalWeightZZ * ProcessEvent.passTopMuCR);
     }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   }//end doFakeRate


   ////////////////////
   //  stop pre-run  //
   ////////////////////


   if(isRunReweightingFactor && !isHaveReweightingFactor) return;
   if(doFakeRate && !isHaveFakeRate) return;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //////////////////////
   //  start post-run  //
   //////////////////////

   if(isSignal && ProcessEvent.Njets == 0) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * 1.03;
   if(isSignal && ProcessEvent.Njets == 1) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * 0.84;
   if(isSignal && ProcessEvent.Njets == 2) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * 0.93;
   if(isSignal && ProcessEvent.Njets >= 3) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * 1.42;
     
   if(isNLOSample && ProcessEvent.Njets >= 2) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * 0.83;

   //////////////////////////////////
   //  Apply Global Selection Cut  //
   //////////////////////////////////

   isCut = false;
   for(int icut = 0; icut < CutInfo.size(); icut++){
     CutForWZPolarization(CutInfo.at(icut), CutLeft.at(icut), CutRight.at(icut), isCut);
   }
   if(isCut) return;

   ///////////
   //  BDT  //
   ///////////

   if(isBDT){
     reader->CalVariable();
     BDTScore = reader->EvaluateMVA();
   }
   if(isBDTSR){
     readerSR->CalVariable();
     BDTScoreSR = readerSR->EvaluateMVA();
   }
   if(isBDTSR100){
     readerSR100->CalVariable();
     BDTScoreSR100 = readerSR100->EvaluateMVA();
   }

   myhists->BkgYield_bkg->HistPtr(iThread - 1)->Fill(0.0, 1);
   myhists->BkgYield_bkg->HistPtr(iThread - 1)->Fill(1, ProcessEvent.passWZInclusive);
   myhists->BkgYield_bkg->HistPtr(iThread - 1)->Fill(2, ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200));
   myhists->BkgYield_bkg->HistPtr(iThread - 1)->Fill(3, ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 100) * (ProcessEvent.Pt_WZ < 70));
   myhists->BkgYield_bkg->HistPtr(iThread - 1)->Fill(4, ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200) * (ProcessEvent.Pt_WZ < 70));

   myhists->Yield_CutFlow_bkg->HistPtr(iThread - 1)->Fill(0.0, 1);
   myhists->Yield_CutFlow_bkg->HistPtr(iThread - 1)->Fill(1, ProcessEvent.passWZInclusive);
   myhists->Yield_CutFlow_bkg->HistPtr(iThread - 1)->Fill(2, ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200));
   myhists->Yield_CutFlow_bkg->HistPtr(iThread - 1)->Fill(3, ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 100) * (ProcessEvent.Pt_WZ < 70));
   myhists->Yield_CutFlow_bkg->HistPtr(iThread - 1)->Fill(4, ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200) * (ProcessEvent.Pt_WZ < 70));

   myhists->NormalizedYield_CutFlow_bkg->HistPtr(iThread - 1)->Fill(0.0, ProcessEvent.NormSF);
   myhists->NormalizedYield_CutFlow_bkg->HistPtr(iThread - 1)->Fill(1, ProcessEvent.NormSF * ProcessEvent.passWZInclusive);
   myhists->NormalizedYield_CutFlow_bkg->HistPtr(iThread - 1)->Fill(2, ProcessEvent.NormSF * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200));
   myhists->NormalizedYield_CutFlow_bkg->HistPtr(iThread - 1)->Fill(3, ProcessEvent.NormSF * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 100) * (ProcessEvent.Pt_WZ < 70));
   myhists->NormalizedYield_CutFlow_bkg->HistPtr(iThread - 1)->Fill(4, ProcessEvent.NormSF * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200) * (ProcessEvent.Pt_WZ < 70));

   myhists->Polarized_CutFlow_bkg->HistPtr(iThread - 1)->Fill(0.0, ProcessEvent.TotalWeight);
   myhists->Polarized_CutFlow_bkg->HistPtr(iThread - 1)->Fill(1, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive);
   myhists->Polarized_CutFlow_bkg->HistPtr(iThread - 1)->Fill(2, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200));
   myhists->Polarized_CutFlow_bkg->HistPtr(iThread - 1)->Fill(3, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 100) * (ProcessEvent.Pt_WZ < 70));
   myhists->Polarized_CutFlow_bkg->HistPtr(iThread - 1)->Fill(4, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200) * (ProcessEvent.Pt_WZ < 70));
   myhists->Polarized_CutFlow_bkg->HistPtr(iThread - 1)->Fill(5, ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70));

   ////////////////////////////////
   //  Apply Reweighting Factor  //
   ////////////////////////////////

   if(isHaveReweightingFactor) isNormalizedNLO = false;

   double ReweightFactor;
   if(isHaveReweightingFactor || isNormalizedNLO){
     if(isHaveReweightingFactor) ReweightFactor = myhists->ReweightFactor->GetBinContent(myhists->ReweightFactor->FindBin(ProcessEvent.Pt_WZ));
     else if(isNormalizedNLO) ReweightFactor = NLOKFactor;
     for(int iprocesshist = 0; iprocesshist < myhists->hist_process.size(); iprocesshist++){
       myhists->hist_process.at(iprocesshist)->InputReweightingFactor(iThread, ReweightFactor);
     }
   }

   /////////////////
   //  Fill plot  //
   /////////////////
   bool isRight = false;
   bool isWrong = false;
   isRight = fabs(ProcessEvent.ZY) > fabs(ProcessEvent.Lep3Eta);
   isWrong = fabs(ProcessEvent.ZY) < fabs(ProcessEvent.Lep3Eta);
   double EtaDiff = fabs(fabs(ProcessEvent.ZY) - fabs(ProcessEvent.Lep3Eta));

   if(OnlyNominal){
     myhists->M_WZ->Fill(iThread, ProcessEvent.M_WZ, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->M_3l->Fill(iThread, ProcessEvent.M_3l, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->Mt_WZ->Fill(iThread, ProcessEvent.Mt_WZ, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->M_Z->Fill(iThread, ProcessEvent.M_Z, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->Mt_W->Fill(iThread, ProcessEvent.Mt_W, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->Met->Fill(iThread, ProcessEvent.Met, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->Njets->Fill(iThread, ProcessEvent.Njets, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->NBjets->Fill(iThread, ProcessEvent.NBjets, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->Lep1Pt->Fill(iThread, ProcessEvent.Lep1Pt, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->Lep2Pt->Fill(iThread, ProcessEvent.Lep2Pt, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->Lep3Pt->Fill(iThread, ProcessEvent.Lep3Pt, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->Lep1Eta->Fill(iThread, ProcessEvent.Lep1Eta, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->Lep2Eta->Fill(iThread, ProcessEvent.Lep2Eta, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->Lep3Eta->Fill(iThread, ProcessEvent.Lep3Eta, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->Lep1Phi->Fill(iThread, ProcessEvent.Lep1Phi, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->Lep2Phi->Fill(iThread, ProcessEvent.Lep2Phi, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->Lep3Phi->Fill(iThread, ProcessEvent.Lep3Phi, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->LepPt->Fill(iThread, ProcessEvent.Lep1Pt, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->LepPt->Fill(iThread, ProcessEvent.Lep2Pt, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->LepPt->Fill(iThread, ProcessEvent.Lep3Pt, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->LepEta->Fill(iThread, ProcessEvent.Lep1Eta, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->LepEta->Fill(iThread, ProcessEvent.Lep2Eta, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->LepEta->Fill(iThread, ProcessEvent.Lep3Eta, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->LepPhi->Fill(iThread, ProcessEvent.Lep1Phi, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->LepPhi->Fill(iThread, ProcessEvent.Lep2Phi, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->LepPhi->Fill(iThread, ProcessEvent.Lep3Phi, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.DecayChannel == 1) myhists->Lep2Pt_mmm->Fill(iThread, ProcessEvent.Lep2Pt, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.DecayChannel == 2) myhists->Lep2Pt_mme->Fill(iThread, ProcessEvent.Lep2Pt, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.DecayChannel == 3) myhists->Lep2Pt_eem->Fill(iThread, ProcessEvent.Lep2Pt, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.DecayChannel == 4) myhists->Lep2Pt_eee->Fill(iThread, ProcessEvent.Lep2Pt, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.DecayChannel == 1) myhists->Lep3Pt_mmm->Fill(iThread, ProcessEvent.Lep3Pt, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.DecayChannel == 2) myhists->Lep3Pt_mme->Fill(iThread, ProcessEvent.Lep3Pt, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.DecayChannel == 3) myhists->Lep3Pt_eem->Fill(iThread, ProcessEvent.Lep3Pt, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.DecayChannel == 4) myhists->Lep3Pt_eee->Fill(iThread, ProcessEvent.Lep3Pt, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.DecayChannel == 1) myhists->Lep3Eta_mmm->Fill(iThread, ProcessEvent.Lep3Eta, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.DecayChannel == 2) myhists->Lep3Eta_mme->Fill(iThread, ProcessEvent.Lep3Eta, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.DecayChannel == 3) myhists->Lep3Eta_eem->Fill(iThread, ProcessEvent.Lep3Eta, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.DecayChannel == 4) myhists->Lep3Eta_eee->Fill(iThread, ProcessEvent.Lep3Eta, ProcessEvent.TotalWeight, ProcessEvent);
     if(ProcessEvent.DecayChannel == 1) myhists->Mt_W_mmm->Fill(iThread, ProcessEvent.Mt_W, ProcessEvent.TotalWeight, ProcessEvent);
     if(ProcessEvent.DecayChannel == 2) myhists->Mt_W_mme->Fill(iThread, ProcessEvent.Mt_W, ProcessEvent.TotalWeight, ProcessEvent);
     if(ProcessEvent.DecayChannel == 3) myhists->Mt_W_eem->Fill(iThread, ProcessEvent.Mt_W, ProcessEvent.TotalWeight, ProcessEvent);
     if(ProcessEvent.DecayChannel == 4) myhists->Mt_W_eee->Fill(iThread, ProcessEvent.Mt_W, ProcessEvent.TotalWeight, ProcessEvent);
     if(ProcessEvent.DecayChannel == 1) myhists->Met_mmm->Fill(iThread, ProcessEvent.Met, ProcessEvent.TotalWeight, ProcessEvent);
     if(ProcessEvent.DecayChannel == 2) myhists->Met_mme->Fill(iThread, ProcessEvent.Met, ProcessEvent.TotalWeight, ProcessEvent);
     if(ProcessEvent.DecayChannel == 3) myhists->Met_eem->Fill(iThread, ProcessEvent.Met, ProcessEvent.TotalWeight, ProcessEvent);
     if(ProcessEvent.DecayChannel == 4) myhists->Met_eee->Fill(iThread, ProcessEvent.Met, ProcessEvent.TotalWeight, ProcessEvent);
     if(ProcessEvent.DecayChannel == 1) myhists->Pt_Z_mmm->Fill(iThread, ProcessEvent.Pt_Z, ProcessEvent.TotalWeight, ProcessEvent);
     if(ProcessEvent.DecayChannel == 2) myhists->Pt_Z_mme->Fill(iThread, ProcessEvent.Pt_Z, ProcessEvent.TotalWeight, ProcessEvent);
     if(ProcessEvent.DecayChannel == 3) myhists->Pt_Z_eem->Fill(iThread, ProcessEvent.Pt_Z, ProcessEvent.TotalWeight, ProcessEvent);
     if(ProcessEvent.DecayChannel == 4) myhists->Pt_Z_eee->Fill(iThread, ProcessEvent.Pt_Z, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->Mpx->Fill(iThread, ProcessEvent.Mpx, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->Mpy->Fill(iThread, ProcessEvent.Mpy, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->Mpz->Fill(iThread, ProcessEvent.Mpz, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->LWTNNNuPz->Fill(iThread, ProcessEvent.LWTNNNuPz, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->TruthNuPz->Fill(iThread, ProcessEvent.TruthNuPz, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->MpzDiff->Fill(iThread, ProcessEvent.Mpz - ProcessEvent.TruthNuPz, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->LWTNNNuPzDiff->Fill(iThread, ProcessEvent.LWTNNNuPz - ProcessEvent.TruthNuPz, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->v_MpzDiff.at(iThread - 1)->Fill(ProcessEvent.Mpz - ProcessEvent.TruthNuPz, ProcessEvent.TotalWeight);
     //myhists->v_LWTNNNuPzDiff.at(iThread - 1)->Fill(ProcessEvent.LWTNNNuPz - ProcessEvent.TruthNuPz, ProcessEvent.TotalWeight);
     //myhists->LWTNNpLL->Fill(iThread, ProcessEvent.LWTNNpLL, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->LWTNNpLT->Fill(iThread, ProcessEvent.LWTNNpLT, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->LWTNNpTL->Fill(iThread, ProcessEvent.LWTNNpTL, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->LWTNNpTT->Fill(iThread, ProcessEvent.LWTNNpTT, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->Pt_W->Fill(iThread, ProcessEvent.Pt_W, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->Pt_Z->Fill(iThread, ProcessEvent.Pt_Z, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->Pt_WZ->Fill(iThread, ProcessEvent.Pt_WZ, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->SumJetPt->Fill(iThread, ProcessEvent.SumJetPt, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->CosThetaV->Fill(iThread, ProcessEvent.CosThetaV, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->CosThetaV_WLZL->Fill(iThread, ProcessEvent.CosThetaV, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->CosThetaV_WLZH->Fill(iThread, ProcessEvent.CosThetaV, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->CosThetaV_WHZL->Fill(iThread, ProcessEvent.CosThetaV, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->CosThetaV_WHZH->Fill(iThread, ProcessEvent.CosThetaV, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->CosThetaVAbs->Fill(iThread, fabs(ProcessEvent.CosThetaV), ProcessEvent.TotalWeight, ProcessEvent);
     myhists->CosThetaLepW->Fill(iThread, ProcessEvent.CosThetaLepW, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->CosThetaLepZ->Fill(iThread, ProcessEvent.CosThetaLepZ, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->DY_3N->Fill(iThread, ProcessEvent.DY_3N, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.Lep3Charge > 0) myhists->DY_WPlusZ->Fill(iThread, ProcessEvent.DY_WZ, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.Lep3Charge < 0) myhists->DY_WMinusZ->Fill(iThread, ProcessEvent.DY_WZ, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.Lep3Charge > 0) myhists->DY_3PlusZ->Fill(iThread, ProcessEvent.DY_3Z, ProcessEvent.TotalWeight, ProcessEvent);
     //if(ProcessEvent.Lep3Charge < 0) myhists->DY_3MinusZ->Fill(iThread, ProcessEvent.DY_3Z, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->DeltaPhiLepWLepZ->Fill(iThread, ProcessEvent.DeltaPhiLepWLepZ, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->DeltaPhiLepWLepZ_WLZL->Fill(iThread, ProcessEvent.DeltaPhiLepWLepZ, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->DeltaPhiLepWLepZ_WLZH->Fill(iThread, ProcessEvent.DeltaPhiLepWLepZ, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->DeltaPhiLepWLepZ_WHZL->Fill(iThread, ProcessEvent.DeltaPhiLepWLepZ, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->DeltaPhiLepWLepZ_WHZH->Fill(iThread, ProcessEvent.DeltaPhiLepWLepZ, ProcessEvent.TotalWeight, ProcessEvent);
     //myhists->DeltaPhiLepWLepZWZFrame->Fill(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, ProcessEvent.TotalWeight, ProcessEvent);
     //if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->DeltaPhiLepWLepZWZFrame_WLZL->Fill(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, ProcessEvent.TotalWeight, ProcessEvent);
     //if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->DeltaPhiLepWLepZWZFrame_WLZH->Fill(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, ProcessEvent.TotalWeight, ProcessEvent);
     //if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->DeltaPhiLepWLepZWZFrame_WHZL->Fill(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, ProcessEvent.TotalWeight, ProcessEvent);
     //if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->DeltaPhiLepWLepZWZFrame_WHZH->Fill(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->R21->Fill(iThread, ProcessEvent.R21, ProcessEvent.TotalWeight, ProcessEvent);
     //if(fabs(ProcessEvent.CosThetaLepW) < 0.4 && fabs(ProcessEvent.CosThetaLepZ) < 0.4) myhists->R21_WLZL->Fill(iThread, ProcessEvent.R21, ProcessEvent.TotalWeight, ProcessEvent);
     //if(fabs(ProcessEvent.CosThetaLepW) < 0.4 && fabs(ProcessEvent.CosThetaLepZ) > 0.4) myhists->R21_WLZH->Fill(iThread, ProcessEvent.R21, ProcessEvent.TotalWeight, ProcessEvent);
     //if(fabs(ProcessEvent.CosThetaLepW) > 0.4 && fabs(ProcessEvent.CosThetaLepZ) < 0.4) myhists->R21_WHZL->Fill(iThread, ProcessEvent.R21, ProcessEvent.TotalWeight, ProcessEvent);
     //if(fabs(ProcessEvent.CosThetaLepW) > 0.4 && fabs(ProcessEvent.CosThetaLepZ) > 0.4) myhists->R21_WHZH->Fill(iThread, ProcessEvent.R21, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->RightZYWLepEta->Fill(iThread, (double)EtaDiff, ProcessEvent.TotalWeight * isRight, ProcessEvent);
     myhists->WrongZYWLepEta->Fill(iThread, (double)EtaDiff, ProcessEvent.TotalWeight * isWrong, ProcessEvent);
     myhists->WDecayStatus->Fill(iThread, ProcessEvent.WDecayStatus, ProcessEvent.TotalWeight, ProcessEvent);
     myhists->ZDecayStatus->Fill(iThread, ProcessEvent.ZDecayStatus, ProcessEvent.TotalWeight, ProcessEvent);
   }

   myhists->Channel->Fill(iThread, (double)ProcessEvent.DecayChannel, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->DY_WZ->Fill(iThread, ProcessEvent.DY_WZ, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->DY_3Z->Fill(iThread, ProcessEvent.DY_3Z, ProcessEvent.TotalWeight, ProcessEvent);

   if(isBDT){
     myhists->BDTScore->Fill(iThread, BDTScore, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->BDTScore_WLZL->Fill(iThread, BDTScore, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->BDTScore_WLZH->Fill(iThread, BDTScore, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->BDTScore_WHZL->Fill(iThread, BDTScore, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->BDTScore_WHZH->Fill(iThread, BDTScore, ProcessEvent.TotalWeight, ProcessEvent);
   }
   if(isBDTSR){
     myhists->BDTScoreSR->Fill(iThread, BDTScoreSR, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->BDTScoreSR_WLZL->Fill(iThread, BDTScoreSR, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->BDTScoreSR_WLZH->Fill(iThread, BDTScoreSR, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->BDTScoreSR_WHZL->Fill(iThread, BDTScoreSR, ProcessEvent.TotalWeight, ProcessEvent);
     if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->BDTScoreSR_WHZH->Fill(iThread, BDTScoreSR, ProcessEvent.TotalWeight, ProcessEvent);
   }
   if(isBDTSR100){
     myhists->BDTScoreSR100->Fill(iThread, BDTScoreSR100, ProcessEvent.TotalWeight, ProcessEvent);
   }

   /////////////////////
   ////  Fake Rate  ////
   /////////////////////

   if(doFakeRate){
     TotalWeight = ProcessEvent.WeightNormalized;
     //TotalWeight = ProcessEvent.TotalWeight;
     if(BkgShortName == "BkgWZQCD" || BkgShortName == "BkgWZEW" || BkgShortName == "BkgZZ" || BkgShortName == "BkgVVV" || BkgShortName == "BkgttbarV"){
       TotalWeight = TotalWeight * (-1);
     }
     else if(isData){
       TotalWeight = TotalWeight;
     }
     else{
       return;
     }

     if(isHaveFakeRate){
       TString Flavor;
       if(ProcessEvent.DecayChannel == 1) Flavor = "mmm";
       if(ProcessEvent.DecayChannel == 2) Flavor = "mme";
       if(ProcessEvent.DecayChannel == 3) Flavor = "eem";
       if(ProcessEvent.DecayChannel == 4) Flavor = "eee";
       if(ProcessEvent.DecayChannel == 5) Flavor = "emm";
       if(ProcessEvent.DecayChannel == 6) Flavor = "mee";

       if(doFakeRate == 1) myFakeRate->GetIndex(ProcessEvent.Lep1Pt, ProcessEvent.Lep2Pt, ProcessEvent.Lep3Pt, Flavor);
       //if(doFakeRate == 1) myFakeRate_ValidationZ->GetIndex(ProcessEvent.Lep1Pt, ProcessEvent.Lep2Pt, ProcessEvent.Lep3Pt, Flavor);
       //if(doFakeRate == 1) myFakeRate_ValidationW->GetIndex(ProcessEvent.Lep1Pt, ProcessEvent.Lep2Pt, ProcessEvent.Lep3Pt, Flavor);
       if(doFakeRate == 2) myFakeRate->GetIndexFullMatrix(ProcessEvent.Lep1Pt, ProcessEvent.Lep2Pt, ProcessEvent.Lep3Pt, Flavor);

       double TTTWeight = ProcessEvent.Lep1WeightZ * ProcessEvent.Lep2WeightZ * ProcessEvent.Lep3WeightW;
       double TTLWeight = ProcessEvent.Lep1WeightZ * ProcessEvent.Lep2WeightZ;
       double TLTWeight = ProcessEvent.Lep1WeightZ * ProcessEvent.Lep3WeightW;
       double LTTWeight = ProcessEvent.Lep2WeightZ * ProcessEvent.Lep3WeightW;
       double TLLWeight = ProcessEvent.Lep1WeightZ;
       double LTLWeight = ProcessEvent.Lep2WeightZ;
       double LLTWeight = ProcessEvent.Lep3WeightW;

       for(int ihist = 0; ihist < myhists->FakeHist_1d.size(); ihist++){
         myhists->FakeHist_1d.at(ihist)->HistPtr(iThread - 1)->Initial(ProcessEvent.passTTT, ProcessEvent.passTTL, ProcessEvent.passTLT, ProcessEvent.passLTT,
                                                                 ProcessEvent.passTLL, ProcessEvent.passLTL, ProcessEvent.passLLT);

         myhists->FakeHist_1d.at(ihist)->HistPtr(iThread - 1)->InitialWeight(TTTWeight, TTLWeight, TLTWeight, LTTWeight, TLLWeight, LTLWeight, LLTWeight);
       }

/*
       int passTTT = ProcessEvent.passZCondition1 * ProcessEvent.passZCondition2 * ProcessEvent.passZCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
       int passTTL = ProcessEvent.passZCondition1 * ProcessEvent.passZCondition2 * (!ProcessEvent.passZCondition3) * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
       int passTLT = ProcessEvent.passZCondition1 * (!ProcessEvent.passZCondition2) * ProcessEvent.passZCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
       int passLTT = (!ProcessEvent.passZCondition1) * ProcessEvent.passZCondition2 * ProcessEvent.passZCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
       int passTLL = ProcessEvent.passZCondition1 * (!ProcessEvent.passZCondition2) * (!ProcessEvent.passZCondition3) * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
       int passLTL = (!ProcessEvent.passZCondition1) * ProcessEvent.passZCondition2 * (!ProcessEvent.passZCondition3) * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
       int passLLT = (!ProcessEvent.passZCondition1) * (!ProcessEvent.passZCondition2) * ProcessEvent.passZCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;

       for(int iprocesshist = 0; iprocesshist < myhists->hist_process.size(); iprocesshist++){
         myhists->hist_process.at(iprocesshist)->TopEnrichCR_Fake->HistPtr(iThread - 1)->Initial(passTTT, passTTL, passTLT, passLTT, passTLL, passLTL, passLLT);
       }
*/

       if(OnlyNominal){
         myhists->M_WZ->FillFake(iThread, ProcessEvent.M_WZ, TotalWeight, ProcessEvent);
         myhists->M_3l->FillFake(iThread, ProcessEvent.M_3l, TotalWeight, ProcessEvent);
         myhists->Mt_WZ->FillFake(iThread, ProcessEvent.Mt_WZ, TotalWeight, ProcessEvent);
         myhists->M_Z->FillFake(iThread, ProcessEvent.M_Z, TotalWeight, ProcessEvent);
         myhists->Mt_W->FillFake(iThread, ProcessEvent.Mt_W, TotalWeight, ProcessEvent);
         myhists->Met->FillFake(iThread, ProcessEvent.Met, TotalWeight, ProcessEvent);
         myhists->Njets->FillFake(iThread, ProcessEvent.Njets, TotalWeight, ProcessEvent);
         myhists->NBjets->FillFake(iThread, ProcessEvent.NBjets, TotalWeight, ProcessEvent);
         //myhists->Lep1Pt->FillFake(iThread, ProcessEvent.Lep1Pt, TotalWeight, ProcessEvent);
         //myhists->Lep2Pt->FillFake(iThread, ProcessEvent.Lep2Pt, TotalWeight, ProcessEvent);
         //myhists->Lep3Pt->FillFake(iThread, ProcessEvent.Lep3Pt, TotalWeight, ProcessEvent);
         //myhists->Lep1Eta->FillFake(iThread, ProcessEvent.Lep1Eta, TotalWeight, ProcessEvent);
         //myhists->Lep2Eta->FillFake(iThread, ProcessEvent.Lep2Eta, TotalWeight, ProcessEvent);
         //myhists->Lep3Eta->FillFake(iThread, ProcessEvent.Lep3Eta, TotalWeight, ProcessEvent);
         //myhists->Lep1Phi->FillFake(iThread, ProcessEvent.Lep1Phi, TotalWeight, ProcessEvent);
         //myhists->Lep2Phi->FillFake(iThread, ProcessEvent.Lep2Phi, TotalWeight, ProcessEvent);
         //myhists->Lep3Phi->FillFake(iThread, ProcessEvent.Lep3Phi, TotalWeight, ProcessEvent);
         myhists->LepPt->FillFake(iThread, ProcessEvent.Lep1Pt, TotalWeight, ProcessEvent);
         myhists->LepPt->FillFake(iThread, ProcessEvent.Lep2Pt, TotalWeight, ProcessEvent);
         myhists->LepPt->FillFake(iThread, ProcessEvent.Lep3Pt, TotalWeight, ProcessEvent);
         myhists->LepEta->FillFake(iThread, ProcessEvent.Lep1Eta, TotalWeight, ProcessEvent);
         myhists->LepEta->FillFake(iThread, ProcessEvent.Lep2Eta, TotalWeight, ProcessEvent);
         myhists->LepEta->FillFake(iThread, ProcessEvent.Lep3Eta, TotalWeight, ProcessEvent);
         myhists->LepPhi->FillFake(iThread, ProcessEvent.Lep1Phi, TotalWeight, ProcessEvent);
         myhists->LepPhi->FillFake(iThread, ProcessEvent.Lep2Phi, TotalWeight, ProcessEvent);
         myhists->LepPhi->FillFake(iThread, ProcessEvent.Lep3Phi, TotalWeight, ProcessEvent);
         //if(ProcessEvent.DecayChannel == 1) myhists->Lep2Pt_mmm->FillFake(iThread, ProcessEvent.Lep2Pt, TotalWeight, ProcessEvent);
         //if(ProcessEvent.DecayChannel == 2) myhists->Lep2Pt_mme->FillFake(iThread, ProcessEvent.Lep2Pt, TotalWeight, ProcessEvent);
         //if(ProcessEvent.DecayChannel == 3) myhists->Lep2Pt_eem->FillFake(iThread, ProcessEvent.Lep2Pt, TotalWeight, ProcessEvent);
         //if(ProcessEvent.DecayChannel == 4) myhists->Lep2Pt_eee->FillFake(iThread, ProcessEvent.Lep2Pt, TotalWeight, ProcessEvent);
         //if(ProcessEvent.DecayChannel == 1) myhists->Lep3Pt_mmm->FillFake(iThread, ProcessEvent.Lep3Pt, TotalWeight, ProcessEvent);
         //if(ProcessEvent.DecayChannel == 2) myhists->Lep3Pt_mme->FillFake(iThread, ProcessEvent.Lep3Pt, TotalWeight, ProcessEvent);
         //if(ProcessEvent.DecayChannel == 3) myhists->Lep3Pt_eem->FillFake(iThread, ProcessEvent.Lep3Pt, TotalWeight, ProcessEvent);
         //if(ProcessEvent.DecayChannel == 4) myhists->Lep3Pt_eee->FillFake(iThread, ProcessEvent.Lep3Pt, TotalWeight, ProcessEvent);
         //if(ProcessEvent.DecayChannel == 1) myhists->Lep3Eta_mmm->FillFake(iThread, ProcessEvent.Lep3Eta, TotalWeight, ProcessEvent);
         //if(ProcessEvent.DecayChannel == 2) myhists->Lep3Eta_mme->FillFake(iThread, ProcessEvent.Lep3Eta, TotalWeight, ProcessEvent);
         //if(ProcessEvent.DecayChannel == 3) myhists->Lep3Eta_eem->FillFake(iThread, ProcessEvent.Lep3Eta, TotalWeight, ProcessEvent);
         //f(ProcessEvent.DecayChannel == 4) myhists->Lep3Eta_eee->FillFake(iThread, ProcessEvent.Lep3Eta, TotalWeight, ProcessEvent);
         if(ProcessEvent.DecayChannel == 1) myhists->Mt_W_mmm->FillFake(iThread, ProcessEvent.Mt_W, TotalWeight, ProcessEvent);
         if(ProcessEvent.DecayChannel == 2) myhists->Mt_W_mme->FillFake(iThread, ProcessEvent.Mt_W, TotalWeight, ProcessEvent);
         if(ProcessEvent.DecayChannel == 3) myhists->Mt_W_eem->FillFake(iThread, ProcessEvent.Mt_W, TotalWeight, ProcessEvent);
         if(ProcessEvent.DecayChannel == 4) myhists->Mt_W_eee->FillFake(iThread, ProcessEvent.Mt_W, TotalWeight, ProcessEvent);
         if(ProcessEvent.DecayChannel == 1) myhists->Met_mmm->FillFake(iThread, ProcessEvent.Met, TotalWeight, ProcessEvent);
         if(ProcessEvent.DecayChannel == 2) myhists->Met_mme->FillFake(iThread, ProcessEvent.Met, TotalWeight, ProcessEvent);
         if(ProcessEvent.DecayChannel == 3) myhists->Met_eem->FillFake(iThread, ProcessEvent.Met, TotalWeight, ProcessEvent);
         if(ProcessEvent.DecayChannel == 4) myhists->Met_eee->FillFake(iThread, ProcessEvent.Met, TotalWeight, ProcessEvent);
         if(ProcessEvent.DecayChannel == 1) myhists->Pt_Z_mmm->FillFake(iThread, ProcessEvent.Pt_Z, TotalWeight, ProcessEvent);
         if(ProcessEvent.DecayChannel == 2) myhists->Pt_Z_mme->FillFake(iThread, ProcessEvent.Pt_Z, TotalWeight, ProcessEvent);
         if(ProcessEvent.DecayChannel == 3) myhists->Pt_Z_eem->FillFake(iThread, ProcessEvent.Pt_Z, TotalWeight, ProcessEvent);
         if(ProcessEvent.DecayChannel == 4) myhists->Pt_Z_eee->FillFake(iThread, ProcessEvent.Pt_Z, TotalWeight, ProcessEvent);
         //myhists->Mpx->FillFake(iThread, ProcessEvent.Mpx, TotalWeight, ProcessEvent);
         //myhists->Mpy->FillFake(iThread, ProcessEvent.Mpy, TotalWeight, ProcessEvent);
         //myhists->Mpz->FillFake(iThread, ProcessEvent.Mpz, TotalWeight, ProcessEvent);
         //myhists->LWTNNNuPz->FillFake(iThread, ProcessEvent.LWTNNNuPz, TotalWeight, ProcessEvent);
         //myhists->TruthNuPz->FillFake(iThread, ProcessEvent.TruthNuPz, TotalWeight, ProcessEvent);
         //myhists->LWTNNpLL->FillFake(iThread, ProcessEvent.LWTNNpLL, TotalWeight, ProcessEvent);
         //myhists->LWTNNpLT->FillFake(iThread, ProcessEvent.LWTNNpLT, TotalWeight, ProcessEvent);
         //myhists->LWTNNpTL->FillFake(iThread, ProcessEvent.LWTNNpTL, TotalWeight, ProcessEvent);
         //myhists->LWTNNpTT->FillFake(iThread, ProcessEvent.LWTNNpTT, TotalWeight, ProcessEvent);
         myhists->Pt_W->FillFake(iThread, ProcessEvent.Pt_W, TotalWeight, ProcessEvent);
         myhists->Pt_Z->FillFake(iThread, ProcessEvent.Pt_Z, TotalWeight, ProcessEvent);
         myhists->Pt_WZ->FillFake(iThread, ProcessEvent.Pt_WZ, TotalWeight, ProcessEvent);
         myhists->SumJetPt->FillFake(iThread, ProcessEvent.SumJetPt, TotalWeight, ProcessEvent);
         myhists->CosThetaV->FillFake(iThread, ProcessEvent.CosThetaV, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->CosThetaV_WLZL->FillFake(iThread, ProcessEvent.CosThetaV, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->CosThetaV_WLZH->FillFake(iThread, ProcessEvent.CosThetaV, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->CosThetaV_WHZL->FillFake(iThread, ProcessEvent.CosThetaV, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->CosThetaV_WHZH->FillFake(iThread, ProcessEvent.CosThetaV, TotalWeight, ProcessEvent);
         myhists->CosThetaVAbs->FillFake(iThread, fabs(ProcessEvent.CosThetaV), TotalWeight, ProcessEvent);
         myhists->CosThetaLepW->FillFake(iThread, ProcessEvent.CosThetaLepW, TotalWeight, ProcessEvent);
         myhists->CosThetaLepZ->FillFake(iThread, ProcessEvent.CosThetaLepZ, TotalWeight, ProcessEvent);
         myhists->DY_3N->FillFake(iThread, ProcessEvent.DY_3N, TotalWeight, ProcessEvent);
         //if(ProcessEvent.Lep3Charge > 0) myhists->DY_WPlusZ->FillFake(iThread, ProcessEvent.DY_WZ, TotalWeight, ProcessEvent);
         //if(ProcessEvent.Lep3Charge < 0) myhists->DY_WMinusZ->FillFake(iThread, ProcessEvent.DY_WZ, TotalWeight, ProcessEvent);
         //if(ProcessEvent.Lep3Charge > 0) myhists->DY_3PlusZ->FillFake(iThread, ProcessEvent.DY_3Z, TotalWeight, ProcessEvent);
         //if(ProcessEvent.Lep3Charge < 0) myhists->DY_3MinusZ->FillFake(iThread, ProcessEvent.DY_3Z, TotalWeight, ProcessEvent);
         myhists->DeltaPhiLepWLepZ->FillFake(iThread, ProcessEvent.DeltaPhiLepWLepZ, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->DeltaPhiLepWLepZ_WLZL->FillFake(iThread, ProcessEvent.DeltaPhiLepWLepZ, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->DeltaPhiLepWLepZ_WLZH->FillFake(iThread, ProcessEvent.DeltaPhiLepWLepZ, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->DeltaPhiLepWLepZ_WHZL->FillFake(iThread, ProcessEvent.DeltaPhiLepWLepZ, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->DeltaPhiLepWLepZ_WHZH->FillFake(iThread, ProcessEvent.DeltaPhiLepWLepZ, TotalWeight, ProcessEvent);
         //myhists->DeltaPhiLepWLepZWZFrame->FillFake(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, TotalWeight, ProcessEvent);
         //if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->DeltaPhiLepWLepZWZFrame_WLZL->FillFake(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, TotalWeight, ProcessEvent);
         //if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->DeltaPhiLepWLepZWZFrame_WLZH->FillFake(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, TotalWeight, ProcessEvent);
         //if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->DeltaPhiLepWLepZWZFrame_WHZL->FillFake(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, TotalWeight, ProcessEvent);
         //if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->DeltaPhiLepWLepZWZFrame_WHZH->FillFake(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, TotalWeight, ProcessEvent);
         myhists->R21->FillFake(iThread, ProcessEvent.R21, TotalWeight, ProcessEvent);
         //if(fabs(ProcessEvent.CosThetaLepW) < 0.4 && fabs(ProcessEvent.CosThetaLepZ) < 0.4) myhists->R21_WLZL->FillFake(iThread, ProcessEvent.R21, TotalWeight, ProcessEvent);
         //if(fabs(ProcessEvent.CosThetaLepW) < 0.4 && fabs(ProcessEvent.CosThetaLepZ) > 0.4) myhists->R21_WLZH->FillFake(iThread, ProcessEvent.R21, TotalWeight, ProcessEvent);
         //if(fabs(ProcessEvent.CosThetaLepW) > 0.4 && fabs(ProcessEvent.CosThetaLepZ) < 0.4) myhists->R21_WHZL->FillFake(iThread, ProcessEvent.R21, TotalWeight, ProcessEvent);
         //if(fabs(ProcessEvent.CosThetaLepW) > 0.4 && fabs(ProcessEvent.CosThetaLepZ) > 0.4) myhists->R21_WHZH->FillFake(iThread, ProcessEvent.R21, TotalWeight, ProcessEvent);
         myhists->RightZYWLepEta->FillFake(iThread, (double)EtaDiff, TotalWeight * isRight, ProcessEvent);
         myhists->WrongZYWLepEta->FillFake(iThread, (double)EtaDiff, TotalWeight * isWrong, ProcessEvent);
         myhists->WDecayStatus->FillFake(iThread, ProcessEvent.WDecayStatus, TotalWeight, ProcessEvent);
         myhists->ZDecayStatus->FillFake(iThread, ProcessEvent.ZDecayStatus, TotalWeight, ProcessEvent);
       }

       myhists->Channel->FillFake(iThread, (double)ProcessEvent.DecayChannel, TotalWeight, ProcessEvent);
       myhists->DY_WZ->FillFake(iThread, ProcessEvent.DY_WZ, TotalWeight, ProcessEvent);
       myhists->DY_3Z->FillFake(iThread, ProcessEvent.DY_3Z, TotalWeight, ProcessEvent);

       if(isBDT){
         myhists->BDTScore->FillFake(iThread, BDTScore, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->BDTScore_WLZL->FillFake(iThread, BDTScore, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->BDTScore_WLZH->FillFake(iThread, BDTScore, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->BDTScore_WHZL->FillFake(iThread, BDTScore, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->BDTScore_WHZH->FillFake(iThread, BDTScore, TotalWeight, ProcessEvent);
       }
       if(isBDTSR){
         myhists->BDTScoreSR->FillFake(iThread, BDTScoreSR, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->BDTScoreSR_WLZL->FillFake(iThread, BDTScoreSR, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) < 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->BDTScoreSR_WLZH->FillFake(iThread, BDTScoreSR, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) < 0.5) myhists->BDTScoreSR_WHZL->FillFake(iThread, BDTScoreSR, TotalWeight, ProcessEvent);
         if(fabs(ProcessEvent.CosThetaLepW) > 0.5 && fabs(ProcessEvent.CosThetaLepZ) > 0.5) myhists->BDTScoreSR_WHZH->FillFake(iThread, BDTScoreSR, TotalWeight, ProcessEvent);
       }
       if(isBDTSR100){
         myhists->BDTScoreSR100->FillFake(iThread, BDTScoreSR100, TotalWeight, ProcessEvent);
       }
     }
   }

}

#endif
