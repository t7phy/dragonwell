// PDFFigure.h: PDF plotter
// Created on 8/31/2023 by Yao Fu

#ifndef PDFHelper_PDFFigure_h
#define PDFHelper_PDFFigure_h

#include <iostream>
#include <dirent.h>
#include <cstring>
#include "RootCommon.h"
#include "Tools/Tools.h"
#ifdef USE_LHAPDF
#include "LHAPDF/LHAPDF.h"
#include "LHAPDF/Reweighting.h"
#endif
#include "CTEQHelper/pdsReader.h"
#include "Uncertainty/PDFUncertainty.h"
#include "Figure/Graph.h"
#include "CTEQHelper/FittingHelper.h"

using namespace std;

class PDFFigure
{
 public:

 TString Option = "Nes";
 TString saveMode = ".pdf";

#ifdef USE_LHAPDF
 map<pair<TString, int>, LHAPDF::PDF*> PDF;
#endif
 map<pair<TString, int>, pdsReader*> CTPDF;

 map<TString, TString> PDFType;
 map<TString, int> PDFnSet;
 map<TString, TString> PDFLegendName;

 vector<double> LogBin;

 map<tuple<TString, int, int, double>, TH1D*> PDFPlot;
 map<tuple<TString, int, int, double>, TH1D*> xPDFPlot;
 map<tuple<TString, int, int, double>, TH1D*> PDFRatio;
 map<tuple<TString, int, int, double>, TH1D*> PDFRatioSelf;
 map<tuple<TString, int, int, double>, TH1D*> PDFRatio68CL;
 map<tuple<TString, int, int, double>, TH1D*> PDFRatioSelf68CL;

 map<tuple<TString, int, double>, TH1D*> PDFErrorPlot;
 map<tuple<TString, int, double>, TH1D*> xPDFErrorPlot;
 map<tuple<TString, int, double>, TH1D*> PDFRatioError;
 map<tuple<TString, int, double>, TH1D*> PDFRatioSelfError;

 map<tuple<TString, int, double>, TH1D*> PDFErrorPlus;
 map<tuple<TString, int, double>, TH1D*> xPDFErrorPlus;
 map<tuple<TString, int, double>, TH1D*> PDFRatioErrorPlus;
 map<tuple<TString, int, double>, TH1D*> PDFRatioSelfErrorPlus;

 map<tuple<TString, int, double>, TH1D*> PDFErrorMinus;
 map<tuple<TString, int, double>, TH1D*> xPDFErrorMinus;
 map<tuple<TString, int, double>, TH1D*> PDFRatioErrorMinus;
 map<tuple<TString, int, double>, TH1D*> PDFRatioSelfErrorMinus;

 map<tuple<TString, int, double>, TH1D*> PDFErrorCentral;
 map<tuple<TString, int, double>, TH1D*> xPDFErrorCentral;
 map<tuple<TString, int, double>, TH1D*> PDFRatioErrorCentral;
 map<tuple<TString, int, double>, TH1D*> PDFRatioSelfErrorCentral;

 map<tuple<TString, int, double>, TH1D*> PDFCorrelation;

 int nErrorPDF;

 PDFFigure(TString Option = "Nes");
 virtual void InitialPDF(TString PDFName, int iSet);
 virtual void InitialSingleLHAPDF(TString PDFName, int iSet);
 virtual void InitialPDFAll(TString PDFName, int nSet);
 virtual void InitialPDFAll(TString PDFName);
 virtual void InitialCTEQPDF(TString GivenName, TString PDFFile, int iSet);
 virtual void InitialCTEQPDFAll(TString GivenName, vector<TString> PDFFiles);
 virtual void InitialCTEQPDF(TString GivenName, pdsReader* pdf, int iSet);
 virtual void InitialCTEQPDFAll(TString GivenName, vector<pdsReader *> PDFFiles);
 virtual void InitialCTEQPDFAll(TString GivenName, TString DirectoryName);
 virtual void InitialSingleCTEQPDF(TString GivenName, TString PDFFile);
 virtual void InitialSingleCTEQPDF(TString GivenName, pdsReader* pdf);

 virtual void GenerateErrorAll(vector<TString> PDFNames, vector<TString> ErrorTypes, double Q);
 virtual void GenerateEigenAll(TString ErrorPDFName, TString EigenPDFName, TString ErrorType, double Q, int nEigenSet);
 virtual void GeneratexPDF(TString PDFName, TString ErrorType, vector<TString> FlavorType, double Q);
 virtual void GenerateSinglePDFAll(vector<TString> ErrorPDFNames, vector<TString> SinglePDFNames, double Q);

 virtual void PreparePDFPlotAll(TString PDFName, double Q);
 virtual void PreparePDFRatio(TString PDFName, int iSet, double Q, TString BaseName);
 virtual void PreparePDFRatioAll(TString PDFName, double Q, TString BaseName);
 virtual void PreparePDFError(TString PDFName, double Q, TString ErrorType);

