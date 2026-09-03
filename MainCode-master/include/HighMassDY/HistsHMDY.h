#ifndef HMDY_HistsHMDY_h
#define HMDY_HistsHMDY_h
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TMath.h"
#include "TTree.h"
#include <vector>
#include "Analysis/makeHists.h"
#include "HighMassDY/TreeForHMDY.h"
#include "HighMassDY/loopHMDY.h"
#include "HighMassDY/topDDHelper.h"

using namespace std;

class HMDYHistGroup;
class HistsHMDY;
class EventHMDY;
class TreeForHMDY;
class loopHMDY;

class HMDYHistGroup
{
 friend class HistsHMDY;

 public:

 ThreadHist<BkgHist *>* SR_ee_bkg;
 ThreadHist<BkgHist *>* SR_mm_bkg;
 ThreadHist<BkgHist *>* SR_em_bkg;

 ThreadHist<BkgHist *>* SR_2D_ee_bkg;
 ThreadHist<BkgHist *>* SR_2D_mm_bkg;
 ThreadHist<BkgHist *>* SR_2D_em_bkg;

 ThreadHist<TH1D *>* topDD_ee;
 ThreadHist<TH1D *>* topDD_mm;

 ThreadHist<TH1D *>* topDD_HighMass_CosTheta_ee;
 ThreadHist<TH1D *>* topDD_HighMass_CosTheta_mm;

 ThreadHist<TH1D *>* topDD_HighMass_Rapidity_ee;
 ThreadHist<TH1D *>* topDD_HighMass_Rapidity_mm;

 ThreadHist<TH2D *>* topDD_2D_ee;
 ThreadHist<TH2D *>* topDD_2D_mm;

 ThreadHist<TH2D *>* topDD_HighMass_CosTheta_2D_ee;
 ThreadHist<TH2D *>* topDD_HighMass_CosTheta_2D_mm;

 ThreadHist<TH2D *>* topDD_HighMass_Rapidity_2D_ee;
 ThreadHist<TH2D *>* topDD_HighMass_Rapidity_2D_mm;

 ThreadHist<BkgHist *>* LowMass_ee_bkg;
 ThreadHist<BkgHist *>* LowMass_mm_bkg;
 ThreadHist<BkgHist *>* LowMass_em_bkg;

 ThreadHist<BkgHist *>* ElFakeCR_bkg;
 ThreadHist<BkgHist *>* MuFakeCR_bkg;

 ThreadHist<BkgHist *>* ElFakeCR_2D_bkg;
 ThreadHist<BkgHist *>* MuFakeCR_2D_bkg;

 ThreadHist<TH1D *>* Truth_DrellYan_El;
 ThreadHist<TH1D *>* Truth_DrellYan_Mu;
 ThreadHist<TH2D *>* Truth_DrellYan_El_2D;
 ThreadHist<TH2D *>* Truth_DrellYan_Mu_2D;

 ThreadHist<TH1D *>* Truth_PI_El;
 ThreadHist<TH1D *>* Truth_PI_Mu;
 ThreadHist<TH2D *>* Truth_PI_El_2D;
 ThreadHist<TH2D *>* Truth_PI_Mu_2D;

 ThreadHist<TH2D *>* Response_DrellYan_El;
 ThreadHist<TH2D *>* Response_DrellYan_Mu;
 ThreadHist<TH1D *>* TruthForUnfold_DrellYan_El;
 ThreadHist<TH1D *>* TruthForUnfold_DrellYan_Mu;
 ThreadHist<TH1D *>* RecoForUnfold_DrellYan_El;
 ThreadHist<TH1D *>* RecoForUnfold_DrellYan_Mu;

 ThreadHist<TH2D *>* Response_PI_El;
 ThreadHist<TH2D *>* Response_PI_Mu;
 ThreadHist<TH1D *>* TruthForUnfold_PI_El;
 ThreadHist<TH1D *>* TruthForUnfold_PI_Mu;
 ThreadHist<TH1D *>* RecoForUnfold_PI_El;
 ThreadHist<TH1D *>* RecoForUnfold_PI_Mu;

