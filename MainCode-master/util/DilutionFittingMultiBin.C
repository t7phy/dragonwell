#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "CompareDataTheory/CompareDataTheory.h"
#include "TMinuitHelper/TMinuitHelper.h"
#include "Tools/Tools.h"
#include "SpecialHist/MultiBinHist.h"

using namespace std;

TH2D* global_Dilution_uu;
TH2D* global_Dilution_dd;
TH2D* global_FZmass_ZY_uu;
TH2D* global_FZmass_ZY_dd;
TH2D* global_FZmass_ZY_gg;
TH2D* global_BZmass_ZY_uu;
TH2D* global_BZmass_ZY_dd;
TH2D* global_BZmass_ZY_gg;

TH2D* global_MC;
TH2D* global_Data;
TH2D* global_MC_AFB2D;
TH2D* global_Data_AFB2D;

MultiBinHist* global_Dilution_uu_multi;
MultiBinHist* global_Dilution_dd_multi;
MultiBinHist* global_FZmass_ZY_uu_multi;
MultiBinHist* global_FZmass_ZY_dd_multi;
MultiBinHist* global_FZmass_ZY_gg_multi;
MultiBinHist* global_BZmass_ZY_uu_multi;
MultiBinHist* global_BZmass_ZY_dd_multi;
MultiBinHist* global_BZmass_ZY_gg_multi;

MultiBinHist* global_ZMass_ZY_uu_multi;
MultiBinHist* global_ZMass_ZY_dd_multi;

MultiBinHist* global_MC_multi;
MultiBinHist* global_Data_multi;
MultiBinHist* global_MC_AFB2D_multi;
MultiBinHist* global_Data_AFB2D_multi;

double MinChi2 = 100000.0;

void udDilutionFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{

 double Chi2 = 0.0;

 MultiBinHist* FZmass_ZY_uu_multi = global_FZmass_ZY_uu_multi->Clone("FZmass_ZY_uu_multi");
 MultiBinHist* FZmass_ZY_dd_multi = global_FZmass_ZY_dd_multi->Clone("FZmass_ZY_dd_multi");
 MultiBinHist* FZmass_ZY_gg_multi = global_FZmass_ZY_gg_multi->Clone("FZmass_ZY_gg_multi");
 MultiBinHist* BZmass_ZY_uu_multi = global_BZmass_ZY_uu_multi->Clone("BZmass_ZY_uu_multi");
 MultiBinHist* BZmass_ZY_dd_multi = global_BZmass_ZY_dd_multi->Clone("BZmass_ZY_dd_multi");
 MultiBinHist* BZmass_ZY_gg_multi = global_BZmass_ZY_gg_multi->Clone("BZmass_ZY_gg_multi");
 MultiBinHist* Dilution_uu_multi = global_Dilution_uu_multi->Clone("Dilution_ZMass_ZY_uu_multi");
 MultiBinHist* Dilution_dd_multi = global_Dilution_dd_multi->Clone("Dilution_ZMass_ZY_dd_multi");

 MultiBinHist* ZMass_ZY_uu_multi = global_ZMass_ZY_uu_multi->Clone("ZMass_ZY_uu_multi");
 MultiBinHist* ZMass_ZY_dd_multi = global_ZMass_ZY_dd_multi->Clone("ZMass_ZY_dd_multi");

 double uIntegralY1 = ZMass_ZY_uu_multi->Integral(0);
 double uIntegralY2 = ZMass_ZY_uu_multi->Integral(1);
 double uIntegralY3 = ZMass_ZY_uu_multi->Integral(2);
 double dIntegralY1 = ZMass_ZY_dd_multi->Integral(0);
 double dIntegralY2 = ZMass_ZY_dd_multi->Integral(1);
 double dIntegralY3 = ZMass_ZY_dd_multi->Integral(2);

 vector<double> uParVector;
 vector<double> dParVector;
 vector<double> gParVector = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

 uParVector.push_back(par[0]);
 uParVector.push_back(par[1]);
 uParVector.push_back(par[2]);
 uParVector.push_back((par[0] * uIntegralY1 + par[1] * uIntegralY2) / (uIntegralY1 + uIntegralY2));
 uParVector.push_back((par[1] * uIntegralY2 + par[2] * uIntegralY3) / (uIntegralY2 + uIntegralY3));
 uParVector.push_back((par[0] * uIntegralY1 + par[1] * uIntegralY2 + par[2] * uIntegralY3) / (uIntegralY1 + uIntegralY2 + uIntegralY3));

 dParVector.push_back(par[3]);
 dParVector.push_back(par[4]);
 dParVector.push_back(par[5]);
 dParVector.push_back((par[3] * dIntegralY1 + par[4] * dIntegralY2) / (dIntegralY1 + dIntegralY2));
 dParVector.push_back((par[4] * dIntegralY2 + par[5] * dIntegralY3) / (dIntegralY2 + dIntegralY3));
 dParVector.push_back((par[3] * dIntegralY1 + par[4] * dIntegralY2 + par[5] * dIntegralY3) / (dIntegralY1 + dIntegralY2 + dIntegralY3));

 ApplyDilution(FZmass_ZY_uu_multi, BZmass_ZY_uu_multi, Dilution_uu_multi, false, uParVector);
 ApplyDilution(FZmass_ZY_dd_multi, BZmass_ZY_dd_multi, Dilution_dd_multi, false, dParVector);
 ApplyDilution(FZmass_ZY_gg_multi, BZmass_ZY_gg_multi, Dilution_uu_multi, true, gParVector);

 uParVector.clear();
 dParVector.clear();

 MultiBinHist* FZmass2D_multi = FZmass_ZY_uu_multi->Clone("FZmass2D");
 FZmass2D_multi->Add(FZmass_ZY_dd_multi);
 FZmass2D_multi->Add(FZmass_ZY_gg_multi);

 MultiBinHist* BZmass2D_multi = BZmass_ZY_uu_multi->Clone("BZmass2D");
 BZmass2D_multi->Add(BZmass_ZY_dd_multi);
 BZmass2D_multi->Add(BZmass_ZY_gg_multi);

 MultiBinHist *AFB2D_multi = FZmass2D_multi->Clone("AFB2D");
 AFB2D_multi->Reset();
 AFBFunction(FZmass2D_multi, BZmass2D_multi, AFB2D_multi);

 double xbins[AFB2D_multi->nbin / 2 + 1];
 for(int i = 0; i < AFB2D_multi->nbin / 2 + 1; i++){xbins[i] = i + 1;}
 MultiBinHist* AFBDiff2D_multi = new MultiBinHist(AFB2D_multi->MultiBinVector);
 AFBDiff2D_multi->DefineHist(AFB2D_multi->name + (TString)"_Diff", AFB2D_multi->name + (TString)"_Diff", AFB2D_multi->nbin / 2, xbins);

 GetAFBDiff(AFB2D_multi, AFBDiff2D_multi);

 global_MC_multi = AFBDiff2D_multi->Clone("global_AFB2D_Diff");
 global_MC_AFB2D_multi = AFB2D_multi->Clone("AFB2D");

 Chi2 = CalculateChi2(global_Data_multi, AFBDiff2D_multi);
 f = Chi2;
 if(f < MinChi2) MinChi2 = f;

 AFBDiff2D_multi->DeleteHist();
 delete AFBDiff2D_multi;

 cout<<"Min Chi2 = "<<MinChi2<<endl;
}

