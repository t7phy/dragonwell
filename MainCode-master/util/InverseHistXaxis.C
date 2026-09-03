#include "RootCommon.h"
#include "Tools/Tools.h"

int main(int argc, char** argv)
{
 if(argc != 3){
   std::cout<<"Usage: ./InverseHistXaxis filename histname"<<std::endl;
   return 0;
 }

 TFile *file = new TFile(argv[1], "UPDATE");
 TH1D *h1 = (TH1D *)file->Get(argv[2]);
 TH1D *inverse_h1;

 InverseHistXaxis(h1, inverse_h1);

 file->cd();
 inverse_h1->Write();
 file->Close();

 return 1;
}
