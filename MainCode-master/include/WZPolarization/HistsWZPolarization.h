#ifndef __HISTS_WZPolarization_H_
#define __HISTS_WZPolarization_H_
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
#include "WZPolarization/TreeForWZPolarization.h"
#include "WZPolarization/loopWZPolarization.h"

using namespace std;

class ProcessHist;
class HistsWZPolarization;
class EventWZPolarization;
class TreeForWZPolarization;
class loopWZPolarization;

class ProcessHist
{
 friend class HistsWZPolarization;

 public:

//WZQCD and Polarized

 ThreadHist<BkgHist *>* InclusivePolarized_bkg;

 ThreadHist<BkgHist *>* SignalPolarized_bkg;

 ThreadHist<BkgHist *>* SignalPtWZPolarized_bkg;

 ThreadHist<BkgHist *>* ZZCRPolarized_bkg;

 ThreadHist<BkgHist *>* TopCRPolarized_bkg;

 ThreadHist<BkgHist *>* HighPtWZCRPolarized_bkg;

 ThreadHist<BkgHist *>* LowPtWZCRPolarized_bkg;

 ThreadHist<BkgHist *>* HighR21CRPolarized_bkg;

 ThreadHist<BkgHist *>* LowR21CRPolarized_bkg;

 ThreadHist<BkgHist *>* LowPtZCRPolarized_bkg;

 ThreadHist<BkgHist *>* HighPtZCRPolarized_bkg;

 ThreadHist<BkgHist *>* PtWZ10CRPolarized_bkg;

 ThreadHist<BkgHist *>* PtWZ20CRPolarized_bkg;

 ThreadHist<BkgHist *>* PtWZ40CRPolarized_bkg;

 ThreadHist<BkgHist *>* SignalNLOPolarized_bkg;

 ThreadHist<BkgHist *>* Signal100NLOPolarized_bkg;


//Truth
 ThreadHist<BkgHist *>* TruthInclusive_bkg;
 
 ThreadHist<BkgHist *>* TruthSignal_bkg;
 
 ThreadHist<BkgHist *>* TruthZZCRPolarized_bkg;
 
 ThreadHist<BkgHist *>* TruthTopCRPolarized_bkg;
 
 ThreadHist<BkgHist *>* TruthHighPtWZCRPolarized_bkg;
 
 ThreadHist<BkgHist *>* TruthLowPtZCRPolarized_bkg;

//Data
 ThreadHist<TH1D *>* Inclusive_Data;
 
 ThreadHist<TH1D *>* Signal_Data;

 ThreadHist<TH1D *>* SignalPtWZ_Data;
 
 ThreadHist<TH1D *>* ZZCRPolarized_Data;
 
 ThreadHist<TH1D *>* TopCRPolarized_Data;
 
 ThreadHist<TH1D *>* HighPtWZCRPolarized_Data;

 ThreadHist<TH1D *>* LowPtWZCRPolarized_Data;

 ThreadHist<TH1D *>* HighR21CRPolarized_Data;

 ThreadHist<TH1D *>* LowR21CRPolarized_Data;

 ThreadHist<TH1D *>* LowPtZCRPolarized_Data;

 ThreadHist<TH1D *>* HighPtZCRPolarized_Data;

 ThreadHist<TH1D *>* PtWZ10CRPolarized_Data;

 ThreadHist<TH1D *>* PtWZ20CRPolarized_Data;

 ThreadHist<TH1D *>* PtWZ40CRPolarized_Data;

 ThreadHist<TH1D *>* TopEnrichCR_Data;

 ThreadHist<TH1D *>* ZjetEnrichCR_Data;

 ThreadHist<TH1D *>* ZFakeElCR_Data;

 ThreadHist<TH1D *>* ZFakeMuCR_Data;

 ThreadHist<TH1D *>* TopElCR_Data;

 ThreadHist<TH1D *>* TopMuCR_Data;

//Final Data(Data - Bkg)
 TH1D* Inclusive_FinalData;
 TH1D* Signal_FinalData;
 TH1D* HighPtWZCR_FinalData;
 TH1D* LowPtZCR_FinalData;

//Final TT(Data - Bkg - LL - LT - TL)
 TH1D* PtWZ10CR_FinalTT;
 TH1D* PtWZ20CR_FinalTT;
 TH1D* PtWZ40CR_FinalTT;
 TH1D* LowPtWZCR_FinalTT;

//Fake
 ThreadHist<FakeHist *>* Inclusive_Fake;

 ThreadHist<FakeHist *>* Signal_Fake;

 ThreadHist<FakeHist *>* SignalPtWZ_Fake;

 ThreadHist<FakeHist *>* ZZCR_Fake;

 ThreadHist<FakeHist *>* TopCR_Fake;

 ThreadHist<FakeHist *>* HighPtWZCR_Fake;

