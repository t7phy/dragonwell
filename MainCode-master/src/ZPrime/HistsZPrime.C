#define ZPrime_HistsZPrime_cxx
#include "ZPrime/HistsZPrime.h"

using namespace std;

HistsZPrime::HistsZPrime()
{
}

void HistsZPrime::bookHists(int TotalThread)
{
 this->TotalThread = TotalThread;
 TString tail = "";

 int Mll_HighMass_bin = 12;  double Mll_HighMass_binning[13] = {130.0, 150.0, 175.0, 200.0, 230.0, 260.0, 300.0, 380.0, 500.0, 700.0, 1000.0, 1500.0, 5000.0};
 int Mll_LowMass_bin = 25;   double Mll_LowMass_left = 66.0; double Mll_LowMass_right = 116.0;
 int pTll_bin = 40;          double pTll_left = 0.0;         double pTll_right = 500.0;
 int costheta_bin = 20;      double costheta_left = -1.0;    double costheta_right = 1.0;
 int DilRapidity_bin = 12;   double DilRapidity_left = 0.0;  double DilRapidity_right = 2.5;
 int PhiStar_bin = 39;       double PhiStar_binning[40] = {0, 0.004, 0.008, 0.012, 0.016, 0.020, 0.024, 0.029, 0.034, 0.039, 0.045, 0.051, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 5, 10, 20, 50, 100};
 int LeadingEta_bin = 36;    double LeadingEta_binning[37] = {-3.0, -2.5, -2.35, -2.2, -2.05, -1.90, -1.75, -1.65, -1.52, -1.37, -1.22, -1.07, -0.92, -0.77, -0.62, -0.47, -0.32, -0.16, 0.0, 0.16, 0.32, 0.47, 0.62, 0.77, 0.92, 1.07, 1.22, 1.37, 1.52, 1.65, 1.75, 1.90, 2.05, 2.20, 2.35, 2.5, 3.0};
 int SubleadingEta_bin = 36; double SubleadingEta_binning[37] = {-3.0, -2.5, -2.35, -2.2, -2.05, -1.90, -1.75, -1.65, -1.52, -1.37, -1.22, -1.07, -0.92, -0.77, -0.62, -0.47, -0.32, -0.16, 0.0, 0.16, 0.32, 0.47, 0.62, 0.77, 0.92, 1.07, 1.22, 1.37, 1.52, 1.65, 1.75, 1.90, 2.05, 2.20, 2.35, 2.5, 3.0};
 int Phi_bin = 36;           double Phi_left = -3.14;        double Phi_right = 3.14;
 int LeadingPt_bin = 10;     double LeadingPt_binning[11] = {40.0, 50.0, 60.0, 80.0, 105.0, 140.0, 190.0, 300.0, 450.0, 700.0, 1000.0};
 int SubleadingPt_bin = 10;  double SubleadingPt_binning[11] = {30.0, 45.0, 60.0, 80.0, 105.0, 140.0, 190.0, 300.0, 450.0, 700.0, 1000.0};
 int z0_bin = 10;            double z0_left = -0.5;          double z0_right = 0.5;
 int d0Sig_bin = 20;         double d0Sig_left = -5.0;       double d0Sig_right = 5.0;

 int Mll_RecoFineBin_bin = 9; double Mll_RecoFineBin_binning[10] = {66.0, 80.0, 100.0, 116.0, 130.0, 150.0, 175.0, 200.0, 230.0, 260.0};
 bookAllProcessHist(Mll_HighMass, "Mll_HighMass", "Mll_HighMass", Mll_HighMass_bin, Mll_HighMass_binning);
 //bookAllProcessHist(Mll_LowMass, "Mll_LowMass", "Mll_LowMass", Mll_LowMass_bin, Mll_LowMass_left, Mll_LowMass_right);
 bookAllProcessHist(Mll_FineBin, "Mll_FineBin", "Mll_FineBin", 160, 130.0, 8130.0);
 bookAllProcessHist(pTll, "pTll", "pTll", pTll_bin, pTll_left, pTll_right);
 //bookAllProcessHist(costheta, "costheta", "costheta", costheta_bin, costheta_left, costheta_right);
 bookAllProcessHist(DilRapidity, "DilRapidity", "DilRapidity", DilRapidity_bin, DilRapidity_left, DilRapidity_right);
 //bookAllProcessHist(PhiStar, "PhiStar", "PhiStar", PhiStar_bin, PhiStar_binning);
 bookAllProcessHist(LeadingLepEta, "LeadingLepEta", "LeadingLepEta", LeadingEta_bin, LeadingEta_binning);
 bookAllProcessHist(SubleadingLepEta, "SubleadingLepEta", "SubleadingLepEta", SubleadingEta_bin, SubleadingEta_binning);
 bookAllProcessHist(LeadingLepPhi, "LeadingLepPhi", "LeadingLepPhi", Phi_bin, Phi_left, Phi_right);
 bookAllProcessHist(SubleadingLepPhi, "SubleadingLepPhi", "SubleadingLepPhi", Phi_bin, Phi_left, Phi_right);
 bookAllProcessHist(LeadingLepPt, "LeadingLepPt", "LeadingLepPt", LeadingPt_bin, LeadingPt_binning);
 bookAllProcessHist(SubleadingLepPt, "SubleadingLepPt", "SubleadingLepPt", SubleadingPt_bin, SubleadingPt_binning);
 //bookAllProcessHist(Lepton1_z0, "Lepton1_z0", "Lepton1_z0", z0_bin, z0_left, z0_right);
 //bookAllProcessHist(Lepton2_z0, "Lepton2_z0", "Lepton2_z0", z0_bin, z0_left, z0_right);
 //bookAllProcessHist(Lepton1_d0Sig, "Lepton1_d0Sig", "Lepton1_d0Sig", d0Sig_bin, d0Sig_left, d0Sig_right);
 //bookAllProcessHist(Lepton2_d0Sig, "Lepton2_d0Sig", "Lepton2_d0Sig", d0Sig_bin, d0Sig_left, d0Sig_right);

 //bookAllProcessHist(DilRapidity_HighMass, "DilRapidity_HighMass", "DilRapidity_HighMass", DilRapidity_bin, DilRapidity_left, DilRapidity_right);
 //bookAllProcessHist(DilRapidity_LowMass,  "DilRapidity_LowMass",  "DilRapidity_LowMass", DilRapidity_bin, DilRapidity_left, DilRapidity_right);

 bookAllProcessHist(LooseLepton1Eta, "LooseLepton1Eta", "LooseLepton1Eta", 36, 0, 3.0);
 bookAllProcessHist(LooseLepton1Pt,  "LooseLepton1Pt",  "LooseLepton1Pt", 100, 28, 500);
 //bookAllProcessHist(LooseLepton3Eta, "LooseLepton3Eta", "LooseLepton3Eta", 36, 0, 2.5);
 bookAllProcessHist(TightLepton1Eta, "TightLepton1Eta", "TightLepton1Eta", 36, 0, 3.0);
 bookAllProcessHist(TightLepton1Pt,  "TightLepton1Pt",  "TightLepton1Pt", 100, 28, 500);
 //bookAllProcessHist(TightLepton3Eta, "TightLepton3Eta", "TightLepton3Eta", 36, 0, 2.5);
 //bookAllProcessHist(LooseMass_eem,   "LooseMass_eem",   "LooseMass_eem", 10, 70, 110);
 //bookAllProcessHist(TightMass_eem,   "TightMass_eem",   "TightMass_eem", 10, 70, 110);
 //bookAllProcessHist(LooseLepton3_d0Sig_eem, "LooseLepton3_d0Sig_eem", "LooseLepton3_d0Sig_eem", 40, 0, 20.0);
 //bookAllProcessHist(TightLepton3_d0Sig_eem, "TightLepton3_d0Sig_eem", "TightLepton3_d0Sig_eem", 40, 0, 20.0);

 int Mass_2D_bin = 4;      double Mass_2D_binning[5] = {116.0, 150.0, 200.0, 300.0, 5000.0};
 int CosTheta_2D_bin = 10; double CosTheta_2D_binning[11] = {-1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0};
 int Rapidity_2D_bin = 10; double Rapidity_2D_binning[11] = {0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5};
 //bookAllProcessHist(HighMass_CosTheta, "HighMass_CosTheta", "HighMass_CosTheta", Mass_2D_bin, Mass_2D_binning, CosTheta_2D_bin, CosTheta_2D_binning);
 //bookAllProcessHist(HighMass_Rapidity, "HighMass_Rapidity", "HighMass_Rapidity", Mass_2D_bin, Mass_2D_binning, Rapidity_2D_bin, Rapidity_2D_binning);

 //int RealEff_pt_bin = 24;  double RealEff_pt_binning[25] = {30.0, 32.5, 35.0, 37.5, 40.0, 42.5, 45.0, 47.5, 50.0, 52.5, 55.0, 57.5, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 150.0, 250.0, 500.0, 1000.0, 2000.0, 4000.0};
 int RealEff_pt_bin = 18; double RealEff_pt_binning[19] = {30.0, 32.0, 34.0, 36.0, 38.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 85.0, 105.0, 120.0, 140.0, 200.0, 300.0, 500.0, 4000.0};
 //int RealEff_pt_bin = 10;  double RealEff_pt_binning[11] = {0.0, 30.0, 45.0, 60.0, 90.0, 150.0, 250.0, 500.0, 1000.0, 2000.0, 4000.0};
 //int RealEff_eta_bin = 11; double RealEff_eta_binning[12] = {0.0, 0.2, 0.45, 0.7, 0.9, 1.37, 1.52, 1.7, 2.01, 2.25, 2.5, 3.0};
 int RealEff_pt_rough_bin = 7;  double RealEff_pt_rough_binning[8] = {30.0, 45.0, 60.0, 90.0, 150.0, 250.0, 500.0, 4000.0};
 int RealEff_eta_bin = 6; double RealEff_eta_binning[7] = {0.0, 0.45, 0.9, 1.37, 1.52, 2.01, 2.47};
 int RealEff_d0sig_bin = 7; double RealEff_d0sig_binning[8] = {0.0, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0};
 int RealEff_ptdiff_bin = 10; double RealEff_ptdiff_binning[11] = {0.0, 0.1, 0.3, 0.5, 1.0, 2.0, 5.0, 10.0, 20.0, 50.0, 100.0};
 int FakeEff_pt_bin = 18; double FakeEff_pt_binning[19] = {30.0, 32.0, 34.0, 36.0, 38.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 85.0, 105.0, 120.0, 140.0, 200.0, 300.0, 500.0, 4000.0};
 int FakeEff_eta_bin = 6; double FakeEff_eta_binning[7] = {0.0, 0.45, 0.9, 1.37, 1.52, 2.01, 2.47};

 int RealEff_mu_pt_bin = 7;  double RealEff_mu_pt_binning[8] = {30.0, 40.0, 60.0, 90.0, 150.0, 250.0, 500.0, 4000.0};
 int RealEff_mu_eta_bin = 5; double RealEff_mu_eta_binning[6] = {0.0, 0.5, 1.01, 1.1, 1.5, 2.5};
 int FakeEff_mu_pt_bin = 3; double FakeEff_mu_pt_binning[4] = {30.0, 40.0, 80.0, 4000.0};
 int FakeEff_mu_eta_bin = 3; double FakeEff_mu_eta_binning[4] = {0.0, 1.01, 1.1, 2.5};

 //bookAllProcessHist(LooseLepton3Pt,  "LooseLepton3Pt",  "LooseLepton3Pt", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning);
 //bookAllProcessHist(TightLepton3Pt,  "TightLepton3Pt",  "TightLepton3Pt", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning);

 this->subName = "";

 //vector<double> TruthMassBinning = {120.0, 180.0, 250.0, 400.0, 600.0, 800.0, 1000.0, 1250.0, 1500.0, 1750.0, 2000.0, 2250.0, 2500.0, 2750.0, 3000.0, 3500.0, 4000.0, 4500.0, 5000.0, 1000000.0};
 vector<double> TruthMassBinning = {120.0, 1000000.0};
 vector<double> TruthMassBinningA4 = {120.0, 300.0, 500.0, 2000.0, 5000.0, 10000.0};
 vector<double> TruthPtBinning = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 200.0, 300.0, 400.0, 1000.0};
 vector<double> TruthYBinning = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

 BookAngularHist(L0_Mass_QT_ZY_uu, "L0_Mass_QT_ZY_uu", "L0", TruthMassBinning.size() - 1, &TruthMassBinning[0], TruthPtBinning.size() - 1, &TruthPtBinning[0], TruthYBinning.size() - 1, &TruthYBinning[0]);
 BookAngularHist(A0_Mass_QT_ZY_uu, "A0_Mass_QT_ZY_uu", "A0", TruthMassBinning.size() - 1, &TruthMassBinning[0], TruthPtBinning.size() - 1, &TruthPtBinning[0], TruthYBinning.size() - 1, &TruthYBinning[0]);
 BookAngularHist(A1_Mass_QT_ZY_uu, "A1_Mass_QT_ZY_uu", "A1", TruthMassBinning.size() - 1, &TruthMassBinning[0], TruthPtBinning.size() - 1, &TruthPtBinning[0], TruthYBinning.size() - 1, &TruthYBinning[0]);
 BookAngularHist(A2_Mass_QT_ZY_uu, "A2_Mass_QT_ZY_uu", "A2", TruthMassBinning.size() - 1, &TruthMassBinning[0], TruthPtBinning.size() - 1, &TruthPtBinning[0], TruthYBinning.size() - 1, &TruthYBinning[0]);
 BookAngularHist(A3_Mass_QT_ZY_uu, "A3_Mass_QT_ZY_uu", "A3", TruthMassBinning.size() - 1, &TruthMassBinning[0], TruthPtBinning.size() - 1, &TruthPtBinning[0], TruthYBinning.size() - 1, &TruthYBinning[0]);
 BookAngularHist(A4_Mass_QT_ZY_uu, "A4_Mass_QT_ZY_uu", "A4", TruthMassBinningA4.size() - 1, &TruthMassBinningA4[0], TruthPtBinning.size() - 1, &TruthPtBinning[0], TruthYBinning.size() - 1, &TruthYBinning[0]);
 BookAngularHist(L0_Mass_QT_ZY_dd, "L0_Mass_QT_ZY_dd", "L0", TruthMassBinning.size() - 1, &TruthMassBinning[0], TruthPtBinning.size() - 1, &TruthPtBinning[0], TruthYBinning.size() - 1, &TruthYBinning[0]);
 BookAngularHist(A0_Mass_QT_ZY_dd, "A0_Mass_QT_ZY_dd", "A0", TruthMassBinning.size() - 1, &TruthMassBinning[0], TruthPtBinning.size() - 1, &TruthPtBinning[0], TruthYBinning.size() - 1, &TruthYBinning[0]);
 BookAngularHist(A1_Mass_QT_ZY_dd, "A1_Mass_QT_ZY_dd", "A1", TruthMassBinning.size() - 1, &TruthMassBinning[0], TruthPtBinning.size() - 1, &TruthPtBinning[0], TruthYBinning.size() - 1, &TruthYBinning[0]);
 BookAngularHist(A2_Mass_QT_ZY_dd, "A2_Mass_QT_ZY_dd", "A2", TruthMassBinning.size() - 1, &TruthMassBinning[0], TruthPtBinning.size() - 1, &TruthPtBinning[0], TruthYBinning.size() - 1, &TruthYBinning[0]);
 BookAngularHist(A3_Mass_QT_ZY_dd, "A3_Mass_QT_ZY_dd", "A3", TruthMassBinning.size() - 1, &TruthMassBinning[0], TruthPtBinning.size() - 1, &TruthPtBinning[0], TruthYBinning.size() - 1, &TruthYBinning[0]);
 BookAngularHist(A4_Mass_QT_ZY_dd, "A4_Mass_QT_ZY_dd", "A4", TruthMassBinningA4.size() - 1, &TruthMassBinningA4[0], TruthPtBinning.size() - 1, &TruthPtBinning[0], TruthYBinning.size() - 1, &TruthYBinning[0]);


 Book2DHist(RealLeptonPtEta_El_Loose, "RealLeptonPtEta_El_Loose", "RealLeptonPtEta_El_Loose", RealEff_pt_bin, RealEff_pt_binning, RealEff_eta_bin, RealEff_eta_binning);
 Book2DHist(RealLeptonPtEta_El_Tight, "RealLeptonPtEta_El_Tight", "RealLeptonPtEta_El_Tight", RealEff_pt_bin, RealEff_pt_binning, RealEff_eta_bin, RealEff_eta_binning);
 Book2DHist(RealLeptonPtEta_Mu_Loose, "RealLeptonPtEta_Mu_Loose", "RealLeptonPtEta_Mu_Loose", RealEff_mu_pt_bin, RealEff_mu_pt_binning, RealEff_mu_eta_bin, RealEff_mu_eta_binning);
 Book2DHist(RealLeptonPtEta_Mu_Tight, "RealLeptonPtEta_Mu_Tight", "RealLeptonPtEta_Mu_Tight", RealEff_mu_pt_bin, RealEff_mu_pt_binning, RealEff_mu_eta_bin, RealEff_mu_eta_binning);

 Book2DHist(RealLepton1PtEta_El_Loose, "RealLepton1PtEta_El_Loose", "RealLepton1PtEta_El_Loose", RealEff_pt_bin, RealEff_pt_binning, RealEff_eta_bin, RealEff_eta_binning);
 Book2DHist(RealLepton1PtEta_El_Tight, "RealLepton1PtEta_El_Tight", "RealLepton1PtEta_El_Tight", RealEff_pt_bin, RealEff_pt_binning, RealEff_eta_bin, RealEff_eta_binning);
 Book2DHist(RealLepton2PtEta_El_Loose, "RealLepton2PtEta_El_Loose", "RealLepton2PtEta_El_Loose", RealEff_pt_bin, RealEff_pt_binning, RealEff_eta_bin, RealEff_eta_binning);
 Book2DHist(RealLepton2PtEta_El_Tight, "RealLepton2PtEta_El_Tight", "RealLepton2PtEta_El_Tight", RealEff_pt_bin, RealEff_pt_binning, RealEff_eta_bin, RealEff_eta_binning);

 Book2DHist(RealLepton1Pt2Pt_El_Loose, "RealLepton1Pt2Pt_El_Loose", "RealLepton1Pt2Pt_El_Loose", RealEff_pt_bin, RealEff_pt_binning, RealEff_ptdiff_bin, RealEff_ptdiff_binning);
 Book2DHist(RealLepton1Pt2Pt_El_Tight, "RealLepton1Pt2Pt_El_Tight", "RealLepton1Pt2Pt_El_Tight", RealEff_pt_bin, RealEff_pt_binning, RealEff_ptdiff_bin, RealEff_ptdiff_binning);

 BookHist(RealLepton1Pt_FineBin_NoMassCut_Loose, "RealLepton1Pt_FineBin_NoMassCut_Loose", "RealLepton1Pt_FineBin_NoMassCut_Loose", 680, 30, 300);
 BookHist(RealLepton1Pt_FineBin_NoMassCut_MediumID, "RealLepton1Pt_FineBin_NoMassCut_MediumID", "RealLepton1Pt_FineBin_NoMassCut_MediumID", 680, 30, 300);
 BookHist(RealLepton1Pt_FineBin_NoMassCut_Iso, "RealLepton1Pt_FineBin_NoMassCut_Iso", "RealLepton1Pt_FineBin_NoMassCut_Iso", 680, 30, 300);
 BookHist(RealLepton1Pt_FineBin_NoMassCut_Tight, "RealLepton1Pt_FineBin_NoMassCut_Tight", "RealLepton1Pt_FineBin_NoMassCut_Tight", 680, 30, 300);
 BookHist(RealLepton1Pt_FineBin_NoMassCut_Truth, "RealLepton1Pt_FineBin_NoMassCut_Truth", "RealLepton1Pt_FineBin_NoMassCut_Truth", 680, 30, 300);
 BookHist(RealLepton2Pt_FineBin_NoMassCut_Loose, "RealLepton2Pt_FineBin_NoMassCut_Loose", "RealLepton2Pt_FineBin_NoMassCut_Loose", 680, 30, 300);
 BookHist(RealLepton2Pt_FineBin_NoMassCut_MediumID, "RealLepton2Pt_FineBin_NoMassCut_MediumID", "RealLepton2Pt_FineBin_NoMassCut_MediumID", 680, 30, 300);
 BookHist(RealLepton2Pt_FineBin_NoMassCut_Iso, "RealLepton2Pt_FineBin_NoMassCut_Iso", "RealLepton2Pt_FineBin_NoMassCut_Iso", 680, 30, 300);
 BookHist(RealLepton2Pt_FineBin_NoMassCut_Tight, "RealLepton2Pt_FineBin_NoMassCut_Tight", "RealLepton2Pt_FineBin_NoMassCut_Tight", 680, 30, 300);
 BookHist(RealLepton2Pt_FineBin_NoMassCut_Truth, "RealLepton2Pt_FineBin_NoMassCut_Truth", "RealLepton2Pt_FineBin_NoMassCut_Truth", 680, 30, 300);

 BookHist(RealLepton1Pt_FineBin_Mass116Cut_Loose, "RealLepton1Pt_FineBin_Mass116Cut_Loose", "RealLepton1Pt_FineBin_Mass116Cut_Loose", 680, 30, 300);
 BookHist(RealLepton1Pt_FineBin_Mass116Cut_MediumID, "RealLepton1Pt_FineBin_Mass116Cut_MediumID", "RealLepton1Pt_FineBin_Mass116Cut_MediumID", 680, 30, 300);
 BookHist(RealLepton1Pt_FineBin_Mass116Cut_Iso, "RealLepton1Pt_FineBin_Mass116Cut_Iso", "RealLepton1Pt_FineBin_Mass116Cut_Iso", 680, 30, 300);
 BookHist(RealLepton1Pt_FineBin_Mass116Cut_Tight, "RealLepton1Pt_FineBin_Mass116Cut_Tight", "RealLepton1Pt_FineBin_Mass116Cut_Tight", 680, 30, 300);
 BookHist(RealLepton1Pt_FineBin_Mass116Cut_Truth, "RealLepton1Pt_FineBin_Mass116Cut_Truth", "RealLepton1Pt_FineBin_Mass116Cut_Truth", 680, 30, 300);
 BookHist(RealLepton2Pt_FineBin_Mass116Cut_Loose, "RealLepton2Pt_FineBin_Mass116Cut_Loose", "RealLepton2Pt_FineBin_Mass116Cut_Loose", 680, 30, 300);
 BookHist(RealLepton2Pt_FineBin_Mass116Cut_MediumID, "RealLepton2Pt_FineBin_Mass116Cut_MediumID", "RealLepton2Pt_FineBin_Mass116Cut_MediumID", 680, 30, 300);
 BookHist(RealLepton2Pt_FineBin_Mass116Cut_Iso, "RealLepton2Pt_FineBin_Mass116Cut_Iso", "RealLepton2Pt_FineBin_Mass116Cut_Iso", 680, 30, 300);
 BookHist(RealLepton2Pt_FineBin_Mass116Cut_Tight, "RealLepton2Pt_FineBin_Mass116Cut_Tight", "RealLepton2Pt_FineBin_Mass116Cut_Tight", 680, 30, 300);
 BookHist(RealLepton2Pt_FineBin_Mass116Cut_Truth, "RealLepton2Pt_FineBin_Mass116Cut_Truth", "RealLepton2Pt_FineBin_Mass116Cut_Truth", 680, 30, 300);

 Book2DHist(Lepton1PtResolution_NoMassCut_Loose, "Lepton1PtResolution_NoMassCut_Loose", "Lepton1PtResolution_NoMassCut_Loose", 40, -1.0, 1.0, 100, 30.0, 230.0);
 Book2DHist(Lepton1PtResolution_NoMassCut_Tight, "Lepton1PtResolution_NoMassCut_Tight", "Lepton1PtResolution_NoMassCut_Tight", 40, -1.0, 1.0, 100, 30.0, 230.0);
 Book2DHist(Lepton2PtResolution_NoMassCut_Loose, "Lepton2PtResolution_NoMassCut_Loose", "Lepton2PtResolution_NoMassCut_Loose", 40, -1.0, 1.0, 100, 30.0, 230.0);
 Book2DHist(Lepton2PtResolution_NoMassCut_Tight, "Lepton2PtResolution_NoMassCut_Tight", "Lepton2PtResolution_NoMassCut_Tight", 40, -1.0, 1.0, 100, 30.0, 230.0);

 Book2DHist(Lepton1PtResolution_Mass116Cut_Loose, "Lepton1PtResolution_Mass116Cut_Loose", "Lepton1PtResolution_Mass116Cut_Loose", 40, -1.0, 1.0, 100, 30.0, 230.0);
 Book2DHist(Lepton1PtResolution_Mass116Cut_Tight, "Lepton1PtResolution_Mass116Cut_Tight", "Lepton1PtResolution_Mass116Cut_Tight", 40, -1.0, 1.0, 100, 30.0, 230.0);
 Book2DHist(Lepton2PtResolution_Mass116Cut_Loose, "Lepton2PtResolution_Mass116Cut_Loose", "Lepton2PtResolution_Mass116Cut_Loose", 40, -1.0, 1.0, 100, 30.0, 230.0);
 Book2DHist(Lepton2PtResolution_Mass116Cut_Tight, "Lepton2PtResolution_Mass116Cut_Tight", "Lepton2PtResolution_Mass116Cut_Tight", 40, -1.0, 1.0, 100, 30.0, 230.0);

 Book2DHist(FakeLeptonPtEta_El_Loose, "FakeLeptonPtEta_El_Loose", "FakeLeptonPtEta_El_Loose", FakeEff_pt_bin, FakeEff_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(FakeLeptonPtEta_El_Tight, "FakeLeptonPtEta_El_Tight", "FakeLeptonPtEta_El_Tight", FakeEff_pt_bin, FakeEff_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(FakeLeptonPtEta_El_PromptSubtr_up_Loose, "FakeLeptonPtEta_El_PromptSubtr_up_Loose", "FakeLeptonPtEta_El_PromptSubtr_up_Loose", FakeEff_pt_bin, FakeEff_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(FakeLeptonPtEta_El_PromptSubtr_up_Tight, "FakeLeptonPtEta_El_PromptSubtr_up_Tight", "FakeLeptonPtEta_El_PromptSubtr_up_Tight", FakeEff_pt_bin, FakeEff_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(FakeLeptonPtEta_El_PromptSubtr_down_Loose, "FakeLeptonPtEta_El_PromptSubtr_down_Loose", "FakeLeptonPtEta_El_PromptSubtr_down_Loose", FakeEff_pt_bin, FakeEff_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(FakeLeptonPtEta_El_PromptSubtr_down_Tight, "FakeLeptonPtEta_El_PromptSubtr_down_Tight", "FakeLeptonPtEta_El_PromptSubtr_down_Tight", FakeEff_pt_bin, FakeEff_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(FakeLeptonPtEta_El_MET_up_Loose, "FakeLeptonPtEta_El_MET_up_Loose", "FakeLeptonPtEta_El_MET_up_Loose", FakeEff_pt_bin, FakeEff_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(FakeLeptonPtEta_El_MET_up_Tight, "FakeLeptonPtEta_El_MET_up_Tight", "FakeLeptonPtEta_El_MET_up_Tight", FakeEff_pt_bin, FakeEff_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(FakeLeptonPtEta_El_MET_down_Loose, "FakeLeptonPtEta_El_MET_down_Loose", "FakeLeptonPtEta_El_MET_down_Loose", FakeEff_pt_bin, FakeEff_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(FakeLeptonPtEta_El_MET_down_Tight, "FakeLeptonPtEta_El_MET_down_Tight", "FakeLeptonPtEta_El_MET_down_Tight", FakeEff_pt_bin, FakeEff_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);

 // Muon
 Book2DHist(FakeLeptonPtEta_Mu_Loose, "FakeLeptonPtEta_Mu_Loose", "FakeLeptonPtEta_Mu_Loose", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning, FakeEff_mu_eta_bin, FakeEff_mu_eta_binning);
 Book2DHist(FakeLeptonPtEta_Mu_Tight, "FakeLeptonPtEta_Mu_Tight", "FakeLeptonPtEta_Mu_Tight", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning, FakeEff_mu_eta_bin, FakeEff_mu_eta_binning);
 Book2DHist(FakeLeptonPtEta_Mu_PromptSubtr_up_Loose, "FakeLeptonPtEta_Mu_PromptSubtr_up_Loose", "FakeLeptonPtEta_Mu_PromptSubtr_up_Loose", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning, FakeEff_mu_eta_bin, FakeEff_mu_eta_binning);
 Book2DHist(FakeLeptonPtEta_Mu_PromptSubtr_up_Tight, "FakeLeptonPtEta_Mu_PromptSubtr_up_Tight", "FakeLeptonPtEta_Mu_PromptSubtr_up_Tight", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning, FakeEff_mu_eta_bin, FakeEff_mu_eta_binning);
 Book2DHist(FakeLeptonPtEta_Mu_PromptSubtr_down_Loose, "FakeLeptonPtEta_Mu_PromptSubtr_down_Loose", "FakeLeptonPtEta_Mu_PromptSubtr_down_Loose", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning, FakeEff_mu_eta_bin, FakeEff_mu_eta_binning);
 Book2DHist(FakeLeptonPtEta_Mu_PromptSubtr_down_Tight, "FakeLeptonPtEta_Mu_PromptSubtr_down_Tight", "FakeLeptonPtEta_Mu_PromptSubtr_down_Tight", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning, FakeEff_mu_eta_bin, FakeEff_mu_eta_binning);
 Book2DHist(FakeLeptonPtEta_Mu_d0sig_up_Loose, "FakeLeptonPtEta_Mu_d0sig_up_Loose", "FakeLeptonPtEta_Mu_d0sig_up_Loose", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning, FakeEff_mu_eta_bin, FakeEff_mu_eta_binning);
 Book2DHist(FakeLeptonPtEta_Mu_d0sig_up_Tight, "FakeLeptonPtEta_Mu_d0sig_up_Tight", "FakeLeptonPtEta_Mu_d0sig_up_Tight", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning, FakeEff_mu_eta_bin, FakeEff_mu_eta_binning);
 Book2DHist(FakeLeptonPtEta_Mu_d0sig_down_Loose, "FakeLeptonPtEta_Mu_d0sig_down_Loose", "FakeLeptonPtEta_Mu_d0sig_down_Loose", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning, FakeEff_mu_eta_bin, FakeEff_mu_eta_binning);
 Book2DHist(FakeLeptonPtEta_Mu_d0sig_down_Tight, "FakeLeptonPtEta_Mu_d0sig_down_Tight", "FakeLeptonPtEta_Mu_d0sig_down_Tight", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning, FakeEff_mu_eta_bin, FakeEff_mu_eta_binning);

 // Closure
 BookHist(FakeLeptonPt_Mu_Loose, "FakeLeptonPt_Mu_Loose", "FakeLeptonPt_Mu_Loose", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning);
 BookHist(FakeLeptonPt_Mu_Tight, "FakeLeptonPt_Mu_Tight", "FakeLeptonPt_Mu_Tight", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning);

 int FakeEff_rough_pt_bin = 6; double FakeEff_rough_pt_binning[8] = {30.0, 40.0, 50.0, 60.0, 85.0, 100.0, 4000.0};
 int FakeEff_rough_eta_bin = 1; double FakeEff_rough_eta_binning[2] = {0.0, 2.47};

 Book2DHist(FakeLeptonPtEta_El_Wjets_Loose, "FakeLeptonPtEta_El_Wjets_Loose", "FakeLeptonPtEta_El_Wjets_Loose", FakeEff_rough_pt_bin, FakeEff_rough_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(FakeLeptonPtEta_El_Wjets_Tight, "FakeLeptonPtEta_El_Wjets_Tight", "FakeLeptonPtEta_El_Wjets_Tight", FakeEff_rough_pt_bin, FakeEff_rough_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(RealLeptonPtEta_El_Wjets_Loose, "RealLeptonPtEta_El_Wjets_Loose", "RealLeptonPtEta_El_Wjets_Loose", FakeEff_rough_pt_bin, FakeEff_rough_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(RealLeptonPtEta_El_Wjets_Tight, "RealLeptonPtEta_El_Wjets_Tight", "RealLeptonPtEta_El_Wjets_Tight", FakeEff_rough_pt_bin, FakeEff_rough_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);

 Book2DHist(RealLepton2PtEta_El_Wjets_Loose, "RealLepton2PtEta_El_Wjets_Loose", "RealLepton2PtEta_El_Wjets_Loose", FakeEff_rough_pt_bin, FakeEff_rough_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 Book2DHist(RealLepton2PtEta_El_Wjets_Tight, "RealLepton2PtEta_El_Wjets_Tight", "RealLepton2PtEta_El_Wjets_Tight", FakeEff_rough_pt_bin, FakeEff_rough_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 //bookAllProcessHist(LeptonPtClosure,  "LeptonPtClosure",  "LeptonPtClosure", FakeEff_rough_pt_bin, FakeEff_rough_pt_binning);

 //bookAllProcessHist(LooseLepton1PtEta, "LooseLepton1PtEta", "LooseLepton1PtEta", FakeEff_pt_bin, FakeEff_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 //bookAllProcessHist(LooseLepton3PtEta, "LooseLepton3PtEta", "LooseLepton3PtEta", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning, FakeEff_mu_eta_bin, FakeEff_mu_eta_binning);
 //bookAllProcessHist(TightLepton1PtEta, "TightLepton1PtEta", "TightLepton1PtEta", FakeEff_pt_bin, FakeEff_pt_binning, FakeEff_eta_bin, FakeEff_eta_binning);
 //bookAllProcessHist(TightLepton3PtEta, "TightLepton3PtEta", "TightLepton3PtEta", FakeEff_mu_pt_bin, FakeEff_mu_pt_binning, FakeEff_mu_eta_bin, FakeEff_mu_eta_binning);

 this->subName = "";
}

void HistsZPrime::LinkClass(HistsZPrime *hist)
{
}

void HistsZPrime::GetTransferFactor()
{
 // For 1D Transfer Factor
 TH1D* TopDD_em = (TH1D *)Mll_HighMass->SR_em_bkg->at(0)->GetHistPtr("TopQuark")->Clone("TopDD_em");
 TransferFactor_ee = (TH1D *)Mll_HighMass->SR_ee_bkg->at(0)->GetHistPtr("TopQuark")->Clone("TransferFactor_ee");
 TransferFactor_mm = (TH1D *)Mll_HighMass->SR_mm_bkg->at(0)->GetHistPtr("TopQuark")->Clone("TransferFactor_mm");

 TransferFactor_ee->Divide(TopDD_em);
 TransferFactor_mm->Divide(TopDD_em);

 // For HighMass CosTheta 2D Transfer Factor
 TH2D* TopDD_HighMass_CosTheta_em = (TH2D *)HighMass_CosTheta->SR_2D_em_bkg->at(0)->GetHistPtr2D("TopQuark")->Clone("TopDD_HighMass_CosTheta_em");
 TransferFactor_HighMass_CosTheta_ee = (TH2D *)HighMass_CosTheta->SR_2D_ee_bkg->at(0)->GetHistPtr2D("TopQuark")->Clone("TransferFactor_HighMass_CosTheta_ee");
 TransferFactor_HighMass_CosTheta_mm = (TH2D *)HighMass_CosTheta->SR_2D_mm_bkg->at(0)->GetHistPtr2D("TopQuark")->Clone("TransferFactor_HighMass_CosTheta_mm");

 TransferFactor_HighMass_CosTheta_ee->Divide(TopDD_HighMass_CosTheta_em);
 TransferFactor_HighMass_CosTheta_mm->Divide(TopDD_HighMass_CosTheta_em);

 // For HighMass Rapidity 2D Transfer Factor
 TH2D* TopDD_HighMass_Rapidity_em = (TH2D *)HighMass_Rapidity->SR_2D_em_bkg->at(0)->GetHistPtr2D("TopQuark")->Clone("TopDD_HighMass_Rapidity_em");
 TransferFactor_HighMass_Rapidity_ee = (TH2D *)HighMass_Rapidity->SR_2D_ee_bkg->at(0)->GetHistPtr2D("TopQuark")->Clone("TransferFactor_HighMass_Rapidity_ee");
 TransferFactor_HighMass_Rapidity_mm = (TH2D *)HighMass_Rapidity->SR_2D_mm_bkg->at(0)->GetHistPtr2D("TopQuark")->Clone("TransferFactor_HighMass_Rapidity_mm");

 TransferFactor_HighMass_Rapidity_ee->Divide(TopDD_HighMass_Rapidity_em);
 TransferFactor_HighMass_Rapidity_mm->Divide(TopDD_HighMass_Rapidity_em);

 hf->cd();
 TransferFactor_ee->Write();
 TransferFactor_mm->Write();
 TransferFactor_HighMass_CosTheta_ee->Write();
 TransferFactor_HighMass_CosTheta_mm->Write();
 TransferFactor_HighMass_Rapidity_ee->Write();
 TransferFactor_HighMass_Rapidity_mm->Write();

 for(int iprocesshist = 0; iprocesshist < hist_process.size(); iprocesshist++){
   hist_process.at(iprocesshist)->ApplyFakeUnc();
 }

}

void HistsZPrime::outputInformation()
{
 hf->cd();

 for(int iprocesshist = 0; iprocesshist < hist_process.size(); iprocesshist++){
   hist_process.at(iprocesshist)->GetFinalData();
 }

 if(doTopDD){
   if(topDD->Dimension == 1){
     topDD->Transfer1D_ee->Write();
     topDD->Transfer1D_mm->Write();
   }
   if(topDD->Dimension == 2){
     topDD->Transfer2D_ee->Write();
     topDD->Transfer2D_mm->Write();
   }
 }

 RealEfficiency_El = (TH2D *)RealLeptonPtEta_El_Tight->at(0)->Clone("RealEfficiency_El");
 RealEfficiency_El->Reset();
 for(int ibinx = 1; ibinx <= RealLeptonPtEta_El_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= RealLeptonPtEta_El_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = RealLeptonPtEta_El_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = RealLeptonPtEta_El_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = RealLeptonPtEta_El_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = RealLeptonPtEta_El_Loose->at(0)->GetBinError(ibinx, ibiny);

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     RealEfficiency_El->SetBinContent(ibinx, ibiny, Efficiency);
     RealEfficiency_El->SetBinError(ibinx, ibiny, Error);
   }
 }

 RealEfficiency_El_Lepton1 = (TH2D *)RealLepton1PtEta_El_Tight->at(0)->Clone("RealEfficiency_El_Lepton1");
 RealEfficiency_El_Lepton1->Reset();
 for(int ibinx = 1; ibinx <= RealLepton1PtEta_El_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= RealLepton1PtEta_El_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = RealLepton1PtEta_El_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = RealLepton1PtEta_El_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = RealLepton1PtEta_El_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = RealLepton1PtEta_El_Loose->at(0)->GetBinError(ibinx, ibiny);

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     RealEfficiency_El_Lepton1->SetBinContent(ibinx, ibiny, Efficiency);
     RealEfficiency_El_Lepton1->SetBinError(ibinx, ibiny, Error);
   }
 }

 RealEfficiency_El_Lepton2 = (TH2D *)RealLepton2PtEta_El_Tight->at(0)->Clone("RealEfficiency_El_Lepton2");
 RealEfficiency_El_Lepton2->Reset();
 for(int ibinx = 1; ibinx <= RealLepton2PtEta_El_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= RealLepton2PtEta_El_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = RealLepton2PtEta_El_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = RealLepton2PtEta_El_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = RealLepton2PtEta_El_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = RealLepton2PtEta_El_Loose->at(0)->GetBinError(ibinx, ibiny);
 
     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     RealEfficiency_El_Lepton2->SetBinContent(ibinx, ibiny, Efficiency);
     RealEfficiency_El_Lepton2->SetBinError(ibinx, ibiny, Error);
   }
 }

 RealEfficiency_El_1Pt2Pt = (TH2D *)RealLepton1Pt2Pt_El_Tight->at(0)->Clone("RealEfficiency_El_1Pt2Pt");
 RealEfficiency_El_1Pt2Pt->Reset();
 for(int ibinx = 1; ibinx <= RealLepton1Pt2Pt_El_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= RealLepton1Pt2Pt_El_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = RealLepton1Pt2Pt_El_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = RealLepton1Pt2Pt_El_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = RealLepton1Pt2Pt_El_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = RealLepton1Pt2Pt_El_Loose->at(0)->GetBinError(ibinx, ibiny);

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     RealEfficiency_El_1Pt2Pt->SetBinContent(ibinx, ibiny, Efficiency);
     RealEfficiency_El_1Pt2Pt->SetBinError(ibinx, ibiny, Error);
   }
 }

 RealEfficiency_Mu = (TH2D *)RealLeptonPtEta_Mu_Tight->at(0)->Clone("RealEfficiency_Mu");
 RealEfficiency_Mu->Reset();
 for(int ibinx = 1; ibinx <= RealLeptonPtEta_Mu_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= RealLeptonPtEta_Mu_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = RealLeptonPtEta_Mu_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = RealLeptonPtEta_Mu_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = RealLeptonPtEta_Mu_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = RealLeptonPtEta_Mu_Loose->at(0)->GetBinError(ibinx, ibiny);

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     RealEfficiency_Mu->SetBinContent(ibinx, ibiny, Efficiency);
     RealEfficiency_Mu->SetBinError(ibinx, ibiny, Error);
   }
 }

///////////////////////////////////////////////////////////////////////////////////////////////

 FakeEfficiency_El = (TH2D *)FakeLeptonPtEta_El_Tight->at(0)->Clone("FakeEfficiency_El");
 FakeEfficiency_El->Reset();
 for(int ibinx = 1; ibinx <= FakeLeptonPtEta_El_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeLeptonPtEta_El_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = FakeLeptonPtEta_El_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = FakeLeptonPtEta_El_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = FakeLeptonPtEta_El_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = FakeLeptonPtEta_El_Loose->at(0)->GetBinError(ibinx, ibiny);

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     FakeEfficiency_El->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_El->SetBinError(ibinx, ibiny, Error);
   }
 }

 FakeEfficiency_El_PromptSubtr_up = (TH2D *)FakeLeptonPtEta_El_PromptSubtr_up_Tight->at(0)->Clone("FakeEfficiency_El_PromptSubtr_up");
 FakeEfficiency_El_PromptSubtr_up->Reset();
 for(int ibinx = 1; ibinx <= FakeLeptonPtEta_El_PromptSubtr_up_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeLeptonPtEta_El_PromptSubtr_up_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = FakeLeptonPtEta_El_PromptSubtr_up_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = FakeLeptonPtEta_El_PromptSubtr_up_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = FakeLeptonPtEta_El_PromptSubtr_up_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = FakeLeptonPtEta_El_PromptSubtr_up_Loose->at(0)->GetBinError(ibinx, ibiny);

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     FakeEfficiency_El_PromptSubtr_up->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_El_PromptSubtr_up->SetBinError(ibinx, ibiny, Error);
   }
 }

 FakeEfficiency_El_PromptSubtr_down = (TH2D *)FakeLeptonPtEta_El_PromptSubtr_down_Tight->at(0)->Clone("FakeEfficiency_El_PromptSubtr_down");
 FakeEfficiency_El_PromptSubtr_down->Reset();
 for(int ibinx = 1; ibinx <= FakeLeptonPtEta_El_PromptSubtr_down_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeLeptonPtEta_El_PromptSubtr_down_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = FakeLeptonPtEta_El_PromptSubtr_down_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = FakeLeptonPtEta_El_PromptSubtr_down_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = FakeLeptonPtEta_El_PromptSubtr_down_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = FakeLeptonPtEta_El_PromptSubtr_down_Loose->at(0)->GetBinError(ibinx, ibiny);
 
     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);
     
     FakeEfficiency_El_PromptSubtr_down->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_El_PromptSubtr_down->SetBinError(ibinx, ibiny, Error);
   }
 }

 FakeEfficiency_El_MET_up = (TH2D *)FakeLeptonPtEta_El_MET_up_Tight->at(0)->Clone("FakeEfficiency_El_MET_up");
 FakeEfficiency_El_MET_up->Reset();
 for(int ibinx = 1; ibinx <= FakeLeptonPtEta_El_MET_up_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeLeptonPtEta_El_MET_up_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = FakeLeptonPtEta_El_MET_up_Tight->at(0)->GetBinContent(ibinx, ibiny); 
     double Loose = FakeLeptonPtEta_El_MET_up_Loose->at(0)->GetBinContent(ibinx, ibiny); 
     double TightError = FakeLeptonPtEta_El_MET_up_Tight->at(0)->GetBinError(ibinx, ibiny); 
     double LooseError = FakeLeptonPtEta_El_MET_up_Loose->at(0)->GetBinError(ibinx, ibiny); 

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     FakeEfficiency_El_MET_up->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_El_MET_up->SetBinError(ibinx, ibiny, Error); 
   }
 }

 FakeEfficiency_El_MET_down = (TH2D *)FakeLeptonPtEta_El_MET_down_Tight->at(0)->Clone("FakeEfficiency_El_MET_down");
 FakeEfficiency_El_MET_down->Reset();
 for(int ibinx = 1; ibinx <= FakeLeptonPtEta_El_MET_down_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeLeptonPtEta_El_MET_down_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = FakeLeptonPtEta_El_MET_down_Tight->at(0)->GetBinContent(ibinx, ibiny); 
     double Loose = FakeLeptonPtEta_El_MET_down_Loose->at(0)->GetBinContent(ibinx, ibiny); 
     double TightError = FakeLeptonPtEta_El_MET_down_Tight->at(0)->GetBinError(ibinx, ibiny); 
     double LooseError = FakeLeptonPtEta_El_MET_down_Loose->at(0)->GetBinError(ibinx, ibiny); 

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     FakeEfficiency_El_MET_down->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_El_MET_down->SetBinError(ibinx, ibiny, Error); 
   }
 }

 FakeEfficiency_El_Stat_up = (TH2D *)FakeEfficiency_El->Clone("FakeEfficiency_El_Stat_up");
 FakeEfficiency_El_Stat_up->Reset();
 for(int ibinx = 1; ibinx <= FakeEfficiency_El->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeEfficiency_El->GetNbinsY(); ibiny++){
     double Efficiency = FakeEfficiency_El->GetBinContent(ibinx, ibiny) + FakeEfficiency_El->GetBinError(ibinx, ibiny);
     
     FakeEfficiency_El_Stat_up->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_El_Stat_up->SetBinError(ibinx, ibiny, 0.0);
   }
 }

 FakeEfficiency_El_Stat_down = (TH2D *)FakeEfficiency_El->Clone("FakeEfficiency_El_Stat_down");
 FakeEfficiency_El_Stat_down->Reset();
 for(int ibinx = 1; ibinx <= FakeEfficiency_El->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeEfficiency_El->GetNbinsY(); ibiny++){
     double Efficiency = FakeEfficiency_El->GetBinContent(ibinx, ibiny) - FakeEfficiency_El->GetBinError(ibinx, ibiny);

     FakeEfficiency_El_Stat_down->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_El_Stat_down->SetBinError(ibinx, ibiny, 0.0);
   }
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 FakeEfficiency_Mu = (TH2D *)FakeLeptonPtEta_Mu_Tight->at(0)->Clone("FakeEfficiency_Mu");
 FakeEfficiency_Mu->Reset();
 for(int ibinx = 1; ibinx <= FakeLeptonPtEta_Mu_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeLeptonPtEta_Mu_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = FakeLeptonPtEta_Mu_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = FakeLeptonPtEta_Mu_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = FakeLeptonPtEta_Mu_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = FakeLeptonPtEta_Mu_Loose->at(0)->GetBinError(ibinx, ibiny);

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);
 
     FakeEfficiency_Mu->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_Mu->SetBinError(ibinx, ibiny, Error);
   }
 }

 FakeEfficiency_Mu_PromptSubtr_up = (TH2D *)FakeLeptonPtEta_Mu_PromptSubtr_up_Tight->at(0)->Clone("FakeEfficiency_Mu_PromptSubtr_up");
 FakeEfficiency_Mu_PromptSubtr_up->Reset();
 for(int ibinx = 1; ibinx <= FakeLeptonPtEta_Mu_PromptSubtr_up_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeLeptonPtEta_Mu_PromptSubtr_up_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = FakeLeptonPtEta_Mu_PromptSubtr_up_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = FakeLeptonPtEta_Mu_PromptSubtr_up_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = FakeLeptonPtEta_Mu_PromptSubtr_up_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = FakeLeptonPtEta_Mu_PromptSubtr_up_Loose->at(0)->GetBinError(ibinx, ibiny);

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     FakeEfficiency_Mu_PromptSubtr_up->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_Mu_PromptSubtr_up->SetBinError(ibinx, ibiny, Error);
   }
 }

 FakeEfficiency_Mu_PromptSubtr_down = (TH2D *)FakeLeptonPtEta_Mu_PromptSubtr_down_Tight->at(0)->Clone("FakeEfficiency_Mu_PromptSubtr_down");
 FakeEfficiency_Mu_PromptSubtr_down->Reset();
 for(int ibinx = 1; ibinx <= FakeLeptonPtEta_Mu_PromptSubtr_down_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeLeptonPtEta_Mu_PromptSubtr_down_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = FakeLeptonPtEta_Mu_PromptSubtr_down_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = FakeLeptonPtEta_Mu_PromptSubtr_down_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = FakeLeptonPtEta_Mu_PromptSubtr_down_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = FakeLeptonPtEta_Mu_PromptSubtr_down_Loose->at(0)->GetBinError(ibinx, ibiny);

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     FakeEfficiency_Mu_PromptSubtr_down->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_Mu_PromptSubtr_down->SetBinError(ibinx, ibiny, Error);
   }
 }

 FakeEfficiency_Mu_d0sig_up = (TH2D *)FakeLeptonPtEta_Mu_d0sig_up_Tight->at(0)->Clone("FakeEfficiency_Mu_d0sig_up");
 FakeEfficiency_Mu_d0sig_up->Reset();
 for(int ibinx = 1; ibinx <= FakeLeptonPtEta_Mu_d0sig_up_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeLeptonPtEta_Mu_d0sig_up_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = FakeLeptonPtEta_Mu_d0sig_up_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = FakeLeptonPtEta_Mu_d0sig_up_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = FakeLeptonPtEta_Mu_d0sig_up_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = FakeLeptonPtEta_Mu_d0sig_up_Loose->at(0)->GetBinError(ibinx, ibiny);

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     FakeEfficiency_Mu_d0sig_up->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_Mu_d0sig_up->SetBinError(ibinx, ibiny, Error);
   }
 }

 FakeEfficiency_Mu_d0sig_down = (TH2D *)FakeLeptonPtEta_Mu_d0sig_down_Tight->at(0)->Clone("FakeEfficiency_Mu_d0sig_down");
 FakeEfficiency_Mu_d0sig_down->Reset();
 for(int ibinx = 1; ibinx <= FakeLeptonPtEta_Mu_d0sig_down_Tight->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeLeptonPtEta_Mu_d0sig_down_Tight->at(0)->GetNbinsY(); ibiny++){
     double Tight = FakeLeptonPtEta_Mu_d0sig_down_Tight->at(0)->GetBinContent(ibinx, ibiny);
     double Loose = FakeLeptonPtEta_Mu_d0sig_down_Loose->at(0)->GetBinContent(ibinx, ibiny);
     double TightError = FakeLeptonPtEta_Mu_d0sig_down_Tight->at(0)->GetBinError(ibinx, ibiny);
     double LooseError = FakeLeptonPtEta_Mu_d0sig_down_Loose->at(0)->GetBinError(ibinx, ibiny);

     double Efficiency = Tight / Loose;
     if(fabs(Loose) < 1e-20) Efficiency = 0.0;
     double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);

     FakeEfficiency_Mu_d0sig_down->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_Mu_d0sig_down->SetBinError(ibinx, ibiny, Error);
   }
 }

 FakeEfficiency_Mu_Stat_up = (TH2D *)FakeEfficiency_Mu->Clone("FakeEfficiency_Mu_Stat_up");
 FakeEfficiency_Mu_Stat_up->Reset();
 for(int ibinx = 1; ibinx <= FakeEfficiency_Mu->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeEfficiency_Mu->GetNbinsY(); ibiny++){
     double Efficiency = FakeEfficiency_Mu->GetBinContent(ibinx, ibiny) + FakeEfficiency_Mu->GetBinError(ibinx, ibiny);

     FakeEfficiency_Mu_Stat_up->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_Mu_Stat_up->SetBinError(ibinx, ibiny, 0.0);
   }
 }

 FakeEfficiency_Mu_Stat_down = (TH2D *)FakeEfficiency_Mu->Clone("FakeEfficiency_Mu_Stat_down");
 FakeEfficiency_Mu_Stat_down->Reset();
 for(int ibinx = 1; ibinx <= FakeEfficiency_Mu->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= FakeEfficiency_Mu->GetNbinsY(); ibiny++){
     double Efficiency = FakeEfficiency_Mu->GetBinContent(ibinx, ibiny) - FakeEfficiency_Mu->GetBinError(ibinx, ibiny);

     FakeEfficiency_Mu_Stat_down->SetBinContent(ibinx, ibiny, Efficiency);
     FakeEfficiency_Mu_Stat_down->SetBinError(ibinx, ibiny, 0.0);
   }
 }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 FakeEfficiency_Mu_1D = (TH1D *)FakeLeptonPt_Mu_Tight->at(0)->Clone("FakeEfficiency_Mu_1D");
 FakeEfficiency_Mu_1D->Reset();
 for(int ibinx = 1; ibinx <= FakeLeptonPt_Mu_Tight->at(0)->GetNbinsX(); ibinx++){
   double Tight = FakeLeptonPt_Mu_Tight->at(0)->GetBinContent(ibinx);
   double Loose = FakeLeptonPt_Mu_Loose->at(0)->GetBinContent(ibinx);
   double TightError = FakeLeptonPt_Mu_Tight->at(0)->GetBinError(ibinx);
   double LooseError = FakeLeptonPt_Mu_Loose->at(0)->GetBinError(ibinx);

   double Efficiency = Tight / Loose;
   if(fabs(Loose) < 1e-20) Efficiency = 0.0;
   double Error = EfficiencyUncertainty(Tight, Loose, TightError, LooseError);
 
   FakeEfficiency_Mu_1D->SetBinContent(ibinx, Efficiency);
   FakeEfficiency_Mu_1D->SetBinError(ibinx, Error);
 }

 FakeEfficiency_El_Wjets = (TH2D *)FakeLeptonPtEta_El_Wjets_Tight->at(0)->Clone("FakeEfficiency_Wjets");
 FakeEfficiency_El_Wjets->Divide(FakeLeptonPtEta_El_Wjets_Tight->at(0), FakeLeptonPtEta_El_Wjets_Loose->at(0), 1, 1, "B");

 RealEfficiency_El_Wjets = (TH2D *)RealLeptonPtEta_El_Wjets_Tight->at(0)->Clone("RealEfficiency_Wjets");
 RealEfficiency_El_Wjets->Divide(RealLeptonPtEta_El_Wjets_Tight->at(0), RealLeptonPtEta_El_Wjets_Loose->at(0), 1, 1, "B");

 RealEfficiency_El_Wjets_Lepton2 = (TH2D *)RealLepton2PtEta_El_Wjets_Tight->at(0)->Clone("RealEfficiency_Wjets_Lepton2");
 RealEfficiency_El_Wjets_Lepton2->Divide(RealLepton2PtEta_El_Wjets_Tight->at(0), RealLepton2PtEta_El_Wjets_Loose->at(0), 1, 1, "B");

 RealEfficiency_El->Write();
 RealEfficiency_El_Lepton1->Write();
 RealEfficiency_El_Lepton2->Write();
 RealEfficiency_El_1Pt2Pt->Write();
 RealEfficiency_Mu->Write();

 FakeEfficiency_El->Write();
 FakeEfficiency_El_Stat_up->Write();
 FakeEfficiency_El_Stat_down->Write();
 FakeEfficiency_El_PromptSubtr_up->Write();
 FakeEfficiency_El_PromptSubtr_down->Write();
 FakeEfficiency_El_MET_up->Write();
 FakeEfficiency_El_MET_down->Write();

 FakeEfficiency_Mu->Write();
 FakeEfficiency_Mu_Stat_up->Write();
 FakeEfficiency_Mu_Stat_down->Write();
 FakeEfficiency_Mu_PromptSubtr_up->Write();
 FakeEfficiency_Mu_PromptSubtr_down->Write();
 FakeEfficiency_Mu_d0sig_up->Write();
 FakeEfficiency_Mu_d0sig_down->Write();

 FakeEfficiency_Mu_1D->Write();
 FakeEfficiency_El_Wjets->Write();
 RealEfficiency_El_Wjets->Write();
 RealEfficiency_El_Wjets_Lepton2->Write();
}
