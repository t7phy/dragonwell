#define TreeForSherpaWW_cxx
#include "Analysis/TreeForSherpaWW.h"

using namespace std;

TreeForSherpaWW::TreeForSherpaWW()
{
 Init();
}

TreeForSherpaWW::~TreeForSherpaWW()
{

}

void TreeForSherpaWW::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);
 }
}

void TreeForSherpaWW::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

}

void TreeForSherpaWW::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForSherpaWW::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("WW");

   // Set branch addresses and branch pointers
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
   fChain[ifile]->SetBranchAddress("ElectronFlavor", &ElectronFlavor, &b_ElectronFlavor);
   fChain[ifile]->SetBranchAddress("eNeutrinoPx", &eNeutrinoPx, &b_eNeutrinoPx);
   fChain[ifile]->SetBranchAddress("eNeutrinoPy", &eNeutrinoPy, &b_eNeutrinoPy);
   fChain[ifile]->SetBranchAddress("eNeutrinoPz", &eNeutrinoPz, &b_eNeutrinoPz);
   fChain[ifile]->SetBranchAddress("eNeutrinoE", &eNeutrinoE, &b_eNeutrinoE);
   fChain[ifile]->SetBranchAddress("MuonPx", &MuonPx, &b_MuonPx);
   fChain[ifile]->SetBranchAddress("MuonPy", &MuonPy, &b_MuonPy);
   fChain[ifile]->SetBranchAddress("MuonPz", &MuonPz, &b_MuonPz);
   fChain[ifile]->SetBranchAddress("MuonE", &MuonE, &b_MuonE);
   fChain[ifile]->SetBranchAddress("MuonFlavor", &MuonFlavor, &b_MuonFlavor);
   fChain[ifile]->SetBranchAddress("mNeutrinoPx", &mNeutrinoPx, &b_mNeutrinoPx);
   fChain[ifile]->SetBranchAddress("mNeutrinoPy", &mNeutrinoPy, &b_mNeutrinoPy);
   fChain[ifile]->SetBranchAddress("mNeutrinoPz", &mNeutrinoPz, &b_mNeutrinoPz);
   fChain[ifile]->SetBranchAddress("mNeutrinoE", &mNeutrinoE, &b_mNeutrinoE);
   fChain[ifile]->SetBranchAddress("quark_flavour", quark_flavour, &b_quark_flavour);
   fChain[ifile]->SetBranchAddress("QuarkPx", QuarkPx, &b_QuarkPx);
   fChain[ifile]->SetBranchAddress("QuarkPy", QuarkPy, &b_QuarkPy);
   fChain[ifile]->SetBranchAddress("QuarkPz", QuarkPz, &b_QuarkPz);
   fChain[ifile]->SetBranchAddress("QuarkE", QuarkE, &b_QuarkE);
   fChain[ifile]->SetBranchAddress("Weights", &Weights, &b_Weights);

   metaTree[ifile] = (TTree *)rootfile[ifile]->Get("metaTree");
   metaTree[ifile]->SetBranchAddress("WeightNames", &WeightNames, &b_WeightNames);

   TotalEntries[ifile] = fChain[ifile]->GetEntries();

}

void TreeForSherpaWW::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);

}
