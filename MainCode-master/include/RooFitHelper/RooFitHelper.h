#ifndef RooFitHelper_h
#define RooFitHelper_h

#include <iostream>
#include "RootCommon.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include "RooFitResult.h"
#include "RooGenericPdf.h"
#include "RooConstVar.h"
#include "RooTFnBinding.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooAddPdf.h"
#include "RooChebychev.h"

using namespace RooFit;
using namespace std;

class RooFitHelper
{
 public:

 TFile* hf;
 bool isLinkFile = false;

#ifdef USE_ROOFIT

//RooFit-related variable defined here
 int npar = 0;
 map<int, RooRealVar*> m_Var;
 map<int, TString> VarNameMap;

 int npdf = 0;
 map<int, RooAbsPdf*> m_Pdf;

 map<int, RooGaussian*> m_Gaussian;
 map<int, RooRealVar*> m_Gaussian_mean;
 map<int, RooRealVar*> m_Gaussian_sigma;

 map<int, RooChebychev*> m_Polynomial;
 map<int, RooRealVar*> m_Polynomial_Var1;
 map<int, RooRealVar*> m_Polynomial_Var2;

 map<int, RooAddPdf*> m_AddPdf;
 map<int, TString> PDFNameMap;

 int ndata = 0;
 map<int, RooDataSet*> m_DataSet;

 int nhist = 0;
 map<int, RooDataHist*> m_DataHist;
 map<int, RooPlot*> m_HistPlot;

 int narg = 0;
 map<int, RooArgSet*> m_ArgSet;

 map<int, TLegend*> m_Legend;

 map<int, TCanvas*> m_Canvas;

#endif


 RooFitHelper();
 virtual ~RooFitHelper(){};

#ifdef USE_ROOFIT
 virtual void FitGaussian(RooDataSet *data);
 virtual void FitGaussian(TH1D *h1);
 virtual void Input(int n, TString name, TString title, double center, double lower, double upper);
 virtual void Input(int n, TString name, TString title, double center);
 virtual void Input(int n, RooRealVar *var);
 virtual void AddGaussian(int n, int ivar, double mean, double sigma);
 virtual void AddPolynomial2(int n, TString name, int ivar, int var1, int var2);
 virtual void AddPdf2(int n, TString name, int pdf1, int pdf2, int fraction);
 virtual void Generate(int n, int input, int output, int NData);
 virtual void GenerateHist(int output, int input, int idata, int nbinx);
 virtual void FitTo(int imodel, int idata);
 virtual void FitToHist(int imodel, int ihist);
 virtual void DrawPdf(int iplot, int ipdf, Style_t style, Color_t color, TString name);
 virtual void SavePlot(int iplot, TString name);
 virtual void FitFunction(TString func, RooArgSet var, RooDataSet *data);
 virtual void FitFunction(TString func, RooArgSet var, TH1D *h1);
 virtual void PlotFunction(TF1* f1, double left, double right);
 virtual void openFile(const char* name){hf = new TFile(name, "RECREATE"); hf->cd(); isLinkFile = true;}
 virtual void LinkFile(TFile* file){this->hf = file; hf->cd(); isLinkFile = true;}
 virtual void SaveFile(){hf->Write(); hf->Close();}

#endif

};
#endif
