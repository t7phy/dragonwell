#include "Analysis/HistsResBosHighMassZ.h"

using namespace std;

void HistsResBosHighMassZ::bookHists(int TotalThread)
{
 int MassBin = 12;
 double MassBinning[13] = {40, 66, 80, 91, 102, 116, 145, 200, 275, 381, 525, 725, 1000};

 int MassBin_LowMass = 5;
 double MassBinning_LowMass[6] = {40, 66, 80, 91, 102, 116};

 int MassBin_HighMass = 7;
 double MassBinning_HighMass[8] = {116, 145, 200, 275, 381, 525, 725, 1000};

 int ZYCCBin = 12;
 double ZYCCBinning[13] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4};

 int ZYCFBin = 6;
 double ZYCFBinning[7] = {2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6};

 int CosThetaBin = 6;
 double CosThetaBinning[7] = {-1.0, -0.7, -0.4, 0.0, 0.4, 0.7, 1.0};

 int ZYBin = 5;
 double ZYBinning[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

// int CrossSectionBin = 8;
// double CrossSectionBinning[9] = {400.0, 500.0, 700.0, 900.0, 1200.0, 1800.0, 3000.0, 4500.0, 6000.0};

 int CrossSectionBin = 6;
 double CrossSectionBinning[7] = {1000.0, 1300.0, 1800.0, 2500.0, 3200.0, 4000.0, 5000.0};

// int HighMassBin = 25;
// double HighMassBinning[26];
// HighMassBinning[0] = 1000.0;
// for(int i = 1; i <= 25; i++){HighMassBinning[i] = pow(10.0, 3.0 + log10(5.0) * i / 25.0);}

 int HighMassBin = 25;
 double HighMassBinning[26];
 HighMassBinning[0] = 500.0;
 for(int i = 1; i <= 25; i++){HighMassBinning[i] = pow(10.0, 3.0 + log10(0.5) + (log10(5.0) - log10(0.5)) * i / 25.0);}

 int HighMassBin2 = 25;
 vector<double> HighMassBinning2;
 HighMassBinning2 = Logspace(1000.0, 5000.0, 26, 10.0);

 int LowMassBin1 = 25;
 vector<double> LowMassBinning1;
 LowMassBinning1 = Logspace(120.0, 1000.0, 26, 10.0);

 int LowMassBin2 = 30;
 vector<double> LowMassBinning2;
 LowMassBinning2 = Logspace(60.0, 1000.0, 31, 10.0);

 vector<double> FullMassBinning = Logspace(50.0, 5000.0, 70, 10.0);

 vector<double> HighMassBinning_upto10000 = Logspace(60.0, 10000.0, 50, 10.0);

 int xBin = 30;
 vector<double> xBinning;
 xBinning = Logspace(1e-4, 1.0, 31, 10.0);

// int FullMTBin = 44;
// double FullMTBinning[45];
// for(int i = 0; i < 41; i++){ FullMTBinning[i] = 60.0 + i; }
// for(int i = 41; i < 45; i++){ FullMTBinning[i] = 100.0 + 100.0 * (i - 40);}

 int FullMTBin = 5;
 double FullMTBinning[6] = {60.0, 100.0, 200.0, 300.0, 400.0, 500.0};

 int WLeptonEtaBin = 10;
 double WLeptonEtaBinning[11] = {0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5};

// int HighMassBin = 32;
// double HighMassBinning[33] = {60.0, 68.8811, 79.0766, 90.7814, 104.219, 119.645, 137.354, 157.685, 181.025, 207.82,
//                             238.581, 273.895, 314.437, 360.979, 414.41, 475.75, 546.169, 627.012, 719.821, 826.367,
//                             948.683, 1089.1, 1250.31, 1435.38, 1647.84, 1891.75, 2171.76, 2493.22, 2862.26, 3285.93,
//                             3772.3, 4330.67, 4971.68};

// int HighMassBin2 = 1;
// double HighMassBinning2[2] = {3000.0, 5000.0};

 double rangeZPt3[9] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 13.0, 16.0, 20.0};
 double rangeATLASZY[7] = {0.0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4};

 ////////////////////////////////
 // ATLAS High Mass DY Binning //
 ////////////////////////////////

 int ATLAS_Mll_HighMass_bin = 13;  double ATLAS_Mll_HighMass_binning[14] = {116.0, 130.0, 150.0, 175.0, 200.0, 230.0, 260.0, 300.0, 380.0, 500.0, 700.0, 1000.0, 1500.0, 5000.0};
 int ATLAS_costheta_bin = 20;      double ATLAS_costheta_binning[21] = {-1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
 int ATLAS_DilRapidity_bin = 12;   double ATLAS_DilRapidity_binning[13];
 for(int ibin = 1; ibin <= 13; ibin++){
   ATLAS_DilRapidity_binning[ibin - 1] = 2.5 / 12.0 * (ibin - 1);
 } 

 int ATLAS_Mll_HighMass_2D_bin = 4;  double ATLAS_Mll_HighMass_2D_binning[5] = {116.0, 150.0, 200.0, 300.0, 5000.0};
 int ATLAS_costheta_2D_bin = 10;     double ATLAS_costheta_2D_binning[11] = {-1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0};
 int ATLAS_DilRapidity_2D_bin = 10;  double ATLAS_DilRapidity_2D_binning[11] = {0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5};

 int ATLAS_Mll_HighMass_2D_bin_1 = 4;  double ATLAS_Mll_HighMass_2D_binning_1[5] = {116.0, 150.0, 200.0, 300.0, 500.0};
 int ATLAS_Mll_HighMass_2D_bin_2 = 1;  double ATLAS_Mll_HighMass_2D_binning_2[2] = {500.0, 1500.0};
 int ATLAS_Mll_HighMass_2D_bin_3 = 1;  double ATLAS_Mll_HighMass_2D_binning_3[2] = {1500.0, 5000.0};

 int ATLAS_DilRapidity_2D_bin_1 = 12;  double ATLAS_DilRapidity_2D_binning_1[13] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4};
 int ATLAS_DilRapidity_2D_bin_2 = 8;   double ATLAS_DilRapidity_2D_binning_2[9] = {0.0, 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.4};
 int ATLAS_DilRapidity_2D_bin_3 = 1;   double ATLAS_DilRapidity_2D_binning_3[2] = {0.0, 2.4};

 int ATLAS_costheta_2D_bin_1 = 10;     double ATLAS_costheta_2D_binning_1[11] = {-1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0};
 int ATLAS_costheta_2D_bin_2 = 8;     double ATLAS_costheta_2D_binning_2[9] = {-1.0, -0.75, -0.5, -0.25, 0.0, 0.25, 0.5, 0.75, 1.0};
 int ATLAS_costheta_2D_bin_3 = 1;     double ATLAS_costheta_2D_binning_3[2] = {-1.0, 1.0};


 int ATLAS_costheta_3D_bin = 2;      double ATLAS_costheta_3D_binning[3] = {-1.0, 0.0, 1.0};

 int ATLAS_Mll_HighMass_fine_bin = 262; double ATLAS_Mll_HighMass_fine_binning[263];
 for(int ibin = 1; ibin <= 185; ibin++){
   ATLAS_Mll_HighMass_fine_binning[ibin - 1] = 116.0 + (double)(ibin - 1);
 }
 for(int ibin = 185; ibin <= 255; ibin++){
   ATLAS_Mll_HighMass_fine_binning[ibin - 1] = 300.0 + 10.0 * (ibin - 184 - 1);
 }
 for(int ibin = 255; ibin <= 263; ibin++){
   ATLAS_Mll_HighMass_fine_binning[ibin - 1] = 1000.0 + 500.0 * (ibin - 254 - 1);
 }

 int ATLAS_DilRapidity_fine_bin = 25; double ATLAS_DilRapidity_fine_binning[26];
 for(int ibin = 1; ibin <= 26; ibin++){
   ATLAS_DilRapidity_fine_binning[ibin - 1] = 0.1 * (ibin - 1);
 }

 int RHIC_WRatio_bin = 9; double RHIC_WRatio_binning[10] = {-1.0, -0.8, -0.5, -0.25, 0.0, 0.25, 0.5, 0.8, 1.0, 1.5};

 this->TotalThread = TotalThread;

   //////////////////////////
   //  Z Event Histograms  //
   //////////////////////////

   BookHist(ZMass_uu, "ZMass_uu", "ZMass_uu", HighMassBin, HighMassBinning);
   BookHist(ZMass_dd, "ZMass_dd", "ZMass_dd", HighMassBin, HighMassBinning);
   BookHist(ZMass_ss, "ZMass_ss", "ZMass_ss", HighMassBin, HighMassBinning);
   BookHist(ZMass_cc, "ZMass_cc", "ZMass_cc", HighMassBin, HighMassBinning);
   BookHist(ZMass_bb, "ZMass_bb", "ZMass_bb", HighMassBin, HighMassBinning);
   BookHist(ZMass_utype, "ZMass_utype", "ZMass_utype", HighMassBin, HighMassBinning);
   BookHist(ZMass_dtype, "ZMass_dtype", "ZMass_dtype", HighMassBin, HighMassBinning);

   Book3DHist(Xsec_3D_CC, "Xsec_3D_CC", "Xsec_3D_CC", MassBin, MassBinning, ZYCCBin, ZYCCBinning, CosThetaBin, CosThetaBinning);
   Book3DHist(Xsec_3D_CF, "Xsec_3D_CF", "Xsec_3D_CF", MassBin, MassBinning, ZYCFBin, ZYCFBinning, CosThetaBin, CosThetaBinning);
   Book3DHist(Xsec_3D_CC_LowMass, "Xsec_3D_CC_LowMass", "Xsec_3D_CC_LowMass", MassBin_LowMass, MassBinning_LowMass, ZYCCBin, ZYCCBinning, CosThetaBin, CosThetaBinning);
   Book3DHist(Xsec_3D_CF_LowMass, "Xsec_3D_CF_LowMass", "Xsec_3D_CF_LowMass", MassBin_LowMass, MassBinning_LowMass, ZYCFBin, ZYCFBinning, CosThetaBin, CosThetaBinning);
   Book3DHist(Xsec_3D_CC_HighMass, "Xsec_3D_CC_HighMass", "Xsec_3D_CC_HighMass", MassBin_HighMass, MassBinning_HighMass, ZYCCBin, ZYCCBinning, CosThetaBin, CosThetaBinning);
   Book3DHist(Xsec_3D_CF_HighMass, "Xsec_3D_CF_HighMass", "Xsec_3D_CF_HighMass", MassBin_HighMass, MassBinning_HighMass, ZYCFBin, ZYCFBinning, CosThetaBin, CosThetaBinning);
   Book3DHist(Xsec_3D_CC_uu, "Xsec_3D_CC_uu", "Xsec_3D_CC_uu", MassBin, MassBinning, ZYCCBin, ZYCCBinning, CosThetaBin, CosThetaBinning);
   Book3DHist(Xsec_3D_CF_uu, "Xsec_3D_CF_uu", "Xsec_3D_CF_uu", MassBin, MassBinning, ZYCFBin, ZYCFBinning, CosThetaBin, CosThetaBinning);
   Book3DHist(Xsec_3D_CC_dd, "Xsec_3D_CC_dd", "Xsec_3D_CC_dd", MassBin, MassBinning, ZYCCBin, ZYCCBinning, CosThetaBin, CosThetaBinning);
   Book3DHist(Xsec_3D_CF_dd, "Xsec_3D_CF_dd", "Xsec_3D_CF_dd", MassBin, MassBinning, ZYCFBin, ZYCFBinning, CosThetaBin, CosThetaBinning);

   Book2DHist(Xsec_2D_CC, "Xsec_2D_CC", "Xsec_2D_CC", MassBin, MassBinning, ZYCCBin, ZYCCBinning);
   Book2DHist(Xsec_2D_CF, "Xsec_2D_CF", "Xsec_2D_CF", MassBin, MassBinning, ZYCFBin, ZYCFBinning);

   BookHist(Xsec_1D_CC, "Xsec_1D_CC", "Xsec_1D_CC", MassBin, MassBinning);
   BookHist(Xsec_1D_CF, "Xsec_1D_CF", "Xsec_1D_CF", MassBin, MassBinning);

   vector<double> MassBin2 = {40.0, 66.0, 116.0, 250.0, 400.0, 600.0, 1000.0};
   vector<double> CosThetaBin2 = {-1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
   Book2DHist(ZMass_CosTheta_uu, "ZMass_CosTheta_uu", "ZMass_CosTheta_uu", MassBin2.size() - 1, &MassBin2[0], CosThetaBin2.size() - 1, &CosThetaBin2[0]);
   Book2DHist(ZMass_CosTheta_dd, "ZMass_CosTheta_dd", "ZMass_CosTheta_dd", MassBin2.size() - 1, &MassBin2[0], CosThetaBin2.size() - 1, &CosThetaBin2[0]);
   Book2DHist(ZMass_CosTheta, "ZMass_CosTheta", "ZMass_CosTheta", MassBin2.size() - 1, &MassBin2[0], CosThetaBin2.size() - 1, &CosThetaBin2[0]);

   //BookHist(ZRapidity_CC, "ZRapidity_CC", "ZRapidity_CC", 25, 0, 5);
   //BookHist(ZRapidity_CF, "ZRapidity_CF", "ZRapidity_CF", 25, 0, 5);
   BookHist(ZRapidity_CC, "ZRapidity_CC", "ZRapidity_CC", ZYCCBin, ZYCCBinning);
   BookHist(ZRapidity_CF, "ZRapidity_CF", "ZRapidity_CF", ZYCFBin, ZYCFBinning);
   BookHist(ZRapidity_CF_Low, "ZRapidity_CF_Low", "ZRapidity_CF_Low", ZYCCBin, ZYCCBinning);

   BookHist(ZPt, "ZPt", "ZPt", 100, 0, 100);

   //BookHist(FZMass_CC, "FZMass_CC", "FZMass_CC", 30, 60, 120);
   //BookHist(BZMass_CC, "BZMass_CC", "BZMass_CC", 30, 60, 120);
   //BookHist(FZMass_CF, "FZMass_CF", "FZMass_CF", 30, 60, 120);
   //BookHist(BZMass_CF, "BZMass_CF", "BZMass_CF", 30, 60, 120);
   BookHist(FZMass_CC, "FZMass_CC", "FZMass_CC", MassBin, MassBinning);
   BookHist(BZMass_CC, "BZMass_CC", "BZMass_CC", MassBin, MassBinning);
   BookHist(FZMass_CF, "FZMass_CF", "FZMass_CF", MassBin, MassBinning);
   BookHist(BZMass_CF, "BZMass_CF", "BZMass_CF", MassBin, MassBinning);

   Book2DHist(FZMass_ZY_CC, "FZMass_ZY_CC", "FZMass_ZY_CC", MassBin, MassBinning, ZYCCBin, ZYCCBinning);
   Book2DHist(BZMass_ZY_CC, "BZMass_ZY_CC", "BZMass_ZY_CC", MassBin, MassBinning, ZYCCBin, ZYCCBinning);
   Book2DHist(FZMass_ZY_CF, "FZMass_ZY_CF", "FZMass_ZY_CF", MassBin, MassBinning, ZYCFBin, ZYCFBinning);
   Book2DHist(BZMass_ZY_CF, "BZMass_ZY_CF", "BZMass_ZY_CF", MassBin, MassBinning, ZYCFBin, ZYCFBinning);

   BookHist(FZMass_LowRegion_CC, "FZMass_LowRegion_CC", "FZMass_LowRegion_CC", 1, 60, 80);
   BookHist(BZMass_LowRegion_CC, "BZMass_LowRegion_CC", "BZMass_LowRegion_CC", 1, 60, 80);
   BookHist(FZMass_LowRegion_CF, "FZMass_LowRegion_CF", "FZMass_LowRegion_CF", 1, 60, 80);
   BookHist(BZMass_LowRegion_CF, "BZMass_LowRegion_CF", "BZMass_LowRegion_CF", 1, 60, 80);
   BookHist(FZMass_HighRegion_CC, "FZMass_HighRegion_CC", "FZMass_HighRegion_CC", 1, 100, 120);
   BookHist(BZMass_HighRegion_CC, "BZMass_HighRegion_CC", "BZMass_HighRegion_CC", 1, 100, 120);
   BookHist(FZMass_HighRegion_CF, "FZMass_HighRegion_CF", "FZMass_HighRegion_CF", 1, 100, 120);
   BookHist(BZMass_HighRegion_CF, "BZMass_HighRegion_CF", "BZMass_HighRegion_CF", 1, 100, 120);

   BookHist(ZMass_HighMass, "ZMass_HighMass", "ZMass_HighMass", HighMassBin, HighMassBinning);
   BookHist(ZMass_HighMass_PerTeV, "ZMass_HighMass_PerTeV", "ZMass_HighMass_PerTeV", 6, 1000.0, 7000.0);

   BookHist(ZMass_FullMass, "ZMass_FullMass", "ZMass_FullMass", FullMassBinning.size() - 1, &FullMassBinning[0]);

   BookHist(FZMass_HighMass, "FZMass_HighMass", "FZMass_HighMass", HighMassBin, HighMassBinning);
   BookHist(BZMass_HighMass, "BZMass_HighMass", "BZMass_HighMass", HighMassBin, HighMassBinning);
   BookHist(FZMass_HighMass2, "FZMass_HighMass2", "FZMass_HighMass2", HighMassBin2, &HighMassBinning2[0]);
   BookHist(BZMass_HighMass2, "BZMass_HighMass2", "BZMass_HighMass2", HighMassBin2, &HighMassBinning2[0]);
   BookHist(FZMass_HighMass_uu, "FZMass_HighMass_uu", "FZMass_HighMass_uu", HighMassBin, HighMassBinning);
   BookHist(BZMass_HighMass_uu, "BZMass_HighMass_uu", "BZMass_HighMass_uu", HighMassBin, HighMassBinning);
   BookHist(FZMass_HighMass_dd, "FZMass_HighMass_dd", "FZMass_HighMass_dd", HighMassBin, HighMassBinning);
   BookHist(BZMass_HighMass_dd, "BZMass_HighMass_dd", "BZMass_HighMass_dd", HighMassBin, HighMassBinning);
   BookHist(FZMass_HighMass_upto10000, "FZMass_HighMass_upto10000", "FZMass_HighMass_upto10000", HighMassBinning_upto10000.size() - 1, &HighMassBinning_upto10000[0]);
   BookHist(BZMass_HighMass_upto10000, "BZMass_HighMass_upto10000", "BZMass_HighMass_upto10000", HighMassBinning_upto10000.size() - 1, &HighMassBinning_upto10000[0]);

   BookHist(FZMass_LowMass1, "FZMass_LowMass1", "FZMass_LowMass1", LowMassBin1, &LowMassBinning1[0]);
   BookHist(BZMass_LowMass1, "BZMass_LowMass1", "BZMass_LowMass1", LowMassBin1, &LowMassBinning1[0]);
   BookHist(FZMass_LowMass2, "FZMass_LowMass2", "FZMass_LowMass2", LowMassBin2, &LowMassBinning2[0]);
   BookHist(BZMass_LowMass2, "BZMass_LowMass2", "BZMass_LowMass2", LowMassBin2, &LowMassBinning2[0]);

   Book2DHist(FZMass_LowMass1_ZY, "FZMass_LowMass1_ZY", "FZMass_LowMass1_ZY", LowMassBin1, &LowMassBinning1[0], ZYBin, ZYBinning);
   Book2DHist(BZMass_LowMass1_ZY, "BZMass_LowMass1_ZY", "BZMass_LowMass1_ZY", LowMassBin1, &LowMassBinning1[0], ZYBin, ZYBinning);
   Book2DHist(FZMass_LowMass2_ZY, "FZMass_LowMass2_ZY", "FZMass_LowMass2_ZY", LowMassBin2, &LowMassBinning2[0], ZYBin, ZYBinning);
   Book2DHist(BZMass_LowMass2_ZY, "BZMass_LowMass2_ZY", "BZMass_LowMass2_ZY", LowMassBin2, &LowMassBinning2[0], ZYBin, ZYBinning);

   BookHist(FZMass_ATLAS_CC, "FZMass_ATLAS_CC", "FZMass_ATLAS_CC", 62, 45, 200);
   BookHist(BZMass_ATLAS_CC, "BZMass_ATLAS_CC", "BZMass_ATLAS_CC", 62, 45, 200);
   BookHist(FZMass_ATLAS_CF, "FZMass_ATLAS_CF", "FZMass_ATLAS_CF", 62, 45, 200);
   BookHist(BZMass_ATLAS_CF, "BZMass_ATLAS_CF", "BZMass_ATLAS_CF", 62, 45, 200);

   BookHist(ZHighMass_CC, "ZHighMass_CC", "ZHighMass_CC", HighMassBin, HighMassBinning);
   BookHist(ZHighMass_CF, "ZHighMass_CF", "ZHighMass_CF", HighMassBin, HighMassBinning);
   BookHist(ZHighMass_CC_PerTeV, "ZHighMass_CC_PerTeV", "ZHighMass_CC_PerTeV", 6, 1000.0, 7000.0);
   BookHist(ZHighMass_CF_PerTeV, "ZHighMass_CF_PerTeV", "ZHighMass_CF_PerTeV", 6, 1000.0, 7000.0);

   BookHist(CrossSection, "CrossSection", "CrossSection", CrossSectionBin, CrossSectionBinning);
   BookHist(CrossSectionF, "CrossSectionF", "CrossSectionF", CrossSectionBin, CrossSectionBinning);
   BookHist(CrossSectionB, "CrossSectionB", "CrossSectionB", CrossSectionBin, CrossSectionBinning);

   Book2DHist(CrossSectionPtY, "CrossSectionPtY", "CrossSectionPtY", 20, 0, 40, 5, 0, 5);

   BookHist(FZMass_Full, "FZMass_Full", "FZMass_Full", 120, 60, 120);
   BookHist(BZMass_Full, "BZMass_Full", "BZMass_Full", 120, 60, 120);
   BookHist(FZMass_Full_uu, "FZMass_Full_uu", "FZMass_Full_uu", 120, 60, 120);
   BookHist(BZMass_Full_uu, "BZMass_Full_uu", "BZMass_Full_uu", 120, 60, 120);
   BookHist(FZMass_Full_dd, "FZMass_Full_dd", "FZMass_Full_dd", 120, 60, 120);
   BookHist(BZMass_Full_dd, "BZMass_Full_dd", "BZMass_Full_dd", 120, 60, 120);

   BookHist(ZHighMass_total, "ZHighMass_total", "ZHighMass_total", HighMassBin, HighMassBinning);
   BookHist(ZHighMass_wrong, "ZHighMass_wrong", "ZHighMass_wrong", HighMassBin, HighMassBinning);
   BookHist(ZHighMass2_total, "ZHighMass2_total", "ZHighMass2_total", HighMassBin2, &HighMassBinning2[0]);
   BookHist(ZHighMass2_wrong, "ZHighMass2_wrong", "ZHighMass2_wrong", HighMassBin2, &HighMassBinning2[0]);
   BookHist(ZHighMass_uu_total, "ZHighMass_uu_total", "ZHighMass_uu_total", HighMassBin, HighMassBinning);
   BookHist(ZHighMass_uu_wrong, "ZHighMass_uu_wrong", "ZHighMass_uu_wrong", HighMassBin, HighMassBinning);
   BookHist(ZHighMass_dd_total, "ZHighMass_dd_total", "ZHighMass_dd_total", HighMassBin, HighMassBinning);
   BookHist(ZHighMass_dd_wrong, "ZHighMass_dd_wrong", "ZHighMass_dd_wrong", HighMassBin, HighMassBinning);
   BookHist(ZHighMass2_uu_total, "ZHighMass2_uu_total", "ZHighMass2_uu_total", HighMassBin2, &HighMassBinning2[0]);
   BookHist(ZHighMass2_uu_wrong, "ZHighMass2_uu_wrong", "ZHighMass2_uu_wrong", HighMassBin2, &HighMassBinning2[0]);
   BookHist(ZHighMass2_dd_total, "ZHighMass2_dd_total", "ZHighMass2_dd_total", HighMassBin2, &HighMassBinning2[0]);
   BookHist(ZHighMass2_dd_wrong, "ZHighMass2_dd_wrong", "ZHighMass2_dd_wrong", HighMassBin2, &HighMassBinning2[0]);

   Book2DHist(ZMass_ZMT, "ZMass_ZMT", "ZMass_ZMT", 20, 60, 260, 20, 60, 260);

   BookHist(ForwardPosiLeptonEta, "ForwardPosiLeptonEta", "ForwardPosiLeptonEta", 20, 0.0, 5.0);
   BookHist(BackwardPosiLeptonEta, "BackwardPosiLeptonEta", "BackwardPosiLeptonEta", 20, 0.0, 5.0);
   BookHist(ForwardNegaLeptonEta, "ForwardNegaLeptonEta", "ForwardNegaLeptonEta", 20, 0.0, 5.0);
   BookHist(BackwardNegaLeptonEta, "BackwardNegaLeptonEta", "BackwardNegaLeptonEta", 20, 0.0, 5.0);

   //////////////////////
   //  ATLAS 8TeV ZPT  //
   //////////////////////

   BookHist(ATLASZPt_Fiduc, "ATLASZPt_Fiduc", "ATLASZPt_Fiduc", 8, rangeZPt3);
   BookHist(ATLASZPt_Total, "ATLASZPt_Total", "ATLASZPt_Total", 8, rangeZPt3);
   Book2DHist(ATLASZPt_2D_Fiduc, "ATLASZPt_2D_Fiduc", "ATLASZPt_2D_Fiduc", 8, rangeZPt3, 6, rangeATLASZY);
   Book2DHist(ATLASZPt_2D_Total, "ATLASZPt_2D_Total", "ATLASZPt_2D_Total", 8, rangeZPt3, 6, rangeATLASZY);
   Book2DHist(ATLASZPt_2D_Total_uu, "ATLASZPt_2D_Total_uu", "ATLASZPt_2D_Total_uu", 8, rangeZPt3, 6, rangeATLASZY);
   Book2DHist(ATLASZPt_2D_Total_dd, "ATLASZPt_2D_Total_dd", "ATLASZPt_2D_Total_dd", 8, rangeZPt3, 6, rangeATLASZY);
   Book2DHist(ATLASZPt_2D_Total_MassWindow, "ATLASZPt_2D_Total_MassWindow", "ATLASZPt_2D_Total_MassWindow", 8, rangeZPt3, 6, rangeATLASZY);

   //////////////////////
   // ATLAS 13TeV HMDY //
   //////////////////////

   BookHist(ATLAS_Mll_HighMass, "ATLAS_Mll_HighMass", "ATLAS_Mll_HighMass", ATLAS_Mll_HighMass_bin, ATLAS_Mll_HighMass_binning);
   BookHist(ATLAS_costheta, "ATLAS_costheta", "ATLAS_costheta", ATLAS_costheta_bin, ATLAS_costheta_binning);
   BookHist(ATLAS_DilRapidity, "ATLAS_DilRapidity", "ATLAS_DilRapidity", ATLAS_DilRapidity_bin, ATLAS_DilRapidity_binning);
   Book2DHist(ATLAS_Mll_HighMass_costheta, "ATLAS_Mll_HighMass_costheta", "ATLAS_Mll_HighMass_costheta", ATLAS_Mll_HighMass_2D_bin, ATLAS_Mll_HighMass_2D_binning, ATLAS_costheta_2D_bin, ATLAS_costheta_2D_binning);
   Book2DHist(ATLAS_Mll_HighMass_DilRapidity, "ATLAS_Mll_HighMass_DilRapidity", "ATLAS_Mll_HighMass_DilRapidity", ATLAS_Mll_HighMass_2D_bin, ATLAS_Mll_HighMass_2D_binning, ATLAS_DilRapidity_2D_bin, ATLAS_DilRapidity_2D_binning);

   Book2DHist(ATLAS_Mll_HighMass_costheta_1, "ATLAS_Mll_HighMass_costheta_h1", "ATLAS_Mll_HighMass_costheta_h1", ATLAS_Mll_HighMass_2D_bin_1, ATLAS_Mll_HighMass_2D_binning_1, ATLAS_costheta_2D_bin_1, ATLAS_costheta_2D_binning_1);
   Book2DHist(ATLAS_Mll_HighMass_DilRapidity_1, "ATLAS_Mll_HighMass_DilRapidity_h1", "ATLAS_Mll_HighMass_DilRapidity_h1", ATLAS_Mll_HighMass_2D_bin_1, ATLAS_Mll_HighMass_2D_binning_1, ATLAS_DilRapidity_2D_bin_1, ATLAS_DilRapidity_2D_binning_1);
   Book2DHist(ATLAS_Mll_HighMass_costheta_2, "ATLAS_Mll_HighMass_costheta_h2", "ATLAS_Mll_HighMass_costheta_h2", ATLAS_Mll_HighMass_2D_bin_2, ATLAS_Mll_HighMass_2D_binning_2, ATLAS_costheta_2D_bin_2, ATLAS_costheta_2D_binning_2);
   Book2DHist(ATLAS_Mll_HighMass_DilRapidity_2, "ATLAS_Mll_HighMass_DilRapidity_h2", "ATLAS_Mll_HighMass_DilRapidity_h2", ATLAS_Mll_HighMass_2D_bin_2, ATLAS_Mll_HighMass_2D_binning_2, ATLAS_DilRapidity_2D_bin_2, ATLAS_DilRapidity_2D_binning_2);
   Book2DHist(ATLAS_Mll_HighMass_costheta_3, "ATLAS_Mll_HighMass_costheta_h3", "ATLAS_Mll_HighMass_costheta_h3", ATLAS_Mll_HighMass_2D_bin_3, ATLAS_Mll_HighMass_2D_binning_3, ATLAS_costheta_2D_bin_3, ATLAS_costheta_2D_binning_3);
   Book2DHist(ATLAS_Mll_HighMass_DilRapidity_3, "ATLAS_Mll_HighMass_DilRapidity_h3", "ATLAS_Mll_HighMass_DilRapidity_h3", ATLAS_Mll_HighMass_2D_bin_3, ATLAS_Mll_HighMass_2D_binning_3, ATLAS_DilRapidity_2D_bin_3, ATLAS_DilRapidity_2D_binning_3);

   Book3DHist(ATLAS_HMDY_Xsec_3D, "ATLAS_HMDY_Xsec_3D", "ATLAS_HMDY_Xsec_3D", ATLAS_Mll_HighMass_2D_bin, ATLAS_Mll_HighMass_2D_binning, ATLAS_DilRapidity_2D_bin, ATLAS_DilRapidity_2D_binning, ATLAS_costheta_3D_bin, ATLAS_costheta_3D_binning);

   BookHist(ATLAS_Mll_HighMass_FineBin, "ATLAS_Mll_HighMass_FineBin", "ATLAS_Mll_HighMass_FineBin", ATLAS_Mll_HighMass_fine_bin, ATLAS_Mll_HighMass_fine_binning);
   BookHist(ATLAS_costheta_FineBin, "ATLAS_costheta_FineBin", "ATLAS_costheta_FineBin", ATLAS_costheta_bin, ATLAS_costheta_binning);
   BookHist(ATLAS_DilRapidity_FineBin, "ATLAS_DilRapidity_FineBin", "ATLAS_DilRapidity_FineBin", ATLAS_DilRapidity_fine_bin, ATLAS_DilRapidity_fine_binning);
   Book2DHist(ATLAS_Mll_HighMass_costheta_FineBin, "ATLAS_Mll_HighMass_costheta_FineBin", "ATLAS_Mll_HighMass_costheta_FineBin", ATLAS_Mll_HighMass_fine_bin, ATLAS_Mll_HighMass_fine_binning, ATLAS_costheta_bin, ATLAS_costheta_binning);
   Book2DHist(ATLAS_Mll_HighMass_DilRapidity_FineBin, "ATLAS_Mll_HighMass_DilRapidity_FineBin", "ATLAS_Mll_HighMass_DilRapidity_FineBin", ATLAS_Mll_HighMass_fine_bin, ATLAS_Mll_HighMass_fine_binning, ATLAS_DilRapidity_fine_bin, ATLAS_DilRapidity_fine_binning);
   Book3DHist(ATLAS_HMDY_Xsec_3D_FineBin, "ATLAS_HMDY_Xsec_3D_FineBin", "ATLAS_HMDY_Xsec_3D_FineBin", ATLAS_Mll_HighMass_fine_bin, ATLAS_Mll_HighMass_fine_binning, ATLAS_DilRapidity_fine_bin, ATLAS_DilRapidity_fine_binning, ATLAS_costheta_3D_bin, ATLAS_costheta_3D_binning);

   //////////////////////////
   //  W Event Histograms  //
   //////////////////////////

   BookHist(PositiveLeptonEta, "PositiveLeptonEta", "PositiveLeptonEta", 20, 0, 2.4);
   BookHist(NegativeLeptonEta, "NegativeLeptonEta", "NegativeLeptonEta", 20, 0, 2.4);
   BookHist(PositiveLeptonEta_NoPtCut, "PositiveLeptonEta_NoPtCut", "PositiveLeptonEta_NoPtCut", 20, 0, 2.4);
   BookHist(NegativeLeptonEta_NoPtCut, "NegativeLeptonEta_NoPtCut", "NegativeLeptonEta_NoPtCut", 20, 0, 2.4);

   BookHist(PositiveLeptonHighEta, "PositiveLeptonHighEta", "PositiveLeptonHighEta", 1, 1.2, 2.4);
   BookHist(NegativeLeptonHighEta, "NegativeLeptonHighEta", "NegativeLeptonHighEta", 1, 1.2, 2.4);
   BookHist(PositiveLeptonLowEta, "PositiveLeptonLowEta", "PositiveLeptonLowEta", 1, 0, 1.2);
   BookHist(NegativeLeptonLowEta, "NegativeLeptonLowEta", "NegativeLeptonLowEta", 1, 0, 1.2);

   BookHist(PositiveLeptonEtaFull, "PositiveLeptonEtaFull", "PositiveLeptonEtaFull", 40, 0, 4.8);
   BookHist(NegativeLeptonEtaFull, "NegativeLeptonEtaFull", "NegativeLeptonEtaFull", 40, 0, 4.8);
   BookHist(PositiveNeutrinoEtaFull, "PositiveNeutrinoEtaFull", "PositiveNeutrinoEtaFull", 40, 0, 4.8);
   BookHist(NegativeNeutrinoEtaFull, "NegativeNeutrinoEtaFull", "NegativeNeutrinoEtaFull", 40, 0, 4.8);

   Book2DHist(PositiveLeptonPtEta, "PositiveLeptonPtEta", "PositiveLeptonPtEta", 10, 30, 50, 10, 0, 2.4);
   Book2DHist(NegativeLeptonPtEta, "NegativeLeptonPtEta", "NegativeLeptonPtEta", 10, 30, 50, 10, 0, 2.4);
   Book2DHist(WPlusMTEta, "WPlusMTEta", "WPlusMTEta", 20, 60, 100, 10, 0, 2.4);
   Book2DHist(WMinusMTEta, "WMinusMTEta", "WMinusMTEta", 20, 60, 100, 10, 0, 2.4);
   Book2DHist(WPlusMTEta_NoPtCut, "WPlusMTEta_NoPtCut", "WPlusMTEta_NoPtCut", 20, 60, 100, 10, 0, 2.4);
   Book2DHist(WMinusMTEta_NoPtCut, "WMinusMTEta_NoPtCut", "WMinusMTEta_NoPtCut", 20, 60, 100, 10, 0, 2.4);
   Book2DHist(WPlusMTEta_Above100, "WPlusMTEta_Above100", "WPlusMTEta_Above100", 5, 100, 500, 10, 0, 2.4);
   Book2DHist(WMinusMTEta_Above100, "WMinusMTEta_Above100", "WMinusMTEta_Above100", 5, 100, 500, 10, 0, 2.4);

   Book2DHist(WPlusMTEta_FullEta, "WPlusMTEta_FullEta", "WPlusMTEta_FullEta", 20, 60, 100, 20, 0, 5.0);
   Book2DHist(WMinusMTEta_FullEta, "WMinusMTEta_FullEta", "WMinusMTEta_FullEta", 20, 60, 100, 20, 0, 5.0);
   Book2DHist(WPlusMTEta_FullEta_Above100, "WPlusMTEta_FullEta_Above100", "WPlusMTEta_FullEta_Above100", 5, 100, 500, 20, 0, 5.0);
   Book2DHist(WMinusMTEta_FullEta_Above100, "WMinusMTEta_FullEta_Above100", "WMinusMTEta_FullEta_Above100", 5, 100, 500, 20, 0, 5.0);

   Book2DHist(WMTx, "WMTx", "WMTx", FullMTBin, FullMTBinning, xBin, &xBinning[0]);
   Book3DHist(WPlusMTCosThetaEta, "WPlusMTCosThetaEta", "WPlusMTCosThetaEta", FullMTBin, FullMTBinning, CosThetaBin, CosThetaBinning, WLeptonEtaBin, WLeptonEtaBinning);
   Book3DHist(WMinusMTCosThetaEta, "WMinusMTCosThetaEta", "WMinusMTCosThetaEta", FullMTBin, FullMTBinning, CosThetaBin, CosThetaBinning, WLeptonEtaBin, WLeptonEtaBinning);

   BookHist(PositiveLeptonPt, "PositiveLeptonPt", "PositiveLeptonPt", 40, 30, 50);
   BookHist(NegativeLeptonPt, "NegativeLeptonPt", "NegativeLeptonPt", 40, 30, 50);
   BookHist(WLeptonPt, "WLeptonPt", "WLeptonPt", 40, 30, 50);

   BookHist(WPlusNeutrinoPt, "WPlusNeutrinoPt", "WPlusNeutrinoPt", 40, 30, 50);
   BookHist(WMinusNeutrinoPt, "WMinusNeutrinoPt", "WMinusNeutrinoPt", 40, 30, 50);
   BookHist(NeutrinoPt, "NeutrinoPt", "NeutrinoPt", 40, 30, 50);

   BookHist(WPlusMT, "WPlusMT", "WPlusMT", 40, 60, 100);
   BookHist(WMinusMT, "WMinusMT", "WMinusMT", 40, 60, 100);
   BookHist(WPlusMT_NoPtCut, "WPlusMT_NoPtCut", "WPlusMT_NoPtCut", 40, 60, 100);
   BookHist(WMinusMT_NoPtCut, "WMinusMT_NoPtCut", "WMinusMT_NoPtCut", 40, 60, 100);
   BookHist(WPlusMT_Above100, "WPlusMT_Above100", "WPlusMT_Above100", 5, 100, 500);
   BookHist(WMinusMT_Above100, "WMinusMT_Above100", "WMinusMT_Above100", 5, 100, 500);
   BookHist(WBosonMT, "WBosonMT", "WBosonMT", 40, 60, 100);

   BookHist(WPlusXsec, "WPlusXsec", "WPlusXsec", 1, 0.0, 2.4);
   BookHist(WMinusXsec, "WMinusXsec", "WMinusXsec", 1, 0.0, 2.4);

   BookHist(WHighMassMT, "WHighMassMT", "WHighMassMT", HighMassBin, HighMassBinning);
   BookHist(WPlusHighMassMT, "WPlusHighMassMT", "WPlusHighMassMT", HighMassBin, HighMassBinning);
   BookHist(WMinusHighMassMT, "WMinusHighMassMT", "WMinusHighMassMT", HighMassBin, HighMassBinning);
   BookHist(WHighMassMT_NoPtCut, "WHighMassMT_NoPtCut", "WHighMassMT_NoPtCut", HighMassBin, HighMassBinning);
   BookHist(WPlusHighMassMT_NoPtCut, "WPlusHighMassMT_NoPtCut", "WPlusHighMassMT_NoPtCut", HighMassBin, HighMassBinning);
   BookHist(WMinusHighMassMT_NoPtCut, "WMinusHighMassMT_NoPtCut", "WMinusHighMassMT_NoPtCut", HighMassBin, HighMassBinning);
   BookHist(WHighMassMT_PerTeV, "WHighMassMT_PerTeV", "WHighMassMT_PerTeV", 6, 1000.0, 7000.0);
   BookHist(WPlusHighMassMT_PerTeV, "WPlusHighMassMT_PerTeV", "WPlusHighMassMT_PerTeV", 6, 1000.0, 7000.0);
   BookHist(WMinusHighMassMT_PerTeV, "WMinusHighMassMT_PerTeV", "WMinusHighMassMT_PerTeV", 6, 1000.0, 7000.0);

   BookHist(WPlusForwardEta, "WPlusForwardEta", "WPlusForwardEta", 20, 0.0, 5.0);
   BookHist(WPlusBackwardEta, "WPlusBackwardEta", "WPlusBackwardEta", 20, 0.0, 5.0);
   BookHist(WMinusForwardEta, "WMinusForwardEta", "WMinusForwardEta", 20, 0.0, 5.0);
   BookHist(WMinusBackwardEta, "WMinusBackwardEta", "WMinusBackwardEta", 20, 0.0, 5.0);

   BookHist(WPlusAverageRapidity, "WPlusAverageRapidity", "WPlusAverageRapidity", 20, 0.0, 5.0);
   BookHist(WMinusAverageRapidity, "WMinusAverageRapidity", "WMinusAverageRapidity", 20, 0.0, 5.0);

   BookHist(WPlusCosTheta, "WPlusCosTheta", "WPlusCosTheta", 40, -1, 1);
   BookHist(WMinusCosTheta, "WMinusCosTheta", "WMinusCosTheta", 40, -1, 1);

   BookHist(WPlusCosTheta_ExpPz, "WPlusCosTheta_ExpPz", "WPlusCosTheta_ExpPz", 40, -1, 1);
   BookHist(WMinusCosTheta_ExpPz, "WMinusCosTheta_ExpPz", "WMinusCosTheta_ExpPz", 40, -1, 1);

   BookHist(WPlusCosTheta_ExpEta, "WPlusCosTheta_ExpEta", "WPlusCosTheta_ExpEta", 40, -1, 1);
   BookHist(WMinusCosTheta_ExpEta, "WMinusCosTheta_ExpEta", "WMinusCosTheta_ExpEta", 40, -1, 1);

   BookHist(WPlusForwardEta_ExpPz, "WPlusForwardEta_ExpPz", "WPlusForwardEta_ExpPz", 20, 0.0, 5.0);
   BookHist(WPlusBackwardEta_ExpPz, "WPlusBackwardEta_ExpPz", "WPlusBackwardEta_ExpPz", 20, 0.0, 5.0);
   BookHist(WMinusForwardEta_ExpPz, "WMinusForwardEta_ExpPz", "WMinusForwardEta_ExpPz", 20, 0.0, 5.0);
   BookHist(WMinusBackwardEta_ExpPz, "WMinusBackwardEta_ExpPz", "WMinusBackwardEta_ExpPz", 20, 0.0, 5.0);

   BookHist(WPlusForwardEta_ExpEta, "WPlusForwardEta_ExpEta", "WPlusForwardEta_ExpEta", 20, 0.0, 5.0);
   BookHist(WPlusBackwardEta_ExpEta, "WPlusBackwardEta_ExpEta", "WPlusBackwardEta_ExpEta", 20, 0.0, 5.0);
   BookHist(WMinusForwardEta_ExpEta, "WMinusForwardEta_ExpEta", "WMinusForwardEta_ExpEta", 20, 0.0, 5.0);
   BookHist(WMinusBackwardEta_ExpEta, "WMinusBackwardEta_ExpEta", "WMinusBackwardEta_ExpEta", 20, 0.0, 5.0);

   BookHist(WPlusForwardDeta, "WPlusForwardDeta", "WPlusForwardDeta", 40, -5.0, 5.0);
   BookHist(WPlusBackwardDeta, "WPlusBackwardDeta", "WPlusBackwardDeta", 40, -5.0, 5.0);
   BookHist(WMinusForwardDeta, "WMinusForwardDeta", "WMinusForwardDeta", 40, -5.0, 5.0);
   BookHist(WMinusBackwardDeta, "WMinusBackwardDeta", "WMinusBackwardDeta", 40, -5.0, 5.0);

   Book2DHist(WPlusLepNuEta, "WPlusLepNuEta", "WPlusLepNuEta", 40, -10, 10, 40, -10, 10);
   Book2DHist(WMinusLepNuEta, "WMinusLepNuEta", "WMinusLepNuEta", 40, -10, 10, 40, -10, 10);

   BookHist(WPlusPzMethodFraction, "WPlusPzMethodFraction", "WPlusPzMethodFraction", 2, 0, 2);
   BookHist(WMinusPzMethodFraction, "WMinusPzMethodFraction", "WMinusPzMethodFraction", 2, 0, 2);
   BookHist(WPlusEtaMethodFraction, "WPlusEtaMethodFraction", "WPlusEtaMethodFraction", 2, 0, 2);
   BookHist(WMinusEtaMethodFraction, "WMinusEtaMethodFraction", "WMinusEtaMethodFraction", 2, 0, 2);

   BookHist(WPt, "WPt", "WPt", 500, 0, 500);

   BookHist(RHIC_WPlus, "RHIC_WPlus", "RHIC_WPlus", RHIC_WRatio_bin, RHIC_WRatio_binning);
   BookHist(RHIC_WMinus, "RHIC_WMinus", "RHIC_WMinus", RHIC_WRatio_bin, RHIC_WRatio_binning);

   vector<double> TotalXsecBinning = {80.0, 90.0, 100.0, 125.0, 150.0, 175.0, 200.0, 300.0, 400.0, 500.0, 1000.0};
   BookHist(TotalXsec_WPlus, "TotalXsec_WPlus", "TotalXsec_WPlus", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
   BookHist(TotalXsec_WMinus, "TotalXsec_WMinus", "TotalXsec_WMinus", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
   BookHist(TotalXsec_Z, "TotalXsec_Z", "TotalXsec_Z", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
   BookAngularHist(A0_ZPt_WPlus, "A0_ZPt_WPlus", "A0", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
   BookAngularHist(A1_ZPt_WPlus, "A1_ZPt_WPlus", "A1", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
   BookAngularHist(A2_ZPt_WPlus, "A2_ZPt_WPlus", "A2", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
   BookAngularHist(A3_ZPt_WPlus, "A3_ZPt_WPlus", "A3", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
   BookAngularHist(A4_ZPt_WPlus, "A4_ZPt_WPlus", "A4", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
   BookAngularHist(A0_ZPt_WMinus, "A0_ZPt_WMinus", "A0", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
   BookAngularHist(A1_ZPt_WMinus, "A1_ZPt_WMinus", "A1", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
   BookAngularHist(A2_ZPt_WMinus, "A2_ZPt_WMinus", "A2", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
   BookAngularHist(A3_ZPt_WMinus, "A3_ZPt_WMinus", "A3", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
   BookAngularHist(A4_ZPt_WMinus, "A4_ZPt_WMinus", "A4", TotalXsecBinning.size() - 1, &TotalXsecBinning[0]);
}

void HistsResBosHighMassZ::outputInformation()
{
 hf->cd();

//////////////////////////////////////////////////////////////////////////////////////////

 FZMass_CC_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass_CC->at(0));
 BZMass_CC_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass_CC->at(0));
 FZMass_CF_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass_CF->at(0));
 BZMass_CF_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass_CF->at(0));

 AFB_CC = (TH1D *)FZMass_CC_Pseudodata->Clone("AFB_CC");
 AFB_CC->Reset();
 AFBFunction(FZMass_CC_Pseudodata, BZMass_CC_Pseudodata, AFB_CC);
 AFB_CC->Write();

 AFB_CF = (TH1D *)FZMass_CF_Pseudodata->Clone("AFB_CF");
 AFB_CF->Reset();
 AFBFunction(FZMass_CF_Pseudodata, BZMass_CF_Pseudodata, AFB_CF);
 AFB_CF->Write();

///////////////////////////////////////////////////////////////////////////////////////////


 FZMass_ZY_CC_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass_ZY_CC->at(0));
 BZMass_ZY_CC_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass_ZY_CC->at(0));
 FZMass_ZY_CF_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass_ZY_CF->at(0));
 BZMass_ZY_CF_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass_ZY_CF->at(0));

 AFB_Mass_ZY_CC = (TH2D *)FZMass_ZY_CC_Pseudodata->Clone("AFB_Mass_ZY_CC");
 AFB_Mass_ZY_CC->Reset();
 AFBFunction(FZMass_ZY_CC_Pseudodata, BZMass_ZY_CC_Pseudodata, AFB_Mass_ZY_CC);
 AFB_Mass_ZY_CC->Write();

 AFB_Mass_ZY_CF = (TH2D *)FZMass_ZY_CF_Pseudodata->Clone("AFB_Mass_ZY_CF");
 AFB_Mass_ZY_CF->Reset();
 AFBFunction(FZMass_ZY_CF_Pseudodata, BZMass_ZY_CF_Pseudodata, AFB_Mass_ZY_CF);
 AFB_Mass_ZY_CF->Write();

 FZMass_ZY_CC_Pseudodata_300 = GenPseudodataNoFluc(300000.0, FZMass_ZY_CC->at(0), "Pseudodata300", 0, false);
 BZMass_ZY_CC_Pseudodata_300 = GenPseudodataNoFluc(300000.0, BZMass_ZY_CC->at(0), "Pseudodata300", 0, false);
 FZMass_ZY_CF_Pseudodata_300 = GenPseudodataNoFluc(300000.0, FZMass_ZY_CF->at(0), "Pseudodata300", 0, false);
 BZMass_ZY_CF_Pseudodata_300 = GenPseudodataNoFluc(300000.0, BZMass_ZY_CF->at(0), "Pseudodata300", 0, false);

 AFB_Mass_ZY_CC_300 = (TH2D *)FZMass_ZY_CC_Pseudodata_300->Clone("AFB_Mass_ZY_CC_300");
 AFB_Mass_ZY_CC_300->Reset();
 AFBFunction(FZMass_ZY_CC_Pseudodata_300, BZMass_ZY_CC_Pseudodata_300, AFB_Mass_ZY_CC_300);
 AFB_Mass_ZY_CC_300->Write();

 AFB_Mass_ZY_CF_300 = (TH2D *)FZMass_ZY_CF_Pseudodata_300->Clone("AFB_Mass_ZY_CF_300");
 AFB_Mass_ZY_CF_300->Reset();
 AFBFunction(FZMass_ZY_CF_Pseudodata_300, BZMass_ZY_CF_Pseudodata_300, AFB_Mass_ZY_CF_300);
 AFB_Mass_ZY_CF_300->Write();

////////////////////////////////////////////////////////////////////////////////////////////

 AFB_LowRegion_CC = (TH1D *)FZMass_LowRegion_CC->at(0)->Clone("AFB_LowRegion_CC");
 AFB_LowRegion_CC->Reset();
 AFB_LowRegion_CF = (TH1D *)FZMass_LowRegion_CF->at(0)->Clone("AFB_LowRegion_CF");
 AFB_LowRegion_CF->Reset();
 AFB_HighRegion_CC = (TH1D *)FZMass_HighRegion_CC->at(0)->Clone("AFB_HighRegion_CC");
 AFB_HighRegion_CC->Reset();
 AFB_HighRegion_CF = (TH1D *)FZMass_HighRegion_CF->at(0)->Clone("AFB_HighRegion_CF");
 AFB_HighRegion_CF->Reset();

 AFBFunction(FZMass_LowRegion_CC->at(0), BZMass_LowRegion_CC->at(0), AFB_LowRegion_CC);
 AFBFunction(FZMass_LowRegion_CF->at(0), BZMass_LowRegion_CF->at(0), AFB_LowRegion_CF);
 AFBFunction(FZMass_HighRegion_CC->at(0), BZMass_HighRegion_CC->at(0), AFB_HighRegion_CC);
 AFBFunction(FZMass_HighRegion_CF->at(0), BZMass_HighRegion_CF->at(0), AFB_HighRegion_CF);

 AFB_LowRegion_CC->Write();
 AFB_LowRegion_CF->Write();
 AFB_HighRegion_CC->Write();
 AFB_HighRegion_CF->Write();

 AFB_Delta_CC = new TH1D("AFB_Delta_CC", "AFB_Delta_CC", 1, 0, 1);
 AFB_Delta_CF = new TH1D("AFB_Delta_CF", "AFB_Delta_CF", 1, 0, 1);

 AFB_Delta_CC->SetBinContent(1, AFB_HighRegion_CC->GetBinContent(1) - AFB_LowRegion_CC->GetBinContent(1));
 AFB_Delta_CC->SetBinError(1, sqrt(AFB_HighRegion_CC->GetBinError(1) * AFB_HighRegion_CC->GetBinError(1) + AFB_LowRegion_CC->GetBinError(1) * AFB_LowRegion_CC->GetBinError(1)));
 AFB_Delta_CF->SetBinContent(1, AFB_HighRegion_CF->GetBinContent(1) - AFB_LowRegion_CF->GetBinContent(1));
 AFB_Delta_CF->SetBinError(1, sqrt(AFB_HighRegion_CF->GetBinError(1) * AFB_HighRegion_CF->GetBinError(1) + AFB_LowRegion_CF->GetBinError(1) * AFB_LowRegion_CF->GetBinError(1)));

 AFB_Delta_CC->Write();
 AFB_Delta_CF->Write();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

 FZMass_HighMass_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass_HighMass->at(0));
 BZMass_HighMass_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass_HighMass->at(0));
 FZMass_HighMass2_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass_HighMass2->at(0));
 BZMass_HighMass2_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass_HighMass2->at(0));

 AFB_HighMass = (TH1D *)FZMass_HighMass_Pseudodata->Clone("AFB_HighMass");
 AFB_HighMass->Reset();
 AFB_HighMass2 = (TH1D *)FZMass_HighMass2_Pseudodata->Clone("AFB_HighMass2");
 AFB_HighMass2->Reset();
 AFB_HighMass_uu = (TH1D *)FZMass_HighMass_uu->at(0)->Clone("AFB_HighMass_uu");
 AFB_HighMass_uu->Reset();
 AFB_HighMass_dd = (TH1D *)FZMass_HighMass_dd->at(0)->Clone("AFB_HighMass_dd");
 AFB_HighMass_dd->Reset();

 AFB_HighMass_upto10000 = (TH1D *)FZMass_HighMass_upto10000->at(0)->Clone("AFB_HighMass_upto10000");
 AFB_HighMass_upto10000->Reset();

 AFBFunction(FZMass_HighMass_Pseudodata, BZMass_HighMass_Pseudodata, AFB_HighMass);
 AFBFunction(FZMass_HighMass2_Pseudodata, BZMass_HighMass2_Pseudodata, AFB_HighMass2);
 AFBFunction(FZMass_HighMass_uu->at(0), BZMass_HighMass_uu->at(0), AFB_HighMass_uu);
 AFBFunction(FZMass_HighMass_dd->at(0), BZMass_HighMass_dd->at(0), AFB_HighMass_dd);
 AFBFunction(FZMass_HighMass_upto10000->at(0), BZMass_HighMass_upto10000->at(0), AFB_HighMass_upto10000);

 AFB_HighMass->Write();
 AFB_HighMass2->Write();
 AFB_HighMass_uu->Write();
 AFB_HighMass_dd->Write();
 AFB_HighMass_upto10000->Write();

 FZMass_HighMass_Pseudodata_300 = GenPseudodataNoFluc(300000.0, FZMass_HighMass->at(0), "Pseudodata300", 0, false);
 BZMass_HighMass_Pseudodata_300 = GenPseudodataNoFluc(300000.0, BZMass_HighMass->at(0), "Pseudodata300", 0, false);
 FZMass_HighMass2_Pseudodata_300 = GenPseudodataNoFluc(300000.0, FZMass_HighMass2->at(0), "Pseudodata300", 0, false);
 BZMass_HighMass2_Pseudodata_300 = GenPseudodataNoFluc(300000.0, BZMass_HighMass2->at(0), "Pseudodata300", 0, false);

 AFB_HighMass_300 = (TH1D *)FZMass_HighMass_Pseudodata_300->Clone("AFB_HighMass_300");
 AFB_HighMass_300->Reset();
 AFB_HighMass2_300 = (TH1D *)FZMass_HighMass2_Pseudodata_300->Clone("AFB_HighMass2_300");
 AFB_HighMass2_300->Reset();

 AFBFunction(FZMass_HighMass_Pseudodata_300, BZMass_HighMass_Pseudodata_300, AFB_HighMass_300);
 AFBFunction(FZMass_HighMass2_Pseudodata_300, BZMass_HighMass2_Pseudodata_300, AFB_HighMass2_300);

 AFB_HighMass_300->Write();
 AFB_HighMass2_300->Write();

 ZMass_HighMass_Pseudodata = GenPseudodataNoFluc(3000000.0, ZMass_HighMass->at(0));
 ZMass_HighMass_Pseudodata_300 = GenPseudodataNoFluc(300000.0, ZMass_HighMass->at(0), "Pseudodata300", 0, false);
 ZMass_HighMass_Pseudodata_140 = GenPseudodataNoFluc(140000.0, ZMass_HighMass->at(0), "Pseudodata140", 0, false);

 ZMass_HighMass_Pseudodata->Write();
 ZMass_HighMass_Pseudodata_300->Write();
 ZMass_HighMass_Pseudodata_140->Write();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 FZMass_LowMass1_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass_LowMass1->at(0));
 BZMass_LowMass1_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass_LowMass1->at(0));
 FZMass_LowMass2_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass_LowMass2->at(0));
 BZMass_LowMass2_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass_LowMass2->at(0));

 FZMass_LowMass1_Pseudodata->Write();
 BZMass_LowMass1_Pseudodata->Write();
 FZMass_LowMass2_Pseudodata->Write();
 BZMass_LowMass2_Pseudodata->Write();

 AFB_LowMass1 = (TH1D *)FZMass_LowMass1_Pseudodata->Clone("AFB_LowMass1");
 AFB_LowMass1->Reset();
 AFB_LowMass2 = (TH1D *)FZMass_LowMass2_Pseudodata->Clone("AFB_LowMass2");
 AFB_LowMass2->Reset();

 AFBFunction(FZMass_LowMass1_Pseudodata, BZMass_LowMass1_Pseudodata, AFB_LowMass1);
 AFBFunction(FZMass_LowMass2_Pseudodata, BZMass_LowMass2_Pseudodata, AFB_LowMass2);

 AFB_LowMass1->Write();
 AFB_LowMass2->Write();

 FZMass_LowMass1_ZY_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass_LowMass1_ZY->at(0));
 BZMass_LowMass1_ZY_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass_LowMass1_ZY->at(0));
 FZMass_LowMass2_ZY_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass_LowMass2_ZY->at(0));
 BZMass_LowMass2_ZY_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass_LowMass2_ZY->at(0));

 FZMass_LowMass1_ZY_Pseudodata->Write();
 BZMass_LowMass1_ZY_Pseudodata->Write();
 FZMass_LowMass2_ZY_Pseudodata->Write();
 BZMass_LowMass2_ZY_Pseudodata->Write();

 AFB_LowMass1_ZY = (TH2D *)FZMass_LowMass1_ZY_Pseudodata->Clone("AFB_LowMass1_ZY");
 AFB_LowMass1_ZY->Reset();
 AFB_LowMass2_ZY = (TH2D *)FZMass_LowMass2_ZY_Pseudodata->Clone("AFB_LowMass2_ZY");
 AFB_LowMass2_ZY->Reset();

 AFBFunction(FZMass_LowMass1_ZY_Pseudodata, BZMass_LowMass1_ZY_Pseudodata, AFB_LowMass1_ZY);
 AFBFunction(FZMass_LowMass2_ZY_Pseudodata, BZMass_LowMass2_ZY_Pseudodata, AFB_LowMass2_ZY);

 AFB_LowMass1_ZY->Write();
 AFB_LowMass2_ZY->Write();

