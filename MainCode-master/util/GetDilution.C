#include "PDFHelper/PDFReweight.h"
#include "Uncertainty/PDFUncertainty.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "RootCommon.h"

int main(int argc, char** argv)
{
 double rangeMass[31] = {60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120};
 double rangeZY[4] = {0.0, 1.0, 2.0, 5.0};
// double rangeZY[2] = {0.0, 5.0};

 PDFReweight *data = new PDFReweight();
 data->openFile("Dilution.root");
// data->InitialPDF("CT18NNLO", 0);
// data->InputPDFnSet(58);
// data->InitialPDFReweightFactor("CT18NNLO", "CT18NNLO", 0, 10);
// data->InitialPDF("MSHT20nnlo_as118", 0);
 data->InitialPDF("i2Tn3sa46_LHA", 2);
// data->InputPDFnSet(64);

 vector<double> XVector;

 for(int i = 0; i < 100; i++){
   XVector.push_back(pow(10, (5.0 / 3.0) * log10((i + 1) / 100.0)));
   //cout<<XVector.at(i)<<endl;
 }

 for(int i = 0; i < XVector.size(); i++){
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<"x: "<<XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" c:"<<data->Getf(4, XVector.at(i), 100.0);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" cbar:"<<data->Getf(-4, XVector.at(i), 100.0);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" s:"<<data->Getf(3, XVector.at(i), 100.0);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" sbar:"<<data->Getf(-3, XVector.at(i), 100.0);
   cout<<endl;
 }

// data->OutputePumpFile("HadronAFB", "HadronAFB", 1, 80, 100, 0, "NoIntegral");

// data->DrawPartonCorrelation(1, 12, 58, "Symmetry");

// cout<<data->GetPDFReweightFactor(2, -2, 0.092177000, 0.00060084615, 92.948382)<<endl;
/* data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_u", 35, 60, 130, 2, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_d", 35, 60, 130, 1, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_s", 35, 60, 130, 3, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_c", 35, 60, 130, 4, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_b", 35, 60, 130, 5, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_ubar", 35, 60, 130, -2, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_dbar", 35, 60, 130, -1, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_sbar", 35, 60, 130, -3, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_cbar", 35, 60, 130, -4, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_bbar", 35, 60, 130, -5, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_uv", 35, 60, 130, 20, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_dv", 35, 60, 130, 10, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_ubouv", 35, 60, 130, 200, "NoIntegral");
 data->OutputePumpFile("RelativePartonDensity", "RelativePartonDensity_dbodv", 35, 60, 130, 100, "NoIntegral");
*/

/* cout<<"0.0001 u:"<<data->Getf(2, 0.0001, 90)<<" ubar:"<<data->Getf(-2, 0.0001, 90)<<" s:"<<data->Getf(3, 0.0001, 90)<<endl;
 cout<<"0.0002 u:"<<data->Getf(2, 0.0002, 90)<<" ubar:"<<data->Getf(-2, 0.0002, 90)<<" s:"<<data->Getf(3, 0.0002, 90)<<endl;
 cout<<"0.0003 u:"<<data->Getf(2, 0.0003, 90)<<" ubar:"<<data->Getf(-2, 0.0003, 90)<<" s:"<<data->Getf(3, 0.0003, 90)<<endl;
 cout<<"0.0004 u:"<<data->Getf(2, 0.0004, 90)<<" ubar:"<<data->Getf(-2, 0.0004, 90)<<" s:"<<data->Getf(3, 0.0004, 90)<<endl;
 cout<<"0.0005 u:"<<data->Getf(2, 0.0005, 90)<<" ubar:"<<data->Getf(-2, 0.0005, 90)<<" s:"<<data->Getf(3, 0.0005, 90)<<endl;
 cout<<"0.0006 u:"<<data->Getf(2, 0.0006, 90)<<" ubar:"<<data->Getf(-2, 0.0006, 90)<<" s:"<<data->Getf(3, 0.0006, 90)<<endl;
 cout<<"0.0007 u:"<<data->Getf(2, 0.0007, 90)<<" ubar:"<<data->Getf(-2, 0.0007, 90)<<" s:"<<data->Getf(3, 0.0007, 90)<<endl;
 cout<<"0.0008 u:"<<data->Getf(2, 0.0008, 90)<<" ubar:"<<data->Getf(-2, 0.0008, 90)<<" s:"<<data->Getf(3, 0.0008, 90)<<endl;
 cout<<"0.0009 u:"<<data->Getf(2, 0.0009, 90)<<" ubar:"<<data->Getf(-2, 0.0009, 90)<<" s:"<<data->Getf(3, 0.0009, 90)<<endl;
 cout<<"0.001  u:"<<data->Getf(2, 0.001, 90)<<" ubar:"<<data->Getf(-2, 0.001, 90)<<" s:"<<data->Getf(3, 0.001, 90)<<endl;
 cout<<"0.002  u:"<<data->Getf(2, 0.002, 90)<<" ubar:"<<data->Getf(-2, 0.002, 90)<<" s:"<<data->Getf(3, 0.002, 90)<<endl;
 cout<<"0.003  u:"<<data->Getf(2, 0.003, 90)<<" ubar:"<<data->Getf(-2, 0.003, 90)<<" s:"<<data->Getf(3, 0.003, 90)<<endl;
 cout<<"0.004  u:"<<data->Getf(2, 0.004, 90)<<" ubar:"<<data->Getf(-2, 0.004, 90)<<" s:"<<data->Getf(3, 0.004, 90)<<endl;
 cout<<"0.005  u:"<<data->Getf(2, 0.005, 90)<<" ubar:"<<data->Getf(-2, 0.005, 90)<<" s:"<<data->Getf(3, 0.005, 90)<<endl;
 cout<<"0.006  u:"<<data->Getf(2, 0.006, 90)<<" ubar:"<<data->Getf(-2, 0.006, 90)<<" s:"<<data->Getf(3, 0.006, 90)<<endl;
 cout<<"0.007  u:"<<data->Getf(2, 0.007, 90)<<" ubar:"<<data->Getf(-2, 0.007, 90)<<" s:"<<data->Getf(3, 0.007, 90)<<endl;
 cout<<"0.008  u:"<<data->Getf(2, 0.008, 90)<<" ubar:"<<data->Getf(-2, 0.008, 90)<<" s:"<<data->Getf(3, 0.008, 90)<<endl;
 cout<<"0.009  u:"<<data->Getf(2, 0.009, 90)<<" ubar:"<<data->Getf(-2, 0.009, 90)<<" s:"<<data->Getf(3, 0.009, 90)<<endl;
 cout<<"0.01  u:"<<data->Getf(2, 0.01, 90)<<" ubar:"<<data->Getf(-2, 0.01, 90)<<" s:"<<data->Getf(3, 0.001, 90)<<endl;
 cout<<"0.02  u:"<<data->Getf(2, 0.02, 90)<<" ubar:"<<data->Getf(-2, 0.02, 90)<<" s:"<<data->Getf(3, 0.002, 90)<<endl;
 cout<<"0.03  u:"<<data->Getf(2, 0.03, 90)<<" ubar:"<<data->Getf(-2, 0.03, 90)<<" s:"<<data->Getf(3, 0.003, 90)<<endl;
 cout<<"0.04  u:"<<data->Getf(2, 0.04, 90)<<" ubar:"<<data->Getf(-2, 0.04, 90)<<" s:"<<data->Getf(3, 0.004, 90)<<endl;
 cout<<"0.05  u:"<<data->Getf(2, 0.05, 90)<<" ubar:"<<data->Getf(-2, 0.05, 90)<<" s:"<<data->Getf(3, 0.005, 90)<<endl;
*/


/* cout<<"uu: "<<data->GetTotalCrossSection(60, 130, 1)<<endl;
 cout<<"dd: "<<data->GetTotalCrossSection(60, 130, 2)<<endl;

 cout<<"uu: "<<data->GetTotalCrossSection(0, 60, 1)<<endl;
 cout<<"dd: "<<data->GetTotalCrossSection(0, 60, 2)<<endl;

 cout<<"uu: "<<data->GetTotalCrossSection(130, 300, 1)<<endl;
 cout<<"dd: "<<data->GetTotalCrossSection(130, 300, 2)<<endl;

 cout<<"Total: "<<data->GetHadronTotalCrossSection(60, 130, 0)<<endl;

// data->DrawDilutionZY(100, 0, 5, 0, "Integral");

 cout<<"u: "<<data->PDFIntegral(90, 2)<<endl;
 cout<<"d: "<<data->PDFIntegral(90, 1)<<endl;
 cout<<"s: "<<data->PDFIntegral(90, 3)<<endl;
 cout<<"c: "<<data->PDFIntegral(90, 4)<<endl;
 cout<<"b: "<<data->PDFIntegral(90, 5)<<endl;
 cout<<"ubar: "<<data->PDFIntegral(90, -2)<<endl;
 cout<<"dbar: "<<data->PDFIntegral(90, -1)<<endl;
 cout<<"sbar: "<<data->PDFIntegral(90, -3)<<endl;
 cout<<"cbar: "<<data->PDFIntegral(90, -4)<<endl;
 cout<<"bbar: "<<data->PDFIntegral(90, -5)<<endl;

 cout<<endl;
 cout<<"u: "<<data->Getf(2, 0.0001, 90)<<endl;
 cout<<"d: "<<data->Getf(1, 0.0001, 90)<<endl;
 cout<<"ubar: "<<data->Getf(-2, 0.0001, 90)<<endl;
 cout<<"dbar: "<<data->Getf(-1, 0.0001, 90)<<endl;
*/

/* TH2D* uuDilutionMassZY[57];
 vector<TH2D *> uuDilutionMassZYs;
 for(int i = 0; i < 57; i++){
   data->InitialPDF("CT14HERA2NNLO", i);
   data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
   data->RetrieveHist(uuDilutionMassZY[i], "DilutionMassZY", i + 1);
   uuDilutionMassZYs.push_back(uuDilutionMassZY[i]);
 }

 TH2D *Error_uu;
 PDFUncertainty *unc_uu = new PDFUncertainty();
 unc_uu->Input2DPlot("Symmetry", uuDilutionMassZYs, Error_uu);

 FileForEPUMP *file_uu = new FileForEPUMP("uuDilutionMassZY");
 file_uu->Input2DTheory(unc_uu);
 file_uu->write2Dtheory();

 TH2D* ddDilutionMassZY[57];
 vector<TH2D *> ddDilutionMassZYs;
 for(int i = 0; i < 57; i++){
   data->InitialPDF("CT14HERA2NNLO", i);
   data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");
   data->RetrieveHist(ddDilutionMassZY[i], "DilutionMassZY", i + 58);
   ddDilutionMassZYs.push_back(ddDilutionMassZY[i]);
 }

 TH2D *Error_dd;
 PDFUncertainty *unc_dd = new PDFUncertainty();
 unc_dd->Input2DPlot("Symmetry", ddDilutionMassZYs, Error_dd);

 FileForEPUMP *file_dd = new FileForEPUMP("ddDilutionMassZY");
 file_dd->Input2DTheory(unc_dd);
 file_dd->write2Dtheory();
*/

/* data->OutputePumpFile("AFBDilutionMass", "uuDilution", 35, 60, 130, 4, "NoIntegral");
 data->OutputePumpFile("XsecFraction", "uuFractionMass", 35, 60, 130, 20, "NoIntegral");
 data->OutputePumpFile("AFBDilutionTimesFraction", "uuDilutionTimesFraction", 35, 60, 130, 4, "NoIntegral");
 data->OutputePumpFile("AFBDilutionMass", "ddDilution", 35, 60, 130, 5, "NoIntegral");
 data->OutputePumpFile("XsecFraction", "ddFractionMass", 35, 60, 130, 10, "NoIntegral");
 data->OutputePumpFile("AFBDilutionTimesFraction", "ddDilutionTimesFraction", 35, 60, 130, 5, "NoIntegral");
*/

/* data->InitialPDF("AFB_Full_60_130_2GeV_RotatedCT14HERA2", 0);
 data->InputPDFnSet(4);
 data->OutputePumpFile("XsecDiff", "XsecDiff", 35, 60, 130, 0, "NoIntegral");
 data->OutputePumpFile("DilutionMass", "uuDilution", 35, 60, 130, 4, "NoIntegral");
 data->OutputePumpFile("DilutionMass", "ddDilution", 35, 60, 130, 5, "NoIntegral");
 data->OutputePumpFile("HadronAFB", "HadronAFB", 35, 60, 130, 0, "NoIntegral");
*/

// data->DrawQuarkAFB(30, 60, 120, 1, "Integral");
// data->DrawQuarkAFB(30, 60, 120, 2, "Integral");
// data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");

// data->DrawDilutionZY(20, -5, 5, 1, "Integral");
// data->DrawDilutionZY(20, -5, 5, 2, "Integral");


//  double Forward = data->HadronCrossSection(93.957252464284110, 7, (TString)"");

//   data->DrawDilutionMass(35, 60, 130, 1, "NoIntegral");
//   data->DrawDilutionMass(35, 60, 130, 2, "NoIntegral");
//   data->GetAFBDilutionMass(1);
//   data->GetAFBDilutionMass(2);
//   data->DrawMass(35, 60, 130, 0, "NoIntegral");
//   data->DrawMass(35, 60, 130, 1, "NoIntegral");
//   data->DrawMass(35, 60, 130, 2, "NoIntegral");
//   data->DrawXsecFraction(35, 60, 130, 1, "NoIntegral");
//   data->DrawQuarkAFB(35, 60, 130, 1, "NoIntegral");
//   data->DrawQuarkAFB(35, 60, 130, 2, "NoIntegral");

// Error_uuXsecFraction->Write();

// data->DrawDilutionMass(30, 60, 120, 3, "Integral");

// data->InputMUF(2.0);
// data->DrawDilutionMass(30, 60, 120, 3, "Integral");

// data->DrawXsecFraction(30, 60, 120, 1, "Integral");
// data->DrawXsecFraction(30, 60, 120, 2, "Integral");
// data->DrawXsecFraction(30, 60, 120, 3, "Integral");
// data->DrawXsecFraction(30, 60, 120, 4, "Integral");
// data->DrawXsecFraction(30, 60, 120, 5, "Integral");
// data->DrawS0Fraction(15, 0, 30, "NoIntegral");
// data->DrawRf(30, 60, 120, 1, "NoIntegral");
// data->DrawRf(30, 60, 120, 2, "NoIntegral");
// data->DrawRf(30, 60, 120, 3, "NoIntegral");
// data->DrawRf(30, 60, 120, 4, "NoIntegral");
// data->DrawRf(30, 60, 120, 5, "NoIntegral");

/*
// data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
// data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");
 data->DrawDilutionMass(30, 60, 120, 4, "Integral");
 data->DrawDilutionMass(30, 60, 120, 5, "Integral");
 data->DrawDilutionMass(30, 60, 120, 6, "Integral");

 data->InitialPDF("uuDilutionMassZY_RotatedCT14HERA2", 1);

 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");

 data->InitialPDF("uuDilutionMassZY_RotatedCT14HERA2", 2);

 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");

 data->InitialPDF("ddDilutionMassZY_RotatedCT14HERA2", 1);

 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");

 data->InitialPDF("ddDilutionMassZY_RotatedCT14HERA2", 2);

 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");

 data->InitialPDF("uuDilutionMass_RotatedCT14HERA2", 1);

 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");
 data->DrawDilutionMass(30, 60, 120, 4, "Integral");
 data->DrawDilutionMass(30, 60, 120, 5, "Integral");
 data->DrawDilutionMass(30, 60, 120, 6, "Integral");

 data->InitialPDF("uuDilutionMass_RotatedCT14HERA2", 2);

 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");
 data->DrawDilutionMass(30, 60, 120, 4, "Integral");
 data->DrawDilutionMass(30, 60, 120, 5, "Integral");
 data->DrawDilutionMass(30, 60, 120, 6, "Integral");

 data->InitialPDF("ddDilutionMass_RotatedCT14HERA2", 1);

 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");
 data->DrawDilutionMass(30, 60, 120, 4, "Integral");
 data->DrawDilutionMass(30, 60, 120, 5, "Integral");
 data->DrawDilutionMass(30, 60, 120, 6, "Integral");

 data->InitialPDF("ddDilutionMass_RotatedCT14HERA2", 2);

 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
 data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");
 data->DrawDilutionMass(30, 60, 120, 4, "Integral");
 data->DrawDilutionMass(30, 60, 120, 5, "Integral");
 data->DrawDilutionMass(30, 60, 120, 6, "Integral");

 data->InitialPDF("DilutionDiffMass_RotatedCT14HERA2", 1);

// data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
// data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");
 data->DrawDilutionMass(30, 60, 120, 4, "Integral");
 data->DrawDilutionMass(30, 60, 120, 5, "Integral");
 data->DrawDilutionMass(30, 60, 120, 6, "Integral");

 data->InitialPDF("DilutionDiffMass_RotatedCT14HERA2", 2);
 
// data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
// data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");
 data->DrawDilutionMass(30, 60, 120, 4, "Integral");
 data->DrawDilutionMass(30, 60, 120, 5, "Integral");
 data->DrawDilutionMass(30, 60, 120, 6, "Integral");

 data->InitialPDF("MSHT20nnlo_as118", 0);

// data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
// data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");
 data->DrawDilutionMass(30, 60, 120, 4, "Integral");
 data->DrawDilutionMass(30, 60, 120, 5, "Integral");
 data->DrawDilutionMass(30, 60, 120, 6, "Integral");

 data->InitialPDF("NNPDF31_nnlo_as_0118_1000", 0);

// data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 1, "Integral");
// data->DrawDilutionMassZY(30, rangeMass, 3, rangeZY, 2, "Integral");
 data->DrawDilutionMass(30, 60, 120, 4, "Integral");
 data->DrawDilutionMass(30, 60, 120, 5, "Integral");
 data->DrawDilutionMass(30, 60, 120, 6, "Integral");
*/

/* double uuFraction = data->GetQuarkAFBFraction(60, 130, 1);
 double ddFraction = data->GetQuarkAFBFraction(60, 130, 2);
 cout<<"Ru: "<<uuFraction<<" Rd: "<<ddFraction<<endl;

 for(int i = 0; i < 30; i++){
   double uu = data->GetQuarkAFB(rangeMass[i], rangeMass[i + 1], 1);
   double dd = data->GetQuarkAFB(rangeMass[i], rangeMass[i + 1], 2);
   double uuCrossSection = data->GetHadronTotalCrossSection(rangeMass[i], rangeMass[i + 1], 10);
   double ddCrossSection = data->GetHadronTotalCrossSection(rangeMass[i], rangeMass[i + 1], 11);
   double uuValue = uuFraction * dd * ddCrossSection / (uuCrossSection + ddCrossSection);
   double ddValue = ddFraction * uu * uuCrossSection / (uuCrossSection + ddCrossSection);

   cout<<"Mass ["<<rangeMass[i]<<", "<<rangeMass[i + 1]<<"]: Ru * ddAFB = "<<uuValue<<" Rd * uuAFB = "<<ddValue<<endl;
 }
*/

/*  TH1D* AFB[100];
  data->InputStw(0.2315);
  data->DrawHadronAFB(35, 60, 130, 0, "Integral");
  data->RetrieveHist(AFB[0], "HadronAFB", 1);

  data->InputStw(0.2324);
  data->DrawHadronAFB(35, 60, 130, 0, "Integral");
  data->RetrieveHist(AFB[1], "HadronAFB", 2);

  data->InputStw(0.2345);
  data->DrawHadronAFB(35, 60, 130, 0, "Integral");
  data->RetrieveHist(AFB[2], "HadronAFB", 3);

  TH1D* AFBDelta1 = (TH1D *)AFB[0]->Clone("AFBDelta1");
  AFBDelta1->Add(AFB[1], -1);
  TH1D* AFBDelta2 = (TH1D *)AFB[0]->Clone("AFBDelta2");
  AFBDelta2->Add(AFB[2], -1);

  AFBDelta1->Write();
  AFBDelta2->Write();

  TH1D* DeltaRatio = (TH1D *)AFBDelta1->Clone("DeltaRatio");
  DeltaRatio->Divide(AFBDelta2);

  DeltaRatio->Write();


  TH1D* AFB[100];
  data->InputStw(0.2315);
  data->DrawQuarkAFB(35, 60, 130, 1, "NoIntegral");
  data->RetrieveHist(AFB[0], "QuarkAFB", 1);

  data->InputStw(0.2324);
  data->DrawQuarkAFB(35, 60, 130, 1, "NoIntegral");
  data->RetrieveHist(AFB[1], "QuarkAFB", 2);

  data->InputStw(0.2345);
  data->DrawQuarkAFB(35, 60, 130, 1, "NoIntegral");
  data->RetrieveHist(AFB[2], "QuarkAFB", 3);

  data->InputStw(0.2315);
  data->DrawQuarkAFB(35, 60, 130, 2, "NoIntegral");
  data->RetrieveHist(AFB[3], "QuarkAFB", 4);

  data->InputStw(0.2324);
  data->DrawQuarkAFB(35, 60, 130, 2, "NoIntegral");
  data->RetrieveHist(AFB[4], "QuarkAFB", 5);

  data->InputStw(0.2345);
  data->DrawQuarkAFB(35, 60, 130, 2, "NoIntegral");
  data->RetrieveHist(AFB[5], "QuarkAFB", 6);

  TH1D* uuAFBDelta1 = (TH1D *)AFB[0]->Clone("uuAFBDelta1");
  uuAFBDelta1->Add(AFB[1], -1);
  TH1D* uuAFBDelta2 = (TH1D *)AFB[0]->Clone("uuAFBDelta2");
  uuAFBDelta2->Add(AFB[2], -1);

  uuAFBDelta1->Write();
  uuAFBDelta2->Write();

  TH1D* ddAFBDelta1 = (TH1D *)AFB[3]->Clone("ddAFBDelta1");
  ddAFBDelta1->Add(AFB[4], -1);
  TH1D* ddAFBDelta2 = (TH1D *)AFB[3]->Clone("ddAFBDelta2");
  ddAFBDelta2->Add(AFB[5], -1);

  ddAFBDelta1->Write();
  ddAFBDelta2->Write();

  TH1D* uuDeltaRatio = (TH1D *)uuAFBDelta1->Clone("uuDeltaRatio");
  uuDeltaRatio->Divide(uuAFBDelta2);

  TH1D* ddDeltaRatio = (TH1D *)ddAFBDelta1->Clone("ddDeltaRatio");
  ddDeltaRatio->Divide(ddAFBDelta2);

  uuDeltaRatio->Write();
  ddDeltaRatio->Write();
*/

// data->DrawPartonCorrelation(200, 100, 56, "Symmetry");

// data->InitialPDF("MSHT20nnlo_as118", 0);
// data->DrawPartonCorrelation(200, 100, 64, "Symmetry");

// data->DrawCombinationCorrelation(1, 64);
// data->DrawCombinationCorrelation(2, 64);





 data->SaveFile();

 return 1;
}

