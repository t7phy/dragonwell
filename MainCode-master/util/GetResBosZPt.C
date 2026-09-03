#include <iostream>
#include "ReadInRoot/ResBosZPt.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "Analysis/HistsResBos.h"

using namespace std;

int main(int argc, char** argv)
{
// ResBosZPt* Run = new ResBosZPt();
// HistsResBos* myhists = new HistsResBos();
// myhists->openFile("save.root");
// myhists->bookHists(1);

// Run->LinkHist(myhists);

// Run->openFile("ZPt_data.txt");
// Run->WriteIn(myhists->v_ZPt.at(0));

// myhists->MergeHists(1);
// myhists->saveHists();
// delete Run;
// cout<<"Master thread is end."<<endl;
// double rangeZPt[21] = {0.0, 2, 4, 6, 8, 10, 13, 16, 20, 25, 30, 37, 45, 55, 65, 75, 85, 105, 150, 200, 900};
 double rangeZPt[9] = {0.0, 2, 4, 6, 8, 10, 13, 16, 20};
 double rangeY[7] = {0.0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4};

 TFile *writefile = new TFile("ATLASRapidityDepData.root", "RECREATE");
 TH2D *Data = new TH2D("YDepZPt", "YDepZPt", 8, rangeZPt, 6, rangeY);
 TH1D *ATLASy1 = new TH1D("ATLASy1", "ATLASy1", 8, rangeZPt);
 TH1D *ATLASy2 = new TH1D("ATLASy2", "ATLASy2", 8, rangeZPt);
 TH1D *ATLASy3 = new TH1D("ATLASy3", "ATLASy3", 8, rangeZPt);
 TH1D *ATLASy4 = new TH1D("ATLASy4", "ATLASy4", 8, rangeZPt);
 TH1D *ATLASy5 = new TH1D("ATLASy5", "ATLASy5", 8, rangeZPt);
 TH1D *ATLASy6 = new TH1D("ATLASy6", "ATLASy6", 8, rangeZPt);
 FileForEPUMP *Tabley1 = new FileForEPUMP("ATLASy1");
 FileForEPUMP *Tabley2 = new FileForEPUMP("ATLASy2");
 FileForEPUMP *Tabley3 = new FileForEPUMP("ATLASy3");
 FileForEPUMP *Tabley4 = new FileForEPUMP("ATLASy4");
 FileForEPUMP *Tabley5 = new FileForEPUMP("ATLASy5");
 FileForEPUMP *Tabley6 = new FileForEPUMP("ATLASy6");
 vector<double> DataPoints;
 vector<double> DataErrors;
 vector<double> StaErrors;
 vector<double> UnCorrErrors;
 vector<double> CorrErrors;
 vector<double> LumiErrors;

 ResBosZPt* run;
 run = new ResBosZPt();
 run->openFile("/Data/yfu/UIDisplay/YDep_pTData/y_0.4.csv");
 run->InputDataFile("/Data/yfu/UIDisplay/HEPData-ins1408516-v1-csv/MC_results_y1.root", "/Data/yfu/UIDisplay/HEPData-ins1408516-v1-csv/MC_results_y2.root");
 run->GetEfficiency("CutEff_ZPt_y1");
 run->GetKFactor("ZPt_y1_Total");
 run->GetTable(18, "2.000E-01");
 run->GetDataAndErr(DataPoints, DataErrors);
 run->GetFullTable(DataPoints, StaErrors, UnCorrErrors, CorrErrors);
 for(int ibinx = 1; ibinx <= Data->GetNbinsX(); ibinx++){
   Data->SetBinContent(ibinx, 1, DataPoints.at(ibinx - 1));
   Data->SetBinError(ibinx, 1, DataErrors.at(ibinx - 1));
   ATLASy1->SetBinContent(ibinx, DataPoints.at(ibinx - 1));
   ATLASy1->SetBinError(ibinx, StaErrors.at(ibinx - 1));
   LumiErrors.push_back(2.8);
 }
 Tabley1->InputData(ATLASy1);
 Tabley1->InputSysErr(UnCorrErrors);
 Tabley1->InputCorrSysErr(CorrErrors, "CorrErr");
 Tabley1->InputCorrSysErr(LumiErrors, "LumiErr");
 Tabley1->writedata();
 DataPoints.clear();
 DataErrors.clear();
 StaErrors.clear();
 UnCorrErrors.clear();
 CorrErrors.clear();
 LumiErrors.clear();
 delete run;
 cout<<endl;

 run = new ResBosZPt();
 run->openFile("/Data/yfu/UIDisplay/YDep_pTData/y_0.4_0.8.csv");
 run->InputDataFile("/Data/yfu/UIDisplay/HEPData-ins1408516-v1-csv/MC_results_y1.root", "/Data/yfu/UIDisplay/HEPData-ins1408516-v1-csv/MC_results_y2.root");
 run->GetEfficiency("CutEff_ZPt_y2");
 run->GetKFactor("ZPt_y2_Total");
 run->GetTable(19, "6.000E-01");
 run->GetDataAndErr(DataPoints, DataErrors);
 run->GetFullTable(DataPoints, StaErrors, UnCorrErrors, CorrErrors);
 for(int ibinx = 1; ibinx <= Data->GetNbinsX(); ibinx++){
   Data->SetBinContent(ibinx, 2, DataPoints.at(ibinx - 1));
   Data->SetBinError(ibinx, 2, DataErrors.at(ibinx - 1));
   ATLASy2->SetBinContent(ibinx, DataPoints.at(ibinx - 1));
   ATLASy2->SetBinError(ibinx, StaErrors.at(ibinx - 1));
   LumiErrors.push_back(2.8);
 }
 Tabley2->InputData(ATLASy2);
 Tabley2->InputSysErr(UnCorrErrors);
 Tabley2->InputCorrSysErr(CorrErrors, "CorrErr");
 Tabley2->InputCorrSysErr(LumiErrors, "LumiErr");
 Tabley2->writedata();
 DataPoints.clear();
 DataErrors.clear();
 StaErrors.clear();
 UnCorrErrors.clear();
 CorrErrors.clear();
 LumiErrors.clear();
 delete run;
 cout<<endl;

 run = new ResBosZPt();
 run->openFile("/Data/yfu/UIDisplay/YDep_pTData/y_0.8_1.2.csv");
 run->InputDataFile("/Data/yfu/UIDisplay/HEPData-ins1408516-v1-csv/MC_results_y1.root", "/Data/yfu/UIDisplay/HEPData-ins1408516-v1-csv/MC_results_y2.root");
 run->GetEfficiency("CutEff_ZPt_y3");
 run->GetKFactor("ZPt_y3_Total");
 run->GetTable(20, "1.000E+00");
 run->GetDataAndErr(DataPoints, DataErrors);
 run->GetFullTable(DataPoints, StaErrors, UnCorrErrors, CorrErrors);
 for(int ibinx = 1; ibinx <= Data->GetNbinsX(); ibinx++){
   Data->SetBinContent(ibinx, 3, DataPoints.at(ibinx - 1));
   Data->SetBinError(ibinx, 3, DataErrors.at(ibinx - 1));
   ATLASy3->SetBinContent(ibinx, DataPoints.at(ibinx - 1));
   ATLASy3->SetBinError(ibinx, StaErrors.at(ibinx - 1));
   LumiErrors.push_back(2.8);
 }
 Tabley3->InputData(ATLASy3);
 Tabley3->InputSysErr(UnCorrErrors);
 Tabley3->InputCorrSysErr(CorrErrors, "CorrErr");
 Tabley3->InputCorrSysErr(LumiErrors, "LumiErr");
 Tabley3->writedata();
 DataPoints.clear();
 DataErrors.clear();
 StaErrors.clear();
 UnCorrErrors.clear();
 CorrErrors.clear();
 LumiErrors.clear();
 delete run;
 cout<<endl;

 run = new ResBosZPt();
 run->openFile("/Data/yfu/UIDisplay/YDep_pTData/y_1.2_1.6.csv");
 run->InputDataFile("/Data/yfu/UIDisplay/HEPData-ins1408516-v1-csv/MC_results_y1.root", "/Data/yfu/UIDisplay/HEPData-ins1408516-v1-csv/MC_results_y2.root");
 run->GetEfficiency("CutEff_ZPt_y4");
 run->GetKFactor("ZPt_y4_Total");
 run->GetTable(21, "1.400E+00");
 run->GetDataAndErr(DataPoints, DataErrors);
 run->GetFullTable(DataPoints, StaErrors, UnCorrErrors, CorrErrors);
 for(int ibinx = 1; ibinx <= Data->GetNbinsX(); ibinx++){
   Data->SetBinContent(ibinx, 4, DataPoints.at(ibinx - 1));
   Data->SetBinError(ibinx, 4, DataErrors.at(ibinx - 1));
   ATLASy4->SetBinContent(ibinx, DataPoints.at(ibinx - 1));
   ATLASy4->SetBinError(ibinx, StaErrors.at(ibinx - 1));
   LumiErrors.push_back(2.8);
 }
 Tabley4->InputData(ATLASy4);
 Tabley4->InputSysErr(UnCorrErrors);
 Tabley4->InputCorrSysErr(CorrErrors, "CorrErr");
 Tabley4->InputCorrSysErr(LumiErrors, "LumiErr");
 Tabley4->writedata();
 DataPoints.clear();
 DataErrors.clear();
 StaErrors.clear();
 UnCorrErrors.clear();
 CorrErrors.clear();
 LumiErrors.clear();
 delete run;
 cout<<endl;

 run = new ResBosZPt();
 run->openFile("/Data/yfu/UIDisplay/YDep_pTData/y_1.6_2.0.csv");
 run->InputDataFile("/Data/yfu/UIDisplay/HEPData-ins1408516-v1-csv/MC_results_y1.root", "/Data/yfu/UIDisplay/HEPData-ins1408516-v1-csv/MC_results_y2.root");
 run->GetEfficiency("CutEff_ZPt_y5");
 run->GetKFactor("ZPt_y5_Total");
 run->GetTable(22, "1.800E+00");
 run->GetDataAndErr(DataPoints, DataErrors);
 run->GetFullTable(DataPoints, StaErrors, UnCorrErrors, CorrErrors);
 for(int ibinx = 1; ibinx <= Data->GetNbinsX(); ibinx++){
   Data->SetBinContent(ibinx, 5, DataPoints.at(ibinx - 1));
   Data->SetBinError(ibinx, 5, DataErrors.at(ibinx - 1));
   ATLASy5->SetBinContent(ibinx, DataPoints.at(ibinx - 1));
   ATLASy5->SetBinError(ibinx, StaErrors.at(ibinx - 1));
   LumiErrors.push_back(2.8);
 }
 Tabley5->InputData(ATLASy5);
 Tabley5->InputSysErr(UnCorrErrors);
 Tabley5->InputCorrSysErr(CorrErrors, "CorrErr");
 Tabley5->InputCorrSysErr(LumiErrors, "LumiErr");
 Tabley5->writedata();
 DataPoints.clear();
 DataErrors.clear();
 StaErrors.clear();
 UnCorrErrors.clear();
 CorrErrors.clear();
 LumiErrors.clear();
 delete run;
 cout<<endl;

 run = new ResBosZPt();
 run->openFile("/Data/yfu/UIDisplay/YDep_pTData/y_2.0_2.4.csv");
 run->InputDataFile("/Data/yfu/UIDisplay/HEPData-ins1408516-v1-csv/MC_results_y1.root", "/Data/yfu/UIDisplay/HEPData-ins1408516-v1-csv/MC_results_y2.root");
 run->GetEfficiency("CutEff_ZPt_y6");
 run->GetKFactor("ZPt_y6_Total");
 run->GetTable(23, "2.200E+00");
 run->GetDataAndErr(DataPoints, DataErrors);
 run->GetFullTable(DataPoints, StaErrors, UnCorrErrors, CorrErrors);
 for(int ibinx = 1; ibinx <= Data->GetNbinsX(); ibinx++){
   Data->SetBinContent(ibinx, 6, DataPoints.at(ibinx - 1));
   Data->SetBinError(ibinx, 6, DataErrors.at(ibinx - 1));
   ATLASy6->SetBinContent(ibinx, DataPoints.at(ibinx - 1));
   ATLASy6->SetBinError(ibinx, StaErrors.at(ibinx - 1));
   LumiErrors.push_back(2.8);
 }
 Tabley6->InputData(ATLASy6);
 Tabley6->InputSysErr(UnCorrErrors);
 Tabley6->InputCorrSysErr(CorrErrors, "CorrErr");
 Tabley6->InputCorrSysErr(LumiErrors, "LumiErr");
 Tabley6->writedata();
 DataPoints.clear();
 DataErrors.clear();
 StaErrors.clear();
 UnCorrErrors.clear();
 CorrErrors.clear();
 LumiErrors.clear();
 delete run;
 cout<<endl;

 writefile->cd();
 Data->Write();
 writefile->Close();
 return 1;
}
