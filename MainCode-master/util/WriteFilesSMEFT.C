#include "FileForEPUMP/FileForEPUMP.h"

using namespace std;

int main( int argc ,char **argv)
{
 if(argc != 2){
   cout<<"usage WriteFilesSMEFT coefficient"<<endl;
   return 0;
 }

 TString rootname = "/mnt/home/fuyao3/Work/MainCode/run/ePumpSMEFT/CT18SMEFT.00/MC_results.root";

 vector<TString> rootNames;
 TString rootName;

 ifstream infile;
  infile.open("theory.list",ios::in);
 while(infile>>rootName){
   rootNames.push_back(rootName);
 }
 infile.close();

 FileForEPUMP* data;

 TString filename = "";

 TString OperatorName = "clq3";
 double coefficient = stod(argv[1]);
 double coefficient_up = 4.029;
 double coefficient_down = -4.301;

 filename = "Xsec_3D_CC";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Xsec_3D_CC_Final_Pseudodata");
 data->InputTheory(rootNames, "Xsec_3D_CC_Final_Pseudodata");
 data->InputOtherKFactor((TString)"Xsec_3D_CC_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "Xsec_3D_CF";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Xsec_3D_CF_Final_Pseudodata");
 data->InputTheory(rootNames, "Xsec_3D_CF_Final_Pseudodata");
 data->InputOtherKFactor((TString)"Xsec_3D_CF_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "Xsec_2D_CC";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Xsec_2D_CC_Final_Pseudodata");
 data->InputTheory(rootNames, "Xsec_2D_CC_Final_Pseudodata");
 data->InputOtherKFactor((TString)"Xsec_2D_CC_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "Xsec_2D_CF";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Xsec_2D_CF_Final_Pseudodata");
 data->InputTheory(rootNames, "Xsec_2D_CF_Final_Pseudodata");
 data->InputOtherKFactor((TString)"Xsec_2D_CF_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "Xsec_1D_CC";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Xsec_1D_CC_Pseudodata");
 data->InputTheory(rootNames, "Xsec_1D_CC_Pseudodata");
 data->InputOtherKFactor((TString)"Xsec_1D_CC_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "Xsec_1D_CF";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "Xsec_1D_CF_Pseudodata");
 data->InputTheory(rootNames, "Xsec_1D_CF_Pseudodata");
 data->InputOtherKFactor((TString)"Xsec_1D_CF_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ZHighMass";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ZMass_HighMass_Pseudodata");
 data->InputTheory(rootNames, "ZMass_HighMass_Pseudodata");
 data->InputOtherKFactor((TString)"ZMass_HighMass_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "PositiveLeptonEta";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "PositiveLeptonEta_Pseudodata");
 data->InputTheory(rootNames, "PositiveLeptonEta_Pseudodata");
 data->InputOtherKFactor((TString)"PositiveLeptonEta_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "NegativeLeptonEta";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "NegativeLeptonEta_Pseudodata");
 data->InputTheory(rootNames, "NegativeLeptonEta_Pseudodata");
 data->InputOtherKFactor((TString)"NegativeLeptonEta_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusMT";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPlusMT_Pseudodata");
 data->InputTheory(rootNames, "WPlusMT_Pseudodata");
 data->InputOtherKFactor((TString)"WPlusMT_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WMinusMT";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WMinusMT_Pseudodata");
 data->InputTheory(rootNames, "WMinusMT_Pseudodata");
 data->InputOtherKFactor((TString)"WMinusMT_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusMT_Above100";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPlusMT_Above100_Pseudodata");
 data->InputTheory(rootNames, "WPlusMT_Above100_Pseudodata");
 data->InputOtherKFactor((TString)"WPlusMT_Above100_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WMinusMT_Above100";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WMinusMT_Above100_Pseudodata");
 data->InputTheory(rootNames, "WMinusMT_Above100_Pseudodata");
 data->InputOtherKFactor((TString)"WMinusMT_Above100_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusMTEta";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPlusMTEta_Final_Pseudodata");
 data->InputTheory(rootNames, "WPlusMTEta_Final_Pseudodata");
 data->InputOtherKFactor((TString)"WPlusMTEta_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WMinusMTEta";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WMinusMTEta_Final_Pseudodata");
 data->InputTheory(rootNames, "WMinusMTEta_Final_Pseudodata");
 data->InputOtherKFactor((TString)"WMinusMTEta_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WPlusMTEta_Above100";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WPlusMTEta_Above100_Final_Pseudodata");
 data->InputTheory(rootNames, "WPlusMTEta_Above100_Final_Pseudodata");
 data->InputOtherKFactor((TString)"WPlusMTEta_Above100_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "WMinusMTEta_Above100";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "WMinusMTEta_Above100_Final_Pseudodata");
 data->InputTheory(rootNames, "WMinusMTEta_Above100_Final_Pseudodata");
 data->InputOtherKFactor((TString)"WMinusMTEta_Above100_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ATLAS_Mll_HighMass";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ATLAS_Mll_HighMass_Pseudodata");
 data->InputTheory(rootNames, "ATLAS_Mll_HighMass_Pseudodata");
 data->InputOtherKFactor((TString)"ATLAS_Mll_HighMass_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ATLAS_costheta";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ATLAS_costheta_Pseudodata");
 data->InputTheory(rootNames, "ATLAS_costheta_Pseudodata");
 data->InputOtherKFactor((TString)"ATLAS_costheta_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ATLAS_DilRapidity";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ATLAS_DilRapidity_Pseudodata");
 data->InputTheory(rootNames, "ATLAS_DilRapidity_Pseudodata");
 data->InputOtherKFactor((TString)"ATLAS_DilRapidity_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ATLAS_Mll_HighMass_costheta";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ATLAS_Mll_HighMass_costheta_NewBinning_Pseudodata");
 data->InputTheory(rootNames, "ATLAS_Mll_HighMass_costheta_NewBinning_Pseudodata");
 data->InputOtherKFactor((TString)"ATLAS_Mll_HighMass_costheta_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ATLAS_Mll_HighMass_DilRapidity";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ATLAS_Mll_HighMass_DilRapidity_NewBinning_Pseudodata");
 data->InputTheory(rootNames, "ATLAS_Mll_HighMass_DilRapidity_NewBinning_Pseudodata");
 data->InputOtherKFactor((TString)"ATLAS_Mll_HighMass_DilRapidity_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 filename = "ATLAS_HMDY_Xsec_3D";
 filename = filename + "_" + OperatorName + TString::Format("_c%.1f", coefficient);
 data = new FileForEPUMP(filename);
 data->InputData(rootname, "ATLAS_HMDY_Xsec_3D_Final_Pseudodata");
 data->InputTheory(rootNames, "ATLAS_HMDY_Xsec_3D_Final_Pseudodata");
 data->InputOtherKFactor((TString)"ATLAS_HMDY_Xsec_3D_" + OperatorName + "_kfactor.txt");
 data->ApplyOtherKFactor(-1, vector<double>{coefficient});
 data->ApplyOtherKFactor(0, vector<double>{0.0});
 data->ApplyOtherKFactor(1, vector<double>{coefficient_up});
 data->ApplyOtherKFactor(2, vector<double>{coefficient_down});
 data->writedata();
 data->writetheory();
 delete data;

 return 1;
}

