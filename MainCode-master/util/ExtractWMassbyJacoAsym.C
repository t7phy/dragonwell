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
//  infile.open("theoryMSHT.list",ios::in);
//  infile.open("theoryCT18As.list",ios::in);

//  infile.open("scale.list",ios::in);
 while(infile>>rootName){
  rootNames.push_back(rootName);
 }
 infile.close();

 TString SlopeName = "JacobianAsymmetryLowQTSlope";
 TString OffsetName = "JacobianAsymmetryLowQTOffset";
 TString DataAsym = "JacobianAsymmetryLowQT_Data";

// TString DataName = "/ustcfs2/yfu/MainCode/run/13TeVWMass/i2Tn3.00/MC_results.root";

 TString DataName = rootNames.at(0);

// TString DataName = "/ustcfs2/yfu/MainCode/run/13TeVWMass/MSHT20.00/MC_results.root";
// TString DataName = "/ustcfs2/yfu/MainCode/run/13TeVWMass/CT18As.00/MC_results.root";

// TString DataName = "Scale1051/MC_results.root";

 TFile *DataFile = new TFile(DataName);
 TH1D* JacoAsymData = (TH1D *)DataFile->Get(DataAsym);

 TFile *writefile = new TFile("saveLowQT.root", "RECREATE");

//////////////////////////////////////////////////////////////////

 vector<TH1D *> SlopeHist(rootNames.size());
 vector<TH1D *> OffsetHist(rootNames.size());
 vector<TH1D *> RatioHist(rootNames.size());
 vector<TH1D *> AsymHist(rootNames.size());

 vector<TH1D *> ResultHist;
 ResultHist.resize(rootNames.size());
 TH1D* ResultPDFError;
//////////////////////////////////////////////////////////////////

 for(int i = 0; i < rootNames.size(); i++){
   TFile* file = new TFile(rootNames.at(i));
   SlopeHist.at(i) = (TH1D *)file->Get(SlopeName);
   OffsetHist.at(i) = (TH1D *)file->Get(OffsetName);
   AsymHist.at(i) = (TH1D *)file->Get(DataAsym);
   RatioHist.at(i) = (TH1D *)OffsetHist.at(i)->Clone((TString)"OffsetOverSlope_PDF" + (int)i);
   RatioHist.at(i)->SetBinContent(1, AsymHist.at(i)->GetBinContent(1));
   RatioHist.at(i)->Divide(SlopeHist.at(i));

   writefile->cd();

   ResultHist.at(i) = new TH1D((TString)"WMassResult_PDF" + (int)i, (TString)"WMassResult_PDF" + (int)i, 1, 0, 1);

   ResultHist.at(i)->SetBinContent(1, (JacoAsymData->GetBinContent(1) - OffsetHist.at(i)->GetBinContent(1)) / SlopeHist.at(i)->GetBinContent(1));
   ResultHist.at(i)->SetBinError(1, 0.0);
 }

 PDFUncertainty* unc = new PDFUncertainty();
 unc->SaveVariBin();
 unc->Input1DPlot("Symmetry", ResultHist, ResultPDFError);

 FileForEPUMP* file_WMass = new FileForEPUMP("WMass");
 file_WMass->InputTheory(ResultHist);
 file_WMass->writetheory();

 TString PDFName = "CT18NNLO";
 int nSet = 58;
 TString ErrorType = "Symmetry";

// TString PDFName = "MSHT20nnlo_as118";
// int nSet = 64;
// TString ErrorType = "Symmetry68";

// TString PDFName = "CT18AsNNLO";
// int nSet = 68;
// TString ErrorType = "Symmetry";


 PDFReweight* PDFPlot = new PDFReweight();
 PDFPlot->openFile((TString)"Dilution_LowQT_WMass_" + PDFName + (TString)".root");
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

/* PDFPlot->DrawPartonCorrelation(ResultHist, 2, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, 1, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, 3, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, 0, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, -2, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, -1, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, 12, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, 38, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(ResultHist, 42, nSet, ErrorType);

 PDFPlot->DrawPartonCorrelation(SlopeHist, 2, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(SlopeHist, 1, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(SlopeHist, 3, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(SlopeHist, 0, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(SlopeHist, -2, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(SlopeHist, -1, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(SlopeHist, 12, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(SlopeHist, 38, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(SlopeHist, 42, nSet, ErrorType);

 PDFPlot->DrawPartonCorrelation(OffsetHist, 2, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(OffsetHist, 1, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(OffsetHist, 3, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(OffsetHist, 0, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(OffsetHist, -2, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(OffsetHist, -1, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(OffsetHist, 12, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(OffsetHist, 38, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(OffsetHist, 42, nSet, ErrorType);

 PDFPlot->DrawPartonCorrelation(RatioHist, 2, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(RatioHist, 1, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(RatioHist, 3, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(RatioHist, 0, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(RatioHist, -2, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(RatioHist, -1, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(RatioHist, 12, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(RatioHist, 38, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(RatioHist, 42, nSet, ErrorType);
*/

 PDFPlot->SaveFile();


/* PDFReweight* PDFPlot = new PDFReweight();
 PDFPlot->openFile((TString)"Dilution_LowQT_Asym_" + PDFName + (TString)".root");
 PDFPlot->InitialPDF(PDFName, 0);
 PDFPlot->DrawPartonCorrelation(AsymHist, 2, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(AsymHist, 1, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(AsymHist, 3, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(AsymHist, 0, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(AsymHist, -2, nSet, ErrorType);
 PDFPlot->DrawPartonCorrelation(AsymHist, -1, nSet, ErrorType);
 for(int i = 12; i <= 39; i++){
   PDFPlot->DrawPartonCorrelation(AsymHist, i, nSet, ErrorType);
 }

 for(int i = 42; i <= 44; i++){
   PDFPlot->DrawPartonCorrelation(AsymHist, i, nSet, ErrorType);
 }

 PDFPlot->SaveFile();
*/

 writefile->Write();
 writefile->Close();

 return 1;

}

