//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon May 25 18:14:57 2020 by ROOT version 6.16/00
// from TTree analysis/analysis
// found on file: submitDir/data-myOutput/testSample.root
//////////////////////////////////////////////////////////

#ifndef TreeForFwdReco_h
#define TreeForFwdReco_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class TreeForFwdReco
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

   vector<float>   *fwdel_e;
   vector<float>   *fwdel_eta;
   vector<float>   *fwdel_phi;
   vector<float>   *fwdel_pt;
   vector<float>   *fwdel_clpt;
   vector<int>     *fwdel_PassPtCut;
   vector<int>     *fwdel_truthMatched;
   vector<float>   *fwdel_corrected_e;
   vector<float>   *fwdel_corrected_eta;
   vector<float>   *fwdel_corrected_phi;
   vector<float>   *fwdel_corrected_pt;
   vector<float>   *fwdel_corrected_clpt;
   vector<int>     *fwdel_corrected_PassPtCut;
   vector<int>     *fwdel_corrected_truthMatched;
   vector<float>   *truthel_e;
   vector<float>   *truthel_eta;
   vector<float>   *truthel_phi;
   vector<float>   *truthel_pt;
   vector<float>   *truthel_et;
   vector<float>   *truthel_deltaE;
   vector<float>   *truthel_deltaPt;
   vector<float>   *truthel_deltaEt;
   vector<int>     *truthel_Region;
   vector<int>     *truthel_truthMatched;
   vector<int>     *truthel_truthMatchedAfterCut;
   Int_t           EventNumber;
   Float_t         AverageMu;
   Int_t           EventRegion;


   // List of branches
   TBranch        *b_fwdel_e;   //!
   TBranch        *b_fwdel_eta;   //!
   TBranch        *b_fwdel_phi;   //!
   TBranch        *b_fwdel_pt;   //!
   TBranch        *b_fwdel_clpt;   //!
   TBranch        *b_fwdel_PassPtCut;   //!
   TBranch        *b_fwdel_truthMatched;   //!
   TBranch        *b_fwdel_corrected_e;   //!
   TBranch        *b_fwdel_corrected_eta;   //!
   TBranch        *b_fwdel_corrected_phi;   //!
   TBranch        *b_fwdel_corrected_pt;   //!
   TBranch        *b_fwdel_corrected_clpt;   //!
   TBranch        *b_fwdel_corrected_PassPtCut;   //!
   TBranch        *b_fwdel_corrected_truthMatched;   //!
   TBranch        *b_truthel_e;   //!
   TBranch        *b_truthel_eta;   //!
   TBranch        *b_truthel_phi;   //!
   TBranch        *b_truthel_pt;   //!
   TBranch        *b_truthel_et;   //!
   TBranch        *b_truthel_deltaE;   //!
   TBranch        *b_truthel_deltaPt;   //!
   TBranch        *b_truthel_deltaEt;   //!
   TBranch        *b_truthel_Region;   //!
   TBranch        *b_truthel_truthMatched;   //!
   TBranch        *b_truthel_truthMatchedAfterCut;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_AverageMu;   //!
   TBranch        *b_EventRegion;   //!

   TreeForFwdReco();
   virtual ~TreeForFwdReco();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void Init();
};

#endif

#ifdef TreeForFwdReco_cxx

void TreeForFwdReco::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   fwdel_e = 0;
   fwdel_eta = 0;
   fwdel_phi = 0;
   fwdel_pt = 0;
   fwdel_clpt = 0;
   fwdel_PassPtCut = 0;
   fwdel_truthMatched = 0;
   fwdel_corrected_e = 0;
   fwdel_corrected_eta = 0;
   fwdel_corrected_phi = 0;
   fwdel_corrected_pt = 0;
   fwdel_corrected_clpt = 0;
   fwdel_corrected_PassPtCut = 0;
   fwdel_corrected_truthMatched = 0;
   truthel_e = 0;
   truthel_eta = 0;
   truthel_phi = 0;
   truthel_pt = 0;
   truthel_et = 0;
   truthel_deltaE = 0;
   truthel_deltaPt = 0;
   truthel_deltaEt = 0;
   truthel_Region = 0;
   truthel_truthMatched = 0;
   truthel_truthMatchedAfterCut = 0;

}

#endif // #ifdef analysis_cxx
