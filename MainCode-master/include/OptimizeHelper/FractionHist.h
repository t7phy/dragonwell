#ifndef FractionHist_h
#define FractionHist_h

#include "RootCommon.h"

class FractionHist
{
 public:

 int EVMax = 29;

 TFile *hf;
 TH1D* Obs[200][29];

 int ObsNumber = 0;

 virtual void openFile(const char* fName);
 virtual void DefineHist(TString name, TString title, int nbin, double left, double right); 
 virtual void DefineHist(TString name, TString title, int nbin, double* xbins);
 virtual void Fill(int iObs, int iEV, int ibin, double Content);
 virtual void saveHist();
};
#endif
