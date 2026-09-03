#include "TRandom3.h"
#include "TFile.h"
#include "TH1D.h"

using namespace std;

int main(int argc, char** argv)
{
 TRandom3 r(0);

 r.Uniform(0, 1);

 TFile* file = new TFile("random.root", "RECREATE");
 file->cd();

 TH1D* U = new TH1D("U", "U", 100, 0, 1);
 TH1D* Exp = new TH1D("Exp", "Exp", 100, 0, 10);

 for(int i = 0; i < 1000000; i++){
   double Value = r.Uniform(0, 1);
   double ExpValue = 0.0;
   if(Value > 0.0) ExpValue = -log(Value);
   U->Fill(Value, 1.0);
   Exp->Fill(ExpValue, 1.0);
 }

 U->Scale(1.0 / U->Integral());
 Exp->Scale(1.0 / Exp->Integral());

 file->Write();
 file->Close();

}

