#ifndef Uncertainty_PDFUncertainty_h
#define Uncertainty_PDFUncertainty_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "TH3F.h"
#include <TRandom3.h>
#include <TMinuit.h>
#include <TApplication.h>
#include "TEnv.h"
#include <TComplex.h>
#include <TGraph.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include "TTree.h"
#include "TString.h"
#include "Tools/Tools.h"

using namespace std;

class PDFUncertainty
{
 public:

 int NPDFs;
 int iflag;

 bool isOutput = false;
 bool isRebin = false;
 bool isRatio = false;

 TString Process = "";

 bool isWasymmetry = false;

 TString histName;
 TString ErrorType;

 TString FName;
 TString BName;
 TString RebinFile;

 TString filelist;

 TFile* writefile;
 bool isWritefile = true;

 TFile* file[1001];
 TFile* file1[1001];
 TFile* file2[1001];
 bool isReadfile = true;

 TH1D *h1[1001];
 vector<TH1D *> hist_1d;
 TH2D *h2[1001];
 vector<TH2D *> hist_2d;

 TH1D *PDF1D[1001];
 TH2D *PDF2D[1001];

 TH1D *FZmass[1001];
 TH1D *BZmass[1001];

 TH1D *PDFCentral1D;
 TH2D *PDFCentral2D;

 TH1D *PDFError1D;
 TH1D *PDFErrorPlus1D;
 TH1D *PDFErrorMinus1D;
 TH1D *PDFEnvelopePlus1D;
 TH1D *PDFEnvelopeMinus1D;
 TH2D *PDFError2D;

 TH1D *PDFStatError1D;
 TH2D *PDFStatError2D;

 TH1D *UncVari[500];

 TH1D *MCVari[500];

 TH2D *Correlation;
 TH2D *Covariance;
 double CovarianceValue;
 vector<double> ParX[500];
 vector<double> ParY[500];

 bool isSaveVariBin = true;
 bool isSaveCovariance = true;
 bool isSaveCorrelation = true;
 bool isSaveMCVari = false;

 bool isInit = false;

 PDFUncertainty(const char* cardfile);
 PDFUncertainty();
 virtual void Main();
 virtual void Input1DPlot(TString ErrorType, vector<TH1D *> Hists, TH1D* &PDFError);
 virtual void Input1DPlot(TString ErrorType, vector<TH1D *> Hists, TH1D* &PDFError, TH1D* &PDFEnvelopePlus, TH1D* &PDFEnvelopeMinus);
 virtual void Input2DPlot(TString ErrorType, vector<TH2D *> Hists, TH2D* &PDFError);
 virtual void GetPDFUncertainty();
 virtual ~PDFUncertainty();
 virtual void Output(){isOutput = true;}
 virtual void SaveVariBin(){isSaveVariBin = true;}
 virtual void SaveMCVari(){isSaveMCVari = true;}
 virtual void AFBFunction(TH1D* FZmass, TH1D* BZmass, TH1D* &Draw_AFB, int i);
};
#endif
