#define ZPrime_loopZPrime_cxx
#include <iostream>
#include "ZPrime/loopZPrime.h"

using namespace std;

loopZPrime::loopZPrime(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopZPrime::InputHist(HistsZPrime* &myhists)
{
 this->myhists = myhists;

 if(myhists->doTopDD){
   doTopDD = true;
   topDD = myhists->topDD->Clone(iThread);
   topDD_HighMass_CosTheta = myhists->topDD_HighMass_CosTheta->Clone(iThread);
   topDD_HighMass_Rapidity = myhists->topDD_HighMass_Rapidity->Clone(iThread);
 }
}

void loopZPrime::InputTree(TreeForZPrime *ZPrimeTree)
{
 this->ZPrimeTree = ZPrimeTree;
 this->RootNames = ZPrimeTree->RootNames;

 this->RootTypes = ZPrimeTree->RootTypes;

 this->FirstFile = ZPrimeTree->FirstFile;
 this->EndFile = ZPrimeTree->EndFile;

 this->OneFilePerJob = ZPrimeTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = ZPrimeTree->TotalEntries[ifile];
 }
}

void loopZPrime::InputTree(TreeForPreZPrime *PreZPrimeTree)
{
 isInputPreTree = true;

 this->PreZPrimeTree = PreZPrimeTree;
 this->RootNames = PreZPrimeTree->RootNames;

 this->RootTypes = PreZPrimeTree->RootTypes;

 this->SumOfWeightsMap = PreZPrimeTree->SumOfWeightsMap;
 this->Years = PreZPrimeTree->Years;
 this->DSIDs = PreZPrimeTree->DSIDs;
 this->isLooseTree = PreZPrimeTree->isLooseTree;

 this->FirstFile = PreZPrimeTree->FirstFile;
 this->EndFile = PreZPrimeTree->EndFile;

 this->OneFilePerJob = PreZPrimeTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = PreZPrimeTree->TotalEntries[ifile];
 }

 this->ZPrimeTree = new TreeForZPrime();

 if(JustGenerateTree){
   if(!NtupleName.Contains("root")) NtupleName = PreZPrimeTree->SaveName;
   this->ZPrimeTree->GenerateFile(NtupleName);
   this->ZPrimeTree->DefineTree(0, "nominal", PreZPrimeTree);
 }

 SSMModel_0p5TeV = new ZPrimeTripletSignalModule("SSMModel_0.5TeV");
 SSMModel_0p5TeV->initialize();
 SSMModel_0p5TeV->setZPrimeMass(500.0);
 SSMModel_0p5TeV->setgmZMode(3);
 if(AngularFileName != "") SSMModel_0p5TeV->PrepareInterpolation(AngularFileName);

 SSMModel_0p6TeV = new ZPrimeTripletSignalModule("SSMModel_0.6TeV");
 SSMModel_0p6TeV->initialize();
 SSMModel_0p6TeV->setZPrimeMass(600.0);
 SSMModel_0p6TeV->setgmZMode(3);
 if(AngularFileName != "") SSMModel_0p6TeV->PrepareInterpolation(AngularFileName);

 SSMModel_0p8TeV = new ZPrimeTripletSignalModule("SSMModel_0.8TeV");
 SSMModel_0p8TeV->initialize();
 SSMModel_0p8TeV->setZPrimeMass(800.0);
 SSMModel_0p8TeV->setgmZMode(3);
 if(AngularFileName != "") SSMModel_0p8TeV->PrepareInterpolation(AngularFileName);

 SSMModel_1TeV = new ZPrimeTripletSignalModule("SSMModel_1TeV");
 SSMModel_1TeV->initialize();
 SSMModel_1TeV->setZPrimeMass(1000.0);
 SSMModel_1TeV->setgmZMode(3);
 if(AngularFileName != "") SSMModel_1TeV->PrepareInterpolation(AngularFileName);

 SSMModel_2TeV = new ZPrimeTripletSignalModule("SSMModel_2TeV");
 SSMModel_2TeV->initialize();
 SSMModel_2TeV->setZPrimeMass(2000.0);
 SSMModel_2TeV->setgmZMode(3);
 if(AngularFileName != "") SSMModel_2TeV->PrepareInterpolation(AngularFileName);

 SSMModel_3TeV = new ZPrimeTripletSignalModule("SSMModel_3TeV");
 SSMModel_3TeV->initialize();
 SSMModel_3TeV->setZPrimeMass(3000.0);
 SSMModel_3TeV->setgmZMode(3);
 if(AngularFileName != "") SSMModel_3TeV->PrepareInterpolation(AngularFileName);

 SSMModel_4TeV = new ZPrimeTripletSignalModule("SSMModel_4TeV");
 SSMModel_4TeV->initialize();
 SSMModel_4TeV->setZPrimeMass(4000.0);
 SSMModel_4TeV->setgmZMode(3);
 if(AngularFileName != "") SSMModel_4TeV->PrepareInterpolation(AngularFileName);

 SSMModel_5TeV = new ZPrimeTripletSignalModule("SSMModel_5TeV");
 SSMModel_5TeV->initialize();
 SSMModel_5TeV->setZPrimeMass(5000.0);
 SSMModel_5TeV->setgmZMode(3);
 if(AngularFileName != "") SSMModel_5TeV->PrepareInterpolation(AngularFileName);

 SSMModel_6TeV = new ZPrimeTripletSignalModule("SSMModel_6TeV");
 SSMModel_6TeV->initialize();
 SSMModel_6TeV->setZPrimeMass(6000.0);
 SSMModel_6TeV->setgmZMode(3);
 if(AngularFileName != "") SSMModel_6TeV->PrepareInterpolation(AngularFileName);

 SSMModel_7TeV = new ZPrimeTripletSignalModule("SSMModel_7TeV");
 SSMModel_7TeV->initialize();
 SSMModel_7TeV->setZPrimeMass(7000.0);
 SSMModel_7TeV->setgmZMode(3);
 if(AngularFileName != "") SSMModel_7TeV->PrepareInterpolation(AngularFileName);

 SSMModel_8TeV = new ZPrimeTripletSignalModule("SSMModel_8TeV");
 SSMModel_8TeV->initialize();
 SSMModel_8TeV->setZPrimeMass(8000.0);
 SSMModel_8TeV->setgmZMode(3);
 if(AngularFileName != "") SSMModel_8TeV->PrepareInterpolation(AngularFileName);

 E6ChiModel_0p5TeV = new ZPrimeTripletSignalModule("E6ChiModel_0.5TeV");
 E6ChiModel_0p5TeV->initialize();
 E6ChiModel_0p5TeV->setZPrimeMass(500.0);
 E6ChiModel_0p5TeV->setgmZMode(3);
 if(AngularFileName != "") E6ChiModel_0p5TeV->PrepareInterpolation(AngularFileName);

 E6ChiModel_0p6TeV = new ZPrimeTripletSignalModule("E6ChiModel_0.6TeV");
 E6ChiModel_0p6TeV->initialize();
 E6ChiModel_0p6TeV->setZPrimeMass(600.0);
 E6ChiModel_0p6TeV->setgmZMode(3);
 if(AngularFileName != "") E6ChiModel_0p6TeV->PrepareInterpolation(AngularFileName);

 E6ChiModel_0p8TeV = new ZPrimeTripletSignalModule("E6ChiModel_0.8TeV");
 E6ChiModel_0p8TeV->initialize();
 E6ChiModel_0p8TeV->setZPrimeMass(800.0);
 E6ChiModel_0p8TeV->setgmZMode(3);
 if(AngularFileName != "") E6ChiModel_0p8TeV->PrepareInterpolation(AngularFileName);

 E6ChiModel_1TeV = new ZPrimeTripletSignalModule("E6ChiModel_1TeV");
 E6ChiModel_1TeV->initialize();
 E6ChiModel_1TeV->setZPrimeMass(1000.0);
 E6ChiModel_1TeV->setgmZMode(3);
 if(AngularFileName != "") E6ChiModel_1TeV->PrepareInterpolation(AngularFileName);

 E6ChiModel_2TeV = new ZPrimeTripletSignalModule("E6ChiModel_2TeV");
 E6ChiModel_2TeV->initialize();
 E6ChiModel_2TeV->setZPrimeMass(2000.0);
 E6ChiModel_2TeV->setgmZMode(3);
 if(AngularFileName != "") E6ChiModel_2TeV->PrepareInterpolation(AngularFileName);

 E6ChiModel_3TeV = new ZPrimeTripletSignalModule("E6ChiModel_3TeV");
 E6ChiModel_3TeV->initialize();
 E6ChiModel_3TeV->setZPrimeMass(3000.0);
 E6ChiModel_3TeV->setgmZMode(3);
 if(AngularFileName != "") E6ChiModel_3TeV->PrepareInterpolation(AngularFileName);

 E6ChiModel_4TeV = new ZPrimeTripletSignalModule("E6ChiModel_4TeV");
 E6ChiModel_4TeV->initialize();
 E6ChiModel_4TeV->setZPrimeMass(4000.0);
 E6ChiModel_4TeV->setgmZMode(3);
 if(AngularFileName != "") E6ChiModel_4TeV->PrepareInterpolation(AngularFileName);

 E6ChiModel_5TeV = new ZPrimeTripletSignalModule("E6ChiModel_5TeV");
 E6ChiModel_5TeV->initialize();
 E6ChiModel_5TeV->setZPrimeMass(5000.0);
 E6ChiModel_5TeV->setgmZMode(3);
 if(AngularFileName != "") E6ChiModel_5TeV->PrepareInterpolation(AngularFileName);

 E6ChiModel_6TeV = new ZPrimeTripletSignalModule("E6ChiModel_6TeV");
 E6ChiModel_6TeV->initialize();
 E6ChiModel_6TeV->setZPrimeMass(6000.0);
 E6ChiModel_6TeV->setgmZMode(3);
 if(AngularFileName != "") E6ChiModel_6TeV->PrepareInterpolation(AngularFileName);

 E6ChiModel_7TeV = new ZPrimeTripletSignalModule("E6ChiModel_7TeV");
 E6ChiModel_7TeV->initialize();
 E6ChiModel_7TeV->setZPrimeMass(7000.0);
 E6ChiModel_7TeV->setgmZMode(3);
 if(AngularFileName != "") E6ChiModel_7TeV->PrepareInterpolation(AngularFileName);

 E6ChiModel_8TeV = new ZPrimeTripletSignalModule("E6ChiModel_8TeV");
 E6ChiModel_8TeV->initialize();
 E6ChiModel_8TeV->setZPrimeMass(8000.0);
 E6ChiModel_8TeV->setgmZMode(3);
 if(AngularFileName != "") E6ChiModel_8TeV->PrepareInterpolation(AngularFileName);

 E6PsiModel_0p5TeV = new ZPrimeTripletSignalModule("E6PsiModel_0.5TeV");
 E6PsiModel_0p5TeV->initialize();
 E6PsiModel_0p5TeV->setZPrimeMass(500.0);
 E6PsiModel_0p5TeV->setgmZMode(3);
 if(AngularFileName != "") E6PsiModel_0p5TeV->PrepareInterpolation(AngularFileName);

 E6PsiModel_0p6TeV = new ZPrimeTripletSignalModule("E6PsiModel_0.6TeV");
 E6PsiModel_0p6TeV->initialize();
 E6PsiModel_0p6TeV->setZPrimeMass(600.0);
 E6PsiModel_0p6TeV->setgmZMode(3);
 if(AngularFileName != "") E6PsiModel_0p6TeV->PrepareInterpolation(AngularFileName);

 E6PsiModel_0p8TeV = new ZPrimeTripletSignalModule("E6PsiModel_0.8TeV");
 E6PsiModel_0p8TeV->initialize();
 E6PsiModel_0p8TeV->setZPrimeMass(800.0);
 E6PsiModel_0p8TeV->setgmZMode(3);
 if(AngularFileName != "") E6PsiModel_0p8TeV->PrepareInterpolation(AngularFileName);

 E6PsiModel_1TeV = new ZPrimeTripletSignalModule("E6PsiModel_1TeV");
 E6PsiModel_1TeV->initialize();
 E6PsiModel_1TeV->setZPrimeMass(1000.0);
 E6PsiModel_1TeV->setgmZMode(3);
 if(AngularFileName != "") E6PsiModel_1TeV->PrepareInterpolation(AngularFileName);

 E6PsiModel_2TeV = new ZPrimeTripletSignalModule("E6PsiModel_2TeV");
 E6PsiModel_2TeV->initialize();
 E6PsiModel_2TeV->setZPrimeMass(2000.0);
 E6PsiModel_2TeV->setgmZMode(3);
 if(AngularFileName != "") E6PsiModel_2TeV->PrepareInterpolation(AngularFileName);

 E6PsiModel_3TeV = new ZPrimeTripletSignalModule("E6PsiModel_3TeV");
 E6PsiModel_3TeV->initialize();
 E6PsiModel_3TeV->setZPrimeMass(3000.0);
 E6PsiModel_3TeV->setgmZMode(3);
 if(AngularFileName != "") E6PsiModel_3TeV->PrepareInterpolation(AngularFileName);

 E6PsiModel_4TeV = new ZPrimeTripletSignalModule("E6PsiModel_4TeV");
 E6PsiModel_4TeV->initialize();
 E6PsiModel_4TeV->setZPrimeMass(4000.0);
 E6PsiModel_4TeV->setgmZMode(3);
 if(AngularFileName != "") E6PsiModel_4TeV->PrepareInterpolation(AngularFileName);

 E6PsiModel_5TeV = new ZPrimeTripletSignalModule("E6PsiModel_5TeV");
 E6PsiModel_5TeV->initialize();
 E6PsiModel_5TeV->setZPrimeMass(5000.0);
 E6PsiModel_5TeV->setgmZMode(3);
 if(AngularFileName != "") E6PsiModel_5TeV->PrepareInterpolation(AngularFileName);

 E6PsiModel_6TeV = new ZPrimeTripletSignalModule("E6PsiModel_6TeV");
 E6PsiModel_6TeV->initialize();
 E6PsiModel_6TeV->setZPrimeMass(6000.0);
 E6PsiModel_6TeV->setgmZMode(3);
 if(AngularFileName != "") E6PsiModel_6TeV->PrepareInterpolation(AngularFileName);

 E6PsiModel_7TeV = new ZPrimeTripletSignalModule("E6PsiModel_7TeV");
 E6PsiModel_7TeV->initialize();
 E6PsiModel_7TeV->setZPrimeMass(7000.0);
 E6PsiModel_7TeV->setgmZMode(3);
 if(AngularFileName != "") E6PsiModel_7TeV->PrepareInterpolation(AngularFileName);

 E6PsiModel_8TeV = new ZPrimeTripletSignalModule("E6PsiModel_8TeV");
 E6PsiModel_8TeV->initialize();
 E6PsiModel_8TeV->setZPrimeMass(8000.0);
 E6PsiModel_8TeV->setgmZMode(3);
 if(AngularFileName != "") E6PsiModel_8TeV->PrepareInterpolation(AngularFileName);

}

void loopZPrime::InputNtupleName(TString NtupleName)
{
//this name will be override by the automatic name
 this->NtupleName = NtupleName;
}

