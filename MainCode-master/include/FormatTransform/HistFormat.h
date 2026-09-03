#ifndef FormatTransform_HistFormat_h
#define FormatTransform_HistFormat_h

#include "RootCommon.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TString.h"
#include <vector>
#include <iostream>
#include <map>
#include "WZPolarization/HistsWZPolarization.h"

using namespace std;

class HistFormat
{
 public:

 TFile *hf;
 TFile *HistFile;

// vector<TString> regionNames{"WZInclusive", "SR", "LowPtZVR", "HighPtWZVR"};
 vector<TString> regionNames{"WZInclusive", "SR", "SRPtZ100", "PtWZ10CR", "PtWZ20CR", "PtWZ40CR", "PtWZ70CR"};

 vector<TString> sampleNames{"Data", "WZQCD", "WLZL", "WLZT", "WTZL", "WTZT", "ZZ", "WZEW", "VVV", "ttbarV", "Non-prompt", "Pseudodata", "WZMixed", "WZRest"};

// vector<TString> categoryNames{"all", "CatLL", "CatLT", "CatTL", "CatTT"};
 vector<TString> categoryNames{"all"};

 map<TString, int> SysNameIndex;
 map<TString, TFile*> SysHistMap;

 vector<TString> HistNames;

 HistsWZPolarization *fHist;

 Int_t Sta_HistNumber = 0;

 HistFormat();
 virtual ~HistFormat();
 virtual void openFile(const char* FileName);
 virtual void openHistFile(const char* FileName);
 virtual void openSysHistFile(TString FileName);
 virtual void InitialHistName();
 virtual void InitialFileStructure();
 virtual void FillHist(TString regionName, TString sampleName, TString categoryName, TDirectory *dir);
 virtual void SaveFile();
 virtual void LinkHist(HistsWZPolarization *myhists);

};
#endif
