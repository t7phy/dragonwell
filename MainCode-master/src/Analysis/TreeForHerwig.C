#define TreeForHerwig_cxx
#include "Analysis/TreeForHerwig.h"

using namespace std;

TreeForHerwig::TreeForHerwig()
{
 Init();
}

TreeForHerwig::~TreeForHerwig()
{

}

void TreeForHerwig::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);
 }
}

void TreeForHerwig::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;
 
 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

}

void TreeForHerwig::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForHerwig::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("Tree");

   fChain[ifile]->SetBranchAddress("PartonID", PartonID, &b_PartonID);
   fChain[ifile]->SetBranchAddress("PartonFraction", PartonFraction, &b_PartonFraction);
   fChain[ifile]->SetBranchAddress("GammaPx", GammaPx, &b_GammaPx);
   fChain[ifile]->SetBranchAddress("GammaPy", GammaPy, &b_GammaPy);
   fChain[ifile]->SetBranchAddress("GammaPz", GammaPz, &b_GammaPz);
   fChain[ifile]->SetBranchAddress("GammaE", GammaE, &b_Gamma);
   fChain[ifile]->SetBranchAddress("GammaMother", GammaMother, &b_GammaMother);
   fChain[ifile]->SetBranchAddress("GammaNumber", &GammaNumber, &b_GammaNumber);
   fChain[ifile]->SetBranchAddress("LeptonPx", &LeptonPx, &b_LeptonPx);
   fChain[ifile]->SetBranchAddress("LeptonPy", &LeptonPy, &b_LeptonPy);
   fChain[ifile]->SetBranchAddress("LeptonPz", &LeptonPz, &b_LeptonPz);
   fChain[ifile]->SetBranchAddress("LeptonE", &LeptonE, &b_LeptonE);
   fChain[ifile]->SetBranchAddress("AntiLeptonPx", &AntiLeptonPx, &b_AntiLeptonPx);
   fChain[ifile]->SetBranchAddress("AntiLeptonPy", &AntiLeptonPy, &b_AntiLeptonPy);
   fChain[ifile]->SetBranchAddress("AntiLeptonPz", &AntiLeptonPz, &b_AntiLeptonPz);
   fChain[ifile]->SetBranchAddress("AntiLeptonE", &AntiLeptonE, &b_AntiLeptonE);
   fChain[ifile]->SetBranchAddress("ZPx", &ZPx, &b_ZPx);
   fChain[ifile]->SetBranchAddress("ZPy", &ZPy, &b_ZPy);
   fChain[ifile]->SetBranchAddress("ZPz", &ZPz, &b_ZPz);
   fChain[ifile]->SetBranchAddress("ZE", &ZE, &b_ZE);
   fChain[ifile]->SetBranchAddress("Weight", &Weight, &b_Weight);

   TotalEntries[ifile] = fChain[ifile]->GetEntries();

}

void TreeForHerwig::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);

}

