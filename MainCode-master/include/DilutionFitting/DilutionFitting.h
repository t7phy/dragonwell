#ifndef DilutionFitting_DilutionFitting_h
#define DilutionFitting_DilutionFitting_h

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Uncertainty/PDFUncertainty.h"
#include "Uncertainty/FitAFBStw.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "TMinuitHelper/TMinuitHelper.h"
#include "ePumpHelper/ePumpHelper.h"
#include <iostream>

using namespace std;

map<vector<int>, TH1D *> *global_uuFittedSlopeEnsemble;
map<vector<int>, TH1D *> *global_uuFittedOffsetEnsemble;
map<vector<int>, TH1D *> *global_ddFittedSlopeEnsemble;
map<vector<int>, TH1D *> *global_ddFittedOffsetEnsemble;

map<vector<int>, TH1D *> *global_DataAFBEnsemble;
map<vector<int>, TH1D *> *global_DataPuEnsemble;
map<vector<int>, TH1D *> *global_DataPdEnsemble;
map<vector<int>, TH1D *> *global_DataDeltauEnsemble;
map<vector<int>, TH1D *> *global_DataDeltadEnsemble;
map<vector<int>, TH1D *> *global_DatauuDilutionEnsemble;
map<vector<int>, TH1D *> *global_DataddDilutionEnsemble;
map<vector<int>, TH1D *> *global_DatauuRelativeXsecEnsemble;
map<vector<int>, TH1D *> *global_DataddRelativeXsecEnsemble;

map<vector<int>, TH1D *> *global_TheoryAFBEnsemble;
map<vector<int>, TH1D *> *global_TheoryPuEnsemble;
map<vector<int>, TH1D *> *global_TheoryPdEnsemble;
map<vector<int>, TH1D *> *global_TheoryDeltauEnsemble;
map<vector<int>, TH1D *> *global_TheoryDeltadEnsemble;
map<vector<int>, TH1D *> *global_TheoryuuDilutionEnsemble;
map<vector<int>, TH1D *> *global_TheoryddDilutionEnsemble;
map<vector<int>, TH1D *> *global_TheoryuuRelativeXsecEnsemble;
map<vector<int>, TH1D *> *global_TheoryddRelativeXsecEnsemble;

map<vector<int>, TH1D *> *global_FittedAFBEnsemble_ptr;
map<vector<int>, TH1D *> global_FittedAFBEnsemble;

int global_iPDF;
int global_iZY;
int global_iQT;

double MinChi2 = 100000.0;

void udDilutionFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 double Chi2 = 0.0;

 TH1D* Dilution_uu = (TH1D *)(*global_TheoryDeltauEnsemble)[(vector<int>{global_iPDF, global_iZY, global_iQT})]->Clone("Dilution_uu");
 TH1D* Dilution_dd = (TH1D *)(*global_TheoryDeltadEnsemble)[(vector<int>{global_iPDF, global_iZY, global_iQT})]->Clone("Dilution_dd");

 for(int ibinx = 1; ibinx <= Dilution_uu->GetNbinsX(); ibinx++){
   double Value = Dilution_uu->GetBinContent(ibinx) + par[1];
   double Error = Dilution_uu->GetBinError(ibinx);
   Dilution_uu->SetBinContent(ibinx, Value);
   Dilution_uu->SetBinError(ibinx, Error);
 }

 for(int ibinx = 1; ibinx <= Dilution_dd->GetNbinsX(); ibinx++){
   double Value = Dilution_dd->GetBinContent(ibinx) + par[2];
   double Error = Dilution_dd->GetBinError(ibinx);
   Dilution_dd->SetBinContent(ibinx, Value);
   Dilution_dd->SetBinError(ibinx, Error);
 }

 TH1D* AFB = (TH1D *)(*global_DataAFBEnsemble)[(vector<int>{global_iZY, global_iQT})]->Clone("AFB_Hadron");
 AFB->Reset();

 for(int ibinx = 1; ibinx <= AFB->GetNbinsX(); ibinx++){
   double Value1 = Dilution_uu->GetBinContent(ibinx);
   double Value2 = ((*global_uuFittedSlopeEnsemble)[(vector<int>{global_iZY, global_iQT})])->GetBinContent(ibinx) * par[0] + ((*global_uuFittedOffsetEnsemble)[(vector<int>{global_iZY, global_iQT})])->GetBinContent(ibinx);

   double Value3 = Dilution_dd->GetBinContent(ibinx);
   double Value4 = ((*global_ddFittedSlopeEnsemble)[(vector<int>{global_iZY, global_iQT})])->GetBinContent(ibinx) * par[0] + ((*global_ddFittedOffsetEnsemble)[(vector<int>{global_iZY, global_iQT})])->GetBinContent(ibinx);

   double Error1 = 0.0;
   double Error2 = 0.0;
   double Error3 = 0.0;
   double Error4 = 0.0;

   double Value = Value1 * Value2 + Value3 * Value4;
   double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

   AFB->SetBinContent(ibinx, Value);
   AFB->SetBinError(ibinx, Error);
 }

 Chi2 = CalculateChi2((*global_DataAFBEnsemble)[(vector<int>{global_iZY, global_iQT})], AFB);

 f = Chi2;
 if(f < MinChi2) MinChi2 = f;

 //global_FittedAFBEnsemble[(vector<int>{global_iPDF, global_iZY, global_iQT})] = (TH1D *)AFB->Clone((TString)"FittedAFB_PDF" + (int)global_iPDF + "_ZY" + (int)global_iZY + (TString)"_QT_" + (int)global_iQT);

 delete Dilution_uu;
 delete Dilution_dd;
 delete AFB;

 cout<<"Min Chi2 = "<<MinChi2<<endl;

}

