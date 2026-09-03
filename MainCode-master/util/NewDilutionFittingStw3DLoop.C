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

TH3D* global_Dilution_uu_Residual;
TH3D* global_Dilution_dd_Residual;
TH3D* global_AFB_uu;
TH3D* global_AFB_dd;
TH3D* global_Dilution_uu_Average;
TH3D* global_Dilution_dd_Average;
TH3D* global_uuFittedSlope;
TH3D* global_uuFittedOffset;
TH3D* global_ddFittedSlope;
TH3D* global_ddFittedOffset;
PDFReweight *global_AFBCalc;

vector<double> random_uu;
vector<double> random_dd;

TH3D* global_MC;
TH3D* global_Data;

TH3D* global_TmpAFB;

int global_FirstYbin;
int global_LastYbin;
int global_FirstQTbin;
int global_LastQTbin;

double global_FittedPu;
double global_FittedPd;
double global_PuError;
double global_PdError;
double global_Correlation;

double MinChi2 = 100000.0;

void udDilutionFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 double Chi2 = 0.0;

 TH3D* AFB_uu = (TH3D *)global_AFB_uu->Clone("AFB_uu");
 TH3D* AFB_dd = (TH3D *)global_AFB_dd->Clone("AFB_dd");
 TH3D* Dilution_uu = (TH3D *)global_Dilution_uu_Residual->Clone("Dilution_uu_Residual");
 TH3D* Dilution_dd = (TH3D *)global_Dilution_dd_Residual->Clone("Dilution_dd_Residual");

 Dilution_uu->Reset();
 Dilution_dd->Reset();

 for(int ibinx = 1; ibinx <= Dilution_uu->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= Dilution_uu->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= Dilution_uu->GetNbinsZ(); ibinz++){
       int Index = (ibiny - 1) * AFB_uu->GetNbinsZ() * 2 + (ibinz - 1) * 2 + 1;

       double Value = global_Dilution_uu_Residual->GetBinContent(ibinx, ibiny, ibinz) + par[Index];
       double Error = global_Dilution_uu_Residual->GetBinError(ibinx, ibiny, ibinz);
       Dilution_uu->SetBinContent(ibinx, ibiny, ibinz, Value);
       Dilution_uu->SetBinError(ibinx, ibiny, ibinz, Error);
     }
   }
 }

 for(int ibinx = 1; ibinx <= Dilution_uu->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= Dilution_uu->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= Dilution_uu->GetNbinsZ(); ibinz++){
       int Index = (ibiny - 1) * AFB_uu->GetNbinsZ() * 2 + (ibinz - 1) * 2 + 2;

       double Value = global_Dilution_dd_Residual->GetBinContent(ibinx, ibiny, ibinz) + par[Index];
       double Error = global_Dilution_dd_Residual->GetBinError(ibinx, ibiny, ibinz);
       Dilution_dd->SetBinContent(ibinx, ibiny, ibinz, Value);
       Dilution_dd->SetBinError(ibinx, ibiny, ibinz, Error);
     }
   }
 }

 TH3D* AFB = (TH3D *)AFB_uu->Clone("AFB_Hadron");
 AFB->Reset();

 TRandom3 random(0);

 double myR = 0.0;

 for(int ibinx = 1; ibinx <= AFB_uu->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= AFB_uu->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= AFB_uu->GetNbinsZ(); ibinz++){

       double Value1 = Dilution_uu->GetBinContent(ibinx, ibiny, ibinz);
       double Value2 = global_uuFittedSlope->GetBinContent(ibinx, ibiny, ibinz) * par[0] + global_uuFittedOffset->GetBinContent(ibinx, ibiny, ibinz);

       double Value3 = Dilution_dd->GetBinContent(ibinx, ibiny, ibinz);
       double Value4 = global_ddFittedSlope->GetBinContent(ibinx, ibiny, ibinz) * par[0] + global_ddFittedOffset->GetBinContent(ibinx, ibiny, ibinz);

//       double Error1 = Dilution_uu->GetBinError(ibin);
       double Error1 = 0.0;
//       double Error2 = global_uuFittedSlope->GetBinError(ibin) * par[2];
       double Error2 = 0.0;

//       double Error3 = Dilution_dd->GetBinError(ibin);
       double Error3 = 0.0;
//       double Error4 = global_ddFittedSlope->GetBinError(ibin) * par[2];
       double Error4 = 0.0;

       double Value = Value1 * Value2 + Value3 * Value4;
       double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

       AFB->SetBinContent(ibinx, ibiny, ibinz, Value);
       AFB->SetBinError(ibinx, ibiny, ibinz, Error);
     }
   }
 }

 Chi2 = CalculateChi2(global_Data, AFB, global_FirstYbin, global_LastYbin, global_FirstQTbin, global_LastQTbin);

 f = Chi2;
 if(f < MinChi2) MinChi2 = f;

 global_MC = (TH3D *)AFB->Clone("Global_AFB_Hadron");

 delete AFB_uu;
 delete AFB_dd;
 delete Dilution_uu;
 delete Dilution_dd;
 delete AFB;

 cout<<"Min Chi2 = "<<MinChi2<<endl;
}

void GetAFBStwLinear()
{
 TString rootName;

 vector<TString> STWTemplates;

 ifstream infile;
  infile.open("STWTemplate.list",ios::in);
 while(infile>>rootName){
  STWTemplates.push_back(rootName);
 }

 TString AFB_uu_Name = "AFB_ZMass_ZY_QT_uu";
 TString AFB_dd_Name = "AFB_ZMass_ZY_QT_dd";

 map<int, double> STWInput;
 map<double, int> FindSTW;
 for(int i = 0; i < 40; i++){
   STWInput[i] = 0.2255 + i * 0.0003;
 }

 int FirstSTW = 15;
 int LastSTW = 30;

 int Index = 0;

 TH3D* uuAFB[40];
 vector<TH3D *> uuAFBs;
 for(int i = FirstSTW; i < LastSTW; i++){

   FindSTW[STWInput[i]] = Index;
   Index++;

   TFile* file = new TFile(STWTemplates.at(i));
   uuAFB[i] = (TH3D *)file->Get(AFB_uu_Name);

   uuAFBs.push_back(uuAFB[i]);
 }

 TH3D* ddAFB[40];
 vector<TH3D *> ddAFBs;
 for(int i = FirstSTW; i < LastSTW; i++){

   TFile* file = new TFile(STWTemplates.at(i));
   ddAFB[i] = (TH3D *)file->Get(AFB_dd_Name);

   ddAFBs.push_back(ddAFB[i]);
 }

 vector<TH3D *> uuLinearPlot;
 vector<TH3D *> ddLinearPlot;
 TH3D* uuFittedSlope;
 TH3D* uuFittedOffset;
 TH3D* ddFittedSlope;
 TH3D* ddFittedOffset;
 FitAFBStw* uuSlopeAndOffset = new FitAFBStw();
 uuSlopeAndOffset->Input(uuAFBs, STWInput[FirstSTW], STWInput[LastSTW - 1], uuLinearPlot, uuFittedSlope, uuFittedOffset);
 FitAFBStw* ddSlopeAndOffset = new FitAFBStw();
 ddSlopeAndOffset->Input(ddAFBs, STWInput[FirstSTW], STWInput[LastSTW - 1], ddLinearPlot, ddFittedSlope, ddFittedOffset);

 global_uuFittedSlope = uuFittedSlope;
 global_uuFittedOffset = uuFittedOffset;
 global_ddFittedSlope = ddFittedSlope;
 global_ddFittedOffset = ddFittedOffset;

}

