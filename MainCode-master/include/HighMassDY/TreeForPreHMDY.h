//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 16 03:49:58 2024 by ROOT version 6.20/06
// from TTree nominal/nominal
// found on file: LJSkim_v6.0_file_Run3_data_merged.root
//////////////////////////////////////////////////////////

#ifndef TreeForPreHMDY_h
#define TreeForPreHMDY_h

#include "RootCommon.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "Tools/Tools.h"

using namespace std;

class TreeForPreHMDY
{
 public :
   bool isData = false;

   TFile *rootfile[1000];
   TTree *fChain[1000];
   long TotalEntries[1000];

   vector<TString> RootNames;

   vector<TString> RootTypes;
   vector<double> CrossSections;
   vector<double> SumOfWeights;
   vector<int> Years;
   vector<int> DSIDs;
   bool isLooseTree = true;
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
   ULong64_t       eventNumber;
   UInt_t          runNumber;
   UInt_t          randomRunNumber;
   UInt_t          mcChannelNumber;
   Float_t         mu;
   Float_t         mu_actual;
   Float_t         mu_original_xAOD;
   Float_t         mu_actual_original_xAOD;
   UInt_t          backgroundFlags;
   UInt_t          hasBadMuon;
   vector<float>   *el_pt;
   vector<float>   *el_eta;
   vector<float>   *el_cl_eta;
   vector<float>   *el_phi;
   vector<float>   *el_e;
   vector<float>   *el_charge;
   vector<float>   *el_topoetcone20;
   vector<float>   *el_ptvarcone20;
   vector<char>    *el_isTight;
   vector<char>    *el_CF;
   vector<float>   *el_d0sig;
   vector<float>   *el_delta_z0_sintheta;
   vector<float>   *mu_pt;
   vector<float>   *mu_eta;
   vector<float>   *mu_phi;
   vector<float>   *mu_e;
   vector<float>   *mu_charge;
   vector<float>   *mu_topoetcone20;
   vector<float>   *mu_ptvarcone30;
   vector<char>    *mu_isTight;
   vector<float>   *mu_d0sig;
   vector<float>   *mu_delta_z0_sintheta;
   vector<float>   *jet_pt;
   vector<float>   *jet_eta;
   vector<float>   *jet_phi;
   vector<float>   *jet_e;
   vector<float>   *jet_jvt;
   Float_t         met_met;
   Float_t         met_phi;
   Int_t           mumuSelection;
   Int_t           emu;
   Int_t           eeSelection;
   Int_t           eeSelection_withmuon;
   Int_t           SingleElectron;
   // Data15
   Char_t          HLT_mu50;
   Char_t          HLT_2mu10;
   Char_t          HLT_mu18_mu8noL1;
   Char_t          HLT_2e12_lhloose_L12EM10VH;
   Char_t          HLT_e120_lhloose;
   Char_t          HLT_mu20_iloose_L1MU15;
   Char_t          HLT_e24_lhmedium_L1EM20VH;
   Char_t          HLT_e60_lhmedium;
   vector<char>    *el_trigMatch_HLT_e60_lhmedium;
   vector<char>    *el_trigMatch_HLT_e120_lhloose;
   vector<char>    *el_trigMatch_HLT_e24_lhmedium_L1EM20VH;
   vector<char>    *mu_trigMatch_HLT_mu50;
   vector<char>    *mu_trigMatch_HLT_mu18_mu8noL1;
   vector<char>    *mu_trigMatch_HLT_mu20_iloose_L1MU15;
   // Data16
   Char_t          HLT_mu26_ivarmedium;
   Char_t          HLT_2mu14;
   Char_t          HLT_2e17_lhvloose_nod0;
   Char_t          HLT_e120_lhvloose_nod0;
   Char_t          HLT_e140_lhloose_nod0;
   Char_t          HLT_e140_lhvloose_nod0;
   Char_t          HLT_e26_lhtight_nod0_ivarloose;
   Char_t          HLT_e60_lhmedium_nod0;
   Char_t          HLT_mu22_mu8noL1;
   vector<char>    *el_trigMatch_HLT_e60_lhmedium_nod0;
   vector<char>    *el_trigMatch_HLT_e140_lhloose_nod0;
   vector<char>    *el_trigMatch_HLT_e26_lhtight_nod0_ivarloose;
   vector<char>    *mu_trigMatch_HLT_mu22_mu8noL1;
   vector<char>    *mu_trigMatch_HLT_mu26_ivarmedium;
   // Data17
   Char_t          HLT_2e24_lhvloose_nod0;
   Char_t          HLT_e60_lhvloose_nod0;
   Char_t          HLT_e300_etcut;
   Char_t          HLT_e26_lhvloose_nod0_L1EM20VH;
   Char_t          HLT_e26_lhvloose_nod0_L1EM22VH;
   Char_t          HLT_e200_etcut;
   // Data18
   Char_t          HLT_2e17_lhvloose_nod0_L12EM15VHI;

