#ifndef __HistsResBosCMS_H_
#define __HistsResBosCMS_H_
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

#include "ReadInRoot/ResBosZPt.h"

class ResBosZPt;

using namespace std;

class HistsResBosCMS : public makeHists
{
 public:

 ThreadHist<TH1D *>* ZY_x1;

 ThreadHist<TH1D *>* ZY_x2;

 ThreadHist<TH1D *>* ZY_x3;

 //Forward and backward vs Mass ZY QT
 ThreadHist<TH3D *>* FZMass_ZY_QT;

 ThreadHist<TH3D *>* BZMass_ZY_QT;

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

 /////////////////////
 //  dilution plot  //
 /////////////////////

 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_wrong;
 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_total;
 TH3D *Dilution_ZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_wrong;
 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_total;
 TH3D *Dilution_ZMass_ZY_QT_dd;

 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_YP_wrong;
 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_YP_right;
 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_YM_wrong;
 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_YM_right;

 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_YP_wrong;
 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_YP_right;
 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_YM_wrong;
 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_YM_right;

 ThreadHist<TH3D *>* ZMass_ZY_QT_YP;
 ThreadHist<TH3D *>* ZMass_ZY_QT_YM;

 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_uu;

 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_dd;

 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_ss;

 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_cc;

 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_bb;

 /////////////////////////
 //  Theory prediction  //
 /////////////////////////

 ThreadHist<TH1D *>* ZpT_Inclusive;

 ThreadHist<TH1D *>* ATLAS8TeV_pT_Mass12_20_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Mass20_30_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Mass30_46_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Mass46_66_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Mass66_116_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Mass116_150_Theory;

 ThreadHist<TH1D *>* ATLAS8TeV_Phi_Y1_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_Phi_Y2_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_Phi_Y3_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_Phi_Y4_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_Phi_Y5_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_Phi_Y6_Theory;

 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y1_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y2_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y3_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y4_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y5_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y6_Theory;

 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y1_Total;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y2_Total;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y3_Total;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y4_Total;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y5_Total;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y6_Total;

 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y1_uu_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y2_uu_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y3_uu_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y4_uu_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y5_uu_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y6_uu_Theory;

 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y1_dd_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y2_dd_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y3_dd_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y4_dd_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y5_dd_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_pT_Y6_dd_Theory;

 ThreadHist<TH1D *>* ATLAS13TeV_pT_Theory;
 ThreadHist<TH1D *>* ATLAS13TeV_Phi_Theory;

 ThreadHist<TH1D *>* CMS13TeV_pT_Theory;
 ThreadHist<TH1D *>* CMS13TeV_Phi_Theory;

 ThreadHist<TH1D *>* LHCb13TeV_pT_Theory;
 ThreadHist<TH1D *>* LHCb13TeV_pT_Total;
 ThreadHist<TH1D *>* LHCb13TeV_pT_uu_Theory;
 ThreadHist<TH1D *>* LHCb13TeV_pT_dd_Theory;
 ThreadHist<TH1D *>* LHCb13TeV_Phi_Theory;

 ThreadHist<TH1D *>* CMS13TeV_pT_Y1_Theory;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y2_Theory;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y3_Theory;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y4_Theory;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y5_Theory;

 ThreadHist<TH1D *>* CMS13TeV_pT_Y1_Total;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y2_Total;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y3_Total;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y4_Total;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y5_Total;

 ThreadHist<TH1D *>* CMS13TeV_pT_Y1_uu_Theory;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y2_uu_Theory;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y3_uu_Theory;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y4_uu_Theory;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y5_uu_Theory;

 ThreadHist<TH1D *>* CMS13TeV_pT_Y1_dd_Theory;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y2_dd_Theory;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y3_dd_Theory;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y4_dd_Theory;
 ThreadHist<TH1D *>* CMS13TeV_pT_Y5_dd_Theory;

 ThreadHist<TH1D *>* CMS13TeV_yZ_Theory;
 ThreadHist<TH1D *>* CMS13TeV_yZ_Total;
 ThreadHist<TH1D *>* LHCb13TeV_yZ_Theory;

