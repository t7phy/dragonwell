#ifndef Tools_h
#define Tools_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TMath.h"
#include "Math/QuantFuncMathCore.h"
#include "Math/ProbFunc.h"
#include "TH1F.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
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
#include "TH2D.h"
#include "TH3D.h"
#include "TGraph.h"
#include "TF1.h"
#include "TLegend.h"
#include <TProfile.h>
#include "TH1D.h"
#include "TString.h"
#include <pthread.h>
#include "TMatrixD.h"
#include "TMatrixDEigen.h"
#include "TDecompSVD.h"
#include "SpecialHist/MultiBinHist.h"
#include "Tools/Integral.h"

using namespace std;

double calculate_theta(TLorentzVector Zboson, TLorentzVector Electron, TLorentzVector Positron);
double calculate_phi(TLorentzVector Electron, TLorentzVector Positron, double myECM);
double calculate_phi_eta(TLorentzVector Electron, TLorentzVector Positron);
double CalculateTransverseMass(TLorentzVector Lepton, TLorentzVector nu);
double CalculateRMS(double* num);
double CalculateRMS(vector<double> num);
double CalculateMean(double* num);
double CalculateMean(vector<double> num);
double CalculateMean(vector<double> num, vector<double> error, double &meanError);
double CalculateMean(vector<double> num, vector<double> error, vector<double> width, double &meanError);

void AFBFunction(TH1D* FZmass, TH1D* BZmass, TH1D* &Draw_AFB);
void AFBFunction(TH2D* FZmass, TH2D* BZmass, TH2D* &Draw_AFB);
void AFBFunction(TH3D* FZmass, TH3D* BZmass, TH3D* &Draw_AFB);
void GetAFBDiff(TH1D* AFB, TH1D* &AFBDiff);
void GetAFBDiff(TH1D* AFB, TH1D* &AFBDiff, TH1D* &AFBDiff_ZPole, TH1D* &AFBDiff_Side);
void GetAFBDiff(TH2D* AFB, TH2D* &AFBDiff);
void GetAFBSlopeAndOffset(TH2D* AFB, TH1D* &AFBSlope, TH1D* &AFBOffset);
void GetAFBAve(TH1D* AFB, TH1D* &AFBAve);
void AFBFraction(TH1D* uuAFB, TH1D* ddAFB, vector<TH1D *> Xsec, TH1D* &Fraction);
void AFBS0Fraction(TH1D* uuAFB, TH1D* ddAFB, vector<TH1D *> Xsec, TH1D* &Fraction);
void AFBS0Fraction(TH2D* uuAFB, TH2D* ddAFB, vector<TH2D *> Xsec, TH2D* &Fraction);
void AFBFunction(TH2D* FZmass, TH2D* BZmass, TH1D* &Draw_AFB);
void AFBFunction(TH3D* FZmass, TH3D* BZmass, TH1D* &Draw_AFB);
void ApplyS0(TH1D* DeltaD, TH1D* &Dilution, double S0, double S0Error);
void ApplyS0(TH2D* DeltaD, TH2D* &Dilution, double S0, double S0Error);
void ApplyS0(TH2D* DeltaD, TH2D* &Dilution, TH1D* S0);
void ApplyDelta(TH1D* Dilution_MC, TH1D* &Dilution_Data, double Delta);
void ApplyDilution(TH1D* &FZmass, TH1D* &BZmass, TH1D* FDilution, TH1D* BDilution);
void ApplyDilution(TH1D* &FZmass, TH1D* &BZmass, TH1D* Dilution, bool isGG = false);
void Apply2DDilution(TH2D* &FZmass, TH2D* &BZmass, TH2D* Dilution, bool isGG = false, double S0 = 0.0);
void Apply2DDilutionNY(TH2D* &FZmass, TH2D* &BZmass, TH2D* Dilution, bool isGG = false, vector<double> S0 = {});
void Apply3DDilution(TH3D* &FZmass, TH3D* &BZmass, TH3D* Dilution);
void GetAFBDilution(TH1D* Dilution, TH1D* &AFBDilution);
void GetXsecFraction(TH1D *Numer, vector<TH1D *> Denom, TH1D* &Fraction);
void GetCoefficientDilution(TH1D* Dilution, TH1D* Fraction, TH1D* &CoefficientDilution);
void GetCoefficientDilution(TH1D* wrong, TH1D* total, TH1D* all, TH1D* &CoefficientDilution);
void GetCoefficientDilution(TH3D* wrong, TH3D* total, TH3D* all, TH3D* &CoefficientDilution);
void GetDilutionAverage(TH1D* Dilution, TH1D* &DilutionAverage, TH1D* &Residual);
void GetDilutionAverage(TH3D* Dilution, TH3D* &DilutionAverage, TH3D* &Residual);
void GetDilutionMeta(TH1D* wrong, TH1D* total, TH1D* all, TH1D* &OneMinusTwoD, TH1D* &RelativeCrossSection);
void GetDilutionMeta(TH3D* wrong, TH3D* total, TH3D* all, TH3D* &OneMinusTwoD, TH3D* &RelativeCrossSection);
void GetHadronAFB(TH1D* AFB_uu, TH1D* AFB_dd, TH1D* Dilution_uu, TH1D* Dilution_dd, TH1D* &AFB);
void GetHadronAFB(TH1D* AFB_uu, TH1D* AFB_dd, TH1D* Delta_uu, TH1D* Delta_dd, double P0u, double P0d, TH1D* &AFB);

