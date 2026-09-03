#ifndef Tools_LatexOutput_h
#define Tools_LatexOutput_h

#include <iostream>
#include <fstream>
#include "RootCommon.h"

using namespace std;

class LatexOutput
{
 public:

 LatexOutput();
 virtual void DataMC(TH1D* MC, TH1D* Data, TString Name);
 virtual int GetNDigit(double num);

};
#endif
