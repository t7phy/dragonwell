#ifndef __HistsMadGraph_H_
#define __HistsMadGraph_H_
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

class HistsMadGraph : public makeHists
{
 public:

 //////////////////////////
 //  Z Event Histograms  //
 //////////////////////////

 ThreadHist<TH3D *>* Xsec_3D_CC;
 ThreadHist<TH3D *>* Xsec_3D_CF;
 ThreadHist<TH2D *>* Xsec_2D_CC;
 ThreadHist<TH2D *>* Xsec_2D_CF;
 ThreadHist<TH1D *>* Xsec_1D_CC;
 ThreadHist<TH1D *>* Xsec_1D_CF;

 ThreadHist<TH1D *>* ZMass_HighMass;
 ThreadHist<TH1D *>* ZMass_HighMass_PerTeV;

 ThreadHist<TH1D *>* ZMass_FullMass;

 ThreadHist<TH2D *>* ZMass_CosTheta_uu;
 ThreadHist<TH2D *>* ZMass_CosTheta_dd;
 ThreadHist<TH2D *>* ZMass_CosTheta;

 //////////////////////////
 //  W Event Histograms  //
 //////////////////////////

 ThreadHist<TH1D *>* PositiveLeptonEta;
 ThreadHist<TH1D *>* NegativeLeptonEta;

 ThreadHist<TH2D *>* WPlusMTEta;
 ThreadHist<TH2D *>* WMinusMTEta;
 ThreadHist<TH2D *>* WPlusMTEta_Above100;
 ThreadHist<TH2D *>* WMinusMTEta_Above100;

 ThreadHist<TH1D *>* WPlusMT;
 ThreadHist<TH1D *>* WMinusMT;
 ThreadHist<TH1D *>* WPlusMT_Above100;
 ThreadHist<TH1D *>* WMinusMT_Above100;

 ThreadHist<TH1D *>* WPlusHighMassMT;
 ThreadHist<TH1D *>* WMinusHighMassMT;
 ThreadHist<TH1D *>* WPlusHighMassMT_PerTeV;
 ThreadHist<TH1D *>* WMinusHighMassMT_PerTeV;

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



 ThreadHist<TH1D *>* ZMass;
 ThreadHist<TH1D *>* ZRapidity;
 ThreadHist<TH1D *>* ZPt;
 ThreadHist<TH1D *>* LeptonPt;
 ThreadHist<TH1D *>* LeptonEta;
 ThreadHist<TH1D *>* FZMass;
 ThreadHist<TH1D *>* BZMass;
 ThreadHist<TH1D *>* ZHighMass;
 ThreadHist<TH1D *>* FZMass_HighMass;
 ThreadHist<TH1D *>* BZMass_HighMass;
 ThreadHist<TH1D *>* CrossSection;
 ThreadHist<TH1D *>* CrossSectionF;
 ThreadHist<TH1D *>* CrossSectionB;
 ThreadHist<TH1D *>* FullCrossSection;

 ThreadHist<TH1D *>* E245_LHCb7TeV_Z;
 ThreadHist<TH1D *>* E245_LHCb7TeV_WPlus;
 ThreadHist<TH1D *>* E245_LHCb7TeV_WMinus;

 ThreadHist<TH1D *>* E246_LHCb8TeV_Z;

 ThreadHist<TH1D *>* E248_ATLAS7TeV_Z;
 ThreadHist<TH1D *>* E248_ATLAS7TeV_WPlus;
 ThreadHist<TH1D *>* E248_ATLAS7TeV_WMinus;

 ThreadHist<TH1D *>* E268_ATLAS7TeV_Z;
 ThreadHist<TH1D *>* E268_ATLAS7TeV_WPlus;
 ThreadHist<TH1D *>* E268_ATLAS7TeV_WMinus;

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

 TH1D* E245_Final;
 TH1D* E246_Final;
 TH1D* E248_Final;
 TH1D* E268_Final;
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

 TH1D* AFB_ZMass;
 TH1D* AFB_ZHighMass;

 TH1D* FZMass_Pseudodata;
 TH1D* BZMass_Pseudodata;

 TH1D* CrossSection_Pseudodata;
 TH1D* CrossSectionF_Pseudodata;
 TH1D* CrossSectionB_Pseudodata;
 TH1D* CrossSectionAFB;
 TH1D* FullCrossSection_Pseudodata;

//member function
 vector<TString> sysName;
 virtual void InitialSysName();
 virtual void bookHists(int TotalThread);
 virtual void outputInformation();
 virtual void ConstructCTEQData();

// template<class T>

};
#endif
