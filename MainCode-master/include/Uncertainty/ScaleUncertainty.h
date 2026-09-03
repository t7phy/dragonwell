#ifndef Uncertainty_ScaleUncertainty_h
#define Uncertainty_ScaleUncertainty_h

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

using namespace std;

class ScaleUncertainty
{
 public:

 int NScales;
 int ScaleCentral;
 int iflag;

 bool isOutput;

 TString histName;
 TString filelist;
 TString ErrorType;

 TFile* file[100];
 TH1D *h1[100];
 TH2D *h2[100];

 TH1D *ScalePlot1D[100];
 TH2D *ScalePlot2D[100];

 TH1D *ScaleError1D;
 TH1D *ScaleErrorUp1D;
 TH1D *ScaleErrorDown1D;

 TH2D *ScaleError2D;
 TH1D *ScaleErrorUp2D;
 TH1D *ScaleErrorDown2D;

 TH1D *ScaleCentral1D;
 TH2D *ScaleCentral2D;

 TH1D *ScaleStatError1D;
 TH2D *ScaleStatError2D;

 TH1D *UncVari[500];
 bool isSaveVariBin = true;

 ScaleUncertainty(const char* cardfile);
 ScaleUncertainty();
 virtual void Main();
 virtual void Input1DPlot(TString ErrorType, vector<TH1D *> Hists, TH1D* &ScaleError);
 virtual void GetScaleUncertainty();
 virtual ~ScaleUncertainty();
};
#endif