 ThreadHist<TH1D *>* ElFake_FakeRate;
 ThreadHist<TH1D *>* ElFake_FakeRate_Stat_up;
 ThreadHist<TH1D *>* ElFake_FakeRate_Stat_down;
 ThreadHist<TH1D *>* ElFake_FakeRate_PromptSubtr_up;
 ThreadHist<TH1D *>* ElFake_FakeRate_PromptSubtr_down;
 ThreadHist<TH1D *>* ElFake_FakeRate_MET_up;
 ThreadHist<TH1D *>* ElFake_FakeRate_MET_down;
 ThreadHist<TH1D *>* ElFake_FakeRate_RealPromptSubtr_up;
 ThreadHist<TH1D *>* ElFake_FakeRate_RealPromptSubtr_down;

 ThreadHist<TH2D *>* ElFake2D_FakeRate;
 ThreadHist<TH2D *>* ElFake2D_FakeRate_Stat_up;
 ThreadHist<TH2D *>* ElFake2D_FakeRate_Stat_down;
 ThreadHist<TH2D *>* ElFake2D_FakeRate_PromptSubtr_up;
 ThreadHist<TH2D *>* ElFake2D_FakeRate_PromptSubtr_down;
 ThreadHist<TH2D *>* ElFake2D_FakeRate_MET_up;
 ThreadHist<TH2D *>* ElFake2D_FakeRate_MET_down;
 ThreadHist<TH2D *>* ElFake2D_FakeRate_RealPromptSubtr_up;
 ThreadHist<TH2D *>* ElFake2D_FakeRate_RealPromptSubtr_down;

 ThreadHist<BkgHist *>* ElFake_TT_bkg;
 ThreadHist<BkgHist *>* ElFake_TL_bkg;
 ThreadHist<BkgHist *>* ElFake_LT_bkg;
 ThreadHist<BkgHist *>* ElFake_LL_bkg;

 ThreadHist<TH1D *>* Fake_MM_FourTerm_TT;
 ThreadHist<TH1D *>* Fake_MM_FourTerm_TL;
 ThreadHist<TH1D *>* Fake_MM_FourTerm_LT;
 ThreadHist<TH1D *>* Fake_MM_FourTerm_LL;

 // Electron/Muon Fake Uncertainty
 ThreadHist<TH1D *>* Fake_El_Stat_up;
 ThreadHist<TH1D *>* Fake_El_Stat_down;
 ThreadHist<TH1D *>* Fake_El_PromptSubtr_up;
 ThreadHist<TH1D *>* Fake_El_PromptSubtr_down;
 ThreadHist<TH1D *>* Fake_El_MET_up;
 ThreadHist<TH1D *>* Fake_El_MET_down;
 ThreadHist<TH1D *>* Fake_El_RealStat_up;
 ThreadHist<TH1D *>* Fake_El_RealStat_down;

 ThreadHist<TH1D *>* Fake_Mu_Stat_up;
 ThreadHist<TH1D *>* Fake_Mu_Stat_down;
 ThreadHist<TH1D *>* Fake_Mu_PromptSubtr_up;
 ThreadHist<TH1D *>* Fake_Mu_PromptSubtr_down;
 ThreadHist<TH1D *>* Fake_Mu_d0sig_up;
 ThreadHist<TH1D *>* Fake_Mu_d0sig_down;
 ThreadHist<TH1D *>* Fake_Mu_RealStat_up;
 ThreadHist<TH1D *>* Fake_Mu_RealStat_down;

 ThreadHist<TH2D *>* Fake2D_El_Stat_up;
 ThreadHist<TH2D *>* Fake2D_El_Stat_down;
 ThreadHist<TH2D *>* Fake2D_El_PromptSubtr_up;
 ThreadHist<TH2D *>* Fake2D_El_PromptSubtr_down;
 ThreadHist<TH2D *>* Fake2D_El_MET_up;
 ThreadHist<TH2D *>* Fake2D_El_MET_down;
 ThreadHist<TH2D *>* Fake2D_El_RealStat_up;
 ThreadHist<TH2D *>* Fake2D_El_RealStat_down;

 ThreadHist<TH2D *>* Fake2D_Mu_Stat_up;
 ThreadHist<TH2D *>* Fake2D_Mu_Stat_down;
 ThreadHist<TH2D *>* Fake2D_Mu_PromptSubtr_up;
 ThreadHist<TH2D *>* Fake2D_Mu_PromptSubtr_down;
 ThreadHist<TH2D *>* Fake2D_Mu_d0sig_up;
 ThreadHist<TH2D *>* Fake2D_Mu_d0sig_down;
 ThreadHist<TH2D *>* Fake2D_Mu_RealStat_up;
 ThreadHist<TH2D *>* Fake2D_Mu_RealStat_down;