void GetWasymmetry(TH1D* AntiLeptonEta, TH1D* LeptonEta, TH1D* &plot_Wasymmetry);
void CalRefWZ(TH1D* Wplus, TH1D* Wminus, TH1D* Z, TH1D* &WZRef);
void SmearHist(TH1D* h1, double* smear);
void Smear2DHist(TH2D* h1, vector<vector<double>> smear);
void Smear3DHist(TH3D* &h1);
void GenGausRandomList(double mean, double rms, vector<double>& list, int length);
void RowExchange(int i, int j, TH2D* &Matrix);
void RowTransform(int i, int j, double scale, TH2D* &Matrix);
void RowScale(int i, double scale, TH2D* &Matrix);
void CalculateInverseMatrix(TH2D* Matrix, TH2D* &InverseMatrix);
void RowExchange(int i, int j, vector<vector<double>> &Matrix);
void RowTransform(int i, int j, double scale, vector<vector<double>> &Matrix);
void RowScale(int i, double scale, vector<vector<double>> &Matrix);
void CalculateInverseMatrix(vector<vector<double>> Matrix, vector<vector<double>> &InverseMatrix);

double CalculateChi2(TH1D* h1, TH1D* h2);
double CalculateChi2(TH2D* h1, TH2D* h2);
double CalculateChi2(TH3D* h1, TH3D* h2);
double CalculateChi2(TH1D* h1, TH1D* h2, TH2D* CovarianceMatrix);
double CalculateChi2WithData(TH1D* h1, TH1D* h2);
double CalculateChi2(TH1D* h1, TH1D* h2, int FirstBin, int LastBin);
double CalculateChi2(TH3D* h1, TH3D* h2, int FirstYBin, int LastYBin, int FirstZBin, int LastZBin);
double CalculateLLH(TH1D* Data, TH1D* MC);
double CalculateLLH(TH1D* Data, TH1D* MC, vector<double> DataFactorial);
double TranslateChi2ToPValue(double chi2, int ndf);
double TranslateChi2ToSpartyness(double chi2, int ndf);
double TLewisChi2(double S, int Npts);
double TranslateGaussSigmaToPValue(double sigma);
double TranslateChi2ToGaussSigma(double chi2, int ndf);
double TranslatePValueToZ(double PValue);
double CalLogFactorial(double x);
double CalculateNormChi2(TH1D* h1, TH1D* h2);
double CalculateNormChi2(TH1D* h1, TH1D* h2, int FirstBin, int LastBin);
double CalculateChi2(TH1D* Theory, TH1D* Data, TH1D* StaErr, TH1D* SysErr, vector<TH1D*> CorrErr);

double CalculateCovariance(vector<double> X, double Xmean, vector<double> Y, double Ymean);

void Chi2Fitting(TH1D* h1, TF1* &fitting);
void Chi2Fitting(TH1D* h1, TF1* &fitting, double &stwResult, double &stwResultErr);
void Chi2Fitting(TH1D* h1, TF1* &fitting, double &stwResult, double &stwResultErr, double chi2);
double Chi2Solution(vector<double> X, vector<double> Y, double Tol = 0.0);
void LinearFitting(TH1D* h1, TF1* &fitting, double* &ResultsPar, double* &ResultsParErr);
void FunctionFitting(TH1D* h1, TF1* &fitting, TString Function, double* &ResultsPar, double* &ResultsParErr, int NPar, double AddedScale = 1.0);