void udDilutionFittingPDF(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 double Chi2 = 0.0;

 int nSet = 58;

 vector<TH1D *> Dilution_uus(nSet);
 vector<TH1D *> Dilution_dds(nSet);
 vector<TH1D *> TheoryTemplates(nSet);
 for(int i = 0; i < nSet; i++){
   Dilution_uus.at(i) = (TH1D *)(*global_TheoryDeltauEnsemble)[(vector<int>{i, global_iZY, global_iQT})]->Clone((TString)"Dilution_uu_PDF" + (int)i);
   Dilution_dds.at(i) = (TH1D *)(*global_TheoryDeltadEnsemble)[(vector<int>{i, global_iZY, global_iQT})]->Clone((TString)"Dilution_dd_PDF" + (int)i);
   TheoryTemplates.at(i) = (TH1D *)(*global_DataAFBEnsemble)[(vector<int>{global_iZY, global_iQT})]->Clone((TString)"AFB_Hadron_PDF" + (int)i);
   TheoryTemplates.at(i)->Reset();
 }


 for(int i = 0; i < nSet; i++){
   for(int ibinx = 1; ibinx <= Dilution_uus.at(i)->GetNbinsX(); ibinx++){
     double Value = Dilution_uus.at(i)->GetBinContent(ibinx) + par[1];
     double Error = Dilution_uus.at(i)->GetBinError(ibinx);
     Dilution_uus.at(i)->SetBinContent(ibinx, Value);
     Dilution_uus.at(i)->SetBinError(ibinx, Error);
   }

   for(int ibinx = 1; ibinx <= Dilution_dds.at(i)->GetNbinsX(); ibinx++){
     double Value = Dilution_dds.at(i)->GetBinContent(ibinx) + par[2];
     double Error = Dilution_dds.at(i)->GetBinError(ibinx);
     Dilution_dds.at(i)->SetBinContent(ibinx, Value);
     Dilution_dds.at(i)->SetBinError(ibinx, Error);
   }
 }

 for(int i = 0; i < nSet; i++){
   for(int ibinx = 1; ibinx <= TheoryTemplates.at(i)->GetNbinsX(); ibinx++){
     double Value1 = Dilution_uus.at(i)->GetBinContent(ibinx);
     double Value2 = ((*global_uuFittedSlopeEnsemble)[(vector<int>{global_iZY, global_iQT})])->GetBinContent(ibinx) * par[0] + ((*global_uuFittedOffsetEnsemble)[(vector<int>{global_iZY, global_iQT})])->GetBinContent(ibinx);

     double Value3 = Dilution_dds.at(i)->GetBinContent(ibinx);
     double Value4 = ((*global_ddFittedSlopeEnsemble)[(vector<int>{global_iZY, global_iQT})])->GetBinContent(ibinx) * par[0] + ((*global_ddFittedOffsetEnsemble)[(vector<int>{global_iZY, global_iQT})])->GetBinContent(ibinx);

     double Error1 = 0.0;
     double Error2 = 0.0;
     double Error3 = 0.0;
     double Error4 = 0.0;

     double Value = Value1 * Value2 + Value3 * Value4;
     double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

     TheoryTemplates.at(i)->SetBinContent(ibinx, Value);
     TheoryTemplates.at(i)->SetBinError(ibinx, Error);
   }
 }

 int nbinx = TheoryTemplates.at(0)->GetNbinsX();
 double* xbinning = new double[nbinx + 1];
 xbinning[0] = TheoryTemplates.at(0)->GetXaxis()->GetBinLowEdge(1);
 for(int i = 1; i <= nbinx; i++){
   xbinning[i] = TheoryTemplates.at(0)->GetXaxis()->GetBinUpEdge(i);
 }
 TH2D* DataCovariance = new TH2D("DataCovariance", "DataCovariance", nbinx, xbinning, nbinx, xbinning);

 for(int ibinx = 1; ibinx <= (*global_DataAFBEnsemble)[(vector<int>{global_iZY, global_iQT})]->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= (*global_DataAFBEnsemble)[(vector<int>{global_iZY, global_iQT})]->GetNbinsX(); ibiny++){
     if(ibinx == ibiny) DataCovariance->SetBinContent(ibinx, ibiny, (*global_DataAFBEnsemble)[(vector<int>{global_iZY, global_iQT})]->GetBinError(ibinx) * (*global_DataAFBEnsemble)[(vector<int>{global_iZY, global_iQT})]->GetBinError(ibiny));
     if(ibinx != ibiny) DataCovariance->SetBinContent(ibinx, ibiny, 0.0);
   }
 }

 TH2D* TheoryCovariance;

 DrawPartonCorrelation(TheoryTemplates, TheoryCovariance, "Symmetry");

 DataCovariance->Add(TheoryCovariance);

 TH2D* InverseCovariance = (TH2D *)DataCovariance->Clone("InverseCovariance");

 InverseCovariance->Reset();
 CalculateInverseMatrix(DataCovariance, InverseCovariance);
