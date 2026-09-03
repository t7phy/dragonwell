#define TreeForCellInfo_cxx
#include "Analysis/TreeForCellInfo.h"

using namespace std;

TreeForCellInfo::TreeForCellInfo()
{
 Init();
}

TreeForCellInfo::~TreeForCellInfo()
{

}

void TreeForCellInfo::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);
 }
}

void TreeForCellInfo::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

}

void TreeForCellInfo::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForCellInfo::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("myTree");

   fChain[ifile]->SetBranchAddress("mu", &mu, &b_mu);
   fChain[ifile]->SetBranchAddress("nTC", &nTC, &b_nTC);
   fChain[ifile]->SetBranchAddress("nEGPart", &nEGPart, &b_nEGPart);
   fChain[ifile]->SetBranchAddress("reco_eta", &reco_eta, &b_reco_eta);
   fChain[ifile]->SetBranchAddress("reco_phi", &reco_phi, &b_reco_phi);
   fChain[ifile]->SetBranchAddress("reco_e", &reco_e, &b_reco_e);
   fChain[ifile]->SetBranchAddress("reco_pt", &reco_pt, &b_reco_pt);
   fChain[ifile]->SetBranchAddress("reco_pdgID", &reco_pdgID, &b_reco_pdgID);
   fChain[ifile]->SetBranchAddress("tc_eta", &tc_eta, &b_tc_eta);
   fChain[ifile]->SetBranchAddress("tc_phi", &tc_phi, &b_tc_phi);
   fChain[ifile]->SetBranchAddress("tc_e", &tc_e, &b_tc_e);
   fChain[ifile]->SetBranchAddress("tc_pt", &tc_pt, &b_tc_pt);
   fChain[ifile]->SetBranchAddress("tc_recoIndex", &tc_recoIndex, &b_tc_recoIndex);
   fChain[ifile]->SetBranchAddress("tc_size", &tc_size, &b_tc_size);
   fChain[ifile]->SetBranchAddress("tc_energyBE0", &tc_energyBE0, &b_tc_energyBE0);
   fChain[ifile]->SetBranchAddress("tc_energyBE1", &tc_energyBE1, &b_tc_energyBE1);
   fChain[ifile]->SetBranchAddress("tc_energyBE2", &tc_energyBE2, &b_tc_energyBE2);
   fChain[ifile]->SetBranchAddress("tc_energyBE3", &tc_energyBE3, &b_tc_energyBE3);
   fChain[ifile]->SetBranchAddress("tc_etaBE0", &tc_etaBE0, &b_tc_etaBE0);
   fChain[ifile]->SetBranchAddress("tc_etaBE1", &tc_etaBE1, &b_tc_etaBE1);
   fChain[ifile]->SetBranchAddress("tc_etaBE2", &tc_etaBE2, &b_tc_etaBE2);
   fChain[ifile]->SetBranchAddress("tc_etaBE3", &tc_etaBE3, &b_tc_etaBE3);
   fChain[ifile]->SetBranchAddress("tc_phiBE0", &tc_phiBE0, &b_tc_phiBE0);
   fChain[ifile]->SetBranchAddress("tc_phiBE1", &tc_phiBE1, &b_tc_phiBE1);
   fChain[ifile]->SetBranchAddress("tc_phiBE2", &tc_phiBE2, &b_tc_phiBE2);
   fChain[ifile]->SetBranchAddress("tc_phiBE3", &tc_phiBE3, &b_tc_phiBE3);
   fChain[ifile]->SetBranchAddress("tc_centerX", &tc_centerX, &b_tc_centerX);
   fChain[ifile]->SetBranchAddress("tc_centerY", &tc_centerY, &b_tc_centerY);
   fChain[ifile]->SetBranchAddress("tc_centerZ", &tc_centerZ, &b_tc_centerZ);
   fChain[ifile]->SetBranchAddress("tc_fracEM", &tc_fracEM, &b_tc_fracEM);
   fChain[ifile]->SetBranchAddress("tc_fracMax", &tc_fracMax, &b_tc_fracMax);
   fChain[ifile]->SetBranchAddress("tc_inBarrel", &tc_inBarrel, &b_tc_inBarrel);
   fChain[ifile]->SetBranchAddress("tc_inEndcap", &tc_inEndcap, &b_tc_inEndcap);
   fChain[ifile]->SetBranchAddress("tc_cell_eta", &tc_cell_eta, &b_tc_cell_eta);
   fChain[ifile]->SetBranchAddress("tc_cell_phi", &tc_cell_phi, &b_tc_cell_phi);
   fChain[ifile]->SetBranchAddress("tc_cell_energy", &tc_cell_energy, &b_tc_cell_energy);
   fChain[ifile]->SetBranchAddress("tc_cell_layer", &tc_cell_layer, &b_tc_cell_layer);
   fChain[ifile]->SetBranchAddress("tc_cell_deta", &tc_cell_deta, &b_tc_cell_deta);
   fChain[ifile]->SetBranchAddress("tc_cell_dphi", &tc_cell_dphi, &b_tc_cell_dphi);
   fChain[ifile]->SetBranchAddress("tc_cell_x", &tc_cell_x, &b_tc_cell_x);
   fChain[ifile]->SetBranchAddress("tc_cell_y", &tc_cell_y, &b_tc_cell_y);
   fChain[ifile]->SetBranchAddress("tc_cell_z", &tc_cell_z, &b_tc_cell_z);
   fChain[ifile]->SetBranchAddress("tc_cell_dx", &tc_cell_dx, &b_tc_cell_dx);
   fChain[ifile]->SetBranchAddress("tc_cell_dy", &tc_cell_dy, &b_tc_cell_dy);
   fChain[ifile]->SetBranchAddress("tc_cell_dz", &tc_cell_dz, &b_tc_cell_dz);
   fChain[ifile]->SetBranchAddress("tc_cell_eta_min", &tc_cell_eta_min, &b_tc_cell_eta_min);
   fChain[ifile]->SetBranchAddress("tc_cell_eta_max", &tc_cell_eta_max, &b_tc_cell_eta_max);
   fChain[ifile]->SetBranchAddress("tc_cell_phi_min", &tc_cell_phi_min, &b_tc_cell_phi_min);
   fChain[ifile]->SetBranchAddress("tc_cell_phi_max", &tc_cell_phi_max, &b_tc_cell_phi_max);
   fChain[ifile]->SetBranchAddress("truth_eta", &truth_eta, &b_truth_eta);
   fChain[ifile]->SetBranchAddress("truth_phi", &truth_phi, &b_truth_phi);
   fChain[ifile]->SetBranchAddress("truth_pt", &truth_pt, &b_truth_pt);
   fChain[ifile]->SetBranchAddress("truth_e", &truth_e, &b_truth_e);
   fChain[ifile]->SetBranchAddress("truth_matched", &truth_matched, &b_truth_matched);

   TotalEntries[ifile] = fChain[ifile]->GetEntries();

}

void TreeForCellInfo::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);

}
