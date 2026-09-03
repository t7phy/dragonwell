#ifndef __HISTS_RESBOS_H_
#define __HISTS_RESBOS_H_
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

class HistsResBos : public makeHists
{
 public:

 /////////////////////////
 //  hadron level plot  //
 /////////////////////////


 ThreadHist<TH1D *>* ZMass;

 ThreadHist<TH1D *>* ZMass_CC;

 ThreadHist<TH1D *>* ZMass_CF;

 ThreadHist<TH1D *>* FZmass;

 ThreadHist<TH1D *>* BZmass;

 ThreadHist<TH1D *>* FZmass_CC;

 ThreadHist<TH1D *>* BZmass_CC;

 ThreadHist<TH1D *>* FZmass_CF;

 ThreadHist<TH1D *>* BZmass_CF;

 ThreadHist<TH1D *>* FZmass_LHCb;

 ThreadHist<TH1D *>* BZmass_LHCb;

 ThreadHist<TH1D *>* ZPt;

 ThreadHist<TH1D *>* ZRapidity;

 ThreadHist<TH1D *>* ZE;

 ThreadHist<TH2D *>* ZYE;

 ThreadHist<TH1D *>* ZRapidity_LHCb;

 ThreadHist<TH1D *>* ZPt_LHCb;

 ThreadHist<TH1D *>* phi_eta_LHCb;

 ThreadHist<TH1D *>* ZRapidityAbs;

 ThreadHist<TH1D *>* ZPzPtBalance;

 ThreadHist<TH1D *>* ZPzPtBalance_CC;

 ThreadHist<TH1D *>* ZPzPtBalance_CF;

 ThreadHist<TH1D *>* CosTheta;

 ThreadHist<TH1D *>* CosThetaQ;

 ThreadHist<TH1D *>* CosTheta_q;

 ThreadHist<TH1D *>* CosTheta_h;

 ThreadHist<TH1D *>* ZRapidity_qqbar;

 ThreadHist<TH1D *>* ZRapidity_qbarq;

 ThreadHist<TH1D *>* CollinsPhi;

 ThreadHist<TH1D *>* plot_phi_eta;

 ThreadHist<TH1D *>* leptonPt;

 ThreadHist<TH1D *>* leptonEta;

 //Lepton Antilepton eta abs
 ThreadHist<TH1D *>* LepEtaAbs;

 ThreadHist<TH1D *>* AntiLepEtaAbs;

 ThreadHist<TH1D *>* LepEtaAbs_CC;

 ThreadHist<TH1D *>* AntiLepEtaAbs_CC;

 ThreadHist<TH1D *>* LepEtaAbs_CF;

 ThreadHist<TH1D *>* AntiLepEtaAbs_CF;

 ThreadHist<TH1D *>* LepEtaAbs_LHCb;

 ThreadHist<TH1D *>* AntiLepEtaAbs_LHCb;

 //Lepton Antilepton eta
 ThreadHist<TH1D *>* LepEta;
 ThreadHist<TH1D *>* AntiLepEta;

 ThreadHist<TH1D *>* LepEta_CC;

 ThreadHist<TH1D *>* AntiLepEta_CC;

 ThreadHist<TH1D *>* LepEta_CF;

 ThreadHist<TH1D *>* AntiLepEta_CF;

 ThreadHist<TH1D *>* LepEta_LHCb;

 ThreadHist<TH1D *>* AntiLepEta_LHCb;

 ThreadHist<TH1D *>* LepEta_HighMass;
 ThreadHist<TH1D *>* AntiLepEta_HighMass;

 ThreadHist<TH1D *>* LepEta_ss;
 ThreadHist<TH1D *>* AntiLepEta_ss;

 ThreadHist<TH1D *>* LepEta_uubar;
 ThreadHist<TH1D *>* AntiLepEta_uubar;
 ThreadHist<TH1D *>* LepEta_ubaru;
 ThreadHist<TH1D *>* AntiLepEta_ubaru;

