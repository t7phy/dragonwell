#include "RootCommon.h"
#include "ePumpHelper/ePumpHelper.h"
#include "Figure/Figure.h"
#include "Tools/Tools.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2 && argc != 3){
   cout<<"Please usage: ./UpdatePDF filename [AlphaS filename]"<<endl;
   return 0;
 }

 TFile* file = new TFile("save.root", "RECREATE");

 ePumpHelper* EU = new ePumpHelper(argv[1]);
 EU->LinkFile(file);
 EU->Initial();
 EU->TurnOffCorrelationCosine();
 EU->Update();

 TString BaseName = "tabsCT18Am248_1164/";
 vector<TString> LMScanDrawList = {BaseName + "E248",
                                   BaseName + "E160",
                                   BaseName + "E542",
                                   BaseName + "E545",
                                   BaseName + "E544",
                                   BaseName + "E514",
                                   BaseName + "E504",
                                   BaseName + "E147",
                                   BaseName + "E102",
                                   BaseName + "E101",
                                   BaseName + "E110",
                                   BaseName + "E126",
                                   BaseName + "E124"};

 //EU->InputLMScanDrawList(LMScanDrawList);

 if(argc == 3){
   EU->ReadAlphaSInput(argv[2]);
   EU->UpdateAlphaSLMScanPDF(0, 0.01, 125.0);
   EU->UpdateAlphaSLMScanPDF(0, 0.03, 125.0);
   EU->UpdateAlphaSLMScanPDF(0, 0.3, 125.0);
   EU->UpdateAlphaSLMScanObservable("tabsCT18Am253/ggHiggsXsec", 0, "#sigma(gg #rightarrow H) [pb]");
 }

 EU->SaveAllHist();
// EU->OutputResult("test/AFB_HighMass_NNPDF40");
// EU->OutputCorrelation("test/AFB_HighMass_NNPDF40", "test/AFB_HighMass_NNPDF40");
// EU->ProcessWeightFunction({"test/CMS8TeVP0_bin1", "test/CMS8TeVP0_bin2", "test/CMS8TeVP0_bin3", "test/CMS8TeVP0_bin4", "test/D05fbP0"});

