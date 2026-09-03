#define TreeForQBH_cxx
#include "QBH/TreeForQBH.h"

using namespace std;

void TreeForQBH::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
}

TreeForQBH::TreeForQBH()
{
 Init();
}

TreeForQBH::~TreeForQBH()
{

}

void TreeForQBH::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));

   TString MCTypeName = GetRootType(RootNames.at(i));
   RootTypes.push_back(MCTypeName);

   SetBranch(i);
 }
}

void TreeForQBH::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));

 TString MCTypeName = GetRootType(RootNames.at(ifile));

 RootTypes.clear();
 RootTypes.push_back(MCTypeName);

 SetBranch(0);
}

void TreeForQBH::CloseFile(int ifile)
{
 rootfile[ifile]->Close();
}

void TreeForQBH::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;
}

void TreeForQBH::LinkHist(HistsQBH* myhists)
{
 this->fHist = myhists;
 this->SystematicName = fHist->SystematicName;
}

TString TreeForQBH::GetRootType(TString RootName)
{
 TString MCTypeName = "";

 if(RootName.Contains("Run3_dijet")){
   MCTypeName = "dijet";
 }
 else if(RootName.Contains("Run3_MGH7EG_LO")){
   MCTypeName = "MGH7EG_LO";
 }
 else if(RootName.Contains("Run3_PhH7EG_NLO")){
   MCTypeName = "PhH7EG_NLO";
 }
 else if(RootName.Contains("Run3_QBHPy8EG_QBH")){
   MCTypeName = "QBHPy8EG_QBH";
 }
 else if(RootName.Contains("Run3_singletop")){
   MCTypeName = "singletop";
 }
 else if(RootName.Contains("Run3_ttbar")){
   MCTypeName = "ttbar";
 }
 else if(RootName.Contains("Run3_ttV")){
   MCTypeName = "ttV";
 }
 else if(RootName.Contains("Run3_Wenu")){
   MCTypeName = "Wenu";
 }
 else if(RootName.Contains("Run3_Wmnu")){
   MCTypeName = "Wmnu";
 }
 else if(RootName.Contains("Run3_Wtnu")){
   MCTypeName = "Wtnu";
 }
 else if(RootName.Contains("Run3_Zee")){
   MCTypeName = "Zee";
 }
 else if(RootName.Contains("Run3_Zmm")){
   MCTypeName = "Zmm";
 }
 else if(RootName.Contains("Run3_Ztt")){
   MCTypeName = "Ztt";
 }
 else if(RootName.Contains("Run3_diboson")){
   MCTypeName = "diboson";
 }
 else if(RootName.Contains("Run3_data")){
   MCTypeName = "data";
 }
 else{
   MCTypeName = "Unknown";
 }

 return MCTypeName;
}

void TreeForQBH::SetBranch(int ifile)
{
   SavedSystematicName = SystematicName;
   if(SystematicName.Contains("FakeBkg")) SavedSystematicName = "nominal";

   fChain[ifile] = (TTree *)rootfile[ifile]->Get(SavedSystematicName);

}

void TreeForQBH::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);
}

void TreeForQBH::GenerateFile(TString FileName)
{
 hf = new TFile(FileName, "RECREATE");
}

void TreeForQBH::DefineTree(int isys, TString TreeName)
{
 cout<<"Defining the tree "<<TreeName<<endl;

 GenerateTree[isys] = new TTree(TreeName, TreeName);
 GenerateTree[isys]->Branch("TotalWeight", &TotalWeight, "TotalWeight/F");
 GenerateTree[isys]->Branch("LeadingLepWeight", &LeadingLepWeight, "LeadingLepWeight/F");
 GenerateTree[isys]->Branch("SubleadingLepWeight", &SubleadingLepWeight, "SubleadingLepWeight/F");
 GenerateTree[isys]->Branch("passLeadingLepTight", &passLeadingLepTight, "passLeadingLepTight/I");
 GenerateTree[isys]->Branch("LepJetMass", &LepJetMass, "LepJetMass/F");

 GenerateTree[isys]->Branch("passInclusive", &passInclusive, "passInclusive/I");
 GenerateTree[isys]->Branch("passFakeCR", &passFakeCR, "passFakeCR/I");
 GenerateTree[isys]->Branch("passWCR", &passWCR, "passWCR/I");
 GenerateTree[isys]->Branch("passWVR", &passWVR, "passWVR/I");
 GenerateTree[isys]->Branch("passZCR", &passZCR, "passZCR/I");
 GenerateTree[isys]->Branch("passZVR", &passZVR, "passZVR/I");
 GenerateTree[isys]->Branch("passTCR", &passTCR, "passTCR/I");
 GenerateTree[isys]->Branch("passTVR", &passTVR, "passTVR/I");
 GenerateTree[isys]->Branch("passSR", &passSR, "passSR/I");
 GenerateTree[isys]->Branch("passSVR", &passSVR, "passSVR/I");

 if(isys == 0){
   Event_CutFlow = new TH1D("Event_CutFlow", "Event_CutFlow", 30, 0, 30);
   Event_CutFlow->SetDirectory(hf);
   Electron_CutFlow = new TH1D("Electron_CutFlow", "Electron_CutFlow", 20, 0, 20);
   Electron_CutFlow->SetDirectory(hf);
   Muon_CutFlow = new TH1D("Muon_CutFlow", "Muon_CutFlow", 20, 0, 20);
   Muon_CutFlow->SetDirectory(hf);

   Event_CutNameMap = new std::map<std::string, double>();
   Electron_CutNameMap = new std::map<std::string, double>();
   Muon_CutNameMap = new std::map<std::string, double>();

   Event_WeightedCutFlow = new TH1D("Event_WeightedCutFlow", "Event_WeightedCutFlow", 30, 0, 30);
   Event_WeightedCutFlow->SetDirectory(hf);
   Electron_WeightedCutFlow = new TH1D("Electron_WeightedCutFlow", "Electron_WeightedCutFlow", 20, 0, 20);
   Electron_WeightedCutFlow->SetDirectory(hf);
   Muon_WeightedCutFlow = new TH1D("Muon_WeightedCutFlow", "Muon_WeightedCutFlow", 20, 0, 20);
   Muon_WeightedCutFlow->SetDirectory(hf);

   Event_WeightedCutNameMap = new std::map<std::string, double>();
   Electron_WeightedCutNameMap = new std::map<std::string, double>();
   Muon_WeightedCutNameMap = new std::map<std::string, double>();

 }

}

void TreeForQBH::FillTree(int isys)
{
 GenerateTree[isys]->Fill();
}

void TreeForQBH::updateCutFlow(TH1D *inCutFlow, std::map<std::string, double> *inLabelMap, std::string cutName, double step, bool doUpdate){
  if(!doUpdate) return;
  double Xpos = -1;
  if(inLabelMap->count(cutName)){
    Xpos = (*inLabelMap)[cutName];
  }
  else{
    (*inLabelMap)[cutName] = inLabelMap->size() * 1.; //this will gives 1 when first call, strange ... doesn't happen with stand alone root run
    std::cout<<"registering new cut "<<cutName<<" at position "<<(*inLabelMap)[cutName]<<std::endl;
    inCutFlow->GetXaxis()->SetBinLabel(inLabelMap->size()+1, cutName.c_str());
    Xpos = (*inLabelMap)[cutName];
  }
  inCutFlow->Fill(Xpos,step);
}


void TreeForQBH::SaveFile()
{
 hf->cd();

 hf->Write();
 hf->Close();
}

