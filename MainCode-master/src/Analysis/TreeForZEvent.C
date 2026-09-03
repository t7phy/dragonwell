#define TreeForZEvent_cxx
#include "Analysis/TreeForZEvent.h"

using namespace std;

TreeForZEvent::TreeForZEvent()
{
 Init();
}

TreeForZEvent::~TreeForZEvent()
{

}

void TreeForZEvent::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);
 }
}

void TreeForZEvent::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

}

void TreeForZEvent::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForZEvent::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("tree");

   // Set branch addresses and branch pointers
   fChain[ifile]->SetBranchAddress("Lep1Px", &Lep1Px, &b_Lep1Px);
   fChain[ifile]->SetBranchAddress("Lep1Py", &Lep1Py, &b_Lep1Py);
   fChain[ifile]->SetBranchAddress("Lep1Pz", &Lep1Pz, &b_Lep1Pz);
   fChain[ifile]->SetBranchAddress("Lep1E", &Lep1E, &b_Lep1E);
   fChain[ifile]->SetBranchAddress("Lep2Px", &Lep2Px, &b_Lep2Px);
   fChain[ifile]->SetBranchAddress("Lep2Py", &Lep2Py, &b_Lep2Py);
   fChain[ifile]->SetBranchAddress("Lep2Pz", &Lep2Pz, &b_Lep2Pz);
   fChain[ifile]->SetBranchAddress("Lep2E", &Lep2E, &b_Lep2E);
   fChain[ifile]->SetBranchAddress("ZPx", &ZPx, &b_ZPx);
   fChain[ifile]->SetBranchAddress("ZPy", &ZPy, &b_ZPy);
   fChain[ifile]->SetBranchAddress("ZPz", &ZPz, &b_ZPz);
   fChain[ifile]->SetBranchAddress("ZE", &ZE, &b_ZE);
   fChain[ifile]->SetBranchAddress("Weight", &Weight, &b_Weight);

   TotalEntries[ifile] = fChain[ifile]->GetEntries();

}

void TreeForZEvent::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);

}
