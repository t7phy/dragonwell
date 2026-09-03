#ifndef PDFHelper_PDFReweight_h
#define PDFHelper_PDFReweight_h

#include <iostream>
#include "PDFHelper/PDFHelper.h"
#include "ElectroweakTheory/ZWidthDep.h"
#include "ElectroweakTheory/ResBosEW.h"

using namespace std;
//using namespace LHAPDF;

class PDFReweight : public PDFHelper
{
 public:

 //1D Plot
 int iZY = 0;
 TH1D *ZYPlot[1000];

 int iMass = 0;
 TH1D *MassPlot[1000];

 int iDilutionZY = 0;
 TH1D *DilutionZYPlot[1000];

 int iDilutionMass = 0;
 TH1D *DilutionMassPlot[1000];

 int iAFBDilutionMass = 0;
 TH1D *AFBDilutionMassPlot[1000];

 int iForwardDilutionMass = 0;
 TH1D *ForwardDilutionMassPlot[1000];

 int iBackwardDilutionMass = 0;
 TH1D *BackwardDilutionMassPlot[1000];

 int iHadronAFB = 0;
 TH1D *HadronAFBPlot[1000];

 int iQuarkAFB = 0;
 TH1D *QuarkAFBPlot[1000];

 int iHadronAFBZY = 0;
 TH1D *HadronAFBZYPlot[1000];

 int iQuarkAFBZY = 0;
 TH1D *QuarkAFBZYPlot[1000];

 int iXsecFraction = 0;
 TH1D *XsecFractionPlot[1000];

 int iAFBDilutionTimesFraction = 0;
 TH1D *AFBDilutionTimesFractionPlot[1000];

 int iRf = 0;
 TH1D *RfPlot[1000];

 int iS0Fraction = 0;
 TH1D *S0FractionPlot[1000];

 int iXsecDiff = 0;
 TH1D *XsecDiffPlot[1000];

 //PDF related plot
 int iPartonCorrelation = 0;
 TH1D *PartonCorrelationPlot[1000];

 int iRelativePartonDensity = 0;
 TH1D *RelativePartonDensityPlot[1000];

 //2D Plot
 int iMassZY = 0;
 TH2D *MassZYPlot[1000];

 int iDilutionMassZY = 0;
 TH2D *DilutionMassZYPlot[1000];

 int iHadronAFBMassZY = 0;
 TH2D *HadronAFBMassZYPlot[1000];

 int iQuarkForwardMassZY = 0;
 TH2D *QuarkForwardMassZYPlot[1000];

 int iQuarkBackwardMassZY = 0;
 TH2D *QuarkBackwardMassZYPlot[1000];

 ZWidthDep *EW;
// ResBosEW *EW;

 PDFReweight();
 virtual void InputStw(double stw){EW->InputStw(stw);};

 virtual void DrawZY(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawMass(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawDilutionZY(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawDilutionMass(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void GetAFBDilutionMass(int iplot);
 virtual void DrawForwardDilutionMass(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawBackwardDilutionMass(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawHadronAFB(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawQuarkAFB(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawHadronAFBZY(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawQuarkAFBZY(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawXsecFraction(int bin, double left, double right, int iflag = 1, TString Process = "NoIntegral");
 virtual void GetAFBDilutionTimesFraction(int iDilut, int iFrac);
 virtual void DrawRf(int bin, double left, double right, int iflag = 1, TString Process = "NoIntegral");
 virtual void DrawS0Fraction(int bin, double left, double right, TString Process = "NoIntegral");
 virtual void DrawXsecDiff(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");

 virtual void DrawPartonCorrelation(int Parton1, int Parton2, int nSet, TString ErrorType = "Symmetry");
 virtual void DrawPartonCorrelation(vector<TH1D *> Variable, int Parton1, int nSet, TString ErrorType = "Symmetry");
 virtual void DrawPartonCorrelation(vector<TH1D *> Variable1, vector<TH1D *> Variable2, TGraph* &graph, TGraph* &central, TString ErrorType = "Symmetry");
 virtual void DrawPartonCorrelation(vector<TH1D *> Variable1, TH2D* &Correlation, TString ErrorType = "Symmetry");
 virtual void DrawCombinationCorrelation(int Parton1, int nSet, TString ErrorType = "Symmetry");
 virtual void DrawRelativePartonDensity(int bin, double left, double right, int iflag);


 virtual void DrawMassZY(int binx, double leftx, double rightx, int biny, double lefty, double righty, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawDilutionMassZY(int binx, double leftx, double rightx, int biny, double lefty, double righty, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawDilutionMassZY(int binx, double* xbins, int biny, double* ybins, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawHadronAFBMassZY(int binx, double leftx, double rightx, int biny, double lefty, double righty, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawQuarkForwardMassZY(int binx, double leftx, double rightx, int biny, double lefty, double righty, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawQuarkBackwardMassZY(int binx, double leftx, double rightx, int biny, double lefty, double righty, int iflag = 0, TString Process = "NoIntegral");

 virtual void RetrieveHist(TH1D* &hist, TString HistName, int i);
 virtual void RetrieveHist(TH2D* &hist, TString HistName, int i);

 virtual void GetPDFUncertainty(TString HistName, int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void OutputePumpFile(TString HistName, TString FileName, int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");

 virtual double HadronCrossSection(double mass, int iflag, TString Process = "");
 virtual double WrongHadronCrossSection(double mass, int iflag, TString Process = "");
 virtual double ZCrossSection(double mass, int iflag, TString Process = "");
 virtual double MassZYCrossSection(double Q, double ZY, int iflag, TString Process);
 virtual double MassZYCrossSectionWrong(double Q, double ZY, int iflag, TString Process);

 virtual double GetQuarkAFB(double left, double right, int iflag);
 virtual double GetQuarkAFBFraction(double left, double right, int iflag);
 virtual double GetRf(double left, double right, int iflag = 1, TString Process = "NoIntegral");

 virtual double GetTotalCrossSection(double left, double right, int iflag);
 virtual double GetForwardCrossSection(double left, double right, int iflag);
 virtual double GetBackwardCrossSection(double left, double right, int iflag);
 virtual double GetHadronTotalCrossSection(double left, double right, int iflag, TString Process = "");
 virtual double GetHadronForwardCrossSection(double left, double right, int iflag);
 virtual double GetHadronBackwardCrossSection(double left, double right, int iflag);
 virtual double GetHadronWrongCrossSection(double left, double right, int iflag, TString Process = "");
 virtual double GetZYCrossSection(double ZY, double massleft, double massright, int iflag, TString Process);
 virtual double GetZYCrossSectionWrong(double ZY, double massleft, double massright, int iflag, TString Process);
 virtual double GetMassZYCrossSection(double massleft, double massright, double zyleft, double zyright, int iflag, TString Process);
 virtual double GetMassZYCrossSectionWrong(double massleft, double massright, double zyleft, double zyright, int iflag, TString Process);


};
#endif
