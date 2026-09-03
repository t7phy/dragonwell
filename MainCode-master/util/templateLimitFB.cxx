#include <BAT/BCGaussianPrior.h>
#include <BAT/BCLog.h>
#include <BAT/BCAux.h>
#include <BATHelper/BCSummaryPriorModel.h>
#include <BATHelper/BCModelOutput.h>
#include <BAT/BCH1D.h>
#include <BAT/BCPriorModel.h>

#include <BATHelper/BCMTFAnalysisFacility.h>
#include <BATHelper/BCMultiTemplateFitter.h>
#include <BATHelper/BCChannel.h>
#include <BATHelper/BCSummaryTool.h>

#include "ePumpHelper/ePumpHelper.h"

#include <TROOT.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TF1.h>
#include <TGraph.h>
#include <TDirectory.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <stdlib.h>

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::string;

int main(int argc, char ** argv)
{
  int iOperator = stoi(argv[5]);
  vector<TString> Operator(9);
  Operator[1] = "ceuRe1111";
  Operator[2] = "cedRe1111";
  Operator[3] = "cluRe1111";
  Operator[4] = "cldRe1111";
  Operator[5] = "clq1Re1111";
  Operator[6] = "clq3Re1111";
  Operator[7] = "cqeRe1111";
  Operator[8] = "cllRe1111";


  TFile* file_ee = new TFile("MC_results.root");
  TFile* file_data = new TFile("MC_results.root");
//  TFile* file_data = new TFile("MC_results_SMEFT_cqlm1_c_0.0.root");
//  TFile* file_data = new TFile("MC_results_SM.root");

  TFile* file_function = new TFile("Parameterize.root");


  TH1D h_F_bkg = *((TH1D*) file_ee->Get("CrossSectionF_Pseudodata"));
  TH1D h_B_bkg = *((TH1D*) file_ee->Get("CrossSectionB_Pseudodata"));

  TH1D h_F_data = *((TH1D*) file_data->Get("CrossSectionF_Pseudodata"));
  TH1D h_B_data = *((TH1D*) file_data->Get("CrossSectionB_Pseudodata"));

///////////////////////////////////////////////////////////////////////////////////////////

  bool doSys = stoi(argv[1]);
  Double_t LumiFactor = stod(argv[2]);
  double DummyPDFUnc;
  int isUpdate;

  cout<<"doSys set to "<<doSys<<endl;
  cout<<"LumiFactor set to "<<LumiFactor<<endl;

  if(doSys){
    isUpdate = stoi(argv[3]);
    DummyPDFUnc = stod(argv[4]);
    cout<<"isUpdate set to "<<isUpdate<<endl;
    cout<<"DummyPDFUnc set to "<<DummyPDFUnc<<endl;
  }

  cout<<"Operator set to "<<Operator[iOperator]<<endl;

  TH1D h_F_sys = *((TH1D*) file_data->Get("CrossSectionF_Pseudodata"));
  TH1D h_B_sys = *((TH1D*) file_data->Get("CrossSectionB_Pseudodata"));

  if(doSys){
    ePumpHelper* EU = new ePumpHelper("test");
    EU->TurnOffCorrelationCosine();
    EU->Initial();
    EU->Update();

    TH1D* OldPDFErrorF = EU->ConstructOldPDFErrorHist("test/CrossSectionF", "", "Relative");
    TH1D* NewPDFErrorF = EU->ConstructNewPDFErrorHist("test/CrossSectionF", "", "Relative");
    TH1D* PDFErrorF;
    if(isUpdate) PDFErrorF = NewPDFErrorF;
    else if(!isUpdate) PDFErrorF = OldPDFErrorF;

    TH1D* OldPDFErrorB = EU->ConstructOldPDFErrorHist("test/CrossSectionB", "", "Relative");
    TH1D* NewPDFErrorB = EU->ConstructNewPDFErrorHist("test/CrossSectionB", "", "Relative");
    TH1D* PDFErrorB;
    if(isUpdate) PDFErrorB = NewPDFErrorB;
    else if(!isUpdate) PDFErrorB = OldPDFErrorB;

    for (int i = 1; i <= h_F_sys.GetNbinsX(); i++){
      h_F_sys.SetBinContent(i, PDFErrorF->GetBinContent(i) * DummyPDFUnc);
      h_B_sys.SetBinContent(i, PDFErrorB->GetBinContent(i) * DummyPDFUnc);
      cout<<"ibin "<<i<<": OldPDFErrorF = "<<OldPDFErrorF->GetBinContent(i)<<" NewPDFErrorF = "<<NewPDFErrorF->GetBinContent(i)<<" CurrentPDFErrorF = "<<PDFErrorF->GetBinContent(i)<<endl;
      cout<<"ibin "<<i<<": OldPDFErrorB = "<<OldPDFErrorB->GetBinContent(i)<<" NewPDFErrorB = "<<NewPDFErrorB->GetBinContent(i)<<" CurrentPDFErrorB = "<<PDFErrorB->GetBinContent(i)<<endl;
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////

  Double_t kFactor = 84.0;

  h_F_bkg.Scale(LumiFactor);
  h_B_bkg.Scale(LumiFactor);
  h_F_data.Scale(LumiFactor);
  h_B_data.Scale(LumiFactor);

  vector<TF1*>* F_funct_vector=new vector<TF1*>(h_F_bkg.GetNbinsX());
  vector<TF1*>* B_funct_vector=new vector<TF1*>(h_B_bkg.GetNbinsX());

  F_funct_vector->at(0) = (TF1 *)file_function->Get((TString)"CrossSectionF_1000_1300_" + Operator[iOperator] + (TString)"_Fitting");
  F_funct_vector->at(1) = (TF1 *)file_function->Get((TString)"CrossSectionF_1300_1800_" + Operator[iOperator] + (TString)"_Fitting");
  F_funct_vector->at(2) = (TF1 *)file_function->Get((TString)"CrossSectionF_1800_2500_" + Operator[iOperator] + (TString)"_Fitting");
  F_funct_vector->at(3) = (TF1 *)file_function->Get((TString)"CrossSectionF_2500_3200_" + Operator[iOperator] + (TString)"_Fitting");
  F_funct_vector->at(4) = (TF1 *)file_function->Get((TString)"CrossSectionF_3200_4000_" + Operator[iOperator] + (TString)"_Fitting");
  F_funct_vector->at(5) = (TF1 *)file_function->Get((TString)"CrossSectionF_4000_5000_" + Operator[iOperator] + (TString)"_Fitting");

  B_funct_vector->at(0) = (TF1 *)file_function->Get((TString)"CrossSectionB_1000_1300_" + Operator[iOperator] + (TString)"_Fitting");
  B_funct_vector->at(1) = (TF1 *)file_function->Get((TString)"CrossSectionB_1300_1800_" + Operator[iOperator] + (TString)"_Fitting");
  B_funct_vector->at(2) = (TF1 *)file_function->Get((TString)"CrossSectionB_1800_2500_" + Operator[iOperator] + (TString)"_Fitting");
  B_funct_vector->at(3) = (TF1 *)file_function->Get((TString)"CrossSectionB_2500_3200_" + Operator[iOperator] + (TString)"_Fitting");
  B_funct_vector->at(4) = (TF1 *)file_function->Get((TString)"CrossSectionB_3200_4000_" + Operator[iOperator] + (TString)"_Fitting");
  B_funct_vector->at(5) = (TF1 *)file_function->Get((TString)"CrossSectionB_4000_5000_" + Operator[iOperator] + (TString)"_Fitting");

  for(int i = 0; i < F_funct_vector->size(); i++){
    F_funct_vector->at(i)->SetParameter(0, F_funct_vector->at(i)->GetParameter(0) * LumiFactor);
    F_funct_vector->at(i)->SetParameter(1, F_funct_vector->at(i)->GetParameter(1) * LumiFactor);
    F_funct_vector->at(i)->SetParameter(2, F_funct_vector->at(i)->GetParameter(2) * LumiFactor);
    B_funct_vector->at(i)->SetParameter(0, B_funct_vector->at(i)->GetParameter(0) * LumiFactor);
    B_funct_vector->at(i)->SetParameter(1, B_funct_vector->at(i)->GetParameter(1) * LumiFactor);
    B_funct_vector->at(i)->SetParameter(2, B_funct_vector->at(i)->GetParameter(2) * LumiFactor);

    //ignore the offset term
    F_funct_vector->at(i)->SetParameter(2, 0.0);
    B_funct_vector->at(i)->SetParameter(2, 0.0);
    /////////////////////////////////////////////

    cout<<"ibin: "<<i + 1<<" Parameter 1: "<<F_funct_vector->at(i)->GetParameter(0)<<" Parameter 2: "<<F_funct_vector->at(i)->GetParameter(1)<<" Parameter 3: "<<F_funct_vector->at(i)->GetParameter(2)<<endl;
    cout<<"ibin: "<<i + 1<<" Parameter 1: "<<B_funct_vector->at(i)->GetParameter(0)<<" Parameter 2: "<<B_funct_vector->at(i)->GetParameter(1)<<" Parameter 3: "<<B_funct_vector->at(i)->GetParameter(2)<<endl;

  }

  int ThetaBins = 2000;
  double maxTheta = 1.0;

  bool doMCMC = true;

  //################################################################################################################################
  // ----------------------------------------------------
  // configure BAT
  // ----------------------------------------------------
  // set nice style for drawing than the ROOT default
  BCAux::SetStyle();
  // open log file
  BCLog::OpenLog("log.txt");
  BCLog::SetLogLevel(BCLog::summary);

  // ----------------------------------------------------
  // Normalization
  // ----------------------------------------------------
  double NFbkg = h_F_bkg.Integral();
  double NBbkg = h_B_bkg.Integral();
  double NFbkgError;
  double NBbkgError;

  h_F_bkg.IntegralAndError(1, h_F_bkg.GetNbinsX(), NFbkgError);
  h_B_bkg.IntegralAndError(1, h_B_bkg.GetNbinsX(), NBbkgError);


  // ----------------------------------------------------
  // create new BCMultiTemplateFitter object
  // ----------------------------------------------------
  BCMultiTemplateFitter * m = new BCMultiTemplateFitter();

  m->SetPrecision(BCEngineMCMC::kMedium);

  BCLog::OutSummary("Test model created");

  // create a new summary tool object
  BCSummaryTool * summary = new BCSummaryTool(m);

  // ----------------------------------------------------
  // Define required input
  // ----------------------------------------------------

  std::cerr<<"maxTheta "<<maxTheta<<std::endl;

  m->AddChannel("F");
  m->AddChannel("B");

  m->AddProcess("FBkg", NFbkg - NFbkgError, NFbkg + NFbkgError);
  m->SetPriorGauss("FBkg", NFbkg, NFbkgError);

  m->AddProcess("BBkg", NBbkg - NBbkgError, NBbkg + NBbkgError);
  m->SetPriorGauss("BBkg", NBbkg, NBbkgError);

  m->AddProcess("Theta",   0., maxTheta);
  m->SetPriorConstant("Theta");

  m->SetData("F", h_F_data);
  m->SetData("B", h_B_data);

  m->SetTemplate("F", "FBkg", h_F_bkg, 1.0);
  m->SetTemplate("B", "BBkg", h_B_bkg, 1.0);

  m->SetTemplate("F", "Theta", F_funct_vector, F_funct_vector->size(), 1.0);
  m->SetTemplate("B", "Theta", B_funct_vector, B_funct_vector->size(), 1.0);

  m->GetChannel(0)->SetFlagChannelActive(true);
  m->GetChannel(1)->SetFlagChannelActive(true);

  m->AddAFBPenalty("F", "B");

///////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////
  //  Systematic  //
  //////////////////

  if(doSys){
    m->AddSystematic("PDF_VAR1", -5.0, 5.0); 
    m->SetPriorGauss("PDF_VAR1", 0.0, 1.0);
    //m->GetParameters().Back().SetPrior(new BCGaussianPrior(0.0, 1.0));

    m->SetSystematicVariation("F", "FBkg", "PDF_VAR1", h_F_sys, h_F_sys);
    m->SetSystematicVariation("B", "BBkg", "PDF_VAR1", h_B_sys, h_B_sys);

    for(int ibin = 1; ibin <= h_F_bkg.GetNbinsX(); ibin++){
      cout<<"data: "<<h_F_data.GetBinContent(ibin)<<" bkg: "<<h_F_bkg.GetBinContent(ibin)<<" sys: "<<h_F_sys.GetBinContent(ibin)<<endl;
    }
    for(int ibin = 1; ibin <= h_B_bkg.GetNbinsX(); ibin++){
      cout<<"data: "<<h_B_data.GetBinContent(ibin)<<" bkg: "<<h_B_bkg.GetBinContent(ibin)<<" sys: "<<h_B_sys.GetBinContent(ibin)<<endl;
    }

  }

///////////////////////////////////////////////////////////////////////////////////////////////////


  //increase number of marginalization bins (higher precision) 
  std::cerr<<"ThetaBins "<<ThetaBins<<std::endl;
  m->SetNbins(ThetaBins);

  // ----------------------------------------------------
  // create prior model for pseudo-experiments
  // ----------------------------------------------------

  // create new prior model
  BCSummaryPriorModel* pm = new BCSummaryPriorModel();
//  BCPriorModel* pm = new BCPriorModel(*m);

  // set model (and make adjustment suitable for background only pseudo-experiments (PE))
  m->SetParameterRange(0, NFbkg, NFbkg);
  m->SetParameterRange(1, NBbkg, NBbkg);
  if(!doSys) m->SetParameterRange(2, 0.0, 1e-20);//set Theta to zero here (flat prior would incl Theta in PE)
  if(doSys) m->SetParameterRange(2, 0.0, 1e-20);
  pm->SetModel(m);

  // ----------------------------------------------------
  // create output object
  // ----------------------------------------------------
  BCModelOutput* pmout = new BCModelOutput(pm, "prior.root");

  // switch writing of Markov Chains on
  pmout->WriteMarkovChain(true);

  // set precision
  pm->SetPrecision(BCEngineMCMC::kMedium);

 // perform marginalization
  pm->MarginalizeAll();
  pm->FindMode(pm->GetBestFitParameters());
  //pm->PrintAllMarginalized(pm->GetSafeName() + "_plots.pdf");
  //pm->PrintParameterPlot(pm->GetSafeName() + "_parameters.pdf");
  //pm->PrintCorrelationPlot(pm->GetSafeName() + "_correlation.pdf");
  //pm->PrintCorrelationMatrix(pm->GetSafeName() + "_correlationMatrix.pdf");
  //pm->PrintKnowledgeUpdatePlots(pm->GetSafeName() + "_update.pdf");

  std::vector<double> bestfit_parameters = m->GetBestFitParameters();
  for(int i = 0; i < bestfit_parameters.size(); i++){
    cout<<"bestfit_parameters: "<<bestfit_parameters.at(i)<<endl;
  }

  // get tree
  TTree* priortree = (TTree*) pmout->GetMarkovChainTree();

  //undo PE modifications
  m->SetParameterRange(0, NFbkg, NFbkg);
  m->SetParameterRange(1, NBbkg, NBbkg);
  m->SetParameterRange(2, 0.0, maxTheta);

  // ----------------------------------------------------------------
  // Perform ensemble test
  // ----------------------------------------------------------------

  // create new analysis facility
  BCMTFAnalysisFacility* facility = new BCMTFAnalysisFacility(m);
  facility->SetFlagMCMC(doMCMC);

  TFile *file = new TFile("zprime_ensembles_mass.root", "RECREATE");
  file->cd();

  // create ensembles
  cout<<"Start Building ensemble:"<<endl;

  int nEnsemble = 1000;

  //double ThirdPar = stod(argv[5]);
  //bestfit_parameters = {Neebkg, 0.0, ThirdPar};
  //TTree* tree = facility->BuildEnsembles( bestfit_parameters, 10000 );//yfu
  TTree* tree = facility->BuildEnsembles( priortree, 10000 );
  tree->Write();

  std::vector<int> details;
  details.push_back(0);
  details.push_back(0);
  //details.push_back(0);
  details.push_back(1);

  // run ensemble test
  cout<<"Start ensemble test:"<<endl;
  TTree* tree_out = facility->PerformEnsembleTest(tree, nEnsemble, details);

  // write trees into file
  tree_out->Write();

  // close file
  file->Close();

  // free memory
  delete file;

  // close log file
  BCLog::CloseLog();

  // close output file
  pmout->Close();

  // free memory
  delete pm;
  delete pmout;
  delete facility;
  delete m;
  delete summary;




  BCLog::OutSummary("Test program ran successfully");
  BCLog::OutSummary("Exiting");


 return 1;
}

