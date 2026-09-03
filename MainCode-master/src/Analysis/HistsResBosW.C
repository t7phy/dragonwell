#include "Analysis/HistsResBosW.h"

using namespace std;

void HistsResBosW::bookHists(int TotalThread)
{
 double rangeZPt[24] = {0,2.5,5,8,11.4,14.9,18.5,22,25.5,29,32.6,36.4,40.4,44.9,50.2,56.4,63.9,73.4,85.4,105,132,173,253,600};
 double rangeEtaAbs[5] = {0, 1, 2, 3, 5};
 double rangeMET[6] = {25, 35, 45, 55, 65, 100};
 double rangeWPt[6] = {0, 2, 4, 6, 8, 10};
 double rangeWE[6] = {0, 200, 400, 600, 800, 1000};

 this->TotalThread = TotalThread;

   BookHist(LeptonEtaAbs, "LeptonEtaAbs", "LeptonEtaAbs", 20, 0, 5);
   BookHist(AntiLeptonEtaAbs, "AntiLeptonEtaAbs", "AntiLeptonEtaAbs", 20, 0, 5);

   BookHist(LeptonEtaAbs_pt35, "LeptonEtaAbs_pt35", "LeptonEtaAbs_pt35", 250, 0, 2.5);
   BookHist(AntiLeptonEtaAbs_pt35, "AntiLeptonEtaAbs_pt35", "AntiLeptonEtaAbs_pt35", 250, 0, 2.5);

   BookHist(LeptonEtaAbs_pt25_35, "LeptonEtaAbs_pt25_35", "LeptonEtaAbs_pt25_35", 250, 0, 2.5);
   BookHist(AntiLeptonEtaAbs_pt25_35, "AntiLeptonEtaAbs_pt25_35", "AntiLeptonEtaAbs_pt25_35", 250, 0, 2.5);

   Book2DHist(LeptonEtaAbs2D, "LeptonEtaAbs2D", "LeptonEtaAbs2D", 25, 0, 2.5, 20, 0, 100);
   Book2DHist(AntiLeptonEtaAbs2D, "AntiLeptonEtaAbs2D", "AntiLeptonEtaAbs2D", 25, 0, 2.5, 20, 0, 100);

   Book2DHist(LeptonEtaAbs_MT2D, "LeptonEtaAbs_MT2D", "LeptonEtaAbs_MT2D", 25, 0, 2.5, 1, 50, 80);
   Book2DHist(AntiLeptonEtaAbs_MT2D, "AntiLeptonEtaAbs_MT2D", "AntiLeptonEtaAbs_MT2D", 25, 0, 2.5, 1, 50, 80);

   Book2DHist(LeptonEtaAbs_ut2D, "LeptonEtaAbs_ut2D", "LeptonEtaAbs_ut2D", 25, 0, 2.5, 1, 0, 5);
   Book2DHist(AntiLeptonEtaAbs_ut2D, "AntiLeptonEtaAbs_ut2D", "AntiLeptonEtaAbs_ut2D", 25, 0, 2.5, 1, 0, 5);

   Book3DHist(LeptonEtaAbs3D_cut30, "LeptonEtaAbs3D_cut30", "LeptonEtaAbs3D_cut30", 25, 0, 2.5, 1, 25, 30, 1, 25, 30);
   Book3DHist(AntiLeptonEtaAbs3D_cut30, "AntiLeptonEtaAbs3D_cut30", "AntiLeptonEtaAbs3D_cut30", 25, 0, 2.5, 1, 25, 30, 1, 25, 30);

   Book3DHist(LeptonEtaAbs3D_cut35, "LeptonEtaAbs3D_cut35", "LeptonEtaAbs3D_cut35", 25, 0, 2.5, 1, 25, 35, 1, 25, 35);
   Book3DHist(AntiLeptonEtaAbs3D_cut35, "AntiLeptonEtaAbs3D_cut35", "AntiLeptonEtaAbs3D_cut35", 25, 0, 2.5, 1, 25, 35, 1, 25, 35);

   Book3DHist(LeptonEtaAbs3D_cut40, "LeptonEtaAbs3D_cut40", "LeptonEtaAbs3D_cut40", 25, 0, 2.5, 1, 25, 40, 1, 25, 40);
   Book3DHist(AntiLeptonEtaAbs3D_cut40, "AntiLeptonEtaAbs3D_cut40", "AntiLeptonEtaAbs3D_cut40", 25, 0, 2.5, 1, 25, 40, 1, 25, 40);

   BookHist(LeptonEtaAbs_LHCb, "LeptonEtaAbs_LHCb", "LeptonEtaAbs_LHCb", 18, 2.0, 4.5);
   BookHist(AntiLeptonEtaAbs_LHCb, "AntiLeptonEtaAbs_LHCb", "AntiLeptonEtaAbs_LHCb", 18, 2.0, 4.5);

   BookHist(WPlusRapidity, "WPlusRapidity", "WPlusRapidity", 20, -5.0, 5.0);
   BookHist(WMinusRapidity, "WMinusRapidity", "WMinusRapidity", 20, -5.0, 5.0);
   BookHist(WPlusPt, "WPlusPt", "WPlusPt", 20, 0.0, 100.0);
   BookHist(WMinusPt, "WMinusPt", "WMinusPt", 20, 0.0, 100.0);
   BookHist(WPlusE, "WPlusE", "WPlusE", 20, 0.0, 1000.0);
   BookHist(WMinusE, "WMinusE", "WMinusE", 20, 0.0, 1000.0);
   Book2DHist(WPlusYPt, "WPlusYPt", "WPlusYPt", 4, rangeEtaAbs, 5, rangeWPt);
   Book2DHist(WMinusYPt, "WMinusYPt", "WMinusYPt", 4, rangeEtaAbs, 5, rangeWPt);
   Book2DHist(WPlusYE, "WPlusYE", "WPlusYE", 4, rangeEtaAbs, 5, rangeWE);
   Book2DHist(WMinusYE, "WMinusYE", "WMinusYE", 4, rangeEtaAbs, 5, rangeWE);

   BookHist(LeptonEta, "LeptonEta", "LeptonEta", 20, -5.0, 5.0);
   BookHist(AntiLeptonEta, "AntiLeptonEta", "AntiLeptonEta", 20, -5.0, 5.0);

   Book2DHist(LeptonEtaMET, "LeptonEtaMET", "LeptonEtaMET", 4, rangeEtaAbs, 5, rangeMET);
   Book2DHist(AntiLeptonEtaMET, "AntiLeptonEtaMET", "AntiLeptonEtaMET", 4, rangeEtaAbs, 5, rangeMET);

   BookHist(WPlusMET, "WPlusMET", "WPlusMET", 20, 25, 100);
   BookHist(WMinusMET, "WMinusMET", "WMinusMET", 20, 25, 100);

   BookHist(WPlusMET_LowEta, "WPlusMET_LowEta", "WPlusMET_LowEta", 20, 25, 100);
   BookHist(WMinusMET_LowEta, "WMinusMET_LowEta", "WMinusMET_LowEta", 20, 25, 100);

   BookHist(WPlusMET_HighEta, "WPlusMET_HighEta", "WPlusMET_HighEta", 20, 25, 100);
   BookHist(WMinusMET_HighEta, "WMinusMET_HighEta", "WMinusMET_HighEta", 20, 25, 100);

   BookHist(LeptonPt, "LeptonPt", "LeptonPt", 20, 25, 100);
   BookHist(AntiLeptonPt, "AntiLeptonPt", "AntiLeptonPt", 20, 25, 100);

   BookHist(LeptonPt_LowEta, "LeptonPt_LowEta", "LeptonPt_LowEta", 20, 25, 100);
   BookHist(AntiLeptonPt_LowEta, "AntiLeptonPt_LowEta", "AntiLeptonPt_LowEta", 20, 25, 100);

   BookHist(LeptonPt_HighEta, "LeptonPt_HighEta", "LeptonPt_HighEta", 20, 25, 100);
   BookHist(AntiLeptonPt_HighEta, "AntiLeptonPt_HighEta", "AntiLeptonPt_HighEta", 20, 25, 100);

   Book2DHist(LeptonEtaPt, "LeptonEtaPt", "LeptonEtaPt", 4, rangeEtaAbs, 5, rangeMET);
   Book2DHist(AntiLeptonEtaPt, "AntiLeptonEtaPt", "AntiLeptonEtaPt", 4, rangeEtaAbs, 5, rangeMET);

   BookHist(E605_Q1, "E605_Q1", "E605_Q1", 6, -0.25, 0.35);
   BookHist(E605_Q2, "E605_Q2", "E605_Q2", 6, -0.25, 0.35);
   BookHist(E605_Q3, "E605_Q3", "E605_Q3", 6, -0.25, 0.35);
   BookHist(E605_Q4, "E605_Q4", "E605_Q4", 6, -0.25, 0.35);
   BookHist(E605_Q5, "E605_Q5", "E605_Q5", 6, -0.25, 0.35);
   BookHist(E605_Q6, "E605_Q6", "E605_Q6", 6, -0.25, 0.35);
   BookHist(E605_Q7, "E605_Q7", "E605_Q7", 7, -0.25, 0.45);
   BookHist(E605_Q8, "E605_Q8", "E605_Q8", 7, -0.25, 0.45);
   BookHist(E605_Q9, "E605_Q9", "E605_Q9", 7, -0.25, 0.45);
   BookHist(E605_Q10, "E605_Q10", "E605_Q10", 7, -0.25, 0.45);
   BookHist(E605_Q11, "E605_Q11", "E605_Q11", 7, -0.25, 0.45);
   BookHist(E605_Q12, "E605_Q12", "E605_Q12", 7, -0.25, 0.45);
   BookHist(E605_Q13, "E605_Q13", "E605_Q13", 7, -0.25, 0.45);
   BookHist(E605_Q14, "E605_Q14", "E605_Q14", 7, -0.25, 0.45);
   BookHist(E605_Q15, "E605_Q15", "E605_Q15", 7, -0.25, 0.45);
   BookHist(E605_Q16, "E605_Q16", "E605_Q16", 7, -0.25, 0.45);
   BookHist(E605_Q17, "E605_Q17", "E605_Q17", 7, -0.25, 0.45);
   BookHist(E605_Q18, "E605_Q18", "E605_Q18", 6, -0.15, 0.45);

}

