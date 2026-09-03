#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{
 TFile *TheoryCorrelationFile = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/FSROn/rootfile/Pythia/AFB_PDFError_MonteCarlo.root");
 TH2D *TheoryCovariance = (TH2D *)TheoryCorrelationFile->Get("CovMatrix_PDFError");
 TH2D *InverseCovariance = (TH2D *)TheoryCovariance->Clone("InverseCovariance");
 InverseCovariance->Reset();

 for(int ibinx = 1; ibinx <= TheoryCovariance->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= TheoryCovariance->GetNbinsY(); ibiny++){
     cout<<InverseCovariance->GetBinContent(ibinx, ibiny)<<" ";
   }
   cout<<endl;
 }

 CalculateInverseMatrix(TheoryCovariance, InverseCovariance);
// ReverseMatrix(TheoryCovariance, InverseCovariance);

 for(int ibinx = 1; ibinx <= TheoryCovariance->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= TheoryCovariance->GetNbinsY(); ibiny++){
     cout<<InverseCovariance->GetBinContent(ibinx, ibiny)<<" ";
   }
   cout<<endl;
 }

 return 1;
}
