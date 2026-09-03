#define loopWZPolarization_cxx
#include <iostream>
#include "WZPolarization/loopWZPolarization.h"

using namespace std;

loopWZPolarization::loopWZPolarization(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopWZPolarization::InputHist(HistsWZPolarization* &myhists)
{
 this->myhists = myhists;

 this->OnlyNominal = myhists->OnlyNominal;
 this->SysNameIndex = myhists->SysNameIndexSignalWZ;//initialize systematic name by hand, otherwise automatically defined in TreeForPreWZPolarization.C
 this->SystematicName = myhists->SystematicName;
 this->doBkg = myhists->doBkg;
 this->doControlRegion = myhists->doControlRegion;
 this->doFakeRate = myhists->doFakeRate;
 this->isHaveFakeRate = myhists->isHaveFakeRate;
 this->isHaveReweightingFactor = myhists->isHaveReweightingFactor;
 if(isNormalizedNLO) this->NLOKFactor = myhists->NLOKFactor;
 if(isNormalizedNLO) this->NLOKFactor_ZZCR = myhists->NLOKFactor_ZZCR;
 if(isNormalizedNLO) this->NLOKFactor_HighPtZCR = myhists->NLOKFactor_HighPtZCR;
 if(isNormalizedNLO) this->NLOKFactor_Signal = myhists->NLOKFactor_Signal;
 if(isNormalizedNLO) this->NLOKFactor_SignalPtWZ = myhists->NLOKFactor_SignalPtWZ;
 if(isNormalizedNLO) this->NLOKFactor_HighPtWZCR = myhists->NLOKFactor_HighPtWZCR;
 if(isNormalizedNLO) this->NLOKFactor_LowPtWZCR = myhists->NLOKFactor_LowPtWZCR;
 if(isNormalizedNLO) this->NLOKFactor_HighR21CR = myhists->NLOKFactor_HighR21CR;
 if(isNormalizedNLO) this->NLOKFactor_LowR21CR = myhists->NLOKFactor_LowR21CR;
 if(isNormalizedNLO){
   for(int iprocesshist = 0; iprocesshist < myhists->hist_process.size(); iprocesshist++){
     myhists->hist_process.at(iprocesshist)->InputNLOKFactor(NLOKFactor, NLOKFactor_ZZCR, NLOKFactor_HighPtZCR, NLOKFactor_Signal, NLOKFactor_SignalPtWZ,
                                                             NLOKFactor_HighPtWZCR, NLOKFactor_LowPtWZCR, NLOKFactor_HighR21CR, NLOKFactor_LowR21CR);
   }
 }

 if(this->isHaveFakeRate) myFakeRate = new DataDriven();
 if(this->isHaveFakeRate && this->doFakeRate == 1) myFakeRate->InputFakeRate(myhists->ZElFakeRate, myhists->ZMuFakeRate, myhists->WElFakeRate, myhists->WMuFakeRate);
// if(this->isHaveFakeRate && this->doFakeRate == 1) myFakeRate->InputFakeRate(myhists->ZFakeElCR_ZRate, myhists->ZFakeMuCR_ZRate, myhists->WElFakeRate, myhists->WMuFakeRate);
// if(this->isHaveFakeRate && this->doFakeRate == 1) myFakeRate->InputFakeRate(myhists->ZFakeElCR_UpSys_ZRate, myhists->ZFakeMuCR_ZRate, myhists->WElFakeRate_UpSys, myhists->WMuFakeRate);
// if(this->isHaveFakeRate && this->doFakeRate == 1) myFakeRate->InputFakeRate(myhists->ZFakeElCR_DownSys_ZRate, myhists->ZFakeMuCR_ZRate, myhists->WElFakeRate_DownSys, myhists->WMuFakeRate);
// if(this->isHaveFakeRate && this->doFakeRate == 1) myFakeRate->InputUpSysFakeRate(myhists->ZFakeElCR_UpSys_ZRate, myhists->ZFakeMuCR_ZRate, myhists->WElFakeRate_UpSys, myhists->WMuFakeRate);
// if(this->isHaveFakeRate && this->doFakeRate == 1) myFakeRate->InputDownSysFakeRate(myhists->ZFakeElCR_DownSys_ZRate, myhists->ZFakeMuCR_ZRate, myhists->WElFakeRate_DownSys, myhists->WMuFakeRate);

// if(this->isHaveFakeRate && this->doFakeRate == 1) myFakeRate->InputFakeRate(myhists->ZElFakeRate, myhists->ZMuFakeRate, myhists->TopElCR_WRate, myhists->TopMuCR_WRate);


 if(this->isHaveFakeRate) myFakeRate_ValidationZ = new DataDriven();
 //if(this->isHaveFakeRate && this->doFakeRate == 1) myFakeRate_ValidationZ->InputFakeRate(myhists->TopElCR_ZRate, myhists->TopMuCR_ZRate, myhists->TopElCR_ZRate, myhists->TopMuCR_ZRate);
 if(this->isHaveFakeRate) myFakeRate_ValidationW = new DataDriven();
 //if(this->isHaveFakeRate && this->doFakeRate == 1) myFakeRate_ValidationW->InputFakeRate(myhists->ZFakeElCR_WRate, myhists->ZFakeMuCR_WRate, myhists->ZFakeElCR_WRate, myhists->ZFakeMuCR_WRate);

}

void loopWZPolarization::InputTree(TreeForWZPolarization *WZPolarizationTree)
{
 this->WZPolarizationTree = WZPolarizationTree;
 this->RootNames = WZPolarizationTree->RootNames;

 this->FirstFile = WZPolarizationTree->FirstFile;
 this->EndFile = WZPolarizationTree->EndFile;

 this->RootTypes = WZPolarizationTree->RootTypes;

 this->doRunPDFAndQCDUnc = WZPolarizationTree->doRunPDFAndQCDUnc;
 this->ErrorType = WZPolarizationTree->ErrorType;
 this->ErrorSet = WZPolarizationTree->ErrorSet;

 this->OneFilePerJob = WZPolarizationTree->OneFilePerJob;

 ///////////////////////////////////////////////////////////////////////////////////////////////
 //  Here, only TotalEntriesSys[ifile][isys] are retrieved from the TreeForWZPolarization     //
 //  Since only one tree will be initialized, the entries of the rest tree will all be zero.  //
 ///////////////////////////////////////////////////////////////////////////////////////////////

 int isys = -1;
 map<TString, int>::iterator sysIter;
 for(sysIter = SysNameIndex.begin(); sysIter != SysNameIndex.end(); sysIter++){
   isys = sysIter->second;

   for(int ifile = FirstFile; ifile < EndFile; ifile++){
     TotalEntriesSys[ifile][isys] = WZPolarizationTree->TotalEntries[ifile][isys];
   }
 }

}

void loopWZPolarization::InputTree(TreeForPreWZPolarization *PreWZPolarizationTree)
{
 isInputPreTree = true;

 this->PreWZPolarizationTree = PreWZPolarizationTree;
 this->RootNames = PreWZPolarizationTree->RootNames;

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 //initialize systematic name automatically by TreeForPreWZPolarization.C, otherwise defined by hand

 //this->SysNameIndex = PreWZPolarizationTree->SysNameIndexSignalWZ;
 //myhists->SysNameIndexSignalWZ = PreWZPolarizationTree->SysNameIndexSignalWZ;
 ////////////////////////////////////////////////////////////////////////////////////////////////////

 this->FirstFile = PreWZPolarizationTree->FirstFile;
 this->EndFile = PreWZPolarizationTree->EndFile;
 
 this->RootTypes = PreWZPolarizationTree->RootTypes;
 this->CrossSections = PreWZPolarizationTree->CrossSections;
 this->SumOfWeights = PreWZPolarizationTree->SumOfWeights;
 this->Lumi1516 = PreWZPolarizationTree->Lumi1516;
 this->Lumi17 = PreWZPolarizationTree->Lumi17;
 this->Lumi18 = PreWZPolarizationTree->Lumi18;

 this->Years = PreWZPolarizationTree->Years;
 this->UniqueYears = PreWZPolarizationTree->UniqueYears;

 this->SumOfWeightsMap = PreWZPolarizationTree->SumOfWeightsMap;
 this->TheoryErrorType = PreWZPolarizationTree->TheoryErrorType;
 
 this->OneFilePerJob = PreWZPolarizationTree->OneFilePerJob;

 this->doTruthSelection = PreWZPolarizationTree->doTruthSelection;
 
 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = PreWZPolarizationTree->TotalEntries[ifile];
 }

// save the tree
 this->WZPolarizationTree = new TreeForWZPolarization();
 if(JustGenerateTree){
   if(!NtupleName.Contains("root")) NtupleName = PreWZPolarizationTree->SaveName;
   this->WZPolarizationTree->GenerateFile(NtupleName);

   /////////////////////////////////////////////////////////////
   //  SysNameIndex is defined in HistsWZPolarization.C(old)  //
   //  SysNameIndex is defined in TreeForPreWZPolarization.C  //
   //  Here, initialize all the systematic trees              //
   //  according to the name defined in the SysNameIndex      //
   /////////////////////////////////////////////////////////////

   map<TString, int>::iterator sysIter;
   for(sysIter = SysNameIndex.begin(); sysIter != SysNameIndex.end(); sysIter++){
     if(RootTypes.at(0) == -1 && sysIter->first != "nominal") continue;

     if((OnlyNominal && sysIter->first == "nominal") || (!OnlyNominal)) this->WZPolarizationTree->DefineTree(sysIter->second, sysIter->first);
   }

   if(RootTypes.at(0) != -1) this->WZPolarizationTree->DefineTruthTree();
 }
}

void loopWZPolarization::InputNtupleName(TString NtupleName)
{
//this name will be override by the automatic name
 this->NtupleName = NtupleName;
}

void loopWZPolarization::RunAllSystematic()
{
 OnlyNominal = false;
}

void loopWZPolarization::GetFullFakeMatrix()
{
 if(isHaveFakeRate && doFakeRate == 2){
   myFakeRate->InputFakeEfficiency(myhists->ZElFakeEff, myhists->ZMuFakeEff, myhists->WElFakeEff, myhists->WMuFakeEff);
   myFakeRate->InputRealEfficiency(myhists->ZElRealEff, myhists->ZMuRealEff, myhists->WElRealEff, myhists->WMuRealEff);

   myFakeRate->GetMatrix(iThread);

   cout<<"Finished to calculate all inverse fake matrix."<<endl;
 }

}

void loopWZPolarization::InitialTMVA(TString FileName)
{
 isBDT = true;

 cout<<"Initialize TMVA Tool:"<<endl;

 reader = new TMVAHelper();
 reader->InputTree(WZPolarizationTree);
 reader->AddVariable();
 reader->BookMVA(FileName);

}

void loopWZPolarization::InitialTMVASR(TString FileName)
{
 isBDTSR = true;

 cout<<"Initialize TMVA Tool for SR:"<<endl;

 readerSR = new TMVAHelper();
 readerSR->InputTree(WZPolarizationTree);
 readerSR->AddVariableSR();
 readerSR->BookMVA(FileName);

}

void loopWZPolarization::InitialTMVASR_NoPtV(TString FileName)
{
  isBDTSR = true;

  cout<<"Initialize TMVA Tool for SR without PtV variables in BDT:"<<endl;

  readerSR = new TMVAHelper();
  readerSR->InputTree(WZPolarizationTree);
  readerSR->AddVariableSR_NoPtV();
  readerSR->BookMVA(FileName);

}

void loopWZPolarization::InitialTMVASR_OnlyDec(TString FileName)
{
  isBDTSR = true;

  cout<<"Initialize TMVA Tool for SR with only W and Z lepton decay angles in BDT:"<<endl;

  readerSR = new TMVAHelper();
  readerSR->InputTree(WZPolarizationTree);
  readerSR->AddVariableSR_OnlyDec();
  readerSR->BookMVA(FileName);

}

void loopWZPolarization::InitialTMVASR100(TString FileName)
{
 isBDTSR100 = true;

 cout<<"Initialize TMVA Tool for SR(PtZ > 100GeV):"<<endl;

 readerSR100 = new TMVAHelper();
 readerSR100->InputTree(WZPolarizationTree);
 readerSR100->AddVariableSR100();
 readerSR100->BookMVA(FileName);

}

void loopWZPolarization::InitialTMVASR100_NoPtV(TString FileName)
{
  isBDTSR100 = true;

  cout<<"Initialize TMVA Tool for SR100 without PtV variables in BDT:"<<endl;

  readerSR100 = new TMVAHelper();
  readerSR100->InputTree(WZPolarizationTree);
  readerSR100->AddVariableSR100_NoPtV();
  readerSR100->BookMVA(FileName);

}

void loopWZPolarization::InitialTMVASR100_OnlyDec(TString FileName)
{
  isBDTSR100 = true;

  cout<<"Initialize TMVA Tool for SR100 with only W and Z lepton decay angles in BDT:"<<endl;

  readerSR100 = new TMVAHelper();
  readerSR100->InputTree(WZPolarizationTree);
  readerSR100->AddVariableSR100_OnlyDec();
  readerSR100->BookMVA(FileName);

}

void loopWZPolarization::InitialLWTNNNuPz(TString EvenFile, TString OddFile)
{
 isLWTNNNuPz = true;

 LwtnnNuPz = new LWTNNHelper();
 LwtnnNuPz->Initialize(EvenFile, OddFile);
}

void loopWZPolarization::InitialLWTNNPolClassifier(TString EvenFile, TString OddFile)
{
 isLWTNNPolClassifier = true;

 LwtnnPolClassifier = new LWTNNHelper();
 LwtnnPolClassifier->InitializePolClassifier(EvenFile, OddFile);
}

void loopWZPolarization::InitialLWTNNNLOPol(TString LLFile, TString LTFile, TString TLFile, TString TTFile)
{
 isLWTNNNLOPol = true;

 LwtnnNLOPol = new LWTNNHelper();
 LwtnnNLOPol->InitializeNLOPol(LLFile, LTFile, TLFile, TTFile);
}