void loopZPrime::ReadTree(int ifile)
{
 if(RootTypes.at(ifile) == "Data") isData = true;
 else isData = false;

 this->MCType = RootTypes.at(ifile);

 if(RootNames.at(ifile).Contains("Loose")) isLooseTree = true;
 else isLooseTree = false;

 if(ZPrimeTree->AdditionalWeightName.count(RootTypes.at(ifile)) > 0) isAdditionalWeight = true;
 else isAdditionalWeight = false;

 if(ZPrimeTree->Normalization.count(RootTypes.at(ifile)) > 0) isChangeNorm = true;
 else isChangeNorm = false;

 if(ZPrimeTree->SystematicName == "Fake_Matrix_Electron__1up" && (RootNames.at(ifile).Contains("ntuple_MM") || RootNames.at(ifile).Contains("Fake_Matrix_Electron"))) isElFake_up = true;
 else isElFake_up = false;

 if(ZPrimeTree->SystematicName == "Fake_Matrix_Electron__1down" && (RootNames.at(ifile).Contains("ntuple_MM") || RootNames.at(ifile).Contains("Fake_Matrix_Electron"))) isElFake_down = true;
 else isElFake_down = false;

 if(ZPrimeTree->SystematicName == "Fake_Matrix_Muon__1up" && (RootNames.at(ifile).Contains("matrix_Data_all_Dimuon") || RootNames.at(ifile).Contains("Fake_Matrix_Muon"))) isMuFake_up = true;
 else isMuFake_up = false;

 if(ZPrimeTree->SystematicName == "Fake_Matrix_Muon__1down" && (RootNames.at(ifile).Contains("matrix_Data_all_Dimuon") || RootNames.at(ifile).Contains("Fake_Matrix_Muon"))) isMuFake_down = true;
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

   ZPrimeTree->GetEntry(ifile, iEvent);

   DefaultEvent.ResetEvent();

   DefaultEvent.passElTrigger                 = ZPrimeTree->passElTrigger;
   DefaultEvent.passMuTrigger                 = ZPrimeTree->passMuTrigger;

   DefaultEvent.Weight_Lepton1_SF             = ZPrimeTree->Weight_Lepton1_SF;
   DefaultEvent.Weight_Lepton2_SF             = ZPrimeTree->Weight_Lepton2_SF;
   DefaultEvent.RunNumber                     = ZPrimeTree->RunNumber;
   DefaultEvent.RandomRunNumber               = ZPrimeTree->randomRunNumber;
   DefaultEvent.EventNumber                   = ZPrimeTree->EventNumber;
   DefaultEvent.mcChannelNumber               = ZPrimeTree->mcChannelNumber;
   DefaultEvent.RecoDilRapidity               = ZPrimeTree->RecoDilRapidity;
   DefaultEvent.RecoDilPhi                    = ZPrimeTree->RecoDilPhi;
   DefaultEvent.RecoDilMass                   = ZPrimeTree->RecoDilMass;
   DefaultEvent.RecoPseudoDilMass             = ZPrimeTree->RecoPseudoDilMass;
   DefaultEvent.RecoDilPt                     = ZPrimeTree->RecoDilPt;
   DefaultEvent.RecoPhiStar                   = ZPrimeTree->RecoPhiStar;
   DefaultEvent.RecoCosThetaStar              = ZPrimeTree->RecoCosThetaStar;
   DefaultEvent.RecoWeight                    = ZPrimeTree->RecoWeight;
   DefaultEvent.RecoWeight_Stat_up            = ZPrimeTree->RecoWeight_Stat_up;
   DefaultEvent.RecoWeight_Stat_down          = ZPrimeTree->RecoWeight_Stat_down;
   DefaultEvent.RecoWeight_PromptSubtr_up     = ZPrimeTree->RecoWeight_PromptSubtr_up;
   DefaultEvent.RecoWeight_PromptSubtr_down   = ZPrimeTree->RecoWeight_PromptSubtr_down;
   DefaultEvent.RecoWeight_MET_up             = ZPrimeTree->RecoWeight_MET_up;
   DefaultEvent.RecoWeight_MET_down           = ZPrimeTree->RecoWeight_MET_down;
   DefaultEvent.RecoWeight_d0sig_up           = ZPrimeTree->RecoWeight_d0sig_up;
   DefaultEvent.RecoWeight_d0sig_down         = ZPrimeTree->RecoWeight_d0sig_down;
   DefaultEvent.RecoWeight_RealStat_up        = ZPrimeTree->RecoWeight_RealStat_up;
   DefaultEvent.RecoWeight_RealStat_down      = ZPrimeTree->RecoWeight_RealStat_down;
   DefaultEvent.RecoWeight_FourTerm_TT        = ZPrimeTree->RecoWeight_FourTerm_TT;
   DefaultEvent.RecoWeight_FourTerm_TL        = ZPrimeTree->RecoWeight_FourTerm_TL;
   DefaultEvent.RecoWeight_FourTerm_LT        = ZPrimeTree->RecoWeight_FourTerm_LT;
   DefaultEvent.RecoWeight_FourTerm_LL        = ZPrimeTree->RecoWeight_FourTerm_LL;
   DefaultEvent.eeChannel                     = ZPrimeTree->eeChannel;
   DefaultEvent.mumuChannel                   = ZPrimeTree->mumuChannel;
   DefaultEvent.emuChannel                    = ZPrimeTree->emuChannel;
   DefaultEvent.eeChannel_withmuon            = ZPrimeTree->eeChannel_withmuon;
   DefaultEvent.SingleElectron                = ZPrimeTree->SingleElectron;

   if(RootNames.at(ifile).Contains("PI_ee")){
     DefaultEvent.mumuChannel = 0;
     DefaultEvent.isElSample = true;
   }
   if(RootNames.at(ifile).Contains("PI_mumu")){
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

   DefaultEvent.TruthDilMass_Born             = ZPrimeTree->TruthDilMass_Born;
   DefaultEvent.TruthDilRapidity_Born         = ZPrimeTree->TruthDilRapidity_Born;
   DefaultEvent.Lepton1_Pt                    = ZPrimeTree->Lepton1_Pt;
   DefaultEvent.Lepton2_Pt                    = ZPrimeTree->Lepton2_Pt;
   DefaultEvent.Lepton3_Pt                    = ZPrimeTree->Lepton3_Pt;
   DefaultEvent.Lepton1_Phi                   = ZPrimeTree->Lepton1_Phi;
   DefaultEvent.Lepton2_Phi                   = ZPrimeTree->Lepton2_Phi;
   DefaultEvent.Lepton3_Phi                   = ZPrimeTree->Lepton3_Phi;
   DefaultEvent.Lepton1_Eta                   = ZPrimeTree->Lepton1_Eta;
   DefaultEvent.Lepton2_Eta                   = ZPrimeTree->Lepton2_Eta;
   DefaultEvent.Lepton3_Eta                   = ZPrimeTree->Lepton3_Eta;
   DefaultEvent.pTllReweight                  = ZPrimeTree->pTllReweight;
   DefaultEvent.ChargeMisIDSFWeight           = ZPrimeTree->ChargeMisIDSFWeight;
   DefaultEvent.ChargeIDSFWeight              = ZPrimeTree->ChargeIDSFWeight;
   DefaultEvent.LeptonSFWeight                = ZPrimeTree->LeptonSFWeight;
   DefaultEvent.PileupWeight                  = ZPrimeTree->PileupWeight;
   DefaultEvent.TriggerSF                     = ZPrimeTree->TriggerSF;
   DefaultEvent.n_Bjets                       = ZPrimeTree->n_Bjets;
   DefaultEvent.MET_Et                        = ZPrimeTree->MET_Et;
   DefaultEvent.Lepton1_z0                    = ZPrimeTree->Lepton1_z0;
   DefaultEvent.Lepton2_z0                    = ZPrimeTree->Lepton2_z0;
   DefaultEvent.Lepton3_z0                    = ZPrimeTree->Lepton3_z0;
   DefaultEvent.Lepton1_d0sig                 = ZPrimeTree->Lepton1_d0sig;
   DefaultEvent.Lepton2_d0sig                 = ZPrimeTree->Lepton2_d0sig;
   DefaultEvent.Lepton3_d0sig                 = ZPrimeTree->Lepton3_d0sig;
   DefaultEvent.Lepton1_DeltaR                = ZPrimeTree->Lepton1_DeltaR;
   DefaultEvent.Lepton2_DeltaR                = ZPrimeTree->Lepton2_DeltaR;
   DefaultEvent.Mu                            = ZPrimeTree->Mu;
   DefaultEvent.MuActual                      = ZPrimeTree->MuActual;
   DefaultEvent.PhiRF                         = ZPrimeTree->PhiRF;
   DefaultEvent.Weight_kFactor_Old            = ZPrimeTree->Weight_kFactor_Old;
   DefaultEvent.Weight_kFactor_QCDEW          = ZPrimeTree->Weight_kFactor_QCDEW;
   DefaultEvent.Weight_kFactor_New_CT18NNLO   = ZPrimeTree->Weight_kFactor_New_CT18NNLO;
   DefaultEvent.Weight_kFactor_New_CT18ANNLO  = ZPrimeTree->Weight_kFactor_New_CT18ANNLO;
   DefaultEvent.Weight_kFactor_PowhegtoSherpa = ZPrimeTree->Weight_kFactor_PowhegtoSherpa;

   DefaultEvent.Lepton_Pt_born                = ZPrimeTree->Lepton_Pt_born;
   DefaultEvent.AntiLepton_Pt_born            = ZPrimeTree->AntiLepton_Pt_born;
   DefaultEvent.Lepton_Eta_born               = ZPrimeTree->Lepton_Eta_born;
   DefaultEvent.AntiLepton_Eta_born           = ZPrimeTree->AntiLepton_Eta_born;
   DefaultEvent.Lepton_Phi_born               = ZPrimeTree->Lepton_Phi_born;
   DefaultEvent.AntiLepton_Phi_born           = ZPrimeTree->AntiLepton_Phi_born;
   DefaultEvent.Lepton_m_born                 = ZPrimeTree->Lepton_m_born;
   DefaultEvent.AntiLepton_m_born             = ZPrimeTree->AntiLepton_m_born;
   DefaultEvent.Lepton_Pt_bare                = ZPrimeTree->Lepton_Pt_bare;
   DefaultEvent.AntiLepton_Pt_bare            = ZPrimeTree->AntiLepton_Pt_bare;
   DefaultEvent.Lepton_Eta_bare               = ZPrimeTree->Lepton_Eta_bare;
   DefaultEvent.AntiLepton_Eta_bare           = ZPrimeTree->AntiLepton_Eta_bare;
   DefaultEvent.Lepton_Phi_bare               = ZPrimeTree->Lepton_Phi_bare;
   DefaultEvent.AntiLepton_Phi_bare           = ZPrimeTree->AntiLepton_Phi_bare;
   DefaultEvent.Lepton_Pt_dressed             = ZPrimeTree->Lepton_Pt_dressed;
   DefaultEvent.Lepton_Eta_dressed            = ZPrimeTree->Lepton_Eta_dressed;
   DefaultEvent.Lepton_Phi_dressed            = ZPrimeTree->Lepton_Phi_dressed;
   DefaultEvent.Lepton_Charge_dressed         = ZPrimeTree->Lepton_Charge_dressed;
   DefaultEvent.AntiLepton_Pt_dressed         = ZPrimeTree->AntiLepton_Pt_dressed;
   DefaultEvent.AntiLepton_Eta_dressed        = ZPrimeTree->AntiLepton_Eta_dressed;
   DefaultEvent.AntiLepton_Phi_dressed        = ZPrimeTree->AntiLepton_Phi_dressed;
   DefaultEvent.AntiLepton_Charge_dressed     = ZPrimeTree->AntiLepton_Charge_dressed;

   DefaultEvent.pass_ee_TT                    = ZPrimeTree->pass_ee_TT;
   DefaultEvent.pass_ee_TL                    = ZPrimeTree->pass_ee_TL;
   DefaultEvent.pass_ee_LT                    = ZPrimeTree->pass_ee_LT;
   DefaultEvent.pass_ee_LL                    = ZPrimeTree->pass_ee_LL;
   DefaultEvent.pass_mm_TT                    = ZPrimeTree->pass_mm_TT;
   DefaultEvent.pass_mm_TL                    = ZPrimeTree->pass_mm_TL;
   DefaultEvent.pass_mm_LT                    = ZPrimeTree->pass_mm_LT;
   DefaultEvent.pass_mm_LL                    = ZPrimeTree->pass_mm_LL;
   DefaultEvent.Lepton1_isTight               = ZPrimeTree->Lepton1_isTight;
   DefaultEvent.Lepton2_isTight               = ZPrimeTree->Lepton2_isTight;
   DefaultEvent.Lepton3_isTight               = ZPrimeTree->Lepton3_isTight;
   DefaultEvent.Lepton1_passMediumID          = ZPrimeTree->Lepton1_passMediumID;
   DefaultEvent.Lepton2_passMediumID          = ZPrimeTree->Lepton2_passMediumID;
   DefaultEvent.Lepton3_passMediumID          = ZPrimeTree->Lepton3_passMediumID;
   DefaultEvent.Lepton1_passLooseID           = ZPrimeTree->Lepton1_passLooseID;
   DefaultEvent.Lepton2_passLooseID           = ZPrimeTree->Lepton2_passLooseID;
   DefaultEvent.Lepton3_passLooseID           = ZPrimeTree->Lepton3_passLooseID;
   DefaultEvent.Lepton1_passIso               = ZPrimeTree->Lepton1_passIso;
   DefaultEvent.Lepton2_passIso               = ZPrimeTree->Lepton2_passIso;
   DefaultEvent.Lepton1_IsoWeight             = ZPrimeTree->Lepton1_IsoWeight;
   DefaultEvent.Lepton2_IsoWeight             = ZPrimeTree->Lepton2_IsoWeight;

   DefaultEvent.Lepton1_Charge                = ZPrimeTree->Lepton1_Charge;
   DefaultEvent.Lepton2_Charge                = ZPrimeTree->Lepton2_Charge;
   DefaultEvent.Lepton1_isTruthMatch          = ZPrimeTree->Lepton1_isTruthMatch;
   DefaultEvent.Lepton2_isTruthMatch          = ZPrimeTree->Lepton2_isTruthMatch;
   DefaultEvent.Lepton1_TightWeight           = ZPrimeTree->Lepton1_TightWeight;
   DefaultEvent.Lepton2_TightWeight           = ZPrimeTree->Lepton2_TightWeight;
   DefaultEvent.Lepton3_TightWeight           = ZPrimeTree->Lepton3_TightWeight;
   DefaultEvent.Lepton1_LooseWeight           = ZPrimeTree->Lepton1_LooseWeight;
   DefaultEvent.Lepton2_LooseWeight           = ZPrimeTree->Lepton2_LooseWeight;
   DefaultEvent.Lepton3_LooseWeight           = ZPrimeTree->Lepton3_LooseWeight;
   DefaultEvent.Lepton1_MediumIDWeight        = ZPrimeTree->Lepton1_MediumIDWeight;
   DefaultEvent.Lepton2_MediumIDWeight        = ZPrimeTree->Lepton2_MediumIDWeight;
   DefaultEvent.PrescaleFactor                = ZPrimeTree->PrescaleFactor;
   DefaultEvent.Lepton1_PrescaleFactor        = ZPrimeTree->Lepton1_PrescaleFactor;
   DefaultEvent.Lepton2_PrescaleFactor        = ZPrimeTree->Lepton2_PrescaleFactor;

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

   if(isAdditionalWeight) DefaultEvent.AdditionalWeight = ZPrimeTree->AdditionalWeight.at(MCType);
   if(isChangeNorm) DefaultEvent.Normalization = ZPrimeTree->Normalization.at(MCType);

   FillHist(DefaultEvent);
 }

}

void loopZPrime::PreLoop(int ifile)
{
 if(RootTypes.at(ifile) == "Data") isData = true;
 else isData = false;

 if(RootNames.at(ifile).Contains("Loose")) isLooseTree = true;
 else isLooseTree = false;

 this->MCType = RootTypes.at(ifile);

 for(int ibkghist = 0; ibkghist < myhists->BkgHist_1d.size(); ibkghist++){
   myhists->BkgHist_1d.at(ibkghist)->HistPtr(iThread - 1)->Initial(RootTypes.at(ifile));
 }

 for(int iprocesshist = 0; iprocesshist < myhists->hist_process.size(); iprocesshist++){
   myhists->hist_process.at(iprocesshist)->Initial(iThread, RootTypes.at(ifile));
 }

 PreZPrimeTree->GetEntry(ifile, 0);
 //CrossSection = GetZPrimeCrossSection(PreZPrimeTree->mcChannelNumber);

 //int DSID = DSIDs.at(ifile);
 //int Year = Years.at(ifile);
 //pair<int, int> RootTypePair;
 //RootTypePair = make_pair(DSID, Year);
 //SumOfWeight = SumOfWeightsMap.at(RootTypePair);

 if(isData) SumOfWeight = 1.0;

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"\r"<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<flush;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"\r"<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
     if(!isThread) cout<<"\r"<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
   }

   PreZPrimeTree->GetEntry(ifile, iEvent);

   if(FillEvents()){
     if(JustGenerateTree) ZPrimeTree->FillTree(0);

     if(FinishProcess) FillHist(SelectedEvent);
   }

 }

}

