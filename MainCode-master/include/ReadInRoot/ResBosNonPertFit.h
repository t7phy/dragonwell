#ifndef ReadInRoot_ResBosNonPertFit_h
#define ReadInRoot_ResBosNonPertFit_h

#include "ReadInRoot/ReadInRoot.h"
#include "Analysis/HistsResBos.h"

using namespace std;

class ResBosNonPertFit : public ReadInRoot
{
 public:

 HistsResBos* myhists;

 double DataPoint;
 double TheoryPoint;
 double Uncertainty;
 double Residue;

 double QMin = 0.0;
 double QMax = 0.0;
 double ymin = 0.0;
 double ymax = 0.0;
 double pT, Chi2, Shift, ShiftData, UnCorrErr, pdfErr, reducedChi2;

 double SavedQMin = 0.0;
 double SavedQMax = 0.0;
 double SavedYmin = 0.0;
 double SavedYmax = 0.0;

 int TotalBin = 0;
 int DataType;
 double *BinCenter;
 double *Binning;

 int iplot = 0;
 int TotalPlot;
 TH1D* DataHist[100];
 TH1D* TheoryHist[100];
 TH1D* OriginalDataHist[100];
 TH1D* ReducedChi2[100];


 int iplot2D = 0;
 TH2D* Data2D[100];
 TH2D* Theory2D[100];
 TH2D* OriginalData2D[100];

 TString skip;

 int Nbin = 0;

 virtual void LinkHist(HistsResBos* &myhists);
 virtual void WriteIn(TString ExperimentName);
 virtual void GetBinning(const char* name, int DataID, TString ExperimentName);
 virtual void WriteIn();
 virtual void CopyHist(TString ExperimentName, TH1D* h1, int nPlot);
 virtual void GetBinning(const char* name);
 virtual void Get2DPlot();
 virtual void RetrieveHist(TString Type, int Index, TH1D* &hist);
};
#endif
