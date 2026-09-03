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

   // List of branches

   TreeForQBH();
   virtual ~TreeForQBH();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void CloseFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void LinkHist(HistsQBH* myhists);
   virtual void Init();

   virtual void updateCutFlow(TH1D *inCutFlow, std::map<std::string, double> *inLabelMap, std::string cutName, double step = 1, bool doUpdate = true); //!
};

#endif
