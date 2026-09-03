//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 12 13:54:03 2020 by ROOT version 6.14/04
// from TTree Zeetree/Zeetree
// found on file: Zeetree.root
//////////////////////////////////////////////////////////

#ifndef TreeForQBH_h
#define TreeForQBH_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "TH1D.h"
#include "QBH/HistsQBH.h"
#include "QBH/loopQBH.h"

class loopQBH;
class HistsQBH;
class TreeForQBH;

using namespace std;

class TreeForQBH
{
 public :

   TFile *rootfile[1000];
   TTree *fChain[1000];
   long TotalEntries[1000];

   vector<TString> RootNames;

   vector<TString> RootTypes;

   map<TString, int> SysNameIndex;
   TString SystematicName = "";
   TString SavedSystematicName = "";

   loopQBH* fLoop;
   HistsQBH* fHist;

   int FirstFile, EndFile;
   bool OneFilePerJob = false;

// Define for generate a new Tree
   TFile *hf;
   TTree *GenerateTree[1000];

   TH1D* Event_CutFlow;
   TH1D* Electron_CutFlow;
   TH1D* Muon_CutFlow;

   std::map<std::string, double> *Event_CutNameMap; //!
   std::map<std::string, double> *Electron_CutNameMap; //!
   std::map<std::string, double> *Muon_CutNameMap; //!

   TH1D* Event_WeightedCutFlow;
   TH1D* Electron_WeightedCutFlow;
   TH1D* Muon_WeightedCutFlow;

   std::map<std::string, double> *Event_WeightedCutNameMap; //!
   std::map<std::string, double> *Electron_WeightedCutNameMap; //!
   std::map<std::string, double> *Muon_WeightedCutNameMap; //!

   TTree *TruthTree;
   virtual void GenerateFile(TString FileName);
   virtual void DefineTree(int isys, TString TreeName);
   virtual void FillTree(int isys);
   //virtual void DefineTruthTree();
   //virtual void FillTruthTree();
   virtual void SaveFile();

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         TotalWeight;
   Float_t         TotalWeightLoose;
   Float_t         LeptonTightWeight;
   Float_t         LeadingLepWeight;
   Float_t         SubleadingLepWeight;
   Int_t           passLeadingLepTight;

   Float_t         LepJetMass;
   Float_t         LeadingLeptonPt;
   Float_t         LeadingLeptonEta;
   Float_t         LeadingJetPt;
   Int_t           Njets;
   Float_t         MissingET;
   Float_t         Mll;
   Float_t         DeltaRLepJet;
   Float_t         detaLepJet;
   Float_t         dphiLepJet;
   Float_t         METSig;
   Int_t           LeptonFlavor;
   Float_t         Lepton1_d0Sig;
   Float_t         Lepton2_d0Sig;

   Int_t           passInclusive;
   Int_t           passFakeCR;
   Int_t           passWCR;
   Int_t           passWVR;
   Int_t           passZCR;
   Int_t           passZVR;
   Int_t           passTCR;
   Int_t           passTVR;
   Int_t           passSR;
   Int_t           passSVR;


   // List of branches
   TBranch        *b_TotalWeight;   //!
   TBranch        *b_LeadingLepWeight;   //!
   TBranch        *b_SubladingLepWeight;   //!
   TBranch        *b_passLeadingLepTight;   //!
   TBranch        *b_LepJetMass;   //!
   TBranch        *b_LeadingLeptonPt;   //!
   TBranch        *b_LeadingLeptonEta;   //!
   TBranch        *b_LeadingJetPt;   //!
   TBranch        *b_Njets;   //!
   TBranch        *b_MissingET;   //!
   TBranch        *b_Mll;   //!
   TBranch        *b_DeltaRLepJet;   //!
   TBranch        *b_detaLepJet;   //!
   TBranch        *b_dphiLepJet;   //!
   TBranch        *b_METSig;   //!
   TBranch        *b_LeptonFlavor;   //!
   TBranch        *b_Lepton1_d0Sig;   //!
   TBranch        *b_Lepton2_d0Sig;   //!

   TBranch        *b_passInclusive;   //!
   TBranch        *b_passFakeCR;   //!
   TBranch        *b_passWCR;   //!
   TBranch        *b_passWVR;   //!
   TBranch        *b_passZCR;   //!
   TBranch        *b_passZVR;   //!
   TBranch        *b_passTCR;   //!
   TBranch        *b_passTVR;   //!
   TBranch        *b_passSR;   //!
   TBranch        *b_passSVR;   //!


   TreeForQBH();
   virtual ~TreeForQBH();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void CloseFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual TString GetRootType(TString RootName);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void LinkHist(HistsQBH* myhists);
   virtual void Init();

   virtual void updateCutFlow(TH1D *inCutFlow, std::map<std::string, double> *inLabelMap, std::string cutName, double step = 1, bool doUpdate = true); //!
};

#endif
