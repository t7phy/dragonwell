#include "FileForEPUMP/FileForEPUMP.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
 double xbins[7] = {75, 80, 85, 90, 95, 100, 105};
 double xbinsCF[5] = {82, 87, 92, 97, 102};

 TString ZeeCCName = "/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/Data_FSROff/BayesUnfold_CCZee.root";
 TString ZmmCCName = "/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/Data_FSROff/BayesUnfold_Zmm.root";
 TString ZeeCFName = "/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/Data_FSROff/BayesUnfold_CFZee.root";
 TFile* DataFile = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/Data_FSROff/BayesUnfold_CCZee.root");
 TFile* DataFileCF = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/Data_FSROff/BayesUnfold_CFZee.root");
 TFile* DataFileZmm = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/Data_FSROff/BayesUnfold_Zmm.root");
 TFile* TheoryFile[100];
 TFile* TheoryCorrelationFile;

 TH1D* DataPlot;
 TH1D* DataPlotCF;
 TH1D* DataPlotZmm;
 TH1D* DataError[100];
 TH1D* DataErrorCF[100];
 TH1D* DataErrorZmm[100];
 TH1D* MCTruthPlot;
 TH1D* MCRecoPlot;
 TH1D* MCTruthPlotCF;
 TH1D* MCRecoPlotCF;
 TH1D* MCTruthPlotZmm;
 TH1D* MCRecoPlotZmm;
 TH2D* DataCorrelation[100];
 TH2D* DataCorrelationCF[100];
 TH2D* DataCorrelationZmm[100];
 TH2D* DataCovariance[100];
 TH2D* TotalDataCovariance;

 TH1D* TheoryFZmass[100];
 TH1D* TheoryBZmass[100];
 TH1D* TheoryPlot[100];
 TH1D* TheoryError[100];
 TH2D* TheoryCovariance;
 TH2D* TotalTheoryCovariance[100];

 TFile* TemplateFile[100];
 TH1D* TheoryTemplate[100];
 TH1D* TemplateFZmass[100];
 TH1D* TemplateBZmass[100];
 vector<TH1D *> v_DataSysErr;
 vector<TH1D *> v_DataSysErrZmm;
 vector<TH1D *> v_TheoryPlotList;
 vector<TH1D *> v_TheoryTemplate;

 TH1D* TemplateFZmassZPole[100];
 TH1D* TemplateBZmassZPole[100];
 TH1D* TheoryTemplateZPole[100];
 vector<TH1D *> v_TheoryTemplateZPole;