 ThreadHist<FakeHist *>* LowPtWZCR_Fake;

 ThreadHist<FakeHist *>* HighR21CR_Fake;

 ThreadHist<FakeHist *>* LowR21CR_Fake;

 ThreadHist<FakeHist *>* LowPtZCR_Fake;

 ThreadHist<FakeHist *>* HighPtZCR_Fake;

 ThreadHist<FakeHist *>* PtWZ10CR_Fake;

 ThreadHist<FakeHist *>* PtWZ20CR_Fake;

 ThreadHist<FakeHist *>* PtWZ40CR_Fake;

 ThreadHist<FakeHist *>* WZInclusiveNoMETCR_Fake;

 ThreadHist<FakeHist *>* ZFakeElCR_Fake;

 ThreadHist<FakeHist *>* ZFakeMuCR_Fake;

 ThreadHist<FakeHist *>* TopEnrichCR_Fake;

 ThreadHist<FakeHist *>* ZjetEnrichCR_Fake;

 ThreadHist<FakeHist *>* TopElCR_Fake;

 ThreadHist<FakeHist *>* TopMuCR_Fake;

//WZQCD systematic
 ThreadHist<SysHist *>* InclusivePolarized_sys;

 ThreadHist<SysHist *>* SignalPolarized_sys;

 ThreadHist<SysHist *>* ZZCRPolarized_sys;

 ThreadHist<SysHist *>* TopCRPolarized_sys;

 ThreadHist<SysHist *>* HighPtWZCRPolarized_sys;

 ThreadHist<SysHist *>* LowPtZCRPolarized_sys;

//All Bkg
 ThreadHist<BkgHist *>* Inclusive_bkg;

 ThreadHist<BkgHist *>* Signal_bkg;

 ThreadHist<BkgHist *>* SignalPtWZ_bkg;

 ThreadHist<BkgHist *>* ZZCR_bkg;

 ThreadHist<BkgHist *>* TopCR_bkg;

 ThreadHist<BkgHist *>* HighPtWZCR_bkg;

 ThreadHist<BkgHist *>* LowPtWZCR_bkg;

 ThreadHist<BkgHist *>* HighR21CR_bkg;

 ThreadHist<BkgHist *>* LowR21CR_bkg;

 ThreadHist<BkgHist *>* LowPtZCR_bkg;

 ThreadHist<BkgHist *>* HighPtZCR_bkg;

 ThreadHist<BkgHist *>* PtWZ10CR_bkg;

 ThreadHist<BkgHist *>* PtWZ20CR_bkg;

 ThreadHist<BkgHist *>* PtWZ40CR_bkg;

 ThreadHist<BkgHist *>* WZInclusiveNoMETCR_bkg;

 ThreadHist<BkgHist *>* ZFakeElCR_bkg;

 ThreadHist<BkgHist *>* ZFakeMuCR_bkg;

 ThreadHist<BkgHist *>* TopEnrichCR_bkg;

 ThreadHist<BkgHist *>* ZjetEnrichCR_bkg;

 ThreadHist<BkgHist *>* TopElCR_bkg;

 ThreadHist<BkgHist *>* TopMuCR_bkg;

//All Bkg with systematic

 ProcessHist();
 virtual void Initial(int iThread, int MCType);
 virtual void Fill(int iThread, double par, double weight, EventWZPolarization ProcessEvent);
 virtual void FillFake(int iThread, double par, double weight, EventWZPolarization ProcessEvent);
 virtual void FillTruth(int iThread, double par, double weight, EventWZPolarization ProcessEvent);
 virtual void InputReweightingFactor(int iThread, double weight);
 virtual void ResetHist();
 virtual void GetFinalData();


 bool OnlyNominal[100] = {true};
 bool doBkg[100] = {false};
 bool doControlRegion[100] = {false};
 int doFakeRate[100] = {0};

 HistsWZPolarization *fHist;
 int TotalThread;

 int MCType[100] = {0};
 bool isData[100] = {false};
 bool isSignal[100] = {false};

 TString HistName = "";
 TString SystematicName = "";

 double ReweightingFactor[100] = {1.0};

 double NLOKFactor = 1.0;
 double NLOKFactor_ZZCR = 1.0;
 double NLOKFactor_HighPtZCR = 1.0;
 double NLOKFactor_Signal = 1.0;
 double NLOKFactor_SignalPtWZ = 1.0;
 double NLOKFactor_HighPtWZCR = 1.0;
 double NLOKFactor_LowPtWZCR = 1.0;
 double NLOKFactor_HighR21CR = 1.0;
 double NLOKFactor_LowR21CR = 1.0;

