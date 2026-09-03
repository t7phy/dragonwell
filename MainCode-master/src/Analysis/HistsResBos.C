#include "Analysis/HistsResBos.h"

using namespace std;

void HistsResBos::bookHists(int TotalThread)
{
 double rangeZPt[24] = {0.0, 2.5, 5,8, 11.4, 14.9, 18.5, 22.0, 25.5, 29.0, 32.6, 36.4, 40.4, 44.9, 50.2, 56.4, 63.9, 73.4, 85.4, 105.0, 132.0, 173.0, 253.0, 600.0};
 double rangeZPt2[44] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.5, 25.0, 27.5, 30.0, 33.0, 36.0, 39.0, 42.0, 45.0, 48.0, 51.0, 54.0, 57.0, 
                      61.0, 65.0, 70.0, 75.0, 80.0, 85.0, 95.0, 105.0, 125.0, 150.0, 175.0, 200.0, 250.0, 300.0, 350.0, 400.0, 470.0, 550.0, 650.0, 900.0};
 double rangePhiEta[37] = {0.0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.051, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 
                      0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 5.0, 10.0};

// double rangeZPt3[21] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 13.0, 16.0, 20.0, 25.0, 30.0, 37.0, 45.0, 55.0, 65.0, 75.0, 85.0, 105.0, 150.0, 200.0, 900.0};
 double rangeZPt3[9] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 13.0, 16.0, 20.0};
 double rangeATLASZY[7] = {0.0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4};

 double rangeEtaAbs[5] = {0, 1, 2, 3, 5};
 double rangeMET[6] = {25, 35, 45, 55, 65, 100};
 double rangePt[6] = {0, 2, 4, 6, 8, 10};
 double rangeE[6] = {0, 200, 400, 600, 800, 1000};

 double rangeZYCC[4] = {0, 1, 2, 2.5};
 double rangeZYCF[5] = {1, 2, 2.5, 3, 4};
 double rangeMassCC[7] = {75, 80, 85, 90, 95, 100, 105};
 double rangeMassCF[5] = {82, 87, 92, 97, 102};

 this->TotalThread = TotalThread;
 TString tail = "";

 int mass_bin = 30;
 double RangeMass[31];
 for(int i = 0; i < 31; i++){RangeMass[i] = 60.0 + i * 2.0;}

 int ZPt_bin = 10; double ZPt_left = 0.0; double ZPt_right = 50.0;
 double RangeZPt[12] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 100.0};

 int ZY_bin = 5; double ZY_left = 0.0; double ZY_right = 5.0;
 double RangeZY[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

// int CMS_mass_bin = 14;
// double RangeCMSMass[15] = {40.0, 50.0, 60.0, 76.0, 86.0, 96.0, 106.0, 120.0, 133.0, 150.0, 171.0, 200.0, 320.0, 500.0, 2000.0};
 int CMS_mass_bin = 12;
 double RangeCMSMass[13] = {40.0, 50.0, 60.0, 76.0, 86.0, 96.0, 106.0, 120.0, 133.0, 150.0, 171.0, 200.0, 320.0};

 int CMS_ZPt_bin = 1;
 double RangeCMSZPt[2] = {0.0, 10000.0};

 int CMS_ZY_bin = 4;
 double RangeCMSZY[5] = {0.0, 1.0, 1.25, 1.5, 2.4};

 BookHist(ZMass, "ZMass", "ZMass", mass_bin, 60, 120);
 BookHist(ZMass_CC, "ZMass_CC", "ZMass_CC", mass_bin, 60, 120);
 BookHist(ZMass_CF, "ZMass_CF", "ZMass_CF", mass_bin, 60, 120);

 BookHist(FZmass, "FZmass", "FZmass", mass_bin, 60, 120);
 BookHist(BZmass, "BZmass", "BZmass", mass_bin, 60, 120);
 BookHist(FZmass_CC, "FZmass_CC", "FZmass_CC", mass_bin, 60, 120);
 BookHist(BZmass_CC, "BZmass_CC", "BZmass_CC", mass_bin, 60, 120);
 BookHist(FZmass_CF, "FZmass_CF", "FZmass_CF", mass_bin, 60, 120);
 BookHist(BZmass_CF, "BZmass_CF", "BZmass_CF", mass_bin, 60, 120);
 BookHist(FZmass_LHCb, "FZmass_LHCb", "FZmass_LHCb", mass_bin, 60, 120);
 BookHist(BZmass_LHCb, "BZmass_LHCb", "BZmass_LHCb", mass_bin, 60, 120);

 BookHist(ZPt, "ZPt", "ZPt", 43, rangeZPt2);
// BookHist(ZPt, "ZPt", "ZPt", 100, 0, 500);
 BookHist(ZRapidity, "ZRapidity", "ZRapidity", 100, 0, 5);
 BookHist(ZE, "ZE", "ZE", 20, 0, 1000);
 Book2DHist(ZYE, "ZYE", "ZYE", 4, rangeEtaAbs, 5, rangeE);

 BookHist(ZRapidity_LHCb, "ZRapidity_LHCb", "ZRapidity_LHCb", 18, 2.0, 4.5);
 BookHist(ZPt_LHCb, "ZPt_LHCb", "ZPt_LHCb", 50, 0.0, 100);
 BookHist(phi_eta_LHCb, "phi_eta_LHCb", "phi_eta_LHCb", 36, rangePhiEta);

 BookHist(ZRapidityAbs, "ZRapidityAbs", "ZRapidityAbs", 50, 0, 5);
 BookHist(ZPzPtBalance, "ZPzPtBalance", "ZPzPtBalance", 1000, 0, 1000);
 BookHist(ZPzPtBalance_CC, "ZPzPtBalance_CC", "ZPzPtBalance_CC", 1000, 0, 1000);
 BookHist(ZPzPtBalance_CF, "ZPzPtBalance_CF", "ZPzPtBalance_CF", 1000, 0, 1000);

 BookHist(CosTheta, "CosTheta", "CosTheta", 20, -1, 1);
 BookHist(CosThetaQ, "CosThetaQ", "CosThetaQ", 20, -1, 1);
 BookHist(CosTheta_q, "CosTheta_q", "CosTheta_q", 20, -1, 1);
 BookHist(CosTheta_h, "CosTheta_h", "CosTheta_h", 20, -1, 1);
 BookHist(ZRapidity_qqbar, "ZRapidity_qqbar", "ZRapidity_qqbar", 20, -5, 5);
 BookHist(ZRapidity_qbarq, "ZRapidity_qbarq", "ZRapidity_qbarq", 20, -5, 5);
 BookHist(CollinsPhi, "phi", "phi", 200, -6.28, 6.28);
 BookHist(plot_phi_eta, "phi_eta", "phi_eta", 36, rangePhiEta);
 BookHist(leptonPt, "leptonPt", "leptonPt", 20, 0, 100);
 BookHist(leptonEta, "leptonEta", "leptonEta", 20, -5, 5);

 BookHist(LepEtaAbs, "LepEtaAbs", "LepEtaAbs", 20, 0, 5);
 BookHist(AntiLepEtaAbs, "AntiLepEtaAbs", "AntiLepEtaAbs", 20, 0, 5);
 BookHist(LepEtaAbs_CC, "LepEtaAbs_CC", "LepEtaAbs_CC", 20, 0, 2.5);
 BookHist(AntiLepEtaAbs_CC, "AntiLepEtaAbs_CC", "AntiLepEtaAbs_CC", 20, 0, 2.5);
 BookHist(LepEtaAbs_CF, "LepEtaAbs_CF", "LepEtaAbs_CF", 20, 0, 5);
 BookHist(AntiLepEtaAbs_CF, "AntiLepEtaAbs_CF", "AntiLepEtaAbs_CF", 20, 0, 5);
 BookHist(LepEtaAbs_LHCb, "LepEtaAbs_LHCb", "LepEtaAbs_LHCb", 20, 2.0, 4.5);
 BookHist(AntiLepEtaAbs_LHCb, "AntiLepEtaAbs_LHCb", "AntiLepEtaAbs_LHCb", 20, 2.0, 4.5);

 BookHist(LepEta, "LepEta", "LepEta", 40, -5, 5);
 BookHist(AntiLepEta, "AntiLepEta", "AntiLepEta", 40, -5, 5);
 BookHist(LepEta_CC, "LepEta_CC", "LepEta_CC", 20, -2.5, 2.5);
 BookHist(AntiLepEta_CC, "AntiLepEta_CC", "AntiLepEta_CC", 20, -2.5, 2.5);
 BookHist(LepEta_CF, "LepEta_CF", "LepEta_CF", 20, -5, 5);
 BookHist(AntiLepEta_CF, "AntiLepEta_CF", "AntiLepEta_CF", 20, -5, 5);
 BookHist(LepEta_LHCb, "LepEta_LHCb", "LepEta_LHCb", 20, -5, 5);
 BookHist(AntiLepEta_LHCb, "AntiLepEta_LHCb", "AntiLepEta_LHCb", 20, -5, 5);
 BookHist(LepEta_HighMass, "LepEta_HighMass", "LepEta_HighMass", 40, -5, 5);
 BookHist(AntiLepEta_HighMass, "AntiLepEta_HighMass", "AntiLepEta_HighMass", 40, -5, 5);
 BookHist(LepEta_ss, "LepEta_ss", "LepEta_ss", 40, -5, 5);
 BookHist(AntiLepEta_ss, "AntiLepEta_ss", "AntiLepEta_ss", 40, -5, 5);
 BookHist(LepEta_uubar, "LepEta_uubar", "LepEta_uubar", 40, -5, 5);
 BookHist(AntiLepEta_uubar, "AntiLepEta_uubar", "AntiLepEta_uubar", 40, -5, 5);
 BookHist(LepEta_ubaru, "LepEta_ubaru", "LepEta_ubaru", 40, -5, 5);
 BookHist(AntiLepEta_ubaru, "AntiLepEta_ubaru", "AntiLepEta_ubaru", 40, -5, 5);
 BookHist(ZRapidity_uubar, "ZRapidity_uubar", "ZRapidity_uubar", 40, -5, 5);
 BookHist(ZRapidity_ubaru, "ZRapidity_ubaru", "ZRapidity_ubaru", 40, -5, 5);

 BookHist(FZRapidity, "FZRapidity", "FZRapidity", 100, 0, 5);
 BookHist(BZRapidity, "BZRapidity", "BZRapidity", 100, 0, 5);
 BookHist(FZRapidity_CC, "FZRapidity_CC", "FZRapidity_CC", 20, 0, 2.5);
 BookHist(BZRapidity_CC, "BZRapidity_CC", "BZRapidity_CC", 20, 0, 2.5);
 BookHist(FZRapidity_CF, "FZRapidity_CF", "FZRapidity_CF", 20, 0, 5);
 BookHist(BZRapidity_CF, "BZRapidity_CF", "BZRapidity_CF", 20, 0, 5);
 BookHist(FZRapidity_LHCb, "FZRapidity_LHCb", "FZRapidity_LHCb", 20, 0, 5);
 BookHist(BZRapidity_LHCb, "BZRapidity_LHCb", "BZRapidity_LHCb", 20, 0, 5);

 Book2DHist(FAveZMass_ZY_QT, "FAveZMass_ZY_QT", "FAveZMass_ZY_QT", ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);
 Book2DHist(BAveZMass_ZY_QT, "BAveZMass_ZY_QT", "BAveZMass_ZY_QT", ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);
 Book3DHist(FZMass_ZY_QT, "FZMass_ZY_QT", "FZMass_ZY_QT", 30, 60, 120, ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);
 Book3DHist(BZMass_ZY_QT, "BZMass_ZY_QT", "BZMass_ZY_QT", 30, 60, 120, ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);
 Book3DHist(CMS_FZMass_ZY_QT, "CMS_FZMass_ZY_QT", "CMS_FZMass_ZY_QT", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(CMS_BZMass_ZY_QT, "CMS_BZMass_ZY_QT", "CMS_BZMass_ZY_QT", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);

 BookHist(AverageZPt_ZY_numer, "AverageZPt_ZY_numer", "AverageZPt_ZY_numer", 20, 0, 5);
 BookHist(AverageZPt_ZY_denom, "AverageZPt_ZY_denom", "AverageZPt_ZY_denom", 20, 0, 5);
 BookHist(AverageZPt_lnQ_numer, "AverageZPt_lnQ_numer", "AverageZPt_lnQ_numer", 20, 4, 5);
 BookHist(AverageZPt_lnQ_denom, "AverageZPt_lnQ_denom", "AverageZPt_lnQ_denom", 20, 4, 5);
 BookHist(AverageLepE_ZY_numer, "AverageLepE_ZY_numer", "AverageLepE_ZY_numer", 20, -5, 5);
 BookHist(AverageLepE_ZY_denom, "AverageLepE_ZY_denom", "AverageLepE_ZY_denom", 20, -5, 5);
 BookHist(AverageAntiLepE_ZY_numer, "AverageAntiLepE_ZY_numer", "AverageAntiLepE_ZY_numer", 20, -5, 5);
 BookHist(AverageAntiLepE_ZY_denom, "AverageAntiLepE_ZY_denom", "AverageAntiLepE_ZY_denom", 20, -5, 5);

 Book2DHist(FZmass_ZPt_uu, "FZmass_ZPt_uu", "FZmass_ZPt_uu", 3, 60, 120, 100, 0, 500);
 Book2DHist(BZmass_ZPt_uu, "BZmass_ZPt_uu", "BZmass_ZPt_uu", 3, 60, 120, 100, 0, 500);
 Book2DHist(FZmass_ZPt_dd, "FZmass_ZPt_dd", "FZmass_ZPt_dd", 3, 60, 120, 100, 0, 500);
 Book2DHist(BZmass_ZPt_dd, "BZmass_ZPt_dd", "BZmass_ZPt_dd", 3, 60, 120, 100, 0, 500);

 BookHist(FZmass_CC_uu, "FZmass_CC_uu", "FZmass_CC_uu", mass_bin, 60, 120);
 BookHist(BZmass_CC_uu, "BZmass_CC_uu", "BZmass_CC_uu", mass_bin, 60, 120);
 BookHist(FZmass_CF_uu, "FZmass_CF_uu", "FZmass_CF_uu", mass_bin, 60, 120);
 BookHist(BZmass_CF_uu, "BZmass_CF_uu", "BZmass_CF_uu", mass_bin, 60, 120);
 BookHist(FZmass_CC_dd, "FZmass_CC_dd", "FZmass_CC_dd", mass_bin, 60, 120);
 BookHist(BZmass_CC_dd, "BZmass_CC_dd", "BZmass_CC_dd", mass_bin, 60, 120);
 BookHist(FZmass_CF_dd, "FZmass_CF_dd", "FZmass_CF_dd", mass_bin, 60, 120);
 BookHist(BZmass_CF_dd, "BZmass_CF_dd", "BZmass_CF_dd", mass_bin, 60, 120);
 BookHist(FZmass_CC_gg, "FZmass_CC_gg", "FZmass_CC_gg", mass_bin, 60, 120);
 BookHist(BZmass_CC_gg, "BZmass_CC_gg", "BZmass_CC_gg", mass_bin, 60, 120);
 BookHist(FZmass_CF_gg, "FZmass_CF_gg", "FZmass_CF_gg", mass_bin, 60, 120);
 BookHist(BZmass_CF_gg, "BZmass_CF_gg", "BZmass_CF_gg", mass_bin, 60, 120);
 BookHist(FZmass_uu, "FZmass_uu", "FZmass_uu", mass_bin, 60, 120);
 BookHist(BZmass_uu, "BZmass_uu", "BZmass_uu", mass_bin, 60, 120);
 BookHist(FZmass_dd, "FZmass_dd", "FZmass_dd", mass_bin, 60, 120);
 BookHist(BZmass_dd, "BZmass_dd", "BZmass_dd", mass_bin, 60, 120);
 BookHist(FZmass_gg, "FZmass_gg", "FZmass_gg", mass_bin, 60, 120);
 BookHist(BZmass_gg, "BZmass_gg", "BZmass_gg", mass_bin, 60, 120);
 BookHist(ZMass_CC_uu, "ZMass_CC_uu", "ZMass_CC_uu", mass_bin, 60, 120);
 BookHist(ZMass_CF_uu, "ZMass_CF_uu", "ZMass_CF_uu", mass_bin, 60, 120);
 BookHist(ZMass_CC_dd, "ZMass_CC_dd", "ZMass_CC_dd", mass_bin, 60, 120);
 BookHist(ZMass_CF_dd, "ZMass_CF_dd", "ZMass_CF_dd", mass_bin, 60, 120);
 BookHist(ZMass_CC_gg, "ZMass_CC_gg", "ZMass_CC_gg", mass_bin, 60, 120);
 BookHist(ZMass_CF_gg, "ZMass_CF_gg", "ZMass_CF_gg", mass_bin, 60, 120);
 BookHist(ZMass_CC_ss, "ZMass_CC_ss", "ZMass_CC_ss", mass_bin, 60, 120);
 BookHist(ZMass_CF_ss, "ZMass_CF_ss", "ZMass_CF_ss", mass_bin, 60, 120);
 BookHist(ZMass_CC_cc, "ZMass_CC_cc", "ZMass_CC_cc", mass_bin, 60, 120);
 BookHist(ZMass_CF_cc, "ZMass_CF_cc", "ZMass_CF_cc", mass_bin, 60, 120);
 BookHist(ZMass_CC_bb, "ZMass_CC_bb", "ZMass_CC_bb", mass_bin, 60, 120);
 BookHist(ZMass_CF_bb, "ZMass_CF_bb", "ZMass_CF_bb", mass_bin, 60, 120);
 BookHist(ZMass_CC_utype, "ZMass_CC_utype", "ZMass_CC_utype", mass_bin, 60, 120);
 BookHist(ZMass_CF_utype, "ZMass_CF_utype", "ZMass_CF_utype", mass_bin, 60, 120);
 BookHist(ZMass_CC_dtype, "ZMass_CC_dtype", "ZMass_CC_dtype", mass_bin, 60, 120);
 BookHist(ZMass_CF_dtype, "ZMass_CF_dtype", "ZMass_CF_dtype", mass_bin, 60, 120);
 BookHist(ZMass_uu, "ZMass_uu", "ZMass_uu", mass_bin, 60, 120);
 BookHist(ZMass_dd, "ZMass_dd", "ZMass_dd", mass_bin, 60, 120);
 BookHist(ZMass_gg, "ZMass_gg", "ZMass_gg", mass_bin, 60, 120);
 BookHist(ZMass_ss, "ZMass_ss", "ZMass_ss", mass_bin, 60, 120);
 BookHist(ZMass_cc, "ZMass_cc", "ZMass_cc", mass_bin, 60, 120);
 BookHist(ZMass_bb, "ZMass_bb", "ZMass_bb", mass_bin, 60, 120);
 BookHist(ZMass_utype, "ZMass_utype", "ZMass_utype", mass_bin, 60, 120);
 BookHist(ZMass_dtype, "ZMass_dtype", "ZMass_dtype", mass_bin, 60, 120);

 BookHist(FZY_uu, "FZY_uu", "FZY_uu", 100, 0, 5);
 BookHist(BZY_uu, "BZY_uu", "BZY_uu", 100, 0, 5);
 BookHist(FZY_dd, "FZY_dd", "FZY_dd", 100, 0, 5);
 BookHist(BZY_dd, "BZY_dd", "BZY_dd", 100, 0, 5);

// BookHist(FZPt_uu, "FZPt_uu", "FZPt_uu", 23, rangeZPt);
// BookHist(BZPt_uu, "BZPt_uu", "BZPt_uu", 23, rangeZPt);
// BookHist(FZPt_dd, "FZPt_dd", "FZPt_dd", 23, rangeZPt);
// BookHist(BZPt_dd, "BZPt_dd", "BZPt_dd", 23, rangeZPt);

 BookHist(FZPt_uu, "FZPt_uu", "FZPt_uu", 100, 0, 500);
 BookHist(BZPt_uu, "BZPt_uu", "BZPt_uu", 100, 0, 500);
 BookHist(FZPt_dd, "FZPt_dd", "FZPt_dd", 100, 0, 500);
 BookHist(BZPt_dd, "BZPt_dd", "BZPt_dd", 100, 0, 500);

 BookHist(ZPt_uub, "ZPt_uub", "ZPt_uub", 50, 0.0, 100.0);
 BookHist(ZMass_uub, "ZMass_uub", "ZMass_uub", 60, 60.0, 120.0);
 BookHist(ZRapidity_uub, "ZRapidity_uub", "ZRapidity_uub", 20, -5.0, 5.0);
 BookHist(ZPt_ddb, "ZPt_ddb", "ZPt_ddb", 50, 0.0, 100.0);
 BookHist(ZMass_ddb, "ZMass_ddb", "ZMass_ddb", 60, 60.0, 120.0);
 BookHist(ZRapidity_ddb, "ZRapidity_ddb", "ZRapidity_ddb", 20, -5.0, 5.0);
 BookHist(ZPt_ssb, "ZPt_ssb", "ZPt_ssb", 50, 0.0, 100.0);
 BookHist(ZMass_ssb, "ZMass_ssb", "ZMass_ssb", 60, 60.0, 120.0);
 BookHist(ZRapidity_ssb, "ZRapidity_ssb", "ZRapidity_ssb", 20, -5.0, 5.0);

 Book3DHist(ZMass_ZY_QT, "ZMass_ZY_QT", "ZMass_ZY_QT", 30, 60, 120, ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);
 Book3DHist(FZMass_ZY_QT_uu, "FZMass_ZY_QT_uu", "FZMass_ZY_QT_uu", 30, 60, 120, ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);
 Book3DHist(BZMass_ZY_QT_uu, "BZMass_ZY_QT_uu", "BZMass_ZY_QT_uu", 30, 60, 120, ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);
 Book3DHist(FZMass_ZY_QT_dd, "FZMass_ZY_QT_dd", "FZMass_ZY_QT_dd", 30, 60, 120, ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);
 Book3DHist(BZMass_ZY_QT_dd, "BZMass_ZY_QT_dd", "BZMass_ZY_QT_dd", 30, 60, 120, ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);
 Book3DHist(ZMass_ZY_QT_uu, "ZMass_ZY_QT_uu", "ZMass_ZY_QT_uu", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(ZMass_ZY_QT_dd, "ZMass_ZY_QT_dd", "ZMass_ZY_QT_dd", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(ZMass_ZY_QT_ss, "ZMass_ZY_QT_ss", "ZMass_ZY_QT_ss", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(ZMass_ZY_QT_cc, "ZMass_ZY_QT_cc", "ZMass_ZY_QT_cc", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(ZMass_ZY_QT_bb, "ZMass_ZY_QT_bb", "ZMass_ZY_QT_bb", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(CMS_ZMass_ZY_QT, "CMS_ZMass_ZY_QT", "CMS_ZMass_ZY_QT", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(CMS_FZMass_ZY_QT_uu, "CMS_FZMass_ZY_QT_uu", "CMS_FZMass_ZY_QT_uu", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(CMS_BZMass_ZY_QT_uu, "CMS_BZMass_ZY_QT_uu", "CMS_BZMass_ZY_QT_uu", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(CMS_FZMass_ZY_QT_dd, "CMS_FZMass_ZY_QT_dd", "CMS_FZMass_ZY_QT_dd", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(CMS_BZMass_ZY_QT_dd, "CMS_BZMass_ZY_QT_dd", "CMS_BZMass_ZY_QT_dd", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);


 BookHist(ZMass_CC_total, "ZMass_CC_total", "ZMass_CC_total", mass_bin, 60, 120);
 BookHist(ZMass_CC_wrong, "ZMass_CC_wrong", "ZMass_CC_wrong", mass_bin, 60, 120);
 BookHist(ZMass_CF_total, "ZMass_CF_total", "ZMass_CF_total", mass_bin, 60, 120);
 BookHist(ZMass_CF_wrong, "ZMass_CF_wrong", "ZMass_CF_wrong", mass_bin, 60, 120);
 BookHist(ZMass_Full_total, "ZMass_Full_total", "ZMass_Full_total", mass_bin, 60, 120);
 BookHist(ZMass_Full_wrong, "ZMass_Full_wrong", "ZMass_Full_wrong", mass_bin, 60, 120);

 BookHist(ZMass_CC_uu_total, "ZMass_CC_uu_total", "ZMass_CC_uu_total", mass_bin, 60, 120);
 BookHist(ZMass_CC_uu_wrong, "ZMass_CC_uu_wrong", "ZMass_CC_uu_wrong", mass_bin, 60, 120);
 BookHist(ZMass_CC_dd_total, "ZMass_CC_dd_total", "ZMass_CC_dd_total", mass_bin, 60, 120);
 BookHist(ZMass_CC_dd_wrong, "ZMass_CC_dd_wrong", "ZMass_CC_dd_wrong", mass_bin, 60, 120);
 BookHist(ZMass_CF_uu_total, "ZMass_CF_uu_total", "ZMass_CF_uu_total", mass_bin, 60, 120);
 BookHist(ZMass_CF_uu_wrong, "ZMass_CF_uu_wrong", "ZMass_CF_uu_wrong", mass_bin, 60, 120);
 BookHist(ZMass_CF_dd_total, "ZMass_CF_dd_total", "ZMass_CF_dd_total", mass_bin, 60, 120);
 BookHist(ZMass_CF_dd_wrong, "ZMass_CF_dd_wrong", "ZMass_CF_dd_wrong", mass_bin, 60, 120);
 BookHist(ZMass_Full_uu_total, "ZMass_Full_uu_total", "ZMass_Full_uu_total", mass_bin, 60, 120);
 BookHist(ZMass_Full_uu_wrong, "ZMass_Full_uu_wrong", "ZMass_Full_uu_wrong", mass_bin, 60, 120);
 BookHist(ZMass_Full_dd_total, "ZMass_Full_dd_total", "ZMass_Full_dd_total", mass_bin, 60, 120);
 BookHist(ZMass_Full_dd_wrong, "ZMass_Full_dd_wrong", "ZMass_Full_dd_wrong", mass_bin, 60, 120);
 BookHist(ZMass_Full_ss_total, "ZMass_Full_ss_total", "ZMass_Full_ss_total", mass_bin, 60, 120);
 BookHist(ZMass_Full_ss_wrong, "ZMass_Full_ss_wrong", "ZMass_Full_ss_wrong", mass_bin, 60, 120);
 BookHist(ZMass_Full_cc_total, "ZMass_Full_cc_total", "ZMass_Full_cc_total", mass_bin, 60, 120);
 BookHist(ZMass_Full_cc_wrong, "ZMass_Full_cc_wrong", "ZMass_Full_cc_wrong", mass_bin, 60, 120);
 BookHist(ZMass_Full_bb_total, "ZMass_Full_bb_total", "ZMass_Full_bb_total", mass_bin, 60, 120);
 BookHist(ZMass_Full_bb_wrong, "ZMass_Full_bb_wrong", "ZMass_Full_bb_wrong", mass_bin, 60, 120);

 BookHist(ZY_uu_wrong, "ZY_uu_wrong", "ZY_uu_wrong", 100, 0, 5);
 BookHist(ZY_uu_total, "ZY_uu_total", "ZY_uu_total", 100, 0, 5);
 BookHist(ZY_dd_wrong, "ZY_dd_wrong", "ZY_dd_wrong", 100, 0, 5);
 BookHist(ZY_dd_total, "ZY_dd_total", "ZY_dd_total", 100, 0, 5);

 BookHist(ZPt_total, "ZPt_total", "ZPt_total", 100, 0, 100);
 BookHist(ZPt_wrong, "ZPt_wrong", "ZPt_wrong", 100, 0, 100);
 BookHist(ZRapidity_total, "ZRapidity_total", "ZRapidity_total", 20, -5, 5);
 BookHist(ZRapidity_wrong, "ZRapidity_wrong", "ZRapidity_wrong", 20, -5, 5);

 Book3DHist(ZMass_ZY_QT_uu_total, "ZMass_ZY_QT_uu_total", "ZMass_ZY_QT_uu_total", 30, 60, 120, ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);
 Book3DHist(ZMass_ZY_QT_uu_wrong, "ZMass_ZY_QT_uu_wrong", "ZMass_ZY_QT_uu_wrong", 30, 60, 120, ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);
 Book3DHist(ZMass_ZY_QT_dd_total, "ZMass_ZY_QT_dd_total", "ZMass_ZY_QT_dd_total", 30, 60, 120, ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);
 Book3DHist(ZMass_ZY_QT_dd_wrong, "ZMass_ZY_QT_dd_wrong", "ZMass_ZY_QT_dd_wrong", 30, 60, 120, ZY_bin, ZY_left, ZY_right, ZPt_bin, ZPt_left, ZPt_right);

 Book3DHist(CMS_ZMass_ZY_QT_uu_total, "CMS_ZMass_ZY_QT_uu_total", "CMS_ZMass_ZY_QT_uu_total", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(CMS_ZMass_ZY_QT_uu_wrong, "CMS_ZMass_ZY_QT_uu_wrong", "CMS_ZMass_ZY_QT_uu_wrong", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(CMS_ZMass_ZY_QT_dd_total, "CMS_ZMass_ZY_QT_dd_total", "CMS_ZMass_ZY_QT_dd_total", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(CMS_ZMass_ZY_QT_dd_wrong, "CMS_ZMass_ZY_QT_dd_wrong", "CMS_ZMass_ZY_QT_dd_wrong", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);

 Book3DHist(XSection_M_Y_CosTheta, "XSection_M_Y_CosTheta", "XSection_M_Y_CosTheta", 14, 60, 130, 20, -5, 5, 4, -1, 1);

 BookHist(ZPt_y1_Total, "ZPt_y1_Total", "ZPt_y1_Total", 8, rangeZPt3);
 BookHist(ZPt_y1_Fiduc, "ZPt_y1_Fiduc", "ZPt_y1_Fiduc", 8, rangeZPt3);
 BookHist(ZPt_y2_Total, "ZPt_y2_Total", "ZPt_y2_Total", 8, rangeZPt3);
 BookHist(ZPt_y2_Fiduc, "ZPt_y2_Fiduc", "ZPt_y2_Fiduc", 8, rangeZPt3);
 BookHist(ZPt_y3_Total, "ZPt_y3_Total", "ZPt_y3_Total", 8, rangeZPt3);
 BookHist(ZPt_y3_Fiduc, "ZPt_y3_Fiduc", "ZPt_y3_Fiduc", 8, rangeZPt3);
 BookHist(ZPt_y4_Total, "ZPt_y4_Total", "ZPt_y4_Total", 8, rangeZPt3);
 BookHist(ZPt_y4_Fiduc, "ZPt_y4_Fiduc", "ZPt_y4_Fiduc", 8, rangeZPt3);
 BookHist(ZPt_y5_Total, "ZPt_y5_Total", "ZPt_y5_Total", 8, rangeZPt3);
 BookHist(ZPt_y5_Fiduc, "ZPt_y5_Fiduc", "ZPt_y5_Fiduc", 8, rangeZPt3);
 BookHist(ZPt_y6_Total, "ZPt_y6_Total", "ZPt_y6_Total", 8, rangeZPt3);
 BookHist(ZPt_y6_Fiduc, "ZPt_y6_Fiduc", "ZPt_y6_Fiduc", 8, rangeZPt3);
 BookHist(ATLASZPt_Fiduc, "ATLASZPt_Fiduc", "ATLASZPt_Fiduc", 8, rangeZPt3);
 BookHist(ATLASZPt_Total, "ATLASZPt_Total", "ATLASZPt_Total", 8, rangeZPt3);
 Book2DHist(ATLASZPt_2D_Fiduc, "ATLASZPt_2D_Fiduc", "ATLASZPt_2D_Fiduc", 8, rangeZPt3, 6, rangeATLASZY);
 Book2DHist(ATLASZPt_2D_Total, "ATLASZPt_2D_Total", "ATLASZPt_2D_Total", 8, rangeZPt3, 6, rangeATLASZY);
 Book2DHist(ATLASZPt_2D_Total_uu, "ATLASZPt_2D_Total_uu", "ATLASZPt_2D_Total_uu", 8, rangeZPt3, 6, rangeATLASZY);
 Book2DHist(ATLASZPt_2D_Total_dd, "ATLASZPt_2D_Total_dd", "ATLASZPt_2D_Total_dd", 8, rangeZPt3, 6, rangeATLASZY);
 Book2DHist(ATLASZPt_2D_Total_MassWindow, "ATLASZPt_2D_Total_MassWindow", "ATLASZPt_2D_Total_MassWindow", 8, rangeZPt3, 6, rangeATLASZY);
 BookHist(ZPt_Threshold, "ZPt_Threshold", "ZPt_Threshold", 1, 0.0, 1.5);

 BookAngularHist(A0_ZPt, "A0_ZPt", "A0", 23, rangeZPt);
 BookAngularHist(A1_ZPt, "A1_ZPt", "A1", 23, rangeZPt);
 BookAngularHist(A2_ZPt, "A2_ZPt", "A2", 23, rangeZPt);
 BookAngularHist(A3_ZPt, "A3_ZPt", "A3", 23, rangeZPt);
 BookAngularHist(A4_ZPt, "A4_ZPt", "A4", 23, rangeZPt);
 BookAngularHist(L0_ZPt, "L0_ZPt", "L0", 23, rangeZPt);

 BookAngularHist(A0_ZPt_LHCb, "A0_ZPt_LHCb", "A0", 23, rangeZPt);
 BookAngularHist(A1_ZPt_LHCb, "A1_ZPt_LHCb", "A1", 23, rangeZPt);
 BookAngularHist(A2_ZPt_LHCb, "A2_ZPt_LHCb", "A2", 23, rangeZPt);
 BookAngularHist(A3_ZPt_LHCb, "A3_ZPt_LHCb", "A3", 23, rangeZPt);
 BookAngularHist(A4_ZPt_LHCb, "A4_ZPt_LHCb", "A4", 23, rangeZPt);
 BookAngularHist(A02_ZPt_LHCb, "A02_ZPt_LHCb", "A02", 23, rangeZPt);

 BookAngularHist(A0_ZY_LHCb, "A0_ZY_LHCb", "A0", 5, 2.5, 5);
 BookAngularHist(A1_ZY_LHCb, "A1_ZY_LHCb", "A1", 5, 2.5, 5);
 BookAngularHist(A2_ZY_LHCb, "A2_ZY_LHCb", "A2", 5, 2.5, 5);
 BookAngularHist(A3_ZY_LHCb, "A3_ZY_LHCb", "A3", 5, 2.5, 5);
 BookAngularHist(A4_ZY_LHCb, "A4_ZY_LHCb", "A4", 5, 2.5, 5);
 BookAngularHist(A02_ZY_LHCb, "A02_ZY_LHCb", "A02", 5, 2.5, 5);

 BookAngularHist(QuarkA4_ZPt_uu, "QuarkA4_ZPt_uu", "A4", 23, rangeZPt);
 BookAngularHist(QuarkA4_ZY_uu, "QuarkA4_ZY_uu", "A4", 10, 0, 5);
 BookAngularHist(QuarkA4_ZPt_dd, "QuarkA4_ZPt_dd", "A4", 23, rangeZPt);
 BookAngularHist(QuarkA4_ZY_dd, "QuarkA4_ZY_dd", "A4", 10, 0, 5);

 BookAngularHist(QuarkL0_ZPt_uu, "QuarkL0_ZPt_uu", "L0", 23, rangeZPt);
 BookAngularHist(QuarkL0_ZY_uu, "QuarkL0_ZY_uu", "L0", 10, 0, 5);
 BookAngularHist(QuarkL0_ZPt_dd, "QuarkL0_ZPt_dd", "L0", 23, rangeZPt);
 BookAngularHist(QuarkL0_ZY_dd, "QuarkL0_ZY_dd", "L0", 10, 0, 5);

 BookAngularHist(A0_Mass_ZY_QT_uu, "A0_Mass_ZY_QT_uu", "A0", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 BookAngularHist(A0_Mass_ZY_QT_dd, "A0_Mass_ZY_QT_dd", "A0", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 BookAngularHist(A0_Mass_ZY_QT_ss, "A0_Mass_ZY_QT_ss", "A0", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 BookAngularHist(A0_Mass_ZY_QT_cc, "A0_Mass_ZY_QT_cc", "A0", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 BookAngularHist(A0_Mass_ZY_QT_bb, "A0_Mass_ZY_QT_bb", "A0", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);


}

void HistsResBos::bookCovHists(int TotalThread)
{
 TString tail = "";

 int mass_bin = 120;

 BookCovHist(FZmass_CC_Cov, "FZmass_CC", "FZmass_CC", mass_bin, 60, 120);
 BookCovHist(BZmass_CC_Cov, "BZmass_CC", "BZmass_CC", mass_bin, 60, 120);
 BookCovHist(FZmass_CF_Cov, "FZmass_CF", "FZmass_CF", mass_bin, 60, 120);
 BookCovHist(BZmass_CF_Cov, "BZmass_CF", "BZmass_CF", mass_bin, 60, 120);


}

void HistsResBos::InputData(TString FileName, TString HistName)
{
 DataFile = new TFile(FileName);
 DataHist = (TH1D *)DataFile->Get(HistName);
}

void HistsResBos::outputInformation()
{
 //For getting the AFB and AFB Slope

 double xbins1[11] = {80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100};
 double xbins2[31] = {60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120};
 double xbins3[9] = {82, 84, 86, 88, 90, 92, 94, 96, 98};
 double xbins4[7] = {84, 86, 88, 90, 92, 94, 96};
 double xbins5[2] = {80, 100};

 int mass_bin = 120;

 //AFB Slope
 TH1D *FZmass_CC_80_100 = (TH1D *)FZmass_CC->at(0)->Rebin(10, "FZmass_CC_80_100", xbins1);
 TH1D *BZmass_CC_80_100 = (TH1D *)BZmass_CC->at(0)->Rebin(10, "BZmass_CC_80_100", xbins1);
 TH1D *FZmass_CF_80_100 = (TH1D *)FZmass_CF->at(0)->Rebin(10, "FZmass_CF_80_100", xbins1);
 TH1D *BZmass_CF_80_100 = (TH1D *)BZmass_CF->at(0)->Rebin(10, "BZmass_CF_80_100", xbins1);
 TH1D *FZmass_80_100 = (TH1D *)FZmass->at(0)->Rebin(10, "FZmass_80_100", xbins1);
 TH1D *BZmass_80_100 = (TH1D *)BZmass->at(0)->Rebin(10, "BZmass_80_100", xbins1);
 TH1D *FZmass_LHCb_80_100 = (TH1D *)FZmass_LHCb->at(0)->Rebin(10, "FZmass_LHCb_80_100", xbins1);
 TH1D *BZmass_LHCb_80_100 = (TH1D *)BZmass_LHCb->at(0)->Rebin(10, "BZmass_LHCb_80_100", xbins1);

 TH1D *FZmass_CC_82_98 = (TH1D *)FZmass_CC->at(0)->Rebin(8, "FZmass_CC_82_98", xbins3);
 TH1D *BZmass_CC_82_98 = (TH1D *)BZmass_CC->at(0)->Rebin(8, "BZmass_CC_82_98", xbins3);
 TH1D *FZmass_CF_82_98 = (TH1D *)FZmass_CF->at(0)->Rebin(8, "FZmass_CF_82_98", xbins3);
 TH1D *BZmass_CF_82_98 = (TH1D *)BZmass_CF->at(0)->Rebin(8, "BZmass_CF_82_98", xbins3);
 TH1D *FZmass_82_98 = (TH1D *)FZmass->at(0)->Rebin(8, "FZmass_82_98", xbins3);
 TH1D *BZmass_82_98 = (TH1D *)BZmass->at(0)->Rebin(8, "BZmass_82_98", xbins3);
 TH1D *FZmass_LHCb_82_98 = (TH1D *)FZmass_LHCb->at(0)->Rebin(8, "FZmass_LHCb_82_98", xbins3);
 TH1D *BZmass_LHCb_82_98 = (TH1D *)BZmass_LHCb->at(0)->Rebin(8, "BZmass_LHCb_82_98", xbins3);

 TH1D *FZmass_CC_84_96 = (TH1D *)FZmass_CC->at(0)->Rebin(6, "FZmass_CC_84_96", xbins4);
 TH1D *BZmass_CC_84_96 = (TH1D *)BZmass_CC->at(0)->Rebin(6, "BZmass_CC_84_96", xbins4);
 TH1D *FZmass_CF_84_96 = (TH1D *)FZmass_CF->at(0)->Rebin(6, "FZmass_CF_84_96", xbins4);
 TH1D *BZmass_CF_84_96 = (TH1D *)BZmass_CF->at(0)->Rebin(6, "BZmass_CF_84_96", xbins4);
 TH1D *FZmass_84_96 = (TH1D *)FZmass->at(0)->Rebin(6, "FZmass_84_96", xbins4);
 TH1D *BZmass_84_96 = (TH1D *)BZmass->at(0)->Rebin(6, "BZmass_84_96", xbins4);
 TH1D *FZmass_LHCb_84_96 = (TH1D *)FZmass_LHCb->at(0)->Rebin(6, "FZmass_LHCb_84_96", xbins4);
 TH1D *BZmass_LHCb_84_96 = (TH1D *)BZmass_LHCb->at(0)->Rebin(6, "BZmass_LHCb_84_96", xbins4);

 TH1D *FZmass_CC_Average = (TH1D *)FZmass_CC->at(0)->Rebin(1, "FZmass_CC_Average", xbins5);
 TH1D *BZmass_CC_Average = (TH1D *)BZmass_CC->at(0)->Rebin(1, "BZmass_CC_Average", xbins5);
 TH1D *FZmass_CF_Average = (TH1D *)FZmass_CF->at(0)->Rebin(1, "FZmass_CF_Average", xbins5);
 TH1D *BZmass_CF_Average = (TH1D *)BZmass_CF->at(0)->Rebin(1, "BZmass_CF_Average", xbins5);
 TH1D *FZmass_Average = (TH1D *)FZmass->at(0)->Rebin(1, "FZmass_Average", xbins5);
 TH1D *BZmass_Average = (TH1D *)BZmass->at(0)->Rebin(1, "BZmass_Average", xbins5);
 TH1D *FZmass_LHCb_Average = (TH1D *)FZmass_LHCb->at(0)->Rebin(1, "FZmass_LHCb_Average", xbins5);
 TH1D *BZmass_LHCb_Average = (TH1D *)BZmass_LHCb->at(0)->Rebin(1, "BZmass_LHCb_Average", xbins5);

 AFB_CC_80_100 = (TH1D *)FZmass_CC_80_100->Clone("AFB_CC_80_100");
 AFB_CC_80_100->Reset();
 AFB_CF_80_100 = (TH1D *)FZmass_CF_80_100->Clone("AFB_CF_80_100");
 AFB_CF_80_100->Reset();
 AFB_Full_80_100 = (TH1D *)FZmass_80_100->Clone("AFB_Full_80_100");
 AFB_Full_80_100->Reset();
 AFB_LHCb_80_100 = (TH1D *)FZmass_LHCb_80_100->Clone("AFB_LHCb_80_100");
 AFB_LHCb_80_100->Reset();

 TH1D *AFB_CC_82_98 = (TH1D *)FZmass_CC_82_98->Clone("AFB_CC_82_98");
 AFB_CC_82_98->Reset();
 TH1D *AFB_CF_82_98 = (TH1D *)FZmass_CF_82_98->Clone("AFB_CF_82_98");
 AFB_CF_82_98->Reset();
 TH1D *AFB_Full_82_98 = (TH1D *)FZmass_82_98->Clone("AFB_Full_82_98");
 AFB_Full_82_98->Reset();
 TH1D *AFB_LHCb_82_98 = (TH1D *)FZmass_LHCb_82_98->Clone("AFB_LHCb_82_98");
 AFB_LHCb_82_98->Reset();

 TH1D *AFB_CC_84_96 = (TH1D *)FZmass_CC_84_96->Clone("AFB_CC_84_96");
 AFB_CC_84_96->Reset();
 TH1D *AFB_CF_84_96 = (TH1D *)FZmass_CF_84_96->Clone("AFB_CF_84_96");
 AFB_CF_84_96->Reset();
 TH1D *AFB_Full_84_96 = (TH1D *)FZmass_84_96->Clone("AFB_Full_84_96");
 AFB_Full_84_96->Reset();
 TH1D *AFB_LHCb_84_96 = (TH1D *)FZmass_LHCb_84_96->Clone("AFB_LHCb_84_96");
 AFB_LHCb_84_96->Reset();

 AveAFB_CC = (TH1D *)FZmass_CC_Average->Clone("AveAFB_CC");
 AveAFB_CC->Reset();
 AveAFB_CF = (TH1D *)FZmass_CF_Average->Clone("AveAFB_CF");
 AveAFB_CF->Reset();
 AveAFB_Full = (TH1D *)FZmass_Average->Clone("AveAFB_Full");
 AveAFB_Full->Reset();
 AveAFB_LHCb = (TH1D *)FZmass_LHCb_Average->Clone("AveAFB_LHCb");
 AveAFB_LHCb->Reset();

 AFBFunction(FZmass_CC_80_100, BZmass_CC_80_100, AFB_CC_80_100);
 AFBFunction(FZmass_CF_80_100, BZmass_CF_80_100, AFB_CF_80_100);
 AFBFunction(FZmass_80_100, BZmass_80_100, AFB_Full_80_100);
 AFBFunction(FZmass_LHCb_80_100, BZmass_LHCb_80_100, AFB_LHCb_80_100);

 AFBFunction(FZmass_CC_82_98, BZmass_CC_82_98, AFB_CC_82_98);
 AFBFunction(FZmass_CF_82_98, BZmass_CF_82_98, AFB_CF_82_98);
 AFBFunction(FZmass_82_98, BZmass_82_98, AFB_Full_82_98);
 AFBFunction(FZmass_LHCb_82_98, BZmass_LHCb_82_98, AFB_LHCb_82_98);

 AFBFunction(FZmass_CC_84_96, BZmass_CC_84_96, AFB_CC_84_96);
 AFBFunction(FZmass_CF_84_96, BZmass_CF_84_96, AFB_CF_84_96);
 AFBFunction(FZmass_84_96, BZmass_84_96, AFB_Full_84_96);
 AFBFunction(FZmass_LHCb_84_96, BZmass_LHCb_84_96, AFB_LHCb_84_96);

 AFBFunction(FZmass_CC_Average, BZmass_CC_Average, AveAFB_CC);
 AFBFunction(FZmass_CF_Average, BZmass_CF_Average, AveAFB_CF);
 AFBFunction(FZmass_Average, BZmass_Average, AveAFB_Full);
 AFBFunction(FZmass_LHCb_Average, BZmass_LHCb_Average, AveAFB_LHCb);

 AFBSlope_CC = new TH1D("AFBSlope_CC", "AFBSlope_CC", 1, 80, 100);
 AFBSlope_CF = new TH1D("AFBSlope_CF", "AFBSlope_CF", 1, 80, 100);
 AFBSlope_Full = new TH1D("AFBSlope_Full", "AFBSlope_Full", 1, 80, 100);
 AFBSlope_LHCb = new TH1D("AFBSlope_LHCb", "AFBSlope_LHCb", 1, 80, 100);

 AFBSlope_82_98_CC = new TH1D("AFBSlope_82_98_CC", "AFBSlope_82_98_CC", 1, 82, 98);
 AFBSlope_82_98_CF = new TH1D("AFBSlope_82_98_CF", "AFBSlope_82_98_CF", 1, 82, 98);
 AFBSlope_82_98_Full = new TH1D("AFBSlope_82_98_Full", "AFBSlope_82_98_Full", 1, 82, 98);
 AFBSlope_82_98_LHCb = new TH1D("AFBSlope_82_98_LHCb", "AFBSlope_82_98_LHCb", 1, 82, 98);

 AFBSlope_84_96_CC = new TH1D("AFBSlope_84_96_CC", "AFBSlope_84_96_CC", 1, 84, 96);
 AFBSlope_84_96_CF = new TH1D("AFBSlope_84_96_CF", "AFBSlope_84_96_CF", 1, 84, 96);
 AFBSlope_84_96_Full = new TH1D("AFBSlope_84_96_Full", "AFBSlope_84_96_Full", 1, 84, 96);
 AFBSlope_84_96_LHCb = new TH1D("AFBSlope_84_96_LHCb", "AFBSlope_84_96_LHCb", 1, 84, 96);

 AFBOffset_CC = new TH1D("AFBOffset_CC", "AFBOffset_CC", 1, 80, 100);
 AFBOffset_CF = new TH1D("AFBOffset_CF", "AFBOffset_CF", 1, 80, 100);
 AFBOffset_Full = new TH1D("AFBOffset_Full", "AFBOffset_Full", 1, 80, 100);
 AFBOffset_LHCb = new TH1D("AFBOffset_LHCb", "AFBOffset_LHCb", 1, 80, 100);

 AFBOffset_82_98_CC = new TH1D("AFBOffset_82_98_CC", "AFBOffset_82_98_CC", 1, 82, 98);
 AFBOffset_82_98_CF = new TH1D("AFBOffset_82_98_CF", "AFBOffset_82_98_CF", 1, 82, 98);
 AFBOffset_82_98_Full = new TH1D("AFBOffset_82_98_Full", "AFBOffset_82_98_Full", 1, 82, 98);
 AFBOffset_82_98_LHCb = new TH1D("AFBOffset_82_98_LHCb", "AFBOffset_82_98_LHCb", 1, 82, 98);

 AFBOffset_84_96_CC = new TH1D("AFBOffset_84_96_CC", "AFBOffset_84_96_CC", 1, 84, 96);
 AFBOffset_84_96_CF = new TH1D("AFBOffset_84_96_CF", "AFBOffset_84_96_CF", 1, 84, 96);
 AFBOffset_84_96_Full = new TH1D("AFBOffset_84_96_Full", "AFBOffset_84_96_Full", 1, 84, 96);
 AFBOffset_84_96_LHCb = new TH1D("AFBOffset_84_96_LHCb", "AFBOffset_84_96_LHCb", 1, 84, 96);

 TF1 *Slope_CC;
 TF1 *Slope_CF;
 TF1 *Slope_Full;
 TF1 *Slope_LHCb;
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
 LinearFitting(AFB_LHCb_80_100, Slope_LHCb, par, parErr);
 AFBSlope_LHCb->SetBinContent(1, par[0]);
 AFBSlope_LHCb->SetBinError(1, parErr[0]);
 AFBOffset_LHCb->SetBinContent(1, par[1]);
 AFBOffset_LHCb->SetBinError(1, parErr[1]);

 TF1 *Slope_82_98_CC;
 TF1 *Slope_82_98_CF;
 TF1 *Slope_82_98_Full;
 TF1 *Slope_82_98_LHCb;
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
 LinearFitting(AFB_LHCb_82_98, Slope_82_98_LHCb, par, parErr);
 AFBSlope_82_98_LHCb->SetBinContent(1, par[0]);
 AFBSlope_82_98_LHCb->SetBinError(1, parErr[0]);
 AFBOffset_82_98_LHCb->SetBinContent(1, par[1]);
 AFBOffset_82_98_LHCb->SetBinError(1, parErr[1]);

 TF1 *Slope_84_96_CC;
 TF1 *Slope_84_96_CF;
 TF1 *Slope_84_96_Full;
 TF1 *Slope_84_96_LHCb;
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
 LinearFitting(AFB_LHCb_84_96, Slope_84_96_LHCb, par, parErr);
 AFBSlope_84_96_LHCb->SetBinContent(1, par[0]);
 AFBSlope_84_96_LHCb->SetBinError(1, parErr[0]);
 AFBOffset_84_96_LHCb->SetBinContent(1, par[1]);
 AFBOffset_84_96_LHCb->SetBinError(1, parErr[1]);

 AFBSlope_CC->Write();
 AFBSlope_CF->Write();
 AFBSlope_Full->Write();
 AFBSlope_LHCb->Write();
 AFBSlope_82_98_CC->Write();
 AFBSlope_82_98_CF->Write();
 AFBSlope_82_98_Full->Write();
 AFBSlope_82_98_LHCb->Write();
 AFBSlope_84_96_CC->Write();
 AFBSlope_84_96_CF->Write();
 AFBSlope_84_96_Full->Write();
 AFBSlope_84_96_LHCb->Write();
 AFBOffset_CC->Write();
 AFBOffset_CF->Write();
 AFBOffset_Full->Write();
 AFBOffset_LHCb->Write();
 AFBOffset_82_98_CC->Write();
 AFBOffset_82_98_CF->Write();
 AFBOffset_82_98_Full->Write();
 AFBOffset_82_98_LHCb->Write();
 AFBOffset_84_96_CC->Write();
 AFBOffset_84_96_CF->Write();
 AFBOffset_84_96_Full->Write();
 AFBOffset_84_96_LHCb->Write();
 AveAFB_CC->Write();
 AveAFB_CF->Write();
 AveAFB_Full->Write();
 AveAFB_LHCb->Write();
 AFB_CC_80_100->Write();
 AFB_CF_80_100->Write();
 AFB_Full_80_100->Write();
 AFB_LHCb_80_100->Write();



 //AFB Diff
 TH1D *FZmass_CC_60_120 = (TH1D *)FZmass_CC->at(0)->Rebin(30, "FZmass_CC_60_120", xbins2);
 TH1D *BZmass_CC_60_120 = (TH1D *)BZmass_CC->at(0)->Rebin(30, "BZmass_CC_60_120", xbins2);
 TH1D *FZmass_CF_60_120 = (TH1D *)FZmass_CF->at(0)->Rebin(30, "FZmass_CF_60_120", xbins2);
 TH1D *BZmass_CF_60_120 = (TH1D *)BZmass_CF->at(0)->Rebin(30, "BZmass_CF_60_120", xbins2);
 TH1D *FZmass_60_120 = (TH1D *)FZmass->at(0)->Rebin(30, "FZmass_60_120", xbins2);
 TH1D *BZmass_60_120 = (TH1D *)BZmass->at(0)->Rebin(30, "BZmass_60_120", xbins2);
 TH1D *FZmass_LHCb_60_120 = (TH1D *)FZmass_LHCb->at(0)->Rebin(30, "FZmass_LHCb_60_120", xbins2);
 TH1D *BZmass_LHCb_60_120 = (TH1D *)BZmass_LHCb->at(0)->Rebin(30, "BZmass_LHCb_60_120", xbins2);

 TH1D *AFB_CC_60_120 = (TH1D *)FZmass_CC_60_120->Clone("AFB_CC_60_120");
 AFB_CC_60_120->Reset();
 TH1D *AFB_CF_60_120 = (TH1D *)FZmass_CF_60_120->Clone("AFB_CF_60_120");
 AFB_CF_60_120->Reset();
 TH1D *AFB_Full_60_120 = (TH1D *)FZmass_60_120->Clone("AFB_Full_60_120");
 AFB_Full_60_120->Reset();
 TH1D *AFB_LHCb_60_120 = (TH1D *)FZmass_LHCb_60_120->Clone("AFB_LHCb_60_120");
 AFB_LHCb_60_120->Reset();

 AFBFunction(FZmass_CC_60_120, BZmass_CC_60_120, AFB_CC_60_120);
 AFBFunction(FZmass_CF_60_120, BZmass_CF_60_120, AFB_CF_60_120);
 AFBFunction(FZmass_60_120, BZmass_60_120, AFB_Full_60_120);
 AFBFunction(FZmass_LHCb_60_120, BZmass_LHCb_60_120, AFB_LHCb_60_120);

 AFBDiff_CC = new TH1D("AFBDiff_CC", "AFBDiff_CC", AFB_CC_60_120->GetNbinsX() / 2, 1, AFB_CC_60_120->GetNbinsX() / 2);
 AFBDiff_CC_ZPole = new TH1D("AFBDiff_CC_ZPole", "AFBDiff_CC_ZPole", 5, 1, 5);
 AFBDiff_CC_Side = new TH1D("AFBDiff_CC_Side", "AFBDiff_CC_Side", 10, 1, 10);

 AFBDiff_CF = new TH1D("AFBDiff_CF", "AFBDiff_CF", AFB_CF_60_120->GetNbinsX() / 2, 1, AFB_CF_60_120->GetNbinsX() / 2);
 AFBDiff_CF_ZPole = new TH1D("AFBDiff_CF_ZPole", "AFBDiff_CF_ZPole", 5, 1, 5);
 AFBDiff_CF_Side = new TH1D("AFBDiff_CF_Side", "AFBDiff_CF_Side", 10, 1, 10);

 AFBDiff_Full = new TH1D("AFBDiff_Full", "AFBDiff_Full", AFB_Full_60_120->GetNbinsX() / 2, 1, AFB_Full_60_120->GetNbinsX() / 2);
 AFBDiff_Full_ZPole = new TH1D("AFBDiff_Full_ZPole", "AFBDiff_Full_ZPole", 5, 1, 5);
 AFBDiff_Full_Side = new TH1D("AFBDiff_Full_Side", "AFBDiff_Full_Side", 10, 1, 10);

 AFBDiff_LHCb = new TH1D("AFBDiff_LHCb", "AFBDiff_LHCb", AFB_LHCb_60_120->GetNbinsX() / 2, 1, AFB_LHCb_60_120->GetNbinsX() / 2);
 AFBDiff_LHCb_ZPole = new TH1D("AFBDiff_LHCb_ZPole", "AFBDiff_LHCb_ZPole", 5, 1, 5);
 AFBDiff_LHCb_Side = new TH1D("AFBDiff_LHCb_Side", "AFBDiff_LHCb_Side", 10, 1, 10);

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

   //LHCb
   Diff = AFB_LHCb_60_120->GetBinContent(FirstBin) - AFB_LHCb_60_120->GetBinContent(LastBin);
   DiffErr = sqrt(AFB_LHCb_60_120->GetBinError(FirstBin) * AFB_LHCb_60_120->GetBinError(FirstBin) + AFB_LHCb_60_120->GetBinError(LastBin) * AFB_LHCb_60_120->GetBinError(LastBin));

   if(ibin <= 10){
     AFBDiff_LHCb_Side->SetBinContent(ibin, Diff);
     AFBDiff_LHCb_Side->SetBinError(ibin, DiffErr);
   }
   else{
     AFBDiff_LHCb_ZPole->SetBinContent(ibin - 10, Diff);
     AFBDiff_LHCb_ZPole->SetBinError(ibin - 10, DiffErr);
   }
   AFBDiff_LHCb->SetBinContent(ibin, Diff);
   AFBDiff_LHCb->SetBinError(ibin, DiffErr);

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

 AFBDiff_LHCb->Write();
 AFBDiff_LHCb_ZPole->Write();
 AFBDiff_LHCb_Side->Write();


 //AFB Gradient
 TH1D *AFB_CC_1GeV = (TH1D *)FZmass_CC->at(0)->Clone("AFB_CC_1GeV");
 AFB_CC_1GeV->Reset();
 TH1D *AFB_CF_1GeV = (TH1D *)FZmass_CF->at(0)->Clone("AFB_CF_1GeV");
 AFB_CF_1GeV->Reset();
 TH1D *AFB_Full_1GeV = (TH1D *)FZmass->at(0)->Clone("AFB_Full_1GeV");
 AFB_Full_1GeV->Reset();
 TH1D *AFB_LHCb_1GeV = (TH1D *)FZmass_LHCb->at(0)->Clone("AFB_LHCb_1GeV");
 AFB_LHCb_1GeV->Reset();


 AFBFunction(FZmass_CC->at(0), BZmass_CC->at(0), AFB_CC_1GeV);
 AFBFunction(FZmass_CF->at(0), BZmass_CF->at(0), AFB_CF_1GeV);
 AFBFunction(FZmass->at(0), BZmass->at(0), AFB_Full_1GeV);
 AFBFunction(FZmass_LHCb->at(0), BZmass_LHCb->at(0), AFB_LHCb_1GeV);

 AFBGradient_CC = new TH1D("AFBGradient_CC", "AFBGradient_CC", mass_bin / 2, 60, 120);
 AFBGradient_CF = new TH1D("AFBGradient_CF", "AFBGradient_CF", mass_bin / 2, 60, 120);
 AFBGradient_Full = new TH1D("AFBGradient_Full", "AFBGradient_Full", mass_bin / 2, 60, 120);
 AFBGradient_LHCb = new TH1D("AFBGradient_LHCb", "AFBGradient_LHCb", mass_bin / 2, 60, 120);

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

   Diff = AFB_LHCb_1GeV->GetBinContent(2 * ibin) - AFB_LHCb_1GeV->GetBinContent(2 * ibin - 1);
   DiffError = sqrt(AFB_LHCb_1GeV->GetBinError(2 * ibin) * AFB_LHCb_1GeV->GetBinError(2 * ibin) + AFB_LHCb_1GeV->GetBinError(2 * ibin - 1) * AFB_LHCb_1GeV->GetBinError(2 * ibin - 1));
   AFBGradient_LHCb->SetBinContent(ibin, Diff);
   AFBGradient_LHCb->SetBinError(ibin, DiffError);

 }

 AFBGradient_CC->Write();
 AFBGradient_CF->Write();
 AFBGradient_Full->Write();
 AFBGradient_LHCb->Write();

 //AFB
// v_FZmass_CC.at(0)->Rebin(2);
// v_BZmass_CC.at(0)->Rebin(2);
// v_FZmass_CF.at(0)->Rebin(2);
// v_BZmass_CF.at(0)->Rebin(2);
// v_FZmass.at(0)->Rebin(2);
// v_BZmass.at(0)->Rebin(2);
// v_FZmass_LHCb.at(0)->Rebin(2);
// v_BZmass_LHCb.at(0)->Rebin(2);

 AFB_CC = (TH1D *)FZmass_CC->at(0)->Clone("AFB_CC");
 AFB_CC->Reset();
 AFB_CF = (TH1D *)FZmass_CF->at(0)->Clone("AFB_CF");
 AFB_CF->Reset();
 AFB_Full = (TH1D *)FZmass->at(0)->Clone("AFB_Full");
 AFB_Full->Reset();
 AFB_LHCb = (TH1D *)FZmass_LHCb->at(0)->Clone("AFB_LHCb");
 AFB_LHCb->Reset();

 AFBFunction(FZmass_CC->at(0), BZmass_CC->at(0), AFB_CC);
 AFBFunction(FZmass_CF->at(0), BZmass_CF->at(0), AFB_CF);
 AFBFunction(FZmass->at(0), BZmass->at(0), AFB_Full);
 AFBFunction(FZmass_LHCb->at(0), BZmass_LHCb->at(0), AFB_LHCb);

 AFB_CC->Write();
 AFB_CF->Write();
 AFB_Full->Write();
 AFB_LHCb->Write();

 AverageZPt_ZY = (TH1D *)AverageZPt_ZY_numer->at(0)->Clone("AverageZPt_ZY");
 AverageZPt_ZY->Divide(AverageZPt_ZY_denom->at(0));
 AverageZPt_ZY->Write();

 AverageZPt_lnQ = (TH1D *)AverageZPt_lnQ_numer->at(0)->Clone("AverageZPt_lnQ");
 AverageZPt_lnQ->Divide(AverageZPt_lnQ_denom->at(0));
 AverageZPt_lnQ->Write();

 AverageLepE_ZY = (TH1D *)AverageLepE_ZY_numer->at(0)->Clone("AverageLepE_ZY");
 AverageLepE_ZY->Divide(AverageLepE_ZY_denom->at(0));
 AverageLepE_ZY->Write();

 AverageAntiLepE_ZY = (TH1D *)AverageAntiLepE_ZY_numer->at(0)->Clone("AverageAntiLepE_ZY");
 AverageAntiLepE_ZY->Divide(AverageAntiLepE_ZY_denom->at(0));
 AverageAntiLepE_ZY->Write();

 RatioLepE_ZY = (TH1D *)AverageLepE_ZY->Clone("RatioLepE_ZY");
 RatioLepE_ZY->Divide(AverageAntiLepE_ZY);
 RatioLepE_ZY->Write();

 //Lepton charge asymmetry
 LepAsym = (TH1D *)LepEtaAbs->at(0)->Clone("LepAsym");
 LepAsym->Reset();
 LepAsym_CC = (TH1D *)LepEtaAbs_CC->at(0)->Clone("LepAsym_CC");
 LepAsym_CC->Reset();
 LepAsym_CF = (TH1D *)LepEtaAbs_CF->at(0)->Clone("LepAsym_CF");
 LepAsym_CF->Reset();
 LepAsym_LHCb = (TH1D *)LepEtaAbs_LHCb->at(0)->Clone("LepAsym_LHCb");
 LepAsym_LHCb->Reset();

 AFBFunction(LepEtaAbs->at(0), AntiLepEtaAbs->at(0), LepAsym);
 AFBFunction(LepEtaAbs_CC->at(0), AntiLepEtaAbs_CC->at(0), LepAsym_CC);
 AFBFunction(LepEtaAbs_CF->at(0), AntiLepEtaAbs_CF->at(0), LepAsym_CF);
 AFBFunction(LepEtaAbs_LHCb->at(0), AntiLepEtaAbs_LHCb->at(0), LepAsym_LHCb);

 LepAsym->Write();
 LepAsym_CC->Write();
 LepAsym_CF->Write();
 LepAsym_LHCb->Write();

 //AFB vs ZY
 AFB_ZY = (TH1D *)FZRapidity->at(0)->Clone("AFB_ZY");
 AFB_ZY->Reset();
 AFB_ZY_CC = (TH1D *)FZRapidity_CC->at(0)->Clone("AFB_ZY_CC");
 AFB_ZY_CC->Reset();
 AFB_ZY_CF = (TH1D *)FZRapidity_CF->at(0)->Clone("AFB_ZY_CF");
 AFB_ZY_CF->Reset();
 AFB_ZY_LHCb = (TH1D *)FZRapidity_LHCb->at(0)->Clone("AFB_ZY_LHCb");
 AFB_ZY_LHCb->Reset();
 AFB_ZY_uu = (TH1D *)FZY_uu->at(0)->Clone("AFB_ZY_uu");
 AFB_ZY_uu->Reset();
 AFB_ZY_dd = (TH1D *)FZY_dd->at(0)->Clone("AFB_ZY_dd");
 AFB_ZY_dd->Reset();

 AFBFunction(FZRapidity->at(0), BZRapidity->at(0), AFB_ZY);
 AFBFunction(FZRapidity_CC->at(0), BZRapidity_CC->at(0), AFB_ZY_CC);
 AFBFunction(FZRapidity_CF->at(0), BZRapidity_CF->at(0), AFB_ZY_CF);
 AFBFunction(FZRapidity_LHCb->at(0), BZRapidity_LHCb->at(0), AFB_ZY_LHCb);
 AFBFunction(FZY_uu->at(0), BZY_uu->at(0), AFB_ZY_uu);
 AFBFunction(FZY_dd->at(0), BZY_dd->at(0), AFB_ZY_dd);

 AFB_ZY->Write();
 AFB_ZY_CC->Write();
 AFB_ZY_CF->Write();
 AFB_ZY_LHCb->Write();
 AFB_ZY_uu->Write();
 AFB_ZY_dd->Write();

 //Average AFB vs ZY ZPt
 AveAFB_ZY_ZPt = (TH2D *)FAveZMass_ZY_QT->at(0)->Clone("AveAFB_ZY_QT");
 AveAFB_ZY_ZPt->Reset();

 AFBFunction(FAveZMass_ZY_QT->at(0), BAveZMass_ZY_QT->at(0), AveAFB_ZY_ZPt);

 AveAFB_ZY_ZPt->Write();

 //AFB vs Mass ZY ZPt
 AFB_Mass_ZY_ZPt = (TH3D *)FZMass_ZY_QT->at(0)->Clone("AFB_ZMass_ZY_QT");
 AFB_Mass_ZY_ZPt->Reset();

 AFBFunction(FZMass_ZY_QT->at(0), BZMass_ZY_QT->at(0), AFB_Mass_ZY_ZPt);

 AFB_Mass_ZY_ZPt->Write();

 AFB_CMS_Mass_ZY_ZPt = (TH3D *)CMS_FZMass_ZY_QT->at(0)->Clone("AFB_CMS_ZMass_ZY_QT");
 AFB_CMS_Mass_ZY_ZPt->Reset();

 AFBFunction(CMS_FZMass_ZY_QT->at(0), CMS_BZMass_ZY_QT->at(0), AFB_CMS_Mass_ZY_ZPt);

 AFB_CMS_Mass_ZY_ZPt->Write();

 //Lepton eta width different
 LepWidthDiff = new TH1D("LepWidthDiff", "LepWidthDiff", 1, 0, 1);
 LepWidthDiff_CC = new TH1D("LepWidthDiff_CC", "LepWidthDiff_CC", 1, 0, 1);
 LepWidthDiff_CF = new TH1D("LepWidthDiff_CF", "LepWidthDiff_CF", 1, 0, 1);
 LepWidthDiff_LHCb = new TH1D("LepWidthDiff_LHCb", "LepWidthDiff_LHCb", 1, 0, 1);

 LepWidthDiff->SetBinContent(1, (LepEta->at(0)->GetRMS() - AntiLepEta->at(0)->GetRMS()));
 LepWidthDiff->SetBinError(1, LepEta->at(0)->GetRMSError());
 LepWidthDiff_CC->SetBinContent(1, (LepEta_CC->at(0)->GetRMS() - AntiLepEta_CC->at(0)->GetRMS()));
 LepWidthDiff_CC->SetBinError(1, LepEta_CC->at(0)->GetRMSError());
 LepWidthDiff_CF->SetBinContent(1, (LepEta_CF->at(0)->GetRMS() - AntiLepEta_CF->at(0)->GetRMS()));
 LepWidthDiff_CF->SetBinError(1, LepEta_CF->at(0)->GetRMSError());
 LepWidthDiff_LHCb->SetBinContent(1, (LepEta_LHCb->at(0)->GetRMS() - AntiLepEta_LHCb->at(0)->GetRMS()));
 LepWidthDiff_LHCb->SetBinError(1, LepEta_LHCb->at(0)->GetRMSError());

 LepWidthDiff->Write();
 LepWidthDiff_CC->Write();
 LepWidthDiff_CF->Write();
 LepWidthDiff_LHCb->Write();

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

 AFBQuarkGradient_CC = new TH1D("AFBQuarkGradient_CC", "AFBQuarkGradient_CC", mass_bin / 2, 60, 120);
 AFBQuarkGradient_CF = new TH1D("AFBQuarkGradient_CF", "AFBQuarkGradient_CF", mass_bin / 2, 60, 120);
 AFBQuarkGradient_Full = new TH1D("AFBQuarkGradient_Full", "AFBQuarkGradient_Full", mass_bin / 2, 60, 120);

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

 GetXsecFraction(ZMass_CC_uu->at(0), Xsec_CC, XsecFraction_CC_uu);
 GetXsecFraction(ZMass_CC_dd->at(0), Xsec_CC, XsecFraction_CC_dd);
 GetXsecFraction(ZMass_CF_uu->at(0), Xsec_CF, XsecFraction_CF_uu);
 GetXsecFraction(ZMass_CF_dd->at(0), Xsec_CF, XsecFraction_CF_dd);
 GetXsecFraction(ZMass_uu->at(0), Xsec_Full, XsecFraction_Full_uu);
 GetXsecFraction(ZMass_dd->at(0), Xsec_Full, XsecFraction_Full_dd);

 XsecFraction_CC_uu->Write();
 XsecFraction_CC_dd->Write();
 XsecFraction_CF_uu->Write();
 XsecFraction_CF_dd->Write();
 XsecFraction_Full_uu->Write();
 XsecFraction_Full_dd->Write();


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

 //AFB vs ZPt
 AFB_ZPt_uu = (TH1D *)FZPt_uu->at(0)->Clone("AFB_ZPt_uu");
 AFB_ZPt_uu->Reset();
 AFB_ZPt_dd = (TH1D *)FZPt_dd->at(0)->Clone("AFB_ZPt_dd");
 AFB_ZPt_dd->Reset();

 AFBFunction(FZPt_uu->at(0), BZPt_uu->at(0), AFB_ZPt_uu);
 AFBFunction(FZPt_dd->at(0), BZPt_dd->at(0), AFB_ZPt_dd);

 AFB_ZPt_uu->Write();
 AFB_ZPt_dd->Write();

 //quark level AFB vs Mass ZPt
 AFB_Mass_ZPt_Full_uu = (TH2D *)FZmass_ZPt_uu->at(0)->Clone("AFB_Mass_ZPt_uu");
 AFB_Mass_ZPt_Full_uu->Reset();
 AFB_Mass_ZPt_Full_dd = (TH2D *)FZmass_ZPt_dd->at(0)->Clone("AFB_Mass_ZPt_dd");
 AFB_Mass_ZPt_Full_dd->Reset();

 AFBFunction(FZmass_ZPt_uu->at(0), BZmass_ZPt_uu->at(0), AFB_Mass_ZPt_Full_uu);
 AFBFunction(FZmass_ZPt_dd->at(0), BZmass_ZPt_dd->at(0), AFB_Mass_ZPt_Full_dd);

 AFB_Mass_ZPt_Full_uu->Write();
 AFB_Mass_ZPt_Full_dd->Write();

 //quark level AFB vs Mass ZY ZPt
 AFB_Mass_ZY_ZPt_uu = (TH3D *)FZMass_ZY_QT_uu->at(0)->Clone("AFB_ZMass_ZY_QT_uu");
 AFB_Mass_ZY_ZPt_uu->Reset();
 AFB_Mass_ZY_ZPt_dd = (TH3D *)FZMass_ZY_QT_dd->at(0)->Clone("AFB_ZMass_ZY_QT_dd");
 AFB_Mass_ZY_ZPt_dd->Reset();

 AFBFunction(FZMass_ZY_QT_uu->at(0), BZMass_ZY_QT_uu->at(0), AFB_Mass_ZY_ZPt_uu);
 AFBFunction(FZMass_ZY_QT_dd->at(0), BZMass_ZY_QT_dd->at(0), AFB_Mass_ZY_ZPt_dd);

 AFB_Mass_ZY_ZPt_uu->Write();
 AFB_Mass_ZY_ZPt_dd->Write();

 AFB_CMS_Mass_ZY_ZPt_uu = (TH3D *)CMS_FZMass_ZY_QT_uu->at(0)->Clone("AFB_CMS_ZMass_ZY_QT_uu");
 AFB_CMS_Mass_ZY_ZPt_uu->Reset();
 AFB_CMS_Mass_ZY_ZPt_dd = (TH3D *)CMS_FZMass_ZY_QT_dd->at(0)->Clone("AFB_CMS_ZMass_ZY_QT_dd");
 AFB_CMS_Mass_ZY_ZPt_dd->Reset();

 AFBFunction(CMS_FZMass_ZY_QT_uu->at(0), CMS_BZMass_ZY_QT_uu->at(0), AFB_CMS_Mass_ZY_ZPt_uu);
 AFBFunction(CMS_FZMass_ZY_QT_dd->at(0), CMS_BZMass_ZY_QT_dd->at(0), AFB_CMS_Mass_ZY_ZPt_dd);

 AFB_CMS_Mass_ZY_ZPt_uu->Write();
 AFB_CMS_Mass_ZY_ZPt_dd->Write();

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

 Dilution_ZMass_ZY_QT_uu = (TH3D *)ZMass_ZY_QT_uu_wrong->at(0)->Clone("Dilution_ZMass_ZY_QT_uu");
 Dilution_ZMass_ZY_QT_uu->Divide(ZMass_ZY_QT_uu_total->at(0));
 Dilution_ZMass_ZY_QT_dd = (TH3D *)ZMass_ZY_QT_dd_wrong->at(0)->Clone("Dilution_ZMass_ZY_QT_dd");
 Dilution_ZMass_ZY_QT_dd->Divide(ZMass_ZY_QT_dd_total->at(0));

 Dilution_ZMass_ZY_QT_uu->Write();
 Dilution_ZMass_ZY_QT_dd->Write();

 Dilution_CMS_ZMass_ZY_QT_uu = (TH3D *)CMS_ZMass_ZY_QT_uu_wrong->at(0)->Clone("Dilution_CMS_ZMass_ZY_QT_uu");
 Dilution_CMS_ZMass_ZY_QT_uu->Divide(CMS_ZMass_ZY_QT_uu_total->at(0));
 Dilution_CMS_ZMass_ZY_QT_dd = (TH3D *)CMS_ZMass_ZY_QT_dd_wrong->at(0)->Clone("Dilution_CMS_ZMass_ZY_QT_dd");
 Dilution_CMS_ZMass_ZY_QT_dd->Divide(CMS_ZMass_ZY_QT_dd_total->at(0));

 Dilution_CMS_ZMass_ZY_QT_uu->Write();
 Dilution_CMS_ZMass_ZY_QT_dd->Write();


// GetCoefficientDilution(Dilution_ZMass_CC_uu, XsecFraction_CC_uu, CoefficientDilution_CC_uu);
// GetCoefficientDilution(Dilution_ZMass_CC_dd, XsecFraction_CC_dd, CoefficientDilution_CC_dd);
// GetCoefficientDilution(Dilution_ZMass_CF_uu, XsecFraction_CF_uu, CoefficientDilution_CF_uu);
// GetCoefficientDilution(Dilution_ZMass_CF_dd, XsecFraction_CF_dd, CoefficientDilution_CF_dd);
// GetCoefficientDilution(Dilution_ZMass_Full_uu, XsecFraction_Full_uu, CoefficientDilution_Full_uu);
// GetCoefficientDilution(Dilution_ZMass_Full_dd, XsecFraction_Full_dd, CoefficientDilution_Full_dd);

 GetCoefficientDilution(ZMass_CC_uu_wrong->at(0), ZMass_CC_uu_total->at(0), ZMass_CC->at(0), CoefficientDilution_CC_uu);
 GetCoefficientDilution(ZMass_CC_dd_wrong->at(0), ZMass_CC_dd_total->at(0), ZMass_CC->at(0), CoefficientDilution_CC_dd);
 GetCoefficientDilution(ZMass_CF_uu_wrong->at(0), ZMass_CF_uu_total->at(0), ZMass_CF->at(0), CoefficientDilution_CF_uu);
 GetCoefficientDilution(ZMass_CF_dd_wrong->at(0), ZMass_CF_dd_total->at(0), ZMass_CF->at(0), CoefficientDilution_CF_dd);
 GetCoefficientDilution(ZMass_Full_uu_wrong->at(0), ZMass_Full_uu_total->at(0), ZMass->at(0), CoefficientDilution_Full_uu);
 GetCoefficientDilution(ZMass_Full_dd_wrong->at(0), ZMass_Full_dd_total->at(0), ZMass->at(0), CoefficientDilution_Full_dd);

 CoefficientDilution_CC_uu->Write();
 CoefficientDilution_CC_dd->Write();
 CoefficientDilution_CF_uu->Write();
 CoefficientDilution_CF_dd->Write();
 CoefficientDilution_Full_uu->Write();
 CoefficientDilution_Full_dd->Write();

 GetDilutionAverage(CoefficientDilution_CC_uu, DilutionAverage_CC_uu, ResidualDilution_CC_uu);
 GetDilutionAverage(CoefficientDilution_CC_dd, DilutionAverage_CC_dd, ResidualDilution_CC_dd);
 GetDilutionAverage(CoefficientDilution_CF_uu, DilutionAverage_CF_uu, ResidualDilution_CF_uu);
 GetDilutionAverage(CoefficientDilution_CF_dd, DilutionAverage_CF_dd, ResidualDilution_CF_dd);
 GetDilutionAverage(CoefficientDilution_Full_uu, DilutionAverage_Full_uu, ResidualDilution_Full_uu);
 GetDilutionAverage(CoefficientDilution_Full_dd, DilutionAverage_Full_dd, ResidualDilution_Full_dd);

 DilutionAverage_CC_uu->Write();
 DilutionAverage_CC_dd->Write();
 DilutionAverage_CF_uu->Write();
 DilutionAverage_CF_dd->Write();
 DilutionAverage_Full_uu->Write();
 DilutionAverage_Full_dd->Write();

 ResidualDilution_CC_uu->Write();
 ResidualDilution_CC_dd->Write();
 ResidualDilution_CF_uu->Write();
 ResidualDilution_CF_dd->Write();
 ResidualDilution_Full_uu->Write();
 ResidualDilution_Full_dd->Write();

 GetCoefficientDilution(ZMass_ZY_QT_uu_wrong->at(0), ZMass_ZY_QT_uu_total->at(0), ZMass_ZY_QT->at(0), CoefficientDilution_ZMass_ZY_QT_uu);
 GetCoefficientDilution(ZMass_ZY_QT_dd_wrong->at(0), ZMass_ZY_QT_dd_total->at(0), ZMass_ZY_QT->at(0), CoefficientDilution_ZMass_ZY_QT_dd);

 CoefficientDilution_ZMass_ZY_QT_uu->Write();
 CoefficientDilution_ZMass_ZY_QT_dd->Write();

 GetDilutionAverage(CoefficientDilution_ZMass_ZY_QT_uu, DilutionAverage_ZMass_ZY_QT_uu, ResidualDilution_ZMass_ZY_QT_uu);
 GetDilutionAverage(CoefficientDilution_ZMass_ZY_QT_dd, DilutionAverage_ZMass_ZY_QT_dd, ResidualDilution_ZMass_ZY_QT_dd);
 
 DilutionAverage_ZMass_ZY_QT_uu->Write();
 DilutionAverage_ZMass_ZY_QT_dd->Write();

 ResidualDilution_ZMass_ZY_QT_uu->Write();
 ResidualDilution_ZMass_ZY_QT_dd->Write();

 GetCoefficientDilution(CMS_ZMass_ZY_QT_uu_wrong->at(0), CMS_ZMass_ZY_QT_uu_total->at(0), CMS_ZMass_ZY_QT->at(0), CoefficientDilution_CMS_ZMass_ZY_QT_uu);
 GetCoefficientDilution(CMS_ZMass_ZY_QT_dd_wrong->at(0), CMS_ZMass_ZY_QT_dd_total->at(0), CMS_ZMass_ZY_QT->at(0), CoefficientDilution_CMS_ZMass_ZY_QT_dd);

 CoefficientDilution_CMS_ZMass_ZY_QT_uu->Write();
 CoefficientDilution_CMS_ZMass_ZY_QT_dd->Write();

 GetDilutionAverage(CoefficientDilution_CMS_ZMass_ZY_QT_uu, DilutionAverage_CMS_ZMass_ZY_QT_uu, ResidualDilution_CMS_ZMass_ZY_QT_uu);
 GetDilutionAverage(CoefficientDilution_CMS_ZMass_ZY_QT_dd, DilutionAverage_CMS_ZMass_ZY_QT_dd, ResidualDilution_CMS_ZMass_ZY_QT_dd);

 DilutionAverage_CMS_ZMass_ZY_QT_uu->Write();
 DilutionAverage_CMS_ZMass_ZY_QT_dd->Write();

 ResidualDilution_CMS_ZMass_ZY_QT_uu->Write();
 ResidualDilution_CMS_ZMass_ZY_QT_dd->Write();

 Dilution_ZPt = (TH1D *)ZPt_wrong->at(0)->Clone("Dilution_ZPt");
 Dilution_ZPt->Divide(ZPt_total->at(0));
 Dilution_ZRapidity = (TH1D *)ZRapidity_wrong->at(0)->Clone("Dilution_ZRapidity");
 Dilution_ZRapidity->Divide(ZRapidity_total->at(0));

 Dilution_ZPt->Write();
 Dilution_ZRapidity->Write();

 //Dilution vs ZY
 Dilution_ZY_uu = (TH1D *)ZY_uu_wrong->at(0)->Clone("Dilution_ZY_uu");
 DilutionFactor_ZY_uu = (TH1D *)ZY_uu_wrong->at(0)->Clone("DilutionFactor_ZY_uu");
 RelativeXsec_ZY_uu = (TH1D *)ZY_uu_total->at(0)->Clone("RelativeXsec_ZY_uu");

 Dilution_ZY_uu->Divide(ZY_uu_total->at(0));
 for(int ibin = 1; ibin <= Dilution_ZY_uu->GetNbinsX(); ibin++){
   DilutionFactor_ZY_uu->SetBinContent(ibin, 1.0 - 2.0 * Dilution_ZY_uu->GetBinContent(ibin));
   DilutionFactor_ZY_uu->SetBinError(ibin, 2.0 * Dilution_ZY_uu->GetBinError(ibin));
 }
 RelativeXsec_ZY_uu->Divide(ZRapidity->at(0));
 GetCoefficientDilution(ZY_uu_wrong->at(0), ZY_uu_total->at(0), ZRapidity->at(0), CoefficientDilution_ZY_uu);

 Dilution_ZY_uu->Write();
 DilutionFactor_ZY_uu->Write();
 RelativeXsec_ZY_uu->Write();
 CoefficientDilution_ZY_uu->Write();

 Dilution_ZY_dd = (TH1D *)ZY_dd_wrong->at(0)->Clone("Dilution_ZY_dd");
 DilutionFactor_ZY_dd = (TH1D *)ZY_dd_wrong->at(0)->Clone("DilutionFactor_ZY_dd");
 RelativeXsec_ZY_dd = (TH1D *)ZY_dd_total->at(0)->Clone("RelativeXsec_ZY_dd");

 Dilution_ZY_dd->Divide(ZY_dd_total->at(0));
 for(int ibin = 1; ibin <= Dilution_ZY_dd->GetNbinsX(); ibin++){
   DilutionFactor_ZY_dd->SetBinContent(ibin, 1.0 - 2.0 * Dilution_ZY_dd->GetBinContent(ibin));
   DilutionFactor_ZY_dd->SetBinError(ibin, 2.0 * Dilution_ZY_dd->GetBinError(ibin));
 }
 RelativeXsec_ZY_dd->Divide(ZRapidity->at(0));
 GetCoefficientDilution(ZY_dd_wrong->at(0), ZY_dd_total->at(0), ZRapidity->at(0), CoefficientDilution_ZY_dd);

 Dilution_ZY_dd->Write();
 DilutionFactor_ZY_dd->Write();
 RelativeXsec_ZY_dd->Write();
 CoefficientDilution_ZY_dd->Write();

 //Cut Efficiency in ZPt
 CutEff_ZPt_y1 = (TH1D *)ZPt_y1_Fiduc->at(0)->Clone("CutEff_ZPt_y1");
 CutEff_ZPt_y1->Divide(ZPt_y1_Total->at(0));
 CutEff_ZPt_y1->Write();

 CutEff_ZPt_y2 = (TH1D *)ZPt_y2_Fiduc->at(0)->Clone("CutEff_ZPt_y2");
 CutEff_ZPt_y2->Divide(ZPt_y2_Total->at(0));
 CutEff_ZPt_y2->Write();

 CutEff_ZPt_y3 = (TH1D *)ZPt_y3_Fiduc->at(0)->Clone("CutEff_ZPt_y3");
 CutEff_ZPt_y3->Divide(ZPt_y3_Total->at(0));
 CutEff_ZPt_y3->Write();

 CutEff_ZPt_y4 = (TH1D *)ZPt_y4_Fiduc->at(0)->Clone("CutEff_ZPt_y4");
 CutEff_ZPt_y4->Divide(ZPt_y4_Total->at(0));
 CutEff_ZPt_y4->Write();

 CutEff_ZPt_y5 = (TH1D *)ZPt_y5_Fiduc->at(0)->Clone("CutEff_ZPt_y5");
 CutEff_ZPt_y5->Divide(ZPt_y5_Total->at(0));
 CutEff_ZPt_y5->Write();

 CutEff_ZPt_y6 = (TH1D *)ZPt_y6_Fiduc->at(0)->Clone("CutEff_ZPt_y6");
 CutEff_ZPt_y6->Divide(ZPt_y6_Total->at(0));
 CutEff_ZPt_y6->Write();

 HistDivideBinWidth(ATLASZPt_2D_Fiduc->at(0), ATLASZPt_2D_Fiduc_Final, "X");
 ATLASZPt_2D_Fiduc_Final->Write();

 HistDivideBinWidth(ATLASZPt_2D_Total->at(0), ATLASZPt_2D_Total_Final, "X");
 ATLASZPt_2D_Total_Final->Write();

 HistDivideBinWidth(ATLASZPt_2D_Total_uu->at(0), ATLASZPt_2D_Total_uu_Final, "X");
 ATLASZPt_2D_Total_uu_Final->Write();

 HistDivideBinWidth(ATLASZPt_2D_Total_dd->at(0), ATLASZPt_2D_Total_dd_Final, "X");
 ATLASZPt_2D_Total_dd_Final->Write();

 HistDivideBinWidth(ATLASZPt_2D_Total_MassWindow->at(0), ATLASZPt_2D_Total_MassWindow_Final, "X");
 ATLASZPt_2D_Total_MassWindow_Final->Write();

 myLog<<"Integral of ZPt in [0, 1.5]GeV: "<<ZPt_Threshold->at(0)->GetBinContent(1)<<endl;

 QuarkA4Ratio_ZPt_uu = (TH1D *)QuarkA4_ZPt_uu->at(0)->AngularHist1D->Clone("QuarkA4Ratio_ZPt_uu");
 QuarkA4Ratio_ZPt_uu->Divide(QuarkL0_ZPt_uu->at(0)->AngularHist1D);
 QuarkA4Ratio_ZY_uu = (TH1D *)QuarkA4_ZY_uu->at(0)->AngularHist1D->Clone("QuarkA4Ratio_ZY_uu");
 QuarkA4Ratio_ZY_uu->Divide(QuarkL0_ZY_uu->at(0)->AngularHist1D);
 QuarkA4Ratio_ZPt_dd = (TH1D *)QuarkA4_ZPt_dd->at(0)->AngularHist1D->Clone("QuarkA4Ratio_ZPt_dd");
 QuarkA4Ratio_ZPt_dd->Divide(QuarkL0_ZPt_dd->at(0)->AngularHist1D);
 QuarkA4Ratio_ZY_dd = (TH1D *)QuarkA4_ZY_dd->at(0)->AngularHist1D->Clone("QuarkA4Ratio_ZY_dd");
 QuarkA4Ratio_ZY_dd->Divide(QuarkL0_ZY_dd->at(0)->AngularHist1D);

 QuarkA4Ratio_ZPt_uu->Write();
 QuarkA4Ratio_ZY_uu->Write();
 QuarkA4Ratio_ZPt_dd->Write();
 QuarkA4Ratio_ZY_dd->Write();

}
