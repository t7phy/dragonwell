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
  if(argc != 3){
    return 0;
  }

  int doSys = stoi(argv[1]);
  int isUpdate = stoi(argv[2]);

  cout<<"doSys: "<<doSys<<endl;
  cout<<"isUpdate: "<<isUpdate<<endl;


  ePumpHelper* EU = new ePumpHelper("test");
  EU->TurnOffCorrelationCosine();
  EU->Initial();
  EU->Update();
  TH1D* OldPDFError;
  EU->ConstructOldPDFErrorHist("test/CrossSection", "", OldPDFError, "Relative");
  TH1D* NewPDFError;
  EU->ConstructNewPDFErrorHist("test/CrossSection", "", NewPDFError, "Relative");
  TH1D* PDFError;
  if(isUpdate) PDFError = NewPDFError;
  else if(!isUpdate) PDFError = OldPDFError;

  vector<TString> Coefficient = {"0.05", "0.1", "0.15", "0.2", "0.25", "0.3", "0.35", "0.4", "0.45", "0.5"};

  TFile* file_ee;
  TFile* file_data;

  TH1D h_ee_bkg;
  TH1D h_ee_data;

  vector<TF1*>* ee_funct_vector;
  vector<TF1*>* mm_funct_vector;

  vector<double> SignalSignificanceValue;
  vector<double> SignalSignificanceError;

  for(int i = 0; i < Coefficient.size(); i++){


    file_ee = new TFile("MC_results.root");
    file_data = new TFile((TString)"MC_results_SMEFT_cqlm1_c_" + Coefficient.at(i) + ".root");
  
    TFile* file_function = new TFile("save.root");
  
  
    h_ee_bkg = *((TH1D*) file_ee->Get("CrossSection_Pseudodata"));
    TH1D h_mm_bkg = *((TH1D*) file_ee->Get("CrossSection_Pseudodata"));
  
    h_ee_data = *((TH1D*) file_data->Get("CrossSection_Pseudodata"));
    TH1D h_mm_data = *((TH1D*) file_data->Get("CrossSection_Pseudodata"));
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  
    //bool doSys = false;
    //bool isUpdate = false;
  
    TH1D h_ee_sys = *((TH1D*) file_data->Get("CrossSection_Pseudodata"));
  
    for (int i = 1; i <= h_ee_sys.GetNbinsX(); i++){
      h_ee_sys.SetBinContent(i, PDFError->GetBinContent(i));
      cout<<"ibin "<<i<<": OldPDFError = "<<OldPDFError->GetBinContent(i)<<" NewPDFError = "<<NewPDFError->GetBinContent(i)<<" CurrentPDFError = "<<PDFError->GetBinContent(i)<<endl;
    }
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  
    Double_t kFactor = 84.0;
    Double_t LumiFactor = 1.0;
  
    h_ee_bkg.Scale(LumiFactor);
    h_mm_bkg.Scale(LumiFactor);
    h_ee_data.Scale(LumiFactor);
    h_mm_data.Scale(LumiFactor);
  
    ee_funct_vector=new vector<TF1*>(h_ee_bkg.GetNbinsX());
    mm_funct_vector=new vector<TF1*>(h_mm_bkg.GetNbinsX());
  
    ee_funct_vector->at(0) = (TF1 *)file_function->Get("CrossSection_400_500_cqlm1_Fitting");
    ee_funct_vector->at(1) = (TF1 *)file_function->Get("CrossSection_500_700_cqlm1_Fitting");
    ee_funct_vector->at(2) = (TF1 *)file_function->Get("CrossSection_700_900_cqlm1_Fitting");
    ee_funct_vector->at(3) = (TF1 *)file_function->Get("CrossSection_900_1200_cqlm1_Fitting");
    ee_funct_vector->at(4) = (TF1 *)file_function->Get("CrossSection_1200_1800_cqlm1_Fitting");
    ee_funct_vector->at(5) = (TF1 *)file_function->Get("CrossSection_1800_3000_cqlm1_Fitting");
    ee_funct_vector->at(6) = (TF1 *)file_function->Get("CrossSection_3000_4500_cqlm1_Fitting");
    ee_funct_vector->at(7) = (TF1 *)file_function->Get("CrossSection_4500_6000_cqlm1_Fitting");
  
    for(int i = 0; i < ee_funct_vector->size(); i++){
      ee_funct_vector->at(i)->SetParameter(0, ee_funct_vector->at(i)->GetParameter(0) * LumiFactor);
      ee_funct_vector->at(i)->SetParameter(1, ee_funct_vector->at(i)->GetParameter(1) * LumiFactor);
      ee_funct_vector->at(i)->SetParameter(2, ee_funct_vector->at(i)->GetParameter(2) * LumiFactor);
      cout<<"ibin: "<<i + 1<<" Parameter 1: "<<ee_funct_vector->at(i)->GetParameter(0)<<" Parameter 2: "<<ee_funct_vector->at(i)->GetParameter(1)<<" Parameter 3: "<<ee_funct_vector->at(i)->GetParameter(2)<<endl;
    }
  
    mm_funct_vector = ee_funct_vector;
  
    int ThetaBins = 500;
    double maxTheta = 0.8;
  
    bool doMCMC = true;
    int nEnsemble = 50;
  
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
      m->AddSystematic("PDF_VAR1", -10, 10); 
      m->SetPriorGauss("PDF_VAR1", 0.0, 1.0);
      //m->GetParameters().Back().SetPrior(new BCGaussianPrior(0.0, 1.0));
  
      m->SetSystematicVariation("ee", "eeBkg", "PDF_VAR1", h_ee_sys, h_ee_sys);
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
    m->SetParameterRange(0, Neebkg - NeebkgError, Neebkg + NeebkgError);
    //m->SetParameterRange(0, Neebkg, Neebkg);
    //m->SetParameterRange(1,Nmmbkg,Nmmbkg);
    //if(!doSys) m->SetParameterRange(1, 0.0, maxTheta);//set Theta to zero here (flat prior would incl Theta in PE)
    //if(doSys) m->SetParameterRange(1, 0.0, 0.0);
    m->SetParameterRange(1, 0.0, maxTheta);
    pm->SetModel(m);
  
    // ----------------------------------------------------
    // create output object
    // ----------------------------------------------------
    BCModelOutput* pmout = new BCModelOutput(m, "prior.root");
  
    // switch writing of Markov Chains on
    pmout->WriteMarkovChain(true);
  
    // set precision
    m->SetPrecision(BCEngineMCMC::kMedium);
  
   // perform marginalization
    m->MarginalizeAll();
    m->FindMode(m->GetBestFitParameters());
    m->PrintAllMarginalized(m->GetSafeName() + "_plots.pdf");
    m->PrintParameterPlot(m->GetSafeName() + "_parameters.pdf");
    m->PrintCorrelationPlot(m->GetSafeName() + "_correlation.pdf");
    m->PrintCorrelationMatrix(m->GetSafeName() + "_correlationMatrix.pdf");
    m->PrintKnowledgeUpdatePlots(m->GetSafeName() + "_update.pdf");
  
    std::vector<double> bestfit_parameters = m->GetBestFitParameters();
    for(int i = 0; i < bestfit_parameters.size(); i++){
      cout<<"bestfit_parameters: "<<bestfit_parameters.at(i)<<endl;
    }

    m->SetParameterRange(m->GetParameters().Index("PDF_VAR1"), 1.0, 1.0);
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
 
    // get tree
    TTree* priortree = (TTree*) pmout->GetMarkovChainTree();
  
    //undo PE modifications
    //m->SetParameterRange(0, Neebkg, Neebkg);
    //m->SetParameterRange(1,Nmmbkg,Nmmbkg);
    //m->SetParameterRange(1, 0.0, maxTheta);
  
    // ----------------------------------------------------------------
    // Perform ensemble test
    // ----------------------------------------------------------------
  
    // create new analysis facility

    double tmp_Significance = 0.0;
    double tmp_SignificanceError = 0.0;
    int SignalIndex = 1;
    int BkgIndex = 2;
    for(int ibin = 1; ibin <= h_ee_bkg.GetNbinsX(); ibin++){
      double Signal = 0.0;
      double Bkg = 0.0;
      double Signal95Quantile = 0.0;
      double Bkg95Quantile = 0.0;
      double SignalError = 0.0;
      double BkgError = 0.0;
      double SignalErrorPDF = 0.0;

      double Signal_Up = 0.0;
      double Signal_Down = 0.0;

      double SignalPar95 = 0.0;
      double BkgPar95 = 0.0;
      double SysPar95 = 0.0;
      SignalPar95 = (m->GetMarginalized( m->GetParameter(SignalIndex).GetName() )).GetQuantile(0.95);
      BkgPar95 = (m->GetMarginalized( m->GetParameter(0).GetName() )).GetQuantile(0.95);
      //if(doSys) SysPar95 = (m->GetMarginalized( m->GetParameter(BkgIndex).GetName() )).GetQuantile(0.95);

      Signal95Quantile = ee_funct_vector->at(ibin - 1)->Eval(SignalPar95);
      if(!doSys) Bkg95Quantile = h_ee_bkg.GetBinContent(ibin);
      //if(doSys) Bkg95Quantile = h_ee_bkg.GetBinContent(ibin) * (1.0 + SysPar95 * h_ee_sys.GetBinContent(ibin));

      Signal = ee_funct_vector->at(ibin - 1)->Eval(bestfit_parameters.at(SignalIndex));
      if(!doSys) Bkg = h_ee_bkg.GetBinContent(ibin);
      if(doSys) Bkg = h_ee_bkg.GetBinContent(ibin) * (1.0 + bestfit_parameters.at(BkgIndex) * h_ee_sys.GetBinContent(ibin));

      Signal_Up = ee_funct_vector->at(ibin - 1)->Eval(bestfit_parameters_up.at(SignalIndex));
      Signal_Down = ee_funct_vector->at(ibin - 1)->Eval(bestfit_parameters_down.at(SignalIndex));

      SignalError = fabs(Signal - Signal95Quantile);
      //BkgError = fabs(Bkg - Bkg95Quantile);

      SignalErrorPDF = fabs(Signal - Signal_Up) > fabs(Signal - Signal_Down) ? fabs(Signal - Signal_Up) : fabs(Signal - Signal_Down);

      tmp_Significance += Signal * Signal / Bkg;
      //tmp_SignificanceError += (4.0 * Signal * Signal * Bkg * Bkg * SignalError * SignalError + pow(Signal, 4) * pow(BkgError, 2)) / (pow(Bkg, 4));
      tmp_SignificanceError += 4.0 * Signal * Signal * SignalError * SignalError / Bkg / Bkg;
      cout<<"ibin "<<ibin<<" SignalEval: "<<bestfit_parameters.at(SignalIndex)<<" Signal95Eval: "<<SignalPar95<<" Signal: "<<Signal<<" Signal95: "<<Signal95Quantile<<" Bkg: "<<Bkg<<" Bkg95: "<<Bkg95Quantile<<endl;
    }
    SignalSignificanceValue.push_back(sqrt(tmp_Significance));
    SignalSignificanceError.push_back(sqrt(tmp_SignificanceError));
  }

  TString SignalFileName;
  if(!doSys) SignalFileName = "SignalSignificance_nopdf.root";
  if(doSys && isUpdate) SignalFileName = "SignalSignificance_newpdf.root";
  if(doSys && !isUpdate) SignalFileName = "SignalSignificance_oldpdf.root";

  TFile* writefile = new TFile(SignalFileName, "RECREATE");
  TH1D* h1 = new TH1D("SignalSignificance", "SignalSignificance", 10, 0.025, 0.525);
  for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
    h1->SetBinContent(ibin, SignalSignificanceValue.at(ibin - 1));
    h1->SetBinError(ibin, SignalSignificanceError.at(ibin - 1));
    //h1->SetBinContent(ibin, SignalSignificanceValue.at(ibin - 1) + SignalSignificanceError.at(ibin - 1));
    //h1->SetBinError(ibin, SignalSignificanceError.at(ibin - 1));
  }

  for(int ibin = 1; ibin <= h_ee_bkg.GetNbinsX(); ibin++){
    h_ee_bkg.SetBinError(ibin, h_ee_bkg.GetBinContent(ibin) * OldPDFError->GetBinContent(ibin));
  }


  writefile->cd();
  h1->Write();
  h_ee_bkg.Write();
  OldPDFError->Write();
  NewPDFError->Write();


  writefile->Close();

  //bestfit_parameters.at(1) = 0.0;

  //if(!doSys) bestfit_parameters = {Neebkg, 0.0};
  //if(doSys) bestfit_parameters = {Neebkg, 0.0, 0.0};


/*

  //TTree* tree = facility->BuildEnsembles( bestfit_parameters, 10000 );//yfu
  TTree* tree = facility->BuildEnsembles( priortree, 10000 );

  std::vector<int> details;
  details.push_back(0);
  details.push_back(0);
  //details.push_back(0);
  details.push_back(1);

  // run ensemble test
  cout<<"Start ensemble test:"<<endl;
  TTree* tree_out = facility->PerformEnsembleTest(tree, nEnsemble, details);

  // write trees into file
  tree->Write();
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
*/

 return 1;
}

