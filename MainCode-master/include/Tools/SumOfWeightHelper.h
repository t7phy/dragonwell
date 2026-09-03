#ifndef Tools_SumOfWeightHelper_h
#define Tools_SumOfWeightHelper_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class SumOfWeightHelper
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

 Double_t        totalWeightedEntries;
 Long64_t        runNumber;

 TBranch         *b_totalWeightedEntries;   //!
 TBranch         *b_runNumber;   //!

 SumOfWeightHelper(const char* FileList);
 virtual void GetSumOfWeight();
 virtual int GetRootType(TString RootName);
 virtual int GetYear(TString RootName);

};

#endif
