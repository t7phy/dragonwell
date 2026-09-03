#ifndef PDFHelper_PDFHelper_h
#define PDFHelper_PDFHelper_h

#include <iostream>
#include <map>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "Tools/Tools.h"
#include "CTEQHelper/pdsReader.h"

#ifdef USE_LHAPDF
#include "LHAPDF/LHAPDF.h"
#include "LHAPDF/Reweighting.h"
#endif

using namespace std;
//using namespace LHAPDF;

class PDFHelper
{
 public:

#ifdef USE_LHAPDF
 LHAPDF::PDF* pold;
 LHAPDF::PDF* pnew;
 LHAPDF::PDF* porigin;
#endif

 pdsReader* CTEQpold;
 pdsReader* CTEQpnew;
 pdsReader* CTEQporigin;

 TString PDFType;
 bool isInitial = false;

 double qold[2], qnew[2], PDFweight;

 TString PDFName = "";
 int iSet = 0;
 int nSet = 0;

 map<int, TString> FlavorName;

 TFile *hf;

 //1D Plot

 //PDF related plot

 //2D Plot

 int uncIndex = 0;
 map<TString, PDFUncertainty *> unc_plot;
 map<TString, FileForEPUMP *> file_plot;
 map<TString, TH1D *> central_plot;

 map<int, TString> PartonNameMap;

 double ECM = 13000.0;

 double muF = 1.0;

 double ErrorLevel = 0.000001;

 double uIntegral = 0.0;
 double dIntegral = 0.0;
 double sIntegral = 0.0;
 double cIntegral = 0.0;
 double bIntegral = 0.0;
 double ubarIntegral = 0.0;
 double dbarIntegral = 0.0;
 double sbarIntegral = 0.0;
 double cbarIntegral = 0.0;
 double bbarIntegral = 0.0;

 double uConvIntegral = 0.0;
 double dConvIntegral = 0.0;
 double sConvIntegral = 0.0;
 double cConvIntegral = 0.0;
 double bConvIntegral = 0.0;
 double ubarConvIntegral = 0.0;
 double dbarConvIntegral = 0.0;
 double sbarConvIntegral = 0.0;
 double cbarConvIntegral = 0.0;
 double bbarConvIntegral = 0.0;

 PDFHelper();
 virtual void InitialPartonName();
 virtual void InitialPDFReweightFactor(const char* OldPDFName, const char* NewPDFName, int oldPDFset, int newPDFset);
 virtual void InitialCTEQPDFReweightFactor(const char* OldPDFName, const char* NewPDFName);
 virtual double GetPDFReweightFactor(int flavour1, int flavour2, double x1, double x2, double Q);
 virtual double GetOldPDF(int flavor1, int flavor2, double x1, double x2, double Q);
 virtual double GetNewPDF(int flavor1, int flavor2, double x1, double x2, double Q);
 virtual void InitialPDF(const char* PDFName, int PDFset);
 virtual void InitialCTEQPDF(const char* PDFName, const char* GivenName, int PDFset);
 virtual void InputPDFnSet(int nSet){this->nSet = nSet;};
 virtual void InputMUF(double muF){this->muF = muF;};
 virtual void InputErrorLevel(double ErrorLevel){this->ErrorLevel = ErrorLevel;};

 virtual TH1D* DrawPDFLumi(int nbin, double Q1, double Q2, int flavor1, int flavor2);
 virtual void CalcPDFLumiUnc(int nbin, double Q1, double Q2, int flavor1, int flavor2, TString ErrorType, TString PDFName, int nSet);

