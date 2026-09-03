#ifndef AngularFunc_h
#define AngularFunc_h
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

using namespace std;

class AngularFunction
{
 public:

 TString myAngular;
 int iThread;

 double k, b;
 double cos_theta, phi, weight;
 int NbinsX, NbinsY, NbinsZ;

 TH1D* VariableHist1D;
 TH1D* AngularHist1D;

 TH2D* VariableHist2D;
 TH2D* AngularHist2D;

 TH3D* VariableHist3D;
 TH3D* AngularHist3D;

 TH1D* h1[1000];
 TH1D* h2[1000][1000];
 TH1D* h3[1000][1000][1000];

 TString histName;

 vector<TH1D *> hist_1d;
 vector<vector<TH2D *>> hist_2d;
 vector<vector<vector<TH3D *>>> hist_3d;
 int iflag;
 int x;

 bool isFill;

 AngularFunction(const char* myAngular, int iThread);
 virtual ~AngularFunction();
 virtual void SetHist(const char* histName, int NbinsX, double xmin, double xmax);
 virtual void SetHist(const char* histName, int NbinsX, double* xbins);
 virtual void SetHist(const char* histName, int NbinsX, double* xbins, int NbinsY, double* ybins);
 virtual void SetHist(const char* histName, int NbinsX, double* xbins, int NbinsY, double* ybins, int NbinsZ, double* zbins);
 virtual void Fill(double myVariable, double weight);
 virtual void Fill(double myVariable1, double myVariable2, double weight);
 virtual void Fill(double myVariable1, double myVariable2, double myVariable3, double weight);
 virtual void Initial(double cos_theta, double phi);
 virtual void GetAngular();
 virtual void Add(AngularFunction* angular1);
 virtual void Reset();
 virtual void Write();
 virtual void End();
};
#endif
