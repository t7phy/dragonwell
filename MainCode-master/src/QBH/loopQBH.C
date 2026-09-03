#define loopQBH_cxx
#include <iostream>
#include "QBH/loopQBH.h"

using namespace std;

loopQBH::loopQBH(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopQBH::InputHist(HistsQBH* &myhists)
{
 this->myhists = myhists;

 if(myhists->doFakeRate){
   doFakeRate = true;
   FakeRate = myhists->FakeRate->Clone(iThread);
   FakeInstance = new DataDriven(1);
   FakeInstance->InputFakeEfficiency(FakeRate->ElFakeEff, FakeRate->MuFakeEff);
   FakeInstance->InputRealEfficiency(FakeRate->ElRealEff, FakeRate->MuRealEff);
 }
}

void loopQBH::InputTree(TreeForQBH *QBHTree)
{
 isInputPreTree = false;

 this->QBHTree = QBHTree;
 this->RootNames = QBHTree->RootNames;

 this->RootTypes = QBHTree->RootTypes;

 this->FirstFile = QBHTree->FirstFile;
 this->EndFile = QBHTree->EndFile;

 this->OneFilePerJob = QBHTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = QBHTree->TotalEntries[ifile];
 }
}

void loopQBH::InputTree(TreeForPreQBH *PreQBHTree)
{
 isInputPreTree = true;

 this->PreQBHTree = PreQBHTree;
 this->RootNames = PreQBHTree->RootNames;

 this->RootTypes = PreQBHTree->RootTypes;

 this->FirstFile = PreQBHTree->FirstFile;
 this->EndFile = PreQBHTree->EndFile;

 this->OneFilePerJob = PreQBHTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = PreQBHTree->TotalEntries[ifile];
 }

 this->QBHTree = new TreeForQBH();

 if(JustGenerateTree){
   if(!NtupleName.Contains("root")) NtupleName = PreQBHTree->SaveName;
   this->QBHTree->GenerateFile(NtupleName);
   this->QBHTree->DefineTree(0, "nominal");
 }
}

void loopQBH::InputNtupleName(TString NtupleName)
{
//this name will be override by the automatic name
 this->NtupleName = NtupleName;
}

void loopQBH::ReadTree(int ifile)
{
 if(RootTypes.at(ifile) == "data") isData = true;
 else isData = false;

 BkgShortName = RootTypes.at(ifile);

 for(int ibkghist = 0; ibkghist < myhists->BkgHist_1d.size(); ibkghist++){
   myhists->BkgHist_1d.at(ibkghist)->HistPtr(iThread - 1)->Initial(RootTypes.at(ifile));
 }

 for(int iprocesshist = 0; iprocesshist < myhists->hist_process.size(); iprocesshist++){
   myhists->hist_process.at(iprocesshist)->Initial(iThread, RootTypes.at(ifile));
 }

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"\r"<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<flush;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"\r"<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
     if(!isThread) cout<<"\r"<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
   }

   QBHTree->GetEntry(ifile, iEvent);

   DefaultEvent.TotalWeight = QBHTree->TotalWeight;
   DefaultEvent.LeadingLepWeight = QBHTree->LeadingLepWeight;
   DefaultEvent.SubleadingLepWeight = QBHTree->SubleadingLepWeight;
   DefaultEvent.passLeadingLepTight = QBHTree->passLeadingLepTight;

   DefaultEvent.LepJetMass = QBHTree->LepJetMass;
   DefaultEvent.LeadingLeptonPt = QBHTree->LeadingLeptonPt;
   DefaultEvent.LeadingLeptonEta = QBHTree->LeadingLeptonEta;
   DefaultEvent.LeadingJetPt = QBHTree->LeadingJetPt;
   DefaultEvent.Njets = QBHTree->Njets;
   DefaultEvent.MissingET = QBHTree->MissingET;
   DefaultEvent.Mll = QBHTree->Mll;
   DefaultEvent.DeltaRLepJet = QBHTree->DeltaRLepJet;
   DefaultEvent.detaLepJet = QBHTree->detaLepJet;
   DefaultEvent.dphiLepJet = QBHTree->dphiLepJet;
   DefaultEvent.METSig = QBHTree->METSig;
   DefaultEvent.LeptonFlavor = QBHTree->LeptonFlavor;
   DefaultEvent.Lepton1_d0Sig = QBHTree->Lepton1_d0Sig;
   DefaultEvent.Lepton2_d0Sig = QBHTree->Lepton2_d0Sig;

   DefaultEvent.passInclusive = QBHTree->passInclusive;
   DefaultEvent.passFakeCR = QBHTree->passFakeCR;
   DefaultEvent.passWCR = QBHTree->passWCR;
   DefaultEvent.passWVR = QBHTree->passWVR;
   DefaultEvent.passZCR = QBHTree->passZCR;
   DefaultEvent.passZVR = QBHTree->passZVR;
   DefaultEvent.passTCR = QBHTree->passTCR;
   DefaultEvent.passTVR = QBHTree->passTVR;
   DefaultEvent.passSR = QBHTree->passSR;
   DefaultEvent.passSVR = QBHTree->passSVR;

   FillHist(DefaultEvent);
 }

}

