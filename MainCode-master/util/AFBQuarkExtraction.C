#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "CompareDataTheory/CompareDataTheory.h"
#include "Tools/Tools.h"
#include "FileForEPUMP/FileForEPUMP.h"

using namespace std;

int main(int argc, char** argv)
{
 double massrange[31] = {60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120};
 double massrange2[2] = {80, 100};

 vector<TString> rootNames;
 TString rootName;

 ifstream infile;
  infile.open("theoryCC.list",ios::in);
//  infile.open("theoryCT18.list",ios::in);
//  infile.open("theoryMSHT.list",ios::in);
//  infile.open("theoryScale.list",ios::in);
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
// TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/MSHT20.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/Pseudodata_0.2315/MC_results_DilutionDiff.root";
// TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/Pseudodata_0.2315/MC_results_AFBRotation2.root";
// TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/Pseudodata_0.2315/If1363.01/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/i2Tn3.00/MC_results.root";

 TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/i2Tn3.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/Scale960/MC_results.root";

 TString EtaRegion = "CF";

 TString VariableName = "AFB_" + EtaRegion;

 TFile* writefile = new TFile(VariableName + "_PDFResults.root", "RECREATE");
 writefile->cd();

 TString SlopeName = "AFBSlope_" + EtaRegion;
 TString QuarkSlopeName = "AFBQuarkSlope_" + EtaRegion;
 TString S0FractionName = "AFBS0Fraction_" + EtaRegion;
 TString AveAFBName = "AveAFB_" + EtaRegion;
 TString Dilution_uu_Name = "Dilution_ZMass_" + EtaRegion + "_uu";
 TString Dilution_dd_Name = "Dilution_ZMass_" + EtaRegion + "_dd";

 if(EtaRegion == "Full") EtaRegion = "";
 if(EtaRegion == "CC") EtaRegion = "_CC";
 if(EtaRegion == "CF") EtaRegion = "_CF";

 TString FZmass_uu_Name = "FZmass" + EtaRegion + "_uu";
 TString FZmass_dd_Name = "FZmass" + EtaRegion + "_dd";
 TString FZmass_gg_Name = "FZmass" + EtaRegion + "_gg";
 TString BZmass_uu_Name = "BZmass" + EtaRegion + "_uu";
 TString BZmass_dd_Name = "BZmass" + EtaRegion + "_dd";
 TString BZmass_gg_Name = "BZmass" + EtaRegion + "_gg";

 TFile *DataFile = new TFile(DataName);
 TH1D *DataAFB = (TH1D *)DataFile->Get(VariableName);
 TH1D *DataSlope = (TH1D *)DataFile->Get(SlopeName);
 TH1D *DataAveAFB = (TH1D *)DataFile->Get(AveAFBName);
// TH1D *DataAFB_60_120 = (TH1D *)DataAFB->Rebin(30, VariableName, massrange);
 cout<<"Data: "<<DataAveAFB->GetBinContent(1)<<" +- "<<DataAveAFB->GetBinError(1)<<endl;

 writefile->cd();
 DataAFB->Write();
// DataAFB_60_120->Write();

 int FirstBin = 11;
 int LastBin = 20;

 TH1D *PDFS0[59];
 TH1D *Dilution_uu[59];
 TH1D *Dilution_dd[59];
 TH1D *DeltaD_uu[59];
 TH1D *DeltaD_dd[59];
 TH1D *PDFHadronAFB[59];
 vector<TH1D *> PDFS0s;
 vector<TH1D *> Dilution_uus;
 vector<TH1D *> Dilution_dds;
 vector<TH1D *> DeltaD_uus;
 vector<TH1D *> DeltaD_dds;
 vector<TH1D *> PDFHadronAFBs;
 for(int i = 0; i < 59; i++){
   TFile* file = new TFile(rootNames.at(i));

   writefile->cd();
   TH1D* QuarkSlope = (TH1D *)file->Get(QuarkSlopeName);
   TH1D* Slope = (TH1D *)file->Get(SlopeName);
   TH1D* S0Fraction = (TH1D *)file->Get(S0FractionName);

   TH1D* AveAFB = (TH1D *)file->Get(AveAFBName);
   cout<<"MC: "<<AveAFB->GetBinContent(1)<<" +- "<<AveAFB->GetBinError(1)<<endl;

   PDFHadronAFB[i] = (TH1D *)file->Get(VariableName);
   PDFHadronAFBs.push_back(PDFHadronAFB[i]);

   double S0FractionValue = S0Fraction->GetBinContent(1);
   //S0FractionValue = 1.0;

   PDFS0[i] = (TH1D *)DataSlope->Clone((TString)"S0_PDF" + (int)i);
   PDFS0[i]->SetBinContent(1, (1 - DataSlope->GetBinContent(1) / QuarkSlope->GetBinContent(1)) / 2.0 / S0FractionValue);
   PDFS0[i]->SetBinError(1, (DataSlope->GetBinError(1) / QuarkSlope->GetBinContent(1)) / 2.0 / S0FractionValue);

   cout<<"Data S0: "<<PDFS0[i]->GetBinContent(1)<<endl;

   Dilution_uu[i] = (TH1D *)file->Get(Dilution_uu_Name);
   Dilution_dd[i] = (TH1D *)file->Get(Dilution_dd_Name);
   DeltaD_uu[i] = (TH1D *)Dilution_uu[i]->Clone((TString)"DeltaD_uu_PDF" + (int)i);
   DeltaD_dd[i] = (TH1D *)Dilution_dd[i]->Clone((TString)"DeltaD_dd_PDF" + (int)i);

   for(int ibinx = 1; ibinx <= Dilution_uu[i]->GetNbinsX(); ibinx++){

     double S0 = (1 - Slope->GetBinContent(1) / QuarkSlope->GetBinContent(1)) / 2.0 / S0FractionValue;
     double S0Error = (Slope->GetBinError(1) / QuarkSlope->GetBinContent(1)) / 2.0 / S0FractionValue;

     DeltaD_uu[i]->SetBinContent(ibinx, Dilution_uu[i]->GetBinContent(ibinx) - S0);
     DeltaD_uu[i]->SetBinError(ibinx, sqrt(Dilution_uu[i]->GetBinError(ibinx) * Dilution_uu[i]->GetBinError(ibinx) + S0Error * S0Error));
     DeltaD_dd[i]->SetBinContent(ibinx, Dilution_dd[i]->GetBinContent(ibinx) - S0);
     DeltaD_dd[i]->SetBinError(ibinx, sqrt(Dilution_dd[i]->GetBinError(ibinx) * Dilution_dd[i]->GetBinError(ibinx) + S0Error * S0Error));

     if(ibinx == 1) cout<<"MC S0: "<<S0<<endl;
     if(ibinx == 1) cout<<"Delta S0: "<<S0 - PDFS0[i]->GetBinContent(1)<<endl;
   }

   PDFS0s.push_back(PDFS0[i]);
   DeltaD_uus.push_back(DeltaD_uu[i]);
   DeltaD_dds.push_back(DeltaD_dd[i]);
 }


 TH1D *PDFHist[59];
 vector<TH1D *> PDFHists;

 TH1D *AveAFBHist[59];
 vector<TH1D *> AveAFBHists;

 for(int i = 0; i < 59; i++){
   TFile* file = new TFile(rootNames.at(i));

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
   ApplyS0(DeltaD_uus.at(i), PDFDilution_uu, PDFS0s.at(i)->GetBinContent(1), PDFS0s.at(i)->GetBinError(1));
   ApplyS0(DeltaD_dds.at(i), PDFDilution_dd, PDFS0s.at(i)->GetBinContent(1), PDFS0s.at(i)->GetBinError(1));

   ApplyDilution(FZmass_uu, BZmass_uu, PDFDilution_uu);
   ApplyDilution(FZmass_dd, BZmass_dd, PDFDilution_dd);
   ApplyDilution(FZmass_gg, BZmass_gg, PDFDilution_uu, true);
   TH1D* FZmass = (TH1D *)FZmass_uu->Clone("FZmass");
   FZmass->Add(FZmass_dd);
   FZmass->Add(FZmass_gg);
   TH1D* BZmass = (TH1D *)BZmass_uu->Clone("BZmass");
   BZmass->Add(BZmass_dd);
   BZmass->Add(BZmass_gg);

   TH1D* FZmass_80_100 = (TH1D *)FZmass->Rebin(1, "FZmass_80_100", massrange2);
   TH1D* BZmass_80_100 = (TH1D *)BZmass->Rebin(1, "BZmass_80_100", massrange2);
   AveAFBHist[i] = (TH1D *)FZmass_80_100->Clone((TString)"AveAFB_ApplyDilution_PDF" + (int)i);
   AFBFunction(FZmass_80_100, BZmass_80_100, AveAFBHist[i]);
   cout<<"Apply dilution: "<<AveAFBHist[i]->GetBinContent(1)<<" +- "<<AveAFBHist[i]->GetBinError(1)<<endl;
   AveAFBHists.push_back(AveAFBHist[i]);

   PDFHist[i] = (TH1D *)FZmass->Clone((TString)"AFB_PDF" + (int)i);
   PDFHist[i]->Reset();
   AFBFunction(FZmass, BZmass, PDFHist[i]);

   writefile->cd();
   TH1D *MCAFB = (TH1D *)file->Get(VariableName);
   MCAFB->Write(VariableName + "_MCPDF" + (int)i);

   PDFHist[i]->Write();
   PDFHists.push_back(PDFHist[i]);
 }

 TH1D *STWHist[40];
 TH1D *STWHadronAFB[40];
 vector<TH1D *> STWHists;
 vector<TH1D *> STWHadronAFBs;
 for(int i = 0; i < 40; i++){
   TFile* file = new TFile(STWTemplates.at(i));

   STWHadronAFB[i] = (TH1D *)file->Get(VariableName);
   STWHadronAFBs.push_back(STWHadronAFB[i]);

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

   TH1D* PDFDilution_uu = (TH1D *)DeltaD_uus.at(0)->Clone("Dilution_uu");
   TH1D* PDFDilution_dd = (TH1D *)DeltaD_dds.at(0)->Clone("Dilution_dd");
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

 double HadronAFBPDFUnc = 0.0;
 CompareDataTheory *HadronRun = new CompareDataTheory();
 HadronRun->GetPDFUncertainty(PDFHadronAFBs, STWHadronAFBs, HadronAFBPDFUnc);

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

 TH1D* AFBunc_Error;
 PDFUncertainty *AFBunc;
 AFBunc = new PDFUncertainty();
 AFBunc->Input1DPlot("Symmetry", PDFHists, AFBunc_Error);

 FileForEPUMP *theoryfile = new FileForEPUMP("ApplyDilutionAFB");
 theoryfile->InputTheory(AFBunc);
 theoryfile->writetheory();

 TH1D* AveAFB_Error;
 PDFUncertainty *AveAFBunc;
 AveAFBunc = new PDFUncertainty();
 AveAFBunc->Input1DPlot("Symmetry", AveAFBHists, AveAFB_Error);
 cout<<"Average AFB: "<<AveAFBHists.at(0)->GetBinContent(1)<<endl;
 cout<<"Average AFB PDF unc: "<<AveAFB_Error->GetBinContent(1)<<endl;

 writefile->cd();
 writefile->Write();

 return 1;

}