 double NLOKFactorError = 0.0;
 double NLOKFactorError_ZZCR = 0.0;
 double NLOKFactorError_HighPtZCR = 0.0;
 double NLOKFactorError_Signal = 0.0;
 double NLOKFactorError_SignalPtWZ = 0.0;
 double NLOKFactorError_HighPtWZCR = 0.0;
 double NLOKFactorError_LowPtWZCR = 0.0;
 double NLOKFactorError_HighR21CR = 0.0;
 double NLOKFactorError_LowR21CR = 0.0;


 virtual void InputNLOKFactor(double Inclusive, double ZZ, double HighPtZ, double Signal, double SignalPtWZ, double HighPtWZ, double LowPtWZ, double HighR21, double LowR21)
 {
   this->NLOKFactor = Inclusive;
   this->NLOKFactor_ZZCR = ZZ;
   this->NLOKFactor_HighPtZCR = HighPtZ;
   this->NLOKFactor_Signal = Signal;
   this->NLOKFactor_SignalPtWZ = SignalPtWZ;
   this->NLOKFactor_HighPtWZCR = HighPtWZ;
   this->NLOKFactor_LowPtWZCR = LowPtWZ;
   this->NLOKFactor_HighR21CR = HighR21;
   this->NLOKFactor_LowR21CR = LowR21;
 }

 double LLNLOWeight[100] = {1.0};
 double LTNLOWeight[100] = {1.0};
 double TLNLOWeight[100] = {1.0};
 double TTNLOWeight[100] = {1.0};
 virtual void InputNLOWeight(int iThread, double LLNLOWeight, double LTNLOWeight, double TLNLOWeight, double TTNLOWeight){
   this->LLNLOWeight[iThread - 1] = LLNLOWeight;
   this->LTNLOWeight[iThread - 1] = LTNLOWeight;
   this->TLNLOWeight[iThread - 1] = TLNLOWeight;
   this->TTNLOWeight[iThread - 1] = TTNLOWeight;
 }

};


class HistsWZPolarization : public makeHists
{
 friend class ProcessHist;

 TreeForWZPolarization *fTree;

 public:

 ProcessHist *M_WZ;
 ProcessHist *M_3l;
 ProcessHist *Mt_WZ;
 ProcessHist *M_Z;
 ProcessHist *Mt_W;
 ProcessHist *Met;
 ProcessHist *Njets;
 ProcessHist *NBjets;
 ProcessHist *Lep1Pt;
 ProcessHist *Lep2Pt;
 ProcessHist *Lep3Pt;
 ProcessHist *Lep1Eta;
 ProcessHist *Lep2Eta;
 ProcessHist *Lep3Eta;
 ProcessHist *Lep1Phi;
 ProcessHist *Lep2Phi;
 ProcessHist *Lep3Phi;
 ProcessHist *LepPt;
 ProcessHist *LepEta;
 ProcessHist *LepPhi;
 ProcessHist *Lep2Pt_mmm;
 ProcessHist *Lep2Pt_mme;
 ProcessHist *Lep2Pt_eem;
 ProcessHist *Lep2Pt_eee;
 ProcessHist *Lep3Pt_mmm;
 ProcessHist *Lep3Pt_mme;
 ProcessHist *Lep3Pt_eem;
 ProcessHist *Lep3Pt_eee;
 ProcessHist *Lep3Eta_mmm;
 ProcessHist *Lep3Eta_mme;
 ProcessHist *Lep3Eta_eem;
 ProcessHist *Lep3Eta_eee;
 ProcessHist *Mt_W_mmm;
 ProcessHist *Mt_W_mme;
 ProcessHist *Mt_W_eem;
 ProcessHist *Mt_W_eee;
 ProcessHist *Met_mmm;
 ProcessHist *Met_mme;
 ProcessHist *Met_eem;
 ProcessHist *Met_eee;
 //ProcessHist *Mpx;
 //ProcessHist *Mpy;
 //ProcessHist *Mpz;
 ProcessHist *LWTNNNuPz;
 ProcessHist *TruthNuPz;
// ProcessHist *MpzDiff;
// ProcessHist *LWTNNNuPzDiff;
 ProcessHist *LWTNNpLL;
 ProcessHist *LWTNNpLT;
 ProcessHist *LWTNNpTL;
 ProcessHist *LWTNNpTT;
 ProcessHist *Pt_W;
 ProcessHist *Pt_Z;
 ProcessHist *Pt_Z_mmm;
 ProcessHist *Pt_Z_mme;
 ProcessHist *Pt_Z_eem;
 ProcessHist *Pt_Z_eee;
 ProcessHist *Pt_WZ;
 ProcessHist *SumJetPt;
 ProcessHist *CosThetaV;
 ProcessHist *CosThetaVAbs;
 ProcessHist *CosThetaV_WLZL;
 ProcessHist *CosThetaV_WLZH;
 ProcessHist *CosThetaV_WHZL;
 ProcessHist *CosThetaV_WHZH;
 ProcessHist *CosThetaLepW;
 ProcessHist *CosThetaLepZ;
 ProcessHist *DY_WZ;
 ProcessHist *DY_3Z;
 ProcessHist *DY_3N;
 ProcessHist *DY_WPlusZ;
 ProcessHist *DY_WMinusZ;
 ProcessHist *DY_3PlusZ;
 ProcessHist *DY_3MinusZ;
 ProcessHist *DeltaPhiLepWLepZ;
 ProcessHist *DeltaPhiLepWLepZ_WLZL;
 ProcessHist *DeltaPhiLepWLepZ_WLZH;
 ProcessHist *DeltaPhiLepWLepZ_WHZL;
 ProcessHist *DeltaPhiLepWLepZ_WHZH;
 ProcessHist *DeltaPhiLepWLepZWZFrame;
 ProcessHist *DeltaPhiLepWLepZWZFrame_WLZL;
 ProcessHist *DeltaPhiLepWLepZWZFrame_WLZH;
 ProcessHist *DeltaPhiLepWLepZWZFrame_WHZL;
 ProcessHist *DeltaPhiLepWLepZWZFrame_WHZH;
 ProcessHist *R21;
 //ProcessHist *R21_WLZL;
 //ProcessHist *R21_WLZH;
 //ProcessHist *R21_WHZL;
 //ProcessHist *R21_WHZH;
 ProcessHist *Channel;
 ProcessHist *BDTScore;
 ProcessHist *BDTScore_WLZL;
 ProcessHist *BDTScore_WLZH;
 ProcessHist *BDTScore_WHZL;
 ProcessHist *BDTScore_WHZH;
 ProcessHist *BDTScoreSR;
 ProcessHist *BDTScoreSR_WLZL;
 ProcessHist *BDTScoreSR_WLZH;
 ProcessHist *BDTScoreSR_WHZL;
 ProcessHist *BDTScoreSR_WHZH;
 ProcessHist *BDTScoreSR100;
 ProcessHist *RightZYWLepEta;
 ProcessHist *WrongZYWLepEta;
 ProcessHist *WDecayStatus;
 ProcessHist *ZDecayStatus;

