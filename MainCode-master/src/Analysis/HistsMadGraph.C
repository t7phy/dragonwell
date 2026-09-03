#include "Analysis/HistsMadGraph.h"

using namespace std;

void HistsMadGraph::bookHists(int TotalThread)
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

 vector<double> v_FullCrossSectionBinning = Logspace(66.0, 5000.0, 51, 10.0);
 int FullCrossSectionBin = 50;
 double FullCrossSectionBinning[51];
 for(int i = 0; i < v_FullCrossSectionBinning.size(); i++){
   FullCrossSectionBinning[i] = v_FullCrossSectionBinning.at(i);
 }

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


 int ATLAS8TeVZPtBin2 = 20;
 double ATLAS8TeVZPtBinning2[21] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 13.0, 16.0, 20.0, 25.0, 30.0, 37.0, 45.0, 55.0, 65.0, 75.0, 85.0,
                                105.0, 150.0, 200.0, 900.0};

 int ATLAS8TeVZPtBin3 = 43;
 double ATLAS8TeVZPtBinning3[44] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.5, 25.0, 27.5, 30.0, 33.0,
                                 36.0, 39.0, 42.0, 45.0, 48.0, 51.0, 54.0, 57.0, 61.0, 65.0, 70.0, 75.0, 80.0, 85.0, 95.0, 105.0,
                                 125.0, 150.0, 175.0, 200.0, 250.0, 300.0, 350.0, 400.0, 470.0, 550.0, 650.0, 900.0};

 int CrossSectionBin = 6;
 double CrossSectionBinning[7] = {1000.0, 1300.0, 1800.0, 2500.0, 3200.0, 4000.0, 5000.0};

 this->TotalThread = TotalThread;

   //////////////////////////
   //  Z Event Histograms  //
   //////////////////////////

   Book3DHist(Xsec_3D_CC, "Xsec_3D_CC", "Xsec_3D_CC", MassBin, MassBinning, ZYCCBin, ZYCCBinning, CosThetaBin, CosThetaBinning);
   Book3DHist(Xsec_3D_CF, "Xsec_3D_CF", "Xsec_3D_CF", MassBin, MassBinning, ZYCFBin, ZYCFBinning, CosThetaBin, CosThetaBinning);

   Book2DHist(Xsec_2D_CC, "Xsec_2D_CC", "Xsec_2D_CC", MassBin, MassBinning, ZYCCBin, ZYCCBinning);
   Book2DHist(Xsec_2D_CF, "Xsec_2D_CF", "Xsec_2D_CF", MassBin, MassBinning, ZYCFBin, ZYCFBinning);

   BookHist(Xsec_1D_CC, "Xsec_1D_CC", "Xsec_1D_CC", MassBin, MassBinning);
   BookHist(Xsec_1D_CF, "Xsec_1D_CF", "Xsec_1D_CF", MassBin, MassBinning);

   vector<double> MassBin2 = {40.0, 66.0, 116.0, 250.0, 400.0, 600.0, 1000.0};
   vector<double> CosThetaBin2 = {-1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
   Book2DHist(ZMass_CosTheta_uu, "ZMass_CosTheta_uu", "ZMass_CosTheta_uu", MassBin2.size() - 1, &MassBin2[0], CosThetaBin2.size() - 1, &CosThetaBin2[0]);
   Book2DHist(ZMass_CosTheta_dd, "ZMass_CosTheta_dd", "ZMass_CosTheta_dd", MassBin2.size() - 1, &MassBin2[0], CosThetaBin2.size() - 1, &CosThetaBin2[0]);
   Book2DHist(ZMass_CosTheta, "ZMass_CosTheta", "ZMass_CosTheta", MassBin2.size() - 1, &MassBin2[0], CosThetaBin2.size() - 1, &CosThetaBin2[0]);

   BookHist(ZMass_HighMass, "ZMass_HighMass", "ZMass_HighMass", HighMassBin, HighMassBinning);
   BookHist(ZMass_HighMass_PerTeV, "ZMass_HighMass_PerTeV", "ZMass_HighMass_PerTeV", 6, 1000.0, 7000.0);

   BookHist(ZMass_FullMass, "ZMass_FullMass", "ZMass_FullMass", FullMassBinning.size() - 1, &FullMassBinning[0]);

   //////////////////////////
   //  W Event Histograms  //
   //////////////////////////

   BookHist(PositiveLeptonEta, "PositiveLeptonEta", "PositiveLeptonEta", 20, 0, 2.4);
   BookHist(NegativeLeptonEta, "NegativeLeptonEta", "NegativeLeptonEta", 20, 0, 2.4);

   Book2DHist(WPlusMTEta, "WPlusMTEta", "WPlusMTEta", 20, 60, 100, 10, 0, 2.4);
   Book2DHist(WMinusMTEta, "WMinusMTEta", "WMinusMTEta", 20, 60, 100, 10, 0, 2.4);
   Book2DHist(WPlusMTEta_Above100, "WPlusMTEta_Above100", "WPlusMTEta_Above100", 5, 100, 500, 10, 0, 2.4);
   Book2DHist(WMinusMTEta_Above100, "WMinusMTEta_Above100", "WMinusMTEta_Above100", 5, 100, 500, 10, 0, 2.4);

   BookHist(WPlusMT, "WPlusMT", "WPlusMT", 40, 60, 100);
   BookHist(WMinusMT, "WMinusMT", "WMinusMT", 40, 60, 100);
   BookHist(WPlusMT_Above100, "WPlusMT_Above100", "WPlusMT_Above100", 5, 100, 500);
   BookHist(WMinusMT_Above100, "WMinusMT_Above100", "WMinusMT_Above100", 5, 100, 500);

   BookHist(WPlusHighMassMT, "WPlusHighMassMT", "WPlusHighMassMT", HighMassBin, HighMassBinning);
   BookHist(WMinusHighMassMT, "WMinusHighMassMT", "WMinusHighMassMT", HighMassBin, HighMassBinning);
   BookHist(WPlusHighMassMT_PerTeV, "WPlusHighMassMT_PerTeV", "WPlusHighMassMT_PerTeV", 6, 1000.0, 7000.0);
   BookHist(WMinusHighMassMT_PerTeV, "WMinusHighMassMT_PerTeV", "WMinusHighMassMT_PerTeV", 6, 1000.0, 7000.0);

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

 BookHist(ZMass, "ZMass", "ZMass", 20, 66, 116);
 BookHist(ZRapidity, "ZRapidity", "ZRapidity", 20, -5, 5);
 BookHist(ZPt, "ZPt", "ZPt", 50, 0, 100);
 BookHist(LeptonPt, "LeptonPt", "LeptonPt", 30, 0, 60);
 BookHist(LeptonEta, "LeptonEta", "LeptonEta", 20, -5, 5);
 BookHist(FZMass, "FZMass", "FZMass", FullCrossSectionBin, FullCrossSectionBinning);
 BookHist(BZMass, "BZMass", "BZMass", FullCrossSectionBin, FullCrossSectionBinning);

 BookHist(ZHighMass, "ZHighMass", "ZHighMass", HighMassBin, HighMassBinning);
 BookHist(FZMass_HighMass, "FZMass_HighMass", "FZMass_HighMass", HighMassBin, HighMassBinning);
 BookHist(BZMass_HighMass, "BZMass_HighMass", "BZMass_HighMass", HighMassBin, HighMassBinning);

 BookHist(CrossSection, "CrossSection", "CrossSection", CrossSectionBin, CrossSectionBinning);
 BookHist(CrossSectionF, "CrossSectionF", "CrossSectionF", CrossSectionBin, CrossSectionBinning);
 BookHist(CrossSectionB, "CrossSectionB", "CrossSectionB", CrossSectionBin, CrossSectionBinning);
 BookHist(FullCrossSection, "FullCrossSection", "FullCrossSection", FullCrossSectionBin, FullCrossSectionBinning);

 vector<double> E245_LHCb7TeV_Z_binning = {2.0, 2.125, 2.25, 2.375, 2.5, 2.625, 2.75, 2.875, 3.0, 3.125, 3.25, 3.375, 3.5, 3.625, 3.75, 3.875, 4.0, 4.25};
 vector<double> E245_LHCb7TeV_W_binning = {2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 4.0, 4.5};
 vector<double> E246_LHCb8TeV_Z_binning = {2.0, 2.125, 2.25, 2.375, 2.5, 2.625, 2.75, 2.875, 3.0, 3.125, 3.25, 3.375, 3.5, 3.625, 3.75, 3.875, 4.0, 4.25};
 vector<double> E248_ATLAS7TeV_W_binning = {0.00, 0.21, 0.42, 0.63, 0.84, 1.05, 1.37, 1.52, 1.74, 1.95, 2.18, 2.50};
 vector<double> E268_ATLAS7TeV_Z_binning = {0.00, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.6};
 vector<double> E268_ATLAS7TeV_W_binning = {0.00, 0.21, 0.42, 0.63, 0.84, 1.05, 1.37, 1.52, 1.74, 1.95, 2.18, 2.50};
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

 BookHist(E268_ATLAS7TeV_Z, "E268_ATLAS7TeV_Z", "E268_ATLAS7TeV_Z", E268_ATLAS7TeV_Z_binning.size() - 1, &E268_ATLAS7TeV_Z_binning[0]);
 BookHist(E268_ATLAS7TeV_WPlus, "E268_ATLAS7TeV_WPlus", "E268_ATLAS7TeV_WPlus", E268_ATLAS7TeV_W_binning.size() - 1, &E268_ATLAS7TeV_W_binning[0]);
 BookHist(E268_ATLAS7TeV_WMinus, "E268_ATLAS7TeV_WMinus", "E268_ATLAS7TeV_WMinus", E268_ATLAS7TeV_W_binning.size() - 1, &E268_ATLAS7TeV_W_binning[0]);

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

}

