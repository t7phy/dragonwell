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
 if(argc != 5){
   cout<<"usage: JacoAsymCorrelation theory.list PDF nSet ErrorType"<<endl;
   return 0;
 }

 vector<TString> rootNames;
 TString rootName;

 ifstream infile;
  infile.open(argv[1],ios::in);
 while(infile>>rootName){
  rootNames.push_back(rootName);
 }
 infile.close();

 TString DataAsym = "JacobianAsymmetryLowQTZ_Data";

 vector<TH1D *> AsymHist(rootNames.size());

 for(int i = 0; i < rootNames.size(); i++){
   TFile* file = new TFile(rootNames.at(i));
   AsymHist.at(i) = (TH1D *)file->Get(DataAsym);
 }


// TString PDFName = "MSHT20nnlo_as118";
// int nSet = 64;
// TString ErrorType = "Symmetry68";

// TString PDFName = "CT18AsNNLO";
// int nSet = 68;
// TString ErrorType = "Symmetry";

 TString PDFName = argv[2];
 int nSet = stoi(argv[3]);
 TString ErrorType = argv[4];


 PDFReweight* PDFPlot = new PDFReweight();
 PDFPlot->openFile((TString)"Dilution_LowQT_Asym_Z_" + PDFName + (TString)".root");
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

 return 1;

}