// CalculateInverseMatrix(TheoryCovariance, InverseCovariance);

 Chi2 = CalculateChi2((*global_DataAFBEnsemble)[(vector<int>{global_iZY, global_iQT})], TheoryTemplates.at(0), InverseCovariance);

 f = Chi2;
 if(f < MinChi2) MinChi2 = f;

 for(int i = 0; i < nSet; i++){
   delete Dilution_uus.at(i);
   delete Dilution_dds.at(i);
   delete TheoryTemplates.at(i);
 }
 delete DataCovariance;
 delete TheoryCovariance;
 delete InverseCovariance;
 delete xbinning;

 cout<<"Min Chi2 = "<<MinChi2<<endl;

}

void LinearDilutionFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 double Chi2 = 0.0;

 TH1D* Dilution_uu = (TH1D *)(*global_TheoryuuDilutionEnsemble)[(vector<int>{global_iPDF, global_iZY, global_iQT})]->Clone("Dilution_uu");
 TH1D* Dilution_dd = (TH1D *)(*global_TheoryddDilutionEnsemble)[(vector<int>{global_iPDF, global_iZY, global_iQT})]->Clone("Dilution_dd");

 TH1D* Delta_uu = (TH1D *)(*global_TheoryDeltauEnsemble)[(vector<int>{global_iPDF, global_iZY, global_iQT})]->Clone("Delta_uu");
 TH1D* Delta_dd = (TH1D *)(*global_TheoryDeltadEnsemble)[(vector<int>{global_iPDF, global_iZY, global_iQT})]->Clone("Delta_dd");

 TH1D* RelativeXsec_uu = (TH1D *)(*global_TheoryuuRelativeXsecEnsemble)[(vector<int>{global_iPDF, global_iZY, global_iQT})]->Clone("RelativeXsec_uu");
 TH1D* RelativeXsec_dd = (TH1D *)(*global_TheoryddRelativeXsecEnsemble)[(vector<int>{global_iPDF, global_iZY, global_iQT})]->Clone("RelativeXsec_dd");

 TH1D* CoefficientDilution_uu = (TH1D *)Dilution_uu->Clone("CoefficientDilution_uu");
 CoefficientDilution_uu->Reset();
 TH1D* CoefficientDilution_dd = (TH1D *)Dilution_dd->Clone("CoefficientDilution_dd");
 CoefficientDilution_dd->Reset();

