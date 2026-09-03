#ifndef TreeForMadGraph_h
#define TreeForMadGraph_h

#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include "TClonesArray.h"
#include "TObject.h"
#include <TFile.h>
#include "ExRootClasses.h"
#include "ExRootAnalysisLinkDef.h"

using namespace std;

class TreeForMadGraph
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

   static constexpr Int_t kMaxEvent = 1;
   static constexpr Int_t kMaxRwgt = 103;
   static constexpr Int_t kMaxParticle = 5;

   // Declaration of leaf types
   Int_t           Event_;
   UInt_t          Event_fUniqueID[kMaxEvent];   //[Event_]
   UInt_t          Event_fBits[kMaxEvent];   //[Event_]
   Long64_t        Event_Number[kMaxEvent];   //[Event_]
   Int_t           Event_Nparticles[kMaxEvent];   //[Event_]
   Int_t           Event_ProcessID[kMaxEvent];   //[Event_]
   Double_t        Event_Weight[kMaxEvent];   //[Event_]
   Double_t        Event_ScalePDF[kMaxEvent];   //[Event_]
   Double_t        Event_CouplingQED[kMaxEvent];   //[Event_]
   Double_t        Event_CouplingQCD[kMaxEvent];   //[Event_]
   Int_t           Event_size;
   Int_t           Rwgt_;
   UInt_t          Rwgt_fUniqueID[kMaxRwgt];   //[Rwgt_]
   UInt_t          Rwgt_fBits[kMaxRwgt];   //[Rwgt_]
   Double_t        Rwgt_Weight[kMaxRwgt];   //[Rwgt_]
   Int_t           Rwgt_size;
   Int_t           Particle_;
   UInt_t          Particle_fUniqueID[kMaxParticle];   //[Particle_]
   UInt_t          Particle_fBits[kMaxParticle];   //[Particle_]
   Int_t           Particle_PID[kMaxParticle];   //[Particle_]
   Int_t           Particle_Status[kMaxParticle];   //[Particle_]
   Int_t           Particle_Mother1[kMaxParticle];   //[Particle_]
   Int_t           Particle_Mother2[kMaxParticle];   //[Particle_]
   Int_t           Particle_ColorLine1[kMaxParticle];   //[Particle_]
   Int_t           Particle_ColorLine2[kMaxParticle];   //[Particle_]
   Double_t        Particle_Px[kMaxParticle];   //[Particle_]
   Double_t        Particle_Py[kMaxParticle];   //[Particle_]
   Double_t        Particle_Pz[kMaxParticle];   //[Particle_]
   Double_t        Particle_E[kMaxParticle];   //[Particle_]
   Double_t        Particle_M[kMaxParticle];   //[Particle_]
   Double_t        Particle_PT[kMaxParticle];   //[Particle_]
   Double_t        Particle_Eta[kMaxParticle];   //[Particle_]
   Double_t        Particle_Phi[kMaxParticle];   //[Particle_]
   Double_t        Particle_Rapidity[kMaxParticle];   //[Particle_]
   Double_t        Particle_LifeTime[kMaxParticle];   //[Particle_]
   Double_t        Particle_Spin[kMaxParticle];   //[Particle_]
   Int_t           Particle_size;

   // List of branches
   TBranch        *b_Event_;   //!
   TBranch        *b_Event_fUniqueID;   //!
   TBranch        *b_Event_fBits;   //!
   TBranch        *b_Event_Number;   //!
   TBranch        *b_Event_Nparticles;   //!
   TBranch        *b_Event_ProcessID;   //!
   TBranch        *b_Event_Weight;   //!
   TBranch        *b_Event_ScalePDF;   //!
   TBranch        *b_Event_CouplingQED;   //!
   TBranch        *b_Event_CouplingQCD;   //!
   TBranch        *b_Event_size;   //!
   TBranch        *b_Rwgt_;   //!
   TBranch        *b_Rwgt_fUniqueID;   //!
   TBranch        *b_Rwgt_fBits;   //!
   TBranch        *b_Rwgt_Weight;   //!
   TBranch        *b_Rwgt_size;   //!
   TBranch        *b_Particle_;   //!
   TBranch        *b_Particle_fUniqueID;   //!
   TBranch        *b_Particle_fBits;   //!
   TBranch        *b_Particle_PID;   //!
   TBranch        *b_Particle_Status;   //!
   TBranch        *b_Particle_Mother1;   //!
   TBranch        *b_Particle_Mother2;   //!
   TBranch        *b_Particle_ColorLine1;   //!
   TBranch        *b_Particle_ColorLine2;   //!
   TBranch        *b_Particle_Px;   //!
   TBranch        *b_Particle_Py;   //!
   TBranch        *b_Particle_Pz;   //!
   TBranch        *b_Particle_E;   //!
   TBranch        *b_Particle_M;   //!
   TBranch        *b_Particle_PT;   //!
   TBranch        *b_Particle_Eta;   //!
   TBranch        *b_Particle_Phi;   //!
   TBranch        *b_Particle_Rapidity;   //!
   TBranch        *b_Particle_LifeTime;   //!
   TBranch        *b_Particle_Spin;   //!
   TBranch        *b_Particle_size;   //!

   TreeForMadGraph();
   virtual ~TreeForMadGraph();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void Init();
};

#endif

#ifdef TreeForMadGraph_cxx

void TreeForMadGraph::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers

   //Event_ = 0;
   //Rwgt_ = 0;
   //Particle_ = 0;
}

#endif
