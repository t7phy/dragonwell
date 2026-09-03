#define HistsPythia_cxx
#include "Analysis/HistsPythia.h"

using namespace std;

HistsPythia::HistsPythia()
{
 m_HistsPythia = this;
}

void HistsPythia::bookHists(int TotalThread)
{
 ZY_bin = 5; ZY_left = 0.0; ZY_right = 5.0;
 ZY_CC_bin = 3; ZY_CC_left = 0.0; ZY_CC_right = 2.5;
 ZY_CF_bin = 3; ZY_CF_left = 1.0; ZY_CF_right = 4.0;

 ZPt_bin = 11; ZPt_left = 0.0; ZPt_right = 100.0;
 ZPt_CC_bin = 11; ZPt_CC_left = 0.0; ZPt_CC_right = 100.0;
 ZPt_CF_bin = 11; ZPt_CF_left = 0.0; ZPt_CF_right = 100.0;

 double rangeZY[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
 double rangeZYCC[4] = {0.0, 0.5, 1.0, 2.5};
 double rangeZYCF[4] = {1.0, 1.5, 2.0, 4.0};

 double RangeZPt[12] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 100.0};
 double RangeZPtCC[12] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 100.0};
 double RangeZPtCF[12] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 100.0};

 double rangeZPt[24] = {0,2.5,5,8,11.4,14.9,18.5,22,25.5,29,32.6,36.4,40.4,44.9,50.2,56.4,63.9,73.4,85.4,105,132,173,253,600};
 double rangeZPt2[44] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.5, 25.0, 27.5, 30.0, 33.0, 36.0, 39.0, 42.0, 45.0, 48.0, 51.0, 54.0, 57.0,
                      61.0, 65.0, 70.0, 75.0, 80.0, 85.0, 95.0, 105.0, 125.0, 150.0, 175.0, 200.0, 250.0, 300.0, 350.0, 400.0, 470.0, 550.0, 650.0, 900.0};
 double rangePhiEta[37] = {0.0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.051, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128,
                      0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 5.0, 10.0};

 double rangeEtaAbs[5] = {0, 1, 2, 3, 5};
 double rangeMET[6] = {25, 35, 45, 55, 65, 100};
 double rangePt[6] = {0, 2, 4, 6, 8, 10};
 double rangeE[6] = {0, 200, 400, 600, 800, 1000};

 double rangeMass[31] = {60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120};

 //Full ZY
 vector<vector<double>> YMultiBin;
 vector<double> tmpYBin;

 tmpYBin = {0.0, 1.0};
 YMultiBin.push_back(tmpYBin);
 tmpYBin = {1.0, 2.0};
 YMultiBin.push_back(tmpYBin);
 tmpYBin = {2.0, 5.0};
 YMultiBin.push_back(tmpYBin);
 tmpYBin = {0.0, 2.0};
 YMultiBin.push_back(tmpYBin);
 tmpYBin = {1.0, 5.0};
 YMultiBin.push_back(tmpYBin);
 tmpYBin = {0.0, 5.0};
 YMultiBin.push_back(tmpYBin);

 //CC ZY
 vector<vector<double>> YMultiBinCC;
 tmpYBin = {0.0, 0.5};
 YMultiBinCC.push_back(tmpYBin);
 tmpYBin = {0.5, 1.0};
 YMultiBinCC.push_back(tmpYBin);
 tmpYBin = {1.0, 2.5};
 YMultiBinCC.push_back(tmpYBin);
 tmpYBin = {0.0, 1.0};
 YMultiBinCC.push_back(tmpYBin);
 tmpYBin = {0.5, 2.5};
 YMultiBinCC.push_back(tmpYBin);
 tmpYBin = {0.0, 2.5};
 YMultiBinCC.push_back(tmpYBin);

 //CF ZY
 vector<vector<double>> YMultiBinCF;
 tmpYBin = {1.0, 1.5};
 YMultiBinCF.push_back(tmpYBin);
 tmpYBin = {1.5, 2.0};
 YMultiBinCF.push_back(tmpYBin);
 tmpYBin = {2.0, 4.0};
 YMultiBinCF.push_back(tmpYBin);
 tmpYBin = {1.0, 2.0};
 YMultiBinCF.push_back(tmpYBin);
 tmpYBin = {1.5, 4.0};
 YMultiBinCF.push_back(tmpYBin);
 tmpYBin = {1.0, 4.0};
 YMultiBinCF.push_back(tmpYBin);

 this->TotalThread = TotalThread;

 BookHist(ZMass, "ZMass", "ZMass", 70, 60, 130);
 BookHist(ZMass_CC, "ZMass_CC", "ZMass_CC", 70, 60, 130);
 BookHist(ZMass_CF, "ZMass_CF", "ZMass_CF", 70, 60, 130);
 BookHist(FZmass, "FZmass", "FZmass", 70, 60, 130);
 BookHist(BZmass, "BZmass", "BZmass", 70, 60, 130);
 BookHist(FZmass_Hadron_uu, "FZmass_Hadron_uu", "FZmass_Hadron_uu", 70, 60, 130);
 BookHist(BZmass_Hadron_uu, "BZmass_Hadron_uu", "BZmass_Hadron_uu", 70, 60, 130);
 BookHist(FZmass_Hadron_dd, "FZmass_Hadron_dd", "FZmass_Hadron_dd", 70, 60, 130);
 BookHist(BZmass_Hadron_dd, "BZmass_Hadron_dd", "BZmass_Hadron_dd", 70, 60, 130);
 BookHist(FZmass_Hadron_utype, "FZmass_Hadron_utype", "FZmass_Hadron_utype", 70, 60, 130);
 BookHist(BZmass_Hadron_utype, "BZmass_Hadron_utype", "BZmass_Hadron_utype", 70, 60, 130);
 BookHist(FZmass_Hadron_dtype, "FZmass_Hadron_dtype", "FZmass_Hadron_dtype", 70, 60, 130);
 BookHist(BZmass_Hadron_dtype, "BZmass_Hadron_dtype", "BZmass_Hadron_dtype", 70, 60, 130);
 BookHist(FZmass_LepPtCut, "FZmass_LepPtCut", "FZmass_LepPtCut", 70, 60, 130);
 BookHist(BZmass_LepPtCut, "BZmass_LepPtCut", "BZmass_LepPtCut", 70, 60, 130);
 BookHist(FZmass_NoLepPtCut, "FZmass_NoLepPtCut", "FZmass_NoLepPtCut", 70, 60, 130);
 BookHist(BZmass_NoLepPtCut, "BZmass_NoLepPtCut", "BZmass_NoLepPtCut", 70, 60, 130);
 BookHist(FZmass_CC, "FZmass_CC", "FZmass_CC", 70, 60, 130);
 BookHist(BZmass_CC, "BZmass_CC", "BZmass_CC", 70, 60, 130);
 BookHist(FZmass_CF, "FZmass_CF", "FZmass_CF", 70, 60, 130);
 BookHist(BZmass_CF, "BZmass_CF", "BZmass_CF", 70, 60, 130);

