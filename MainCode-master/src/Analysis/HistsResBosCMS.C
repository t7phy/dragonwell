#include "Analysis/HistsResBosCMS.h"

using namespace std;

void HistsResBosCMS::bookHists(int TotalThread)
{
 int CMS_mass_bin = 12;
 double RangeCMSMass[13] = {40.0, 50.0, 60.0, 76.0, 86.0, 96.0, 106.0, 120.0, 133.0, 150.0, 171.0, 200.0, 320.0};
// int CMS_mass_bin = 7;
// double RangeCMSMass[8] = {60.0, 76.0, 86.0, 96.0, 106.0, 120.0, 133.0, 150.0};
// int CMS_mass_bin = 35;
// double RangeCMSMass[36] = {60.0, 62.0, 64.0, 66.0, 68.0, 70.0, 72.0, 74.0, 76.0, 78.0, 80.0, 82.0, 84.0, 86.0, 88.0, 90.0,
//                           92.0, 94.0, 96.0, 98.0, 100.0, 102.0, 104.0, 106.0, 108.0, 110.0, 112.0, 114.0, 116.0, 118.0, 120.0,
//                           122.0, 124.0, 126.0, 128.0, 130.0};

 int CMS_ZPt_bin = 1;
 double RangeCMSZPt[2] = {0.0, 10000.0};
// int CMS_ZPt_Fine_bin = 17;
// double RangeCMSFineZPt[18] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 60.0, 80.0, 100.0, 300.0, 500.0, 1000.0, 10000.0};
 int CMS_ZPt_Fine_bin = 1;
 double RangeCMSFineZPt[2] = {0.0, 10000.0};

 int CMS_ZY_bin = 4;
 double RangeCMSZY[5] = {0.0, 1.0, 1.25, 1.5, 2.4};
// int CMS_ZY_bin = 1;
// double RangeCMSZY[2] = {2.2, 2.5};

 int ATLAS8TeVZPtBin1 = 8;
 double ATLAS8TeVZPtBinning1[9] = {45.0, 55.0, 65.0, 75.0, 85.0, 105.0, 150.0, 200.0, 900.0};

 int ATLAS8TeVZPtBin2 = 20;
 double ATLAS8TeVZPtBinning2[21] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 13.0, 16.0, 20.0, 25.0, 30.0, 37.0, 45.0, 55.0, 65.0, 75.0, 85.0,
                                105.0, 150.0, 200.0, 900.0};

 int ATLAS8TeVZPtBin3 = 43;
 double ATLAS8TeVZPtBinning3[44] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.5, 25.0, 27.5, 30.0, 33.0,
                                 36.0, 39.0, 42.0, 45.0, 48.0, 51.0, 54.0, 57.0, 61.0, 65.0, 70.0, 75.0, 80.0, 85.0, 95.0, 105.0,
                                 125.0, 150.0, 175.0, 200.0, 250.0, 300.0, 350.0, 400.0, 470.0, 550.0, 650.0, 900.0};

 int ATLAS8TeVPhiBin = 36;
 double ATLAS8TeVPhiBinning[37] =  {0.0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.051, 0.057, 0.064, 0.072,
                               0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918,
                               1.153, 1.496, 1.947, 2.522, 3.277, 5.0, 10.0};

 int ATLAS13TeVZPtBin = 43;
 double ATLAS13TeVZPtBinning[44] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.5, 25.0, 27.5, 30.0, 33.0,
                                 36.0, 39.0, 42.0, 45.0, 48.0, 51.0, 54.0, 57.0, 61.0, 65.0, 70.0, 75.0, 80.0, 85.0, 95.0, 105.0,
                                 125.0, 150.0, 175.0, 200.0, 250.0, 300.0, 350.0, 400.0, 470.0, 550.0, 650.0, 900.0};

 int ATLAS13TeVPhiBin = 36;
 double ATLAS13TeVPhiBinning[37] = {0.0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.051, 0.057, 0.064, 0.072,
                               0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918,
                               1.153, 1.496, 1.947, 2.522, 3.277, 5.0, 10.0};

 int CMS13TeVZPtBin = 35;
 double CMS13TeVZPtBinning[36] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 16.0, 18.0, 20.0, 22.0,
                               25.0, 28.0, 32.0, 37.0, 43.0, 52.0, 65.0, 85.0, 120.0, 160.0, 190.0, 220.0, 250.0, 300.0, 400.0, 500.0,
                               800.0, 1500.0};

 int CMS13TeVPhiBin = 34;
 double CMS13TeVPhiBinning[35] = {0.001, 0.002, 0.003, 0.004, 0.005, 0.006, 0.007, 0.008, 0.009, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07,
                             0.08, 0.09, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 3.0, 5.0, 7.0, 10.0, 20.0, 30.0, 50.0};

 int LHCb13TeVZPtBin = 14;
 double LHCb13TeVZPtBinning[15] = {0.0, 2.2, 3.4, 4.6, 5.8, 7.2, 8.7, 10.5, 12.8, 15.4, 19.0, 24.5, 34.0, 63.0, 270.0};

 int LHCb13TeVPhiBin = 15;
 double LHCb13TeVPhiBinning[16] = {0.002, 0.01, 0.02, 0.03, 0.05, 0.07, 0.10, 0.15, 0.20, 0.30, 0.40, 0.60, 0.80, 1.20, 2.00, 4.00};

 int CMS13TeVZPtBin1 = 33;
 double CMS13TeVZPtBinning1[34] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 16.0, 18.0, 20.0, 22.0,
                               25.0, 28.0, 32.0, 37.0, 43.0, 52.0, 65.0, 85.0, 120.0, 160.0, 190.0, 220.0, 250.0, 300.0, 400.0, 1500.0};

 int CMS13TeVyZBin = 12;
 double CMS13TeVyZBinning[13] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4};

 int ATLAS8TeVAngularBin = 23;
 double ATLAS8TeVAngularBinning[24] = {0.0, 2.5, 5,8, 11.4, 14.9, 18.5, 22.0, 25.5, 29.0, 32.6, 36.4, 40.4, 44.9, 50.2, 56.4, 63.9, 73.4, 85.4, 105.0, 132.0, 173.0, 253.0, 600.0};

 int ATLAS8TeVWEtaBin = 11;
 double ATLAS8TeVWEtaBinning[12] = {0.0, 0.21, 0.42, 0.63, 0.84, 1.05, 1.37, 1.52, 1.74, 1.95, 2.18, 2.4};

 int ATLAS7TeVZPtBin = 26;
 double ATLAS7TeVZPtBinning[27] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 22.0, 26.0, 30.0, 34.0, 38.0, 42.0, 46.0, 
                             50.0, 54.0, 60.0, 70.0, 80.0, 100.0, 150.0, 200.0, 300.0, 800.0};

 int CMS8TeVZPtBin = 18;
 double CMS8TeVZPtBinning[19] = {0.0, 2.5, 5.0, 7.5, 10.0, 12.5, 15.0, 17.5, 20.0, 30.0, 40.0, 50.0, 70.0, 90.0, 110.0, 150.0, 190.0, 250.0, 600.0};

 int CMS7TeVZPtBin = 18;
 double CMS7TeVZPtBinning[19] = {0.0, 2.5, 5.0, 7.5, 10.0, 12.5, 15.0, 17.5, 20.0, 30.0, 40.0, 50.0, 70.0, 90.0, 110.0, 150.0, 190.0, 250.0, 600.0};

 int ATLAS7TeVPhiBin = 34;
 double ATLAS7TeVPhiBinning[35] = {0.0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.051, 0.057, 0.064, 0.072,
                                0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918,
                                1.153, 1.496, 1.947, 2.522, 3.277};

 this->TotalThread = TotalThread;

 BookHist(ZY_x1, "ZY_x1", "ZY_x1", 1000, -5, 5);
 BookHist(ZY_x2, "ZY_x2", "ZY_x2", 1000, -5, 5);
 BookHist(ZY_x3, "ZY_x3", "ZY_x3", 1000, -5, 5);

 Book3DHist(FZMass_ZY_QT, "FZMass_ZY_QT", "FZMass_ZY_QT", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(BZMass_ZY_QT, "BZMass_ZY_QT", "BZMass_ZY_QT", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);

 Book3DHist(ZMass_ZY_QT, "ZMass_ZY_QT", "ZMass_ZY_QT", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(FZMass_ZY_QT_uu, "FZMass_ZY_QT_uu", "FZMass_ZY_QT_uu", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(BZMass_ZY_QT_uu, "BZMass_ZY_QT_uu", "BZMass_ZY_QT_uu", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(FZMass_ZY_QT_dd, "FZMass_ZY_QT_dd", "FZMass_ZY_QT_dd", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(BZMass_ZY_QT_dd, "BZMass_ZY_QT_dd", "BZMass_ZY_QT_dd", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);

 Book3DHist(ZMass_ZY_QT_uu, "ZMass_ZY_QT_uu", "ZMass_ZY_QT_uu", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_dd, "ZMass_ZY_QT_dd", "ZMass_ZY_QT_dd", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_ss, "ZMass_ZY_QT_ss", "ZMass_ZY_QT_ss", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_cc, "ZMass_ZY_QT_cc", "ZMass_ZY_QT_cc", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_bb, "ZMass_ZY_QT_bb", "ZMass_ZY_QT_bb", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);

 Book3DHist(ZMass_ZY_QT_uu_total, "ZMass_ZY_QT_uu_total", "ZMass_ZY_QT_uu_total", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_uu_wrong, "ZMass_ZY_QT_uu_wrong", "ZMass_ZY_QT_uu_wrong", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_dd_total, "ZMass_ZY_QT_dd_total", "ZMass_ZY_QT_dd_total", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_dd_wrong, "ZMass_ZY_QT_dd_wrong", "ZMass_ZY_QT_dd_wrong", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);

 Book3DHist(ZMass_ZY_QT_uu_YP_wrong, "ZMass_ZY_QT_uu_YP_wrong", "ZMass_ZY_QT_uu_YP_wrong", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_uu_YP_right, "ZMass_ZY_QT_uu_YP_right", "ZMass_ZY_QT_uu_YP_right", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_uu_YM_wrong, "ZMass_ZY_QT_uu_YM_wrong", "ZMass_ZY_QT_uu_YM_wrong", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_uu_YM_right, "ZMass_ZY_QT_uu_YM_right", "ZMass_ZY_QT_uu_YM_right", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);

 Book3DHist(ZMass_ZY_QT_dd_YP_wrong, "ZMass_ZY_QT_dd_YP_wrong", "ZMass_ZY_QT_dd_YP_wrong", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_dd_YP_right, "ZMass_ZY_QT_dd_YP_right", "ZMass_ZY_QT_dd_YP_right", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_dd_YM_wrong, "ZMass_ZY_QT_dd_YM_wrong", "ZMass_ZY_QT_dd_YM_wrong", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_dd_YM_right, "ZMass_ZY_QT_dd_YM_right", "ZMass_ZY_QT_dd_YM_right", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);

 Book3DHist(ZMass_ZY_QT_YP, "ZMass_ZY_QT_YP", "ZMass_ZY_QT_YP", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_YM, "ZMass_ZY_QT_YM", "ZMass_ZY_QT_YM", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);

 if(RootType != "FittingCMSData"){
   BookAngularHist(A0_Mass_ZY_QT_uu, "A0_Mass_ZY_QT_uu", "A0", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
   BookAngularHist(A0_Mass_ZY_QT_dd, "A0_Mass_ZY_QT_dd", "A0", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
   BookAngularHist(A0_Mass_ZY_QT_ss, "A0_Mass_ZY_QT_ss", "A0", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
   BookAngularHist(A0_Mass_ZY_QT_cc, "A0_Mass_ZY_QT_cc", "A0", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
   BookAngularHist(A0_Mass_ZY_QT_bb, "A0_Mass_ZY_QT_bb", "A0", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 }


 BookHist(ZpT_Inclusive, "ZpT_Inclusive", "ZpT_Inclusive", ATLAS8TeVZPtBin3, ATLAS8TeVZPtBinning3);
 BookHist(ATLAS8TeV_pT_Mass12_20_Theory, "ATLAS8TeV_pT_Mass12_20_Theory", "ATLAS8TeV_pT_Mass12_20_Theory", ATLAS8TeVZPtBin1, ATLAS8TeVZPtBinning1);
 BookHist(ATLAS8TeV_pT_Mass20_30_Theory, "ATLAS8TeV_pT_Mass20_30_Theory", "ATLAS8TeV_pT_Mass20_30_Theory", ATLAS8TeVZPtBin1, ATLAS8TeVZPtBinning1);
 BookHist(ATLAS8TeV_pT_Mass30_46_Theory, "ATLAS8TeV_pT_Mass30_46_Theory", "ATLAS8TeV_pT_Mass30_46_Theory", ATLAS8TeVZPtBin1, ATLAS8TeVZPtBinning1);
 BookHist(ATLAS8TeV_pT_Mass46_66_Theory, "ATLAS8TeV_pT_Mass46_66_Theory", "ATLAS8TeV_pT_Mass46_66_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Mass66_116_Theory, "ATLAS8TeV_pT_Mass66_116_Theory", "ATLAS8TeV_pT_Mass66_116_Theory", ATLAS8TeVZPtBin3, ATLAS8TeVZPtBinning3);
 BookHist(ATLAS8TeV_pT_Mass116_150_Theory, "ATLAS8TeV_pT_Mass116_150_Theory", "ATLAS8TeV_pT_Mass116_150_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);

 BookHist(ATLAS8TeV_Phi_Y1_Theory, "ATLAS8TeV_Phi_Y1_Theory", "ATLAS8TeV_Phi_Y1_Theory", ATLAS8TeVPhiBin, ATLAS8TeVPhiBinning);
 BookHist(ATLAS8TeV_Phi_Y2_Theory, "ATLAS8TeV_Phi_Y2_Theory", "ATLAS8TeV_Phi_Y2_Theory", ATLAS8TeVPhiBin, ATLAS8TeVPhiBinning);
 BookHist(ATLAS8TeV_Phi_Y3_Theory, "ATLAS8TeV_Phi_Y3_Theory", "ATLAS8TeV_Phi_Y3_Theory", ATLAS8TeVPhiBin, ATLAS8TeVPhiBinning);
 BookHist(ATLAS8TeV_Phi_Y4_Theory, "ATLAS8TeV_Phi_Y4_Theory", "ATLAS8TeV_Phi_Y4_Theory", ATLAS8TeVPhiBin, ATLAS8TeVPhiBinning);
 BookHist(ATLAS8TeV_Phi_Y5_Theory, "ATLAS8TeV_Phi_Y5_Theory", "ATLAS8TeV_Phi_Y5_Theory", ATLAS8TeVPhiBin, ATLAS8TeVPhiBinning);
 BookHist(ATLAS8TeV_Phi_Y6_Theory, "ATLAS8TeV_Phi_Y6_Theory", "ATLAS8TeV_Phi_Y6_Theory", ATLAS8TeVPhiBin, ATLAS8TeVPhiBinning);
 BookHist(ATLAS8TeV_pT_Y1_Theory, "ATLAS8TeV_pT_Y1_Theory", "ATLAS8TeV_pT_Y1_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y2_Theory, "ATLAS8TeV_pT_Y2_Theory", "ATLAS8TeV_pT_Y2_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y3_Theory, "ATLAS8TeV_pT_Y3_Theory", "ATLAS8TeV_pT_Y3_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y4_Theory, "ATLAS8TeV_pT_Y4_Theory", "ATLAS8TeV_pT_Y4_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y5_Theory, "ATLAS8TeV_pT_Y5_Theory", "ATLAS8TeV_pT_Y5_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y6_Theory, "ATLAS8TeV_pT_Y6_Theory", "ATLAS8TeV_pT_Y6_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y1_Total, "ATLAS8TeV_pT_Y1_Total", "ATLAS8TeV_pT_Y1_Total", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y2_Total, "ATLAS8TeV_pT_Y2_Total", "ATLAS8TeV_pT_Y2_Total", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y3_Total, "ATLAS8TeV_pT_Y3_Total", "ATLAS8TeV_pT_Y3_Total", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y4_Total, "ATLAS8TeV_pT_Y4_Total", "ATLAS8TeV_pT_Y4_Total", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y5_Total, "ATLAS8TeV_pT_Y5_Total", "ATLAS8TeV_pT_Y5_Total", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y6_Total, "ATLAS8TeV_pT_Y6_Total", "ATLAS8TeV_pT_Y6_Total", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y1_uu_Theory, "ATLAS8TeV_pT_Y1_uu_Theory", "ATLAS8TeV_pT_Y1_uu_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y2_uu_Theory, "ATLAS8TeV_pT_Y2_uu_Theory", "ATLAS8TeV_pT_Y2_uu_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y3_uu_Theory, "ATLAS8TeV_pT_Y3_uu_Theory", "ATLAS8TeV_pT_Y3_uu_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y4_uu_Theory, "ATLAS8TeV_pT_Y4_uu_Theory", "ATLAS8TeV_pT_Y4_uu_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y5_uu_Theory, "ATLAS8TeV_pT_Y5_uu_Theory", "ATLAS8TeV_pT_Y5_uu_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y6_uu_Theory, "ATLAS8TeV_pT_Y6_uu_Theory", "ATLAS8TeV_pT_Y6_uu_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y1_dd_Theory, "ATLAS8TeV_pT_Y1_dd_Theory", "ATLAS8TeV_pT_Y1_dd_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y2_dd_Theory, "ATLAS8TeV_pT_Y2_dd_Theory", "ATLAS8TeV_pT_Y2_dd_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y3_dd_Theory, "ATLAS8TeV_pT_Y3_dd_Theory", "ATLAS8TeV_pT_Y3_dd_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y4_dd_Theory, "ATLAS8TeV_pT_Y4_dd_Theory", "ATLAS8TeV_pT_Y4_dd_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y5_dd_Theory, "ATLAS8TeV_pT_Y5_dd_Theory", "ATLAS8TeV_pT_Y5_dd_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS8TeV_pT_Y6_dd_Theory, "ATLAS8TeV_pT_Y6_dd_Theory", "ATLAS8TeV_pT_Y6_dd_Theory", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(ATLAS13TeV_pT_Theory, "ATLAS13TeV_pT_Theory", "ATLAS13TeV_pT_Theory", ATLAS13TeVZPtBin, ATLAS13TeVZPtBinning);
 BookHist(ATLAS13TeV_Phi_Theory, "ATLAS13TeV_Phi_Theory", "ATLAS13TeV_Phi_Theory", ATLAS13TeVPhiBin, ATLAS13TeVPhiBinning);
 BookHist(CMS13TeV_pT_Theory, "CMS13TeV_pT_Theory", "CMS13TeV_pT_Theory", CMS13TeVZPtBin, CMS13TeVZPtBinning);
 BookHist(CMS13TeV_Phi_Theory, "CMS13TeV_Phi_Theory", "CMS13TeV_Phi_Theory", CMS13TeVPhiBin, CMS13TeVPhiBinning);
 BookHist(LHCb13TeV_pT_Theory, "LHCb13TeV_pT_Theory", "LHCb13TeV_pT_Theory", LHCb13TeVZPtBin, LHCb13TeVZPtBinning);
 BookHist(LHCb13TeV_pT_Total, "LHCb13TeV_pT_Total", "LHCb13TeV_pT_Total", LHCb13TeVZPtBin, LHCb13TeVZPtBinning);
 BookHist(LHCb13TeV_pT_uu_Theory, "LHCb13TeV_pT_uu_Theory", "LHCb13TeV_pT_uu_Theory", LHCb13TeVZPtBin, LHCb13TeVZPtBinning);
 BookHist(LHCb13TeV_pT_dd_Theory, "LHCb13TeV_pT_dd_Theory", "LHCb13TeV_pT_dd_Theory", LHCb13TeVZPtBin, LHCb13TeVZPtBinning);
 BookHist(LHCb13TeV_Phi_Theory, "LHCb13TeV_Phi_Theory", "LHCb13TeV_Phi_Theory", LHCb13TeVPhiBin, LHCb13TeVPhiBinning);
 BookHist(CMS13TeV_pT_Y1_Theory, "CMS13TeV_pT_Y1_Theory", "CMS13TeV_pT_Y1_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y2_Theory, "CMS13TeV_pT_Y2_Theory", "CMS13TeV_pT_Y2_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y3_Theory, "CMS13TeV_pT_Y3_Theory", "CMS13TeV_pT_Y3_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y4_Theory, "CMS13TeV_pT_Y4_Theory", "CMS13TeV_pT_Y4_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y5_Theory, "CMS13TeV_pT_Y5_Theory", "CMS13TeV_pT_Y5_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y1_Total, "CMS13TeV_pT_Y1_Total", "CMS13TeV_pT_Y1_Total", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y2_Total, "CMS13TeV_pT_Y2_Total", "CMS13TeV_pT_Y2_Total", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y3_Total, "CMS13TeV_pT_Y3_Total", "CMS13TeV_pT_Y3_Total", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y4_Total, "CMS13TeV_pT_Y4_Total", "CMS13TeV_pT_Y4_Total", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y5_Total, "CMS13TeV_pT_Y5_Total", "CMS13TeV_pT_Y5_Total", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y1_uu_Theory, "CMS13TeV_pT_Y1_uu_Theory", "CMS13TeV_pT_Y1_uu_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y2_uu_Theory, "CMS13TeV_pT_Y2_uu_Theory", "CMS13TeV_pT_Y2_uu_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y3_uu_Theory, "CMS13TeV_pT_Y3_uu_Theory", "CMS13TeV_pT_Y3_uu_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y4_uu_Theory, "CMS13TeV_pT_Y4_uu_Theory", "CMS13TeV_pT_Y4_uu_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y5_uu_Theory, "CMS13TeV_pT_Y5_uu_Theory", "CMS13TeV_pT_Y5_uu_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y1_dd_Theory, "CMS13TeV_pT_Y1_dd_Theory", "CMS13TeV_pT_Y1_dd_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y2_dd_Theory, "CMS13TeV_pT_Y2_dd_Theory", "CMS13TeV_pT_Y2_dd_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y3_dd_Theory, "CMS13TeV_pT_Y3_dd_Theory", "CMS13TeV_pT_Y3_dd_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y4_dd_Theory, "CMS13TeV_pT_Y4_dd_Theory", "CMS13TeV_pT_Y4_dd_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_pT_Y5_dd_Theory, "CMS13TeV_pT_Y5_dd_Theory", "CMS13TeV_pT_Y5_dd_Theory", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 BookHist(CMS13TeV_yZ_Theory, "CMS13TeV_yZ_Theory", "CMS13TeV_yZ_Theory", CMS13TeVyZBin, CMS13TeVyZBinning);
 BookHist(CMS13TeV_yZ_Total, "CMS13TeV_yZ_Total", "CMS13TeV_yZ_Total", CMS13TeVyZBin, CMS13TeVyZBinning);
 BookHist(LHCb13TeV_yZ_Theory, "LHCb13TeV_yZ_Theory", "LHCb13TeV_yZ_Theory", 500, -5, 5);
 BookHist(ATLAS8TeV_WPlus_Eta_Theory, "ATLAS8TeV_WPlus_Eta_Theory", "ATLAS8TeV_WPlus_Eta_Theory", ATLAS8TeVWEtaBin, ATLAS8TeVWEtaBinning);
 BookHist(ATLAS8TeV_WMinus_Eta_Theory, "ATLAS8TeV_WMinus_Eta_Theory", "ATLAS8TeV_WMinus_Eta_Theory", ATLAS8TeVWEtaBin, ATLAS8TeVWEtaBinning);
 BookHist(ATLAS7TeV_pT_Theory, "ATLAS7TeV_pT_Theory", "ATLAS7TeV_pT_Theory", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);
 BookHist(ATLAS7TeV_pT_Y1_Theory, "ATLAS7TeV_pT_Y1_Theory", "ATLAS7TeV_pT_Y1_Theory", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);
 BookHist(ATLAS7TeV_pT_Y2_Theory, "ATLAS7TeV_pT_Y2_Theory", "ATLAS7TeV_pT_Y2_Theory", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);
 BookHist(ATLAS7TeV_pT_Y3_Theory, "ATLAS7TeV_pT_Y3_Theory", "ATLAS7TeV_pT_Y3_Theory", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);
 BookHist(CMS8TeV_pT_Theory, "CMS8TeV_pT_Theory", "CMS8TeV_pT_Theory", CMS8TeVZPtBin, CMS8TeVZPtBinning);
 BookHist(CMS7TeV_pT_Theory, "CMS7TeV_pT_Theory", "CMS7TeV_pT_Theory", CMS7TeVZPtBin, CMS7TeVZPtBinning);
 BookHist(ATLAS7TeV_Phi_Theory, "ATLAS7TeV_Phi_Theory", "ATLAS7TeV_Phi_Theory", ATLAS7TeVPhiBin, ATLAS7TeVPhiBinning);
 BookHist(ATLAS7TeV_Phi_Y1_Theory, "ATLAS7TeV_Phi_Y1_Theory", "ATLAS7TeV_Phi_Y1_Theory", ATLAS7TeVPhiBin, ATLAS7TeVPhiBinning);
 BookHist(ATLAS7TeV_Phi_Y2_Theory, "ATLAS7TeV_Phi_Y2_Theory", "ATLAS7TeV_Phi_Y2_Theory", ATLAS7TeVPhiBin, ATLAS7TeVPhiBinning);
 BookHist(ATLAS7TeV_Phi_Y3_Theory, "ATLAS7TeV_Phi_Y3_Theory", "ATLAS7TeV_Phi_Y3_Theory", ATLAS7TeVPhiBin, ATLAS7TeVPhiBinning);

 BookAngularHist(ATLAS8TeV_A0_pT_Theory, "ATLAS8TeV_A0_pT_Theory_Final", "A0", ATLAS8TeVAngularBin, ATLAS8TeVAngularBinning);
 BookAngularHist(ATLAS8TeV_A1_pT_Theory, "ATLAS8TeV_A1_pT_Theory_Final", "A1", ATLAS8TeVAngularBin, ATLAS8TeVAngularBinning);
 BookAngularHist(ATLAS8TeV_A2_pT_Theory, "ATLAS8TeV_A2_pT_Theory_Final", "A2", ATLAS8TeVAngularBin, ATLAS8TeVAngularBinning);
 BookAngularHist(ATLAS8TeV_A3_pT_Theory, "ATLAS8TeV_A3_pT_Theory_Final", "A3", ATLAS8TeVAngularBin, ATLAS8TeVAngularBinning);
 BookAngularHist(ATLAS8TeV_A4_pT_Theory, "ATLAS8TeV_A4_pT_Theory_Final", "A4", ATLAS8TeVAngularBin, ATLAS8TeVAngularBinning);
 BookAngularHist(ATLAS8TeV_A02_pT_Theory, "ATLAS8TeV_A02_pT_Theory_Final", "A02", ATLAS8TeVAngularBin, ATLAS8TeVAngularBinning);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 /////////////////////////////
 // CTEQ Drell-Yan k-factor //
 /////////////////////////////

 vector<double> E245_LHCb7TeV_Z_binning = {2.0, 2.125, 2.25, 2.375, 2.5, 2.625, 2.75, 2.875, 3.0, 3.125, 3.25, 3.375, 3.5, 3.625, 3.75, 3.875, 4.0, 4.25};
 vector<double> E245_LHCb7TeV_W_binning = {2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 4.0, 4.5};
 vector<double> E246_LHCb8TeV_Z_binning = {2.0, 2.125, 2.25, 2.375, 2.5, 2.625, 2.75, 2.875, 3.0, 3.125, 3.25, 3.375, 3.5, 3.625, 3.75, 3.875, 4.0, 4.25};
 vector<double> E248_ATLAS7TeV_W_binning = {0.00, 0.21, 0.42, 0.63, 0.84, 1.05, 1.37, 1.52, 1.74, 1.95, 2.18, 2.50};
 vector<double> E249_CMS8TeV_W_binning = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.85, 2.1, 2.4};
 vector<double> E250_LHCb8TeV_Z_binning = {2.0, 2.125, 2.25, 2.375, 2.5, 2.625, 2.75, 2.875, 3.0, 3.125, 3.25, 3.375, 3.5, 3.625, 3.75, 3.875, 4.0, 4.25, 4.5};
 vector<double> E250_LHCb8TeV_W_binning = {2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 4.0, 4.5};
 vector<double> E225_CDF1p8TeV_W_binning = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.45, 1.7, 1.9, 2.1, 2.5};
 vector<double> E227_CDF1p96TeV_W_binning = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.45, 1.7, 1.9, 2.1, 2.5};
 vector<double> E234_D01p96TeV_W_binning = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 2.0};
 vector<double> E261_CDF1p96_Z_binning = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9};
 vector<double> E266_CMS7TeV_W_binning = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.85, 2.1, 2.4};
 vector<double> E281_D01p96TeV_W_binning = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.6, 1.8, 2.0, 2.2, 2.4, 2.7, 3.2};
 vector<double> E211_ATLAS8TeV_W_binning = {0.0, 0.21, 0.42, 0.63, 0.84, 1.05, 1.37, 1.52, 1.74, 1.95, 2.18, 2.4};
 vector<double> E218_LHCb13TeV_Z_binning = {2.125, 2.25, 2.375, 2.5, 2.625, 2.75, 2.875, 3.0, 3.125, 3.25, 3.375, 3.5, 3.625, 3.75, 3.875, 4.0, 4.25, 4.5};
 vector<double> E214_ATLAS8TeV_Z_costheta_binning = {-1.0, -0.7, -0.4, 0.0, 0.4, 0.7, 1.0};
 vector<double> E214_ATLAS8TeV_Z_rapidity_binning = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4};
 vector<double> E215_ATLAS5TeV_W_binning = {0.0, 0.21, 0.42, 0.63, 0.84, 1.05, 1.37, 1.52, 1.74, 1.95, 2.18, 2.5};
 vector<double> E217_LHCb8TeV_W_binning = {2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75};

 BookHist(E245_LHCb7TeV_Z, "E245_LHCb7TeV_Z", "E245_LHCb7TeV_Z", E245_LHCb7TeV_Z_binning.size() - 1, &E245_LHCb7TeV_Z_binning[0]);
 BookHist(E245_LHCb7TeV_WPlus, "E245_LHCb7TeV_WPlus", "E245_LHCb7TeV_WPlus", E245_LHCb7TeV_W_binning.size() - 1, &E245_LHCb7TeV_W_binning[0]);
 BookHist(E245_LHCb7TeV_WMinus, "E245_LHCb7TeV_WMinus", "E245_LHCb7TeV_WMinus", E245_LHCb7TeV_W_binning.size() - 1, &E245_LHCb7TeV_W_binning[0]);

 BookHist(E246_LHCb8TeV_Z, "E246_LHCb8TeV_Z", "E246_LHCb8TeV_Z", E246_LHCb8TeV_Z_binning.size() - 1, &E246_LHCb8TeV_Z_binning[0]);

 BookHist(E248_ATLAS7TeV_Z, "E248_ATLAS7TeV_Z", "E248_ATLAS7TeV_Z", 12, 0.0, 2.4);
 BookHist(E248_ATLAS7TeV_WPlus, "E248_ATLAS7TeV_WPlus", "E248_ATLAS7TeV_WPlus", E248_ATLAS7TeV_W_binning.size() - 1, &E248_ATLAS7TeV_W_binning[0]);
 BookHist(E248_ATLAS7TeV_WMinus, "E248_ATLAS7TeV_WMinus", "E248_ATLAS7TeV_WMinus", E248_ATLAS7TeV_W_binning.size() - 1, &E248_ATLAS7TeV_W_binning[0]);

 BookHist(E249_CMS8TeV_WPlus, "E249_CMS8TeV_WPlus", "E249_CMS8TeV_WPlus", E249_CMS8TeV_W_binning.size() - 1, &E249_CMS8TeV_W_binning[0]);
 BookHist(E249_CMS8TeV_WMinus, "E249_CMS8TeV_WMinus", "E249_CMS8TeV_WMinus", E249_CMS8TeV_W_binning.size() - 1, &E249_CMS8TeV_W_binning[0]);

 BookHist(E250_LHCb8TeV_Z, "E250_LHCb8TeV_Z", "E250_LHCb8TeV_Z", E250_LHCb8TeV_Z_binning.size() - 1, &E250_LHCb8TeV_Z_binning[0]);
 BookHist(E250_LHCb8TeV_WPlus, "E250_LHCb8TeV_WPlus", "E250_LHCb8TeV_WPlus", E250_LHCb8TeV_W_binning.size() - 1, &E250_LHCb8TeV_W_binning[0]);
 BookHist(E250_LHCb8TeV_WMinus, "E250_LHCb8TeV_WMinus", "E250_LHCb8TeV_WMinus", E250_LHCb8TeV_W_binning.size() - 1, &E250_LHCb8TeV_W_binning[0]);

 BookHist(E253_ATLAS8TeV_ZPt1, "E253_ATLAS8TeV_ZPt1", "E253_ATLAS8TeV_ZPt1", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 BookHist(E253_ATLAS8TeV_ZPt2, "E253_ATLAS8TeV_ZPt2", "E253_ATLAS8TeV_ZPt2", ATLAS8TeVZPtBin3, ATLAS8TeVZPtBinning3);
 BookHist(E253_ATLAS8TeV_ZPt3, "E253_ATLAS8TeV_ZPt3", "E253_ATLAS8TeV_ZPt3", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);

 BookHist(E225_CDF1p8TeV_WPlus, "E225_CDF1p8TeV_WPlus", "E225_CDF1p8TeV_WPlus", E225_CDF1p8TeV_W_binning.size() - 1, &E225_CDF1p8TeV_W_binning[0]);
 BookHist(E225_CDF1p8TeV_WMinus, "E225_CDF1p8TeV_WMinus", "E225_CDF1p8TeV_WMinus", E225_CDF1p8TeV_W_binning.size() - 1, &E225_CDF1p8TeV_W_binning[0]);

 BookHist(E227_CDF1p96TeV_WPlus, "E227_CDF1p96TeV_WPlus", "E227_CDF1p96TeV_WPlus", E227_CDF1p96TeV_W_binning.size() - 1, &E227_CDF1p96TeV_W_binning[0]);
 BookHist(E227_CDF1p96TeV_WMinus, "E227_CDF1p96TeV_WMinus", "E227_CDF1p96TeV_WMinus", E227_CDF1p96TeV_W_binning.size() - 1, &E227_CDF1p96TeV_W_binning[0]);

 BookHist(E234_D01p96TeV_WPlus, "E234_D01p96TeV_WPlus", "E234_D01p96TeV_WPlus", E234_D01p96TeV_W_binning.size() - 1, &E234_D01p96TeV_W_binning[0]);
 BookHist(E234_D01p96TeV_WMinus, "E234_D01p96TeV_WMinus", "E234_D01p96TeV_WMinus", E234_D01p96TeV_W_binning.size() - 1, &E234_D01p96TeV_W_binning[0]);

 BookHist(E260_D01p96TeV_Z, "E260_D01p96TeV_Z", "E260_D01p96TeV_Z", 28, 0.0, 2.8);

 BookHist(E261_CDF1p96TeV_Z, "E261_CDF1p96TeV_Z", "E261_CDF1p96TeV_Z", E261_CDF1p96_Z_binning.size() - 1, &E261_CDF1p96_Z_binning[0]);

 BookHist(E266_CMS7TeV_WPlus, "E266_CMS7TeV_WPlus", "E266_CMS7TeV_WPlus", E266_CMS7TeV_W_binning.size() - 1, &E266_CMS7TeV_W_binning[0]);
 BookHist(E266_CMS7TeV_WMinus, "E266_CMS7TeV_WMinus", "E266_CMS7TeV_WMinus", E266_CMS7TeV_W_binning.size() - 1, &E266_CMS7TeV_W_binning[0]);

 BookHist(E267_CMS7TeV_WPlus, "E267_CMS7TeV_WPlus", "E267_CMS7TeV_WPlus", 12, 0.0, 2.4);
 BookHist(E267_CMS7TeV_WMinus, "E267_CMS7TeV_WMinus", "E267_CMS7TeV_WMinus", 12, 0.0, 2.4);

 BookHist(E281_D01p96TeV_WPlus, "E281_D01p96TeV_WPlus", "E281_D01p96TeV_WPlus", E281_D01p96TeV_W_binning.size() - 1, &E281_D01p96TeV_W_binning[0]);
 BookHist(E281_D01p96TeV_WMinus, "E281_D01p96TeV_WMinus", "E281_D01p96TeV_WMinus", E281_D01p96TeV_W_binning.size() - 1, &E281_D01p96TeV_W_binning[0]);

 BookHist(E211_ATLAS8TeV_WPlus, "E211_ATLAS8TeV_WPlus", "E211_ATLAS8TeV_WPlus", E211_ATLAS8TeV_W_binning.size() - 1, &E211_ATLAS8TeV_W_binning[0]);
 BookHist(E211_ATLAS8TeV_WMinus, "E211_ATLAS8TeV_WMinus", "E211_ATLAS8TeV_WMinus", E211_ATLAS8TeV_W_binning.size() - 1, &E211_ATLAS8TeV_W_binning[0]);

 BookHist(E212_CMS13TeV_Z, "E212_CMS13TeV_Z", "E212_CMS13TeV_Z", 12, 0.0, 2.4);

 BookHist(E218_LHCb13TeV_Z, "E218_LHCb13TeV_Z", "E218_LHCb13TeV_Z", E218_LHCb13TeV_Z_binning.size() - 1, &E218_LHCb13TeV_Z_binning[0]);

 Book2DHist(E214_ATLAS8TeV_Z1, "E214_ATLAS8TeV_Z1", "E214_ATLAS8TeV_Z1", E214_ATLAS8TeV_Z_rapidity_binning.size() - 1, &E214_ATLAS8TeV_Z_rapidity_binning[0], E214_ATLAS8TeV_Z_costheta_binning.size() - 1, &E214_ATLAS8TeV_Z_costheta_binning[0]);
 Book2DHist(E214_ATLAS8TeV_Z2, "E214_ATLAS8TeV_Z2", "E214_ATLAS8TeV_Z2", E214_ATLAS8TeV_Z_rapidity_binning.size() - 1, &E214_ATLAS8TeV_Z_rapidity_binning[0], E214_ATLAS8TeV_Z_costheta_binning.size() - 1, &E214_ATLAS8TeV_Z_costheta_binning[0]);
 Book2DHist(E214_ATLAS8TeV_Z3, "E214_ATLAS8TeV_Z3", "E214_ATLAS8TeV_Z3", E214_ATLAS8TeV_Z_rapidity_binning.size() - 1, &E214_ATLAS8TeV_Z_rapidity_binning[0], E214_ATLAS8TeV_Z_costheta_binning.size() - 1, &E214_ATLAS8TeV_Z_costheta_binning[0]);
 Book2DHist(E214_ATLAS8TeV_Z4, "E214_ATLAS8TeV_Z4", "E214_ATLAS8TeV_Z4", E214_ATLAS8TeV_Z_rapidity_binning.size() - 1, &E214_ATLAS8TeV_Z_rapidity_binning[0], E214_ATLAS8TeV_Z_costheta_binning.size() - 1, &E214_ATLAS8TeV_Z_costheta_binning[0]);
 Book2DHist(E214_ATLAS8TeV_Z5, "E214_ATLAS8TeV_Z5", "E214_ATLAS8TeV_Z5", E214_ATLAS8TeV_Z_rapidity_binning.size() - 1, &E214_ATLAS8TeV_Z_rapidity_binning[0], E214_ATLAS8TeV_Z_costheta_binning.size() - 1, &E214_ATLAS8TeV_Z_costheta_binning[0]);
 Book2DHist(E214_ATLAS8TeV_Z6, "E214_ATLAS8TeV_Z6", "E214_ATLAS8TeV_Z6", E214_ATLAS8TeV_Z_rapidity_binning.size() - 1, &E214_ATLAS8TeV_Z_rapidity_binning[0], E214_ATLAS8TeV_Z_costheta_binning.size() - 1, &E214_ATLAS8TeV_Z_costheta_binning[0]);

 BookHist(E215_ATLAS5TeV_Z, "E215_ATLAS5TeV_Z", "E215_ATLAS5TeV_Z", 5, 0.0, 2.5);
 BookHist(E215_ATLAS5TeV_WPlus, "E215_ATLAS5TeV_WPlus", "E215_ATLAS5TeV_WPlus", E215_ATLAS5TeV_W_binning.size() - 1, &E215_ATLAS5TeV_W_binning[0]);
 BookHist(E215_ATLAS5TeV_WMinus, "E215_ATLAS5TeV_WMinus", "E215_ATLAS5TeV_WMinus", E215_ATLAS5TeV_W_binning.size() - 1, &E215_ATLAS5TeV_W_binning[0]);

 BookHist(E217_LHCb8TeV_WPlus, "E217_LHCb8TeV_WPlus", "E217_LHCb8TeV_WPlus", E217_LHCb8TeV_W_binning.size() - 1, &E217_LHCb8TeV_W_binning[0]);
 BookHist(E217_LHCb8TeV_WMinus, "E217_LHCb8TeV_WMinus", "E217_LHCb8TeV_WMinus", E217_LHCb8TeV_W_binning.size() - 1, &E217_LHCb8TeV_W_binning[0]);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 BookHist(ZPt_FineBin, "ZPt_FineBin", "ZPt_FineBin", 200, 0, 20);
 BookHist(ZPt_FineBin_HighPt, "ZPt_FineBin_HighPt", "ZPt_FineBin_HighPt", 400, 0, 200);

 BookHist(TotalCrossSection_8TeV, "TotalCrossSection_8TeV", "TotalCrossSection_8TeV", 1, 0, 100);

 vector<double> NNLOJetYBin = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
 vector<double> NNLOJetQTBin = {0.5, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 
                               24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 70.0, 80.0, 90.0, 100.0, 125.0, 150.0, 175.0, 200.0, 
                               300.0, 400.0, 500.0, 1000.0};
 Book2DHist(WPlusYQT, "WPlusYQT", "WPlusYQT", NNLOJetYBin.size() - 1, &NNLOJetYBin[0], NNLOJetQTBin.size() - 1, &NNLOJetQTBin[0]);

 AFB_Mass_ZY_ZPt = (TH3D *)FZMass_ZY_QT->at(0)->Clone("AFB_ZMass_ZY_QT");
 AFB_Mass_ZY_ZPt->Reset();

 AFB_Mass_ZY_ZPt_uu = (TH3D *)FZMass_ZY_QT_uu->at(0)->Clone("AFB_ZMass_ZY_QT_uu");
 AFB_Mass_ZY_ZPt_uu->Reset();
 AFB_Mass_ZY_ZPt_dd = (TH3D *)FZMass_ZY_QT_dd->at(0)->Clone("AFB_ZMass_ZY_QT_dd");
 AFB_Mass_ZY_ZPt_dd->Reset();

}

void HistsResBosCMS::outputInformation()
{
 //AFB vs Mass ZY ZPt
 AFBFunction(FZMass_ZY_QT->at(0), BZMass_ZY_QT->at(0), AFB_Mass_ZY_ZPt);

 if(RootType != "FittingCMSData"){
   //quark level AFB vs Mass ZY ZPt
   AFBFunction(FZMass_ZY_QT_uu->at(0), BZMass_ZY_QT_uu->at(0), AFB_Mass_ZY_ZPt_uu);
   AFBFunction(FZMass_ZY_QT_dd->at(0), BZMass_ZY_QT_dd->at(0), AFB_Mass_ZY_ZPt_dd);

   //Dilution
   GetCoefficientDilution(ZMass_ZY_QT_uu_wrong->at(0), ZMass_ZY_QT_uu_total->at(0), ZMass_ZY_QT->at(0), CoefficientDilution_ZMass_ZY_QT_uu);
   GetCoefficientDilution(ZMass_ZY_QT_dd_wrong->at(0), ZMass_ZY_QT_dd_total->at(0), ZMass_ZY_QT->at(0), CoefficientDilution_ZMass_ZY_QT_dd);

   GetDilutionAverage(CoefficientDilution_ZMass_ZY_QT_uu, DilutionAverage_ZMass_ZY_QT_uu, ResidualDilution_ZMass_ZY_QT_uu);
   GetDilutionAverage(CoefficientDilution_ZMass_ZY_QT_dd, DilutionAverage_ZMass_ZY_QT_dd, ResidualDilution_ZMass_ZY_QT_dd);

   GetDilutionMeta(ZMass_ZY_QT_uu_wrong->at(0), ZMass_ZY_QT_uu_total->at(0), ZMass_ZY_QT->at(0), OneMinusTwoD_uu, RelativeCrossSection_uu);
   GetDilutionMeta(ZMass_ZY_QT_dd_wrong->at(0), ZMass_ZY_QT_dd_total->at(0), ZMass_ZY_QT->at(0), OneMinusTwoD_dd, RelativeCrossSection_dd);
 }

 ReadData();

 ATLAS8TeV_Phi_Y1_Theory->at(0)->Scale(1.0 / ATLAS8TeV_Phi_Y1_Theory->at(0)->Integral());
 ATLAS8TeV_Phi_Y2_Theory->at(0)->Scale(1.0 / ATLAS8TeV_Phi_Y2_Theory->at(0)->Integral());
 ATLAS8TeV_Phi_Y3_Theory->at(0)->Scale(1.0 / ATLAS8TeV_Phi_Y3_Theory->at(0)->Integral());
 ATLAS8TeV_Phi_Y4_Theory->at(0)->Scale(1.0 / ATLAS8TeV_Phi_Y4_Theory->at(0)->Integral());
 ATLAS8TeV_Phi_Y5_Theory->at(0)->Scale(1.0 / ATLAS8TeV_Phi_Y5_Theory->at(0)->Integral());
 ATLAS8TeV_Phi_Y6_Theory->at(0)->Scale(1.0 / ATLAS8TeV_Phi_Y6_Theory->at(0)->Integral());

 ATLAS13TeV_pT_Theory->at(0)->Scale(1.0 / ATLAS13TeV_pT_Theory->at(0)->Integral());
 ATLAS13TeV_Phi_Theory->at(0)->Scale(1.0 / ATLAS13TeV_Phi_Theory->at(0)->Integral());

 ATLAS7TeV_pT_Theory->at(0)->Scale(1.0 / ATLAS7TeV_pT_Theory->at(0)->Integral());
 ATLAS7TeV_pT_Y1_Theory->at(0)->Scale(1.0 / ATLAS7TeV_pT_Y1_Theory->at(0)->Integral());
 ATLAS7TeV_pT_Y2_Theory->at(0)->Scale(1.0 / ATLAS7TeV_pT_Y2_Theory->at(0)->Integral());
 ATLAS7TeV_pT_Y3_Theory->at(0)->Scale(1.0 / ATLAS7TeV_pT_Y3_Theory->at(0)->Integral());

 CMS8TeV_pT_Theory->at(0)->Scale(1.0 / CMS8TeV_pT_Theory->at(0)->Integral());
 CMS7TeV_pT_Theory->at(0)->Scale(1.0 / CMS7TeV_pT_Theory->at(0)->Integral());

 ATLAS7TeV_Phi_Theory->at(0)->Scale(1.0 / ATLAS7TeV_Phi_Theory->at(0)->Integral());
 ATLAS7TeV_Phi_Y1_Theory->at(0)->Scale(1.0 / ATLAS7TeV_Phi_Y1_Theory->at(0)->Integral());
 ATLAS7TeV_Phi_Y2_Theory->at(0)->Scale(1.0 / ATLAS7TeV_Phi_Y2_Theory->at(0)->Integral());
 ATLAS7TeV_Phi_Y3_Theory->at(0)->Scale(1.0 / ATLAS7TeV_Phi_Y3_Theory->at(0)->Integral());

 HistDivideBinWidth(ATLAS8TeV_pT_Mass12_20_Theory->at(0), ATLAS8TeV_pT_Mass12_20_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_pT_Mass20_30_Theory->at(0), ATLAS8TeV_pT_Mass20_30_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_pT_Mass30_46_Theory->at(0), ATLAS8TeV_pT_Mass30_46_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_pT_Mass46_66_Theory->at(0), ATLAS8TeV_pT_Mass46_66_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_pT_Mass66_116_Theory->at(0), ATLAS8TeV_pT_Mass66_116_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_pT_Mass116_150_Theory->at(0), ATLAS8TeV_pT_Mass116_150_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_Phi_Y1_Theory->at(0), ATLAS8TeV_Phi_Y1_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_Phi_Y2_Theory->at(0), ATLAS8TeV_Phi_Y2_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_Phi_Y3_Theory->at(0), ATLAS8TeV_Phi_Y3_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_Phi_Y4_Theory->at(0), ATLAS8TeV_Phi_Y4_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_Phi_Y5_Theory->at(0), ATLAS8TeV_Phi_Y5_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_Phi_Y6_Theory->at(0), ATLAS8TeV_Phi_Y6_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_pT_Y1_Theory->at(0), ATLAS8TeV_pT_Y1_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_pT_Y2_Theory->at(0), ATLAS8TeV_pT_Y2_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_pT_Y3_Theory->at(0), ATLAS8TeV_pT_Y3_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_pT_Y4_Theory->at(0), ATLAS8TeV_pT_Y4_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_pT_Y5_Theory->at(0), ATLAS8TeV_pT_Y5_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_pT_Y6_Theory->at(0), ATLAS8TeV_pT_Y6_Theory_Final);
 HistDivideBinWidth(ATLAS13TeV_pT_Theory->at(0), ATLAS13TeV_pT_Theory_Final);
 HistDivideBinWidth(ATLAS13TeV_Phi_Theory->at(0), ATLAS13TeV_Phi_Theory_Final);
 HistDivideBinWidth(CMS13TeV_pT_Theory->at(0), CMS13TeV_pT_Theory_Final);
 HistDivideBinWidth(CMS13TeV_Phi_Theory->at(0), CMS13TeV_Phi_Theory_Final);
 HistDivideBinWidth(LHCb13TeV_pT_Theory->at(0), LHCb13TeV_pT_Theory_Final);
 HistDivideBinWidth(LHCb13TeV_Phi_Theory->at(0), LHCb13TeV_Phi_Theory_Final);
 HistDivideBinWidth(CMS13TeV_pT_Y1_Theory->at(0), CMS13TeV_pT_Y1_Theory_Final);
 HistDivideBinWidth(CMS13TeV_pT_Y2_Theory->at(0), CMS13TeV_pT_Y2_Theory_Final);
 HistDivideBinWidth(CMS13TeV_pT_Y3_Theory->at(0), CMS13TeV_pT_Y3_Theory_Final);
 HistDivideBinWidth(CMS13TeV_pT_Y4_Theory->at(0), CMS13TeV_pT_Y4_Theory_Final);
 HistDivideBinWidth(CMS13TeV_pT_Y5_Theory->at(0), CMS13TeV_pT_Y5_Theory_Final);
 HistDivideBinWidth(CMS13TeV_yZ_Theory->at(0), CMS13TeV_yZ_Theory_Final);
 HistDivideBinWidth(ZPt_FineBin->at(0), ZPt_FineBin_Final);
 HistDivideBinWidth(ZPt_FineBin_HighPt->at(0), ZPt_FineBin_HighPt_Final);

 HistDivideBinWidth(ATLAS8TeV_WPlus_Eta_Theory->at(0), ATLAS8TeV_WPlus_Eta_Theory_Final);
 HistDivideBinWidth(ATLAS8TeV_WMinus_Eta_Theory->at(0), ATLAS8TeV_WMinus_Eta_Theory_Final);

 HistDivideBinWidth(ATLAS7TeV_pT_Theory->at(0), ATLAS7TeV_pT_Theory_Final);
 HistDivideBinWidth(ATLAS7TeV_pT_Y1_Theory->at(0), ATLAS7TeV_pT_Y1_Theory_Final);
 HistDivideBinWidth(ATLAS7TeV_pT_Y2_Theory->at(0), ATLAS7TeV_pT_Y2_Theory_Final);
 HistDivideBinWidth(ATLAS7TeV_pT_Y3_Theory->at(0), ATLAS7TeV_pT_Y3_Theory_Final);
 HistDivideBinWidth(CMS8TeV_pT_Theory->at(0), CMS8TeV_pT_Theory_Final);
 HistDivideBinWidth(CMS7TeV_pT_Theory->at(0), CMS7TeV_pT_Theory_Final);
 HistDivideBinWidth(ATLAS7TeV_Phi_Theory->at(0), ATLAS7TeV_Phi_Theory_Final);
 HistDivideBinWidth(ATLAS7TeV_Phi_Y1_Theory->at(0), ATLAS7TeV_Phi_Y1_Theory_Final);
 HistDivideBinWidth(ATLAS7TeV_Phi_Y2_Theory->at(0), ATLAS7TeV_Phi_Y2_Theory_Final);
 HistDivideBinWidth(ATLAS7TeV_Phi_Y3_Theory->at(0), ATLAS7TeV_Phi_Y3_Theory_Final);

 ApplyKFactorToHist(ATLAS8TeV_pT_Y1_Theory_Final, ATLAS8TeV_pT_Y1_KFactor, ATLAS8TeV_pT_Y1_Theory_HigherOrder, 20.0);
 ApplyKFactorToHist(ATLAS8TeV_pT_Y2_Theory_Final, ATLAS8TeV_pT_Y2_KFactor, ATLAS8TeV_pT_Y2_Theory_HigherOrder, 20.0);
 ApplyKFactorToHist(ATLAS8TeV_pT_Y3_Theory_Final, ATLAS8TeV_pT_Y3_KFactor, ATLAS8TeV_pT_Y3_Theory_HigherOrder, 20.0);
 ApplyKFactorToHist(ATLAS8TeV_pT_Y4_Theory_Final, ATLAS8TeV_pT_Y4_KFactor, ATLAS8TeV_pT_Y4_Theory_HigherOrder, 20.0);
 ApplyKFactorToHist(ATLAS8TeV_pT_Y5_Theory_Final, ATLAS8TeV_pT_Y5_KFactor, ATLAS8TeV_pT_Y5_Theory_HigherOrder, 20.0);
 ApplyKFactorToHist(ATLAS8TeV_pT_Y6_Theory_Final, ATLAS8TeV_pT_Y6_KFactor, ATLAS8TeV_pT_Y6_Theory_HigherOrder, 20.0);
 ApplyKFactorToHist(ATLAS8TeV_pT_Mass66_116_Theory_Final, ATLAS8TeV_pT_Mass66_116_KFactor, ATLAS8TeV_pT_Mass66_116_Theory_HigherOrder, 20.0);

 ATLAS8TeV_pT_Mass12_20_Theory_Final->Write();
 ATLAS8TeV_pT_Mass20_30_Theory_Final->Write();
 ATLAS8TeV_pT_Mass30_46_Theory_Final->Write();
 ATLAS8TeV_pT_Mass46_66_Theory_Final->Write();
 ATLAS8TeV_pT_Mass66_116_Theory_Final->Write();
 ATLAS8TeV_pT_Mass116_150_Theory_Final->Write();
 ATLAS8TeV_Phi_Y1_Theory_Final->Write();
 ATLAS8TeV_Phi_Y2_Theory_Final->Write();
 ATLAS8TeV_Phi_Y3_Theory_Final->Write();
 ATLAS8TeV_Phi_Y4_Theory_Final->Write();
 ATLAS8TeV_Phi_Y5_Theory_Final->Write();
 ATLAS8TeV_Phi_Y6_Theory_Final->Write();
 ATLAS8TeV_pT_Y1_Theory_Final->Write();
 ATLAS8TeV_pT_Y2_Theory_Final->Write();
 ATLAS8TeV_pT_Y3_Theory_Final->Write();
 ATLAS8TeV_pT_Y4_Theory_Final->Write();
 ATLAS8TeV_pT_Y5_Theory_Final->Write();
 ATLAS8TeV_pT_Y6_Theory_Final->Write();
 ATLAS13TeV_pT_Theory_Final->Write();
 ATLAS13TeV_Phi_Theory_Final->Write();
 CMS13TeV_pT_Theory_Final->Write();
 CMS13TeV_Phi_Theory_Final->Write();
 LHCb13TeV_pT_Theory_Final->Write();
 LHCb13TeV_Phi_Theory_Final->Write();
 CMS13TeV_pT_Y1_Theory_Final->Write();
 CMS13TeV_pT_Y2_Theory_Final->Write();
 CMS13TeV_pT_Y3_Theory_Final->Write();
 CMS13TeV_pT_Y4_Theory_Final->Write();
 CMS13TeV_pT_Y5_Theory_Final->Write();
 CMS13TeV_yZ_Theory_Final->Write();
 ATLAS8TeV_pT_Y1_Theory_HigherOrder->Write();
 ATLAS8TeV_pT_Y2_Theory_HigherOrder->Write();
 ATLAS8TeV_pT_Y3_Theory_HigherOrder->Write();
 ATLAS8TeV_pT_Y4_Theory_HigherOrder->Write();
 ATLAS8TeV_pT_Y5_Theory_HigherOrder->Write();
 ATLAS8TeV_pT_Y6_Theory_HigherOrder->Write();
 ATLAS8TeV_pT_Mass66_116_Theory_HigherOrder->Write();

 LatexOutput* output = new LatexOutput();
 output->DataMC(ATLAS8TeV_pT_Y1_Theory_Final, ATLAS8TeV_pT_Y1_Data, "ATLAS8TeV_pT_Y1");
 output->DataMC(ATLAS8TeV_pT_Y2_Theory_Final, ATLAS8TeV_pT_Y2_Data, "ATLAS8TeV_pT_Y2");
 output->DataMC(ATLAS8TeV_pT_Y3_Theory_Final, ATLAS8TeV_pT_Y3_Data, "ATLAS8TeV_pT_Y3");
 output->DataMC(ATLAS8TeV_pT_Y4_Theory_Final, ATLAS8TeV_pT_Y4_Data, "ATLAS8TeV_pT_Y4");
 output->DataMC(ATLAS8TeV_pT_Y5_Theory_Final, ATLAS8TeV_pT_Y5_Data, "ATLAS8TeV_pT_Y5");
 output->DataMC(ATLAS8TeV_pT_Y6_Theory_Final, ATLAS8TeV_pT_Y6_Data, "ATLAS8TeV_pT_Y6");
 output->DataMC(ATLAS8TeV_Phi_Y1_Theory_Final, ATLAS8TeV_Phi_Y1_Data, "ATLAS8TeV_Phi_Y1");
 output->DataMC(ATLAS8TeV_Phi_Y2_Theory_Final, ATLAS8TeV_Phi_Y2_Data, "ATLAS8TeV_Phi_Y2");
 output->DataMC(ATLAS8TeV_Phi_Y3_Theory_Final, ATLAS8TeV_Phi_Y3_Data, "ATLAS8TeV_Phi_Y3");
 output->DataMC(ATLAS8TeV_Phi_Y4_Theory_Final, ATLAS8TeV_Phi_Y4_Data, "ATLAS8TeV_Phi_Y4");
 output->DataMC(ATLAS8TeV_Phi_Y5_Theory_Final, ATLAS8TeV_Phi_Y5_Data, "ATLAS8TeV_Phi_Y5");
 output->DataMC(ATLAS8TeV_Phi_Y6_Theory_Final, ATLAS8TeV_Phi_Y6_Data, "ATLAS8TeV_Phi_Y6");


 ZPt_FineBin_Final->Write();
 ZPt_FineBin_HighPt_Final->Write();

 ATLAS8TeV_WPlus_Eta_Theory_Final->Write();
 ATLAS8TeV_WMinus_Eta_Theory_Final->Write();

 ATLAS7TeV_pT_Theory_Final->Write();
 ATLAS7TeV_pT_Y1_Theory_Final->Write();
 ATLAS7TeV_pT_Y2_Theory_Final->Write();
 ATLAS7TeV_pT_Y3_Theory_Final->Write();
 CMS8TeV_pT_Theory_Final->Write();
 CMS7TeV_pT_Theory_Final->Write();
 ATLAS7TeV_Phi_Theory_Final->Write();
 ATLAS7TeV_Phi_Y1_Theory_Final->Write();
 ATLAS7TeV_Phi_Y2_Theory_Final->Write();
 ATLAS7TeV_Phi_Y3_Theory_Final->Write();

 ATLAS8TeV_pT_Y1_CutEff = (TH1D *)ATLAS8TeV_pT_Y1_Theory->at(0)->Clone("ATLAS8TeV_pT_Y1_CutEff");
 ATLAS8TeV_pT_Y1_CutEff->Divide(ATLAS8TeV_pT_Y1_Total->at(0));
 ATLAS8TeV_pT_Y2_CutEff = (TH1D *)ATLAS8TeV_pT_Y2_Theory->at(0)->Clone("ATLAS8TeV_pT_Y2_CutEff");
 ATLAS8TeV_pT_Y2_CutEff->Divide(ATLAS8TeV_pT_Y2_Total->at(0));
 ATLAS8TeV_pT_Y3_CutEff = (TH1D *)ATLAS8TeV_pT_Y3_Theory->at(0)->Clone("ATLAS8TeV_pT_Y3_CutEff");
 ATLAS8TeV_pT_Y3_CutEff->Divide(ATLAS8TeV_pT_Y3_Total->at(0));
 ATLAS8TeV_pT_Y4_CutEff = (TH1D *)ATLAS8TeV_pT_Y4_Theory->at(0)->Clone("ATLAS8TeV_pT_Y4_CutEff");
 ATLAS8TeV_pT_Y4_CutEff->Divide(ATLAS8TeV_pT_Y4_Total->at(0));
 ATLAS8TeV_pT_Y5_CutEff = (TH1D *)ATLAS8TeV_pT_Y5_Theory->at(0)->Clone("ATLAS8TeV_pT_Y5_CutEff");
 ATLAS8TeV_pT_Y5_CutEff->Divide(ATLAS8TeV_pT_Y5_Total->at(0));
 ATLAS8TeV_pT_Y6_CutEff = (TH1D *)ATLAS8TeV_pT_Y6_Theory->at(0)->Clone("ATLAS8TeV_pT_Y6_CutEff");
 ATLAS8TeV_pT_Y6_CutEff->Divide(ATLAS8TeV_pT_Y6_Total->at(0));

 CMS13TeV_pT_Y1_CutEff = (TH1D *)CMS13TeV_pT_Y1_Theory->at(0)->Clone("CMS13TeV_pT_Y1_CutEff");
 CMS13TeV_pT_Y1_CutEff->Divide(CMS13TeV_pT_Y1_Total->at(0));
 CMS13TeV_pT_Y2_CutEff = (TH1D *)CMS13TeV_pT_Y2_Theory->at(0)->Clone("CMS13TeV_pT_Y2_CutEff");
 CMS13TeV_pT_Y2_CutEff->Divide(CMS13TeV_pT_Y2_Total->at(0));
 CMS13TeV_pT_Y3_CutEff = (TH1D *)CMS13TeV_pT_Y3_Theory->at(0)->Clone("CMS13TeV_pT_Y3_CutEff");
 CMS13TeV_pT_Y3_CutEff->Divide(CMS13TeV_pT_Y3_Total->at(0));
 CMS13TeV_pT_Y4_CutEff = (TH1D *)CMS13TeV_pT_Y4_Theory->at(0)->Clone("CMS13TeV_pT_Y4_CutEff");
 CMS13TeV_pT_Y4_CutEff->Divide(CMS13TeV_pT_Y4_Total->at(0));
 CMS13TeV_pT_Y5_CutEff = (TH1D *)CMS13TeV_pT_Y5_Theory->at(0)->Clone("CMS13TeV_pT_Y5_CutEff");
 CMS13TeV_pT_Y5_CutEff->Divide(CMS13TeV_pT_Y5_Total->at(0));

 LHCb13TeV_pT_CutEff = (TH1D *)LHCb13TeV_pT_Theory->at(0)->Clone("LHCb13TeV_pT_CutEff");
 LHCb13TeV_pT_CutEff->Divide(LHCb13TeV_pT_Total->at(0));

/* for(int ibin = 1; ibin <= 8; ibin++){
   cout<<fixed<<setprecision(5)<<"Y1 ibin "<<ibin<<": "<<ATLAS8TeV_pT_Y1_CutEff->GetBinContent(ibin) * 0.033662<<endl;
 }
 for(int ibin = 1; ibin <= 8; ibin++){
   cout<<fixed<<setprecision(5)<<"Y2 ibin "<<ibin<<": "<<ATLAS8TeV_pT_Y2_CutEff->GetBinContent(ibin) * 0.033662<<endl;
 }
 for(int ibin = 1; ibin <= 8; ibin++){
   cout<<fixed<<setprecision(5)<<"Y3 ibin "<<ibin<<": "<<ATLAS8TeV_pT_Y3_CutEff->GetBinContent(ibin) * 0.033662<<endl;
 }
 for(int ibin = 1; ibin <= 8; ibin++){
   cout<<fixed<<setprecision(5)<<"Y4 ibin "<<ibin<<": "<<ATLAS8TeV_pT_Y4_CutEff->GetBinContent(ibin) * 0.033662<<endl;
 }
 for(int ibin = 1; ibin <= 8; ibin++){
   cout<<fixed<<setprecision(5)<<"Y5 ibin "<<ibin<<": "<<ATLAS8TeV_pT_Y5_CutEff->GetBinContent(ibin) * 0.033662<<endl;
 }
 for(int ibin = 1; ibin <= 8; ibin++){
   cout<<fixed<<setprecision(5)<<"Y6 ibin "<<ibin<<": "<<ATLAS8TeV_pT_Y6_CutEff->GetBinContent(ibin) * 0.033662<<endl;
 }
*/

 cout<<"CMS13TeV pT Cut Efficiency:"<<endl;
 for(int ibin = 1; ibin <= 16; ibin++){
   cout<<fixed<<setprecision(5)<<"Y1 ibin "<<ibin<<": "<<CMS13TeV_pT_Y1_CutEff->GetBinContent(ibin) * 0.033662<<endl;
 }
 for(int ibin = 1; ibin <= 16; ibin++){
   cout<<fixed<<setprecision(5)<<"Y2 ibin "<<ibin<<": "<<CMS13TeV_pT_Y2_CutEff->GetBinContent(ibin) * 0.033662<<endl;
 }
 for(int ibin = 1; ibin <= 16; ibin++){
   cout<<fixed<<setprecision(5)<<"Y3 ibin "<<ibin<<": "<<CMS13TeV_pT_Y3_CutEff->GetBinContent(ibin) * 0.033662<<endl;
 }
 for(int ibin = 1; ibin <= 16; ibin++){
   cout<<fixed<<setprecision(5)<<"Y4 ibin "<<ibin<<": "<<CMS13TeV_pT_Y4_CutEff->GetBinContent(ibin) * 0.033662<<endl;
 }
 for(int ibin = 1; ibin <= 16; ibin++){
   cout<<fixed<<setprecision(5)<<"Y5 ibin "<<ibin<<": "<<CMS13TeV_pT_Y5_CutEff->GetBinContent(ibin) * 0.033662<<endl;
 }

 cout<<"LHCb13TeV pT Cut Efficiency:"<<endl;
 for(int ibin = 1; ibin <= 10; ibin++){
   cout<<fixed<<setprecision(5)<<"ibin "<<ibin<<": "<<LHCb13TeV_pT_CutEff->GetBinContent(ibin) * 0.033662 / 2.0<<endl;
 }

 ATLAS8TeV_pT_Y1_CutEff->Write();
 ATLAS8TeV_pT_Y2_CutEff->Write();
 ATLAS8TeV_pT_Y3_CutEff->Write();
 ATLAS8TeV_pT_Y4_CutEff->Write();
 ATLAS8TeV_pT_Y5_CutEff->Write();
 ATLAS8TeV_pT_Y6_CutEff->Write();

 CMS13TeV_pT_Y1_CutEff->Write();
 CMS13TeV_pT_Y2_CutEff->Write();
 CMS13TeV_pT_Y3_CutEff->Write();
 CMS13TeV_pT_Y4_CutEff->Write();
 CMS13TeV_pT_Y5_CutEff->Write();

 LHCb13TeV_pT_CutEff->Write();

/* for(int ibinx = 1; ibinx <= AFB_Mass_ZY_ZPt_uu->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= AFB_Mass_ZY_ZPt_uu->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= AFB_Mass_ZY_ZPt_uu->GetNbinsZ(); ibinz++){

       double Value1 = CoefficientDilution_ZMass_ZY_QT_uu->GetBinContent(ibinx, ibiny, ibinz);
       double Value2 = AFB_Mass_ZY_ZPt_uu->GetBinContent(ibinx, ibiny, ibinz);

       double Value3 = CoefficientDilution_ZMass_ZY_QT_dd->GetBinContent(ibinx, ibiny, ibinz);
       double Value4 = AFB_Mass_ZY_ZPt_dd->GetBinContent(ibinx, ibiny, ibinz);

       double Error1 = CoefficientDilution_ZMass_ZY_QT_uu->GetBinError(ibinx, ibiny, ibinz);
       double Error2 = AFB_Mass_ZY_ZPt_uu->GetBinError(ibinx, ibiny, ibinz);

       double Error3 = CoefficientDilution_ZMass_ZY_QT_dd->GetBinError(ibinx, ibiny, ibinz);
       double Error4 = AFB_Mass_ZY_ZPt_dd->GetBinError(ibinx, ibiny, ibinz);

       double Value = Value1 * Value2 + Value3 * Value4;
       double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

       HadronAFB->SetBinContent(ibinx, ibiny, ibinz, Value);
       HadronAFB->SetBinError(ibinx, ibiny, ibinz, Error);
     }
   }
 }
*/

 if(RootType != "FittingCMSData") Save();

 ConstructCTEQData();
}

void HistsResBosCMS::ConstructCTEQData()
{
 hf->cd();

 int nBin;
 vector<double> m_theory;

 function<int(vector<TH1D *>)> GetNBin = [&](vector<TH1D *> Hists){
   int N = 0;

   for(int i = 0; i < Hists.size(); i++){
     N += Hists.at(i)->GetNbinsX();
   }

   return N;
 };

 function<vector<double>(vector<TH1D *>)> PushTheory = [&](vector<TH1D *> Hists){
   vector<double> theory;

   theory.clear();

   for(int i = 0; i < Hists.size(); i++){
     for(int ibin = 1; ibin <= Hists.at(i)->GetNbinsX(); ibin++){
       theory.push_back(Hists.at(i)->GetBinContent(ibin));
     }
   }

   return theory;
 };

 function<void(vector<TH1D *>, double)> ApplyBranchingRatio = [&](vector<TH1D *> Hists, double BR){
   for(int i = 0; i < Hists.size(); i++){
     for(int ibin = 1; ibin <= Hists.at(i)->GetNbinsX(); ibin++){
       Hists.at(i)->SetBinContent(ibin, Hists.at(i)->GetBinContent(ibin) * BR);
     }
   }
 };

 function<void(TH1D* &, TString, int, vector<double>)> SaveTheory = [&](TH1D* &h, TString name, int N, vector<double> theory){
   h = new TH1D(name, name, N, 0, (double)N);
   for(int ibin = 1; ibin <= N; ibin++){
     h->SetBinContent(ibin, theory.at(ibin - 1));
     h->SetBinError(ibin, 0.0);
   }
   h->Write();
 };

 // E245
 TH1D* E245_LHCb7TeV_Z_Final;
 TH1D* E245_LHCb7TeV_WPlus_Final;
 TH1D* E245_LHCb7TeV_WMinus_Final;

 //HistDivideBinWidth(E245_LHCb7TeV_Z->at(0), E245_LHCb7TeV_Z_Final);
 //HistDivideBinWidth(E245_LHCb7TeV_WPlus->at(0), E245_LHCb7TeV_WPlus_Final);
 //HistDivideBinWidth(E245_LHCb7TeV_WMinus->at(0), E245_LHCb7TeV_WMinus_Final);
 E245_LHCb7TeV_Z_Final = (TH1D *)E245_LHCb7TeV_Z->at(0)->Clone("E245_LHCb7TeV_Z_Final");
 E245_LHCb7TeV_WPlus_Final = (TH1D *)E245_LHCb7TeV_WPlus->at(0)->Clone("E245_LHCb7TeV_WPlus_Final");
 E245_LHCb7TeV_WMinus_Final = (TH1D *)E245_LHCb7TeV_WMinus->at(0)->Clone("E245_LHCb7TeV_WMinus_Final");

 nBin = GetNBin(vector<TH1D *>{E245_LHCb7TeV_Z_Final, E245_LHCb7TeV_WPlus_Final, E245_LHCb7TeV_WMinus_Final});
 m_theory = PushTheory(vector<TH1D *>{E245_LHCb7TeV_Z_Final, E245_LHCb7TeV_WPlus_Final, E245_LHCb7TeV_WMinus_Final});
 SaveTheory(E245_Final, "E245_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E246
 TH1D* E246_LHCb8TeV_Z_Final;
 HistDivideBinWidth(E246_LHCb8TeV_Z->at(0), E246_LHCb8TeV_Z_Final);

 nBin = GetNBin(vector<TH1D *>{E246_LHCb8TeV_Z_Final});
 m_theory = PushTheory(vector<TH1D *>{E246_LHCb8TeV_Z_Final});
 SaveTheory(E246_Final, "E246_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E248
 TH1D* E248_ATLAS7TeV_Z_Final;
 TH1D* E248_ATLAS7TeV_WPlus_Final;
 TH1D* E248_ATLAS7TeV_WMinus_Final;

 HistDivideBinWidth(E248_ATLAS7TeV_Z->at(0), E248_ATLAS7TeV_Z_Final);
 HistDivideBinWidth(E248_ATLAS7TeV_WPlus->at(0), E248_ATLAS7TeV_WPlus_Final);
 HistDivideBinWidth(E248_ATLAS7TeV_WMinus->at(0), E248_ATLAS7TeV_WMinus_Final);

 nBin = GetNBin(vector<TH1D *>{E248_ATLAS7TeV_Z_Final, E248_ATLAS7TeV_WPlus_Final, E248_ATLAS7TeV_WMinus_Final});
 ApplyBranchingRatio(vector<TH1D *>{E248_ATLAS7TeV_Z_Final, E248_ATLAS7TeV_WPlus_Final, E248_ATLAS7TeV_WMinus_Final}, 0.5);
 m_theory = PushTheory(vector<TH1D *>{E248_ATLAS7TeV_Z_Final, E248_ATLAS7TeV_WPlus_Final, E248_ATLAS7TeV_WMinus_Final});
 SaveTheory(E248_Final, "E248_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E249
 TH1D* E249_CMS8TeV_WPlus_Final;
 TH1D* E249_CMS8TeV_WMinus_Final;
 HistDivideBinWidth(E249_CMS8TeV_WPlus->at(0), E249_CMS8TeV_WPlus_Final);
 HistDivideBinWidth(E249_CMS8TeV_WMinus->at(0), E249_CMS8TeV_WMinus_Final);

 TH1D* E249_Wasymmetry = (TH1D *)E249_CMS8TeV_WPlus_Final->Clone("E249_Wasymmetry");
 AFBFunction(E249_CMS8TeV_WPlus_Final, E249_CMS8TeV_WMinus_Final, E249_Wasymmetry);

 nBin = GetNBin(vector<TH1D *>{E249_CMS8TeV_WPlus_Final, E249_CMS8TeV_WMinus_Final, E249_Wasymmetry});
 ApplyBranchingRatio(vector<TH1D *>{E249_CMS8TeV_WPlus_Final, E249_CMS8TeV_WMinus_Final}, 0.5);
 ApplyBranchingRatio(vector<TH1D *>{E249_Wasymmetry}, 100.0);
 m_theory = PushTheory(vector<TH1D *>{E249_CMS8TeV_WPlus_Final, E249_CMS8TeV_WMinus_Final, E249_Wasymmetry});
 SaveTheory(E249_Final, "E249_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E250
 TH1D* E250_LHCb8TeV_Z_Final;
 TH1D* E250_LHCb8TeV_WPlus_Final;
 TH1D* E250_LHCb8TeV_WMinus_Final;

 //HistDivideBinWidth(E250_LHCb8TeV_Z->at(0), E250_LHCb8TeV_Z_Final);
 //HistDivideBinWidth(E250_LHCb8TeV_WPlus->at(0), E250_LHCb8TeV_WPlus_Final);
 //HistDivideBinWidth(E250_LHCb8TeV_WMinus->at(0), E250_LHCb8TeV_WMinus_Final);
 E250_LHCb8TeV_Z_Final = (TH1D *)E250_LHCb8TeV_Z->at(0)->Clone("E250_LHCb8TeV_Z_Final");
 E250_LHCb8TeV_WPlus_Final = (TH1D *)E250_LHCb8TeV_WPlus->at(0)->Clone("E250_LHCb8TeV_WPlus_Final");
 E250_LHCb8TeV_WMinus_Final = (TH1D *)E250_LHCb8TeV_WMinus->at(0)->Clone("E250_LHCb8TeV_WMinus_Final");

 TH1D* E250_Wasymmetry = (TH1D *)E250_LHCb8TeV_WPlus_Final->Clone("E250_Wasymmetry");
 AFBFunction(E250_LHCb8TeV_WPlus_Final, E250_LHCb8TeV_WMinus_Final, E250_Wasymmetry);

 nBin = GetNBin(vector<TH1D *>{E250_LHCb8TeV_WPlus_Final, E250_LHCb8TeV_WMinus_Final, E250_LHCb8TeV_Z_Final, E250_Wasymmetry});
 ApplyBranchingRatio(vector<TH1D *>{E250_Wasymmetry}, 100.0);
 m_theory = PushTheory(vector<TH1D *>{E250_LHCb8TeV_WPlus_Final, E250_LHCb8TeV_WMinus_Final, E250_LHCb8TeV_Z_Final, E250_Wasymmetry});
 SaveTheory(E250_Final, "E250_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E253
 TH1D* E253_ATLAS8TeV_ZPt1_Final;
 TH1D* E253_ATLAS8TeV_ZPt2_Final;
 TH1D* E253_ATLAS8TeV_ZPt3_Final;

 HistDivideBinWidth(E253_ATLAS8TeV_ZPt1->at(0), E253_ATLAS8TeV_ZPt1_Final);
 HistDivideBinWidth(E253_ATLAS8TeV_ZPt2->at(0), E253_ATLAS8TeV_ZPt2_Final);
 HistDivideBinWidth(E253_ATLAS8TeV_ZPt3->at(0), E253_ATLAS8TeV_ZPt3_Final);

 nBin = GetNBin(vector<TH1D *>{E253_ATLAS8TeV_ZPt1_Final, E253_ATLAS8TeV_ZPt2_Final, E253_ATLAS8TeV_ZPt3_Final});
 m_theory = PushTheory(vector<TH1D *>{E253_ATLAS8TeV_ZPt1_Final, E253_ATLAS8TeV_ZPt2_Final, E253_ATLAS8TeV_ZPt3_Final});
 SaveTheory(E253_Final, "E253_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E225
 TH1D* E225_CDF1p8TeV_WPlus_Final;
 TH1D* E225_CDF1p8TeV_WMinus_Final;
 HistDivideBinWidth(E225_CDF1p8TeV_WPlus->at(0), E225_CDF1p8TeV_WPlus_Final);
 HistDivideBinWidth(E225_CDF1p8TeV_WMinus->at(0), E225_CDF1p8TeV_WMinus_Final);

 nBin = GetNBin(vector<TH1D *>{E225_CDF1p8TeV_WPlus_Final, E225_CDF1p8TeV_WMinus_Final});
 m_theory = PushTheory(vector<TH1D *>{E225_CDF1p8TeV_WPlus_Final, E225_CDF1p8TeV_WMinus_Final});
 SaveTheory(E225_Final, "E225_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E227
 TH1D* E227_CDF1p96TeV_WPlus_Final;
 TH1D* E227_CDF1p96TeV_WMinus_Final;
 HistDivideBinWidth(E227_CDF1p96TeV_WPlus->at(0), E227_CDF1p96TeV_WPlus_Final);
 HistDivideBinWidth(E227_CDF1p96TeV_WMinus->at(0), E227_CDF1p96TeV_WMinus_Final);

 nBin = GetNBin(vector<TH1D *>{E227_CDF1p96TeV_WPlus_Final, E227_CDF1p96TeV_WMinus_Final});
 m_theory = PushTheory(vector<TH1D *>{E227_CDF1p96TeV_WPlus_Final, E227_CDF1p96TeV_WMinus_Final});
 SaveTheory(E227_Final, "E227_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E234
 TH1D* E234_D01p96TeV_WPlus_Final;
 TH1D* E234_D01p96TeV_WMinus_Final;
 HistDivideBinWidth(E234_D01p96TeV_WPlus->at(0), E234_D01p96TeV_WPlus_Final);
 HistDivideBinWidth(E234_D01p96TeV_WMinus->at(0), E234_D01p96TeV_WMinus_Final);

 nBin = GetNBin(vector<TH1D *>{E234_D01p96TeV_WPlus_Final, E234_D01p96TeV_WMinus_Final});
 m_theory = PushTheory(vector<TH1D *>{E234_D01p96TeV_WPlus_Final, E234_D01p96TeV_WMinus_Final});
 SaveTheory(E234_Final, "E234_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E260
 TH1D* E260_D01p96TeV_Z_Final;
 HistDivideBinWidth(E260_D01p96TeV_Z->at(0), E260_D01p96TeV_Z_Final);

 nBin = GetNBin(vector<TH1D *>{E260_D01p96TeV_Z_Final});
 ApplyBranchingRatio(vector<TH1D *>{E260_D01p96TeV_Z_Final}, 0.5);
 m_theory = PushTheory(vector<TH1D *>{E260_D01p96TeV_Z_Final});
 SaveTheory(E260_Final, "E260_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E261
 TH1D* E261_CDF1p96TeV_Z_Final;
 HistDivideBinWidth(E261_CDF1p96TeV_Z->at(0), E261_CDF1p96TeV_Z_Final);

 nBin = GetNBin(vector<TH1D *>{E261_CDF1p96TeV_Z_Final});
 ApplyBranchingRatio(vector<TH1D *>{E261_CDF1p96TeV_Z_Final}, 0.5);
 m_theory = PushTheory(vector<TH1D *>{E261_CDF1p96TeV_Z_Final});
 SaveTheory(E261_Final, "E261_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E266
 TH1D* E266_CMS7TeV_WPlus_Final;
 TH1D* E266_CMS7TeV_WMinus_Final;
 HistDivideBinWidth(E266_CMS7TeV_WPlus->at(0), E266_CMS7TeV_WPlus_Final);
 HistDivideBinWidth(E266_CMS7TeV_WMinus->at(0), E266_CMS7TeV_WMinus_Final);

 nBin = GetNBin(vector<TH1D *>{E266_CMS7TeV_WPlus_Final, E266_CMS7TeV_WMinus_Final});
 m_theory = PushTheory(vector<TH1D *>{E266_CMS7TeV_WPlus_Final, E266_CMS7TeV_WMinus_Final});
 SaveTheory(E266_Final, "E266_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E267
 TH1D* E267_CMS7TeV_WPlus_Final_tmp;
 TH1D* E267_CMS7TeV_WMinus_Final_tmp;
 HistDivideBinWidth(E267_CMS7TeV_WPlus->at(0), E267_CMS7TeV_WPlus_Final_tmp);
 HistDivideBinWidth(E267_CMS7TeV_WMinus->at(0), E267_CMS7TeV_WMinus_Final_tmp);

 TH1D* E267_CMS7TeV_WPlus_Final = new TH1D("E267_CMS7TeV_WPlus_Final", "E267_CMS7TeV_WPlus_Final", E267_CMS7TeV_WPlus_Final_tmp->GetNbinsX() - 1, 0, E267_CMS7TeV_WPlus_Final_tmp->GetNbinsX() - 1.0);
 TH1D* E267_CMS7TeV_WMinus_Final = new TH1D("E267_CMS7TeV_WMinus_Final", "E267_CMS7TeV_WMinus_Final", E267_CMS7TeV_WMinus_Final_tmp->GetNbinsX() - 1, 0, E267_CMS7TeV_WMinus_Final_tmp->GetNbinsX() - 1.0);

 for(int i = 1; i <= 7; i++){
   E267_CMS7TeV_WPlus_Final->SetBinContent(i, E267_CMS7TeV_WPlus_Final_tmp->GetBinContent(i));
   E267_CMS7TeV_WPlus_Final->SetBinError(i, E267_CMS7TeV_WPlus_Final_tmp->GetBinError(i));

   E267_CMS7TeV_WMinus_Final->SetBinContent(i, E267_CMS7TeV_WMinus_Final_tmp->GetBinContent(i));
   E267_CMS7TeV_WMinus_Final->SetBinError(i, E267_CMS7TeV_WMinus_Final_tmp->GetBinError(i));
 }

 for(int i = 8; i <= 11; i++){
   E267_CMS7TeV_WPlus_Final->SetBinContent(i, E267_CMS7TeV_WPlus_Final_tmp->GetBinContent(i + 1));
   E267_CMS7TeV_WPlus_Final->SetBinError(i, E267_CMS7TeV_WPlus_Final_tmp->GetBinError(i + 1));

   E267_CMS7TeV_WMinus_Final->SetBinContent(i, E267_CMS7TeV_WMinus_Final_tmp->GetBinContent(i + 1));
   E267_CMS7TeV_WMinus_Final->SetBinError(i, E267_CMS7TeV_WMinus_Final_tmp->GetBinError(i + 1));
 }

 nBin = GetNBin(vector<TH1D *>{E267_CMS7TeV_WPlus_Final, E267_CMS7TeV_WMinus_Final});
 m_theory = PushTheory(vector<TH1D *>{E267_CMS7TeV_WPlus_Final, E267_CMS7TeV_WMinus_Final});
 SaveTheory(E267_Final, "E267_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E281
 TH1D* E281_D01p96TeV_WPlus_Final;
 TH1D* E281_D01p96TeV_WMinus_Final;
 HistDivideBinWidth(E281_D01p96TeV_WPlus->at(0), E281_D01p96TeV_WPlus_Final);
 HistDivideBinWidth(E281_D01p96TeV_WMinus->at(0), E281_D01p96TeV_WMinus_Final);

 nBin = GetNBin(vector<TH1D *>{E281_D01p96TeV_WPlus_Final, E281_D01p96TeV_WMinus_Final});
 m_theory = PushTheory(vector<TH1D *>{E281_D01p96TeV_WPlus_Final, E281_D01p96TeV_WMinus_Final});
 SaveTheory(E281_Final, "E281_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E211
 TH1D* E211_ATLAS8TeV_WPlus_Final;
 TH1D* E211_ATLAS8TeV_WMinus_Final;
 HistDivideBinWidth(E211_ATLAS8TeV_WPlus->at(0), E211_ATLAS8TeV_WPlus_Final);
 HistDivideBinWidth(E211_ATLAS8TeV_WMinus->at(0), E211_ATLAS8TeV_WMinus_Final);

 nBin = GetNBin(vector<TH1D *>{E211_ATLAS8TeV_WPlus_Final, E211_ATLAS8TeV_WMinus_Final});
 ApplyBranchingRatio(vector<TH1D *>{E211_ATLAS8TeV_WPlus_Final, E211_ATLAS8TeV_WMinus_Final}, 0.5);
 m_theory = PushTheory(vector<TH1D *>{E211_ATLAS8TeV_WPlus_Final, E211_ATLAS8TeV_WMinus_Final});
 SaveTheory(E211_Final, "E211_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E212
 TH1D* E212_CMS13TeV_Z_Final;
 HistDivideBinWidth(E212_CMS13TeV_Z->at(0), E212_CMS13TeV_Z_Final);

 nBin = GetNBin(vector<TH1D *>{E212_CMS13TeV_Z_Final});
 m_theory = PushTheory(vector<TH1D *>{E212_CMS13TeV_Z_Final});
 SaveTheory(E212_Final, "E212_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E218
 TH1D* E218_LHCb13TeV_Z_Final;
 HistDivideBinWidth(E218_LHCb13TeV_Z->at(0), E218_LHCb13TeV_Z_Final);

 nBin = GetNBin(vector<TH1D *>{E218_LHCb13TeV_Z_Final});
 m_theory = PushTheory(vector<TH1D *>{E218_LHCb13TeV_Z_Final});
 SaveTheory(E218_Final, "E218_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E214
 for(int ibinx = 1; ibinx <= E214_ATLAS8TeV_Z1->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= E214_ATLAS8TeV_Z1->at(0)->GetNbinsY(); ibiny++){
     m_theory.push_back(E214_ATLAS8TeV_Z1->at(0)->GetBinContent(ibinx, ibiny) / E214_ATLAS8TeV_Z1->at(0)->GetYaxis()->GetBinWidth(ibiny) / 14.0 / 0.4);//1.0 / costheta width / mass width / (2 * rapidity width)
   }
 }

 for(int ibinx = 1; ibinx <= E214_ATLAS8TeV_Z2->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= E214_ATLAS8TeV_Z2->at(0)->GetNbinsY(); ibiny++){
     m_theory.push_back(E214_ATLAS8TeV_Z2->at(0)->GetBinContent(ibinx, ibiny) / E214_ATLAS8TeV_Z2->at(0)->GetYaxis()->GetBinWidth(ibiny) / 11.0 / 0.4);
   }
 }

 for(int ibinx = 1; ibinx <= E214_ATLAS8TeV_Z3->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= E214_ATLAS8TeV_Z3->at(0)->GetNbinsY(); ibiny++){
     m_theory.push_back(E214_ATLAS8TeV_Z3->at(0)->GetBinContent(ibinx, ibiny) / E214_ATLAS8TeV_Z3->at(0)->GetYaxis()->GetBinWidth(ibiny) / 11.0 / 0.4);
   }
 }

 for(int ibinx = 1; ibinx <= E214_ATLAS8TeV_Z4->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= E214_ATLAS8TeV_Z4->at(0)->GetNbinsY(); ibiny++){
     m_theory.push_back(E214_ATLAS8TeV_Z4->at(0)->GetBinContent(ibinx, ibiny) / E214_ATLAS8TeV_Z4->at(0)->GetYaxis()->GetBinWidth(ibiny) / 14.0 / 0.4);
   }
 }

 for(int ibinx = 1; ibinx <= E214_ATLAS8TeV_Z5->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= E214_ATLAS8TeV_Z5->at(0)->GetNbinsY(); ibiny++){
     m_theory.push_back(E214_ATLAS8TeV_Z5->at(0)->GetBinContent(ibinx, ibiny) / E214_ATLAS8TeV_Z5->at(0)->GetYaxis()->GetBinWidth(ibiny) / 34.0 / 0.4);
   }
 }

 for(int ibinx = 1; ibinx <= E214_ATLAS8TeV_Z6->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= E214_ATLAS8TeV_Z6->at(0)->GetNbinsY(); ibiny++){
     m_theory.push_back(E214_ATLAS8TeV_Z6->at(0)->GetBinContent(ibinx, ibiny) / E214_ATLAS8TeV_Z6->at(0)->GetYaxis()->GetBinWidth(ibiny) / 50.0 / 0.4);
   }
 }

 vector<double> tmp_theory;
 for(int i = 2; i < 4; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 8; i < 10; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 14; i < 16; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 20; i < 22; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 26; i < 28; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 32; i < 34; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 38; i < 40; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 44; i < 46; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 50; i < 52; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 73; i < 77; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 79; i < 83; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 85; i < 89; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 91; i < 95; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 97; i < 101; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 103; i < 107; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 109; i < 113; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 116; i < 118; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 122; i < 124; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 128; i < 130; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 145; i < 149; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 151; i < 155; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 157; i < 161; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 163; i < 167; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 169; i < 173; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 175; i < 179; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 181; i < 185; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 188; i < 190; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 194; i < 196; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 200; i < 202; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 217; i < 221; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 223; i < 227; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 229; i < 233; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 235; i < 239; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 241; i < 245; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 247; i < 251; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 253; i < 257; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 260; i < 262; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 266; i < 268; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 272; i < 274; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 289; i < 293; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 295; i < 299; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 301; i < 305; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 307; i < 311; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 313; i < 317; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 319; i < 323; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 325; i < 329; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 332; i < 334; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 338; i < 340; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 344; i < 346; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 361; i < 365; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 367; i < 371; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 373; i < 377; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 379; i < 383; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 385; i < 389; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 391; i < 395; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 397; i < 401; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 404; i < 406; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 410; i < 412; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 416; i < 418; i++) tmp_theory.push_back(m_theory.at(i));

 m_theory = tmp_theory;
 nBin = m_theory.size();
 SaveTheory(E214_Final, "E214_Final", nBin, m_theory);
 E214_BinWidth = (TH1D *)E214_Final->Clone("E214_BinWidth");
 nBin = 0; m_theory.clear();

 for(int ibinx = 1; ibinx <= E214_ATLAS8TeV_Z1->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= E214_ATLAS8TeV_Z1->at(0)->GetNbinsY(); ibiny++){
     m_theory.push_back(1.0 / E214_ATLAS8TeV_Z1->at(0)->GetYaxis()->GetBinWidth(ibiny) / 14.0 / 0.4);//1.0 / costheta width / mass width / (2 * rapidity width)
   }
 }

 for(int ibinx = 1; ibinx <= E214_ATLAS8TeV_Z2->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= E214_ATLAS8TeV_Z2->at(0)->GetNbinsY(); ibiny++){
     m_theory.push_back(1.0 / E214_ATLAS8TeV_Z2->at(0)->GetYaxis()->GetBinWidth(ibiny) / 11.0 / 0.4);
   }
 }

 for(int ibinx = 1; ibinx <= E214_ATLAS8TeV_Z3->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= E214_ATLAS8TeV_Z3->at(0)->GetNbinsY(); ibiny++){
     m_theory.push_back(1.0 / E214_ATLAS8TeV_Z3->at(0)->GetYaxis()->GetBinWidth(ibiny) / 11.0 / 0.4);
   }
 }

 for(int ibinx = 1; ibinx <= E214_ATLAS8TeV_Z4->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= E214_ATLAS8TeV_Z4->at(0)->GetNbinsY(); ibiny++){
     m_theory.push_back(1.0 / E214_ATLAS8TeV_Z4->at(0)->GetYaxis()->GetBinWidth(ibiny) / 14.0 / 0.4);
   }
 }

 for(int ibinx = 1; ibinx <= E214_ATLAS8TeV_Z5->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= E214_ATLAS8TeV_Z5->at(0)->GetNbinsY(); ibiny++){
     m_theory.push_back(1.0 / E214_ATLAS8TeV_Z5->at(0)->GetYaxis()->GetBinWidth(ibiny) / 34.0 / 0.4);
   }
 }

 for(int ibinx = 1; ibinx <= E214_ATLAS8TeV_Z6->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= E214_ATLAS8TeV_Z6->at(0)->GetNbinsY(); ibiny++){
     m_theory.push_back(1.0 / E214_ATLAS8TeV_Z6->at(0)->GetYaxis()->GetBinWidth(ibiny) / 50.0 / 0.4);
   }
 }

 tmp_theory.clear();
 for(int i = 2; i < 4; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 8; i < 10; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 14; i < 16; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 20; i < 22; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 26; i < 28; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 32; i < 34; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 38; i < 40; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 44; i < 46; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 50; i < 52; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 73; i < 77; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 79; i < 83; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 85; i < 89; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 91; i < 95; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 97; i < 101; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 103; i < 107; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 109; i < 113; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 116; i < 118; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 122; i < 124; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 128; i < 130; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 145; i < 149; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 151; i < 155; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 157; i < 161; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 163; i < 167; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 169; i < 173; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 175; i < 179; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 181; i < 185; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 188; i < 190; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 194; i < 196; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 200; i < 202; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 217; i < 221; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 223; i < 227; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 229; i < 233; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 235; i < 239; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 241; i < 245; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 247; i < 251; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 253; i < 257; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 260; i < 262; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 266; i < 268; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 272; i < 274; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 289; i < 293; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 295; i < 299; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 301; i < 305; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 307; i < 311; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 313; i < 317; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 319; i < 323; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 325; i < 329; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 332; i < 334; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 338; i < 340; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 344; i < 346; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 361; i < 365; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 367; i < 371; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 373; i < 377; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 379; i < 383; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 385; i < 389; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 391; i < 395; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 397; i < 401; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 404; i < 406; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 410; i < 412; i++) tmp_theory.push_back(m_theory.at(i));
 for(int i = 416; i < 418; i++) tmp_theory.push_back(m_theory.at(i));
 m_theory = tmp_theory;

 for(int ibin = 1; ibin <= E214_BinWidth->GetNbinsX(); ibin++){
   E214_BinWidth->SetBinContent(ibin, m_theory.at(ibin - 1));
 }
 E214_BinWidth->Write();

 nBin = 0; m_theory.clear();

 // E215
 TH1D* E215_ATLAS5TeV_Z_Final;
 TH1D* E215_ATLAS5TeV_WPlus_Final;
 TH1D* E215_ATLAS5TeV_WMinus_Final;

 HistDivideBinWidth(E215_ATLAS5TeV_Z->at(0), E215_ATLAS5TeV_Z_Final);
 HistDivideBinWidth(E215_ATLAS5TeV_WPlus->at(0), E215_ATLAS5TeV_WPlus_Final);
 HistDivideBinWidth(E215_ATLAS5TeV_WMinus->at(0), E215_ATLAS5TeV_WMinus_Final);

 nBin = GetNBin(vector<TH1D *>{E215_ATLAS5TeV_WPlus_Final, E215_ATLAS5TeV_WMinus_Final, E215_ATLAS5TeV_Z_Final});
 ApplyBranchingRatio(vector<TH1D *>{E215_ATLAS5TeV_WPlus_Final, E215_ATLAS5TeV_WMinus_Final, E215_ATLAS5TeV_Z_Final}, 0.5);
 m_theory = PushTheory(vector<TH1D *>{E215_ATLAS5TeV_WPlus_Final, E215_ATLAS5TeV_WMinus_Final, E215_ATLAS5TeV_Z_Final});
 SaveTheory(E215_Final, "E215_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();

 // E217
 TH1D* E217_LHCb8TeV_WPlus_Final;
 TH1D* E217_LHCb8TeV_WMinus_Final;
 //HistDivideBinWidth(E217_LHCb8TeV_WPlus->at(0), E217_LHCb8TeV_WPlus_Final);
 //HistDivideBinWidth(E217_LHCb8TeV_WMinus->at(0), E217_LHCb8TeV_WMinus_Final);
 E217_LHCb8TeV_WPlus_Final = (TH1D *)E217_LHCb8TeV_WPlus->at(0)->Clone("E217_LHCb8TeV_WPlus_Final");
 E217_LHCb8TeV_WMinus_Final = (TH1D *)E217_LHCb8TeV_WMinus->at(0)->Clone("E217_LHCb8TeV_WMinus_Final");

 nBin = GetNBin(vector<TH1D *>{E217_LHCb8TeV_WPlus_Final, E217_LHCb8TeV_WMinus_Final});
 m_theory = PushTheory(vector<TH1D *>{E217_LHCb8TeV_WPlus_Final, E217_LHCb8TeV_WMinus_Final});
 SaveTheory(E217_Final, "E217_Final", nBin, m_theory);
 nBin = 0; m_theory.clear();
}

void HistsResBosCMS::Save()
{
 hf->cd();

 AFB_Mass_ZY_ZPt->Write();

 if(RootType != "FittingCMSData"){
   AFB_Mass_ZY_ZPt_uu->Write();
   AFB_Mass_ZY_ZPt_dd->Write();

   CoefficientDilution_ZMass_ZY_QT_uu->Write();
   CoefficientDilution_ZMass_ZY_QT_dd->Write();

   DilutionAverage_ZMass_ZY_QT_uu->Write();
   DilutionAverage_ZMass_ZY_QT_dd->Write();

   ResidualDilution_ZMass_ZY_QT_uu->Write();
   ResidualDilution_ZMass_ZY_QT_dd->Write();

   OneMinusTwoD_uu->Write();
   OneMinusTwoD_dd->Write();

   RelativeCrossSection_uu->Write();
   RelativeCrossSection_dd->Write();
 }
}

void HistsResBosCMS::Reset()
{
 AFB_Mass_ZY_ZPt->Reset();

 if(RootType != "FittingCMSData"){
   AFB_Mass_ZY_ZPt_uu->Reset();
   AFB_Mass_ZY_ZPt_dd->Reset();

   CoefficientDilution_ZMass_ZY_QT_uu->Reset();
   CoefficientDilution_ZMass_ZY_QT_dd->Reset();

   DilutionAverage_ZMass_ZY_QT_uu->Reset();
   DilutionAverage_ZMass_ZY_QT_dd->Reset();

   ResidualDilution_ZMass_ZY_QT_uu->Reset();
   ResidualDilution_ZMass_ZY_QT_dd->Reset();

   OneMinusTwoD_uu->Reset();
   OneMinusTwoD_dd->Reset();

   RelativeCrossSection_uu->Reset();
   RelativeCrossSection_dd->Reset();
 }
}

void HistsResBosCMS::ReadData()
{
 ///////////////////////////
 //  Read published data  //
 ///////////////////////////

 if(DataList.size() == 66){

   TString DataName_ATLAS8TeV_pT_Mass12_20 = DataList.at(0);
   TString DataName_ATLAS8TeV_pT_Mass20_30 = DataList.at(1);
   TString DataName_ATLAS8TeV_pT_Mass30_46 = DataList.at(2);
   TString DataName_ATLAS8TeV_pT_Mass46_66 = DataList.at(3);
   TString DataName_ATLAS8TeV_pT_Mass66_116 = DataList.at(4);
   TString DataName_ATLAS8TeV_pT_Mass116_150 = DataList.at(5);
   TString DataName_ATLAS8TeV_Phi_Y1 = DataList.at(6);
   TString DataName_ATLAS8TeV_Phi_Y2 = DataList.at(7);
   TString DataName_ATLAS8TeV_Phi_Y3 = DataList.at(8);
   TString DataName_ATLAS8TeV_Phi_Y4 = DataList.at(9);
   TString DataName_ATLAS8TeV_Phi_Y5 = DataList.at(10);
   TString DataName_ATLAS8TeV_Phi_Y6 = DataList.at(11);
   TString DataName_ATLAS8TeV_pT_Y1 = DataList.at(12);
   TString DataName_ATLAS8TeV_pT_Y2 = DataList.at(13);
   TString DataName_ATLAS8TeV_pT_Y3 = DataList.at(14);
   TString DataName_ATLAS8TeV_pT_Y4 = DataList.at(15);
   TString DataName_ATLAS8TeV_pT_Y5 = DataList.at(16);
   TString DataName_ATLAS8TeV_pT_Y6 = DataList.at(17);
   TString DataName_ATLAS13TeV_pT = DataList.at(18);
   TString DataName_ATLAS13TeV_Phi = DataList.at(19);
   TString DataName_CMS13TeV_pT = DataList.at(20);
   TString DataName_CMS13TeV_Phi = DataList.at(21);
   TString DataName_LHCb13TeV_pT = DataList.at(22);
   TString DataName_LHCb13TeV_Phi = DataList.at(23);
   TString DataName_CMS13TeV_pT_Y1 = DataList.at(24);
   TString DataName_CMS13TeV_pT_Y2 = DataList.at(25);
   TString DataName_CMS13TeV_pT_Y3 = DataList.at(26);
   TString DataName_CMS13TeV_pT_Y4 = DataList.at(27);
   TString DataName_CMS13TeV_pT_Y5 = DataList.at(28);
   TString DataName_CMS13TeV_yZ = DataList.at(29);
   TString DataName_ATLAS8TeV_A0 = DataList.at(30);
   TString DataName_ATLAS8TeV_A1 = DataList.at(31);
   TString DataName_ATLAS8TeV_A2 = DataList.at(32);
   TString DataName_ATLAS8TeV_A3 = DataList.at(33);
   TString DataName_ATLAS8TeV_A4 = DataList.at(34);
   TString DataName_ATLAS8TeV_A02 = DataList.at(35);
   TString DataName_ATLAS8TeV_A0_UnReg = DataList.at(36);
   TString DataName_ATLAS8TeV_A1_UnReg = DataList.at(37);
   TString DataName_ATLAS8TeV_A2_UnReg = DataList.at(38);
   TString DataName_ATLAS8TeV_A3_UnReg = DataList.at(39);
   TString DataName_ATLAS8TeV_A4_UnReg = DataList.at(40);
   TString DataName_ATLAS8TeV_A02_UnReg = DataList.at(41);

   TString NLO_ATLAS8TeV_pT_Y1 = DataList.at(42);
   TString NLO_ATLAS8TeV_pT_Y2 = DataList.at(43);
   TString NLO_ATLAS8TeV_pT_Y3 = DataList.at(44);
   TString NLO_ATLAS8TeV_pT_Y4 = DataList.at(45);
   TString NLO_ATLAS8TeV_pT_Y5 = DataList.at(46);
   TString NLO_ATLAS8TeV_pT_Y6 = DataList.at(47);
   TString NLO_ATLAS8TeV_pT_Mass66_116 = DataList.at(48);
   TString NNLO_ATLAS8TeV_pT_Y1 = DataList.at(49);
   TString NNLO_ATLAS8TeV_pT_Y2 = DataList.at(50);
   TString NNLO_ATLAS8TeV_pT_Y3 = DataList.at(51);
   TString NNLO_ATLAS8TeV_pT_Y4 = DataList.at(52);
   TString NNLO_ATLAS8TeV_pT_Y5 = DataList.at(53);
   TString NNLO_ATLAS8TeV_pT_Y6 = DataList.at(54);
   TString NNLO_ATLAS8TeV_pT_Mass66_116 = DataList.at(55);

   TString DataName_ATLAS7TeV_pT = DataList.at(56);
   TString DataName_ATLAS7TeV_pT_Y1 = DataList.at(57);
   TString DataName_ATLAS7TeV_pT_Y2 = DataList.at(58);
   TString DataName_ATLAS7TeV_pT_Y3 = DataList.at(59);
   TString DataName_CMS8TeV_pT = DataList.at(60);
   TString DataName_CMS7TeV_pT = DataList.at(61);
   TString DataName_ATLAS7TeV_Phi = DataList.at(62);
   TString DataName_ATLAS7TeV_Phi_Y1 = DataList.at(63);
   TString DataName_ATLAS7TeV_Phi_Y2 = DataList.at(64);
   TString DataName_ATLAS7TeV_Phi_Y3 = DataList.at(65);

   ATLAS8TeV_pT_Mass12_20_Data = (TH1D *)ATLAS8TeV_pT_Mass12_20_Theory->at(0)->Clone("ATLAS8TeV_pT_Mass12_20_Data");
   ATLAS8TeV_pT_Mass20_30_Data = (TH1D *)ATLAS8TeV_pT_Mass20_30_Theory->at(0)->Clone("ATLAS8TeV_pT_Mass20_30_Data");
   ATLAS8TeV_pT_Mass30_46_Data = (TH1D *)ATLAS8TeV_pT_Mass30_46_Theory->at(0)->Clone("ATLAS8TeV_pT_Mass30_46_Data");
   ATLAS8TeV_pT_Mass46_66_Data = (TH1D *)ATLAS8TeV_pT_Mass46_66_Theory->at(0)->Clone("ATLAS8TeV_pT_Mass46_66_Data");
   ATLAS8TeV_pT_Mass66_116_Data = (TH1D *)ATLAS8TeV_pT_Mass66_116_Theory->at(0)->Clone("ATLAS8TeV_pT_Mass66_116_Data");
   ATLAS8TeV_pT_Mass116_150_Data = (TH1D *)ATLAS8TeV_pT_Mass116_150_Theory->at(0)->Clone("ATLAS8TeV_pT_Mass116_150_Data");
   ATLAS8TeV_Phi_Y1_Data = (TH1D *)ATLAS8TeV_Phi_Y1_Theory->at(0)->Clone("ATLAS8TeV_Phi_Y1_Data");
   ATLAS8TeV_Phi_Y2_Data = (TH1D *)ATLAS8TeV_Phi_Y2_Theory->at(0)->Clone("ATLAS8TeV_Phi_Y2_Data");
   ATLAS8TeV_Phi_Y3_Data = (TH1D *)ATLAS8TeV_Phi_Y3_Theory->at(0)->Clone("ATLAS8TeV_Phi_Y3_Data");
   ATLAS8TeV_Phi_Y4_Data = (TH1D *)ATLAS8TeV_Phi_Y4_Theory->at(0)->Clone("ATLAS8TeV_Phi_Y4_Data");
   ATLAS8TeV_Phi_Y5_Data = (TH1D *)ATLAS8TeV_Phi_Y5_Theory->at(0)->Clone("ATLAS8TeV_Phi_Y5_Data");
   ATLAS8TeV_Phi_Y6_Data = (TH1D *)ATLAS8TeV_Phi_Y6_Theory->at(0)->Clone("ATLAS8TeV_Phi_Y6_Data");
   ATLAS8TeV_pT_Y1_Data = (TH1D *)ATLAS8TeV_pT_Y1_Theory->at(0)->Clone("ATLAS8TeV_pT_Y1_Data");
   ATLAS8TeV_pT_Y2_Data = (TH1D *)ATLAS8TeV_pT_Y2_Theory->at(0)->Clone("ATLAS8TeV_pT_Y2_Data");
   ATLAS8TeV_pT_Y3_Data = (TH1D *)ATLAS8TeV_pT_Y3_Theory->at(0)->Clone("ATLAS8TeV_pT_Y3_Data");
   ATLAS8TeV_pT_Y4_Data = (TH1D *)ATLAS8TeV_pT_Y4_Theory->at(0)->Clone("ATLAS8TeV_pT_Y4_Data");
   ATLAS8TeV_pT_Y5_Data = (TH1D *)ATLAS8TeV_pT_Y5_Theory->at(0)->Clone("ATLAS8TeV_pT_Y5_Data");
   ATLAS8TeV_pT_Y6_Data = (TH1D *)ATLAS8TeV_pT_Y6_Theory->at(0)->Clone("ATLAS8TeV_pT_Y6_Data");
   ATLAS13TeV_pT_Data = (TH1D *)ATLAS13TeV_pT_Theory->at(0)->Clone("ATLAS13TeV_pT_Data");
   ATLAS13TeV_Phi_Data = (TH1D *)ATLAS13TeV_Phi_Theory->at(0)->Clone("ATLAS13TeV_Phi_Data");
   CMS13TeV_pT_Data = (TH1D *)CMS13TeV_pT_Theory->at(0)->Clone("CMS13TeV_pT_Data");
   CMS13TeV_Phi_Data = (TH1D *)CMS13TeV_Phi_Theory->at(0)->Clone("CMS13TeV_Phi_Data");
   LHCb13TeV_pT_Data = (TH1D *)LHCb13TeV_pT_Theory->at(0)->Clone("LHCb13TeV_pT_Data");
   LHCb13TeV_Phi_Data = (TH1D *)LHCb13TeV_Phi_Theory->at(0)->Clone("LHCb13TeV_Phi_Data");
   CMS13TeV_pT_Y1_Data = (TH1D *)CMS13TeV_pT_Y1_Theory->at(0)->Clone("CMS13TeV_pT_Y1_Data");
   CMS13TeV_pT_Y2_Data = (TH1D *)CMS13TeV_pT_Y2_Theory->at(0)->Clone("CMS13TeV_pT_Y2_Data");
   CMS13TeV_pT_Y3_Data = (TH1D *)CMS13TeV_pT_Y3_Theory->at(0)->Clone("CMS13TeV_pT_Y3_Data");
   CMS13TeV_pT_Y4_Data = (TH1D *)CMS13TeV_pT_Y4_Theory->at(0)->Clone("CMS13TeV_pT_Y4_Data");
   CMS13TeV_pT_Y5_Data = (TH1D *)CMS13TeV_pT_Y5_Theory->at(0)->Clone("CMS13TeV_pT_Y5_Data");
   CMS13TeV_yZ_Data = (TH1D *)CMS13TeV_yZ_Theory->at(0)->Clone("CMS13TeV_yZ_Data");
   ATLAS8TeV_A0_pT_Data = (TH1D *)ATLAS8TeV_A0_pT_Theory->at(0)->AngularHist1D->Clone("ATLAS8TeV_A0_pT_Data");
   ATLAS8TeV_A1_pT_Data = (TH1D *)ATLAS8TeV_A1_pT_Theory->at(0)->AngularHist1D->Clone("ATLAS8TeV_A1_pT_Data");
   ATLAS8TeV_A2_pT_Data = (TH1D *)ATLAS8TeV_A2_pT_Theory->at(0)->AngularHist1D->Clone("ATLAS8TeV_A2_pT_Data");
   ATLAS8TeV_A3_pT_Data = (TH1D *)ATLAS8TeV_A3_pT_Theory->at(0)->AngularHist1D->Clone("ATLAS8TeV_A3_pT_Data");
   ATLAS8TeV_A4_pT_Data = (TH1D *)ATLAS8TeV_A4_pT_Theory->at(0)->AngularHist1D->Clone("ATLAS8TeV_A4_pT_Data");
   ATLAS8TeV_A02_pT_Data = (TH1D *)ATLAS8TeV_A02_pT_Theory->at(0)->AngularHist1D->Clone("ATLAS8TeV_A02_pT_Data");
   ATLAS8TeV_A0_pT_Data_UnReg = (TH1D *)ATLAS8TeV_A0_pT_Theory->at(0)->AngularHist1D->Clone("ATLAS8TeV_A0_pT_Data_UnReg");
   ATLAS8TeV_A1_pT_Data_UnReg = (TH1D *)ATLAS8TeV_A1_pT_Theory->at(0)->AngularHist1D->Clone("ATLAS8TeV_A1_pT_Data_UnReg");
   ATLAS8TeV_A2_pT_Data_UnReg = (TH1D *)ATLAS8TeV_A2_pT_Theory->at(0)->AngularHist1D->Clone("ATLAS8TeV_A2_pT_Data_UnReg");
   ATLAS8TeV_A3_pT_Data_UnReg = (TH1D *)ATLAS8TeV_A3_pT_Theory->at(0)->AngularHist1D->Clone("ATLAS8TeV_A3_pT_Data_UnReg");
   ATLAS8TeV_A4_pT_Data_UnReg = (TH1D *)ATLAS8TeV_A4_pT_Theory->at(0)->AngularHist1D->Clone("ATLAS8TeV_A4_pT_Data_UnReg");
   ATLAS8TeV_A02_pT_Data_UnReg = (TH1D *)ATLAS8TeV_A02_pT_Theory->at(0)->AngularHist1D->Clone("ATLAS8TeV_A02_pT_Data_UnReg");

   ATLAS7TeV_pT_Data = (TH1D *)ATLAS7TeV_pT_Theory->at(0)->Clone("ATLAS7TeV_pT_Data");
   ATLAS7TeV_pT_Y1_Data = (TH1D *)ATLAS7TeV_pT_Y1_Theory->at(0)->Clone("ATLAS7TeV_pT_Y1_Data");
   ATLAS7TeV_pT_Y2_Data = (TH1D *)ATLAS7TeV_pT_Y2_Theory->at(0)->Clone("ATLAS7TeV_pT_Y2_Data");
   ATLAS7TeV_pT_Y3_Data = (TH1D *)ATLAS7TeV_pT_Y3_Theory->at(0)->Clone("ATLAS7TeV_pT_Y3_Data");
   CMS8TeV_pT_Data = (TH1D *)CMS8TeV_pT_Theory->at(0)->Clone("CMS8TeV_pT_Data");
   CMS7TeV_pT_Data = (TH1D *)CMS7TeV_pT_Theory->at(0)->Clone("CMS7TeV_pT_Data");
   ATLAS7TeV_Phi_Data = (TH1D *)ATLAS7TeV_Phi_Theory->at(0)->Clone("ATLAS7TeV_Phi_Data");
   ATLAS7TeV_Phi_Y1_Data = (TH1D *)ATLAS7TeV_Phi_Y1_Theory->at(0)->Clone("ATLAS7TeV_Phi_Y1_Data");
   ATLAS7TeV_Phi_Y2_Data = (TH1D *)ATLAS7TeV_Phi_Y2_Theory->at(0)->Clone("ATLAS7TeV_Phi_Y2_Data");
   ATLAS7TeV_Phi_Y3_Data = (TH1D *)ATLAS7TeV_Phi_Y3_Theory->at(0)->Clone("ATLAS7TeV_Phi_Y3_Data");

   ATLAS8TeV_pT_Y1_KFactor = (TH1D *)ATLAS8TeV_pT_Y1_Theory->at(0)->Clone("ATLAS8TeV_pT_Y1_KFactor");
   ATLAS8TeV_pT_Y2_KFactor = (TH1D *)ATLAS8TeV_pT_Y2_Theory->at(0)->Clone("ATLAS8TeV_pT_Y2_KFactor");
   ATLAS8TeV_pT_Y3_KFactor = (TH1D *)ATLAS8TeV_pT_Y3_Theory->at(0)->Clone("ATLAS8TeV_pT_Y3_KFactor");
   ATLAS8TeV_pT_Y4_KFactor = (TH1D *)ATLAS8TeV_pT_Y4_Theory->at(0)->Clone("ATLAS8TeV_pT_Y4_KFactor");
   ATLAS8TeV_pT_Y5_KFactor = (TH1D *)ATLAS8TeV_pT_Y5_Theory->at(0)->Clone("ATLAS8TeV_pT_Y5_KFactor");
   ATLAS8TeV_pT_Y6_KFactor = (TH1D *)ATLAS8TeV_pT_Y6_Theory->at(0)->Clone("ATLAS8TeV_pT_Y6_KFactor");
   ATLAS8TeV_pT_Mass66_116_KFactor = (TH1D *)ATLAS8TeV_pT_Mass66_116_Theory->at(0)->Clone("ATLAS8TeV_pT_Mass66_116_KFactor");
   ATLAS8TeV_pT_Y1_Theory_HigherOrder = (TH1D *)ATLAS8TeV_pT_Y1_Theory->at(0)->Clone("ATLAS8TeV_pT_Y1_Theory_HigherOrder");
   ATLAS8TeV_pT_Y2_Theory_HigherOrder = (TH1D *)ATLAS8TeV_pT_Y2_Theory->at(0)->Clone("ATLAS8TeV_pT_Y2_Theory_HigherOrder");
   ATLAS8TeV_pT_Y3_Theory_HigherOrder = (TH1D *)ATLAS8TeV_pT_Y3_Theory->at(0)->Clone("ATLAS8TeV_pT_Y3_Theory_HigherOrder");
   ATLAS8TeV_pT_Y4_Theory_HigherOrder = (TH1D *)ATLAS8TeV_pT_Y4_Theory->at(0)->Clone("ATLAS8TeV_pT_Y4_Theory_HigherOrder");
   ATLAS8TeV_pT_Y5_Theory_HigherOrder = (TH1D *)ATLAS8TeV_pT_Y5_Theory->at(0)->Clone("ATLAS8TeV_pT_Y5_Theory_HigherOrder");
   ATLAS8TeV_pT_Y6_Theory_HigherOrder = (TH1D *)ATLAS8TeV_pT_Y6_Theory->at(0)->Clone("ATLAS8TeV_pT_Y6_Theory_HigherOrder");
   ATLAS8TeV_pT_Mass66_116_Theory_HigherOrder = (TH1D *)ATLAS8TeV_pT_Mass66_116_Theory->at(0)->Clone("ATLAS8TeV_pT_Mass66_116_Theory_HigherOrder");

   ResBosZPt* file_ATLAS8TeV_pT_Mass12_20 = new ResBosZPt(DataName_ATLAS8TeV_pT_Mass12_20);
   file_ATLAS8TeV_pT_Mass12_20->WriteIn(ATLAS8TeV_pT_Mass12_20_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_pT_Mass20_30 = new ResBosZPt(DataName_ATLAS8TeV_pT_Mass20_30);
   file_ATLAS8TeV_pT_Mass20_30->WriteIn(ATLAS8TeV_pT_Mass20_30_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_pT_Mass30_46 = new ResBosZPt(DataName_ATLAS8TeV_pT_Mass30_46);
   file_ATLAS8TeV_pT_Mass30_46->WriteIn(ATLAS8TeV_pT_Mass30_46_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_pT_Mass46_66 = new ResBosZPt(DataName_ATLAS8TeV_pT_Mass46_66);
   file_ATLAS8TeV_pT_Mass46_66->WriteIn(ATLAS8TeV_pT_Mass46_66_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_pT_Mass66_116 = new ResBosZPt(DataName_ATLAS8TeV_pT_Mass66_116);
   file_ATLAS8TeV_pT_Mass66_116->WriteIn(ATLAS8TeV_pT_Mass66_116_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_pT_Mass116_150 = new ResBosZPt(DataName_ATLAS8TeV_pT_Mass116_150);
   file_ATLAS8TeV_pT_Mass116_150->WriteIn(ATLAS8TeV_pT_Mass116_150_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_Phi_Y1 = new ResBosZPt(DataName_ATLAS8TeV_Phi_Y1);
   file_ATLAS8TeV_Phi_Y1->WriteIn(ATLAS8TeV_Phi_Y1_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_Phi_Y2 = new ResBosZPt(DataName_ATLAS8TeV_Phi_Y2);
   file_ATLAS8TeV_Phi_Y2->WriteIn(ATLAS8TeV_Phi_Y2_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_Phi_Y3 = new ResBosZPt(DataName_ATLAS8TeV_Phi_Y3);
   file_ATLAS8TeV_Phi_Y3->WriteIn(ATLAS8TeV_Phi_Y3_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_Phi_Y4 = new ResBosZPt(DataName_ATLAS8TeV_Phi_Y4);
   file_ATLAS8TeV_Phi_Y4->WriteIn(ATLAS8TeV_Phi_Y4_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_Phi_Y5 = new ResBosZPt(DataName_ATLAS8TeV_Phi_Y5);
   file_ATLAS8TeV_Phi_Y5->WriteIn(ATLAS8TeV_Phi_Y5_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_Phi_Y6 = new ResBosZPt(DataName_ATLAS8TeV_Phi_Y6);
   file_ATLAS8TeV_Phi_Y6->WriteIn(ATLAS8TeV_Phi_Y6_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_pT_Y1 = new ResBosZPt(DataName_ATLAS8TeV_pT_Y1);
   file_ATLAS8TeV_pT_Y1->WriteIn(ATLAS8TeV_pT_Y1_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_pT_Y2 = new ResBosZPt(DataName_ATLAS8TeV_pT_Y2);
   file_ATLAS8TeV_pT_Y2->WriteIn(ATLAS8TeV_pT_Y2_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_pT_Y3 = new ResBosZPt(DataName_ATLAS8TeV_pT_Y3);
   file_ATLAS8TeV_pT_Y3->WriteIn(ATLAS8TeV_pT_Y3_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_pT_Y4 = new ResBosZPt(DataName_ATLAS8TeV_pT_Y4);
   file_ATLAS8TeV_pT_Y4->WriteIn(ATLAS8TeV_pT_Y4_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_pT_Y5 = new ResBosZPt(DataName_ATLAS8TeV_pT_Y5);
   file_ATLAS8TeV_pT_Y5->WriteIn(ATLAS8TeV_pT_Y5_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_pT_Y6 = new ResBosZPt(DataName_ATLAS8TeV_pT_Y6);
   file_ATLAS8TeV_pT_Y6->WriteIn(ATLAS8TeV_pT_Y6_Data, 10, true);

   ResBosZPt* file_ATLAS13TeV_pT = new ResBosZPt(DataName_ATLAS13TeV_pT);
   file_ATLAS13TeV_pT->WriteIn(ATLAS13TeV_pT_Data, 6, false);

   ResBosZPt* file_ATLAS13TeV_Phi = new ResBosZPt(DataName_ATLAS13TeV_Phi);
   file_ATLAS13TeV_Phi->WriteIn(ATLAS13TeV_Phi_Data, 6, false);

   ResBosZPt* file_CMS13TeV_pT = new ResBosZPt(DataName_CMS13TeV_pT);
   file_CMS13TeV_pT->WriteIn(CMS13TeV_pT_Data, 4, false);

   ResBosZPt* file_CMS13TeV_Phi = new ResBosZPt(DataName_CMS13TeV_Phi);
   file_CMS13TeV_Phi->WriteIn(CMS13TeV_Phi_Data, 6, false);

   ResBosZPt* file_LHCb13TeV_pT = new ResBosZPt(DataName_LHCb13TeV_pT);
   file_LHCb13TeV_pT->InputPhaseSpace(60.0, 120.0, 2.0, 4.5);
   file_LHCb13TeV_pT->WriteIn(LHCb13TeV_pT_Data, 10, false);

   ResBosZPt* file_LHCb13TeV_Phi = new ResBosZPt(DataName_LHCb13TeV_Phi);
   file_LHCb13TeV_Phi->WriteIn(LHCb13TeV_Phi_Data, 10, false);

   ResBosZPt* file_CMS13TeV_pT_Y1 = new ResBosZPt(DataName_CMS13TeV_pT_Y1);
   file_CMS13TeV_pT_Y1->InputPhaseSpace(76.1876, 106.1876, 0.0, 0.4);
   file_CMS13TeV_pT_Y1->WriteIn(CMS13TeV_pT_Y1_Data, 4, false);

   ResBosZPt* file_CMS13TeV_pT_Y2 = new ResBosZPt(DataName_CMS13TeV_pT_Y2);
   file_CMS13TeV_pT_Y2->InputPhaseSpace(76.1876, 106.1876, 0.4, 0.8);
   file_CMS13TeV_pT_Y2->WriteIn(CMS13TeV_pT_Y2_Data, 4, false);

   ResBosZPt* file_CMS13TeV_pT_Y3 = new ResBosZPt(DataName_CMS13TeV_pT_Y3);
   file_CMS13TeV_pT_Y3->InputPhaseSpace(76.1876, 106.1876, 0.8, 1.2);
   file_CMS13TeV_pT_Y3->WriteIn(CMS13TeV_pT_Y3_Data, 4, false);

   ResBosZPt* file_CMS13TeV_pT_Y4 = new ResBosZPt(DataName_CMS13TeV_pT_Y4);
   file_CMS13TeV_pT_Y4->InputPhaseSpace(76.1876, 106.1876, 1.2, 1.6);
   file_CMS13TeV_pT_Y4->WriteIn(CMS13TeV_pT_Y4_Data, 4, false);

   ResBosZPt* file_CMS13TeV_pT_Y5 = new ResBosZPt(DataName_CMS13TeV_pT_Y5);
   file_CMS13TeV_pT_Y5->InputPhaseSpace(76.1876, 106.1876, 1.6, 2.4);
   file_CMS13TeV_pT_Y5->WriteIn(CMS13TeV_pT_Y5_Data, 4, false);

   ResBosZPt* file_CMS13TeV_yZ = new ResBosZPt(DataName_CMS13TeV_yZ);
   file_CMS13TeV_yZ->WriteIn(CMS13TeV_yZ_Data, 6, false);

   ResBosZPt* file_ATLAS8TeV_A0 = new ResBosZPt(DataName_ATLAS8TeV_A0);
   file_ATLAS8TeV_A0->WriteIn(ATLAS8TeV_A0_pT_Data, 10, false);

   ResBosZPt* file_ATLAS8TeV_A1 = new ResBosZPt(DataName_ATLAS8TeV_A1);
   file_ATLAS8TeV_A1->WriteIn(ATLAS8TeV_A1_pT_Data, 10, false);

   ResBosZPt* file_ATLAS8TeV_A2 = new ResBosZPt(DataName_ATLAS8TeV_A2);
   file_ATLAS8TeV_A2->WriteIn(ATLAS8TeV_A2_pT_Data, 10, false);

   ResBosZPt* file_ATLAS8TeV_A3 = new ResBosZPt(DataName_ATLAS8TeV_A3);
   file_ATLAS8TeV_A3->WriteIn(ATLAS8TeV_A3_pT_Data, 10, false);

   ResBosZPt* file_ATLAS8TeV_A4 = new ResBosZPt(DataName_ATLAS8TeV_A4);
   file_ATLAS8TeV_A4->WriteIn(ATLAS8TeV_A4_pT_Data, 10, false);

   ResBosZPt* file_ATLAS8TeV_A02 = new ResBosZPt(DataName_ATLAS8TeV_A02);
   file_ATLAS8TeV_A02->WriteIn(ATLAS8TeV_A02_pT_Data, 10, false);

   ResBosZPt* file_ATLAS8TeV_A0_UnReg = new ResBosZPt(DataName_ATLAS8TeV_A0_UnReg);
   file_ATLAS8TeV_A0_UnReg->WriteIn(ATLAS8TeV_A0_pT_Data_UnReg, 8, false);

   ResBosZPt* file_ATLAS8TeV_A1_UnReg = new ResBosZPt(DataName_ATLAS8TeV_A1_UnReg);
   file_ATLAS8TeV_A1_UnReg->WriteIn(ATLAS8TeV_A1_pT_Data_UnReg, 8, false);

   ResBosZPt* file_ATLAS8TeV_A2_UnReg = new ResBosZPt(DataName_ATLAS8TeV_A2_UnReg);
   file_ATLAS8TeV_A2_UnReg->WriteIn(ATLAS8TeV_A2_pT_Data_UnReg, 8, false);

   ResBosZPt* file_ATLAS8TeV_A3_UnReg = new ResBosZPt(DataName_ATLAS8TeV_A3_UnReg);
   file_ATLAS8TeV_A3_UnReg->WriteIn(ATLAS8TeV_A3_pT_Data_UnReg, 8, false);

   ResBosZPt* file_ATLAS8TeV_A4_UnReg = new ResBosZPt(DataName_ATLAS8TeV_A4_UnReg);
   file_ATLAS8TeV_A4_UnReg->WriteIn(ATLAS8TeV_A4_pT_Data_UnReg, 8, false);

   ResBosZPt* file_ATLAS8TeV_A02_UnReg = new ResBosZPt(DataName_ATLAS8TeV_A02_UnReg);
   file_ATLAS8TeV_A02_UnReg->WriteIn(ATLAS8TeV_A02_pT_Data_UnReg, 8, false);

   ResBosZPt* file_ATLAS7TeV_pT = new ResBosZPt(DataName_ATLAS7TeV_pT);
   file_ATLAS7TeV_pT->WriteIn(ATLAS7TeV_pT_Data, 10, true);

   ResBosZPt* file_ATLAS7TeV_pT_Y1 = new ResBosZPt(DataName_ATLAS7TeV_pT_Y1);
   file_ATLAS7TeV_pT_Y1->WriteIn(ATLAS7TeV_pT_Y1_Data, 10, true);

   ResBosZPt* file_ATLAS7TeV_pT_Y2 = new ResBosZPt(DataName_ATLAS7TeV_pT_Y2);
   file_ATLAS7TeV_pT_Y2->WriteIn(ATLAS7TeV_pT_Y2_Data, 10, true);

   ResBosZPt* file_ATLAS7TeV_pT_Y3 = new ResBosZPt(DataName_ATLAS7TeV_pT_Y3);
   file_ATLAS7TeV_pT_Y3->WriteIn(ATLAS7TeV_pT_Y3_Data, 10, true);

   ResBosZPt* file_CMS8TeV_pT = new ResBosZPt(DataName_CMS8TeV_pT);
   file_CMS8TeV_pT->WriteIn(CMS8TeV_pT_Data, 6, false);

   ResBosZPt* file_CMS7TeV_pT = new ResBosZPt(DataName_CMS7TeV_pT);
   file_CMS7TeV_pT->WriteIn(CMS7TeV_pT_Data, 6, false);

   ResBosZPt* file_ATLAS7TeV_Phi = new ResBosZPt(DataName_ATLAS7TeV_Phi);
   file_ATLAS7TeV_Phi->WriteIn(ATLAS7TeV_Phi_Data, 10, true);

   ResBosZPt* file_ATLAS7TeV_Phi_Y1 = new ResBosZPt(DataName_ATLAS7TeV_Phi_Y1);
   file_ATLAS7TeV_Phi_Y1->WriteIn(ATLAS7TeV_Phi_Y1_Data, 10, true);

   ResBosZPt* file_ATLAS7TeV_Phi_Y2 = new ResBosZPt(DataName_ATLAS7TeV_Phi_Y2);
   file_ATLAS7TeV_Phi_Y2->WriteIn(ATLAS7TeV_Phi_Y2_Data, 10, true);

   ResBosZPt* file_ATLAS7TeV_Phi_Y3 = new ResBosZPt(DataName_ATLAS7TeV_Phi_Y3);
   file_ATLAS7TeV_Phi_Y3->WriteIn(ATLAS7TeV_Phi_Y3_Data, 10, true);

   ResBosZPt* file_ATLAS8TeV_pT_Y1_KFactor = new ResBosZPt();
   file_ATLAS8TeV_pT_Y1_KFactor->ReadKFactor(ATLAS8TeV_pT_Y1_KFactor, NNLO_ATLAS8TeV_pT_Y1, NLO_ATLAS8TeV_pT_Y1);

   ResBosZPt* file_ATLAS8TeV_pT_Y2_KFactor = new ResBosZPt();
   file_ATLAS8TeV_pT_Y2_KFactor->ReadKFactor(ATLAS8TeV_pT_Y2_KFactor, NNLO_ATLAS8TeV_pT_Y2, NLO_ATLAS8TeV_pT_Y2);

   ResBosZPt* file_ATLAS8TeV_pT_Y3_KFactor = new ResBosZPt();
   file_ATLAS8TeV_pT_Y3_KFactor->ReadKFactor(ATLAS8TeV_pT_Y3_KFactor, NNLO_ATLAS8TeV_pT_Y3, NLO_ATLAS8TeV_pT_Y3);

   ResBosZPt* file_ATLAS8TeV_pT_Y4_KFactor = new ResBosZPt();
   file_ATLAS8TeV_pT_Y4_KFactor->ReadKFactor(ATLAS8TeV_pT_Y4_KFactor, NNLO_ATLAS8TeV_pT_Y4, NLO_ATLAS8TeV_pT_Y4);

   ResBosZPt* file_ATLAS8TeV_pT_Y5_KFactor = new ResBosZPt();
   file_ATLAS8TeV_pT_Y5_KFactor->ReadKFactor(ATLAS8TeV_pT_Y5_KFactor, NNLO_ATLAS8TeV_pT_Y5, NLO_ATLAS8TeV_pT_Y5);

   ResBosZPt* file_ATLAS8TeV_pT_Y6_KFactor = new ResBosZPt();
   file_ATLAS8TeV_pT_Y6_KFactor->ReadKFactor(ATLAS8TeV_pT_Y6_KFactor, NNLO_ATLAS8TeV_pT_Y6, NLO_ATLAS8TeV_pT_Y6);

   ResBosZPt* file_ATLAS8TeV_pT_Mass66_116_KFactor = new ResBosZPt();
   file_ATLAS8TeV_pT_Mass66_116_KFactor->ReadKFactor(ATLAS8TeV_pT_Mass66_116_KFactor, NNLO_ATLAS8TeV_pT_Mass66_116, NLO_ATLAS8TeV_pT_Mass66_116);

   ATLAS8TeV_pT_Mass12_20_Data->Write();
   ATLAS8TeV_pT_Mass20_30_Data->Write();
   ATLAS8TeV_pT_Mass30_46_Data->Write();
   ATLAS8TeV_pT_Mass46_66_Data->Write();
   ATLAS8TeV_pT_Mass66_116_Data->Write();
   ATLAS8TeV_pT_Mass116_150_Data->Write();
   ATLAS8TeV_Phi_Y1_Data->Write();
   ATLAS8TeV_Phi_Y2_Data->Write();
   ATLAS8TeV_Phi_Y3_Data->Write();
   ATLAS8TeV_Phi_Y4_Data->Write();
   ATLAS8TeV_Phi_Y5_Data->Write();
   ATLAS8TeV_Phi_Y6_Data->Write();
   ATLAS8TeV_pT_Y1_Data->Write();
   ATLAS8TeV_pT_Y2_Data->Write();
   ATLAS8TeV_pT_Y3_Data->Write();
   ATLAS8TeV_pT_Y4_Data->Write();
   ATLAS8TeV_pT_Y5_Data->Write();
   ATLAS8TeV_pT_Y6_Data->Write();
   ATLAS13TeV_pT_Data->Write();
   ATLAS13TeV_Phi_Data->Write();
   CMS13TeV_pT_Data->Write();
   CMS13TeV_Phi_Data->Write();
   LHCb13TeV_pT_Data->Write();
   LHCb13TeV_Phi_Data->Write();
   CMS13TeV_pT_Y1_Data->Write();
   CMS13TeV_pT_Y2_Data->Write();
   CMS13TeV_pT_Y3_Data->Write();
   CMS13TeV_pT_Y4_Data->Write();
   CMS13TeV_pT_Y5_Data->Write();
   CMS13TeV_yZ_Data->Write();
   ATLAS8TeV_A0_pT_Data->Write();
   ATLAS8TeV_A1_pT_Data->Write();
   ATLAS8TeV_A2_pT_Data->Write();
   ATLAS8TeV_A3_pT_Data->Write();
   ATLAS8TeV_A4_pT_Data->Write();
   ATLAS8TeV_A02_pT_Data->Write();
   ATLAS8TeV_A0_pT_Data_UnReg->Write();
   ATLAS8TeV_A1_pT_Data_UnReg->Write();
   ATLAS8TeV_A2_pT_Data_UnReg->Write();
   ATLAS8TeV_A3_pT_Data_UnReg->Write();
   ATLAS8TeV_A4_pT_Data_UnReg->Write();
   ATLAS8TeV_A02_pT_Data_UnReg->Write();
   ATLAS7TeV_pT_Data->Write();
   ATLAS7TeV_pT_Y1_Data->Write();
   ATLAS7TeV_pT_Y2_Data->Write();
   ATLAS7TeV_pT_Y3_Data->Write();
   CMS8TeV_pT_Data->Write();
   CMS7TeV_pT_Data->Write();
   ATLAS7TeV_Phi_Data->Write();
   ATLAS7TeV_Phi_Y1_Data->Write();
   ATLAS7TeV_Phi_Y2_Data->Write();
   ATLAS7TeV_Phi_Y3_Data->Write();

   ATLAS8TeV_pT_Y1_KFactor->Write();
   ATLAS8TeV_pT_Y2_KFactor->Write();
   ATLAS8TeV_pT_Y3_KFactor->Write();
   ATLAS8TeV_pT_Y4_KFactor->Write();
   ATLAS8TeV_pT_Y5_KFactor->Write();
   ATLAS8TeV_pT_Y6_KFactor->Write();
   ATLAS8TeV_pT_Mass66_116_KFactor->Write();
 }

}

void HistsResBosCMS::InitialSysName()
{

}
