//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 16 03:49:58 2024 by ROOT version 6.20/06
// from TTree nominal/nominal
// found on file: LJSkim_v6.0_file_Run3_data_merged.root
//////////////////////////////////////////////////////////

#ifndef TreeForPreQBH_h
#define TreeForPreQBH_h

#include "RootCommon.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "Tools/Tools.h"
#include "Tools/Log.h"

using namespace std;

class TreeForPreQBH
{
 public :
   bool isData = false;

   TFile *rootfile[1000];
   TTree *fChain[1000];
   TDirectoryFile* dir[1000];
   long TotalEntries[1000];

   vector<TString> RootNames;

   vector<TString> RootTypes;
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
   vector<int>     *DFCommonJets_eventClean_LooseBad;
   vector<int>     *jet_ConeTruthLabelID;
   vector<float>   *jet_E;
   vector<float>   *jet_Jvt;
   vector<int>     *jet_PartonTruthLabelID;
   vector<bool>    *jet_btag;
   vector<float>   *jet_btag_sf;
   vector<float>   *jet_eta;
   vector<float>   *jet_phi;
   vector<float>   *jet_pt;
   vector<float>   *truth_el_E;
   vector<int>     *truth_el_barcode;
   vector<float>   *truth_el_eta;
   vector<int>     *truth_el_parentID;
   vector<int>     *truth_el_pdgId;
   vector<float>   *truth_el_phi;
   vector<float>   *truth_el_pt;
   vector<int>     *truth_el_status;
   vector<int>     *truth_el_truthOrigin;
   vector<int>     *truth_el_truthType;
   vector<int>     *truth_jet_ConeTruthLabelID;
   vector<float>   *truth_jet_E;
   vector<float>   *truth_jet_Jvt;
   vector<int>     *truth_jet_PartonTruthLabelID;
   vector<float>   *truth_jet_eta;
   vector<float>   *truth_jet_phi;
   vector<float>   *truth_jet_pt;
   vector<float>   *truth_muon_E;
   vector<int>     *truth_muon_barcode;
   vector<float>   *truth_muon_eta;
   vector<int>     *truth_muon_parentID;
   vector<int>     *truth_muon_pdgId;
   vector<float>   *truth_muon_phi;
   vector<float>   *truth_muon_pt;
   vector<int>     *truth_muon_status;
   vector<int>     *truth_muon_truthOrigin;
   vector<int>     *truth_muon_truthType;
   Float_t         weight_norm;
   Float_t         weight_lumi;
   Int_t           runNumber;
   Long64_t        eventNumber;
   Int_t           lumiBlock;
   UInt_t          coreFlags;
   Int_t           bcid;
   Int_t           mcEventNumber; // MC
   Int_t           mcChannelNumber; // MC
   Int_t           NPV;
   Float_t         actualInteractionsPerCrossing;
   Float_t         averageInteractionsPerCrossing;
   Float_t         weight_pileup;
   Float_t         correctedAverageMu;
   Float_t         correctedAndScaledAverageMu;
   Float_t         correctedActualMu;
   Float_t         correctedAndScaledActualMu;
   Float_t         weight_pileup_up;
   Float_t         weight_pileup_down;
   Int_t           rand_run_nr; // MC
   Int_t           rand_lumiblock_nr; // MC
   Float_t         beamSpotWeight;
   Int_t           passL1;
   Int_t           passHLT;
   Int_t           ntruth_muon;
   Int_t           ntruth_el;
   Int_t           ntruth_jet;
   Int_t           njet;
   Float_t         metFinalTrk;
   Float_t         metFinalTrkPx;
   Float_t         metFinalTrkPy;
   Float_t         metFinalTrkSumEt;
   Float_t         metFinalTrkPhi;
   Float_t         metFinalTrkOverSqrtSumEt;
   Float_t         metFinalTrkOverSqrtHt;
   Float_t         metFinalTrkSignificance;
   Float_t         metFinalTrkSigDirectional;
   Float_t         metEle;
   Float_t         metEleSumEt;
   Float_t         metElePhi;
   Float_t         metMuons;
   Float_t         metMuonsSumEt;
   Float_t         metMuonsPhi;
   Float_t         metJet;
   Float_t         metJetSumEt;
   Float_t         metJetPhi;
   Float_t         metSoftTrk;
   Float_t         metSoftTrkSumEt;
   Float_t         metSoftTrkPhi;
   Bool_t          HLT_j360;
   Bool_t          HLT_j380;
   Bool_t          HLT_j420;
   Bool_t          HLT_j420_pf_ftf_preselj225_L1J100;
   Bool_t          HLT_e24_lhmedium_L1EM20VH;
   Bool_t          HLT_e60_lhmedium;
   Bool_t          HLT_e120_lhloose;
   Bool_t          HLT_e26_lhtight_nod0_ivarloose;
   Bool_t          HLT_e60_lhmedium_nod0;
   Bool_t          HLT_e140_lhloose_nod0;
   Bool_t          HLT_e26_lhtight_ivarloose_L1EM22VHI;
   Bool_t          HLT_e26_lhtight_ivarloose_L1eEM26M;
   Bool_t          HLT_e60_lhmedium_L1EM22VHI;
   Bool_t          HLT_e60_lhmedium_L1eEM26M;
   Bool_t          HLT_e140_lhloose_L1EM22VHI;
   Bool_t          HLT_e140_lhloose_L1eEM26M;
   Bool_t          HLT_mu20_iloose_L1MU15;
   Bool_t          HLT_mu26_ivarmedium;
   Bool_t          HLT_mu50;
   Bool_t          HLT_mu40;
   Bool_t          HLT_mu24_ivarmedium_L1MU14FCH;
   Bool_t          HLT_mu50_L1MU14FCH;
   Bool_t          HLT_2e12_lhloose_L12EM10VH;
   Bool_t          HLT_2e17_lhvloose_nod0;
   Bool_t          HLT_2e24_lhvloose_nod0;
   Bool_t          HLT_2e24_lhvloose_L12EM20VH;
   Bool_t          HLT_2e24_lhvloose_L12eEM24L;
   Bool_t          HLT_singleLep;
   Bool_t          HLT_singleJet;
   Int_t           randomRunNumber;
   Int_t           datasetNumber;
   Int_t           year;
   Float_t         mcEventWeight = 1.0;
   Float_t         sample_xSec;
   Float_t         sample_xSec_up_rel;
   Float_t         sample_xSec_down_rel;
   Float_t         sample_kFactor;
   Float_t         sample_filterEff;
   Float_t         weight_gen;
   Float_t         weight_lepton;
   Float_t         weight_jvt;
   Float_t         weight_btag;
   Float_t         weight_singleleptonTrigSF;
   Float_t         weight_dileptonTrigSF;
   Float_t         fakeweight;
   Int_t           n_truth_el;
   Int_t           n_truth_mu;
   Int_t           n_truth_lep;
   Int_t           n_el;
   Int_t           n_mu;
   Int_t           n_lep;
   Int_t           n_signal_el;
   Int_t           n_signal_mu;
   Int_t           n_signal_lep;
   Int_t           n_bjets;
   Int_t           lepton1_isEl;
   Float_t         lepton1_m;
   Float_t         lepton1_E;
   Float_t         lepton1_pt;
   Float_t         lepton1_phi;
   Float_t         lepton1_eta;
   Float_t         lepton1_charge;
   Int_t           lepton1_truthType;
   Int_t           lepton1_truthOrigin;
   Int_t           lepton1_IFFType;
   Bool_t          lepton1_isPromptIFF;
   Float_t         lepton1_d0sig;
   Float_t         lepton1_z0sinTheta;
   Float_t         lepton1_d0;
   Float_t         lepton1_z0;
   Int_t           lepton1_isSig;
   Int_t           lepton1_isIso;
   Bool_t          lepton1_isMatched;
   Float_t         lepton1_truthE;
   Float_t         lepton1_truthpt;
   Float_t         lepton1_truthphi;
   Float_t         lepton1_trutheta;
   Int_t           lepton1_truthpdgid;
   Int_t           lepton2_isEl;
   Float_t         lepton2_m;
   Float_t         lepton2_E;
   Float_t         lepton2_pt;
   Float_t         lepton2_phi;
   Float_t         lepton2_eta;
   Float_t         lepton2_charge;
   Int_t           lepton2_truthType;
   Int_t           lepton2_truthOrigin;
   Int_t           lepton2_IFFType;
   Bool_t          lepton2_isPromptIFF;
   Float_t         lepton2_d0sig;
   Float_t         lepton2_z0sinTheta;
   Float_t         lepton2_d0;
   Float_t         lepton2_z0;
   Int_t           lepton2_isSig;
   Int_t           lepton2_isIso;
   Bool_t          lepton2_isMatched;
   Float_t         lepton2_truthE;
   Float_t         lepton2_truthpt;
   Float_t         lepton2_truthphi;
   Float_t         lepton2_trutheta;
   Int_t           lepton2_truthpdgid;
   Bool_t          lepton_singleleptrigMatched;
   Bool_t          lepton_dileptrigMatched;
   Float_t         jet1_pt;
   Float_t         jet1_phi;
   Float_t         jet1_eta;
   Float_t         jet1_E;
   Int_t           jet1_PartonTruthLabelID;
   Int_t           jet1_ConeTruthLabelID;
   Float_t         jet1_Jvt;
   Bool_t          jet1_btag_DL1dv01_FixedCutBEff_77;
   Float_t         mLepJet;
   Float_t         dRLepJet;
   Float_t         detaLepJet;
   Float_t         dphiLepJet;
   Float_t         LepOvermLepJet;
   Float_t         matched_mLepJet;
   Float_t         truth_mLepJet;
   Float_t         truth_dRLepJet;
   Float_t         mindphiJetMet;
   Float_t         dphiLepMet;
   Float_t         born_dilepton_m;
   Float_t         hardscatter_W_m;
   Float_t         dilepton_m;
   Float_t         dilepton_pt;
   Float_t         dilepton_phi;
   Float_t         dilepton_eta;
   Float_t         dilepton_DeltaR;
   Float_t         dilepton_DeltaEta;
   Float_t         dilepton_DeltaPhi;
   Float_t         dilepton_CosThetaStar;
   Float_t         mt_lep1;
   Float_t         mt_lep2;
   Float_t         jets_HT;
   Float_t         meff;