 virtual double uqk(double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(x < 1.0) Value = pold->xfxQ(2, x, muF * Q) / x;
   else Value = 0.0;
#endif
   return Value;
 }
 virtual double dqk(double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(x < 1.0) Value = pold->xfxQ(1, x, muF * Q) / x;
   else Value = 0.0;
#endif
   return Value;
 }
 virtual double sqk(double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(x < 1.0) Value = pold->xfxQ(3, x, muF * Q) / x;
   else Value = 0.0;
#endif
   return Value;
 }
 virtual double cqk(double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(x < 1.0) Value = pold->xfxQ(4, x, muF * Q) / x;
   else Value = 0.0;
#endif
   return Value;
 }
 virtual double bqk(double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(x < 1.0) Value = pold->xfxQ(5, x, muF * Q) / x;
   else Value = 0.0;
#endif
   return Value;
 }
 virtual double ubar(double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(x < 1.0) Value = pold->xfxQ(-2, x, muF * Q) / x;
   else Value = 0.0;
#endif
   return Value;
 }
 virtual double dbar(double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(x < 1.0) Value = pold->xfxQ(-1, x, muF * Q) / x;
   else Value = 0.0;
#endif
   return Value;
 }
 virtual double sbar(double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(x < 1.0) Value = pold->xfxQ(-3, x, muF * Q) / x;
   else Value = 0.0;
#endif
   return Value;
 }
 virtual double cbar(double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(x < 1.0) Value = pold->xfxQ(-4, x, muF * Q) / x;
   else Value = 0.0;
#endif
   return Value;
 }
 virtual double bbar(double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(x < 1.0) Value = pold->xfxQ(-5, x, muF * Q) / x;
   else Value = 0.0;
#endif
   return Value;
 }

 virtual double Getf(int flavor, double x, double Q);
 virtual double Getx1x2Combination(int flavor, double x1, double x2, double Q);
 virtual double GetfOrigin(int flavor, double x, double Q);
 virtual double Getxf(int flavor, double x, double Q);
 virtual double GetF1F2(int flavor, double x, double Q);
 virtual double GetF1F2dY(int flavor, double x, double Q);
 virtual double GetF1F2dYRight(int flavor, double x, double Q);
 virtual double GetF1F2dYWrong(int flavor, double x, double Q);
 virtual double GetF1F2YInput(int flavor, double y, double Q);
 virtual double GetPDFLumi(double x, int flavor1, int flavor2, double Q);
 virtual double GetValence(int flavor, double x, double Q);
 virtual double GetNormPDF(int flavor, double x, double Q);
 virtual double GetDilution(int flavor, double y, double q);

 virtual double CfCf(double mass, int flavor, TString Process = "");
 virtual double CfCfQgtQbar(double mass, int flavor, TString Process = "");
 virtual double CfCfQltQbar(double mass, int flavor, TString Process = "");
 virtual double PDFIntegral(double mass, int flavor);
 virtual double xPDFIntegral(double mass, int flavor);
 virtual double CfCfIntegral(double left, double right, int flavor, TString Process = "");

 virtual double PDFLumiIntegralX(double Q, int flavor1, int flavor2);
 virtual double PDFLumiIntegralQ(double Q1, double Q2, int flavor1, int flavor2);

 bool isLinkFile = false;
 virtual void openFile(TString FileName);
 virtual void LinkFile(TFile* hf);
 virtual void SaveFile();

 //////////////////////
 // For Z Production //
 //////////////////////

 virtual double HadronCrossSection(double mass, int iflag, TString Process = ""){return 0.0;};
 virtual double WrongHadronCrossSection(double mass, int iflag, TString Process = ""){return 0.0;};
 virtual double ZCrossSection(double mass, int iflag, TString Process = ""){return 0.0;};
 virtual double MassZYCrossSection(double Q, double ZY, int iflag, TString Process){return 0.0;};
 virtual double MassZYCrossSectionWrong(double Q, double ZY, int iflag, TString Process){return 0.0;};
 virtual double GetZYCrossSection(double ZY, double massleft, double massright, int iflag, TString Process){return 0.0;};
 virtual double GetZYCrossSectionWrong(double ZY, double massleft, double massright, int iflag, TString Process){return 0.0;};

 ///////////////////////
 // For WW Production //
 ///////////////////////

