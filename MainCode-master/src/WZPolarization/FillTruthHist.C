#ifndef WZPol_FillTruthHist_cxx
#define WZPol_FillTruthHist_cxx

#include <iostream>
#include "WZPolarization/loopWZPolarization.h"

using namespace std;

void loopWZPolarization::FillTruthHist(EventWZPolarization ProcessEvent)
{
   int MCType = ProcessEvent.MCType;

//   TotalWeight = ProcessEvent.WeightNormalized * ProcessEvent.Lep1WeightZ * ProcessEvent.Lep2WeightZ * ProcessEvent.Lep3WeightW;
//   TotalWeight = ProcessEvent.WeightNormalized;

   ProcessEvent.TotalWeight = ProcessEvent.TotalWeightNoKFactor;
   ProcessEvent.passWZInclusive = ProcessEvent.passHardWZInclusive;
   if(ProcessEvent.isTauEvent) return;

   if(isRunReweightingFactor){
     myhists->Pt_WZ->FillTruth(iThread, ProcessEvent.Pt_WZ, ProcessEvent.TotalWeight, ProcessEvent);
     
     return;
   }

   TotalWeight = ProcessEvent.TotalWeight * ProcessEvent.passWZInclusive * ProcessEvent.passSignalRegion;
   myhists->M_WZ->FillTruth(iThread, ProcessEvent.M_WZ, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Mt_WZ->FillTruth(iThread, ProcessEvent.Mt_WZ, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->M_Z->FillTruth(iThread, ProcessEvent.M_Z, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Mt_W->FillTruth(iThread, ProcessEvent.Mt_W, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Met->FillTruth(iThread, ProcessEvent.Met, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Njets->FillTruth(iThread, ProcessEvent.Njets, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->NBjets->FillTruth(iThread, ProcessEvent.NBjets, ProcessEvent.TotalWeight, ProcessEvent);
/*   myhists->Lep1Pt->FillTruth(iThread, ProcessEvent.Lep1Pt, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Lep2Pt->FillTruth(iThread, ProcessEvent.Lep2Pt, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Lep3Pt->FillTruth(iThread, ProcessEvent.Lep3Pt, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Lep1Eta->FillTruth(iThread, ProcessEvent.Lep1Eta, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Lep2Eta->FillTruth(iThread, ProcessEvent.Lep2Eta, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Lep3Eta->FillTruth(iThread, ProcessEvent.Lep3Eta, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Lep1Phi->FillTruth(iThread, ProcessEvent.Lep1Phi, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Lep2Phi->FillTruth(iThread, ProcessEvent.Lep2Phi, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Lep3Phi->FillTruth(iThread, ProcessEvent.Lep3Phi, ProcessEvent.TotalWeight, ProcessEvent);
*/
   myhists->LepPt->FillTruth(iThread, ProcessEvent.Lep1Pt, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->LepPt->FillTruth(iThread, ProcessEvent.Lep2Pt, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->LepPt->FillTruth(iThread, ProcessEvent.Lep3Pt, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->LepEta->FillTruth(iThread, ProcessEvent.Lep1Eta, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->LepEta->FillTruth(iThread, ProcessEvent.Lep2Eta, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->LepEta->FillTruth(iThread, ProcessEvent.Lep3Eta, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->LepPhi->FillTruth(iThread, ProcessEvent.Lep1Phi, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->LepPhi->FillTruth(iThread, ProcessEvent.Lep2Phi, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->LepPhi->FillTruth(iThread, ProcessEvent.Lep3Phi, ProcessEvent.TotalWeight, ProcessEvent);
   //myhists->Mpx->FillTruth(iThread, ProcessEvent.Mpx, ProcessEvent.TotalWeight, ProcessEvent);
   //myhists->Mpy->FillTruth(iThread, ProcessEvent.Mpy, ProcessEvent.TotalWeight, ProcessEvent);
   //myhists->Mpz->FillTruth(iThread, ProcessEvent.Mpz, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Pt_W->FillTruth(iThread, ProcessEvent.Pt_W, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Pt_Z->FillTruth(iThread, ProcessEvent.Pt_Z, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->Pt_WZ->FillTruth(iThread, ProcessEvent.Pt_WZ, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->CosThetaV->FillTruth(iThread, ProcessEvent.CosThetaV, ProcessEvent.TotalWeight, ProcessEvent);
   if(fabs(ProcessEvent.CosThetaLepW) < 0.4 && fabs(ProcessEvent.CosThetaLepZ) < 0.4) myhists->CosThetaV_WLZL->FillTruth(iThread, ProcessEvent.CosThetaV, ProcessEvent.TotalWeight, ProcessEvent);
   if(fabs(ProcessEvent.CosThetaLepW) < 0.4 && fabs(ProcessEvent.CosThetaLepZ) > 0.4) myhists->CosThetaV_WLZH->FillTruth(iThread, ProcessEvent.CosThetaV, ProcessEvent.TotalWeight, ProcessEvent);
   if(fabs(ProcessEvent.CosThetaLepW) > 0.4 && fabs(ProcessEvent.CosThetaLepZ) < 0.4) myhists->CosThetaV_WHZL->FillTruth(iThread, ProcessEvent.CosThetaV, ProcessEvent.TotalWeight, ProcessEvent);
   if(fabs(ProcessEvent.CosThetaLepW) > 0.4 && fabs(ProcessEvent.CosThetaLepZ) > 0.4) myhists->CosThetaV_WHZH->FillTruth(iThread, ProcessEvent.CosThetaV, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->CosThetaVAbs->FillTruth(iThread, fabs(ProcessEvent.CosThetaV), ProcessEvent.TotalWeight, ProcessEvent);
   myhists->CosThetaLepW->FillTruth(iThread, ProcessEvent.CosThetaLepW, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->CosThetaLepZ->FillTruth(iThread, ProcessEvent.CosThetaLepZ, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->DY_WZ->FillTruth(iThread, ProcessEvent.DY_WZ, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->DY_3Z->FillTruth(iThread, ProcessEvent.DY_3Z, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->DY_3N->FillTruth(iThread, ProcessEvent.DY_3N, ProcessEvent.TotalWeight, ProcessEvent);
   myhists->DeltaPhiLepWLepZ->FillTruth(iThread, ProcessEvent.DeltaPhiLepWLepZ, ProcessEvent.TotalWeight, ProcessEvent);
   if(fabs(ProcessEvent.CosThetaLepW) < 0.4 && fabs(ProcessEvent.CosThetaLepZ) < 0.4) myhists->DeltaPhiLepWLepZ_WLZL->FillTruth(iThread, ProcessEvent.DeltaPhiLepWLepZ, ProcessEvent.TotalWeight, ProcessEvent);
   if(fabs(ProcessEvent.CosThetaLepW) < 0.4 && fabs(ProcessEvent.CosThetaLepZ) > 0.4) myhists->DeltaPhiLepWLepZ_WLZH->FillTruth(iThread, ProcessEvent.DeltaPhiLepWLepZ, ProcessEvent.TotalWeight, ProcessEvent);
   if(fabs(ProcessEvent.CosThetaLepW) > 0.4 && fabs(ProcessEvent.CosThetaLepZ) < 0.4) myhists->DeltaPhiLepWLepZ_WHZL->FillTruth(iThread, ProcessEvent.DeltaPhiLepWLepZ, ProcessEvent.TotalWeight, ProcessEvent);
   if(fabs(ProcessEvent.CosThetaLepW) > 0.4 && fabs(ProcessEvent.CosThetaLepZ) > 0.4) myhists->DeltaPhiLepWLepZ_WHZH->FillTruth(iThread, ProcessEvent.DeltaPhiLepWLepZ, ProcessEvent.TotalWeight, ProcessEvent);
/*   myhists->DeltaPhiLepWLepZWZFrame->FillTruth(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, ProcessEvent.TotalWeight, ProcessEvent);
   if(fabs(ProcessEvent.CosThetaLepW) < 0.4 && fabs(ProcessEvent.CosThetaLepZ) < 0.4) myhists->DeltaPhiLepWLepZWZFrame_WLZL->FillTruth(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, ProcessEvent.TotalWeight, ProcessEvent);
   if(fabs(ProcessEvent.CosThetaLepW) < 0.4 && fabs(ProcessEvent.CosThetaLepZ) > 0.4) myhists->DeltaPhiLepWLepZWZFrame_WLZH->FillTruth(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, ProcessEvent.TotalWeight, ProcessEvent);
   if(fabs(ProcessEvent.CosThetaLepW) > 0.4 && fabs(ProcessEvent.CosThetaLepZ) < 0.4) myhists->DeltaPhiLepWLepZWZFrame_WHZL->FillTruth(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, ProcessEvent.TotalWeight, ProcessEvent);
   if(fabs(ProcessEvent.CosThetaLepW) > 0.4 && fabs(ProcessEvent.CosThetaLepZ) > 0.4) myhists->DeltaPhiLepWLepZWZFrame_WHZH->FillTruth(iThread, ProcessEvent.DeltaPhiLepWLepZWZFrame, ProcessEvent.TotalWeight, ProcessEvent);
*/
   myhists->R21->FillTruth(iThread, ProcessEvent.R21, ProcessEvent.TotalWeight, ProcessEvent);
   //if(fabs(ProcessEvent.CosThetaLepW) < 0.4 && fabs(ProcessEvent.CosThetaLepZ) < 0.4) myhists->R21_WLZL->FillTruth(iThread, ProcessEvent.R21, ProcessEvent.TotalWeight, ProcessEvent);
   //if(fabs(ProcessEvent.CosThetaLepW) < 0.4 && fabs(ProcessEvent.CosThetaLepZ) > 0.4) myhists->R21_WLZH->FillTruth(iThread, ProcessEvent.R21, ProcessEvent.TotalWeight, ProcessEvent);
   //if(fabs(ProcessEvent.CosThetaLepW) > 0.4 && fabs(ProcessEvent.CosThetaLepZ) < 0.4) myhists->R21_WHZL->FillTruth(iThread, ProcessEvent.R21, ProcessEvent.TotalWeight, ProcessEvent);
   //if(fabs(ProcessEvent.CosThetaLepW) > 0.4 && fabs(ProcessEvent.CosThetaLepZ) > 0.4) myhists->R21_WHZH->FillTruth(iThread, ProcessEvent.R21, ProcessEvent.TotalWeight, ProcessEvent);



     double ReweightFactor;
     if(isHaveReweightingFactor) ReweightFactor = myhists->ReweightFactor_Truth->GetBinContent(myhists->ReweightFactor_Truth->FindBin(ProcessEvent.Pt_WZ));
     if(!isHaveReweightingFactor) ReweightFactor = 1.0;


}

#endif
