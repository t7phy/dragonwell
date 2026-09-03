//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 12 13:54:03 2020 by ROOT version 6.14/04
// from TTree Zeetree/Zeetree
// found on file: Zeetree.root
//////////////////////////////////////////////////////////

#ifndef ZPrime_TreeForZPrime_h
#define ZPrime_TreeForZPrime_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "TH1D.h"
#include "ZPrime/HistsZPrime.h"
#include "ZPrime/loopZPrime.h"
#include "ZPrime/TreeForPreZPrime.h"

class loopZPrime;
class HistsZPrime;
//class TreeForZPrime;

using namespace std;

class TreeForZPrime
{
 public:

   TFile *rootfile[1000];
   TTree *fChain[1000];
   long TotalEntries[1000];

   vector<TString> RootNames;
   vector<TString> RootTypes;
   vector<TString> subTypes;

   map<TString, int> SysNameIndex;
   TString SystematicName = "";
   TString SavedSystematicName = "";
   map<TString, double> Normalization;

   map<TString, TString> AdditionalWeightName;
   map<TString, Double_t> AdditionalWeight;
   map<TString, TBranch *> AdditionalWeightBranch;

   loopZPrime* fLoop;
   HistsZPrime* fHist;

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
   virtual void DefineTree(int isys, TString TreeName, TreeForPreZPrime* input);
   virtual void FillTree(int isys);
   //virtual void DefineTruthTree();
   //virtual void FillTruthTree();
   virtual void SaveFile();

// Fixed size dimensions of array or collections stored in the TTree if any.

   vector<int>     v_DFCommonJets_eventClean_LooseBad;
   vector<int>     v_jet_ConeTruthLabelID;
   vector<float>   v_jet_E;
   vector<float>   v_jet_Jvt;
   vector<int>     v_jet_PartonTruthLabelID;
   vector<bool>    v_jet_btag;
   vector<int>     v_jet_btag_score;
   vector<float>   v_jet_btag_sf;
   vector<float>   v_jet_eta;
   vector<char>    v_jet_isJvtHS;
   vector<float>   v_jet_phi;
   vector<float>   v_jet_pt;
   vector<int>     v_truth_jet_ConeTruthLabelID;
   vector<float>   v_truth_jet_E;
   vector<float>   v_truth_jet_Jvt;
   vector<int>     v_truth_jet_PartonTruthLabelID;
   vector<float>   v_truth_jet_eta;
   vector<float>   v_truth_jet_phi;
   vector<float>   v_truth_jet_pt;


   // Declaration of leaf types
   vector<int>     *DFCommonJets_eventClean_LooseBad;
   vector<int>     *jet_ConeTruthLabelID;
   vector<float>   *jet_E;
   vector<float>   *jet_Jvt;
   vector<int>     *jet_PartonTruthLabelID;
   vector<bool>    *jet_btag;
   vector<int>     *jet_btag_score;
   vector<float>   *jet_btag_sf;
   vector<float>   *jet_eta;
   vector<char>    *jet_isJvtHS;
   vector<float>   *jet_phi;
   vector<float>   *jet_pt;

   //signal sample
   vector<int>     *truth_jet_ConeTruthLabelID;
   vector<float>   *truth_jet_E;
   vector<float>   *truth_jet_Jvt;
   vector<int>     *truth_jet_PartonTruthLabelID;
   vector<float>   *truth_jet_eta;
   vector<float>   *truth_jet_phi;
   vector<float>   *truth_jet_pt;

   Float_t         weight_norm;
   Float_t         weight_lumi;
   Int_t           runNumber;
   Long64_t        eventNumber;
   Int_t           lumiBlock;
   UInt_t          coreFlags;
   Int_t           bcid;
   Int_t           NPV;
   Float_t         actualInteractionsPerCrossing;
   Float_t         averageInteractionsPerCrossing;
   Float_t         weight_pileup;
   Float_t         correctedAverageMu;
   Float_t         correctedAndScaledAverageMu;
   Float_t         correctedActualMu;
   Float_t         correctedAndScaledActualMu;

   //signal sample
   Float_t         weight_pileup_up;
   Float_t         weight_pileup_down;

   Float_t         beamSpotWeight;