//Apply the first derivative term
 for(int ibinx = 1; ibinx <= CoefficientDilution_uu->GetNbinsX(); ibinx++){
   double Value = Dilution_uu->GetBinContent(ibinx) + par[3] * (Dilution_uu->GetBinCenter(ibinx) - 90.0);
   double Error = Dilution_uu->GetBinError(ibinx);
   Dilution_uu->SetBinContent(ibinx, Value);
   Dilution_uu->SetBinError(ibinx, Error);
 }

 for(int ibinx = 1; ibinx <= CoefficientDilution_dd->GetNbinsX(); ibinx++){
   double Value = Dilution_dd->GetBinContent(ibinx) + par[4] * (Dilution_dd->GetBinCenter(ibinx) - 90.0);
   double Error = Dilution_dd->GetBinError(ibinx);
   Dilution_dd->SetBinContent(ibinx, Value);
   Dilution_dd->SetBinError(ibinx, Error);
 }

//Construct the coefficient dilution
 for(int ibinx = 1; ibinx <= CoefficientDilution_uu->GetNbinsX(); ibinx++){
   double Value = Dilution_uu->GetBinContent(ibinx) * RelativeXsec_uu->GetBinContent(ibinx);
   double Error = Delta_uu->GetBinError(ibinx);
   CoefficientDilution_uu->SetBinContent(ibinx, Value);
   CoefficientDilution_uu->SetBinError(ibinx, Error);
   //cout<<"RelativeXsec uu bin "<<ibinx<<": "<<Dilution_uu->GetBinContent(ibinx)<<" "<<RelativeXsec_uu->GetBinContent(ibinx)<<endl;
 }

 for(int ibinx = 1; ibinx <= CoefficientDilution_dd->GetNbinsX(); ibinx++){
   double Value = Dilution_dd->GetBinContent(ibinx) * RelativeXsec_dd->GetBinContent(ibinx);
   double Error = Delta_dd->GetBinError(ibinx);
   CoefficientDilution_dd->SetBinContent(ibinx, Value);
   CoefficientDilution_dd->SetBinError(ibinx, Error);
   //cout<<"RelativeXsec dd bin "<<ibinx<<": "<<Dilution_dd->GetBinContent(ibinx)<<" "<<RelativeXsec_dd->GetBinContent(ibinx)<<endl;
 }

//Construct the new Delta and P0 term
 TH1D* ConstructedDelta_uu;
 TH1D* ConstructedDelta_dd;

 vector<double> Value;
 vector<double> Error;
 vector<double> BinWidth;
 double MeanError;
 
 for(int ibin = 1; ibin <= CoefficientDilution_uu->GetNbinsX(); ibin++){
   Value.push_back(CoefficientDilution_uu->GetBinContent(ibin));
   Error.push_back(CoefficientDilution_uu->GetBinError(ibin));
   BinWidth.push_back(CoefficientDilution_uu->GetXaxis()->GetBinUpEdge(ibin) - CoefficientDilution_uu->GetXaxis()->GetBinLowEdge(ibin));
 }
 
 double Mean = CalculateMean(Value, Error, BinWidth, MeanError);
 
 ConstructedDelta_uu = (TH1D *)CoefficientDilution_uu->Clone(CoefficientDilution_uu->GetName() + (TString)"_Residual");
 ConstructedDelta_uu->Reset();
 
 for(int ibin = 1; ibin <= CoefficientDilution_uu->GetNbinsX(); ibin++){
   double Value = CoefficientDilution_uu->GetBinContent(ibin) - Mean;
   double Error = CoefficientDilution_uu->GetBinError(ibin);
   
   ConstructedDelta_uu->SetBinContent(ibin, Value);
   ConstructedDelta_uu->SetBinError(ibin, Error);
 }

 Value.clear();
 Error.clear();
 BinWidth.clear();

 for(int ibin = 1; ibin <= CoefficientDilution_dd->GetNbinsX(); ibin++){
   Value.push_back(CoefficientDilution_dd->GetBinContent(ibin));
   Error.push_back(CoefficientDilution_dd->GetBinError(ibin));
   BinWidth.push_back(CoefficientDilution_dd->GetXaxis()->GetBinUpEdge(ibin) - CoefficientDilution_dd->GetXaxis()->GetBinLowEdge(ibin));
 }

 Mean = CalculateMean(Value, Error, BinWidth, MeanError);

 ConstructedDelta_dd = (TH1D *)CoefficientDilution_dd->Clone(CoefficientDilution_dd->GetName() + (TString)"_Residual");
 ConstructedDelta_dd->Reset();

 for(int ibin = 1; ibin <= CoefficientDilution_dd->GetNbinsX(); ibin++){
   double Value = CoefficientDilution_dd->GetBinContent(ibin) - Mean;
   double Error = CoefficientDilution_dd->GetBinError(ibin);

   ConstructedDelta_dd->SetBinContent(ibin, Value);
   ConstructedDelta_dd->SetBinError(ibin, Error);
 }

 Value.clear();
 Error.clear();
 BinWidth.clear();