void StaticFitting(void(*fcn)(Int_t &, Double_t *, Double_t &f, Double_t *, Int_t), vector<TString> ParNames, vector<double> ParCenters, vector<double> ParSteps, vector<double> ParLowers, vector<double> ParUppers);

//vector
double DeltaPhi(double Phi1, double Phi2);
double CosPhi(vector<double> v1, vector<double> v2);

void RowTransform0(int i, double scale, int j, TH2D *matrix);
void RowScale0(int i, double scale, TH2D *matrix);
void ReverseMatrix(TH2D *matrix, TH2D *reverse);
void MatrixDotVector(TH2D *matrix, TH1D *vec, TH1D *result);
void SolveLinearEquation(TH2D *A, TH1D *X, TH1D *B);
void VectorDotVector(TH1D *vec1, TH1D *vec2, double &result);
void VectorDotVector(TH1D *vec1, TH1D *vec2, TH2D *result);
void SearchEigenVector(TH2D *matrix, double &val, TH1D *vec, double lim);
void SearchAllEigenVector(TH2D *matrix, double *val, TH1D **vec, double lim);

double CalculateCosThetaV(TLorentzVector WBoson_lab, TLorentzVector ZBoson_lab);
double CalculateCosThetaLepW(TLorentzVector WBoson_lab, TLorentzVector ZBoson_lab, TLorentzVector WLepton_lab);
double CalculateCosThetaLepZ(TLorentzVector WBoson_lab, TLorentzVector ZBoson_lab, TLorentzVector ZLepton_lab);
double CalculateDY_WZ(TLorentzVector WBoson_lab, TLorentzVector ZBoson_lab);
double CalculateDY_3Z(TLorentzVector ZBoson_lab, TLorentzVector WLepton_lab);
double CalculateDY_3N(TLorentzVector ZLepton_lab, TLorentzVector WLepton_lab);
double CalculateNeutrinoPz(TLorentzVector Lepton, TLorentzVector Neutrino, double WMass);
double CalculateNeutrinoPz_Eta(TLorentzVector Lepton, TLorentzVector Neutrino, double WMass, int Charge);
pair<double, int> CalculateNeutrinoPz_Eta2(TLorentzVector Lepton, TLorentzVector Neutrino, double WMass, int Charge);
double CosAngle_W_WZ_lab(TLorentzVector W_lep, TLorentzVector W_Nu, TLorentzVector Z_lep_minus, TLorentzVector Z_lep_plus);
double CalculateDeltaPhiLepWLepZ(TLorentzVector ZLepton_lab, TLorentzVector WLepton_lab);
double CalculateDeltaPhiLepWLepZWZFrame(TLorentzVector ZLepton_lab, TLorentzVector WLepton_lab, TLorentzVector WZPropagator_lab);
double CalculateR21(TLorentzVector ZBoson_lab, TLorentzVector WBoson_lab);

double GetCrossSection(int mcChannelNumber);
double GetRunLuminosity(int runNumber);

//HistHelper
void InverseHistXaxis(TH1D *h1, TH1D* &inverse_h1);
void InverseHistXaxis(TH2D *h1, TH2D* &inverse_h1);
void ConstructTH2D(vector<TH1D *> hists, TH2D* &h2, double* BinningY);
void ConstructTH2D(vector<TH1D *> hists, TH2D* &h2, int nbiny);
TH1D* GenPseudodata(double lumi, TH1D* h1, TString subName = "Pseudodata", int seed = 0, bool isNorm = false);
TH1D* GenPseudodataNoFluc(double lumi, TH1D* h1, TString subName = "Pseudodata", int seed = 0, bool isNorm = false);
TH2D* GenPseudodata(double lumi, TH2D* h1, TString subName = "Pseudodata", int seed = 0, bool isNorm = false);
TH2D* GenPseudodataNoFluc(double lumi, TH2D* h1, TString subName = "Pseudodata", int seed = 0, bool isNorm = false);
TH3D* GenPseudodata(double lumi, TH3D* h1, TString subName = "Pseudodata", int seed = 0, bool isNorm = false);
TH3D* GenPseudodataNoFluc(double lumi, TH3D* h1, TString subName = "Pseudodata", int seed = 0, bool isNorm = false);
void HistDivideBinWidth(TH1D* h1, TH1D* &h1Past);
void HistDivideBinWidth(TH2D* h1, TH2D* &h1Past, TString flag);
void HistDivideBinWidth(TH3D* h1, TH3D* &h1Past, TString flag);
void HistDivideBinWidth(TH1D* h1, TH1D* &h1Past, double add_factor);
vector<double> GetHistBinning(TH1D* h);
void ApplyKFactorToHist(TH1D* Origin, TH1D* KFactor, TH1D* &HighOrder, double Cut);
void DecompositeTH3DtoTH1D(vector<TH3D *> Input, vector<vector<TH1D *>> &Output);
void DivideHist(TH1D* h1, TH1D* h2, TH1D* &Ratio);
TH1D* HistExtend(vector<TH1D *> hists);