   //signal sample
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
   Bool_t          HLT_e120_lhvloose_L1EM22VHI;
   Float_t         prescale_HLT_e120_lhvloose_L1EM22VHI;
   Bool_t          HLT_e100_lhvloose_L1EM22VHI;
   Float_t         prescale_HLT_e100_lhvloose_L1EM22VHI;
   Bool_t          HLT_e80_lhvloose_L1EM22VHI;
   Float_t         prescale_HLT_e80_lhvloose_L1EM22VHI;
   Bool_t          HLT_e60_lhvloose_L1EM22VHI;
   Float_t         prescale_HLT_e60_lhvloose_L1EM22VHI;
   Bool_t          HLT_e40_lhvloose_L1EM22VHI;
   Float_t         prescale_HLT_e40_lhvloose_L1EM22VHI;
   Bool_t          HLT_e30_lhvloose_L1EM22VHI;
   Float_t         prescale_HLT_e30_lhvloose_L1EM22VHI;
   Bool_t          HLT_e20_lhvloose_L1EM15VH;
   Float_t         prescale_HLT_e20_lhvloose_L1EM15VH;
   Bool_t          HLT_e120_lhvloose_L1eEM28M;
   Float_t         prescale_HLT_e120_lhvloose_L1eEM28M;
   Bool_t          HLT_e100_lhvloose_L1eEM28M;
   Float_t         prescale_HLT_e100_lhvloose_L1eEM28M;
   Bool_t          HLT_e80_lhvloose_L1eEM28M;
   Float_t         prescale_HLT_e80_lhvloose_L1eEM28M;
   Bool_t          HLT_e60_lhvloose_L1eEM28M;
   Float_t         prescale_HLT_e60_lhvloose_L1eEM28M;
   Bool_t          HLT_e40_lhvloose_L1eEM28M;
   Float_t         prescale_HLT_e40_lhvloose_L1eEM28M;
   Bool_t          HLT_e30_lhvloose_L1eEM28M;
   Float_t         prescale_HLT_e30_lhvloose_L1eEM28M;
   Bool_t          HLT_e20_lhvloose_L1eEM18L;
   Float_t         prescale_HLT_e20_lhvloose_L1eEM18L;

   //signal sample
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
   Float_t         mcEventWeight;
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
   Int_t           n_bjets_65;
   Int_t           n_bjets_70;
   Int_t           n_bjets_77;
   Int_t           n_bjets_85;
   Int_t           n_bjets_90;
   Int_t           n_bjets;
   Int_t           lepton1_isEl;
   Float_t         lepton1_m;
   Float_t         lepton1_E;
   Float_t         lepton1_pt;
   Float_t         lepton1_phi;
   Float_t         lepton1_eta;
   Float_t         lepton1_caloeta;
   Float_t         lepton1_charge;
   Int_t           lepton1_truthType;
   Int_t           lepton1_truthOrigin;
   Int_t           lepton1_IFFType;
   Bool_t          lepton1_isPromptIFF;
   Bool_t          lepton1_isIsoHighPtCaloOnly;
   Bool_t          lepton1_isIsoLoose_VarRad;
   Bool_t          lepton1_isIsoTight_VarRad;
   Bool_t          lepton1_isIDLoose;
   Bool_t          lepton1_isIDMedium;
   Bool_t          lepton1_isIDTight;
   Float_t         lepton1_RecoWeight;
   Float_t         lepton1_IsoHighPtCaloOnlyWeight;
   Float_t         lepton1_IsoLoose_VarRadWeight;
   Float_t         lepton1_IsoTight_VarRadWeight;
   Float_t         lepton1_IDLooseWeight;
   Float_t         lepton1_IDMediumWeight;
   Float_t         lepton1_IDTightWeight;
   Int_t           lepton1_ambiguityType;
   Int_t           lepton1_addAmbiguity;
   Float_t         lepton1_d0sig;
   Float_t         lepton1_z0sinTheta;
   Float_t         lepton1_d0;
   Float_t         lepton1_z0;
   Int_t           lepton1_isSig;
   Int_t           lepton1_isIso;
   Bool_t          lepton1_isTruthMatched;

   //signal sample
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
   Float_t         lepton2_caloeta;
   Float_t         lepton2_charge;
   Int_t           lepton2_truthType;
   Int_t           lepton2_truthOrigin;
   Int_t           lepton2_IFFType;
   Bool_t          lepton2_isPromptIFF;
   Bool_t          lepton2_isIsoHighPtCaloOnly;
   Bool_t          lepton2_isIsoLoose_VarRad;
   Bool_t          lepton2_isIsoTight_VarRad;
   Bool_t          lepton2_isIDLoose;
   Bool_t          lepton2_isIDMedium;
   Bool_t          lepton2_isIDTight;
   Float_t         lepton2_RecoWeight;
   Float_t         lepton2_IsoHighPtCaloOnlyWeight;
   Float_t         lepton2_IsoLoose_VarRadWeight;
   Float_t         lepton2_IsoTight_VarRadWeight;
   Float_t         lepton2_IDLooseWeight;
   Float_t         lepton2_IDMediumWeight;
   Float_t         lepton2_IDTightWeight;
   Int_t           lepton2_ambiguityType;
   Int_t           lepton2_addAmbiguity;
   Float_t         lepton2_d0sig;
   Float_t         lepton2_z0sinTheta;
   Float_t         lepton2_d0;
   Float_t         lepton2_z0;
   Int_t           lepton2_isSig;
   Int_t           lepton2_isIso;
   Bool_t          lepton2_isTruthMatched;

