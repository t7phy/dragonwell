//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Sep 18 19:26:05 2020 by ROOT version 6.14/04
// from TTree myTree/myTree
// found on file: /lustre/AtlUser/yfu/Repository/WZPolarization/run/CellInformation/myfile.root
//////////////////////////////////////////////////////////

#ifndef TreeForCellInfo_h
#define TreeForCellInfo_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "LinkDef.h"

using namespace std;

class TreeForCellInfo
{
 public :

   TFile *rootfile[1000];
   TTree *fChain[1000];
   long TotalEntries[1000];

   vector<TString> RootNames;

   vector<int> RootTypes;
   vector<double> CrossSections;
   vector<double> SumOfWeights;
   int nchannel;
   double CrossSection;
   double SumOfWeight;

   int FirstFile, EndFile;
   bool OneFilePerJob = false;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        mu;
   Double_t        nTC;
   Double_t        nEGPart;
   vector<float>   *reco_eta;
   vector<float>   *reco_phi;
   vector<float>   *reco_e;
   vector<float>   *reco_pt;
   vector<float>   *reco_pdgID;
   vector<float>   *tc_eta;
   vector<float>   *tc_phi;
   vector<float>   *tc_e;
   vector<float>   *tc_pt;
   vector<int>     *tc_recoIndex;
   vector<float>   *tc_size;
   vector<float>   *tc_energyBE0;
   vector<float>   *tc_energyBE1;
   vector<float>   *tc_energyBE2;
   vector<float>   *tc_energyBE3;
   vector<float>   *tc_etaBE0;
   vector<float>   *tc_etaBE1;
   vector<float>   *tc_etaBE2;
   vector<float>   *tc_etaBE3;
   vector<float>   *tc_phiBE0;
   vector<float>   *tc_phiBE1;
   vector<float>   *tc_phiBE2;
   vector<float>   *tc_phiBE3;
   vector<float>   *tc_centerX;
   vector<float>   *tc_centerY;
   vector<float>   *tc_centerZ;
   vector<float>   *tc_fracEM;
   vector<float>   *tc_fracMax;
   vector<int>     *tc_inBarrel;
   vector<int>     *tc_inEndcap;
   vector<vector<float> > *tc_cell_eta;
   vector<vector<float> > *tc_cell_phi;
   vector<vector<float> > *tc_cell_energy;
   vector<vector<int> > *tc_cell_layer;
   vector<vector<float> > *tc_cell_deta;
   vector<vector<float> > *tc_cell_dphi;
   vector<vector<float> > *tc_cell_x;
   vector<vector<float> > *tc_cell_y;
   vector<vector<float> > *tc_cell_z;
   vector<vector<float> > *tc_cell_dx;
   vector<vector<float> > *tc_cell_dy;
   vector<vector<float> > *tc_cell_dz;
   vector<vector<double> > *tc_cell_eta_min;
   vector<vector<double> > *tc_cell_eta_max;
   vector<vector<double> > *tc_cell_phi_min;
   vector<vector<double> > *tc_cell_phi_max;
   vector<float>   *truth_eta;
   vector<float>   *truth_phi;
   vector<float>   *truth_pt;
   vector<float>   *truth_e;
   vector<float>   *truth_matched;

