#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "CompareDataTheory/CompareDataTheory.h"
#include "TMinuitHelper/TMinuitHelper.h"
#include "Tools/Tools.h"

using namespace std;

TH1D* global_Dilution_uu_Residual;
TH1D* global_Dilution_dd_Residual;
TH1D* global_AFB_uu;
TH1D* global_AFB_dd;
TH1D* global_Dilution_uu_Average;
TH1D* global_Dilution_dd_Average;

TH1D* global_MC;
TH1D* global_Data;

double MinChi2 = 100000.0;

void udDilutionFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{

 double Chi2 = 0.0;

 TH1D* AFB_uu = (TH1D *)global_AFB_uu->Clone("AFB_uu");
 TH1D* AFB_dd = (TH1D *)global_AFB_dd->Clone("AFB_dd");
 TH1D* Dilution_uu = (TH1D *)global_Dilution_uu_Residual->Clone("Dilution_uu_Residual");
 TH1D* Dilution_dd = (TH1D *)global_Dilution_dd_Residual->Clone("Dilution_dd_Residual");

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

 for(int ibin = 1; ibin <= AFB_uu->GetNbinsX(); ibin++){
   double Value1 = Dilution_uu->GetBinContent(ibin);
   double Value2 = AFB_uu->GetBinContent(ibin);
   double Value3 = Dilution_dd->GetBinContent(ibin);
   double Value4 = AFB_dd->GetBinContent(ibin);

   double Error1 = Dilution_uu->GetBinError(ibin);
   double Error2 = AFB_uu->GetBinError(ibin);
   double Error3 = Dilution_dd->GetBinError(ibin);
   double Error4 = AFB_dd->GetBinError(ibin);

   double Value = Value1 * Value2 + Value3 * Value4;
   double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

   AFB->SetBinContent(ibin, Value);
   AFB->SetBinError(ibin, Error);
 }


 Chi2 = CalculateChi2(global_Data, AFB);
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

 TString EtaRegion = "Full";

 TString VariableName = "AFB_" + EtaRegion;

 TFile* writefile = new TFile(VariableName + "_PDFResults.root", "RECREATE");
 writefile->cd();

 TString AFBName = "AFB_" + EtaRegion;

 TString Dilution_uu_Name = "CoefficientDilution_ZMass_" + EtaRegion + "_uu_Residual";
 TString Dilution_dd_Name = "CoefficientDilution_ZMass_" + EtaRegion + "_dd_Residual";
 TString AFB_uu_Name = "AFB_" + EtaRegion + "_uu";
 TString AFB_dd_Name = "AFB_" + EtaRegion + "_dd";

 if(EtaRegion == "Full") EtaRegion = "";
 if(EtaRegion == "CC") EtaRegion = "_CC";
 if(EtaRegion == "CF") EtaRegion = "_CF";
 TString ZMass_Name = "ZMass" + EtaRegion;

 TFile *DataFile = new TFile(DataName);

 TH1D *DataAFB = (TH1D *)DataFile->Get(AFBName);

 global_Data = (TH1D *)DataAFB->Clone(AFBName);

 writefile->cd();
 DataAFB->Write();


////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////

 vector<double> Su;
 vector<double> Sd;
 TH1D* SFittingResult[59];
 vector<TH1D *> SFittingResults;

 TH1D *AveAFBHist[59];
 vector<TH1D *> AveAFBHists;

 TH1D* PDFAFB[59];
 vector<TH1D *> PDFAFBs;

 for(int i = 0; i < 59; i++){
   TFile* file = new TFile(rootNames.at(i));
   TH1D* Dilution_uu = (TH1D *)file->Get(Dilution_uu_Name);
   TH1D* Dilution_dd = (TH1D *)file->Get(Dilution_dd_Name);
   TH1D* AFB_uu = (TH1D *)file->Get(AFB_uu_Name);
   TH1D* AFB_dd = (TH1D *)file->Get(AFB_dd_Name);
   TH1D* ZMass = (TH1D *)file->Get(ZMass_Name);
   ZMass->Rebin(2);

   global_Dilution_uu_Residual = Dilution_uu;
   global_Dilution_dd_Residual = Dilution_dd;
   global_AFB_uu = AFB_uu;
   global_AFB_dd = AFB_dd;

   TMinuitHelper *myMinuit = new TMinuitHelper(2);
   myMinuit->SetFCN(udDilutionFitting);
   myMinuit->Input(0, "Su", 0.2, 0.5, 0.0, 0.5);
   myMinuit->Input(1, "Sd", 0.2, 0.5, 0.0, 0.5);
   myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
   myMinuit->Exec("MIGRAD", 100000, 0.001);
   myMinuit->GetParameter();
   double* SPar = new double[2];
   double* SParError = new double[2];
   myMinuit->GetParametersAndError(SPar, SParError);
   Su.push_back(SPar[0]);
   Sd.push_back(SPar[1]);

   SFittingResult[i] = new TH1D((TString)"SFittingResult_PDF" + (int)i, (TString)"SFittingResult_PDF" + (int)i, 2, 0, 2);
   SFittingResult[i]->SetBinContent(1, SPar[0]);
   SFittingResult[i]->SetBinContent(2, SPar[1]);
   SFittingResult[i]->SetBinError(1, SParError[0]);
   SFittingResult[i]->SetBinError(2, SParError[1]);

   SFittingResults.push_back(SFittingResult[i]);



/////////////////

////////////////

   writefile->cd();
   SFittingResult[i]->Write();
   global_MC->Write((TString)"AFB_PDF" + (int)i);
   PDFAFBs.push_back(global_MC);

   TH1D* TmpAFB = (TH1D *)global_MC->Clone("TmpAFB");
   TmpAFB->Reset();
   for(int ibin = 1; ibin <= AFB_uu->GetNbinsX(); ibin++){
     double Value1 = Dilution_uu->GetBinContent(ibin) + SFittingResults.at(0)->GetBinContent(1);
     double Value2 = AFB_uu->GetBinContent(ibin);
     double Value3 = Dilution_dd->GetBinContent(ibin) + SFittingResults.at(0)->GetBinContent(2);
     double Value4 = AFB_dd->GetBinContent(ibin);

     double Error1 = Dilution_uu->GetBinError(ibin);
     double Error2 = AFB_uu->GetBinError(ibin);
     double Error3 = Dilution_dd->GetBinError(ibin);
     double Error4 = AFB_dd->GetBinError(ibin);

     double Value = Value1 * Value2 + Value3 * Value4;
     double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

     TmpAFB->SetBinContent(ibin, Value);
     TmpAFB->SetBinError(ibin, Error);
   }

   AveAFBHist[i] = new TH1D((TString)"AveAFB_PDF" + (int)i, (TString)"AveAFB_PDF" + (int)i, 1, 0, 1);
   double NF = 0.0;
   double NB = 0.0;
   for(int ibin = 1; ibin <= ZMass->GetNbinsX(); ibin++){
     NF += ZMass->GetBinContent(ibin) * (1 + TmpAFB->GetBinContent(ibin) / 2.0);
     NB += ZMass->GetBinContent(ibin) * (1 - TmpAFB->GetBinContent(ibin) / 2.0);
   }
   double Value = (NF - NB) / (NF + NB);
   AveAFBHist[i]->SetBinContent(1, Value);
   AveAFBHists.push_back(AveAFBHist[i]);

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

 TH1D* AveAFB_Error;
 PDFUncertainty *AveAFBunc;
 AveAFBunc = new PDFUncertainty();
 AveAFBunc->Input1DPlot("Symmetry", AveAFBHists, AveAFB_Error);
 cout<<"uubar P0: "<<SFittingResults.at(0)->GetBinContent(1)<<" error: "<<SFittingResults.at(0)->GetBinError(1)<<endl;
 cout<<"ddbar P0: "<<SFittingResults.at(0)->GetBinContent(2)<<" error: "<<SFittingResults.at(0)->GetBinError(2)<<endl;
 cout<<"Average AFB: "<<AveAFBHists.at(0)->GetBinContent(1)<<endl;
 cout<<"Average AFB PDF unc: "<<AveAFB_Error->GetBinContent(1)<<endl;

// TH1D* AFBunc_Error;
// PDFUncertainty *AFBunc;
// AFBunc = new PDFUncertainty();
// AFBunc->Input1DPlot("Symmetry", PDFHists, AFBunc_Error);

 writefile->cd();
 writefile->Write();
 writefile->Close();

 return 1;

}
