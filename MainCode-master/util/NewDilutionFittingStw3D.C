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

// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/i2Tn3.00/MC_results.root";
 TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/250M/i2Tn3.00/MC_results.root";
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

 TFile* writefile = new TFile(VariableName + "_PDFResults.root", "RECREATE");
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

 global_Data = (TH3D *)DataAFB->Clone(AFBName);

 writefile->cd();
 DataAFB->Write();


 int FirstYbin = 4;
 int LastYbin = 4;
 int FirstQTbin = 1;
 int LastQTbin = 2;

 int nYbin = LastYbin - FirstYbin + 1;
 int nQTbin = 2;
 int NPar = nYbin * nQTbin * 2;

 global_FirstYbin = FirstYbin;
 global_LastYbin = LastYbin;
 global_FirstQTbin = FirstQTbin;
 global_LastQTbin = LastQTbin;

////////////////////////////////////////////////////////////////
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

   writefile->cd();
   uuAFB[i]->Write((TString)"AFB_uu_STW" + (int)i);
 }

 TH3D* ddAFB[40];
 vector<TH3D *> ddAFBs;
 for(int i = FirstSTW; i < LastSTW; i++){

   TFile* file = new TFile(STWTemplates.at(i));
   ddAFB[i] = (TH3D *)file->Get(AFB_dd_Name);

   ddAFBs.push_back(ddAFB[i]);

   writefile->cd();
   ddAFB[i]->Write((TString)"AFB_dd_STW" + (int)i);
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

 PDFReweight *AFBCalc = new PDFReweight();
 AFBCalc->InitialPDF("CT18NNLO", 0);
 AFBCalc->InputStw(0.2315);

 global_AFBCalc = AFBCalc;
////////////////////////////////////////////////////////////////

 vector<double> Su;
 vector<double> Sd;
 TH1D* SFittingResult[59];
 vector<TH1D *> SFittingResults;

 TH1D* P0Data;

 TH3D* PDFAFB[59];
 vector<TH3D *> PDFAFBs;

 TH3D* TmpAFB[59];
 vector<TH3D *> TmpAFBs;

 TH3D* AverageDilution_uu[59];
 vector<TH3D *> AverageDilution_uus;
 TH3D* AverageDilution_dd[59];
 vector<TH3D *> AverageDilution_dds;

 TH1D* PDFP0[59];
 vector<TH1D *> PDFP0s;

 TRandom3 random(0);

 double myR = 0.0;

 for(int i = 0; i < 59; i++){
   TFile* file = new TFile(rootNames.at(i));

//   file = new TFile("/Data/yfu/MainCode/run/ResBosDilution/250M/i2Tn3.00/MC_results.root");
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
     P0Data = new TH1D("P0Data", "P0Data", 100, 0, 100);
     int NPars = AFB_uu->GetNbinsY() * AFB_uu->GetNbinsZ() * 2 + 1;
     TMinuitHelper *myMinuit = new TMinuitHelper(NPars);
     myMinuit->SetFCN(udDilutionFitting);
     myMinuit->Input(0, "Stw", 0.2315, 0.01, 0.22, 0.24);
     int Index = 0;
     for(int iy = 1; iy <= AFB_uu->GetNbinsY(); iy++){
       for(int iqt = 1; iqt <= AFB_uu->GetNbinsZ(); iqt++){
         Index++; 
//         if(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin) myMinuit->Input(Index, (TString)"Su_Y" + (int)iy + "_QT" + (int)iqt, 0.2, 0.2, 0.0, 1.0);
//         if(!(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin)) myMinuit->Input(Index, (TString)"Su_Y" + (int)iy + "_QT" + (int)iqt, AverageDilution_uus.at(0)->GetBinContent(1, iy, iqt), 0.0, 0.0, 0.5);
         myMinuit->Input(Index, (TString)"Su_Y" + (int)iy + "_QT" + (int)iqt, AverageDilution_uus.at(0)->GetBinContent(1, iy, iqt), 0.0, 0.0, 1.0);
         Index++;
//         if(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin) myMinuit->Input(Index, (TString)"Sd_Y" + (int)iy + "_QT" + (int)iqt, 0.2, 0.2, 0.0, 1.0);
//         if(!(iy >= FirstYbin && iy <= LastYbin && iqt >= FirstQTbin && iqt <= LastQTbin)) myMinuit->Input(Index, (TString)"Sd_Y" + (int)iy + "_QT" + (int)iqt, AverageDilution_dds.at(0)->GetBinContent(1, iy, iqt), 0.0, 0.0, 0.5);
         myMinuit->Input(Index, (TString)"Sd_Y" + (int)iy + "_QT" + (int)iqt, AverageDilution_dds.at(0)->GetBinContent(1, iy, iqt), 0.0, 0.0, 1.0);
         //iy     = (Index - 1) / NbinsZ / 2 + 1
         //iqt    = (Index - 1) % (NBinsZ * 2) / 2 + 1
         //u or d = (Index - 1) % (NBinsZ * 2) % 2 + 1
         //Index  = (iy - 1) * (NbinsZ * 2) + (iqt - 1) * 2 + iflavor;

         P0Data->SetBinContent((iy - 1) * AverageDilution_uus.at(i)->GetNbinsZ() * 2 + (iqt - 1) * 2 + 1, AverageDilution_uus.at(0)->GetBinContent(1, iy, iqt));
         P0Data->SetBinError((iy - 1) * AverageDilution_uus.at(i)->GetNbinsZ() * 2 + (iqt - 1) * 2 + 1, AverageDilution_uus.at(0)->GetBinError(1, iy, iqt));
         P0Data->SetBinContent((iy - 1) * AverageDilution_uus.at(i)->GetNbinsZ() * 2 + (iqt - 1) * 2 + 2, AverageDilution_dds.at(0)->GetBinContent(1, iy, iqt));
         P0Data->SetBinError((iy - 1) * AverageDilution_uus.at(i)->GetNbinsZ() * 2 + (iqt - 1) * 2 + 2, AverageDilution_dds.at(0)->GetBinError(1, iy, iqt));
       }
     }

     myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
     myMinuit->Exec("MIGRAD", 100000, 0.001);
     myMinuit->GetParameter();

     double* SPar = new double[NPars];
     double* SParError = new double[NPars];
     myMinuit->GetParametersAndError(SPar, SParError);
     SFittingResult[i] = new TH1D((TString)"SFittingResult_PDF" + (int)i, (TString)"SFittingResult_PDF" + (int)i, NPars, 0, NPars);
     for(int ipar = 1; ipar <= NPars; ipar++){
       SFittingResult[i]->SetBinContent(ipar, SPar[ipar - 1]);
       SFittingResult[i]->SetBinError(ipar, SParError[ipar - 1]);
     }
     SFittingResults.push_back(SFittingResult[i]);
   }

   PDFP0[i] = new TH1D((TString)"P0Result_PDF" + (int)i, (TString)"P0Result_PDF" + (int)i, NPar + 1, 0, NPar + 1);
   for(int iy = FirstYbin; iy <= LastYbin; iy++){
     for(int iqt = 1; iqt <= nQTbin; iqt++){
       int Index = (iy - FirstYbin) * nQTbin * 2 + (iqt - 1) * 2 + 1;
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


 TH1D* STWValue[59];
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

 for(int i = 0; i < 59; i++){
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

 TH1D *STWValueError;
 PDFUncertainty *STWValuePDFunc;
 STWValuePDFunc = new PDFUncertainty();
 STWValuePDFunc->SaveVariBin();
 STWValuePDFunc->Input1DPlot("Symmetry", STWValues, STWValueError);

 TH1D *PDFP0Error;
 PDFUncertainty *PDFP0PDFunc;
 PDFP0PDFunc = new PDFUncertainty();
 PDFP0PDFunc->SaveVariBin();
 PDFP0PDFunc->Input1DPlot("Symmetry", PDFP0s, PDFP0Error);

 for(int iy = FirstYbin; iy <= LastYbin; iy++){
   for(int iqt = FirstQTbin; iqt <= LastQTbin; iqt++){
     int Index = (iy - 1) * TmpAFBs.at(0)->GetNbinsZ() * 2 + (iqt - 1) * 2 + 2;
     cout<<"MC uubar Y bin "<<iy<<" QT bin "<<iqt<<" P0: "<<AverageDilution_uus.at(0)->GetBinContent(1, iy, iqt)<<" Fitted P0: "<<SFittingResults.at(0)->GetBinContent(Index)<<" error: "<<SFittingResults.at(0)->GetBinError(Index)<<endl;
     cout<<"MC ddbar Y bin "<<iy<<" QT bin "<<iqt<<" P0: "<<AverageDilution_dds.at(0)->GetBinContent(1, iy, iqt)<<" Fitted P0: "<<SFittingResults.at(0)->GetBinContent(Index + 1)<<" error: "<<SFittingResults.at(0)->GetBinError(Index + 1)<<endl;
   }
 }

 cout<<"Central value: "<<SFittingResults.at(0)->GetBinContent(1)<<" error: "<<SFittingResults.at(0)->GetBinError(1)<<endl;
 cout<<"stw Central value: "<<STWValues.at(0)->GetBinContent(1)<<" PDF unc: "<<STWValueError->GetBinContent(1)<<endl;

////////////////////////////////////////////////////////////////////////////////////////////
//File For ePump

 TH1D* P0Theory[59];
 vector<TH1D *> P0Theorys;

 for(int i = 0; i < PDFP0s.size(); i++){
   P0Theory[i] = new TH1D((TString)"P0Theory_" + (int)i, (TString)"P0Theory_" + (int)i, NPar, 0, NPar);
   for(int ibin = 1; ibin <= NPar; ibin++){
     P0Theory[i]->SetBinContent(ibin, PDFP0s.at(i)->GetBinContent(ibin + 1));
     P0Theory[i]->SetBinError(ibin, PDFP0s.at(i)->GetBinError(ibin + 1));
   }
   P0Theorys.push_back(P0Theory[i]);
 }

 TH1D *P0TheoryError;
 PDFUncertainty *P0Theory_unc;
 P0Theory_unc = new PDFUncertainty();
 P0Theory_unc->SaveVariBin();
 P0Theory_unc->Input1DPlot("Symmetry", P0Theorys, P0TheoryError);

 FileForEPUMP *P0Theory_file = new FileForEPUMP("P0Theory");
 P0Theory_file->InputData(P0Theorys.at(0));
 P0Theory_file->InputTheory(P0Theory_unc);
 P0Theory_file->writedata();
 P0Theory_file->writetheory();

////////////////////////////////////////////////////////////////////////////////////////////

 writefile->cd();
 writefile->Write();
 writefile->Close();

 return 1;

}