/////////////////////////////////////////////////////////////////////////////////////////////
 for(int ibinx = 1; ibinx <= Dilution_uu->GetNbinsX(); ibinx++){
   double Value = ConstructedDelta_uu->GetBinContent(ibinx) + par[1];
   double Error = Delta_uu->GetBinError(ibinx);

   Delta_uu->SetBinContent(ibinx, Value);
   Delta_uu->SetBinError(ibinx, Error);
 }

 for(int ibinx = 1; ibinx <= Dilution_dd->GetNbinsX(); ibinx++){
   double Value = ConstructedDelta_dd->GetBinContent(ibinx) + par[2];
   double Error = Delta_dd->GetBinError(ibinx);

   Delta_dd->SetBinContent(ibinx, Value);
   Delta_dd->SetBinError(ibinx, Error);
 }

//////////////////////////////////////////////////////////////////////////////////////////////

 TH1D* AFB = (TH1D *)(*global_DataAFBEnsemble)[(vector<int>{global_iZY, global_iQT})]->Clone("AFB_Hadron");
 AFB->Reset();

 for(int ibinx = 1; ibinx <= AFB->GetNbinsX(); ibinx++){
   double Value1 = Delta_uu->GetBinContent(ibinx);
   double Value2 = ((*global_uuFittedSlopeEnsemble)[(vector<int>{global_iZY, global_iQT})])->GetBinContent(ibinx) * par[0] + ((*global_uuFittedOffsetEnsemble)[(vector<int>{global_iZY, global_iQT})])->GetBinContent(ibinx);

   double Value3 = Delta_dd->GetBinContent(ibinx);
   double Value4 = ((*global_ddFittedSlopeEnsemble)[(vector<int>{global_iZY, global_iQT})])->GetBinContent(ibinx) * par[0] + ((*global_ddFittedOffsetEnsemble)[(vector<int>{global_iZY, global_iQT})])->GetBinContent(ibinx);

   double Error1 = 0.0;
   double Error2 = 0.0;

   double Error3 = 0.0;
   double Error4 = 0.0;

   double Value = Value1 * Value2 + Value3 * Value4;
   double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

   AFB->SetBinContent(ibinx, Value);
   AFB->SetBinError(ibinx, Error);
 }

 Chi2 = CalculateChi2((*global_DataAFBEnsemble)[(vector<int>{global_iZY, global_iQT})], AFB);

 f = Chi2;
 if(f < MinChi2) MinChi2 = f;

 //global_FittedAFBEnsemble[(vector<int>{global_iPDF, global_iZY, global_iQT})] = (TH1D *)AFB->Clone((TString)"FittedAFB_PDF" + (int)global_iPDF + "_ZY" + (int)global_iZY + (TString)"_QT_" + (int)global_iQT);

 delete Dilution_uu;
 delete Dilution_dd;
 delete Delta_uu;
 delete Delta_dd;
 delete RelativeXsec_uu;
 delete RelativeXsec_dd;
 delete CoefficientDilution_uu;
 delete CoefficientDilution_dd;
 delete ConstructedDelta_uu;
 delete ConstructedDelta_dd;
 delete AFB;

 cout<<"Min Chi2 = "<<MinChi2<<endl;

}