 // Electron Fake
 ThreadHist<TH1D *>* Fake_PromptSubtrUp;
 ThreadHist<TH1D *>* Fake_PromptSubtrDown;
 ThreadHist<TH1D *>* Fake_noW;
 ThreadHist<TH1D *>* Fake_noDY;
 ThreadHist<TH1D *>* Fake_noZMass;
 ThreadHist<TH1D *>* Fake_StatsUp;
 ThreadHist<TH1D *>* Fake_StatsDown;

 // Muon Fake
 ThreadHist<TH1D *>* Fake_stats_1up;
 ThreadHist<TH1D *>* Fake_stats_1down;
 ThreadHist<TH1D *>* Fake_d0Sig_1up;
 ThreadHist<TH1D *>* Fake_d0Sig_1down;

 TH1D* ElFake_Nominal;
 TH1D* MuFake_Nominal;

 TH2D* ElFake2D_Nominal;
 TH2D* MuFake2D_Nominal;

 TH1D* FinalData_ee;
 TH1D* FinalData_mm;
 TH1D* FinalData_topDD_ee;
 TH1D* FinalData_topDD_mm;
 TH1D* FinalData_topDD_HighMass_CosTheta_ee;
 TH1D* FinalData_topDD_HighMass_CosTheta_mm;
 TH1D* FinalData_topDD_HighMass_Rapidity_ee;
 TH1D* FinalData_topDD_HighMass_Rapidity_mm;

 TH1D* SumMC_ee;
 TH1D* SumMC_mm;
 TH1D* SumMC_topDD_ee;
 TH1D* SumMC_topDD_mm;
 TH1D* SumMC_topDD_HighMass_CosTheta_ee;
 TH1D* SumMC_topDD_HighMass_CosTheta_mm;
 TH1D* SumMC_topDD_HighMass_Rapidity_ee;
 TH1D* SumMC_topDD_HighMass_Rapidity_mm;

 TH2D* FinalData_2D_ee;
 TH2D* FinalData_2D_mm;
 TH2D* FinalData_2D_topDD_ee;
 TH2D* FinalData_2D_topDD_mm;
 TH2D* FinalData_2D_topDD_HighMass_CosTheta_ee;
 TH2D* FinalData_2D_topDD_HighMass_CosTheta_mm;
 TH2D* FinalData_2D_topDD_HighMass_Rapidity_ee;
 TH2D* FinalData_2D_topDD_HighMass_Rapidity_mm;

 TH2D* SumMC_2D_ee;
 TH2D* SumMC_2D_mm;
 TH2D* SumMC_2D_topDD_ee;
 TH2D* SumMC_2D_topDD_mm;
 TH2D* SumMC_2D_topDD_HighMass_CosTheta_ee;
 TH2D* SumMC_2D_topDD_HighMass_CosTheta_mm;
 TH2D* SumMC_2D_topDD_HighMass_Rapidity_ee;
 TH2D* SumMC_2D_topDD_HighMass_Rapidity_mm;


 HistsHMDY *fHist;
 int TotalThread;

 TString HistName = "";
 TString SystematicName = "";

 HMDYHistGroup();
 virtual void Initial(int iThread, TString MCType);
 virtual void Fill(int iThread, double par, double weight, EventHMDY ProcessEvent);
 virtual void Fill(int iThread, double par1, double par2, double weight, EventHMDY ProcessEvent);
 virtual void FillFakeUnc(int iThread, double par, double weight, EventHMDY ProcessEvent);
 virtual void FillFakeUnc(int iThread, double par1, double par2, double weight, EventHMDY ProcessEvent);
 virtual void FillTruth(int iThread, double par1, double weight, EventHMDY ProcessEvent);
 virtual void FillTruth(int iThread, double par1, double par2, double weight, EventHMDY ProcessEvent);
 virtual void FillUnfold(int iThread, double reco, double truth, double weight, int passReco, int passTruth, EventHMDY ProcessEvent);
 virtual void ApplyFakeUnc();
 virtual void ResetHist();
 virtual void GetFinalData();

 TString MCType[100] = {""};
 bool isData[100] = {false};
 bool isSignal[100] = {false};
 bool isTop[100] = {false};

 bool isFillFakeUnc = false;
 virtual void doFillFakeUnc(){isFillFakeUnc = true;}

 int Dimension = 1;
};

class HistsHMDY : public makeHists
{
 friend class HMDYHistGroup;

 TreeForHMDY *fTree;

 public:

 HMDYHistGroup* Mll_HighMass;
 HMDYHistGroup* Mll_LowMass;
 HMDYHistGroup* Mll_FineBin;
 HMDYHistGroup* pTll;
 HMDYHistGroup* costheta;
 HMDYHistGroup* DilRapidity;
 HMDYHistGroup* PhiStar;
 HMDYHistGroup* LeadingLepEta;
 HMDYHistGroup* SubleadingLepEta;
 HMDYHistGroup* LeadingLepPhi;
 HMDYHistGroup* SubleadingLepPhi;
 HMDYHistGroup* LeadingLepPt;
 HMDYHistGroup* SubleadingLepPt;
 HMDYHistGroup* LeadingLepPt_FineBin;
 HMDYHistGroup* SubleadingLepPt_FineBin;
 HMDYHistGroup* Lepton1_z0;
 HMDYHistGroup* Lepton2_z0;
 HMDYHistGroup* Lepton1_d0Sig;
 HMDYHistGroup* Lepton2_d0Sig;

 HMDYHistGroup* DilRapidity_HighMass;
 HMDYHistGroup* DilRapidity_LowMass;

 HMDYHistGroup* LooseLepton1Eta;
 HMDYHistGroup* LooseLepton1Pt;
 HMDYHistGroup* LooseLepton3Eta;
 HMDYHistGroup* LooseLepton3Pt;

 HMDYHistGroup* TightLepton1Eta;
 HMDYHistGroup* TightLepton1Pt;
 HMDYHistGroup* TightLepton3Eta;
 HMDYHistGroup* TightLepton3Pt;

 HMDYHistGroup* LooseLepton1PtEta;
 HMDYHistGroup* LooseLepton3PtEta;
 HMDYHistGroup* TightLepton1PtEta;
 HMDYHistGroup* TightLepton3PtEta;

 HMDYHistGroup* LooseMass_eem;
 HMDYHistGroup* TightMass_eem;

 HMDYHistGroup* LooseLepton3_d0Sig_eem;
 HMDYHistGroup* TightLepton3_d0Sig_eem;

 HMDYHistGroup* HighMass_CosTheta;
 HMDYHistGroup* HighMass_Rapidity;

 HMDYHistGroup* LeptonPtClosure;

 TH1D* TransferFactor_ee;
 TH1D* TransferFactor_mm;
 TH2D* TransferFactor_HighMass_CosTheta_ee;
 TH2D* TransferFactor_HighMass_CosTheta_mm;
 TH2D* TransferFactor_HighMass_Rapidity_ee;
 TH2D* TransferFactor_HighMass_Rapidity_mm;

 ThreadHist<TH2D *>* RealLeptonPtEta_El_Loose;
 ThreadHist<TH2D *>* RealLeptonPtEta_El_Tight;
 ThreadHist<TH2D *>* RealLeptonPtEta_Mu_Loose;
 ThreadHist<TH2D *>* RealLeptonPtEta_Mu_Tight;

 ThreadHist<TH2D *>* RealLepton1PtEta_El_Loose;
 ThreadHist<TH2D *>* RealLepton1PtEta_El_Tight;
 ThreadHist<TH2D *>* RealLepton2PtEta_El_Loose;
 ThreadHist<TH2D *>* RealLepton2PtEta_El_Tight;

 ThreadHist<TH2D *>* RealLepton1Pt2Pt_El_Loose;
 ThreadHist<TH2D *>* RealLepton1Pt2Pt_El_Tight;

 ThreadHist<TH1D *>* RealLepton1Pt_FineBin_NoMassCut_Loose;
 ThreadHist<TH1D *>* RealLepton1Pt_FineBin_NoMassCut_MediumID;
 ThreadHist<TH1D *>* RealLepton1Pt_FineBin_NoMassCut_Iso;
 ThreadHist<TH1D *>* RealLepton1Pt_FineBin_NoMassCut_Tight;
 ThreadHist<TH1D *>* RealLepton1Pt_FineBin_NoMassCut_Truth;
 ThreadHist<TH1D *>* RealLepton2Pt_FineBin_NoMassCut_Loose;
 ThreadHist<TH1D *>* RealLepton2Pt_FineBin_NoMassCut_MediumID;
 ThreadHist<TH1D *>* RealLepton2Pt_FineBin_NoMassCut_Iso;
 ThreadHist<TH1D *>* RealLepton2Pt_FineBin_NoMassCut_Tight;
 ThreadHist<TH1D *>* RealLepton2Pt_FineBin_NoMassCut_Truth;