 ThreadHist<TH1D *>* ATLAS8TeV_WPlus_Eta_Theory;
 ThreadHist<TH1D *>* ATLAS8TeV_WMinus_Eta_Theory;

 ThreadHist<TH1D *>* ATLAS7TeV_pT_Theory;
 ThreadHist<TH1D *>* ATLAS7TeV_pT_Y1_Theory;
 ThreadHist<TH1D *>* ATLAS7TeV_pT_Y2_Theory;
 ThreadHist<TH1D *>* ATLAS7TeV_pT_Y3_Theory;

 ThreadHist<TH1D *>* CMS8TeV_pT_Theory;

 ThreadHist<TH1D *>* CMS7TeV_pT_Theory;

 ThreadHist<TH1D *>* ATLAS7TeV_Phi_Theory;
 ThreadHist<TH1D *>* ATLAS7TeV_Phi_Y1_Theory;
 ThreadHist<TH1D *>* ATLAS7TeV_Phi_Y2_Theory;
 ThreadHist<TH1D *>* ATLAS7TeV_Phi_Y3_Theory;

 ThreadHist<AngularFunction* >* ATLAS8TeV_A0_pT_Theory;
 ThreadHist<AngularFunction* >* ATLAS8TeV_A1_pT_Theory;
 ThreadHist<AngularFunction* >* ATLAS8TeV_A2_pT_Theory;
 ThreadHist<AngularFunction* >* ATLAS8TeV_A3_pT_Theory;
 ThreadHist<AngularFunction* >* ATLAS8TeV_A4_pT_Theory;
 ThreadHist<AngularFunction* >* ATLAS8TeV_A02_pT_Theory;

////////////////////////////////////////////////////////////////////////////////////

 /////////////////////////////
 // CTEQ Drell-Yan k-factor //
 /////////////////////////////

 ThreadHist<TH1D *>* E245_LHCb7TeV_Z;
 ThreadHist<TH1D *>* E245_LHCb7TeV_WPlus;
 ThreadHist<TH1D *>* E245_LHCb7TeV_WMinus;

 ThreadHist<TH1D *>* E246_LHCb8TeV_Z;

 ThreadHist<TH1D *>* E248_ATLAS7TeV_Z;
 ThreadHist<TH1D *>* E248_ATLAS7TeV_WPlus;
 ThreadHist<TH1D *>* E248_ATLAS7TeV_WMinus;

 ThreadHist<TH1D *>* E249_CMS8TeV_WPlus;
 ThreadHist<TH1D *>* E249_CMS8TeV_WMinus;

 ThreadHist<TH1D *>* E250_LHCb8TeV_Z;
 ThreadHist<TH1D *>* E250_LHCb8TeV_WPlus;
 ThreadHist<TH1D *>* E250_LHCb8TeV_WMinus;

 ThreadHist<TH1D *>* E253_ATLAS8TeV_ZPt1;
 ThreadHist<TH1D *>* E253_ATLAS8TeV_ZPt2;
 ThreadHist<TH1D *>* E253_ATLAS8TeV_ZPt3;

 ThreadHist<TH1D *>* E225_CDF1p8TeV_WPlus;
 ThreadHist<TH1D *>* E225_CDF1p8TeV_WMinus;

 ThreadHist<TH1D *>* E227_CDF1p96TeV_WPlus;
 ThreadHist<TH1D *>* E227_CDF1p96TeV_WMinus;

 ThreadHist<TH1D *>* E234_D01p96TeV_WPlus;
 ThreadHist<TH1D *>* E234_D01p96TeV_WMinus;

 ThreadHist<TH1D *>* E260_D01p96TeV_Z;

 ThreadHist<TH1D *>* E261_CDF1p96TeV_Z;

 ThreadHist<TH1D *>* E266_CMS7TeV_WPlus;
 ThreadHist<TH1D *>* E266_CMS7TeV_WMinus;

 ThreadHist<TH1D *>* E267_CMS7TeV_WPlus;
 ThreadHist<TH1D *>* E267_CMS7TeV_WMinus;

 ThreadHist<TH1D *>* E281_D01p96TeV_WPlus;
 ThreadHist<TH1D *>* E281_D01p96TeV_WMinus;

