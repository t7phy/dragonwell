#include <iostream>
#include "CTEQHelper/LMScanHelper.h"

using namespace std;

int main(int argc, char** argv)
{
 vector<TString> DataList;
 vector<TString> SummaryList;
 TString FileName;

 ifstream infile;
  infile.open("data.list");

 while(infile >> FileName){
   DataList.push_back(FileName);
 }

 ifstream sumfiles("sum.list");

 while(sumfiles >> FileName){
   SummaryList.push_back(FileName);
 }

 vector<double> ParaList(15);
 for(int i = 0; i < 15; i++){
   ParaList.at(i) = 0.110 + 0.001 * i;
 }

 TFile* file = new TFile("save.root", "RECREATE");

 LMScanHelper* run = new LMScanHelper();
 run->LinkFile(file);
 run->InitialParameter(ParaList);
 run->InitialData(DataList);
 run->InitialSummary(SummaryList);
 run->DrawChi2("AlphaS");

 vector<TString> PlotDataList = {"E545", "E542", "E544", "E160", "E573", "E245", "E204", "E514", "E580", "E110"};

 run->Plotting("", PlotDataList);

 file->cd();
 file->Close();

 return 1;
}
