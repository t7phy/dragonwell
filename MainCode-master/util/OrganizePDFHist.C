#include <iostream>
#include <fstream>
#include "RootCommon.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 4){
   cout<<"usage: ./OrganizePDFHist data.list variable.list PDFName"<<endl;
   return 0;
 }

 TString PDFName = argv[3];

 TString name;
 TString type;

 vector<TString> VariableNames;
 vector<TString> VariableTypes;
 vector<TString> FileNames;

 ifstream datalist;
  datalist.open(argv[1]);
 while(datalist >> name){
   FileNames.push_back(name);
 }
 datalist.close();

 ifstream varlist;
  varlist.open(argv[2]);
 while(varlist >> name){
   varlist >> type;
   VariableNames.push_back(name);
   VariableTypes.push_back(type);
 }
 varlist.close();

 vector<TFile *> RootFiles;
 RootFiles.resize(FileNames.size());
 for(int i = 0; i < FileNames.size(); i++){
   RootFiles.at(i) = new TFile(FileNames.at(i));
 }

 TFile* writefile = new TFile((TString)"Pseudodata_" + PDFName + (TString)".root", "RECREATE");
 for(int ivar = 0; ivar < VariableNames.size(); ivar++){
   for(int ifile = 0; ifile < FileNames.size(); ifile++){
     writefile->cd();
     if(VariableTypes.at(ivar) == "TH1D"){
       TH1D* hist = (TH1D *)RootFiles.at(ifile)->Get(VariableNames.at(ivar));
       hist->Write(VariableNames.at(ivar) + (TString)"_" + PDFName + (TString)"_" + ifile);
     }

     if(VariableTypes.at(ivar) == "TH2D"){
       TH2D* hist = (TH2D *)RootFiles.at(ifile)->Get(VariableNames.at(ivar));
       hist->Write(VariableNames.at(ivar) + (TString)"_" + PDFName + (TString)"_" + ifile);
     }

     if(VariableTypes.at(ivar) == "TH3D"){
       TH3D* hist = (TH3D *)RootFiles.at(ifile)->Get(VariableNames.at(ivar));
       hist->Write(VariableNames.at(ivar) + (TString)"_" + PDFName + (TString)"_" + ifile);
     }
   }
 }

 writefile->cd();
 writefile->Close();

 return 1;
}
