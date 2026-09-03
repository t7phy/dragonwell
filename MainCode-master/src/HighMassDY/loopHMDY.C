#define loopHMDY_cxx
#include <iostream>
#include "HighMassDY/loopHMDY.h"

using namespace std;

loopHMDY::loopHMDY(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopHMDY::InputHist(HistsHMDY* &myhists)
{
 this->myhists = myhists;

 if(myhists->doTopDD){
   doTopDD = true;
   topDD = myhists->topDD->Clone(iThread);
   topDD_HighMass_CosTheta = myhists->topDD_HighMass_CosTheta->Clone(iThread);
   topDD_HighMass_Rapidity = myhists->topDD_HighMass_Rapidity->Clone(iThread);
 }
}

void loopHMDY::InputTree(TreeForHMDY *HMDYTree)
{
 this->HMDYTree = HMDYTree;
 this->RootNames = HMDYTree->RootNames;

 this->RootTypes = HMDYTree->RootTypes;

 this->FirstFile = HMDYTree->FirstFile;
 this->EndFile = HMDYTree->EndFile;

 this->OneFilePerJob = HMDYTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = HMDYTree->TotalEntries[ifile];
 }
}

void loopHMDY::InputTree(TreeForPreHMDY *PreHMDYTree)
{
 isInputPreTree = true;

 this->PreHMDYTree = PreHMDYTree;
 this->RootNames = PreHMDYTree->RootNames;

 this->RootTypes = PreHMDYTree->RootTypes;

 this->SumOfWeightsMap = PreHMDYTree->SumOfWeightsMap;
 this->Years = PreHMDYTree->Years;
 this->DSIDs = PreHMDYTree->DSIDs;
 this->isLooseTree = PreHMDYTree->isLooseTree;

 this->FirstFile = PreHMDYTree->FirstFile;
 this->EndFile = PreHMDYTree->EndFile;

 this->OneFilePerJob = PreHMDYTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = PreHMDYTree->TotalEntries[ifile];
 }

 this->HMDYTree = new TreeForHMDY();

 if(JustGenerateTree){
   if(!NtupleName.Contains("root")) NtupleName = PreHMDYTree->SaveName;
   this->HMDYTree->GenerateFile(NtupleName);
   this->HMDYTree->DefineTree(0, "hmdyTree");
 }
}

void loopHMDY::InputNtupleName(TString NtupleName)
{
//this name will be override by the automatic name
 this->NtupleName = NtupleName;
}

void loopHMDY::ReadTree(int ifile)
{
 if(RootTypes.at(ifile) == "Data") isData = true;
 else isData = false;

 this->MCType = RootTypes.at(ifile);

 if(RootNames.at(ifile).Contains("_Loose_")) isLooseTree = true;
 else isLooseTree = false;

 if(HMDYTree->AdditionalWeightName.count(RootTypes.at(ifile)) > 0) isAdditionalWeight = true;
 else isAdditionalWeight = false;

 if(HMDYTree->Normalization.count(RootTypes.at(ifile)) > 0) isChangeNorm = true;
 else isChangeNorm = false;

 if(HMDYTree->SystematicName == "Fake_Matrix_Electron__1up" && (RootNames.at(ifile).Contains("ntuple_MM") || RootNames.at(ifile).Contains("Fake_Matrix_Electron"))) isElFake_up = true;
 else isElFake_up = false;

 if(HMDYTree->SystematicName == "Fake_Matrix_Electron__1down" && (RootNames.at(ifile).Contains("ntuple_MM") || RootNames.at(ifile).Contains("Fake_Matrix_Electron"))) isElFake_down = true;
 else isElFake_down = false;

 if(HMDYTree->SystematicName == "Fake_Matrix_Muon__1up" && (RootNames.at(ifile).Contains("matrix_Data_all_Dimuon") || RootNames.at(ifile).Contains("Fake_Matrix_Muon"))) isMuFake_up = true;
 else isMuFake_up = false;

 if(HMDYTree->SystematicName == "Fake_Matrix_Muon__1down" && (RootNames.at(ifile).Contains("matrix_Data_all_Dimuon") || RootNames.at(ifile).Contains("Fake_Matrix_Muon"))) isMuFake_down = true;
 else isMuFake_down = false;

 for(int ibkghist = 0; ibkghist < myhists->BkgHist_1d.size(); ibkghist++){
   myhists->BkgHist_1d.at(ibkghist)->HistPtr(iThread - 1)->Initial(RootTypes.at(ifile));
 }

 for(int iprocesshist = 0; iprocesshist < myhists->hist_process.size(); iprocesshist++){
   myhists->hist_process.at(iprocesshist)->Initial(iThread, RootTypes.at(ifile));
   if(isElFake_up || isElFake_down || isMuFake_up || isMuFake_down) myhists->hist_process.at(iprocesshist)->doFillFakeUnc();
 }

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"\r"<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<flush;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"\r"<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
     if(!isThread) cout<<"\r"<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
   }

   HMDYTree->GetEntry(ifile, iEvent);

   DefaultEvent.ResetEvent();

   DefaultEvent.Weight_Lepton1_SF             = HMDYTree->Weight_Lepton1_SF;
   DefaultEvent.Weight_Lepton2_SF             = HMDYTree->Weight_Lepton2_SF;
   DefaultEvent.RunNumber                     = HMDYTree->RunNumber;
   DefaultEvent.EventNumber                   = HMDYTree->EventNumber;
   DefaultEvent.mcChannelNumber               = HMDYTree->mcChannelNumber;
   DefaultEvent.RecoDilRapidity               = HMDYTree->RecoDilRapidity;
   DefaultEvent.RecoDilPhi                    = HMDYTree->RecoDilPhi;
   DefaultEvent.RecoDilMass                   = HMDYTree->RecoDilMass;
   DefaultEvent.RecoPseudoDilMass             = HMDYTree->RecoPseudoDilMass;
   DefaultEvent.RecoDilPt                     = HMDYTree->RecoDilPt;
   DefaultEvent.RecoPhiStar                   = HMDYTree->RecoPhiStar;
   DefaultEvent.RecoCosThetaStar              = HMDYTree->RecoCosThetaStar;
   DefaultEvent.RecoWeight                    = HMDYTree->RecoWeight;
   DefaultEvent.RecoWeight_Stat_up            = HMDYTree->RecoWeight_Stat_up;
   DefaultEvent.RecoWeight_Stat_down          = HMDYTree->RecoWeight_Stat_down;
   DefaultEvent.RecoWeight_PromptSubtr_up     = HMDYTree->RecoWeight_PromptSubtr_up;
   DefaultEvent.RecoWeight_PromptSubtr_down   = HMDYTree->RecoWeight_PromptSubtr_down;
   DefaultEvent.RecoWeight_MET_up             = HMDYTree->RecoWeight_MET_up;
   DefaultEvent.RecoWeight_MET_down           = HMDYTree->RecoWeight_MET_down;
   DefaultEvent.RecoWeight_d0sig_up           = HMDYTree->RecoWeight_d0sig_up;
   DefaultEvent.RecoWeight_d0sig_down         = HMDYTree->RecoWeight_d0sig_down;
   DefaultEvent.RecoWeight_RealStat_up        = HMDYTree->RecoWeight_RealStat_up;
   DefaultEvent.RecoWeight_RealStat_down      = HMDYTree->RecoWeight_RealStat_down;
   DefaultEvent.RecoWeight_FourTerm_TT        = HMDYTree->RecoWeight_FourTerm_TT;
   DefaultEvent.RecoWeight_FourTerm_TL        = HMDYTree->RecoWeight_FourTerm_TL;
   DefaultEvent.RecoWeight_FourTerm_LT        = HMDYTree->RecoWeight_FourTerm_LT;
   DefaultEvent.RecoWeight_FourTerm_LL        = HMDYTree->RecoWeight_FourTerm_LL;
   DefaultEvent.eeChannel                     = HMDYTree->eeChannel;
   DefaultEvent.mumuChannel                   = HMDYTree->mumuChannel;
   DefaultEvent.emuChannel                    = HMDYTree->emuChannel;
   DefaultEvent.eeChannel_withmuon            = HMDYTree->eeChannel_withmuon;
   DefaultEvent.SingleElectron                = HMDYTree->SingleElectron;

   if(RootNames.at(ifile).Contains("PI_ee")){
     DefaultEvent.mumuChannel = 0;
     DefaultEvent.isElSample = true;
   }
   if(RootNames.at(ifile).Contains("PI_mumu") || RootNames.at(ifile).Contains("PI_mm")){
     DefaultEvent.eeChannel = 0;
     DefaultEvent.isMuSample = true;
   }
   if(RootNames.at(ifile).Contains("DrellYan_ee")){
     DefaultEvent.mumuChannel = 0;
     DefaultEvent.isElSample = true;
   }
   if(RootNames.at(ifile).Contains("DrellYan_mumu") || RootNames.at(ifile).Contains("DrellYan_mm")){
     DefaultEvent.eeChannel = 0;
     DefaultEvent.isMuSample = true;
   }

   DefaultEvent.TruthDilMass_Born             = HMDYTree->TruthDilMass_Born;
   DefaultEvent.TruthDilRapidity_Born         = HMDYTree->TruthDilRapidity_Born;
   DefaultEvent.Lepton1_Pt                    = HMDYTree->Lepton1_Pt;
   DefaultEvent.Lepton2_Pt                    = HMDYTree->Lepton2_Pt;
   DefaultEvent.Lepton3_Pt                    = HMDYTree->Lepton3_Pt;
   DefaultEvent.Lepton1_Phi                   = HMDYTree->Lepton1_Phi;
   DefaultEvent.Lepton2_Phi                   = HMDYTree->Lepton2_Phi;
   DefaultEvent.Lepton3_Phi                   = HMDYTree->Lepton3_Phi;
   DefaultEvent.Lepton1_Eta                   = HMDYTree->Lepton1_Eta;
   DefaultEvent.Lepton2_Eta                   = HMDYTree->Lepton2_Eta;
   DefaultEvent.Lepton3_Eta                   = HMDYTree->Lepton3_Eta;
   DefaultEvent.pTllReweight                  = HMDYTree->pTllReweight;
   DefaultEvent.ChargeMisIDSFWeight           = HMDYTree->ChargeMisIDSFWeight;
   DefaultEvent.ChargeIDSFWeight              = HMDYTree->ChargeIDSFWeight;
   DefaultEvent.LeptonSFWeight                = HMDYTree->LeptonSFWeight;
   DefaultEvent.PileupWeight                  = HMDYTree->PileupWeight;
   DefaultEvent.TriggerSF                     = HMDYTree->TriggerSF;
   DefaultEvent.n_Bjets                       = HMDYTree->n_Bjets;
   DefaultEvent.MET_Et                        = HMDYTree->MET_Et;
   DefaultEvent.Lepton1_z0                    = HMDYTree->Lepton1_z0;
   DefaultEvent.Lepton2_z0                    = HMDYTree->Lepton2_z0;
   DefaultEvent.Lepton3_z0                    = HMDYTree->Lepton3_z0;
   DefaultEvent.Lepton1_d0sig                 = HMDYTree->Lepton1_d0sig;
   DefaultEvent.Lepton2_d0sig                 = HMDYTree->Lepton2_d0sig;
   DefaultEvent.Lepton3_d0sig                 = HMDYTree->Lepton3_d0sig;
   DefaultEvent.Lepton1_DeltaR                = HMDYTree->Lepton1_DeltaR;
   DefaultEvent.Lepton2_DeltaR                = HMDYTree->Lepton2_DeltaR;
   DefaultEvent.Mu                            = HMDYTree->Mu;
   DefaultEvent.MuActual                      = HMDYTree->MuActual;
   DefaultEvent.PhiRF                         = HMDYTree->PhiRF;
   DefaultEvent.Weight_kFactor_Old            = HMDYTree->Weight_kFactor_Old;
   DefaultEvent.Weight_kFactor_QCDEW          = HMDYTree->Weight_kFactor_QCDEW;
   DefaultEvent.Weight_kFactor_New_CT18NNLO   = HMDYTree->Weight_kFactor_New_CT18NNLO;
   DefaultEvent.Weight_kFactor_New_CT18ANNLO  = HMDYTree->Weight_kFactor_New_CT18ANNLO;
   DefaultEvent.Weight_kFactor_PowhegtoSherpa = HMDYTree->Weight_kFactor_PowhegtoSherpa;

   DefaultEvent.Lepton_Pt_born                = HMDYTree->Lepton_Pt_born;
   DefaultEvent.AntiLepton_Pt_born            = HMDYTree->AntiLepton_Pt_born;
   DefaultEvent.Lepton_Eta_born               = HMDYTree->Lepton_Eta_born;
   DefaultEvent.AntiLepton_Eta_born           = HMDYTree->AntiLepton_Eta_born;
   DefaultEvent.Lepton_Phi_born               = HMDYTree->Lepton_Phi_born;
   DefaultEvent.AntiLepton_Phi_born           = HMDYTree->AntiLepton_Phi_born;
   DefaultEvent.Lepton_m_born                 = HMDYTree->Lepton_m_born;
   DefaultEvent.AntiLepton_m_born             = HMDYTree->AntiLepton_m_born;
   DefaultEvent.Lepton_Pt_bare                = HMDYTree->Lepton_Pt_bare;
   DefaultEvent.AntiLepton_Pt_bare            = HMDYTree->AntiLepton_Pt_bare;
   DefaultEvent.Lepton_Eta_bare               = HMDYTree->Lepton_Eta_bare;
   DefaultEvent.AntiLepton_Eta_bare           = HMDYTree->AntiLepton_Eta_bare;
   DefaultEvent.Lepton_Phi_bare               = HMDYTree->Lepton_Phi_bare;
   DefaultEvent.AntiLepton_Phi_bare           = HMDYTree->AntiLepton_Phi_bare;
   DefaultEvent.Lepton_Pt_dressed             = HMDYTree->Lepton_Pt_dressed;
   DefaultEvent.Lepton_Eta_dressed            = HMDYTree->Lepton_Eta_dressed;
   DefaultEvent.Lepton_Phi_dressed            = HMDYTree->Lepton_Phi_dressed;
   DefaultEvent.Lepton_Charge_dressed         = HMDYTree->Lepton_Charge_dressed;
   DefaultEvent.AntiLepton_Pt_dressed         = HMDYTree->AntiLepton_Pt_dressed;
   DefaultEvent.AntiLepton_Eta_dressed        = HMDYTree->AntiLepton_Eta_dressed;
   DefaultEvent.AntiLepton_Phi_dressed        = HMDYTree->AntiLepton_Phi_dressed;
   DefaultEvent.AntiLepton_Charge_dressed     = HMDYTree->AntiLepton_Charge_dressed;

   DefaultEvent.pass_ee_TT                    = HMDYTree->pass_ee_TT;
   DefaultEvent.pass_ee_TL                    = HMDYTree->pass_ee_TL;
   DefaultEvent.pass_ee_LT                    = HMDYTree->pass_ee_LT;
   DefaultEvent.pass_ee_LL                    = HMDYTree->pass_ee_LL;
   DefaultEvent.pass_mm_TT                    = HMDYTree->pass_mm_TT;
   DefaultEvent.pass_mm_TL                    = HMDYTree->pass_mm_TL;
   DefaultEvent.pass_mm_LT                    = HMDYTree->pass_mm_LT;
   DefaultEvent.pass_mm_LL                    = HMDYTree->pass_mm_LL;
   DefaultEvent.Lepton1_isTight               = HMDYTree->Lepton1_isTight;
   DefaultEvent.Lepton2_isTight               = HMDYTree->Lepton2_isTight;
   DefaultEvent.Lepton3_isTight               = HMDYTree->Lepton3_isTight;
   DefaultEvent.Lepton1_passMediumID          = HMDYTree->Lepton1_passMediumID;
   DefaultEvent.Lepton2_passMediumID          = HMDYTree->Lepton2_passMediumID;
   DefaultEvent.Lepton3_passMediumID          = HMDYTree->Lepton3_passMediumID;
   DefaultEvent.Lepton1_passLooseID           = HMDYTree->Lepton1_passLooseID;
   DefaultEvent.Lepton2_passLooseID           = HMDYTree->Lepton2_passLooseID;
   DefaultEvent.Lepton3_passLooseID           = HMDYTree->Lepton3_passLooseID;
   DefaultEvent.Lepton1_passIso               = HMDYTree->Lepton1_passIso;
   DefaultEvent.Lepton2_passIso               = HMDYTree->Lepton2_passIso;
   DefaultEvent.Lepton1_IsoWeight             = HMDYTree->Lepton1_IsoWeight;
   DefaultEvent.Lepton2_IsoWeight             = HMDYTree->Lepton2_IsoWeight;

   DefaultEvent.Lepton1_Charge                = HMDYTree->Lepton1_Charge;
   DefaultEvent.Lepton2_Charge                = HMDYTree->Lepton2_Charge;
   DefaultEvent.Lepton1_isTruthMatch          = HMDYTree->Lepton1_isTruthMatch;
   DefaultEvent.Lepton2_isTruthMatch          = HMDYTree->Lepton2_isTruthMatch;
   DefaultEvent.Lepton1_TightWeight           = HMDYTree->Lepton1_TightWeight;
   DefaultEvent.Lepton2_TightWeight           = HMDYTree->Lepton2_TightWeight;
   DefaultEvent.Lepton3_TightWeight           = HMDYTree->Lepton3_TightWeight;
   DefaultEvent.Lepton1_LooseWeight           = HMDYTree->Lepton1_LooseWeight;
   DefaultEvent.Lepton2_LooseWeight           = HMDYTree->Lepton2_LooseWeight;
   DefaultEvent.Lepton3_LooseWeight           = HMDYTree->Lepton3_LooseWeight;
   DefaultEvent.Lepton1_MediumIDWeight        = HMDYTree->Lepton1_MediumIDWeight;
   DefaultEvent.Lepton2_MediumIDWeight        = HMDYTree->Lepton2_MediumIDWeight;
   DefaultEvent.PrescaleFactor                = HMDYTree->PrescaleFactor;
   DefaultEvent.Lepton1_PrescaleFactor        = HMDYTree->Lepton1_PrescaleFactor;
   DefaultEvent.Lepton2_PrescaleFactor        = HMDYTree->Lepton2_PrescaleFactor;

   //if(DefaultEvent.eeChannel && !DefaultEvent.mumuChannel && !DefaultEvent.emuChannel
   //&& DefaultEvent.pass_ee_TT
   //&& DefaultEvent.Lepton1_Pt > 40.0 && DefaultEvent.Lepton2_Pt > 30.0
   //&& DefaultEvent.RecoDilMass > 116.0 && DefaultEvent.RecoDilMass < 130.0){
   //  cout<<DefaultEvent.EventNumber<<endl;
   //}

   //if(DefaultEvent.mcChannelNumber == 301010){
   //  cout<<DefaultEvent.EventNumber<<endl;
   //}
   //else continue;

   //if(DefaultEvent.RecoDilMass > 175.0 && DefaultEvent.RecoDilMass < 200.0
   //&& DefaultEvent.Lepton1_Pt > 40.0 && DefaultEvent.Lepton2_Pt > 30.0
   //&& DefaultEvent.eeChannel && !DefaultEvent.mumuChannel && !DefaultEvent.emuChannel
   //&& !(DefaultEvent.TruthDilMass_Born > 120.0 && DefaultEvent.mcChannelNumber == 361106.0)){
   //  cout<<DefaultEvent.EventNumber<<"  "<<DefaultEvent.RecoDilMass<<"  "<<DefaultEvent.RecoWeight<<"  "<<DefaultEvent.LeptonSFWeight<<"  "<<DefaultEvent.Weight_kFactor_New_CT18ANNLO<<"  ";
   //  cout<<DefaultEvent.PileupWeight<<"  "<<DefaultEvent.ChargeMisIDSFWeight<<endl;
   //}

   if(isAdditionalWeight) DefaultEvent.AdditionalWeight = HMDYTree->AdditionalWeight.at(MCType);
   if(isChangeNorm) DefaultEvent.Normalization = HMDYTree->Normalization.at(MCType);

   FillHist(DefaultEvent);
 }

}

