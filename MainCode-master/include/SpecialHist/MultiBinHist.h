#ifndef SpecialHist_MultiBinHist_h
#define SpecialHist_MultiBinHist_h

#include "TH1D.h"
#include "TH2D.h"
#include "TString.h"
#include <vector>
#include <iostream>
#include <map>

using namespace std;

class MultiBinHist
{
 public:

 vector<vector<double>> MultiBinVector;
 double** MultiBin;

 int nbin;
 TString name;

 TH2D* myHist[1000];
 vector<TH2D *> hist_vector;

 MultiBinHist();
 MultiBinHist(vector<vector<double>> MultiBinVector);
 virtual void DefineHist(TString name, TString title, int nbin, double* xbins);
 virtual void Fill(double par1, double par2, double weight);
 virtual void Input(vector<TH2D *> hist_vector);
 virtual MultiBinHist* Clone(TString name);
 virtual void Add(MultiBinHist *hist2);
 virtual void Divide(MultiBinHist *hist2);
 virtual double Integral(int i);
 virtual void Reset();
 virtual void DeleteHist();
 virtual void Write();

};

void AFBFunction(MultiBinHist* FZmass, MultiBinHist* BZmass, MultiBinHist* &Draw_AFB);
void GetAFBDiff(MultiBinHist* AFB, MultiBinHist* &AFBDiff);
void InverseHistXaxis(MultiBinHist *h1, MultiBinHist* &inverse_h1);
void ApplyDilution(MultiBinHist* &FZmass, MultiBinHist* &BZmass, MultiBinHist* Dilution, bool isGG, vector<double> S0);
double CalculateChi2(MultiBinHist* h1, MultiBinHist* h2);

#endif