void loopWZPolarization::ReadTree(int ifile)
{

   ////////////////////////////////////////////////////////////////
   //  Same as what has been done in TreeForWZPolarization       //
   //  Only one tree will be looped.                             //
   //  The SystematicName must be defined in the SysNameIndex    //
   //  Except the systematic relative to the fake background     //
   //  (eg: FakeBkg_MetCut_1up)                                  //
   //  (In this case, the nominal tree will be initialized)      //
   ////////////////////////////////////////////////////////////////


 SavedSystematicName = SystematicName;
 if(SystematicName.Contains("FakeBkg")) SavedSystematicName = "nominal";

 if(RootTypes.at(ifile) == -1 && SavedSystematicName != "nominal"){
   cout<<"INFO: move to the nominal tree for data."<<endl;
   SavedSystematicName = "nominal";
 }

 int isys = -1;
 map<TString, int>::iterator sysIter;
 for(sysIter = SysNameIndex.begin(); sysIter != SysNameIndex.end(); sysIter++){
   isys = sysIter->second;

   if(SystematicName == ""){
     if(OnlyNominal && isys != 0) continue;
   }
   else{
     if(sysIter->first != SavedSystematicName) continue;
   }

   RunningSys = isys;

   int MCType = RootTypes.at(ifile);
   if(isTest) cout<<MCType<<endl;

   //////////////////////////////////////
   //   Initial Background histogram   //
   //////////////////////////////////////

   for(int ibkghist = 0; ibkghist < myhists->BkgHist_1d.size(); ibkghist++){
     myhists->BkgHist_1d.at(ibkghist)->HistPtr(iThread - 1)->Initial(MCType);
     if(myhists->BkgHist_1d.at(ibkghist)->HistPtr(iThread - 1)->ProcessName == "SignalWZ") BkgShortName = myhists->BkgHist_1d.at(ibkghist)->HistPtr(iThread - 1)->ShortName;
   }

   for(int iprocesshist = 0; iprocesshist < myhists->hist_process.size(); iprocesshist++){
     myhists->hist_process.at(iprocesshist)->Initial(iThread, MCType);
     myhists->hist_process.at(iprocesshist)->InputNLOKFactor(NLOKFactor, NLOKFactor_ZZCR, NLOKFactor_HighPtZCR, NLOKFactor_Signal, NLOKFactor_SignalPtWZ,
                                                             NLOKFactor_HighPtWZCR, NLOKFactor_LowPtWZCR, NLOKFactor_HighR21CR, NLOKFactor_LowR21CR);
   }

   if(this->isHaveFakeRate){
     if(SystematicName == "FakeBkg_Stat__1up") myFakeRate->RunUpStat();
     if(SystematicName == "FakeBkg_Stat__1down") myFakeRate->RunDownStat();

     for(int ihist = 0; ihist < myhists->FakeHist_1d.size(); ihist++){
       myhists->FakeHist_1d.at(ihist)->HistPtr(iThread - 1)->LinkFakeRate(myFakeRate);
     }
     //for(int iprocesshist = 0; iprocesshist < myhists->hist_process.size(); iprocesshist++){
       //myhists->hist_process.at(iprocesshist)->v_TopEnrichCR_Fake.at(iThread - 1)->LinkFakeRate(myFakeRate_ValidationZ);
       //myhists->hist_process.at(iprocesshist)->v_WZInclusiveNoMETCR_Fake.at(iThread - 1)->LinkFakeRate(myFakeRate_ValidationW);
     //}
   }

   ////////////////////
   //   Loop Event   //
   ////////////////////

   for(long iEvent = InitialEntrySys[RunningSys] - 1; iEvent < NentriesSys[RunningSys]; iEvent++){
     Sta_TotalNumber++;
     if(isTest) cout<<"\r"<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event. "<<flush;

     if(Sta_TotalNumber % 1000000 == 0){ 
       if(isThread) cout<<"\r"<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished. "<<flush;
       if(!isThread) cout<<"\r"<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished. "<<flush;//yfu
     }
  
     WZPolarizationTree->GetEntry(ifile, RunningSys, iEvent);

     DefaultEvent.MCType = MCType;
     DefaultEvent.DecayChannel = WZPolarizationTree->Flavor;
     DefaultEvent.Yields = WZPolarizationTree->Yields;
     DefaultEvent.isMC = WZPolarizationTree->isMC;
     DefaultEvent.Channel = WZPolarizationTree->Channel;
     DefaultEvent.Year = WZPolarizationTree->Year;
     DefaultEvent.NormSF = WZPolarizationTree->NormSF;
     DefaultEvent.WeightSign = WZPolarizationTree->WeightSign;
     DefaultEvent.WeightNormalized = WZPolarizationTree->WeightNormalized;
     DefaultEvent.Weight = WZPolarizationTree->Weight;
     DefaultEvent.TotalWeight = WZPolarizationTree->TotalWeight;
     DefaultEvent.WeightNormalizedNoKFactor = WZPolarizationTree->WeightNormalizedNoKFactor;
     DefaultEvent.WeightNoKFactor = WZPolarizationTree->WeightNoKFactor;
     DefaultEvent.TotalWeightNoKFactor = WZPolarizationTree->TotalWeightNoKFactor;
     DefaultEvent.M_WZ = WZPolarizationTree->M_WZ;
     DefaultEvent.M_3l = WZPolarizationTree->M_3l;
     DefaultEvent.Mt_WZ = WZPolarizationTree->Mt_WZ;
     DefaultEvent.M_Z = WZPolarizationTree->M_Z;
     DefaultEvent.Mt_W = WZPolarizationTree->Mt_W;
     DefaultEvent.Met = WZPolarizationTree->Met;
     DefaultEvent.Njets = WZPolarizationTree->Njets;
     DefaultEvent.NBjets = WZPolarizationTree->NBjets;
     DefaultEvent.SumOfWeight = WZPolarizationTree->SumOfWeight;
     DefaultEvent.Luminosity = WZPolarizationTree->Luminosity;
     DefaultEvent.CrossSection = WZPolarizationTree->CrossSection;
     DefaultEvent.Lep1Pt = WZPolarizationTree->Lep1Pt;
     DefaultEvent.Lep2Pt = WZPolarizationTree->Lep2Pt;
     DefaultEvent.Lep3Pt = WZPolarizationTree->Lep3Pt;
     DefaultEvent.Lep1Eta = WZPolarizationTree->Lep1Eta;
     DefaultEvent.Lep2Eta = WZPolarizationTree->Lep2Eta;
     DefaultEvent.Lep3Eta = WZPolarizationTree->Lep3Eta;
     DefaultEvent.Lep1Phi = WZPolarizationTree->Lep1Phi;
     DefaultEvent.Lep2Phi = WZPolarizationTree->Lep2Phi;
     DefaultEvent.Lep3Phi = WZPolarizationTree->Lep3Phi;
     DefaultEvent.Lep1Flavor = WZPolarizationTree->Lep1Flavor;
     DefaultEvent.Lep2Flavor = WZPolarizationTree->Lep2Flavor;
     DefaultEvent.Lep3Flavor = WZPolarizationTree->Lep3Flavor;
     DefaultEvent.Lep1Charge = WZPolarizationTree->Lep1Charge;
     DefaultEvent.Lep2Charge = WZPolarizationTree->Lep2Charge;
     DefaultEvent.Lep3Charge = WZPolarizationTree->Lep3Charge;
     DefaultEvent.Lep1Ambiguity = WZPolarizationTree->Lep1Ambiguity;
     DefaultEvent.Lep2Ambiguity = WZPolarizationTree->Lep2Ambiguity;
     DefaultEvent.Lep3Ambiguity = WZPolarizationTree->Lep3Ambiguity;
     DefaultEvent.TruthLep1Pt = WZPolarizationTree->TruthLep1Pt;
     DefaultEvent.TruthLep2Pt = WZPolarizationTree->TruthLep2Pt;
     DefaultEvent.TruthLep3Pt = WZPolarizationTree->TruthLep3Pt;
     DefaultEvent.TruthLep1Eta = WZPolarizationTree->TruthLep1Eta;
     DefaultEvent.TruthLep2Eta = WZPolarizationTree->TruthLep2Eta;
     DefaultEvent.TruthLep3Eta = WZPolarizationTree->TruthLep3Eta;
     DefaultEvent.TruthLep1Phi = WZPolarizationTree->TruthLep1Phi;
     DefaultEvent.TruthLep2Phi = WZPolarizationTree->TruthLep2Phi;
     DefaultEvent.TruthLep3Phi = WZPolarizationTree->TruthLep3Phi;
     DefaultEvent.TruthLep1Flavor = WZPolarizationTree->TruthLep1Flavor;
     DefaultEvent.TruthLep2Flavor = WZPolarizationTree->TruthLep2Flavor;
     DefaultEvent.TruthLep3Flavor = WZPolarizationTree->TruthLep3Flavor;
     DefaultEvent.Mpx = WZPolarizationTree->Mpx;
     DefaultEvent.Mpy = WZPolarizationTree->Mpy;
     DefaultEvent.Mpz = WZPolarizationTree->Mpz;
     DefaultEvent.LWTNNNuPz = WZPolarizationTree->LWTNNNuPz;
     DefaultEvent.TruthNuPz = WZPolarizationTree->TruthNuPz;
     DefaultEvent.LWTNNpLL = WZPolarizationTree->LWTNNpLL;
     DefaultEvent.LWTNNpLT = WZPolarizationTree->LWTNNpLT;
     DefaultEvent.LWTNNpTL = WZPolarizationTree->LWTNNpTL;
     DefaultEvent.LWTNNpTT = WZPolarizationTree->LWTNNpTT;
     DefaultEvent.LLNLOWeight = WZPolarizationTree->LLNLOWeight;
     DefaultEvent.LTNLOWeight = WZPolarizationTree->LTNLOWeight;
     DefaultEvent.TLNLOWeight = WZPolarizationTree->TLNLOWeight;
     DefaultEvent.TTNLOWeight = WZPolarizationTree->TTNLOWeight;
     DefaultEvent.Lep1WeightZ = WZPolarizationTree->Lep1WeightZ;
     DefaultEvent.Lep2WeightZ = WZPolarizationTree->Lep2WeightZ;
     DefaultEvent.Lep3WeightZ = WZPolarizationTree->Lep3WeightZ;
     DefaultEvent.Lep1WeightW = WZPolarizationTree->Lep1WeightW;
     DefaultEvent.Lep2WeightW = WZPolarizationTree->Lep2WeightW;
     DefaultEvent.Lep3WeightW = WZPolarizationTree->Lep3WeightW;
     DefaultEvent.Pt_W = WZPolarizationTree->Pt_W;
     DefaultEvent.Pt_Z = WZPolarizationTree->Pt_Z;
     DefaultEvent.Pt_WZ = WZPolarizationTree->Pt_WZ;
     DefaultEvent.SumJetPt = WZPolarizationTree->SumJetPt;
     DefaultEvent.CosThetaV = WZPolarizationTree->CosThetaV;
     DefaultEvent.CosThetaLepW = WZPolarizationTree->CosThetaLepW;
     DefaultEvent.CosThetaLepZ = WZPolarizationTree->CosThetaLepZ;
     DefaultEvent.DY_WZ = WZPolarizationTree->DY_WZ;
     DefaultEvent.DY_3Z = WZPolarizationTree->DY_3Z;
     DefaultEvent.DY_3N = WZPolarizationTree->DY_3N;
     DefaultEvent.DeltaPhiLepWLepZ = WZPolarizationTree->DeltaPhiLepWLepZ;
     DefaultEvent.DeltaPhiLepWLepZWZFrame = WZPolarizationTree->DeltaPhiLepWLepZWZFrame;
     DefaultEvent.R21 = WZPolarizationTree->R21;
     DefaultEvent.WLepPt = WZPolarizationTree->WLepPt;
     DefaultEvent.ZLeadingLepPt = WZPolarizationTree->ZLeadingLepPt;
     DefaultEvent.ZSubleadingLepPt = WZPolarizationTree->ZSubleadingLepPt;
     DefaultEvent.WLepEta = WZPolarizationTree->WLepEta;
     DefaultEvent.ZLeadingLepEta = WZPolarizationTree->ZLeadingLepEta;
     DefaultEvent.ZSubleadingLepEta = WZPolarizationTree->ZSubleadingLepEta;
     DefaultEvent.WLepPhi = WZPolarizationTree->WLepPhi;
     DefaultEvent.ZLeadingLepPhi = WZPolarizationTree->ZLeadingLepPhi;
     DefaultEvent.ZSubleadingLepPhi = WZPolarizationTree->ZSubleadingLepPhi;

     DefaultEvent.Lep1MediumIDWeight = WZPolarizationTree->Lep1MediumIDWeight;
     DefaultEvent.Lep2MediumIDWeight = WZPolarizationTree->Lep2MediumIDWeight;
     DefaultEvent.Lep3MediumIDWeight = WZPolarizationTree->Lep3MediumIDWeight;
     DefaultEvent.Lep1TightIDWeight = WZPolarizationTree->Lep1TightIDWeight;
     DefaultEvent.Lep2TightIDWeight = WZPolarizationTree->Lep2TightIDWeight;
     DefaultEvent.Lep3TightIDWeight = WZPolarizationTree->Lep3TightIDWeight;
     DefaultEvent.Lep1MediumIsoWeight = WZPolarizationTree->Lep1MediumIsoWeight;
     DefaultEvent.Lep2MediumIsoWeight = WZPolarizationTree->Lep2MediumIsoWeight;
     DefaultEvent.Lep3MediumIsoWeight = WZPolarizationTree->Lep3MediumIsoWeight;
     DefaultEvent.Lep1TightIsoWeight = WZPolarizationTree->Lep1TightIsoWeight;
     DefaultEvent.Lep2TightIsoWeight = WZPolarizationTree->Lep2TightIsoWeight;
     DefaultEvent.Lep3TightIsoWeight = WZPolarizationTree->Lep3TightIsoWeight;

     DefaultEvent.passZZCR = WZPolarizationTree->passZZCR;
     DefaultEvent.passTopCR = WZPolarizationTree->passTopCR;
     DefaultEvent.passZFakeElCR = WZPolarizationTree->passZFakeElCR;
     DefaultEvent.passZFakeElCR_UpSys = WZPolarizationTree->passZFakeElCR_UpSys;
     DefaultEvent.passZFakeElCR_DownSys = WZPolarizationTree->passZFakeElCR_DownSys;
     DefaultEvent.passZFakeMuCR = WZPolarizationTree->passZFakeMuCR;
     DefaultEvent.passTopElCR = WZPolarizationTree->passTopElCR;
     DefaultEvent.passTopMuCR = WZPolarizationTree->passTopMuCR;
     DefaultEvent.passWZInclusive = WZPolarizationTree->passWZInclusive;
     DefaultEvent.passHardWZInclusive = WZPolarizationTree->passHardWZInclusive;
     DefaultEvent.passWZInclusiveLoose = WZPolarizationTree->passWZInclusiveLoose;
     DefaultEvent.passHardWZInclusiveLoose = WZPolarizationTree->passHardWZInclusiveLoose;
     DefaultEvent.passWZqqSR = WZPolarizationTree->passWZqqSR;
     DefaultEvent.passWZqqCR = WZPolarizationTree->passWZqqCR;
     DefaultEvent.passWZVBSSR = WZPolarizationTree->passWZVBSSR;
     DefaultEvent.passWZVBSCR = WZPolarizationTree->passWZVBSCR;
     DefaultEvent.passWZInclusiveNoMET = WZPolarizationTree->passWZInclusiveNoMET;
     DefaultEvent.passTopEnrichCR = WZPolarizationTree->passTopEnrichCR;
     DefaultEvent.passTTT = WZPolarizationTree->passTTT;
     DefaultEvent.passTTL = WZPolarizationTree->passTTL;
     DefaultEvent.passTLT = WZPolarizationTree->passTLT;
     DefaultEvent.passLTT = WZPolarizationTree->passLTT;
     DefaultEvent.passTLL = WZPolarizationTree->passTLL;
     DefaultEvent.passLTL = WZPolarizationTree->passLTL;
     DefaultEvent.passLLT = WZPolarizationTree->passLLT;
     DefaultEvent.passZCondition = WZPolarizationTree->passZCondition;
     DefaultEvent.passWCondition = WZPolarizationTree->passWCondition;
     DefaultEvent.passSignalRegion = WZPolarizationTree->passSignalRegion;
     DefaultEvent.passHighPtWZCR = WZPolarizationTree->passHighPtWZCR;
     DefaultEvent.passLowPtZCR = WZPolarizationTree->passLowPtZCR;
     DefaultEvent.passTruthMatch1 = WZPolarizationTree->passTruthMatch1;
     DefaultEvent.passTruthMatch2 = WZPolarizationTree->passTruthMatch2;
     DefaultEvent.passTruthMatch3 = WZPolarizationTree->passTruthMatch3;
     DefaultEvent.passZCondition1 = WZPolarizationTree->passZCondition1;
     DefaultEvent.passZCondition2 = WZPolarizationTree->passZCondition2;
     DefaultEvent.passZCondition3 = WZPolarizationTree->passZCondition3;
     DefaultEvent.passWCondition1 = WZPolarizationTree->passWCondition1;
     DefaultEvent.passWCondition2 = WZPolarizationTree->passWCondition2;
     DefaultEvent.passWCondition3 = WZPolarizationTree->passWCondition3;
     DefaultEvent.passMediumID1 = WZPolarizationTree->passMediumID1;
     DefaultEvent.passMediumID2 = WZPolarizationTree->passMediumID2;
     DefaultEvent.passMediumID3 = WZPolarizationTree->passMediumID3;
     DefaultEvent.passTightID1 = WZPolarizationTree->passTightID1;
     DefaultEvent.passTightID2 = WZPolarizationTree->passTightID2;
     DefaultEvent.passTightID3 = WZPolarizationTree->passTightID3;
     DefaultEvent.passIPID1 = WZPolarizationTree->passIPID1;
     DefaultEvent.passIPID2 = WZPolarizationTree->passIPID2;
     DefaultEvent.passIPID3 = WZPolarizationTree->passIPID3;
     DefaultEvent.isTauEvent = WZPolarizationTree->isTauEvent;
     DefaultEvent.passDeltaR = WZPolarizationTree->passDeltaR;
     DefaultEvent.passThreeBaseline = WZPolarizationTree->passThreeBaseline;

     TLorentzVector ZLep1;
     ZLep1.SetPtEtaPhiM(DefaultEvent.Lep1Pt, DefaultEvent.Lep1Eta, DefaultEvent.Lep1Phi, 0.0);
     TLorentzVector ZLep2;
     ZLep2.SetPtEtaPhiM(DefaultEvent.Lep2Pt, DefaultEvent.Lep2Eta, DefaultEvent.Lep2Phi, 0.0);
     TLorentzVector WLep;
     WLep.SetPtEtaPhiM(DefaultEvent.Lep3Pt, DefaultEvent.Lep3Eta, DefaultEvent.Lep3Phi, 0.0);

     TLorentzVector ZBoson = ZLep1 + ZLep2;
     DefaultEvent.DeltaPhiZBosonLepW = DeltaPhi(ZBoson.Phi(), DefaultEvent.Lep3Phi);
     DefaultEvent.ZY = ZBoson.Rapidity();

     DefaultEvent.WLepPz = WLep.Pz();
     DefaultEvent.NeutrinoPz = DefaultEvent.Mpz;
     DefaultEvent.ZLep1Pz = ZLep1.Pz();
     DefaultEvent.ZLep2Pz = ZLep2.Pz();

     if(DefaultEvent.WLepPz > 0 && DefaultEvent.NeutrinoPz > 0) DefaultEvent.WDecayStatus = 0.5;
     if(DefaultEvent.WLepPz > 0 && DefaultEvent.NeutrinoPz < 0) DefaultEvent.WDecayStatus = 1.5;
     if(DefaultEvent.WLepPz < 0 && DefaultEvent.NeutrinoPz > 0) DefaultEvent.WDecayStatus = 2.5;
     if(DefaultEvent.WLepPz < 0 && DefaultEvent.NeutrinoPz < 0) DefaultEvent.WDecayStatus = 3.5;

     if(DefaultEvent.ZLep1Pz > 0 && DefaultEvent.ZLep2Pz > 0) DefaultEvent.ZDecayStatus = 0.5;
     if(DefaultEvent.ZLep1Pz > 0 && DefaultEvent.ZLep2Pz < 0) DefaultEvent.ZDecayStatus = 1.5;
     if(DefaultEvent.ZLep1Pz < 0 && DefaultEvent.ZLep2Pz > 0) DefaultEvent.ZDecayStatus = 2.5;
     if(DefaultEvent.ZLep1Pz < 0 && DefaultEvent.ZLep2Pz < 0) DefaultEvent.ZDecayStatus = 3.5;


     /////////////////////////////////////
     //   Get PDF and QCD uncertainty   //
     /////////////////////////////////////

     bool isSignal = false;
     bool isNLOSample = false;
     bool isWZ = false;

     if(MCType == 364253) isNLOSample = true;
     if(MCType == 500290 || MCType == 500291 || MCType == 500292 || MCType == 500293 || MCType == 500294 || MCType == 500295 || MCType == 500296 || MCType == 500297) isSignal = true;
     if(MCType == 501793 || MCType == 501794 || MCType == 501795 || MCType == 501796 || MCType == 501797 || MCType == 501798 || MCType == 501799 || MCType == 501800) isSignal = true;
     if(MCType == 507019 || MCType == 507020 || MCType == 507021 || MCType == 507022 || MCType == 507023 || MCType == 507024 || MCType == 507025 || MCType == 507026) isSignal = true;
     if(MCType == 507027 || MCType == 507028 || MCType == 507029 || MCType == 507030 || MCType == 507031 || MCType == 507032 || MCType == 507033 || MCType == 507034) isSignal = true;

     if(isNLOSample || isSignal) isWZ = true;

     if(doRunPDFAndQCDUnc && isSignal){
       DefaultEvent.PDFWeights = WZPolarizationTree->PDFWeights;
       DefaultEvent.QCDWeights = WZPolarizationTree->QCDWeights;

       if(ErrorType == "PDF" && ErrorSet >= DefaultEvent.PDFWeights->size()){
         cout<<"ERROR: exceed the PDF weights size."<<endl;
         return;
       }
       if(ErrorType == "QCD" && ErrorSet >= DefaultEvent.QCDWeights->size()){
         cout<<"ERROR: channel:"<<MCType<<", exceed the QCD weights size. The maximum QCD weights size is "<<DefaultEvent.QCDWeights->size()<<endl;
         return;
       }

     }

//     DefaultEvent.TotalWeight = DefaultEvent.WeightNormalized * DefaultEvent.Lep1WeightZ * DefaultEvent.Lep2WeightZ * DefaultEvent.Lep3WeightW;

     if(MCType == 364253){
       for(int iprocesshist = 0; iprocesshist < myhists->hist_process.size(); iprocesshist++){
         myhists->hist_process.at(iprocesshist)->InputNLOWeight(iThread, DefaultEvent.LLNLOWeight, DefaultEvent.LTNLOWeight, DefaultEvent.TLNLOWeight, DefaultEvent.TTNLOWeight);
       }
     }

     ProcessEvent.ResetEvent();
     ProcessEvent = DefaultEvent;

     //bool isMuon1EtaGt25 = false;
     //bool isMuon2EtaGt25 = false;
     //bool isMuon3EtaGt25 = false;
     //if(fabs(ProcessEvent.Lep1Flavor) == 13){
     //  isMuon1EtaGt25 = ()
     //}


//     if(ProcessEvent.Pt_Z < 200.0) continue;
//     if(ProcessEvent.Pt_WZ > 70.0) continue;

//     if(ProcessEvent.DecayChannel != 4) continue;

     ////////////////////////
     //   Fill histogram   //
     ////////////////////////

     FillHist(ProcessEvent);
   }
 }
}