 ThreadHist<TH1D *>* RealLepton1Pt_FineBin_Mass116Cut_Loose;
 ThreadHist<TH1D *>* RealLepton1Pt_FineBin_Mass116Cut_MediumID;
 ThreadHist<TH1D *>* RealLepton1Pt_FineBin_Mass116Cut_Iso;
 ThreadHist<TH1D *>* RealLepton1Pt_FineBin_Mass116Cut_Tight;
 ThreadHist<TH1D *>* RealLepton1Pt_FineBin_Mass116Cut_Truth;
 ThreadHist<TH1D *>* RealLepton2Pt_FineBin_Mass116Cut_Loose;
 ThreadHist<TH1D *>* RealLepton2Pt_FineBin_Mass116Cut_MediumID;
 ThreadHist<TH1D *>* RealLepton2Pt_FineBin_Mass116Cut_Iso;
 ThreadHist<TH1D *>* RealLepton2Pt_FineBin_Mass116Cut_Tight;
 ThreadHist<TH1D *>* RealLepton2Pt_FineBin_Mass116Cut_Truth;

 ThreadHist<TH2D *>* Lepton1PtResolution_NoMassCut_Loose;
 ThreadHist<TH2D *>* Lepton1PtResolution_NoMassCut_Tight;
 ThreadHist<TH2D *>* Lepton2PtResolution_NoMassCut_Loose;
 ThreadHist<TH2D *>* Lepton2PtResolution_NoMassCut_Tight;
 ThreadHist<TH2D *>* Lepton1PtResolution_Mass116Cut_Loose;
 ThreadHist<TH2D *>* Lepton1PtResolution_Mass116Cut_Tight;
 ThreadHist<TH2D *>* Lepton2PtResolution_Mass116Cut_Loose;
 ThreadHist<TH2D *>* Lepton2PtResolution_Mass116Cut_Tight;

 ThreadHist<TH2D *>* FakeLeptonPtEta_El_Loose;
 ThreadHist<TH2D *>* FakeLeptonPtEta_El_Tight;
 ThreadHist<TH2D *>* FakeLeptonPtEta_El_PromptSubtr_up_Loose;
 ThreadHist<TH2D *>* FakeLeptonPtEta_El_PromptSubtr_up_Tight;
 ThreadHist<TH2D *>* FakeLeptonPtEta_El_PromptSubtr_down_Loose;
 ThreadHist<TH2D *>* FakeLeptonPtEta_El_PromptSubtr_down_Tight;
 ThreadHist<TH2D *>* FakeLeptonPtEta_El_MET_up_Loose;
 ThreadHist<TH2D *>* FakeLeptonPtEta_El_MET_up_Tight;
 ThreadHist<TH2D *>* FakeLeptonPtEta_El_MET_down_Loose;
 ThreadHist<TH2D *>* FakeLeptonPtEta_El_MET_down_Tight;

 ThreadHist<TH2D *>* FakeLeptonPtEta_Mu_Loose;
 ThreadHist<TH2D *>* FakeLeptonPtEta_Mu_Tight;
 ThreadHist<TH2D *>* FakeLeptonPtEta_Mu_PromptSubtr_up_Loose;
 ThreadHist<TH2D *>* FakeLeptonPtEta_Mu_PromptSubtr_up_Tight;
 ThreadHist<TH2D *>* FakeLeptonPtEta_Mu_PromptSubtr_down_Loose;
 ThreadHist<TH2D *>* FakeLeptonPtEta_Mu_PromptSubtr_down_Tight;
 ThreadHist<TH2D *>* FakeLeptonPtEta_Mu_d0sig_up_Loose;
 ThreadHist<TH2D *>* FakeLeptonPtEta_Mu_d0sig_up_Tight;
 ThreadHist<TH2D *>* FakeLeptonPtEta_Mu_d0sig_down_Loose;
 ThreadHist<TH2D *>* FakeLeptonPtEta_Mu_d0sig_down_Tight;

 ThreadHist<TH1D *>* FakeLeptonPt_Mu_Loose;
 ThreadHist<TH1D *>* FakeLeptonPt_Mu_Tight;

