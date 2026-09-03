#ifndef TMVAInterface_TMVAReader_h
#define TMVAInterface_TMVAReader_h

#include "RootCommon.h"

#ifdef USE_TMVA
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#endif

using namespace std;

class TMVAReader
{
 public:
#ifdef USE_TMVA
 map<TString, TMVA::Reader *> readerMap;
 map<TString, TString> MethodMap;
#endif

 map<TString, TFile *> FileMap;
 map<pair<TString, TString>, TTree *> TreeMap;
 map<TString, TH1D *> HistMap;
 map<TString, Float_t> ValueMap;
 map<TString, Double_t> ContentMap;

 TMVAReader();
 virtual void InputTree(TString FileName, TString TreeName);
 virtual void Initialize(TString ComponentName);
 virtual void BookMVA(TString ComponentName, TString MethodName, TString FileName);
 virtual void AddVariable(TString Name);
 virtual void DefineHist(TString ComponentName, int nbin, double left, double right);
 virtual void LoopTrees(TString ComponentName, vector<pair<TString, TString>> FileNames);
 virtual TH1D* RetrieveHist(TString ComponentName);
 virtual double EvaluateMVA(TString ComponentName);
};
#endif
