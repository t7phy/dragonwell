#ifndef UnfoldHist_h
#define UnfoldHist_h

#include "TH1D.h"
#include "TString.h"
#include <vector>
#include <iostream>
#include <map>
#include "Tools/Tools.h"

using namespace std;

class UnfoldHist
{
 public:

 int nbin_reco;
 int nbin_truth;

 TString name;

 vector<TH1D *> TruthToReco;
 vector<TH1D *> RecoToTruth;
 TH1D* RecoHist;
 TH1D* TruthHist;

 map<int, TH1D *> UnfoldedHist;
 map<int, TH1D *> PriorHist;

 TH2D* ResponseMatrix;

 UnfoldHist();

 virtual void DefineHist(TString name, TString title, int nbin_reco, double left_reco, double right_reco, int nbin_truth, double left_truth, double right_truth);
 virtual void DefineHist(TString name, TString title, int nbin_reco, double* xbins_reco, int nbin_truth, double* xbins_truth);
 virtual void Fill(double reco, double truth, double weight);

 virtual void Unfolding();

 virtual void DeleteHist();
 virtual void Add(UnfoldHist* hist1);
 virtual void Reset();
 virtual void Write();

};
#endif

