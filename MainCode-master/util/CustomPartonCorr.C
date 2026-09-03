#include "RootCommon.h"
#include "PDFHelper/PDFReweight.h"

using namespace std;

int main(int argc, char* argv[])
{
 if(argc != 4){
   cout<<"Usage ./CustomPartonCorr variable.list theory.list ErrorType"<<endl;
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
 v_HistVector.resize(HistNames.size());

 vector<vector<TH1D *>> v_HistVectorBin;

 TFile* writefile = new TFile("PartonCorr_" + (TString)argv[3] + ".root", "RECREATE");
 TFile* theoryfile[rootNames.size()];

 PDFReweight* PDFPlot = new PDFReweight();
 PDFPlot->LinkFile(writefile);
 PDFPlot->InitialPDF("CT18NNLO", 0);
// PDFPlot->InitialPDF("CT18AsNNLO", 0);
// PDFPlot->InitialPDF("CT18AsLatNNLO", 0);
// PDFPlot->InitialPDF("MSHT20nnlo_as118", 0);


 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   theoryfile[ifile] = new TFile(rootNames.at(ifile));
 }

 for(int ihist = 0; ihist < HistNames.size(); ihist++){
   writefile->cd();

   for(int ifile = 0; ifile < rootNames.size(); ifile++){
     v_HistVector.at(ihist).push_back((TH1D *)theoryfile[ifile]->Get(HistNames.at(ihist)));
     v_HistVector.at(ihist).at(ifile)->Write(HistNames.at(ihist) + (TString)"_PDF" + (int)ifile);
   }
 }

 int Nbin = 0;
 for(int ihist = 0; ihist < HistNames.size(); ihist++){
   Nbin += v_HistVector.at(ihist).at(0)->GetNbinsX();
 }

 v_HistVectorBin.resize(Nbin);

 for(int ihist = 0; ihist < HistNames.size(); ihist++){
   writefile->cd();

   int NSavedHist = 0;
   for(int jhist = 0; jhist < ihist; jhist++){
     NSavedHist += v_HistVector.at(jhist).at(0)->GetNbinsX();
   }

   for(int ifile = 0; ifile < rootNames.size(); ifile++){

     for(int ibin = 1; ibin <= v_HistVector.at(ihist).at(ifile)->GetNbinsX(); ibin++){
       TString HistName = HistNames.at(ihist) + (TString)"_bin" + (int)ibin + (TString)"_PDF" + (int)ifile;
       int NHist = (ibin - 1) + NSavedHist;
       v_HistVectorBin.at(NHist).push_back(new TH1D(HistName, HistName, 1, 0, 1));
       v_HistVectorBin.at(NHist).at(ifile)->SetBinContent(1, v_HistVector.at(ihist).at(ifile)->GetBinContent(ibin));
       v_HistVectorBin.at(NHist).at(ifile)->SetBinError(1, v_HistVector.at(ihist).at(ifile)->GetBinError(ibin));
     }
   }
 }

 for(int ihist = 0; ihist < v_HistVectorBin.size(); ihist++){
   cout<<"Draw parton correlation for histogram "<<ihist + 1<<endl;
//   PDFPlot->DrawPartonCorrelation(v_HistVectorBin.at(ihist), 2, 58, argv[3]);
//   PDFPlot->DrawPartonCorrelation(v_HistVectorBin.at(ihist), 1, 58, argv[3]);
//   PDFPlot->DrawPartonCorrelation(v_HistVectorBin.at(ihist), 3, 68, argv[3]);
//   PDFPlot->DrawPartonCorrelation(v_HistVectorBin.at(ihist), 0, 58, argv[3]);
//   PDFPlot->DrawPartonCorrelation(v_HistVectorBin.at(ihist), -2, 58, argv[3]);
//   PDFPlot->DrawPartonCorrelation(v_HistVectorBin.at(ihist), -1, 58, argv[3]);
//   for(int i = 12; i <= 39; i++){
//     PDFPlot->DrawPartonCorrelation(v_HistVectorBin.at(ihist), i, 58, argv[3]);
//   }
  
   for(int i = 42; i <= 46; i++){
     PDFPlot->DrawPartonCorrelation(v_HistVectorBin.at(ihist), i, 58, argv[3]);
   }
 }


 ///////////////////////
 //  delete and save  //
 ///////////////////////

 for(int ihist = 0; ihist < HistNames.size(); ihist++){
   writefile->cd();

   int NSavedHist = 0;
   for(int jhist = 0; jhist < ihist; jhist++){
     NSavedHist += v_HistVector.at(jhist).at(0)->GetNbinsX();
   }

   for(int ifile = 0; ifile < rootNames.size(); ifile++){

     for(int ibin = 1; ibin <= v_HistVector.at(ihist).at(ifile)->GetNbinsX(); ibin++){
       int NHist = (ibin - 1) + NSavedHist;
       delete v_HistVectorBin.at(NHist).at(ifile);
     }
   }
 }

 PDFPlot->SaveFile();

 return 1;
}