/* EU->DrawL2SensitivityAll(2, 100.0);
 EU->DrawL2SensitivityAll(-2, 100.0);
 EU->DrawL2SensitivityAll(1, 100.0);
 EU->DrawL2SensitivityAll(-1, 100.0);
 EU->DrawL2SensitivityAll(15, 100.0);

*/

 for(int i = 0; i < EU->AllDataNames.size(); i++){
   //EU->DrawCorrChi2AndData("test/WPlusMTEta", EU->AllDataNames.at(i));
   //EU->DrawCorrChi2AndData("test/WMinusMTEta", EU->AllDataNames.at(i));
   //EU->DrawCorrChi2AndData("test/PositiveLeptonEta", EU->AllDataNames.at(i));
   //EU->DrawCorrChi2AndData("test/NegativeLeptonEta", EU->AllDataNames.at(i));
   //EU->DrawCorrChi2AndData(vector<TString>{"test/Xsec_3D_CC", "test/Xsec_3D_CF"}, EU->AllDataNames.at(i));
   //EU->DrawCorrChi2AndData(vector<TString>{"test/PositiveLeptonEta", "test/Xsec_3D_CC", "test/Xsec_3D_CF"}, EU->AllDataNames.at(i));
   //EU->DrawCorrChi2AndData(vector<TString>{"test/NegativeLeptonEta", "test/Xsec_3D_CC", "test/Xsec_3D_CF"}, EU->AllDataNames.at(i));
 }



 TString InputArgs = argv[1];
 TString PseudodataName;
 TString Luminosity;

 if(InputArgs.Contains("Xsec-1D")) PseudodataName = "Mass";
 if(InputArgs.Contains("Xsec-2D")) PseudodataName = "Mass-Rapidity";
 if(InputArgs.Contains("Xsec-3D")) PseudodataName = "Mass-Rapidity-Angle";
 if(InputArgs.Contains("WPlusEta")) PseudodataName = "#eta_{l} (W^{+})";
 if(InputArgs.Contains("WMinusEta")) PseudodataName = "#eta_{l} (W^{-})";
 if(InputArgs.Contains("WLeptonEta")) PseudodataName = "#eta_{l} (W^{+} + W^{-})";
 if(InputArgs.Contains("WPlusMT")) PseudodataName = "M_{T} (W^{+})";
 if(InputArgs.Contains("WMinusMT")) PseudodataName = "M_{T} (W^{-})";
 if(InputArgs.Contains("WMT")) PseudodataName = "M_{T} (W^{+} + W^{-})";
 if(InputArgs.Contains("WPlusMT-Eta")) PseudodataName = "M_{T} + #eta_{l} (W^{+})";
 if(InputArgs.Contains("WMinusMT-Eta")) PseudodataName = "M_{T} + #eta_{l} (W^{-})";
 if(InputArgs.Contains("WMT-Eta")) PseudodataName = "M_{T} + #eta_{l} (W^{+} + W^{-})";
 if(InputArgs.Contains("WPlusMT") && InputArgs.Contains("NCDY")) PseudodataName = "NCDY + M_{T} (W^{+})";
 if(InputArgs.Contains("WMinusMT") && InputArgs.Contains("NCDY")) PseudodataName = "NCDY + M_{T} (W^{-})";
 if(InputArgs.Contains("WMT") && InputArgs.Contains("NCDY")) PseudodataName = "NCDY + M_{T} (CCDY)";
 if(InputArgs.Contains("WPlusEta") && InputArgs.Contains("NCDY")) PseudodataName = "NCDY + #eta_{l} (W^{+})";
 if(InputArgs.Contains("WMinusEta") && InputArgs.Contains("NCDY")) PseudodataName = "NCDY + #eta_{l} (W^{-})";
 if(InputArgs.Contains("WLeptonEta") && InputArgs.Contains("NCDY")) PseudodataName = "NCDY + #eta_{l} (CCDY)";
 if(InputArgs.Contains("WPlusMT-Eta") && InputArgs.Contains("NCDY")) PseudodataName = "NCDY + W^{+}";
 if(InputArgs.Contains("WMinusMT-Eta") && InputArgs.Contains("NCDY")) PseudodataName = "NCDY + W^{-}";
 if(InputArgs.Contains("WMT-Eta") && InputArgs.Contains("NCDY")) PseudodataName = "NCDY + CCDY";
 if(InputArgs.Contains("ATLAS_Mll_HighMass")) PseudodataName = "Mass (ATLAS HMDY)";
 if(InputArgs.Contains("ATLAS_costheta")) PseudodataName = "cos #theta^{*}_{CS} (ATLAS HMDY)";
 if(InputArgs.Contains("ATLAS_DilRapidity")) PseudodataName = "Rapidity (ATLAS HMDY)";
 if(InputArgs.Contains("ATLAS_Mll_HighMass_costheta")) PseudodataName = "Mass + cos #theta^{*}_{CS} (ATLAS HMDY)";
 if(InputArgs.Contains("ATLAS_Mll_HighMass_DilRapidity")) PseudodataName = "Mass + Rapidity (ATLAS HMDY)";
 if(InputArgs.Contains("ATLAS_HMDY_Xsec_3D")) PseudodataName = "Mass-Rapidity-Angle (ATLAS HMDY)";

 if(InputArgs.Contains("-140")) Luminosity = "140";
 else if(InputArgs.Contains("-300")) Luminosity = "300";
 else if(InputArgs.Contains("-6000")) Luminosity = "6000";
 else if(InputArgs.Contains("-600")) Luminosity = "600";
 else Luminosity = "3000";

 if(InputArgs.Contains("ATLAS_")) Luminosity = "140";
 if(InputArgs.Contains("ATLAS_") && InputArgs.Contains("-300")) Luminosity = "-300";

 cout<<"ePump-Update: "<<argv[1]<<endl;

 cout<<endl;
 cout<<"Relative PDF uncertainty for Z High Mass in CC and CF region of 3000 fb-1"<<endl;
 cout<<endl;

 cout<<"\\begin{table}[H]"<<endl;
 cout<<"    \\centering"<<endl;
 cout<<"    \\begin{tabular}{c|cc|cc}"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"     & \\multicolumn{2}{c}{CC Selection} & \\multicolumn{2}{|c}{CF Selection} \\\\"<<endl;
 cout<<"     & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] \\\\"<<endl;
 cout<<"     \\hline"<<endl;
 cout<<fixed<<setprecision(1)<<"        1 & "<<EU->GetOldRelativePDFError("test/ZHighMass_CC", 8) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_CC", 8) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/ZHighMass_CF", 8) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_CF", 8) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        2 & "<<EU->GetOldRelativePDFError("test/ZHighMass_CC", 15) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_CC", 15) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/ZHighMass_CF", 15) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_CF", 15) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        3 & "<<EU->GetOldRelativePDFError("test/ZHighMass_CC", 20) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_CC", 20) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/ZHighMass_CF", 20) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_CF", 20) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        4 & "<<EU->GetOldRelativePDFError("test/ZHighMass_CC", 23) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_CC", 23) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/ZHighMass_CF", 23) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_CF", 23) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        5 & "<<EU->GetOldRelativePDFError("test/ZHighMass_CC", 24) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_CC", 24) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/ZHighMass_CF", 24) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_CF", 24) * 100.0<<" \\\\"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\end{tabular}"<<endl;
 cout<<"    \\caption{}"<<endl;
 cout<<"    \\label{tab:PDFUnc_Xsec3D}"<<endl;
 cout<<"\\end{table}"<<endl;

 cout<<endl;
 cout<<"Relative PDF uncertainty for Z High Mass and W, W+, W- High Mass MT of 3000 fb-1"<<endl;
 cout<<endl;

 cout<<"\\begin{table}[H]"<<endl;
 cout<<"    \\centering"<<endl;
 cout<<"    \\begin{tabular}{c|cc|cc|cc|cc}"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"     & \\multicolumn{2}{|c}{$m_{\\ell\\ell}$ (NCDY) [TeV]} & \\multicolumn{2}{|c}{$M_T$ (CCDY) [TeV]} & \\multicolumn{2}{|c}{$M_T$ ($W^+$) [TeV]} & \\multicolumn{2}{|c}{$M_T$ ($W^-$) [TeV]} \\\\"<<endl;
 cout<<"     $m_{\\ell\\ell}(M_T)$ & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] \\\\"<<endl;
 cout<<"     \\hline"<<endl;
 cout<<fixed<<setprecision(1)<<"        $>1$ & "<<EU->GetOldRelativePDFError("test/ZHighMass_Integral", 0) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_Integral", 0) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WHighMassMT_Integral", 0) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT_Integral", 0) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT_Integral", 0) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT_Integral", 0) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT_Integral", 0) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT_Integral", 0) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        $>2$ & "<<EU->GetOldRelativePDFError("test/ZHighMass_Integral", 1) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_Integral", 1) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WHighMassMT_Integral", 1) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT_Integral", 1) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT_Integral", 1) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT_Integral", 1) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT_Integral", 1) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT_Integral", 1) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        $>3$ & "<<EU->GetOldRelativePDFError("test/ZHighMass_Integral", 2) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_Integral", 2) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WHighMassMT_Integral", 2) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT_Integral", 2) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT_Integral", 2) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT_Integral", 2) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT_Integral", 2) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT_Integral", 2) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        $>4$ & "<<EU->GetOldRelativePDFError("test/ZHighMass_Integral", 3) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_Integral", 3) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WHighMassMT_Integral", 3) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT_Integral", 3) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT_Integral", 3) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT_Integral", 3) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT_Integral", 3) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT_Integral", 3) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        $>5$ & "<<EU->GetOldRelativePDFError("test/ZHighMass_Integral", 4) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass_Integral", 4) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WHighMassMT_Integral", 4) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT_Integral", 4) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT_Integral", 4) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT_Integral", 4) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT_Integral", 4) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT_Integral", 4) * 100.0<<" \\\\"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\end{tabular}"<<endl; cout<<"    \\caption{"<<argv[1]<<"}"<<endl;
 cout<<"    \\label{tab:PDFUnc_Xsec3D}"<<endl; cout<<"\\end{table}"<<endl;

 cout<<endl;
 cout<<"Relative PDF uncertainty for W High Mass MT and Z High Mass of 3000 fb-1"<<endl;
 cout<<endl;

 cout<<"\\begin{table}[H]"<<endl;
 cout<<"    \\centering"<<endl;
 cout<<"    \\begin{tabular}{c|cc|cc}"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"     & \\multicolumn{2}{c}{$M_T$ (CCDY) [TeV]} & \\multicolumn{2}{|c}{$m_{\\ell\\ell}$ (NCDY) [TeV]} \\\\"<<endl;
 cout<<"     & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] \\\\"<<endl;
 cout<<"     \\hline"<<endl;
 cout<<fixed<<setprecision(1)<<"        1 & "<<EU->GetOldRelativePDFError("test/WHighMassMT", 8) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT", 8) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/ZHighMass", 8) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass", 8) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        2 & "<<EU->GetOldRelativePDFError("test/WHighMassMT", 15) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT", 15) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/ZHighMass", 15) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass", 15) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        3 & "<<EU->GetOldRelativePDFError("test/WHighMassMT", 20) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT", 20) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/ZHighMass", 20) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass", 20) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        4 & "<<EU->GetOldRelativePDFError("test/WHighMassMT", 23) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT", 23) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/ZHighMass", 23) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass", 23) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        5 & "<<EU->GetOldRelativePDFError("test/WHighMassMT", 24) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT", 24) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/ZHighMass", 24) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass", 24) * 100.0<<" \\\\"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\end{tabular}"<<endl; cout<<"    \\caption{"<<argv[1]<<"}"<<endl;
 cout<<"    \\label{tab:PDFUnc_Xsec3D}"<<endl; cout<<"\\end{table}"<<endl;

 cout<<endl;
 cout<<"Relative PDF uncertainty for W+ and W- High Mass of 3000 fb-1"<<endl;
 cout<<endl;

 cout<<"\\begin{table}[H]"<<endl; cout<<"    \\centering"<<endl;
 cout<<"    \\begin{tabular}{c|cc|cc}"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"     & \\multicolumn{2}{c}{$M_T$ ($W^+$) [TeV]} & \\multicolumn{2}{|c}{$M_T$ ($W^-$) [TeV]} \\\\"<<endl;
 cout<<"     & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] \\\\"<<endl;
 cout<<"     \\hline"<<endl;
 cout<<fixed<<setprecision(1)<<"        1 & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT", 8) * 100.0<<" & "<< EU->GetNewRelativePDFError("test/WPlusHighMassMT", 8) * 100.0<<" & "<< EU->GetOldRelativePDFError("test/WMinusHighMassMT", 8) * 100.0<<" & "<< EU->GetNewRelativePDFError("test/WMinusHighMassMT", 8) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        2 & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT", 15) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT", 15) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT", 15) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT", 15) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        3 & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT", 20) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT", 20) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT", 20) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT", 20) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        4 & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT", 23) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT", 23) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT", 23) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT", 23) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        5 & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT", 24) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT", 24) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT", 24) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT", 24) * 100.0<<" \\\\"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\end{tabular}"<<endl; cout<<"    \\caption{"<<argv[1]<<"}"<<endl;
 cout<<"    \\label{tab:PDFUnc_Xsec3D}"<<endl; cout<<"\\end{table}"<<endl;

 cout<<endl;
 cout<<"Relative PDF uncertainty for Z High Mass and W, W+, W- High Mass MT of 3000 fb-1"<<endl;
 cout<<endl;

 cout<<"\\begin{table}[H]"<<endl;
 cout<<"    \\centering"<<endl;
 cout<<"    \\begin{tabular}{c|cc|cc|cc|cc}"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"     & \\multicolumn{2}{|c}{$m_{\\ell\\ell}$ (NCDY) [TeV]} & \\multicolumn{2}{|c}{$M_T$ (CCDY) [TeV]} & \\multicolumn{2}{|c}{$M_T$ ($W^+$) [TeV]} & \\multicolumn{2}{|c}{$M_T$ ($W^-$) [TeV]} \\\\"<<endl;
 cout<<"     & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] & $\\delta^{PDF}_{pre}$ [\\%] & $\\delta^{PDF}_{post}$ [\\%] \\\\"<<endl;
 cout<<"     \\hline"<<endl;
 cout<<fixed<<setprecision(1)<<"        1 & "<<EU->GetOldRelativePDFError("test/ZHighMass", 8) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass", 8) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WHighMassMT", 8) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT", 8) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT", 8) * 100.0<<" & "<< EU->GetNewRelativePDFError("test/WPlusHighMassMT", 8) * 100.0<<" & "<< EU->GetOldRelativePDFError("test/WMinusHighMassMT", 8) * 100.0<<" & "<< EU->GetNewRelativePDFError("test/WMinusHighMassMT", 8) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        2 & "<<EU->GetOldRelativePDFError("test/ZHighMass", 15) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass", 15) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WHighMassMT", 15) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT", 15) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT", 15) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT", 15) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT", 15) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT", 15) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        3 & "<<EU->GetOldRelativePDFError("test/ZHighMass", 20) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass", 20) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WHighMassMT", 20) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT", 20) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT", 20) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT", 20) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT", 20) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT", 20) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        4 & "<<EU->GetOldRelativePDFError("test/ZHighMass", 23) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass", 23) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WHighMassMT", 23) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT", 23) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT", 23) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT", 23) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT", 23) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT", 23) * 100.0<<" \\\\"<<endl;
 cout<<fixed<<setprecision(1)<<"        5 & "<<EU->GetOldRelativePDFError("test/ZHighMass", 24) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/ZHighMass", 24) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WHighMassMT", 24) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WHighMassMT", 24) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WPlusHighMassMT", 24) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WPlusHighMassMT", 24) * 100.0<<" & "<<EU->GetOldRelativePDFError("test/WMinusHighMassMT", 24) * 100.0<<" & "<<EU->GetNewRelativePDFError("test/WMinusHighMassMT", 24) * 100.0<<" \\\\"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\hline"<<endl;
 cout<<"    \\end{tabular}"<<endl; cout<<"    \\caption{"<<argv[1]<<"}"<<endl;
 cout<<"    \\label{tab:PDFUnc_Xsec3D}"<<endl; cout<<"\\end{table}"<<endl;

 cout<<endl;

 int HighMassBin = 25;
 double HighMassBinning[26];
 HighMassBinning[0] = 500.0;
 for(int i = 1; i <= 25; i++){HighMassBinning[i] = pow(10.0, 3.0 + log10(0.5) + (log10(5.0) - log10(0.5)) * i / 25.0);}

 vector<double> FullMassBinning = Logspace(50.0, 5000.0, 70, 10.0);

 Figure* f;


 f = new Figure("ZFullMass_" + EU->FileName + ".pdf", "Dilepton mass [GeV]", "Cross Section [pb]");
 f->SetMode("CUSTOM");
 f->DefineHist(1, "h1", "h1", FullMassBinning.size() - 1, &FullMassBinning[0]);
 f->DefineHist(2, "h2", "h2", FullMassBinning.size() - 1, &FullMassBinning[0]);
 f->Input(1, EU->ConstructOldTheoryWithPDFError("test/ZMass_FullMass", ""), "PDF Error");
 f->Input(2, EU->ConstructOldTheoryWithPDFError("test/ZMass_FullMass", ""), "");
 f->Compare("MultiRatio");
 f->SetLogY();
 f->SetLogX();
 f->SetXNoExponent();
 f->SetCustomPlot(1, 1, "E2");
 f->SetCustomPlot(1, 2, "E0");
 f->SetCustomPlot(2, 1, "E2");
 f->SetCustomPlot(2, 2, "L0");
 f->IgnoreCustomError(2, 2);
 f->SetCustomPlotFormat(1, 2, kBlack);
 f->SetCustomPlotFormat(2, 2, kBlue);
 f->SetCustomYRange(2, 0.7, 1.3);
 f->SetLegendPosition(0.6, 0.64, 0.8, 0.7);
 f->AddCustomText(1, 0.6, 0.85, "#font[72]{ResBos2} CT18NNLO");
 f->AddCustomText(2, 0.6, 0.75, "#sqrt{s} = 13 TeV");
 f->SetPadTitle(2, "Rel. Error");
 f->Draw();
 delete f;


 f = new Figure("ZHighMass_" + EU->FileName + ".pdf", "Dilepton mass [GeV]", "Events");
 f->SetMode("CUSTOM");
 f->DefineHist(1, "h1", "h1", HighMassBin, HighMassBinning);
 f->DefineHist(2, "h2", "h2", HighMassBin, HighMassBinning);
 f->Input(1, EU->ConstructOldTheoryWithPDFError("test/ZHighMass", ""), "PDF Error [CT18]");
 f->Input(2, EU->ConstructNewTheoryWithPDFError("test/ZHighMass", ""), "PDF Error [Update]");
 f->Compare("MultiRatio");
 f->SetLogY();
 f->SetLogX();
 f->SetXNoExponent();
 f->SetCustomPlot(1, 1, "E2");
 f->SetCustomPlot(1, 2, "E2");
 f->SetCustomPlot(2, 1, "E2");
 f->SetCustomPlot(2, 2, "E2");
 f->SetCustomYRange(2, 0.7, 1.3);
 f->SetLegendPosition(0.6, 0.75, 0.8, 0.9);
 f->AddText(1, "#font[72]{ResBos2} CT18NNLO");
 f->AddCustomText(1, 0.03, 0.01, (TString)"Updated by " + PseudodataName + (TString)" in " + Luminosity + (TString)" fb^{-1}");
 f->Draw();
 delete f;

 f = new Figure("WHighMassMT_" + EU->FileName + ".pdf", "M_{T} [GeV]", "Events");
 f->SetMode("CUSTOM");
 f->DefineHist(1, "h1", "h1", HighMassBin, HighMassBinning);
 f->DefineHist(2, "h2", "h2", HighMassBin, HighMassBinning);
 f->Input(1, EU->ConstructOldTheoryWithPDFError("test/WHighMassMT", ""), "PDF Error [CT18]");
 f->Input(2, EU->ConstructNewTheoryWithPDFError("test/WHighMassMT", ""), "PDF Error [Update]");
 f->Compare("MultiRatio");
 f->SetLogY();
 f->SetLogX();
 f->SetXNoExponent();
 f->SetCustomPlot(1, 1, "E2");
 f->SetCustomPlot(1, 2, "E2");
 f->SetCustomPlot(2, 1, "E2");
 f->SetCustomPlot(2, 2, "E2");
 f->SetCustomYRange(2, 0.7, 1.3);
 f->SetLegendPosition(0.6, 0.75, 0.8, 0.9);
 f->AddText(1, "#font[72]{ResBos2} CT18NNLO");
 f->AddCustomText(1, 0.03, 0.01, (TString)"Updated by " + PseudodataName + (TString)" in " + Luminosity + (TString)" fb^{-1}");
 f->Draw();
 delete f;

 f = new Figure("WPlusHighMassMT_" + EU->FileName + ".pdf", "M_{T}(W^{+}) [GeV]", "Events");
 f->SetMode("CUSTOM");
 f->DefineHist(1, "h1", "h1", HighMassBin, HighMassBinning);
 f->DefineHist(2, "h2", "h2", HighMassBin, HighMassBinning);
 f->Input(1, EU->ConstructOldTheoryWithPDFError("test/WPlusHighMassMT", ""), "PDF Error [CT18]");
 f->Input(2, EU->ConstructNewTheoryWithPDFError("test/WPlusHighMassMT", ""), "PDF Error [Update]");
 f->Compare("MultiRatio");
 f->SetLogY();
 f->SetLogX();
 f->SetXNoExponent();
 f->SetCustomPlot(1, 1, "E2");
 f->SetCustomPlot(1, 2, "E2");
 f->SetCustomPlot(2, 1, "E2");
 f->SetCustomPlot(2, 2, "E2");
 f->SetCustomYRange(2, 0.7, 1.3);
 f->SetLegendPosition(0.6, 0.75, 0.8, 0.9);
 f->AddText(1, "#font[72]{ResBos2} CT18NNLO");
 f->AddCustomText(1, 0.03, 0.01, (TString)"Updated by " + PseudodataName + (TString)" in " + Luminosity + (TString)" fb^{-1}");
 f->Draw();
 delete f;

 f = new Figure("WMinusHighMassMT_" + EU->FileName + ".pdf", "M_{T}(W^{-}) [GeV]", "Events");
 f->SetMode("CUSTOM");
 f->DefineHist(1, "h1", "h1", HighMassBin, HighMassBinning);
 f->DefineHist(2, "h2", "h2", HighMassBin, HighMassBinning);
 f->Input(1, EU->ConstructOldTheoryWithPDFError("test/WMinusHighMassMT", ""), "PDF Error [CT18]");
 f->Input(2, EU->ConstructNewTheoryWithPDFError("test/WMinusHighMassMT", ""), "PDF Error [Update]");
 f->Compare("MultiRatio");
 f->SetLogY();
 f->SetLogX();
 f->SetXNoExponent();
 f->SetCustomPlot(1, 1, "E2");
 f->SetCustomPlot(1, 2, "E2");
 f->SetCustomPlot(2, 1, "E2");
 f->SetCustomPlot(2, 2, "E2");
 f->SetCustomYRange(2, 0.7, 1.3);
 f->SetLegendPosition(0.6, 0.75, 0.8, 0.9);
 f->AddText(1, "#font[72]{ResBos2} CT18NNLO");
 f->AddCustomText(1, 0.03, 0.01, (TString)"Updated by " + PseudodataName + (TString)" in " + Luminosity + (TString)" fb^{-1}");
 f->Draw();
 delete f;

 int ATLAS_Mll_HighMass_bin = 13;  double ATLAS_Mll_HighMass_binning[14] = {116.0, 130.0, 150.0, 175.0, 200.0, 230.0, 260.0, 300.0, 380.0, 500.0, 700.0, 1000.0, 1500.0, 5000.0};

 f = new Figure((TString)"ATLAS_Mll_HighMass_" + EU->FileName + ".pdf", "Dilepton mass [GeV]", "Events");
 f->SetMode("CUSTOM");
 f->DefineHist(1, "h1", "h1", ATLAS_Mll_HighMass_bin, ATLAS_Mll_HighMass_binning);
 f->DefineHist(2, "h2", "h2", ATLAS_Mll_HighMass_bin, ATLAS_Mll_HighMass_binning);
 f->Input(1, EU->ConstructOldTheoryWithPDFError("test/ATLAS_Mll_HighMass", ""), "PDF Error [CT18]");
 f->Input(2, EU->ConstructNewTheoryWithPDFError("test/ATLAS_Mll_HighMass", ""), "PDF Error [Update]");
 f->Compare("MultiRatio");
 f->SetLogY();
 f->SetLogX();
 f->SetXNoExponent();
 f->SetCustomPlot(1, 1, "E2");
 f->SetCustomPlot(1, 2, "E2");
 f->SetCustomPlot(2, 1, "E2");
 f->SetCustomPlot(2, 2, "E2");
 f->SetCustomYRange(2, 0.9, 1.1);
 f->SetLegendPosition(0.5, 0.75, 0.7, 0.9);
 f->AddText(1, "#font[72]{ResBos2} CT18NNLO");
 f->Draw();



 //cout<<EU->ConstructOldTheoryWithPDFError("test/ATLAS_Mll_HighMass", "")->GetBinContent(13)<<endl;
 //cout<<EU->ConstructOldTheoryWithPDFError("test/ATLAS_Mll_HighMass", "")->GetBinError(13)<<endl;


 //EU->SetPDFLMScanXRange(-2, 0.3, 100.0, 0.018, 0.04);


