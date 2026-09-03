#ifndef ZPrime_HistsZPrime_h
#define ZPrime_HistsZPrime_h
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
#include "ZPrime/TreeForZPrime.h"
#include "ZPrime/loopZPrime.h"
#include "ZPrime/ZPrimetopDDHelper.h"

using namespace std;

class ZPrimeHistGroup;
class HistsZPrime;
class EventZPrime;
class TreeForZPrime;
class loopZPrime;

class ZPrimeHistGroup
{
 friend class HistsZPrime;

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

 ThreadHist<TH1D *>* SSM_ee_0p5TeV;
 ThreadHist<TH1D *>* SSM_ee_0p6TeV;
 ThreadHist<TH1D *>* SSM_ee_0p8TeV;
 ThreadHist<TH1D *>* SSM_ee_1TeV;
 ThreadHist<TH1D *>* SSM_ee_2TeV;
 ThreadHist<TH1D *>* SSM_ee_3TeV;
 ThreadHist<TH1D *>* SSM_ee_4TeV;
 ThreadHist<TH1D *>* SSM_ee_5TeV;
 ThreadHist<TH1D *>* SSM_ee_6TeV;
 ThreadHist<TH1D *>* SSM_ee_7TeV;
 ThreadHist<TH1D *>* SSM_ee_8TeV;

 ThreadHist<TH1D *>* E6Chi_ee_0p5TeV;
 ThreadHist<TH1D *>* E6Chi_ee_0p6TeV;
 ThreadHist<TH1D *>* E6Chi_ee_0p8TeV;
 ThreadHist<TH1D *>* E6Chi_ee_1TeV;
 ThreadHist<TH1D *>* E6Chi_ee_2TeV;
 ThreadHist<TH1D *>* E6Chi_ee_3TeV;
 ThreadHist<TH1D *>* E6Chi_ee_4TeV;
 ThreadHist<TH1D *>* E6Chi_ee_5TeV;
 ThreadHist<TH1D *>* E6Chi_ee_6TeV;
 ThreadHist<TH1D *>* E6Chi_ee_7TeV;
 ThreadHist<TH1D *>* E6Chi_ee_8TeV;

 ThreadHist<TH1D *>* E6Psi_ee_0p5TeV;
 ThreadHist<TH1D *>* E6Psi_ee_0p6TeV;
 ThreadHist<TH1D *>* E6Psi_ee_0p8TeV;
 ThreadHist<TH1D *>* E6Psi_ee_1TeV;
 ThreadHist<TH1D *>* E6Psi_ee_2TeV;
 ThreadHist<TH1D *>* E6Psi_ee_3TeV;
 ThreadHist<TH1D *>* E6Psi_ee_4TeV;
 ThreadHist<TH1D *>* E6Psi_ee_5TeV;
 ThreadHist<TH1D *>* E6Psi_ee_6TeV;
 ThreadHist<TH1D *>* E6Psi_ee_7TeV;
 ThreadHist<TH1D *>* E6Psi_ee_8TeV;

 ThreadHist<TH1D *>* SSM_mm_0p5TeV;
 ThreadHist<TH1D *>* SSM_mm_0p6TeV;
 ThreadHist<TH1D *>* SSM_mm_0p8TeV;
 ThreadHist<TH1D *>* SSM_mm_1TeV;
 ThreadHist<TH1D *>* SSM_mm_2TeV;
 ThreadHist<TH1D *>* SSM_mm_3TeV;
 ThreadHist<TH1D *>* SSM_mm_4TeV;
 ThreadHist<TH1D *>* SSM_mm_5TeV;
 ThreadHist<TH1D *>* SSM_mm_6TeV;
 ThreadHist<TH1D *>* SSM_mm_7TeV;
 ThreadHist<TH1D *>* SSM_mm_8TeV;

