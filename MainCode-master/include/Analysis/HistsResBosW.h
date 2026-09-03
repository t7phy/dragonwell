#ifndef __HISTS_RESBOSW_H_
#define __HISTS_RESBOSW_H_
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

class HistsResBosW : public makeHists
{
 public:

 ThreadHist<TH1D *>* LeptonEtaAbs;
 ThreadHist<TH1D *>* AntiLeptonEtaAbs;

 ThreadHist<TH1D *>* LeptonEtaAbs_pt35;
 ThreadHist<TH1D *>* AntiLeptonEtaAbs_pt35;

 ThreadHist<TH1D *>* LeptonEtaAbs_pt25_35;
 ThreadHist<TH1D *>* AntiLeptonEtaAbs_pt25_35;

 ThreadHist<TH2D *>* LeptonEtaAbs2D;
 ThreadHist<TH2D *>* AntiLeptonEtaAbs2D;

 ThreadHist<TH2D *>* LeptonEtaAbs_MT2D;
 ThreadHist<TH2D *>* AntiLeptonEtaAbs_MT2D;

 ThreadHist<TH2D *>* LeptonEtaAbs_ut2D;
 ThreadHist<TH2D *>* AntiLeptonEtaAbs_ut2D;

 ThreadHist<TH3D *>* LeptonEtaAbs3D_cut30;
 ThreadHist<TH3D *>* AntiLeptonEtaAbs3D_cut30;

 ThreadHist<TH3D *>* LeptonEtaAbs3D_cut35;
 ThreadHist<TH3D *>* AntiLeptonEtaAbs3D_cut35;

 ThreadHist<TH3D *>* LeptonEtaAbs3D_cut40;
 ThreadHist<TH3D *>* AntiLeptonEtaAbs3D_cut40;

 ThreadHist<TH1D *>* LeptonEtaAbs_LHCb;
 ThreadHist<TH1D *>* AntiLeptonEtaAbs_LHCb;

 ThreadHist<TH1D *>* WPlusRapidity;
 ThreadHist<TH1D *>* WMinusRapidity;

 ThreadHist<TH1D *>* WPlusPt;
 ThreadHist<TH1D *>* WMinusPt;

 ThreadHist<TH1D *>* WPlusE;
 ThreadHist<TH1D *>* WMinusE;

 ThreadHist<TH2D *>* WPlusYPt;
 ThreadHist<TH2D *>* WMinusYPt;

 ThreadHist<TH2D *>* WPlusYE;
 ThreadHist<TH2D *>* WMinusYE;

 ThreadHist<TH1D *>* LeptonEta;

 ThreadHist<TH1D *>* AntiLeptonEta;

 ThreadHist<TH2D *>* LeptonEtaMET;
 ThreadHist<TH2D *>* AntiLeptonEtaMET;

 ThreadHist<TH1D *>* WPlusMET;

 ThreadHist<TH1D *>* WMinusMET;

 ThreadHist<TH1D *>* WPlusMET_LowEta;

 ThreadHist<TH1D *>* WMinusMET_LowEta;

 ThreadHist<TH1D *>* WPlusMET_HighEta;

 ThreadHist<TH1D *>* WMinusMET_HighEta;

 ThreadHist<TH1D *>* LeptonPt;

 ThreadHist<TH1D *>* AntiLeptonPt;

 ThreadHist<TH1D *>* LeptonPt_LowEta;

 ThreadHist<TH1D *>* AntiLeptonPt_LowEta;

 ThreadHist<TH1D *>* LeptonPt_HighEta;

 ThreadHist<TH1D *>* AntiLeptonPt_HighEta;

 ThreadHist<TH2D *>* LeptonEtaPt;
 ThreadHist<TH2D *>* AntiLeptonEtaPt;

 ThreadHist<TH1D *>* E605_Q1;
 ThreadHist<TH1D *>* E605_Q2;
 ThreadHist<TH1D *>* E605_Q3;
 ThreadHist<TH1D *>* E605_Q4;
 ThreadHist<TH1D *>* E605_Q5;
 ThreadHist<TH1D *>* E605_Q6;
 ThreadHist<TH1D *>* E605_Q7;
 ThreadHist<TH1D *>* E605_Q8;
 ThreadHist<TH1D *>* E605_Q9;
 ThreadHist<TH1D *>* E605_Q10;
 ThreadHist<TH1D *>* E605_Q11;
 ThreadHist<TH1D *>* E605_Q12;
 ThreadHist<TH1D *>* E605_Q13;
 ThreadHist<TH1D *>* E605_Q14;
 ThreadHist<TH1D *>* E605_Q15;
 ThreadHist<TH1D *>* E605_Q16;
 ThreadHist<TH1D *>* E605_Q17;
 ThreadHist<TH1D *>* E605_Q18;

 TH1D* E605_Q1_Final;
 TH1D* E605_Q2_Final;
 TH1D* E605_Q3_Final;
 TH1D* E605_Q4_Final;
 TH1D* E605_Q5_Final;
 TH1D* E605_Q6_Final;
 TH1D* E605_Q7_Final;
 TH1D* E605_Q8_Final;
 TH1D* E605_Q9_Final;
 TH1D* E605_Q10_Final;
 TH1D* E605_Q11_Final;
 TH1D* E605_Q12_Final;
 TH1D* E605_Q13_Final;
 TH1D* E605_Q14_Final;
 TH1D* E605_Q15_Final;
 TH1D* E605_Q16_Final;
 TH1D* E605_Q17_Final;
 TH1D* E605_Q18_Final;


 virtual void bookHists(int TotalThread);
 virtual void outputInformation();

// template<class T>

};
#endif