void loopWZPolarization::PreLoop(int ifile)
{
 int Year = Years.at(ifile);
 int UniqueYear = UniqueYears.at(ifile);
 int MCType = RootTypes.at(ifile);
 pair<int, int> RootTypePair;
 RootTypePair = make_pair(MCType, Year);
 double SumOfWeight = SumOfWeightsMap[RootTypePair];

 SelectedEvent.MCType = MCType;
 SelectedEvent.Channel = MCType;
 SelectedEvent.Year = Year;
 SelectedEvent.UniqueYear = UniqueYear;
 SelectedEvent.CrossSection = CrossSections.at(ifile);
 SelectedEvent.SumOfWeight = SumOfWeight;
 TruthEvent.MCType = MCType;
 TruthEvent.Channel = MCType;
 TruthEvent.Year = Year;
 TruthEvent.CrossSection = CrossSections.at(ifile);
 TruthEvent.SumOfWeight = SumOfWeight;

 for(int ibkghist = 0; ibkghist < myhists->BkgHist_1d.size(); ibkghist++){
   myhists->BkgHist_1d.at(ibkghist)->HistPtr(iThread - 1)->Initial(MCType);
   if(myhists->BkgHist_1d.at(ibkghist)->HistPtr(iThread - 1)->ProcessName == "SignalWZ") BkgShortName = myhists->BkgHist_1d.at(ibkghist)->HistPtr(iThread - 1)->ShortName;
 }

 for(int iprocesshist = 0; iprocesshist < myhists->hist_process.size(); iprocesshist++){
   myhists->hist_process.at(iprocesshist)->Initial(iThread, MCType);
 }

 if(this->isHaveFakeRate){
   for(int ihist = 0; ihist < myhists->FakeHist_1d.size(); ihist++){
     myhists->FakeHist_1d.at(ihist)->HistPtr(iThread - 1)->LinkFakeRate(myFakeRate);
   }
 }

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"\r"<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<flush;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"\r"<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
     if(!isThread) cout<<"\r"<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
   }

   if(!doTruthSelection) PreWZPolarizationTree->GetEntry(ifile, iEvent);
   if(doTruthSelection) PreWZPolarizationTree->GetTruthEntry(ifile, iEvent);

   ////////////////////////////////
   //  For fitting closure test  //
   ////////////////////////////////
   //if(PreWZPolarizationTree->EventNumber % 2 != 0) continue; // Even event number
   //if(PreWZPolarizationTree->EventNumber % 2 == 0) continue; // Odd event number


   ///////////////////////////////////////////////////////////////////////
   //  The trees have been initialized in InputTree()                   //
   //  According to the SystematicName saved in the branch,             //
   //  it will automatically find which tree should be filled           //
   //  if there is no event with one tree name(eg: FakeBkg_MetCut_1up)  //
   //  This tree will be no entries.(not cause a bug)                   //
   ///////////////////////////////////////////////////////////////////////

   int isys = -1;
   isys = myhists->FindSysIndex((TString)PreWZPolarizationTree->Systematic->c_str(), "SignalWZ");
   SelectedEvent.SystematicName = (TString)PreWZPolarizationTree->Systematic->c_str();
   if((TString)PreWZPolarizationTree->Systematic->c_str() != "nominal" && isys == 0){
     cout<<"ERROR! Unknown systematic will fill in the nominal branch. Systematic is "<<PreWZPolarizationTree->Systematic->c_str()<<endl;
     continue;
   }

   if(isys == 0) isNominal = true;
   else isNominal = false;
   if(OnlyNominal && !isNominal) continue;

   if(!doTruthSelection){//only select reco events
     if(FillEvents()){
       if(JustGenerateTree){
         if((OnlyNominal && isys == 0) || (!OnlyNominal)) WZPolarizationTree->FillTree(isys);
       }

       if(FinishProcess && isNominal) FillHist(SelectedEvent);
     }
   }

   if(doTruthSelection){//only select truth events
     if(isNominal && MCType != -1 && TruthSelection()){
       if(JustGenerateTree) WZPolarizationTree->FillTruthTree();
       if(FinishProcess) FillTruthHist(TruthEvent);
     }
   }
 }

// for(auto EventNumberIter = EventNumber.begin(); EventNumberIter != EventNumber.end(); EventNumberIter++){
//   cout<<*EventNumberIter<<endl;
// }
}

