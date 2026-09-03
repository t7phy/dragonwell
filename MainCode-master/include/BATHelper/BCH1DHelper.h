#ifndef BATHelper_BCH1DHelper_h
#define BATHelper_BCH1DHelper_h

#include "TH1D.h"
#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "BAT/BCH1D.h"
#include "BAT/BCH2D.h"
#include "BAT/BCLog.h"
#include "BAT/BCMath.h"

using std::vector;

TH1D * GetSmallestIntervalHistogram(BCH1D h, double level);
std::vector<double> GetSmallestIntervals(BCH1D h, double content = 0.68);
TH1D* CalculateIntegratedHistogram(BCH2D h);
double GetLevel(TH1D* fIntegratedHistogram, double p);


#endif