 ThreadHist<TH1D *>* MpzDiff;

 ThreadHist<TH1D *>* LWTNNNuPzDiff;

 ThreadHist<TH1D *>* Event_CutFlow;

 ThreadHist<BkgHist *>* Yield_CutFlow_bkg;

 ThreadHist<BkgHist *>* NormalizedYield_CutFlow_bkg;

 ThreadHist<BkgHist *>* Polarized_CutFlow_bkg;


 double NLOKFactor = 1.0;
 double NLOKFactor_ZZCR = 1.0;
 double NLOKFactor_HighPtZCR = 1.0;
 double NLOKFactor_Signal = 1.0;
 double NLOKFactor_SignalPtWZ = 1.0;
 double NLOKFactor_HighPtWZCR = 1.0;
 double NLOKFactor_LowPtWZCR = 1.0;
 double NLOKFactor_HighR21CR = 1.0;
 double NLOKFactor_LowR21CR = 1.0;

 double NLOKFactorError = 0.0;
 double NLOKFactorError_ZZCR = 0.0;
 double NLOKFactorError_HighPtZCR = 0.0;
 double NLOKFactorError_Signal = 0.0;
 double NLOKFactorError_SignalPtWZ = 0.0;
 double NLOKFactorError_HighPtWZCR = 0.0;
 double NLOKFactorError_LowPtWZCR = 0.0;
 double NLOKFactorError_HighR21CR = 0.0;
 double NLOKFactorError_LowR21CR = 0.0;


 TH1D* ReweightFactor;
 TH1D* ReweightFactor_Truth;

 ThreadHist<BkgHist *>* BkgYield_bkg;

 ThreadHist<BkgHist *>* PolarizedYield_bkg;

 ThreadHist<BkgHist *>* PolarizedYield_ZZCR_bkg;

 ThreadHist<BkgHist *>* PolarizedYield_HighPtZCR_bkg;

 ThreadHist<BkgHist *>* PolarizedYield_Signal_bkg;

 ThreadHist<BkgHist *>* PolarizedYield_SignalPtWZ_bkg;

 ThreadHist<BkgHist *>* PolarizedYield_HighPtWZCR_bkg;

 ThreadHist<BkgHist *>* PolarizedYield_LowPtWZCR_bkg;

 ThreadHist<BkgHist *>* PolarizedYield_HighR21CR_bkg;

 ThreadHist<BkgHist *>* PolarizedYield_LowR21CR_bkg;


 ThreadHist<TH1D *>* LeptonCount;


 TH1D* Ratio_Inclusive;
 TH1D* Ratio_Signal;
 TH1D* Ratio_HighPtWZCR;
 TH1D* Ratio_LowPtZCR;


//Fake Rate
 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_PassZ;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_UpSys_PassZ;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_DownSys_PassZ;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeMu_PassZ;

