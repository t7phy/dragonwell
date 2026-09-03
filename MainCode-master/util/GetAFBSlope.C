#include "Tools/Tools.h"
#include "Analysis/HistsResBos.h"
#include "RootCommon.h"

int main(int argc, char **argv)
{
 if(argc != 2){
   cout<<"ERROR! usage ./GetAFBSlope filename"<<endl;
   return 0;
 }

 double xbins1[11] = {80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100};
 double xbins2[31] = {60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120};
 double xbins3[11] = {78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98};
 double xbins4[2] = {78, 98};
 double xbins5[3] = {80, 88, 100};
 double xbins6[3] = {80, 88, 91};

 TFile *file = new TFile(argv[1], "UPDATE");
 TH1D *FZmass = (TH1D *)file->Get("FZmass_CF");
 TH1D *BZmass = (TH1D *)file->Get("BZmass_CF");
 TH1D *FZmass2 = (TH1D *)file->Get("FZmass_CF");
 TH1D *BZmass2 = (TH1D *)file->Get("BZmass_CF");
 TH1D *FZmass3 = (TH1D *)file->Get("FZmass_CF");
 TH1D *BZmass3 = (TH1D *)file->Get("BZmass_CF");
 TH1D *FZmass4 = (TH1D *)file->Get("FZmass_CF");
 TH1D *BZmass4 = (TH1D *)file->Get("BZmass_CF");
 TH1D *FZmass5 = (TH1D *)file->Get("FZmass_CF");
 TH1D *BZmass5 = (TH1D *)file->Get("BZmass_CF");
 TH1D *FZmass6 = (TH1D *)file->Get("FZmass_CF");
 TH1D *BZmass6 = (TH1D *)file->Get("BZmass_CF");

 FZmass = (TH1D *)FZmass->Rebin(10, "FZmass", xbins1);
 BZmass = (TH1D *)BZmass->Rebin(10, "BZmass", xbins1);

 FZmass2 = (TH1D *)FZmass2->Rebin(30, "FZmass2", xbins2);
 BZmass2 = (TH1D *)BZmass2->Rebin(30, "BZmass2", xbins2);

 FZmass3 = (TH1D *)FZmass3->Rebin(10, "FZmass3", xbins3);
 BZmass3 = (TH1D *)BZmass3->Rebin(10, "BZmass3", xbins3);

 FZmass4 = (TH1D *)FZmass4->Rebin(1, "FZmass4", xbins4);
 BZmass4 = (TH1D *)BZmass4->Rebin(1, "BZmass4", xbins4);

 FZmass5 = (TH1D *)FZmass5->Rebin(2, "FZmass5", xbins5);
 BZmass5 = (TH1D *)BZmass5->Rebin(2, "BZmass5", xbins5);

 FZmass6 = (TH1D *)FZmass6->Rebin(2, "FZmass6", xbins6);
 BZmass6 = (TH1D *)BZmass6->Rebin(2, "BZmass6", xbins6);

// FZmass->Rebin(2);
// BZmass->Rebin(2);

 TH1D *AFB = (TH1D *)FZmass->Clone("AFB");
 AFB->Reset();
 AFBFunction(FZmass, BZmass, AFB);

 TH1D *AFB2 = (TH1D *)FZmass2->Clone("AFB");
 AFB2->Reset();
 AFBFunction(FZmass2, BZmass2, AFB2);

 TH1D *AFB3 = (TH1D *)FZmass3->Clone("AFB_78_98_10bin");
 AFB3->Reset();
 AFBFunction(FZmass3, BZmass3, AFB3);

 TH1D *AFB4 = (TH1D *)FZmass4->Clone("AFB_78_98_1bin");
 AFB4->Reset();
 AFBFunction(FZmass4, BZmass4, AFB4);

 TH1D *AFB5 = (TH1D *)FZmass5->Clone("AFB_80_100_2bin");
 AFB5->Reset();
 AFBFunction(FZmass5, BZmass5, AFB5);

 TH1D *AFB6 = (TH1D *)FZmass6->Clone("AFB_80_91_2bin");
 AFB6->Reset();
 AFBFunction(FZmass6, BZmass6, AFB6);


 TH1D *AFBSlope = new TH1D("AFBSlope", "AFBSlope", 1, 80, 100);
 TH1D *AFBDiff = new TH1D("AFBDiffSym", "AFBDiffSym", AFB2->GetNbinsX() / 2, 1, AFB2->GetNbinsX() / 2);
 TH1D *AFBDiff_ZPole = new TH1D("AFBDiff_ZPole", "AFBDiff_ZPole", 5, 1, 5);
 TH1D *AFBDiff_Side = new TH1D("AFBDiff_Side", "AFBDiff_Side", 10, 1, 10);
 TH1D *AFBDiff_ZPole_78_98 = new TH1D("AFBDiff_ZPole_78_98", "AFBDiff_ZPole_78_98", 5, 1, 5);
 TH1D *AFBDiff_ZPole_80_100_2bin = new TH1D("AFBDiff_ZPole_80_100_2bin", "AFBDiff_ZPole_80_100_2bin", 1, 1, 2);
 TH1D *AFBDiff_ZPole_80_91_2bin = new TH1D("AFBDiff_ZPole_80_91_2bin", "AFBDiff_ZPole_80_91_2bin", 1, 1, 2);


 for(int ibin = 1; ibin <= AFBDiff->GetNbinsX(); ibin++){
   int FirstBin = ibin;
   int LastBin = AFBDiff->GetNbinsX() * 2 - (ibin - 1);

   double Diff = AFB2->GetBinContent(FirstBin) - AFB2->GetBinContent(LastBin);
   double DiffErr = sqrt(AFB2->GetBinError(FirstBin) * AFB2->GetBinError(FirstBin) + AFB2->GetBinError(LastBin) * AFB2->GetBinError(LastBin));

   if(ibin <= 10){
     AFBDiff_Side->SetBinContent(ibin, Diff);
     AFBDiff_Side->SetBinError(ibin, DiffErr);
   }
   else{
     AFBDiff_ZPole->SetBinContent(ibin - 10, Diff);
     AFBDiff_ZPole->SetBinError(ibin - 10, DiffErr);
   }
 }

 for(int ibin = 1; ibin <= AFBDiff_ZPole_78_98->GetNbinsX(); ibin++){
   int FirstBin = ibin;
   int LastBin = AFBDiff_ZPole_78_98->GetNbinsX() * 2 - (ibin - 1);

   double Diff = AFB3->GetBinContent(FirstBin) - AFB3->GetBinContent(LastBin);
   double DiffErr = sqrt(AFB3->GetBinError(FirstBin) * AFB3->GetBinError(FirstBin) + AFB3->GetBinError(LastBin) * AFB3->GetBinError(LastBin));

   AFBDiff_ZPole_78_98->SetBinContent(ibin, Diff);
   AFBDiff_ZPole_78_98->SetBinError(ibin, DiffErr);
 }

 for(int ibin = 1; ibin <= AFBDiff_ZPole_80_100_2bin->GetNbinsX(); ibin++){
   int FirstBin = ibin;
   int LastBin = AFBDiff_ZPole_80_100_2bin->GetNbinsX() * 2 - (ibin - 1);

   double Diff = AFB5->GetBinContent(FirstBin) - AFB5->GetBinContent(LastBin);
   double DiffErr = sqrt(AFB5->GetBinError(FirstBin) * AFB5->GetBinError(FirstBin) + AFB5->GetBinError(LastBin) * AFB5->GetBinError(LastBin));

   AFBDiff_ZPole_80_100_2bin->SetBinContent(ibin, Diff);
   AFBDiff_ZPole_80_100_2bin->SetBinError(ibin, DiffErr);

   cout<<FirstBin<<" "<<AFB5->GetBinContent(FirstBin)<<" "<<AFB5->GetBinError(FirstBin)<<endl;
   cout<<FirstBin<<" "<<AFB5->GetBinContent(LastBin)<<" "<<AFB5->GetBinError(LastBin)<<endl;
 }

 for(int ibin = 1; ibin <= AFBDiff_ZPole_80_91_2bin->GetNbinsX(); ibin++){
   int FirstBin = ibin;
   int LastBin = AFBDiff_ZPole_80_91_2bin->GetNbinsX() * 2 - (ibin - 1);

   double Diff = AFB6->GetBinContent(FirstBin) - AFB6->GetBinContent(LastBin);
   double DiffErr = sqrt(AFB6->GetBinError(FirstBin) * AFB6->GetBinError(FirstBin) + AFB6->GetBinError(LastBin) * AFB6->GetBinError(LastBin));

   AFBDiff_ZPole_80_91_2bin->SetBinContent(ibin, Diff);
   AFBDiff_ZPole_80_91_2bin->SetBinError(ibin, DiffErr);

   cout<<FirstBin<<" "<<AFB6->GetBinContent(FirstBin)<<" "<<AFB6->GetBinError(FirstBin)<<endl;
   cout<<FirstBin<<" "<<AFB6->GetBinContent(LastBin)<<" "<<AFB6->GetBinError(LastBin)<<endl;
 }


 TF1 *fitting;
 double *par = new double[2];
 double *parErr = new double[2];
 LinearFitting(AFB, fitting, par, parErr);

 AFBSlope->SetBinContent(1, par[0]);
 AFBSlope->SetBinError(1, parErr[0]);

 file->cd();
 AFB->Write();
 AFBSlope->Write();
/* AFBDiff->Write();
 AFBDiff_ZPole->Write();
 AFBDiff_Side->Write();
 AFBDiff_ZPole_78_98->Write();
 AFB3->Write();
 AFB4->Write();
 AFBDiff_ZPole_80_100_2bin->Write();
 AFB5->Write();
*/
 AFBDiff_ZPole_80_91_2bin->Write();
 AFB6->Write();

 return 1;
}