   //signal sample
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
   Bool_t          jet1_btag_65;
   Bool_t          jet1_btag_70;
   Bool_t          jet1_btag_77;
   Bool_t          jet1_btag_85;
   Bool_t          jet1_btag_90;
   Bool_t          jet1_btag;

   //signal sample
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

   Float_t         born_lepton1_E;
   Float_t         born_lepton1_pt;
   Float_t         born_lepton1_eta;
   Float_t         born_lepton1_phi;
   Float_t         born_lepton2_E;
   Float_t         born_lepton2_pt;
   Float_t         born_lepton2_eta;
   Float_t         born_lepton2_phi;
   Float_t         born_dilepton_m;
   Int_t           n_born_lepton;
   Int_t           n_truth_boson;
   Float_t         truth_boson_m;
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

   Int_t           passElTrigger;
   Int_t           passMuTrigger;







   Double_t        Weight_Lepton1_SF;
   Double_t        Weight_Lepton2_SF;
   Int_t           RunNumber;
   ULong64_t       EventNumber;
   Double_t        mcChannelNumber;
   Double_t        RecoDilRapidity;
   Double_t        RecoDilPhi;
   Double_t        RecoDilMass;
   Double_t        RecoPseudoDilMass;
   Double_t        RecoDilPt;
   Double_t        RecoPhiStar;
   Double_t        RecoCosThetaStar;
   Double_t        RecoWeight = 0.0;
   Double_t        RecoWeight_Stat_up = 0.0;
   Double_t        RecoWeight_Stat_down = 0.0;
   Double_t        RecoWeight_PromptSubtr_up = 0.0;
   Double_t        RecoWeight_PromptSubtr_down = 0.0;
   Double_t        RecoWeight_MET_up = 0.0;
   Double_t        RecoWeight_MET_down = 0.0;
   Double_t        RecoWeight_d0sig_up = 0.0;
   Double_t        RecoWeight_d0sig_down = 0.0;
   Double_t        RecoWeight_RealStat_up = 0.0;
   Double_t        RecoWeight_RealStat_down = 0.0;
   Double_t        RecoWeight_FourTerm_TT = 0.0;
   Double_t        RecoWeight_FourTerm_TL = 0.0;
   Double_t        RecoWeight_FourTerm_LT = 0.0;
   Double_t        RecoWeight_FourTerm_LL = 0.0;
   Bool_t          eeChannel = 0;
   Bool_t          mumuChannel = 0;
   Bool_t          emuChannel = 0;
   Bool_t          eeChannel_withmuon = 0;
   Bool_t          SingleElectron = 0;
   Double_t        TruthDilMass_Born;
   Double_t        TruthDilRapidity_Born;
   Double_t        Lepton1_Pt;
   Double_t        Lepton2_Pt;
   Double_t        Lepton3_Pt;
   Double_t        Lepton1_Phi;
   Double_t        Lepton2_Phi;
   Double_t        Lepton3_Phi;
   Double_t        Lepton1_Eta;
   Double_t        Lepton2_Eta;
   Double_t        Lepton3_Eta;
   Double_t        pTllReweight;
   Double_t        ChargeMisIDSFWeight;
   Double_t        ChargeIDSFWeight;
   Double_t        LeptonSFWeight;
   Double_t        PileupWeight;
   Double_t        TriggerSF;
   Int_t           n_Bjets;
   Double_t        MET_Et;
   Double_t        Lepton1_z0;
   Double_t        Lepton2_z0;
   Double_t        Lepton3_z0;
   Double_t        Lepton1_d0sig;
   Double_t        Lepton2_d0sig;
   Double_t        Lepton3_d0sig;
   Double_t        Lepton1_DeltaR;
   Double_t        Lepton2_DeltaR;
   Double_t        Mu;
   Double_t        MuActual;
   Double_t        PhiRF;
   Double_t        Weight_kFactor_Old;
   Double_t        Weight_kFactor_QCDEW;
   Double_t        Weight_kFactor_New_CT18NNLO;
   Double_t        Weight_kFactor_New_CT18ANNLO;
   Double_t        Weight_kFactor_PowhegtoSherpa;

   Double_t        Weight_indiv_SF_EL_ChargeMisID_STAT_UP;
   Double_t        Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN;
   Double_t        Weight_indiv_SF_EL_ChargeMisID_SYST_UP;
   Double_t        Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN;

   Double_t        Lepton_Pt_born;
   Double_t        AntiLepton_Pt_born;
   Double_t        Lepton_Eta_born;
   Double_t        AntiLepton_Eta_born;
   Double_t        Lepton_Phi_born;
   Double_t        AntiLepton_Phi_born;
   Double_t        Lepton_m_born;
   Double_t        AntiLepton_m_born;
   Double_t        Lepton_Pt_bare;
   Double_t        AntiLepton_Pt_bare;
   Double_t        Lepton_Eta_bare;
   Double_t        AntiLepton_Eta_bare;
   Double_t        Lepton_Phi_bare;
   Double_t        AntiLepton_Phi_bare;
   Double_t        Lepton_Pt_dressed;
   Double_t        Lepton_Eta_dressed;
   Double_t        Lepton_Phi_dressed;
   Double_t        Lepton_Charge_dressed;
   Double_t        AntiLepton_Pt_dressed;
   Double_t        AntiLepton_Eta_dressed;
   Double_t        AntiLepton_Phi_dressed;
   Double_t        AntiLepton_Charge_dressed;