void loopQBH::PreLoop(int ifile)
{
 if(RootTypes.at(ifile) == "data") isData = true;
 else isData = false;

 BkgShortName = RootTypes.at(ifile);

// TString HistName = (TString)"try_" + iThread;
// TH2D* h = new TH2D(HistName, HistName, 5, 130, 500, 5, 0.0, 2.5);
// PreQBHTree->fChain[ifile]->Draw("fabs(lepton1_eta):lepton1_pt>>"+HistName, "1", "goff");
// cout<<h->GetEntries()<<endl;

 for(int ibkghist = 0; ibkghist < myhists->BkgHist_1d.size(); ibkghist++){
   myhists->BkgHist_1d.at(ibkghist)->HistPtr(iThread - 1)->Initial(RootTypes.at(ifile));
 }

 for(int iprocesshist = 0; iprocesshist < myhists->hist_process.size(); iprocesshist++){
   myhists->hist_process.at(iprocesshist)->Initial(iThread, RootTypes.at(ifile));
 }

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"\r"<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<flush;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"\r"<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
     if(!isThread) cout<<"\r"<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
   }

   PreQBHTree->GetEntry(ifile, iEvent);

   if(FillEvents()){
     if(JustGenerateTree) QBHTree->FillTree(0);

     if(FinishProcess) FillHist(SelectedEvent);
   }

 }
}

