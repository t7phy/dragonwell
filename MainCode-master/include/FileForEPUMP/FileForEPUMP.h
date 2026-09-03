#ifndef FileForEPUMP_h
#define FileForEPUMP_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TMath.h"
#include "TH1D.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "TH3F.h"
#include <TRandom3.h>
#include <TMinuit.h>
#include <TApplication.h>
#include "TEnv.h"
#include <TComplex.h>
#include <TGraph.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include "TTree.h"
#include "Tools/Tools.h"
#include "Uncertainty/PDFUncertainty.h"

using namespace std;

class FileForEPUMP
{
 public:

 TString fileName;

 ofstream myData;
 ofstream myTheory;

 double DataPoint;
 double StaError, TotError, UncError, Corr1, Corr2;
 double Corr[100];
 double StaErrorX, StaErrorY, UncErrorX, UncErrorY;
 double CorrelationCoefficient, StaCovariance;
 double DataPointkFactor = 1;
 double StaErrorkFactor = 1;
 double SysErrorkFactor = 1;

 int DataNBin = 0;

 char pdfname[40];

 bool isRebin;
 int RebinType;
 double *xbins;
 int size;

 bool isInputStaErr = false;
 bool isInputSysErr = false;
 bool isInputCorrSysErr = false;
 double *StaErr;
 double *SysErr;
 double *CorrSysErr[100];
 TString CorrSysName[100];
 int CountCorrSysErr = 0;

 double *TheoryPoint;
 double *DataStaError1;
 double *DataStaError2;
 double *DataStaError3;

 double DataStaError2D[100][100];

 double myR;

 TFile *file = 0;
 TFile *file1 = 0;
 TFile *file2 = 0;
 TFile *CorrelationFile;
 TFile *CovarianceFile;

 TH1D* h1;
 TH1D* h2;
 TH2D* Correlation;
 TH2D* CovarianceMatrix;

 bool isInputCorrelationFile = false;
 bool isInputCovarianceMatrix = false;
 bool CorrelationPlus;
 bool CorrelationZero;
 bool CorrelationMinus;

 TH1D* FZmass;
 TH1D* BZmass;

 TH1D* Wplus;
 TH1D* Wminus;
 TH1D* ZRapidity;

 TH2D* Hist2D_1;
 TH2D* Hist2D_2;

 TH3D* Hist3D_1;
 TH3D* Hist3D_2;

 TFile* files[100] = {0};
 TFile* files1[100] = {0};
 TFile* files2[100] = {0};
 TFile* Extendedfiles[100] = {0};
 TH1D* histos[100];
 TH1D* histos1[100];
 TH1D* histos2[100];
 TH1D* histos3[100];
 TH1D* Extendedhistos[100];

 TH2D* histos2d[100];
 TH2D* histos2d_1[100];
 TH2D* histos2d_2[100];

 TH3D* histos3d[100];
 TH3D* histos3d_1[100];
 TH3D* histos3d_2[100];

 vector<TFile *> v_files;
 vector<TFile *> v_files1;
 vector<TFile *> v_files2;
 vector<TH1D *> v_histos;
 vector<TH1D *> v_histos1;
 vector<TH1D *> v_histos2;
 vector<TH1D *> v_histos3;
 map<TString, vector<TH1D *>> v_Extendedhistos;

 vector<TH2D *> v_histos2d;
 vector<TH3D *> v_histos3d;

 vector<TString> ParaNames;

 bool isAFB;
 bool isDataAFB = false;
 bool isTheoryAFB = false;
 bool isDataRefWZ = false;
 bool isTheoryRefWZ = false;
 bool isSideband;
 bool isStatSmear;

 bool isRemoveBins = false;
 double RemoveLeftBin = 0.0;
 double RemoveRightBin = 0.0;

 bool isSkipRange = false;
 double SkipLeft = 0.0;
 double SkipRight = 0.0;
 double xSkipLeft = 0.0;
 double xSkipRight = 0.0;
 double ySkipLeft = 0.0;
 double ySkipRight = 0.0;

 bool isInput = false;
 bool isInput2D = false;
 bool isInput3D = false;

 int Error_type;

 bool isNorm = false;
 int DataNormFactor = 1;
 int TheoryNormFactor = 1;
 double DataCrossSection = 1.0;
 double TheoryCrossSection = 1.0;

 bool isReweightStatistics = false;
 double CustomLuminosity = 1.0;

 bool doCallWriteData = false;
 map<int, bool> DataWritenMap_1d;
 map<tuple<int, int>, bool> DataWritenMap_2d;
 map<tuple<int, int, int>, bool> DataWritenMap_3d;

 map<tuple<int, int, int>, bool> RemoveTag3D;

