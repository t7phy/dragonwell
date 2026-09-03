#include "DilutionFitting/StrangeAsymmetry.h"

StrangeAsymmetry::StrangeAsymmetry()
{

}

void StrangeAsymmetry::InitialData(TString DataName)
{
 this->DataName = DataName;

 TFile *DataFile = new TFile(DataName);
/*
 Data_WPlusAFC_MT = (TH1D *)DataFile->Get(WPlusAFC_MT_Name);
 Data_WMinusAFC_MT = (TH1D *)DataFile->Get(WMinusAFC_MT_Name);

 Data_WPlusAFC_MT_ud_Average = (TH1D *)DataFile->Get(WPlusAFC_MT_ud_Average_Name);
 Data_WPlusAFC_MT_cs_Average = (TH1D *)DataFile->Get(WPlusAFC_MT_cs_Average_Name);
 Data_WMinusAFC_MT_ud_Average = (TH1D *)DataFile->Get(WMinusAFC_MT_ud_Average_Name);
 Data_WMinusAFC_MT_cs_Average = (TH1D *)DataFile->Get(WMinusAFC_MT_cs_Average_Name);

 global_Data_WPlusAFC_MT = Data_WPlusAFC_MT;
 global_Data_WMinusAFC_MT = Data_WMinusAFC_MT;
*/

 Data_PositiveAFC = (TH1D *)DataFile->Get(PositiveAFC_Name);
 Data_NegativeAFC = (TH1D *)DataFile->Get(NegativeAFC_Name);
 Data_PositiveAFC_uu_Average = (TH1D *)DataFile->Get(PositiveAFC_uu_Average_Name);
 Data_NegativeAFC_uu_Average = (TH1D *)DataFile->Get(NegativeAFC_uu_Average_Name);
 Data_PositiveAFC_dd_Average = (TH1D *)DataFile->Get(PositiveAFC_dd_Average_Name);
 Data_NegativeAFC_dd_Average = (TH1D *)DataFile->Get(NegativeAFC_dd_Average_Name);
 Data_PositiveAFC_ss_Average = (TH1D *)DataFile->Get(PositiveAFC_ss_Average_Name);
 Data_NegativeAFC_ss_Average = (TH1D *)DataFile->Get(NegativeAFC_ss_Average_Name);

 global_Data_PositiveAFC = Data_PositiveAFC;
 global_Data_NegativeAFC = Data_NegativeAFC;

 cout<<"Initialize data finished."<<endl;

}

void StrangeAsymmetry::OpenFile()
{
 writefile = new TFile("StrangeAsymmetry.root", "RECREATE");
 writefile->cd();
}

