#ifndef MCFMWWBoost_h
#define MCFMWWBoost_h

#include "RootCommon.h"
#include "ReadInRoot/ReadInRoot.h"
#include "Analysis/HistsResBos.h"

using namespace std;

class MCFMWWBoost : public ReadInRoot
{
 public:

 HistsResBos* myhists;

 double DataPoint;
 double TheoryPoint;
 double Uncertainty;
 double Residue;

 int TotalBin = 0;
 int DataType;
 double *BinCenter;
 double *Binning;
 double *DeltaBin;

 int iplot = 0;
 map<TString, TH1D *> DataHist;
 map<TString, TH1D *> TheoryHist;

 int iplot2D = 0;
 TH2D* Data2D[100];
 TH2D* Theory2D[100];

 TH1D* BoostAsymmetry;
 TH1D* BoostAsymmetryW;

 TString subName = "";

 virtual void LinkHist(HistsResBos* &myhists);
 virtual void WriteIn(TString VariableName);
 virtual void GetBinning(const char* name, TString VariableName);
 virtual void GetAdditionalPlot();
 virtual void ReadInMCFM_10_3(TString FileName, TH1D* &hist, int RemoveBins);

 virtual void InputSubName(TString subName){this->subName = subName;};

 virtual void Add(MCFMWWBoost* run){
   for(auto iter = DataHist.begin(); iter != DataHist.end(); iter++){
     this->DataHist[iter->first]->Add(run->DataHist[iter->first]);
   }
 }
 virtual void Divide(MCFMWWBoost* run){
   for(auto iter = DataHist.begin(); iter != DataHist.end(); iter++){
     this->DataHist[iter->first]->Divide(run->DataHist[iter->first]);
   }
 }
 virtual void Scale(double num){
   for(auto iter = DataHist.begin(); iter != DataHist.end(); iter++){
     this->DataHist[iter->first]->Scale(num);
   }
 }
 virtual void Write(){
   for(auto iter = DataHist.begin(); iter != DataHist.end(); iter++){
     this->DataHist[iter->first]->Write();
   }
 }
};

#endif