void MainFunction(int FirstYbin, int LastYbin, int FirstQTbin, int LastQTbin, double &uuDelta, double &uuSigma, double &ddDelta, double &ddSigma)
{
 double massrange[31] = {60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120};

 vector<TString> rootNames;
 TString rootName;

 ifstream infile;
  infile.open("theoryCC.list",ios::in);
//  infile.open("theoryY_1_1.5.list",ios::in);
//  infile.open("theoryY_2_2.5.list",ios::in);
//  infile.open("theoryZPt_0_5.list",ios::in);
//  infile.open("theoryZPt_5_10.list",ios::in);
 while(infile>>rootName){
  rootNames.push_back(rootName);
 }
 infile.close();

 vector<TString> STWTemplates;
  infile.open("STWTemplate.list",ios::in);
//  infile.open("STWTemplateY_1_1.5.list",ios::in);
//  infile.open("STWTemplateY_2_2.5.list",ios::in);
//  infile.open("STWTemplateZPt_0_5.list",ios::in);
//  infile.open("STWTemplateZPt_5_10.list",ios::in);
 while(infile>>rootName){
  STWTemplates.push_back(rootName);
 }

 int NPDFs = rootNames.size() - 1;

// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/i2Tn3.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/NNPDF40.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/NNPDF31.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/TryCutReweighting/Pseudodata/MC_results.root";
 TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/MSHT20.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/250M/i2Tn3.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/Y_1_1.5/i2Tn3.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/Y_2_2.5/i2Tn3.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/ZPt_0_5/i2Tn3.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/ZPt_5_10/i2Tn3.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/250M/i2Tn3.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/FullAFB_RotatedCT18NNLO_LHA.01/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/STWTemplate/Y_1_1.5/0.2345/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/STWTemplate/250M/0.2324/MC_results.root";

 TString EtaRegion = "Full";

 TString VariableName = "AFB_" + EtaRegion;

 TFile* writefile = new TFile(VariableName + "_PDFResults_" + (int)FirstYbin + "_" + (int)LastYbin + "_" + (int)FirstQTbin + "_" + (int)LastQTbin + ".root", "RECREATE");
 writefile->cd();

 TString AFBName = "AFB_ZMass_ZY_QT";

// TString Dilution_uu_Name = "CoefficientDilution_ZMass_" + EtaRegion + "_uu_Residual";
// TString Dilution_dd_Name = "CoefficientDilution_ZMass_" + EtaRegion + "_dd_Residual";
// TString AveDilution_uu_Name = "CoefficientDilution_ZMass_" + EtaRegion + "_uu_Average";
// TString AveDilution_dd_Name = "CoefficientDilution_ZMass_" + EtaRegion + "_dd_Average";

// TString Dilution_uu_Name = "CoefficientZMass_" + EtaRegion + "_uu_wrong_Residual";
// TString Dilution_dd_Name = "CoefficientZMass_" + EtaRegion + "_dd_wrong_Residual";
// TString AveDilution_uu_Name = "CoefficientZMass_" + EtaRegion + "_uu_wrong_Average";
// TString AveDilution_dd_Name = "CoefficientZMass_" + EtaRegion + "_dd_wrong_Average";

 TString Dilution_uu_Name = "CoefficientZMass_ZY_QT_uu_wrong_Residual";
 TString Dilution_dd_Name = "CoefficientZMass_ZY_QT_dd_wrong_Residual";
 TString AveDilution_uu_Name = "CoefficientZMass_ZY_QT_uu_wrong_Average";
 TString AveDilution_dd_Name = "CoefficientZMass_ZY_QT_dd_wrong_Average";

 TString AFB_uu_Name = "AFB_ZMass_ZY_QT_uu";
 TString AFB_dd_Name = "AFB_ZMass_ZY_QT_dd";

 TFile *DataFile = new TFile(DataName);

 TH3D *DataAFB = (TH3D *)DataFile->Get(AFBName);
 TH3D *Data_uuEpsilon = (TH3D *)DataFile->Get(Dilution_uu_Name);
 TH3D *Data_ddEpsilon = (TH3D *)DataFile->Get(Dilution_dd_Name);
 TH3D *Data_AverageDilution_uu = (TH3D *)DataFile->Get(AveDilution_uu_Name);
 TH3D *Data_AverageDilution_dd = (TH3D *)DataFile->Get(AveDilution_dd_Name);

///////////////////////////////////////
 Smear3DHist(DataAFB);
///////////////////////////////////////

 global_Data = (TH3D *)DataAFB->Clone(AFBName);

 writefile->cd();
 DataAFB->Write();


// int FirstYbin = 1;
// int LastYbin = 4;
// int FirstQTbin = 1;
// int LastQTbin = 1;

 global_FirstYbin = FirstYbin;
 global_LastYbin = LastYbin;
 global_FirstQTbin = FirstQTbin;
 global_LastQTbin = LastQTbin;

////////////////////////////////////////////////////////////////
 PDFReweight *AFBCalc = new PDFReweight();
 AFBCalc->InitialPDF("CT18NNLO", 0);
 AFBCalc->InputStw(0.2315);

 global_AFBCalc = AFBCalc;
////////////////////////////////////////////////////////////////

 vector<double> Su;
 vector<double> Sd;
 TH1D* SFittingResult[NPDFs + 1];
 vector<TH1D *> SFittingResults;

 TH3D* PDFAFB[NPDFs + 1];
 vector<TH3D *> PDFAFBs;

 TH3D* TmpAFB[NPDFs + 1];
 vector<TH3D *> TmpAFBs;

 TH3D* AverageDilution_uu[NPDFs + 1];
 vector<TH3D *> AverageDilution_uus;
 TH3D* AverageDilution_dd[NPDFs + 1];
 vector<TH3D *> AverageDilution_dds;

 TH1D* PDFPu[NPDFs + 1];
 vector<TH1D *> PDFPus;
 TH1D* PDFPd[NPDFs + 1];
 vector<TH1D *> PDFPds;
 TH1D* PDFP0[NPDFs + 1];
 vector<TH1D *> PDFP0s;

 TRandom3 random(0);

 double myR = 0.0;

 for(int i = 0; i < NPDFs + 1; i++){
   TFile* file = new TFile(rootNames.at(i));
//   if(i == 0) file = new TFile(DataName);
//   if(i == 0) file = new TFile(STWTemplates.at(23));
//   if(i == 0) file = new TFile("/Data/yfu/MainCode/run/ResBosDilution/STWTemplate/Y_1_1.5/0.2345/MC_results.root");

   TH3D* Dilution_uu = (TH3D *)file->Get(Dilution_uu_Name);
   TH3D* Dilution_dd = (TH3D *)file->Get(Dilution_dd_Name);
   TH3D* AFB_uu = (TH3D *)file->Get(AFB_uu_Name);
   TH3D* AFB_dd = (TH3D *)file->Get(AFB_dd_Name);

   global_Dilution_uu_Residual = Dilution_uu;
   global_Dilution_dd_Residual = Dilution_dd;

   TH3D* DilutionAverage_uu = (TH3D *)file->Get(AveDilution_uu_Name);
   AverageDilution_uu[i] = (TH3D *)DilutionAverage_uu->Clone(AveDilution_uu_Name);
   AverageDilution_uus.push_back(AverageDilution_uu[i]);

   TH3D* DilutionAverage_dd = (TH3D *)file->Get(AveDilution_dd_Name);
   AverageDilution_dd[i] = (TH3D *)DilutionAverage_dd->Clone(AveDilution_dd_Name);
   AverageDilution_dds.push_back(AverageDilution_dd[i]);

//   global_Dilution_uu_Residual = Data_uuEpsilon;
//   global_Dilution_dd_Residual = Data_ddEpsilon;

   global_AFB_uu = AFB_uu;
   global_AFB_dd = AFB_dd;

   if(i == 0){
     int NPars = AFB_uu->GetNbinsY() * AFB_uu->GetNbinsZ() * 2 + 1;
     TMinuitHelper *myMinuit = new TMinuitHelper(NPars);
     myMinuit->SetFCN(udDilutionFitting);
     myMinuit->Input(0, "Stw", 0.2315, 0.01, 0.22, 0.24);
     int Index = 0;
     for(int iy = 1; iy <= AFB_uu->GetNbinsY(); iy++){
       for(int iqt = 1; iqt <= AFB_uu->GetNbinsZ(); iqt++){
         Index++; 
         if(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin) myMinuit->Input(Index, (TString)"Su_Y" + (int)iy + "_QT" + (int)iqt, 0.2, 0.2, 0.0, 1.0);
         if(!(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin)) myMinuit->Input(Index, (TString)"Su_Y" + (int)iy + "_QT" + (int)iqt, AverageDilution_uus.at(0)->GetBinContent(1, iy, iqt), 0.0, 0.0, 1.0);
         Index++;
         if(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin) myMinuit->Input(Index, (TString)"Sd_Y" + (int)iy + "_QT" + (int)iqt, 0.2, 0.2, 0.0, 1.0);
         if(!(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin)) myMinuit->Input(Index, (TString)"Sd_Y" + (int)iy + "_QT" + (int)iqt, AverageDilution_dds.at(0)->GetBinContent(1, iy, iqt), 0.0, 0.0, 1.0);
         //iy     = (Index - 1) / NbinsZ / 2 + 1
         //iqt    = (Index - 1) % (NBinsZ * 2) / 2 + 1
         //u or d = (Index - 1) % (NBinsZ * 2) % 2 + 1
         //Index  = (iy - 1) * (NbinsZ * 2) + (iqt - 1) * 2 + iflavor;
       }
     }

     myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
     myMinuit->Exec("MIGRAD", 100000, 0.001);
     myMinuit->GetParameter();

     double* SPar = new double[NPars];
     double* SParError = new double[NPars];
     int uIndex = (FirstYbin - 1) * AverageDilution_uus.at(i)->GetNbinsZ() * 2 + (FirstQTbin - 1) * 2 + 2;
     int dIndex = (FirstYbin - 1) * AverageDilution_uus.at(i)->GetNbinsZ() * 2 + (FirstQTbin - 1) * 2 + 3;

     myMinuit->GetParametersAndError(SPar, SParError);
     cout<<"Fitted Pu: "<<SPar[uIndex - 1]<<" Fitted Pd: "<<SPar[dIndex - 1]<<endl;
     cout<<"Fitted Pu Error: "<<SParError[uIndex - 1]<<" Fitted Pd Error: "<<SParError[dIndex - 1]<<endl;
     cout<<"Correlation between parameter "<<uIndex<<" and "<<dIndex<<": "<<myMinuit->GetCorrelation(2, 3)<<endl;
     global_FittedPu = SPar[uIndex - 1];
     global_FittedPd = SPar[dIndex - 1];
     global_PuError = SParError[uIndex - 1];
     global_PdError = SParError[dIndex - 1];
     global_Correlation = myMinuit->GetCorrelation(2, 3);

     SFittingResult[i] = new TH1D((TString)"SFittingResult_PDF" + (int)i, (TString)"SFittingResult_PDF" + (int)i, NPars, 0, NPars);
     for(int ipar = 1; ipar <= NPars; ipar++){
       SFittingResult[i]->SetBinContent(ipar, SPar[ipar - 1]);
       SFittingResult[i]->SetBinError(ipar, SParError[ipar - 1]);
     }
     SFittingResults.push_back(SFittingResult[i]);

   }

   PDFP0[i] = new TH1D((TString)"P0Result_PDF" + (int)i, (TString)"P0Result_PDF" + (int)i, 101, 0, 101);
   for(int iy = 1; iy <= AverageDilution_uus.at(0)->GetNbinsY(); iy++){
     for(int iqt = 1; iqt <= AverageDilution_uus.at(0)->GetNbinsZ(); iqt++){
       int Index = (iy - 1) * AverageDilution_uus.at(i)->GetNbinsZ() * 2 + (iqt - 1) * 2 + 1;
       PDFP0[i]->SetBinContent(Index + 1, AverageDilution_uus.at(i)->GetBinContent(1, iy, iqt));
       PDFP0[i]->SetBinError(Index + 1, AverageDilution_uus.at(i)->GetBinError(1, iy, iqt));
       PDFP0[i]->SetBinContent(Index + 2, AverageDilution_dds.at(i)->GetBinContent(1, iy, iqt));
       PDFP0[i]->SetBinError(Index + 2, AverageDilution_dds.at(i)->GetBinError(1, iy, iqt));
     }
   }
   PDFP0s.push_back(PDFP0[i]);

   TmpAFB[i] = (TH3D *)global_MC->Clone((TString)"TmpAFB_PDF" + (int)i);
   TmpAFB[i]->Reset();
   for(int ibinx = 1; ibinx <= AFB_uu->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= AFB_uu->GetNbinsY(); ibiny++){
       for(int ibinz = 1; ibinz <= AFB_uu->GetNbinsZ(); ibinz++){
         int Index = (ibiny - 1) * AFB_uu->GetNbinsZ() * 2 + (ibinz - 1) * 2 + 2;
         double Value1 = Dilution_uu->GetBinContent(ibinx, ibiny, ibinz) + SFittingResults.at(0)->GetBinContent(Index);
         double Value2 = global_uuFittedSlope->GetBinContent(ibinx, ibiny, ibinz) * SFittingResults.at(0)->GetBinContent(1) + global_uuFittedOffset->GetBinContent(ibinx, ibiny, ibinz);

         double Value3 = Dilution_dd->GetBinContent(ibinx, ibiny, ibinz) + SFittingResults.at(0)->GetBinContent(Index + 1);
         double Value4 = global_ddFittedSlope->GetBinContent(ibinx, ibiny, ibinz) * SFittingResults.at(0)->GetBinContent(1) + global_ddFittedOffset->GetBinContent(ibinx, ibiny, ibinz);

         double Error1 = Dilution_uu->GetBinError(ibinx, ibiny, ibinz);
         double Error2 = AFB_uu->GetBinError(ibinx, ibiny, ibinz);
         double Error3 = Dilution_dd->GetBinError(ibinx, ibiny, ibinz);
         double Error4 = AFB_dd->GetBinError(ibinx, ibiny, ibinz);

         double Value = Value1 * Value2 + Value3 * Value4;
         double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

         TmpAFB[i]->SetBinContent(ibinx, ibiny, ibinz, Value);
         TmpAFB[i]->SetBinError(ibinx, ibiny, ibinz, DataAFB->GetBinError(ibinx, ibiny, ibinz));
       }
     }
   }
   TmpAFBs.push_back(TmpAFB[i]);

/////////////////
//   cout<<"here?"<<endl;
////////////////

   writefile->cd();
   //SFittingResult[i]->Write();
   global_MC->Write((TString)"AFB_PDF" + (int)i);
   if(i == 0) SFittingResult[i]->Write();

   PDFAFBs.push_back(global_MC);

   MinChi2 = 100000.0;
 }


 TH1D* STWValue[NPDFs + 1];
 vector<TH1D *> STWValues;

 TFile* file = new TFile(rootNames.at(0));
 TH3D* Dilution_uu = (TH3D *)file->Get(Dilution_uu_Name);
 TH3D* Dilution_dd = (TH3D *)file->Get(Dilution_dd_Name);
 TH3D* AFB_uu = (TH3D *)file->Get(AFB_uu_Name);
 TH3D* AFB_dd = (TH3D *)file->Get(AFB_dd_Name);

 global_Dilution_uu_Residual = Dilution_uu;
 global_Dilution_dd_Residual = Dilution_dd;
 global_AFB_uu = AFB_uu;
 global_AFB_dd = AFB_dd;


