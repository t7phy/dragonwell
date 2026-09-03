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
   double xbins1[22] = {60,62,64,66,68,70,72,74,76,78,80,100,102,104,106,108,110,112,114,116,118,120};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 22;
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

 if(iflag == 9){
   double xbins1[9] = {-2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 9;
 }

 if(iflag == 10){
   double xbins1[14] = {-5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 14;
 }
 if(iflag == 11){
   double xbins1[31] = {60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 31;
 }

 return xbins;
}

int main( int argc ,char **argv)
{
 TString EtaRegion = "CC";
 TString Statistic = "500M";
 TString STW = "2324";
// TString rootname = (TString)"/Data/yfu/MainCode/run/stwPDF/PseudoData_0." + STW + (TString)"/MC_results.root";
// TString rootname = "/Data/yfu/MainCode/run/stwPDF/130fb-1_ZTemplate_CF/PseudoData_0.2345/MC_results.root";
// TString rootname = "/Data/yfu/MainCode/run/stwPDF/MMHT_50M_ZTemplate/PseudoData_0.2345/MC_results.root";
// TString rootname = "/Data/yfu/MainCode/run/stwPDF/MMHT_130fb-1_ZTemplate/PseudoData_0.2345/MC_results.root";
// TString rootname = "/Data/yfu/MainCode/run/AFBQuarkExtraction/Pseudodata_0.2315/If1363.01/MC_results.root";
// TString rootname = "/Data/yfu/MainCode/run/AFBQuarkExtraction/If1363.00/MC_results.root";
// TString rootname = "/Data/yfu/MainCode/run/PythiaWW/If1363.00/MC_results.root";
// TString rootname = "/Data/yfu/MainCode/run/ResBosDilution/i2Tn3.00/MC_results.root";
// TString rootname = "/msu/data/t3work5/yfu/MainCode/run/ResBosHighMassZ/i2Tn3.00/MC_results.root";
// TString rootname = "/msu/data/t3work5/yfu/MainCode/run/ResBosHighMassZ/HighMassAFB/CT18As.00/MC_results.root";
// TString rootname = "/msu/data/t3work5/yfu/MainCode/run/ResBosHighMassZ/HighMassAFB/CT18AsLat.00/MC_results.root";

// TString rootname = "/Data/yfu/MainCode/run/ResBosDilution/250M/i2Tn3.00/MC_results.root";
// TString rootname = "/Data/yfu/MainCode/run/ChangeStrangeQuark/MC_results.root";
// TString rootname = "/Data/yfu/MainCode/run/ResBosDilution/FullAFB_RotatedCT18NNLO_LHA.01/MC_results.root";
// TString rootname = "/ustcfs2/yfu/MainCode/run/13TeVWMass/i2Tn3.00/MC_results.root";
// TString rootname = "/msu/data/t3work12/yaofu/MainCode/run/ResBosHighMassZ/Save2025.11.3/i2Tn3.00/MC_results_onlyZ.root";
 TString rootname = "/msu/data/t3work12/yaofu/MainCode/run/ResBosHighMassZ/i2Tn3.00/MC_results.root";
 TString rootnameMSHT20 = "/ustcfs2/yfu/MainCode/run/ResBosHighMassZ/MSHT20.00/MC_results.root";
 TString rootnameNNPDF40 = "/ustcfs2/yfu/MainCode/run/ResBosHighMassZ/NNPDF40.00/MC_results.root";

// TString rootname = "/ustcfs2/yfu/MainCode/run/TryExtendedParameter/i2Tn3.00/MC_results.root";
// TString rootname2324 = "/ustcfs2/yfu/MainCode/run/TryExtendedParameter/STWTemplate/0.2324/MC_results.root";

 vector<TString> rootNames;
 TString rootName;

 ifstream infile;
  infile.open("theory.list",ios::in);
//  infile.open("theoryMSHT.list",ios::in);
//  infile.open("theoryCT18As.list",ios::in);
//  infile.open("theoryCT18AsLat.list",ios::in);
//  infile.open("theory250M.list",ios::in);
 while(infile>>rootName){
   rootNames.push_back(rootName);
 }
 infile.close();

 vector<TString> ExtendedNames;
 infile.open("stw.list", ios::in);
 while(infile>>rootName){
   ExtendedNames.push_back(rootName);
 }
 infile.close();

 FileForEPUMP* data;
 double* xbins;
 int size;

 TString filename = "";

/* filename = "ZMass_FullMass";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZMass_FullMass");
 data->InputTheory(rootNames, "ZMass_FullMass");
 data->writedata();
 data->writetheory();
 delete data;
*/

 filename = "WPlusMTEta_FullEta";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "WPlusMTEta_FullEta_Pseudodata");
 data->Input2DTheory(rootNames, "WPlusMTEta_FullEta_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "WMinusMTEta_FullEta";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "WMinusMTEta_FullEta_Pseudodata");
 data->Input2DTheory(rootNames, "WMinusMTEta_FullEta_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "WPlusMTEta_FullEta_Above100";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "WPlusMTEta_FullEta_Above100_Pseudodata");
 data->Input2DTheory(rootNames, "WPlusMTEta_FullEta_Above100_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "WMinusMTEta_FullEta_Above100";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "WMinusMTEta_FullEta_Above100_Pseudodata");
 data->Input2DTheory(rootNames, "WMinusMTEta_FullEta_Above100_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;


/* TString filename = "3DXSection";
 data[0] = new FileForEPUMP(filename);
 data[0]->Input3DData(rootname, "XSection_M_Y_CosTheta"); //0 means not rebin
 data[0]->Input3DTheory(rootNames, "XSection_M_Y_CosTheta");
 data[0]->write3Ddata();
 data[0]->write3Dtheory();

 xbins = new double[100];
 xbins = DefineBins(size, 3);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 filename = "AFB_Sideband_LHCb";
 data[1] = new FileForEPUMP(filename);
 data[1]->SetSideband();
 data[1]->Rebin(xbins, size);
 data[1]->InputData(rootname, "FZmass_LHCb", "BZmass_LHCb"); //0 means not rebin
 data[1]->InputTheory(rootNames, "FZmass_LHCb", "BZmass_LHCb");
 data[1]->writedata();
 data[1]->writetheory();

 infile.close();
 infile.open("theoryW.list", ios::in);
 vector<TString> rootNamesW;
 while(infile >> rootName){
   rootNamesW.push_back(rootName);
 }
*/
/* STW = "2315";
 rootname = (TString)"/lustre/AtlUser/yfu/MainCode/run/stwPDF/PseudoData_0." + STW + (TString)"/MC_results.root";
 filename = "Wasymmetry_LHCb";
 data[2] = new FileForEPUMP(filename);
 data[2]->Rebin(5);
 data[2]->InputData(rootname, "AntiLeptonEtaAbs_LHCb", "LeptonEtaAbs_LHCb"); //0 means not rebin
 data[2]->InputTheory(rootNamesW, "AntiLeptonEtaAbs_LHCb", "LeptonEtaAbs_LHCb");
 data[2]->GetDataStaError();
 data[2]->writedata();
 data[2]->writetheory();
*/

// TString rootname1 = "/Data/yfu/MainCode/run/stwPDF/PseudoData_0.2315/MC_results.root";
// TString rootname2 = "/Data/yfu/MainCode/run/stwPDF/PseudoData_0.2324/MC_results.root";

// TString rootname1 = "/Data/yfu/MainCode/run/PythiaWW/Pseudodata_0.2315/MC_results.root";

/*
// TString rootname2 = "/Data/yfu/MainCode/run/stwPDF/STWTemplate/0.2324/MC_results.root";
// TString rootname1 = "/lustre/AtlUser/yfu/MainCode/run/stwPDF/WSample/If1363.31/MC_results.root";
// TString rootname2 = "/Data/yfu/MainCode/run/stwPDF/If1363.00/MC_results.root";
 filename = "WoverZ_DiffPDF_LHCb_300fb";
 data[3] = new FileForEPUMP(filename);
// data[3]->Rebin(5);
 data[3]->SpecialStaError(0.66);
 data[3]->InputData(rootname1, rootname2, "AntiLeptonEtaAbs_LHCb", "LeptonEtaAbs_LHCb", "ZRapidity_LHCb");
 data[3]->InputTheory(rootNamesW, rootNames, "AntiLeptonEtaAbs_LHCb", "LeptonEtaAbs_LHCb", "ZRapidity_LHCb");
 data[3]->GetDataStaError();
 data[3]->writedata();
 data[3]->writetheory();

 xbins = new double[100];
 xbins = DefineBins(size, 9);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 filename = "WEtaoverZY_ATLAS_Central";
 data[4] = new FileForEPUMP(filename);
 data[4]->Rebin(xbins, size);
 data[4]->InputData(rootname1, rootname2, "AntiLeptonEta", "LeptonEta", "ZRapidity");
 data[4]->InputTheory(rootNamesW, rootNames, "AntiLeptonEta", "LeptonEta", "ZRapidity");
 data[4]->GetDataStaError();
 data[4]->writedata();
 data[4]->writetheory();
 delete xbins;

 xbins = new double[100];
 xbins = DefineBins(size, 10);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 filename = "WEtaoverZY_ATLAS_Side";
 data[5] = new FileForEPUMP(filename);
 data[5]->Rebin(xbins, size);
 data[5]->RemoveSpecialBins(-2.0, 2.0);
 data[5]->InputData(rootname1, rootname2, "AntiLeptonEta", "LeptonEta", "ZRapidity");
 data[5]->InputTheory(rootNamesW, rootNames, "AntiLeptonEta", "LeptonEta", "ZRapidity");
 data[5]->GetDataStaError();
 data[5]->writedata();
 data[5]->writetheory();
 delete xbins;

 filename = "WEtaoverZY_ATLAS_Full";
 data[6] = new FileForEPUMP(filename);
 data[6]->InputData(rootname1, rootname2, "AntiLeptonEta", "LeptonEta", "ZRapidity");
 data[6]->InputTheory(rootNamesW, rootNames, "AntiLeptonEta", "LeptonEta", "ZRapidity");
 data[6]->GetDataStaError();
 data[6]->writedata();
 data[6]->writetheory();

 xbins = new double[100];
 xbins = DefineBins(size, 9);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 filename = "WYoverZY_ATLAS_Central";
 data[7] = new FileForEPUMP(filename);
 data[7]->Rebin(xbins, size);
 data[7]->InputData(rootname1, rootname2, "WPlusRapidity", "WMinusRapidity", "ZRapidity");
 data[7]->InputTheory(rootNamesW, rootNames, "WPlusRapidity", "WMinusRapidity", "ZRapidity");
 data[7]->GetDataStaError();
 data[7]->writedata();
 data[7]->writetheory();
 delete xbins;

 xbins = new double[100];
 xbins = DefineBins(size, 10);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 filename = "WYoverZY_ATLAS_Side";
 data[8] = new FileForEPUMP(filename);
 data[8]->Rebin(xbins, size);
 data[8]->RemoveSpecialBins(-2.0, 2.0);
 data[8]->InputData(rootname1, rootname2, "WPlusRapidity", "WMinusRapidity", "ZRapidity");
 data[8]->InputTheory(rootNamesW, rootNames, "WPlusRapidity", "WMinusRapidity", "ZRapidity");
 data[8]->GetDataStaError();
 data[8]->writedata();
 data[8]->writetheory();
 delete xbins;

 filename = "WYoverZY_ATLAS_Full";
 data[9] = new FileForEPUMP(filename);
 data[9]->InputData(rootname1, rootname2, "WPlusRapidity", "WMinusRapidity", "ZRapidity");
 data[9]->InputTheory(rootNamesW, rootNames, "WPlusRapidity", "WMinusRapidity", "ZRapidity");
 data[9]->GetDataStaError();
 data[9]->writedata();
 data[9]->writetheory();

 filename = "LeptonEtaMET";
 data[10] = new FileForEPUMP(filename);
// data[10]->Input2DData(rootname1, "LeptonEtaMET", "AntiLeptonEtaMET", "Add");
// data[10]->Input2DTheory(rootNamesW, "LeptonEtaMET", "AntiLeptonEtaMET", "Add");
 data[10]->Input2DData(rootname1, "LeptonEtaMET");
 data[10]->Input2DTheory(rootNamesW, "LeptonEtaMET");
 data[10]->GetDataStaError();
 data[10]->write2Ddata();
 data[10]->write2Dtheory();

 filename = "ZRapidity";
 data[11] = new FileForEPUMP(filename);
 data[11]->InputData(rootname2, "ZRapidity");
 data[11]->InputTheory(rootNames, "ZRapidity");
 data[11]->GetDataStaError();
 data[11]->writedata();
 data[11]->writetheory();

 filename = "WRapidity";
 data[12] = new FileForEPUMP(filename);
 data[12]->InputData(rootname1, "WPlusRapidity", "WMinusRapidity", "Add");
 data[12]->InputTheory(rootNamesW, "WPlusRapidity", "WMinusRapidity", "Add");
 data[12]->GetDataStaError();
 data[12]->writedata();
 data[12]->writetheory();

 filename = "MET";
 data[13] = new FileForEPUMP(filename);
 data[13]->InputData(rootname1, "WPlusMET", "WMinusMET", "Add");
 data[13]->InputTheory(rootNamesW, "WPlusMET", "WMinusMET", "Add");
 data[13]->GetDataStaError();
 data[13]->writedata();
 data[13]->writetheory();

 filename = "MET_LowEta";
 data[14] = new FileForEPUMP(filename);
 data[14]->InputData(rootname1, "WPlusMET_LowEta", "WMinusMET_LowEta", "Add");
 data[14]->InputTheory(rootNamesW, "WPlusMET_LowEta", "WMinusMET_LowEta", "Add");
 data[14]->GetDataStaError();
 data[14]->writedata();
 data[14]->writetheory();

 filename = "MET_HighEta";
 data[15] = new FileForEPUMP(filename);
 data[15]->InputData(rootname1, "WPlusMET_HighEta", "WMinusMET_HighEta", "Add");
 data[15]->InputTheory(rootNamesW, "WPlusMET_HighEta", "WMinusMET_HighEta", "Add");
 data[15]->GetDataStaError();
 data[15]->writedata();
 data[15]->writetheory();

 filename = "LeptonPt";
 data[16] = new FileForEPUMP(filename);
 data[16]->InputData(rootname1, "AntiLeptonPt", "LeptonPt", "Add");
 data[16]->InputTheory(rootNamesW, "AntiLeptonPt", "LeptonPt", "Add");
 data[16]->GetDataStaError();
 data[16]->writedata();
 data[16]->writetheory();

 filename = "LeptonPt_LowEta";
 data[17] = new FileForEPUMP(filename);
 data[17]->InputData(rootname1, "AntiLeptonPt_LowEta", "LeptonPt_LowEta", "Add");
 data[17]->InputTheory(rootNamesW, "AntiLeptonPt_LowEta", "LeptonPt_LowEta", "Add");
 data[17]->GetDataStaError();
 data[17]->writedata();
 data[17]->writetheory();

 filename = "LeptonPt_HighEta";
 data[18] = new FileForEPUMP(filename);
 data[18]->InputData(rootname1, "AntiLeptonPt_HighEta", "LeptonPt_HighEta", "Add");
 data[18]->InputTheory(rootNamesW, "AntiLeptonPt_HighEta", "LeptonPt_HighEta", "Add");
 data[18]->GetDataStaError();
 data[18]->writedata();
 data[18]->writetheory();

 filename = "LeptonEtaPt";
 data[19] = new FileForEPUMP(filename);
 data[19]->Input2DData(rootname1, "LeptonEtaPt", "AntiLeptonEtaPt", "Add");
 data[19]->Input2DTheory(rootNamesW, "LeptonEtaPt", "AntiLeptonEtaPt", "Add");
 data[19]->GetDataStaError();
 data[19]->write2Ddata();
 data[19]->write2Dtheory();

 filename = "WLeptonEtaAbs";
 data[20] = new FileForEPUMP(filename);
 data[20]->Input2DData(rootname1, "LeptonEtaAbs", "AntiLeptonEtaAbs", "Add");
 data[20]->Input2DTheory(rootNamesW, "LeptonEtaAbs", "AntiLeptonEtaAbs", "Add");
 data[20]->GetDataStaError();
 data[20]->write2Ddata();
 data[20]->write2Dtheory();
*/

/*
 filename = "AFBSlope_CC_80_100_1bin_2345";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFBSlope_CC");
 data->InputTheory(rootNames, "AFBSlope_CC");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFBSlope_CF_80_100_1bin_2345";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFBSlope_CF");
 data->InputTheory(rootNames, "AFBSlope_CF");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFBSlope_LHCb_80_100_1bin_2345";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFBSlope_LHCb");
 data->InputTheory(rootNames, "AFBSlope_LHCb");
 data->writedata();
 data->writetheory();
 delete data;
*/

/*
 filename = "AFBDiff_CC_60_120_2GeV_ZPole_2345";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFBDiff_CC_ZPole");
 data->InputTheory(rootNames, "AFBDiff_CC_ZPole");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFBDiff_CC_60_120_2GeV_Side_2345";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFBDiff_CC_Side");
 data->InputTheory(rootNames, "AFBDiff_CC_Side");
 data->writedata();
 data->writetheory();
 delete data;
*/

/* filename = "AFBDiff_CF_60_120_2GeV_ZPole_2345";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFBDiff_CF_ZPole");
 data->InputTheory(rootNames, "AFBDiff_CF_ZPole");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFBDiff_CF_60_120_2GeV_Side_2345";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFBDiff_CF_Side");
 data->InputTheory(rootNames, "AFBDiff_CF_Side");
 data->writedata();
 data->writetheory();
 delete data;
*/

/* filename = "AFB_CC_80_100_1bin_2315";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AveAFB_CC");
 data->InputTheory(rootNames, "AveAFB_CC");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_CF_80_100_1bin_2315";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AveAFB_CF");
 data->InputTheory(rootNames, "AveAFB_CF");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_Full_80_100_1bin_2315";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AveAFB_Full");
 data->InputTheory(rootNames, "AveAFB_Full");
 data->writedata();
 data->writetheory();
 delete data;
*/

/*
 filename = "AFBDiff_LHCb_60_120_2GeV_ZPole_2345";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFBDiff_LHCb_ZPole");
 data->InputTheory(rootNames, "AFBDiff_LHCb_ZPole");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFBDiff_LHCb_60_120_2GeV_Side_2345";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFBDiff_LHCb_Side");
 data->InputTheory(rootNames, "AFBDiff_LHCb_Side");
 data->writedata();
 data->writetheory();
 delete data;
*/

/*
 filename = "AFB_CC_80_100_1bin_2315";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AveAFB_CC");
 data->InputTheory(rootNames, "AveAFB_CC");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_CF_80_100_1bin_2315";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AveAFB_CF");
 data->InputTheory(rootNames, "AveAFB_CF");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_CC_80_100_10bin_2315";
 xbins = new double[100];
 xbins = DefineBins(size, 2);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 data = new FileForEPUMP(filename);
 data->Rebin(xbins, size);
 data->InputData(rootname, "FZmass_CC", "BZmass_CC");
 data->InputTheory(rootNames, "FZmass_CC", "BZmass_CC");
 data->writedata();
 data->writetheory();
 delete[] xbins;

 filename = "AFB_CF_80_100_10bin_2315";
 xbins = new double[100];
 xbins = DefineBins(size, 2);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 data = new FileForEPUMP(filename);
 data->Rebin(xbins, size);
 data->InputData(rootname, "FZmass_CF", "BZmass_CF");
 data->InputTheory(rootNames, "FZmass_CF", "BZmass_CF");
 data->writedata();
 data->writetheory();
 delete[] xbins;

 filename = "AFB_CC_60_120_2GeV_Side_2315";
 xbins = new double[100];
 xbins = DefineBins(size, 3);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 data = new FileForEPUMP(filename);
 data->SetSideband();
 data->Rebin(xbins, size);
 data->InputData(rootname, "FZmass_CC", "BZmass_CC");
 data->InputTheory(rootNames, "FZmass_CC", "BZmass_CC");
 data->writedata();
 data->writetheory();
 delete[] xbins;

 filename = "AFB_CF_60_120_2GeV_Side_2315";
 xbins = new double[100];
 xbins = DefineBins(size, 3);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 data = new FileForEPUMP(filename);
 data->SetSideband();
 data->Rebin(xbins, size);
 data->InputData(rootname, "FZmass_CF", "BZmass_CF");
 data->InputTheory(rootNames, "FZmass_CF", "BZmass_CF");
 data->writedata();
 data->writetheory();
 delete[] xbins;

 filename = "AFB_CC_60_120_2GeV_Full_2315";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_CC");
 data->InputTheory(rootNames, "AFB_CC");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_CF_60_120_2GeV_Full_2315";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_CF");
 data->InputTheory(rootNames, "AFB_CF");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_Full_60_120_2GeV_Full_2315";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Full");
 data->InputTheory(rootNames, "AFB_Full");
 data->writedata();
 data->writetheory();
 delete data;
*/

/*
 for(int i = 0; i < 40; i++){
   int STWINPUT = 2255 + 3 * i;
//   rootname = (TString)"/Data/yfu/MainCode/run/stwPDF/130fb-1_ZTemplate/STWTemplate/0." + (int)STWINPUT + (TString)"/MC_results.root";
   rootname = (TString)"/Data/yfu/MainCode/run/ResBosDilution/STWTemplate/250M/0." + (int)STWINPUT + (TString)"/MC_results.root";
   filename = (TString)"AFB_Full_60_130_2GeV_Full_" + (int)STWINPUT;
   data = new FileForEPUMP(filename);
   data->InputData(rootname, "AFB_Full");
   data->InputTheory(rootNames, "AFB_Full");
   data->writedata();
   data->writetheory();
   delete data;
 }
*/

/* filename = "WWBoostAsymmetry";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Ratio_AllFlavor");
 data->InputTheory(rootNames, "Ratio_AllFlavor");
 data->writedata();
 data->writetheory();
 delete data;
*/

/* filename = "WWBoostAsymmetry_WY";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Ratio_AllFlavor");
 data->InputTheory(rootNames, "Ratio_AllFlavor");
 data->writedata();
 data->writetheory();
 delete data;
*/

/* filename = "QuarkAFB_Full_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Full_qq");
 data->InputTheory(rootNames, "AFB_Full_qq");
 data->writedata();
 data->writetheory();
 delete data;
*/

/* filename = "HadronAFB_Full_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Full");
 data->InputTheory(rootNames, "AFB_Full");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "QuarkAFB_Full_uu_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Full_uu");
 data->InputTheory(rootNames, "AFB_Full_uu");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "QuarkAFB_Full_dd_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Full_dd");
 data->InputTheory(rootNames, "AFB_Full_dd");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "QuarkAFB_Full_uudd_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Full_uudd");
 data->InputTheory(rootNames, "AFB_Full_uudd");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "QuarkAFB_Full_gluon_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Full_gluon");
 data->InputTheory(rootNames, "AFB_Full_gluon");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "HadronAveAFB_Full_uu_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AveAFB_Full_uu");
 data->InputTheory(rootNames, "AveAFB_Full_uu");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "HadronAveAFB_Full_dd_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AveAFB_Full_dd");
 data->InputTheory(rootNames, "AveAFB_Full_dd");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "HadronAveAFB_Full_uudd_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AveAFB_Full_uudd");
 data->InputTheory(rootNames, "AveAFB_Full_uudd");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "HadronAveAFB_Full_utype_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AveAFB_Full_utype");
 data->InputTheory(rootNames, "AveAFB_Full_utype");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "HadronAveAFB_Full_dtype_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AveAFB_Full_dtype");
 data->InputTheory(rootNames, "AveAFB_Full_dtype");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "HadronAveAFB_Full_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AveAFB_Full");
 data->InputTheory(rootNames, "AveAFB_Full");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "HadronAFB_Full_uu_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Hadron_Full_uu");
 data->InputTheory(rootNames, "AFB_Hadron_Full_uu");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "HadronAFB_Full_dd_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Hadron_Full_dd");
 data->InputTheory(rootNames, "AFB_Hadron_Full_dd");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "HadronAFB_Full_uudd_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Hadron_Full_uudd");
 data->InputTheory(rootNames, "AFB_Hadron_Full_uudd");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "HadronAFB_Full_utype_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Hadron_Full_utype");
 data->InputTheory(rootNames, "AFB_Hadron_Full_utype");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "HadronAFB_Full_dtype_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Hadron_Full_dtype");
 data->InputTheory(rootNames, "AFB_Hadron_Full_dtype");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "QuarkAveAFB_Full_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "QuarkAveAFB_Full");
 data->InputTheory(rootNames, "QuarkAveAFB_Full");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "QuarkAveAFB_Full_uudd_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "QuarkAveAFB_Full_uudd");
 data->InputTheory(rootNames, "QuarkAveAFB_Full_uudd");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "QuarkAveAFB_Full_gluon_Pythia";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "QuarkAveAFB_Full_gluon");
 data->InputTheory(rootNames, "QuarkAveAFB_Full_gluon");
 data->writedata();
 data->writetheory();
 delete data;
*/

/* filename = "AFBDiff_Full_60_120_2GeV_2315";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFBDiff_Full");
 data->InputTheory(rootNames, "AFBDiff_Full");
 data->writedata();
 data->writetheory();
 delete data;
*/

/* filename = "QuarkAFB";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Full_qq");
 data->InputTheory(rootNames, "AFB_Full_qq");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "HadronAFB";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Full");
 data->InputTheory(rootNames, "AFB_Full");
 data->writedata();
 data->writetheory();
 delete data;
*/

/*
 filename = "WRapidityPt";
 data[32] = new FileForEPUMP(filename);
 data[32]->Input2DData(rootname1, "WPlusYPt", "WMinusYPt", "Add");
 data[32]->Input2DTheory(rootNamesW, "WPlusYPt", "WMinusYPt", "Add");
 data[32]->GetDataStaError();
 data[32]->write2Ddata();
 data[32]->write2Dtheory();

 filename = "WRapidityE";
 data[33] = new FileForEPUMP(filename);
 data[33]->Input2DData(rootname1, "WPlusYE", "WMinusYE", "Add");
 data[33]->Input2DTheory(rootNamesW, "WPlusYE", "WMinusYE", "Add");
 data[33]->GetDataStaError();
 data[33]->write2Ddata();
 data[33]->write2Dtheory();

 filename = "WE";
 data[34] = new FileForEPUMP(filename);
 data[34]->InputData(rootname1, "WPlusE", "WMinusE", "Add");
 data[34]->InputTheory(rootNamesW, "WPlusE", "WMinusE", "Add");
 data[34]->GetDataStaError();
 data[34]->writedata();
 data[34]->writetheory();

 filename = "ZRapidityE";
 data[35] = new FileForEPUMP(filename);
 data[35]->Input2DData(rootname2, "ZYE");
 data[35]->Input2DTheory(rootNames, "ZYE");
 data[35]->GetDataStaError();
 data[35]->write2Ddata();
 data[35]->write2Dtheory();

 filename = "ZRapidity_2315";
 data[36] = new FileForEPUMP(filename);
 data[36]->InputData(rootname2, "ZRapidity");
 data[36]->InputTheory(rootNames, "ZRapidity");
 data[36]->GetDataStaError();
 data[36]->writedata();
 data[36]->writetheory();

 filename = "LepWidthDiff_2315";
 data[37] = new FileForEPUMP(filename);
 data[37]->InputData(rootname2, "LepWidthDiff");
 data[37]->InputTheory(rootNames, "LepWidthDiff");
 data[37]->GetDataStaError();
 data[37]->writedata();
 data[37]->writetheory();

 filename = "LepWidthDiff_CC_2315";
 data[38] = new FileForEPUMP(filename);
 data[38]->InputData(rootname2, "LepWidthDiff_CC");
 data[38]->InputTheory(rootNames, "LepWidthDiff_CC");
 data[38]->GetDataStaError();
 data[38]->writedata();
 data[38]->writetheory();

 filename = "LepWidthDiff_CF_2315";
 data[39] = new FileForEPUMP(filename);
 data[39]->InputData(rootname2, "LepWidthDiff_CF");
 data[39]->InputTheory(rootNames, "LepWidthDiff_CF");
 data[39]->GetDataStaError();
 data[39]->writedata();
 data[39]->writetheory();

 filename = "LepAsym_CF_2324";
 data[40] = new FileForEPUMP(filename);
 data[40]->InputData(rootname2, "LepAsym_CF");
 data[40]->InputTheory(rootNames, "LepAsym_CF");
 data[40]->writedata();
 data[40]->writetheory();
*/

/* filename = "ZRapidity";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZRapidity");
 data->InputTheory(rootNames, "ZRapidity");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_3D_Full_2315";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "AFB_ZMass_ZY_QT");
 data->Input3DTheory(rootNames, "AFB_ZMass_ZY_QT");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "3DCrossSection";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "ZMass_ZY_QT");
 data->Input3DTheory(rootNames, "ZMass_ZY_QT");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;
*/
/* filename = "AFB_Full_60_130_2GeV_2315_2500M";
 xbins = new double[100];
 xbins = DefineBins(size, 11);
 cout<<"Mass min = "<<xbins[0]<<endl;
 cout<<"Mass max = "<<xbins[size - 1]<<endl;
 cout<<"bin number = "<<size - 1<<endl;
 data = new FileForEPUMP(filename);
 data->Rebin(xbins, size);
 data->InputData(rootname, "FZmass", "BZmass");
 data->InputTheory(rootNames, "FZmass", "BZmass");
 data->writedata();
 data->writetheory();
 delete[] xbins;
*/
/* filename = "AveAFB_ZY_QT";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "AveAFB_ZY_QT");
 data->Input2DTheory(rootNames, "AveAFB_ZY_QT");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;
*/

/* filename = "ChangePDF_ZRapidity";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ChangePDF_ZRapidity");
 data->InputTheory(rootNames, "ZRapidity");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ChangePDF_Wasymmetry";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ChangePDF_Wasymmetry");
 data->InputTheory(rootNames, "Wasymmetry");
 data->writedata();
 data->writetheory();
 delete data;
*/

/* filename = "ZMass_ZY_QT";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "ZMass_ZY_QT");
 data->Input3DTheory(rootNames, "ZMass_ZY_QT");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "Deltau";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "CoefficientZMass_ZY_QT_uu_wrong_Residual");
 data->Input3DTheory(rootNames, "CoefficientZMass_ZY_QT_uu_wrong_Residual");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "Deltad";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "CoefficientZMass_ZY_QT_dd_wrong_Residual");
 data->Input3DTheory(rootNames, "CoefficientZMass_ZY_QT_dd_wrong_Residual");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "ZMass_ZY1_QT2";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "ZMass_ZY_QT", 1, 2);
 data->Input3DTheory(rootNames, "ZMass_ZY_QT", 1, 2);
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ZMass_ZY2_QT2";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "ZMass_ZY_QT", 2, 2);
 data->Input3DTheory(rootNames, "ZMass_ZY_QT", 2, 2);
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ZMass_ZY3_QT2";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "ZMass_ZY_QT", 3, 2);
 data->Input3DTheory(rootNames, "ZMass_ZY_QT", 3, 2);
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ZMass_ZY4_QT2";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "ZMass_ZY_QT", 4, 2);
 data->Input3DTheory(rootNames, "ZMass_ZY_QT", 4, 2);
 data->writedata();
 data->writetheory();
 delete data;
*/

/*
 filename = "AFB_WPlusY";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_WPlusY");
 data->InputTheory(rootNames, "AFB_WPlusY");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_WMinusY";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_WMinusY");
 data->InputTheory(rootNames, "AFB_WMinusY");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_WPlusY_reco_80385";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_WPlusY_reco_80385");
 data->InputTheory(rootNames, "AFB_WPlusY_reco_80385");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_WMinusY_reco_80385";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_WMinusY_reco_80385");
 data->InputTheory(rootNames, "AFB_WMinusY_reco_80385");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_WPlusY_reco_80395";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_WPlusY_reco_80395");
 data->InputTheory(rootNames, "AFB_WPlusY_reco_80395");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_WMinusY_reco_80395";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_WMinusY_reco_80395");
 data->InputTheory(rootNames, "AFB_WMinusY_reco_80395");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_WPlusY_reco_80375";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_WPlusY_reco_80375");
 data->InputTheory(rootNames, "AFB_WPlusY_reco_80375");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_WMinusY_reco_80375";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_WMinusY_reco_80375");
 data->InputTheory(rootNames, "AFB_WMinusY_reco_80375");
 data->writedata();
 data->writetheory();
 delete data;
*/

/* For Z/W update

 filename = "Xsec_3D_CC";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "Xsec_3D_CC_Pseudodata");
 data->Input3DTheory(rootNames, "Xsec_3D_CC_Pseudodata");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "Xsec_3D_CF";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "Xsec_3D_CF_Pseudodata");
 data->Input3DTheory(rootNames, "Xsec_3D_CF_Pseudodata");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "Xsec_3D_CC_LowMass";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "Xsec_3D_CC_LowMass_Pseudodata");
 data->Input3DTheory(rootNames, "Xsec_3D_CC_LowMass_Pseudodata");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "Xsec_3D_CF_LowMass";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "Xsec_3D_CF_LowMass_Pseudodata");
 data->Input3DTheory(rootNames, "Xsec_3D_CF_LowMass_Pseudodata");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "Xsec_3D_CC_HighMass";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "Xsec_3D_CC_HighMass_Pseudodata");
 data->Input3DTheory(rootNames, "Xsec_3D_CC_HighMass_Pseudodata");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;
 
 filename = "Xsec_3D_CF_HighMass";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "Xsec_3D_CF_HighMass_Pseudodata");
 data->Input3DTheory(rootNames, "Xsec_3D_CF_HighMass_Pseudodata");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "Xsec_3D_CC_300";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "Xsec_3D_CC_Pseudodata300");
 data->Input3DTheory(rootNames, "Xsec_3D_CC_Pseudodata300");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "Xsec_3D_CF_300";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "Xsec_3D_CF_Pseudodata300");
 data->Input3DTheory(rootNames, "Xsec_3D_CF_Pseudodata300");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "Xsec_3D_CC_140";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "Xsec_3D_CC_Pseudodata140");
 data->Input3DTheory(rootNames, "Xsec_3D_CC_Pseudodata140");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "Xsec_3D_CF_140";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "Xsec_3D_CF_Pseudodata140");
 data->Input3DTheory(rootNames, "Xsec_3D_CF_Pseudodata140");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;

 filename = "Xsec_2D_CC";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "Xsec_2D_CC_Pseudodata");
 data->Input2DTheory(rootNames, "Xsec_2D_CC_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "Xsec_2D_CF";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "Xsec_2D_CF_Pseudodata");
 data->Input2DTheory(rootNames, "Xsec_2D_CF_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "Xsec_2D_CC_300";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "Xsec_2D_CC_Pseudodata300");
 data->Input2DTheory(rootNames, "Xsec_2D_CC_Pseudodata300");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "Xsec_2D_CF_300";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "Xsec_2D_CF_Pseudodata300");
 data->Input2DTheory(rootNames, "Xsec_2D_CF_Pseudodata300");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "Xsec_2D_CC_140";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "Xsec_2D_CC_Pseudodata140");
 data->Input2DTheory(rootNames, "Xsec_2D_CC_Pseudodata140");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "Xsec_2D_CF_140";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "Xsec_2D_CF_Pseudodata140");
 data->Input2DTheory(rootNames, "Xsec_2D_CF_Pseudodata140");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "Xsec_1D_CC";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Xsec_1D_CC_Pseudodata");
 data->InputTheory(rootNames, "Xsec_1D_CC_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "Xsec_1D_CF";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Xsec_1D_CF_Pseudodata");
 data->InputTheory(rootNames, "Xsec_1D_CF_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "Xsec_1D_CC_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Xsec_1D_CC_Pseudodata300");
 data->InputTheory(rootNames, "Xsec_1D_CC_Pseudodata300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "Xsec_1D_CF_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Xsec_1D_CF_Pseudodata300");
 data->InputTheory(rootNames, "Xsec_1D_CF_Pseudodata300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "Xsec_1D_CC_140";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Xsec_1D_CC_Pseudodata140");
 data->InputTheory(rootNames, "Xsec_1D_CC_Pseudodata140");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "Xsec_1D_CF_140";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Xsec_1D_CF_Pseudodata140");
 data->InputTheory(rootNames, "Xsec_1D_CF_Pseudodata140");
 data->writedata();
 data->writetheory();
 delete data;
*/

/* filename = "ZRapidity_CC_0_2.4";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZRapidity_CC_Pseudodata");
 data->InputTheory(rootNames, "ZRapidity_CC_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ZRapidity_CF_2.4_3.4";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZRapidity_CF_Pseudodata");
 data->InputTheory(rootNames, "ZRapidity_CF_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ZRapidity_CF_0_2.4";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZRapidity_CF_Low_Pseudodata");
 data->InputTheory(rootNames, "ZRapidity_CF_Low_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_CC_40_1000";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_CC");
 data->InputTheory(rootNames, "AFB_CC");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_CF_40_1000";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_CF");
 data->InputTheory(rootNames, "AFB_CF");
 data->writedata();
 data->writetheory();
 delete data;
*/

/*
 filename = "AFB_Mass_ZY_CC";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "AFB_Mass_ZY_CC");
 data->Input2DTheory(rootNames, "AFB_Mass_ZY_CC");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "AFB_Mass_ZY_CF";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "AFB_Mass_ZY_CF");
 data->Input2DTheory(rootNames, "AFB_Mass_ZY_CF");
 data->SkipRange2D(524, 726, 2.79, 3.01);
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "AFB_Mass_ZY_CC_300";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "AFB_Mass_ZY_CC_300");
 data->Input2DTheory(rootNames, "AFB_Mass_ZY_CC_300");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "AFB_Mass_ZY_CF_300";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "AFB_Mass_ZY_CF_300");
 data->Input2DTheory(rootNames, "AFB_Mass_ZY_CF_300");
 data->SkipRange2D(524, 726, 2.79, 3.01);
 data->write2Ddata();
 data->write2Dtheory();
 delete data;
*/

/* For Z/W update

 filename = "ZHighMass";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZMass_HighMass_Pseudodata");
 data->InputTheory(rootNames, "ZMass_HighMass_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ZHighMass_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZMass_HighMass_Pseudodata300");
 data->InputTheory(rootNames, "ZMass_HighMass_Pseudodata300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ZHighMass_140";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZMass_HighMass_Pseudodata140");
 data->InputTheory(rootNames, "ZMass_HighMass_Pseudodata140");
 data->writedata();
 data->writetheory();
 delete data;


 filename = "ZHighMass_CC";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZHighMass_CC_Pseudodata");
 data->InputTheory(rootNames, "ZHighMass_CC_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ZHighMass_CF";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZHighMass_CF_Pseudodata");
 data->InputTheory(rootNames, "ZHighMass_CF_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "PositiveLeptonEta";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "PositiveLeptonEta_Pseudodata");
 data->InputTheory(rootNames, "PositiveLeptonEta_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "NegativeLeptonEta";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "NegativeLeptonEta_Pseudodata");
 data->InputTheory(rootNames, "NegativeLeptonEta_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "PositiveLeptonEta_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "PositiveLeptonEta_Pseudodata300");
 data->InputTheory(rootNames, "PositiveLeptonEta_Pseudodata300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "NegativeLeptonEta_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "NegativeLeptonEta_Pseudodata300");
 data->InputTheory(rootNames, "NegativeLeptonEta_Pseudodata300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "PositiveLeptonEta_140";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "PositiveLeptonEta_Pseudodata140");
 data->InputTheory(rootNames, "PositiveLeptonEta_Pseudodata140");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "NegativeLeptonEta_140";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "NegativeLeptonEta_Pseudodata140");
 data->InputTheory(rootNames, "NegativeLeptonEta_Pseudodata140");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusMT";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPlusMT_Pseudodata");
 data->InputTheory(rootNames, "WPlusMT_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WMinusMT";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WMinusMT_Pseudodata");
 data->InputTheory(rootNames, "WMinusMT_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusMT_Above100";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPlusMT_Above100_Pseudodata");
 data->InputTheory(rootNames, "WPlusMT_Above100_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WMinusMT_Above100";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WMinusMT_Above100_Pseudodata");
 data->InputTheory(rootNames, "WMinusMT_Above100_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusMT_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPlusMT_Pseudodata300");
 data->InputTheory(rootNames, "WPlusMT_Pseudodata300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WMinusMT_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WMinusMT_Pseudodata300");
 data->InputTheory(rootNames, "WMinusMT_Pseudodata300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusMT_140";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPlusMT_Pseudodata140");
 data->InputTheory(rootNames, "WPlusMT_Pseudodata140");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WMinusMT_140";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WMinusMT_Pseudodata140");
 data->InputTheory(rootNames, "WMinusMT_Pseudodata140");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusMTEta";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "WPlusMTEta_Pseudodata");
 data->Input2DTheory(rootNames, "WPlusMTEta_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "WMinusMTEta";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "WMinusMTEta_Pseudodata");
 data->Input2DTheory(rootNames, "WMinusMTEta_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "WPlusMTEta_Above100";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "WPlusMTEta_Above100_Pseudodata");
 data->Input2DTheory(rootNames, "WPlusMTEta_Above100_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "WMinusMTEta_Above100";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "WMinusMTEta_Above100_Pseudodata");
 data->Input2DTheory(rootNames, "WMinusMTEta_Above100_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "WPlusMTEta_300";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "WPlusMTEta_Pseudodata300");
 data->Input2DTheory(rootNames, "WPlusMTEta_Pseudodata300");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "WMinusMTEta_300";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "WMinusMTEta_Pseudodata300");
 data->Input2DTheory(rootNames, "WMinusMTEta_Pseudodata300");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "WPlusMTEta_140";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "WPlusMTEta_Pseudodata140");
 data->Input2DTheory(rootNames, "WPlusMTEta_Pseudodata140");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "WMinusMTEta_140";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "WMinusMTEta_Pseudodata140");
 data->Input2DTheory(rootNames, "WMinusMTEta_Pseudodata140");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;
*/

/* filename = "PositiveLeptonPt";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "PositiveLeptonPt_Pseudodata");
 data->InputTheory(rootNames, "PositiveLeptonPt_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "NegativeLeptonPt";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "NegativeLeptonPt_Pseudodata");
 data->InputTheory(rootNames, "NegativeLeptonPt_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "PositiveLeptonPtEta";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "PositiveLeptonPtEta_Pseudodata");
 data->Input2DTheory(rootNames, "PositiveLeptonPtEta_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "NegativeLeptonPtEta";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "NegativeLeptonPtEta_Pseudodata");
 data->Input2DTheory(rootNames, "NegativeLeptonPtEta_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "WLeptonPt";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WLeptonPt_Pseudodata");
 data->InputTheory(rootNames, "WLeptonPt_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "NeutrinoPt";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "NeutrinoPt_Pseudodata");
 data->InputTheory(rootNames, "NeutrinoPt_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WBosonMT";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WBosonMT_Pseudodata");
 data->InputTheory(rootNames, "WBosonMT_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;
*/

/*
 for(int i = 1; i <= 20; i++){
   filename = (TString)"WPlusMTEta_MT" + i;
   data = new FileForEPUMP(filename);
   data->Input2DData(rootname, "WPlusMTEta_Pseudodata", i, 0);
   data->Input2DTheory(rootNames, "WPlusMTEta_Pseudodata", i, 0);
   data->writedata();
   data->writetheory();
   delete data;
  
   filename = (TString)"WMinusMTEta_MT" + i;
   data = new FileForEPUMP(filename);
   data->Input2DData(rootname, "WMinusMTEta_Pseudodata", i, 0);
   data->Input2DTheory(rootNames, "WMinusMTEta_Pseudodata", i, 0);
   data->writedata();
   data->writetheory();
   delete data;
 }
*/

/* For Z/W update

 filename = "ATLAS_Mll_HighMass";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ATLAS_Mll_HighMass_Pseudodata");
 data->InputTheory(rootNames, "ATLAS_Mll_HighMass_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ATLAS_costheta";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ATLAS_costheta_Pseudodata");
 data->InputTheory(rootNames, "ATLAS_costheta_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ATLAS_DilRapidity";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ATLAS_DilRapidity_Pseudodata");
 data->InputTheory(rootNames, "ATLAS_DilRapidity_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ATLAS_Mll_HighMass_costheta";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "ATLAS_Mll_HighMass_costheta_Pseudodata");
 data->Input2DTheory(rootNames, "ATLAS_Mll_HighMass_costheta_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "ATLAS_Mll_HighMass_DilRapidity";
 data = new FileForEPUMP(filename);
 data->Input2DData(rootname, "ATLAS_Mll_HighMass_DilRapidity_Pseudodata");
 data->Input2DTheory(rootNames, "ATLAS_Mll_HighMass_DilRapidity_Pseudodata");
 data->write2Ddata();
 data->write2Dtheory();
 delete data;

 filename = "ATLAS_HMDY_Xsec_3D";
 data = new FileForEPUMP(filename);
 data->Input3DData(rootname, "ATLAS_HMDY_Xsec_3D_Pseudodata");
 data->Input3DTheory(rootNames, "ATLAS_HMDY_Xsec_3D_Pseudodata");
 data->write3Ddata();
 data->write3Dtheory();
 delete data;
*/

/*
 filename = "WLeptonEtaAsymmetry";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WLeptonEtaAsymmetry");
 data->InputTheory(rootNames, "WLeptonEtaAsymmetry");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPositiveLeptonEtaAsymmetry";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPositiveLeptonEtaAsymmetry");
 data->InputTheory(rootNames, "WPositiveLeptonEtaAsymmetry");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WNegativeLeptonEtaAsymmetry";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WNegativeLeptonEtaAsymmetry");
 data->InputTheory(rootNames, "WNegativeLeptonEtaAsymmetry");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WLeptonEtaAsymmetry_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WLeptonEtaAsymmetry_300");
 data->InputTheory(rootNames, "WLeptonEtaAsymmetry_300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPositiveLeptonEtaAsymmetry_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPositiveLeptonEtaAsymmetry_300");
 data->InputTheory(rootNames, "WPositiveLeptonEtaAsymmetry_300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WNegativeLeptonEtaAsymmetry_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WNegativeLeptonEtaAsymmetry_300");
 data->InputTheory(rootNames, "WNegativeLeptonEtaAsymmetry_300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WLeptonEtaShapeAsymmetry";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WLeptonEtaShapeAsymmetry");
 data->InputTheory(rootNames, "WLeptonEtaShapeAsymmetry");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_CF";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_CF");
 data->InputTheory(rootNames, "AFB_CF");
 data->writedata();
 data->writetheory();
 delete data;
*/


/* For Z/W update

 filename = "WLeptonPtAsymmetry";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WLeptonPtAsymmetry");
 data->InputTheory(rootNames, "WLeptonPtAsymmetry");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "NeutrinoPtAsymmetry";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "NeutrinoPtAsymmetry");
 data->InputTheory(rootNames, "NeutrinoPtAsymmetry");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WBosonMTAsymmetry";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WBosonMTAsymmetry");
 data->InputTheory(rootNames, "WBosonMTAsymmetry");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WHighMassMT";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WHighMassMT_Pseudodata");
 data->InputTheory(rootNames, "WHighMassMT_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusHighMassMT";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPlusHighMassMT_Pseudodata");
 data->InputTheory(rootNames, "WPlusHighMassMT_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WMinusHighMassMT";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WMinusHighMassMT_Pseudodata");
 data->InputTheory(rootNames, "WMinusHighMassMT_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WHighMassMT_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WHighMassMT_Pseudodata300");
 data->InputTheory(rootNames, "WHighMassMT_Pseudodata300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusHighMassMT_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPlusHighMassMT_Pseudodata300");
 data->InputTheory(rootNames, "WPlusHighMassMT_Pseudodata300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WMinusHighMassMT_300";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WMinusHighMassMT_Pseudodata300");
 data->InputTheory(rootNames, "WMinusHighMassMT_Pseudodata300");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WHighMassMT_140";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WHighMassMT_Pseudodata140");
 data->InputTheory(rootNames, "WHighMassMT_Pseudodata140");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusHighMassMT_140";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPlusHighMassMT_Pseudodata140");
 data->InputTheory(rootNames, "WPlusHighMassMT_Pseudodata140");
 data->writedata();
 data->writetheory();
 delete data;
 
 filename = "WMinusHighMassMT_140";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WMinusHighMassMT_Pseudodata140");
 data->InputTheory(rootNames, "WMinusHighMassMT_Pseudodata140");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ZHighMass_Integral";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZMass_HighMass_Integral");
 data->InputTheory(rootNames, "ZMass_HighMass_Integral");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ZHighMass_CC_Integral";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZHighMass_CC_Integral");
 data->InputTheory(rootNames, "ZHighMass_CC_Integral");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ZHighMass_CF_Integral";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZHighMass_CF_Integral");
 data->InputTheory(rootNames, "ZHighMass_CF_Integral");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WHighMassMT_Integral";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WHighMassMT_Integral");
 data->InputTheory(rootNames, "WHighMassMT_Integral");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusHighMassMT_Integral";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPlusHighMassMT_Integral");
 data->InputTheory(rootNames, "WPlusHighMassMT_Integral");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WMinusHighMassMT_Integral";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WMinusHighMassMT_Integral");
 data->InputTheory(rootNames, "WMinusHighMassMT_Integral");
 data->writedata();
 data->writetheory();
 delete data;
*/

/*
 filename = "CrossSection";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "CrossSection_Pseudodata");
 data->InputTheory(rootNames, "CrossSection_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "CrossSectionF";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "CrossSectionF_Pseudodata");
 data->InputTheory(rootNames, "CrossSectionF_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "CrossSectionB";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "CrossSectionB_Pseudodata");
 data->InputTheory(rootNames, "CrossSectionB_Pseudodata");
 data->writedata();
 data->writetheory();
 delete data;
*/

/*
 filename = "JacobianAsymmetry";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "JacobianAsymmetry");
 data->InputTheory(rootNames, "JacobianAsymmetry");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "JacobianAsymmetryLowQT";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "JacobianAsymmetryLowQT");
 data->InputTheory(rootNames, "JacobianAsymmetryLowQT");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "LeptonPt_LHC";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "LeptonPt_LHC_Pseudodata_Final");
 data->InputTheory(rootNames, "LeptonPt_LHC_Pseudodata_Final");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "LeptonPt_LowQT_LHC";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "LeptonPt_LowQT_LHC_Pseudodata_Final");
 data->InputTheory(rootNames, "LeptonPt_LowQT_LHC_Pseudodata_Final");
 data->writedata();
 data->writetheory();
 delete data;
*/

/*
 filename = "AFB_HighMass_CT18";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_HighMass_MSHT20";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameMSHT20, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_HighMass_NNPDF40";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameNNPDF40, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata();
 data->writetheory();
 delete data;
*/

/*
 filename = "AFB_HighMass_500_1044_CT18";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata(1, 8);
 data->writetheory(1, 8);
 delete data;

 filename = "AFB_HighMass_500_1044_MSHT20";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameMSHT20, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata(1, 8);
 data->writetheory(1, 8);
 delete data;

 filename = "AFB_HighMass_500_1044_NNPDF40";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameNNPDF40, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata(1, 8);
 data->writetheory(1, 8);
 delete data;

 filename = "AFB_HighMass_1044_3154_CT18";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata(9, 20);
 data->writetheory(9, 20);
 delete data;

 filename = "AFB_HighMass_1044_3154_MSHT20";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameMSHT20, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata(9, 20);
 data->writetheory(9, 20);
 delete data;

 filename = "AFB_HighMass_1044_3154_NNPDF40";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameNNPDF40, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata(9, 20);
 data->writetheory(9, 20);
 delete data;

 filename = "AFB_HighMass_3154_5000_CT18";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata(21, 25);
 data->writetheory(21, 25);
 delete data;

 filename = "AFB_HighMass_3154_5000_MSHT20";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameMSHT20, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata(21, 25);
 data->writetheory(21, 25);
 delete data;

 filename = "AFB_HighMass_3154_5000_NNPDF40";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameNNPDF40, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata(21, 25);
 data->writetheory(21, 25);
 delete data;
*/

/*
 filename = "AFB_LowMass1_CT18";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_LowMass1");
 data->InputTheory(rootNames, "AFB_LowMass1");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_LowMass1_MSHT20";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameMSHT20, "AFB_LowMass1");
 data->InputTheory(rootNames, "AFB_LowMass1");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_LowMass1_NNPDF40";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameNNPDF40, "AFB_LowMass1");
 data->InputTheory(rootNames, "AFB_LowMass1");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_LowMass2_CT18";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_LowMass2");
 data->InputTheory(rootNames, "AFB_LowMass2");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_LowMass2_MSHT20";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameMSHT20, "AFB_LowMass2");
 data->InputTheory(rootNames, "AFB_LowMass2");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_LowMass2_NNPDF40";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameNNPDF40, "AFB_LowMass2");
 data->InputTheory(rootNames, "AFB_LowMass2");
 data->writedata();
 data->writetheory();
 delete data;

 for(int i = 1; i <= 5; i++){
   filename = (TString)"AFB_LowMass1_ZY" + (int)i + (TString)"_CT18";
   data = new FileForEPUMP(filename);
   data->Input2DData(rootname, "AFB_LowMass1_ZY", i);
   data->Input2DTheory(rootNames, "AFB_LowMass1_ZY", i);
   if(i == 4) data->SkipRange(428, 467);
   data->writedata();
   data->writetheory();
   delete data;

   filename = (TString)"AFB_LowMass1_ZY" + (int)i + (TString)"_MSHT20";
   data = new FileForEPUMP(filename);
   data->Input2DData(rootnameMSHT20, "AFB_LowMass1_ZY", i);
   data->Input2DTheory(rootNames, "AFB_LowMass1_ZY", i);
   if(i == 4) data->SkipRange(428, 467);
   data->writedata();
   data->writetheory();
   delete data;

   filename = (TString)"AFB_LowMass1_ZY" + (int)i + (TString)"_NNPDF40";
   data = new FileForEPUMP(filename);
   data->Input2DData(rootnameNNPDF40, "AFB_LowMass1_ZY", i);
   data->Input2DTheory(rootNames, "AFB_LowMass1_ZY", i);
   if(i == 4) data->SkipRange(428, 467);
   data->writedata();
   data->writetheory();
   delete data;

   filename = (TString)"AFB_LowMass2_ZY" + (int)i + (TString)"_CT18";
   data = new FileForEPUMP(filename);
   data->Input2DData(rootname, "AFB_LowMass2_ZY", i);
   data->Input2DTheory(rootNames, "AFB_LowMass2_ZY", i);
   if(i == 4) data->SkipRange(429, 600);
   data->writedata();
   data->writetheory();
   delete data;

   filename = (TString)"AFB_LowMass2_ZY" + (int)i + (TString)"_MSHT20";
   data = new FileForEPUMP(filename);
   data->Input2DData(rootnameMSHT20, "AFB_LowMass2_ZY", i);
   data->Input2DTheory(rootNames, "AFB_LowMass2_ZY", i);
   if(i == 4) data->SkipRange(429, 600);
   data->writedata();
   data->writetheory();
   delete data;

   filename = (TString)"AFB_LowMass2_ZY" + (int)i + (TString)"_NNPDF40";
   data = new FileForEPUMP(filename);
   data->Input2DData(rootnameNNPDF40, "AFB_LowMass2_ZY", i);
   data->Input2DTheory(rootNames, "AFB_LowMass2_ZY", i);
   if(i == 4) data->SkipRange(429, 600);
   data->writedata();
   data->writetheory();
   delete data;

 }
*/

/* filename = "AFB_ATLAS_CC";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_ATLAS_CC");
 data->InputTheory(rootNames, "AFB_ATLAS_CC");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_ATLAS_CF";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_ATLAS_CF");
 data->InputTheory(rootNames, "AFB_ATLAS_CF");
 data->writedata();
 data->writetheory();
 delete data;
*/

/* filename = "AFB_HighMass_CT18_ForMSHT";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_HighMass_MSHT20_ForMSHT";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameMSHT20, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata();
 data->writetheory();
 delete data;

 filename = "AFB_HighMass_NNPDF40_ForMSHT";
 data = new FileForEPUMP(filename);
 data->InputData(rootnameNNPDF40, "AFB_HighMass");
 data->InputTheory(rootNames, "AFB_HighMass");
 data->writedata();
 data->writetheory();
 delete data;
*/

/* filename = "AFB_2315";
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "AFB_Full");
 data->InputTheory(rootNames, "AFB_Full");
 data->InputExtendedTheory("stw", ExtendedNames, "AFB_Full");
 data->writedata();
 data->writetheory();
 data->writeExtendedtheory();
 delete data;

 filename = "AFB_2324";
 data = new FileForEPUMP(filename);
 data->InputData(rootname2324, "AFB_Full");
 data->InputTheory(rootNames, "AFB_Full");
 data->InputExtendedTheory("stw", ExtendedNames, "AFB_Full");
 data->writedata();
 data->writetheory();
 data->writeExtendedtheory();
 delete data;
*/

 return 1;
}
