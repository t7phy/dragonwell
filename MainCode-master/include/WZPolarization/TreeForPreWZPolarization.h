//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 12 13:54:03 2020 by ROOT version 6.14/04
// from TTree Zeetree/Zeetree
// found on file: Zeetree.root
//////////////////////////////////////////////////////////

#ifndef TreeForPreWZPolarization_h
#define TreeForPreWZPolarization_h

#include "RootCommon.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "Tools/Tools.h"

using namespace std;

class TreeForPreWZPolarization
{
 public :
   bool isData = false;

   TFile *rootfile[1000];
   TTree *fChain[1000];
   long TotalEntries[1000];

   vector<TString> RootNames;

   vector<int> RootTypes;
   vector<double> CrossSections;
   vector<double> SumOfWeights;
   vector<int> Years;
   int nchannel;
   TString SaveName;
   double CrossSection;
//   double SumOfWeight;
   int Year;
   int UniqueYear = 0;
   vector<int> UniqueYears;

   map<pair<int, int>, double> SumOfWeightsMap;
   double Lumi1516 = 0.0;
   double Lumi17 = 0.0;
   double Lumi18 = 0.0;

   map<pair<int, int>, TString> TheoryErrorType;

   vector<TString> SysNameSignalWZ;
   map<TString, int> SysNameIndexSignalWZ;

   int FirstFile, EndFile;
   bool OneFilePerJob = false;

   TTree *metaTree[1000];
   long metaTreeEntries[1000];

   TTree * TruthTree[1000];
   long TruthTreeEntries[1000];

// Fixed size dimensions of array or collections stored in the TTree if any.

   bool doTruthSelection = false;
   bool doPDFAndQCDUnc = false;

   // Declaration of leaf types
   Long64_t        runNumber;
   Long64_t        mcChannelNumber;
   Double_t        totalWeightedEntries;
   Double_t        crossSection;
   string          *inputFileName;
   vector<string>  *WeightNames;

   string          *Systematic;
   Long64_t        EventNumber;
   Long64_t        RunNumber;
   Long64_t        OriginRunNumber;
   Long64_t        ChannelNumber;
   Float_t         AverageMu;
   Float_t         MCEventWeight;
   vector<float>   *MCEventWeights;
   Float_t         MCPileupWeight;
   Float_t         JetWeight;
   Float_t         KFactor;
   Float_t         VertexWeight;
   Float_t         met_et;
   Float_t         met_px;
   Float_t         met_py;
   Int_t           nSoftMuons;
   Int_t           nSoftElectrons;
   Int_t           nSoftJets;
   vector<float>   *el_e;
   vector<float>   *el_eta;
   vector<float>   *el_phi;
   vector<float>   *el_pt;
   vector<float>   *el_charge;
   vector<float>   *el_d0Sig;
   vector<int>     *el_mediumID;
   vector<float>   *el_mediumIDWeight;
   vector<int>     *el_tightID;
   vector<float>   *el_tightIDWeight;
   vector<int>     *el_FCLooseIso;
   vector<float>   *el_FCLooseIsoWeight;
   vector<int>     *el_FCTightIso;
   vector<float>   *el_FCTightIsoWeight;
   vector<int>     *el_FCHighPtIso;
   vector<float>   *el_FCHighPtIsoWeight;
   vector<int>     *el_HighPtCaloOnlyIso;
   vector<float>   *el_HighPtCaloOnly_MediumID_IsoWeight;
   vector<float>   *el_HighPtCaloOnly_TightID_IsoWeight;
   vector<int>     *el_Loose_VarRadIso;
   vector<float>   *el_Loose_VarRad_MediumID_IsoWeight;
   vector<float>   *el_Loose_VarRad_TightID_IsoWeight;
   vector<int>     *el_Tight_VarRadIso;
   vector<float>   *el_Tight_VarRad_MediumID_IsoWeight;
   vector<float>   *el_Tight_VarRad_TightID_IsoWeight;
   vector<int>     *el_triggerMatched;
   vector<int>     *el_truthMatched;
   vector<float>   *el_recoWeight;
   vector<int>     *el_isbaseline;
   vector<int>     *el_isAmbiguity;
   vector<float>   *mu_e;
   vector<float>   *mu_eta;
   vector<float>   *mu_phi;
   vector<float>   *mu_pt;
   vector<float>   *mu_charge;
   vector<float>   *mu_d0Sig;
   vector<int>     *mu_mediumID;
   vector<float>   *mu_mediumIDWeight;
   vector<int>     *mu_tightID;
   vector<float>   *mu_tightIDWeight;
   vector<int>     *mu_FCLooseIso;
   vector<float>   *mu_FCLooseIsoWeight;
   vector<int>     *mu_FCTightIso;
   vector<float>   *mu_FCTightIsoWeight;
   vector<int>     *mu_PflowLooseIso;
   vector<float>   *mu_PflowLooseIsoWeight;
   vector<int>     *mu_PflowTightIso;
   vector<float>   *mu_PflowTightIsoWeight;
   vector<int>     *mu_triggerMatched;
   vector<int>     *mu_truthMatched;
   vector<float>   *mu_IPWeight;
   vector<int>     *mu_isbaseline;
   vector<float>   *jt_e;
   vector<float>   *jt_eta;
   vector<float>   *jt_phi;
   vector<float>   *jt_pt;
   vector<int>     *jt_passJVT;
   vector<int>     *jt_passBtag;
   //vector<float>   *truth_e;
   //vector<float>   *truth_eta;
   //vector<float>   *truth_phi;
   //vector<float>   *truth_pt;
   //vector<int>     *truth_pid;
   //vector<int>     *truth_mid;
   Float_t         truthPropagator_px;
   Float_t         truthPropagator_py;
   Float_t         truthPropagator_pz;
   Float_t         truthPropagator_e;
   Long64_t        pdgSequence;

