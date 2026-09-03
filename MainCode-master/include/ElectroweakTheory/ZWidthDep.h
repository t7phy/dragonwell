#ifndef ElectroweakTheory_ZWidthDep_h
#define ElectroweakTheory_ZWidthDep_h

#include "RootCommon.h"
#include <iostream>

using namespace std;

class ZWidthDep
{
 public:

 TFile *hf;

 TH1D *plot_ReChiMassDerive[1000];
 TH1D *plot_ChiSquareMassDerive[1000];
 TH1D *plot_ReChiStwDerive[1000];
 TH1D *plot_ChiSquareStwDerive[1000];
 TH1D *plot_AFBMassDerive[1000];
 TH1D *plot_AFBStwDerive[1000];
 TH1D *plot_AFBStwDeriveMassDep[1000];
 TH1D *plot_AFBMassStwDeriveMassDep[1000];
 TH1D *plot_AFB[1000];
 TH1D *plot_ReChiStwDeriveMassDep[1000];
 TH1D *plot_ChiSquareStwDeriveMassDep[1000];
 TH1D *plot_A41MassDerive[1000];
 TH1D *plot_A41StwDeriveMassDep[1000];
 TH1D *plot_A42MassDerive[1000];
 TH1D *plot_A42StwDeriveMassDep[1000];
 TH1D *plot_A4[1000];
 TH1D *plot_L0[1000];
 TH1D *plot_DeltaO[1000];
 TH1D *plot_AFBStw[1000];

 TF1 *plot_AFBCurve[1000];

 int iReChi = 0;
 int iChiSquare = 0;
 int iReChiStw = 0;
 int iChiSquareStw = 0;
 int iAFBMassDerive = 0;
 int iAFBStwDerive = 0;
 int iAFBStwDeriveMassDep = 0;
 int iAFBMassStwDeriveMassDep = 0;
 int iAFB = 0;
 int iReChiStwDeriveMassDep = 0;
 int iChiSquareStwDeriveMassDep = 0;
 int iA41 = 0;
 int iA41StwDeriveMassDep = 0;
 int iA42 = 0;
 int iA42StwDeriveMassDep = 0;
 int iA4 = 0;
 int iL0 = 0;
 int iDeltaO = 0;
 int iAFBCurve = 0;
 int iAFBStw;

 double ZPeakMass = 91.1876;
 double ZWidth = 2.4952;
 double WPeakMass = 80.385;
// double ZWidth = 0.01;
// double ZWidth = 0.083;

 double ChargeQ = 2.0 / 3.0;
 double Chargel = -1.0;

 double I3Q = 0.5;
 double I3l = -0.5;

 double stwQ = 0.2315;
 double stwl = 0.2315;

 double gVq;
 double gAq;
 double gVl;
 double gAl;

 int iflag;

 ZWidthDep();
 virtual void openFile(TString FileName);
 virtual void InputStw(double stw);
 virtual void InputQuark(int iflag);
 virtual double ReChi(double mass);
 virtual double ChiSquare(double mass);
 virtual double CalL0(double mass);
 virtual double CalL0Gamma(double mass);
 virtual double CalL0Interference(double mass);
 virtual double CalL0Z(double mass);
 virtual double CalA4(double mass);
 virtual double CalA4Interference(double mass);
 virtual double CalA4Z(double mass);
 virtual double CalAFB(double mass, TString flag = "");
 virtual double CalAFBCurve(double x){return 1;};
 virtual double CalA41(double mass);
 virtual double CalA42(double mass);
 virtual double pyalem(double q2);
 virtual double ZCrossSection(double mass, int iflag, TString Process = "");
 virtual double ReChiMassDerive(double mass, double DeltaMass);
 virtual double ReChiStwDerive(double stw, double DeltaStw, double mass);
 virtual double ChiSquareMassDerive(double mass, double DeltaMass);
 virtual double ChiSquareStwDerive(double stw, double DeltaStw, double mass);
 virtual double A41MassDerive(double mass, double DeltaMass);
 virtual double A41StwDerive(double stw, double DeltaStw, double mass);
 virtual double A42MassDerive(double mass, double DeltaMass);
 virtual double A42StwDerive(double stw, double DeltaStw, double mass);
 virtual double AFBMassDerive(double mass, double DeltaMass);
 virtual double AFBStwDerive(double stw, double DeltaStw, double mass, TString flag = "");
 virtual double AFBMassStwDerive(double mass, double DeltaMass, double stw, double DeltaStw);
 virtual void DrawReChiMassDerive(int bin, double left, double right, double DeltaMass);
 virtual void DrawReChiStwDerive(int bin, double left, double right, double DeltaStw, double mass);
 virtual void DrawReChiStwDeriveMassDep(int bin, double left, double right);
 virtual void DrawChiSquareMassDerive(int bin, double left, double right, double DeltaMass);
 virtual void DrawChiSquareStwDerive(int bin, double left, double right, double DeltaStw, double mass);
 virtual void DrawChiSquareStwDeriveMassDep(int bin, double left, double right);
 virtual void DrawAFB(int bin, double left, double right, TString flag = "");
 virtual void DrawAFBStw(int bin, double left, double right, double mass, TString flag = "");
 virtual void DrawAFBMassDerive(int bin, double left, double right, double DeltaMass);
 virtual void DrawAFBStwDerive(int bin, double left, double right, double DeltaStw, double mass, TString flag = "");
 virtual void DrawAFBStwDeriveMassDep(int bin, double left, double right, TString flag = "");
 virtual void DrawAFBMassStwDeriveMassDep(int bin, double left, double right, double stw);
 virtual void DrawA41MassDerive(int bin, double left, double right, double DeltaMass);
 virtual void DrawA41StwDeriveMassDep(int bin, double left, double right);
 virtual void DrawA42MassDerive(int bin, double left, double right, double DeltaMass);
 virtual void DrawA42StwDeriveMassDep(int bin, double left, double right);
 virtual void DrawA4(int bin, double left, double right);
 virtual void DrawL0(int bin, double left, double right);
 virtual void DrawDeltaO(int bin, double left, double right);
 virtual void DrawAFBCurve(double left, double right);
 virtual void SaveFile();
};

#endif