 virtual TH1D* DrawPDFvsX(TString PDFName, int iSet, int flavor, double Q);
 virtual TH1D* DrawPDFvsQ();
 virtual TH1D* DrawPDFCorrelation(vector<TH1D *> Variable, TString PDFName, int flavor, double Q, TString ErrorType);

 virtual double Getf(TString PDFName, int iSet, int flavor, double x, double Q);

 virtual void ApplyPDFError(TH1D* &central, TH1D* &error){
   for(int ibin = 1; ibin <= central->GetNbinsX(); ibin++){
     central->SetBinError(ibin, error->GetBinContent(ibin));
   }
 }
 virtual void RemoveErrors(TH1D* &hist){
   for(int ibin = 1; ibin <= hist->GetNbinsX(); ibin++){
     hist->SetBinError(ibin, 0.0);
   }
 }

 virtual void GetRatio(TH1D* &numer, TH1D* &denom){
   for(int ibin = 1; ibin <= numer->GetNbinsX(); ibin++){
     if(fabs(denom->GetBinContent(ibin)) < 1e-20){
       numer->SetBinContent(ibin, 0.0);
     }
     else{
       numer->SetBinContent(ibin, numer->GetBinContent(ibin) / denom->GetBinContent(ibin));
     }
   }
 }

 virtual void GetRatio68(TH1D* &numer, TH1D* &denom){
   for(int ibin = 1; ibin <= numer->GetNbinsX(); ibin++){
     if(fabs(denom->GetBinContent(ibin)) < 1e-20){
       numer->SetBinContent(ibin, 0.0);
     }
     else{
       numer->SetBinContent(ibin, ((numer->GetBinContent(ibin) - denom->GetBinContent(ibin)) / 1.645 + denom->GetBinContent(ibin)) / denom->GetBinContent(ibin));
     }
   }
 }

 virtual void ConvertRatioTo68CL(TH1D* &hist90, TH1D* &hist68){
   for(int ibin = 1; ibin <= hist90->GetNbinsX(); ibin++){
     if(fabs(hist90->GetBinContent(ibin)) < 1e-20){
       hist68->SetBinContent(ibin, 0.0);
     }
     else{
       hist68->SetBinContent(ibin, hist90->GetBinContent(ibin) / 1.645 + (1.0 - 1.0 / 1.645));
     }
     hist68->SetBinError(ibin, 0.0);
   }
 }

 virtual void GetxPDF(TH1D* &pdf, TH1D* &xpdf){
   for(int ibin = 1; ibin <= pdf->GetNbinsX(); ibin++){
     xpdf->SetBinContent(ibin, pdf->GetBinContent(ibin) * pdf->GetBinCenter(ibin));
     xpdf->SetBinError(ibin, 0.0);
   }
 }

 TFile* hf;
 bool isLinkFile = false;
 virtual void openFile(TString name){hf = new TFile(name, "RECREATE"); hf->cd(); isLinkFile = true;}
 virtual void LinkFile(TFile* file){hf = file; hf->cd(); isLinkFile = true;}
 virtual void SaveFile(){
   hf->cd();
   //hf->Write();
   hf->Close();
 }

 vector<TString> PlotNames;
 vector<TString> RatioPlotNames;
 vector<TString> RatioSelfPlotNames;
 virtual void OutputTexFile(TString name);

 vector<double> FlavorListAll;
 vector<double> FlavorListNes;
 map<int, TString> FlavorNameMap;
 map<int, TString> TitleMap;
 map<TString, int> FlavorNameIndex;

 virtual void DefineCombination(){
   FittingHelper* Instance = new FittingHelper();
   Instance->DefineCombination(FlavorNameMap, TitleMap, FlavorNameIndex);
   delete Instance;

   for(auto iter = FlavorNameMap.begin(); iter != FlavorNameMap.end(); iter++){
     FlavorListAll.push_back(iter->first);
   }

   FlavorListNes = {0, 1, 2};
 }

 virtual void SetupNesFlavorList(vector<TString> FlavorNames){
   Option = "Nes";

   FlavorListNes.clear();
   FlavorListNes.resize(FlavorNames.size());

   for(int i = 0; i < FlavorNames.size(); i++){
     FlavorListNes.at(i) = FlavorNameIndex[FlavorNames.at(i)];
   }
 }

 map<int, Color_t> PlotFillColor;
 map<int, Color_t> PlotLineColor;
 map<int, Style_t> PlotFillStyle;
 map<int, Style_t> PlotLineStyle;

 map<int, Color_t> EigenLineColor;
 map<int, Style_t> EigenLineStyle;

 map<int, double> PlotYMin;
 map<int, double> PlotYMax;

 map<int, double> xPlotYMin;
 map<int, double> xPlotYMax;

