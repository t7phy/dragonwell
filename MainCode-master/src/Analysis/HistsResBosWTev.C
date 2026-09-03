#include "Analysis/HistsResBosWTev.h"

using namespace std;

void HistsResBosWTev::bookHists(int TotalThread)
{
 double rangeZPt[24] = {0,2.5,5,8,11.4,14.9,18.5,22,25.5,29,32.6,36.4,40.4,44.9,50.2,56.4,63.9,73.4,85.4,105,132,173,253,600};
 double rangeEtaAbs[5] = {0, 1, 2, 3, 5};
 double rangeMET[6] = {25, 35, 45, 55, 65, 100};
 double rangeWPt[6] = {0, 2, 4, 6, 8, 10};
 double rangeWE[6] = {0, 200, 400, 600, 800, 1000};

 double rangeEta1[12] = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.45, 1.7, 1.9, 2.1, 2.5};//w225
 double rangeEta2[12] = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.45, 1.7, 1.9, 2.2, 2.5};//w227
 double rangeEta3[10] = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 2.0};//w234
 double rangeEta4[14] = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.6, 1.8, 2.0, 2.2, 2.4, 2.7, 3.2};//w281
// double rangeWPt[42] = {0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5,
//                      10, 10.5, 11, 11.5, 12, 12.5, 13, 13.5, 14, 14.5, 15, 15.5, 16, 16.5, 17, 17.5, 18, 18.5, 19, 19.5, 20, 20.5};

 this->TotalThread = TotalThread;

 BookHist(LeptonEta_w225, "LeptonEta_w225", "LeptonEta_w225", 11, rangeEta1);
 BookHist(AntiLeptonEta_w225, "AntiLeptonEta_w225", "AntiLeptonEta_w225", 11, rangeEta1);

 BookHist(LeptonEta_w227, "LeptonEta_w227", "LeptonEta_w227", 11, rangeEta2);
 BookHist(AntiLeptonEta_w227, "AntiLeptonEta_w227", "AntiLeptonEta_w227", 11, rangeEta2);

 BookHist(LeptonEta_w234, "LeptonEta_w234", "LeptonEta_w234", 9, rangeEta3);
 BookHist(AntiLeptonEta_w234, "AntiLeptonEta_w234", "AntiLeptonEta_w234", 9, rangeEta3);

 BookHist(LeptonEta_w281, "LeptonEta_w281", "LeptonEta_w281", 13, rangeEta4);
 BookHist(AntiLeptonEta_w281, "AntiLeptonEta_w281", "AntiLeptonEta_w281", 13, rangeEta4);

 BookHist(WPlusRapidity, "WPlusRapidity", "WPlusRapidity", 20, -5.0, 5.0);
 BookHist(WPlusPt, "WPlusPt", "WPlusPt", 100, 0.0, 100.0);

 BookHist(WMinusRapidity, "WMinusRapidity", "WMinusRapidity", 20, -5.0, 5.0);
 BookHist(WMinusPt, "WMinusPt", "WMinusPt", 100, 0.0, 100.0);

 BookHist(LeptonEta, "LeptonEta", "LeptonEta", 20, -5.0, 5.0);
 BookHist(AntiLeptonEta, "AntiLeptonEta", "AntiLeptonEta", 20, -5.0, 5.0);

 BookHist(LeptonPt, "LeptonPt", "LeptonPt", 50, 10, 60);

 BookHist(MtW_CDF, "MtW_CDF", "MtW_CDF", 50, 65, 90);
 BookHist(LeptonPt_CDF, "LeptonPt_CDF", "LeptonPt_CDF", 64, 32, 48);
 BookHist(NuPt_CDF, "NuPt_CDF", "NuPt_CDF", 64, 32, 48);
 BookHist(LeptonPt_WPlus_CDF, "LeptonPt_WPlus_CDF", "LeptonPt_WPlus_CDF", 64, 32, 48);
 BookHist(NuPt_WPlus_CDF, "NuPt_WPlus_CDF", "NuPt_WPlus_CDF", 64, 32, 48);
 BookHist(LeptonPt_WMinus_CDF, "LeptonPt_WMinus_CDF", "LeptonPt_WMinus_CDF", 64, 32, 48);
 BookHist(NuPt_WMinus_CDF, "NuPt_WMinus_CDF", "NuPt_WMinus_CDF", 64, 32, 48);
 BookHist(DeltaPhi_CDF, "DeltaPhi_CDF", "DeltaPhi_CDF", 30, 2.5, 3.14);
 BookHist(WPt_CDF, "WPt_CDF", "WPt_CDF", 30, 0, 15);
 BookHist(ZPt_CDF, "ZPt_CDF", "ZPt_CDF", 30, 0, 30);
 BookHist(WPt_CDF_FineBin, "WPt_CDF_FineBin", "WPt_CDF_FineBin", 30, 0, 15);
 BookHist(ZPt_CDF_FineBin, "ZPt_CDF_FineBin", "ZPt_CDF_FineBin", 30, 0, 15);
 BookHist(WPt_CDF_ScaleUp, "WPt_CDF_ScaleUp", "WPt_CDF_ScaleUp", 30, 0, 15);
 BookHist(WPt_CDF_ScaleDown, "WPt_CDF_ScaleDown", "WPt_CDF_ScaleDown", 30, 0, 15);
 BookHist(WPt_CDF_ScaleVari, "WPt_CDF_ScaleVari", "WPt_CDF_ScaleVari", 30, 0, 15);

 BookHist(MtW_CDF_Smear, "MtW_CDF_Smear", "MtW_CDF_Smear", 50, 65, 90);
 BookHist(LeptonPt_CDF_Smear, "LeptonPt_CDF_Smear", "LeptonPt_CDF_Smear", 64, 32, 48);
 BookHist(NuPt_CDF_Smear, "NuPt_CDF_Smear", "NuPt_CDF_Smear", 64, 32, 48);
 BookHist(DeltaPhi_CDF_Smear, "DeltaPhi_CDF_Smear", "DeltaPhi_CDF_Smear", 30, 2.5, 3.14);
 BookHist(WPt_CDF_Smear, "WPt_CDF_Smear", "WPt_CDF_Smear", 30, 0, 15);
 BookHist(ZPt_CDF_Smear, "ZPt_CDF_Smear", "ZPt_CDF_Smear", 30, 0, 30);

 BookHist(MtW_Inclusive, "MtW_Inclusive", "MtW_Inclusive", 50, 65, 90);
 BookHist(LeptonPt_Inclusive, "LeptonPt_Inclusive", "LeptonPt_Inclusive", 64, 32, 48);
 BookHist(NuPt_Inclusive, "NuPt_Inclusive", "NuPt_Inclusive", 64, 32, 48);
 BookHist(LeptonPt_WPlus_Inclusive, "LeptonPt_WPlus_Inclusive", "LeptonPt_WPlus_Inclusive", 64, 32, 48);
 BookHist(NuPt_WPlus_Inclusive, "NuPt_WPlus_Inclusive", "NuPt_WPlus_Inclusive", 64, 32, 48);
 BookHist(LeptonPt_WMinus_Inclusive, "LeptonPt_WMinus_Inclusive", "LeptonPt_WMinus_Inclusive", 64, 32, 48);
 BookHist(NuPt_WMinus_Inclusive, "NuPt_WMinus_Inclusive", "NuPt_WMinus_Inclusive", 64, 32, 48);
 BookHist(LeptonEta_WPlus_Inclusive, "LeptonEta_WPlus_Inclusive", "LeptonEta_WPlus_Inclusive", 40, -5, 5);
 BookHist(NuEta_WPlus_Inclusive, "NuEta_WPlus_Inclusive", "NuEta_WPlus_Inclusive", 40, -5, 5);
 BookHist(LeptonEta_WMinus_Inclusive, "LeptonEta_WMinus_Inclusive", "LeptonEta_WMinus_Inclusive", 40, -5, 5);
 BookHist(NuEta_WMinus_Inclusive, "NuEta_WMinus_Inclusive", "NuEta_WMinus_Inclusive", 40, -5, 5);
 BookHist(DeltaPhi_Inclusive, "DeltaPhi_Inclusive", "DeltaPhi_Inclusive", 30, 2.5, 3.14);
 BookHist(WPt_Inclusive, "WPt_Inclusive", "WPt_Inclusive", 60, 0, 30);
 BookHist(ZPt_Inclusive, "ZPt_Inclusive", "ZPt_Inclusive", 30, 0, 30);
 BookHist(WPt_Inclusive_LargeRange, "WPt_Inclusive_LargeRange", "WPt_Inclusive_LargeRange", 200, 0, 100);
 BookHist(ZPt_Inclusive_LargeRange, "ZPt_Inclusive_LargeRange", "ZPt_Inclusive_LargeRange", 200, 0, 100);

 BookHist(MtW_EventCount, "MtW_EventCount", "MtW_EventCount", 50, 65, 90);
 BookHist(MtW_Smear_EventCount, "MtW_Smear_EventCount", "MtW_Smear_EventCount", 50, 65, 90);

 BookHist(MtW_new_CDF, "MtW_new_CDF", "MtW_new_CDF", 50, 65, 90);
 BookHist(MtW_new_CDF_Smear, "MtW_new_CDF_Smear", "MtW_new_CDF_Smear", 50, 65, 90);

 BookMultiWeightHist(LeptonPt_LHC_Low_multiweight, 21, "LeptonPt_LHC_Low", "LeptonPt_LHC_Low", 1, LeptonPtMin, LeptonPtMiddle);
 BookMultiWeightHist(LeptonPt_LHC_High_multiweight, 21, "LeptonPt_LHC_High", "LeptonPt_LHC_High", 1, LeptonPtMiddle, LeptonPtMax);
 BookMultiWeightHist(LeptonPt_LowQT_LHC_Low_multiweight, 21, "LeptonPt_LowQT_LHC_Low", "LeptonPt_LowQT_LHC_Low", 1, LeptonPtMin, LeptonPtMiddle);
 BookMultiWeightHist(LeptonPt_LowQT_LHC_High_multiweight, 21, "LeptonPt_LowQT_LHC_High", "LeptonPt_LowQT_LHC_High", 1, LeptonPtMiddle, LeptonPtMax);
 BookHist(LeptonPt_LHC, "LeptonPt_LHC", "LeptonPt_LHC", 22, 33, 44);
 BookHist(LeptonPt_LHC_WPlus, "LeptonPt_LHC_WPlus", "LeptonPt_LHC_WPlus", 22, 33, 44);
 BookHist(LeptonPt_LHC_WMinus, "LeptonPt_LHC_WMinus", "LeptonPt_LHC_WMinus", 22, 33, 44);
 BookHist(LeptonPt_LHC_Low, "LeptonPt_LHC_Low", "LeptonPt_LHC_Low", 1, LeptonPtMin, LeptonPtMiddle);
 BookHist(LeptonPt_LHC_High, "LeptonPt_LHC_High", "LeptonPt_LHC_High", 1, LeptonPtMiddle, LeptonPtMax);

 BookHist(LeptonPt_LowQT_LHC, "LeptonPt_LowQT_LHC", "LeptonPt_LowQT_LHC", 20, 30, 50);
 BookHist(LeptonPt_LowQT_LHC_Tail, "LeptonPt_LowQT_LHC_Tail", "LeptonPt_LowQT_LHC_Tail", 20, 37, 47);

 BookHist(LeptonPt_LowQT_LHC_Low, "LeptonPt_LowQT_LHC_Low", "LeptonPt_LowQT_LHC_Low", 1, LeptonPtMin, LeptonPtMiddle);
 BookHist(LeptonPt_LowQT_LHC_High, "LeptonPt_LowQT_LHC_High", "LeptonPt_LowQT_LHC_High", 1, LeptonPtMiddle, LeptonPtMax);
 BookHist(LeptonPt_LowQT_Z_LHC_Low, "LeptonPt_LowQT_Z_LHC_Low", "LeptonPt_LowQT_Z_LHC_Low", 1, LeptonPtMin, LeptonPtMiddle);
 BookHist(LeptonPt_LowQT_Z_LHC_High, "LeptonPt_LowQT_Z_LHC_High", "LeptonPt_LowQT_Z_LHC_High", 1, LeptonPtMiddle, LeptonPtMax);
 BookHist(MtW_LowQT_LHC, "MtW_LowQT_LHC", "MtW_LowQT_LHC", 20, 60, 100);
 BookHist(WPlusPt_LHC, "WPlusPt_LHC", "WPlusPt_LHC", 40, 0, 40);
 BookHist(WMinusPt_LHC, "WMinusPt_LHC", "WMinusPt_LHC", 40, 0, 40);
 BookHist(ZPt_LHC, "ZPt_LHC", "ZPt_LHC", 40, 0, 40);

 BookHist(WMass_Inclusive, "WMass_Inclusive", "WMass_Inclusive", 30, 70, 100);

 BookAngularHist(A0_ZPt, "A0_ZPt", "A0", 23, rangeZPt);
 BookAngularHist(A1_ZPt, "A1_ZPt", "A1", 23, rangeZPt);
 BookAngularHist(A2_ZPt, "A2_ZPt", "A2", 23, rangeZPt);
 BookAngularHist(A3_ZPt, "A3_ZPt", "A3", 23, rangeZPt);
 BookAngularHist(A4_ZPt, "A4_ZPt", "A4", 23, rangeZPt);
 BookAngularHist(L0_ZPt, "L0_ZPt", "L0", 23, rangeZPt);

 BookAngularHist(A0_ZY, "A0_ZY", "A0", 40, -4, 4);
 BookAngularHist(A1_ZY, "A1_ZY", "A1", 40, -4, 4);
 BookAngularHist(A2_ZY, "A2_ZY", "A2", 40, -4, 4);
 BookAngularHist(A3_ZY, "A3_ZY", "A3", 40, -4, 4);
 BookAngularHist(A4_ZY, "A4_ZY", "A4", 40, -4, 4);


 RatioWZ_ScaleEnvelope = new TH1D("RatioWZ_ScaleEnvelope", "RatioWZ_ScaleEnvelope", 30, 0, 15);
 RatioWZ_ScaleEnvelope->SetBinContent(1, 0.994589);
 RatioWZ_ScaleEnvelope->SetBinError(1, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(2, 0.994778);
 RatioWZ_ScaleEnvelope->SetBinError(2, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(3, 0.9951);
 RatioWZ_ScaleEnvelope->SetBinError(3, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(4, 0.995469);
 RatioWZ_ScaleEnvelope->SetBinError(4, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(5, 0.996266);
 RatioWZ_ScaleEnvelope->SetBinError(5, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(6, 0.996951);
 RatioWZ_ScaleEnvelope->SetBinError(6, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(7, 0.997681);
 RatioWZ_ScaleEnvelope->SetBinError(7, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(8, 0.998008);
 RatioWZ_ScaleEnvelope->SetBinError(8, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(9, 0.999476);
 RatioWZ_ScaleEnvelope->SetBinError(9, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(10, 1.00047);
 RatioWZ_ScaleEnvelope->SetBinError(10, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(11, 1.00144);
 RatioWZ_ScaleEnvelope->SetBinError(11, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(12, 1.00239);
 RatioWZ_ScaleEnvelope->SetBinError(12, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(13, 1.00302);
 RatioWZ_ScaleEnvelope->SetBinError(13, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(14, 1.00336);
 RatioWZ_ScaleEnvelope->SetBinError(14, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(15, 1.00382);
 RatioWZ_ScaleEnvelope->SetBinError(15, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(16, 1.00429);
 RatioWZ_ScaleEnvelope->SetBinError(16, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(17, 1.00465);
 RatioWZ_ScaleEnvelope->SetBinError(17, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(18, 1.0048);
 RatioWZ_ScaleEnvelope->SetBinError(18, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(19, 1.00491);
 RatioWZ_ScaleEnvelope->SetBinError(19, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(20, 1.00503);
 RatioWZ_ScaleEnvelope->SetBinError(20, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(21, 1.0051);
 RatioWZ_ScaleEnvelope->SetBinError(21, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(22, 1.00513);
 RatioWZ_ScaleEnvelope->SetBinError(22, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(23, 1.00514);
 RatioWZ_ScaleEnvelope->SetBinError(23, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(24, 1.00518);
 RatioWZ_ScaleEnvelope->SetBinError(24, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(25, 1.00525);
 RatioWZ_ScaleEnvelope->SetBinError(25, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(26, 1.00539);
 RatioWZ_ScaleEnvelope->SetBinError(26, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(27, 1.00552);
 RatioWZ_ScaleEnvelope->SetBinError(27, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(28, 1.00552);
 RatioWZ_ScaleEnvelope->SetBinError(28, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(29, 1.00538);
 RatioWZ_ScaleEnvelope->SetBinError(29, 0.0);
 RatioWZ_ScaleEnvelope->SetBinContent(30, 1.00518);
 RatioWZ_ScaleEnvelope->SetBinError(30, 0.0);
}

void HistsResBosWTev::outputInformation()
{
 if(RootType == "ResBosWTev"){
   Prediction_w225 = (TH1D *)AntiLeptonEta_w225->at(0)->Clone("Prediction_w225");
   Prediction_w225->Reset();
   Data_w225 = (TH1D *)AntiLeptonEta_w225->at(0)->Clone("Data_w225");
   Data_w225->Reset();
   GetWasymmetry(AntiLeptonEta_w225->at(0), LeptonEta_w225->at(0), Prediction_w225);

   Prediction_w227 = (TH1D *)AntiLeptonEta_w227->at(0)->Clone("Prediction_w227");
   Prediction_w227->Reset();
   Data_w227 = (TH1D *)AntiLeptonEta_w227->at(0)->Clone("Data_w227");
   Data_w227->Reset();
   GetWasymmetry(AntiLeptonEta_w227->at(0), LeptonEta_w227->at(0), Prediction_w227);

   Prediction_w234 = (TH1D *)AntiLeptonEta_w234->at(0)->Clone("Prediction_w234");
   Prediction_w234->Reset();
   Data_w234 = (TH1D *)AntiLeptonEta_w234->at(0)->Clone("Data_w234");
   Data_w234->Reset();
   GetWasymmetry(AntiLeptonEta_w234->at(0), LeptonEta_w234->at(0), Prediction_w234);

   Prediction_w281 = (TH1D *)AntiLeptonEta_w281->at(0)->Clone("Prediction_w281");
   Prediction_w281->Reset();
   Data_w281 = (TH1D *)AntiLeptonEta_w281->at(0)->Clone("Data_w281");
   Data_w281->Reset();
   GetWasymmetry(AntiLeptonEta_w281->at(0), LeptonEta_w281->at(0), Prediction_w281);

   ReadData();

   hf->cd();

   Prediction_w225->Write();
   Prediction_w227->Write();
   Prediction_w234->Write();
   Prediction_w281->Write();
   Data_w225->Write();
   Data_w227->Write();
   Data_w234->Write();
   Data_w281->Write();

   MtW_CDF_Data = new TH1D("MtW_CDF_Data", "MtW_CDF_Data", 50, 65, 90);
   MtW_CDF_Data->SetBinContent(1, 36842.1);
   MtW_CDF_Data->SetBinContent(2, 39707.6);
   MtW_CDF_Data->SetBinContent(3, 42163.7);
   MtW_CDF_Data->SetBinContent(4, 44210.5);
   MtW_CDF_Data->SetBinContent(5, 46257.3);
   MtW_CDF_Data->SetBinContent(6, 48713.5);
   MtW_CDF_Data->SetBinContent(7, 50350.9);
   MtW_CDF_Data->SetBinContent(8, 52397.7);
   MtW_CDF_Data->SetBinContent(9, 54444.4);
   MtW_CDF_Data->SetBinContent(10, 55672.5);
   MtW_CDF_Data->SetBinContent(11, 57309.9);
   MtW_CDF_Data->SetBinContent(12, 58538);
   MtW_CDF_Data->SetBinContent(13, 60175.4);
   MtW_CDF_Data->SetBinContent(14, 61403.5);
   MtW_CDF_Data->SetBinContent(15, 62631.6);
   MtW_CDF_Data->SetBinContent(16, 63859.6);
   MtW_CDF_Data->SetBinContent(17, 64678.4);
   MtW_CDF_Data->SetBinContent(18, 65087.7);
   MtW_CDF_Data->SetBinContent(19, 65906.4);
   MtW_CDF_Data->SetBinContent(20, 66315.8);
   MtW_CDF_Data->SetBinContent(21, 66725.1);
   MtW_CDF_Data->SetBinContent(22, 65906.4);
   MtW_CDF_Data->SetBinContent(23, 65497.1);
   MtW_CDF_Data->SetBinContent(24, 65087.7);
   MtW_CDF_Data->SetBinContent(25, 64678.4);
   MtW_CDF_Data->SetBinContent(26, 63450.3);
   MtW_CDF_Data->SetBinContent(27, 61812.9);
   MtW_CDF_Data->SetBinContent(28, 60584.8);
   MtW_CDF_Data->SetBinContent(29, 58947.4);
   MtW_CDF_Data->SetBinContent(30, 56491.2);
   MtW_CDF_Data->SetBinContent(31, 54035.1);
   MtW_CDF_Data->SetBinContent(32, 51578.9);
   MtW_CDF_Data->SetBinContent(33, 48713.5);
   MtW_CDF_Data->SetBinContent(34, 45848);
   MtW_CDF_Data->SetBinContent(35, 42982.5);
   MtW_CDF_Data->SetBinContent(36, 40117);
   MtW_CDF_Data->SetBinContent(37, 37251.5);
   MtW_CDF_Data->SetBinContent(38, 34386);
   MtW_CDF_Data->SetBinContent(39, 31520.5);
   MtW_CDF_Data->SetBinContent(40, 29064.3);
   MtW_CDF_Data->SetBinContent(41, 26608.2);
   MtW_CDF_Data->SetBinContent(42, 24561.4);
   MtW_CDF_Data->SetBinContent(43, 22105.3);
   MtW_CDF_Data->SetBinContent(44, 20058.5);
   MtW_CDF_Data->SetBinContent(45, 18011.7);
   MtW_CDF_Data->SetBinContent(46, 16374.3);
   MtW_CDF_Data->SetBinContent(47, 14736.8);
   MtW_CDF_Data->SetBinContent(48, 13508.8);
   MtW_CDF_Data->SetBinContent(49, 11871.3);
   MtW_CDF_Data->SetBinContent(50, 11052.6);
   for(int ibin = 1; ibin <= MtW_CDF_Data->GetNbinsX(); ibin++){MtW_CDF_Data->SetBinError(ibin, 0.0);}
  
   LeptonPt_CDF_Data = new TH1D("LeptonPt_CDF_Data", "LeptonPt_CDF_Data", 64, 32, 48);
   LeptonPt_CDF_Data->SetBinContent(1, 32982.5);
   LeptonPt_CDF_Data->SetBinContent(2, 34386);
   LeptonPt_CDF_Data->SetBinContent(3, 35438.6);
   LeptonPt_CDF_Data->SetBinContent(4, 36491.2);
   LeptonPt_CDF_Data->SetBinContent(5, 37543.9);
   LeptonPt_CDF_Data->SetBinContent(6, 38596.5);
   LeptonPt_CDF_Data->SetBinContent(7, 40000);
   LeptonPt_CDF_Data->SetBinContent(8, 41052.6);
   LeptonPt_CDF_Data->SetBinContent(9, 42105.3);
   LeptonPt_CDF_Data->SetBinContent(10, 43508.8);
   LeptonPt_CDF_Data->SetBinContent(11, 44561.4);
   LeptonPt_CDF_Data->SetBinContent(12, 45614);
   LeptonPt_CDF_Data->SetBinContent(13, 47017.5);
   LeptonPt_CDF_Data->SetBinContent(14, 47719.3);
   LeptonPt_CDF_Data->SetBinContent(15, 49122.8);
   LeptonPt_CDF_Data->SetBinContent(16, 49824.6);
   LeptonPt_CDF_Data->SetBinContent(17, 51228.1);
   LeptonPt_CDF_Data->SetBinContent(18, 52280.7);
   LeptonPt_CDF_Data->SetBinContent(19, 52982.5);
   LeptonPt_CDF_Data->SetBinContent(20, 54035.1);
   LeptonPt_CDF_Data->SetBinContent(21, 54736.8);
   LeptonPt_CDF_Data->SetBinContent(22, 55438.6);
   LeptonPt_CDF_Data->SetBinContent(23, 56140.4);
   LeptonPt_CDF_Data->SetBinContent(24, 56491.2);
   LeptonPt_CDF_Data->SetBinContent(25, 56842.1);
   LeptonPt_CDF_Data->SetBinContent(26, 56842.1);
   LeptonPt_CDF_Data->SetBinContent(27, 56491.2);
   LeptonPt_CDF_Data->SetBinContent(28, 55789.5);
   LeptonPt_CDF_Data->SetBinContent(29, 55087.7);
   LeptonPt_CDF_Data->SetBinContent(30, 53684.2);
   LeptonPt_CDF_Data->SetBinContent(31, 52631.6);
   LeptonPt_CDF_Data->SetBinContent(32, 50877.2);
   LeptonPt_CDF_Data->SetBinContent(33, 48771.9);
   LeptonPt_CDF_Data->SetBinContent(34, 46666.7);
   LeptonPt_CDF_Data->SetBinContent(35, 43859.6);
   LeptonPt_CDF_Data->SetBinContent(36, 41403.5);
   LeptonPt_CDF_Data->SetBinContent(37, 38947.4);
   LeptonPt_CDF_Data->SetBinContent(38, 36491.2);
   LeptonPt_CDF_Data->SetBinContent(39, 34035.1);
   LeptonPt_CDF_Data->SetBinContent(40, 31578.9);
   LeptonPt_CDF_Data->SetBinContent(41, 29122.8);
   LeptonPt_CDF_Data->SetBinContent(42, 27368.4);
   LeptonPt_CDF_Data->SetBinContent(43, 25263.2);
   LeptonPt_CDF_Data->SetBinContent(44, 23157.9);
   LeptonPt_CDF_Data->SetBinContent(45, 21754.4);
   LeptonPt_CDF_Data->SetBinContent(46, 20000);
   LeptonPt_CDF_Data->SetBinContent(47, 18596.5);
   LeptonPt_CDF_Data->SetBinContent(48, 17193);
   LeptonPt_CDF_Data->SetBinContent(49, 15789.5);
   LeptonPt_CDF_Data->SetBinContent(50, 14736.8);
   LeptonPt_CDF_Data->SetBinContent(51, 13684.2);
   LeptonPt_CDF_Data->SetBinContent(52, 12631.6);
   LeptonPt_CDF_Data->SetBinContent(53, 11578.9);
   LeptonPt_CDF_Data->SetBinContent(54, 10877.2);
   LeptonPt_CDF_Data->SetBinContent(55, 10175.4);
   LeptonPt_CDF_Data->SetBinContent(56, 9122.81);
   LeptonPt_CDF_Data->SetBinContent(57, 8771.93);
   LeptonPt_CDF_Data->SetBinContent(58, 7719.3);
   LeptonPt_CDF_Data->SetBinContent(59, 7368.42);
   LeptonPt_CDF_Data->SetBinContent(60, 6666.67);
   LeptonPt_CDF_Data->SetBinContent(61, 5964.91);
   LeptonPt_CDF_Data->SetBinContent(62, 5614.04);
   LeptonPt_CDF_Data->SetBinContent(63, 5263.16);
   LeptonPt_CDF_Data->SetBinContent(64, 4912.28);
   for(int ibin = 1; ibin <= LeptonPt_CDF_Data->GetNbinsX(); ibin++){LeptonPt_CDF_Data->SetBinError(ibin, 0.0);}
  
   NuPt_CDF_Data = new TH1D("NuPt_CDF_Data", "NuPt_CDF_Data", 64, 32, 48);
   NuPt_CDF_Data->SetBinContent(1, 34280);
   NuPt_CDF_Data->SetBinContent(2, 35190.1);
   NuPt_CDF_Data->SetBinContent(3, 36403.5);
   NuPt_CDF_Data->SetBinContent(4, 37313.6);
   NuPt_CDF_Data->SetBinContent(5, 38527);
   NuPt_CDF_Data->SetBinContent(6, 39437.1);
   NuPt_CDF_Data->SetBinContent(7, 40347.2);
   NuPt_CDF_Data->SetBinContent(8, 41560.7);
   NuPt_CDF_Data->SetBinContent(9, 42167.4);
   NuPt_CDF_Data->SetBinContent(10, 43077.5);
   NuPt_CDF_Data->SetBinContent(11, 43684.2);
   NuPt_CDF_Data->SetBinContent(12, 44594.3);
   NuPt_CDF_Data->SetBinContent(13, 45504.4);
   NuPt_CDF_Data->SetBinContent(14, 46111.1);
   NuPt_CDF_Data->SetBinContent(15, 46717.8);
   NuPt_CDF_Data->SetBinContent(16, 47324.6);
   NuPt_CDF_Data->SetBinContent(17, 47627.9);
   NuPt_CDF_Data->SetBinContent(18, 48234.6);
   NuPt_CDF_Data->SetBinContent(19, 48538);
   NuPt_CDF_Data->SetBinContent(20, 48841.4);
   NuPt_CDF_Data->SetBinContent(21, 49144.7);
   NuPt_CDF_Data->SetBinContent(22, 49144.7);
   NuPt_CDF_Data->SetBinContent(23, 49144.7);
   NuPt_CDF_Data->SetBinContent(24, 49144.7);
   NuPt_CDF_Data->SetBinContent(25, 48841.4);
   NuPt_CDF_Data->SetBinContent(26, 48234.6);
   NuPt_CDF_Data->SetBinContent(27, 47931.3);
   NuPt_CDF_Data->SetBinContent(28, 47627.9);
   NuPt_CDF_Data->SetBinContent(29, 46717.8);
   NuPt_CDF_Data->SetBinContent(30, 45807.7);
   NuPt_CDF_Data->SetBinContent(31, 44897.7);
   NuPt_CDF_Data->SetBinContent(32, 43987.6);
   NuPt_CDF_Data->SetBinContent(33, 42774.1);
   NuPt_CDF_Data->SetBinContent(34, 41560.7);
   NuPt_CDF_Data->SetBinContent(35, 40347.2);
   NuPt_CDF_Data->SetBinContent(36, 38830.4);
   NuPt_CDF_Data->SetBinContent(37, 37313.6);
   NuPt_CDF_Data->SetBinContent(38, 35796.8);
   NuPt_CDF_Data->SetBinContent(39, 34583.3);
   NuPt_CDF_Data->SetBinContent(40, 32763.2);
   NuPt_CDF_Data->SetBinContent(41, 31549.7);
   NuPt_CDF_Data->SetBinContent(42, 29729.5);
   NuPt_CDF_Data->SetBinContent(43, 28516.1);
   NuPt_CDF_Data->SetBinContent(44, 26695.9);
   NuPt_CDF_Data->SetBinContent(45, 25179.1);
   NuPt_CDF_Data->SetBinContent(46, 23965.6);
   NuPt_CDF_Data->SetBinContent(47, 22448.8);
   NuPt_CDF_Data->SetBinContent(48, 21235.4);
   NuPt_CDF_Data->SetBinContent(49, 20021.9);
   NuPt_CDF_Data->SetBinContent(50, 18808.5);
   NuPt_CDF_Data->SetBinContent(51, 17595);
   NuPt_CDF_Data->SetBinContent(52, 16381.6);
   NuPt_CDF_Data->SetBinContent(53, 15168.1);
   NuPt_CDF_Data->SetBinContent(54, 14258);
   NuPt_CDF_Data->SetBinContent(55, 13348);
   NuPt_CDF_Data->SetBinContent(56, 12437.9);
   NuPt_CDF_Data->SetBinContent(57, 11527.8);
   NuPt_CDF_Data->SetBinContent(58, 10617.7);
   NuPt_CDF_Data->SetBinContent(59, 9707.6);
   NuPt_CDF_Data->SetBinContent(60, 9100.88);
   NuPt_CDF_Data->SetBinContent(61, 8190.79);
   NuPt_CDF_Data->SetBinContent(62, 7584.06);
   NuPt_CDF_Data->SetBinContent(63, 6977.34);
   NuPt_CDF_Data->SetBinContent(64, 6370.61);
   for(int ibin = 1; ibin <= NuPt_CDF_Data->GetNbinsX(); ibin++){NuPt_CDF_Data->SetBinError(ibin, 0.0);}
  
   MtW_CDF_Data->Write();
   LeptonPt_CDF_Data->Write();
   NuPt_CDF_Data->Write();

   MtW_CDF_Electron = new TH1D("MtW_CDF_Electron", "MtW_CDF_Electron", 50, 65, 90);
   MtW_CDF_Electron->SetBinContent(1, 26644.1);
   MtW_CDF_Electron->SetBinContent(2, 28532.7);
   MtW_CDF_Electron->SetBinContent(3, 30219.1);
   MtW_CDF_Electron->SetBinContent(4, 31905.4);
   MtW_CDF_Electron->SetBinContent(5, 33524.3);
   MtW_CDF_Electron->SetBinContent(6, 35210.6);
   MtW_CDF_Electron->SetBinContent(7, 36559.7);
   MtW_CDF_Electron->SetBinContent(8, 38043.7);
   MtW_CDF_Electron->SetBinContent(9, 39325.3);
   MtW_CDF_Electron->SetBinContent(10, 40539.4);
   MtW_CDF_Electron->SetBinContent(11, 41551.2);
   MtW_CDF_Electron->SetBinContent(12, 42563);
   MtW_CDF_Electron->SetBinContent(13, 43507.4);
   MtW_CDF_Electron->SetBinContent(14, 44181.9);
   MtW_CDF_Electron->SetBinContent(15, 45126.3);
   MtW_CDF_Electron->SetBinContent(16, 45665.9);
   MtW_CDF_Electron->SetBinContent(17, 46003.1);
   MtW_CDF_Electron->SetBinContent(18, 46273);
   MtW_CDF_Electron->SetBinContent(19, 46475.3);
   MtW_CDF_Electron->SetBinContent(20, 46475.3);
   MtW_CDF_Electron->SetBinContent(21, 46340.4);
   MtW_CDF_Electron->SetBinContent(22, 45935.7);
   MtW_CDF_Electron->SetBinContent(23, 45531);
   MtW_CDF_Electron->SetBinContent(24, 45126.3);
   MtW_CDF_Electron->SetBinContent(25, 44384.3);
   MtW_CDF_Electron->SetBinContent(26, 43439.9);
   MtW_CDF_Electron->SetBinContent(27, 42495.6);
   MtW_CDF_Electron->SetBinContent(28, 41146.5);
   MtW_CDF_Electron->SetBinContent(29, 39662.5);
   MtW_CDF_Electron->SetBinContent(30, 38111.1);
   MtW_CDF_Electron->SetBinContent(31, 36357.3);
   MtW_CDF_Electron->SetBinContent(32, 34603.5);
   MtW_CDF_Electron->SetBinContent(33, 32714.8);
   MtW_CDF_Electron->SetBinContent(34, 30893.6);
   MtW_CDF_Electron->SetBinContent(35, 28870);
   MtW_CDF_Electron->SetBinContent(36, 27116.2);
   MtW_CDF_Electron->SetBinContent(37, 24957.7);
   MtW_CDF_Electron->SetBinContent(38, 23069);
   MtW_CDF_Electron->SetBinContent(39, 21315.2);
   MtW_CDF_Electron->SetBinContent(40, 19696.4);
   MtW_CDF_Electron->SetBinContent(41, 17942.6);
   MtW_CDF_Electron->SetBinContent(42, 16121.3);
   MtW_CDF_Electron->SetBinContent(43, 14772.3);
   MtW_CDF_Electron->SetBinContent(44, 13220.8);
   MtW_CDF_Electron->SetBinContent(45, 11939.2);
   MtW_CDF_Electron->SetBinContent(46, 10792.5);
   MtW_CDF_Electron->SetBinContent(47, 9780.73);
   MtW_CDF_Electron->SetBinContent(48, 8836.38);
   MtW_CDF_Electron->SetBinContent(49, 7959.49);
   MtW_CDF_Electron->SetBinContent(50, 7217.5);
   for(int ibin = 1; ibin <= MtW_CDF_Electron->GetNbinsX(); ibin++){MtW_CDF_Electron->SetBinError(ibin, 0.0);}

   LeptonPt_CDF_Electron = new TH1D("LeptonPt_CDF_Electron", "LeptonPt_CDF_Electron", 64, 32, 48);
   LeptonPt_CDF_Electron->SetBinContent(1, 24656);
   LeptonPt_CDF_Electron->SetBinContent(2, 25593.1);
   LeptonPt_CDF_Electron->SetBinContent(3, 26471.5);
   LeptonPt_CDF_Electron->SetBinContent(4, 27408.6);
   LeptonPt_CDF_Electron->SetBinContent(5, 28287.1);
   LeptonPt_CDF_Electron->SetBinContent(6, 29165.5);
   LeptonPt_CDF_Electron->SetBinContent(7, 30161.1);
   LeptonPt_CDF_Electron->SetBinContent(8, 30981.1);
   LeptonPt_CDF_Electron->SetBinContent(9, 31859.5);
   LeptonPt_CDF_Electron->SetBinContent(10, 32855.2);
   LeptonPt_CDF_Electron->SetBinContent(11, 33675.1);
   LeptonPt_CDF_Electron->SetBinContent(12, 34495);
   LeptonPt_CDF_Electron->SetBinContent(13, 35314.9);
   LeptonPt_CDF_Electron->SetBinContent(14, 36076.2);
   LeptonPt_CDF_Electron->SetBinContent(15, 37013.3);
   LeptonPt_CDF_Electron->SetBinContent(16, 37540.4);
   LeptonPt_CDF_Electron->SetBinContent(17, 38477.4);
   LeptonPt_CDF_Electron->SetBinContent(18, 39063.1);
   LeptonPt_CDF_Electron->SetBinContent(19, 39883);
   LeptonPt_CDF_Electron->SetBinContent(20, 40351.5);
   LeptonPt_CDF_Electron->SetBinContent(21, 40820);
   LeptonPt_CDF_Electron->SetBinContent(22, 41347.1);
   LeptonPt_CDF_Electron->SetBinContent(23, 41640);
   LeptonPt_CDF_Electron->SetBinContent(24, 41698.5);
   LeptonPt_CDF_Electron->SetBinContent(25, 41815.6);
   LeptonPt_CDF_Electron->SetBinContent(26, 41581.4);
   LeptonPt_CDF_Electron->SetBinContent(27, 41405.7);
   LeptonPt_CDF_Electron->SetBinContent(28, 40937.2);
   LeptonPt_CDF_Electron->SetBinContent(29, 40410.1);
   LeptonPt_CDF_Electron->SetBinContent(30, 39473);
   LeptonPt_CDF_Electron->SetBinContent(31, 38301.7);
   LeptonPt_CDF_Electron->SetBinContent(32, 37130.4);
   LeptonPt_CDF_Electron->SetBinContent(33, 35666.3);
   LeptonPt_CDF_Electron->SetBinContent(34, 34085);
   LeptonPt_CDF_Electron->SetBinContent(35, 32562.3);
   LeptonPt_CDF_Electron->SetBinContent(36, 30688.2);
   LeptonPt_CDF_Electron->SetBinContent(37, 29165.5);
   LeptonPt_CDF_Electron->SetBinContent(38, 26998.6);
   LeptonPt_CDF_Electron->SetBinContent(39, 25300.2);
   LeptonPt_CDF_Electron->SetBinContent(40, 23660.4);
   LeptonPt_CDF_Electron->SetBinContent(41, 21786.3);
   LeptonPt_CDF_Electron->SetBinContent(42, 20087.9);
   LeptonPt_CDF_Electron->SetBinContent(43, 18740.9);
   LeptonPt_CDF_Electron->SetBinContent(44, 17101.1);
   LeptonPt_CDF_Electron->SetBinContent(45, 15812.6);
   LeptonPt_CDF_Electron->SetBinContent(46, 14465.6);
   LeptonPt_CDF_Electron->SetBinContent(47, 13470);
   LeptonPt_CDF_Electron->SetBinContent(48, 12357.3);
   LeptonPt_CDF_Electron->SetBinContent(49, 11420.2);
   LeptonPt_CDF_Electron->SetBinContent(50, 10600.3);
   LeptonPt_CDF_Electron->SetBinContent(51, 9721.85);
   LeptonPt_CDF_Electron->SetBinContent(52, 8960.5);
   LeptonPt_CDF_Electron->SetBinContent(53, 8316.28);
   LeptonPt_CDF_Electron->SetBinContent(54, 7672.06);
   LeptonPt_CDF_Electron->SetBinContent(55, 7027.84);
   LeptonPt_CDF_Electron->SetBinContent(56, 6500.75);
   LeptonPt_CDF_Electron->SetBinContent(57, 5973.66);
   LeptonPt_CDF_Electron->SetBinContent(58, 5563.71);
   LeptonPt_CDF_Electron->SetBinContent(59, 5095.18);
   LeptonPt_CDF_Electron->SetBinContent(60, 4626.66);
   LeptonPt_CDF_Electron->SetBinContent(61, 4216.7);
   LeptonPt_CDF_Electron->SetBinContent(62, 3865.31);
   LeptonPt_CDF_Electron->SetBinContent(63, 3631.05);
   LeptonPt_CDF_Electron->SetBinContent(64, 3396.79);
   for(int ibin = 1; ibin <= LeptonPt_CDF_Electron->GetNbinsX(); ibin++){LeptonPt_CDF_Electron->SetBinError(ibin, 0.0);}

   NuPt_CDF_Electron = new TH1D("NuPt_CDF_Electron", "NuPt_CDF_Electron", 64, 32, 48);
   NuPt_CDF_Electron->SetBinContent(1, 26603.7);
   NuPt_CDF_Electron->SetBinContent(2, 27375.6);
   NuPt_CDF_Electron->SetBinContent(3, 28250.4);
   NuPt_CDF_Electron->SetBinContent(4, 29022.3);
   NuPt_CDF_Electron->SetBinContent(5, 29845.6);
   NuPt_CDF_Electron->SetBinContent(6, 30411.6);
   NuPt_CDF_Electron->SetBinContent(7, 31080.6);
   NuPt_CDF_Electron->SetBinContent(8, 31801);
   NuPt_CDF_Electron->SetBinContent(9, 32418.5);
   NuPt_CDF_Electron->SetBinContent(10, 33138.9);
   NuPt_CDF_Electron->SetBinContent(11, 33653.5);
   NuPt_CDF_Electron->SetBinContent(12, 34219.5);
   NuPt_CDF_Electron->SetBinContent(13, 34682.6);
   NuPt_CDF_Electron->SetBinContent(14, 35197.2);
   NuPt_CDF_Electron->SetBinContent(15, 35660.3);
   NuPt_CDF_Electron->SetBinContent(16, 36020.5);
   NuPt_CDF_Electron->SetBinContent(17, 36329.3);
   NuPt_CDF_Electron->SetBinContent(18, 36638);
   NuPt_CDF_Electron->SetBinContent(19, 36740.9);
   NuPt_CDF_Electron->SetBinContent(20, 36895.3);
   NuPt_CDF_Electron->SetBinContent(21, 36998.2);
   NuPt_CDF_Electron->SetBinContent(22, 36843.9);
   NuPt_CDF_Electron->SetBinContent(23, 36843.9);
   NuPt_CDF_Electron->SetBinContent(24, 36586.6);
   NuPt_CDF_Electron->SetBinContent(25, 36329.3);
   NuPt_CDF_Electron->SetBinContent(26, 35917.6);
   NuPt_CDF_Electron->SetBinContent(27, 35505.9);
   NuPt_CDF_Electron->SetBinContent(28, 34991.4);
   NuPt_CDF_Electron->SetBinContent(29, 34373.9);
   NuPt_CDF_Electron->SetBinContent(30, 33653.5);
   NuPt_CDF_Electron->SetBinContent(31, 32778.7);
   NuPt_CDF_Electron->SetBinContent(32, 32109.7);
   NuPt_CDF_Electron->SetBinContent(33, 31183.5);
   NuPt_CDF_Electron->SetBinContent(34, 30102.9);
   NuPt_CDF_Electron->SetBinContent(35, 29279.5);
   NuPt_CDF_Electron->SetBinContent(36, 28096);
   NuPt_CDF_Electron->SetBinContent(37, 27015.4);
   NuPt_CDF_Electron->SetBinContent(38, 26037.7);
   NuPt_CDF_Electron->SetBinContent(39, 24802.7);
   NuPt_CDF_Electron->SetBinContent(40, 23722.1);
   NuPt_CDF_Electron->SetBinContent(41, 22641.5);
   NuPt_CDF_Electron->SetBinContent(42, 21406.5);
   NuPt_CDF_Electron->SetBinContent(43, 20274.4);
   NuPt_CDF_Electron->SetBinContent(44, 19451.1);
   NuPt_CDF_Electron->SetBinContent(45, 18216.1);
   NuPt_CDF_Electron->SetBinContent(46, 17238.4);
   NuPt_CDF_Electron->SetBinContent(47, 16157.8);
   NuPt_CDF_Electron->SetBinContent(48, 15180.1);
   NuPt_CDF_Electron->SetBinContent(49, 14305.3);
   NuPt_CDF_Electron->SetBinContent(50, 13327.6);
   NuPt_CDF_Electron->SetBinContent(51, 12401.4);
   NuPt_CDF_Electron->SetBinContent(52, 11526.6);
   NuPt_CDF_Electron->SetBinContent(53, 10960.5);
   NuPt_CDF_Electron->SetBinContent(54, 10137.2);
   NuPt_CDF_Electron->SetBinContent(55, 9468.25);
   NuPt_CDF_Electron->SetBinContent(56, 8747.84);
   NuPt_CDF_Electron->SetBinContent(57, 8027.43);
   NuPt_CDF_Electron->SetBinContent(58, 7461.39);
   NuPt_CDF_Electron->SetBinContent(59, 6895.36);
   NuPt_CDF_Electron->SetBinContent(60, 6277.86);
   NuPt_CDF_Electron->SetBinContent(61, 5866.2);
   NuPt_CDF_Electron->SetBinContent(62, 5351.62);
   NuPt_CDF_Electron->SetBinContent(63, 4991.42);
   NuPt_CDF_Electron->SetBinContent(64, 4631.21);
   for(int ibin = 1; ibin <= NuPt_CDF_Electron->GetNbinsX(); ibin++){NuPt_CDF_Electron->SetBinError(ibin, 0.0);}

   MtW_CDF_Electron->Write();
   LeptonPt_CDF_Electron->Write();
   NuPt_CDF_Electron->Write();

   MtW_CDF->at(0)->Scale(1.0 / 5.0);
   LeptonPt_CDF->at(0)->Scale(1.0 / 5.0);
   NuPt_CDF->at(0)->Scale(1.0 / 5.0);
   DeltaPhi_CDF->at(0)->Scale(1.0 / 5.0);
   WPt_CDF->at(0)->Scale(1.0 / 5.0);
   ZPt_CDF->at(0)->Scale(1.0 / 5.0);
   WPt_CDF_FineBin->at(0)->Scale(1.0 / 5.0);
   ZPt_CDF_FineBin->at(0)->Scale(1.0 / 5.0);
   WPt_CDF_ScaleUp->at(0)->Scale(1.0 / 5.0);
   WPt_CDF_ScaleDown->at(0)->Scale(1.0 / 5.0);
   WPt_CDF_ScaleVari->at(0)->Scale(1.0 / 5.0);

   MtW_CDF_Smear->at(0)->Scale(1.0 / 5.0);
   LeptonPt_CDF_Smear->at(0)->Scale(1.0 / 5.0);
   NuPt_CDF_Smear->at(0)->Scale(1.0 / 5.0);
   DeltaPhi_CDF_Smear->at(0)->Scale(1.0 / 5.0);
   WPt_CDF_Smear->at(0)->Scale(1.0 / 5.0);
   ZPt_CDF_Smear->at(0)->Scale(1.0 / 5.0);
  
   MtW_CDF_Pseudodata = GenPseudodata(8800.0, MtW_CDF->at(0));
   LeptonPt_CDF_Pseudodata = GenPseudodata(8800.0, LeptonPt_CDF->at(0));
   NuPt_CDF_Pseudodata = GenPseudodata(8800.0, NuPt_CDF->at(0));
   DeltaPhi_CDF_Pseudodata = GenPseudodata(8800.0, DeltaPhi_CDF->at(0));
   WPt_CDF_Pseudodata = GenPseudodata(8800.0, WPt_CDF->at(0));
   WPt_CDF_Pseudodata_NoFluc = GenPseudodataNoFluc(8800.0, WPt_CDF->at(0), "Pseudodata_NoFluc");
   WPt_CDF_ScaleUp_NoFluc = GenPseudodataNoFluc(8800.0, WPt_CDF_ScaleUp->at(0), "Pseudodata_NoFluc");
   WPt_CDF_ScaleDown_NoFluc = GenPseudodataNoFluc(8800.0, WPt_CDF_ScaleDown->at(0), "Pseudodata_NoFluc");
   WPt_CDF_ScaleVari_NoFluc = GenPseudodataNoFluc(8800.0, WPt_CDF_ScaleVari->at(0), "Pseudodata_NoFluc");
   ZPt_CDF_Pseudodata = GenPseudodata(8800.0, ZPt_CDF->at(0));
  
   MtW_CDF_Pseudodata->Write();
   LeptonPt_CDF_Pseudodata->Write();
   NuPt_CDF_Pseudodata->Write();
   DeltaPhi_CDF_Pseudodata->Write();
   WPt_CDF_Pseudodata->Write();
   WPt_CDF_Pseudodata_NoFluc->Write();
   WPt_CDF_ScaleUp_NoFluc->Write();
   WPt_CDF_ScaleDown_NoFluc->Write();
   WPt_CDF_ScaleVari_NoFluc->Write();
   ZPt_CDF_Pseudodata->Write();

   myLog<<LOG_INFO<<"Chi2 of pT(W): "<<CalculateChi2WithData(WPt_CDF_ScaleVari_NoFluc, WPt_CDF_Pseudodata_NoFluc)<<endl;

   MtW_CDF_Smear_Pseudodata = GenPseudodata(8800.0, MtW_CDF_Smear->at(0));
   LeptonPt_CDF_Smear_Pseudodata = GenPseudodata(8800.0, LeptonPt_CDF_Smear->at(0));
   NuPt_CDF_Smear_Pseudodata = GenPseudodata(8800.0, NuPt_CDF_Smear->at(0));
   DeltaPhi_CDF_Smear_Pseudodata = GenPseudodata(8800.0, DeltaPhi_CDF_Smear->at(0));
   WPt_CDF_Smear_Pseudodata = GenPseudodata(8800.0, WPt_CDF_Smear->at(0));
   ZPt_CDF_Smear_Pseudodata = GenPseudodata(8800.0, ZPt_CDF_Smear->at(0));
  
   MtW_CDF_Smear_Pseudodata->Write();
   LeptonPt_CDF_Smear_Pseudodata->Write();
   NuPt_CDF_Smear_Pseudodata->Write();
   DeltaPhi_CDF_Smear_Pseudodata->Write();
   WPt_CDF_Smear_Pseudodata->Write();
   ZPt_CDF_Smear_Pseudodata->Write();
  
   MtW_CDF_LargeStat = GenPseudodata(8800000.0, MtW_CDF->at(0), "LargeStat");
   LeptonPt_CDF_LargeStat = GenPseudodata(8800000.0, LeptonPt_CDF->at(0), "LargeStat");
   NuPt_CDF_LargeStat = GenPseudodata(8800000.0, NuPt_CDF->at(0), "LargeStat");
   DeltaPhi_CDF_LargeStat = GenPseudodata(8800000.0, DeltaPhi_CDF->at(0), "LargeStat");
   WPt_CDF_LargeStat = GenPseudodata(8800000.0, WPt_CDF->at(0), "LargeStat");
   ZPt_CDF_LargeStat = GenPseudodata(8800000.0, ZPt_CDF->at(0), "LargeStat");
   WPt_CDF_FineBin_LargeStat = GenPseudodata(8800000.0, WPt_CDF_FineBin->at(0), "LargeStat");
   ZPt_CDF_FineBin_LargeStat = GenPseudodata(8800000.0, ZPt_CDF_FineBin->at(0), "LargeStat");
  
   MtW_CDF_LargeStat->Write();
   LeptonPt_CDF_LargeStat->Write();
   NuPt_CDF_LargeStat->Write();
   DeltaPhi_CDF_LargeStat->Write();
   WPt_CDF_LargeStat->Write();
   ZPt_CDF_LargeStat->Write();
   WPt_CDF_FineBin_LargeStat->Write();
   ZPt_CDF_FineBin_LargeStat->Write();
  
   MtW_CDF_Smear_LargeStat = GenPseudodata(8800000.0, MtW_CDF_Smear->at(0), "LargeStat");
   LeptonPt_CDF_Smear_LargeStat = GenPseudodata(8800000.0, LeptonPt_CDF_Smear->at(0), "LargeStat");
   NuPt_CDF_Smear_LargeStat = GenPseudodata(8800000.0, NuPt_CDF_Smear->at(0), "LargeStat");
   DeltaPhi_CDF_Smear_LargeStat = GenPseudodata(8800000.0, DeltaPhi_CDF_Smear->at(0), "LargeStat");
   WPt_CDF_Smear_LargeStat = GenPseudodata(8800000.0, WPt_CDF_Smear->at(0), "LargeStat");
   ZPt_CDF_Smear_LargeStat = GenPseudodata(8800000.0, ZPt_CDF_Smear->at(0), "LargeStat");
  
   MtW_CDF_Smear_LargeStat->Write();
   LeptonPt_CDF_Smear_LargeStat->Write();
   NuPt_CDF_Smear_LargeStat->Write();
   DeltaPhi_CDF_Smear_LargeStat->Write();
   WPt_CDF_Smear_LargeStat->Write();
   ZPt_CDF_Smear_LargeStat->Write();
  
   FiducialCrossSection_W = new TH1D("FiducialCrossSection_W", "FiducialCrossSection_W", 1, 0, 1);
   FiducialCrossSection_Z = new TH1D("FiducialCrossSection_Z", "FiducialCrossSection_Z", 1, 0, 1);
  
   FiducialCrossSection_W->SetBinContent(1, WPt_CDF->at(0)->Integral());
   FiducialCrossSection_W->SetBinError(1, 0.0);
   FiducialCrossSection_Z->SetBinContent(1, ZPt_CDF->at(0)->Integral());
   FiducialCrossSection_Z->SetBinError(1, 0.0);
  
   FiducialCrossSection_W->Write();
   FiducialCrossSection_Z->Write();
  
   FiducialCrossSection_Smear_W = new TH1D("FiducialCrossSection_Smear_W", "FiducialCrossSection_Smear_W", 1, 0, 1);
   FiducialCrossSection_Smear_Z = new TH1D("FiducialCrossSection_Smear_Z", "FiducialCrossSection_Smear_Z", 1, 0, 1);
  
   FiducialCrossSection_Smear_W->SetBinContent(1, WPt_CDF_Smear->at(0)->Integral());
   FiducialCrossSection_Smear_W->SetBinError(1, 0.0);
   FiducialCrossSection_Smear_Z->SetBinContent(1, ZPt_CDF_Smear->at(0)->Integral());
   FiducialCrossSection_Smear_Z->SetBinError(1, 0.0);
  
   FiducialCrossSection_Smear_W->Write();
   FiducialCrossSection_Smear_Z->Write();

   RatioWZ_ScaleEnvelope->Write();

   //no QT cut
   MultiWeightHist* LeptonPtAsymmetry_multiweight = LeptonPt_LHC_Low_multiweight->at(0)->GetAsymHist(LeptonPt_LHC_High_multiweight->at(0));
   JacobianAsymmetry = new TH1D("JacobianAsymmetry", "JacobianAsymmetry", 21, 80.3265, 80.4315);

   for(int iWeight = 0; iWeight < LeptonPtAsymmetry_multiweight->nWeight; iWeight++){
     JacobianAsymmetry->SetBinContent(iWeight + 1, LeptonPtAsymmetry_multiweight->GetHistPtr(iWeight)->GetBinContent(1));
     JacobianAsymmetry->SetBinError(iWeight + 1, LeptonPtAsymmetry_multiweight->GetHistPtr(iWeight)->GetBinError(1));
   }
   JacobianAsymmetrySlope = new TH1D("JacobianAsymmetrySlope", "JacobianAsymmetrySlope", 1, 80.3265, 80.4315);
   JacobianAsymmetryOffset = new TH1D("JacobianAsymmetryOffset", "JacobianAsymmetryOffset", 1, 80.3265, 80.4315);

   TH1D* tmpJacobianAsymmetry = new TH1D("tmpJacobianAsymmetry", "tmpJacobianAsymmetry", 21, 0.3265, 0.4315);
   for(int iWeight = 0; iWeight < LeptonPtAsymmetry_multiweight->nWeight; iWeight++){
     tmpJacobianAsymmetry->SetBinContent(iWeight + 1, LeptonPtAsymmetry_multiweight->GetHistPtr(iWeight)->GetBinContent(1));
     tmpJacobianAsymmetry->SetBinError(iWeight + 1, LeptonPtAsymmetry_multiweight->GetHistPtr(iWeight)->GetBinError(1));
   }
   TF1* JacobianAsymmetry_fitting;
   double* Par;
   double* ParErr;
   FunctionFitting(tmpJacobianAsymmetry, JacobianAsymmetry_fitting, "[0]*x+[1]", Par, ParErr, 2);
   JacobianAsymmetrySlope->SetBinContent(1, Par[0]);
   JacobianAsymmetrySlope->SetBinError(1, ParErr[0]);
   JacobianAsymmetryOffset->SetBinContent(1, Par[1] - 80.0 * Par[0]);
   JacobianAsymmetryOffset->SetBinError(1, ParErr[1]);

   //LowQT
   MultiWeightHist* LeptonPtAsymmetryLowQT_multiweight = LeptonPt_LowQT_LHC_Low_multiweight->at(0)->GetAsymHist(LeptonPt_LowQT_LHC_High_multiweight->at(0));
   JacobianAsymmetryLowQT = new TH1D("JacobianAsymmetryLowQT", "JacobianAsymmetryLowQT", 21, 80.3265, 80.4315);

   for(int iWeight = 0; iWeight < LeptonPtAsymmetryLowQT_multiweight->nWeight; iWeight++){
     JacobianAsymmetryLowQT->SetBinContent(iWeight + 1, LeptonPtAsymmetryLowQT_multiweight->GetHistPtr(iWeight)->GetBinContent(1));
     JacobianAsymmetryLowQT->SetBinError(iWeight + 1, LeptonPtAsymmetryLowQT_multiweight->GetHistPtr(iWeight)->GetBinError(1));
   }
   JacobianAsymmetryLowQTSlope = new TH1D("JacobianAsymmetryLowQTSlope", "JacobianAsymmetryLowQTSlope", 1, 80.3265, 80.4315);
   JacobianAsymmetryLowQTOffset = new TH1D("JacobianAsymmetryLowQTOffset", "JacobianAsymmetryLowQTOffset", 1, 80.3265, 80.4315);

   TH1D* tmpJacobianAsymmetryLowQT = new TH1D("tmpJacobianAsymmetryLowQT", "tmpJacobianAsymmetryLowQT", 21, 0.3265, 0.4315);
   for(int iWeight = 0; iWeight < LeptonPtAsymmetryLowQT_multiweight->nWeight; iWeight++){
     tmpJacobianAsymmetryLowQT->SetBinContent(iWeight + 1, LeptonPtAsymmetryLowQT_multiweight->GetHistPtr(iWeight)->GetBinContent(1));
     tmpJacobianAsymmetryLowQT->SetBinError(iWeight + 1, LeptonPtAsymmetryLowQT_multiweight->GetHistPtr(iWeight)->GetBinError(1));
   }
   TF1* JacobianAsymmetryLowQT_fitting;
   double* ParLowQT;
   double* ParErrLowQT;
   FunctionFitting(tmpJacobianAsymmetryLowQT, JacobianAsymmetryLowQT_fitting, "[0]*x+[1]", ParLowQT, ParErrLowQT, 2);
   JacobianAsymmetryLowQTSlope->SetBinContent(1, ParLowQT[0]);
   JacobianAsymmetryLowQTSlope->SetBinError(1, ParErrLowQT[0]);
   JacobianAsymmetryLowQTOffset->SetBinContent(1, ParLowQT[1] - 80.0 * ParLowQT[0]);
   JacobianAsymmetryLowQTOffset->SetBinError(1, ParErrLowQT[1]);

   JacobianAsymmetry->Write();
   tmpJacobianAsymmetry->Write();
   JacobianAsymmetrySlope->Write();
   JacobianAsymmetryOffset->Write();

   JacobianAsymmetryLowQT->Write();
   tmpJacobianAsymmetryLowQT->Write();
   JacobianAsymmetryLowQTSlope->Write();
   JacobianAsymmetryLowQTOffset->Write();

   //no QT cut
   LeptonPt_LHC_Pseudodata = GenPseudodataNoFluc(139000.0, LeptonPt_LHC->at(0));
   LeptonPt_LHC_Low_Pseudodata = GenPseudodataNoFluc(139000.0, LeptonPt_LHC_Low->at(0));
   LeptonPt_LHC_High_Pseudodata = GenPseudodataNoFluc(139000.0, LeptonPt_LHC_High->at(0));

   LeptonPt_LHC_Pseudodata->Scale(1.0 / LeptonPt_LHC_Pseudodata->Integral());
   TH1D* LeptonPt_LHC_Pseudodata_Final;
   HistDivideBinWidth(LeptonPt_LHC_Pseudodata, LeptonPt_LHC_Pseudodata_Final);

   JacobianAsymmetry_Data = new TH1D("JacobianAsymmetry_Data", "JacobianAsymmetry_Data", 21, 80.3265, 80.4315);

   TH1D* tmpAsymmetry = (TH1D *)LeptonPt_LHC_Low_Pseudodata->Clone("tmpAsymmetry");
   tmpAsymmetry->Reset();
   AFBFunction(LeptonPt_LHC_Low_Pseudodata, LeptonPt_LHC_High_Pseudodata, tmpAsymmetry);
   for(int ibin = 1; ibin <= JacobianAsymmetry_Data->GetNbinsX(); ibin++){
     JacobianAsymmetry_Data->SetBinContent(ibin, tmpAsymmetry->GetBinContent(1));
     JacobianAsymmetry_Data->SetBinError(ibin, tmpAsymmetry->GetBinError(1));
   }

   //LowQT
   LeptonPt_LowQT_LHC_Pseudodata = GenPseudodataNoFluc(139000.0, LeptonPt_LowQT_LHC->at(0));
   LeptonPt_LowQT_LHC_Tail_Pseudodata = GenPseudodataNoFluc(139000.0, LeptonPt_LowQT_LHC_Tail->at(0));
   LeptonPt_LowQT_LHC_Low_Pseudodata = GenPseudodataNoFluc(139000.0, LeptonPt_LowQT_LHC_Low->at(0));
   LeptonPt_LowQT_LHC_High_Pseudodata = GenPseudodataNoFluc(139000.0, LeptonPt_LowQT_LHC_High->at(0));

   TH1D* LeptonPt_LowQT_LHC_Pseudodata_Final;
   HistDivideBinWidth(LeptonPt_LowQT_LHC_Pseudodata, LeptonPt_LowQT_LHC_Pseudodata_Final);

   JacobianAsymmetryLowQT_Data = new TH1D("JacobianAsymmetryLowQT_Data", "JacobianAsymmetryLowQT_Data", 21, 80.3265, 80.4315);

   TH1D* tmpAsymmetryLowQT = (TH1D *)LeptonPt_LowQT_LHC_Low_Pseudodata->Clone("tmpAsymmetryLowQT");
   tmpAsymmetryLowQT->Reset();
   AFBFunction(LeptonPt_LowQT_LHC_Low_Pseudodata, LeptonPt_LowQT_LHC_High_Pseudodata, tmpAsymmetryLowQT);
   for(int ibin = 1; ibin <= JacobianAsymmetryLowQT_Data->GetNbinsX(); ibin++){
     JacobianAsymmetryLowQT_Data->SetBinContent(ibin, tmpAsymmetryLowQT->GetBinContent(1));
     JacobianAsymmetryLowQT_Data->SetBinError(ibin, tmpAsymmetryLowQT->GetBinError(1));
   }

   MtW_LowQT_LHC_Pseudodata = GenPseudodataNoFluc(139000.0, MtW_LowQT_LHC->at(0));

   //LowQT Z
   LeptonPt_LowQT_Z_LHC_Low_Pseudodata = GenPseudodataNoFluc(139000.0, LeptonPt_LowQT_Z_LHC_Low->at(0));
   LeptonPt_LowQT_Z_LHC_High_Pseudodata = GenPseudodataNoFluc(139000.0, LeptonPt_LowQT_Z_LHC_High->at(0));
   TH1D* JacobianAsymmetryLowQTZ_Data = (TH1D *)LeptonPt_LowQT_Z_LHC_Low_Pseudodata->Clone("JacobianAsymmetryLowQTZ_Data");
   JacobianAsymmetryLowQTZ_Data->Reset();
   AFBFunction(LeptonPt_LowQT_Z_LHC_Low_Pseudodata, LeptonPt_LowQT_Z_LHC_High_Pseudodata, JacobianAsymmetryLowQTZ_Data);

   LeptonPt_LHC_Pseudodata_Final->Write();
   LeptonPt_LHC_Low_Pseudodata->Write();
   LeptonPt_LHC_High_Pseudodata->Write();
   JacobianAsymmetry_Data->Write();

   LeptonPt_LowQT_LHC_Pseudodata->Write();
   LeptonPt_LowQT_LHC_Tail_Pseudodata->Write();
   LeptonPt_LowQT_LHC_Pseudodata_Final->Write();
   LeptonPt_LowQT_LHC_Low_Pseudodata->Write();
   LeptonPt_LowQT_LHC_High_Pseudodata->Write();
   JacobianAsymmetryLowQT_Data->Write();

   MtW_LowQT_LHC_Pseudodata->Write();

   LeptonPt_LowQT_Z_LHC_Low_Pseudodata->Write();
   LeptonPt_LowQT_Z_LHC_High_Pseudodata->Write();
   JacobianAsymmetryLowQTZ_Data->Write();

 }

/* NormalizedWPt_CDF = (TH1D *)WPt_CDF->at(0)->Clone("NormalizedWPt_CDF");
 NormalizedWPt_Inclusive = (TH1D *)WPt_Inclusive->at(0)->Clone("NormalizedWPt_Inclusive");
 NormalizedWPt_CDF->Scale(1.0 / NormalizedWPt_CDF->Integral());
 NormalizedWPt_Inclusive->Scale(1.0 / NormalizedWPt_Inclusive->Integral());

 RatioWZ_CDF = (TH1D *)NormalizedWPt_CDF->Clone("RatioWZ_CDF");
 RatioWZ_CDF->Divide(NormalizedZPt_CDF);
 RatioWZ_Inclusive = (TH1D *)NormalizedWPt_Inclusive->Clone("RatioWZ_Inclusive");
 RatioWZ_Inclusive->Divide(NormalizedZPt_Inclusive);

 RatioWZ_CDF->Write();
 RatioWZ_Inclusive->Write();
*/

}

void HistsResBosWTev::InputData(vector<TString> DataList)
{
 this->DataList = DataList;
}

void HistsResBosWTev::ReadData()
{
 double skip;
 int ibin;

 infile.open(DataList.at(0), ios::in);

 for(int i = 0; i < 6; i++){
   getline(infile, FileLine);
   cout<<FileLine<<endl;
 }
 ibin = 0;
 while(infile >> skip){
   ibin++;
   infile >> skip >> skip >> DataPoint >> StaErr >> SysErr;
   getline(infile, FileLine);
   Data_w225->SetBinContent(ibin, DataPoint);
   Data_w225->SetBinError(ibin, sqrt(StaErr * StaErr + SysErr * SysErr));
 }

 infile.close();

 infile.open(DataList.at(1), ios::in);

 for(int i = 0; i < 6; i++){
   getline(infile, FileLine);
   cout<<FileLine<<endl;
 }
 ibin = 0;
 while(infile >> skip){
   ibin++;
   infile >> skip >> skip >> DataPoint >> StaErr >> SysErr;
   getline(infile, FileLine);
   Data_w227->SetBinContent(ibin, DataPoint);
   Data_w227->SetBinError(ibin, sqrt(StaErr * StaErr + SysErr * SysErr));
 }

 infile.close();

 infile.open(DataList.at(2), ios::in);

 for(int i = 0; i < 6; i++){
   getline(infile, FileLine);
   cout<<FileLine<<endl;
 }
 ibin = 0;
 while(infile >> skip){
   ibin++;
   infile >> skip >> skip >> DataPoint >> StaErr >> SysErr;
   getline(infile, FileLine);
   Data_w234->SetBinContent(ibin, DataPoint);
   Data_w234->SetBinError(ibin, sqrt(StaErr * StaErr + SysErr * SysErr));
 }

 infile.close();

 infile.open(DataList.at(3), ios::in);

 for(int i = 0; i < 6; i++){
   getline(infile, FileLine);
   cout<<FileLine<<endl;
 }
 ibin = 0;
 while(infile >> skip){
   ibin++;
   infile >> skip >> skip >> DataPoint >> StaErr >> TotErr >> SysErr;
   getline(infile, FileLine);
   Data_w281->SetBinContent(ibin, DataPoint);
   Data_w281->SetBinError(ibin, sqrt(StaErr * StaErr + SysErr * SysErr));
 }

 infile.close();

/* TFile *file = new TFile(DataList.at(4));
 NormalizedZPt_CDF = (TH1D *)file->Get("WPt_CDF");
 NormalizedZPt_Inclusive = (TH1D *)file->Get("WPt_Inclusive");
 NormalizedZPt_CDF->Scale(1.0 / NormalizedZPt_CDF->Integral());
 NormalizedZPt_Inclusive->Scale(1.0 / NormalizedZPt_Inclusive->Integral());
*/

}

void HistsResBosWTev::InitialCDFData()
{
   hf->cd();

   MtW_CDF_Data = new TH1D("MtW_CDF_Data", "MtW_CDF_Data", 50, 65, 90);
   MtW_CDF_Data->SetBinContent(1, 36842.1);
   MtW_CDF_Data->SetBinContent(2, 39707.6);
   MtW_CDF_Data->SetBinContent(3, 42163.7);
   MtW_CDF_Data->SetBinContent(4, 44210.5);
   MtW_CDF_Data->SetBinContent(5, 46257.3);
   MtW_CDF_Data->SetBinContent(6, 48713.5);
   MtW_CDF_Data->SetBinContent(7, 50350.9);
   MtW_CDF_Data->SetBinContent(8, 52397.7);
   MtW_CDF_Data->SetBinContent(9, 54444.4);
   MtW_CDF_Data->SetBinContent(10, 55672.5);
   MtW_CDF_Data->SetBinContent(11, 57309.9);
   MtW_CDF_Data->SetBinContent(12, 58538);
   MtW_CDF_Data->SetBinContent(13, 60175.4);
   MtW_CDF_Data->SetBinContent(14, 61403.5);
   MtW_CDF_Data->SetBinContent(15, 62631.6);
   MtW_CDF_Data->SetBinContent(16, 63859.6);
   MtW_CDF_Data->SetBinContent(17, 64678.4);
   MtW_CDF_Data->SetBinContent(18, 65087.7);
   MtW_CDF_Data->SetBinContent(19, 65906.4);
   MtW_CDF_Data->SetBinContent(20, 66315.8);
   MtW_CDF_Data->SetBinContent(21, 66725.1);
   MtW_CDF_Data->SetBinContent(22, 65906.4);
   MtW_CDF_Data->SetBinContent(23, 65497.1);
   MtW_CDF_Data->SetBinContent(24, 65087.7);
   MtW_CDF_Data->SetBinContent(25, 64678.4);
   MtW_CDF_Data->SetBinContent(26, 63450.3);
   MtW_CDF_Data->SetBinContent(27, 61812.9);
   MtW_CDF_Data->SetBinContent(28, 60584.8);
   MtW_CDF_Data->SetBinContent(29, 58947.4);
   MtW_CDF_Data->SetBinContent(30, 56491.2);
   MtW_CDF_Data->SetBinContent(31, 54035.1);
   MtW_CDF_Data->SetBinContent(32, 51578.9);
   MtW_CDF_Data->SetBinContent(33, 48713.5);
   MtW_CDF_Data->SetBinContent(34, 45848);
   MtW_CDF_Data->SetBinContent(35, 42982.5);
   MtW_CDF_Data->SetBinContent(36, 40117);
   MtW_CDF_Data->SetBinContent(37, 37251.5);
   MtW_CDF_Data->SetBinContent(38, 34386);
   MtW_CDF_Data->SetBinContent(39, 31520.5);
   MtW_CDF_Data->SetBinContent(40, 29064.3);
   MtW_CDF_Data->SetBinContent(41, 26608.2);
   MtW_CDF_Data->SetBinContent(42, 24561.4);
   MtW_CDF_Data->SetBinContent(43, 22105.3);
   MtW_CDF_Data->SetBinContent(44, 20058.5);
   MtW_CDF_Data->SetBinContent(45, 18011.7);
   MtW_CDF_Data->SetBinContent(46, 16374.3);
   MtW_CDF_Data->SetBinContent(47, 14736.8);
   MtW_CDF_Data->SetBinContent(48, 13508.8);
   MtW_CDF_Data->SetBinContent(49, 11871.3);
   MtW_CDF_Data->SetBinContent(50, 11052.6);
   for(int ibin = 1; ibin <= MtW_CDF_Data->GetNbinsX(); ibin++){MtW_CDF_Data->SetBinError(ibin, 0.0);}
  
   LeptonPt_CDF_Data = new TH1D("LeptonPt_CDF_Data", "LeptonPt_CDF_Data", 64, 32, 48);
   LeptonPt_CDF_Data->SetBinContent(1, 32982.5);
   LeptonPt_CDF_Data->SetBinContent(2, 34386);
   LeptonPt_CDF_Data->SetBinContent(3, 35438.6);
   LeptonPt_CDF_Data->SetBinContent(4, 36491.2);
   LeptonPt_CDF_Data->SetBinContent(5, 37543.9);
   LeptonPt_CDF_Data->SetBinContent(6, 38596.5);
   LeptonPt_CDF_Data->SetBinContent(7, 40000);
   LeptonPt_CDF_Data->SetBinContent(8, 41052.6);
   LeptonPt_CDF_Data->SetBinContent(9, 42105.3);
   LeptonPt_CDF_Data->SetBinContent(10, 43508.8);
   LeptonPt_CDF_Data->SetBinContent(11, 44561.4);
   LeptonPt_CDF_Data->SetBinContent(12, 45614);
   LeptonPt_CDF_Data->SetBinContent(13, 47017.5);
   LeptonPt_CDF_Data->SetBinContent(14, 47719.3);
   LeptonPt_CDF_Data->SetBinContent(15, 49122.8);
   LeptonPt_CDF_Data->SetBinContent(16, 49824.6);
   LeptonPt_CDF_Data->SetBinContent(17, 51228.1);
   LeptonPt_CDF_Data->SetBinContent(18, 52280.7);
   LeptonPt_CDF_Data->SetBinContent(19, 52982.5);
   LeptonPt_CDF_Data->SetBinContent(20, 54035.1);
   LeptonPt_CDF_Data->SetBinContent(21, 54736.8);
   LeptonPt_CDF_Data->SetBinContent(22, 55438.6);
   LeptonPt_CDF_Data->SetBinContent(23, 56140.4);
   LeptonPt_CDF_Data->SetBinContent(24, 56491.2);
   LeptonPt_CDF_Data->SetBinContent(25, 56842.1);
   LeptonPt_CDF_Data->SetBinContent(26, 56842.1);
   LeptonPt_CDF_Data->SetBinContent(27, 56491.2);
   LeptonPt_CDF_Data->SetBinContent(28, 55789.5);
   LeptonPt_CDF_Data->SetBinContent(29, 55087.7);
   LeptonPt_CDF_Data->SetBinContent(30, 53684.2);
   LeptonPt_CDF_Data->SetBinContent(31, 52631.6);
   LeptonPt_CDF_Data->SetBinContent(32, 50877.2);
   LeptonPt_CDF_Data->SetBinContent(33, 48771.9);
   LeptonPt_CDF_Data->SetBinContent(34, 46666.7);
   LeptonPt_CDF_Data->SetBinContent(35, 43859.6);
   LeptonPt_CDF_Data->SetBinContent(36, 41403.5);
   LeptonPt_CDF_Data->SetBinContent(37, 38947.4);
   LeptonPt_CDF_Data->SetBinContent(38, 36491.2);
   LeptonPt_CDF_Data->SetBinContent(39, 34035.1);
   LeptonPt_CDF_Data->SetBinContent(40, 31578.9);
   LeptonPt_CDF_Data->SetBinContent(41, 29122.8);
   LeptonPt_CDF_Data->SetBinContent(42, 27368.4);
   LeptonPt_CDF_Data->SetBinContent(43, 25263.2);
   LeptonPt_CDF_Data->SetBinContent(44, 23157.9);
   LeptonPt_CDF_Data->SetBinContent(45, 21754.4);
   LeptonPt_CDF_Data->SetBinContent(46, 20000);
   LeptonPt_CDF_Data->SetBinContent(47, 18596.5);
   LeptonPt_CDF_Data->SetBinContent(48, 17193);
   LeptonPt_CDF_Data->SetBinContent(49, 15789.5);
   LeptonPt_CDF_Data->SetBinContent(50, 14736.8);
   LeptonPt_CDF_Data->SetBinContent(51, 13684.2);
   LeptonPt_CDF_Data->SetBinContent(52, 12631.6);
   LeptonPt_CDF_Data->SetBinContent(53, 11578.9);
   LeptonPt_CDF_Data->SetBinContent(54, 10877.2);
   LeptonPt_CDF_Data->SetBinContent(55, 10175.4);
   LeptonPt_CDF_Data->SetBinContent(56, 9122.81);
   LeptonPt_CDF_Data->SetBinContent(57, 8771.93);
   LeptonPt_CDF_Data->SetBinContent(58, 7719.3);
   LeptonPt_CDF_Data->SetBinContent(59, 7368.42);
   LeptonPt_CDF_Data->SetBinContent(60, 6666.67);
   LeptonPt_CDF_Data->SetBinContent(61, 5964.91);
   LeptonPt_CDF_Data->SetBinContent(62, 5614.04);
   LeptonPt_CDF_Data->SetBinContent(63, 5263.16);
   LeptonPt_CDF_Data->SetBinContent(64, 4912.28);
   for(int ibin = 1; ibin <= LeptonPt_CDF_Data->GetNbinsX(); ibin++){LeptonPt_CDF_Data->SetBinError(ibin, 0.0);}
  
   NuPt_CDF_Data = new TH1D("NuPt_CDF_Data", "NuPt_CDF_Data", 64, 32, 48);
   NuPt_CDF_Data->SetBinContent(1, 34280);
   NuPt_CDF_Data->SetBinContent(2, 35190.1);
   NuPt_CDF_Data->SetBinContent(3, 36403.5);
   NuPt_CDF_Data->SetBinContent(4, 37313.6);
   NuPt_CDF_Data->SetBinContent(5, 38527);
   NuPt_CDF_Data->SetBinContent(6, 39437.1);
   NuPt_CDF_Data->SetBinContent(7, 40347.2);
   NuPt_CDF_Data->SetBinContent(8, 41560.7);
   NuPt_CDF_Data->SetBinContent(9, 42167.4);
   NuPt_CDF_Data->SetBinContent(10, 43077.5);
   NuPt_CDF_Data->SetBinContent(11, 43684.2);
   NuPt_CDF_Data->SetBinContent(12, 44594.3);
   NuPt_CDF_Data->SetBinContent(13, 45504.4);
   NuPt_CDF_Data->SetBinContent(14, 46111.1);
   NuPt_CDF_Data->SetBinContent(15, 46717.8);
   NuPt_CDF_Data->SetBinContent(16, 47324.6);
   NuPt_CDF_Data->SetBinContent(17, 47627.9);
   NuPt_CDF_Data->SetBinContent(18, 48234.6);
   NuPt_CDF_Data->SetBinContent(19, 48538);
   NuPt_CDF_Data->SetBinContent(20, 48841.4);
   NuPt_CDF_Data->SetBinContent(21, 49144.7);
   NuPt_CDF_Data->SetBinContent(22, 49144.7);
   NuPt_CDF_Data->SetBinContent(23, 49144.7);
   NuPt_CDF_Data->SetBinContent(24, 49144.7);
   NuPt_CDF_Data->SetBinContent(25, 48841.4);
   NuPt_CDF_Data->SetBinContent(26, 48234.6);
   NuPt_CDF_Data->SetBinContent(27, 47931.3);
   NuPt_CDF_Data->SetBinContent(28, 47627.9);
   NuPt_CDF_Data->SetBinContent(29, 46717.8);
   NuPt_CDF_Data->SetBinContent(30, 45807.7);
   NuPt_CDF_Data->SetBinContent(31, 44897.7);
   NuPt_CDF_Data->SetBinContent(32, 43987.6);
   NuPt_CDF_Data->SetBinContent(33, 42774.1);
   NuPt_CDF_Data->SetBinContent(34, 41560.7);
   NuPt_CDF_Data->SetBinContent(35, 40347.2);
   NuPt_CDF_Data->SetBinContent(36, 38830.4);
   NuPt_CDF_Data->SetBinContent(37, 37313.6);
   NuPt_CDF_Data->SetBinContent(38, 35796.8);
   NuPt_CDF_Data->SetBinContent(39, 34583.3);
   NuPt_CDF_Data->SetBinContent(40, 32763.2);
   NuPt_CDF_Data->SetBinContent(41, 31549.7);
   NuPt_CDF_Data->SetBinContent(42, 29729.5);
   NuPt_CDF_Data->SetBinContent(43, 28516.1);
   NuPt_CDF_Data->SetBinContent(44, 26695.9);
   NuPt_CDF_Data->SetBinContent(45, 25179.1);
   NuPt_CDF_Data->SetBinContent(46, 23965.6);
   NuPt_CDF_Data->SetBinContent(47, 22448.8);
   NuPt_CDF_Data->SetBinContent(48, 21235.4);
   NuPt_CDF_Data->SetBinContent(49, 20021.9);
   NuPt_CDF_Data->SetBinContent(50, 18808.5);
   NuPt_CDF_Data->SetBinContent(51, 17595);
   NuPt_CDF_Data->SetBinContent(52, 16381.6);
   NuPt_CDF_Data->SetBinContent(53, 15168.1);
   NuPt_CDF_Data->SetBinContent(54, 14258);
   NuPt_CDF_Data->SetBinContent(55, 13348);
   NuPt_CDF_Data->SetBinContent(56, 12437.9);
   NuPt_CDF_Data->SetBinContent(57, 11527.8);
   NuPt_CDF_Data->SetBinContent(58, 10617.7);
   NuPt_CDF_Data->SetBinContent(59, 9707.6);
   NuPt_CDF_Data->SetBinContent(60, 9100.88);
   NuPt_CDF_Data->SetBinContent(61, 8190.79);
   NuPt_CDF_Data->SetBinContent(62, 7584.06);
   NuPt_CDF_Data->SetBinContent(63, 6977.34);
   NuPt_CDF_Data->SetBinContent(64, 6370.61);
   for(int ibin = 1; ibin <= NuPt_CDF_Data->GetNbinsX(); ibin++){NuPt_CDF_Data->SetBinError(ibin, 0.0);}

   MtW_CDF_Data->Write();
   LeptonPt_CDF_Data->Write();
   NuPt_CDF_Data->Write();

   MtW_CDF_Electron = new TH1D("MtW_CDF_Electron", "MtW_CDF_Electron", 50, 65, 90);
   MtW_CDF_Electron->SetBinContent(1, 26644.1);
   MtW_CDF_Electron->SetBinContent(2, 28532.7);
   MtW_CDF_Electron->SetBinContent(3, 30219.1);
   MtW_CDF_Electron->SetBinContent(4, 31905.4);
   MtW_CDF_Electron->SetBinContent(5, 33524.3);
   MtW_CDF_Electron->SetBinContent(6, 35210.6);
   MtW_CDF_Electron->SetBinContent(7, 36559.7);
   MtW_CDF_Electron->SetBinContent(8, 38043.7);
   MtW_CDF_Electron->SetBinContent(9, 39325.3);
   MtW_CDF_Electron->SetBinContent(10, 40539.4);
   MtW_CDF_Electron->SetBinContent(11, 41551.2);
   MtW_CDF_Electron->SetBinContent(12, 42563);
   MtW_CDF_Electron->SetBinContent(13, 43507.4);
   MtW_CDF_Electron->SetBinContent(14, 44181.9);
   MtW_CDF_Electron->SetBinContent(15, 45126.3);
   MtW_CDF_Electron->SetBinContent(16, 45665.9);
   MtW_CDF_Electron->SetBinContent(17, 46003.1);
   MtW_CDF_Electron->SetBinContent(18, 46273);
   MtW_CDF_Electron->SetBinContent(19, 46475.3);
   MtW_CDF_Electron->SetBinContent(20, 46475.3);
   MtW_CDF_Electron->SetBinContent(21, 46340.4);
   MtW_CDF_Electron->SetBinContent(22, 45935.7);
   MtW_CDF_Electron->SetBinContent(23, 45531);
   MtW_CDF_Electron->SetBinContent(24, 45126.3);
   MtW_CDF_Electron->SetBinContent(25, 44384.3);
   MtW_CDF_Electron->SetBinContent(26, 43439.9);
   MtW_CDF_Electron->SetBinContent(27, 42495.6);
   MtW_CDF_Electron->SetBinContent(28, 41146.5);
   MtW_CDF_Electron->SetBinContent(29, 39662.5);
   MtW_CDF_Electron->SetBinContent(30, 38111.1);
   MtW_CDF_Electron->SetBinContent(31, 36357.3);
   MtW_CDF_Electron->SetBinContent(32, 34603.5);
   MtW_CDF_Electron->SetBinContent(33, 32714.8);
   MtW_CDF_Electron->SetBinContent(34, 30893.6);
   MtW_CDF_Electron->SetBinContent(35, 28870);
   MtW_CDF_Electron->SetBinContent(36, 27116.2);
   MtW_CDF_Electron->SetBinContent(37, 24957.7);
   MtW_CDF_Electron->SetBinContent(38, 23069);
   MtW_CDF_Electron->SetBinContent(39, 21315.2);
   MtW_CDF_Electron->SetBinContent(40, 19696.4);
   MtW_CDF_Electron->SetBinContent(41, 17942.6);
   MtW_CDF_Electron->SetBinContent(42, 16121.3);
   MtW_CDF_Electron->SetBinContent(43, 14772.3);
   MtW_CDF_Electron->SetBinContent(44, 13220.8);
   MtW_CDF_Electron->SetBinContent(45, 11939.2);
   MtW_CDF_Electron->SetBinContent(46, 10792.5);
   MtW_CDF_Electron->SetBinContent(47, 9780.73);
   MtW_CDF_Electron->SetBinContent(48, 8836.38);
   MtW_CDF_Electron->SetBinContent(49, 7959.49);
   MtW_CDF_Electron->SetBinContent(50, 7217.5);
   for(int ibin = 1; ibin <= MtW_CDF_Electron->GetNbinsX(); ibin++){MtW_CDF_Electron->SetBinError(ibin, 0.0);}

   LeptonPt_CDF_Electron = new TH1D("LeptonPt_CDF_Electron", "LeptonPt_CDF_Electron", 64, 32, 48);
   LeptonPt_CDF_Electron->SetBinContent(1, 24656);
   LeptonPt_CDF_Electron->SetBinContent(2, 25593.1);
   LeptonPt_CDF_Electron->SetBinContent(3, 26471.5);
   LeptonPt_CDF_Electron->SetBinContent(4, 27408.6);
   LeptonPt_CDF_Electron->SetBinContent(5, 28287.1);
   LeptonPt_CDF_Electron->SetBinContent(6, 29165.5);
   LeptonPt_CDF_Electron->SetBinContent(7, 30161.1);
   LeptonPt_CDF_Electron->SetBinContent(8, 30981.1);
   LeptonPt_CDF_Electron->SetBinContent(9, 31859.5);
   LeptonPt_CDF_Electron->SetBinContent(10, 32855.2);
   LeptonPt_CDF_Electron->SetBinContent(11, 33675.1);
   LeptonPt_CDF_Electron->SetBinContent(12, 34495);
   LeptonPt_CDF_Electron->SetBinContent(13, 35314.9);
   LeptonPt_CDF_Electron->SetBinContent(14, 36076.2);
   LeptonPt_CDF_Electron->SetBinContent(15, 37013.3);
   LeptonPt_CDF_Electron->SetBinContent(16, 37540.4);
   LeptonPt_CDF_Electron->SetBinContent(17, 38477.4);
   LeptonPt_CDF_Electron->SetBinContent(18, 39063.1);
   LeptonPt_CDF_Electron->SetBinContent(19, 39883);
   LeptonPt_CDF_Electron->SetBinContent(20, 40351.5);
   LeptonPt_CDF_Electron->SetBinContent(21, 40820);
   LeptonPt_CDF_Electron->SetBinContent(22, 41347.1);
   LeptonPt_CDF_Electron->SetBinContent(23, 41640);
   LeptonPt_CDF_Electron->SetBinContent(24, 41698.5);
   LeptonPt_CDF_Electron->SetBinContent(25, 41815.6);
   LeptonPt_CDF_Electron->SetBinContent(26, 41581.4);
   LeptonPt_CDF_Electron->SetBinContent(27, 41405.7);
   LeptonPt_CDF_Electron->SetBinContent(28, 40937.2);
   LeptonPt_CDF_Electron->SetBinContent(29, 40410.1);
   LeptonPt_CDF_Electron->SetBinContent(30, 39473);
   LeptonPt_CDF_Electron->SetBinContent(31, 38301.7);
   LeptonPt_CDF_Electron->SetBinContent(32, 37130.4);
   LeptonPt_CDF_Electron->SetBinContent(33, 35666.3);
   LeptonPt_CDF_Electron->SetBinContent(34, 34085);
   LeptonPt_CDF_Electron->SetBinContent(35, 32562.3);
   LeptonPt_CDF_Electron->SetBinContent(36, 30688.2);
   LeptonPt_CDF_Electron->SetBinContent(37, 29165.5);
   LeptonPt_CDF_Electron->SetBinContent(38, 26998.6);
   LeptonPt_CDF_Electron->SetBinContent(39, 25300.2);
   LeptonPt_CDF_Electron->SetBinContent(40, 23660.4);
   LeptonPt_CDF_Electron->SetBinContent(41, 21786.3);
   LeptonPt_CDF_Electron->SetBinContent(42, 20087.9);
   LeptonPt_CDF_Electron->SetBinContent(43, 18740.9);
   LeptonPt_CDF_Electron->SetBinContent(44, 17101.1);
   LeptonPt_CDF_Electron->SetBinContent(45, 15812.6);
   LeptonPt_CDF_Electron->SetBinContent(46, 14465.6);
   LeptonPt_CDF_Electron->SetBinContent(47, 13470);
   LeptonPt_CDF_Electron->SetBinContent(48, 12357.3);
   LeptonPt_CDF_Electron->SetBinContent(49, 11420.2);
   LeptonPt_CDF_Electron->SetBinContent(50, 10600.3);
   LeptonPt_CDF_Electron->SetBinContent(51, 9721.85);
   LeptonPt_CDF_Electron->SetBinContent(52, 8960.5);
   LeptonPt_CDF_Electron->SetBinContent(53, 8316.28);
   LeptonPt_CDF_Electron->SetBinContent(54, 7672.06);
   LeptonPt_CDF_Electron->SetBinContent(55, 7027.84);
   LeptonPt_CDF_Electron->SetBinContent(56, 6500.75);
   LeptonPt_CDF_Electron->SetBinContent(57, 5973.66);
   LeptonPt_CDF_Electron->SetBinContent(58, 5563.71);
   LeptonPt_CDF_Electron->SetBinContent(59, 5095.18);
   LeptonPt_CDF_Electron->SetBinContent(60, 4626.66);
   LeptonPt_CDF_Electron->SetBinContent(61, 4216.7);
   LeptonPt_CDF_Electron->SetBinContent(62, 3865.31);
   LeptonPt_CDF_Electron->SetBinContent(63, 3631.05);
   LeptonPt_CDF_Electron->SetBinContent(64, 3396.79);
   for(int ibin = 1; ibin <= LeptonPt_CDF_Electron->GetNbinsX(); ibin++){LeptonPt_CDF_Electron->SetBinError(ibin, 0.0);}

   NuPt_CDF_Electron = new TH1D("NuPt_CDF_Electron", "NuPt_CDF_Electron", 64, 32, 48);
   NuPt_CDF_Electron->SetBinContent(1, 26603.7);
   NuPt_CDF_Electron->SetBinContent(2, 27375.6);
   NuPt_CDF_Electron->SetBinContent(3, 28250.4);
   NuPt_CDF_Electron->SetBinContent(4, 29022.3);
   NuPt_CDF_Electron->SetBinContent(5, 29845.6);
   NuPt_CDF_Electron->SetBinContent(6, 30411.6);
   NuPt_CDF_Electron->SetBinContent(7, 31080.6);
   NuPt_CDF_Electron->SetBinContent(8, 31801);
   NuPt_CDF_Electron->SetBinContent(9, 32418.5);
   NuPt_CDF_Electron->SetBinContent(10, 33138.9);
   NuPt_CDF_Electron->SetBinContent(11, 33653.5);
   NuPt_CDF_Electron->SetBinContent(12, 34219.5);
   NuPt_CDF_Electron->SetBinContent(13, 34682.6);
   NuPt_CDF_Electron->SetBinContent(14, 35197.2);
   NuPt_CDF_Electron->SetBinContent(15, 35660.3);
   NuPt_CDF_Electron->SetBinContent(16, 36020.5);
   NuPt_CDF_Electron->SetBinContent(17, 36329.3);
   NuPt_CDF_Electron->SetBinContent(18, 36638);
   NuPt_CDF_Electron->SetBinContent(19, 36740.9);
   NuPt_CDF_Electron->SetBinContent(20, 36895.3);
   NuPt_CDF_Electron->SetBinContent(21, 36998.2);
   NuPt_CDF_Electron->SetBinContent(22, 36843.9);
   NuPt_CDF_Electron->SetBinContent(23, 36843.9);
   NuPt_CDF_Electron->SetBinContent(24, 36586.6);
   NuPt_CDF_Electron->SetBinContent(25, 36329.3);
   NuPt_CDF_Electron->SetBinContent(26, 35917.6);
   NuPt_CDF_Electron->SetBinContent(27, 35505.9);
   NuPt_CDF_Electron->SetBinContent(28, 34991.4);
   NuPt_CDF_Electron->SetBinContent(29, 34373.9);
   NuPt_CDF_Electron->SetBinContent(30, 33653.5);
   NuPt_CDF_Electron->SetBinContent(31, 32778.7);
   NuPt_CDF_Electron->SetBinContent(32, 32109.7);
   NuPt_CDF_Electron->SetBinContent(33, 31183.5);
   NuPt_CDF_Electron->SetBinContent(34, 30102.9);
   NuPt_CDF_Electron->SetBinContent(35, 29279.5);
   NuPt_CDF_Electron->SetBinContent(36, 28096);
   NuPt_CDF_Electron->SetBinContent(37, 27015.4);
   NuPt_CDF_Electron->SetBinContent(38, 26037.7);
   NuPt_CDF_Electron->SetBinContent(39, 24802.7);
   NuPt_CDF_Electron->SetBinContent(40, 23722.1);
   NuPt_CDF_Electron->SetBinContent(41, 22641.5);
   NuPt_CDF_Electron->SetBinContent(42, 21406.5);
   NuPt_CDF_Electron->SetBinContent(43, 20274.4);
   NuPt_CDF_Electron->SetBinContent(44, 19451.1);
   NuPt_CDF_Electron->SetBinContent(45, 18216.1);
   NuPt_CDF_Electron->SetBinContent(46, 17238.4);
   NuPt_CDF_Electron->SetBinContent(47, 16157.8);
   NuPt_CDF_Electron->SetBinContent(48, 15180.1);
   NuPt_CDF_Electron->SetBinContent(49, 14305.3);
   NuPt_CDF_Electron->SetBinContent(50, 13327.6);
   NuPt_CDF_Electron->SetBinContent(51, 12401.4);
   NuPt_CDF_Electron->SetBinContent(52, 11526.6);
   NuPt_CDF_Electron->SetBinContent(53, 10960.5);
   NuPt_CDF_Electron->SetBinContent(54, 10137.2);
   NuPt_CDF_Electron->SetBinContent(55, 9468.25);
   NuPt_CDF_Electron->SetBinContent(56, 8747.84);
   NuPt_CDF_Electron->SetBinContent(57, 8027.43);
   NuPt_CDF_Electron->SetBinContent(58, 7461.39);
   NuPt_CDF_Electron->SetBinContent(59, 6895.36);
   NuPt_CDF_Electron->SetBinContent(60, 6277.86);
   NuPt_CDF_Electron->SetBinContent(61, 5866.2);
   NuPt_CDF_Electron->SetBinContent(62, 5351.62);
   NuPt_CDF_Electron->SetBinContent(63, 4991.42);
   NuPt_CDF_Electron->SetBinContent(64, 4631.21);
   for(int ibin = 1; ibin <= NuPt_CDF_Electron->GetNbinsX(); ibin++){NuPt_CDF_Electron->SetBinError(ibin, 0.0);}

   MtW_CDF_Electron->Write();
   LeptonPt_CDF_Electron->Write();
   NuPt_CDF_Electron->Write();

}
