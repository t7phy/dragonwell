#ifndef BkgHist_h
#define BkgHist_h

#include "TH1D.h"
#include "TString.h"
#include <vector>
#include <iostream>
#include <map>
#include "Tools/Tools.h"

using namespace std;

class BkgHist
{
 public:

 int MCType;
 TString MCTypeName;

 vector<TString> bkgName;
 map<TString, int> NameIndex;

 TString RequiredProcessName;
 vector<TString> UsedList;
 map<int, int> ListFlag;

 TString HistName;

 TH1D* myHist[1000];
 TH2D* myHist2D[1000];

 vector<TH1D *> BkgHist_1d;
 vector<TH2D *> BkgHist_2d;

 int Dimension = 1;

 vector<TString> AdditionalName;
 map<TString, TH1D *> AdditionalHist;
 map<TString, TH2D *> AdditionalHist2D;

 double KFactor = 1.0;
 double KFactors[1000] = {1.0};

 bool isWplusenuEvent = false;
 bool isWplusmunuEvent = false;
 bool isWplustaonuEvent = false;
 bool isWminusenuEvent = false;
 bool isWminusmunuEvent = false;
 bool isWminustaonuEvent = false;
 bool isZeeEvent = false;
 bool isZmumuEvent = false;
 bool isData = false;

 int iBkg = -1;
 int iWHist = -1;

 bool NoBkgHist = false;

 TString ProcessName;
 TString ShortName;

 BkgHist(TString ProcessName);
 virtual void DefineHist(TString name, TString title, int nbin, double left, double right, int iflag = 1);
 virtual void DefineHist(TString name, TString title, int nbin, double* xbins, int iflag = 1);
 virtual void DefineHist(TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty, int iflag = 1);
 virtual void DefineHist(TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins, int iflag = 1);
 virtual void DefineAdditionalName();
 virtual void DefineAdditionalHist(TString name, TString title, int nbin, double left, double right);
 virtual void DefineAdditionalHist(TString name, TString title, int nbin, double* xbins);
 virtual void DefineAdditionalHist(TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty);
 virtual void DefineAdditionalHist(TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins);
 virtual void Initial(int MCType);
 virtual void Initial(TString MCTypeName);

 virtual void DefineBkgName(TString ProcessName);
 virtual void GetRequiredList(TString ProcessName);
 virtual void Fill(double par, double weight);
 virtual void Fill(double par1, double par2, double weight);
 virtual void InputKFactor(double KFactor);
 TH1D* GetHistPtr(TString name);
 TH2D* GetHistPtr2D(TString name);
 virtual void DeleteHist();
 virtual void Add(BkgHist* hist1);
 virtual void Reset();
 virtual void Write();

};
#endif