 ThreadHist<TH1D *>* Lep3Pt_TopEl_PassZ;

 ThreadHist<TH1D *>* Lep3Pt_TopMu_PassZ;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_PassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_UpSys_PassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_DownSys_PassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeMu_PassW;

 ThreadHist<TH1D *>* Lep3Pt_TopEl_PassW;

 ThreadHist<TH1D *>* Lep3Pt_TopMu_PassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_UnPassZ;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_UpSys_UnPassZ;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_DownSys_UnPassZ;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeMu_UnPassZ;

 ThreadHist<TH1D *>* Lep3Pt_TopEl_UnPassZ;

 ThreadHist<TH1D *>* Lep3Pt_TopMu_UnPassZ;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_UnPassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_UpSys_UnPassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_DownSys_UnPassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeMu_UnPassW;

 ThreadHist<TH1D *>* Lep3Pt_TopEl_UnPassW;

 ThreadHist<TH1D *>* Lep3Pt_TopMu_UnPassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_Loose;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_UpSys_Loose;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_DownSys_Loose;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeMu_Loose;

 ThreadHist<TH1D *>* Lep3Pt_TopEl_Loose;

 ThreadHist<TH1D *>* Lep3Pt_TopMu_Loose;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_PassMedium;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeMu_PassMedium;

 ThreadHist<TH1D *>* Lep3Pt_TopEl_PassMedium;

 ThreadHist<TH1D *>* Lep3Pt_TopMu_PassMedium;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_PassTight;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeMu_PassTight;

 ThreadHist<TH1D *>* Lep3Pt_TopEl_PassTight;

 ThreadHist<TH1D *>* Lep3Pt_TopMu_PassTight;

 //Fake rate correction
 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_LargeMtW_PassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_LargeMtW_UnPassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeMu_LargeMtW_PassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeMu_LargeMtW_UnPassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_LowMtW_PassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeEl_LowMtW_UnPassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeMu_LowMtW_PassW;

 ThreadHist<TH1D *>* Lep3Pt_ZFakeMu_LowMtW_UnPassW;

 //Real Efficiency
 ThreadHist<TH1D *>* Lep3Pt_RealEl_PassZ;

 ThreadHist<TH1D *>* Lep3Pt_RealEl_UnPassZ;

 ThreadHist<TH1D *>* Lep3Pt_RealEl_PassW;

 ThreadHist<TH1D *>* Lep3Pt_RealEl_UnPassW;

 ThreadHist<TH1D *>* Lep3Pt_RealEl_Loose;

 ThreadHist<TH1D *>* Lep3Pt_RealMu_PassZ;

 ThreadHist<TH1D *>* Lep3Pt_RealMu_UnPassZ;

 ThreadHist<TH1D *>* Lep3Pt_RealMu_PassW;

 ThreadHist<TH1D *>* Lep3Pt_RealMu_UnPassW;

 ThreadHist<TH1D *>* Lep3Pt_RealMu_Loose;

 //Lepton2 Fake rate
 ThreadHist<TH1D *>* Lep2Pt_ZFakeEl_PassZ;

 ThreadHist<TH1D *>* Lep2Pt_ZFakeMu_PassZ;

 ThreadHist<TH1D *>* Lep2Pt_TopEl_PassZ;

 ThreadHist<TH1D *>* Lep2Pt_TopMu_PassZ;

 ThreadHist<TH1D *>* Lep2Pt_ZFakeEl_UnPassZ;

 ThreadHist<TH1D *>* Lep2Pt_ZFakeMu_UnPassZ;

 ThreadHist<TH1D *>* Lep2Pt_TopEl_UnPassZ;

 ThreadHist<TH1D *>* Lep2Pt_TopMu_UnPassZ;


 //Lepton3 MET distribution
 ThreadHist<TH1D *>* Lep3MET_ZFakeEl_PassW;

 ThreadHist<TH1D *>* Lep3MET_ZFakeEl_UnPassW;

 ThreadHist<TH1D *>* Lep3MET_ZFakeMu_PassW;

 ThreadHist<TH1D *>* Lep3MET_ZFakeMu_UnPassW;

 ThreadHist<TH2D *>* Lep3PtMET_ZFakeEl_PassW;

 ThreadHist<TH2D *>* Lep3PtMET_ZFakeEl_UnPassW;

 ThreadHist<TH2D *>* Lep3PtMET_ZFakeMu_PassW;

 ThreadHist<TH2D *>* Lep3PtMET_ZFakeMu_UnPassW;

 ThreadHist<TH1D *>* AverageLep3Pt_Lep3MET_ZFakeEl_Loose_numer;
 ThreadHist<TH1D *>* AverageLep3Pt_Lep3MET_ZFakeEl_Loose_denom;
 TH1D* AverageLep3Pt_Lep3MET_ZFakeEl_Loose;