   //Truth tree
   Long64_t        TruthEventNumber;
   Long64_t        TruthRunNumber;
   Long64_t        TruthOriginRunNumber;
   Long64_t        TruthChannelNumber;
   Float_t         TruthAverageMu;
   Long64_t        TruthYear;
   Float_t         TruthMCEventWeight;
   vector<float>   *TruthMCEventWeights;
   Float_t         TruthMCPileupWeight;
   Float_t         TruthJetWeight;
   Float_t         TruthKFactor;
   Float_t         TruthVertexWeight;
   vector<float>   *truth_e;
   vector<float>   *truth_eta;
   vector<float>   *truth_phi;
   vector<float>   *truth_pt;
   vector<int>     *truth_pid;
   vector<int>     *truth_mid;
   //

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_totalWeightedEntries;   //!
   TBranch        *b_crossSection;   //!
   TBranch        *b_inputFileName;   //!
   TBranch        *b_WeightNames;   //!

   TBranch        *b_Systematic;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_OriginRunNumber;   //!
   TBranch        *b_ChannelNumber;   //!
   TBranch        *b_AverageMu;   //!
   TBranch        *b_MCEventWeight;   //!
   TBranch        *b_MCEventWeights;   //!
   TBranch        *b_MCPileupWeight;   //!
   TBranch        *b_JetWeight;   //!
   TBranch        *b_KFactor;   //!
   TBranch        *b_VertexWeight;   //!
   TBranch        *b_met_et;   //!
   TBranch        *b_met_px;   //!
   TBranch        *b_met_py;   //!
   TBranch        *b_nSoftMuons;   //!
   TBranch        *b_nSoftElectrons;   //!
   TBranch        *b_nSoftJets;   //!
   TBranch        *b_el_e;   //!
   TBranch        *b_el_eta;   //!
   TBranch        *b_el_phi;   //!
   TBranch        *b_el_pt;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_d0Sig;   //!
   TBranch        *b_el_mediumID;   //!
   TBranch        *b_el_mediumIDWeight;   //!
   TBranch        *b_el_tightID;   //!
   TBranch        *b_el_tightIDWeight;   //!
   TBranch        *b_el_FCLooseIso;   //!
   TBranch        *b_el_FCLooseIsoWeight;   //!
   TBranch        *b_el_FCTightIso;   //!
   TBranch        *b_el_FCTightIsoWeight;   //!
   TBranch        *b_el_FCHighPtIso;   //!
   TBranch        *b_el_FCHighPtIsoWeight;   //!
   TBranch        *b_el_HighPtCaloOnlyIso;   //!
   TBranch        *b_el_HighPtCaloOnly_MediumID_IsoWeight;   //!
   TBranch        *b_el_HighPtCaloOnly_TightID_IsoWeight;   //!
   TBranch        *b_el_Tight_VarRadIso;   //!
   TBranch        *b_el_Tight_VarRad_MediumID_IsoWeight;   //!
   TBranch        *b_el_Tight_VarRad_TightID_IsoWeight;   //!
   TBranch        *b_el_Loose_VarRadIso;   //!
   TBranch        *b_el_Loose_VarRad_MediumID_IsoWeight;   //!
   TBranch        *b_el_Loose_VarRad_TightID_IsoWeight;   //!
   TBranch        *b_el_triggerMatched;   //!
   TBranch        *b_el_truthMatched;   //!
   TBranch        *b_el_recoWeight;   //!
   TBranch        *b_el_isbaseline;   //!
   TBranch        *b_el_isAmbiguity;   //!
   TBranch        *b_mu_e;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_d0Sig;   //!
   TBranch        *b_mu_mediumID;   //!
   TBranch        *b_mu_mediumIDWeight;   //!
   TBranch        *b_mu_tightID;   //!
   TBranch        *b_mu_tightIDWeight;   //!
   TBranch        *b_mu_FCLooseIso;   //!
   TBranch        *b_mu_FCLooseIsoWeight;   //!
   TBranch        *b_mu_FCTightIso;   //!
   TBranch        *b_mu_FCTightIsoWeight;   //!
   TBranch        *b_mu_PflowLooseIso;   //!
   TBranch        *b_mu_PflowLooseIsoWeight;   //!
   TBranch        *b_mu_PflowTightIso;   //!
   TBranch        *b_mu_PflowTightIsoWeight;   //!
   TBranch        *b_mu_triggerMatched;   //!
   TBranch        *b_mu_truthMatched;   //!
   TBranch        *b_mu_IPWeight;   //!
   TBranch        *b_mu_isbaseline;   //!
   TBranch        *b_jt_e;   //!
   TBranch        *b_jt_eta;   //!
   TBranch        *b_jt_phi;   //!
   TBranch        *b_jt_pt;   //!
   TBranch        *b_jt_passJVT;   //!
   TBranch        *b_jt_passBtag;   //!
   //TBranch        *b_truth_e;   //!
   //TBranch        *b_truth_eta;   //!
   //TBranch        *b_truth_phi;   //!
   //TBranch        *b_truth_pt;   //!
   //TBranch        *b_truth_pid;   //!
   //TBranch        *b_truth_mid;   //!
   TBranch        *b_truthPropagator_px;   //!
   TBranch        *b_truthPropagator_py;   //!
   TBranch        *b_truthPropagator_pz;   //!
   TBranch        *b_truthPropagator_e;   //!
   TBranch        *b_pdgSequence;   //!