 ThreadHist<TH1D *>* ZRapidity_uubar;
 ThreadHist<TH1D *>* ZRapidity_ubaru;


 //Forward and backward rapidity
 ThreadHist<TH1D *>* FZRapidity;

 ThreadHist<TH1D *>* BZRapidity;

 ThreadHist<TH1D *>* FZRapidity_CC;

 ThreadHist<TH1D *>* BZRapidity_CC;

 ThreadHist<TH1D *>* FZRapidity_CF;

 ThreadHist<TH1D *>* BZRapidity_CF;

 ThreadHist<TH1D *>* FZRapidity_LHCb;

 ThreadHist<TH1D *>* BZRapidity_LHCb;

 //Average Forward and backward vs Mass ZY QT
 ThreadHist<TH2D *>* FAveZMass_ZY_QT;

 ThreadHist<TH2D *>* BAveZMass_ZY_QT;

 //Forward and backward vs Mass ZY QT
 ThreadHist<TH3D *>* FZMass_ZY_QT;

 ThreadHist<TH3D *>* BZMass_ZY_QT;

 ThreadHist<TH3D *>* CMS_FZMass_ZY_QT;

 ThreadHist<TH3D *>* CMS_BZMass_ZY_QT;

 ThreadHist<TH1D *>* AverageZPt_ZY_numer;
 ThreadHist<TH1D *>* AverageZPt_ZY_denom;
 TH1D *AverageZPt_ZY;

 ThreadHist<TH1D *>* AverageZPt_lnQ_numer;
 ThreadHist<TH1D *>* AverageZPt_lnQ_denom;
 TH1D *AverageZPt_lnQ;

 ThreadHist<TH1D *>* AverageLepE_ZY_numer;
 ThreadHist<TH1D *>* AverageLepE_ZY_denom;
 TH1D *AverageLepE_ZY;

 ThreadHist<TH1D *>* AverageAntiLepE_ZY_numer;
 ThreadHist<TH1D *>* AverageAntiLepE_ZY_denom;
 TH1D *AverageAntiLepE_ZY;

 TH1D *RatioLepE_ZY;

 //Forward and backward ZMass ZPt 2D plot
 ThreadHist<TH2D *>* FZmass_ZPt_uu;

 ThreadHist<TH2D *>* BZmass_ZPt_uu;

 ThreadHist<TH2D *>* FZmass_ZPt_dd;

 ThreadHist<TH2D *>* BZmass_ZPt_dd;


 ////////////////////////
 //  quark level plot  //
 ////////////////////////


 //Forward and backward ZMass
 ThreadHist<TH1D *>* FZmass_CC_uu;

 ThreadHist<TH1D *>* BZmass_CC_uu;

 ThreadHist<TH1D *>* FZmass_CF_uu;

 ThreadHist<TH1D *>* BZmass_CF_uu;

 ThreadHist<TH1D *>* FZmass_CC_dd;

 ThreadHist<TH1D *>* BZmass_CC_dd;

 ThreadHist<TH1D *>* FZmass_CF_dd;

 ThreadHist<TH1D *>* BZmass_CF_dd;

 ThreadHist<TH1D *>* FZmass_CC_gg;

 ThreadHist<TH1D *>* BZmass_CC_gg;

 ThreadHist<TH1D *>* FZmass_CF_gg;

 ThreadHist<TH1D *>* BZmass_CF_gg;

 ThreadHist<TH1D *>* FZmass_uu;

 ThreadHist<TH1D *>* BZmass_uu;

 ThreadHist<TH1D *>* FZmass_dd;

 ThreadHist<TH1D *>* BZmass_dd;

 ThreadHist<TH1D *>* FZmass_gg;

 ThreadHist<TH1D *>* BZmass_gg;

 ThreadHist<TH1D *>* ZMass_CC_uu;

