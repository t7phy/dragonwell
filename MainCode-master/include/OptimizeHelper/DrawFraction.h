#ifndef DrawFraction_h
#define DrawFraction_h

#include "RootCommon.h"
#include "OptimizeHelper/FractionHist.h"

using namespace std;

class DrawFraction
{
 public:

 ifstream infile;
 FractionHist* myhists;

 int EVMax = 29;

 double DataPoint, DataSet, iObs;
 string FileLine;

 int SkipBins;
 int SkipBinsDataSet;

 DrawFraction(const char* FracFile);
 virtual void LinkHist(FractionHist* myhists);
 virtual void FillHist();
 virtual void SkipBin(int iDataSet, int ibin);
};
#endif
