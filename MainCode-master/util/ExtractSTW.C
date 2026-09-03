#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"

using namespace std;

int main(int argc, char** argv)
{
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

 TString VariableName = "AFBSlope_CF";
 TString AFBSlopeName_CC = "AFBSlope_CC";
 TString AFBSlopeName_CF = "AFBSlope_CF";
 TString AFBSlopeName_Full = "AFBSlope_Full";
 TString AFBOffsetName_CC = "AFBOffset_CC";
 TString AFBOffsetName_CF = "AFBOffset_CF";
 TString AFBOffsetName_Full = "AFBOffset_Full";

/* TH1D *PDFSet[57];
 TH1D *PDFHist[57];
 TH1D *PDFError;
 vector<TH1D *> PDFHists;
*/
/* for(int i = 0; i < 57; i++){
   TFile* file = new TFile(rootNames.at(i));
   PDFHist[i] = (TH1D *)file->Get(VariableName);
   PDFSet[i] = new TH1D((TString)"ExtractResult_" + (int)i, (TString)"ExtractResult_" + (int)i, 1, 0, 1);
 }


 TH1D *STWHist[40];
 for(int i = 0; i < 40; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   STWHist[i] = (TH1D *)file->Get(VariableName);
   delete file;
 }
*/

 TFile* writefile = new TFile(VariableName + "_PDFResults.root", "RECREATE");
 TH1D *AFBSlope_CC_PDF = new TH1D("AFBSlope_CC_PDF", "AFBSlope_CC_PDF", 57, 0, 57);
 TH1D *AFBSlope_CF_PDF = new TH1D("AFBSlope_CF_PDF", "AFBSlope_CF_PDF", 57, 0, 57);
 TH1D *AFBSlope_Full_PDF = new TH1D("AFBSlope_Full_PDF", "AFBSlope_Full_PDF", 57, 0, 57);
 TH1D *AFBSlope_CC_STW = new TH1D("AFBSlope_CC_STW", "AFBSlope_CC_STW", 40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);
 TH1D *AFBSlope_CF_STW = new TH1D("AFBSlope_CF_STW", "AFBSlope_CF_STW", 40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);
 TH1D *AFBSlope_Full_STW = new TH1D("AFBSlope_Full_STW", "AFBSlope_Full_STW", 40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);
 TH1D *AFBSlope_CC_PDFError = new TH1D("AFBSlope_CC_PDFError_STW", "AFBSlope_CC_PDFError_STW", 40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);
 TH1D *AFBSlope_CF_PDFError = new TH1D("AFBSlope_CF_PDFError_STW", "AFBSlope_CF_PDFError_STW", 40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);
 TH1D *AFBSlope_Full_PDFError = new TH1D("AFBSlope_Full_PDFError_STW", "AFBSlope_Full_PDFError_STW", 40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);


 vector<TH1D *> AFBSlope_CCs;
 vector<TH1D *> AFBSlope_CFs;
 vector<TH1D *> AFBSlope_Fulls;
 TH1D *hist_CC[57];
 TH1D *hist_CF[57];
 TH1D *hist_Full[57];

 for(int i = 0; i < 57; i++){
   TFile* file = new TFile(rootNames.at(i));
   hist_CC[i] = (TH1D *)file->Get(AFBSlopeName_CC);
   AFBSlope_CC_PDF->SetBinContent(i + 1, hist_CC[i]->GetBinContent(1));
   AFBSlope_CC_PDF->SetBinError(i + 1, hist_CC[i]->GetBinError(1));
   AFBSlope_CCs.push_back(hist_CC[i]);

   hist_CF[i] = (TH1D *)file->Get(AFBSlopeName_CF);
   AFBSlope_CF_PDF->SetBinContent(i + 1, hist_CF[i]->GetBinContent(1));
   AFBSlope_CF_PDF->SetBinError(i + 1, hist_CF[i]->GetBinError(1));
   AFBSlope_CFs.push_back(hist_CF[i]);

   hist_Full[i] = (TH1D *)file->Get(AFBSlopeName_Full);
   AFBSlope_Full_PDF->SetBinContent(i + 1, hist_Full[i]->GetBinContent(1));
   AFBSlope_Full_PDF->SetBinError(i + 1, hist_Full[i]->GetBinError(1));
   AFBSlope_Fulls.push_back(hist_Full[i]);

 }

 for(int i = 0; i < 40; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   TH1D *hist_CC = (TH1D *)file->Get(AFBSlopeName_CC);
   AFBSlope_CC_STW->SetBinContent(i + 1, hist_CC->GetBinContent(1));
   AFBSlope_CC_STW->SetBinError(i + 1, hist_CC->GetBinError(1));
   TH1D *hist_CF = (TH1D *)file->Get(AFBSlopeName_CF);
   AFBSlope_CF_STW->SetBinContent(i + 1, hist_CF->GetBinContent(1));
   AFBSlope_CF_STW->SetBinError(i + 1, hist_CF->GetBinError(1));
   TH1D *hist_Full = (TH1D *)file->Get(AFBSlopeName_Full);
   AFBSlope_Full_STW->SetBinContent(i + 1, hist_Full->GetBinContent(1));
   AFBSlope_Full_STW->SetBinError(i + 1, hist_Full->GetBinError(1));
 }

 writefile->cd();

// AFBSlope_CC_PDF->Write();
// AFBSlope_CF_PDF->Write();
// AFBSlope_Full_PDF->Write();
// AFBSlope_CC_STW->Write();
// AFBSlope_CF_STW->Write();
// AFBSlope_Full_STW->Write();

/* for(int iPDF = 0; iPDF < 57; iPDF++){
   TH1D *Chi2Hist = new TH1D((TString)"Chi2_" + (int)iPDF, (TString)"Chi2_" + (int)iPDF, 40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);
   TF1 *Fitting;
   for(int i = 0; i < 40; i++){
     double Chi2 = CalculateChi2(PDFHist[iPDF], STWHist[i]);
     Chi2Hist->SetBinContent(i, Chi2);
   }
   double stw, stwError;
   Chi2Fitting(Chi2Hist, Fitting, stw, stwError);
   PDFSet[iPDF]->SetBinContent(1, stw);
   PDFSet[iPDF]->SetBinError(1, stwError);
   PDFHists.push_back(PDFSet[iPDF]);

   writefile->cd();
   Chi2Hist->Write();
   delete Chi2Hist;
   delete Fitting;
 }

 for(int iPDF = 0; iPDF < 57; iPDF++){
   cout<<"PDF "<<iPDF<<": "<<PDFHists.at(iPDF)->GetBinContent(1)<<endl;
 }
*/

 TH1D *AFBSlope_CC_Error;
 TH1D *AFBSlope_CF_Error;
 TH1D *AFBSlope_Full_Error;

 PDFUncertainty *AFBSlope_CC_unc = new PDFUncertainty();
 AFBSlope_CC_unc->Input1DPlot("Symmetry", AFBSlope_CCs, AFBSlope_CC_Error);

 PDFUncertainty *AFBSlope_CF_unc = new PDFUncertainty();
 AFBSlope_CF_unc->Input1DPlot("Symmetry", AFBSlope_CFs, AFBSlope_CF_Error);

 PDFUncertainty *AFBSlope_Full_unc = new PDFUncertainty();
 AFBSlope_Full_unc->Input1DPlot("Symmetry", AFBSlope_Fulls, AFBSlope_Full_Error);

 for(int i = 0; i < 40; i++){
   AFBSlope_CC_PDFError->SetBinContent(i + 1, AFBSlope_CCs.at(0)->GetBinContent(1));
   AFBSlope_CC_PDFError->SetBinError(i + 1, AFBSlope_CC_Error->GetBinContent(1));
   AFBSlope_CF_PDFError->SetBinContent(i + 1, AFBSlope_CFs.at(0)->GetBinContent(1));
   AFBSlope_CF_PDFError->SetBinError(i + 1, AFBSlope_CF_Error->GetBinContent(1));
   AFBSlope_Full_PDFError->SetBinContent(i + 1, AFBSlope_Fulls.at(0)->GetBinContent(1));
   AFBSlope_Full_PDFError->SetBinError(i + 1, AFBSlope_Full_Error->GetBinContent(1));
 }

// cout<<"Central :"<<PDFHists.at(0)->GetBinContent(1)<<endl;
// cout<<"Sta Error:"<<PDFHists.at(0)->GetBinError(1)<<endl;
// cout<<"PDF Error: "<<PDFError->GetBinContent(1)<<endl;

 writefile->cd();
 writefile->Write();

 writefile->Close();

 return 1;
}