void StrangeAsymmetry::InitialTheory()
{
 TString rootName;

 ifstream infile;
  infile.open("theory.list",ios::in);
 while(infile>>rootName){
  rootNames.push_back(rootName);
 }
 infile.close();

 for(int i = 0; i < rootNames.size(); i++){
   TFile* file = new TFile(rootNames.at(i));

   if(onlyCentral && i != 0) continue;
/*
   WPlusRelativeXsec_MT_ud_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(WPlusRelativeXsec_MT_ud_Name);
   WPlusRelativeXsec_MT_cs_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(WPlusRelativeXsec_MT_cs_Name);
   WPlusRelativeXsec_MT_other_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(WPlusRelativeXsec_MT_other_Name);

   WMinusRelativeXsec_MT_ud_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(WMinusRelativeXsec_MT_ud_Name);
   WMinusRelativeXsec_MT_cs_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(WMinusRelativeXsec_MT_cs_Name);
   WMinusRelativeXsec_MT_other_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(WMinusRelativeXsec_MT_other_Name);

   WPlusAFC_MT_ud_Residual_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(WPlusAFC_MT_ud_Residual_Name);
   WPlusAFC_MT_cs_Residual_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(WPlusAFC_MT_cs_Residual_Name);

   WMinusAFC_MT_ud_Residual_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(WMinusAFC_MT_ud_Residual_Name);
   WMinusAFC_MT_cs_Residual_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(WMinusAFC_MT_cs_Residual_Name);

   WPlusAFC_MT_other_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(WPlusAFC_MT_other_Name);
   WMinusAFC_MT_other_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(WMinusAFC_MT_other_Name);
*/

   RelativeXsec_uu_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(RelativeXsec_uu_Name);
   RelativeXsec_dd_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(RelativeXsec_dd_Name);
   RelativeXsec_ss_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(RelativeXsec_ss_Name);
   RelativeXsec_other_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(RelativeXsec_other_Name);

   PositiveAFC_uu_Residual_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(PositiveAFC_uu_Residual_Name);
   NegativeAFC_uu_Residual_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(NegativeAFC_uu_Residual_Name);
   PositiveAFC_dd_Residual_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(PositiveAFC_dd_Residual_Name);
   NegativeAFC_dd_Residual_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(NegativeAFC_dd_Residual_Name);
   PositiveAFC_ss_Residual_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(PositiveAFC_ss_Residual_Name);
   NegativeAFC_ss_Residual_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(NegativeAFC_ss_Residual_Name);
   PositiveAFC_other_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(PositiveAFC_other_Name);
   NegativeAFC_other_Ensemble[(vector<int>{i})] = (TH1D *)file->Get(NegativeAFC_other_Name);

   if(i % 10 == 0) cout<<"No."<<i<<" Theory finished."<<endl;
 }
/*
 global_WPlusRelativeXsec_MT_ud_Ensemble = &WPlusRelativeXsec_MT_ud_Ensemble;
 global_WPlusRelativeXsec_MT_cs_Ensemble = &WPlusRelativeXsec_MT_cs_Ensemble;
 global_WPlusRelativeXsec_MT_other_Ensemble = &WPlusRelativeXsec_MT_other_Ensemble;

 global_WMinusRelativeXsec_MT_ud_Ensemble = &WMinusRelativeXsec_MT_ud_Ensemble;
 global_WMinusRelativeXsec_MT_cs_Ensemble = &WMinusRelativeXsec_MT_cs_Ensemble;
 global_WMinusRelativeXsec_MT_other_Ensemble = &WMinusRelativeXsec_MT_other_Ensemble;

 global_WPlusAFC_MT_ud_Residual_Ensemble = &WPlusAFC_MT_ud_Residual_Ensemble;
 global_WPlusAFC_MT_cs_Residual_Ensemble = &WPlusAFC_MT_cs_Residual_Ensemble;

 global_WMinusAFC_MT_ud_Residual_Ensemble = &WMinusAFC_MT_ud_Residual_Ensemble;
 global_WMinusAFC_MT_cs_Residual_Ensemble = &WMinusAFC_MT_cs_Residual_Ensemble;

 global_WPlusAFC_MT_other_Ensemble = &WPlusAFC_MT_other_Ensemble;
 global_WMinusAFC_MT_other_Ensemble = &WMinusAFC_MT_other_Ensemble;
*/

 global_RelativeXsec_uu_Ensemble = &RelativeXsec_uu_Ensemble;
 global_RelativeXsec_dd_Ensemble = &RelativeXsec_dd_Ensemble;
 global_RelativeXsec_ss_Ensemble = &RelativeXsec_ss_Ensemble;
 global_RelativeXsec_other_Ensemble = &RelativeXsec_other_Ensemble;

 global_PositiveAFC_uu_Residual_Ensemble = &PositiveAFC_uu_Residual_Ensemble;
 global_NegativeAFC_uu_Residual_Ensemble = &NegativeAFC_uu_Residual_Ensemble;
 global_PositiveAFC_dd_Residual_Ensemble = &PositiveAFC_dd_Residual_Ensemble;
 global_NegativeAFC_dd_Residual_Ensemble = &NegativeAFC_dd_Residual_Ensemble;
 global_PositiveAFC_ss_Residual_Ensemble = &PositiveAFC_ss_Residual_Ensemble;
 global_NegativeAFC_ss_Residual_Ensemble = &NegativeAFC_ss_Residual_Ensemble;
 global_PositiveAFC_other_Ensemble = &PositiveAFC_other_Ensemble;
 global_NegativeAFC_other_Ensemble = &NegativeAFC_other_Ensemble;

 cout<<"Initialize theory finished."<<endl;
}

