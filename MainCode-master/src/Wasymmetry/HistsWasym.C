#include "Wasymmetry/HistsWasym.h"

using namespace std;

void HistsWasym::bookHists(int TotalThread)
{
 this->TotalThread = TotalThread;
 TString tail = "";

 bookProcessHists((TString)"WSignal_Electron", (TString)"_WEvent");
 bookProcessHists((TString)"WSignal_Muon", (TString)"_WEvent");
 bookProcessHists((TString)"ZSignal_Electron", (TString)"_ZEvent");
 bookProcessHists((TString)"ZSignal_Muon", (TString)"_ZEvent");
}

void HistsWasym::bookProcessHists(TString ProcessName, TString subName)
{
 this->subName = subName;

 if(ProcessName == "WSignal_Electron"){
   InitialSysName(ProcessName);
   InitialBkgName(ProcessName);

   BookHist(DataWEvent_Ele_CutFlow, "Ele_CutFlow_Data", "Ele_CutFlow_Data", 20, 0, 20);
   BookHist(DataWEvent_Posi_CutFlow, "Posi_CutFlow_Data", "Posi_CutFlow_Data", 20, 0, 20);
   BookHist(DataWEvent_Ele_eta, "Ele_eta_Data", "Ele_eta_Data", 20, -2.5, 2.5);
   BookHist(DataWEvent_Posi_eta, "Posi_eta_Data", "Posi_eta_Data", 20, -2.5, 2.5);
   BookHist(DataWEvent_WenuPt_reco, "WenuPt_reco_Data", "WenuPt_reco_Data", 100, 0, 100);

   BookHist(TruthWEvent_Ele_eta, "Ele_eta_Truth", "Ele_eta_Truth", 20, -2.5, 2.5);
   BookHist(TruthWEvent_Posi_eta, "Posi_eta_Truth", "Posi_eta_Truth", 20, -2.5, 2.5);

   BookSysHist(WEvent_Ele_CutFlow_sys, sysNameWenu, "Ele_CutFlow", "Ele_CutFlow", 20, 0, 20);
   BookSysHist(WEvent_Posi_CutFlow_sys, sysNameWenu, "Posi_CutFlow", "Posi_CutFlow", 20, 0, 20);
   BookSysHist(WEvent_Ele_eta_sys, sysNameWenu, "Ele_eta", "Ele_eta", 20, -2.5, 2.5);
   BookSysHist(WEvent_Posi_eta_sys, sysNameWenu, "Posi_eta", "Posi_eta", 20, -2.5, 2.5);
   BookSysHist(WEvent_WenuPt_reco_sys, sysNameWenu, "WenuPt_reco", "WenuPt_reco", 100, 0, 100);

   BookBkgHist(WEvent_Ele_CutFlow_bkg, ProcessName, "Ele_CutFlow", "Ele_CutFlow", 20, 0, 20);
   BookBkgHist(WEvent_Posi_CutFlow_bkg, ProcessName, "Posi_CutFlow", "Posi_CutFlow", 20, 0, 20);
   BookBkgHist(WEvent_Ele_eta_bkg, ProcessName, "Ele_eta", "Ele_eta", 20, -2.5, 2.5);
   BookBkgHist(WEvent_Posi_eta_bkg, ProcessName, "Posi_eta", "Posi_eta", 20, -2.5, 2.5);
   BookBkgHist(WEvent_WenuPt_reco_bkg, ProcessName, "WenuPt_reco", "WenuPt_reco", 100, 0, 100);

 }

 if(ProcessName == "WSignal_Muon"){
   InitialSysName(ProcessName);
   InitialBkgName(ProcessName);

   BookHist(DataWEvent_Muon_CutFlow, "Muon_CutFlow_Data", "Muon_CutFlow_Data", 20, 0, 20);
   BookHist(DataWEvent_AntiMuon_CutFlow, "AntiMuon_CutFlow_Data", "AntiMuon_CutFlow_Data", 20, 0, 20);
   BookHist(DataWEvent_Muon_eta, "Muon_eta_Data", "Muon_eta_Data", 20, -2.5, 2.5);
   BookHist(DataWEvent_AntiMuon_eta, "AntiMuon_eta_Data", "AntiMuon_eta_Data", 20, -2.5, 2.5);
   BookHist(DataWEvent_WmunuPt_reco, "WmunuPt_reco_Data", "WmunuPt_reco_Data", 100, 0, 100);

   BookHist(TruthWEvent_Muon_eta, "Muon_eta_Truth", "Muon_eta_Truth", 20, -2.5, 2.5);
   BookHist(TruthWEvent_AntiMuon_eta, "AntiMuon_eta_Truth", "AntiMuon_eta_Truth", 20, -2.5, 2.5);

   BookSysHist(WEvent_Muon_CutFlow_sys, sysNameWmunu, "Muon_CutFlow", "Muon_CutFlow", 20, 0, 20);
   BookSysHist(WEvent_AntiMuon_CutFlow_sys, sysNameWmunu, "AntiMuon_CutFlow", "AntiMuon_CutFlow", 20, 0, 20);
   BookSysHist(WEvent_Muon_eta_sys, sysNameWmunu, "Muon_eta", "Muon_eta", 20, -2.5, 2.5);
   BookSysHist(WEvent_AntiMuon_eta_sys, sysNameWmunu, "AntiMuon_eta", "AntiMuon_eta", 20, -2.5, 2.5);
   BookSysHist(WEvent_WmunuPt_reco_sys, sysNameWmunu, "WmunuPt_reco", "WmunuPt_reco", 100, 0, 100);

   BookBkgHist(WEvent_Muon_CutFlow_bkg, ProcessName, "Muon_CutFlow", "Muon_CutFlow", 20, 0, 20);
   BookBkgHist(WEvent_AntiMuon_CutFlow_bkg, ProcessName, "AntiMuon_CutFlow", "AntiMuon_CutFlow", 20, 0, 20);
   BookBkgHist(WEvent_Muon_eta_bkg, ProcessName, "Muon_eta", "Muon_eta", 20, -2.5, 2.5);
   BookBkgHist(WEvent_AntiMuon_eta_bkg, ProcessName, "AntiMuon_eta", "AntiMuon_eta", 20, -2.5, 2.5);
   BookBkgHist(WEvent_WmunuPt_reco_bkg, ProcessName, "WmunuPt_reco", "WmunuPt_reco", 100, 0, 100);


 }
 if(ProcessName == "ZSignal_Electron"){
   InitialSysName(ProcessName);
   InitialBkgName(ProcessName);

   BookHist(DataZEvent_ZeeEvent_CutFlow, "ZeeEvent_CutFlow_Data", "ZeeEvent_CutFlow_Data", 20, 0, 20);
   BookHist(DataZEvent_Ele_CutFlow, "Ele_CutFlow_Data", "Ele_CutFlow_Data", 20, 0, 20);
   BookHist(DataZEvent_Posi_CutFlow, "Posi_CutFlow_Data", "Posi_CutFlow_Data", 20, 0, 20);
   BookHist(DataZEvent_Ele_eta, "Ele_eta_Data", "Ele_eta_Data", 20, -2.5, 2.5);
   BookHist(DataZEvent_Posi_eta, "Posi_eta_Data", "Posi_eta_Data", 20, -2.5, 2.5);
   BookHist(DataZEvent_ZeeMass_reco, "ZeeMass_reco_Data", "ZeeMass_reco_Data", 35, 60, 130);
   BookHist(DataZEvent_ZeePt_reco, "ZeePt_reco_Data", "ZeePt_reco_Data", 50, 0, 100);
   BookHist(DataZEvent_ZeeRapidity_reco, "ZeeRapidity_reco_Data", "ZeeRapidity_reco_Data", 20, -5, 5);

   BookSysHist(ZEvent_ZeeEvent_CutFlow_sys, sysNameZee, "ZeeEvent_CutFlow", "ZeeEvent_CutFlow", 20, 0, 20);
   BookSysHist(ZEvent_Ele_CutFlow_sys, sysNameZee, "Ele_CutFlow", "Ele_CutFlow", 20, 0, 20);
   BookSysHist(ZEvent_Posi_CutFlow_sys, sysNameZee, "Posi_CutFlow", "Posi_CutFlow", 20, 0, 20);
   BookSysHist(ZEvent_Ele_eta_sys, sysNameZee, "Ele_eta", "Ele_eta", 20, -2.5, 2.5);
   BookSysHist(ZEvent_Posi_eta_sys, sysNameZee, "Posi_eta", "Posi_eta", 20, -2.5, 2.5);
   BookSysHist(ZEvent_ZeeMass_reco_sys, sysNameZee, "ZeeMass_reco", "ZeeMass_reco", 35, 60, 130);
   BookSysHist(ZEvent_ZeePt_reco_sys, sysNameZee, "ZeePt_reco", "ZeePt_reco", 50, 0, 100);
   BookSysHist(ZEvent_ZeeRapidity_reco_sys, sysNameZee, "ZeeRapidity_reco", "ZeeRapidity_reco", 20, -5, 5);

   BookBkgHist(ZEvent_ZeeEvent_CutFlow_bkg, ProcessName, "ZeeEvent_CutFlow", "ZeeEvent_CutFlow", 20, 0, 20);
   BookBkgHist(ZEvent_Ele_CutFlow_bkg, ProcessName, "Ele_CutFlow", "Ele_CutFlow", 20, 0, 20);
   BookBkgHist(ZEvent_Posi_CutFlow_bkg, ProcessName, "Posi_CutFlow", "Posi_CutFlow", 20, 0, 20);
   BookBkgHist(ZEvent_Ele_eta_bkg, ProcessName, "Ele_eta", "Ele_eta", 20, -2.5, 2.5);
   BookBkgHist(ZEvent_Posi_eta_bkg, ProcessName, "Posi_eta", "Posi_eta", 20, -2.5, 2.5);
   BookBkgHist(ZEvent_ZeeMass_reco_bkg, ProcessName, "ZeeMass_reco", "ZeeMass_reco", 35, 60, 130);
   BookBkgHist(ZEvent_ZeePt_reco_bkg, ProcessName, "ZeePt_reco", "ZeePt_reco", 50, 0, 100);
   BookBkgHist(ZEvent_ZeeRapidity_reco_bkg, ProcessName, "ZeeRapidity_reco", "ZeeRapidity_reco", 20, -5, 5);


 }
 if(ProcessName == "ZSignal_Muon"){
   InitialSysName(ProcessName);
   InitialBkgName(ProcessName);

   BookHist(DataZEvent_ZmmEvent_CutFlow, "ZmmEvent_CutFlow_Data", "ZmmEvent_CutFlow_Data", 20, 0, 20);
   BookHist(DataZEvent_Muon_CutFlow,     "Muon_CutFlow_Data",     "Muon_CutFlow_Data",     20, 0, 20);
   BookHist(DataZEvent_AntiMuon_CutFlow, "AntiMuon_CutFlow_Data", "AntiMuon_CutFlow_Data", 20, 0, 20);
   BookHist(DataZEvent_Muon_eta,         "Muon_eta_Data",         "Muon_eta_Data",         20, -5, 5);
   BookHist(DataZEvent_AntiMuon_eta,     "AntiMuon_eta_Data",     "AntiMuon_eta_Data",     20, -5, 5);
   BookHist(DataZEvent_ZmmMass_reco,     "ZmmMass_reco_Data",     "ZmmMass_reco_Data",     35, 60, 130);
   BookHist(DataZEvent_ZmmPt_reco,       "ZmmPt_reco_Data",       "ZmmPt_reco_Data",       50, 0, 100);
   BookHist(DataZEvent_ZmmRapidity_reco, "ZmmRapidity_reco_Data", "ZmmRapidity_reco_Data", 20, -5, 5);

/*   BookSysHist(ZEvent_ZmmEvent_CutFlow_sys, sysNameZmm, "ZmmEvent_CutFlow", "ZmmEvent_CutFlow", 20, 0, 20);
   BookSysHist(ZEvent_Muon_CutFlow_sys, sysNameZmm, "Muon_CutFlow", "Muon_CutFlow", 20, 0, 20);
   BookSysHist(ZEvent_AntiMuon_CutFlow_sys, sysNameZmm, "AntiMuon_CutFlow", "AntiMuon_CutFlow", 20, 0, 20);
   BookSysHist(ZEvent_Muon_eta_sys, sysNameZmm, "Muon_eta", "Muon_eta", 20, -5, 5);
   BookSysHist(ZEvent_AntiMuon_eta_sys, sysNameZmm, "AntiMuon_eta", "AntiMuon_eta", 20, -5, 5);
   BookSysHist(ZEvent_ZmmMass_reco_sys, sysNameZmm, "ZmmMass_reco", "ZmmMass_reco", 35, 60, 130);
   BookSysHist(ZEvent_ZmmPt_reco_sys, sysNameZmm, "ZmmPt_reco", "ZmmPt_reco", 50, 0, 100);
   BookSysHist(ZEvent_ZmmRapidity_reco_sys, sysNameZmm, "ZmmRapidity_reco", "ZmmRapidity_reco", 20, -5, 5);
*/
   BookBkgHist(ZEvent_ZmmEvent_CutFlow_bkg, ProcessName, "ZmmEvent_CutFlow", "ZmmEvent_CutFlow", 20, 0, 20);
   BookBkgHist(ZEvent_Muon_CutFlow_bkg, ProcessName, "Muon_CutFlow", "Muon_CutFlow", 20, 0, 20);
   BookBkgHist(ZEvent_AntiMuon_CutFlow_bkg, ProcessName, "AntiMuon_CutFlow", "AntiMuon_CutFlow", 20, 0, 20);
   BookBkgHist(ZEvent_Muon_eta_bkg, ProcessName, "Muon_eta", "Muon_eta", 20, -5, 5);
   BookBkgHist(ZEvent_AntiMuon_eta_bkg, ProcessName, "AntiMuon_eta", "AntiMuon_eta", 20, -5, 5);
   BookBkgHist(ZEvent_ZmmMass_reco_bkg, ProcessName, "ZmmMass_reco", "ZmmMass_reco", 35, 60, 130);
   BookBkgHist(ZEvent_ZmmPt_reco_bkg, ProcessName, "ZmmPt_reco", "ZmmPt_reco", 50, 0, 100);
   BookBkgHist(ZEvent_ZmmRapidity_reco_bkg, ProcessName, "ZmmRapidity_reco", "ZmmRapidity_reco", 20, -5, 5);


 }

}

