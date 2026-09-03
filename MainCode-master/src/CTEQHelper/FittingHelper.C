#include "CTEQHelper/FittingHelper.h"

FittingHelper::FittingHelper()
{
 gStyle->SetLineStyleString(11, "20 12 4 12 4 12");
 gStyle->SetLineStyleString(12, "20 12 4 12 4 12 4 12 4 12");
 gStyle->SetLineStyleString(13, "20 20 12 12");
 gStyle->SetLineStyleString(14, "20 12 20 12 4 12 4 12");
 gStyle->SetLineStyleString(15, "80 20 4 12");
 for(int i = 2; i <= 100; i++){
   PlotLineStyle[i] = i;
 }

}

void FittingHelper::Loading(const char* name)
{

}

void FittingHelper::DrawLMScanPlot(map<TString, TF1 *> FittingResults, TString FigureName, TString XaxisName, TString YaxisName)
{
 double Tsq = 100.0;
 double xmin, xmax;

 map<double, TString> LMErrors;

 for(auto iter = FittingResults.begin(); iter != FittingResults.end(); iter++){
   double par[3];
   iter->second->GetParameters(par);

   double Central = -par[1] / (2 * par[0]);
   double MinChi2 = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);
   double Solution1 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - Tsq))) / (2 * par[0]);
   double Solution2 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - Tsq))) / (2 * par[0]);
   double Solution3 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - 2.0 * Tsq - 50.0))) / (2 * par[0]);
   double Solution4 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - 2.0 * Tsq - 50.0))) / (2 * par[0]);

   cout<<"MinChi2 for Data "<<iter->first<<" = "<<MinChi2<<" Central = "<<Central<<" Solution1 = "<<Solution1<<" Solution2 = "<<Solution2<<" Solution3 = "<<Solution3<<" Solution4 = "<<Solution4<<" Delta = "<<(Solution2 - Solution1) / 2.0<<endl;

   if(iter->first == "Total"){
     xmin = Solution3;
     xmax = Solution4;
   }

   double Delta = par[0] * -1.0;

   if(iter->first != "Total") LMErrors[Delta] = iter->first;//sorting
 }

 for(auto iter = LMErrors.begin(); iter != LMErrors.end(); iter++){
   cout<<"Sorting: "<<iter->first<<", "<<iter->second<<endl;
 }

 Figure* f;

 f = new Figure(FigureName, XaxisName, YaxisName);
 f->SetMode("CUSTOM");
 f->InputTF1(1, FittingResults[(TString)"Total"], "Total");

 int iplot = 2;

 if(LMScanDrawList.size() == 0){
   for(auto iter = LMErrors.begin(); iter != LMErrors.end(); iter++){
     if(iplot >= 15) break;
     f->InputTF1(iplot, FittingResults[iter->second], DataLegend[iter->second]);
     iplot++;
   }
 }
 else{
   for(int i = 0; i < LMScanDrawList.size(); i++){
     f->InputTF1(i + 2, FittingResults[LMScanDrawList.at(i)], DataLegend[LMScanDrawList.at(i)]);
   }
 }

 f->Compare("MultiSimple");
 f->SetCustomPlotFormat(1, 1, kBlack);
 f->SetCanvasSize(1400.0, 1200.0);
 f->SetLegendPosition(1.0, 0.4, 1.2, 0.9);
 f->SetCustomLegendSize(1, 0.025);
 f->SetCustomRightMargin(1, 0.2);
 f->SetCustomLeftMargin(1, 0.15);
 f->SetXRange(xmin, xmax);
 f->SetCustomYRange(1, -20, 50);
 f->SetCustomXTitleOffset(1, 1.0);

 if(LMScanDrawList.size() == 0){
   for(int i = 2; i <= 16; i++){
     f->SetCustomLineStyle(1, i, PlotLineStyle[i]);
   }
 }
 else{
   for(int i = 1; i <= LMScanDrawList.size(); i++){
     f->SetCustomLineStyle(1, i + 1, PlotLineStyle[i + 1]);
   }
 }

 f->SetCustomLineWidth(1, 1, 6);

 f->Draw();

 LMErrors.clear();
}

