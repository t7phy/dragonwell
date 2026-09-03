//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Mar 15 17:10:30 2020 by ROOT version 6.18/02
// from TTree Tree/Low mu run data and MC
// found on file: /Data/chenw/LowMu_Data/Data17_Part1.root
//////////////////////////////////////////////////////////

#ifndef TreeForWasym_h
#define TreeForWasym_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class TreeForWasym
{
 public:

   TFile *rootfile[1000];
   TTree *fChain[1000];
   int TotalEntries[1000];

   vector<TString> RootNames;

   vector<int> RootTypes;
   vector<double> CrossSections;
   vector<double> SumOfWeights;
   int nchannel;
   double CrossSection;
   double SumOfWeight;

   int FirstFile, EndFile;
   bool OneFilePerJob = false;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         EventWeight_gen;
   Float_t         EventWeight_pu;
   Float_t         EventWeight_vertex;
   Float_t         RunNumber;
   Float_t         EvtNumber;
   Float_t         vxp_z0;
   Float_t         npv;
   UInt_t          nTracksPV;
   Float_t         nintime;
   Float_t         bcid;
   Float_t         lbn;
   Float_t         actual_mu;
   UInt_t          mcChannelNumber;
   UInt_t          nHadPart;
   UInt_t          nHadChargedPart;
   Float_t         sumPtHadPart;
   Float_t         sumPtChargedPart;
   Bool_t          passTrigger_el;
   Bool_t          passTrigger_mu;
   vector<float>   *jet_pt;
   vector<float>   *jet_eta;
   vector<float>   *jet_phi;
   vector<float>   *mu_pt;
   vector<float>   *mu_eta;
   vector<float>   *mu_phi;
   vector<float>   *mu_charge;
   vector<float>   *mu_d0sig;
   vector<float>   *mu_delta_z0;
   vector<bool>    *mu_isTight;
   vector<bool>    *mu_trigMatch;
   vector<bool>    *mu_inrecoil;
   vector<float>   *mu_isolation_ptcone20;
   vector<float>   *mu_isolation_ptvarcone20;
   vector<float>   *mu_isolation_ptvarcone30;
   vector<float>   *mu_isolation_ptvarcone40;
   vector<float>   *mu_isolation_topoetcone20;
   vector<float>   *mu_isolation_topoetcone30;
   vector<float>   *mu_isolation_topoetcone40;
   vector<bool>    *mu_isIsolated;
   vector<float>   *mu_corrected_pt;
   vector<float>   *mu_recosf;
   vector<float>   *mu_recomceff;
   vector<float>   *mu_isosf;
   vector<float>   *mu_isomceff;
   vector<float>   *mu_ttvasf;
   vector<float>   *mu_ttvamceff;
   vector<float>   *mu_trigsf;
   vector<float>   *mu_trigmceff;
   vector<float>   *mu_syspt_MUON_ID__1down;
   vector<float>   *mu_syspt_MUON_ID__1up;
   vector<float>   *mu_syspt_MUON_MS__1down;
   vector<float>   *mu_syspt_MUON_MS__1up;
   vector<float>   *mu_syspt_MUON_SAGITTA_RESBIAS__1down;
   vector<float>   *mu_syspt_MUON_SAGITTA_RESBIAS__1up;
   vector<float>   *mu_syspt_MUON_SAGITTA_RHO__1down;
   vector<float>   *mu_syspt_MUON_SAGITTA_RHO__1up;
   vector<float>   *mu_syspt_MUON_SCALE__1down;
   vector<float>   *mu_syspt_MUON_SCALE__1up;
   vector<float>   *mu_recosf_MuRecoSys_uncorr_up;
   vector<float>   *mu_recosf_MuRecoSys_uncorr_down;
   vector<int>     *mu_recosf_MuRecoSys_uncorr_BinNumber;
   UInt_t          mu_recosf_MuRecoSys_uncorr_MaxBinNumber;
   vector<float>   *mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down;
   vector<float>   *mu_recosf_MuRecoSys_corr_BKGFRACTION_down;
   vector<float>   *mu_recosf_MuRecoSys_corr_LUMIUNCERT_down;
   vector<float>   *mu_recosf_MuRecoSys_corr_MCXSEC_down;
   vector<float>   *mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_down;
   vector<float>   *mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up;
   vector<float>   *mu_recosf_MuRecoSys_corr_BKGFRACTION_up;
   vector<float>   *mu_recosf_MuRecoSys_corr_LUMIUNCERT_up;
   vector<float>   *mu_recosf_MuRecoSys_corr_MCXSEC_up;
   vector<float>   *mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_up;
   vector<float>   *mu_recosf_MuRecoSys_corr_MATCHING_SYM_up;
   vector<float>   *mu_recosf_MuRecoSys_corr_TRUTH_SYM_up;
   vector<float>   *mu_recosf_MuRecoSys_corr_MATCHING_SYM_down;
   vector<float>   *mu_recosf_MuRecoSys_corr_TRUTH_SYM_down;
   vector<float>   *mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_up;
   vector<float>   *mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_down;
   vector<float>   *mu_recosf_MuRecoSys_corr_PtDEPENDENCY_up;
   vector<float>   *mu_recosf_MuRecoSys_corr_PtDEPENDENCY_down;
   vector<float>   *mu_isosf_MuIsoSys_uncorr_up;
   vector<float>   *mu_isosf_MuIsoSys_uncorr_down;
   vector<int>     *mu_isosf_MuIsoSys_uncorr_BinNumber;
   UInt_t          mu_isosf_MuIsoSys_uncorr_MaxBinNumber;
   vector<float>   *mu_isosf_MuIsoSys_corr_eta_up;
   vector<float>   *mu_isosf_MuIsoSys_corr_eta_down;
   vector<float>   *mu_isosf_MuIsoSys_corr_mass_up;
   vector<float>   *mu_isosf_MuIsoSys_corr_mass_down;
   vector<float>   *mu_isosf_MuIsoSys_corr_tpdR_up;
   vector<float>   *mu_isosf_MuIsoSys_corr_tpdR_down;
   vector<float>   *mu_isosf_MuIsoSys_corr_isoBkg_up;
   vector<float>   *mu_isosf_MuIsoSys_corr_isoBkg_down;
   vector<float>   *mu_isosf_MuIsoSys_corr_probeQ_up;
   vector<float>   *mu_isosf_MuIsoSys_corr_probeQ_down;
   vector<float>   *mu_isosf_MuIsoSys_corr_tagIsol_up;
   vector<float>   *mu_isosf_MuIsoSys_corr_tagIsol_down;
   vector<float>   *mu_isosf_MuIsoSys_corr_dRmuj_up;
   vector<float>   *mu_isosf_MuIsoSys_corr_dRmuj_down;
   vector<float>   *mu_ttvasf_MuTTVASys_uncorr_up;
   vector<float>   *mu_ttvasf_MuTTVASys_uncorr_down;
   vector<int>     *mu_ttvasf_MuTTVASys_uncorr_BinNumber;
   UInt_t          mu_ttvasf_MuTTVASys_uncorr_MaxBinNumber;
   vector<float>   *mu_ttvasf_MuTTVASys_corr_QCDTEMPLATE_down;
   vector<float>   *mu_ttvasf_MuTTVASys_corr_LUMIUNCERT_down;
   vector<float>   *mu_ttvasf_MuTTVASys_corr_BKGFRACTION_down;
   vector<float>   *mu_ttvasf_MuTTVASys_corr_MCXSEC_down;
   vector<float>   *mu_ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_down;
   vector<float>   *mu_ttvasf_MuTTVASys_corr_QCDTEMPLATE_up;
   vector<float>   *mu_ttvasf_MuTTVASys_corr_LUMIUNCERT_up;
   vector<float>   *mu_ttvasf_MuTTVASys_corr_BKGFRACTION_up;
   vector<float>   *mu_ttvasf_MuTTVASys_corr_MCXSEC_up;
   vector<float>   *mu_ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_up;
   vector<float>   *mu_trigsf_MuTrigSys_PtEta_up;
   vector<float>   *mu_trigsf_MuTrigSys_PtEta_down;
   vector<int>     *mu_trigsf_MuTrigSys_PtEta_uncorr_BinNumber;
   UInt_t          mu_trigsf_MuTrigSys_PtEta_uncorr_MaxBinNumber;
   vector<float>   *mu_trigsf_MuTrigSys_PtEta_corr_iso_loose_avg;
   vector<float>   *mu_trigsf_MuTrigSys_PtEta_corr_dPhi_avg;
   vector<float>   *mu_trigsf_MuTrigSys_PtEta_corr_noIP_avg;
   vector<float>   *mu_trigsf_MuTrigSys_PtEta_corr_iso_tight_avg;
   vector<float>   *mu_trigsf_MuTrigSys_PtEta_corr_mlltight_avg;
   vector<float>   *el_pt;
   vector<float>   *el_eta;
   vector<float>   *el_phi;
   vector<float>   *el_qOverP;
   vector<float>   *el_charge;
   vector<float>   *el_d0sig;
   vector<float>   *el_delta_z0;
   vector<bool>    *el_isTight;
   vector<bool>    *el_isMedium;
   vector<bool>    *el_trigMatch;
   vector<bool>    *el_inrecoil;
   vector<bool>    *el_inrecoil_loose;
   vector<bool>    *el_inrecoil_medium;
   vector<float>   *el_isolation_ptcone20;
   vector<float>   *el_isolation_ptvarcone20;
   vector<float>   *el_isolation_ptvarcone30;
   vector<float>   *el_isolation_ptvarcone40;
   vector<float>   *el_isolation_topoetcone20;
   vector<float>   *el_isolation_topoetcone20ptCorrection;
   vector<float>   *el_isolation_topoetcone30;
   vector<float>   *el_isolation_topoetcone30ptCorrection;
   vector<float>   *el_isolation_topoetcone40;
   vector<float>   *el_isolation_topoetcone40ptCorrection;
   vector<bool>    *el_isIsolated;
   vector<float>   *el_corrected_pt;
   vector<float>   *el_recosf;
   vector<float>   *el_recomceff;
   vector<float>   *el_isosf;
   vector<float>   *el_isomceff;
   vector<float>   *el_idsf;
   vector<float>   *el_idmceff;
   vector<float>   *el_trigsf;
   vector<float>   *el_trigmceff;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1down;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1up;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1down;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1up;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1down;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1up;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1down;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1up;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1down;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1up;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1down;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1up;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_FULL_UncorrUncertaintyNP33__1down;
   vector<float>   *el_sysrecosf_EL_EFF_Reco_FULL_UncorrUncertaintyNP33__1up;
   vector<float>   *el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_up;
   vector<float>   *el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_down;
   vector<float>   *el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_up;
   vector<float>   *el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_down;
   vector<float>   *el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_up;
   vector<float>   *el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_down;
   vector<float>   *el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_up;
   vector<float>   *el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_down;
   vector<float>   *el_isosf_ElIsoSys_uncorr_up;
   vector<float>   *el_isosf_ElIsoSys_uncorr_down;
   vector<int>     *el_isosf_ElIsoSys_uncorr_BinNumber;
   UInt_t          el_isosf_ElIsoSys_uncorr_MaxBinNumber;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_down;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_up;
   vector<float>   *el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_down;
   vector<float>   *el_idsf_ElIDSys_uncorr_up;
   vector<float>   *el_idsf_ElIDSys_uncorr_down;
   vector<int>     *el_idsf_ElIDSys_uncorr_BinNumber;
   UInt_t          el_idsf_ElIDSys_uncorr_MaxBinNumber;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr10_up;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr10_down;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr11_up;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr11_down;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr12_up;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr12_down;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr13_up;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr13_down;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr14_up;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr14_down;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr8_up;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr8_down;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr9_up;
   vector<float>   *el_trigsf_ElTrigSys_FullSim_corr9_down;
   vector<float>   *el_trigsf_ElTrigSys_uncorr_up;
   vector<float>   *el_trigsf_ElTrigSys_uncorr_down;
   vector<int>     *el_trigsf_ElTrigSys_uncorr_BinNumber;
   UInt_t          el_trigsf_ElTrigSys_uncorr_MaxBinNumber;
   vector<float>   *el_corrected_pt_scaleUp_NP1;
   vector<float>   *el_corrected_pt_scaleUp_NP2;
   vector<float>   *el_corrected_pt_scaleUp_NP3;
   vector<float>   *el_corrected_pt_scaleUp_NP4;
   vector<float>   *el_corrected_pt_scaleUp_NP5;
   vector<float>   *el_corrected_pt_scaleUp_NP6;
   vector<float>   *el_corrected_pt_scaleUp_NP7;
   vector<float>   *el_corrected_pt_scaleUp_NP8;
   vector<float>   *el_corrected_pt_scaleUp_NP9;
   vector<float>   *el_corrected_pt_scaleUp_NP10;
   vector<float>   *el_corrected_pt_scaleUp_NP11;
   vector<float>   *el_corrected_pt_scaleUp_NP12;
   vector<float>   *el_corrected_pt_scaleUp_NP13;
   vector<float>   *el_corrected_pt_scaleUp_NP14;
   vector<float>   *el_corrected_pt_scaleUp_NP15;
   vector<float>   *el_corrected_pt_scaleUp_NP16;
   vector<float>   *el_corrected_pt_scaleUp_NP17;
   vector<float>   *el_corrected_pt_scaleUp_NP18;
   vector<float>   *el_corrected_pt_scaleUp_NP19;
   vector<float>   *el_corrected_pt_scaleUp_NP20;
   vector<float>   *el_corrected_pt_scaleUp_NP21;
   vector<float>   *el_corrected_pt_scaleUp_NP22;
   vector<float>   *el_corrected_pt_scaleUp_NP23;
   vector<float>   *el_corrected_pt_scaleUp_NP24;
   vector<float>   *el_corrected_pt_scaleDown_NP1;
   vector<float>   *el_corrected_pt_scaleDown_NP2;
   vector<float>   *el_corrected_pt_scaleDown_NP3;
   vector<float>   *el_corrected_pt_scaleDown_NP4;
   vector<float>   *el_corrected_pt_scaleDown_NP5;
   vector<float>   *el_corrected_pt_scaleDown_NP6;
   vector<float>   *el_corrected_pt_scaleDown_NP7;
   vector<float>   *el_corrected_pt_scaleDown_NP8;
   vector<float>   *el_corrected_pt_scaleDown_NP9;
   vector<float>   *el_corrected_pt_scaleDown_NP10;
   vector<float>   *el_corrected_pt_scaleDown_NP11;
   vector<float>   *el_corrected_pt_scaleDown_NP12;
   vector<float>   *el_corrected_pt_scaleDown_NP13;
   vector<float>   *el_corrected_pt_scaleDown_NP14;
   vector<float>   *el_corrected_pt_scaleDown_NP15;
   vector<float>   *el_corrected_pt_scaleDown_NP16;
   vector<float>   *el_corrected_pt_scaleDown_NP17;
   vector<float>   *el_corrected_pt_scaleDown_NP18;
   vector<float>   *el_corrected_pt_scaleDown_NP19;
   vector<float>   *el_corrected_pt_scaleDown_NP20;
   vector<float>   *el_corrected_pt_scaleDown_NP21;
   vector<float>   *el_corrected_pt_scaleDown_NP22;
   vector<float>   *el_corrected_pt_scaleDown_NP23;
   vector<float>   *el_corrected_pt_scaleDown_NP24;
   vector<float>   *el_corrected_pt_cUp_NP1;
   vector<float>   *el_corrected_pt_cUp_NP2;
   vector<float>   *el_corrected_pt_cUp_NP3;
   vector<float>   *el_corrected_pt_cUp_NP4;
   vector<float>   *el_corrected_pt_cUp_NP5;
   vector<float>   *el_corrected_pt_cUp_NP6;
   vector<float>   *el_corrected_pt_cUp_NP7;
   vector<float>   *el_corrected_pt_cUp_NP8;
   vector<float>   *el_corrected_pt_cUp_NP9;
   vector<float>   *el_corrected_pt_cUp_NP10;
   vector<float>   *el_corrected_pt_cUp_NP11;
   vector<float>   *el_corrected_pt_cUp_NP12;
   vector<float>   *el_corrected_pt_cUp_NP13;
   vector<float>   *el_corrected_pt_cUp_NP14;
   vector<float>   *el_corrected_pt_cUp_NP15;
   vector<float>   *el_corrected_pt_cUp_NP16;
   vector<float>   *el_corrected_pt_cUp_NP17;
   vector<float>   *el_corrected_pt_cUp_NP18;
   vector<float>   *el_corrected_pt_cUp_NP19;
   vector<float>   *el_corrected_pt_cUp_NP20;
   vector<float>   *el_corrected_pt_cUp_NP21;
   vector<float>   *el_corrected_pt_cUp_NP22;
   vector<float>   *el_corrected_pt_cUp_NP23;
   vector<float>   *el_corrected_pt_cUp_NP24;
   vector<float>   *el_corrected_pt_cDown_NP1;
   vector<float>   *el_corrected_pt_cDown_NP2;
   vector<float>   *el_corrected_pt_cDown_NP3;
   vector<float>   *el_corrected_pt_cDown_NP4;
   vector<float>   *el_corrected_pt_cDown_NP5;
   vector<float>   *el_corrected_pt_cDown_NP6;
   vector<float>   *el_corrected_pt_cDown_NP7;
   vector<float>   *el_corrected_pt_cDown_NP8;
   vector<float>   *el_corrected_pt_cDown_NP9;
   vector<float>   *el_corrected_pt_cDown_NP10;
   vector<float>   *el_corrected_pt_cDown_NP11;
   vector<float>   *el_corrected_pt_cDown_NP12;
   vector<float>   *el_corrected_pt_cDown_NP13;
   vector<float>   *el_corrected_pt_cDown_NP14;
   vector<float>   *el_corrected_pt_cDown_NP15;
   vector<float>   *el_corrected_pt_cDown_NP16;
   vector<float>   *el_corrected_pt_cDown_NP17;
   vector<float>   *el_corrected_pt_cDown_NP18;
   vector<float>   *el_corrected_pt_cDown_NP19;
   vector<float>   *el_corrected_pt_cDown_NP20;
   vector<float>   *el_corrected_pt_cDown_NP21;
   vector<float>   *el_corrected_pt_cDown_NP22;
   vector<float>   *el_corrected_pt_cDown_NP23;
   vector<float>   *el_corrected_pt_cDown_NP24;
   vector<float>   *fwdel_pt;
   vector<float>   *fwdel_eta;
   vector<float>   *fwdel_phi;
   Float_t         u_pt_el_loose_pfo;
   Float_t         u_pt_el_loose_pfoCharged;
   Float_t         u_pt_el_loose_pfoEM;
   Float_t         u_pt_el_loose_pfoEMCentral;
   Float_t         u_pt_el_loose_pfoEMForward;
   Float_t         u_pt_el_loose_pfoNeutral;
   Float_t         u_pt_el_loose_pfoNeutralEM;
   Float_t         u_pt_el_loose_pfoNeutralEMCentral;
   Float_t         u_pt_el_loose_pfoNeutralEMForward;
   Float_t         u_pt_el_loose_pfovor;
   Float_t         u_pt_el_loose_pfovorsp;
   Float_t         u_pt_el_medium_pfo;
   Float_t         u_pt_el_medium_pfoCharged;
   Float_t         u_pt_el_medium_pfoEM;
   Float_t         u_pt_el_medium_pfoEMCentral;
   Float_t         u_pt_el_medium_pfoEMForward;
   Float_t         u_pt_el_medium_pfoNeutral;
   Float_t         u_pt_el_medium_pfoNeutralEM;
   Float_t         u_pt_el_medium_pfoNeutralEMCentral;
   Float_t         u_pt_el_medium_pfoNeutralEMForward;
   Float_t         u_pt_el_medium_pfovor;
   Float_t         u_pt_el_medium_pfovorsp;
   Float_t         u_phi_el_loose_pfo;
   Float_t         u_phi_el_loose_pfoCharged;
   Float_t         u_phi_el_loose_pfoEM;
   Float_t         u_phi_el_loose_pfoEMCentral;
   Float_t         u_phi_el_loose_pfoEMForwar ;
   Float_t         u_phi_el_loose_pfoNeutral;
   Float_t         u_phi_el_loose_pfoNeutralEM;
   Float_t         u_phi_el_loose_pfoNeutralEMCentral;
   Float_t         u_phi_el_loose_pfoNeutralEMForwar ;
   Float_t         u_phi_el_loose_pfovor;
   Float_t         u_phi_el_loose_pfovorsp;
   Float_t         u_phi_el_medium_pfo;
   Float_t         u_phi_el_medium_pfoCharged;
   Float_t         u_phi_el_medium_pfoEM;
   Float_t         u_phi_el_medium_pfoEMCentral;
   Float_t         u_phi_el_medium_pfoEMForward;
   Float_t         u_phi_el_medium_pfoNeutral;
   Float_t         u_phi_el_medium_pfoNeutralEM;
   Float_t         u_phi_el_medium_pfoNeutralEMCentral;
   Float_t         u_phi_el_medium_pfoNeutralEMForward;
   Float_t         u_phi_el_medium_pfovor;
   Float_t         u_phi_el_medium_pfovorsp;
   Float_t         u_sumet_el_loose_pfo;
   Float_t         u_sumet_el_loose_pfoCharged;
   Float_t         u_sumet_el_loose_pfoEM;
   Float_t         u_sumet_el_loose_pfoEMCentral;
   Float_t         u_sumet_el_loose_pfoEMForward;
   Float_t         u_sumet_el_loose_pfoNeutral;
   Float_t         u_sumet_el_loose_pfoNeutralEM;
   Float_t         u_sumet_el_loose_pfoNeutralEMCentral;
   Float_t         u_sumet_el_loose_pfoNeutralEMForward;
   Float_t         u_sumet_el_medium_pfo;
   Float_t         u_sumet_el_medium_pfoCharged;
   Float_t         u_sumet_el_medium_pfoEM;
   Float_t         u_sumet_el_medium_pfoEMCentral;
   Float_t         u_sumet_el_medium_pfoEMForward;
   Float_t         u_sumet_el_medium_pfoNeutral;
   Float_t         u_sumet_el_medium_pfoNeutralEM;
   Float_t         u_sumet_el_medium_pfoNeutralEMCentral;
   Float_t         u_sumet_el_medium_pfoNeutralEMForward;
   Float_t         sumEt_loose;
   Float_t         sumEtUE_loose;
   Float_t         sumEt_medium;
   Float_t         sumEtUE_mediumF;
   Float_t         u_corrected_pt_el_loose_pfoEM;
   Float_t         u_corrected_phi_el_loose_pfoEM;
   Float_t         sumetweight_el_loose_pfoEM;
   Float_t         u_corrected_pt_el_medium_pfoEM;
   Float_t         u_corrected_phi_el_medium_pfoEM;
   Float_t         sumetweight_el_medium_pfoEM;
   Float_t         uParBoson;
   Float_t         uPerpBoson;
   Float_t         uParGenBoson;
   Float_t         uPerpGenBoson;
   Float_t         uParLepton;
   Float_t         uPerpLepton;
   Int_t           el_loose_u_ncones_removed;
   Int_t           el_medium_u_ncones_removed;
   Int_t           u_nPFO_charged;
   Int_t           u_nPFO_neutral;
   vector<float>   *incl_mu_pt;
   vector<float>   *incl_mu_ptloss;
   vector<float>   *incl_mu_eta;
   vector<float>   *incl_mu_phi;
   vector<float>   *incl_mu_d0sig;
   vector<float>   *incl_mu_delta_z0;
   vector<float>   *u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_UP;
   vector<float>   *u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_UP;
   vector<float>   *sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_UP;
   vector<float>   *u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_DOWN;
   vector<float>   *u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_DOWN;
   vector<float>   *sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_DOWN;
   vector<float>   *u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_UP;
   vector<float>   *u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_UP;
   vector<float>   *sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_UP;
   vector<float>   *u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_DOWN;
   vector<float>   *u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_DOWN;
   vector<float>   *sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_DOWN;
   vector<float>   *u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_UP;
   vector<float>   *u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_UP;
   vector<float>   *sumetweight_el_loose_pfoEM_RESPONSE_STAT0_UP;
   vector<float>   *u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_DOWN;
   vector<float>   *u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_DOWN;
   vector<float>   *sumetweight_el_loose_pfoEM_RESPONSE_STAT0_DOWN;
   vector<float>   *u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_UP;
   vector<float>   *u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_UP;
   vector<float>   *sumetweight_el_loose_pfoEM_RESPONSE_STAT1_UP;
   vector<float>   *u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_DOWN;
   vector<float>   *u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_DOWN;
   vector<float>   *sumetweight_el_loose_pfoEM_RESPONSE_STAT1_DOWN;
   vector<float>   *u_corrected_pt_el_medium_pfoEM_RESOLUTION_STAT0_UP;
   vector<float>   *u_corrected_phi_el_medium_pfoEM_RESOLUTION_STAT0_UP;
   vector<float>   *sumetweight_el_medium_pfoEM_RESOLUTION_STAT0_UP;
   vector<float>   *u_corrected_pt_el_medium_pfoEM_RESOLUTION_STAT0_DOWN;
   vector<float>   *u_corrected_phi_el_medium_pfoEM_RESOLUTION_STAT0_DOWN;
   vector<float>   *sumetweight_el_medium_pfoEM_RESOLUTION_STAT0_DOWN;
   vector<float>   *u_corrected_pt_el_medium_pfoEM_RESOLUTION_STAT1_UP;
   vector<float>   *u_corrected_phi_el_medium_pfoEM_RESOLUTION_STAT1_UP;
   vector<float>   *sumetweight_el_medium_pfoEM_RESOLUTION_STAT1_UP;
   vector<float>   *u_corrected_pt_el_medium_pfoEM_RESOLUTION_STAT1_DOWN;
   vector<float>   *u_corrected_phi_el_medium_pfoEM_RESOLUTION_STAT1_DOWN;
   vector<float>   *sumetweight_el_medium_pfoEM_RESOLUTION_STAT1_DOWN;
   vector<float>   *u_corrected_pt_el_medium_pfoEM_RESPONSE_STAT0_UP;
   vector<float>   *u_corrected_phi_el_medium_pfoEM_RESPONSE_STAT0_UP;
   vector<float>   *sumetweight_el_medium_pfoEM_RESPONSE_STAT0_UP;
   vector<float>   *u_corrected_pt_el_medium_pfoEM_RESPONSE_STAT0_DOWN;
   vector<float>   *u_corrected_phi_el_medium_pfoEM_RESPONSE_STAT0_DOWN;
   vector<float>   *sumetweight_el_medium_pfoEM_RESPONSE_STAT0_DOWN;
   vector<float>   *u_corrected_pt_el_medium_pfoEM_RESPONSE_STAT1_UP;
   vector<float>   *u_corrected_phi_el_medium_pfoEM_RESPONSE_STAT1_UP;
   vector<float>   *sumetweight_el_medium_pfoEM_RESPONSE_STAT1_UP;
   vector<float>   *u_corrected_pt_el_medium_pfoEM_RESPONSE_STAT1_DOWN;
   vector<float>   *u_corrected_phi_el_medium_pfoEM_RESPONSE_STAT1_DOWN;
   vector<float>   *sumetweight_el_medium_pfoEM_RESPONSE_STAT1_DOWN;
   Float_t         u_corrected_pt_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
   Float_t         u_corrected_phi_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
   Float_t         sumetweight_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
   Float_t         u_corrected_pt_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
   Float_t         u_corrected_phi_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
   Float_t         sumetweight_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
   Float_t         u_corrected_pt_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
   Float_t         u_corrected_phi_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
   Float_t         sumetweight_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
   Float_t         u_corrected_pt_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
   Float_t         u_corrected_phi_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
   Float_t         sumetweight_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
   Float_t         u_corrected_pt_el_loose_pfoEM_RESPONSE_SYS_UP;
   Float_t         u_corrected_phi_el_loose_pfoEM_RESPONSE_SYS_UP;
   Float_t         sumetweight_el_loose_pfoEM_RESPONSE_SYS_UP;
   Float_t         u_corrected_pt_el_loose_pfoEM_RESPONSE_SYS_DOWN;
   Float_t         u_corrected_phi_el_loose_pfoEM_RESPONSE_SYS_DOWN;
   Float_t         sumetweight_el_loose_pfoEM_RESPONSE_SYS_DOWN;
   Float_t         u_corrected_pt_el_loose_pfoEM_SET_SYS;
   Float_t         u_corrected_phi_el_loose_pfoEM_SET_SYS;
   Float_t         sumetweight_el_loose_pfoEM_SET_SYS;
   Float_t         u_corrected_pt_el_medium_pfoEM_RESOLUTION_EXTSYS_UP;
   Float_t         u_corrected_phi_el_medium_pfoEM_RESOLUTION_EXTSYS_UP;
   Float_t         sumetweight_el_medium_pfoEM_RESOLUTION_EXTSYS_UP;
   Float_t         u_corrected_pt_el_medium_pfoEM_RESOLUTION_EXTSYS_DOWN;
   Float_t         u_corrected_phi_el_medium_pfoEM_RESOLUTION_EXTSYS_DOWN;
   Float_t         sumetweight_el_medium_pfoEM_RESOLUTION_EXTSYS_DOWN;
   Float_t         u_corrected_pt_el_medium_pfoEM_RESPONSE_EXTSYS_UP;
   Float_t         u_corrected_phi_el_medium_pfoEM_RESPONSE_EXTSYS_UP;
   Float_t         sumetweight_el_medium_pfoEM_RESPONSE_EXTSYS_UP;
   Float_t         u_corrected_pt_el_medium_pfoEM_RESPONSE_EXTSYS_DOWN;
   Float_t         u_corrected_phi_el_medium_pfoEM_RESPONSE_EXTSYS_DOWN;
   Float_t         sumetweight_el_medium_pfoEM_RESPONSE_EXTSYS_DOWN;
   Float_t         u_corrected_pt_el_medium_pfoEM_RESPONSE_SYS_UP;
   Float_t         u_corrected_phi_el_medium_pfoEM_RESPONSE_SYS_UP;
   Float_t         sumetweight_el_medium_pfoEM_RESPONSE_SYS_UP;
   Float_t         u_corrected_pt_el_medium_pfoEM_RESPONSE_SYS_DOWN;
   Float_t         u_corrected_phi_el_medium_pfoEM_RESPONSE_SYS_DOWN;
   Float_t         sumetweight_el_medium_pfoEM_RESPONSE_SYS_DOWN;
   Float_t         u_corrected_pt_el_medium_pfoEM_SET_SYS;
   Float_t         u_corrected_phi_el_medium_pfoEM_SET_SYS;
   Float_t         sumetweight_el_medium_pfoEM_SET_SYS;
   Float_t         tu_pt_Int;
   Float_t         tu_pt_IntMuons;
   Float_t         tu_pt_IntOut;
   Float_t         tu_pt_NonInt;
   Float_t         tu_phi_Int;
   Float_t         tu_phi_IntMuons;
   Float_t         tu_phi_IntOut;
   Float_t         tu_phi_NonInt;
   Float_t         tu_sumet_Int;
   Float_t         tu_sumet_IntMuons;
   Float_t         tu_sumet_IntOut;
   Float_t         tu_sumet_NonInt;
   vector<float>   *tlep_dressed_pt;
   vector<float>   *tlep_dressed_eta;
   vector<float>   *tlep_dressed_phi;
   vector<float>   *tlep_dressed_e;
   vector<int>     *tlep_dressed_pdgId;
   vector<float>   *tlep_bare_pt;
   vector<float>   *tlep_bare_eta;
   vector<float>   *tlep_bare_phi;
   vector<float>   *tlep_bare_e;
   vector<int>     *tlep_bare_pdgId;
   vector<float>   *tlep_born_pt;
   vector<float>   *tlep_born_eta;
   vector<float>   *tlep_born_phi;
   vector<float>   *tlep_born_e;
   vector<int>     *tlep_born_pdgId;
   vector<float>   *tneutrino_pt;
   vector<float>   *tneutrino_eta;
   vector<float>   *tneutrino_phi;
   vector<float>   *tneutrino_e;
   vector<int>     *tneutrino_pdgId;
   vector<float>   *tbornneutrino_pt;
   vector<float>   *tbornneutrino_eta;
   vector<float>   *tbornneutrino_phi;
   vector<float>   *tbornneutrino_e;
   vector<int>     *tbornneutrino_pdgId;
   vector<float>   *tphoton_pt;
   vector<float>   *tphoton_eta;
   vector<float>   *tphoton_phi;
   vector<float>   *tphoton_e;
   vector<float>   *tjet_pt;
   vector<float>   *tjet_eta;
   vector<float>   *tjet_phi;
   vector<float>   *tjet_e;
   Float_t         tboson_pt;
   Float_t         tboson_eta;
   Float_t         tboson_phi;
   Float_t         tboson_e;
   Int_t           tboson_pdgId;
   Int_t           tparton_pdgId1;
   Int_t           tparton_pdgId2;

   // List of branches
   TBranch        *b_EventWeight_gen;   //!
   TBranch        *b_EventWeight_pu;   //!
   TBranch        *b_EventWeight_vertex;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EvtNumber;   //!
   TBranch        *b_vxp_z0;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_nTracksPV;   //!
   TBranch        *b_nintime;   //!
   TBranch        *b_bcid;   //!
   TBranch        *b_lbn;   //!
   TBranch        *b_actual_mu;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_nHadPart;   //!
   TBranch        *b_nHadChargedPart;   //!
   TBranch        *b_sumPtHadPart;   //!
   TBranch        *b_sumPtChargedPart;   //!
   TBranch        *b_passTrigger_el;   //!
   TBranch        *b_passTrigger_mu;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_d0sig;   //!
   TBranch        *b_mu_delta_z0;   //!
   TBranch        *b_mu_isTight;   //!
   TBranch        *b_mu_trigMatch;   //!
   TBranch        *b_mu_inrecoil;   //!
   TBranch        *b_mu_isolation_ptcone20;   //!
   TBranch        *b_mu_isolation_ptvarcone20;   //!
   TBranch        *b_mu_isolation_ptvarcone30;   //!
   TBranch        *b_mu_isolation_ptvarcone40;   //!
   TBranch        *b_mu_isolation_topoetcone20;   //!
   TBranch        *b_mu_isolation_topoetcone30;   //!
   TBranch        *b_mu_isolation_topoetcone40;   //!
   TBranch        *b_mu_isIsolated;   //!
   TBranch        *b_mu_corrected_pt;   //!
   TBranch        *b_mu_recosf;   //!
   TBranch        *b_mu_recomceff;   //!
   TBranch        *b_mu_isosf;   //!
   TBranch        *b_mu_isomceff;   //!
   TBranch        *b_mu_ttvasf;   //!
   TBranch        *b_mu_ttvamceff;   //!
   TBranch        *b_mu_trigsf;   //!
   TBranch        *b_mu_trigmceff;   //!
   TBranch        *b_mu_syspt_MUON_ID__1down;   //!
   TBranch        *b_mu_syspt_MUON_ID__1up;   //!
   TBranch        *b_mu_syspt_MUON_MS__1down;   //!
   TBranch        *b_mu_syspt_MUON_MS__1up;   //!
   TBranch        *b_mu_syspt_MUON_SAGITTA_RESBIAS__1down;   //!
   TBranch        *b_mu_syspt_MUON_SAGITTA_RESBIAS__1up;   //!
   TBranch        *b_mu_syspt_MUON_SAGITTA_RHO__1down;   //!
   TBranch        *b_mu_syspt_MUON_SAGITTA_RHO__1up;   //!
   TBranch        *b_mu_syspt_MUON_SCALE__1down;   //!
   TBranch        *b_mu_syspt_MUON_SCALE__1up;   //!
   TBranch        *b_mu_recosf_MuRecoSys_uncorr_up;   //!
   TBranch        *b_mu_recosf_MuRecoSys_uncorr_down;   //!
   TBranch        *b_mu_recosf_MuRecoSys_uncorr_BinNumber;   //!
   TBranch        *b_mu_recosf_MuRecoSys_uncorr_MaxBinNumber;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_BKGFRACTION_down;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_LUMIUNCERT_down;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_MCXSEC_down;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_down;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_BKGFRACTION_up;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_LUMIUNCERT_up;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_MCXSEC_up;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_up;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_MATCHING_SYM_up;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_TRUTH_SYM_up;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_MATCHING_SYM_down;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_TRUTH_SYM_down;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_up;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_down;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_PtDEPENDENCY_up;   //!
   TBranch        *b_mu_recosf_MuRecoSys_corr_PtDEPENDENCY_down;   //!
   TBranch        *b_mu_isosf_MuIsoSys_uncorr_up;   //!
   TBranch        *b_mu_isosf_MuIsoSys_uncorr_down;   //!
   TBranch        *b_mu_isosf_MuIsoSys_uncorr_BinNumber;   //!
   TBranch        *b_mu_isosf_MuIsoSys_uncorr_MaxBinNumber;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_eta_up;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_eta_down;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_mass_up;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_mass_down;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_tpdR_up;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_tpdR_down;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_isoBkg_up;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_isoBkg_down;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_probeQ_up;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_probeQ_down;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_tagIsol_up;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_tagIsol_down;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_dRmuj_up;   //!
   TBranch        *b_mu_isosf_MuIsoSys_corr_dRmuj_down;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_uncorr_up;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_uncorr_down;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_uncorr_BinNumber;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_uncorr_MaxBinNumber;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_corr_QCDTEMPLATE_down;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_corr_LUMIUNCERT_down;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_corr_BKGFRACTION_down;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_corr_MCXSEC_down;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_down;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_corr_QCDTEMPLATE_up;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_corr_LUMIUNCERT_up;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_corr_BKGFRACTION_up;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_corr_MCXSEC_up;   //!
   TBranch        *b_mu_ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_up;   //!
   TBranch        *b_mu_trigsf_MuTrigSys_PtEta_up;   //!
   TBranch        *b_mu_trigsf_MuTrigSys_PtEta_down;   //!
   TBranch        *b_mu_trigsf_MuTrigSys_PtEta_uncorr_BinNumber;   //!
   TBranch        *b_mu_trigsf_MuTrigSys_PtEta_uncorr_MaxBinNumber;   //!
   TBranch        *b_mu_trigsf_MuTrigSys_PtEta_corr_iso_loose_avg;   //!
   TBranch        *b_mu_trigsf_MuTrigSys_PtEta_corr_dPhi_avg;   //!
   TBranch        *b_mu_trigsf_MuTrigSys_PtEta_corr_noIP_avg;   //!
   TBranch        *b_mu_trigsf_MuTrigSys_PtEta_corr_iso_tight_avg;   //!
   TBranch        *b_mu_trigsf_MuTrigSys_PtEta_corr_mlltight_avg;   //!
   TBranch        *b_el_pt;   //!
   TBranch        *b_el_eta;   //!
   TBranch        *b_el_phi;   //!
   TBranch        *b_el_qOverP;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_d0sig;   //!
   TBranch        *b_el_delta_z0;   //!
   TBranch        *b_el_isTight;   //!
   TBranch        *b_el_isMedium;   //!
   TBranch        *b_el_trigMatch;   //!
   TBranch        *b_el_inrecoil;   //!
   TBranch        *b_el_inrecoil_loose;   //!
   TBranch        *b_el_inrecoil_medium;   //!
   TBranch        *b_el_isolation_ptcone20;   //!
   TBranch        *b_el_isolation_ptvarcone20;   //!
   TBranch        *b_el_isolation_ptvarcone30;   //!
   TBranch        *b_el_isolation_ptvarcone40;   //!
   TBranch        *b_el_isolation_topoetcone20;   //!
   TBranch        *b_el_isolation_topoetcone20ptCorrection;   //!
   TBranch        *b_el_isolation_topoetcone30;   //!
   TBranch        *b_el_isolation_topoetcone30ptCorrection;   //!
   TBranch        *b_el_isolation_topoetcone40;   //!
   TBranch        *b_el_isolation_topoetcone40ptCorrection;   //!
   TBranch        *b_el_isIsolated;   //!
   TBranch        *b_el_corrected_pt;   //!
   TBranch        *b_el_recosf;   //!
   TBranch        *b_el_recomceff;   //!
   TBranch        *b_el_isosf;   //!
   TBranch        *b_el_isomceff;   //!
   TBranch        *b_el_idsf;   //!
   TBranch        *b_el_idmceff;   //!
   TBranch        *b_el_trigsf;   //!
   TBranch        *b_el_trigmceff;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1down;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1up;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1down;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1up;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1down;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1up;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1down;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1up;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1down;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1up;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1down;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1up;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_FULL_UncorrUncertaintyNP33__1down;   //!
   TBranch        *b_el_sysrecosf_EL_EFF_Reco_FULL_UncorrUncertaintyNP33__1up;   //!
   TBranch        *b_el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_up;   //!
   TBranch        *b_el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_down;   //!
   TBranch        *b_el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_up;   //!
   TBranch        *b_el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_down;   //!
   TBranch        *b_el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_up;   //!
   TBranch        *b_el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_down;   //!
   TBranch        *b_el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_up;   //!
   TBranch        *b_el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_down;   //!
   TBranch        *b_el_isosf_ElIsoSys_uncorr_up;   //!
   TBranch        *b_el_isosf_ElIsoSys_uncorr_down;   //!
   TBranch        *b_el_isosf_ElIsoSys_uncorr_BinNumber;   //!
   TBranch        *b_el_isosf_ElIsoSys_uncorr_MaxBinNumber;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_down;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_up;   //!
   TBranch        *b_el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_down;   //!
   TBranch        *b_el_idsf_ElIDSys_uncorr_up;   //!
   TBranch        *b_el_idsf_ElIDSys_uncorr_down;   //!
   TBranch        *b_el_idsf_ElIDSys_uncorr_BinNumber;   //!
   TBranch        *b_el_idsf_ElIDSys_uncorr_MaxBinNumber;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr10_up;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr10_down;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr11_up;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr11_down;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr12_up;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr12_down;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr13_up;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr13_down;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr14_up;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr14_down;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr8_up;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr8_down;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr9_up;   //!
   TBranch        *b_el_trigsf_ElTrigSys_FullSim_corr9_down;   //!
   TBranch        *b_el_trigsf_ElTrigSys_uncorr_up;   //!
   TBranch        *b_el_trigsf_ElTrigSys_uncorr_down;   //!
   TBranch        *b_el_trigsf_ElTrigSys_uncorr_BinNumber;   //!
   TBranch        *b_el_trigsf_ElTrigSys_uncorr_MaxBinNumber;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP1;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP2;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP3;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP4;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP5;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP6;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP7;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP8;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP9;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP10;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP11;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP12;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP13;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP14;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP15;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP16;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP17;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP18;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP19;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP20;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP21;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP22;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP23;   //!
   TBranch        *b_el_corrected_pt_scaleUp_NP24;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP1;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP2;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP3;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP4;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP5;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP6;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP7;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP8;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP9;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP10;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP11;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP12;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP13;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP14;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP15;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP16;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP17;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP18;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP19;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP20;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP21;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP22;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP23;   //!
   TBranch        *b_el_corrected_pt_scaleDown_NP24;   //!
   TBranch        *b_el_corrected_pt_cUp_NP1;   //!
   TBranch        *b_el_corrected_pt_cUp_NP2;   //!
   TBranch        *b_el_corrected_pt_cUp_NP3;   //!
   TBranch        *b_el_corrected_pt_cUp_NP4;   //!
   TBranch        *b_el_corrected_pt_cUp_NP5;   //!
   TBranch        *b_el_corrected_pt_cUp_NP6;   //!
   TBranch        *b_el_corrected_pt_cUp_NP7;   //!
   TBranch        *b_el_corrected_pt_cUp_NP8;   //!
   TBranch        *b_el_corrected_pt_cUp_NP9;   //!
   TBranch        *b_el_corrected_pt_cUp_NP10;   //!
   TBranch        *b_el_corrected_pt_cUp_NP11;   //!
   TBranch        *b_el_corrected_pt_cUp_NP12;   //!
   TBranch        *b_el_corrected_pt_cUp_NP13;   //!
   TBranch        *b_el_corrected_pt_cUp_NP14;   //!
   TBranch        *b_el_corrected_pt_cUp_NP15;   //!
   TBranch        *b_el_corrected_pt_cUp_NP16;   //!
   TBranch        *b_el_corrected_pt_cUp_NP17;   //!
   TBranch        *b_el_corrected_pt_cUp_NP18;   //!
   TBranch        *b_el_corrected_pt_cUp_NP19;   //!
   TBranch        *b_el_corrected_pt_cUp_NP20;   //!
   TBranch        *b_el_corrected_pt_cUp_NP21;   //!
   TBranch        *b_el_corrected_pt_cUp_NP22;   //!
   TBranch        *b_el_corrected_pt_cUp_NP23;   //!
   TBranch        *b_el_corrected_pt_cUp_NP24;   //!
   TBranch        *b_el_corrected_pt_cDown_NP1;   //!
   TBranch        *b_el_corrected_pt_cDown_NP2;   //!
   TBranch        *b_el_corrected_pt_cDown_NP3;   //!
   TBranch        *b_el_corrected_pt_cDown_NP4;   //!
   TBranch        *b_el_corrected_pt_cDown_NP5;   //!
   TBranch        *b_el_corrected_pt_cDown_NP6;   //!
   TBranch        *b_el_corrected_pt_cDown_NP7;   //!
   TBranch        *b_el_corrected_pt_cDown_NP8;   //!
   TBranch        *b_el_corrected_pt_cDown_NP9;   //!
   TBranch        *b_el_corrected_pt_cDown_NP10;   //!
   TBranch        *b_el_corrected_pt_cDown_NP11;   //!
   TBranch        *b_el_corrected_pt_cDown_NP12;   //!
   TBranch        *b_el_corrected_pt_cDown_NP13;   //!
   TBranch        *b_el_corrected_pt_cDown_NP14;   //!
   TBranch        *b_el_corrected_pt_cDown_NP15;   //!
   TBranch        *b_el_corrected_pt_cDown_NP16;   //!
   TBranch        *b_el_corrected_pt_cDown_NP17;   //!
   TBranch        *b_el_corrected_pt_cDown_NP18;   //!
   TBranch        *b_el_corrected_pt_cDown_NP19;   //!
   TBranch        *b_el_corrected_pt_cDown_NP20;   //!
   TBranch        *b_el_corrected_pt_cDown_NP21;   //!
   TBranch        *b_el_corrected_pt_cDown_NP22;   //!
   TBranch        *b_el_corrected_pt_cDown_NP23;   //!
   TBranch        *b_el_corrected_pt_cDown_NP24;   //!
   TBranch        *b_fwdel_pt;   //!
   TBranch        *b_fwdel_eta;   //!
   TBranch        *b_fwdel_phi;   //!
   TBranch        *b_u_pt_el_loose_pfo;   //!
   TBranch        *b_u_pt_el_loose_pfoCharged;   //!
   TBranch        *b_u_pt_el_loose_pfoEM;   //!
   TBranch        *b_u_pt_el_loose_pfoEMCentral;   //!
   TBranch        *b_u_pt_el_loose_pfoEMForward;   //!
   TBranch        *b_u_pt_el_loose_pfoNeutral;   //!
   TBranch        *b_u_pt_el_loose_pfoNeutralEM;   //!
   TBranch        *b_u_pt_el_loose_pfoNeutralEMCentral;   //!
   TBranch        *b_u_pt_el_loose_pfoNeutralEMForward;   //!
   TBranch        *b_u_pt_el_loose_pfovor;   //!
   TBranch        *b_u_pt_el_loose_pfovorsp;   //!
   TBranch        *b_u_pt_el_medium_pfo;   //!
   TBranch        *b_u_pt_el_medium_pfoCharged;   //!
   TBranch        *b_u_pt_el_medium_pfoEM;   //!
   TBranch        *b_u_pt_el_medium_pfoEMCentral;   //!
   TBranch        *b_u_pt_el_medium_pfoEMForward;   //!
   TBranch        *b_u_pt_el_medium_pfoNeutral;   //!
   TBranch        *b_u_pt_el_medium_pfoNeutralEM;   //!
   TBranch        *b_u_pt_el_medium_pfoNeutralEMCentral;   //!
   TBranch        *b_u_pt_el_medium_pfoNeutralEMForward;   //!
   TBranch        *b_u_pt_el_medium_pfovor;   //!
   TBranch        *b_u_pt_el_medium_pfovorsp;   //!
   TBranch        *b_u_phi_el_loose_pfo;   //!
   TBranch        *b_u_phi_el_loose_pfoCharged;   //!
   TBranch        *b_u_phi_el_loose_pfoEM;   //!
   TBranch        *b_u_phi_el_loose_pfoEMCentral;   //!
   TBranch        *b_u_phi_el_loose_pfoEMForwar ;   //!
   TBranch        *b_u_phi_el_loose_pfoNeutral;   //!
   TBranch        *b_u_phi_el_loose_pfoNeutralEM;   //!
   TBranch        *b_u_phi_el_loose_pfoNeutralEMCentral;   //!
   TBranch        *b_u_phi_el_loose_pfoNeutralEMForwar ;   //!
   TBranch        *b_u_phi_el_loose_pfovor;   //!
   TBranch        *b_u_phi_el_loose_pfovorsp;   //!
   TBranch        *b_u_phi_el_medium_pfo;   //!
   TBranch        *b_u_phi_el_medium_pfoCharged;   //!
   TBranch        *b_u_phi_el_medium_pfoEM;   //!
   TBranch        *b_u_phi_el_medium_pfoEMCentral;   //!
   TBranch        *b_u_phi_el_medium_pfoEMForward;   //!
   TBranch        *b_u_phi_el_medium_pfoNeutral;   //!
   TBranch        *b_u_phi_el_medium_pfoNeutralEM;   //!
   TBranch        *b_u_phi_el_medium_pfoNeutralEMCentral;   //!
   TBranch        *b_u_phi_el_medium_pfoNeutralEMForward;   //!
   TBranch        *b_u_phi_el_medium_pfovor;   //!
   TBranch        *b_u_phi_el_medium_pfovorsp;   //!
   TBranch        *b_u_sumet_el_loose_pfo;   //!
   TBranch        *b_u_sumet_el_loose_pfoCharged;   //!
   TBranch        *b_u_sumet_el_loose_pfoEM;   //!
   TBranch        *b_u_sumet_el_loose_pfoEMCentral;   //!
   TBranch        *b_u_sumet_el_loose_pfoEMForward;   //!
   TBranch        *b_u_sumet_el_loose_pfoNeutral;   //!
   TBranch        *b_u_sumet_el_loose_pfoNeutralEM;   //!
   TBranch        *b_u_sumet_el_loose_pfoNeutralEMCentral;   //!
   TBranch        *b_u_sumet_el_loose_pfoNeutralEMForward;   //!
   TBranch        *b_u_sumet_el_medium_pfo;   //!
   TBranch        *b_u_sumet_el_medium_pfoCharged;   //!
   TBranch        *b_u_sumet_el_medium_pfoEM;   //!
   TBranch        *b_u_sumet_el_medium_pfoEMCentral;   //!
   TBranch        *b_u_sumet_el_medium_pfoEMForward;   //!
   TBranch        *b_u_sumet_el_medium_pfoNeutral;   //!
   TBranch        *b_u_sumet_el_medium_pfoNeutralEM;   //!
   TBranch        *b_u_sumet_el_medium_pfoNeutralEMCentral;   //!
   TBranch        *b_u_sumet_el_medium_pfoNeutralEMForward;   //!
   TBranch        *b_sumEt_loose;   //!
   TBranch        *b_sumEtUE_loose;   //!
   TBranch        *b_sumEt_medium;   //!
   TBranch        *b_sumEtUE_medium;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM;   //!
   TBranch        *b_uParBoson;   //!
   TBranch        *b_uPerpBoson;   //!
   TBranch        *b_uParGenBoson;   //!
   TBranch        *b_uPerpGenBoson;   //!
   TBranch        *b_uParLepton;   //!
   TBranch        *b_uPerpLepton;   //!
   TBranch        *b_el_loose_u_ncones_removed;   //!
   TBranch        *b_el_medium_u_ncones_removed;   //!
   TBranch        *b_u_nPFO_charged;   //!
   TBranch        *b_u_nPFO_neutral;   //!
   TBranch        *b_incl_mu_pt;   //!
   TBranch        *b_incl_mu_ptloss;   //!
   TBranch        *b_incl_mu_eta;   //!
   TBranch        *b_incl_mu_phi;   //!
   TBranch        *b_incl_mu_d0sig;   //!
   TBranch        *b_incl_mu_delta_z0;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_UP;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_UP;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_UP;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_DOWN;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_UP;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_UP;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_UP;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_DOWN;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_UP;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_UP;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESPONSE_STAT0_UP;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_DOWN;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESPONSE_STAT0_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_UP;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_UP;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESPONSE_STAT1_UP;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_DOWN;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESPONSE_STAT1_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESOLUTION_STAT0_UP;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESOLUTION_STAT0_UP;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESOLUTION_STAT0_UP;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESOLUTION_STAT0_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESOLUTION_STAT0_DOWN;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESOLUTION_STAT0_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESOLUTION_STAT1_UP;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESOLUTION_STAT1_UP;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESOLUTION_STAT1_UP;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESOLUTION_STAT1_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESOLUTION_STAT1_DOWN;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESOLUTION_STAT1_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESPONSE_STAT0_UP;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESPONSE_STAT0_UP;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESPONSE_STAT0_UP;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESPONSE_STAT0_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESPONSE_STAT0_DOWN;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESPONSE_STAT0_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESPONSE_STAT1_UP;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESPONSE_STAT1_UP;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESPONSE_STAT1_UP;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESPONSE_STAT1_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESPONSE_STAT1_DOWN;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESPONSE_STAT1_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESPONSE_EXTSYS_UP;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESPONSE_EXTSYS_UP;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESPONSE_EXTSYS_UP;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESPONSE_SYS_UP;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESPONSE_SYS_UP;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESPONSE_SYS_UP;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_RESPONSE_SYS_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_RESPONSE_SYS_DOWN;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_RESPONSE_SYS_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_loose_pfoEM_SET_SYS;   //!
   TBranch        *b_u_corrected_phi_el_loose_pfoEM_SET_SYS;   //!
   TBranch        *b_sumetweight_el_loose_pfoEM_SET_SYS;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESOLUTION_EXTSYS_UP;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESOLUTION_EXTSYS_UP;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESOLUTION_EXTSYS_UP;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESOLUTION_EXTSYS_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESOLUTION_EXTSYS_DOWN;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESOLUTION_EXTSYS_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESPONSE_EXTSYS_UP;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESPONSE_EXTSYS_UP;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESPONSE_EXTSYS_UP;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESPONSE_EXTSYS_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESPONSE_EXTSYS_DOWN;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESPONSE_EXTSYS_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESPONSE_SYS_UP;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESPONSE_SYS_UP;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESPONSE_SYS_UP;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_RESPONSE_SYS_DOWN;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_RESPONSE_SYS_DOWN;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_RESPONSE_SYS_DOWN;   //!
   TBranch        *b_u_corrected_pt_el_medium_pfoEM_SET_SYS;   //!
   TBranch        *b_u_corrected_phi_el_medium_pfoEM_SET_SYS;   //!
   TBranch        *b_sumetweight_el_medium_pfoEM_SET_SYS;   //!
   TBranch        *b_tu_pt_Int;   //!
   TBranch        *b_tu_pt_IntMuons;   //!
   TBranch        *b_tu_pt_IntOut;   //!
   TBranch        *b_tu_pt_NonInt;   //!
   TBranch        *b_tu_phi_Int;   //!
   TBranch        *b_tu_phi_IntMuons;   //!
   TBranch        *b_tu_phi_IntOut;   //!
   TBranch        *b_tu_phi_NonInt;   //!
   TBranch        *b_tu_sumet_Int;   //!
   TBranch        *b_tu_sumet_IntMuons;   //!
   TBranch        *b_tu_sumet_IntOut;   //!
   TBranch        *b_tu_sumet_NonInt;   //!
   TBranch        *b_tlep_dressed_pt;   //!
   TBranch        *b_tlep_dressed_eta;   //!
   TBranch        *b_tlep_dressed_phi;   //!
   TBranch        *b_tlep_dressed_e;   //!
   TBranch        *b_tlep_dressed_pdgId;   //!
   TBranch        *b_tlep_bare_pt;   //!
   TBranch        *b_tlep_bare_eta;   //!
   TBranch        *b_tlep_bare_phi;   //!
   TBranch        *b_tlep_bare_e;   //!
   TBranch        *b_tlep_bare_pdgId;   //!
   TBranch        *b_tlep_born_pt;   //!
   TBranch        *b_tlep_born_eta;   //!
   TBranch        *b_tlep_born_phi;   //!
   TBranch        *b_tlep_born_e;   //!
   TBranch        *b_tlep_born_pdgId;   //!
   TBranch        *b_tneutrino_pt;   //!
   TBranch        *b_tneutrino_eta;   //!
   TBranch        *b_tneutrino_phi;   //!
   TBranch        *b_tneutrino_e;   //!
   TBranch        *b_tneutrino_pdgId;   //!
   TBranch        *b_tbornneutrino_pt;   //!
   TBranch        *b_tbornneutrino_eta;   //!
   TBranch        *b_tbornneutrino_phi;   //!
   TBranch        *b_tbornneutrino_e;   //!
   TBranch        *b_tbornneutrino_pdgId;   //!
   TBranch        *b_tphoton_pt;   //!
   TBranch        *b_tphoton_eta;   //!
   TBranch        *b_tphoton_phi;   //!
   TBranch        *b_tphoton_e;   //!
   TBranch        *b_tjet_pt;   //!
   TBranch        *b_tjet_eta;   //!
   TBranch        *b_tjet_phi;   //!
   TBranch        *b_tjet_e;   //!
   TBranch        *b_tboson_pt;   //!
   TBranch        *b_tboson_eta;   //!
   TBranch        *b_tboson_phi;   //!
   TBranch        *b_tboson_e;   //!
   TBranch        *b_tboson_pdgId;   //!
   TBranch        *b_tparton_pdgId1;   //!
   TBranch        *b_tparton_pdgId2;   //!

   TreeForWasym();
   virtual ~TreeForWasym();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual int GetRootType(TString RootName);
   virtual double GetCrossSection(int nchannel);
   virtual double GetSumOfWeight(int nchannel);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, int i);
   virtual void Init();

};

