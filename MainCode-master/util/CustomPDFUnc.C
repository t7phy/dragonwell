#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"

using namespace std;

int main(int argc, char* argv[])
{
 if(argc != 4){
   cout<<"Usage ./CustomPDFUnc variable.list theory.list ErrorType"<<endl;
 }

 vector<TString> HistNames;
 vector<TString> rootNames;

 ifstream infile;
  infile.open(argv[1]);
 TString HistName;
 while(infile >> HistName){
   HistNames.push_back(HistName);
 }

 ifstream theorylist;
  theorylist.open(argv[2]);
 while(theorylist >> HistName){
   rootNames.push_back(HistName);
 }

 vector<vector<TH1D *>> v_HistVector;
 vector<TH1D *> v_HistError;
 vector<PDFUncertainty *> v_PDFUnc;

 v_HistVector.resize(HistNames.size());
 v_HistError.resize(HistNames.size());
 v_PDFUnc.resize(HistNames.size());

 TFile* writefile = new TFile("PDFUnc_" + (TString)argv[3] + ".root", "RECREATE");
 TFile* theoryfile[rootNames.size()];

 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   theoryfile[ifile] = new TFile(rootNames.at(ifile));
 }

 for(int ihist = 0; ihist < HistNames.size(); ihist++){
   writefile->cd();

   v_PDFUnc.at(ihist) = new PDFUncertainty();
   for(int ifile = 0; ifile < rootNames.size(); ifile++){
     v_HistVector.at(ihist).push_back((TH1D *)theoryfile[ifile]->Get(HistNames.at(ihist)));
     v_HistVector.at(ihist).at(ifile)->Write(HistNames.at(ihist) + (TString)"_PDF" + (int)ifile);
   }
   v_PDFUnc.at(ihist)->SaveVariBin();
   v_PDFUnc.at(ihist)->Input1DPlot((TString)argv[3], v_HistVector.at(ihist), v_HistError.at(ihist));
 }

 writefile->Write();
 writefile->Close();

 return 1;
}