   vector<char>    *el_trigMatch_HLT_e26_lhvloose_nod0_L1EM20VH;
   vector<char>    *el_trigMatch_HLT_e26_lhvloose_nod0_L1EM22VH;
   vector<char>    *el_trigMatch_HLT_e60_lhvloose_nod0;
   vector<char>    *el_trigMatch_HLT_e120_lhvloose_nod0;
   vector<char>    *el_trigMatch_HLT_e140_lhvloose_nod0;
   vector<char>    *el_trigMatch_HLT_e200_etcut;
   vector<char>    *el_trigMatch_HLT_e300_etcut;

   Double_t        weight_KFactor;
   vector<bool>    *mu_isMedium;
   vector<bool>    *mu_isHighPt;
   vector<float>   *mu_PtID;
   vector<float>   *mu_PtMS;
   vector<bool>    *mu_isolation_FixedCutTight;
   vector<bool>    *mu_isolation_FixedCutLoose;
   vector<bool>    *mu_isolation_FixedCutPflowTight;
   vector<bool>    *mu_isolation_FixedCutPflowLoose;
   vector<bool>    *mu_isolation_FCTightTrackOnly_FixedRad;
   vector<bool>    *mu_isolation_TightTrackOnly_VarRad;
   vector<bool>    *el_isolation_FixedCutLoose;
   vector<bool>    *el_isolation_FixedCutTight;
   vector<bool>    *el_isolation_PflowTight;
   vector<bool>    *el_isolation_TightTrackOnly;
   vector<bool>    *el_isolation_TightTrackOnly_FixedRad;
   vector<bool>    *el_isElTight;
   vector<float>   *el_SF_Reco;
   vector<float>   *el_SF_Reco_Corr;
   vector<float>   *el_SF_ID_LooseAndBLayerLH;
   vector<float>   *el_SF_ID_MediumLH;
   vector<float>   *el_SF_Iso_FCTight;
   vector<float>   *mu_SF_TTVA;
   vector<float>   *mu_SF_ID_HighPt;
   vector<float>   *mu_SF_ID_Loose;
   vector<float>   *mu_SF_ID_Medium;
   vector<float>   *mu_SF_Iso_FCTightTrackOnly_FixedRad;
   vector<float>   *mu_SF_Iso_TightTrackOnly_VarRad;
   vector<bool>    *fwdel_isTight;
   vector<bool>    *fwdel_isMedium;
   vector<bool>    *fwdel_isLoose;
   vector<bool>    *el_isElMedium;
   vector<bool>    *el_isElLoose;
   vector<bool>    *el_DFCommonElectronsECIDS;
   vector<double>  *el_DFCommonElectronsECIDSResult;
   vector<float>   *el_isPromptLepton;
   Float_t         weight_mc;
   Float_t         weight_pileup;
   Float_t         weight_leptonSF;
   Float_t         weight_globalLeptonTriggerSF = 1.0;
   Float_t         weight_jvt;
   Float_t         weight_pileup_UP;
   Float_t         weight_pileup_DOWN;
   Float_t         weight_indiv_SF_EL_ChargeMisID;
   Float_t         weight_indiv_SF_EL_ChargeMisID_STAT_UP;
   Float_t         weight_indiv_SF_EL_ChargeMisID_STAT_DOWN;
   Float_t         weight_indiv_SF_EL_ChargeMisID_SYST_UP;
   Float_t         weight_indiv_SF_EL_ChargeMisID_SYST_DOWN;
   Float_t         Lepton_Pt_born;
   Float_t         AntiLepton_Pt_born;
   Float_t         Lepton_Eta_born;
   Float_t         AntiLepton_Eta_born;
   Float_t         Lepton_Phi_born;
   Float_t         AntiLepton_Phi_born;
   Float_t         Lepton_m_born;
   Float_t         AntiLepton_m_born;
   Float_t         Lepton_Pt_bare;
   Float_t         AntiLepton_Pt_bare;
   Float_t         Lepton_Eta_bare;
   Float_t         AntiLepton_Eta_bare;
   Float_t         Lepton_Phi_bare;
   Float_t         AntiLepton_Phi_bare;
   Float_t         Lepton_Pt_dressed;
   Float_t         Lepton_Eta_dressed;
   Float_t         Lepton_Phi_dressed;
   Float_t         Lepton_Charge_dressed;
   Float_t         AntiLepton_Pt_dressed;
   Float_t         AntiLepton_Eta_dressed;
   Float_t         AntiLepton_Phi_dressed;
   Float_t         AntiLepton_Charge_dressed;
   Float_t         Dilepton_Pt_born;
   Float_t         Dilepton_Rapidity_born;
   Float_t         Dilepton_Eta_born;
   Float_t         Dilepton_Phi_born;
   Float_t         Dilepton_Mass_born;

