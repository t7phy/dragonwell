#include "Analysis/TreeForResBos.h"

using namespace std;

TreeForResBos::TreeForResBos()
{

}

TreeForResBos::~TreeForResBos()
{

}

void TreeForResBos::Reweight()
{
 isReweight = true;
}

void TreeForResBos::TurnOnFSR()
{
 isFSR = true;
}

void TreeForResBos::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);

   nchannel = GetRootType(RootNames.at(i));
   RootTypes.push_back(nchannel);
 }
}

void TreeForResBos::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

 RootTypes.clear();

 nchannel = GetRootType(RootNames.at(ifile));
 RootTypes.push_back(nchannel);
}

TString TreeForResBos::GetRootType(TString RootName)
{
 TString nchannel;

 if(RootName.Contains("wp")) nchannel = "wp";
 if(RootName.Contains("wm")) nchannel = "wm";
 if(RootName.Contains("zu")) nchannel = "zu";
 if(RootName.Contains("zd")) nchannel = "zd";

 return nchannel;
}

void TreeForResBos::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForResBos::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("h10");

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

   if(isFSR){
     fChain[ifile]->SetBranchAddress("Px_g1",&Photon1Px);
     fChain[ifile]->SetBranchAddress("Py_g1",&Photon1Py);
     fChain[ifile]->SetBranchAddress("Pz_g1",&Photon1Pz);
     fChain[ifile]->SetBranchAddress("E_g1",&Photon1E);
   
     fChain[ifile]->SetBranchAddress("Px_g2",&Photon2Px);
     fChain[ifile]->SetBranchAddress("Py_g2",&Photon2Py);
     fChain[ifile]->SetBranchAddress("Pz_g2",&Photon2Pz);
     fChain[ifile]->SetBranchAddress("E_g2",&Photon2E);
   }

   if(isDilution){
     fChain[ifile]->SetBranchAddress("costhe_h",&costhe_h);
     fChain[ifile]->SetBranchAddress("costhe_q",&costhe_q);
     fChain[ifile]->SetBranchAddress("Type",&Type);
   }

   TotalEntries[ifile] = fChain[ifile]->GetEntries();
}

void TreeForResBos::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);
// cout<<tboson_pt<<endl;

}
