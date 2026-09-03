#ifndef __HistsResBosHighMassZ_H_
#define __HistsResBosHighMassZ_H_
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

using namespace std;

class HistsResBosHighMassZ : public makeHists
{
 public:

 //////////////////////////
 //  Z Event Histograms  //
 //////////////////////////

 ThreadHist<TH1D *>* ZMass_uu;
 ThreadHist<TH1D *>* ZMass_dd;
 ThreadHist<TH1D *>* ZMass_ss;
 ThreadHist<TH1D *>* ZMass_cc;
 ThreadHist<TH1D *>* ZMass_bb;
 ThreadHist<TH1D *>* ZMass_utype;
 ThreadHist<TH1D *>* ZMass_dtype;
 ThreadHist<TH3D *>* Xsec_3D_CC;
 ThreadHist<TH3D *>* Xsec_3D_CF;
 ThreadHist<TH3D *>* Xsec_3D_CC_LowMass;
 ThreadHist<TH3D *>* Xsec_3D_CF_LowMass;
 ThreadHist<TH3D *>* Xsec_3D_CC_HighMass;
 ThreadHist<TH3D *>* Xsec_3D_CF_HighMass;
 ThreadHist<TH3D *>* Xsec_3D_CC_uu;
 ThreadHist<TH3D *>* Xsec_3D_CF_uu;
 ThreadHist<TH3D *>* Xsec_3D_CC_dd;
 ThreadHist<TH3D *>* Xsec_3D_CF_dd;
 ThreadHist<TH2D *>* Xsec_2D_CC;
 ThreadHist<TH2D *>* Xsec_2D_CF;
 ThreadHist<TH1D *>* Xsec_1D_CC;
 ThreadHist<TH1D *>* Xsec_1D_CF;
 ThreadHist<TH2D *>* ZMass_CosTheta_uu;
 ThreadHist<TH2D *>* ZMass_CosTheta_dd;
 ThreadHist<TH2D *>* ZMass_CosTheta;

 ThreadHist<TH1D *>* ZRapidity_CC;
 ThreadHist<TH1D *>* ZRapidity_CF;
 ThreadHist<TH1D *>* ZRapidity_CF_Low;
 ThreadHist<TH1D *>* ZPt;
 ThreadHist<TH1D *>* FZMass_CC;
 ThreadHist<TH1D *>* BZMass_CC;
 ThreadHist<TH1D *>* FZMass_CF;
 ThreadHist<TH1D *>* BZMass_CF;
 ThreadHist<TH1D *>* FZMass_LowRegion_CC;
 ThreadHist<TH1D *>* BZMass_LowRegion_CC;
 ThreadHist<TH1D *>* FZMass_LowRegion_CF;
 ThreadHist<TH1D *>* BZMass_LowRegion_CF;
 ThreadHist<TH1D *>* FZMass_HighRegion_CC;
 ThreadHist<TH1D *>* BZMass_HighRegion_CC;
 ThreadHist<TH1D *>* FZMass_HighRegion_CF;
 ThreadHist<TH1D *>* BZMass_HighRegion_CF;

 ThreadHist<TH1D *>* ZMass_HighMass;
 ThreadHist<TH1D *>* ZMass_HighMass_PerTeV;

 ThreadHist<TH1D *>* ZMass_FullMass;

 ThreadHist<TH1D *>* FZMass_HighMass;
 ThreadHist<TH1D *>* BZMass_HighMass;
 ThreadHist<TH1D *>* FZMass_HighMass2;
 ThreadHist<TH1D *>* BZMass_HighMass2;
 ThreadHist<TH1D *>* FZMass_HighMass_uu;
 ThreadHist<TH1D *>* BZMass_HighMass_uu;
 ThreadHist<TH1D *>* FZMass_HighMass_dd;
 ThreadHist<TH1D *>* BZMass_HighMass_dd;
 ThreadHist<TH1D *>* FZMass_HighMass_upto10000;
 ThreadHist<TH1D *>* BZMass_HighMass_upto10000;

 ThreadHist<TH1D *>* FZMass_LowMass1;
 ThreadHist<TH1D *>* BZMass_LowMass1;
 ThreadHist<TH1D *>* FZMass_LowMass2;
 ThreadHist<TH1D *>* BZMass_LowMass2;

