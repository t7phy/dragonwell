#include <iostream>
#include "DilutionFitting/FlavorSearch.h"

using namespace std;

int main(int argc, char** argv)
{
 int nSet = 58;
 vector<TH1D *> HistVector(nSet + 1);
 vector<double> Observable(nSet + 1);


 TFile* file = new TFile("save_LeptonPt_LowQT_LHC_Pseudodata.root");

 for(int i = 0; i <= nSet; i++){
   HistVector.at(i) = (TH1D *)file->Get((TString)"WMassResult_PDF" + (int)i);
   Observable.at(i) = HistVector.at(i)->GetBinContent(1);
 }

 vector<TString> rootNames;
 TString rootName;

 ifstream infile;
  infile.open("theory.list",ios::in);
 while(infile>>rootName){
   rootNames.push_back(rootName);
 }
 infile.close();

/* for(int i = 0; i <= nSet; i++){
   TFile* file = new TFile(rootNames.at(i));
   HistVector.at(i) = (TH1D *)file->Get((TString)"LeptonPt_LowQT_LHC_High");
   Observable.at(i) = HistVector.at(i)->GetBinContent(1);
 }
*/

 FlavorSearch* run = new FlavorSearch();
 run->openFile("FlavorCombination.root");
 run->InitialPDFAll("CT18NNLO", 58);
 run->InitialAllFlavors();
 run->InputObservable(Observable);

 run->TurnOffAll();
 run->FitParameter(11);
 run->FitParameter(12);
 //run->FitParameter(13);
 //run->FitParameter(14);
 //run->FitParameter(15);
 run->FitParameter(16);
 run->FitParameter(17);
 run->FitParameter(18);
 //run->FitParameter(19);
 //run->FitParameter(20);
 //run->FitParameter(21);

 //run->Fit(2, 1);
 //run->DrawCorrelation();
 //run->Fit(3, 1);
 //run->DrawCorrelation();
 //run->Fit(4, 1);
 //run->DrawCorrelation();
 run->Fit(1, 1);
 run->DrawCorrelation();

 run->DrawSpecialCorrelation("Special");

 run->ResetParameters();
 run->SetParameter(11, 1.0);
 run->SetParameter(12, -1.0);
 run->SetParameter(16, -3.0);
 run->SetParameter(17, -1.0);
 run->SetParameter(18, -1.0);
 run->DrawCorrelation("Fix1");
 
 //run->IndividualContribution();
 //run->ScanAllCombinations();
 run->SaveFile();

 return 1;
}

