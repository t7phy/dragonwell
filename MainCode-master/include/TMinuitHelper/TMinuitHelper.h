#ifndef TMinuitHelper_h
#define TMinuitHelper_h

#include "RootCommon.h"

class TMinuitHelper
{
 public:

 TMinuit* myMinuit;

 Int_t ierflg;
 Double_t arglist[10];

 int maxpar;

 bool isSetMaxIterations = false;
 bool isSetPrintLevel = false;
 bool isSetErrorDef = false;
 int MaxIteration;
 int PrintLevel;
 double ErrorDef;

 TMinuitHelper(int maxpar);
 virtual ~TMinuitHelper();
 virtual void SetMaxIterations(int MaxIteration);
 virtual void SetFCN(void(*fcn)(Int_t &, Double_t *, Double_t &f, Double_t *, Int_t));
 virtual void SetPrintLevel(int PrintLevel);
 virtual void SetErrorDef(double ErrorDef);
 virtual void Input(int n, TString name, double center, double step, double lower, double upper);
 virtual void Input(int n, TString name, double center, double step);
 virtual void Exec(TString name, int MaxCall, double Tolerance);
 virtual void GetParameter();
 virtual void GetParameters(double* &DataPoints);
 virtual void GetParametersAndError(double* &DataPoints, double* &DataErrors);
 virtual double GetCorrelation(int i, int j);

};
#endif