void loopHMDY::PreLoop(int ifile)
{
 if(RootTypes.at(ifile) == "Data") isData = true;
 else isData = false;

 for(int ibkghist = 0; ibkghist < myhists->BkgHist_1d.size(); ibkghist++){
   myhists->BkgHist_1d.at(ibkghist)->HistPtr(iThread - 1)->Initial(RootTypes.at(ifile));
 }

 for(int iprocesshist = 0; iprocesshist < myhists->hist_process.size(); iprocesshist++){
   myhists->hist_process.at(iprocesshist)->Initial(iThread, RootTypes.at(ifile));
 }

 PreHMDYTree->GetEntry(ifile, 0);
 CrossSection = GetHMDYCrossSection(PreHMDYTree->mcChannelNumber);

 int DSID = DSIDs.at(ifile);
 int Year = Years.at(ifile);
 pair<int, int> RootTypePair;
 RootTypePair = make_pair(DSID, Year);
 SumOfWeight = SumOfWeightsMap.at(RootTypePair);

 if(isData) SumOfWeight = 1.0;

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"\r"<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<flush;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"\r"<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
     if(!isThread) cout<<"\r"<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
   }

   PreHMDYTree->GetEntry(ifile, iEvent);

   if(FillEvents()){
     if(JustGenerateTree) HMDYTree->FillTree(0);

     if(FinishProcess) FillHist(SelectedEvent);
   }

 }

}

