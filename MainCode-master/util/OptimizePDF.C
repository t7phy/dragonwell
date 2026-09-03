#include "RootCommon.h"
#include "ePumpHelper/ePumpHelper.h"
#include "PDFHelper/PDFFigure.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"Please usage: ./OptimizePDF filename"<<endl;
   return 0;
 }

 TFile* file = new TFile("save.root", "RECREATE");

 ePumpHelper* EU = new ePumpHelper(argv[1]);
 EU->InitialOptimize();
 EU->Optimize();

 PDFFigure* run = new PDFFigure();
 run->InitialCTEQPDFAll("BeforeOptimize", EU->OldPDFSet);
 run->InitialCTEQPDFAll("AfterOptimize", EU->NewPDFSet);
 run->SetLegendName("BeforeOptimize", "CT18NNLO");
 run->SetupNesFlavorList(vector<TString>{"gluon", "d", "u", "s", "ubou", "dbod", "dboub"});
 run->GenerateEigenAll("BeforeOptimize", "AfterOptimize", "Symmetry", 100.0, 3);
 
 EU->LinkFile(file);

 EU->SaveOptimizeHist();
 file->Write();
 file->Close();


 return 1;
}