void HistsResBosW::outputInformation()
{
 HistDivideBinWidth(E605_Q1->at(0), E605_Q1_Final, 0.2 / pow(7.1, 3) * 1000.0);
 HistDivideBinWidth(E605_Q2->at(0), E605_Q2_Final, 0.2 / pow(7.31, 3) * 1000.0);
 HistDivideBinWidth(E605_Q3->at(0), E605_Q3_Final, 0.2 / pow(7.51, 3) * 1000.0);
 HistDivideBinWidth(E605_Q4->at(0), E605_Q4_Final, 0.2 / pow(7.71, 3) * 1000.0);
 HistDivideBinWidth(E605_Q5->at(0), E605_Q5_Final, 0.2 / pow(7.91, 3) * 1000.0);
 HistDivideBinWidth(E605_Q6->at(0), E605_Q6_Final, 0.2 / pow(8.11, 3) * 1000.0);
 HistDivideBinWidth(E605_Q7->at(0), E605_Q7_Final, 0.2 / pow(8.31, 3) * 1000.0);
 HistDivideBinWidth(E605_Q8->at(0), E605_Q8_Final, 0.2 / pow(8.50, 3) * 1000.0);
 HistDivideBinWidth(E605_Q9->at(0), E605_Q9_Final, 0.2 / pow(8.71, 3) * 1000.0);
 HistDivideBinWidth(E605_Q10->at(0), E605_Q10_Final, 0.2 / pow(8.91, 3) * 1000.0);
 HistDivideBinWidth(E605_Q11->at(0), E605_Q11_Final, 0.2 / pow(10.51, 3) * 1000.0);
 HistDivideBinWidth(E605_Q12->at(0), E605_Q12_Final, 0.2 / pow(10.71, 3) * 1000.0);
 HistDivideBinWidth(E605_Q13->at(0), E605_Q13_Final, 0.2 / pow(10.91, 3) * 1000.0);
 HistDivideBinWidth(E605_Q14->at(0), E605_Q14_Final, 0.2 / pow(11.31, 3) * 1000.0);
 HistDivideBinWidth(E605_Q15->at(0), E605_Q15_Final, 0.2 / pow(12.11, 3) * 1000.0);
 HistDivideBinWidth(E605_Q16->at(0), E605_Q16_Final, 0.2 / pow(13.31, 3) * 1000.0);
 HistDivideBinWidth(E605_Q17->at(0), E605_Q17_Final, 0.2 / pow(14.91, 3) * 1000.0);
 HistDivideBinWidth(E605_Q18->at(0), E605_Q18_Final, 0.2 / pow(16.91, 3) * 1000.0);

 E605_Q1_Final->Write();
 E605_Q2_Final->Write();
 E605_Q3_Final->Write();
 E605_Q4_Final->Write();
 E605_Q5_Final->Write();
 E605_Q6_Final->Write();
 E605_Q7_Final->Write();
 E605_Q8_Final->Write();
 E605_Q9_Final->Write();
 E605_Q10_Final->Write();
 E605_Q11_Final->Write();
 E605_Q12_Final->Write();
 E605_Q13_Final->Write();
 E605_Q14_Final->Write();
 E605_Q15_Final->Write();
 E605_Q16_Final->Write();
 E605_Q17_Final->Write();
 E605_Q18_Final->Write();

}