 ThreadHist<TH1D *>* AverageLep3Pt_Lep3MET_ZFakeMu_Loose_numer;
 ThreadHist<TH1D *>* AverageLep3Pt_Lep3MET_ZFakeMu_Loose_denom;
 TH1D* AverageLep3Pt_Lep3MET_ZFakeMu_Loose;

 ThreadHist<TH1D *>* AverageLep3Pt_Lep3MET_ZFakeEl_PassW_numer;
 TH1D* AverageLep3Pt_Lep3MET_ZFakeEl_PassW;
 
 ThreadHist<TH1D *>* AverageLep3Pt_Lep3MET_ZFakeMu_PassW_numer;
 TH1D* AverageLep3Pt_Lep3MET_ZFakeMu_PassW;

 ThreadHist<TH1D *>* AverageLep3Pt_Lep3MET_ZFakeEl_UnPassW_numer;
 TH1D* AverageLep3Pt_Lep3MET_ZFakeEl_UnPassW;

 ThreadHist<TH1D *>* AverageLep3Pt_Lep3MET_ZFakeMu_UnPassW_numer;
 TH1D* AverageLep3Pt_Lep3MET_ZFakeMu_UnPassW;


 TH1D *ZElFakeRate;
 TH1D *ZMuFakeRate;
 TH1D *WElFakeRate;
 TH1D *WMuFakeRate;

 TH1D *ZElFakeRate_UpSys;
 TH1D *ZMuFakeRate_UpSys;
 TH1D *WElFakeRate_UpSys;
 TH1D *WMuFakeRate_UpSys;

 TH1D *ZElFakeRate_DownSys;
 TH1D *ZMuFakeRate_DownSys;
 TH1D *WElFakeRate_DownSys;
 TH1D *WMuFakeRate_DownSys;

 TH1D *ZElFakeEff;
 TH1D *ZMuFakeEff;
 TH1D *WElFakeEff;
 TH1D *WMuFakeEff;

 TH1D *ZElRealEff;
 TH1D *ZMuRealEff;
 TH1D *WElRealEff;
 TH1D *WMuRealEff;

 TH1D *ZFakeElCR_ZRate;
 TH1D *ZFakeElCR_UpSys_ZRate;
 TH1D *ZFakeElCR_DownSys_ZRate;
 TH1D *ZFakeElCR_WRate;
 TH1D *ZFakeElCR_UpSys_WRate;
 TH1D *ZFakeElCR_DownSys_WRate;
 TH1D *ZFakeMuCR_ZRate;
 TH1D *ZFakeMuCR_WRate;
 TH1D *TopElCR_ZRate;
 TH1D *TopElCR_WRate;
 TH1D *TopMuCR_ZRate;
 TH1D *TopMuCR_WRate;

 TH1D *ZFakeElCR_ZRate2;
 TH1D *ZFakeMuCR_ZRate2;
 TH1D *TopElCR_ZRate2;
 TH1D *TopMuCR_ZRate2;

 TH1D *ZFakeElCR_MET_WRate;
 TH1D *ZFakeMuCR_MET_WRate;

 TH2D *ZFakeElCR_PtMET_WRate;
 TH2D *ZFakeMuCR_PtMET_WRate;

 TH1D *ZFakeEl_LargeMtW;
 TH1D *ZFakeMu_LargeMtW;
 TH1D *ZFakeEl_LowMtW;
 TH1D *ZFakeMu_LowMtW;
 TH1D *ZFakeEl_Correction;
 TH1D *ZFakeMu_Correction;

 TH1D *Deep_DY_WZ_TT;
 TH1D *Deep_DY_3Z_TT;

 TH1D *Deep_DY_WZ_TT_DataSubtracted;
 TH1D *Deep_DY_3Z_TT_DataSubtracted;