bool loopZPrime::FillEvents()
{
 SelectedEvent.ResetEvent();

 bool ElTriggerSelectionPassed = false;

 bool FakeElTriggerSelectionPassed = false;

 bool PassTrig = false;

 if(isNormalRun || isElRealEffRun || isMuRealEffRun || isUnfoldRun) PassTrig = ElTriggerSelectionPassed;

 if(isElFakeEffRun) PassTrig = FakeElTriggerSelectionPassed; 

 if(isData){
   if(PreZPrimeTree->runNumber >= 430536 && PreZPrimeTree->runNumber <= 440613) SelectedEvent.passElTrigger = PreZPrimeTree->HLT_2e24_lhvloose_L12EM20VH;

   if(PreZPrimeTree->runNumber >= 451094 && PreZPrimeTree->runNumber <= 456749) SelectedEvent.passElTrigger = PreZPrimeTree->HLT_2e24_lhvloose_L12eEM24L;

   if(PreZPrimeTree->runNumber >= 473235 && PreZPrimeTree->runNumber <= 486706) SelectedEvent.passElTrigger = PreZPrimeTree->HLT_2e24_lhvloose_L12eEM24L;

   if(PreZPrimeTree->runNumber >= 430536 && PreZPrimeTree->runNumber <= 440613) SelectedEvent.passMuTrigger = PreZPrimeTree->HLT_mu24_ivarmedium_L1MU14FCH || PreZPrimeTree->HLT_mu50_L1MU14FCH;

   if(PreZPrimeTree->runNumber >= 451094 && PreZPrimeTree->runNumber <= 456749) SelectedEvent.passMuTrigger = PreZPrimeTree->HLT_mu24_ivarmedium_L1MU14FCH || PreZPrimeTree->HLT_mu50_L1MU14FCH;

   if(PreZPrimeTree->runNumber >= 473235 && PreZPrimeTree->runNumber <= 486706) SelectedEvent.passMuTrigger = PreZPrimeTree->HLT_mu24_ivarmedium_L1MU14FCH || PreZPrimeTree->HLT_mu50_L1MU14FCH;
 }
 else{
   if(PreZPrimeTree->randomRunNumber >= 430536 && PreZPrimeTree->randomRunNumber <= 440613) SelectedEvent.passElTrigger = PreZPrimeTree->HLT_2e24_lhvloose_L12EM20VH;
   
   if(PreZPrimeTree->randomRunNumber >= 451094 && PreZPrimeTree->randomRunNumber <= 456749) SelectedEvent.passElTrigger = PreZPrimeTree->HLT_2e24_lhvloose_L12eEM24L;

   if(PreZPrimeTree->randomRunNumber >= 473235 && PreZPrimeTree->randomRunNumber <= 486706) SelectedEvent.passElTrigger = PreZPrimeTree->HLT_2e24_lhvloose_L12eEM24L;

   if(PreZPrimeTree->randomRunNumber >= 430536 && PreZPrimeTree->randomRunNumber <= 440613) SelectedEvent.passMuTrigger = PreZPrimeTree->HLT_mu24_ivarmedium_L1MU14FCH || PreZPrimeTree->HLT_mu50_L1MU14FCH;
   
   if(PreZPrimeTree->randomRunNumber >= 451094 && PreZPrimeTree->randomRunNumber <= 456749) SelectedEvent.passMuTrigger = PreZPrimeTree->HLT_mu24_ivarmedium_L1MU14FCH || PreZPrimeTree->HLT_mu50_L1MU14FCH;
   
   if(PreZPrimeTree->randomRunNumber >= 473235 && PreZPrimeTree->randomRunNumber <= 486706) SelectedEvent.passMuTrigger = PreZPrimeTree->HLT_mu24_ivarmedium_L1MU14FCH || PreZPrimeTree->HLT_mu50_L1MU14FCH;
 }


 /////////////////////////////////////////////////////////////////////////////////////////////////

 double Lumi = 0.0;
 if(PreZPrimeTree->runNumber == 284500.0){
   Lumi = 36.64674;
 }
 if(PreZPrimeTree->runNumber == 300000.0){
   Lumi = 44.6306;
 }
 if(PreZPrimeTree->runNumber == 310000.0){
   Lumi = 58.7916;
 }

 int nElectron = 0;
 int nTightElectron = 0;
 vector<int> ElectronIndex;

 int nMuon = 0;
 int nTightMuon = 0;
 vector<int> MuonIndex;

 nElectron = PreZPrimeTree->n_el;
 nMuon = PreZPrimeTree->n_mu;

 nTightElectron = PreZPrimeTree->n_signal_el;
 nTightMuon = PreZPrimeTree->n_signal_mu;

 if(!isTruthRun){

 if(nElectron >= 1 && nMuon == 0 && isElFakeEffRun){

   SelectedEvent.Lepton1.P4.SetPtEtaPhiM(PreZPrimeTree->lepton1_pt, PreZPrimeTree->lepton1_eta, PreZPrimeTree->lepton1_phi, PreZPrimeTree->lepton1_m);

   SelectedEvent.Lepton1.Flavor = 11;
   SelectedEvent.Lepton1.Charge = PreZPrimeTree->lepton1_charge;
   if(isLooseTree) SelectedEvent.Lepton1.isTight = !(PreZPrimeTree->lepton1_isIsoHighPtCaloOnly) && (PreZPrimeTree->lepton1_isIDTight);

   if(isLooseTree){
     SelectedEvent.Lepton1.RecoSF = PreZPrimeTree->lepton1_RecoWeight;
     SelectedEvent.Lepton1.IDSF = PreZPrimeTree->lepton1_IDTightWeight;
     SelectedEvent.Lepton1.LooseIDSF = PreZPrimeTree->lepton1_IDLooseWeight;
     SelectedEvent.Lepton1.IsoSF = PreZPrimeTree->lepton1_IsoHighPtCaloOnlyWeight;

     SelectedEvent.Lepton1.TightWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.IDSF * SelectedEvent.Lepton1.IsoSF;
     SelectedEvent.Lepton1.LooseWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.LooseIDSF * SelectedEvent.Lepton1.IsoSF;

     SelectedEvent.Lepton1.mediumID = PreZPrimeTree->lepton1_isIDMedium;
     SelectedEvent.Lepton1.looseID = !(PreZPrimeTree->lepton1_isIsoHighPtCaloOnly) && PreZPrimeTree->lepton1_isIDLoose;
   }

   SelectedEvent.Lepton1.z0 = PreZPrimeTree->lepton1_z0;
   SelectedEvent.Lepton1.d0Sig = PreZPrimeTree->lepton1_d0sig;

   SelectedEvent.eeChannel = false;
   SelectedEvent.mumuChannel = false;
   SelectedEvent.emuChannel = false;
   SelectedEvent.SingleElectron = true;

   if(nElectron == 2){
     SelectedEvent.Lepton2.P4.SetPtEtaPhiM(PreZPrimeTree->lepton2_pt, PreZPrimeTree->lepton2_eta, PreZPrimeTree->lepton2_phi, PreZPrimeTree->lepton2_m);

     SelectedEvent.Lepton2.Flavor = 11;
     SelectedEvent.Lepton2.Charge = PreZPrimeTree->lepton2_charge;
     if(isLooseTree) SelectedEvent.Lepton2.isTight = !(PreZPrimeTree->lepton2_isIsoHighPtCaloOnly) && (PreZPrimeTree->lepton2_isIDTight);
  
     if(isLooseTree){
       SelectedEvent.Lepton2.RecoSF = PreZPrimeTree->lepton2_RecoWeight;
       SelectedEvent.Lepton2.IDSF = PreZPrimeTree->lepton2_IDTightWeight;
       SelectedEvent.Lepton2.LooseIDSF = PreZPrimeTree->lepton2_IDLooseWeight;
       SelectedEvent.Lepton2.IsoSF = PreZPrimeTree->lepton2_IsoHighPtCaloOnlyWeight;

       SelectedEvent.Lepton2.TightWeight = SelectedEvent.Lepton2.RecoSF * SelectedEvent.Lepton2.IDSF * SelectedEvent.Lepton2.IsoSF;
       SelectedEvent.Lepton2.LooseWeight = SelectedEvent.Lepton2.RecoSF * SelectedEvent.Lepton2.LooseIDSF * SelectedEvent.Lepton2.IsoSF;

       SelectedEvent.Lepton2.mediumID = PreZPrimeTree->lepton2_isIDMedium;
       SelectedEvent.Lepton2.looseID = !(PreZPrimeTree->lepton2_isIsoHighPtCaloOnly) && PreZPrimeTree->lepton2_isIDLoose;
     }
  
     SelectedEvent.Lepton2.z0 = PreZPrimeTree->lepton2_z0;
     SelectedEvent.Lepton2.d0Sig = PreZPrimeTree->lepton2_d0sig;

     if(SelectedEvent.Lepton1.P4.Pt() < SelectedEvent.Lepton2.P4.Pt()){
       ZPrimeLepton Lepton_tmp = SelectedEvent.Lepton1;
       SelectedEvent.Lepton1 = SelectedEvent.Lepton2;
       SelectedEvent.Lepton2 = Lepton_tmp;

     }
   }

   if(isLooseTree){
     if(PreZPrimeTree->datasetNumber < 0){

       if(PreZPrimeTree->randomRunNumber >= 430536 && PreZPrimeTree->randomRunNumber <= 440613){
         if(SelectedEvent.Lepton1.P4.Pt() > 21.0 && SelectedEvent.Lepton1.P4.Pt() < 30.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e20_lhvloose_L1EM15VH * PreZPrimeTree->prescale_HLT_e20_lhvloose_L1EM15VH;
         else if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 40.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e30_lhvloose_L1EM22VHI * PreZPrimeTree->prescale_HLT_e30_lhvloose_L1EM22VHI;
         else if(SelectedEvent.Lepton1.P4.Pt() > 40.0 && SelectedEvent.Lepton1.P4.Pt() < 60.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e40_lhvloose_L1EM22VHI * PreZPrimeTree->prescale_HLT_e40_lhvloose_L1EM22VHI;
         else if(SelectedEvent.Lepton1.P4.Pt() > 60.0 && SelectedEvent.Lepton1.P4.Pt() < 80.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e60_lhvloose_L1EM22VHI * PreZPrimeTree->prescale_HLT_e60_lhvloose_L1EM22VHI;
         else if(SelectedEvent.Lepton1.P4.Pt() > 80.0 && SelectedEvent.Lepton1.P4.Pt() < 100.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e80_lhvloose_L1EM22VHI * PreZPrimeTree->prescale_HLT_e80_lhvloose_L1EM22VHI;
         else if(SelectedEvent.Lepton1.P4.Pt() > 100.0 && SelectedEvent.Lepton1.P4.Pt() < 120.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e100_lhvloose_L1EM22VHI * PreZPrimeTree->prescale_HLT_e100_lhvloose_L1EM22VHI;
         else if(SelectedEvent.Lepton1.P4.Pt() > 120.0 && SelectedEvent.Lepton1.P4.Pt() < 1e6) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e120_lhvloose_L1EM22VHI * PreZPrimeTree->prescale_HLT_e120_lhvloose_L1EM22VHI;
       }
       else if(PreZPrimeTree->runNumber >= 451094 && PreZPrimeTree->runNumber <= 456749){
         if(SelectedEvent.Lepton1.P4.Pt() > 21.0 && SelectedEvent.Lepton1.P4.Pt() < 30.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e20_lhvloose_L1eEM18L * PreZPrimeTree->prescale_HLT_e20_lhvloose_L1eEM18L;
         else if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 40.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e30_lhvloose_L1eEM28M * PreZPrimeTree->prescale_HLT_e30_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 40.0 && SelectedEvent.Lepton1.P4.Pt() < 60.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e40_lhvloose_L1eEM28M * PreZPrimeTree->prescale_HLT_e40_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 60.0 && SelectedEvent.Lepton1.P4.Pt() < 80.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e60_lhvloose_L1eEM28M * PreZPrimeTree->prescale_HLT_e60_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 80.0 && SelectedEvent.Lepton1.P4.Pt() < 100.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e80_lhvloose_L1eEM28M * PreZPrimeTree->prescale_HLT_e80_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 100.0 && SelectedEvent.Lepton1.P4.Pt() < 120.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e100_lhvloose_L1eEM28M * PreZPrimeTree->prescale_HLT_e100_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 120.0 && SelectedEvent.Lepton1.P4.Pt() < 1e6) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e120_lhvloose_L1eEM28M * PreZPrimeTree->prescale_HLT_e120_lhvloose_L1eEM28M;
       }
       else if(PreZPrimeTree->runNumber >= 473235 && PreZPrimeTree->runNumber <= 486706){
         if(SelectedEvent.Lepton1.P4.Pt() > 21.0 && SelectedEvent.Lepton1.P4.Pt() < 30.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e20_lhvloose_L1eEM18L * PreZPrimeTree->prescale_HLT_e20_lhvloose_L1eEM18L;
         else if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 40.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e30_lhvloose_L1eEM28M * PreZPrimeTree->prescale_HLT_e30_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 40.0 && SelectedEvent.Lepton1.P4.Pt() < 60.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e40_lhvloose_L1eEM28M * PreZPrimeTree->prescale_HLT_e40_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 60.0 && SelectedEvent.Lepton1.P4.Pt() < 80.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e60_lhvloose_L1eEM28M * PreZPrimeTree->prescale_HLT_e60_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 80.0 && SelectedEvent.Lepton1.P4.Pt() < 100.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e80_lhvloose_L1eEM28M * PreZPrimeTree->prescale_HLT_e80_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 100.0 && SelectedEvent.Lepton1.P4.Pt() < 120.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e100_lhvloose_L1eEM28M * PreZPrimeTree->prescale_HLT_e100_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 120.0 && SelectedEvent.Lepton1.P4.Pt() < 1e6) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e120_lhvloose_L1eEM28M * PreZPrimeTree->prescale_HLT_e120_lhvloose_L1eEM28M;
       }
     }
     else{
       if(PreZPrimeTree->randomRunNumber >= 430536 && PreZPrimeTree->randomRunNumber <= 440613){
         if(SelectedEvent.Lepton1.P4.Pt() > 21.0 && SelectedEvent.Lepton1.P4.Pt() < 30.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e20_lhvloose_L1EM15VH;
         else if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 40.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e30_lhvloose_L1EM22VHI;
         else if(SelectedEvent.Lepton1.P4.Pt() > 40.0 && SelectedEvent.Lepton1.P4.Pt() < 60.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e40_lhvloose_L1EM22VHI;
         else if(SelectedEvent.Lepton1.P4.Pt() > 60.0 && SelectedEvent.Lepton1.P4.Pt() < 80.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e60_lhvloose_L1EM22VHI;
         else if(SelectedEvent.Lepton1.P4.Pt() > 80.0 && SelectedEvent.Lepton1.P4.Pt() < 100.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e80_lhvloose_L1EM22VHI;
         else if(SelectedEvent.Lepton1.P4.Pt() > 100.0 && SelectedEvent.Lepton1.P4.Pt() < 120.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e100_lhvloose_L1EM22VHI;
         else if(SelectedEvent.Lepton1.P4.Pt() > 120.0 && SelectedEvent.Lepton1.P4.Pt() < 1e6) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e120_lhvloose_L1EM22VHI;
       }
       else if(PreZPrimeTree->randomRunNumber >= 451094 && PreZPrimeTree->randomRunNumber <= 456749){
         if(SelectedEvent.Lepton1.P4.Pt() > 21.0 && SelectedEvent.Lepton1.P4.Pt() < 30.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e20_lhvloose_L1eEM18L;
         else if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 40.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e30_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 40.0 && SelectedEvent.Lepton1.P4.Pt() < 60.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e40_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 60.0 && SelectedEvent.Lepton1.P4.Pt() < 80.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e60_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 80.0 && SelectedEvent.Lepton1.P4.Pt() < 100.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e80_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 100.0 && SelectedEvent.Lepton1.P4.Pt() < 120.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e100_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 120.0 && SelectedEvent.Lepton1.P4.Pt() < 1e6) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e120_lhvloose_L1eEM28M;
       }
       else if(PreZPrimeTree->randomRunNumber >= 473235 && PreZPrimeTree->randomRunNumber <= 486706){
         if(SelectedEvent.Lepton1.P4.Pt() > 21.0 && SelectedEvent.Lepton1.P4.Pt() < 30.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e20_lhvloose_L1eEM18L;
         else if(SelectedEvent.Lepton1.P4.Pt() > 30.0 && SelectedEvent.Lepton1.P4.Pt() < 40.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e30_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 40.0 && SelectedEvent.Lepton1.P4.Pt() < 60.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e40_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 60.0 && SelectedEvent.Lepton1.P4.Pt() < 80.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e60_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 80.0 && SelectedEvent.Lepton1.P4.Pt() < 100.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e80_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 100.0 && SelectedEvent.Lepton1.P4.Pt() < 120.0) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e100_lhvloose_L1eEM28M;
         else if(SelectedEvent.Lepton1.P4.Pt() > 120.0 && SelectedEvent.Lepton1.P4.Pt() < 1e6) SelectedEvent.Lepton1.PrescaleFactor = PreZPrimeTree->HLT_e120_lhvloose_L1eEM28M;
       }
     }

   }


 }

 else if(nElectron == 2 && nTightMuon == 0){
   SelectedEvent.Lepton1.P4.SetPtEtaPhiM(PreZPrimeTree->lepton1_pt, PreZPrimeTree->lepton1_eta, PreZPrimeTree->lepton1_phi, PreZPrimeTree->lepton1_m);
   SelectedEvent.Lepton2.P4.SetPtEtaPhiM(PreZPrimeTree->lepton2_pt, PreZPrimeTree->lepton2_eta, PreZPrimeTree->lepton2_phi, PreZPrimeTree->lepton2_m);

   SelectedEvent.Lepton1.Flavor = 11;
   SelectedEvent.Lepton1.Charge = PreZPrimeTree->lepton1_charge;

   if(isLooseTree){
     SelectedEvent.Lepton1.isTight = (PreZPrimeTree->lepton1_isIDTight);
     SelectedEvent.Lepton1.looseID = (PreZPrimeTree->lepton1_isIDLoose);

     if(isElRealEffRun){
       SelectedEvent.Lepton1.isTight = (PreZPrimeTree->lepton1_isIDTight) && (PreZPrimeTree->lepton1_isIsoHighPtCaloOnly);
       SelectedEvent.Lepton1.looseID = (PreZPrimeTree->lepton1_isIDLoose) && (PreZPrimeTree->lepton1_isIsoHighPtCaloOnly);
     }

     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.RecoSF = PreZPrimeTree->lepton1_RecoWeight;
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.IDSF = PreZPrimeTree->lepton1_IDTightWeight;
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.LooseIDSF = PreZPrimeTree->lepton1_IDLooseWeight;
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.IsoSF = PreZPrimeTree->lepton1_IsoHighPtCaloOnlyWeight;

     SelectedEvent.Lepton1.TightWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.IDSF * SelectedEvent.Lepton1.IsoSF;
     SelectedEvent.Lepton1.LooseWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.LooseIDSF * SelectedEvent.Lepton1.IsoSF;

     SelectedEvent.Lepton1.mediumID = PreZPrimeTree->lepton1_isIDMedium;

     SelectedEvent.Lepton1.FCTightIso = PreZPrimeTree->lepton1_isIsoHighPtCaloOnly;
   }

   SelectedEvent.Lepton1.z0 = PreZPrimeTree->lepton1_z0;
   SelectedEvent.Lepton1.d0Sig = PreZPrimeTree->lepton1_d0sig;

   SelectedEvent.Lepton2.Flavor = 11;
   SelectedEvent.Lepton2.Charge = PreZPrimeTree->lepton2_charge;

   if(isLooseTree){
     SelectedEvent.Lepton2.isTight = (PreZPrimeTree->lepton2_isIDTight);
     SelectedEvent.Lepton2.looseID = (PreZPrimeTree->lepton2_isIDLoose);

     if(isElRealEffRun){
       SelectedEvent.Lepton1.isTight = (PreZPrimeTree->lepton1_isIDTight) && (PreZPrimeTree->lepton1_isIsoHighPtCaloOnly);
       SelectedEvent.Lepton1.looseID = (PreZPrimeTree->lepton1_isIDLoose) && (PreZPrimeTree->lepton1_isIsoHighPtCaloOnly);
     }

     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.RecoSF = PreZPrimeTree->lepton2_RecoWeight;
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.IDSF = PreZPrimeTree->lepton2_IDTightWeight;
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.LooseIDSF = PreZPrimeTree->lepton2_IDLooseWeight;
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.IsoSF = PreZPrimeTree->lepton2_IsoHighPtCaloOnlyWeight;
     
     SelectedEvent.Lepton2.TightWeight = SelectedEvent.Lepton2.RecoSF * SelectedEvent.Lepton2.IDSF * SelectedEvent.Lepton2.IsoSF;
     SelectedEvent.Lepton2.LooseWeight = SelectedEvent.Lepton2.RecoSF * SelectedEvent.Lepton2.LooseIDSF * SelectedEvent.Lepton2.IsoSF;
     
     SelectedEvent.Lepton2.mediumID = PreZPrimeTree->lepton2_isIDMedium;

     SelectedEvent.Lepton2.FCTightIso = PreZPrimeTree->lepton2_isIsoHighPtCaloOnly;
   }

   SelectedEvent.Lepton2.z0 = PreZPrimeTree->lepton2_z0;
   SelectedEvent.Lepton2.d0Sig = PreZPrimeTree->lepton2_d0sig;

   SelectedEvent.eeChannel = true;
   SelectedEvent.mumuChannel = false;
   SelectedEvent.emuChannel = false;

   if(PreZPrimeTree->dilepton_m < 130.0) return false;

   if(doMuFakeBkg) return false;
 }

/*
 else if(nElectron == 0 && nMuon == 2 && PreZPrimeTree->mumuSelection){
   SelectedEvent.Lepton1.P4.SetPtEtaPhiE(PreZPrimeTree->mu_pt->at(MuonIndex.at(0)) / 1000.0, PreZPrimeTree->mu_eta->at(MuonIndex.at(0)), PreZPrimeTree->mu_phi->at(MuonIndex.at(0)), PreZPrimeTree->mu_e->at(MuonIndex.at(0)) / 1000.0);
   SelectedEvent.Lepton2.P4.SetPtEtaPhiE(PreZPrimeTree->mu_pt->at(MuonIndex.at(1)) / 1000.0, PreZPrimeTree->mu_eta->at(MuonIndex.at(1)), PreZPrimeTree->mu_phi->at(MuonIndex.at(1)), PreZPrimeTree->mu_e->at(MuonIndex.at(1)) / 1000.0);

   SelectedEvent.Lepton1.Flavor = 13;
   SelectedEvent.Lepton1.Charge = PreZPrimeTree->mu_charge->at(MuonIndex.at(0));
   if(isZPrimeinclusiveWP){
     if(isLooseTree) SelectedEvent.Lepton1.isTight = PreZPrimeTree->mu_isTight->at(MuonIndex.at(0));// For inclusive ZPrime
   }
   else{
     if(isLooseTree) SelectedEvent.Lepton1.isTight = PreZPrimeTree->mu_isHighPt->at(MuonIndex.at(0)) * PreZPrimeTree->mu_isolation_TightTrackOnly_VarRad->at(MuonIndex.at(0));// For ZPrime+b
   }

   if(isLooseTree){
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.TTVASF = PreZPrimeTree->mu_SF_TTVA->at(MuonIndex.at(0));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.IDSF = PreZPrimeTree->mu_SF_ID_HighPt->at(MuonIndex.at(0));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.LooseIDSF = PreZPrimeTree->mu_SF_ID_HighPt->at(MuonIndex.at(0));

     if(isZPrimeinclusiveWP){
       if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.IsoSF = PreZPrimeTree->mu_SF_Iso_FCTightTrackOnly_FixedRad->at(MuonIndex.at(0));// For inclusive ZPrime
     }
     else{
       if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton1.IsoSF = PreZPrimeTree->mu_SF_Iso_TightTrackOnly_VarRad->at(MuonIndex.at(0));// For ZPrime+b
     }

     SelectedEvent.Lepton1.TightWeight = SelectedEvent.Lepton1.TTVASF * SelectedEvent.Lepton1.IDSF * SelectedEvent.Lepton1.IsoSF;
     SelectedEvent.Lepton1.LooseWeight = SelectedEvent.Lepton1.TTVASF * SelectedEvent.Lepton1.LooseIDSF;

     SelectedEvent.Lepton1.looseID = PreZPrimeTree->mu_isHighPt->at(MuonIndex.at(0));// to be consistent with electron
   }

   SelectedEvent.Lepton1.z0 = PreZPrimeTree->mu_delta_z0_sintheta->at(MuonIndex.at(0));
   SelectedEvent.Lepton1.d0Sig = PreZPrimeTree->mu_d0sig->at(MuonIndex.at(0));

   SelectedEvent.Lepton2.Flavor = 13;
   SelectedEvent.Lepton2.Charge = PreZPrimeTree->mu_charge->at(MuonIndex.at(1));

   if(isZPrimeinclusiveWP){
     if(isLooseTree) SelectedEvent.Lepton2.isTight = PreZPrimeTree->mu_isTight->at(MuonIndex.at(1));// For inclusive ZPrime
   }
   else{
     if(isLooseTree) SelectedEvent.Lepton2.isTight = PreZPrimeTree->mu_isHighPt->at(MuonIndex.at(1)) * PreZPrimeTree->mu_isolation_TightTrackOnly_VarRad->at(MuonIndex.at(1));// For ZPrime+b
   }

   if(isLooseTree){
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.TTVASF = PreZPrimeTree->mu_SF_TTVA->at(MuonIndex.at(1));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.IDSF = PreZPrimeTree->mu_SF_ID_HighPt->at(MuonIndex.at(1));
     if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.LooseIDSF = PreZPrimeTree->mu_SF_ID_HighPt->at(MuonIndex.at(1));

     if(isZPrimeinclusiveWP){
       if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.IsoSF = PreZPrimeTree->mu_SF_Iso_FCTightTrackOnly_FixedRad->at(MuonIndex.at(1));// For inclusive ZPrime
     }
     else{
       if(isElRealEffRun || isMuRealEffRun || isUnfoldRun) SelectedEvent.Lepton2.IsoSF = PreZPrimeTree->mu_SF_Iso_TightTrackOnly_VarRad->at(MuonIndex.at(1));// For ZPrime+b
     }

     SelectedEvent.Lepton2.TightWeight = SelectedEvent.Lepton2.TTVASF * SelectedEvent.Lepton2.IDSF * SelectedEvent.Lepton2.IsoSF;
     SelectedEvent.Lepton2.LooseWeight = SelectedEvent.Lepton2.TTVASF * SelectedEvent.Lepton2.LooseIDSF;

     SelectedEvent.Lepton2.looseID = PreZPrimeTree->mu_isHighPt->at(MuonIndex.at(1));// to be consistent with electron
   }

   SelectedEvent.Lepton2.z0 = PreZPrimeTree->mu_delta_z0_sintheta->at(MuonIndex.at(1));
   SelectedEvent.Lepton2.d0Sig = PreZPrimeTree->mu_d0sig->at(MuonIndex.at(1));

   SelectedEvent.eeChannel = false;
   SelectedEvent.mumuChannel = true;
   SelectedEvent.emuChannel = false;

   if(doElFakeBkg) return false;
 }
 else if(nElectron == 1 && nMuon == 1 && PreZPrimeTree->emu){
   SelectedEvent.Lepton1.P4.SetPtEtaPhiE(PreZPrimeTree->el_pt->at(ElectronIndex.at(0)) / 1000.0, PreZPrimeTree->el_eta->at(ElectronIndex.at(0)), PreZPrimeTree->el_phi->at(ElectronIndex.at(0)), PreZPrimeTree->el_e->at(ElectronIndex.at(0)) / 1000.0);
   SelectedEvent.Lepton2.P4.SetPtEtaPhiE(PreZPrimeTree->mu_pt->at(MuonIndex.at(0)) / 1000.0, PreZPrimeTree->mu_eta->at(MuonIndex.at(0)), PreZPrimeTree->mu_phi->at(MuonIndex.at(0)), PreZPrimeTree->mu_e->at(MuonIndex.at(0)) / 1000.0);

   SelectedEvent.Lepton1.Flavor = 11;
   SelectedEvent.Lepton1.Charge = PreZPrimeTree->el_charge->at(ElectronIndex.at(0));
   if(isLooseTree) SelectedEvent.Lepton1.isTight = PreZPrimeTree->el_isTight->at(ElectronIndex.at(0));

   if(isLooseTree){
     if(isFakeEffRun) SelectedEvent.Lepton1.RecoSF = PreZPrimeTree->el_SF_Reco_Corr->at(ElectronIndex.at(0));
     if(isFakeEffRun) SelectedEvent.Lepton1.IDSF = PreZPrimeTree->el_SF_ID_MediumLH->at(ElectronIndex.at(0));
     if(isFakeEffRun) SelectedEvent.Lepton1.LooseIDSF = PreZPrimeTree->el_SF_ID_LooseAndBLayerLH->at(ElectronIndex.at(0));
     if(isFakeEffRun) SelectedEvent.Lepton1.IsoSF = PreZPrimeTree->el_SF_Iso_FCTight->at(ElectronIndex.at(0));

     SelectedEvent.Lepton1.TightWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.IDSF * SelectedEvent.Lepton1.IsoSF;
     SelectedEvent.Lepton1.LooseWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.LooseIDSF;
   }

   SelectedEvent.Lepton1.z0 = PreZPrimeTree->el_delta_z0_sintheta->at(ElectronIndex.at(0));
   SelectedEvent.Lepton1.d0Sig = PreZPrimeTree->el_d0sig->at(ElectronIndex.at(0));
 
   SelectedEvent.Lepton2.Flavor = 13;
   SelectedEvent.Lepton2.Charge = PreZPrimeTree->mu_charge->at(MuonIndex.at(0));
   if(isLooseTree) SelectedEvent.Lepton2.isTight = PreZPrimeTree->mu_isTight->at(MuonIndex.at(0));

   if(isLooseTree){
     if(isFakeEffRun) SelectedEvent.Lepton2.TTVASF = PreZPrimeTree->mu_SF_TTVA->at(MuonIndex.at(0));
     if(isFakeEffRun) SelectedEvent.Lepton2.IDSF = PreZPrimeTree->mu_SF_ID_HighPt->at(MuonIndex.at(0));
     if(isFakeEffRun) SelectedEvent.Lepton2.LooseIDSF = PreZPrimeTree->mu_SF_ID_Loose->at(MuonIndex.at(0));
     if(isFakeEffRun) SelectedEvent.Lepton2.IsoSF = PreZPrimeTree->mu_SF_Iso_FCTightTrackOnly_FixedRad->at(MuonIndex.at(0));

     SelectedEvent.Lepton2.TightWeight = SelectedEvent.Lepton2.TTVASF * SelectedEvent.Lepton2.IDSF * SelectedEvent.Lepton2.IsoSF;
     SelectedEvent.Lepton2.LooseWeight = SelectedEvent.Lepton2.TTVASF * SelectedEvent.Lepton2.LooseIDSF;
   }

   SelectedEvent.Lepton2.z0 = PreZPrimeTree->mu_delta_z0_sintheta->at(MuonIndex.at(0));
   SelectedEvent.Lepton2.d0Sig = PreZPrimeTree->mu_d0sig->at(MuonIndex.at(0));

   SelectedEvent.eeChannel = false;
   SelectedEvent.mumuChannel = false;
   SelectedEvent.emuChannel = true;
 }
 else if(nElectron == 2 && nMuon == 1 && PreZPrimeTree->eeSelection_withmuon){
   SelectedEvent.Lepton1.P4.SetPtEtaPhiE(PreZPrimeTree->el_pt->at(ElectronIndex.at(0)) / 1000.0, PreZPrimeTree->el_eta->at(ElectronIndex.at(0)), PreZPrimeTree->el_phi->at(ElectronIndex.at(0)), PreZPrimeTree->el_e->at(ElectronIndex.at(0)) / 1000.0);
   SelectedEvent.Lepton2.P4.SetPtEtaPhiE(PreZPrimeTree->el_pt->at(ElectronIndex.at(1)) / 1000.0, PreZPrimeTree->el_eta->at(ElectronIndex.at(1)), PreZPrimeTree->el_phi->at(ElectronIndex.at(1)), PreZPrimeTree->el_e->at(ElectronIndex.at(1)) / 1000.0);

   SelectedEvent.Lepton1.Flavor = 11;
   SelectedEvent.Lepton1.Charge = PreZPrimeTree->el_charge->at(ElectronIndex.at(0));
   if(isLooseTree) SelectedEvent.Lepton1.isTight = PreZPrimeTree->el_isTight->at(ElectronIndex.at(0));

   if(isLooseTree){
     if(isMuFakeEffRun) SelectedEvent.Lepton1.RecoSF = PreZPrimeTree->el_SF_Reco_Corr->at(ElectronIndex.at(0));
     if(isMuFakeEffRun) SelectedEvent.Lepton1.IDSF = PreZPrimeTree->el_SF_ID_MediumLH->at(ElectronIndex.at(0));
     if(isMuFakeEffRun) SelectedEvent.Lepton1.LooseIDSF = PreZPrimeTree->el_SF_ID_LooseAndBLayerLH->at(ElectronIndex.at(0));
     if(isMuFakeEffRun) SelectedEvent.Lepton1.IsoSF = PreZPrimeTree->el_SF_Iso_FCTight->at(ElectronIndex.at(0));

     SelectedEvent.Lepton1.TightWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.IDSF * SelectedEvent.Lepton1.IsoSF;
     SelectedEvent.Lepton1.LooseWeight = SelectedEvent.Lepton1.RecoSF * SelectedEvent.Lepton1.LooseIDSF;

     SelectedEvent.Lepton1.mediumID = PreZPrimeTree->el_isElMedium->at(ElectronIndex.at(0));
     SelectedEvent.Lepton1.looseID = PreZPrimeTree->el_isElLoose->at(ElectronIndex.at(0));
   }

   SelectedEvent.Lepton1.z0 = PreZPrimeTree->el_delta_z0_sintheta->at(ElectronIndex.at(0));
   SelectedEvent.Lepton1.d0Sig = PreZPrimeTree->el_d0sig->at(ElectronIndex.at(0));

   SelectedEvent.Lepton2.Flavor = 11;
   SelectedEvent.Lepton2.Charge = PreZPrimeTree->el_charge->at(ElectronIndex.at(1));
   if(isLooseTree) SelectedEvent.Lepton2.isTight = PreZPrimeTree->el_isTight->at(ElectronIndex.at(1));

   if(isLooseTree){
     if(isMuFakeEffRun) SelectedEvent.Lepton2.RecoSF = PreZPrimeTree->el_SF_Reco_Corr->at(ElectronIndex.at(1));
     if(isMuFakeEffRun) SelectedEvent.Lepton2.IDSF = PreZPrimeTree->el_SF_ID_MediumLH->at(ElectronIndex.at(1));
     if(isMuFakeEffRun) SelectedEvent.Lepton2.LooseIDSF = PreZPrimeTree->el_SF_ID_LooseAndBLayerLH->at(ElectronIndex.at(1));
     if(isMuFakeEffRun) SelectedEvent.Lepton2.IsoSF = PreZPrimeTree->el_SF_Iso_FCTight->at(ElectronIndex.at(1));

     SelectedEvent.Lepton2.TightWeight = SelectedEvent.Lepton2.RecoSF * SelectedEvent.Lepton2.IDSF * SelectedEvent.Lepton2.IsoSF;
     SelectedEvent.Lepton2.LooseWeight = SelectedEvent.Lepton2.RecoSF * SelectedEvent.Lepton2.LooseIDSF;

     SelectedEvent.Lepton2.mediumID = PreZPrimeTree->el_isElMedium->at(ElectronIndex.at(1));
     SelectedEvent.Lepton2.looseID = PreZPrimeTree->el_isElLoose->at(ElectronIndex.at(1));
   }

   SelectedEvent.Lepton2.z0 = PreZPrimeTree->el_delta_z0_sintheta->at(ElectronIndex.at(1));
   SelectedEvent.Lepton2.d0Sig = PreZPrimeTree->el_d0sig->at(ElectronIndex.at(1));

   SelectedEvent.Lepton3.P4.SetPtEtaPhiE(PreZPrimeTree->mu_pt->at(MuonIndex.at(0)) / 1000.0, PreZPrimeTree->mu_eta->at(MuonIndex.at(0)), PreZPrimeTree->mu_phi->at(MuonIndex.at(0)), PreZPrimeTree->mu_e->at(MuonIndex.at(0)) / 1000.0);
   SelectedEvent.Lepton3.Flavor = 13;
   SelectedEvent.Lepton3.Charge = PreZPrimeTree->mu_charge->at(MuonIndex.at(0));

   if(isZPrimeinclusiveWP){
     if(isLooseTree) SelectedEvent.Lepton3.isTight = PreZPrimeTree->mu_isTight->at(MuonIndex.at(0));// For inclusive ZPrime
   }
   else{
     if(isLooseTree) SelectedEvent.Lepton3.isTight = PreZPrimeTree->mu_isHighPt->at(MuonIndex.at(0)) * PreZPrimeTree->mu_isolation_TightTrackOnly_VarRad->at(MuonIndex.at(0));// For ZPrime+b
   }

   if(isLooseTree){
     if(isMuFakeEffRun) SelectedEvent.Lepton3.TTVASF = PreZPrimeTree->mu_SF_TTVA->at(MuonIndex.at(0));
     if(isMuFakeEffRun) SelectedEvent.Lepton3.IDSF = PreZPrimeTree->mu_SF_ID_HighPt->at(MuonIndex.at(0));
     if(isMuFakeEffRun) SelectedEvent.Lepton3.LooseIDSF = PreZPrimeTree->mu_SF_ID_HighPt->at(MuonIndex.at(0));

     if(isZPrimeinclusiveWP){
       if(isMuFakeEffRun) SelectedEvent.Lepton3.IsoSF = PreZPrimeTree->mu_SF_Iso_FCTightTrackOnly_FixedRad->at(MuonIndex.at(0));// For inclusive ZPrime
     }
     else{
       if(isMuFakeEffRun) SelectedEvent.Lepton3.IsoSF = PreZPrimeTree->mu_SF_Iso_TightTrackOnly_VarRad->at(MuonIndex.at(0));// For ZPrime+b
     }

     SelectedEvent.Lepton3.TightWeight = SelectedEvent.Lepton3.TTVASF * SelectedEvent.Lepton3.IDSF * SelectedEvent.Lepton3.IsoSF;
     SelectedEvent.Lepton3.LooseWeight = SelectedEvent.Lepton3.TTVASF * SelectedEvent.Lepton3.LooseIDSF;

     SelectedEvent.Lepton3.looseID = PreZPrimeTree->mu_isHighPt->at(MuonIndex.at(0));// to be consistent with electron
   }

   SelectedEvent.Lepton3.z0 = PreZPrimeTree->mu_delta_z0_sintheta->at(MuonIndex.at(0));
   SelectedEvent.Lepton3.d0Sig = PreZPrimeTree->mu_d0sig->at(MuonIndex.at(0));

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
*/

 if(isElRealEffRun || isMuRealEffRun){
   if(SelectedEvent.Lepton1.Charge * SelectedEvent.Lepton2.Charge > 0) return false;
 }

// if(SelectedEvent.Lepton1.P4.Pt() < SelectedEvent.Lepton2.P4.Pt()){
//   ZPrimeLepton Lepton_tmp = SelectedEvent.Lepton1;
//   SelectedEvent.Lepton1 = SelectedEvent.Lepton2;
//   SelectedEvent.Lepton2 = Lepton_tmp;
// }

 if(SelectedEvent.eeChannel){
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

 ///////////////////////////////////////////////////////////////////////

 SelectedEvent.RunNumber = PreZPrimeTree->runNumber;
 SelectedEvent.RandomRunNumber = PreZPrimeTree->randomRunNumber;
 SelectedEvent.EventNumber = PreZPrimeTree->eventNumber;
 SelectedEvent.mcChannelNumber = PreZPrimeTree->datasetNumber;
 SelectedEvent.RecoDilRapidity = Propagator.Rapidity();
 SelectedEvent.RecoDilPhi = Propagator.Phi();
 SelectedEvent.RecoDilMass = Propagator.M();
 SelectedEvent.RecoPseudoDilMass = -999.0;
 SelectedEvent.RecoDilPt = Propagator.Pt();
 SelectedEvent.RecoPhiStar = calculate_phi_eta(Lepton, Antilepton);
 SelectedEvent.RecoCosThetaStar = calculate_theta(Propagator, Lepton, Antilepton) * Propagator.Rapidity() / fabs(Propagator.Rapidity());

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
 SelectedEvent.LeptonSFWeight = PreZPrimeTree->weight_lepton;
 SelectedEvent.PileupWeight = PreZPrimeTree->weight_pileup;

 SelectedEvent.TriggerSF = PreZPrimeTree->weight_dileptonTrigSF;
 if(SelectedEvent.SingleElectron) SelectedEvent.TriggerSF = 1.0;

 SelectedEvent.n_Bjets = -999;
 SelectedEvent.MET_Et = PreZPrimeTree->metEle;
 SelectedEvent.Lepton1_z0 = SelectedEvent.Lepton1.z0;
 SelectedEvent.Lepton2_z0 = SelectedEvent.Lepton2.z0;
 SelectedEvent.Lepton3_z0 = SelectedEvent.Lepton3.z0;
 SelectedEvent.Lepton1_d0sig = SelectedEvent.Lepton1.d0Sig;
 SelectedEvent.Lepton2_d0sig = SelectedEvent.Lepton2.d0Sig;
 SelectedEvent.Lepton3_d0sig = SelectedEvent.Lepton3.d0Sig;
 SelectedEvent.Mu = PreZPrimeTree->averageInteractionsPerCrossing;
 SelectedEvent.MuActual = PreZPrimeTree->actualInteractionsPerCrossing;
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
 SelectedEvent.Lepton1_isTight = SelectedEvent.Lepton1.isTight;
 SelectedEvent.Lepton2_isTight = SelectedEvent.Lepton2.isTight;
 SelectedEvent.Lepton3_isTight = SelectedEvent.Lepton3.isTight;
 SelectedEvent.Lepton1_passIso = SelectedEvent.Lepton1.FCTightIso;
 SelectedEvent.Lepton2_passIso = SelectedEvent.Lepton2.FCTightIso;
 SelectedEvent.Lepton1_IsoWeight = SelectedEvent.Lepton1.IsoSF;
 SelectedEvent.Lepton2_IsoWeight = SelectedEvent.Lepton2.IsoSF;
 SelectedEvent.Lepton1_PrescaleFactor = SelectedEvent.Lepton1.PrescaleFactor;
 SelectedEvent.Lepton2_PrescaleFactor = SelectedEvent.Lepton2.PrescaleFactor;

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

 SelectedEvent.TotalWeight = PreZPrimeTree->weight_gen
                           * PreZPrimeTree->weight_lumi
                           * PreZPrimeTree->mcEventWeight
                           * PreZPrimeTree->weight_norm
                           * PreZPrimeTree->weight_lepton
                           * PreZPrimeTree->weight_dileptonTrigSF
                           * PreZPrimeTree->weight_pileup
                           * PreZPrimeTree->beamSpotWeight;

 if(isLooseTree){
   if(SelectedEvent.eeChannel || SelectedEvent.mumuChannel){
     SelectedEvent.TotalWeightLoose = PreZPrimeTree->weight_gen
                                    * PreZPrimeTree->weight_lumi
                                    * PreZPrimeTree->mcEventWeight
                                    * PreZPrimeTree->weight_norm
                                    * PreZPrimeTree->weight_dileptonTrigSF
                                    * PreZPrimeTree->weight_pileup
                                    * PreZPrimeTree->beamSpotWeight;

     SelectedEvent.TotalWeight = PreZPrimeTree->weight_gen
                               * PreZPrimeTree->weight_lumi
                               * PreZPrimeTree->mcEventWeight
                               * PreZPrimeTree->weight_norm
                               * PreZPrimeTree->weight_dileptonTrigSF
                               * PreZPrimeTree->weight_pileup
                               * PreZPrimeTree->beamSpotWeight;
   }
   else if(SelectedEvent.SingleElectron){
     SelectedEvent.TotalWeightLoose = PreZPrimeTree->weight_gen
                                    * PreZPrimeTree->weight_lumi
                                    * PreZPrimeTree->mcEventWeight
                                    * PreZPrimeTree->weight_norm
                                    * PreZPrimeTree->weight_pileup
                                    * PreZPrimeTree->beamSpotWeight;
   }
 }

 if(isData){
   SelectedEvent.TotalWeightLoose = 1.0;
   SelectedEvent.TotalWeight = 1.0;
 }

 if(SelectedEvent.eeChannel) SelectedEvent.TotalWeightLoose = SelectedEvent.TotalWeightLoose * SelectedEvent.passElTrigger;
 if(SelectedEvent.mumuChannel) SelectedEvent.TotalWeightLoose = SelectedEvent.TotalWeightLoose * SelectedEvent.passMuTrigger;

 if(SelectedEvent.eeChannel) SelectedEvent.TotalWeight = SelectedEvent.TotalWeight * SelectedEvent.passElTrigger;
 if(SelectedEvent.mumuChannel) SelectedEvent.TotalWeight = SelectedEvent.TotalWeight * SelectedEvent.passMuTrigger;

 if(isLooseTree && !isElFakeEffRun){
   SelectedEvent.TotalWeight = SelectedEvent.TotalWeight
                             * SelectedEvent.Lepton1_TightWeight
                             * SelectedEvent.Lepton2_TightWeight
                             * SelectedEvent.Lepton1_isTight
                             * SelectedEvent.Lepton2_isTight
                             * PreZPrimeTree->lepton1_isIsoHighPtCaloOnly
                             * PreZPrimeTree->lepton2_isIsoHighPtCaloOnly;
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
 }


 ZPrimeTree->v_DFCommonJets_eventClean_LooseBad.clear();
 ZPrimeTree->v_jet_ConeTruthLabelID.clear();
 ZPrimeTree->v_jet_E.clear();
 ZPrimeTree->v_jet_Jvt.clear();
 ZPrimeTree->v_jet_PartonTruthLabelID.clear();
 ZPrimeTree->v_jet_btag.clear();
 ZPrimeTree->v_jet_btag_score.clear();
 ZPrimeTree->v_jet_btag_sf.clear();
 ZPrimeTree->v_jet_eta.clear();
 ZPrimeTree->v_jet_isJvtHS.clear();
 ZPrimeTree->v_jet_phi.clear();
 ZPrimeTree->v_jet_pt.clear();
 ZPrimeTree->v_truth_jet_ConeTruthLabelID.clear();
 ZPrimeTree->v_truth_jet_E.clear();
 ZPrimeTree->v_truth_jet_Jvt.clear();
 ZPrimeTree->v_truth_jet_PartonTruthLabelID.clear();
 ZPrimeTree->v_truth_jet_eta.clear();
 ZPrimeTree->v_truth_jet_phi.clear();
 ZPrimeTree->v_truth_jet_pt.clear();

 for(int i = 0; i < PreZPrimeTree->DFCommonJets_eventClean_LooseBad->size(); i++) {ZPrimeTree->v_DFCommonJets_eventClean_LooseBad.push_back(PreZPrimeTree->DFCommonJets_eventClean_LooseBad->at(i));}
 for(int i = 0; i < PreZPrimeTree->jet_ConeTruthLabelID->size(); i++)             {ZPrimeTree->v_jet_ConeTruthLabelID.push_back(            PreZPrimeTree->jet_ConeTruthLabelID->at(i));}
 for(int i = 0; i < PreZPrimeTree->jet_E->size(); i++)                            {ZPrimeTree->v_jet_E.push_back(                           PreZPrimeTree->jet_E->at(i));}
 for(int i = 0; i < PreZPrimeTree->jet_Jvt->size(); i++)                          {ZPrimeTree->v_jet_Jvt.push_back(                         PreZPrimeTree->jet_Jvt->at(i));}
 for(int i = 0; i < PreZPrimeTree->jet_PartonTruthLabelID->size(); i++)           {ZPrimeTree->v_jet_PartonTruthLabelID.push_back(          PreZPrimeTree->jet_PartonTruthLabelID->at(i));}
 for(int i = 0; i < PreZPrimeTree->jet_btag->size(); i++)                         {ZPrimeTree->v_jet_btag.push_back(                        PreZPrimeTree->jet_btag->at(i));}
 for(int i = 0; i < PreZPrimeTree->jet_btag_score->size(); i++)                   {ZPrimeTree->v_jet_btag_score.push_back(                  PreZPrimeTree->jet_btag_score->at(i));}
 for(int i = 0; i < PreZPrimeTree->jet_btag_sf->size(); i++)                      {ZPrimeTree->v_jet_btag_sf.push_back(                     PreZPrimeTree->jet_btag_sf->at(i));}
 for(int i = 0; i < PreZPrimeTree->jet_eta->size(); i++)                          {ZPrimeTree->v_jet_eta.push_back(                         PreZPrimeTree->jet_eta->at(i));}
 for(int i = 0; i < PreZPrimeTree->jet_isJvtHS->size(); i++)                      {ZPrimeTree->v_jet_isJvtHS.push_back(                     PreZPrimeTree->jet_isJvtHS->at(i));}
 for(int i = 0; i < PreZPrimeTree->jet_phi->size(); i++)                          {ZPrimeTree->v_jet_phi.push_back(                         PreZPrimeTree->jet_phi->at(i));}
 for(int i = 0; i < PreZPrimeTree->jet_pt->size(); i++)                           {ZPrimeTree->v_jet_pt.push_back(                          PreZPrimeTree->jet_pt->at(i));}

 if(!isElFakeEffRun){
   for(int i = 0; i < PreZPrimeTree->truth_jet_ConeTruthLabelID->size(); i++)       {ZPrimeTree->v_truth_jet_ConeTruthLabelID.push_back(      PreZPrimeTree->truth_jet_ConeTruthLabelID->at(i));}
   for(int i = 0; i < PreZPrimeTree->truth_jet_E->size(); i++)                      {ZPrimeTree->v_truth_jet_E.push_back(                     PreZPrimeTree->truth_jet_E->at(i));}
   for(int i = 0; i < PreZPrimeTree->truth_jet_Jvt->size(); i++)                    {ZPrimeTree->v_truth_jet_Jvt.push_back(                   PreZPrimeTree->truth_jet_Jvt->at(i));}
   for(int i = 0; i < PreZPrimeTree->truth_jet_PartonTruthLabelID->size(); i++)     {ZPrimeTree->v_truth_jet_PartonTruthLabelID.push_back(    PreZPrimeTree->truth_jet_PartonTruthLabelID->at(i));}
   for(int i = 0; i < PreZPrimeTree->truth_jet_eta->size(); i++)                    {ZPrimeTree->v_truth_jet_eta.push_back(                   PreZPrimeTree->truth_jet_eta->at(i));}
   for(int i = 0; i < PreZPrimeTree->truth_jet_phi->size(); i++)                    {ZPrimeTree->v_truth_jet_phi.push_back(                   PreZPrimeTree->truth_jet_phi->at(i));}
   for(int i = 0; i < PreZPrimeTree->truth_jet_pt->size(); i++)                     {ZPrimeTree->v_truth_jet_pt.push_back(                    PreZPrimeTree->truth_jet_pt->at(i));}
 }

 ZPrimeTree->weight_norm =                                PreZPrimeTree->weight_norm;
 ZPrimeTree->weight_lumi =                                PreZPrimeTree->weight_lumi;
 ZPrimeTree->runNumber =                                  PreZPrimeTree->runNumber;
 ZPrimeTree->eventNumber =                                PreZPrimeTree->eventNumber;
 ZPrimeTree->lumiBlock =                                  PreZPrimeTree->lumiBlock;
 ZPrimeTree->coreFlags =                                  PreZPrimeTree->coreFlags;
 ZPrimeTree->bcid =                                       PreZPrimeTree->bcid;
 ZPrimeTree->NPV =                                        PreZPrimeTree->NPV;
 ZPrimeTree->actualInteractionsPerCrossing =              PreZPrimeTree->actualInteractionsPerCrossing;
 ZPrimeTree->averageInteractionsPerCrossing =             PreZPrimeTree->averageInteractionsPerCrossing;
 ZPrimeTree->weight_pileup =                              PreZPrimeTree->weight_pileup;
 ZPrimeTree->correctedAverageMu =                         PreZPrimeTree->correctedAverageMu;
 ZPrimeTree->correctedAndScaledAverageMu =                PreZPrimeTree->correctedAndScaledAverageMu;
 ZPrimeTree->correctedActualMu =                          PreZPrimeTree->correctedActualMu;
 ZPrimeTree->correctedAndScaledActualMu =                 PreZPrimeTree->correctedAndScaledActualMu;
 ZPrimeTree->weight_pileup_up =                           PreZPrimeTree->weight_pileup_up;
 ZPrimeTree->weight_pileup_down =                         PreZPrimeTree->weight_pileup_down;
 ZPrimeTree->beamSpotWeight =                             PreZPrimeTree->beamSpotWeight;
 ZPrimeTree->ntruth_jet =                                 PreZPrimeTree->ntruth_jet;
 ZPrimeTree->njet =                                       PreZPrimeTree->njet;
 ZPrimeTree->metFinalTrk =                                PreZPrimeTree->metFinalTrk;
 ZPrimeTree->metFinalTrkPx =                              PreZPrimeTree->metFinalTrkPx;
 ZPrimeTree->metFinalTrkPy =                              PreZPrimeTree->metFinalTrkPy;
 ZPrimeTree->metFinalTrkSumEt =                           PreZPrimeTree->metFinalTrkSumEt;
 ZPrimeTree->metFinalTrkPhi =                             PreZPrimeTree->metFinalTrkPhi;
 ZPrimeTree->metFinalTrkOverSqrtSumEt =                   PreZPrimeTree->metFinalTrkOverSqrtSumEt;
 ZPrimeTree->metFinalTrkOverSqrtHt =                      PreZPrimeTree->metFinalTrkOverSqrtHt;
 ZPrimeTree->metFinalTrkSignificance =                    PreZPrimeTree->metFinalTrkSignificance;
 ZPrimeTree->metFinalTrkSigDirectional =                  PreZPrimeTree->metFinalTrkSigDirectional;
 ZPrimeTree->metEle =                                     PreZPrimeTree->metEle;
 ZPrimeTree->metEleSumEt =                                PreZPrimeTree->metEleSumEt;
 ZPrimeTree->metElePhi =                                  PreZPrimeTree->metElePhi;
 ZPrimeTree->metMuons =                                   PreZPrimeTree->metMuons;
 ZPrimeTree->metMuonsSumEt =                              PreZPrimeTree->metMuonsSumEt;
 ZPrimeTree->metMuonsPhi =                                PreZPrimeTree->metMuonsPhi;
 ZPrimeTree->metJet =                                     PreZPrimeTree->metJet;
 ZPrimeTree->metJetSumEt =                                PreZPrimeTree->metJetSumEt;
 ZPrimeTree->metJetPhi =                                  PreZPrimeTree->metJetPhi;
 ZPrimeTree->metSoftTrk =                                 PreZPrimeTree->metSoftTrk;
 ZPrimeTree->metSoftTrkSumEt =                            PreZPrimeTree->metSoftTrkSumEt;
 ZPrimeTree->metSoftTrkPhi =                              PreZPrimeTree->metSoftTrkPhi;
 ZPrimeTree->HLT_e120_lhvloose_L1EM22VHI =                PreZPrimeTree->HLT_e120_lhvloose_L1EM22VHI;
 ZPrimeTree->prescale_HLT_e120_lhvloose_L1EM22VHI =       PreZPrimeTree->prescale_HLT_e120_lhvloose_L1EM22VHI;
 ZPrimeTree->HLT_e100_lhvloose_L1EM22VHI =                PreZPrimeTree->HLT_e100_lhvloose_L1EM22VHI;
 ZPrimeTree->prescale_HLT_e100_lhvloose_L1EM22VHI =       PreZPrimeTree->prescale_HLT_e100_lhvloose_L1EM22VHI;
 ZPrimeTree->HLT_e80_lhvloose_L1EM22VHI =                 PreZPrimeTree->HLT_e80_lhvloose_L1EM22VHI;
 ZPrimeTree->prescale_HLT_e80_lhvloose_L1EM22VHI =        PreZPrimeTree->prescale_HLT_e80_lhvloose_L1EM22VHI;
 ZPrimeTree->HLT_e60_lhvloose_L1EM22VHI =                 PreZPrimeTree->HLT_e60_lhvloose_L1EM22VHI;
 ZPrimeTree->prescale_HLT_e60_lhvloose_L1EM22VHI =        PreZPrimeTree->prescale_HLT_e60_lhvloose_L1EM22VHI;
 ZPrimeTree->HLT_e40_lhvloose_L1EM22VHI =                 PreZPrimeTree->HLT_e40_lhvloose_L1EM22VHI;
 ZPrimeTree->prescale_HLT_e40_lhvloose_L1EM22VHI =        PreZPrimeTree->prescale_HLT_e40_lhvloose_L1EM22VHI;
 ZPrimeTree->HLT_e30_lhvloose_L1EM22VHI =                 PreZPrimeTree->HLT_e30_lhvloose_L1EM22VHI;
 ZPrimeTree->prescale_HLT_e30_lhvloose_L1EM22VHI =        PreZPrimeTree->prescale_HLT_e30_lhvloose_L1EM22VHI;
 ZPrimeTree->HLT_e20_lhvloose_L1EM15VH =                  PreZPrimeTree->HLT_e20_lhvloose_L1EM15VH;
 ZPrimeTree->prescale_HLT_e20_lhvloose_L1EM15VH =         PreZPrimeTree->prescale_HLT_e20_lhvloose_L1EM15VH;
 ZPrimeTree->HLT_e120_lhvloose_L1eEM28M =                 PreZPrimeTree->HLT_e120_lhvloose_L1eEM28M;
 ZPrimeTree->prescale_HLT_e120_lhvloose_L1eEM28M =        PreZPrimeTree->prescale_HLT_e120_lhvloose_L1eEM28M;
 ZPrimeTree->HLT_e100_lhvloose_L1eEM28M =                 PreZPrimeTree->HLT_e100_lhvloose_L1eEM28M;
 ZPrimeTree->prescale_HLT_e100_lhvloose_L1eEM28M =        PreZPrimeTree->prescale_HLT_e100_lhvloose_L1eEM28M;
 ZPrimeTree->HLT_e80_lhvloose_L1eEM28M =                  PreZPrimeTree->HLT_e80_lhvloose_L1eEM28M;
 ZPrimeTree->prescale_HLT_e80_lhvloose_L1eEM28M =         PreZPrimeTree->prescale_HLT_e80_lhvloose_L1eEM28M;
 ZPrimeTree->HLT_e60_lhvloose_L1eEM28M =                  PreZPrimeTree->HLT_e60_lhvloose_L1eEM28M;
 ZPrimeTree->prescale_HLT_e60_lhvloose_L1eEM28M =         PreZPrimeTree->prescale_HLT_e60_lhvloose_L1eEM28M;
 ZPrimeTree->HLT_e40_lhvloose_L1eEM28M =                  PreZPrimeTree->HLT_e40_lhvloose_L1eEM28M;
 ZPrimeTree->prescale_HLT_e40_lhvloose_L1eEM28M =         PreZPrimeTree->prescale_HLT_e40_lhvloose_L1eEM28M;
 ZPrimeTree->HLT_e30_lhvloose_L1eEM28M =                  PreZPrimeTree->HLT_e30_lhvloose_L1eEM28M;
 ZPrimeTree->prescale_HLT_e30_lhvloose_L1eEM28M =         PreZPrimeTree->prescale_HLT_e30_lhvloose_L1eEM28M;
 ZPrimeTree->HLT_e20_lhvloose_L1eEM18L =                  PreZPrimeTree->HLT_e20_lhvloose_L1eEM18L;
 ZPrimeTree->prescale_HLT_e20_lhvloose_L1eEM18L =         PreZPrimeTree->prescale_HLT_e20_lhvloose_L1eEM18L;
 ZPrimeTree->HLT_mu20_iloose_L1MU15 =                     PreZPrimeTree->HLT_mu20_iloose_L1MU15;
 ZPrimeTree->HLT_mu26_ivarmedium =                        PreZPrimeTree->HLT_mu26_ivarmedium;
 ZPrimeTree->HLT_mu50 =                                   PreZPrimeTree->HLT_mu50;
 ZPrimeTree->HLT_mu40 =                                   PreZPrimeTree->HLT_mu40;
 ZPrimeTree->HLT_mu24_ivarmedium_L1MU14FCH =              PreZPrimeTree->HLT_mu24_ivarmedium_L1MU14FCH;
 ZPrimeTree->HLT_mu50_L1MU14FCH =                         PreZPrimeTree->HLT_mu50_L1MU14FCH;
 ZPrimeTree->HLT_2e12_lhloose_L12EM10VH =                 PreZPrimeTree->HLT_2e12_lhloose_L12EM10VH;
 ZPrimeTree->HLT_2e17_lhvloose_nod0 =                     PreZPrimeTree->HLT_2e17_lhvloose_nod0;
 ZPrimeTree->HLT_2e24_lhvloose_nod0 =                     PreZPrimeTree->HLT_2e24_lhvloose_nod0;
 ZPrimeTree->HLT_2e24_lhvloose_L12EM20VH =                PreZPrimeTree->HLT_2e24_lhvloose_L12EM20VH;
 ZPrimeTree->HLT_2e24_lhvloose_L12eEM24L =                PreZPrimeTree->HLT_2e24_lhvloose_L12eEM24L;
 ZPrimeTree->HLT_singleLep =                              PreZPrimeTree->HLT_singleLep;
 ZPrimeTree->HLT_singleJet =                              PreZPrimeTree->HLT_singleJet;
 ZPrimeTree->randomRunNumber =                            PreZPrimeTree->randomRunNumber;
 ZPrimeTree->datasetNumber =                              PreZPrimeTree->datasetNumber;
 ZPrimeTree->year =                                       PreZPrimeTree->year;
 ZPrimeTree->mcEventWeight =                              PreZPrimeTree->mcEventWeight;
 ZPrimeTree->sample_xSec =                                PreZPrimeTree->sample_xSec;
 ZPrimeTree->sample_xSec_up_rel =                         PreZPrimeTree->sample_xSec_up_rel;
 ZPrimeTree->sample_xSec_down_rel =                       PreZPrimeTree->sample_xSec_down_rel;
 ZPrimeTree->sample_kFactor =                             PreZPrimeTree->sample_kFactor;
 ZPrimeTree->sample_filterEff =                           PreZPrimeTree->sample_filterEff;
 ZPrimeTree->weight_gen =                                 PreZPrimeTree->weight_gen;
 ZPrimeTree->weight_lepton =                              PreZPrimeTree->weight_lepton;
 ZPrimeTree->weight_jvt =                                 PreZPrimeTree->weight_jvt;
 ZPrimeTree->weight_btag =                                PreZPrimeTree->weight_btag;
 ZPrimeTree->weight_singleleptonTrigSF =                  PreZPrimeTree->weight_singleleptonTrigSF;
 ZPrimeTree->weight_dileptonTrigSF =                      PreZPrimeTree->weight_dileptonTrigSF;
 ZPrimeTree->fakeweight =                                 SelectedEvent.RecoWeight;//fake weight
 ZPrimeTree->n_truth_el =                                 PreZPrimeTree->n_truth_el;
 ZPrimeTree->n_truth_mu =                                 PreZPrimeTree->n_truth_mu;
 ZPrimeTree->n_truth_lep =                                PreZPrimeTree->n_truth_lep;
 ZPrimeTree->n_el =                                       PreZPrimeTree->n_el;
 ZPrimeTree->n_mu =                                       PreZPrimeTree->n_mu;
 ZPrimeTree->n_lep =                                      PreZPrimeTree->n_lep;
 ZPrimeTree->n_signal_el =                                PreZPrimeTree->n_signal_el;
 ZPrimeTree->n_signal_mu =                                PreZPrimeTree->n_signal_mu;
 ZPrimeTree->n_signal_lep =                               PreZPrimeTree->n_signal_lep;
 ZPrimeTree->n_bjets_65 =                                 PreZPrimeTree->n_bjets_65;
 ZPrimeTree->n_bjets_70 =                                 PreZPrimeTree->n_bjets_70;
 ZPrimeTree->n_bjets_77 =                                 PreZPrimeTree->n_bjets_77;
 ZPrimeTree->n_bjets_85 =                                 PreZPrimeTree->n_bjets_85;
 ZPrimeTree->n_bjets_90 =                                 PreZPrimeTree->n_bjets_90;
 ZPrimeTree->n_bjets =                                    PreZPrimeTree->n_bjets;
 ZPrimeTree->lepton1_isEl =                               PreZPrimeTree->lepton1_isEl;
 ZPrimeTree->lepton1_m =                                  PreZPrimeTree->lepton1_m;
 ZPrimeTree->lepton1_E =                                  PreZPrimeTree->lepton1_E;
 ZPrimeTree->lepton1_pt =                                 PreZPrimeTree->lepton1_pt;
 ZPrimeTree->lepton1_phi =                                PreZPrimeTree->lepton1_phi;
 ZPrimeTree->lepton1_eta =                                PreZPrimeTree->lepton1_eta;
 ZPrimeTree->lepton1_caloeta =                            PreZPrimeTree->lepton1_caloeta;
 ZPrimeTree->lepton1_charge =                             PreZPrimeTree->lepton1_charge;
 ZPrimeTree->lepton1_truthType =                          PreZPrimeTree->lepton1_truthType;
 ZPrimeTree->lepton1_truthOrigin =                        PreZPrimeTree->lepton1_truthOrigin;
 ZPrimeTree->lepton1_IFFType =                            PreZPrimeTree->lepton1_IFFType;
 ZPrimeTree->lepton1_isPromptIFF =                        PreZPrimeTree->lepton1_isPromptIFF;
 ZPrimeTree->lepton1_isIsoHighPtCaloOnly =                PreZPrimeTree->lepton1_isIsoHighPtCaloOnly;
 ZPrimeTree->lepton1_isIsoLoose_VarRad =                  PreZPrimeTree->lepton1_isIsoLoose_VarRad;
 ZPrimeTree->lepton1_isIsoTight_VarRad =                  PreZPrimeTree->lepton1_isIsoTight_VarRad;
 ZPrimeTree->lepton1_isIDLoose =                          PreZPrimeTree->lepton1_isIDLoose;
 ZPrimeTree->lepton1_isIDMedium =                         PreZPrimeTree->lepton1_isIDMedium;
 ZPrimeTree->lepton1_isIDTight =                          PreZPrimeTree->lepton1_isIDTight;
 ZPrimeTree->lepton1_RecoWeight =                         PreZPrimeTree->lepton1_RecoWeight;
 ZPrimeTree->lepton1_IsoHighPtCaloOnlyWeight =            PreZPrimeTree->lepton1_IsoHighPtCaloOnlyWeight;
 ZPrimeTree->lepton1_IsoLoose_VarRadWeight =              PreZPrimeTree->lepton1_IsoLoose_VarRadWeight;
 ZPrimeTree->lepton1_IsoTight_VarRadWeight =              PreZPrimeTree->lepton1_IsoTight_VarRadWeight;
 ZPrimeTree->lepton1_IDLooseWeight =                      PreZPrimeTree->lepton1_IDLooseWeight;
 ZPrimeTree->lepton1_IDMediumWeight =                     PreZPrimeTree->lepton1_IDMediumWeight;
 ZPrimeTree->lepton1_IDTightWeight =                      PreZPrimeTree->lepton1_IDTightWeight;
 ZPrimeTree->lepton1_ambiguityType =                      PreZPrimeTree->lepton1_ambiguityType;
 ZPrimeTree->lepton1_addAmbiguity =                       PreZPrimeTree->lepton1_addAmbiguity;
 ZPrimeTree->lepton1_d0sig =                              PreZPrimeTree->lepton1_d0sig;
 ZPrimeTree->lepton1_z0sinTheta =                         PreZPrimeTree->lepton1_z0sinTheta;
 ZPrimeTree->lepton1_d0 =                                 PreZPrimeTree->lepton1_d0;
 ZPrimeTree->lepton1_z0 =                                 PreZPrimeTree->lepton1_z0;
 ZPrimeTree->lepton1_isSig =                              PreZPrimeTree->lepton1_isSig;
 ZPrimeTree->lepton1_isIso =                              PreZPrimeTree->lepton1_isIso;
 ZPrimeTree->lepton1_isTruthMatched =                     PreZPrimeTree->lepton1_isTruthMatched;
 ZPrimeTree->lepton1_isMatched =                          PreZPrimeTree->lepton1_isMatched;
 ZPrimeTree->lepton1_truthE =                             PreZPrimeTree->lepton1_truthE;
 ZPrimeTree->lepton1_truthpt =                            PreZPrimeTree->lepton1_truthpt;
 ZPrimeTree->lepton1_truthphi =                           PreZPrimeTree->lepton1_truthphi;
 ZPrimeTree->lepton1_trutheta =                           PreZPrimeTree->lepton1_trutheta;
 ZPrimeTree->lepton1_truthpdgid =                         PreZPrimeTree->lepton1_truthpdgid;
 ZPrimeTree->lepton2_isEl =                               PreZPrimeTree->lepton2_isEl;
 ZPrimeTree->lepton2_m =                                  PreZPrimeTree->lepton2_m;
 ZPrimeTree->lepton2_E =                                  PreZPrimeTree->lepton2_E;
 ZPrimeTree->lepton2_pt =                                 PreZPrimeTree->lepton2_pt;
 ZPrimeTree->lepton2_phi =                                PreZPrimeTree->lepton2_phi;
 ZPrimeTree->lepton2_eta =                                PreZPrimeTree->lepton2_eta;
 ZPrimeTree->lepton2_caloeta =                            PreZPrimeTree->lepton2_caloeta;
 ZPrimeTree->lepton2_charge =                             PreZPrimeTree->lepton2_charge;
 ZPrimeTree->lepton2_truthType =                          PreZPrimeTree->lepton2_truthType;
 ZPrimeTree->lepton2_truthOrigin =                        PreZPrimeTree->lepton2_truthOrigin;
 ZPrimeTree->lepton2_IFFType =                            PreZPrimeTree->lepton2_IFFType;
 ZPrimeTree->lepton2_isPromptIFF =                        PreZPrimeTree->lepton2_isPromptIFF;
 ZPrimeTree->lepton2_isIsoHighPtCaloOnly =                PreZPrimeTree->lepton2_isIsoHighPtCaloOnly;
 ZPrimeTree->lepton2_isIsoLoose_VarRad =                  PreZPrimeTree->lepton2_isIsoLoose_VarRad;
 ZPrimeTree->lepton2_isIsoTight_VarRad =                  PreZPrimeTree->lepton2_isIsoTight_VarRad;
 ZPrimeTree->lepton2_isIDLoose =                          PreZPrimeTree->lepton2_isIDLoose;
 ZPrimeTree->lepton2_isIDMedium =                         PreZPrimeTree->lepton2_isIDMedium;
 ZPrimeTree->lepton2_isIDTight =                          PreZPrimeTree->lepton2_isIDTight;
 ZPrimeTree->lepton2_RecoWeight =                         PreZPrimeTree->lepton2_RecoWeight;
 ZPrimeTree->lepton2_IsoHighPtCaloOnlyWeight =            PreZPrimeTree->lepton2_IsoHighPtCaloOnlyWeight;
 ZPrimeTree->lepton2_IsoLoose_VarRadWeight =              PreZPrimeTree->lepton2_IsoLoose_VarRadWeight;
 ZPrimeTree->lepton2_IsoTight_VarRadWeight =              PreZPrimeTree->lepton2_IsoTight_VarRadWeight;
 ZPrimeTree->lepton2_IDLooseWeight =                      PreZPrimeTree->lepton2_IDLooseWeight;
 ZPrimeTree->lepton2_IDMediumWeight =                     PreZPrimeTree->lepton2_IDMediumWeight;
 ZPrimeTree->lepton2_IDTightWeight =                      PreZPrimeTree->lepton2_IDTightWeight;
 ZPrimeTree->lepton2_ambiguityType =                      PreZPrimeTree->lepton2_ambiguityType;
 ZPrimeTree->lepton2_addAmbiguity =                       PreZPrimeTree->lepton2_addAmbiguity;
 ZPrimeTree->lepton2_d0sig =                              PreZPrimeTree->lepton2_d0sig;
 ZPrimeTree->lepton2_z0sinTheta =                         PreZPrimeTree->lepton2_z0sinTheta;
 ZPrimeTree->lepton2_d0 =                                 PreZPrimeTree->lepton2_d0;
 ZPrimeTree->lepton2_z0 =                                 PreZPrimeTree->lepton2_z0;
 ZPrimeTree->lepton2_isSig =                              PreZPrimeTree->lepton2_isSig;
 ZPrimeTree->lepton2_isIso =                              PreZPrimeTree->lepton2_isIso;
 ZPrimeTree->lepton2_isTruthMatched =                     PreZPrimeTree->lepton2_isTruthMatched;
 ZPrimeTree->lepton2_isMatched =                          PreZPrimeTree->lepton2_isMatched;
 ZPrimeTree->lepton2_truthE =                             PreZPrimeTree->lepton2_truthE;
 ZPrimeTree->lepton2_truthpt =                            PreZPrimeTree->lepton2_truthpt;
 ZPrimeTree->lepton2_truthphi =                           PreZPrimeTree->lepton2_truthphi;
 ZPrimeTree->lepton2_trutheta =                           PreZPrimeTree->lepton2_trutheta;
 ZPrimeTree->lepton2_truthpdgid =                         PreZPrimeTree->lepton2_truthpdgid;
 ZPrimeTree->lepton_singleleptrigMatched =                PreZPrimeTree->lepton_singleleptrigMatched;
 ZPrimeTree->lepton_dileptrigMatched =                    PreZPrimeTree->lepton_dileptrigMatched;
 ZPrimeTree->jet1_pt =                                    PreZPrimeTree->jet1_pt;
 ZPrimeTree->jet1_phi =                                   PreZPrimeTree->jet1_phi;
 ZPrimeTree->jet1_eta =                                   PreZPrimeTree->jet1_eta;
 ZPrimeTree->jet1_E =                                     PreZPrimeTree->jet1_E;
 ZPrimeTree->jet1_PartonTruthLabelID =                    PreZPrimeTree->jet1_PartonTruthLabelID;
 ZPrimeTree->jet1_ConeTruthLabelID =                      PreZPrimeTree->jet1_ConeTruthLabelID;
 ZPrimeTree->jet1_Jvt =                                   PreZPrimeTree->jet1_Jvt;
 ZPrimeTree->jet1_btag_65 =                               PreZPrimeTree->jet1_btag_65;
 ZPrimeTree->jet1_btag_70 =                               PreZPrimeTree->jet1_btag_70;
 ZPrimeTree->jet1_btag_77 =                               PreZPrimeTree->jet1_btag_77;
 ZPrimeTree->jet1_btag_85 =                               PreZPrimeTree->jet1_btag_85;
 ZPrimeTree->jet1_btag_90 =                               PreZPrimeTree->jet1_btag_90;
 ZPrimeTree->jet1_btag =                                  PreZPrimeTree->jet1_btag;
 ZPrimeTree->mLepJet =                                    PreZPrimeTree->mLepJet;
 ZPrimeTree->dRLepJet =                                   PreZPrimeTree->dRLepJet;
 ZPrimeTree->detaLepJet =                                 PreZPrimeTree->detaLepJet;
 ZPrimeTree->dphiLepJet =                                 PreZPrimeTree->dphiLepJet;
 ZPrimeTree->LepOvermLepJet =                             PreZPrimeTree->LepOvermLepJet;
 ZPrimeTree->matched_mLepJet =                            PreZPrimeTree->matched_mLepJet;
 ZPrimeTree->truth_mLepJet =                              PreZPrimeTree->truth_mLepJet;
 ZPrimeTree->truth_dRLepJet =                             PreZPrimeTree->truth_dRLepJet;
 ZPrimeTree->mindphiJetMet =                              PreZPrimeTree->mindphiJetMet;
 ZPrimeTree->dphiLepMet =                                 PreZPrimeTree->dphiLepMet;
 ZPrimeTree->born_lepton1_E =                             PreZPrimeTree->born_lepton1_E;
 ZPrimeTree->born_lepton1_pt =                            PreZPrimeTree->born_lepton1_pt;
 ZPrimeTree->born_lepton1_eta =                           PreZPrimeTree->born_lepton1_eta;
 ZPrimeTree->born_lepton1_phi =                           PreZPrimeTree->born_lepton1_phi;
 ZPrimeTree->born_lepton2_E =                             PreZPrimeTree->born_lepton2_E;
 ZPrimeTree->born_lepton2_pt =                            PreZPrimeTree->born_lepton2_pt;
 ZPrimeTree->born_lepton2_eta =                           PreZPrimeTree->born_lepton2_eta;
 ZPrimeTree->born_lepton2_phi =                           PreZPrimeTree->born_lepton2_phi;
 ZPrimeTree->born_dilepton_m =                            PreZPrimeTree->born_dilepton_m;
 ZPrimeTree->n_born_lepton =                              PreZPrimeTree->n_born_lepton;
 ZPrimeTree->n_truth_boson =                              PreZPrimeTree->n_truth_boson;
 ZPrimeTree->truth_boson_m =                              PreZPrimeTree->truth_boson_m;
 ZPrimeTree->hardscatter_W_m =                            PreZPrimeTree->hardscatter_W_m;
 ZPrimeTree->dilepton_m =                                 PreZPrimeTree->dilepton_m;
 ZPrimeTree->dilepton_pt =                                PreZPrimeTree->dilepton_pt;
 ZPrimeTree->dilepton_phi =                               PreZPrimeTree->dilepton_phi;
 ZPrimeTree->dilepton_eta =                               PreZPrimeTree->dilepton_eta;
 ZPrimeTree->dilepton_DeltaR =                            PreZPrimeTree->dilepton_DeltaR;
 ZPrimeTree->dilepton_DeltaEta =                          PreZPrimeTree->dilepton_DeltaEta;
 ZPrimeTree->dilepton_DeltaPhi =                          PreZPrimeTree->dilepton_DeltaPhi;
 ZPrimeTree->dilepton_CosThetaStar =                      PreZPrimeTree->dilepton_CosThetaStar;
 ZPrimeTree->mt_lep1 =                                    PreZPrimeTree->mt_lep1;
 ZPrimeTree->mt_lep2 =                                    PreZPrimeTree->mt_lep2;
 ZPrimeTree->jets_HT =                                    PreZPrimeTree->jets_HT;
 ZPrimeTree->meff =                                       PreZPrimeTree->meff;

 ZPrimeTree->passElTrigger =                              SelectedEvent.passElTrigger;
 ZPrimeTree->passMuTrigger =                              SelectedEvent.passMuTrigger;










 ZPrimeTree->RecoWeight =                    SelectedEvent.RecoWeight;
 ZPrimeTree->RecoWeight_Stat_up =            SelectedEvent.RecoWeight_Stat_up;
 ZPrimeTree->RecoWeight_Stat_down =          SelectedEvent.RecoWeight_Stat_down;
 ZPrimeTree->RecoWeight_PromptSubtr_up =     SelectedEvent.RecoWeight_PromptSubtr_up;
 ZPrimeTree->RecoWeight_PromptSubtr_down =   SelectedEvent.RecoWeight_PromptSubtr_down;
 ZPrimeTree->RecoWeight_MET_up =             SelectedEvent.RecoWeight_MET_up;
 ZPrimeTree->RecoWeight_MET_down =           SelectedEvent.RecoWeight_MET_down;
 ZPrimeTree->RecoWeight_d0sig_up =           SelectedEvent.RecoWeight_d0sig_up;
 ZPrimeTree->RecoWeight_d0sig_down =         SelectedEvent.RecoWeight_d0sig_down;
 ZPrimeTree->RecoWeight_RealStat_up =        SelectedEvent.RecoWeight_RealStat_up;
 ZPrimeTree->RecoWeight_RealStat_down =      SelectedEvent.RecoWeight_RealStat_down;
 ZPrimeTree->RecoWeight_FourTerm_TT =        SelectedEvent.RecoWeight_FourTerm_TT;
 ZPrimeTree->RecoWeight_FourTerm_TL =        SelectedEvent.RecoWeight_FourTerm_TL;
 ZPrimeTree->RecoWeight_FourTerm_LT =        SelectedEvent.RecoWeight_FourTerm_LT;
 ZPrimeTree->RecoWeight_FourTerm_LL =        SelectedEvent.RecoWeight_FourTerm_LL;

 ZPrimeTree->eeChannel =                     SelectedEvent.eeChannel;
 ZPrimeTree->mumuChannel =                   SelectedEvent.mumuChannel;
 ZPrimeTree->emuChannel =                    SelectedEvent.emuChannel;
 ZPrimeTree->eeChannel_withmuon =            SelectedEvent.eeChannel_withmuon;
 ZPrimeTree->SingleElectron =                SelectedEvent.SingleElectron;
 ZPrimeTree->TruthDilMass_Born =             SelectedEvent.TruthDilMass_Born;
 ZPrimeTree->TruthDilRapidity_Born =         SelectedEvent.TruthDilRapidity_Born;
 ZPrimeTree->Lepton1_Pt =                    SelectedEvent.Lepton1_Pt;
 ZPrimeTree->Lepton2_Pt =                    SelectedEvent.Lepton2_Pt;
 ZPrimeTree->Lepton3_Pt =                    SelectedEvent.Lepton3_Pt;
 ZPrimeTree->Lepton1_Phi =                   SelectedEvent.Lepton1_Phi;
 ZPrimeTree->Lepton2_Phi =                   SelectedEvent.Lepton2_Phi;
 ZPrimeTree->Lepton3_Phi =                   SelectedEvent.Lepton3_Phi;
 ZPrimeTree->Lepton1_Eta =                   SelectedEvent.Lepton1_Eta;
 ZPrimeTree->Lepton2_Eta =                   SelectedEvent.Lepton2_Eta;
 ZPrimeTree->Lepton3_Eta =                   SelectedEvent.Lepton3_Eta;
 ZPrimeTree->pTllReweight =                  SelectedEvent.pTllReweight;
 ZPrimeTree->ChargeMisIDSFWeight =           SelectedEvent.ChargeMisIDSFWeight;
 ZPrimeTree->ChargeIDSFWeight =              SelectedEvent.ChargeIDSFWeight;
 ZPrimeTree->LeptonSFWeight =                SelectedEvent.LeptonSFWeight;
 ZPrimeTree->PileupWeight =                  SelectedEvent.PileupWeight;
 ZPrimeTree->TriggerSF =                     SelectedEvent.TriggerSF;
 ZPrimeTree->n_Bjets =                       SelectedEvent.n_Bjets;
 ZPrimeTree->MET_Et =                        SelectedEvent.MET_Et;
 ZPrimeTree->Lepton1_z0 =                    SelectedEvent.Lepton1_z0;
 ZPrimeTree->Lepton2_z0 =                    SelectedEvent.Lepton2_z0;
 ZPrimeTree->Lepton3_z0 =                    SelectedEvent.Lepton3_z0;
 ZPrimeTree->Lepton1_d0sig =                 SelectedEvent.Lepton1_d0sig;
 ZPrimeTree->Lepton2_d0sig =                 SelectedEvent.Lepton2_d0sig;
 ZPrimeTree->Lepton3_d0sig =                 SelectedEvent.Lepton3_d0sig;
 ZPrimeTree->Lepton1_DeltaR =                SelectedEvent.Lepton1_DeltaR;
 ZPrimeTree->Lepton2_DeltaR =                SelectedEvent.Lepton2_DeltaR;
 ZPrimeTree->Mu =                            SelectedEvent.Mu;
 ZPrimeTree->MuActual =                      SelectedEvent.MuActual;
 ZPrimeTree->PhiRF =                         SelectedEvent.PhiRF;
 ZPrimeTree->Weight_kFactor_Old =            SelectedEvent.Weight_kFactor_Old;
 ZPrimeTree->Weight_kFactor_QCDEW =          SelectedEvent.Weight_kFactor_QCDEW;
 ZPrimeTree->Weight_kFactor_New_CT18NNLO =   SelectedEvent.Weight_kFactor_New_CT18NNLO;
 ZPrimeTree->Weight_kFactor_New_CT18ANNLO =  SelectedEvent.Weight_kFactor_New_CT18ANNLO;
 ZPrimeTree->Weight_kFactor_PowhegtoSherpa = SelectedEvent.Weight_kFactor_PowhegtoSherpa;

 ZPrimeTree->Weight_indiv_SF_EL_ChargeMisID_STAT_UP   = SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_STAT_UP;
 ZPrimeTree->Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN = SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN;
 ZPrimeTree->Weight_indiv_SF_EL_ChargeMisID_SYST_UP   = SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_SYST_UP;
 ZPrimeTree->Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN = SelectedEvent.Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN;

 ZPrimeTree->Lepton_Pt_born                = SelectedEvent.Lepton_Pt_born;
 ZPrimeTree->AntiLepton_Pt_born            = SelectedEvent.AntiLepton_Pt_born;
 ZPrimeTree->Lepton_Eta_born               = SelectedEvent.Lepton_Eta_born;
 ZPrimeTree->AntiLepton_Eta_born           = SelectedEvent.AntiLepton_Eta_born;
 ZPrimeTree->Lepton_Phi_born               = SelectedEvent.Lepton_Phi_born;
 ZPrimeTree->AntiLepton_Phi_born           = SelectedEvent.AntiLepton_Phi_born;
 ZPrimeTree->Lepton_m_born                 = SelectedEvent.Lepton_m_born;
 ZPrimeTree->AntiLepton_m_born             = SelectedEvent.AntiLepton_m_born;
 ZPrimeTree->Lepton_Pt_bare                = SelectedEvent.Lepton_Pt_bare;
 ZPrimeTree->AntiLepton_Pt_bare            = SelectedEvent.AntiLepton_Pt_bare;
 ZPrimeTree->Lepton_Eta_bare               = SelectedEvent.Lepton_Eta_bare;
 ZPrimeTree->AntiLepton_Eta_bare           = SelectedEvent.AntiLepton_Eta_bare;
 ZPrimeTree->Lepton_Phi_bare               = SelectedEvent.Lepton_Phi_bare;
 ZPrimeTree->AntiLepton_Phi_bare           = SelectedEvent.AntiLepton_Phi_bare;
 ZPrimeTree->Lepton_Pt_dressed             = SelectedEvent.Lepton_Pt_dressed;
 ZPrimeTree->Lepton_Eta_dressed            = SelectedEvent.Lepton_Eta_dressed;
 ZPrimeTree->Lepton_Phi_dressed            = SelectedEvent.Lepton_Phi_dressed;
 ZPrimeTree->Lepton_Charge_dressed         = SelectedEvent.Lepton_Charge_dressed;
 ZPrimeTree->AntiLepton_Pt_dressed         = SelectedEvent.AntiLepton_Pt_dressed;
 ZPrimeTree->AntiLepton_Eta_dressed        = SelectedEvent.AntiLepton_Eta_dressed;
 ZPrimeTree->AntiLepton_Phi_dressed        = SelectedEvent.AntiLepton_Phi_dressed;
 ZPrimeTree->AntiLepton_Charge_dressed     = SelectedEvent.AntiLepton_Charge_dressed;

 ZPrimeTree->pass_ee_TT =                    SelectedEvent.pass_ee_TT;
 ZPrimeTree->pass_ee_TL =                    SelectedEvent.pass_ee_TL;
 ZPrimeTree->pass_ee_LT =                    SelectedEvent.pass_ee_LT;
 ZPrimeTree->pass_ee_LL =                    SelectedEvent.pass_ee_LL;
 ZPrimeTree->pass_mm_TT =                    SelectedEvent.pass_mm_TT;
 ZPrimeTree->pass_mm_TL =                    SelectedEvent.pass_mm_TL;
 ZPrimeTree->pass_mm_LT =                    SelectedEvent.pass_mm_LT;
 ZPrimeTree->pass_mm_LL =                    SelectedEvent.pass_mm_LL;
 ZPrimeTree->Lepton1_isTight =               SelectedEvent.Lepton1.isTight;
 ZPrimeTree->Lepton2_isTight =               SelectedEvent.Lepton2.isTight;
 ZPrimeTree->Lepton3_isTight =               SelectedEvent.Lepton3.isTight;
 ZPrimeTree->Lepton1_passMediumID =          SelectedEvent.Lepton1_passMediumID;
 ZPrimeTree->Lepton2_passMediumID =          SelectedEvent.Lepton2_passMediumID;
 ZPrimeTree->Lepton3_passMediumID =          SelectedEvent.Lepton3_passMediumID;
 ZPrimeTree->Lepton1_passLooseID =           SelectedEvent.Lepton1_passLooseID;
 ZPrimeTree->Lepton2_passLooseID =           SelectedEvent.Lepton2_passLooseID;
 ZPrimeTree->Lepton3_passLooseID =           SelectedEvent.Lepton3_passLooseID;
 ZPrimeTree->Lepton1_passIso =               SelectedEvent.Lepton1_passIso;
 ZPrimeTree->Lepton2_passIso =               SelectedEvent.Lepton2_passIso;
 ZPrimeTree->Lepton1_IsoWeight =             SelectedEvent.Lepton1_IsoWeight;
 ZPrimeTree->Lepton2_IsoWeight =             SelectedEvent.Lepton2_IsoWeight;

 ZPrimeTree->Lepton1_Charge =                SelectedEvent.Lepton1.Charge;
 ZPrimeTree->Lepton2_Charge =                SelectedEvent.Lepton2.Charge;
 ZPrimeTree->Lepton1_isTruthMatch =          SelectedEvent.Lepton1.isTruthMatch;
 ZPrimeTree->Lepton2_isTruthMatch =          SelectedEvent.Lepton2.isTruthMatch;
 ZPrimeTree->Lepton1_TightWeight =           SelectedEvent.Lepton1_TightWeight;
 ZPrimeTree->Lepton2_TightWeight =           SelectedEvent.Lepton2_TightWeight;
 ZPrimeTree->Lepton3_TightWeight =           SelectedEvent.Lepton3_TightWeight;
 ZPrimeTree->Lepton1_LooseWeight =           SelectedEvent.Lepton1_LooseWeight;
 ZPrimeTree->Lepton2_LooseWeight =           SelectedEvent.Lepton2_LooseWeight;
 ZPrimeTree->Lepton3_LooseWeight =           SelectedEvent.Lepton3_LooseWeight;
 ZPrimeTree->Lepton1_MediumIDWeight =        SelectedEvent.Lepton1_MediumIDWeight;
 ZPrimeTree->Lepton2_MediumIDWeight =        SelectedEvent.Lepton2_MediumIDWeight;
 ZPrimeTree->PrescaleFactor =                SelectedEvent.PrescaleFactor;
 ZPrimeTree->Lepton1_PrescaleFactor =        SelectedEvent.Lepton1_PrescaleFactor;
 ZPrimeTree->Lepton2_PrescaleFactor =        SelectedEvent.Lepton2_PrescaleFactor;


 } // !TruthRun

 if(isTruthRun){
   SelectedEvent.TotalWeight = PreZPrimeTree->weight_gen
                             * PreZPrimeTree->weight_lumi
                             * PreZPrimeTree->mcEventWeight
                             * PreZPrimeTree->weight_norm;

   SelectedEvent.RecoDilMass = PreZPrimeTree->born_dilepton_m;
 }

 SelectedEvent.born_lepton1_E     = PreZPrimeTree->born_lepton1_E;
 SelectedEvent.born_lepton1_pt    = PreZPrimeTree->born_lepton1_pt;
 SelectedEvent.born_lepton1_eta   = PreZPrimeTree->born_lepton1_eta;
 SelectedEvent.born_lepton1_phi   = PreZPrimeTree->born_lepton1_phi;
 SelectedEvent.born_lepton1_pdgid = PreZPrimeTree->born_lepton1_pdgid;
 SelectedEvent.born_lepton2_E     = PreZPrimeTree->born_lepton2_E;
 SelectedEvent.born_lepton2_pt    = PreZPrimeTree->born_lepton2_pt;
 SelectedEvent.born_lepton2_eta   = PreZPrimeTree->born_lepton2_eta;
 SelectedEvent.born_lepton2_phi   = PreZPrimeTree->born_lepton2_phi;
 SelectedEvent.born_lepton2_pdgid = PreZPrimeTree->born_lepton2_pdgid;
 SelectedEvent.pdf_pdgId1         = PreZPrimeTree->pdf_pdgId1;
 SelectedEvent.pdf_pdgId2         = PreZPrimeTree->pdf_pdgId2;
 SelectedEvent.n_born_lepton      = PreZPrimeTree->n_born_lepton;

 TLorentzVector Lepton, Antilepton, ZBoson;

 if(SelectedEvent.n_born_lepton == 2){
   if(SelectedEvent.born_lepton1_pdgid > 0 && SelectedEvent.born_lepton2_pdgid < 0){
     Lepton.SetPtEtaPhiE(SelectedEvent.born_lepton1_pt, SelectedEvent.born_lepton1_eta, SelectedEvent.born_lepton1_phi, SelectedEvent.born_lepton1_E);
     Antilepton.SetPtEtaPhiE(SelectedEvent.born_lepton2_pt, SelectedEvent.born_lepton2_eta, SelectedEvent.born_lepton2_phi, SelectedEvent.born_lepton2_E);
   }
   else if(SelectedEvent.born_lepton2_pdgid > 0 && SelectedEvent.born_lepton1_pdgid < 0){
     Antilepton.SetPtEtaPhiE(SelectedEvent.born_lepton1_pt, SelectedEvent.born_lepton1_eta, SelectedEvent.born_lepton1_phi, SelectedEvent.born_lepton1_E);
     Lepton.SetPtEtaPhiE(SelectedEvent.born_lepton2_pt, SelectedEvent.born_lepton2_eta, SelectedEvent.born_lepton2_phi, SelectedEvent.born_lepton2_E);
   }
   else{
     cout<<"ERROR! no lepton-antilepton pair."<<endl;
   }
 }

 ZBoson = Lepton + Antilepton;
 SelectedEvent.born_CosThetaCS = calculate_theta(ZBoson, Lepton, Antilepton) * ZBoson.Rapidity() / fabs(ZBoson.Rapidity());
 SelectedEvent.born_PhiCS = calculate_phi(Lepton, Antilepton, 13600.0 / 2.0);
 SelectedEvent.born_dilepton_mass = PreZPrimeTree->born_dilepton_m;
 SelectedEvent.born_dilepton_pt = PreZPrimeTree->born_dilepton_pt;
 SelectedEvent.born_dilepton_rapidity = PreZPrimeTree->born_dilepton_rapidity;

 if(doSignalReweight && (SelectedEvent.n_born_lepton == 2)){
   SSMModel_0p5TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            SelectedEvent.born_dilepton_rapidity);
   SSMModel_0p5TeV->setModelParametersSSM("SSM");
   if(AngularFileName != "") SSMModel_0p5TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_SSM_0p5TeV = SSMModel_0p5TeV->getRWFactor();

   SSMModel_0p6TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   SSMModel_0p6TeV->setModelParametersSSM("SSM");
   if(AngularFileName != "") SSMModel_0p6TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_SSM_0p6TeV = SSMModel_0p6TeV->getRWFactor();

   SSMModel_0p8TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   SSMModel_0p8TeV->setModelParametersSSM("SSM");
   if(AngularFileName != "") SSMModel_0p8TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_SSM_0p8TeV = SSMModel_0p8TeV->getRWFactor();

   SSMModel_1TeV->execute(PreZPrimeTree->truth_sHat,
                          PreZPrimeTree->truth_tHat,
                          PreZPrimeTree->truth_uHat,
                          PreZPrimeTree->pdf_pdgId1,
                          PreZPrimeTree->pdf_pdgId2,
                          PreZPrimeTree->born_lepton1_pdgid,
                          PreZPrimeTree->born_lepton2_pdgid,
                          SelectedEvent.born_CosThetaCS,
                          SelectedEvent.born_PhiCS,
                          SelectedEvent.born_dilepton_mass,
                          SelectedEvent.born_dilepton_pt,
                          fabs(SelectedEvent.born_dilepton_rapidity));
   SSMModel_1TeV->setModelParametersSSM("SSM");
   if(AngularFileName != "") SSMModel_1TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_SSM_1TeV = SSMModel_1TeV->getRWFactor();

   SSMModel_2TeV->execute(PreZPrimeTree->truth_sHat,
                          PreZPrimeTree->truth_tHat,
                          PreZPrimeTree->truth_uHat,
                          PreZPrimeTree->pdf_pdgId1,
                          PreZPrimeTree->pdf_pdgId2,
                          PreZPrimeTree->born_lepton1_pdgid,
                          PreZPrimeTree->born_lepton2_pdgid,
                          SelectedEvent.born_CosThetaCS,
                          SelectedEvent.born_PhiCS,
                          SelectedEvent.born_dilepton_mass,
                          SelectedEvent.born_dilepton_pt,
                          fabs(SelectedEvent.born_dilepton_rapidity));
   SSMModel_2TeV->setModelParametersSSM("SSM");
   if(AngularFileName != "") SSMModel_2TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_SSM_2TeV = SSMModel_2TeV->getRWFactor();
 
   SSMModel_3TeV->execute(PreZPrimeTree->truth_sHat,
                          PreZPrimeTree->truth_tHat,
                          PreZPrimeTree->truth_uHat,
                          PreZPrimeTree->pdf_pdgId1,
                          PreZPrimeTree->pdf_pdgId2,
                          PreZPrimeTree->born_lepton1_pdgid,
                          PreZPrimeTree->born_lepton2_pdgid,
                          SelectedEvent.born_CosThetaCS,
                          SelectedEvent.born_PhiCS,
                          SelectedEvent.born_dilepton_mass,
                          SelectedEvent.born_dilepton_pt,
                          fabs(SelectedEvent.born_dilepton_rapidity));
   SSMModel_3TeV->setModelParametersSSM("SSM");
   if(AngularFileName != "") SSMModel_3TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_SSM_3TeV = SSMModel_3TeV->getRWFactor();

   SSMModel_4TeV->execute(PreZPrimeTree->truth_sHat,
                          PreZPrimeTree->truth_tHat,
                          PreZPrimeTree->truth_uHat,
                          PreZPrimeTree->pdf_pdgId1,
                          PreZPrimeTree->pdf_pdgId2,
                          PreZPrimeTree->born_lepton1_pdgid,
                          PreZPrimeTree->born_lepton2_pdgid,
                          SelectedEvent.born_CosThetaCS,
                          SelectedEvent.born_PhiCS,
                          SelectedEvent.born_dilepton_mass,
                          SelectedEvent.born_dilepton_pt,
                          fabs(SelectedEvent.born_dilepton_rapidity));
   SSMModel_4TeV->setModelParametersSSM("SSM");
   if(AngularFileName != "") SSMModel_4TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_SSM_4TeV = SSMModel_4TeV->getRWFactor();

   SSMModel_5TeV->execute(PreZPrimeTree->truth_sHat,
                          PreZPrimeTree->truth_tHat,
                          PreZPrimeTree->truth_uHat,
                          PreZPrimeTree->pdf_pdgId1,
                          PreZPrimeTree->pdf_pdgId2,
                          PreZPrimeTree->born_lepton1_pdgid,
                          PreZPrimeTree->born_lepton2_pdgid,
                          SelectedEvent.born_CosThetaCS,
                          SelectedEvent.born_PhiCS,
                          SelectedEvent.born_dilepton_mass,
                          SelectedEvent.born_dilepton_pt,
                          fabs(SelectedEvent.born_dilepton_rapidity));
   SSMModel_5TeV->setModelParametersSSM("SSM");
   if(AngularFileName != "") SSMModel_5TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_SSM_5TeV = SSMModel_5TeV->getRWFactor();

   SSMModel_6TeV->execute(PreZPrimeTree->truth_sHat,
                          PreZPrimeTree->truth_tHat,
                          PreZPrimeTree->truth_uHat,
                          PreZPrimeTree->pdf_pdgId1,
                          PreZPrimeTree->pdf_pdgId2,
                          PreZPrimeTree->born_lepton1_pdgid,
                          PreZPrimeTree->born_lepton2_pdgid,
                          SelectedEvent.born_CosThetaCS,
                          SelectedEvent.born_PhiCS,
                          SelectedEvent.born_dilepton_mass,
                          SelectedEvent.born_dilepton_pt,
                          fabs(SelectedEvent.born_dilepton_rapidity));
   SSMModel_6TeV->setModelParametersSSM("SSM");
   if(AngularFileName != "") SSMModel_6TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_SSM_6TeV = SSMModel_6TeV->getRWFactor();

   SSMModel_7TeV->execute(PreZPrimeTree->truth_sHat,
                          PreZPrimeTree->truth_tHat,
                          PreZPrimeTree->truth_uHat,
                          PreZPrimeTree->pdf_pdgId1,
                          PreZPrimeTree->pdf_pdgId2,
                          PreZPrimeTree->born_lepton1_pdgid,
                          PreZPrimeTree->born_lepton2_pdgid,
                          SelectedEvent.born_CosThetaCS,
                          SelectedEvent.born_PhiCS,
                          SelectedEvent.born_dilepton_mass,
                          SelectedEvent.born_dilepton_pt,
                          fabs(SelectedEvent.born_dilepton_rapidity));
   SSMModel_7TeV->setModelParametersSSM("SSM");
   if(AngularFileName != "") SSMModel_7TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_SSM_7TeV = SSMModel_7TeV->getRWFactor();

   SSMModel_8TeV->execute(PreZPrimeTree->truth_sHat,
                          PreZPrimeTree->truth_tHat,
                          PreZPrimeTree->truth_uHat,
                          PreZPrimeTree->pdf_pdgId1,
                          PreZPrimeTree->pdf_pdgId2,
                          PreZPrimeTree->born_lepton1_pdgid,
                          PreZPrimeTree->born_lepton2_pdgid,
                          SelectedEvent.born_CosThetaCS,
                          SelectedEvent.born_PhiCS,
                          SelectedEvent.born_dilepton_mass,
                          SelectedEvent.born_dilepton_pt,
                          fabs(SelectedEvent.born_dilepton_rapidity));
   SSMModel_8TeV->setModelParametersSSM("SSM");
   if(AngularFileName != "") SSMModel_8TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_SSM_8TeV = SSMModel_8TeV->getRWFactor();

   E6ChiModel_0p5TeV->execute(PreZPrimeTree->truth_sHat,
                              PreZPrimeTree->truth_tHat,
                              PreZPrimeTree->truth_uHat,
                              PreZPrimeTree->pdf_pdgId1,
                              PreZPrimeTree->pdf_pdgId2,
                              PreZPrimeTree->born_lepton1_pdgid,
                              PreZPrimeTree->born_lepton2_pdgid,
                              SelectedEvent.born_CosThetaCS,
                              SelectedEvent.born_PhiCS,
                              SelectedEvent.born_dilepton_mass,
                              SelectedEvent.born_dilepton_pt,
                              fabs(SelectedEvent.born_dilepton_rapidity));
   E6ChiModel_0p5TeV->setModelParametersE6("Chi", 0.0);
   if(AngularFileName != "") E6ChiModel_0p5TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Chi_0p5TeV = E6ChiModel_0p5TeV->getRWFactor();

   E6ChiModel_0p6TeV->execute(PreZPrimeTree->truth_sHat,
                              PreZPrimeTree->truth_tHat,
                              PreZPrimeTree->truth_uHat,
                              PreZPrimeTree->pdf_pdgId1,
                              PreZPrimeTree->pdf_pdgId2,
                              PreZPrimeTree->born_lepton1_pdgid,
                              PreZPrimeTree->born_lepton2_pdgid,
                              SelectedEvent.born_CosThetaCS,
                              SelectedEvent.born_PhiCS,
                              SelectedEvent.born_dilepton_mass,
                              SelectedEvent.born_dilepton_pt,
                              fabs(SelectedEvent.born_dilepton_rapidity));
   E6ChiModel_0p6TeV->setModelParametersE6("Chi", 0.0);
   if(AngularFileName != "") E6ChiModel_0p6TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Chi_0p6TeV = E6ChiModel_0p6TeV->getRWFactor();

   E6ChiModel_0p8TeV->execute(PreZPrimeTree->truth_sHat,
                              PreZPrimeTree->truth_tHat,
                              PreZPrimeTree->truth_uHat,
                              PreZPrimeTree->pdf_pdgId1,
                              PreZPrimeTree->pdf_pdgId2,
                              PreZPrimeTree->born_lepton1_pdgid,
                              PreZPrimeTree->born_lepton2_pdgid,
                              SelectedEvent.born_CosThetaCS,
                              SelectedEvent.born_PhiCS,
                              SelectedEvent.born_dilepton_mass,
                              SelectedEvent.born_dilepton_pt,
                              fabs(SelectedEvent.born_dilepton_rapidity));
   E6ChiModel_0p8TeV->setModelParametersE6("Chi", 0.0);
   if(AngularFileName != "") E6ChiModel_0p8TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Chi_0p8TeV = E6ChiModel_0p8TeV->getRWFactor();

   E6ChiModel_1TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6ChiModel_1TeV->setModelParametersE6("Chi", 0.0);
   if(AngularFileName != "") E6ChiModel_1TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Chi_1TeV = E6ChiModel_1TeV->getRWFactor();

   E6ChiModel_2TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6ChiModel_2TeV->setModelParametersE6("Chi", 0.0);
   if(AngularFileName != "") E6ChiModel_2TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Chi_2TeV = E6ChiModel_2TeV->getRWFactor();

   E6ChiModel_3TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6ChiModel_3TeV->setModelParametersE6("Chi", 0.0);
   if(AngularFileName != "") E6ChiModel_3TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Chi_3TeV = E6ChiModel_3TeV->getRWFactor();

   E6ChiModel_4TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6ChiModel_4TeV->setModelParametersE6("Chi", 0.0);
   if(AngularFileName != "") E6ChiModel_4TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Chi_4TeV = E6ChiModel_4TeV->getRWFactor();

   E6ChiModel_5TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6ChiModel_5TeV->setModelParametersE6("Chi", 0.0);
   if(AngularFileName != "") E6ChiModel_5TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Chi_5TeV = E6ChiModel_5TeV->getRWFactor();

   E6ChiModel_6TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6ChiModel_6TeV->setModelParametersE6("Chi", 0.0);
   if(AngularFileName != "") E6ChiModel_6TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Chi_6TeV = E6ChiModel_6TeV->getRWFactor();

   E6ChiModel_7TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6ChiModel_7TeV->setModelParametersE6("Chi", 0.0);
   if(AngularFileName != "") E6ChiModel_7TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Chi_7TeV = E6ChiModel_7TeV->getRWFactor();

   E6ChiModel_8TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6ChiModel_8TeV->setModelParametersE6("Chi", 0.0);
   if(AngularFileName != "") E6ChiModel_8TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Chi_8TeV = E6ChiModel_8TeV->getRWFactor();

   E6PsiModel_0p5TeV->execute(PreZPrimeTree->truth_sHat,
                              PreZPrimeTree->truth_tHat,
                              PreZPrimeTree->truth_uHat,
                              PreZPrimeTree->pdf_pdgId1,
                              PreZPrimeTree->pdf_pdgId2,
                              PreZPrimeTree->born_lepton1_pdgid,
                              PreZPrimeTree->born_lepton2_pdgid,
                              SelectedEvent.born_CosThetaCS,
                              SelectedEvent.born_PhiCS,
                              SelectedEvent.born_dilepton_mass,
                              SelectedEvent.born_dilepton_pt,
                              fabs(SelectedEvent.born_dilepton_rapidity));
   E6PsiModel_0p5TeV->setModelParametersE6("Psi", 0.0);
   if(AngularFileName != "") E6PsiModel_0p5TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Psi_0p5TeV = E6PsiModel_0p5TeV->getRWFactor();

   E6PsiModel_0p6TeV->execute(PreZPrimeTree->truth_sHat,
                              PreZPrimeTree->truth_tHat,
                              PreZPrimeTree->truth_uHat,
                              PreZPrimeTree->pdf_pdgId1,
                              PreZPrimeTree->pdf_pdgId2,
                              PreZPrimeTree->born_lepton1_pdgid,
                              PreZPrimeTree->born_lepton2_pdgid,
                              SelectedEvent.born_CosThetaCS,
                              SelectedEvent.born_PhiCS,
                              SelectedEvent.born_dilepton_mass,
                              SelectedEvent.born_dilepton_pt,
                              fabs(SelectedEvent.born_dilepton_rapidity));
   E6PsiModel_0p6TeV->setModelParametersE6("Psi", 0.0);
   if(AngularFileName != "") E6PsiModel_0p6TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Psi_0p6TeV = E6PsiModel_0p6TeV->getRWFactor();

   E6PsiModel_0p8TeV->execute(PreZPrimeTree->truth_sHat,
                              PreZPrimeTree->truth_tHat,
                              PreZPrimeTree->truth_uHat,
                              PreZPrimeTree->pdf_pdgId1,
                              PreZPrimeTree->pdf_pdgId2,
                              PreZPrimeTree->born_lepton1_pdgid,
                              PreZPrimeTree->born_lepton2_pdgid,
                              SelectedEvent.born_CosThetaCS,
                              SelectedEvent.born_PhiCS,
                              SelectedEvent.born_dilepton_mass,
                              SelectedEvent.born_dilepton_pt,
                              fabs(SelectedEvent.born_dilepton_rapidity));
   E6PsiModel_0p8TeV->setModelParametersE6("Psi", 0.0);
   if(AngularFileName != "") E6PsiModel_0p8TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Psi_0p8TeV = E6PsiModel_0p8TeV->getRWFactor();

   E6PsiModel_1TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6PsiModel_1TeV->setModelParametersE6("Psi", 0.0);
   if(AngularFileName != "") E6PsiModel_1TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Psi_1TeV = E6PsiModel_1TeV->getRWFactor();

   E6PsiModel_2TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6PsiModel_2TeV->setModelParametersE6("Psi", 0.0);
   if(AngularFileName != "") E6PsiModel_2TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Psi_2TeV = E6PsiModel_2TeV->getRWFactor();

   E6PsiModel_3TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6PsiModel_3TeV->setModelParametersE6("Psi", 0.0);
   if(AngularFileName != "") E6PsiModel_3TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Psi_3TeV = E6PsiModel_3TeV->getRWFactor();

   E6PsiModel_4TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6PsiModel_4TeV->setModelParametersE6("Psi", 0.0);
   if(AngularFileName != "") E6PsiModel_4TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Psi_4TeV = E6PsiModel_4TeV->getRWFactor();

   E6PsiModel_5TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6PsiModel_5TeV->setModelParametersE6("Psi", 0.0);
   if(AngularFileName != "") E6PsiModel_5TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Psi_5TeV = E6PsiModel_5TeV->getRWFactor();

   E6PsiModel_6TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6PsiModel_6TeV->setModelParametersE6("Psi", 0.0);
   if(AngularFileName != "") E6PsiModel_6TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Psi_6TeV = E6PsiModel_6TeV->getRWFactor();

   E6PsiModel_7TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6PsiModel_7TeV->setModelParametersE6("Psi", 0.0);
   if(AngularFileName != "") E6PsiModel_7TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Psi_7TeV = E6PsiModel_7TeV->getRWFactor();

   E6PsiModel_8TeV->execute(PreZPrimeTree->truth_sHat,
                            PreZPrimeTree->truth_tHat,
                            PreZPrimeTree->truth_uHat,
                            PreZPrimeTree->pdf_pdgId1,
                            PreZPrimeTree->pdf_pdgId2,
                            PreZPrimeTree->born_lepton1_pdgid,
                            PreZPrimeTree->born_lepton2_pdgid,
                            SelectedEvent.born_CosThetaCS,
                            SelectedEvent.born_PhiCS,
                            SelectedEvent.born_dilepton_mass,
                            SelectedEvent.born_dilepton_pt,
                            fabs(SelectedEvent.born_dilepton_rapidity));
   E6PsiModel_8TeV->setModelParametersE6("Psi", 0.0);
   if(AngularFileName != "") E6PsiModel_8TeV->calcRWNLO();
   SelectedEvent.ReweightFactor_E6Psi_8TeV = E6PsiModel_8TeV->getRWFactor();
 }

 if(doApplyKFactor){
   //int bin = KFactorHist->FindBin(PreZPrimeTree->born_dilepton_m);
   //SelectedEvent.kfactor_nnlo = KFactorHist->GetBinContent(bin);
   //if(PreZPrimeTree->born_dilepton_m < 130.0) SelectedEvent.kfactor_nnlo = 1.0;
   //if(PreZPrimeTree->born_dilepton_m > 7000.0) SelectedEvent.kfactor_nnlo = 1.0;

   SelectedEvent.kfactor_nnlo = Zgamma_13p6TeV_CT18ANNLO_CT10_Central_spline(PreZPrimeTree->born_dilepton_m);

   SelectedEvent.kfactor_nnlo_up = Zgamma_13p6TeV_CT18ANNLO_CT10_Up_spline(PreZPrimeTree->born_dilepton_m);

   SelectedEvent.kfactor_nnlo_down = Zgamma_13p6TeV_CT18ANNLO_CT10_Down_spline(PreZPrimeTree->born_dilepton_m);

   SelectedEvent.kfactor_ew = (1.0 + ((ew_z_spline(PreZPrimeTree->born_dilepton_m) - 1.0) / Zgamma_CT10nnlo_CT10nnlo(PreZPrimeTree->born_dilepton_m)));
 }

 ZPrimeTree->ReweightFactor_SSM_0p5TeV = SelectedEvent.ReweightFactor_SSM_0p5TeV;
 ZPrimeTree->ReweightFactor_SSM_0p6TeV = SelectedEvent.ReweightFactor_SSM_0p6TeV;
 ZPrimeTree->ReweightFactor_SSM_0p8TeV = SelectedEvent.ReweightFactor_SSM_0p8TeV;
 ZPrimeTree->ReweightFactor_SSM_1TeV = SelectedEvent.ReweightFactor_SSM_1TeV;
 ZPrimeTree->ReweightFactor_SSM_2TeV = SelectedEvent.ReweightFactor_SSM_2TeV;
 ZPrimeTree->ReweightFactor_SSM_3TeV = SelectedEvent.ReweightFactor_SSM_3TeV;
 ZPrimeTree->ReweightFactor_SSM_4TeV = SelectedEvent.ReweightFactor_SSM_4TeV;
 ZPrimeTree->ReweightFactor_SSM_5TeV = SelectedEvent.ReweightFactor_SSM_5TeV;
 ZPrimeTree->ReweightFactor_SSM_6TeV = SelectedEvent.ReweightFactor_SSM_6TeV;
 ZPrimeTree->ReweightFactor_SSM_7TeV = SelectedEvent.ReweightFactor_SSM_7TeV;
 ZPrimeTree->ReweightFactor_SSM_8TeV = SelectedEvent.ReweightFactor_SSM_8TeV;

 ZPrimeTree->ReweightFactor_E6Chi_0p5TeV = SelectedEvent.ReweightFactor_E6Chi_0p5TeV;
 ZPrimeTree->ReweightFactor_E6Chi_0p6TeV = SelectedEvent.ReweightFactor_E6Chi_0p6TeV;
 ZPrimeTree->ReweightFactor_E6Chi_0p8TeV = SelectedEvent.ReweightFactor_E6Chi_0p8TeV;
 ZPrimeTree->ReweightFactor_E6Chi_1TeV = SelectedEvent.ReweightFactor_E6Chi_1TeV;
 ZPrimeTree->ReweightFactor_E6Chi_2TeV = SelectedEvent.ReweightFactor_E6Chi_2TeV;
 ZPrimeTree->ReweightFactor_E6Chi_3TeV = SelectedEvent.ReweightFactor_E6Chi_3TeV;
 ZPrimeTree->ReweightFactor_E6Chi_4TeV = SelectedEvent.ReweightFactor_E6Chi_4TeV;
 ZPrimeTree->ReweightFactor_E6Chi_5TeV = SelectedEvent.ReweightFactor_E6Chi_5TeV;
 ZPrimeTree->ReweightFactor_E6Chi_6TeV = SelectedEvent.ReweightFactor_E6Chi_6TeV;
 ZPrimeTree->ReweightFactor_E6Chi_7TeV = SelectedEvent.ReweightFactor_E6Chi_7TeV;
 ZPrimeTree->ReweightFactor_E6Chi_8TeV = SelectedEvent.ReweightFactor_E6Chi_8TeV;

 ZPrimeTree->ReweightFactor_E6Psi_0p5TeV = SelectedEvent.ReweightFactor_E6Psi_0p5TeV;
 ZPrimeTree->ReweightFactor_E6Psi_0p6TeV = SelectedEvent.ReweightFactor_E6Psi_0p6TeV;
 ZPrimeTree->ReweightFactor_E6Psi_0p8TeV = SelectedEvent.ReweightFactor_E6Psi_0p8TeV;
 ZPrimeTree->ReweightFactor_E6Psi_1TeV = SelectedEvent.ReweightFactor_E6Psi_1TeV;
 ZPrimeTree->ReweightFactor_E6Psi_2TeV = SelectedEvent.ReweightFactor_E6Psi_2TeV;
 ZPrimeTree->ReweightFactor_E6Psi_3TeV = SelectedEvent.ReweightFactor_E6Psi_3TeV;
 ZPrimeTree->ReweightFactor_E6Psi_4TeV = SelectedEvent.ReweightFactor_E6Psi_4TeV;
 ZPrimeTree->ReweightFactor_E6Psi_5TeV = SelectedEvent.ReweightFactor_E6Psi_5TeV;
 ZPrimeTree->ReweightFactor_E6Psi_6TeV = SelectedEvent.ReweightFactor_E6Psi_6TeV;
 ZPrimeTree->ReweightFactor_E6Psi_7TeV = SelectedEvent.ReweightFactor_E6Psi_7TeV;
 ZPrimeTree->ReweightFactor_E6Psi_8TeV = SelectedEvent.ReweightFactor_E6Psi_8TeV;

 ZPrimeTree->kfactor_nnlo = SelectedEvent.kfactor_nnlo;
 ZPrimeTree->kfactor_nnlo_up = SelectedEvent.kfactor_nnlo_up;
 ZPrimeTree->kfactor_nnlo_down = SelectedEvent.kfactor_nnlo_down;
 ZPrimeTree->kfactor_ew = SelectedEvent.kfactor_ew;

 ElectronIndex.clear();
 MuonIndex.clear();

 return true;
}

double loopZPrime::GetGlobalTriggerSF(int randomRunNumber, double el1_pt, double el1_eta, double el2_pt, double el2_eta)
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

void EventZPrime::ResetEvent()
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
 RandomRunNumber = -999;
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

 passElTrigger = 0;
 passMuTrigger = 0;

 Lepton1_FakeRate = -999.0;
 Lepton2_FakeRate = -999.0;

 isElSample = false;
 isMuSample = false;

 isZeeIncOverlap = false;

 born_lepton1_E = -999.0;
 born_lepton1_pt = -999.0;
 born_lepton1_eta = -999.0;
 born_lepton1_phi = -999.0;
 born_lepton1_pdgid = 0;
 born_lepton2_E = -999.0;
 born_lepton2_pt = -999.0;
 born_lepton2_eta = -999.0;
 born_lepton2_phi = -999.0;
 born_lepton2_pdgid = 0;
 pdf_pdgId1 = 0;
 pdf_pdgId2 = 0;
 n_born_lepton = 0;
 born_CosThetaCS = 0.0;
 born_PhiCS = 0.0;
 born_dilepton_mass = -999.0;
 born_dilepton_pt = -999.0;
 born_dilepton_rapidity = -999.0;

 ReweightFactor_SSM_0p5TeV = -999.0;
 ReweightFactor_SSM_0p6TeV = -999.0;
 ReweightFactor_SSM_0p8TeV = -999.0;
 ReweightFactor_SSM_1TeV = -999.0;
 ReweightFactor_SSM_2TeV = -999.0;
 ReweightFactor_SSM_3TeV = -999.0;
 ReweightFactor_SSM_4TeV = -999.0;
 ReweightFactor_SSM_5TeV = -999.0;
 ReweightFactor_SSM_6TeV = -999.0;
 ReweightFactor_SSM_7TeV = -999.0;
 ReweightFactor_SSM_8TeV = -999.0;

 ReweightFactor_E6Chi_0p5TeV = -999.0;
 ReweightFactor_E6Chi_0p6TeV = -999.0;
 ReweightFactor_E6Chi_0p8TeV = -999.0;
 ReweightFactor_E6Chi_1TeV = -999.0;
 ReweightFactor_E6Chi_2TeV = -999.0;
 ReweightFactor_E6Chi_3TeV = -999.0;
 ReweightFactor_E6Chi_4TeV = -999.0;
 ReweightFactor_E6Chi_5TeV = -999.0;
 ReweightFactor_E6Chi_6TeV = -999.0;
 ReweightFactor_E6Chi_7TeV = -999.0;
 ReweightFactor_E6Chi_8TeV = -999.0;

 ReweightFactor_E6Psi_0p5TeV = -999.0;
 ReweightFactor_E6Psi_0p6TeV = -999.0;
 ReweightFactor_E6Psi_0p8TeV = -999.0;
 ReweightFactor_E6Psi_1TeV = -999.0;
 ReweightFactor_E6Psi_2TeV = -999.0;
 ReweightFactor_E6Psi_3TeV = -999.0;
 ReweightFactor_E6Psi_4TeV = -999.0;
 ReweightFactor_E6Psi_5TeV = -999.0;
 ReweightFactor_E6Psi_6TeV = -999.0;
 ReweightFactor_E6Psi_7TeV = -999.0;
 ReweightFactor_E6Psi_8TeV = -999.0;

 kfactor_nnlo = 1.0;
 kfactor_nnlo_up = 1.0;
 kfactor_nnlo_down = 1.0;
 kfactor_ew = 1.0;
}

void ZPrimeLepton::ResetEvent()
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

void loopZPrime::End(int RootNumber)
{
 cout<<"\r"<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<"  "<<flush;//yfu

 if(!isInputPreTree){
   if(!ZPrimeTree->fChain[RootNumber])
    {
     cout<<"XXXXX**Runing: BIG ERROR!!! No File loaded!"<<endl;
     return;
    }
   ZPrimeTree->CloseFile(RootNumber);
   delete ZPrimeTree->fChain[RootNumber]->GetCurrentFile();
 }

 if(isInputPreTree){
   if(!PreZPrimeTree->fChain[RootNumber])
    {
     cout<<"XXXXX**Runing: BIG ERROR!!! No File loaded!"<<endl;
     return;
    }
   PreZPrimeTree->CloseFile(RootNumber);
   delete PreZPrimeTree->fChain[RootNumber]->GetCurrentFile();
 }
}

void loopZPrime::Finish()
{
 myLog<<LOG_INFO<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(!isInputPreTree){
   if(EndFile == RootNames.size()) delete ZPrimeTree;
 }

 if(isInputPreTree){
   if(EndFile == RootNames.size()) delete PreZPrimeTree;
 }

 if(JustGenerateTree){
   ZPrimeTree->SaveFile();
 }

 //for multi-run the loop function
 if(isInputPreTree){
   delete ZPrimeTree;
 }

}

loopZPrime::~loopZPrime()
{
}