 ThreadHist<TH2D *>* FZMass_LowMass1_ZY;
 ThreadHist<TH2D *>* BZMass_LowMass1_ZY;
 ThreadHist<TH2D *>* FZMass_LowMass2_ZY;
 ThreadHist<TH2D *>* BZMass_LowMass2_ZY;

 ThreadHist<TH1D *>* FZMass_ATLAS_CC;
 ThreadHist<TH1D *>* BZMass_ATLAS_CC;
 ThreadHist<TH1D *>* FZMass_ATLAS_CF;
 ThreadHist<TH1D *>* BZMass_ATLAS_CF;

 ThreadHist<TH1D *>* ZHighMass_CC;
 ThreadHist<TH1D *>* ZHighMass_CF;
 ThreadHist<TH1D *>* ZHighMass_CC_PerTeV;
 ThreadHist<TH1D *>* ZHighMass_CF_PerTeV;
 ThreadHist<TH2D *>* FZMass_ZY_CC;
 ThreadHist<TH2D *>* BZMass_ZY_CC;
 ThreadHist<TH2D *>* FZMass_ZY_CF;
 ThreadHist<TH2D *>* BZMass_ZY_CF;
 ThreadHist<TH1D *>* CrossSection;
 ThreadHist<TH1D *>* CrossSectionF;
 ThreadHist<TH1D *>* CrossSectionB;

 ThreadHist<TH2D *>* CrossSectionPtY;

 ThreadHist<TH1D *>* FZMass_Full;
 ThreadHist<TH1D *>* BZMass_Full;
 ThreadHist<TH1D *>* FZMass_Full_uu;
 ThreadHist<TH1D *>* BZMass_Full_uu;
 ThreadHist<TH1D *>* FZMass_Full_dd;
 ThreadHist<TH1D *>* BZMass_Full_dd;

 ThreadHist<TH2D *>* ZMass_ZMT;

 ThreadHist<TH1D *>* ForwardPosiLeptonEta;
 ThreadHist<TH1D *>* BackwardPosiLeptonEta;
 ThreadHist<TH1D *>* ForwardNegaLeptonEta;
 ThreadHist<TH1D *>* BackwardNegaLeptonEta;

 /////////////////////
 //  Dilution plot  //
 /////////////////////

 ThreadHist<TH1D *>* ZHighMass_total;
 ThreadHist<TH1D *>* ZHighMass_wrong;
 TH1D *Dilution_ZHighMass;

 ThreadHist<TH1D *>* ZHighMass2_total;
 ThreadHist<TH1D *>* ZHighMass2_wrong;
 TH1D *Dilution_ZHighMass2;

 //quark ZMass dilution
 ThreadHist<TH1D *>* ZHighMass_uu_total;
 ThreadHist<TH1D *>* ZHighMass_uu_wrong;
 TH1D *Dilution_ZHighMass_uu;

 ThreadHist<TH1D *>* ZHighMass_dd_total;
 ThreadHist<TH1D *>* ZHighMass_dd_wrong;
 TH1D *Dilution_ZHighMass_dd;

 ThreadHist<TH1D *>* ZHighMass2_uu_total;
 ThreadHist<TH1D *>* ZHighMass2_uu_wrong;
 TH1D *Dilution_ZHighMass2_uu;

 ThreadHist<TH1D *>* ZHighMass2_dd_total;
 ThreadHist<TH1D *>* ZHighMass2_dd_wrong;
 TH1D *Dilution_ZHighMass2_dd;

 //////////////////////
 //  ATLAS 8TeV ZPT  //
 //////////////////////

 ThreadHist<TH1D *>* ATLASZPt_Fiduc;

 ThreadHist<TH1D *>* ATLASZPt_Total;

 ThreadHist<TH2D *>* ATLASZPt_2D_Fiduc;

 ThreadHist<TH2D *>* ATLASZPt_2D_Total;

 ThreadHist<TH2D *>* ATLASZPt_2D_Total_uu;

 ThreadHist<TH2D *>* ATLASZPt_2D_Total_dd;

 ThreadHist<TH2D *>* ATLASZPt_2D_Total_MassWindow;

