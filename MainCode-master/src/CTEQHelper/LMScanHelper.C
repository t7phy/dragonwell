#include "CTEQHelper/LMScanHelper.h"

LMScanHelper::LMScanHelper()
{
 DefineDataLegend();
}

void LMScanHelper::InitialData(vector<TString> DataList)
{
 DataFiles.resize(DataList.size());

 for(int i = 0; i < DataList.size(); i++){
   DataFiles.at(i) = new dtaReader(DataList.at(i), (TString)"_Para_" + (int)(i + 1));
   DataFiles.at(i)->ReadFile();
 }

 this->DataNameMap = DataFiles.at(0)->DataNameMap;
 this->DataNameMap[9999] = (TString)"Total";

 for(auto iter = DataNameMap.begin(); iter != DataNameMap.end(); iter++){
   DataIndex[iter->second] = iter->first;
 }

}

void LMScanHelper::InitialSummary(vector<TString> SummaryList)
{
 SummaryFiles.resize(SummaryList.size());

 for(int i = 0; i < SummaryList.size(); i++){
   SummaryFiles.at(i) = new sumReader();
   SummaryFiles.at(i)->Initialize(SummaryList.at(i));
 }
}

void LMScanHelper::DrawChi2(TString subName)
{
 if(isLinkFile) hf->cd();

 if(LMPara.size() != DataFiles.size()){
   cout<<"ERROR! Parameter and data files don't match."<<endl;
   return;
 }

 vector<double> Binning(LMPara.size() + 1);
 double step = LMPara.at(1) - LMPara.at(0);
 for(int i = 0; i < LMPara.size(); i++){
   Binning.at(i) = LMPara.at(i) - step / 2.0;
 }
 Binning.at(LMPara.size()) = LMPara.at(LMPara.size() - 1) + step / 2.0;


 for(auto iter = DataFiles.at(0)->DataChi2.begin(); iter != DataFiles.at(0)->DataChi2.end(); iter++){
   TString HistName = (TString)"Chi2_E" + (int)iter->first + "_" + subName;
   Chi2Hist[iter->first] = new TH1D(HistName, HistName, Binning.size() - 1, &Binning[0]);

   HistName.ReplaceAll("Chi2", "Chi2Zero");
   Chi2ZeroHist[iter->first] = new TH1D(HistName, HistName, Binning.size() - 1, &Binning[0]);
 }

 TString HistName = "Chi2_Total_" + subName;
 Chi2Hist[9999] = new TH1D(HistName, HistName, Binning.size() - 1, &Binning[0]);

 HistName.ReplaceAll("Chi2", "Chi2Zero");
 Chi2ZeroHist[9999] = new TH1D(HistName, HistName, Binning.size() - 1, &Binning[0]);

 for(int i = 0; i < DataFiles.size(); i++){

   for(auto iter = Chi2Hist.begin(); iter != Chi2Hist.end(); iter++){
     if(iter->first != 9999) Chi2Hist[iter->first]->SetBinContent(i + 1, DataFiles.at(i)->DataChi2[iter->first]->GetBinContent(1));
     if(iter->first != 9999) Chi2Hist[iter->first]->SetBinError(i + 1, 0.0);

     //if(iter->first == 9999) Chi2Hist[iter->first]->SetBinContent(i + 1, DataFiles.at(i)->GetSumOfChi2());
     if(iter->first == 9999) Chi2Hist[iter->first]->SetBinContent(i + 1, SummaryFiles.at(i)->Chi2F);
     if(iter->first == 9999) Chi2Hist[iter->first]->SetBinError(i + 1, 0.0);
   }

 }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Finding the bestfit and errors of the total chi2 function

 TString FittingName = (TString)"Chi2Fitting_Total_" + subName;
 Chi2Fitting[9999] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", Binning.at(0) - step * 10.0, Binning.at(Binning.size() - 1) + step * 10.0);
 Chi2Hist[9999]->Fit(Chi2Fitting[9999], "W");

 double par[3];
 Chi2Fitting[9999]->GetParameters(par);

 double Central = -par[1] / (2 * par[0]);
 BestChi2[9999] = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);

 double Solution1 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2[9999] - 100.0))) / (2 * par[0]);
 double Solution2 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2[9999] - 100.0))) / (2 * par[0]);
 double Solution3 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2[9999] - 230.0))) / (2 * par[0]);
 double Solution4 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2[9999] - 230.0))) / (2 * par[0]);
 double Solution1_T37 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2[9999] - 37.0))) / (2 * par[0]);
 double Solution2_T37 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2[9999] - 37.0))) / (2 * par[0]);
 double Solution1_T10 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2[9999] - 10.0))) / (2 * par[0]);
 double Solution2_T10 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2[9999] - 10.0))) / (2 * par[0]);

 PlotXMin = Solution3;
 PlotXMax = Solution4;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 map<double, int> LMErrors;

 for(auto iter = Chi2Hist.begin(); iter != Chi2Hist.end(); iter++){

   TString FittingName;
   if(iter->first != 9999) FittingName = (TString)"Chi2Fitting_E" + iter->first + "_" + subName;
   if(iter->first == 9999) FittingName = (TString)"Chi2Fitting_Total_" + subName;

   if(iter->first != 9999){

     Chi2Fitting[iter->first] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", Binning.at(0) - step * 10.0, Binning.at(Binning.size() - 1) + step * 10.0);
     Chi2Hist[iter->first]->Fit(Chi2Fitting[iter->first], "W");

     double par[3];
     Chi2Fitting[iter->first]->GetParameters(par);

     double MinChi2;
     if(iter->first == 9999) MinChi2 = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);
     if(iter->first != 9999) MinChi2 = Chi2Fitting[iter->first]->Eval(Central);//Central is the bestfit of the total chi2

     BestChi2[iter->first] = MinChi2;

   }

   for(int ibin = 1; ibin <= iter->second->GetNbinsX(); ibin++){
     Chi2ZeroHist[iter->first]->SetBinContent(ibin, iter->second->GetBinContent(ibin) - BestChi2[iter->first]);
     Chi2ZeroHist[iter->first]->SetBinError(ibin, 0.0);
   }

   FittingName.ReplaceAll("Chi2Fitting", "Chi2ZeroFitting");
   Chi2ZeroFitting[iter->first] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", Binning.at(0) - step * 10.0, Binning.at(Binning.size() - 1) + step * 10.0);
   Chi2ZeroHist[iter->first]->Fit(Chi2ZeroFitting[iter->first], "W");


   double par[3];
   Chi2ZeroFitting[iter->first]->GetParameters(par);
   double Solution1 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - 100.0))) / (2 * par[0]);
   double Solution2 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - 100.0))) / (2 * par[0]);
   if(iter->first != 9999) LMErrors[(Solution2 - Solution1) / 2.0] = iter->first;

   if(isLinkFile) Chi2Hist[iter->first]->Write();
   if(isLinkFile) Chi2Fitting[iter->first]->Write();
   if(isLinkFile) Chi2ZeroHist[iter->first]->Write();
   if(isLinkFile) Chi2ZeroFitting[iter->first]->Write();
 }

 TString FigureName = (TString)"AlphaSLMScan" + subName + "_auto.pdf";
 TString XaxisName = "#alpha_{s}(M_{Z})";
 TString YaxisName = "#Delta #chi^{2}";

 Figure* f;

 f = new Figure(FigureName, XaxisName, YaxisName);
 f->SetMode("CUSTOM");
 f->InputTF1(1, Chi2ZeroFitting[9999], "Total");

 int iplot = 2;
 for(auto iter = LMErrors.begin(); iter != LMErrors.end(); iter++){
   if(iplot >= 16) break;
   f->InputTF1(iplot, Chi2ZeroFitting[iter->second], DataLegend[DataNameMap.at(iter->second)]);
   iplot++;
 }

 f->Compare("MultiSimple");
 f->SetCustomPlotFormat(1, 1, kBlack);
 f->SetCanvasSize(1400.0, 1200.0);
 f->SetLegendPosition(1.0, 0.4, 1.2, 0.9);
 f->SetCustomLegendSize(1, 0.025);
 f->SetCustomRightMargin(1, 0.2);
 f->SetCustomLeftMargin(1, 0.15);
 f->SetXRange(PlotXMin, PlotXMax);
 f->SetCustomYRange(1, -20, 100);
 f->SetCustomXTitleOffset(1, 1.0);

 for(int i = 0; i < 14; i++){
   f->SetCustomLineStyle(1, i + 2, PlotLineStyle[i + 2]);
 }

 f->SetCustomLineWidth(1, 1, 6);

 f->Draw();

 cout<<"T2 = 100:"<<endl;
 cout<<"AlphaS = "<<fixed<<setprecision(10)<<Central<<" + "<<Solution2 - Central<<" - "<<Central - Solution1<<endl;
 cout<<"AlphaS up = "<<Solution2<<endl;
 cout<<"AlphaS down = "<<Solution1<<endl;
 cout<<"T2 = 37:"<<endl;
 cout<<"AlphaS = "<<Central<<" + "<<Solution2_T37 - Central<<" - "<<Central - Solution1_T37<<endl;
 cout<<"AlphaS up = "<<Solution2_T37<<endl;
 cout<<"AlphaS down = "<<Solution1_T37<<endl;
 cout<<"T2 = 10:"<<endl;
 cout<<"AlphaS = "<<Central<<" + "<<Solution2_T10 - Central<<" - "<<Central - Solution1_T10<<endl;
 cout<<"AlphaS up = "<<Solution2_T10<<endl;
 cout<<"AlphaS down = "<<Solution1_T10<<endl;

}

