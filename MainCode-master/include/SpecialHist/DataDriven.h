#ifndef SpecialHist_DataDriven_h
#define SpecialHist_DataDriven_h

#include "TH1D.h"
#include "TH2D.h"
#include "TString.h"
#include <vector>
#include <iostream>
#include <map>
#include "Tools/Tools.h"

class DataDriven
{
 public:

 int FakeObjects;

 TH1D *ZElFakeRate;
 TH1D *ZMuFakeRate;
 TH1D *WElFakeRate;
 TH1D *WMuFakeRate;

 TH1D *ZElFakeRate_UpSys;
 TH1D *ZMuFakeRate_UpSys;
 TH1D *WElFakeRate_UpSys;
 TH1D *WMuFakeRate_UpSys;

 TH1D *ZElFakeRate_DownSys;
 TH1D *ZMuFakeRate_DownSys;
 TH1D *WElFakeRate_DownSys;
 TH1D *WMuFakeRate_DownSys;

 TH1D *ZElFakeEff;
 TH1D *ZMuFakeEff;
 TH1D *WElFakeEff;
 TH1D *WMuFakeEff;

 TH1D *ZElRealEff;
 TH1D *ZMuRealEff;
 TH1D *WElRealEff;
 TH1D *WMuRealEff;

 TH1D *ElFakeEff;
 TH1D *MuFakeEff;
 TH1D *ElRealEff;
 TH1D *MuRealEff;
 TH2D *ElFakeEff2D;
 TH2D *MuFakeEff2D;
 TH2D *ElRealEff2D;
 TH2D *MuRealEff2D;

 int Lep1_bin;
 int Lep2_bin;
 int Lep3_bin;

 double F1 = 0.0;
 double F2 = 0.0;
 double F3 = 0.0;

 double F1_UpStat = 0.0;
 double F2_UpStat = 0.0;
 double F3_UpStat = 0.0;

 double F1_DownStat = 0.0;
 double F2_DownStat = 0.0;
 double F3_DownStat = 0.0;

 double F1_UpSys = 0.0;
 double F2_UpSys = 0.0;
 double F3_UpSys = 0.0;

 double F1_DownSys = 0.0;
 double F2_DownSys = 0.0;
 double F3_DownSys = 0.0;

 double f1 = 0.0;
 double f2 = 0.0;
 double f3 = 0.0;
 double e1 = 0.0;
 double e2 = 0.0;
 double e3 = 0.0;
 double f1bar = 0.0;
 double f2bar = 0.0;
 double f3bar = 0.0;
 double e1bar = 0.0;
 double e2bar = 0.0;
 double e3bar = 0.0;

 TH1D *FakeRate[3];
 TH1D *FakeRate_UpSys[3];
 TH1D *FakeRate_DownSys[3];
 TH1D *FakeEff[3];
 TH1D *RealEff[3];
 vector<TH1D *> v_FakeRate;

 TH2D *FakeMatrix;
 TH2D *InverseFakeMatrix;

 bool isUnknown = false;

 map<vector<int>, TH2D *> FakeMatrixMap;
 map<vector<int>, TH2D *> InverseFakeMatrixMap;

 int doFakeRate = -999;
 bool isInputUpSysFakeRate = false;
 bool isInputDownSysFakeRate = false;


 DataDriven();
 DataDriven(int nfake);

 // 3 leptons
 virtual void InputFakeRate(TH1D* ZElFakeRate, TH1D* ZMuFakeRate, TH1D* WElFakeRate, TH1D* WMuFakeRate);
 virtual void InputUpSysFakeRate(TH1D* ZElFakeRate, TH1D* ZMuFakeRate, TH1D* WElFakeRate, TH1D* WMuFakeRate);
 virtual void InputDownSysFakeRate(TH1D* ZElFakeRate, TH1D* ZMuFakeRate, TH1D* WElFakeRate, TH1D* WMuFakeRate);
 virtual void InputFakeEfficiency(TH1D* ZElFakeEff, TH1D* ZMuFakeEff, TH1D* WElFakeEff, TH1D* WMuFakeEff);
 virtual void InputRealEfficiency(TH1D* ZElRealEff, TH1D* ZMuRealEff, TH1D* WElRealEff, TH1D* WMuRealEff);
 virtual void GetIndex(double Lep1Pt, double Lep2Pt, double Lep3Pt, TString Flavor);
 virtual void GetIndexFullMatrix(double Lep1Pt, double Lep2Pt, double Lep3Pt, TString Flavor);
 virtual void GetMatrix(int iThread);

 // 2 leptons

 // 1 lepton
 virtual void InputFakeEfficiency(TH1D* ElFakeEff, TH1D* MuFakeEff);
 virtual void InputRealEfficiency(TH1D* ElRealEff, TH1D* MuRealEff);
 virtual void InputFakeEfficiency(TH2D* ElFakeEff, TH2D* MuFakeEff);
 virtual void InputRealEfficiency(TH2D* ElRealEff, TH2D* MuRealEff);
 virtual void GetIndex(double par, int Flavor);
 virtual void GetIndex2D(double par1, double par2, int Flavor);

 bool isRunUpStat = false;
 bool isRunDownStat = false;
 virtual void RunUpStat(){isRunUpStat = true;};
 virtual void RunDownStat(){isRunDownStat = true;};

};
#endif
