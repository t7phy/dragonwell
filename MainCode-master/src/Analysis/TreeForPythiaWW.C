#define TreeForPythiaWW_cxx
#include "Analysis/TreeForPythiaWW.h"

using namespace std;

TreeForPythiaWW::TreeForPythiaWW()
{
 Init();
}

TreeForPythiaWW::~TreeForPythiaWW()
{

}

void TreeForPythiaWW::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);
 }
}

void TreeForPythiaWW::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;
 
 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

}

void TreeForPythiaWW::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForPythiaWW::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("WW");

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

/*   fChain[ifile]->SetBranchAddress("AntiLeptonPx", &AntiLeptonPx, &b_AntiLeptonPx);
   fChain[ifile]->SetBranchAddress("AntiLeptonPy", &AntiLeptonPy, &b_AntiLeptonPy);
   fChain[ifile]->SetBranchAddress("AntiLeptonPz", &AntiLeptonPz, &b_AntiLeptonPz);
   fChain[ifile]->SetBranchAddress("AntiLeptonE", &AntiLeptonE, &b_AntiLeptonE);
   fChain[ifile]->SetBranchAddress("AntiLeptonID", &AntiLeptonID, &b_AntiLeptonID);
   fChain[ifile]->SetBranchAddress("LeptonPx", &LeptonPx, &b_LeptonPx);
   fChain[ifile]->SetBranchAddress("LeptonPy", &LeptonPy, &b_LeptonPy);
   fChain[ifile]->SetBranchAddress("LeptonPz", &LeptonPz, &b_LeptonPz);
   fChain[ifile]->SetBranchAddress("LeptonE", &LeptonE, &b_LeptonE);
   fChain[ifile]->SetBranchAddress("LeptonID", &LeptonID, &b_LeptonID);
   fChain[ifile]->SetBranchAddress("QuarkPx", &QuarkPx, &b_QuarkPx);
   fChain[ifile]->SetBranchAddress("QuarkPy", &QuarkPy, &b_QuarkPy);
   fChain[ifile]->SetBranchAddress("QuarkPz", &QuarkPz, &b_QuarkPz);
   fChain[ifile]->SetBranchAddress("QuarkE", &QuarkE, &b_QuarkE);
   fChain[ifile]->SetBranchAddress("QuarkID", &QuarkID, &b_QuarkID);
   fChain[ifile]->SetBranchAddress("AntiQuarkPx", &AntiQuarkPx, &b_AntiQuarkPx);
   fChain[ifile]->SetBranchAddress("AntiQuarkPy", &AntiQuarkPy, &b_AntiQuarkPy);
   fChain[ifile]->SetBranchAddress("AntiQuarkPz", &AntiQuarkPz, &b_AntiQuarkPz);
   fChain[ifile]->SetBranchAddress("AntiQuarkE", &AntiQuarkE, &b_AntiQuarkE);
   fChain[ifile]->SetBranchAddress("AntiQuarkID", &AntiQuarkID, &b_AntiQuarkID);
*/
   TotalEntries[ifile] = fChain[ifile]->GetEntries();

}

void TreeForPythiaWW::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);

}