 ThreadHist<TH1D *>* ZMass_CC_dd;

 ThreadHist<TH1D *>* ZMass_CC_gg;

 ThreadHist<TH1D *>* ZMass_CC_ss;

 ThreadHist<TH1D *>* ZMass_CC_cc;

 ThreadHist<TH1D *>* ZMass_CC_bb;

 ThreadHist<TH1D *>* ZMass_CC_utype;

 ThreadHist<TH1D *>* ZMass_CC_dtype;

 ThreadHist<TH1D *>* ZMass_CF_uu;

 ThreadHist<TH1D *>* ZMass_CF_dd;

 ThreadHist<TH1D *>* ZMass_CF_gg;

 ThreadHist<TH1D *>* ZMass_CF_ss;

 ThreadHist<TH1D *>* ZMass_CF_cc;

 ThreadHist<TH1D *>* ZMass_CF_bb;

 ThreadHist<TH1D *>* ZMass_CF_utype;

 ThreadHist<TH1D *>* ZMass_CF_dtype;

 ThreadHist<TH1D *>* ZMass_uu;

 ThreadHist<TH1D *>* ZMass_dd;

 ThreadHist<TH1D *>* ZMass_gg;

 ThreadHist<TH1D *>* ZMass_ss;

 ThreadHist<TH1D *>* ZMass_cc;

 ThreadHist<TH1D *>* ZMass_bb;

 ThreadHist<TH1D *>* ZMass_utype;

 ThreadHist<TH1D *>* ZMass_dtype;

 //AFB vs ZY
 ThreadHist<TH1D *>* FZY_uu;
 ThreadHist<TH1D *>* BZY_uu;
 ThreadHist<TH1D *>* FZY_dd;
 ThreadHist<TH1D *>* BZY_dd;


 //AFB vs ZPt
 ThreadHist<TH1D *>* FZPt_uu;

 ThreadHist<TH1D *>* BZPt_uu;

 ThreadHist<TH1D *>* FZPt_dd;

 ThreadHist<TH1D *>* BZPt_dd;

 //quark level ZPt ZY and ZMass
 ThreadHist<TH1D *>* ZPt_uub;

 ThreadHist<TH1D *>* ZRapidity_uub;

 ThreadHist<TH1D *>* ZMass_uub;

 ThreadHist<TH1D *>* ZPt_ddb;

 ThreadHist<TH1D *>* ZRapidity_ddb;

 ThreadHist<TH1D *>* ZMass_ddb;

 ThreadHist<TH1D *>* ZPt_ssb;

 ThreadHist<TH1D *>* ZRapidity_ssb;

 ThreadHist<TH1D *>* ZMass_ssb;

 //ZMass ZY QT 3D plot
 ThreadHist<TH3D *>* ZMass_ZY_QT;

 ThreadHist<TH3D *>* FZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* BZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* FZMass_ZY_QT_dd;

 ThreadHist<TH3D *>* BZMass_ZY_QT_dd;

 ThreadHist<TH3D *>* ZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* ZMass_ZY_QT_dd;

 ThreadHist<TH3D *>* ZMass_ZY_QT_ss;

 ThreadHist<TH3D *>* ZMass_ZY_QT_cc;

 ThreadHist<TH3D *>* ZMass_ZY_QT_bb;

 ThreadHist<TH3D *>* CMS_ZMass_ZY_QT;

 ThreadHist<TH3D *>* CMS_FZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* CMS_BZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* CMS_FZMass_ZY_QT_dd;

 ThreadHist<TH3D *>* CMS_BZMass_ZY_QT_dd;

 /////////////////////
 //  dilution plot  //
 /////////////////////

 //ZMass dilution
 ThreadHist<TH1D *>* ZMass_CC_total;
 ThreadHist<TH1D *>* ZMass_CC_wrong;
 TH1D *Dilution_ZMass_CC;

