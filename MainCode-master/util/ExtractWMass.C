#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "PDFHelper/PDFReweight.h"
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{
 vector<TString> rootNames;
 TString rootName;

 ifstream infile;
  infile.open("theory.list",ios::in);
 while(infile>>rootName){
  rootNames.push_back(rootName);
 }
 infile.close();

 vector<TString> WMassTemplates;
  infile.open("WMassTemplate.list",ios::in);
 while(infile>>rootName){
  WMassTemplates.push_back(rootName);
 }

 TString VariableName = argv[1];

 TString PDFName = "CT18NNLO";
 int nSet = 58;
 TString ErrorType = "Symmetry";

// TString PDFName = "CT18AsNNLO";
// int nSet = 68;
// TString ErrorType = "Symmetry";

 TFile *writefile = new TFile("save_" + VariableName + ".root", "RECREATE");

//////////////////////////////////////////////////////////////////
 vector<TH1D *> TemplateHist;
 TemplateHist.resize(WMassTemplates.size());

 for(int i = 0; i < WMassTemplates.size(); i++){
   TFile* file = new TFile(WMassTemplates.at(i));
   TemplateHist.at(i) = (TH1D *)file->Get(VariableName);
 }

//////////////////////////////////////////////////////////////////

 vector<TH1D *> Chi2Hist;
 Chi2Hist.resize(rootNames.size());

 vector<TH1D *> ResultHist;
 ResultHist.resize(rootNames.size());
 TH1D* ResultPDFError;
//////////////////////////////////////////////////////////////////

 vector<TH1D *> PDFHist;
 PDFHist.resize(rootNames.size());

 vector<TH1D  *> NormalizedPDFHist;
 NormalizedPDFHist.resize(rootNames.size());

 for(int i = 0; i < rootNames.size(); i++){
   TFile* file = new TFile(rootNames.at(i));
   PDFHist.at(i) = (TH1D *)file->Get(VariableName);

   NormalizedPDFHist.at(i) = (TH1D *)PDFHist.at(i)->Clone("Normalized_" + VariableName);
   NormalizedPDFHist.at(i)->Scale(1.0 / PDFHist.at(i)->Integral());

   writefile->cd();
   Chi2Hist.at(i) = new TH1D((TString)"Chi2_PDF" + (int)i, (TString)"Chi2_PDF" + (int)i, 100, 0.336 - 0.001 / 2.0, 0.435 + 0.001 / 2.0);

   ResultHist.at(i) = new TH1D((TString)"WMassResult_PDF" + (int)i, (TString)"WMassResult_PDF" + (int)i, 1, 0, 1);

   for(int imass = 1; imass <= Chi2Hist.at(i)->GetNbinsX(); imass++){
     double Chi2 = CalculateNormChi2(PDFHist.at(i), TemplateHist.at(imass - 1));
     Chi2Hist.at(i)->SetBinContent(imass, Chi2);
     //Chi2Hist.at(i)->SetBinError(imass, 0.0);
   }

   TF1* fitting;
   double WMassValue;
   double WMassError;

   cout<<i<<":  ";
   Chi2Fitting(Chi2Hist.at(i), fitting, WMassValue, WMassError);
   ResultHist.at(i)->SetBinContent(1, WMassValue + 80.0);
   ResultHist.at(i)->SetBinError(1, WMassError);
 }

 PDFUncertainty* unc = new PDFUncertainty();
 unc->SaveVariBin();
 unc->Input1DPlot(ErrorType, ResultHist, ResultPDFError);

 FileForEPUMP* file_PDFHist = new FileForEPUMP(VariableName);
 file_PDFHist->InputTheory(PDFHist);
 file_PDFHist->writetheory();

 FileForEPUMP* file_NormalizedPDFHist = new FileForEPUMP("Normalized_" + VariableName);
 file_NormalizedPDFHist->InputTheory(NormalizedPDFHist);
 file_NormalizedPDFHist->writetheory();

 FileForEPUMP* file_WMass = new FileForEPUMP("WMass_" + VariableName);
 file_WMass->InputTheory(ResultHist);
 file_WMass->writetheory();

/* PDFReweight* PDFPlot = new PDFReweight();
 PDFPlot->openFile((TString)"Dilution_" + VariableName + (TString)".root");
 PDFPlot->InitialPDF(PDFName, 0);
 PDFPlot->DrawPartonCorrelation(ResultHist, 2, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, 1, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, 3, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, 0, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, -2, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, -1, nSet, ErrorType);
 for(int i = 12; i <= 39; i++){
   PDFPlot->DrawPartonCorrelation(ResultHist, i, nSet, ErrorType);
 }

 for(int i = 42; i <= 44; i++){
   PDFPlot->DrawPartonCorrelation(ResultHist, i, nSet, ErrorType);
 }
 PDFPlot->SaveFile();
*/
 writefile->Write();
 writefile->Close();

 return 1;

}

