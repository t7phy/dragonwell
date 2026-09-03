#ifndef TreeForResBos_h
#define TreeForResBos_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class TreeForResBos
{
 public:

   TFile *rootfile[1000];
   TTree *fChain[1000];
   long TotalEntries[1000];

   bool isReweight = false;
   bool isFSR = false;
   bool isDilution = false;

   vector<TString> RootNames;
   vector<TString> RootTypes;
   TString nchannel;

   int FirstFile, EndFile;
   bool OneFilePerJob = false;

 Float_t        ElectronPx;
 Float_t        ElectronPy;
 Float_t        ElectronPz;
 Float_t        ElectronE;
 Float_t        PositronPx;
 Float_t        PositronPy;
 Float_t        PositronPz;
 Float_t        PositronE;
 Float_t        Weight;
 Float_t        ZPx;
 Float_t        ZPy;
 Float_t        ZPz;
 Float_t        ZE;
 Float_t        costhe_h;
 Float_t        costhe_q;
 Float_t          Type;

 Float_t        Photon1Px;
 Float_t        Photon1Py;
 Float_t        Photon1Pz;
 Float_t        Photon1E;
 Float_t        Photon2Px;
 Float_t        Photon2Py;
 Float_t        Photon2Pz;
 Float_t        Photon2E;

   TreeForResBos();
   virtual ~TreeForResBos();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual TString GetRootType(TString RootName);
   virtual void InputFile(vector<TString> RootNames);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void Reweight();
   virtual void TurnOnFSR();
   virtual void TurnOnDilution(){isDilution = true;}
};
#endif
