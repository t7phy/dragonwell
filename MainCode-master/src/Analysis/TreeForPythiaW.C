#define TreeForPythiaW_cxx
#include "Analysis/TreeForPythiaW.h"

using namespace std;

TreeForPythiaW::TreeForPythiaW()
{
 Init();
}

TreeForPythiaW::~TreeForPythiaW()
{

}

void TreeForPythiaW::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);
 }
}

void TreeForPythiaW::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

}

void TreeForPythiaW::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForPythiaW::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("Tree");

   fChain[ifile]->SetBranchAddress("GammaPx", GammaPx, &b_GammaPx);
   fChain[ifile]->SetBranchAddress("GammaPy", GammaPy, &b_GammaPy);
   fChain[ifile]->SetBranchAddress("GammaPz", GammaPz, &b_GammaPz);
   fChain[ifile]->SetBranchAddress("GammaE", GammaE, &b_Gamma);
   fChain[ifile]->SetBranchAddress("GammaMother", GammaMother, &b_GammaMother);
   fChain[ifile]->SetBranchAddress("GammaNumber", &GammaNumber, &b_GammaNumber);
   fChain[ifile]->SetBranchAddress("MuonPx", &MuonPx, &b_MuonPx);
   fChain[ifile]->SetBranchAddress("MuonPy", &MuonPy, &b_MuonPy);
   fChain[ifile]->SetBranchAddress("MuonPz", &MuonPz, &b_MuonPz);
   fChain[ifile]->SetBranchAddress("MuonE", &MuonE, &b_MuonE);
   fChain[ifile]->SetBranchAddress("MuonCharge", &MuonCharge, &b_MuonCharge);
   fChain[ifile]->SetBranchAddress("NeutrinoPx", &NeutrinoPx, &b_NeutrinoPx);
   fChain[ifile]->SetBranchAddress("NeutrinoPy", &NeutrinoPy, &b_NeutrinoPy);
   fChain[ifile]->SetBranchAddress("NeutrinoPz", &NeutrinoPz, &b_NeutrinoPz);
   fChain[ifile]->SetBranchAddress("NeutrinoE", &NeutrinoE, &b_NeutrinoE);
   fChain[ifile]->SetBranchAddress("WbosonPx", &WbosonPx, &b_WbosonPx);
   fChain[ifile]->SetBranchAddress("WbosonPy", &WbosonPy, &b_WbosonPy);
   fChain[ifile]->SetBranchAddress("WbosonPz", &WbosonPz, &b_WbosonPz);
   fChain[ifile]->SetBranchAddress("WbosonE", &WbosonE, &b_WbosonE);
   fChain[ifile]->SetBranchAddress("QuarkFlavour", QuarkFlavour, &b_QuarkFlavour);
   fChain[ifile]->SetBranchAddress("QuarkPx", QuarkPx, &b_QuarkPx);
   fChain[ifile]->SetBranchAddress("QuarkPy", QuarkPy, &b_QuarkPy);
   fChain[ifile]->SetBranchAddress("QuarkPz", QuarkPz, &b_QuarkPz);
   fChain[ifile]->SetBranchAddress("QuarkE", QuarkE, &b_QuarkE);

   TotalEntries[ifile] = fChain[ifile]->GetEntries();

}

void TreeForPythiaW::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);
}