bool loopWZPolarization::FillEvents()
{

///////////////////////////////
//      Retrieve Events      //
///////////////////////////////

 SelectedEvent.ResetEvent();

 bool isData = false;
 if(SelectedEvent.MCType == -1) isData = true;

 Lepton Lepton1;
 Lepton Lepton2;
 Lepton Lepton3;

 Lepton TruthLepton1;
 Lepton TruthLepton2;
 Lepton TruthLepton3;

 //reco level
 int CountElectron = 0;
 vector<int> ElectronSize;
 for(int i = 0; i < PreWZPolarizationTree->el_eta->size(); i++){
   CountElectron++;
   ElectronSize.push_back(i);
 }

 int CountMuon = 0;
 vector<int> MuonSize;
 for(int i = 0; i < PreWZPolarizationTree->mu_eta->size(); i++){
   CountMuon++;
   MuonSize.push_back(i);
 }

 int CountJet = 0;
 int CountBJet = 0;
 for(int i = 0; i < PreWZPolarizationTree->jt_eta->size(); i++){
   CountJet++;
   SelectedEvent.SumJetPt += PreWZPolarizationTree->jt_pt->at(i) / GeV;

   if(!PreWZPolarizationTree->jt_passBtag->at(i)) continue;
   CountBJet++;
 }

 //truth level
/* int CountTruthElectron = 0;
 vector<int> TruthElectronSize;
 int CountTruthMuon = 0;
 vector<int> TruthMuonSize;
 int CountTruthNeutrino = 0;
 vector<int> TruthNeutrinoSize;
 if(!isData){
   for(int i = 0; i < PreWZPolarizationTree->truth_eta->size(); i++){
     if(fabs(PreWZPolarizationTree->truth_pid->at(i)) == 11){
       CountTruthElectron++;
       TruthElectronSize.push_back(i);
     }
     if(fabs(PreWZPolarizationTree->truth_pid->at(i)) == 13){
       CountTruthMuon++;
       TruthMuonSize.push_back(i);
     }
     if(fabs(PreWZPolarizationTree->truth_pid->at(i)) == 12 || fabs(PreWZPolarizationTree->truth_pid->at(i)) == 14){
       CountTruthNeutrino++;
       TruthNeutrinoSize.push_back(i);
     }
   }
 }
*/
 //if(!(CountMuon == 2 && CountElectron == 1)) return false;//yfu
 //if(PreWZPolarizationTree->EventNumber != 47357312) return false;

 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "all", 1, isNominal);
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "all", SelectedEvent.TotalWeightNoKFactor, isNominal);

 if(isTest) cout<<"Total number of lepton: "<<CountElectron + CountMuon<<endl;
 if(!JustGenerateTree && isNominal) myhists->LeptonCount->HistPtr(iThread - 1)->Fill(CountElectron + CountMuon, 1.0);

 if((CountElectron + CountMuon) < 3) return false;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, ">=3 baseline leptons", 1, isNominal);
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, ">=3 baseline leptons", SelectedEvent.TotalWeightNoKFactor, isNominal);

 if((CountElectron + CountMuon) != 3) return false;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "==3 baseline leptons", 1, isNominal);
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "==3 baseline leptons", SelectedEvent.TotalWeightNoKFactor, isNominal);

 if(CountElectron == 1 && CountMuon == 2){
   Flavor = "emm";
   Lepton1.P4.SetPtEtaPhiE(PreWZPolarizationTree->el_pt->at(ElectronSize.at(0)) / GeV, PreWZPolarizationTree->el_eta->at(ElectronSize.at(0)), PreWZPolarizationTree->el_phi->at(ElectronSize.at(0)), PreWZPolarizationTree->el_e->at(ElectronSize.at(0)) / GeV);
   Lepton2.P4.SetPtEtaPhiE(PreWZPolarizationTree->mu_pt->at(MuonSize.at(0)) / GeV, PreWZPolarizationTree->mu_eta->at(MuonSize.at(0)), PreWZPolarizationTree->mu_phi->at(MuonSize.at(0)), PreWZPolarizationTree->mu_e->at(MuonSize.at(0)) / GeV);
   Lepton3.P4.SetPtEtaPhiE(PreWZPolarizationTree->mu_pt->at(MuonSize.at(1)) / GeV, PreWZPolarizationTree->mu_eta->at(MuonSize.at(1)), PreWZPolarizationTree->mu_phi->at(MuonSize.at(1)), PreWZPolarizationTree->mu_e->at(MuonSize.at(1)) / GeV);

   Lepton1.Flavor = "Electron";
   Lepton2.Flavor = "Muon";
   Lepton3.Flavor = "Muon";

   Lepton1.pdgID = 11;
   Lepton2.pdgID = 13;
   Lepton3.pdgID = 13;

   Lepton1.Charge = PreWZPolarizationTree->el_charge->at(ElectronSize.at(0));
   Lepton2.Charge = PreWZPolarizationTree->mu_charge->at(MuonSize.at(0));
   Lepton3.Charge = PreWZPolarizationTree->mu_charge->at(MuonSize.at(1));

   Lepton1.d0Sig = PreWZPolarizationTree->el_d0Sig->at(ElectronSize.at(0));
   Lepton2.d0Sig = PreWZPolarizationTree->mu_d0Sig->at(MuonSize.at(0));
   Lepton3.d0Sig = PreWZPolarizationTree->mu_d0Sig->at(MuonSize.at(1));

   Lepton1.mediumID = PreWZPolarizationTree->el_mediumID->at(ElectronSize.at(0));
   Lepton2.mediumID = PreWZPolarizationTree->mu_mediumID->at(MuonSize.at(0));
   Lepton3.mediumID = PreWZPolarizationTree->mu_mediumID->at(MuonSize.at(1));

   if(!isData) Lepton1.mediumIDWeight = PreWZPolarizationTree->el_mediumIDWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.mediumIDWeight = PreWZPolarizationTree->mu_mediumIDWeight->at(MuonSize.at(0));
   if(!isData) Lepton3.mediumIDWeight = PreWZPolarizationTree->mu_mediumIDWeight->at(MuonSize.at(1));

   Lepton1.tightID = PreWZPolarizationTree->el_tightID->at(ElectronSize.at(0));
   Lepton2.tightID = PreWZPolarizationTree->mu_tightID->at(MuonSize.at(0));
   Lepton3.tightID = PreWZPolarizationTree->mu_tightID->at(MuonSize.at(1));

   if(!isData) Lepton1.tightIDWeight = PreWZPolarizationTree->el_tightIDWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.tightIDWeight = PreWZPolarizationTree->mu_tightIDWeight->at(MuonSize.at(0));
   if(!isData) Lepton3.tightIDWeight = PreWZPolarizationTree->mu_tightIDWeight->at(MuonSize.at(1));

   Lepton1.FCLooseIso = PreWZPolarizationTree->el_FCLooseIso->at(ElectronSize.at(0));
   Lepton2.FCLooseIso = PreWZPolarizationTree->mu_FCLooseIso->at(MuonSize.at(0));
   Lepton3.FCLooseIso = PreWZPolarizationTree->mu_FCLooseIso->at(MuonSize.at(1));

   if(!isData) Lepton1.FCLooseIsoWeight = PreWZPolarizationTree->el_FCLooseIsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.FCLooseIsoWeight = PreWZPolarizationTree->mu_FCLooseIsoWeight->at(MuonSize.at(0));
   if(!isData) Lepton3.FCLooseIsoWeight = PreWZPolarizationTree->mu_FCLooseIsoWeight->at(MuonSize.at(1));

   Lepton1.FCTightIso = PreWZPolarizationTree->el_FCTightIso->at(ElectronSize.at(0));
   //Lepton2.FCTightIso = PreWZPolarizationTree->mu_FCTightIso->at(MuonSize.at(0));
   //Lepton3.FCTightIso = PreWZPolarizationTree->mu_FCTightIso->at(MuonSize.at(1));

   //Lepton1.FCHighPtIso = PreWZPolarizationTree->el_FCHighPtIso->at(ElectronSize.at(0));
   Lepton1.HighPtCaloOnlyIso = PreWZPolarizationTree->el_HighPtCaloOnlyIso->at(ElectronSize.at(0));
   Lepton1.Loose_VarRadIso = PreWZPolarizationTree->el_Loose_VarRadIso->at(ElectronSize.at(0));
   Lepton1.Tight_VarRadIso = PreWZPolarizationTree->el_Tight_VarRadIso->at(ElectronSize.at(0));
   Lepton2.PflowLooseIso = PreWZPolarizationTree->mu_PflowLooseIso->at(MuonSize.at(0));
   Lepton3.PflowLooseIso = PreWZPolarizationTree->mu_PflowLooseIso->at(MuonSize.at(1));
   Lepton2.PflowTightIso = PreWZPolarizationTree->mu_PflowTightIso->at(MuonSize.at(0));
   Lepton3.PflowTightIso = PreWZPolarizationTree->mu_PflowTightIso->at(MuonSize.at(1));

   if(!isData) Lepton1.FCTightIsoWeight = PreWZPolarizationTree->el_FCTightIsoWeight->at(ElectronSize.at(0));
   //if(!isData) Lepton2.FCTightIsoWeight = PreWZPolarizationTree->mu_FCTightIsoWeight->at(MuonSize.at(0));
   //if(!isData) Lepton3.FCTightIsoWeight = PreWZPolarizationTree->mu_FCTightIsoWeight->at(MuonSize.at(1));

   //if(!isData) Lepton1.FCHighPtIsoWeight = PreWZPolarizationTree->el_FCHighPtIsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.HighPtCaloOnly_MediumID_IsoWeight = PreWZPolarizationTree->el_HighPtCaloOnly_MediumID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.HighPtCaloOnly_TightID_IsoWeight = PreWZPolarizationTree->el_HighPtCaloOnly_TightID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.Loose_VarRad_MediumID_IsoWeight = PreWZPolarizationTree->el_Loose_VarRad_MediumID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.Loose_VarRad_TightID_IsoWeight = PreWZPolarizationTree->el_Loose_VarRad_TightID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.Tight_VarRad_MediumID_IsoWeight = PreWZPolarizationTree->el_Tight_VarRad_MediumID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.Tight_VarRad_TightID_IsoWeight = PreWZPolarizationTree->el_Tight_VarRad_TightID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.PflowLooseIsoWeight = PreWZPolarizationTree->mu_PflowLooseIsoWeight->at(MuonSize.at(0));
   if(!isData) Lepton3.PflowLooseIsoWeight = PreWZPolarizationTree->mu_PflowLooseIsoWeight->at(MuonSize.at(1));
   if(!isData) Lepton2.PflowTightIsoWeight = PreWZPolarizationTree->mu_PflowTightIsoWeight->at(MuonSize.at(0));
   if(!isData) Lepton3.PflowTightIsoWeight = PreWZPolarizationTree->mu_PflowTightIsoWeight->at(MuonSize.at(1));

   Lepton1.triggerMatched = PreWZPolarizationTree->el_triggerMatched->at(ElectronSize.at(0));
   Lepton2.triggerMatched = PreWZPolarizationTree->mu_triggerMatched->at(MuonSize.at(0));
   Lepton3.triggerMatched = PreWZPolarizationTree->mu_triggerMatched->at(MuonSize.at(1));

   Lepton1.truthMatched = PreWZPolarizationTree->el_truthMatched->at(ElectronSize.at(0));
   Lepton2.truthMatched = PreWZPolarizationTree->mu_truthMatched->at(MuonSize.at(0));
   Lepton3.truthMatched = PreWZPolarizationTree->mu_truthMatched->at(MuonSize.at(1));

   Lepton1.isBaseline = PreWZPolarizationTree->el_isbaseline->at(ElectronSize.at(0));
   Lepton2.isBaseline = PreWZPolarizationTree->mu_isbaseline->at(MuonSize.at(0));
   Lepton3.isBaseline = PreWZPolarizationTree->mu_isbaseline->at(MuonSize.at(1));

   Lepton1.isAmbiguity = PreWZPolarizationTree->el_isAmbiguity->at(ElectronSize.at(0));
   Lepton2.isAmbiguity = 0;
   Lepton3.isAmbiguity = 0;

   if(!isData) Lepton1.recoWeight = PreWZPolarizationTree->el_recoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.IPWeight = PreWZPolarizationTree->mu_IPWeight->at(MuonSize.at(0));
   if(!isData) Lepton3.IPWeight = PreWZPolarizationTree->mu_IPWeight->at(MuonSize.at(1));

   SelectedEvent.CutLepton1 = Lepton1;
   SelectedEvent.CutLepton2 = Lepton2;
   SelectedEvent.CutLepton3 = Lepton3;

   if(fabs(Lepton1.Charge + Lepton2.Charge + Lepton3.Charge) > 2) SelectedEvent.isThreeSameCharge = true;
   if(SelectedEvent.isThreeSameCharge == true) return false;
   if(Lepton1.Charge * Lepton2.Charge > 0){
     SelectedEvent.Lepton1 = Lepton3;//opposite mu
     SelectedEvent.Lepton2 = Lepton2;//same mu
     SelectedEvent.Lepton3 = Lepton1;//same e
   }
   if(Lepton1.Charge * Lepton3.Charge > 0){
     SelectedEvent.Lepton1 = Lepton2;//opposite mu
     SelectedEvent.Lepton2 = Lepton3;//same mu
     SelectedEvent.Lepton3 = Lepton1;//same e
   }
   if(Lepton2.Charge * Lepton3.Charge > 0){
     SelectedEvent.Lepton1 = Lepton1;//opposite e
     SelectedEvent.Lepton2 = Lepton2;//same mu
     SelectedEvent.Lepton3 = Lepton3;//same mu
   }
 }

 if(CountElectron == 2 && CountMuon == 1){
   Flavor = "eem";
   Lepton1.P4.SetPtEtaPhiE(PreWZPolarizationTree->el_pt->at(ElectronSize.at(0)) / GeV, PreWZPolarizationTree->el_eta->at(ElectronSize.at(0)), PreWZPolarizationTree->el_phi->at(ElectronSize.at(0)), PreWZPolarizationTree->el_e->at(ElectronSize.at(0)) / GeV);
   Lepton2.P4.SetPtEtaPhiE(PreWZPolarizationTree->el_pt->at(ElectronSize.at(1)) / GeV, PreWZPolarizationTree->el_eta->at(ElectronSize.at(1)), PreWZPolarizationTree->el_phi->at(ElectronSize.at(1)), PreWZPolarizationTree->el_e->at(ElectronSize.at(1)) / GeV);
   Lepton3.P4.SetPtEtaPhiE(PreWZPolarizationTree->mu_pt->at(MuonSize.at(0)) / GeV, PreWZPolarizationTree->mu_eta->at(MuonSize.at(0)), PreWZPolarizationTree->mu_phi->at(MuonSize.at(0)), PreWZPolarizationTree->mu_e->at(MuonSize.at(0)) / GeV);

   Lepton1.Flavor = "Electron";
   Lepton2.Flavor = "Electron";
   Lepton3.Flavor = "Muon";

   Lepton1.pdgID = 11;
   Lepton2.pdgID = 11;
   Lepton3.pdgID = 13;

   Lepton1.Charge = PreWZPolarizationTree->el_charge->at(ElectronSize.at(0));
   Lepton2.Charge = PreWZPolarizationTree->el_charge->at(ElectronSize.at(1));
   Lepton3.Charge = PreWZPolarizationTree->mu_charge->at(MuonSize.at(0));

   Lepton1.d0Sig = PreWZPolarizationTree->el_d0Sig->at(ElectronSize.at(0));
   Lepton2.d0Sig = PreWZPolarizationTree->el_d0Sig->at(ElectronSize.at(1));
   Lepton3.d0Sig = PreWZPolarizationTree->mu_d0Sig->at(MuonSize.at(0));

   Lepton1.mediumID = PreWZPolarizationTree->el_mediumID->at(ElectronSize.at(0));
   Lepton2.mediumID = PreWZPolarizationTree->el_mediumID->at(ElectronSize.at(1));
   Lepton3.mediumID = PreWZPolarizationTree->mu_mediumID->at(MuonSize.at(0));

   if(!isData) Lepton1.mediumIDWeight = PreWZPolarizationTree->el_mediumIDWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.mediumIDWeight = PreWZPolarizationTree->el_mediumIDWeight->at(ElectronSize.at(1));
   if(!isData) Lepton3.mediumIDWeight = PreWZPolarizationTree->mu_mediumIDWeight->at(MuonSize.at(0));

   Lepton1.tightID = PreWZPolarizationTree->el_tightID->at(ElectronSize.at(0));
   Lepton2.tightID = PreWZPolarizationTree->el_tightID->at(ElectronSize.at(1));
   Lepton3.tightID = PreWZPolarizationTree->mu_tightID->at(MuonSize.at(0));

   if(!isData) Lepton1.tightIDWeight = PreWZPolarizationTree->el_tightIDWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.tightIDWeight = PreWZPolarizationTree->el_tightIDWeight->at(ElectronSize.at(1));
   if(!isData) Lepton3.tightIDWeight = PreWZPolarizationTree->mu_tightIDWeight->at(MuonSize.at(0));

   Lepton1.FCLooseIso = PreWZPolarizationTree->el_FCLooseIso->at(ElectronSize.at(0));
   Lepton2.FCLooseIso = PreWZPolarizationTree->el_FCLooseIso->at(ElectronSize.at(1));
   Lepton3.FCLooseIso = PreWZPolarizationTree->mu_FCLooseIso->at(MuonSize.at(0));

   if(!isData) Lepton1.FCLooseIsoWeight = PreWZPolarizationTree->el_FCLooseIsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.FCLooseIsoWeight = PreWZPolarizationTree->el_FCLooseIsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton3.FCLooseIsoWeight = PreWZPolarizationTree->mu_FCLooseIsoWeight->at(MuonSize.at(0));

   Lepton1.FCTightIso = PreWZPolarizationTree->el_FCTightIso->at(ElectronSize.at(0));
   Lepton2.FCTightIso = PreWZPolarizationTree->el_FCTightIso->at(ElectronSize.at(1));
   //Lepton3.FCTightIso = PreWZPolarizationTree->mu_FCTightIso->at(MuonSize.at(0));

   //Lepton1.FCHighPtIso = PreWZPolarizationTree->el_FCHighPtIso->at(ElectronSize.at(0));
   Lepton1.HighPtCaloOnlyIso = PreWZPolarizationTree->el_HighPtCaloOnlyIso->at(ElectronSize.at(0));
   Lepton1.Loose_VarRadIso = PreWZPolarizationTree->el_Loose_VarRadIso->at(ElectronSize.at(0));
   Lepton1.Tight_VarRadIso = PreWZPolarizationTree->el_Tight_VarRadIso->at(ElectronSize.at(0));
   //Lepton2.FCHighPtIso = PreWZPolarizationTree->el_FCHighPtIso->at(ElectronSize.at(1));
   Lepton2.HighPtCaloOnlyIso = PreWZPolarizationTree->el_HighPtCaloOnlyIso->at(ElectronSize.at(1));
   Lepton2.Loose_VarRadIso = PreWZPolarizationTree->el_Loose_VarRadIso->at(ElectronSize.at(1));
   Lepton2.Tight_VarRadIso = PreWZPolarizationTree->el_Tight_VarRadIso->at(ElectronSize.at(1));
   Lepton3.PflowLooseIso = PreWZPolarizationTree->mu_PflowLooseIso->at(MuonSize.at(0));
   Lepton3.PflowTightIso = PreWZPolarizationTree->mu_PflowTightIso->at(MuonSize.at(0));

   if(!isData) Lepton1.FCTightIsoWeight = PreWZPolarizationTree->el_FCTightIsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.FCTightIsoWeight = PreWZPolarizationTree->el_FCTightIsoWeight->at(ElectronSize.at(1));
   //if(!isData) Lepton3.FCTightIsoWeight = PreWZPolarizationTree->mu_FCTightIsoWeight->at(MuonSize.at(0));

   //if(!isData) Lepton1.FCHighPtIsoWeight = PreWZPolarizationTree->el_FCHighPtIsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.HighPtCaloOnly_MediumID_IsoWeight = PreWZPolarizationTree->el_HighPtCaloOnly_MediumID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.HighPtCaloOnly_TightID_IsoWeight = PreWZPolarizationTree->el_HighPtCaloOnly_TightID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.Loose_VarRad_MediumID_IsoWeight = PreWZPolarizationTree->el_Loose_VarRad_MediumID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.Loose_VarRad_TightID_IsoWeight = PreWZPolarizationTree->el_Loose_VarRad_TightID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.Tight_VarRad_MediumID_IsoWeight = PreWZPolarizationTree->el_Tight_VarRad_MediumID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.Tight_VarRad_TightID_IsoWeight = PreWZPolarizationTree->el_Tight_VarRad_TightID_IsoWeight->at(ElectronSize.at(0));
   //if(!isData) Lepton2.FCHighPtIsoWeight = PreWZPolarizationTree->el_FCHighPtIsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton2.HighPtCaloOnly_MediumID_IsoWeight = PreWZPolarizationTree->el_HighPtCaloOnly_MediumID_IsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton2.HighPtCaloOnly_TightID_IsoWeight = PreWZPolarizationTree->el_HighPtCaloOnly_TightID_IsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton2.Loose_VarRad_MediumID_IsoWeight = PreWZPolarizationTree->el_Loose_VarRad_MediumID_IsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton2.Loose_VarRad_TightID_IsoWeight = PreWZPolarizationTree->el_Loose_VarRad_TightID_IsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton2.Tight_VarRad_MediumID_IsoWeight = PreWZPolarizationTree->el_Tight_VarRad_MediumID_IsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton2.Tight_VarRad_TightID_IsoWeight = PreWZPolarizationTree->el_Tight_VarRad_TightID_IsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton3.PflowLooseIsoWeight = PreWZPolarizationTree->mu_PflowLooseIsoWeight->at(MuonSize.at(0));
   if(!isData) Lepton3.PflowTightIsoWeight = PreWZPolarizationTree->mu_PflowTightIsoWeight->at(MuonSize.at(0));

   Lepton1.triggerMatched = PreWZPolarizationTree->el_triggerMatched->at(ElectronSize.at(0));
   Lepton2.triggerMatched = PreWZPolarizationTree->el_triggerMatched->at(ElectronSize.at(1));
   Lepton3.triggerMatched = PreWZPolarizationTree->mu_triggerMatched->at(MuonSize.at(0));

   Lepton1.truthMatched = PreWZPolarizationTree->el_truthMatched->at(ElectronSize.at(0));
   Lepton2.truthMatched = PreWZPolarizationTree->el_truthMatched->at(ElectronSize.at(1));
   Lepton3.truthMatched = PreWZPolarizationTree->mu_truthMatched->at(MuonSize.at(0));

   Lepton1.isBaseline = PreWZPolarizationTree->el_isbaseline->at(ElectronSize.at(0));
   Lepton2.isBaseline = PreWZPolarizationTree->el_isbaseline->at(ElectronSize.at(1));
   Lepton3.isBaseline = PreWZPolarizationTree->mu_isbaseline->at(MuonSize.at(0));

   Lepton1.isAmbiguity = PreWZPolarizationTree->el_isAmbiguity->at(ElectronSize.at(0));
   Lepton2.isAmbiguity = PreWZPolarizationTree->el_isAmbiguity->at(ElectronSize.at(1));
   Lepton3.isAmbiguity = 0;

   if(!isData) Lepton1.recoWeight = PreWZPolarizationTree->el_recoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.recoWeight = PreWZPolarizationTree->el_recoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton3.IPWeight = PreWZPolarizationTree->mu_IPWeight->at(MuonSize.at(0));

   SelectedEvent.CutLepton1 = Lepton1;
   SelectedEvent.CutLepton2 = Lepton2;
   SelectedEvent.CutLepton3 = Lepton3;

   if(fabs(Lepton1.Charge + Lepton2.Charge + Lepton3.Charge) > 2) SelectedEvent.isThreeSameCharge = true;
   if(SelectedEvent.isThreeSameCharge == true) return false;
   if(Lepton1.Charge * Lepton2.Charge > 0){
     SelectedEvent.Lepton1 = Lepton3;//opposite mu
     SelectedEvent.Lepton2 = Lepton2;//same e
     SelectedEvent.Lepton3 = Lepton1;//same e
   }
   if(Lepton1.Charge * Lepton3.Charge > 0){ 
     SelectedEvent.Lepton1 = Lepton2;//opposite e
     SelectedEvent.Lepton2 = Lepton1;//same e
     SelectedEvent.Lepton3 = Lepton3;//same mu
   }
   if(Lepton2.Charge * Lepton3.Charge > 0){ 
     SelectedEvent.Lepton1 = Lepton1;//opposite e
     SelectedEvent.Lepton2 = Lepton2;//same e
     SelectedEvent.Lepton3 = Lepton3;//same mu
   }


 }

 if(CountElectron == 3 && CountMuon == 0){
   Flavor = "eee";
   Lepton1.P4.SetPtEtaPhiE(PreWZPolarizationTree->el_pt->at(ElectronSize.at(0)) / GeV, PreWZPolarizationTree->el_eta->at(ElectronSize.at(0)), PreWZPolarizationTree->el_phi->at(ElectronSize.at(0)), PreWZPolarizationTree->el_e->at(ElectronSize.at(0)) / GeV);
   Lepton2.P4.SetPtEtaPhiE(PreWZPolarizationTree->el_pt->at(ElectronSize.at(1)) / GeV, PreWZPolarizationTree->el_eta->at(ElectronSize.at(1)), PreWZPolarizationTree->el_phi->at(ElectronSize.at(1)), PreWZPolarizationTree->el_e->at(ElectronSize.at(1)) / GeV);
   Lepton3.P4.SetPtEtaPhiE(PreWZPolarizationTree->el_pt->at(ElectronSize.at(2)) / GeV, PreWZPolarizationTree->el_eta->at(ElectronSize.at(2)), PreWZPolarizationTree->el_phi->at(ElectronSize.at(2)), PreWZPolarizationTree->el_e->at(ElectronSize.at(2)) / GeV);

   Lepton1.Flavor = "Electron";
   Lepton2.Flavor = "Electron";
   Lepton3.Flavor = "Electron";

   Lepton1.pdgID = 11;
   Lepton2.pdgID = 11;
   Lepton3.pdgID = 11;

   Lepton1.Charge = PreWZPolarizationTree->el_charge->at(ElectronSize.at(0));
   Lepton2.Charge = PreWZPolarizationTree->el_charge->at(ElectronSize.at(1));
   Lepton3.Charge = PreWZPolarizationTree->el_charge->at(ElectronSize.at(2));

   Lepton1.d0Sig = PreWZPolarizationTree->el_d0Sig->at(ElectronSize.at(0));
   Lepton2.d0Sig = PreWZPolarizationTree->el_d0Sig->at(ElectronSize.at(1));
   Lepton3.d0Sig = PreWZPolarizationTree->el_d0Sig->at(ElectronSize.at(2));

   Lepton1.mediumID = PreWZPolarizationTree->el_mediumID->at(ElectronSize.at(0));
   Lepton2.mediumID = PreWZPolarizationTree->el_mediumID->at(ElectronSize.at(1));
   Lepton3.mediumID = PreWZPolarizationTree->el_mediumID->at(ElectronSize.at(2));

   if(!isData) Lepton1.mediumIDWeight = PreWZPolarizationTree->el_mediumIDWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.mediumIDWeight = PreWZPolarizationTree->el_mediumIDWeight->at(ElectronSize.at(1));
   if(!isData) Lepton3.mediumIDWeight = PreWZPolarizationTree->el_mediumIDWeight->at(ElectronSize.at(2));

   Lepton1.tightID = PreWZPolarizationTree->el_tightID->at(ElectronSize.at(0));
   Lepton2.tightID = PreWZPolarizationTree->el_tightID->at(ElectronSize.at(1));
   Lepton3.tightID = PreWZPolarizationTree->el_tightID->at(ElectronSize.at(2));

   if(!isData) Lepton1.tightIDWeight = PreWZPolarizationTree->el_tightIDWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.tightIDWeight = PreWZPolarizationTree->el_tightIDWeight->at(ElectronSize.at(1));
   if(!isData) Lepton3.tightIDWeight = PreWZPolarizationTree->el_tightIDWeight->at(ElectronSize.at(2));

   Lepton1.FCLooseIso = PreWZPolarizationTree->el_FCLooseIso->at(ElectronSize.at(0));
   Lepton2.FCLooseIso = PreWZPolarizationTree->el_FCLooseIso->at(ElectronSize.at(1));
   Lepton3.FCLooseIso = PreWZPolarizationTree->el_FCLooseIso->at(ElectronSize.at(2));

   if(!isData) Lepton1.FCLooseIsoWeight = PreWZPolarizationTree->el_FCLooseIsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.FCLooseIsoWeight = PreWZPolarizationTree->el_FCLooseIsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton3.FCLooseIsoWeight = PreWZPolarizationTree->el_FCLooseIsoWeight->at(ElectronSize.at(2));

   Lepton1.FCTightIso = PreWZPolarizationTree->el_FCTightIso->at(ElectronSize.at(0));
   Lepton2.FCTightIso = PreWZPolarizationTree->el_FCTightIso->at(ElectronSize.at(1));
   Lepton3.FCTightIso = PreWZPolarizationTree->el_FCTightIso->at(ElectronSize.at(2));

   //Lepton1.FCHighPtIso = PreWZPolarizationTree->el_FCHighPtIso->at(ElectronSize.at(0));
   Lepton1.HighPtCaloOnlyIso = PreWZPolarizationTree->el_HighPtCaloOnlyIso->at(ElectronSize.at(0));
   Lepton1.Loose_VarRadIso = PreWZPolarizationTree->el_Loose_VarRadIso->at(ElectronSize.at(0));
   Lepton1.Tight_VarRadIso = PreWZPolarizationTree->el_Tight_VarRadIso->at(ElectronSize.at(0));
   //Lepton2.FCHighPtIso = PreWZPolarizationTree->el_FCHighPtIso->at(ElectronSize.at(1));
   Lepton2.HighPtCaloOnlyIso = PreWZPolarizationTree->el_HighPtCaloOnlyIso->at(ElectronSize.at(1));
   Lepton2.Loose_VarRadIso = PreWZPolarizationTree->el_Loose_VarRadIso->at(ElectronSize.at(1));
   Lepton2.Tight_VarRadIso = PreWZPolarizationTree->el_Tight_VarRadIso->at(ElectronSize.at(1));
   //Lepton3.FCHighPtIso = PreWZPolarizationTree->el_FCHighPtIso->at(ElectronSize.at(2));
   Lepton3.HighPtCaloOnlyIso = PreWZPolarizationTree->el_HighPtCaloOnlyIso->at(ElectronSize.at(2));
   Lepton3.Loose_VarRadIso = PreWZPolarizationTree->el_Loose_VarRadIso->at(ElectronSize.at(2));
   Lepton3.Tight_VarRadIso = PreWZPolarizationTree->el_Tight_VarRadIso->at(ElectronSize.at(2));

   if(!isData) Lepton1.FCTightIsoWeight = PreWZPolarizationTree->el_FCTightIsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.FCTightIsoWeight = PreWZPolarizationTree->el_FCTightIsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton3.FCTightIsoWeight = PreWZPolarizationTree->el_FCTightIsoWeight->at(ElectronSize.at(2));

   //if(!isData) Lepton1.FCHighPtIsoWeight = PreWZPolarizationTree->el_FCHighPtIsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.HighPtCaloOnly_MediumID_IsoWeight = PreWZPolarizationTree->el_HighPtCaloOnly_MediumID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.HighPtCaloOnly_TightID_IsoWeight = PreWZPolarizationTree->el_HighPtCaloOnly_TightID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.Loose_VarRad_MediumID_IsoWeight = PreWZPolarizationTree->el_Loose_VarRad_MediumID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.Loose_VarRad_TightID_IsoWeight = PreWZPolarizationTree->el_Loose_VarRad_TightID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.Tight_VarRad_MediumID_IsoWeight = PreWZPolarizationTree->el_Tight_VarRad_MediumID_IsoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton1.Tight_VarRad_TightID_IsoWeight = PreWZPolarizationTree->el_Tight_VarRad_TightID_IsoWeight->at(ElectronSize.at(0));
   //if(!isData) Lepton2.FCHighPtIsoWeight = PreWZPolarizationTree->el_FCHighPtIsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton2.HighPtCaloOnly_MediumID_IsoWeight = PreWZPolarizationTree->el_HighPtCaloOnly_MediumID_IsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton2.HighPtCaloOnly_TightID_IsoWeight = PreWZPolarizationTree->el_HighPtCaloOnly_TightID_IsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton2.Loose_VarRad_MediumID_IsoWeight = PreWZPolarizationTree->el_Loose_VarRad_MediumID_IsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton2.Loose_VarRad_TightID_IsoWeight = PreWZPolarizationTree->el_Loose_VarRad_TightID_IsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton2.Tight_VarRad_MediumID_IsoWeight = PreWZPolarizationTree->el_Tight_VarRad_MediumID_IsoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton2.Tight_VarRad_TightID_IsoWeight = PreWZPolarizationTree->el_Tight_VarRad_TightID_IsoWeight->at(ElectronSize.at(1));
   //if(!isData) Lepton3.FCHighPtIsoWeight = PreWZPolarizationTree->el_FCHighPtIsoWeight->at(ElectronSize.at(2));
   if(!isData) Lepton3.HighPtCaloOnly_MediumID_IsoWeight = PreWZPolarizationTree->el_HighPtCaloOnly_MediumID_IsoWeight->at(ElectronSize.at(2));
   if(!isData) Lepton3.HighPtCaloOnly_TightID_IsoWeight = PreWZPolarizationTree->el_HighPtCaloOnly_TightID_IsoWeight->at(ElectronSize.at(2));
   if(!isData) Lepton3.Loose_VarRad_MediumID_IsoWeight = PreWZPolarizationTree->el_Loose_VarRad_MediumID_IsoWeight->at(ElectronSize.at(2));
   if(!isData) Lepton3.Loose_VarRad_TightID_IsoWeight = PreWZPolarizationTree->el_Loose_VarRad_TightID_IsoWeight->at(ElectronSize.at(2));
   if(!isData) Lepton3.Tight_VarRad_MediumID_IsoWeight = PreWZPolarizationTree->el_Tight_VarRad_MediumID_IsoWeight->at(ElectronSize.at(2));
   if(!isData) Lepton3.Tight_VarRad_TightID_IsoWeight = PreWZPolarizationTree->el_Tight_VarRad_TightID_IsoWeight->at(ElectronSize.at(2));

   Lepton1.triggerMatched = PreWZPolarizationTree->el_triggerMatched->at(ElectronSize.at(0));
   Lepton2.triggerMatched = PreWZPolarizationTree->el_triggerMatched->at(ElectronSize.at(1));
   Lepton3.triggerMatched = PreWZPolarizationTree->el_triggerMatched->at(ElectronSize.at(2));

   Lepton1.truthMatched = PreWZPolarizationTree->el_truthMatched->at(ElectronSize.at(0));
   Lepton2.truthMatched = PreWZPolarizationTree->el_truthMatched->at(ElectronSize.at(1));
   Lepton3.truthMatched = PreWZPolarizationTree->el_truthMatched->at(ElectronSize.at(2));

   Lepton1.isBaseline = PreWZPolarizationTree->el_isbaseline->at(ElectronSize.at(0));
   Lepton2.isBaseline = PreWZPolarizationTree->el_isbaseline->at(ElectronSize.at(1));
   Lepton3.isBaseline = PreWZPolarizationTree->el_isbaseline->at(ElectronSize.at(2));

   Lepton1.isAmbiguity = PreWZPolarizationTree->el_isAmbiguity->at(ElectronSize.at(0));
   Lepton2.isAmbiguity = PreWZPolarizationTree->el_isAmbiguity->at(ElectronSize.at(1));
   Lepton3.isAmbiguity = PreWZPolarizationTree->el_isAmbiguity->at(ElectronSize.at(2));

   if(!isData) Lepton1.recoWeight = PreWZPolarizationTree->el_recoWeight->at(ElectronSize.at(0));
   if(!isData) Lepton2.recoWeight = PreWZPolarizationTree->el_recoWeight->at(ElectronSize.at(1));
   if(!isData) Lepton3.recoWeight = PreWZPolarizationTree->el_recoWeight->at(ElectronSize.at(2));

   SelectedEvent.CutLepton1 = Lepton1;
   SelectedEvent.CutLepton2 = Lepton2;
   SelectedEvent.CutLepton3 = Lepton3;

   if(fabs(Lepton1.Charge + Lepton2.Charge + Lepton3.Charge) > 2) SelectedEvent.isThreeSameCharge = true;
   if(SelectedEvent.isThreeSameCharge == true) return false;
   if(Lepton1.Charge * Lepton2.Charge > 0){
     SelectedEvent.Lepton1 = Lepton3;//opposite e
     SelectedEvent.Lepton2 = Lepton2;//same e
     SelectedEvent.Lepton3 = Lepton1;//same e
   }
   if(Lepton1.Charge * Lepton3.Charge > 0){
     SelectedEvent.Lepton1 = Lepton2;//opposite e
     SelectedEvent.Lepton2 = Lepton1;//same e
     SelectedEvent.Lepton3 = Lepton3;//same e
   }
   if(Lepton2.Charge * Lepton3.Charge > 0){
     SelectedEvent.Lepton1 = Lepton1;//opposite e
     SelectedEvent.Lepton2 = Lepton2;//same e
     SelectedEvent.Lepton3 = Lepton3;//same e
   }


 }

 if(CountElectron == 0 && CountMuon == 3){
   Flavor = "mmm";
   Lepton1.P4.SetPtEtaPhiE(PreWZPolarizationTree->mu_pt->at(MuonSize.at(0)) / GeV, PreWZPolarizationTree->mu_eta->at(MuonSize.at(0)), PreWZPolarizationTree->mu_phi->at(MuonSize.at(0)), PreWZPolarizationTree->mu_e->at(MuonSize.at(0)) / GeV);
   Lepton2.P4.SetPtEtaPhiE(PreWZPolarizationTree->mu_pt->at(MuonSize.at(1)) / GeV, PreWZPolarizationTree->mu_eta->at(MuonSize.at(1)), PreWZPolarizationTree->mu_phi->at(MuonSize.at(1)), PreWZPolarizationTree->mu_e->at(MuonSize.at(1)) / GeV);
   Lepton3.P4.SetPtEtaPhiE(PreWZPolarizationTree->mu_pt->at(MuonSize.at(2)) / GeV, PreWZPolarizationTree->mu_eta->at(MuonSize.at(2)), PreWZPolarizationTree->mu_phi->at(MuonSize.at(2)), PreWZPolarizationTree->mu_e->at(MuonSize.at(2)) / GeV);

   Lepton1.Flavor = "Muon";
   Lepton2.Flavor = "Muon";
   Lepton3.Flavor = "Muon";

   Lepton1.pdgID = 13;
   Lepton2.pdgID = 13;
   Lepton3.pdgID = 13;

   Lepton1.Charge = PreWZPolarizationTree->mu_charge->at(MuonSize.at(0));
   Lepton2.Charge = PreWZPolarizationTree->mu_charge->at(MuonSize.at(1));
   Lepton3.Charge = PreWZPolarizationTree->mu_charge->at(MuonSize.at(2));

   Lepton1.d0Sig = PreWZPolarizationTree->mu_d0Sig->at(MuonSize.at(0));
   Lepton2.d0Sig = PreWZPolarizationTree->mu_d0Sig->at(MuonSize.at(1));
   Lepton3.d0Sig = PreWZPolarizationTree->mu_d0Sig->at(MuonSize.at(2));

   Lepton1.mediumID = PreWZPolarizationTree->mu_mediumID->at(MuonSize.at(0));
   Lepton2.mediumID = PreWZPolarizationTree->mu_mediumID->at(MuonSize.at(1));
   Lepton3.mediumID = PreWZPolarizationTree->mu_mediumID->at(MuonSize.at(2));

   if(!isData) Lepton1.mediumIDWeight = PreWZPolarizationTree->mu_mediumIDWeight->at(MuonSize.at(0));
   if(!isData) Lepton2.mediumIDWeight = PreWZPolarizationTree->mu_mediumIDWeight->at(MuonSize.at(1));
   if(!isData) Lepton3.mediumIDWeight = PreWZPolarizationTree->mu_mediumIDWeight->at(MuonSize.at(2));

   Lepton1.tightID = PreWZPolarizationTree->mu_tightID->at(MuonSize.at(0));
   Lepton2.tightID = PreWZPolarizationTree->mu_tightID->at(MuonSize.at(1));
   Lepton3.tightID = PreWZPolarizationTree->mu_tightID->at(MuonSize.at(2));

   if(!isData) Lepton1.tightIDWeight = PreWZPolarizationTree->mu_tightIDWeight->at(MuonSize.at(0));
   if(!isData) Lepton2.tightIDWeight = PreWZPolarizationTree->mu_tightIDWeight->at(MuonSize.at(1));
   if(!isData) Lepton3.tightIDWeight = PreWZPolarizationTree->mu_tightIDWeight->at(MuonSize.at(2));

   Lepton1.FCLooseIso = PreWZPolarizationTree->mu_FCLooseIso->at(MuonSize.at(0));
   Lepton2.FCLooseIso = PreWZPolarizationTree->mu_FCLooseIso->at(MuonSize.at(1));
   Lepton3.FCLooseIso = PreWZPolarizationTree->mu_FCLooseIso->at(MuonSize.at(2));

   if(!isData) Lepton1.FCLooseIsoWeight = PreWZPolarizationTree->mu_FCLooseIsoWeight->at(MuonSize.at(0));
   if(!isData) Lepton2.FCLooseIsoWeight = PreWZPolarizationTree->mu_FCLooseIsoWeight->at(MuonSize.at(1));
   if(!isData) Lepton3.FCLooseIsoWeight = PreWZPolarizationTree->mu_FCLooseIsoWeight->at(MuonSize.at(2));

   //Lepton1.FCTightIso = PreWZPolarizationTree->mu_FCTightIso->at(MuonSize.at(0));
   //Lepton2.FCTightIso = PreWZPolarizationTree->mu_FCTightIso->at(MuonSize.at(1));
   //Lepton3.FCTightIso = PreWZPolarizationTree->mu_FCTightIso->at(MuonSize.at(2));

   Lepton1.PflowLooseIso = PreWZPolarizationTree->mu_PflowLooseIso->at(MuonSize.at(0));
   Lepton2.PflowLooseIso = PreWZPolarizationTree->mu_PflowLooseIso->at(MuonSize.at(1));
   Lepton3.PflowLooseIso = PreWZPolarizationTree->mu_PflowLooseIso->at(MuonSize.at(2));
   Lepton1.PflowTightIso = PreWZPolarizationTree->mu_PflowTightIso->at(MuonSize.at(0));
   Lepton2.PflowTightIso = PreWZPolarizationTree->mu_PflowTightIso->at(MuonSize.at(1));
   Lepton3.PflowTightIso = PreWZPolarizationTree->mu_PflowTightIso->at(MuonSize.at(2));

   //if(!isData) Lepton1.FCTightIsoWeight = PreWZPolarizationTree->mu_FCTightIsoWeight->at(MuonSize.at(0));
   //if(!isData) Lepton2.FCTightIsoWeight = PreWZPolarizationTree->mu_FCTightIsoWeight->at(MuonSize.at(1));
   //if(!isData) Lepton3.FCTightIsoWeight = PreWZPolarizationTree->mu_FCTightIsoWeight->at(MuonSize.at(2));

   if(!isData) Lepton1.PflowLooseIsoWeight = PreWZPolarizationTree->mu_PflowLooseIsoWeight->at(MuonSize.at(0));
   if(!isData) Lepton2.PflowLooseIsoWeight = PreWZPolarizationTree->mu_PflowLooseIsoWeight->at(MuonSize.at(1));
   if(!isData) Lepton3.PflowLooseIsoWeight = PreWZPolarizationTree->mu_PflowLooseIsoWeight->at(MuonSize.at(2));
   if(!isData) Lepton1.PflowTightIsoWeight = PreWZPolarizationTree->mu_PflowTightIsoWeight->at(MuonSize.at(0));
   if(!isData) Lepton2.PflowTightIsoWeight = PreWZPolarizationTree->mu_PflowTightIsoWeight->at(MuonSize.at(1));
   if(!isData) Lepton3.PflowTightIsoWeight = PreWZPolarizationTree->mu_PflowTightIsoWeight->at(MuonSize.at(2));

   Lepton1.triggerMatched = PreWZPolarizationTree->mu_triggerMatched->at(MuonSize.at(0));
   Lepton2.triggerMatched = PreWZPolarizationTree->mu_triggerMatched->at(MuonSize.at(1));
   Lepton3.triggerMatched = PreWZPolarizationTree->mu_triggerMatched->at(MuonSize.at(2));

   Lepton1.truthMatched = PreWZPolarizationTree->mu_truthMatched->at(MuonSize.at(0));
   Lepton2.truthMatched = PreWZPolarizationTree->mu_truthMatched->at(MuonSize.at(1));
   Lepton3.truthMatched = PreWZPolarizationTree->mu_truthMatched->at(MuonSize.at(2));

   Lepton1.isBaseline = PreWZPolarizationTree->mu_isbaseline->at(MuonSize.at(0));
   Lepton2.isBaseline = PreWZPolarizationTree->mu_isbaseline->at(MuonSize.at(1));
   Lepton3.isBaseline = PreWZPolarizationTree->mu_isbaseline->at(MuonSize.at(2));

   Lepton1.isAmbiguity = 0;
   Lepton2.isAmbiguity = 0;
   Lepton3.isAmbiguity = 0;

   if(!isData) Lepton1.IPWeight = PreWZPolarizationTree->mu_IPWeight->at(MuonSize.at(0));
   if(!isData) Lepton2.IPWeight = PreWZPolarizationTree->mu_IPWeight->at(MuonSize.at(1));
   if(!isData) Lepton3.IPWeight = PreWZPolarizationTree->mu_IPWeight->at(MuonSize.at(2));

   SelectedEvent.CutLepton1 = Lepton1;
   SelectedEvent.CutLepton2 = Lepton2;
   SelectedEvent.CutLepton3 = Lepton3;

   if(fabs(Lepton1.Charge + Lepton2.Charge + Lepton3.Charge) > 2) SelectedEvent.isThreeSameCharge = true;
   if(SelectedEvent.isThreeSameCharge == true) return false;
   if(Lepton1.Charge * Lepton2.Charge > 0){
     SelectedEvent.Lepton1 = Lepton3;//opposite mu
     SelectedEvent.Lepton2 = Lepton2;//same mu
     SelectedEvent.Lepton3 = Lepton1;//same mu
   }
   if(Lepton1.Charge * Lepton3.Charge > 0){
     SelectedEvent.Lepton1 = Lepton2;//opposite mu
     SelectedEvent.Lepton2 = Lepton1;//same mu
     SelectedEvent.Lepton3 = Lepton3;//same mu
   }
   if(Lepton2.Charge * Lepton3.Charge > 0){
     SelectedEvent.Lepton1 = Lepton1;//opposite mu
     SelectedEvent.Lepton2 = Lepton2;//same mu
     SelectedEvent.Lepton3 = Lepton3;//same mu
   }

 }

 if(isTest) cout<<"Flavor: "<<Flavor<<endl;

 if(SelectedEvent.Lepton1.pdgID == 13 && SelectedEvent.Lepton2.pdgID == 13 && SelectedEvent.Lepton3.pdgID == 13) SelectedEvent.m_Channel = 1;//mmm
 if(SelectedEvent.Lepton1.pdgID == 13 && SelectedEvent.Lepton2.pdgID == 13 && SelectedEvent.Lepton3.pdgID == 11) SelectedEvent.m_Channel = 2;//mme
 if(SelectedEvent.Lepton1.pdgID == 11 && SelectedEvent.Lepton2.pdgID == 11 && SelectedEvent.Lepton3.pdgID == 13) SelectedEvent.m_Channel = 3;//eem
 if(SelectedEvent.Lepton1.pdgID == 11 && SelectedEvent.Lepton2.pdgID == 11 && SelectedEvent.Lepton3.pdgID == 11) SelectedEvent.m_Channel = 4;//eee
 if(SelectedEvent.Lepton1.pdgID == 11 && SelectedEvent.Lepton2.pdgID == 13 && SelectedEvent.Lepton3.pdgID == 13) SelectedEvent.m_Channel = 5;//emm
 if(SelectedEvent.Lepton1.pdgID == 13 && SelectedEvent.Lepton2.pdgID == 11 && SelectedEvent.Lepton3.pdgID == 11) SelectedEvent.m_Channel = 6;//mee

 if(SelectedEvent.m_Channel == 1 || SelectedEvent.m_Channel == 4){//find Z lepton
   if(fabs((SelectedEvent.Lepton1.P4 + SelectedEvent.Lepton2.P4).M() - ZPeakMass) > fabs((SelectedEvent.Lepton1.P4 + SelectedEvent.Lepton3.P4).M() - ZPeakMass)){
     Lepton tmplep = SelectedEvent.Lepton3;
     SelectedEvent.Lepton3 = SelectedEvent.Lepton2;
     SelectedEvent.Lepton2 = tmplep;
   }
 }

 if(SelectedEvent.m_Channel == 5 || SelectedEvent.m_Channel == 6){//make Lep2Pt > Lep3Pt
   if(fabs(SelectedEvent.Lepton2.P4.Pt() < fabs(SelectedEvent.Lepton3.P4.Pt()))){
     Lepton tmplep = SelectedEvent.Lepton3;
     SelectedEvent.Lepton3 = SelectedEvent.Lepton2;
     SelectedEvent.Lepton2 = tmplep;
   }
 }

 SelectedEvent.WNeutrino.P4.SetPxPyPzE(PreWZPolarizationTree->met_px, PreWZPolarizationTree->met_py, 0, PreWZPolarizationTree->met_et);//The unit of met is GeV.

 SelectedEvent.Njets = CountJet;
 SelectedEvent.NBjets = CountBJet;

