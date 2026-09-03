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


  TH1D h_ee_bkg = *((TH1D*) file_ee->Get("CrossSection_Pseudodata"));
  TH1D h_mm_bkg = *((TH1D*) file_ee->Get("CrossSection_Pseudodata"));

  TH1D h_ee_data = *((TH1D*) file_data->Get("CrossSection_Pseudodata"));
  TH1D h_mm_data = *((TH1D*) file_data->Get("CrossSection_Pseudodata"));

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

  TH1D h_ee_sys = *((TH1D*) file_data->Get("CrossSection_Pseudodata"));

  if(doSys){
    ePumpHelper* EU = new ePumpHelper("test");
    EU->TurnOffCorrelationCosine();
    EU->Initial();
    EU->Update();
    //TH1D* OldPDFError = EU->ConstructOldPDFErrorHist("test/CrossSection", "", "Relative", 3, 8);
    //TH1D* NewPDFError = EU->ConstructNewPDFErrorHist("test/CrossSection", "", "Relative", 3, 8);
    TH1D* OldPDFError = EU->ConstructOldPDFErrorHist("test/CrossSection", "", "Relative");
    TH1D* NewPDFError = EU->ConstructNewPDFErrorHist("test/CrossSection", "", "Relative");
    TH1D* PDFError;
    if(isUpdate) PDFError = NewPDFError;
    else if(!isUpdate) PDFError = OldPDFError;

    for (int i = 1; i <= h_ee_sys.GetNbinsX(); i++){
      h_ee_sys.SetBinContent(i, PDFError->GetBinContent(i) * DummyPDFUnc);
      //h_ee_sys.SetBinContent(i, DummyPDFUnc * i);
      cout<<"ibin "<<i<<": OldPDFError = "<<OldPDFError->GetBinContent(i)<<" NewPDFError = "<<NewPDFError->GetBinContent(i)<<" CurrentPDFError = "<<PDFError->GetBinContent(i)<<endl;
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////

  Double_t kFactor = 84.0;

  h_ee_bkg.Scale(LumiFactor);
  h_mm_bkg.Scale(LumiFactor);
  h_ee_data.Scale(LumiFactor);
  h_mm_data.Scale(LumiFactor);

  vector<TF1*>* ee_funct_vector=new vector<TF1*>(h_ee_bkg.GetNbinsX());
  vector<TF1*>* mm_funct_vector=new vector<TF1*>(h_mm_bkg.GetNbinsX());

/*  ee_funct_vector->at(0) = (TF1 *)file_function->Get("CrossSection_400_500_cqlm1_Fitting");
  ee_funct_vector->at(1) = (TF1 *)file_function->Get("CrossSection_500_700_cqlm1_Fitting");
  ee_funct_vector->at(2) = (TF1 *)file_function->Get("CrossSection_700_900_cqlm1_Fitting");
  ee_funct_vector->at(3) = (TF1 *)file_function->Get("CrossSection_900_1200_cqlm1_Fitting");
  ee_funct_vector->at(4) = (TF1 *)file_function->Get("CrossSection_1200_1800_cqlm1_Fitting");
  ee_funct_vector->at(5) = (TF1 *)file_function->Get("CrossSection_1800_3000_cqlm1_Fitting");
  ee_funct_vector->at(6) = (TF1 *)file_function->Get("CrossSection_3000_4500_cqlm1_Fitting");
  ee_funct_vector->at(7) = (TF1 *)file_function->Get("CrossSection_4500_6000_cqlm1_Fitting");
*/

/*  ee_funct_vector->at(0) = (TF1 *)file_function->Get("CrossSection_700_900_cqlm1_Fitting");
  ee_funct_vector->at(1) = (TF1 *)file_function->Get("CrossSection_900_1200_cqlm1_Fitting");
  ee_funct_vector->at(2) = (TF1 *)file_function->Get("CrossSection_1200_1800_cqlm1_Fitting");
  ee_funct_vector->at(3) = (TF1 *)file_function->Get("CrossSection_1800_3000_cqlm1_Fitting");
  ee_funct_vector->at(4) = (TF1 *)file_function->Get("CrossSection_3000_4500_cqlm1_Fitting");
  ee_funct_vector->at(5) = (TF1 *)file_function->Get("CrossSection_4500_6000_cqlm1_Fitting");
*/
  ee_funct_vector->at(0) = (TF1 *)file_function->Get((TString)"CrossSection_1000_1300_" + Operator[iOperator] + (TString)"_Fitting");
  ee_funct_vector->at(1) = (TF1 *)file_function->Get((TString)"CrossSection_1300_1800_" + Operator[iOperator] + (TString)"_Fitting");
  ee_funct_vector->at(2) = (TF1 *)file_function->Get((TString)"CrossSection_1800_2500_" + Operator[iOperator] + (TString)"_Fitting");
  ee_funct_vector->at(3) = (TF1 *)file_function->Get((TString)"CrossSection_2500_3200_" + Operator[iOperator] + (TString)"_Fitting");
  ee_funct_vector->at(4) = (TF1 *)file_function->Get((TString)"CrossSection_3200_4000_" + Operator[iOperator] + (TString)"_Fitting");
  ee_funct_vector->at(5) = (TF1 *)file_function->Get((TString)"CrossSection_4000_5000_" + Operator[iOperator] + (TString)"_Fitting");

  for(int i = 0; i < ee_funct_vector->size(); i++){
    ee_funct_vector->at(i)->SetParameter(0, ee_funct_vector->at(i)->GetParameter(0) * LumiFactor);
    ee_funct_vector->at(i)->SetParameter(1, ee_funct_vector->at(i)->GetParameter(1) * LumiFactor);
    ee_funct_vector->at(i)->SetParameter(2, ee_funct_vector->at(i)->GetParameter(2) * LumiFactor);

    //ignore the offset term
    ee_funct_vector->at(i)->SetParameter(2, 0.0);

    //ignore the linear term
    ee_funct_vector->at(i)->SetParameter(1, 0.0);
    /////////////////////////////////////////////

    cout<<"ibin: "<<i + 1<<" Parameter 1: "<<ee_funct_vector->at(i)->GetParameter(0)<<" Parameter 2: "<<ee_funct_vector->at(i)->GetParameter(1)<<" Parameter 3: "<<ee_funct_vector->at(i)->GetParameter(2)<<endl;
  }

  mm_funct_vector = ee_funct_vector;

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
  double Neebkg = h_ee_bkg.Integral();
  double Nmmbkg = h_mm_bkg.Integral();
  double NeebkgError;
  double NmmbkgError;

  h_ee_bkg.IntegralAndError(1, h_ee_bkg.GetNbinsX(), NeebkgError);
  h_mm_bkg.IntegralAndError(1, h_mm_bkg.GetNbinsX(), NmmbkgError);


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

  m->AddChannel("ee");
  //m->AddChannel("mm");

  m->AddProcess("eeBkg", Neebkg - NeebkgError, Neebkg + NeebkgError);
  m->SetPriorGauss("eeBkg", Neebkg, NeebkgError);

  //m->AddProcess("mmBkg", Nmmbkg, Nmmbkg);
  //m->SetPriorGauss("mmBkg", Nmmbkg, sqrt(Neebkg));

  m->AddProcess("Theta",   0., maxTheta);
  m->SetPriorConstant("Theta");

  m->SetData("ee", h_ee_data);
  //m->SetData("mm", h_mm_data);

  TH1D h_ee_dummy = TH1D((h_ee_data));
  for(int ibin=0;ibin<=h_ee_dummy.GetNbinsX()+1;ibin++){
    h_ee_dummy.SetBinContent(ibin,0.0);
    h_ee_dummy.SetBinError(ibin,0.0);
  }

  TH1D h_mm_dummy = TH1D((h_mm_data));
  for(int ibin=0;ibin<=h_mm_dummy.GetNbinsX()+1;ibin++){
    h_mm_dummy.SetBinContent(ibin,0.0);
    h_mm_dummy.SetBinError(ibin,0.0);
  }

  m->SetTemplate("ee", "eeBkg", h_ee_bkg, 1.0);
  //m->SetTemplate("mm", "mmBkg", h_mm_bkg, 1.0);

  //m->SetTemplate("ee", "mmBkg", h_ee_dummy, 1.0);
  //m->SetTemplate("mm", "eeBkg", h_mm_dummy, 1.0);

  m->SetTemplate("ee", "Theta", ee_funct_vector,ee_funct_vector->size(),1.0);
  //m->SetTemplate("mm", "Theta", mm_funct_vector,mm_funct_vector->size(),1.0);

  m->GetChannel(0)->SetFlagChannelActive(true);
  //m->GetChannel(1)->SetFlagChannelActive(false);


///////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////
  //  Systematic  //
  //////////////////

  if(doSys){
    m->AddSystematic("PDF_VAR1", -5.0, 5.0); 
    m->SetPriorGauss("PDF_VAR1", 0.0, 1.0);
    //m->GetParameters().Back().SetPrior(new BCGaussianPrior(0.0, 1.0));

    m->SetSystematicVariation("ee", "eeBkg", "PDF_VAR1", h_ee_sys, h_ee_sys);

    for(int ibin = 1; ibin <= h_ee_bkg.GetNbinsX(); ibin++){
      cout<<"data: "<<h_ee_data.GetBinContent(ibin)<<" bkg: "<<h_ee_bkg.GetBinContent(ibin)<<" sys: "<<h_ee_sys.GetBinContent(ibin)<<endl;
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
  //m->SetParameterRange(0, Neebkg - NeebkgError, Neebkg + NeebkgError);
  m->SetParameterRange(0, Neebkg, Neebkg);
  //m->SetParameterRange(1,Nmmbkg,Nmmbkg);
  if(!doSys) m->SetParameterRange(1, 0.0, 1e-20);//set Theta to zero here (flat prior would incl Theta in PE)
  if(doSys) m->SetParameterRange(1, 0.0, 1e-20);
  //m->SetParameterRange(1, 0.0, maxTheta);
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

/*  m->SetParameterRange(m->GetParameters().Index("PDF_VAR1"), 1.0, 1.0);
  m->MarginalizeAll();
  m->FindMode(m->GetBestFitParameters());
  std::vector<double> bestfit_parameters_up = m->GetBestFitParameters();
  for(int i = 0; i < bestfit_parameters_up.size(); i++){
    cout<<"bestfit_parameters(up): "<<bestfit_parameters_up.at(i)<<endl;
  }

  m->SetParameterRange(m->GetParameters().Index("PDF_VAR1"), -1.0, -1.0);
  m->MarginalizeAll();
  m->FindMode(m->GetBestFitParameters());
  std::vector<double> bestfit_parameters_down = m->GetBestFitParameters();
  for(int i = 0; i < bestfit_parameters_down.size(); i++){
    cout<<"bestfit_parameters(down): "<<bestfit_parameters_down.at(i)<<endl;
  }
*/
  // get tree
  TTree* priortree = (TTree*) pmout->GetMarkovChainTree();

  //undo PE modifications
  m->SetParameterRange(0, Neebkg, Neebkg);
  //m->SetParameterRange(1,Nmmbkg,Nmmbkg);
  m->SetParameterRange(1, 0.0, maxTheta);

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

  //bestfit_parameters.at(1) = 0.0;

  //if(!doSys) bestfit_parameters = {Neebkg, 0.0};
  //if(doSys) bestfit_parameters = {Neebkg, 0.0, 0.0};




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

