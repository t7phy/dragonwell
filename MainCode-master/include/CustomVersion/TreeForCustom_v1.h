//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 12 13:54:03 2020 by ROOT version 6.14/04
// from TTree Zeetree/Zeetree
// found on file: Zeetree.root
//////////////////////////////////////////////////////////

#ifndef TreeForCustom_v1_h
#define TreeForCustom_v1_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class TreeForCustom_v1
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
   Double_t        GammaPx[10];
   Double_t        GammaPy[10];
   Double_t        GammaPz[10];
   Double_t        GammaE[10];
   Int_t           GammaMother[10];
   Int_t           GammaNumber;
   Double_t        ElectronPx;
   Double_t        ElectronPy;
   Double_t        ElectronPz;
   Double_t        ElectronE;
   Double_t        PositronPx;
   Double_t        PositronPy;
   Double_t        PositronPz;
   Double_t        PositronE;
   Double_t        ZPx;
   Double_t        ZPy;
   Double_t        ZPz;
   Double_t        ZE;
   Int_t           quark_flavour[2];
   Double_t        QuarkPx[2];
   Double_t        QuarkPy[2];
   Double_t        QuarkPz[2];
   Double_t        QuarkE[2];

   // List of branches
   TBranch        *b_GammaPx;   //!
   TBranch        *b_GammaPy;   //!
   TBranch        *b_GammaPz;   //!
   TBranch        *b_Gamma;   //!
   TBranch        *b_GammaMother;   //!
   TBranch        *b_GammaNumber;   //!
   TBranch        *b_ElectronPx;   //!
   TBranch        *b_ElectronPy;   //!
   TBranch        *b_ElectronPz;   //!
   TBranch        *b_ElectronE;   //!
   TBranch        *b_PositronPx;   //!
   TBranch        *b_PositronPy;   //!
   TBranch        *b_PositronPz;   //!
   TBranch        *b_PositronE;   //!
   TBranch        *b_ZPx;   //!
   TBranch        *b_ZPy;   //!
   TBranch        *b_ZPz;   //!
   TBranch        *b_ZE;   //!
   TBranch        *b_quark_flavour;   //!
   TBranch        *b_QuarkPx;   //!
   TBranch        *b_QuarkPy;   //!
   TBranch        *b_QuarkPz;   //!
   TBranch        *b_QuarkE;   //!

   TreeForCustom_v1();
   virtual ~TreeForCustom_v1();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void Init();
};

#endif

#ifdef TreeForCustom_v1_cxx
void TreeForCustom_v1::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
}

#endif
