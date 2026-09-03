#ifndef Tools_SimpleIntegral_h
#define Tools_SimpleIntegral_h

#include "RootCommon.h"

class SimpleIntegral
{
 public:

 TString myFormula;

 TF1* fitting;

 SimpleIntegral();
 virtual void InputFormula(TString myFormula);
 virtual void SetParameters(double p0, double p1, double p2 = 0, double p3 = 0, double p4 = 0, double p5 = 0, double p6 = 0, double p7 = 0, double p8 = 0, double p9 = 0, double p10 = 0);
 virtual double GetIntegral(double left, double right);
 virtual double Gaus(double x);
 virtual double GausPlus(double x, double y);
 virtual double GausPlus2(double x, double y, double z);
 virtual double Simpson(double(SimpleIntegral::*fcn)(double), double left, double right);
};

#endif