 ThreadHist<TH1D *>* E6Chi_mm_0p5TeV;
 ThreadHist<TH1D *>* E6Chi_mm_0p6TeV;
 ThreadHist<TH1D *>* E6Chi_mm_0p8TeV;
 ThreadHist<TH1D *>* E6Chi_mm_1TeV;
 ThreadHist<TH1D *>* E6Chi_mm_2TeV;
 ThreadHist<TH1D *>* E6Chi_mm_3TeV;
 ThreadHist<TH1D *>* E6Chi_mm_4TeV;
 ThreadHist<TH1D *>* E6Chi_mm_5TeV;
 ThreadHist<TH1D *>* E6Chi_mm_6TeV;
 ThreadHist<TH1D *>* E6Chi_mm_7TeV;
 ThreadHist<TH1D *>* E6Chi_mm_8TeV;

 ThreadHist<TH1D *>* E6Psi_mm_0p5TeV;
 ThreadHist<TH1D *>* E6Psi_mm_0p6TeV;
 ThreadHist<TH1D *>* E6Psi_mm_0p8TeV;
 ThreadHist<TH1D *>* E6Psi_mm_1TeV;
 ThreadHist<TH1D *>* E6Psi_mm_2TeV;
 ThreadHist<TH1D *>* E6Psi_mm_3TeV;
 ThreadHist<TH1D *>* E6Psi_mm_4TeV;
 ThreadHist<TH1D *>* E6Psi_mm_5TeV;
 ThreadHist<TH1D *>* E6Psi_mm_6TeV;
 ThreadHist<TH1D *>* E6Psi_mm_7TeV;
 ThreadHist<TH1D *>* E6Psi_mm_8TeV;

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


 HistsZPrime *fHist;
 int TotalThread;

 TString HistName = "";
 TString SystematicName = "";

 ZPrimeHistGroup();
 virtual void Initial(int iThread, TString MCType);
 virtual void Fill(int iThread, double par, double weight, EventZPrime ProcessEvent);
 virtual void Fill(int iThread, double par1, double par2, double weight, EventZPrime ProcessEvent);
 virtual void FillFakeUnc(int iThread, double par, double weight, EventZPrime ProcessEvent);
 virtual void FillFakeUnc(int iThread, double par1, double par2, double weight, EventZPrime ProcessEvent);
 virtual void FillTruth(int iThread, double par1, double weight, EventZPrime ProcessEvent);
 virtual void FillTruth(int iThread, double par1, double par2, double weight, EventZPrime ProcessEvent);
 virtual void FillUnfold(int iThread, double reco, double truth, double weight, int passReco, int passTruth, EventZPrime ProcessEvent);
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

class HistsZPrime : public makeHists
{
 friend class ZPrimeHistGroup;

 TreeForZPrime *fTree;

 public:

 ZPrimeHistGroup* Mll_HighMass;
 ZPrimeHistGroup* Mll_LowMass;
 ZPrimeHistGroup* Mll_FineBin;
 ZPrimeHistGroup* pTll;
 ZPrimeHistGroup* costheta;
 ZPrimeHistGroup* DilRapidity;
 ZPrimeHistGroup* PhiStar;
 ZPrimeHistGroup* LeadingLepEta;
 ZPrimeHistGroup* SubleadingLepEta;
 ZPrimeHistGroup* LeadingLepPhi;
 ZPrimeHistGroup* SubleadingLepPhi;
 ZPrimeHistGroup* LeadingLepPt;
 ZPrimeHistGroup* SubleadingLepPt;
 ZPrimeHistGroup* LeadingLepPt_FineBin;
 ZPrimeHistGroup* SubleadingLepPt_FineBin;
 ZPrimeHistGroup* Lepton1_z0;
 ZPrimeHistGroup* Lepton2_z0;
 ZPrimeHistGroup* Lepton1_d0Sig;
 ZPrimeHistGroup* Lepton2_d0Sig;

 ZPrimeHistGroup* DilRapidity_HighMass;
 ZPrimeHistGroup* DilRapidity_LowMass;

 ZPrimeHistGroup* LooseLepton1Eta;
 ZPrimeHistGroup* LooseLepton1Pt;
 ZPrimeHistGroup* LooseLepton3Eta;
 ZPrimeHistGroup* LooseLepton3Pt;