///////////////////////////////////
//                               //
//  Delta M induced uncertainty  //
//                               //
///////////////////////////////////

 TH1D* PuValue[NPDFs + 1];
 vector<TH1D *> PuValues;

 TH1D* PdValue[NPDFs + 1];
 vector<TH1D *> PdValues;

/* for(int i = 0; i < NPDFs + 1; i++){
   global_Data = (TH3D *)TmpAFBs.at(i)->Clone(AFBName + "_Tmp_PDF" + (int)i);

   int NPars = TmpAFBs.at(i)->GetNbinsY() * TmpAFBs.at(i)->GetNbinsZ() * 2 + 1;
   TMinuitHelper *myMinuit = new TMinuitHelper(NPars);
   myMinuit->SetFCN(udDilutionFitting);
   myMinuit->Input(0, "Stw", 0.2315, 0.01, 0.22, 0.24);
   for(int iy = 1; iy <= TmpAFBs.at(i)->GetNbinsY(); iy++){
     for(int iqt = 1; iqt <= TmpAFBs.at(i)->GetNbinsZ(); iqt++){
       int Index = (iy - 1) * TmpAFBs.at(i)->GetNbinsZ() * 2 + (iqt - 1) * 2 + 1;
       myMinuit->Input(Index, (TString)"Su_Y" + (int)iy + "_QT" + (int)iqt, SFittingResults.at(0)->GetBinContent(Index + 1), 0.0, 0.0, 1.0);
       myMinuit->Input(Index + 1, (TString)"Sd_Y" + (int)iy + "_QT" + (int)iqt, SFittingResults.at(0)->GetBinContent(Index + 2), 0.0, 0.0, 1.0);
     }
   }
   myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
   myMinuit->Exec("MIGRAD", 100000, 0.001);
   myMinuit->GetParameter();
   double* SPar = new double[NPars];
   myMinuit->GetParameters(SPar);

   STWValue[i] = new TH1D((TString)"STWValueResult_PDF" + (int)i, (TString)"STWValueResult_PDF" + (int)i, 1, 0, 1);
   STWValue[i]->SetBinContent(1, SPar[0]);
   STWValue[i]->SetBinError(1, 0);

   STWValues.push_back(STWValue[i]);

   MinChi2 = 100000.0;
 }


 for(int i = 0; i < NPDFs + 1; i++){
   global_Data = (TH3D *)TmpAFBs.at(i)->Clone(AFBName + "_Tmp_PDF" + (int)i);

   int NPars = TmpAFBs.at(i)->GetNbinsY() * TmpAFBs.at(i)->GetNbinsZ() * 2 + 1;
   TMinuitHelper *myMinuit = new TMinuitHelper(NPars);
   myMinuit->SetFCN(udDilutionFitting);
   myMinuit->Input(0, "Stw", SFittingResults.at(0)->GetBinContent(1), 0.0, 0.22, 0.24);
   for(int iy = 1; iy <= TmpAFBs.at(i)->GetNbinsY(); iy++){
     for(int iqt = 1; iqt <= TmpAFBs.at(i)->GetNbinsZ(); iqt++){
       int Index = (iy - 1) * TmpAFBs.at(i)->GetNbinsZ() * 2 + (iqt - 1) * 2 + 1;
       if(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin) myMinuit->Input(Index, (TString)"Su_Y" + (int)iy + "_QT" + (int)iqt, 0.2, 0.2, 0.0, 1.0);
       if(!(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin)) myMinuit->Input(Index, (TString)"Su_Y" + (int)iy + "_QT" + (int)iqt, SFittingResults.at(0)->GetBinContent(Index + 1), 0.0, 0.0, 1.0);
       if(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin) myMinuit->Input(Index + 1, (TString)"Sd_Y" + (int)iy + "_QT" + (int)iqt, SFittingResults.at(0)->GetBinContent(Index + 2), 0.0, 0.0, 1.0);
       if(!(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin)) myMinuit->Input(Index + 1, (TString)"Sd_Y" + (int)iy + "_QT" + (int)iqt, SFittingResults.at(0)->GetBinContent(Index + 2), 0.0, 0.0, 1.0);
     }
   }
   myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
   myMinuit->Exec("MIGRAD", 100000, 0.001);
   myMinuit->GetParameter();
   double* SPar = new double[NPars];
   myMinuit->GetParameters(SPar);

   PuValue[i] = new TH1D((TString)"PuValueResult_PDF" + (int)i, (TString)"PuValueResult_PDF" + (int)i, 1, 0, 1);
   int Index = (FirstYbin - 1) * TmpAFBs.at(i)->GetNbinsZ() * 2 + (FirstQTbin - 1) * 2 + 1;
   PuValue[i]->SetBinContent(1, SPar[Index]);
   PuValue[i]->SetBinError(1, 0);

   PuValues.push_back(PuValue[i]);

   MinChi2 = 100000.0;
 }

 for(int i = 0; i < NPDFs + 1; i++){
   global_Data = (TH3D *)TmpAFBs.at(i)->Clone(AFBName + "_Tmp_PDF" + (int)i);

   int NPars = TmpAFBs.at(i)->GetNbinsY() * TmpAFBs.at(i)->GetNbinsZ() * 2 + 1;
   TMinuitHelper *myMinuit = new TMinuitHelper(NPars);
   myMinuit->SetFCN(udDilutionFitting);
   myMinuit->Input(0, "Stw", SFittingResults.at(0)->GetBinContent(1), 0.0, 0.22, 0.24);
   for(int iy = 1; iy <= TmpAFBs.at(i)->GetNbinsY(); iy++){
     for(int iqt = 1; iqt <= TmpAFBs.at(i)->GetNbinsZ(); iqt++){
       int Index = (iy - 1) * TmpAFBs.at(i)->GetNbinsZ() * 2 + (iqt - 1) * 2 + 1;
       if(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin) myMinuit->Input(Index, (TString)"Su_Y" + (int)iy + "_QT" + (int)iqt, SFittingResults.at(0)->GetBinContent(Index + 1), 0.0, 0.0, 1.0);
       if(!(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin)) myMinuit->Input(Index, (TString)"Su_Y" + (int)iy + "_QT" + (int)iqt, SFittingResults.at(0)->GetBinContent(Index + 1), 0.0, 0.0, 1.0);
       if(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin) myMinuit->Input(Index + 1, (TString)"Sd_Y" + (int)iy + "_QT" + (int)iqt, 0.2, 0.2, 0.0, 1.0);
       if(!(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin)) myMinuit->Input(Index + 1, (TString)"Sd_Y" + (int)iy + "_QT" + (int)iqt, SFittingResults.at(0)->GetBinContent(Index + 2), 0.0, 0.0, 1.0);
     }
   }
   myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
   myMinuit->Exec("MIGRAD", 100000, 0.001);
   myMinuit->GetParameter();
   double* SPar = new double[NPars];
   myMinuit->GetParameters(SPar);

   PdValue[i] = new TH1D((TString)"PdValueResult_PDF" + (int)i, (TString)"PdValueResult_PDF" + (int)i, 1, 0, 1);
   int Index = (FirstYbin - 1) * TmpAFBs.at(i)->GetNbinsZ() * 2 + (FirstQTbin - 1) * 2 + 1;
   PdValue[i]->SetBinContent(1, SPar[Index + 1]);
   PdValue[i]->SetBinError(1, 0);

   PdValues.push_back(PdValue[i]);

   MinChi2 = 100000.0;
 }
*/

 writefile->cd();

