#include <iostream>
#include <TH1D.h>
#include <TROOT.h>
#include <TFile.h>
#include "TTree.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TF1.h>
#include "TH2D.h"
#include "THStack.h"
#include "TColor.h"
#include "TGaxis.h"
#include "TLatex.h"

using namespace std;

class THStackFigure
{
 public:

 TCanvas *MyN;
 TGaxis *axis1;

 TString myFigureName;
 TString myXTitle;
 TString myYTitle;

 TFile* file[100];
 TTree* tree[100];
 TFile* StackFile[100];
 TFile* PDFfile[100];
 TH1D* h1[100];
 TH2D* h2[100];
 TH1D* PDF1[100];
 TText* text[100];

 THStack* myStack;
 TH1D* MergedStackHist;
 TH1D* StackHist[100];
 TH1D* tmpStackHist[100];

 TH1D* tmph1[100];
 TH2D* tmph2[100];

 TLegend *legend1;
 TLegend *legend2;
 TLegend *legend3;

 TString myLegendName[100];
 TString myCustomLegendName[10][100];
 TString myStackLegendName[100];
 TString myPDFLegendName[100];
 TString myText[100];
 int TextFont[100] = {42};
 TString MergedLegendName;

 map<TString, Color_t> StackColor;

 double legendxmin, legendxmax, legendymin, legendymax;
 int NColumn = 1;
 double TextX, TextY;
 double XRangeMin, XRangeMax, YRangeMin, YRangeMax;
 double BottomMargin, TopMargin, LeftMargin, RightMargin;
 double wmin, wmax;
 double ymin, ymax;

 double YTitleOffset = 1;

 double NumerPoint, DenomPoint, NumerError, DenomError;
 double DataPoint, DataError;

 double LegendTextSize;

 int ndiv;

 bool isSingle;
 bool isSingleRatio;
 bool isSimple;
 bool isRatio;
 bool isDelta;
 bool isDeltaSigma;
 bool isPDF;
 bool is2D;

 bool isInput;
 bool isInputStack;
 bool isInputPDFError;

 bool withPDFError;
 int Process;

 bool isHIST;
 bool isE0;

 bool isAddGaxis;

 bool isNorm;
 bool isLogX = false;
 bool isLogY = false;
 bool isEfficiency;

 bool isSetXRange;
 bool isSetYRange;
 bool isSetYRange0;

 bool isWsample;

 bool isRebin;
 int RebinType;
 double* rebin;
 int ngroup;

 bool DoSave;

 bool isDefineHist = false;

 bool isDivideBinWidth[500] = {false};

 int FigureCount;
 int StackFigureCount;
 int PDFFigureCount;
 int TextCount;

 double PDFScaleFactor = 1.0;
 double PDFUncRangeMin;
 double PDFUncRangeMax;
 bool isSetPDFUncRange = false;

 int TotalPadNumber = 0;
 int CustomFigureCount[10] = {0};
 TH1D* Custom[10][500] = {0};
 bool isCustom = false;
 TString myPadName[10];
 bool isSetCustomYRange[10] = {0};
 double CustomYRangeMin[10];
 double CustomYRangeMax[10];
 double CustomLegendSize[10] = {0.04};
 TH1D* tmpHist[500];

 TFile *ErrorFile[100];
 TH1D *HistError[100];  
 bool isInputError = false;
 bool isResetError[10][500] = {0};

 bool isDrawStack = true;

 THStackFigure(const char* FigureName, const char* XTitle, const char* YTitle);
 virtual ~THStackFigure();
 virtual void SetMode(const char* ModeName);
 virtual void SetPlot(const char* PlotMode);
 virtual void SetNorm();
 virtual void SetLogX();
 virtual void SetLogY();

 virtual void Input(int Number, const char* rootName, const char* histName, const char* legendName = "");
 virtual void Input2D(int Number, const char* rootName, const char* histName, int binx, int biny, const char* legendName = "");
 virtual void InputTree(int Number, const char* rootName, const char* treeName, const char* histName, int nbin, double left, double right, const char* VariableName, const char* WeightName, const char* legendName = "");
 virtual void InputStack(int Number, const char* rootName, const char* histName, TString legendName, Color_t color);
 virtual void InputStack2D(int Number, const char* rootName, const char* histName, int binx, int biny, TString legendName, Color_t color);
 virtual void InputTreeStack(int Number, const char* rootName, const char* treeName, const char* histName, int nbin, double left, double right, const char* VariableName, const char* WeightName, const char* legendName, Color_t color);
 virtual void SumStack(const char* LegendName = "");
 virtual void ChangeStackScale(int Number, double scale);


 virtual void InputError(int Number, const char* rootName, const char* histName, const char* legendName = "");

 virtual void DefineCustomHist(int Number, int histNumber1, int histNumber2 = 0, TString process = "", const char* LegendName = "");

 virtual void SetCustomPad(int TotalPadNumber);
 virtual void CustomSetting(int PadNumber, int histNumber1, int histNumber2 = 0, TString process = "");
 virtual void InputCustomStack(int Number, int histNumber1, int histNumber2 = 0, TString process = "", TString legendName = "", Color_t color = 0);
 virtual void SetCustomPlotFormat(int PadNumber, int Number, Color_t Color, Style_t style = 8);
 virtual void SetPadTitle(int PadNumber, const char* PadName);
 virtual void SetCustomYRange(int PadNumber, double ymin, double ymax);
 virtual void SetCustomLegendSize(int PadNumber, double size);
 virtual void SetLegendNColumn(int NColumn);
 virtual void CustomNorm(int PadNumber, int fig1, int fig2, int BaseOne = 1);
 virtual void SetCustomError(int Number, int ErrorNumber);

 virtual void ResetError(int PadNumber, int Number){isResetError[PadNumber][Number] = true;Custom[PadNumber][Number]->SetFillStyle(3354);}

 virtual void SetXRange(double xmin, double xmax);
 virtual void SetYRange(double ymin, double ymax, int iPlot = 1);

 virtual void Draw();
 virtual void SaveFigure();
 virtual void Rebin(int Nbin, double* xbins);
 virtual void Rebin(int Nbin);
 virtual void SetLegendPosition(double xmin, double ymin, double xmax, double ymax);
 virtual void SetLegendTextSize(double LegendTextSize);
 virtual void SetYTitleOffset(double offset);
 virtual void NoStack(){isDrawStack = false;}

 virtual void AddText(int Number, const char* TextContent);
 virtual void SetTextFont(int Number, int Font){TextFont[Number] = Font;};
 virtual void SetDivideBinWidth(){
   for(int i = 1; i <= 100; i++){
     isDivideBinWidth[i] = true;
   }
 }
};

