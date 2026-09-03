#define TreeForResBosHighMassZ_cxx
#include "Analysis/TreeForResBosHighMassZ.h"

using namespace std;

TreeForResBosHighMassZ::TreeForResBosHighMassZ()
{
 Init();
}

TreeForResBosHighMassZ::~TreeForResBosHighMassZ()
{

}

void TreeForResBosHighMassZ::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);
 }
}

void TreeForResBosHighMassZ::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

}

void TreeForResBosHighMassZ::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForResBosHighMassZ::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("h10");

   // Set branch addresses and branch pointers
   fChain[ifile]->SetBranchAddress("Px_d1", &Px_d1, &b_Px_d1);
   fChain[ifile]->SetBranchAddress("Py_d1", &Py_d1, &b_Py_d1);
   fChain[ifile]->SetBranchAddress("Pz_d1", &Pz_d1, &b_Pz_d1);
   fChain[ifile]->SetBranchAddress("E_d1", &E_d1, &b_E_d1);
   fChain[ifile]->SetBranchAddress("Px_d2", &Px_d2, &b_Px_d2);
   fChain[ifile]->SetBranchAddress("Py_d2", &Py_d2, &b_Py_d2);
   fChain[ifile]->SetBranchAddress("Pz_d2", &Pz_d2, &b_Pz_d2);
   fChain[ifile]->SetBranchAddress("E_d2", &E_d2, &b_E_d2);
   fChain[ifile]->SetBranchAddress("Px_V", &Px_V, &b_Px_V);
   fChain[ifile]->SetBranchAddress("Py_V", &Py_V, &b_Py_V);
   fChain[ifile]->SetBranchAddress("Pz_V", &Pz_V, &b_Pz_V);
   fChain[ifile]->SetBranchAddress("E_V", &E_V, &b_E_V);
   fChain[ifile]->SetBranchAddress("costhe_h", &costhe_h, &b_costhe_h);
   fChain[ifile]->SetBranchAddress("costhe_q", &costhe_q, &b_costhe_q);
   fChain[ifile]->SetBranchAddress("Type", &Type, &b_Type);
//   fChain[ifile]->SetBranchAddress("WT00", &WT00, &b_WT00);
   if(!isReweight) fChain[ifile]->SetBranchAddress("WT00",&Weight);
   if(isReweight) fChain[ifile]->SetBranchAddress("WT01",&Weight);

   TotalEntries[ifile] = fChain[ifile]->GetEntries();

}

void TreeForResBosHighMassZ::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);

}
