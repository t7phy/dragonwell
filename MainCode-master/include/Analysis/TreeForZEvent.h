#ifndef TreeForZEvent_h
#define TreeForZEvent_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

using namespace std;

class TreeForZEvent
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
   Double_t        Lep1Px;
   Double_t        Lep1Py;
   Double_t        Lep1Pz;
   Double_t        Lep1E;
   Double_t        Lep2Px;
   Double_t        Lep2Py;
   Double_t        Lep2Pz;
   Double_t        Lep2E;
   Double_t        ZPx;
   Double_t        ZPy;
   Double_t        ZPz;
   Double_t        ZE;
   Double_t        Weight;

   // List of branches
   TBranch        *b_Lep1Px;   //!
   TBranch        *b_Lep1Py;   //!
   TBranch        *b_Lep1Pz;   //!
   TBranch        *b_Lep1E;   //!
   TBranch        *b_Lep2Px;   //!
   TBranch        *b_Lep2Py;   //!
   TBranch        *b_Lep2Pz;   //!
   TBranch        *b_Lep2E;   //!
   TBranch        *b_ZPx;   //!
   TBranch        *b_ZPy;   //!
   TBranch        *b_ZPz;   //!
   TBranch        *b_ZE;   //!
   TBranch        *b_Weight;   //!

   TreeForZEvent();
   virtual ~TreeForZEvent();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void Init();
};

#endif

#ifdef TreeForZEvent_cxx

void TreeForZEvent::Init()
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
