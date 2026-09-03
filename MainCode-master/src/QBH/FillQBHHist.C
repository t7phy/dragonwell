#ifndef QBH_FillHist_cxx
#define QBH_FillHist_cxx

#include <iostream>
#include "QBH/loopQBH.h"

using namespace std;

void loopQBH::FillHist(EventQBH ProcessEvent)
{
 if(doFakeRate){
   FakeInstance->GetIndex2D(ProcessEvent.LeadingLeptonPt, fabs(ProcessEvent.LeadingLeptonEta), ProcessEvent.LeptonFlavor);
   ProcessEvent.FakeEff = FakeInstance->f1;
   ProcessEvent.RealEff = FakeInstance->e1;
  
   if(isTest){
     cout<<"RootType: "<<BkgShortName<<endl;
     cout<<"Fake Efficiency: "<<ProcessEvent.FakeEff<<endl;
     cout<<"Real Efficiency: "<<ProcessEvent.RealEff<<endl;
     cout<<"Weight: "<<TotalWeight<<endl;
   }
 }

 myhists->LepJetMass->Fill(iThread, ProcessEvent.LepJetMass, ProcessEvent.TotalWeight, ProcessEvent);
 myhists->LepJetMass_LowBornMass->Fill(iThread, ProcessEvent.LepJetMass, ProcessEvent.TotalWeight * (ProcessEvent.BornMass < 105.0), ProcessEvent);
 myhists->LepJetMass_HighBornMass->Fill(iThread, ProcessEvent.LepJetMass, ProcessEvent.TotalWeight * (ProcessEvent.BornMass > 105.0), ProcessEvent);
 myhists->LepJetMass_LowBornMass_El->Fill(iThread, ProcessEvent.LepJetMass, ProcessEvent.TotalWeight * (ProcessEvent.BornMass < 105.0) * (ProcessEvent.LeptonFlavor == 11), ProcessEvent);
 myhists->LepJetMass_HighBornMass_El->Fill(iThread, ProcessEvent.LepJetMass, ProcessEvent.TotalWeight * (ProcessEvent.BornMass > 105.0) * (ProcessEvent.LeptonFlavor == 11), ProcessEvent);
 myhists->LepJetMass_LowBornMass_Mu->Fill(iThread, ProcessEvent.LepJetMass, ProcessEvent.TotalWeight * (ProcessEvent.BornMass < 105.0) * (ProcessEvent.LeptonFlavor == 13), ProcessEvent);
 myhists->LepJetMass_HighBornMass_Mu->Fill(iThread, ProcessEvent.LepJetMass, ProcessEvent.TotalWeight * (ProcessEvent.BornMass > 105.0) * (ProcessEvent.LeptonFlavor == 13), ProcessEvent);
 //myhists->LepJetMass_El->Fill(iThread, ProcessEvent.LepJetMass, ProcessEvent.TotalWeight * (ProcessEvent.LeptonFlavor == 11), ProcessEvent);
 //myhists->LepJetMass_Mu->Fill(iThread, ProcessEvent.LepJetMass, ProcessEvent.TotalWeight * (ProcessEvent.LeptonFlavor == 13), ProcessEvent);
 myhists->LeadingLeptonPt->Fill(iThread, ProcessEvent.LeadingLeptonPt, ProcessEvent.TotalWeight, ProcessEvent);
 myhists->LeadingLeptonEta->Fill(iThread, ProcessEvent.LeadingLeptonEta, ProcessEvent.TotalWeight, ProcessEvent);
 myhists->LeadingJetPt->Fill(iThread, ProcessEvent.LeadingJetPt, ProcessEvent.TotalWeight, ProcessEvent);
 myhists->Njets->Fill(iThread, ProcessEvent.Njets, ProcessEvent.TotalWeight, ProcessEvent);
 myhists->MissingET->Fill(iThread, ProcessEvent.MissingET, ProcessEvent.TotalWeight, ProcessEvent);
 myhists->Mll->Fill(iThread, ProcessEvent.Mll, ProcessEvent.TotalWeight, ProcessEvent);
 myhists->DeltaRLepJet->Fill(iThread, ProcessEvent.DeltaRLepJet, ProcessEvent.TotalWeight, ProcessEvent);
 myhists->detaLepJet->Fill(iThread, ProcessEvent.detaLepJet, ProcessEvent.TotalWeight, ProcessEvent);
 //myhists->detaLepJet_El->Fill(iThread, ProcessEvent.detaLepJet, ProcessEvent.TotalWeight * (ProcessEvent.LeptonFlavor == 11), ProcessEvent);
 //myhists->detaLepJet_Mu->Fill(iThread, ProcessEvent.detaLepJet, ProcessEvent.TotalWeight * (ProcessEvent.LeptonFlavor == 13), ProcessEvent);
 myhists->dphiLepJet->Fill(iThread, ProcessEvent.dphiLepJet, ProcessEvent.TotalWeight, ProcessEvent);
 //myhists->dphiLepJet_El->Fill(iThread, ProcessEvent.dphiLepJet, ProcessEvent.TotalWeight * (ProcessEvent.LeptonFlavor == 11), ProcessEvent);
 //myhists->dphiLepJet_Mu->Fill(iThread, ProcessEvent.dphiLepJet, ProcessEvent.TotalWeight * (ProcessEvent.LeptonFlavor == 13), ProcessEvent);
 myhists->METSig->Fill(iThread, ProcessEvent.METSig, ProcessEvent.TotalWeight, ProcessEvent);
 //myhists->METSig_El->Fill(iThread, ProcessEvent.METSig, ProcessEvent.TotalWeight * (ProcessEvent.LeptonFlavor == 11), ProcessEvent);
 //myhists->METSig_Mu->Fill(iThread, ProcessEvent.METSig, ProcessEvent.TotalWeight * (ProcessEvent.LeptonFlavor == 13), ProcessEvent);
 myhists->Lepton1_d0Sig->Fill(iThread, ProcessEvent.Lepton1_d0Sig, ProcessEvent.TotalWeight, ProcessEvent);
 myhists->Lepton2_d0Sig->Fill(iThread, ProcessEvent.Lepton2_d0Sig, ProcessEvent.TotalWeight, ProcessEvent);
 myhists->BornMass->Fill(iThread, ProcessEvent.BornMass, ProcessEvent.TotalWeight, ProcessEvent);

 /////////////////////
 // Fake Background //
 /////////////////////

/*
 FakeInstance->GetIndex2D(ProcessEvent.LeadingLeptonPt, fabs(ProcessEvent.LeadingLeptonEta), ProcessEvent.LeptonFlavor);
 ProcessEvent.FakeEff = FakeInstance->f1;
 ProcessEvent.RealEff = FakeInstance->e1;

 double TotalWeight;
 if(BkgShortName == "data") TotalWeight = ProcessEvent.TotalWeight;
 //else if(BkgShortName == "singletop"
 //     || BkgShortName == "ttbar"
 //     || BkgShortName == "ttV"
 //     || BkgShortName == "Wenu"
 //     || BkgShortName == "Wmnu"
 //     || BkgShortName == "Wtnu"
 //     || BkgShortName == "Zee"
 //     || BkgShortName == "Zmm"
 //     || BkgShortName == "Ztt"
 //     || BkgShortName == "diboson"){
 //  TotalWeight = ProcessEvent.TotalWeight * (-1.0);
 //}
 else TotalWeight = 0.0;

 if(isTest){
   cout<<"RootType: "<<BkgShortName<<endl;
   cout<<"Fake Efficiency: "<<ProcessEvent.FakeEff<<endl;
   cout<<"Real Efficiency: "<<ProcessEvent.RealEff<<endl;
   cout<<"Weight: "<<TotalWeight<<endl;
 }

 myhists->LepJetMass->FillFake(iThread, ProcessEvent.LepJetMass, TotalWeight, ProcessEvent);
 //myhists->LepJetMass_El->FillFake(iThread, ProcessEvent.LepJetMass, TotalWeight * (ProcessEvent.LeptonFlavor == 11), ProcessEvent);
 //myhists->LepJetMass_Mu->FillFake(iThread, ProcessEvent.LepJetMass, TotalWeight * (ProcessEvent.LeptonFlavor == 13), ProcessEvent);
 myhists->LeadingLeptonPt->FillFake(iThread, ProcessEvent.LeadingLeptonPt, TotalWeight, ProcessEvent);
 myhists->LeadingLeptonEta->FillFake(iThread, ProcessEvent.LeadingLeptonEta, TotalWeight, ProcessEvent);
 myhists->LeadingJetPt->FillFake(iThread, ProcessEvent.LeadingJetPt, TotalWeight, ProcessEvent);
 myhists->Njets->FillFake(iThread, ProcessEvent.Njets, TotalWeight, ProcessEvent);
 myhists->MissingET->FillFake(iThread, ProcessEvent.MissingET, TotalWeight, ProcessEvent);
 myhists->Mll->FillFake(iThread, ProcessEvent.Mll, TotalWeight, ProcessEvent);
 myhists->DeltaRLepJet->FillFake(iThread, ProcessEvent.DeltaRLepJet, TotalWeight, ProcessEvent);
 myhists->detaLepJet->FillFake(iThread, ProcessEvent.detaLepJet, TotalWeight, ProcessEvent);
 //myhists->detaLepJet_El->FillFake(iThread, ProcessEvent.detaLepJet, TotalWeight * (ProcessEvent.LeptonFlavor == 11), ProcessEvent);
 //myhists->detaLepJet_Mu->FillFake(iThread, ProcessEvent.detaLepJet, TotalWeight * (ProcessEvent.LeptonFlavor == 13), ProcessEvent);
 myhists->dphiLepJet->FillFake(iThread, ProcessEvent.dphiLepJet, TotalWeight, ProcessEvent);
 //myhists->dphiLepJet_El->FillFake(iThread, ProcessEvent.dphiLepJet, TotalWeight * (ProcessEvent.LeptonFlavor == 11), ProcessEvent);
 //myhists->dphiLepJet_Mu->FillFake(iThread, ProcessEvent.dphiLepJet, TotalWeight * (ProcessEvent.LeptonFlavor == 13), ProcessEvent);
 myhists->METSig->FillFake(iThread, ProcessEvent.METSig, TotalWeight, ProcessEvent);
 //myhists->METSig_El->FillFake(iThread, ProcessEvent.METSig, TotalWeight * (ProcessEvent.LeptonFlavor == 11), ProcessEvent);
 //myhists->METSig_Mu->FillFake(iThread, ProcessEvent.METSig, TotalWeight * (ProcessEvent.LeptonFlavor == 13), ProcessEvent);
*/

}
#endif