#endif

#ifdef TreeForWasym_cxx

void TreeForWasym::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jet_pt = 0;
   jet_eta = 0;
   jet_phi = 0;
   mu_pt = 0;
   mu_eta = 0;
   mu_phi = 0;
   mu_charge = 0;
   mu_d0sig = 0;
   mu_delta_z0 = 0;
   mu_isTight = 0;
   mu_trigMatch = 0;
   mu_inrecoil = 0;
   mu_isolation_ptcone20 = 0;
   mu_isolation_ptvarcone20 = 0;
   mu_isolation_ptvarcone30 = 0;
   mu_isolation_ptvarcone40 = 0;
   mu_isolation_topoetcone20 = 0;
   mu_isolation_topoetcone30 = 0;
   mu_isolation_topoetcone40 = 0;
   mu_isIsolated = 0;
   mu_corrected_pt = 0;
   mu_recosf = 0;
   mu_recomceff = 0;
   mu_isosf = 0;
   mu_isomceff = 0;
   mu_ttvasf = 0;
   mu_ttvamceff = 0;
   mu_trigsf = 0;
   mu_trigmceff = 0;
   mu_syspt_MUON_ID__1down = 0;
   mu_syspt_MUON_ID__1up = 0;
   mu_syspt_MUON_MS__1down = 0;
   mu_syspt_MUON_MS__1up = 0;
   mu_syspt_MUON_SAGITTA_RESBIAS__1down = 0;
   mu_syspt_MUON_SAGITTA_RESBIAS__1up = 0;
   mu_syspt_MUON_SAGITTA_RHO__1down = 0;
   mu_syspt_MUON_SAGITTA_RHO__1up = 0;
   mu_syspt_MUON_SCALE__1down = 0;
   mu_syspt_MUON_SCALE__1up = 0;
   mu_recosf_MuRecoSys_uncorr_up = 0;
   mu_recosf_MuRecoSys_uncorr_down = 0;
   mu_recosf_MuRecoSys_uncorr_BinNumber = 0;
   mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down = 0;
   mu_recosf_MuRecoSys_corr_BKGFRACTION_down = 0;
   mu_recosf_MuRecoSys_corr_LUMIUNCERT_down = 0;
   mu_recosf_MuRecoSys_corr_MCXSEC_down = 0;
   mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_down = 0;
   mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up = 0;
   mu_recosf_MuRecoSys_corr_BKGFRACTION_up = 0;
   mu_recosf_MuRecoSys_corr_LUMIUNCERT_up = 0;
   mu_recosf_MuRecoSys_corr_MCXSEC_up = 0;
   mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_up = 0;
   mu_recosf_MuRecoSys_corr_MATCHING_SYM_up = 0;
   mu_recosf_MuRecoSys_corr_TRUTH_SYM_up = 0;
   mu_recosf_MuRecoSys_corr_MATCHING_SYM_down = 0;
   mu_recosf_MuRecoSys_corr_TRUTH_SYM_down = 0;
   mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_up = 0;
   mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_down = 0;
   mu_recosf_MuRecoSys_corr_PtDEPENDENCY_up = 0;
   mu_recosf_MuRecoSys_corr_PtDEPENDENCY_down = 0;
   mu_isosf_MuIsoSys_uncorr_up = 0;
   mu_isosf_MuIsoSys_uncorr_down = 0;
   mu_isosf_MuIsoSys_uncorr_BinNumber = 0;
   mu_isosf_MuIsoSys_corr_eta_up = 0;
   mu_isosf_MuIsoSys_corr_eta_down = 0;
   mu_isosf_MuIsoSys_corr_mass_up = 0;
   mu_isosf_MuIsoSys_corr_mass_down = 0;
   mu_isosf_MuIsoSys_corr_tpdR_up = 0;
   mu_isosf_MuIsoSys_corr_tpdR_down = 0;
   mu_isosf_MuIsoSys_corr_isoBkg_up = 0;
   mu_isosf_MuIsoSys_corr_isoBkg_down = 0;
   mu_isosf_MuIsoSys_corr_probeQ_up = 0;
   mu_isosf_MuIsoSys_corr_probeQ_down = 0;
   mu_isosf_MuIsoSys_corr_tagIsol_up = 0;
   mu_isosf_MuIsoSys_corr_tagIsol_down = 0;
   mu_isosf_MuIsoSys_corr_dRmuj_up = 0;
   mu_isosf_MuIsoSys_corr_dRmuj_down = 0;
   mu_ttvasf_MuTTVASys_uncorr_up = 0;
   mu_ttvasf_MuTTVASys_uncorr_down = 0;
   mu_ttvasf_MuTTVASys_uncorr_BinNumber = 0;
   mu_ttvasf_MuTTVASys_corr_QCDTEMPLATE_down = 0;
   mu_ttvasf_MuTTVASys_corr_LUMIUNCERT_down = 0;
   mu_ttvasf_MuTTVASys_corr_BKGFRACTION_down = 0;
   mu_ttvasf_MuTTVASys_corr_MCXSEC_down = 0;
   mu_ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_down = 0;
   mu_ttvasf_MuTTVASys_corr_QCDTEMPLATE_up = 0;
   mu_ttvasf_MuTTVASys_corr_LUMIUNCERT_up = 0;
   mu_ttvasf_MuTTVASys_corr_BKGFRACTION_up = 0;
   mu_ttvasf_MuTTVASys_corr_MCXSEC_up = 0;
   mu_ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_up = 0;
   mu_trigsf_MuTrigSys_PtEta_up = 0;
   mu_trigsf_MuTrigSys_PtEta_down = 0;
   mu_trigsf_MuTrigSys_PtEta_uncorr_BinNumber = 0;
   mu_trigsf_MuTrigSys_PtEta_corr_iso_loose_avg = 0;
   mu_trigsf_MuTrigSys_PtEta_corr_dPhi_avg = 0;
   mu_trigsf_MuTrigSys_PtEta_corr_noIP_avg = 0;
   mu_trigsf_MuTrigSys_PtEta_corr_iso_tight_avg = 0;
   mu_trigsf_MuTrigSys_PtEta_corr_mlltight_avg = 0;
   el_pt = 0;
   el_eta = 0;
   el_phi = 0;
   el_qOverP = 0;
   el_charge = 0;
   el_d0sig = 0;
   el_delta_z0 = 0;
   el_isTight = 0;
   el_isMedium = 0;
   el_trigMatch = 0;
   el_inrecoil = 0;
   el_inrecoil_loose = 0;
   el_inrecoil_medium = 0;
   el_isolation_ptcone20 = 0;
   el_isolation_ptvarcone20 = 0;
   el_isolation_ptvarcone30 = 0;
   el_isolation_ptvarcone40 = 0;
   el_isolation_topoetcone20 = 0;
   el_isolation_topoetcone20ptCorrection = 0;
   el_isolation_topoetcone30 = 0;
   el_isolation_topoetcone30ptCorrection = 0;
   el_isolation_topoetcone40 = 0;
   el_isolation_topoetcone40ptCorrection = 0;
   el_isIsolated = 0;
   el_corrected_pt = 0;
   el_recosf = 0;
   el_recomceff = 0;
   el_isosf = 0;
   el_isomceff = 0;
   el_idsf = 0;
   el_idmceff = 0;
   el_trigsf = 0;
   el_trigmceff = 0;
   el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1down = 0;
   el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1up = 0;
   el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1down = 0;
   el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1up = 0;
   el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1down = 0;
   el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1up = 0;
   el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1down = 0;
   el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1up = 0;
   el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1down = 0;
   el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1up = 0;
   el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1down = 0;
   el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1up = 0;
   el_sysrecosf_EL_EFF_Reco_FULL_UncorrUncertaintyNP33__1down = 0;
   el_sysrecosf_EL_EFF_Reco_FULL_UncorrUncertaintyNP33__1up = 0;
   el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_up = 0;
   el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_down = 0;
   el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_up = 0;
   el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_down = 0;
   el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_up = 0;
   el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_down = 0;
   el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_up = 0;
   el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_down = 0;
   el_isosf_ElIsoSys_uncorr_up = 0;
   el_isosf_ElIsoSys_uncorr_down = 0;
   el_isosf_ElIsoSys_uncorr_BinNumber = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_down = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_up = 0;
   el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_down = 0;
   el_idsf_ElIDSys_uncorr_up = 0;
   el_idsf_ElIDSys_uncorr_down = 0;
   el_idsf_ElIDSys_uncorr_BinNumber = 0;
   el_trigsf_ElTrigSys_FullSim_corr10_up = 0;
   el_trigsf_ElTrigSys_FullSim_corr10_down = 0;
   el_trigsf_ElTrigSys_FullSim_corr11_up = 0;
   el_trigsf_ElTrigSys_FullSim_corr11_down = 0;
   el_trigsf_ElTrigSys_FullSim_corr12_up = 0;
   el_trigsf_ElTrigSys_FullSim_corr12_down = 0;
   el_trigsf_ElTrigSys_FullSim_corr13_up = 0;
   el_trigsf_ElTrigSys_FullSim_corr13_down = 0;
   el_trigsf_ElTrigSys_FullSim_corr14_up = 0;
   el_trigsf_ElTrigSys_FullSim_corr14_down = 0;
   el_trigsf_ElTrigSys_FullSim_corr8_up = 0;
   el_trigsf_ElTrigSys_FullSim_corr8_down = 0;
   el_trigsf_ElTrigSys_FullSim_corr9_up = 0;
   el_trigsf_ElTrigSys_FullSim_corr9_down = 0;
   el_trigsf_ElTrigSys_uncorr_up = 0;
   el_trigsf_ElTrigSys_uncorr_down = 0;
   el_trigsf_ElTrigSys_uncorr_BinNumber = 0;
   el_corrected_pt_scaleUp_NP1 = 0;
   el_corrected_pt_scaleUp_NP2 = 0;
   el_corrected_pt_scaleUp_NP3 = 0;
   el_corrected_pt_scaleUp_NP4 = 0;
   el_corrected_pt_scaleUp_NP5 = 0;
   el_corrected_pt_scaleUp_NP6 = 0;
   el_corrected_pt_scaleUp_NP7 = 0;
   el_corrected_pt_scaleUp_NP8 = 0;
   el_corrected_pt_scaleUp_NP9 = 0;
   el_corrected_pt_scaleUp_NP10 = 0;
   el_corrected_pt_scaleUp_NP11 = 0;
   el_corrected_pt_scaleUp_NP12 = 0;
   el_corrected_pt_scaleUp_NP13 = 0;
   el_corrected_pt_scaleUp_NP14 = 0;
   el_corrected_pt_scaleUp_NP15 = 0;
   el_corrected_pt_scaleUp_NP16 = 0;
   el_corrected_pt_scaleUp_NP17 = 0;
   el_corrected_pt_scaleUp_NP18 = 0;
   el_corrected_pt_scaleUp_NP19 = 0;
   el_corrected_pt_scaleUp_NP20 = 0;
   el_corrected_pt_scaleUp_NP21 = 0;
   el_corrected_pt_scaleUp_NP22 = 0;
   el_corrected_pt_scaleUp_NP23 = 0;
   el_corrected_pt_scaleUp_NP24 = 0;
   el_corrected_pt_scaleDown_NP1 = 0;
   el_corrected_pt_scaleDown_NP2 = 0;
   el_corrected_pt_scaleDown_NP3 = 0;
   el_corrected_pt_scaleDown_NP4 = 0;
   el_corrected_pt_scaleDown_NP5 = 0;
   el_corrected_pt_scaleDown_NP6 = 0;
   el_corrected_pt_scaleDown_NP7 = 0;
   el_corrected_pt_scaleDown_NP8 = 0;
   el_corrected_pt_scaleDown_NP9 = 0;
   el_corrected_pt_scaleDown_NP10 = 0;
   el_corrected_pt_scaleDown_NP11 = 0;
   el_corrected_pt_scaleDown_NP12 = 0;
   el_corrected_pt_scaleDown_NP13 = 0;
   el_corrected_pt_scaleDown_NP14 = 0;
   el_corrected_pt_scaleDown_NP15 = 0;
   el_corrected_pt_scaleDown_NP16 = 0;
   el_corrected_pt_scaleDown_NP17 = 0;
   el_corrected_pt_scaleDown_NP18 = 0;
   el_corrected_pt_scaleDown_NP19 = 0;
   el_corrected_pt_scaleDown_NP20 = 0;
   el_corrected_pt_scaleDown_NP21 = 0;
   el_corrected_pt_scaleDown_NP22 = 0;
   el_corrected_pt_scaleDown_NP23 = 0;
   el_corrected_pt_scaleDown_NP24 = 0;
   el_corrected_pt_cUp_NP1 = 0;
   el_corrected_pt_cUp_NP2 = 0;
   el_corrected_pt_cUp_NP3 = 0;
   el_corrected_pt_cUp_NP4 = 0;
   el_corrected_pt_cUp_NP5 = 0;
   el_corrected_pt_cUp_NP6 = 0;
   el_corrected_pt_cUp_NP7 = 0;
   el_corrected_pt_cUp_NP8 = 0;
   el_corrected_pt_cUp_NP9 = 0;
   el_corrected_pt_cUp_NP10 = 0;
   el_corrected_pt_cUp_NP11 = 0;
   el_corrected_pt_cUp_NP12 = 0;
   el_corrected_pt_cUp_NP13 = 0;
   el_corrected_pt_cUp_NP14 = 0;
   el_corrected_pt_cUp_NP15 = 0;
   el_corrected_pt_cUp_NP16 = 0;
   el_corrected_pt_cUp_NP17 = 0;
   el_corrected_pt_cUp_NP18 = 0;
   el_corrected_pt_cUp_NP19 = 0;
   el_corrected_pt_cUp_NP20 = 0;
   el_corrected_pt_cUp_NP21 = 0;
   el_corrected_pt_cUp_NP22 = 0;
   el_corrected_pt_cUp_NP23 = 0;
   el_corrected_pt_cUp_NP24 = 0;
   el_corrected_pt_cDown_NP1 = 0;
   el_corrected_pt_cDown_NP2 = 0;
   el_corrected_pt_cDown_NP3 = 0;
   el_corrected_pt_cDown_NP4 = 0;
   el_corrected_pt_cDown_NP5 = 0;
   el_corrected_pt_cDown_NP6 = 0;
   el_corrected_pt_cDown_NP7 = 0;
   el_corrected_pt_cDown_NP8 = 0;
   el_corrected_pt_cDown_NP9 = 0;
   el_corrected_pt_cDown_NP10 = 0;
   el_corrected_pt_cDown_NP11 = 0;
   el_corrected_pt_cDown_NP12 = 0;
   el_corrected_pt_cDown_NP13 = 0;
   el_corrected_pt_cDown_NP14 = 0;
   el_corrected_pt_cDown_NP15 = 0;
   el_corrected_pt_cDown_NP16 = 0;
   el_corrected_pt_cDown_NP17 = 0;
   el_corrected_pt_cDown_NP18 = 0;
   el_corrected_pt_cDown_NP19 = 0;
   el_corrected_pt_cDown_NP20 = 0;
   el_corrected_pt_cDown_NP21 = 0;
   el_corrected_pt_cDown_NP22 = 0;
   el_corrected_pt_cDown_NP23 = 0;
   el_corrected_pt_cDown_NP24 = 0;
   fwdel_pt = 0;
   fwdel_eta = 0;
   fwdel_phi = 0;
   incl_mu_pt = 0;
   incl_mu_ptloss = 0;
   incl_mu_eta = 0;
   incl_mu_phi = 0;
   incl_mu_d0sig = 0;
   incl_mu_delta_z0 = 0;
   u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_UP = 0;
   u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_UP = 0;
   sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_UP = 0;
   u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_DOWN = 0;
   u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_DOWN = 0;
   sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_DOWN = 0;
   u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_UP = 0;
   u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_UP = 0;
   sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_UP = 0;
   u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_DOWN = 0;
   u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_DOWN = 0;
   sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_DOWN = 0;
   u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_UP = 0;
   u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_UP = 0;
   sumetweight_el_loose_pfoEM_RESPONSE_STAT0_UP = 0;
   u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_DOWN = 0;
   u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_DOWN = 0;
   sumetweight_el_loose_pfoEM_RESPONSE_STAT0_DOWN = 0;
   u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_UP = 0;
   u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_UP = 0;
   sumetweight_el_loose_pfoEM_RESPONSE_STAT1_UP = 0;
   u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_DOWN = 0;
   u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_DOWN = 0;
   sumetweight_el_loose_pfoEM_RESPONSE_STAT1_DOWN = 0;
   u_corrected_pt_el_medium_pfoEM_RESOLUTION_STAT0_UP = 0;
   u_corrected_phi_el_medium_pfoEM_RESOLUTION_STAT0_UP = 0;
   sumetweight_el_medium_pfoEM_RESOLUTION_STAT0_UP = 0;
   u_corrected_pt_el_medium_pfoEM_RESOLUTION_STAT0_DOWN = 0;
   u_corrected_phi_el_medium_pfoEM_RESOLUTION_STAT0_DOWN = 0;
   sumetweight_el_medium_pfoEM_RESOLUTION_STAT0_DOWN = 0;
   u_corrected_pt_el_medium_pfoEM_RESOLUTION_STAT1_UP = 0;
   u_corrected_phi_el_medium_pfoEM_RESOLUTION_STAT1_UP = 0;
   sumetweight_el_medium_pfoEM_RESOLUTION_STAT1_UP = 0;
   u_corrected_pt_el_medium_pfoEM_RESOLUTION_STAT1_DOWN = 0;
   u_corrected_phi_el_medium_pfoEM_RESOLUTION_STAT1_DOWN = 0;
   sumetweight_el_medium_pfoEM_RESOLUTION_STAT1_DOWN = 0;
   u_corrected_pt_el_medium_pfoEM_RESPONSE_STAT0_UP = 0;
   u_corrected_phi_el_medium_pfoEM_RESPONSE_STAT0_UP = 0;
   sumetweight_el_medium_pfoEM_RESPONSE_STAT0_UP = 0;
   u_corrected_pt_el_medium_pfoEM_RESPONSE_STAT0_DOWN = 0;
   u_corrected_phi_el_medium_pfoEM_RESPONSE_STAT0_DOWN = 0;
   sumetweight_el_medium_pfoEM_RESPONSE_STAT0_DOWN = 0;
   u_corrected_pt_el_medium_pfoEM_RESPONSE_STAT1_UP = 0;
   u_corrected_phi_el_medium_pfoEM_RESPONSE_STAT1_UP = 0;
   sumetweight_el_medium_pfoEM_RESPONSE_STAT1_UP = 0;
   u_corrected_pt_el_medium_pfoEM_RESPONSE_STAT1_DOWN = 0;
   u_corrected_phi_el_medium_pfoEM_RESPONSE_STAT1_DOWN = 0;
   sumetweight_el_medium_pfoEM_RESPONSE_STAT1_DOWN = 0;
   tlep_dressed_pt = 0;
   tlep_dressed_eta = 0;
   tlep_dressed_phi = 0;
   tlep_dressed_e = 0;
   tlep_dressed_pdgId = 0;
   tlep_bare_pt = 0;
   tlep_bare_eta = 0;
   tlep_bare_phi = 0;
   tlep_bare_e = 0;
   tlep_bare_pdgId = 0;
   tlep_born_pt = 0;
   tlep_born_eta = 0;
   tlep_born_phi = 0;
   tlep_born_e = 0;
   tlep_born_pdgId = 0;
   tneutrino_pt = 0;
   tneutrino_eta = 0;
   tneutrino_phi = 0;
   tneutrino_e = 0;
   tneutrino_pdgId = 0;
   tbornneutrino_pt = 0;
   tbornneutrino_eta = 0;
   tbornneutrino_phi = 0;
   tbornneutrino_e = 0;
   tbornneutrino_pdgId = 0;
   tphoton_pt = 0;
   tphoton_eta = 0;
   tphoton_phi = 0;
   tphoton_e = 0;
   tjet_pt = 0;
   tjet_eta = 0;
   tjet_phi = 0;
   tjet_e = 0;

}
#endif