 virtual double WWHadronCrossSectiony(double y, int i, double Q, double Y0){return 0.0;};
 virtual double WWHadronCrossSectionY0(double y, int i, double Q, double Y0){return 0.0;};
 virtual double WWQuarkCrossSectionY0Q(double Y0, int i, double Q){return 0.0;};
 virtual double WWHadronCrossSectionY0Q(double Y0, int flavor, double Q){return 0.0;};
 virtual double WWHadronCrossSectionQ(double Q, int flavor){return 0.0;};
 virtual double WWQuarkCrossSectionQ(double Q, int flavor){return 0.0;};
 virtual double IntegralWWHadronCrossSectionQ(double left, double right, int flavor){return 0.0;};
 virtual double IntegralWWQuarkCrossSectionQ(double left, double right, int flavor){return 0.0;};
 virtual double BoostCrossSection(double Q, double Delta, int flavor, TString rest){return 0.0;};
 virtual double TotalBoostCrossSection(double Delta, int flavor){return 0.0;};






 int initncall = 1000;
 double initstep = -1.0;
 bool initisOutput = true;

 int ncall = 1000;
 double step = -1.0;
 bool isOutput = true;

 void ResetIntegral(){this->ncall = this->initncall; this->step = this->initstep; this->isOutput = this->initisOutput;};

 double Simpson(double(PDFHelper::*fcn)(double), double left, double right);
 double SimpsonLog10(double(PDFHelper::*fcn)(double), double left, double right);

