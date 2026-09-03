//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 12 14:40:34 2020 by ROOT version 6.14/04
// from TTree Tree/Tree
// found on file: Zee_20M_FSRon_NNPDF31nnloas0118.root
//////////////////////////////////////////////////////////

#ifndef TreeForHerwig_h
#define TreeForHerwig_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

using namespace std;

class TreeForHerwig
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
   Int_t           PartonID[2];
   Double_t        PartonFraction[2];
   Double_t        GammaPx[10];
   Double_t        GammaPy[10];
   Double_t        GammaPz[10];
   Double_t        GammaE[10];
   Int_t           GammaMother[10];
   Int_t           GammaNumber;
   Double_t        LeptonPx;
   Double_t        LeptonPy;
   Double_t        LeptonPz;
   Double_t        LeptonE;
   Double_t        AntiLeptonPx;
   Double_t        AntiLeptonPy;
   Double_t        AntiLeptonPz;
   Double_t        AntiLeptonE;
   Double_t        ZPx;
   Double_t        ZPy;
   Double_t        ZPz;
   Double_t        ZE;
   Double_t        Weight;

   // List of branches
   TBranch        *b_PartonID;   //!
   TBranch        *b_PartonFraction;   //!
   TBranch        *b_GammaPx;   //!
   TBranch        *b_GammaPy;   //!
   TBranch        *b_GammaPz;   //!
   TBranch        *b_Gamma;   //!
   TBranch        *b_GammaMother;   //!
   TBranch        *b_GammaNumber;   //!
   TBranch        *b_LeptonPx;   //!
   TBranch        *b_LeptonPy;   //!
   TBranch        *b_LeptonPz;   //!
   TBranch        *b_LeptonE;   //!
   TBranch        *b_AntiLeptonPx;   //!
   TBranch        *b_AntiLeptonPy;   //!
   TBranch        *b_AntiLeptonPz;   //!
   TBranch        *b_AntiLeptonE;   //!
   TBranch        *b_ZPx;   //!
   TBranch        *b_ZPy;   //!
   TBranch        *b_ZPz;   //!
   TBranch        *b_ZE;   //!
   TBranch        *b_Weight;   //!

   TreeForHerwig();
   virtual ~TreeForHerwig();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void Init();
};

#endif

#ifdef TreeForHerwig_cxx

void TreeForHerwig::Init()
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
