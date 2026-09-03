#include <iostream>
#include "RootCommon.h"
#include "PDFHelper/PDFReweight.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 4){
   cout<<"usage: ./DrawWZCorrelation W.list Z.list ErrorType"<<endl;
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

 WHists.resize(WList.size());
 ZHists.resize(ZList.size());

 TFile* writefile = new TFile("WZCorrelation.root", "RECREATE");
 writefile->cd();

 for(int i = 0; i < WHists.size(); i++){
   TFile *file = new TFile(WList.at(i));
   WHists.at(i) = (TH1D *)file->Get("FiducialCrossSection_W");

   writefile->cd();
   WHists.at(i)->Write((TString)"FiducialCrossSection_W_PDF" + (int)i);
 }

 for(int i = 0; i < ZHists.size(); i++){
   TFile *file = new TFile(ZList.at(i));
   ZHists.at(i) = (TH1D *)file->Get("FiducialCrossSection_Z");

   writefile->cd();
   ZHists.at(i)->Write((TString)"FiducialCrossSection_Z_PDF" + (int)i);
 }

 TGraph* ellipse;
 TGraph* central;

 PDFReweight* data = new PDFReweight();
 data->DrawPartonCorrelation(ZHists, WHists, ellipse, central, argv[3]);

 ellipse->Write(ellipse->GetName());
 central->Write(central->GetName());

 writefile->Write();
 writefile->Close();

 return 1;
}