int main(int argc, char** argv)
{
 double massrange[31] = {60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120};

 vector<TString> rootNames;
 TString rootName;

 ifstream infile;
  infile.open("theoryCC.list",ios::in);
 while(infile>>rootName){
  rootNames.push_back(rootName);
 }
 infile.close();

 vector<TString> STWTemplates;
  infile.open("STWTemplate.list",ios::in);
 while(infile>>rootName){
  STWTemplates.push_back(rootName);
 }

 TString DataName = "/Data/yfu/MainCode/run/DilutionFitting/Pseudodata_0.2315/MC_results_mmht.root";
// TString DataName = "/Data/yfu/MainCode/run/DilutionFitting/If1363.00/MC_results.root";

 TString EtaRegion = "Full";

 TString VariableName = "AFB_" + EtaRegion;

 TFile* writefile = new TFile(VariableName + "_PDFResults.root", "RECREATE");
 writefile->cd();

 TString AFBName = "AFB_" + EtaRegion;

 TString Dilution2D_uu_Name = "Dilution_ZMass_ZY_uu";
 TString Dilution2D_dd_Name = "Dilution_ZMass_ZY_dd";
 TString FZmass_ZY_uu_Name = "FZmass_ZY_uu";
 TString FZmass_ZY_dd_Name = "FZmass_ZY_dd";
 TString FZmass_ZY_gg_Name = "FZmass_ZY_gg";
 TString BZmass_ZY_uu_Name = "BZmass_ZY_uu";
 TString BZmass_ZY_dd_Name = "BZmass_ZY_dd";
 TString BZmass_ZY_gg_Name = "BZmass_ZY_gg";
 TString ZMass_ZY_uu_Name = "ZMass_ZY_uu_total";
 TString ZMass_ZY_dd_Name = "ZMass_ZY_dd_total";
 TString ZMass_ZY_gg_Name = "ZMass_ZY_gg_total";
 TString AFB2DName = "AFB_Mass_ZY_Full";
 TString AFB2DDiffName = "AFB_Mass_ZY_Full_Diff";

 TFile *DataFile = new TFile(DataName);

 TH1D *DataAFB = (TH1D *)DataFile->Get("AFB_Full");
 DataAFB = (TH1D *)DataAFB->Rebin(30, "AFB_Full", massrange);

 vector<TH2D *> Data2DDiffVector;
 for(int imulti = 1; imulti <= 6; imulti++){
   TH2D *Data2DDiff = (TH2D *)DataFile->Get(AFB2DDiffName + "_MultiBin" + (int)imulti);
   Data2DDiffVector.push_back(Data2DDiff);
 }
 global_Data_multi = new MultiBinHist();
 global_Data_multi->Input(Data2DDiffVector);

 writefile->cd();
 DataAFB->Write();

 global_Data_multi->Write();

 vector<double> Su;
 vector<double> Sd;
 vector<double> Sg;
 vector<vector<double>> Sus;
 vector<vector<double>> Sds;
 vector<vector<double>> Sgs;
 TH1D* SFittingResult[57];
 vector<TH1D *> SFittingResults;
 for(int i = 0; i < 1; i++){
   TFile* file = new TFile(rootNames.at(i));

   vector<TH2D *> FZmass_ZY_uu_Vector;
   for(int imulti = 1; imulti <= 6; imulti++){
     TH2D *FZmass_ZY_uu = (TH2D *)file->Get(FZmass_ZY_uu_Name + "_MultiBin" + (int)imulti);
     FZmass_ZY_uu_Vector.push_back(FZmass_ZY_uu);
   }
   MultiBinHist* FZmass_ZY_uu_multi = new MultiBinHist();
   FZmass_ZY_uu_multi->Input(FZmass_ZY_uu_Vector);
   FZmass_ZY_uu_Vector.clear();

   vector<TH2D *> FZmass_ZY_dd_Vector;
   for(int imulti = 1; imulti <= 6; imulti++){
     TH2D *FZmass_ZY_dd = (TH2D *)file->Get(FZmass_ZY_dd_Name + "_MultiBin" + (int)imulti);
     FZmass_ZY_dd_Vector.push_back(FZmass_ZY_dd);
   }
   MultiBinHist* FZmass_ZY_dd_multi = new MultiBinHist();
   FZmass_ZY_dd_multi->Input(FZmass_ZY_dd_Vector);
   FZmass_ZY_dd_Vector.clear();

   vector<TH2D *> FZmass_ZY_gg_Vector;
   for(int imulti = 1; imulti <= 6; imulti++){
     TH2D *FZmass_ZY_gg = (TH2D *)file->Get(FZmass_ZY_gg_Name + "_MultiBin" + (int)imulti);
     FZmass_ZY_gg_Vector.push_back(FZmass_ZY_gg);
   }
   MultiBinHist* FZmass_ZY_gg_multi = new MultiBinHist();
   FZmass_ZY_gg_multi->Input(FZmass_ZY_gg_Vector);
   FZmass_ZY_gg_Vector.clear();

   vector<TH2D *> BZmass_ZY_uu_Vector;
   for(int imulti = 1; imulti <= 6; imulti++){
     TH2D *BZmass_ZY_uu = (TH2D *)file->Get(BZmass_ZY_uu_Name + "_MultiBin" + (int)imulti);
     BZmass_ZY_uu_Vector.push_back(BZmass_ZY_uu);
   }
   MultiBinHist* BZmass_ZY_uu_multi = new MultiBinHist();
   BZmass_ZY_uu_multi->Input(BZmass_ZY_uu_Vector);
   BZmass_ZY_uu_Vector.clear();

   vector<TH2D *> BZmass_ZY_dd_Vector;
   for(int imulti = 1; imulti <= 6; imulti++){
     TH2D *BZmass_ZY_dd = (TH2D *)file->Get(BZmass_ZY_dd_Name + "_MultiBin" + (int)imulti);
     BZmass_ZY_dd_Vector.push_back(BZmass_ZY_dd);
   }
   MultiBinHist* BZmass_ZY_dd_multi = new MultiBinHist();
   BZmass_ZY_dd_multi->Input(BZmass_ZY_dd_Vector);
   BZmass_ZY_dd_Vector.clear();

   vector<TH2D *> BZmass_ZY_gg_Vector;
   for(int imulti = 1; imulti <= 6; imulti++){
     TH2D *BZmass_ZY_gg = (TH2D *)file->Get(BZmass_ZY_gg_Name + "_MultiBin" + (int)imulti);
     BZmass_ZY_gg_Vector.push_back(BZmass_ZY_gg);
   }
   MultiBinHist* BZmass_ZY_gg_multi = new MultiBinHist();
   BZmass_ZY_gg_multi->Input(BZmass_ZY_gg_Vector);
   BZmass_ZY_gg_Vector.clear();

   vector<TH2D *> PDFDilution_uu_Vector;
   for(int imulti = 1; imulti <= 6; imulti++){
     TH2D *PDFDilution_uu = (TH2D *)file->Get(Dilution2D_uu_Name + "_MultiBin" + (int)imulti);
     PDFDilution_uu_Vector.push_back(PDFDilution_uu);
   }
   MultiBinHist* PDFDilution_uu_multi = new MultiBinHist();
   PDFDilution_uu_multi->Input(PDFDilution_uu_Vector);
   PDFDilution_uu_Vector.clear();

   vector<TH2D *> PDFDilution_dd_Vector;
   for(int imulti = 1; imulti <= 6; imulti++){
     TH2D *PDFDilution_dd = (TH2D *)file->Get(Dilution2D_dd_Name + "_MultiBin" + (int)imulti);
     PDFDilution_dd_Vector.push_back(PDFDilution_dd);
   }
   MultiBinHist* PDFDilution_dd_multi = new MultiBinHist();
   PDFDilution_dd_multi->Input(PDFDilution_dd_Vector);
   PDFDilution_dd_Vector.clear();

   vector<TH2D *> ZMass_ZY_uu_Vector;
   for(int imulti = 1; imulti <= 6; imulti++){
     TH2D *ZMass_ZY_uu = (TH2D *)file->Get(ZMass_ZY_uu_Name + "_MultiBin" + (int)imulti);
     ZMass_ZY_uu_Vector.push_back(ZMass_ZY_uu);
   }
   MultiBinHist* ZMass_ZY_uu_multi = new MultiBinHist();
   ZMass_ZY_uu_multi->Input(ZMass_ZY_uu_Vector);
   ZMass_ZY_uu_Vector.clear();

   vector<TH2D *> ZMass_ZY_dd_Vector;
   for(int imulti = 1; imulti <= 6; imulti++){
     TH2D *ZMass_ZY_dd = (TH2D *)file->Get(ZMass_ZY_dd_Name + "_MultiBin" + (int)imulti);
     ZMass_ZY_dd_Vector.push_back(ZMass_ZY_dd);
   }
   MultiBinHist* ZMass_ZY_dd_multi = new MultiBinHist();
   ZMass_ZY_dd_multi->Input(ZMass_ZY_dd_Vector);
   ZMass_ZY_dd_Vector.clear();

   global_FZmass_ZY_uu_multi = FZmass_ZY_uu_multi;
   global_FZmass_ZY_dd_multi = FZmass_ZY_dd_multi;
   global_FZmass_ZY_gg_multi = FZmass_ZY_gg_multi;
   global_BZmass_ZY_uu_multi = BZmass_ZY_uu_multi;
   global_BZmass_ZY_dd_multi = BZmass_ZY_dd_multi;
   global_BZmass_ZY_gg_multi = BZmass_ZY_gg_multi;
   global_Dilution_uu_multi = PDFDilution_uu_multi;
   global_Dilution_dd_multi = PDFDilution_dd_multi;
   global_ZMass_ZY_uu_multi = ZMass_ZY_uu_multi;
   global_ZMass_ZY_dd_multi = ZMass_ZY_dd_multi;

   TMinuitHelper *myMinuit = new TMinuitHelper(6);
   myMinuit->SetFCN(udDilutionFitting);
   myMinuit->Input(0, "SuY1", 0.0, 0.01, 0.0, 0.02);
   myMinuit->Input(1, "SuY2", 0.002, 0.01, 0.0, 0.02);
   myMinuit->Input(2, "SuY3", 0.005, 0.01, 0.0, 0.02);
   myMinuit->Input(3, "SdY1", 0.0, 0.01, 0.0, 0.02);
   myMinuit->Input(4, "SdY2", 0.002, 0.01, 0.0, 0.02);
   myMinuit->Input(5, "SdY3", 0.005, 0.01, 0.0, 0.02);

//   myMinuit->Input(0, "SuY1", 0.012, 0.0, 0.002, 0.0021);
//   myMinuit->Input(1, "SuY2", 0.012, 0.0, 0.006, 0.0061);
//   myMinuit->Input(2, "SuY3", 0.012, 0.0, 0.008, 0.0081);
//   myMinuit->Input(3, "SdY1", 0.012, 0.0, 0.0, 0.001);
//   myMinuit->Input(4, "SdY2", 0.012, 0.0, 0.005, 0.0051);
//   myMinuit->Input(5, "SdY3", 0.012, 0.0, 0.008, 0.0081);

//   myMinuit->Input(0, "SuY1", 0.0, 0.0, 0.0, 0.0021);
//   myMinuit->Input(1, "SuY2", 0.0, 0.0, 0.0, 0.0061);
//   myMinuit->Input(2, "SuY3", 0.0, 0.0, 0.0, 0.0081);
//   myMinuit->Input(3, "SdY1", 0.0, 0.0, 0.0, 0.001);
//   myMinuit->Input(4, "SdY2", 0.0, 0.0, 0.0, 0.0051);
//   myMinuit->Input(5, "SdY3", 0.0, 0.0, 0.0, 0.0081);
   myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
   myMinuit->Exec("MIGRAD", 100000, 0.001);
   myMinuit->GetParameter();
   double* SPar = new double[6];
   myMinuit->GetParameters(SPar);

   Su.push_back(SPar[0]);
   Su.push_back(SPar[1]);
   Su.push_back(SPar[2]);

   Sd.push_back(SPar[3]);
   Sd.push_back(SPar[4]);
   Sd.push_back(SPar[5]);

   Sg = {0.0, 0.0, 0.0};

   Sus.push_back(Su);
   Sds.push_back(Sd);
   Sgs.push_back(Sg);
   Su.clear();
   Sd.clear();
   Sg.clear();

//   SFittingResult[i] = new TH1D((TString)"SFittingResult_PDF" + (int)i, (TString)"SFittingResult_PDF" + (int)i, 2, 0, 2);
//   SFittingResult[i]->SetBinContent(1, SPar[0]);
//   SFittingResult[i]->SetBinContent(2, SPar[1]);
//   SFittingResult[i]->SetBinError(1, 0);
//   SFittingResult[i]->SetBinError(2, 0);

//   SFittingResults.push_back(SFittingResult[i]);

/////////////////

   TH2D* FZmass_ZY_uu = (TH2D *)file->Get(FZmass_ZY_uu_Name);
   TH2D* FZmass_ZY_dd = (TH2D *)file->Get(FZmass_ZY_dd_Name);
   TH2D* FZmass_ZY_gg = (TH2D *)file->Get(FZmass_ZY_gg_Name);
   TH2D* BZmass_ZY_uu = (TH2D *)file->Get(BZmass_ZY_uu_Name);
   TH2D* BZmass_ZY_dd = (TH2D *)file->Get(BZmass_ZY_dd_Name);
   TH2D* BZmass_ZY_gg = (TH2D *)file->Get(BZmass_ZY_gg_Name);
   TH2D* PDFDilution_uu = (TH2D *)file->Get(Dilution2D_uu_Name);
   TH2D* PDFDilution_dd = (TH2D *)file->Get(Dilution2D_dd_Name);

   Apply2DDilutionNY(FZmass_ZY_uu, BZmass_ZY_uu, PDFDilution_uu, false, Sus.at(i));
   Apply2DDilutionNY(FZmass_ZY_dd, BZmass_ZY_dd, PDFDilution_dd, false, Sds.at(i));
   Apply2DDilutionNY(FZmass_ZY_gg, BZmass_ZY_gg, PDFDilution_uu, true, Sgs.at(i));

   TH2D* FZmass2D = (TH2D *)FZmass_ZY_uu->Clone("FZmass2D");
   FZmass2D->Add(FZmass_ZY_dd);
   FZmass2D->Add(FZmass_ZY_gg);

   TH2D* BZmass2D = (TH2D *)BZmass_ZY_uu->Clone("BZmass2D");
   BZmass2D->Add(BZmass_ZY_dd);
   BZmass2D->Add(BZmass_ZY_gg);

   TH1D* Converted_AFB = new TH1D((TString)"AFB_PDF" + (int)i, (TString)"AFB_PDF" + (int)i, FZmass2D->GetNbinsX(), FZmass2D->GetXaxis()->GetBinLowEdge(1), FZmass2D->GetXaxis()->GetBinUpEdge(FZmass2D->GetNbinsX()));

   AFBFunction(FZmass2D, BZmass2D, Converted_AFB);

////////////////

   writefile->cd();
//   SFittingResult[i]->Write();
//   global_MC->Write();
//   global_MC_AFB2D->Write();
   Converted_AFB->Write();

   MinChi2 = 100000.0;
 }
/*
 TH1D* PDFAFB[57];
 TH2D* PDFDilution_uu[57];
 TH2D* PDFDilution_dd[57];
 vector<TH1D *> PDFAFBs;
 vector<TH2D *> PDFDilution_uus;
 vector<TH2D *> PDFDilution_dds;
 for(int i = 0; i < 57; i++){
   TFile* file = new TFile(rootNames.at(i));
   TH2D* FZmass_ZY_uu = (TH2D *)file->Get(FZmass_ZY_uu_Name);
   TH2D* FZmass_ZY_dd = (TH2D *)file->Get(FZmass_ZY_dd_Name);
   TH2D* FZmass_ZY_gg = (TH2D *)file->Get(FZmass_ZY_gg_Name);
   TH2D* BZmass_ZY_uu = (TH2D *)file->Get(BZmass_ZY_uu_Name);
   TH2D* BZmass_ZY_dd = (TH2D *)file->Get(BZmass_ZY_dd_Name);
   TH2D* BZmass_ZY_gg = (TH2D *)file->Get(BZmass_ZY_gg_Name);
   PDFDilution_uu[i] = (TH2D *)file->Get(Dilution2D_uu_Name);
   PDFDilution_dd[i] = (TH2D *)file->Get(Dilution2D_dd_Name);

   Apply2DDilution(FZmass_ZY_uu, BZmass_ZY_uu, PDFDilution_uu[i], false, Su.at(i));
   Apply2DDilution(FZmass_ZY_dd, BZmass_ZY_dd, PDFDilution_dd[i], false, Sd.at(i));
   Apply2DDilution(FZmass_ZY_gg, BZmass_ZY_gg, PDFDilution_uu[i], true, 0.0);

   TH2D* FZmass2D = (TH2D *)FZmass_ZY_uu->Clone("FZmass2D");
   FZmass2D->Add(FZmass_ZY_dd);
   FZmass2D->Add(FZmass_ZY_gg);

   TH2D* BZmass2D = (TH2D *)BZmass_ZY_uu->Clone("BZmass2D");
   BZmass2D->Add(BZmass_ZY_dd);
   BZmass2D->Add(BZmass_ZY_gg);

   PDFAFB[i] = new TH1D((TString)"AFB_PDF" + (int)i, (TString)"AFB_PDF" + (int)i, FZmass2D->GetNbinsX(), FZmass2D->GetXaxis()->GetBinLowEdge(1), FZmass2D->GetXaxis()->GetBinUpEdge(FZmass2D->GetNbinsX()));

   AFBFunction(FZmass2D, BZmass2D, PDFAFB[i]);

   PDFAFBs.push_back(PDFAFB[i]);
   PDFDilution_uus.push_back(PDFDilution_uu[i]);
   PDFDilution_dds.push_back(PDFDilution_dd[i]);

   writefile->cd();
   PDFAFB[i]->Write();

   cout<<Su.at(i)<<" "<<Sd.at(i)<<" "<<SFittingResult[i]->GetBinContent(1)<<" "<<SFittingResult[i]->GetBinContent(2)<<endl;
 }

 TH1D* STWAFB[40];
 vector<TH1D *> STWAFBs;
 for(int i = 0; i < 40; i++){
   TFile* file = new TFile(STWTemplates.at(i));
   TH2D* FZmass_ZY_uu = (TH2D *)file->Get(FZmass_ZY_uu_Name);
   TH2D* FZmass_ZY_dd = (TH2D *)file->Get(FZmass_ZY_dd_Name);
   TH2D* FZmass_ZY_gg = (TH2D *)file->Get(FZmass_ZY_gg_Name);
   TH2D* BZmass_ZY_uu = (TH2D *)file->Get(BZmass_ZY_uu_Name);
   TH2D* BZmass_ZY_dd = (TH2D *)file->Get(BZmass_ZY_dd_Name);
   TH2D* BZmass_ZY_gg = (TH2D *)file->Get(BZmass_ZY_gg_Name);

   Apply2DDilution(FZmass_ZY_uu, BZmass_ZY_uu, PDFDilution_uus.at(0), false, Su.at(0));
   Apply2DDilution(FZmass_ZY_dd, BZmass_ZY_dd, PDFDilution_dds.at(0), false, Sd.at(0));
   Apply2DDilution(FZmass_ZY_gg, BZmass_ZY_gg, PDFDilution_uus.at(0), true, 0.0);

   TH2D* FZmass2D = (TH2D *)FZmass_ZY_uu->Clone("FZmass2D");
   FZmass2D->Add(FZmass_ZY_dd);
   FZmass2D->Add(FZmass_ZY_gg);

   TH2D* BZmass2D = (TH2D *)BZmass_ZY_uu->Clone("BZmass2D");
   BZmass2D->Add(BZmass_ZY_dd);
   BZmass2D->Add(BZmass_ZY_gg);

   STWAFB[i] = new TH1D((TString)"AFB_STW" + (int)i, (TString)"AFB_STW" + (int)i, FZmass2D->GetNbinsX(), FZmass2D->GetXaxis()->GetBinLowEdge(1), FZmass2D->GetXaxis()->GetBinUpEdge(FZmass2D->GetNbinsX()));

   AFBFunction(FZmass2D, BZmass2D, STWAFB[i]);

   STWAFBs.push_back(STWAFB[i]);

   writefile->cd();
   STWAFB[i]->Write();
 }

 double AFBPDFUnc = 0.0;
 CompareDataTheory *run = new CompareDataTheory();
 run->LinkOutFile(writefile);
 run->GetPDFUncertainty(PDFAFBs, STWAFBs, AFBPDFUnc);

 TH1D *Chi2_FittedSuSd = new TH1D("Chi2_FittedSuSd", "Chi2_FittedSuSd", 40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);
 TF1 *Fitting;
 for(int i = 0; i < STWAFBs.size(); i++){
   double Chi2 = CalculateChi2(DataAFB, STWAFBs.at(i));
   Chi2_FittedSuSd->SetBinContent(i, Chi2);
 }
 double stwFittedSuSd, stwErrorFittedSuSd;
 Chi2Fitting(Chi2_FittedSuSd, Fitting, stwFittedSuSd, stwErrorFittedSuSd);

 cout<<"FittedSuSd: "<<endl;
 cout<<"Central value: "<<stwFittedSuSd<<" Stat.unc: "<<stwErrorFittedSuSd<<" PDF unc: "<<AFBPDFUnc<<endl;

 TH1D *SFittingResultError;
 PDFUncertainty *SFittingResultPDFunc;
 SFittingResultPDFunc = new PDFUncertainty();
 SFittingResultPDFunc->SaveVariBin();
 SFittingResultPDFunc->Input1DPlot("Symmetry", SFittingResults, SFittingResultError);
*/



// for(int ibinx = 1; ibinx <= DataDilution->GetNbinsX(); ibinx++){
//   for(int ibiny = 1; ibiny <= DataDilution->GetNbinsY(); ibiny++){
 //     cout<<ibinx<<" "<<ibiny<<" "<<DataDilution->GetBinContent(ibinx, ibiny)<<" "<<DataDilution2->GetBinContent(ibinx, ibiny)<<" "<<DataDilution->GetBinContent(ibinx, ibiny) - DataDilution2->GetBinContent(ibinx, ibiny)<<endl;
//   }
// }

 writefile->cd();
 writefile->Write();
 writefile->Close();

 return 1;

}
