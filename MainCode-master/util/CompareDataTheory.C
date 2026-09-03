#include "Tools/Tools.h"
#include "CompareDataTheory/CompareDataTheory.h"

using namespace std;

int main(int argc, char** argv)
{
 CompareDataTheory run;
 run.Output();
// run.MakeSysUnCorr();
 run.OpenFile("Results.root");

// double xbins[11] = {66, 71, 76, 81, 86, 91, 96, 101, 106, 111, 116};
 double xbins[7] = {75, 80, 85, 90, 95, 100, 105};
 TFile* DataFile = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/Data_FSROff/BayesUnfold_CCZee.root");
 TFile* DataFileZmm = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/Data_FSROff/BayesUnfold_Zmm.root");
 TFile* TheoryFile[100];
 TFile* TheoryCorrelationFile;

 TH1D* DataPlot;
 TH1D* DataPlotZmm;
 TH1D* DataError[100];
 TH1D* DataErrorZmm[100];
 TH1D* MCTruthPlot;
 TH1D* MCRecoPlot;
 TH1D* MCTruthPlotZmm;
 TH1D* MCRecoPlotZmm;
 TH2D* DataCorrelation[100];
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
// DataPlot = (TH1D *)DataFile->Get("Data_AFB");
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


 run.InputDataCentral(DataPlot);
// run.InputDataStaErr(DataError[1]);
 run.InputDataStaCorrelation(DataCorrelation[1], DataError[1]);
 run.InputDataStaCorrelation(DataCorrelation[2], DataError[2]);
// run.InputDataSysErr(v_DataSysErr);
 run.GetTotalDataCovariance();

// run.InputDataCentral(DataPlotZmm);
// run.InputDataStaCorrelation(DataCorrelationZmm[1], DataErrorZmm[1]);
// run.InputDataStaCorrelation(DataCorrelationZmm[2], DataErrorZmm[2]);
// run.InputDataSysErr(v_DataSysErrZmm);
// run.GetTotalDataCovariance();

///////////////////////////////////////////////////////////////////////////////////////////////////




//      Theory      //
 TheoryPlot[1] = MCTruthPlot;

 TheoryFile[2] = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/rootfile/ResBos_FSROff/MC_results.root");
 TheoryFile[3] = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/rootfile/Pythia_FSROff/NNPDF31_nnlo_as_0118_13TeV_Legacy_w321_y1/NNPDF_0000/JOB1/MC_results.root");
 TheoryFile[4] = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/rootfile/HERWIG_FSROff/MC_results.root");
 TheoryFile[5] = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/rootfile/ResBos_FSROff/MC_results.root");
 TheoryFile[6] = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/rootfile/Pythia_Template/0.2315/MC_results.root");
 TheoryFile[7] = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/rootfile/ResBos_Template/Template_CT14HERA2NNLO/0.2315/MC_results.root");
 TheoryFile[8] = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/rootfile/ResBos_ZFitter_cwang/MC_results.root");
 TheoryFile[9] = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/rootfile/ResBos_yao_old/MC_results.root");

 TheoryFZmass[2] = (TH1D *)TheoryFile[2]->Get("FZmass_CC");
 TheoryBZmass[2] = (TH1D *)TheoryFile[2]->Get("BZmass_CC");
 TheoryFZmass[2] = (TH1D *)TheoryFZmass[2]->Rebin(6, "FZmass_CC_2", xbins);
 TheoryBZmass[2] = (TH1D *)TheoryBZmass[2]->Rebin(6, "BZmass_CC_2", xbins);
 TheoryPlot[2] = (TH1D *)TheoryFZmass[2]->Clone((TString)"TheoryPlot_2");
 TheoryPlot[2]->Reset();
 AFBFunction(TheoryFZmass[2], TheoryBZmass[2], TheoryPlot[2]);

 TheoryFZmass[3] = (TH1D *)TheoryFile[3]->Get("FZmass_CC");
 TheoryBZmass[3] = (TH1D *)TheoryFile[3]->Get("BZmass_CC");
 TheoryFZmass[3] = (TH1D *)TheoryFZmass[3]->Rebin(6, "FZmass_CC_3", xbins);
 TheoryBZmass[3] = (TH1D *)TheoryBZmass[3]->Rebin(6, "BZmass_CC_3", xbins);
 TheoryPlot[3] = (TH1D *)TheoryFZmass[3]->Clone((TString)"TheoryPlot_3");
 TheoryPlot[3]->Reset();
 AFBFunction(TheoryFZmass[3], TheoryBZmass[3], TheoryPlot[3]);

 TheoryFZmass[4] = (TH1D *)TheoryFile[4]->Get("FZmass_CC");
 TheoryBZmass[4] = (TH1D *)TheoryFile[4]->Get("BZmass_CC");
 TheoryFZmass[4] = (TH1D *)TheoryFZmass[4]->Rebin(6, "FZmass_CC_4", xbins);
 TheoryBZmass[4] = (TH1D *)TheoryBZmass[4]->Rebin(6, "BZmass_CC_4", xbins);
 TheoryPlot[4] = (TH1D *)TheoryFZmass[4]->Clone((TString)"TheoryPlot_4");
 TheoryPlot[4]->Reset();
 AFBFunction(TheoryFZmass[4], TheoryBZmass[4], TheoryPlot[4]);

 TheoryFZmass[6] = (TH1D *)TheoryFile[6]->Get("FZmass_CC");
 TheoryBZmass[6] = (TH1D *)TheoryFile[6]->Get("BZmass_CC");
 TheoryFZmass[6] = (TH1D *)TheoryFZmass[6]->Rebin(6, "FZmass_CC_6", xbins);
 TheoryBZmass[6] = (TH1D *)TheoryBZmass[6]->Rebin(6, "BZmass_CC_6", xbins);
 TheoryPlot[6] = (TH1D *)TheoryFZmass[6]->Clone((TString)"TheoryPlot_6");
 TheoryPlot[6]->Reset();
 AFBFunction(TheoryFZmass[6], TheoryBZmass[6], TheoryPlot[6]);

 TheoryFZmass[7] = (TH1D *)TheoryFile[7]->Get("FZmass_CC");
 TheoryBZmass[7] = (TH1D *)TheoryFile[7]->Get("BZmass_CC");
 TheoryFZmass[7] = (TH1D *)TheoryFZmass[7]->Rebin(6, "FZmass_CC_7", xbins);
 TheoryBZmass[7] = (TH1D *)TheoryBZmass[7]->Rebin(6, "BZmass_CC_7", xbins);
 TheoryPlot[7] = (TH1D *)TheoryFZmass[7]->Clone((TString)"TheoryPlot_7");
 TheoryPlot[7]->Reset();
 AFBFunction(TheoryFZmass[7], TheoryBZmass[7], TheoryPlot[7]);

 TheoryFZmass[8] = (TH1D *)TheoryFile[8]->Get("FZmass_CC");
 TheoryBZmass[8] = (TH1D *)TheoryFile[8]->Get("BZmass_CC");
 TheoryFZmass[8] = (TH1D *)TheoryFZmass[8]->Rebin(6, "FZmass_CC_8", xbins);
 TheoryBZmass[8] = (TH1D *)TheoryBZmass[8]->Rebin(6, "BZmass_CC_8", xbins);
 TheoryPlot[8] = (TH1D *)TheoryFZmass[8]->Clone((TString)"TheoryPlot_8");
 TheoryPlot[8]->Reset();
 AFBFunction(TheoryFZmass[8], TheoryBZmass[8], TheoryPlot[8]);

 TheoryFZmass[9] = (TH1D *)TheoryFile[9]->Get("FZmass_CC");
 TheoryBZmass[9] = (TH1D *)TheoryFile[9]->Get("BZmass_CC");
 TheoryFZmass[9] = (TH1D *)TheoryFZmass[9]->Rebin(6, "FZmass_CC_9", xbins);
 TheoryBZmass[9] = (TH1D *)TheoryBZmass[9]->Rebin(6, "BZmass_CC_9", xbins);
 TheoryPlot[9] = (TH1D *)TheoryFZmass[9]->Clone((TString)"TheoryPlot_9");
 TheoryPlot[9]->Reset();
 AFBFunction(TheoryFZmass[9], TheoryBZmass[9], TheoryPlot[9]);

// using theory as pseudodata for test
// run.InputDataCentral(TheoryPlot[8], 1);
// run.GetTotalDataCovariance();

 for(int i = 1; i <= 4; i++){
   v_TheoryPlotList.push_back(TheoryPlot[i]);
 }

 TheoryCorrelationFile = new TFile("/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/rootfile/Pythia_FSROff/AFB_PDFError_MonteCarlo.root");
 TheoryCovariance = (TH2D *)TheoryCorrelationFile->Get("CovMatrix_PDFError");

 TFile *TheoryCT10PDFUncFile = new TFile("/lustre/AtlUser/yfu/pku_resbos/CT14HERA2NNLO_13TeV/rootfile/Pythia/rootfile/AFB_PDFError_Symmetry.root");
 TH1D *TheoryCT10PDFUnc = (TH1D *)TheoryCT10PDFUncFile->Get("AFB_PDFError");


 run.InputTheoryCentral(v_TheoryPlotList);
// run.InputTheoryPDFCovariance(TheoryCovariance);
 run.GetTotalTheoryCovariance();
 run.GetChi2();

/////////////////////////////////////////////////////////////////////////////////////////////////////

 double ZPole[2] = {80.0, 100.0};

 for(int i = 0; i < 40; i++){
   int stw = 2255 + i * 3;
   TemplateFile[i] = new TFile((TString)"/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/rootfile/ResBos_Template/Template_CT10/0." + (int)stw + (TString)"/MC_results.root");
//   TemplateFile[i] = new TFile((TString)"/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/rootfile/ResBos_Template/Template_CT14HERA2NNLO/0." + (int)stw + (TString)"/MC_results.root");
//   TemplateFile[i] = new TFile((TString)"/lustre/AtlUser/yfu/ATLASUnfoldingMCSample/rootfile/Pythia_Template/0." + (int)stw + (TString)"/MC_results.root");
   TemplateFZmass[i] = (TH1D *)TemplateFile[i]->Get("FZmass_CC");
   TemplateBZmass[i] = (TH1D *)TemplateFile[i]->Get("BZmass_CC");
   TemplateFZmass[i] = (TH1D *)TemplateFZmass[i]->Rebin(6, (TString)"FZmass_CC_Template_" + (int)i, xbins);
   TemplateBZmass[i] = (TH1D *)TemplateBZmass[i]->Rebin(6, (TString)"BZmass_CC_Template_" + (int)i, xbins);
   TheoryTemplate[i] = (TH1D *)TemplateFZmass[i]->Clone((TString)"AFB_Template_CC_" + (int)(i + 1));
   TheoryTemplate[i]->Reset();
   AFBFunction(TemplateFZmass[i], TemplateBZmass[i], TheoryTemplate[i]);
   v_TheoryTemplate.push_back(TheoryTemplate[i]);

   TemplateFZmassZPole[i] = (TH1D *)TemplateFZmass[i]->Rebin(1, (TString)"ZPoleFZmass_CC_Template_" + (int)i, ZPole);
   TemplateBZmassZPole[i] = (TH1D *)TemplateBZmass[i]->Rebin(1, (TString)"ZPoleBZmass_CC_Template_" + (int)i, ZPole);
   AFBFunction(TemplateFZmassZPole[i], TemplateBZmassZPole[i], TheoryTemplateZPole[i]);
   v_TheoryTemplateZPole.push_back(TheoryTemplateZPole[i]);

 }
 run.InputTemplateRange(40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);
 run.InputTheoryTemplate(v_TheoryTemplate);
 run.FitAFBStw(v_TheoryTemplateZPole);

 run.Save();


 return 1;
}
