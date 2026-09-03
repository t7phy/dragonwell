#include <iostream>
#include "RootCommon.h"
#include "DilutionFitting/DilutionFitting.h"

using namespace std;

int main(int argc, char** argv)
{
 TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/i2Tn3.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/DeltaZY2QT2_RotatedCT18NNLO.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/ResBosDilution/MSHT20.00/MC_results.root";

 DilutionFitting* run = new DilutionFitting();
 //run->OnlyCentral();
 run->OpenFile();
 run->GetAFBStwLinear();
 run->InitialData(DataName);
 run->InitialTheory();
 run->InitialResult();

 for(int i = 1; i <= 10; i++){
   run->Fitting(0, 1, i);
   run->Fitting(0, 2, i);
   run->Fitting(0, 3, i);
   run->Fitting(0, 4, i);
   run->FittingCorr(1, i);
   run->FittingCorr(2, i);
   run->FittingCorr(3, i);
   run->FittingCorr(4, i);

//   run->Fitting(0, 2, i);
//   run->Fitting(0, 4, i);
 }

 run->GetStwCombinedError();
// run->DeltaInducedUnc(1, 2);
// run->DeltaInducedUnc(2, 2);
// run->DeltaInducedUnc(3, 2);
// run->DeltaInducedUnc(4, 2);
// run->LinearFitting(0, 4, 2);
 run->Save();

 return 1;
}
