#ifndef ZPrime_SysZPrime_h
#define ZPrime_SysZPrime_h

#include "RootCommon.h"

using namespace std;

class SysZPrime
{
 public:

 TFile* writefile;

 vector<TString> ElSysList;
 vector<TString> MuSysList;

 vector<TFile *> ElRootFiles;
 vector<TFile *> MuRootFiles;

 vector<TString> HistNames;
 vector<TString> BkgNames_ee;
 vector<TString> BkgNames_mm;

 vector<TString> ElSystematics;
 vector<TString> MuSystematics;

 map<TString, vector<TH1D *>> ElSysHist_1d;
 map<TString, vector<TH1D *>> MuSysHist_1d;

 map<TString, TH1D *> ElFinalHist;
 map<TString, TH1D *> MuFinalHist;
 map<TString, TH1D *> ElUncHist;
 map<TString, TH1D *> MuUncHist;

 map<TString, vector<TH1D *>> ElSysVariation;
 map<TString, vector<TH1D *>> MuSysVariation;

 SysZPrime(){
   InitSysName();
   InitHistName();
 }
 virtual void ReadList(TString ElFileName, TString MuFileName);
 virtual void Initialize(vector<TString> ElRootNames, vector<TString> MuRootNames);
 virtual void CalculateSysUnc();
 virtual void SaveFile(TString FileName);

 virtual void InitSysName();
 virtual void InitHistName(){
   HistNames.push_back("Mll_HighMass");
   HistNames.push_back("pTll");
   HistNames.push_back("costheta");
   HistNames.push_back("DilRapidity");
   HistNames.push_back("LeadingLepEta");
   HistNames.push_back("SubleadingLepEta");

   BkgNames_ee.push_back("_SR_ee_Data");
   BkgNames_ee.push_back("_SR_ee_SumMC");
   BkgNames_ee.push_back("_SR_ee_topDD_SumMC");
   BkgNames_ee.push_back("_SR_ee_topDD_HighMass_CosTheta_SumMC");
   BkgNames_ee.push_back("_SR_ee_topDD_HighMass_Rapidity_SumMC");
   BkgNames_ee.push_back("_SR_ee_DrellYan");
   BkgNames_ee.push_back("_SR_ee_PhotonInduced");
   BkgNames_ee.push_back("_SR_ee_TopQuark");
   BkgNames_ee.push_back("_SR_ee_Diboson");
   BkgNames_ee.push_back("_SR_ee_Wjets_DD");
   BkgNames_ee.push_back("_SR_ee_Ztautau");
   BkgNames_ee.push_back("_topDD_ee");
   BkgNames_ee.push_back("_topDD_HighMass_CosTheta_ee");
   BkgNames_ee.push_back("_topDD_HighMass_Rapidity_ee");

   BkgNames_mm.push_back("_SR_mm_Data");
   BkgNames_mm.push_back("_SR_mm_SumMC");
   BkgNames_mm.push_back("_SR_mm_topDD_SumMC");
   BkgNames_mm.push_back("_SR_mm_topDD_HighMass_CosTheta_SumMC");
   BkgNames_mm.push_back("_SR_mm_topDD_HighMass_Rapidity_SumMC");
   BkgNames_mm.push_back("_SR_mm_DrellYan");
   BkgNames_mm.push_back("_SR_mm_PhotonInduced");
   BkgNames_mm.push_back("_SR_mm_TopQuark");
   BkgNames_mm.push_back("_SR_mm_Diboson");
   BkgNames_mm.push_back("_SR_mm_Wjets_DD");
   BkgNames_mm.push_back("_SR_mm_Ztautau");
   BkgNames_mm.push_back("_topDD_mm");
   BkgNames_mm.push_back("_topDD_HighMass_CosTheta_mm");
   BkgNames_mm.push_back("_topDD_HighMass_Rapidity_mm");
 }
};
#endif
