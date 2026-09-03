#include "CTEQHelper/EVsets.h"

EVsets::EVsets()
{
 DefineCombination();
 DefineDataLegend();
 xValues = Logspace(1e-5, 1, 500, 10);
 QValues = Logspace(1.3, 3000, 500, 10);
}

void EVsets::DrawAllL2Sensitivity(int flavor, double Q)
{
 for(int i = 0; i < fData.at(0)->GetDataSize(); i++){
   L2Sensitivity[make_tuple(fData.at(0)->GetDataName(i), flavor, Q)] = DrawL2Sensitivity(fData.at(0)->GetDataSet().at(i), flavor, Q);
 }

 double x = Sorting_x;

 map<TString, double> L2SensitivityResult;
 map<double, TString> L2Inverse;
 for(int idata = 0; idata < fData.at(0)->GetDataSize(); idata++){
   TString DataName = fData.at(0)->GetDataName(idata);
   double L2 = CalcL2Sensitivity(fData.at(0)->GetDataSet().at(idata), flavor, x, Q);
   L2SensitivityResult[DataName] = L2;
   L2Inverse[1.0 - fabs(L2)] = DataName;
 }

 cout<<"L2 Sensitivity:"<<endl;
 int iplot = 1;
 for(auto iter = L2Inverse.begin(); iter != L2Inverse.end(); iter++){
   cout<<fixed<<setprecision(3)<<iter->second<<": "<<L2SensitivityResult[iter->second]<<endl;
   iplot++;
 }

 TString FigureName = (TString)"L2Sensitivity_" + FlavorNameMap[flavor] + "_Q" + TString::Format("%.1f", Q) + "_Top15.pdf";
 TString YAxisName = "L_{2} Sensitivity";
 if(isDrawAbsoluteL2) YAxisName = "|L_{2} Sensitivity|";

 Graph* g;
 g = new Graph(FigureName, "x", YAxisName);
 g->SetMode("CUSTOM");

 if(L2SensitivityDrawList.size() == 0){
   iplot = 1;
   for(auto iter = L2Inverse.begin(); iter != L2Inverse.end(); iter++){
     if(iplot >= 7) break;
     g->Input(iplot, L2Sensitivity[make_tuple(iter->second, flavor, Q)], DataLegend[iter->second]);
     iplot++;
   }
 }
 else{
   for(int i = 0; i < L2SensitivityDrawList.size(); i++){
     g->Input(i + 1, L2Sensitivity[make_tuple(L2SensitivityDrawList.at(i), flavor, Q)], DataLegend[L2SensitivityDrawList.at(i)]);
   }
 }

 g->Compare("MultiSimple");
 g->SetLogX();

 double LegendYMin = 0.4;
 if(L2SensitivityDrawList.size() >= 13) LegendYMin = 0.4 - (L2SensitivityDrawList.size() - 13) * 0.05;

 bool InsideLegend = false;

 if(!InsideLegend){
   g->SetCanvasSize(1400.0, 800.0);
   g->SetLegendPosition(1.0, LegendYMin, 1.3, 0.95);
   g->SetCustomLegendSize(1, 0.04);
   g->SetCustomRightMargin(1, 0.25);
   g->SetCustomLeftMargin(1, 0.1);
   g->SetCustomYTitleOffset(1, 1.0);
   g->SetXRange(1e-5, 0.85);
   g->SetCustomXLabelSize(1, 0.04);
   g->AddText(1, TitleMap[flavor] + " at Q = " + TString::Format("%.1f", Q) + " GeV");
   g->SetTextLeftBias(0.7);
   g->SetCustomTextSize(1, 0.04);
 }
 else{
   g->SetCanvasSize(1400.0, 1000.0);
   g->SetLegendPosition(0.1, 0.73, 0.8, 0.95);
   g->SetCustomLegendSize(1, 0.05);
   g->SetCustomRightMargin(1, 0.1);
   g->SetCustomLeftMargin(1, 0.1);
   g->SetCustomYTitleOffset(1, 1.0);
   g->SetXRange(1e-5, 0.85);
   g->SetCustomXLabelSize(1, 0.04);
   g->AddText(1, TitleMap[flavor] + " at Q = " + TString::Format("%.1f", Q) + " GeV");
   g->SetCustomTextSize(1, 0.06);
   g->SetLegendNColumns(2);
 }

 if(L2SensitivityDrawList.size() == 0){
   for(int i = 1; i <= 6; i++){
     g->SetCustomLineStyle(1, i, PlotLineStyle[i + 1]);
   }
 }
 else{
   for(int i = 1; i <= L2SensitivityDrawList.size(); i++){
     g->SetCustomLineStyle(1, i, PlotLineStyle[i + 1]);
   }
 }

 g->Draw();

}