   //Truth tree
   TBranch        *b_TruthEventNumber;   //!
   TBranch        *b_TruthRunNumber;   //!
   TBranch        *b_TruthOriginRunNumber;   //!
   TBranch        *b_TruthChannelNumber;   //!
   TBranch        *b_TruthAverageMu;   //!
   TBranch        *b_TruthYear;   //!
   TBranch        *b_TruthMCEventWeight;   //!
   TBranch        *b_TruthMCEventWeights;   //!
   TBranch        *b_TruthMCPileupWeight;   //!
   TBranch        *b_TruthJetWeight;   //!
   TBranch        *b_TruthKFactor;   //!
   TBranch        *b_TruthVertexWeight;   //!
   TBranch        *b_truth_e;   //!
   TBranch        *b_truth_eta;   //!
   TBranch        *b_truth_phi;   //!
   TBranch        *b_truth_pt;   //!
   TBranch        *b_truth_pid;   //!
   TBranch        *b_truth_mid;   //!

   TreeForPreWZPolarization();
   virtual ~TreeForPreWZPolarization();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void CloseFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual int GetRootType(TString RootName);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void GetTruthEntry(int ifile, long i);
   virtual double GetSumOfWeight(int nchannel, int Year);
   virtual void GetPDFAndQCDIndex(int ifile);
   virtual int GetYear(TString RootName);
   virtual void InputSumOfWeight(map<pair<int, int>, double> SumOfWeightsMap);
   virtual void InputLuminosity(double Lumi1516, double Lumi17, double Lumi18);
   virtual void Init();

