#define TreeForFwdReco_cxx
#include "Analysis/TreeForFwdReco.h"

using namespace std;

TreeForFwdReco::TreeForFwdReco()
{
 Init();
}

TreeForFwdReco::~TreeForFwdReco()
{

}

void TreeForFwdReco::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);
 }
}

void TreeForFwdReco::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

}

void TreeForFwdReco::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForFwdReco::SetBranch(int ifile)
{
//   fChain[ifile] = (TTree *)rootfile[ifile]->Get("SelectedEvents_nominal");
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("analysis");

   fChain[ifile]->SetBranchAddress("fwdel_e", &fwdel_e, &b_fwdel_e);
   fChain[ifile]->SetBranchAddress("fwdel_eta", &fwdel_eta, &b_fwdel_eta);
   fChain[ifile]->SetBranchAddress("fwdel_phi", &fwdel_phi, &b_fwdel_phi);
   fChain[ifile]->SetBranchAddress("fwdel_pt", &fwdel_pt, &b_fwdel_pt);
   fChain[ifile]->SetBranchAddress("fwdel_clpt", &fwdel_clpt, &b_fwdel_clpt);
   fChain[ifile]->SetBranchAddress("fwdel_PassPtCut", &fwdel_PassPtCut, &b_fwdel_PassPtCut);
   fChain[ifile]->SetBranchAddress("fwdel_truthMatched", &fwdel_truthMatched, &b_fwdel_truthMatched);
   fChain[ifile]->SetBranchAddress("fwdel_corrected_e", &fwdel_corrected_e, &b_fwdel_corrected_e);
   fChain[ifile]->SetBranchAddress("fwdel_corrected_eta", &fwdel_corrected_eta, &b_fwdel_corrected_eta);
   fChain[ifile]->SetBranchAddress("fwdel_corrected_phi", &fwdel_corrected_phi, &b_fwdel_corrected_phi);
   fChain[ifile]->SetBranchAddress("fwdel_corrected_pt", &fwdel_corrected_pt, &b_fwdel_corrected_pt);
   fChain[ifile]->SetBranchAddress("fwdel_corrected_clpt", &fwdel_corrected_clpt, &b_fwdel_corrected_clpt);
   fChain[ifile]->SetBranchAddress("fwdel_corrected_PassPtCut", &fwdel_corrected_PassPtCut, &b_fwdel_corrected_PassPtCut);
   fChain[ifile]->SetBranchAddress("fwdel_corrected_truthMatched", &fwdel_corrected_truthMatched, &b_fwdel_corrected_truthMatched);
   fChain[ifile]->SetBranchAddress("truthel_e", &truthel_e, &b_truthel_e);
   fChain[ifile]->SetBranchAddress("truthel_eta", &truthel_eta, &b_truthel_eta);
   fChain[ifile]->SetBranchAddress("truthel_phi", &truthel_phi, &b_truthel_phi);
   fChain[ifile]->SetBranchAddress("truthel_pt", &truthel_pt, &b_truthel_pt);
   fChain[ifile]->SetBranchAddress("truthel_et", &truthel_et, &b_truthel_et);
   fChain[ifile]->SetBranchAddress("truthel_deltaE", &truthel_deltaE, &b_truthel_deltaE);
   fChain[ifile]->SetBranchAddress("truthel_deltaPt", &truthel_deltaPt, &b_truthel_deltaPt);
   fChain[ifile]->SetBranchAddress("truthel_deltaEt", &truthel_deltaEt, &b_truthel_deltaEt);
   fChain[ifile]->SetBranchAddress("truthel_Region", &truthel_Region, &b_truthel_Region);
   fChain[ifile]->SetBranchAddress("truthel_truthMatched", &truthel_truthMatched, &b_truthel_truthMatched);
   fChain[ifile]->SetBranchAddress("truthel_truthMatchedAfterCut", &truthel_truthMatchedAfterCut, &b_truthel_truthMatchedAfterCut);
   fChain[ifile]->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain[ifile]->SetBranchAddress("AverageMu", &AverageMu, &b_AverageMu);
   fChain[ifile]->SetBranchAddress("EventRegion", &EventRegion, &b_EventRegion);

   TotalEntries[ifile] = fChain[ifile]->GetEntries();

}

void TreeForFwdReco::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);
}

