#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Tools/Tools.h"

void TemplateFitting(TString TemplatesName, TString DataName, TString VariableName, double left, double right, double step)
{
 TString rootName;
 vector<TString> Templates;

 ifstream infile;
  infile.open(TemplatesName,ios::in);
 while(infile>>rootName){
  Templates.push_back(rootName);
 }

 TFile* DataFile = new TFile(DataName);
 TH1D* DataHist = (TH1D *)DataFile->Get(VariableName + (TString)"_Pseudodata");

 TFile *writefile = new TFile((TString)"save_" + VariableName + (TString)".root", "RECREATE");

//////////////////////////////////////////////////////////////////
 vector<TH1D *> TemplateHist;
 TemplateHist.resize(Templates.size());

 for(int i = 0; i < Templates.size(); i++){
   TFile* file = new TFile(Templates.at(i));
   TemplateHist.at(i) = (TH1D *)file->Get(VariableName);
 }
//////////////////////////////////////////////////////////////////

 int nbin = Templates.size();

 TH1D* Chi2Hist;

 writefile->cd();
 DataHist->Write(VariableName + "_Data");

 Chi2Hist = new TH1D("Chi2", "Chi2", nbin, left - step / 2.0, right + step / 2.0);

 for(int i = 1; i <= Chi2Hist->GetNbinsX(); i++){
   double Chi2 = CalculateChi2(DataHist, TemplateHist.at(i - 1));
   Chi2Hist->SetBinContent(i, Chi2);
   Chi2Hist->SetBinError(i, 0.0);
   TemplateHist.at(i - 1)->Write(VariableName + "_Template" + (int)i);
 }

 TF1* fitting;
 double Value;
 double Error;
 Chi2Fitting(Chi2Hist, fitting, Value, Error);

 writefile->Write();
 writefile->Close();

}

void TemplateFittingNorm(TString TemplatesName, TString DataName, TString VariableName, double left, double right, double step, int FirstBin, int LastBin)
{
 TString rootName;
 vector<TString> Templates;

 ifstream infile;
  infile.open(TemplatesName,ios::in);
 while(infile>>rootName){
  Templates.push_back(rootName);
 }

 TFile* DataFile = new TFile(DataName);
// TH1D* DataHist = (TH1D *)DataFile->Get(VariableName + (TString)"_Pseudodata");
// TH1D* DataHist = (TH1D *)DataFile->Get(VariableName + (TString)"_LargeStat");
 TH1D* DataHist = (TH1D *)DataFile->Get(VariableName);

 TFile *writefile = new TFile((TString)"save_" + VariableName + (TString)".root", "RECREATE");

//////////////////////////////////////////////////////////////////
 vector<TH1D *> TemplateHist;
 TemplateHist.resize(Templates.size());

 for(int i = 0; i < Templates.size(); i++){
   TFile* file = new TFile(Templates.at(i));
   TemplateHist.at(i) = (TH1D *)file->Get(VariableName);
 }
//////////////////////////////////////////////////////////////////

 int nbin = Templates.size();

 TH1D* Chi2Hist;

 writefile->cd();
 DataHist->Write(VariableName + "_Data");

 Chi2Hist = new TH1D("Chi2", "Chi2", nbin, left - step / 2.0, right + step / 2.0);

 for(int i = 1; i <= Chi2Hist->GetNbinsX(); i++){
   double Chi2;
   if(FirstBin < 0 || LastBin < 0) Chi2 = CalculateNormChi2(DataHist, TemplateHist.at(i - 1));
   if(FirstBin > 0 && LastBin > 0) Chi2 = CalculateNormChi2(DataHist, TemplateHist.at(i - 1), FirstBin, LastBin);
   Chi2Hist->SetBinContent(i, Chi2);
   Chi2Hist->SetBinError(i, 0.0);
   TemplateHist.at(i - 1)->Write(VariableName + "_Template" + (int)i);
 }

 TF1* fitting;
 double Value;
 double Error;
 Chi2Fitting(Chi2Hist, fitting, Value, Error);

 writefile->Write();
 writefile->Close();

}

void TemplateFittingNorm(TString TemplatesName, TString DataName, TString VariableName, TString DataVariableName, double left, double right, double step, int FirstBin, int LastBin)
{
 TString rootName;
 vector<TString> Templates;

 ifstream infile;
  infile.open(TemplatesName,ios::in);
 while(infile>>rootName){
  Templates.push_back(rootName);
 }

 TFile* DataFile = new TFile(DataName);
// TH1D* DataHist = (TH1D *)DataFile->Get(VariableName + (TString)"_Pseudodata");
// TH1D* DataHist = (TH1D *)DataFile->Get(VariableName + (TString)"_LargeStat");
 TH1D* DataHist = (TH1D *)DataFile->Get(DataVariableName);

 TFile *writefile = new TFile((TString)"save_" + VariableName + (TString)".root", "RECREATE");

//////////////////////////////////////////////////////////////////
 vector<TH1D *> TemplateHist;
 TemplateHist.resize(Templates.size());

 for(int i = 0; i < Templates.size(); i++){
   TFile* file = new TFile(Templates.at(i));
   TemplateHist.at(i) = (TH1D *)file->Get(VariableName);
 }
//////////////////////////////////////////////////////////////////

 int nbin = Templates.size();

 TH1D* Chi2Hist;

 writefile->cd();
 DataHist->Write(DataVariableName + "_Data");

 Chi2Hist = new TH1D("Chi2", "Chi2", nbin, left - step / 2.0, right + step / 2.0);

 for(int i = 1; i <= Chi2Hist->GetNbinsX(); i++){
   double Chi2;
   if(FirstBin < 0 || LastBin < 0) Chi2 = CalculateNormChi2(DataHist, TemplateHist.at(i - 1));
   if(FirstBin > 0 && LastBin > 0) Chi2 = CalculateNormChi2(DataHist, TemplateHist.at(i - 1), FirstBin, LastBin);
   Chi2Hist->SetBinContent(i, Chi2);
   Chi2Hist->SetBinError(i, 0.0);
   TemplateHist.at(i - 1)->Write(VariableName + "_Template" + (int)i);
 }

 TF1* fitting;
 double Value;
 double Error;
 Chi2Fitting(Chi2Hist, fitting, Value, Error, 30);

 writefile->Write();
 writefile->Close();

}