void StrangeAsymmetry::InitialResult()
{
 for(int i = 0; i < rootNames.size(); i++){
   writefile->cd();
/*
   Result_WPlusXsecStrength_ud[(vector<int>{i})] = new TH1D((TString)"Result_WPlusXsecStrength_ud_PDF" + (int)i, (TString)"Result_WPlusXsecStrength_ud_PDF" + (int)i, 1, 0, 1);
   Result_WPlusXsecStrength_cs[(vector<int>{i})] = new TH1D((TString)"Result_WPlusXsecStrength_cs_PDF" + (int)i, (TString)"Result_WPlusXsecStrength_cs_PDF" + (int)i, 1, 0, 1);
   Result_WPlusAFC_MT_ud_Average[(vector<int>{i})] = new TH1D((TString)"Result_WPlusAFC_MT_ud_Average_PDF" + (int)i, (TString)"Result_WPlusAFC_MT_ud_Average_PDF" + (int)i, 1, 0, 1);
   Result_WPlusAFC_MT_cs_Average[(vector<int>{i})] = new TH1D((TString)"Result_WPlusAFC_MT_cs_Average_PDF" + (int)i, (TString)"Result_WPlusAFC_MT_cs_Average_PDF" + (int)i, 1, 0, 1);
   Result_WMinusXsecStrength_ud[(vector<int>{i})] = new TH1D((TString)"Result_WMinusXsecStrength_ud_PDF" + (int)i, (TString)"Result_WMinusXsecStrength_ud_PDF" + (int)i, 1, 0, 1);
   Result_WMinusXsecStrength_cs[(vector<int>{i})] = new TH1D((TString)"Result_WMinusXsecStrength_cs_PDF" + (int)i, (TString)"Result_WMinusXsecStrength_cs_PDF" + (int)i, 1, 0, 1);
   Result_WMinusAFC_MT_ud_Average[(vector<int>{i})] = new TH1D((TString)"Result_WMinusAFC_MT_ud_Average_PDF" + (int)i, (TString)"Result_WMinusAFC_MT_ud_Average_PDF" + (int)i, 1, 0, 1);
   Result_WMinusAFC_MT_cs_Average[(vector<int>{i})] = new TH1D((TString)"Result_WMinusAFC_MT_cs_Average_PDF" + (int)i, (TString)"Result_WMinusAFC_MT_cs_Average_PDF" + (int)i, 1, 0, 1);

   Result_WPlusAFC_MT[(vector<int>{i})] = (TH1D *)Data_WPlusAFC_MT->Clone((TString)"Result_WPlusAFC_MT_PDF" + (int)i);
   Result_WMinusAFC_MT[(vector<int>{i})] = (TH1D *)Data_WMinusAFC_MT->Clone((TString)"Result_WMinusAFC_MT_PDF" + (int)i);
*/

   Result_XsecStrength_uu[(vector<int>{i})] = new TH1D((TString)"Result_XsecStrength_uu_PDF" + (int)i, (TString)"Result_XsecStrength_uu_PDF" + (int)i, 1, 0, 1);
   Result_XsecStrength_dd[(vector<int>{i})] = new TH1D((TString)"Result_XsecStrength_dd_PDF" + (int)i, (TString)"Result_XsecStrength_dd_PDF" + (int)i, 1, 0, 1);
   Result_XsecStrength_ss[(vector<int>{i})] = new TH1D((TString)"Result_XsecStrength_ss_PDF" + (int)i, (TString)"Result_XsecStrength_ss_PDF" + (int)i, 1, 0, 1);

   Result_PositiveAFC_uu_Average[(vector<int>{i})] = new TH1D((TString)"Result_PositiveAFC_uu_Average_PDF" + (int)i, (TString)"Result_PositiveAFC_uu_Average_PDF" + (int)i, 1, 0, 1);
   Result_NegativeAFC_uu_Average[(vector<int>{i})] = new TH1D((TString)"Result_NegativeAFC_uu_Average_PDF" + (int)i, (TString)"Result_NegativeAFC_uu_Average_PDF" + (int)i, 1, 0, 1);
   Result_PositiveAFC_dd_Average[(vector<int>{i})] = new TH1D((TString)"Result_PositiveAFC_dd_Average_PDF" + (int)i, (TString)"Result_PositiveAFC_dd_Average_PDF" + (int)i, 1, 0, 1);
   Result_NegativeAFC_dd_Average[(vector<int>{i})] = new TH1D((TString)"Result_NegativeAFC_dd_Average_PDF" + (int)i, (TString)"Result_NegativeAFC_dd_Average_PDF" + (int)i, 1, 0, 1);
   Result_PositiveAFC_ss_Average[(vector<int>{i})] = new TH1D((TString)"Result_PositiveAFC_ss_Average_PDF" + (int)i, (TString)"Result_PositiveAFC_ss_Average_PDF" + (int)i, 1, 0, 1);
   Result_NegativeAFC_ss_Average[(vector<int>{i})] = new TH1D((TString)"Result_NegativeAFC_ss_Average_PDF" + (int)i, (TString)"Result_NegativeAFC_ss_Average_PDF" + (int)i, 1, 0, 1);

   Result_PositiveAFC[(vector<int>{i})] = (TH1D *)Data_PositiveAFC->Clone((TString)"Result_PositiveAFC_PDF" + (int)i);
   Result_NegativeAFC[(vector<int>{i})] = (TH1D *)Data_NegativeAFC->Clone((TString)"Result_NegativeAFC_PDF" + (int)i);
 }

}

