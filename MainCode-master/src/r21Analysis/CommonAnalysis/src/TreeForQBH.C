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

   SetBranch(i);
 }
}

void TreeForQBH::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));

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

