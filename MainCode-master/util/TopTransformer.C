#include "Tools/TopReader.h"

int main(int argc, char** argv)
{
 if(argc != 4){
   cout<<"usage: ./TopTransformer topname histname filename"<<endl;
 }

 TFile* file = new TFile(argv[3], "RECREATE");
 file->cd();

 TopReader data(argv[1]);
 TH1D* h1 = data.outputHistogram(argv[2]);

 file->Write();
 file->Close();

 return 1;
}
