#define ZPrime_TreeForZPrime_cxx
#include "ZPrime/TreeForZPrime.h"

using namespace std;

void TreeForZPrime::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers

   // Set object pointer
   DFCommonJets_eventClean_LooseBad = 0;
   jet_ConeTruthLabelID = 0;
   jet_E = 0;
   jet_Jvt = 0;
   jet_PartonTruthLabelID = 0;
   jet_btag = 0;
   jet_btag_score = 0;
   jet_btag_sf = 0;
   jet_eta = 0;
   jet_isJvtHS = 0;
   jet_phi = 0;
   jet_pt = 0;

   truth_jet_ConeTruthLabelID = 0;
   truth_jet_E = 0;
   truth_jet_Jvt = 0;
   truth_jet_PartonTruthLabelID = 0;
   truth_jet_eta = 0;
   truth_jet_phi = 0;
   truth_jet_pt = 0;

}

TreeForZPrime::TreeForZPrime()
{
 Init();
}

TreeForZPrime::~TreeForZPrime()
{

}

void TreeForZPrime::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));

   SetBranch(i);
 }
}

void TreeForZPrime::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));

 SetBranch(0);
}

void TreeForZPrime::CloseFile(int ifile)
{
 rootfile[ifile]->Close();
}

void TreeForZPrime::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;
}

void TreeForZPrime::LinkHist(HistsZPrime* myhists)
{
 this->fHist = myhists;
 this->SystematicName = fHist->SystematicName;
}

void TreeForZPrime::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("hmdyTree");

   fChain[ifile]->SetBranchStatus("*", 1);
   fChain[ifile]->SetBranchAddress("Weight_Lepton1_SF", &Weight_Lepton1_SF, &b_Weight_Lepton1_SF);
   fChain[ifile]->SetBranchAddress("Weight_Lepton2_SF", &Weight_Lepton2_SF, &b_Weight_Lepton2_SF);
   fChain[ifile]->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain[ifile]->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain[ifile]->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   fChain[ifile]->SetBranchAddress("RecoDilRapidity", &RecoDilRapidity, &b_RecoDilRapidity);
   fChain[ifile]->SetBranchAddress("RecoDilPhi", &RecoDilPhi, &b_RecoDilPhi);
   fChain[ifile]->SetBranchAddress("RecoDilMass", &RecoDilMass, &b_RecoDilMass);
   fChain[ifile]->SetBranchAddress("RecoPseudoDilMass", &RecoPseudoDilMass, &b_RecoPseudoDilMass);
   fChain[ifile]->SetBranchAddress("RecoDilPt", &RecoDilPt, &b_RecoDilPt);
   fChain[ifile]->SetBranchAddress("RecoPhiStar", &RecoPhiStar, &b_RecoPhiStar);
   fChain[ifile]->SetBranchAddress("RecoCosThetaStar", &RecoCosThetaStar, &b_RecoCosThetaStar);
   fChain[ifile]->SetBranchAddress("RecoWeight", &RecoWeight, &b_RecoWeight);
   fChain[ifile]->SetBranchAddress("RecoWeight_FourTerm_TT", &RecoWeight_FourTerm_TT, &b_RecoWeight_FourTerm_TT);
   fChain[ifile]->SetBranchAddress("RecoWeight_FourTerm_TL", &RecoWeight_FourTerm_TL, &b_RecoWeight_FourTerm_TL);
   fChain[ifile]->SetBranchAddress("RecoWeight_FourTerm_LT", &RecoWeight_FourTerm_LT, &b_RecoWeight_FourTerm_LT);
   fChain[ifile]->SetBranchAddress("RecoWeight_FourTerm_LL", &RecoWeight_FourTerm_LL, &b_RecoWeight_FourTerm_LL);
   fChain[ifile]->SetBranchAddress("eeChannel", &eeChannel, &b_eeChannel);
   fChain[ifile]->SetBranchAddress("mumuChannel", &mumuChannel, &b_mumuChannel);
   fChain[ifile]->SetBranchAddress("emuChannel", &emuChannel, &b_emuChannel);
   fChain[ifile]->SetBranchAddress("eeChannel_withmuon", &eeChannel_withmuon, &b_eeChannel_withmuon);
   fChain[ifile]->SetBranchAddress("SingleElectron", &SingleElectron, &b_SingleElectron);
   fChain[ifile]->SetBranchAddress("TruthDilMass_Born", &TruthDilMass_Born, &b_TruthDilMass_Born);
   fChain[ifile]->SetBranchAddress("TruthDilRapidity_Born", &TruthDilRapidity_Born, &b_TruthDilRapidity_Born);
   fChain[ifile]->SetBranchAddress("Lepton1_Pt", &Lepton1_Pt, &b_Lepton1_Pt);
   fChain[ifile]->SetBranchAddress("Lepton2_Pt", &Lepton2_Pt, &b_Lepton2_Pt);
   fChain[ifile]->SetBranchAddress("Lepton3_Pt", &Lepton3_Pt, &b_Lepton3_Pt);
   fChain[ifile]->SetBranchAddress("Lepton1_Phi", &Lepton1_Phi, &b_Lepton1_Phi);
   fChain[ifile]->SetBranchAddress("Lepton2_Phi", &Lepton2_Phi, &b_Lepton2_Phi);
   fChain[ifile]->SetBranchAddress("Lepton3_Phi", &Lepton3_Phi, &b_Lepton3_Phi);
   fChain[ifile]->SetBranchAddress("Lepton1_Eta", &Lepton1_Eta, &b_Lepton1_Eta);
   fChain[ifile]->SetBranchAddress("Lepton2_Eta", &Lepton2_Eta, &b_Lepton2_Eta);
   fChain[ifile]->SetBranchAddress("Lepton3_Eta", &Lepton3_Eta, &b_Lepton3_Eta);
   fChain[ifile]->SetBranchAddress("pTllReweight", &pTllReweight, &b_pTllReweight);
   fChain[ifile]->SetBranchAddress("ChargeMisIDSFWeight", &ChargeMisIDSFWeight, &b_ChargeMisIDSFWeight);
   //fChain[ifile]->SetBranchAddress("Weight_indiv_SF_EL_ChargeMisID_STAT_UP",   &Weight_indiv_SF_EL_ChargeMisID_STAT_UP,   &b_Weight_indiv_SF_EL_ChargeMisID_STAT_UP);
   //fChain[ifile]->SetBranchAddress("Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN", &Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN, &b_Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN);
   //fChain[ifile]->SetBranchAddress("Weight_indiv_SF_EL_ChargeMisID_SYST_UP",   &Weight_indiv_SF_EL_ChargeMisID_SYST_UP,   &b_Weight_indiv_SF_EL_ChargeMisID_SYST_UP);
   //fChain[ifile]->SetBranchAddress("Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN", &Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN, &b_Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN);
   //fChain[ifile]->SetBranchAddress("ChargeIDSFWeight", &ChargeIDSFWeight, &b_ChargeIDSFWeight);
   fChain[ifile]->SetBranchAddress("LeptonSFWeight", &LeptonSFWeight, &b_LeptonSFWeight);
   fChain[ifile]->SetBranchAddress("PileupWeight", &PileupWeight, &b_PileupWeight);
   fChain[ifile]->SetBranchAddress("TriggerSF", &TriggerSF, &b_TriggerSF);
   fChain[ifile]->SetBranchAddress("n_Bjets", &n_Bjets, &b_n_Bjets);
   fChain[ifile]->SetBranchAddress("MET_Et", &MET_Et, &b_MET_Et);
   fChain[ifile]->SetBranchAddress("Lepton1_z0", &Lepton1_z0, &b_Lepton1_z0);
   fChain[ifile]->SetBranchAddress("Lepton2_z0", &Lepton2_z0, &b_Lepton2_z0);
   fChain[ifile]->SetBranchAddress("Lepton3_z0", &Lepton3_z0, &b_Lepton3_z0);
   fChain[ifile]->SetBranchAddress("Lepton1_d0sig", &Lepton1_d0sig, &b_Lepton1_d0sig);
   fChain[ifile]->SetBranchAddress("Lepton2_d0sig", &Lepton2_d0sig, &b_Lepton2_d0sig);
   fChain[ifile]->SetBranchAddress("Lepton3_d0sig", &Lepton3_d0sig, &b_Lepton3_d0sig);
   //fChain[ifile]->SetBranchAddress("Lepton1_DeltaR", &Lepton1_DeltaR, &b_Lepton1_DeltaR);
   //fChain[ifile]->SetBranchAddress("Lepton2_DeltaR", &Lepton2_DeltaR, &b_Lepton2_DeltaR);
   fChain[ifile]->SetBranchAddress("Mu", &Mu, &b_Mu);
   fChain[ifile]->SetBranchAddress("MuActual", &MuActual, &b_MuActual);
   fChain[ifile]->SetBranchAddress("PhiRF", &PhiRF, &b_PhiRF);
   fChain[ifile]->SetBranchAddress("Weight_kFactor_Old", &Weight_kFactor_Old, &b_Weight_kFactor_Old);
   fChain[ifile]->SetBranchAddress("Weight_kFactor_QCDEW", &Weight_kFactor_QCDEW, &b_Weight_kFactor_QCDEW);
   fChain[ifile]->SetBranchAddress("Weight_kFactor_New_CT18NNLO", &Weight_kFactor_New_CT18NNLO, &b_Weight_kFactor_New_CT18NNLO);
   fChain[ifile]->SetBranchAddress("Weight_kFactor_New_CT18ANNLO", &Weight_kFactor_New_CT18ANNLO, &b_Weight_kFactor_New_CT18ANNLO);
   fChain[ifile]->SetBranchAddress("Weight_kFactor_PowhegtoSherpa", &Weight_kFactor_PowhegtoSherpa, &b_Weight_kFactor_PowhegtoSherpa);

   fChain[ifile]->SetBranchAddress("Lepton_Pt_born", &Lepton_Pt_born, &b_Lepton_Pt_born);
   fChain[ifile]->SetBranchAddress("AntiLepton_Pt_born", &AntiLepton_Pt_born, &b_AntiLepton_Pt_born);
   fChain[ifile]->SetBranchAddress("Lepton_Eta_born", &Lepton_Eta_born, &b_Lepton_Eta_born);
   fChain[ifile]->SetBranchAddress("AntiLepton_Eta_born", &AntiLepton_Eta_born, &b_AntiLepton_Eta_born);
   fChain[ifile]->SetBranchAddress("Lepton_Phi_born", &Lepton_Phi_born, &b_Lepton_Phi_born);
   fChain[ifile]->SetBranchAddress("AntiLepton_Phi_born", &AntiLepton_Phi_born, &b_AntiLepton_Phi_born);
   fChain[ifile]->SetBranchAddress("Lepton_m_born", &Lepton_m_born, &b_Lepton_m_born);
   fChain[ifile]->SetBranchAddress("AntiLepton_m_born", &AntiLepton_m_born, &b_AntiLepton_m_born);
   fChain[ifile]->SetBranchAddress("Lepton_Pt_bare", &Lepton_Pt_bare, &b_Lepton_Pt_bare);
   fChain[ifile]->SetBranchAddress("AntiLepton_Pt_bare", &AntiLepton_Pt_bare, &b_AntiLepton_Pt_bare);
   fChain[ifile]->SetBranchAddress("Lepton_Eta_bare", &Lepton_Eta_bare, &b_Lepton_Eta_bare);
   fChain[ifile]->SetBranchAddress("AntiLepton_Eta_bare", &AntiLepton_Eta_bare, &b_AntiLepton_Eta_bare);
   fChain[ifile]->SetBranchAddress("Lepton_Phi_bare", &Lepton_Phi_bare, &b_Lepton_Phi_bare);
   fChain[ifile]->SetBranchAddress("AntiLepton_Phi_bare", &AntiLepton_Phi_bare, &b_AntiLepton_Phi_bare);
   fChain[ifile]->SetBranchAddress("Lepton_Pt_dressed", &Lepton_Pt_dressed, &b_Lepton_Pt_dressed);
   fChain[ifile]->SetBranchAddress("Lepton_Eta_dressed", &Lepton_Eta_dressed, &b_Lepton_Eta_dressed);
   fChain[ifile]->SetBranchAddress("Lepton_Phi_dressed", &Lepton_Phi_dressed, &b_Lepton_Phi_dressed);
   fChain[ifile]->SetBranchAddress("Lepton_Charge_dressed", &Lepton_Charge_dressed, &b_Lepton_Charge_dressed);
   fChain[ifile]->SetBranchAddress("AntiLepton_Pt_dressed", &AntiLepton_Pt_dressed, &b_AntiLepton_Pt_dressed);
   fChain[ifile]->SetBranchAddress("AntiLepton_Eta_dressed", &AntiLepton_Eta_dressed, &b_AntiLepton_Eta_dressed);
   fChain[ifile]->SetBranchAddress("AntiLepton_Phi_dressed", &AntiLepton_Phi_dressed, &b_AntiLepton_Phi_dressed);
   fChain[ifile]->SetBranchAddress("AntiLepton_Charge_dressed", &AntiLepton_Charge_dressed, &b_AntiLepton_Charge_dressed);

   fChain[ifile]->SetBranchAddress("Lepton1_Charge", &Lepton1_Charge, &b_Lepton1_Charge);
   fChain[ifile]->SetBranchAddress("Lepton2_Charge", &Lepton2_Charge, &b_Lepton2_Charge);

   if(RootNames.at(ifile).Contains("Loose")){
     fChain[ifile]->SetBranchAddress("pass_ee_TT", &pass_ee_TT, &b_pass_ee_TT);
     fChain[ifile]->SetBranchAddress("pass_ee_TL", &pass_ee_TL, &b_pass_ee_TL);
     fChain[ifile]->SetBranchAddress("pass_ee_LT", &pass_ee_LT, &b_pass_ee_LT);
     fChain[ifile]->SetBranchAddress("pass_ee_LL", &pass_ee_LL, &b_pass_ee_LL);
     fChain[ifile]->SetBranchAddress("pass_mm_TT", &pass_mm_TT, &b_pass_mm_TT);
     fChain[ifile]->SetBranchAddress("pass_mm_TL", &pass_mm_TL, &b_pass_mm_TL);
     fChain[ifile]->SetBranchAddress("pass_mm_LT", &pass_mm_LT, &b_pass_mm_LT);
     fChain[ifile]->SetBranchAddress("pass_mm_LL", &pass_mm_LL, &b_pass_mm_LL);
     fChain[ifile]->SetBranchAddress("Lepton1_isTight", &Lepton1_isTight, &b_Lepton1_isTight);
     fChain[ifile]->SetBranchAddress("Lepton2_isTight", &Lepton2_isTight, &b_Lepton2_isTight);
     fChain[ifile]->SetBranchAddress("Lepton3_isTight", &Lepton3_isTight, &b_Lepton3_isTight);
     fChain[ifile]->SetBranchAddress("Lepton1_passMediumID", &Lepton1_passMediumID, &b_Lepton1_passMediumID);
     fChain[ifile]->SetBranchAddress("Lepton2_passMediumID", &Lepton2_passMediumID, &b_Lepton2_passMediumID);
     fChain[ifile]->SetBranchAddress("Lepton3_passMediumID", &Lepton3_passMediumID, &b_Lepton3_passMediumID);
     fChain[ifile]->SetBranchAddress("Lepton1_passLooseID", &Lepton1_passLooseID, &b_Lepton1_passLooseID);
     fChain[ifile]->SetBranchAddress("Lepton2_passLooseID", &Lepton2_passLooseID, &b_Lepton2_passLooseID);
     fChain[ifile]->SetBranchAddress("Lepton3_passLooseID", &Lepton3_passLooseID, &b_Lepton3_passLooseID);
     fChain[ifile]->SetBranchAddress("Lepton1_passIso", &Lepton1_passIso, &b_Lepton1_passIso);
     fChain[ifile]->SetBranchAddress("Lepton2_passIso", &Lepton2_passIso, &b_Lepton2_passIso);
     fChain[ifile]->SetBranchAddress("Lepton1_IsoWeight", &Lepton1_IsoWeight, &b_Lepton1_IsoWeight);
     fChain[ifile]->SetBranchAddress("Lepton2_IsoWeight", &Lepton2_IsoWeight, &b_Lepton2_IsoWeight);

     fChain[ifile]->SetBranchAddress("Lepton1_isTruthMatch", &Lepton1_isTruthMatch, &b_Lepton1_isTruthMatch);
     fChain[ifile]->SetBranchAddress("Lepton2_isTruthMatch", &Lepton2_isTruthMatch, &b_Lepton2_isTruthMatch);
     fChain[ifile]->SetBranchAddress("Lepton1_TightWeight", &Lepton1_TightWeight, &b_Lepton1_TightWeight);
     fChain[ifile]->SetBranchAddress("Lepton2_TightWeight", &Lepton2_TightWeight, &b_Lepton2_TightWeight);
     fChain[ifile]->SetBranchAddress("Lepton3_TightWeight", &Lepton3_TightWeight, &b_Lepton3_TightWeight);
     fChain[ifile]->SetBranchAddress("Lepton1_LooseWeight", &Lepton1_LooseWeight, &b_Lepton1_LooseWeight);
     fChain[ifile]->SetBranchAddress("Lepton2_LooseWeight", &Lepton2_LooseWeight, &b_Lepton2_LooseWeight);
     fChain[ifile]->SetBranchAddress("Lepton3_LooseWeight", &Lepton3_LooseWeight, &b_Lepton3_LooseWeight);
     fChain[ifile]->SetBranchAddress("Lepton1_MediumIDWeight", &Lepton1_MediumIDWeight, &b_Lepton1_MediumIDWeight);
     fChain[ifile]->SetBranchAddress("Lepton2_MediumIDWeight", &Lepton2_MediumIDWeight, &b_Lepton2_MediumIDWeight);
     fChain[ifile]->SetBranchAddress("PrescaleFactor", &PrescaleFactor, &b_PrescaleFactor);
     fChain[ifile]->SetBranchAddress("Lepton1_PrescaleFactor", &Lepton1_PrescaleFactor, &b_Lepton1_PrescaleFactor);
     fChain[ifile]->SetBranchAddress("Lepton2_PrescaleFactor", &Lepton2_PrescaleFactor, &b_Lepton2_PrescaleFactor);
   }

   if(AdditionalWeightName.count(RootTypes.at(ifile)) > 0){
     if((AdditionalWeightName.at(RootTypes.at(ifile)).Contains("EL_") && (!RootNames.at(ifile).Contains("DrellYan_mumu") && !RootNames.at(ifile).Contains("DrellYan_mm")))
     || (AdditionalWeightName.at(RootTypes.at(ifile)).Contains("MU_") && !RootNames.at(ifile).Contains("DrellYan_ee"))
     ){
       fChain[ifile]->SetBranchAddress(AdditionalWeightName.at(RootTypes.at(ifile)), &(AdditionalWeight.at(RootTypes.at(ifile))), &(AdditionalWeightBranch.at(RootTypes.at(ifile))));
     }
   }

   if(SystematicName.Contains("Fake_Matrix_")){
     if(RootNames.at(ifile).Contains("Fake_Matrix_")){
       fChain[ifile]->SetBranchAddress("RecoWeight_Stat_up",   &RecoWeight_Stat_up,   &b_RecoWeight_Stat_up);
       fChain[ifile]->SetBranchAddress("RecoWeight_Stat_down", &RecoWeight_Stat_down, &b_RecoWeight_Stat_down);
       fChain[ifile]->SetBranchAddress("RecoWeight_PromptSubtr_up",   &RecoWeight_PromptSubtr_up,   &b_RecoWeight_PromptSubtr_up);
       fChain[ifile]->SetBranchAddress("RecoWeight_PromptSubtr_down", &RecoWeight_PromptSubtr_down, &b_RecoWeight_PromptSubtr_down);
       fChain[ifile]->SetBranchAddress("RecoWeight_RealStat_up",   &RecoWeight_RealStat_up,   &b_RecoWeight_RealStat_up);
       fChain[ifile]->SetBranchAddress("RecoWeight_RealStat_down", &RecoWeight_RealStat_down, &b_RecoWeight_RealStat_down);
       fChain[ifile]->SetBranchAddress("RecoWeight_MET_up",   &RecoWeight_MET_up,   &b_RecoWeight_MET_up);
       fChain[ifile]->SetBranchAddress("RecoWeight_MET_down", &RecoWeight_MET_down, &b_RecoWeight_MET_down);
       fChain[ifile]->SetBranchAddress("RecoWeight_d0sig_up",   &RecoWeight_d0sig_up,   &b_RecoWeight_d0sig_up);
       fChain[ifile]->SetBranchAddress("RecoWeight_d0sig_down", &RecoWeight_d0sig_down, &b_RecoWeight_d0sig_down);
     }

     /*
     if(RootNames.at(ifile).Contains("ntuple_MM")){
       fChain[ifile]->SetBranchAddress("RecoWeight_PromptSubtrUp", &RecoWeight_PromptSubtrUp, &b_RecoWeight_PromptSubtrUp);
       fChain[ifile]->SetBranchAddress("RecoWeight_PromptSubtrDown", &RecoWeight_PromptSubtrDown, &b_RecoWeight_PromptSubtrDown);
       fChain[ifile]->SetBranchAddress("RecoWeight_noW", &RecoWeight_noW, &b_RecoWeight_noW);
       fChain[ifile]->SetBranchAddress("RecoWeight_noDY", &RecoWeight_noDY, &b_RecoWeight_noDY);
       fChain[ifile]->SetBranchAddress("RecoWeight_noZMass", &RecoWeight_noZMass, &b_RecoWeight_noZMass);
       fChain[ifile]->SetBranchAddress("RecoWeight_StatsUp", &RecoWeight_StatsUp, &b_RecoWeight_StatsUp);
       fChain[ifile]->SetBranchAddress("RecoWeight_StatsDown", &RecoWeight_StatsDown, &b_RecoWeight_StatsDown);
       fChain[ifile]->SetBranchAddress("RecoWeight_matrix_1up", &RecoWeight_matrix_1up, &b_RecoWeight_matrix_1up);
       fChain[ifile]->SetBranchAddress("RecoWeight_matrix_1down", &RecoWeight_matrix_1down, &b_RecoWeight_matrix_1down);
     }
     */
   }

   if(SystematicName.Contains("Fake_Matrix_Muon")){

     /*
     if(RootNames.at(ifile).Contains("matrix_Data_all_Dimuon")){
       fChain[ifile]->SetBranchAddress("RecoWeight_stats_1up", &RecoWeight_stats_1up, &b_RecoWeight_stats_1up);
       fChain[ifile]->SetBranchAddress("RecoWeight_stats_1down", &RecoWeight_stats_1down, &b_RecoWeight_stats_1down);
       fChain[ifile]->SetBranchAddress("RecoWeight_d0Sig_1up", &RecoWeight_d0Sig_1up, &b_RecoWeight_d0Sig_1up);
       fChain[ifile]->SetBranchAddress("RecoWeight_d0Sig_1down", &RecoWeight_d0Sig_1down, &b_RecoWeight_d0Sig_1down);
     }
     */
   }

   TotalEntries[ifile] = fChain[ifile]->GetEntries();
}

