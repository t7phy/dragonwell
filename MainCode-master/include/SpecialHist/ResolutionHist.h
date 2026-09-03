#ifndef ResolutionHist_h
#define ResolutionHist_h
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TMath.h"
#include "TH1D.h"
#include "TH3D.h"
#include <iostream>
#include <vector>
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
#include "TF1.h"

using namespace std;

class ResolutionHist
{
 public:

 double deltaE, weight;
 double par[3];

 int NbinsX, NbinsY;

 TH1D* VariableHist1D;
 TH1D* ResolutionHist1D;

 TH2D* VariableHist2D;
 TH2D* ResolutionHist2D;

 TH1D* h1[100];
 TH1D* h2[100][100];

 TF1* f1[100];
 TF1* f2[100][100];

 int iflag;
 int x;

 TString histName;
 TString type;

 int iThread;
 vector<TH1D *> hist_1d;

 ResolutionHist(TString type, int iThread);
 virtual ~ResolutionHist();
 virtual void SetHist(const char* histName, int NbinsX, double xmin, double xmax);
 virtual void SetHist(const char* histName, int NbinsX, double* xbins);
 virtual void SetHist(const char* histName, int NbinsX, double* xbins, int NbinsY, double* ybins);
 virtual void FillResolution(double myVariable);
 virtual void FillResolution(double myVariable1, double myVariable2);
 virtual void Fill(double deltaE, double weight);
 virtual void FitResolution(bool isDeleteHist = true);
 virtual void End();
 virtual void Add(ResolutionHist* hist1);
 virtual void Reset();
 virtual void Write();

};

#endif