THStackFigure::THStackFigure(const char* FigureName, const char* XTitle, const char* YTitle)
{
 myStack = new THStack("myStack", "myStack");
 FigureCount = 0;
 StackFigureCount = 0;
 PDFFigureCount = 0;
 TextCount = 0;

 isSingle = false;
 isSingleRatio = false;
 isSimple = false;
 isRatio = false;
 isDelta = false;
 isDeltaSigma = false;
 isPDF = false;
 is2D = false;

 isInput = false;
 isInputStack = false;
 isInputPDFError = false;

 withPDFError = false;
 Process = 0;

 isHIST = false;
 isE0 = false;

 isAddGaxis = false;

 isNorm = false;
 isLogX = false;
 isLogY = false;
 isEfficiency = false;

 isSetXRange = false;
 isSetYRange = false;
 isSetYRange0 = false;

 isWsample = false;

 isRebin = false;
 RebinType = 0;

 DoSave = false;

 LegendTextSize = 0.04;

 myFigureName = FigureName;
 myXTitle = XTitle;
 myYTitle = YTitle;
}

THStackFigure::~THStackFigure()
{
}

void THStackFigure::SetMode(const char* ModeName)
{
 TString myMode = ModeName;
 if(myMode == "SINGLE") isSingle = true;
 if(myMode == "SINGLERATIO") isSingleRatio = true;
 if(myMode == "SIMPLE") isSimple = true;
 if(myMode == "RATIO") isRatio = true;
 if(myMode == "DELTA") isDelta = true;
 if(myMode == "DELTASIGMA") isDeltaSigma = true;
 if(myMode == "PDF") isPDF = true;
 if(myMode == "2DFIGURE") is2D = true;
 if(myMode == "CUSTOM") isCustom = true;
}

void THStackFigure::SetPlot(const char* PlotMode)
{
 TString myPlotMode = PlotMode;
 if(myPlotMode == "HIST") isHIST = true;
 if(myPlotMode == "E0") isE0 = true;
}

void THStackFigure::SetNorm()
{
 isNorm = true;
}

void THStackFigure::SetLogX()
{
 isLogX = true;
}

void THStackFigure::SetLogY()
{
 isLogY = true;
}

void THStackFigure::SaveFigure()
{
 DoSave = true;
}

void THStackFigure::Rebin(int Nbin)
{
 isRebin = true;
 RebinType = 1;
 ngroup = Nbin;
}

void THStackFigure::Rebin(int Nbin, double* xbins)
{
 isRebin = true;
 RebinType = 2;
 rebin = xbins;
 ngroup = Nbin;
}

void THStackFigure::SetLegendPosition(double xmin, double ymin, double xmax, double ymax)
{
 legendxmin = xmin;
 legendxmax = xmax;
 legendymin = ymin;
 legendymax = ymax;
}

void THStackFigure::SetLegendTextSize(double LegendTextSize)
{
 this->LegendTextSize = LegendTextSize;
}

void THStackFigure::SetYTitleOffset(double offset)
{
 YTitleOffset = offset;
}

