#ifndef TreeForResBosHighMassZ_h
#define TreeForResBosHighMassZ_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

using namespace std;

class TreeForResBosHighMassZ
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
   Float_t         Px_d1;
   Float_t         Py_d1;
   Float_t         Pz_d1;
   Float_t         E_d1;
   Float_t         Px_d2;
   Float_t         Py_d2;
   Float_t         Pz_d2;
   Float_t         E_d2;
   Float_t         Px_V;
   Float_t         Py_V;
   Float_t         Pz_V;
   Float_t         E_V;
   Float_t         costhe_h;
   Float_t         costhe_q;
   Float_t         Type;
   Float_t         WT00;
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

   TreeForResBosHighMassZ();
   virtual ~TreeForResBosHighMassZ();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void Init();

   bool isReweight = false;
   virtual void Reweight(){isReweight = true;};

   bool isDilution = false;
   virtual void TurnOnDilution(){isDilution = true;}
};

#endif

#ifdef TreeForResBosHighMassZ_cxx

void TreeForResBosHighMassZ::Init()
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