   Float_t         PS_HLT_e26_lhvloose_nod0_L1EM20VH;
   Float_t         PS_HLT_e26_lhvloose_nod0_L1EM22VH;
   Float_t         PS_HLT_e60_lhvloose_nod0;
   Float_t         PS_HLT_e200_etcut;
   Float_t         PS_HLT_e120_lhvloose_nod0;
   Float_t         PS_HLT_e140_lhvloose_nod0;
   Float_t         PS_HLT_e300_etcut;


   //Truth tree

   // List of branches
   TBranch        *b_eventNumber;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_randomRunNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_mu_actual;   //!
   TBranch        *b_mu_original_xAOD;   //!
   TBranch        *b_mu_actual_original_xAOD;   //!
   TBranch        *b_backgroundFlags;   //!
   TBranch        *b_hasBadMuon;   //!
   TBranch        *b_el_pt;   //!
   TBranch        *b_el_eta;   //!
   TBranch        *b_el_cl_eta;   //!
   TBranch        *b_el_phi;   //!
   TBranch        *b_el_e;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_topoetcone20;   //!
   TBranch        *b_el_ptvarcone20;   //!
   TBranch        *b_el_isTight;   //!
   TBranch        *b_el_CF;   //!
   TBranch        *b_el_d0sig;   //!
   TBranch        *b_el_delta_z0_sintheta;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_e;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_topoetcone20;   //!
   TBranch        *b_mu_ptvarcone30;   //!
   TBranch        *b_mu_isTight;   //!
   TBranch        *b_mu_d0sig;   //!
   TBranch        *b_mu_delta_z0_sintheta;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_e;   //!
   TBranch        *b_jet_jvt;   //!
   TBranch        *b_met_met;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_mumuSelection;   //!
   TBranch        *b_emu;   //!
   TBranch        *b_eeSelection;   //!
   TBranch        *b_eeSelection_withmuon;   //!
   TBranch        *b_SingleElectron;   //!