class DilutionFitting
{
 public:

 TMinuitHelper* myMinuit;

/////////////////////////////////////////////////////
 TString AFB_uu_Name = "AFB_ZMass_ZY_QT_uu";
 TString AFB_dd_Name = "AFB_ZMass_ZY_QT_dd";

 vector<TString> STWTemplates;
 vector<TH3D *> uuLinearPlot;
 vector<TH3D *> ddLinearPlot;
 TH3D* uuFittedSlope;
 TH3D* uuFittedOffset;
 TH3D* ddFittedSlope;
 TH3D* ddFittedOffset;
 FitAFBStw* uuSlopeAndOffset;
 FitAFBStw* ddSlopeAndOffset;

 map<int, double> STWInput;
 map<double, int> FindSTW;

 int FirstSTW = 15;
 int LastSTW = 30;

 TFile* STWFiles[40];

 TH3D* uuAFB[40];
 vector<TH3D *> uuAFBs;
 TH3D* ddAFB[40];
 vector<TH3D *> ddAFBs;

 map<vector<int>, TH1D *> uuFittedSlopeEnsemble;
 map<vector<int>, TH1D *> uuFittedOffsetEnsemble;
 map<vector<int>, TH1D *> ddFittedSlopeEnsemble;
 map<vector<int>, TH1D *> ddFittedOffsetEnsemble;

//////////////////////////////////////////////////////

 TFile* writefile;

 TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/MSHT20.00/MC_results.root";

 TString AFBName = "AFB_ZMass_ZY_QT";

 TString Dilution_uu_Name = "Dilution_ZMass_ZY_QT_uu";
 TString Dilution_dd_Name = "Dilution_ZMass_ZY_QT_dd";
 TString Delta_uu_Name = "CoefficientZMass_ZY_QT_uu_wrong_Residual";
 TString Delta_dd_Name = "CoefficientZMass_ZY_QT_dd_wrong_Residual";
 TString AveDilution_uu_Name = "CoefficientZMass_ZY_QT_uu_wrong_Average";
 TString AveDilution_dd_Name = "CoefficientZMass_ZY_QT_dd_wrong_Average";
 TString Xsec_uu_Name = "ZMass_ZY_QT_uu_total";
 TString Xsec_dd_Name = "ZMass_ZY_QT_dd_total";
 TString Xsec_all_Name = "ZMass_ZY_QT";

 TString ErrorType = "Symmetry";

 vector<TString> rootNames;

 vector<double> Su;
 vector<double> Sd;
 vector<TH1D *> SFittingResults;

 vector<TH3D *> PDFAFBs;

 vector<TH3D *> TmpAFBs;

 vector<TH3D *> AverageDilution_uus;
 vector<TH3D *> AverageDilution_dds;

 vector<TH1D *> PDFPus;
 vector<TH1D *> PDFPds;
 vector<TH1D *> PDFP0s;

 TH3D *Data_Xsec_all;

 map<vector<int>, TH1D *> DataAFBEnsemble;
 map<vector<int>, TH1D *> DataPuEnsemble;
 map<vector<int>, TH1D *> DataPdEnsemble;
 map<vector<int>, TH1D *> DataDeltauEnsemble;
 map<vector<int>, TH1D *> DataDeltadEnsemble;
 map<vector<int>, TH1D *> DatauuDilutionEnsemble;
 map<vector<int>, TH1D *> DataddDilutionEnsemble;
 map<vector<int>, TH1D *> DatauuRelativeXsecEnsemble;
 map<vector<int>, TH1D *> DataddRelativeXsecEnsemble;

 map<vector<int>, TH1D *> TheoryAFBEnsemble;
 map<vector<int>, TH1D *> TheoryPuEnsemble;
 map<vector<int>, TH1D *> TheoryPdEnsemble;
 map<vector<int>, TH1D *> TheoryDeltauEnsemble;
 map<vector<int>, TH1D *> TheoryDeltadEnsemble;
 map<vector<int>, TH1D *> TheoryuuDilutionEnsemble;
 map<vector<int>, TH1D *> TheoryddDilutionEnsemble;
 map<vector<int>, TH1D *> TheoryuuRelativeXsecEnsemble;
 map<vector<int>, TH1D *> TheoryddRelativeXsecEnsemble;

