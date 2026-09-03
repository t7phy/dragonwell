#ifndef SysHist_h
#define SysHist_h

#include "TH1D.h"
#include "TString.h"
#include <vector>
#include "Tools/Tools.h"

using namespace std;

class SysHist
{
 public:

 vector<TString> sysName;

 TH1D* myHist[1000];
 vector<TH1D *> SysHist_1d;

 TString HistName = "";

 SysHist(vector<TString> sysName);
 virtual void DefineHist(TString name, TString title, int nbin, double left, double right);
 virtual void DefineHist(TString name, TString title, int nbin, double* xbins);
 virtual void Fill(int isys, double par, double weight);
 virtual void DeleteHist();
 virtual void Add(SysHist* hist1);
 virtual void Reset();
 virtual void Write();

};
#endif