   // Data15
   TBranch        *b_HLT_mu50;   //!
   TBranch        *b_HLT_2mu10;   //!
   TBranch        *b_HLT_mu18_mu8noL1;   //!
   TBranch        *b_HLT_2e12_lhloose_L12EM10VH;   //!
   TBranch        *b_HLT_e120_lhloose;   //!
   TBranch        *b_HLT_mu20_iloose_L1MU15;   //!
   TBranch        *b_HLT_e24_lhmedium_L1EM20VH;   //!
   TBranch        *b_HLT_e60_lhmedium;   //!
   TBranch        *b_el_trigMatch_HLT_e60_lhmedium;   //!
   TBranch        *b_el_trigMatch_HLT_e120_lhloose;   //!
   TBranch        *b_el_trigMatch_HLT_e24_lhmedium_L1EM20VH;   //!
   TBranch        *b_mu_trigMatch_HLT_mu50;   //!
   TBranch        *b_mu_trigMatch_HLT_mu18_mu8noL1;   //!
   TBranch        *b_mu_trigMatch_HLT_mu20_iloose_L1MU15;   //!
   // Data16
   TBranch        *b_HLT_mu26_ivarmedium;   //!
   TBranch        *b_HLT_2mu14;   //!
   TBranch        *b_HLT_2e17_lhvloose_nod0;   //!
   TBranch        *b_HLT_e140_lhloose_nod0;   //!
   TBranch        *b_HLT_e140_lhvloose_nod0;   //!
   TBranch        *b_HLT_e26_lhtight_nod0_ivarloose;   //!
   TBranch        *b_HLT_e60_lhmedium_nod0;   //!
   TBranch        *b_HLT_mu22_mu8noL1;   //!
   TBranch        *b_el_trigMatch_HLT_e60_lhmedium_nod0;   //!
   TBranch        *b_el_trigMatch_HLT_e140_lhloose_nod0;   //!
   TBranch        *b_el_trigMatch_HLT_e26_lhtight_nod0_ivarloose;   //!
   TBranch        *b_mu_trigMatch_HLT_mu22_mu8noL1;   //!
   TBranch        *b_mu_trigMatch_HLT_mu26_ivarmedium;   //!
   // Data17
   TBranch        *b_HLT_2e24_lhvloose_nod0;   //!
   TBranch        *b_HLT_e60_lhvloose_nod0;   //!
   TBranch        *b_HLT_e300_etcut;   //!
   TBranch        *b_HLT_e120_lhvloose_nod0;   //!
   TBranch        *b_HLT_e26_lhvloose_nod0_L1EM20VH;   //!
   TBranch        *b_HLT_e26_lhvloose_nod0_L1EM22VH;   //!
   TBranch        *b_HLT_e200_etcut;   //!
   // Data18
   TBranch        *b_HLT_2e17_lhvloose_nod0_L12EM15VHI;   //!

   TBranch        *b_el_trigMatch_HLT_e26_lhvloose_nod0_L1EM20VH;   //!
   TBranch        *b_el_trigMatch_HLT_e26_lhvloose_nod0_L1EM22VH;   //!
   TBranch        *b_el_trigMatch_HLT_e60_lhvloose_nod0;   //!
   TBranch        *b_el_trigMatch_HLT_e120_lhvloose_nod0;   //!
   TBranch        *b_el_trigMatch_HLT_e140_lhvloose_nod0;   //!
   TBranch        *b_el_trigMatch_HLT_e200_etcut;   //!
   TBranch        *b_el_trigMatch_HLT_e300_etcut;   //!