void ChangeHistPercentErr(TH1D* &h1, double percent, TString type);

void TemplateFitting(TString TemplatesName, TString DataName, TString VariableName, double left, double right, double step);
void TemplateFittingNorm(TString TemplatesName, TString DataName, TString VariableName, double left, double right, double step, int FirstBin = -1, int LastBin = -1);
void TemplateFittingNorm(TString TemplatesName, TString DataName, TString VariableName, TString DataVariableName, double left, double right, double step, int FirstBin = -1, int LastBin = -1);

//SimpleUncertainty.C
double DivideUncertainty(TH1D* h1, TH1D* h2, int bin);
double DivideUncertainty(double Value1, double Value2, double Error1, double Error2);// A/B
double DivideUncertainty2(double Value1, double Value2, double Error1, double Error2);// (A-B)/A
double EfficiencyUncertainty(double Value1, double Value2, double Error1, double Error2);// A/(A+B)

double Simpson(double(*fcn)(double), double left, double right);
double SimpsonLog10(double(*fcn)(double), double left, double right);
template<typename T>
double Simpson(T *t, double(T::*fcn)(double), double left, double right);
double Simpson(std::function<double(double)> fcn, double left, double right, int ncall, double step, bool isOutput);
double SimpsonLog10(std::function<double(double)> fcn, double left, double right, int ncall, double step, bool isOutput);

//Draw Ellipse
TGraph* GenerateEllipse(double X0, double Y0, double DeltaX, double DeltaY, double cosphi);

//PartonCorrelation
void DrawPartonCorrelation(vector<TH1D *> Variable1, TH2D* &Correlation, TString ErrorType);
void DrawCorrelationCosine(vector<TH1D *> OneNumber, vector<TH1D *> h1, TH1D* &CorrHist, TString ErrorType, int BinLeft = -1, int BinRight = -1);
void DrawIntegralCorrelationCosine(vector<TH1D *> OneNumber, vector<TH1D *> h1, TH1D* &CorrHist, TString ErrorType);
void Draw1DCorrelationCosine(vector<TH1D *> h1, vector<TH1D *> h2, vector<TH1D *> &CorrHist, TString ErrorType);
void Draw2DCorrelationCosine(vector<TH2D *> h1, vector<TH1D *> h2, vector<vector<TH1D *>> &CorrHist, TString ErrorType);

//ResBos Function copy
double ResBosRandom(int iseed);

//String Helper
void TrimString(std::string &s);
bool isInteger(const std::string &str);
bool isFloat(const std::string &str);
std::vector<std::string> Tokenizestring(std::string line, std::string delimiters = " \t", std::string commentString = "", bool KeepQuote = false);
std::vector<TString> Str2Tok(TString str, TString delimiters = " \t", TString CommentString = "", bool KeepQuote = false);
std::vector<std::vector<TString>> GetLinesTokenized(vector<TString> FullFile, TString BeginTag, TString EndTag, bool RemoveEmptyLine, bool RemoveTag, TString Delimiter, TString CommentString);
std::map<TString, std::vector<TString>> ListAnalyzer(const std::vector<std::vector<TString>> &VectorList);

//Utility
std::vector<double> Logspace(double start, double stop, size_t num = 50, double base = 10.0);
std::vector<double> CenterToBinning(std::vector<double> Q);

//Matrix decomposition
void Decomposition(vector<double> DATA, TMatrixD input);

//SMEFT Parameterization
void ParameterizeFunc(vector<vector<double>> &hists, vector<TH1D *> &outhists, vector<TF1 *> &funcs, vector<TString> names, double BinLeft, double BinRight);
void ParameterizeAFBFunc(vector<vector<double>> &hists, vector<TH1D *> &outhists, TH1D* SM_F, TH1D* SM_B, vector<TF1 *> &funcsF, vector<TF1 *> &funcsB, vector<TF1 *> &funcs, vector<TString> names, double BinLeft, double BinRight);

//Unfolding
TH1D* IterativeBayesianUnfold(const TH1D* measured, const TH2D* response, int nIterations);

string getTime();

#endif