bool loopHMDY::FillEvents()
{
 SelectedEvent.ResetEvent();

 bool ElTriggerSelectionPassed = false;

 // Trigger
 if(PreHMDYTree->mcChannelNumber < 10){
   if(PreHMDYTree->runNumber >= 276073. && PreHMDYTree->runNumber <= 284484. && PreHMDYTree->HLT_2e12_lhloose_L12EM10VH)
     ElTriggerSelectionPassed = true;

   if(PreHMDYTree->runNumber >= 297730. && PreHMDYTree->runNumber <= 314199. && PreHMDYTree->HLT_2e17_lhvloose_nod0)
     ElTriggerSelectionPassed = true;

   if(PreHMDYTree->runNumber >= 325713. && PreHMDYTree->runNumber <= 340453. && PreHMDYTree->HLT_2e24_lhvloose_nod0)
     ElTriggerSelectionPassed = true;

   if(PreHMDYTree->runNumber >= 348885. && PreHMDYTree->runNumber <= 364292. && PreHMDYTree->HLT_2e24_lhvloose_nod0)
     ElTriggerSelectionPassed = true;
 }
 else{
   if(PreHMDYTree->randomRunNumber >= 276073. && PreHMDYTree->randomRunNumber <= 284484. && PreHMDYTree->HLT_2e12_lhloose_L12EM10VH)
     ElTriggerSelectionPassed = true;

   if(PreHMDYTree->randomRunNumber >= 297730. && PreHMDYTree->randomRunNumber <= 314199. && PreHMDYTree->HLT_2e17_lhvloose_nod0)
     ElTriggerSelectionPassed = true;

   if(PreHMDYTree->randomRunNumber >= 325713. && PreHMDYTree->randomRunNumber <= 340453. && (PreHMDYTree->HLT_2e24_lhvloose_nod0))
     ElTriggerSelectionPassed = true;

   if(PreHMDYTree->randomRunNumber >= 348885. && PreHMDYTree->randomRunNumber <= 364292. && (PreHMDYTree->HLT_2e24_lhvloose_nod0))
     ElTriggerSelectionPassed = true;
 }

 bool FakeElTriggerSelectionPassed = false;

 if(PreHMDYTree->mcChannelNumber < 10){
   if(PreHMDYTree->runNumber >= 276073. && PreHMDYTree->runNumber <= 284484. && (PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH || PreHMDYTree->HLT_e60_lhvloose_nod0)){
     FakeElTriggerSelectionPassed = true;
     if(PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH) SelectedEvent.PrescaleFactor = PreHMDYTree->PS_HLT_e26_lhvloose_nod0_L1EM20VH;
     else if(PreHMDYTree->HLT_e60_lhvloose_nod0) SelectedEvent.PrescaleFactor = PreHMDYTree->PS_HLT_e60_lhvloose_nod0;
   }

   if(PreHMDYTree->runNumber >= 297730. && PreHMDYTree->runNumber <= 314199. && (PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH || PreHMDYTree->HLT_e60_lhvloose_nod0 || PreHMDYTree->HLT_e120_lhvloose_nod0 || PreHMDYTree->HLT_e140_lhvloose_nod0)){
     FakeElTriggerSelectionPassed = true;
     if(PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH) SelectedEvent.PrescaleFactor = PreHMDYTree->PS_HLT_e26_lhvloose_nod0_L1EM20VH;
     else if(PreHMDYTree->HLT_e60_lhvloose_nod0) SelectedEvent.PrescaleFactor = PreHMDYTree->PS_HLT_e60_lhvloose_nod0;
     else if(PreHMDYTree->HLT_e120_lhvloose_nod0) SelectedEvent.PrescaleFactor = PreHMDYTree->PS_HLT_e120_lhvloose_nod0;
     else if(PreHMDYTree->HLT_e140_lhvloose_nod0) SelectedEvent.PrescaleFactor = PreHMDYTree->PS_HLT_e140_lhvloose_nod0;
   }

   if(PreHMDYTree->runNumber >= 325713. && PreHMDYTree->runNumber <= 340453. && (PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH || PreHMDYTree->HLT_e60_lhvloose_nod0 || PreHMDYTree->HLT_e140_lhvloose_nod0)){
     FakeElTriggerSelectionPassed = true;
     if(PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH) SelectedEvent.PrescaleFactor = PreHMDYTree->PS_HLT_e26_lhvloose_nod0_L1EM20VH;
     else if(PreHMDYTree->HLT_e60_lhvloose_nod0) SelectedEvent.PrescaleFactor = PreHMDYTree->PS_HLT_e60_lhvloose_nod0;
     else if(PreHMDYTree->HLT_e140_lhvloose_nod0) SelectedEvent.PrescaleFactor = PreHMDYTree->PS_HLT_e140_lhvloose_nod0;
   }

   if(PreHMDYTree->runNumber >= 348885. && PreHMDYTree->runNumber <= 364292. && (PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM22VH || PreHMDYTree->HLT_e60_lhvloose_nod0 || PreHMDYTree->HLT_e140_lhvloose_nod0)){
     FakeElTriggerSelectionPassed = true;
     if(PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM22VH) SelectedEvent.PrescaleFactor = PreHMDYTree->PS_HLT_e26_lhvloose_nod0_L1EM22VH;
     else if(PreHMDYTree->HLT_e60_lhvloose_nod0) SelectedEvent.PrescaleFactor = PreHMDYTree->PS_HLT_e60_lhvloose_nod0;
     else if(PreHMDYTree->HLT_e140_lhvloose_nod0) SelectedEvent.PrescaleFactor = PreHMDYTree->PS_HLT_e140_lhvloose_nod0;
   }
 }
 else{
   if(PreHMDYTree->runNumber == 284500. && (PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH || PreHMDYTree->HLT_e60_lhvloose_nod0 || PreHMDYTree->HLT_e120_lhvloose_nod0 || PreHMDYTree->HLT_e140_lhvloose_nod0))
     FakeElTriggerSelectionPassed = true;

   if(PreHMDYTree->runNumber == 300000. && (PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH || PreHMDYTree->HLT_e60_lhvloose_nod0 || PreHMDYTree->HLT_e140_lhvloose_nod0))
     FakeElTriggerSelectionPassed = true;

   if(PreHMDYTree->runNumber == 310000. && (PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM22VH || PreHMDYTree->HLT_e60_lhvloose_nod0 || PreHMDYTree->HLT_e140_lhvloose_nod0))
     FakeElTriggerSelectionPassed = true;
 }

 bool PassTrig = false;

 if(isNormalRun || isElRealEffRun || isMuRealEffRun || isUnfoldRun) PassTrig = ElTriggerSelectionPassed;

 if(isElFakeEffRun) PassTrig = FakeElTriggerSelectionPassed; 

 //if(!TriggerSelectionPassed) return false;

 // Truth
 if(!isData){
   SelectedEvent.TruthDilMass_Born = PreHMDYTree->Dilepton_Mass_born;
   SelectedEvent.TruthDilRapidity_Born = fabs(PreHMDYTree->Dilepton_Rapidity_born);
 }

// if(PreHMDYTree->mcChannelNumber == 361106 || PreHMDYTree->mcChannelNumber == 361107){
//   if(SelectedEvent.TruthDilMass_Born <= 120.0) return false;
// }
 /////////////////////////////////////////////////////////////////////////////////////////////////

 double Lumi = 0.0;
 if(PreHMDYTree->runNumber == 284500.0){
   Lumi = 36.64674;
 }
 if(PreHMDYTree->runNumber == 300000.0){
   Lumi = 44.6306;
 }
 if(PreHMDYTree->runNumber == 310000.0){
   Lumi = 58.7916;
 }

 int nElectron = 0;
 int nTightElectron = 0;
 vector<int> ElectronIndex;
 for(int i = 0; i < PreHMDYTree->el_pt->size(); i++){
   if(PreHMDYTree->el_pt->at(i) < 28000.0) continue;
   nElectron++;
   ElectronIndex.push_back(i);

   //if(PreHMDYTree->el_pt->size() != PreHMDYTree->el_isTight->size()) continue; // HMDY+b Sample

   if(isLooseTree){
     if(!PreHMDYTree->el_isTight->at(i)) continue;
     nTightElectron++;
   }
 }

 int nMuon = 0;
 int nTightMuon = 0;
 vector<int> MuonIndex;
 for(int i = 0; i < PreHMDYTree->mu_pt->size(); i++){
   if(PreHMDYTree->mu_pt->at(i) < 28000.0) continue;
   if(fabs(PreHMDYTree->mu_eta->at(i)) > 2.5) continue;
   nMuon++;
   MuonIndex.push_back(i);

   if(isLooseTree){
     if(!PreHMDYTree->mu_isTight->at(i)) continue;
     nTightMuon++;
   }
 }

 if(nElectron >= 1 && nMuon == 0 && PreHMDYTree->SingleElectron && FakeElTriggerSelectionPassed && isElFakeEffRun){

   SelectedEvent.Lepton1.P4.SetPtEtaPhiE(PreHMDYTree->el_pt->at(ElectronIndex.at(0)) / 1000.0, PreHMDYTree->el_eta->at(ElectronIndex.at(0)), PreHMDYTree->el_phi->at(ElectronIndex.at(0)), PreHMDYTree->el_e->at(ElectronIndex.at(0)) / 1000.0);

   SelectedEvent.Lepton1.Flavor = 11;
   SelectedEvent.Lepton1.Charge = PreHMDYTree->el_charge->at(ElectronIndex.at(0));
   if(isLooseTree) SelectedEvent.Lepton1.isTight = PreHMDYTree->el_isTight->at(ElectronIndex.at(0));

   if(isLooseTree){
     SelectedEvent.Lepton1.RecoSF = PreHMDYTree->el_SF_Reco_Corr->at(ElectronIndex.at(0));
     SelectedEvent.Lepton1.IDSF = PreHMDYTree->el_SF_ID_MediumLH->at(ElectronIndex.at(0));
     SelectedEvent.Lepton1.LooseIDSF = PreHMDYTree->el_SF_ID_LooseAndBLayerLH->at(ElectronIndex.at(0));
     //SelectedEvent.Lepton1.LooseIDSF = PreHMDYTree->el_SF_ID_MediumLH->at(ElectronIndex.at(0));
     SelectedEvent.Lepton1.IsoSF = PreHMDYTree->el_SF_Iso_FCTight->at(ElectronIndex.at(0));

     SelectedEvent.Lepton1.TightWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.IDSF * SelectedEvent.Lepton1.IsoSF;
     SelectedEvent.Lepton1.LooseWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.LooseIDSF;

     SelectedEvent.Lepton1.mediumID = PreHMDYTree->el_isElMedium->at(ElectronIndex.at(0));
     SelectedEvent.Lepton1.looseID = PreHMDYTree->el_isElLoose->at(ElectronIndex.at(0));
     //SelectedEvent.Lepton1.looseID = PreHMDYTree->el_isElMedium->at(ElectronIndex.at(0));
   }

   SelectedEvent.Lepton1.z0 = PreHMDYTree->el_delta_z0_sintheta->at(ElectronIndex.at(0));
   SelectedEvent.Lepton1.d0Sig = PreHMDYTree->el_d0sig->at(ElectronIndex.at(0));

   int Index = ElectronIndex.at(0);

   SelectedEvent.eeChannel = false;
   SelectedEvent.mumuChannel = false;
   SelectedEvent.emuChannel = false;
   SelectedEvent.SingleElectron = true;

   if(nElectron == 2){
     SelectedEvent.Lepton2.P4.SetPtEtaPhiE(PreHMDYTree->el_pt->at(ElectronIndex.at(1)) / 1000.0, PreHMDYTree->el_eta->at(ElectronIndex.at(1)), PreHMDYTree->el_phi->at(ElectronIndex.at(1)), PreHMDYTree->el_e->at(ElectronIndex.at(1)) / 1000.0);

     SelectedEvent.Lepton2.Flavor = 11;
     SelectedEvent.Lepton2.Charge = PreHMDYTree->el_charge->at(ElectronIndex.at(1));
     if(isLooseTree) SelectedEvent.Lepton2.isTight = PreHMDYTree->el_isTight->at(ElectronIndex.at(1));
  
     if(isLooseTree){
       SelectedEvent.Lepton2.RecoSF = PreHMDYTree->el_SF_Reco_Corr->at(ElectronIndex.at(1));
       SelectedEvent.Lepton2.IDSF = PreHMDYTree->el_SF_ID_MediumLH->at(ElectronIndex.at(1));
       SelectedEvent.Lepton2.LooseIDSF = PreHMDYTree->el_SF_ID_LooseAndBLayerLH->at(ElectronIndex.at(1));
       //SelectedEvent.Lepton2.LooseIDSF = PreHMDYTree->el_SF_ID_MediumLH->at(ElectronIndex.at(1));
       SelectedEvent.Lepton2.IsoSF = PreHMDYTree->el_SF_Iso_FCTight->at(ElectronIndex.at(1));
  
       SelectedEvent.Lepton2.TightWeight = SelectedEvent.Lepton2.RecoSF * SelectedEvent.Lepton2.IDSF * SelectedEvent.Lepton2.IsoSF;
       SelectedEvent.Lepton2.LooseWeight = SelectedEvent.Lepton2.RecoSF * SelectedEvent.Lepton2.LooseIDSF;
  
       SelectedEvent.Lepton2.mediumID = PreHMDYTree->el_isElMedium->at(ElectronIndex.at(1));
       SelectedEvent.Lepton2.looseID = PreHMDYTree->el_isElLoose->at(ElectronIndex.at(1));
       //SelectedEvent.Lepton2.looseID = PreHMDYTree->el_isElMedium->at(ElectronIndex.at(1));
     }
  
     SelectedEvent.Lepton2.z0 = PreHMDYTree->el_delta_z0_sintheta->at(ElectronIndex.at(1));
     SelectedEvent.Lepton2.d0Sig = PreHMDYTree->el_d0sig->at(ElectronIndex.at(1));

     if(SelectedEvent.Lepton1.P4.Pt() < SelectedEvent.Lepton2.P4.Pt()){
       HMDYLepton Lepton_tmp = SelectedEvent.Lepton1;
       SelectedEvent.Lepton1 = SelectedEvent.Lepton2;
       SelectedEvent.Lepton2 = Lepton_tmp;

       Index = ElectronIndex.at(1);
     }

     SelectedEvent.eeChannel = true;
   }

   if(isLooseTree){
     if(PreHMDYTree->mcChannelNumber < 10){
       if(PreHMDYTree->runNumber >= 276073. && PreHMDYTree->runNumber <= 284484.){

         if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 65.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH * PreHMDYTree->el_trigMatch_HLT_e26_lhvloose_nod0_L1EM20VH->at(Index) * PreHMDYTree->PS_HLT_e26_lhvloose_nod0_L1EM20VH;
         else if(SelectedEvent.Lepton1.P4.Pt() > 65.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e60_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e60_lhvloose_nod0->at(Index) * PreHMDYTree->PS_HLT_e60_lhvloose_nod0;

       }

       if(PreHMDYTree->runNumber >= 297730. && PreHMDYTree->runNumber <= 314199.){

         if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 65.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH * PreHMDYTree->el_trigMatch_HLT_e26_lhvloose_nod0_L1EM20VH->at(Index) * PreHMDYTree->PS_HLT_e26_lhvloose_nod0_L1EM20VH;
         else if(SelectedEvent.Lepton1.P4.Pt() > 65.0 && SelectedEvent.Lepton1.P4.Pt() < 126.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e60_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e60_lhvloose_nod0->at(Index) * PreHMDYTree->PS_HLT_e60_lhvloose_nod0;
         else if(SelectedEvent.Lepton1.P4.Pt() > 126.0 && SelectedEvent.Lepton1.P4.Pt() < 147.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e120_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e120_lhvloose_nod0->at(Index) * PreHMDYTree->PS_HLT_e120_lhvloose_nod0;
         else if(SelectedEvent.Lepton1.P4.Pt() > 147.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e140_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e140_lhvloose_nod0->at(Index) * PreHMDYTree->PS_HLT_e140_lhvloose_nod0;

       }

       if(PreHMDYTree->runNumber >= 325713. && PreHMDYTree->runNumber <= 340453.){

         if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 65.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH * PreHMDYTree->el_trigMatch_HLT_e26_lhvloose_nod0_L1EM20VH->at(Index) * PreHMDYTree->PS_HLT_e26_lhvloose_nod0_L1EM20VH;
         else if(SelectedEvent.Lepton1.P4.Pt() > 65.0 && SelectedEvent.Lepton1.P4.Pt() < 147.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e60_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e60_lhvloose_nod0->at(Index) * PreHMDYTree->PS_HLT_e60_lhvloose_nod0;
         else if(SelectedEvent.Lepton1.P4.Pt() > 147.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e140_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e140_lhvloose_nod0->at(Index) * PreHMDYTree->PS_HLT_e140_lhvloose_nod0;

       }

       if(PreHMDYTree->runNumber >= 348885. && PreHMDYTree->runNumber <= 364292.){

         if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 65.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM22VH * PreHMDYTree->el_trigMatch_HLT_e26_lhvloose_nod0_L1EM22VH->at(Index) * PreHMDYTree->PS_HLT_e26_lhvloose_nod0_L1EM22VH;
         else if(SelectedEvent.Lepton1.P4.Pt() > 65.0 && SelectedEvent.Lepton1.P4.Pt() < 147.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e60_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e60_lhvloose_nod0->at(Index) * PreHMDYTree->PS_HLT_e60_lhvloose_nod0;
         else if(SelectedEvent.Lepton1.P4.Pt() > 147.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e140_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e140_lhvloose_nod0->at(Index) * PreHMDYTree->PS_HLT_e140_lhvloose_nod0;

       }
     }
     else{

       if(PreHMDYTree->runNumber == 284500.){

         if(PreHMDYTree->randomRunNumber >= 276073. && PreHMDYTree->randomRunNumber <= 284484.){
  
           if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 65.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH * PreHMDYTree->el_trigMatch_HLT_e26_lhvloose_nod0_L1EM20VH->at(Index) * 1.0;
           else if(SelectedEvent.Lepton1.P4.Pt() > 65.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e60_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e60_lhvloose_nod0->at(Index) *  1.0;

         }
  
         if(PreHMDYTree->randomRunNumber >= 297730. && PreHMDYTree->randomRunNumber <= 314199.){
  
           if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 65.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH * PreHMDYTree->el_trigMatch_HLT_e26_lhvloose_nod0_L1EM20VH->at(Index) * 1.0;
           else if(SelectedEvent.Lepton1.P4.Pt() > 65.0 && SelectedEvent.Lepton1.P4.Pt() < 126.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e60_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e60_lhvloose_nod0->at(Index) * 1.0;
           else if(SelectedEvent.Lepton1.P4.Pt() > 126.0 && SelectedEvent.Lepton1.P4.Pt() < 147.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e120_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e120_lhvloose_nod0->at(Index) * 1.0;
           else if(SelectedEvent.Lepton1.P4.Pt() > 147.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e140_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e140_lhvloose_nod0->at(Index) * 1.0;

         }

       }

       if(PreHMDYTree->runNumber == 300000.){
         if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 65.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM20VH * PreHMDYTree->el_trigMatch_HLT_e26_lhvloose_nod0_L1EM20VH->at(Index) * 1.0;
         else if(SelectedEvent.Lepton1.P4.Pt() > 65.0 && SelectedEvent.Lepton1.P4.Pt() < 147.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e60_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e60_lhvloose_nod0->at(Index) * 1.0;
         else if(SelectedEvent.Lepton1.P4.Pt() > 147.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e140_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e140_lhvloose_nod0->at(Index) * 1.0;

       }

       if(PreHMDYTree->runNumber == 310000.){
         if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 65.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e26_lhvloose_nod0_L1EM22VH * PreHMDYTree->el_trigMatch_HLT_e26_lhvloose_nod0_L1EM22VH->at(Index) * 1.0;
         else if(SelectedEvent.Lepton1.P4.Pt() > 65.0 && SelectedEvent.Lepton1.P4.Pt() < 147.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e60_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e60_lhvloose_nod0->at(Index) * 1.0;
         else if(SelectedEvent.Lepton1.P4.Pt() > 147.0) SelectedEvent.Lepton1.PrescaleFactor = PreHMDYTree->HLT_e140_lhvloose_nod0 * PreHMDYTree->el_trigMatch_HLT_e140_lhvloose_nod0->at(Index) * 1.0;

       }
     }

   }


 }
 else if(nElectron == 2 && nTightMuon == 0 && PreHMDYTree->eeSelection && PassTrig){
   SelectedEvent.Lepton1.P4.SetPtEtaPhiE(PreHMDYTree->el_pt->at(ElectronIndex.at(0)) / 1000.0, PreHMDYTree->el_eta->at(ElectronIndex.at(0)), PreHMDYTree->el_phi->at(ElectronIndex.at(0)), PreHMDYTree->el_e->at(ElectronIndex.at(0)) / 1000.0);
   SelectedEvent.Lepton2.P4.SetPtEtaPhiE(PreHMDYTree->el_pt->at(ElectronIndex.at(1)) / 1000.0, PreHMDYTree->el_eta->at(ElectronIndex.at(1)), PreHMDYTree->el_phi->at(ElectronIndex.at(1)), PreHMDYTree->el_e->at(ElectronIndex.at(1)) / 1000.0);

   SelectedEvent.Lepton1.Flavor = 11;
   SelectedEvent.Lepton1.Charge = PreHMDYTree->el_charge->at(ElectronIndex.at(0));

   if(isLooseTree){
     SelectedEvent.Lepton1.isTight = PreHMDYTree->el_isTight->at(ElectronIndex.at(0));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.RecoSF = PreHMDYTree->el_SF_Reco_Corr->at(ElectronIndex.at(0));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.IDSF = PreHMDYTree->el_SF_ID_MediumLH->at(ElectronIndex.at(0));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.LooseIDSF = PreHMDYTree->el_SF_ID_LooseAndBLayerLH->at(ElectronIndex.at(0));
     //if(isElRealEffRun) SelectedEvent.Lepton1.LooseIDSF = PreHMDYTree->el_SF_ID_MediumLH->at(ElectronIndex.at(0));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.IsoSF = PreHMDYTree->el_SF_Iso_FCTight->at(ElectronIndex.at(0));

     SelectedEvent.Lepton1.TightWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.IDSF * SelectedEvent.Lepton1.IsoSF;
     SelectedEvent.Lepton1.LooseWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.LooseIDSF;

     SelectedEvent.Lepton1.mediumID = PreHMDYTree->el_isElMedium->at(ElectronIndex.at(0));
     SelectedEvent.Lepton1.looseID = PreHMDYTree->el_isElLoose->at(ElectronIndex.at(0));
     //SelectedEvent.Lepton1.looseID = PreHMDYTree->el_isElMedium->at(ElectronIndex.at(0));
     SelectedEvent.Lepton1.FCTightIso = PreHMDYTree->el_isolation_FixedCutTight->at(ElectronIndex.at(0));
   }

   SelectedEvent.Lepton1.z0 = PreHMDYTree->el_delta_z0_sintheta->at(ElectronIndex.at(0));
   SelectedEvent.Lepton1.d0Sig = PreHMDYTree->el_d0sig->at(ElectronIndex.at(0));

   SelectedEvent.Lepton2.Flavor = 11;
   SelectedEvent.Lepton2.Charge = PreHMDYTree->el_charge->at(ElectronIndex.at(1));

   if(isLooseTree){
     SelectedEvent.Lepton2.isTight = PreHMDYTree->el_isTight->at(ElectronIndex.at(1));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.RecoSF = PreHMDYTree->el_SF_Reco_Corr->at(ElectronIndex.at(1));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.IDSF = PreHMDYTree->el_SF_ID_MediumLH->at(ElectronIndex.at(1));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.LooseIDSF = PreHMDYTree->el_SF_ID_LooseAndBLayerLH->at(ElectronIndex.at(1));
     //if(isElRealEffRun) SelectedEvent.Lepton2.LooseIDSF = PreHMDYTree->el_SF_ID_MediumLH->at(ElectronIndex.at(1));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.IsoSF = PreHMDYTree->el_SF_Iso_FCTight->at(ElectronIndex.at(1));

     SelectedEvent.Lepton2.TightWeight = SelectedEvent.Lepton2.RecoSF * SelectedEvent.Lepton2.IDSF * SelectedEvent.Lepton2.IsoSF;
     SelectedEvent.Lepton2.LooseWeight = SelectedEvent.Lepton2.RecoSF * SelectedEvent.Lepton2.LooseIDSF;

     SelectedEvent.Lepton2.mediumID = PreHMDYTree->el_isElMedium->at(ElectronIndex.at(1));
     SelectedEvent.Lepton2.looseID = PreHMDYTree->el_isElLoose->at(ElectronIndex.at(1));
     //SelectedEvent.Lepton2.looseID = PreHMDYTree->el_isElMedium->at(ElectronIndex.at(1));
     SelectedEvent.Lepton2.FCTightIso = PreHMDYTree->el_isolation_FixedCutTight->at(ElectronIndex.at(1));
   }

   SelectedEvent.Lepton2.z0 = PreHMDYTree->el_delta_z0_sintheta->at(ElectronIndex.at(1));
   SelectedEvent.Lepton2.d0Sig = PreHMDYTree->el_d0sig->at(ElectronIndex.at(1));

   SelectedEvent.eeChannel = true;
   SelectedEvent.mumuChannel = false;
   SelectedEvent.emuChannel = false;

   if(doMuFakeBkg || doElMuFakeBkg) return false;
 }
 else if(nElectron == 0 && nMuon == 2 && PreHMDYTree->mumuSelection){
   SelectedEvent.Lepton1.P4.SetPtEtaPhiE(PreHMDYTree->mu_pt->at(MuonIndex.at(0)) / 1000.0, PreHMDYTree->mu_eta->at(MuonIndex.at(0)), PreHMDYTree->mu_phi->at(MuonIndex.at(0)), PreHMDYTree->mu_e->at(MuonIndex.at(0)) / 1000.0);
   SelectedEvent.Lepton2.P4.SetPtEtaPhiE(PreHMDYTree->mu_pt->at(MuonIndex.at(1)) / 1000.0, PreHMDYTree->mu_eta->at(MuonIndex.at(1)), PreHMDYTree->mu_phi->at(MuonIndex.at(1)), PreHMDYTree->mu_e->at(MuonIndex.at(1)) / 1000.0);

   SelectedEvent.Lepton1.Flavor = 13;
   SelectedEvent.Lepton1.Charge = PreHMDYTree->mu_charge->at(MuonIndex.at(0));
   if(isHMDYinclusiveWP){
     if(isLooseTree) SelectedEvent.Lepton1.isTight = PreHMDYTree->mu_isTight->at(MuonIndex.at(0));// For inclusive HMDY
   }
   else{
     if(isLooseTree) SelectedEvent.Lepton1.isTight = PreHMDYTree->mu_isHighPt->at(MuonIndex.at(0)) * PreHMDYTree->mu_isolation_TightTrackOnly_VarRad->at(MuonIndex.at(0));// For HMDY+b
   }

   if(isLooseTree){
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.TTVASF = PreHMDYTree->mu_SF_TTVA->at(MuonIndex.at(0));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.IDSF = PreHMDYTree->mu_SF_ID_HighPt->at(MuonIndex.at(0));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.LooseIDSF = PreHMDYTree->mu_SF_ID_HighPt->at(MuonIndex.at(0));

     if(isHMDYinclusiveWP){
       if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.IsoSF = PreHMDYTree->mu_SF_Iso_FCTightTrackOnly_FixedRad->at(MuonIndex.at(0));// For inclusive HMDY
     }
     else{
       if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.IsoSF = PreHMDYTree->mu_SF_Iso_TightTrackOnly_VarRad->at(MuonIndex.at(0));// For HMDY+b
     }

     SelectedEvent.Lepton1.TightWeight = SelectedEvent.Lepton1.TTVASF * SelectedEvent.Lepton1.IDSF * SelectedEvent.Lepton1.IsoSF;
     SelectedEvent.Lepton1.LooseWeight = SelectedEvent.Lepton1.TTVASF * SelectedEvent.Lepton1.LooseIDSF;

     SelectedEvent.Lepton1.looseID = PreHMDYTree->mu_isHighPt->at(MuonIndex.at(0));// to be consistent with electron
   }

   SelectedEvent.Lepton1.z0 = PreHMDYTree->mu_delta_z0_sintheta->at(MuonIndex.at(0));
   SelectedEvent.Lepton1.d0Sig = PreHMDYTree->mu_d0sig->at(MuonIndex.at(0));

   SelectedEvent.Lepton2.Flavor = 13;
   SelectedEvent.Lepton2.Charge = PreHMDYTree->mu_charge->at(MuonIndex.at(1));

   if(isHMDYinclusiveWP){
     if(isLooseTree) SelectedEvent.Lepton2.isTight = PreHMDYTree->mu_isTight->at(MuonIndex.at(1));// For inclusive HMDY
   }
   else{
     if(isLooseTree) SelectedEvent.Lepton2.isTight = PreHMDYTree->mu_isHighPt->at(MuonIndex.at(1)) * PreHMDYTree->mu_isolation_TightTrackOnly_VarRad->at(MuonIndex.at(1));// For HMDY+b
   }

   if(isLooseTree){
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.TTVASF = PreHMDYTree->mu_SF_TTVA->at(MuonIndex.at(1));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.IDSF = PreHMDYTree->mu_SF_ID_HighPt->at(MuonIndex.at(1));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.LooseIDSF = PreHMDYTree->mu_SF_ID_HighPt->at(MuonIndex.at(1));

     if(isHMDYinclusiveWP){
       if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.IsoSF = PreHMDYTree->mu_SF_Iso_FCTightTrackOnly_FixedRad->at(MuonIndex.at(1));// For inclusive HMDY
     }
     else{
       if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.IsoSF = PreHMDYTree->mu_SF_Iso_TightTrackOnly_VarRad->at(MuonIndex.at(1));// For HMDY+b
     }

     SelectedEvent.Lepton2.TightWeight = SelectedEvent.Lepton2.TTVASF * SelectedEvent.Lepton2.IDSF * SelectedEvent.Lepton2.IsoSF;
     SelectedEvent.Lepton2.LooseWeight = SelectedEvent.Lepton2.TTVASF * SelectedEvent.Lepton2.LooseIDSF;

     SelectedEvent.Lepton2.looseID = PreHMDYTree->mu_isHighPt->at(MuonIndex.at(1));// to be consistent with electron
   }

   SelectedEvent.Lepton2.z0 = PreHMDYTree->mu_delta_z0_sintheta->at(MuonIndex.at(1));
   SelectedEvent.Lepton2.d0Sig = PreHMDYTree->mu_d0sig->at(MuonIndex.at(1));

   SelectedEvent.eeChannel = false;
   SelectedEvent.mumuChannel = true;
   SelectedEvent.emuChannel = false;

   if(doElFakeBkg || doElMuFakeBkg) return false;
 }
 else if(nElectron == 1 && nMuon == 1 && PreHMDYTree->emu){
   SelectedEvent.Lepton1.P4.SetPtEtaPhiE(PreHMDYTree->el_pt->at(ElectronIndex.at(0)) / 1000.0, PreHMDYTree->el_eta->at(ElectronIndex.at(0)), PreHMDYTree->el_phi->at(ElectronIndex.at(0)), PreHMDYTree->el_e->at(ElectronIndex.at(0)) / 1000.0);
   SelectedEvent.Lepton2.P4.SetPtEtaPhiE(PreHMDYTree->mu_pt->at(MuonIndex.at(0)) / 1000.0, PreHMDYTree->mu_eta->at(MuonIndex.at(0)), PreHMDYTree->mu_phi->at(MuonIndex.at(0)), PreHMDYTree->mu_e->at(MuonIndex.at(0)) / 1000.0);

   SelectedEvent.Lepton1.Flavor = 11;
   SelectedEvent.Lepton1.Charge = PreHMDYTree->el_charge->at(ElectronIndex.at(0));
   if(isLooseTree) SelectedEvent.Lepton1.isTight = PreHMDYTree->el_isTight->at(ElectronIndex.at(0));
   if(isLooseTree) SelectedEvent.Lepton1.looseID = PreHMDYTree->el_isElLoose->at(ElectronIndex.at(0));

   if(isLooseTree){
     if(isFakeEffRun) SelectedEvent.Lepton1.RecoSF = PreHMDYTree->el_SF_Reco_Corr->at(ElectronIndex.at(0));
     if(isFakeEffRun) SelectedEvent.Lepton1.IDSF = PreHMDYTree->el_SF_ID_MediumLH->at(ElectronIndex.at(0));
     if(isFakeEffRun) SelectedEvent.Lepton1.LooseIDSF = PreHMDYTree->el_SF_ID_LooseAndBLayerLH->at(ElectronIndex.at(0));
     if(isFakeEffRun) SelectedEvent.Lepton1.IsoSF = PreHMDYTree->el_SF_Iso_FCTight->at(ElectronIndex.at(0));

     SelectedEvent.Lepton1.TightWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.IDSF * SelectedEvent.Lepton1.IsoSF;
     SelectedEvent.Lepton1.LooseWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.LooseIDSF;
   }

   SelectedEvent.Lepton1.z0 = PreHMDYTree->el_delta_z0_sintheta->at(ElectronIndex.at(0));
   SelectedEvent.Lepton1.d0Sig = PreHMDYTree->el_d0sig->at(ElectronIndex.at(0));
 
   SelectedEvent.Lepton2.Flavor = 13;
   SelectedEvent.Lepton2.Charge = PreHMDYTree->mu_charge->at(MuonIndex.at(0));
   if(isLooseTree) SelectedEvent.Lepton2.isTight = PreHMDYTree->mu_isTight->at(MuonIndex.at(0));
   if(isLooseTree) SelectedEvent.Lepton2.looseID = PreHMDYTree->mu_isHighPt->at(MuonIndex.at(0));// to be consistent with electron

   if(isLooseTree){
     if(isFakeEffRun) SelectedEvent.Lepton2.TTVASF = PreHMDYTree->mu_SF_TTVA->at(MuonIndex.at(0));
     if(isFakeEffRun) SelectedEvent.Lepton2.IDSF = PreHMDYTree->mu_SF_ID_HighPt->at(MuonIndex.at(0));
     if(isFakeEffRun) SelectedEvent.Lepton2.LooseIDSF = PreHMDYTree->mu_SF_ID_Loose->at(MuonIndex.at(0));
     if(isFakeEffRun) SelectedEvent.Lepton2.IsoSF = PreHMDYTree->mu_SF_Iso_FCTightTrackOnly_FixedRad->at(MuonIndex.at(0));

     SelectedEvent.Lepton2.TightWeight = SelectedEvent.Lepton2.TTVASF * SelectedEvent.Lepton2.IDSF * SelectedEvent.Lepton2.IsoSF;
     SelectedEvent.Lepton2.LooseWeight = SelectedEvent.Lepton2.TTVASF * SelectedEvent.Lepton2.LooseIDSF;
   }

   SelectedEvent.Lepton2.z0 = PreHMDYTree->mu_delta_z0_sintheta->at(MuonIndex.at(0));
   SelectedEvent.Lepton2.d0Sig = PreHMDYTree->mu_d0sig->at(MuonIndex.at(0));

   SelectedEvent.eeChannel = false;
   SelectedEvent.mumuChannel = false;
   SelectedEvent.emuChannel = true;

   if(doElFakeBkg || doMuFakeBkg) return false;
 }
 else if(nElectron == 2 && nMuon == 1 && PreHMDYTree->eeSelection_withmuon){
   SelectedEvent.Lepton1.P4.SetPtEtaPhiE(PreHMDYTree->el_pt->at(ElectronIndex.at(0)) / 1000.0, PreHMDYTree->el_eta->at(ElectronIndex.at(0)), PreHMDYTree->el_phi->at(ElectronIndex.at(0)), PreHMDYTree->el_e->at(ElectronIndex.at(0)) / 1000.0);
   SelectedEvent.Lepton2.P4.SetPtEtaPhiE(PreHMDYTree->el_pt->at(ElectronIndex.at(1)) / 1000.0, PreHMDYTree->el_eta->at(ElectronIndex.at(1)), PreHMDYTree->el_phi->at(ElectronIndex.at(1)), PreHMDYTree->el_e->at(ElectronIndex.at(1)) / 1000.0);

   SelectedEvent.Lepton1.Flavor = 11;
   SelectedEvent.Lepton1.Charge = PreHMDYTree->el_charge->at(ElectronIndex.at(0));
   if(isLooseTree) SelectedEvent.Lepton1.isTight = PreHMDYTree->el_isTight->at(ElectronIndex.at(0));

   if(isLooseTree){
     if(isMuFakeEffRun) SelectedEvent.Lepton1.RecoSF = PreHMDYTree->el_SF_Reco_Corr->at(ElectronIndex.at(0));
     if(isMuFakeEffRun) SelectedEvent.Lepton1.IDSF = PreHMDYTree->el_SF_ID_MediumLH->at(ElectronIndex.at(0));
     if(isMuFakeEffRun) SelectedEvent.Lepton1.LooseIDSF = PreHMDYTree->el_SF_ID_LooseAndBLayerLH->at(ElectronIndex.at(0));
     if(isMuFakeEffRun) SelectedEvent.Lepton1.IsoSF = PreHMDYTree->el_SF_Iso_FCTight->at(ElectronIndex.at(0));

     SelectedEvent.Lepton1.TightWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.IDSF * SelectedEvent.Lepton1.IsoSF;
     SelectedEvent.Lepton1.LooseWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.LooseIDSF;

     SelectedEvent.Lepton1.mediumID = PreHMDYTree->el_isElMedium->at(ElectronIndex.at(0));
     SelectedEvent.Lepton1.looseID = PreHMDYTree->el_isElLoose->at(ElectronIndex.at(0));
   }

   SelectedEvent.Lepton1.z0 = PreHMDYTree->el_delta_z0_sintheta->at(ElectronIndex.at(0));
   SelectedEvent.Lepton1.d0Sig = PreHMDYTree->el_d0sig->at(ElectronIndex.at(0));

   SelectedEvent.Lepton2.Flavor = 11;
   SelectedEvent.Lepton2.Charge = PreHMDYTree->el_charge->at(ElectronIndex.at(1));
   if(isLooseTree) SelectedEvent.Lepton2.isTight = PreHMDYTree->el_isTight->at(ElectronIndex.at(1));

   if(isLooseTree){
     if(isMuFakeEffRun) SelectedEvent.Lepton2.RecoSF = PreHMDYTree->el_SF_Reco_Corr->at(ElectronIndex.at(1));
     if(isMuFakeEffRun) SelectedEvent.Lepton2.IDSF = PreHMDYTree->el_SF_ID_MediumLH->at(ElectronIndex.at(1));
     if(isMuFakeEffRun) SelectedEvent.Lepton2.LooseIDSF = PreHMDYTree->el_SF_ID_LooseAndBLayerLH->at(ElectronIndex.at(1));
     if(isMuFakeEffRun) SelectedEvent.Lepton2.IsoSF = PreHMDYTree->el_SF_Iso_FCTight->at(ElectronIndex.at(1));

     SelectedEvent.Lepton2.TightWeight = SelectedEvent.Lepton2.RecoSF * SelectedEvent.Lepton2.IDSF * SelectedEvent.Lepton2.IsoSF;
     SelectedEvent.Lepton2.LooseWeight = SelectedEvent.Lepton2.RecoSF * SelectedEvent.Lepton2.LooseIDSF;

     SelectedEvent.Lepton2.mediumID = PreHMDYTree->el_isElMedium->at(ElectronIndex.at(1));
     SelectedEvent.Lepton2.looseID = PreHMDYTree->el_isElLoose->at(ElectronIndex.at(1));
   }

   SelectedEvent.Lepton2.z0 = PreHMDYTree->el_delta_z0_sintheta->at(ElectronIndex.at(1));
   SelectedEvent.Lepton2.d0Sig = PreHMDYTree->el_d0sig->at(ElectronIndex.at(1));

   SelectedEvent.Lepton3.P4.SetPtEtaPhiE(PreHMDYTree->mu_pt->at(MuonIndex.at(0)) / 1000.0, PreHMDYTree->mu_eta->at(MuonIndex.at(0)), PreHMDYTree->mu_phi->at(MuonIndex.at(0)), PreHMDYTree->mu_e->at(MuonIndex.at(0)) / 1000.0);
   SelectedEvent.Lepton3.Flavor = 13;
   SelectedEvent.Lepton3.Charge = PreHMDYTree->mu_charge->at(MuonIndex.at(0));

   if(isHMDYinclusiveWP){
     if(isLooseTree) SelectedEvent.Lepton3.isTight = PreHMDYTree->mu_isTight->at(MuonIndex.at(0));// For inclusive HMDY
   }
   else{
     if(isLooseTree) SelectedEvent.Lepton3.isTight = PreHMDYTree->mu_isHighPt->at(MuonIndex.at(0)) * PreHMDYTree->mu_isolation_TightTrackOnly_VarRad->at(MuonIndex.at(0));// For HMDY+b
   }

   if(isLooseTree){
     if(isMuFakeEffRun) SelectedEvent.Lepton3.TTVASF = PreHMDYTree->mu_SF_TTVA->at(MuonIndex.at(0));
     if(isMuFakeEffRun) SelectedEvent.Lepton3.IDSF = PreHMDYTree->mu_SF_ID_HighPt->at(MuonIndex.at(0));
     if(isMuFakeEffRun) SelectedEvent.Lepton3.LooseIDSF = PreHMDYTree->mu_SF_ID_HighPt->at(MuonIndex.at(0));

     if(isHMDYinclusiveWP){
       if(isMuFakeEffRun) SelectedEvent.Lepton3.IsoSF = PreHMDYTree->mu_SF_Iso_FCTightTrackOnly_FixedRad->at(MuonIndex.at(0));// For inclusive HMDY
     }
     else{
       if(isMuFakeEffRun) SelectedEvent.Lepton3.IsoSF = PreHMDYTree->mu_SF_Iso_TightTrackOnly_VarRad->at(MuonIndex.at(0));// For HMDY+b
     }

     SelectedEvent.Lepton3.TightWeight = SelectedEvent.Lepton3.TTVASF * SelectedEvent.Lepton3.IDSF * SelectedEvent.Lepton3.IsoSF;
     SelectedEvent.Lepton3.LooseWeight = SelectedEvent.Lepton3.TTVASF * SelectedEvent.Lepton3.LooseIDSF;

     SelectedEvent.Lepton3.looseID = PreHMDYTree->mu_isHighPt->at(MuonIndex.at(0));// to be consistent with electron
   }

   SelectedEvent.Lepton3.z0 = PreHMDYTree->mu_delta_z0_sintheta->at(MuonIndex.at(0));
   SelectedEvent.Lepton3.d0Sig = PreHMDYTree->mu_d0sig->at(MuonIndex.at(0));

   SelectedEvent.eeChannel = false;
   SelectedEvent.mumuChannel = false;
   SelectedEvent.emuChannel = false;
   SelectedEvent.eeChannel_withmuon = true;

   if(!isUnfoldRun){
     if(SelectedEvent.Lepton1.Charge * SelectedEvent.Lepton2.Charge > 0) return false;
   }
 }
 else{
   if(!isUnfoldRun) return false;
 }

 if((isNormalRun || isElRealEffRun || isMuRealEffRun) && !isUnfoldRun){
   if(SelectedEvent.Lepton1.Charge * SelectedEvent.Lepton2.Charge > 0) return false;
 }

 if(SelectedEvent.Lepton1.P4.Pt() < SelectedEvent.Lepton2.P4.Pt()){
   HMDYLepton Lepton_tmp = SelectedEvent.Lepton1;
   SelectedEvent.Lepton1 = SelectedEvent.Lepton2;
   SelectedEvent.Lepton2 = Lepton_tmp;
 }

 if(SelectedEvent.eeChannel){
// if(nElectron == 2 && nMuon == 0){
   if(SelectedEvent.Lepton1.isTight && SelectedEvent.Lepton2.isTight && SelectedEvent.Lepton1.looseID && SelectedEvent.Lepton2.looseID) SelectedEvent.pass_ee_TT = true;
   if(!SelectedEvent.Lepton1.isTight && SelectedEvent.Lepton2.isTight && SelectedEvent.Lepton1.looseID && SelectedEvent.Lepton2.looseID) SelectedEvent.pass_ee_LT = true;
   if(SelectedEvent.Lepton1.isTight && !SelectedEvent.Lepton2.isTight && SelectedEvent.Lepton1.looseID && SelectedEvent.Lepton2.looseID) SelectedEvent.pass_ee_TL = true;
   if(!SelectedEvent.Lepton1.isTight && !SelectedEvent.Lepton2.isTight && SelectedEvent.Lepton1.looseID && SelectedEvent.Lepton2.looseID) SelectedEvent.pass_ee_LL = true;
 }

 if(SelectedEvent.mumuChannel){
   if(SelectedEvent.Lepton1.isTight && SelectedEvent.Lepton2.isTight && SelectedEvent.Lepton1.looseID && SelectedEvent.Lepton2.looseID) SelectedEvent.pass_mm_TT = true;
   if(!SelectedEvent.Lepton1.isTight && SelectedEvent.Lepton2.isTight && SelectedEvent.Lepton1.looseID && SelectedEvent.Lepton2.looseID) SelectedEvent.pass_mm_LT = true;
   if(SelectedEvent.Lepton1.isTight && !SelectedEvent.Lepton2.isTight && SelectedEvent.Lepton1.looseID && SelectedEvent.Lepton2.looseID) SelectedEvent.pass_mm_TL = true;
   if(!SelectedEvent.Lepton1.isTight && !SelectedEvent.Lepton2.isTight && SelectedEvent.Lepton1.looseID && SelectedEvent.Lepton2.looseID) SelectedEvent.pass_mm_LL = true;
 }

 if(SelectedEvent.emuChannel){
   if(SelectedEvent.Lepton1.isTight && SelectedEvent.Lepton2.isTight && SelectedEvent.Lepton1.looseID && SelectedEvent.Lepton2.looseID) SelectedEvent.pass_em_TT = true;
   if(!SelectedEvent.Lepton1.isTight && SelectedEvent.Lepton2.isTight && SelectedEvent.Lepton1.looseID && SelectedEvent.Lepton2.looseID) SelectedEvent.pass_em_LT = true;
   if(SelectedEvent.Lepton1.isTight && !SelectedEvent.Lepton2.isTight && SelectedEvent.Lepton1.looseID && SelectedEvent.Lepton2.looseID) SelectedEvent.pass_em_TL = true;
   if(!SelectedEvent.Lepton1.isTight && !SelectedEvent.Lepton2.isTight && SelectedEvent.Lepton1.looseID && SelectedEvent.Lepton2.looseID) SelectedEvent.pass_em_LL = true;
 }

 // add eeSelection/mumuSelection/emu cut only for nominal Tree,
 // we don't add those cuts for nominal_Loose tree since we need to include on peak event for real/fake efficiency
 /*if(!isLooseTree){
   if(SelectedEvent.eeChannel && PreHMDYTree->eeSelection){
     SelectedEvent.pass_ee_TT = true;
     SelectedEvent.pass_ee_TL = false;
     SelectedEvent.pass_ee_LT = false;
     SelectedEvent.pass_ee_LL = false;
   }
   else if(SelectedEvent.mumuChannel && PreHMDYTree->mumuSelection){
     SelectedEvent.pass_mm_TT = true;
     SelectedEvent.pass_mm_TL = false;
     SelectedEvent.pass_mm_LT = false;
     SelectedEvent.pass_mm_LL = false;
   }
   else if(SelectedEvent.emuChannel && PreHMDYTree->emu){
     SelectedEvent.pass_ee_TT = false;
     SelectedEvent.pass_ee_TL = false;
     SelectedEvent.pass_ee_LT = false;
     SelectedEvent.pass_ee_LL = false;
     SelectedEvent.pass_mm_TT = false;
     SelectedEvent.pass_mm_TL = false;
     SelectedEvent.pass_mm_LT = false;
     SelectedEvent.pass_mm_LL = false;
   }
   else{
     return false;
   }
 }*/

 TLorentzVector Lepton, Antilepton;
 if(SelectedEvent.Lepton1.Charge == -1){
   Lepton = SelectedEvent.Lepton1.P4;
   Antilepton = SelectedEvent.Lepton2.P4;
 }
 if(SelectedEvent.Lepton2.Charge == -1){
   Lepton = SelectedEvent.Lepton2.P4;
   Antilepton = SelectedEvent.Lepton1.P4;
 }

 TLorentzVector Propagator = SelectedEvent.Lepton1.P4 + SelectedEvent.Lepton2.P4;

 // Truth
 double LeptonMass = 0.0;
 int mcChannelNumber = PreHMDYTree->mcChannelNumber;
 if(mcChannelNumber == 361106.0 || (mcChannelNumber >= 301000.0 && mcChannelNumber <= 301018.0) || (mcChannelNumber >= 364834.0 && mcChannelNumber <= 364840.0)){
   LeptonMass = 0.511 * 0.001;
 }
 if(mcChannelNumber == 361107.0 || (mcChannelNumber >= 301020.0 && mcChannelNumber <= 301038.0) || (mcChannelNumber >= 364841.0 && mcChannelNumber <= 364847.0)){
   LeptonMass = 0.105;
 }

 TLorentzVector TruthLepton_Born, TruthAntilepton_Born;
 if(!isData){
   TruthLepton_Born.SetPtEtaPhiM(PreHMDYTree->Lepton_Pt_born, PreHMDYTree->Lepton_Eta_born, PreHMDYTree->Lepton_Phi_born, LeptonMass);
   TruthAntilepton_Born.SetPtEtaPhiM(PreHMDYTree->AntiLepton_Pt_born, PreHMDYTree->AntiLepton_Eta_born, PreHMDYTree->AntiLepton_Phi_born, LeptonMass);
 }
 TLorentzVector TruthPropagator_Born = TruthLepton_Born + TruthAntilepton_Born;

 TLorentzVector TruthLepton_Bare, TruthAntilepton_Bare;
 if(!isData){
   TruthLepton_Bare.SetPtEtaPhiM(PreHMDYTree->Lepton_Pt_bare, PreHMDYTree->Lepton_Eta_bare, PreHMDYTree->Lepton_Phi_bare, LeptonMass);
   TruthAntilepton_Bare.SetPtEtaPhiM(PreHMDYTree->AntiLepton_Pt_bare, PreHMDYTree->AntiLepton_Eta_bare, PreHMDYTree->AntiLepton_Phi_bare, LeptonMass);
 }

// if(mcChannelNumber == 361106.0 || (mcChannelNumber >= 301000.0 && mcChannelNumber <= 301018.0) || (mcChannelNumber >= 364834.0 && mcChannelNumber <= 364840.0)
// || mcChannelNumber == 361107.0 || (mcChannelNumber >= 301020.0 && mcChannelNumber <= 301038.0) || (mcChannelNumber >= 364841.0 && mcChannelNumber <= 364847.0)){
   if(SelectedEvent.eeChannel || SelectedEvent.mumuChannel || SelectedEvent.SingleElectron){
     if(SelectedEvent.Lepton1.Charge == -1){
       SelectedEvent.Lepton1_DeltaR = SelectedEvent.Lepton1.P4.DeltaR(TruthLepton_Bare);
       SelectedEvent.Lepton2_DeltaR = SelectedEvent.Lepton2.P4.DeltaR(TruthAntilepton_Bare);

       if(SelectedEvent.Lepton1.P4.DeltaR(TruthLepton_Bare) < 0.2) SelectedEvent.Lepton1.isTruthMatch = 1;
       else SelectedEvent.Lepton1.isTruthMatch = 0;
  
       if(SelectedEvent.Lepton2.P4.DeltaR(TruthAntilepton_Bare) < 0.2) SelectedEvent.Lepton2.isTruthMatch = 1;
       else SelectedEvent.Lepton2.isTruthMatch = 0;
  
     }
     else if(SelectedEvent.Lepton1.Charge == 1){
       SelectedEvent.Lepton1_DeltaR = SelectedEvent.Lepton1.P4.DeltaR(TruthAntilepton_Bare);
       SelectedEvent.Lepton2_DeltaR = SelectedEvent.Lepton2.P4.DeltaR(TruthLepton_Bare);

       if(SelectedEvent.Lepton1.P4.DeltaR(TruthAntilepton_Bare) < 0.2) SelectedEvent.Lepton1.isTruthMatch = 1;
       else SelectedEvent.Lepton1.isTruthMatch = 0;
  
       if(SelectedEvent.Lepton2.P4.DeltaR(TruthLepton_Bare) < 0.2) SelectedEvent.Lepton2.isTruthMatch = 1;
       else SelectedEvent.Lepton2.isTruthMatch = 0;
     }
   }
// }
// else{
//   SelectedEvent.Lepton1.isTruthMatch = 1;
//   SelectedEvent.Lepton2.isTruthMatch = 1;
// }

 SelectedEvent.Lepton_Pt_born             = PreHMDYTree->Lepton_Pt_born;
 SelectedEvent.AntiLepton_Pt_born         = PreHMDYTree->AntiLepton_Pt_born;
 SelectedEvent.Lepton_Eta_born            = PreHMDYTree->Lepton_Eta_born;
 SelectedEvent.AntiLepton_Eta_born        = PreHMDYTree->AntiLepton_Eta_born;
 SelectedEvent.Lepton_Phi_born            = PreHMDYTree->Lepton_Phi_born;
 SelectedEvent.AntiLepton_Phi_born        = PreHMDYTree->AntiLepton_Phi_born;
 SelectedEvent.Lepton_m_born              = PreHMDYTree->Lepton_m_born;
 SelectedEvent.AntiLepton_m_born          = PreHMDYTree->AntiLepton_m_born;
 SelectedEvent.Lepton_Pt_bare             = PreHMDYTree->Lepton_Pt_bare;
 SelectedEvent.AntiLepton_Pt_bare         = PreHMDYTree->AntiLepton_Pt_bare;
 SelectedEvent.Lepton_Eta_bare            = PreHMDYTree->Lepton_Eta_bare;
 SelectedEvent.AntiLepton_Eta_bare        = PreHMDYTree->AntiLepton_Eta_bare;
 SelectedEvent.Lepton_Phi_bare            = PreHMDYTree->Lepton_Phi_bare;
 SelectedEvent.AntiLepton_Phi_bare        = PreHMDYTree->AntiLepton_Phi_bare;
 SelectedEvent.Lepton_Pt_dressed          = PreHMDYTree->Lepton_Pt_dressed;
 SelectedEvent.Lepton_Eta_dressed         = PreHMDYTree->Lepton_Eta_dressed;
 SelectedEvent.Lepton_Phi_dressed         = PreHMDYTree->Lepton_Phi_dressed;
 SelectedEvent.Lepton_Charge_dressed      = PreHMDYTree->Lepton_Charge_dressed;
 SelectedEvent.AntiLepton_Pt_dressed      = PreHMDYTree->AntiLepton_Pt_dressed;
 SelectedEvent.AntiLepton_Eta_dressed     = PreHMDYTree->AntiLepton_Eta_dressed;
 SelectedEvent.AntiLepton_Phi_dressed     = PreHMDYTree->AntiLepton_Phi_dressed;
 SelectedEvent.AntiLepton_Charge_dressed  = PreHMDYTree->AntiLepton_Charge_dressed;


 ///////////////////////////////////////////////////////////////////////

 SelectedEvent.Weight_Lepton1_SF = 1.0;
 SelectedEvent.Weight_Lepton2_SF = 1.0;
 SelectedEvent.RunNumber = PreHMDYTree->runNumber;
 SelectedEvent.EventNumber = PreHMDYTree->eventNumber;
 SelectedEvent.mcChannelNumber = PreHMDYTree->mcChannelNumber;
 SelectedEvent.RecoDilRapidity = Propagator.Rapidity();
 SelectedEvent.RecoDilPhi = Propagator.Phi();
 SelectedEvent.RecoDilMass = Propagator.M();
 SelectedEvent.RecoPseudoDilMass = -999.0;
 SelectedEvent.RecoDilPt = Propagator.Pt();
 SelectedEvent.RecoPhiStar = calculate_phi_eta(Lepton, Antilepton);
 SelectedEvent.RecoCosThetaStar = calculate_theta(Propagator, Lepton, Antilepton) * Propagator.Rapidity() / fabs(Propagator.Rapidity());

 SelectedEvent.RecoWeight = Lumi * CrossSection / SumOfWeight * PreHMDYTree->weight_mc;

 SelectedEvent.Lepton1_Pt = SelectedEvent.Lepton1.P4.Pt();
 SelectedEvent.Lepton2_Pt = SelectedEvent.Lepton2.P4.Pt();
 SelectedEvent.Lepton3_Pt = SelectedEvent.Lepton3.P4.Pt();
 SelectedEvent.Lepton1_Phi = SelectedEvent.Lepton1.P4.Phi();
 SelectedEvent.Lepton2_Phi = SelectedEvent.Lepton2.P4.Phi();
 SelectedEvent.Lepton3_Phi = SelectedEvent.Lepton3.P4.Phi();
 SelectedEvent.Lepton1_Eta = SelectedEvent.Lepton1.P4.Eta();
 SelectedEvent.Lepton2_Eta = SelectedEvent.Lepton2.P4.Eta();
 SelectedEvent.Lepton3_Eta = SelectedEvent.Lepton3.P4.Eta();
 SelectedEvent.pTllReweight = 1.0;
 SelectedEvent.ChargeMisIDSFWeight = PreHMDYTree->weight_indiv_SF_EL_ChargeMisID;
 SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_STAT_UP   = PreHMDYTree->weight_indiv_SF_EL_ChargeMisID_STAT_UP / PreHMDYTree->weight_indiv_SF_EL_ChargeMisID;
 SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN = PreHMDYTree->weight_indiv_SF_EL_ChargeMisID_STAT_DOWN / PreHMDYTree->weight_indiv_SF_EL_ChargeMisID;
 SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_SYST_UP   = PreHMDYTree->weight_indiv_SF_EL_ChargeMisID_SYST_UP / PreHMDYTree->weight_indiv_SF_EL_ChargeMisID;
 SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN = PreHMDYTree->weight_indiv_SF_EL_ChargeMisID_SYST_DOWN / PreHMDYTree->weight_indiv_SF_EL_ChargeMisID;
 SelectedEvent.ChargeIDSFWeight = 1.0;
 SelectedEvent.LeptonSFWeight = PreHMDYTree->weight_leptonSF;
 SelectedEvent.PileupWeight = PreHMDYTree->weight_pileup;

 SelectedEvent.TriggerSF = PreHMDYTree->weight_globalLeptonTriggerSF;
 if(SelectedEvent.eeChannel && !isData) SelectedEvent.TriggerSF = GetGlobalTriggerSF(PreHMDYTree->randomRunNumber, SelectedEvent.Lepton1_Pt, SelectedEvent.Lepton1_Eta, SelectedEvent.Lepton2_Pt, SelectedEvent.Lepton2_Eta);
 if(SelectedEvent.SingleElectron) SelectedEvent.TriggerSF = 1.0;

 SelectedEvent.n_Bjets = -999;
 SelectedEvent.MET_Et = PreHMDYTree->met_met;
 SelectedEvent.Lepton1_z0 = SelectedEvent.Lepton1.z0;
 SelectedEvent.Lepton2_z0 = SelectedEvent.Lepton2.z0;
 SelectedEvent.Lepton3_z0 = SelectedEvent.Lepton3.z0;
 SelectedEvent.Lepton1_d0sig = SelectedEvent.Lepton1.d0Sig;
 SelectedEvent.Lepton2_d0sig = SelectedEvent.Lepton2.d0Sig;
 SelectedEvent.Lepton3_d0sig = SelectedEvent.Lepton3.d0Sig;
 SelectedEvent.Mu = PreHMDYTree->mu;
 SelectedEvent.MuActual = PreHMDYTree->mu_actual;
 SelectedEvent.PhiRF = calculate_phi(Lepton, Antilepton, 13000.0);

 SelectedEvent.Lepton1_TightWeight = SelectedEvent.Lepton1.TightWeight;
 SelectedEvent.Lepton2_TightWeight = SelectedEvent.Lepton2.TightWeight;
 SelectedEvent.Lepton3_TightWeight = SelectedEvent.Lepton3.TightWeight;
 SelectedEvent.Lepton1_LooseWeight = SelectedEvent.Lepton1.LooseWeight;
 SelectedEvent.Lepton2_LooseWeight = SelectedEvent.Lepton2.LooseWeight;
 SelectedEvent.Lepton3_LooseWeight = SelectedEvent.Lepton3.LooseWeight;
 SelectedEvent.Lepton1_MediumIDWeight = SelectedEvent.Lepton1.IDSF;
 SelectedEvent.Lepton2_MediumIDWeight = SelectedEvent.Lepton2.IDSF;
 SelectedEvent.Lepton1_passMediumID = SelectedEvent.Lepton1.mediumID;
 SelectedEvent.Lepton2_passMediumID = SelectedEvent.Lepton2.mediumID;
 SelectedEvent.Lepton3_passMediumID = SelectedEvent.Lepton3.mediumID;
 SelectedEvent.Lepton1_passLooseID = SelectedEvent.Lepton1.looseID;
 SelectedEvent.Lepton2_passLooseID = SelectedEvent.Lepton2.looseID;
 SelectedEvent.Lepton3_passLooseID = SelectedEvent.Lepton3.looseID;
 SelectedEvent.Lepton1_passIso = SelectedEvent.Lepton1.FCTightIso;
 SelectedEvent.Lepton2_passIso = SelectedEvent.Lepton2.FCTightIso;
 SelectedEvent.Lepton1_IsoWeight = SelectedEvent.Lepton1.IsoSF;
 SelectedEvent.Lepton2_IsoWeight = SelectedEvent.Lepton2.IsoSF;
 SelectedEvent.Lepton1_PrescaleFactor = SelectedEvent.Lepton1.PrescaleFactor;
 SelectedEvent.Lepton2_PrescaleFactor = SelectedEvent.Lepton2.PrescaleFactor;

 if(mcChannelNumber == 361106.0 || (mcChannelNumber >= 301000.0 && mcChannelNumber <= 301018.0)
 || mcChannelNumber == 361107.0 || (mcChannelNumber >= 301020.0 && mcChannelNumber <= 301038.0)
 || (mcChannelNumber >= 700000.0 && mcChannelNumber <= 700130.0)
 || (mcChannelNumber >= 364116.0 && mcChannelNumber <= 364127.0)){
   SelectedEvent.Weight_kFactor_Old = 1.0;
   SelectedEvent.Weight_kFactor_QCDEW = 1.0;
   SelectedEvent.Weight_kFactor_New_CT18NNLO = Zgamma_CT14nnlo_CT10_New(SelectedEvent.TruthDilMass_Born)
                                             * Zgamma_CT18NNLO_CT14nnlo_Central_spline(SelectedEvent.TruthDilMass_Born)
                                             * (1.0 + ((ew_z_spline(SelectedEvent.TruthDilMass_Born) - 1.0) / Zgamma_CT10nnlo_CT10nnlo(SelectedEvent.TruthDilMass_Born)));
   SelectedEvent.Weight_kFactor_New_CT18ANNLO = Zgamma_CT14nnlo_CT10_New(SelectedEvent.TruthDilMass_Born)
                                              * Zgamma_CT18ANNLO_CT14nnlo_Central_spline(SelectedEvent.TruthDilMass_Born)
                                              * (1.0 + ((ew_z_spline(SelectedEvent.TruthDilMass_Born) - 1.0) / Zgamma_CT10nnlo_CT10nnlo(SelectedEvent.TruthDilMass_Born)));
   SelectedEvent.Weight_kFactor_PowhegtoSherpa = 1.0;
 }
 else{
   SelectedEvent.Weight_kFactor_Old = 1.0;
   SelectedEvent.Weight_kFactor_QCDEW = 1.0;
   SelectedEvent.Weight_kFactor_New_CT18NNLO = 1.0;
   SelectedEvent.Weight_kFactor_New_CT18ANNLO = 1.0;
   SelectedEvent.Weight_kFactor_PowhegtoSherpa = 1.0;
 }

 if(isData){
   SelectedEvent.RecoWeight = 1.0;
   SelectedEvent.ChargeMisIDSFWeight = 1.0;
   SelectedEvent.LeptonSFWeight = 1.0;
   SelectedEvent.PileupWeight = 1.0;
   SelectedEvent.TriggerSF = 1.0;
   SelectedEvent.Weight_kFactor_Old = 1.0;
   SelectedEvent.Weight_kFactor_QCDEW = 1.0;
   SelectedEvent.Weight_kFactor_New_CT18NNLO = 1.0;
   SelectedEvent.Weight_kFactor_New_CT18ANNLO = 1.0;
   SelectedEvent.Weight_kFactor_PowhegtoSherpa = 1.0;
   SelectedEvent.Lepton1_TightWeight = 1.0;
   SelectedEvent.Lepton2_TightWeight = 1.0;
   SelectedEvent.Lepton3_TightWeight = 1.0;
   SelectedEvent.Lepton1_LooseWeight = 1.0;
   SelectedEvent.Lepton2_LooseWeight = 1.0;
   SelectedEvent.Lepton3_LooseWeight = 1.0;
   SelectedEvent.Lepton1_MediumIDWeight = 1.0;
   SelectedEvent.Lepton2_MediumIDWeight = 1.0;
   SelectedEvent.Lepton1_IsoWeight = 1.0;
   SelectedEvent.Lepton2_IsoWeight = 1.0;

   SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_STAT_UP = 1.0;
   SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN = 1.0;
   SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_SYST_UP = 1.0;
   SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN = 1.0;
 }

 if((isNormalRun || isElRealEffRun || isMuRealEffRun) && !isUnfoldRun){
   if(SelectedEvent.RecoDilMass <= 66.0) return false;
 }

 if(doFakeBkg){
   if(doElFakeBkg){
     int passTT = 0, passTL = 0, passLT = 0, passLL = 0;
     if(SelectedEvent.pass_ee_TT) passTT = 1;
     if(SelectedEvent.pass_ee_TL) passTL = 1;
     if(SelectedEvent.pass_ee_LT) passLT = 1;
     if(SelectedEvent.pass_ee_LL) passLL = 1;

     double SavedRecoWeight = SelectedEvent.RecoWeight;

     WeightRun->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight = SelectedEvent.RecoWeight * WeightRun->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));
     SelectedEvent.RecoWeight_FourTerm_TT = SavedRecoWeight * WeightRun->FourTermTT;
     SelectedEvent.RecoWeight_FourTerm_TL = SavedRecoWeight * WeightRun->FourTermTL;
     SelectedEvent.RecoWeight_FourTerm_LT = SavedRecoWeight * WeightRun->FourTermLT;
     SelectedEvent.RecoWeight_FourTerm_LL = SavedRecoWeight * WeightRun->FourTermLL;

     WeightRun_Stat_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_Stat_up = SavedRecoWeight * WeightRun_Stat_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));
     WeightRun_Stat_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_Stat_down = SavedRecoWeight * WeightRun_Stat_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));

     WeightRun_PromptSubtr_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_PromptSubtr_up = SavedRecoWeight * WeightRun_PromptSubtr_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));
     WeightRun_PromptSubtr_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_PromptSubtr_down = SavedRecoWeight * WeightRun_PromptSubtr_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));

     WeightRun_MET_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_MET_up = SavedRecoWeight * WeightRun_MET_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));
     WeightRun_MET_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_MET_down = SavedRecoWeight * WeightRun_MET_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));

     WeightRun_RealStat_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_RealStat_up = SavedRecoWeight * WeightRun_RealStat_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));
     WeightRun_RealStat_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_RealStat_down = SavedRecoWeight * WeightRun_RealStat_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));
   }

   if(doMuFakeBkg){
     int passTT = 0, passTL = 0, passLT = 0, passLL = 0;
     if(SelectedEvent.pass_mm_TT) passTT = 1;
     if(SelectedEvent.pass_mm_TL) passTL = 1;
     if(SelectedEvent.pass_mm_LT) passLT = 1;
     if(SelectedEvent.pass_mm_LL) passLL = 1;

     WeightRun->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight = WeightRun->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));

     WeightRun_Stat_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_Stat_up = WeightRun_Stat_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));
     WeightRun_Stat_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_Stat_down = WeightRun_Stat_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));

     WeightRun_PromptSubtr_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_PromptSubtr_up = WeightRun_PromptSubtr_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));
     WeightRun_PromptSubtr_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_PromptSubtr_down = WeightRun_PromptSubtr_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));

     WeightRun_d0sig_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_d0sig_up = WeightRun_d0sig_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));
     WeightRun_d0sig_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_d0sig_down = WeightRun_d0sig_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));

     WeightRun_RealStat_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_RealStat_up = WeightRun_RealStat_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));
     WeightRun_RealStat_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_RealStat_down = WeightRun_RealStat_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta));
   }

   if(doElMuFakeBkg){
     int passTT = 0, passTL = 0, passLT = 0, passLL = 0;
     if(SelectedEvent.pass_em_TT) passTT = 1;
     if(SelectedEvent.pass_em_TL) passTL = 1;
     if(SelectedEvent.pass_em_LT) passLT = 1;
     if(SelectedEvent.pass_em_LL) passLL = 1;

     bool is_exchanged = false;
     if(SelectedEvent.Lepton1.Flavor == 13 && SelectedEvent.Lepton2.Flavor == 11) is_exchanged = true;

     WeightRun->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight = WeightRun->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);
     SelectedEvent.RecoWeight_FourTerm_TT = WeightRun->FourTermTT;
     SelectedEvent.RecoWeight_FourTerm_TL = WeightRun->FourTermTL;
     SelectedEvent.RecoWeight_FourTerm_LT = WeightRun->FourTermLT;
     SelectedEvent.RecoWeight_FourTerm_LL = WeightRun->FourTermLL;

     WeightRun_El_Stat_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_El_Stat_up = WeightRun_El_Stat_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);
     WeightRun_El_Stat_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_El_Stat_down = WeightRun_El_Stat_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);

     WeightRun_El_PromptSubtr_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_El_PromptSubtr_up = WeightRun_El_PromptSubtr_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);
     WeightRun_El_PromptSubtr_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_El_PromptSubtr_down = WeightRun_El_PromptSubtr_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);

     WeightRun_El_RealStat_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_El_RealStat_up = WeightRun_El_RealStat_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);
     WeightRun_El_RealStat_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_El_RealStat_down = WeightRun_El_RealStat_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);

     WeightRun_Mu_Stat_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_Mu_Stat_up = WeightRun_Mu_Stat_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);
     WeightRun_Mu_Stat_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_Mu_Stat_down = WeightRun_Mu_Stat_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);

     WeightRun_Mu_PromptSubtr_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_Mu_PromptSubtr_up = WeightRun_Mu_PromptSubtr_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);
     WeightRun_Mu_PromptSubtr_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_Mu_PromptSubtr_down = WeightRun_Mu_PromptSubtr_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);

     WeightRun_Mu_RealStat_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_Mu_RealStat_up = WeightRun_Mu_RealStat_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);
     WeightRun_Mu_RealStat_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_Mu_RealStat_down = WeightRun_Mu_RealStat_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);

     WeightRun_MET_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_MET_up = WeightRun_MET_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);
     WeightRun_MET_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_MET_down = WeightRun_MET_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);

     WeightRun_d0sig_up->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_d0sig_up = WeightRun_d0sig_up->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);
     WeightRun_d0sig_down->InputSelection(passTT, passTL, passLT, passLL);
     SelectedEvent.RecoWeight_d0sig_down = WeightRun_d0sig_down->GetFakeWeight(SelectedEvent.Lepton1_Pt, fabs(SelectedEvent.Lepton1_Eta), SelectedEvent.Lepton2_Pt, fabs(SelectedEvent.Lepton2_Eta), is_exchanged);

   }
 }

 HMDYTree->Weight_Lepton1_SF =               SelectedEvent.Weight_Lepton1_SF;
 HMDYTree->Weight_Lepton2_SF =               SelectedEvent.Weight_Lepton2_SF;
 HMDYTree->RunNumber =                       SelectedEvent.RunNumber;
 HMDYTree->EventNumber =                     SelectedEvent.EventNumber;
 HMDYTree->mcChannelNumber =                 SelectedEvent.mcChannelNumber;
 HMDYTree->RecoDilRapidity =                 SelectedEvent.RecoDilRapidity;
 HMDYTree->RecoDilPhi =                      SelectedEvent.RecoDilPhi;
 HMDYTree->RecoDilMass =                     SelectedEvent.RecoDilMass;
 HMDYTree->RecoPseudoDilMass =               SelectedEvent.RecoPseudoDilMass;
 HMDYTree->RecoDilPt =                       SelectedEvent.RecoDilPt;
 HMDYTree->RecoPhiStar =                     SelectedEvent.RecoPhiStar;
 HMDYTree->RecoCosThetaStar =                SelectedEvent.RecoCosThetaStar;
 HMDYTree->RecoWeight =                      SelectedEvent.RecoWeight;
 HMDYTree->RecoWeight_Stat_up =              SelectedEvent.RecoWeight_Stat_up;
 HMDYTree->RecoWeight_Stat_down =            SelectedEvent.RecoWeight_Stat_down;
 HMDYTree->RecoWeight_PromptSubtr_up =       SelectedEvent.RecoWeight_PromptSubtr_up;
 HMDYTree->RecoWeight_PromptSubtr_down =     SelectedEvent.RecoWeight_PromptSubtr_down;
 HMDYTree->RecoWeight_MET_up =               SelectedEvent.RecoWeight_MET_up;
 HMDYTree->RecoWeight_MET_down =             SelectedEvent.RecoWeight_MET_down;
 HMDYTree->RecoWeight_d0sig_up =             SelectedEvent.RecoWeight_d0sig_up;
 HMDYTree->RecoWeight_d0sig_down =           SelectedEvent.RecoWeight_d0sig_down;
 HMDYTree->RecoWeight_RealStat_up =          SelectedEvent.RecoWeight_RealStat_up;
 HMDYTree->RecoWeight_RealStat_down =        SelectedEvent.RecoWeight_RealStat_down;
 HMDYTree->RecoWeight_FourTerm_TT =          SelectedEvent.RecoWeight_FourTerm_TT;
 HMDYTree->RecoWeight_FourTerm_TL =          SelectedEvent.RecoWeight_FourTerm_TL;
 HMDYTree->RecoWeight_FourTerm_LT =          SelectedEvent.RecoWeight_FourTerm_LT;
 HMDYTree->RecoWeight_FourTerm_LL =          SelectedEvent.RecoWeight_FourTerm_LL;
 HMDYTree->RecoWeight_El_Stat_up =           SelectedEvent.RecoWeight_El_Stat_up;
 HMDYTree->RecoWeight_El_Stat_down =         SelectedEvent.RecoWeight_El_Stat_down;
 HMDYTree->RecoWeight_El_PromptSubtr_up =    SelectedEvent.RecoWeight_El_PromptSubtr_up;
 HMDYTree->RecoWeight_El_PromptSubtr_down =  SelectedEvent.RecoWeight_El_PromptSubtr_down;
 HMDYTree->RecoWeight_El_RealStat_up =       SelectedEvent.RecoWeight_El_RealStat_up;
 HMDYTree->RecoWeight_El_RealStat_down =     SelectedEvent.RecoWeight_El_RealStat_down;
 HMDYTree->RecoWeight_Mu_Stat_up =           SelectedEvent.RecoWeight_Mu_Stat_up;
 HMDYTree->RecoWeight_Mu_Stat_down =         SelectedEvent.RecoWeight_Mu_Stat_down;
 HMDYTree->RecoWeight_Mu_PromptSubtr_up =    SelectedEvent.RecoWeight_Mu_PromptSubtr_up;
 HMDYTree->RecoWeight_Mu_PromptSubtr_down =  SelectedEvent.RecoWeight_Mu_PromptSubtr_down;
 HMDYTree->RecoWeight_Mu_RealStat_up =       SelectedEvent.RecoWeight_Mu_RealStat_up;
 HMDYTree->RecoWeight_Mu_RealStat_down =     SelectedEvent.RecoWeight_Mu_RealStat_down;
 HMDYTree->eeChannel =                       SelectedEvent.eeChannel;
 HMDYTree->mumuChannel =                     SelectedEvent.mumuChannel;
 HMDYTree->emuChannel =                      SelectedEvent.emuChannel;
 HMDYTree->eeChannel_withmuon =              SelectedEvent.eeChannel_withmuon;
 HMDYTree->SingleElectron =                  SelectedEvent.SingleElectron;
 HMDYTree->TruthDilMass_Born =               SelectedEvent.TruthDilMass_Born;
 HMDYTree->TruthDilRapidity_Born =           SelectedEvent.TruthDilRapidity_Born;
 HMDYTree->Lepton1_Pt =                      SelectedEvent.Lepton1_Pt;
 HMDYTree->Lepton2_Pt =                      SelectedEvent.Lepton2_Pt;
 HMDYTree->Lepton3_Pt =                      SelectedEvent.Lepton3_Pt;
 HMDYTree->Lepton1_Phi =                     SelectedEvent.Lepton1_Phi;
 HMDYTree->Lepton2_Phi =                     SelectedEvent.Lepton2_Phi;
 HMDYTree->Lepton3_Phi =                     SelectedEvent.Lepton3_Phi;
 HMDYTree->Lepton1_Eta =                     SelectedEvent.Lepton1_Eta;
 HMDYTree->Lepton2_Eta =                     SelectedEvent.Lepton2_Eta;
 HMDYTree->Lepton3_Eta =                     SelectedEvent.Lepton3_Eta;
 HMDYTree->pTllReweight =                    SelectedEvent.pTllReweight;
 HMDYTree->ChargeMisIDSFWeight =             SelectedEvent.ChargeMisIDSFWeight;
 HMDYTree->ChargeIDSFWeight =                SelectedEvent.ChargeIDSFWeight;
 HMDYTree->LeptonSFWeight =                  SelectedEvent.LeptonSFWeight;
 HMDYTree->PileupWeight =                    SelectedEvent.PileupWeight;
 HMDYTree->TriggerSF =                       SelectedEvent.TriggerSF;
 HMDYTree->n_Bjets =                         SelectedEvent.n_Bjets;
 HMDYTree->MET_Et =                          SelectedEvent.MET_Et;
 HMDYTree->Lepton1_z0 =                      SelectedEvent.Lepton1_z0;
 HMDYTree->Lepton2_z0 =                      SelectedEvent.Lepton2_z0;
 HMDYTree->Lepton3_z0 =                      SelectedEvent.Lepton3_z0;
 HMDYTree->Lepton1_d0sig =                   SelectedEvent.Lepton1_d0sig;
 HMDYTree->Lepton2_d0sig =                   SelectedEvent.Lepton2_d0sig;
 HMDYTree->Lepton3_d0sig =                   SelectedEvent.Lepton3_d0sig;
 HMDYTree->Lepton1_DeltaR =                  SelectedEvent.Lepton1_DeltaR;
 HMDYTree->Lepton2_DeltaR =                  SelectedEvent.Lepton2_DeltaR;
 HMDYTree->Mu =                              SelectedEvent.Mu;
 HMDYTree->MuActual =                        SelectedEvent.MuActual;
 HMDYTree->PhiRF =                           SelectedEvent.PhiRF;
 HMDYTree->Weight_kFactor_Old =              SelectedEvent.Weight_kFactor_Old;
 HMDYTree->Weight_kFactor_QCDEW =            SelectedEvent.Weight_kFactor_QCDEW;
 HMDYTree->Weight_kFactor_New_CT18NNLO =     SelectedEvent.Weight_kFactor_New_CT18NNLO;
 HMDYTree->Weight_kFactor_New_CT18ANNLO =    SelectedEvent.Weight_kFactor_New_CT18ANNLO;
 HMDYTree->Weight_kFactor_PowhegtoSherpa =   SelectedEvent.Weight_kFactor_PowhegtoSherpa;

 HMDYTree->Weight_indiv_SF_EL_ChargeMisID_STAT_UP   = SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_STAT_UP;
 HMDYTree->Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN = SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN;
 HMDYTree->Weight_indiv_SF_EL_ChargeMisID_SYST_UP   = SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_SYST_UP;
 HMDYTree->Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN = SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN;

 HMDYTree->Lepton_Pt_born                = SelectedEvent.Lepton_Pt_born;
 HMDYTree->AntiLepton_Pt_born            = SelectedEvent.AntiLepton_Pt_born;
 HMDYTree->Lepton_Eta_born               = SelectedEvent.Lepton_Eta_born;
 HMDYTree->AntiLepton_Eta_born           = SelectedEvent.AntiLepton_Eta_born;
 HMDYTree->Lepton_Phi_born               = SelectedEvent.Lepton_Phi_born;
 HMDYTree->AntiLepton_Phi_born           = SelectedEvent.AntiLepton_Phi_born;
 HMDYTree->Lepton_m_born                 = SelectedEvent.Lepton_m_born;
 HMDYTree->AntiLepton_m_born             = SelectedEvent.AntiLepton_m_born;
 HMDYTree->Lepton_Pt_bare                = SelectedEvent.Lepton_Pt_bare;
 HMDYTree->AntiLepton_Pt_bare            = SelectedEvent.AntiLepton_Pt_bare;
 HMDYTree->Lepton_Eta_bare               = SelectedEvent.Lepton_Eta_bare;
 HMDYTree->AntiLepton_Eta_bare           = SelectedEvent.AntiLepton_Eta_bare;
 HMDYTree->Lepton_Phi_bare               = SelectedEvent.Lepton_Phi_bare;
 HMDYTree->AntiLepton_Phi_bare           = SelectedEvent.AntiLepton_Phi_bare;
 HMDYTree->Lepton_Pt_dressed             = SelectedEvent.Lepton_Pt_dressed;
 HMDYTree->Lepton_Eta_dressed            = SelectedEvent.Lepton_Eta_dressed;
 HMDYTree->Lepton_Phi_dressed            = SelectedEvent.Lepton_Phi_dressed;
 HMDYTree->Lepton_Charge_dressed         = SelectedEvent.Lepton_Charge_dressed;
 HMDYTree->AntiLepton_Pt_dressed         = SelectedEvent.AntiLepton_Pt_dressed;
 HMDYTree->AntiLepton_Eta_dressed        = SelectedEvent.AntiLepton_Eta_dressed;
 HMDYTree->AntiLepton_Phi_dressed        = SelectedEvent.AntiLepton_Phi_dressed;
 HMDYTree->AntiLepton_Charge_dressed     = SelectedEvent.AntiLepton_Charge_dressed;

 HMDYTree->pass_ee_TT =                    SelectedEvent.pass_ee_TT;
 HMDYTree->pass_ee_TL =                    SelectedEvent.pass_ee_TL;
 HMDYTree->pass_ee_LT =                    SelectedEvent.pass_ee_LT;
 HMDYTree->pass_ee_LL =                    SelectedEvent.pass_ee_LL;
 HMDYTree->pass_mm_TT =                    SelectedEvent.pass_mm_TT;
 HMDYTree->pass_mm_TL =                    SelectedEvent.pass_mm_TL;
 HMDYTree->pass_mm_LT =                    SelectedEvent.pass_mm_LT;
 HMDYTree->pass_mm_LL =                    SelectedEvent.pass_mm_LL;
 HMDYTree->pass_em_TT =                    SelectedEvent.pass_em_TT;
 HMDYTree->pass_em_TL =                    SelectedEvent.pass_em_TL;
 HMDYTree->pass_em_LT =                    SelectedEvent.pass_em_LT;
 HMDYTree->pass_em_LL =                    SelectedEvent.pass_em_LL;
 HMDYTree->Lepton1_isTight =               SelectedEvent.Lepton1.isTight;
 HMDYTree->Lepton2_isTight =               SelectedEvent.Lepton2.isTight;
 HMDYTree->Lepton3_isTight =               SelectedEvent.Lepton3.isTight;
 HMDYTree->Lepton1_passMediumID =          SelectedEvent.Lepton1_passMediumID;
 HMDYTree->Lepton2_passMediumID =          SelectedEvent.Lepton2_passMediumID;
 HMDYTree->Lepton3_passMediumID =          SelectedEvent.Lepton3_passMediumID;
 HMDYTree->Lepton1_passLooseID =           SelectedEvent.Lepton1_passLooseID;
 HMDYTree->Lepton2_passLooseID =           SelectedEvent.Lepton2_passLooseID;
 HMDYTree->Lepton3_passLooseID =           SelectedEvent.Lepton3_passLooseID;
 HMDYTree->Lepton1_passIso =               SelectedEvent.Lepton1_passIso;
 HMDYTree->Lepton2_passIso =               SelectedEvent.Lepton2_passIso;
 HMDYTree->Lepton1_IsoWeight =             SelectedEvent.Lepton1_IsoWeight;
 HMDYTree->Lepton2_IsoWeight =             SelectedEvent.Lepton2_IsoWeight;

 HMDYTree->Lepton1_Charge =                SelectedEvent.Lepton1.Charge;
 HMDYTree->Lepton2_Charge =                SelectedEvent.Lepton2.Charge;
 HMDYTree->Lepton1_isTruthMatch =          SelectedEvent.Lepton1.isTruthMatch;
 HMDYTree->Lepton2_isTruthMatch =          SelectedEvent.Lepton2.isTruthMatch;
 HMDYTree->Lepton1_TightWeight =           SelectedEvent.Lepton1_TightWeight;
 HMDYTree->Lepton2_TightWeight =           SelectedEvent.Lepton2_TightWeight;
 HMDYTree->Lepton3_TightWeight =           SelectedEvent.Lepton3_TightWeight;
 HMDYTree->Lepton1_LooseWeight =           SelectedEvent.Lepton1_LooseWeight;
 HMDYTree->Lepton2_LooseWeight =           SelectedEvent.Lepton2_LooseWeight;
 HMDYTree->Lepton3_LooseWeight =           SelectedEvent.Lepton3_LooseWeight;
 HMDYTree->Lepton1_MediumIDWeight =        SelectedEvent.Lepton1_MediumIDWeight;
 HMDYTree->Lepton2_MediumIDWeight =        SelectedEvent.Lepton2_MediumIDWeight;
 HMDYTree->PrescaleFactor =                SelectedEvent.PrescaleFactor;
 HMDYTree->Lepton1_PrescaleFactor =        SelectedEvent.Lepton1_PrescaleFactor;
 HMDYTree->Lepton2_PrescaleFactor =        SelectedEvent.Lepton2_PrescaleFactor;

 ElectronIndex.clear();
 MuonIndex.clear();

 return true;
}

