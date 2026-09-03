#include "FormatTransform/PDFAndQCDError.h"
#include "WZPolarization/HistsWZPolarization.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 4){
   cout<<"ERROR! usage ./PDFAndQCDError MC_results.root"<<endl;
   cout<<"    or usage ./PDFAndQCDError MC_results PDF 100"<<endl;
   return 0;   
 }

 HistsWZPolarization *myhists = new HistsWZPolarization();
 myhists->bookHists(1);

 PDFAndQCDError run;
 run.LinkHist(myhists);
 run.openPDFHistFile(argv[1], argv[2], atoi(argv[3]));
 run.openFile((TString)"MC_results_" + (TString)argv[2] + (TString)"Error.root");
 run.InitialFileStructure();
 run.SaveFile();

 return 1;
}
