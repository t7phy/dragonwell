#define TreeForPythia_cxx
#include "Analysis/TreeForPythia.h"

using namespace std;

TreeForPythia::TreeForPythia()
{
 Init();
}

TreeForPythia::~TreeForPythia()
{

}

void TreeForPythia::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);
 }
}

void TreeForPythia::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

}

void TreeForPythia::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForPythia::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("h10");

   fChain[ifile]->SetBranchAddress("GammaPx", GammaPx, &b_GammaPx);
   fChain[ifile]->SetBranchAddress("GammaPy", GammaPy, &b_GammaPy);
   fChain[ifile]->SetBranchAddress("GammaPz", GammaPz, &b_GammaPz);
   fChain[ifile]->SetBranchAddress("GammaE", GammaE, &b_Gamma);
   fChain[ifile]->SetBranchAddress("GammaMother", GammaMother, &b_GammaMother);
   fChain[ifile]->SetBranchAddress("GammaNumber", &GammaNumber, &b_GammaNumber);
   fChain[ifile]->SetBranchAddress("ElectronPx", &ElectronPx, &b_ElectronPx);
   fChain[ifile]->SetBranchAddress("ElectronPy", &ElectronPy, &b_ElectronPy);
   fChain[ifile]->SetBranchAddress("ElectronPz", &ElectronPz, &b_ElectronPz);
   fChain[ifile]->SetBranchAddress("ElectronE", &ElectronE, &b_ElectronE);
   fChain[ifile]->SetBranchAddress("PositronPx", &PositronPx, &b_PositronPx);
   fChain[ifile]->SetBranchAddress("PositronPy", &PositronPy, &b_PositronPy);
   fChain[ifile]->SetBranchAddress("PositronPz", &PositronPz, &b_PositronPz);
   fChain[ifile]->SetBranchAddress("PositronE", &PositronE, &b_PositronE);
   fChain[ifile]->SetBranchAddress("ZPx", &ZPx, &b_ZPx);
   fChain[ifile]->SetBranchAddress("ZPy", &ZPy, &b_ZPy);
   fChain[ifile]->SetBranchAddress("ZPz", &ZPz, &b_ZPz);
   fChain[ifile]->SetBranchAddress("ZE", &ZE, &b_ZE);
   fChain[ifile]->SetBranchAddress("quark_flavour", quark_flavour, &b_quark_flavour);
   fChain[ifile]->SetBranchAddress("QuarkPx", QuarkPx, &b_QuarkPx);
   fChain[ifile]->SetBranchAddress("QuarkPy", QuarkPy, &b_QuarkPy);
   fChain[ifile]->SetBranchAddress("QuarkPz", QuarkPz, &b_QuarkPz);
   fChain[ifile]->SetBranchAddress("QuarkE", QuarkE, &b_QuarkE);

   TotalEntries[ifile] = fChain[ifile]->GetEntries();

}

void TreeForPythia::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);
}