void FittingHelper::DefineCTEQDataLegend(std::map<TString, TString> &legend)
{
 DataLegend[(TString)"E245"] = "LHCb 7 TeV W/Z";
 DataLegend[(TString)"E246"] = "LHCb 8 TeV y_{Z}";
 DataLegend[(TString)"E248"] = "ATLAS 7 TeV W/Z"; // 4.6 fb^{-1}
 DataLegend[(TString)"E249"] = "CMS 8 TeV A_{ch}";
 DataLegend[(TString)"E250"] = "LHCb 8 TeV W/Z";
 DataLegend[(TString)"E253"] = "ATLAS 8 TeV Z p_{T}";
 DataLegend[(TString)"E542"] = "CMS 7 TeV jet";
 DataLegend[(TString)"E544"] = "ATLAS 7 TeV jet";
 DataLegend[(TString)"E545"] = "CMS 8 TeV jet";
 DataLegend[(TString)"E573"] = "CMS 8 TeV Top";
 DataLegend[(TString)"E580"] = "ATLAS 8 TeV Top";
 DataLegend[(TString)"E160"] = "HERA I + II";
 DataLegend[(TString)"E101"] = "BCDMS F^{p}_{2}";
 DataLegend[(TString)"E102"] = "BCDMS F^{d}_{2}";
 DataLegend[(TString)"E104"] = "NMC F^{d}_{2}/F^{p}_{2}";
 DataLegend[(TString)"E108"] = "CDHSW F^{p}_{2}";
 DataLegend[(TString)"E109"] = "CDHSW x_{B}F^{p}_{3}";
 DataLegend[(TString)"E110"] = "CCFR F_{2}";
 DataLegend[(TString)"E111"] = "CCFR F_{3}";
 DataLegend[(TString)"E124"] = "NuTeV #nu#mu#mu SIDIS";
 DataLegend[(TString)"E125"] = "NuTeV #bar{#nu}#mu#mu SIDIS";
 DataLegend[(TString)"E126"] = "CCFR #nu#mu#mu SIDIS";
 DataLegend[(TString)"E127"] = "CCFR #bar{#nu}#mu#mu SIDIS";
 DataLegend[(TString)"E145"] = "H1";
 DataLegend[(TString)"E147"] = "HERA charm";
 DataLegend[(TString)"E169"] = "H1 F_{L}";
 DataLegend[(TString)"E201"] = "E605";
 DataLegend[(TString)"E203"] = "E866 pd/2pp";
 DataLegend[(TString)"E204"] = "E866 pp xf";
 DataLegend[(TString)"E206"] = "E906";
 DataLegend[(TString)"E225"] = "CDF run-1 A_{ch}";
 DataLegend[(TString)"E227"] = "CDF run-2 A_{ch}";
 DataLegend[(TString)"E234"] = "D0 run-2 A_{ch}";
 DataLegend[(TString)"E260"] = "D0 run-2 Z rapidity";
 DataLegend[(TString)"E261"] = "CDF run-2 Z rapidity";
 DataLegend[(TString)"E266"] = "CMS 7 TeV e A_{ch}";
 DataLegend[(TString)"E267"] = "CMS 7 TeV #mu A_{ch}";
 DataLegend[(TString)"E268"] = "ATLAS 7 TeV W/Z"; // 35 pb^{-1}
 DataLegend[(TString)"E281"] = "D0 run-2 A_{ch}";
 DataLegend[(TString)"E504"] = "CDF run-2 jet";
 DataLegend[(TString)"E514"] = "D0 run-2 jet";
 DataLegend[(TString)"E211"] = "ATLAS 8 TeV A_{ch}";
 DataLegend[(TString)"E212"] = "CMS 13 TeV y_{Z}";
 DataLegend[(TString)"E218"] = "LHCb 13 TeV y_{Z}";
 DataLegend[(TString)"E214"] = "ATLAS 8 TeV Z 3d ";
 DataLegend[(TString)"E215"] = "ATLAS 5 TeV W/Z";
 DataLegend[(TString)"E217"] = "LHCb 8 TeV W+/W-";
 DataLegend[(TString)"E521"] = "ATLAS 13 TeV y_{t#bar{t}}";
 DataLegend[(TString)"E528"] = "CMS 13 TeV y_{t#bar{t}}";
 DataLegend[(TString)"E587"] = "ATLAS 13 TeV Top";
 DataLegend[(TString)"E581"] = "CMS 13 TeV m_{t#bar{t}}";
 DataLegend[(TString)"E553"] = "ATLAS 8 TeV jet";
 DataLegend[(TString)"E554"] = "ATLAS 13 TeV jet";
 DataLegend[(TString)"E555"] = "CMS 13 TeV jet";


 DataLegend[(TString)"LHCb7ZWrap"] = "LHCb 7 TeV W/Z";
 DataLegend[(TString)"LHCb8ZResKF"] = "LHCb 8 TeV y_{Z}";
 DataLegend[(TString)"ATL7ZW"] = "ATLAS 7 TeV W/Z"; // 4.6 fb^{-1}
 DataLegend[(TString)"CMS8Wxa"] = "CMS 8 TeV A_{ch}";
 DataLegend[(TString)"LHCb8WZ"] = "LHCb 8 TeV W/Z";
 DataLegend[(TString)"ATL8ZpT"] = "ATLAS 8 TeV Z p_{T}";
 DataLegend[(TString)"CMS7jtR7y6"] = "CMS 7 TeV jet";
 DataLegend[(TString)"ATL7jtR6u"] = "ATLAS 7 TeV jet";
 DataLegend[(TString)"CMS8jtR7"] = "CMS 8 TeV jet";
 DataLegend[(TString)"CMS8pTtyt"] = "CMS 8 TeV Top";
 DataLegend[(TString)"ATL8ttcoma"] = "ATLAS 8 TeV Top";
 DataLegend[(TString)"HERAIpII"] = "HERA I + II";
 DataLegend[(TString)"BcdF2pCor"] = "BCDMS F^{p}_{2}";
 DataLegend[(TString)"BcdF2dCor"] = "BCDMS F^{d}_{2}";
 DataLegend[(TString)"NmcRatCor"] = "NMC F^{d}_{2}/F^{p}_{2}";
 DataLegend[(TString)"cdhswf2"] = "CDHSW F^{p}_{2}";
 DataLegend[(TString)"cdhswf3"] = "CDHSW x_{B}F^{p}_{3}";
 DataLegend[(TString)"ccfrf2.mi"] = "CCFR F_{2}";
 DataLegend[(TString)"ccfrf3.md"] = "CCFR F_{3}";
 DataLegend[(TString)"NuTvNuChXN"] = "NuTeV #nu#mu#mu SIDIS";
 DataLegend[(TString)"NuTvNbChXN"] = "NuTeV #bar{#nu}#mu#mu SIDIS";
 DataLegend[(TString)"CcfrNuChXN"] = "CCFR #nu#mu#mu SIDIS";
 DataLegend[(TString)"CcfrNbChXN"] = "CCFR #bar{#nu}#mu#mu SIDIS";
 DataLegend[(TString)"Hn+9900x0b"] = "H1";
 DataLegend[(TString)"Hn1X0c"] = "HERA charm";
 DataLegend[(TString)"H1FL10"] = "H1 F_{L}";
 DataLegend[(TString)"e605"] = "E605";
 DataLegend[(TString)"e866f"] = "E866 pd/2pp";
 DataLegend[(TString)"e866ppxf"] = "E866 pp xf";
 DataLegend[(TString)"e906aF"] = "E906";
 DataLegend[(TString)"cdfLasy"] = "CDF run-1 A_{ch}";
 DataLegend[(TString)"cdfLasy2"] = "CDF run-2 A_{ch}";
 DataLegend[(TString)"d02Masy1"] = "D0 run-2 A_{ch}";
 DataLegend[(TString)"ZyD02a"] = "D0 run-2 Z rapidity";
 DataLegend[(TString)"ZyCDF2"] = "CDF run-2 Z rapidity";
 DataLegend[(TString)"CMS7Masy2"] = "CMS 7 TeV e A_{ch}";
 DataLegend[(TString)"CMS7Easy"] = "CMS 7 TeV #mu A_{ch}";
 DataLegend[(TString)"ATL7_WZ"] = "ATLAS 7 TeV W/Z"; // 35 pb^{-1}
 DataLegend[(TString)"d02Easy5"] = "D0 run-2 A_{ch}";
 DataLegend[(TString)"cdf2jtCor2"] = "CDF run-2 jet";
 DataLegend[(TString)"d02jtCor2"] = "D0 run-2 jet";
 DataLegend[(TString)"ATL8W_new3"] = "ATLAS 8 TeV A_{ch}";
 DataLegend[(TString)"CMS13Zmu_new2"] = "CMS 13 TeV y_{Z}";
 DataLegend[(TString)"LHCb13Zy2_Decom.data"] = "LHCb 13 TeV y_{Z}";
 DataLegend[(TString)"ATL8Z3d"] = "ATLAS 8 TeV Z 3d ";
 DataLegend[(TString)"ATL5WZunc.data"] = "ATLAS 5 TeV W/Z";
 DataLegend[(TString)"LHCb8W_Lastm2.data"] = "LHCb 8 TeV W+/W-";
 DataLegend[(TString)"ATL13ytt_HTO2"] = "ATLAS 13 TeV y_{t#bar{t}}";
 DataLegend[(TString)"CMS13ytt_HTO2"] = "CMS 13 TeV y_{t#bar{t}}";
 DataLegend[(TString)"ATL13LepJ_MttYttYBHTtt_HTO2"] = "ATLAS 13 TeV Top";
 DataLegend[(TString)"CMS13lj21mtt_HTO2"] = "CMS 13 TeV m_{t#bar{t}}";
 DataLegend[(TString)"ATL8_Inc_pTjDecor"] = "ATLAS 8 TeV jet";
 DataLegend[(TString)"ATL13_Inc_pTjDecor"] = "ATLAS 13 TeV jet";
 DataLegend[(TString)"CMS13_Inc_pTj"] = "CMS 13 TeV jet";

 legend = DataLegend;
}

