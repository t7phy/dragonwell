#ifndef ZPrime_SumOfWeight_h
#define ZPrime_SumOfWeight_h

#include "RootCommon.h"

using namespace std;

class ZPrimeSumOfWeight
{
 public:

 TFile *rootfile;
 TTree *metaTree;
 int metaTreeEntries;

 vector<TString> RootNames;
 map<pair<int, int>, double> SumOfWeightsMap;
 map<pair<int, int>, double> LumiMap;

 vector<int> Channels;
 vector<int> Years;

 double Lumi1516 = 0.0;
 double Lumi17 = 0.0;
 double Lumi18 = 0.0;

 Float_t        totalEventsWeighted;
 Int_t           dsid;

 TBranch         *b_totalEventsWeighted;   //!
 TBranch         *b_dsid;   //!

 ZPrimeSumOfWeight(TString FileList);
 virtual void GetSumOfWeight();
 virtual TString GetRootType(TString name);
 virtual int GetYear(TString RootName);

};
#endif
