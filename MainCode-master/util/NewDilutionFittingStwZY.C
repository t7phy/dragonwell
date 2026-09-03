#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "Uncertainty/FitAFBStw.h"
#include "CompareDataTheory/CompareDataTheory.h"
#include "TMinuitHelper/TMinuitHelper.h"
#include "Tools/Tools.h"

using namespace std;

TH1D* global_Dilution_CC_uu_Residual;
TH1D* global_Dilution_CC_dd_Residual;
TH1D* global_AFB_CC_uu;
TH1D* global_AFB_CC_dd;
TH1D* global_Dilution_CC_uu_Average;
TH1D* global_Dilution_CC_dd_Average;
TH1D* global_uuFittedSlope_CC;
TH1D* global_uuFittedOffset_CC;
TH1D* global_ddFittedSlope_CC;
TH1D* global_ddFittedOffset_CC;

TH1D* global_Dilution_CF_uu_Residual;
TH1D* global_Dilution_CF_dd_Residual;
TH1D* global_AFB_CF_uu;
TH1D* global_AFB_CF_dd;
TH1D* global_Dilution_CF_uu_Average;
TH1D* global_Dilution_CF_dd_Average;
TH1D* global_uuFittedSlope_CF;
TH1D* global_uuFittedOffset_CF;
TH1D* global_ddFittedSlope_CF;
TH1D* global_ddFittedOffset_CF;

TH1D* global_MC_CC;
TH1D* global_MC_CF;
TH1D* global_Data_CC;
TH1D* global_Data_CF;

double MinChi2 = 100000.0;

void udDilutionFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{

 double Chi2 = 0.0;

 TH1D* AFB_CC_uu = (TH1D *)global_AFB_CC_uu->Clone("AFB_CC_uu");
 TH1D* AFB_CC_dd = (TH1D *)global_AFB_CC_dd->Clone("AFB_CC_dd");
 TH1D* Dilution_CC_uu = (TH1D *)global_Dilution_CC_uu_Residual->Clone("Dilution_CC_uu_Residual");
 TH1D* Dilution_CC_dd = (TH1D *)global_Dilution_CC_dd_Residual->Clone("Dilution_CC_dd_Residual");

 TH1D* AFB_CF_uu = (TH1D *)global_AFB_CF_uu->Clone("AFB_CF_uu");
 TH1D* AFB_CF_dd = (TH1D *)global_AFB_CF_dd->Clone("AFB_CF_dd");
 TH1D* Dilution_CF_uu = (TH1D *)global_Dilution_CF_uu_Residual->Clone("Dilution_CF_uu_Residual");
 TH1D* Dilution_CF_dd = (TH1D *)global_Dilution_CF_dd_Residual->Clone("Dilution_CF_dd_Residual");

 Dilution_CC_uu->Reset();
 Dilution_CC_dd->Reset();
 Dilution_CF_uu->Reset();
 Dilution_CF_dd->Reset();

 for(int ibin = 1; ibin <= Dilution_CC_uu->GetNbinsX(); ibin++){
   double Value = global_Dilution_CC_uu_Residual->GetBinContent(ibin) + par[0];
   double Error = global_Dilution_CC_uu_Residual->GetBinError(ibin);
   Dilution_CC_uu->SetBinContent(ibin, Value);
   Dilution_CC_uu->SetBinError(ibin, Error);
 }

 for(int ibin = 1; ibin <= Dilution_CC_dd->GetNbinsX(); ibin++){
   double Value = global_Dilution_CC_dd_Residual->GetBinContent(ibin) + par[1];
   double Error = global_Dilution_CC_dd_Residual->GetBinError(ibin);
   Dilution_CC_dd->SetBinContent(ibin, Value);
   Dilution_CC_dd->SetBinError(ibin, Error);
 }

 for(int ibin = 1; ibin <= Dilution_CF_uu->GetNbinsX(); ibin++){
   double Value = global_Dilution_CF_uu_Residual->GetBinContent(ibin) + par[2];
   double Error = global_Dilution_CF_uu_Residual->GetBinError(ibin);
   Dilution_CF_uu->SetBinContent(ibin, Value);
   Dilution_CF_uu->SetBinError(ibin, Error);
 }

 for(int ibin = 1; ibin <= Dilution_CF_dd->GetNbinsX(); ibin++){
   double Value = global_Dilution_CF_dd_Residual->GetBinContent(ibin) + par[3];
   double Error = global_Dilution_CF_dd_Residual->GetBinError(ibin);
   Dilution_CF_dd->SetBinContent(ibin, Value);
   Dilution_CF_dd->SetBinError(ibin, Error);
 }


 TH1D* AFB_CC = (TH1D *)AFB_CC_uu->Clone("AFB_Hadron_CC");
 AFB_CC->Reset();
 TH1D* AFB_CF = (TH1D *)AFB_CF_uu->Clone("AFB_Hadron_CF");
 AFB_CF->Reset();

 for(int ibin = 1; ibin <= AFB_CC_uu->GetNbinsX(); ibin++){
   double Value1 = Dilution_CC_uu->GetBinContent(ibin);
   double Value2 = global_uuFittedSlope_CC->GetBinContent(ibin) * par[4] + global_uuFittedOffset_CC->GetBinContent(ibin);

   double Value3 = Dilution_CC_dd->GetBinContent(ibin);
   double Value4 = global_ddFittedSlope_CC->GetBinContent(ibin) * par[4] + global_ddFittedOffset_CC->GetBinContent(ibin);

//   double Error1 = Dilution_CC_uu->GetBinError(ibin);
   double Error1 = 0.0;
//   double Error2 = global_uuFittedSlope_CC->GetBinError(ibin) * par[4];
   double Error2 = 0.0;

//   double Error3 = Dilution_CC_dd->GetBinError(ibin);
   double Error3 = 0.0;
//   double Error4 = global_ddFittedSlope_CC->GetBinError(ibin) * par[4];
   double Error4 = 0.0;

   double Value = Value1 * Value2 + Value3 * Value4;
   double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

   AFB_CC->SetBinContent(ibin, Value);
   AFB_CC->SetBinError(ibin, Error);
 }

 for(int ibin = 1; ibin <= AFB_CF_uu->GetNbinsX(); ibin++){
   double Value1 = Dilution_CF_uu->GetBinContent(ibin);
   double Value2 = global_uuFittedSlope_CF->GetBinContent(ibin) * par[4] + global_uuFittedOffset_CF->GetBinContent(ibin);

   double Value3 = Dilution_CF_dd->GetBinContent(ibin);
   double Value4 = global_ddFittedSlope_CF->GetBinContent(ibin) * par[4] + global_ddFittedOffset_CF->GetBinContent(ibin);

//   double Error1 = Dilution_CF_uu->GetBinError(ibin);
   double Error1 = 0.0;
//   double Error2 = global_uuFittedSlope_CF->GetBinError(ibin) * par[4];
   double Error2 = 0.0;

//   double Error3 = Dilution_CF_dd->GetBinError(ibin);
   double Error3 = 0.0;
//   double Error4 = global_ddFittedSlope_CF->GetBinError(ibin) * par[4];
   double Error4 = 0.0;

   double Value = Value1 * Value2 + Value3 * Value4;
   double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

   AFB_CF->SetBinContent(ibin, Value);
   AFB_CF->SetBinError(ibin, Error);
 }


 Chi2 = CalculateChi2(global_Data_CC, AFB_CC) + CalculateChi2(global_Data_CF, AFB_CF);
 f = Chi2;
 if(f < MinChi2) MinChi2 = f;

 global_MC_CC = (TH1D *)AFB_CC->Clone("Global_AFB_Hadron_CC");
 global_MC_CF = (TH1D *)AFB_CF->Clone("Global_AFB_Hadron_CF");

 delete AFB_CC;
 delete AFB_CF;

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

 TString EtaRegion = "CF";

 TString VariableName = "AFB_" + EtaRegion;

 TFile* writefile = new TFile(VariableName + "_PDFResults.root", "RECREATE");
 writefile->cd();

 TString AFBName_CC = "AFB_CC";
 TString AFBName_CF = "AFB_CF";

 TString Dilution_CC_uu_Name = "CoefficientDilution_ZMass_CC_uu_Residual";
 TString Dilution_CC_dd_Name = "CoefficientDilution_ZMass_CC_dd_Residual";
 TString AFB_CC_uu_Name = "AFB_CC_uu";
 TString AFB_CC_dd_Name = "AFB_CC_dd";

 TString Dilution_CF_uu_Name = "CoefficientDilution_ZMass_CF_uu_Residual";
 TString Dilution_CF_dd_Name = "CoefficientDilution_ZMass_CF_dd_Residual";
 TString AFB_CF_uu_Name = "AFB_CF_uu";
 TString AFB_CF_dd_Name = "AFB_CF_dd";

 TFile *DataFile = new TFile(DataName);

 TH1D *DataAFB_CC = (TH1D *)DataFile->Get(AFBName_CC);
 TH1D *DataAFB_CF = (TH1D *)DataFile->Get(AFBName_CF);

 global_Data_CC = (TH1D *)DataAFB_CC->Clone(AFBName_CC);
 global_Data_CF = (TH1D *)DataAFB_CF->Clone(AFBName_CF);

 writefile->cd();
 DataAFB_CC->Write();
 DataAFB_CF->Write();


////////////////////////////////////////////////////////////////

 TH1D* uuAFB_CC[40];
 vector<TH1D *> uuAFB_CCs;
 for(int i = 0; i < 40; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   uuAFB_CC[i] = (TH1D *)file->Get(AFB_CC_uu_Name);

   uuAFB_CCs.push_back(uuAFB_CC[i]);

   writefile->cd();
 }

 TH1D* uuAFB_CF[40];
 vector<TH1D *> uuAFB_CFs;
 for(int i = 0; i < 40; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   uuAFB_CF[i] = (TH1D *)file->Get(AFB_CF_uu_Name);

   uuAFB_CFs.push_back(uuAFB_CF[i]);

   writefile->cd();
 }


 TH1D* ddAFB_CC[40];
 vector<TH1D *> ddAFB_CCs;
 for(int i = 0; i < 40; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   ddAFB_CC[i] = (TH1D *)file->Get(AFB_CC_dd_Name);

   ddAFB_CCs.push_back(ddAFB_CC[i]);

   writefile->cd();
 }

 TH1D* ddAFB_CF[40];
 vector<TH1D *> ddAFB_CFs;
 for(int i = 0; i < 40; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   ddAFB_CF[i] = (TH1D *)file->Get(AFB_CF_dd_Name);

   ddAFB_CFs.push_back(ddAFB_CF[i]);

   writefile->cd();
 }

 vector<TH1D *> uuLinearPlot_CC;
 vector<TH1D *> ddLinearPlot_CC;
 TH1D* uuFittedSlope_CC;
 TH1D* uuFittedOffset_CC;
 TH1D* ddFittedSlope_CC;
 TH1D* ddFittedOffset_CC;
 FitAFBStw* uuSlopeAndOffset_CC = new FitAFBStw();
 uuSlopeAndOffset_CC->Input(uuAFB_CCs, 0.2255, 0.2372, uuLinearPlot_CC, uuFittedSlope_CC, uuFittedOffset_CC);
 FitAFBStw* ddSlopeAndOffset_CC = new FitAFBStw();
 ddSlopeAndOffset_CC->Input(ddAFB_CCs, 0.2255, 0.2372, ddLinearPlot_CC, ddFittedSlope_CC, ddFittedOffset_CC);

 vector<TH1D *> uuLinearPlot_CF;
 vector<TH1D *> ddLinearPlot_CF;
 TH1D* uuFittedSlope_CF;
 TH1D* uuFittedOffset_CF;
 TH1D* ddFittedSlope_CF;
 TH1D* ddFittedOffset_CF;
 FitAFBStw* uuSlopeAndOffset_CF = new FitAFBStw();
 uuSlopeAndOffset_CF->Input(uuAFB_CFs, 0.2255, 0.2372, uuLinearPlot_CF, uuFittedSlope_CF, uuFittedOffset_CF);
 FitAFBStw* ddSlopeAndOffset_CF = new FitAFBStw();
 ddSlopeAndOffset_CF->Input(ddAFB_CFs, 0.2255, 0.2372, ddLinearPlot_CF, ddFittedSlope_CF, ddFittedOffset_CF);

 global_uuFittedSlope_CC = uuFittedSlope_CC;
 global_uuFittedOffset_CC = uuFittedOffset_CC;
 global_ddFittedSlope_CC = ddFittedSlope_CC;
 global_ddFittedOffset_CC = ddFittedOffset_CC;

 global_uuFittedSlope_CF = uuFittedSlope_CF;
 global_uuFittedOffset_CF = uuFittedOffset_CF;
 global_ddFittedSlope_CF = ddFittedSlope_CF;
 global_ddFittedOffset_CF = ddFittedOffset_CF;

////////////////////////////////////////////////////////////////

 vector<double> Su;
 vector<double> Sd;
 TH1D* SFittingResult[59];
 vector<TH1D *> SFittingResults;

 TH1D *AveAFBHist[59];
 vector<TH1D *> AveAFBHists;

 TH1D* PDFAFB[59];
 vector<TH1D *> PDFAFBs;

 for(int i = 0; i < 1; i++){
   TFile* file = new TFile(rootNames.at(i));
   TH1D* Dilution_CC_uu = (TH1D *)file->Get(Dilution_CC_uu_Name);
   TH1D* Dilution_CC_dd = (TH1D *)file->Get(Dilution_CC_dd_Name);
   TH1D* AFB_CC_uu = (TH1D *)file->Get(AFB_CC_uu_Name);
   TH1D* AFB_CC_dd = (TH1D *)file->Get(AFB_CC_dd_Name);

   TH1D* Dilution_CF_uu = (TH1D *)file->Get(Dilution_CF_uu_Name);
   TH1D* Dilution_CF_dd = (TH1D *)file->Get(Dilution_CF_dd_Name);
   TH1D* AFB_CF_uu = (TH1D *)file->Get(AFB_CF_uu_Name);
   TH1D* AFB_CF_dd = (TH1D *)file->Get(AFB_CF_dd_Name);

   global_Dilution_CC_uu_Residual = Dilution_CC_uu;
   global_Dilution_CC_dd_Residual = Dilution_CC_dd;
   global_AFB_CC_uu = AFB_CC_uu;
   global_AFB_CC_dd = AFB_CC_dd;

   global_Dilution_CF_uu_Residual = Dilution_CF_uu;
   global_Dilution_CF_dd_Residual = Dilution_CF_dd;
   global_AFB_CF_uu = AFB_CF_uu;
   global_AFB_CF_dd = AFB_CF_dd;

   TMinuitHelper *myMinuit = new TMinuitHelper(5);
   myMinuit->SetFCN(udDilutionFitting);
   myMinuit->Input(0, "Su_CC", 0.2, 0.5, 0.0, 0.5);
   myMinuit->Input(1, "Sd_CC", 0.2, 0.5, 0.0, 0.5);
   myMinuit->Input(2, "Su_CF", 0.2, 0.5, 0.0, 0.5);
   myMinuit->Input(3, "Sd_CF", 0.2, 0.5, 0.0, 0.5);
   myMinuit->Input(4, "Stw", 0.2315, 0.01, 0.23, 0.24);
   myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
   myMinuit->Exec("MIGRAD", 100000, 0.001);
   myMinuit->GetParameter();
   double* SPar = new double[3];
   myMinuit->GetParameters(SPar);
   Su.push_back(SPar[0]);
   Sd.push_back(SPar[1]);

   SFittingResult[i] = new TH1D((TString)"SFittingResult_PDF" + (int)i, (TString)"SFittingResult_PDF" + (int)i, 2, 0, 2);
   SFittingResult[i]->SetBinContent(1, SPar[0]);
   SFittingResult[i]->SetBinContent(2, SPar[1]);
   SFittingResult[i]->SetBinError(1, 0);
   SFittingResult[i]->SetBinError(2, 0);

   SFittingResults.push_back(SFittingResult[i]);



/////////////////

////////////////

   writefile->cd();
   SFittingResult[i]->Write();
   global_MC_CC->Write((TString)"AFB_CC_PDF" + (int)i);
   global_MC_CF->Write((TString)"AFB_CF_PDF" + (int)i);

   PDFAFBs.push_back(global_MC_CC);

   MinChi2 = 100000.0;
 }

/* for(int i = 0; i < 57; i++){
   TFile* file = new TFile(rootNames.at(i));
   TH2D* FZmass_ZY_uu = (TH2D *)file->Get(FZmass_ZY_uu_Name);
   TH2D* FZmass_ZY_dd = (TH2D *)file->Get(FZmass_ZY_dd_Name);
   TH2D* FZmass_ZY_gg = (TH2D *)file->Get(FZmass_ZY_gg_Name);
   TH2D* BZmass_ZY_uu = (TH2D *)file->Get(BZmass_ZY_uu_Name);
   TH2D* BZmass_ZY_dd = (TH2D *)file->Get(BZmass_ZY_dd_Name);
   TH2D* BZmass_ZY_gg = (TH2D *)file->Get(BZmass_ZY_gg_Name);
   PDFDilution_uu[i] = (TH2D *)file->Get(Dilution2D_uu_Name);
   PDFDilution_dd[i] = (TH2D *)file->Get(Dilution2D_dd_Name);

   Apply2DDilution(FZmass_ZY_uu, BZmass_ZY_uu, PDFDilution_uu[i], false, Su.at(i));
   Apply2DDilution(FZmass_ZY_dd, BZmass_ZY_dd, PDFDilution_dd[i], false, Sd.at(i));
   Apply2DDilution(FZmass_ZY_gg, BZmass_ZY_gg, PDFDilution_uu[i], true, 0.0);

   TH2D* FZmass2D = (TH2D *)FZmass_ZY_uu->Clone("FZmass2D");
   FZmass2D->Add(FZmass_ZY_dd);
   FZmass2D->Add(FZmass_ZY_gg);

   TH2D* BZmass2D = (TH2D *)BZmass_ZY_uu->Clone("BZmass2D");
   BZmass2D->Add(BZmass_ZY_dd);
   BZmass2D->Add(BZmass_ZY_gg);

   PDFAFB[i] = new TH1D((TString)"AFB_PDF" + (int)i, (TString)"AFB_PDF" + (int)i, FZmass2D->GetNbinsX(), FZmass2D->GetXaxis()->GetBinLowEdge(1), FZmass2D->GetXaxis()->GetBinUpEdge(FZmass2D->GetNbinsX()));

   AFBFunction(FZmass2D, BZmass2D, PDFAFB[i]);

   PDFAFBs.push_back(PDFAFB[i]);
   PDFDilution_uus.push_back(PDFDilution_uu[i]);
   PDFDilution_dds.push_back(PDFDilution_dd[i]);

   writefile->cd();
   PDFAFB[i]->Write();

   cout<<Su.at(i)<<" "<<Sd.at(i)<<" "<<SFittingResult[i]->GetBinContent(1)<<" "<<SFittingResult[i]->GetBinContent(2)<<endl;
 }

*/


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

 TH1D *SFittingResultError;
 PDFUncertainty *SFittingResultPDFunc;
 SFittingResultPDFunc = new PDFUncertainty();
 SFittingResultPDFunc->SaveVariBin();
 SFittingResultPDFunc->Input1DPlot("Symmetry", SFittingResults, SFittingResultError);
*/

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

 writefile->cd();
 writefile->Write();
 writefile->Close();

 return 1;

}