bool loopQBH::FillEvents()
{
 SelectedEvent.ResetEvent();

 SelectedEvent.passTrig = PreQBHTree->HLT_singleLep
                       // * PreQBHTree->HLT_singleJet
                        * PreQBHTree->lepton_singleleptrigMatched;

 if(isTest){
   cout<<"Single Lepton Trigger: "<<PreQBHTree->HLT_singleLep<<endl;
   cout<<"Single Jet Trigger: "<<PreQBHTree->HLT_singleJet<<endl;
   cout<<"Single Lepton TriggerMatched: "<<PreQBHTree->lepton_singleleptrigMatched<<endl;
   cout<<"n Signal Leptons = "<<PreQBHTree->n_signal_lep<<endl;
 }

 if(!SelectedEvent.passTrig) return false;
// if(PreQBHTree->n_signal_lep != 1) return false;

// if(PreQBHTree->born_dilepton_m < 105.0) return false;

 SelectedEvent.JetWeight = PreQBHTree->weight_jvt * PreQBHTree->weight_btag;
 SelectedEvent.NormSF = PreQBHTree->weight_norm * PreQBHTree->weight_lumi * PreQBHTree->weight_gen;

 SelectedEvent.LeadingLepWeight = PreQBHTree->weight_lepton * PreQBHTree->weight_singleleptonTrigSF;

 if(isData) SelectedEvent.JetWeight = 1.0;
 if(isData) SelectedEvent.NormSF = 1.0;
 if(isData) SelectedEvent.LeadingLepWeight = 1.0;

 SelectedEvent.TotalWeight = PreQBHTree->mcEventWeight
                           * PreQBHTree->weight_pileup
                           * PreQBHTree->beamSpotWeight
                           //* SelectedEvent.JetWeight
                           * SelectedEvent.NormSF
                           * SelectedEvent.LeadingLepWeight;

 SelectedEvent.TotalWeightLoose =  PreQBHTree->mcEventWeight
                                 * PreQBHTree->weight_pileup
                                 * PreQBHTree->beamSpotWeight
                                 //* SelectedEvent.JetWeight
                                 * SelectedEvent.NormSF
                                 * PreQBHTree->weight_singleleptonTrigSF;

 SelectedEvent.LeptonTightWeight = PreQBHTree->weight_lepton;

 if(isData) SelectedEvent.TotalWeight = 1.0;
 if(isData) SelectedEvent.TotalWeightLoose = 1.0;
 if(isData) SelectedEvent.LeptonTightWeight = 1.0;

 SelectedEvent.passLeadingLepTight = PreQBHTree->lepton1_isSig * PreQBHTree->lepton1_isIso * (PreQBHTree->n_signal_lep > 0);

 SelectedEvent.LeadingLepton.P4.SetPtEtaPhiM(PreQBHTree->lepton1_pt, PreQBHTree->lepton1_eta, PreQBHTree->lepton1_phi, PreQBHTree->lepton1_m);

 if(PreQBHTree->lepton2_pt >= 0.0) SelectedEvent.SubleadingLepton.P4.SetPtEtaPhiM(PreQBHTree->lepton2_pt, PreQBHTree->lepton2_eta, PreQBHTree->lepton2_phi, PreQBHTree->lepton2_m);
 else SelectedEvent.SubleadingLepton.P4.SetPtEtaPhiM(0.0, 0.0, 0.0, 0.0);

 SelectedEvent.Lepton1_d0Sig = PreQBHTree->lepton1_d0sig;
 SelectedEvent.Lepton2_d0Sig = PreQBHTree->lepton2_d0sig;

 SelectedEvent.LeadingJet.P4.SetPtEtaPhiE(PreQBHTree->jet1_pt, PreQBHTree->jet1_eta, PreQBHTree->jet1_phi, PreQBHTree->jet1_E);

 TLorentzVector LepJet = SelectedEvent.LeadingLepton.P4 + SelectedEvent.LeadingJet.P4;
 TLorentzVector Dilepton = SelectedEvent.LeadingLepton.P4 + SelectedEvent.SubleadingLepton.P4;
 TLorentzVector metVector;
 metVector.SetPxPyPzE(PreQBHTree->metFinalTrkPx, PreQBHTree->metFinalTrkPy, 0.0, PreQBHTree->metFinalTrk);

 SelectedEvent.LepJetMass = LepJet.M();
 SelectedEvent.LeadingLeptonPt = SelectedEvent.LeadingLepton.P4.Pt();
 SelectedEvent.LeadingLeptonEta = SelectedEvent.LeadingLepton.P4.Eta();

 if(PreQBHTree->lepton1_isEl) SelectedEvent.LeptonFlavor = 11;
 else if(PreQBHTree->lepton1_isEl == 0) SelectedEvent.LeptonFlavor = 13;

 SelectedEvent.SubleadingLeptonPt = PreQBHTree->lepton2_pt;
 SelectedEvent.LeadingJetPt = SelectedEvent.LeadingJet.P4.Pt();

 SelectedEvent.MissingET = PreQBHTree->metFinalTrk;
 SelectedEvent.Mll = Dilepton.M();

 SelectedEvent.DeltaRLepJet = SelectedEvent.LeadingLepton.P4.DeltaR(SelectedEvent.LeadingJet.P4);
 //SelectedEvent.detaLepJet = SelectedEvent.LeadingLepton.P4.Eta() - SelectedEvent.LeadingJet.P4.Eta();
 //SelectedEvent.dphiLepJet = DeltaPhi(SelectedEvent.LeadingLepton.P4.Phi(), SelectedEvent.LeadingJet.P4.Phi());
 SelectedEvent.detaLepJet = PreQBHTree->detaLepJet;
 SelectedEvent.dphiLepJet = PreQBHTree->dphiLepJet;
 SelectedEvent.METSig = PreQBHTree->metFinalTrkSignificance;

 SelectedEvent.Njets = PreQBHTree->njet;
 SelectedEvent.NBjets = PreQBHTree->n_bjets;

 SelectedEvent.isSFOS = (PreQBHTree->lepton1_isEl + PreQBHTree->lepton2_isEl == 0 || PreQBHTree->lepton1_isEl + PreQBHTree->lepton2_isEl == 2)
                     && (PreQBHTree->lepton1_charge * PreQBHTree->lepton2_charge < 0);

 if(PreQBHTree->lepton2_pt < 0.0) SelectedEvent.isSFOS = 0;

 SelectedEvent.BornMass = PreQBHTree->born_dilepton_m;

 SelectedEvent.passInclusive = (SelectedEvent.LepJetMass < 3000.0)
                            //&& (PreQBHTree->metFinalTrkSignificance > 3.5)
                            && (SelectedEvent.dphiLepJet > 2.8)
                            && (SelectedEvent.detaLepJet < 3.25);

 SelectedEvent.passFakeCR = 1;

 SelectedEvent.passWCR = (SelectedEvent.LepJetMass > 1000.0 && SelectedEvent.LepJetMass < 3000.0)
                      && (SelectedEvent.LeadingLeptonPt > 130.0)
                      && (SelectedEvent.SubleadingLeptonPt < 10.0)
                      && (SelectedEvent.LeadingJetPt > 130.0)
                      //&& (SelectedEvent.SubleadingJetPt < 130.0)
                      && (SelectedEvent.NBjets == 0)
                      && (SelectedEvent.MissingET > 60.0);

 SelectedEvent.passWVR = (SelectedEvent.LepJetMass > 1500.0 && SelectedEvent.LepJetMass < 3000.0)
                      && (SelectedEvent.LeadingLeptonPt > 130.0)
                      && (SelectedEvent.SubleadingLeptonPt < 10.0)
                      && (SelectedEvent.LeadingJetPt > 130.0)
                      //&& (SelectedEvent.SubleadingJetPt < 130.0)
                      && (SelectedEvent.NBjets == 0)
                      && (SelectedEvent.MissingET > 60.0);

 SelectedEvent.passZCR = (SelectedEvent.LepJetMass > 1000.0 && SelectedEvent.LepJetMass < 3000.0)
                      && (SelectedEvent.LeadingLeptonPt > 130.0)
                      && (SelectedEvent.SubleadingLeptonPt > 30.0)
                      && (SelectedEvent.isSFOS)
                      && (SelectedEvent.LeadingJetPt > 130.0)
                      //&& (SelectedEvent.SubleadingJetPt < 130.0)
                      && (SelectedEvent.Mll > 70.0 && SelectedEvent.Mll < 110.0);

 SelectedEvent.passZVR = (SelectedEvent.LepJetMass > 1500.0 && SelectedEvent.LepJetMass < 3000.0)
                      && (SelectedEvent.LeadingLeptonPt > 130.0)
                      && (SelectedEvent.SubleadingLeptonPt > 30.0)
                      && (SelectedEvent.isSFOS)
                      && (SelectedEvent.LeadingJetPt > 130.0)
                      //&& (SelectedEvent.SubleadingJetPt < 130.0)
                      && (SelectedEvent.Mll > 70.0 && SelectedEvent.Mll < 110.0);

 SelectedEvent.passTCR = (SelectedEvent.LepJetMass > 1000.0 && SelectedEvent.LepJetMass < 3000.0)
                      && (SelectedEvent.LeadingLeptonPt > 130.0)
                      && (SelectedEvent.SubleadingLeptonPt < 10.0)
                      && (SelectedEvent.LeadingJetPt > 130.0)
                      //&& (SelectedEvent.SubleadingJetPt < 130.0)
                      && (SelectedEvent.Njets >= 3)
                      && (SelectedEvent.NBjets >= 2);

 SelectedEvent.passTVR = (SelectedEvent.LepJetMass > 1500.0 && SelectedEvent.LepJetMass < 3000.0)
                      && (SelectedEvent.LeadingLeptonPt > 130.0)
                      && (SelectedEvent.SubleadingLeptonPt < 10.0)
                      && (SelectedEvent.LeadingJetPt > 130.0)
                      //&& (SelectedEvent.SubleadingJetPt < 130.0)
                      && (SelectedEvent.Njets >= 3)
                      && (SelectedEvent.NBjets >= 2);

 SelectedEvent.passSR  = (SelectedEvent.LepJetMass > 2000.0)
                      && (SelectedEvent.LeadingLeptonPt > 130.0)
                      && (SelectedEvent.SubleadingLeptonPt < 10.0)
                      && (SelectedEvent.LeadingJetPt > 130.0);
                      //&& (SelectedEvent.SubleadingJetPt < 130.0);

 SelectedEvent.passSVR = (SelectedEvent.LepJetMass > 1500.0 && SelectedEvent.LepJetMass < 3000.0)
                      && (SelectedEvent.LeadingLeptonPt > 130.0)
                      && (SelectedEvent.SubleadingLeptonPt < 10.0)
                      && (SelectedEvent.LeadingJetPt > 130.0);
                      //&& (SelectedEvent.SubleadingJetPt < 130.0);

 QBHTree->TotalWeight = SelectedEvent.TotalWeight;
 QBHTree->TotalWeightLoose = SelectedEvent.TotalWeightLoose;
 QBHTree->LeptonTightWeight = SelectedEvent.LeptonTightWeight;
 QBHTree->LeadingLepWeight = SelectedEvent.LeadingLepWeight;
 QBHTree->SubleadingLepWeight = SelectedEvent.SubleadingLepWeight;
 QBHTree->passLeadingLepTight = SelectedEvent.passLeadingLepTight;

 QBHTree->LepJetMass = SelectedEvent.LepJetMass;
 QBHTree->LeadingLeptonPt = SelectedEvent.LeadingLeptonPt;
 QBHTree->LeadingLeptonEta = SelectedEvent.LeadingLeptonEta;
 QBHTree->LeadingJetPt = SelectedEvent.LeadingJetPt;
 QBHTree->Njets = SelectedEvent.Njets;
 QBHTree->MissingET = SelectedEvent.MissingET;
 QBHTree->Mll = SelectedEvent.Mll;
 QBHTree->DeltaRLepJet = SelectedEvent.DeltaRLepJet;
 QBHTree->detaLepJet = SelectedEvent.detaLepJet;
 QBHTree->dphiLepJet = SelectedEvent.dphiLepJet;
 QBHTree->METSig = SelectedEvent.METSig;
 QBHTree->LeptonFlavor = SelectedEvent.LeptonFlavor;
 QBHTree->Lepton1_d0Sig = SelectedEvent.Lepton1_d0Sig;
 QBHTree->Lepton2_d0Sig = SelectedEvent.Lepton2_d0Sig;

 QBHTree->passInclusive = SelectedEvent.passInclusive;
 QBHTree->passFakeCR = SelectedEvent.passFakeCR;
 QBHTree->passWCR = SelectedEvent.passWCR;
 QBHTree->passWVR = SelectedEvent.passWVR;
 QBHTree->passZCR = SelectedEvent.passZCR;
 QBHTree->passZVR = SelectedEvent.passZVR;
 QBHTree->passTCR = SelectedEvent.passTCR;
 QBHTree->passTVR = SelectedEvent.passTVR;
 QBHTree->passSR = SelectedEvent.passSR;
 QBHTree->passSVR = SelectedEvent.passSVR;

 return true;
}

