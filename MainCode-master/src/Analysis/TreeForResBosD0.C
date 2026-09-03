#define TreeForResBosD0_cxx
#include "Analysis/TreeForResBosD0.h"

using namespace std;

TreeForResBosD0::TreeForResBosD0()
{
 Init();
}

TreeForResBosD0::~TreeForResBosD0()
{

}

void TreeForResBosD0::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);
 }
}

void TreeForResBosD0::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

}

void TreeForResBosD0::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForResBosD0::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("h10");

   // Set branch addresses and branch pointers
   fChain[ifile]->SetBranchAddress("Px_d2",&ElectronPx);
   fChain[ifile]->SetBranchAddress("Py_d2",&ElectronPy);
   fChain[ifile]->SetBranchAddress("Pz_d2",&ElectronPz);
   fChain[ifile]->SetBranchAddress("E_d2",&ElectronE);

   fChain[ifile]->SetBranchAddress("Px_d1",&PositronPx);
   fChain[ifile]->SetBranchAddress("Py_d1",&PositronPy);
   fChain[ifile]->SetBranchAddress("Pz_d1",&PositronPz);
   fChain[ifile]->SetBranchAddress("E_d1",&PositronE);

   fChain[ifile]->SetBranchAddress("Px_V",&ZPx);
   fChain[ifile]->SetBranchAddress("Py_V",&ZPy);
   fChain[ifile]->SetBranchAddress("Pz_V",&ZPz);
   fChain[ifile]->SetBranchAddress("E_V",&ZE);

   if(!isReweight) fChain[ifile]->SetBranchAddress("WT00",&Weight);
   if(isReweight) fChain[ifile]->SetBranchAddress("WT01",&Weight);

   if(isDilution){
     fChain[ifile]->SetBranchAddress("costhe_h",&costhe_h);
     fChain[ifile]->SetBranchAddress("costhe_q",&costhe_q);
     fChain[ifile]->SetBranchAddress("Type",&Type);
   }

   TotalEntries[ifile] = fChain[ifile]->GetEntries();

}

void TreeForResBosD0::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);

}
