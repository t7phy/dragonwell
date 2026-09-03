#include "FormatTransform/SystematicError.h"
#include "WZPolarization/HistsWZPolarization.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"ERROR! usage ./SystematicError MC_results.root"<<endl;
   cout<<"    or usage ./SystematicError MC_results"<<endl;
   return 0;   
 }

 HistsWZPolarization *myhists = new HistsWZPolarization();
 myhists->bookHists(1);

 SystematicError run;
 run.LinkHist(myhists);
 run.openSysHistFile(argv[1]);
 run.InitialHistName();
 run.openFile("MC_results.root");
 run.InitialFileStructure();
 run.SaveFile();

 return 1;
}