//////////////////////////////////////////////////////////////////////////////////////////////////////

 FZMass_ATLAS_CC_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass_ATLAS_CC->at(0));
 BZMass_ATLAS_CC_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass_ATLAS_CC->at(0));
 FZMass_ATLAS_CF_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass_ATLAS_CF->at(0));
 BZMass_ATLAS_CF_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass_ATLAS_CF->at(0));

 AFB_ATLAS_CC = (TH1D *)FZMass_ATLAS_CC_Pseudodata->Clone("AFB_ATLAS_CC");
 AFB_ATLAS_CC->Reset();
 AFBFunction(FZMass_ATLAS_CC_Pseudodata, BZMass_ATLAS_CC_Pseudodata, AFB_ATLAS_CC);
 AFB_ATLAS_CC->Write();

 AFB_ATLAS_CF = (TH1D *)FZMass_ATLAS_CF_Pseudodata->Clone("AFB_ATLAS_CF");
 AFB_ATLAS_CF->Reset();
 AFBFunction(FZMass_ATLAS_CF_Pseudodata, BZMass_ATLAS_CF_Pseudodata, AFB_ATLAS_CF);
 AFB_ATLAS_CF->Write();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

 TH1D* AFB_Full = (TH1D *)FZMass_Full->at(0)->Clone("AFB_Full");
 AFB_Full->Reset();
 AFBFunction(FZMass_Full->at(0), BZMass_Full->at(0), AFB_Full);
 AFB_Full->Write();

 TH1D* AFB_Full_uu = (TH1D *)FZMass_Full_uu->at(0)->Clone("AFB_Full_uu");
 AFB_Full_uu->Reset();
 AFBFunction(FZMass_Full_uu->at(0), BZMass_Full_uu->at(0), AFB_Full_uu);
 AFB_Full_uu->Write();

 TH1D* AFB_Full_dd = (TH1D *)FZMass_Full_dd->at(0)->Clone("AFB_Full_dd");
 AFB_Full_dd->Reset();
 AFBFunction(FZMass_Full_dd->at(0), BZMass_Full_dd->at(0), AFB_Full_dd);
 AFB_Full_dd->Write();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

 Dilution_ZHighMass = (TH1D *)ZHighMass_wrong->at(0)->Clone("Dilution_ZHighMass");
 Dilution_ZHighMass->Divide(ZHighMass_total->at(0));
 Dilution_ZHighMass2 = (TH1D *)ZHighMass2_wrong->at(0)->Clone("Dilution_ZHighMass2");
 Dilution_ZHighMass2->Divide(ZHighMass2_total->at(0));
 Dilution_ZHighMass_uu = (TH1D *)ZHighMass_uu_wrong->at(0)->Clone("Dilution_ZHighMass_uu");
 Dilution_ZHighMass_uu->Divide(ZHighMass_uu_total->at(0));
 Dilution_ZHighMass_dd = (TH1D *)ZHighMass_dd_wrong->at(0)->Clone("Dilution_ZHighMass_dd");
 Dilution_ZHighMass_dd->Divide(ZHighMass_dd_total->at(0));
 Dilution_ZHighMass2_uu = (TH1D *)ZHighMass2_uu_wrong->at(0)->Clone("Dilution_ZHighMass2_uu");
 Dilution_ZHighMass2_uu->Divide(ZHighMass2_uu_total->at(0));
 Dilution_ZHighMass2_dd = (TH1D *)ZHighMass2_dd_wrong->at(0)->Clone("Dilution_ZHighMass2_dd");
 Dilution_ZHighMass2_dd->Divide(ZHighMass2_dd_total->at(0));

 Dilution_ZHighMass->Write();
 Dilution_ZHighMass2->Write();
 Dilution_ZHighMass_uu->Write();
 Dilution_ZHighMass_dd->Write();
 Dilution_ZHighMass2_uu->Write();
 Dilution_ZHighMass2_dd->Write();