 ThreadHist<TH2D *>* FakeLeptonPtEta_El_Wjets_Loose;
 ThreadHist<TH2D *>* FakeLeptonPtEta_El_Wjets_Tight;
 ThreadHist<TH2D *>* RealLeptonPtEta_El_Wjets_Loose;
 ThreadHist<TH2D *>* RealLeptonPtEta_El_Wjets_Tight;
 ThreadHist<TH2D *>* RealLepton2PtEta_El_Wjets_Loose;
 ThreadHist<TH2D *>* RealLepton2PtEta_El_Wjets_Tight;

 TH2D* RealEfficiency_El;
 TH2D* RealEfficiency_Mu;

 TH2D* RealEfficiency_El_Lepton1;
 TH2D* RealEfficiency_El_Lepton2;

 TH2D* RealEfficiency_El_LowD0Sig_Lepton1;
 TH2D* RealEfficiency_El_LowD0Sig_Lepton2;

 TH2D* RealEfficiency_El_HighD0Sig_Lepton1;
 TH2D* RealEfficiency_El_HighD0Sig_Lepton2;

 TH2D* RealEfficiency_El_ClosePt_Lepton1;
 TH2D* RealEfficiency_El_ClosePt_Lepton2;

 TH2D* RealEfficiency_El_SmallMET_Lepton1;
 TH2D* RealEfficiency_El_SmallMET_Lepton2;

 TH2D* RealEfficiency_El_PtD0Sig_Lepton1;
 TH2D* RealEfficiency_El_PtD0Sig_Lepton2;

 TH3D* RealEfficiency_El_PtEtaD0Sig_Lepton1;
 TH3D* RealEfficiency_El_PtEtaD0Sig_Lepton2;

 TH2D* RealEfficiency_El_1Pt2Pt;

 TH2D* FakeEfficiency_El;
 TH2D* FakeEfficiency_El_Stat_up;
 TH2D* FakeEfficiency_El_Stat_down;
 TH2D* FakeEfficiency_El_PromptSubtr_up;
 TH2D* FakeEfficiency_El_PromptSubtr_down;
 TH2D* FakeEfficiency_El_MET_up;
 TH2D* FakeEfficiency_El_MET_down;

 TH2D* FakeEfficiency_Mu;
 TH2D* FakeEfficiency_Mu_Stat_up;
 TH2D* FakeEfficiency_Mu_Stat_down;
 TH2D* FakeEfficiency_Mu_PromptSubtr_up;
 TH2D* FakeEfficiency_Mu_PromptSubtr_down;
 TH2D* FakeEfficiency_Mu_d0sig_up;
 TH2D* FakeEfficiency_Mu_d0sig_down;

 TH1D* FakeEfficiency_Mu_1D;

 TH2D* FakeEfficiency_El_Wjets;
 TH2D* RealEfficiency_El_Wjets;
 TH2D* RealEfficiency_El_Wjets_Lepton2;

 HistsHMDY();
 virtual void bookHists(int TotalThread);
 virtual void outputInformation();
 virtual void bookAllProcessHist(HMDYHistGroup* &hist, TString name, TString title, int nbin, double left, double right);
 virtual void bookAllProcessHist(HMDYHistGroup* &hist, TString name, TString title, int nbin, double* xbins);
 virtual void bookAllProcessHist(HMDYHistGroup* &hist, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty);
 virtual void bookAllProcessHist(HMDYHistGroup* &hist, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins);
 virtual void DefineHist(HMDYHistGroup* &hist, TString name, TString title, int nbin, double left, double right);
 virtual void DefineHist(HMDYHistGroup* &hist, TString name, TString title, int nbin, double* xbins);
 virtual void DefineHist(HMDYHistGroup* &hist, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty);
 virtual void DefineHist(HMDYHistGroup* &hist, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins);
 virtual void LinkClass(HistsHMDY *hist);

 virtual void GetTransferFactor();

 TString SystematicName = "";
 void InputSystematicName(TString SystematicName){this->SystematicName = SystematicName;};

 vector<HMDYHistGroup *> hist_process;
 vector<TString> HistNames;

 bool doTopDD = false;
 topDDHelper* topDD;
 topDDHelper* topDD_HighMass_CosTheta;
 topDDHelper* topDD_HighMass_Rapidity;
 virtual void InputTopDD(topDDHelper* topDD, topDDHelper* topDD_HighMass_CosTheta, topDDHelper* topDD_HighMass_Rapidity){
   this->topDD = topDD;
   this->topDD_HighMass_CosTheta = topDD_HighMass_CosTheta;
   this->topDD_HighMass_Rapidity = topDD_HighMass_Rapidity;
   doTopDD = true;
 }
};
#endif
