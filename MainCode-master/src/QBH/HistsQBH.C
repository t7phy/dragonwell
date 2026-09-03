#define HistsQBH_cxx
#include "QBH/HistsQBH.h"

using namespace std;

HistsQBH::HistsQBH()
{
}

void HistsQBH::bookHists(int TotalThread)
{
 this->TotalThread = TotalThread;
 TString tail = "";

 int LepJetMass_bin = 20;        double LepJetMass_left = 700.0;        double LepJetMass_right = 10000.0;
 int LeadingLeptonPt_bin = 20;   double LeadingLeptonPt_left = 130.0;   double LeadingLeptonPt_right = 500.0;
 int LeadingLeptonEta_bin = 20;  double LeadingLeptonEta_left = -2.5;   double LeadingLeptonEta_right = 2.5;
 int LeadingJetPt_bin = 20;      double LeadingJetPt_left = 130.0;      double LeadingJetPt_right = 500.0;
 int Njets_bin = 10;             double Njets_left = 0.0;               double Njets_right = 10.0;
 int MissingET_bin = 40;         double MissingET_left = 10.0;          double MissingET_right = 300.0;
 int Mll_bin = 20;               double Mll_left = 70.0;                double Mll_right = 110.0;
 int DeltaRLepJet_bin = 20;      double DeltaRLepJet_left = 0.0;        double DeltaRLepJet_right = 5.0;
 int detaLepJet_bin = 20;        double detaLepJet_left = 0.0;          double detaLepJet_right = 5.0;
 int dphiLepJet_bin = 20;        double dphiLepJet_left = 0.0;          double dphiLepJet_right = 3.2;
 int METSig_bin = 32;            double METSig_left = 0.0;              double METSig_right = 16.0;
 int d0Sig_bin = 40;             double d0Sig_left = -10.0;             double d0Sig_right = 10.0;

 bookAllProcessHist(LepJetMass, "LepJetMass", "LepJetMass", LepJetMass_bin, LepJetMass_left, LepJetMass_right);
 bookAllProcessHist(LepJetMass_El, "LepJetMass_El", "LepJetMass_El", LepJetMass_bin, LepJetMass_left, LepJetMass_right);
 bookAllProcessHist(LepJetMass_Mu, "LepJetMass_Mu", "LepJetMass_Mu", LepJetMass_bin, LepJetMass_left, LepJetMass_right);
 bookAllProcessHist(LepJetMass_LowBornMass, "LepJetMass_LowBornMass", "LepJetMass_LowBornMass", LepJetMass_bin, LepJetMass_left, LepJetMass_right);
 bookAllProcessHist(LepJetMass_HighBornMass, "LepJetMass_HighBornMass", "LepJetMass_HighBornMass", LepJetMass_bin, LepJetMass_left, LepJetMass_right);
 bookAllProcessHist(LepJetMass_LowBornMass_El, "LepJetMass_LowBornMass_El", "LepJetMass_LowBornMass_El", LepJetMass_bin, LepJetMass_left, LepJetMass_right);
 bookAllProcessHist(LepJetMass_HighBornMass_El, "LepJetMass_HighBornMass_El", "LepJetMass_HighBornMass_El", LepJetMass_bin, LepJetMass_left, LepJetMass_right);
 bookAllProcessHist(LepJetMass_LowBornMass_Mu, "LepJetMass_LowBornMass_Mu", "LepJetMass_LowBornMass_Mu", LepJetMass_bin, LepJetMass_left, LepJetMass_right);
 bookAllProcessHist(LepJetMass_HighBornMass_Mu, "LepJetMass_HighBornMass_Mu", "LepJetMass_HighBornMass_Mu", LepJetMass_bin, LepJetMass_left, LepJetMass_right);
 bookAllProcessHist(LeadingLeptonPt, "LeadingLeptonPt", "LeadingLeptonPt", LeadingLeptonPt_bin, LeadingLeptonPt_left, LeadingLeptonPt_right);
 bookAllProcessHist(LeadingLeptonEta, "LeadingLeptonEta", "LeadingLeptonEta", LeadingLeptonEta_bin, LeadingLeptonEta_left, LeadingLeptonEta_right);
 bookAllProcessHist(LeadingJetPt, "LeadingJetPt", "LeadingJetPt", LeadingJetPt_bin, LeadingJetPt_left, LeadingJetPt_right);
 bookAllProcessHist(Njets, "Njets", "Njets", Njets_bin, Njets_left, Njets_right);
 bookAllProcessHist(MissingET, "MissingET", "MissingET", MissingET_bin, MissingET_left, MissingET_right);
 bookAllProcessHist(Mll, "Mll", "Mll", Mll_bin, Mll_left, Mll_right);
 bookAllProcessHist(DeltaRLepJet, "DeltaRLepJet", "DeltaRLepJet", DeltaRLepJet_bin, DeltaRLepJet_left, DeltaRLepJet_right);
 bookAllProcessHist(detaLepJet, "detaLepJet", "detaLepJet", detaLepJet_bin, detaLepJet_left, detaLepJet_right);
 bookAllProcessHist(detaLepJet_El, "detaLepJet_El", "detaLepJet_El", detaLepJet_bin, detaLepJet_left, detaLepJet_right);
 bookAllProcessHist(detaLepJet_Mu, "detaLepJet_Mu", "detaLepJet_Mu", detaLepJet_bin, detaLepJet_left, detaLepJet_right);
 bookAllProcessHist(dphiLepJet, "dphiLepJet", "dphiLepJet", dphiLepJet_bin, dphiLepJet_left, dphiLepJet_right);
 bookAllProcessHist(dphiLepJet_El, "dphiLepJet_El", "dphiLepJet_El", dphiLepJet_bin, dphiLepJet_left, dphiLepJet_right);
 bookAllProcessHist(dphiLepJet_Mu, "dphiLepJet_Mu", "dphiLepJet_Mu", dphiLepJet_bin, dphiLepJet_left, dphiLepJet_right);
 bookAllProcessHist(METSig, "METSig", "METSig", METSig_bin, METSig_left, METSig_right);
 bookAllProcessHist(METSig_El, "METSig_El", "METSig_El", METSig_bin, METSig_left, METSig_right);
 bookAllProcessHist(METSig_Mu, "METSig_Mu", "METSig_Mu", METSig_bin, METSig_left, METSig_right);
 bookAllProcessHist(Lepton1_d0Sig, "Lepton1_d0Sig", "Lepton1_d0Sig", d0Sig_bin, d0Sig_left, d0Sig_right);
 bookAllProcessHist(Lepton2_d0Sig, "Lepton2_d0Sig", "Lepton2_d0Sig", d0Sig_bin, d0Sig_left, d0Sig_right);
 bookAllProcessHist(BornMass, "BornMass", "BornMass", 40, 60, 260);

 this->subName = "";
}

void HistsQBH::LinkClass(HistsQBH *hist)
{
}

void HistsQBH::outputInformation()
{
 if(doFakeRate){
   FakeRate->ElFakeEff->Write();
   FakeRate->MuFakeEff->Write();
   FakeRate->ElRealEff->Write();
   FakeRate->MuRealEff->Write();
   FakeRate->ElFakeTight->Write();
   FakeRate->ElFakeLoose->Write();
   FakeRate->MuFakeTight->Write();
   FakeRate->MuFakeLoose->Write();
   FakeRate->ElRealTight->Write();
   FakeRate->ElRealLoose->Write();
   FakeRate->MuRealTight->Write();
   FakeRate->MuRealLoose->Write();
 }
}
