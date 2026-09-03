#ifndef __HISTS_RESBOSWTEV_H_
#define __HISTS_RESBOSWTEV_H_
#include <iostream>
#include <fstream>
#include <string>
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

using namespace std;

class HistsResBosWTev : public makeHists
{
 public:

 ifstream infile;

 ThreadHist<TH1D *>* LeptonEta_w225;
 ThreadHist<TH1D *>* AntiLeptonEta_w225;

 ThreadHist<TH1D *>* LeptonEta_w227;
 ThreadHist<TH1D *>* AntiLeptonEta_w227;

 ThreadHist<TH1D *>* LeptonEta_w234;
 ThreadHist<TH1D *>* AntiLeptonEta_w234;

 ThreadHist<TH1D *>* LeptonEta_w281;
 ThreadHist<TH1D *>* AntiLeptonEta_w281;

 ThreadHist<TH1D *>* WPlusRapidity;

 ThreadHist<TH1D *>* WPlusPt;

 ThreadHist<TH1D *>* WMinusRapidity;

 ThreadHist<TH1D *>* WMinusPt;

 ThreadHist<TH1D *>* LeptonEta;

 ThreadHist<TH1D *>* AntiLeptonEta;

 ThreadHist<TH1D *>* LeptonPt;

 ThreadHist<TH1D *>* AntiLeptonPt;

 ThreadHist<TH1D *>* MtW_CDF;

 ThreadHist<TH1D *>* LeptonPt_CDF;

 ThreadHist<TH1D *>* NuPt_CDF;

 ThreadHist<TH1D *>* LeptonPt_WPlus_CDF;

 ThreadHist<TH1D *>* NuPt_WPlus_CDF;

 ThreadHist<TH1D *>* LeptonPt_WMinus_CDF;

 ThreadHist<TH1D *>* NuPt_WMinus_CDF;

 ThreadHist<TH1D *>* DeltaPhi_CDF;

 ThreadHist<TH1D *>* WPt_CDF;

 ThreadHist<TH1D *>* ZPt_CDF;

 ThreadHist<TH1D *>* WPt_CDF_FineBin;

 ThreadHist<TH1D *>* ZPt_CDF_FineBin;

 ThreadHist<TH1D *>* WPt_CDF_ScaleUp;

 ThreadHist<TH1D *>* WPt_CDF_ScaleDown;

 ThreadHist<TH1D *>* WPt_CDF_ScaleVari;

 ThreadHist<TH1D *>* WPt_Inclusive_LargeRange;

 ThreadHist<TH1D *>* ZPt_Inclusive_LargeRange;

 ThreadHist<TH1D *>* MtW_CDF_Smear;

 ThreadHist<TH1D *>* LeptonPt_CDF_Smear;

 ThreadHist<TH1D *>* NuPt_CDF_Smear;

 ThreadHist<TH1D *>* DeltaPhi_CDF_Smear;

 ThreadHist<TH1D *>* WPt_CDF_Smear;

 ThreadHist<TH1D *>* ZPt_CDF_Smear;

 ThreadHist<TH1D *>* MtW_Inclusive;

 ThreadHist<TH1D *>* LeptonPt_Inclusive;

 ThreadHist<TH1D *>* NuPt_Inclusive;

 ThreadHist<TH1D *>* LeptonPt_WPlus_Inclusive;

 ThreadHist<TH1D *>* NuPt_WPlus_Inclusive;

 ThreadHist<TH1D *>* LeptonPt_WMinus_Inclusive;

 ThreadHist<TH1D *>* NuPt_WMinus_Inclusive;

 ThreadHist<TH1D *>* LeptonEta_WPlus_Inclusive;

 ThreadHist<TH1D *>* NuEta_WPlus_Inclusive;

 ThreadHist<TH1D *>* LeptonEta_WMinus_Inclusive;

 ThreadHist<TH1D *>* NuEta_WMinus_Inclusive;

 ThreadHist<TH1D *>* DeltaPhi_Inclusive;

 ThreadHist<TH1D *>* WPt_Inclusive;

