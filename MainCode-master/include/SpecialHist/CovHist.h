#ifndef CovHist_h
#define CovHist_h

#include "TH1D.h"
#include "TH2D.h"
#include "TString.h"
#include <vector>
#include <iostream>
#include <map>
#include "Tools/Tools.h"

using namespace std;

class CovHist
{
 public:

 TH1D* myHist[1000];
 vector<TH1D *> CovHist_1d;

 TH1D* HistCentral;
 TH1D* HistError;
 TH2D* CovarianceHist;
 TH2D* CorrelationHist;

 double DataMean, DataRMS, CovarianceValue;

 double* DataPoint;
 vector<double> v_DataPoint[1000];

 int length;

 CovHist(int length = 1000);
 virtual void DefineHist(TString name, TString title, int nbin, double left, double right);
 virtual void InputHist(vector<TH1D *> v_hist, TString name, TString title, int nbin, double left, double right);
 virtual void Fill(double par, double weight, int i);
 virtual void GetUncertainty();
 virtual void DeleteHist();
 virtual void Add(CovHist* hist1);
 virtual void Reset();
 virtual void Write();


};
#endif