/* EU->PDFLMScanModule(-2, 0.1, 100.0, 0);
 EU->PDFLMScanModule(-2, 0.1, 100.0, 1);

 double X1 = EU->GetTheoryTemplate("test/TwoPar2", 0, 1);
 double X2 = EU->GetTheoryTemplate("test/TwoPar2", 0, 2);
 double X3 = EU->GetTheoryTemplate("test/TwoPar2", 0, 3);
 double X4 = EU->GetTheoryTemplate("test/TwoPar2", 0, 4);
 double u1 = EU->GetTheoryTemplate("test/ubar", 0, 1);
 double u2 = EU->GetTheoryTemplate("test/ubar", 0, 2);
 double u3 = EU->GetTheoryTemplate("test/ubar", 0, 3);
 double u4 = EU->GetTheoryTemplate("test/ubar", 0, 4);
 double X1new = EU->GetNewTheoryTemplate("test/TwoPar2", 0, 1);
 double X2new = EU->GetNewTheoryTemplate("test/TwoPar2", 0, 2);
 double X3new = EU->GetNewTheoryTemplate("test/TwoPar2", 0, 3);
 double X4new = EU->GetNewTheoryTemplate("test/TwoPar2", 0, 4);
 double u1new = EU->GetNewTheoryTemplate("test/ubar", 0, 1);
 double u2new = EU->GetNewTheoryTemplate("test/ubar", 0, 2);
 double u3new = EU->GetNewTheoryTemplate("test/ubar", 0, 3);
 double u4new = EU->GetNewTheoryTemplate("test/ubar", 0, 4);

 double u11 = EU->GetTheoryTemplate("test/ubar2", 0, 1);
 double u12 = EU->GetTheoryTemplate("test/ubar2", 0, 2);
 double u13 = EU->GetTheoryTemplate("test/ubar2", 0, 3);
 double u14 = EU->GetTheoryTemplate("test/ubar2", 0, 4);
 double u21 = EU->GetTheoryTemplate("test/ubar2", 1, 1);
 double u22 = EU->GetTheoryTemplate("test/ubar2", 1, 2);
 double u23 = EU->GetTheoryTemplate("test/ubar2", 1, 3);
 double u24 = EU->GetTheoryTemplate("test/ubar2", 1, 4);

 double u11new = EU->GetNewTheoryTemplate("test/ubar2", 0, 1);
 double u12new = EU->GetNewTheoryTemplate("test/ubar2", 0, 2);
 double u13new = EU->GetNewTheoryTemplate("test/ubar2", 0, 3);
 double u14new = EU->GetNewTheoryTemplate("test/ubar2", 0, 4);
 double u21new = EU->GetNewTheoryTemplate("test/ubar2", 1, 1);
 double u22new = EU->GetNewTheoryTemplate("test/ubar2", 1, 2);
 double u23new = EU->GetNewTheoryTemplate("test/ubar2", 1, 3);
 double u24new = EU->GetNewTheoryTemplate("test/ubar2", 1, 4);

 cout<<"X1 = "<<X1<<" X2 = "<<X2<<" X3 = "<<X3<<" X4 = "<<X4<<" u1 = "<<u1<<" u2 = "<<u2<<" u3 = "<<u3<<" u4 = "<<u4<<endl;
 cout<<"X1new = "<<X1new<<" X2new = "<<X2new<<" X3new = "<<X3new<<" X4new = "<<X4new<<" u1new = "<<u1new<<" u2new = "<<u2new<<" u3new = "<<u3new<<" u4new = "<<u4new<<endl;
 cout<<"u11 = "<<u11<<" u12 = "<<u12<<" u13 = "<<u13<<" u14 = "<<u14<<" u21 = "<<u21<<" u22 = "<<u22<<" u23 = "<<u23<<" u24 = "<<u24<<endl;
 cout<<"u11new = "<<u11new<<" u12new = "<<u12new<<" u13new = "<<u13new<<" u14new = "<<u14new<<" u21new = "<<u21new<<" u22new = "<<u22new<<" u23new = "<<u23new<<" u24new = "<<u24new<<endl;
*/



