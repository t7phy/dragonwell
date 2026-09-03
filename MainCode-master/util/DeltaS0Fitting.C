#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "CompareDataTheory/CompareDataTheory.h"
#include "TMinuitHelper/TMinuitHelper.h"
#include "Tools/Tools.h"

using namespace std;


TH1D* global_AFBDiff_MC;
TH1D* global_AFBDiff_Data;
TH1D* global_AFBQuarkDiff;
TH1D* global_AFBFraction;
TH1D* global_AFBS0Fraction;

double MinChi2 = 100000.0;

void DeltaS0Fitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 double Chi2 = 0.0;

 TH1D* AFBDiff_MC = (TH1D *)global_AFBDiff_MC->Clone("AFBDiff_MC");
 TH1D* AFBDiff_Data = (TH1D *)global_AFBDiff_Data->Clone("AFBDiff_Data");
 TH1D* AFBQuarkDiff = (TH1D *)global_AFBQuarkDiff->Clone("AFBQuarkDiff");
 TH1D* AFBFraction = (TH1D *)global_AFBFraction->Clone("AFBFraction");
 TH1D* AFBS0Fraction = (TH1D *)global_AFBS0Fraction->Clone("AFBS0Fraction");

 TH1D* HadronDelta = (TH1D *)AFBDiff_MC->Clone("HadronDelta");
 HadronDelta->Add(AFBDiff_Data, -1);
 HadronDelta->Divide(AFBQuarkDiff);
 HadronDelta->Scale(0.5);

 int FirstBin = 3;
 int LastBin = AFBFraction->GetNbinsX();

// for(int ibin = 1; ibin <= AFBFraction->GetNbinsX(); ibin++){
 for(int ibin = FirstBin; ibin <= LastBin; ibin++){
   double Value = AFBFraction->GetBinContent(ibin);
   double S0Fraction = AFBS0Fraction->GetBinContent(ibin);
   AFBFraction->SetBinContent(ibin, par[0] * S0Fraction + Value * par[1]);
   AFBFraction->SetBinError(ibin, 0);
 }

 Chi2 = CalculateChi2(HadronDelta, AFBFraction, FirstBin, LastBin);
 f = Chi2;
 if(f < MinChi2) MinChi2 = f;

 delete AFBDiff_MC;
 delete AFBDiff_Data;
 delete AFBQuarkDiff;
 delete AFBFraction;
 delete HadronDelta;

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

// TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/Pseudodata_0.2315/MC_results_nnpdf.root";
// TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/If1363.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/Pseudodata_0.2315/MC_results_DilutionDiff.root";
 TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/Pseudodata_0.2315/MC_results_AFBRotation.root";

 TString EtaRegion = "Full";

 TString VariableName = "AFB_" + EtaRegion;

 TFile* writefile = new TFile(VariableName + "_PDFResults.root", "RECREATE");
 writefile->cd();

 TString DiffName = "AFBDiff_" + EtaRegion;
 TString QuarkDiffName = "AFBQuarkDiff_" + EtaRegion;
 TString FractionName = "AFBQuarkFraction_" + EtaRegion;
 TString S0FractionName = "AFBS0Fraction_" + EtaRegion;
 TString SlopeName = "AFBSlope_" + EtaRegion;
 TString QuarkSlopeName = "AFBQuarkSlope_" + EtaRegion;
 TString Dilution_uu_Name = "Dilution_ZMass_" + EtaRegion + "_uu";
 TString Dilution_dd_Name = "Dilution_ZMass_" + EtaRegion + "_dd";
 TString FZmass_uu_Name = "FZmass_uu";
 TString FZmass_dd_Name = "FZmass_dd";
 TString FZmass_gg_Name = "FZmass_gg";
 TString BZmass_uu_Name = "BZmass_uu";
 TString BZmass_dd_Name = "BZmass_dd";
 TString BZmass_gg_Name = "BZmass_gg";

 TFile *DataFile = new TFile(DataName);
 TH1D *DataAFB = (TH1D *)DataFile->Get(VariableName);
 TH1D *DataSlope = (TH1D *)DataFile->Get(SlopeName);
 TH1D *DataAFBDiff = (TH1D *)DataFile->Get(DiffName);

 global_AFBDiff_Data = (TH1D *)DataAFBDiff->Clone(DiffName);