 ThreadHist<TH1D *>* E211_ATLAS8TeV_WPlus;
 ThreadHist<TH1D *>* E211_ATLAS8TeV_WMinus;

 ThreadHist<TH1D *>* E212_CMS13TeV_Z;

 ThreadHist<TH1D *>* E218_LHCb13TeV_Z;

 ThreadHist<TH2D *>* E214_ATLAS8TeV_Z1;
 ThreadHist<TH2D *>* E214_ATLAS8TeV_Z2;
 ThreadHist<TH2D *>* E214_ATLAS8TeV_Z3;
 ThreadHist<TH2D *>* E214_ATLAS8TeV_Z4;
 ThreadHist<TH2D *>* E214_ATLAS8TeV_Z5;
 ThreadHist<TH2D *>* E214_ATLAS8TeV_Z6;

 ThreadHist<TH1D *>* E215_ATLAS5TeV_Z;
 ThreadHist<TH1D *>* E215_ATLAS5TeV_WPlus;
 ThreadHist<TH1D *>* E215_ATLAS5TeV_WMinus;

 ThreadHist<TH1D *>* E217_LHCb8TeV_WPlus;
 ThreadHist<TH1D *>* E217_LHCb8TeV_WMinus;

////////////////////////////////////////////////////////////////////////////////////

 ThreadHist<TH1D *>* ZPt_FineBin;
 ThreadHist<TH1D *>* ZPt_FineBin_HighPt;

 ThreadHist<TH1D *>* TotalCrossSection_8TeV;

 TH3D *AFB_Mass_ZY_ZPt;

 TH3D *AFB_Mass_ZY_ZPt_uu;
 TH3D *AFB_Mass_ZY_ZPt_dd;

 TH3D *CoefficientDilution_ZMass_ZY_QT_uu;
 TH3D *CoefficientDilution_ZMass_ZY_QT_dd;
 TH3D *ResidualDilution_ZMass_ZY_QT_uu;
 TH3D *ResidualDilution_ZMass_ZY_QT_dd;
 TH3D *DilutionAverage_ZMass_ZY_QT_uu;
 TH3D *DilutionAverage_ZMass_ZY_QT_dd;

 TH3D *OneMinusTwoD_uu;
 TH3D *OneMinusTwoD_dd;
 TH3D *RelativeCrossSection_uu;
 TH3D *RelativeCrossSection_dd;

 ////////////////////////
 // Check with NNLOJet //
 ////////////////////////

 ThreadHist<TH2D *>* WPlusYQT;

 //////////////////////
 //  Published Data  //
 //////////////////////