void EventQBH::ResetEvent()
{
 passTrig = 0;

 JetWeight = 1.0;
 NormSF = 1.0;
 TotalWeight = 1.0;
 TotalWeightLoose = 1.0;
 LeptonTightWeight = 1.0;

 LeadingLepWeight = 1.0;
 SubleadingLepWeight = 1.0;

 passLeadingLepTight = 0;

 LepJetMass = -999.0;
 LeadingLeptonPt = -999.0;
 LeadingLeptonEta = -999.0;
 SubleadingLeptonPt = -999.0;
 LeadingJetPt = -999.0;
 SubleadingJetPt = -999.0;
 Njets = -1;
 NBjets = -1;
 MissingET = -999.0;
 Mll = -999.0;
 isSFOS = 0;
 DeltaRLepJet = -999.0;
 detaLepJet = -999.0;
 dphiLepJet = -999.0;
 METSig = -999.0;
 LeptonFlavor = 0;
 Lepton1_d0Sig = -999.0;
 Lepton2_d0Sig = -999.0;

 passInclusive = 0;
 passFakeCR = 0;
 passWCR = 0;
 passWVR = 0;
 passZCR = 0;
 passZVR = 0;
 passTCR = 0;
 passTVR = 0;
 passSR = 0;
 passSVR = 0;

 LeadingLepton.ResetEvent();
 SubleadingLepton.ResetEvent();
 LeadingJet.ResetEvent();
}