 //////////////////////
 // ATLAS 13TeV HMDY //
 //////////////////////

 ThreadHist<TH1D *>* ATLAS_Mll_HighMass;
 ThreadHist<TH1D *>* ATLAS_costheta;
 ThreadHist<TH1D *>* ATLAS_DilRapidity;

 ThreadHist<TH2D *>* ATLAS_Mll_HighMass_DilRapidity;
 ThreadHist<TH2D *>* ATLAS_Mll_HighMass_costheta;

 ThreadHist<TH2D *>* ATLAS_Mll_HighMass_DilRapidity_1;
 ThreadHist<TH2D *>* ATLAS_Mll_HighMass_costheta_1;

 ThreadHist<TH2D *>* ATLAS_Mll_HighMass_DilRapidity_2;
 ThreadHist<TH2D *>* ATLAS_Mll_HighMass_costheta_2;

 ThreadHist<TH2D *>* ATLAS_Mll_HighMass_DilRapidity_3;
 ThreadHist<TH2D *>* ATLAS_Mll_HighMass_costheta_3;

 ThreadHist<TH3D *>* ATLAS_HMDY_Xsec_3D;

 ThreadHist<TH1D *>* ATLAS_Mll_HighMass_FineBin;
 ThreadHist<TH1D *>* ATLAS_costheta_FineBin;
 ThreadHist<TH1D *>* ATLAS_DilRapidity_FineBin;

 ThreadHist<TH2D *>* ATLAS_Mll_HighMass_DilRapidity_FineBin;
 ThreadHist<TH2D *>* ATLAS_Mll_HighMass_costheta_FineBin;

 ThreadHist<TH3D *>* ATLAS_HMDY_Xsec_3D_FineBin;

 //////////////////////////
 //  W Event Histograms  //
 //////////////////////////

 ThreadHist<TH1D *>* PositiveLeptonEta;
 ThreadHist<TH1D *>* NegativeLeptonEta;
 ThreadHist<TH1D *>* PositiveLeptonEta_NoPtCut;
 ThreadHist<TH1D *>* NegativeLeptonEta_NoPtCut;
 ThreadHist<TH1D *>* PositiveLeptonHighEta;
 ThreadHist<TH1D *>* NegativeLeptonHighEta;
 ThreadHist<TH1D *>* PositiveLeptonLowEta;
 ThreadHist<TH1D *>* NegativeLeptonLowEta;

 ThreadHist<TH1D *>* PositiveLeptonEtaFull;
 ThreadHist<TH1D *>* NegativeLeptonEtaFull;
 ThreadHist<TH1D *>* PositiveNeutrinoEtaFull;
 ThreadHist<TH1D *>* NegativeNeutrinoEtaFull;

 ThreadHist<TH1D *>* PositiveLeptonPt;
 ThreadHist<TH1D *>* NegativeLeptonPt;

 ThreadHist<TH2D *>* PositiveLeptonPtEta;
 ThreadHist<TH2D *>* NegativeLeptonPtEta;

 ThreadHist<TH2D *>* WPlusMTEta;
 ThreadHist<TH2D *>* WMinusMTEta;
 ThreadHist<TH2D *>* WPlusMTEta_NoPtCut;
 ThreadHist<TH2D *>* WMinusMTEta_NoPtCut;
 ThreadHist<TH2D *>* WPlusMTEta_Above100;
 ThreadHist<TH2D *>* WMinusMTEta_Above100;

 ThreadHist<TH2D *>* WPlusMTEta_FullEta;
 ThreadHist<TH2D *>* WMinusMTEta_FullEta;
 ThreadHist<TH2D *>* WPlusMTEta_FullEta_Above100;
 ThreadHist<TH2D *>* WMinusMTEta_FullEta_Above100;

 ThreadHist<TH2D *>* WMTx;
 ThreadHist<TH3D *>* WPlusMTCosThetaEta;
 ThreadHist<TH3D *>* WMinusMTCosThetaEta;

 ThreadHist<TH1D *>* WLeptonPt;

 ThreadHist<TH1D *>* WPlusNeutrinoPt;
 ThreadHist<TH1D *>* WMinusNeutrinoPt;

 ThreadHist<TH1D *>* NeutrinoPt;

