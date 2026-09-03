#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "Uncertainty/FitAFBStw.h"
#include "CompareDataTheory/CompareDataTheory.h"
#include "TMinuitHelper/TMinuitHelper.h"
#include "PDFHelper/PDFReweight.h"
#include "Tools/Tools.h"

using namespace std;

TH1D* global_Dilution_uu_Residual;
TH1D* global_Dilution_dd_Residual;
TH1D* global_Dilution_ss_Residual;
TH1D* global_Dilution_cc_Residual;
TH1D* global_Dilution_bb_Residual;
TH1D* global_AFB_uu;
TH1D* global_AFB_dd;
TH1D* global_Dilution_uu_Average;
TH1D* global_Dilution_dd_Average;
TH1D* global_uuFittedSlope;
TH1D* global_uuFittedOffset;
TH1D* global_ddFittedSlope;
TH1D* global_ddFittedOffset;
PDFReweight *global_AFBCalc;

TH1D* global_MC;
TH1D* global_Data;

TH1D* global_TmpAFB;

double MinChi2 = 100000.0;

void udDilutionFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
// double xbins[11] = {80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100};
// TH1D* Data_80_100 = (TH1D *)global_Data->Rebin(10, "Data_80_100", xbins);

 double Chi2 = 0.0;

 TH1D* AFB_uu = (TH1D *)global_AFB_uu->Clone("AFB_uu");
 TH1D* AFB_dd = (TH1D *)global_AFB_dd->Clone("AFB_dd");
 TH1D* Dilution_uu = (TH1D *)global_Dilution_uu_Residual->Clone("Dilution_uu_Residual");
 TH1D* Dilution_dd = (TH1D *)global_Dilution_dd_Residual->Clone("Dilution_dd_Residual");
// TH1D* Dilution_ss = (TH1D *)global_Dilution_ss_Residual->Clone("Dilution_ss_Residual");
// TH1D* Dilution_cc = (TH1D *)global_Dilution_cc_Residual->Clone("Dilution_cc_Residual");
// TH1D* Dilution_bb = (TH1D *)global_Dilution_bb_Residual->Clone("Dilution_bb_Residual");

// TH1D* AFB_uu = (TH1D *)global_AFB_uu->Rebin(10, "AFB_uu", xbins);
// TH1D* AFB_dd = (TH1D *)global_AFB_dd->Rebin(10, "AFB_dd", xbins);
// TH1D* Dilution_uu = (TH1D *)global_Dilution_uu_Residual->Rebin(10, "Dilution_uu_Residual", xbins);
// TH1D* Dilution_dd = (TH1D *)global_Dilution_dd_Residual->Rebin(10, "Dilution_dd_Residual", xbins);

 Dilution_uu->Reset();
 Dilution_dd->Reset();
// Dilution_ss->Reset();
// Dilution_cc->Reset();
// Dilution_bb->Reset();

 for(int ibin = 1; ibin <= Dilution_uu->GetNbinsX(); ibin++){
   double Value = global_Dilution_uu_Residual->GetBinContent(ibin) + par[0];
   double Error = global_Dilution_uu_Residual->GetBinError(ibin);
   Dilution_uu->SetBinContent(ibin, Value);
   Dilution_uu->SetBinError(ibin, Error);
 }

 for(int ibin = 1; ibin <= Dilution_dd->GetNbinsX(); ibin++){
   double Value = global_Dilution_dd_Residual->GetBinContent(ibin) + par[1];
   double Error = global_Dilution_dd_Residual->GetBinError(ibin);
   Dilution_dd->SetBinContent(ibin, Value);
   Dilution_dd->SetBinError(ibin, Error);
 }

/* for(int ibin = 1; ibin <= Dilution_ss->GetNbinsX(); ibin++){
   double Value = global_Dilution_ss_Residual->GetBinContent(ibin) + par[3];
   double Error = global_Dilution_ss_Residual->GetBinError(ibin);
   Dilution_ss->SetBinContent(ibin, Value);
   Dilution_ss->SetBinError(ibin, Error);
 }

 for(int ibin = 1; ibin <= Dilution_cc->GetNbinsX(); ibin++){
   double Value = global_Dilution_cc_Residual->GetBinContent(ibin) + par[4];
   double Error = global_Dilution_cc_Residual->GetBinError(ibin);
   Dilution_cc->SetBinContent(ibin, Value);
   Dilution_cc->SetBinError(ibin, Error);
 }

 for(int ibin = 1; ibin <= Dilution_bb->GetNbinsX(); ibin++){
   double Value = global_Dilution_bb_Residual->GetBinContent(ibin) + par[5];
   double Error = global_Dilution_bb_Residual->GetBinError(ibin);
   Dilution_bb->SetBinContent(ibin, Value);
   Dilution_bb->SetBinError(ibin, Error);
 }
*/

 TH1D* AFB = (TH1D *)AFB_uu->Clone("AFB_Hadron");
 AFB->Reset();

 global_AFBCalc->InputStw(par[2]);

 for(int ibin = 1; ibin <= AFB_uu->GetNbinsX(); ibin++){
   double BinLeft = AFB_uu->GetXaxis()->GetBinLowEdge(ibin);
   double BinRight = AFB_uu->GetXaxis()->GetBinUpEdge(ibin);

   double Value1 = Dilution_uu->GetBinContent(ibin);
//   double Value1 = Dilution_uu->GetBinContent(ibin) + Dilution_cc->GetBinContent(ibin);
   double Value2 = global_uuFittedSlope->GetBinContent(ibin) * par[2] + global_uuFittedOffset->GetBinContent(ibin);
//   double Value2 = global_AFBCalc->GetQuarkAFB(BinLeft, BinRight, 1000);

   double Value3 = Dilution_dd->GetBinContent(ibin);
//   double Value3 = Dilution_dd->GetBinContent(ibin) + Dilution_ss->GetBinContent(ibin) + Dilution_bb->GetBinContent(ibin);
   double Value4 = global_ddFittedSlope->GetBinContent(ibin) * par[2] + global_ddFittedOffset->GetBinContent(ibin);
//   double Value4 = global_AFBCalc->GetQuarkAFB(BinLeft, BinRight, 2000);

//   double Error1 = Dilution_uu->GetBinError(ibin);
   double Error1 = 0.0;
//   double Error2 = global_uuFittedSlope->GetBinError(ibin) * par[2];
   double Error2 = 0.0;

//   double Error3 = Dilution_dd->GetBinError(ibin);
   double Error3 = 0.0;
//   double Error4 = global_ddFittedSlope->GetBinError(ibin) * par[2];
   double Error4 = 0.0;

   double Value = Value1 * Value2 + Value3 * Value4;
   double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

   AFB->SetBinContent(ibin, Value);
   AFB->SetBinError(ibin, Error);
 }

// double xbins[11] = {80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100};
// TH1D* Data_80_100 = (TH1D *)global_Data->Rebin(10, "Data_80_100", xbins);
// TH1D* MC_80_100 = (TH1D *)AFB->Rebin(10, "MC_80_100", xbins);

 Chi2 = CalculateChi2(global_Data, AFB);
