#ifndef Tools_SimpleFunction_h
#define Tools_SimpleFunction_h

#include "RootCommon.h"

using namespace std;

class SimpleFunction
{
 public:

 TFile *hf;

 double y = 0.0;
 double x1 = 0.0;
 double x2 = 0.0;
 double Q0 = 1.6;
 double Q = 91.1876;
 double ECM = 8000;
 double b2 = 0.0;
 double b = 0.0;
 double g[6] = {0.0};
 double Function = 0.0;
 TString FunctionName = "";

 enum class FunctionType{BLNY, IY, IY1, IY2, IY6};
 FunctionType myFunction;

 int iplot = 0;
 TH1D* Plot[1000];

 bool isOutput = false;

 SimpleFunction();
 virtual void openFile(TString FileName);
 virtual void Output(){isOutput = true;}
 virtual void InputVariable(double y);
 virtual void InputNonPert(double g1, double g2, double g3, double g4, double g5, double g6);
 virtual void CalParameters();
 virtual void SetFunction(TString FunctionName);
 virtual void CalFunction();
 virtual void BLNYFunction();
 virtual void IYFunction();
 virtual void IY1Function();
 virtual void IY2Function();
 virtual void IY6Function();
 virtual void OutputFunction(){cout<<"Function = "<<Function<<endl<<endl;}
 virtual void DrawFunction(int nbin, double left, double right);
 virtual void SaveFile();
};

#endif