 ThreadHist<TH1D *>* ZMass_CF_total;
 ThreadHist<TH1D *>* ZMass_CF_wrong;
 TH1D *Dilution_ZMass_CF;

 ThreadHist<TH1D *>* ZMass_Full_total;
 ThreadHist<TH1D *>* ZMass_Full_wrong;
 TH1D *Dilution_ZMass_Full;

 //quark ZMass dilution
 ThreadHist<TH1D *>* ZMass_CC_uu_total;
 ThreadHist<TH1D *>* ZMass_CC_uu_wrong;
 TH1D *Dilution_ZMass_CC_uu;

 ThreadHist<TH1D *>* ZMass_CC_dd_total;
 ThreadHist<TH1D *>* ZMass_CC_dd_wrong;
 TH1D *Dilution_ZMass_CC_dd;

 ThreadHist<TH1D *>* ZMass_CF_uu_total;
 ThreadHist<TH1D *>* ZMass_CF_uu_wrong;
 TH1D *Dilution_ZMass_CF_uu;

 ThreadHist<TH1D *>* ZMass_CF_dd_total;
 ThreadHist<TH1D *>* ZMass_CF_dd_wrong;
 TH1D *Dilution_ZMass_CF_dd;

 ThreadHist<TH1D *>* ZMass_Full_uu_total;
 ThreadHist<TH1D *>* ZMass_Full_uu_wrong;
 TH1D *Dilution_ZMass_Full_uu;

 ThreadHist<TH1D *>* ZMass_Full_dd_total;
 ThreadHist<TH1D *>* ZMass_Full_dd_wrong;
 TH1D *Dilution_ZMass_Full_dd;

 ThreadHist<TH1D *>* ZMass_Full_ss_total;
 ThreadHist<TH1D *>* ZMass_Full_ss_wrong;
 TH1D *Dilution_ZMass_Full_ss;

 ThreadHist<TH1D *>* ZMass_Full_cc_total;
 ThreadHist<TH1D *>* ZMass_Full_cc_wrong;
 TH1D *Dilution_ZMass_Full_cc;

 ThreadHist<TH1D *>* ZMass_Full_bb_total;
 ThreadHist<TH1D *>* ZMass_Full_bb_wrong;
 TH1D *Dilution_ZMass_Full_bb;

 //Dilution vs ZY
 ThreadHist<TH1D *>* ZY_uu_wrong;
 ThreadHist<TH1D *>* ZY_uu_total;
 TH1D* Dilution_ZY_uu;
 TH1D* DilutionFactor_ZY_uu;
 TH1D* RelativeXsec_ZY_uu;
 TH1D* CoefficientDilution_ZY_uu;

 ThreadHist<TH1D *>* ZY_dd_wrong;
 ThreadHist<TH1D *>* ZY_dd_total;
 TH1D* Dilution_ZY_dd;
 TH1D* DilutionFactor_ZY_dd;
 TH1D* RelativeXsec_ZY_dd;
 TH1D* CoefficientDilution_ZY_dd;

 //Dilution vs ZPt ZY CosThetaQ
 ThreadHist<TH1D *>* ZPt_total;
 ThreadHist<TH1D *>* ZPt_wrong;
 TH1D *Dilution_ZPt;

 ThreadHist<TH1D *>* ZRapidity_total;
 ThreadHist<TH1D *>* ZRapidity_wrong;
 TH1D *Dilution_ZRapidity;

 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_wrong;
 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_total;
 TH3D *Dilution_ZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_wrong;
 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_total;
 TH3D *Dilution_ZMass_ZY_QT_dd;

 ThreadHist<TH3D *>* CMS_ZMass_ZY_QT_uu_wrong;
 ThreadHist<TH3D *>* CMS_ZMass_ZY_QT_uu_total;
 TH3D *Dilution_CMS_ZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* CMS_ZMass_ZY_QT_dd_wrong;
 ThreadHist<TH3D *>* CMS_ZMass_ZY_QT_dd_total;
 TH3D *Dilution_CMS_ZMass_ZY_QT_dd;

