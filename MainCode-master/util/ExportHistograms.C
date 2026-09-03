#include "FormatTransform/HistFormat.h"
#include "WZPolarization/HistsWZPolarization.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"ERROR! usage ./ExportHistograms MC_results.root"<<endl;
   cout<<"    or usage ./ExportHistograms MC_results"<<endl;
   return 0;   
 }

 HistsWZPolarization *myhists = new HistsWZPolarization();

 HistFormat run;
 run.LinkHist(myhists);
 run.openSysHistFile(argv[1]);
 run.openFile("ExportHistograms.root");
 run.InitialFileStructure();
 run.SaveFile();

 return 1;
}
