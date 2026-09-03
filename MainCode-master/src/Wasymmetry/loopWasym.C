#define loopWasym_cxx
#include <iostream>
#include "Wasymmetry/loopWasym.h"

using namespace std;

loopWasym::loopWasym(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopWasym::InputHist(HistsWasym* &myhists)
{
 this->myhists = myhists;

}

void loopWasym::InputTree(TreeForWasym *WasymTree)
{
 this->WasymTree = WasymTree;
 this->RootNames = WasymTree->RootNames;

 this->FirstFile = WasymTree->FirstFile;
 this->EndFile = WasymTree->EndFile;

 this->RootTypes = WasymTree->RootTypes;
 this->CrossSections = WasymTree->CrossSections;
 this->SumOfWeights = WasymTree->SumOfWeights;

 this->OneFilePerJob = WasymTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = WasymTree->TotalEntries[ifile];
 }

}

void loopWasym::RunAllSystematic()
{
 OnlyNominal = false;
}

void loopWasym::ReadTree(int ifile)
{
 bool isSignal = false;

 int MCType = RootTypes.at(ifile);
 TotalWeight = Lumi * CrossSections.at(ifile) / SumOfWeights.at(ifile);

 isWplusenuEvent = false;
 isWplusmunuEvent = false;
 isWplustaonuEvent = false;
 isWminusenuEvent = false;
 isWminusmunuEvent = false;
 isWminustaonuEvent = false;
 isZeeEvent = false;
 isZmumuEvent = false;
 isData = false;

 if(MCType == 361100) isWplusenuEvent = true;
 if(MCType == 361101) isWplusmunuEvent = true;
 if(MCType == 361102) isWplustaonuEvent = true;
 if(MCType == 361103) isWminusenuEvent = true;
 if(MCType == 361104) isWminusmunuEvent = true;
 if(MCType == 361105) isWminustaonuEvent = true;
 if(MCType == 361106) isZeeEvent = true;
 if(MCType == 361107) isZmumuEvent = true;
 if(MCType == -1) isData = true;

 for(int ibkghist = 0; ibkghist < myhists->BkgHist_1d.size(); ibkghist++){
   myhists->BkgHist_1d.at(ibkghist)->at(iThread - 1)->Initial(MCType);
 }

 if(isData) TotalWeight = 1.0;

 isElectron = false;
 isMuon = false;
 if(isWplusenuEvent || isWminusenuEvent || isZeeEvent) isElectron = true;
 if(isWplusmunuEvent || isWminusmunuEvent || isZmumuEvent) isMuon = true;
 if(isElectron || isMuon) isSignal = true;

 if(isTest) cout<<endl;
 if(isTest) cout<<"Root Type is "<<MCType<<endl;
 if(isTest) cout<<"Total Weight is "<<TotalWeight<<endl;
 if(isTest) cout<<endl;

 //Start loop
 for(int iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){ 
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }
  
   WasymTree->GetEntry(ifile, iEvent);


   //Define Parameters
   DefaultEvent.el_pt = WasymTree->el_corrected_pt;
   DefaultEvent.el_eta = WasymTree->el_eta;
   DefaultEvent.el_phi = WasymTree->el_phi;
   DefaultEvent.el_delta_z0 = WasymTree->el_delta_z0;
   DefaultEvent.el_d0sig = WasymTree->el_d0sig;
   DefaultEvent.el_isMedium = WasymTree->el_isMedium;
   DefaultEvent.el_charge = WasymTree->el_charge;
   DefaultEvent.el_trigMatch = WasymTree->el_trigMatch;
   DefaultEvent.el_isolation_ptvarcone20 = WasymTree->el_isolation_ptvarcone20;

   DefaultEvent.el_recosf = WasymTree->el_recosf;
   DefaultEvent.el_idsf = WasymTree->el_idsf;
   DefaultEvent.el_isosf = WasymTree->el_isosf;
   DefaultEvent.el_trigsf = WasymTree->el_trigsf;
   DefaultEvent.el_trigmceff = WasymTree->el_trigmceff;

   DefaultEvent.mu_pt = WasymTree->mu_corrected_pt;
   DefaultEvent.mu_eta = WasymTree->mu_eta;
   DefaultEvent.mu_phi = WasymTree->mu_phi;
   DefaultEvent.mu_delta_z0 = WasymTree->mu_delta_z0;
   DefaultEvent.mu_d0sig = WasymTree->mu_d0sig;
   DefaultEvent.mu_charge = WasymTree->mu_charge;
   DefaultEvent.mu_trigMatch = WasymTree->mu_trigMatch;
   DefaultEvent.mu_isolation_ptvarcone20 = WasymTree->mu_isolation_ptvarcone20;

   DefaultEvent.mu_recosf = WasymTree->mu_recosf;
   DefaultEvent.mu_ttvasf = WasymTree->mu_ttvasf;
   DefaultEvent.mu_isosf = WasymTree->mu_isosf;
   DefaultEvent.mu_trigsf = WasymTree->mu_trigsf;
   DefaultEvent.mu_trigmceff = WasymTree->mu_trigmceff;

   if(MCType == -1){
     DefaultEvent.Recoil = WasymTree->u_pt_el_loose_pfoEM;
     DefaultEvent.Recoil_Phi = WasymTree->u_phi_el_loose_pfoEM;
     DefaultEvent.SumETWeight = 1.0;
   }
   if(isSignal){
     DefaultEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM;
     DefaultEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM;
     DefaultEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM;
   }
   if(MCType != -1 && !isSignal){
     DefaultEvent.Recoil = WasymTree->u_pt_el_loose_pfoEM;
     DefaultEvent.Recoil_Phi = WasymTree->u_phi_el_loose_pfoEM;
     DefaultEvent.SumETWeight = 1.0;
   }

   DefaultEvent.el_inrecoil = WasymTree->el_inrecoil;
   DefaultEvent.mu_inrecoil = WasymTree->mu_inrecoil;

   DefaultEvent.EventWeight_gen = WasymTree->EventWeight_gen;
   DefaultEvent.EventWeight_vertex = WasymTree->EventWeight_vertex;

   if(MCType != -1){
     DefaultEvent.Truth_Lepton_Pt = WasymTree->tlep_born_pt;
     DefaultEvent.Truth_Lepton_Eta = WasymTree->tlep_born_eta;
     DefaultEvent.Truth_Lepton_Phi = WasymTree->tlep_born_phi;
     DefaultEvent.Truth_Lepton_E = WasymTree->tlep_born_e;
     DefaultEvent.Truth_Lepton_ID = WasymTree->tlep_born_pdgId;

     DefaultEvent.Truth_Neutrino_Pt = WasymTree->tbornneutrino_pt;
     DefaultEvent.Truth_Neutrino_Eta = WasymTree->tbornneutrino_eta;
     DefaultEvent.Truth_Neutrino_Phi = WasymTree->tbornneutrino_phi;
     DefaultEvent.Truth_Neutrino_E = WasymTree->tbornneutrino_e;
     DefaultEvent.Truth_Neutrino_ID = WasymTree->tbornneutrino_pdgId;
   }


   //Start Selection
   if(OnlyNominal){
     ProcessEvent = DefaultEvent;
     TruthWenuSelection(MCType, &ProcessEvent);
     TruthWmunuSelection(MCType, &ProcessEvent);

     WenuSelection(MCType, "Nominal", &ProcessEvent);
     WmunuSelection(MCType, "Nominal", &ProcessEvent);
     ZeeSelection(MCType, "Nominal", &ProcessEvent);
     ZmumuSelection(MCType, "Nominal", &ProcessEvent);

   }
   if(!OnlyNominal){
     ProcessEvent = DefaultEvent;
     TruthWenuSelection(MCType, &ProcessEvent);
     TruthWmunuSelection(MCType, &ProcessEvent);

     //W Signal Electron
     ProcessEvent = DefaultEvent;
     WenuSelection(MCType, "Nominal", &ProcessEvent);

     if(MCType == 361100 || MCType == 361103){
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1down;
       WenuSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1down", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1up;
       WenuSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1up", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1down;
       WenuSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1down", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1up;
       WenuSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1up", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1down;
       WenuSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1down", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1up;
       WenuSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1up", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1down;
       WenuSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1down", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1up;
       WenuSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1up", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1down;
       WenuSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1down", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1up;
       WenuSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1up", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1down;
       WenuSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1down", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1up;
       WenuSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1up", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_down;
       WenuSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_down", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_up;
       WenuSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_up", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_down;
       WenuSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_down", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_up;
       WenuSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_up", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_down;
       WenuSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_down", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_up;
       WenuSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_up", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_down;
       WenuSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_down", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_up;
       WenuSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_up", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_uncorr_up;
       WenuSelection(MCType, "isosf_ElIsoSys_uncorr_up", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_uncorr_down;
       WenuSelection(MCType, "isosf_ElIsoSys_uncorr_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_down;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_up;
       WenuSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_uncorr_up;
       WenuSelection(MCType, "idsf_ElIDSys_uncorr_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_uncorr_down;
       WenuSelection(MCType, "idsf_ElIDSys_uncorr_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr8_down;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr8_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr8_up;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr8_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr9_down;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr9_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr9_up;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr9_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr10_down;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr10_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr10_up;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr10_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr11_down;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr11_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr11_up;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr11_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr12_down;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr12_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr12_up;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr12_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr13_down;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr13_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr13_up;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr13_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr14_down;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr14_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr14_up;
       WenuSelection(MCType, "trigsf_ElTrigSys_FullSim_corr14_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_uncorr_up;
       WenuSelection(MCType, "trigsf_ElTrigSys_uncorr_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_uncorr_down;
       WenuSelection(MCType, "trigsf_ElTrigSys_uncorr_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP1;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP1", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP1;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP1", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP2;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP2", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP2;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP2", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP3;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP3", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP3;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP3", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP4;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP4", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP4;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP4", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP5;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP5", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP5;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP5", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP6;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP6", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP6;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP6", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP7;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP7", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP7;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP7", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP8;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP8", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP8;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP8", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP9;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP9", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP9;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP9", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP10;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP10", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP10;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP10", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP11;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP11", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP11;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP11", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP12;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP12", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP12;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP12", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP13;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP13", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP13;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP13", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP14;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP14", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP14;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP14", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP15;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP15", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP15;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP15", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP16;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP16", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP16;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP16", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP17;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP17", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP17;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP17", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP18;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP18", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP18;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP18", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP19;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP19", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP19;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP19", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP20;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP20", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP20;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP20", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP21;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP21", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP21;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP21", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP22;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP22", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP22;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP22", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP23;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP23", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP23;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP23", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP24;
       WenuSelection(MCType, "corrected_pt_scaleDown_NP24", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP24;
       WenuSelection(MCType, "corrected_pt_scaleUp_NP24", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP1;
       WenuSelection(MCType, "corrected_pt_cDown_NP1", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP1;
       WenuSelection(MCType, "corrected_pt_cUp_NP1", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP2;
       WenuSelection(MCType, "corrected_pt_cDown_NP2", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP2;
       WenuSelection(MCType, "corrected_pt_cUp_NP2", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP3;
       WenuSelection(MCType, "corrected_pt_cDown_NP3", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP3;
       WenuSelection(MCType, "corrected_pt_cUp_NP3", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP4;
       WenuSelection(MCType, "corrected_pt_cDown_NP4", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP4;
       WenuSelection(MCType, "corrected_pt_cUp_NP4", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP5;
       WenuSelection(MCType, "corrected_pt_cDown_NP5", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP5;
       WenuSelection(MCType, "corrected_pt_cUp_NP5", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP6;
       WenuSelection(MCType, "corrected_pt_cDown_NP6", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP6;
       WenuSelection(MCType, "corrected_pt_cUp_NP6", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP7;
       WenuSelection(MCType, "corrected_pt_cDown_NP7", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP7;
       WenuSelection(MCType, "corrected_pt_cUp_NP7", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP8;
       WenuSelection(MCType, "corrected_pt_cDown_NP8", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP8;
       WenuSelection(MCType, "corrected_pt_cUp_NP8", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP9;
       WenuSelection(MCType, "corrected_pt_cDown_NP9", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP9;
       WenuSelection(MCType, "corrected_pt_cUp_NP9", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP10;
       WenuSelection(MCType, "corrected_pt_cDown_NP10", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP10;
       WenuSelection(MCType, "corrected_pt_cUp_NP10", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP11;
       WenuSelection(MCType, "corrected_pt_cDown_NP11", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP11;
       WenuSelection(MCType, "corrected_pt_cUp_NP11", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP12;
       WenuSelection(MCType, "corrected_pt_cDown_NP12", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP12;
       WenuSelection(MCType, "corrected_pt_cUp_NP12", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP13;
       WenuSelection(MCType, "corrected_pt_cDown_NP13", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP13;
       WenuSelection(MCType, "corrected_pt_cUp_NP13", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP14;
       WenuSelection(MCType, "corrected_pt_cDown_NP14", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP14;
       WenuSelection(MCType, "corrected_pt_cUp_NP14", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP15;
       WenuSelection(MCType, "corrected_pt_cDown_NP15", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP15;
       WenuSelection(MCType, "corrected_pt_cUp_NP15", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP16;
       WenuSelection(MCType, "corrected_pt_cDown_NP16", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP16;
       WenuSelection(MCType, "corrected_pt_cUp_NP16", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP17;
       WenuSelection(MCType, "corrected_pt_cDown_NP17", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP17;
       WenuSelection(MCType, "corrected_pt_cUp_NP17", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP18;
       WenuSelection(MCType, "corrected_pt_cDown_NP18", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP18;
       WenuSelection(MCType, "corrected_pt_cUp_NP18", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP19;
       WenuSelection(MCType, "corrected_pt_cDown_NP19", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP19;
       WenuSelection(MCType, "corrected_pt_cUp_NP19", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP20;
       WenuSelection(MCType, "corrected_pt_cDown_NP20", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP20;
       WenuSelection(MCType, "corrected_pt_cUp_NP20", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP21;
       WenuSelection(MCType, "corrected_pt_cDown_NP21", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP21;
       WenuSelection(MCType, "corrected_pt_cUp_NP21", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP22;
       WenuSelection(MCType, "corrected_pt_cDown_NP22", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP22;
       WenuSelection(MCType, "corrected_pt_cUp_NP22", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP23;
       WenuSelection(MCType, "corrected_pt_cDown_NP23", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP23;
       WenuSelection(MCType, "corrected_pt_cUp_NP23", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP24;
       WenuSelection(MCType, "corrected_pt_cDown_NP24", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP24;
       WenuSelection(MCType, "corrected_pt_cUp_NP24", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       for(int iRecoilSys = 0; iRecoilSys < 14; iRecoilSys++){
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_DOWN->at(iRecoilSys);
         WenuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_UP->at(iRecoilSys);
         WenuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT0_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_DOWN->at(iRecoilSys);
         WenuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_UP->at(iRecoilSys);
         WenuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT1_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
       }

       ProcessEvent = DefaultEvent;

       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
       WenuSelection(MCType, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_DOWN", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
       WenuSelection(MCType, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_UP", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       for(int iRecoilSys = 0; iRecoilSys < 15; iRecoilSys++){
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT0_DOWN->at(iRecoilSys);
         WenuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT0_UP->at(iRecoilSys);
         WenuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT0_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT1_DOWN->at(iRecoilSys);
         WenuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT1_UP->at(iRecoilSys);
         WenuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT1_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
       }

       ProcessEvent = DefaultEvent;

       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
       WenuSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_DOWN", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
       WenuSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_UP", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_SYS_DOWN;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_SYS_DOWN;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_SYS_DOWN;
       WenuSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_SYS_DOWN", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_SYS_UP;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_SYS_UP;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_SYS_UP;
       WenuSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_SYS_UP", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_SET_SYS;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_SET_SYS;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_SET_SYS;
       WenuSelection(MCType, "Recoil_loose_pfoEM_SET_SYS", &ProcessEvent);
     }


     //W Signal Muon
     ProcessEvent = DefaultEvent;
     WmunuSelection(MCType, "Nominal", &ProcessEvent);

     if(MCType == 361101 || MCType == 361104){
       ProcessEvent.mu_pt = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down;
       WmunuSelection(MCType, "syspt_MUON_ID__1down", &ProcessEvent);
       ProcessEvent.mu_pt = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up;
       WmunuSelection(MCType, "syspt_MUON_ID__1up", &ProcessEvent);
       ProcessEvent.mu_pt = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_down;
       WmunuSelection(MCType, "syspt_MUON_MS__1down", &ProcessEvent);
       ProcessEvent.mu_pt = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_up;
       WmunuSelection(MCType, "syspt_MUON_MS__1up", &ProcessEvent);
       ProcessEvent.mu_pt = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_down;
       WmunuSelection(MCType, "syspt_MUON_SCALE__1down", &ProcessEvent);
       ProcessEvent.mu_pt = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_up;
       WmunuSelection(MCType, "syspt_MUON_SCALE__1up", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_QCDTEMPLATE_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_QCDTEMPLATE_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_down;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_BKGFRACTION_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_up;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_BKGFRACTION_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_down;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_LUMIUNCERT_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_up;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_LUMIUNCERT_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_down;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_MCXSEC_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_up;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_MCXSEC_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_down;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_SUPRESSIONSCALE_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_up;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_SUPRESSIONSCALE_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_MATCHING_SYM_down;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_MATCHING_SYM_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_MATCHING_SYM_up;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_MATCHING_SYM_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_TRUTH_SYM_down;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_TRUTH_SYM_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_TRUTH_SYM_up;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_TRUTH_SYM_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_down;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_up;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_PtDEPENDENCY_down;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_PtDEPENDENCY_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_PtDEPENDENCY_up;
       WmunuSelection(MCType, "recosf_MuRecoSys_corr_PtDEPENDENCY_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_uncorr_up;
       WmunuSelection(MCType, "recosf_MuRecoSys_uncorr_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_uncorr_down;
       WmunuSelection(MCType, "recosf_MuRecoSys_uncorr_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_eta_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_eta_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_down;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_mass_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_up;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_mass_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_down;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_tpdR_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_up;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_tpdR_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_down;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_isoBkg_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_up;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_isoBkg_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_down;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_probeQ_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_up;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_probeQ_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_MATCHING_SYM_down;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_tagIsol_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_MATCHING_SYM_up;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_tagIsol_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_TRUTH_SYM_down;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_dRmuj_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_TRUTH_SYM_up;
       WmunuSelection(MCType, "isosf_MuIsoSys_corr_dRmuj_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_down;
       WmunuSelection(MCType, "isosf_MuIsoSys_uncorr_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_up;
       WmunuSelection(MCType, "isosf_MuIsoSys_uncorr_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down;
       WmunuSelection(MCType, "ttvasf_MuTTVASys_corr_QCDTEMPLATE_down", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up;
       WmunuSelection(MCType, "ttvasf_MuTTVASys_corr_QCDTEMPLATE_up", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_down;
       WmunuSelection(MCType, "ttvasf_MuTTVASys_corr_LUMIUNCERT_down", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_up;
       WmunuSelection(MCType, "ttvasf_MuTTVASys_corr_LUMIUNCERT_up", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_down;
       WmunuSelection(MCType, "ttvasf_MuTTVASys_corr_BKGFRACTION_down", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_up;
       WmunuSelection(MCType, "ttvasf_MuTTVASys_corr_BKGFRACTION_up", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_down;
       WmunuSelection(MCType, "ttvasf_MuTTVASys_corr_MCXSEC_down", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_up;
       WmunuSelection(MCType, "ttvasf_MuTTVASys_corr_MCXSEC_up", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_down;
       WmunuSelection(MCType, "ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_down", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_up;
       WmunuSelection(MCType, "ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_up", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_MATCHING_SYM_down;
       WmunuSelection(MCType, "ttvasf_MuTTVASys_uncorr_up", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_MATCHING_SYM_up;
       WmunuSelection(MCType, "ttvasf_MuTTVASys_uncorr_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down;
       WmunuSelection(MCType, "trigsf_MuTrigSys_PtEta_corr_iso_loose_avg", &ProcessEvent);
       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up;
       WmunuSelection(MCType, "trigsf_MuTrigSys_PtEta_corr_dPhi_avg", &ProcessEvent);
       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_down;
       WmunuSelection(MCType, "trigsf_MuTrigSys_PtEta_corr_noIP_avg", &ProcessEvent);
       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_up;
       WmunuSelection(MCType, "trigsf_MuTrigSys_PtEta_corr_iso_tight_avg", &ProcessEvent);
       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_down;
       WmunuSelection(MCType, "trigsf_MuTrigSys_PtEta_corr_mlltight_avg", &ProcessEvent);
       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_up;
       WmunuSelection(MCType, "trigsf_MuTrigSys_PtEta_up", &ProcessEvent);
       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_down;
       WmunuSelection(MCType, "trigsf_MuTrigSys_PtEta_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       for(int iRecoilSys = 0; iRecoilSys < 14; iRecoilSys++){
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_DOWN->at(iRecoilSys);
         WmunuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_UP->at(iRecoilSys);
         WmunuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT0_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_DOWN->at(iRecoilSys);
         WmunuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_UP->at(iRecoilSys);
         WmunuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT1_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
       }

       ProcessEvent = DefaultEvent;

       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
       WmunuSelection(MCType, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_DOWN", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
       WmunuSelection(MCType, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_UP", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       for(int iRecoilSys = 0; iRecoilSys < 15; iRecoilSys++){
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT0_DOWN->at(iRecoilSys);
         WmunuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT0_UP->at(iRecoilSys);
         WmunuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT0_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT1_DOWN->at(iRecoilSys);
         WmunuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT1_UP->at(iRecoilSys);
         WmunuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT1_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
       }

       ProcessEvent = DefaultEvent;

       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
       WmunuSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_DOWN", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
       WmunuSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_UP", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_SYS_DOWN;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_SYS_DOWN;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_SYS_DOWN;
       WmunuSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_SYS_DOWN", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_SYS_UP;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_SYS_UP;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_SYS_UP;
       WmunuSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_SYS_UP", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_SET_SYS;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_SET_SYS;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_SET_SYS;
       WmunuSelection(MCType, "Recoil_loose_pfoEM_SET_SYS", &ProcessEvent);
     }


     //Z Signal Electron
     ProcessEvent = DefaultEvent;
     ZeeSelection(MCType, "Nominal", &ProcessEvent);

     if(MCType == 361106){
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1down;
       ZeeSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1down", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1up;
       ZeeSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP0__1up", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1down;
       ZeeSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1down", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1up;
       ZeeSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP1__1up", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1down;
       ZeeSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1down", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1up;
       ZeeSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP2__1up", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1down;
       ZeeSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1down", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1up;
       ZeeSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP3__1up", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1down;
       ZeeSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1down", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1up;
       ZeeSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP4__1up", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1down;
       ZeeSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1down", &ProcessEvent);
       ProcessEvent.el_recosf = WasymTree->el_sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1up;
       ZeeSelection(MCType, "sysrecosf_EL_EFF_Reco_CorrUncertaintyNP5__1up", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_down;
       ZeeSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_down", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_up;
       ZeeSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr11_up", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_down;
       ZeeSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_down", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_up;
       ZeeSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr12_up", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_down;
       ZeeSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_down", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_up;
       ZeeSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr13_up", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_down;
       ZeeSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_down", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_up;
       ZeeSelection(MCType, "isosf_ElIsoSys_FullSim_FixedCutLoose_corr14_up", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_uncorr_up;
       ZeeSelection(MCType, "isosf_ElIsoSys_uncorr_up", &ProcessEvent);
       ProcessEvent.el_isosf = WasymTree->el_isosf_ElIsoSys_uncorr_down;
       ZeeSelection(MCType, "isosf_ElIsoSys_uncorr_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr1_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr2_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr3_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr4_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr5_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr6_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr7_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr8_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr9_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr10_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr11_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr12_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr13_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_down;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_down", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_up;
       ZeeSelection(MCType, "idsf_ElIDSys_FullSim_MediumLLH_d0z0_corr14_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_uncorr_up;
       ZeeSelection(MCType, "idsf_ElIDSys_uncorr_up", &ProcessEvent);
       ProcessEvent.el_idsf = WasymTree->el_idsf_ElIDSys_uncorr_down;
       ZeeSelection(MCType, "idsf_ElIDSys_uncorr_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr8_down;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr8_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr8_up;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr8_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr9_down;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr9_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr9_up;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr9_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr10_down;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr10_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr10_up;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr10_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr11_down;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr11_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr11_up;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr11_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr12_down;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr12_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr12_up;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr12_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr13_down;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr13_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr13_up;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr13_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr14_down;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr14_down", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_FullSim_corr14_up;
       ZeeSelection(MCType, "trigsf_ElTrigSys_FullSim_corr14_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_uncorr_up;
       ZeeSelection(MCType, "trigsf_ElTrigSys_uncorr_up", &ProcessEvent);
       ProcessEvent.el_trigsf = WasymTree->el_trigsf_ElTrigSys_uncorr_down;
       ZeeSelection(MCType, "trigsf_ElTrigSys_uncorr_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP1;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP1", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP1;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP1", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP2;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP2", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP2;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP2", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP3;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP3", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP3;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP3", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP4;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP4", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP4;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP4", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP5;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP5", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP5;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP5", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP6;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP6", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP6;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP6", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP7;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP7", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP7;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP7", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP8;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP8", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP8;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP8", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP9;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP9", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP9;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP9", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP10;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP10", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP10;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP10", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP11;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP11", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP11;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP11", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP12;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP12", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP12;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP12", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP13;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP13", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP13;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP13", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP14;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP14", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP14;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP14", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP15;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP15", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP15;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP15", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP16;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP16", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP16;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP16", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP17;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP17", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP17;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP17", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP18;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP18", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP18;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP18", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP19;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP19", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP19;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP19", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP20;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP20", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP20;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP20", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP21;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP21", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP21;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP21", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP22;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP22", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP22;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP22", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP23;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP23", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP23;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP23", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleDown_NP24;
       ZeeSelection(MCType, "corrected_pt_scaleDown_NP24", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_scaleUp_NP24;
       ZeeSelection(MCType, "corrected_pt_scaleUp_NP24", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP1;
       ZeeSelection(MCType, "corrected_pt_cDown_NP1", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP1;
       ZeeSelection(MCType, "corrected_pt_cUp_NP1", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP2;
       ZeeSelection(MCType, "corrected_pt_cDown_NP2", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP2;
       ZeeSelection(MCType, "corrected_pt_cUp_NP2", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP3;
       ZeeSelection(MCType, "corrected_pt_cDown_NP3", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP3;
       ZeeSelection(MCType, "corrected_pt_cUp_NP3", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP4;
       ZeeSelection(MCType, "corrected_pt_cDown_NP4", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP4;
       ZeeSelection(MCType, "corrected_pt_cUp_NP4", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP5;
       ZeeSelection(MCType, "corrected_pt_cDown_NP5", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP5;
       ZeeSelection(MCType, "corrected_pt_cUp_NP5", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP6;
       ZeeSelection(MCType, "corrected_pt_cDown_NP6", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP6;
       ZeeSelection(MCType, "corrected_pt_cUp_NP6", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP7;
       ZeeSelection(MCType, "corrected_pt_cDown_NP7", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP7;
       ZeeSelection(MCType, "corrected_pt_cUp_NP7", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP8;
       ZeeSelection(MCType, "corrected_pt_cDown_NP8", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP8;
       ZeeSelection(MCType, "corrected_pt_cUp_NP8", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP9;
       ZeeSelection(MCType, "corrected_pt_cDown_NP9", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP9;
       ZeeSelection(MCType, "corrected_pt_cUp_NP9", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP10;
       ZeeSelection(MCType, "corrected_pt_cDown_NP10", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP10;
       ZeeSelection(MCType, "corrected_pt_cUp_NP10", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP11;
       ZeeSelection(MCType, "corrected_pt_cDown_NP11", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP11;
       ZeeSelection(MCType, "corrected_pt_cUp_NP11", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP12;
       ZeeSelection(MCType, "corrected_pt_cDown_NP12", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP12;
       ZeeSelection(MCType, "corrected_pt_cUp_NP12", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP13;
       ZeeSelection(MCType, "corrected_pt_cDown_NP13", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP13;
       ZeeSelection(MCType, "corrected_pt_cUp_NP13", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP14;
       ZeeSelection(MCType, "corrected_pt_cDown_NP14", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP14;
       ZeeSelection(MCType, "corrected_pt_cUp_NP14", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP15;
       ZeeSelection(MCType, "corrected_pt_cDown_NP15", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP15;
       ZeeSelection(MCType, "corrected_pt_cUp_NP15", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP16;
       ZeeSelection(MCType, "corrected_pt_cDown_NP16", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP16;
       ZeeSelection(MCType, "corrected_pt_cUp_NP16", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP17;
       ZeeSelection(MCType, "corrected_pt_cDown_NP17", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP17;
       ZeeSelection(MCType, "corrected_pt_cUp_NP17", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP18;
       ZeeSelection(MCType, "corrected_pt_cDown_NP18", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP18;
       ZeeSelection(MCType, "corrected_pt_cUp_NP18", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP19;
       ZeeSelection(MCType, "corrected_pt_cDown_NP19", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP19;
       ZeeSelection(MCType, "corrected_pt_cUp_NP19", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP20;
       ZeeSelection(MCType, "corrected_pt_cDown_NP20", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP20;
       ZeeSelection(MCType, "corrected_pt_cUp_NP20", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP21;
       ZeeSelection(MCType, "corrected_pt_cDown_NP21", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP21;
       ZeeSelection(MCType, "corrected_pt_cUp_NP21", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP22;
       ZeeSelection(MCType, "corrected_pt_cDown_NP22", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP22;
       ZeeSelection(MCType, "corrected_pt_cUp_NP22", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP23;
       ZeeSelection(MCType, "corrected_pt_cDown_NP23", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP23;
       ZeeSelection(MCType, "corrected_pt_cUp_NP23", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cDown_NP24;
       ZeeSelection(MCType, "corrected_pt_cDown_NP24", &ProcessEvent);
       ProcessEvent.el_pt = WasymTree->el_corrected_pt_cUp_NP24;
       ZeeSelection(MCType, "corrected_pt_cUp_NP24", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       for(int iRecoilSys = 0; iRecoilSys < 14; iRecoilSys++){
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_DOWN->at(iRecoilSys);
         ZeeSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_UP->at(iRecoilSys);
         ZeeSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT0_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_DOWN->at(iRecoilSys);
         ZeeSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_UP->at(iRecoilSys);
         ZeeSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT1_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
       }

       ProcessEvent = DefaultEvent;

       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
       ZeeSelection(MCType, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_DOWN", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
       ZeeSelection(MCType, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_UP", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       for(int iRecoilSys = 0; iRecoilSys < 15; iRecoilSys++){
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT0_DOWN->at(iRecoilSys);
         ZeeSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT0_UP->at(iRecoilSys);
         ZeeSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT0_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT1_DOWN->at(iRecoilSys);
         ZeeSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT1_UP->at(iRecoilSys);
         ZeeSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT1_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
       }

       ProcessEvent = DefaultEvent;

       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
       ZeeSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_DOWN", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
       ZeeSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_UP", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_SYS_DOWN;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_SYS_DOWN;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_SYS_DOWN;
       ZeeSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_SYS_DOWN", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_SYS_UP;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_SYS_UP;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_SYS_UP;
       ZeeSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_SYS_UP", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_SET_SYS;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_SET_SYS;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_SET_SYS;
       ZeeSelection(MCType, "Recoil_loose_pfoEM_SET_SYS", &ProcessEvent);
     }


     //Z Signal Muon
     ProcessEvent = DefaultEvent;
     ZmumuSelection(MCType, "Nominal", &ProcessEvent);

     if(MCType == 361107){
       ProcessEvent.mu_pt = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down;
       ZmumuSelection(MCType, "syspt_MUON_ID__1down", &ProcessEvent);
       ProcessEvent.mu_pt = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up;
       ZmumuSelection(MCType, "syspt_MUON_ID__1up", &ProcessEvent);
       ProcessEvent.mu_pt = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_down;
       ZmumuSelection(MCType, "syspt_MUON_MS__1down", &ProcessEvent);
       ProcessEvent.mu_pt = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_up;
       ZmumuSelection(MCType, "syspt_MUON_MS__1up", &ProcessEvent);
       ProcessEvent.mu_pt = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_down;
       ZmumuSelection(MCType, "syspt_MUON_SCALE__1down", &ProcessEvent);
       ProcessEvent.mu_pt = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_up;
       ZmumuSelection(MCType, "syspt_MUON_SCALE__1up", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_QCDTEMPLATE_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_QCDTEMPLATE_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_down;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_BKGFRACTION_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_up;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_BKGFRACTION_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_down;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_LUMIUNCERT_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_up;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_LUMIUNCERT_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_down;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_MCXSEC_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_up;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_MCXSEC_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_down;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_SUPRESSIONSCALE_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_up;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_SUPRESSIONSCALE_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_MATCHING_SYM_down;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_MATCHING_SYM_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_MATCHING_SYM_up;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_MATCHING_SYM_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_TRUTH_SYM_down;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_TRUTH_SYM_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_TRUTH_SYM_up;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_TRUTH_SYM_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_down;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_up;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_PtDEPENDENCY_down;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_PtDEPENDENCY_down", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_corr_PtDEPENDENCY_up;
       ZmumuSelection(MCType, "recosf_MuRecoSys_corr_PtDEPENDENCY_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_uncorr_up;
       ZmumuSelection(MCType, "recosf_MuRecoSys_uncorr_up", &ProcessEvent);
       ProcessEvent.mu_recosf = WasymTree->mu_recosf_MuRecoSys_uncorr_down;
       ZmumuSelection(MCType, "recosf_MuRecoSys_uncorr_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_eta_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_eta_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_down;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_mass_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_up;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_mass_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_down;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_tpdR_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_up;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_tpdR_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_down;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_isoBkg_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_up;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_isoBkg_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_down;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_probeQ_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_up;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_probeQ_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_MATCHING_SYM_down;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_tagIsol_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_MATCHING_SYM_up;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_tagIsol_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_TRUTH_SYM_down;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_dRmuj_down", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_TRUTH_SYM_up;
       ZmumuSelection(MCType, "isosf_MuIsoSys_corr_dRmuj_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_down;
       ZmumuSelection(MCType, "isosf_MuIsoSys_uncorr_up", &ProcessEvent);
       ProcessEvent.mu_isosf = WasymTree->mu_recosf_MuRecoSys_corr_HIGHTOLOWEXTRAPOLATION_up;
       ZmumuSelection(MCType, "isosf_MuIsoSys_uncorr_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down;
       ZmumuSelection(MCType, "ttvasf_MuTTVASys_corr_QCDTEMPLATE_down", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up;
       ZmumuSelection(MCType, "ttvasf_MuTTVASys_corr_QCDTEMPLATE_up", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_down;
       ZmumuSelection(MCType, "ttvasf_MuTTVASys_corr_LUMIUNCERT_down", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_up;
       ZmumuSelection(MCType, "ttvasf_MuTTVASys_corr_LUMIUNCERT_up", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_down;
       ZmumuSelection(MCType, "ttvasf_MuTTVASys_corr_BKGFRACTION_down", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_up;
       ZmumuSelection(MCType, "ttvasf_MuTTVASys_corr_BKGFRACTION_up", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_down;
       ZmumuSelection(MCType, "ttvasf_MuTTVASys_corr_MCXSEC_down", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_up;
       ZmumuSelection(MCType, "ttvasf_MuTTVASys_corr_MCXSEC_up", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_down;
       ZmumuSelection(MCType, "ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_down", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_SUPRESSIONSCALE_up;
       ZmumuSelection(MCType, "ttvasf_MuTTVASys_corr_SUPRESSIONSCALE_up", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_MATCHING_SYM_down;
       ZmumuSelection(MCType, "ttvasf_MuTTVASys_uncorr_up", &ProcessEvent);
       ProcessEvent.mu_ttvasf = WasymTree->mu_recosf_MuRecoSys_corr_MATCHING_SYM_up;
       ZmumuSelection(MCType, "ttvasf_MuTTVASys_uncorr_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_down;
       ZmumuSelection(MCType, "trigsf_MuTrigSys_PtEta_corr_iso_loose_avg", &ProcessEvent);
       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_QCDTEMPLATE_up;
       ZmumuSelection(MCType, "trigsf_MuTrigSys_PtEta_corr_dPhi_avg", &ProcessEvent);
       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_down;
       ZmumuSelection(MCType, "trigsf_MuTrigSys_PtEta_corr_noIP_avg", &ProcessEvent);
       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_BKGFRACTION_up;
       ZmumuSelection(MCType, "trigsf_MuTrigSys_PtEta_corr_iso_tight_avg", &ProcessEvent);
       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_down;
       ZmumuSelection(MCType, "trigsf_MuTrigSys_PtEta_corr_mlltight_avg", &ProcessEvent);
       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_LUMIUNCERT_up;
       ZmumuSelection(MCType, "trigsf_MuTrigSys_PtEta_up", &ProcessEvent);
       ProcessEvent.mu_trigsf = WasymTree->mu_recosf_MuRecoSys_corr_MCXSEC_down;
       ZmumuSelection(MCType, "trigsf_MuTrigSys_PtEta_down", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       for(int iRecoilSys = 0; iRecoilSys < 14; iRecoilSys++){
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_DOWN->at(iRecoilSys);
         ZmumuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT0_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT0_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT0_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT0_UP->at(iRecoilSys);
         ZmumuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT0_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_DOWN->at(iRecoilSys);
         ZmumuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT1_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_STAT1_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_STAT1_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_STAT1_UP->at(iRecoilSys);
         ZmumuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESOLUTION_STAT1_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
       }

       ProcessEvent = DefaultEvent;

       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_EXTSYS_DOWN;
       ZmumuSelection(MCType, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_DOWN", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESOLUTION_EXTSYS_UP;
       ZmumuSelection(MCType, "Recoil_loose_pfoEM_RESOLUTION_EXTSYS_UP", &ProcessEvent);

       ProcessEvent = DefaultEvent;

       for(int iRecoilSys = 0; iRecoilSys < 15; iRecoilSys++){
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT0_DOWN->at(iRecoilSys);
         ZmumuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT0_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT0_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT0_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT0_UP->at(iRecoilSys);
         ZmumuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT0_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_DOWN->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT1_DOWN->at(iRecoilSys);
         ZmumuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT1_DOWN" + (int)(iRecoilSys + 1), &ProcessEvent);
         ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_STAT1_UP->at(iRecoilSys);
         ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_STAT1_UP->at(iRecoilSys);
         ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_STAT1_UP->at(iRecoilSys);
         ZmumuSelection(MCType, (TString)"Recoil_loose_pfoEM_RESPONSE_STAT1_UP" + (int)(iRecoilSys + 1), &ProcessEvent);
       }

       ProcessEvent = DefaultEvent;

       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_EXTSYS_DOWN;
       ZmumuSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_DOWN", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_EXTSYS_UP;
       ZmumuSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_EXTSYS_UP", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_SYS_DOWN;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_SYS_DOWN;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_SYS_DOWN;
       ZmumuSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_SYS_DOWN", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_RESPONSE_SYS_UP;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_RESPONSE_SYS_UP;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_RESPONSE_SYS_UP;
       ZmumuSelection(MCType, "Recoil_loose_pfoEM_RESPONSE_SYS_UP", &ProcessEvent);
       ProcessEvent.Recoil = WasymTree->u_corrected_pt_el_loose_pfoEM_SET_SYS;
       ProcessEvent.Recoil_Phi = WasymTree->u_corrected_phi_el_loose_pfoEM_SET_SYS;
       ProcessEvent.SumETWeight = WasymTree->sumetweight_el_loose_pfoEM_SET_SYS;
       ZmumuSelection(MCType, "Recoil_loose_pfoEM_SET_SYS", &ProcessEvent);
     }

   }//end systematic

 }//end loop

}

bool loopWasym::BaseLineElectron(float el_pt, float el_delta_z0, float el_d0sig, float el_eta, bool el_isMedium)
{
 bool isPass = true;

 if(el_pt < 15000) isPass = false;
 if(fabs(el_delta_z0) > 0.5 || fabs(el_d0sig) > 5.) isPass = false;
 if(fabs(el_eta) >= 1.37 && fabs(el_eta) <= 1.52) isPass = false;
 if(fabs(el_eta) > 2.47) isPass = false;
 if(el_isMedium != 1) isPass = false;

 return isPass;
}

bool loopWasym::BaseLineMuon(float mu_pt, float mu_delta_z0, float mu_d0sig, float mu_eta)
{
 bool isPass = true;

 if(mu_pt < 15000) isPass = false;
 if(fabs(mu_delta_z0 > 0.5) || fabs(mu_d0sig > 3.)) isPass = false;
 if(fabs(mu_eta) > 2.4) isPass = false;

 return isPass;
}

void loopWasym::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!WasymTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete WasymTree->fChain[RootNumber]->GetCurrentFile();
}

void loopWasym::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete WasymTree;

}

loopWasym::~loopWasym()
{
}