void FittingHelper::DefineCombination(std::map<int, TString> &FlavorNameMap, std::map<int, TString> &TitleMap, std::map<TString, int> &FlavorNameIndex)
{
 FlavorNameMap[0] = "gluon";
 FlavorNameMap[1] = "d";
 FlavorNameMap[2] = "u";
 FlavorNameMap[3] = "s";
 FlavorNameMap[4] = "c";
 FlavorNameMap[5] = "b";
 FlavorNameMap[-1] = "dbar";
 FlavorNameMap[-2] = "ubar";
 FlavorNameMap[-3] = "sbar";
 FlavorNameMap[-4] = "cbar";
 FlavorNameMap[-5] = "bbar";
 FlavorNameMap[6] = "uv";
 FlavorNameMap[7] = "dv";
 FlavorNameMap[8] = "sv";
 FlavorNameMap[9] = "ubouv";
 FlavorNameMap[10] = "dbodv";
 FlavorNameMap[11] = "ubou";
 FlavorNameMap[12] = "dbod";
 FlavorNameMap[13] = "gluon5";
 FlavorNameMap[14] = "uod";
 FlavorNameMap[15] = "ubodb";
 FlavorNameMap[16] = "uvodv";
 FlavorNameMap[17] = "dbou";
 FlavorNameMap[18] = "ubod";
 FlavorNameMap[19] = "dboub";
 FlavorNameMap[20] = "dou";
 FlavorNameMap[21] = "Rs";

 TitleMap[0] = "gluon";
 TitleMap[1] = "d";
 TitleMap[2] = "u";
 TitleMap[3] = "s";
 TitleMap[4] = "c";
 TitleMap[5] = "b";
 TitleMap[-1] = "#bar{d}";
 TitleMap[-2] = "#bar{u}";
 TitleMap[-3] = "#bar{s}";
 TitleMap[-4] = "#bar{c}";
 TitleMap[-5] = "#bar{b}";
 TitleMap[6] = "u_{v}";
 TitleMap[7] = "d_{v}";
 TitleMap[8] = "s-#bar{s}";
 TitleMap[9] = "#bar{u}/u_{v}";
 TitleMap[10] = "#bar{d}/d_{v}";
 TitleMap[11] = "#bar{u}/u";
 TitleMap[12] = "#bar{d}/d";
 TitleMap[13] = "g/5";
 TitleMap[14] = "u/d";
 TitleMap[15] = "#bar{u}/#bar{d}";
 TitleMap[16] = "u_{v}/d_{v}";
 TitleMap[17] = "#bar{d}/u";
 TitleMap[18] = "#bar{u}/d";
 TitleMap[19] = "#bar{d}/#bar{u}";
 TitleMap[20] = "d/u";
 TitleMap[21] = "(s+#bar{s})/(#bar{u}+#bar{d})";

 for(auto iter = FlavorNameMap.begin(); iter != FlavorNameMap.end(); iter++){
   FlavorNameIndex[iter->second] = iter->first;
 }
}

