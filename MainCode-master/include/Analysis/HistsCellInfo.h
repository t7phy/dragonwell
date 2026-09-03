#ifndef __HISTS_CELLINFO_H_
#define __HISTS_CELLINFO_H_
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TMath.h"
#include "TTree.h"
#include <vector>
#include "Analysis/makeHists.h"

using namespace std;

class HistsCellInfo : public makeHists
{
 public:

 bool isFillCellHist = false;

 map<int, TH2D*> CellHistMap;

 map<double, int> CellEtaBinMap;
 map<double, int> CellPhiBinMap;
 map<double, int> CellXBinMap;
 map<double, int> CellYBinMap;

 ThreadHist<TH2D *>* ClusterSizeMu;

 ThreadHist<TH1D *>* ClusterSizeLowMu;

 ThreadHist<TH1D *>* ClusterSizeMediumMu;

 ThreadHist<TH1D *>* ClusterSizeHighMu;


 virtual void bookCellHist(int iCluster, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty);
 virtual void bookCellHist(int iCluster, set<double> CellEta, set<double> CellPhi);
 virtual void FillCellHist(int iCluster, map<pair<int, int>, double> CellEnergyMap);
 virtual void FindCellBin(int iCluster, double keyx, double keyy, double Value, map<pair<int, int>, double> &CellEnergyMap);
 virtual void FindCellBin(int iCluster, map<pair<double, double>, double> CellMap, map<pair<int, int>, double> &CellEnergyMap);
 virtual void FindCellBin(int iCluster, set<double> CellEta, set<double> CellPhi, double deta, double dphi, map<pair<double, double>, double> CellMap);
 virtual void FindCellBinXY(int iCluster, set<double> CellX, set<double> CellY, double dx, double dy, map<pair<double, double>, double> CellMapXY);

//member function
 vector<TString> sysName;
 virtual void InitialSysName();
 virtual void bookHists(int TotalThread);

// template<class T>

};
#endif