 TH1D* ATLAS8TeV_pT_Mass12_20_Data;
 TH1D* ATLAS8TeV_pT_Mass20_30_Data;
 TH1D* ATLAS8TeV_pT_Mass30_46_Data;
 TH1D* ATLAS8TeV_pT_Mass46_66_Data;
 TH1D* ATLAS8TeV_pT_Mass66_116_Data;
 TH1D* ATLAS8TeV_pT_Mass116_150_Data;
 TH1D* ATLAS8TeV_Phi_Y1_Data;
 TH1D* ATLAS8TeV_Phi_Y2_Data;
 TH1D* ATLAS8TeV_Phi_Y3_Data;
 TH1D* ATLAS8TeV_Phi_Y4_Data;
 TH1D* ATLAS8TeV_Phi_Y5_Data;
 TH1D* ATLAS8TeV_Phi_Y6_Data;
 TH1D* ATLAS8TeV_pT_Y1_Data;
 TH1D* ATLAS8TeV_pT_Y2_Data;
 TH1D* ATLAS8TeV_pT_Y3_Data;
 TH1D* ATLAS8TeV_pT_Y4_Data;
 TH1D* ATLAS8TeV_pT_Y5_Data;
 TH1D* ATLAS8TeV_pT_Y6_Data;
 TH1D* ATLAS13TeV_pT_Data;
 TH1D* ATLAS13TeV_Phi_Data;
 TH1D* CMS13TeV_pT_Data;
 TH1D* CMS13TeV_Phi_Data;
 TH1D* LHCb13TeV_pT_Data;
 TH1D* LHCb13TeV_Phi_Data;
 TH1D* CMS13TeV_pT_Y1_Data;
 TH1D* CMS13TeV_pT_Y2_Data;
 TH1D* CMS13TeV_pT_Y3_Data;
 TH1D* CMS13TeV_pT_Y4_Data;
 TH1D* CMS13TeV_pT_Y5_Data;
 TH1D* CMS13TeV_yZ_Data;
 TH1D* ATLAS8TeV_A0_pT_Data;
 TH1D* ATLAS8TeV_A1_pT_Data;
 TH1D* ATLAS8TeV_A2_pT_Data;
 TH1D* ATLAS8TeV_A3_pT_Data;
 TH1D* ATLAS8TeV_A4_pT_Data;
 TH1D* ATLAS8TeV_A02_pT_Data;
 TH1D* ATLAS8TeV_A0_pT_Data_UnReg;
 TH1D* ATLAS8TeV_A1_pT_Data_UnReg;
 TH1D* ATLAS8TeV_A2_pT_Data_UnReg;
 TH1D* ATLAS8TeV_A3_pT_Data_UnReg;
 TH1D* ATLAS8TeV_A4_pT_Data_UnReg;
 TH1D* ATLAS8TeV_A02_pT_Data_UnReg;
 TH1D* ATLAS7TeV_pT_Data;
 TH1D* ATLAS7TeV_pT_Y1_Data;
 TH1D* ATLAS7TeV_pT_Y2_Data;
 TH1D* ATLAS7TeV_pT_Y3_Data;
 TH1D* CMS8TeV_pT_Data;
 TH1D* CMS7TeV_pT_Data;
 TH1D* ATLAS7TeV_Phi_Data;
 TH1D* ATLAS7TeV_Phi_Y1_Data;
 TH1D* ATLAS7TeV_Phi_Y2_Data;
 TH1D* ATLAS7TeV_Phi_Y3_Data;

 TH1D* ATLAS8TeV_pT_Mass12_20_Theory_Final;
 TH1D* ATLAS8TeV_pT_Mass20_30_Theory_Final;
 TH1D* ATLAS8TeV_pT_Mass30_46_Theory_Final;
 TH1D* ATLAS8TeV_pT_Mass46_66_Theory_Final;
 TH1D* ATLAS8TeV_pT_Mass66_116_Theory_Final;
 TH1D* ATLAS8TeV_pT_Mass116_150_Theory_Final;
 TH1D* ATLAS8TeV_Phi_Y1_Theory_Final;
 TH1D* ATLAS8TeV_Phi_Y2_Theory_Final;
 TH1D* ATLAS8TeV_Phi_Y3_Theory_Final;
 TH1D* ATLAS8TeV_Phi_Y4_Theory_Final;
 TH1D* ATLAS8TeV_Phi_Y5_Theory_Final;
 TH1D* ATLAS8TeV_Phi_Y6_Theory_Final;
 TH1D* ATLAS8TeV_pT_Y1_Theory_Final;
 TH1D* ATLAS8TeV_pT_Y2_Theory_Final;
 TH1D* ATLAS8TeV_pT_Y3_Theory_Final;
 TH1D* ATLAS8TeV_pT_Y4_Theory_Final;
 TH1D* ATLAS8TeV_pT_Y5_Theory_Final;
 TH1D* ATLAS8TeV_pT_Y6_Theory_Final;
 TH1D* ATLAS13TeV_pT_Theory_Final;
 TH1D* ATLAS13TeV_Phi_Theory_Final;
 TH1D* CMS13TeV_pT_Theory_Final;
 TH1D* CMS13TeV_Phi_Theory_Final;
 TH1D* LHCb13TeV_pT_Theory_Final;
 TH1D* LHCb13TeV_Phi_Theory_Final;
 TH1D* CMS13TeV_pT_Y1_Theory_Final;
 TH1D* CMS13TeV_pT_Y2_Theory_Final;
 TH1D* CMS13TeV_pT_Y3_Theory_Final;
 TH1D* CMS13TeV_pT_Y4_Theory_Final;
 TH1D* CMS13TeV_pT_Y5_Theory_Final;
 TH1D* CMS13TeV_yZ_Theory_Final;