void LMScanHelper::Plotting(TString subName, vector<TString> DataList)
{
 TString FigureName = (TString)"AlphaSLMScan" + subName + ".pdf";
 TString XaxisName = "#alpha_{s}(M_{Z})";
 TString YaxisName = "#Delta #chi^{2}";

 PlotXMin = 0.108;
 PlotXMax = 0.128;
 cout<<"The XRange is modified manually"<<endl;

 Figure* f;

 f = new Figure(FigureName, XaxisName, YaxisName);
 f->SetMode("CUSTOM");
 f->InputTF1(1, Chi2ZeroFitting[9999], "Total");
 int iplot = 2;
 for(int i = 0; i < DataList.size(); i++){
   cout<<"Adding data "<<DataList.at(i)<<"..."<<endl;
   f->InputTF1(iplot, Chi2ZeroFitting[DataIndex[DataList.at(i)]], DataLegend[DataList.at(i)]);
   iplot++;
 }
 f->Compare("MultiSimple");
 f->SetCustomPlotFormat(1, 1, kBlack);
 f->SetCanvasSize(1400.0, 1200.0);
 f->SetLegendPosition(1.0, 0.4, 1.2, 0.9);
 f->SetCustomLegendSize(1, 0.025);
 f->SetCustomRightMargin(1, 0.2);
 f->SetCustomLeftMargin(1, 0.15);
 f->SetXRange(PlotXMin, PlotXMax);
 f->SetCustomYRange(1, -20, 100);
 f->SetCustomXTitleOffset(1, 1.0);

 for(int i = 0; i < DataList.size(); i++){
   f->SetCustomLineStyle(1, i + 2, PlotLineStyle[i + 2]);
 }

 f->SetCustomLineWidth(1, 1, 6);

 f->Draw();

}