void EVsets::DrawAllL2SensitivityQ(int flavor, double x)
{
 double Q = Sorting_Q;

 for(int i = 0; i < fData.at(0)->GetDataSize(); i++){
   L2Sensitivity[make_tuple(fData.at(0)->GetDataName(i), flavor, x)] = DrawL2SensitivityQ(fData.at(0)->GetDataSet().at(i), flavor, x);
 }

 map<TString, double> L2SensitivityResult;
 map<double, TString> L2Inverse;
 for(int idata = 0; idata < fData.at(0)->GetDataSize(); idata++){
   TString DataName = fData.at(0)->GetDataName(idata);
   double L2 = CalcL2Sensitivity(fData.at(0)->GetDataSet().at(idata), flavor, x, Q);
   L2SensitivityResult[DataName] = L2;
   L2Inverse[1.0 - fabs(L2)] = DataName;
 }

 cout<<"L2 Sensitivity:"<<endl;
 int iplot = 1;
 for(auto iter = L2Inverse.begin(); iter != L2Inverse.end(); iter++){
   cout<<fixed<<setprecision(3)<<iter->second<<": "<<L2SensitivityResult[iter->second]<<endl;
   iplot++;
 }

 TString FigureName = (TString)"L2Sensitivity_" + FlavorNameMap[flavor] + "_x" + TString::Format("%.2f", x) + "_Top15.pdf";
 TString YAxisName = "L_{2} Sensitivity";
 if(isDrawAbsoluteL2) YAxisName = "|L_{2} Sensitivity|";

 Graph* g;
 g = new Graph(FigureName, "Q", YAxisName);
 g->SetMode("CUSTOM");

 if(L2SensitivityDrawList.size() == 0){
   iplot = 1;
   for(auto iter = L2Inverse.begin(); iter != L2Inverse.end(); iter++){
     if(iplot >= 16) break;
     g->Input(iplot, L2Sensitivity[make_tuple(iter->second, flavor, x)], DataLegend[iter->second]);
     iplot++;
   }
 }
 else{
   for(int i = 0; i < L2SensitivityDrawList.size(); i++){
     g->Input(i + 1, L2Sensitivity[make_tuple(L2SensitivityDrawList.at(i), flavor, x)], DataLegend[L2SensitivityDrawList.at(i)]);
   }
 }

 g->Compare("MultiSimple");
 g->SetLogX();
 g->SetCanvasSize(1400.0, 800.0);
 g->SetLegendPosition(1.0, 0.4, 1.3, 0.9);
 g->SetCustomLegendSize(1, 0.025);
 g->SetCustomRightMargin(1, 0.2);
 g->SetCustomLeftMargin(1, 0.1);
 g->SetCustomYTitleOffset(1, 1.0);
 //g->SetCustomYRange(1, -9, 9);
 g->SetXRange(1.3, 3000.0);
 g->SetCustomXLabelSize(1, 0.04);
 g->AddText(1, TitleMap[flavor] + " at x = " + TString::Format("%.2f", x));
 g->SetTextLeftBias(0.7);
 g->SetCustomTextSize(1, 0.04);

 if(L2SensitivityDrawList.size() == 0){
   for(int i = 1; i <= 15; i++){
     g->SetCustomLineStyle(1, i, PlotLineStyle[i + 1]);
   }
 }
 else{
   for(int i = 1; i <= L2SensitivityDrawList.size(); i++){
     g->SetCustomLineStyle(1, i, PlotLineStyle[i + 1]);
   }
 }

 g->Draw();

}

TH1D* EVsets::DrawL2Sensitivity(int DataID, int flavor, double Q)
{
 cout<<"Draw L2 Sensitivity for Data "<<DataID<<" flavor "<<FlavorNameMap[flavor]<<" at Q = "<<Q<<"GeV"<<endl;
 if(isLinkFile) hf->cd();

 TString HistName = (TString)"L2Sensitivity_Data" + (int)DataID + "_" + FlavorNameMap[flavor] + "_Q" + TString::Format("%.0f", Q);

 TH1D* h1 = new TH1D(HistName, HistName, xValues.size() - 1, &xValues[0]);
 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double x = h1->GetBinCenter(ibin);
   h1->SetBinContent(ibin, CalcL2Sensitivity(DataID, flavor, x, Q));
   h1->SetBinError(ibin, 0.0);
 }

 return h1;
}

