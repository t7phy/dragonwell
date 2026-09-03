#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "Uncertainty/FitAFBStw.h"
#include "CompareDataTheory/CompareDataTheory.h"
#include "TMinuitHelper/TMinuitHelper.h"
#include "PDFHelper/PDFReweight.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "Tools/Tools.h"

using namespace std;

TH1D* global_Dilution_uu_Residual;
TH1D* global_Dilution_dd_Residual;
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

// TH1D* AFB_uu = (TH1D *)global_AFB_uu->Rebin(10, "AFB_uu", xbins);
// TH1D* AFB_dd = (TH1D *)global_AFB_dd->Rebin(10, "AFB_dd", xbins);
// TH1D* Dilution_uu = (TH1D *)global_Dilution_uu_Residual->Rebin(10, "Dilution_uu_Residual", xbins);
// TH1D* Dilution_dd = (TH1D *)global_Dilution_dd_Residual->Rebin(10, "Dilution_dd_Residual", xbins);

 Dilution_uu->Reset();
 Dilution_dd->Reset();

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

 TH1D* AFB = (TH1D *)AFB_uu->Clone("AFB_Hadron");
 AFB->Reset();

 global_AFBCalc->InputStw(par[2]);

 for(int ibin = 1; ibin <= AFB_uu->GetNbinsX(); ibin++){
   double BinLeft = AFB_uu->GetXaxis()->GetBinLowEdge(ibin);
   double BinRight = AFB_uu->GetXaxis()->GetBinUpEdge(ibin);

   double Value1 = Dilution_uu->GetBinContent(ibin);
   double Value2 = global_uuFittedSlope->GetBinContent(ibin) * par[2] + global_uuFittedOffset->GetBinContent(ibin);
//   double Value2 = global_uuFittedSlope->GetBinContent(ibin) * 0.2315 + global_uuFittedOffset->GetBinContent(ibin);
//   double Value2 = global_AFBCalc->GetQuarkAFB(BinLeft, BinRight, 1000);

   double Value3 = Dilution_dd->GetBinContent(ibin);
   double Value4 = global_ddFittedSlope->GetBinContent(ibin) * par[2] + global_ddFittedOffset->GetBinContent(ibin);
//   double Value4 = global_ddFittedSlope->GetBinContent(ibin) * 0.2315 + global_ddFittedOffset->GetBinContent(ibin);
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

 TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/i2Tn3.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/250M/i2Tn3.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/FullAFB_RotatedCT18NNLO_LHA.01/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/STWTemplate/0.2303/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/STWTemplate/250M/0.2324/MC_results.root";

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

 TFile *DataFile = new TFile(DataName);

 TH1D *DataAFB = (TH1D *)DataFile->Get(AFBName);
 TH1D *DataAFB_uu = (TH1D *)DataFile->Get(AFB_uu_Name);
 TH1D *DataAFB_dd = (TH1D *)DataFile->Get(AFB_dd_Name);

 TH1D *Data_uuEpsilon = (TH1D *)DataFile->Get(Dilution_uu_Name);
 TH1D *Data_ddEpsilon = (TH1D *)DataFile->Get(Dilution_dd_Name);

 global_Data = (TH1D *)DataAFB->Clone(AFBName);

 writefile->cd();
 DataAFB->Write();


////////////////////////////////////////////////////////////////
 double STWInput[40];
 for(int i = 0; i < 40; i++){
   STWInput[i] = 0.2255 + i * 0.0003;
 }

 int FirstSTW = 0;
 int LastSTW = 40;

 TH1D* uuAFB[40];
 vector<TH1D *> uuAFBs;
 for(int i = FirstSTW; i < LastSTW; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   uuAFB[i] = (TH1D *)file->Get(AFB_uu_Name);

   uuAFBs.push_back(uuAFB[i]);

   writefile->cd();
   uuAFB[i]->Write((TString)"AFB_uu_STW" + (int)i);
 }

 TH1D* ddAFB[40];
 vector<TH1D *> ddAFBs;
 for(int i = FirstSTW; i < LastSTW; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   ddAFB[i] = (TH1D *)file->Get(AFB_dd_Name);

   ddAFBs.push_back(ddAFB[i]);

   writefile->cd();
   ddAFB[i]->Write((TString)"AFB_dd_STW" + (int)i);
 }

 TH1D* HadronAFB[40];
 vector<TH1D *> HadronAFBs;
 for(int i = FirstSTW; i < LastSTW; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   HadronAFB[i] = (TH1D *)file->Get(AFBName);

   HadronAFBs.push_back(HadronAFB[i]);

   writefile->cd();
   HadronAFB[i]->Write((TString)"AFB_STW" + (int)i);
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

 TH1D* Chi2Plot_uu = new TH1D("Chi2Plot_uu", "Chi2Plot_uu", LastSTW - FirstSTW, STWInput[FirstSTW] - 0.0003 / 2.0, STWInput[LastSTW - 1] + 0.0003 / 2.0);

 for(int ibin = 1; ibin <= Chi2Plot_uu->GetNbinsX(); ibin++){
   TH1D* tmpAFB = (TH1D *)DataAFB_uu->Clone("tmpAFB_uu");
   tmpAFB->Reset();
   for(int imass = 1; imass <= tmpAFB->GetNbinsX(); imass++){
     double Value = uuFittedSlope->GetBinContent(imass) * Chi2Plot_uu->GetBinCenter(ibin) + uuFittedOffset->GetBinContent(imass);
     double Error = uuFittedSlope->GetBinError(imass) * Chi2Plot_uu->GetBinCenter(ibin);

     tmpAFB->SetBinContent(imass, Value);
     tmpAFB->SetBinError(imass, Error);
   }
   double Chi2 = CalculateChi2(tmpAFB, DataAFB_uu);
   Chi2Plot_uu->SetBinContent(ibin, Chi2);
 }

 TH1D* Chi2Plot_dd = new TH1D("Chi2Plot_dd", "Chi2Plot_dd", LastSTW - FirstSTW, STWInput[FirstSTW] - 0.0003 / 2.0, STWInput[LastSTW - 1] + 0.0003 / 2.0);

 for(int ibin = 1; ibin <= Chi2Plot_dd->GetNbinsX(); ibin++){
   TH1D* tmpAFB = (TH1D *)DataAFB_dd->Clone("tmpAFB_dd");
   tmpAFB->Reset();
   for(int imass = 1; imass <= tmpAFB->GetNbinsX(); imass++){
     double Value = ddFittedSlope->GetBinContent(imass) * Chi2Plot_dd->GetBinCenter(ibin) + ddFittedOffset->GetBinContent(imass);
     double Error = ddFittedSlope->GetBinError(imass) * Chi2Plot_dd->GetBinCenter(ibin);

     tmpAFB->SetBinContent(imass, Value);
     tmpAFB->SetBinError(imass, Error);
   }
   double Chi2 = CalculateChi2(tmpAFB, DataAFB_dd);
   Chi2Plot_dd->SetBinContent(ibin, Chi2);
 }


 TF1* fitting_uu;
 Chi2Fitting(Chi2Plot_uu, fitting_uu);

 TF1* fitting_dd;
 Chi2Fitting(Chi2Plot_dd, fitting_dd);



 TH1D* STWValue[59];
 vector<TH1D *> STWValues;

 TH1D* PuValue[59];
 vector<TH1D *> PuValues;

 TH1D* PdValue[59];
 vector<TH1D *> PdValues;

 for(int i = 0; i < 59; i++){
   TFile* file = new TFile(rootNames.at(i));

   TH1D* AFB = (TH1D *)file->Get(AFBName);
   PuValue[i] = (TH1D *)file->Get(AveDilution_uu_Name);
   PdValue[i] = (TH1D *)file->Get(AveDilution_dd_Name);

   TH1D* Chi2Plot = new TH1D("Chi2Plot", "Chi2Plot", LastSTW - FirstSTW, STWInput[FirstSTW] - 0.0003 / 2.0, STWInput[LastSTW - 1] + 0.0003 / 2.0);

   for(int ibin = 1; ibin <= Chi2Plot_dd->GetNbinsX(); ibin++){
     double Chi2 = CalculateChi2(AFB, HadronAFBs.at(ibin - 1));
     Chi2Plot->SetBinContent(ibin, Chi2);
   }
   double stw, stwError;
   TF1* fitting;
   Chi2Fitting(Chi2Plot, fitting, stw, stwError);

   STWValue[i] = new TH1D((TString)"STWValueResult_PDF" + (int)i, (TString)"STWValueResult_PDF" + (int)i, 1, 0, 1);
   STWValue[i]->SetBinContent(1, stw);
   STWValue[i]->SetBinError(1, stwError);

   STWValues.push_back(STWValue[i]);
   PuValues.push_back(PuValue[i]);
   PdValues.push_back(PdValue[i]);
 }

 TH1D *STWValueError;
 PDFUncertainty *STWValuePDFunc;
 STWValuePDFunc = new PDFUncertainty();
 STWValuePDFunc->SaveVariBin();
 STWValuePDFunc->Input1DPlot("Symmetry", STWValues, STWValueError);

 TH1D *PuValueError;
 PDFUncertainty *PuValuePDFunc;
 PuValuePDFunc = new PDFUncertainty();
 PuValuePDFunc->SaveVariBin();
 PuValuePDFunc->Input1DPlot("Symmetry", PuValues, PuValueError);

 TH1D *PdValueError;
 PDFUncertainty *PdValuePDFunc;
 PdValuePDFunc = new PDFUncertainty();
 PdValuePDFunc->SaveVariBin();
 PdValuePDFunc->Input1DPlot("Symmetry", PdValues, PdValueError);

 FileForEPUMP* STWValueFile;
 STWValueFile = new FileForEPUMP("STWValue");
 STWValueFile->InputData(STWValues.at(0));
 STWValueFile->InputTheory(STWValuePDFunc);
 STWValueFile->writedata();
 STWValueFile->writetheory();

 FileForEPUMP* PuValueFile;
 PuValueFile = new FileForEPUMP("PuValue");
 PuValueFile->InputData(PuValues.at(0));
 PuValueFile->InputTheory(PuValuePDFunc);
 PuValueFile->writedata();
 PuValueFile->writetheory();

 FileForEPUMP* PdValueFile;
 PdValueFile = new FileForEPUMP("PdValue");
 PdValueFile->InputData(PdValues.at(0));
 PdValueFile->InputTheory(PdValuePDFunc);
 PdValueFile->writedata();
 PdValueFile->writetheory();


////////////////////////////////////////////////////////////////////////////////////////////

 writefile->cd();
 writefile->Write();
 writefile->Close();

 return 1;

}