   Bool_t          pass_ee_TT;
   Bool_t          pass_ee_TL;
   Bool_t          pass_ee_LT;
   Bool_t          pass_ee_LL;
   Bool_t          pass_mm_TT;
   Bool_t          pass_mm_TL;
   Bool_t          pass_mm_LT;
   Bool_t          pass_mm_LL;
   Int_t           Lepton1_isTight;
   Int_t           Lepton2_isTight;
   Int_t           Lepton3_isTight;
   Int_t           Lepton1_passMediumID;
   Int_t           Lepton2_passMediumID;
   Int_t           Lepton3_passMediumID;
   Int_t           Lepton1_passLooseID;
   Int_t           Lepton2_passLooseID;
   Int_t           Lepton3_passLooseID;
   Int_t           Lepton1_passIso;
   Int_t           Lepton2_passIso;
   Double_t        Lepton1_IsoWeight;
   Double_t        Lepton2_IsoWeight;

   Int_t           Lepton1_Charge;
   Int_t           Lepton2_Charge;
   Int_t           Lepton1_isTruthMatch;
   Int_t           Lepton2_isTruthMatch;
   Double_t        Lepton1_TightWeight;
   Double_t        Lepton2_TightWeight;
   Double_t        Lepton3_TightWeight;
   Double_t        Lepton1_LooseWeight;
   Double_t        Lepton2_LooseWeight;
   Double_t        Lepton3_LooseWeight;
   Double_t        Lepton1_MediumIDWeight;
   Double_t        Lepton2_MediumIDWeight;
   Double_t        PrescaleFactor;
   Double_t        Lepton1_PrescaleFactor;
   Double_t        Lepton2_PrescaleFactor;

   vector<int>     v_ele_isLHLoose;
   vector<int>     v_ele_isLHMedium;
   vector<int>     v_ele_isFixedCutTightIso;
   Double_t        RecoWeight_PromptSubtrUp = 0.0;
   Double_t        RecoWeight_PromptSubtrDown = 0.0;
   Double_t        RecoWeight_noW = 0.0;
   Double_t        RecoWeight_noDY = 0.0;
   Double_t        RecoWeight_noZMass = 0.0;
   Double_t        RecoWeight_StatsUp = 0.0;
   Double_t        RecoWeight_StatsDown = 0.0;
   Double_t        RecoWeight_CombineError = 0.0;
   Double_t        RecoWeight_matrix_1up = 0.0;
   Double_t        RecoWeight_matrix_1down = 0.0;
   Double_t        RecoWeight_stats_1up = 0.0;
   Double_t        RecoWeight_stats_1down = 0.0;
   Double_t        RecoWeight_d0Sig_1up = 0.0;
   Double_t        RecoWeight_d0Sig_1down = 0.0;

   Double_t        ReweightFactor_SSM_0p5TeV;
   Double_t        ReweightFactor_SSM_0p6TeV;
   Double_t        ReweightFactor_SSM_0p8TeV;
   Double_t        ReweightFactor_SSM_1TeV;
   Double_t        ReweightFactor_SSM_2TeV;
   Double_t        ReweightFactor_SSM_3TeV;
   Double_t        ReweightFactor_SSM_4TeV;
   Double_t        ReweightFactor_SSM_5TeV;
   Double_t        ReweightFactor_SSM_6TeV;
   Double_t        ReweightFactor_SSM_7TeV;
   Double_t        ReweightFactor_SSM_8TeV;

   Double_t        ReweightFactor_E6Chi_0p5TeV;
   Double_t        ReweightFactor_E6Chi_0p6TeV;
   Double_t        ReweightFactor_E6Chi_0p8TeV;
   Double_t        ReweightFactor_E6Chi_1TeV;
   Double_t        ReweightFactor_E6Chi_2TeV;
   Double_t        ReweightFactor_E6Chi_3TeV;
   Double_t        ReweightFactor_E6Chi_4TeV;
   Double_t        ReweightFactor_E6Chi_5TeV;
   Double_t        ReweightFactor_E6Chi_6TeV;
   Double_t        ReweightFactor_E6Chi_7TeV;
   Double_t        ReweightFactor_E6Chi_8TeV;

