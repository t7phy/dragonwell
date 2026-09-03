#ifndef Uncertainty_SystematicUncertainty_h
#define Uncertainty_SystematicUncertainty_h

#include "RootCommon.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TString.h"
#include <vector>
#include <iostream>
#include <map>
#include "WZPolarization/HistsWZPolarization.h"

using namespace std;

class SystematicUncertainty
{
 public:

 TH1D *UncVari[500];
 TH1D *UncVariStat[500];
 bool isSaveVariBin = false;
 bool isSaveCovariance = false;
 bool isSaveCorrelation = false;

 map<TString, int> SysNameIndex;
 map<TString, TFile*> SysHistMap;
 map<int, TH1D*> SysIndexMap;

 map<int, TString> SysNames;
 vector<TString> HistNames;

 HistsWZPolarization *fHist;

 Int_t Sta_HistNumber = 0;

 SystematicUncertainty(map<TString, int> SysNameIndex, map<int, TString> SysNames);
 virtual void SaveVariBin(){isSaveVariBin = true;}
 virtual void GetUncertainty(TString HistName, map<int, TH1D*> SysIndexMap);

};

#endif
