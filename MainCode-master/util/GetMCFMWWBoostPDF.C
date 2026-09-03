#include "ReadInRoot/MCFMWWBoost.h"
#include "Uncertainty/PDFUncertainty.h"
#include "FileForEPUMP/FileForEPUMP.h"

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"usage: ./GetMCFMWWBoostPDF results"<<endl;
   return 0;
 }

 HistsResBos* myhists = new HistsResBos();
 myhists->openFile("save.root");

 vector<TH1D *> BoostAsymmetry_AllFlavors;
 vector<TH1D *> BoostAsymmetryW_AllFlavors;

 for(int i = 0; i < 57; i++){
   TString FileName = (TString)argv[1] + (TString)"/WW_lo_13Tev_binned_" + (int)i + (TString)".dat";

   MCFMWWBoost* Run = new MCFMWWBoost();
   Run->LinkHist(myhists);
   Run->InputSubName((TString)"_" + (int)i);

   Run->openFile(FileName);
   Run->GetBinning(FileName, "ElectronEta");
   Run->WriteIn("ElectronEta");

   Run->openFile(FileName);
   Run->GetBinning(FileName, "PositronEta");
   Run->WriteIn("PositronEta");

   Run->openFile(FileName);
   Run->GetBinning(FileName, "WPlusRapidity");
   Run->WriteIn("WPlusRapidity");
 
   Run->openFile(FileName);
   Run->GetBinning(FileName, "WMinusRapidity");
   Run->WriteIn("WMinusRapidity");

   Run->openFile(FileName);
   Run->GetBinning(FileName, "Right");
   Run->WriteIn("Right");

   Run->openFile(FileName);
   Run->GetBinning(FileName, "Wrong");
   Run->WriteIn("Wrong");

   Run->openFile(FileName);
   Run->GetBinning(FileName, "RightW");
   Run->WriteIn("RightW");
 
   Run->openFile(FileName);
   Run->GetBinning(FileName, "WrongW");
   Run->WriteIn("WrongW");

   Run->GetAdditionalPlot();

   BoostAsymmetry_AllFlavors.push_back(Run->BoostAsymmetry);
   BoostAsymmetryW_AllFlavors.push_back(Run->BoostAsymmetryW);
 }

 myhists->hf->cd();

 TH1D* BoostAsymmetry_AllFlavor_Error;
 PDFUncertainty* BoostAsymmetry_AllFlavor_unc = new PDFUncertainty();
 BoostAsymmetry_AllFlavor_unc->Input1DPlot("Symmetry", BoostAsymmetry_AllFlavors, BoostAsymmetry_AllFlavor_Error);

 TH1D* BoostAsymmetryW_AllFlavor_Error;
 PDFUncertainty* BoostAsymmetryW_AllFlavor_unc = new PDFUncertainty();
 BoostAsymmetryW_AllFlavor_unc->Input1DPlot("Symmetry", BoostAsymmetryW_AllFlavors, BoostAsymmetryW_AllFlavor_Error);

 FileForEPUMP* BoostAsymmetry_AllFlavor_file = new FileForEPUMP("BoostAsymmetry_AllFlavor_MCFM");
 BoostAsymmetry_AllFlavor_file->InputData(BoostAsymmetry_AllFlavors.at(0));
 BoostAsymmetry_AllFlavor_file->InputTheory(BoostAsymmetry_AllFlavor_unc);
 BoostAsymmetry_AllFlavor_file->writedata();
 BoostAsymmetry_AllFlavor_file->writetheory();

 FileForEPUMP* BoostAsymmetryW_AllFlavor_file = new FileForEPUMP("BoostAsymmetryW_AllFlavor_MCFM");
 BoostAsymmetryW_AllFlavor_file->InputData(BoostAsymmetryW_AllFlavors.at(0));
 BoostAsymmetryW_AllFlavor_file->InputTheory(BoostAsymmetryW_AllFlavor_unc);
 BoostAsymmetryW_AllFlavor_file->writedata();
 BoostAsymmetryW_AllFlavor_file->writetheory();

// myhists->saveHists();
 myhists->hf->Write();
 myhists->hf->Close();

 return 1;
}
