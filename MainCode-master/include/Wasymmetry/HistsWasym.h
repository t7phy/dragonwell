#ifndef __HISTS_WASYM_H_
#define __HISTS_WASYM_H_
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

class HistsWasym : public makeHists
{
 public:
//W Electron Event Plot 
 ThreadHist<TH1D *>* DataWEvent_Ele_CutFlow;
 ThreadHist<SysHist *>* WEvent_Ele_CutFlow_sys;
 ThreadHist<BkgHist *>* WEvent_Ele_CutFlow_bkg;

 ThreadHist<TH1D *>* DataWEvent_Posi_CutFlow;
 ThreadHist<SysHist *>* WEvent_Posi_CutFlow_sys;
 ThreadHist<BkgHist *>* WEvent_Posi_CutFlow_bkg;

 ThreadHist<TH1D *>* TruthWEvent_Ele_eta;
 ThreadHist<TH1D *>* DataWEvent_Ele_eta;
 ThreadHist<SysHist *>* WEvent_Ele_eta_sys;
 ThreadHist<BkgHist *>* WEvent_Ele_eta_bkg;

 ThreadHist<TH1D *>* TruthWEvent_Posi_eta;
 ThreadHist<TH1D *>* DataWEvent_Posi_eta;
 ThreadHist<SysHist *>* WEvent_Posi_eta_sys;
 ThreadHist<BkgHist *>* WEvent_Posi_eta_bkg;

 ThreadHist<TH1D *>* DataWEvent_WenuPt_reco;
 ThreadHist<SysHist *>* WEvent_WenuPt_reco_sys;
 ThreadHist<BkgHist *>* WEvent_WenuPt_reco_bkg;

//W Muon Event Plot
 ThreadHist<TH1D *>* DataWEvent_Muon_CutFlow;
 ThreadHist<SysHist *>* WEvent_Muon_CutFlow_sys;
 ThreadHist<BkgHist *>* WEvent_Muon_CutFlow_bkg;

 ThreadHist<TH1D *>* DataWEvent_AntiMuon_CutFlow;
 ThreadHist<SysHist *>* WEvent_AntiMuon_CutFlow_sys;
 ThreadHist<BkgHist *>* WEvent_AntiMuon_CutFlow_bkg;

 ThreadHist<TH1D *>* TruthWEvent_Muon_eta;
 ThreadHist<TH1D *>* DataWEvent_Muon_eta;
 ThreadHist<SysHist *>* WEvent_Muon_eta_sys;
 ThreadHist<BkgHist *>* WEvent_Muon_eta_bkg;

 ThreadHist<TH1D *>* TruthWEvent_AntiMuon_eta;
 ThreadHist<TH1D *>* DataWEvent_AntiMuon_eta;
 ThreadHist<SysHist *>* WEvent_AntiMuon_eta_sys;
 ThreadHist<BkgHist *>* WEvent_AntiMuon_eta_bkg;

 ThreadHist<TH1D *>* DataWEvent_WmunuPt_reco;
 ThreadHist<SysHist *>* WEvent_WmunuPt_reco_sys;
 ThreadHist<BkgHist *>* WEvent_WmunuPt_reco_bkg;

//Z Electron Event Plot
 ThreadHist<TH1D *>* DataZEvent_Ele_CutFlow;
 ThreadHist<SysHist *>* ZEvent_Ele_CutFlow_sys;
 ThreadHist<BkgHist *>* ZEvent_Ele_CutFlow_bkg;

 ThreadHist<TH1D *>* DataZEvent_Posi_CutFlow;
 ThreadHist<SysHist *>* ZEvent_Posi_CutFlow_sys;
 ThreadHist<BkgHist *>* ZEvent_Posi_CutFlow_bkg;

 ThreadHist<TH1D *>* DataZEvent_Ele_eta;
 ThreadHist<SysHist *>* ZEvent_Ele_eta_sys;
 ThreadHist<BkgHist *>* ZEvent_Ele_eta_bkg;

 ThreadHist<TH1D *>* DataZEvent_Posi_eta;
 ThreadHist<SysHist *>* ZEvent_Posi_eta_sys;
 ThreadHist<BkgHist *>* ZEvent_Posi_eta_bkg;