 template<typename T1>
 double Simpson(double(PDFHelper::*fcn)(double, T1), double left, double right, T1 iflag)
 {
  if(this->ncall == -1) this->ncall = (right - left) / this->step;
  if(this->step < 0) this->step = (right - left) / (double)(this->ncall);

  int ncall = this->ncall;
  double step = this->step;
  bool isOutput = this->isOutput;
  double Value = 0.0;

  for(int i = 0; i < ncall; i++){
    double a = left + step * i;
    double b = left + step * (i + 1);
    double x1 = 0.0;
    double f1 = 0.0;

    x1 = a;
    f1 = (this->*fcn)(x1, iflag);
    double term1 = f1;
    Value += f1;

    x1 = (a + b) / 2.0;
    f1 = (this->*fcn)(x1, iflag);
    double term2 = 4.0 * f1;
    Value += 4.0 * f1;

    x1 = b;
    f1 = (this->*fcn)(x1, iflag);
    double term3 = f1;
    Value += f1;

    if(ncall >= 10 && i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
  }

  if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
  if(isOutput) cout<<endl;

  double Result = (step / 6.0) * Value;

  ResetIntegral();

  return Result;
 }


 template<typename T1>
 double SimpsonLog10(double(PDFHelper::*fcn)(double, T1), double left, double right, T1 iflag)
 {
  if(this->ncall == -1) this->ncall = (right - left) / this->step;
  if(this->step < 0) this->step = (right - left) / (double)(this->ncall);

  int ncall = this->ncall;
  double step = this->step;
  bool isOutput = this->isOutput;
  double Value = 0.0;

  for(int i = 0; i < ncall; i++){
    double a = left + step * i;
    double b = left + step * (i + 1);
    double x1 = 0.0;
    double f1 = 0.0;

    x1 = a;
    f1 = (this->*fcn)(pow(10.0, x1), iflag) * log(10) * pow(10.0, x1);
    double term1 = f1;
    Value += f1;

    x1 = (a + b) / 2.0;
    f1 = (this->*fcn)(pow(10.0, x1), iflag) * log(10) * pow(10.0, x1);
    double term2 = 4.0 * f1;
    Value += 4.0 * f1;

    x1 = b;
    f1 = (this->*fcn)(pow(10.0, x1), iflag) * log(10) * pow(10.0, x1);
    double term3 = f1;
    Value += f1;

    if(ncall >= 10 && i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
  }

  if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
  if(isOutput) cout<<endl;

  double Result = (step / 6.0) * Value;

  ResetIntegral();

  return Result;
 }

 template<typename T1, typename T3>
 double Simpson(double(PDFHelper::*fcn)(T1, double, T3), double left, double right, T1 flavor, T3 mass)
 {
  if(this->ncall == -1) this->ncall = (right - left) / this->step;
  if(this->step < 0) this->step = (right - left) / (double)(this->ncall);

  int ncall = this->ncall;
  double step = this->step;
  bool isOutput = this->isOutput;
  double Value = 0.0;

  for(int i = 0; i < ncall; i++){
    double a = left + step * i;
    double b = left + step * (i + 1);
    double x1 = 0.0;
    double f1 = 0.0;

    x1 = a;
    f1 = (this->*fcn)(flavor, x1, mass);
    double term1 = f1;
    Value += f1;

    x1 = (a + b) / 2.0;
    f1 = (this->*fcn)(flavor, x1, mass);
    double term2 = 4.0 * f1;
    Value += 4.0 * f1;

    x1 = b;
    f1 = (this->*fcn)(flavor, x1, mass);
    double term3 = f1;
    Value += f1;

    if(ncall >= 10 && i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
  }

  if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
  if(isOutput) cout<<endl;

  double Result = (step / 6.0) * Value;

  ResetIntegral();

  return Result;
 }

 template<typename T1, typename T3>
 double SimpsonLog10(double(PDFHelper::*fcn)(T1, double, T3), double left, double right, T1 flavor, T3 mass)
 {
  if(this->ncall == -1) this->ncall = (right - left) / this->step;
  if(this->step < 0) this->step = (right - left) / (double)(this->ncall);

  int ncall = this->ncall;
  double step = this->step;
  bool isOutput = this->isOutput;
  double Value = 0.0;

  for(int i = 0; i < ncall; i++){
    double a = left + step * i;
    double b = left + step * (i + 1);
    double x1 = 0.0;
    double f1 = 0.0;

    x1 = a;
    f1 = (this->*fcn)(flavor, pow(10.0, x1), mass) * log(10) * pow(10.0, x1);
    double term1 = f1;
    Value += f1;

    x1 = (a + b) / 2.0;
    f1 = (this->*fcn)(flavor, pow(10.0, x1), mass) * log(10) * pow(10.0, x1);
    double term2 = 4.0 * f1;
    Value += 4.0 * f1;

    x1 = b;
    f1 = (this->*fcn)(flavor, pow(10.0, x1), mass) * log(10) * pow(10.0, x1);
    double term3 = f1;
    Value += f1;

    if(ncall >= 10 && i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
  }

  if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
  if(isOutput) cout<<endl;

  double Result = (step / 6.0) * Value;

  ResetIntegral();

  return Result;
 }

 template<typename T2, typename T3>
 double Simpson(double(PDFHelper::*fcn)(double, T2, T3), double left, double right, T2 par1, T3 par2)
 {
  if(this->ncall == -1) this->ncall = (right - left) / this->step;
  if(this->step < 0) this->step = (right - left) / (double)(this->ncall);

  int ncall = this->ncall;
  double step = this->step;
  bool isOutput = this->isOutput;
  double Value = 0.0;

  for(int i = 0; i < ncall; i++){
    double a = left + step * i;
    double b = left + step * (i + 1);
    double x1 = 0.0;
    double f1 = 0.0;

    x1 = a;
    f1 = (this->*fcn)(x1, par1, par2);
    double term1 = f1;
    Value += f1;

    x1 = (a + b) / 2.0;
    f1 = (this->*fcn)(x1, par1, par2);
    double term2 = 4.0 * f1;
    Value += 4.0 * f1;

    x1 = b;
    f1 = (this->*fcn)(x1, par1, par2);
    double term3 = f1;
    Value += f1;

    if(ncall >= 10 && i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
  }

  if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
  if(isOutput) cout<<endl;

  double Result = (step / 6.0) * Value;

  ResetIntegral();

  return Result;
 }

 template<typename T2, typename T3>
 double SimpsonLog10(double(PDFHelper::*fcn)(double, T2, T3), double left, double right, T2 par1, T3 par2)
 {
  if(this->ncall == -1) this->ncall = (right - left) / this->step;
  if(this->step < 0) this->step = (right - left) / (double)(this->ncall);

  int ncall = this->ncall;
  double step = this->step;
  bool isOutput = this->isOutput;
  double Value = 0.0;

  for(int i = 0; i < ncall; i++){
    double a = left + step * i;
    double b = left + step * (i + 1);
    double x1 = 0.0;
    double f1 = 0.0;

    x1 = a;
    f1 = (this->*fcn)(pow(10.0, x1), par1, par2) * log(10) * pow(10.0, x1);
    double term1 = f1;
    Value += f1;

    x1 = (a + b) / 2.0;
    f1 = (this->*fcn)(pow(10.0, x1), par1, par2) * log(10) * pow(10.0, x1);
    double term2 = 4.0 * f1;
    Value += 4.0 * f1;

    x1 = b;
    f1 = (this->*fcn)(pow(10.0, x1), par1, par2) * log(10) * pow(10.0, x1);
    double term3 = f1;
    Value += f1;

    if(ncall >= 10 && i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
  }

  if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
  if(isOutput) cout<<endl;

  double Result = (step / 6.0) * Value;

  ResetIntegral();

  return Result;
 }

 template<typename T2, typename T3, typename T4>
 double Simpson(double(PDFHelper::*fcn)(double, T2, T3, T4), double left, double right, T2 par1, T3 par2, T4 par3)
 {
  if(this->ncall == -1) this->ncall = (right - left) / this->step;
  if(this->step < 0) this->step = (right - left) / (double)(this->ncall);

  int ncall = this->ncall;
  double step = this->step;
  bool isOutput = this->isOutput;
  double Value = 0.0;

  for(int i = 0; i < ncall; i++){
    double a = left + step * i;
    double b = left + step * (i + 1);
    double x1 = 0.0;
    double f1 = 0.0;

    x1 = a;
    f1 = (this->*fcn)(x1, par1, par2, par3);
    double term1 = f1;
    Value += f1;

    x1 = (a + b) / 2.0;
    f1 = (this->*fcn)(x1, par1, par2, par3);
    double term2 = 4.0 * f1;
    Value += 4.0 * f1;

    x1 = b;
    f1 = (this->*fcn)(x1, par1, par2, par3);
    double term3 = f1;
    Value += f1;

    if(ncall >= 10 && i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
  }

  if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
  if(isOutput) cout<<endl;

  double Result = (step / 6.0) * Value;

  ResetIntegral();

  return Result;
 }

 template<typename T2, typename T3, typename T4>
 double SimpsonLog10(double(PDFHelper::*fcn)(double, T2, T3, T4), double left, double right, T2 par1, T3 par2, T4 par3)
 {
  if(this->ncall == -1) this->ncall = (right - left) / this->step;
  if(this->step < 0) this->step = (right - left) / (double)(this->ncall);

  int ncall = this->ncall;
  double step = this->step;
  bool isOutput = this->isOutput;
  double Value = 0.0;

  for(int i = 0; i < ncall; i++){
    double a = left + step * i;
    double b = left + step * (i + 1);
    double x1 = 0.0;
    double f1 = 0.0;

    x1 = a;
    f1 = (this->*fcn)(pow(10.0, x1), par1, par2, par3) * log(10) * pow(10.0, x1);
    double term1 = f1;
    Value += f1;

    x1 = (a + b) / 2.0;
    f1 = (this->*fcn)(pow(10.0, x1), par1, par2, par3) * log(10) * pow(10.0, x1);
    double term2 = 4.0 * f1;
    Value += 4.0 * f1;

    x1 = b;
    f1 = (this->*fcn)(pow(10.0, x1), par1, par2, par3) * log(10) * pow(10.0, x1);
    double term3 = f1;
    Value += f1;

    if(ncall >= 10 && i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
  }

  if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
  if(isOutput) cout<<endl;

  double Result = (step / 6.0) * Value;

  ResetIntegral();

  return Result;
 }

 template<typename T2, typename T3, typename T4, typename T5>
 double Simpson(double(PDFHelper::*fcn)(double, T2, T3, T4, T5), double left, double right, T2 par1, T3 par2, T4 par3, T5 par4)
 {
  if(this->ncall == -1) this->ncall = (right - left) / this->step;
  if(this->step < 0) this->step = (right - left) / (double)(this->ncall);

  int ncall = this->ncall;
  double step = this->step;
  bool isOutput = this->isOutput;
  double Value = 0.0;

  for(int i = 0; i < ncall; i++){
    double a = left + step * i;
    double b = left + step * (i + 1);
    double x1 = 0.0;
    double f1 = 0.0;

    x1 = a;
    f1 = (this->*fcn)(x1, par1, par2, par3, par4);
    double term1 = f1;
    Value += f1;

    x1 = (a + b) / 2.0;
    f1 = (this->*fcn)(x1, par1, par2, par3, par4);
    double term2 = 4.0 * f1;
    Value += 4.0 * f1;

    x1 = b;
    f1 = (this->*fcn)(x1, par1, par2, par3, par4);
    double term3 = f1;
    Value += f1;

    if(ncall >= 10 && i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
  }

  if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
  if(isOutput) cout<<endl;

  double Result = (step / 6.0) * Value;

  ResetIntegral();

  return Result;
 }

 template<typename T2, typename T3, typename T4, typename T5>
 double SimpsonLog10(double(PDFHelper::*fcn)(double, T2, T3, T4, T5), double left, double right, T2 par1, T3 par2, T4 par3, T5 par4)
 {
  if(this->ncall == -1) this->ncall = (right - left) / this->step;
  if(this->step < 0) this->step = (right - left) / (double)(this->ncall);

  int ncall = this->ncall;
  double step = this->step;
  bool isOutput = this->isOutput;
  double Value = 0.0;

  for(int i = 0; i < ncall; i++){
    double a = left + step * i;
    double b = left + step * (i + 1);
    double x1 = 0.0;
    double f1 = 0.0;

    x1 = a;
    f1 = (this->*fcn)(pow(10.0, x1), par1, par2, par3, par4) * log(10) * pow(10.0, x1);
    double term1 = f1;
    Value += f1;

    x1 = (a + b) / 2.0;
    f1 = (this->*fcn)(pow(10.0, x1), par1, par2, par3, par4) * log(10) * pow(10.0, x1);
    double term2 = 4.0 * f1;
    Value += 4.0 * f1;

    x1 = b;
    f1 = (this->*fcn)(pow(10.0, x1), par1, par2, par3, par4) * log(10) * pow(10.0, x1);
    double term3 = f1;
    Value += f1;

    if(ncall >= 10 && i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
  }

  if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
  if(isOutput) cout<<endl;

  double Result = (step / 6.0) * Value;

  ResetIntegral();

  return Result;
 }



/* uConvIntegral = CfCfIntegral(2);
 dConvIntegral = CfCfIntegral(1);
 sConvIntegral = CfCfIntegral(3);
 cConvIntegral = CfCfIntegral(4);
 bConvIntegral = CfCfIntegral(5);
 ubarConvIntegral = CfCfIntegral(-2);
 dbarConvIntegral = CfCfIntegral(-1);
 sbarConvIntegral = CfCfIntegral(-3);
 cbarConvIntegral = CfCfIntegral(-4);
 bbarConvIntegral = CfCfIntegral(-5);

 cout<<"Convolute Integral:"<<endl;
 cout<<"u: "<<uConvIntegral<<" ubar: "<<ubarConvIntegral<<endl;
 cout<<"d: "<<dConvIntegral<<" dbar: "<<dbarConvIntegral<<endl;
 cout<<"s: "<<sConvIntegral<<" sbar: "<<sbarConvIntegral<<endl;
 cout<<"c: "<<cConvIntegral<<" cbar: "<<cbarConvIntegral<<endl;
 cout<<"b: "<<bConvIntegral<<" bbar: "<<bbarConvIntegral<<endl;
*/


/* double f1Integral;
 double f2Integral;
 f1Integral = PDFIntegral(Q, flavor);
 if(flavor == 2) f2Integral = f1Integral - 2;
 if(flavor == 1) f2Integral = f1Integral - 1;
 if(flavor == -2) f2Integral = f1Integral + 2;
 if(flavor == -1) f2Integral = f1Integral + 1;
 if(abs(flavor) == 3) f2Integral = f1Integral;
 if(abs(flavor) == 4) f2Integral = f1Integral;
 if(abs(flavor) == 5) f2Integral = f1Integral;
 double uIntegral = PDFIntegral(Q, 2);
 double dIntegral = PDFIntegral(Q, 1);
 double sIntegral = PDFIntegral(Q, 3);
 double cIntegral = PDFIntegral(Q, 4);
 double bIntegral = PDFIntegral(Q, 5);
 double ubarIntegral = uIntegral - 2;
 double dbarIntegral = dIntegral - 1;
 double sbarIntegral = sIntegral;
 double cbarIntegral = cIntegral;
 double bbarIntegral = bIntegral;
*/

/*
 double muF = 60;

 this->uIntegral = PDFIntegral(muF, 2);
 this->dIntegral = PDFIntegral(muF, 1);
 this->sIntegral = PDFIntegral(muF, 3);
 this->cIntegral = PDFIntegral(muF, 4);
 this->bIntegral = PDFIntegral(muF, 5);
 this->ubarIntegral = PDFIntegral(muF, -2);
 this->dbarIntegral = PDFIntegral(muF, -1);
 this->sbarIntegral = PDFIntegral(muF, -3);
 this->cbarIntegral = PDFIntegral(muF, -4);
 this->bbarIntegral = PDFIntegral(muF, -5);

 cout<<"Q: "<<muF<<endl;
 cout<<"u: "<<uIntegral<<" ubar: "<<ubarIntegral<<endl;
 cout<<"d: "<<dIntegral<<" dbar: "<<dbarIntegral<<endl;
 cout<<"s: "<<sIntegral<<" sbar: "<<sbarIntegral<<endl;
 cout<<"c: "<<cIntegral<<" cbar: "<<cbarIntegral<<endl;
 cout<<"b: "<<bIntegral<<" bbar: "<<bbarIntegral<<endl;

 muF = 91.1876;

 this->uIntegral = PDFIntegral(muF, 2);
 this->dIntegral = PDFIntegral(muF, 1);
 this->sIntegral = PDFIntegral(muF, 3);
 this->cIntegral = PDFIntegral(muF, 4);
 this->bIntegral = PDFIntegral(muF, 5);
 this->ubarIntegral = PDFIntegral(muF, -2);
 this->dbarIntegral = PDFIntegral(muF, -1);
 this->sbarIntegral = PDFIntegral(muF, -3);
 this->cbarIntegral = PDFIntegral(muF, -4);
 this->bbarIntegral = PDFIntegral(muF, -5);

 cout<<"Q: "<<muF<<endl;
 cout<<"u: "<<uIntegral<<" ubar: "<<ubarIntegral<<endl;
 cout<<"d: "<<dIntegral<<" dbar: "<<dbarIntegral<<endl;
 cout<<"s: "<<sIntegral<<" sbar: "<<sbarIntegral<<endl;
 cout<<"c: "<<cIntegral<<" cbar: "<<cbarIntegral<<endl;
 cout<<"b: "<<bIntegral<<" bbar: "<<bbarIntegral<<endl;

 muF = 130;

 this->uIntegral = PDFIntegral(muF, 2);
 this->dIntegral = PDFIntegral(muF, 1);
 this->sIntegral = PDFIntegral(muF, 3);
 this->cIntegral = PDFIntegral(muF, 4);
 this->bIntegral = PDFIntegral(muF, 5);
 this->ubarIntegral = PDFIntegral(muF, -2);
 this->dbarIntegral = PDFIntegral(muF, -1);
 this->sbarIntegral = PDFIntegral(muF, -3);
 this->cbarIntegral = PDFIntegral(muF, -4);
 this->bbarIntegral = PDFIntegral(muF, -5);

 cout<<"Q: "<<muF<<endl;
 cout<<"u: "<<uIntegral<<" ubar: "<<ubarIntegral<<endl;
 cout<<"d: "<<dIntegral<<" dbar: "<<dbarIntegral<<endl;
 cout<<"s: "<<sIntegral<<" sbar: "<<sbarIntegral<<endl;
 cout<<"c: "<<cIntegral<<" cbar: "<<cbarIntegral<<endl;
 cout<<"b: "<<bIntegral<<" bbar: "<<bbarIntegral<<endl;

*/

};
#endif
