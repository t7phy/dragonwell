#include <iostream>
#include "CTEQHelper/EVsets.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 4){
   cout<<"usage: ./DrawL2Sensitivity pdflist dtalist subName"<<endl;
   return 0;
 }

 EVsets* run = new EVsets();
 run->InitializePDF(argv[1]);
 run->InitializeData(argv[2]);
 run->openFile("save.root");
// run->DrawAllL2Sensitivity(0, 100.0);
// run->DrawL2Sensitivity(245, 0, 100.0);
 run->OutputePumpTheory(argv[3]);
 run->SaveFile();

 return 1;
}