void StrangeAsymmetry::Fitting(int iPDF)
{
 myMinuit = new TMinuitHelper(8);
 if(onlyCentral) iPDF = 0;
 global_iPDF_as = iPDF;
 myMinuit->SetFCN(WStrangeAsymmetryFitting);

 myMinuit->Input(0, "WPlusXsecStrength_ud", 1.0, 0.0, 0.9, 1.1);
 myMinuit->Input(1, "WPlusXsecStrength_cs", 1.0, 0.0, 0.9, 1.1);
 myMinuit->Input(2, "WPlusAFC_MT_ud_Average", 0.6, 0.1, 0.5, 1.0);
 myMinuit->Input(3, "WPlusAFC_MT_cs_Average", 0.6, 0.1, 0.5, 1.0);
 myMinuit->Input(4, "WMinusXsecStrength_ud", 1.0, 0.0, 0.9, 1.1);
 myMinuit->Input(5, "WMinusXsecStrength_cs", 1.0, 0.0, 0.9, 1.1);
 myMinuit->Input(6, "WMinusAFC_MT_ud_Average", 0.6, 0.1, 0.5, 1.0);
 myMinuit->Input(7, "WMinusAFC_MT_cs_Average", 0.6, 0.1, 0.5, 1.0);

 myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
 myMinuit->Exec("MIGRAD", 100000, 0.001);
 double* SPar = new double[8];
 double* SParError = new double[8];
 myMinuit->GetParametersAndError(SPar, SParError);
 cout<<"Fitted WPlusXsecStrength_ud: "<<SPar[0]<<" Error: "<<SParError[0]<<" Delta: "<<SPar[0] - 1.0<<endl;
 cout<<"Fitted WPlusXsecStrength_cs: "<<SPar[1]<<" Error: "<<SParError[1]<<" Delta: "<<SPar[1] - 1.0<<endl;
 cout<<"Fitted WPlusAFC_MT_ud_Average: "<<SPar[2]<<" Error: "<<SParError[2]<<" Delta: "<<SPar[2] - Data_WPlusAFC_MT_ud_Average->GetBinContent(1)<<" Data: "<<Data_WPlusAFC_MT_ud_Average->GetBinContent(1)<<endl;
 cout<<"Fitted WPlusAFC_MT_cs_Average: "<<SPar[3]<<" Error: "<<SParError[3]<<" Delta: "<<SPar[3] - Data_WPlusAFC_MT_cs_Average->GetBinContent(1)<<" Data: "<<Data_WPlusAFC_MT_cs_Average->GetBinContent(1)<<endl;
 cout<<"Fitted WMinusXsecStrength_ud: "<<SPar[4]<<" Error: "<<SParError[4]<<" Delta: "<<SPar[4] - 1.0<<endl;
 cout<<"Fitted WMinusXsecStrength_cs: "<<SPar[5]<<" Error: "<<SParError[5]<<" Delta: "<<SPar[5] - 1.0<<endl;
 cout<<"Fitted WMinusAFC_MT_ud_Average: "<<SPar[6]<<" Error: "<<SParError[6]<<" Delta: "<<SPar[6] - Data_WMinusAFC_MT_ud_Average->GetBinContent(1)<<" Data: "<<Data_WMinusAFC_MT_ud_Average->GetBinContent(1)<<endl;
 cout<<"Fitted WMinusAFC_MT_cs_Average: "<<SPar[7]<<" Error: "<<SParError[7]<<" Delta: "<<SPar[7] - Data_WMinusAFC_MT_cs_Average->GetBinContent(1)<<" Data: "<<Data_WMinusAFC_MT_cs_Average->GetBinContent(1)<<endl;

 Result_WPlusXsecStrength_ud[(vector<int>{iPDF})]->SetBinContent(1, SPar[0]);
 Result_WPlusXsecStrength_cs[(vector<int>{iPDF})]->SetBinContent(1, SPar[1]);
 Result_WPlusAFC_MT_ud_Average[(vector<int>{iPDF})]->SetBinContent(1, SPar[2]);
 Result_WPlusAFC_MT_cs_Average[(vector<int>{iPDF})]->SetBinContent(1, SPar[3]);
 Result_WMinusXsecStrength_ud[(vector<int>{iPDF})]->SetBinContent(1, SPar[4]);
 Result_WMinusXsecStrength_cs[(vector<int>{iPDF})]->SetBinContent(1, SPar[5]);
 Result_WMinusAFC_MT_ud_Average[(vector<int>{iPDF})]->SetBinContent(1, SPar[6]);
 Result_WMinusAFC_MT_cs_Average[(vector<int>{iPDF})]->SetBinContent(1, SPar[7]);

 delete myMinuit;

 MinChi2_as = 100000.0;

}