double loopHMDY::GetGlobalTriggerSF(int randomRunNumber, double el1_pt, double el1_eta, double el2_pt, double el2_eta)
{
	// open TFile
        if(TriggerFile == 0){
          TriggerFile = new TFile("/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/trigger/efficiencySF.DI_E_2015_e12_lhloose_L1EM10VH_2016_e17_lhvloose_nod0_2017_2018_e24_lhvloose_nod0_L1EM20VH.MediumLLH_d0z0_v13_isolFCTight.root");
        }

	TH2D* sf_ee = nullptr;
	if (randomRunNumber >= 276073. && randomRunNumber <= 284484.)
		sf_ee = (TH2D *)TriggerFile->Get("266904_284484/FullSim_sf");	
	if (randomRunNumber >= 297730. && randomRunNumber <= 314199.)
		sf_ee = (TH2D *)TriggerFile->Get("296939_311481/FullSim_sf");
	if (randomRunNumber >= 325713. && randomRunNumber <= 340453.)
		sf_ee = (TH2D *)TriggerFile->Get("324320_340453/FullSim_sf");
	if (randomRunNumber >= 348885. && randomRunNumber <= 364292.)
		sf_ee = (TH2D *)TriggerFile->Get("342183_9999999/FullSim_sf");

	//std::cout << el1_pt << " " << el1_eta << " " << el2_pt << " " << el2_eta << std::endl;

	// check range of the histogram
	//std::cout << "sf_ee->GetXaxis()->GetXmin(): " << sf_ee->GetXaxis()->GetXmin() << std::endl;
	//std::cout << "sf_ee->GetXaxis()->GetXmax(): " << sf_ee->GetXaxis()->GetXmax() << std::endl;
	if(el1_pt > 999)
           el1_pt = 999;

        if(el2_pt > 999)
           el2_pt = 999;

        auto sf_el1 = sf_ee->GetBinContent(sf_ee->FindBin(1000*el1_pt, el1_eta));
	auto sf_el2 = sf_ee->GetBinContent(sf_ee->FindBin(1000*el2_pt, el2_eta));

	//std::cout << "sf_el1: " << sf_el1 << std::endl;
	//std::cout << "sf_el2: " << sf_el2 << std::endl;

	return sf_el1 * sf_el2;
}

