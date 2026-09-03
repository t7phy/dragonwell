#ifndef TreeForResBosCMS_h
#define TreeForResBosCMS_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

using namespace std;

class TreeForResBosCMS
{
 public :

   TFile *rootfile[1000];
   TTree *fChain[1000];
   long TotalEntries[1000];

   bool isReweight = false;
   bool isFSR = false;
   bool isDilution = false;

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

   Float_t         ElectronPx;
   Float_t         ElectronPy;
   Float_t         ElectronPz;
   Float_t         ElectronE;
   Float_t         PositronPx;
   Float_t         PositronPy;
   Float_t         PositronPz;
   Float_t         PositronE;
   Float_t         ZPx;
   Float_t         ZPy;
   Float_t         ZPz;
   Float_t         ZE;
   Float_t         costhe_h;
   Float_t         costhe_q;
   Float_t         Type;
   Float_t         Weight;

   // List of branches
   TBranch        *b_Px_d1;   //!
   TBranch        *b_Py_d1;   //!
   TBranch        *b_Pz_d1;   //!
   TBranch        *b_E_d1;   //!
   TBranch        *b_Px_d2;   //!
   TBranch        *b_Py_d2;   //!
   TBranch        *b_Pz_d2;   //!
   TBranch        *b_E_d2;   //!
   TBranch        *b_Px_V;   //!
   TBranch        *b_Py_V;   //!
   TBranch        *b_Pz_V;   //!
   TBranch        *b_E_V;   //!
   TBranch        *b_costhe_h;   //!
   TBranch        *b_costhe_q;   //!
   TBranch        *b_Type;   //!
   TBranch        *b_WT00;   //!

   TreeForResBosCMS();
   virtual ~TreeForResBosCMS();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void Init();
   virtual void Reweight(){isReweight = true;};
   virtual void TurnOnFSR(){isFSR = true;};
   virtual void TurnOnDilution(){isDilution = true;}
};

#endif

#ifdef TreeForResBosCMS_cxx

void TreeForResBosCMS::Init()
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