   // List of branches
   TBranch        *b_mu;   //!
   TBranch        *b_nTC;   //!
   TBranch        *b_nEGPart;   //!
   TBranch        *b_reco_eta;   //!
   TBranch        *b_reco_phi;   //!
   TBranch        *b_reco_e;   //!
   TBranch        *b_reco_pt;   //!
   TBranch        *b_reco_pdgID;   //!
   TBranch        *b_tc_eta;   //!
   TBranch        *b_tc_phi;   //!
   TBranch        *b_tc_e;   //!
   TBranch        *b_tc_pt;   //!
   TBranch        *b_tc_recoIndex;   //!
   TBranch        *b_tc_size;   //!
   TBranch        *b_tc_energyBE0;   //!
   TBranch        *b_tc_energyBE1;   //!
   TBranch        *b_tc_energyBE2;   //!
   TBranch        *b_tc_energyBE3;   //!
   TBranch        *b_tc_etaBE0;   //!
   TBranch        *b_tc_etaBE1;   //!
   TBranch        *b_tc_etaBE2;   //!
   TBranch        *b_tc_etaBE3;   //!
   TBranch        *b_tc_phiBE0;   //!
   TBranch        *b_tc_phiBE1;   //!
   TBranch        *b_tc_phiBE2;   //!
   TBranch        *b_tc_phiBE3;   //!
   TBranch        *b_tc_centerX;   //!
   TBranch        *b_tc_centerY;   //!
   TBranch        *b_tc_centerZ;   //!
   TBranch        *b_tc_fracEM;   //!
   TBranch        *b_tc_fracMax;   //!
   TBranch        *b_tc_inBarrel;   //!
   TBranch        *b_tc_inEndcap;   //!
   TBranch        *b_tc_cell_eta;   //!
   TBranch        *b_tc_cell_phi;   //!
   TBranch        *b_tc_cell_energy;   //!
   TBranch        *b_tc_cell_layer;   //!
   TBranch        *b_tc_cell_deta;   //!
   TBranch        *b_tc_cell_dphi;   //!
   TBranch        *b_tc_cell_x;   //!
   TBranch        *b_tc_cell_y;   //!
   TBranch        *b_tc_cell_z;   //!
   TBranch        *b_tc_cell_dx;   //!
   TBranch        *b_tc_cell_dy;   //!
   TBranch        *b_tc_cell_dz;   //!
   TBranch        *b_tc_cell_eta_min;   //!
   TBranch        *b_tc_cell_eta_max;   //!
   TBranch        *b_tc_cell_phi_min;   //!
   TBranch        *b_tc_cell_phi_max;   //!
   TBranch        *b_truth_eta;   //!
   TBranch        *b_truth_phi;   //!
   TBranch        *b_truth_pt;   //!
   TBranch        *b_truth_e;   //!
   TBranch        *b_truth_matched;   //!

   TreeForCellInfo();
   virtual ~TreeForCellInfo();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void Init();
};

#endif

#ifdef TreeForCellInfo_cxx
void TreeForCellInfo::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   reco_eta = 0;
   reco_phi = 0;
   reco_e = 0;
   reco_pt = 0;
   reco_pdgID = 0;
   tc_eta = 0;
   tc_phi = 0;
   tc_e = 0;
   tc_pt = 0;
   tc_recoIndex = 0;
   tc_size = 0;
   tc_energyBE0 = 0;
   tc_energyBE1 = 0;
   tc_energyBE2 = 0;
   tc_energyBE3 = 0;
   tc_etaBE0 = 0;
   tc_etaBE1 = 0;
   tc_etaBE2 = 0;
   tc_etaBE3 = 0;
   tc_phiBE0 = 0;
   tc_phiBE1 = 0;
   tc_phiBE2 = 0;
   tc_phiBE3 = 0;
   tc_centerX = 0;
   tc_centerY = 0;
   tc_centerZ = 0;
   tc_fracEM = 0;
   tc_fracMax = 0;
   tc_inBarrel = 0;
   tc_inEndcap = 0;
   tc_cell_eta = 0;
   tc_cell_phi = 0;
   tc_cell_energy = 0;
   tc_cell_layer = 0;
   tc_cell_deta = 0;
   tc_cell_dphi = 0;
   tc_cell_x = 0;
   tc_cell_y = 0;
   tc_cell_z = 0;
   tc_cell_dx = 0;
   tc_cell_dy = 0;
   tc_cell_dz = 0;
   tc_cell_eta_min = 0;
   tc_cell_eta_max = 0;
   tc_cell_phi_min = 0;
   tc_cell_phi_max = 0;
   truth_eta = 0;
   truth_phi = 0;
   truth_pt = 0;
   truth_e = 0;
   truth_matched = 0;

}

#endif