void QBHLepton::ResetEvent()
{
 P4.SetPtEtaPhiM(0,0,0,0);

}

void loopQBH::End(int RootNumber)
{
 cout<<"\r"<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<"  "<<flush;//yfu

 if(!isInputPreTree){
   if(!QBHTree->fChain[RootNumber])
    {
     cout<<"XXXXX**Runing: BIG ERROR!!! No File loaded!"<<endl;
     return;
    }
   QBHTree->CloseFile(RootNumber);
   delete QBHTree->fChain[RootNumber]->GetCurrentFile();
 }

 if(isInputPreTree){
   if(!PreQBHTree->fChain[RootNumber])
    {
     cout<<"XXXXX**Runing: BIG ERROR!!! No File loaded!"<<endl;
     return;
    }
   PreQBHTree->CloseFile(RootNumber);
   //cout<<"file address: "<<PreQBHTree->fChain[RootNumber]<<endl;
   //cout<<"tree address: "<<PreQBHTree->fChain[RootNumber]->GetCurrentFile()<<endl;
   //delete PreQBHTree->fChain[RootNumber]->GetCurrentFile();
   //delete PreQBHTree->fChain[RootNumber];
   //delete PreQBHTree->rootfile[RootNumber];
 }
}

void loopQBH::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(!isInputPreTree){
   if(EndFile == RootNames.size()) delete QBHTree;
 }

 if(isInputPreTree){
   if(EndFile == RootNames.size()) delete PreQBHTree;
 }

 if(JustGenerateTree){
   QBHTree->SaveFile();
 }

 //for multi-run the loop function
 if(isInputPreTree){
   delete QBHTree;
 }

}

loopQBH::~loopQBH()
{
}


