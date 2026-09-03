#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "Uncertainty/FitAFBStw.h"
#include "CompareDataTheory/CompareDataTheory.h"
#include "TMinuitHelper/TMinuitHelper.h"
#include "PDFHelper/PDFReweight.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "Tools/Tools.h"

using namespace std;

vector<TH1D *> global_uuLinearPlot;
vector<TH1D *> global_ddLinearPlot;

TH3D* global_uuFittedSlope;
TH3D* global_uuFittedOffset;
TH3D* global_ddFittedSlope;
TH3D* global_ddFittedOffset;

void GetAFBStwLinear()
{
 TString rootName;

 vector<TString> STWTemplates;

 ifstream infile;
  infile.open("STWTemplate.list",ios::in);
 while(infile>>rootName){
  STWTemplates.push_back(rootName);
 }

 TString AFB_uu_Name = "AFB_ZMass_ZY_QT_uu";
 TString AFB_dd_Name = "AFB_ZMass_ZY_QT_dd";

 map<int, double> STWInput;
 map<double, int> FindSTW;
 for(int i = 0; i < 40; i++){
   STWInput[i] = 0.2255 + i * 0.0003;
 }

 int FirstSTW = 15;
 int LastSTW = 30;

 int Index = 0;

 TH3D* uuAFB[40];
 vector<TH3D *> uuAFBs;
 for(int i = FirstSTW; i < LastSTW; i++){

   FindSTW[STWInput[i]] = Index;
   Index++;

   TFile* file = new TFile(STWTemplates.at(i));
   uuAFB[i] = (TH3D *)file->Get(AFB_uu_Name);

   uuAFBs.push_back(uuAFB[i]);
 }

 TH3D* ddAFB[40];
 vector<TH3D *> ddAFBs;
 for(int i = FirstSTW; i < LastSTW; i++){

   TFile* file = new TFile(STWTemplates.at(i));
   ddAFB[i] = (TH3D *)file->Get(AFB_dd_Name);

   ddAFBs.push_back(ddAFB[i]);
 }

 vector<TH3D *> uuLinearPlot;
 vector<TH3D *> ddLinearPlot;
 TH3D* uuFittedSlope;
 TH3D* uuFittedOffset;
 TH3D* ddFittedSlope;
 TH3D* ddFittedOffset;
 FitAFBStw* uuSlopeAndOffset = new FitAFBStw();
 uuSlopeAndOffset->Input(uuAFBs, STWInput[FirstSTW], STWInput[LastSTW - 1], uuLinearPlot, uuFittedSlope, uuFittedOffset);
 FitAFBStw* ddSlopeAndOffset = new FitAFBStw();
 ddSlopeAndOffset->Input(ddAFBs, STWInput[FirstSTW], STWInput[LastSTW - 1], ddLinearPlot, ddFittedSlope, ddFittedOffset);

 vector<TH1D *> uu1DLinearPlot;
 vector<TH1D *> dd1DLinearPlot;
 uuSlopeAndOffset->Get1DLinearPlot(uu1DLinearPlot);
 ddSlopeAndOffset->Get1DLinearPlot(dd1DLinearPlot);

 global_uuLinearPlot = uu1DLinearPlot;
 global_ddLinearPlot = dd1DLinearPlot;

 global_uuFittedSlope = uuFittedSlope;
 global_uuFittedOffset = uuFittedOffset;
 global_ddFittedSlope = ddFittedSlope;
 global_ddFittedOffset = ddFittedOffset;
}

int main(int argc, char** argv)
{
 GetAFBStwLinear();

 TString DataName = "/ustcfs2/yfu/MainCode/run/CMSDilution/ResBosCMS/0.2315/MC_results.root";

 TString Dilution_uu_Name = "CoefficientZMass_ZY_QT_uu_wrong_Residual";
 TString Dilution_dd_Name = "CoefficientZMass_ZY_QT_dd_wrong_Residual";
 TString AveDilution_uu_Name = "CoefficientZMass_ZY_QT_uu_wrong_Average";
 TString AveDilution_dd_Name = "CoefficientZMass_ZY_QT_dd_wrong_Average";
 TString AFB_uu_Name = "AFB_ZMass_ZY_QT_uu";
 TString AFB_dd_Name = "AFB_ZMass_ZY_QT_dd";

 TFile *DataFile = new TFile(DataName);

 TH3D* Dilution_uu = (TH3D *)DataFile->Get(Dilution_uu_Name);
 TH3D* Dilution_dd = (TH3D *)DataFile->Get(Dilution_dd_Name);
 TH3D* AveDilution_uu = (TH3D *)DataFile->Get(AveDilution_uu_Name);
 TH3D* AveDilution_dd = (TH3D *)DataFile->Get(AveDilution_dd_Name);
 TH3D* AFB_uu = (TH3D *)DataFile->Get(AFB_uu_Name);
 TH3D* AFB_dd = (TH3D *)DataFile->Get(AFB_dd_Name);

 TH3D* CrossSection_uu = (TH3D *)DataFile->Get("ZMass_ZY_QT_uu");
 TH3D* CrossSection_dd = (TH3D *)DataFile->Get("ZMass_ZY_QT_dd");
 TH3D* CrossSection_ss = (TH3D *)DataFile->Get("ZMass_ZY_QT_ss");
 TH3D* CrossSection_cc = (TH3D *)DataFile->Get("ZMass_ZY_QT_cc");
 TH3D* CrossSection_bb = (TH3D *)DataFile->Get("ZMass_ZY_QT_bb");

 TH3D* A0_uu = (TH3D *)DataFile->Get("A0_Mass_ZY_QT_uu");
 TH3D* A0_dd = (TH3D *)DataFile->Get("A0_Mass_ZY_QT_dd");
 TH3D* A0_ss = (TH3D *)DataFile->Get("A0_Mass_ZY_QT_ss");
 TH3D* A0_cc = (TH3D *)DataFile->Get("A0_Mass_ZY_QT_cc");
 TH3D* A0_bb = (TH3D *)DataFile->Get("A0_Mass_ZY_QT_bb");

 TFile* writefile = new TFile("CMSCrossSection.root", "RECREATE");
 writefile->cd();

 for(int i = 0; i < global_uuLinearPlot.size(); i++){
   global_uuLinearPlot.at(i)->Write();
   global_ddLinearPlot.at(i)->Write();
 }

 Dilution_uu->Write();
 Dilution_dd->Write();
 AveDilution_uu->Write();
 AveDilution_dd->Write();
 AFB_uu->Write();
 AFB_dd->Write();

 CrossSection_uu->Write();
 CrossSection_dd->Write();
 CrossSection_ss->Write();
 CrossSection_cc->Write();
 CrossSection_bb->Write();

 A0_uu->Write();
 A0_dd->Write();
 A0_ss->Write();
 A0_cc->Write();
 A0_bb->Write();

 global_uuFittedSlope->Write();
 global_uuFittedOffset->Write();
 global_ddFittedSlope->Write();
 global_ddFittedOffset->Write();

 writefile->Close();

 return 1;
}