 int M_WZ_bin = 20;          double M_WZ_left = 0.0;           double M_WZ_right = 500.0;
 int M_3l_bin = 20;          double M_3l_left = 0.0;           double M_3l_right = 200.0;
 int Mt_WZ_bin = 20;         double Mt_WZ_left = 0.0;          double Mt_WZ_right = 500.0;
 int M_Z_bin = 20;           double M_Z_left = 0.0;            double M_Z_right = 200.0;
 int Mt_W_bin = 20;          double Mt_W_left = 0.0;           double Mt_W_right = 200.0;
 int Met_bin = 40;           double Met_left = 20.0;           double Met_right = 420.0;
 int Njets_bin = 10;         double Njets_left = 0.0;          double Njets_right = 10.0;
 int NBjets_bin = 6;         double NBjets_left = 0.0;         double NBjets_right = 6.0;
 int Lep1Pt_bin = 40;        double Lep1Pt_left = 20.0;        double Lep1Pt_right = 420.0;
 int Lep2Pt_bin = 40;        double Lep2Pt_left = 20.0;        double Lep2Pt_right = 420.0;
 int Lep3Pt_bin = 40;        double Lep3Pt_left = 20.0;        double Lep3Pt_right = 420.0;
 int Lep1Eta_bin = 20;       double Lep1Eta_left = -2.5;       double Lep1Eta_right = 2.5;
 int Lep2Eta_bin = 20;       double Lep2Eta_left = -2.5;       double Lep2Eta_right = 2.5;
 int Lep3Eta_bin = 20;       double Lep3Eta_left = -2.5;       double Lep3Eta_right = 2.5;
 int Lep1Phi_bin = 20;       double Lep1Phi_left = -3.14;      double Lep1Phi_right = 3.14;
 int Lep2Phi_bin = 20;       double Lep2Phi_left = -3.14;      double Lep2Phi_right = 3.14;
 int Lep3Phi_bin = 20;       double Lep3Phi_left = -3.14;      double Lep3Phi_right = 3.14;
 int Mpx_bin = 20;           double Mpx_left = 0.0;            double Mpx_right = 200.0;
 int Mpy_bin = 20;           double Mpy_left = 0.0;            double Mpy_right = 200.0;
 int Mpz_bin = 20;           double Mpz_left = 0.0;            double Mpz_right = 200.0;
 int MpzDiff_bin = 20;       double MpzDiff_left = 0.0;        double MpzDiff_right = 200.0;
 int LWTNNpLL_bin = 20;      double LWTNNpLL_left = 0.0;       double LWTNNpLL_right = 1.0;
 int Pt_W_bin = 60;          double Pt_W_left = 0.0;           double Pt_W_right = 600.0;
 int Pt_Z_bin = 7;          double Pt_Z_left = 0.0;           double Pt_Z_right = 200.0;
 int Pt_WZ_bin = 20;         double Pt_WZ_left = 0.0;          double Pt_WZ_right = 200.0;
 int SumJetPt_bin = 20;      double SumJetPt_left = 0.0;       double SumJetPt_right = 200.0;
 int CosThetaV_bin = 40;     double CosThetaV_left = -1.0;     double CosThetaV_right = 1.0;
 int CosThetaVAbs_bin = 20;  double CosThetaVAbs_left = 0.0;   double CosThetaVAbs_right = 1.0;
 int CosThetaLepW_bin = 20;  double CosThetaLepW_left = -1.0;  double CosThetaLepW_right = 1.0;
 int CosThetaLepZ_bin = 20;  double CosThetaLepZ_left = -1.0;  double CosThetaLepZ_right = 1.0;
 int DY_WZ_bin = 10;         double DY_WZ_left = -6.0;         double DY_WZ_right = 6.0;
 int DY_3Z_bin = 20;         double DY_3Z_left = -6.0;         double DY_3Z_right = 6.0;
 int DY_3N_bin = 20;         double DY_3N_left = -6.0;         double DY_3N_right = 6.0;
 int Truth_Pt_WZ_bin = 20;   double Truth_Pt_WZ_left = 0.0;    double Truth_Pt_WZ_right = 200000.0;
 int DeltaPhi_bin = 20;      double DeltaPhi_left = 0.0;       double DeltaPhi_right = 3.14;
 int R21_bin = 20;           double R21_left = 0.0;            double R21_right = 1.0;
 int Channel_bin = 6;        double Channel_left = 0.0;        double Channel_right = 6.0;
 int BDTScore_bin = 20;      double BDTScore_left = 0.0;       double BDTScore_right = 1.0;
 int EtaDiff_bin = 5;        double EtaDiff_left = 0.0;        double EtaDiff_right = 2.5;