 ThreadHist<TH3D *>* XSection_M_Y_CosTheta;

 ThreadHist<TH1D *>* ZPt_y1_Total;

 ThreadHist<TH1D *>* ZPt_y1_Fiduc;

 ThreadHist<TH1D *>* ZPt_y2_Total;

 ThreadHist<TH1D *>* ZPt_y2_Fiduc;

 ThreadHist<TH1D *>* ZPt_y3_Total;

 ThreadHist<TH1D *>* ZPt_y3_Fiduc;

 ThreadHist<TH1D *>* ZPt_y4_Total;

 ThreadHist<TH1D *>* ZPt_y4_Fiduc;

 ThreadHist<TH1D *>* ZPt_y5_Total;

 ThreadHist<TH1D *>* ZPt_y5_Fiduc;

 ThreadHist<TH1D *>* ZPt_y6_Total;

 ThreadHist<TH1D *>* ZPt_y6_Fiduc;

 ThreadHist<TH1D *>* ATLASZPt_Fiduc;

 ThreadHist<TH1D *>* ATLASZPt_Total;

 ThreadHist<TH2D *>* ATLASZPt_2D_Fiduc;

 ThreadHist<TH2D *>* ATLASZPt_2D_Total;

 ThreadHist<TH2D *>* ATLASZPt_2D_Total_uu;

 ThreadHist<TH2D *>* ATLASZPt_2D_Total_dd;

 ThreadHist<TH2D *>* ATLASZPt_2D_Total_MassWindow;

 ThreadHist<TH1D *>* ZPt_Threshold;

 ThreadHist<AngularFunction *>* A0_ZPt;

 ThreadHist<AngularFunction *>* A1_ZPt;

 ThreadHist<AngularFunction *>* A2_ZPt;

 ThreadHist<AngularFunction *>* A3_ZPt;

 ThreadHist<AngularFunction *>* A4_ZPt;

 ThreadHist<AngularFunction *>* L0_ZPt;

 ThreadHist<AngularFunction *>* A0_ZPt_LHCb;

 ThreadHist<AngularFunction *>* A1_ZPt_LHCb;

 ThreadHist<AngularFunction *>* A2_ZPt_LHCb;

 ThreadHist<AngularFunction *>* A3_ZPt_LHCb;

 ThreadHist<AngularFunction *>* A4_ZPt_LHCb;

 ThreadHist<AngularFunction *>* A02_ZPt_LHCb;

 ThreadHist<AngularFunction *>* A0_ZY_LHCb;

 ThreadHist<AngularFunction *>* A1_ZY_LHCb;

 ThreadHist<AngularFunction *>* A2_ZY_LHCb;

 ThreadHist<AngularFunction *>* A3_ZY_LHCb;

 ThreadHist<AngularFunction *>* A4_ZY_LHCb;

 ThreadHist<AngularFunction *>* A02_ZY_LHCb;

 ThreadHist<AngularFunction *>* QuarkA4_ZPt_uu;

 ThreadHist<AngularFunction *>* QuarkA4_ZY_uu;

 ThreadHist<AngularFunction *>* QuarkA4_ZPt_dd;

 ThreadHist<AngularFunction *>* QuarkA4_ZY_dd;

 ThreadHist<AngularFunction *>* QuarkL0_ZPt_uu;

 ThreadHist<AngularFunction *>* QuarkL0_ZY_uu;

 ThreadHist<AngularFunction *>* QuarkL0_ZPt_dd;

 ThreadHist<AngularFunction *>* QuarkL0_ZY_dd;

 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_uu;

 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_dd;

 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_ss;

 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_cc;

 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_bb;


// For study energy scale //
 ThreadHist<CovHist *>* FZmass_CC_Cov;

