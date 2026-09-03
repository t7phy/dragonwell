#ifndef ZPrime_FillHist_cxx
#define ZPrime_FillHist_cxx

#include <iostream>
#include "ZPrime/loopZPrime.h"

using namespace std;

void loopZPrime::FillHist(EventZPrime ProcessEvent)
{
 double RecoWeight = (ProcessEvent.RecoWeight == ProcessEvent.RecoWeight) ? ProcessEvent.RecoWeight : 0;
 ProcessEvent.RecoWeight = RecoWeight;

// if(isData) RecoWeight = 1.0;

 ProcessEvent.isZeeIncOverlap = (ProcessEvent.RecoDilMass > 120.0)
                             && (ProcessEvent.mcChannelNumber >= 700786 && ProcessEvent.mcChannelNumber <= 700788);

 if(isAdditionalWeight) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * ProcessEvent.AdditionalWeight;
 if(isChangeNorm) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * ProcessEvent.Normalization;

 ProcessEvent.passSelectionEl = (ProcessEvent.eeChannel && !ProcessEvent.mumuChannel && !ProcessEvent.emuChannel)
                             && (ProcessEvent.RecoDilMass > 130.0)
                             && (ProcessEvent.Lepton1_Pt > 30.0)
                             && (ProcessEvent.Lepton2_Pt > 30.0)
                             && !(ProcessEvent.isZeeIncOverlap);

 ProcessEvent.passSelectionMu = (!ProcessEvent.eeChannel && ProcessEvent.mumuChannel && !ProcessEvent.emuChannel)
                             && (ProcessEvent.RecoDilMass > 130.0)
                             && (ProcessEvent.Lepton1_Pt > 30.0)
                             && (ProcessEvent.Lepton2_Pt > 30.0)
                             && !(ProcessEvent.isZeeIncOverlap);

 if(isTruthRun){
   ProcessEvent.passSelectionEl = 1;
   ProcessEvent.passSelectionMu = 1;
 }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 TLorentzVector Lepton, Antilepton, ZBoson;

 if(ProcessEvent.n_born_lepton == 2){
   if(ProcessEvent.born_lepton1_pdgid > 0 && ProcessEvent.born_lepton2_pdgid < 0){
     Lepton.SetPtEtaPhiE(ProcessEvent.born_lepton1_pt, ProcessEvent.born_lepton1_eta, ProcessEvent.born_lepton1_phi, ProcessEvent.born_lepton1_E);
     Antilepton.SetPtEtaPhiE(ProcessEvent.born_lepton2_pt, ProcessEvent.born_lepton2_eta, ProcessEvent.born_lepton2_phi, ProcessEvent.born_lepton2_E);
   }
   else if(ProcessEvent.born_lepton2_pdgid > 0 && ProcessEvent.born_lepton1_pdgid < 0){
     Antilepton.SetPtEtaPhiE(ProcessEvent.born_lepton1_pt, ProcessEvent.born_lepton1_eta, ProcessEvent.born_lepton1_phi, ProcessEvent.born_lepton1_E);
     Lepton.SetPtEtaPhiE(ProcessEvent.born_lepton2_pt, ProcessEvent.born_lepton2_eta, ProcessEvent.born_lepton2_phi, ProcessEvent.born_lepton2_E);
   }
   else{
     cout<<"ERROR! no lepton-antilepton pair."<<endl;
   }
 }

 bool isZU = false;
 bool isZD = false;

 isZU = ((fabs(ProcessEvent.pdf_pdgId1) == 2 || fabs(ProcessEvent.pdf_pdgId2) == 2)
      || (fabs(ProcessEvent.pdf_pdgId1) == 4 || fabs(ProcessEvent.pdf_pdgId2) == 4)
      || (fabs(ProcessEvent.pdf_pdgId1) == 6 || fabs(ProcessEvent.pdf_pdgId2) == 6))
      && (ProcessEvent.n_born_lepton == 2);

 isZD = ((fabs(ProcessEvent.pdf_pdgId1) == 1 || fabs(ProcessEvent.pdf_pdgId2) == 1)
      || (fabs(ProcessEvent.pdf_pdgId1) == 3 || fabs(ProcessEvent.pdf_pdgId2) == 3)
      || (fabs(ProcessEvent.pdf_pdgId1) == 5 || fabs(ProcessEvent.pdf_pdgId2) == 5))
      && (ProcessEvent.n_born_lepton == 2);

 ZBoson = Lepton + Antilepton;
 double CosThetaCS = calculate_theta(ZBoson, Lepton, Antilepton) * ZBoson.Rapidity() / fabs(ZBoson.Rapidity());
 double PhiCS = calculate_phi(Lepton, Antilepton, 13600.0 / 2.0);

 myhists->L0_Mass_QT_ZY_uu->at(iThread - 1)->Initial(CosThetaCS, PhiCS);
 myhists->L0_Mass_QT_ZY_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), fabs(ZBoson.Rapidity()), ProcessEvent.TotalWeight * isZU);
 myhists->A0_Mass_QT_ZY_uu->at(iThread - 1)->Initial(CosThetaCS, PhiCS);
 myhists->A0_Mass_QT_ZY_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), fabs(ZBoson.Rapidity()), ProcessEvent.TotalWeight * isZU);
 myhists->A1_Mass_QT_ZY_uu->at(iThread - 1)->Initial(CosThetaCS, PhiCS);
 myhists->A1_Mass_QT_ZY_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), fabs(ZBoson.Rapidity()), ProcessEvent.TotalWeight * isZU);
 myhists->A2_Mass_QT_ZY_uu->at(iThread - 1)->Initial(CosThetaCS, PhiCS);
 myhists->A2_Mass_QT_ZY_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), fabs(ZBoson.Rapidity()), ProcessEvent.TotalWeight * isZU);
 myhists->A3_Mass_QT_ZY_uu->at(iThread - 1)->Initial(CosThetaCS, PhiCS);
 myhists->A3_Mass_QT_ZY_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), fabs(ZBoson.Rapidity()), ProcessEvent.TotalWeight * isZU);
 myhists->A4_Mass_QT_ZY_uu->at(iThread - 1)->Initial(CosThetaCS, PhiCS);
 myhists->A4_Mass_QT_ZY_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), fabs(ZBoson.Rapidity()), ProcessEvent.TotalWeight * isZU);

 myhists->L0_Mass_QT_ZY_dd->at(iThread - 1)->Initial(CosThetaCS, PhiCS);
 myhists->L0_Mass_QT_ZY_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), fabs(ZBoson.Rapidity()), ProcessEvent.TotalWeight * isZD);
 myhists->A0_Mass_QT_ZY_dd->at(iThread - 1)->Initial(CosThetaCS, PhiCS);
 myhists->A0_Mass_QT_ZY_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), fabs(ZBoson.Rapidity()), ProcessEvent.TotalWeight * isZD);
 myhists->A1_Mass_QT_ZY_dd->at(iThread - 1)->Initial(CosThetaCS, PhiCS);
 myhists->A1_Mass_QT_ZY_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), fabs(ZBoson.Rapidity()), ProcessEvent.TotalWeight * isZD);
 myhists->A2_Mass_QT_ZY_dd->at(iThread - 1)->Initial(CosThetaCS, PhiCS);
 myhists->A2_Mass_QT_ZY_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), fabs(ZBoson.Rapidity()), ProcessEvent.TotalWeight * isZD);
 myhists->A3_Mass_QT_ZY_dd->at(iThread - 1)->Initial(CosThetaCS, PhiCS);
 myhists->A3_Mass_QT_ZY_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), fabs(ZBoson.Rapidity()), ProcessEvent.TotalWeight * isZD);
 myhists->A4_Mass_QT_ZY_dd->at(iThread - 1)->Initial(CosThetaCS, PhiCS);
 myhists->A4_Mass_QT_ZY_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), fabs(ZBoson.Rapidity()), ProcessEvent.TotalWeight * isZD);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 ProcessEvent.passSelectionElMu = (!ProcessEvent.eeChannel && !ProcessEvent.mumuChannel && ProcessEvent.emuChannel)
                               && (ProcessEvent.RecoDilMass > 130.0)
                               && (ProcessEvent.Lepton1_Pt > 30.0)
                               && (ProcessEvent.Lepton2_Pt > 30.0)
                               && !(ProcessEvent.isZeeIncOverlap);


 if(doTopDD){
   topDD->GetWeight(ProcessEvent.RecoDilMass);
   ProcessEvent.topTransferEl = topDD->Weight_ee;
   ProcessEvent.topTransferMu = topDD->Weight_mm;

   topDD_HighMass_CosTheta->GetWeight(ProcessEvent.RecoDilMass, ProcessEvent.RecoCosThetaStar);
   ProcessEvent.topTransferEl_HighMass_CosTheta = topDD_HighMass_CosTheta->Weight_ee;
   ProcessEvent.topTransferMu_HighMass_CosTheta = topDD_HighMass_CosTheta->Weight_mm;

   topDD_HighMass_Rapidity->GetWeight(ProcessEvent.RecoDilMass, fabs(ProcessEvent.RecoDilRapidity));
   ProcessEvent.topTransferEl_HighMass_Rapidity = topDD_HighMass_Rapidity->Weight_ee;
   ProcessEvent.topTransferMu_HighMass_Rapidity = topDD_HighMass_Rapidity->Weight_mm;

   if(ZPrimeTree->SystematicName.Contains("TopDD_Mass_Stat__1up")){
     topDD->GetWeightStatUp(ProcessEvent.RecoDilMass);
     ProcessEvent.topTransferEl = topDD->Weight_ee;
     ProcessEvent.topTransferMu = topDD->Weight_mm;
   }
   if(ZPrimeTree->SystematicName.Contains("TopDD_Mass_Stat__1down")){
     topDD->GetWeightStatDown(ProcessEvent.RecoDilMass);
     ProcessEvent.topTransferEl = topDD->Weight_ee;
     ProcessEvent.topTransferMu = topDD->Weight_mm;
   }
   if(ZPrimeTree->SystematicName.Contains("TopDD_Mass_CosTheta_Stat__1up")){
     topDD_HighMass_CosTheta->GetWeightStatUp(ProcessEvent.RecoDilMass, ProcessEvent.RecoCosThetaStar);
     ProcessEvent.topTransferEl_HighMass_CosTheta = topDD_HighMass_CosTheta->Weight_ee;
     ProcessEvent.topTransferMu_HighMass_CosTheta = topDD_HighMass_CosTheta->Weight_mm;
   }
   if(ZPrimeTree->SystematicName.Contains("TopDD_Mass_CosTheta_Stat__1down")){
     topDD_HighMass_CosTheta->GetWeightStatDown(ProcessEvent.RecoDilMass, ProcessEvent.RecoCosThetaStar);
     ProcessEvent.topTransferEl_HighMass_CosTheta = topDD_HighMass_CosTheta->Weight_ee;
     ProcessEvent.topTransferMu_HighMass_CosTheta = topDD_HighMass_CosTheta->Weight_mm;
   }
   if(ZPrimeTree->SystematicName.Contains("TopDD_Mass_Rapidity_Stat__1up")){
     topDD_HighMass_Rapidity->GetWeightStatUp(ProcessEvent.RecoDilMass, fabs(ProcessEvent.RecoDilRapidity));
     ProcessEvent.topTransferEl_HighMass_Rapidity = topDD_HighMass_Rapidity->Weight_ee;
     ProcessEvent.topTransferMu_HighMass_Rapidity = topDD_HighMass_Rapidity->Weight_mm;
   }
   if(ZPrimeTree->SystematicName.Contains("TopDD_Mass_Rapidity_Stat__1down")){
     topDD_HighMass_Rapidity->GetWeightStatDown(ProcessEvent.RecoDilMass, fabs(ProcessEvent.RecoDilRapidity));
     ProcessEvent.topTransferEl_HighMass_Rapidity = topDD_HighMass_Rapidity->Weight_ee;
     ProcessEvent.topTransferMu_HighMass_Rapidity = topDD_HighMass_Rapidity->Weight_mm;
   }
 }

 if(ProcessEvent.passSelectionElMu || (MCType == "Wjets_DD" && ProcessEvent.passSelectionMu)){
   TLorentzVector Lepton1;
   TLorentzVector Lepton2;
   Lepton1.SetPtEtaPhiM(ProcessEvent.Lepton1_Pt, ProcessEvent.Lepton1_Eta, ProcessEvent.Lepton1_Phi, 0.0);
   Lepton2.SetPtEtaPhiM(ProcessEvent.Lepton2_Pt, ProcessEvent.Lepton2_Eta, ProcessEvent.Lepton2_Phi, 0.0);
   ProcessEvent.RecoPhiStar = calculate_phi_eta(Lepton1, Lepton2);
 }

 ProcessEvent.passElFake = (ProcessEvent.MET_Et < 25.0)
                        && !(ProcessEvent.Lepton1_passMediumID && ProcessEvent.Lepton2_passMediumID)
                        && (fabs(ProcessEvent.RecoDilMass - 91.1876) > 20.0)
                        && !(ProcessEvent.isZeeIncOverlap);

 ProcessEvent.passElFake = !(ProcessEvent.Lepton1_passMediumID && ProcessEvent.Lepton2_passMediumID)
                        && (fabs(ProcessEvent.RecoDilMass - 91.1876) > 20.0)
                        && !(ProcessEvent.isZeeIncOverlap);

 ProcessEvent.passElFake_MET_up = (ProcessEvent.MET_Et < 15.0)
                        && !(ProcessEvent.Lepton1_passMediumID && ProcessEvent.Lepton2_passMediumID)
                        && (fabs(ProcessEvent.RecoDilMass - 91.1876) > 20.0)
                        && !(ProcessEvent.isZeeIncOverlap);

 ProcessEvent.passElFake_MET_down = (ProcessEvent.MET_Et < 35.0)
                        && !(ProcessEvent.Lepton1_passMediumID && ProcessEvent.Lepton2_passMediumID)
                        && (fabs(ProcessEvent.RecoDilMass - 91.1876) > 20.0)
                        && !(ProcessEvent.isZeeIncOverlap);

 ProcessEvent.passMuFake = (fabs(ProcessEvent.RecoDilMass - 91.1876) < 20.0)
                        && (ProcessEvent.Lepton1_isTight && ProcessEvent.Lepton2_isTight)
                        && (fabs(ProcessEvent.Lepton3_d0sig) > 3.0)
                        && !(ProcessEvent.isZeeIncOverlap);

 ProcessEvent.passMuFake_d0sig_up = (fabs(ProcessEvent.RecoDilMass - 91.1876) < 20.0)
                        && (ProcessEvent.Lepton1_isTight && ProcessEvent.Lepton2_isTight)
                        && (fabs(ProcessEvent.Lepton3_d0sig) > 3.5)
                        && !(ProcessEvent.isZeeIncOverlap);

 ProcessEvent.passMuFake_d0sig_down = (fabs(ProcessEvent.RecoDilMass - 91.1876) < 20.0)
                        && (ProcessEvent.Lepton1_isTight && ProcessEvent.Lepton2_isTight)
                        && (fabs(ProcessEvent.Lepton3_d0sig) > 2.5)
                        && !(ProcessEvent.isZeeIncOverlap);

 if(doFakeBkg){
   WeightRun->GetFakeRate(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta));
   ProcessEvent.Lepton1_FakeRate = WeightRun->Lepton1_FakeRate;
   ProcessEvent.Lepton2_FakeRate = WeightRun->Lepton2_FakeRate;

   WeightRun_Stat_up->GetFakeRate(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta));
   ProcessEvent.Lepton1_FakeRate_Stat_up = WeightRun_Stat_up->Lepton1_FakeRate;
   ProcessEvent.Lepton2_FakeRate_Stat_up = WeightRun_Stat_up->Lepton2_FakeRate;

   WeightRun_Stat_down->GetFakeRate(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta));
   ProcessEvent.Lepton1_FakeRate_Stat_down = WeightRun_Stat_down->Lepton1_FakeRate;
   ProcessEvent.Lepton2_FakeRate_Stat_down = WeightRun_Stat_down->Lepton2_FakeRate;

   WeightRun_PromptSubtr_up->GetFakeRate(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta));
   ProcessEvent.Lepton1_FakeRate_PromptSubtr_up = WeightRun_PromptSubtr_up->Lepton1_FakeRate;
   ProcessEvent.Lepton2_FakeRate_PromptSubtr_up = WeightRun_PromptSubtr_up->Lepton2_FakeRate;
 
   WeightRun_PromptSubtr_down->GetFakeRate(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta));
   ProcessEvent.Lepton1_FakeRate_PromptSubtr_down = WeightRun_PromptSubtr_down->Lepton1_FakeRate;
   ProcessEvent.Lepton2_FakeRate_PromptSubtr_down = WeightRun_PromptSubtr_down->Lepton2_FakeRate;

   WeightRun_MET_up->GetFakeRate(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta));
   ProcessEvent.Lepton1_FakeRate_MET_up = WeightRun_MET_up->Lepton1_FakeRate;
   ProcessEvent.Lepton2_FakeRate_MET_up = WeightRun_MET_up->Lepton2_FakeRate;

   WeightRun_MET_down->GetFakeRate(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta));
   ProcessEvent.Lepton1_FakeRate_MET_down = WeightRun_MET_down->Lepton1_FakeRate;
   ProcessEvent.Lepton2_FakeRate_MET_down = WeightRun_MET_down->Lepton2_FakeRate;
 }

 myhists->Mll_HighMass->Fill(iThread, ProcessEvent.RecoDilMass, 1.0, ProcessEvent);
 myhists->Mll_FineBin->Fill(iThread, ProcessEvent.RecoDilMass, 1.0, ProcessEvent);
 //myhists->Mll_LowMass->Fill(iThread, ProcessEvent.RecoDilMass, 1.0, ProcessEvent);
 myhists->pTll->Fill(iThread, ProcessEvent.RecoDilPt, 1.0, ProcessEvent);
 //myhists->costheta->Fill(iThread, ProcessEvent.RecoCosThetaStar, 1.0, ProcessEvent);
 myhists->DilRapidity->Fill(iThread, fabs(ProcessEvent.RecoDilRapidity), 1.0, ProcessEvent);
 //myhists->PhiStar->Fill(iThread, ProcessEvent.RecoPhiStar, 1.0, ProcessEvent);
 myhists->LeadingLepEta->Fill(iThread, ProcessEvent.Lepton1_Eta, 1.0, ProcessEvent);
 myhists->SubleadingLepEta->Fill(iThread, ProcessEvent.Lepton2_Eta, 1.0, ProcessEvent);
 myhists->LeadingLepPhi->Fill(iThread, ProcessEvent.Lepton1_Phi, 1.0, ProcessEvent);
 myhists->SubleadingLepPhi->Fill(iThread, ProcessEvent.Lepton2_Phi, 1.0, ProcessEvent);
 myhists->LeadingLepPt->Fill(iThread, ProcessEvent.Lepton1_Pt, 1.0, ProcessEvent);
 myhists->SubleadingLepPt->Fill(iThread, ProcessEvent.Lepton2_Pt, 1.0, ProcessEvent);
 //myhists->Lepton1_z0->Fill(iThread, ProcessEvent.Lepton1_z0, 1.0, ProcessEvent);
 //myhists->Lepton2_z0->Fill(iThread, ProcessEvent.Lepton2_z0, 1.0, ProcessEvent);
 //myhists->Lepton1_d0Sig->Fill(iThread, ProcessEvent.Lepton1_d0sig, 1.0, ProcessEvent);
 //myhists->Lepton2_d0Sig->Fill(iThread, ProcessEvent.Lepton2_d0sig, 1.0, ProcessEvent);

 //myhists->DilRapidity_HighMass->Fill(iThread, fabs(ProcessEvent.RecoDilRapidity), (ProcessEvent.RecoDilMass > 200.0), ProcessEvent);
 //myhists->DilRapidity_LowMass->Fill(iThread, fabs(ProcessEvent.RecoDilRapidity), (ProcessEvent.RecoDilMass < 200.0), ProcessEvent);

 //myhists->HighMass_CosTheta->Fill(iThread, ProcessEvent.RecoDilMass, ProcessEvent.RecoCosThetaStar, 1.0, ProcessEvent);
 //myhists->HighMass_Rapidity->Fill(iThread, ProcessEvent.RecoDilMass, fabs(ProcessEvent.RecoDilRapidity), 1.0, ProcessEvent);

 myhists->LooseLepton1Eta->Fill(iThread, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_passLooseID * ProcessEvent.Lepton1_LooseWeight, ProcessEvent);
 myhists->LooseLepton1Pt->Fill(iThread, ProcessEvent.Lepton1_Pt, ProcessEvent.Lepton1_passLooseID * ProcessEvent.Lepton1_LooseWeight, ProcessEvent);

 //myhists->LooseLepton3Eta->Fill(iThread, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.Lepton3_passLooseID * ProcessEvent.Lepton3_LooseWeight, ProcessEvent);
 //myhists->LooseLepton3Pt->Fill(iThread, ProcessEvent.Lepton3_Pt, ProcessEvent.Lepton3_passLooseID * ProcessEvent.Lepton3_LooseWeight, ProcessEvent);
 //myhists->LooseMass_eem->Fill(iThread, ProcessEvent.RecoDilMass, ProcessEvent.Lepton3_passLooseID * ProcessEvent.Lepton3_LooseWeight, ProcessEvent);
 //myhists->LooseLepton3_d0Sig_eem->Fill(iThread, fabs(ProcessEvent.Lepton3_d0sig), ProcessEvent.Lepton3_passLooseID * ProcessEvent.Lepton3_LooseWeight, ProcessEvent);

 myhists->TightLepton1Eta->Fill(iThread, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_isTight * ProcessEvent.Lepton1_TightWeight, ProcessEvent);
 myhists->TightLepton1Pt->Fill(iThread, ProcessEvent.Lepton1_Pt, ProcessEvent.Lepton1_isTight * ProcessEvent.Lepton1_TightWeight, ProcessEvent);

 //myhists->TightLepton3Eta->Fill(iThread, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.Lepton3_isTight * ProcessEvent.Lepton3_TightWeight, ProcessEvent);
 //myhists->TightLepton3Pt->Fill(iThread, ProcessEvent.Lepton3_Pt, ProcessEvent.Lepton3_isTight * ProcessEvent.Lepton3_TightWeight, ProcessEvent);
 //myhists->TightMass_eem->Fill(iThread, ProcessEvent.RecoDilMass, ProcessEvent.Lepton3_isTight * ProcessEvent.Lepton3_TightWeight, ProcessEvent);
 //myhists->TightLepton3_d0Sig_eem->Fill(iThread, fabs(ProcessEvent.Lepton3_d0sig), ProcessEvent.Lepton3_isTight * ProcessEvent.Lepton3_TightWeight, ProcessEvent);

 //myhists->LeptonPtClosure->Fill(iThread, ProcessEvent.Lepton1_Pt, 1.0, ProcessEvent);

 if(isLooseTree){
   // Real Efficiency
   if(MCType == "DrellYan"){
   //if(MCType == "DrellYan" || MCType == "Diboson" || MCType == "TopQuark" || MCType == "PhotonInduced" || MCType == "Ztautau"){
     TLorentzVector Lepton1, Lepton2;
     Lepton1.SetPtEtaPhiM(ProcessEvent.Lepton1_Pt, ProcessEvent.Lepton1_Eta, ProcessEvent.Lepton1_Phi, 0.0);
     Lepton2.SetPtEtaPhiM(ProcessEvent.Lepton2_Pt, ProcessEvent.Lepton2_Eta, ProcessEvent.Lepton2_Phi, 0.0);
     double dR = Lepton1.DeltaR(Lepton2);

     double Lepton1LooseWeight = ProcessEvent.TotalWeightLoose * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton1_passIso;
     double Lepton2LooseWeight = ProcessEvent.TotalWeightLoose * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton2_passIso;
     double Lepton1TightWeight = ProcessEvent.TotalWeightLoose * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton1_passIso;
     double Lepton2TightWeight = ProcessEvent.TotalWeightLoose * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton2_passIso;
     double Lepton1MediumIDWeight = ProcessEvent.TotalWeightLoose * ProcessEvent.Lepton1_MediumIDWeight;
     double Lepton2MediumIDWeight = ProcessEvent.TotalWeightLoose * ProcessEvent.Lepton2_MediumIDWeight;
     double Lepton1LooseIsoWeight = ProcessEvent.TotalWeightLoose * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton1_IsoWeight;
     double Lepton2LooseIsoWeight = ProcessEvent.TotalWeightLoose * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton2_IsoWeight;

     double TruthWeight = ProcessEvent.RecoWeight;

     bool passRealEl = (ProcessEvent.eeChannel)
                    && (ProcessEvent.RecoDilMass > 130.0)
                    && !(ProcessEvent.isZeeIncOverlap);

     bool passRealMu = ProcessEvent.mumuChannel
                    && (ProcessEvent.RecoDilMass > 130.0)
                    && !(ProcessEvent.isZeeIncOverlap);

     myhists->RealLeptonPtEta_El_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1LooseWeight * passRealEl * ProcessEvent.Lepton1_passLooseID);
     if(ProcessEvent.eeChannel) myhists->RealLeptonPtEta_El_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta), Lepton2LooseWeight * passRealEl * ProcessEvent.Lepton2_passLooseID);
     myhists->RealLeptonPtEta_El_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1TightWeight * passRealEl * ProcessEvent.Lepton1_isTight);
     if(ProcessEvent.eeChannel) myhists->RealLeptonPtEta_El_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta), Lepton2TightWeight * passRealEl * ProcessEvent.Lepton2_isTight);

     myhists->RealLepton1PtEta_El_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1LooseWeight * passRealEl * ProcessEvent.Lepton1_passLooseID);
     if(ProcessEvent.eeChannel) myhists->RealLepton2PtEta_El_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta), Lepton2LooseWeight * passRealEl * ProcessEvent.Lepton2_passLooseID);
     myhists->RealLepton1PtEta_El_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1TightWeight * passRealEl * ProcessEvent.Lepton1_isTight);
     if(ProcessEvent.eeChannel) myhists->RealLepton2PtEta_El_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta), Lepton2TightWeight * passRealEl * ProcessEvent.Lepton2_isTight);

     myhists->RealLepton1Pt2Pt_El_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton1_Pt - ProcessEvent.Lepton2_Pt), Lepton2LooseWeight * passRealEl * ProcessEvent.Lepton2_passLooseID);
     myhists->RealLepton1Pt2Pt_El_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton1_Pt - ProcessEvent.Lepton2_Pt), Lepton2LooseWeight * passRealEl * ProcessEvent.Lepton2_isTight);

     myhists->RealLepton1Pt_FineBin_NoMassCut_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, Lepton1LooseWeight * passRealEl * ProcessEvent.Lepton1_passLooseID);
     myhists->RealLepton1Pt_FineBin_NoMassCut_MediumID->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, Lepton1MediumIDWeight * passRealEl * ProcessEvent.Lepton1_passMediumID);
     myhists->RealLepton1Pt_FineBin_NoMassCut_Iso->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, Lepton1LooseIsoWeight * passRealEl * ProcessEvent.Lepton1_passLooseID * ProcessEvent.Lepton1_passIso);
     myhists->RealLepton1Pt_FineBin_NoMassCut_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, Lepton1TightWeight * passRealEl * ProcessEvent.Lepton1_isTight);
     myhists->RealLepton2Pt_FineBin_NoMassCut_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, Lepton2LooseWeight * passRealEl * ProcessEvent.Lepton2_passLooseID);
     myhists->RealLepton2Pt_FineBin_NoMassCut_MediumID->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, Lepton2MediumIDWeight * passRealEl * ProcessEvent.Lepton2_passMediumID);
     myhists->RealLepton2Pt_FineBin_NoMassCut_Iso->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, Lepton2LooseIsoWeight * passRealEl * ProcessEvent.Lepton2_passLooseID * ProcessEvent.Lepton2_passIso);
     myhists->RealLepton2Pt_FineBin_NoMassCut_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, Lepton2TightWeight * passRealEl * ProcessEvent.Lepton2_isTight);

     myhists->RealLepton1Pt_FineBin_Mass116Cut_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, Lepton1LooseWeight * passRealEl * ProcessEvent.Lepton1_passLooseID * (ProcessEvent.RecoDilMass > 116.0));
     myhists->RealLepton1Pt_FineBin_Mass116Cut_MediumID->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, Lepton1MediumIDWeight * passRealEl * ProcessEvent.Lepton1_passMediumID * (ProcessEvent.RecoDilMass > 116.0));
     myhists->RealLepton1Pt_FineBin_Mass116Cut_Iso->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, Lepton1LooseIsoWeight * passRealEl * ProcessEvent.Lepton1_passLooseID * ProcessEvent.Lepton1_passIso * (ProcessEvent.RecoDilMass > 116.0));
     myhists->RealLepton1Pt_FineBin_Mass116Cut_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, Lepton1TightWeight * passRealEl * ProcessEvent.Lepton1_isTight * (ProcessEvent.RecoDilMass > 116.0));
     myhists->RealLepton2Pt_FineBin_Mass116Cut_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, Lepton2LooseWeight * passRealEl * ProcessEvent.Lepton2_passLooseID * (ProcessEvent.RecoDilMass > 116.0));
     myhists->RealLepton2Pt_FineBin_Mass116Cut_MediumID->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, Lepton2MediumIDWeight * passRealEl * ProcessEvent.Lepton2_passMediumID * (ProcessEvent.RecoDilMass > 116.0));
     myhists->RealLepton2Pt_FineBin_Mass116Cut_Iso->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, Lepton2LooseIsoWeight * passRealEl * ProcessEvent.Lepton2_passLooseID * ProcessEvent.Lepton2_passIso * (ProcessEvent.RecoDilMass > 116.0));
     myhists->RealLepton2Pt_FineBin_Mass116Cut_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, Lepton2TightWeight * passRealEl * ProcessEvent.Lepton2_isTight * (ProcessEvent.RecoDilMass > 116.0));

     double Lepton1_Resolution = (ProcessEvent.Lepton1_Pt - ProcessEvent.TruthLepton1_Born.P4.Pt()) / ProcessEvent.TruthLepton1_Born.P4.Pt();
     double Lepton2_Resolution = (ProcessEvent.Lepton2_Pt - ProcessEvent.TruthLepton2_Born.P4.Pt()) / ProcessEvent.TruthLepton2_Born.P4.Pt();

     myhists->Lepton1PtResolution_NoMassCut_Loose->at(iThread - 1)->Fill(Lepton1_Resolution, ProcessEvent.Lepton1_Pt, Lepton1LooseWeight * passRealEl * ProcessEvent.Lepton1_passLooseID);
     myhists->Lepton1PtResolution_NoMassCut_Tight->at(iThread - 1)->Fill(Lepton1_Resolution, ProcessEvent.Lepton1_Pt, Lepton1TightWeight * passRealEl * ProcessEvent.Lepton1_isTight);
     myhists->Lepton2PtResolution_NoMassCut_Loose->at(iThread - 1)->Fill(Lepton2_Resolution, ProcessEvent.Lepton2_Pt, Lepton2LooseWeight * passRealEl * ProcessEvent.Lepton2_passLooseID);
     myhists->Lepton2PtResolution_NoMassCut_Tight->at(iThread - 1)->Fill(Lepton2_Resolution, ProcessEvent.Lepton2_Pt, Lepton2TightWeight * passRealEl * ProcessEvent.Lepton2_isTight);
     myhists->Lepton1PtResolution_Mass116Cut_Loose->at(iThread - 1)->Fill(Lepton1_Resolution, ProcessEvent.Lepton1_Pt, Lepton1LooseWeight * passRealEl * ProcessEvent.Lepton1_passLooseID * (ProcessEvent.RecoDilMass > 116.0));
     myhists->Lepton1PtResolution_Mass116Cut_Tight->at(iThread - 1)->Fill(Lepton1_Resolution, ProcessEvent.Lepton1_Pt, Lepton1TightWeight * passRealEl * ProcessEvent.Lepton1_isTight * (ProcessEvent.RecoDilMass > 116.0));
     myhists->Lepton2PtResolution_Mass116Cut_Loose->at(iThread - 1)->Fill(Lepton2_Resolution, ProcessEvent.Lepton2_Pt, Lepton2LooseWeight * passRealEl * ProcessEvent.Lepton2_passLooseID * (ProcessEvent.RecoDilMass > 116.0));
     myhists->Lepton2PtResolution_Mass116Cut_Tight->at(iThread - 1)->Fill(Lepton2_Resolution, ProcessEvent.Lepton2_Pt, Lepton2TightWeight * passRealEl * ProcessEvent.Lepton2_isTight * (ProcessEvent.RecoDilMass > 116.0));

     myhists->RealLeptonPtEta_Mu_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1LooseWeight * passRealMu * ProcessEvent.Lepton1_passLooseID);
     myhists->RealLeptonPtEta_Mu_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta), Lepton2LooseWeight * passRealMu * ProcessEvent.Lepton2_passLooseID);
     myhists->RealLeptonPtEta_Mu_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1TightWeight * passRealMu * ProcessEvent.Lepton1_isTight);
     myhists->RealLeptonPtEta_Mu_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta), Lepton2TightWeight * passRealMu * ProcessEvent.Lepton2_isTight);
   }

   // Fake Efficiency
   double Lepton1LooseWeight = ProcessEvent.Lepton1_PrescaleFactor * ProcessEvent.TotalWeightLoose * ProcessEvent.Lepton1_LooseWeight;
   double Lepton1TightWeight = ProcessEvent.Lepton1_PrescaleFactor * ProcessEvent.TotalWeightLoose * ProcessEvent.Lepton1_TightWeight;
   double Lepton3LooseWeight = ProcessEvent.TotalWeightLoose * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton3_LooseWeight;
   double Lepton3TightWeight = ProcessEvent.TotalWeightLoose * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton3_TightWeight;

   if(isData){
     myhists->FakeLeptonPtEta_El_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_PrescaleFactor * ProcessEvent.TotalWeightLoose * ProcessEvent.SingleElectron * ProcessEvent.passElFake * ProcessEvent.Lepton1_passLooseID);
     myhists->FakeLeptonPtEta_El_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_PrescaleFactor * ProcessEvent.TotalWeightLoose * ProcessEvent.SingleElectron * ProcessEvent.passElFake * ProcessEvent.Lepton1_isTight);

     myhists->FakeLeptonPtEta_El_PromptSubtr_up_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_PrescaleFactor * ProcessEvent.TotalWeightLoose * ProcessEvent.SingleElectron * ProcessEvent.passElFake * ProcessEvent.Lepton1_passLooseID);
     myhists->FakeLeptonPtEta_El_PromptSubtr_up_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_PrescaleFactor * ProcessEvent.TotalWeightLoose * ProcessEvent.SingleElectron * ProcessEvent.passElFake * ProcessEvent.Lepton1_isTight);

     myhists->FakeLeptonPtEta_El_PromptSubtr_down_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_PrescaleFactor * ProcessEvent.TotalWeightLoose * ProcessEvent.SingleElectron * ProcessEvent.passElFake * ProcessEvent.Lepton1_passLooseID);
     myhists->FakeLeptonPtEta_El_PromptSubtr_down_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_PrescaleFactor * ProcessEvent.TotalWeightLoose * ProcessEvent.SingleElectron * ProcessEvent.passElFake * ProcessEvent.Lepton1_isTight);

     myhists->FakeLeptonPtEta_El_MET_up_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_PrescaleFactor * ProcessEvent.TotalWeightLoose * ProcessEvent.SingleElectron * ProcessEvent.passElFake_MET_up * ProcessEvent.Lepton1_passLooseID);
     myhists->FakeLeptonPtEta_El_MET_up_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_PrescaleFactor * ProcessEvent.TotalWeightLoose * ProcessEvent.SingleElectron * ProcessEvent.passElFake_MET_up * ProcessEvent.Lepton1_isTight);

     myhists->FakeLeptonPtEta_El_MET_down_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_PrescaleFactor * ProcessEvent.TotalWeightLoose * ProcessEvent.SingleElectron * ProcessEvent.passElFake_MET_down * ProcessEvent.Lepton1_passLooseID);
     myhists->FakeLeptonPtEta_El_MET_down_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_PrescaleFactor * ProcessEvent.TotalWeightLoose * ProcessEvent.SingleElectron * ProcessEvent.passElFake_MET_down * ProcessEvent.Lepton1_isTight);

     // For muon, we use eem event
     myhists->FakeLeptonPtEta_Mu_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_passLooseID);
     myhists->FakeLeptonPtEta_Mu_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_isTight);

     myhists->FakeLeptonPtEta_Mu_PromptSubtr_up_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_passLooseID);
     myhists->FakeLeptonPtEta_Mu_PromptSubtr_up_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_isTight);

     myhists->FakeLeptonPtEta_Mu_PromptSubtr_down_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_passLooseID);
     myhists->FakeLeptonPtEta_Mu_PromptSubtr_down_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_isTight);

     myhists->FakeLeptonPtEta_Mu_d0sig_up_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake_d0sig_up * ProcessEvent.Lepton3_passLooseID);
     myhists->FakeLeptonPtEta_Mu_d0sig_up_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake_d0sig_up * ProcessEvent.Lepton3_isTight);

     myhists->FakeLeptonPtEta_Mu_d0sig_down_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake_d0sig_down * ProcessEvent.Lepton3_passLooseID);
     myhists->FakeLeptonPtEta_Mu_d0sig_down_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake_d0sig_down * ProcessEvent.Lepton3_isTight);


     myhists->FakeLeptonPt_Mu_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_passLooseID);
     myhists->FakeLeptonPt_Mu_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_isTight);
   }
   else{
     myhists->FakeLeptonPtEta_El_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1LooseWeight * ProcessEvent.SingleElectron * ProcessEvent.passElFake * ProcessEvent.Lepton1_passLooseID * (-1.0));
     myhists->FakeLeptonPtEta_El_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1TightWeight * ProcessEvent.SingleElectron * ProcessEvent.passElFake * ProcessEvent.Lepton1_isTight * (-1.0));

     myhists->FakeLeptonPtEta_El_PromptSubtr_up_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1LooseWeight * ProcessEvent.SingleElectron * ProcessEvent.passElFake * ProcessEvent.Lepton1_passLooseID * (-0.9));
     myhists->FakeLeptonPtEta_El_PromptSubtr_up_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1TightWeight * ProcessEvent.SingleElectron * ProcessEvent.passElFake * ProcessEvent.Lepton1_isTight * (-0.9));

     myhists->FakeLeptonPtEta_El_PromptSubtr_down_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1LooseWeight * ProcessEvent.SingleElectron * ProcessEvent.passElFake * ProcessEvent.Lepton1_passLooseID * (-1.1));
     myhists->FakeLeptonPtEta_El_PromptSubtr_down_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1TightWeight * ProcessEvent.SingleElectron * ProcessEvent.passElFake * ProcessEvent.Lepton1_isTight * (-1.1));

     myhists->FakeLeptonPtEta_El_MET_up_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1LooseWeight * ProcessEvent.SingleElectron * ProcessEvent.passElFake_MET_up * ProcessEvent.Lepton1_passLooseID * (-1.0));
     myhists->FakeLeptonPtEta_El_MET_up_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1TightWeight * ProcessEvent.SingleElectron * ProcessEvent.passElFake_MET_up * ProcessEvent.Lepton1_isTight * (-1.0));

     myhists->FakeLeptonPtEta_El_MET_down_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1LooseWeight * ProcessEvent.SingleElectron * ProcessEvent.passElFake_MET_down * ProcessEvent.Lepton1_passLooseID * (-1.0));
     myhists->FakeLeptonPtEta_El_MET_down_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), Lepton1TightWeight * ProcessEvent.SingleElectron * ProcessEvent.passElFake_MET_down * ProcessEvent.Lepton1_isTight * (-1.0));

     if(MCType == "Diboson" || MCType == "Triboson" || MCType == "ttV"){
       myhists->FakeLeptonPtEta_Mu_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), Lepton3LooseWeight * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_passLooseID * (-1.0));
       myhists->FakeLeptonPtEta_Mu_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), Lepton3TightWeight * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_isTight * (-1.0));

       myhists->FakeLeptonPtEta_Mu_PromptSubtr_up_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), Lepton3LooseWeight * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_passLooseID * (-0.9));
       myhists->FakeLeptonPtEta_Mu_PromptSubtr_up_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), Lepton3TightWeight * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_isTight * (-0.9));

       myhists->FakeLeptonPtEta_Mu_PromptSubtr_down_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), Lepton3LooseWeight * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_passLooseID * (-1.1));
       myhists->FakeLeptonPtEta_Mu_PromptSubtr_down_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), Lepton3TightWeight * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_isTight * (-1.1));

       myhists->FakeLeptonPtEta_Mu_d0sig_up_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), Lepton3LooseWeight * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake_d0sig_up * ProcessEvent.Lepton3_passLooseID * (-1.0));
       myhists->FakeLeptonPtEta_Mu_d0sig_up_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), Lepton3TightWeight * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake_d0sig_up * ProcessEvent.Lepton3_isTight * (-1.0));

       myhists->FakeLeptonPtEta_Mu_d0sig_down_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), Lepton3LooseWeight * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake_d0sig_down * ProcessEvent.Lepton3_passLooseID * (-1.0));
       myhists->FakeLeptonPtEta_Mu_d0sig_down_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), Lepton3TightWeight * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake_d0sig_down * ProcessEvent.Lepton3_isTight * (-1.0));

       myhists->FakeLeptonPt_Mu_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, Lepton3LooseWeight * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_passLooseID * (-1.0));
       myhists->FakeLeptonPt_Mu_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton3_Pt, Lepton3TightWeight * ProcessEvent.eeChannel_withmuon * ProcessEvent.passMuFake * ProcessEvent.Lepton3_isTight * (-1.0));
     }
   }

   // Closure
   myhists->FakeLeptonPtEta_El_Wjets_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel * ProcessEvent.Lepton1_isTight * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton1_isTruthMatch * (!ProcessEvent.Lepton2_isTruthMatch) * ProcessEvent.Lepton2_isTight * ProcessEvent.Lepton2_TightWeight);
   myhists->FakeLeptonPtEta_El_Wjets_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel * ProcessEvent.Lepton1_isTight * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton1_isTruthMatch * (!ProcessEvent.Lepton2_isTruthMatch) * ProcessEvent.Lepton2_passLooseID * ProcessEvent.Lepton2_LooseWeight);

   myhists->RealLeptonPtEta_El_Wjets_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.TotalWeightLoose * (ProcessEvent.eeChannel || ProcessEvent.SingleElectron) * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton1_isTight * ProcessEvent.Lepton1_TightWeight);
   myhists->RealLeptonPtEta_El_Wjets_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.TotalWeightLoose * (ProcessEvent.eeChannel || ProcessEvent.SingleElectron) * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton1_passLooseID * ProcessEvent.Lepton1_LooseWeight);

   myhists->RealLepton2PtEta_El_Wjets_Tight->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel * (!ProcessEvent.Lepton1_isTruthMatch) * (ProcessEvent.Lepton2_isTruthMatch) * ProcessEvent.Lepton2_isTight * ProcessEvent.Lepton2_TightWeight);
   myhists->RealLepton2PtEta_El_Wjets_Loose->at(iThread - 1)->Fill(ProcessEvent.Lepton2_Pt, fabs(ProcessEvent.Lepton2_Eta), ProcessEvent.TotalWeightLoose * ProcessEvent.eeChannel * (!ProcessEvent.Lepton1_isTruthMatch) * (ProcessEvent.Lepton2_isTruthMatch) * ProcessEvent.Lepton2_passLooseID * ProcessEvent.Lepton2_LooseWeight);

   //myhists->LooseLepton1PtEta->Fill(iThread, ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton1_passLooseID, ProcessEvent);
   //myhists->TightLepton1PtEta->Fill(iThread, ProcessEvent.Lepton1_Pt, fabs(ProcessEvent.Lepton1_Eta), ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton1_isTight, ProcessEvent);
   //myhists->LooseLepton3PtEta->Fill(iThread, ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.Lepton3_LooseWeight * ProcessEvent.Lepton3_passLooseID, ProcessEvent);
   //myhists->TightLepton3PtEta->Fill(iThread, ProcessEvent.Lepton3_Pt, fabs(ProcessEvent.Lepton3_Eta), ProcessEvent.Lepton3_LooseWeight * ProcessEvent.Lepton3_isTight, ProcessEvent);

 }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loopZPrime::FillTopDDHist(EventZPrime ProcessEvent)
{
 double RecoWeight = (ProcessEvent.RecoWeight == ProcessEvent.RecoWeight) ? ProcessEvent.RecoWeight : 0;

 if(isData) RecoWeight = 1.0;

 ProcessEvent.isZeeIncOverlap = (ProcessEvent.RecoDilMass > 120.0)
                             && (ProcessEvent.mcChannelNumber >= 700786 && ProcessEvent.mcChannelNumber <= 700788);

 if(isAdditionalWeight) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * ProcessEvent.AdditionalWeight;
 if(isChangeNorm) ProcessEvent.TotalWeight = ProcessEvent.TotalWeight * ProcessEvent.Normalization;

 ProcessEvent.passSelectionEl = (ProcessEvent.eeChannel && !ProcessEvent.mumuChannel && !ProcessEvent.emuChannel)
                             && (ProcessEvent.RecoDilMass > 130.0)
                             && (ProcessEvent.Lepton1_Pt > 30.0)
                             && (ProcessEvent.Lepton2_Pt > 30.0)
                             && !(ProcessEvent.isZeeIncOverlap);

 ProcessEvent.passSelectionMu = (!ProcessEvent.eeChannel && ProcessEvent.mumuChannel && !ProcessEvent.emuChannel)
                             && (ProcessEvent.RecoDilMass > 130.0)
                             && (ProcessEvent.Lepton1_Pt > 30.0)
                             && (ProcessEvent.Lepton2_Pt > 30.0)
                             && !(ProcessEvent.isZeeIncOverlap);

 ProcessEvent.passSelectionElMu = (!ProcessEvent.eeChannel && !ProcessEvent.mumuChannel && ProcessEvent.emuChannel)
                               && (ProcessEvent.RecoDilMass > 130.0)
                               && (ProcessEvent.Lepton1_Pt > 30.0)
                               && (ProcessEvent.Lepton2_Pt > 30.0)
                               && !(ProcessEvent.isZeeIncOverlap);


}
#endif