   Double_t        ReweightFactor_E6Psi_0p5TeV;
   Double_t        ReweightFactor_E6Psi_0p6TeV;
   Double_t        ReweightFactor_E6Psi_0p8TeV;
   Double_t        ReweightFactor_E6Psi_1TeV;
   Double_t        ReweightFactor_E6Psi_2TeV;
   Double_t        ReweightFactor_E6Psi_3TeV;
   Double_t        ReweightFactor_E6Psi_4TeV;
   Double_t        ReweightFactor_E6Psi_5TeV;
   Double_t        ReweightFactor_E6Psi_6TeV;
   Double_t        ReweightFactor_E6Psi_7TeV;
   Double_t        ReweightFactor_E6Psi_8TeV;

   Double_t        kfactor_nnlo;
   Double_t        kfactor_nnlo_up;
   Double_t        kfactor_nnlo_down;
   Double_t        kfactor_ew;

   // List of branches
   TBranch        *b_DFCommonJets_eventClean_LooseBad;   //!
   TBranch        *b_jet_ConeTruthLabelID;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_Jvt;   //!
   TBranch        *b_jet_PartonTruthLabelID;   //!
   TBranch        *b_jet_btag;   //!
   TBranch        *b_jet_btag_score;   //!
   TBranch        *b_jet_btag_sf;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_isJvtHS;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_pt;   //!

   //signal sample
   TBranch        *b_truth_jet_ConeTruthLabelID;   //!
   TBranch        *b_truth_jet_E;   //!
   TBranch        *b_truth_jet_Jvt;   //!
   TBranch        *b_truth_jet_PartonTruthLabelID;   //!
   TBranch        *b_truth_jet_eta;   //!
   TBranch        *b_truth_jet_phi;   //!
   TBranch        *b_truth_jet_pt;   //!

   TBranch        *b_weight_norm;   //!
   TBranch        *b_weight_lumi;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_coreFlags;   //!
   TBranch        *b_bcid;   //!
   TBranch        *b_NPV;   //!
   TBranch        *b_actualInteractionsPerCrossing;   //!
   TBranch        *b_averageInteractionsPerCrossing;   //!
   TBranch        *b_weight_pileup;   //!
   TBranch        *b_correctedAverageMu;   //!
   TBranch        *b_correctedAndScaledAverageMu;   //!
   TBranch        *b_correctedActualMu;   //!
   TBranch        *b_correctedAndScaledActualMu;   //!

   //signal sample
   TBranch        *b_weight_pileup_up;   //!
   TBranch        *b_weight_pileup_down;   //!

   TBranch        *b_beamSpotWeight;   //!

   //signal sample
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
   TBranch        *b_HLT_e120_lhvloose_L1EM22VHI;   //!
   TBranch        *b_prescale_HLT_e120_lhvloose_L1EM22VHI;   //!
   TBranch        *b_HLT_e100_lhvloose_L1EM22VHI;   //!
   TBranch        *b_prescale_HLT_e100_lhvloose_L1EM22VHI;   //!
   TBranch        *b_HLT_e80_lhvloose_L1EM22VHI;   //!
   TBranch        *b_prescale_HLT_e80_lhvloose_L1EM22VHI;   //!
   TBranch        *b_HLT_e60_lhvloose_L1EM22VHI;   //!
   TBranch        *b_prescale_HLT_e60_lhvloose_L1EM22VHI;   //!
   TBranch        *b_HLT_e40_lhvloose_L1EM22VHI;   //!
   TBranch        *b_prescale_HLT_e40_lhvloose_L1EM22VHI;   //!
   TBranch        *b_HLT_e30_lhvloose_L1EM22VHI;   //!
   TBranch        *b_prescale_HLT_e30_lhvloose_L1EM22VHI;   //!
   TBranch        *b_HLT_e20_lhvloose_L1EM15VH;   //!
   TBranch        *b_prescale_HLT_e20_lhvloose_L1EM15VH;   //!
   TBranch        *b_HLT_e120_lhvloose_L1eEM28M;   //!
   TBranch        *b_prescale_HLT_e120_lhvloose_L1eEM28M;   //!
   TBranch        *b_HLT_e100_lhvloose_L1eEM28M;   //!
   TBranch        *b_prescale_HLT_e100_lhvloose_L1eEM28M;   //!
   TBranch        *b_HLT_e80_lhvloose_L1eEM28M;   //!
   TBranch        *b_prescale_HLT_e80_lhvloose_L1eEM28M;   //!
   TBranch        *b_HLT_e60_lhvloose_L1eEM28M;   //!
   TBranch        *b_prescale_HLT_e60_lhvloose_L1eEM28M;   //!
   TBranch        *b_HLT_e40_lhvloose_L1eEM28M;   //!
   TBranch        *b_prescale_HLT_e40_lhvloose_L1eEM28M;   //!
   TBranch        *b_HLT_e30_lhvloose_L1eEM28M;   //!
   TBranch        *b_prescale_HLT_e30_lhvloose_L1eEM28M;   //!
   TBranch        *b_HLT_e20_lhvloose_L1eEM18L;   //!
   TBranch        *b_prescale_HLT_e20_lhvloose_L1eEM18L;   //!

