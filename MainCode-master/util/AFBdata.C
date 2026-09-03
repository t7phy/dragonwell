#include "FileForEPUMP/FileForEPUMP.h"

using namespace std;

double* DefineBins(int &size, int iflag)
{
 double* xbins = new double[100];
 if(iflag == 1){
   double xbins1[2] = {80,100};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 2;
 }
 if(iflag == 2){
   double xbins1[11] = {80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 11;
 }
 if(iflag == 3){
   double xbins1[27] = {60,62,64,66,68,70,72,74,76,78,80,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 27;
 }
 if(iflag == 4){
   double xbins1[12] = {60,65,70,75,80,100,105,110,115,120,125,130};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 12;
 }
 if(iflag == 5){
   double xbins1[52] = {60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 52;
 }
 if(iflag == 6){
   double xbins1[36] = {60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 36;
 }
 if(iflag == 7){
   double xbins1[15] = {60,65,70,75,80,85,90,95,100,105,110,115,120,125,130};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 15;
 }

 if(iflag == 8){
   double xbins1[11] = {66, 71, 76, 81, 86, 91, 96, 101, 106, 111, 116};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 11;
 }
 return xbins;
}

int main( int argc ,char **argv)
{
 TString EtaRegion = "CF";
 TString Statistic = "250M";
 TString STW = "2345";
 TString rootname = "/lustre/AtlUser/whma/CorrelationStudy/testdir/ResBos_CT14HERA2NNLO/merged.root";
 TString CorrName = "/lustre/AtlUser/yfu/pku_resbos/CT14HERA2NNLO_13TeV/rootfile/AFB_" + EtaRegion + "_PDFError_Symmetry.root";
 vector<TString> rootNames;
 TString rootName;

 ifstream infile;
  infile.open("theory" + EtaRegion + ".list",ios::in);
 while(infile>>rootName){
  rootNames.push_back(rootName);
 }

 TFile *file = new TFile(rootname);
// TH1D *h1 = (TH1D *)file->Get("AFB_" + EtaRegion);
 TH2D *Correlation = (TH2D *)file->Get("CovMatrix_" + EtaRegion);
// TH1D *h2 = (TH1D *)file->Get("AFB_" + EtaRegion + "_origin");

 TFile *Corrfile = new TFile(CorrName);
 TH1D *AFB1 = (TH1D *)Corrfile->Get("AFB_PDF1");
 TH1D *AFB0 = (TH1D *)Corrfile->Get("AFB_PDFCentral");
 TH1D *CorrHist = (TH1D *)AFB1->Clone("AFB1");
 CorrHist->Add(AFB0, -1);


 FileForEPUMP* data[1001];
 double* xbins;
 int size;

 double* myDataPoint;
 double* mySysErr;
 mySysErr = new double[100];
 double* myCorrSysErr;
 myCorrSysErr = new double[100];

 cout<<"Energy Scale uncertainty:"<<endl;
 for(int ibin = 0; ibin < Correlation->GetNbinsX(); ibin++){
   mySysErr[ibin] = sqrt(Correlation->GetBinContent(ibin + 1, ibin + 1));
   cout<<mySysErr[ibin]<<endl;
 }

 cout<<"PDF Correlated uncertainty:"<<endl;
 for(int ibin = 0; ibin < CorrHist->GetNbinsX(); ibin++){
   myCorrSysErr[ibin] = CorrHist->GetBinContent(ibin + 1);
   cout<<myCorrSysErr[ibin]<<endl;
 }
/*
  double DataPoint = h1->GetBinContent(ibin + 1);
  double StaError = h1->GetBinError(ibin + 1);
  double TotError = 0;
  double UncError = mySysErr[ibin];
  double Corr1 = mySysErr[ibin] / DataPoint;
  double Corr2 = 0;
  cout<<(h1->GetBinCenter(ibin+1) - h1->GetBinWidth(ibin+1) / 2)<<"     "<<(h1->GetBinCenter(ibin+1) + h1->GetBinWidth(ibin+1) / 2)<<"     "<<DataPoint<<"     "<<StaError<<"     "<<TotError<<"     "<<UncError<<"     "<<Corr1<<"     "<<Corr2<<endl;
 }
*/
 xbins = new double[100];
 xbins = DefineBins(size, 6);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 TString filename;
 for(int i = 4; i < 5; i++){
   filename = "AFB_" + EtaRegion + "_EnergyScale_" + (int)(i + 1) + "_withCorrErr";
   data[i] = new FileForEPUMP(filename);
   data[i]->Rebin(xbins, size);
   data[i]->InputData(rootname, "AFB_" + EtaRegion + "_" + (int)(i + 1), 0); //0 means not rebin
   data[i]->InputTheory(rootNames, "FZmass_" + EtaRegion, "BZmass_" + EtaRegion);
   data[i]->InputSysErr(mySysErr);
   data[i]->InputCorrSysErr(myCorrSysErr, "EnergyCorr");
   data[i]->SpecialStaError(0.1);
   data[i]->writedata();
   data[i]->writetheory();
   delete data[i];
 }
 delete[] xbins;

 xbins = new double[100];
 xbins = DefineBins(size, 6);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 filename = "AFB_" + EtaRegion + "_EnergyScale_5";
 data[1] = new FileForEPUMP(filename);
 data[1]->Rebin(xbins, size);
 data[1]->InputCovarianceMatrix(rootname, "CovMatrix_" + EtaRegion);
 data[1]->InputData(rootname, "AFB_" + EtaRegion + "_5", 0); //0 means not rebin
 data[1]->InputTheory(rootNames, "FZmass_" + EtaRegion, "BZmass_" + EtaRegion);
 data[1]->InputSysErr(mySysErr);
 data[1]->SpecialStaError(0.1);
 data[1]->writedata();
 data[1]->writetheory();
 delete data[1];
 delete xbins;

 xbins = new double[100];
 xbins = DefineBins(size, 8);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 filename = "AFB_" + EtaRegion + "_Correlation";
 data[1001] = new FileForEPUMP(filename);
 data[1001]->Rebin(xbins, size);
 data[1001]->InputCovarianceMatrix(rootname, "CovMatrix_" + EtaRegion);
 data[1001]->InputSysErr(mySysErr);
 data[1001]->InputData(rootNames.at(0), "FZmass_" + EtaRegion, "BZmass_" + EtaRegion);
 data[1001]->InputTheory(rootNames, "FZmass_" + EtaRegion, "BZmass_" + EtaRegion);
 data[1001]->SpecialStaError(0.1);
 data[1001]->writedata();
 data[1001]->writetheory();
 delete[] xbins;

/*
 xbins = new double[100];
 xbins = DefineBins(size, 7);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 filename = "AFB_" + EtaRegion + "_Full_CorrelationMinus";
 data[2] = new FileForEPUMP(filename);
 data[2]->Rebin(xbins, size);
 data[2]->InputCorrelation(-1);
 data[2]->InputSysErr(mySysErr);
 data[2]->writedata(rootname, "AFB_" + EtaRegion);
 data[2]->AFBtheory(rootNames, "FZmass_" + EtaRegion, "BZmass_" + EtaRegion);
 delete[] xbins;

 delete[] mySysErr;
 mySysErr = new double[100];
 for(int ibin = 0; ibin < h1->GetNbinsX(); ibin++){
   if(((h1->GetBinCenter(ibin+1) - h1->GetBinWidth(ibin+1) / 2) >= 80 && (h1->GetBinCenter(ibin+1) + h1->GetBinWidth(ibin+1) / 2) <= 100)) continue;
   cout<<(h1->GetBinCenter(ibin+1) - h1->GetBinWidth(ibin+1) / 2)<<" "<<(h1->GetBinCenter(ibin+1) + h1->GetBinWidth(ibin+1) / 2)<<endl;
   mySysErr[ibin] = (h1->GetBinContent(ibin + 1) - h2->GetBinContent(ibin + 1));
 }

 xbins = new double[100];
 xbins = DefineBins(size, 4);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 filename = "AFB_" + EtaRegion + "_Side_CorrelationPlus";
 data[3] = new FileForEPUMP(filename);
 data[3]->SetSideband();
 data[3]->Rebin(xbins, size);
 data[3]->InputCorrelation(1);
 data[3]->InputSysErr(mySysErr);
 data[3]->writedata(rootname, "AFB_" + EtaRegion);
 data[3]->AFBtheory(rootNames, "FZmass_" + EtaRegion, "BZmass_" + EtaRegion);
 delete[] xbins;

 xbins = new double[100];
 xbins = DefineBins(size, 4);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 filename = "AFB_" + EtaRegion + "_Side_CorrelationZero";
 data[4] = new FileForEPUMP(filename);
 data[4]->SetSideband();
 data[4]->Rebin(xbins, size);
 data[4]->InputCorrelation(0);
 data[4]->InputSysErr(mySysErr);
 data[4]->writedata(rootname, "AFB_" + EtaRegion);
 data[4]->AFBtheory(rootNames, "FZmass_" + EtaRegion, "BZmass_" + EtaRegion);
 delete[] xbins;

 xbins = new double[100];
 xbins = DefineBins(size, 4);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 filename = "AFB_" + EtaRegion + "_Side_CorrelationMinus";
 data[5] = new FileForEPUMP(filename);
 data[5]->SetSideband();
 data[5]->Rebin(xbins, size);
 data[5]->InputCorrelation(-1);
 data[5]->InputSysErr(mySysErr);
 data[5]->writedata(rootname, "AFB_" + EtaRegion);
 data[5]->AFBtheory(rootNames, "FZmass_" + EtaRegion, "BZmass_" + EtaRegion);
 delete[] xbins;
*/
 return 1;
}