 double Pt_Z_binning[32] = {0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 320, 340, 360, 380, 400, 
                            420, 440, 460, 480, 500, 550, 600, 700, 800, 900, 1000};
// int FakeEl_bin = 5;         double FakeEl_binning[6] = {15, 25, 35, 60, 100, 1000};
// int FakeMu_bin = 5;         double FakeMu_binning[6] = {15, 25, 35, 60, 100, 1000};
// int FakeEl_bin = 9;         double FakeEl_binning[10] = {15, 20, 22, 24, 26, 28, 30, 35, 60, 1000};
// int FakeMu_bin = 9;         double FakeMu_binning[10] = {15, 20, 22, 24, 26, 28, 30, 35, 60, 1000};
// int FakeEl_bin = 4;         double FakeEl_binning[5] = {15, 25, 35, 60, 1000};
// int FakeMu_bin = 4;         double FakeMu_binning[5] = {15, 25, 35, 60, 1000};
// int FakeEl_bin = 1;         double FakeEl_binning[2] = {0, 10000};
// int FakeMu_bin = 1;         double FakeMu_binning[2] = {0, 10000};
 int FakeEl_bin = 4;         double FakeEl_binning[5] = {15, 20, 30, 50, 200};
 int FakeMu_bin = 4;         double FakeMu_binning[5] = {15, 20, 30, 50, 200};
 int FakeEl1_bin = 8;         double FakeEl1_binning[9] = {15, 20, 25, 30, 35, 40, 50, 70, 200};
 int FakeMu1_bin = 8;         double FakeMu1_binning[9] = {15, 20, 25, 30, 35, 40, 50, 70, 200};
// int FakeEl_bin = 5;         double FakeEl_binning[6] = {15, 20, 30, 50, 200, 10000};
// int FakeMu_bin = 5;         double FakeMu_binning[6] = {15, 20, 30, 50, 200, 10000};
// int FakeEl_bin = 8;         double FakeEl_binning[9] = {15, 20, 30, 50, 70, 90, 120, 160, 200};
// int FakeMu_bin = 8;         double FakeMu_binning[9] = {15, 20, 30, 50, 70, 90, 120, 160, 200};


// int FakeEl_bin = 3;         double FakeEl_binning[4] = {15, 60, 100, 10000};
// int FakeMu_bin = 3;         double FakeMu_binning[4] = {15, 60, 100, 10000};

// int FakeMET_bin = 10;       double FakeMET_binning[11] = {0, 5, 10, 25, 35, 45, 55, 70, 80, 100, 200};
// int FakeMET_bin = 2;       double FakeMET_binning[3] = {0, 25, 200};
 int FakeMET_bin = 8;       double FakeMET_binning[9] = {0, 10, 20, 30, 40, 50, 60, 70, 80};
// int FakeMET_bin = 2;       double FakeMET_binning[3] = {0, 30, 80};


 int FakeElCorrection_bin = 4;  double FakeElCorrection_binning[5] = {15, 20, 30, 50, 200};
 int FakeMuCorrection_bin = 4;  double FakeMuCorrection_binning[5] = {15, 20, 30, 50, 200};
// int FakeElCorrection_bin = 1;  double FakeElCorrection_binning[2] = {0, 10000};
// int FakeMuCorrection_bin = 1;  double FakeMuCorrection_binning[2] = {0, 10000};



 vector<ProcessHist *> hist_process;
 vector<TString> HistNames;

//member function
 vector<TString> sysName;
 HistsWZPolarization();
 virtual void bookHists(int TotalThread);
 virtual void bookProcessHists(TString ProcessName, TString subName);
 virtual void GetReweightFactor();
 virtual void GetFakeRate();
 virtual void LinkClass(HistsWZPolarization *hist);
 virtual void outputInformation();
 virtual void bookAllProcessHist(ProcessHist* &hist, TString name, TString title, int nbin, double left, double right);
 virtual void bookAllProcessHist(ProcessHist* &hist, TString name, TString title, int nbin, double* xbins);
 virtual void DefineHist(ProcessHist* &hist, TString name, TString title, int nbin, double left, double right);
 virtual void DefineHist(ProcessHist* &hist, TString name, TString title, int nbin, double* xbins);
 virtual void CustomMerge(int TotalThread, int notDelete = 0){};
 virtual void CustomReset(int TotalThread){};
 virtual void SaveCustomFakePlot();
 virtual void InputCustomFakeRate();
 virtual void outputTeXInfo();

// template<class T>

 vector<TString> SysNameSignalWZ;
 vector<TString> BkgNameSignalWZ;
 map<TString, int> SysNameIndexSignalWZ;
 map<TString, int> BkgNameIndexSignalWZ;

 vector<TString> BkgNameZZControlRegion;
 map<TString, int> BkgNameIndexZZControlRegion;
 vector<TString> BkgNameTopControlRegion;
 map<TString, int> BkgNameIndexTopControlRegion;
 vector<TString> BkgNameWZPolarized;
 map<TString, int> BkgNameIndexWZPolarized;

 TString SystematicName = "";

 void InputSystematicName(TString SystematicName);
 virtual int FindSysIndex(TString SysName, TString ProcessName);
 virtual void DefineSysName(int index, TString Name, TString ProcessName);
 virtual void InitialSysName(TString ProcessName);
 virtual void InitialBkgName(TString ProcessName);

 bool OnlyNominal = true;
 virtual void RunAllSystematic(){OnlyNominal = false;}

 bool doBkg = false;
 virtual void RunBkg(){doBkg = true;}

 bool doControlRegion = false;
 virtual void RunControlRegion(){doControlRegion = true;}

 int doFakeRate = 0;
 virtual void RunFakeRate(int doFakeRate){this->doFakeRate = doFakeRate;}

 bool isHaveFakeRate = false;

 bool isRunReweightingFactor = false;
 bool isHaveReweightingFactor = false;

 map<TString, ofstream> TeXInfo;
};

#ifdef HistsWZPolarization_cxx
HistsWZPolarization* FinalHists;
double Min_Chi2 = 1000000.0;
#endif
void ScaleFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);

#endif
