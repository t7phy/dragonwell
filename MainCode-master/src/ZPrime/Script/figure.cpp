#include "/home/yaofu/figure/THStackFigure.h"
#include "/home/yaofu/figure/Figure.h"

void figure()
{
 THStackFigure* h;

 TString histName[100];
 histName[0] = "Mll_HighMass";
 histName[1] = "pTll";
 histName[2] = "costheta";
 histName[3] = "DilRapidity";
 histName[4] = "LeadingLepEta";
 histName[5] = "SubleadingLepEta";
 histName[6] = "Mll_LowMass";

 TString AxisName[100];
 AxisName[0] = "M [GeV]";
 AxisName[1] = "p_{T} [GeV]";
 AxisName[2] = "cos #theta_{CS}^{*}";
 AxisName[3] = "y";
 AxisName[4] = "Leading Lepton #eta";
 AxisName[5] = "Subleading Lepton #eta";
 AxisName[6] = "M [GeV]";

 TString Category[10];
 Category[0] = "SR_ee";
 Category[1] = "SR_mm";
 Category[2] = "SR_em";
 Category[3] = "LowMass_ee";
 Category[4] = "LowMass_mm";

 for(int ihist = 0; ihist <= 3; ihist++){
   for(int iregion = 0; iregion <= 1; iregion++){

     h = new THStackFigure(histName[ihist] + "_" + Category[iregion] + ".png", AxisName[ihist], "Events");
     h->SaveFigure();
     h->SetMode("CUSTOM");
     h->SetPlot("E0");
     h->SetLegendPosition(0.7, 0.65, 0.9, 0.99);
     h->Input(1, "MC_results_AllSys.root",      histName[ihist] + "_" + Category[iregion] + "_Data", "Data");
     h->Input(2, "MC_results_AllSys.root",      histName[ihist] + "_" + Category[iregion] + "_SumMC", "Stat. unc");
     h->InputStack(1, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_Ztautau_Final", "Z#rightarrow#tau#tau", kCyan);
     h->InputStack(2, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_Wjets_DD_Final", "Multijets", kYellow);
     h->InputStack(3, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_Diboson_Final", "Diboson", kMagenta);
     h->InputStack(4, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_TopQuark_Final", "Top quarks", kGreen);
     h->InputStack(5, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_PhotonInduced_Final", "Photon-Induced", kOrange);
     h->InputStack(6, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_DrellYan_Final", "Drell-Yan", kRed);
     h->SumStack("Syst. unc + Stat. unc");
     h->SetCustomPad(2);
     h->CustomSetting(1, 1);//Data
     h->CustomSetting(1, -1);//Syst
     h->CustomSetting(1, 2);//Stat
     h->CustomSetting(2, -1, -1, "Divide");
     h->CustomSetting(2, 2, 2, "Divide");
     h->CustomSetting(2, 1, -1, "Divide");
     h->ResetError(1, 2);
     h->ResetError(1, 3);
     h->ResetError(2, 1);
     h->ResetError(2, 2);
     if(iregion == 0) h->SetCustomYRange(2, 0.8, 1.2);
     if(iregion == 1) h->SetCustomYRange(2, 0.5, 1.5);
     h->SetCustomPlotFormat(1, 1, kBlack);
     h->SetCustomPlotFormat(1, 2, kBlue);
     h->SetCustomPlotFormat(1, 3, kRed);
     h->SetCustomPlotFormat(2, 1, kBlue);
     h->SetCustomPlotFormat(2, 2, kRed);
     h->SetCustomPlotFormat(2, 3, kBlack);
     h->SetCustomLegendSize(1, 0.03);
     h->SetPadTitle(2, "#frac{Data}{MC}");
     if(histName[ihist].Contains("Mll_HighMass") || histName[ihist].Contains("pTll")){
       h->SetLogY();
     }
     if(histName[ihist].Contains("Mll_HighMass")){
       h->SetLogX();
       h->SetCustomYRange(1, 1, 1e7);
     }
     h->Draw();
   }
 }

 for(int ihist = 0; ihist <= 3; ihist++){
   for(int iregion = 0; iregion <= 1; iregion++){
   
     TString topDDRegion;
     if(iregion == 0) topDDRegion = "_topDD_ee_Final";
     if(iregion == 1) topDDRegion = "_topDD_mm_Final";

     h = new THStackFigure(histName[ihist] + "_" + Category[iregion] + "_topDD.png", AxisName[ihist], "Events");
     h->SaveFigure();
     h->SetMode("CUSTOM");
     h->SetPlot("E0");
     h->SetLegendPosition(0.7, 0.65, 0.9, 0.99);
     h->Input(1, "MC_results_AllSys.root",      histName[ihist] + "_" + Category[iregion] + "_Data", "Data");
     h->Input(2, "MC_results_AllSys.root",      histName[ihist] + "_" + Category[iregion] + "_topDD_SumMC", "Stat. unc");
     h->InputStack(1, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_Ztautau_Final", "Z#rightarrow#tau#tau", kCyan);
     h->InputStack(2, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_Wjets_DD_Final", "Multijets", kYellow);
     h->InputStack(3, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_Diboson_Final", "Diboson", kMagenta);
     h->InputStack(4, "MC_results_AllSys.root", histName[ihist] + topDDRegion, "Top quarks", kGreen);
     h->InputStack(5, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_PhotonInduced_Final", "Photon-Induced", kOrange);
     h->InputStack(6, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_DrellYan_Final", "Drell-Yan", kRed);
     h->SumStack("Syst. unc + Stat. unc");
     h->SetCustomPad(2);
     h->CustomSetting(1, 1);//Data
     h->CustomSetting(1, -1);//Syst
     h->CustomSetting(1, 2);//Stat
     h->CustomSetting(2, -1, -1, "Divide");
     h->CustomSetting(2, 2, 2, "Divide");
     h->CustomSetting(2, 1, -1, "Divide");
     h->ResetError(1, 2);
     h->ResetError(1, 3);
     h->ResetError(2, 1);
     h->ResetError(2, 2);
     if(iregion == 0) h->SetCustomYRange(2, 0.8, 1.2);
     if(iregion == 1) h->SetCustomYRange(2, 0.5, 1.5);
     h->SetCustomPlotFormat(1, 1, kBlack);
     h->SetCustomPlotFormat(1, 2, kBlue);
     h->SetCustomPlotFormat(1, 3, kRed);
     h->SetCustomPlotFormat(2, 1, kBlue);
     h->SetCustomPlotFormat(2, 2, kRed);
     h->SetCustomPlotFormat(2, 3, kBlack);
     h->SetCustomLegendSize(1, 0.03);
     h->SetPadTitle(2, "#frac{Data}{MC}");
     if(histName[ihist].Contains("Mll_HighMass") || histName[ihist].Contains("pTll")){
       h->SetLogY();
     } 
     if(histName[ihist].Contains("Mll_HighMass")){
       h->SetLogX();
       h->SetCustomYRange(1, 1, 1e7);
     } 
     h->Draw();
   } 
 } 

 for(int ihist = 0; ihist <= 3; ihist++){
   for(int iregion = 0; iregion <= 1; iregion++){

     TString topDDRegion;
     if(iregion == 0) topDDRegion = "_topDD_HighMass_Rapidity_ee_Final";
     if(iregion == 1) topDDRegion = "_topDD_HighMass_Rapidity_mm_Final";

     h = new THStackFigure(histName[ihist] + "_" + Category[iregion] + "_topDD_Mass_Y.png", AxisName[ihist], "Events");
     h->SaveFigure();
     h->SetMode("CUSTOM");
     h->SetPlot("E0");
     h->SetLegendPosition(0.7, 0.65, 0.9, 0.99);
     h->Input(1, "MC_results_AllSys.root",      histName[ihist] + "_" + Category[iregion] + "_Data", "Data");
     h->Input(2, "MC_results_AllSys.root",      histName[ihist] + "_" + Category[iregion] + "_topDD_HighMass_Rapidity_SumMC", "Stat. unc");
     h->InputStack(1, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_Ztautau_Final", "Z#rightarrow#tau#tau", kCyan);
     h->InputStack(2, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_Wjets_DD_Final", "Multijets", kYellow);
     h->InputStack(3, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_Diboson_Final", "Diboson", kMagenta);
     h->InputStack(4, "MC_results_AllSys.root", histName[ihist] + topDDRegion, "Top quarks", kGreen);
     h->InputStack(5, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_PhotonInduced_Final", "Photon-Induced", kOrange);
     h->InputStack(6, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_DrellYan_Final", "Drell-Yan", kRed);
     h->SumStack("Syst. unc + Stat. unc");
     h->SetCustomPad(2);
     h->CustomSetting(1, 1);//Data
     h->CustomSetting(1, -1);//Syst
     h->CustomSetting(1, 2);//Stat
     h->CustomSetting(2, -1, -1, "Divide");
     h->CustomSetting(2, 2, 2, "Divide");
     h->CustomSetting(2, 1, -1, "Divide");
     h->ResetError(1, 2);
     h->ResetError(1, 3);
     h->ResetError(2, 1);
     h->ResetError(2, 2);
     if(iregion == 0) h->SetCustomYRange(2, 0.8, 1.2);
     if(iregion == 1) h->SetCustomYRange(2, 0.5, 1.5);
     h->SetCustomPlotFormat(1, 1, kBlack);
     h->SetCustomPlotFormat(1, 2, kBlue);
     h->SetCustomPlotFormat(1, 3, kRed);
     h->SetCustomPlotFormat(2, 1, kBlue);
     h->SetCustomPlotFormat(2, 2, kRed);
     h->SetCustomPlotFormat(2, 3, kBlack);
     h->SetCustomLegendSize(1, 0.03);
     h->SetPadTitle(2, "#frac{Data}{MC}");
     if(histName[ihist].Contains("Mll_HighMass") || histName[ihist].Contains("pTll")){
       h->SetLogY();
     }
     if(histName[ihist].Contains("Mll_HighMass")){
       h->SetLogX();
       h->SetCustomYRange(1, 1, 1e7);
     }
     h->Draw();
   }
 }

 for(int ihist = 0; ihist <= 3; ihist++){
   for(int iregion = 0; iregion <= 1; iregion++){

     TString topDDRegion;
     if(iregion == 0) topDDRegion = "_topDD_HighMass_CosTheta_ee_Final";
     if(iregion == 1) topDDRegion = "_topDD_HighMass_CosTheta_mm_Final";

     h = new THStackFigure(histName[ihist] + "_" + Category[iregion] + "_topDD_Mass_CosTheta.png", AxisName[ihist], "Events");
     h->SaveFigure();
     h->SetMode("CUSTOM");
     h->SetPlot("E0");
     h->SetLegendPosition(0.7, 0.65, 0.9, 0.99);
     h->Input(1, "MC_results_AllSys.root",      histName[ihist] + "_" + Category[iregion] + "_Data", "Data");
     h->Input(2, "MC_results_AllSys.root",      histName[ihist] + "_" + Category[iregion] + "_topDD_HighMass_CosTheta_SumMC", "Stat. unc");
     h->InputStack(1, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_Ztautau_Final", "Z#rightarrow#tau#tau", kCyan);
     h->InputStack(2, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_Wjets_DD_Final", "Multijets", kYellow);
     h->InputStack(3, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_Diboson_Final", "Diboson", kMagenta);
     h->InputStack(4, "MC_results_AllSys.root", histName[ihist] + topDDRegion, "Top quarks", kGreen);
     h->InputStack(5, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_PhotonInduced_Final", "Photon-Induced", kOrange);
     h->InputStack(6, "MC_results_AllSys.root", histName[ihist] + "_" + Category[iregion] + "_DrellYan_Final", "Drell-Yan", kRed);
     h->SumStack("Syst. unc + Stat. unc");
     h->SetCustomPad(2);
     h->CustomSetting(1, 1);//Data
     h->CustomSetting(1, -1);//Syst
     h->CustomSetting(1, 2);//Stat
     h->CustomSetting(2, -1, -1, "Divide");
     h->CustomSetting(2, 2, 2, "Divide");
     h->CustomSetting(2, 1, -1, "Divide");
     h->ResetError(1, 2);
     h->ResetError(1, 3);
     h->ResetError(2, 1);
     h->ResetError(2, 2);
     if(iregion == 0) h->SetCustomYRange(2, 0.8, 1.2);
     if(iregion == 1) h->SetCustomYRange(2, 0.5, 1.5);
     h->SetCustomPlotFormat(1, 1, kBlack);
     h->SetCustomPlotFormat(1, 2, kBlue);
     h->SetCustomPlotFormat(1, 3, kRed);
     h->SetCustomPlotFormat(2, 1, kBlue);
     h->SetCustomPlotFormat(2, 2, kRed);
     h->SetCustomPlotFormat(2, 3, kBlack);
     h->SetCustomLegendSize(1, 0.03);
     h->SetPadTitle(2, "#frac{Data}{MC}");
     if(histName[ihist].Contains("Mll_HighMass") || histName[ihist].Contains("pTll")){
       h->SetLogY();
     }
     if(histName[ihist].Contains("Mll_HighMass")){
       h->SetLogX();
       h->SetCustomYRange(1, 1, 1e7);
     }
     h->Draw();
   }
 }

}