//      Data       //
 DataPlot = (TH1D *)DataFile->Get("Unfolding_AFB_Final");
 MCTruthPlot = (TH1D *)DataFile->Get("MCTrue_AFB");
 MCRecoPlot = (TH1D *)DataFile->Get("MCReco_AFB");
 DataCorrelation[1] = (TH2D *)DataFile->Get("CorrelationMatrix_MCStat");
 DataCorrelation[2] = (TH2D *)DataFile->Get("CorrelationMatrix_DataStat");
 DataError[1] = (TH1D *)DataFile->Get("Unfolding_DataStatErr");
 DataError[2] = (TH1D *)DataFile->Get("Unfolding_MCStatErr");

 DataError[3] = (TH1D *)DataFile->Get("Unfolding_MethodErr");
 DataError[4] = (TH1D *)DataFile->Get("Unfolding_SystematicErr");
 DataError[5] = (TH1D *)DataFile->Get("Unfolding_IDErr");
 DataError[6] = (TH1D *)DataFile->Get("Unfolding_ISOErr");
 DataError[7] = (TH1D *)DataFile->Get("Unfolding_RECOErr");
 DataError[8] = (TH1D *)DataFile->Get("Unfolding_TRIGErr");
 DataError[9] = (TH1D *)DataFile->Get("Unfolding_ScaleCalibrationErr");
 DataError[10] = (TH1D *)DataFile->Get("Unfolding_SmearCalibrationErr");
 for(int i = 5; i <= 10; i++){
   v_DataSysErr.push_back(DataError[i]);
 }

 DataPlotZmm = (TH1D *)DataFileZmm->Get("Unfolding_AFB_Final");
 MCTruthPlotZmm = (TH1D *)DataFileZmm->Get("MCTrue_AFB");
 MCRecoPlotZmm = (TH1D *)DataFileZmm->Get("MCReco_AFB");
 DataCorrelationZmm[1] = (TH2D *)DataFileZmm->Get("CorrelationMatrix_MCStat");
 DataCorrelationZmm[2] = (TH2D *)DataFileZmm->Get("CorrelationMatrix_DataStat");
 DataErrorZmm[1] = (TH1D *)DataFileZmm->Get("Unfolding_DataStatErr");
 DataErrorZmm[2] = (TH1D *)DataFileZmm->Get("Unfolding_MCStatErr");

 DataErrorZmm[3] = (TH1D *)DataFileZmm->Get("Unfolding_ISOSTATErr");
 DataErrorZmm[4] = (TH1D *)DataFileZmm->Get("Unfolding_ISOSYSErr");
 DataErrorZmm[5] = (TH1D *)DataFileZmm->Get("Unfolding_TTVASTATErr");
 DataErrorZmm[6] = (TH1D *)DataFileZmm->Get("Unfolding_TTVASYSErr");
 DataErrorZmm[7] = (TH1D *)DataFileZmm->Get("Unfolding_RECOSTATErr");
 DataErrorZmm[8] = (TH1D *)DataFileZmm->Get("Unfolding_RECOSYSErr");
 DataErrorZmm[9] = (TH1D *)DataFileZmm->Get("Unfolding_TRIGSTATErr");
 DataErrorZmm[10] = (TH1D *)DataFileZmm->Get("Unfolding_TRIGSYSErr");
 DataErrorZmm[11] = (TH1D *)DataFileZmm->Get("Unfolding_ScaleCalibrationErr");
 DataErrorZmm[12] = (TH1D *)DataFileZmm->Get("Unfolding_SmearCalibrationErr");
 for(int i = 3; i <= 12; i++){
   v_DataSysErrZmm.push_back(DataErrorZmm[i]);
 }

 DataPlotCF = (TH1D *)DataFileCF->Get("Unfolding_AFB_Final");
 MCTruthPlotCF = (TH1D *)DataFileCF->Get("MCTrue_AFB");
 MCRecoPlotCF = (TH1D *)DataFileCF->Get("MCReco_AFB");
 DataCorrelationCF[1] = (TH2D *)DataFileCF->Get("CorrelationMatrix_MCStat");
 DataCorrelationCF[2] = (TH2D *)DataFileCF->Get("CorrelationMatrix_DataStat");
 DataErrorCF[1] = (TH1D *)DataFileCF->Get("Unfolding_DataStatErr");
 DataErrorCF[2] = (TH1D *)DataFileCF->Get("Unfolding_MCStatErr");

 DataErrorCF[3] = (TH1D *)DataFileCF->Get("Unfolding_MethodErr");
 DataErrorCF[4] = (TH1D *)DataFileCF->Get("Unfolding_SystematicErr");
 DataErrorCF[5] = (TH1D *)DataFileCF->Get("Unfolding_IDErr");
 DataErrorCF[6] = (TH1D *)DataFileCF->Get("Unfolding_ISOErr");
 DataErrorCF[7] = (TH1D *)DataFileCF->Get("Unfolding_RECOErr");
 DataErrorCF[8] = (TH1D *)DataFileCF->Get("Unfolding_TRIGErr");
 DataErrorCF[9] = (TH1D *)DataFileCF->Get("Unfolding_ScaleCalibrationErr");
 DataErrorCF[10] = (TH1D *)DataFileCF->Get("Unfolding_SmearCalibrationErr");



 double* mySysErrZee;
 mySysErrZee = new double[100];
 double* myStaErrZee;
 myStaErrZee = new double[100];

 double* mySysErrCF;
 mySysErrCF = new double[100];
 double* myStaErrCF;
 myStaErrCF = new double[100];

 double* mySysErrZmm;
 mySysErrZmm = new double[100];
 double* myStaErrZmm;
 myStaErrZmm = new double[100];

 for(int ibin = 0; ibin < DataError[5]->GetNbinsX(); ibin++){
   for(int i = 5; i <= 10; i++){
     mySysErrZee[ibin] += DataError[i]->GetBinContent(ibin + 1) * DataError[i]->GetBinContent(ibin + 1);
   }
   mySysErrZee[ibin] = sqrt(mySysErrZee[ibin]);
   cout<<"Zee Systematic Error: "<<mySysErrZee[ibin]<<endl;
 }
 cout<<endl;

 for(int ibin = 0; ibin < DataError[1]->GetNbinsX(); ibin++){
   for(int i = 1; i <= 2; i++){
     myStaErrZee[ibin] += DataError[i]->GetBinContent(ibin + 1) * DataError[i]->GetBinContent(ibin + 1);
   }
   myStaErrZee[ibin] = sqrt(myStaErrZee[ibin]);
   cout<<"Zee Statistical Error: "<<myStaErrZee[ibin]<<endl;
 }
 cout<<endl;

 for(int ibin = 0; ibin < DataErrorCF[5]->GetNbinsX(); ibin++){
   for(int i = 5; i <= 10; i++){
     mySysErrCF[ibin] += DataErrorCF[i]->GetBinContent(ibin + 1) * DataErrorCF[i]->GetBinContent(ibin + 1);
   }
   mySysErrCF[ibin] = sqrt(mySysErrCF[ibin]);
   cout<<"Zee CF Systematic Error: "<<mySysErrCF[ibin]<<endl;
 }
 cout<<endl;
 
 for(int ibin = 0; ibin < DataErrorCF[1]->GetNbinsX(); ibin++){
   for(int i = 1; i <= 2; i++){
     myStaErrCF[ibin] += DataErrorCF[i]->GetBinContent(ibin + 1) * DataErrorCF[i]->GetBinContent(ibin + 1);
   }
   myStaErrCF[ibin] = sqrt(myStaErrCF[ibin]);
   cout<<"Zee CF Statistical Error: "<<myStaErrCF[ibin]<<endl;
 }
 cout<<endl;

 for(int ibin = 0; ibin < DataErrorZmm[3]->GetNbinsX(); ibin++){
   for(int i = 3; i <= 12; i++){
     mySysErrZmm[ibin] += DataErrorZmm[i]->GetBinContent(ibin + 1) * DataErrorZmm[i]->GetBinContent(ibin + 1);
   }
   mySysErrZmm[ibin] = sqrt(mySysErrZmm[ibin]);
   cout<<"Zmm Systematic Error: "<<mySysErrZmm[ibin]<<endl;
 }
 cout<<endl;

 for(int ibin = 0; ibin < DataErrorZmm[1]->GetNbinsX(); ibin++){
   for(int i = 1; i <= 2; i++){
     myStaErrZmm[ibin] += DataErrorZmm[i]->GetBinContent(ibin + 1) * DataErrorZmm[i]->GetBinContent(ibin + 1);
   }
   myStaErrZmm[ibin] = sqrt(myStaErrZmm[ibin]);
   cout<<"Zmm Statistical Error: "<<myStaErrZmm[ibin]<<endl;
 }
 cout<<endl;

 TString EtaRegion = "CC";

 vector<TString> rootNames;
 TString rootName;
 ifstream infile;
  infile.open("theory" + EtaRegion + ".list",ios::in);
 while(infile>>rootName){
  rootNames.push_back(rootName);
 }

 vector<TString> rootNamesCF;
 TString rootNameCF;
 ifstream infileCF;
  infileCF.open("theoryCF.list",ios::in);
 while(infileCF>>rootNameCF){
  rootNamesCF.push_back(rootNameCF);
 }

 FileForEPUMP* data[100];
 TString filename = "AFB_CC_Zee";
 data[0] = new FileForEPUMP(filename);
 data[0]->Rebin(xbins, 7);
 data[0]->InputData(ZeeCCName, "Unfolding_AFB_Final", 0); //0 means not rebin
 data[0]->InputTheory(rootNames, "FZmass_" + EtaRegion, "BZmass_" + EtaRegion);
 data[0]->InputStaErr(myStaErrZee);
 data[0]->InputSysErr(mySysErrZee);
 data[0]->writedata();
 data[0]->writetheory();

 filename = "AFB_CC_Zmm";
 data[1] = new FileForEPUMP(filename);
 data[1]->Rebin(xbins, 7);
 data[1]->InputData(ZmmCCName, "Unfolding_AFB_Final", 0); //0 means not rebin
 data[1]->InputTheory(rootNames, "FZmass_" + EtaRegion, "BZmass_" + EtaRegion);
 data[1]->InputStaErr(myStaErrZmm);
 data[1]->InputSysErr(mySysErrZmm);
 data[1]->writedata();
 data[1]->writetheory();

 filename = "AFB_CF_Zee";
 data[2] = new FileForEPUMP(filename);
 data[2]->Rebin(xbinsCF, 5);
 data[2]->InputData(ZeeCCName, "Unfolding_AFB_Final", 0); //0 means not rebin
 data[2]->InputTheory(rootNamesCF, "FZmass_CF", "BZmass_CF");
 data[2]->InputStaErr(myStaErrCF);
 data[2]->InputSysErr(mySysErrCF);
 data[2]->writedata();
 data[2]->writetheory();

 return 1;
}