TH1D* EVsets::DrawL2Sensitivity(vector<double> Chi2Set, int npt, TString name, int flavor, double Q)
{
 cout<<"Draw L2 Sensitivity for Data "<<name<<" flavor "<<FlavorNameMap[flavor]<<" at Q = "<<Q<<"GeV"<<endl;
 if(isLinkFile) hf->cd();

 TString HistName = (TString)"L2Sensitivity_Data_" + name + "_" + FlavorNameMap[flavor] + "_Q" + TString::Format("%.0f", Q);

 TH1D* h1 = new TH1D(HistName, HistName, xValues.size() - 1, &xValues[0]);
 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double x = h1->GetBinCenter(ibin);
   h1->SetBinContent(ibin, CalcL2Sensitivity(Chi2Set, npt, flavor, x, Q));
   h1->SetBinError(ibin, 0.0);
 }

 return h1;
}

TH1D* EVsets::DrawL2SensitivityQ(int DataID, int flavor, double x)
{
 cout<<"Draw L2 Sensitivity for Data "<<DataID<<" flavor "<<FlavorNameMap[flavor]<<" at x = "<<x<<endl;
 if(isLinkFile) hf->cd();

 TString HistName = (TString)"L2Sensitivity_Data" + (int)DataID + "_" + FlavorNameMap[flavor] + "_x" + TString::Format("%.2f", x);
 HistName.ReplaceAll(".", "p");

 TH1D* h1 = new TH1D(HistName, HistName, QValues.size() - 1, &QValues[0]);
 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double Q = h1->GetBinCenter(ibin);
   h1->SetBinContent(ibin, CalcL2Sensitivity(DataID, flavor, x, Q));
   h1->SetBinError(ibin, 0.0);
 }

 return h1;
}

double EVsets::CalcL2Sensitivity(int DataID, int flavor, double x, double Q)
{
 //L2 Sensitivity = Corr * (PDF unc. of Total chi2)

 double Value = 0.0;

 double Numer = 0.0;
 double Denom = 0.0;
 double Denom2 = 0.0;

 for(int i = 0; i < NEV; i++){
   double DeltaR = (fData.at(2 * i + 2)->GetChi2(DataID) - fData.at(2 * i + 1)->GetChi2(DataID)) / 2.0;
   double DeltaF = (fPDFs.at(2 * i + 2)->Getf(flavor, x, Q) - fPDFs.at(2 * i + 1)->Getf(flavor, x, Q)) / 2.0;

   Numer += DeltaR * DeltaF;
   Denom2 += DeltaF * DeltaF;
 }

 Denom = sqrt(Denom2);// * sqrt(fData.at(0)->GetAveReducedChi2(DataID));

 if(fabs(Denom) > 1e-20) Value = Numer / Denom;

 if(!isfinite(Value)) Value = 0.0;

 if(isDrawAbsoluteL2) Value = fabs(Value);

 return Value;
}

double EVsets::CalcL2Sensitivity(vector<double> Chi2Set, int npt, int flavor, double x, double Q)
{
 //L2 Sensitivity = Corr * (PDF unc. of Total chi2)

 double Value = 0.0;

 double Numer = 0.0;
 double Denom = 0.0;
 double Denom2 = 0.0;
 double Chi2PDFUnc2 = 0.0;

 for(int i = 0; i < (Chi2Set.size() - 1) / 2; i++){
   double DeltaR = (Chi2Set.at(2 * i + 2) - Chi2Set.at(2 * i + 1)) / 2.0;
   double DeltaF = (fPDFs.at(2 * i + 2)->Getf(flavor, x, Q) - fPDFs.at(2 * i + 1)->Getf(flavor, x, Q)) / 2.0;

   Numer += DeltaR * DeltaF;
   Denom2 += DeltaF * DeltaF;
   Chi2PDFUnc2 += DeltaR * DeltaR;
 }

 Denom = sqrt(Denom2);

 if(fabs(Denom) > 1e-20) Value = Numer / Denom;

 if(!isfinite(Value)) Value = 0.0;

 if(isDrawAbsoluteL2) Value = fabs(Value);

 return Value;
}