void HistsWasym::RunAllSystematic()
{
 OnlyNominal = false;
}

int HistsWasym::FindSysIndex(TString SysName, TString ProcessName)
{
 int index;
 if(ProcessName == "WSignal_Electron") index = SysNameWenuIndex[SysName];
 if(ProcessName == "WSignal_Muon") index = SysNameWmunuIndex[SysName];
 if(ProcessName == "ZSignal_Electron") index = SysNameZeeIndex[SysName];
 if(ProcessName == "ZSignal_Muon") index = SysNameZmmIndex[SysName];

 return index;
}

void HistsWasym::DefineSysName(int index, TString Name, TString ProcessName)
{
 if(ProcessName == "WSignal_Electron"){
   SysNameWenuIndex[Name] = index;
   sysNameWenu.push_back(Name);
 }

 if(ProcessName == "WSignal_Muon"){
   SysNameWmunuIndex[Name] = index;
   sysNameWmunu.push_back(Name);
 }

 if(ProcessName == "ZSignal_Electron"){
   SysNameZeeIndex[Name] = index;
   sysNameZee.push_back(Name);
 }

 if(ProcessName == "ZSignal_Muon"){
   SysNameZmmIndex[Name] = index;
   sysNameZmm.push_back(Name);
 }

}

void HistsWasym::InitialBkgName(TString ProcessName)
{
 if(ProcessName == "WSignal_Electron"){
   bkgNameWenu.push_back("BkgTao");
   bkgNameWenu.push_back("BkgDiboson");
   bkgNameWenu.push_back("BkgWtop");
   bkgNameWenu.push_back("Bkgttbar");
   bkgNameWenu.push_back("BkgSingletop");
   bkgNameWenu.push_back("BkgWZ");

   for(int i = 0; i < bkgNameWenu.size(); i++){
     NameIndexWenu[bkgNameWenu.at(i)] = i;
   }
 }

 if(ProcessName == "WSignal_Muon"){
   bkgNameWmunu.push_back("BkgTao");
   bkgNameWmunu.push_back("BkgDiboson");
   bkgNameWmunu.push_back("BkgWtop");
   bkgNameWmunu.push_back("Bkgttbar");
   bkgNameWmunu.push_back("BkgSingletop");
   bkgNameWmunu.push_back("BkgWZ");

   for(int i = 0; i < bkgNameWmunu.size(); i++){
     NameIndexWmunu[bkgNameWmunu.at(i)] = i;
   }
 }

 if(ProcessName == "ZSignal_Electron"){
   bkgNameZee.push_back("BkgTao");
   bkgNameZee.push_back("BkgDiboson");
   bkgNameZee.push_back("BkgWtop");
   bkgNameZee.push_back("Bkgttbar");
   bkgNameZee.push_back("BkgSingletop");
   bkgNameZee.push_back("BkgWZ");

   for(int i = 0; i < bkgNameZee.size(); i++){
     NameIndexZee[bkgNameZee.at(i)] = i;
   }
 }

 if(ProcessName == "ZSignal_Muon"){
   bkgNameZmm.push_back("BkgTao");
   bkgNameZmm.push_back("BkgDiboson");
   bkgNameZmm.push_back("BkgWtop");
   bkgNameZmm.push_back("Bkgttbar");
   bkgNameZmm.push_back("BkgSingletop");
   bkgNameZmm.push_back("BkgWZ");
 
   for(int i = 0; i < bkgNameZmm.size(); i++){
     NameIndexZmm[bkgNameZmm.at(i)] = i;
   }
 }

}