void TreeForZPrime::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);
}

void TreeForZPrime::GenerateFile(TString FileName)
{
 hf = new TFile(FileName, "RECREATE");
}

void TreeForZPrime::DefineTree(int isys, TString TreeName)
{
 cout<<"Defining the tree "<<TreeName<<endl;

 TDirectory *subdir = hf->mkdir("LJAlgo");
 subdir->cd();

 GenerateTree[isys] = new TTree(TreeName, TreeName);

 GenerateTree[isys]->Branch( "DFCommonJets_eventClean_LooseBad",       "vector<int>",     &v_DFCommonJets_eventClean_LooseBad);
 GenerateTree[isys]->Branch( "jet_ConeTruthLabelID",                   "vector<int>",     &v_jet_ConeTruthLabelID);
 GenerateTree[isys]->Branch( "jet_E",                                  "vector<float>",   &v_jet_E);
 GenerateTree[isys]->Branch( "jet_Jvt",                                "vector<float>",   &v_jet_Jvt);
 GenerateTree[isys]->Branch( "jet_PartonTruthLabelID",                 "vector<int>",     &v_jet_PartonTruthLabelID);
 GenerateTree[isys]->Branch( "jet_btag",                               "vector<bool>",    &v_jet_btag);
 GenerateTree[isys]->Branch( "jet_btag_score",                         "vector<int>",     &v_jet_btag_score);
 GenerateTree[isys]->Branch( "jet_btag_sf",                            "vector<float>",   &v_jet_btag_sf);
 GenerateTree[isys]->Branch( "jet_eta",                                "vector<float>",   &v_jet_eta);
 GenerateTree[isys]->Branch( "jet_isJvtHS",                            "vector<char>",    &v_jet_isJvtHS);
 GenerateTree[isys]->Branch( "jet_phi",                                "vector<float>",   &v_jet_phi);
 GenerateTree[isys]->Branch( "jet_pt",                                 "vector<float>",   &v_jet_pt);
 GenerateTree[isys]->Branch( "truth_jet_ConeTruthLabelID",             "vector<int>",     &v_truth_jet_ConeTruthLabelID);
 GenerateTree[isys]->Branch( "truth_jet_E",                            "vector<float>",   &v_truth_jet_E);
 GenerateTree[isys]->Branch( "truth_jet_Jvt",                          "vector<float>",   &v_truth_jet_Jvt);
 GenerateTree[isys]->Branch( "truth_jet_PartonTruthLabelID",           "vector<int>",     &v_truth_jet_PartonTruthLabelID);
 GenerateTree[isys]->Branch( "truth_jet_eta",                          "vector<float>",   &v_truth_jet_eta);
 GenerateTree[isys]->Branch( "truth_jet_phi",                          "vector<float>",   &v_truth_jet_phi);
 GenerateTree[isys]->Branch( "truth_jet_pt",                           "vector<float>",   &v_truth_jet_pt);
 GenerateTree[isys]->Branch( "weight_norm",                            &weight_norm);
 GenerateTree[isys]->Branch( "weight_lumi",                            &weight_lumi);
 GenerateTree[isys]->Branch( "runNumber",                              &runNumber);
 GenerateTree[isys]->Branch( "eventNumber",                            &eventNumber);
 GenerateTree[isys]->Branch( "lumiBlock",                              &lumiBlock);
 GenerateTree[isys]->Branch( "coreFlags",                              &coreFlags);
 GenerateTree[isys]->Branch( "bcid",                                   &bcid);
 GenerateTree[isys]->Branch( "NPV",                                    &NPV);
 GenerateTree[isys]->Branch( "actualInteractionsPerCrossing",          &actualInteractionsPerCrossing);
 GenerateTree[isys]->Branch( "averageInteractionsPerCrossing",         &averageInteractionsPerCrossing);
 GenerateTree[isys]->Branch( "weight_pileup",                          &weight_pileup);
 GenerateTree[isys]->Branch( "correctedAverageMu",                     &correctedAverageMu);
 GenerateTree[isys]->Branch( "correctedAndScaledAverageMu",            &correctedAndScaledAverageMu);
 GenerateTree[isys]->Branch( "correctedActualMu",                      &correctedActualMu);
 GenerateTree[isys]->Branch( "correctedAndScaledActualMu",             &correctedAndScaledActualMu);
 GenerateTree[isys]->Branch( "weight_pileup_up",                       &weight_pileup_up);
 GenerateTree[isys]->Branch( "weight_pileup_down",                     &weight_pileup_down);
 GenerateTree[isys]->Branch( "beamSpotWeight",                         &beamSpotWeight);
 GenerateTree[isys]->Branch( "ntruth_jet",                             &ntruth_jet);
 GenerateTree[isys]->Branch( "njet",                                   &njet);
 GenerateTree[isys]->Branch( "metFinalTrk",                            &metFinalTrk);
 GenerateTree[isys]->Branch( "metFinalTrkPx",                          &metFinalTrkPx);
 GenerateTree[isys]->Branch( "metFinalTrkPy",                          &metFinalTrkPy);
 GenerateTree[isys]->Branch( "metFinalTrkSumEt",                       &metFinalTrkSumEt);
 GenerateTree[isys]->Branch( "metFinalTrkPhi",                         &metFinalTrkPhi);
 GenerateTree[isys]->Branch( "metFinalTrkOverSqrtSumEt",               &metFinalTrkOverSqrtSumEt);
 GenerateTree[isys]->Branch( "metFinalTrkOverSqrtHt",                  &metFinalTrkOverSqrtHt);
 GenerateTree[isys]->Branch( "metFinalTrkSignificance",                &metFinalTrkSignificance);
 GenerateTree[isys]->Branch( "metFinalTrkSigDirectional",              &metFinalTrkSigDirectional);
 GenerateTree[isys]->Branch( "metEle",                                 &metEle);
 GenerateTree[isys]->Branch( "metEleSumEt",                            &metEleSumEt);
 GenerateTree[isys]->Branch( "metElePhi",                              &metElePhi);
 GenerateTree[isys]->Branch( "metMuons",                               &metMuons);
 GenerateTree[isys]->Branch( "metMuonsSumEt",                          &metMuonsSumEt);
 GenerateTree[isys]->Branch( "metMuonsPhi",                            &metMuonsPhi);
 GenerateTree[isys]->Branch( "metJet",                                 &metJet);
 GenerateTree[isys]->Branch( "metJetSumEt",                            &metJetSumEt);
 GenerateTree[isys]->Branch( "metJetPhi",                              &metJetPhi);
 GenerateTree[isys]->Branch( "metSoftTrk",                             &metSoftTrk);
 GenerateTree[isys]->Branch( "metSoftTrkSumEt",                        &metSoftTrkSumEt);
 GenerateTree[isys]->Branch( "metSoftTrkPhi",                          &metSoftTrkPhi);
 GenerateTree[isys]->Branch( "HLT_e120_lhvloose_L1EM22VHI",            &HLT_e120_lhvloose_L1EM22VHI);
 GenerateTree[isys]->Branch( "prescale_HLT_e120_lhvloose_L1EM22VHI",   &prescale_HLT_e120_lhvloose_L1EM22VHI);
 GenerateTree[isys]->Branch( "HLT_e100_lhvloose_L1EM22VHI",            &HLT_e100_lhvloose_L1EM22VHI);
 GenerateTree[isys]->Branch( "prescale_HLT_e100_lhvloose_L1EM22VHI",   &prescale_HLT_e100_lhvloose_L1EM22VHI);
 GenerateTree[isys]->Branch( "HLT_e80_lhvloose_L1EM22VHI",             &HLT_e80_lhvloose_L1EM22VHI);
 GenerateTree[isys]->Branch( "prescale_HLT_e80_lhvloose_L1EM22VHI",    &prescale_HLT_e80_lhvloose_L1EM22VHI);
 GenerateTree[isys]->Branch( "HLT_e60_lhvloose_L1EM22VHI",             &HLT_e60_lhvloose_L1EM22VHI);
 GenerateTree[isys]->Branch( "prescale_HLT_e60_lhvloose_L1EM22VHI",    &prescale_HLT_e60_lhvloose_L1EM22VHI);
 GenerateTree[isys]->Branch( "HLT_e40_lhvloose_L1EM22VHI",             &HLT_e40_lhvloose_L1EM22VHI);
 GenerateTree[isys]->Branch( "prescale_HLT_e40_lhvloose_L1EM22VHI",    &prescale_HLT_e40_lhvloose_L1EM22VHI);
 GenerateTree[isys]->Branch( "HLT_e30_lhvloose_L1EM22VHI",             &HLT_e30_lhvloose_L1EM22VHI);
 GenerateTree[isys]->Branch( "prescale_HLT_e30_lhvloose_L1EM22VHI",    &prescale_HLT_e30_lhvloose_L1EM22VHI);
 GenerateTree[isys]->Branch( "HLT_e20_lhvloose_L1EM15VH",              &HLT_e20_lhvloose_L1EM15VH);
 GenerateTree[isys]->Branch( "prescale_HLT_e20_lhvloose_L1EM15VH",     &prescale_HLT_e20_lhvloose_L1EM15VH);
 GenerateTree[isys]->Branch( "HLT_e120_lhvloose_L1eEM28M",             &HLT_e120_lhvloose_L1eEM28M);
 GenerateTree[isys]->Branch( "prescale_HLT_e120_lhvloose_L1eEM28M",    &prescale_HLT_e120_lhvloose_L1eEM28M);
 GenerateTree[isys]->Branch( "HLT_e100_lhvloose_L1eEM28M",             &HLT_e100_lhvloose_L1eEM28M);
 GenerateTree[isys]->Branch( "prescale_HLT_e100_lhvloose_L1eEM28M",    &prescale_HLT_e100_lhvloose_L1eEM28M);
 GenerateTree[isys]->Branch( "HLT_e80_lhvloose_L1eEM28M",              &HLT_e80_lhvloose_L1eEM28M);
 GenerateTree[isys]->Branch( "prescale_HLT_e80_lhvloose_L1eEM28M",     &prescale_HLT_e80_lhvloose_L1eEM28M);
 GenerateTree[isys]->Branch( "HLT_e60_lhvloose_L1eEM28M",              &HLT_e60_lhvloose_L1eEM28M);
 GenerateTree[isys]->Branch( "prescale_HLT_e60_lhvloose_L1eEM28M",     &prescale_HLT_e60_lhvloose_L1eEM28M);
 GenerateTree[isys]->Branch( "HLT_e40_lhvloose_L1eEM28M",              &HLT_e40_lhvloose_L1eEM28M);
 GenerateTree[isys]->Branch( "prescale_HLT_e40_lhvloose_L1eEM28M",     &prescale_HLT_e40_lhvloose_L1eEM28M);
 GenerateTree[isys]->Branch( "HLT_e30_lhvloose_L1eEM28M",              &HLT_e30_lhvloose_L1eEM28M);
 GenerateTree[isys]->Branch( "prescale_HLT_e30_lhvloose_L1eEM28M",     &prescale_HLT_e30_lhvloose_L1eEM28M);
 GenerateTree[isys]->Branch( "HLT_e20_lhvloose_L1eEM18L",              &HLT_e20_lhvloose_L1eEM18L);
 GenerateTree[isys]->Branch( "prescale_HLT_e20_lhvloose_L1eEM18L",     &prescale_HLT_e20_lhvloose_L1eEM18L);
 GenerateTree[isys]->Branch( "HLT_mu20_iloose_L1MU15",                 &HLT_mu20_iloose_L1MU15);
 GenerateTree[isys]->Branch( "HLT_mu26_ivarmedium",                    &HLT_mu26_ivarmedium);
 GenerateTree[isys]->Branch( "HLT_mu50",                               &HLT_mu50);
 GenerateTree[isys]->Branch( "HLT_mu40",                               &HLT_mu40);
 GenerateTree[isys]->Branch( "HLT_mu24_ivarmedium_L1MU14FCH",          &HLT_mu24_ivarmedium_L1MU14FCH);
 GenerateTree[isys]->Branch( "HLT_mu50_L1MU14FCH",                     &HLT_mu50_L1MU14FCH);
 GenerateTree[isys]->Branch( "HLT_2e12_lhloose_L12EM10VH",             &HLT_2e12_lhloose_L12EM10VH);
 GenerateTree[isys]->Branch( "HLT_2e17_lhvloose_nod0",                 &HLT_2e17_lhvloose_nod0);
 GenerateTree[isys]->Branch( "HLT_2e24_lhvloose_nod0",                 &HLT_2e24_lhvloose_nod0);
 GenerateTree[isys]->Branch( "HLT_2e24_lhvloose_L12EM20VH",            &HLT_2e24_lhvloose_L12EM20VH);
 GenerateTree[isys]->Branch( "HLT_2e24_lhvloose_L12eEM24L",            &HLT_2e24_lhvloose_L12eEM24L);
 GenerateTree[isys]->Branch( "HLT_singleLep",                          &HLT_singleLep);
 GenerateTree[isys]->Branch( "HLT_singleJet",                          &HLT_singleJet);
 GenerateTree[isys]->Branch( "randomRunNumber",                        &randomRunNumber);
 GenerateTree[isys]->Branch( "datasetNumber",                          &datasetNumber);
 GenerateTree[isys]->Branch( "year",                                   &year);
 GenerateTree[isys]->Branch( "mcEventWeight",                          &mcEventWeight);
 GenerateTree[isys]->Branch( "sample_xSec",                            &sample_xSec);
 GenerateTree[isys]->Branch( "sample_xSec_up_rel",                     &sample_xSec_up_rel);
 GenerateTree[isys]->Branch( "sample_xSec_down_rel",                   &sample_xSec_down_rel);
 GenerateTree[isys]->Branch( "sample_kFactor",                         &sample_kFactor);
 GenerateTree[isys]->Branch( "sample_filterEff",                       &sample_filterEff);
 GenerateTree[isys]->Branch( "weight_gen",                             &weight_gen);
 GenerateTree[isys]->Branch( "weight_lepton",                          &weight_lepton);
 GenerateTree[isys]->Branch( "weight_jvt",                             &weight_jvt);
 GenerateTree[isys]->Branch( "weight_btag",                            &weight_btag);
 GenerateTree[isys]->Branch( "weight_singleleptonTrigSF",              &weight_singleleptonTrigSF);
 GenerateTree[isys]->Branch( "weight_dileptonTrigSF",                  &weight_dileptonTrigSF);
 GenerateTree[isys]->Branch( "fakeweight",                             &fakeweight);
 GenerateTree[isys]->Branch( "n_truth_el",                             &n_truth_el);
 GenerateTree[isys]->Branch( "n_truth_mu",                             &n_truth_mu);
 GenerateTree[isys]->Branch( "n_truth_lep",                            &n_truth_lep);
 GenerateTree[isys]->Branch( "n_el",                                   &n_el);
 GenerateTree[isys]->Branch( "n_mu",                                   &n_mu);
 GenerateTree[isys]->Branch( "n_lep",                                  &n_lep);
 GenerateTree[isys]->Branch( "n_signal_el",                            &n_signal_el);
 GenerateTree[isys]->Branch( "n_signal_mu",                            &n_signal_mu);
 GenerateTree[isys]->Branch( "n_signal_lep",                           &n_signal_lep);
 GenerateTree[isys]->Branch( "n_bjets_65",                             &n_bjets_65);
 GenerateTree[isys]->Branch( "n_bjets_70",                             &n_bjets_70);
 GenerateTree[isys]->Branch( "n_bjets_77",                             &n_bjets_77);
 GenerateTree[isys]->Branch( "n_bjets_85",                             &n_bjets_85);
 GenerateTree[isys]->Branch( "n_bjets_90",                             &n_bjets_90);
 GenerateTree[isys]->Branch( "n_bjets",                                &n_bjets);
 GenerateTree[isys]->Branch( "lepton1_isEl",                           &lepton1_isEl);
 GenerateTree[isys]->Branch( "lepton1_m",                              &lepton1_m);
 GenerateTree[isys]->Branch( "lepton1_E",                              &lepton1_E);
 GenerateTree[isys]->Branch( "lepton1_pt",                             &lepton1_pt);
 GenerateTree[isys]->Branch( "lepton1_phi",                            &lepton1_phi);
 GenerateTree[isys]->Branch( "lepton1_eta",                            &lepton1_eta);
 GenerateTree[isys]->Branch( "lepton1_caloeta",                        &lepton1_caloeta);
 GenerateTree[isys]->Branch( "lepton1_charge",                         &lepton1_charge);
 GenerateTree[isys]->Branch( "lepton1_truthType",                      &lepton1_truthType);
 GenerateTree[isys]->Branch( "lepton1_truthOrigin",                    &lepton1_truthOrigin);
 GenerateTree[isys]->Branch( "lepton1_IFFType",                        &lepton1_IFFType);
 GenerateTree[isys]->Branch( "lepton1_isPromptIFF",                    &lepton1_isPromptIFF);
 GenerateTree[isys]->Branch( "lepton1_isIsoHighPtCaloOnly",            &lepton1_isIsoHighPtCaloOnly);
 GenerateTree[isys]->Branch( "lepton1_isIsoLoose_VarRad",              &lepton1_isIsoLoose_VarRad);
 GenerateTree[isys]->Branch( "lepton1_isIsoTight_VarRad",              &lepton1_isIsoTight_VarRad);
 GenerateTree[isys]->Branch( "lepton1_isIDLoose",                      &lepton1_isIDLoose);
 GenerateTree[isys]->Branch( "lepton1_isIDMedium",                     &lepton1_isIDMedium);
 GenerateTree[isys]->Branch( "lepton1_isIDTight",                      &lepton1_isIDTight);
 GenerateTree[isys]->Branch( "lepton1_RecoWeight",                     &lepton1_RecoWeight);
 GenerateTree[isys]->Branch( "lepton1_IsoHighPtCaloOnlyWeight",        &lepton1_IsoHighPtCaloOnlyWeight);
 GenerateTree[isys]->Branch( "lepton1_IsoLoose_VarRadWeight",          &lepton1_IsoLoose_VarRadWeight);
 GenerateTree[isys]->Branch( "lepton1_IsoTight_VarRadWeight",          &lepton1_IsoTight_VarRadWeight);
 GenerateTree[isys]->Branch( "lepton1_IDLooseWeight",                  &lepton1_IDLooseWeight);
 GenerateTree[isys]->Branch( "lepton1_IDMediumWeight",                 &lepton1_IDMediumWeight);
 GenerateTree[isys]->Branch( "lepton1_IDTightWeight",                  &lepton1_IDTightWeight);
 GenerateTree[isys]->Branch( "lepton1_ambiguityType",                  &lepton1_ambiguityType);
 GenerateTree[isys]->Branch( "lepton1_addAmbiguity",                   &lepton1_addAmbiguity);
 GenerateTree[isys]->Branch( "lepton1_d0sig",                          &lepton1_d0sig);
 GenerateTree[isys]->Branch( "lepton1_z0sinTheta",                     &lepton1_z0sinTheta);
 GenerateTree[isys]->Branch( "lepton1_d0",                             &lepton1_d0);
 GenerateTree[isys]->Branch( "lepton1_z0",                             &lepton1_z0);
 GenerateTree[isys]->Branch( "lepton1_isSig",                          &lepton1_isSig);
 GenerateTree[isys]->Branch( "lepton1_isIso",                          &lepton1_isIso);
 GenerateTree[isys]->Branch( "lepton1_isTruthMatched",                 &lepton1_isTruthMatched);
 GenerateTree[isys]->Branch( "lepton1_isMatched",                      &lepton1_isMatched);
 GenerateTree[isys]->Branch( "lepton1_truthE",                         &lepton1_truthE);
 GenerateTree[isys]->Branch( "lepton1_truthpt",                        &lepton1_truthpt);
 GenerateTree[isys]->Branch( "lepton1_truthphi",                       &lepton1_truthphi);
 GenerateTree[isys]->Branch( "lepton1_trutheta",                       &lepton1_trutheta);
 GenerateTree[isys]->Branch( "lepton1_truthpdgid",                     &lepton1_truthpdgid);
 GenerateTree[isys]->Branch( "lepton2_isEl",                           &lepton2_isEl);
 GenerateTree[isys]->Branch( "lepton2_m",                              &lepton2_m);
 GenerateTree[isys]->Branch( "lepton2_E",                              &lepton2_E);
 GenerateTree[isys]->Branch( "lepton2_pt",                             &lepton2_pt);
 GenerateTree[isys]->Branch( "lepton2_phi",                            &lepton2_phi);
 GenerateTree[isys]->Branch( "lepton2_eta",                            &lepton2_eta);
 GenerateTree[isys]->Branch( "lepton2_caloeta",                        &lepton2_caloeta);
 GenerateTree[isys]->Branch( "lepton2_charge",                         &lepton2_charge);
 GenerateTree[isys]->Branch( "lepton2_truthType",                      &lepton2_truthType);
 GenerateTree[isys]->Branch( "lepton2_truthOrigin",                    &lepton2_truthOrigin);
 GenerateTree[isys]->Branch( "lepton2_IFFType",                        &lepton2_IFFType);
 GenerateTree[isys]->Branch( "lepton2_isPromptIFF",                    &lepton2_isPromptIFF);
 GenerateTree[isys]->Branch( "lepton2_isIsoHighPtCaloOnly",            &lepton2_isIsoHighPtCaloOnly);
 GenerateTree[isys]->Branch( "lepton2_isIsoLoose_VarRad",              &lepton2_isIsoLoose_VarRad);
 GenerateTree[isys]->Branch( "lepton2_isIsoTight_VarRad",              &lepton2_isIsoTight_VarRad);
 GenerateTree[isys]->Branch( "lepton2_isIDLoose",                      &lepton2_isIDLoose);
 GenerateTree[isys]->Branch( "lepton2_isIDMedium",                     &lepton2_isIDMedium);
 GenerateTree[isys]->Branch( "lepton2_isIDTight",                      &lepton2_isIDTight);
 GenerateTree[isys]->Branch( "lepton2_RecoWeight",                     &lepton2_RecoWeight);
 GenerateTree[isys]->Branch( "lepton2_IsoHighPtCaloOnlyWeight",        &lepton2_IsoHighPtCaloOnlyWeight);
 GenerateTree[isys]->Branch( "lepton2_IsoLoose_VarRadWeight",          &lepton2_IsoLoose_VarRadWeight);
 GenerateTree[isys]->Branch( "lepton2_IsoTight_VarRadWeight",          &lepton2_IsoTight_VarRadWeight);
 GenerateTree[isys]->Branch( "lepton2_IDLooseWeight",                  &lepton2_IDLooseWeight);
 GenerateTree[isys]->Branch( "lepton2_IDMediumWeight",                 &lepton2_IDMediumWeight);
 GenerateTree[isys]->Branch( "lepton2_IDTightWeight",                  &lepton2_IDTightWeight);
 GenerateTree[isys]->Branch( "lepton2_ambiguityType",                  &lepton2_ambiguityType);
 GenerateTree[isys]->Branch( "lepton2_addAmbiguity",                   &lepton2_addAmbiguity);
 GenerateTree[isys]->Branch( "lepton2_d0sig",                          &lepton2_d0sig);
 GenerateTree[isys]->Branch( "lepton2_z0sinTheta",                     &lepton2_z0sinTheta);
 GenerateTree[isys]->Branch( "lepton2_d0",                             &lepton2_d0);
 GenerateTree[isys]->Branch( "lepton2_z0",                             &lepton2_z0);
 GenerateTree[isys]->Branch( "lepton2_isSig",                          &lepton2_isSig);
 GenerateTree[isys]->Branch( "lepton2_isIso",                          &lepton2_isIso);
 GenerateTree[isys]->Branch( "lepton2_isTruthMatched",                 &lepton2_isTruthMatched);
 GenerateTree[isys]->Branch( "lepton2_isMatched",                      &lepton2_isMatched);
 GenerateTree[isys]->Branch( "lepton2_truthE",                         &lepton2_truthE);
 GenerateTree[isys]->Branch( "lepton2_truthpt",                        &lepton2_truthpt);
 GenerateTree[isys]->Branch( "lepton2_truthphi",                       &lepton2_truthphi);
 GenerateTree[isys]->Branch( "lepton2_trutheta",                       &lepton2_trutheta);
 GenerateTree[isys]->Branch( "lepton2_truthpdgid",                     &lepton2_truthpdgid);
 GenerateTree[isys]->Branch( "lepton_singleleptrigMatched",            &lepton_singleleptrigMatched);
 GenerateTree[isys]->Branch( "lepton_dileptrigMatched",                &lepton_dileptrigMatched);
 GenerateTree[isys]->Branch( "jet1_pt",                                &jet1_pt);
 GenerateTree[isys]->Branch( "jet1_phi",                               &jet1_phi);
 GenerateTree[isys]->Branch( "jet1_eta",                               &jet1_eta);
 GenerateTree[isys]->Branch( "jet1_E",                                 &jet1_E);
 GenerateTree[isys]->Branch( "jet1_PartonTruthLabelID",                &jet1_PartonTruthLabelID);
 GenerateTree[isys]->Branch( "jet1_ConeTruthLabelID",                  &jet1_ConeTruthLabelID);
 GenerateTree[isys]->Branch( "jet1_Jvt",                               &jet1_Jvt);
 GenerateTree[isys]->Branch( "jet1_btag_65",                           &jet1_btag_65);
 GenerateTree[isys]->Branch( "jet1_btag_70",                           &jet1_btag_70);
 GenerateTree[isys]->Branch( "jet1_btag_77",                           &jet1_btag_77);
 GenerateTree[isys]->Branch( "jet1_btag_85",                           &jet1_btag_85);
 GenerateTree[isys]->Branch( "jet1_btag_90",                           &jet1_btag_90);
 GenerateTree[isys]->Branch( "jet1_btag",                              &jet1_btag);
 GenerateTree[isys]->Branch( "mLepJet",                                &mLepJet);
 GenerateTree[isys]->Branch( "dRLepJet",                               &dRLepJet);
 GenerateTree[isys]->Branch( "detaLepJet",                             &detaLepJet);
 GenerateTree[isys]->Branch( "dphiLepJet",                             &dphiLepJet);
 GenerateTree[isys]->Branch( "LepOvermLepJet",                         &LepOvermLepJet);
 GenerateTree[isys]->Branch( "matched_mLepJet",                        &matched_mLepJet);
 GenerateTree[isys]->Branch( "truth_mLepJet",                          &truth_mLepJet);
 GenerateTree[isys]->Branch( "truth_dRLepJet",                         &truth_dRLepJet);
 GenerateTree[isys]->Branch( "mindphiJetMet",                          &mindphiJetMet);
 GenerateTree[isys]->Branch( "dphiLepMet",                             &dphiLepMet);
 GenerateTree[isys]->Branch( "born_lepton1_E",                         &born_lepton1_E);
 GenerateTree[isys]->Branch( "born_lepton1_pt",                        &born_lepton1_pt);
 GenerateTree[isys]->Branch( "born_lepton1_eta",                       &born_lepton1_eta);
 GenerateTree[isys]->Branch( "born_lepton1_phi",                       &born_lepton1_phi);
 GenerateTree[isys]->Branch( "born_lepton2_E",                         &born_lepton2_E);
 GenerateTree[isys]->Branch( "born_lepton2_pt",                        &born_lepton2_pt);
 GenerateTree[isys]->Branch( "born_lepton2_eta",                       &born_lepton2_eta);
 GenerateTree[isys]->Branch( "born_lepton2_phi",                       &born_lepton2_phi);
 GenerateTree[isys]->Branch( "born_dilepton_m",                        &born_dilepton_m);
 GenerateTree[isys]->Branch( "n_born_lepton",                          &n_born_lepton);
 GenerateTree[isys]->Branch( "n_truth_boson",                          &n_truth_boson);
 GenerateTree[isys]->Branch( "truth_boson_m",                          &truth_boson_m);
 GenerateTree[isys]->Branch( "hardscatter_W_m",                        &hardscatter_W_m);
 GenerateTree[isys]->Branch( "dilepton_m",                             &dilepton_m);
 GenerateTree[isys]->Branch( "dilepton_pt",                            &dilepton_pt);
 GenerateTree[isys]->Branch( "dilepton_phi",                           &dilepton_phi);
 GenerateTree[isys]->Branch( "dilepton_eta",                           &dilepton_eta);
 GenerateTree[isys]->Branch( "dilepton_DeltaR",                        &dilepton_DeltaR);
 GenerateTree[isys]->Branch( "dilepton_DeltaEta",                      &dilepton_DeltaEta);
 GenerateTree[isys]->Branch( "dilepton_DeltaPhi",                      &dilepton_DeltaPhi);
 GenerateTree[isys]->Branch( "dilepton_CosThetaStar",                  &dilepton_CosThetaStar);
 GenerateTree[isys]->Branch( "mt_lep1",                                &mt_lep1);
 GenerateTree[isys]->Branch( "mt_lep2",                                &mt_lep2);
 GenerateTree[isys]->Branch( "jets_HT",                                &jets_HT);
 GenerateTree[isys]->Branch( "meff",                                   &meff);

 GenerateTree[isys]->Branch( "passElTrigger",                          &passElTrigger);
 GenerateTree[isys]->Branch( "passMuTrigger",                          &passMuTrigger);

 GenerateTree[isys]->Branch("RecoWeight",                       &RecoWeight,                    "RecoWeight/D");
 GenerateTree[isys]->Branch("RecoWeight_Stat_up",               &RecoWeight_Stat_up,            "RecoWeight_Stat_up/D");
 GenerateTree[isys]->Branch("RecoWeight_Stat_down",             &RecoWeight_Stat_down,          "RecoWeight_Stat_down/D");
 GenerateTree[isys]->Branch("RecoWeight_MET_up",                &RecoWeight_MET_up,             "RecoWeight_MET_up/D");
 GenerateTree[isys]->Branch("RecoWeight_MET_down",              &RecoWeight_MET_down,           "RecoWeight_MET_down/D");
 GenerateTree[isys]->Branch("RecoWeight_PromptSubtr_up",        &RecoWeight_PromptSubtr_up,     "RecoWeight_PromptSubtr_up/D");
 GenerateTree[isys]->Branch("RecoWeight_PromptSubtr_down",      &RecoWeight_PromptSubtr_down,   "RecoWeight_PromptSubtr_down/D");
 GenerateTree[isys]->Branch("RecoWeight_d0sig_up",              &RecoWeight_d0sig_up,           "RecoWeight_d0sig_up/D");
 GenerateTree[isys]->Branch("RecoWeight_d0sig_down",            &RecoWeight_d0sig_down,         "RecoWeight_d0sig_down/D");
 GenerateTree[isys]->Branch("RecoWeight_RealStat_up",           &RecoWeight_RealStat_up,        "RecoWeight_RealStat_up/D");
 GenerateTree[isys]->Branch("RecoWeight_RealStat_down",         &RecoWeight_RealStat_down,      "RecoWeight_RealStat_down/D");
 GenerateTree[isys]->Branch("RecoWeight_FourTerm_TT",           &RecoWeight_FourTerm_TT,        "RecoWeight_FourTerm_TT/D");
 GenerateTree[isys]->Branch("RecoWeight_FourTerm_TL",           &RecoWeight_FourTerm_TL,        "RecoWeight_FourTerm_TL/D");
 GenerateTree[isys]->Branch("RecoWeight_FourTerm_LT",           &RecoWeight_FourTerm_LT,        "RecoWeight_FourTerm_LT/D");
 GenerateTree[isys]->Branch("RecoWeight_FourTerm_LL",           &RecoWeight_FourTerm_LL,        "RecoWeight_FourTerm_LL/D");


/*
 GenerateTree[isys]->Branch("Weight_Lepton1_SF",                &Weight_Lepton1_SF,            "Weight_Lepton1_SF/D");
 GenerateTree[isys]->Branch("Weight_Lepton2_SF",                &Weight_Lepton2_SF,            "Weight_Lepton2_SF/D");
 GenerateTree[isys]->Branch("RunNumber",                        &RunNumber,                    "RunNumber/I");
 GenerateTree[isys]->Branch("EventNumber",                      &EventNumber);
 GenerateTree[isys]->Branch("mcChannelNumber",                  &mcChannelNumber,              "mcChannelNumber/D");
 GenerateTree[isys]->Branch("RecoDilRapidity",                  &RecoDilRapidity,              "RecoDilRapidity/D");
 GenerateTree[isys]->Branch("RecoDilPhi",                       &RecoDilPhi,                   "RecoDilPhi/D");
 GenerateTree[isys]->Branch("RecoDilMass",                      &RecoDilMass,                  "RecoDilMass/D");
 GenerateTree[isys]->Branch("RecoPseudoDilMass",                &RecoPseudoDilMass,            "RecoPseudoDilMass/D");
 GenerateTree[isys]->Branch("RecoDilPt",                        &RecoDilPt,                    "RecoDilPt/D");
 GenerateTree[isys]->Branch("RecoPhiStar",                      &RecoPhiStar,                  "RecoPhiStar/D");
 GenerateTree[isys]->Branch("RecoCosThetaStar",                 &RecoCosThetaStar,             "RecoCosThetaStar/D");
 GenerateTree[isys]->Branch("eeChannel",                        &eeChannel);
 GenerateTree[isys]->Branch("mumuChannel",                      &mumuChannel);
 GenerateTree[isys]->Branch("emuChannel",                       &emuChannel);
 GenerateTree[isys]->Branch("eeChannel_withmuon",               &eeChannel_withmuon);
 GenerateTree[isys]->Branch("SingleElectron",                   &SingleElectron);
 GenerateTree[isys]->Branch("TruthDilMass_Born",                &TruthDilMass_Born,            "TruthDilMass_Born/D");
 GenerateTree[isys]->Branch("TruthDilRapidity_Born",            &TruthDilRapidity_Born,        "TruthDilRapidity_Born/D");
 GenerateTree[isys]->Branch("Lepton1_Pt",                       &Lepton1_Pt,                   "Lepton1_Pt/D");
 GenerateTree[isys]->Branch("Lepton2_Pt",                       &Lepton2_Pt,                   "Lepton2_Pt/D");
 GenerateTree[isys]->Branch("Lepton3_Pt",                       &Lepton3_Pt,                   "Lepton3_Pt/D");
 GenerateTree[isys]->Branch("Lepton1_Phi",                      &Lepton1_Phi,                  "Lepton1_Phi/D");
 GenerateTree[isys]->Branch("Lepton2_Phi",                      &Lepton2_Phi,                  "Lepton2_Phi/D");
 GenerateTree[isys]->Branch("Lepton3_Phi",                      &Lepton3_Phi,                  "Lepton3_Phi/D");
 GenerateTree[isys]->Branch("Lepton1_Eta",                      &Lepton1_Eta,                  "Lepton1_Eta/D");
 GenerateTree[isys]->Branch("Lepton2_Eta",                      &Lepton2_Eta,                  "Lepton2_Eta/D");
 GenerateTree[isys]->Branch("Lepton3_Eta",                      &Lepton3_Eta,                  "Lepton3_Eta/D");
 GenerateTree[isys]->Branch("pTllReweight",                     &pTllReweight,                 "pTllReweight/D");
 GenerateTree[isys]->Branch("ChargeMisIDSFWeight",              &ChargeMisIDSFWeight,          "ChargeMisIDSFWeight/D");
 GenerateTree[isys]->Branch("Weight_indiv_SF_EL_ChargeMisID_STAT_UP",      &Weight_indiv_SF_EL_ChargeMisID_STAT_UP,  "Weight_indiv_SF_EL_ChargeMisID_STAT_UP/D");
 GenerateTree[isys]->Branch("Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN",    &Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN,"Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN/D");
 GenerateTree[isys]->Branch("Weight_indiv_SF_EL_ChargeMisID_SYST_UP",      &Weight_indiv_SF_EL_ChargeMisID_SYST_UP,  "Weight_indiv_SF_EL_ChargeMisID_SYST_UP/D");
 GenerateTree[isys]->Branch("Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN",    &Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN,"Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN/D");
 GenerateTree[isys]->Branch("LeptonSFWeight",                   &LeptonSFWeight,               "LeptonSFWeight/D");
 GenerateTree[isys]->Branch("PileupWeight",                     &PileupWeight,                 "PileupWeight/D");
 GenerateTree[isys]->Branch("TriggerSF",                        &TriggerSF,                    "TriggerSF/D");
 GenerateTree[isys]->Branch("n_Bjets",                          &n_Bjets,                      "n_Bjets/I");
 GenerateTree[isys]->Branch("MET_Et",                           &MET_Et,                       "MET_Et/D");
 GenerateTree[isys]->Branch("Lepton1_z0",                       &Lepton1_z0,                   "Lepton1_z0/D");
 GenerateTree[isys]->Branch("Lepton2_z0",                       &Lepton2_z0,                   "Lepton2_z0/D");
 GenerateTree[isys]->Branch("Lepton3_z0",                       &Lepton3_z0,                   "Lepton3_z0/D");
 GenerateTree[isys]->Branch("Lepton1_d0sig",                    &Lepton1_d0sig,                "Lepton1_d0sig/D");
 GenerateTree[isys]->Branch("Lepton2_d0sig",                    &Lepton2_d0sig,                "Lepton2_d0sig/D");
 GenerateTree[isys]->Branch("Lepton3_d0sig",                    &Lepton3_d0sig,                "Lepton3_d0sig/D");
 GenerateTree[isys]->Branch("Lepton1_DeltaR",                   &Lepton1_DeltaR,               "Lepton1_DeltaR/D");
 GenerateTree[isys]->Branch("Lepton2_DeltaR",                   &Lepton2_DeltaR,               "Lepton2_DeltaR/D");
 GenerateTree[isys]->Branch("Mu",                               &Mu,                           "Mu/D");
 GenerateTree[isys]->Branch("MuActual",                         &MuActual,                     "MuActual/D");
 GenerateTree[isys]->Branch("PhiRF",                            &PhiRF,                        "PhiRF/D");
 GenerateTree[isys]->Branch("Weight_kFactor_Old",               &Weight_kFactor_Old,           "Weight_kFactor_Old/D");
 GenerateTree[isys]->Branch("Weight_kFactor_QCDEW",             &Weight_kFactor_QCDEW,         "Weight_kFactor_QCDEW/D");
 GenerateTree[isys]->Branch("Weight_kFactor_New_CT18NNLO",      &Weight_kFactor_New_CT18NNLO,  "Weight_kFactor_New_CT18NNLO/D");
 GenerateTree[isys]->Branch("Weight_kFactor_New_CT18ANNLO",     &Weight_kFactor_New_CT18ANNLO, "Weight_kFactor_New_CT18ANNLO/D");
 GenerateTree[isys]->Branch("Weight_kFactor_PowhegtoSherpa",    &Weight_kFactor_PowhegtoSherpa,"Weight_kFactor_PowhegtoSherpa/D");

 GenerateTree[isys]->Branch("Lepton_Pt_born",                   &Lepton_Pt_born,               "Lepton_Pt_born/D");
 GenerateTree[isys]->Branch("AntiLepton_Pt_born",               &AntiLepton_Pt_born,           "AntiLepton_Pt_born/D");
 GenerateTree[isys]->Branch("Lepton_Eta_born",                  &Lepton_Eta_born,              "Lepton_Eta_born/D");
 GenerateTree[isys]->Branch("AntiLepton_Eta_born",              &AntiLepton_Eta_born,          "AntiLepton_Eta_born/D");
 GenerateTree[isys]->Branch("Lepton_Phi_born",                  &Lepton_Phi_born,              "Lepton_Phi_born/D");
 GenerateTree[isys]->Branch("AntiLepton_Phi_born",              &AntiLepton_Phi_born,          "AntiLepton_Phi_born/D");
 GenerateTree[isys]->Branch("Lepton_m_born",                    &Lepton_m_born,                "Lepton_m_born/D");
 GenerateTree[isys]->Branch("AntiLepton_m_born",                &AntiLepton_m_born,            "AntiLepton_m_born/D");
 GenerateTree[isys]->Branch("Lepton_Pt_bare",                   &Lepton_Pt_bare,               "Lepton_Pt_bare/D");
 GenerateTree[isys]->Branch("AntiLepton_Pt_bare",               &AntiLepton_Pt_bare,           "AntiLepton_Pt_bare/D");
 GenerateTree[isys]->Branch("Lepton_Eta_bare",                  &Lepton_Eta_bare,              "Lepton_Eta_bare/D");
 GenerateTree[isys]->Branch("AntiLepton_Eta_bare",              &AntiLepton_Eta_bare,          "AntiLepton_Eta_bare/D");
 GenerateTree[isys]->Branch("Lepton_Phi_bare",                  &Lepton_Phi_bare,              "Lepton_Phi_bare/D");
 GenerateTree[isys]->Branch("AntiLepton_Phi_bare",              &AntiLepton_Phi_bare,          "AntiLepton_Phi_bare/D");
 GenerateTree[isys]->Branch("Lepton_Pt_dressed",                &Lepton_Pt_dressed,            "Lepton_Pt_dressed/D");
 GenerateTree[isys]->Branch("Lepton_Eta_dressed",               &Lepton_Eta_dressed,           "Lepton_Eta_dressed/D");
 GenerateTree[isys]->Branch("Lepton_Phi_dressed",               &Lepton_Phi_dressed,           "Lepton_Phi_dressed/D");
 GenerateTree[isys]->Branch("Lepton_Charge_dressed",            &Lepton_Charge_dressed,        "Lepton_Charge_dressed/D");
 GenerateTree[isys]->Branch("AntiLepton_Pt_dressed",            &AntiLepton_Pt_dressed,        "AntiLepton_Pt_dressed/D");
 GenerateTree[isys]->Branch("AntiLepton_Eta_dressed",           &AntiLepton_Eta_dressed,       "AntiLepton_Eta_dressed/D");
 GenerateTree[isys]->Branch("AntiLepton_Phi_dressed",           &AntiLepton_Phi_dressed,       "AntiLepton_Phi_dressed/D");
 GenerateTree[isys]->Branch("AntiLepton_Charge_dressed",        &AntiLepton_Charge_dressed,    "AntiLepton_Charge_dressed/D");

 GenerateTree[isys]->Branch("pass_ee_TT",                       &pass_ee_TT);
 GenerateTree[isys]->Branch("pass_ee_TL",                       &pass_ee_TL);
 GenerateTree[isys]->Branch("pass_ee_LT",                       &pass_ee_LT);
 GenerateTree[isys]->Branch("pass_ee_LL",                       &pass_ee_LL);
 GenerateTree[isys]->Branch("pass_mm_TT",                       &pass_mm_TT);
 GenerateTree[isys]->Branch("pass_mm_TL",                       &pass_mm_TL);
 GenerateTree[isys]->Branch("pass_mm_LT",                       &pass_mm_LT);
 GenerateTree[isys]->Branch("pass_mm_LL",                       &pass_mm_LL);
 GenerateTree[isys]->Branch("Lepton1_isTight",                  &Lepton1_isTight,               "Lepton1_isTight/I");
 GenerateTree[isys]->Branch("Lepton2_isTight",                  &Lepton2_isTight,               "Lepton2_isTight/I");
 GenerateTree[isys]->Branch("Lepton3_isTight",                  &Lepton3_isTight,               "Lepton3_isTight/I");
 GenerateTree[isys]->Branch("Lepton1_passMediumID",             &Lepton1_passMediumID,          "Lepton1_passMediumID/I");
 GenerateTree[isys]->Branch("Lepton2_passMediumID",             &Lepton2_passMediumID,          "Lepton2_passMediumID/I");
 GenerateTree[isys]->Branch("Lepton3_passMediumID",             &Lepton3_passMediumID,          "Lepton3_passMediumID/I");
 GenerateTree[isys]->Branch("Lepton1_passLooseID",              &Lepton1_passLooseID,           "Lepton1_passLooseID/I");
 GenerateTree[isys]->Branch("Lepton2_passLooseID",              &Lepton2_passLooseID,           "Lepton2_passLooseID/I");
 GenerateTree[isys]->Branch("Lepton3_passLooseID",              &Lepton3_passLooseID,           "Lepton3_passLooseID/I");
 GenerateTree[isys]->Branch("Lepton1_passIso",                  &Lepton1_passIso,               "Lepton1_passIso/I");
 GenerateTree[isys]->Branch("Lepton2_passIso",                  &Lepton2_passIso,               "Lepton2_passIso/I");
 GenerateTree[isys]->Branch("Lepton1_IsoWeight",                &Lepton1_IsoWeight,             "Lepton1_IsoWeight/D");
 GenerateTree[isys]->Branch("Lepton2_IsoWeight",                &Lepton2_IsoWeight,             "Lepton2_IsoWeight/D");

 GenerateTree[isys]->Branch("Lepton1_Charge",                   &Lepton1_Charge,                "Lepton1_Charge/I");
 GenerateTree[isys]->Branch("Lepton2_Charge",                   &Lepton2_Charge,                "Lepton2_Charge/I");
 GenerateTree[isys]->Branch("Lepton1_isTruthMatch",             &Lepton1_isTruthMatch,          "Lepton1_isTruthMatch/I");
 GenerateTree[isys]->Branch("Lepton2_isTruthMatch",             &Lepton2_isTruthMatch,          "Lepton2_isTruthMatch/I");
 GenerateTree[isys]->Branch("Lepton1_TightWeight",              &Lepton1_TightWeight,           "Lepton1_TightWeight/D");
 GenerateTree[isys]->Branch("Lepton2_TightWeight",              &Lepton2_TightWeight,           "Lepton2_TightWeight/D");
 GenerateTree[isys]->Branch("Lepton3_TightWeight",              &Lepton3_TightWeight,           "Lepton3_TightWeight/D");
 GenerateTree[isys]->Branch("Lepton1_LooseWeight",              &Lepton1_LooseWeight,           "Lepton1_LooseWeight/D");
 GenerateTree[isys]->Branch("Lepton2_LooseWeight",              &Lepton2_LooseWeight,           "Lepton2_LooseWeight/D");
 GenerateTree[isys]->Branch("Lepton3_LooseWeight",              &Lepton3_LooseWeight,           "Lepton3_LooseWeight/D");
 GenerateTree[isys]->Branch("Lepton1_MediumIDWeight",           &Lepton1_MediumIDWeight,        "Lepton1_MediumIDWeight/D");
 GenerateTree[isys]->Branch("Lepton2_MediumIDWeight",           &Lepton2_MediumIDWeight,        "Lepton2_MediumIDWeight/D");
 GenerateTree[isys]->Branch("PrescaleFactor",                   &PrescaleFactor,                "PrescaleFactor/D");
 GenerateTree[isys]->Branch("Lepton1_PrescaleFactor",           &Lepton1_PrescaleFactor,        "Lepton1_PrescaleFactor/D");
 GenerateTree[isys]->Branch("Lepton2_PrescaleFactor",           &Lepton2_PrescaleFactor,        "Lepton2_PrescaleFactor/D");

 GenerateTree[isys]->Branch("ele_isLHLoose",                    "vector<int>",  &v_ele_isLHLoose);
 GenerateTree[isys]->Branch("ele_isLHMedium",                   "vector<int>",  &v_ele_isLHMedium);
 GenerateTree[isys]->Branch("ele_isFixedCutTightIso",           "vector<int>",  &v_ele_isFixedCutTightIso);
 GenerateTree[isys]->Branch("RecoWeight",                       &RecoWeight,                    "RecoWeight/D");
 GenerateTree[isys]->Branch("RecoWeight_Stat_up",               &RecoWeight_Stat_up,            "RecoWeight_Stat_up/D");
 GenerateTree[isys]->Branch("RecoWeight_Stat_down",             &RecoWeight_Stat_down,          "RecoWeight_Stat_down/D");
 GenerateTree[isys]->Branch("RecoWeight_MET_up",                &RecoWeight_MET_up,             "RecoWeight_MET_up/D");
 GenerateTree[isys]->Branch("RecoWeight_MET_down",              &RecoWeight_MET_down,           "RecoWeight_MET_down/D");
 GenerateTree[isys]->Branch("RecoWeight_PromptSubtr_up",        &RecoWeight_PromptSubtr_up,     "RecoWeight_PromptSubtr_up/D");
 GenerateTree[isys]->Branch("RecoWeight_PromptSubtr_down",      &RecoWeight_PromptSubtr_down,   "RecoWeight_PromptSubtr_down/D");
 GenerateTree[isys]->Branch("RecoWeight_d0sig_up",              &RecoWeight_d0sig_up,           "RecoWeight_d0sig_up/D");
 GenerateTree[isys]->Branch("RecoWeight_d0sig_down",            &RecoWeight_d0sig_down,         "RecoWeight_d0sig_down/D");
 GenerateTree[isys]->Branch("RecoWeight_RealStat_up",           &RecoWeight_RealStat_up,        "RecoWeight_RealStat_up/D");
 GenerateTree[isys]->Branch("RecoWeight_RealStat_down",         &RecoWeight_RealStat_down,      "RecoWeight_RealStat_down/D");
 GenerateTree[isys]->Branch("RecoWeight_FourTerm_TT",           &RecoWeight_FourTerm_TT,        "RecoWeight_FourTerm_TT/D");
 GenerateTree[isys]->Branch("RecoWeight_FourTerm_TL",           &RecoWeight_FourTerm_TL,        "RecoWeight_FourTerm_TL/D");
 GenerateTree[isys]->Branch("RecoWeight_FourTerm_LT",           &RecoWeight_FourTerm_LT,        "RecoWeight_FourTerm_LT/D");
 GenerateTree[isys]->Branch("RecoWeight_FourTerm_LL",           &RecoWeight_FourTerm_LL,        "RecoWeight_FourTerm_LL/D");

 GenerateTree[isys]->Branch("RecoWeight_PromptSubtrUp",         &RecoWeight_PromptSubtrUp,      "RecoWeight_PromptSubtrUp/D");
 GenerateTree[isys]->Branch("RecoWeight_PromptSubtrDown",       &RecoWeight_PromptSubtrDown,    "RecoWeight_PromptSubtrDown/D");
 GenerateTree[isys]->Branch("RecoWeight_noW",                   &RecoWeight_noW,                "RecoWeight_noW/D");
 GenerateTree[isys]->Branch("RecoWeight_noDY",                  &RecoWeight_noDY,               "RecoWeight_noDY/D");
 GenerateTree[isys]->Branch("RecoWeight_noZMass",               &RecoWeight_noZMass,            "RecoWeight_noZMass/D");
 GenerateTree[isys]->Branch("RecoWeight_StatsUp",               &RecoWeight_StatsUp,            "RecoWeight_StatsUp/D");
 GenerateTree[isys]->Branch("RecoWeight_StatsDown",             &RecoWeight_StatsDown,          "RecoWeight_StatsDown/D");
 GenerateTree[isys]->Branch("RecoWeight_CombineError",          &RecoWeight_CombineError,       "RecoWeight_CombineError/D");
 GenerateTree[isys]->Branch("RecoWeight_matrix_1up",            &RecoWeight_matrix_1up,         "RecoWeight_matrix_1up/D");
 GenerateTree[isys]->Branch("RecoWeight_matrix_1down",          &RecoWeight_matrix_1down,       "RecoWeight_matrix_1down/D");
*/

 if(isys == 0){
   Event_CutFlow = new TH1D("Event_CutFlow", "Event_CutFlow", 30, 0, 30);
   Event_CutFlow->SetDirectory(hf);
   Electron_CutFlow = new TH1D("Electron_CutFlow", "Electron_CutFlow", 20, 0, 20);
   Electron_CutFlow->SetDirectory(hf);
   Muon_CutFlow = new TH1D("Muon_CutFlow", "Muon_CutFlow", 20, 0, 20);
   Muon_CutFlow->SetDirectory(hf);

   Event_CutNameMap = new std::map<std::string, double>();
   Electron_CutNameMap = new std::map<std::string, double>();
   Muon_CutNameMap = new std::map<std::string, double>();

   Event_WeightedCutFlow = new TH1D("Event_WeightedCutFlow", "Event_WeightedCutFlow", 30, 0, 30);
   Event_WeightedCutFlow->SetDirectory(hf);
   Electron_WeightedCutFlow = new TH1D("Electron_WeightedCutFlow", "Electron_WeightedCutFlow", 20, 0, 20);
   Electron_WeightedCutFlow->SetDirectory(hf);
   Muon_WeightedCutFlow = new TH1D("Muon_WeightedCutFlow", "Muon_WeightedCutFlow", 20, 0, 20);
   Muon_WeightedCutFlow->SetDirectory(hf);

   Event_WeightedCutNameMap = new std::map<std::string, double>();
   Electron_WeightedCutNameMap = new std::map<std::string, double>();
   Muon_WeightedCutNameMap = new std::map<std::string, double>();

 }

}

