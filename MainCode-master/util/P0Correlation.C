#include <iostream>
#include "RootCommon.h"
#include "Tools/Tools.h"
#include "PDFHelper/PDFReweight.h"

using namespace std;

int main(int argc, char** argv)
{
 ifstream infile;
   infile.open("theory.list", ios::in);

 TString rootName;
 vector<TString> rootNames;

 while(infile >> rootName){
   rootNames.push_back(rootName);
 }

 vector<TH3D *> P0uTheory(rootNames.size());
 vector<TH3D *> P0dTheory(rootNames.size());

 for(int i = 0; i < rootNames.size(); i++){
   TFile* file = new TFile(rootNames.at(i));

   P0uTheory.at(i) = (TH3D *)file->Get("CoefficientZMass_ZY_QT_uu_wrong_Average");
   P0dTheory.at(i) = (TH3D *)file->Get("CoefficientZMass_ZY_QT_dd_wrong_Average");
 }

 vector<vector<TH1D *>> P0uValueSet;
 vector<vector<TH1D *>> P0dValueSet;

 DecompositeTH3DtoTH1D(P0uTheory, P0uValueSet);
 DecompositeTH3DtoTH1D(P0dTheory, P0dValueSet);

 TFile* writefile = new TFile("P0Correlation.root", "RECREATE");
 writefile->cd();

 PDFReweight* run = new PDFReweight();
 run->LinkFile(writefile);
 run->InitialPDF("CT18NNLO", 0);
 for(int i = 0; i < P0uValueSet.size(); i++){
   run->DrawPartonCorrelation(P0uValueSet.at(i), 33, 58, "Symmetry");
   run->DrawPartonCorrelation(P0uValueSet.at(i), 34, 58, "Symmetry");
   run->DrawPartonCorrelation(P0dValueSet.at(i), 33, 58, "Symmetry");
   run->DrawPartonCorrelation(P0dValueSet.at(i), 34, 58, "Symmetry");
 }

 writefile->Write();
 writefile->Close();

 return 1;

}