// BookHist(ZPt, "ZPt", "ZPt", 43, rangeZPt2);
 BookHist(ZPt, "ZPt", "ZPt", 100, 0, 100);
 BookHist(ZRapidity, "ZRapidity", "ZRapidity", 100, -5, 5);
 BookHist(ZPt_LepPtCut, "ZPt_LepPtCut", "ZPt_LepPtCut", 100, 0, 100);
 BookHist(ZRapidity_LepPtCut, "ZRapidity_LepPtCut", "ZRapidity_LepPtCut", 100, -5, 5);
 BookHist(ZPt_NoLepPtCut, "ZPt_NoLepPtCut", "ZPt_NoLepPtCut", 100, 0, 100);
 BookHist(ZRapidity_NoLepPtCut, "ZRapidity_NoLepPtCut", "ZRapidity_NoLepPtCut", 100, -5, 5);
 BookHist(ZRapidityAbs, "ZRapidityAbs", "ZRapidityAbs", 20, 0, 5);
 BookHist(ZPzPtBalance, "ZPzPtBalance", "ZPzPtBalance", 1000, 0, 1000);
 BookHist(ZPzPtBalance_CC, "ZPzPtBalance_CC", "ZPzPtBalance_CC", 1000, 0, 1000);
 BookHist(ZPzPtBalance_CF, "ZPzPtBalance_CF", "ZPzPtBalance_CF", 1000, 0, 1000);
 BookHist(QuarkPzZPzBalance, "QuarkPzZPzBalance", "QuarkPzZPzBalance", 50, -10, 10);
 BookHist(QuarkPzZPzBalance_CC, "QuarkPzZPzBalance_CC", "QuarkPzZPzBalance_CC", 50, -10, 10);
 BookHist(QuarkPzZPzBalance_CF, "QuarkPzZPzBalance_CF", "QuarkPzZPzBalance_CF", 50, -10, 10);
 BookHist(Quark1Pz, "Quark1Pz", "Quark1Pz", 50, -2000, 2000);
 BookHist(Quark2Pz, "Quark2Pz", "Quark2Pz", 50, -2000, 2000);

 Book2DHist(ZMass_ZY, "ZMass_ZY", "ZMass_ZY", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(ZMass_ZY_CC, "ZMass_ZY_CC", "ZMass_ZY_CC", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(ZMass_ZY_CF, "ZMass_ZY_CF", "ZMass_ZY_CF", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(FZMass_ZY, "FZMass_ZY", "FZMass_ZY", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(BZMass_ZY, "BZMass_ZY", "BZMass_ZY", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(FZMass_ZY_CC, "FZMass_ZY_CC", "FZMass_ZY_CC", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(BZMass_ZY_CC, "BZMass_ZY_CC", "BZMass_ZY_CC", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(FZMass_ZY_CF, "FZMass_ZY_CF", "FZMass_ZY_CF", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(BZMass_ZY_CF, "BZMass_ZY_CF", "BZMass_ZY_CF", 30, rangeMass, ZY_CF_bin, rangeZYCF);

 Book2DHist(ZMass_ZPt, "ZMass_ZPt", "ZMass_ZPt", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(ZMass_ZPt_CC, "ZMass_ZPt_CC", "ZMass_ZPt_CC", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(ZMass_ZPt_CF, "ZMass_ZPt_CF", "ZMass_ZPt_CF", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(FZMass_ZPt, "FZMass_ZPt", "FZMass_ZPt", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(BZMass_ZPt, "BZMass_ZPt", "BZMass_ZPt", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(FZMass_ZPt_CC, "FZMass_ZPt_CC", "FZMass_ZPt_CC", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(BZMass_ZPt_CC, "BZMass_ZPt_CC", "BZMass_ZPt_CC", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(FZMass_ZPt_CF, "FZMass_ZPt_CF", "FZMass_ZPt_CF", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(BZMass_ZPt_CF, "BZMass_ZPt_CF", "BZMass_ZPt_CF", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);

 BookMultiBinHist(ZMass_ZY_multi, YMultiBin, "ZMass_ZY", "ZMass_ZY", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CC_multi, YMultiBinCC, "ZMass_ZY_CC", "ZMass_ZY_CC", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CF_multi, YMultiBinCF, "ZMass_ZY_CF", "ZMass_ZY_CF", 30, rangeMass);
 BookMultiBinHist(FZMass_ZY_multi, YMultiBin, "FZMass_ZY", "FZMass_ZY", 30, rangeMass);
 BookMultiBinHist(BZMass_ZY_multi, YMultiBin, "BZMass_ZY", "BZMass_ZY", 30, rangeMass);
 BookMultiBinHist(FZMass_ZY_CC_multi, YMultiBinCC, "FZMass_ZY_CC", "FZMass_ZY_CC", 30, rangeMass);
 BookMultiBinHist(BZMass_ZY_CC_multi, YMultiBinCC, "BZMass_ZY_CC", "BZMass_ZY_CC", 30, rangeMass);
 BookMultiBinHist(FZMass_ZY_CF_multi, YMultiBinCF, "FZMass_ZY_CF", "FZMass_ZY_CF", 30, rangeMass);
 BookMultiBinHist(BZMass_ZY_CF_multi, YMultiBinCF, "BZMass_ZY_CF", "BZMass_ZY_CF", 30, rangeMass);

 Book3DHist(ZMass_ZY_QT, "ZMass_ZY_QT", "ZMass_ZY_QT", 35, 60, 130, ZY_bin, ZY_left, ZY_right, 5, 0, 100);
 Book3DHist(FZMass_ZY_QT, "FZMass_ZY_QT", "FZMass_ZY_QT", 35, 60, 130, ZY_bin, ZY_left, ZY_right, 5, 0, 100);
 Book3DHist(BZMass_ZY_QT, "BZMass_ZY_QT", "BZMass_ZY_QT", 35, 60, 130, ZY_bin, ZY_left, ZY_right, 5, 0, 100);

 BookHist(CosTheta, "CosTheta", "CosTheta", 20, -1, 1);
 BookHist(CosTheta_LepPtCut, "CosTheta_LepPtCut", "CosTheta_LepPtCut", 20, -1, 1);
 BookHist(CosThetaQ, "CosThetaQ", "CosThetaQ", 20, -1, 1);
 BookHist(CollinsPhi, "phi", "phi", 200, -6.28, 6.28);
 BookHist(plot_phi_eta, "phi_eta", "phi_eta", 10000, 0, 10);
 BookHist(leptonPt, "leptonPt", "leptonPt", 50, 10, 60);
 BookHist(leptonEta, "leptonEta", "leptonEta", 20, -5, 5);

 BookHist(LepEtaAbs, "LepEtaAbs", "LepEtaAbs", 20, 0, 5);
 BookHist(AntiLepEtaAbs, "AntiLepEtaAbs", "AntiLepEtaAbs", 20, 0, 5);
 BookHist(LepEtaAbs_CC, "LepEtaAbs_CC", "LepEtaAbs_CC", 20, 0, 2.5);
 BookHist(AntiLepEtaAbs_CC, "AntiLepEtaAbs_CC", "AntiLepEtaAbs_CC", 20, 0, 2.5);
 BookHist(LepEtaAbs_CF, "LepEtaAbs_CF", "LepEtaAbs_CF", 20, 0, 5);
 BookHist(AntiLepEtaAbs_CF, "AntiLepEtaAbs_CF", "AntiLepEtaAbs_CF", 20, 0, 5);

 BookHist(LepEta, "LepEta", "LepEta", 20, -5, 5);
 BookHist(AntiLepEta, "AntiLepEta", "AntiLepEta", 20, -5, 5);
 BookHist(LepEta_CC, "LepEta_CC", "LepEta_CC", 20, -2.5, 2.5);
 BookHist(AntiLepEta_CC, "AntiLepEta_CC", "AntiLepEta_CC", 20, -2.5, 2.5);
 BookHist(LepEta_CF, "LepEta_CF", "LepEta_CF", 20, -5, 5);
 BookHist(AntiLepEta_CF, "AntiLepEta_CF", "AntiLepEta_CF", 20, -5, 5);

 BookHist(FZRapidity, "FZRapidity", "FZRapidity", 50, 0, 5);
 BookHist(BZRapidity, "BZRapidity", "BZRapidity", 50, 0, 5);
 BookHist(FZRapidity_LepPtCut, "FZRapidity_LepPtCut", "FZRapidity_LepPtCut", 50, 0, 5);
 BookHist(BZRapidity_LepPtCut, "BZRapidity_LepPtCut", "BZRapidity_LepPtCut", 50, 0, 5);
 BookHist(FZRapidity_NoLepPtCut, "FZRapidity_NoLepPtCut", "FZRapidity_NoLepPtCut", 50, 0, 5);
 BookHist(BZRapidity_NoLepPtCut, "BZRapidity_NoLepPtCut", "BZRapidity_NoLepPtCut", 50, 0, 5);
 BookHist(FZRapidity_CC, "FZRapidity_CC", "FZRapidity_CC", 20, 0, 2.5);
 BookHist(BZRapidity_CC, "BZRapidity_CC", "BZRapidity_CC", 20, 0, 2.5);
 BookHist(FZRapidity_CF, "FZRapidity_CF", "FZRapidity_CF", 20, 1, 4);
 BookHist(BZRapidity_CF, "BZRapidity_CF", "BZRapidity_CF", 20, 1, 4);

 BookHist(FZPt, "FZPt", "FZPt", 100, 0, 100);
 BookHist(BZPt, "BZPt", "BZPt", 100, 0, 100);
 BookHist(FZPt_LepPtCut, "FZPt_LepPtCut", "FZPt_LepPtCut", 100, 0, 100);
 BookHist(BZPt_LepPtCut, "BZPt_LepPtCut", "BZPt_LepPtCut", 100, 0, 100);
 BookHist(FZPt_NoLepPtCut, "FZPt_NoLepPtCut", "FZPt_NoLepPtCut", 100, 0, 100);
 BookHist(BZPt_NoLepPtCut, "BZPt_NoLepPtCut", "BZPt_NoLepPtCut", 100, 0, 100);

 BookHist(AverageZPt_ZY_numer, "AverageZPt_ZY_numer", "AverageZPt_ZY_numer", 20, 0, 5);
 BookHist(AverageZPt_ZY_denom, "AverageZPt_ZY_denom", "AverageZPt_ZY_denom", 20, 0, 5);
 BookHist(AverageZPt_lnQ_numer, "AverageZPt_lnQ_numer", "AverageZPt_lnQ_numer", 20, 4, 5);
 BookHist(AverageZPt_lnQ_denom, "AverageZPt_lnQ_denom", "AverageZPt_lnQ_denom", 20, 4, 5);
 BookHist(AverageZY_ZY_numer, "AverageZY_ZY_numer", "AverageZY_ZY_numer", 20, 0, 5);
 BookHist(AverageZY_ZY_denom, "AverageZY_ZY_denom", "AverageZY_ZY_denom", 20, 0, 5);

 BookHist(FZmass_CC_uu, "FZmass_CC_uu", "FZmass_CC_uu", 70, 60, 130);
 BookHist(BZmass_CC_uu, "BZmass_CC_uu", "BZmass_CC_uu", 70, 60, 130);
 BookHist(FZmass_CF_uu, "FZmass_CF_uu", "FZmass_CF_uu", 70, 60, 130);
 BookHist(BZmass_CF_uu, "BZmass_CF_uu", "BZmass_CF_uu", 70, 60, 130);
 BookHist(FZmass_CC_dd, "FZmass_CC_dd", "FZmass_CC_dd", 70, 60, 130);
 BookHist(BZmass_CC_dd, "BZmass_CC_dd", "BZmass_CC_dd", 70, 60, 130);
 BookHist(FZmass_CF_dd, "FZmass_CF_dd", "FZmass_CF_dd", 70, 60, 130);
 BookHist(BZmass_CF_dd, "BZmass_CF_dd", "BZmass_CF_dd", 70, 60, 130);
 BookHist(FZmass_CC_gg, "FZmass_CC_gg", "FZmass_CC_gg", 70, 60, 130);
 BookHist(BZmass_CC_gg, "BZmass_CC_gg", "BZmass_CC_gg", 70, 60, 130);
 BookHist(FZmass_CF_gg, "FZmass_CF_gg", "FZmass_CF_gg", 70, 60, 130);
 BookHist(BZmass_CF_gg, "BZmass_CF_gg", "BZmass_CF_gg", 70, 60, 130);
 BookHist(FZmass_uu, "FZmass_uu", "FZmass_uu", 70, 60, 130);
 BookHist(BZmass_uu, "BZmass_uu", "BZmass_uu", 70, 60, 130);
 BookHist(FZmass_dd, "FZmass_dd", "FZmass_dd", 70, 60, 130);
 BookHist(BZmass_dd, "BZmass_dd", "BZmass_dd", 70, 60, 130);
 BookHist(FZmass_gg, "FZmass_gg", "FZmass_gg", 70, 60, 130);
 BookHist(BZmass_gg, "BZmass_gg", "BZmass_gg", 70, 60, 130);
 BookHist(ZMass_CC_uu, "ZMass_CC_uu", "ZMass_CC_uu", 30, 60, 120);
 BookHist(ZMass_CF_uu, "ZMass_CF_uu", "ZMass_CF_uu", 30, 60, 120);
 BookHist(ZMass_CC_dd, "ZMass_CC_dd", "ZMass_CC_dd", 30, 60, 120);
 BookHist(ZMass_CF_dd, "ZMass_CF_dd", "ZMass_CF_dd", 30, 60, 120);
 BookHist(ZMass_CC_gg, "ZMass_CC_gg", "ZMass_CC_gg", 30, 60, 120);
 BookHist(ZMass_CF_gg, "ZMass_CF_gg", "ZMass_CF_gg", 30, 60, 120);
 BookHist(ZMass_CC_ss, "ZMass_CC_ss", "ZMass_CC_ss", 30, 60, 120);
 BookHist(ZMass_CF_ss, "ZMass_CF_ss", "ZMass_CF_ss", 30, 60, 120);
 BookHist(ZMass_CC_cc, "ZMass_CC_cc", "ZMass_CC_cc", 30, 60, 120);
 BookHist(ZMass_CF_cc, "ZMass_CF_cc", "ZMass_CF_cc", 30, 60, 120);
 BookHist(ZMass_CC_bb, "ZMass_CC_bb", "ZMass_CC_bb", 30, 60, 120);
 BookHist(ZMass_CF_bb, "ZMass_CF_bb", "ZMass_CF_bb", 30, 60, 120);
 BookHist(ZMass_CC_utype, "ZMass_CC_utype", "ZMass_CC_utype", 30, 60, 120);
 BookHist(ZMass_CF_utype, "ZMass_CF_utype", "ZMass_CF_utype", 30, 60, 120);
 BookHist(ZMass_CC_dtype, "ZMass_CC_dtype", "ZMass_CC_dtype", 30, 60, 120);
 BookHist(ZMass_CF_dtype, "ZMass_CF_dtype", "ZMass_CF_dtype", 30, 60, 120);
 BookHist(ZMass_uu, "ZMass_uu", "ZMass_uu", 30, 60, 120);
 BookHist(ZMass_dd, "ZMass_dd", "ZMass_dd", 30, 60, 120);
 BookHist(ZMass_gg, "ZMass_gg", "ZMass_gg", 30, 60, 120);
 BookHist(ZMass_ss, "ZMass_ss", "ZMass_ss", 30, 60, 120);
 BookHist(ZMass_cc, "ZMass_cc", "ZMass_cc", 30, 60, 120);
 BookHist(ZMass_bb, "ZMass_bb", "ZMass_bb", 30, 60, 120);
 BookHist(ZMass_utype, "ZMass_utype", "ZMass_utype", 30, 60, 120);
 BookHist(ZMass_dtype, "ZMass_dtype", "ZMass_dtype", 30, 60, 120);

 BookHist(FZPt_uu, "FZPt_uu", "FZPt_uu", 23, rangeZPt);
 BookHist(BZPt_uu, "BZPt_uu", "BZPt_uu", 23, rangeZPt);
 BookHist(FZPt_dd, "FZPt_dd", "FZPt_dd", 23, rangeZPt);
 BookHist(BZPt_dd, "BZPt_dd", "BZPt_dd", 23, rangeZPt);

 Book2DHist(ZMass_ZY_uu, "ZMass_ZY_uu", "ZMass_ZY_uu", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(ZMass_ZY_dd, "ZMass_ZY_dd", "ZMass_ZY_dd", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(ZMass_ZY_ss, "ZMass_ZY_ss", "ZMass_ZY_ss", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(ZMass_ZY_cc, "ZMass_ZY_cc", "ZMass_ZY_cc", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(ZMass_ZY_bb, "ZMass_ZY_bb", "ZMass_ZY_bb", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(ZMass_ZY_CC_uu, "ZMass_ZY_CC_uu", "ZMass_ZY_CC_uu", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(ZMass_ZY_CC_dd, "ZMass_ZY_CC_dd", "ZMass_ZY_CC_dd", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(ZMass_ZY_CC_ss, "ZMass_ZY_CC_ss", "ZMass_ZY_CC_ss", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(ZMass_ZY_CC_cc, "ZMass_ZY_CC_cc", "ZMass_ZY_CC_cc", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(ZMass_ZY_CC_bb, "ZMass_ZY_CC_bb", "ZMass_ZY_CC_bb", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(ZMass_ZY_CF_uu, "ZMass_ZY_CF_uu", "ZMass_ZY_CF_uu", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(ZMass_ZY_CF_dd, "ZMass_ZY_CF_dd", "ZMass_ZY_CF_dd", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(ZMass_ZY_CF_ss, "ZMass_ZY_CF_ss", "ZMass_ZY_CF_ss", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(ZMass_ZY_CF_cc, "ZMass_ZY_CF_cc", "ZMass_ZY_CF_cc", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(ZMass_ZY_CF_bb, "ZMass_ZY_CF_bb", "ZMass_ZY_CF_bb", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(FZmass_ZY_uu, "FZmass_ZY_uu", "FZmass_ZY_uu", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(BZmass_ZY_uu, "BZmass_ZY_uu", "BZmass_ZY_uu", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(FZmass_ZY_dd, "FZmass_ZY_dd", "FZmass_ZY_dd", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(BZmass_ZY_dd, "BZmass_ZY_dd", "BZmass_ZY_dd", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(FZmass_ZY_gg, "FZmass_ZY_gg", "FZmass_ZY_gg", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(BZmass_ZY_gg, "BZmass_ZY_gg", "BZmass_ZY_gg", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(FZmass_ZY_CC_uu, "FZmass_ZY_CC_uu", "FZmass_ZY_CC_uu", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(BZmass_ZY_CC_uu, "BZmass_ZY_CC_uu", "BZmass_ZY_CC_uu", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(FZmass_ZY_CC_dd, "FZmass_ZY_CC_dd", "FZmass_ZY_CC_dd", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(BZmass_ZY_CC_dd, "BZmass_ZY_CC_dd", "BZmass_ZY_CC_dd", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(FZmass_ZY_CC_gg, "FZmass_ZY_CC_gg", "FZmass_ZY_CC_gg", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(BZmass_ZY_CC_gg, "BZmass_ZY_CC_gg", "BZmass_ZY_CC_gg", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(FZmass_ZY_CF_uu, "FZmass_ZY_CF_uu", "FZmass_ZY_CF_uu", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(BZmass_ZY_CF_uu, "BZmass_ZY_CF_uu", "BZmass_ZY_CF_uu", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(FZmass_ZY_CF_dd, "FZmass_ZY_CF_dd", "FZmass_ZY_CF_dd", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(BZmass_ZY_CF_dd, "BZmass_ZY_CF_dd", "BZmass_ZY_CF_dd", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(FZmass_ZY_CF_gg, "FZmass_ZY_CF_gg", "FZmass_ZY_CF_gg", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(BZmass_ZY_CF_gg, "BZmass_ZY_CF_gg", "BZmass_ZY_CF_gg", 30, rangeMass, ZY_CF_bin, rangeZYCF);

 Book2DHist(ZMass_ZPt_uu, "ZMass_ZPt_uu", "ZMass_ZPt_uu", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(ZMass_ZPt_dd, "ZMass_ZPt_dd", "ZMass_ZPt_dd", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(ZMass_ZPt_ss, "ZMass_ZPt_ss", "ZMass_ZPt_ss", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(ZMass_ZPt_cc, "ZMass_ZPt_cc", "ZMass_ZPt_cc", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(ZMass_ZPt_bb, "ZMass_ZPt_bb", "ZMass_ZPt_bb", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(ZMass_ZPt_CC_uu, "ZMass_ZPt_CC_uu", "ZMass_ZPt_CC_uu", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(ZMass_ZPt_CC_dd, "ZMass_ZPt_CC_dd", "ZMass_ZPt_CC_dd", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(ZMass_ZPt_CC_ss, "ZMass_ZPt_CC_ss", "ZMass_ZPt_CC_ss", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(ZMass_ZPt_CC_cc, "ZMass_ZPt_CC_cc", "ZMass_ZPt_CC_cc", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(ZMass_ZPt_CC_bb, "ZMass_ZPt_CC_bb", "ZMass_ZPt_CC_bb", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(ZMass_ZPt_CF_uu, "ZMass_ZPt_CF_uu", "ZMass_ZPt_CF_uu", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(ZMass_ZPt_CF_dd, "ZMass_ZPt_CF_dd", "ZMass_ZPt_CF_dd", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(ZMass_ZPt_CF_ss, "ZMass_ZPt_CF_ss", "ZMass_ZPt_CF_ss", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(ZMass_ZPt_CF_cc, "ZMass_ZPt_CF_cc", "ZMass_ZPt_CF_cc", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(ZMass_ZPt_CF_bb, "ZMass_ZPt_CF_bb", "ZMass_ZPt_CF_bb", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
// Book2DHist(FZmass_ZPt_uu, "FZmass_ZPt_uu", "FZmass_ZPt_uu", 30, rangeMass, ZPt_bin, RangeZPt);
// Book2DHist(BZmass_ZPt_uu, "BZmass_ZPt_uu", "BZmass_ZPt_uu", 30, rangeMass, ZPt_bin, RangeZPt);
// Book2DHist(FZmass_ZPt_dd, "FZmass_ZPt_dd", "FZmass_ZPt_dd", 30, rangeMass, ZPt_bin, RangeZPt);
// Book2DHist(BZmass_ZPt_dd, "BZmass_ZPt_dd", "BZmass_ZPt_dd", 30, rangeMass, ZPt_bin, RangeZPt);

 Book2DHist(FZmass_ZPt_uu, "FZmass_ZPt_uu", "FZmass_ZPt_uu", 3, 60, 120, 100, 0, 500);
 Book2DHist(BZmass_ZPt_uu, "BZmass_ZPt_uu", "BZmass_ZPt_uu", 3, 60, 120, 100, 0, 500);
 Book2DHist(FZmass_ZPt_dd, "FZmass_ZPt_dd", "FZmass_ZPt_dd", 3, 60, 120, 100, 0, 500);
 Book2DHist(BZmass_ZPt_dd, "BZmass_ZPt_dd", "BZmass_ZPt_dd", 3, 60, 120, 100, 0, 500);

 Book2DHist(FZmass_ZPt_gg, "FZmass_ZPt_gg", "FZmass_ZPt_gg", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(BZmass_ZPt_gg, "BZmass_ZPt_gg", "BZmass_ZPt_gg", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(FZmass_ZPt_CC_uu, "FZmass_ZPt_CC_uu", "FZmass_ZPt_CC_uu", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(BZmass_ZPt_CC_uu, "BZmass_ZPt_CC_uu", "BZmass_ZPt_CC_uu", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(FZmass_ZPt_CC_dd, "FZmass_ZPt_CC_dd", "FZmass_ZPt_CC_dd", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(BZmass_ZPt_CC_dd, "BZmass_ZPt_CC_dd", "BZmass_ZPt_CC_dd", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(FZmass_ZPt_CC_gg, "FZmass_ZPt_CC_gg", "FZmass_ZPt_CC_gg", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(BZmass_ZPt_CC_gg, "BZmass_ZPt_CC_gg", "BZmass_ZPt_CC_gg", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(FZmass_ZPt_CF_uu, "FZmass_ZPt_CF_uu", "FZmass_ZPt_CF_uu", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(BZmass_ZPt_CF_uu, "BZmass_ZPt_CF_uu", "BZmass_ZPt_CF_uu", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(FZmass_ZPt_CF_dd, "FZmass_ZPt_CF_dd", "FZmass_ZPt_CF_dd", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(BZmass_ZPt_CF_dd, "BZmass_ZPt_CF_dd", "BZmass_ZPt_CF_dd", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(FZmass_ZPt_CF_gg, "FZmass_ZPt_CF_gg", "FZmass_ZPt_CF_gg", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(BZmass_ZPt_CF_gg, "BZmass_ZPt_CF_gg", "BZmass_ZPt_CF_gg", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);

 BookMultiBinHist(FZmass_ZY_uu_multi, YMultiBin, "FZmass_ZY_uu", "FZmass_ZY_uu", 30, rangeMass);
 BookMultiBinHist(BZmass_ZY_uu_multi, YMultiBin, "BZmass_ZY_uu", "BZmass_ZY_uu", 30, rangeMass);
 BookMultiBinHist(FZmass_ZY_dd_multi, YMultiBin, "FZmass_ZY_dd", "FZmass_ZY_dd", 30, rangeMass);
 BookMultiBinHist(BZmass_ZY_dd_multi, YMultiBin, "BZmass_ZY_dd", "BZmass_ZY_dd", 30, rangeMass);
 BookMultiBinHist(FZmass_ZY_gg_multi, YMultiBin, "FZmass_ZY_gg", "FZmass_ZY_gg", 30, rangeMass);
 BookMultiBinHist(BZmass_ZY_gg_multi, YMultiBin, "BZmass_ZY_gg", "BZmass_ZY_gg", 30, rangeMass);
 BookMultiBinHist(FZmass_ZY_CC_uu_multi, YMultiBinCC, "FZmass_ZY_CC_uu", "FZmass_ZY_CC_uu", 30, rangeMass);
 BookMultiBinHist(BZmass_ZY_CC_uu_multi, YMultiBinCC, "BZmass_ZY_CC_uu", "BZmass_ZY_CC_uu", 30, rangeMass);
 BookMultiBinHist(FZmass_ZY_CC_dd_multi, YMultiBinCC, "FZmass_ZY_CC_dd", "FZmass_ZY_CC_dd", 30, rangeMass);
 BookMultiBinHist(BZmass_ZY_CC_dd_multi, YMultiBinCC, "BZmass_ZY_CC_dd", "BZmass_ZY_CC_dd", 30, rangeMass);
 BookMultiBinHist(FZmass_ZY_CC_gg_multi, YMultiBinCC, "FZmass_ZY_CC_gg", "FZmass_ZY_CC_gg", 30, rangeMass);
 BookMultiBinHist(BZmass_ZY_CC_gg_multi, YMultiBinCC, "BZmass_ZY_CC_gg", "BZmass_ZY_CC_gg", 30, rangeMass);
 BookMultiBinHist(FZmass_ZY_CF_uu_multi, YMultiBinCF, "FZmass_ZY_CF_uu", "FZmass_ZY_CF_uu", 30, rangeMass);
 BookMultiBinHist(BZmass_ZY_CF_uu_multi, YMultiBinCF, "BZmass_ZY_CF_uu", "BZmass_ZY_CF_uu", 30, rangeMass);
 BookMultiBinHist(FZmass_ZY_CF_dd_multi, YMultiBinCF, "FZmass_ZY_CF_dd", "FZmass_ZY_CF_dd", 30, rangeMass);
 BookMultiBinHist(BZmass_ZY_CF_dd_multi, YMultiBinCF, "BZmass_ZY_CF_dd", "BZmass_ZY_CF_dd", 30, rangeMass);
 BookMultiBinHist(FZmass_ZY_CF_gg_multi, YMultiBinCF, "FZmass_ZY_CF_gg", "FZmass_ZY_CF_gg", 30, rangeMass);
 BookMultiBinHist(BZmass_ZY_CF_gg_multi, YMultiBinCF, "BZmass_ZY_CF_gg", "BZmass_ZY_CF_gg", 30, rangeMass);

 BookHist(FZRapidity_uu, "FZRapidity_uu", "FZRapidity_uu", 20, 0, 5);
 BookHist(BZRapidity_uu, "BZRapidity_uu", "BZRapidity_uu", 20, 0, 5);
 BookHist(FZRapidity_CC_uu, "FZRapidity_CC_uu", "FZRapidity_CC_uu", 20, 0, 2.5);
 BookHist(BZRapidity_CC_uu, "BZRapidity_CC_uu", "BZRapidity_CC_uu", 20, 0, 2.5);
 BookHist(FZRapidity_CF_uu, "FZRapidity_CF_uu", "FZRapidity_CF_uu", 20, 1, 4);
 BookHist(BZRapidity_CF_uu, "BZRapidity_CF_uu", "BZRapidity_CF_uu", 20, 1, 4);
 BookHist(FZRapidity_dd, "FZRapidity_dd", "FZRapidity_dd", 20, 0, 5);
 BookHist(BZRapidity_dd, "BZRapidity_dd", "BZRapidity_dd", 20, 0, 5);
 BookHist(FZRapidity_CC_dd, "FZRapidity_CC_dd", "FZRapidity_CC_dd", 20, 0, 2.5);
 BookHist(BZRapidity_CC_dd, "BZRapidity_CC_dd", "BZRapidity_CC_dd", 20, 0, 2.5);
 BookHist(FZRapidity_CF_dd, "FZRapidity_CF_dd", "FZRapidity_CF_dd", 20, 1, 4);
 BookHist(BZRapidity_CF_dd, "BZRapidity_CF_dd", "BZRapidity_CF_dd", 20, 1, 4);
 BookHist(FZRapidity_gg, "FZRapidity_gg", "FZRapidity_gg", 20, 0, 5);
 BookHist(BZRapidity_gg, "BZRapidity_gg", "BZRapidity_gg", 20, 0, 5);
 BookHist(FZRapidity_CC_gg, "FZRapidity_CC_gg", "FZRapidity_CC_gg", 20, 0, 2.5);
 BookHist(BZRapidity_CC_gg, "BZRapidity_CC_gg", "BZRapidity_CC_gg", 20, 0, 2.5);
 BookHist(FZRapidity_CF_gg, "FZRapidity_CF_gg", "FZRapidity_CF_gg", 20, 1, 4);
 BookHist(BZRapidity_CF_gg, "BZRapidity_CF_gg", "BZRapidity_CF_gg", 20, 1, 4);

 BookHist(ZPt_uub, "ZPt_uub", "ZPt_uub", 50, 0.0, 100.0);
 BookHist(ZMass_uub, "ZMass_uub", "ZMass_uub", 70, 60.0, 130.0);
 BookHist(ZRapidity_uub, "ZRapidity_uub", "ZRapidity_uub", 20, -5.0, 5.0);
 BookHist(ZPt_ddb, "ZPt_ddb", "ZPt_ddb", 50, 0.0, 100.0);
 BookHist(ZMass_ddb, "ZMass_ddb", "ZMass_ddb", 70, 60.0, 130.0);
 BookHist(ZRapidity_ddb, "ZRapidity_ddb", "ZRapidity_ddb", 20, -5.0, 5.0);
 BookHist(ZPt_ssb, "ZPt_ssb", "ZPt_ssb", 50, 0.0, 100.0);
 BookHist(ZMass_ssb, "ZMass_ssb", "ZMass_ssb", 70, 60.0, 130.0);
 BookHist(ZRapidity_ssb, "ZRapidity_ssb", "ZRapidity_ssb", 20, -5.0, 5.0);

 BookHist(ZMass_CC_total, "ZMass_CC_total", "ZMass_CC_total", 35, 60, 130);
 BookHist(ZMass_CC_wrong, "ZMass_CC_wrong", "ZMass_CC_wrong", 35, 60, 130);
 BookHist(ZMass_CF_total, "ZMass_CF_total", "ZMass_CF_total", 35, 60, 130);
 BookHist(ZMass_CF_wrong, "ZMass_CF_wrong", "ZMass_CF_wrong", 35, 60, 130);
 BookHist(ZMass_Full_total, "ZMass_Full_total", "ZMass_Full_total", 35, 60, 130);
 BookHist(ZMass_Full_wrong, "ZMass_Full_wrong", "ZMass_Full_wrong", 35, 60, 130);

 BookHist(ZMass_CC_uu_total, "ZMass_CC_uu_total", "ZMass_CC_uu_total", 35, 60, 130);
 BookHist(ZMass_CC_uu_wrong, "ZMass_CC_uu_wrong", "ZMass_CC_uu_wrong", 35, 60, 130);
 BookHist(ZMass_CC_dd_total, "ZMass_CC_dd_total", "ZMass_CC_dd_total", 35, 60, 130);
 BookHist(ZMass_CC_dd_wrong, "ZMass_CC_dd_wrong", "ZMass_CC_dd_wrong", 35, 60, 130);
 BookHist(ZMass_CF_uu_total, "ZMass_CF_uu_total", "ZMass_CF_uu_total", 35, 60, 130);
 BookHist(ZMass_CF_uu_wrong, "ZMass_CF_uu_wrong", "ZMass_CF_uu_wrong", 35, 60, 130);
 BookHist(ZMass_CF_dd_total, "ZMass_CF_dd_total", "ZMass_CF_dd_total", 35, 60, 130);
 BookHist(ZMass_CF_dd_wrong, "ZMass_CF_dd_wrong", "ZMass_CF_dd_wrong", 35, 60, 130);
 BookHist(ZMass_Full_uu_total, "ZMass_Full_uu_total", "ZMass_Full_uu_total", 35, 60, 130);
 BookHist(ZMass_Full_uu_wrong, "ZMass_Full_uu_wrong", "ZMass_Full_uu_wrong", 35, 60, 130);
 BookHist(ZMass_Full_dd_total, "ZMass_Full_dd_total", "ZMass_Full_dd_total", 35, 60, 130);
 BookHist(ZMass_Full_dd_wrong, "ZMass_Full_dd_wrong", "ZMass_Full_dd_wrong", 35, 60, 130);
 BookHist(ZMass_Full_ss_total, "ZMass_Full_ss_total", "ZMass_Full_ss_total", 35, 60, 130);
 BookHist(ZMass_Full_ss_wrong, "ZMass_Full_ss_wrong", "ZMass_Full_ss_wrong", 35, 60, 130);
 BookHist(ZMass_Full_cc_total, "ZMass_Full_cc_total", "ZMass_Full_cc_total", 35, 60, 130);
 BookHist(ZMass_Full_cc_wrong, "ZMass_Full_cc_wrong", "ZMass_Full_cc_wrong", 35, 60, 130);
 BookHist(ZMass_Full_bb_total, "ZMass_Full_bb_total", "ZMass_Full_bb_total", 35, 60, 130);
 BookHist(ZMass_Full_bb_wrong, "ZMass_Full_bb_wrong", "ZMass_Full_bb_wrong", 35, 60, 130);

 BookHist(FZmass_CC_uu_total, "FZmass_CC_uu_total", "FZmass_CC_uu_total", 35, 60, 130);
 BookHist(FZmass_CC_uu_wrong, "FZmass_CC_uu_wrong", "FZmass_CC_uu_wrong", 35, 60, 130);
 BookHist(BZmass_CC_uu_total, "BZmass_CC_uu_total", "BZmass_CC_uu_total", 35, 60, 130);
 BookHist(BZmass_CC_uu_wrong, "BZmass_CC_uu_wrong", "BZmass_CC_uu_wrong", 35, 60, 130);
 BookHist(FZmass_CC_dd_total, "FZmass_CC_dd_total", "FZmass_CC_dd_total", 35, 60, 130);
 BookHist(FZmass_CC_dd_wrong, "FZmass_CC_dd_wrong", "FZmass_CC_dd_wrong", 35, 60, 130);
 BookHist(BZmass_CC_dd_total, "BZmass_CC_dd_total", "BZmass_CC_dd_total", 35, 60, 130);
 BookHist(BZmass_CC_dd_wrong, "BZmass_CC_dd_wrong", "BZmass_CC_dd_wrong", 35, 60, 130);
 BookHist(FZmass_CF_uu_total, "FZmass_CF_uu_total", "FZmass_CF_uu_total", 35, 60, 130);
 BookHist(FZmass_CF_uu_wrong, "FZmass_CF_uu_wrong", "FZmass_CF_uu_wrong", 35, 60, 130);
 BookHist(BZmass_CF_uu_total, "BZmass_CF_uu_total", "BZmass_CF_uu_total", 35, 60, 130);
 BookHist(BZmass_CF_uu_wrong, "BZmass_CF_uu_wrong", "BZmass_CF_uu_wrong", 35, 60, 130);
 BookHist(FZmass_CF_dd_total, "FZmass_CF_dd_total", "FZmass_CF_dd_total", 35, 60, 130);
 BookHist(FZmass_CF_dd_wrong, "FZmass_CF_dd_wrong", "FZmass_CF_dd_wrong", 35, 60, 130);
 BookHist(BZmass_CF_dd_total, "BZmass_CF_dd_total", "BZmass_CF_dd_total", 35, 60, 130);
 BookHist(BZmass_CF_dd_wrong, "BZmass_CF_dd_wrong", "BZmass_CF_dd_wrong", 35, 60, 130);
 BookHist(FZmass_Full_uu_total, "FZmass_Full_uu_total", "FZmass_Full_uu_total", 35, 60, 130);
 BookHist(FZmass_Full_uu_wrong, "FZmass_Full_uu_wrong", "FZmass_Full_uu_wrong", 35, 60, 130);
 BookHist(BZmass_Full_uu_total, "BZmass_Full_uu_total", "BZmass_Full_uu_total", 35, 60, 130);
 BookHist(BZmass_Full_uu_wrong, "BZmass_Full_uu_wrong", "BZmass_Full_uu_wrong", 35, 60, 130);
 BookHist(FZmass_Full_dd_total, "FZmass_Full_dd_total", "FZmass_Full_dd_total", 35, 60, 130);
 BookHist(FZmass_Full_dd_wrong, "FZmass_Full_dd_wrong", "FZmass_Full_dd_wrong", 35, 60, 130);
 BookHist(BZmass_Full_dd_total, "BZmass_Full_dd_total", "BZmass_Full_dd_total", 35, 60, 130);
 BookHist(BZmass_Full_dd_wrong, "BZmass_Full_dd_wrong", "BZmass_Full_dd_wrong", 35, 60, 130);

 Book2DHist(ZMass_ZY_total, "ZMass_ZY_total", "ZMass_ZY_total", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(ZMass_ZY_wrong, "ZMass_ZY_wrong", "ZMass_ZY_wrong", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(ZMass_ZY_CC_total, "ZMass_ZY_CC_total", "ZMass_ZY_CC_total", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(ZMass_ZY_CC_wrong, "ZMass_ZY_CC_wrong", "ZMass_ZY_CC_wrong", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(ZMass_ZY_CF_total, "ZMass_ZY_CF_total", "ZMass_ZY_CF_total", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(ZMass_ZY_CF_wrong, "ZMass_ZY_CF_wrong", "ZMass_ZY_CF_wrong", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(ZMass_ZY_uu_total, "ZMass_ZY_uu_total", "ZMass_ZY_uu_total", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(ZMass_ZY_uu_wrong, "ZMass_ZY_uu_wrong", "ZMass_ZY_uu_wrong", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(ZMass_ZY_CC_uu_total, "ZMass_ZY_CC_uu_total", "ZMass_ZY_CC_uu_total", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(ZMass_ZY_CC_uu_wrong, "ZMass_ZY_CC_uu_wrong", "ZMass_ZY_CC_uu_wrong", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(ZMass_ZY_CF_uu_total, "ZMass_ZY_CF_uu_total", "ZMass_ZY_CF_uu_total", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(ZMass_ZY_CF_uu_wrong, "ZMass_ZY_CF_uu_wrong", "ZMass_ZY_CF_uu_wrong", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(ZMass_ZY_dd_total, "ZMass_ZY_dd_total", "ZMass_ZY_dd_total", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(ZMass_ZY_dd_wrong, "ZMass_ZY_dd_wrong", "ZMass_ZY_dd_wrong", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(ZMass_ZY_CC_dd_total, "ZMass_ZY_CC_dd_total", "ZMass_ZY_CC_dd_total", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(ZMass_ZY_CC_dd_wrong, "ZMass_ZY_CC_dd_wrong", "ZMass_ZY_CC_dd_wrong", 30, rangeMass, ZY_CC_bin, rangeZYCC);
 Book2DHist(ZMass_ZY_CF_dd_total, "ZMass_ZY_CF_dd_total", "ZMass_ZY_CF_dd_total", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(ZMass_ZY_CF_dd_wrong, "ZMass_ZY_CF_dd_wrong", "ZMass_ZY_CF_dd_wrong", 30, rangeMass, ZY_CF_bin, rangeZYCF);
 Book2DHist(FZMass_ZY_total, "FZMass_ZY_total", "FZMass_ZY_total", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(FZMass_ZY_wrong, "FZMass_ZY_wrong", "FZMass_ZY_wrong", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(BZMass_ZY_total, "BZMass_ZY_total", "BZMass_ZY_total", 30, rangeMass, ZY_bin, rangeZY);
 Book2DHist(BZMass_ZY_wrong, "BZMass_ZY_wrong", "BZMass_ZY_wrong", 30, rangeMass, ZY_bin, rangeZY);

 Book2DHist(ZMass_ZPt_total, "ZMass_ZPt_total", "ZMass_ZPt_total", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(ZMass_ZPt_wrong, "ZMass_ZPt_wrong", "ZMass_ZPt_wrong", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(ZMass_ZPt_CC_total, "ZMass_ZPt_CC_total", "ZMass_ZPt_CC_total", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(ZMass_ZPt_CC_wrong, "ZMass_ZPt_CC_wrong", "ZMass_ZPt_CC_wrong", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(ZMass_ZPt_CF_total, "ZMass_ZPt_CF_total", "ZMass_ZPt_CF_total", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(ZMass_ZPt_CF_wrong, "ZMass_ZPt_CF_wrong", "ZMass_ZPt_CF_wrong", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(ZMass_ZPt_uu_total, "ZMass_ZPt_uu_total", "ZMass_ZPt_uu_total", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(ZMass_ZPt_uu_wrong, "ZMass_ZPt_uu_wrong", "ZMass_ZPt_uu_wrong", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(ZMass_ZPt_CC_uu_total, "ZMass_ZPt_CC_uu_total", "ZMass_ZPt_CC_uu_total", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(ZMass_ZPt_CC_uu_wrong, "ZMass_ZPt_CC_uu_wrong", "ZMass_ZPt_CC_uu_wrong", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(ZMass_ZPt_CF_uu_total, "ZMass_ZPt_CF_uu_total", "ZMass_ZPt_CF_uu_total", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(ZMass_ZPt_CF_uu_wrong, "ZMass_ZPt_CF_uu_wrong", "ZMass_ZPt_CF_uu_wrong", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(ZMass_ZPt_dd_total, "ZMass_ZPt_dd_total", "ZMass_ZPt_dd_total", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(ZMass_ZPt_dd_wrong, "ZMass_ZPt_dd_wrong", "ZMass_ZPt_dd_wrong", 30, rangeMass, ZPt_bin, RangeZPt);
 Book2DHist(ZMass_ZPt_CC_dd_total, "ZMass_ZPt_CC_dd_total", "ZMass_ZPt_CC_dd_total", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(ZMass_ZPt_CC_dd_wrong, "ZMass_ZPt_CC_dd_wrong", "ZMass_ZPt_CC_dd_wrong", 30, rangeMass, ZPt_CC_bin, RangeZPtCC);
 Book2DHist(ZMass_ZPt_CF_dd_total, "ZMass_ZPt_CF_dd_total", "ZMass_ZPt_CF_dd_total", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);
 Book2DHist(ZMass_ZPt_CF_dd_wrong, "ZMass_ZPt_CF_dd_wrong", "ZMass_ZPt_CF_dd_wrong", 30, rangeMass, ZPt_CF_bin, RangeZPtCF);

 BookMultiBinHist(ZMass_ZY_total_multi, YMultiBin, "ZMass_ZY_total", "ZMass_ZY_total", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_wrong_multi, YMultiBin, "ZMass_ZY_wrong", "ZMass_ZY_wrong", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CC_total_multi, YMultiBinCC, "ZMass_ZY_CC_total", "ZMass_ZY_CC_total", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CC_wrong_multi, YMultiBinCC, "ZMass_ZY_CC_wrong", "ZMass_ZY_CC_wrong", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CF_total_multi, YMultiBinCF, "ZMass_ZY_CF_total", "ZMass_ZY_CF_total", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CF_wrong_multi, YMultiBinCF, "ZMass_ZY_CF_wrong", "ZMass_ZY_CF_wrong", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_uu_total_multi, YMultiBin, "ZMass_ZY_uu_total", "ZMass_ZY_uu_total", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_uu_wrong_multi, YMultiBin, "ZMass_ZY_uu_wrong", "ZMass_ZY_uu_wrong", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CC_uu_total_multi, YMultiBinCC, "ZMass_ZY_CC_uu_total", "ZMass_ZY_CC_uu_total", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CC_uu_wrong_multi, YMultiBinCC, "ZMass_ZY_CC_uu_wrong", "ZMass_ZY_CC_uu_wrong", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CF_uu_total_multi, YMultiBinCF, "ZMass_ZY_CF_uu_total", "ZMass_ZY_CF_uu_total", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CF_uu_wrong_multi, YMultiBinCF, "ZMass_ZY_CF_uu_wrong", "ZMass_ZY_CF_uu_wrong", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_dd_total_multi, YMultiBin, "ZMass_ZY_dd_total", "ZMass_ZY_dd_total", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_dd_wrong_multi, YMultiBin, "ZMass_ZY_dd_wrong", "ZMass_ZY_dd_wrong", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CC_dd_total_multi, YMultiBinCC, "ZMass_ZY_CC_dd_total", "ZMass_ZY_CC_dd_total", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CC_dd_wrong_multi, YMultiBinCC, "ZMass_ZY_CC_dd_wrong", "ZMass_ZY_CC_dd_wrong", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CF_dd_total_multi, YMultiBinCF, "ZMass_ZY_CF_dd_total", "ZMass_ZY_CF_dd_total", 30, rangeMass);
 BookMultiBinHist(ZMass_ZY_CF_dd_wrong_multi, YMultiBinCF, "ZMass_ZY_CF_dd_wrong", "ZMass_ZY_CF_dd_wrong", 30, rangeMass);

 Book3DHist(ZMass_ZY_QT_total, "ZMass_ZY_QT_total", "ZMass_ZY_QT_total", 35, 60, 130, ZY_bin, ZY_left, ZY_right, 5, 0, 100);
 Book3DHist(ZMass_ZY_QT_wrong, "ZMass_ZY_QT_wrong", "ZMass_ZY_QT_wrong", 35, 60, 130, ZY_bin, ZY_left, ZY_right, 5, 0, 100);
 Book3DHist(ZMass_ZY_QT_CC_total, "ZMass_ZY_QT_CC_total", "ZMass_ZY_QT_CC_total", 35, 60, 130, ZY_CC_bin, ZY_CC_left, ZY_CC_right, 5, 0, 100);
 Book3DHist(ZMass_ZY_QT_CC_wrong, "ZMass_ZY_QT_CC_wrong", "ZMass_ZY_QT_CC_wrong", 35, 60, 130, ZY_CC_bin, ZY_CC_left, ZY_CC_right, 5, 0, 100);
 Book3DHist(ZMass_ZY_QT_CF_total, "ZMass_ZY_QT_CF_total", "ZMass_ZY_QT_CF_total", 35, 60, 130, ZY_CF_bin, ZY_CF_left, ZY_CF_right, 5, 0, 100);
 Book3DHist(ZMass_ZY_QT_CF_wrong, "ZMass_ZY_QT_CF_wrong", "ZMass_ZY_QT_CF_wrong", 35, 60, 130, ZY_CF_bin, ZY_CF_left, ZY_CF_right, 5, 0, 100);

// BookHist(ZPt_total, "ZPt_total", "ZPt_total", 43, rangeZPt2);
// BookHist(ZPt_wrong, "ZPt_wrong", "ZPt_wrong", 43, rangeZPt2);
 BookHist(ZPt_total, "ZPt_total", "ZPt_total", 100, 0, 100);
 BookHist(ZPt_wrong, "ZPt_wrong", "ZPt_wrong", 100, 0, 100);
 BookHist(ZPt_LepPtCut_total, "ZPt_LepPtCut_total", "ZPt_LepPtCut_total", 100, 0, 100);
 BookHist(ZPt_LepPtCut_wrong, "ZPt_LepPtCut_wrong", "ZPt_LepPtCut_wrong", 100, 0, 100);
 BookHist(ZPt_NoLepPtCut_total, "ZPt_NoLepPtCut_total", "ZPt_NoLepPtCut_total", 100, 0, 100);
 BookHist(ZPt_NoLepPtCut_wrong, "ZPt_NoLepPtCut_wrong", "ZPt_NoLepPtCut_wrong", 100, 0, 100);
 BookHist(ZRapidity_total, "ZRapidity_total", "ZRapidity_total", 20, -5, 5);
 BookHist(ZRapidity_wrong, "ZRapidity_wrong", "ZRapidity_wrong", 20, -5, 5);
 BookHist(ZRapidity_LepPtCut_total, "ZRapidity_LepPtCut_total", "ZRapidity_LepPtCut_total", 20, -5, 5);
 BookHist(ZRapidity_LepPtCut_wrong, "ZRapidity_LepPtCut_wrong", "ZRapidity_LepPtCut_wrong", 20, -5, 5);
 BookHist(ZRapidity_NoLepPtCut_total, "ZRapidity_NoLepPtCut_total", "ZRapidity_NoLepPtCut_total", 20, -5, 5);
 BookHist(ZRapidity_NoLepPtCut_wrong, "ZRapidity_NoLepPtCut_wrong", "ZRapidity_NoLepPtCut_wrong", 20, -5, 5);
 BookHist(ZRapidity_uu_total, "ZRapidity_uu_total", "ZRapidity_uu_total", 20, -5, 5);
 BookHist(ZRapidity_uu_wrong, "ZRapidity_uu_wrong", "ZRapidity_uu_wrong", 20, -5, 5);
 BookHist(ZRapidity_dd_total, "ZRapidity_dd_total", "ZRapidity_dd_total", 20, -5, 5);
 BookHist(ZRapidity_dd_wrong, "ZRapidity_dd_wrong", "ZRapidity_dd_wrong", 20, -5, 5);
 BookHist(ZRapidityAbs_total, "ZRapidityAbs_total", "ZRapidityAbs_total", 20, 0, 5);
 BookHist(ZRapidityAbs_wrong, "ZRapidityAbs_wrong", "ZRapidityAbs_wrong", 20, 0, 5);
 BookHist(CosThetaQ_total, "CosThetaQ_total", "CosThetaQ_total", 20, -1, 1);
 BookHist(CosThetaQ_wrong, "CosThetaQ_wrong", "CosThetaQ_wrong", 20, -1, 1);

 BookAngularHist(A0_ZPt, "A0_ZPt", "A0", 23, rangeZPt);
 BookAngularHist(A1_ZPt, "A1_ZPt", "A1", 23, rangeZPt);
 BookAngularHist(A2_ZPt, "A2_ZPt", "A2", 23, rangeZPt);
 BookAngularHist(A3_ZPt, "A3_ZPt", "A3", 23, rangeZPt);
 BookAngularHist(A4_ZPt, "A4_ZPt", "A4", 23, rangeZPt);
 BookAngularHist(L0_ZPt, "L0_ZPt", "L0", 23, rangeZPt);


}

void HistsPythia::GetReweightFactor()
{
 ResetHists();
}

void HistsPythia::RetrieveWeight(double ZY, double &FZY, double &BZY, double &FZY_CC, double &BZY_CC, double &FZY_CF, double &BZY_CF)
{
}

void HistsPythia::outputInformation()
{
 double rangeZY[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
 double rangeZYCC[4] = {0.0, 0.5, 1.0, 2.5};
 double rangeZYCF[4] = {1.0, 1.5, 2.0, 4.0};

 double RangeZPt[6] = {0.0, 20.0, 40.0, 60.0, 80.0, 100.0};
 double RangeZPtCC[6] = {0.0, 20.0, 40.0, 60.0, 80.0, 100.0};
 double RangeZPtCF[6] = {0.0, 20.0, 40.0, 60.0, 80.0, 100.0};

 //For getting the AFB and AFB Slope

 double xbins1[11] = {80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100};
 double xbins2[31] = {60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120};
 double xbins3[9] = {82, 84, 86, 88, 90, 92, 94, 96, 98};
 double xbins4[7] = {84, 86, 88, 90, 92, 94, 96};
 double xbins5[2] = {80, 100};

 //AFB Slope
 TH1D *FZmass_CC_80_100 = (TH1D *)FZmass_CC->at(0)->Rebin(10, "FZmass_CC_80_100", xbins1);
 TH1D *BZmass_CC_80_100 = (TH1D *)BZmass_CC->at(0)->Rebin(10, "BZmass_CC_80_100", xbins1);
 TH1D *FZmass_CF_80_100 = (TH1D *)FZmass_CF->at(0)->Rebin(10, "FZmass_CF_80_100", xbins1);
 TH1D *BZmass_CF_80_100 = (TH1D *)BZmass_CF->at(0)->Rebin(10, "BZmass_CF_80_100", xbins1);
 TH1D *FZmass_80_100 = (TH1D *)FZmass->at(0)->Rebin(10, "FZmass_80_100", xbins1);
 TH1D *BZmass_80_100 = (TH1D *)BZmass->at(0)->Rebin(10, "BZmass_80_100", xbins1);

 TH1D *FZmass_CC_82_98 = (TH1D *)FZmass_CC->at(0)->Rebin(8, "FZmass_CC_82_98", xbins3);
 TH1D *BZmass_CC_82_98 = (TH1D *)BZmass_CC->at(0)->Rebin(8, "BZmass_CC_82_98", xbins3);
 TH1D *FZmass_CF_82_98 = (TH1D *)FZmass_CF->at(0)->Rebin(8, "FZmass_CF_82_98", xbins3);
 TH1D *BZmass_CF_82_98 = (TH1D *)BZmass_CF->at(0)->Rebin(8, "BZmass_CF_82_98", xbins3);
 TH1D *FZmass_82_98 = (TH1D *)FZmass->at(0)->Rebin(8, "FZmass_82_98", xbins3);
 TH1D *BZmass_82_98 = (TH1D *)BZmass->at(0)->Rebin(8, "BZmass_82_98", xbins3);

 TH1D *FZmass_CC_84_96 = (TH1D *)FZmass_CC->at(0)->Rebin(6, "FZmass_CC_84_96", xbins4);
 TH1D *BZmass_CC_84_96 = (TH1D *)BZmass_CC->at(0)->Rebin(6, "BZmass_CC_84_96", xbins4);
 TH1D *FZmass_CF_84_96 = (TH1D *)FZmass_CF->at(0)->Rebin(6, "FZmass_CF_84_96", xbins4);
 TH1D *BZmass_CF_84_96 = (TH1D *)BZmass_CF->at(0)->Rebin(6, "BZmass_CF_84_96", xbins4);
 TH1D *FZmass_84_96 = (TH1D *)FZmass->at(0)->Rebin(6, "FZmass_84_96", xbins4);
 TH1D *BZmass_84_96 = (TH1D *)BZmass->at(0)->Rebin(6, "BZmass_84_96", xbins4);

 TH1D *FZmass_CC_Average = (TH1D *)FZmass_CC->at(0)->Rebin(1, "FZmass_CC_Average", xbins5);
 TH1D *BZmass_CC_Average = (TH1D *)BZmass_CC->at(0)->Rebin(1, "BZmass_CC_Average", xbins5);
 TH1D *FZmass_CF_Average = (TH1D *)FZmass_CF->at(0)->Rebin(1, "FZmass_CF_Average", xbins5);
 TH1D *BZmass_CF_Average = (TH1D *)BZmass_CF->at(0)->Rebin(1, "BZmass_CF_Average", xbins5);
 TH1D *FZmass_Average = (TH1D *)FZmass->at(0)->Rebin(1, "FZmass_Average", xbins5);
 TH1D *BZmass_Average = (TH1D *)BZmass->at(0)->Rebin(1, "BZmass_Average", xbins5);

 TH1D *FZmass_Hadron_uu_Average = (TH1D *)FZmass_Hadron_uu->at(0)->Rebin(1, "FZmass_Hadron_uu_Average", xbins5);
 TH1D *BZmass_Hadron_uu_Average = (TH1D *)BZmass_Hadron_uu->at(0)->Rebin(1, "BZmass_Hadron_uu_Average", xbins5);
 TH1D *FZmass_Hadron_dd_Average = (TH1D *)FZmass_Hadron_dd->at(0)->Rebin(1, "FZmass_Hadron_dd_Average", xbins5);
 TH1D *BZmass_Hadron_dd_Average = (TH1D *)BZmass_Hadron_dd->at(0)->Rebin(1, "BZmass_Hadron_dd_Average", xbins5);

 TH1D *FZmass_Hadron_uudd_Average = (TH1D *)FZmass_Hadron_uu->at(0)->Rebin(1, "FZmass_Hadron_uudd_Average", xbins5);
 FZmass_Hadron_uudd_Average->Add(FZmass_Hadron_dd_Average);
 TH1D *BZmass_Hadron_uudd_Average = (TH1D *)BZmass_Hadron_uu->at(0)->Rebin(1, "BZmass_Hadron_uudd_Average", xbins5);
 BZmass_Hadron_uudd_Average->Add(BZmass_Hadron_dd_Average);

 TH1D *FZmass_Hadron_utype_Average = (TH1D *)FZmass_Hadron_utype->at(0)->Rebin(1, "FZmass_Hadron_utype_Average", xbins5);
 TH1D *BZmass_Hadron_utype_Average = (TH1D *)BZmass_Hadron_utype->at(0)->Rebin(1, "BZmass_Hadron_utype_Average", xbins5);
 TH1D *FZmass_Hadron_dtype_Average = (TH1D *)FZmass_Hadron_dtype->at(0)->Rebin(1, "FZmass_Hadron_dtype_Average", xbins5);
 TH1D *BZmass_Hadron_dtype_Average = (TH1D *)BZmass_Hadron_dtype->at(0)->Rebin(1, "BZmass_Hadron_dtype_Average", xbins5);

 TH1D *AFB_CC_80_100 = (TH1D *)FZmass_CC_80_100->Clone("AFB_CC_80_100");
 AFB_CC_80_100->Reset();
 TH1D *AFB_CF_80_100 = (TH1D *)FZmass_CF_80_100->Clone("AFB_CF_80_100");
 AFB_CF_80_100->Reset();
 TH1D *AFB_Full_80_100 = (TH1D *)FZmass_80_100->Clone("AFB_Full_80_100");
 AFB_Full_80_100->Reset();

 TH1D *AFB_CC_82_98 = (TH1D *)FZmass_CC_82_98->Clone("AFB_CC_82_98");
 AFB_CC_82_98->Reset();
 TH1D *AFB_CF_82_98 = (TH1D *)FZmass_CF_82_98->Clone("AFB_CF_82_98");
 AFB_CF_82_98->Reset();
 TH1D *AFB_Full_82_98 = (TH1D *)FZmass_82_98->Clone("AFB_Full_82_98");
 AFB_Full_82_98->Reset();

 TH1D *AFB_CC_84_96 = (TH1D *)FZmass_CC_84_96->Clone("AFB_CC_84_96");
 AFB_CC_84_96->Reset();
 TH1D *AFB_CF_84_96 = (TH1D *)FZmass_CF_84_96->Clone("AFB_CF_84_96");
 AFB_CF_84_96->Reset();
 TH1D *AFB_Full_84_96 = (TH1D *)FZmass_84_96->Clone("AFB_Full_84_96");
 AFB_Full_84_96->Reset();

 AveAFB_CC = (TH1D *)FZmass_CC_Average->Clone("AveAFB_CC");
 AveAFB_CC->Reset();
 AveAFB_CF = (TH1D *)FZmass_CF_Average->Clone("AveAFB_CF");
 AveAFB_CF->Reset();
 AveAFB_Full = (TH1D *)FZmass_Average->Clone("AveAFB_Full");
 AveAFB_Full->Reset();
 AveAFB_Full_uu = (TH1D *)FZmass_Hadron_uu_Average->Clone("AveAFB_Full_uu");
 AveAFB_Full_uu->Reset();
 AveAFB_Full_dd = (TH1D *)FZmass_Hadron_dd_Average->Clone("AveAFB_Full_dd");
 AveAFB_Full_dd->Reset();
 AveAFB_Full_uudd = (TH1D *)FZmass_Hadron_uudd_Average->Clone("AveAFB_Full_uudd");
 AveAFB_Full_uudd->Reset();
 AveAFB_Full_utype = (TH1D *)FZmass_Hadron_utype_Average->Clone("AveAFB_Full_utype");
 AveAFB_Full_utype->Reset();
 AveAFB_Full_dtype = (TH1D *)FZmass_Hadron_dtype_Average->Clone("AveAFB_Full_dtype");
 AveAFB_Full_dtype->Reset();

 AFBFunction(FZmass_CC_80_100, BZmass_CC_80_100, AFB_CC_80_100);
 AFBFunction(FZmass_CF_80_100, BZmass_CF_80_100, AFB_CF_80_100);
 AFBFunction(FZmass_80_100, BZmass_80_100, AFB_Full_80_100);

 AFBFunction(FZmass_CC_82_98, BZmass_CC_82_98, AFB_CC_82_98);
 AFBFunction(FZmass_CF_82_98, BZmass_CF_82_98, AFB_CF_82_98);
 AFBFunction(FZmass_82_98, BZmass_82_98, AFB_Full_82_98);

 AFBFunction(FZmass_CC_84_96, BZmass_CC_84_96, AFB_CC_84_96);
 AFBFunction(FZmass_CF_84_96, BZmass_CF_84_96, AFB_CF_84_96);
 AFBFunction(FZmass_84_96, BZmass_84_96, AFB_Full_84_96);

 AFBFunction(FZmass_CC_Average, BZmass_CC_Average, AveAFB_CC);
 AFBFunction(FZmass_CF_Average, BZmass_CF_Average, AveAFB_CF);
 AFBFunction(FZmass_Average, BZmass_Average, AveAFB_Full);
 AFBFunction(FZmass_Hadron_uu_Average, BZmass_Hadron_uu_Average, AveAFB_Full_uu);
 AFBFunction(FZmass_Hadron_dd_Average, BZmass_Hadron_dd_Average, AveAFB_Full_dd);
 AFBFunction(FZmass_Hadron_uudd_Average, BZmass_Hadron_uudd_Average, AveAFB_Full_uudd);
 AFBFunction(FZmass_Hadron_utype_Average, BZmass_Hadron_utype_Average, AveAFB_Full_utype);
 AFBFunction(FZmass_Hadron_dtype_Average, BZmass_Hadron_dtype_Average, AveAFB_Full_dtype);

 AFBSlope_CC = new TH1D("AFBSlope_CC", "AFBSlope_CC", 1, 80, 100);
 AFBSlope_CF = new TH1D("AFBSlope_CF", "AFBSlope_CF", 1, 80, 100);
 AFBSlope_Full = new TH1D("AFBSlope_Full", "AFBSlope_Full", 1, 80, 100);

 AFBSlope_82_98_CC = new TH1D("AFBSlope_82_98_CC", "AFBSlope_82_98_CC", 1, 82, 98);
 AFBSlope_82_98_CF = new TH1D("AFBSlope_82_98_CF", "AFBSlope_82_98_CF", 1, 82, 98);
 AFBSlope_82_98_Full = new TH1D("AFBSlope_82_98_Full", "AFBSlope_82_98_Full", 1, 82, 98);

 AFBSlope_84_96_CC = new TH1D("AFBSlope_84_96_CC", "AFBSlope_84_96_CC", 1, 84, 96);
 AFBSlope_84_96_CF = new TH1D("AFBSlope_84_96_CF", "AFBSlope_84_96_CF", 1, 84, 96);
 AFBSlope_84_96_Full = new TH1D("AFBSlope_84_96_Full", "AFBSlope_84_96_Full", 1, 84, 96);

 AFBOffset_CC = new TH1D("AFBOffset_CC", "AFBOffset_CC", 1, 80, 100);
 AFBOffset_CF = new TH1D("AFBOffset_CF", "AFBOffset_CF", 1, 80, 100);
 AFBOffset_Full = new TH1D("AFBOffset_Full", "AFBOffset_Full", 1, 80, 100);

 AFBOffset_82_98_CC = new TH1D("AFBOffset_82_98_CC", "AFBOffset_82_98_CC", 1, 82, 98);
 AFBOffset_82_98_CF = new TH1D("AFBOffset_82_98_CF", "AFBOffset_82_98_CF", 1, 82, 98);
 AFBOffset_82_98_Full = new TH1D("AFBOffset_82_98_Full", "AFBOffset_82_98_Full", 1, 82, 98);

 AFBOffset_84_96_CC = new TH1D("AFBOffset_84_96_CC", "AFBOffset_84_96_CC", 1, 84, 96);
 AFBOffset_84_96_CF = new TH1D("AFBOffset_84_96_CF", "AFBOffset_84_96_CF", 1, 84, 96);
 AFBOffset_84_96_Full = new TH1D("AFBOffset_84_96_Full", "AFBOffset_84_96_Full", 1, 84, 96);

 TF1 *Slope_CC;
 TF1 *Slope_CF;
 TF1 *Slope_Full;
 double *par = new double[2];
 double *parErr = new double[2];
 LinearFitting(AFB_CC_80_100, Slope_CC, par, parErr);
 AFBSlope_CC->SetBinContent(1, par[0]);
 AFBSlope_CC->SetBinError(1, parErr[0]);
 AFBOffset_CC->SetBinContent(1, par[1]);
 AFBOffset_CC->SetBinError(1, parErr[1]);
 LinearFitting(AFB_CF_80_100, Slope_CF, par, parErr);
 AFBSlope_CF->SetBinContent(1, par[0]);
 AFBSlope_CF->SetBinError(1, parErr[0]);
 AFBOffset_CF->SetBinContent(1, par[1]);
 AFBOffset_CF->SetBinError(1, parErr[1]);
 LinearFitting(AFB_Full_80_100, Slope_Full, par, parErr);
 AFBSlope_Full->SetBinContent(1, par[0]);
 AFBSlope_Full->SetBinError(1, parErr[0]);
 AFBOffset_Full->SetBinContent(1, par[1]);
 AFBOffset_Full->SetBinError(1, parErr[1]);

 TF1 *Slope_82_98_CC;
 TF1 *Slope_82_98_CF;
 TF1 *Slope_82_98_Full;
 LinearFitting(AFB_CC_82_98, Slope_82_98_CC, par, parErr);
 AFBSlope_82_98_CC->SetBinContent(1, par[0]);
 AFBSlope_82_98_CC->SetBinError(1, parErr[0]);
 AFBOffset_82_98_CC->SetBinContent(1, par[1]);
 AFBOffset_82_98_CC->SetBinError(1, parErr[1]);
 LinearFitting(AFB_CF_82_98, Slope_82_98_CF, par, parErr);
 AFBSlope_82_98_CF->SetBinContent(1, par[0]);
 AFBSlope_82_98_CF->SetBinError(1, parErr[0]);
 AFBOffset_82_98_CF->SetBinContent(1, par[1]);
 AFBOffset_82_98_CF->SetBinError(1, parErr[1]);
 LinearFitting(AFB_Full_82_98, Slope_82_98_Full, par, parErr);
 AFBSlope_82_98_Full->SetBinContent(1, par[0]);
 AFBSlope_82_98_Full->SetBinError(1, parErr[0]);
 AFBOffset_82_98_Full->SetBinContent(1, par[1]);
 AFBOffset_82_98_Full->SetBinError(1, parErr[1]);

 TF1 *Slope_84_96_CC;
 TF1 *Slope_84_96_CF;
 TF1 *Slope_84_96_Full;
 LinearFitting(AFB_CC_84_96, Slope_84_96_CC, par, parErr);
 AFBSlope_84_96_CC->SetBinContent(1, par[0]);
 AFBSlope_84_96_CC->SetBinError(1, parErr[0]);
 AFBOffset_84_96_CC->SetBinContent(1, par[1]);
 AFBOffset_84_96_CC->SetBinError(1, parErr[1]);
 LinearFitting(AFB_CF_84_96, Slope_84_96_CF, par, parErr);
 AFBSlope_84_96_CF->SetBinContent(1, par[0]);
 AFBSlope_84_96_CF->SetBinError(1, parErr[0]);
 AFBOffset_84_96_CF->SetBinContent(1, par[1]);
 AFBOffset_84_96_CF->SetBinError(1, parErr[1]);
 LinearFitting(AFB_Full_84_96, Slope_84_96_Full, par, parErr);
 AFBSlope_84_96_Full->SetBinContent(1, par[0]);
 AFBSlope_84_96_Full->SetBinError(1, parErr[0]);
 AFBOffset_84_96_Full->SetBinContent(1, par[1]);
 AFBOffset_84_96_Full->SetBinError(1, parErr[1]);

 AFBSlope_CC->Write();
 AFBSlope_CF->Write();
 AFBSlope_Full->Write();
 AFBSlope_82_98_CC->Write();
 AFBSlope_82_98_CF->Write();
 AFBSlope_82_98_Full->Write();
 AFBSlope_84_96_CC->Write();
 AFBSlope_84_96_CF->Write();
 AFBSlope_84_96_Full->Write();
 AFBOffset_CC->Write();
 AFBOffset_CF->Write();
 AFBOffset_Full->Write();
 AFBOffset_82_98_CC->Write();
 AFBOffset_82_98_CF->Write();
 AFBOffset_82_98_Full->Write();
 AFBOffset_84_96_CC->Write();
 AFBOffset_84_96_CF->Write();
 AFBOffset_84_96_Full->Write();
 AveAFB_CC->Write();
 AveAFB_CF->Write();
 AveAFB_Full->Write();
 AveAFB_Full_uu->Write();
 AveAFB_Full_dd->Write();
 AveAFB_Full_uudd->Write();
 AveAFB_Full_utype->Write();
 AveAFB_Full_dtype->Write();

 //AFB Diff
 TH1D *FZmass_CC_60_120 = (TH1D *)FZmass_CC->at(0)->Rebin(30, "FZmass_CC_60_120", xbins2);
 TH1D *BZmass_CC_60_120 = (TH1D *)BZmass_CC->at(0)->Rebin(30, "BZmass_CC_60_120", xbins2);
 TH1D *FZmass_CF_60_120 = (TH1D *)FZmass_CF->at(0)->Rebin(30, "FZmass_CF_60_120", xbins2);
 TH1D *BZmass_CF_60_120 = (TH1D *)BZmass_CF->at(0)->Rebin(30, "BZmass_CF_60_120", xbins2);
 TH1D *FZmass_60_120 = (TH1D *)FZmass->at(0)->Rebin(30, "FZmass_60_120", xbins2);
 TH1D *BZmass_60_120 = (TH1D *)BZmass->at(0)->Rebin(30, "BZmass_60_120", xbins2);

 TH1D *AFB_CC_60_120 = (TH1D *)FZmass_CC_60_120->Clone("AFB_CC_60_120");
 AFB_CC_60_120->Reset();
 TH1D *AFB_CF_60_120 = (TH1D *)FZmass_CF_60_120->Clone("AFB_CF_60_120");
 AFB_CF_60_120->Reset();
 TH1D *AFB_Full_60_120 = (TH1D *)FZmass_60_120->Clone("AFB_Full_60_120");
 AFB_Full_60_120->Reset();

 AFBFunction(FZmass_CC_60_120, BZmass_CC_60_120, AFB_CC_60_120);
 AFBFunction(FZmass_CF_60_120, BZmass_CF_60_120, AFB_CF_60_120);
 AFBFunction(FZmass_60_120, BZmass_60_120, AFB_Full_60_120);

 AFBDiff_CC = new TH1D("AFBDiff_CC", "AFBDiff_CC", AFB_CC_60_120->GetNbinsX() / 2, 1, AFB_CC_60_120->GetNbinsX() / 2);
 AFBDiff_CC_ZPole = new TH1D("AFBDiff_CC_ZPole", "AFBDiff_CC_ZPole", 5, 1, 5);
 AFBDiff_CC_Side = new TH1D("AFBDiff_CC_Side", "AFBDiff_CC_Side", 10, 1, 10);

 AFBDiff_CF = new TH1D("AFBDiff_CF", "AFBDiff_CF", AFB_CF_60_120->GetNbinsX() / 2, 1, AFB_CF_60_120->GetNbinsX() / 2);
 AFBDiff_CF_ZPole = new TH1D("AFBDiff_CF_ZPole", "AFBDiff_CF_ZPole", 5, 1, 5);
 AFBDiff_CF_Side = new TH1D("AFBDiff_CF_Side", "AFBDiff_CF_Side", 10, 1, 10);

 AFBDiff_Full = new TH1D("AFBDiff_Full", "AFBDiff_Full", AFB_Full_60_120->GetNbinsX() / 2, 1, AFB_Full_60_120->GetNbinsX() / 2);
 AFBDiff_Full_ZPole = new TH1D("AFBDiff_Full_ZPole", "AFBDiff_Full_ZPole", 5, 1, 5);
 AFBDiff_Full_Side = new TH1D("AFBDiff_Full_Side", "AFBDiff_Full_Side", 10, 1, 10);

 for(int ibin = 1; ibin <= AFBDiff_CC->GetNbinsX(); ibin++){
   int FirstBin = ibin;
   int LastBin = AFBDiff_CC->GetNbinsX() * 2 - (ibin - 1);

   //CC
   double Diff = AFB_CC_60_120->GetBinContent(FirstBin) - AFB_CC_60_120->GetBinContent(LastBin);
   double DiffErr = sqrt(AFB_CC_60_120->GetBinError(FirstBin) * AFB_CC_60_120->GetBinError(FirstBin) + AFB_CC_60_120->GetBinError(LastBin) * AFB_CC_60_120->GetBinError(LastBin));

   if(ibin <= 10){
     AFBDiff_CC_Side->SetBinContent(ibin, Diff);
     AFBDiff_CC_Side->SetBinError(ibin, DiffErr);
   }
   else{
     AFBDiff_CC_ZPole->SetBinContent(ibin - 10, Diff);
     AFBDiff_CC_ZPole->SetBinError(ibin - 10, DiffErr);
   }
   AFBDiff_CC->SetBinContent(ibin, Diff);
   AFBDiff_CC->SetBinError(ibin, DiffErr);

   //CF
   Diff = AFB_CF_60_120->GetBinContent(FirstBin) - AFB_CF_60_120->GetBinContent(LastBin);
   DiffErr = sqrt(AFB_CF_60_120->GetBinError(FirstBin) * AFB_CF_60_120->GetBinError(FirstBin) + AFB_CF_60_120->GetBinError(LastBin) * AFB_CF_60_120->GetBinError(LastBin));

   if(ibin <= 10){
     AFBDiff_CF_Side->SetBinContent(ibin, Diff);
     AFBDiff_CF_Side->SetBinError(ibin, DiffErr);
   }
   else{
     AFBDiff_CF_ZPole->SetBinContent(ibin - 10, Diff);
     AFBDiff_CF_ZPole->SetBinError(ibin - 10, DiffErr);
   }
   AFBDiff_CF->SetBinContent(ibin, Diff);
   AFBDiff_CF->SetBinError(ibin, DiffErr);

   //Full
   Diff = AFB_Full_60_120->GetBinContent(FirstBin) - AFB_Full_60_120->GetBinContent(LastBin);
   DiffErr = sqrt(AFB_Full_60_120->GetBinError(FirstBin) * AFB_Full_60_120->GetBinError(FirstBin) + AFB_Full_60_120->GetBinError(LastBin) * AFB_Full_60_120->GetBinError(LastBin));

   if(ibin <= 10){
     AFBDiff_Full_Side->SetBinContent(ibin, Diff);
     AFBDiff_Full_Side->SetBinError(ibin, DiffErr);
   }
   else{
     AFBDiff_Full_ZPole->SetBinContent(ibin - 10, Diff);
     AFBDiff_Full_ZPole->SetBinError(ibin - 10, DiffErr);
   }
   AFBDiff_Full->SetBinContent(ibin, Diff);
   AFBDiff_Full->SetBinError(ibin, DiffErr);

 }

 AFBDiff_CC->Write();
 AFBDiff_CC_ZPole->Write();
 AFBDiff_CC_Side->Write();

 AFBDiff_CF->Write();
 AFBDiff_CF_ZPole->Write();
 AFBDiff_CF_Side->Write();

 AFBDiff_Full->Write();
 AFBDiff_Full_ZPole->Write();
 AFBDiff_Full_Side->Write();


 //AFB Gradient
 TH1D *AFB_CC_1GeV = (TH1D *)FZmass_CC->at(0)->Clone("AFB_CC_1GeV");
 AFB_CC_1GeV->Reset();
 TH1D *AFB_CF_1GeV = (TH1D *)FZmass_CF->at(0)->Clone("AFB_CF_1GeV");
 AFB_CF_1GeV->Reset();
 TH1D *AFB_Full_1GeV = (TH1D *)FZmass->at(0)->Clone("AFB_Full_1GeV");
 AFB_Full_1GeV->Reset();

 AFBFunction(FZmass_CC->at(0), BZmass_CC->at(0), AFB_CC_1GeV);
 AFBFunction(FZmass_CF->at(0), BZmass_CF->at(0), AFB_CF_1GeV);
 AFBFunction(FZmass->at(0), BZmass->at(0), AFB_Full_1GeV);

 AFBGradient_CC = new TH1D("AFBGradient_CC", "AFBGradient_CC", 35, 60, 130);
 AFBGradient_CF = new TH1D("AFBGradient_CF", "AFBGradient_CF", 35, 60, 130);
 AFBGradient_Full = new TH1D("AFBGradient_Full", "AFBGradient_Full", 35, 60, 130);

 for(int ibin = 1; ibin < AFBGradient_CC->GetNbinsX(); ibin++){
   double Diff;
   double DiffError;

   Diff = AFB_CC_1GeV->GetBinContent(2 * ibin) - AFB_CC_1GeV->GetBinContent(2 * ibin - 1);
   DiffError = sqrt(AFB_CC_1GeV->GetBinError(2 * ibin) * AFB_CC_1GeV->GetBinError(2 * ibin) + AFB_CC_1GeV->GetBinError(2 * ibin - 1) * AFB_CC_1GeV->GetBinError(2 * ibin - 1));
   AFBGradient_CC->SetBinContent(ibin, Diff);
   AFBGradient_CC->SetBinError(ibin, DiffError);

   Diff = AFB_CF_1GeV->GetBinContent(2 * ibin) - AFB_CF_1GeV->GetBinContent(2 * ibin - 1);
   DiffError = sqrt(AFB_CF_1GeV->GetBinError(2 * ibin) * AFB_CF_1GeV->GetBinError(2 * ibin) + AFB_CF_1GeV->GetBinError(2 * ibin - 1) * AFB_CF_1GeV->GetBinError(2 * ibin - 1));
   AFBGradient_CF->SetBinContent(ibin, Diff);
   AFBGradient_CF->SetBinError(ibin, DiffError);

   Diff = AFB_Full_1GeV->GetBinContent(2 * ibin) - AFB_Full_1GeV->GetBinContent(2 * ibin - 1);
   DiffError = sqrt(AFB_Full_1GeV->GetBinError(2 * ibin) * AFB_Full_1GeV->GetBinError(2 * ibin) + AFB_Full_1GeV->GetBinError(2 * ibin - 1) * AFB_Full_1GeV->GetBinError(2 * ibin - 1));
   AFBGradient_Full->SetBinContent(ibin, Diff);
   AFBGradient_Full->SetBinError(ibin, DiffError);
 }

 AFBGradient_CC->Write();
 AFBGradient_CF->Write();
 AFBGradient_Full->Write();

 //AFB
 FZmass_CC->at(0)->Rebin(2);
 BZmass_CC->at(0)->Rebin(2);
 FZmass_CF->at(0)->Rebin(2);
 BZmass_CF->at(0)->Rebin(2);
 FZmass->at(0)->Rebin(2);
 BZmass->at(0)->Rebin(2);
 FZmass_Hadron_uu->at(0)->Rebin(2);
 BZmass_Hadron_uu->at(0)->Rebin(2);
 FZmass_Hadron_dd->at(0)->Rebin(2);
 BZmass_Hadron_dd->at(0)->Rebin(2);
 FZmass_Hadron_utype->at(0)->Rebin(2);
 BZmass_Hadron_utype->at(0)->Rebin(2);
 FZmass_Hadron_dtype->at(0)->Rebin(2);
 BZmass_Hadron_dtype->at(0)->Rebin(2);
 FZmass_LepPtCut->at(0)->Rebin(2);
 BZmass_LepPtCut->at(0)->Rebin(2);
 FZmass_NoLepPtCut->at(0)->Rebin(2);
 BZmass_NoLepPtCut->at(0)->Rebin(2);

 AFB_CC = (TH1D *)FZmass_CC->at(0)->Clone("AFB_CC");
 AFB_CC->Reset();
 AFB_CF = (TH1D *)FZmass_CF->at(0)->Clone("AFB_CF");
 AFB_CF->Reset();
 AFB_Full = (TH1D *)FZmass->at(0)->Clone("AFB_Full");
 AFB_Full->Reset();
 AFB_Hadron_Full_uu = (TH1D *)FZmass_Hadron_uu->at(0)->Clone("AFB_Hadron_Full_uu");
 AFB_Hadron_Full_uu->Reset();
 AFB_Hadron_Full_dd = (TH1D *)FZmass_Hadron_dd->at(0)->Clone("AFB_Hadron_Full_dd");
 AFB_Hadron_Full_dd->Reset();
 AFB_Hadron_Full_utype = (TH1D *)FZmass_Hadron_utype->at(0)->Clone("AFB_Hadron_Full_utype");
 AFB_Hadron_Full_utype->Reset();
 AFB_Hadron_Full_dtype = (TH1D *)FZmass_Hadron_dtype->at(0)->Clone("AFB_Hadron_Full_dtype");
 AFB_Hadron_Full_dtype->Reset();
 AFB_LepPtCut = (TH1D *)FZmass_LepPtCut->at(0)->Clone("AFB_LepPtCut");
 AFB_LepPtCut->Reset();
 AFB_NoLepPtCut = (TH1D *)FZmass_NoLepPtCut->at(0)->Clone("AFB_NoLepPtCut");
 AFB_NoLepPtCut->Reset();

 TH1D* FZmass_Hadron_uudd = (TH1D *)FZmass_Hadron_uu->at(0)->Clone("FZmass_Hadron_uudd");
 FZmass_Hadron_uudd->Add(FZmass_Hadron_dd->at(0));
 TH1D* BZmass_Hadron_uudd = (TH1D *)BZmass_Hadron_uu->at(0)->Clone("BZmass_Hadron_uudd");
 BZmass_Hadron_uudd->Add(BZmass_Hadron_dd->at(0));
 AFB_Hadron_Full_uudd = (TH1D *)FZmass_Hadron_uudd->Clone("AFB_Hadron_Full_uudd");
 AFB_Hadron_Full_uudd->Reset();

 AFBFunction(FZmass_CC->at(0), BZmass_CC->at(0), AFB_CC);
 AFBFunction(FZmass_CF->at(0), BZmass_CF->at(0), AFB_CF);
 AFBFunction(FZmass->at(0), BZmass->at(0), AFB_Full);
 AFBFunction(FZmass_Hadron_uu->at(0), BZmass_Hadron_uu->at(0), AFB_Hadron_Full_uu);
 AFBFunction(FZmass_Hadron_dd->at(0), BZmass_Hadron_dd->at(0), AFB_Hadron_Full_dd);
 AFBFunction(FZmass_Hadron_uudd, BZmass_Hadron_uudd, AFB_Hadron_Full_uudd);
 AFBFunction(FZmass_Hadron_utype->at(0), BZmass_Hadron_utype->at(0), AFB_Hadron_Full_utype);
 AFBFunction(FZmass_Hadron_dtype->at(0), BZmass_Hadron_dtype->at(0), AFB_Hadron_Full_dtype);
 AFBFunction(FZmass_LepPtCut->at(0), BZmass_LepPtCut->at(0), AFB_LepPtCut);
 AFBFunction(FZmass_NoLepPtCut->at(0), BZmass_NoLepPtCut->at(0), AFB_NoLepPtCut);

 AFB_CC->Write();
 AFB_CF->Write();
 AFB_Full->Write();
 AFB_Hadron_Full_uu->Write();
 AFB_Hadron_Full_dd->Write();
 AFB_Hadron_Full_uudd->Write();
 AFB_Hadron_Full_utype->Write();
 AFB_Hadron_Full_dtype->Write();
 AFB_LepPtCut->Write();
 AFB_NoLepPtCut->Write();

//AFB vs Mass ZY
/* AFB_Mass_ZY_CC = (TH2D *)FZMass_ZY_CC->at(0)->Clone("AFB_Mass_ZY_CC");
 AFB_Mass_ZY_CC->Reset();
 AFB_Mass_ZY_CF = (TH2D *)FZMass_ZY_CF->at(0)->Clone("AFB_Mass_ZY_CF");
 AFB_Mass_ZY_CF->Reset();
 AFB_Mass_ZY_Full = (TH2D *)FZMass_ZY->at(0)->Clone("AFB_Mass_ZY_Full");
 AFB_Mass_ZY_Full->Reset();

 AFBFunction(FZMass_ZY_CC->at(0), BZMass_ZY_CC->at(0), AFB_Mass_ZY_CC);
 AFBFunction(FZMass_ZY_CF->at(0), BZMass_ZY_CF->at(0), AFB_Mass_ZY_CF);
 AFBFunction(FZMass_ZY->at(0), BZMass_ZY->at(0), AFB_Mass_ZY_Full);

 AFB_Mass_ZY_CC->Write();
 AFB_Mass_ZY_CF->Write();
 AFB_Mass_ZY_Full->Write();

 AFBSlope_ZY_CC = new TH1D("AFBSlope_ZY_CC", "AFBSlope_ZY_CC", ZY_CC_bin, rangeZYCC);
 AFBSlope_ZY_CF = new TH1D("AFBSlope_ZY_CF", "AFBSlope_ZY_CF", ZY_CF_bin, rangeZYCF);
 AFBSlope_ZY_Full = new TH1D("AFBSlope_ZY_Full", "AFBSlope_ZY_Full", ZY_bin, rangeZY);
 AFBOffset_ZY_CC = new TH1D("AFBOffset_ZY_CC", "AFBOffset_ZY_CC", ZY_CC_bin, rangeZYCC);
 AFBOffset_ZY_CF = new TH1D("AFBOffset_ZY_CF", "AFBOffset_ZY_CF", ZY_CF_bin, rangeZYCF);
 AFBOffset_ZY_Full = new TH1D("AFBOffset_ZY_Full", "AFBOffset_ZY_Full", ZY_bin, rangeZY);

 GetAFBSlopeAndOffset(AFB_Mass_ZY_CC, AFBSlope_ZY_CC, AFBOffset_ZY_CC);
 GetAFBSlopeAndOffset(AFB_Mass_ZY_CF, AFBSlope_ZY_CF, AFBOffset_ZY_CF);
 GetAFBSlopeAndOffset(AFB_Mass_ZY_Full, AFBSlope_ZY_Full, AFBOffset_ZY_Full);

 AFBSlope_ZY_CC->Write();
 AFBSlope_ZY_CF->Write();
 AFBSlope_ZY_Full->Write();
 AFBOffset_ZY_CC->Write();
 AFBOffset_ZY_CF->Write();
 AFBOffset_ZY_Full->Write();
*/
//AFB vs Mass ZPt
/* AFB_Mass_ZPt_CC = (TH2D *)FZMass_ZPt_CC->at(0)->Clone("AFB_Mass_ZPt_CC");
 AFB_Mass_ZPt_CC->Reset();
 AFB_Mass_ZPt_CF = (TH2D *)FZMass_ZPt_CF->at(0)->Clone("AFB_Mass_ZPt_CF");
 AFB_Mass_ZPt_CF->Reset();
 AFB_Mass_ZPt_Full = (TH2D *)FZMass_ZPt->at(0)->Clone("AFB_Mass_ZPt_Full");
 AFB_Mass_ZPt_Full->Reset();

 AFBFunction(FZMass_ZPt_CC->at(0), BZMass_ZPt_CC->at(0), AFB_Mass_ZPt_CC);
 AFBFunction(FZMass_ZPt_CF->at(0), BZMass_ZPt_CF->at(0), AFB_Mass_ZPt_CF);
 AFBFunction(FZMass_ZPt->at(0), BZMass_ZPt->at(0), AFB_Mass_ZPt_Full);

 AFB_Mass_ZPt_CC->Write();
 AFB_Mass_ZPt_CF->Write();
 AFB_Mass_ZPt_Full->Write();

 AFBSlope_ZPt_CC = new TH1D("AFBSlope_ZPt_CC", "AFBSlope_ZPt_CC", ZPt_CC_bin, RangeZPtCC);
 AFBSlope_ZPt_CF = new TH1D("AFBSlope_ZPt_CF", "AFBSlope_ZPt_CF", ZPt_CF_bin, RangeZPtCF);
 AFBSlope_ZPt_Full = new TH1D("AFBSlope_ZPt_Full", "AFBSlope_ZPt_Full", ZPt_bin, RangeZPt);
 AFBOffset_ZPt_CC = new TH1D("AFBOffset_ZPt_CC", "AFBOffset_ZPt_CC", ZPt_CC_bin, RangeZPtCC);
 AFBOffset_ZPt_CF = new TH1D("AFBOffset_ZPt_CF", "AFBOffset_ZPt_CF", ZPt_CF_bin, RangeZPtCF);
 AFBOffset_ZPt_Full = new TH1D("AFBOffset_ZPt_Full", "AFBOffset_ZPt_Full", ZPt_bin, RangeZPt);

 GetAFBSlopeAndOffset(AFB_Mass_ZPt_CC, AFBSlope_ZPt_CC, AFBOffset_ZPt_CC);
 GetAFBSlopeAndOffset(AFB_Mass_ZPt_CF, AFBSlope_ZPt_CF, AFBOffset_ZPt_CF);
 GetAFBSlopeAndOffset(AFB_Mass_ZPt_Full, AFBSlope_ZPt_Full, AFBOffset_ZPt_Full);

 AFBSlope_ZPt_CC->Write();
 AFBSlope_ZPt_CF->Write();
 AFBSlope_ZPt_Full->Write();
 AFBOffset_ZPt_CC->Write();
 AFBOffset_ZPt_CF->Write();
 AFBOffset_ZPt_Full->Write();
*/
//AFB multibin ZY
/* AFB_Mass_ZY_CC_multi = FZMass_ZY_CC_multi->at(0)->Clone("AFB_Mass_ZY_CC");
 AFB_Mass_ZY_CC_multi->Reset();
 AFB_Mass_ZY_CF_multi = FZMass_ZY_CF_multi->at(0)->Clone("AFB_Mass_ZY_CF");
 AFB_Mass_ZY_CF_multi->Reset();
 AFB_Mass_ZY_Full_multi = FZMass_ZY_multi->at(0)->Clone("AFB_Mass_ZY_Full");
 AFB_Mass_ZY_Full_multi->Reset();

 AFBFunction(FZMass_ZY_CC_multi->at(0), BZMass_ZY_CC_multi->at(0), AFB_Mass_ZY_CC_multi);
 AFBFunction(FZMass_ZY_CF_multi->at(0), BZMass_ZY_CF_multi->at(0), AFB_Mass_ZY_CF_multi);
 AFBFunction(FZMass_ZY_multi->at(0), BZMass_ZY_multi->at(0), AFB_Mass_ZY_Full_multi);

 AFB_Mass_ZY_CC_multi->Write();
 AFB_Mass_ZY_CF_multi->Write();
 AFB_Mass_ZY_Full_multi->Write();


 AFBDiff_Mass_ZY_CC = new TH2D(AFB_Mass_ZY_CC->GetName() + (TString)"_Diff", AFB_Mass_ZY_CC->GetName() + (TString)"_Diff", AFB_Mass_ZY_CC->GetNbinsX() / 2, 1, AFB_Mass_ZY_CC->GetNbinsX() / 2, AFB_Mass_ZY_CC->GetNbinsY(), 1, AFB_Mass_ZY_CC->GetNbinsY());
 AFBDiff_Mass_ZY_CF = new TH2D(AFB_Mass_ZY_CF->GetName() + (TString)"_Diff", AFB_Mass_ZY_CF->GetName() + (TString)"_Diff", AFB_Mass_ZY_CF->GetNbinsX() / 2, 1, AFB_Mass_ZY_CF->GetNbinsX() / 2, AFB_Mass_ZY_CF->GetNbinsY(), 1, AFB_Mass_ZY_CF->GetNbinsY());
 AFBDiff_Mass_ZY_Full = new TH2D(AFB_Mass_ZY_Full->GetName() + (TString)"_Diff", AFB_Mass_ZY_Full->GetName() + (TString)"_Diff", AFB_Mass_ZY_Full->GetNbinsX() / 2, 1, AFB_Mass_ZY_Full->GetNbinsX() / 2, AFB_Mass_ZY_Full->GetNbinsY(), 1, AFB_Mass_ZY_Full->GetNbinsY());

 GetAFBDiff(AFB_Mass_ZY_CC, AFBDiff_Mass_ZY_CC);
 GetAFBDiff(AFB_Mass_ZY_CF, AFBDiff_Mass_ZY_CF);
 GetAFBDiff(AFB_Mass_ZY_Full, AFBDiff_Mass_ZY_Full);

 AFBDiff_Mass_ZY_CC->Write();
 AFBDiff_Mass_ZY_CF->Write();
 AFBDiff_Mass_ZY_Full->Write();

 double xbins[AFB_Mass_ZY_CC_multi->nbin / 2 + 1];
 for(int i = 0; i < AFB_Mass_ZY_CC_multi->nbin / 2 + 1; i++){xbins[i] = i + 1;}
 AFBDiff_Mass_ZY_CC_multi = new MultiBinHist(AFB_Mass_ZY_CC_multi->MultiBinVector);
 AFBDiff_Mass_ZY_CC_multi->DefineHist(AFB_Mass_ZY_CC_multi->name + (TString)"_Diff", AFB_Mass_ZY_CC_multi->name + (TString)"_Diff", AFB_Mass_ZY_CC_multi->nbin / 2, xbins);
 AFBDiff_Mass_ZY_CF_multi = new MultiBinHist(AFB_Mass_ZY_CF_multi->MultiBinVector);
 AFBDiff_Mass_ZY_CF_multi->DefineHist(AFB_Mass_ZY_CF_multi->name + (TString)"_Diff", AFB_Mass_ZY_CF_multi->name + (TString)"_Diff", AFB_Mass_ZY_CF_multi->nbin / 2, xbins);
 AFBDiff_Mass_ZY_Full_multi = new MultiBinHist(AFB_Mass_ZY_Full_multi->MultiBinVector);
 AFBDiff_Mass_ZY_Full_multi->DefineHist(AFB_Mass_ZY_Full_multi->name + (TString)"_Diff", AFB_Mass_ZY_Full_multi->name + (TString)"_Diff", AFB_Mass_ZY_Full_multi->nbin / 2, xbins);

 GetAFBDiff(AFB_Mass_ZY_CC_multi, AFBDiff_Mass_ZY_CC_multi);
 GetAFBDiff(AFB_Mass_ZY_CF_multi, AFBDiff_Mass_ZY_CF_multi);
 GetAFBDiff(AFB_Mass_ZY_Full_multi, AFBDiff_Mass_ZY_Full_multi);

 AFBDiff_Mass_ZY_CC_multi->Write();
 AFBDiff_Mass_ZY_CF_multi->Write();
 AFBDiff_Mass_ZY_Full_multi->Write();
*/

 AverageZPt_ZY = (TH1D *)AverageZPt_ZY_numer->at(0)->Clone("AverageZPt_ZY");
 AverageZPt_ZY->Divide(AverageZPt_ZY_denom->at(0));
 AverageZPt_ZY->Write();

 AverageZPt_lnQ = (TH1D *)AverageZPt_lnQ_numer->at(0)->Clone("AverageZPt_lnQ");
 AverageZPt_lnQ->Divide(AverageZPt_lnQ_denom->at(0));
 AverageZPt_lnQ->Write();

 AverageZY_ZY = (TH1D *)AverageZY_ZY_numer->at(0)->Clone("AverageZY_ZY");
 AverageZY_ZY->Divide(AverageZY_ZY_denom->at(0));
 AverageZY_ZY->Write();

 //Lepton charge asymmetry
 LepAsym = (TH1D *)LepEtaAbs->at(0)->Clone("LepAsym");
 LepAsym->Reset();
 LepAsym_CC = (TH1D *)LepEtaAbs_CC->at(0)->Clone("LepAsym_CC");
 LepAsym_CC->Reset();
 LepAsym_CF = (TH1D *)LepEtaAbs_CF->at(0)->Clone("LepAsym_CF");
 LepAsym_CF->Reset();

 AFBFunction(LepEtaAbs->at(0), AntiLepEtaAbs->at(0), LepAsym);
 AFBFunction(LepEtaAbs_CC->at(0), AntiLepEtaAbs_CC->at(0), LepAsym_CC);
 AFBFunction(LepEtaAbs_CF->at(0), AntiLepEtaAbs_CF->at(0), LepAsym_CF);

 LepAsym->Write();
 LepAsym_CC->Write();
 LepAsym_CF->Write();

 //AFB vs ZY
 AFB_ZY = (TH1D *)FZRapidity->at(0)->Clone("AFB_ZY");
 AFB_ZY->Reset();
 AFB_ZY_LepPtCut = (TH1D *)FZRapidity_LepPtCut->at(0)->Clone("AFB_ZY_LepPtCut");
 AFB_ZY_LepPtCut->Reset();
 AFB_ZY_NoLepPtCut = (TH1D *)FZRapidity_NoLepPtCut->at(0)->Clone("AFB_ZY_NoLepPtCut");
 AFB_ZY_NoLepPtCut->Reset();
 AFB_ZY_CC = (TH1D *)FZRapidity_CC->at(0)->Clone("AFB_ZY_CC");
 AFB_ZY_CC->Reset();
 AFB_ZY_CF = (TH1D *)FZRapidity_CF->at(0)->Clone("AFB_ZY_CF");
 AFB_ZY_CF->Reset();

 AFBFunction(FZRapidity->at(0), BZRapidity->at(0), AFB_ZY);
 AFBFunction(FZRapidity_LepPtCut->at(0), BZRapidity_LepPtCut->at(0), AFB_ZY_LepPtCut);
 AFBFunction(FZRapidity_NoLepPtCut->at(0), BZRapidity_NoLepPtCut->at(0), AFB_ZY_NoLepPtCut);
 AFBFunction(FZRapidity_CC->at(0), BZRapidity_CC->at(0), AFB_ZY_CC);
 AFBFunction(FZRapidity_CF->at(0), BZRapidity_CF->at(0), AFB_ZY_CF);

 AFB_ZY->Write();
 AFB_ZY_LepPtCut->Write();
 AFB_ZY_NoLepPtCut->Write();
 AFB_ZY_CC->Write();
 AFB_ZY_CF->Write();

 //AFB vs ZPt
 AFB_ZPt = (TH1D *)FZPt->at(0)->Clone("AFB_ZPt");
 AFB_ZPt->Reset();
 AFB_ZPt_LepPtCut = (TH1D *)FZPt_LepPtCut->at(0)->Clone("AFB_ZPt_LepPtCut");
 AFB_ZPt_LepPtCut->Reset();
 AFB_ZPt_NoLepPtCut = (TH1D *)FZPt_NoLepPtCut->at(0)->Clone("AFB_ZPt_NoLepPtCut");
 AFB_ZPt_NoLepPtCut->Reset();

 AFBFunction(FZPt->at(0), BZPt->at(0), AFB_ZPt);
 AFBFunction(FZPt_LepPtCut->at(0), BZPt_LepPtCut->at(0), AFB_ZPt_LepPtCut);
 AFBFunction(FZPt_NoLepPtCut->at(0), BZPt_NoLepPtCut->at(0), AFB_ZPt_NoLepPtCut);

 AFB_ZPt->Write();
 AFB_ZPt_LepPtCut->Write();
 AFB_ZPt_NoLepPtCut->Write();

 //Lepton eta width different
 LepWidthDiff = new TH1D("LepWidthDiff", "LepWidthDiff", 1, 0, 1);
 LepWidthDiff_CC = new TH1D("LepWidthDiff_CC", "LepWidthDiff_CC", 1, 0, 1);
 LepWidthDiff_CF = new TH1D("LepWidthDiff_CF", "LepWidthDiff_CF", 1, 0, 1);

 LepWidthDiff->SetBinContent(1, (LepEta->at(0)->GetRMS() - AntiLepEta->at(0)->GetRMS()));
 LepWidthDiff->SetBinError(1, LepEta->at(0)->GetRMSError());
 LepWidthDiff_CC->SetBinContent(1, (LepEta_CC->at(0)->GetRMS() - AntiLepEta_CC->at(0)->GetRMS()));
 LepWidthDiff_CC->SetBinError(1, LepEta_CC->at(0)->GetRMSError());
 LepWidthDiff_CF->SetBinContent(1, (LepEta_CF->at(0)->GetRMS() - AntiLepEta_CF->at(0)->GetRMS()));
 LepWidthDiff_CF->SetBinError(1, LepEta_CF->at(0)->GetRMSError());

 LepWidthDiff->Write();
 LepWidthDiff_CC->Write();
 LepWidthDiff_CF->Write();

 //quark level AFB Gradient
 TH1D *FZmass_CC_qq_1GeV = (TH1D *)FZmass_CC_uu->at(0)->Clone("FZmass_CC_qq_1GeV");
 FZmass_CC_qq_1GeV->Add(FZmass_CC_dd->at(0));
 FZmass_CC_qq_1GeV->Add(FZmass_CC_gg->at(0));
 TH1D *FZmass_CF_qq_1GeV = (TH1D *)FZmass_CF_uu->at(0)->Clone("FZmass_CF_qq_1GeV");
 FZmass_CF_qq_1GeV->Add(FZmass_CF_dd->at(0));
 FZmass_CF_qq_1GeV->Add(FZmass_CF_gg->at(0));
 TH1D *FZmass_qq_1GeV = (TH1D *)FZmass_uu->at(0)->Clone("FZmass_qq_1GeV");
 FZmass_qq_1GeV->Add(FZmass_dd->at(0));
 FZmass_qq_1GeV->Add(FZmass_gg->at(0));
 TH1D *BZmass_CC_qq_1GeV = (TH1D *)BZmass_CC_uu->at(0)->Clone("BZmass_CC_qq_1GeV");
 BZmass_CC_qq_1GeV->Add(BZmass_CC_dd->at(0));
 BZmass_CC_qq_1GeV->Add(BZmass_CC_gg->at(0));
 TH1D *BZmass_CF_qq_1GeV = (TH1D *)BZmass_CF_uu->at(0)->Clone("BZmass_CF_qq_1GeV");
 BZmass_CF_qq_1GeV->Add(BZmass_CF_dd->at(0));
 BZmass_CF_qq_1GeV->Add(BZmass_CF_gg->at(0));
 TH1D *BZmass_qq_1GeV = (TH1D *)BZmass_uu->at(0)->Clone("BZmass_qq_1GeV");
 BZmass_qq_1GeV->Add(BZmass_dd->at(0));
 BZmass_qq_1GeV->Add(BZmass_gg->at(0));

 TH1D *AFBQuark_CC_1GeV = (TH1D *)FZmass_CC_uu->at(0)->Clone("AFB_CC_qq_1GeV");
 AFBQuark_CC_1GeV->Reset();
 TH1D *AFBQuark_CF_1GeV = (TH1D *)FZmass_CF_uu->at(0)->Clone("AFB_CF_qq_1GeV");
 AFBQuark_CF_1GeV->Reset();
 TH1D *AFBQuark_Full_1GeV = (TH1D *)FZmass_uu->at(0)->Clone("AFB_Full_qq_1GeV");
 AFBQuark_Full_1GeV->Reset();

 AFBFunction(FZmass_CC_qq_1GeV, BZmass_CC_qq_1GeV, AFBQuark_CC_1GeV);
 AFBFunction(FZmass_CF_qq_1GeV, BZmass_CF_qq_1GeV, AFBQuark_CF_1GeV);
 AFBFunction(FZmass_qq_1GeV, BZmass_qq_1GeV, AFBQuark_Full_1GeV);

 AFBQuarkGradient_CC = new TH1D("AFBQuarkGradient_CC", "AFBQuarkGradient_CC", 35, 60, 130);
 AFBQuarkGradient_CF = new TH1D("AFBQuarkGradient_CF", "AFBQuarkGradient_CF", 35, 60, 130);
 AFBQuarkGradient_Full = new TH1D("AFBQuarkGradient_Full", "AFBQuarkGradient_Full", 35, 60, 130);

 for(int ibin = 1; ibin < AFBQuarkGradient_CC->GetNbinsX(); ibin++){
   double Diff;
   double DiffError;

   Diff = AFBQuark_CC_1GeV->GetBinContent(2 * ibin) - AFBQuark_CC_1GeV->GetBinContent(2 * ibin - 1);
   DiffError = sqrt(AFBQuark_CC_1GeV->GetBinError(2 * ibin) * AFBQuark_CC_1GeV->GetBinError(2 * ibin) + AFBQuark_CC_1GeV->GetBinError(2 * ibin - 1) * AFBQuark_CC_1GeV->GetBinError(2 * ibin - 1));
   AFBQuarkGradient_CC->SetBinContent(ibin, Diff);
   AFBQuarkGradient_CC->SetBinError(ibin, DiffError);

   Diff = AFBQuark_CF_1GeV->GetBinContent(2 * ibin) - AFBQuark_CF_1GeV->GetBinContent(2 * ibin - 1);
   DiffError = sqrt(AFBQuark_CF_1GeV->GetBinError(2 * ibin) * AFBQuark_CF_1GeV->GetBinError(2 * ibin) + AFBQuark_CF_1GeV->GetBinError(2 * ibin - 1) * AFBQuark_CF_1GeV->GetBinError(2 * ibin - 1));
   AFBQuarkGradient_CF->SetBinContent(ibin, Diff);
   AFBQuarkGradient_CF->SetBinError(ibin, DiffError);

   Diff = AFBQuark_Full_1GeV->GetBinContent(2 * ibin) - AFBQuark_Full_1GeV->GetBinContent(2 * ibin - 1);
   DiffError = sqrt(AFBQuark_Full_1GeV->GetBinError(2 * ibin) * AFBQuark_Full_1GeV->GetBinError(2 * ibin) + AFBQuark_Full_1GeV->GetBinError(2 * ibin - 1) * AFBQuark_Full_1GeV->GetBinError(2 * ibin - 1));
   AFBQuarkGradient_Full->SetBinContent(ibin, Diff);
   AFBQuarkGradient_Full->SetBinError(ibin, DiffError);
 }

 AFBQuarkGradient_CC->Write();
 AFBQuarkGradient_CF->Write();
 AFBQuarkGradient_Full->Write();

 //quark level AFB
 FZmass_CC_uu->at(0)->Rebin(2);
 BZmass_CC_uu->at(0)->Rebin(2);
 FZmass_CF_uu->at(0)->Rebin(2);
 BZmass_CF_uu->at(0)->Rebin(2);
 FZmass_uu->at(0)->Rebin(2);
 BZmass_uu->at(0)->Rebin(2);
 FZmass_CC_dd->at(0)->Rebin(2);
 BZmass_CC_dd->at(0)->Rebin(2);
 FZmass_CF_dd->at(0)->Rebin(2);
 BZmass_CF_dd->at(0)->Rebin(2);
 FZmass_dd->at(0)->Rebin(2);
 BZmass_dd->at(0)->Rebin(2);
 FZmass_CC_gg->at(0)->Rebin(2);
 BZmass_CC_gg->at(0)->Rebin(2);
 FZmass_CF_gg->at(0)->Rebin(2);
 BZmass_CF_gg->at(0)->Rebin(2);
 FZmass_gg->at(0)->Rebin(2);
 BZmass_gg->at(0)->Rebin(2);


 TH1D *FZmass_CC_qq = (TH1D *)FZmass_CC_uu->at(0)->Clone("FZmass_CC_qq");
 FZmass_CC_qq->Add(FZmass_CC_dd->at(0));
 FZmass_CC_qq->Add(FZmass_CC_gg->at(0));
 TH1D *FZmass_CF_qq = (TH1D *)FZmass_CF_uu->at(0)->Clone("FZmass_CF_qq");
 FZmass_CF_qq->Add(FZmass_CF_dd->at(0));
 FZmass_CF_qq->Add(FZmass_CF_gg->at(0));
 TH1D *FZmass_qq = (TH1D *)FZmass_uu->at(0)->Clone("FZmass_qq");
 FZmass_qq->Add(FZmass_dd->at(0));
 FZmass_qq->Add(FZmass_gg->at(0));
 TH1D *BZmass_CC_qq = (TH1D *)BZmass_CC_uu->at(0)->Clone("BZmass_CC_qq");
 BZmass_CC_qq->Add(BZmass_CC_dd->at(0));
 BZmass_CC_qq->Add(BZmass_CC_gg->at(0));
 TH1D *BZmass_CF_qq = (TH1D *)BZmass_CF_uu->at(0)->Clone("BZmass_CF_qq");
 BZmass_CF_qq->Add(BZmass_CF_dd->at(0));
 BZmass_CF_qq->Add(BZmass_CF_gg->at(0));
 TH1D *BZmass_qq = (TH1D *)BZmass_uu->at(0)->Clone("BZmass_qq");
 BZmass_qq->Add(BZmass_dd->at(0));
 BZmass_qq->Add(BZmass_gg->at(0));

 TH1D *FZmass_uudd = (TH1D *)FZmass_uu->at(0)->Clone("FZmass_uudd");
 FZmass_uudd->Add(FZmass_dd->at(0));
 TH1D *BZmass_uudd = (TH1D *)BZmass_uu->at(0)->Clone("BZmass_uudd");
 BZmass_uudd->Add(BZmass_dd->at(0));

 AFB_CC_uu = (TH1D *)FZmass_CC_uu->at(0)->Clone("AFB_CC_uu");
 AFB_CC_uu->Reset();
 AFB_CF_uu = (TH1D *)FZmass_CF_uu->at(0)->Clone("AFB_CF_uu");
 AFB_CF_uu->Reset();
 AFB_Full_uu = (TH1D *)FZmass_uu->at(0)->Clone("AFB_Full_uu");
 AFB_Full_uu->Reset();
 AFB_CC_dd = (TH1D *)FZmass_CC_dd->at(0)->Clone("AFB_CC_dd");
 AFB_CC_dd->Reset();
 AFB_CF_dd = (TH1D *)FZmass_CF_dd->at(0)->Clone("AFB_CF_dd");
 AFB_CF_dd->Reset();
 AFB_Full_dd = (TH1D *)FZmass_dd->at(0)->Clone("AFB_Full_dd");
 AFB_Full_dd->Reset();
 AFB_CC_qq = (TH1D *)FZmass_CC_qq->Clone("AFB_CC_qq");
 AFB_CC_qq->Reset();
 AFB_CF_qq = (TH1D *)FZmass_CF_qq->Clone("AFB_CF_qq");
 AFB_CF_qq->Reset();
 AFB_Full_qq = (TH1D *)FZmass_qq->Clone("AFB_Full_qq");
 AFB_Full_qq->Reset();
 AFB_Full_uudd = (TH1D *)FZmass_uudd->Clone("AFB_Full_uudd");
 AFB_Full_uudd->Reset();
 AFB_Full_gluon = (TH1D *)FZmass_gg->at(0)->Clone("AFB_Full_gluon");
 AFB_Full_gluon->Reset();


 if(FZmass_CC_uu->at(0)->GetEntries() != 0){
   AFBFunction(FZmass_CC_uu->at(0), BZmass_CC_uu->at(0), AFB_CC_uu);
   AFBFunction(FZmass_CF_uu->at(0), BZmass_CF_uu->at(0), AFB_CF_uu);
   AFBFunction(FZmass_uu->at(0), BZmass_uu->at(0), AFB_Full_uu);

   AFBFunction(FZmass_CC_dd->at(0), BZmass_CC_dd->at(0), AFB_CC_dd);
   AFBFunction(FZmass_CF_dd->at(0), BZmass_CF_dd->at(0), AFB_CF_dd);
   AFBFunction(FZmass_dd->at(0), BZmass_dd->at(0), AFB_Full_dd);

   AFBFunction(FZmass_CC_qq, BZmass_CC_qq, AFB_CC_qq);
   AFBFunction(FZmass_CF_qq, BZmass_CF_qq, AFB_CF_qq);
   AFBFunction(FZmass_qq, BZmass_qq, AFB_Full_qq);

   AFBFunction(FZmass_uudd, BZmass_uudd, AFB_Full_uudd);
   AFBFunction(FZmass_gg->at(0), BZmass_gg->at(0), AFB_Full_gluon);

 }

 FZmass_CC_qq->Write();
 BZmass_CC_qq->Write();
 FZmass_CF_qq->Write();
 BZmass_CF_qq->Write();
 FZmass_qq->Write();
 BZmass_qq->Write();

 AFB_CC_uu->Write();
 AFB_CF_uu->Write();
 AFB_Full_uu->Write();
 AFB_CC_dd->Write();
 AFB_CF_dd->Write();
 AFB_Full_dd->Write();
 AFB_CC_qq->Write();
 AFB_CF_qq->Write();
 AFB_Full_qq->Write();
 AFB_Full_uudd->Write();
 AFB_Full_gluon->Write();

 TH1D *FZmass_CC_qq_60_120 = (TH1D *)FZmass_CC_qq->Rebin(30, "FZmass_CC_qq_60_120", xbins2);
 TH1D *BZmass_CC_qq_60_120 = (TH1D *)BZmass_CC_qq->Rebin(30, "BZmass_CC_qq_60_120", xbins2);
 TH1D *FZmass_CF_qq_60_120 = (TH1D *)FZmass_CF_qq->Rebin(30, "FZmass_CF_qq_60_120", xbins2);
 TH1D *BZmass_CF_qq_60_120 = (TH1D *)BZmass_CF_qq->Rebin(30, "BZmass_CF_qq_60_120", xbins2);
 TH1D *FZmass_qq_60_120 = (TH1D *)FZmass_qq->Rebin(30, "FZmass_qq_60_120", xbins2);
 TH1D *BZmass_qq_60_120 = (TH1D *)BZmass_qq->Rebin(30, "BZmass_qq_60_120", xbins2);

 TH1D *FZmass_CC_uu_60_120 = (TH1D *)FZmass_CC_uu->at(0)->Rebin(30, "FZmass_CC_uu_60_120", xbins2);
 TH1D *BZmass_CC_uu_60_120 = (TH1D *)BZmass_CC_uu->at(0)->Rebin(30, "BZmass_CC_uu_60_120", xbins2);
 TH1D *FZmass_CF_uu_60_120 = (TH1D *)FZmass_CF_uu->at(0)->Rebin(30, "FZmass_CF_uu_60_120", xbins2);
 TH1D *BZmass_CF_uu_60_120 = (TH1D *)BZmass_CF_uu->at(0)->Rebin(30, "BZmass_CF_uu_60_120", xbins2);
 TH1D *FZmass_uu_60_120 = (TH1D *)FZmass_uu->at(0)->Rebin(30, "FZmass_uu_60_120", xbins2);
 TH1D *BZmass_uu_60_120 = (TH1D *)BZmass_uu->at(0)->Rebin(30, "BZmass_uu_60_120", xbins2);

 TH1D *FZmass_CC_dd_60_120 = (TH1D *)FZmass_CC_dd->at(0)->Rebin(30, "FZmass_CC_dd_60_120", xbins2);
 TH1D *BZmass_CC_dd_60_120 = (TH1D *)BZmass_CC_dd->at(0)->Rebin(30, "BZmass_CC_dd_60_120", xbins2);
 TH1D *FZmass_CF_dd_60_120 = (TH1D *)FZmass_CF_dd->at(0)->Rebin(30, "FZmass_CF_dd_60_120", xbins2);
 TH1D *BZmass_CF_dd_60_120 = (TH1D *)BZmass_CF_dd->at(0)->Rebin(30, "BZmass_CF_dd_60_120", xbins2);
 TH1D *FZmass_dd_60_120 = (TH1D *)FZmass_dd->at(0)->Rebin(30, "FZmass_dd_60_120", xbins2);
 TH1D *BZmass_dd_60_120 = (TH1D *)BZmass_dd->at(0)->Rebin(30, "BZmass_dd_60_120", xbins2);

 TH1D *AFB_CC_qq_60_120 = (TH1D *)FZmass_CC_qq_60_120->Clone("AFB_CC_qq_60_120");
 AFB_CC_qq_60_120->Reset();
 TH1D *AFB_CF_qq_60_120 = (TH1D *)FZmass_CF_qq_60_120->Clone("AFB_CF_qq_60_120");
 AFB_CF_qq_60_120->Reset();
 TH1D *AFB_Full_qq_60_120 = (TH1D *)FZmass_qq_60_120->Clone("AFB_Full_qq_60_120");
 AFB_Full_qq_60_120->Reset();

 TH1D *AFB_CC_uu_60_120 = (TH1D *)FZmass_CC_uu_60_120->Clone("AFB_CC_uu_60_120");
 AFB_CC_uu_60_120->Reset();
 TH1D *AFB_CF_uu_60_120 = (TH1D *)FZmass_CF_uu_60_120->Clone("AFB_CF_uu_60_120");
 AFB_CF_uu_60_120->Reset();
 TH1D *AFB_Full_uu_60_120 = (TH1D *)FZmass_uu_60_120->Clone("AFB_Full_uu_60_120");
 AFB_Full_uu_60_120->Reset();

 TH1D *AFB_CC_dd_60_120 = (TH1D *)FZmass_CC_dd_60_120->Clone("AFB_CC_dd_60_120");
 AFB_CC_dd_60_120->Reset();
 TH1D *AFB_CF_dd_60_120 = (TH1D *)FZmass_CF_dd_60_120->Clone("AFB_CF_dd_60_120");
 AFB_CF_dd_60_120->Reset();
 TH1D *AFB_Full_dd_60_120 = (TH1D *)FZmass_dd_60_120->Clone("AFB_Full_dd_60_120");
 AFB_Full_dd_60_120->Reset();

 AFBFunction(FZmass_CC_qq_60_120, BZmass_CC_qq_60_120, AFB_CC_qq_60_120);
 AFBFunction(FZmass_CF_qq_60_120, BZmass_CF_qq_60_120, AFB_CF_qq_60_120);
 AFBFunction(FZmass_qq_60_120, BZmass_qq_60_120, AFB_Full_qq_60_120);

 AFBFunction(FZmass_CC_uu_60_120, BZmass_CC_uu_60_120, AFB_CC_uu_60_120);
 AFBFunction(FZmass_CF_uu_60_120, BZmass_CF_uu_60_120, AFB_CF_uu_60_120);
 AFBFunction(FZmass_uu_60_120, BZmass_uu_60_120, AFB_Full_uu_60_120);

 AFBFunction(FZmass_CC_dd_60_120, BZmass_CC_dd_60_120, AFB_CC_dd_60_120);
 AFBFunction(FZmass_CF_dd_60_120, BZmass_CF_dd_60_120, AFB_CF_dd_60_120);
 AFBFunction(FZmass_dd_60_120, BZmass_dd_60_120, AFB_Full_dd_60_120);

 AFBQuarkDiff_CC = new TH1D("AFBQuarkDiff_CC", "AFBQuarkDiff_CC", AFB_CC_qq_60_120->GetNbinsX() / 2, 1, AFB_CC_qq_60_120->GetNbinsX() / 2);
 AFBQuarkDiff_CC_ZPole = new TH1D("AFBQuarkDiff_CC_ZPole", "AFBQuarkDiff_CC_ZPole", 5, 1, 5);
 AFBQuarkDiff_CC_Side = new TH1D("AFBQuarkDiff_CC_Side", "AFBQuarkDiff_CC_Side", 10, 1, 10);

 AFBQuarkDiff_CF = new TH1D("AFBQuarkDiff_CF", "AFBQuarkDiff_CF", AFB_CF_qq_60_120->GetNbinsX() / 2, 1, AFB_CF_qq_60_120->GetNbinsX() / 2);
 AFBQuarkDiff_CF_ZPole = new TH1D("AFBQuarkDiff_CF_ZPole", "AFBQuarkDiff_CF_ZPole", 5, 1, 5);
 AFBQuarkDiff_CF_Side = new TH1D("AFBQuarkDiff_CF_Side", "AFBQuarkDiff_CF_Side", 10, 1, 10);

 AFBQuarkDiff_Full = new TH1D("AFBQuarkDiff_Full", "AFBQuarkDiff_Full", AFB_Full_qq_60_120->GetNbinsX() / 2, 1, AFB_Full_qq_60_120->GetNbinsX() / 2);
 AFBQuarkDiff_Full_ZPole = new TH1D("AFBQuarkDiff_Full_ZPole", "AFBQuarkDiff_Full_ZPole", 5, 1, 5);
 AFBQuarkDiff_Full_Side = new TH1D("AFBQuarkDiff_Full_Side", "AFBQuarkDiff_Full_Side", 10, 1, 10);

 GetAFBDiff(AFB_CC_qq_60_120, AFBQuarkDiff_CC, AFBQuarkDiff_CC_ZPole, AFBQuarkDiff_CC_Side);
 GetAFBDiff(AFB_CF_qq_60_120, AFBQuarkDiff_CF, AFBQuarkDiff_CF_ZPole, AFBQuarkDiff_CF_Side);
 GetAFBDiff(AFB_Full_qq_60_120, AFBQuarkDiff_Full, AFBQuarkDiff_Full_ZPole, AFBQuarkDiff_Full_Side);

 AFBQuarkDiff_CC->Write();
 AFBQuarkDiff_CC_ZPole->Write();
 AFBQuarkDiff_CC_Side->Write();

 AFBQuarkDiff_CF->Write();
 AFBQuarkDiff_CF_ZPole->Write();
 AFBQuarkDiff_CF_Side->Write();

 AFBQuarkDiff_Full->Write();
 AFBQuarkDiff_Full_ZPole->Write();
 AFBQuarkDiff_Full_Side->Write();

 //AFBQuarkFraction and AFBS0Fraction
 AFBQuarkFraction_CC = new TH1D("AFBQuarkFraction_CC", "AFBQuarkFraction_CC", AFB_CC_qq_60_120->GetNbinsX() / 2, 1, AFB_CC_qq_60_120->GetNbinsX() / 2);
 AFBQuarkFraction_CF = new TH1D("AFBQuarkFraction_CF", "AFBQuarkFraction_CF", AFB_CF_qq_60_120->GetNbinsX() / 2, 1, AFB_CF_qq_60_120->GetNbinsX() / 2);
 AFBQuarkFraction_Full = new TH1D("AFBQuarkFraction_Full", "AFBQuarkFraction_Full", AFB_Full_qq_60_120->GetNbinsX() / 2, 1, AFB_Full_qq_60_120->GetNbinsX() / 2);

 vector<TH1D *> Xsec_CC = {ZMass_CC_uu->at(0), ZMass_CC_dd->at(0), ZMass_CC_ss->at(0), ZMass_CC_cc->at(0), ZMass_CC_bb->at(0)};
 vector<TH1D *> Xsec_CF = {ZMass_CF_uu->at(0), ZMass_CF_dd->at(0), ZMass_CF_ss->at(0), ZMass_CF_cc->at(0), ZMass_CF_bb->at(0)};
 vector<TH1D *> Xsec_Full = {ZMass_uu->at(0), ZMass_dd->at(0), ZMass_ss->at(0), ZMass_cc->at(0), ZMass_bb->at(0)};

 AFBFraction(AFB_CC_uu_60_120, AFB_CC_dd_60_120, Xsec_CC, AFBQuarkFraction_CC);
 AFBFraction(AFB_CF_uu_60_120, AFB_CF_dd_60_120, Xsec_CF, AFBQuarkFraction_CF);
 AFBFraction(AFB_Full_uu_60_120, AFB_Full_dd_60_120, Xsec_Full, AFBQuarkFraction_Full);

 AFBQuarkFraction_CC->Write();
 AFBQuarkFraction_CF->Write();
 AFBQuarkFraction_Full->Write();

 AFBS0Fraction_CC = new TH1D("AFBS0Fraction_CC", "AFBS0Fraction_CC", AFB_CC_qq_60_120->GetNbinsX() / 2, 1, AFB_CC_qq_60_120->GetNbinsX() / 2);
 AFBS0Fraction_CF = new TH1D("AFBS0Fraction_CF", "AFBS0Fraction_CF", AFB_CF_qq_60_120->GetNbinsX() / 2, 1, AFB_CF_qq_60_120->GetNbinsX() / 2);
 AFBS0Fraction_Full = new TH1D("AFBS0Fraction_Full", "AFBS0Fraction_Full", AFB_Full_qq_60_120->GetNbinsX() / 2, 1, AFB_Full_qq_60_120->GetNbinsX() / 2);

 AFBS0Fraction(AFB_CC_uu_60_120, AFB_CC_dd_60_120, Xsec_CC, AFBS0Fraction_CC);
 AFBS0Fraction(AFB_CF_uu_60_120, AFB_CF_dd_60_120, Xsec_CF, AFBS0Fraction_CF);
 AFBS0Fraction(AFB_Full_uu_60_120, AFB_Full_dd_60_120, Xsec_Full, AFBS0Fraction_Full);

 AFBS0Fraction_CC->Write();
 AFBS0Fraction_CF->Write();
 AFBS0Fraction_Full->Write();

//AFBQuarkFraction and AFBS0Fraction 2D
/*
 TH2D* AFBQuark_Mass_ZY_uu = (TH2D *)FZmass_ZY_uu->at(0)->Clone("AFBQuark_Mass_ZY_Full_uu");
 AFBQuark_Mass_ZY_uu->Reset();
 TH2D* AFBQuark_Mass_ZY_dd = (TH2D *)FZmass_ZY_dd->at(0)->Clone("AFBQuark_Mass_ZY_Full_dd");
 AFBQuark_Mass_ZY_dd->Reset();

 TH2D* AFBQuark_Mass_ZY_CC_uu = (TH2D *)FZmass_ZY_CC_uu->at(0)->Clone("AFBQuark_Mass_ZY_CC_uu");
 AFBQuark_Mass_ZY_CC_uu->Reset();
 TH2D* AFBQuark_Mass_ZY_CC_dd = (TH2D *)FZmass_ZY_CC_dd->at(0)->Clone("AFBQuark_Mass_ZY_CC_dd");
 AFBQuark_Mass_ZY_CC_dd->Reset();

 TH2D* AFBQuark_Mass_ZY_CF_uu = (TH2D *)FZmass_ZY_CF_uu->at(0)->Clone("AFBQuark_Mass_ZY_CF_uu");
 AFBQuark_Mass_ZY_CF_uu->Reset();
 TH2D* AFBQuark_Mass_ZY_CF_dd = (TH2D *)FZmass_ZY_CF_dd->at(0)->Clone("AFBQuark_Mass_ZY_CF_dd");
 AFBQuark_Mass_ZY_CF_dd->Reset();

 AFBFunction(FZmass_ZY_uu->at(0), BZmass_ZY_uu->at(0), AFBQuark_Mass_ZY_uu);
 AFBFunction(FZmass_ZY_dd->at(0), BZmass_ZY_dd->at(0), AFBQuark_Mass_ZY_dd);
 AFBFunction(FZmass_ZY_CC_uu->at(0), BZmass_ZY_CC_uu->at(0), AFBQuark_Mass_ZY_CC_uu);
 AFBFunction(FZmass_ZY_CC_dd->at(0), BZmass_ZY_CC_dd->at(0), AFBQuark_Mass_ZY_CC_dd);
 AFBFunction(FZmass_ZY_CF_uu->at(0), BZmass_ZY_CF_uu->at(0), AFBQuark_Mass_ZY_CF_uu);
 AFBFunction(FZmass_ZY_CF_dd->at(0), BZmass_ZY_CF_dd->at(0), AFBQuark_Mass_ZY_CF_dd);

 vector<TH2D *> Xsec_ZY_CC = {ZMass_ZY_CC_uu->at(0), ZMass_ZY_CC_dd->at(0), ZMass_ZY_CC_ss->at(0), ZMass_ZY_CC_cc->at(0), ZMass_ZY_CC_bb->at(0)};
 vector<TH2D *> Xsec_ZY_CF = {ZMass_ZY_CF_uu->at(0), ZMass_ZY_CF_dd->at(0), ZMass_ZY_CF_ss->at(0), ZMass_ZY_CF_cc->at(0), ZMass_ZY_CF_bb->at(0)};
 vector<TH2D *> Xsec_ZY_Full = {ZMass_ZY_uu->at(0), ZMass_ZY_dd->at(0), ZMass_ZY_ss->at(0), ZMass_ZY_cc->at(0), ZMass_ZY_bb->at(0)};

 AFBS0Fraction_ZY_CC = new TH2D("AFBS0Fraction_ZY_CC", "AFBS0Fraction_ZY_CC", AFBQuark_Mass_ZY_CC_uu->GetNbinsX() / 2, 1, AFBQuark_Mass_ZY_CC_uu->GetNbinsX() / 2, ZY_CC_bin, 1, ZY_CC_bin);
 AFBS0Fraction_ZY_CF = new TH2D("AFBS0Fraction_ZY_CF", "AFBS0Fraction_ZY_CF", AFBQuark_Mass_ZY_CF_uu->GetNbinsX() / 2, 1, AFBQuark_Mass_ZY_CF_uu->GetNbinsX() / 2, ZY_CF_bin, 1, ZY_CF_bin);
 AFBS0Fraction_ZY_Full = new TH2D("AFBS0Fraction_ZY_Full", "AFBS0Fraction_ZY_Full", AFBQuark_Mass_ZY_uu->GetNbinsX() / 2, 1, AFBQuark_Mass_ZY_uu->GetNbinsX() / 2, ZY_bin, 1, ZY_bin);

 AFBS0Fraction(AFBQuark_Mass_ZY_CC_uu, AFBQuark_Mass_ZY_CC_dd, Xsec_ZY_CC, AFBS0Fraction_ZY_CC);
 AFBS0Fraction(AFBQuark_Mass_ZY_CF_uu, AFBQuark_Mass_ZY_CF_dd, Xsec_ZY_CF, AFBS0Fraction_ZY_CF);
 AFBS0Fraction(AFBQuark_Mass_ZY_uu, AFBQuark_Mass_ZY_dd, Xsec_ZY_Full, AFBS0Fraction_ZY_Full);

 AFBS0Fraction_ZY_CC->Write();
 AFBS0Fraction_ZY_CF->Write();
 AFBS0Fraction_ZY_Full->Write();

 TH2D* AFBQuark_Mass_ZPt_uu = (TH2D *)FZmass_ZPt_uu->at(0)->Clone("AFBQuark_Mass_ZPt_Full_uu");
 AFBQuark_Mass_ZPt_uu->Reset();
 TH2D* AFBQuark_Mass_ZPt_dd = (TH2D *)FZmass_ZPt_dd->at(0)->Clone("AFBQuark_Mass_ZPt_Full_dd");
 AFBQuark_Mass_ZPt_dd->Reset();

 TH2D* AFBQuark_Mass_ZPt_CC_uu = (TH2D *)FZmass_ZPt_CC_uu->at(0)->Clone("AFBQuark_Mass_ZPt_CC_uu");
 AFBQuark_Mass_ZPt_CC_uu->Reset();
 TH2D* AFBQuark_Mass_ZPt_CC_dd = (TH2D *)FZmass_ZPt_CC_dd->at(0)->Clone("AFBQuark_Mass_ZPt_CC_dd");
 AFBQuark_Mass_ZPt_CC_dd->Reset();

 TH2D* AFBQuark_Mass_ZPt_CF_uu = (TH2D *)FZmass_ZPt_CF_uu->at(0)->Clone("AFBQuark_Mass_ZPt_CF_uu");
 AFBQuark_Mass_ZPt_CF_uu->Reset();
 TH2D* AFBQuark_Mass_ZPt_CF_dd = (TH2D *)FZmass_ZPt_CF_dd->at(0)->Clone("AFBQuark_Mass_ZPt_CF_dd");
 AFBQuark_Mass_ZPt_CF_dd->Reset();

 AFBFunction(FZmass_ZPt_uu->at(0), BZmass_ZPt_uu->at(0), AFBQuark_Mass_ZPt_uu);
 AFBFunction(FZmass_ZPt_dd->at(0), BZmass_ZPt_dd->at(0), AFBQuark_Mass_ZPt_dd);
 AFBFunction(FZmass_ZPt_CC_uu->at(0), BZmass_ZPt_CC_uu->at(0), AFBQuark_Mass_ZPt_CC_uu);
 AFBFunction(FZmass_ZPt_CC_dd->at(0), BZmass_ZPt_CC_dd->at(0), AFBQuark_Mass_ZPt_CC_dd);
 AFBFunction(FZmass_ZPt_CF_uu->at(0), BZmass_ZPt_CF_uu->at(0), AFBQuark_Mass_ZPt_CF_uu);
 AFBFunction(FZmass_ZPt_CF_dd->at(0), BZmass_ZPt_CF_dd->at(0), AFBQuark_Mass_ZPt_CF_dd);

 vector<TH2D *> Xsec_ZPt_CC = {ZMass_ZPt_CC_uu->at(0), ZMass_ZPt_CC_dd->at(0), ZMass_ZPt_CC_ss->at(0), ZMass_ZPt_CC_cc->at(0), ZMass_ZPt_CC_bb->at(0)};
 vector<TH2D *> Xsec_ZPt_CF = {ZMass_ZPt_CF_uu->at(0), ZMass_ZPt_CF_dd->at(0), ZMass_ZPt_CF_ss->at(0), ZMass_ZPt_CF_cc->at(0), ZMass_ZPt_CF_bb->at(0)};
 vector<TH2D *> Xsec_ZPt_Full = {ZMass_ZPt_uu->at(0), ZMass_ZPt_dd->at(0), ZMass_ZPt_ss->at(0), ZMass_ZPt_cc->at(0), ZMass_ZPt_bb->at(0)};

 AFBS0Fraction_ZPt_CC = new TH2D("AFBS0Fraction_ZPt_CC", "AFBS0Fraction_ZPt_CC", AFBQuark_Mass_ZPt_CC_uu->GetNbinsX() / 2, 1, AFBQuark_Mass_ZPt_CC_uu->GetNbinsX() / 2, ZPt_CC_bin, 1, ZPt_CC_bin);
 AFBS0Fraction_ZPt_CF = new TH2D("AFBS0Fraction_ZPt_CF", "AFBS0Fraction_ZPt_CF", AFBQuark_Mass_ZPt_CF_uu->GetNbinsX() / 2, 1, AFBQuark_Mass_ZPt_CF_uu->GetNbinsX() / 2, ZPt_CF_bin, 1, ZPt_CF_bin);
 AFBS0Fraction_ZPt_Full = new TH2D("AFBS0Fraction_ZPt_Full", "AFBS0Fraction_ZPt_Full", AFBQuark_Mass_ZPt_uu->GetNbinsX() / 2, 1, AFBQuark_Mass_ZPt_uu->GetNbinsX() / 2, ZPt_bin, 1, ZPt_bin);

 AFBS0Fraction(AFBQuark_Mass_ZPt_CC_uu, AFBQuark_Mass_ZPt_CC_dd, Xsec_ZPt_CC, AFBS0Fraction_ZPt_CC);
 AFBS0Fraction(AFBQuark_Mass_ZPt_CF_uu, AFBQuark_Mass_ZPt_CF_dd, Xsec_ZPt_CF, AFBS0Fraction_ZPt_CF);
 AFBS0Fraction(AFBQuark_Mass_ZPt_uu, AFBQuark_Mass_ZPt_dd, Xsec_ZPt_Full, AFBS0Fraction_ZPt_Full);

 AFBS0Fraction_ZPt_CC->Write();
 AFBS0Fraction_ZPt_CF->Write();
 AFBS0Fraction_ZPt_Full->Write();
*/

//quark level AFB vs Mass ZY
/* TH2D *FZmass_ZY_CC_qq = (TH2D *)FZmass_ZY_CC_uu->at(0)->Clone("FZmass_ZY_CC_qq");
 FZmass_ZY_CC_qq->Add(FZmass_ZY_CC_dd->at(0));
 FZmass_ZY_CC_qq->Add(FZmass_ZY_CC_gg->at(0));
 TH2D *BZmass_ZY_CC_qq = (TH2D *)BZmass_ZY_CC_uu->at(0)->Clone("BZmass_ZY_CC_qq");
 BZmass_ZY_CC_qq->Add(BZmass_ZY_CC_dd->at(0));
 BZmass_ZY_CC_qq->Add(BZmass_ZY_CC_gg->at(0));
 TH2D *FZmass_ZY_CF_qq = (TH2D *)FZmass_ZY_CF_uu->at(0)->Clone("FZmass_ZY_CF_qq");
 FZmass_ZY_CF_qq->Add(FZmass_ZY_CF_dd->at(0));
 FZmass_ZY_CF_qq->Add(FZmass_ZY_CF_gg->at(0));
 TH2D *BZmass_ZY_CF_qq = (TH2D *)BZmass_ZY_CF_uu->at(0)->Clone("BZmass_ZY_CF_qq");
 BZmass_ZY_CF_qq->Add(BZmass_ZY_CF_dd->at(0));
 BZmass_ZY_CF_qq->Add(BZmass_ZY_CF_gg->at(0));
 TH2D *FZmass_ZY_qq = (TH2D *)FZmass_ZY_uu->at(0)->Clone("FZmass_ZY_Full_qq");
 FZmass_ZY_qq->Add(FZmass_ZY_dd->at(0));
 FZmass_ZY_qq->Add(FZmass_ZY_gg->at(0));
 TH2D *BZmass_ZY_qq = (TH2D *)BZmass_ZY_uu->at(0)->Clone("BZmass_ZY_Full_qq");
 BZmass_ZY_qq->Add(BZmass_ZY_dd->at(0));
 BZmass_ZY_qq->Add(BZmass_ZY_gg->at(0));

 AFBQuark_Mass_ZY_CC = (TH2D *)FZmass_ZY_CC_uu->at(0)->Clone("AFBQuark_Mass_ZY_CC");
 AFBQuark_Mass_ZY_CC->Reset();
 AFBQuark_Mass_ZY_CF = (TH2D *)FZmass_ZY_CF_uu->at(0)->Clone("AFBQuark_Mass_ZY_CF");
 AFBQuark_Mass_ZY_CF->Reset();
 AFBQuark_Mass_ZY_Full = (TH2D *)FZmass_ZY_uu->at(0)->Clone("AFBQuark_Mass_ZY_Full");
 AFBQuark_Mass_ZY_Full->Reset();

 AFBFunction(FZmass_ZY_CC_qq, BZmass_ZY_CC_qq, AFBQuark_Mass_ZY_CC);
 AFBFunction(FZmass_ZY_CF_qq, BZmass_ZY_CF_qq, AFBQuark_Mass_ZY_CF);
 AFBFunction(FZmass_ZY_qq, BZmass_ZY_qq, AFBQuark_Mass_ZY_Full);

 AFBQuark_Mass_ZY_CC->Write();
 AFBQuark_Mass_ZY_CF->Write();
 AFBQuark_Mass_ZY_Full->Write();

 AFBQuarkSlope_ZY_CC = new TH1D("AFBQuarkSlope_ZY_CC", "AFBQuarkSlope_ZY_CC", ZY_CC_bin, rangeZYCC);
 AFBQuarkSlope_ZY_CF = new TH1D("AFBQuarkSlope_ZY_CF", "AFBQuarkSlope_ZY_CF", ZY_CF_bin, rangeZYCF);
 AFBQuarkSlope_ZY_Full = new TH1D("AFBQuarkSlope_ZY_Full", "AFBQuarkSlope_ZY_Full", ZY_bin, rangeZY);
 AFBQuarkOffset_ZY_CC = new TH1D("AFBQuarkOffset_ZY_CC", "AFBQuarkOffset_ZY_CC", ZY_CC_bin, rangeZYCC);
 AFBQuarkOffset_ZY_CF = new TH1D("AFBQuarkOffset_ZY_CF", "AFBQuarkOffset_ZY_CF", ZY_CF_bin, rangeZYCF);
 AFBQuarkOffset_ZY_Full = new TH1D("AFBQuarkOffset_ZY_Full", "AFBQuarkOffset_ZY_Full", ZY_bin, rangeZY);

 GetAFBSlopeAndOffset(AFBQuark_Mass_ZY_CC, AFBQuarkSlope_ZY_CC, AFBQuarkOffset_ZY_CC);
 GetAFBSlopeAndOffset(AFBQuark_Mass_ZY_CF, AFBQuarkSlope_ZY_CF, AFBQuarkOffset_ZY_CF);
 GetAFBSlopeAndOffset(AFBQuark_Mass_ZY_Full, AFBQuarkSlope_ZY_Full, AFBQuarkOffset_ZY_Full);

 AFBQuarkSlope_ZY_CC->Write();
 AFBQuarkSlope_ZY_CF->Write();
 AFBQuarkSlope_ZY_Full->Write();
 AFBQuarkOffset_ZY_CC->Write();
 AFBQuarkOffset_ZY_CF->Write();
 AFBQuarkOffset_ZY_Full->Write();
*/
//quark level AFB vs Mass ZPt
/* TH2D *FZmass_ZPt_CC_qq = (TH2D *)FZmass_ZPt_CC_uu->at(0)->Clone("FZmass_ZPt_CC_qq");
 FZmass_ZPt_CC_qq->Add(FZmass_ZPt_CC_dd->at(0));
 FZmass_ZPt_CC_qq->Add(FZmass_ZPt_CC_gg->at(0));
 TH2D *BZmass_ZPt_CC_qq = (TH2D *)BZmass_ZPt_CC_uu->at(0)->Clone("BZmass_ZPt_CC_qq");
 BZmass_ZPt_CC_qq->Add(BZmass_ZPt_CC_dd->at(0));
 BZmass_ZPt_CC_qq->Add(BZmass_ZPt_CC_gg->at(0));
 TH2D *FZmass_ZPt_CF_qq = (TH2D *)FZmass_ZPt_CF_uu->at(0)->Clone("FZmass_ZPt_CF_qq");
 FZmass_ZPt_CF_qq->Add(FZmass_ZPt_CF_dd->at(0));
 FZmass_ZPt_CF_qq->Add(FZmass_ZPt_CF_gg->at(0));
 TH2D *BZmass_ZPt_CF_qq = (TH2D *)BZmass_ZPt_CF_uu->at(0)->Clone("BZmass_ZPt_CF_qq");
 BZmass_ZPt_CF_qq->Add(BZmass_ZPt_CF_dd->at(0));
 BZmass_ZPt_CF_qq->Add(BZmass_ZPt_CF_gg->at(0));
 TH2D *FZmass_ZPt_qq = (TH2D *)FZmass_ZPt_uu->at(0)->Clone("FZmass_ZPt_Full_qq");
 FZmass_ZPt_qq->Add(FZmass_ZPt_dd->at(0));
 FZmass_ZPt_qq->Add(FZmass_ZPt_gg->at(0));
 TH2D *BZmass_ZPt_qq = (TH2D *)BZmass_ZPt_uu->at(0)->Clone("BZmass_ZPt_Full_qq");
 BZmass_ZPt_qq->Add(BZmass_ZPt_dd->at(0));
 BZmass_ZPt_qq->Add(BZmass_ZPt_gg->at(0));

 AFBQuark_Mass_ZPt_CC = (TH2D *)FZmass_ZPt_CC_uu->at(0)->Clone("AFBQuark_Mass_ZPt_CC");
 AFBQuark_Mass_ZPt_CC->Reset();
 AFBQuark_Mass_ZPt_CF = (TH2D *)FZmass_ZPt_CF_uu->at(0)->Clone("AFBQuark_Mass_ZPt_CF");
 AFBQuark_Mass_ZPt_CF->Reset();
 AFBQuark_Mass_ZPt_Full = (TH2D *)FZmass_ZPt_uu->at(0)->Clone("AFBQuark_Mass_ZPt_Full");
 AFBQuark_Mass_ZPt_Full->Reset();

 AFBFunction(FZmass_ZPt_CC_qq, BZmass_ZPt_CC_qq, AFBQuark_Mass_ZPt_CC);
 AFBFunction(FZmass_ZPt_CF_qq, BZmass_ZPt_CF_qq, AFBQuark_Mass_ZPt_CF);
 AFBFunction(FZmass_ZPt_qq, BZmass_ZPt_qq, AFBQuark_Mass_ZPt_Full);

 AFBQuark_Mass_ZPt_CC->Write();
 AFBQuark_Mass_ZPt_CF->Write();
 AFBQuark_Mass_ZPt_Full->Write();
*/

 AFB_Mass_ZPt_Full_uu = (TH2D *)FZmass_ZPt_uu->at(0)->Clone("AFB_Mass_ZPt_uu");
 AFB_Mass_ZPt_Full_uu->Reset();
 AFB_Mass_ZPt_Full_dd = (TH2D *)FZmass_ZPt_dd->at(0)->Clone("AFB_Mass_ZPt_dd");
 AFB_Mass_ZPt_Full_dd->Reset();

 AFBFunction(FZmass_ZPt_uu->at(0), BZmass_ZPt_uu->at(0), AFB_Mass_ZPt_Full_uu);
 AFBFunction(FZmass_ZPt_dd->at(0), BZmass_ZPt_dd->at(0), AFB_Mass_ZPt_Full_dd);

 AFB_Mass_ZPt_Full_uu->Write();
 AFB_Mass_ZPt_Full_dd->Write();

/*
 AFBQuarkSlope_ZPt_CC = new TH1D("AFBQuarkSlope_ZPt_CC", "AFBQuarkSlope_ZPt_CC", ZPt_CC_bin, RangeZPtCC);
 AFBQuarkSlope_ZPt_CF = new TH1D("AFBQuarkSlope_ZPt_CF", "AFBQuarkSlope_ZPt_CF", ZPt_CF_bin, RangeZPtCF);
 AFBQuarkSlope_ZPt_Full = new TH1D("AFBQuarkSlope_ZPt_Full", "AFBQuarkSlope_ZPt_Full", ZPt_bin, RangeZPt);
 AFBQuarkOffset_ZPt_CC = new TH1D("AFBQuarkOffset_ZPt_CC", "AFBQuarkOffset_ZPt_CC", ZPt_CC_bin, RangeZPtCC);
 AFBQuarkOffset_ZPt_CF = new TH1D("AFBQuarkOffset_ZPt_CF", "AFBQuarkOffset_ZPt_CF", ZPt_CF_bin, RangeZPtCF);
 AFBQuarkOffset_ZPt_Full = new TH1D("AFBQuarkOffset_ZPt_Full", "AFBQuarkOffset_ZPt_Full", ZPt_bin, RangeZPt);

 GetAFBSlopeAndOffset(AFBQuark_Mass_ZPt_CC, AFBQuarkSlope_ZPt_CC, AFBQuarkOffset_ZPt_CC);
 GetAFBSlopeAndOffset(AFBQuark_Mass_ZPt_CF, AFBQuarkSlope_ZPt_CF, AFBQuarkOffset_ZPt_CF);
 GetAFBSlopeAndOffset(AFBQuark_Mass_ZPt_Full, AFBQuarkSlope_ZPt_Full, AFBQuarkOffset_ZPt_Full);

 AFBQuarkSlope_ZPt_CC->Write();
 AFBQuarkSlope_ZPt_CF->Write();
 AFBQuarkSlope_ZPt_Full->Write();
 AFBQuarkOffset_ZPt_CC->Write();
 AFBQuarkOffset_ZPt_CF->Write();
 AFBQuarkOffset_ZPt_Full->Write();
*/
 //AFBQuark Slope
 TH1D *FZmass_CC_qq_80_100 = (TH1D *)FZmass_CC_qq->Rebin(10, "FZmass_CC_qq_80_100", xbins1);
 TH1D *BZmass_CC_qq_80_100 = (TH1D *)BZmass_CC_qq->Rebin(10, "BZmass_CC_qq_80_100", xbins1);
 TH1D *FZmass_CF_qq_80_100 = (TH1D *)FZmass_CF_qq->Rebin(10, "FZmass_CF_qq_80_100", xbins1);
 TH1D *BZmass_CF_qq_80_100 = (TH1D *)BZmass_CF_qq->Rebin(10, "BZmass_CF_qq_80_100", xbins1);
 TH1D *FZmass_qq_80_100 = (TH1D *)FZmass_qq->Rebin(10, "FZmass_qq_80_100", xbins1);
 TH1D *BZmass_qq_80_100 = (TH1D *)BZmass_qq->Rebin(10, "BZmass_qq_80_100", xbins1);

 TH1D *FZmass_CC_qq_82_98 = (TH1D *)FZmass_CC_qq->Rebin(8, "FZmass_CC_qq_82_98", xbins3);
 TH1D *BZmass_CC_qq_82_98 = (TH1D *)BZmass_CC_qq->Rebin(8, "BZmass_CC_qq_82_98", xbins3);
 TH1D *FZmass_CF_qq_82_98 = (TH1D *)FZmass_CF_qq->Rebin(8, "FZmass_CF_qq_82_98", xbins3);
 TH1D *BZmass_CF_qq_82_98 = (TH1D *)BZmass_CF_qq->Rebin(8, "BZmass_CF_qq_82_98", xbins3);
 TH1D *FZmass_qq_82_98 = (TH1D *)FZmass_qq->Rebin(8, "FZmass_qq_82_98", xbins3);
 TH1D *BZmass_qq_82_98 = (TH1D *)BZmass_qq->Rebin(8, "BZmass_qq_82_98", xbins3);

 TH1D *FZmass_CC_qq_84_96 = (TH1D *)FZmass_CC_qq->Rebin(6, "FZmass_CC_qq_84_96", xbins4);
 TH1D *BZmass_CC_qq_84_96 = (TH1D *)BZmass_CC_qq->Rebin(6, "BZmass_CC_qq_84_96", xbins4);
 TH1D *FZmass_CF_qq_84_96 = (TH1D *)FZmass_CF_qq->Rebin(6, "FZmass_CF_qq_84_96", xbins4);
 TH1D *BZmass_CF_qq_84_96 = (TH1D *)BZmass_CF_qq->Rebin(6, "BZmass_CF_qq_84_96", xbins4);
 TH1D *FZmass_qq_84_96 = (TH1D *)FZmass_qq->Rebin(6, "FZmass_qq_84_96", xbins4);
 TH1D *BZmass_qq_84_96 = (TH1D *)BZmass_qq->Rebin(6, "BZmass_qq_84_96", xbins4);

 TH1D *FZmass_CC_qq_Average = (TH1D *)FZmass_CC_qq->Rebin(1, "FZmass_CC_qq_Average", xbins5);
 TH1D *BZmass_CC_qq_Average = (TH1D *)BZmass_CC_qq->Rebin(1, "BZmass_CC_qq_Average", xbins5);
 TH1D *FZmass_CF_qq_Average = (TH1D *)FZmass_CF_qq->Rebin(1, "FZmass_CF_qq_Average", xbins5);
 TH1D *BZmass_CF_qq_Average = (TH1D *)BZmass_CF_qq->Rebin(1, "BZmass_CF_qq_Average", xbins5);
 TH1D *FZmass_qq_Average = (TH1D *)FZmass_qq->Rebin(1, "FZmass_qq_Average", xbins5);
 TH1D *BZmass_qq_Average = (TH1D *)BZmass_qq->Rebin(1, "BZmass_qq_Average", xbins5);
 TH1D *FZmass_uudd_Average = (TH1D *)FZmass_uudd->Rebin(1, "FZmass_uudd_Average", xbins5);
 TH1D *BZmass_uudd_Average = (TH1D *)BZmass_uudd->Rebin(1, "BZmass_uudd_Average", xbins5);
 TH1D *FZmass_gluon_Average = (TH1D *)FZmass_gg->at(0)->Rebin(1, "FZmass_gluon_Average", xbins5);
 TH1D *BZmass_gluon_Average = (TH1D *)BZmass_gg->at(0)->Rebin(1, "BZmass_gluon_Average", xbins5);


 TH1D *AFB_CC_qq_80_100 = (TH1D *)FZmass_CC_qq_80_100->Clone("AFB_CC_qq_80_100");
 AFB_CC_qq_80_100->Reset();
 TH1D *AFB_CF_qq_80_100 = (TH1D *)FZmass_CF_qq_80_100->Clone("AFB_CF_qq_80_100");
 AFB_CF_qq_80_100->Reset();
 TH1D *AFB_Full_qq_80_100 = (TH1D *)FZmass_qq_80_100->Clone("AFB_Full_qq_80_100");
 AFB_Full_qq_80_100->Reset();

 TH1D *AFB_CC_qq_82_98 = (TH1D *)FZmass_CC_qq_82_98->Clone("AFB_CC_qq_82_98");
 AFB_CC_qq_82_98->Reset();
 TH1D *AFB_CF_qq_82_98 = (TH1D *)FZmass_CF_qq_82_98->Clone("AFB_CF_qq_82_98");
 AFB_CF_qq_82_98->Reset();
 TH1D *AFB_Full_qq_82_98 = (TH1D *)FZmass_qq_82_98->Clone("AFB_Full_qq_82_98");
 AFB_Full_qq_82_98->Reset();

 TH1D *AFB_CC_qq_84_96 = (TH1D *)FZmass_CC_qq_84_96->Clone("AFB_CC_qq_84_96");
 AFB_CC_qq_84_96->Reset();
 TH1D *AFB_CF_qq_84_96 = (TH1D *)FZmass_CF_qq_84_96->Clone("AFB_CF_qq_84_96");
 AFB_CF_qq_84_96->Reset();
 TH1D *AFB_Full_qq_84_96 = (TH1D *)FZmass_qq_84_96->Clone("AFB_Full_qq_84_96");
 AFB_Full_qq_84_96->Reset();

 QuarkAveAFB_CC = (TH1D *)FZmass_CC_qq_Average->Clone("QuarkAveAFB_CC");
 QuarkAveAFB_CC->Reset();
 QuarkAveAFB_CF = (TH1D *)FZmass_CF_qq_Average->Clone("QuarkAveAFB_CF");
 QuarkAveAFB_CF->Reset();
 QuarkAveAFB_Full = (TH1D *)FZmass_qq_Average->Clone("QuarkAveAFB_Full");
 QuarkAveAFB_Full->Reset();
 QuarkAveAFB_Full_uudd = (TH1D *)FZmass_uudd_Average->Clone("QuarkAveAFB_Full_uudd");
 QuarkAveAFB_Full_uudd->Reset();
 QuarkAveAFB_Full_gluon = (TH1D *)FZmass_gluon_Average->Clone("QuarkAveAFB_Full_gluon");
 QuarkAveAFB_Full_gluon->Reset();

 AFBFunction(FZmass_CC_qq_80_100, BZmass_CC_qq_80_100, AFB_CC_qq_80_100);
 AFBFunction(FZmass_CF_qq_80_100, BZmass_CF_qq_80_100, AFB_CF_qq_80_100);
 AFBFunction(FZmass_qq_80_100, BZmass_qq_80_100, AFB_Full_qq_80_100);

 AFBFunction(FZmass_CC_qq_82_98, BZmass_CC_qq_82_98, AFB_CC_qq_82_98);
 AFBFunction(FZmass_CF_qq_82_98, BZmass_CF_qq_82_98, AFB_CF_qq_82_98);
 AFBFunction(FZmass_qq_82_98, BZmass_qq_82_98, AFB_Full_qq_82_98);

 AFBFunction(FZmass_CC_qq_84_96, BZmass_CC_qq_84_96, AFB_CC_qq_84_96);
 AFBFunction(FZmass_CF_qq_84_96, BZmass_CF_qq_84_96, AFB_CF_qq_84_96);
 AFBFunction(FZmass_qq_84_96, BZmass_qq_84_96, AFB_Full_qq_84_96);

 AFBFunction(FZmass_CC_qq_Average, BZmass_CC_qq_Average, QuarkAveAFB_CC);
 AFBFunction(FZmass_CF_qq_Average, BZmass_CF_qq_Average, QuarkAveAFB_CF);
 AFBFunction(FZmass_qq_Average, BZmass_qq_Average, QuarkAveAFB_Full);
 AFBFunction(FZmass_uudd_Average, BZmass_uudd_Average, QuarkAveAFB_Full_uudd);
 AFBFunction(FZmass_gluon_Average, BZmass_gluon_Average, QuarkAveAFB_Full_gluon);

 AFBQuarkSlope_CC = new TH1D("AFBQuarkSlope_CC", "AFBQuarkSlope_CC", 1, 80, 100);
 AFBQuarkSlope_CF = new TH1D("AFBQuarkSlope_CF", "AFBQuarkSlope_CF", 1, 80, 100);
 AFBQuarkSlope_Full = new TH1D("AFBQuarkSlope_Full", "AFBQuarkSlope_Full", 1, 80, 100);

 AFBQuarkSlope_82_98_CC = new TH1D("AFBQuarkSlope_82_98_CC", "AFBQuarkSlope_82_98_CC", 1, 82, 98);
 AFBQuarkSlope_82_98_CF = new TH1D("AFBQuarkSlope_82_98_CF", "AFBQuarkSlope_82_98_CF", 1, 82, 98);
 AFBQuarkSlope_82_98_Full = new TH1D("AFBQuarkSlope_82_98_Full", "AFBQuarkSlope_82_98_Full", 1, 82, 98);

 AFBQuarkSlope_84_96_CC = new TH1D("AFBQuarkSlope_84_96_CC", "AFBQuarkSlope_84_96_CC", 1, 84, 96);
 AFBQuarkSlope_84_96_CF = new TH1D("AFBQuarkSlope_84_96_CF", "AFBQuarkSlope_84_96_CF", 1, 84, 96);
 AFBQuarkSlope_84_96_Full = new TH1D("AFBQuarkSlope_84_96_Full", "AFBQuarkSlope_84_96_Full", 1, 84, 96);

 AFBQuarkOffset_CC = new TH1D("AFBQuarkOffset_CC", "AFBQuarkOffset_CC", 1, 80, 100);
 AFBQuarkOffset_CF = new TH1D("AFBQuarkOffset_CF", "AFBQuarkOffset_CF", 1, 80, 100);
 AFBQuarkOffset_Full = new TH1D("AFBQuarkOffset_Full", "AFBQuarkOffset_Full", 1, 80, 100);

 AFBQuarkOffset_82_98_CC = new TH1D("AFBQuarkOffset_82_98_CC", "AFBQuarkOffset_82_98_CC", 1, 82, 98);
 AFBQuarkOffset_82_98_CF = new TH1D("AFBQuarkOffset_82_98_CF", "AFBQuarkOffset_82_98_CF", 1, 82, 98);
 AFBQuarkOffset_82_98_Full = new TH1D("AFBQuarkOffset_82_98_Full", "AFBQuarkOffset_82_98_Full", 1, 82, 98);

 AFBQuarkOffset_84_96_CC = new TH1D("AFBQuarkOffset_84_96_CC", "AFBQuarkOffset_84_96_CC", 1, 84, 96);
 AFBQuarkOffset_84_96_CF = new TH1D("AFBQuarkOffset_84_96_CF", "AFBQuarkOffset_84_96_CF", 1, 84, 96);
 AFBQuarkOffset_84_96_Full = new TH1D("AFBQuarkOffset_84_96_Full", "AFBQuarkOffset_84_96_Full", 1, 84, 96);

 TF1 *Slope_qq_CC;
 TF1 *Slope_qq_CF;
 TF1 *Slope_qq_Full;
 LinearFitting(AFB_CC_qq_80_100, Slope_qq_CC, par, parErr);
 AFBQuarkSlope_CC->SetBinContent(1, par[0]);
 AFBQuarkSlope_CC->SetBinError(1, parErr[0]);
 AFBQuarkOffset_CC->SetBinContent(1, par[1]);
 AFBQuarkOffset_CC->SetBinError(1, parErr[1]);
 LinearFitting(AFB_CF_qq_80_100, Slope_qq_CF, par, parErr);
 AFBQuarkSlope_CF->SetBinContent(1, par[0]);
 AFBQuarkSlope_CF->SetBinError(1, parErr[0]);
 AFBQuarkOffset_CF->SetBinContent(1, par[1]);
 AFBQuarkOffset_CF->SetBinError(1, parErr[1]);
 LinearFitting(AFB_Full_qq_80_100, Slope_qq_Full, par, parErr);
 AFBQuarkSlope_Full->SetBinContent(1, par[0]);
 AFBQuarkSlope_Full->SetBinError(1, parErr[0]);
 AFBQuarkOffset_Full->SetBinContent(1, par[1]);
 AFBQuarkOffset_Full->SetBinError(1, parErr[1]);

 TF1 *Slope_qq_82_98_CC;
 TF1 *Slope_qq_82_98_CF;
 TF1 *Slope_qq_82_98_Full;
 LinearFitting(AFB_CC_qq_82_98, Slope_qq_82_98_CC, par, parErr);
 AFBQuarkSlope_82_98_CC->SetBinContent(1, par[0]);
 AFBQuarkSlope_82_98_CC->SetBinError(1, parErr[0]);
 AFBQuarkOffset_82_98_CC->SetBinContent(1, par[1]);
 AFBQuarkOffset_82_98_CC->SetBinError(1, parErr[1]);
 LinearFitting(AFB_CF_qq_82_98, Slope_qq_82_98_CF, par, parErr);
 AFBQuarkSlope_82_98_CF->SetBinContent(1, par[0]);
 AFBQuarkSlope_82_98_CF->SetBinError(1, parErr[0]);
 AFBQuarkOffset_82_98_CF->SetBinContent(1, par[1]);
 AFBQuarkOffset_82_98_CF->SetBinError(1, parErr[1]);
 LinearFitting(AFB_Full_qq_82_98, Slope_qq_82_98_Full, par, parErr);
 AFBQuarkSlope_82_98_Full->SetBinContent(1, par[0]);
 AFBQuarkSlope_82_98_Full->SetBinError(1, parErr[0]);
 AFBQuarkOffset_82_98_Full->SetBinContent(1, par[1]);
 AFBQuarkOffset_82_98_Full->SetBinError(1, parErr[1]);

 TF1 *Slope_qq_84_96_CC;
 TF1 *Slope_qq_84_96_CF;
 TF1 *Slope_qq_84_96_Full;
 LinearFitting(AFB_CC_qq_84_96, Slope_qq_84_96_CC, par, parErr);
 AFBQuarkSlope_84_96_CC->SetBinContent(1, par[0]);
 AFBQuarkSlope_84_96_CC->SetBinError(1, parErr[0]);
 AFBQuarkOffset_84_96_CC->SetBinContent(1, par[1]);
 AFBQuarkOffset_84_96_CC->SetBinError(1, parErr[1]);
 LinearFitting(AFB_CF_qq_84_96, Slope_qq_84_96_CF, par, parErr);
 AFBQuarkSlope_84_96_CF->SetBinContent(1, par[0]);
 AFBQuarkSlope_84_96_CF->SetBinError(1, parErr[0]);
 AFBQuarkOffset_84_96_CF->SetBinContent(1, par[1]);
 AFBQuarkOffset_84_96_CF->SetBinError(1, parErr[1]);
 LinearFitting(AFB_Full_qq_84_96, Slope_qq_84_96_Full, par, parErr);
 AFBQuarkSlope_84_96_Full->SetBinContent(1, par[0]);
 AFBQuarkSlope_84_96_Full->SetBinError(1, parErr[0]);
 AFBQuarkOffset_84_96_Full->SetBinContent(1, par[1]);
 AFBQuarkOffset_84_96_Full->SetBinError(1, parErr[1]);

 AFBQuarkSlope_CC->Write();
 AFBQuarkSlope_CF->Write();
 AFBQuarkSlope_Full->Write();
 AFBQuarkSlope_82_98_CC->Write();
 AFBQuarkSlope_82_98_CF->Write();
 AFBQuarkSlope_82_98_Full->Write();
 AFBQuarkSlope_84_96_CC->Write();
 AFBQuarkSlope_84_96_CF->Write();
 AFBQuarkSlope_84_96_Full->Write();
 AFBQuarkOffset_CC->Write();
 AFBQuarkOffset_CF->Write();
 AFBQuarkOffset_Full->Write();
 AFBQuarkOffset_82_98_CC->Write();
 AFBQuarkOffset_82_98_CF->Write();
 AFBQuarkOffset_82_98_Full->Write();
 AFBQuarkOffset_84_96_CC->Write();
 AFBQuarkOffset_84_96_CF->Write();
 AFBQuarkOffset_84_96_Full->Write();
 QuarkAveAFB_CC->Write();
 QuarkAveAFB_CF->Write();
 QuarkAveAFB_Full->Write();
 QuarkAveAFB_Full_uudd->Write();
 QuarkAveAFB_Full_gluon->Write();

 //AFB vs ZPt
 AFB_ZPt_uu = (TH1D *)FZPt_uu->at(0)->Clone("AFB_ZPt_uu");
 AFB_ZPt_uu->Reset();
 AFB_ZPt_dd = (TH1D *)FZPt_dd->at(0)->Clone("AFB_ZPt_dd");
 AFB_ZPt_dd->Reset();

 AFBFunction(FZPt_uu->at(0), BZPt_uu->at(0), AFB_ZPt_uu);
 AFBFunction(FZPt_dd->at(0), BZPt_dd->at(0), AFB_ZPt_dd);

 AFB_ZPt_uu->Write();
 AFB_ZPt_dd->Write();

 //Dilution
 Dilution_ZMass_CC = (TH1D *)ZMass_CC_wrong->at(0)->Clone("Dilution_ZMass_CC");
 Dilution_ZMass_CC->Divide(ZMass_CC_total->at(0));
 Dilution_ZMass_CF = (TH1D *)ZMass_CF_wrong->at(0)->Clone("Dilution_ZMass_CF");
 Dilution_ZMass_CF->Divide(ZMass_CF_total->at(0));
 Dilution_ZMass_Full = (TH1D *)ZMass_Full_wrong->at(0)->Clone("Dilution_ZMass_Full");
 Dilution_ZMass_Full->Divide(ZMass_Full_total->at(0));

 Dilution_ZMass_CC->Write();
 Dilution_ZMass_CF->Write();
 Dilution_ZMass_Full->Write();

 Dilution_ZMass_CC_uu = (TH1D *)ZMass_CC_uu_wrong->at(0)->Clone("Dilution_ZMass_CC_uu");
 Dilution_ZMass_CC_uu->Divide(ZMass_CC_uu_total->at(0));
 Dilution_ZMass_CC_dd = (TH1D *)ZMass_CC_dd_wrong->at(0)->Clone("Dilution_ZMass_CC_dd");
 Dilution_ZMass_CC_dd->Divide(ZMass_CC_dd_total->at(0));
 Dilution_ZMass_CF_uu = (TH1D *)ZMass_CF_uu_wrong->at(0)->Clone("Dilution_ZMass_CF_uu");
 Dilution_ZMass_CF_uu->Divide(ZMass_CF_uu_total->at(0));
 Dilution_ZMass_CF_dd = (TH1D *)ZMass_CF_dd_wrong->at(0)->Clone("Dilution_ZMass_CF_dd");
 Dilution_ZMass_CF_dd->Divide(ZMass_CF_dd_total->at(0));
 Dilution_ZMass_Full_uu = (TH1D *)ZMass_Full_uu_wrong->at(0)->Clone("Dilution_ZMass_Full_uu");
 Dilution_ZMass_Full_uu->Divide(ZMass_Full_uu_total->at(0));
 Dilution_ZMass_Full_dd = (TH1D *)ZMass_Full_dd_wrong->at(0)->Clone("Dilution_ZMass_Full_dd");
 Dilution_ZMass_Full_dd->Divide(ZMass_Full_dd_total->at(0));
 Dilution_ZMass_Full_ss = (TH1D *)ZMass_Full_ss_wrong->at(0)->Clone("Dilution_ZMass_Full_ss");
 Dilution_ZMass_Full_ss->Divide(ZMass_Full_ss_total->at(0));
 Dilution_ZMass_Full_cc = (TH1D *)ZMass_Full_cc_wrong->at(0)->Clone("Dilution_ZMass_Full_cc");
 Dilution_ZMass_Full_cc->Divide(ZMass_Full_cc_total->at(0));
 Dilution_ZMass_Full_bb = (TH1D *)ZMass_Full_bb_wrong->at(0)->Clone("Dilution_ZMass_Full_bb");
 Dilution_ZMass_Full_bb->Divide(ZMass_Full_bb_total->at(0));

 Dilution_ZMass_CC_uu->Write();
 Dilution_ZMass_CC_dd->Write();
 Dilution_ZMass_CF_uu->Write();
 Dilution_ZMass_CF_dd->Write();
 Dilution_ZMass_Full_uu->Write();
 Dilution_ZMass_Full_dd->Write();
 Dilution_ZMass_Full_ss->Write();
 Dilution_ZMass_Full_cc->Write();
 Dilution_ZMass_Full_bb->Write();

 Dilution_FZmass_CC_uu = (TH1D *)FZmass_CC_uu_wrong->at(0)->Clone("Dilution_FZMass_CC_uu");
 Dilution_FZmass_CC_uu->Divide(FZmass_CC_uu_total->at(0));
 Dilution_BZmass_CC_uu = (TH1D *)BZmass_CC_uu_wrong->at(0)->Clone("Dilution_BZMass_CC_uu");
 Dilution_BZmass_CC_uu->Divide(BZmass_CC_uu_total->at(0));
 Dilution_FZmass_CC_dd = (TH1D *)FZmass_CC_dd_wrong->at(0)->Clone("Dilution_FZMass_CC_dd");
 Dilution_FZmass_CC_dd->Divide(FZmass_CC_dd_total->at(0));
 Dilution_BZmass_CC_dd = (TH1D *)BZmass_CC_dd_wrong->at(0)->Clone("Dilution_BZMass_CC_dd");
 Dilution_BZmass_CC_dd->Divide(BZmass_CC_dd_total->at(0));
 Dilution_FZmass_CF_uu = (TH1D *)FZmass_CF_uu_wrong->at(0)->Clone("Dilution_FZMass_CF_uu");
 Dilution_FZmass_CF_uu->Divide(FZmass_CF_uu_total->at(0));
 Dilution_BZmass_CF_uu = (TH1D *)BZmass_CF_uu_wrong->at(0)->Clone("Dilution_BZMass_CF_uu");
 Dilution_BZmass_CF_uu->Divide(BZmass_CF_uu_total->at(0));
 Dilution_FZmass_CF_dd = (TH1D *)FZmass_CF_dd_wrong->at(0)->Clone("Dilution_FZMass_CF_dd");
 Dilution_FZmass_CF_dd->Divide(FZmass_CF_dd_total->at(0));
 Dilution_BZmass_CF_dd = (TH1D *)BZmass_CF_dd_wrong->at(0)->Clone("Dilution_BZMass_CF_dd");
 Dilution_BZmass_CF_dd->Divide(BZmass_CF_dd_total->at(0));
 Dilution_FZmass_Full_uu = (TH1D *)FZmass_Full_uu_wrong->at(0)->Clone("Dilution_FZMass_Full_uu");
 Dilution_FZmass_Full_uu->Divide(FZmass_Full_uu_total->at(0));
 Dilution_BZmass_Full_uu = (TH1D *)BZmass_Full_uu_wrong->at(0)->Clone("Dilution_BZMass_Full_uu");
 Dilution_BZmass_Full_uu->Divide(BZmass_Full_uu_total->at(0));
 Dilution_FZmass_Full_dd = (TH1D *)FZmass_Full_dd_wrong->at(0)->Clone("Dilution_FZMass_Full_dd");
 Dilution_FZmass_Full_dd->Divide(FZmass_Full_dd_total->at(0));
 Dilution_BZmass_Full_dd = (TH1D *)BZmass_Full_dd_wrong->at(0)->Clone("Dilution_BZMass_Full_dd");
 Dilution_BZmass_Full_dd->Divide(BZmass_Full_dd_total->at(0));

 Dilution_FZmass_CC_uu->Write();
 Dilution_BZmass_CC_uu->Write();
 Dilution_FZmass_CC_dd->Write();
 Dilution_BZmass_CC_dd->Write();
 Dilution_FZmass_CF_uu->Write();
 Dilution_BZmass_CF_uu->Write();
 Dilution_FZmass_CF_dd->Write();
 Dilution_BZmass_CF_dd->Write();
 Dilution_FZmass_Full_uu->Write();
 Dilution_BZmass_Full_uu->Write();
 Dilution_FZmass_Full_dd->Write();
 Dilution_BZmass_Full_dd->Write();

 Dilution_ZMass_ZY = (TH2D *)ZMass_ZY_wrong->at(0)->Clone("Dilution_ZMass_ZY");
 Dilution_ZMass_ZY->Divide(ZMass_ZY_total->at(0));
 Dilution_ZMass_ZY_CC = (TH2D *)ZMass_ZY_CC_wrong->at(0)->Clone("Dilution_ZMass_ZY_CC");
 Dilution_ZMass_ZY_CC->Divide(ZMass_ZY_CC_total->at(0));
 Dilution_ZMass_ZY_CF = (TH2D *)ZMass_ZY_CF_wrong->at(0)->Clone("Dilution_ZMass_ZY_CF");
 Dilution_ZMass_ZY_CF->Divide(ZMass_ZY_CF_total->at(0));
 Dilution_ZMass_ZY_uu = (TH2D *)ZMass_ZY_uu_wrong->at(0)->Clone("Dilution_ZMass_ZY_uu");
 Dilution_ZMass_ZY_uu->Divide(ZMass_ZY_uu_total->at(0));
 Dilution_ZMass_ZY_CC_uu = (TH2D *)ZMass_ZY_CC_uu_wrong->at(0)->Clone("Dilution_ZMass_ZY_CC_uu");
 Dilution_ZMass_ZY_CC_uu->Divide(ZMass_ZY_CC_uu_total->at(0));
 Dilution_ZMass_ZY_CF_uu = (TH2D *)ZMass_ZY_CF_uu_wrong->at(0)->Clone("Dilution_ZMass_ZY_CF_uu");
 Dilution_ZMass_ZY_CF_uu->Divide(ZMass_ZY_CF_uu_total->at(0));
 Dilution_ZMass_ZY_dd = (TH2D *)ZMass_ZY_dd_wrong->at(0)->Clone("Dilution_ZMass_ZY_dd");
 Dilution_ZMass_ZY_dd->Divide(ZMass_ZY_dd_total->at(0));
 Dilution_ZMass_ZY_CC_dd = (TH2D *)ZMass_ZY_CC_dd_wrong->at(0)->Clone("Dilution_ZMass_ZY_CC_dd");
 Dilution_ZMass_ZY_CC_dd->Divide(ZMass_ZY_CC_dd_total->at(0));
 Dilution_ZMass_ZY_CF_dd = (TH2D *)ZMass_ZY_CF_dd_wrong->at(0)->Clone("Dilution_ZMass_ZY_CF_dd");
 Dilution_ZMass_ZY_CF_dd->Divide(ZMass_ZY_CF_dd_total->at(0));

 Dilution_ZMass_ZY->Write();
 Dilution_ZMass_ZY_CC->Write();
 Dilution_ZMass_ZY_CF->Write();
 Dilution_ZMass_ZY_uu->Write();
 Dilution_ZMass_ZY_CC_uu->Write();
 Dilution_ZMass_ZY_CF_uu->Write();
 Dilution_ZMass_ZY_dd->Write();
 Dilution_ZMass_ZY_CC_dd->Write();
 Dilution_ZMass_ZY_CF_dd->Write();

 Dilution_ZMass_ZPt = (TH2D *)ZMass_ZPt_wrong->at(0)->Clone("Dilution_ZMass_ZPt");
 Dilution_ZMass_ZPt->Divide(ZMass_ZPt_total->at(0));
 Dilution_ZMass_ZPt_CC = (TH2D *)ZMass_ZPt_CC_wrong->at(0)->Clone("Dilution_ZMass_ZPt_CC");
 Dilution_ZMass_ZPt_CC->Divide(ZMass_ZPt_CC_total->at(0));
 Dilution_ZMass_ZPt_CF = (TH2D *)ZMass_ZPt_CF_wrong->at(0)->Clone("Dilution_ZMass_ZPt_CF");
 Dilution_ZMass_ZPt_CF->Divide(ZMass_ZPt_CF_total->at(0));
 Dilution_ZMass_ZPt_uu = (TH2D *)ZMass_ZPt_uu_wrong->at(0)->Clone("Dilution_ZMass_ZPt_uu");
 Dilution_ZMass_ZPt_uu->Divide(ZMass_ZPt_uu_total->at(0));
 Dilution_ZMass_ZPt_CC_uu = (TH2D *)ZMass_ZPt_CC_uu_wrong->at(0)->Clone("Dilution_ZMass_ZPt_CC_uu");
 Dilution_ZMass_ZPt_CC_uu->Divide(ZMass_ZPt_CC_uu_total->at(0));
 Dilution_ZMass_ZPt_CF_uu = (TH2D *)ZMass_ZPt_CF_uu_wrong->at(0)->Clone("Dilution_ZMass_ZPt_CF_uu");
 Dilution_ZMass_ZPt_CF_uu->Divide(ZMass_ZPt_CF_uu_total->at(0));
 Dilution_ZMass_ZPt_dd = (TH2D *)ZMass_ZPt_dd_wrong->at(0)->Clone("Dilution_ZMass_ZPt_dd");
 Dilution_ZMass_ZPt_dd->Divide(ZMass_ZPt_dd_total->at(0));
 Dilution_ZMass_ZPt_CC_dd = (TH2D *)ZMass_ZPt_CC_dd_wrong->at(0)->Clone("Dilution_ZMass_ZPt_CC_dd");
 Dilution_ZMass_ZPt_CC_dd->Divide(ZMass_ZPt_CC_dd_total->at(0));
 Dilution_ZMass_ZPt_CF_dd = (TH2D *)ZMass_ZPt_CF_dd_wrong->at(0)->Clone("Dilution_ZMass_ZPt_CF_dd");
 Dilution_ZMass_ZPt_CF_dd->Divide(ZMass_ZPt_CF_dd_total->at(0));

 Dilution_ZMass_ZPt->Write();
 Dilution_ZMass_ZPt_CC->Write();
 Dilution_ZMass_ZPt_CF->Write();
 Dilution_ZMass_ZPt_uu->Write();
 Dilution_ZMass_ZPt_CC_uu->Write();
 Dilution_ZMass_ZPt_CF_uu->Write();
 Dilution_ZMass_ZPt_dd->Write();
 Dilution_ZMass_ZPt_CC_dd->Write();
 Dilution_ZMass_ZPt_CF_dd->Write();

/* Dilution_ZMass_ZY_multi = ZMass_ZY_wrong_multi->at(0)->Clone("Dilution_ZMass_ZY");
 Dilution_ZMass_ZY_multi->Divide(ZMass_ZY_total_multi->at(0));
 Dilution_ZMass_ZY_CC_multi = ZMass_ZY_CC_wrong_multi->at(0)->Clone("Dilution_ZMass_ZY_CC");
 Dilution_ZMass_ZY_CC_multi->Divide(ZMass_ZY_CC_total_multi->at(0));
 Dilution_ZMass_ZY_CF_multi = ZMass_ZY_CF_wrong_multi->at(0)->Clone("Dilution_ZMass_ZY_CF");
 Dilution_ZMass_ZY_CF_multi->Divide(ZMass_ZY_CF_total_multi->at(0));
 Dilution_ZMass_ZY_uu_multi = ZMass_ZY_uu_wrong_multi->at(0)->Clone("Dilution_ZMass_ZY_uu");
 Dilution_ZMass_ZY_uu_multi->Divide(ZMass_ZY_uu_total_multi->at(0));
 Dilution_ZMass_ZY_CC_uu_multi = ZMass_ZY_CC_uu_wrong_multi->at(0)->Clone("Dilution_ZMass_ZY_CC_uu");
 Dilution_ZMass_ZY_CC_uu_multi->Divide(ZMass_ZY_CC_uu_total_multi->at(0));
 Dilution_ZMass_ZY_CF_uu_multi = ZMass_ZY_CF_uu_wrong_multi->at(0)->Clone("Dilution_ZMass_ZY_CF_uu");
 Dilution_ZMass_ZY_CF_uu_multi->Divide(ZMass_ZY_CF_uu_total_multi->at(0));
 Dilution_ZMass_ZY_dd_multi = ZMass_ZY_dd_wrong_multi->at(0)->Clone("Dilution_ZMass_ZY_dd");
 Dilution_ZMass_ZY_dd_multi->Divide(ZMass_ZY_dd_total_multi->at(0));
 Dilution_ZMass_ZY_CC_dd_multi = ZMass_ZY_CC_dd_wrong_multi->at(0)->Clone("Dilution_ZMass_ZY_CC_dd");
 Dilution_ZMass_ZY_CC_dd_multi->Divide(ZMass_ZY_CC_dd_total_multi->at(0));
 Dilution_ZMass_ZY_CF_dd_multi = ZMass_ZY_CF_dd_wrong_multi->at(0)->Clone("Dilution_ZMass_ZY_CF_dd");
 Dilution_ZMass_ZY_CF_dd_multi->Divide(ZMass_ZY_CF_dd_total_multi->at(0));

 Dilution_ZMass_ZY_multi->Write();
 Dilution_ZMass_ZY_CC_multi->Write();
 Dilution_ZMass_ZY_CF_multi->Write();
 Dilution_ZMass_ZY_uu_multi->Write();
 Dilution_ZMass_ZY_CC_uu_multi->Write();
 Dilution_ZMass_ZY_CF_uu_multi->Write();
 Dilution_ZMass_ZY_dd_multi->Write();
 Dilution_ZMass_ZY_CC_dd_multi->Write();
 Dilution_ZMass_ZY_CF_dd_multi->Write();
*/
 Dilution_FZMass_ZY = (TH2D *)FZMass_ZY_wrong->at(0)->Clone("Dilution_FZMass_ZY");
 Dilution_FZMass_ZY->Divide(FZMass_ZY_total->at(0));
 Dilution_BZMass_ZY = (TH2D *)BZMass_ZY_wrong->at(0)->Clone("Dilution_BZMass_ZY");
 Dilution_BZMass_ZY->Divide(BZMass_ZY_total->at(0));

 Dilution_FZMass_ZY->Write();
 Dilution_BZMass_ZY->Write();

 Dilution_ZMass_ZY_QT = (TH3D *)ZMass_ZY_QT_wrong->at(0)->Clone("Dilution_ZMass_ZY_QT");
 Dilution_ZMass_ZY_QT->Divide(ZMass_ZY_QT_total->at(0));
 Dilution_ZMass_ZY_QT_CC = (TH3D *)ZMass_ZY_QT_CC_wrong->at(0)->Clone("Dilution_ZMass_ZY_QT_CC");
 Dilution_ZMass_ZY_QT_CC->Divide(ZMass_ZY_QT_CC_total->at(0));
 Dilution_ZMass_ZY_QT_CF = (TH3D *)ZMass_ZY_QT_CF_wrong->at(0)->Clone("Dilution_ZMass_ZY_QT_CF");
 Dilution_ZMass_ZY_QT_CF->Divide(ZMass_ZY_QT_CF_total->at(0));

 Dilution_ZMass_ZY_QT->Write();
 Dilution_ZMass_ZY_QT_CC->Write();
 Dilution_ZMass_ZY_QT_CF->Write();

 Dilution_ZPt = (TH1D *)ZPt_wrong->at(0)->Clone("Dilution_ZPt");
 Dilution_ZPt->Divide(ZPt_total->at(0));
 Dilution_ZPt_LepPtCut = (TH1D *)ZPt_LepPtCut_wrong->at(0)->Clone("Dilution_ZPt_LepPtCut");
 Dilution_ZPt_LepPtCut->Divide(ZPt_LepPtCut_total->at(0));
 Dilution_ZPt_NoLepPtCut = (TH1D *)ZPt_NoLepPtCut_wrong->at(0)->Clone("Dilution_ZPt_NoLepPtCut");
 Dilution_ZPt_NoLepPtCut->Divide(ZPt_NoLepPtCut_total->at(0));
 Dilution_ZRapidity = (TH1D *)ZRapidity_wrong->at(0)->Clone("Dilution_ZRapidity");
 Dilution_ZRapidity->Divide(ZRapidity_total->at(0));
 Dilution_ZRapidity_LepPtCut = (TH1D *)ZRapidity_LepPtCut_wrong->at(0)->Clone("Dilution_ZRapidity_LepPtCut");
 Dilution_ZRapidity_LepPtCut->Divide(ZRapidity_LepPtCut_total->at(0));
 Dilution_ZRapidity_NoLepPtCut = (TH1D *)ZRapidity_NoLepPtCut_wrong->at(0)->Clone("Dilution_ZRapidity_NoLepPtCut");
 Dilution_ZRapidity_NoLepPtCut->Divide(ZRapidity_NoLepPtCut_total->at(0));
 Dilution_ZRapidityAbs = (TH1D *)ZRapidityAbs_wrong->at(0)->Clone("Dilution_ZRapidityAbs");
 Dilution_ZRapidityAbs->Divide(ZRapidityAbs_total->at(0));
 Dilution_ZRapidity_uu = (TH1D *)ZRapidity_uu_wrong->at(0)->Clone("Dilution_ZRapidity_uu");
 Dilution_ZRapidity_uu->Divide(ZRapidity_uu_total->at(0));
 Dilution_ZRapidity_dd = (TH1D *)ZRapidity_dd_wrong->at(0)->Clone("Dilution_ZRapidity_dd");
 Dilution_ZRapidity_dd->Divide(ZRapidity_dd_total->at(0));
 Dilution_CosThetaQ = (TH1D *)CosThetaQ_wrong->at(0)->Clone("Dilution_CosThetaQ");
 Dilution_CosThetaQ->Divide(CosThetaQ_total->at(0));

 Dilution_ZPt->Write();
 Dilution_ZPt_LepPtCut->Write();
 Dilution_ZPt_NoLepPtCut->Write();
 Dilution_ZRapidity->Write();
 Dilution_ZRapidity_LepPtCut->Write();
 Dilution_ZRapidity_NoLepPtCut->Write();
 Dilution_ZRapidity_uu->Write();
 Dilution_ZRapidity_dd->Write();
 Dilution_ZRapidityAbs->Write();
 Dilution_CosThetaQ->Write();

 DilutionGradient_CC = (TH1D *)AFBGradient_CC->Clone("DilutionGradient_CC");
 DilutionGradient_CC->Divide(AFBQuarkGradient_CC);
 DilutionGradient_CF = (TH1D *)AFBGradient_CF->Clone("DilutionGradient_CF");
 DilutionGradient_CF->Divide(AFBQuarkGradient_CF);
 DilutionGradient_Full = (TH1D *)AFBGradient_Full->Clone("DilutionGradient_Full");
 DilutionGradient_Full->Divide(AFBQuarkGradient_Full);

 DilutionGradient_CC->Write();
 DilutionGradient_CF->Write();
 DilutionGradient_Full->Write();

 DilutionAFB_CC = (TH1D *)AFB_CC->Clone("DilutionAFB_CC");
 DilutionAFB_CC->Divide(AFB_CC_qq);
 DilutionAFB_CF = (TH1D *)AFB_CF->Clone("DilutionAFB_CF");
 DilutionAFB_CF->Divide(AFB_CF_qq);
 DilutionAFB_Full = (TH1D *)AFB_Full->Clone("DilutionAFB_Full");
 DilutionAFB_Full->Divide(AFB_Full_qq);

 DilutionAFB_CC->Write();
 DilutionAFB_CF->Write();
 DilutionAFB_Full->Write();

/* Dilution_Linear = (TH1D *)AverageZY_ZY->Clone("Dilution_Linear");
 for(int ibin = 1; ibin <= Dilution_Linear->GetNbinsX(); ibin++){
   Dilution_Linear->SetBinContent(ibin, Dilution_k * AverageZY_ZY->GetBinContent(ibin) + Dilution_b);
   Dilution_Linear->SetBinError(ibin, Dilution_k * AverageZY_ZY->GetBinError(ibin));
 }

 Dilution_Linear->Write();
*/
}

void HistsPythia::InitialSysName()
{

}

void HistsPythia::GetPartOfResults()
{
}

void HistsPythia::LinkClass(HistsPythia *hist)
{
 m_HistsPythia = hist;
}

void HistsPythia::InputParameter(double k, double b)
{
 this->Dilution_k = k;
 this->Dilution_b = b;

 cout<<"k: "<<Dilution_k<<" b: "<<Dilution_b<<endl;
}

////////////////////////////////////////
//////////   fitting code   ////////////
////////////////////////////////////////

void DilutionFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 if(!m_HistsPythia->HaveMerged){
   cout<<"ERROR: The histogram has not been merged."<<endl;
   return;
 }

 double Chi2 = 0.0;

 TH1D* h1[2];

 h1[0] = (TH1D *)m_HistsPythia->AverageZY_ZY->Clone("Y");

 for(int ibin = 1; ibin <= h1[0]->GetNbinsX(); ibin++){
   h1[0]->SetBinContent(ibin, par[0] * h1[0]->GetBinContent(ibin) + par[1]);
 }


 Chi2 = CalculateChi2(h1[0], m_HistsPythia->Dilution_ZRapidityAbs);

 f = Chi2;

 if(f < MinChi2) MinChi2 = f;

 cout<<"Min Chi2 = "<<MinChi2<<endl;
}