void TreeForZPrime::DefineTree(int isys, TString TreeName, TreeForPreZPrime* input)
{
 cout<<"Defining the tree "<<TreeName<<endl;

 //TDirectory *subdir = hf->mkdir("LJAlgo");
 TDirectory *subdir = hf->mkdir("LJAlgoTruth");
 subdir->cd();

 GenerateTree[isys] = input->fChain[0]->CloneTree(0);

 GenerateTree[isys]->Branch( "passElTrigger",                          &passElTrigger);
 GenerateTree[isys]->Branch( "passMuTrigger",                          &passMuTrigger);

 GenerateTree[isys]->Branch("RecoWeight",                       &RecoWeight,                    "RecoWeight/D");
 GenerateTree[isys]->Branch("RecoWeight_Stat_up",               &RecoWeight_Stat_up,            "RecoWeight_Stat_up/D");
 GenerateTree[isys]->Branch("RecoWeight_Stat_down",             &RecoWeight_Stat_down,          "RecoWeight_Stat_down/D");
 GenerateTree[isys]->Branch("RecoWeight_MET_up",                &RecoWeight_MET_up,             "RecoWeight_MET_up/D");
 GenerateTree[isys]->Branch("RecoWeight_MET_down",              &RecoWeight_MET_down,           "RecoWeight_MET_down/D");
 GenerateTree[isys]->Branch("RecoWeight_PromptSubtr_up",        &RecoWeight_PromptSubtr_up,     "RecoWeight_PromptSubtr_up/D");
 GenerateTree[isys]->Branch("RecoWeight_PromptSubtr_down",      &RecoWeight_PromptSubtr_down,   "RecoWeight_PromptSubtr_down/D");
 GenerateTree[isys]->Branch("RecoWeight_d0sig_up",              &RecoWeight_d0sig_up,           "RecoWeight_d0sig_up/D");
 GenerateTree[isys]->Branch("RecoWeight_d0sig_down",            &RecoWeight_d0sig_down,         "RecoWeight_d0sig_down/D");
 GenerateTree[isys]->Branch("RecoWeight_RealStat_up",           &RecoWeight_RealStat_up,        "RecoWeight_RealStat_up/D");
 GenerateTree[isys]->Branch("RecoWeight_RealStat_down",         &RecoWeight_RealStat_down,      "RecoWeight_RealStat_down/D");
 GenerateTree[isys]->Branch("RecoWeight_FourTerm_TT",           &RecoWeight_FourTerm_TT,        "RecoWeight_FourTerm_TT/D");
 GenerateTree[isys]->Branch("RecoWeight_FourTerm_TL",           &RecoWeight_FourTerm_TL,        "RecoWeight_FourTerm_TL/D");
 GenerateTree[isys]->Branch("RecoWeight_FourTerm_LT",           &RecoWeight_FourTerm_LT,        "RecoWeight_FourTerm_LT/D");
 GenerateTree[isys]->Branch("RecoWeight_FourTerm_LL",           &RecoWeight_FourTerm_LL,        "RecoWeight_FourTerm_LL/D");

 GenerateTree[isys]->Branch( "ReweightFactor_SSM_0p5TeV",                        &ReweightFactor_SSM_0p5TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_SSM_0p6TeV",                        &ReweightFactor_SSM_0p6TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_SSM_0p8TeV",                        &ReweightFactor_SSM_0p8TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_SSM_1TeV",                          &ReweightFactor_SSM_1TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_SSM_2TeV",                          &ReweightFactor_SSM_2TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_SSM_3TeV",                          &ReweightFactor_SSM_3TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_SSM_4TeV",                          &ReweightFactor_SSM_4TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_SSM_5TeV",                          &ReweightFactor_SSM_5TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_SSM_6TeV",                          &ReweightFactor_SSM_6TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_SSM_7TeV",                          &ReweightFactor_SSM_7TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_SSM_8TeV",                          &ReweightFactor_SSM_8TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Chi_0p5TeV",                      &ReweightFactor_E6Chi_0p5TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Chi_0p6TeV",                      &ReweightFactor_E6Chi_0p6TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Chi_0p8TeV",                      &ReweightFactor_E6Chi_0p8TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Chi_1TeV",                        &ReweightFactor_E6Chi_1TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Chi_2TeV",                        &ReweightFactor_E6Chi_2TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Chi_3TeV",                        &ReweightFactor_E6Chi_3TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Chi_4TeV",                        &ReweightFactor_E6Chi_4TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Chi_5TeV",                        &ReweightFactor_E6Chi_5TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Chi_6TeV",                        &ReweightFactor_E6Chi_6TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Chi_7TeV",                        &ReweightFactor_E6Chi_7TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Chi_8TeV",                        &ReweightFactor_E6Chi_8TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Psi_0p5TeV",                      &ReweightFactor_E6Psi_0p5TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Psi_0p6TeV",                      &ReweightFactor_E6Psi_0p6TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Psi_0p8TeV",                      &ReweightFactor_E6Psi_0p8TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Psi_1TeV",                        &ReweightFactor_E6Psi_1TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Psi_2TeV",                        &ReweightFactor_E6Psi_2TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Psi_3TeV",                        &ReweightFactor_E6Psi_3TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Psi_4TeV",                        &ReweightFactor_E6Psi_4TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Psi_5TeV",                        &ReweightFactor_E6Psi_5TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Psi_6TeV",                        &ReweightFactor_E6Psi_6TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Psi_7TeV",                        &ReweightFactor_E6Psi_7TeV);
 GenerateTree[isys]->Branch( "ReweightFactor_E6Psi_8TeV",                        &ReweightFactor_E6Psi_8TeV);

 GenerateTree[isys]->Branch( "kfactor_nnlo",                                     &kfactor_nnlo);
 GenerateTree[isys]->Branch( "kfactor_nnlo_up",                                  &kfactor_nnlo_up);
 GenerateTree[isys]->Branch( "kfactor_nnlo_down",                                &kfactor_nnlo_down);
 GenerateTree[isys]->Branch( "kfactor_ew",                                       &kfactor_ew);

 if(isys == 0){
   Event_CutFlow = new TH1D("Event_CutFlow", "Event_CutFlow", 30, 0, 30);
   Event_CutFlow->SetDirectory(hf);
   Electron_CutFlow = new TH1D("Electron_CutFlow", "Electron_CutFlow", 20, 0, 20);
   Electron_CutFlow->SetDirectory(hf);
   Muon_CutFlow = new TH1D("Muon_CutFlow", "Muon_CutFlow", 20, 0, 20);
   Muon_CutFlow->SetDirectory(hf);

   Event_CutNameMap = new std::map<std::string, double>();
   Electron_CutNameMap = new std::map<std::string, double>();
   Muon_CutNameMap = new std::map<std::string, double>();

   Event_WeightedCutFlow = new TH1D("Event_WeightedCutFlow", "Event_WeightedCutFlow", 30, 0, 30);
   Event_WeightedCutFlow->SetDirectory(hf);
   Electron_WeightedCutFlow = new TH1D("Electron_WeightedCutFlow", "Electron_WeightedCutFlow", 20, 0, 20);
   Electron_WeightedCutFlow->SetDirectory(hf);
   Muon_WeightedCutFlow = new TH1D("Muon_WeightedCutFlow", "Muon_WeightedCutFlow", 20, 0, 20);
   Muon_WeightedCutFlow->SetDirectory(hf);

   Event_WeightedCutNameMap = new std::map<std::string, double>();
   Electron_WeightedCutNameMap = new std::map<std::string, double>();
   Muon_WeightedCutNameMap = new std::map<std::string, double>();

 }
}

void TreeForZPrime::FillTree(int isys)
{
 GenerateTree[isys]->Fill();
}

void TreeForZPrime::InputSystematic(TString sysName)
{
 SystematicName = sysName;

 if(SystematicName.Contains("nominal") || SystematicName.Contains("Fake_") || SystematicName.Contains("TopDD_")){
   SystematicSelection("nominal");
 }
 else if(SystematicName.Contains("Luminosity")){
   SystematicSelection("nominal");
   RootTypes.clear();
   for(int i = 0; i < RootNames.size(); i++){
     TString RootType = GetRootType(RootNames.at(i));
     RootTypes.push_back(RootType);
   }
   if(SystematicName.Contains("up")){
     for(int i = 0; i < RootNames.size(); i++){
       if(RootTypes.at(i) == "Data" || RootTypes.at(i) == "Wjets_DD"){
         Normalization[RootTypes.at(i)] = 1.0;
       }
       else Normalization[RootTypes.at(i)] = 1.0086;
     }
   }
   if(SystematicName.Contains("down")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "Data" || RootTypes.at(i) == "Wjets_DD"){
         Normalization[RootTypes.at(i)] = 1.0;
       }
       else Normalization[RootTypes.at(i)] = 1.0 - 0.0086;
     }
   }
 }
 else if(SystematicName.Contains("PIVariation")){
   SystematicSelection("nominal");
   RootTypes.clear();
   for(int i = 0; i < RootNames.size(); i++){
     TString RootType = GetRootType(RootNames.at(i));
     RootTypes.push_back(RootType);
   }
   if(SystematicName.Contains("up")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "PhotonInduced"){
         Normalization[RootTypes.at(i)] = 1.3;
       }
       else Normalization[RootTypes.at(i)] = 1.0;
     }
   }
   if(SystematicName.Contains("down")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "PhotonInduced"){
         Normalization[RootTypes.at(i)] = 1.0 - 0.3;
       }
       else Normalization[RootTypes.at(i)] = 1.0;
     }
   }
 }
 else if(SystematicName.Contains("Di-boson")){
   SystematicSelection("nominal");
   RootTypes.clear();
   for(int i = 0; i < RootNames.size(); i++){
     TString RootType = GetRootType(RootNames.at(i));
     RootTypes.push_back(RootType);
   }
   if(SystematicName.Contains("up")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "Diboson"){
         Normalization[RootTypes.at(i)] = 1.06;
       }
       else Normalization[RootTypes.at(i)] = 1.0;
     }
   }
   if(SystematicName.Contains("down")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "Diboson"){
         Normalization[RootTypes.at(i)] = 1.0 - 0.06;
       }
       else Normalization[RootTypes.at(i)] = 1.0;
     }
   }
 }
 else if(SystematicName.Contains("LepSF_EL_Reco")){
   SystematicSelection("nominal");
   RootTypes.clear();
   for(int i = 0; i < RootNames.size(); i++){
     TString RootType = GetRootType(RootNames.at(i));
     RootTypes.push_back(RootType);
   }
   if(SystematicName.Contains("up")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_EL_Reco_UP";
         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
   if(SystematicName.Contains("down")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_EL_Reco_DOWN";
         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
 }
 else if(SystematicName.Contains("LepSF_EL_Isol")){
   SystematicSelection("nominal");
   RootTypes.clear();
   for(int i = 0; i < RootNames.size(); i++){
     TString RootType = GetRootType(RootNames.at(i));
     RootTypes.push_back(RootType);
   }
   if(SystematicName.Contains("up")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_EL_Isol_UP";
         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
   if(SystematicName.Contains("down")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_EL_Isol_DOWN";
         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
 }
 else if(SystematicName.Contains("LepSF_EL_Trigger")){
   SystematicSelection("nominal");
   RootTypes.clear();
   for(int i = 0; i < RootNames.size(); i++){
     TString RootType = GetRootType(RootNames.at(i));
     RootTypes.push_back(RootType);
   }
   if(SystematicName.Contains("up")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_EL_Trigger_UP";
         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
   if(SystematicName.Contains("down")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_EL_Trigger_DOWN";
         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
 }
 else if(SystematicName.Contains("LepSF_EL_ChargeMisID_SYST")){
   SystematicSelection("nominal");
   RootTypes.clear();
   for(int i = 0; i < RootNames.size(); i++){
     TString RootType = GetRootType(RootNames.at(i));
     RootTypes.push_back(RootType);
   }
   if(SystematicName.Contains("up")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_EL_ChargeMisID_SYST_UP";
         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
   if(SystematicName.Contains("down")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN";
         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
 }
 else if(SystematicName.Contains("LepSF_EL_ChargeMisID_STAT")){
   SystematicSelection("nominal");
   RootTypes.clear();
   for(int i = 0; i < RootNames.size(); i++){
     TString RootType = GetRootType(RootNames.at(i));
     RootTypes.push_back(RootType);
   }
   if(SystematicName.Contains("up")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_EL_ChargeMisID_STAT_UP";
         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
   if(SystematicName.Contains("down")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN";
         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
 }
 else if(SystematicName.Contains("LepSF_EL_ID_")){
   SystematicSelection("nominal");
   RootTypes.clear();
   for(int i = 0; i < RootNames.size(); i++){
     TString RootType = GetRootType(RootNames.at(i));
     RootTypes.push_back(RootType);
   }
   if(SystematicName.Contains("up")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         if(SystematicName.Contains("LepSF_EL_ID_1")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_1";
         else if(SystematicName.Contains("LepSF_EL_ID_2")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_2";
         else if(SystematicName.Contains("LepSF_EL_ID_3")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_3";
         else if(SystematicName.Contains("LepSF_EL_ID_4")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_4";
         else if(SystematicName.Contains("LepSF_EL_ID_5")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_5";
         else if(SystematicName.Contains("LepSF_EL_ID_6")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_6";
         else if(SystematicName.Contains("LepSF_EL_ID_7")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_7";
         else if(SystematicName.Contains("LepSF_EL_ID_8")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_8";
         else if(SystematicName.Contains("LepSF_EL_ID_9")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_9";
         else if(SystematicName.Contains("LepSF_EL_ID_10")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_10";
         else if(SystematicName.Contains("LepSF_EL_ID_11")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_11";
         else if(SystematicName.Contains("LepSF_EL_ID_12")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_12";
         else if(SystematicName.Contains("LepSF_EL_ID_13")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_13";
         else if(SystematicName.Contains("LepSF_EL_ID_14")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_14";
         else if(SystematicName.Contains("LepSF_EL_ID_15")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_15";
         else if(SystematicName.Contains("LepSF_EL_ID_16")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_16";
         else if(SystematicName.Contains("LepSF_EL_ID_17")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_17";
         else if(SystematicName.Contains("LepSF_EL_ID_18")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_18";
         else if(SystematicName.Contains("LepSF_EL_ID_19")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_19";
         else if(SystematicName.Contains("LepSF_EL_ID_20")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_20";
         else if(SystematicName.Contains("LepSF_EL_ID_21")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_21";
         else if(SystematicName.Contains("LepSF_EL_ID_22")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_22";
         else if(SystematicName.Contains("LepSF_EL_ID_23")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_23";
         else if(SystematicName.Contains("LepSF_EL_ID_24")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_24";
         else if(SystematicName.Contains("LepSF_EL_ID_25")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_25";
         else if(SystematicName.Contains("LepSF_EL_ID_26")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_26";
         else if(SystematicName.Contains("LepSF_EL_ID_27")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_27";
         else if(SystematicName.Contains("LepSF_EL_ID_28")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_28";
         else if(SystematicName.Contains("LepSF_EL_ID_29")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_29";
         else if(SystematicName.Contains("LepSF_EL_ID_30")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_30";
         else if(SystematicName.Contains("LepSF_EL_ID_31")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_31";
         else if(SystematicName.Contains("LepSF_EL_ID_32")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_32";
         else if(SystematicName.Contains("LepSF_EL_ID_33")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_33";
         else if(SystematicName.Contains("LepSF_EL_ID_34")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_UP_34";

         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
   if(SystematicName.Contains("down")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         if(SystematicName.Contains("LepSF_EL_ID_1")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_1";
         else if(SystematicName.Contains("LepSF_EL_ID_2")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_2";
         else if(SystematicName.Contains("LepSF_EL_ID_3")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_3";
         else if(SystematicName.Contains("LepSF_EL_ID_4")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_4";
         else if(SystematicName.Contains("LepSF_EL_ID_5")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_5";
         else if(SystematicName.Contains("LepSF_EL_ID_6")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_6";
         else if(SystematicName.Contains("LepSF_EL_ID_7")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_7";
         else if(SystematicName.Contains("LepSF_EL_ID_8")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_8";
         else if(SystematicName.Contains("LepSF_EL_ID_9")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_9";
         else if(SystematicName.Contains("LepSF_EL_ID_10")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_10";
         else if(SystematicName.Contains("LepSF_EL_ID_11")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_11";
         else if(SystematicName.Contains("LepSF_EL_ID_12")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_12";
         else if(SystematicName.Contains("LepSF_EL_ID_13")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_13";
         else if(SystematicName.Contains("LepSF_EL_ID_14")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_14";
         else if(SystematicName.Contains("LepSF_EL_ID_15")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_15";
         else if(SystematicName.Contains("LepSF_EL_ID_16")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_16";
         else if(SystematicName.Contains("LepSF_EL_ID_17")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_17";
         else if(SystematicName.Contains("LepSF_EL_ID_18")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_18";
         else if(SystematicName.Contains("LepSF_EL_ID_19")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_19";
         else if(SystematicName.Contains("LepSF_EL_ID_20")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_20";
         else if(SystematicName.Contains("LepSF_EL_ID_21")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_21";
         else if(SystematicName.Contains("LepSF_EL_ID_22")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_22";
         else if(SystematicName.Contains("LepSF_EL_ID_23")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_23";
         else if(SystematicName.Contains("LepSF_EL_ID_24")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_24";
         else if(SystematicName.Contains("LepSF_EL_ID_25")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_25";
         else if(SystematicName.Contains("LepSF_EL_ID_26")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_26";
         else if(SystematicName.Contains("LepSF_EL_ID_27")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_27";
         else if(SystematicName.Contains("LepSF_EL_ID_28")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_28";
         else if(SystematicName.Contains("LepSF_EL_ID_29")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_29";
         else if(SystematicName.Contains("LepSF_EL_ID_30")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_30";
         else if(SystematicName.Contains("LepSF_EL_ID_31")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_31";
         else if(SystematicName.Contains("LepSF_EL_ID_32")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_32";
         else if(SystematicName.Contains("LepSF_EL_ID_33")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_33";
         else if(SystematicName.Contains("LepSF_EL_ID_34")) AdditionalWeightName[RootTypes.at(i)] = "Weight_leptonSF_EL_SF_SIMPLIFIED_ID_DOWN_34";

         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
 }
 else if(SystematicName.Contains("LepSF_MU_")){
   SystematicSelection("nominal");
   RootTypes.clear();
   for(int i = 0; i < RootNames.size(); i++){
     TString RootType = GetRootType(RootNames.at(i));
     RootTypes.push_back(RootType);
   }
   if(SystematicName.Contains("up")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         if(SystematicName.Contains("LepSF_MU_TTVA")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_TTVA_UP";
         else if(SystematicName.Contains("LepSF_MU_TTVA_STAT")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_TTVA_STAT_UP";
         else if(SystematicName.Contains("LepSF_MU_ID_STAT")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_ID_STAT_UP";
         else if(SystematicName.Contains("LepSF_MU_ID_STAT_LOWPT")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_ID_STAT_LOWPT_UP";
         else if(SystematicName.Contains("LepSF_MU_ID_SYST")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_ID_UP";
         else if(SystematicName.Contains("LepSF_MU_ID_SYST_LOWPT")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_ID_SYST_LOWPT_UP";
         else if(SystematicName.Contains("LepSF_MU_Trigger")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_Trigger_UP";
         else if(SystematicName.Contains("LepSF_MU_Isol")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_Isol_UP";
         else if(SystematicName.Contains("LepSF_MU_ID_BAD_MUON_VETO")){
           if(RootTypes.at(i) == "TopQuark") AdditionalWeightName[RootTypes.at(i)] = "weight_indiv_SF_MU_ID_BAD_MUON_VETO_UP";
           if(RootTypes.at(i) == "DrellYan") AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_ID_BAD_MUON_VETO_UP";
         }
         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
   if(SystematicName.Contains("down")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark" || RootTypes.at(i) == "DrellYan"){
         if(SystematicName.Contains("LepSF_MU_TTVA")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_TTVA_DOWN";
         else if(SystematicName.Contains("LepSF_MU_TTVA_STAT")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_TTVA_STAT_DOWN";
         else if(SystematicName.Contains("LepSF_MU_ID_STAT")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_ID_STAT_DOWN";
         else if(SystematicName.Contains("LepSF_MU_ID_STAT_LOWPT")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_ID_STAT_LOWPT_DOWN";
         else if(SystematicName.Contains("LepSF_MU_ID_SYST")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_ID_DOWN";
         else if(SystematicName.Contains("LepSF_MU_ID_SYST_LOWPT")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_ID_SYST_LOWPT_DOWN";
         else if(SystematicName.Contains("LepSF_MU_Trigger")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_Trigger_DOWN";
         else if(SystematicName.Contains("LepSF_MU_Isol")) AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_Isol_DOWN";
         else if(SystematicName.Contains("LepSF_MU_ID_BAD_MUON_VETO")){ 
           if(RootTypes.at(i) == "TopQuark") AdditionalWeightName[RootTypes.at(i)] = "weight_indiv_SF_MU_ID_BAD_MUON_VETO_DOWN";
           if(RootTypes.at(i) == "DrellYan") AdditionalWeightName[RootTypes.at(i)] = "Weight_indiv_SF_MU_ID_BAD_MUON_VETO_DOWN";
         }

         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
 }
 else if(SystematicName.Contains("PDF4LHC_") || SystematicName.Contains("ISR_RenFact") || SystematicName.Contains("ISR_Var3c") || SystematicName.Contains("FSR_RenFact")){
   SystematicSelection("nominal");
   RootTypes.clear();
   for(int i = 0; i < RootNames.size(); i++){
     TString RootType = GetRootType(RootNames.at(i));
     RootTypes.push_back(RootType);
   }
   if(SystematicName.Contains("up")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark"){
         if(SystematicName.Contains("PDF4LHC_1")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_1";
         else if(SystematicName.Contains("PDF4LHC_2")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_2";
         else if(SystematicName.Contains("PDF4LHC_3")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_3";
         else if(SystematicName.Contains("PDF4LHC_4")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_4";
         else if(SystematicName.Contains("PDF4LHC_5")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_5";
         else if(SystematicName.Contains("PDF4LHC_6")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_6";
         else if(SystematicName.Contains("PDF4LHC_7")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_7";
         else if(SystematicName.Contains("PDF4LHC_8")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_8";
         else if(SystematicName.Contains("PDF4LHC_9")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_9";
         else if(SystematicName.Contains("PDF4LHC_10")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_10";
         else if(SystematicName.Contains("PDF4LHC_11")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_11";
         else if(SystematicName.Contains("PDF4LHC_12")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_12";
         else if(SystematicName.Contains("PDF4LHC_13")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_13";
         else if(SystematicName.Contains("PDF4LHC_14")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_14";
         else if(SystematicName.Contains("PDF4LHC_15")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_15";
         else if(SystematicName.Contains("PDF4LHC_16")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_16";
         else if(SystematicName.Contains("PDF4LHC_17")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_17";
         else if(SystematicName.Contains("PDF4LHC_18")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_18";
         else if(SystematicName.Contains("PDF4LHC_19")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_19";
         else if(SystematicName.Contains("PDF4LHC_20")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_20";
         else if(SystematicName.Contains("PDF4LHC_21")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_21";
         else if(SystematicName.Contains("PDF4LHC_22")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_22";
         else if(SystematicName.Contains("PDF4LHC_23")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_23";
         else if(SystematicName.Contains("PDF4LHC_24")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_24";
         else if(SystematicName.Contains("PDF4LHC_25")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_25";
         else if(SystematicName.Contains("PDF4LHC_26")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_26";
         else if(SystematicName.Contains("PDF4LHC_27")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_27";
         else if(SystematicName.Contains("PDF4LHC_28")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_28";
         else if(SystematicName.Contains("PDF4LHC_29")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_29";
         else if(SystematicName.Contains("PDF4LHC_30")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_30";
         else if(SystematicName.Contains("ISR_RenFact")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_ISR_RenFact_Up";
         else if(SystematicName.Contains("ISR_Var3c")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_ISR_Var3c_Up";
         else if(SystematicName.Contains("FSR_RenFact")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_FSR_RenFact_Up";

         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
   if(SystematicName.Contains("down")){
     for(int i = 0; i < RootTypes.size(); i++){
       if(RootTypes.at(i) == "TopQuark"){
         if(SystematicName.Contains("PDF4LHC_1")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_1";
         else if(SystematicName.Contains("PDF4LHC_2")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_2";
         else if(SystematicName.Contains("PDF4LHC_3")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_3";
         else if(SystematicName.Contains("PDF4LHC_4")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_4";
         else if(SystematicName.Contains("PDF4LHC_5")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_5";
         else if(SystematicName.Contains("PDF4LHC_6")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_6";
         else if(SystematicName.Contains("PDF4LHC_7")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_7";
         else if(SystematicName.Contains("PDF4LHC_8")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_8";
         else if(SystematicName.Contains("PDF4LHC_9")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_9";
         else if(SystematicName.Contains("PDF4LHC_10")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_10";
         else if(SystematicName.Contains("PDF4LHC_11")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_11";
         else if(SystematicName.Contains("PDF4LHC_12")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_12";
         else if(SystematicName.Contains("PDF4LHC_13")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_13";
         else if(SystematicName.Contains("PDF4LHC_14")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_14";
         else if(SystematicName.Contains("PDF4LHC_15")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_15";
         else if(SystematicName.Contains("PDF4LHC_16")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_16";
         else if(SystematicName.Contains("PDF4LHC_17")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_17";
         else if(SystematicName.Contains("PDF4LHC_18")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_18";
         else if(SystematicName.Contains("PDF4LHC_19")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_19";
         else if(SystematicName.Contains("PDF4LHC_20")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_20";
         else if(SystematicName.Contains("PDF4LHC_21")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_21";
         else if(SystematicName.Contains("PDF4LHC_22")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_22";
         else if(SystematicName.Contains("PDF4LHC_23")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_23";
         else if(SystematicName.Contains("PDF4LHC_24")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_24";
         else if(SystematicName.Contains("PDF4LHC_25")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_25";
         else if(SystematicName.Contains("PDF4LHC_26")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_26";
         else if(SystematicName.Contains("PDF4LHC_27")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_27";
         else if(SystematicName.Contains("PDF4LHC_28")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_28";
         else if(SystematicName.Contains("PDF4LHC_29")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_29";
         else if(SystematicName.Contains("PDF4LHC_30")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_PDF4LHC_30";
         else if(SystematicName.Contains("ISR_RenFact")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_ISR_RenFact_Down";
         else if(SystematicName.Contains("ISR_Var3c")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_ISR_Var3c_Down";
         else if(SystematicName.Contains("FSR_RenFact")) AdditionalWeightName[RootTypes.at(i)] = "Weight_Top_FSR_RenFact_Down";

         AdditionalWeight[RootTypes.at(i)] = 1.0;
         AdditionalWeightBranch[RootTypes.at(i)] = 0;
       }
     }
   }
 }
 else if(SystematicName.Contains("HardScatterMCAdNlo")){
   SystematicSelection("nominal", "HardScatter_MCAdNlo");
   if(SystematicName.Contains("up")){

   }
   if(SystematicName.Contains("down")){

   }
 }
 else if(SystematicName.Contains("FragHadModelHerwig7")){
   SystematicSelection("nominal", "Fragmentation_Herwig7");
   if(SystematicName.Contains("up")){

   }
   if(SystematicName.Contains("down")){

   }
 }
 else if(SystematicName.Contains("ISRVariationNtuple")){
   SystematicSelection("nominal", "ISR");
   if(SystematicName.Contains("up")){

   }
   if(SystematicName.Contains("down")){

   }
 }
 else if(SystematicName.Contains("TopMassVariation")){
   if(SystematicName.Contains("up")){
     SystematicSelection("nominal", "MassUP");

   }
   if(SystematicName.Contains("down")){
     SystematicSelection("nominal", "MassDown");

   }
 }
 else if(SystematicName.Contains("EG_RESOLUTION_AF2")
      || SystematicName.Contains("EG_RESOLUTION_MATERIALCALO")
      || SystematicName.Contains("EG_RESOLUTION_MATERIALCRYO")
      || SystematicName.Contains("EG_RESOLUTION_MATERIALGAP")
      || SystematicName.Contains("EG_RESOLUTION_MATERIALIBL")
      || SystematicName.Contains("EG_RESOLUTION_MATERIALPP0")
      || SystematicName.Contains("EG_RESOLUTION_PILEUP")
      || SystematicName.Contains("EG_RESOLUTION_SAMPLINGTERM")
      || SystematicName.Contains("EG_RESOLUTION_ZSMEARING")
      || SystematicName.Contains("EG_SCALE_E4SCINTILLATOR")
      || SystematicName.Contains("EG_SCALE_G4")
      || SystematicName.Contains("EG_SCALE_L1GAIN")
      || SystematicName.Contains("EG_SCALE_L2GAIN")
      || SystematicName.Contains("EG_SCALE_LARCALIB")
      || SystematicName.Contains("EG_SCALE_LARELECCALIB")
      || SystematicName.Contains("EG_SCALE_LARELECUNCONV")
      || SystematicName.Contains("EG_SCALE_LARUNCONVCALIB")
      || SystematicName.Contains("EG_SCALE_MATCALO")
      || SystematicName.Contains("EG_SCALE_MATCRYO")
      || SystematicName.Contains("EG_SCALE_MATID")
      || SystematicName.Contains("EG_SCALE_MATPP0")
      || SystematicName.Contains("EG_SCALE_PEDESTAL")
      || SystematicName.Contains("EG_SCALE_PS_BARREL_B12")
      || SystematicName.Contains("EG_SCALE_TOPOCLUSTER_THRES")
      || SystematicName.Contains("EG_SCALE_WTOTS1")
      || SystematicName.Contains("EG_SCALE_ZEESYST")
      || SystematicName.Contains("EG_SCALE_PS")
      || SystematicName.Contains("EG_SCALE_S12")
      || SystematicName.Contains("MUON_SAGITTA_RESBIAS")
      || SystematicName.Contains("MUON_ID")
      || SystematicName.Contains("MUON_MS")
      || SystematicName.Contains("MUON_SCALE")
      || SystematicName.Contains("MUON_CB")
 ){
   SystematicSelection(SystematicName);
   if(SystematicName.Contains("up")){
   }
   if(SystematicName.Contains("down")){
   }
 }

 RootTypes.clear();
 for(int i = 0; i < RootNames.size(); i++){
   TString RootType = GetRootType(RootNames.at(i));
   RootTypes.push_back(RootType);
 }
}

void TreeForZPrime::SystematicSelection(TString sysName, TString AdditionalSelection)
{
 for(vector<TString>::iterator it = RootNames.begin(); it != RootNames.end();){

   if((*it).Contains("ntuple_MM_2024")
   || (*it).Contains("ntuple_MM_2025")
   || (*it).Contains("Fake_Matrix_Electron")
   || (*it).Contains("Fake_Matrix_Muon")
   || (*it).Contains("matrix_Data")
   || (*it).Contains("nominal_Data")
   || (*it).Contains("nominal_Diboson")
   || (*it).Contains("nominal_Triboson")
   || (*it).Contains("nominal_ttV")
   || (*it).Contains("nominal_PI")
   || (*it).Contains("nominal_Wjets")
   || (*it).Contains("nominal_Ztautau")){
     ++it;
     continue;
   }

   if((sysName == "nominal") && !((*it).Contains("nominal"))){
     it = RootNames.erase(it);
   }
   else if((sysName.Contains("EG_")) && !((*it).Contains(sysName))){
     it = RootNames.erase(it);
   }
   else if((sysName.Contains("MUON_")) && !((*it).Contains(sysName))){
     if((sysName.Contains("MUON_ID") || sysName.Contains("MUON_MS"))){
       if((*it).Contains("nominal_singleTop") || (*it).Contains("nominal_TopQuark")){
         ++it;
         continue;
       }
     }
     it = RootNames.erase(it);
   }
   else{
     ++it;
   }

 }

 for(vector<TString>::iterator it = RootNames.begin(); it != RootNames.end();){

   if((*it).Contains("ntuple_MM_2024")
   || (*it).Contains("ntuple_MM_2025")
   || (*it).Contains("Fake_Matrix_Electron")
   || (*it).Contains("Fake_Matrix_Muon")
   || (*it).Contains("matrix_Data")
   || (*it).Contains("nominal_Data")
   || (*it).Contains("nominal_Diboson")
   || (*it).Contains("nominal_Triboson")
   || (*it).Contains("nominal_ttV")
   || (*it).Contains("nominal_PI")
   || (*it).Contains("nominal_Wjets")
   || (*it).Contains("nominal_Ztautau")){
     ++it;
     continue;
   }

   if((*it).Contains("nominal_TopQuark_") || (*it).Contains("nominal_Loose_TopQuark_")){
     if((AdditionalSelection == "") && ((*it).Contains("Sys_"))){
       it = RootNames.erase(it);
     }
     else if((AdditionalSelection == "Fragmentation_Herwig7") && !((*it).Contains("Fragmentation_Herwig7"))){
       it = RootNames.erase(it);
     }
     else if((AdditionalSelection == "HardScatter_MCAdNlo") && !((*it).Contains("HardScatter_MCAdNlo"))){
       it = RootNames.erase(it);
     }
     else if((AdditionalSelection == "ISR") && !((*it).Contains("ISR"))){
       it = RootNames.erase(it);
     }
     else if((AdditionalSelection == "MassDown") && !((*it).Contains("MassDown"))){
       it = RootNames.erase(it);
     }
     else if((AdditionalSelection == "MassUP") && !((*it).Contains("MassUP")) && !((*it).Contains("MassUp"))){
       it = RootNames.erase(it);
     }
     else{
       ++it;
     }
   }
   else{
     ++it;
   }
 }

}

void TreeForZPrime::BkgSelection(TString name)
{
 if(name == "all") return;

 for(vector<TString>::iterator it = RootNames.begin(); it != RootNames.end();){

   if(name == "TopQuark" && !((*it).Contains("TopQuark") || (*it).Contains("singleTop"))){
     it = RootNames.erase(it);
   }
   else{
     ++it;
   }
 }

 RootTypes.clear();
 for(int i = 0; i < RootNames.size(); i++){
   TString RootType = GetRootType(RootNames.at(i));
   RootTypes.push_back(RootType);
 }

}

TString TreeForZPrime::GetRootType(TString name)
{
 TString RootType;

 if(name.Contains("nominal_Data") || name.Contains("nominal_Loose_Data")){
   RootType = "Data";
 }
 else if(name.Contains("DrellYan") || name.Contains("Ztoee") || name.Contains("Ztomumu")){
   RootType = "DrellYan";
 }
 else if(name.Contains("PI_")){
   RootType = "PhotonInduced";
 }
 else if(name.Contains("TopQuark") || name.Contains("singleTop")){
   RootType = "TopQuark";
 }
 else if(name.Contains("Diboson")){
   RootType = "Diboson";
 }
 else if(name.Contains("Triboson")){
   RootType = "Triboson";
 }
 else if(name.Contains("ttV")){
   RootType = "ttV";
 }
 else if(name.Contains("ntuple_MM") || name.Contains("matrix_Data") || name.Contains("Fake_Matrix_Electron") || name.Contains("Fake_Matrix_Muon")){
   RootType = "Wjets_DD";
 }
 else if(name.Contains("Ztautau")){
   RootType = "Ztautau";
 }
 else if(name.Contains("Wjets_")){
   RootType = "Wjets";
 }

 return RootType;
}

void TreeForZPrime::updateCutFlow(TH1D *inCutFlow, std::map<std::string, double> *inLabelMap, std::string cutName, double step, bool doUpdate){
  if(!doUpdate) return;
  double Xpos = -1;
  if(inLabelMap->count(cutName)){
    Xpos = (*inLabelMap)[cutName];
  }
  else{
    (*inLabelMap)[cutName] = inLabelMap->size() * 1.; //this will gives 1 when first call, strange ... doesn't happen with stand alone root run
    std::cout<<"registering new cut "<<cutName<<" at position "<<(*inLabelMap)[cutName]<<std::endl;
    inCutFlow->GetXaxis()->SetBinLabel(inLabelMap->size()+1, cutName.c_str());
    Xpos = (*inLabelMap)[cutName];
  }
  inCutFlow->Fill(Xpos,step);
}


void TreeForZPrime::SaveFile()
{
 hf->cd();

 hf->Write();
 hf->Close();
}

