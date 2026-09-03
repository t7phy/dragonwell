#ifndef PDFHelper_WWProduction_h
#define PDFHelper_WWProduction_h

#include "PDFHelper/PDFHelper.h"

using namespace std;

class WWProduction : public PDFHelper
{
 public:

 double QuarkMass[6] = {0.0, 0.0, 0.0, 0.0, 1.3, 4.75};
 double QuarkCharge[6] = {0.0};
 double I3Q[6] = {0.0};

 double stw = 0.2315;
 double WMass = 80.385;
 double ZMass = 91.1876;

 double alphaEM0 = 0.00729735;
 double alphaEMMz = 0.007763340902;

 int iWWMass = 0;
 TH1D *WWMassPlot[1000];

 int iWWQuarkMass = 0;
 TH1D *WWQuarkMassPlot[1000];

 int iBoostAsymmetry = 0;
 TH1D *BoostAsymmetryPlot[1000];

 WWProduction();

 virtual void DrawWWMass(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawWWQuarkMass(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");
 virtual void DrawBoostAsymmetry(int bin, double left, double right, int iflag = 0, TString Process = "NoIntegral");

 virtual double CalT(int i, double Q, double Y0);
 virtual double CalU(int i, double Q, double Y0);
 virtual double Omega(double x);
 virtual double CalA(int i, double Q, double Y0);
 virtual double CalIstu(int i, double Q, double Y0);
 virtual double CalIsut(int i, double Q, double Y0);
 virtual double CalEstu(int i, double Q, double Y0);
 virtual double CalEsut(int i, double Q, double Y0);
 virtual double WWCrossSection(int i, double Q, double Y0);

 virtual double WWHadronCrossSectiony(double y, int i, double Q, double Y0);
 virtual double WWHadronCrossSectionY0(double y, int i, double Q, double Y0);
 virtual double WWQuarkCrossSectionY0Q(double Y0, int i, double Q);
 virtual double WWHadronCrossSectionY0Q(double Y0, int flavor, double Q);
 virtual double WWHadronCrossSectionQ(double Q, int flavor);
 virtual double WWQuarkCrossSectionQ(double Q, int flavor);
 virtual double IntegralWWHadronCrossSectionQ(double left, double right, int flavor);
 virtual double IntegralWWQuarkCrossSectionQ(double left, double right, int flavor);
 virtual double BoostCrossSection(double Q, double Delta, int flavor, TString rest);
 virtual double BoostCrossSectionTerm1(double Q, double Delta, int flavor, TString rest);
 virtual double BoostCrossSectionTerm2(double Q, double Delta, int flavor, TString rest);
 virtual double BoostCrossSectionTerm3(double Q, double Delta, int flavor, TString rest);
 virtual double BoostCrossSectionTerm4(double Q, double Delta, int flavor, TString rest);
 virtual double TotalBoostCrossSection(double Delta, int flavor);
 virtual double IntegralBoostCrossSection(double left, double right, int flavor);

};
#endif
