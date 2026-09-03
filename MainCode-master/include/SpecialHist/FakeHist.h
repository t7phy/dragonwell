#ifndef SpecialHist_FakeHist_h
#define SpecialHist_FakeHist_h

#include "TH1D.h"
#include "TString.h"
#include <vector>
#include <iostream>
#include <map>
#include "Tools/Tools.h"
#include "SpecialHist/DataDriven.h"

class FakeHist
{
 public:

 int FakeObjects;

 DataDriven *myFakeRate;

 int passTTT = 0;
 int passTTL = 0;
 int passTLT = 0;
 int passLTT = 0;
 int passTLL = 0;
 int passLTL = 0;
 int passLLT = 0;
 int passWeight[7] = {0};

 double passTTTWeight = 0.0;
 double passTTLWeight = 0.0;
 double passTLTWeight = 0.0;
 double passLTTWeight = 0.0;
 double passTLLWeight = 0.0;
 double passLTLWeight = 0.0;
 double passLLTWeight = 0.0;

 map<TString, TH1D *> myHist;
 TH1D *myHist_RRR;
 TH1D *myHist_RRF;
 TH1D *myHist_RFR;
 TH1D *myHist_FRR;
 TH1D *myHist_RFF;
 TH1D *myHist_FRF;
 TH1D *myHist_FFR;

 vector<TH1D *> FakeHist_1d;
 TString HistName = "";

 TH1D *FinalFakeHist;
 TH1D *FinalFakeHist_UpStat;
 TH1D *FinalFakeHist_DownStat;
 TH1D *FinalFakeHist_UpSys;
 TH1D *FinalFakeHist_DownSys;

 int doFakeRate = -999;
 bool isInputUpSysFakeRate = false;
 bool isInputDownSysFakeRate = false;

 bool isFillUpStatFakeRate = true;
 bool isFillDownStatFakeRate = true;

 FakeHist();
 virtual void DefineHist(TString name, TString title, int nbin, double left, double right);
 virtual void DefineHist(TString name, TString title, int nbin, double* xbins);
 virtual void LinkFakeRate(DataDriven* myFakeRate);
 virtual void Initial(int passTTT, int passTTL, int passTLT, int passLTT, int passTLL, int passLTL, int passLLT);
 virtual void InitialWeight(double passTTTWeight, double passTTLWeight, double passTLTWeight, double passLTTWeight, double passTLLWeight, double passLTLWeight, double passLLTWeight);
 virtual void Fill(double par, double Weight);
 virtual void FillFullMatrix(double par, double Weight);
 virtual void GetFakeHist();
 virtual void GetFakeHistFullMatrix();
 virtual void DeleteHist();
 virtual void Add(FakeHist* hist1);
 virtual void Reset();
 virtual void Write();

};
#endif
