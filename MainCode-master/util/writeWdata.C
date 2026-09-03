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
   double xbins1[16] = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5};
   memcpy(xbins, xbins1, sizeof(xbins1));
   size = 16;
 }
 return xbins;
}

int main( int argc ,char **argv)
{
//rootname input the pseudodata, for giving a correct statistical uncertainty
 TString rootname = "/lustre/AtlUser/yfu/pku_resbos/CT14HERA2NNLO_13TeV/Wsample/PseudoData_0.2315_CT14HERA2NNLO_tmp/If1363.00/MC_results.root";
// TString rootname = "MC_results_lowmu.root";
 TString AntiLeptonName1 = "AntiLeptonEtaAbs";
 TString LeptonName1 = "LeptonEtaAbs";

 TString AntiLeptonName2 = "AntiLeptonEtaAbs_pt25_35";
 TString LeptonName2 = "LeptonEtaAbs_pt25_35";

 TString AntiLeptonName3 = "AntiLeptonEtaAbs_pt35";
 TString LeptonName3 = "LeptonEtaAbs_pt35";

 TString AntiLeptonName4 = "AntiLeptonEtaAbs2D";
 TString LeptonName4 = "LeptonEtaAbs2D";

 TString AntiLeptonName5 = "AntiLeptonEtaAbs3D_cut30";
 TString LeptonName5 = "LeptonEtaAbs3D_cut30";

 TString AntiLeptonName6 = "AntiLeptonEtaAbs3D_cut35";
 TString LeptonName6 = "LeptonEtaAbs3D_cut35";

 TString AntiLeptonName7 = "AntiLeptonEtaAbs3D_cut40";
 TString LeptonName7 = "LeptonEtaAbs3D_cut40";

 TString AntiLeptonName8 = "AntiLeptonEtaAbs_MT2D";
 TString LeptonName8 = "LeptonEtaAbs_MT2D";

 TString AntiLeptonName9 = "AntiLeptonEtaAbs_ut2D";
 TString LeptonName9 = "LeptonEtaAbs_ut2D";

//dataname input the PDF central set, for giving a reasonable W asymmetry value compared with theory 
 
 ifstream infile;
  infile.open("wpm.list",ios::in);

 vector<TString> rootnames;
 TString rootName;
 while(infile>>rootName){
   rootnames.push_back(rootName);
 }

 FileForEPUMP* data[100];
 TString fileName;

 fileName = "Wasymmetry";
 data[0] = new FileForEPUMP(fileName);
 data[0]->Rebin(10);
 data[0]->InputData(rootname, AntiLeptonName1, LeptonName1);
 data[0]->InputTheory(rootnames, AntiLeptonName1, LeptonName1);
 data[0]->GetDataStaError();
 data[0]->writedata();
 data[0]->writetheory();

 fileName = "Wasymmetry_pt25_35";
 data[1] = new FileForEPUMP(fileName);
 data[1]->Rebin(10);
 data[1]->InputData(rootname, AntiLeptonName2, LeptonName2);
 data[1]->InputTheory(rootnames, AntiLeptonName2, LeptonName2);
 data[1]->GetDataStaError();
 data[1]->writedata();
 data[1]->writetheory();

 fileName = "Wasymmetry_pt35";
 data[2] = new FileForEPUMP(fileName);
 data[2]->Rebin(10);
 data[2]->InputData(rootname, AntiLeptonName3, LeptonName3);
 data[2]->InputTheory(rootnames, AntiLeptonName3, LeptonName3);
 data[2]->GetDataStaError();
 data[2]->writedata();
 data[2]->writetheory();

 fileName = "Wasymmetry_pt1_met1_cut30";
 data[3] = new FileForEPUMP(fileName);
 data[3]->Input3DData(rootname, AntiLeptonName5, LeptonName5, 1, 1);
 data[3]->Input3DTheory(rootnames, AntiLeptonName5, LeptonName5, 1, 1);
 data[3]->GetDataStaError();
 data[3]->writedata();
 data[3]->writetheory();

 fileName = "Wasymmetry_pt1_met2_cut30";
 data[4] = new FileForEPUMP(fileName);
 data[4]->Input3DData(rootname, AntiLeptonName5, LeptonName5, 1, 2);
 data[4]->Input3DTheory(rootnames, AntiLeptonName5, LeptonName5, 1, 2);
 data[4]->GetDataStaError();
 data[4]->writedata();
 data[4]->writetheory();

 fileName = "Wasymmetry_pt2_met1_cut30";
 data[5] = new FileForEPUMP(fileName);
 data[5]->Input3DData(rootname, AntiLeptonName5, LeptonName5, 2, 1);
 data[5]->Input3DTheory(rootnames, AntiLeptonName5, LeptonName5, 2, 1);
 data[5]->GetDataStaError();
 data[5]->writedata();
 data[5]->writetheory();

 fileName = "Wasymmetry_pt2_met2_cut30";
 data[6] = new FileForEPUMP(fileName);
 data[6]->Input3DData(rootname, AntiLeptonName5, LeptonName5, 2, 2);
 data[6]->Input3DTheory(rootnames, AntiLeptonName5, LeptonName5, 2, 2);
 data[6]->GetDataStaError();
 data[6]->writedata();
 data[6]->writetheory();

 fileName = "Wasymmetry_pt1_met1_cut35";
 data[7] = new FileForEPUMP(fileName);
 data[7]->Input3DData(rootname, AntiLeptonName6, LeptonName6, 1, 1);
 data[7]->Input3DTheory(rootnames, AntiLeptonName6, LeptonName6, 1, 1);
 data[7]->GetDataStaError();
 data[7]->writedata();
 data[7]->writetheory();

 fileName = "Wasymmetry_pt1_met2_cut35";
 data[8] = new FileForEPUMP(fileName);
 data[8]->Input3DData(rootname, AntiLeptonName6, LeptonName6, 1, 2);
 data[8]->Input3DTheory(rootnames, AntiLeptonName6, LeptonName6, 1, 2);
 data[8]->GetDataStaError();
 data[8]->writedata();
 data[8]->writetheory();

 fileName = "Wasymmetry_pt2_met1_cut35";
 data[9] = new FileForEPUMP(fileName);
 data[9]->Input3DData(rootname, AntiLeptonName6, LeptonName6, 2, 1);
 data[9]->Input3DTheory(rootnames, AntiLeptonName6, LeptonName6, 2, 1);
 data[9]->GetDataStaError();
 data[9]->writedata();
 data[9]->writetheory();

 fileName = "Wasymmetry_pt2_met2_cut35";
 data[10] = new FileForEPUMP(fileName);
 data[10]->Input3DData(rootname, AntiLeptonName6, LeptonName6, 2, 2);
 data[10]->Input3DTheory(rootnames, AntiLeptonName6, LeptonName6, 2, 2);
 data[10]->GetDataStaError();
 data[10]->writedata();
 data[10]->writetheory();

 fileName = "Wasymmetry_pt1_met1_cut40";
 data[11] = new FileForEPUMP(fileName);
 data[11]->Input3DData(rootname, AntiLeptonName7, LeptonName7, 1, 1);
 data[11]->Input3DTheory(rootnames, AntiLeptonName7, LeptonName7, 1, 1);
 data[11]->GetDataStaError();
 data[11]->writedata();
 data[11]->writetheory();

 fileName = "Wasymmetry_pt1_met2_cut40";
 data[12] = new FileForEPUMP(fileName);
 data[12]->Input3DData(rootname, AntiLeptonName7, LeptonName7, 1, 2);
 data[12]->Input3DTheory(rootnames, AntiLeptonName7, LeptonName7, 1, 2);
 data[12]->GetDataStaError();
 data[12]->writedata();
 data[12]->writetheory();

 fileName = "Wasymmetry_pt2_met1_cut40";
 data[13] = new FileForEPUMP(fileName);
 data[13]->Input3DData(rootname, AntiLeptonName7, LeptonName7, 2, 1);
 data[13]->Input3DTheory(rootnames, AntiLeptonName7, LeptonName7, 2, 1);
 data[13]->GetDataStaError();
 data[13]->writedata();
 data[13]->writetheory();

 fileName = "Wasymmetry_pt2_met2_cut40";
 data[14] = new FileForEPUMP(fileName);
 data[14]->Input3DData(rootname, AntiLeptonName7, LeptonName7, 2, 2);
 data[14]->Input3DTheory(rootnames, AntiLeptonName7, LeptonName7, 2, 2);
 data[14]->GetDataStaError();
 data[14]->writedata();
 data[14]->writetheory();


 for(int ibin = 6; ibin <= 21; ibin++){
   fileName = (TString)"Wasymmetry_ptbin_" + (int)ibin;
   data[ibin + 9] = new FileForEPUMP(fileName);
   data[ibin + 9]->Input2DData(rootname, AntiLeptonName4, LeptonName4, ibin);
   data[ibin + 9]->Input2DTheory(rootnames, AntiLeptonName4, LeptonName4, ibin);
   data[ibin + 9]->GetDataStaError();
   data[ibin + 9]->writedata();
   data[ibin + 9]->writetheory();
 }

 fileName = (TString)"Wasymmetry_MTbin_1";
 data[22] = new FileForEPUMP(fileName);
 data[22]->Input2DData(rootname, AntiLeptonName8, LeptonName8, 1);
 data[22]->Input2DTheory(rootnames, AntiLeptonName8, LeptonName8, 1);
 data[22]->GetDataStaError();
 data[22]->writedata();
 data[22]->writetheory();

 fileName = (TString)"Wasymmetry_MTbin_2";
 data[23] = new FileForEPUMP(fileName);
 data[23]->Input2DData(rootname, AntiLeptonName8, LeptonName8, 2);
 data[23]->Input2DTheory(rootnames, AntiLeptonName8, LeptonName8, 2);
 data[23]->GetDataStaError();
 data[23]->writedata();
 data[23]->writetheory();

 fileName = (TString)"Wasymmetry_utbin_1";
 data[24] = new FileForEPUMP(fileName);
 data[24]->Input2DData(rootname, AntiLeptonName9, LeptonName9, 1);
 data[24]->Input2DTheory(rootnames, AntiLeptonName9, LeptonName9, 1);
 data[24]->GetDataStaError();
 data[24]->writedata();
 data[24]->writetheory();

 fileName = (TString)"Wasymmetry_utbin_2";
 data[25] = new FileForEPUMP(fileName);
 data[25]->Input2DData(rootname, AntiLeptonName9, LeptonName9, 2);
 data[25]->Input2DTheory(rootnames, AntiLeptonName9, LeptonName9, 2);
 data[25]->GetDataStaError();
 data[25]->writedata();
 data[25]->writetheory();

 for(int ibin = 6; ibin < 13; ibin++){
   fileName = (TString)"LeptonEta_pt_" + (int)ibin;
   data[ibin + 25 - 5] = new FileForEPUMP(fileName);
   data[ibin + 25 - 5]->Input2DData(rootname, LeptonName4, ibin);
   data[ibin + 25 - 5]->Input2DTheory(rootnames, LeptonName4, ibin);
   data[ibin + 25 - 5]->Normalization(100, 8);
   data[ibin + 25 - 5]->GetDataStaError();
   data[ibin + 25 - 5]->writedata();
   data[ibin + 25 - 5]->writetheory();
 }

 for(int ibin = 6; ibin < 13; ibin++){
   fileName = (TString)"AntiLeptonEta_pt_" + (int)ibin;
   data[ibin + 32 - 5] = new FileForEPUMP(fileName);
   data[ibin + 32 - 5]->Input2DData(rootname, AntiLeptonName4, ibin);
   data[ibin + 32 - 5]->Input2DTheory(rootnames, AntiLeptonName4, ibin);
   data[ibin + 32 - 5]->Normalization(100, 8);
   data[ibin + 32 - 5]->GetDataStaError();
   data[ibin + 32 - 5]->writedata();
   data[ibin + 32 - 5]->writetheory();
 }

 double* xbins;
 int size;

 xbins = new double[100];
 xbins = DefineBins(size, 6);
 fileName = "Wasym15_1_2.5";
 data[40] = new FileForEPUMP(fileName);
 data[40]->Rebin(xbins, size);
 data[40]->InputData(rootname, AntiLeptonName1, LeptonName1);
 data[40]->InputTheory(rootnames, AntiLeptonName1, LeptonName1);
 data[40]->GetDataStaError();
 data[40]->writedata();
 data[40]->writetheory();
 return 1;
}
