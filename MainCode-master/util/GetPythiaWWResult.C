#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{
 vector<TString> rootNames;
 TString rootName;

 ifstream infile;
  infile.open("theoryCC.list",ios::in);
 while(infile>>rootName){
  rootNames.push_back(rootName);
 }
 infile.close();

 TFile* writefile = new TFile("save.root", "RECREATE");
 writefile->cd();

 TString Ratio_uu_Name = "Ratio_uu";
 TString Ratio_dd_Name = "Ratio_dd";
 TString Ratio_ss_Name = "Ratio_ss";
 TString Ratio_cc_Name = "Ratio_cc";
 TString Ratio_bb_Name = "Ratio_bb";
 TString Ratio_AllFlavor_Name = "Ratio_AllFlavor";
 TString RatioW_uu_Name = "RatioW_uu";
 TString RatioW_dd_Name = "RatioW_dd";
 TString RatioW_ss_Name = "RatioW_ss";
 TString RatioW_cc_Name = "RatioW_cc";
 TString RatioW_bb_Name = "RatioW_bb";
 TString RatioW_AllFlavor_Name = "RatioW_AllFlavor";
 TString BoostAsymmetry_uu_Name = "BoostAsymmetry_uu";
 TString BoostAsymmetry_dd_Name = "BoostAsymmetry_dd";
 TString BoostAsymmetry_ss_Name = "BoostAsymmetry_ss";
 TString BoostAsymmetry_cc_Name = "BoostAsymmetry_cc";
 TString BoostAsymmetry_bb_Name = "BoostAsymmetry_bb";
 TString BoostAsymmetry_AllFlavor_Name = "BoostAsymmetry_AllFlavor";
 TString BoostAsymmetryW_uu_Name = "BoostAsymmetryW_uu";
 TString BoostAsymmetryW_dd_Name = "BoostAsymmetryW_dd";
 TString BoostAsymmetryW_ss_Name = "BoostAsymmetryW_ss";
 TString BoostAsymmetryW_cc_Name = "BoostAsymmetryW_cc";
 TString BoostAsymmetryW_bb_Name = "BoostAsymmetryW_bb";
 TString BoostAsymmetryW_AllFlavor_Name = "BoostAsymmetryW_AllFlavor";

 int nSet = rootNames.size();

 TH1D* Ratio_uu[nSet];
 vector<TH1D *> Ratio_uus;

 TH1D* Ratio_dd[nSet];
 vector<TH1D *> Ratio_dds;

 TH1D* Ratio_ss[nSet];
 vector<TH1D *> Ratio_sss;

 TH1D* Ratio_cc[nSet];
 vector<TH1D *> Ratio_ccs;

 TH1D* Ratio_bb[nSet];
 vector<TH1D *> Ratio_bbs;

 TH1D* Ratio_AllFlavor[nSet];
 vector<TH1D *> Ratio_AllFlavors;

 TH1D* RatioW_uu[nSet];
 vector<TH1D *> RatioW_uus;

 TH1D* RatioW_dd[nSet];
 vector<TH1D *> RatioW_dds;

 TH1D* RatioW_ss[nSet];
 vector<TH1D *> RatioW_sss;

 TH1D* RatioW_cc[nSet];
 vector<TH1D *> RatioW_ccs;

 TH1D* RatioW_bb[nSet];
 vector<TH1D *> RatioW_bbs;

 TH1D* RatioW_AllFlavor[nSet];
 vector<TH1D *> RatioW_AllFlavors;

 TH1D* BoostAsymmetry_uu[nSet];
 vector<TH1D *> BoostAsymmetry_uus;

 TH1D* BoostAsymmetry_dd[nSet];
 vector<TH1D *> BoostAsymmetry_dds;

 TH1D* BoostAsymmetry_ss[nSet];
 vector<TH1D *> BoostAsymmetry_sss;

 TH1D* BoostAsymmetry_cc[nSet];
 vector<TH1D *> BoostAsymmetry_ccs;

 TH1D* BoostAsymmetry_bb[nSet];
 vector<TH1D *> BoostAsymmetry_bbs;

 TH1D* BoostAsymmetry_AllFlavor[nSet];
 vector<TH1D *> BoostAsymmetry_AllFlavors;
 
 TH1D* BoostAsymmetryW_uu[nSet];
 vector<TH1D *> BoostAsymmetryW_uus;
   
 TH1D* BoostAsymmetryW_dd[nSet];
 vector<TH1D *> BoostAsymmetryW_dds;

 TH1D* BoostAsymmetryW_ss[nSet];
 vector<TH1D *> BoostAsymmetryW_sss;

 TH1D* BoostAsymmetryW_cc[nSet];
 vector<TH1D *> BoostAsymmetryW_ccs;

 TH1D* BoostAsymmetryW_bb[nSet];
 vector<TH1D *> BoostAsymmetryW_bbs;

 TH1D* BoostAsymmetryW_AllFlavor[nSet];
 vector<TH1D *> BoostAsymmetryW_AllFlavors;

 for(int i = 0; i < nSet; i++){
   TFile* file = new TFile(rootNames.at(i));

   Ratio_uu[i] = (TH1D *)file->Get(Ratio_uu_Name);
   Ratio_dd[i] = (TH1D *)file->Get(Ratio_dd_Name);
   Ratio_ss[i] = (TH1D *)file->Get(Ratio_ss_Name);
   Ratio_cc[i] = (TH1D *)file->Get(Ratio_cc_Name);
   Ratio_bb[i] = (TH1D *)file->Get(Ratio_bb_Name);
   Ratio_AllFlavor[i] = (TH1D *)file->Get(Ratio_AllFlavor_Name);
   RatioW_uu[i] = (TH1D *)file->Get(RatioW_uu_Name);
   RatioW_dd[i] = (TH1D *)file->Get(RatioW_dd_Name);
   RatioW_ss[i] = (TH1D *)file->Get(RatioW_ss_Name);
   RatioW_cc[i] = (TH1D *)file->Get(RatioW_cc_Name);
   RatioW_bb[i] = (TH1D *)file->Get(RatioW_bb_Name);
   RatioW_AllFlavor[i] = (TH1D *)file->Get(RatioW_AllFlavor_Name);
   BoostAsymmetry_uu[i] = (TH1D *)file->Get(BoostAsymmetry_uu_Name);
   BoostAsymmetry_dd[i] = (TH1D *)file->Get(BoostAsymmetry_dd_Name);
   BoostAsymmetry_ss[i] = (TH1D *)file->Get(BoostAsymmetry_ss_Name);
   BoostAsymmetry_cc[i] = (TH1D *)file->Get(BoostAsymmetry_cc_Name);
   BoostAsymmetry_bb[i] = (TH1D *)file->Get(BoostAsymmetry_bb_Name);
   BoostAsymmetry_AllFlavor[i] = (TH1D *)file->Get(BoostAsymmetry_AllFlavor_Name);
   BoostAsymmetryW_uu[i] = (TH1D *)file->Get(BoostAsymmetryW_uu_Name);
   BoostAsymmetryW_dd[i] = (TH1D *)file->Get(BoostAsymmetryW_dd_Name);
   BoostAsymmetryW_ss[i] = (TH1D *)file->Get(BoostAsymmetryW_ss_Name);
   BoostAsymmetryW_cc[i] = (TH1D *)file->Get(BoostAsymmetryW_cc_Name);
   BoostAsymmetryW_bb[i] = (TH1D *)file->Get(BoostAsymmetryW_bb_Name);
   BoostAsymmetryW_AllFlavor[i] = (TH1D *)file->Get(BoostAsymmetryW_AllFlavor_Name);

   Ratio_uus.push_back(Ratio_uu[i]);
   Ratio_dds.push_back(Ratio_dd[i]);
   Ratio_sss.push_back(Ratio_ss[i]);
   Ratio_ccs.push_back(Ratio_cc[i]);
   Ratio_bbs.push_back(Ratio_bb[i]);
   Ratio_AllFlavors.push_back(Ratio_AllFlavor[i]);
   RatioW_uus.push_back(RatioW_uu[i]);
   RatioW_dds.push_back(RatioW_dd[i]);
   RatioW_sss.push_back(RatioW_ss[i]);
   RatioW_ccs.push_back(RatioW_cc[i]);
   RatioW_bbs.push_back(RatioW_bb[i]);
   RatioW_AllFlavors.push_back(RatioW_AllFlavor[i]);
   BoostAsymmetry_uus.push_back(BoostAsymmetry_uu[i]);
   BoostAsymmetry_dds.push_back(BoostAsymmetry_dd[i]);
   BoostAsymmetry_sss.push_back(BoostAsymmetry_ss[i]);
   BoostAsymmetry_ccs.push_back(BoostAsymmetry_cc[i]);
   BoostAsymmetry_bbs.push_back(BoostAsymmetry_bb[i]);
   BoostAsymmetry_AllFlavors.push_back(BoostAsymmetry_AllFlavor[i]);
   BoostAsymmetryW_uus.push_back(BoostAsymmetryW_uu[i]);
   BoostAsymmetryW_dds.push_back(BoostAsymmetryW_dd[i]);
   BoostAsymmetryW_sss.push_back(BoostAsymmetryW_ss[i]);
   BoostAsymmetryW_ccs.push_back(BoostAsymmetryW_cc[i]);
   BoostAsymmetryW_bbs.push_back(BoostAsymmetryW_bb[i]);
   BoostAsymmetryW_AllFlavors.push_back(BoostAsymmetryW_AllFlavor[i]);

   writefile->cd();
 }


 TH1D* Ratio_uu_Error;
 TH1D* Ratio_dd_Error;
 TH1D* Ratio_ss_Error;
 TH1D* Ratio_cc_Error;
 TH1D* Ratio_bb_Error;
 TH1D* Ratio_AllFlavor_Error;
 TH1D* RatioW_uu_Error;
 TH1D* RatioW_dd_Error;
 TH1D* RatioW_ss_Error;
 TH1D* RatioW_cc_Error;
 TH1D* RatioW_bb_Error;
 TH1D* RatioW_AllFlavor_Error;
 TH1D* BoostAsymmetry_uu_Error;
 TH1D* BoostAsymmetry_dd_Error;
 TH1D* BoostAsymmetry_ss_Error;
 TH1D* BoostAsymmetry_cc_Error;
 TH1D* BoostAsymmetry_bb_Error;
 TH1D* BoostAsymmetry_AllFlavor_Error;
 TH1D* BoostAsymmetryW_uu_Error;
 TH1D* BoostAsymmetryW_dd_Error;
 TH1D* BoostAsymmetryW_ss_Error;
 TH1D* BoostAsymmetryW_cc_Error;
 TH1D* BoostAsymmetryW_bb_Error;
 TH1D* BoostAsymmetryW_AllFlavor_Error;

 PDFUncertainty *Ratio_uu_unc;
 Ratio_uu_unc = new PDFUncertainty();
 Ratio_uu_unc->Input1DPlot("Symmetry", Ratio_uus, Ratio_uu_Error);

 PDFUncertainty *Ratio_dd_unc;
 Ratio_dd_unc = new PDFUncertainty();
 Ratio_dd_unc->Input1DPlot("Symmetry", Ratio_dds, Ratio_dd_Error);

 PDFUncertainty *Ratio_ss_unc;
 Ratio_ss_unc = new PDFUncertainty();
 Ratio_ss_unc->Input1DPlot("Symmetry", Ratio_sss, Ratio_ss_Error);

 PDFUncertainty *Ratio_cc_unc;
 Ratio_cc_unc = new PDFUncertainty();
 Ratio_cc_unc->Input1DPlot("Symmetry", Ratio_ccs, Ratio_cc_Error);

 PDFUncertainty *Ratio_bb_unc;
 Ratio_bb_unc = new PDFUncertainty();
 Ratio_bb_unc->Input1DPlot("Symmetry", Ratio_bbs, Ratio_bb_Error);

 PDFUncertainty *Ratio_AllFlavor_unc;
 Ratio_AllFlavor_unc = new PDFUncertainty();
 Ratio_AllFlavor_unc->Input1DPlot("Symmetry", Ratio_AllFlavors, Ratio_AllFlavor_Error);

 PDFUncertainty *RatioW_uu_unc;
 RatioW_uu_unc = new PDFUncertainty();
 RatioW_uu_unc->Input1DPlot("Symmetry", RatioW_uus, RatioW_uu_Error);

 PDFUncertainty *RatioW_dd_unc;
 RatioW_dd_unc = new PDFUncertainty();
 RatioW_dd_unc->Input1DPlot("Symmetry", RatioW_dds, RatioW_dd_Error);

 PDFUncertainty *RatioW_ss_unc;
 RatioW_ss_unc = new PDFUncertainty();
 RatioW_ss_unc->Input1DPlot("Symmetry", RatioW_sss, RatioW_ss_Error);

 PDFUncertainty *RatioW_cc_unc;
 RatioW_cc_unc = new PDFUncertainty();
 RatioW_cc_unc->Input1DPlot("Symmetry", RatioW_ccs, RatioW_cc_Error);

 PDFUncertainty *RatioW_bb_unc;
 RatioW_bb_unc = new PDFUncertainty();
 RatioW_bb_unc->Input1DPlot("Symmetry", RatioW_bbs, RatioW_bb_Error);

 PDFUncertainty *RatioW_AllFlavor_unc;
 RatioW_AllFlavor_unc = new PDFUncertainty();
 RatioW_AllFlavor_unc->Input1DPlot("Symmetry", RatioW_AllFlavors, RatioW_AllFlavor_Error);

 PDFUncertainty *BoostAsymmetry_uu_unc;
 BoostAsymmetry_uu_unc = new PDFUncertainty();
 BoostAsymmetry_uu_unc->Input1DPlot("Symmetry", BoostAsymmetry_uus, BoostAsymmetry_uu_Error);

 PDFUncertainty *BoostAsymmetry_dd_unc;
 BoostAsymmetry_dd_unc = new PDFUncertainty();
 BoostAsymmetry_dd_unc->Input1DPlot("Symmetry", BoostAsymmetry_dds, BoostAsymmetry_dd_Error);

 PDFUncertainty *BoostAsymmetry_ss_unc;
 BoostAsymmetry_ss_unc = new PDFUncertainty();
 BoostAsymmetry_ss_unc->Input1DPlot("Symmetry", BoostAsymmetry_sss, BoostAsymmetry_ss_Error);

 PDFUncertainty *BoostAsymmetry_cc_unc;
 BoostAsymmetry_cc_unc = new PDFUncertainty();
 BoostAsymmetry_cc_unc->Input1DPlot("Symmetry", BoostAsymmetry_ccs, BoostAsymmetry_cc_Error);

 PDFUncertainty *BoostAsymmetry_bb_unc;
 BoostAsymmetry_bb_unc = new PDFUncertainty();
 BoostAsymmetry_bb_unc->Input1DPlot("Symmetry", BoostAsymmetry_bbs, BoostAsymmetry_bb_Error);

 PDFUncertainty *BoostAsymmetry_AllFlavor_unc;
 BoostAsymmetry_AllFlavor_unc = new PDFUncertainty();
 BoostAsymmetry_AllFlavor_unc->Input1DPlot("Symmetry", BoostAsymmetry_AllFlavors, BoostAsymmetry_AllFlavor_Error);

 PDFUncertainty *BoostAsymmetryW_uu_unc;
 BoostAsymmetryW_uu_unc = new PDFUncertainty();
 BoostAsymmetryW_uu_unc->Input1DPlot("Symmetry", BoostAsymmetryW_uus, BoostAsymmetryW_uu_Error);

 PDFUncertainty *BoostAsymmetryW_dd_unc;
 BoostAsymmetryW_dd_unc = new PDFUncertainty();
 BoostAsymmetryW_dd_unc->Input1DPlot("Symmetry", BoostAsymmetryW_dds, BoostAsymmetryW_dd_Error);

 PDFUncertainty *BoostAsymmetryW_ss_unc;
 BoostAsymmetryW_ss_unc = new PDFUncertainty();
 BoostAsymmetryW_ss_unc->Input1DPlot("Symmetry", BoostAsymmetryW_sss, BoostAsymmetryW_ss_Error);

 PDFUncertainty *BoostAsymmetryW_cc_unc;
 BoostAsymmetryW_cc_unc = new PDFUncertainty();
 BoostAsymmetryW_cc_unc->Input1DPlot("Symmetry", BoostAsymmetryW_ccs, BoostAsymmetryW_cc_Error);

 PDFUncertainty *BoostAsymmetryW_bb_unc;
 BoostAsymmetryW_bb_unc = new PDFUncertainty();
 BoostAsymmetryW_bb_unc->Input1DPlot("Symmetry", BoostAsymmetryW_bbs, BoostAsymmetryW_bb_Error);

 PDFUncertainty *BoostAsymmetryW_AllFlavor_unc;
 BoostAsymmetryW_AllFlavor_unc = new PDFUncertainty();
 BoostAsymmetryW_AllFlavor_unc->Input1DPlot("Symmetry", BoostAsymmetryW_AllFlavors, BoostAsymmetryW_AllFlavor_Error);

 FileForEPUMP *Ratio_uu_file = new FileForEPUMP("Ratio_uu");
 Ratio_uu_file->InputData(Ratio_uus.at(0));
 Ratio_uu_file->InputTheory(Ratio_uu_unc);
 Ratio_uu_file->writedata();
 Ratio_uu_file->writetheory();

 FileForEPUMP *Ratio_dd_file = new FileForEPUMP("Ratio_dd");
 Ratio_dd_file->InputData(Ratio_dds.at(0));
 Ratio_dd_file->InputTheory(Ratio_dd_unc);
 Ratio_dd_file->writedata();
 Ratio_dd_file->writetheory();

 FileForEPUMP *Ratio_ss_file = new FileForEPUMP("Ratio_ss");
 Ratio_ss_file->InputData(Ratio_sss.at(0));
 Ratio_ss_file->InputTheory(Ratio_ss_unc);
 Ratio_ss_file->writedata();
 Ratio_ss_file->writetheory();

 FileForEPUMP *Ratio_cc_file = new FileForEPUMP("Ratio_cc");
 Ratio_cc_file->InputData(Ratio_ccs.at(0));
 Ratio_cc_file->InputTheory(Ratio_cc_unc);
 Ratio_cc_file->writedata();
 Ratio_cc_file->writetheory();

 FileForEPUMP *Ratio_bb_file = new FileForEPUMP("Ratio_bb");
 Ratio_bb_file->InputData(Ratio_bbs.at(0));
 Ratio_bb_file->InputTheory(Ratio_bb_unc);
 Ratio_bb_file->writedata();
 Ratio_bb_file->writetheory();

 FileForEPUMP *Ratio_AllFlavor_file = new FileForEPUMP("Ratio_AllFlavor");
 Ratio_AllFlavor_file->InputData(Ratio_AllFlavors.at(0));
 Ratio_AllFlavor_file->InputTheory(Ratio_AllFlavor_unc);
 Ratio_AllFlavor_file->writedata();
 Ratio_AllFlavor_file->writetheory();

 FileForEPUMP *RatioW_uu_file = new FileForEPUMP("RatioW_uu");
 RatioW_uu_file->InputData(RatioW_uus.at(0));
 RatioW_uu_file->InputTheory(RatioW_uu_unc);
 RatioW_uu_file->writedata();
 RatioW_uu_file->writetheory();

 FileForEPUMP *RatioW_dd_file = new FileForEPUMP("RatioW_dd");
 RatioW_dd_file->InputData(RatioW_dds.at(0));
 RatioW_dd_file->InputTheory(RatioW_dd_unc);
 RatioW_dd_file->writedata();
 RatioW_dd_file->writetheory();

 FileForEPUMP *RatioW_ss_file = new FileForEPUMP("RatioW_ss");
 RatioW_ss_file->InputData(RatioW_sss.at(0));
 RatioW_ss_file->InputTheory(RatioW_ss_unc);
 RatioW_ss_file->writedata();
 RatioW_ss_file->writetheory();

 FileForEPUMP *RatioW_cc_file = new FileForEPUMP("RatioW_cc");
 RatioW_cc_file->InputData(RatioW_ccs.at(0));
 RatioW_cc_file->InputTheory(RatioW_cc_unc);
 RatioW_cc_file->writedata();
 RatioW_cc_file->writetheory();

 FileForEPUMP *RatioW_bb_file = new FileForEPUMP("RatioW_bb");
 RatioW_bb_file->InputData(RatioW_bbs.at(0));
 RatioW_bb_file->InputTheory(RatioW_bb_unc);
 RatioW_bb_file->writedata();
 RatioW_bb_file->writetheory();

 FileForEPUMP *RatioW_AllFlavor_file = new FileForEPUMP("RatioW_AllFlavor");
 RatioW_AllFlavor_file->InputData(RatioW_AllFlavors.at(0));
 RatioW_AllFlavor_file->InputTheory(RatioW_AllFlavor_unc);
 RatioW_AllFlavor_file->writedata();
 RatioW_AllFlavor_file->writetheory();

 FileForEPUMP *BoostAsymmetry_uu_file = new FileForEPUMP("BoostAsymmetry_uu");
 BoostAsymmetry_uu_file->InputData(BoostAsymmetry_uus.at(0));
 BoostAsymmetry_uu_file->InputTheory(BoostAsymmetry_uu_unc);
 BoostAsymmetry_uu_file->writedata();
 BoostAsymmetry_uu_file->writetheory();

 FileForEPUMP *BoostAsymmetry_dd_file = new FileForEPUMP("BoostAsymmetry_dd");
 BoostAsymmetry_dd_file->InputData(BoostAsymmetry_dds.at(0));
 BoostAsymmetry_dd_file->InputTheory(BoostAsymmetry_dd_unc);
 BoostAsymmetry_dd_file->writedata();
 BoostAsymmetry_dd_file->writetheory();

 FileForEPUMP *BoostAsymmetry_ss_file = new FileForEPUMP("BoostAsymmetry_ss");
 BoostAsymmetry_ss_file->InputData(BoostAsymmetry_sss.at(0));
 BoostAsymmetry_ss_file->InputTheory(BoostAsymmetry_ss_unc);
 BoostAsymmetry_ss_file->writedata();
 BoostAsymmetry_ss_file->writetheory();

 FileForEPUMP *BoostAsymmetry_cc_file = new FileForEPUMP("BoostAsymmetry_cc");
 BoostAsymmetry_cc_file->InputData(BoostAsymmetry_ccs.at(0));
 BoostAsymmetry_cc_file->InputTheory(BoostAsymmetry_cc_unc);
 BoostAsymmetry_cc_file->writedata();
 BoostAsymmetry_cc_file->writetheory();

 FileForEPUMP *BoostAsymmetry_bb_file = new FileForEPUMP("BoostAsymmetry_bb");
 BoostAsymmetry_bb_file->InputData(BoostAsymmetry_bbs.at(0));
 BoostAsymmetry_bb_file->InputTheory(BoostAsymmetry_bb_unc);
 BoostAsymmetry_bb_file->writedata();
 BoostAsymmetry_bb_file->writetheory();

 FileForEPUMP *BoostAsymmetry_AllFlavor_file = new FileForEPUMP("BoostAsymmetry_AllFlavor");
 BoostAsymmetry_AllFlavor_file->InputData(BoostAsymmetry_AllFlavors.at(0));
 BoostAsymmetry_AllFlavor_file->InputTheory(BoostAsymmetry_AllFlavor_unc);
 BoostAsymmetry_AllFlavor_file->writedata();
 BoostAsymmetry_AllFlavor_file->writetheory();

 FileForEPUMP *BoostAsymmetryW_uu_file = new FileForEPUMP("BoostAsymmetryW_uu");
 BoostAsymmetryW_uu_file->InputData(BoostAsymmetryW_uus.at(0));
 BoostAsymmetryW_uu_file->InputTheory(BoostAsymmetryW_uu_unc);
 BoostAsymmetryW_uu_file->writedata();
 BoostAsymmetryW_uu_file->writetheory();

 FileForEPUMP *BoostAsymmetryW_dd_file = new FileForEPUMP("BoostAsymmetryW_dd");
 BoostAsymmetryW_dd_file->InputData(BoostAsymmetryW_dds.at(0));
 BoostAsymmetryW_dd_file->InputTheory(BoostAsymmetryW_dd_unc);
 BoostAsymmetryW_dd_file->writedata();
 BoostAsymmetryW_dd_file->writetheory();

 FileForEPUMP *BoostAsymmetryW_ss_file = new FileForEPUMP("BoostAsymmetryW_ss");
 BoostAsymmetryW_ss_file->InputData(BoostAsymmetryW_sss.at(0));
 BoostAsymmetryW_ss_file->InputTheory(BoostAsymmetryW_ss_unc);
 BoostAsymmetryW_ss_file->writedata();
 BoostAsymmetryW_ss_file->writetheory();

 FileForEPUMP *BoostAsymmetryW_cc_file = new FileForEPUMP("BoostAsymmetryW_cc");
 BoostAsymmetryW_cc_file->InputData(BoostAsymmetryW_ccs.at(0));
 BoostAsymmetryW_cc_file->InputTheory(BoostAsymmetryW_cc_unc);
 BoostAsymmetryW_cc_file->writedata();
 BoostAsymmetryW_cc_file->writetheory();

 FileForEPUMP *BoostAsymmetryW_bb_file = new FileForEPUMP("BoostAsymmetryW_bb");
 BoostAsymmetryW_bb_file->InputData(BoostAsymmetryW_bbs.at(0));
 BoostAsymmetryW_bb_file->InputTheory(BoostAsymmetryW_bb_unc);
 BoostAsymmetryW_bb_file->writedata();
 BoostAsymmetryW_bb_file->writetheory();

 FileForEPUMP *BoostAsymmetryW_AllFlavor_file = new FileForEPUMP("BoostAsymmetryW_AllFlavor");
 BoostAsymmetryW_AllFlavor_file->InputData(BoostAsymmetryW_AllFlavors.at(0));
 BoostAsymmetryW_AllFlavor_file->InputTheory(BoostAsymmetryW_AllFlavor_unc);
 BoostAsymmetryW_AllFlavor_file->writedata();
 BoostAsymmetryW_AllFlavor_file->writetheory();


 cout<<"Ratio uu:"<<endl;
 for(int ibin = 1; ibin <= Ratio_uus.at(0)->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<Ratio_uus.at(0)->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<Ratio_uus.at(0)->GetBinError(ibin);
   cout<<"(stat) +- ";
   cout<<fixed<<setprecision(3)<<Ratio_uu_Error->GetBinContent(ibin)<<"(pdf)  ";
 }
 cout<<endl;

 cout<<"Ratio dd:"<<endl;
 for(int ibin = 1; ibin <= Ratio_dds.at(0)->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<Ratio_dds.at(0)->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<Ratio_dds.at(0)->GetBinError(ibin);
   cout<<"(stat) +- ";
   cout<<fixed<<setprecision(3)<<Ratio_dd_Error->GetBinContent(ibin)<<"(pdf)  ";
 }
 cout<<endl;

 cout<<"Ratio ss:"<<endl;
 for(int ibin = 1; ibin <= Ratio_sss.at(0)->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<Ratio_sss.at(0)->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<Ratio_sss.at(0)->GetBinError(ibin);
   cout<<"(stat) +- ";
   cout<<fixed<<setprecision(3)<<Ratio_ss_Error->GetBinContent(ibin)<<"(pdf)  ";
 }
 cout<<endl;

 cout<<"Ratio cc:"<<endl;
 for(int ibin = 1; ibin <= Ratio_ccs.at(0)->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<Ratio_ccs.at(0)->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<Ratio_ccs.at(0)->GetBinError(ibin);
   cout<<"(stat) +- ";
   cout<<fixed<<setprecision(3)<<Ratio_cc_Error->GetBinContent(ibin)<<"(pdf)  ";
 }
 cout<<endl;

 cout<<"Ratio bb:"<<endl;
 for(int ibin = 1; ibin <= Ratio_bbs.at(0)->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<Ratio_bbs.at(0)->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<Ratio_bbs.at(0)->GetBinError(ibin);
   cout<<"(stat) +- ";
   cout<<fixed<<setprecision(3)<<Ratio_bb_Error->GetBinContent(ibin)<<"(pdf)  ";
 }
 cout<<endl;

 cout<<"Ratio AllFlavor:"<<endl;
 for(int ibin = 1; ibin <= Ratio_AllFlavors.at(0)->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<Ratio_AllFlavors.at(0)->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<Ratio_AllFlavors.at(0)->GetBinError(ibin);
   cout<<"(stat) +- ";
   cout<<fixed<<setprecision(3)<<Ratio_AllFlavor_Error->GetBinContent(ibin)<<"(pdf)  ";
 }
 cout<<endl;


 writefile->cd();
 writefile->Write();

 return 1;

}