// Chi2 = CalculateChi2(Data_80_100, MC_80_100);
// Chi2 = CalculateChi2(Data_80_100, AFB);

 f = Chi2;
 if(f < MinChi2) MinChi2 = f;

 global_MC = (TH1D *)AFB->Clone("Global_AFB_Hadron");

 delete AFB;

 cout<<"Min Chi2 = "<<MinChi2<<endl;
}

int main(int argc, char** argv)
{
 double massrange[31] = {60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120};

 vector<TString> rootNames;
 TString rootName;

 ifstream infile;
  infile.open("theoryCC.list",ios::in);
 while(infile>>rootName){
  rootNames.push_back(rootName);
 }
 infile.close();

 vector<TString> STWTemplates;
  infile.open("STWTemplate.list",ios::in);
 while(infile>>rootName){
  STWTemplates.push_back(rootName);
 }

// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/i2Tn3.00/MC_results.root";
 TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/250M/i2Tn3.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/FullAFB_RotatedCT18NNLO_LHA.01/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/STWTemplate/0.2324/MC_results.root";

 TString EtaRegion = "Full";

 TString VariableName = "AFB_" + EtaRegion;

 TFile* writefile = new TFile(VariableName + "_PDFResults.root", "RECREATE");
 writefile->cd();

 TString AFBName = "AFB_" + EtaRegion;

 TString Dilution_uu_Name = "CoefficientDilution_ZMass_" + EtaRegion + "_uu_Residual";
 TString Dilution_dd_Name = "CoefficientDilution_ZMass_" + EtaRegion + "_dd_Residual";
 TString AveDilution_uu_Name = "CoefficientDilution_ZMass_" + EtaRegion + "_uu_Average";
 TString AveDilution_dd_Name = "CoefficientDilution_ZMass_" + EtaRegion + "_dd_Average";

 TString AFB_uu_Name = "AFB_" + EtaRegion + "_uu";
 TString AFB_dd_Name = "AFB_" + EtaRegion + "_dd";

 TString Zmass_uu_wrong_Name = "ZMass_" + EtaRegion + "_uu_wrong";
 TString Zmass_uu_total_Name = "ZMass_" + EtaRegion + "_uu_total";
 TString Zmass_dd_wrong_Name = "ZMass_" + EtaRegion + "_dd_wrong";
 TString Zmass_dd_total_Name = "ZMass_" + EtaRegion + "_dd_total";
 TString Zmass_ss_wrong_Name = "ZMass_" + EtaRegion + "_ss_wrong";
 TString Zmass_ss_total_Name = "ZMass_" + EtaRegion + "_ss_total";
 TString Zmass_cc_wrong_Name = "ZMass_" + EtaRegion + "_cc_wrong";
 TString Zmass_cc_total_Name = "ZMass_" + EtaRegion + "_cc_total";
 TString Zmass_bb_wrong_Name = "ZMass_" + EtaRegion + "_bb_wrong";
 TString Zmass_bb_total_Name = "ZMass_" + EtaRegion + "_bb_total";

 TString Zmass_utype_wrong_Name = "ZMass_" + EtaRegion + "_utype_wrong";
 TString Zmass_dtype_wrong_Name = "ZMass_" + EtaRegion + "_dtype_wrong";
 TString Zmass_utype_total_Name = "ZMass_" + EtaRegion + "_utype_total";
 TString Zmass_dtype_total_Name = "ZMass_" + EtaRegion + "_dtype_total";

 if(EtaRegion == "Full") EtaRegion = "";
 if(EtaRegion == "CC") EtaRegion = "_CC";
 if(EtaRegion == "CF") EtaRegion = "_CF";

 TString Zmass_Name = "ZMass" + EtaRegion;
 TString FZmass_Name = "FZmass" + EtaRegion;
 TString BZmass_Name = "BZmass" + EtaRegion;

 TString FZmass_uu_Name = "FZmass" + EtaRegion + "_uu";
 TString FZmass_dd_Name = "FZmass" + EtaRegion + "_dd";
 TString FZmass_gg_Name = "FZmass" + EtaRegion + "_gg";
 TString BZmass_uu_Name = "BZmass" + EtaRegion + "_uu";
 TString BZmass_dd_Name = "BZmass" + EtaRegion + "_dd";
 TString BZmass_gg_Name = "BZmass" + EtaRegion + "_gg";

 TString Zmass_uu_Name = "ZMass" + EtaRegion + "_uu";
 TString Zmass_dd_Name = "ZMass" + EtaRegion + "_dd";
 TString Zmass_ss_Name = "ZMass" + EtaRegion + "_ss";
 TString Zmass_cc_Name = "ZMass" + EtaRegion + "_cc";
 TString Zmass_bb_Name = "ZMass" + EtaRegion + "_bb";


 TFile *DataFile = new TFile(DataName);

 TH1D *DataAFB = (TH1D *)DataFile->Get(AFBName);
 TH1D *Data_uuEpsilon = (TH1D *)DataFile->Get(Dilution_uu_Name);
 TH1D *Data_ddEpsilon = (TH1D *)DataFile->Get(Dilution_dd_Name);
 TH1D *Data_FZmass = (TH1D *)DataFile->Get(FZmass_Name);
 TH1D *Data_BZmass = (TH1D *)DataFile->Get(BZmass_Name);

 Data_FZmass->Rebin(4);
 Data_BZmass->Rebin(4);

 global_Data = (TH1D *)Data_FZmass->Clone(AFBName);
 global_Data->Reset();

 AFBFunction(Data_FZmass, Data_BZmass, global_Data);

 writefile->cd();
 DataAFB->Write();


////////////////////////////////////////////////////////////////
 map<int, double> STWInput;
 map<double, int> FindSTW;
 for(int i = 0; i < 40; i++){
   STWInput[i] = 0.2255 + i * 0.0003;
 }

 int FirstSTW = 15;
 int LastSTW = 30;

 int Index = 0;

 TH1D* uuAFB[40];
 vector<TH1D *> uuAFBs;
 for(int i = FirstSTW; i < LastSTW; i++){

   FindSTW[STWInput[i]] = Index;
   Index++;

   TFile* file = new TFile(STWTemplates.at(i));
   TH1D* FZmass = (TH1D *)file->Get(FZmass_uu_Name);
   TH1D* BZmass = (TH1D *)file->Get(BZmass_uu_Name);
   FZmass->Rebin(4);
   BZmass->Rebin(4);

   uuAFB[i] = (TH1D *)FZmass->Clone(AFB_uu_Name);
   uuAFB[i]->Reset();

   AFBFunction(FZmass, BZmass, uuAFB[i]);

   uuAFBs.push_back(uuAFB[i]);

   writefile->cd();
   uuAFB[i]->Write((TString)"AFB_uu_STW" + (int)i);
 }

 TH1D* ddAFB[40];
 vector<TH1D *> ddAFBs;
 for(int i = FirstSTW; i < LastSTW; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   TH1D* FZmass = (TH1D *)file->Get(FZmass_dd_Name);
   TH1D* BZmass = (TH1D *)file->Get(BZmass_dd_Name);
   FZmass->Rebin(4);
   BZmass->Rebin(4);

   ddAFB[i] = (TH1D *)FZmass->Clone(AFB_dd_Name);
   ddAFB[i]->Reset();

   AFBFunction(FZmass, BZmass, ddAFB[i]);

   ddAFBs.push_back(ddAFB[i]);

   writefile->cd();
   ddAFB[i]->Write((TString)"AFB_dd_STW" + (int)i);
 }

 vector<TH1D *> uuLinearPlot;
 vector<TH1D *> ddLinearPlot;
 TH1D* uuFittedSlope;
 TH1D* uuFittedOffset;
 TH1D* ddFittedSlope;
 TH1D* ddFittedOffset;
 FitAFBStw* uuSlopeAndOffset = new FitAFBStw();
 uuSlopeAndOffset->Input(uuAFBs, STWInput[FirstSTW], STWInput[LastSTW - 1], uuLinearPlot, uuFittedSlope, uuFittedOffset);
 FitAFBStw* ddSlopeAndOffset = new FitAFBStw();
 ddSlopeAndOffset->Input(ddAFBs, STWInput[FirstSTW], STWInput[LastSTW - 1], ddLinearPlot, ddFittedSlope, ddFittedOffset);

 global_uuFittedSlope = uuFittedSlope;
 global_uuFittedOffset = uuFittedOffset;
 global_ddFittedSlope = ddFittedSlope;
 global_ddFittedOffset = ddFittedOffset;


 PDFReweight *AFBCalc = new PDFReweight();
 AFBCalc->InitialPDF("CT18NNLO", 0);
 AFBCalc->InputStw(0.2315);

 global_AFBCalc = AFBCalc;
////////////////////////////////////////////////////////////////

 vector<double> Su;
 vector<double> Sd;
 TH1D* SFittingResult[59];
 vector<TH1D *> SFittingResults;

 TH1D *AveAFBHist[59];
 vector<TH1D *> AveAFBHists;

 TH1D* PDFAFB[59];
 vector<TH1D *> PDFAFBs;

 TH1D* TmpAFB[59];
 vector<TH1D *> TmpAFBs;

 TH1D* AverageDilution_uu[59];
 vector<TH1D *> AverageDilution_uus;
 TH1D* AverageDilution_dd[59];
 vector<TH1D *> AverageDilution_dds;
 TH1D* AverageDilution_ss[59];
 vector<TH1D *> AverageDilution_sss;
 TH1D* AverageDilution_cc[59];
 vector<TH1D *> AverageDilution_ccs;
 TH1D* AverageDilution_bb[59];
 vector<TH1D *> AverageDilution_bbs;

 for(int i = 0; i < 59; i++){
   TFile* file = new TFile(rootNames.at(i));
//   if(i == 0) file = new TFile(STWTemplates.at(23));
   TH1D* FZmass_uu = (TH1D *)file->Get(FZmass_uu_Name);
   TH1D* BZmass_uu = (TH1D *)file->Get(BZmass_uu_Name);
   FZmass_uu->Rebin(4);
   BZmass_uu->Rebin(4);
   TH1D* AFB_uu = (TH1D *)FZmass_uu->Clone(AFB_uu_Name);
   AFB_uu->Reset();
   AFBFunction(FZmass_uu, BZmass_uu, AFB_uu);

   TH1D* FZmass_dd = (TH1D *)file->Get(FZmass_dd_Name);
   TH1D* BZmass_dd = (TH1D *)file->Get(BZmass_dd_Name);
   FZmass_dd->Rebin(4);
   BZmass_dd->Rebin(4);
   TH1D* AFB_dd = (TH1D *)FZmass_dd->Clone(AFB_dd_Name);
   AFB_dd->Reset();
   AFBFunction(FZmass_dd, BZmass_dd, AFB_dd);

   TH1D* ZMass = (TH1D *)file->Get(Zmass_Name);
   ZMass->Rebin(4);

   TH1D* ZMass_uu = (TH1D *)file->Get(Zmass_uu_Name);
   TH1D* ZMass_dd = (TH1D *)file->Get(Zmass_dd_Name);
   TH1D* ZMass_ss = (TH1D *)file->Get(Zmass_ss_Name);
   TH1D* ZMass_cc = (TH1D *)file->Get(Zmass_cc_Name);
   TH1D* ZMass_bb = (TH1D *)file->Get(Zmass_bb_Name);
   TH1D* ZMass_uu_wrong = (TH1D *)file->Get(Zmass_uu_wrong_Name);
   TH1D* ZMass_uu_total = (TH1D *)file->Get(Zmass_uu_total_Name);
   TH1D* ZMass_dd_wrong = (TH1D *)file->Get(Zmass_dd_wrong_Name);
   TH1D* ZMass_dd_total = (TH1D *)file->Get(Zmass_dd_total_Name);
   TH1D* ZMass_ss_wrong = (TH1D *)file->Get(Zmass_ss_wrong_Name);
   TH1D* ZMass_ss_total = (TH1D *)file->Get(Zmass_ss_total_Name);
   TH1D* ZMass_cc_wrong = (TH1D *)file->Get(Zmass_cc_wrong_Name);
   TH1D* ZMass_cc_total = (TH1D *)file->Get(Zmass_cc_total_Name);
   TH1D* ZMass_bb_wrong = (TH1D *)file->Get(Zmass_bb_wrong_Name);
   TH1D* ZMass_bb_total = (TH1D *)file->Get(Zmass_bb_total_Name);

   TH1D* ZMass_utype_wrong = (TH1D *)ZMass_uu_wrong->Clone(Zmass_utype_wrong_Name);
   //ZMass_utype_wrong->Add(ZMass_cc_wrong);
   TH1D* ZMass_dtype_wrong = (TH1D *)ZMass_dd_wrong->Clone(Zmass_dtype_wrong_Name);
   //ZMass_dtype_wrong->Add(ZMass_ss_wrong);
   //ZMass_dtype_wrong->Add(ZMass_bb_wrong);

   TH1D* ZMass_utype_total = (TH1D *)ZMass_uu_total->Clone(Zmass_utype_total_Name);
   //ZMass_utype_total->Add(ZMass_cc_total);
   TH1D* ZMass_dtype_total = (TH1D *)ZMass_dd_total->Clone(Zmass_dtype_total_Name);
   //ZMass_dtype_total->Add(ZMass_ss_total);
   //ZMass_dtype_total->Add(ZMass_bb_total);


   ZMass_uu->Rebin(4);
   ZMass_dd->Rebin(4);
   ZMass_ss->Rebin(4);
   ZMass_cc->Rebin(4);
   ZMass_bb->Rebin(4);
   ZMass_uu_wrong->Rebin(4);
   ZMass_uu_total->Rebin(4);
   ZMass_dd_wrong->Rebin(4);
   ZMass_dd_total->Rebin(4);
   ZMass_ss_wrong->Rebin(4);
   ZMass_ss_total->Rebin(4);
   ZMass_cc_wrong->Rebin(4);
   ZMass_cc_total->Rebin(4);
   ZMass_bb_wrong->Rebin(4);
   ZMass_bb_total->Rebin(4);

   vector<TH1D *> Xsec = {ZMass_uu, ZMass_dd, ZMass_ss, ZMass_cc, ZMass_bb};
   TH1D* XsecFraction_uu = (TH1D *)ZMass_uu->Clone("XsecFraction_uu");
   XsecFraction_uu->Reset();
   TH1D* XsecFraction_dd = (TH1D *)ZMass_dd->Clone("XsecFraction_dd");
   XsecFraction_dd->Reset();

   GetXsecFraction(ZMass_uu, Xsec, XsecFraction_uu);
   GetXsecFraction(ZMass_dd, Xsec, XsecFraction_dd);

   TH1D* Dilution_uu = (TH1D *)ZMass_uu_wrong->Clone("Dilution_uu");
   Dilution_uu->Divide(ZMass_uu_total);
   TH1D* Dilution_dd = (TH1D *)ZMass_dd_wrong->Clone("Dilution_dd");
   Dilution_dd->Divide(ZMass_dd_total);

   TH1D* CoefficientDilution_uu;
   TH1D* CoefficientDilution_dd;
   TH1D* CoefficientDilution_ss;
   TH1D* CoefficientDilution_cc;
   TH1D* CoefficientDilution_bb;
   TH1D* CoefficientDilution_utype;
   TH1D* CoefficientDilution_dtype;

   TH1D* DilutionAverage_uu;
   TH1D* DilutionAverage_dd;
   TH1D* DilutionAverage_ss;
   TH1D* DilutionAverage_cc;
   TH1D* DilutionAverage_bb;
   TH1D* DilutionAverage_utype;
   TH1D* DilutionAverage_dtype;

   TH1D* ResidualDilution_uu;
   TH1D* ResidualDilution_dd;
   TH1D* ResidualDilution_ss;
   TH1D* ResidualDilution_cc;
   TH1D* ResidualDilution_bb;
   TH1D* ResidualDilution_utype;
   TH1D* ResidualDilution_dtype;

//   GetCoefficientDilution(Dilution_uu, XsecFraction_uu, CoefficientDilution_uu);
//   GetCoefficientDilution(Dilution_dd, XsecFraction_dd, CoefficientDilution_dd);
   GetCoefficientDilution(ZMass_uu_wrong, ZMass_uu_total, ZMass, CoefficientDilution_uu);
   GetCoefficientDilution(ZMass_dd_wrong, ZMass_dd_total, ZMass, CoefficientDilution_dd);
   GetCoefficientDilution(ZMass_ss_wrong, ZMass_ss_total, ZMass, CoefficientDilution_ss);
   GetCoefficientDilution(ZMass_cc_wrong, ZMass_cc_total, ZMass, CoefficientDilution_cc);
   GetCoefficientDilution(ZMass_bb_wrong, ZMass_bb_total, ZMass, CoefficientDilution_bb);
   GetCoefficientDilution(ZMass_utype_wrong, ZMass_utype_total, ZMass, CoefficientDilution_utype);
   GetCoefficientDilution(ZMass_dtype_wrong, ZMass_dtype_total, ZMass, CoefficientDilution_dtype);

   GetDilutionAverage(CoefficientDilution_uu, DilutionAverage_uu, ResidualDilution_uu);
   GetDilutionAverage(CoefficientDilution_dd, DilutionAverage_dd, ResidualDilution_dd);
   GetDilutionAverage(CoefficientDilution_ss, DilutionAverage_ss, ResidualDilution_ss);
   GetDilutionAverage(CoefficientDilution_cc, DilutionAverage_cc, ResidualDilution_cc);
   GetDilutionAverage(CoefficientDilution_bb, DilutionAverage_bb, ResidualDilution_bb);
   GetDilutionAverage(CoefficientDilution_utype, DilutionAverage_utype, ResidualDilution_utype);
   GetDilutionAverage(CoefficientDilution_dtype, DilutionAverage_dtype, ResidualDilution_dtype);

   global_Dilution_uu_Residual = ResidualDilution_uu;
   global_Dilution_dd_Residual = ResidualDilution_dd;
//   global_Dilution_uu_Residual = ResidualDilution_utype;
//   global_Dilution_dd_Residual = ResidualDilution_dtype;
//   global_Dilution_ss_Residual = ResidualDilution_ss;
//   global_Dilution_cc_Residual = ResidualDilution_cc;
//   global_Dilution_bb_Residual = ResidualDilution_bb;

   AverageDilution_uu[i] = DilutionAverage_uu;
   AverageDilution_dd[i] = DilutionAverage_dd;
//   AverageDilution_uu[i] = DilutionAverage_utype;
//   AverageDilution_dd[i] = DilutionAverage_dtype;
//   AverageDilution_ss[i] = DilutionAverage_ss;
//   AverageDilution_cc[i] = DilutionAverage_cc;
//   AverageDilution_bb[i] = DilutionAverage_bb;
   AverageDilution_uus.push_back(AverageDilution_uu[i]);
   AverageDilution_dds.push_back(AverageDilution_dd[i]);

//   AverageDilution_sss.push_back(AverageDilution_ss[i]);
//   AverageDilution_ccs.push_back(AverageDilution_cc[i]);
//   AverageDilution_bbs.push_back(AverageDilution_bb[i]);


//   global_Dilution_uu_Residual = Data_uuEpsilon;
//   global_Dilution_dd_Residual = Data_ddEpsilon;

   global_AFB_uu = AFB_uu;
   global_AFB_dd = AFB_dd;

   if(i == 0){
     TMinuitHelper *myMinuit = new TMinuitHelper(3);
     myMinuit->SetFCN(udDilutionFitting);
     myMinuit->Input(0, "Su", 0.2, 0.5, 0.0, 0.5);
     myMinuit->Input(1, "Sd", 0.2, 0.5, 0.0, 0.5);
     myMinuit->Input(2, "Stw", 0.2315, 0.01, 0.23, 0.24);
//     myMinuit->Input(3, "Ss", 0.0, 0.1, -0.1, 0.1);
//     myMinuit->Input(4, "Sc", 0.0, 0.1, -0.1, 0.1);
//     myMinuit->Input(5, "Sb", 0.0, 0.1, -0.1, 0.1);
     myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
     myMinuit->Exec("MIGRAD", 100000, 0.001);
     myMinuit->GetParameter();
     double* SPar = new double[6];
     double* SParError = new double[6];
     myMinuit->GetParametersAndError(SPar, SParError);
     Su.push_back(SPar[0]);
     Sd.push_back(SPar[1]);

     SFittingResult[i] = new TH1D((TString)"SFittingResult_PDF" + (int)i, (TString)"SFittingResult_PDF" + (int)i, 6, 0, 6);
     SFittingResult[i]->SetBinContent(1, SPar[0]);
     SFittingResult[i]->SetBinContent(2, SPar[1]);
     SFittingResult[i]->SetBinContent(3, SPar[2]);
//     SFittingResult[i]->SetBinContent(4, SPar[3]);
//     SFittingResult[i]->SetBinContent(5, SPar[4]);
//     SFittingResult[i]->SetBinContent(6, SPar[5]);
     SFittingResult[i]->SetBinError(1, SParError[0]);
     SFittingResult[i]->SetBinError(2, SParError[1]);
     SFittingResult[i]->SetBinError(3, SParError[2]);
//     SFittingResult[i]->SetBinError(4, SParError[3]);
//     SFittingResult[i]->SetBinError(5, SParError[4]);
//     SFittingResult[i]->SetBinError(6, SParError[5]);

     SFittingResults.push_back(SFittingResult[i]);
   }

   TmpAFB[i] = (TH1D *)global_MC->Clone((TString)"TmpAFB_PDF" + (int)i);
   TmpAFB[i]->Reset();
   for(int ibin = 1; ibin <= AFB_uu->GetNbinsX(); ibin++){
     double Value1 = ResidualDilution_uu->GetBinContent(ibin) + SFittingResults.at(0)->GetBinContent(1);
     double Value2 = global_uuFittedSlope->GetBinContent(ibin) * SFittingResults.at(0)->GetBinContent(3) + global_uuFittedOffset->GetBinContent(ibin);

     double Value3 = ResidualDilution_dd->GetBinContent(ibin) + SFittingResults.at(0)->GetBinContent(2);
     double Value4 = global_ddFittedSlope->GetBinContent(ibin) * SFittingResults.at(0)->GetBinContent(3) + global_ddFittedOffset->GetBinContent(ibin);

     double Error1 = ResidualDilution_uu->GetBinError(ibin);
     double Error2 = AFB_uu->GetBinError(ibin);
     double Error3 = ResidualDilution_dd->GetBinError(ibin);
     double Error4 = AFB_dd->GetBinError(ibin);

     double Value = Value1 * Value2 + Value3 * Value4;
     double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

     TmpAFB[i]->SetBinContent(ibin, Value);
     TmpAFB[i]->SetBinError(ibin, DataAFB->GetBinError(ibin));
   }
   TmpAFBs.push_back(TmpAFB[i]);

/////////////////
   //cout<<"here?"<<endl;
////////////////

   writefile->cd();
   //SFittingResult[i]->Write();
   global_MC->Write((TString)"AFB_PDF" + (int)i);
   PDFAFBs.push_back(global_MC);

   MinChi2 = 100000.0;
 }


 TH1D* STWValue[59];
 vector<TH1D *> STWValues;

 TFile* file = new TFile(rootNames.at(0));

   TH1D* FZmass_uu = (TH1D *)file->Get(FZmass_uu_Name);
   TH1D* BZmass_uu = (TH1D *)file->Get(BZmass_uu_Name);
   FZmass_uu->Rebin(4);
   BZmass_uu->Rebin(4);
   TH1D* AFB_uu = (TH1D *)FZmass_uu->Clone(AFB_uu_Name);
   AFB_uu->Reset();
   AFBFunction(FZmass_uu, BZmass_uu, AFB_uu);

   TH1D* FZmass_dd = (TH1D *)file->Get(FZmass_dd_Name);
   TH1D* BZmass_dd = (TH1D *)file->Get(BZmass_dd_Name);
   FZmass_dd->Rebin(4);
   BZmass_dd->Rebin(4);
   TH1D* AFB_dd = (TH1D *)FZmass_dd->Clone(AFB_dd_Name);
   AFB_dd->Reset();
   AFBFunction(FZmass_dd, BZmass_dd, AFB_dd);

   TH1D* ZMass = (TH1D *)file->Get(Zmass_Name);
   ZMass->Rebin(4);

   TH1D* ZMass_uu = (TH1D *)file->Get(Zmass_uu_Name);
   TH1D* ZMass_dd = (TH1D *)file->Get(Zmass_dd_Name);
   TH1D* ZMass_ss = (TH1D *)file->Get(Zmass_ss_Name);
   TH1D* ZMass_cc = (TH1D *)file->Get(Zmass_cc_Name);
   TH1D* ZMass_bb = (TH1D *)file->Get(Zmass_bb_Name);
   TH1D* ZMass_uu_wrong = (TH1D *)file->Get(Zmass_uu_wrong_Name);
   TH1D* ZMass_uu_total = (TH1D *)file->Get(Zmass_uu_total_Name);
   TH1D* ZMass_dd_wrong = (TH1D *)file->Get(Zmass_dd_wrong_Name);
   TH1D* ZMass_dd_total = (TH1D *)file->Get(Zmass_dd_total_Name);
   TH1D* ZMass_ss_wrong = (TH1D *)file->Get(Zmass_ss_wrong_Name);
   TH1D* ZMass_ss_total = (TH1D *)file->Get(Zmass_ss_total_Name);
   TH1D* ZMass_cc_wrong = (TH1D *)file->Get(Zmass_cc_wrong_Name);
   TH1D* ZMass_cc_total = (TH1D *)file->Get(Zmass_cc_total_Name);
   TH1D* ZMass_bb_wrong = (TH1D *)file->Get(Zmass_bb_wrong_Name);
   TH1D* ZMass_bb_total = (TH1D *)file->Get(Zmass_bb_total_Name);

   TH1D* ZMass_utype_wrong = (TH1D *)ZMass_uu_wrong->Clone(Zmass_utype_wrong_Name);
   //ZMass_utype_wrong->Add(ZMass_cc_wrong);
   TH1D* ZMass_dtype_wrong = (TH1D *)ZMass_dd_wrong->Clone(Zmass_dtype_wrong_Name);
   //ZMass_dtype_wrong->Add(ZMass_ss_wrong);
   //ZMass_dtype_wrong->Add(ZMass_bb_wrong);

   TH1D* ZMass_utype_total = (TH1D *)ZMass_uu_total->Clone(Zmass_utype_total_Name);
   //ZMass_utype_total->Add(ZMass_cc_total);
   TH1D* ZMass_dtype_total = (TH1D *)ZMass_dd_total->Clone(Zmass_dtype_total_Name);
   //ZMass_dtype_total->Add(ZMass_ss_total);
   //ZMass_dtype_total->Add(ZMass_bb_total);

   ZMass_uu->Rebin(4);
   ZMass_dd->Rebin(4);
   ZMass_ss->Rebin(4);
   ZMass_cc->Rebin(4);
   ZMass_bb->Rebin(4);
   ZMass_uu_wrong->Rebin(4);
   ZMass_uu_total->Rebin(4);
   ZMass_dd_wrong->Rebin(4);
   ZMass_dd_total->Rebin(4);
   ZMass_ss_wrong->Rebin(4);
   ZMass_ss_total->Rebin(4);
   ZMass_cc_wrong->Rebin(4);
   ZMass_cc_total->Rebin(4);
   ZMass_bb_wrong->Rebin(4);
   ZMass_bb_total->Rebin(4);

   vector<TH1D *> Xsec = {ZMass_uu, ZMass_dd, ZMass_ss, ZMass_cc, ZMass_bb};
   TH1D* XsecFraction_uu = (TH1D *)ZMass_uu->Clone("XsecFraction_uu");
   XsecFraction_uu->Reset();
   TH1D* XsecFraction_dd = (TH1D *)ZMass_dd->Clone("XsecFraction_dd");
   XsecFraction_dd->Reset();

   GetXsecFraction(ZMass_uu, Xsec, XsecFraction_uu);
   GetXsecFraction(ZMass_dd, Xsec, XsecFraction_dd);

   TH1D* Dilution_uu = (TH1D *)ZMass_uu_wrong->Clone("Dilution_uu");
   Dilution_uu->Divide(ZMass_uu_total);
   TH1D* Dilution_dd = (TH1D *)ZMass_dd_wrong->Clone("Dilution_dd");
   Dilution_dd->Divide(ZMass_dd_total);

   TH1D* CoefficientDilution_uu;
   TH1D* CoefficientDilution_dd;
   TH1D* CoefficientDilution_ss;
   TH1D* CoefficientDilution_cc;
   TH1D* CoefficientDilution_bb;
   TH1D* CoefficientDilution_utype;
   TH1D* CoefficientDilution_dtype;

   TH1D* DilutionAverage_uu;
   TH1D* DilutionAverage_dd;
   TH1D* DilutionAverage_ss;
   TH1D* DilutionAverage_cc;
   TH1D* DilutionAverage_bb;
   TH1D* DilutionAverage_utype;
   TH1D* DilutionAverage_dtype;

   TH1D* ResidualDilution_uu;
   TH1D* ResidualDilution_dd;
   TH1D* ResidualDilution_ss;
   TH1D* ResidualDilution_cc;
   TH1D* ResidualDilution_bb;
   TH1D* ResidualDilution_utype;
   TH1D* ResidualDilution_dtype;

//   GetCoefficientDilution(Dilution_uu, XsecFraction_uu, CoefficientDilution_uu);
//   GetCoefficientDilution(Dilution_dd, XsecFraction_dd, CoefficientDilution_dd);
   GetCoefficientDilution(ZMass_uu_wrong, ZMass_uu_total, ZMass, CoefficientDilution_uu);
   GetCoefficientDilution(ZMass_dd_wrong, ZMass_dd_total, ZMass, CoefficientDilution_dd);
   GetCoefficientDilution(ZMass_ss_wrong, ZMass_ss_total, ZMass, CoefficientDilution_ss);
   GetCoefficientDilution(ZMass_cc_wrong, ZMass_cc_total, ZMass, CoefficientDilution_cc);
   GetCoefficientDilution(ZMass_bb_wrong, ZMass_bb_total, ZMass, CoefficientDilution_bb);
   GetCoefficientDilution(ZMass_utype_wrong, ZMass_utype_total, ZMass, CoefficientDilution_utype);
   GetCoefficientDilution(ZMass_dtype_wrong, ZMass_dtype_total, ZMass, CoefficientDilution_dtype);

   GetDilutionAverage(CoefficientDilution_uu, DilutionAverage_uu, ResidualDilution_uu);
   GetDilutionAverage(CoefficientDilution_dd, DilutionAverage_dd, ResidualDilution_dd);
   GetDilutionAverage(CoefficientDilution_ss, DilutionAverage_ss, ResidualDilution_ss);
   GetDilutionAverage(CoefficientDilution_cc, DilutionAverage_cc, ResidualDilution_cc);
   GetDilutionAverage(CoefficientDilution_bb, DilutionAverage_bb, ResidualDilution_bb);
   GetDilutionAverage(CoefficientDilution_utype, DilutionAverage_utype, ResidualDilution_utype);
   GetDilutionAverage(CoefficientDilution_dtype, DilutionAverage_dtype, ResidualDilution_dtype);

   global_Dilution_uu_Residual = ResidualDilution_uu;
   global_Dilution_dd_Residual = ResidualDilution_dd;
//   global_Dilution_uu_Residual = ResidualDilution_utype;
//   global_Dilution_dd_Residual = ResidualDilution_dtype;
//   global_Dilution_ss_Residual = ResidualDilution_ss;
//   global_Dilution_cc_Residual = ResidualDilution_cc;
//   global_Dilution_bb_Residual = ResidualDilution_bb;

   global_AFB_uu = AFB_uu;
   global_AFB_dd = AFB_dd;

 for(int i = 0; i < 59; i++){
   global_Data = (TH1D *)TmpAFBs.at(i)->Clone(AFBName + "_Tmp_PDF" + (int)i);

   TMinuitHelper *myMinuit = new TMinuitHelper(3);
   myMinuit->SetFCN(udDilutionFitting);
   myMinuit->Input(0, "Su", SFittingResults.at(0)->GetBinContent(1), 0.0, 0.0, 0.5);
   myMinuit->Input(1, "Sd", SFittingResults.at(0)->GetBinContent(2), 0.0, 0.0, 0.5);
   myMinuit->Input(2, "Stw", 0.2315, 0.01, 0.23, 0.24);
//   myMinuit->Input(3, "Ss", SFittingResults.at(0)->GetBinContent(4), 0.0, 0.0, 0.5);
//   myMinuit->Input(4, "Sc", SFittingResults.at(0)->GetBinContent(5), 0.0, 0.0, 0.5);
//   myMinuit->Input(5, "Sb", SFittingResults.at(0)->GetBinContent(6), 0.0, 0.0, 0.5);
   myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
   myMinuit->Exec("MIGRAD", 100000, 0.001);
   myMinuit->GetParameter();
   double* SPar = new double[3];
   myMinuit->GetParameters(SPar);

   STWValue[i] = new TH1D((TString)"STWValueResult_PDF" + (int)i, (TString)"STWValueResult_PDF" + (int)i, 1, 0, 1);
   STWValue[i]->SetBinContent(1, SPar[2]);
   STWValue[i]->SetBinError(1, 0);

   STWValues.push_back(STWValue[i]);

   MinChi2 = 100000.0;
 }


/* TH1D* STWAFB[40];
 vector<TH1D *> STWAFBs;
 for(int i = 0; i < 40; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   STWAFB[i] = (TH1D *)file->Get(AFBName);

   STWAFBs.push_back(STWAFB[i]);

   writefile->cd();
   STWAFB[i]->Write((TString)"AFB_STW" + (int)i);
 }

 double AFBPDFUnc = 0.0;
 CompareDataTheory *run = new CompareDataTheory();
 run->LinkOutFile(writefile);
 run->GetPDFUncertainty(PDFAFBs, STWAFBs, AFBPDFUnc);

 TH1D *Chi2_FittedSuSd = new TH1D("Chi2_FittedSuSd", "Chi2_FittedSuSd", 40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);
 TF1 *Fitting;
 for(int i = 0; i < STWAFBs.size(); i++){
   double Chi2 = CalculateChi2(DataAFB, STWAFBs.at(i));
   Chi2_FittedSuSd->SetBinContent(i, Chi2);
 }
 double stwFittedSuSd, stwErrorFittedSuSd;
 Chi2Fitting(Chi2_FittedSuSd, Fitting, stwFittedSuSd, stwErrorFittedSuSd);

 cout<<"FittedSuSd: "<<endl;
 cout<<"Central value: "<<stwFittedSuSd<<" Stat.unc: "<<stwErrorFittedSuSd<<" PDF unc: "<<AFBPDFUnc<<endl;
*/

/* TH1D *SFittingResultError;
 PDFUncertainty *SFittingResultPDFunc;
 SFittingResultPDFunc = new PDFUncertainty();
 SFittingResultPDFunc->SaveVariBin();
 SFittingResultPDFunc->Input1DPlot("Symmetry", SFittingResults, SFittingResultError);
 cout<<"Central value: "<<SFittingResults.at(0)->GetBinContent(3)<<" PDF unc: "<<SFittingResultError->GetBinContent(3)<<endl;
*/
 TH1D *STWValueError;
 PDFUncertainty *STWValuePDFunc;
 STWValuePDFunc = new PDFUncertainty();
 STWValuePDFunc->SaveVariBin();
 STWValuePDFunc->Input1DPlot("Symmetry", STWValues, STWValueError);
 cout<<"MC uubar P0: "<<AverageDilution_uus.at(0)->GetBinContent(1)<<endl;
 cout<<"MC ddbar P0: "<<AverageDilution_dds.at(0)->GetBinContent(1)<<endl;
// cout<<"MC ssbar P0: "<<AverageDilution_sss.at(0)->GetBinContent(1)<<endl;
// cout<<"MC ccbar P0: "<<AverageDilution_ccs.at(0)->GetBinContent(1)<<endl;
// cout<<"MC bbbar P0: "<<AverageDilution_bbs.at(0)->GetBinContent(1)<<endl;
 cout<<"uubar P0: "<<SFittingResults.at(0)->GetBinContent(1)<<" error: "<<SFittingResults.at(0)->GetBinError(1)<<endl;
 cout<<"ddbar P0: "<<SFittingResults.at(0)->GetBinContent(2)<<" error: "<<SFittingResults.at(0)->GetBinError(2)<<endl;
// cout<<"ssbar P0: "<<SFittingResults.at(0)->GetBinContent(4)<<" error: "<<SFittingResults.at(0)->GetBinError(4)<<endl;
// cout<<"ccbar P0: "<<SFittingResults.at(0)->GetBinContent(5)<<" error: "<<SFittingResults.at(0)->GetBinError(5)<<endl;
// cout<<"bbbar P0: "<<SFittingResults.at(0)->GetBinContent(6)<<" error: "<<SFittingResults.at(0)->GetBinError(6)<<endl;
 cout<<"Central value: "<<SFittingResults.at(0)->GetBinContent(3)<<" error: "<<SFittingResults.at(0)->GetBinError(3)<<endl;
 cout<<"Central value: "<<STWValues.at(0)->GetBinContent(1)<<" PDF unc: "<<STWValueError->GetBinContent(1)<<endl;


// TH1D* AveAFB_Error;
// PDFUncertainty *AveAFBunc;
// AveAFBunc = new PDFUncertainty();
// AveAFBunc->Input1DPlot("Symmetry", AveAFBHists, AveAFB_Error);
// cout<<"Average AFB: "<<AveAFBHists.at(0)->GetBinContent(1)<<endl;
// cout<<"Average AFB PDF unc: "<<AveAFB_Error->GetBinContent(1)<<endl;

// TH1D* AFBunc_Error;
// PDFUncertainty *AFBunc;
// AFBunc = new PDFUncertainty();
// AFBunc->Input1DPlot("Symmetry", PDFHists, AFBunc_Error);


/////////////////////////////////////////////////////////////////////////////////////////
 TH1D* uuDilution[59];
 vector<TH1D *> uuDilutions;

 TH1D* ddDilution[59];
 vector<TH1D *> ddDilutions;

 TH1D* uuAveDilution[59];
 vector<TH1D *> uuAveDilutions;

 TH1D* ddAveDilution[59];
 vector<TH1D *> ddAveDilutions;

 TH1D* AFB_Hadron[59];
 vector<TH1D *> AFB_Hadrons;

 TH1D* AFB_uu_Central;
 TH1D* AFB_dd_Central;
 for(int i = 0; i < 59; i++){
   TFile* file = new TFile(rootNames.at(i));
   TH1D* Dilution_uu = (TH1D *)file->Get(Dilution_uu_Name);
   TH1D* Dilution_dd = (TH1D *)file->Get(Dilution_dd_Name);
   TH1D* AveDilution_uu = (TH1D *)file->Get(AveDilution_uu_Name);
   TH1D* AveDilution_dd = (TH1D *)file->Get(AveDilution_dd_Name);
   TH1D* AFB_uu = (TH1D *)file->Get(AFB_uu_Name);
   TH1D* AFB_dd = (TH1D *)file->Get(AFB_dd_Name);
   TH1D* AFB = (TH1D *)file->Get(AFBName);

   uuDilution[i] = (TH1D *)Dilution_uu->Clone((TString)"uuDilution_PDF" + (int)i);
   ddDilution[i] = (TH1D *)Dilution_dd->Clone((TString)"ddDilution_PDF" + (int)i);
   uuAveDilution[i] = (TH1D *)AveDilution_uu->Clone((TString)"uuAveDilution_PDF" + (int)i);
   ddAveDilution[i] = (TH1D *)AveDilution_dd->Clone((TString)"ddAveDilution_PDF" + (int)i);
   if(i == 0) AFB_uu_Central = (TH1D *)AFB_uu->Clone((TString)"AFB_uu_Central");
   if(i == 0) AFB_dd_Central = (TH1D *)AFB_dd->Clone((TString)"AFB_dd_Central");
   AFB_Hadron[i] = (TH1D *)AFB->Clone((TString)"AFB_Hadron_PDF" + (int)i);


   uuDilutions.push_back(uuDilution[i]);
   ddDilutions.push_back(ddDilution[i]);
   uuAveDilutions.push_back(uuAveDilution[i]);
   ddAveDilutions.push_back(ddAveDilution[i]);
   AFB_Hadrons.push_back(AFB_Hadron[i]);

   writefile->cd();
 }

 TH1D* AFB_Central;
 AFB_Central = (TH1D *)AFB_Hadrons.at(0)->Clone("AFB_Central");
 AFB_Central->Reset();

 TH1D* AFB_Central_PDFError;
 AFB_Central_PDFError = (TH1D *)AFB_Hadrons.at(0)->Clone("AFB_Central_PDFError");
 AFB_Central_PDFError->Reset();

 TH1D *uuDilution_AFB;
 TH1D *uuDilutionError;
 PDFUncertainty *uuDilutionPDFunc;
 uuDilutionPDFunc = new PDFUncertainty();
 uuDilutionPDFunc->Input1DPlot("Symmetry", uuDilutions, uuDilutionError);
 uuDilution_AFB = (TH1D *)uuDilutionError->Clone("uuDilution_AFB");
 uuDilution_AFB->Reset();

 TH1D *ddDilution_AFB;
 TH1D *ddDilutionError;
 PDFUncertainty *ddDilutionPDFunc;
 ddDilutionPDFunc = new PDFUncertainty();
 ddDilutionPDFunc->Input1DPlot("Symmetry", ddDilutions, ddDilutionError);
 ddDilution_AFB = (TH1D *)ddDilutionError->Clone("ddDilution_AFB");
 ddDilution_AFB->Reset();

 TH1D *uuAveDilution_AFB;
 TH1D *uuAveDilutionError;
 TH1D *uuAveDilutionAFBError;
 PDFUncertainty *uuAveDilutionPDFunc;
 uuAveDilutionPDFunc = new PDFUncertainty();
 uuAveDilutionPDFunc->Input1DPlot("Symmetry", uuAveDilutions, uuAveDilutionError);
 uuAveDilution_AFB = (TH1D *)AFB_Hadrons.at(0)->Clone("uuAveDilution_AFB");
 uuAveDilution_AFB->Reset();
 uuAveDilutionAFBError = (TH1D *)AFB_Hadrons.at(0)->Clone("uuAveDilutionAFBError");
 uuAveDilutionAFBError->Reset();


 TH1D *ddAveDilution_AFB;
 TH1D *ddAveDilutionError;
 TH1D *ddAveDilutionAFBError;
 PDFUncertainty *ddAveDilutionPDFunc;
 ddAveDilutionPDFunc = new PDFUncertainty();
 ddAveDilutionPDFunc->Input1DPlot("Symmetry", ddAveDilutions, ddAveDilutionError);
 ddAveDilution_AFB = (TH1D *)AFB_Hadrons.at(0)->Clone("ddAveDilution_AFB");
 ddAveDilution_AFB->Reset();
 ddAveDilutionAFBError = (TH1D *)AFB_Hadrons.at(0)->Clone("ddAveDilutionAFBError");
 ddAveDilutionAFBError->Reset();

 TH1D *AFBHadronError;
 PDFUncertainty *AFBHadronPDFunc;
 AFBHadronPDFunc = new PDFUncertainty();
 AFBHadronPDFunc->Input1DPlot("Symmetry", AFB_Hadrons, AFBHadronError);

 for(int ibin = 1; ibin <= AFB_uu_Central->GetNbinsX(); ibin++){
   double Value1 = uuDilutions.at(0)->GetBinContent(ibin) + uuAveDilutions.at(0)->GetBinContent(1);
   double Value2 = AFB_uu_Central->GetBinContent(ibin);
   double Value3 = ddDilutions.at(0)->GetBinContent(ibin) + ddAveDilutions.at(0)->GetBinContent(1);
   double Value4 = AFB_dd_Central->GetBinContent(ibin);

   double Value = fabs(Value1 * Value2 + Value3 * Value4 - AFB_Hadrons.at(0)->GetBinContent(ibin)) / fabs(AFB_Hadrons.at(0)->GetBinContent(ibin));

   AFB_Central->SetBinContent(ibin, Value1 * Value2 + Value3 * Value4);
   AFB_Central->SetBinError(ibin, 0.0);
 }

 for(int ibin = 1; ibin <= AFB_uu_Central->GetNbinsX(); ibin++){
   double Value1 = uuDilutions.at(0)->GetBinContent(ibin) + uuAveDilutions.at(0)->GetBinContent(1) + uuDilutionError->GetBinContent(ibin);
   double Value2 = AFB_uu_Central->GetBinContent(ibin);
   double Value3 = ddDilutions.at(0)->GetBinContent(ibin) + ddAveDilutions.at(0)->GetBinContent(1);
   double Value4 = AFB_dd_Central->GetBinContent(ibin);
   double Value5 = AFB_uu_Central->GetBinContent(ibin) * uuDilutionError->GetBinContent(ibin);

   double Value = fabs(Value1 * Value2 + Value3 * Value4 - AFB_Hadrons.at(0)->GetBinContent(ibin)) / fabs(AFB_Hadrons.at(0)->GetBinContent(ibin));

   uuDilution_AFB->SetBinContent(ibin, Value1 * Value2 + Value3 * Value4);
   uuDilutionError->SetBinContent(ibin, fabs(Value5));
   uuDilutionError->SetBinError(ibin, 0.0);
 }

 for(int ibin = 1; ibin <= AFB_uu_Central->GetNbinsX(); ibin++){
   double Value1 = uuDilutions.at(0)->GetBinContent(ibin) + uuAveDilutions.at(0)->GetBinContent(1) + uuAveDilutionError->GetBinContent(1);
   double Value2 = AFB_uu_Central->GetBinContent(ibin);
   double Value3 = ddDilutions.at(0)->GetBinContent(ibin) + ddAveDilutions.at(0)->GetBinContent(1);
   double Value4 = AFB_dd_Central->GetBinContent(ibin);
   double Value5 = AFB_uu_Central->GetBinContent(ibin) * uuAveDilutionError->GetBinContent(1);

   double Value = fabs(Value1 * Value2 + Value3 * Value4 - AFB_Hadrons.at(0)->GetBinContent(ibin)) / fabs(AFB_Hadrons.at(0)->GetBinContent(ibin));

   uuAveDilution_AFB->SetBinContent(ibin, Value1 * Value2 + Value3 * Value4);
   uuAveDilutionAFBError->SetBinContent(ibin, fabs(Value5));
 }

 for(int ibin = 1; ibin <= AFB_uu_Central->GetNbinsX(); ibin++){
   double Value1 = uuDilutions.at(0)->GetBinContent(ibin) + uuAveDilutions.at(0)->GetBinContent(1);
   double Value2 = AFB_uu_Central->GetBinContent(ibin);
   double Value3 = ddDilutions.at(0)->GetBinContent(ibin) + ddAveDilutions.at(0)->GetBinContent(1) + ddDilutionError->GetBinContent(ibin);
   double Value4 = AFB_dd_Central->GetBinContent(ibin);
   double Value5 = AFB_dd_Central->GetBinContent(ibin) * ddDilutionError->GetBinContent(ibin);

   double Value = fabs(Value1 * Value2 + Value3 * Value4 - AFB_Hadrons.at(0)->GetBinContent(ibin)) / fabs(AFB_Hadrons.at(0)->GetBinContent(ibin));

   ddDilution_AFB->SetBinContent(ibin, Value1 * Value2 + Value3 * Value4);
   ddDilutionError->SetBinContent(ibin, fabs(Value5));
 }

 for(int ibin = 1; ibin <= AFB_uu_Central->GetNbinsX(); ibin++){
   double Value1 = uuDilutions.at(0)->GetBinContent(ibin) + uuAveDilutions.at(0)->GetBinContent(1);
   double Value2 = AFB_uu_Central->GetBinContent(ibin);
   double Value3 = ddDilutions.at(0)->GetBinContent(ibin) + ddAveDilutions.at(0)->GetBinContent(1) + ddAveDilutionError->GetBinContent(1);
   double Value4 = AFB_dd_Central->GetBinContent(ibin);
   double Value5 = AFB_dd_Central->GetBinContent(ibin) * ddAveDilutionError->GetBinContent(1);

   double Value = fabs(Value1 * Value2 + Value3 * Value4 - AFB_Hadrons.at(0)->GetBinContent(ibin)) / fabs(AFB_Hadrons.at(0)->GetBinContent(ibin));

   ddAveDilution_AFB->SetBinContent(ibin, Value1 * Value2 + Value3 * Value4);
   ddAveDilutionAFBError->SetBinContent(ibin, fabs(Value5));
 }

 for(int ibin = 1; ibin <= AFB_uu_Central->GetNbinsX(); ibin++){
   double Value1 = uuDilutionError->GetBinContent(ibin) + uuAveDilutionError->GetBinContent(1);
   double Value2 = AFB_uu_Central->GetBinContent(ibin);
   double Value3 = ddDilutionError->GetBinContent(ibin) + ddAveDilutionError->GetBinContent(1);
   double Value4 = AFB_dd_Central->GetBinContent(ibin);

   double Value = fabs(Value1 * Value2 + Value3 * Value4);

   AFB_Central_PDFError->SetBinContent(ibin, Value);
   AFB_Central_PDFError->SetBinError(ibin, 0.0);
 }

////////////////////////////////////////////////////////////////////////////////////////////

 writefile->cd();
 writefile->Write();
 writefile->Close();

 return 1;

}