/*
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "3 same charge lepton", 1, isNominal);

 PassTrig = (SelectedEvent.Lepton1.triggerMatched || SelectedEvent.Lepton2.triggerMatched || SelectedEvent.Lepton3.triggerMatched);
 if(!PassTrig) return false;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass trigger", 1, isNominal);

 double LeadingPtDecision = 27.0;
 if(SelectedEvent.UniqueYear == 15) LeadingPtDecision = 25.0;
 else LeadingPtDecision = 27.0;

 set<double> LeptonPt;
 LeptonPt.insert(SelectedEvent.Lepton1.P4.Pt());
 LeptonPt.insert(SelectedEvent.Lepton2.P4.Pt());
 LeptonPt.insert(SelectedEvent.Lepton3.P4.Pt());
 set<double>::iterator LeptonPtIter = LeptonPt.end();
 passLeadingLepPt = (*(--LeptonPtIter) > LeadingPtDecision);
 if(!passLeadingLepPt) return false;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass leading lepton pt", 1, isNominal);
*/

 SelectedEvent.ZLepton1 = SelectedEvent.Lepton1;
 SelectedEvent.ZLepton2 = SelectedEvent.Lepton2;
 SelectedEvent.WLepton = SelectedEvent.Lepton3;

 SelectedEvent.WLep = SelectedEvent.WLepton;
 if(SelectedEvent.ZLepton1.P4.Pt() > SelectedEvent.ZLepton2.P4.Pt()){
   SelectedEvent.ZLeadingLep = SelectedEvent.ZLepton1;
   SelectedEvent.ZSubleadingLep = SelectedEvent.ZLepton2;
 }
 else{
   SelectedEvent.ZLeadingLep = SelectedEvent.ZLepton2;
   SelectedEvent.ZSubleadingLep = SelectedEvent.ZLepton1;
 }

 double NeutrinoPz;
 if(isLWTNNNuPz) SelectedEvent.LWTNNNuPz = LwtnnNuPz->GetNuPz(SelectedEvent.WLepton.P4, SelectedEvent.WNeutrino.P4, PreWZPolarizationTree->EventNumber, WPeakMass);
 SelectedEvent.Mpz = CalculateNeutrinoPz(SelectedEvent.WLepton.P4, SelectedEvent.WNeutrino.P4, WPeakMass);

 if(!isLWTNNNuPz) NeutrinoPz = SelectedEvent.Mpz;
 if(isLWTNNNuPz) NeutrinoPz = SelectedEvent.LWTNNNuPz;

 double NeutrinoE = sqrt(NeutrinoPz * NeutrinoPz + PreWZPolarizationTree->met_et * PreWZPolarizationTree->met_et);

 SelectedEvent.WNeutrino.P4.SetPxPyPzE(PreWZPolarizationTree->met_px, PreWZPolarizationTree->met_py, NeutrinoPz, NeutrinoE);

 /////////////////////////////////
 //  retrieve the truth events  //
 /////////////////////////////////

/*
 if(!isData){
   if(PreWZPolarizationTree->truth_pt->size() >= 1) TruthLepton1.P4.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(0) / GeV, PreWZPolarizationTree->truth_eta->at(0), PreWZPolarizationTree->truth_phi->at(0), PreWZPolarizationTree->truth_e->at(0) / GeV);
   if(PreWZPolarizationTree->truth_pt->size() >= 2) TruthLepton2.P4.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(1) / GeV, PreWZPolarizationTree->truth_eta->at(1), PreWZPolarizationTree->truth_phi->at(1), PreWZPolarizationTree->truth_e->at(1) / GeV);
   if(PreWZPolarizationTree->truth_pt->size() >= 3) TruthLepton3.P4.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(2) / GeV, PreWZPolarizationTree->truth_eta->at(2), PreWZPolarizationTree->truth_phi->at(2), PreWZPolarizationTree->truth_e->at(2) / GeV);

   if(PreWZPolarizationTree->truth_pt->size() >= 1) TruthLepton1.pdgID = fabs(PreWZPolarizationTree->truth_pid->at(0));
   if(PreWZPolarizationTree->truth_pt->size() >= 2) TruthLepton2.pdgID = fabs(PreWZPolarizationTree->truth_pid->at(1));
   if(PreWZPolarizationTree->truth_pt->size() >= 3) TruthLepton3.pdgID = fabs(PreWZPolarizationTree->truth_pid->at(2));

   double dR1 = 0.0;
   double dR2 = 0.0;
   double dR3 = 0.0;
   map<double, Lepton> LeptonDeltaR;
   map<double, Lepton>::iterator LeptonDeltaRIter;

   LeptonDeltaR[TruthLepton1.P4.DeltaR(SelectedEvent.Lepton1.P4)] = TruthLepton1;
   LeptonDeltaR[TruthLepton2.P4.DeltaR(SelectedEvent.Lepton1.P4)] = TruthLepton2;
   LeptonDeltaR[TruthLepton3.P4.DeltaR(SelectedEvent.Lepton1.P4)] = TruthLepton3;
   LeptonDeltaRIter = LeptonDeltaR.begin();
   SelectedEvent.TruthLepton1 = LeptonDeltaRIter->second;
   LeptonDeltaR.clear();

   LeptonDeltaR[TruthLepton1.P4.DeltaR(SelectedEvent.Lepton2.P4)] = TruthLepton1;
   LeptonDeltaR[TruthLepton2.P4.DeltaR(SelectedEvent.Lepton2.P4)] = TruthLepton2;
   LeptonDeltaR[TruthLepton3.P4.DeltaR(SelectedEvent.Lepton2.P4)] = TruthLepton3;
   LeptonDeltaRIter = LeptonDeltaR.begin();
   SelectedEvent.TruthLepton2 = LeptonDeltaRIter->second;
   LeptonDeltaR.clear();

   LeptonDeltaR[TruthLepton1.P4.DeltaR(SelectedEvent.Lepton3.P4)] = TruthLepton1;
   LeptonDeltaR[TruthLepton2.P4.DeltaR(SelectedEvent.Lepton3.P4)] = TruthLepton2;
   LeptonDeltaR[TruthLepton3.P4.DeltaR(SelectedEvent.Lepton3.P4)] = TruthLepton3;
   LeptonDeltaRIter = LeptonDeltaR.begin();
   SelectedEvent.TruthLepton3 = LeptonDeltaRIter->second;
   LeptonDeltaR.clear();
 }
*/