 map<vector<int>, TH1D *> ResultPuEnsemble;
 map<vector<int>, TH1D *> ResultPdEnsemble;
 map<vector<int>, TH1D *> ResultStwEnsemble;

 map<vector<int>, TH1D *> ResultPuDeltaEnsemble;
 map<vector<int>, TH1D *> ResultPdDeltaEnsemble;
 map<vector<int>, TH1D *> ResultStwDeltaEnsemble;

 map<vector<int>, TH1D *> ResultPuDeltaMVariEnsemble;
 map<vector<int>, TH1D *> ResultPdDeltaMVariEnsemble;
 map<vector<int>, TH1D *> ResultStwDeltaMVariEnsemble;

 map<vector<int>, TH1D *> ResultPuDeltaMuncEnsemble;
 map<vector<int>, TH1D *> ResultPdDeltaMuncEnsemble;
 map<vector<int>, TH1D *> ResultStwDeltaMuncEnsemble;

 map<vector<int>, TH1D *> ResultPuFituncEnsemble;
 map<vector<int>, TH1D *> ResultPdFituncEnsemble;
 map<vector<int>, TH1D *> ResultStwFituncEnsemble;

 map<vector<int>, TH1D *> ResultPuPDFuncEnsemble;
 map<vector<int>, TH1D *> ResultPdPDFuncEnsemble;
 map<vector<int>, TH1D *> ResultDeltauPDFuncEnsemble;
 map<vector<int>, TH1D *> ResultDeltadPDFuncEnsemble;

 bool onlyCentral = false;

 DilutionFitting();
 virtual void GetAFBStwLinear();
 virtual void InitialData(TString DataName);
 virtual void OpenFile();
 virtual void Save(){
   writefile->cd();

   for(int ibinz = 1; ibinz <= uuFittedSlope->GetNbinsZ(); ibinz++){
     writefile->cd();
   
     for(int i = 0; i < rootNames.size(); i++){
       ResultPuDeltaMVariEnsemble[(vector<int>{i, ibinz})]->Write();
       ResultPdDeltaMVariEnsemble[(vector<int>{i, ibinz})]->Write();
       ResultStwDeltaMVariEnsemble[(vector<int>{i, ibinz})]->Write();
     }

     ResultPuEnsemble[(vector<int>{ibinz})]->Write();
     ResultPdEnsemble[(vector<int>{ibinz})]->Write();
     ResultStwEnsemble[(vector<int>{ibinz})]->Write();
     ResultPuDeltaEnsemble[(vector<int>{ibinz})]->Write();
     ResultPdDeltaEnsemble[(vector<int>{ibinz})]->Write();
     ResultStwDeltaEnsemble[(vector<int>{ibinz})]->Write();
     ResultPuDeltaMuncEnsemble[(vector<int>{ibinz})]->Write();
     ResultPdDeltaMuncEnsemble[(vector<int>{ibinz})]->Write();
     ResultStwDeltaMuncEnsemble[(vector<int>{ibinz})]->Write();
     ResultPuFituncEnsemble[(vector<int>{ibinz})]->Write();
     ResultPdFituncEnsemble[(vector<int>{ibinz})]->Write();
     ResultStwFituncEnsemble[(vector<int>{ibinz})]->Write();
     ResultPuPDFuncEnsemble[(vector<int>{ibinz})]->Write();
     ResultPdPDFuncEnsemble[(vector<int>{ibinz})]->Write();
   }

//   writefile->Write();
   writefile->Close();
   cout<<"File closed."<<endl;
 }
 virtual void InitialTheory();
 virtual void InitialResult();
 virtual void UpdateDelta();
 virtual void Fitting(int iPDF, int iZY, int iQT);
 virtual void FittingCorr(int iZY, int iQT);
 virtual void LinearFitting(int iPDF, int iZY, int iQT);
 virtual void DeltaInducedUnc(int iZY, int iQT);
 virtual void GetStwCombinedError();
 virtual void OnlyCentral(){onlyCentral = true;}

};

#endif