 FileForEPUMP(const char* fileName);
 virtual ~FileForEPUMP();
 virtual void InputData(const char* rootName, const char* histName, int iflag = 1);
 virtual void InputData(const char* rootName, const char* histName1, const char* histName2, TString Process, int iflag = 1);
 virtual void InputData(const char* rootName, const char* histName1, const char* histName2, int iflag = 1);
 virtual void InputData(const char* rootName1, const char* rootName2, const char* histName1, const char* histName2, const char* histName3, int iflag = 1);
 virtual void InputData(TH1D *h1){this->h1 = (TH1D *)h1->Clone((TString)h1->GetName() + "_ClonedData");};
 virtual void Input2DData(const char* rootName, const char* histName1);
 virtual void Input2DData(const char* rootName, const char* histName1, const char* histName2, TString Process);
 virtual void Input2DData(const char* rootName, const char* histName, int ibin);
 virtual void Input2DData(const char* rootName, const char* histName, int ibinx, int ibiny);
 virtual void Input2DData(const char* rootName, const char* histName1, const char* histName2, int ibin, int iflag = 1);
 virtual void Input3DData(const char* rootName, const char* histName1);
 virtual void Input3DData(const char* rootName, const char* histName1, int ibiny, int ibinz, int iflag = 1);
 virtual void Input3DData(const char* rootName, const char* histName1, const char* histName2, int ibiny, int ibinz, int iflag = 1);
// virtual void InputData(const char* rootName1, const char* rootName2, const char* histName);
 virtual void InputTheory(vector<TString> rootNames, const char* histName);
 virtual void InputTheory(vector<TString> rootNames, const char* histName1, const char* histName2, TString Process);
 virtual void InputTheory(vector<TString> rootNames, const char* histName1, const char* histName2);
 virtual void InputTheory(vector<TString> rootNames1, vector<TString> rootNames2, const char* histName1, const char* histName2, const char* histName3);
 virtual void Input2DTheory(vector<TString> rootNames, const char* histName1);
 virtual void Input2DTheory(vector<TString> rootNames, const char* histName1, const char* histName2, TString Process);
 virtual void Input2DTheory(vector<TString> rootNames, const char* histName, int ibin);
 virtual void Input2DTheory(vector<TString> rootNames, const char* histName, int ibinx, int ibiny);
 virtual void Input2DTheory(vector<TString> rootNames, const char* histName1, const char* histName2, int ibin);
 virtual void Input3DTheory(vector<TString> rootNames, const char* histName1);
 virtual void Input3DTheory(vector<TString> rootNames, const char* histName1, int ibiny, int ibinz);
 virtual void Input3DTheory(vector<TString> rootNames, const char* histName1, const char* histName2, int ibiny, int ibinz);
 virtual void InputTheory(vector<TString> rootNames1, vector<TString> rootNames2, const char* histName);
 virtual void InputTheory(PDFUncertainty *unc);
 virtual void InputTheory(TH1D *h1, int nSet);
 virtual void InputTheory(vector<TH1D *> histos);
 virtual void Input2DTheory(PDFUncertainty *unc);
 virtual void InputExtendedTheory(TString ParaName, vector<TString> rootNames, const char* histName);
 virtual void SpecialStaError(double kFactor);
 virtual void ReweightStatistics(double lumi){isReweightStatistics = true; CustomLuminosity = lumi;};
 virtual void Normalization(int DataNormFactor = 1, int TheoryNormFactor = 1);
 virtual void writedata();
 virtual void writetheory();
 virtual void writedata(int FirstBin, int LastBin);
 virtual void writetheory(int FirstBin, int LastBin);
 virtual void write2Ddata();
 virtual void write2Dtheory();
 virtual void write3Ddata();
 virtual void write3Dtheory();
 virtual void writeExtendedtheory();
 virtual void GetDataStaError();
 virtual void SetAFB();
 virtual void SetSideband();
 virtual void Rebin(int Nbin);
 virtual void Rebin(double *rebin, int Nbin);
 virtual void RemoveSpecialBins(double left, double right);
 virtual void SkipRange(double left, double right){isSkipRange = true; SkipLeft = left; SkipRight = right;}
 virtual void SkipRange2D(double xleft, double xright, double yleft, double yright){isSkipRange = true; xSkipLeft = xleft; xSkipRight = xright; ySkipLeft = yleft; ySkipRight = yright;}
 virtual void InputStaErr(double *myStaErr);
 virtual void InputSysErr(double *mySysErr);
 virtual void InputSysErr(vector<double> mySysErr);
 virtual void InputCorrSysErr(double* myCorrSysErr, const char* CorrName);
 virtual void InputCorrSysErr(vector<double> myCorrSysErr, const char* CorrName);
 virtual void InputCorrelation(const char* rootName, const char* histName);
 virtual void InputCovarianceMatrix(const char* rootName, const char* histName);
 virtual void InputCovarianceMatrix(TH2D* matrix);
 virtual void InputCorrelation(int iflag);

 enum class KFactorType {Simple, Linear, Quadratic};
 struct OtherKFactor{
   KFactorType type;
   vector<double> parameters;
 };

 vector<vector<OtherKFactor>> OtherKFactorList;
 vector<double> FinalOtherKFactor;
 vector<double> DataOtherKFactor = {};
 map<int, vector<double>> TheoryOtherKFactor;

 virtual void InputOtherKFactor(TString path);
 virtual void ApplyOtherKFactor(int index, vector<double> zVec);

 virtual void End();
};
#endif