 ThreadHist<CovHist *>* BZmass_CC_Cov;

 ThreadHist<CovHist *>* FZmass_CF_Cov;

 ThreadHist<CovHist *>* BZmass_CF_Cov;
/////////////////////////////////////////

 int ZY_bin = 5; double ZY_left = 0.0; double ZY_right = 5.0;
 int ZY_CC_bin = 3; double ZY_CC_left = 0.0; double ZY_CC_right = 2.5;
 int ZY_CF_bin = 3; double ZY_CF_left = 1.0; double ZY_CF_right = 4.0;
// double rangeZY[ZY_bin + 1];
// double rangeZYCC[ZY_CC_bin + 1];
// double rangeZYCF[ZY_CF_bin + 1];

 int ZPt_bin = 5; double ZPt_left = 0.0; double ZPt_right = 100.0;
 int ZPt_CC_bin = 5; double ZPt_CC_left = 0.0; double ZPt_CC_right = 100.0;
 int ZPt_CF_bin = 5; double ZPt_CF_left = 0.0; double ZPt_CF_right = 100.0;
// double RangeZPt[ZPt_bin + 1];
// double RangeZPtCC[ZPt_CC_bin + 1];
// double RangeZPtCF[ZPt_CF_bin + 1];


 TH1D *AFB_CC;
 TH1D *AFB_CF;
 TH1D *AFB_Full;
 TH1D *AFB_LHCb;

 TH2D *AFB_Mass_ZY_CC;
 TH2D *AFB_Mass_ZY_CF;

 TH1D *AFB_CC_80_100;
 TH1D *AFB_CF_80_100;
 TH1D *AFB_Full_80_100;
 TH1D *AFB_LHCb_80_100;

 TH2D *AveAFB_ZY_ZPt;
 TH3D *AFB_Mass_ZY_ZPt;
 TH3D *AFB_CMS_Mass_ZY_ZPt;


 TH1D *AFBSlope_CC;
 TH1D *AFBSlope_CF;
 TH1D *AFBSlope_Full;
 TH1D *AFBSlope_LHCb;

 TH1D *AFBSlope_82_98_CC;
 TH1D *AFBSlope_82_98_CF;
 TH1D *AFBSlope_82_98_Full;
 TH1D *AFBSlope_82_98_LHCb;

 TH1D *AFBSlope_84_96_CC;
 TH1D *AFBSlope_84_96_CF;
 TH1D *AFBSlope_84_96_Full;
 TH1D *AFBSlope_84_96_LHCb;

 TH1D *AFBOffset_CC;
 TH1D *AFBOffset_CF;
 TH1D *AFBOffset_Full;
 TH1D *AFBOffset_LHCb;

 TH1D *AFBOffset_82_98_CC;
 TH1D *AFBOffset_82_98_CF;
 TH1D *AFBOffset_82_98_Full;
 TH1D *AFBOffset_82_98_LHCb;

 TH1D *AFBOffset_84_96_CC;
 TH1D *AFBOffset_84_96_CF;
 TH1D *AFBOffset_84_96_Full;
 TH1D *AFBOffset_84_96_LHCb;

 TH1D *AFBQuarkSlope_CC;
 TH1D *AFBQuarkSlope_CF;
 TH1D *AFBQuarkSlope_Full;
 TH1D *AFBQuarkSlope_LHCb;

 TH1D *AFBQuarkSlope_82_98_CC;
 TH1D *AFBQuarkSlope_82_98_CF;
 TH1D *AFBQuarkSlope_82_98_Full;

 TH1D *AFBQuarkSlope_84_96_CC;
 TH1D *AFBQuarkSlope_84_96_CF;
 TH1D *AFBQuarkSlope_84_96_Full;

 TH1D *AFBQuarkOffset_CC;
 TH1D *AFBQuarkOffset_CF;
 TH1D *AFBQuarkOffset_Full;
 TH1D *AFBQuarkOffset_LHCb;

