#ifndef FormatTransform_SystematicError_h
#define FormatTransform_SystematicError_h

#include "RootCommon.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TString.h"
#include <vector>
#include <iostream>
#include <map>
#include "WZPolarization/HistsWZPolarization.h"
#include "Uncertainty/SystematicUncertainty.h"

using namespace std;

class SystematicError
{
 public:

 TFile *hf;
 TFile *HistFile;

// vector<TString> regionNames{"Inclusive", "Signal", "LowPtZCR", "HighPtWZCR", "ZZCR", "TopCR"};
// vector<TString> regionNames{"Inclusive", "Signal", "HighPtZCR", "ZZCR"};
 vector<TString> regionNames{"Single", "PtWZ10CR", "PtWZ20CR", "PtWZ40CR", "LowPtWZCR"};
// vector<TString> ProcessNames{"Polarized"};
// vector<TString> ProcessNames{"Polarized", "SignalWZ", "SignalWZPolarized", "FakeBkg"};
 vector<TString> ProcessNames{"Single", "FinalTT", "TT", "SignalWZPolarized"};

 map<TString, int> SysNameIndex;
 map<TString, TFile*> SysHistMap;
 map<int, TH1D*> SysIndexMap;

 map<int, TString> SysNames;
 vector<TString> HistNames;
 map<TString, TString> HistType;

 HistsWZPolarization *fHist;

 Int_t Sta_HistNumber = 0;

 SystematicError();
 virtual ~SystematicError();
 virtual void openFile(const char* FileName);
 virtual void openHistFile(const char* FileName);
 virtual void openSysHistFile(TString FileName);
 virtual void InitialHistName();
 virtual void InitialFileStructure();
 virtual void FillHist(TString regionName, TString ProcessName);
 virtual void GetSystematicError(TString HistName, map<int, TH1D*> SysIndexMap);
 virtual void SaveFile();
 virtual void LinkHist(HistsWZPolarization *myhists);

};
#endif
