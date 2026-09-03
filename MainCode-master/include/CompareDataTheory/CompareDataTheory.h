#ifndef CompareDataTheory_h
#define CompareDataTheory_h

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Uncertainty/PDFUncertainty.h"

class CompareDataTheory
{
 public:

 TFile *hf;
 TFile *outFile;
 bool isLinkFile = false;

 int DataNbins;
 int TheoryNbins;

 int DataCovCount = 1;
 int TheoryPlotCount = 1;

 TH1D* DataPlot;
 TH1D* DataError[100];
 TH2D* DataCovariance[100];
 TH2D* TotalDataCovariance;

 TH1D* TheoryPlot[100];
 TH2D* TheoryStaCovariance[100];
 TH2D* TheoryPDFCovariance;
 TH2D* TotalTheoryCovariance[100];

 bool isPDFCovariance = false;

 TH2D* TotalCovariance[100];
 TH2D* InverseCovariance[100];
 double Chi2[100] = {0};
 double Sigma[100] = {0};

 TH2D* TemplateStaCovariance[100];
 TH2D* TemplateCovariance[100];
 TH2D* TemplateInverseCovariance[100];
 double TemplateChi2[100];
 TH1D* Chi2Hist;
 TF1* FitHist;

 TH1D* Ratio[100];
 TH1D* RatioTemplate[100];

 double TheoryStatCov;

 bool isOutput = false;
 bool isUnCorrSys = false;
 bool isIgnoreTemplateStatistic = false;

 int size;
 double left, right;

 bool isInputBinRange = false;
 int FirstBin;
 int LastBin;

 CompareDataTheory();
 virtual void InputDataCentral(TH1D* DataPlot, int isGetError = 0);
 virtual void InputDataStaCorrelation(TH2D* Correlation, TH1D* StaErr);
 virtual void InputDataStaErr(TH1D* StaErr);
 virtual void InputDataCovariance(TH2D* Covariance);
 virtual void InputDataSysErr(vector<TH1D *> DataSysErr);
 virtual void GetTotalDataCovariance();
 virtual void InputTheoryCentral(vector<TH1D *> TheoryPlotList);
 virtual void InputTheoryPDFCovariance(TH2D* Covariance);
 virtual void GetTotalTheoryCovariance();
 virtual void InputTemplateRange(int size, double left, double right);
 virtual void InputTheoryTemplate(vector<TH1D *> TheoryTemplate);
 virtual void FitAFBStw(vector<TH1D *> v_Plot);
 virtual void GetChi2();
 virtual void OpenFile(TString FileName);
 virtual void Save();
 virtual void Output(){isOutput = true;}
 virtual void MakeSysUnCorr(){isUnCorrSys = true;}
 virtual void IgnoreTemplateStatistic(){isIgnoreTemplateStatistic = true;}
 virtual void GetPDFUncertainty(vector<TH1D *> PDFHists, vector<TH1D *> STWHists, double &PDFUnc);
 virtual void LinkOutFile(TFile* &outFile);
 virtual void InputBinRange(int FirstBin, int LastBin);
};
#endif