   TBranch        *b_weight_KFactor;   //!
   TBranch        *b_mu_isMedium;   //!
   TBranch        *b_mu_isHighPt;   //!
   TBranch        *b_mu_PtID;   //!
   TBranch        *b_mu_PtMS;   //!
   TBranch        *b_mu_isolation_FixedCutTight;   //!
   TBranch        *b_mu_isolation_FixedCutLoose;   //!
   TBranch        *b_mu_isolation_FixedCutPflowTight;   //!
   TBranch        *b_mu_isolation_FixedCutPflowLoose;   //!
   TBranch        *b_mu_isolation_FCTightTrackOnly_FixedRad;   //!
   TBranch        *b_mu_isolation_TightTrackOnly_VarRad;   //!
   TBranch        *b_el_isolation_FixedCutLoose;   //!
   TBranch        *b_el_isolation_FixedCutTight;   //!
   TBranch        *b_el_isolation_PflowTight;   //!
   TBranch        *b_el_isolation_TightTrackOnly;   //!
   TBranch        *b_el_isolation_TightTrackOnly_FixedRad;   //!
   TBranch        *b_el_isElTight;   //!
   TBranch        *b_el_SF_Reco;   //!
   TBranch        *b_el_SF_Reco_Corr;   //!
   TBranch        *b_el_SF_ID_LooseAndBLayerLH;   //!
   TBranch        *b_el_SF_ID_MediumLH;   //!
   TBranch        *b_el_SF_Iso_FCTight;   //!
   TBranch        *b_mu_SF_TTVA;   //!
   TBranch        *b_mu_SF_ID_HighPt;   //!
   TBranch        *b_mu_SF_ID_Loose;   //!
   TBranch        *b_mu_SF_ID_Medium;   //!
   TBranch        *b_mu_SF_Iso_FCTightTrackOnly_FixedRad;   //!
   TBranch        *b_mu_SF_Iso_TightTrackOnly_VarRad;   //!
   TBranch        *b_fwdel_isTight;   //!
   TBranch        *b_fwdel_isMedium;   //!
   TBranch        *b_fwdel_isLoose;   //!
   TBranch        *b_el_isElMedium;   //!
   TBranch        *b_el_isElLoose;   //!
   TBranch        *b_el_DFCommonElectronsECIDS;   //!
   TBranch        *b_el_DFCommonElectronsECIDSResult;   //!
   TBranch        *b_el_isPromptLepton;   //!
   TBranch        *b_weight_mc;   //!
   TBranch        *b_weight_pileup;   //!
   TBranch        *b_weight_leptonSF;   //!
   TBranch        *b_weight_globalLeptonTriggerSF;   //!
   TBranch        *b_weight_jvt;   //!
   TBranch        *b_weight_pileup_UP;   //!
   TBranch        *b_weight_pileup_DOWN;   //!
   TBranch        *b_weight_indiv_SF_EL_ChargeMisID;   //!
   TBranch        *b_weight_indiv_SF_EL_ChargeMisID_STAT_UP;   //!
   TBranch        *b_weight_indiv_SF_EL_ChargeMisID_STAT_DOWN;   //!
   TBranch        *b_weight_indiv_SF_EL_ChargeMisID_SYST_UP;   //!
   TBranch        *b_weight_indiv_SF_EL_ChargeMisID_SYST_DOWN;   //!
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
   TBranch        *b_Dilepton_Pt_born;   //!
   TBranch        *b_Dilepton_Rapidity_born;   //!
   TBranch        *b_Dilepton_Eta_born;   //!
   TBranch        *b_Dilepton_Phi_born;   //!
   TBranch        *b_Dilepton_Mass_born;   //!

   TBranch        *b_PS_HLT_e26_lhvloose_nod0_L1EM20VH;   //!
   TBranch        *b_PS_HLT_e26_lhvloose_nod0_L1EM22VH;   //!
   TBranch        *b_PS_HLT_e60_lhvloose_nod0;   //!
   TBranch        *b_PS_HLT_e200_etcut;   //!
   TBranch        *b_PS_HLT_e120_lhvloose_nod0;   //!
   TBranch        *b_PS_HLT_e140_lhvloose_nod0;   //!
   TBranch        *b_PS_HLT_e300_etcut;   //!

   //Truth tree

   TreeForPreHMDY();
   virtual ~TreeForPreHMDY();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void CloseFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual TString GetRootType(TString name);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void GetTruthEntry(int ifile, long i);
   virtual double GetSumOfWeight(int nchannel, int Year);
   virtual void GetPDFAndQCDIndex(int ifile);
   virtual int GetYear(TString RootName);
   virtual void InputSumOfWeight(map<pair<int, int>, double> SumOfWeightsMap);
   virtual void InputLuminosity(double Lumi1516, double Lumi17, double Lumi18);
   virtual void Init();

   TString TreeName = "nominal";
   virtual void InputTreeName(TString name){TreeName = name;}

   virtual void BkgSelection(TString BkgName);
   virtual void YearSelection(int Year);
   virtual void DoTruthSelection(){doTruthSelection = true;}
   virtual void SavePDFAndQCDUnc(){doPDFAndQCDUnc = true;}
   virtual void InitialSysName();
};