void HistsWasym::InitialSysName(TString ProcessName)
{
 if(ProcessName == "WSignal_Electron"){
   DefineSysName(0, "Nominal", ProcessName);
   if(OnlyNominal) return;

   DefineSysName(1, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1down", ProcessName);
   DefineSysName(2, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1up", ProcessName);
   DefineSysName(3, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1down", ProcessName);
   DefineSysName(4, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1up", ProcessName);
   DefineSysName(5, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1down", ProcessName);
   DefineSysName(6, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1up", ProcessName);
   DefineSysName(7, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1down", ProcessName);
   DefineSysName(8, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1up", ProcessName);
   DefineSysName(9, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1down", ProcessName);
   DefineSysName(10, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1up", ProcessName);
   DefineSysName(11, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1down", ProcessName);
   DefineSysName(12, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1up", ProcessName);

   DefineSysName(13, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_down", ProcessName);
   DefineSysName(14, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_up", ProcessName);
   DefineSysName(15, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_down", ProcessName);
   DefineSysName(16, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_up", ProcessName);
   DefineSysName(17, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_down", ProcessName);
   DefineSysName(18, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_up", ProcessName);
   DefineSysName(19, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_down", ProcessName);
   DefineSysName(20, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_up", ProcessName);
   DefineSysName(21, "isosf_ElIsoSys_uncorr_up", ProcessName);
   DefineSysName(22, "isosf_ElIsoSys_uncorr_down", ProcessName);

   DefineSysName(23, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_down", ProcessName);
   DefineSysName(24, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_up", ProcessName);
   DefineSysName(25, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_down", ProcessName);
   DefineSysName(26, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_up", ProcessName);
   DefineSysName(27, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_down", ProcessName);
   DefineSysName(28, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_up", ProcessName);
   DefineSysName(29, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_down", ProcessName);
   DefineSysName(30, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_up", ProcessName);
   DefineSysName(31, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_down", ProcessName);
   DefineSysName(32, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_up", ProcessName);
   DefineSysName(33, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_down", ProcessName);
   DefineSysName(34, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_up", ProcessName);
   DefineSysName(35, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_down", ProcessName);
   DefineSysName(36, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_up", ProcessName);
   DefineSysName(37, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_down", ProcessName);
   DefineSysName(38, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_up", ProcessName);
   DefineSysName(39, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_down", ProcessName);
   DefineSysName(40, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_up", ProcessName);
   DefineSysName(41, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_down", ProcessName);
   DefineSysName(42, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_up", ProcessName);
   DefineSysName(43, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_down", ProcessName);
   DefineSysName(44, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_up", ProcessName);
   DefineSysName(45, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_down", ProcessName);
   DefineSysName(46, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_up", ProcessName);
   DefineSysName(47, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_down", ProcessName);
   DefineSysName(48, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_up", ProcessName);
   DefineSysName(49, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_down", ProcessName);
   DefineSysName(50, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_up", ProcessName);
   DefineSysName(51, "idsf_ElIDSys_uncorr_up", ProcessName);
   DefineSysName(52, "idsf_ElIDSys_uncorr_down", ProcessName);

   DefineSysName(53, "trigsf_ElTrigSys_FullSim_corr8_down", ProcessName);
   DefineSysName(54, "trigsf_ElTrigSys_FullSim_corr8_up", ProcessName);
   DefineSysName(55, "trigsf_ElTrigSys_FullSim_corr9_down", ProcessName);
   DefineSysName(56, "trigsf_ElTrigSys_FullSim_corr9_up", ProcessName);
   DefineSysName(57, "trigsf_ElTrigSys_FullSim_corr10_down", ProcessName);
   DefineSysName(58, "trigsf_ElTrigSys_FullSim_corr10_up", ProcessName);
   DefineSysName(59, "trigsf_ElTrigSys_FullSim_corr11_down", ProcessName);
   DefineSysName(60, "trigsf_ElTrigSys_FullSim_corr11_up", ProcessName);
   DefineSysName(61, "trigsf_ElTrigSys_FullSim_corr12_down", ProcessName);
   DefineSysName(62, "trigsf_ElTrigSys_FullSim_corr12_up", ProcessName);
   DefineSysName(63, "trigsf_ElTrigSys_FullSim_corr13_down", ProcessName);
   DefineSysName(64, "trigsf_ElTrigSys_FullSim_corr13_up", ProcessName);
   DefineSysName(65, "trigsf_ElTrigSys_FullSim_corr14_down", ProcessName);
   DefineSysName(66, "trigsf_ElTrigSys_FullSim_corr14_up", ProcessName);
   DefineSysName(67, "trigsf_ElTrigSys_uncorr_up", ProcessName);
   DefineSysName(68, "trigsf_ElTrigSys_uncorr_down", ProcessName);

   DefineSysName(69, "corrected_pt_scaleDown_NP1", ProcessName);
   DefineSysName(70, "corrected_pt_scaleUp_NP1", ProcessName);
   DefineSysName(71, "corrected_pt_scaleDown_NP2", ProcessName);
   DefineSysName(72, "corrected_pt_scaleUp_NP2", ProcessName);
   DefineSysName(73, "corrected_pt_scaleDown_NP3", ProcessName);
   DefineSysName(74, "corrected_pt_scaleUp_NP3", ProcessName);
   DefineSysName(75, "corrected_pt_scaleDown_NP4", ProcessName);
   DefineSysName(76, "corrected_pt_scaleUp_NP4", ProcessName);
   DefineSysName(77, "corrected_pt_scaleDown_NP5", ProcessName);
   DefineSysName(78, "corrected_pt_scaleUp_NP5", ProcessName);
   DefineSysName(79, "corrected_pt_scaleDown_NP6", ProcessName);
   DefineSysName(80, "corrected_pt_scaleUp_NP6", ProcessName);
   DefineSysName(81, "corrected_pt_scaleDown_NP7", ProcessName);
   DefineSysName(82, "corrected_pt_scaleUp_NP7", ProcessName);
   DefineSysName(83, "corrected_pt_scaleDown_NP8", ProcessName);
   DefineSysName(84, "corrected_pt_scaleUp_NP8", ProcessName);
   DefineSysName(85, "corrected_pt_scaleDown_NP9", ProcessName);
   DefineSysName(86, "corrected_pt_scaleUp_NP9", ProcessName);
   DefineSysName(87, "corrected_pt_scaleDown_NP10", ProcessName);
   DefineSysName(88, "corrected_pt_scaleUp_NP10", ProcessName);
   DefineSysName(89, "corrected_pt_scaleDown_NP11", ProcessName);
   DefineSysName(90, "corrected_pt_scaleUp_NP11", ProcessName);
   DefineSysName(91, "corrected_pt_scaleDown_NP12", ProcessName);
   DefineSysName(92, "corrected_pt_scaleUp_NP12", ProcessName);
   DefineSysName(93, "corrected_pt_scaleDown_NP13", ProcessName);
   DefineSysName(94, "corrected_pt_scaleUp_NP13", ProcessName);
   DefineSysName(95, "corrected_pt_scaleDown_NP14", ProcessName);
   DefineSysName(96, "corrected_pt_scaleUp_NP14", ProcessName);
   DefineSysName(97, "corrected_pt_scaleDown_NP15", ProcessName);
   DefineSysName(98, "corrected_pt_scaleUp_NP15", ProcessName);
   DefineSysName(99, "corrected_pt_scaleDown_NP16", ProcessName);
   DefineSysName(100, "corrected_pt_scaleUp_NP16", ProcessName);
   DefineSysName(101, "corrected_pt_scaleDown_NP17", ProcessName);
   DefineSysName(102, "corrected_pt_scaleUp_NP17", ProcessName);
   DefineSysName(103, "corrected_pt_scaleDown_NP18", ProcessName);
   DefineSysName(104, "corrected_pt_scaleUp_NP18", ProcessName);
   DefineSysName(105, "corrected_pt_scaleDown_NP19", ProcessName);
   DefineSysName(106, "corrected_pt_scaleUp_NP19", ProcessName);
   DefineSysName(107, "corrected_pt_scaleDown_NP20", ProcessName);
   DefineSysName(108, "corrected_pt_scaleUp_NP20", ProcessName);
   DefineSysName(109, "corrected_pt_scaleDown_NP21", ProcessName);
   DefineSysName(110, "corrected_pt_scaleUp_NP21", ProcessName);
   DefineSysName(111, "corrected_pt_scaleDown_NP22", ProcessName);
   DefineSysName(112, "corrected_pt_scaleUp_NP22", ProcessName);
   DefineSysName(113, "corrected_pt_scaleDown_NP23", ProcessName);
   DefineSysName(114, "corrected_pt_scaleUp_NP23", ProcessName);
   DefineSysName(115, "corrected_pt_scaleDown_NP24", ProcessName);
   DefineSysName(116, "corrected_pt_scaleUp_NP24", ProcessName);

   DefineSysName(117, "corrected_pt_cDown_NP1", ProcessName);
   DefineSysName(118, "corrected_pt_cUp_NP1", ProcessName);
   DefineSysName(119, "corrected_pt_cDown_NP2", ProcessName);
   DefineSysName(120, "corrected_pt_cUp_NP2", ProcessName);
   DefineSysName(121, "corrected_pt_cDown_NP3", ProcessName);
   DefineSysName(122, "corrected_pt_cUp_NP3", ProcessName);
   DefineSysName(123, "corrected_pt_cDown_NP4", ProcessName);
   DefineSysName(124, "corrected_pt_cUp_NP4", ProcessName);
   DefineSysName(125, "corrected_pt_cDown_NP5", ProcessName);
   DefineSysName(126, "corrected_pt_cUp_NP5", ProcessName);
   DefineSysName(127, "corrected_pt_cDown_NP6", ProcessName);
   DefineSysName(128, "corrected_pt_cUp_NP6", ProcessName);
   DefineSysName(129, "corrected_pt_cDown_NP7", ProcessName);
   DefineSysName(130, "corrected_pt_cUp_NP7", ProcessName);
   DefineSysName(131, "corrected_pt_cDown_NP8", ProcessName);
   DefineSysName(132, "corrected_pt_cUp_NP8", ProcessName);
   DefineSysName(133, "corrected_pt_cDown_NP9", ProcessName);
   DefineSysName(134, "corrected_pt_cUp_NP9", ProcessName);
   DefineSysName(135, "corrected_pt_cDown_NP10", ProcessName);
   DefineSysName(136, "corrected_pt_cUp_NP10", ProcessName);
   DefineSysName(137, "corrected_pt_cDown_NP11", ProcessName);
   DefineSysName(138, "corrected_pt_cUp_NP11", ProcessName);
   DefineSysName(139, "corrected_pt_cDown_NP12", ProcessName);
   DefineSysName(140, "corrected_pt_cUp_NP12", ProcessName);
   DefineSysName(141, "corrected_pt_cDown_NP13", ProcessName);
   DefineSysName(142, "corrected_pt_cUp_NP13", ProcessName);
   DefineSysName(143, "corrected_pt_cDown_NP14", ProcessName);
   DefineSysName(144, "corrected_pt_cUp_NP14", ProcessName);
   DefineSysName(145, "corrected_pt_cDown_NP15", ProcessName);
   DefineSysName(146, "corrected_pt_cUp_NP15", ProcessName);
   DefineSysName(147, "corrected_pt_cDown_NP16", ProcessName);
   DefineSysName(148, "corrected_pt_cUp_NP16", ProcessName);
   DefineSysName(149, "corrected_pt_cDown_NP17", ProcessName);
   DefineSysName(150, "corrected_pt_cUp_NP17", ProcessName);
   DefineSysName(151, "corrected_pt_cDown_NP18", ProcessName);
   DefineSysName(152, "corrected_pt_cUp_NP18", ProcessName);
   DefineSysName(153, "corrected_pt_cDown_NP19", ProcessName);
   DefineSysName(154, "corrected_pt_cUp_NP19", ProcessName);
   DefineSysName(155, "corrected_pt_cDown_NP20", ProcessName);
   DefineSysName(156, "corrected_pt_cUp_NP20", ProcessName);
   DefineSysName(157, "corrected_pt_cDown_NP21", ProcessName);
   DefineSysName(158, "corrected_pt_cUp_NP21", ProcessName);
   DefineSysName(159, "corrected_pt_cDown_NP22", ProcessName);
   DefineSysName(160, "corrected_pt_cUp_NP22", ProcessName);
   DefineSysName(161, "corrected_pt_cDown_NP23", ProcessName);
   DefineSysName(162, "corrected_pt_cUp_NP23", ProcessName);
   DefineSysName(163, "corrected_pt_cDown_NP24", ProcessName);
   DefineSysName(164, "corrected_pt_cUp_NP24", ProcessName);

   DefineSysName(165, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN1", ProcessName);
   DefineSysName(166, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP1", ProcessName);
   DefineSysName(167, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN1", ProcessName);
   DefineSysName(168, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP1", ProcessName);
   DefineSysName(169, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN2", ProcessName);
   DefineSysName(170, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP2", ProcessName);
   DefineSysName(171, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN2", ProcessName);
   DefineSysName(172, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP2", ProcessName);
   DefineSysName(173, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN3", ProcessName);
   DefineSysName(174, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP3", ProcessName);
   DefineSysName(175, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN3", ProcessName);
   DefineSysName(176, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP3", ProcessName);
   DefineSysName(177, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN4", ProcessName);
   DefineSysName(178, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP4", ProcessName);
   DefineSysName(179, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN4", ProcessName);
   DefineSysName(180, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP4", ProcessName);
   DefineSysName(181, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN5", ProcessName);
   DefineSysName(182, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP5", ProcessName);
   DefineSysName(183, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN5", ProcessName);
   DefineSysName(184, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP5", ProcessName);
   DefineSysName(185, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN6", ProcessName);
   DefineSysName(186, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP6", ProcessName);
   DefineSysName(187, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN6", ProcessName);
   DefineSysName(188, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP6", ProcessName);
   DefineSysName(189, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN7", ProcessName);
   DefineSysName(190, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP7", ProcessName);
   DefineSysName(191, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN7", ProcessName);
   DefineSysName(192, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP7", ProcessName);
   DefineSysName(193, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN8", ProcessName);
   DefineSysName(194, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP8", ProcessName);
   DefineSysName(195, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN8", ProcessName);
   DefineSysName(196, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP8", ProcessName);
   DefineSysName(197, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN9", ProcessName);
   DefineSysName(198, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP9", ProcessName);
   DefineSysName(199, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN9", ProcessName);
   DefineSysName(200, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP9", ProcessName);
   DefineSysName(201, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN10", ProcessName);
   DefineSysName(202, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP10", ProcessName);
   DefineSysName(203, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN10", ProcessName);
   DefineSysName(204, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP10", ProcessName);
   DefineSysName(205, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN11", ProcessName);
   DefineSysName(206, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP11", ProcessName);
   DefineSysName(207, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN11", ProcessName);
   DefineSysName(208, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP11", ProcessName);
   DefineSysName(209, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN12", ProcessName);
   DefineSysName(210, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP12", ProcessName);
   DefineSysName(211, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN12", ProcessName);
   DefineSysName(212, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP12", ProcessName);
   DefineSysName(213, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN13", ProcessName);
   DefineSysName(214, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP13", ProcessName);
   DefineSysName(215, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN13", ProcessName);
   DefineSysName(216, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP13", ProcessName);
   DefineSysName(217, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN14", ProcessName);
   DefineSysName(218, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP14", ProcessName);
   DefineSysName(219, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN14", ProcessName);
   DefineSysName(220, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP14", ProcessName);

   DefineSysName(220, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_DOWN", ProcessName);
   DefineSysName(221, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_UP", ProcessName);

   DefineSysName(222, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN1", ProcessName);
   DefineSysName(223, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP1", ProcessName);
   DefineSysName(224, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN1", ProcessName);
   DefineSysName(225, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP1", ProcessName);
   DefineSysName(226, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN2", ProcessName);
   DefineSysName(227, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP2", ProcessName);
   DefineSysName(228, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN2", ProcessName);
   DefineSysName(229, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP2", ProcessName);
   DefineSysName(230, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN3", ProcessName);
   DefineSysName(231, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP3", ProcessName);
   DefineSysName(232, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN3", ProcessName);
   DefineSysName(233, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP3", ProcessName);
   DefineSysName(234, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN4", ProcessName);
   DefineSysName(235, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP4", ProcessName);
   DefineSysName(236, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN4", ProcessName);
   DefineSysName(237, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP4", ProcessName);
   DefineSysName(238, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN5", ProcessName);
   DefineSysName(239, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP5", ProcessName);
   DefineSysName(240, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN5", ProcessName);
   DefineSysName(241, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP5", ProcessName);
   DefineSysName(242, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN6", ProcessName);
   DefineSysName(243, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP6", ProcessName);
   DefineSysName(244, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN6", ProcessName);
   DefineSysName(245, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP6", ProcessName);
   DefineSysName(246, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN7", ProcessName);
   DefineSysName(247, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP7", ProcessName);
   DefineSysName(248, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN7", ProcessName);
   DefineSysName(249, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP7", ProcessName);
   DefineSysName(250, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN8", ProcessName);
   DefineSysName(251, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP8", ProcessName);
   DefineSysName(252, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN8", ProcessName);
   DefineSysName(253, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP8", ProcessName);
   DefineSysName(254, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN9", ProcessName);
   DefineSysName(255, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP9", ProcessName);
   DefineSysName(256, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN9", ProcessName);
   DefineSysName(257, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP9", ProcessName);
   DefineSysName(258, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN10", ProcessName);
   DefineSysName(259, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP10", ProcessName);
   DefineSysName(260, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN10", ProcessName);
   DefineSysName(261, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP10", ProcessName);
   DefineSysName(262, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN11", ProcessName);
   DefineSysName(263, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP11", ProcessName);
   DefineSysName(264, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN11", ProcessName);
   DefineSysName(265, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP11", ProcessName);
   DefineSysName(266, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN12", ProcessName);
   DefineSysName(267, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP12", ProcessName);
   DefineSysName(268, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN12", ProcessName);
   DefineSysName(269, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP12", ProcessName);
   DefineSysName(270, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN13", ProcessName);
   DefineSysName(271, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP13", ProcessName);
   DefineSysName(272, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN13", ProcessName);
   DefineSysName(273, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP13", ProcessName);
   DefineSysName(274, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN14", ProcessName);
   DefineSysName(275, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP14", ProcessName);
   DefineSysName(276, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN14", ProcessName);
   DefineSysName(277, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP14", ProcessName);
   DefineSysName(278, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN15", ProcessName);
   DefineSysName(279, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP15", ProcessName);
   DefineSysName(280, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN15", ProcessName);
   DefineSysName(281, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP15", ProcessName);

   DefineSysName(282, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_DOWN", ProcessName);
   DefineSysName(283, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_UP", ProcessName);
   DefineSysName(284, "Recoil_loose_pfoEM_RESPONSE_SYS_DOWN", ProcessName);
   DefineSysName(285, "Recoil_loose_pfoEM_RESPONSE_SYS_UP", ProcessName);
   DefineSysName(286, "Recoil_loose_pfoEM_SET_SYS", ProcessName);

 }
 if(ProcessName == "WSignal_Muon"){
   DefineSysName(0, "Nominal", ProcessName);
   if(OnlyNominal) return;

   DefineSysName(1, "syspt_MUON_ID__1down", ProcessName);
   DefineSysName(2, "syspt_MUON_ID__1up", ProcessName);
   DefineSysName(3, "syspt_MUON_MS__1down", ProcessName);
   DefineSysName(4, "syspt_MUON_MS__1up", ProcessName);
   DefineSysName(5, "syspt_MUON_SCALE__1down", ProcessName);
   DefineSysName(6, "syspt_MUON_SCALE__1up", ProcessName);

   DefineSysName(7, "recosf_MuRecoSys_corr_QCDTEMPLATE_down", ProcessName);
   DefineSysName(8, "recosf_MuRecoSys_corr_QCDTEMPLATE_up", ProcessName);
   DefineSysName(9, "recosf_MuRecoSys_corr_BKGFRACTION_down", ProcessName);
   DefineSysName(10, "recosf_MuRecoSys_corr_BKGFRACTION_up", ProcessName);
   DefineSysName(11, "recosf_MuRecoSys_corr_LUMIUNCERT_down", ProcessName);
   DefineSysName(12, "recosf_MuRecoSys_corr_LUMIUNCERT_up", ProcessName);
   DefineSysName(13, "recosf_MuRecoSys_corr_MCXSEC_down", ProcessName);
   DefineSysName(14, "recosf_MuRecoSys_corr_MCXSEC_up", ProcessName);
   DefineSysName(15, "recosf_MuRecoSys_corr_SUPRESSIONSCALE_down", ProcessName);
   DefineSysName(16, "recosf_MuRecoSys_corr_SUPRESSIONSCALE_up", ProcessName);
   DefineSysName(17, "recosf_MuRecoSys_corr_MATCHING_SYM_down", ProcessName);
   DefineSysName(18, "recosf_MuRecoSys_corr_MATCHING_SYM_up", ProcessName);
   DefineSysName(19, "recosf_MuRecoSys_corr_TRUTH_SYM_down", ProcessName);
   DefineSysName(20, "recosf_MuRecoSys_corr_TRUTH_SYM_up", ProcessName);
   DefineSysName(21, "recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_down", ProcessName);
   DefineSysName(22, "recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_up", ProcessName);
   DefineSysName(23, "recosf_MuRecoSys_corr_PtDEPENDENCY_down", ProcessName);
   DefineSysName(24, "recosf_MuRecoSys_corr_PtDEPENDENCY_up", ProcessName);
   DefineSysName(25, "recosf_MuRecoSys_uncorr_up", ProcessName);
   DefineSysName(26, "recosf_MuRecoSys_uncorr_down", ProcessName);

   DefineSysName(27, "isosf_MuIsoSys_corr_eta_down", ProcessName);
   DefineSysName(28, "isosf_MuIsoSys_corr_eta_up", ProcessName);
   DefineSysName(29, "isosf_MuIsoSys_corr_mass_down", ProcessName);
   DefineSysName(30, "isosf_MuIsoSys_corr_mass_up", ProcessName);
   DefineSysName(31, "isosf_MuIsoSys_corr_tpdR_down", ProcessName);
   DefineSysName(32, "isosf_MuIsoSys_corr_tpdR_up", ProcessName);
   DefineSysName(33, "isosf_MuIsoSys_corr_isoBkg_down", ProcessName);
   DefineSysName(34, "isosf_MuIsoSys_corr_isoBkg_up", ProcessName);
   DefineSysName(35, "isosf_MuIsoSys_corr_probeQ_down", ProcessName);
   DefineSysName(36, "isosf_MuIsoSys_corr_probeQ_up", ProcessName);
   DefineSysName(37, "isosf_MuIsoSys_corr_tagIsol_down", ProcessName);
   DefineSysName(38, "isosf_MuIsoSys_corr_tagIsol_up", ProcessName);
   DefineSysName(39, "isosf_MuIsoSys_corr_dRmuj_down", ProcessName);
   DefineSysName(40, "isosf_MuIsoSys_corr_dRmuj_up", ProcessName);
   DefineSysName(41, "isosf_MuIsoSys_uncorr_up", ProcessName);
   DefineSysName(42, "isosf_MuIsoSys_uncorr_down", ProcessName);

   DefineSysName(43, "ttvasf_MuTTVASys_corr_QCDTEMPLATE_down", ProcessName);
   DefineSysName(44, "ttvasf_MuTTVASys_corr_QCDTEMPLATE_up", ProcessName);
   DefineSysName(45, "ttvasf_MuTTVASys_corr_LUMIUNCERT_down", ProcessName);
   DefineSysName(46, "ttvasf_MuTTVASys_corr_LUMIUNCERT_up", ProcessName);
   DefineSysName(47, "ttvasf_MuTTVASys_corr_BKGFRACTION_down", ProcessName);
   DefineSysName(48, "ttvasf_MuTTVASys_corr_BKGFRACTION_up", ProcessName);
   DefineSysName(49, "ttvasf_MuTTVASys_corr_MCXSEC_down", ProcessName);
   DefineSysName(50, "ttvasf_MuTTVASys_corr_MCXSEC_up", ProcessName);
   DefineSysName(51, "ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_down", ProcessName);
   DefineSysName(52, "ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_up", ProcessName);
   DefineSysName(53, "ttvasf_MuTTVASys_uncorr_up", ProcessName);
   DefineSysName(54, "ttvasf_MuTTVASys_uncorr_down", ProcessName);

   DefineSysName(55, "trigsf_MuTrigSys_PtEta_corr_iso_loose_avg", ProcessName);
   DefineSysName(56, "trigsf_MuTrigSys_PtEta_corr_dPhi_avg", ProcessName);
   DefineSysName(57, "trigsf_MuTrigSys_PtEta_corr_noIP_avg", ProcessName);
   DefineSysName(58, "trigsf_MuTrigSys_PtEta_corr_iso_tight_avg", ProcessName);
   DefineSysName(59, "trigsf_MuTrigSys_PtEta_corr_mlltight_avg", ProcessName);
   DefineSysName(60, "trigsf_MuTrigSys_PtEta_up", ProcessName);
   DefineSysName(61, "trigsf_MuTrigSys_PtEta_down", ProcessName);

   DefineSysName(62, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN1", ProcessName);
   DefineSysName(63, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP1", ProcessName);
   DefineSysName(64, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN1", ProcessName);
   DefineSysName(65, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP1", ProcessName);
   DefineSysName(66, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN2", ProcessName);
   DefineSysName(67, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP2", ProcessName);
   DefineSysName(68, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN2", ProcessName);
   DefineSysName(69, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP2", ProcessName);
   DefineSysName(70, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN3", ProcessName);
   DefineSysName(71, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP3", ProcessName);
   DefineSysName(72, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN3", ProcessName);
   DefineSysName(73, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP3", ProcessName);
   DefineSysName(74, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN4", ProcessName);
   DefineSysName(75, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP4", ProcessName);
   DefineSysName(76, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN4", ProcessName);
   DefineSysName(77, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP4", ProcessName);
   DefineSysName(78, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN5", ProcessName);
   DefineSysName(79, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP5", ProcessName);
   DefineSysName(80, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN5", ProcessName);
   DefineSysName(81, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP5", ProcessName);
   DefineSysName(82, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN6", ProcessName);
   DefineSysName(83, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP6", ProcessName);
   DefineSysName(84, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN6", ProcessName);
   DefineSysName(85, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP6", ProcessName);
   DefineSysName(86, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN7", ProcessName);
   DefineSysName(87, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP7", ProcessName);
   DefineSysName(88, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN7", ProcessName);
   DefineSysName(89, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP7", ProcessName);
   DefineSysName(90, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN8", ProcessName);
   DefineSysName(91, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP8", ProcessName);
   DefineSysName(92, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN8", ProcessName);
   DefineSysName(93, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP8", ProcessName);
   DefineSysName(94, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN9", ProcessName);
   DefineSysName(95, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP9", ProcessName);
   DefineSysName(96, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN9", ProcessName);
   DefineSysName(97, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP9", ProcessName);
   DefineSysName(98, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN10", ProcessName);
   DefineSysName(99, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP10", ProcessName);
   DefineSysName(100, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN10", ProcessName);
   DefineSysName(101, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP10", ProcessName);
   DefineSysName(102, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN11", ProcessName);
   DefineSysName(103, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP11", ProcessName);
   DefineSysName(104, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN11", ProcessName);
   DefineSysName(105, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP11", ProcessName);
   DefineSysName(106, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN12", ProcessName);
   DefineSysName(107, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP12", ProcessName);
   DefineSysName(108, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN12", ProcessName);
   DefineSysName(109, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP12", ProcessName);
   DefineSysName(110, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN13", ProcessName);
   DefineSysName(111, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP13", ProcessName);
   DefineSysName(112, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN13", ProcessName);
   DefineSysName(113, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP13", ProcessName);
   DefineSysName(114, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN14", ProcessName);
   DefineSysName(115, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP14", ProcessName);
   DefineSysName(116, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN14", ProcessName);
   DefineSysName(117, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP14", ProcessName);

   DefineSysName(118, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_DOWN", ProcessName);
   DefineSysName(119, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_UP", ProcessName);

   DefineSysName(120, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN1", ProcessName);
   DefineSysName(121, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP1", ProcessName);
   DefineSysName(122, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN1", ProcessName);
   DefineSysName(123, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP1", ProcessName);
   DefineSysName(124, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN2", ProcessName);
   DefineSysName(125, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP2", ProcessName);
   DefineSysName(126, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN2", ProcessName);
   DefineSysName(127, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP2", ProcessName);
   DefineSysName(128, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN3", ProcessName);
   DefineSysName(129, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP3", ProcessName);
   DefineSysName(130, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN3", ProcessName);
   DefineSysName(131, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP3", ProcessName);
   DefineSysName(132, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN4", ProcessName);
   DefineSysName(133, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP4", ProcessName);
   DefineSysName(134, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN4", ProcessName);
   DefineSysName(135, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP4", ProcessName);
   DefineSysName(136, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN5", ProcessName);
   DefineSysName(137, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP5", ProcessName);
   DefineSysName(138, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN5", ProcessName);
   DefineSysName(139, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP5", ProcessName);
   DefineSysName(140, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN6", ProcessName);
   DefineSysName(141, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP6", ProcessName);
   DefineSysName(142, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN6", ProcessName);
   DefineSysName(143, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP6", ProcessName);
   DefineSysName(144, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN7", ProcessName);
   DefineSysName(145, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP7", ProcessName);
   DefineSysName(146, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN7", ProcessName);
   DefineSysName(147, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP7", ProcessName);
   DefineSysName(148, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN8", ProcessName);
   DefineSysName(149, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP8", ProcessName);
   DefineSysName(150, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN8", ProcessName);
   DefineSysName(151, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP8", ProcessName);
   DefineSysName(152, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN9", ProcessName);
   DefineSysName(153, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP9", ProcessName);
   DefineSysName(154, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN9", ProcessName);
   DefineSysName(155, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP9", ProcessName);
   DefineSysName(156, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN10", ProcessName);
   DefineSysName(157, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP10", ProcessName);
   DefineSysName(158, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN10", ProcessName);
   DefineSysName(159, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP10", ProcessName);
   DefineSysName(160, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN11", ProcessName);
   DefineSysName(161, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP11", ProcessName);
   DefineSysName(162, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN11", ProcessName);
   DefineSysName(163, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP11", ProcessName);
   DefineSysName(164, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN12", ProcessName);
   DefineSysName(165, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP12", ProcessName);
   DefineSysName(166, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN12", ProcessName);
   DefineSysName(167, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP12", ProcessName);
   DefineSysName(168, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN13", ProcessName);
   DefineSysName(169, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP13", ProcessName);
   DefineSysName(170, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN13", ProcessName);
   DefineSysName(171, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP13", ProcessName);
   DefineSysName(172, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN14", ProcessName);
   DefineSysName(173, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP14", ProcessName);
   DefineSysName(174, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN14", ProcessName);
   DefineSysName(175, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP14", ProcessName);
   DefineSysName(176, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN15", ProcessName);
   DefineSysName(177, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP15", ProcessName);
   DefineSysName(178, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN15", ProcessName);
   DefineSysName(179, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP15", ProcessName);

   DefineSysName(180, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_DOWN", ProcessName);
   DefineSysName(181, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_UP", ProcessName);
   DefineSysName(182, "Recoil_loose_pfoEM_RESPONSE_SYS_DOWN", ProcessName);
   DefineSysName(183, "Recoil_loose_pfoEM_RESPONSE_SYS_UP", ProcessName);
   DefineSysName(184, "Recoil_loose_pfoEM_SET_SYS", ProcessName);

 }
 if(ProcessName == "ZSignal_Electron"){
   DefineSysName(0, "Nominal", ProcessName);
   if(OnlyNominal) return;

   DefineSysName(1, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1down", ProcessName);
   DefineSysName(2, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1up", ProcessName);
   DefineSysName(3, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1down", ProcessName);
   DefineSysName(4, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1up", ProcessName);
   DefineSysName(5, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1down", ProcessName);
   DefineSysName(6, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1up", ProcessName);
   DefineSysName(7, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1down", ProcessName);
   DefineSysName(8, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1up", ProcessName);
   DefineSysName(9, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1down", ProcessName);
   DefineSysName(10, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1up", ProcessName);
   DefineSysName(11, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1down", ProcessName);
   DefineSysName(12, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1up", ProcessName);

   DefineSysName(13, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_down", ProcessName);
   DefineSysName(14, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_up", ProcessName);
   DefineSysName(15, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_down", ProcessName);
   DefineSysName(16, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_up", ProcessName);
   DefineSysName(17, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_down", ProcessName);
   DefineSysName(18, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_up", ProcessName);
   DefineSysName(19, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_down", ProcessName);
   DefineSysName(20, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_up", ProcessName);
   DefineSysName(21, "isosf_ElIsoSys_uncorr_up", ProcessName);
   DefineSysName(22, "isosf_ElIsoSys_uncorr_down", ProcessName);

   DefineSysName(23, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_down", ProcessName);
   DefineSysName(24, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_up", ProcessName);
   DefineSysName(25, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_down", ProcessName);
   DefineSysName(26, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_up", ProcessName);
   DefineSysName(27, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_down", ProcessName);
   DefineSysName(28, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_up", ProcessName);
   DefineSysName(29, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_down", ProcessName);
   DefineSysName(30, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_up", ProcessName);
   DefineSysName(31, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_down", ProcessName);
   DefineSysName(32, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_up", ProcessName);
   DefineSysName(33, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_down", ProcessName);
   DefineSysName(34, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_up", ProcessName);
   DefineSysName(35, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_down", ProcessName);
   DefineSysName(36, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_up", ProcessName);
   DefineSysName(37, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_down", ProcessName);
   DefineSysName(38, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_up", ProcessName);
   DefineSysName(39, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_down", ProcessName);
   DefineSysName(40, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_up", ProcessName);
   DefineSysName(41, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_down", ProcessName);
   DefineSysName(42, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_up", ProcessName);
   DefineSysName(43, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_down", ProcessName);
   DefineSysName(44, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_up", ProcessName);
   DefineSysName(45, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_down", ProcessName);
   DefineSysName(46, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_up", ProcessName);
   DefineSysName(47, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_down", ProcessName);
   DefineSysName(48, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_up", ProcessName);
   DefineSysName(49, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_down", ProcessName);
   DefineSysName(50, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_up", ProcessName);
   DefineSysName(51, "idsf_ElIDSys_uncorr_up", ProcessName);
   DefineSysName(52, "idsf_ElIDSys_uncorr_down", ProcessName);

   DefineSysName(53, "trigsf_ElTrigSys_FullSim_corr8_down", ProcessName);
   DefineSysName(54, "trigsf_ElTrigSys_FullSim_corr8_up", ProcessName);
   DefineSysName(55, "trigsf_ElTrigSys_FullSim_corr9_down", ProcessName);
   DefineSysName(56, "trigsf_ElTrigSys_FullSim_corr9_up", ProcessName);
   DefineSysName(57, "trigsf_ElTrigSys_FullSim_corr10_down", ProcessName);
   DefineSysName(58, "trigsf_ElTrigSys_FullSim_corr10_up", ProcessName);
   DefineSysName(59, "trigsf_ElTrigSys_FullSim_corr11_down", ProcessName);
   DefineSysName(60, "trigsf_ElTrigSys_FullSim_corr11_up", ProcessName);
   DefineSysName(61, "trigsf_ElTrigSys_FullSim_corr12_down", ProcessName);
   DefineSysName(62, "trigsf_ElTrigSys_FullSim_corr12_up", ProcessName);
   DefineSysName(63, "trigsf_ElTrigSys_FullSim_corr13_down", ProcessName);
   DefineSysName(64, "trigsf_ElTrigSys_FullSim_corr13_up", ProcessName);
   DefineSysName(65, "trigsf_ElTrigSys_FullSim_corr14_down", ProcessName);
   DefineSysName(66, "trigsf_ElTrigSys_FullSim_corr14_up", ProcessName);
   DefineSysName(67, "trigsf_ElTrigSys_uncorr_up", ProcessName);
   DefineSysName(68, "trigsf_ElTrigSys_uncorr_down", ProcessName);

   DefineSysName(69, "corrected_pt_scaleDown_NP1", ProcessName);
   DefineSysName(70, "corrected_pt_scaleUp_NP1", ProcessName);
   DefineSysName(71, "corrected_pt_scaleDown_NP2", ProcessName);
   DefineSysName(72, "corrected_pt_scaleUp_NP2", ProcessName);
   DefineSysName(73, "corrected_pt_scaleDown_NP3", ProcessName);
   DefineSysName(74, "corrected_pt_scaleUp_NP3", ProcessName);
   DefineSysName(75, "corrected_pt_scaleDown_NP4", ProcessName);
   DefineSysName(76, "corrected_pt_scaleUp_NP4", ProcessName);
   DefineSysName(77, "corrected_pt_scaleDown_NP5", ProcessName);
   DefineSysName(78, "corrected_pt_scaleUp_NP5", ProcessName);
   DefineSysName(79, "corrected_pt_scaleDown_NP6", ProcessName);
   DefineSysName(80, "corrected_pt_scaleUp_NP6", ProcessName);
   DefineSysName(81, "corrected_pt_scaleDown_NP7", ProcessName);
   DefineSysName(82, "corrected_pt_scaleUp_NP7", ProcessName);
   DefineSysName(83, "corrected_pt_scaleDown_NP8", ProcessName);
   DefineSysName(84, "corrected_pt_scaleUp_NP8", ProcessName);
   DefineSysName(85, "corrected_pt_scaleDown_NP9", ProcessName);
   DefineSysName(86, "corrected_pt_scaleUp_NP9", ProcessName);
   DefineSysName(87, "corrected_pt_scaleDown_NP10", ProcessName);
   DefineSysName(88, "corrected_pt_scaleUp_NP10", ProcessName);
   DefineSysName(89, "corrected_pt_scaleDown_NP11", ProcessName);
   DefineSysName(90, "corrected_pt_scaleUp_NP11", ProcessName);
   DefineSysName(91, "corrected_pt_scaleDown_NP12", ProcessName);
   DefineSysName(92, "corrected_pt_scaleUp_NP12", ProcessName);
   DefineSysName(93, "corrected_pt_scaleDown_NP13", ProcessName);
   DefineSysName(94, "corrected_pt_scaleUp_NP13", ProcessName);
   DefineSysName(95, "corrected_pt_scaleDown_NP14", ProcessName);
   DefineSysName(96, "corrected_pt_scaleUp_NP14", ProcessName);
   DefineSysName(97, "corrected_pt_scaleDown_NP15", ProcessName);
   DefineSysName(98, "corrected_pt_scaleUp_NP15", ProcessName);
   DefineSysName(99, "corrected_pt_scaleDown_NP16", ProcessName);
   DefineSysName(100, "corrected_pt_scaleUp_NP16", ProcessName);
   DefineSysName(101, "corrected_pt_scaleDown_NP17", ProcessName);
   DefineSysName(102, "corrected_pt_scaleUp_NP17", ProcessName);
   DefineSysName(103, "corrected_pt_scaleDown_NP18", ProcessName);
   DefineSysName(104, "corrected_pt_scaleUp_NP18", ProcessName);
   DefineSysName(105, "corrected_pt_scaleDown_NP19", ProcessName);
   DefineSysName(106, "corrected_pt_scaleUp_NP19", ProcessName);
   DefineSysName(107, "corrected_pt_scaleDown_NP20", ProcessName);
   DefineSysName(108, "corrected_pt_scaleUp_NP20", ProcessName);
   DefineSysName(109, "corrected_pt_scaleDown_NP21", ProcessName);
   DefineSysName(110, "corrected_pt_scaleUp_NP21", ProcessName);
   DefineSysName(111, "corrected_pt_scaleDown_NP22", ProcessName);
   DefineSysName(112, "corrected_pt_scaleUp_NP22", ProcessName);
   DefineSysName(113, "corrected_pt_scaleDown_NP23", ProcessName);
   DefineSysName(114, "corrected_pt_scaleUp_NP23", ProcessName);
   DefineSysName(115, "corrected_pt_scaleDown_NP24", ProcessName);
   DefineSysName(116, "corrected_pt_scaleUp_NP24", ProcessName);

   DefineSysName(117, "corrected_pt_cDown_NP1", ProcessName);
   DefineSysName(118, "corrected_pt_cUp_NP1", ProcessName);
   DefineSysName(119, "corrected_pt_cDown_NP2", ProcessName);
   DefineSysName(120, "corrected_pt_cUp_NP2", ProcessName);
   DefineSysName(121, "corrected_pt_cDown_NP3", ProcessName);
   DefineSysName(122, "corrected_pt_cUp_NP3", ProcessName);
   DefineSysName(123, "corrected_pt_cDown_NP4", ProcessName);
   DefineSysName(124, "corrected_pt_cUp_NP4", ProcessName);
   DefineSysName(125, "corrected_pt_cDown_NP5", ProcessName);
   DefineSysName(126, "corrected_pt_cUp_NP5", ProcessName);
   DefineSysName(127, "corrected_pt_cDown_NP6", ProcessName);
   DefineSysName(128, "corrected_pt_cUp_NP6", ProcessName);
   DefineSysName(129, "corrected_pt_cDown_NP7", ProcessName);
   DefineSysName(130, "corrected_pt_cUp_NP7", ProcessName);
   DefineSysName(131, "corrected_pt_cDown_NP8", ProcessName);
   DefineSysName(132, "corrected_pt_cUp_NP8", ProcessName);
   DefineSysName(133, "corrected_pt_cDown_NP9", ProcessName);
   DefineSysName(134, "corrected_pt_cUp_NP9", ProcessName);
   DefineSysName(135, "corrected_pt_cDown_NP10", ProcessName);
   DefineSysName(136, "corrected_pt_cUp_NP10", ProcessName);
   DefineSysName(137, "corrected_pt_cDown_NP11", ProcessName);
   DefineSysName(138, "corrected_pt_cUp_NP11", ProcessName);
   DefineSysName(139, "corrected_pt_cDown_NP12", ProcessName);
   DefineSysName(140, "corrected_pt_cUp_NP12", ProcessName);
   DefineSysName(141, "corrected_pt_cDown_NP13", ProcessName);
   DefineSysName(142, "corrected_pt_cUp_NP13", ProcessName);
   DefineSysName(143, "corrected_pt_cDown_NP14", ProcessName);
   DefineSysName(144, "corrected_pt_cUp_NP14", ProcessName);
   DefineSysName(145, "corrected_pt_cDown_NP15", ProcessName);
   DefineSysName(146, "corrected_pt_cUp_NP15", ProcessName);
   DefineSysName(147, "corrected_pt_cDown_NP16", ProcessName);
   DefineSysName(148, "corrected_pt_cUp_NP16", ProcessName);
   DefineSysName(149, "corrected_pt_cDown_NP17", ProcessName);
   DefineSysName(150, "corrected_pt_cUp_NP17", ProcessName);
   DefineSysName(151, "corrected_pt_cDown_NP18", ProcessName);
   DefineSysName(152, "corrected_pt_cUp_NP18", ProcessName);
   DefineSysName(153, "corrected_pt_cDown_NP19", ProcessName);
   DefineSysName(154, "corrected_pt_cUp_NP19", ProcessName);
   DefineSysName(155, "corrected_pt_cDown_NP20", ProcessName);
   DefineSysName(156, "corrected_pt_cUp_NP20", ProcessName);
   DefineSysName(157, "corrected_pt_cDown_NP21", ProcessName);
   DefineSysName(158, "corrected_pt_cUp_NP21", ProcessName);
   DefineSysName(159, "corrected_pt_cDown_NP22", ProcessName);
   DefineSysName(160, "corrected_pt_cUp_NP22", ProcessName);
   DefineSysName(161, "corrected_pt_cDown_NP23", ProcessName);
   DefineSysName(162, "corrected_pt_cUp_NP23", ProcessName);
   DefineSysName(163, "corrected_pt_cDown_NP24", ProcessName);
   DefineSysName(164, "corrected_pt_cUp_NP24", ProcessName);

   DefineSysName(165, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN1", ProcessName);
   DefineSysName(166, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP1", ProcessName);
   DefineSysName(167, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN1", ProcessName);
   DefineSysName(168, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP1", ProcessName);
   DefineSysName(169, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN2", ProcessName);
   DefineSysName(170, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP2", ProcessName);
   DefineSysName(171, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN2", ProcessName);
   DefineSysName(172, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP2", ProcessName);
   DefineSysName(173, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN3", ProcessName);
   DefineSysName(174, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP3", ProcessName);
   DefineSysName(175, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN3", ProcessName);
   DefineSysName(176, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP3", ProcessName);
   DefineSysName(177, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN4", ProcessName);
   DefineSysName(178, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP4", ProcessName);
   DefineSysName(179, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN4", ProcessName);
   DefineSysName(180, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP4", ProcessName);
   DefineSysName(181, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN5", ProcessName);
   DefineSysName(182, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP5", ProcessName);
   DefineSysName(183, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN5", ProcessName);
   DefineSysName(184, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP5", ProcessName);
   DefineSysName(185, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN6", ProcessName);
   DefineSysName(186, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP6", ProcessName);
   DefineSysName(187, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN6", ProcessName);
   DefineSysName(188, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP6", ProcessName);
   DefineSysName(189, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN7", ProcessName);
   DefineSysName(190, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP7", ProcessName);
   DefineSysName(191, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN7", ProcessName);
   DefineSysName(192, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP7", ProcessName);
   DefineSysName(193, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN8", ProcessName);
   DefineSysName(194, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP8", ProcessName);
   DefineSysName(195, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN8", ProcessName);
   DefineSysName(196, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP8", ProcessName);
   DefineSysName(197, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN9", ProcessName);
   DefineSysName(198, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP9", ProcessName);
   DefineSysName(199, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN9", ProcessName);
   DefineSysName(200, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP9", ProcessName);
   DefineSysName(201, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN10", ProcessName);
   DefineSysName(202, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP10", ProcessName);
   DefineSysName(203, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN10", ProcessName);
   DefineSysName(204, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP10", ProcessName);
   DefineSysName(205, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN11", ProcessName);
   DefineSysName(206, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP11", ProcessName);
   DefineSysName(207, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN11", ProcessName);
   DefineSysName(208, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP11", ProcessName);
   DefineSysName(209, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN12", ProcessName);
   DefineSysName(210, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP12", ProcessName);
   DefineSysName(211, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN12", ProcessName);
   DefineSysName(212, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP12", ProcessName);
   DefineSysName(213, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN13", ProcessName);
   DefineSysName(214, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP13", ProcessName);
   DefineSysName(215, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN13", ProcessName);
   DefineSysName(216, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP13", ProcessName);
   DefineSysName(217, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN14", ProcessName);
   DefineSysName(218, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP14", ProcessName);
   DefineSysName(219, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN14", ProcessName);
   DefineSysName(220, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP14", ProcessName);

   DefineSysName(220, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_DOWN", ProcessName);
   DefineSysName(221, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_UP", ProcessName);

   DefineSysName(222, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN1", ProcessName);
   DefineSysName(223, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP1", ProcessName);
   DefineSysName(224, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN1", ProcessName);
   DefineSysName(225, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP1", ProcessName);
   DefineSysName(226, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN2", ProcessName);
   DefineSysName(227, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP2", ProcessName);
   DefineSysName(228, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN2", ProcessName);
   DefineSysName(229, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP2", ProcessName);
   DefineSysName(230, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN3", ProcessName);
   DefineSysName(231, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP3", ProcessName);
   DefineSysName(232, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN3", ProcessName);
   DefineSysName(233, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP3", ProcessName);
   DefineSysName(234, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN4", ProcessName);
   DefineSysName(235, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP4", ProcessName);
   DefineSysName(236, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN4", ProcessName);
   DefineSysName(237, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP4", ProcessName);
   DefineSysName(238, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN5", ProcessName);
   DefineSysName(239, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP5", ProcessName);
   DefineSysName(240, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN5", ProcessName);
   DefineSysName(241, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP5", ProcessName);
   DefineSysName(242, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN6", ProcessName);
   DefineSysName(243, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP6", ProcessName);
   DefineSysName(244, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN6", ProcessName);
   DefineSysName(245, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP6", ProcessName);
   DefineSysName(246, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN7", ProcessName);
   DefineSysName(247, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP7", ProcessName);
   DefineSysName(248, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN7", ProcessName);
   DefineSysName(249, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP7", ProcessName);
   DefineSysName(250, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN8", ProcessName);
   DefineSysName(251, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP8", ProcessName);
   DefineSysName(252, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN8", ProcessName);
   DefineSysName(253, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP8", ProcessName);
   DefineSysName(254, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN9", ProcessName);
   DefineSysName(255, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP9", ProcessName);
   DefineSysName(256, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN9", ProcessName);
   DefineSysName(257, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP9", ProcessName);
   DefineSysName(258, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN10", ProcessName);
   DefineSysName(259, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP10", ProcessName);
   DefineSysName(260, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN10", ProcessName);
   DefineSysName(261, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP10", ProcessName);
   DefineSysName(262, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN11", ProcessName);
   DefineSysName(263, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP11", ProcessName);
   DefineSysName(264, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN11", ProcessName);
   DefineSysName(265, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP11", ProcessName);
   DefineSysName(266, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN12", ProcessName);
   DefineSysName(267, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP12", ProcessName);
   DefineSysName(268, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN12", ProcessName);
   DefineSysName(269, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP12", ProcessName);
   DefineSysName(270, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN13", ProcessName);
   DefineSysName(271, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP13", ProcessName);
   DefineSysName(272, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN13", ProcessName);
   DefineSysName(273, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP13", ProcessName);
   DefineSysName(274, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN14", ProcessName);
   DefineSysName(275, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP14", ProcessName);
   DefineSysName(276, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN14", ProcessName);
   DefineSysName(277, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP14", ProcessName);
   DefineSysName(278, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN15", ProcessName);
   DefineSysName(279, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP15", ProcessName);
   DefineSysName(280, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN15", ProcessName);
   DefineSysName(281, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP15", ProcessName);

   DefineSysName(282, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_DOWN", ProcessName);
   DefineSysName(283, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_UP", ProcessName);
   DefineSysName(284, "Recoil_loose_pfoEM_RESPONSE_SYS_DOWN", ProcessName);
   DefineSysName(285, "Recoil_loose_pfoEM_RESPONSE_SYS_UP", ProcessName);
   DefineSysName(286, "Recoil_loose_pfoEM_SET_SYS", ProcessName);

 }
 if(ProcessName == "ZSignal_Muon"){
   DefineSysName(0, "Nominal", ProcessName);
   if(OnlyNominal) return;

   DefineSysName(1, "syspt_MUON_ID__1down", ProcessName);
   DefineSysName(2, "syspt_MUON_ID__1up", ProcessName);
   DefineSysName(3, "syspt_MUON_MS__1down", ProcessName);
   DefineSysName(4, "syspt_MUON_MS__1up", ProcessName);
   DefineSysName(5, "syspt_MUON_SCALE__1down", ProcessName);
   DefineSysName(6, "syspt_MUON_SCALE__1up", ProcessName);

   DefineSysName(7, "recosf_MuRecoSys_corr_QCDTEMPLATE_down", ProcessName);
   DefineSysName(8, "recosf_MuRecoSys_corr_QCDTEMPLATE_up", ProcessName);
   DefineSysName(9, "recosf_MuRecoSys_corr_BKGFRACTION_down", ProcessName);
   DefineSysName(10, "recosf_MuRecoSys_corr_BKGFRACTION_up", ProcessName);
   DefineSysName(11, "recosf_MuRecoSys_corr_LUMIUNCERT_down", ProcessName);
   DefineSysName(12, "recosf_MuRecoSys_corr_LUMIUNCERT_up", ProcessName);
   DefineSysName(13, "recosf_MuRecoSys_corr_MCXSEC_down", ProcessName);
   DefineSysName(14, "recosf_MuRecoSys_corr_MCXSEC_up", ProcessName);
   DefineSysName(15, "recosf_MuRecoSys_corr_SUPRESSIONSCALE_down", ProcessName);
   DefineSysName(16, "recosf_MuRecoSys_corr_SUPRESSIONSCALE_up", ProcessName);
   DefineSysName(17, "recosf_MuRecoSys_corr_MATCHING_SYM_down", ProcessName);
   DefineSysName(18, "recosf_MuRecoSys_corr_MATCHING_SYM_up", ProcessName);
   DefineSysName(19, "recosf_MuRecoSys_corr_TRUTH_SYM_down", ProcessName);
   DefineSysName(20, "recosf_MuRecoSys_corr_TRUTH_SYM_up", ProcessName);
   DefineSysName(21, "recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_down", ProcessName);
   DefineSysName(22, "recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_up", ProcessName);
   DefineSysName(23, "recosf_MuRecoSys_corr_PtDEPENDENCY_down", ProcessName);
   DefineSysName(24, "recosf_MuRecoSys_corr_PtDEPENDENCY_up", ProcessName);
   DefineSysName(25, "recosf_MuRecoSys_uncorr_up", ProcessName);
   DefineSysName(26, "recosf_MuRecoSys_uncorr_down", ProcessName);

   DefineSysName(27, "isosf_MuIsoSys_corr_eta_down", ProcessName);
   DefineSysName(28, "isosf_MuIsoSys_corr_eta_up", ProcessName);
   DefineSysName(29, "isosf_MuIsoSys_corr_mass_down", ProcessName);
   DefineSysName(30, "isosf_MuIsoSys_corr_mass_up", ProcessName);
   DefineSysName(31, "isosf_MuIsoSys_corr_tpdR_down", ProcessName);
   DefineSysName(32, "isosf_MuIsoSys_corr_tpdR_up", ProcessName);
   DefineSysName(33, "isosf_MuIsoSys_corr_isoBkg_down", ProcessName);
   DefineSysName(34, "isosf_MuIsoSys_corr_isoBkg_up", ProcessName);
   DefineSysName(35, "isosf_MuIsoSys_corr_probeQ_down", ProcessName);
   DefineSysName(36, "isosf_MuIsoSys_corr_probeQ_up", ProcessName);
   DefineSysName(37, "isosf_MuIsoSys_corr_tagIsol_down", ProcessName);
   DefineSysName(38, "isosf_MuIsoSys_corr_tagIsol_up", ProcessName);
   DefineSysName(39, "isosf_MuIsoSys_corr_dRmuj_down", ProcessName);
   DefineSysName(40, "isosf_MuIsoSys_corr_dRmuj_up", ProcessName);
   DefineSysName(41, "isosf_MuIsoSys_uncorr_up", ProcessName);
   DefineSysName(42, "isosf_MuIsoSys_uncorr_down", ProcessName);

   DefineSysName(43, "ttvasf_MuTTVASys_corr_QCDTEMPLATE_down", ProcessName);
   DefineSysName(44, "ttvasf_MuTTVASys_corr_QCDTEMPLATE_up", ProcessName);
   DefineSysName(45, "ttvasf_MuTTVASys_corr_LUMIUNCERT_down", ProcessName);
   DefineSysName(46, "ttvasf_MuTTVASys_corr_LUMIUNCERT_up", ProcessName);
   DefineSysName(47, "ttvasf_MuTTVASys_corr_BKGFRACTION_down", ProcessName);
   DefineSysName(48, "ttvasf_MuTTVASys_corr_BKGFRACTION_up", ProcessName);
   DefineSysName(49, "ttvasf_MuTTVASys_corr_MCXSEC_down", ProcessName);
   DefineSysName(50, "ttvasf_MuTTVASys_corr_MCXSEC_up", ProcessName);
   DefineSysName(51, "ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_down", ProcessName);
   DefineSysName(52, "ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_up", ProcessName);
   DefineSysName(53, "ttvasf_MuTTVASys_uncorr_up", ProcessName);
   DefineSysName(54, "ttvasf_MuTTVASys_uncorr_down", ProcessName);

   DefineSysName(55, "trigsf_MuTrigSys_PtEta_corr_iso_loose_avg", ProcessName);
   DefineSysName(56, "trigsf_MuTrigSys_PtEta_corr_dPhi_avg", ProcessName);
   DefineSysName(57, "trigsf_MuTrigSys_PtEta_corr_noIP_avg", ProcessName);
   DefineSysName(58, "trigsf_MuTrigSys_PtEta_corr_iso_tight_avg", ProcessName);
   DefineSysName(59, "trigsf_MuTrigSys_PtEta_corr_mlltight_avg", ProcessName);
   DefineSysName(60, "trigsf_MuTrigSys_PtEta_up", ProcessName);
   DefineSysName(61, "trigsf_MuTrigSys_PtEta_down", ProcessName);

   DefineSysName(62, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN1", ProcessName);
   DefineSysName(63, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP1", ProcessName);
   DefineSysName(64, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN1", ProcessName);
   DefineSysName(65, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP1", ProcessName);
   DefineSysName(66, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN2", ProcessName);
   DefineSysName(67, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP2", ProcessName);
   DefineSysName(68, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN2", ProcessName);
   DefineSysName(69, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP2", ProcessName);
   DefineSysName(70, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN3", ProcessName);
   DefineSysName(71, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP3", ProcessName);
   DefineSysName(72, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN3", ProcessName);
   DefineSysName(73, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP3", ProcessName);
   DefineSysName(74, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN4", ProcessName);
   DefineSysName(75, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP4", ProcessName);
   DefineSysName(76, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN4", ProcessName);
   DefineSysName(77, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP4", ProcessName);
   DefineSysName(78, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN5", ProcessName);
   DefineSysName(79, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP5", ProcessName);
   DefineSysName(80, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN5", ProcessName);
   DefineSysName(81, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP5", ProcessName);
   DefineSysName(82, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN6", ProcessName);
   DefineSysName(83, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP6", ProcessName);
   DefineSysName(84, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN6", ProcessName);
   DefineSysName(85, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP6", ProcessName);
   DefineSysName(86, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN7", ProcessName);
   DefineSysName(87, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP7", ProcessName);
   DefineSysName(88, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN7", ProcessName);
   DefineSysName(89, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP7", ProcessName);
   DefineSysName(90, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN8", ProcessName);
   DefineSysName(91, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP8", ProcessName);
   DefineSysName(92, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN8", ProcessName);
   DefineSysName(93, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP8", ProcessName);
   DefineSysName(94, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN9", ProcessName);
   DefineSysName(95, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP9", ProcessName);
   DefineSysName(96, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN9", ProcessName);
   DefineSysName(97, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP9", ProcessName);
   DefineSysName(98, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN10", ProcessName);
   DefineSysName(99, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP10", ProcessName);
   DefineSysName(100, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN10", ProcessName);
   DefineSysName(101, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP10", ProcessName);
   DefineSysName(102, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN11", ProcessName);
   DefineSysName(103, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP11", ProcessName);
   DefineSysName(104, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN11", ProcessName);
   DefineSysName(105, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP11", ProcessName);
   DefineSysName(106, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN12", ProcessName);
   DefineSysName(107, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP12", ProcessName);
   DefineSysName(108, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN12", ProcessName);
   DefineSysName(109, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP12", ProcessName);
   DefineSysName(110, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN13", ProcessName);
   DefineSysName(111, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP13", ProcessName);
   DefineSysName(112, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN13", ProcessName);
   DefineSysName(113, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP13", ProcessName);
   DefineSysName(114, "Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN14", ProcessName);
   DefineSysName(115, "Recoil_loose_pfoEM_RESOLUTION_STAT0_UP14", ProcessName);
   DefineSysName(116, "Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN14", ProcessName);
   DefineSysName(117, "Recoil_loose_pfoEM_RESOLUTION_STAT1_UP14", ProcessName);

   DefineSysName(118, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_DOWN", ProcessName);
   DefineSysName(119, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_UP", ProcessName);

   DefineSysName(120, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN1", ProcessName);
   DefineSysName(121, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP1", ProcessName);
   DefineSysName(122, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN1", ProcessName);
   DefineSysName(123, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP1", ProcessName);
   DefineSysName(124, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN2", ProcessName);
   DefineSysName(125, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP2", ProcessName);
   DefineSysName(126, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN2", ProcessName);
   DefineSysName(127, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP2", ProcessName);
   DefineSysName(128, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN3", ProcessName);
   DefineSysName(129, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP3", ProcessName);
   DefineSysName(130, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN3", ProcessName);
   DefineSysName(131, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP3", ProcessName);
   DefineSysName(132, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN4", ProcessName);
   DefineSysName(133, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP4", ProcessName);
   DefineSysName(134, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN4", ProcessName);
   DefineSysName(135, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP4", ProcessName);
   DefineSysName(136, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN5", ProcessName);
   DefineSysName(137, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP5", ProcessName);
   DefineSysName(138, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN5", ProcessName);
   DefineSysName(139, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP5", ProcessName);
   DefineSysName(140, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN6", ProcessName);
   DefineSysName(141, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP6", ProcessName);
   DefineSysName(142, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN6", ProcessName);
   DefineSysName(143, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP6", ProcessName);
   DefineSysName(144, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN7", ProcessName);
   DefineSysName(145, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP7", ProcessName);
   DefineSysName(146, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN7", ProcessName);
   DefineSysName(147, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP7", ProcessName);
   DefineSysName(148, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN8", ProcessName);
   DefineSysName(149, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP8", ProcessName);
   DefineSysName(150, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN8", ProcessName);
   DefineSysName(151, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP8", ProcessName);
   DefineSysName(152, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN9", ProcessName);
   DefineSysName(153, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP9", ProcessName);
   DefineSysName(154, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN9", ProcessName);
   DefineSysName(155, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP9", ProcessName);
   DefineSysName(156, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN10", ProcessName);
   DefineSysName(157, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP10", ProcessName);
   DefineSysName(158, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN10", ProcessName);
   DefineSysName(159, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP10", ProcessName);
   DefineSysName(160, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN11", ProcessName);
   DefineSysName(161, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP11", ProcessName);
   DefineSysName(162, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN11", ProcessName);
   DefineSysName(163, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP11", ProcessName);
   DefineSysName(164, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN12", ProcessName);
   DefineSysName(165, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP12", ProcessName);
   DefineSysName(166, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN12", ProcessName);
   DefineSysName(167, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP12", ProcessName);
   DefineSysName(168, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN13", ProcessName);
   DefineSysName(169, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP13", ProcessName);
   DefineSysName(170, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN13", ProcessName);
   DefineSysName(171, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP13", ProcessName);
   DefineSysName(172, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN14", ProcessName);
   DefineSysName(173, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP14", ProcessName);
   DefineSysName(174, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN14", ProcessName);
   DefineSysName(175, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP14", ProcessName);
   DefineSysName(176, "Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN15", ProcessName);
   DefineSysName(177, "Recoil_loose_pfoEM_RESPONSE_STAT0_UP15", ProcessName);
   DefineSysName(178, "Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN15", ProcessName);
   DefineSysName(179, "Recoil_loose_pfoEM_RESPONSE_STAT1_UP15", ProcessName);

   DefineSysName(180, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_DOWN", ProcessName);
   DefineSysName(181, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_UP", ProcessName);
   DefineSysName(182, "Recoil_loose_pfoEM_RESPONSE_SYS_DOWN", ProcessName);
   DefineSysName(183, "Recoil_loose_pfoEM_RESPONSE_SYS_UP", ProcessName);
   DefineSysName(184, "Recoil_loose_pfoEM_SET_SYS", ProcessName);

 }


}