   //signal sample
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
   TBranch        *b_n_bjets_65;   //!
   TBranch        *b_n_bjets_70;   //!
   TBranch        *b_n_bjets_77;   //!
   TBranch        *b_n_bjets_85;   //!
   TBranch        *b_n_bjets_90;   //!
   TBranch        *b_n_bjets;   //!
   TBranch        *b_lepton1_isEl;   //!
   TBranch        *b_lepton1_m;   //!
   TBranch        *b_lepton1_E;   //!
   TBranch        *b_lepton1_pt;   //!
   TBranch        *b_lepton1_phi;   //!
   TBranch        *b_lepton1_eta;   //!
   TBranch        *b_lepton1_caloeta;   //!
   TBranch        *b_lepton1_charge;   //!
   TBranch        *b_lepton1_truthType;   //!
   TBranch        *b_lepton1_truthOrigin;   //!
   TBranch        *b_lepton1_IFFType;   //!
   TBranch        *b_lepton1_isPromptIFF;   //!
   TBranch        *b_lepton1_isIsoHighPtCaloOnly;   //!
   TBranch        *b_lepton1_isIsoLoose_VarRad;   //!
   TBranch        *b_lepton1_isIsoTight_VarRad;   //!
   TBranch        *b_lepton1_isIDLoose;   //!
   TBranch        *b_lepton1_isIDMedium;   //!
   TBranch        *b_lepton1_isIDTight;   //!
   TBranch        *b_lepton1_RecoWeight;   //!
   TBranch        *b_lepton1_IsoHighPtCaloOnlyWeight;   //!
   TBranch        *b_lepton1_IsoLoose_VarRadWeight;   //!
   TBranch        *b_lepton1_IsoTight_VarRadWeight;   //!
   TBranch        *b_lepton1_IDLooseWeight;   //!
   TBranch        *b_lepton1_IDMediumWeight;   //!
   TBranch        *b_lepton1_IDTightWeight;   //!
   TBranch        *b_lepton1_ambiguityType;   //!
   TBranch        *b_lepton1_addAmbiguity;   //!
   TBranch        *b_lepton1_d0sig;   //!
   TBranch        *b_lepton1_z0sinTheta;   //!
   TBranch        *b_lepton1_d0;   //!
   TBranch        *b_lepton1_z0;   //!
   TBranch        *b_lepton1_isSig;   //!
   TBranch        *b_lepton1_isIso;   //!
   TBranch        *b_lepton1_isTruthMatched;   //!

   //signal sample
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
   TBranch        *b_lepton2_caloeta;   //!
   TBranch        *b_lepton2_charge;   //!
   TBranch        *b_lepton2_truthType;   //!
   TBranch        *b_lepton2_truthOrigin;   //!
   TBranch        *b_lepton2_IFFType;   //!
   TBranch        *b_lepton2_isPromptIFF;   //!
   TBranch        *b_lepton2_isIsoHighPtCaloOnly;   //!
   TBranch        *b_lepton2_isIsoLoose_VarRad;   //!
   TBranch        *b_lepton2_isIsoTight_VarRad;   //!
   TBranch        *b_lepton2_isIDLoose;   //!
   TBranch        *b_lepton2_isIDMedium;   //!
   TBranch        *b_lepton2_isIDTight;   //!
   TBranch        *b_lepton2_RecoWeight;   //!
   TBranch        *b_lepton2_IsoHighPtCaloOnlyWeight;   //!
   TBranch        *b_lepton2_IsoLoose_VarRadWeight;   //!
   TBranch        *b_lepton2_IsoTight_VarRadWeight;   //!
   TBranch        *b_lepton2_IDLooseWeight;   //!
   TBranch        *b_lepton2_IDMediumWeight;   //!
   TBranch        *b_lepton2_IDTightWeight;   //!
   TBranch        *b_lepton2_ambiguityType;   //!
   TBranch        *b_lepton2_addAmbiguity;   //!
   TBranch        *b_lepton2_d0sig;   //!
   TBranch        *b_lepton2_z0sinTheta;   //!
   TBranch        *b_lepton2_d0;   //!
   TBranch        *b_lepton2_z0;   //!
   TBranch        *b_lepton2_isSig;   //!
   TBranch        *b_lepton2_isIso;   //!
   TBranch        *b_lepton2_isTruthMatched;   //!

   //signal sample
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
   TBranch        *b_jet1_btag_65;   //!
   TBranch        *b_jet1_btag_70;   //!
   TBranch        *b_jet1_btag_77;   //!
   TBranch        *b_jet1_btag_85;   //!
   TBranch        *b_jet1_btag_90;   //!
   TBranch        *b_jet1_btag;   //!

   //signal sample
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