#endif

#ifdef TreeForPreHMDY_cxx
void TreeForPreHMDY::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   el_pt = 0;
   el_eta = 0;
   el_cl_eta = 0;
   el_phi = 0;
   el_e = 0;
   el_charge = 0;
   el_topoetcone20 = 0;
   el_ptvarcone20 = 0;
   el_isTight = 0;
   el_CF = 0;
   el_d0sig = 0;
   el_delta_z0_sintheta = 0;
   mu_pt = 0;
   mu_eta = 0;
   mu_phi = 0;
   mu_e = 0;
   mu_charge = 0;
   mu_topoetcone20 = 0;
   mu_ptvarcone30 = 0;
   mu_isTight = 0;
   mu_d0sig = 0;
   mu_delta_z0_sintheta = 0;
   jet_pt = 0;
   jet_eta = 0;
   jet_phi = 0;
   jet_e = 0;
   jet_jvt = 0;
   el_trigMatch_HLT_e60_lhmedium = 0;
   el_trigMatch_HLT_e120_lhloose = 0;
   el_trigMatch_HLT_e24_lhmedium_L1EM20VH = 0;
   mu_trigMatch_HLT_mu50 = 0;
   mu_trigMatch_HLT_mu18_mu8noL1 = 0;
   mu_trigMatch_HLT_mu20_iloose_L1MU15 = 0;
   el_trigMatch_HLT_e60_lhmedium_nod0 = 0;
   el_trigMatch_HLT_e140_lhloose_nod0 = 0;
   el_trigMatch_HLT_e26_lhtight_nod0_ivarloose = 0;
   mu_trigMatch_HLT_mu22_mu8noL1 = 0;
   mu_trigMatch_HLT_mu26_ivarmedium = 0;
   el_trigMatch_HLT_e26_lhvloose_nod0_L1EM20VH = 0;
   el_trigMatch_HLT_e26_lhvloose_nod0_L1EM22VH = 0;
   el_trigMatch_HLT_e60_lhvloose_nod0 = 0;
   el_trigMatch_HLT_e120_lhvloose_nod0 = 0;
   el_trigMatch_HLT_e140_lhvloose_nod0 = 0;
   el_trigMatch_HLT_e200_etcut = 0;
   el_trigMatch_HLT_e300_etcut = 0;
   mu_isMedium = 0;
   mu_isHighPt = 0;
   mu_PtID = 0;
   mu_PtMS = 0;
   mu_isolation_FixedCutTight = 0;
   mu_isolation_FixedCutLoose = 0;
   mu_isolation_FixedCutPflowTight = 0;
   mu_isolation_FixedCutPflowLoose = 0;
   mu_isolation_FCTightTrackOnly_FixedRad = 0;
   mu_isolation_TightTrackOnly_VarRad = 0;
   el_isolation_FixedCutLoose = 0;
   el_isolation_FixedCutTight = 0;
   el_isolation_PflowTight = 0;
   el_isolation_TightTrackOnly = 0;
   el_isolation_TightTrackOnly_FixedRad = 0;
   el_isElTight = 0;
   el_SF_Reco = 0;
   el_SF_Reco_Corr = 0;
   el_SF_ID_LooseAndBLayerLH = 0;
   el_SF_ID_MediumLH = 0;
   el_SF_Iso_FCTight = 0;
   mu_SF_TTVA = 0;
   mu_SF_ID_HighPt = 0;
   mu_SF_ID_Loose = 0;
   mu_SF_ID_Medium = 0;
   mu_SF_Iso_FCTightTrackOnly_FixedRad = 0;
   mu_SF_Iso_TightTrackOnly_VarRad = 0;
   fwdel_isTight = 0;
   fwdel_isMedium = 0;
   fwdel_isLoose = 0;
   el_isElMedium = 0;
   el_isElLoose = 0;
   el_DFCommonElectronsECIDS = 0;
   el_DFCommonElectronsECIDSResult = 0;
   el_isPromptLepton = 0;

}

#endif