/////////////////////////
//      Apply Cut      //
/////////////////////////

 GetCutInformation();

// if(PreWZPolarizationTree->EventNumber == 35183){
//   cout<<PreWZPolarizationTree->EventNumber<<" MET: "<<SelectedEvent.WNeutrino.P4.Pt()<<" Px: "<<SelectedEvent.WNeutrino.P4.Px()<<" Py: "<<SelectedEvent.WNeutrino.P4.Py()<<" Pz: "<<SelectedEvent.WNeutrino.P4.Pz()<<" M: "<<SelectedEvent.WNeutrino.P4.M()<<" Mt_W: "<<SelectedEvent.Mt_W<<endl;
//   cout<<"ZLepton1: "<<"E: "<<SelectedEvent.ZLepton1.P4.E()<<" pT: "<<SelectedEvent.ZLepton1.P4.Pt()<<" eta: "<<SelectedEvent.ZLepton1.P4.Eta()<<" phi: "<<SelectedEvent.ZLepton1.P4.Phi()<<" id: "<<SelectedEvent.ZLepton1.pdgID<<endl;
//   cout<<"ZLepton2: "<<"E: "<<SelectedEvent.ZLepton2.P4.E()<<" pT: "<<SelectedEvent.ZLepton2.P4.Pt()<<" eta: "<<SelectedEvent.ZLepton2.P4.Eta()<<" phi: "<<SelectedEvent.ZLepton2.P4.Phi()<<" id: "<<SelectedEvent.ZLepton2.pdgID<<endl;
//   cout<<"WLepton: "<<"E: "<<SelectedEvent.WLepton.P4.E()<<" pT: "<<SelectedEvent.WLepton.P4.Pt()<<" eta: "<<SelectedEvent.WLepton.P4.Eta()<<" phi: "<<SelectedEvent.WLepton.P4.Phi()<<" id: "<<SelectedEvent.WLepton.pdgID<<endl;
// }

///////////////////////////////
///////////////////////////////

/////////////////////////////
//      Record Events      //
/////////////////////////////

 WBoson = SelectedEvent.WLepton.P4 + SelectedEvent.WNeutrino.P4;
 ZBoson = SelectedEvent.ZLepton1.P4 + SelectedEvent.ZLepton2.P4;
 WZPropagator = WBoson + ZBoson;

 if(isLWTNNPolClassifier) LwtnnPolClassifier->ReadPolClassifier(SelectedEvent.ZLepton1.P4, SelectedEvent.ZLepton2.P4, SelectedEvent.WLepton.P4, SelectedEvent.WNeutrino.P4, PreWZPolarizationTree->EventNumber);
 if(isLWTNNPolClassifier) LwtnnPolClassifier->GetFraction(SelectedEvent.LWTNNpLL, SelectedEvent.LWTNNpLT, SelectedEvent.LWTNNpTL, SelectedEvent.LWTNNpTT);

 SelectedEvent.Lep1Pt = SelectedEvent.ZLepton1.P4.Pt();
 SelectedEvent.Lep2Pt = SelectedEvent.ZLepton2.P4.Pt();
 SelectedEvent.Lep3Pt = SelectedEvent.WLepton.P4.Pt();

 SelectedEvent.Lep1Eta = SelectedEvent.ZLepton1.P4.Eta();
 SelectedEvent.Lep2Eta = SelectedEvent.ZLepton2.P4.Eta();
 SelectedEvent.Lep3Eta = SelectedEvent.WLepton.P4.Eta();

 SelectedEvent.Lep1Phi = SelectedEvent.ZLepton1.P4.Phi();
 SelectedEvent.Lep2Phi = SelectedEvent.ZLepton2.P4.Phi();
 SelectedEvent.Lep3Phi = SelectedEvent.WLepton.P4.Phi();

 SelectedEvent.Lep1Flavor = SelectedEvent.ZLepton1.pdgID;
 SelectedEvent.Lep2Flavor = SelectedEvent.ZLepton2.pdgID;
 SelectedEvent.Lep3Flavor = SelectedEvent.WLepton.pdgID;

 SelectedEvent.Lep1Charge = SelectedEvent.ZLepton1.Charge;
 SelectedEvent.Lep2Charge = SelectedEvent.ZLepton2.Charge;
 SelectedEvent.Lep3Charge = SelectedEvent.WLepton.Charge;

 SelectedEvent.Lep1Ambiguity = SelectedEvent.ZLepton1.isAmbiguity;
 SelectedEvent.Lep2Ambiguity = SelectedEvent.ZLepton2.isAmbiguity;
 SelectedEvent.Lep3Ambiguity = SelectedEvent.WLepton.isAmbiguity;

/* SelectedEvent.TruthLep1Pt = SelectedEvent.TruthLepton1.P4.Pt();
 SelectedEvent.TruthLep2Pt = SelectedEvent.TruthLepton2.P4.Pt();
 SelectedEvent.TruthLep3Pt = SelectedEvent.TruthLepton3.P4.Pt();

 SelectedEvent.TruthLep1Eta = SelectedEvent.TruthLepton1.P4.Eta();
 SelectedEvent.TruthLep2Eta = SelectedEvent.TruthLepton2.P4.Eta();
 SelectedEvent.TruthLep3Eta = SelectedEvent.TruthLepton3.P4.Eta();

 SelectedEvent.TruthLep1Phi = SelectedEvent.TruthLepton1.P4.Phi();
 SelectedEvent.TruthLep2Phi = SelectedEvent.TruthLepton2.P4.Phi();
 SelectedEvent.TruthLep3Phi = SelectedEvent.TruthLepton3.P4.Phi();

 SelectedEvent.TruthLep1Flavor = SelectedEvent.TruthLepton1.pdgID;
 SelectedEvent.TruthLep2Flavor = SelectedEvent.TruthLepton2.pdgID;
 SelectedEvent.TruthLep3Flavor = SelectedEvent.TruthLepton3.pdgID;
*/

 SelectedEvent.Flavor = Flavor;

 SelectedEvent.M_WZ = WZPropagator.M();
 SelectedEvent.Mt_WZ = WZPropagator.Mt();
 SelectedEvent.M_Z = ZBoson.M();
 SelectedEvent.Mt_W = CalculateTransverseMass(SelectedEvent.WLepton.P4, SelectedEvent.WNeutrino.P4);
 SelectedEvent.Pt_W = WBoson.Pt();
 SelectedEvent.Pt_Z = ZBoson.Pt();
 SelectedEvent.Pt_WZ = WZPropagator.Pt();
 SelectedEvent.Met = SelectedEvent.WNeutrino.P4.Pt();

 SelectedEvent.Mpx = SelectedEvent.WNeutrino.P4.Px();
 SelectedEvent.Mpy = SelectedEvent.WNeutrino.P4.Py();

 SelectedEvent.DY_WZ = CalculateDY_WZ(WBoson, ZBoson);
 SelectedEvent.DY_3Z = CalculateDY_3Z(ZBoson, SelectedEvent.WLepton.P4);
 SelectedEvent.DY_3N = (SelectedEvent.ZLepton1.Charge < 0) ? CalculateDY_3N(SelectedEvent.ZLepton1.P4, SelectedEvent.WLepton.P4) : CalculateDY_3N(SelectedEvent.ZLepton2.P4, SelectedEvent.WLepton.P4);

 SelectedEvent.CosThetaV = CalculateCosThetaV(WBoson, ZBoson);
 SelectedEvent.CosThetaLepW = CalculateCosThetaLepW(WBoson, ZBoson, SelectedEvent.WLepton.P4);
 SelectedEvent.CosThetaLepZ = (SelectedEvent.ZLepton1.Charge < 0) ? CalculateCosThetaLepZ(WBoson, ZBoson, SelectedEvent.ZLepton1.P4) : CalculateCosThetaLepZ(WBoson, ZBoson, SelectedEvent.ZLepton2.P4);

 SelectedEvent.DeltaPhiLepWLepZ = (SelectedEvent.ZLepton1.Charge < 0) ? CalculateDeltaPhiLepWLepZ(SelectedEvent.ZLepton1.P4, SelectedEvent.WLepton.P4) : CalculateDeltaPhiLepWLepZ(SelectedEvent.ZLepton2.P4, SelectedEvent.WLepton.P4);
 SelectedEvent.DeltaPhiLepWLepZWZFrame = (SelectedEvent.ZLepton1.Charge < 0) ? CalculateDeltaPhiLepWLepZWZFrame(SelectedEvent.ZLepton1.P4, SelectedEvent.WLepton.P4, WZPropagator) : CalculateDeltaPhiLepWLepZWZFrame(SelectedEvent.ZLepton2.P4, SelectedEvent.WLepton.P4, WZPropagator);
 SelectedEvent.R21 = CalculateR21(ZBoson, WBoson);

 SelectedEvent.WLepPt = SelectedEvent.WLep.P4.Pt();
 SelectedEvent.ZLeadingLepPt = SelectedEvent.ZLeadingLep.P4.Pt();
 SelectedEvent.ZSubleadingLepPt = SelectedEvent.ZSubleadingLep.P4.Pt();
 SelectedEvent.WLepEta = SelectedEvent.WLep.P4.Eta();
 SelectedEvent.ZLeadingLepEta = SelectedEvent.ZLeadingLep.P4.Eta();
 SelectedEvent.ZSubleadingLepEta = SelectedEvent.ZSubleadingLep.P4.Eta();
 SelectedEvent.WLepPhi = SelectedEvent.WLep.P4.Phi();
 SelectedEvent.ZLeadingLepPhi = SelectedEvent.ZLeadingLep.P4.Phi();
 SelectedEvent.ZSubleadingLepPhi = SelectedEvent.ZSubleadingLep.P4.Phi();

//Luminosity 1516: 36215
//Luminosity 17  : 43450.4
//Luminosity 18  : 59937.1

 if(SelectedEvent.Year == 1516) SelectedEvent.Luminosity = Lumi1516;
 if(SelectedEvent.Year == 17) SelectedEvent.Luminosity = Lumi17;
 if(SelectedEvent.Year == 18) SelectedEvent.Luminosity = Lumi18;

 SelectedEvent.NormSF = SelectedEvent.Luminosity * SelectedEvent.CrossSection / SelectedEvent.SumOfWeight;
// SelectedEvent.NormSF = 1.0;

 double KFactor = 1.0;
 if(SelectedEvent.MCType == 501793 || SelectedEvent.MCType == 501794 || SelectedEvent.MCType == 500291 || SelectedEvent.MCType == 500295) KFactor = 1.34;
 if(SelectedEvent.MCType == 501795 || SelectedEvent.MCType == 501796 || SelectedEvent.MCType == 500290 || SelectedEvent.MCType == 500294) KFactor = 2.05;
 if(SelectedEvent.MCType == 501797 || SelectedEvent.MCType == 501798 || SelectedEvent.MCType == 500292 || SelectedEvent.MCType == 500296) KFactor = 2.10;
 if(SelectedEvent.MCType == 501799 || SelectedEvent.MCType == 501800 || SelectedEvent.MCType == 500293 || SelectedEvent.MCType == 500297) KFactor = 1.51;

 SelectedEvent.Weight = PreWZPolarizationTree->MCEventWeight * PreWZPolarizationTree->MCPileupWeight * PreWZPolarizationTree->JetWeight * PreWZPolarizationTree->VertexWeight * KFactor;
 SelectedEvent.WeightNoKFactor = PreWZPolarizationTree->MCEventWeight * PreWZPolarizationTree->MCPileupWeight * PreWZPolarizationTree->JetWeight * PreWZPolarizationTree->VertexWeight;

 SelectedEvent.WeightNormalized = SelectedEvent.NormSF * SelectedEvent.Weight;
 SelectedEvent.WeightNormalizedNoKFactor = SelectedEvent.NormSF * SelectedEvent.WeightNoKFactor;

 SelectedEvent.passSignalRegion = (SelectedEvent.Pt_Z > 200)
                                  && (SelectedEvent.Pt_WZ < 70);

 SelectedEvent.pass100SignalRegion = (SelectedEvent.Pt_Z > 100)
                                     && (SelectedEvent.Pt_WZ < 70);

 SelectedEvent.passHighPtWZCR = (SelectedEvent.Pt_Z > 200)
                                && (SelectedEvent.Pt_WZ > 70);

 SelectedEvent.passLowPtZCR = (SelectedEvent.Pt_Z < 200)
                              && (SelectedEvent.Pt_WZ < 70);

 if(isData) SelectedEvent.Luminosity = 1.0;
 if(isData) SelectedEvent.CrossSection = 1.0;
 if(isData) SelectedEvent.SumOfWeight = 1.0;
 if(isData) SelectedEvent.WeightNormalized = 1.0;
 if(isData) SelectedEvent.WeightNormalizedNoKFactor = 1.0;
 if(isData) SelectedEvent.Lep1WeightZ = 1.0;
 if(isData) SelectedEvent.Lep2WeightZ = 1.0;
 if(isData) SelectedEvent.Lep3WeightZ = 1.0;
 if(isData) SelectedEvent.Lep1WeightW = 1.0;
 if(isData) SelectedEvent.Lep2WeightW = 1.0;
 if(isData) SelectedEvent.Lep3WeightW = 1.0;
 if(isData) SelectedEvent.Lep1MediumIDWeight = 1.0;
 if(isData) SelectedEvent.Lep1TightIDWeight = 1.0;
 if(isData) SelectedEvent.Lep1MediumIsoWeight = 1.0;
 if(isData) SelectedEvent.Lep1TightIsoWeight = 1.0;
 if(isData) SelectedEvent.Lep2MediumIDWeight = 1.0;
 if(isData) SelectedEvent.Lep2TightIDWeight = 1.0;
 if(isData) SelectedEvent.Lep2MediumIsoWeight = 1.0;
 if(isData) SelectedEvent.Lep2TightIsoWeight = 1.0;
 if(isData) SelectedEvent.Lep3MediumIDWeight = 1.0;
 if(isData) SelectedEvent.Lep3TightIDWeight = 1.0;
 if(isData) SelectedEvent.Lep3MediumIsoWeight = 1.0;
 if(isData) SelectedEvent.Lep3TightIsoWeight = 1.0;


 if(isTest) cout<<"CrossSection: "<<SelectedEvent.CrossSection<<" Luminosity: "<<SelectedEvent.Luminosity<<" MCEventWeight: "<<PreWZPolarizationTree->MCEventWeight<<" Weight: "<<SelectedEvent.Weight<<" SumOfWeight: "<<SelectedEvent.SumOfWeight<<" WeightNormalized: "<<SelectedEvent.WeightNormalized<<" Year: "<<SelectedEvent.Year<<endl;

 SelectedEvent.TotalWeight = SelectedEvent.WeightNormalized * SelectedEvent.Lep1WeightZ * SelectedEvent.Lep2WeightZ * SelectedEvent.Lep3WeightW;
 SelectedEvent.TotalWeightNoKFactor = SelectedEvent.WeightNormalizedNoKFactor * SelectedEvent.Lep1WeightZ * SelectedEvent.Lep2WeightZ * SelectedEvent.Lep3WeightW;

/* if(doTruthSelection){
   isTauEvent = false;
   if(SelectedEvent.MCType == 364253){
     for(int i = 0; i < PreWZPolarizationTree->truth_pid->size(); i++){
       if(fabs(PreWZPolarizationTree->truth_pid->at(i)) == 15 || fabs(PreWZPolarizationTree->truth_pid->at(i)) == 16) isTauEvent = true;
     }

     int CountNeutrino = 0;
     int NeutrinoID = 0;
     for(int i = 0; i < PreWZPolarizationTree->truth_pid->size(); i++){
       if(fabs(PreWZPolarizationTree->truth_pid->at(i)) == 12 || fabs(PreWZPolarizationTree->truth_pid->at(i)) == 14
                                                              || fabs(PreWZPolarizationTree->truth_pid->at(i)) == 16){
         CountNeutrino++;
         NeutrinoID = i;
       }
     }
     if(CountNeutrino == 1){
       TLorentzVector TruthNeutrino;
       TruthNeutrino.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(NeutrinoID) / GeV, PreWZPolarizationTree->truth_eta->at(NeutrinoID), PreWZPolarizationTree->truth_phi->at(NeutrinoID), PreWZPolarizationTree->truth_e->at(NeutrinoID) / GeV);
       SelectedEvent.TruthNuPz = TruthNeutrino.Pz();
     }
   }
 }

 SelectedEvent.isTauEvent = isTauEvent;
*/

 TLorentzVector TruthZLepton1, TruthZLepton2, TruthWLepton, TruthNeutrino;
 TruthZLepton1.SetPtEtaPhiM(0,0,0,0);
 TruthZLepton2.SetPtEtaPhiM(0,0,0,0);
 TruthWLepton.SetPtEtaPhiM(0,0,0,0);
 TruthNeutrino.SetPtEtaPhiM(0,0,0,0);

 if(SelectedEvent.MCType == 364253){
   //if(genTruthLepton(TruthZLepton1, TruthZLepton2, TruthWLepton, TruthNeutrino)){
   //  if(isLWTNNNLOPol) SelectedEvent.LLNLOWeight = LwtnnNLOPol->GetNLOWeight("00dnn", TruthZLepton1, TruthZLepton2, TruthWLepton, TruthNeutrino);
   //  if(isLWTNNNLOPol) SelectedEvent.LTNLOWeight = LwtnnNLOPol->GetNLOWeight("0Tdnn", TruthZLepton1, TruthZLepton2, TruthWLepton, TruthNeutrino);
   //  if(isLWTNNNLOPol) SelectedEvent.TLNLOWeight = LwtnnNLOPol->GetNLOWeight("T0dnn", TruthZLepton1, TruthZLepton2, TruthWLepton, TruthNeutrino);
   //  if(isLWTNNNLOPol) SelectedEvent.TTNLOWeight = LwtnnNLOPol->GetNLOWeight("TTdnn", TruthZLepton1, TruthZLepton2, TruthWLepton, TruthNeutrino);
   //}
 }

 PDFWeights.clear();
 QCDWeights.clear();
 if(PreWZPolarizationTree->doPDFAndQCDUnc && isNominal){
   for(int iunc = 0; iunc < PreWZPolarizationTree->MCEventWeights->size(); iunc++){
     pair<int, int> TypeUncPair;
     TypeUncPair = make_pair(SelectedEvent.MCType, iunc);

     if(TheoryErrorType[TypeUncPair] == "PDF"){
       double MCEventWeight = PreWZPolarizationTree->MCEventWeights->at(iunc);
       double WeightNoKFactor = MCEventWeight * PreWZPolarizationTree->MCPileupWeight * PreWZPolarizationTree->JetWeight * PreWZPolarizationTree->VertexWeight;
       double WeightNormalizedNoKFactor = SelectedEvent.NormSF * WeightNoKFactor;
       double TotalWeightNoKFactor = WeightNormalizedNoKFactor * SelectedEvent.Lep1WeightZ * SelectedEvent.Lep2WeightZ * SelectedEvent.Lep3WeightW;
       PDFWeights.push_back(TotalWeightNoKFactor);
       //if(isTest) cout<<iunc<<" "<<PreWZPolarizationTree->WeightNames->at(iunc)<<" "<<TheoryErrorType[TypeUncPair]<<" "<<TotalWeightNoKFactor<<endl;
     }
     if(TheoryErrorType[TypeUncPair] == "QCD"){
       double MCEventWeight = PreWZPolarizationTree->MCEventWeights->at(iunc);
       double WeightNoKFactor = MCEventWeight * PreWZPolarizationTree->MCPileupWeight * PreWZPolarizationTree->JetWeight * PreWZPolarizationTree->VertexWeight;
       double WeightNormalizedNoKFactor = SelectedEvent.NormSF * WeightNoKFactor;
       double TotalWeightNoKFactor = WeightNormalizedNoKFactor * SelectedEvent.Lep1WeightZ * SelectedEvent.Lep2WeightZ * SelectedEvent.Lep3WeightW;
       QCDWeights.push_back(TotalWeightNoKFactor);
       //if(isTest) cout<<iunc<<" "<<PreWZPolarizationTree->WeightNames->at(iunc)<<" "<<TheoryErrorType[TypeUncPair]<<" "<<TotalWeightNoKFactor<<endl;
     }
   }
   if(isTest) cout<<"PDF weight size: "<<PDFWeights.size()<<" QCD weight size: "<<QCDWeights.size()<<endl;
 }

 if(JustGenerateTree){
   FillZLepton1CutFlow();
   FillZLepton2CutFlow();
   FillWLeptonCutFlow();
   FillZLepton1WeightedCutFlow();
   FillZLepton2WeightedCutFlow();
   FillWLeptonWeightedCutFlow();
 }

 if(SelectedEvent.isThreeSameCharge == true) return false;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "3 same charge lepton", 1, isNominal);
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "3 same charge lepton", SelectedEvent.TotalWeightNoKFactor, isNominal);

 PassTrig = (SelectedEvent.Lepton1.triggerMatched || SelectedEvent.Lepton2.triggerMatched || SelectedEvent.Lepton3.triggerMatched);

