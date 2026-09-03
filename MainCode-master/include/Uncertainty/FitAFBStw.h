#ifndef FitAFBStw_h
#define FitAFBStw_h

#include "RootCommon.h"
#include "Tools/Tools.h"

class FitAFBStw
{
 public:

 int NStw;
 double left, right, step;

 bool isRebin;

 TFile* file[500];
 TH1D *h1[500];
 TH2D *h2[500];
 TH3D *h3[500];
 TH1D *FZmass[500];
 TH1D *BZmass[500];

 vector<TH1D *> v_LinearPlot;
 TH1D *LinearPlot[500];

 vector<TH1D *> v_LinearPlot_1d;
 TH1D *LinearPlot_1d[10000];

 vector<TH2D *> v_LinearPlot_2d;
 TH2D *LinearPlot_2d[500];

 vector<TH3D *> v_LinearPlot_3d;
 TH3D *LinearPlot_3d[500];

 TH1D *FittedSlope;
 TH1D *FittedOffset;

 TH2D *FittedSlope_2d;
 TH2D *FittedOffset_2d;

 TH3D *FittedSlope_3d;
 TH3D *FittedOffset_3d;

 TString FName;
 TString BName;
 TString outputName;
 TString RebinFile;

 TString filelist;

 vector<TH1D *> v_Plot;
 vector<TH2D *> v_Plot_2d;
 vector<TH3D *> v_Plot_3d;

 bool isInput = false;

 bool isInputLumiAndXSec = false;
 double Lumi, XSec, TotalEvents;

 FitAFBStw();
 FitAFBStw(const char* cardfile);
 virtual void Main();
 virtual void Input(vector<TH1D *> v_Plot, double left, double right);
 virtual void Input(vector<TH1D *> v_Plot, double left, double right, vector<TH1D *> &v_LinearPlot, TH1D* &FittedSlope, TH1D* &FittedOffset);
 virtual void Input(vector<TH3D *> v_Plot, double left, double right, vector<TH3D *> &v_LinearPlot, TH3D* &FittedSlope, TH3D* &FittedOffset);
 virtual void Get1DLinearPlot(vector<TH1D *> &v_LinearPlot);
 virtual void InputLumiAndXSec(double Lumi, double XSec);
 virtual void Fitting();
 virtual void MultiFitting();
 virtual void MultiFitting3D();
};

#endif
