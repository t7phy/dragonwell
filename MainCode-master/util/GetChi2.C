#include <iostream>
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 4){
   cout<<"usage: ./GetChi2 rootfile1 rootfile2 histgram"<<endl;
   return 0;
 }

 TFile* file1 = new TFile(argv[1]);
 TH1D* h1 = (TH1D *)file1->Get(argv[3]);

 h1->Scale(1.0 / h1->Integral());

 TFile* file2 = new TFile(argv[2]);
 TH1D* h2 = (TH1D *)file2->Get(argv[3]);
 h2->Scale(1.0 / h2->Integral());

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double N1 = h1->GetBinContent(ibin);
   double N2 = h2->GetBinContent(ibin);
   double N2Error = h2->GetBinError(ibin);
   //cout<<"bin "<<ibin<<" : Difference: "<<(N1 - N2)<<" Error: "<<(N2Error)<<endl;
 }

 double Chi2 = CalculateChi2WithData(h2, h1);
 double PValue = TranslateChi2ToPValue(Chi2, h1->GetNbinsX() - 1);
 double Spartyness = TranslateChi2ToSpartyness(Chi2, h1->GetNbinsX() - 1);

 cout<<"Chi2 = "<<Chi2<<" P-Value: "<<PValue<<" Spartyness: "<<Spartyness<<endl;
 cout<<Chi2<<" & "<<PValue<<" & "<<Spartyness<<"\\\\"<<endl;

 return 1;
}