 TH1D *AFBQuarkOffset_82_98_CC;
 TH1D *AFBQuarkOffset_82_98_CF;
 TH1D *AFBQuarkOffset_82_98_Full;

 TH1D *AFBQuarkOffset_84_96_CC;
 TH1D *AFBQuarkOffset_84_96_CF;
 TH1D *AFBQuarkOffset_84_96_Full;

 TH1D *AFBDiff_CC;
 TH1D *AFBDiff_CF;
 TH1D *AFBDiff_Full;
 TH1D *AFBDiff_LHCb;

 TH1D *AFBDiff_CC_ZPole;
 TH1D *AFBDiff_CF_ZPole;
 TH1D *AFBDiff_Full_ZPole;
 TH1D *AFBDiff_LHCb_ZPole;

 TH1D *AFBDiff_CC_Side;
 TH1D *AFBDiff_CF_Side;
 TH1D *AFBDiff_Full_Side;
 TH1D *AFBDiff_LHCb_Side;

 TH1D *AFBGradient_CC;
 TH1D *AFBGradient_CF;
 TH1D *AFBGradient_Full;
 TH1D *AFBGradient_LHCb;

 TH1D *AFBQuarkGradient_CC;
 TH1D *AFBQuarkGradient_CF;
 TH1D *AFBQuarkGradient_Full;

 TH1D *DilutionGradient_CC;
 TH1D *DilutionGradient_CF;
 TH1D *DilutionGradient_Full;

 TH1D *AFBQuarkDiff_CC;
 TH1D *AFBQuarkDiff_CF;
 TH1D *AFBQuarkDiff_Full;

 TH1D *AFBQuarkDiff_CC_Side;
 TH1D *AFBQuarkDiff_CF_Side;
 TH1D *AFBQuarkDiff_Full_Side;

 TH1D *AFBQuarkDiff_CC_ZPole;
 TH1D *AFBQuarkDiff_CF_ZPole;
 TH1D *AFBQuarkDiff_Full_ZPole;

 TH1D *AFBQuarkFraction_CC;
 TH1D *AFBQuarkFraction_CF;
 TH1D *AFBQuarkFraction_Full;

 TH1D *AFBS0Fraction_CC;
 TH1D *AFBS0Fraction_CF;
 TH1D *AFBS0Fraction_Full;

 TH1D *AFB_CC_uu;
 TH1D *AFB_CF_uu;
 TH1D *AFB_Full_uu;
 TH1D *AFB_LHCb_uu;

 TH1D *AFB_CC_dd;
 TH1D *AFB_CF_dd;
 TH1D *AFB_Full_dd;
 TH1D *AFB_LHCb_dd;

 TH1D *AFB_CC_qq;
 TH1D *AFB_CF_qq;
 TH1D *AFB_Full_qq;
 TH1D *AFB_LHCb_qq;

 TH1D *AFB_ZPt_uu;
 TH1D *AFB_ZPt_dd;

 TH2D *AFB_Mass_ZPt_Full_uu;
 TH2D *AFB_Mass_ZPt_Full_dd;

 TH3D *AFB_Mass_ZY_ZPt_uu;
 TH3D *AFB_Mass_ZY_ZPt_dd;

 TH3D *AFB_CMS_Mass_ZY_ZPt_uu;
 TH3D *AFB_CMS_Mass_ZY_ZPt_dd;

 TH1D *XsecFraction_CC_uu;
 TH1D *XsecFraction_CC_dd;
 TH1D *XsecFraction_CF_uu;
 TH1D *XsecFraction_CF_dd;
 TH1D *XsecFraction_Full_uu;
 TH1D *XsecFraction_Full_dd;

 TH1D *CoefficientDilution_CC_uu;
 TH1D *CoefficientDilution_CC_dd;
 TH1D *CoefficientDilution_CF_uu;
 TH1D *CoefficientDilution_CF_dd;
 TH1D *CoefficientDilution_Full_uu;
 TH1D *CoefficientDilution_Full_dd;