/* TH1D *STWValueError;
 PDFUncertainty *STWValuePDFunc;
 STWValuePDFunc = new PDFUncertainty();
 STWValuePDFunc->SaveVariBin();
// STWValuePDFunc->Input1DPlot("Symmetry", STWValues, STWValueError);
// STWValuePDFunc->Input1DPlot("Symmetry68", STWValues, STWValueError);
 STWValuePDFunc->Input1DPlot("MonteCarlo", STWValues, STWValueError);

 TH1D *PuValueError;
 PDFUncertainty *PuValuePDFunc;
 PuValuePDFunc = new PDFUncertainty();
 PuValuePDFunc->SaveVariBin();
// PuValuePDFunc->Input1DPlot("Symmetry", PuValues, PuValueError);
// PuValuePDFunc->Input1DPlot("Symmetry68", PuValues, PuValueError);
 PuValuePDFunc->Input1DPlot("MonteCarlo", PuValues, PuValueError);

 TH1D *PdValueError;
 PDFUncertainty *PdValuePDFunc;
 PdValuePDFunc = new PDFUncertainty();
 PdValuePDFunc->SaveVariBin();
// PdValuePDFunc->Input1DPlot("Symmetry", PdValues, PdValueError);
// PdValuePDFunc->Input1DPlot("Symmetry68", PdValues, PdValueError);
 PdValuePDFunc->Input1DPlot("MonteCarlo", PdValues, PdValueError);
*/
 TH1D *PDFP0Error;
 PDFUncertainty *PDFP0PDFunc;
 PDFP0PDFunc = new PDFUncertainty();
 PDFP0PDFunc->SaveVariBin();
