#include "RootCommon.h"

int main(int argc, char** argv)
{
 TFile *writefile = new TFile("TryGraph.root", "RECREATE");
 writefile->cd();

 TF1 *f1 = new TF1("function", "sin(x)", 0, 1);

 TGraph *h1 = new TGraph();
 h1->SetName("h1");



 h1->Write();

 writefile->Write();
 writefile->Close();

 return 1;
}