   TBranch        *b_born_lepton1_E;   //!
   TBranch        *b_born_lepton1_pt;   //!
   TBranch        *b_born_lepton1_eta;   //!
   TBranch        *b_born_lepton1_phi;   //!
   TBranch        *b_born_lepton2_E;   //!
   TBranch        *b_born_lepton2_pt;   //!
   TBranch        *b_born_lepton2_eta;   //!
   TBranch        *b_born_lepton2_phi;   //!
   TBranch        *b_born_dilepton_m;   //!
   TBranch        *b_n_born_lepton;   //!
   TBranch        *b_n_truth_boson;   //!
   TBranch        *b_truth_boson_m;   //!
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

   TBranch        *b_passElTrigger;   //!
   TBranch        *b_passMuTrigger;   //!







   TBranch        *b_Weight_Lepton1_SF;   //!
   TBranch        *b_Weight_Lepton2_SF;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_RecoDilRapidity;   //!
   TBranch        *b_RecoDilPhi;   //!
   TBranch        *b_RecoDilMass;   //!
   TBranch        *b_RecoPseudoDilMass;   //!
   TBranch        *b_RecoDilPt;   //!
   TBranch        *b_RecoPhiStar;   //!
   TBranch        *b_RecoCosThetaStar;   //!
   TBranch        *b_RecoWeight;   //!
   TBranch        *b_RecoWeight_Stat_up;   //!
   TBranch        *b_RecoWeight_Stat_down;   //!
   TBranch        *b_RecoWeight_PromptSubtr_up;   //!
   TBranch        *b_RecoWeight_PromptSubtr_down;   //!
   TBranch        *b_RecoWeight_MET_up;   //!
   TBranch        *b_RecoWeight_MET_down;   //!
   TBranch        *b_RecoWeight_d0sig_up;   //!
   TBranch        *b_RecoWeight_d0sig_down;   //!
   TBranch        *b_RecoWeight_RealStat_up;   //!
   TBranch        *b_RecoWeight_RealStat_down;   //!
   TBranch        *b_RecoWeight_FourTerm_TT;   //!
   TBranch        *b_RecoWeight_FourTerm_TL;   //!
   TBranch        *b_RecoWeight_FourTerm_LT;   //!
   TBranch        *b_RecoWeight_FourTerm_LL;   //!
   TBranch        *b_eeChannel;   //!
   TBranch        *b_mumuChannel;   //!
   TBranch        *b_emuChannel;   //!
   TBranch        *b_eeChannel_withmuon;   //!
   TBranch        *b_SingleElectron;   //!
   TBranch        *b_TruthDilMass_Born;   //!
   TBranch        *b_TruthDilRapidity_Born;   //!
   TBranch        *b_Lepton1_Pt;   //!
   TBranch        *b_Lepton2_Pt;   //!
   TBranch        *b_Lepton3_Pt;   //!
   TBranch        *b_Lepton1_Phi;   //!
   TBranch        *b_Lepton2_Phi;   //!
   TBranch        *b_Lepton3_Phi;   //!
   TBranch        *b_Lepton1_Eta;   //!
   TBranch        *b_Lepton2_Eta;   //!
   TBranch        *b_Lepton3_Eta;   //!
   TBranch        *b_pTllReweight;   //!
   TBranch        *b_ChargeMisIDSFWeight;   //!
   TBranch        *b_ChargeIDSFWeight;   //!
   TBranch        *b_LeptonSFWeight;   //!
   TBranch        *b_PileupWeight;   //!
   TBranch        *b_TriggerSF;   //!
   TBranch        *b_n_Bjets;   //!
   TBranch        *b_MET_Et;   //!
   TBranch        *b_Lepton1_z0;   //!
   TBranch        *b_Lepton2_z0;   //!
   TBranch        *b_Lepton3_z0;   //!
   TBranch        *b_Lepton1_d0sig;   //!
   TBranch        *b_Lepton2_d0sig;   //!
   TBranch        *b_Lepton3_d0sig;   //!
   TBranch        *b_Lepton1_DeltaR;   //!
   TBranch        *b_Lepton2_DeltaR;   //!
   TBranch        *b_Mu;   //!
   TBranch        *b_MuActual;   //!
   TBranch        *b_PhiRF;   //!
   TBranch        *b_Weight_kFactor_Old;   //!
   TBranch        *b_Weight_kFactor_QCDEW;   //!
   TBranch        *b_Weight_kFactor_New_CT18NNLO;   //!
   TBranch        *b_Weight_kFactor_New_CT18ANNLO;   //!
   TBranch        *b_Weight_kFactor_PowhegtoSherpa;   //!

   TBranch        *b_Weight_indiv_SF_EL_ChargeMisID_STAT_UP;   //!
   TBranch        *b_Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN;   //!
   TBranch        *b_Weight_indiv_SF_EL_ChargeMisID_SYST_UP;   //!
   TBranch        *b_Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN;   //!