 ThreadHist<TH1D *>* WPlusMT;
 ThreadHist<TH1D *>* WMinusMT;
 ThreadHist<TH1D *>* WPlusMT_NoPtCut;
 ThreadHist<TH1D *>* WMinusMT_NoPtCut;
 ThreadHist<TH1D *>* WPlusMT_Above100;
 ThreadHist<TH1D *>* WMinusMT_Above100;
 ThreadHist<TH1D *>* WBosonMT;

 ThreadHist<TH1D *>* WPlusXsec;
 ThreadHist<TH1D *>* WMinusXsec;

 ThreadHist<TH1D *>* WHighMassMT;
 ThreadHist<TH1D *>* WPlusHighMassMT;
 ThreadHist<TH1D *>* WMinusHighMassMT;
 ThreadHist<TH1D *>* WHighMassMT_NoPtCut;
 ThreadHist<TH1D *>* WPlusHighMassMT_NoPtCut;
 ThreadHist<TH1D *>* WMinusHighMassMT_NoPtCut;
 ThreadHist<TH1D *>* WHighMassMT_PerTeV;
 ThreadHist<TH1D *>* WPlusHighMassMT_PerTeV;
 ThreadHist<TH1D *>* WMinusHighMassMT_PerTeV;

 ThreadHist<TH1D *>* WPlusForwardEta;
 ThreadHist<TH1D *>* WPlusBackwardEta;
 ThreadHist<TH1D *>* WMinusForwardEta;
 ThreadHist<TH1D *>* WMinusBackwardEta;

 ThreadHist<TH1D *>* WPlusAverageRapidity;
 ThreadHist<TH1D *>* WMinusAverageRapidity;

 ThreadHist<TH1D *>* WPlusCosTheta;
 ThreadHist<TH1D *>* WMinusCosTheta;

 ThreadHist<TH1D *>* WPlusCosTheta_ExpPz;
 ThreadHist<TH1D *>* WMinusCosTheta_ExpPz;

 ThreadHist<TH1D *>* WPlusCosTheta_ExpEta;
 ThreadHist<TH1D *>* WMinusCosTheta_ExpEta;

 ThreadHist<TH1D *>* WPlusForwardEta_ExpPz;
 ThreadHist<TH1D *>* WPlusBackwardEta_ExpPz;
 ThreadHist<TH1D *>* WMinusForwardEta_ExpPz;
 ThreadHist<TH1D *>* WMinusBackwardEta_ExpPz;

 ThreadHist<TH1D *>* WPlusForwardEta_ExpEta;
 ThreadHist<TH1D *>* WPlusBackwardEta_ExpEta;
 ThreadHist<TH1D *>* WMinusForwardEta_ExpEta;
 ThreadHist<TH1D *>* WMinusBackwardEta_ExpEta;

 ThreadHist<TH1D *>* WPlusForwardDeta;
 ThreadHist<TH1D *>* WPlusBackwardDeta;
 ThreadHist<TH1D *>* WMinusForwardDeta;
 ThreadHist<TH1D *>* WMinusBackwardDeta;

 ThreadHist<TH2D *>* WPlusLepNuEta;
 ThreadHist<TH2D *>* WMinusLepNuEta;

 ThreadHist<TH1D *>* WPlusPzMethodFraction;
 ThreadHist<TH1D *>* WMinusPzMethodFraction;
 ThreadHist<TH1D *>* WPlusEtaMethodFraction;
 ThreadHist<TH1D *>* WMinusEtaMethodFraction;

 ThreadHist<TH1D *>* WPt;

 ThreadHist<TH1D *>* RHIC_WPlus;
 ThreadHist<TH1D *>* RHIC_WMinus;

