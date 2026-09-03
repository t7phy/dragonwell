#ifndef __HISTS_PYTHIA_H_
#define __HISTS_PYTHIA_H_
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

class HistsPythia : public makeHists
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

 ThreadHist<TH1D *>* FZmass_Hadron_uu;

 ThreadHist<TH1D *>* BZmass_Hadron_uu;

 ThreadHist<TH1D *>* FZmass_Hadron_dd;

 ThreadHist<TH1D *>* BZmass_Hadron_dd;

 ThreadHist<TH1D *>* FZmass_Hadron_utype;

 ThreadHist<TH1D *>* BZmass_Hadron_utype;

 ThreadHist<TH1D *>* FZmass_Hadron_dtype;

 ThreadHist<TH1D *>* BZmass_Hadron_dtype;

 ThreadHist<TH1D *>* FZmass_LepPtCut;

 ThreadHist<TH1D *>* BZmass_LepPtCut;

 ThreadHist<TH1D *>* FZmass_NoLepPtCut;

 ThreadHist<TH1D *>* BZmass_NoLepPtCut;

 ThreadHist<TH1D *>* FZmass_CC;

 ThreadHist<TH1D *>* BZmass_CC;

 ThreadHist<TH1D *>* FZmass_CF;

 ThreadHist<TH1D *>* BZmass_CF;

 ThreadHist<TH1D *>* ZPt;

 ThreadHist<TH1D *>* ZRapidity;

 ThreadHist<TH1D *>* ZPt_LepPtCut;

 ThreadHist<TH1D *>* ZRapidity_LepPtCut;

 ThreadHist<TH1D *>* ZPt_NoLepPtCut;

 ThreadHist<TH1D *>* ZRapidity_NoLepPtCut;

 ThreadHist<TH1D *>* ZRapidityAbs;

 ThreadHist<TH1D *>* ZPzPtBalance;

 ThreadHist<TH1D *>* ZPzPtBalance_CC;

 ThreadHist<TH1D *>* ZPzPtBalance_CF;

 ThreadHist<TH1D *>* QuarkPzZPzBalance;

 ThreadHist<TH1D *>* QuarkPzZPzBalance_CC;

 ThreadHist<TH1D *>* QuarkPzZPzBalance_CF;

 ThreadHist<TH1D *>* Quark1Pz;

 ThreadHist<TH1D *>* Quark2Pz;

 //ZMass ZY 2D plot
 ThreadHist<TH2D *>* ZMass_ZY;

 ThreadHist<TH2D *>* ZMass_ZY_CC;

 ThreadHist<TH2D *>* ZMass_ZY_CF;

 ThreadHist<TH2D *>* FZMass_ZY;

 ThreadHist<TH2D *>* BZMass_ZY;

 ThreadHist<TH2D *>* FZMass_ZY_CC;

 ThreadHist<TH2D *>* BZMass_ZY_CC;

 ThreadHist<TH2D *>* FZMass_ZY_CF;

 ThreadHist<TH2D *>* BZMass_ZY_CF;

 //ZMass ZPt 2D plot
 ThreadHist<TH2D *>* ZMass_ZPt;

 ThreadHist<TH2D *>* ZMass_ZPt_CC;

 ThreadHist<TH2D *>* ZMass_ZPt_CF;

 ThreadHist<TH2D *>* FZMass_ZPt;

 ThreadHist<TH2D *>* BZMass_ZPt;

 ThreadHist<TH2D *>* FZMass_ZPt_CC;

 ThreadHist<TH2D *>* BZMass_ZPt_CC;

 ThreadHist<TH2D *>* FZMass_ZPt_CF;

 ThreadHist<TH2D *>* BZMass_ZPt_CF;


 //ZMass ZY MultiBin plot
 ThreadHist<MultiBinHist *>* ZMass_ZY_multi;

 ThreadHist<MultiBinHist *>* ZMass_ZY_CC_multi;

 ThreadHist<MultiBinHist *>* ZMass_ZY_CF_multi;

 ThreadHist<MultiBinHist *>* FZMass_ZY_multi;

 ThreadHist<MultiBinHist *>* BZMass_ZY_multi;

 ThreadHist<MultiBinHist *>* FZMass_ZY_CC_multi;

 ThreadHist<MultiBinHist *>* BZMass_ZY_CC_multi;

 ThreadHist<MultiBinHist *>* FZMass_ZY_CF_multi;

 ThreadHist<MultiBinHist *>* BZMass_ZY_CF_multi;


 //ZMass ZY QT 3D plot
 ThreadHist<TH3D *>* ZMass_ZY_QT;

 ThreadHist<TH3D *>* FZMass_ZY_QT;

 ThreadHist<TH3D *>* BZMass_ZY_QT;

 ThreadHist<TH1D *>* CosTheta;

 ThreadHist<TH1D *>* CosTheta_LepPtCut;

 ThreadHist<TH1D *>* CosTheta_NoLepPtCut;

 ThreadHist<TH1D *>* CosThetaQ;

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

 //Lepton Antilepton eta
 ThreadHist<TH1D *>* LepEta;

 ThreadHist<TH1D *>* AntiLepEta;

 ThreadHist<TH1D *>* LepEta_CC;

 ThreadHist<TH1D *>* AntiLepEta_CC;

 ThreadHist<TH1D *>* LepEta_CF;

 ThreadHist<TH1D *>* AntiLepEta_CF;

 //Forward and backward rapidity
 ThreadHist<TH1D *>* FZRapidity;

 ThreadHist<TH1D *>* BZRapidity;

 ThreadHist<TH1D *>* FZRapidity_LepPtCut;

 ThreadHist<TH1D *>* BZRapidity_LepPtCut;

 ThreadHist<TH1D *>* FZRapidity_NoLepPtCut;

 ThreadHist<TH1D *>* BZRapidity_NoLepPtCut;

 ThreadHist<TH1D *>* FZRapidity_CC;

 ThreadHist<TH1D *>* BZRapidity_CC;

 ThreadHist<TH1D *>* FZRapidity_CF;

 ThreadHist<TH1D *>* BZRapidity_CF;

 ThreadHist<TH1D *>* FZPt;

 ThreadHist<TH1D *>* BZPt;

 ThreadHist<TH1D *>* FZPt_LepPtCut;

 ThreadHist<TH1D *>* BZPt_LepPtCut;

 ThreadHist<TH1D *>* FZPt_NoLepPtCut;

 ThreadHist<TH1D *>* BZPt_NoLepPtCut;

 ThreadHist<TH1D *>* AverageZPt_ZY_numer;
 ThreadHist<TH1D *>* AverageZPt_ZY_denom;
 TH1D *AverageZPt_ZY;

 ThreadHist<TH1D *>* AverageZPt_lnQ_numer;
 ThreadHist<TH1D *>* AverageZPt_lnQ_denom;
 TH1D *AverageZPt_lnQ;

 ThreadHist<TH1D *>* AverageZY_ZY_numer;
 ThreadHist<TH1D *>* AverageZY_ZY_denom;
 TH1D *AverageZY_ZY;



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

 //AFB vs ZPt
 ThreadHist<TH1D *>* FZPt_uu;

 ThreadHist<TH1D *>* BZPt_uu;

 ThreadHist<TH1D *>* FZPt_dd;

 ThreadHist<TH1D *>* BZPt_dd;

 //Forward and backward ZMass ZY 2D plot
 ThreadHist<TH2D *>* ZMass_ZY_uu;

 ThreadHist<TH2D *>* ZMass_ZY_dd;

 ThreadHist<TH2D *>* ZMass_ZY_ss;

 ThreadHist<TH2D *>* ZMass_ZY_cc;

 ThreadHist<TH2D *>* ZMass_ZY_bb;

 ThreadHist<TH2D *>* ZMass_ZY_CC_uu;

 ThreadHist<TH2D *>* ZMass_ZY_CC_dd;

 ThreadHist<TH2D *>* ZMass_ZY_CC_ss;

 ThreadHist<TH2D *>* ZMass_ZY_CC_cc;

 ThreadHist<TH2D *>* ZMass_ZY_CC_bb;

 ThreadHist<TH2D *>* ZMass_ZY_CF_uu;

 ThreadHist<TH2D *>* ZMass_ZY_CF_dd;

 ThreadHist<TH2D *>* ZMass_ZY_CF_ss;

 ThreadHist<TH2D *>* ZMass_ZY_CF_cc;

 ThreadHist<TH2D *>* ZMass_ZY_CF_bb;

 ThreadHist<TH2D *>* FZmass_ZY_uu;

 ThreadHist<TH2D *>* BZmass_ZY_uu;

 ThreadHist<TH2D *>* FZmass_ZY_dd;

 ThreadHist<TH2D *>* BZmass_ZY_dd;

 ThreadHist<TH2D *>* FZmass_ZY_gg;

 ThreadHist<TH2D *>* BZmass_ZY_gg;

 ThreadHist<TH2D *>* FZmass_ZY_CC_uu;

 ThreadHist<TH2D *>* BZmass_ZY_CC_uu;

 ThreadHist<TH2D *>* FZmass_ZY_CC_dd;

 ThreadHist<TH2D *>* BZmass_ZY_CC_dd;

 ThreadHist<TH2D *>* FZmass_ZY_CC_gg;

 ThreadHist<TH2D *>* BZmass_ZY_CC_gg;

 ThreadHist<TH2D *>* FZmass_ZY_CF_uu;

 ThreadHist<TH2D *>* BZmass_ZY_CF_uu;

 ThreadHist<TH2D *>* FZmass_ZY_CF_dd;

 ThreadHist<TH2D *>* BZmass_ZY_CF_dd;

 ThreadHist<TH2D *>* FZmass_ZY_CF_gg;

 ThreadHist<TH2D *>* BZmass_ZY_CF_gg;

 //Forward and backward ZMass ZPt 2D plot
 ThreadHist<TH2D *>* ZMass_ZPt_uu;

 ThreadHist<TH2D *>* ZMass_ZPt_dd;

 ThreadHist<TH2D *>* ZMass_ZPt_ss;

 ThreadHist<TH2D *>* ZMass_ZPt_cc;

 ThreadHist<TH2D *>* ZMass_ZPt_bb;

 ThreadHist<TH2D *>* ZMass_ZPt_CC_uu;

 ThreadHist<TH2D *>* ZMass_ZPt_CC_dd;

 ThreadHist<TH2D *>* ZMass_ZPt_CC_ss;

 ThreadHist<TH2D *>* ZMass_ZPt_CC_cc;

 ThreadHist<TH2D *>* ZMass_ZPt_CC_bb;

 ThreadHist<TH2D *>* ZMass_ZPt_CF_uu;

 ThreadHist<TH2D *>* ZMass_ZPt_CF_dd;

 ThreadHist<TH2D *>* ZMass_ZPt_CF_ss;

 ThreadHist<TH2D *>* ZMass_ZPt_CF_cc;

 ThreadHist<TH2D *>* ZMass_ZPt_CF_bb;

 ThreadHist<TH2D *>* FZmass_ZPt_uu;

 ThreadHist<TH2D *>* BZmass_ZPt_uu;

 ThreadHist<TH2D *>* FZmass_ZPt_dd;

 ThreadHist<TH2D *>* BZmass_ZPt_dd;

 ThreadHist<TH2D *>* FZmass_ZPt_gg;

 ThreadHist<TH2D *>* BZmass_ZPt_gg;

 ThreadHist<TH2D *>* FZmass_ZPt_CC_uu;

 ThreadHist<TH2D *>* BZmass_ZPt_CC_uu;

 ThreadHist<TH2D *>* FZmass_ZPt_CC_dd;

 ThreadHist<TH2D *>* BZmass_ZPt_CC_dd;

 ThreadHist<TH2D *>* FZmass_ZPt_CC_gg;

 ThreadHist<TH2D *>* BZmass_ZPt_CC_gg;

 ThreadHist<TH2D *>* FZmass_ZPt_CF_uu;

 ThreadHist<TH2D *>* BZmass_ZPt_CF_uu;

 ThreadHist<TH2D *>* FZmass_ZPt_CF_dd;

 ThreadHist<TH2D *>* BZmass_ZPt_CF_dd;

 ThreadHist<TH2D *>* FZmass_ZPt_CF_gg;

 ThreadHist<TH2D *>* BZmass_ZPt_CF_gg;

 //Forward and backward ZMass ZY MultiBin plot
 ThreadHist<MultiBinHist *>* FZmass_ZY_uu_multi;

 ThreadHist<MultiBinHist *>* BZmass_ZY_uu_multi;

 ThreadHist<MultiBinHist *>* FZmass_ZY_dd_multi;

 ThreadHist<MultiBinHist *>* BZmass_ZY_dd_multi;

 ThreadHist<MultiBinHist *>* FZmass_ZY_gg_multi;

 ThreadHist<MultiBinHist *>* BZmass_ZY_gg_multi;

 ThreadHist<MultiBinHist *>* FZmass_ZY_CC_uu_multi;

 ThreadHist<MultiBinHist *>* BZmass_ZY_CC_uu_multi;

 ThreadHist<MultiBinHist *>* FZmass_ZY_CC_dd_multi;

 ThreadHist<MultiBinHist *>* BZmass_ZY_CC_dd_multi;

 ThreadHist<MultiBinHist *>* FZmass_ZY_CC_gg_multi;

 ThreadHist<MultiBinHist *>* BZmass_ZY_CC_gg_multi;

 ThreadHist<MultiBinHist *>* FZmass_ZY_CF_uu_multi;

 ThreadHist<MultiBinHist *>* BZmass_ZY_CF_uu_multi;

 ThreadHist<MultiBinHist *>* FZmass_ZY_CF_dd_multi;

 ThreadHist<MultiBinHist *>* BZmass_ZY_CF_dd_multi;

 ThreadHist<MultiBinHist *>* FZmass_ZY_CF_gg_multi;

 ThreadHist<MultiBinHist *>* BZmass_ZY_CF_gg_multi;

 //Forward and backward ZY
 ThreadHist<TH1D *>* FZRapidity_uu;

 ThreadHist<TH1D *>* BZRapidity_uu;

 ThreadHist<TH1D *>* FZRapidity_CC_uu;

 ThreadHist<TH1D *>* BZRapidity_CC_uu;

 ThreadHist<TH1D *>* FZRapidity_CF_uu;

 ThreadHist<TH1D *>* BZRapidity_CF_uu;

 ThreadHist<TH1D *>* FZRapidity_dd;

 ThreadHist<TH1D *>* BZRapidity_dd;

 ThreadHist<TH1D *>* FZRapidity_CC_dd;

 ThreadHist<TH1D *>* BZRapidity_CC_dd;

 ThreadHist<TH1D *>* FZRapidity_CF_dd;

 ThreadHist<TH1D *>* BZRapidity_CF_dd;

 ThreadHist<TH1D *>* FZRapidity_gg;

 ThreadHist<TH1D *>* BZRapidity_gg;

 ThreadHist<TH1D *>* FZRapidity_CC_gg;

 ThreadHist<TH1D *>* BZRapidity_CC_gg;

 ThreadHist<TH1D *>* FZRapidity_CF_gg;

 ThreadHist<TH1D *>* BZRapidity_CF_gg;

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

 //Forward and backward dilution
 ThreadHist<TH1D *>* FZmass_CC_uu_total;
 ThreadHist<TH1D *>* FZmass_CC_uu_wrong;
 TH1D *Dilution_FZmass_CC_uu;

 ThreadHist<TH1D *>* BZmass_CC_uu_total;
 ThreadHist<TH1D *>* BZmass_CC_uu_wrong;
 TH1D *Dilution_BZmass_CC_uu;

 ThreadHist<TH1D *>* FZmass_CC_dd_total;
 ThreadHist<TH1D *>* FZmass_CC_dd_wrong;
 TH1D *Dilution_FZmass_CC_dd;

 ThreadHist<TH1D *>* BZmass_CC_dd_total;
 ThreadHist<TH1D *>* BZmass_CC_dd_wrong;
 TH1D *Dilution_BZmass_CC_dd;

 ThreadHist<TH1D *>* FZmass_CF_uu_total;
 ThreadHist<TH1D *>* FZmass_CF_uu_wrong;
 TH1D *Dilution_FZmass_CF_uu;

 ThreadHist<TH1D *>* BZmass_CF_uu_total;
 ThreadHist<TH1D *>* BZmass_CF_uu_wrong;
 TH1D *Dilution_BZmass_CF_uu;

 ThreadHist<TH1D *>* FZmass_CF_dd_total;
 ThreadHist<TH1D *>* FZmass_CF_dd_wrong;
 TH1D *Dilution_FZmass_CF_dd;

 ThreadHist<TH1D *>* BZmass_CF_dd_total;
 ThreadHist<TH1D *>* BZmass_CF_dd_wrong;
 TH1D *Dilution_BZmass_CF_dd;

 ThreadHist<TH1D *>* FZmass_Full_uu_total;
 ThreadHist<TH1D *>* FZmass_Full_uu_wrong;
 TH1D *Dilution_FZmass_Full_uu;

 ThreadHist<TH1D *>* BZmass_Full_uu_total;
 ThreadHist<TH1D *>* BZmass_Full_uu_wrong;
 TH1D *Dilution_BZmass_Full_uu;

 ThreadHist<TH1D *>* FZmass_Full_dd_total;
 ThreadHist<TH1D *>* FZmass_Full_dd_wrong;
 TH1D *Dilution_FZmass_Full_dd;

 ThreadHist<TH1D *>* BZmass_Full_dd_total;
 ThreadHist<TH1D *>* BZmass_Full_dd_wrong;
 TH1D *Dilution_BZmass_Full_dd;


 //AFB Dilution Mass ZY 2D
 ThreadHist<TH2D *>* ZMass_ZY_total;
 ThreadHist<TH2D *>* ZMass_ZY_wrong;
 TH2D *Dilution_ZMass_ZY;

 ThreadHist<TH2D *>* ZMass_ZY_CC_total;
 ThreadHist<TH2D *>* ZMass_ZY_CC_wrong;
 TH2D *Dilution_ZMass_ZY_CC;

 ThreadHist<TH2D *>* ZMass_ZY_CF_total;
 ThreadHist<TH2D *>* ZMass_ZY_CF_wrong;
 TH2D *Dilution_ZMass_ZY_CF;

 ThreadHist<TH2D *>* ZMass_ZY_uu_total;
 ThreadHist<TH2D *>* ZMass_ZY_uu_wrong;
 TH2D *Dilution_ZMass_ZY_uu;

 ThreadHist<TH2D *>* ZMass_ZY_CC_uu_total;
 ThreadHist<TH2D *>* ZMass_ZY_CC_uu_wrong;
 TH2D *Dilution_ZMass_ZY_CC_uu;

 ThreadHist<TH2D *>* ZMass_ZY_CF_uu_total;
 ThreadHist<TH2D *>* ZMass_ZY_CF_uu_wrong;
 TH2D *Dilution_ZMass_ZY_CF_uu;

 ThreadHist<TH2D *>* ZMass_ZY_dd_total;
 ThreadHist<TH2D *>* ZMass_ZY_dd_wrong;
 TH2D *Dilution_ZMass_ZY_dd;

 ThreadHist<TH2D *>* ZMass_ZY_CC_dd_total;
 ThreadHist<TH2D *>* ZMass_ZY_CC_dd_wrong;
 TH2D *Dilution_ZMass_ZY_CC_dd;

 ThreadHist<TH2D *>* ZMass_ZY_CF_dd_total;
 ThreadHist<TH2D *>* ZMass_ZY_CF_dd_wrong;
 TH2D *Dilution_ZMass_ZY_CF_dd;

 ThreadHist<TH2D *>* FZMass_ZY_total;
 ThreadHist<TH2D *>* FZMass_ZY_wrong;
 TH2D *Dilution_FZMass_ZY;

 ThreadHist<TH2D *>* BZMass_ZY_total;
 ThreadHist<TH2D *>* BZMass_ZY_wrong;
 TH2D *Dilution_BZMass_ZY;

 //AFB Dilution Mass ZPt 2D
 ThreadHist<TH2D *>* ZMass_ZPt_total;
 ThreadHist<TH2D *>* ZMass_ZPt_wrong;
 TH2D *Dilution_ZMass_ZPt;

 ThreadHist<TH2D *>* ZMass_ZPt_CC_total;
 ThreadHist<TH2D *>* ZMass_ZPt_CC_wrong;
 TH2D *Dilution_ZMass_ZPt_CC;

 ThreadHist<TH2D *>* ZMass_ZPt_CF_total;
 ThreadHist<TH2D *>* ZMass_ZPt_CF_wrong;
 TH2D *Dilution_ZMass_ZPt_CF;

 ThreadHist<TH2D *>* ZMass_ZPt_uu_total;
 ThreadHist<TH2D *>* ZMass_ZPt_uu_wrong;
 TH2D *Dilution_ZMass_ZPt_uu;

 ThreadHist<TH2D *>* ZMass_ZPt_CC_uu_total;
 ThreadHist<TH2D *>* ZMass_ZPt_CC_uu_wrong;
 TH2D *Dilution_ZMass_ZPt_CC_uu;

 ThreadHist<TH2D *>* ZMass_ZPt_CF_uu_total;
 ThreadHist<TH2D *>* ZMass_ZPt_CF_uu_wrong;
 TH2D *Dilution_ZMass_ZPt_CF_uu;

 ThreadHist<TH2D *>* ZMass_ZPt_dd_total;
 ThreadHist<TH2D *>* ZMass_ZPt_dd_wrong;
 TH2D *Dilution_ZMass_ZPt_dd;

 ThreadHist<TH2D *>* ZMass_ZPt_CC_dd_total;
 ThreadHist<TH2D *>* ZMass_ZPt_CC_dd_wrong;
 TH2D *Dilution_ZMass_ZPt_CC_dd;

 ThreadHist<TH2D *>* ZMass_ZPt_CF_dd_total;
 ThreadHist<TH2D *>* ZMass_ZPt_CF_dd_wrong;
 TH2D *Dilution_ZMass_ZPt_CF_dd;

 //AFB Dilution MultiBin
 ThreadHist<MultiBinHist *>* ZMass_ZY_total_multi;
 ThreadHist<MultiBinHist *>* ZMass_ZY_wrong_multi;
 MultiBinHist *Dilution_ZMass_ZY_multi;

 ThreadHist<MultiBinHist *>* ZMass_ZY_CC_total_multi;
 ThreadHist<MultiBinHist *>* ZMass_ZY_CC_wrong_multi;
 MultiBinHist *Dilution_ZMass_ZY_CC_multi;

 ThreadHist<MultiBinHist *>* ZMass_ZY_CF_total_multi;
 ThreadHist<MultiBinHist *>* ZMass_ZY_CF_wrong_multi;
 MultiBinHist *Dilution_ZMass_ZY_CF_multi;

 ThreadHist<MultiBinHist *>* ZMass_ZY_uu_total_multi;
 ThreadHist<MultiBinHist *>* ZMass_ZY_uu_wrong_multi;
 MultiBinHist *Dilution_ZMass_ZY_uu_multi;

 ThreadHist<MultiBinHist *>* ZMass_ZY_CC_uu_total_multi;
 ThreadHist<MultiBinHist *>* ZMass_ZY_CC_uu_wrong_multi;
 MultiBinHist *Dilution_ZMass_ZY_CC_uu_multi;

 ThreadHist<MultiBinHist *>* ZMass_ZY_CF_uu_total_multi;
 ThreadHist<MultiBinHist *>* ZMass_ZY_CF_uu_wrong_multi;
 MultiBinHist *Dilution_ZMass_ZY_CF_uu_multi;

 ThreadHist<MultiBinHist *>* ZMass_ZY_dd_total_multi;
 ThreadHist<MultiBinHist *>* ZMass_ZY_dd_wrong_multi;
 MultiBinHist *Dilution_ZMass_ZY_dd_multi;

 ThreadHist<MultiBinHist *>* ZMass_ZY_CC_dd_total_multi;
 ThreadHist<MultiBinHist *>* ZMass_ZY_CC_dd_wrong_multi;
 MultiBinHist *Dilution_ZMass_ZY_CC_dd_multi;

 ThreadHist<MultiBinHist *>* ZMass_ZY_CF_dd_total_multi;
 ThreadHist<MultiBinHist *>* ZMass_ZY_CF_dd_wrong_multi;
 MultiBinHist *Dilution_ZMass_ZY_CF_dd_multi;


 //AFB Dilution 3D
 ThreadHist<TH3D *>* ZMass_ZY_QT_total;
 ThreadHist<TH3D *>* ZMass_ZY_QT_wrong;
 TH3D *Dilution_ZMass_ZY_QT;

 ThreadHist<TH3D *>* ZMass_ZY_QT_CC_total;
 ThreadHist<TH3D *>* ZMass_ZY_QT_CC_wrong;
 TH3D *Dilution_ZMass_ZY_QT_CC;

 ThreadHist<TH3D *>* ZMass_ZY_QT_CF_total;
 ThreadHist<TH3D *>* ZMass_ZY_QT_CF_wrong;
 TH3D *Dilution_ZMass_ZY_QT_CF;

 //Dilution vs ZPt ZY CosThetaQ
 ThreadHist<TH1D *>* ZPt_total;
 ThreadHist<TH1D *>* ZPt_wrong;
 TH1D *Dilution_ZPt;

 ThreadHist<TH1D *>* ZPt_LepPtCut_total;
 ThreadHist<TH1D *>* ZPt_LepPtCut_wrong;
 TH1D *Dilution_ZPt_LepPtCut;

 ThreadHist<TH1D *>* ZPt_NoLepPtCut_total;
 ThreadHist<TH1D *>* ZPt_NoLepPtCut_wrong;
 TH1D *Dilution_ZPt_NoLepPtCut;

 ThreadHist<TH1D *>* ZRapidity_total;
 ThreadHist<TH1D *>* ZRapidity_wrong;
 TH1D *Dilution_ZRapidity;

 ThreadHist<TH1D *>* ZRapidity_LepPtCut_total;
 ThreadHist<TH1D *>* ZRapidity_LepPtCut_wrong;
 TH1D *Dilution_ZRapidity_LepPtCut;

 ThreadHist<TH1D *>* ZRapidity_NoLepPtCut_total;
 ThreadHist<TH1D *>* ZRapidity_NoLepPtCut_wrong;
 TH1D *Dilution_ZRapidity_NoLepPtCut;

 ThreadHist<TH1D *>* ZRapidity_uu_total;
 ThreadHist<TH1D *>* ZRapidity_uu_wrong;
 TH1D *Dilution_ZRapidity_uu;

 ThreadHist<TH1D *>* ZRapidity_dd_total;
 ThreadHist<TH1D *>* ZRapidity_dd_wrong;
 TH1D *Dilution_ZRapidity_dd;

 ThreadHist<TH1D *>* ZRapidityAbs_total;
 ThreadHist<TH1D *>* ZRapidityAbs_wrong;
 TH1D *Dilution_ZRapidityAbs;

 ThreadHist<TH1D *>* CosThetaQ_total;
 ThreadHist<TH1D *>* CosThetaQ_wrong;
 TH1D *Dilution_CosThetaQ;

 ThreadHist<AngularFunction *>* A0_ZPt;

 ThreadHist<AngularFunction *>* A1_ZPt;

 ThreadHist<AngularFunction *>* A2_ZPt;

 ThreadHist<AngularFunction *>* A3_ZPt;

 ThreadHist<AngularFunction *>* A4_ZPt;

 ThreadHist<AngularFunction *>* L0_ZPt;

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
 TH1D *AFB_LepPtCut;
 TH1D *AFB_NoLepPtCut;

 TH2D *AFB_Mass_ZY_CC;
 TH2D *AFB_Mass_ZY_CF;
 TH2D *AFB_Mass_ZY_Full;

 TH2D *AFB_Mass_ZPt_CC;
 TH2D *AFB_Mass_ZPt_CF;
 TH2D *AFB_Mass_ZPt_Full;

 MultiBinHist *AFB_Mass_ZY_CC_multi;
 MultiBinHist *AFB_Mass_ZY_CF_multi;
 MultiBinHist *AFB_Mass_ZY_Full_multi;

 TH1D *AFBSlope_ZY_CC;
 TH1D *AFBSlope_ZY_CF;
 TH1D *AFBSlope_ZY_Full;
 TH1D *AFBOffset_ZY_CC;
 TH1D *AFBOffset_ZY_CF;
 TH1D *AFBOffset_ZY_Full;

 TH1D *AFBSlope_ZPt_CC;
 TH1D *AFBSlope_ZPt_CF;
 TH1D *AFBSlope_ZPt_Full;
 TH1D *AFBOffset_ZPt_CC;
 TH1D *AFBOffset_ZPt_CF;
 TH1D *AFBOffset_ZPt_Full;

 TH1D *AFBSlope_CC;
 TH1D *AFBSlope_CF;
 TH1D *AFBSlope_Full;

 TH1D *AFBSlope_82_98_CC;
 TH1D *AFBSlope_82_98_CF;
 TH1D *AFBSlope_82_98_Full;

 TH1D *AFBSlope_84_96_CC;
 TH1D *AFBSlope_84_96_CF;
 TH1D *AFBSlope_84_96_Full;

 TH1D *AFBOffset_CC;
 TH1D *AFBOffset_CF;
 TH1D *AFBOffset_Full;

 TH1D *AFBOffset_82_98_CC;
 TH1D *AFBOffset_82_98_CF;
 TH1D *AFBOffset_82_98_Full;

 TH1D *AFBOffset_84_96_CC;
 TH1D *AFBOffset_84_96_CF;
 TH1D *AFBOffset_84_96_Full;

 TH2D *AFBQuark_Mass_ZY_CC;
 TH2D *AFBQuark_Mass_ZY_CF;
 TH2D *AFBQuark_Mass_ZY_Full;

 TH2D *AFBQuark_Mass_ZPt_CC;
 TH2D *AFBQuark_Mass_ZPt_CF;
 TH2D *AFBQuark_Mass_ZPt_Full;

 TH1D *AFBQuarkSlope_ZY_CC;
 TH1D *AFBQuarkSlope_ZY_CF;
 TH1D *AFBQuarkSlope_ZY_Full;
 TH1D *AFBQuarkOffset_ZY_CC;
 TH1D *AFBQuarkOffset_ZY_CF;
 TH1D *AFBQuarkOffset_ZY_Full;

 TH1D *AFBQuarkSlope_ZPt_CC;
 TH1D *AFBQuarkSlope_ZPt_CF;
 TH1D *AFBQuarkSlope_ZPt_Full;
 TH1D *AFBQuarkOffset_ZPt_CC;
 TH1D *AFBQuarkOffset_ZPt_CF;
 TH1D *AFBQuarkOffset_ZPt_Full;

 TH1D *AFBQuarkSlope_CC;
 TH1D *AFBQuarkSlope_CF;
 TH1D *AFBQuarkSlope_Full;

 TH1D *AFBQuarkSlope_82_98_CC;
 TH1D *AFBQuarkSlope_82_98_CF;
 TH1D *AFBQuarkSlope_82_98_Full;

 TH1D *AFBQuarkSlope_84_96_CC;
 TH1D *AFBQuarkSlope_84_96_CF;
 TH1D *AFBQuarkSlope_84_96_Full;

 TH1D *AFBQuarkOffset_CC;
 TH1D *AFBQuarkOffset_CF;
 TH1D *AFBQuarkOffset_Full;

 TH1D *AFBQuarkOffset_82_98_CC;
 TH1D *AFBQuarkOffset_82_98_CF;
 TH1D *AFBQuarkOffset_82_98_Full;

 TH1D *AFBQuarkOffset_84_96_CC;
 TH1D *AFBQuarkOffset_84_96_CF;
 TH1D *AFBQuarkOffset_84_96_Full;

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

 TH2D *AFBS0Fraction_ZY_CC;
 TH2D *AFBS0Fraction_ZY_CF;
 TH2D *AFBS0Fraction_ZY_Full;

 TH2D *AFBS0Fraction_ZPt_CC;
 TH2D *AFBS0Fraction_ZPt_CF;
 TH2D *AFBS0Fraction_ZPt_Full;

 TH1D *AFBDiff_CC;
 TH1D *AFBDiff_CF;
 TH1D *AFBDiff_Full;

 TH1D *AFBDiff_CC_ZPole;
 TH1D *AFBDiff_CF_ZPole;
 TH1D *AFBDiff_Full_ZPole;

 TH1D *AFBDiff_CC_Side;
 TH1D *AFBDiff_CF_Side;
 TH1D *AFBDiff_Full_Side;

 TH2D *AFBDiff_Mass_ZY_CC;
 TH2D *AFBDiff_Mass_ZY_CF;
 TH2D *AFBDiff_Mass_ZY_Full;

 MultiBinHist *AFBDiff_Mass_ZY_CC_multi;
 MultiBinHist *AFBDiff_Mass_ZY_CF_multi;
 MultiBinHist *AFBDiff_Mass_ZY_Full_multi;

 TH1D *AFBGradient_CC;
 TH1D *AFBGradient_CF;
 TH1D *AFBGradient_Full;

 TH1D *AFBQuarkGradient_CC;
 TH1D *AFBQuarkGradient_CF;
 TH1D *AFBQuarkGradient_Full;

 TH1D *DilutionGradient_CC;
 TH1D *DilutionGradient_CF;
 TH1D *DilutionGradient_Full;

 TH1D *DilutionAFB_CC;
 TH1D *DilutionAFB_CF;
 TH1D *DilutionAFB_Full;

 TH1D *AveAFB_CC;
 TH1D *AveAFB_CF;
 TH1D *AveAFB_Full;

 TH1D *QuarkAveAFB_CC;
 TH1D *QuarkAveAFB_CF;
 TH1D *QuarkAveAFB_Full;

 TH1D *AFB_CC_uu;
 TH1D *AFB_CF_uu;
 TH1D *AFB_Full_uu;

 TH1D *AFB_CC_dd;
 TH1D *AFB_CF_dd;
 TH1D *AFB_Full_dd;

 TH1D *AFB_CC_qq;
 TH1D *AFB_CF_qq;
 TH1D *AFB_Full_qq;

 TH1D *AFB_Full_uudd;
 TH1D *AFB_Full_gluon;

 TH1D *AFB_ZPt_uu;
 TH1D *AFB_ZPt_dd;

 TH2D *AFB_Mass_ZPt_Full_uu;
 TH2D *AFB_Mass_ZPt_Full_dd;

 TH1D *AFB_Hadron_Full_uu;
 TH1D *AFB_Hadron_Full_dd;
 TH1D *AFB_Hadron_Full_uudd;

 TH1D *AFB_Hadron_Full_utype;
 TH1D *AFB_Hadron_Full_dtype;

 TH1D *AveAFB_Full_uu;
 TH1D *AveAFB_Full_dd;
 TH1D *AveAFB_Full_uudd;

 TH1D *AveAFB_Full_utype;
 TH1D *AveAFB_Full_dtype;

 TH1D *QuarkAveAFB_Full_uu;
 TH1D *QuarkAveAFB_Full_dd;
 TH1D *QuarkAveAFB_Full_uudd;
 TH1D *QuarkAveAFB_Full_gluon;

 TH1D *AFB_qq_ApplyDilution;
 TH1D *AFB_qq_ApplyDilution_CC;
 TH1D *AFB_qq_ApplyDilution_CF;

 TH1D *FZRapidity_CC_qq;
 TH1D *BZRapidity_CC_qq;

 TH1D *FZRapidity_CF_qq;
 TH1D *BZRapidity_CF_qq;

 TH1D *FZRapidity_qq;
 TH1D *BZRapidity_qq;

 TH1D *LepAsym;
 TH1D *LepAsym_CC;
 TH1D *LepAsym_CF;

 TH1D *AFB_ZY;
 TH1D *AFB_ZY_LepPtCut;
 TH1D *AFB_ZY_NoLepPtCut;
 TH1D *AFB_ZY_CC;
 TH1D *AFB_ZY_CF;

 TH1D *AFB_ZPt;
 TH1D *AFB_ZPt_LepPtCut;
 TH1D *AFB_ZPt_NoLepPtCut;

 TH1D *AFB_ZY_qq;
 TH1D *AFB_ZY_CC_qq;
 TH1D *AFB_ZY_CF_qq;

 TH1D *LepWidthDiff;
 TH1D *LepWidthDiff_CC;
 TH1D *LepWidthDiff_CF;

 TH1D *ReweightFactor_FZRapidity;
 TH1D *ReweightFactor_BZRapidity;
 TH1D *ReweightFactor_FZRapidity_CC;
 TH1D *ReweightFactor_BZRapidity_CC;
 TH1D *ReweightFactor_FZRapidity_CF;
 TH1D *ReweightFactor_BZRapidity_CF;

 TH1D *Dilution_Linear;
 double Dilution_k;
 double Dilution_b;

//member function
 vector<TString> sysName;
 HistsPythia();
 virtual void InitialSysName();
 virtual void bookHists(int TotalThread);
 virtual void GetReweightFactor();
 virtual void RetrieveWeight(double ZY, double &FZY, double &BZY, double &FZY_CC, double &BZY_CC, double &FZY_CF, double &BZY_CF);
 virtual void LinkClass(HistsPythia *hist);
 virtual void InputParameter(double k, double b);
 virtual void GetPartOfResults();
 virtual void outputInformation();

// template<class T>

};

#ifdef HistsPythia_cxx
HistsPythia* m_HistsPythia;
double MinChi2 = 1000000.0;
#endif
void DilutionFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);

#endif
