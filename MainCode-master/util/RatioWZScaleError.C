#include <iostream>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 3){
   cout<<"usage: ./RatioWZScaleError W.list Z.list"<<endl;
   return 0;
 }

 vector<TString> WList;
 vector<TString> ZList;

 TString rootName;

 ifstream infile;
  infile.open(argv[1], ios::in);
 while(infile>>rootName){
   WList.push_back(rootName);
 }
 infile.close();

 infile.open(argv[2], ios::in);
 while(infile>>rootName){
   ZList.push_back(rootName);
 }

 if(WList.size() != ZList.size()){
   cout<<"Please use the same PDF sets."<<endl;
   return 0;
 }

 vector<TH1D *> WHists;
 vector<TH1D *> ZHists;
 vector<TH1D *> CorrelatedHists;
 vector<TH1D *> UncorrelatedHists;
 vector<TH1D *> RatioWZHists;
 vector<TH1D *> RatioOfRatio;
 vector<TH1D *> WPts;
 vector<TH1D *> ZPts;


 WHists.resize(WList.size());
 ZHists.resize(ZList.size());
 RatioOfRatio.resize(WList.size());

 CorrelatedHists.resize(WList.size());
 UncorrelatedHists.resize(WList.size() * ZList.size());
 RatioWZHists.resize(WList.size());

 WPts.resize(WList.size());
 ZPts.resize(ZList.size());

 TFile* writefile = new TFile("RatioWZ.root", "RECREATE");
 writefile->cd();

 for(int i = 0; i < WHists.size(); i++){
   TFile *file = new TFile(WList.at(i));
   WPts.at(i) = (TH1D *)file->Get("WPt_CDF_FineBin");
   WPts.at(i) = (TH1D *)WPts.at(i)->Clone((TString)"AbsoluteWPt_CDF_Scale" + (int)i);

   writefile->cd();
   WPts.at(i)->Write();
 }

 for(int i = 0; i < ZHists.size(); i++){
   TFile *file = new TFile(ZList.at(i));
   ZPts.at(i) = (TH1D *)file->Get("ZPt_CDF_FineBin");
   ZPts.at(i) = (TH1D *)ZPts.at(i)->Clone((TString)"AbsoluteZPt_CDF_Scale" + (int)i);

   writefile->cd();
   ZPts.at(i)->Write();
 }

 for(int i = 0; i < WHists.size(); i++){
   TFile *file = new TFile(WList.at(i));
   WHists.at(i) = (TH1D *)file->Get("WPt_CDF_FineBin");
   WHists.at(i)->Scale(1.0 / WHists.at(i)->Integral());

   writefile->cd();
   WHists.at(i)->Write((TString)"WPt_CDF_Scale" + (int)i);
 }

 for(int i = 0; i < ZHists.size(); i++){
   TFile *file = new TFile(ZList.at(i));
   ZHists.at(i) = (TH1D *)file->Get("ZPt_CDF_FineBin");
   ZHists.at(i)->Scale(1.0 / ZHists.at(i)->Integral());

   writefile->cd();
   ZHists.at(i)->Write((TString)"ZPt_CDF_Scale" + (int)i);
 }

 for(int i = 0; i < CorrelatedHists.size(); i++){
   writefile->cd();
   CorrelatedHists.at(i) = (TH1D *)WHists.at(i)->Clone((TString)"Ratio_WZ_CorrelatedScale" + (int)i);
   CorrelatedHists.at(i)->Divide(ZHists.at(i));

   CorrelatedHists.at(i)->Write();
 }

 for(int i = 0; i < RatioOfRatio.size(); i++){
   writefile->cd();
   RatioOfRatio.at(i) = (TH1D *)CorrelatedHists.at(i)->Clone((TString)"RatioOfRatio_Scale" + (int)i);
   RatioOfRatio.at(i)->Divide(CorrelatedHists.at(0));

   RatioOfRatio.at(i)->Write();
 }

 for(int i = 0; i < ZHists.size(); i++){
   for(int j = 0; j < WHists.size(); j++){
     writefile->cd();

     double Index = j + i * ZHists.size();
     UncorrelatedHists.at(Index) = (TH1D *)WHists.at(i)->Clone((TString)"Ratio_WZ_UnCorrelatedScale" + (int)Index);
     UncorrelatedHists.at(Index)->Divide(ZHists.at(j));

     UncorrelatedHists.at(Index)->Write();
   }
 }

 for(int i = 0; i < RatioWZHists.size(); i++){
   writefile->cd();
   RatioWZHists.at(i) = (TH1D *)WHists.at(i)->Clone((TString)"RatioWZ_Scale" + (int)i);
   RatioWZHists.at(i)->Divide(ZHists.at(0));

   RatioWZHists.at(i)->Write();
 }

 TH1D* CorrelatedError;
 TH1D* UncorrelatedError;
 TH1D* RatioOfRatioError;
 TH1D* RatioOfRatioEnvelopePlus;
 TH1D* RatioOfRatioEnvelopeMinus;
 TH1D* WPtError;
 TH1D* ZPtError;


 PDFUncertainty* unc_Correlated = new PDFUncertainty();
 unc_Correlated->Input1DPlot("EnvelopScale", CorrelatedHists, CorrelatedError);

 PDFUncertainty* unc_Uncorrelated = new PDFUncertainty();
 unc_Uncorrelated->Input1DPlot("EnvelopScale", UncorrelatedHists, UncorrelatedError);

 TH1D* RatioWZError;

 PDFUncertainty* unc_RatioWZ = new PDFUncertainty();
 unc_RatioWZ->Input1DPlot("EnvelopScale", RatioWZHists, RatioWZError);

 PDFUncertainty* unc_RatioOfRatio = new PDFUncertainty();
 unc_RatioOfRatio->Input1DPlot("EnvelopScaleShape", RatioOfRatio, RatioOfRatioError, RatioOfRatioEnvelopePlus, RatioOfRatioEnvelopeMinus);

 PDFUncertainty* unc_WPt = new PDFUncertainty();
 unc_WPt->Input1DPlot("EnvelopScale", WPts, WPtError);

 PDFUncertainty* unc_ZPt = new PDFUncertainty();
 unc_ZPt->Input1DPlot("EnvelopScale", ZPts, ZPtError);


 writefile->cd();

 writefile->Write();
 writefile->Close();

 return 1;
}