 ThreadHist<TH1D *>* TotalXsec_WPlus;
 ThreadHist<TH1D *>* TotalXsec_WMinus;
 ThreadHist<TH1D *>* TotalXsec_Z;
 ThreadHist<AngularFunction *>* A0_ZPt_WPlus;
 ThreadHist<AngularFunction *>* A1_ZPt_WPlus;
 ThreadHist<AngularFunction *>* A2_ZPt_WPlus;
 ThreadHist<AngularFunction *>* A3_ZPt_WPlus;
 ThreadHist<AngularFunction *>* A4_ZPt_WPlus;
 ThreadHist<AngularFunction *>* A0_ZPt_WMinus;
 ThreadHist<AngularFunction *>* A1_ZPt_WMinus;
 ThreadHist<AngularFunction *>* A2_ZPt_WMinus;
 ThreadHist<AngularFunction *>* A3_ZPt_WMinus;
 ThreadHist<AngularFunction *>* A4_ZPt_WMinus;

/////////////////////////////////////////////////////////////

 TH1D* AFB_CC;
 TH1D* AFB_CF;
 TH1D* AFB_LowRegion_CC;
 TH1D* AFB_LowRegion_CF;
 TH1D* AFB_HighRegion_CC;
 TH1D* AFB_HighRegion_CF;
 TH1D* AFB_Delta_CC;
 TH1D* AFB_Delta_CF;
 TH2D* AFB_Mass_ZY_CC;
 TH2D* AFB_Mass_ZY_CF;
 TH1D* AFB_HighMass;
 TH1D* AFB_HighMass2;
 TH1D* AFB_HighMass_uu;
 TH1D* AFB_HighMass_dd;
 TH1D* AFB_HighMass_upto10000;

 TH2D* AFB_Mass_ZY_CC_300;
 TH2D* AFB_Mass_ZY_CF_300;
 TH1D* AFB_HighMass_300;
 TH1D* AFB_HighMass2_300;

 TH1D* AFB_LowMass1;
 TH1D* AFB_LowMass2;

 TH2D* AFB_LowMass1_ZY;
 TH2D* AFB_LowMass2_ZY;

 TH1D* AFB_ATLAS_CC;
 TH1D* AFB_ATLAS_CF;

 TH1D* Corr_AFB_HighMassZ_CC;
 TH1D* Corr_AFB_HighMassZ_CF;

 TH1D* ZMass_utype_Pseudodata;
 TH1D* ZMass_dtype_Pseudodata;

 TH3D* Xsec_3D_CC_Pseudodata;
 TH3D* Xsec_3D_CF_Pseudodata;
 TH3D* Xsec_3D_CC_LowMass_Pseudodata;
 TH3D* Xsec_3D_CF_LowMass_Pseudodata;
 TH3D* Xsec_3D_CC_HighMass_Pseudodata;
 TH3D* Xsec_3D_CF_HighMass_Pseudodata;
 TH2D* Xsec_2D_CC_Pseudodata;
 TH2D* Xsec_2D_CF_Pseudodata;
 TH1D* Xsec_1D_CC_Pseudodata;
 TH1D* Xsec_1D_CF_Pseudodata;
 TH3D* Xsec_3D_CC_Pseudodata_300;
 TH3D* Xsec_3D_CF_Pseudodata_300;
 TH2D* Xsec_2D_CC_Pseudodata_300;
 TH2D* Xsec_2D_CF_Pseudodata_300;
 TH1D* Xsec_1D_CC_Pseudodata_300;
 TH1D* Xsec_1D_CF_Pseudodata_300;
 TH3D* Xsec_3D_CC_Pseudodata_140;
 TH3D* Xsec_3D_CF_Pseudodata_140;
 TH2D* Xsec_2D_CC_Pseudodata_140;
 TH2D* Xsec_2D_CF_Pseudodata_140;
 TH1D* Xsec_1D_CC_Pseudodata_140;
 TH1D* Xsec_1D_CF_Pseudodata_140;

 TH1D* ZRapidity_CC_Pseudodata;
 TH1D* ZRapidity_CF_Pseudodata;
 TH1D* ZRapidity_CF_Low_Pseudodata;
 TH1D* ZHighMass_CC_Pseudodata;
 TH1D* ZHighMass_CF_Pseudodata;

 TH1D* FZMass_CC_Pseudodata;
 TH1D* BZMass_CC_Pseudodata;
 TH1D* FZMass_CF_Pseudodata;
 TH1D* BZMass_CF_Pseudodata;

 TH2D* FZMass_ZY_CC_Pseudodata;
 TH2D* BZMass_ZY_CC_Pseudodata;
 TH2D* FZMass_ZY_CF_Pseudodata;
 TH2D* BZMass_ZY_CF_Pseudodata;

