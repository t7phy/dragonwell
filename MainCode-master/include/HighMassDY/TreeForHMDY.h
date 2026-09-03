//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 12 13:54:03 2020 by ROOT version 6.14/04
// from TTree Zeetree/Zeetree
// found on file: Zeetree.root
//////////////////////////////////////////////////////////

#ifndef TreeForHMDY_h
#define TreeForHMDY_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "TH1D.h"
#include "HighMassDY/HistsHMDY.h"
#include "HighMassDY/loopHMDY.h"

class loopHMDY;
class HistsHMDY;
class TreeForHMDY;

using namespace std;

class TreeForHMDY
{
 public :

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

   loopHMDY* fLoop;
   HistsHMDY* fHist;

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
   Double_t        RecoWeight_El_Stat_up = 0.0;
   Double_t        RecoWeight_El_Stat_down = 0.0;
   Double_t        RecoWeight_El_PromptSubtr_up = 0.0;
   Double_t        RecoWeight_El_PromptSubtr_down = 0.0;
   Double_t        RecoWeight_El_RealStat_up = 0.0;
   Double_t        RecoWeight_El_RealStat_down = 0.0;
   Double_t        RecoWeight_Mu_Stat_up = 0.0;
   Double_t        RecoWeight_Mu_Stat_down = 0.0;
   Double_t        RecoWeight_Mu_PromptSubtr_up = 0.0;
   Double_t        RecoWeight_Mu_PromptSubtr_down = 0.0;
   Double_t        RecoWeight_Mu_RealStat_up = 0.0;
   Double_t        RecoWeight_Mu_RealStat_down = 0.0;
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
   Bool_t          pass_em_TT;
   Bool_t          pass_em_TL;
   Bool_t          pass_em_LT;
   Bool_t          pass_em_LL;
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

   // List of branches
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

   TreeForHMDY();
   virtual ~TreeForHMDY();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void CloseFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual TString GetRootType(TString RootName);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void LinkHist(HistsHMDY* myhists);
   virtual void Init();

   virtual void InputSystematic(TString sysName);
   virtual void SystematicSelection(TString sysName, TString AdditionalSelection = "");
   virtual void BkgSelection(TString name);

   virtual void updateCutFlow(TH1D *inCutFlow, std::map<std::string, double> *inLabelMap, std::string cutName, double step = 1, bool doUpdate = true); //!
};

#endif