 TH1D* ATLAS8TeV_WPlus_Eta_Theory_Final;
 TH1D* ATLAS8TeV_WMinus_Eta_Theory_Final;

 TH1D* ATLAS7TeV_pT_Theory_Final;
 TH1D* ATLAS7TeV_pT_Y1_Theory_Final;
 TH1D* ATLAS7TeV_pT_Y2_Theory_Final;
 TH1D* ATLAS7TeV_pT_Y3_Theory_Final;
 TH1D* CMS8TeV_pT_Theory_Final;

 TH1D* CMS7TeV_pT_Theory_Final;
 TH1D* ATLAS7TeV_Phi_Theory_Final;
 TH1D* ATLAS7TeV_Phi_Y1_Theory_Final;
 TH1D* ATLAS7TeV_Phi_Y2_Theory_Final;
 TH1D* ATLAS7TeV_Phi_Y3_Theory_Final;

 TH1D* ATLAS8TeV_pT_Y1_KFactor;
 TH1D* ATLAS8TeV_pT_Y2_KFactor;
 TH1D* ATLAS8TeV_pT_Y3_KFactor;
 TH1D* ATLAS8TeV_pT_Y4_KFactor;
 TH1D* ATLAS8TeV_pT_Y5_KFactor;
 TH1D* ATLAS8TeV_pT_Y6_KFactor;
 TH1D* ATLAS8TeV_pT_Mass66_116_KFactor;

 TH1D* ATLAS8TeV_pT_Y1_Theory_HigherOrder;
 TH1D* ATLAS8TeV_pT_Y2_Theory_HigherOrder;
 TH1D* ATLAS8TeV_pT_Y3_Theory_HigherOrder;
 TH1D* ATLAS8TeV_pT_Y4_Theory_HigherOrder;
 TH1D* ATLAS8TeV_pT_Y5_Theory_HigherOrder;
 TH1D* ATLAS8TeV_pT_Y6_Theory_HigherOrder;
 TH1D* ATLAS8TeV_pT_Mass66_116_Theory_HigherOrder;

 TH1D* ATLAS8TeV_pT_Y1_CutEff;
 TH1D* ATLAS8TeV_pT_Y2_CutEff;
 TH1D* ATLAS8TeV_pT_Y3_CutEff;
 TH1D* ATLAS8TeV_pT_Y4_CutEff;
 TH1D* ATLAS8TeV_pT_Y5_CutEff;
 TH1D* ATLAS8TeV_pT_Y6_CutEff;

 TH1D* CMS13TeV_pT_Y1_CutEff;
 TH1D* CMS13TeV_pT_Y2_CutEff;
 TH1D* CMS13TeV_pT_Y3_CutEff;
 TH1D* CMS13TeV_pT_Y4_CutEff;
 TH1D* CMS13TeV_pT_Y5_CutEff;

 TH1D* LHCb13TeV_pT_CutEff;

 TH1D* ZPt_FineBin_Final;
 TH1D* ZPt_FineBin_HighPt_Final;

 TH1D* E245_Final;
 TH1D* E246_Final;
 TH1D* E248_Final;
 TH1D* E249_Final;
 TH1D* E250_Final;
 TH1D* E253_Final;
 TH1D* E225_Final;
 TH1D* E227_Final;
 TH1D* E234_Final;
 TH1D* E260_Final;
 TH1D* E261_Final;
 TH1D* E266_Final;
 TH1D* E267_Final;
 TH1D* E281_Final;
 TH1D* E211_Final;
 TH1D* E212_Final;
 TH1D* E218_Final;
 TH1D* E214_Final;
 TH1D* E215_Final;
 TH1D* E217_Final;

 TH1D* E214_BinWidth;

 vector<TString> DataList;

//member function
 vector<TString> sysName;
 HistsResBosCMS(){};
 HistsResBosCMS(TString RootType){this->RootType = RootType;};
 virtual void InitialSysName();
 virtual void bookHists(int TotalThread);
 virtual void outputInformation();
 virtual void ConstructCTEQData();
 virtual void Save();
 virtual void Reset();
 virtual void InputData(vector<TString> DataList){this->DataList = DataList;};
 virtual void ReadData();

// template<class T>

};
#endif