void StrangeAsymmetry::FittingZ(int iPDF)
{
 myMinuit = new TMinuitHelper(9);
 if(onlyCentral) iPDF = 0;
 global_iPDF_as = iPDF;
 myMinuit->SetFCN(ZStrangeAsymmetryFitting);

 double PositiveAFC_uu_InitValue = 0.6;

 myMinuit->Input(0, "XsecStrength_uu", 1.0, 1.0, 0.9, 1.1);
 myMinuit->Input(1, "XsecStrength_dd", 1.0, 1.0, 0.9, 1.1);
 myMinuit->Input(2, "XsecStrength_ss", 1.0, 1.0, 0.9, 1.1);
 myMinuit->Input(3, "PositiveAFC_uu_Average", 0.6, 0.1, 0.5, 1.0);
 myMinuit->Input(4, "PositiveAFC_dd_Average", 0.6, 0.1, 0.5, 1.0);
 myMinuit->Input(5, "PositiveAFC_ss_Average", 0.6, 0.1, 0.5, 1.0);
 myMinuit->Input(6, "NegativeAFC_uu_Average", 0.6, 0.1, 0.5, 1.0);
 myMinuit->Input(7, "NegativeAFC_dd_Average", 0.6, 0.1, 0.5, 1.0);
 myMinuit->Input(8, "NegativeAFC_ss_Average", 0.6, 0.1, 0.5, 1.0);

 myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
 myMinuit->Exec("MIGRAD", 100000, 0.001);
 double* SPar = new double[9];
 double* SParError = new double[9];
 myMinuit->GetParametersAndError(SPar, SParError);
 cout<<"Fitted XsecStrength_uu: "<<SPar[0]<<" Error: "<<SParError[0]<<" Delta: "<<SPar[0] - 1.0<<endl;
 cout<<"Fitted XsecStrength_dd: "<<SPar[1]<<" Error: "<<SParError[1]<<" Delta: "<<SPar[1] - 1.0<<endl;
 cout<<"Fitted XsecStrength_ss: "<<SPar[2]<<" Error: "<<SParError[2]<<" Delta: "<<SPar[2] - 1.0<<endl;

 cout<<"Fitted PositiveAFC_uu_Average: "<<SPar[3]<<" Error: "<<SParError[3]<<" Delta: "<<SPar[3] - Data_PositiveAFC_uu_Average->GetBinContent(1)<<" Data: "<<Data_PositiveAFC_uu_Average->GetBinContent(1)<<endl;
 cout<<"Fitted PositiveAFC_dd_Average: "<<SPar[4]<<" Error: "<<SParError[4]<<" Delta: "<<SPar[4] - Data_PositiveAFC_dd_Average->GetBinContent(1)<<" Data: "<<Data_PositiveAFC_dd_Average->GetBinContent(1)<<endl;
 cout<<"Fitted PositiveAFC_ss_Average: "<<SPar[5]<<" Error: "<<SParError[5]<<" Delta: "<<SPar[5] - Data_PositiveAFC_ss_Average->GetBinContent(1)<<" Data: "<<Data_PositiveAFC_ss_Average->GetBinContent(1)<<endl;

 cout<<"Fitted NegativeAFC_uu_Average: "<<SPar[6]<<" Error: "<<SParError[6]<<" Delta: "<<SPar[6] - Data_NegativeAFC_uu_Average->GetBinContent(1)<<" Data: "<<Data_NegativeAFC_uu_Average->GetBinContent(1)<<endl;
 cout<<"Fitted NegativeAFC_dd_Average: "<<SPar[7]<<" Error: "<<SParError[7]<<" Delta: "<<SPar[7] - Data_NegativeAFC_dd_Average->GetBinContent(1)<<" Data: "<<Data_NegativeAFC_dd_Average->GetBinContent(1)<<endl;
 cout<<"Fitted NegativeAFC_ss_Average: "<<SPar[8]<<" Error: "<<SParError[8]<<" Delta: "<<SPar[8] - Data_NegativeAFC_ss_Average->GetBinContent(1)<<" Data: "<<Data_NegativeAFC_ss_Average->GetBinContent(1)<<endl;

 Result_XsecStrength_uu[(vector<int>{iPDF})]->SetBinContent(1, SPar[0]);
 Result_XsecStrength_dd[(vector<int>{iPDF})]->SetBinContent(1, SPar[1]);
 Result_XsecStrength_ss[(vector<int>{iPDF})]->SetBinContent(1, SPar[2]);
 Result_PositiveAFC_uu_Average[(vector<int>{iPDF})]->SetBinContent(1, SPar[3]);
 Result_PositiveAFC_dd_Average[(vector<int>{iPDF})]->SetBinContent(1, SPar[4]);
 Result_PositiveAFC_ss_Average[(vector<int>{iPDF})]->SetBinContent(1, SPar[5]);
 Result_NegativeAFC_uu_Average[(vector<int>{iPDF})]->SetBinContent(1, SPar[6]);
 Result_NegativeAFC_dd_Average[(vector<int>{iPDF})]->SetBinContent(1, SPar[7]);
 Result_NegativeAFC_ss_Average[(vector<int>{iPDF})]->SetBinContent(1, SPar[8]);

 delete myMinuit;

 MinChi2_as = 100000.0;

}