 ZPrimeHistGroup* TightLepton1Eta;
 ZPrimeHistGroup* TightLepton1Pt;
 ZPrimeHistGroup* TightLepton3Eta;
 ZPrimeHistGroup* TightLepton3Pt;

 ZPrimeHistGroup* LooseLepton1PtEta;
 ZPrimeHistGroup* LooseLepton3PtEta;
 ZPrimeHistGroup* TightLepton1PtEta;
 ZPrimeHistGroup* TightLepton3PtEta;

 ZPrimeHistGroup* LooseMass_eem;
 ZPrimeHistGroup* TightMass_eem;

 ZPrimeHistGroup* LooseLepton3_d0Sig_eem;
 ZPrimeHistGroup* TightLepton3_d0Sig_eem;

 ZPrimeHistGroup* HighMass_CosTheta;
 ZPrimeHistGroup* HighMass_Rapidity;

 ZPrimeHistGroup* LeptonPtClosure;

 TH1D* TransferFactor_ee;
 TH1D* TransferFactor_mm;
 TH2D* TransferFactor_HighMass_CosTheta_ee;
 TH2D* TransferFactor_HighMass_CosTheta_mm;
 TH2D* TransferFactor_HighMass_Rapidity_ee;
 TH2D* TransferFactor_HighMass_Rapidity_mm;

 ThreadHist<AngularFunction *>* L0_Mass_QT_ZY_uu;
 ThreadHist<AngularFunction *>* A0_Mass_QT_ZY_uu;
 ThreadHist<AngularFunction *>* A1_Mass_QT_ZY_uu;
 ThreadHist<AngularFunction *>* A2_Mass_QT_ZY_uu;
 ThreadHist<AngularFunction *>* A3_Mass_QT_ZY_uu;
 ThreadHist<AngularFunction *>* A4_Mass_QT_ZY_uu;
 ThreadHist<AngularFunction *>* L0_Mass_QT_ZY_dd;
 ThreadHist<AngularFunction *>* A0_Mass_QT_ZY_dd;
 ThreadHist<AngularFunction *>* A1_Mass_QT_ZY_dd;
 ThreadHist<AngularFunction *>* A2_Mass_QT_ZY_dd;
 ThreadHist<AngularFunction *>* A3_Mass_QT_ZY_dd;
 ThreadHist<AngularFunction *>* A4_Mass_QT_ZY_dd;

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

 HistsZPrime();
 virtual void bookHists(int TotalThread);
 virtual void outputInformation();
 virtual void bookAllProcessHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbin, double left, double right);
 virtual void bookAllProcessHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbin, double* xbins);
 virtual void bookAllProcessHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty);
 virtual void bookAllProcessHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins);
 virtual void DefineHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbin, double left, double right);
 virtual void DefineHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbin, double* xbins);
 virtual void DefineHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty);
 virtual void DefineHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins);
 virtual void LinkClass(HistsZPrime *hist);

 virtual void GetTransferFactor();

 TString SystematicName = "";
 void InputSystematicName(TString SystematicName){this->SystematicName = SystematicName;};

 vector<ZPrimeHistGroup *> hist_process;
 vector<TString> HistNames;

 bool doTopDD = false;
 ZPrimetopDDHelper* topDD;
 ZPrimetopDDHelper* topDD_HighMass_CosTheta;
 ZPrimetopDDHelper* topDD_HighMass_Rapidity;
 virtual void InputTopDD(ZPrimetopDDHelper* topDD, ZPrimetopDDHelper* topDD_HighMass_CosTheta, ZPrimetopDDHelper* topDD_HighMass_Rapidity){
   this->topDD = topDD;
   this->topDD_HighMass_CosTheta = topDD_HighMass_CosTheta;
   this->topDD_HighMass_Rapidity = topDD_HighMass_Rapidity;
   doTopDD = true;
 }
};
#endif