// PDFP0PDFunc->Input1DPlot("Symmetry", PDFP0s, PDFP0Error);
// PDFP0PDFunc->Input1DPlot("Symmetry68", PDFP0s, PDFP0Error);
 PDFP0PDFunc->Input1DPlot("MonteCarlo", PDFP0s, PDFP0Error);


 for(int iy = FirstYbin; iy <= LastYbin; iy++){
   for(int iqt = FirstQTbin; iqt <= LastQTbin; iqt++){
     int Index = (iy - 1) * TmpAFBs.at(0)->GetNbinsZ() * 2 + (iqt - 1) * 2 + 2;
//     cout<<"MC uubar Y bin "<<iy<<" QT bin "<<iqt<<" P0: "<<AverageDilution_uus.at(0)->GetBinContent(1, iy, iqt)<<" Fitted P0: "<<SFittingResults.at(0)->GetBinContent(Index)<<" error: "<<SFittingResults.at(0)->GetBinError(Index)<<endl;
//     cout<<"MC ddbar Y bin "<<iy<<" QT bin "<<iqt<<" P0: "<<AverageDilution_dds.at(0)->GetBinContent(1, iy, iqt)<<" Fitted P0: "<<SFittingResults.at(0)->GetBinContent(Index + 1)<<" error: "<<SFittingResults.at(0)->GetBinError(Index + 1)<<endl;
     cout<<"Data uubar Y bin "<<iy<<" QT bin "<<iqt<<" P0: "<<Data_AverageDilution_uu->GetBinContent(1, iy, iqt)<<" Fitted P0: "<<SFittingResults.at(0)->GetBinContent(Index)<<" error: "<<SFittingResults.at(0)->GetBinError(Index)<<endl;
     cout<<"Data ddbar Y bin "<<iy<<" QT bin "<<iqt<<" P0: "<<Data_AverageDilution_dd->GetBinContent(1, iy, iqt)<<" Fitted P0: "<<SFittingResults.at(0)->GetBinContent(Index + 1)<<" error: "<<SFittingResults.at(0)->GetBinError(Index + 1)<<endl;
//     uuDelta = AverageDilution_uus.at(0)->GetBinContent(1, iy, iqt) - SFittingResults.at(0)->GetBinContent(Index);
     uuDelta = Data_AverageDilution_uu->GetBinContent(1, iy, iqt) - SFittingResults.at(0)->GetBinContent(Index);
     uuSigma = SFittingResults.at(0)->GetBinError(Index);
//     ddDelta = AverageDilution_dds.at(0)->GetBinContent(1, iy, iqt) - SFittingResults.at(0)->GetBinContent(Index + 1);
     ddDelta = Data_AverageDilution_dd->GetBinContent(1, iy, iqt) - SFittingResults.at(0)->GetBinContent(Index + 1);
     ddSigma = SFittingResults.at(0)->GetBinError(Index + 1);
   }
 }