   TBranch        *b_Lepton_Pt_born;   //!
   TBranch        *b_AntiLepton_Pt_born;   //!
   TBranch        *b_Lepton_Eta_born;   //!
   TBranch        *b_AntiLepton_Eta_born;   //!
   TBranch        *b_Lepton_Phi_born;   //!
   TBranch        *b_AntiLepton_Phi_born;   //!
   TBranch        *b_Lepton_m_born;   //!
   TBranch        *b_AntiLepton_m_born;   //!
   TBranch        *b_Lepton_Pt_bare;   //!
   TBranch        *b_AntiLepton_Pt_bare;   //!
   TBranch        *b_Lepton_Eta_bare;   //!
   TBranch        *b_AntiLepton_Eta_bare;   //!
   TBranch        *b_Lepton_Phi_bare;   //!
   TBranch        *b_AntiLepton_Phi_bare;   //!
   TBranch        *b_Lepton_Pt_dressed;   //!
   TBranch        *b_Lepton_Eta_dressed;   //!
   TBranch        *b_Lepton_Phi_dressed;   //!
   TBranch        *b_Lepton_Charge_dressed;   //!
   TBranch        *b_AntiLepton_Pt_dressed;   //!
   TBranch        *b_AntiLepton_Eta_dressed;   //!
   TBranch        *b_AntiLepton_Phi_dressed;   //!
   TBranch        *b_AntiLepton_Charge_dressed;   //!

   TBranch        *b_pass_ee_TT;   //!
   TBranch        *b_pass_ee_TL;   //!
   TBranch        *b_pass_ee_LT;   //!
   TBranch        *b_pass_ee_LL;   //!
   TBranch        *b_pass_mm_TT;   //!
   TBranch        *b_pass_mm_TL;   //!
   TBranch        *b_pass_mm_LT;   //!
   TBranch        *b_pass_mm_LL;   //!
   TBranch        *b_Lepton1_isTight;   //!
   TBranch        *b_Lepton2_isTight;   //!
   TBranch        *b_Lepton3_isTight;   //!
   TBranch        *b_Lepton1_passMediumID;   //!
   TBranch        *b_Lepton2_passMediumID;   //!
   TBranch        *b_Lepton3_passMediumID;   //!
   TBranch        *b_Lepton1_passLooseID;   //!
   TBranch        *b_Lepton2_passLooseID;   //!
   TBranch        *b_Lepton3_passLooseID;   //!
   TBranch        *b_Lepton1_passIso;   //!
   TBranch        *b_Lepton2_passIso;   //!
   TBranch        *b_Lepton1_IsoWeight;   //!
   TBranch        *b_Lepton2_IsoWeight;   //!

   TBranch        *b_Lepton1_Charge;   //!
   TBranch        *b_Lepton2_Charge;   //!
   TBranch        *b_Lepton1_isTruthMatch;   //!
   TBranch        *b_Lepton2_isTruthMatch;   //!
   TBranch        *b_Lepton1_TightWeight;   //!
   TBranch        *b_Lepton2_TightWeight;   //!
   TBranch        *b_Lepton3_TightWeight;   //!
   TBranch        *b_Lepton1_LooseWeight;   //!
   TBranch        *b_Lepton2_LooseWeight;   //!
   TBranch        *b_Lepton3_LooseWeight;   //!
   TBranch        *b_Lepton1_MediumIDWeight;   //!
   TBranch        *b_Lepton2_MediumIDWeight;   //!
   TBranch        *b_PrescaleFactor;   //!
   TBranch        *b_Lepton1_PrescaleFactor;   //!
   TBranch        *b_Lepton2_PrescaleFactor;   //!

   TBranch        *b_RecoWeight_PromptSubtrUp;   //!
   TBranch        *b_RecoWeight_PromptSubtrDown;   //!
   TBranch        *b_RecoWeight_noW;   //!
   TBranch        *b_RecoWeight_noDY;   //!
   TBranch        *b_RecoWeight_noZMass;   //!
   TBranch        *b_RecoWeight_StatsUp;   //!
   TBranch        *b_RecoWeight_StatsDown;   //!
   TBranch        *b_RecoWeight_CombineError;   //!
   TBranch        *b_RecoWeight_matrix_1up;   //!
   TBranch        *b_RecoWeight_matrix_1down;   //!
   TBranch        *b_RecoWeight_stats_1up;   //!
   TBranch        *b_RecoWeight_stats_1down;   //!
   TBranch        *b_RecoWeight_d0Sig_1up;   //!
   TBranch        *b_RecoWeight_d0Sig_1down;   //!

   TreeForZPrime();
   virtual ~TreeForZPrime();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void CloseFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual TString GetRootType(TString RootName);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void LinkHist(HistsZPrime* myhists);
   virtual void Init();

   virtual void InputSystematic(TString sysName);
   virtual void SystematicSelection(TString sysName, TString AdditionalSelection = "");
   virtual void BkgSelection(TString name);

   virtual void updateCutFlow(TH1D *inCutFlow, std::map<std::string, double> *inLabelMap, std::string cutName, double step = 1, bool doUpdate = true); //!
};

#endif


