#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{

 if(argc != 3){
   cout<<"./WMassSmear Data.list Variable"<<endl;
   return 0;
 }

 TString TemplatesName = "WMassTemplate.list";
 TString DataList = argv[1];
 TString VariableName = argv[2];
 TString rootName;

 vector<TString> Templates;
 vector<TString> DataLists;

 ifstream infile;
  infile.open(TemplatesName,ios::in);
 while(infile>>rootName){
  Templates.push_back(rootName);
 }
 infile.close();

 infile.open(DataList,ios::in);
 while(infile>>rootName){
  DataLists.push_back(rootName);
 }

//////////////////////////////////////////////////////////////////

 vector<TH1D *> DataHists;
 DataHists.resize(DataLists.size());

 for(int i = 0; i < DataLists.size(); i++){
   TFile* DataFile = new TFile(DataLists.at(i));
   DataHists.at(i) = (TH1D *)DataFile->Get(VariableName);
 }

//////////////////////////////////////////////////////////////////
 vector<TH1D *> TemplateHist;
 TemplateHist.resize(Templates.size());

 for(int i = 0; i < Templates.size(); i++){
   TFile* file = new TFile(Templates.at(i));
   TemplateHist.at(i) = (TH1D *)file->Get(VariableName);
 }
//////////////////////////////////////////////////////////////////

 TFile* writefile = new TFile((TString)"save_" + VariableName + (TString)".root", "RECREATE");
 TTree* tree = new TTree("Tree", "Tree");
 tree->SetDirectory(writefile);
 double Value = 0.0;
 tree->Branch("WMass", &Value, "WMass/D");

//////////////////////////////////////////////////////////////////

 int nbin = Templates.size();

 vector<TH1D *> Chi2Hists;
 Chi2Hists.resize(DataLists.size());
 vector<TF1 *> Fittings;
 Fittings.resize(DataLists.size());

 vector<double> Values;
 vector<double> Errors;
 Values.resize(DataLists.size());
 Errors.resize(DataLists.size());

 for(int idata = 0; idata < DataLists.size(); idata++){
   Chi2Hists.at(idata) = new TH1D((TString)"Chi2_" + (int)idata, (TString)"Chi2_" + (int)idata, 100, 0.336 - 0.001 / 2.0, 0.435 + 0.001 / 2.0);

   for(int i = 1; i <= Chi2Hists.at(idata)->GetNbinsX(); i++){
     double Chi2;
     Chi2 = CalculateNormChi2(DataHists.at(idata), TemplateHist.at(i - 1));
     Chi2Hists.at(idata)->SetBinContent(i, Chi2);
     Chi2Hists.at(idata)->SetBinError(i, 0.0);
     if(idata == 0) TemplateHist.at(i - 1)->Write(VariableName + "_Template" + (int)i);
   }

   Chi2Fitting(Chi2Hists.at(idata), Fittings.at(idata), Values.at(idata), Errors.at(idata));
   Value = Values.at(idata) + 80.0;
   tree->Fill();
 }
 double Mean = CalculateMean(Values);
 double RMS = CalculateRMS(Values);

 cout<<"Mean: "<<Mean<<" RMS: "<<RMS<<endl;

 writefile->Write();
 writefile->Close();

 return 1;
}

