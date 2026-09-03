#include <iostream>
#include <fstream>
#include "Tools/Tools.h"
#include "Calculation/PineAPPLHelper.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"usage: PineAPPLConvolute GridName"<<endl;
   return 0;
 }

 TString GridName = argv[1];
 //TString GridName = "/mnt/home/fuyao3/FittingCode/PineAPPLtables/CMS_TTBAR_8TEV_LJ_DIF_YTTBAR.pineappl.lz4";
 //TString GridName = "/mnt/home/fuyao3/FittingCode/PineAPPLtables/ATLAS_TTBAR_13TEV_HADR_DIF_MTTBAR-YTTBAR.pineappl.lz4";

 PineAPPLHelper* run = new PineAPPLHelper();

 run->InitialPDF("CT18NNLO", 0);
 cout<<getTime()<<": Initialize PDF done."<<endl;

 run->InitialGrid(GridName);
 cout<<getTime()<<": Initialize Grid done."<<endl;

 run->DefaultConvolute();

 return 1;
}