void EventHMDY::ResetEvent()
{
 Lepton1.ResetEvent();
 Lepton2.ResetEvent();
 Lepton3.ResetEvent();

 TruthLepton1_Born.ResetEvent();
 TruthLepton2_Born.ResetEvent();
 TruthLepton1_Bare.ResetEvent();
 TruthLepton2_Bare.ResetEvent();
 TruthLepton1_Dressed.ResetEvent();
 TruthLepton2_Dressed.ResetEvent();

 TotalWeight = 0.0;
 TotalWeightLoose = 0.0;
 passSelection = 0;
 passSelectionEl = 0;
 passSelectionMu = 0;
 passSelectionElMu = 0;
 topTransferEl = 0.0;
 topTransferMu = 0.0;
 topTransferEl_HighMass_CosTheta = 0.0;
 topTransferMu_HighMass_CosTheta = 0.0;
 topTransferEl_HighMass_Rapidity = 0.0;
 topTransferMu_HighMass_Rapidity = 0.0;
 AdditionalWeight = 1.0;
 Normalization = 1.0;

 RecoWeight_PromptSubtrUp = 0.0;
 RecoWeight_PromptSubtrDown = 0.0;
 RecoWeight_noW = 0.0;
 RecoWeight_noDY = 0.0;
 RecoWeight_noZMass = 0.0;
 RecoWeight_StatsUp = 0.0;
 RecoWeight_StatsDown = 0.0;
 RecoWeight_stats_1up = 0.0;
 RecoWeight_stats_1down = 0.0;
 RecoWeight_d0Sig_1up = 0.0;
 RecoWeight_d0Sig_1down = 0.0;

 passSelectionEl_LowMass = 0;
 passSelectionMu_LowMass = 0;
 passSelectionElMu_LowMass = 0;

 Weight_Lepton1_SF = 1.0;
 Weight_Lepton2_SF = 1.0;
 RunNumber = -999;
 EventNumber = -999;
 mcChannelNumber = -999.0;
 RecoDilRapidity = -999.0;
 RecoDilPhi = -999.0;
 RecoDilMass = -999.0;
 RecoPseudoDilMass = -999.0;
 RecoDilPt = -999.0;
 RecoPhiStar = -999.0;
 RecoCosThetaStar = -999.0;
 RecoWeight = 0.0;
 RecoWeight_Stat_up = 0.0;
 RecoWeight_Stat_down = 0.0;
 RecoWeight_PromptSubtr_up = 0.0;
 RecoWeight_PromptSubtr_down = 0.0;
 RecoWeight_MET_up = 0.0;
 RecoWeight_MET_down = 0.0;
 RecoWeight_d0sig_up = 0.0;
 RecoWeight_d0sig_down = 0.0;
 RecoWeight_RealStat_up = 0.0;
 RecoWeight_RealStat_down = 0.0;
 RecoWeight_El_Stat_up = 0.0;
 RecoWeight_El_Stat_down = 0.0;
 RecoWeight_El_PromptSubtr_up = 0.0;
 RecoWeight_El_PromptSubtr_down = 0.0;
 RecoWeight_El_RealStat_up = 0.0;
 RecoWeight_El_RealStat_down = 0.0;
 RecoWeight_Mu_Stat_up = 0.0;
 RecoWeight_Mu_Stat_down = 0.0;
 RecoWeight_Mu_PromptSubtr_up = 0.0;
 RecoWeight_Mu_PromptSubtr_down = 0.0;
 RecoWeight_Mu_RealStat_up = 0.0;
 RecoWeight_Mu_RealStat_down = 0.0;
 RecoWeight_FourTerm_TT = 0.0;
 RecoWeight_FourTerm_TL = 0.0;
 RecoWeight_FourTerm_LT = 0.0;
 RecoWeight_FourTerm_LL = 0.0;
 eeChannel = false;
 mumuChannel = false;
 emuChannel = false;
 eeChannel_withmuon = false;
 SingleElectron = false;
 TruthDilMass_Born = -999.0;
 TruthDilRapidity_Born = -999.0;
 Lepton1_Pt = -999.0;
 Lepton2_Pt = -999.0;
 Lepton3_Pt = -999.0;
 Lepton1_Phi = -999.0;
 Lepton2_Phi = -999.0;
 Lepton3_Phi = -999.0;
 Lepton1_Eta = -999.0;
 Lepton2_Eta = -999.0;
 Lepton3_Eta = -999.0;
 pTllReweight = -999.0;
 ChargeMisIDSFWeight = -999.0;
 ChargeIDSFWeight = -999.0;
 LeptonSFWeight = -999.0;
 PileupWeight = -999.0;
 TriggerSF = 1.0;
 n_Bjets = -999;
 MET_Et = -999.0;
 Lepton1_z0 = -999.0;
 Lepton2_z0 = -999.0;
 Lepton3_z0 = -999.0;
 Lepton1_d0sig = -999.0;
 Lepton2_d0sig = -999.0;
 Lepton3_d0sig = -999.0;
 Lepton1_DeltaR = 999.0;
 Lepton2_DeltaR = 999.0;
 Mu = -999.0;
 MuActual = -999.0;
 PhiRF = -999.0;
 Weight_kFactor_Old = 1.0;
 Weight_kFactor_QCDEW = 1.0;
 Weight_kFactor_New_CT18NNLO = 1.0;
 Weight_kFactor_New_CT18ANNLO = 1.0;
 Weight_kFactor_PowhegtoSherpa = 1.0;

 Weight_indiv_SF_EL_ChargeMisID_STAT_UP = 1.0;
 Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN = 1.0;
 Weight_indiv_SF_EL_ChargeMisID_SYST_UP = 1.0;
 Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN = 1.0;

 Lepton_Pt_born = -999.0;
 AntiLepton_Pt_born = -999.0;
 Lepton_Eta_born = -999.0;
 AntiLepton_Eta_born = -999.0;
 Lepton_Phi_born = -999.0;
 AntiLepton_Phi_born = -999.0;
 Lepton_m_born = -999.0;
 AntiLepton_m_born = -999.0;
 Lepton_Pt_bare = -999.0;
 AntiLepton_Pt_bare = -999.0;
 Lepton_Eta_bare = -999.0;
 AntiLepton_Eta_bare = -999.0;
 Lepton_Phi_bare = -999.0;
 AntiLepton_Phi_bare = -999.0;
 Lepton_Pt_dressed = -999.0;
 Lepton_Eta_dressed = -999.0;
 Lepton_Phi_dressed = -999.0;
 Lepton_Charge_dressed = -999.0;
 AntiLepton_Pt_dressed = -999.0;
 AntiLepton_Eta_dressed = -999.0;
 AntiLepton_Phi_dressed = -999.0;
 AntiLepton_Charge_dressed = -999.0;

 pass_ee_TT = false;
 pass_ee_TL = false;
 pass_ee_LT = false;
 pass_ee_LL = false;
 pass_mm_TT = false;
 pass_mm_TL = false;
 pass_mm_LT = false;
 pass_mm_LL = false;
 pass_em_TT = false;
 pass_em_TL = false;
 pass_em_LT = false;
 pass_em_LL = false;
 Lepton1_isTight = 0;
 Lepton2_isTight = 0;
 Lepton3_isTight = 0;
 Lepton1_passMediumID = 0;
 Lepton2_passMediumID = 0;
 Lepton3_passMediumID = 0;
 Lepton1_passLooseID = 0;
 Lepton2_passLooseID = 0;
 Lepton3_passLooseID = 0;
 Lepton1_passIso = 0;
 Lepton2_passIso = 0;
 Lepton1_IsoWeight = 0.0;
 Lepton2_IsoWeight = 0.0;

 Lepton1_Charge = 0;
 Lepton2_Charge = 0;
 Lepton1_isTruthMatch = 0;
 Lepton2_isTruthMatch = 0;
 Lepton1_TightWeight = 0.0;
 Lepton2_TightWeight = 0.0;
 Lepton3_TightWeight = 0.0;
 Lepton1_LooseWeight = 0.0;
 Lepton2_LooseWeight = 0.0;
 Lepton3_LooseWeight = 0.0;
 Lepton1_MediumIDWeight = 0.0;
 Lepton2_MediumIDWeight = 0.0;

 PrescaleFactor = 1.0;
 Lepton1_PrescaleFactor = 1.0;
 Lepton2_PrescaleFactor = 1.0;

 passElFake = 0;
 passMuFake = 0;

 Lepton1_FakeRate = -999.0;
 Lepton2_FakeRate = -999.0;

 isElSample = false;
 isMuSample = false;
}