 ThreadHist<TH1D *>* DataZEvent_ZeeEvent_CutFlow;
 ThreadHist<SysHist *>* ZEvent_ZeeEvent_CutFlow_sys;
 ThreadHist<BkgHist *>* ZEvent_ZeeEvent_CutFlow_bkg;

 ThreadHist<TH1D *>* DataZEvent_ZeeMass_reco;
 ThreadHist<SysHist *>* ZEvent_ZeeMass_reco_sys;
 ThreadHist<BkgHist *>* ZEvent_ZeeMass_reco_bkg;

 ThreadHist<TH1D *>* DataZEvent_ZeePt_reco;
 ThreadHist<SysHist *>* ZEvent_ZeePt_reco_sys;
 ThreadHist<BkgHist *>* ZEvent_ZeePt_reco_bkg;

 ThreadHist<TH1D *>* DataZEvent_ZeeRapidity_reco;
 ThreadHist<SysHist *>* ZEvent_ZeeRapidity_reco_sys;
 ThreadHist<BkgHist *>* ZEvent_ZeeRapidity_reco_bkg;

//Z Muon Event Plot
 ThreadHist<TH1D *>* DataZEvent_Muon_CutFlow;
 ThreadHist<SysHist *>* ZEvent_Muon_CutFlow_sys;
 ThreadHist<BkgHist *>* ZEvent_Muon_CutFlow_bkg;

 ThreadHist<TH1D *>* DataZEvent_AntiMuon_CutFlow;
 ThreadHist<SysHist *>* ZEvent_AntiMuon_CutFlow_sys;
 ThreadHist<BkgHist *>* ZEvent_AntiMuon_CutFlow_bkg;

 ThreadHist<TH1D *>* DataZEvent_Muon_eta;
 ThreadHist<SysHist *>* ZEvent_Muon_eta_sys;
 ThreadHist<BkgHist *>* ZEvent_Muon_eta_bkg;

 ThreadHist<TH1D *>* DataZEvent_AntiMuon_eta;
 ThreadHist<SysHist *>* ZEvent_AntiMuon_eta_sys;
 ThreadHist<BkgHist *>* ZEvent_AntiMuon_eta_bkg;

 ThreadHist<TH1D *>* DataZEvent_ZmmEvent_CutFlow;
 ThreadHist<SysHist *>* ZEvent_ZmmEvent_CutFlow_sys;
 ThreadHist<BkgHist *>* ZEvent_ZmmEvent_CutFlow_bkg;

 ThreadHist<TH1D *>* DataZEvent_ZmmMass_reco;
 ThreadHist<SysHist *>* ZEvent_ZmmMass_reco_sys;
 ThreadHist<BkgHist *>* ZEvent_ZmmMass_reco_bkg;

 ThreadHist<TH1D *>* DataZEvent_ZmmPt_reco;
 ThreadHist<SysHist *>* ZEvent_ZmmPt_reco_sys;
 ThreadHist<BkgHist *>* ZEvent_ZmmPt_reco_bkg;

 ThreadHist<TH1D *>* DataZEvent_ZmmRapidity_reco;
 ThreadHist<SysHist *>* ZEvent_ZmmRapidity_reco_sys;
 ThreadHist<BkgHist *>* ZEvent_ZmmRapidity_reco_bkg;


 vector<TString> sysNameWenu;
 vector<TString> sysNameWmunu;
 vector<TString> sysNameZee;
 vector<TString> sysNameZmm;
 map<TString, int> SysNameWenuIndex;
 map<TString, int> SysNameWmunuIndex;
 map<TString, int> SysNameZeeIndex;
 map<TString, int> SysNameZmmIndex;

 vector<TString> bkgNameWenu;
 vector<TString> bkgNameWmunu;
 vector<TString> bkgNameZee;
 vector<TString> bkgNameZmm;
 map<TString, int> NameIndexWenu;
 map<TString, int> NameIndexWmunu;
 map<TString, int> NameIndexZee;
 map<TString, int> NameIndexZmm;

 bool OnlyNominal = true;
 virtual void RunAllSystematic();


 virtual int FindSysIndex(TString SysName, TString ProcessName);
 virtual void DefineSysName(int index, TString Name, TString ProcessName);

//member function
 virtual void InitialBkgName(TString ProcessName);

 virtual void InitialSysName(TString ProcessName);
 virtual void bookHists(int TotalThread);
 virtual void bookProcessHists(TString ProcessName, TString subName);

// template<class T>

};
#endif