///////////////////////////////////////////////////////////////////////////////////////////////////////////

 ZMass_utype_Pseudodata = GenPseudodataNoFluc(3000000.0, ZMass_utype->at(0));
 ZMass_dtype_Pseudodata = GenPseudodataNoFluc(3000000.0, ZMass_dtype->at(0));
 Xsec_3D_CC_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_3D_CC->at(0));
 Xsec_3D_CF_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_3D_CF->at(0));
 Xsec_3D_CC_LowMass_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_3D_CC_LowMass->at(0));
 Xsec_3D_CF_LowMass_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_3D_CF_LowMass->at(0));
 Xsec_3D_CC_HighMass_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_3D_CC_HighMass->at(0));
 Xsec_3D_CF_HighMass_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_3D_CF_HighMass->at(0));
 Xsec_2D_CC_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_2D_CC->at(0));
 Xsec_2D_CF_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_2D_CF->at(0));
 Xsec_1D_CC_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_1D_CC->at(0));
 Xsec_1D_CF_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_1D_CF->at(0));
 ZRapidity_CC_Pseudodata = GenPseudodataNoFluc(3000000.0, ZRapidity_CC->at(0));
 ZRapidity_CF_Pseudodata = GenPseudodataNoFluc(3000000.0, ZRapidity_CF->at(0));
 ZRapidity_CF_Low_Pseudodata = GenPseudodataNoFluc(3000000.0, ZRapidity_CF_Low->at(0));
 ZHighMass_CC_Pseudodata = GenPseudodataNoFluc(3000000.0, ZHighMass_CC->at(0));
 ZHighMass_CF_Pseudodata = GenPseudodataNoFluc(3000000.0, ZHighMass_CF->at(0));
 CrossSection_Pseudodata = GenPseudodataNoFluc(3000000.0, CrossSection->at(0));
 CrossSectionF_Pseudodata = GenPseudodataNoFluc(3000000.0, CrossSectionF->at(0));
 CrossSectionB_Pseudodata = GenPseudodataNoFluc(3000000.0, CrossSectionB->at(0));

 Xsec_3D_CC_Pseudodata_300 = GenPseudodataNoFluc(300000.0, Xsec_3D_CC->at(0), "Pseudodata300", 0, false);
 Xsec_3D_CF_Pseudodata_300 = GenPseudodataNoFluc(300000.0, Xsec_3D_CF->at(0), "Pseudodata300", 0, false);
 Xsec_2D_CC_Pseudodata_300 = GenPseudodataNoFluc(300000.0, Xsec_2D_CC->at(0), "Pseudodata300", 0, false);
 Xsec_2D_CF_Pseudodata_300 = GenPseudodataNoFluc(300000.0, Xsec_2D_CF->at(0), "Pseudodata300", 0, false);
 Xsec_1D_CC_Pseudodata_300 = GenPseudodataNoFluc(300000.0, Xsec_1D_CC->at(0), "Pseudodata300", 0, false);
 Xsec_1D_CF_Pseudodata_300 = GenPseudodataNoFluc(300000.0, Xsec_1D_CF->at(0), "Pseudodata300", 0, false);
 Xsec_3D_CC_Pseudodata_140 = GenPseudodataNoFluc(140000.0, Xsec_3D_CC->at(0), "Pseudodata140", 0, false);
 Xsec_3D_CF_Pseudodata_140 = GenPseudodataNoFluc(140000.0, Xsec_3D_CF->at(0), "Pseudodata140", 0, false);
 Xsec_2D_CC_Pseudodata_140 = GenPseudodataNoFluc(140000.0, Xsec_2D_CC->at(0), "Pseudodata140", 0, false);
 Xsec_2D_CF_Pseudodata_140 = GenPseudodataNoFluc(140000.0, Xsec_2D_CF->at(0), "Pseudodata140", 0, false);
 Xsec_1D_CC_Pseudodata_140 = GenPseudodataNoFluc(140000.0, Xsec_1D_CC->at(0), "Pseudodata140", 0, false);
 Xsec_1D_CF_Pseudodata_140 = GenPseudodataNoFluc(140000.0, Xsec_1D_CF->at(0), "Pseudodata140", 0, false);

 CrossSectionAFB = (TH1D *)CrossSectionF_Pseudodata->Clone("CrossSectionAFB");
 CrossSectionAFB->Reset();
 AFBFunction(CrossSectionF_Pseudodata, CrossSectionB_Pseudodata, CrossSectionAFB);

 ZMass_utype_Pseudodata->Write();
 ZMass_dtype_Pseudodata->Write();
 Xsec_3D_CC_Pseudodata->Write();
 Xsec_3D_CF_Pseudodata->Write();
 Xsec_3D_CC_LowMass_Pseudodata->Write();
 Xsec_3D_CF_LowMass_Pseudodata->Write();
 Xsec_3D_CC_HighMass_Pseudodata->Write();
 Xsec_3D_CF_HighMass_Pseudodata->Write();
 Xsec_2D_CC_Pseudodata->Write();
 Xsec_2D_CF_Pseudodata->Write();
 Xsec_1D_CC_Pseudodata->Write();
 Xsec_1D_CF_Pseudodata->Write();
 ZRapidity_CC_Pseudodata->Write();
 ZRapidity_CF_Pseudodata->Write();
 ZRapidity_CF_Low_Pseudodata->Write();
 ZHighMass_CC_Pseudodata->Write();
 ZHighMass_CF_Pseudodata->Write();
 CrossSection_Pseudodata->Write();
 CrossSectionF_Pseudodata->Write();
 CrossSectionB_Pseudodata->Write();
 CrossSectionAFB->Write();

 Xsec_3D_CC_Pseudodata_300->Write();
 Xsec_3D_CF_Pseudodata_300->Write();
 Xsec_2D_CC_Pseudodata_300->Write();
 Xsec_2D_CF_Pseudodata_300->Write();
 Xsec_1D_CC_Pseudodata_300->Write();
 Xsec_1D_CF_Pseudodata_300->Write();
 Xsec_3D_CC_Pseudodata_140->Write();
 Xsec_3D_CF_Pseudodata_140->Write();
 Xsec_2D_CC_Pseudodata_140->Write();
 Xsec_2D_CF_Pseudodata_140->Write();
 Xsec_1D_CC_Pseudodata_140->Write();
 Xsec_1D_CF_Pseudodata_140->Write();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

 AFB_PosiLeptonEta = (TH1D *)ForwardPosiLeptonEta->at(0)->Clone("AFB_PosiLeptonEta");
 AFB_PosiLeptonEta->Reset();
 AFBFunction(ForwardPosiLeptonEta->at(0), BackwardPosiLeptonEta->at(0), AFB_PosiLeptonEta);
 AFB_PosiLeptonEta->Write();

 AFB_NegaLeptonEta = (TH1D *)ForwardNegaLeptonEta->at(0)->Clone("AFB_NegaLeptonEta");
 AFB_NegaLeptonEta->Reset();
 AFBFunction(ForwardNegaLeptonEta->at(0), BackwardNegaLeptonEta->at(0), AFB_NegaLeptonEta);
 AFB_NegaLeptonEta->Write();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////
 //  ATLAS 8TeV ZPT  //
 //////////////////////

 HistDivideBinWidth(ATLASZPt_2D_Fiduc->at(0), ATLASZPt_2D_Fiduc_Final, "X");
 HistDivideBinWidth(ATLASZPt_2D_Total->at(0), ATLASZPt_2D_Total_Final, "X");
 HistDivideBinWidth(ATLASZPt_2D_Total_uu->at(0), ATLASZPt_2D_Total_uu_Final, "X");
 HistDivideBinWidth(ATLASZPt_2D_Total_dd->at(0), ATLASZPt_2D_Total_dd_Final, "X");
 HistDivideBinWidth(ATLASZPt_2D_Total_MassWindow->at(0), ATLASZPt_2D_Total_MassWindow_Final, "X");

 ATLASZPt_2D_Fiduc_Final->Write();
 ATLASZPt_2D_Total_Final->Write();
 ATLASZPt_2D_Total_uu_Final->Write();
 ATLASZPt_2D_Total_dd_Final->Write();
 ATLASZPt_2D_Total_MassWindow_Final->Write();

 //////////////////////
 // ATLAS 13TeV HMDY //
 //////////////////////

 ATLAS_Mll_HighMass_Pseudodata = GenPseudodataNoFluc(140000.0, ATLAS_Mll_HighMass->at(0));
 ATLAS_costheta_Pseudodata = GenPseudodataNoFluc(140000.0, ATLAS_costheta->at(0));
 ATLAS_DilRapidity_Pseudodata = GenPseudodataNoFluc(140000.0, ATLAS_DilRapidity->at(0));
 ATLAS_Mll_HighMass_costheta_Pseudodata = GenPseudodataNoFluc(140000.0, ATLAS_Mll_HighMass_costheta->at(0));
 ATLAS_Mll_HighMass_DilRapidity_Pseudodata = GenPseudodataNoFluc(140000.0, ATLAS_Mll_HighMass_DilRapidity->at(0));
 ATLAS_HMDY_Xsec_3D_Pseudodata = GenPseudodataNoFluc(140000.0, ATLAS_HMDY_Xsec_3D->at(0));

 ATLAS_Mll_HighMass_Pseudodata->Write();
 ATLAS_costheta_Pseudodata->Write();
 ATLAS_DilRapidity_Pseudodata->Write();
 ATLAS_Mll_HighMass_costheta_Pseudodata->Write();
 ATLAS_Mll_HighMass_DilRapidity_Pseudodata->Write();
 ATLAS_HMDY_Xsec_3D_Pseudodata->Write();

 ATLAS_Mll_HighMass_FineBin_Pseudodata = GenPseudodataNoFluc(3000000.0, ATLAS_Mll_HighMass_FineBin->at(0));
 ATLAS_costheta_FineBin_Pseudodata = GenPseudodataNoFluc(3000000.0, ATLAS_costheta_FineBin->at(0));
 ATLAS_DilRapidity_FineBin_Pseudodata = GenPseudodataNoFluc(3000000.0, ATLAS_DilRapidity_FineBin->at(0));
 ATLAS_Mll_HighMass_costheta_FineBin_Pseudodata = GenPseudodataNoFluc(3000000.0, ATLAS_Mll_HighMass_costheta_FineBin->at(0));
 ATLAS_Mll_HighMass_DilRapidity_FineBin_Pseudodata = GenPseudodataNoFluc(3000000.0, ATLAS_Mll_HighMass_DilRapidity_FineBin->at(0));
 ATLAS_HMDY_Xsec_3D_FineBin_Pseudodata = GenPseudodataNoFluc(3000000.0, ATLAS_HMDY_Xsec_3D_FineBin->at(0));

 ATLAS_Mll_HighMass_FineBin_Pseudodata->Write();
 ATLAS_costheta_FineBin_Pseudodata->Write();
 ATLAS_DilRapidity_FineBin_Pseudodata->Write();
 ATLAS_Mll_HighMass_costheta_FineBin_Pseudodata->Write();
 ATLAS_Mll_HighMass_DilRapidity_FineBin_Pseudodata->Write();
 ATLAS_HMDY_Xsec_3D_FineBin_Pseudodata->Write();

 ATLAS_Mll_HighMass_costheta_NewBinning = new TH1D("ATLAS_Mll_HighMass_costheta_NewBinning", "ATLAS_Mll_HighMass_costheta_NewBinning", 49, 0, 49);

 int ibin = 1;
 for(int ibinx = 1; ibinx <= ATLAS_Mll_HighMass_costheta_1->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= ATLAS_Mll_HighMass_costheta_1->at(0)->GetNbinsY(); ibiny++){
     ATLAS_Mll_HighMass_costheta_NewBinning->SetBinContent(ibin, ATLAS_Mll_HighMass_costheta_1->at(0)->GetBinContent(ibinx, ibiny));
     ATLAS_Mll_HighMass_costheta_NewBinning->SetBinError(ibin, ATLAS_Mll_HighMass_costheta_1->at(0)->GetBinError(ibinx, ibiny));
     ibin++;
   }
 }

 for(int ibinx = 1; ibinx <= ATLAS_Mll_HighMass_costheta_2->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= ATLAS_Mll_HighMass_costheta_2->at(0)->GetNbinsY(); ibiny++){
     ATLAS_Mll_HighMass_costheta_NewBinning->SetBinContent(ibin, ATLAS_Mll_HighMass_costheta_2->at(0)->GetBinContent(ibinx, ibiny));
     ATLAS_Mll_HighMass_costheta_NewBinning->SetBinError(ibin, ATLAS_Mll_HighMass_costheta_2->at(0)->GetBinError(ibinx, ibiny));
     ibin++;
   }
 }

 for(int ibinx = 1; ibinx <= ATLAS_Mll_HighMass_costheta_3->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= ATLAS_Mll_HighMass_costheta_3->at(0)->GetNbinsY(); ibiny++){
     ATLAS_Mll_HighMass_costheta_NewBinning->SetBinContent(ibin, ATLAS_Mll_HighMass_costheta_3->at(0)->GetBinContent(ibinx, ibiny));
     ATLAS_Mll_HighMass_costheta_NewBinning->SetBinError(ibin, ATLAS_Mll_HighMass_costheta_3->at(0)->GetBinError(ibinx, ibiny));
     ibin++;
   }
 }

 ATLAS_Mll_HighMass_DilRapidity_NewBinning = new TH1D("ATLAS_Mll_HighMass_DilRapidity_NewBinning", "ATLAS_Mll_HighMass_DilRapidity_NewBinning", 57, 0, 57);

 ibin = 1;
 for(int ibinx = 1; ibinx <= ATLAS_Mll_HighMass_DilRapidity_1->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= ATLAS_Mll_HighMass_DilRapidity_1->at(0)->GetNbinsY(); ibiny++){
     ATLAS_Mll_HighMass_DilRapidity_NewBinning->SetBinContent(ibin, ATLAS_Mll_HighMass_DilRapidity_1->at(0)->GetBinContent(ibinx, ibiny));
     ATLAS_Mll_HighMass_DilRapidity_NewBinning->SetBinError(ibin, ATLAS_Mll_HighMass_DilRapidity_1->at(0)->GetBinError(ibinx, ibiny));
     ibin++;
   }
 }

 for(int ibinx = 1; ibinx <= ATLAS_Mll_HighMass_DilRapidity_2->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= ATLAS_Mll_HighMass_DilRapidity_2->at(0)->GetNbinsY(); ibiny++){
     ATLAS_Mll_HighMass_DilRapidity_NewBinning->SetBinContent(ibin, ATLAS_Mll_HighMass_DilRapidity_2->at(0)->GetBinContent(ibinx, ibiny));
     ATLAS_Mll_HighMass_DilRapidity_NewBinning->SetBinError(ibin, ATLAS_Mll_HighMass_DilRapidity_2->at(0)->GetBinError(ibinx, ibiny));
     ibin++;
   }
 }

 for(int ibinx = 1; ibinx <= ATLAS_Mll_HighMass_DilRapidity_3->at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= ATLAS_Mll_HighMass_DilRapidity_3->at(0)->GetNbinsY(); ibiny++){
     ATLAS_Mll_HighMass_DilRapidity_NewBinning->SetBinContent(ibin, ATLAS_Mll_HighMass_DilRapidity_3->at(0)->GetBinContent(ibinx, ibiny));
     ATLAS_Mll_HighMass_DilRapidity_NewBinning->SetBinError(ibin, ATLAS_Mll_HighMass_DilRapidity_3->at(0)->GetBinError(ibinx, ibiny));
     ibin++;
   }
 }

 ATLAS_Mll_HighMass_costheta_NewBinning_Pseudodata = GenPseudodataNoFluc(140000.0, ATLAS_Mll_HighMass_costheta_NewBinning);
 ATLAS_Mll_HighMass_DilRapidity_NewBinning_Pseudodata = GenPseudodataNoFluc(140000.0, ATLAS_Mll_HighMass_DilRapidity_NewBinning);

 ATLAS_Mll_HighMass_costheta_NewBinning->Write();
 ATLAS_Mll_HighMass_DilRapidity_NewBinning->Write();

 ATLAS_Mll_HighMass_costheta_NewBinning_Pseudodata->Write();
 ATLAS_Mll_HighMass_DilRapidity_NewBinning_Pseudodata->Write();