 TH2D* FZMass_ZY_CC_Pseudodata_300;
 TH2D* BZMass_ZY_CC_Pseudodata_300;
 TH2D* FZMass_ZY_CF_Pseudodata_300;
 TH2D* BZMass_ZY_CF_Pseudodata_300;

 TH1D* ZMass_HighMass_Pseudodata;
 TH1D* ZMass_HighMass_Pseudodata_300;
 TH1D* ZMass_HighMass_Pseudodata_140;

 TH1D* ZMass_HighMass_Integral;
 TH1D* ZHighMass_CC_Integral;
 TH1D* ZHighMass_CF_Integral;

 TH1D* FZMass_HighMass_Pseudodata;
 TH1D* BZMass_HighMass_Pseudodata;
 TH1D* FZMass_HighMass2_Pseudodata;
 TH1D* BZMass_HighMass2_Pseudodata;

 TH1D* FZMass_HighMass_Pseudodata_300;
 TH1D* BZMass_HighMass_Pseudodata_300;
 TH1D* FZMass_HighMass2_Pseudodata_300;
 TH1D* BZMass_HighMass2_Pseudodata_300;

 TH1D* FZMass_LowMass1_Pseudodata;
 TH1D* BZMass_LowMass1_Pseudodata;
 TH1D* FZMass_LowMass2_Pseudodata;
 TH1D* BZMass_LowMass2_Pseudodata;

 TH2D* FZMass_LowMass1_ZY_Pseudodata;
 TH2D* BZMass_LowMass1_ZY_Pseudodata;
 TH2D* FZMass_LowMass2_ZY_Pseudodata;
 TH2D* BZMass_LowMass2_ZY_Pseudodata;

 TH1D* FZMass_ATLAS_CC_Pseudodata;
 TH1D* BZMass_ATLAS_CC_Pseudodata;
 TH1D* FZMass_ATLAS_CF_Pseudodata;
 TH1D* BZMass_ATLAS_CF_Pseudodata;

 TH1D* CrossSection_Pseudodata;
 TH1D* CrossSectionF_Pseudodata;
 TH1D* CrossSectionB_Pseudodata;
 TH1D* CrossSectionAFB;

 TH1D* AFB_PosiLeptonEta;
 TH1D* AFB_NegaLeptonEta;

 //////////////////////
 //  ATLAS 8TeV ZPT  //
 //////////////////////

 TH2D *ATLASZPt_2D_Fiduc_Final;
 TH2D *ATLASZPt_2D_Total_Final;
 TH2D *ATLASZPt_2D_Total_uu_Final;
 TH2D *ATLASZPt_2D_Total_dd_Final;
 TH2D *ATLASZPt_2D_Total_MassWindow_Final;

 //////////////////////
 // ATLAS 13TeV HMDY //
 //////////////////////

 TH1D* ATLAS_Mll_HighMass_Pseudodata;
 TH1D* ATLAS_costheta_Pseudodata;
 TH1D* ATLAS_DilRapidity_Pseudodata;

 TH2D* ATLAS_Mll_HighMass_DilRapidity_Pseudodata;
 TH2D* ATLAS_Mll_HighMass_costheta_Pseudodata;

 TH3D* ATLAS_HMDY_Xsec_3D_Pseudodata;

 TH1D* ATLAS_Mll_HighMass_FineBin_Pseudodata;
 TH1D* ATLAS_costheta_FineBin_Pseudodata;
 TH1D* ATLAS_DilRapidity_FineBin_Pseudodata;

 TH2D* ATLAS_Mll_HighMass_DilRapidity_FineBin_Pseudodata;
 TH2D* ATLAS_Mll_HighMass_costheta_FineBin_Pseudodata;
 
 TH3D* ATLAS_HMDY_Xsec_3D_FineBin_Pseudodata;

 TH1D* ATLAS_Mll_HighMass_DilRapidity_NewBinning;
 TH1D* ATLAS_Mll_HighMass_costheta_NewBinning;
 TH1D* ATLAS_Mll_HighMass_DilRapidity_NewBinning_Pseudodata;
 TH1D* ATLAS_Mll_HighMass_costheta_NewBinning_Pseudodata;

/////////////////////////////////////////////////////////////