void THStackFigure::Input(int Number, const char* rootName, const char* histName, const char* legendName)
{
 isInput = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 if(!isDefineHist) h1[Number] = (TH1D *)file[Number]->Get(histName);
 if(isDefineHist){
   tmph1[Number] = (TH1D *)file[Number]->Get(histName);
   for(int ibin = 1; ibin <= tmph1[Number]->GetNbinsX(); ibin++){
     h1[Number]->SetBinContent(ibin, tmph1[Number]->GetBinContent(ibin));
     h1[Number]->SetBinError(ibin, tmph1[Number]->GetBinError(ibin));
   }
 }

 myLegendName[Number] = legendName;

 if(isRebin)
 {
  cout<<"Histogram has been rebinned."<<endl;
  if(RebinType == 1) h1[Number]->Rebin(ngroup);
  if(RebinType == 2) h1[Number] = (TH1D *)h1[Number]->Rebin(ngroup, histName, rebin);
  if(is2D) {cout<<"Error: 2D histogram cannot be rebined"<<endl; return;}
 }

 if(isDivideBinWidth[Number]){
   for(int ibin = 0; ibin < h1[Number]->GetNbinsX(); ibin ++){
     cout<<(h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1))<<endl;
     h1[Number]->SetBinContent(ibin + 1, h1[Number]->GetBinContent(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     h1[Number]->SetBinError(ibin + 1, h1[Number]->GetBinError(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     cout<<h1[Number]->GetBinContent(ibin + 1)<<endl;
   }
 }

// cout<<"Integral of "<<legendName<<": "<<h1[Number]->Integral()<<endl;
// cout<<legendName<<": mmm: "<<h1[Number]->GetBinContent(2)<<" mme: "<<h1[Number]->GetBinContent(3)<<" eem: "<<h1[Number]->GetBinContent(4)<<" eee: "<<h1[Number]->GetBinContent(5)<<endl;
}

void THStackFigure::Input2D(int Number, const char* rootName, const char* histName, int binx, int biny, const char* legendName)
{
 isInput = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 TH2D *hist_2D = (TH2D *)file[Number]->Get(histName);

 if(binx == 0){
//   h1[Number] = new TH1D(legendName, legendName, hist_2D->GetNbinsX(), hist_2D->GetXaxis()->GetBinLowEdge(1), hist_2D->GetXaxis()->GetBinUpEdge(hist_2D->GetNbinsX()));
   if(!isDefineHist) h1[Number] = hist_2D->ProjectionX(hist_2D->GetName() + (TString)"_px_" + (int)biny, biny, biny);

   for(int ibin = 1; ibin <= hist_2D->GetNbinsX(); ibin++){
     h1[Number]->SetBinContent(ibin, hist_2D->GetBinContent(ibin, biny));
     h1[Number]->SetBinError(ibin, hist_2D->GetBinError(ibin, biny));
   }
 }
 else if(biny == 0){
//   h1[Number] = new TH1D(legendName, legendName, hist_2D->GetNbinsY(), hist_2D->GetYaxis()->GetBinLowEdge(1), hist_2D->GetYaxis()->GetBinUpEdge(hist_2D->GetNbinsY()));
   if(!isDefineHist) h1[Number] = hist_2D->ProjectionY(hist_2D->GetName() + (TString)"_py_" + (int)binx, binx, binx);

   for(int ibin = 1; ibin <= hist_2D->GetNbinsY(); ibin++){
     h1[Number]->SetBinContent(ibin, hist_2D->GetBinContent(binx, ibin));
     h1[Number]->SetBinError(ibin, hist_2D->GetBinError(binx, ibin));
   }
 }

 myLegendName[Number] = legendName;

 if(isRebin)
 {
  cout<<"Histogram has been rebinned."<<endl;
  if(RebinType == 1) h1[Number]->Rebin(ngroup);
  if(RebinType == 2) h1[Number] = (TH1D *)h1[Number]->Rebin(ngroup, histName, rebin);
  if(is2D) {cout<<"Error: 2D histogram cannot be rebined"<<endl; return;}
 }

 if(isDivideBinWidth[Number]){
   for(int ibin = 0; ibin < h1[Number]->GetNbinsX(); ibin ++){
     cout<<(h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1))<<endl;
     h1[Number]->SetBinContent(ibin + 1, h1[Number]->GetBinContent(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     h1[Number]->SetBinError(ibin + 1, h1[Number]->GetBinError(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     cout<<h1[Number]->GetBinContent(ibin + 1)<<endl;
   }
 }
}

void THStackFigure::InputTree(int Number, const char* rootName, const char* treeName, const char* histName, int nbin, double left, double right, const char* VariableName, const char* WeightName, const char* legendName)
{
 isInput = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 tree[Number] = (TTree *)file[Number]->Get(treeName);

 h1[Number] = new TH1D(histName, histName, nbin, left, right);
 tree[Number]->Draw((TString)VariableName + ">>" + h1[Number]->GetName(), WeightName, "goff");

 myLegendName[Number] = legendName;

}

void THStackFigure::InputError(int Number, const char* rootName, const char* histName, const char* legendName)
{
 isInputError = true;

 ErrorFile[Number] = new TFile(rootName);

 HistError[Number] = (TH1D *)ErrorFile[Number]->Get(histName);

 HistError[Number]->SetFillStyle(3354);
 HistError[Number]->SetFillColor(kBlack);
}

void THStackFigure::InputStack(int Number, const char* rootName, const char* histName, TString legendName, Color_t color)
{
 isInputStack = true;
 
 StackFigureCount++;
 StackColor[legendName] = color;

 StackFile[Number] = new TFile(rootName);
 
 if(!isDefineHist) StackHist[Number] = (TH1D *)StackFile[Number]->Get(histName);
 if(isDefineHist){
   tmpStackHist[Number] = (TH1D *)StackFile[Number]->Get(histName);
   for(int ibin = 1; ibin <= tmpStackHist[Number]->GetNbinsX(); ibin++){
     StackHist[Number]->SetBinContent(ibin, tmpStackHist[Number]->GetBinContent(ibin));
     StackHist[Number]->SetBinError(ibin, tmpStackHist[Number]->GetBinError(ibin));
   }
 }

 myStackLegendName[Number] = legendName;

 if(isRebin)
 {
  cout<<"Histogram has been rebinned."<<endl;
  if(RebinType == 1) StackHist[Number]->Rebin(ngroup);
  if(RebinType == 2) StackHist[Number] = (TH1D *)StackHist[Number]->Rebin(ngroup, histName, rebin);
  if(is2D) {cout<<"Error: 2D histogram cannot be rebined"<<endl; return;}
 }

 if(isDivideBinWidth[Number]){
   for(int ibin = 0; ibin < StackHist[Number]->GetNbinsX(); ibin ++){
     cout<<(StackHist[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - StackHist[Number]->GetXaxis()->GetBinLowEdge(ibin + 1))<<endl;
     StackHist[Number]->SetBinContent(ibin + 1, StackHist[Number]->GetBinContent(ibin + 1) / (StackHist[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - StackHist[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     StackHist[Number]->SetBinError(ibin + 1, StackHist[Number]->GetBinError(ibin + 1) / (StackHist[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - StackHist[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     cout<<StackHist[Number]->GetBinContent(ibin + 1)<<endl;
   }
 }

 StackHist[Number]->SetFillColor(color);
 StackHist[Number]->SetLineColor(kBlack);
 StackHist[Number]->SetLineWidth(2);
 StackHist[Number]->SetMarkerSize(0);

 myStack->Add(StackHist[Number]);

// cout<<"Integral of "<<legendName<<": "<<StackHist[Number]->Integral()<<endl;
// cout<<legendName<<": mmm: "<<StackHist[Number]->GetBinContent(2)<<" mme: "<<StackHist[Number]->GetBinContent(3)<<" eem: "<<StackHist[Number]->GetBinContent(4)<<" eee: "<<StackHist[Number]->GetBinContent(5)<<endl;
}

void THStackFigure::InputStack2D(int Number, const char* rootName, const char* histName, int binx, int biny, TString legendName, Color_t color)
{
 isInputStack = true;

 StackFigureCount++;
 StackColor[legendName] = color;

 StackFile[Number] = new TFile(rootName);

 TH2D *hist_2D = (TH2D *)StackFile[Number]->Get(histName);

 if(binx == 0){
   if(!isDefineHist) StackHist[Number] = hist_2D->ProjectionX(hist_2D->GetName() + (TString)"_px_" + (int)biny, biny, biny);

   for(int ibin = 1; ibin <= hist_2D->GetNbinsX(); ibin++){
     StackHist[Number]->SetBinContent(ibin, hist_2D->GetBinContent(ibin, biny));
     StackHist[Number]->SetBinError(ibin, hist_2D->GetBinError(ibin, biny));
   }
 }
 else if(biny == 0){
   if(!isDefineHist) StackHist[Number] = hist_2D->ProjectionY(hist_2D->GetName() + (TString)"_py_" + (int)binx, binx, binx);

   for(int ibin = 1; ibin <= hist_2D->GetNbinsY(); ibin++){
     StackHist[Number]->SetBinContent(ibin, hist_2D->GetBinContent(binx, ibin));
     StackHist[Number]->SetBinError(ibin, hist_2D->GetBinError(binx, ibin));
   }
 }

 myStackLegendName[Number] = legendName;

 if(isDivideBinWidth[Number]){
   for(int ibin = 0; ibin < StackHist[Number]->GetNbinsX(); ibin ++){
     cout<<(StackHist[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - StackHist[Number]->GetXaxis()->GetBinLowEdge(ibin + 1))<<endl;
     StackHist[Number]->SetBinContent(ibin + 1, StackHist[Number]->GetBinContent(ibin + 1) / (StackHist[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - StackHist[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     StackHist[Number]->SetBinError(ibin + 1, StackHist[Number]->GetBinError(ibin + 1) / (StackHist[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - StackHist[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     cout<<StackHist[Number]->GetBinContent(ibin + 1)<<endl;
   }
 }

 StackHist[Number]->SetFillColor(color);
 StackHist[Number]->SetLineColor(kBlack);
 StackHist[Number]->SetLineWidth(2);
 StackHist[Number]->SetMarkerSize(0);

 myStack->Add(StackHist[Number]);
}

void THStackFigure::InputTreeStack(int Number, const char* rootName, const char* treeName, const char* histName, int nbin, double left, double right, const char* VariableName, const char* WeightName, const char* legendName, Color_t color)
{
 isInputStack = true;

 StackFigureCount++;
 StackColor[legendName] = color;

 StackFile[Number] = new TFile(rootName);

 tree[Number] = (TTree *)StackFile[Number]->Get(treeName);

 StackHist[Number] = new TH1D(histName, histName, nbin, left, right);
 tree[Number]->Draw((TString)VariableName + ">>" + h1[Number]->GetName(), WeightName, "goff");

 myStackLegendName[Number] = legendName;

 StackHist[Number]->SetFillColor(color);
 StackHist[Number]->SetLineColor(kBlack);
 StackHist[Number]->SetLineWidth(2);
 StackHist[Number]->SetMarkerSize(0);

 myStack->Add(StackHist[Number]);

}

void THStackFigure::ChangeStackScale(int Number, double scale)
{
 StackHist[Number]->Scale(scale);
}

void THStackFigure::InputCustomStack(int Number, int histNumber1, int histNumber2, TString process, TString legendName, Color_t color)
{
 isInputStack = true;

 StackFigureCount++;
 StackColor[legendName] = color;

 TH1D* tmpHist;
 if(histNumber1 > 0) StackHist[Number] = (TH1D *)h1[histNumber1]->Clone((TString)"StackHist_" + (int)Number);
 if(histNumber2 > 0) tmpHist = (TH1D *)h1[histNumber2]->Clone((TString)"tmpHist" + (int)histNumber2);

 if((TString)process == "Plus"){
   StackHist[Number]->Add(tmpHist);
 }
 if((TString)process == "Minus"){
   StackHist[Number]->Add(tmpHist, -1);
 }
 if((TString)process == "Divide"){
   StackHist[Number]->Divide(tmpHist);
 }
 if((TString)process == "Pull"){
   for(int ibin = 1; ibin <= StackHist[Number]->GetNbinsX(); ibin++){
     StackHist[Number]->SetBinContent(ibin, (StackHist[Number]->GetBinContent(ibin) - tmpHist->GetBinContent(ibin)) / sqrt(StackHist[Number]->GetBinError(ibin) * StackHist[Number]->GetBinError(ibin) + tmpHist->GetBinError(ibin) * tmpHist->GetBinError(ibin)));
   }
 }

 myStackLegendName[Number] = legendName;

 if(isRebin)
 {
  cout<<"Histogram has been rebinned."<<endl;
  if(RebinType == 1) StackHist[Number]->Rebin(ngroup);
  if(RebinType == 2) StackHist[Number] = (TH1D *)StackHist[Number]->Rebin(ngroup, legendName, rebin);
  if(is2D) {cout<<"Error: 2D histogram cannot be rebined"<<endl; return;}
 }

 StackHist[Number]->SetFillColor(color);
 StackHist[Number]->SetLineColor(kBlack);
 StackHist[Number]->SetLineWidth(2);
 StackHist[Number]->SetMarkerSize(0);

 myStack->Add(StackHist[Number]);
}

void THStackFigure::SumStack(const char* LegendName)
{
 if(!isInputStack) return;

 MergedStackHist = (TH1D *)StackHist[1]->Clone("MergedStackHist");
 for(int ihist = 2; ihist <= StackFigureCount; ihist++){
   MergedStackHist->Add(StackHist[ihist]);
 }

 MergedLegendName = LegendName;
}

//Custom
void THStackFigure::SetCustomPad(int TotalPadNumber)
{
 if(!isCustom){
   cout<<"Please set mode to CUSTOM"<<endl;
   return;
 }

 this->TotalPadNumber = TotalPadNumber;

}

void THStackFigure::DefineCustomHist(int Number, int histNumber1, int histNumber2, TString process, const char* LegendName)
{
 tmpHist[Number] = (TH1D *)h1[histNumber1]->Clone("tmp");
 if((TString)process == "Plus"){
   tmpHist[Number]->Add(h1[histNumber2]);
 }
 if((TString)process == "Minus"){
   tmpHist[Number]->Add(h1[histNumber2], -1);
 }
 if((TString)process == "Divide"){
   tmpHist[Number]->Divide(h1[histNumber2]);
 }
 if((TString)process == "Pull"){
   for(int ibin = 1; ibin <= h1[histNumber1]->GetNbinsX(); ibin++){
     tmpHist[Number]->SetBinContent(ibin, (h1[histNumber1]->GetBinContent(ibin) - h1[histNumber2]->GetBinContent(ibin)) / sqrt(h1[histNumber1]->GetBinError(ibin) * h1[histNumber1]->GetBinError(ibin) + h1[histNumber2]->GetBinError(ibin) * h1[histNumber2]->GetBinError(ibin)));
   }
 }
 if((TString)process == "Quadrature"){
   for(int ibin = 1; ibin <= h1[histNumber1]->GetNbinsX(); ibin++){
     tmpHist[Number]->SetBinContent(ibin, sqrt(h1[histNumber1]->GetBinContent(ibin) * h1[histNumber1]->GetBinContent(ibin) + h1[histNumber2]->GetBinContent(ibin) * h1[histNumber2]->GetBinContent(ibin)));
   }
 }
 if((TString)process == "InheritError"){
   for(int ibin = 1; ibin <= tmpHist[Number]->GetNbinsX(); ibin++){
     tmpHist[Number]->SetBinError(ibin, h1[histNumber2]->GetBinError(ibin));
   }
 }
 if((TString)process == "CombineError"){
   for(int ibin = 1; ibin <= tmpHist[Number]->GetNbinsX(); ibin++){
     double Error1 = tmpHist[Number]->GetBinError(ibin);
     double Error2 = h1[histNumber2]->GetBinError(ibin);
     double Error = sqrt(Error1 * Error1 + Error2 * Error2);
     tmpHist[Number]->SetBinError(ibin, Error);
   }
 }

 myLegendName[Number] = LegendName;

 int tmpNumber = Number;
 if(tmpNumber <= FigureCount) return;
 h1[tmpNumber] = (TH1D *)tmpHist[Number]->Clone((TString)"tmp_" + (int)Number);

 FigureCount++;

 if((TString)process == "") return;

}

void THStackFigure::CustomSetting(int PadNumber, int histNumber1, int histNumber2, TString process)
{
 if(!isCustom){
   cout<<"Please set mode to CUSTOM"<<endl;
   return;
 }
 if(!isInput){
   cout<<"Please input at first"<<endl;
   return;
 }
 if(PadNumber > TotalPadNumber){
   cout<<"Out of pad range"<<endl;
   return;
 }

 CustomFigureCount[PadNumber]++;

 int Number = CustomFigureCount[PadNumber];

 if(histNumber1 > 0) Custom[PadNumber][Number] = (TH1D *)h1[histNumber1]->Clone((TString)"Custom_" + (int)PadNumber + (TString)"_" + (int)Number);
 if(histNumber1 > 0) myCustomLegendName[PadNumber][Number] = myLegendName[histNumber1];

 if(histNumber1 == -1) Custom[PadNumber][Number] = (TH1D *)MergedStackHist->Clone((TString)"Custom_" + (int)PadNumber + (TString)"_" + (int)Number);
 if(histNumber1 == -1) myCustomLegendName[PadNumber][Number] = MergedLegendName;
 if(histNumber1 == -1) Custom[PadNumber][Number]->SetFillStyle(3354);
 if(histNumber1 == -1) Custom[PadNumber][Number]->SetFillColor(kBlack);
 if(histNumber1 == -1 && histNumber2 == -1) isResetError[PadNumber][Number] = true;

 TH1D* tmpHist;
 if(histNumber2 > 0) tmpHist = (TH1D *)h1[histNumber2]->Clone((TString)"tmpHist" + (int)histNumber2);
 if(histNumber2 == -1) tmpHist = (TH1D *)MergedStackHist->Clone("tmpHist_MergedStackHist");


 if((TString)process == "Plus"){
   Custom[PadNumber][Number]->Add(tmpHist);
 }
 if((TString)process == "Minus"){
   Custom[PadNumber][Number]->Add(tmpHist, -1);
 }
 if((TString)process == "Divide"){
//   cout<<myCustomLegendName[PadNumber][Number]<<" "<<Custom[PadNumber][Number]->Integral() / MergedStackHist->Integral()<<endl;
   double Chi2 = 0.0;
   for(int ibin = 1; ibin <= tmpHist->GetNbinsX(); ibin++){
     Chi2 += (Custom[PadNumber][Number]->GetBinContent(ibin) - tmpHist->GetBinContent(ibin)) * (Custom[PadNumber][Number]->GetBinContent(ibin) - tmpHist->GetBinContent(ibin)) / (Custom[PadNumber][Number]->GetBinError(ibin) * Custom[PadNumber][Number]->GetBinError(ibin) + tmpHist->GetBinError(ibin) * tmpHist->GetBinError(ibin));
     //cout<<Custom[PadNumber][Number]->GetBinContent(ibin)<<" "<<tmpHist->GetBinContent(ibin)<<endl;
   }
   cout<<"Chi2: "<<Chi2<<endl;

   Custom[PadNumber][Number]->Divide(tmpHist);
 }
 if((TString)process == "Pull"){
   for(int ibin = 1; ibin <= Custom[PadNumber][Number]->GetNbinsX(); ibin++){
     Custom[PadNumber][Number]->SetBinContent(ibin, (Custom[PadNumber][Number]->GetBinContent(ibin) - tmpHist->GetBinContent(ibin)) / sqrt(Custom[PadNumber][Number]->GetBinError(ibin) * Custom[PadNumber][Number]->GetBinError(ibin) + tmpHist->GetBinError(ibin) * tmpHist->GetBinError(ibin)));
   }
 }
 if((TString)process == "InheritError"){
   for(int ibin = 1; ibin <= Custom[PadNumber][Number]->GetNbinsX(); ibin++){
     Custom[PadNumber][Number]->SetBinError(ibin, tmpHist->GetBinError(ibin));
   }
 }
 if((TString)process == "") return;

// if(histNumber2 != 0) delete tmpHist;
}

void THStackFigure::SetCustomPlotFormat(int PadNumber, int Number, Color_t Color, Style_t style)
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 Custom[PadNumber][Number]->SetMarkerStyle(style);
 Custom[PadNumber][Number]->SetMarkerColor(Color);
 Custom[PadNumber][Number]->SetMarkerSize(1);
 Custom[PadNumber][Number]->SetLineWidth(4);
 Custom[PadNumber][Number]->SetLineColor(Color);
 Custom[PadNumber][Number]->SetFillColor(Color);
 Custom[PadNumber][Number]->SetLineStyle(1);

 if(isResetError[PadNumber][Number]){
   Custom[PadNumber][Number]->SetMarkerSize(0);
   Custom[PadNumber][Number]->SetLineWidth(0);
 }
//   legend1->AddEntry(h1[Number], myLegendName[Number],"lpfe");
}

void THStackFigure::SetPadTitle(int PadNumber, const char* PadName)
{
 myPadName[PadNumber] = PadName;
}

void THStackFigure::SetCustomYRange(int PadNumber, double ymin, double ymax)
{
 isSetCustomYRange[PadNumber] = true;

 CustomYRangeMin[PadNumber] = ymin;
 CustomYRangeMax[PadNumber] = ymax;
}

void THStackFigure::SetCustomLegendSize(int PadNumber, double size)
{
 CustomLegendSize[PadNumber] = size;
}

void THStackFigure::SetLegendNColumn(int NColumn)
{
 this->NColumn = NColumn;
}

void THStackFigure::CustomNorm(int PadNumber, int fig1, int fig2, int BaseOne)
{
 if(!isCustom){
   cout<<"Please set mode to CUSTOM"<<endl;
   return;
 }
 if(!isInput){
   cout<<"Please input at first"<<endl;
   return;
 }

 if(PadNumber == 0){
   double figsum1;
   double figsum2;
   if(fig1 == -1) figsum1 = MergedStackHist->Integral();
   else figsum1 = h1[fig1]->Integral();

   if(fig2 == -1) figsum2 = MergedStackHist->Integral();
   else figsum2 = h1[fig2]->Integral();

   if(BaseOne == 1) h1[fig2]->Scale(figsum1 / figsum2);
   if(BaseOne == 2) h1[fig1]->Scale(figsum2 / figsum1);

   if(BaseOne == 1) cout<<(figsum1 / figsum2)<<endl;
   if(BaseOne == 2) cout<<(figsum2 / figsum1)<<endl;

   return;
 }

 double figsum1 = Custom[PadNumber][fig1]->Integral();
 double figsum2 = Custom[PadNumber][fig2]->Integral();

 if(BaseOne == 1) Custom[PadNumber][fig2]->Scale(figsum1 / figsum2);
 if(BaseOne == 2) Custom[PadNumber][fig1]->Scale(figsum2 / figsum1);
}

void THStackFigure::SetCustomError(int Number, int ErrorNumber)
{
 if(!isInputError) return;

 if(Number != -1){
   for(int ibin = 0; ibin < h1[Number]->GetNbinsX(); ibin++){
     h1[Number]->SetBinError(ibin + 1, HistError[ErrorNumber]->GetBinError(ibin + 1));
   }
 }

 if(Number == -1){
   for(int ibin = 0; ibin < MergedStackHist->GetNbinsX(); ibin++){
     MergedStackHist->SetBinError(ibin + 1, HistError[ErrorNumber]->GetBinError(ibin + 1));
   }
 }

}

void THStackFigure::SetXRange(double xmin, double xmax)
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 if(!is2D){
   h1[1]->GetXaxis()->SetRangeUser(xmin, xmax);
   if(withPDFError) PDF1[1]->GetXaxis()->SetRangeUser(xmin, xmax);

   this->XRangeMin = xmin;
   this->XRangeMax = xmax;
 }

 isSetXRange = true;
}

void THStackFigure::AddText(int Number, const char* TextContent)
{
 if(Number == 0) {cout<<"WARNING!! Please add text from No.1"<<endl;}
 myText[Number] = TextContent;

 TextCount++;
}

void THStackFigure::SetYRange(double ymin, double ymax, int iPlot)
{
 if(is2D){
  cout<<"SetYRange is only for single plot."<<endl;
  cout<<"Other plot type please use other tools."<<endl;
  return;
 }

 isSetYRange = true;

 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 if(!is2D){
   if(iPlot == 0){
     isSetYRange0 = true;
     isSetYRange = false;
     this->ymin = ymin;
     this->ymax = ymax;
     return;
   }
   h1[iPlot]->GetYaxis()->SetRangeUser(ymin, ymax);
 }
}

void THStackFigure::Draw()
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 if(isPDF) isSingle = false;

 TPad *pad1;
 TPad *pad2;
 TPad *pad3;
 if((isRatio || isDelta || isDeltaSigma) && !isPDF)
 {
  /****************************************/
  /*********Ratio/Delta/Pull Plot**********/
  /****************************************/
//  double sum1 = h1[1]->Integral();
//  double sum2 = h1[2]->Integral();
//  if(isNorm) h1[1]->Scale(sum2 / sum1);

  MyN = new TCanvas("MyN","MyN",700,700);
  gStyle->SetGridWidth(1);
  MyN->cd();
  pad1 = new TPad("pad1", "pad1", 0, 0.25, 1.0, 1.0);
  BottomMargin = 0;
  TopMargin = 0.15;
  LeftMargin = 0.15;
  RightMargin = 0.05;
  pad1->SetBottomMargin(BottomMargin);
  pad1->SetTopMargin(TopMargin);
  pad1->SetLeftMargin(LeftMargin);
  pad1->SetRightMargin(RightMargin);
//  pad1->SetGridx();
//  pad1->SetGridy();
  pad1->Draw();
  pad1->cd();

  myStack->SetTitle("");
//  myStack->SetStats(0);

  if(isE0)
  {
   myStack->Draw("HIST");
   h1[1]->Draw("E0 same");
  }
  if(isHIST)
  {
   myStack->Draw("HIST");
   h1[1]->Draw("HIST same");
  }

  h1[1]->GetYaxis()->SetTitle(myYTitle);
  h1[1]->GetYaxis()->SetTitleSize(0.06);
  h1[1]->GetYaxis()->SetTitleFont(42);
  h1[1]->GetYaxis()->SetTitleOffset(0.7);

  h1[1]->GetYaxis()->SetLabelSize(0.04);
  h1[1]->GetYaxis()->SetLabelFont(42);

  h1[1]->SetMarkerStyle(7);
  h1[1]->SetMarkerColor(kRed+1);
  h1[1]->SetLineWidth(3);
  h1[1]->SetLineColor(kRed+1);

  YRangeMax = h1[1]->GetMaximum();
  YRangeMin = h1[1]->GetMinimum();

  if(YRangeMax < MergedStackHist->GetMaximum()) YRangeMax = MergedStackHist->GetMaximum();
  if(YRangeMin < MergedStackHist->GetMinimum()) YRangeMin = MergedStackHist->GetMinimum();

  if(!isSetXRange){
    XRangeMax = h1[1]->GetXaxis()->GetBinUpEdge(h1[1]->GetNbinsX());
    XRangeMin = h1[1]->GetXaxis()->GetBinLowEdge(1);
  }

  int iPlot = 2;

  if(XRangeMax < h1[1]->GetXaxis()->GetBinUpEdge(h1[1]->GetNbinsX())) XRangeMax = h1[1]->GetXaxis()->GetBinUpEdge(h1[1]->GetNbinsX());
  if(XRangeMin > h1[1]->GetXaxis()->GetBinLowEdge(1)) XRangeMin = h1[1]->GetXaxis()->GetBinLowEdge(1);

  if(isLogX) gPad->SetLogx();
  if(isLogY) gPad->SetLogy();

  if(!isSetYRange) h1[1]->GetYaxis()->SetRangeUser(YRangeMin - fabs(YRangeMin) * 0.1, YRangeMax + fabs(YRangeMax) * 0.3);
  if(!isSetYRange) myStack->SetMaximum(YRangeMax + fabs(YRangeMax) * 0.3);

  double textlength = (legendymax - legendymin) / 2;
  int iText = 0;
  while(iText<=TextCount){
    iText++;
    text[iText] = new TLatex();

    TextX = XRangeMin + (XRangeMax - XRangeMin) * legendxmin;
    TextY = (YRangeMax + fabs(YRangeMax) * 0.1) - (YRangeMax + fabs(YRangeMax) * 0.1 - YRangeMin + fabs(YRangeMin) * 0.1) * ((1 - legendymax) + iText * textlength);
    text[iText]->SetText(TextX, TextY, myText[iText]);
    text[iText]->SetTextSize(0.04);
    text[iText]->SetTextFont(42);
    text[iText]->Draw("same");
  }

  double steplength = legendymax - legendymin;
  legendymax = legendymax - (TextCount + 0.5) * 0.5 * steplength;
  legendymin = legendymin - (TextCount + 0.5) * 0.5 * steplength;

  legend1 = new TLegend(legendxmin * (1 - LeftMargin - RightMargin) + LeftMargin, legendymin * (1 - TopMargin - BottomMargin) + BottomMargin, legendxmax * (1 - LeftMargin - RightMargin) + LeftMargin, legendymax * (1 - TopMargin - BottomMargin) + BottomMargin);

  legend1->AddEntry(h1[1], myLegendName[1],"lpe");
  for(int ihist = 1; ihist <= StackFigureCount; ihist++){
    legend1->AddEntry(StackHist[ihist], myStackLegendName[ihist], "f");
  }
  legend1->SetNColumns(1);
  legend1->Draw("same");
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetLineColor(0);
  legend1->SetLineWidth(0);
  legend1->SetTextSize(0.04);
  legend1->SetTextFont(42);

  MyN->cd();
  pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.25);
  BottomMargin = 0.3;
  TopMargin = 0;
  LeftMargin = 0.15;
  RightMargin = 0.05;
  pad2->SetBottomMargin(BottomMargin);
  pad2->SetTopMargin(TopMargin);
  pad2->SetLeftMargin(LeftMargin);
  pad2->SetRightMargin(RightMargin);
  pad2->SetGridx();
  pad2->SetGridy();
  pad2->Draw();
  pad2->cd();

  h1[0] = (TH1D*)h1[1]->Clone("h0");

  if(isRatio) h1[0]->Divide(MergedStackHist);
  if(isDelta) h1[0]->Add(MergedStackHist, -1);
  if(isDeltaSigma)
  {
   for(int ibin = 1; ibin < h1[1]->GetNbinsX() + 1; ibin++)
   {
    h1[0]->SetBinContent(ibin, (h1[1]->GetBinContent(ibin) - MergedStackHist->GetBinContent(ibin)) / sqrt(h1[1]->GetBinError(ibin) * h1[1]->GetBinError(ibin) + MergedStackHist->GetBinError(ibin) * MergedStackHist->GetBinError(ibin)));
   }
  }

  h1[0]->SetTitle("");
  h1[0]->SetStats(0);
  if(isE0) h1[0]->Draw("E0");
  if(isHIST) h1[0]->Draw("HIST");

  h1[0]->GetYaxis()->SetNdivisions(505);

  if(isRatio) h1[0]->GetYaxis()->SetTitle("#frac{" + myLegendName[1] + "}{" + myLegendName[2] + "}");
  if(isDelta) h1[0]->GetYaxis()->SetTitle("#Delta" + myYTitle);
  if(isDeltaSigma) h1[0]->GetYaxis()->SetTitle("#frac{#Delta}{#sigma}");

  if(!isSetYRange0) h1[0]->GetYaxis()->SetRangeUser(h1[0]->GetMinimum() / 1.01, h1[0]->GetMaximum() * 1.01);
  else h1[0]->GetYaxis()->SetRangeUser(ymin, ymax);

  h1[0]->GetYaxis()->SetTitleSize(0.1);
  h1[0]->GetYaxis()->SetTitleFont(42);
  h1[0]->GetYaxis()->SetTitleOffset(0.4);

  h1[0]->GetYaxis()->SetLabelFont(42);// Absolute font size in pixel (precision 3)
  h1[0]->GetYaxis()->SetLabelSize(0.1);

  h1[0]->SetLineWidth(2);

  h1[0]->GetXaxis()->SetTitle(myXTitle);
  h1[0]->GetXaxis()->SetTitleSize(0.12);
  h1[0]->GetXaxis()->SetTitleFont(42);
  h1[0]->GetXaxis()->SetTitleOffset(1);

  h1[0]->GetXaxis()->SetLabelSize(0.12);
  h1[0]->GetXaxis()->SetLabelFont(42);

  if(isLogX) gPad->SetLogx();
  if(isLogY) gPad->SetLogy();
 }

 if(isCustom)
 {
   MyN = new TCanvas("MyN","MyN",1000,1000);
   MyN->cd();
   if(isLogX) gPad->SetLogx();
   if(isLogY){
     gPad->SetLogy();
   }
   gStyle->SetGridWidth(1);

   if(TotalPadNumber == 1){

   }

   if(TotalPadNumber == 2){
     pad1 = new TPad("pad1", "pad1", 0, 0.25, 1.0, 1.0);
     BottomMargin = 0;
     TopMargin = 0.15;
     LeftMargin = 0.15;
     RightMargin = 0.05;
     pad1->SetBottomMargin(BottomMargin);
     pad1->SetTopMargin(TopMargin);
     pad1->SetLeftMargin(LeftMargin);
     pad1->SetRightMargin(RightMargin);
     pad1->Draw();
     pad1->cd();

     Custom[1][1]->SetTitle("");
     Custom[1][1]->SetStats(0);

     Custom[1][1]->GetYaxis()->SetTitle(myYTitle);
     Custom[1][1]->GetYaxis()->SetTitleSize(0.06);
     Custom[1][1]->GetYaxis()->SetTitleFont(42);
     Custom[1][1]->GetYaxis()->SetTitleOffset(0.7);

     Custom[1][1]->GetYaxis()->SetLabelSize(0.04);
     Custom[1][1]->GetYaxis()->SetLabelFont(42);

//     Custom[1][1]->SetMarkerStyle(7);
//     Custom[1][1]->SetMarkerColor(kBlue+1);
//     Custom[1][1]->SetLineWidth(3);
//     Custom[1][1]->SetLineColor(kBlue+1);

     myStack->SetTitle("");

     if(isDrawStack) myStack->Draw("HIST");
     myStack->GetYaxis()->SetTitle(myYTitle);

     if(isLogY){
       for(int iPlot = 1; iPlot <= CustomFigureCount[1]; iPlot++){
         for(int ibin = 1; ibin <= Custom[1][iPlot]->GetNbinsX(); ibin++){
           if(Custom[1][iPlot]->GetBinContent(ibin) <= 1e-9){
             Custom[1][iPlot]->SetBinContent(ibin, 1e-9);
             Custom[1][iPlot]->SetBinError(ibin, 1e-9);
           }
         }
       }
     }

     if(isE0 && !isResetError[1][1]) Custom[1][1]->Draw("E0 same");
     if(isHIST && !isResetError[1][1]) Custom[1][1]->Draw("HIST same");
     if(isResetError[1][1]) Custom[1][1]->Draw("E2 same");

     YRangeMax = Custom[1][1]->GetMaximum();
     YRangeMin = Custom[1][1]->GetMinimum();
     if(!isSetXRange){
       XRangeMax = Custom[1][1]->GetXaxis()->GetBinUpEdge(Custom[1][1]->GetNbinsX());
       XRangeMin = Custom[1][1]->GetXaxis()->GetBinLowEdge(1);
     }

     int iPlot = 1;
     while(iPlot <= CustomFigureCount[1]){
      if(isE0 && !isResetError[1][iPlot]) Custom[1][iPlot]->Draw("E0 same");
      if(isHIST && !isResetError[1][iPlot]) Custom[1][iPlot]->Draw("HIST same");
      if(isResetError[1][iPlot]) Custom[1][iPlot]->Draw("E2 same");

      if(isResetError[1][iPlot]){
        iPlot++;
        continue;
      }

      if(YRangeMax < Custom[1][iPlot]->GetMaximum()) YRangeMax = Custom[1][iPlot]->GetMaximum();
      if(YRangeMin > Custom[1][iPlot]->GetMinimum()) YRangeMin = Custom[1][iPlot]->GetMinimum();
      if(YRangeMax < MergedStackHist->GetMaximum()) YRangeMax = MergedStackHist->GetMaximum();
      if(YRangeMin < MergedStackHist->GetMinimum()) YRangeMin = MergedStackHist->GetMinimum();
      if(!isSetXRange){
        if(XRangeMax < Custom[1][iPlot]->GetXaxis()->GetBinUpEdge(Custom[1][iPlot]->GetNbinsX())) XRangeMax = Custom[1][iPlot]->GetXaxis()->GetBinUpEdge(Custom[1][iPlot]->GetNbinsX());
        if(XRangeMin > Custom[1][iPlot]->GetXaxis()->GetBinLowEdge(1)) XRangeMin = Custom[1][iPlot]->GetXaxis()->GetBinLowEdge(1);
      }
      iPlot++;
     }

     if(isLogX) gPad->SetLogx();
     if(isLogY){
       gPad->SetLogy();
     }

     if(!isSetCustomYRange[1]) Custom[1][1]->GetYaxis()->SetRangeUser(YRangeMin - fabs(YRangeMin) * 0.1, YRangeMax + fabs(YRangeMax) * 0.3);
     if(!isSetYRange && isDrawStack) myStack->SetMaximum(YRangeMax + fabs(YRangeMax) * 0.3);

     if(isSetXRange) Custom[1][1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     if(isSetCustomYRange[1]){
       Custom[1][1]->GetYaxis()->SetRangeUser(CustomYRangeMin[1], CustomYRangeMax[1]);
       myStack->GetYaxis()->SetRangeUser(CustomYRangeMin[1], CustomYRangeMax[1]);
       myStack->SetMinimum(CustomYRangeMin[1]);
       myStack->SetMaximum(CustomYRangeMax[1]);
     }

     double textlength = (legendymax - legendymin) / (CustomFigureCount[1] + 1);
     int iText = 0;
     while(iText<=TextCount){
       iText++;
       text[iText] = new TLatex();

       TextX = XRangeMin + (XRangeMax - XRangeMin) * legendxmin * 1.05;
       TextY = (YRangeMax + fabs(YRangeMax) * 0.3) - (YRangeMax + fabs(YRangeMax) * 0.3) * ((1 - legendymax) + iText * textlength);

       if(isLogX) TextX = pow(10, (log10(XRangeMin) + (0 - log10(XRangeMin)) * legendxmin));
       TextY = (YRangeMax + fabs(YRangeMax) * 0.3) - (YRangeMax + fabs(YRangeMax) * 0.3 - YRangeMin + fabs(YRangeMin) * 0.1) * ((1 - legendymax) + iText * textlength);

       text[iText]->SetText(TextX, TextY, myText[iText]);
       text[iText]->SetTextSize(CustomLegendSize[1]);
       text[iText]->SetTextFont(TextFont[iText]);
       text[iText]->Draw("same");
     }

     double steplength = legendymax - legendymin;
     legendymax = legendymax - (TextCount + 0.5) * (1.0 / (CustomFigureCount[1] + 1)) * steplength;
     legendymin = legendymin - (TextCount + 0.5) * (1.0 / (CustomFigureCount[1] + 1)) * steplength;

     legend1 = new TLegend(legendxmin * (1 - LeftMargin - RightMargin) + LeftMargin, legendymin * (1 - TopMargin - BottomMargin) + BottomMargin, legendxmax * (1 - LeftMargin - RightMargin) + LeftMargin, legendymax * (1 - TopMargin - BottomMargin) + BottomMargin);

     for(int i = 1; i < CustomFigureCount[1] + 1; i++){
       if(!((TString)myCustomLegendName[1][i] == "") && !isResetError[1][i]) legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"lpe");
       if(!((TString)myCustomLegendName[1][i] == "") && isResetError[1][i]) legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"lf");
     }
     for(int ihist = StackFigureCount; ihist >= 1; ihist--){
       if(isDrawStack) legend1->AddEntry(StackHist[ihist], myStackLegendName[ihist], "f");
     }

     legend1->SetNColumns(NColumn);
     legend1->Draw("same");
     legend1->SetFillColor(0);
     legend1->SetFillStyle(0);
     legend1->SetLineColor(0);
     legend1->SetLineWidth(0);
     legend1->SetTextSize(CustomLegendSize[1]);
     legend1->SetTextFont(42);


     MyN->cd();
     pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.25);
     BottomMargin = 0.3;
     TopMargin = 0;
     LeftMargin = 0.15;
     RightMargin = 0.05;
     pad2->SetBottomMargin(BottomMargin);
     pad2->SetTopMargin(TopMargin);
     pad2->SetLeftMargin(LeftMargin);
     pad2->SetRightMargin(RightMargin);
     pad2->SetGridx();
     pad2->SetGridy();
     pad2->Draw();
     pad2->cd();

     Custom[2][1]->SetTitle("");
     Custom[2][1]->SetStats(0);

     if(!isSetYRange0) Custom[2][1]->GetYaxis()->SetRangeUser(Custom[2][1]->GetMinimum() / 1.01, Custom[2][1]->GetMaximum() * 1.01);
     else Custom[2][1]->GetYaxis()->SetRangeUser(ymin, ymax);

     if(isSetXRange) Custom[2][1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     if(isSetCustomYRange[2]) Custom[2][1]->GetYaxis()->SetRangeUser(CustomYRangeMin[2], CustomYRangeMax[2]);

     Custom[2][1]->GetYaxis()->SetTitle(myPadName[2]);
     Custom[2][1]->GetYaxis()->SetTitleSize(0.1);
     Custom[2][1]->GetYaxis()->SetTitleFont(42);
     Custom[2][1]->GetYaxis()->SetTitleOffset(0.4);

     Custom[2][1]->GetYaxis()->SetLabelFont(42);// Absolute font size in pixel (precision 3)
     Custom[2][1]->GetYaxis()->SetLabelSize(0.1);

     Custom[2][1]->GetYaxis()->SetNdivisions(505);

//     Custom[2][1]->SetLineWidth(2);

     Custom[2][1]->GetXaxis()->SetTitle(myXTitle);
     Custom[2][1]->GetXaxis()->SetTitleSize(0.12);
     Custom[2][1]->GetXaxis()->SetTitleFont(42);
     Custom[2][1]->GetXaxis()->SetTitleOffset(1);

     Custom[2][1]->GetXaxis()->SetLabelSize(0.12);
     Custom[2][1]->GetXaxis()->SetLabelFont(42);

     gStyle->SetHatchesLineWidth(2);

     if(isE0 && !isResetError[2][1]) Custom[2][1]->Draw("E0");
     if(isHIST && !isResetError[2][1]) Custom[2][1]->Draw("HIST");
     if(isResetError[2][1]) Custom[2][1]->Draw("E2");

     iPlot = 1;
     while(iPlot <= CustomFigureCount[2]){
      if(isE0 && !isResetError[2][iPlot]) Custom[2][iPlot]->Draw("E0 same");
      if(isHIST && !isResetError[2][iPlot]) Custom[2][iPlot]->Draw("HIST same");
      if(isResetError[2][iPlot]) Custom[2][iPlot]->Draw("E2 same");
      iPlot++;
     }

     if(isLogX) gPad->SetLogx();

   }

 }

 if(DoSave) MyN->SaveAs(myFigureName);

 for(int i = 1; i <= FigureCount; i++){
//   file[i]->Close();
//   delete file[i];
 }

}