// TH1D *DataAFB_60_120 = (TH1D *)DataAFB->Rebin(30, VariableName, massrange);

 writefile->cd();
 DataAFB->Write();
// DataAFB_60_120->Write();

 int FirstBin = 11;
 int LastBin = 20;

 TH1D *PDFS0[57];
 TH1D *Dilution_uu[57];
 TH1D *Dilution_dd[57];
 TH1D *DeltaD_uu[57];
 TH1D *DeltaD_dd[57];
 vector<TH1D *> PDFS0s;
 vector<TH1D *> Dilution_uus;
 vector<TH1D *> Dilution_dds;
 vector<TH1D *> DeltaD_uus;
 vector<TH1D *> DeltaD_dds;
 vector<double> S0;
 vector<double> Su;
 vector<double> Sd;
 for(int i = 0; i < 1; i++){
   TFile* file = new TFile(rootNames.at(i));

   writefile->cd();
   TH1D* QuarkSlope = (TH1D *)file->Get(QuarkSlopeName);
   TH1D* Slope = (TH1D *)file->Get(SlopeName);

   TH1D* AFBDiff = (TH1D *)file->Get(DiffName);
   TH1D* AFBQuarkDiff = (TH1D *)file->Get(QuarkDiffName);
   TH1D* AFBFraction = (TH1D *)file->Get(FractionName);
   TH1D* AFBS0Fraction = (TH1D *)file->Get(S0FractionName);

   PDFS0[i] = (TH1D *)DataSlope->Clone((TString)"S0_PDF" + (int)i);
   PDFS0[i]->SetBinContent(1, (1 - DataSlope->GetBinContent(1) / QuarkSlope->GetBinContent(1)) / 2);
   PDFS0[i]->SetBinError(1, (DataSlope->GetBinError(1) / QuarkSlope->GetBinContent(1)) / 2);

   cout<<"Data S0: "<<PDFS0[i]->GetBinContent(1)<<endl;

   Dilution_uu[i] = (TH1D *)file->Get(Dilution_uu_Name);
   Dilution_dd[i] = (TH1D *)file->Get(Dilution_dd_Name);
   DeltaD_uu[i] = (TH1D *)Dilution_uu[i]->Clone((TString)"DeltaD_uu_PDF" + (int)i);
   DeltaD_dd[i] = (TH1D *)Dilution_dd[i]->Clone((TString)"DeltaD_dd_PDF" + (int)i);

   for(int ibinx = 1; ibinx <= Dilution_uu[i]->GetNbinsX(); ibinx++){

     double S0 = (1 - Slope->GetBinContent(1) / QuarkSlope->GetBinContent(1)) / 2;
     double S0Error = (Slope->GetBinError(1) / QuarkSlope->GetBinContent(1)) / 2;

     DeltaD_uu[i]->SetBinContent(ibinx, Dilution_uu[i]->GetBinContent(ibinx) - S0);
     DeltaD_uu[i]->SetBinError(ibinx, sqrt(Dilution_uu[i]->GetBinError(ibinx) * Dilution_uu[i]->GetBinError(ibinx) + S0Error * S0Error));
     DeltaD_dd[i]->SetBinContent(ibinx, Dilution_dd[i]->GetBinContent(ibinx) - S0);
     DeltaD_dd[i]->SetBinError(ibinx, sqrt(Dilution_dd[i]->GetBinError(ibinx) * Dilution_dd[i]->GetBinError(ibinx) + S0Error * S0Error));

     if(ibinx == 1) cout<<"MC S0: "<<S0<<endl;
   }

   global_AFBDiff_MC = AFBDiff;
   global_AFBQuarkDiff = AFBQuarkDiff;
   global_AFBFraction = AFBFraction;
   global_AFBS0Fraction = AFBS0Fraction;

   TMinuitHelper *myMinuit = new TMinuitHelper(2);
   myMinuit->SetFCN(DeltaS0Fitting);
   myMinuit->Input(0, "S0", 0.5, 0.5, -1.0, 1.0);
   myMinuit->Input(1, "Su", 0.5, 0.5, -1.0, 1.0);
   myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
   myMinuit->Exec("MIGRAD", 100000, 0.001);
   myMinuit->GetParameter();
   double* SPar = new double[2];
   myMinuit->GetParameters(SPar);
   S0.push_back(SPar[0]);
   Su.push_back(SPar[1]);
   Sd.push_back(SPar[1] * (-1.0));

   PDFS0s.push_back(PDFS0[i]);
   DeltaD_uus.push_back(DeltaD_uu[i]);
   DeltaD_dds.push_back(DeltaD_dd[i]);
 }


 TH1D *PDFHist[57];
 vector<TH1D *> PDFHists;

 for(int i = 0; i < 1; i++){
   TFile* file = new TFile(rootNames.at(i));

   TH1D* FZmass_uu = (TH1D *)file->Get(FZmass_uu_Name);
   TH1D* FZmass_dd = (TH1D *)file->Get(FZmass_dd_Name);
   TH1D* FZmass_gg = (TH1D *)file->Get(FZmass_gg_Name);
   TH1D* BZmass_uu = (TH1D *)file->Get(BZmass_uu_Name);
   TH1D* BZmass_dd = (TH1D *)file->Get(BZmass_dd_Name);
   TH1D* BZmass_gg = (TH1D *)file->Get(BZmass_gg_Name);
   TH1D* DilutionMC_uu = (TH1D *)file->Get(Dilution_uu_Name);
   TH1D* DilutionMC_dd = (TH1D *)file->Get(Dilution_dd_Name);

   FZmass_uu->Rebin(2);
   FZmass_dd->Rebin(2);
   FZmass_gg->Rebin(2);
   BZmass_uu->Rebin(2);
   BZmass_dd->Rebin(2);
   BZmass_gg->Rebin(2);

   TH1D* PDFDilution_uu = (TH1D *)DeltaD_uus.at(i)->Clone("Dilution_uu");
   TH1D* PDFDilution_dd = (TH1D *)DeltaD_dds.at(i)->Clone("Dilution_dd");
   //ApplyS0(DeltaD_uus.at(i), PDFDilution_uu, PDFS0s.at(i)->GetBinContent(1), PDFS0s.at(i)->GetBinError(1));
   //ApplyS0(DeltaD_dds.at(i), PDFDilution_dd, PDFS0s.at(i)->GetBinContent(1), PDFS0s.at(i)->GetBinError(1));

   ApplyDelta(DilutionMC_uu, PDFDilution_uu, S0.at(i) + Su.at(i));
   ApplyDelta(DilutionMC_dd, PDFDilution_dd, S0.at(i) + Sd.at(i));

   ApplyDilution(FZmass_uu, BZmass_uu, PDFDilution_uu);
   ApplyDilution(FZmass_dd, BZmass_dd, PDFDilution_dd);
   ApplyDilution(FZmass_gg, BZmass_gg, PDFDilution_uu, true);
   TH1D* FZmass = (TH1D *)FZmass_uu->Clone("FZmass");
   FZmass->Add(FZmass_dd);
   FZmass->Add(FZmass_gg);
   TH1D* BZmass = (TH1D *)BZmass_uu->Clone("BZmass");
   BZmass->Add(BZmass_dd);
   BZmass->Add(BZmass_gg);

   PDFHist[i] = (TH1D *)FZmass->Clone((TString)"AFB_PDF" + (int)i);
   PDFHist[i]->Reset();
   AFBFunction(FZmass, BZmass, PDFHist[i]);

   writefile->cd();
   PDFHist[i]->Write();
   PDFHists.push_back(PDFHist[i]);
 }