   //Truth tree

   // List of branches
   TBranch        *b_DFCommonJets_eventClean_LooseBad;   //!
   TBranch        *b_jet_ConeTruthLabelID;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_Jvt;   //!
   TBranch        *b_jet_PartonTruthLabelID;   //!
   TBranch        *b_jet_btag;   //!
   TBranch        *b_jet_btag_sf;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_truth_el_E;   //!
   TBranch        *b_truth_el_barcode;   //!
   TBranch        *b_truth_el_eta;   //!
   TBranch        *b_truth_el_parentID;   //!
   TBranch        *b_truth_el_pdgId;   //!
   TBranch        *b_truth_el_phi;   //!
   TBranch        *b_truth_el_pt;   //!
   TBranch        *b_truth_el_status;   //!
   TBranch        *b_truth_el_truthOrigin;   //!
   TBranch        *b_truth_el_truthType;   //!
   TBranch        *b_truth_jet_ConeTruthLabelID;   //!
   TBranch        *b_truth_jet_E;   //!
   TBranch        *b_truth_jet_Jvt;   //!
   TBranch        *b_truth_jet_PartonTruthLabelID;   //!
   TBranch        *b_truth_jet_eta;   //!
   TBranch        *b_truth_jet_phi;   //!
   TBranch        *b_truth_jet_pt;   //!
   TBranch        *b_truth_muon_E;   //!
   TBranch        *b_truth_muon_barcode;   //!
   TBranch        *b_truth_muon_eta;   //!
   TBranch        *b_truth_muon_parentID;   //!
   TBranch        *b_truth_muon_pdgId;   //!
   TBranch        *b_truth_muon_phi;   //!
   TBranch        *b_truth_muon_pt;   //!
   TBranch        *b_truth_muon_status;   //!
   TBranch        *b_truth_muon_truthOrigin;   //!
   TBranch        *b_truth_muon_truthType;   //!
   TBranch        *b_weight_norm;   //!
   TBranch        *b_weight_lumi;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_coreFlags;   //!
   TBranch        *b_bcid;   //!
   TBranch        *b_mcEventNumber;   //! MC
   TBranch        *b_mcChannelNumber;   //! MC
   TBranch        *b_NPV;   //!
   TBranch        *b_actualInteractionsPerCrossing;   //!
   TBranch        *b_averageInteractionsPerCrossing;   //!
   TBranch        *b_weight_pileup;   //!
   TBranch        *b_correctedAverageMu;   //!
   TBranch        *b_correctedAndScaledAverageMu;   //!
   TBranch        *b_correctedActualMu;   //!
   TBranch        *b_correctedAndScaledActualMu;   //!
   TBranch        *b_weight_pileup_up;   //!
   TBranch        *b_weight_pileup_down;   //!
   TBranch        *b_rand_run_nr;   //! MC
   TBranch        *b_rand_lumiblock_nr;   //! MC
   TBranch        *b_beamSpotWeight;   //!
   TBranch        *b_passL1;   //!
   TBranch        *b_passHLT;   //!
   TBranch        *b_ntruth_muon;   //!
   TBranch        *b_ntruth_el;   //!
   TBranch        *b_ntruth_jet;   //!
   TBranch        *b_njet;   //!
   TBranch        *b_metFinalTrk;   //!
   TBranch        *b_metFinalTrkPx;   //!
   TBranch        *b_metFinalTrkPy;   //!
   TBranch        *b_metFinalTrkSumEt;   //!
   TBranch        *b_metFinalTrkPhi;   //!
   TBranch        *b_metFinalTrkOverSqrtSumEt;   //!
   TBranch        *b_metFinalTrkOverSqrtHt;   //!
   TBranch        *b_metFinalTrkSignificance;   //!
   TBranch        *b_metFinalTrkSigDirectional;   //!
   TBranch        *b_metEle;   //!
   TBranch        *b_metEleSumEt;   //!
   TBranch        *b_metElePhi;   //!
   TBranch        *b_metMuons;   //!
   TBranch        *b_metMuonsSumEt;   //!
   TBranch        *b_metMuonsPhi;   //!
   TBranch        *b_metJet;   //!
   TBranch        *b_metJetSumEt;   //!
   TBranch        *b_metJetPhi;   //!
   TBranch        *b_metSoftTrk;   //!
   TBranch        *b_metSoftTrkSumEt;   //!
   TBranch        *b_metSoftTrkPhi;   //!
   TBranch        *b_HLT_j360;   //!
   TBranch        *b_HLT_j380;   //!
   TBranch        *b_HLT_j420;   //!
   TBranch        *b_HLT_j420_pf_ftf_preselj225_L1J100;   //!
   TBranch        *b_HLT_e24_lhmedium_L1EM20VH;   //!
   TBranch        *b_HLT_e60_lhmedium;   //!
   TBranch        *b_HLT_e120_lhloose;   //!
   TBranch        *b_HLT_e26_lhtight_nod0_ivarloose;   //!
   TBranch        *b_HLT_e60_lhmedium_nod0;   //!
   TBranch        *b_HLT_e140_lhloose_nod0;   //!
   TBranch        *b_HLT_e26_lhtight_ivarloose_L1EM22VHI;   //!
   TBranch        *b_HLT_e26_lhtight_ivarloose_L1eEM26M;   //!
   TBranch        *b_HLT_e60_lhmedium_L1EM22VHI;   //!
   TBranch        *b_HLT_e60_lhmedium_L1eEM26M;   //!
   TBranch        *b_HLT_e140_lhloose_L1EM22VHI;   //!
   TBranch        *b_HLT_e140_lhloose_L1eEM26M;   //!
   TBranch        *b_HLT_mu20_iloose_L1MU15;   //!
   TBranch        *b_HLT_mu26_ivarmedium;   //!
   TBranch        *b_HLT_mu50;   //!
   TBranch        *b_HLT_mu40;   //!
   TBranch        *b_HLT_mu24_ivarmedium_L1MU14FCH;   //!
   TBranch        *b_HLT_mu50_L1MU14FCH;   //!
   TBranch        *b_HLT_2e12_lhloose_L12EM10VH;   //!
   TBranch        *b_HLT_2e17_lhvloose_nod0;   //!
   TBranch        *b_HLT_2e24_lhvloose_nod0;   //!
   TBranch        *b_HLT_2e24_lhvloose_L12EM20VH;   //!
   TBranch        *b_HLT_2e24_lhvloose_L12eEM24L;   //!
   TBranch        *b_HLT_singleLep;   //!
   TBranch        *b_HLT_singleJet;   //!
   TBranch        *b_randomRunNumber;   //!
   TBranch        *b_datasetNumber;   //!
   TBranch        *b_year;   //!
   TBranch        *b_mcEventWeight;   //!
   TBranch        *b_sample_xSec;   //!
   TBranch        *b_sample_xSec_up_rel;   //!
   TBranch        *b_sample_xSec_down_rel;   //!
   TBranch        *b_sample_kFactor;   //!
   TBranch        *b_sample_filterEff;   //!
   TBranch        *b_weight_gen;   //!
   TBranch        *b_weight_lepton;   //!
   TBranch        *b_weight_jvt;   //!
   TBranch        *b_weight_btag;   //!
   TBranch        *b_weight_singleleptonTrigSF;   //!
   TBranch        *b_weight_dileptonTrigSF;   //!
   TBranch        *b_fakeweight;   //!
   TBranch        *b_n_truth_el;   //!
   TBranch        *b_n_truth_mu;   //!
   TBranch        *b_n_truth_lep;   //!
   TBranch        *b_n_el;   //!
   TBranch        *b_n_mu;   //!
   TBranch        *b_n_lep;   //!
   TBranch        *b_n_signal_el;   //!
   TBranch        *b_n_signal_mu;   //!
   TBranch        *b_n_signal_lep;   //!
   TBranch        *b_n_bjets;   //!
   TBranch        *b_lepton1_isEl;   //!
   TBranch        *b_lepton1_m;   //!
   TBranch        *b_lepton1_E;   //!
   TBranch        *b_lepton1_pt;   //!
   TBranch        *b_lepton1_phi;   //!
   TBranch        *b_lepton1_eta;   //!
   TBranch        *b_lepton1_charge;   //!
   TBranch        *b_lepton1_truthType;   //!
   TBranch        *b_lepton1_truthOrigin;   //!
   TBranch        *b_lepton1_IFFType;   //!
   TBranch        *b_lepton1_isPromptIFF;   //!
   TBranch        *b_lepton1_d0sig;   //!
   TBranch        *b_lepton1_z0sinTheta;   //!
   TBranch        *b_lepton1_d0;   //!
   TBranch        *b_lepton1_z0;   //!
   TBranch        *b_lepton1_isSig;   //!
   TBranch        *b_lepton1_isIso;   //!
   TBranch        *b_lepton1_isMatched;   //!
   TBranch        *b_lepton1_truthE;   //!
   TBranch        *b_lepton1_truthpt;   //!
   TBranch        *b_lepton1_truthphi;   //!
   TBranch        *b_lepton1_trutheta;   //!
   TBranch        *b_lepton1_truthpdgid;   //!
   TBranch        *b_lepton2_isEl;   //!
   TBranch        *b_lepton2_m;   //!
   TBranch        *b_lepton2_E;   //!
   TBranch        *b_lepton2_pt;   //!
   TBranch        *b_lepton2_phi;   //!
   TBranch        *b_lepton2_eta;   //!
   TBranch        *b_lepton2_charge;   //!
   TBranch        *b_lepton2_truthType;   //!
   TBranch        *b_lepton2_truthOrigin;   //!
   TBranch        *b_lepton2_IFFType;   //!
   TBranch        *b_lepton2_isPromptIFF;   //!
   TBranch        *b_lepton2_d0sig;   //!
   TBranch        *b_lepton2_z0sinTheta;   //!
   TBranch        *b_lepton2_d0;   //!
   TBranch        *b_lepton2_z0;   //!
   TBranch        *b_lepton2_isSig;   //!
   TBranch        *b_lepton2_isIso;   //!
   TBranch        *b_lepton2_isMatched;   //!
   TBranch        *b_lepton2_truthE;   //!
   TBranch        *b_lepton2_truthpt;   //!
   TBranch        *b_lepton2_truthphi;   //!
   TBranch        *b_lepton2_trutheta;   //!
   TBranch        *b_lepton2_truthpdgid;   //!
   TBranch        *b_lepton_singleleptrigMatched;   //!
   TBranch        *b_lepton_dileptrigMatched;   //!
   TBranch        *b_jet1_pt;   //!
   TBranch        *b_jet1_phi;   //!
   TBranch        *b_jet1_eta;   //!
   TBranch        *b_jet1_E;   //!
   TBranch        *b_jet1_PartonTruthLabelID;   //!
   TBranch        *b_jet1_ConeTruthLabelID;   //!
   TBranch        *b_jet1_Jvt;   //!
   TBranch        *b_jet1_btag_DL1dv01_FixedCutBEff_77;   //!
   TBranch        *b_mLepJet;   //!
   TBranch        *b_dRLepJet;   //!
   TBranch        *b_detaLepJet;   //!
   TBranch        *b_dphiLepJet;   //!
   TBranch        *b_LepOvermLepJet;   //!
   TBranch        *b_matched_mLepJet;   //!
   TBranch        *b_truth_mLepJet;   //!
   TBranch        *b_truth_dRLepJet;   //!
   TBranch        *b_mindphiJetMet;   //!
   TBranch        *b_dphiLepMet;   //!
   TBranch        *b_born_dilepton_m;   //!
   TBranch        *b_hardscatter_W_m;   //!
   TBranch        *b_dilepton_m;   //!
   TBranch        *b_dilepton_pt;   //!
   TBranch        *b_dilepton_phi;   //!
   TBranch        *b_dilepton_eta;   //!
   TBranch        *b_dilepton_DeltaR;   //!
   TBranch        *b_dilepton_DeltaEta;   //!
   TBranch        *b_dilepton_DeltaPhi;   //!
   TBranch        *b_dilepton_CosThetaStar;   //!
   TBranch        *b_mt_lep1;   //!
   TBranch        *b_mt_lep2;   //!
   TBranch        *b_jets_HT;   //!
   TBranch        *b_meff;   //!