 virtual void DefinePlottingStyle(){
   PlotFillColor[1] = kBlue;
   PlotLineColor[1] = kBlue;
   PlotFillStyle[1] = 3001;
   PlotLineStyle[1] = 1;

   PlotFillColor[2] = kRed;
   PlotLineColor[2] = kRed;
   PlotFillStyle[2] = 3144;
   PlotLineStyle[2] = 2;

   PlotFillColor[3] = kGreen + 2;
   PlotLineColor[3] = kGreen + 2;
   PlotFillStyle[3] = 3004;
   PlotLineStyle[3] = 3;

   PlotFillColor[4] = kMagenta;
   PlotLineColor[4] = kMagenta;
   PlotFillStyle[4] = 3144;
   PlotLineStyle[4] = 5;

   PlotFillColor[5] = kOrange + 7;
   PlotLineColor[5] = kOrange + 7;
   PlotFillStyle[5] = 3144;
   PlotLineStyle[5] = 4;

   PlotFillColor[6] = kCyan;
   PlotLineColor[6] = kCyan;
   PlotFillStyle[6] = 3144;
   PlotLineStyle[6] = 6;

   PlotFillColor[7] = kYellow - 3;
   PlotLineColor[7] = kYellow - 3;
   PlotFillStyle[7] = 3144;
   PlotLineStyle[7] = 7;

   PlotFillColor[8] = kOrange + 10;
   PlotLineColor[8] = kOrange + 10;
   PlotFillStyle[8] = 3144;
   PlotLineStyle[8] = 8;

   EigenLineColor[1] = kRed;
   EigenLineColor[2] = kGreen + 2;
   EigenLineStyle[1] = 1;
   EigenLineStyle[2] = 1;

   EigenLineColor[3] = kRed + 3;
   EigenLineColor[4] = kOrange + 10;
   EigenLineStyle[3] = 2;
   EigenLineStyle[4] = 2;

   EigenLineColor[5] = kYellow - 3;
   EigenLineColor[6] = kCyan;
   EigenLineStyle[5] = 3;
   EigenLineStyle[6] = 3;

   EigenLineColor[7] = kMagenta - 7;
   EigenLineColor[8] = kPink + 1;
   EigenLineStyle[7] = 4;
   EigenLineStyle[8] = 4;

   for(int i = -5; i <= 100; i++){
     PlotYMin[i] = 0.8;
     PlotYMax[i] = 1.2;
   }
   PlotYMin[3] = 0.6;//s
   PlotYMax[3] = 1.4;

   PlotYMin[9] = 0.5;//ubouv
   PlotYMax[9] = 1.5;

   PlotYMin[10] = 0.5;//dbodv
   PlotYMax[10] = 1.5;

   PlotYMin[15] = 0.7;//ubodb
   PlotYMax[15] = 1.3;

   PlotYMin[21] = 0.0;//Rs
   PlotYMax[21] = 2.0;

   xPlotYMin[11] = -0.05;//ubou
   xPlotYMax[11] = 1.35;

   xPlotYMin[12] = -0.05;//dbod
   xPlotYMax[12] = 1.35;

   xPlotYMin[14] = -0.05;//uod
   xPlotYMax[14] = 1.35;

   xPlotYMin[17] = -0.05;//dbou
   xPlotYMax[17] = 1.35;

   xPlotYMin[18] = -0.05;//ubod
   xPlotYMax[18] = 1.35;

   xPlotYMin[15] = -0.05;//ubodb
   xPlotYMax[15] = 1.35;

   xPlotYMin[19] = -0.05;//dboub
   xPlotYMax[19] = 2.35;

   xPlotYMin[20] = -0.05;//dou
   xPlotYMax[20] = 1.35;

   xPlotYMin[21] = 0.0;//Rs
   xPlotYMax[21] = 2.0;

   for(int i = 1; i <= 100; i++){
     PlotNoFill[i] = false;
   }
 }

 map<int, bool> PlotNoFill;
 virtual void SetNoFill(int iPlot){
   PlotNoFill[iPlot] = true;
 }

 virtual void SetYRange(double ymin, double ymax){
   PlotYMin[-99] = ymin;
   PlotYMax[-99] = ymax;
 }

 virtual void SetLegendName(TString PDFName, TString LegendName){
   if(LegendName == "0") return;

   PDFLegendName[PDFName] = LegendName;
 }

 double LegendXmin = 0.4;
 double LegendYmin = 0.7;
 double LegendXmax = 0.8;
 double LegendYmax = 0.95;
 virtual void SetLegendPosition(double xmin, double ymin, double xmax, double ymax){
   this->LegendXmin = xmin;
   this->LegendYmin = ymin;
   this->LegendXmax = xmax;
   this->LegendYmax = ymax;
 }
 double TextLeftBias = 0.2;
 virtual void SetTextLeftBias(double bias){this->TextLeftBias = bias;}
};
#endif