 ThreadHist<TH1D *>* ZPt_Inclusive;

 ThreadHist<TH1D *>* MtW_EventCount;

 ThreadHist<TH1D *>* MtW_Smear_EventCount;

 ThreadHist<TH1D *>* MtW_new_CDF;
 ThreadHist<TH1D *>* MtW_new_CDF_Smear;

 ThreadHist<MultiWeightHist *>* LeptonPt_LHC_Low_multiweight;
 ThreadHist<MultiWeightHist *>* LeptonPt_LHC_High_multiweight;
 ThreadHist<MultiWeightHist *>* LeptonPt_LowQT_LHC_Low_multiweight;
 ThreadHist<MultiWeightHist *>* LeptonPt_LowQT_LHC_High_multiweight;
 ThreadHist<TH1D *>* LeptonPt_LHC;
 ThreadHist<TH1D *>* LeptonPt_LHC_WPlus;
 ThreadHist<TH1D *>* LeptonPt_LHC_WMinus;
 ThreadHist<TH1D *>* LeptonPt_LHC_Low;
 ThreadHist<TH1D *>* LeptonPt_LHC_High;
 ThreadHist<TH1D *>* LeptonPt_LowQT_LHC;
 ThreadHist<TH1D *>* LeptonPt_LowQT_LHC_Tail;
 ThreadHist<TH1D *>* LeptonPt_LowQT_LHC_Low;
 ThreadHist<TH1D *>* LeptonPt_LowQT_LHC_High;
 ThreadHist<TH1D *>* MtW_LowQT_LHC;

 ThreadHist<TH1D *>* LeptonPt_LowQT_Z_LHC_Low;
 ThreadHist<TH1D *>* LeptonPt_LowQT_Z_LHC_High;

 ThreadHist<TH1D *>* WPlusPt_LHC;
 ThreadHist<TH1D *>* WMinusPt_LHC;
 ThreadHist<TH1D *>* ZPt_LHC;

 ThreadHist<TH1D *>* WMass_Inclusive;

 TH1D *Prediction_w225;
 TH1D *Data_w225;

 TH1D *Prediction_w227;
 TH1D *Data_w227;

 TH1D *Prediction_w234;
 TH1D *Data_w234;

 TH1D *Prediction_w281;
 TH1D *Data_w281;

 TH1D *RatioWZ_CDF;
 TH1D *RatioWZ_Inclusive;
 TH1D *RatioWZ_ScaleEnvelope;
 TH1D *NormalizedWPt_CDF;
 TH1D *NormalizedWPt_Inclusive;
 TH1D *NormalizedZPt_CDF;
 TH1D *NormalizedZPt_Inclusive;

 TH1D *MtW_CDF_Pseudodata;
 TH1D *LeptonPt_CDF_Pseudodata;
 TH1D *NuPt_CDF_Pseudodata;
 TH1D *DeltaPhi_CDF_Pseudodata;
 TH1D *WPt_CDF_Pseudodata;
 TH1D *WPt_CDF_Pseudodata_NoFluc;
 TH1D *WPt_CDF_ScaleUp_NoFluc;
 TH1D *WPt_CDF_ScaleDown_NoFluc;
 TH1D *WPt_CDF_ScaleVari_NoFluc;
 TH1D *ZPt_CDF_Pseudodata;

 TH1D *MtW_CDF_LargeStat;
 TH1D *LeptonPt_CDF_LargeStat;
 TH1D *NuPt_CDF_LargeStat;
 TH1D *DeltaPhi_CDF_LargeStat;
 TH1D *WPt_CDF_LargeStat;
 TH1D *ZPt_CDF_LargeStat;
 TH1D *WPt_CDF_FineBin_LargeStat;
 TH1D *ZPt_CDF_FineBin_LargeStat;

 TH1D *MtW_CDF_Smear_Pseudodata;
 TH1D *LeptonPt_CDF_Smear_Pseudodata;
 TH1D *NuPt_CDF_Smear_Pseudodata;
 TH1D *DeltaPhi_CDF_Smear_Pseudodata;
 TH1D *WPt_CDF_Smear_Pseudodata;
 TH1D *ZPt_CDF_Smear_Pseudodata;