void HistsMadGraph::outputInformation()
{
 hf->cd();

///////////////////////////////////////////////////////////////////////////////////////////
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

 TH1D* ATLAS_Mll_HighMass_costheta_NewBinning = new TH1D("ATLAS_Mll_HighMass_costheta_NewBinning", "ATLAS_Mll_HighMass_costheta_NewBinning", 49, 0, 49);

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

 TH1D* ATLAS_Mll_HighMass_DilRapidity_NewBinning = new TH1D("ATLAS_Mll_HighMass_DilRapidity_NewBinning", "ATLAS_Mll_HighMass_DilRapidity_NewBinning", 57, 0, 57);

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

 ATLAS_Mll_HighMass_costheta_NewBinning->Write();
 ATLAS_Mll_HighMass_DilRapidity_NewBinning->Write();

 TH1D* ZMass_HighMass_Integral = new TH1D("ZMass_HighMass_Integral", "ZMass_HighMass_Integral", 5, 0.5, 5.5);
 for(int i = 1; i <= 5; i++){
   double Error = 0.0;
   double Integral = ZMass_HighMass_PerTeV->at(0)->IntegralAndError(i, ZMass_HighMass_PerTeV->at(0)->GetNbinsX(), Error);
   ZMass_HighMass_Integral->SetBinContent(i, Integral);
   ZMass_HighMass_Integral->SetBinError(i, Error);
 }
 ZMass_HighMass_Integral->Write();

 TH1D* WPlusHighMassMT_Integral = new TH1D("WPlusHighMassMT_Integral", "WPlusHighMassMT_Integral", 5, 0.5, 5.5);
 for(int i = 1; i <= 5; i++){
   double Error = 0.0;
   double Integral = WPlusHighMassMT_PerTeV->at(0)->IntegralAndError(i, WPlusHighMassMT_PerTeV->at(0)->GetNbinsX(), Error);
   WPlusHighMassMT_Integral->SetBinContent(i, Integral);
   WPlusHighMassMT_Integral->SetBinError(i, Error);
 }
 WPlusHighMassMT_Integral->Write();

 TH1D* WMinusHighMassMT_Integral = new TH1D("WMinusHighMassMT_Integral", "WMinusHighMassMT_Integral", 5, 0.5, 5.5);
 for(int i = 1; i <= 5; i++){
   double Error = 0.0;
   double Integral = WMinusHighMassMT_PerTeV->at(0)->IntegralAndError(i, WMinusHighMassMT_PerTeV->at(0)->GetNbinsX(), Error);
   WMinusHighMassMT_Integral->SetBinContent(i, Integral);
   WMinusHighMassMT_Integral->SetBinError(i, Error);
 }
 WMinusHighMassMT_Integral->Write();

///////////////////////////////////////////////////////////////////////////////////////////

 ConstructCTEQData();

 FZMass_Pseudodata = GenPseudodataNoFluc(3000000.0, FZMass->at(0));
 FZMass_Pseudodata->Write();
 BZMass_Pseudodata = GenPseudodataNoFluc(3000000.0, BZMass->at(0));
 BZMass_Pseudodata->Write();

 AFB_ZMass = (TH1D *)FZMass_Pseudodata->Clone("AFB_ZMass");
 AFB_ZMass->Reset();
 AFBFunction(FZMass_Pseudodata, BZMass_Pseudodata, AFB_ZMass);
 AFB_ZMass->Write();

 AFB_ZHighMass = (TH1D *)FZMass_HighMass->at(0)->Clone("AFB_ZHighMass");
 AFB_ZHighMass->Reset();
 AFBFunction(FZMass_HighMass->at(0), BZMass_HighMass->at(0), AFB_ZHighMass);
 AFB_ZHighMass->Write();

 CrossSection_Pseudodata = GenPseudodataNoFluc(3000000.0, CrossSection->at(0));
 CrossSection_Pseudodata->Write();

 CrossSectionF_Pseudodata = GenPseudodataNoFluc(3000000.0, CrossSectionF->at(0));
 CrossSectionF_Pseudodata->Write();

 CrossSectionB_Pseudodata = GenPseudodataNoFluc(3000000.0, CrossSectionB->at(0));
 CrossSectionB_Pseudodata->Write();

 CrossSectionAFB = (TH1D *)CrossSectionF_Pseudodata->Clone("CrossSectionAFB");
 CrossSectionAFB->Reset();
 AFBFunction(CrossSectionF_Pseudodata, CrossSectionB_Pseudodata, CrossSectionAFB);
 CrossSectionAFB->Write();

 FullCrossSection_Pseudodata = GenPseudodataNoFluc(3000000.0, FullCrossSection->at(0));
 FullCrossSection_Pseudodata->Write();

}