// EU->PDFLMScanModule(-2, 0.3, 100.0, 0);
// EU->PDFLMScanModule(-2, 0.3, 100.0, 1);


 //EU->PDFLMScanModule(15, 0.3, 100.0, 0);
 //EU->PDFLMScanModule(15, 0.3, 100.0, 1);

/* EU->PDFLMScanModule(6, 0.1, 100.0, 0);
 EU->PDFLMScanModule(7, 0.1, 100.0, 0);
 EU->PDFLMScanModule(6, 0.2, 100.0, 0);
 EU->PDFLMScanModule(7, 0.2, 100.0, 0);
 EU->DrawL2SensitivityAll(6, 100.0);
 EU->DrawL2SensitivityAll(7, 100.0);
 EU->CalcL2Sensitivity(6, 0.1, 100.0);
 EU->CalcL2Sensitivity(7, 0.1, 100.0);
*/

 vector<TString> DataList = {};
 //EU->PDFLMScanPlotting(-1, 0.3, 100.0, "_ePumpUpdated", DataList);

// file->Write();

// EU->DefineCombination();
// EU->DefineDataLegend();
// EU->NameTransfer();

// EU->LMScanModule("tabs/E201.CT18NNLO", 10);
// EU->PDFLMScanModule(1, 0.002, 100.0);
// EU->PDFLMScanModule(1, 0.3, 100.0);

/*
 EU->DefineDataLegend();
 EU->NameTransfer();
 EU->DrawL2SensitivityAll(0, 125.0);
// EU->PDFLMScanModule(0, 0.3, 125.0);
 EU->CalcL2Sensitivity(0, 0.3, 125.0);
*/

// EU->AlphaSLMScanModule(91.19);

 //vector<TString> DataList = {"E545", "E253", "E542", "E544", "E160", "E573", "E245", "E204", "E514", "E580", "E110"};

 //EU->PDFLMScanPlotting(21, 0.3, 125.0, "_ePumpUpdated", DataList);
 //EU->AlphaSLMScanPlotting(91.19, "_ePump", DataList);

// EU->AlphaSLMScanModule(91.19);

// EU->PDFLMScanModule(0, 0.01, 125.0);
// EU->PDFLMScanModule(0, 0.03, 125.0);
// EU->PDFLMScanModule(0, 0.3, 125.0);
// EU->LMScanModule("tabsCT18Am253/ggHiggsXsec", 0, "#sigma(gg #rightarrow H) [pb]");

// EU->DrawL2SensitivityAll(0, 125.0);
// EU->CalcL2Sensitivity(0, 0.03, 125.0);

 file->Write();
 file->Close();

 return 1;
}