// if(JustGenerateTree) FillCutFlow();
// if(JustGenerateTree) FillWeightedCutFlow();

 if(!PassTrig) return false;

 double LeadingPtDecision = 27.0;
 if(SelectedEvent.UniqueYear == 15) LeadingPtDecision = 25.0;
 else LeadingPtDecision = 27.0;

// set<double> LeptonPt;
// LeptonPt.insert(SelectedEvent.Lepton1.P4.Pt());
// LeptonPt.insert(SelectedEvent.Lepton2.P4.Pt());
// LeptonPt.insert(SelectedEvent.Lepton3.P4.Pt());
// set<double>::iterator LeptonPtIter = LeptonPt.end();

 set<double> LeptonPtTrig;
 if(SelectedEvent.Lepton1.triggerMatched) LeptonPtTrig.insert(SelectedEvent.Lepton1.P4.Pt());
 if(SelectedEvent.Lepton2.triggerMatched) LeptonPtTrig.insert(SelectedEvent.Lepton2.P4.Pt());
 if(SelectedEvent.Lepton3.triggerMatched) LeptonPtTrig.insert(SelectedEvent.Lepton3.P4.Pt());
 auto LeptonPtTrigIter = LeptonPtTrig.end();

// passLeadingLepPt = (*(--LeptonPtIter) > LeadingPtDecision) && (*(--LeptonPtTrigIter) > LeadingPtDecision);
 passLeadingLepPt = (*(--LeptonPtTrigIter) > LeadingPtDecision);

 if(JustGenerateTree) FillCutFlow();
 if(JustGenerateTree) FillWeightedCutFlow();

 if(!passLeadingLepPt) return false;

// cout<<PreWZPolarizationTree->EventNumber<<endl;

 int DecayChannel = 0;
 if(SelectedEvent.Flavor == "mmm") DecayChannel = 1;
 if(SelectedEvent.Flavor == "emm") DecayChannel = 2;
 if(SelectedEvent.Flavor == "eem") DecayChannel = 3;
 if(SelectedEvent.Flavor == "eee") DecayChannel = 4;
 if(SelectedEvent.m_Channel == 5) DecayChannel = 5;
 if(SelectedEvent.m_Channel == 6) DecayChannel = 6;

 SelectedEvent.DecayChannel = DecayChannel;

 SelectedEvent.EventNumber = PreWZPolarizationTree->EventNumber;

 WZPolarizationTree->Flavor = DecayChannel;
 WZPolarizationTree->EventNumber = SelectedEvent.EventNumber;
 WZPolarizationTree->Yields = SelectedEvent.Yields;
 WZPolarizationTree->isMC = SelectedEvent.isMC;
 WZPolarizationTree->Channel = SelectedEvent.Channel;
 WZPolarizationTree->Year = SelectedEvent.Year;
 WZPolarizationTree->NormSF = SelectedEvent.NormSF;
 WZPolarizationTree->WeightSign = SelectedEvent.WeightSign;
 WZPolarizationTree->WeightNormalized = SelectedEvent.WeightNormalized;
 WZPolarizationTree->Weight = SelectedEvent.Weight;
 WZPolarizationTree->TotalWeight = SelectedEvent.TotalWeight;
 WZPolarizationTree->WeightNormalizedNoKFactor = SelectedEvent.WeightNormalizedNoKFactor;
 WZPolarizationTree->WeightNoKFactor = SelectedEvent.WeightNoKFactor;
 WZPolarizationTree->TotalWeightNoKFactor = SelectedEvent.TotalWeightNoKFactor;
 WZPolarizationTree->M_WZ = SelectedEvent.M_WZ;
 WZPolarizationTree->M_3l = SelectedEvent.M_3l;
 WZPolarizationTree->Mt_WZ = SelectedEvent.Mt_WZ;
 WZPolarizationTree->M_Z = SelectedEvent.M_Z;
 WZPolarizationTree->Mt_W = SelectedEvent.Mt_W;
 WZPolarizationTree->Met = SelectedEvent.Met;
 WZPolarizationTree->Njets = SelectedEvent.Njets;
 WZPolarizationTree->NBjets = SelectedEvent.NBjets;
 WZPolarizationTree->SumOfWeight = SelectedEvent.SumOfWeight;
 WZPolarizationTree->Luminosity = SelectedEvent.Luminosity;
 WZPolarizationTree->CrossSection = SelectedEvent.CrossSection;
 WZPolarizationTree->Lep1Pt = SelectedEvent.Lep1Pt;
 WZPolarizationTree->Lep2Pt = SelectedEvent.Lep2Pt;
 WZPolarizationTree->Lep3Pt = SelectedEvent.Lep3Pt;
 WZPolarizationTree->Lep1Eta = SelectedEvent.Lep1Eta;
 WZPolarizationTree->Lep2Eta = SelectedEvent.Lep2Eta;
 WZPolarizationTree->Lep3Eta = SelectedEvent.Lep3Eta;
 WZPolarizationTree->Lep1Phi = SelectedEvent.Lep1Phi;
 WZPolarizationTree->Lep2Phi = SelectedEvent.Lep2Phi;
 WZPolarizationTree->Lep3Phi = SelectedEvent.Lep3Phi;
 WZPolarizationTree->Lep1Flavor = SelectedEvent.Lep1Flavor;
 WZPolarizationTree->Lep2Flavor = SelectedEvent.Lep2Flavor;
 WZPolarizationTree->Lep3Flavor = SelectedEvent.Lep3Flavor;
 WZPolarizationTree->Lep1Charge = SelectedEvent.Lep1Charge;
 WZPolarizationTree->Lep2Charge = SelectedEvent.Lep2Charge;
 WZPolarizationTree->Lep3Charge = SelectedEvent.Lep3Charge;
 WZPolarizationTree->Lep1Ambiguity = SelectedEvent.Lep1Ambiguity;
 WZPolarizationTree->Lep2Ambiguity = SelectedEvent.Lep2Ambiguity;
 WZPolarizationTree->Lep3Ambiguity = SelectedEvent.Lep3Ambiguity;
/* WZPolarizationTree->TruthLep1Pt = SelectedEvent.TruthLep1Pt;
 WZPolarizationTree->TruthLep2Pt = SelectedEvent.TruthLep2Pt;
 WZPolarizationTree->TruthLep3Pt = SelectedEvent.TruthLep3Pt;
 WZPolarizationTree->TruthLep1Eta = SelectedEvent.TruthLep1Eta;
 WZPolarizationTree->TruthLep2Eta = SelectedEvent.TruthLep2Eta;
 WZPolarizationTree->TruthLep3Eta = SelectedEvent.TruthLep3Eta;
 WZPolarizationTree->TruthLep1Phi = SelectedEvent.TruthLep1Phi;
 WZPolarizationTree->TruthLep2Phi = SelectedEvent.TruthLep2Phi;
 WZPolarizationTree->TruthLep3Phi = SelectedEvent.TruthLep3Phi;
 WZPolarizationTree->TruthLep1Flavor = SelectedEvent.TruthLep1Flavor;
 WZPolarizationTree->TruthLep2Flavor = SelectedEvent.TruthLep2Flavor;
 WZPolarizationTree->TruthLep3Flavor = SelectedEvent.TruthLep3Flavor;
*/ WZPolarizationTree->Mpx = SelectedEvent.Mpx;
 WZPolarizationTree->Mpy = SelectedEvent.Mpy;
 WZPolarizationTree->Mpz = SelectedEvent.Mpz;
 WZPolarizationTree->LWTNNNuPz = SelectedEvent.LWTNNNuPz;
 WZPolarizationTree->TruthNuPz = SelectedEvent.TruthNuPz;
 WZPolarizationTree->LWTNNpLL = SelectedEvent.LWTNNpLL;
 WZPolarizationTree->LWTNNpLT = SelectedEvent.LWTNNpLT;
 WZPolarizationTree->LWTNNpTL = SelectedEvent.LWTNNpTL;
 WZPolarizationTree->LWTNNpTT = SelectedEvent.LWTNNpTT;
 WZPolarizationTree->LLNLOWeight = SelectedEvent.LLNLOWeight;
 WZPolarizationTree->LTNLOWeight = SelectedEvent.LTNLOWeight;
 WZPolarizationTree->TLNLOWeight = SelectedEvent.TLNLOWeight;
 WZPolarizationTree->TTNLOWeight = SelectedEvent.TTNLOWeight;
 WZPolarizationTree->Lep1WeightZ = SelectedEvent.Lep1WeightZ;
 WZPolarizationTree->Lep2WeightZ = SelectedEvent.Lep2WeightZ;
 WZPolarizationTree->Lep3WeightZ = SelectedEvent.Lep3WeightZ;
 WZPolarizationTree->Lep1WeightW = SelectedEvent.Lep1WeightW;
 WZPolarizationTree->Lep2WeightW = SelectedEvent.Lep2WeightW;
 WZPolarizationTree->Lep3WeightW = SelectedEvent.Lep3WeightW;
 WZPolarizationTree->Pt_W = SelectedEvent.Pt_W;
 WZPolarizationTree->Pt_Z = SelectedEvent.Pt_Z;
 WZPolarizationTree->Pt_WZ = SelectedEvent.Pt_WZ;
 WZPolarizationTree->SumJetPt = SelectedEvent.SumJetPt;
 WZPolarizationTree->CosThetaV = SelectedEvent.CosThetaV;
 WZPolarizationTree->CosThetaLepW = SelectedEvent.CosThetaLepW;
 WZPolarizationTree->CosThetaLepZ = SelectedEvent.CosThetaLepZ;
 WZPolarizationTree->DY_WZ = SelectedEvent.DY_WZ;
 WZPolarizationTree->DY_3Z = SelectedEvent.DY_3Z;
 WZPolarizationTree->DY_3N = SelectedEvent.DY_3N;
 WZPolarizationTree->Truth_Pt_WZ = SelectedEvent.Truth_Pt_WZ;
 WZPolarizationTree->DeltaPhiLepWLepZ = SelectedEvent.DeltaPhiLepWLepZ;
 WZPolarizationTree->DeltaPhiLepWLepZWZFrame = SelectedEvent.DeltaPhiLepWLepZWZFrame;
 WZPolarizationTree->R21 = SelectedEvent.R21;
 WZPolarizationTree->WLepPt = SelectedEvent.WLepPt;
 WZPolarizationTree->ZLeadingLepPt = SelectedEvent.ZLeadingLepPt;
 WZPolarizationTree->ZSubleadingLepPt = SelectedEvent.ZSubleadingLepPt;
 WZPolarizationTree->WLepEta = SelectedEvent.WLepEta;
 WZPolarizationTree->ZLeadingLepEta = SelectedEvent.ZLeadingLepEta;
 WZPolarizationTree->ZSubleadingLepEta = SelectedEvent.ZSubleadingLepEta;
 WZPolarizationTree->WLepPhi = SelectedEvent.WLepPhi;
 WZPolarizationTree->ZLeadingLepPhi = SelectedEvent.ZLeadingLepPhi;
 WZPolarizationTree->ZSubleadingLepPhi = SelectedEvent.ZSubleadingLepPhi;
 WZPolarizationTree->Lep1D0Sig = fabs(SelectedEvent.ZLepton1.d0Sig);
 WZPolarizationTree->Lep2D0Sig = fabs(SelectedEvent.ZLepton2.d0Sig);
 WZPolarizationTree->Lep3D0Sig = fabs(SelectedEvent.WLepton.d0Sig);

 WZPolarizationTree->Lep1MediumIDWeight = SelectedEvent.Lep1MediumIDWeight;
 WZPolarizationTree->Lep2MediumIDWeight = SelectedEvent.Lep2MediumIDWeight;
 WZPolarizationTree->Lep3MediumIDWeight = SelectedEvent.Lep3MediumIDWeight;
 WZPolarizationTree->Lep1TightIDWeight = SelectedEvent.Lep1TightIDWeight;
 WZPolarizationTree->Lep2TightIDWeight = SelectedEvent.Lep2TightIDWeight;
 WZPolarizationTree->Lep3TightIDWeight = SelectedEvent.Lep3TightIDWeight;
 WZPolarizationTree->Lep1MediumIsoWeight = SelectedEvent.Lep1MediumIsoWeight;
 WZPolarizationTree->Lep2MediumIsoWeight = SelectedEvent.Lep2MediumIsoWeight;
 WZPolarizationTree->Lep3MediumIsoWeight = SelectedEvent.Lep3MediumIsoWeight;
 WZPolarizationTree->Lep1TightIsoWeight = SelectedEvent.Lep1TightIsoWeight;
 WZPolarizationTree->Lep2TightIsoWeight = SelectedEvent.Lep2TightIsoWeight;
 WZPolarizationTree->Lep3TightIsoWeight = SelectedEvent.Lep3TightIsoWeight;


 WZPolarizationTree->passZZCR = SelectedEvent.passZZCR;
 WZPolarizationTree->passTopCR = SelectedEvent.passTopCR;
 WZPolarizationTree->passZFakeElCR = SelectedEvent.passZFakeElCR;
 WZPolarizationTree->passZFakeElCR_UpSys = SelectedEvent.passZFakeElCR_UpSys;
 WZPolarizationTree->passZFakeElCR_DownSys = SelectedEvent.passZFakeElCR_DownSys;
 WZPolarizationTree->passZFakeMuCR = SelectedEvent.passZFakeMuCR;
 WZPolarizationTree->passTopElCR = SelectedEvent.passTopElCR;
 WZPolarizationTree->passTopMuCR = SelectedEvent.passTopMuCR;
 WZPolarizationTree->passWZInclusive = SelectedEvent.passWZInclusive;
 WZPolarizationTree->passHardWZInclusive = SelectedEvent.passHardWZInclusive;
 WZPolarizationTree->passWZInclusiveLoose = SelectedEvent.passWZInclusiveLoose;
 WZPolarizationTree->passHardWZInclusiveLoose = SelectedEvent.passHardWZInclusiveLoose;
 WZPolarizationTree->passWZqqSR = SelectedEvent.passWZqqSR;
 WZPolarizationTree->passWZqqCR = SelectedEvent.passWZqqCR;
 WZPolarizationTree->passWZVBSSR = SelectedEvent.passWZVBSSR;
 WZPolarizationTree->passWZVBSCR = SelectedEvent.passWZVBSCR;
 WZPolarizationTree->passWZInclusiveNoMET = SelectedEvent.passWZInclusiveNoMET;
 WZPolarizationTree->passTopEnrichCR = SelectedEvent.passTopEnrichCR;
 WZPolarizationTree->passTTT = SelectedEvent.passTTT;
 WZPolarizationTree->passTTL = SelectedEvent.passTTL;
 WZPolarizationTree->passTLT = SelectedEvent.passTLT;
 WZPolarizationTree->passLTT = SelectedEvent.passLTT;
 WZPolarizationTree->passTLL = SelectedEvent.passTLL;
 WZPolarizationTree->passLTL = SelectedEvent.passLTL;
 WZPolarizationTree->passLLT = SelectedEvent.passLLT;
 WZPolarizationTree->passZCondition = SelectedEvent.passZCondition;
 WZPolarizationTree->passWCondition = SelectedEvent.passWCondition;
 WZPolarizationTree->passSignalRegion = SelectedEvent.passSignalRegion;
 WZPolarizationTree->pass100SignalRegion = SelectedEvent.pass100SignalRegion;
 WZPolarizationTree->passHighPtWZCR = SelectedEvent.passHighPtWZCR;
 WZPolarizationTree->passLowPtZCR = SelectedEvent.passLowPtZCR;
 WZPolarizationTree->passTruthMatch1 = SelectedEvent.passTruthMatch1;
 WZPolarizationTree->passTruthMatch2 = SelectedEvent.passTruthMatch2;
 WZPolarizationTree->passTruthMatch3 = SelectedEvent.passTruthMatch3;
 WZPolarizationTree->passZCondition1 = SelectedEvent.passZCondition1;
 WZPolarizationTree->passZCondition2 = SelectedEvent.passZCondition2;
 WZPolarizationTree->passZCondition3 = SelectedEvent.passZCondition3;
 WZPolarizationTree->passWCondition1 = SelectedEvent.passWCondition1;
 WZPolarizationTree->passWCondition2 = SelectedEvent.passWCondition2;
 WZPolarizationTree->passWCondition3 = SelectedEvent.passWCondition3;
 WZPolarizationTree->passMediumID1 = SelectedEvent.passMediumID1;
 WZPolarizationTree->passMediumID2 = SelectedEvent.passMediumID2;
 WZPolarizationTree->passMediumID3 = SelectedEvent.passMediumID3;
 WZPolarizationTree->passTightID1 = SelectedEvent.passTightID1;
 WZPolarizationTree->passTightID2 = SelectedEvent.passTightID2;
 WZPolarizationTree->passTightID3 = SelectedEvent.passTightID3;
 WZPolarizationTree->passIPID1 = SelectedEvent.passIPID1;
 WZPolarizationTree->passIPID2 = SelectedEvent.passIPID2;
 WZPolarizationTree->passIPID3 = SelectedEvent.passIPID3;
 WZPolarizationTree->isTauEvent = SelectedEvent.isTauEvent;
 WZPolarizationTree->passDeltaR = SelectedEvent.passDeltaR;
 WZPolarizationTree->passThreeBaseline = SelectedEvent.passThreeBaseline;
 WZPolarizationTree->passZZVeto = ((PreWZPolarizationTree->nSoftElectrons + PreWZPolarizationTree->nSoftMuons) < 4);
 WZPolarizationTree->vPDFWeights = PDFWeights;
 WZPolarizationTree->vQCDWeights = QCDWeights;

 ElectronSize.clear();
 MuonSize.clear();

 return true;
}

int loopWZPolarization::FindSysIndex(const char* sysname)
{
 int index = 0;
 index = SysNameIndex[(TString)sysname];
 return index;
}

