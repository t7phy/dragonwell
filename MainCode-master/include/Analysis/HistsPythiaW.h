#ifndef __HISTS_PYTHIAW_H_
#define __HISTS_PYTHIAW_H_
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

class HistsPythiaW : public makeHists
{
 public:

 ThreadHist<TH1D *>* FZmass_CC;

 ThreadHist<TH1D *>* BZmass_CC;

 ThreadHist<TH1D *>* FZmass_CF;

 ThreadHist<TH1D *>* BZmass_CF;

 ThreadHist<TH1D *>* ZPt;

 ThreadHist<TH1D *>* ZRapidity;

 ThreadHist<TH1D *>* ZMass;

 ThreadHist<TH1D *>* FZmass;

 ThreadHist<TH1D *>* BZmass;

 ThreadHist<TH1D *>* CosTheta;

 ThreadHist<TH1D *>* CollinsPhi;

 ThreadHist<TH1D *>* plot_phi_eta;

 ThreadHist<TH1D *>* leptonPt;

 ThreadHist<TH1D *>* leptonEta;

 ThreadHist<TH1D *>* WPt_ud;

 ThreadHist<TH1D *>* WRapidity_ud;

 ThreadHist<TH1D *>* WMass_ud;

 ThreadHist<TH1D *>* LeptonEta_ud;

 ThreadHist<TH1D *>* LeptonEta_LHCb_ud;

 ThreadHist<TH1D *>* WPt_cs;

 ThreadHist<TH1D *>* WRapidity_cs;

 ThreadHist<TH1D *>* WMass_cs;

 ThreadHist<TH1D *>* LeptonEta_cs;

 ThreadHist<TH1D *>* LeptonEta_LHCb_cs;

 ThreadHist<TH1D *>* WPt_us;

 ThreadHist<TH1D *>* WRapidity_us;

 ThreadHist<TH1D *>* WMass_us;

 ThreadHist<TH1D *>* LeptonEta_us;

 ThreadHist<TH1D *>* LeptonEta_LHCb_us;

 ThreadHist<AngularFunction *>* A0_ZPt;

 ThreadHist<AngularFunction *>* A1_ZPt;

 ThreadHist<AngularFunction *>* A2_ZPt;

 ThreadHist<AngularFunction *>* A3_ZPt;

 ThreadHist<AngularFunction *>* A4_ZPt;

 ThreadHist<AngularFunction *>* L0_ZPt;

//member function
 vector<TString> sysName;
 virtual void InitialSysName();
 virtual void bookHists(int TotalThread);

// template<class T>

};
#endif
