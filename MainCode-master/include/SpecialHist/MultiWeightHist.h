#ifndef SpecialHist_MultiWeightHist_h
#define SpecialHist_MultiWeightHist_h

#include "RootCommon.h"
#include "Tools/Tools.h"

using namespace std;

class MultiWeightHist
{
 public:

 int nWeight = 1;

 int nbin;
 TString name;

 vector<TH1D *> hist_vector;

 MultiWeightHist();
 MultiWeightHist(int nWeight);
 virtual void DefineHist(TString name, TString title, int nbin, double left, double right);
 virtual void DefineHist(TString name, TString title, int nbin, double* xbins);
 virtual void Fill(double par1, vector<double> weights);
 virtual MultiWeightHist* Clone(TString name);
 virtual void Add(MultiWeightHist *hist2);
 virtual void Divide(MultiWeightHist *hist2);
 virtual MultiWeightHist* GetAsymHist(MultiWeightHist *hist2);
 virtual TH1D* GetHistPtr(int i){return hist_vector.at(i);};
 virtual void Reset();
 virtual void DeleteHist();
 virtual void Write();

};

#endif