void HistsMadGraph::ConstructCTEQData()
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

 // E268
 TH1D* E268_ATLAS7TeV_Z_Final;
 TH1D* E268_ATLAS7TeV_WPlus_Final;
 TH1D* E268_ATLAS7TeV_WMinus_Final;

 HistDivideBinWidth(E268_ATLAS7TeV_Z->at(0), E268_ATLAS7TeV_Z_Final);
 HistDivideBinWidth(E268_ATLAS7TeV_WPlus->at(0), E268_ATLAS7TeV_WPlus_Final);
 HistDivideBinWidth(E268_ATLAS7TeV_WMinus->at(0), E268_ATLAS7TeV_WMinus_Final);

 TH1D* E268_Wasymmetry = (TH1D *)E268_ATLAS7TeV_WPlus_Final->Clone("E268_Wasymmetry");
 AFBFunction(E268_ATLAS7TeV_WPlus_Final, E268_ATLAS7TeV_WMinus_Final, E268_Wasymmetry);

 nBin = GetNBin(vector<TH1D *>{E268_ATLAS7TeV_WPlus_Final, E268_ATLAS7TeV_Z_Final, E268_ATLAS7TeV_WMinus_Final, E268_Wasymmetry});
 m_theory = PushTheory(vector<TH1D *>{E268_ATLAS7TeV_WPlus_Final, E268_ATLAS7TeV_Z_Final, E268_ATLAS7TeV_WMinus_Final, E268_Wasymmetry});
 SaveTheory(E268_Final, "E268_Final", nBin, m_theory);
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

void HistsMadGraph::InitialSysName()
{

}