/*
 TH1D *STWHist[40];
 vector<TH1D *> STWHists;
 for(int i = 0; i < 40; i++){
   TFile* file = new TFile(STWTemplates.at(i));

   TH1D* FZmass_uu = (TH1D *)file->Get(FZmass_uu_Name);
   TH1D* FZmass_dd = (TH1D *)file->Get(FZmass_dd_Name);
   TH1D* FZmass_gg = (TH1D *)file->Get(FZmass_gg_Name);
   TH1D* BZmass_uu = (TH1D *)file->Get(BZmass_uu_Name);
   TH1D* BZmass_dd = (TH1D *)file->Get(BZmass_dd_Name);
   TH1D* BZmass_gg = (TH1D *)file->Get(BZmass_gg_Name);

   FZmass_uu->Rebin(2);
   FZmass_dd->Rebin(2);
   FZmass_gg->Rebin(2);
   BZmass_uu->Rebin(2);
   BZmass_dd->Rebin(2);
   BZmass_gg->Rebin(2);

   TH1D* PDFDilution_uu = (TH1D *)DeltaD_uus.at(i)->Clone("Dilution_uu");
   TH1D* PDFDilution_dd = (TH1D *)DeltaD_dds.at(i)->Clone("Dilution_dd");
   ApplyS0(DeltaD_uus.at(0), PDFDilution_uu, PDFS0s.at(0)->GetBinContent(1), PDFS0s.at(0)->GetBinError(1));
   ApplyS0(DeltaD_dds.at(0), PDFDilution_dd, PDFS0s.at(0)->GetBinContent(1), PDFS0s.at(0)->GetBinError(1));

   ApplyDilution(FZmass_uu, BZmass_uu, PDFDilution_uu);
   ApplyDilution(FZmass_dd, BZmass_dd, PDFDilution_dd);
   ApplyDilution(FZmass_gg, BZmass_gg, PDFDilution_uu, true);

   TH1D* FZmass = (TH1D *)FZmass_uu->Clone("FZmass");
   FZmass->Add(FZmass_dd);
   FZmass->Add(FZmass_gg);

   TH1D* BZmass = (TH1D *)BZmass_uu->Clone("BZmass");
   BZmass->Add(BZmass_dd);
   BZmass->Add(BZmass_gg);

   STWHist[i] = new TH1D((TString)"AFB_STW" + (int)i, (TString)"AFB_STW" + (int)i, FZmass->GetNbinsX(), FZmass->GetXaxis()->GetBinLowEdge(1), FZmass->GetXaxis()->GetBinUpEdge(FZmass->GetNbinsX()));

   AFBFunction(FZmass, BZmass, STWHist[i]);

   writefile->cd();
   STWHist[i]->Write();
   STWHists.push_back(STWHist[i]);
 }

 double ppAFBPDFUnc = 0.0;
 CompareDataTheory *run = new CompareDataTheory();
 run->LinkOutFile(writefile);
 run->InputBinRange(FirstBin, LastBin);
 run->GetPDFUncertainty(PDFHists, STWHists, ppAFBPDFUnc);


 TH1D *Chi2_DeltaS0 = new TH1D("Chi2_DeltaS0", "Chi2_DeltaS0", 40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);
 TF1 *FittingDeltaS0;
 for(int i = 0; i < STWHists.size(); i++){
   double Chi2 = CalculateChi2(DataAFB, STWHists.at(i), FirstBin, LastBin);
   Chi2_DeltaS0->SetBinContent(i, Chi2);
 }
 double stwDeltaS0, stwErrorDeltaS0;
 Chi2Fitting(Chi2_DeltaS0, FittingDeltaS0, stwDeltaS0, stwErrorDeltaS0);

 cout<<"DeltaS0: "<<endl;
 cout<<"Central value: "<<stwDeltaS0<<" Stat.unc: "<<stwErrorDeltaS0<<" PDF unc: "<<ppAFBPDFUnc<<endl;
*/
 writefile->cd();
 writefile->Write();

 return 1;

}
