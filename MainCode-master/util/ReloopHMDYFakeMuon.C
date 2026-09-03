#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include <Eigen/Dense>

using namespace std;

int main(int argc, char** argv)
{
 TFile* file = new TFile("/msu/data/t3work12/yaofu/HMDYSamples/ForPlots/output_matrix_Data_all_Dimuon.root");
 TTree* tree = (TTree *)file->Get("hmdyTree");

   Double_t        Weight_Lepton1_SF;
   Double_t        Weight_Lepton2_SF;
   Int_t           RunNumber;
   ULong64_t       EventNumber;
   Double_t        mcChannelNumber;
   Double_t        RecoDilRapidity;
   Double_t        RecoDilPhi;
   Double_t        RecoDilMass;
   Double_t        RecoPseudoDilMass;
   Double_t        RecoDilPt;
   Double_t        RecoPhiStar;
   Double_t        RecoCosThetaStar;
   Bool_t          eeChannel;
   Bool_t          mumuChannel;
   Bool_t          emuChannel;
   Bool_t          FwdeeChannel;

   Int_t           eeChannel_int;
   Int_t           mumuChannel_int;
   Int_t           emuChannel_int;
   Int_t           FwdeeChannel_int;

   Double_t        TruthDilMass_Born;
   Double_t        TruthDilRapidity_Born;
   Double_t        Lepton1_Pt;
   Double_t        Lepton2_Pt;
   Double_t        Lepton1_Phi;
   Double_t        Lepton2_Phi;
   Double_t        Lepton1_Eta;
   Double_t        Lepton2_Eta;
   Double_t        pTllReweight;
   Double_t        ChargeMisIDSFWeight;
   Double_t        LeptonSFWeight;
   Double_t        PileupWeight;
   Int_t           n_Bjets;
   Double_t        MET_Et;
   Double_t        Lepton1_z0;
   Double_t        Lepton2_z0;
   Double_t        Lepton1_d0sig;
   Double_t        Lepton2_d0sig;
   Double_t        Mu;
   Double_t        MuActual;
   Double_t        PhiRF;
   Double_t        Weight_kFactor_Old;
   Double_t        Weight_kFactor_QCDEW;
   Double_t        Weight_kFactor_New_CT18NNLO;
   Double_t        Weight_kFactor_New_CT18ANNLO;
   Double_t        Weight_kFactor_PowhegtoSherpa;
   Bool_t          pass_ee_TT;
   Bool_t          pass_ee_TL;
   Bool_t          pass_ee_LT;
   Bool_t          pass_ee_LL;
   vector<int>     *ele_isLHLoose;
   vector<int>     *ele_isLHMedium;
   vector<int>     *ele_isFixedCutTightIso;
   Double_t        RecoWeight;
   Double_t        RecoWeight_stats_1up;
   Double_t        RecoWeight_stats_1down;
   Double_t        RecoWeight_d0Sig_1up;
   Double_t        RecoWeight_d0Sig_1down;

   TBranch        *b_Weight_Lepton1_SF;   //!
   TBranch        *b_Weight_Lepton2_SF;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_RecoDilRapidity;   //!
   TBranch        *b_RecoDilPhi;   //!
   TBranch        *b_RecoDilMass;   //!
   TBranch        *b_RecoPseudoDilMass;   //!
   TBranch        *b_RecoDilPt;   //!
   TBranch        *b_RecoPhiStar;   //!
   TBranch        *b_RecoCosThetaStar;   //!
   TBranch        *b_eeChannel;   //!
   TBranch        *b_mumuChannel;   //!
   TBranch        *b_emuChannel;   //!
   TBranch        *b_FwdeeChannel;   //!
   TBranch        *b_TruthDilMass_Born;   //!
   TBranch        *b_TruthDilRapidity_Born;   //!
   TBranch        *b_Lepton1_Pt;   //!
   TBranch        *b_Lepton2_Pt;   //!
   TBranch        *b_Lepton1_Phi;   //!
   TBranch        *b_Lepton2_Phi;   //!
   TBranch        *b_Lepton1_Eta;   //!
   TBranch        *b_Lepton2_Eta;   //!
   TBranch        *b_pTllReweight;   //!
   TBranch        *b_ChargeMisIDSFWeight;   //!
   TBranch        *b_LeptonSFWeight;   //!
   TBranch        *b_PileupWeight;   //!
   TBranch        *b_n_Bjets;   //!
   TBranch        *b_MET_Et;   //!
   TBranch        *b_Lepton1_z0;   //!
   TBranch        *b_Lepton2_z0;   //!
   TBranch        *b_Lepton1_d0sig;   //!
   TBranch        *b_Lepton2_d0sig;   //!
   TBranch        *b_Mu;   //!
   TBranch        *b_MuActual;   //!
   TBranch        *b_PhiRF;   //!
   TBranch        *b_Weight_kFactor_Old;   //!
   TBranch        *b_Weight_kFactor_QCDEW;   //!
   TBranch        *b_Weight_kFactor_New_CT18NNLO;   //!
   TBranch        *b_Weight_kFactor_New_CT18ANNLO;   //!
   TBranch        *b_Weight_kFactor_PowhegtoSherpa;   //!
   TBranch        *b_pass_ee_TT;   //!
   TBranch        *b_pass_ee_TL;   //!
   TBranch        *b_pass_ee_LT;   //!
   TBranch        *b_pass_ee_LL;   //!
   TBranch        *b_ele_isLHLoose;   //!
   TBranch        *b_ele_isLHMedium;   //!
   TBranch        *b_ele_isFixedCutTightIso;   //!
   TBranch        *b_RecoWeight;   //!
   TBranch        *b_RecoWeight_stats_1up;   //!
   TBranch        *b_RecoWeight_stats_1down;   //!
   TBranch        *b_RecoWeight_d0Sig_1up;   //!
   TBranch        *b_RecoWeight_d0Sig_1down;   //!

   ele_isLHLoose = 0;
   ele_isLHMedium = 0;
   ele_isFixedCutTightIso = 0;

   vector<int> v_ele_isLHLoose;
   vector<int> v_ele_isLHMedium;
   vector<int> v_ele_isFixedCutTightIso;

   tree->SetBranchAddress("RecoDilRapidity", &RecoDilRapidity, &b_RecoDilRapidity);
   tree->SetBranchAddress("RecoDilMass", &RecoDilMass, &b_RecoDilMass);
   tree->SetBranchAddress("RecoDilPt", &RecoDilPt, &b_RecoDilPt);
   tree->SetBranchAddress("RecoPhiStar", &RecoPhiStar, &b_RecoPhiStar);
   tree->SetBranchAddress("RecoCosThetaStar", &RecoCosThetaStar, &b_RecoCosThetaStar);
   tree->SetBranchAddress("RecoWeight", &RecoWeight, &b_RecoWeight);
   tree->SetBranchAddress("RecoWeight_stats_1up", &RecoWeight_stats_1up, &b_RecoWeight_stats_1up);
   tree->SetBranchAddress("RecoWeight_stats_1down", &RecoWeight_stats_1down, &b_RecoWeight_stats_1down);
   tree->SetBranchAddress("RecoWeight_d0Sig_1up", &RecoWeight_d0Sig_1up, &b_RecoWeight_d0Sig_1up);
   tree->SetBranchAddress("RecoWeight_d0Sig_1down", &RecoWeight_d0Sig_1down, &b_RecoWeight_d0Sig_1down);
   tree->SetBranchAddress("eeChannel", &eeChannel_int, &b_eeChannel);
   tree->SetBranchAddress("mumuChannel", &mumuChannel_int, &b_mumuChannel);
   tree->SetBranchAddress("emuChannel", &emuChannel_int, &b_emuChannel);
   tree->SetBranchAddress("FwdeeChannel", &FwdeeChannel_int, &b_FwdeeChannel);
   tree->SetBranchAddress("Lepton1_Pt", &Lepton1_Pt, &b_Lepton1_Pt);
   tree->SetBranchAddress("Lepton2_Pt", &Lepton2_Pt, &b_Lepton2_Pt);
   tree->SetBranchAddress("Lepton1_Phi", &Lepton1_Phi, &b_Lepton1_Phi);
   tree->SetBranchAddress("Lepton2_Phi", &Lepton2_Phi, &b_Lepton2_Phi);
   tree->SetBranchAddress("Lepton1_Eta", &Lepton1_Eta, &b_Lepton1_Eta);
   tree->SetBranchAddress("Lepton2_Eta", &Lepton2_Eta, &b_Lepton2_Eta);
   tree->SetBranchAddress("MET_Et", &MET_Et, &b_MET_Et);
   tree->SetBranchAddress("Weight_kFactor_Old", &Weight_kFactor_Old, &b_Weight_kFactor_Old);
   tree->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   tree->SetBranchAddress("TruthDilMass_Born", &TruthDilMass_Born, &b_TruthDilMass_Born);
   tree->SetBranchAddress("ChargeMisIDSFWeight", &ChargeMisIDSFWeight, &b_ChargeMisIDSFWeight);
   tree->SetBranchAddress("LeptonSFWeight", &LeptonSFWeight, &b_LeptonSFWeight);
   tree->SetBranchAddress("PileupWeight", &PileupWeight, &b_PileupWeight);
   tree->SetBranchAddress("Weight_kFactor_New_CT18ANNLO", &Weight_kFactor_New_CT18ANNLO, &b_Weight_kFactor_New_CT18ANNLO);

 TFile* outfile = new TFile("output_matrix_Data_all_Dimuon_reloop.root", "RECREATE");
 outfile->cd();
 TTree* outtree = new TTree("hmdyTree", "hmdyTree");

 outtree->Branch("Weight_Lepton1_SF",                &Weight_Lepton1_SF,            "Weight_Lepton1_SF/D");
 outtree->Branch("Weight_Lepton2_SF",                &Weight_Lepton2_SF,            "Weight_Lepton2_SF/D");
 outtree->Branch("RunNumber",                        &RunNumber,                    "RunNumber/I");
 outtree->Branch("EventNumber",                      &EventNumber);
 outtree->Branch("mcChannelNumber",                  &mcChannelNumber,              "mcChannelNumber/D");
 outtree->Branch("RecoDilRapidity",                  &RecoDilRapidity,              "RecoDilRapidity/D");
 outtree->Branch("RecoDilPhi",                       &RecoDilPhi,                   "RecoDilPhi/D");
 outtree->Branch("RecoDilMass",                      &RecoDilMass,                  "RecoDilMass/D");
 outtree->Branch("RecoPseudoDilMass",                &RecoPseudoDilMass,            "RecoPseudoDilMass/D");
 outtree->Branch("RecoDilPt",                        &RecoDilPt,                    "RecoDilPt/D");
 outtree->Branch("RecoPhiStar",                      &RecoPhiStar,                  "RecoPhiStar/D");
 outtree->Branch("RecoCosThetaStar",                 &RecoCosThetaStar,             "RecoCosThetaStar/D");
 outtree->Branch("eeChannel",                        &eeChannel);
 outtree->Branch("mumuChannel",                      &mumuChannel);
 outtree->Branch("emuChannel",                       &emuChannel);
 outtree->Branch("FwdeeChannel",                     &FwdeeChannel);
 outtree->Branch("TruthDilMass_Born",                &TruthDilMass_Born,            "TruthDilMass_Born/D");
 outtree->Branch("TruthDilRapidity_Born",            &TruthDilRapidity_Born,        "TruthDilRapidity_Born/D");
 outtree->Branch("Lepton1_Pt",                       &Lepton1_Pt,                   "Lepton1_Pt/D");
 outtree->Branch("Lepton2_Pt",                       &Lepton2_Pt,                   "Lepton2_Pt/D");
 outtree->Branch("Lepton1_Phi",                      &Lepton1_Phi,                  "Lepton1_Phi/D");
 outtree->Branch("Lepton2_Phi",                      &Lepton2_Phi,                  "Lepton2_Phi/D");
 outtree->Branch("Lepton1_Eta",                      &Lepton1_Eta,                  "Lepton1_Eta/D");
 outtree->Branch("Lepton2_Eta",                      &Lepton2_Eta,                  "Lepton2_Eta/D");
 outtree->Branch("pTllReweight",                     &pTllReweight,                 "pTllReweight/D");
 outtree->Branch("ChargeMisIDSFWeight",              &ChargeMisIDSFWeight,          "ChargeMisIDSFWeight/D");
 outtree->Branch("LeptonSFWeight",                   &LeptonSFWeight,               "LeptonSFWeight/D");
 outtree->Branch("PileupWeight",                     &PileupWeight,                 "PileupWeight/D");
 outtree->Branch("n_Bjets",                          &n_Bjets,                      "n_Bjets/I");
 outtree->Branch("MET_Et",                           &MET_Et,                       "MET_Et/D");
 outtree->Branch("Lepton1_z0",                       &Lepton1_z0,                   "Lepton1_z0/D");
 outtree->Branch("Lepton2_z0",                       &Lepton2_z0,                   "Lepton2_z0/D");
 outtree->Branch("Lepton1_d0sig",                    &Lepton1_d0sig,                "Lepton1_d0sig/D");
 outtree->Branch("Lepton2_d0sig",                    &Lepton2_d0sig,                "Lepton2_d0sig/D");
 outtree->Branch("Mu",                               &Mu,                           "Mu/D");
 outtree->Branch("MuActual",                         &MuActual,                     "MuActual/D");
 outtree->Branch("PhiRF",                            &PhiRF,                        "PhiRF/D");
 outtree->Branch("Weight_kFactor_Old",               &Weight_kFactor_Old,           "Weight_kFactor_Old/D");
 outtree->Branch("Weight_kFactor_QCDEW",             &Weight_kFactor_QCDEW,         "Weight_kFactor_QCDEW/D");
 outtree->Branch("Weight_kFactor_New_CT18NNLO",      &Weight_kFactor_New_CT18NNLO,  "Weight_kFactor_New_CT18NNLO/D");
 outtree->Branch("Weight_kFactor_New_CT18ANNLO",     &Weight_kFactor_New_CT18ANNLO, "Weight_kFactor_New_CT18ANNLO/D");
 outtree->Branch("Weight_kFactor_PowhegtoSherpa",    &Weight_kFactor_PowhegtoSherpa,"Weight_kFactor_PowhegtoSherpa/D");
 outtree->Branch("RecoWeight",                       &RecoWeight,                    "RecoWeight/D");
 outtree->Branch("RecoWeight_stats_1up",             &RecoWeight_stats_1up,          "RecoWeight_stats_1up/D");
 outtree->Branch("RecoWeight_stats_1down",           &RecoWeight_stats_1down,        "RecoWeight_stats_1down/D");
 outtree->Branch("RecoWeight_d0Sig_1up",             &RecoWeight_d0Sig_1up,          "RecoWeight_d0Sig_1up/D");
 outtree->Branch("RecoWeight_d0Sig_1down",           &RecoWeight_d0Sig_1down,        "RecoWeight_d0Sig_1down/D");

 int Entries = tree->GetEntries();

 int ientry = 0;
 for(int i = 0; i < Entries; i++){
   tree->GetEntry(i);

   if(i % 1000000 == 0) cout<<i<<" events have finished."<<endl;

   eeChannel = eeChannel_int;
   mumuChannel = mumuChannel_int;
   emuChannel = emuChannel_int;
   FwdeeChannel = FwdeeChannel_int;

   outtree->Fill();
 }

 cout<<"Tree Entries = "<<outtree->GetEntries()<<endl;

 outfile->cd();
 outtree->Write();
 outfile->Close();

 return 1;
}