   //Truth tree

   TreeForPreQBH();
   virtual ~TreeForPreQBH();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void CloseFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual TString GetRootType(TString RootName);
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

   TH2D* ElFakeEff;
   TH2D* MuFakeEff;
   TH2D* ElRealEff;
   TH2D* MuRealEff;
   TH2D* ElFakeTight;
   TH2D* ElFakeLoose;
   TH2D* MuFakeTight;
   TH2D* MuFakeLoose;
   TH2D* ElRealTight;
   TH2D* ElRealLoose;
   TH2D* MuRealTight;
   TH2D* MuRealLoose;
   virtual void GetFakeFactor();

   Logstream myLog;
   virtual void LinkLog(Logstream log){this->myLog = log;}
};

#endif

#ifdef TreeForPreQBH_cxx
void TreeForPreQBH::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   DFCommonJets_eventClean_LooseBad = 0;
   jet_ConeTruthLabelID = 0;
   jet_E = 0;
   jet_Jvt = 0;
   jet_PartonTruthLabelID = 0;
   jet_btag = 0;
   jet_btag_sf = 0;
   jet_eta = 0;
   jet_phi = 0;
   jet_pt = 0;
   truth_el_E = 0;
   truth_el_barcode = 0;
   truth_el_eta = 0;
   truth_el_parentID = 0;
   truth_el_pdgId = 0;
   truth_el_phi = 0;
   truth_el_pt = 0;
   truth_el_status = 0;
   truth_el_truthOrigin = 0;
   truth_el_truthType = 0;
   truth_jet_ConeTruthLabelID = 0;
   truth_jet_E = 0;
   truth_jet_Jvt = 0;
   truth_jet_PartonTruthLabelID = 0;
   truth_jet_eta = 0;
   truth_jet_phi = 0;
   truth_jet_pt = 0;
   truth_muon_E = 0;
   truth_muon_barcode = 0;
   truth_muon_eta = 0;
   truth_muon_parentID = 0;
   truth_muon_pdgId = 0;
   truth_muon_phi = 0;
   truth_muon_pt = 0;
   truth_muon_status = 0;
   truth_muon_truthOrigin = 0;
   truth_muon_truthType = 0;

}

#endif