 TH1D* PositiveLeptonEta_Pseudodata;
 TH1D* NegativeLeptonEta_Pseudodata;
 TH1D* PositiveLeptonHighEta_Pseudodata;
 TH1D* NegativeLeptonHighEta_Pseudodata;
 TH1D* PositiveLeptonLowEta_Pseudodata;
 TH1D* NegativeLeptonLowEta_Pseudodata;
 TH1D* PositiveLeptonPt_Pseudodata;
 TH1D* NegativeLeptonPt_Pseudodata;
 TH2D* PositiveLeptonPtEta_Pseudodata;
 TH2D* NegativeLeptonPtEta_Pseudodata;
 TH2D* WPlusMTEta_Pseudodata;
 TH2D* WMinusMTEta_Pseudodata;
 TH1D* WLeptonPt_Pseudodata;
 TH1D* WPlusNeutrinoPt_Pseudodata;
 TH1D* WMinusNeutrinoPt_Pseudodata;
 TH1D* NeutrinoPt_Pseudodata;
 TH1D* WPlusMT_Pseudodata;
 TH1D* WMinusMT_Pseudodata;
 TH1D* WBosonMT_Pseudodata;
 TH1D* WPlusXsec_Pseudodata;
 TH1D* WMinusXsec_Pseudodata;
 TH1D* WHighMassMT_Pseudodata;
 TH1D* WPlusHighMassMT_Pseudodata;
 TH1D* WMinusHighMassMT_Pseudodata;
 TH2D* WPlusMTEta_Above100_Pseudodata;
 TH2D* WMinusMTEta_Above100_Pseudodata;
 TH1D* WPlusMT_Above100_Pseudodata;
 TH1D* WMinusMT_Above100_Pseudodata;

 TH2D* WPlusMTEta_FullEta_Pseudodata;
 TH2D* WMinusMTEta_FullEta_Pseudodata;
 TH2D* WPlusMTEta_FullEta_Above100_Pseudodata;
 TH2D* WMinusMTEta_FullEta_Above100_Pseudodata;

 TH1D* PositiveLeptonEta_Pseudodata_300;
 TH1D* NegativeLeptonEta_Pseudodata_300;
 TH1D* PositiveLeptonHighEta_Pseudodata_300;
 TH1D* NegativeLeptonHighEta_Pseudodata_300;
 TH1D* PositiveLeptonLowEta_Pseudodata_300;
 TH1D* NegativeLeptonLowEta_Pseudodata_300;
 TH1D* PositiveLeptonPt_Pseudodata_300;
 TH1D* NegativeLeptonPt_Pseudodata_300;
 TH2D* PositiveLeptonPtEta_Pseudodata_300;
 TH2D* NegativeLeptonPtEta_Pseudodata_300;
 TH2D* WPlusMTEta_Pseudodata_300;
 TH2D* WMinusMTEta_Pseudodata_300;
 TH1D* WLeptonPt_Pseudodata_300;
 TH1D* WPlusNeutrinoPt_Pseudodata_300;
 TH1D* WMinusNeutrinoPt_Pseudodata_300;
 TH1D* NeutrinoPt_Pseudodata_300;
 TH1D* WPlusMT_Pseudodata_300;
 TH1D* WMinusMT_Pseudodata_300;
 TH1D* WBosonMT_Pseudodata_300;
 TH1D* WPlusXsec_Pseudodata_300;
 TH1D* WMinusXsec_Pseudodata_300;
 TH1D* WHighMassMT_Pseudodata_300;
 TH1D* WPlusHighMassMT_Pseudodata_300;
 TH1D* WMinusHighMassMT_Pseudodata_300;
 TH1D* PositiveLeptonEta_Pseudodata_140;
 TH1D* NegativeLeptonEta_Pseudodata_140;
 TH1D* PositiveLeptonHighEta_Pseudodata_140;
 TH1D* NegativeLeptonHighEta_Pseudodata_140;
 TH1D* PositiveLeptonLowEta_Pseudodata_140;
 TH1D* NegativeLeptonLowEta_Pseudodata_140;
 TH1D* PositiveLeptonPt_Pseudodata_140;
 TH1D* NegativeLeptonPt_Pseudodata_140;
 TH2D* PositiveLeptonPtEta_Pseudodata_140;
 TH2D* NegativeLeptonPtEta_Pseudodata_140;
 TH2D* WPlusMTEta_Pseudodata_140;
 TH2D* WMinusMTEta_Pseudodata_140;
 TH1D* WLeptonPt_Pseudodata_140;
 TH1D* WPlusNeutrinoPt_Pseudodata_140;
 TH1D* WMinusNeutrinoPt_Pseudodata_140;
 TH1D* NeutrinoPt_Pseudodata_140;
 TH1D* WPlusMT_Pseudodata_140;
 TH1D* WMinusMT_Pseudodata_140;
 TH1D* WBosonMT_Pseudodata_140;
 TH1D* WPlusXsec_Pseudodata_140;
 TH1D* WMinusXsec_Pseudodata_140;
 TH1D* WHighMassMT_Pseudodata_140;
 TH1D* WPlusHighMassMT_Pseudodata_140;
 TH1D* WMinusHighMassMT_Pseudodata_140;

