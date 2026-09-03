#ifndef ReadInRoot_ePumpOutput_h
#define ReadInRoot_ePumpOutput_h

#include "ReadInRoot/ReadInRoot.h"
#include "Analysis/HistsResBos.h"

using namespace std;

class ePumpOutput : public ReadInRoot
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

 int iplot = 0;

 int iplot2D = 0;
 TH2D* Data2D[100];
 TH2D* Theory2D[100];

 TH1D* OldSpartynessHist;
 TH1D* NewSpartynessHist;
 TH1D* DeltaSpartynessHist;

 double OldSpartyness;
 double NewSpartyness;

 vector<TString> Experiments;

 ePumpOutput();
 virtual void LinkHist(HistsResBos* &myhists);
 virtual void WriteIn();
 virtual void RetrieveHist(TH1D* &Old, TH1D* &New, TH1D* &Delta);
 virtual void Get2DPlot();
 virtual void InitialExperiments();
};
#endif
