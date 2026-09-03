#ifndef PDFHelper_OldPDFFigure_h
#define PDFHelper_OldPDFFigure_h

#include <iostream>
#include "RootCommon.h"
#include "ElectroweakTheory/ZWidthDep.h"

#ifdef USE_LHAPDF
#include "LHAPDF/LHAPDF.h"
#include "LHAPDF/Reweighting.h"
#endif

#include "CTEQHelper/pdsReader.h"

using namespace std;
//using namespace LHAPDF;

class OldPDFFigure
{
 public:

#ifdef USE_LHAPDF
 LHAPDF::PDF* pold;
 LHAPDF::PDF* pnew;
 map<int, LHAPDF::PDF*> myPDF;
#endif

 map<int, pdsReader*> CTPDF;
 map<pair<TString, int>, pdsReader*> CTPDFIndex;
 map<TString, int> CTPDFnSet;

 map<int, bool> isInitialPDF;
 map<int, int> nSetMap;

 map<int, TString> PDFType;
 map<int, int> PDFErrorIndex;


 double qold[2], qnew[2], PDFweight;

 TString PDFName = "";
 TString PDFName1 = "";
 TString PDFName2 = "";
 int iSet = 0;
 int iSet1 = 0;
 int iSet2 = 0;
 map<int, TString> PDFNameMap;
 map<TString, int> PDFNameIndex;


 int nBin = 4999;
 double LogBin[5000] = {0.0};
 double muF = 1.0;
 map<int, double> CLFactor;

 TFile *hf;

 map<pair<int, int>, TH1D *> PDFCentralPlot;
 map<pair<int, int>, TH1D *> PDFErrorPlot;
 map<pair<int, int>, TH1D *> PDFErrorPlusPlot;
 map<pair<int, int>, TH1D *> PDFErrorMinusPlot;

 map<vector<int>, TH1D *> PDFCentralRatioPlot;
 map<vector<int>, TH1D *> PDFErrorRatioPlot;
 map<vector<int>, TH1D *> PDFErrorPlusRatioPlot;
 map<vector<int>, TH1D *> PDFErrorMinusRatioPlot;

 map<vector<int>, TH1D *> PDFEigenPlot;
 map<vector<int>, TH1D *> PDFEigenRatioPlot;
 map<vector<int>, TH1D *> PDFEigenErrorPlot;

 map<int, TString> FlavorNameMap;

 bool isTimeX = false;

 OldPDFFigure();
 virtual void InitialPDF(int iPDF, const char* PDFName, int PDFset = 0);
 virtual void InitialCTEQPDF(int iPDF, TString PDFName, TString GivenName, int PDFset = 0);
 virtual void InitialCTEQPDFSets(int iPDF, vector<TString> PDFNames, TString GivenName);
 virtual void InitialErrorPDF(int iPDF, const char* PDFName, int PDFset);
 virtual void InitialPDF1(const char* PDFName, int PDFset = 0);
 virtual void InitialPDF2(const char* PDFName, int PDFset = 0);
 virtual void InitialTwoPDF(const char* PDFName1, const char* PDFName2, int PDFset1 = 0, int PDFset2 = 0);
 virtual void InputPDFnSet(int iPDF, int nSet);

 virtual void CompareTwoPDFWithError(int flavor);
 virtual void ComparePDFWithEigen(int flavor);
 virtual void ComparePDFWithEigen(int iPDF1, int iPDF2, int flavor);

 virtual void GetPDFRatio(int iPDF1, int iPDF2, int flavor);
 virtual void GetPDFEigenRatio(int iPDF1, int iPDF2, int Eigen, int flavor);

 virtual void GetPDFCentral(int iPDF, int flavor);
 virtual void GetPDFEigen(int iPDF, int Eigen, int flavor);
 virtual void GetPDFError(int iPDF, int flavor);

 virtual TH1D* DrawPDFvsX(int iPDF, int flavor, double Q, vector<double> x);
 virtual TH1D* DrawPDFvsQ(int iPDF, int flavor, double x, vector<double> Q);

 virtual double Getf(int iPDF, int flavor, double x, double Q, int iSet = 0);
 virtual double Getxf(int iPDF, int flavor, double x, double Q);

 virtual double GetfError(TString PDFName, int flavor, double x, double Q, TString ErrorType);

 virtual void DefineCombination();

 virtual void SetCL90(int iPDF){CLFactor[iPDF] = 1.0;};
 virtual void SetCL68(int iPDF){CLFactor[iPDF] = 1.645;};
 virtual void TimeX(){isTimeX = true;};
 virtual void openFile(TString FileName);
 virtual void SaveFile();

};
#endif