void loopWZPolarization::DefineSysName()
{
 SysNameIndex[(TString)"nominal"] = 0;
 SysNameIndex[(TString)"EG_RESOLUTION_ALL__1down"] = 1;
 SysNameIndex[(TString)"EG_RESOLUTION_ALL__1up"] = 2;
 SysNameIndex[(TString)"EG_SCALE_AF2__1down"] = 3;
 SysNameIndex[(TString)"EG_SCALE_AF2__1up"] = 4;
 SysNameIndex[(TString)"EG_SCALE_ALL__1down"] = 5;
 SysNameIndex[(TString)"EG_SCALE_ALL__1up"] = 6;
 SysNameIndex[(TString)"EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1down"] = 7;
 SysNameIndex[(TString)"EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1up"] = 8;
 SysNameIndex[(TString)"EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down"] = 9;
 SysNameIndex[(TString)"EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up"] = 10;
 SysNameIndex[(TString)"EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down"] = 11;
 SysNameIndex[(TString)"EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up"] = 12;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_0__1down"] = 13;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_0__1up"] = 14;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_1__1down"] = 15;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_1__1up"] = 16;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_2__1down"] = 17;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_2__1up"] = 18;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_3__1down"] = 19;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_3__1up"] = 20;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_4__1down"] = 21;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_4__1up"] = 22;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_5__1down"] = 23;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_5__1up"] = 24;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_6__1down"] = 25;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_6__1up"] = 26;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_7__1down"] = 27;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_7__1up"] = 28;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_8__1down"] = 29;
 SysNameIndex[(TString)"FT_EFF_Eigen_B_8__1up"] = 30;
 SysNameIndex[(TString)"FT_EFF_Eigen_C_0__1down"] = 31;
 SysNameIndex[(TString)"FT_EFF_Eigen_C_0__1up"] = 32;
 SysNameIndex[(TString)"FT_EFF_Eigen_C_1__1down"] = 33;
 SysNameIndex[(TString)"FT_EFF_Eigen_C_1__1up"] = 34;
 SysNameIndex[(TString)"FT_EFF_Eigen_C_2__1down"] = 35;
 SysNameIndex[(TString)"FT_EFF_Eigen_C_2__1up"] = 36;
 SysNameIndex[(TString)"FT_EFF_Eigen_C_3__1down"] = 37;
 SysNameIndex[(TString)"FT_EFF_Eigen_C_3__1up"] = 38;
 SysNameIndex[(TString)"FT_EFF_Eigen_C_4__1down"] = 39;
 SysNameIndex[(TString)"FT_EFF_Eigen_C_4__1up"] = 40;
 SysNameIndex[(TString)"FT_EFF_Eigen_Light_0__1down"] = 41;
 SysNameIndex[(TString)"FT_EFF_Eigen_Light_0__1up"] = 42;
 SysNameIndex[(TString)"FT_EFF_Eigen_Light_1__1down"] = 43;
 SysNameIndex[(TString)"FT_EFF_Eigen_Light_1__1up"] = 44;
 SysNameIndex[(TString)"FT_EFF_Eigen_Light_2__1down"] = 45;
 SysNameIndex[(TString)"FT_EFF_Eigen_Light_2__1up"] = 46;
 SysNameIndex[(TString)"FT_EFF_Eigen_Light_3__1down"] = 47;
 SysNameIndex[(TString)"FT_EFF_Eigen_Light_3__1up"] = 48;
 SysNameIndex[(TString)"FT_EFF_extrapolation__1down"] = 49;
 SysNameIndex[(TString)"FT_EFF_extrapolation__1up"] = 50;
 SysNameIndex[(TString)"FT_EFF_extrapolation_from_charm__1down"] = 51;
 SysNameIndex[(TString)"FT_EFF_extrapolation_from_charm__1up"] = 52;
 SysNameIndex[(TString)"JET_EtaIntercalibration_NonClosure_2018data__1down"] = 53;
 SysNameIndex[(TString)"JET_EtaIntercalibration_NonClosure_2018data__1up"] = 54;
 SysNameIndex[(TString)"JET_EtaIntercalibration_NonClosure_highE__1down"] = 55;
 SysNameIndex[(TString)"JET_EtaIntercalibration_NonClosure_highE__1up"] = 56;
 SysNameIndex[(TString)"JET_EtaIntercalibration_NonClosure_negEta__1down"] = 57;
 SysNameIndex[(TString)"JET_EtaIntercalibration_NonClosure_negEta__1up"] = 58;
 SysNameIndex[(TString)"JET_EtaIntercalibration_NonClosure_posEta__1down"] = 59;
 SysNameIndex[(TString)"JET_EtaIntercalibration_NonClosure_posEta__1up"] = 60;
 SysNameIndex[(TString)"JET_Flavor_Response__1down"] = 61;
 SysNameIndex[(TString)"JET_Flavor_Response__1up"] = 62;
 SysNameIndex[(TString)"JET_GroupedNP_1__1down"] = 63;
 SysNameIndex[(TString)"JET_GroupedNP_1__1up"] = 64;
 SysNameIndex[(TString)"JET_GroupedNP_2__1down"] = 65;
 SysNameIndex[(TString)"JET_GroupedNP_2__1up"] = 66;
 SysNameIndex[(TString)"JET_GroupedNP_3__1down"] = 67;
 SysNameIndex[(TString)"JET_GroupedNP_3__1up"] = 68;
 SysNameIndex[(TString)"JET_JER_DataVsMC_MC16__1down"] = 69;
 SysNameIndex[(TString)"JET_JER_DataVsMC_MC16__1up"] = 70;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_1__1down"] = 71;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_1__1up"] = 72;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_2__1down"] = 73;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_2__1up"] = 74;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_3__1down"] = 75;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_3__1up"] = 76;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_4__1down"] = 77;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_4__1up"] = 78;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_5__1down"] = 79;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_5__1up"] = 80;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_6__1down"] = 81;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_6__1up"] = 82;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_7restTerm__1down"] = 83;
 SysNameIndex[(TString)"JET_JER_EffectiveNP_7restTerm__1up"] = 84;
 SysNameIndex[(TString)"JET_JvtEfficiency__1down"] = 85;
 SysNameIndex[(TString)"JET_JvtEfficiency__1up"] = 86;
 SysNameIndex[(TString)"JET_fJvtEfficiency__1down"] = 87;
 SysNameIndex[(TString)"JET_fJvtEfficiency__1up"] = 88;
 SysNameIndex[(TString)"MET_SoftTrk_ResoPara__1down"] = 89;
 SysNameIndex[(TString)"MET_SoftTrk_ResoPara__1up"] = 90;
 SysNameIndex[(TString)"MET_SoftTrk_ResoPerp__1down"] = 91;
 SysNameIndex[(TString)"MET_SoftTrk_ResoPerp__1up"] = 92;
 SysNameIndex[(TString)"MET_SoftTrk_ScaleDown__1down"] = 93;
 SysNameIndex[(TString)"MET_SoftTrk_ScaleUp__1up"] = 94;
 SysNameIndex[(TString)"MUON_ID__1down"] = 95;
 SysNameIndex[(TString)"MUON_ID__1up"] = 96;
 SysNameIndex[(TString)"MUON_MS__1down"] = 97;
 SysNameIndex[(TString)"MUON_MS__1up"] = 98;
 SysNameIndex[(TString)"MUON_SAGITTA_RESBIAS__1down"] = 99;
 SysNameIndex[(TString)"MUON_SAGITTA_RESBIAS__1up"] = 100;
 SysNameIndex[(TString)"MUON_SAGITTA_RHO__1down"] = 101;
 SysNameIndex[(TString)"MUON_SAGITTA_RHO__1up"] = 102;
 SysNameIndex[(TString)"MUON_SCALE__1down"] = 103;
 SysNameIndex[(TString)"MUON_SCALE__1up"] = 104;
 SysNameIndex[(TString)"PRW_DATASF__1down"] = 105;
 SysNameIndex[(TString)"PRW_DATASF__1up"] = 106;

}

void EventWZPolarization::ResetEvent()
{
   //MCType = 0;
   Flavor = "";
   EventNumber = -999;
   Yields = 0;
   DecayChannel = -1;
   isMC = 0;
   //Channel = 0;
   //Year = 0;
   //UniqueYear = 0;
   NormSF = 1.0;
   WeightSign = 1.0;
   WeightNormalized = 1.0;
   Weight = 1.0;
   TotalWeight = 1.0;
   WeightNormalizedNoKFactor = 1.0;
   WeightNoKFactor = 1.0;
   TotalWeightNoKFactor = 1.0;
   M_WZ = 0.0;
   M_3l = 0.0;
   Mt_WZ = 0.0;
   M_Z = 0.0;
   ZY = 0.0;
   Mt_W = 0.0;
   Met = 0.0;
   Njets = -1;
   NBjets = -1;
   //SumOfWeight = 1.0;
   Luminosity = 1.0;
   //CrossSection = 1.0;
   Lep1Pt = 0.0;
   Lep2Pt = 0.0;
   Lep3Pt = 0.0;
   Lep1Eta = 0.0;
   Lep2Eta = 0.0;
   Lep3Eta = 0.0;
   Lep1Phi = 0.0;
   Lep2Phi = 0.0;
   Lep3Phi = 0.0;
   dR_Lep1_Lep2 = -99.0;
   dR_Lep1_Lep3 = -99.0;
   dR_Lep2_Lep3 = -99.0;
   Lep1Flavor = 0;
   Lep2Flavor = 0;
   Lep3Flavor = 0;
   Lep1Charge = 0;
   Lep2Charge = 0;
   Lep3Charge = 0;
   Lep1Ambiguity = -999;
   Lep2Ambiguity = -999;
   Lep3Ambiguity = -999;
   TruthLep1Pt = 0.0;
   TruthLep2Pt = 0.0;
   TruthLep3Pt = 0.0;
   TruthLep1Eta = 0.0;
   TruthLep2Eta = 0.0;
   TruthLep3Eta = 0.0;
   TruthLep1Phi = 0.0;
   TruthLep2Phi = 0.0;
   TruthLep3Phi = 0.0;
   TruthLep1Flavor = 0;
   TruthLep2Flavor = 0;
   TruthLep3Flavor = 0;
   Mpx = 0.0;
   Mpy = 0.0;
   Mpz = 0.0;
   LWTNNNuPz = -99.0;
   TruthNuPz = -99.0;
   LWTNNpLL = -99.0;
   LWTNNpLT = -99.0;
   LWTNNpTL = -99.0;
   LWTNNpTT = -99.0;
   LLNLOWeight = -99.0;
   LTNLOWeight = -99.0;
   TLNLOWeight = -99.0;
   TTNLOWeight = -99.0;
   Lep1WeightZ = 1.0;
   Lep2WeightZ = 1.0;
   Lep3WeightZ = 1.0;
   Lep1WeightW = 1.0;
   Lep2WeightW = 1.0;
   Lep3WeightW = 1.0;
   Pt_W = 0.0;
   Pt_Z = 0.0;
   Pt_WZ = 0.0;
   SumJetPt = 0.0;
   CosThetaV = -99.0;
   CosThetaLepW = -99.0;
   CosThetaLepZ = -99.0;
   DY_WZ = -99.0;
   DY_3Z = -99.0;
   DY_3N = -99.0;
   Truth_Pt_WZ = -99.0;
   DeltaPhiLepWLepZ = -99.0;
   DeltaPhiLepWLepZWZFrame = -99.0;
   DeltaPhiZBosonLepW = -99.0;
   R21 = -99.0;
   WLepPt = -99.0;
   ZLeadingLepPt = -99.0;
   ZSubleadingLepPt = -99.0;
   WLepEta = -99.0;
   ZLeadingLepEta = -99.0;
   ZSubleadingLepEta = -99.0;
   WLepPhi = -99.0;
   ZLeadingLepPhi = -99.0;
   ZSubleadingLepPhi = -99.0;
   WLepPz  = -99.0;
   NeutrinoPz = -99.0;
   ZLep1Pz = -99.0;
   ZLep2Pz = -99.0;
   WDecayStatus = -1.0;
   ZDecayStatus = -1.0;

   Lep1MediumIDWeight = 1.0;
   Lep2MediumIDWeight = 1.0;
   Lep3MediumIDWeight = 1.0;
   Lep1TightIDWeight = 1.0;
   Lep2TightIDWeight = 1.0;
   Lep3TightIDWeight = 1.0;
   Lep1MediumIsoWeight = 1.0;
   Lep2MediumIsoWeight = 1.0;
   Lep3MediumIsoWeight = 1.0;
   Lep1TightIsoWeight = 1.0;
   Lep2TightIsoWeight = 1.0;
   Lep3TightIsoWeight = 1.0;

   WLepton.ResetEvent();
   WNeutrino.ResetEvent();
   ZLepton1.ResetEvent();
   ZLepton2.ResetEvent();

   Lepton1.ResetEvent();
   Lepton2.ResetEvent();
   Lepton3.ResetEvent();

   TruthWLepton.ResetEvent();
   TruthWNeutrino.ResetEvent();
   TruthZLepton1.ResetEvent();
   TruthZLepton2.ResetEvent();

   TruthLepton1.ResetEvent();
   TruthLepton2.ResetEvent();
   TruthLepton3.ResetEvent();

   CutLepton1.ResetEvent();
   CutLepton2.ResetEvent();
   CutLepton3.ResetEvent();

   WLep.ResetEvent();
   ZLeadingLep.ResetEvent();
   ZSubleadingLep.ResetEvent();

   m_Channel = -1;

   passZZCR = 0;
   passTopCR = 0;
   passZFakeElCR = 0;
   passZFakeElCR_UpSys = 0;
   passZFakeElCR_DownSys = 0;
   passZFakeMuCR = 0;
   passTopElCR = 0;
   passTopMuCR = 0;
   passWZInclusive = 0;
   passHardWZInclusive = 0;
   passWZInclusiveLoose = 0;
   passHardWZInclusiveLoose = 0;
   passWZqqSR = 0;
   passWZqqCR = 0;
   passWZVBSSR = 0;
   passWZVBSCR = 0;
   passWZInclusiveNoMET = 0;
   passTopEnrichCR = 0;
   passZjetEnrichCR = 0;
   passTTT = 0;
   passTTL = 0;
   passTLT = 0;
   passLTT = 0;
   passTLL = 0;
   passLTL = 0;
   passLLT = 0;
   passZCondition = 0;
   passWCondition = 0;
   passSignalRegion = 0;
   pass100SignalRegion = 0;
   passHighPtWZCR = 0;
   passLowPtZCR = 0;

   passTruthMatch1 = 0;
   passTruthMatch2 = 0;
   passTruthMatch3 = 0;
   passZCondition1 = 0;
   passZCondition2 = 0;
   passZCondition3 = 0;
   passWCondition1 = 0;
   passWCondition2 = 0;
   passWCondition3 = 0;
   passMediumID1 = 0;
   passMediumID2 = 0;
   passMediumID3 = 0;
   passTightID1 = 0;
   passTightID2 = 0;
   passTightID3 = 0;
   passIPID1 = 0;
   passIPID2 = 0;
   passIPID3 = 0;

   passDeltaR = 0;

   isTauEvent = 0;

   passThreeBaseline = 0;

   //SystematicName = "";

   isThreeSameCharge = false;
}

void Lepton::ResetEvent()
{
   Flavor = "";
   pdgID = 0;
   Pt = 0.0;
   Eta = 0.0;
   Phi = 0.0;
   E = 0.0;
   Charge = -99;
   d0Sig = -99.0;

   Level = 0;
   ZLevel = 0;
   WLevel = 0;

   mediumID = 0;
   tightID = 0;
   FCLooseIso = 0;
   FCTightIso = 0;
   FCHighPtIso = 0;
   HighPtCaloOnlyIso = 0;
   Loose_VarRadIso = 0;
   Tight_VarRadIso = 0;
   PflowLooseIso = 0;
   PflowTightIso = 0;
   ZTightIso = 0;
   WTightIso = 0;
   ZTightIsoWeight = 1.0;
   WTightIsoWeight = 1.0;
   IPID = 0;
   mediumIDWeight = 1.0;
   tightIDWeight = 1.0;
   FCLooseIsoWeight = 1.0;
   FCTightIsoWeight = 1.0;
   FCHighPtIsoWeight = 1.0;
   HighPtCaloOnly_MediumID_IsoWeight = 1.0;
   HighPtCaloOnly_TightID_IsoWeight = 1.0;
   Loose_VarRad_MediumID_IsoWeight = 1.0;
   Loose_VarRad_TightID_IsoWeight = 1.0;
   Tight_VarRad_MediumID_IsoWeight = 1.0;
   Tight_VarRad_TightID_IsoWeight = 1.0;
   PflowLooseIsoWeight = 1.0;
   PflowTightIsoWeight = 1.0;
   triggerMatched = 0;
   truthMatched = 0;
   recoWeight = 1.0;
   IPWeight = 1.0;
   isBaseline = 0;
   isAmbiguity = 0;

   P4.SetPtEtaPhiM(0,0,0,0);
}

void loopWZPolarization::InitialSys(int ifile)
{
 int isys = -1;
 map<TString, int>::iterator sysIter;
 for(sysIter = SysNameIndex.begin(); sysIter != SysNameIndex.end(); sysIter++){
   isys = sysIter->second;

   if(isThread){
     if(!OneFilePerJob){
       NEvents = TotalEntriesSys[ifile][isys] / TotalThread;

       InitialEntrySys[isys] = (iThread - 1) * NEvents + 1;
       NentriesSys[isys] = iThread * NEvents;
       if(iThread == TotalThread) NentriesSys[isys] = TotalEntriesSys[ifile][isys];
     }
     if(OneFilePerJob){
       InitialEntrySys[isys] = 1;
       NentriesSys[isys] = TotalEntriesSys[ifile][isys];
     }

   }
   else{
     InitialEntrySys[isys] = 1;
     NentriesSys[isys] = TotalEntriesSys[ifile][isys];
     iThread = 1;
   }

   if(isTest){
     NentriesSys[isys] = InitialEntrySys[isys] + 10;
     if(NentriesSys[isys] > TotalEntriesSys[ifile][isys]) NentriesSys[isys] = TotalEntriesSys[ifile][isys];
   }

 }
}

void loopWZPolarization::End(int RootNumber)
{
 cout<<"\r"<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<"  "<<flush;//yfu

 if(!isInputPreTree){
   if(!WZPolarizationTree->fChain[RootNumber][RunningSys])
    {
     cout<<"XXXXX**Runing: BIG ERROR!!! No File loaded!"<<endl;
     return;
    }
   WZPolarizationTree->CloseFile(RootNumber);
   delete WZPolarizationTree->fChain[RootNumber][RunningSys]->GetCurrentFile();
 }

 if(isInputPreTree){
   if(!PreWZPolarizationTree->fChain[RootNumber])
    {
     cout<<"XXXXX**Runing: BIG ERROR!!! No File loaded!"<<endl;
     return;
    }
   PreWZPolarizationTree->CloseFile(RootNumber);
   delete PreWZPolarizationTree->fChain[RootNumber]->GetCurrentFile();
 }


}

void loopWZPolarization::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(!isInputPreTree){
   if(EndFile == RootNames.size()) delete WZPolarizationTree;
 }

 if(isInputPreTree){
   if(EndFile == RootNames.size()) delete PreWZPolarizationTree;
 }

 if(JustGenerateTree){
   WZPolarizationTree->SaveFile();
 }

 //for multi-run the loop function
 if(isInputPreTree){
   delete WZPolarizationTree;
 }

}

loopWZPolarization::~loopWZPolarization()
{
}