void HMDYLepton::ResetEvent()
{
 Flavor = 0;
 Charge = 0;
 isTight = 0;
 isTruthMatch = 0;
 TrigMatch = 0;

 looseID = 0;
 mediumID = 0;
 tightID = 0;
 FCLooseIso = 0;
 FCTightIso = 0;

 z0 = -999.0;
 d0Sig = -999.0;

 TriggerSF = -999.0;
 IsoSF = -999.0;
 RecoSF = -999.0;
 IDSF = -999.0;
 TTVASF = -999.0;

 LooseIDSF = -999.0;

 TightWeight = -999.0;
 LooseWeight = -999.0;

 PrescaleFactor = 0.0;

 P4.SetPtEtaPhiM(0,0,0,0);
}

void loopHMDY::End(int RootNumber)
{
 cout<<"\r"<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<"  "<<flush;//yfu

 if(!isInputPreTree){
   if(!HMDYTree->fChain[RootNumber])
    {
     cout<<"XXXXX**Runing: BIG ERROR!!! No File loaded!"<<endl;
     return;
    }
   HMDYTree->CloseFile(RootNumber);
   delete HMDYTree->fChain[RootNumber]->GetCurrentFile();
 }

 if(isInputPreTree){
   if(!PreHMDYTree->fChain[RootNumber])
    {
     cout<<"XXXXX**Runing: BIG ERROR!!! No File loaded!"<<endl;
     return;
    }
   PreHMDYTree->CloseFile(RootNumber);
   delete PreHMDYTree->fChain[RootNumber]->GetCurrentFile();
 }
}

void loopHMDY::Finish()
{
 myLog<<LOG_INFO<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(!isInputPreTree){
   if(EndFile == RootNames.size()) delete HMDYTree;
 }

 if(isInputPreTree){
   if(EndFile == RootNames.size()) delete PreHMDYTree;
 }

 if(JustGenerateTree){
   HMDYTree->SaveFile();
 }

 //for multi-run the loop function
 if(isInputPreTree){
   delete HMDYTree;
 }

}

loopHMDY::~loopHMDY()
{
}