 TH1D *ResidualDilution_CC_uu;
 TH1D *ResidualDilution_CC_dd;
 TH1D *ResidualDilution_CF_uu;
 TH1D *ResidualDilution_CF_dd;
 TH1D *ResidualDilution_Full_uu;
 TH1D *ResidualDilution_Full_dd;

 TH1D *DilutionAverage_CC_uu;
 TH1D *DilutionAverage_CC_dd;
 TH1D *DilutionAverage_CF_uu;
 TH1D *DilutionAverage_CF_dd;
 TH1D *DilutionAverage_Full_uu;
 TH1D *DilutionAverage_Full_dd;

 TH3D *CoefficientDilution_ZMass_ZY_QT_uu;
 TH3D *CoefficientDilution_ZMass_ZY_QT_dd;
 TH3D *ResidualDilution_ZMass_ZY_QT_uu;
 TH3D *ResidualDilution_ZMass_ZY_QT_dd;
 TH3D *DilutionAverage_ZMass_ZY_QT_uu;
 TH3D *DilutionAverage_ZMass_ZY_QT_dd;

 TH3D *CoefficientDilution_CMS_ZMass_ZY_QT_uu;
 TH3D *CoefficientDilution_CMS_ZMass_ZY_QT_dd;
 TH3D *ResidualDilution_CMS_ZMass_ZY_QT_uu;
 TH3D *ResidualDilution_CMS_ZMass_ZY_QT_dd;
 TH3D *DilutionAverage_CMS_ZMass_ZY_QT_uu;
 TH3D *DilutionAverage_CMS_ZMass_ZY_QT_dd;

 TH1D *AveAFB_CC;
 TH1D *AveAFB_CF;
 TH1D *AveAFB_Full;
 TH1D *AveAFB_LHCb;

 TH1D *QuarkAveAFB_CC;
 TH1D *QuarkAveAFB_CF;
 TH1D *QuarkAveAFB_Full;

 TH1D *LepAsym;
 TH1D *LepAsym_CC;
 TH1D *LepAsym_CF;
 TH1D *LepAsym_LHCb;

 TH1D *AFB_ZY;
 TH1D *AFB_ZY_CC;
 TH1D *AFB_ZY_CF;
 TH1D *AFB_ZY_LHCb;
 TH1D *AFB_ZY_uu;
 TH1D *AFB_ZY_dd;

 TH1D *LepWidthDiff;
 TH1D *LepWidthDiff_CC;
 TH1D *LepWidthDiff_CF;
 TH1D *LepWidthDiff_LHCb;

 TH1D *CutEff_ZPt_y1;
 TH1D *CutEff_ZPt_y2;
 TH1D *CutEff_ZPt_y3;
 TH1D *CutEff_ZPt_y4;
 TH1D *CutEff_ZPt_y5;
 TH1D *CutEff_ZPt_y6;
 TH2D *ATLASZPt_2D_Fiduc_Final;
 TH2D *ATLASZPt_2D_Total_Final;
 TH2D *ATLASZPt_2D_Total_uu_Final;
 TH2D *ATLASZPt_2D_Total_dd_Final;
 TH2D *ATLASZPt_2D_Total_MassWindow_Final;

 TH1D *QuarkA4Ratio_ZPt_uu;
 TH1D *QuarkA4Ratio_ZY_uu;
 TH1D *QuarkA4Ratio_ZPt_dd;
 TH1D *QuarkA4Ratio_ZY_dd;

 virtual void bookHists(int TotalThread);
 virtual void bookCovHists(int TotalThread);
 virtual void outputInformation();

// template<class T>

 TFile *DataFile;
 TH1D *DataHist;

 virtual void InputData(TString FileName, TString HistName);


};
#endif