//////////////////////////////////////////////////////////////////////////////////////////////////

 PositiveLeptonEta_Pseudodata = GenPseudodataNoFluc(3000000.0, PositiveLeptonEta->at(0));
 NegativeLeptonEta_Pseudodata = GenPseudodataNoFluc(3000000.0, NegativeLeptonEta->at(0));
 PositiveLeptonHighEta_Pseudodata = GenPseudodataNoFluc(3000000.0, PositiveLeptonHighEta->at(0));
 NegativeLeptonHighEta_Pseudodata = GenPseudodataNoFluc(3000000.0, NegativeLeptonHighEta->at(0));
 PositiveLeptonLowEta_Pseudodata = GenPseudodataNoFluc(3000000.0, PositiveLeptonLowEta->at(0));
 NegativeLeptonLowEta_Pseudodata = GenPseudodataNoFluc(3000000.0, NegativeLeptonLowEta->at(0));
 PositiveLeptonPt_Pseudodata = GenPseudodataNoFluc(3000000.0, PositiveLeptonPt->at(0));
 NegativeLeptonPt_Pseudodata = GenPseudodataNoFluc(3000000.0, NegativeLeptonPt->at(0));
 PositiveLeptonPtEta_Pseudodata = GenPseudodataNoFluc(3000000.0, PositiveLeptonPtEta->at(0));
 NegativeLeptonPtEta_Pseudodata = GenPseudodataNoFluc(3000000.0, NegativeLeptonPtEta->at(0));
 WPlusMTEta_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusMTEta->at(0));
 WMinusMTEta_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusMTEta->at(0));
 WPlusMTEta_Above100_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusMTEta_Above100->at(0));
 WMinusMTEta_Above100_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusMTEta_Above100->at(0));
 WPlusMTEta_FullEta_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusMTEta_FullEta->at(0));
 WMinusMTEta_FullEta_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusMTEta_FullEta->at(0));
 WPlusMTEta_FullEta_Above100_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusMTEta_FullEta_Above100->at(0));
 WMinusMTEta_FullEta_Above100_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusMTEta_FullEta_Above100->at(0));
 WLeptonPt_Pseudodata = GenPseudodataNoFluc(3000000.0, WLeptonPt->at(0));
 WPlusNeutrinoPt_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusNeutrinoPt->at(0));
 WMinusNeutrinoPt_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusNeutrinoPt->at(0));
 NeutrinoPt_Pseudodata = GenPseudodataNoFluc(3000000.0, NeutrinoPt->at(0));
 WPlusMT_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusMT->at(0));
 WMinusMT_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusMT->at(0));
 WPlusMT_Above100_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusMT_Above100->at(0));
 WMinusMT_Above100_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusMT_Above100->at(0));
 WBosonMT_Pseudodata = GenPseudodataNoFluc(3000000.0, WBosonMT->at(0));
 WPlusXsec_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusXsec->at(0));
 WMinusXsec_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusXsec->at(0));
 WHighMassMT_Pseudodata = GenPseudodataNoFluc(3000000.0, WHighMassMT->at(0));
 WPlusHighMassMT_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusHighMassMT->at(0));
 WMinusHighMassMT_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusHighMassMT->at(0));
 WPlusForwardEta_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusForwardEta->at(0));
 WPlusBackwardEta_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusBackwardEta->at(0));
 WMinusForwardEta_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusForwardEta->at(0));
 WMinusBackwardEta_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusBackwardEta->at(0));
 WPlusForwardEta_ExpPz_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusForwardEta_ExpPz->at(0));
 WPlusBackwardEta_ExpPz_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusBackwardEta_ExpPz->at(0));
 WMinusForwardEta_ExpPz_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusForwardEta_ExpPz->at(0));
 WMinusBackwardEta_ExpPz_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusBackwardEta_ExpPz->at(0));
 WPlusForwardEta_ExpEta_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusForwardEta_ExpEta->at(0));
 WPlusBackwardEta_ExpEta_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusBackwardEta_ExpEta->at(0));
 WMinusForwardEta_ExpEta_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusForwardEta_ExpEta->at(0));
 WMinusBackwardEta_ExpEta_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusBackwardEta_ExpEta->at(0));

 PositiveLeptonEta_Pseudodata_300 = GenPseudodataNoFluc(300000.0, PositiveLeptonEta->at(0), "Pseudodata300", 0, false);
 NegativeLeptonEta_Pseudodata_300 = GenPseudodataNoFluc(300000.0, NegativeLeptonEta->at(0), "Pseudodata300", 0, false);
 PositiveLeptonHighEta_Pseudodata_300 = GenPseudodataNoFluc(300000.0, PositiveLeptonHighEta->at(0), "Pseudodata300", 0, false);
 NegativeLeptonHighEta_Pseudodata_300 = GenPseudodataNoFluc(300000.0, NegativeLeptonHighEta->at(0), "Pseudodata300", 0, false);
 PositiveLeptonLowEta_Pseudodata_300 = GenPseudodataNoFluc(300000.0, PositiveLeptonLowEta->at(0), "Pseudodata300", 0, false);
 NegativeLeptonLowEta_Pseudodata_300 = GenPseudodataNoFluc(300000.0, NegativeLeptonLowEta->at(0), "Pseudodata300", 0, false);
 PositiveLeptonPt_Pseudodata_300 = GenPseudodataNoFluc(300000.0, PositiveLeptonPt->at(0), "Pseudodata300", 0, false);
 NegativeLeptonPt_Pseudodata_300 = GenPseudodataNoFluc(300000.0, NegativeLeptonPt->at(0), "Pseudodata300", 0, false);
 PositiveLeptonPtEta_Pseudodata_300 = GenPseudodataNoFluc(300000.0, PositiveLeptonPtEta->at(0), "Pseudodata300", 0, false);
 NegativeLeptonPtEta_Pseudodata_300 = GenPseudodataNoFluc(300000.0, NegativeLeptonPtEta->at(0), "Pseudodata300", 0, false);
 WPlusMTEta_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WPlusMTEta->at(0), "Pseudodata300", 0, false);
 WMinusMTEta_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WMinusMTEta->at(0), "Pseudodata300", 0, false);
 WLeptonPt_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WLeptonPt->at(0), "Pseudodata300", 0, false);
 WPlusNeutrinoPt_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WPlusNeutrinoPt->at(0), "Pseudodata300", 0, false);
 WMinusNeutrinoPt_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WMinusNeutrinoPt->at(0), "Pseudodata300", 0, false);
 NeutrinoPt_Pseudodata_300 = GenPseudodataNoFluc(300000.0, NeutrinoPt->at(0), "Pseudodata300", 0, false);
 WPlusMT_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WPlusMT->at(0), "Pseudodata300", 0, false);
 WMinusMT_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WMinusMT->at(0), "Pseudodata300", 0, false);
 WBosonMT_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WBosonMT->at(0), "Pseudodata300", 0, false);
 WPlusXsec_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WPlusXsec->at(0), "Pseudodata300", 0, false);
 WMinusXsec_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WMinusXsec->at(0), "Pseudodata300", 0, false);
 WHighMassMT_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WHighMassMT->at(0), "Pseudodata300", 0, false);
 WPlusHighMassMT_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WPlusHighMassMT->at(0), "Pseudodata300", 0, false);
 WMinusHighMassMT_Pseudodata_300 = GenPseudodataNoFluc(300000.0, WMinusHighMassMT->at(0), "Pseudodata300", 0, false);

 PositiveLeptonEta_Pseudodata_140 = GenPseudodataNoFluc(140000.0, PositiveLeptonEta->at(0), "Pseudodata140", 0, false);
 NegativeLeptonEta_Pseudodata_140 = GenPseudodataNoFluc(140000.0, NegativeLeptonEta->at(0), "Pseudodata140", 0, false);
 PositiveLeptonHighEta_Pseudodata_140 = GenPseudodataNoFluc(140000.0, PositiveLeptonHighEta->at(0), "Pseudodata140", 0, false);
 NegativeLeptonHighEta_Pseudodata_140 = GenPseudodataNoFluc(140000.0, NegativeLeptonHighEta->at(0), "Pseudodata140", 0, false);
 PositiveLeptonLowEta_Pseudodata_140 = GenPseudodataNoFluc(140000.0, PositiveLeptonLowEta->at(0), "Pseudodata140", 0, false);
 NegativeLeptonLowEta_Pseudodata_140 = GenPseudodataNoFluc(140000.0, NegativeLeptonLowEta->at(0), "Pseudodata140", 0, false);
 PositiveLeptonPt_Pseudodata_140 = GenPseudodataNoFluc(140000.0, PositiveLeptonPt->at(0), "Pseudodata140", 0, false);
 NegativeLeptonPt_Pseudodata_140 = GenPseudodataNoFluc(140000.0, NegativeLeptonPt->at(0), "Pseudodata140", 0, false);
 PositiveLeptonPtEta_Pseudodata_140 = GenPseudodataNoFluc(140000.0, PositiveLeptonPtEta->at(0), "Pseudodata140", 0, false);
 NegativeLeptonPtEta_Pseudodata_140 = GenPseudodataNoFluc(140000.0, NegativeLeptonPtEta->at(0), "Pseudodata140", 0, false);
 WPlusMTEta_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WPlusMTEta->at(0), "Pseudodata140", 0, false);
 WMinusMTEta_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WMinusMTEta->at(0), "Pseudodata140", 0, false);
 WLeptonPt_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WLeptonPt->at(0), "Pseudodata140", 0, false);
 WPlusNeutrinoPt_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WPlusNeutrinoPt->at(0), "Pseudodata140", 0, false);
 WMinusNeutrinoPt_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WMinusNeutrinoPt->at(0), "Pseudodata140", 0, false);
 NeutrinoPt_Pseudodata_140 = GenPseudodataNoFluc(140000.0, NeutrinoPt->at(0), "Pseudodata140", 0, false);
 WPlusMT_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WPlusMT->at(0), "Pseudodata140", 0, false);
 WMinusMT_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WMinusMT->at(0), "Pseudodata140", 0, false);
 WBosonMT_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WBosonMT->at(0), "Pseudodata140", 0, false);
 WPlusXsec_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WPlusXsec->at(0), "Pseudodata140", 0, false);
 WMinusXsec_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WMinusXsec->at(0), "Pseudodata140", 0, false);
 WHighMassMT_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WHighMassMT->at(0), "Pseudodata140", 0, false);
 WPlusHighMassMT_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WPlusHighMassMT->at(0), "Pseudodata140", 0, false);
 WMinusHighMassMT_Pseudodata_140 = GenPseudodataNoFluc(140000.0, WMinusHighMassMT->at(0), "Pseudodata140", 0, false);

 PositiveLeptonEta_Pseudodata->Write();
 NegativeLeptonEta_Pseudodata->Write();
 PositiveLeptonHighEta_Pseudodata->Write();
 NegativeLeptonHighEta_Pseudodata->Write();
 PositiveLeptonLowEta_Pseudodata->Write();
 NegativeLeptonLowEta_Pseudodata->Write();
 PositiveLeptonPt_Pseudodata->Write();
 NegativeLeptonPt_Pseudodata->Write();
 PositiveLeptonPtEta_Pseudodata->Write();
 NegativeLeptonPtEta_Pseudodata->Write();
 WPlusMTEta_Pseudodata->Write();
 WMinusMTEta_Pseudodata->Write();
 WPlusMTEta_Above100_Pseudodata->Write();
 WMinusMTEta_Above100_Pseudodata->Write();
 WPlusMTEta_FullEta_Pseudodata->Write();
 WMinusMTEta_FullEta_Pseudodata->Write();
 WPlusMTEta_FullEta_Above100_Pseudodata->Write();
 WMinusMTEta_FullEta_Above100_Pseudodata->Write();
 WLeptonPt_Pseudodata->Write();
 WPlusNeutrinoPt_Pseudodata->Write();
 WMinusNeutrinoPt_Pseudodata->Write();
 NeutrinoPt_Pseudodata->Write();
 WPlusMT_Pseudodata->Write();
 WMinusMT_Pseudodata->Write();
 WPlusMT_Above100_Pseudodata->Write();
 WMinusMT_Above100_Pseudodata->Write();
 WBosonMT_Pseudodata->Write();
 WPlusXsec_Pseudodata->Write();
 WMinusXsec_Pseudodata->Write();
 WHighMassMT_Pseudodata->Write();
 WPlusHighMassMT_Pseudodata->Write();
 WMinusHighMassMT_Pseudodata->Write();
 WPlusForwardEta_Pseudodata->Write();
 WPlusBackwardEta_Pseudodata->Write();
 WMinusForwardEta_Pseudodata->Write();
 WMinusBackwardEta_Pseudodata->Write();
 WPlusForwardEta_ExpPz_Pseudodata->Write();
 WPlusBackwardEta_ExpPz_Pseudodata->Write();
 WMinusForwardEta_ExpPz_Pseudodata->Write();
 WMinusBackwardEta_ExpPz_Pseudodata->Write();
 WPlusForwardEta_ExpEta_Pseudodata->Write();
 WPlusBackwardEta_ExpEta_Pseudodata->Write();
 WMinusForwardEta_ExpEta_Pseudodata->Write();
 WMinusBackwardEta_ExpEta_Pseudodata->Write();

 PositiveLeptonEta_Pseudodata_300->Write();
 NegativeLeptonEta_Pseudodata_300->Write();
 PositiveLeptonHighEta_Pseudodata_300->Write();
 NegativeLeptonHighEta_Pseudodata_300->Write();
 PositiveLeptonLowEta_Pseudodata_300->Write();
 NegativeLeptonLowEta_Pseudodata_300->Write();
 PositiveLeptonPt_Pseudodata_300->Write();
 NegativeLeptonPt_Pseudodata_300->Write();
 PositiveLeptonPtEta_Pseudodata_300->Write();
 NegativeLeptonPtEta_Pseudodata_300->Write();
 WPlusMTEta_Pseudodata_300->Write();
 WMinusMTEta_Pseudodata_300->Write();
 WLeptonPt_Pseudodata_300->Write();
 WPlusNeutrinoPt_Pseudodata_300->Write();
 WMinusNeutrinoPt_Pseudodata_300->Write();
 NeutrinoPt_Pseudodata_300->Write();
 WPlusMT_Pseudodata_300->Write();
 WMinusMT_Pseudodata_300->Write();
 WBosonMT_Pseudodata_300->Write();
 WPlusXsec_Pseudodata_300->Write();
 WMinusXsec_Pseudodata_300->Write();
 WHighMassMT_Pseudodata_300->Write();
 WPlusHighMassMT_Pseudodata_300->Write();
 WMinusHighMassMT_Pseudodata_300->Write();

 PositiveLeptonEta_Pseudodata_140->Write();
 NegativeLeptonEta_Pseudodata_140->Write();
 PositiveLeptonHighEta_Pseudodata_140->Write();
 NegativeLeptonHighEta_Pseudodata_140->Write();
 PositiveLeptonLowEta_Pseudodata_140->Write();
 NegativeLeptonLowEta_Pseudodata_140->Write();
 PositiveLeptonPt_Pseudodata_140->Write();
 NegativeLeptonPt_Pseudodata_140->Write();
 PositiveLeptonPtEta_Pseudodata_140->Write();
 NegativeLeptonPtEta_Pseudodata_140->Write();
 WPlusMTEta_Pseudodata_140->Write();
 WMinusMTEta_Pseudodata_140->Write();
 WLeptonPt_Pseudodata_140->Write();
 WPlusNeutrinoPt_Pseudodata_140->Write();
 WMinusNeutrinoPt_Pseudodata_140->Write();
 NeutrinoPt_Pseudodata_140->Write();
 WPlusMT_Pseudodata_140->Write();
 WMinusMT_Pseudodata_140->Write();
 WBosonMT_Pseudodata_140->Write();
 WPlusXsec_Pseudodata_140->Write();
 WMinusXsec_Pseudodata_140->Write();
 WHighMassMT_Pseudodata_140->Write();
 WPlusHighMassMT_Pseudodata_140->Write();
 WMinusHighMassMT_Pseudodata_140->Write();

 WLeptonEtaAsymmetry = (TH1D *)PositiveLeptonEta_Pseudodata->Clone("WLeptonEtaAsymmetry");
 WLeptonEtaAsymmetry->Reset();
 WLeptonPtAsymmetry = (TH1D *)PositiveLeptonPt_Pseudodata->Clone("WLeptonPtAsymmetry");
 WLeptonPtAsymmetry->Reset();
 NeutrinoPtAsymmetry = (TH1D *)WPlusNeutrinoPt_Pseudodata->Clone("NeutrinoPtAsymmetry");
 NeutrinoPtAsymmetry->Reset();
 WBosonMTAsymmetry = (TH1D *)WPlusMT_Pseudodata->Clone("WBosonMTAsymmetry");
 WBosonMTAsymmetry->Reset();
 WBosonXsecAsymmetry = (TH1D *)WPlusXsec_Pseudodata->Clone("WBosonXsecAsymmetry");
 WBosonXsecAsymmetry->Reset();
 WPositiveLeptonEtaAsymmetry = (TH1D *)PositiveLeptonLowEta_Pseudodata->Clone("WPositiveLeptonEtaAsymmetry");
 WPositiveLeptonEtaAsymmetry->Reset();
 WNegativeLeptonEtaAsymmetry = (TH1D *)NegativeLeptonLowEta_Pseudodata->Clone("WNegativeLeptonEtaAsymmetry");
 WNegativeLeptonEtaAsymmetry->Reset();
 WMTEtaAsymmetry = (TH2D *)WPlusMTEta_Pseudodata->Clone("WMTEtaAsymmetry");
 WMTEtaAsymmetry->Reset();

 AFBFunction(PositiveLeptonEta_Pseudodata, NegativeLeptonEta_Pseudodata, WLeptonEtaAsymmetry);
 AFBFunction(PositiveLeptonPt_Pseudodata, NegativeLeptonPt_Pseudodata, WLeptonPtAsymmetry);
 AFBFunction(WPlusNeutrinoPt_Pseudodata, WMinusNeutrinoPt_Pseudodata, NeutrinoPtAsymmetry);
 AFBFunction(WPlusMT_Pseudodata, WMinusMT_Pseudodata, WBosonMTAsymmetry);
 AFBFunction(WPlusXsec_Pseudodata, WMinusXsec_Pseudodata, WBosonXsecAsymmetry);
 AFBFunction(PositiveLeptonLowEta_Pseudodata, PositiveLeptonHighEta_Pseudodata, WPositiveLeptonEtaAsymmetry);
 AFBFunction(NegativeLeptonLowEta_Pseudodata, NegativeLeptonHighEta_Pseudodata, WNegativeLeptonEtaAsymmetry);
 AFBFunction(WPlusMTEta_Pseudodata, WMinusMTEta_Pseudodata, WMTEtaAsymmetry);

 WLeptonEtaAsymmetry->Write();
 WLeptonPtAsymmetry->Write();
 NeutrinoPtAsymmetry->Write();
 WBosonMTAsymmetry->Write();
 WBosonXsecAsymmetry->Write();
 WPositiveLeptonEtaAsymmetry->Write();
 WNegativeLeptonEtaAsymmetry->Write();
 WMTEtaAsymmetry->Write();

 WLeptonEtaAsymmetry_300 = (TH1D *)PositiveLeptonEta_Pseudodata_300->Clone("WLeptonEtaAsymmetry_300");
 WLeptonEtaAsymmetry_300->Reset();
 WLeptonPtAsymmetry_300 = (TH1D *)PositiveLeptonPt_Pseudodata_300->Clone("WLeptonPtAsymmetry_300");
 WLeptonPtAsymmetry_300->Reset();
 NeutrinoPtAsymmetry_300 = (TH1D *)WPlusNeutrinoPt_Pseudodata_300->Clone("NeutrinoPtAsymmetry_300");
 NeutrinoPtAsymmetry_300->Reset();
 WBosonMTAsymmetry_300 = (TH1D *)WPlusMT_Pseudodata_300->Clone("WBosonMTAsymmetry_300");
 WBosonMTAsymmetry_300->Reset();
 WBosonXsecAsymmetry_300 = (TH1D *)WPlusXsec_Pseudodata_300->Clone("WBosonXsecAsymmetry_300");
 WBosonXsecAsymmetry_300->Reset();
 WPositiveLeptonEtaAsymmetry_300 = (TH1D *)PositiveLeptonLowEta_Pseudodata_300->Clone("WPositiveLeptonEtaAsymmetry_300");
 WPositiveLeptonEtaAsymmetry_300->Reset();
 WNegativeLeptonEtaAsymmetry_300 = (TH1D *)NegativeLeptonLowEta_Pseudodata_300->Clone("WNegativeLeptonEtaAsymmetry_300");
 WNegativeLeptonEtaAsymmetry_300->Reset();
 WMTEtaAsymmetry_300 = (TH2D *)WPlusMTEta_Pseudodata_300->Clone("WMTEtaAsymmetry_300");
 WMTEtaAsymmetry_300->Reset();

 AFBFunction(PositiveLeptonEta_Pseudodata_300, NegativeLeptonEta_Pseudodata_300, WLeptonEtaAsymmetry_300);
 AFBFunction(PositiveLeptonPt_Pseudodata_300, NegativeLeptonPt_Pseudodata_300, WLeptonPtAsymmetry_300);
 AFBFunction(WPlusNeutrinoPt_Pseudodata_300, WMinusNeutrinoPt_Pseudodata_300, NeutrinoPtAsymmetry_300);
 AFBFunction(WPlusMT_Pseudodata_300, WMinusMT_Pseudodata_300, WBosonMTAsymmetry_300);
 AFBFunction(WPlusXsec_Pseudodata_300, WMinusXsec_Pseudodata_300, WBosonXsecAsymmetry_300);
 AFBFunction(PositiveLeptonLowEta_Pseudodata_300, PositiveLeptonHighEta_Pseudodata_300, WPositiveLeptonEtaAsymmetry_300);
 AFBFunction(NegativeLeptonLowEta_Pseudodata_300, NegativeLeptonHighEta_Pseudodata_300, WNegativeLeptonEtaAsymmetry_300);
 AFBFunction(WPlusMTEta_Pseudodata_300, WMinusMTEta_Pseudodata_300, WMTEtaAsymmetry_300);

 WLeptonEtaAsymmetry_300->Write();
 WLeptonPtAsymmetry_300->Write();
 NeutrinoPtAsymmetry_300->Write();
 WBosonMTAsymmetry_300->Write();
 WBosonXsecAsymmetry_300->Write();
 WPositiveLeptonEtaAsymmetry_300->Write();
 WNegativeLeptonEtaAsymmetry_300->Write();
 WMTEtaAsymmetry_300->Write();

 WLeptonEtaShapeAsymmetry = (TH1D *)PositiveLeptonEta_Pseudodata->Clone("WLeptonEtaShapeAsymmetry");
 WLeptonEtaShapeAsymmetry->Reset();
 WMTEtaShapeAsymmetry = (TH2D *)WPlusMTEta_Pseudodata->Clone("WMTEtaShapeAsymmetry");
 WMTEtaShapeAsymmetry->Reset();

 TH1D* PositiveLeptonEtaShape = (TH1D *)PositiveLeptonEta_Pseudodata->Clone("PositiveLeptonEtaShape");
 PositiveLeptonEtaShape->Scale(1.0 / PositiveLeptonEtaShape->Integral());
 TH1D* NegativeLeptonEtaShape = (TH1D *)NegativeLeptonEta_Pseudodata->Clone("NegativeLeptonEtaShape");
 NegativeLeptonEtaShape->Scale(1.0 / NegativeLeptonEtaShape->Integral());

 TH2D* WPlusMTEtaShape = (TH2D *)WPlusMTEta_Pseudodata->Clone("WPlusMTEtaShape");
 WPlusMTEtaShape->Scale(1.0 / WPlusMTEtaShape->Integral());
 TH2D* WMinusMTEtaShape = (TH2D *)WMinusMTEta_Pseudodata->Clone("WMinusMTEtaShape");
 WMinusMTEtaShape->Scale(1.0 / WMinusMTEtaShape->Integral());

 AFBFunction(PositiveLeptonEtaShape, NegativeLeptonEtaShape, WLeptonEtaShapeAsymmetry);
 AFBFunction(WPlusMTEtaShape, WMinusMTEtaShape, WMTEtaShapeAsymmetry);

 WLeptonEtaShapeAsymmetry->Write();
 WMTEtaShapeAsymmetry->Write();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 auto TH2DtoTH1D = [&](TH2D* h2){
   int nBin = h2->GetNbinsX() * h2->GetNbinsY();
   TH1D* h1 = new TH1D(h2->GetName() + (TString)"_Final", h2->GetName() + (TString)"_Final", nBin, 0, (double)nBin);
   
   int ibin = 1; 
   for(int ibinx = 1; ibinx <= h2->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= h2->GetNbinsY(); ibiny++){
       h1->SetBinContent(ibin, h2->GetBinContent(ibinx, ibiny));
       h1->SetBinError(ibin, h2->GetBinError(ibinx, ibiny));
       ibin++;
     }
   }
   
   return h1;
 };

 auto TH3DtoTH1D = [&](TH3D* h3){
   int nBin = h3->GetNbinsX() * h3->GetNbinsY() * h3->GetNbinsZ();
   TH1D* h1 = new TH1D(h3->GetName() + (TString)"_Final", h3->GetName() + (TString)"_Final", nBin, 0, (double)nBin);
   
   int ibin = 1; 
   for(int ibinx = 1; ibinx <= h3->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= h3->GetNbinsY(); ibiny++){
       for(int ibinz = 1; ibinz <= h3->GetNbinsZ(); ibinz++){
         h1->SetBinContent(ibin, h3->GetBinContent(ibinx, ibiny, ibinz));
         h1->SetBinError(ibin, h3->GetBinError(ibinx, ibiny, ibinz));
         ibin++;
       }
     }
   }
   
   return h1;
 };

 TH1D* Xsec_3D_CC_Final = TH3DtoTH1D(Xsec_3D_CC->at(0));
 TH1D* Xsec_3D_CF_Final = TH3DtoTH1D(Xsec_3D_CF->at(0));
 TH1D* Xsec_2D_CC_Final = TH2DtoTH1D(Xsec_2D_CC->at(0));
 TH1D* Xsec_2D_CF_Final = TH2DtoTH1D(Xsec_2D_CF->at(0));
 TH1D* ZMass_CosTheta_uu_Final = TH2DtoTH1D(ZMass_CosTheta_uu->at(0));
 TH1D* ZMass_CosTheta_dd_Final = TH2DtoTH1D(ZMass_CosTheta_dd->at(0));
 TH1D* ZMass_CosTheta_Final = TH2DtoTH1D(ZMass_CosTheta->at(0));
 TH1D* ATLAS_HMDY_Xsec_3D_Final = TH3DtoTH1D(ATLAS_HMDY_Xsec_3D->at(0));
 TH1D* WPlusMTEta_Final = TH2DtoTH1D(WPlusMTEta->at(0));
 TH1D* WMinusMTEta_Final = TH2DtoTH1D(WMinusMTEta->at(0));
 TH1D* WPlusMTEta_Above100_Final = TH2DtoTH1D(WPlusMTEta_Above100->at(0));
 TH1D* WMinusMTEta_Above100_Final = TH2DtoTH1D(WMinusMTEta_Above100->at(0));

 Xsec_3D_CC_Final->Write();
 Xsec_3D_CF_Final->Write();
 Xsec_2D_CC_Final->Write();
 Xsec_2D_CF_Final->Write();
 ZMass_CosTheta_uu_Final->Write();
 ZMass_CosTheta_dd_Final->Write();
 ZMass_CosTheta_Final->Write();
 ATLAS_HMDY_Xsec_3D_Final->Write();
 WPlusMTEta_Final->Write();
 WMinusMTEta_Final->Write();
 WPlusMTEta_Above100_Final->Write();
 WMinusMTEta_Above100_Final->Write();

 TH1D* Xsec_3D_CC_Final_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_3D_CC_Final);
 TH1D* Xsec_3D_CF_Final_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_3D_CF_Final);
 TH1D* Xsec_2D_CC_Final_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_2D_CC_Final);
 TH1D* Xsec_2D_CF_Final_Pseudodata = GenPseudodataNoFluc(3000000.0, Xsec_2D_CF_Final);
 TH1D* ZMass_CosTheta_uu_Final_Pseudodata = GenPseudodataNoFluc(3000000.0, ZMass_CosTheta_uu_Final);
 TH1D* ZMass_CosTheta_dd_Final_Pseudodata = GenPseudodataNoFluc(3000000.0, ZMass_CosTheta_dd_Final);
 TH1D* ZMass_CosTheta_Final_Pseudodata = GenPseudodataNoFluc(3000000.0, ZMass_CosTheta_Final);
 TH1D* ATLAS_HMDY_Xsec_3D_Final_Pseudodata = GenPseudodataNoFluc(140000.0, ATLAS_HMDY_Xsec_3D_Final);
 TH1D* WPlusMTEta_Final_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusMTEta_Final);
 TH1D* WMinusMTEta_Final_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusMTEta_Final);
 TH1D* WPlusMTEta_Above100_Final_Pseudodata = GenPseudodataNoFluc(3000000.0, WPlusMTEta_Above100_Final);
 TH1D* WMinusMTEta_Above100_Final_Pseudodata = GenPseudodataNoFluc(3000000.0, WMinusMTEta_Above100_Final);

 Xsec_3D_CC_Final_Pseudodata->Write();
 Xsec_3D_CF_Final_Pseudodata->Write();
 Xsec_2D_CC_Final_Pseudodata->Write();
 Xsec_2D_CF_Final_Pseudodata->Write();
 ZMass_CosTheta_uu_Final_Pseudodata->Write();
 ZMass_CosTheta_dd_Final_Pseudodata->Write();
 ZMass_CosTheta_Final_Pseudodata->Write();
 ATLAS_HMDY_Xsec_3D_Final_Pseudodata->Write();
 WPlusMTEta_Final_Pseudodata->Write();
 WMinusMTEta_Final_Pseudodata->Write();
 WPlusMTEta_Above100_Final_Pseudodata->Write();
 WMinusMTEta_Above100_Final_Pseudodata->Write();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ZMass_HighMass_Integral = new TH1D("ZMass_HighMass_Integral", "ZMass_HighMass_Integral", 5, 0.5, 5.5);
 for(int i = 1; i <= 5; i++){
   double Error = 0.0;
   double Integral = ZMass_HighMass_PerTeV->at(0)->IntegralAndError(i, ZMass_HighMass_PerTeV->at(0)->GetNbinsX(), Error);
   ZMass_HighMass_Integral->SetBinContent(i, Integral);
   ZMass_HighMass_Integral->SetBinError(i, Error);
 }
 ZMass_HighMass_Integral->Write();

 ZHighMass_CC_Integral = new TH1D("ZHighMass_CC_Integral", "ZHighMass_CC_Integral", 5, 0.5, 5.5);
 for(int i = 1; i <= 5; i++){
   double Error = 0.0;
   double Integral = ZHighMass_CC_PerTeV->at(0)->IntegralAndError(i, ZHighMass_CC_PerTeV->at(0)->GetNbinsX(), Error);
   ZHighMass_CC_Integral->SetBinContent(i, Integral);
   ZHighMass_CC_Integral->SetBinError(i, Error);
 }
 ZHighMass_CC_Integral->Write();

 ZHighMass_CF_Integral = new TH1D("ZHighMass_CF_Integral", "ZHighMass_CF_Integral", 5, 0.5, 5.5);
 for(int i = 1; i <= 5; i++){
   double Error = 0.0;
   double Integral = ZHighMass_CF_PerTeV->at(0)->IntegralAndError(i, ZHighMass_CF_PerTeV->at(0)->GetNbinsX(), Error);
   ZHighMass_CF_Integral->SetBinContent(i, Integral);
   ZHighMass_CF_Integral->SetBinError(i, Error);
 }
 ZHighMass_CF_Integral->Write();

 WHighMassMT_Integral = new TH1D("WHighMassMT_Integral", "WHighMassMT_Integral", 5, 0.5, 5.5);
 for(int i = 1; i <= 5; i++){
   double Error = 0.0;
   double Integral = WHighMassMT_PerTeV->at(0)->IntegralAndError(i, WHighMassMT_PerTeV->at(0)->GetNbinsX(), Error);
   WHighMassMT_Integral->SetBinContent(i, Integral);
   WHighMassMT_Integral->SetBinError(i, Error);
 }
 WHighMassMT_Integral->Write();

 WPlusHighMassMT_Integral = new TH1D("WPlusHighMassMT_Integral", "WPlusHighMassMT_Integral", 5, 0.5, 5.5);
 for(int i = 1; i <= 5; i++){
   double Error = 0.0;
   double Integral = WPlusHighMassMT_PerTeV->at(0)->IntegralAndError(i, WPlusHighMassMT_PerTeV->at(0)->GetNbinsX(), Error);
   WPlusHighMassMT_Integral->SetBinContent(i, Integral);
   WPlusHighMassMT_Integral->SetBinError(i, Error);
 }
 WPlusHighMassMT_Integral->Write();

 WMinusHighMassMT_Integral = new TH1D("WMinusHighMassMT_Integral", "WMinusHighMassMT_Integral", 5, 0.5, 5.5);
 for(int i = 1; i <= 5; i++){
   double Error = 0.0;
   double Integral = WMinusHighMassMT_PerTeV->at(0)->IntegralAndError(i, WMinusHighMassMT_PerTeV->at(0)->GetNbinsX(), Error);
   WMinusHighMassMT_Integral->SetBinContent(i, Integral);
   WMinusHighMassMT_Integral->SetBinError(i, Error);
 }
 WMinusHighMassMT_Integral->Write();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 WPositiveLeptonEtaMean = new TH1D("WPositiveLeptonEtaMean", "WPositiveLeptonEtaMean", 1, 0, 1);
 WPositiveLeptonEtaMean->SetBinContent(1, PositiveLeptonEta_Pseudodata->GetMean());
 WPositiveLeptonEtaMean->SetBinError(1, PositiveLeptonEta_Pseudodata->GetMeanError());
 WNegativeLeptonEtaMean = new TH1D("WNegativeLeptonEtaMean", "WNegativeLeptonEtaMean", 1, 0, 1);
 WNegativeLeptonEtaMean->SetBinContent(1, NegativeLeptonEta_Pseudodata->GetMean());
 WNegativeLeptonEtaMean->SetBinError(1, NegativeLeptonEta_Pseudodata->GetMeanError());

 LeptonEtaMeanRatio = (TH1D *)WPositiveLeptonEtaMean->Clone("LeptonEtaMeanRatio");
 LeptonEtaMeanRatio->Divide(WNegativeLeptonEtaMean);

 WPositiveLeptonEtaMean->Write();
 WNegativeLeptonEtaMean->Write();
 LeptonEtaMeanRatio->Write();

 WPositiveLeptonEtaMean_300 = new TH1D("WPositiveLeptonEtaMean_300", "WPositiveLeptonEtaMean_300", 1, 0, 1);
 WPositiveLeptonEtaMean_300->SetBinContent(1, PositiveLeptonEta_Pseudodata_300->GetMean());
 WPositiveLeptonEtaMean_300->SetBinError(1, PositiveLeptonEta_Pseudodata_300->GetMeanError());
 WNegativeLeptonEtaMean_300 = new TH1D("WNegativeLeptonEtaMean_300", "WNegativeLeptonEtaMean_300", 1, 0, 1);
 WNegativeLeptonEtaMean_300->SetBinContent(1, NegativeLeptonEta_Pseudodata_300->GetMean());
 WNegativeLeptonEtaMean_300->SetBinError(1, NegativeLeptonEta_Pseudodata_300->GetMeanError());
 
 LeptonEtaMeanRatio_300 = (TH1D *)WPositiveLeptonEtaMean_300->Clone("LeptonEtaMeanRatio_300");
 LeptonEtaMeanRatio_300->Divide(WNegativeLeptonEtaMean_300);

 WPositiveLeptonEtaMean_300->Write();
 WNegativeLeptonEtaMean_300->Write();
 LeptonEtaMeanRatio_300->Write();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 WPlusAFB = (TH1D *)WPlusForwardEta_Pseudodata->Clone("WPlusAFB");
 WPlusAFB->Reset();
 AFBFunction(WPlusForwardEta_Pseudodata, WPlusBackwardEta_Pseudodata, WPlusAFB);

 WMinusAFB = (TH1D *)WMinusForwardEta_Pseudodata->Clone("WMinusAFB");
 WMinusAFB->Reset();
 AFBFunction(WMinusForwardEta_Pseudodata, WMinusBackwardEta_Pseudodata, WMinusAFB);

 WPlusAFB->Write();
 WMinusAFB->Write();

 WPlusRapidityAverage = (TH1D *)WPlusAverageRapidity->at(0)->Clone("WPlusRapidityAverage");
 WMinusRapidityAverage = (TH1D *)WMinusAverageRapidity->at(0)->Clone("WMinusRapidityAverage");
 for(int ibin = 1; ibin <= WPlusRapidityAverage->GetNbinsX(); ibin++){
   WPlusRapidityAverage->SetBinContent(ibin, WPlusRapidityAverage->GetBinContent(ibin) / (WPlusForwardEta->at(0)->GetBinContent(ibin) + WPlusBackwardEta->at(0)->GetBinContent(ibin)));
   WMinusRapidityAverage->SetBinContent(ibin, WMinusRapidityAverage->GetBinContent(ibin) / (WMinusForwardEta->at(0)->GetBinContent(ibin) + WMinusBackwardEta->at(0)->GetBinContent(ibin)));
 }
 WPlusRapidityAverage->Write();
 WMinusRapidityAverage->Write();

 WPlusAFB_ExpPz = (TH1D *)WPlusForwardEta_ExpPz_Pseudodata->Clone("WPlusAFB_ExpPz");
 WPlusAFB_ExpPz->Reset();
 AFBFunction(WPlusForwardEta_ExpPz_Pseudodata, WPlusBackwardEta_ExpPz_Pseudodata, WPlusAFB_ExpPz);

 WMinusAFB_ExpPz = (TH1D *)WMinusForwardEta_ExpPz_Pseudodata->Clone("WMinusAFB_ExpPz");
 WMinusAFB_ExpPz->Reset();
 AFBFunction(WMinusForwardEta_ExpPz_Pseudodata, WMinusBackwardEta_ExpPz_Pseudodata, WMinusAFB_ExpPz);

 WPlusAFB_ExpPz->Write();
 WMinusAFB_ExpPz->Write();

 WPlusAFB_ExpEta = (TH1D *)WPlusForwardEta_ExpEta_Pseudodata->Clone("WPlusAFB_ExpEta");
 WPlusAFB_ExpEta->Reset();
 AFBFunction(WPlusForwardEta_ExpEta_Pseudodata, WPlusBackwardEta_ExpEta_Pseudodata, WPlusAFB_ExpEta);

 WMinusAFB_ExpEta = (TH1D *)WMinusForwardEta_ExpEta_Pseudodata->Clone("WMinusAFB_ExpEta");
 WMinusAFB_ExpEta->Reset();
 AFBFunction(WMinusForwardEta_ExpEta_Pseudodata, WMinusBackwardEta_ExpEta_Pseudodata, WMinusAFB_ExpEta);

 WPlusAFB_ExpEta->Write();
 WMinusAFB_ExpEta->Write();

 RHIC_WRatio = (TH1D *)RHIC_WPlus->at(0)->Clone("RHIC_WRatio");
 RHIC_WRatio->Divide(RHIC_WMinus->at(0));
 RHIC_WRatio->Write();

 RHIC_WRatio_Data = (TH1D *)RHIC_WPlus->at(0)->Clone("RHIC_WRatio_Data");
 RHIC_WRatio_Data->Reset();
 RHIC_WRatio_Data->SetBinContent(1, 1.9); RHIC_WRatio_Data->SetBinError(1, sqrt(pow(0.2, 2) + pow(0.1, 2)));
 RHIC_WRatio_Data->SetBinContent(2, 3.8); RHIC_WRatio_Data->SetBinError(2, sqrt(pow(0.3, 2) + pow(0.1, 2)));
 RHIC_WRatio_Data->SetBinContent(3, 4.6); RHIC_WRatio_Data->SetBinError(3, sqrt(pow(0.3, 2) + pow(0.1, 2)));
 RHIC_WRatio_Data->SetBinContent(4, 5.9); RHIC_WRatio_Data->SetBinError(4, sqrt(pow(0.4, 2) + pow(0.2, 2)));
 RHIC_WRatio_Data->SetBinContent(5, 6.7); RHIC_WRatio_Data->SetBinError(5, sqrt(pow(0.5, 2) + pow(0.3, 2)));
 RHIC_WRatio_Data->SetBinContent(6, 5.4); RHIC_WRatio_Data->SetBinError(6, sqrt(pow(0.4, 2) + pow(0.3, 2)));
 RHIC_WRatio_Data->SetBinContent(7, 3.3); RHIC_WRatio_Data->SetBinError(7, sqrt(pow(0.2, 2) + pow(0.1, 2)));
 RHIC_WRatio_Data->SetBinContent(8, 2.0); RHIC_WRatio_Data->SetBinError(8, sqrt(pow(0.2, 2) + pow(0.1, 2)));
 RHIC_WRatio_Data->SetBinContent(9, 0.9); RHIC_WRatio_Data->SetBinError(9, sqrt(pow(0.1, 2) + pow(0.1, 2)));
 RHIC_WRatio_Data->Write();
}

void HistsResBosHighMassZ::InitialSysName()
{

}
