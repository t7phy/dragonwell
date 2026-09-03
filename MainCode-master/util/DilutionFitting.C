#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "CompareDataTheory/CompareDataTheory.h"
#include "TMinuitHelper/TMinuitHelper.h"
#include "Tools/Tools.h"

using namespace std;

TH2D* global_Dilution_uu;
TH2D* global_Dilution_dd;
TH2D* global_FZmass_ZY_uu;
TH2D* global_FZmass_ZY_dd;
TH2D* global_FZmass_ZY_gg;
TH2D* global_BZmass_ZY_uu;
TH2D* global_BZmass_ZY_dd;
TH2D* global_BZmass_ZY_gg;

TH2D* global_MC;
TH2D* global_Data;
TH2D* global_MC_AFB2D;
TH2D* global_Data_AFB2D;

double MinChi2 = 100000.0;

void udDilutionFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{

 double Chi2 = 0.0;

 TH2D* FZmass_ZY_uu = (TH2D *)global_FZmass_ZY_uu->Clone("FZmass_ZY_uu");
 TH2D* FZmass_ZY_dd = (TH2D *)global_FZmass_ZY_dd->Clone("FZmass_ZY_dd");
 TH2D* FZmass_ZY_gg = (TH2D *)global_FZmass_ZY_gg->Clone("FZmass_ZY_gg");
 TH2D* BZmass_ZY_uu = (TH2D *)global_BZmass_ZY_uu->Clone("BZmass_ZY_uu");
 TH2D* BZmass_ZY_dd = (TH2D *)global_BZmass_ZY_dd->Clone("BZmass_ZY_dd");
 TH2D* BZmass_ZY_gg = (TH2D *)global_BZmass_ZY_gg->Clone("BZmass_ZY_gg");
 TH2D* Dilution_uu = (TH2D *)global_Dilution_uu->Clone("Dilution_ZMass_ZY_uu");
 TH2D* Dilution_dd = (TH2D *)global_Dilution_dd->Clone("Dilution_ZMass_ZY_dd");

 Apply2DDilution(FZmass_ZY_uu, BZmass_ZY_uu, Dilution_uu, false, par[0]);
 Apply2DDilution(FZmass_ZY_dd, BZmass_ZY_dd, Dilution_dd, false, par[1]);
 Apply2DDilution(FZmass_ZY_gg, BZmass_ZY_gg, Dilution_uu, true, 0.0);

 TH2D* FZmass2D = (TH2D *)FZmass_ZY_uu->Clone("FZmass2D");
 FZmass2D->Add(FZmass_ZY_dd);
 FZmass2D->Add(FZmass_ZY_gg);

 TH2D* BZmass2D = (TH2D *)BZmass_ZY_uu->Clone("BZmass2D");
 BZmass2D->Add(BZmass_ZY_dd);
 BZmass2D->Add(BZmass_ZY_gg);

 TH2D *AFB2D = (TH2D *)FZmass2D->Clone("AFB2D");
 AFB2D->Reset();
 AFBFunction(FZmass2D, BZmass2D, AFB2D);

 TH2D *AFBDiff2D = new TH2D(AFB2D->GetName() + (TString)"_Diff", AFB2D->GetName() + (TString)"_Diff", AFB2D->GetNbinsX() / 2, 1, AFB2D->GetNbinsX() / 2, AFB2D->GetNbinsY(), 1, AFB2D->GetNbinsY());
 GetAFBDiff(AFB2D, AFBDiff2D);

 global_MC = (TH2D *)AFBDiff2D->Clone("global_AFB2D_Diff");
 global_MC_AFB2D = (TH2D *)AFB2D->Clone("AFB2D");

 Chi2 = CalculateChi2(global_Data, AFBDiff2D);
 f = Chi2;
 if(f < MinChi2) MinChi2 = f;

 delete AFBDiff2D;

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

 TString DataName = "/Data/yfu/MainCode/run/DilutionFitting/Pseudodata_0.2315/MC_results_mmht.root";
// TString DataName = "/Data/yfu/MainCode/run/DilutionFitting/If1363.01/MC_results.root";

 TString EtaRegion = "Full";

 TString VariableName = "AFB_" + EtaRegion;

 TFile* writefile = new TFile(VariableName + "_PDFResults.root", "RECREATE");
 writefile->cd();

 TString AFBName = "AFB_" + EtaRegion;

 TString Dilution2D_uu_Name = "Dilution_ZMass_ZY_uu";
 TString Dilution2D_dd_Name = "Dilution_ZMass_ZY_dd";
 TString FZmass_ZY_uu_Name = "FZmass_ZY_uu";
 TString FZmass_ZY_dd_Name = "FZmass_ZY_dd";
 TString FZmass_ZY_gg_Name = "FZmass_ZY_gg";
 TString BZmass_ZY_uu_Name = "BZmass_ZY_uu";
 TString BZmass_ZY_dd_Name = "BZmass_ZY_dd";
 TString BZmass_ZY_gg_Name = "BZmass_ZY_gg";

 TString AFB2DName = "AFB_Mass_ZY_Full";
 TString AFB2DDiffName = "AFB_Mass_ZY_Full_Diff";

 TFile *DataFile = new TFile(DataName);
// TFile *DataFile2 = new TFile(DataName2);
 TH2D *Data2DDiff = (TH2D *)DataFile->Get(AFB2DDiffName);

 TH1D *DataAFB = (TH1D *)DataFile->Get(AFBName);
 DataAFB = (TH1D *)DataAFB->Rebin(30, AFBName, massrange);

 TH2D *DataAFB2D = (TH2D *)DataFile->Get(AFB2DName);

 global_Data = (TH2D *)Data2DDiff->Clone(AFB2DDiffName);

// TH2D *DataDilution = (TH2D *)DataFile->Get(Dilution2D_uu_Name);
// TH2D *DataDilution2 = (TH2D *)DataFile2->Get(Dilution2D_uu_Name);

 writefile->cd();
 Data2DDiff->Write();
 DataAFB->Write();
 DataAFB2D->Write();

 vector<double> Su;
 vector<double> Sd;
 TH1D* SFittingResult[57];
 vector<TH1D *> SFittingResults;
 for(int i = 0; i < 1; i++){
   TFile* file = new TFile(rootNames.at(i));
   TH2D* FZmass_ZY_uu = (TH2D *)file->Get(FZmass_ZY_uu_Name);
   TH2D* FZmass_ZY_dd = (TH2D *)file->Get(FZmass_ZY_dd_Name);
   TH2D* FZmass_ZY_gg = (TH2D *)file->Get(FZmass_ZY_gg_Name);
   TH2D* BZmass_ZY_uu = (TH2D *)file->Get(BZmass_ZY_uu_Name);
   TH2D* BZmass_ZY_dd = (TH2D *)file->Get(BZmass_ZY_dd_Name);
   TH2D* BZmass_ZY_gg = (TH2D *)file->Get(BZmass_ZY_gg_Name);
   TH2D* PDFDilution_uu = (TH2D *)file->Get(Dilution2D_uu_Name);
   TH2D* PDFDilution_dd = (TH2D *)file->Get(Dilution2D_dd_Name);

   global_FZmass_ZY_uu = FZmass_ZY_uu;
   global_FZmass_ZY_dd = FZmass_ZY_dd;
   global_FZmass_ZY_gg = FZmass_ZY_gg;
   global_BZmass_ZY_uu = BZmass_ZY_uu;
   global_BZmass_ZY_dd = BZmass_ZY_dd;
   global_BZmass_ZY_gg = BZmass_ZY_gg;
   global_Dilution_uu = PDFDilution_uu;
   global_Dilution_dd = PDFDilution_dd;

   TMinuitHelper *myMinuit = new TMinuitHelper(2);
   myMinuit->SetFCN(udDilutionFitting);
   myMinuit->Input(0, "Su", 0.5, 0.5, -1.0, 1.0);
   myMinuit->Input(1, "Sd", 0.5, 0.5, -1.0, 1.0);
   myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
   myMinuit->Exec("MIGRAD", 100000, 0.001);
   myMinuit->GetParameter();
   double* SPar = new double[2];
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

   Apply2DDilution(FZmass_ZY_uu, BZmass_ZY_uu, PDFDilution_uu, false, Su.at(i));
   Apply2DDilution(FZmass_ZY_dd, BZmass_ZY_dd, PDFDilution_dd, false, Sd.at(i));
   Apply2DDilution(FZmass_ZY_gg, BZmass_ZY_gg, PDFDilution_uu, true, 0.0);

   TH2D* FZmass2D = (TH2D *)FZmass_ZY_uu->Clone("FZmass2D");
   FZmass2D->Add(FZmass_ZY_dd);
   FZmass2D->Add(FZmass_ZY_gg);

   TH2D* BZmass2D = (TH2D *)BZmass_ZY_uu->Clone("BZmass2D");
   BZmass2D->Add(BZmass_ZY_dd);
   BZmass2D->Add(BZmass_ZY_gg);

   TH1D* Converted_AFB = new TH1D((TString)"AFB_PDF" + (int)i, (TString)"AFB_PDF" + (int)i, FZmass2D->GetNbinsX(), FZmass2D->GetXaxis()->GetBinLowEdge(1), FZmass2D->GetXaxis()->GetBinUpEdge(FZmass2D->GetNbinsX()));

   AFBFunction(FZmass2D, BZmass2D, Converted_AFB);

////////////////

   writefile->cd();
   SFittingResult[i]->Write();
   global_MC->Write();
   global_MC_AFB2D->Write();
   Converted_AFB->Write();

   MinChi2 = 100000.0;
 }
/*
 TH1D* PDFAFB[57];
 TH2D* PDFDilution_uu[57];
 TH2D* PDFDilution_dd[57];
 vector<TH1D *> PDFAFBs;
 vector<TH2D *> PDFDilution_uus;
 vector<TH2D *> PDFDilution_dds;
 for(int i = 0; i < 57; i++){
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

 TH1D* STWAFB[40];
 vector<TH1D *> STWAFBs;
 for(int i = 0; i < 40; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   TH2D* FZmass_ZY_uu = (TH2D *)file->Get(FZmass_ZY_uu_Name);
   TH2D* FZmass_ZY_dd = (TH2D *)file->Get(FZmass_ZY_dd_Name);
   TH2D* FZmass_ZY_gg = (TH2D *)file->Get(FZmass_ZY_gg_Name);
   TH2D* BZmass_ZY_uu = (TH2D *)file->Get(BZmass_ZY_uu_Name);
   TH2D* BZmass_ZY_dd = (TH2D *)file->Get(BZmass_ZY_dd_Name);
   TH2D* BZmass_ZY_gg = (TH2D *)file->Get(BZmass_ZY_gg_Name);

   Apply2DDilution(FZmass_ZY_uu, BZmass_ZY_uu, PDFDilution_uus.at(0), false, Su.at(0));
   Apply2DDilution(FZmass_ZY_dd, BZmass_ZY_dd, PDFDilution_dds.at(0), false, Sd.at(0));
   Apply2DDilution(FZmass_ZY_gg, BZmass_ZY_gg, PDFDilution_uus.at(0), true, 0.0);

   TH2D* FZmass2D = (TH2D *)FZmass_ZY_uu->Clone("FZmass2D");
   FZmass2D->Add(FZmass_ZY_dd);
   FZmass2D->Add(FZmass_ZY_gg);

   TH2D* BZmass2D = (TH2D *)BZmass_ZY_uu->Clone("BZmass2D");
   BZmass2D->Add(BZmass_ZY_dd);
   BZmass2D->Add(BZmass_ZY_gg);

   STWAFB[i] = new TH1D((TString)"AFB_STW" + (int)i, (TString)"AFB_STW" + (int)i, FZmass2D->GetNbinsX(), FZmass2D->GetXaxis()->GetBinLowEdge(1), FZmass2D->GetXaxis()->GetBinUpEdge(FZmass2D->GetNbinsX()));

   AFBFunction(FZmass2D, BZmass2D, STWAFB[i]);

   STWAFBs.push_back(STWAFB[i]);

   writefile->cd();
   STWAFB[i]->Write();
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



// for(int ibinx = 1; ibinx <= DataDilution->GetNbinsX(); ibinx++){
//   for(int ibiny = 1; ibiny <= DataDilution->GetNbinsY(); ibiny++){
 //     cout<<ibinx<<" "<<ibiny<<" "<<DataDilution->GetBinContent(ibinx, ibiny)<<" "<<DataDilution2->GetBinContent(ibinx, ibiny)<<" "<<DataDilution->GetBinContent(ibinx, ibiny) - DataDilution2->GetBinContent(ibinx, ibiny)<<endl;
//   }
// }

 writefile->cd();
 writefile->Write();
 writefile->Close();

 return 1;

}