 TH1D* WHighMassMT_Integral;
 TH1D* WPlusHighMassMT_Integral;
 TH1D* WMinusHighMassMT_Integral;

 TH1D* WLeptonEtaAsymmetry;
 TH1D* WLeptonPtAsymmetry;
 TH1D* NeutrinoPtAsymmetry;
 TH1D* WBosonMTAsymmetry;
 TH1D* WBosonXsecAsymmetry;
 TH1D* WPositiveLeptonEtaAsymmetry;
 TH1D* WNegativeLeptonEtaAsymmetry;
 TH2D* WMTEtaAsymmetry;

 TH1D* WLeptonEtaAsymmetry_300;
 TH1D* WLeptonPtAsymmetry_300;
 TH1D* NeutrinoPtAsymmetry_300;
 TH1D* WBosonMTAsymmetry_300;
 TH1D* WBosonXsecAsymmetry_300;
 TH1D* WPositiveLeptonEtaAsymmetry_300;
 TH1D* WNegativeLeptonEtaAsymmetry_300;
 TH2D* WMTEtaAsymmetry_300;

 TH1D* WLeptonEtaShapeAsymmetry;
 TH2D* WMTEtaShapeAsymmetry;

 TH1D* WPositiveLeptonEtaMean;
 TH1D* WNegativeLeptonEtaMean;
 TH1D* LeptonEtaMeanRatio;

 TH1D* WPositiveLeptonEtaMean_300;
 TH1D* WNegativeLeptonEtaMean_300;
 TH1D* LeptonEtaMeanRatio_300;

 TH1D* WPlusForwardEta_Pseudodata;
 TH1D* WPlusBackwardEta_Pseudodata;
 TH1D* WMinusForwardEta_Pseudodata;
 TH1D* WMinusBackwardEta_Pseudodata;

 TH1D* WPlusForwardEta_ExpPz_Pseudodata;
 TH1D* WPlusBackwardEta_ExpPz_Pseudodata;
 TH1D* WMinusForwardEta_ExpPz_Pseudodata;
 TH1D* WMinusBackwardEta_ExpPz_Pseudodata;

 TH1D* WPlusForwardEta_ExpEta_Pseudodata;
 TH1D* WPlusBackwardEta_ExpEta_Pseudodata;
 TH1D* WMinusForwardEta_ExpEta_Pseudodata;
 TH1D* WMinusBackwardEta_ExpEta_Pseudodata;

 TH1D* WPlusAFB;
 TH1D* WMinusAFB;

 TH1D* WPlusRapidityAverage;
 TH1D* WMinusRapidityAverage;

 TH1D* WPlusAFB_ExpPz;
 TH1D* WMinusAFB_ExpPz;

 TH1D* WPlusAFB_ExpEta;
 TH1D* WMinusAFB_ExpEta;

 TH1D* RHIC_WRatio;
 TH1D* RHIC_WRatio_Data;

//member function
 vector<TString> sysName;
 virtual void InitialSysName();
 virtual void bookHists(int TotalThread);
 virtual void outputInformation();

// template<class T>

};
#endif
