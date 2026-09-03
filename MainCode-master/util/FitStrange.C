#include <iostream>
#include "RootCommon.h"
#include "DilutionFitting/StrangeAsymmetry.h"

using namespace std;

int main(int argc, char** argv)
{
 TString DataName = "/ustcfs2/yfu/MainCode/run/WDilution/CT18As.00/MC_results.root";

 StrangeAsymmetry* run = new StrangeAsymmetry();
 //run->OnlyCentral();
 run->OpenFile();
 run->InitialData(DataName);
 run->InitialTheory();
 run->InitialResult();

 run->FittingZ(0);

 run->Save();

 return 1;
}