   virtual void BkgSelection(TString BkgName);
   virtual void YearSelection(int Year);
   virtual void DoTruthSelection(){doTruthSelection = true;}
   virtual void SavePDFAndQCDUnc(){doPDFAndQCDUnc = true;}
   virtual void InitialSysName();
};

#endif

#ifdef TreeForPreWZPolarization_cxx
void TreeForPreWZPolarization::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   inputFileName = 0;
   WeightNames = 0;

   Systematic = 0;
   MCEventWeights = 0;
   TruthMCEventWeights = 0;
   el_e = 0;
   el_eta = 0;
   el_phi = 0;
   el_pt = 0;
   el_charge = 0;
   el_d0Sig = 0;
   el_mediumID = 0;
   el_mediumIDWeight = 0;
   el_tightID = 0;
   el_tightIDWeight = 0;
   el_FCLooseIso = 0;
   el_FCLooseIsoWeight = 0;
   el_FCTightIso = 0;
   el_FCTightIsoWeight = 0;
   el_FCHighPtIso = 0;
   el_FCHighPtIsoWeight = 0;
   el_HighPtCaloOnlyIso = 0;
   el_HighPtCaloOnly_MediumID_IsoWeight = 0;
   el_HighPtCaloOnly_TightID_IsoWeight = 0;
   el_Tight_VarRadIso = 0;
   el_Tight_VarRad_MediumID_IsoWeight = 0;
   el_Tight_VarRad_TightID_IsoWeight = 0;
   el_Loose_VarRadIso = 0;
   el_Loose_VarRad_MediumID_IsoWeight = 0;
   el_Loose_VarRad_TightID_IsoWeight = 0;
   el_triggerMatched = 0;
   el_truthMatched = 0;
   el_recoWeight = 0;
   el_isbaseline = 0;
   el_isAmbiguity = 0;
   mu_e = 0;
   mu_eta = 0;
   mu_phi = 0;
   mu_pt = 0;
   mu_charge = 0;
   mu_d0Sig = 0;
   mu_mediumID = 0;
   mu_mediumIDWeight = 0;
   mu_tightID = 0;
   mu_tightIDWeight = 0;
   mu_FCLooseIso = 0;
   mu_FCLooseIsoWeight = 0;
   mu_FCTightIso = 0;
   mu_FCTightIsoWeight = 0;
   mu_PflowLooseIso = 0;
   mu_PflowLooseIsoWeight = 0;
   mu_PflowTightIso = 0;
   mu_PflowTightIsoWeight = 0;
   mu_triggerMatched = 0;
   mu_truthMatched = 0;
   mu_IPWeight = 0;
   mu_isbaseline = 0;
   jt_e = 0;
   jt_eta = 0;
   jt_phi = 0;
   jt_pt = 0;
   jt_passJVT = 0;
   jt_passBtag = 0;
   truth_e = 0;
   truth_eta = 0;
   truth_phi = 0;
   truth_pt = 0;
   truth_pid = 0;
   truth_mid = 0;

}

#endif