/////////////////////////////////////////////////////////////////////////////////
void EVsets::OutputePumpTheory(TString subName)
{
 for(int idata = 0; idata < fData.at(0)->GetDataSize(); idata++){
   ofstream outfile;
   outfile.open((TString)"E" + (int)(fData.at(0)->GetDataID(idata)) + subName + (TString)".theory");
   outfile<<"Theory Column"<<endl;
   outfile<<"      5"<<endl;
   for(int i = 0; i < fData.size(); i++){
     if(i < 10) outfile<<" Data : If1363H.0"<<i<<".dta"<<endl;
     if(i >= 10) outfile<<" Data : If1363H."<<i<<".dta"<<endl;
     for(int ipt = 1; ipt <= fData.at(i)->GetDataNpt(idata); ipt++){
       outfile << setw(15) << scientific << uppercase << setprecision(3) << fData.at(i)->GetYPoint(idata, ipt);
       outfile << setw(15) << scientific << uppercase << setprecision(3) << fData.at(i)->GetQPoint(idata, ipt);
       outfile << setw(15) << scientific << uppercase << setprecision(3) << fData.at(i)->GetRsPoint(idata, ipt);
       outfile << setw(15) << scientific << uppercase << setprecision(5) << fData.at(i)->GetExpPoint(idata, ipt);
       outfile << setw(15) << scientific << uppercase << setprecision(5) << fData.at(i)->GetTheoryPoint(idata, ipt);
       outfile << endl;
     }
   }
   outfile.close();
 }

 ofstream outfile;
 outfile.open("test.in");
 outfile<<"+++ N(EV pairs)                     N(Data Sets)   PDFtype(C/L/N)  DiagonalQuad(Y/N)  Dyn_Tol?(Y/N)   Tol_squared"<<endl;
 outfile<<"        "<<(fData.size() - 1) / 2<<"                                  "<<fData.at(0)->GetDataSize()<<"               C             N                 Y             100.0"<<endl;
 outfile<<"+++ ObservableFile                    N(Observables)  Data?(Y/N)      Error_type     Weight           PS:"<<endl;
 for(int idata = 0; idata < fData.at(0)->GetDataSize(); idata++){
   outfile<<(TString)"test/E" + (int)(fData.at(0)->GetDataID(idata)) + subName + (TString)"                           "<<fData.at(0)->GetDataNpt(idata)<<"              Y             1           0.0"<<endl;
 }

 outfile<<"+++     PDFname                    PDFout"<<endl;
 outfile<<"PDFs/i2Tn3.58/i2Tn3                 outPDFs/i2Tn3"<<endl;
 outfile<<""<<endl;
 outfile<<""<<endl;
 outfile<<""<<endl;
 outfile<<"# .in for ePump_v20171221 and after"<<endl;
 outfile<<"# 2021.0115.0214.+0800.Fri.CST"<<endl;
 outfile<<"# /home/doc/physics/projects/CTEQPDFs/CT18NNLO.ev"<<endl;

 outfile.close();

}

/////////////////////////////////////////////////////////////////////////////////

void EVsets::InitializeData(TString list)
{
 cout<<"Initialize Data:"<<endl;

 TString FileName;
 vector<TString> FileNames;

 ifstream infile;
  infile.open(list, ios::in);

 while(infile >> FileName){
   FileNames.push_back(FileName);
 }

 fData.resize(FileNames.size());
 for(int i = 0; i < fData.size(); i++){
   fData.at(i) = new dtaReader(FileNames.at(i), (TString)"_PDF_" + (int)i);
   fData.at(i)->ReadFile();
 }

 NEV = (fData.size() - 1) / 2;

 FileNames.clear();
 infile.close();
}

void EVsets::InitializePDF(TString list)
{
 cout<<"Initialize PDF:"<<endl;

 TString FileName;
 vector<TString> FileNames;

 ifstream infile;
  infile.open(list, ios::in);

 while(infile >> FileName){
   FileNames.push_back(FileName);
 }

 fPDFs.resize(FileNames.size());
 for(int i = 0; i < fPDFs.size(); i++){
   fPDFs.at(i) = new pdsReader();
   fPDFs.at(i)->Initialize(FileNames.at(i));
 }

 NEV = (fPDFs.size() - 1) / 2;

 FileNames.clear();
 infile.close();
}