/* int Index = (FirstYbin - 1) * TmpAFBs.at(0)->GetNbinsZ() * 2 + (FirstQTbin - 1) * 2 + 2;
 cout<<"Central value: "<<SFittingResults.at(0)->GetBinContent(1)<<" error: "<<SFittingResults.at(0)->GetBinError(1)<<endl;
 cout<<"stw Central value: "<<STWValues.at(0)->GetBinContent(1)<<" DeltaM unc: "<<STWValueError->GetBinContent(1)<<endl;
 cout<<"P0u Central value: "<<PuValues.at(0)->GetBinContent(1)<<" DeltaM unc: "<<PuValueError->GetBinContent(1)<<" PDF unc: "<<PDFP0Error->GetBinContent(Index)<<endl;
 cout<<"P0d Central value: "<<PdValues.at(0)->GetBinContent(1)<<" DeltaM unc: "<<PdValueError->GetBinContent(1)<<" PDF unc: "<<PDFP0Error->GetBinContent(Index + 1)<<endl;
*/

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

 writefile->cd();
 writefile->Write();
 writefile->Close();

}

int main(int argc, char** argv)
{
 GetAFBStwLinear();

 TFile* file = new TFile("save.root", "RECREATE");
 file->cd();

 int FirstYbin = 1;
 int LastYbin = 4;

 int nYbin = LastYbin - FirstYbin + 1;
 int nQTbin = 2;

 int NPar = nYbin * nQTbin * 2;

// TH2D* uuResults = new TH2D((TString)"uuResults_" + (int) + FirstYbin + "_" + (int)LastYbin, (TString)"uuResults_" + (int) + FirstYbin + "_" + (int)LastYbin, 1, 0, 1, 10, 0, 10);
// TH2D* ddResults = new TH2D((TString)"ddResults_" + (int) + FirstYbin + "_" + (int)LastYbin, (TString)"ddResults_" + (int) + FirstYbin + "_" + (int)LastYbin, 1, 0, 1, 10, 0, 10);

 TH2D* uuResults = new TH2D((TString)"uuResults", (TString)"uuResults", 4, 0, 4, 10, 0, 50);
 TH2D* ddResults = new TH2D((TString)"ddResults", (TString)"ddResults", 4, 0, 4, 10, 0, 50);
 TH2D* stwResults = new TH2D((TString)"stwResults", (TString)"stwResults", 4, 0, 4, 10, 0, 50);
 TH2D* uuP0 = new TH2D((TString)"uuP0", (TString)"uuP0", 4, 0, 4, 10, 0, 50);
 TH2D* ddP0 = new TH2D((TString)"ddP0", (TString)"ddP0", 4, 0, 4, 10, 0, 50);
 TH2D* stw = new TH2D((TString)"stw", (TString)"stw", 4, 0, 4, 10, 0, 50);
 TH2D* uuDelta = new TH2D((TString)"uuDelta", (TString)"uuDelta", 4, 0, 4, 10, 0, 50);
 TH2D* ddDelta = new TH2D((TString)"ddDelta", (TString)"ddDelta", 4, 0, 4, 10, 0, 50);
 TH2D* stwDelta = new TH2D((TString)"stwDelta", (TString)"stwDelta", 4, 0, 4, 10, 0, 50);
 TH2D* uuError = new TH2D((TString)"uuError", (TString)"uuError", 4, 0, 4, 10, 0, 50);
 TH2D* ddError = new TH2D((TString)"ddError", (TString)"ddError", 4, 0, 4, 10, 0, 50);
 TH2D* stwError = new TH2D((TString)"stwError", (TString)"stwError", 4, 0, 4, 10, 0, 50);
 TH2D* uuFittingResults = new TH2D((TString)"uuFittingResults", (TString)"uuFittingResults", 4, 0, 4, 10, 0, 50);
 TH2D* ddFittingResults = new TH2D((TString)"ddFittingResults", (TString)"ddFittingResults", 4, 0, 4, 10, 0, 50);
 TH2D* uuFittingResultsNoErr = new TH2D((TString)"uuFittingResultsNoErr", (TString)"uuFittingResultsNoErr", 4, 0, 4, 10, 0, 50);
 TH2D* ddFittingResultsNoErr = new TH2D((TString)"ddFittingResultsNoErr", (TString)"ddFittingResultsNoErr", 4, 0, 4, 10, 0, 50);
 TH2D* uuP0PDFunc = new TH2D((TString)"uuP0PDFunc", (TString)"uuP0PDFunc", 4, 0, 4, 10, 0, 50);
 TH2D* ddP0PDFunc = new TH2D((TString)"ddP0PDFunc", (TString)"ddP0PDFunc", 4, 0, 4, 10, 0, 50);
 TH2D* uuP0DeltaMunc = new TH2D((TString)"uuP0DeltaMunc", (TString)"uuP0DeltaMunc", 4, 0, 4, 10, 0, 50);
 TH2D* ddP0DeltaMunc = new TH2D((TString)"ddP0DeltaMunc", (TString)"ddP0DeltaMunc", 4, 0, 4, 10, 0, 50);

 TH1D* P0Data = new TH1D("P0Data", "P0Data", NPar, 0, NPar);
 TH2D* Correlation = new TH2D("Correlation", "Correlation", NPar, 0, NPar, NPar, 0, NPar);
 TH2D* CovarianceMatrix = new TH2D("CovarianceMatrix", "CovarianceMatrix", NPar, 0, NPar, NPar, 0, NPar);
 TH2D* InverseCovarianceMatrix = new TH2D("InverseCovarianceMatrix", "InverseCovarianceMatrix", NPar, 0, NPar, NPar, 0, NPar);

 double CombinedStw = 0.0;
 double CombinedStwErr = 0.0;

 double CombinedErr = 0.0;
 double CombinedNumer = 0.0;

 for(int ibinx = 1; ibinx <= CovarianceMatrix->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= CovarianceMatrix->GetNbinsY(); ibiny++){
     if(ibinx == ibiny){
       Correlation->SetBinContent(ibinx, ibiny, 1.0);
       CovarianceMatrix->SetBinContent(ibinx, ibiny, 1.0);
     }
     else{
       Correlation->SetBinContent(ibinx, ibiny, 0.0);
       CovarianceMatrix->SetBinContent(ibinx, ibiny, 0.0);
     }
   }
 }

 for(int ibiny = FirstYbin; ibiny <= LastYbin; ibiny++){
   for(int ibinz = 1; ibinz <= nQTbin; ibinz++){

//////////////////
//              //
//  First call  //
//              //
//////////////////


     double uuDeltaValue, uuSigmaValue, ddDeltaValue, ddSigmaValue;
     MainFunction(ibiny, ibiny, ibinz, ibinz, uuDeltaValue, uuSigmaValue, ddDeltaValue, ddSigmaValue);
     cout<<"uuDelta: "<<uuDeltaValue<<" uuSigma: "<<uuSigmaValue<<endl;
     cout<<"ddDelta: "<<ddDeltaValue<<" ddSigma: "<<ddSigmaValue<<endl;
     if(uuSigmaValue > 1e-10) uuResults->SetBinContent(ibiny, ibinz, uuDeltaValue/uuSigmaValue);
     uuResults->SetBinError(ibiny, ibinz, 0.0);
     if(ddSigmaValue > 1e-10) ddResults->SetBinContent(ibiny, ibinz, ddDeltaValue/ddSigmaValue);
     ddResults->SetBinError(ibiny, ibinz, 0.0);

     int uIndex = (ibiny - FirstYbin) * nQTbin * 2 + (ibinz - 1) * 2 + 1;
     int dIndex = (ibiny - FirstYbin) * nQTbin * 2 + (ibinz - 1) * 2 + 2;

     P0Data->SetBinContent(uIndex, global_FittedPu);
     P0Data->SetBinError(uIndex, global_PuError);
     P0Data->SetBinContent(dIndex, global_FittedPd);
     P0Data->SetBinError(dIndex, global_PdError);
     //global_Correlation = 0.0;
     Correlation->SetBinContent(uIndex, dIndex, global_Correlation);
     Correlation->SetBinContent(dIndex, uIndex, global_Correlation);
     CovarianceMatrix->SetBinContent(uIndex, dIndex, global_Correlation * global_PuError * global_PdError);
     CovarianceMatrix->SetBinContent(dIndex, uIndex, global_Correlation * global_PuError * global_PdError);
     CovarianceMatrix->SetBinContent(uIndex, uIndex, global_PuError * global_PuError);
     CovarianceMatrix->SetBinContent(dIndex, dIndex, global_PdError * global_PdError);



///////////////////
//               //
//  Second call  //
//               //
///////////////////

     TFile* f = new TFile((TString)"AFB_Full_PDFResults_" + (int)ibiny + "_" + (int)ibiny + "_" + (int)ibinz + "_" + (int)ibinz + ".root");
     //TFile* fOrigin = new TFile("AFB_Full_PDFResults_Origin.root");
     TH1D* SFittingResult = (TH1D *)f->Get("SFittingResult_PDF0");
     //TH1D* SFittingResultOrigin = (TH1D *)fOrigin->Get("SFittingResult_PDF0");
     TH1D* P0Result_PDF0_PDFError = (TH1D *)f->Get("P0Result_PDF0_PDFError");//PDF unc
     //TH1D* PuValueError = (TH1D *)f->Get("PuValueResult_PDF0_PDFError");//DeltaM unc
     //TH1D* PdValueError = (TH1D *)f->Get("PdValueResult_PDF0_PDFError");//DeltaM unc

     int Index = (ibiny - 1) * 2 * 10 + (ibinz - 1) * 2 + 2;
     //uuResults->SetBinContent(ibiny, ibinz, (SFittingResult->GetBinContent(Index) - SFittingResultOrigin->GetBinContent(Index)) / SFittingResult->GetBinError(Index));
     uuResults->SetBinContent(ibiny, ibinz, uuDeltaValue / SFittingResult->GetBinError(Index));
     uuResults->SetBinError(ibiny, ibinz, 0.0);
     //ddResults->SetBinContent(ibiny, ibinz, (SFittingResult->GetBinContent(Index + 1) - SFittingResultOrigin->GetBinContent(Index + 1)) / SFittingResult->GetBinError(Index + 1));
     ddResults->SetBinContent(ibiny, ibinz, ddDeltaValue / SFittingResult->GetBinError(Index + 1));
     ddResults->SetBinError(ibiny, ibinz, 0.0);
     stwResults->SetBinContent(ibiny, ibinz, (SFittingResult->GetBinContent(1) - 0.2315) / SFittingResult->GetBinError(1));
     stwResults->SetBinError(ibiny, ibinz, 0.0);
     //uuP0->SetBinContent(ibiny, ibinz, SFittingResultOrigin->GetBinContent(Index));
     //uuP0->SetBinError(ibiny, ibinz, sqrt(SFittingResultOrigin->GetBinContent(Index)));
     uuP0->SetBinError(ibiny, ibinz, 0.0);
     //ddP0->SetBinContent(ibiny, ibinz, SFittingResultOrigin->GetBinContent(Index + 1));
     //ddP0->SetBinError(ibiny, ibinz, sqrt(SFittingResultOrigin->GetBinContent(Index + 1)));
     ddP0->SetBinError(ibiny, ibinz, 0.0);
     stw->SetBinContent(ibiny, ibinz, (SFittingResult->GetBinContent(1)));
     stw->SetBinError(ibiny, ibinz, 0.0);
     //uuDelta->SetBinContent(ibiny, ibinz, fabs(SFittingResult->GetBinContent(Index) - SFittingResultOrigin->GetBinContent(Index)));
     uuDelta->SetBinContent(ibiny, ibinz, fabs(uuDeltaValue));
     uuDelta->SetBinError(ibiny, ibinz, 0.0);
     //ddDelta->SetBinContent(ibiny, ibinz, fabs(SFittingResult->GetBinContent(Index + 1) - SFittingResultOrigin->GetBinContent(Index + 1)));
     ddDelta->SetBinContent(ibiny, ibinz, fabs(ddDeltaValue));
     ddDelta->SetBinError(ibiny, ibinz, 0.0);
     stwDelta->SetBinContent(ibiny, ibinz, (SFittingResult->GetBinContent(1) - 0.2315));
     stwDelta->SetBinError(ibiny, ibinz, 0.0);
     uuError->SetBinContent(ibiny, ibinz, SFittingResult->GetBinError(Index));
     uuError->SetBinError(ibiny, ibinz, 0.0);
     ddError->SetBinContent(ibiny, ibinz, SFittingResult->GetBinError(Index + 1));
     ddError->SetBinError(ibiny, ibinz, 0.0);
     stwError->SetBinContent(ibiny, ibinz, SFittingResult->GetBinError(1));
     stwError->SetBinError(ibiny, ibinz, 0.0);
     uuFittingResults->SetBinContent(ibiny, ibinz, SFittingResult->GetBinContent(Index));
     uuFittingResults->SetBinError(ibiny, ibinz, SFittingResult->GetBinError(Index));
     ddFittingResults->SetBinContent(ibiny, ibinz, SFittingResult->GetBinContent(Index + 1));
     ddFittingResults->SetBinError(ibiny, ibinz, SFittingResult->GetBinError(Index + 1));
     uuFittingResultsNoErr->SetBinContent(ibiny, ibinz, SFittingResult->GetBinContent(Index));
     uuFittingResultsNoErr->SetBinError(ibiny, ibinz, 0.0);
     ddFittingResultsNoErr->SetBinContent(ibiny, ibinz, SFittingResult->GetBinContent(Index + 1));
     ddFittingResultsNoErr->SetBinError(ibiny, ibinz, 0.0);
     uuP0PDFunc->SetBinContent(ibiny, ibinz, P0Result_PDF0_PDFError->GetBinContent(Index));
     uuP0PDFunc->SetBinError(ibiny, ibinz, 0.0);
     ddP0PDFunc->SetBinContent(ibiny, ibinz, P0Result_PDF0_PDFError->GetBinContent(Index + 1));
     ddP0PDFunc->SetBinError(ibiny, ibinz, 0.0);
     //uuP0DeltaMunc->SetBinContent(ibiny, ibinz, PuValueError->GetBinContent(1));
     //uuP0DeltaMunc->SetBinError(ibiny, ibinz, 0.0);
     //ddP0DeltaMunc->SetBinContent(ibiny, ibinz, PdValueError->GetBinContent(1));
     //ddP0DeltaMunc->SetBinError(ibiny, ibinz, 0.0);
     cout<<"PDF unc: "<<ibiny<<" "<<ibinz<<" "<<uuP0PDFunc->GetBinContent(ibiny, ibinz)<<" "<<ddP0PDFunc->GetBinContent(ibiny, ibinz)<<endl;
     cout<<"DeltaM unc: "<<ibiny<<" "<<ibinz<<" "<<" "<<uuP0DeltaMunc->GetBinContent(ibiny, ibinz)<<" "<<ddP0DeltaMunc->GetBinContent(ibiny, ibinz)<<endl;
     cout<<"Fitting unc: "<<ibiny<<" "<<ibinz<<" "<<" "<<uuError->GetBinContent(ibiny, ibinz)<<" "<<ddError->GetBinContent(ibiny, ibinz)<<endl;

     CombinedErr += 1.0 / (SFittingResult->GetBinError(1) * SFittingResult->GetBinError(1));
     CombinedNumer += SFittingResult->GetBinContent(1) /( SFittingResult->GetBinError(1) * SFittingResult->GetBinError(1));



   }
 }


// CombinedStw = CombinedNumer / CombinedErr;
// CombinedStwErr = 1.0 / sqrt(CombinedErr);

/* CalculateInverseMatrix(CovarianceMatrix, InverseCovarianceMatrix);

 FileForEPUMP *P0Theory_file = new FileForEPUMP("P0Theory");
 P0Theory_file->InputData(P0Data);
 P0Theory_file->InputCovarianceMatrix(InverseCovarianceMatrix);
 P0Theory_file->writedata();
*/

 cout<<"Combined stw = "<<CombinedStw<<endl;
 cout<<"Combined stw error = "<<CombinedStwErr<<endl;


 file->Write();
 file->Close();

 return 1;
}
