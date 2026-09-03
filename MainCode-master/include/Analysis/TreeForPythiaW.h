//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 12 13:54:03 2020 by ROOT version 6.14/04
// from TTree Zeetree/Zeetree
// found on file: Zeetree.root
//////////////////////////////////////////////////////////

#ifndef TreeForPythiaW_h
#define TreeForPythiaW_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class TreeForPythiaW
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
   Double_t        MuonPx;
   Double_t        MuonPy;
   Double_t        MuonPz;
   Double_t        MuonE;
   Double_t        MuonCharge;
   Double_t        NeutrinoPx;
   Double_t        NeutrinoPy;
   Double_t        NeutrinoPz;
   Double_t        NeutrinoE;
   Double_t        WbosonPx;
   Double_t        WbosonPy;
   Double_t        WbosonPz;
   Double_t        WbosonE;
   Int_t           QuarkFlavour[2];
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
   TBranch        *b_MuonPx;   //!
   TBranch        *b_MuonPy;   //!
   TBranch        *b_MuonPz;   //!
   TBranch        *b_MuonE;   //!
   TBranch        *b_MuonCharge;   //!
   TBranch        *b_NeutrinoPx;   //!
   TBranch        *b_NeutrinoPy;   //!
   TBranch        *b_NeutrinoPz;   //!
   TBranch        *b_NeutrinoE;   //!
   TBranch        *b_WbosonPx;   //!
   TBranch        *b_WbosonPy;   //!
   TBranch        *b_WbosonPz;   //!
   TBranch        *b_WbosonE;   //!
   TBranch        *b_QuarkFlavour;   //!
   TBranch        *b_QuarkPx;   //!
   TBranch        *b_QuarkPy;   //!
   TBranch        *b_QuarkPz;   //!
   TBranch        *b_QuarkE;   //!

   TreeForPythiaW();
   virtual ~TreeForPythiaW();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void Init();
};

#endif

#ifdef TreeForPythiaW_cxx
void TreeForPythiaW::Init()
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
