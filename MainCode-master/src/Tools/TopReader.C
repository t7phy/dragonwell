#include "Tools/TopReader.h"

TopReader::TopReader(const char* name)
{
 Initialize(name);
}

void TopReader::Initialize(const char* name)
{
 data.open(name);

 for(int i = 0; i < 13; i++){
   getline(data, FileLine);
   cout<<FileLine<<endl;
 }

 double LowerBoundary = 0.0, UpperBoundary = 0.0;
 double Number;
 TString skip;

 data >> skip >> skip >> skip >> LowerBoundary >> UpperBoundary;
 getline(data, FileLine);
 getline(data, FileLine);
 cout<<FileLine<<endl;

 while(data >> skip){
   if(skip == "HISTO") break;
   Number = stod(skip.Data());
   BinCenters.push_back(Number);

   data >> skip;
   Number = stod(skip.Data());
   Values.push_back(Number);
 }

 Binning.push_back(LowerBoundary);
 for(int i = 0; i < BinCenters.size(); i++){
   double Upper = BinCenters.at(i) * 2.0 - Binning.at(i);
   Binning.push_back(Upper);
 }

}

TH1D* TopReader::outputHistogram(const char* name)
{
 TH1D* h1;

 h1 = new TH1D(name, name, Binning.size() - 1, &Binning[0]);

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   h1->SetBinContent(ibin, Values.at(ibin - 1));
   h1->SetBinError(ibin, 0.0);
 }

 return h1;

}