 TH1D *MtW_CDF_Smear_LargeStat;
 TH1D *LeptonPt_CDF_Smear_LargeStat;
 TH1D *NuPt_CDF_Smear_LargeStat;
 TH1D *DeltaPhi_CDF_Smear_LargeStat;
 TH1D *WPt_CDF_Smear_LargeStat;
 TH1D *ZPt_CDF_Smear_LargeStat;

 TH1D *FiducialCrossSection_W;
 TH1D *FiducialCrossSection_Z;

 TH1D *FiducialCrossSection_Smear_W;
 TH1D *FiducialCrossSection_Smear_Z;

 TH1D *MtW_CDF_Data;
 TH1D *LeptonPt_CDF_Data;
 TH1D *NuPt_CDF_Data;

 TH1D *MtW_CDF_Electron;
 TH1D *LeptonPt_CDF_Electron;
 TH1D *NuPt_CDF_Electron;

 TH1D *JacobianAsymmetry;
 TH1D *JacobianAsymmetrySlope;
 TH1D *JacobianAsymmetryOffset;
 TH1D *JacobianAsymmetryLowQT;
 TH1D *JacobianAsymmetryLowQTSlope;
 TH1D *JacobianAsymmetryLowQTOffset;
 TH1D *LeptonPt_LHC_Pseudodata;
 TH1D *LeptonPt_LHC_Low_Pseudodata;
 TH1D *LeptonPt_LHC_High_Pseudodata;
 TH1D *JacobianAsymmetry_Data;
 TH1D *LeptonPt_LowQT_LHC_Pseudodata;
 TH1D *LeptonPt_LowQT_LHC_Tail_Pseudodata;
 TH1D *LeptonPt_LowQT_LHC_Low_Pseudodata;
 TH1D *LeptonPt_LowQT_LHC_High_Pseudodata;
 TH1D *JacobianAsymmetryLowQT_Data;

 TH1D *LeptonPt_LowQT_Z_LHC_Low_Pseudodata;
 TH1D *LeptonPt_LowQT_Z_LHC_High_Pseudodata;
 TH1D *JacobianAsymmetryLowQTZ_Data;

 TH1D *MtW_LowQT_LHC_Pseudodata;

 ThreadHist<AngularFunction *>* A0_ZPt;

 ThreadHist<AngularFunction *>* A1_ZPt;

 ThreadHist<AngularFunction *>* A2_ZPt;

 ThreadHist<AngularFunction *>* A3_ZPt;

 ThreadHist<AngularFunction *>* A4_ZPt;

 ThreadHist<AngularFunction *>* L0_ZPt;

 ThreadHist<AngularFunction *>* A0_ZY;

 ThreadHist<AngularFunction *>* A1_ZY;

 ThreadHist<AngularFunction *>* A2_ZY;

 ThreadHist<AngularFunction *>* A3_ZY;

 ThreadHist<AngularFunction *>* A4_ZY;

 double DataPoint;
 double StaErr;
 double SysErr;
 double TotErr;
 vector<TString> DataList;
 string FileLine;

 HistsResBosWTev(){};
 HistsResBosWTev(TString RootType){this->RootType = RootType;};
 virtual void bookHists(int TotalThread);
 virtual void outputInformation();
 virtual void ReadData();
 virtual void InputData(vector<TString> DataList);
 virtual void InitialCDFData();

 double LeptonPtMin = 32.0;
 double LeptonPtMiddle = 37.0;
 double LeptonPtMax = 47.0;

 virtual void InputJacoAsymInput(double LeptonPtMin, double LeptonPtMiddle, double LeptonPtMax){
   this->LeptonPtMin = LeptonPtMin;
   this->LeptonPtMiddle = LeptonPtMiddle;
   this->LeptonPtMax = LeptonPtMax;
 }

// template<class T>

};
#endif
