#ifndef FormatTransform_PDFAndQCDError_h
#define FormatTransform_PDFAndQCDError_h

#include "RootCommon.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TString.h"
#include <vector>
#include <iostream>
#include <map>
#include "WZPolarization/HistsWZPolarization.h"
#include "Uncertainty/PDFUncertainty.h"
#include "Uncertainty/ScaleUncertainty.h"

using namespace std;

class PDFAndQCDError
{
 public:

 TFile *hf;
 TFile *HistFile;

// vector<TString> regionNames{"Inclusive", "Signal", "LowPtZCR", "HighPtWZCR", "ZZCR", "TopCR"};
// vector<TString> regionNames{"Single"};
 vector<TString> regionNames{"Single", "Inclusive", "SignalPtWZ", "SignalPtZ100", "PtWZ10CR", "PtWZ20CR", "PtWZ40CR", "LowPtWZCR"};
// vector<TString> ProcessNames{"WZQCD"};
// vector<TString> ProcessNames{"WZQCD", "Polarized"};
 vector<TString> ProcessNames{"Single", "WZMixed", "WZRest", "LL", "LT", "TL", "TT", "Total", "BkgZZ", "BkgWZEW", "BkgVVV", "BkgttbarV", "Fake", "FinalTT"};

 vector<TString> HistNames;
 map<TString, TString> HistType;

 vector<TFile *> FileList;
 vector<TH1D *> HistVector;
 TString ProcessName = "";

 TH1D *HistMerge;

 HistsWZPolarization *fHist;

 Int_t Sta_HistNumber = 0;

 PDFAndQCDError();
 virtual ~PDFAndQCDError();
 virtual void openFile(const char* FileName);
 virtual void openHistFile(const char* FileName);
 virtual void openPDFHistFile(TString FileName, TString ProcessName, int size);
 virtual void InitialHistName();
 virtual void InitialFileStructure();
 virtual void FillHist(TString regionName, TString ProcessName);
 virtual void GetPDFAndQCDError(TString HistName, vector<TH1D *> HistVector);
 virtual void SaveFile();
 virtual void LinkHist(HistsWZPolarization *myhists);

};
#endif
