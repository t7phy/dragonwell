// ***************************************************************
// This file was created using the ./CreateProject.sh script
// for project BCMultiTemplateFitter
// ./CreateProject.sh is part of Bayesian Analysis Toolkit (BAT).
// BAT can be downloaded from http://www.mppmu.mpg.de/bat
// ***************************************************************

#include <BAT/BCLog.h>
#include <BAT/BCAux.h>
#include <BATHelper/BCSummaryPriorModel.h>
#include <BATHelper/BCModelOutput.h>
#include <BAT/BCH1D.h>

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

void readTextFile(string filename, vector<string> & vecLines)
{
  std::ifstream fileStream;
  vector<string> lines;

  fileStream.open(filename.c_str());
  if (fileStream.is_open() == false){
    cout << "Unable to open file \"" << filename << "\"" << endl;
    exit(1);
  }

  string lineBuffer;
  const unsigned int maxLineLength=1000;
  char charLineBuffer[maxLineLength];

  vecLines.clear();

  while(fileStream.good()){

    fileStream.getline(charLineBuffer,maxLineLength);
    lineBuffer = charLineBuffer;
    if (lineBuffer == "") continue;
    if (lineBuffer.substr(0,1) == "#") continue; // # as line comment symbol
    vecLines.push_back( lineBuffer );
  }
}

map<string, string> readInputFilenames(string filenameInputsConfig)
{
  vector<string> vecLines;
  map<string, string> mapFilenames;
  readTextFile(filenameInputsConfig, vecLines);

  for (vector<string>::const_iterator curLineI = vecLines.begin(); curLineI != vecLines.end(); ++curLineI)
  {
    string label;
    string value;
    label = curLineI->substr(0, curLineI->find("=") -1);
    value = curLineI->substr(curLineI->find("=") + 2);

    cout << label << "\t" << value << endl;

    mapFilenames.insert(std::pair<string,string>(label,value));
  }
  return mapFilenames;
}

int main(int argc, char ** argv){

  map<string, string> mapInputFilenames = readInputFilenames("inputs.conf"); // inputs_condor.conf automatically renamed to this, so no need to change.

  if(argc<11){
    cerr<<"You have: " << argc << " inputs.\n";
    cerr<<"usage:  templateLimitBATcombSys.exe iRun doEnsemble nEnsemble iMass doPlots doMCMC doSYS doTheory doElectron doMuon [model]\n";
    exit(1);
  }

  cout << "++ Running: " << argv[0] << endl;

  //Some flags to set (could come from cmd line)
  int  iRun       = atoi(argv[1]);           // iRun number (for parallel running)
  bool doEnsemble = atoi(argv[2]);//true;    // true=doPEs, false=data analysis
  int  nEnsemble  = atoi(argv[3]);//150;     // Number of pseudo-experiments (PEs) if doEnsemble is true
  int  iMass      = atoi(argv[4]);           // template number
  bool doPlots    = atoi(argv[5]);//true;    // Make plots of posterior PDF etc, for data analysis
  bool doMCMC     = atoi(argv[6]);//true;    // only relevant for PEs (use MarkovChain MC for marginalization or Minuit profiling)
  bool doSys      = atoi(argv[7]);//true;
  bool doTheoryUncertainty = atoi(argv[8]);  // false= Z' theory uncertainty outside of likelihood , true= Z' theory uncertainty included in likelihood function
                                             // Theory uncertainties were not updated for use in the likelihood in 2012 so this option does nothing at the moment
  bool doElectron          = atoi(argv[9]);
  bool doMuon              = atoi(argv[10]);

  int model = atoi(argv[11]);  //0 - SSM Z' 1 - Graviton

  double lumi = atoi(argv[12]);
  int doDis = atoi(argv[13]);
  int isUpdate = atoi(argv[14]);


  bool doXsecLimit=true;            // true=set xsec limits [pb] false=set N_zprime limits [counts]
  double lumiRatioMMoEE=1.0;        // only relevant if limit is set in units of N_zprime
  double lumiRatioMLoEE=1.0;        // only relevant if limit is set in units of N_zprime
  double maxNsig=1000.0;             // max parameter range of signal (in counts)
  bool activateEE=doElectron;   // enable EE channel
  bool activateMM=doMuon;       // enable MM channel

  bool discovery=doDis;

  cout<<"doEnsemble: "<<doEnsemble<<"\n";
  cout<<"nEnsemble: "<<nEnsemble<<"\n";
  cout<<"iMass: "<< iMass <<"\n";
  cout<<"doPlots: "<< doPlots <<"\n";
  cout<<"doMCMC: "<< doMCMC <<"\n";
  cout<<"doSys: "<< doSys <<"\n";
  cout<<"doTheoryUncertainty: "<< doTheoryUncertainty <<"\n";
  cout<<"doElectron: "<<doElectron<<"\n";
  cout<<"doMuon: "<<doMuon<<"\n";
  cout<<"lumiRatioMMoEE: "<<lumiRatioMMoEE<<"\n";
  cout<<"lumiRatioMLoEE: "<<lumiRatioMLoEE<<"\n";
  cout<<"maxNsig: "<<maxNsig<<"\n";
  cout<<"model: "<<model<<"\n\n\n";
  cout<<"lumi: "<<lumi<<"\n\n\n";

  // Define label based on settings
  string labelTxt = "";
  if (activateEE && !activateMM)
    labelTxt = "_ee";
  if (activateMM && !activateEE)
    labelTxt = "_mm";
  if (activateMM && activateEE)
    labelTxt = "_comb";

  if (doSys)
    labelTxt +="_Sys";

  // set nicer style for drawing than the ROOT default
  BCAux::SetStyle();

  // remember old directory
  TDirectory* f = gDirectory;

  //##############################

  // Get Electron Templates
  TFile * file_ee_SigTemp = new TFile( mapInputFilenames["File_Signal_ZPrime_Templates_ee"].c_str(), "READ");
  cout << "ee Signal Template file: \"" << file_ee_SigTemp->GetName() << "\"\n";

  TH1D h_ee_sgn;
  // Z'
  if (model == 0){
    if (iMass == 0){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_2500M_smear_withcuts_total"));
    }
    else if (iMass == 1){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_3500M_smear_withcuts_total"));
    }
    else if (iMass == 2){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_4500M_smear_withcuts_total"));
    }
    else if (iMass == 3){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_5500M_smear_withcuts_total"));
    }
    else if (iMass == 4){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_6500M_smear_withcuts_total"));
    }
    else if (iMass == 5){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_7500M_smear_withcuts_total"));
    }
    else if (iMass == 6){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_8500M_smear_withcuts_total"));
    }
    else if (iMass == 7){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_9500M_smear_withcuts_total"));
    }
    else if (iMass == 8){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_10500M_smear_withcuts_total"));
    }
    else if (iMass == 9){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_11500M_smear_withcuts_total"));
    }
    else if (iMass == 10){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_12500M_smear_withcuts_total"));
    }
    else if (iMass == 11){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_13500M_smear_withcuts_total"));
    }
    else if (iMass == 12){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Zee_14500M_smear_withcuts_total"));
    }
  }
    
  // W'
  if (model == 1){
    if (iMass == 0){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Wenu_2500M_smear_withcuts_total"));
    }
    else if (iMass == 1){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Wenu_3500M_smear_withcuts_total"));
    }
    else if (iMass == 2){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Wenu_4500M_smear_withcuts_total"));
    }
    else if (iMass == 3){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Wenu_5500M_smear_withcuts_total"));
    }
    else if (iMass == 4){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Wenu_6500M_smear_withcuts_total"));
    }
    else if (iMass == 5){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Wenu_7500M_smear_withcuts_total"));
    }
    else if (iMass == 6){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Wenu_8500M_smear_withcuts_total"));
    }
    else if (iMass == 7){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Wenu_9500M_smear_withcuts_total"));
    }
    else if (iMass == 8){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Wenu_10500M_smear_withcuts_total"));
    }
    else if (iMass == 9){
      h_ee_sgn = *((TH1D*) file_ee_SigTemp->Get("Mll_Wenu_11500M_smear_withcuts_total"));
    }
  }

  // Get Electron Background & NZee, Aee
  TFile * file_ee_sm = new TFile(mapInputFilenames["File_BackgroundAndData_ee"].c_str(),"READ");
  cout << "ee background and data file: \"" << file_ee_sm->GetName() <<"\"" << endl;
  TH1D h_ee_bkg;
  if (model == 0){
    h_ee_bkg = *((TH1D*) file_ee_sm->Get("Mll_withcuts_and_trigger_gold_1l"));
  }
  if (model == 1){
    h_ee_bkg = *((TH1D*) file_ee_sm->Get("MT_withcuts_and_trigger_gold_1l"));
  }

  // Get Electron Data
  TH1D h_ee_data;
  if (model == 0){
    h_ee_data = *((TH1D*) file_ee_sm->Get("Mll_withcuts_and_trigger_gold_1l")); // Asimov
  }
  if (model == 1){
    h_ee_data = *((TH1D*) file_ee_sm->Get("MT_withcuts_and_trigger_gold_1l")); // Asimov
  }


  for (int i=1; i < h_ee_bkg.GetXaxis()->GetNbins()+1; i++){
    if (h_ee_sgn.GetBinContent(i) == 0 || h_ee_bkg.GetBinContent(i) == 0){
      h_ee_sgn.SetBinContent(i,1e-20);
      h_ee_bkg.SetBinContent(i,1e-20);
      h_ee_data.SetBinContent(i,1e-20);
    }
  }

  if (discovery){
    TH1D *dummy_ee_data = (TH1D*)h_ee_data.Clone();
    TH1D *dummy_ee = (TH1D*)h_ee_sgn.Clone();
    dummy_ee_data->Add(dummy_ee);
    h_ee_data = *dummy_ee_data;
  }

  TH1D h_DummySys_ee = h_ee_sgn;

  // close files
  file_ee_SigTemp->Close();
  file_ee_sm->Close(); 

  delete file_ee_SigTemp;
  delete file_ee_sm;

  //##############################

  // Get Muon Templates
  TFile * file_mm_SigTemp = new TFile( mapInputFilenames["File_Signal_ZPrime_Templates_mm"].c_str(), "READ");
  cout << "mm Signal Template file: \"" << file_mm_SigTemp->GetName() << "\"\n";

  TH1D h_mm_sgn;
  // Z'
  if (model == 0){
    if (iMass == 0){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_2500M_smear_withcuts_total"));
    }
    else if (iMass == 1){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_3500M_smear_withcuts_total"));
    }
    else if (iMass == 2){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_4500M_smear_withcuts_total"));
    }
    else if (iMass == 3){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_5500M_smear_withcuts_total"));
    }
    else if (iMass == 4){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_6500M_smear_withcuts_total"));
    }
    else if (iMass == 5){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_7500M_smear_withcuts_total"));
    }
    else if (iMass == 6){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_8500M_smear_withcuts_total"));
    }
    else if (iMass == 7){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_9500M_smear_withcuts_total"));
    }
    else if (iMass == 8){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_10500M_smear_withcuts_total"));
    }
    else if (iMass == 9){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_11500M_smear_withcuts_total"));
    }
    else if (iMass == 10){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_12500M_smear_withcuts_total"));
    }
    else if (iMass == 11){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_13500M_smear_withcuts_total"));
    }
    else if (iMass == 12){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Zmumu_14500M_smear_withcuts_total"));
    }
  }

  // W'
  if (model == 1){
    if (iMass == 0){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Wmunu_2500M_smear_withcuts_total"));
    }
    else if (iMass == 1){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Wmunu_3500M_smear_withcuts_total"));
    }
    else if (iMass == 2){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Wmunu_4500M_smear_withcuts_total"));
    }
    else if (iMass == 3){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Wmunu_5500M_smear_withcuts_total"));
    }
    else if (iMass == 4){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Wmunu_6500M_smear_withcuts_total"));
    }
    else if (iMass == 5){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Wmunu_7500M_smear_withcuts_total"));
    }
    else if (iMass == 6){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Wmunu_8500M_smear_withcuts_total"));
    }
    else if (iMass == 7){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Wmunu_9500M_smear_withcuts_total"));
    }
    else if (iMass == 8){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Wmunu_10500M_smear_withcuts_total"));
    }
    else if (iMass == 9){
      h_mm_sgn = *((TH1D*) file_mm_SigTemp->Get("Mll_Wmunu_11500M_smear_withcuts_total"));
    }
  }

  // Get Electron Background & NZmm, Amm
  TFile * file_mm_sm = new TFile(mapInputFilenames["File_BackgroundAndData_mm"].c_str(),"READ");
  cout << "mm background and data file: \"" << file_mm_sm->GetName() <<"\"" << endl;
  TH1D h_mm_bkg;
  if (model == 0){
    h_mm_bkg = *((TH1D*) file_mm_sm->Get("Mll_withcuts_and_trigger_gold_1l"));
  }
  if (model == 1){
    h_mm_bkg = *((TH1D*) file_mm_sm->Get("MT_withcuts_and_trigger_gold_1l"));
  }

  // Get Electron Data
  TH1D h_mm_data;
  if (model == 0){
    h_mm_data = *((TH1D*) file_mm_sm->Get("Mll_withcuts_and_trigger_gold_1l")); // Asimov
  }
  if (model == 1){
    h_mm_data = *((TH1D*) file_mm_sm->Get("MT_withcuts_and_trigger_gold_1l")); // Asimov
  }

  for (int i=1; i < h_mm_bkg.GetXaxis()->GetNbins()+1; i++){
    if (h_mm_bkg.GetBinContent(i) == 0 || h_mm_sgn.GetBinContent(i) == 0){
      h_mm_bkg.SetBinContent(i,1e-20);
      h_mm_sgn.SetBinContent(i,1e-20);
      h_mm_data.SetBinContent(i,1e-20);
    }
  }

  if (discovery){
    TH1D *dummy_mm_data = (TH1D*)h_mm_data.Clone();
    TH1D *dummy_mm = (TH1D*)h_mm_sgn.Clone();
    dummy_mm_data->Add(dummy_mm);
    h_mm_data = *dummy_mm_data;
  }

  TH1D h_DummySys_mm = h_mm_sgn;

  // close files
  file_mm_SigTemp->Close();
  file_mm_sm->Close();  

  delete file_mm_SigTemp;
  delete file_mm_sm;

  // go back to old directory for memory handling
  f->cd();

  //################################################################################################################################
  // ----------------------------------------------------
  // configure BAT
  // ----------------------------------------------------
  // set nice style for drawing than the ROOT default
  BCAux::SetStyle();
  std::ostringstream iMassTxt; iMassTxt << iMass <<"_run"<<iRun;
  // open log file
  BCLog::OpenLog(("log_mass"+iMassTxt.str()+labelTxt+".txt").c_str());
  BCLog::SetLogLevel(BCLog::summary);

  //##############
  // 3000 -> 36 = 0.012
  // 3000 -> 80 = 0.0267
  // 3000 -> 300 = 0.1
  // 3000 -> 15000 = 5
  // double ScaleFactor = 5;
  // h_ee_bkg.Scale(ScaleFactor);
  // h_ee_data.Scale(ScaleFactor);
  // h_ee_sgn.Scale(ScaleFactor);
  // h_mm_bkg.Scale(ScaleFactor);
  // h_mm_data.Scale(ScaleFactor);
  // h_mm_sgn.Scale(ScaleFactor);
  //##############

  // ----------------------------------------------------
  // Normalization
  // ----------------------------------------------------
  double Neebkg = h_ee_bkg.Integral();
  double Nmmbkg = h_mm_bkg.Integral();

  // ----------------------------------------------------
  // create new BCMultiTemplateFitter object
  // ----------------------------------------------------
  BCMultiTemplateFitter* m = new BCMultiTemplateFitter();

  m->SetPrecision(BCEngineMCMC::kMedium);//yfu

  BCLog::OutSummary("Test model created");

  // create a new summary tool object
  BCSummaryTool * summary = new BCSummaryTool(m);

  // ----------------------------------------------------
  // Define required inputs
  // ----------------------------------------------------
  
  // Mass points: MUST CORRESPOND TO THE INPUT TEMPLATES!
  //              Please make sure that all inputs in this section are consistent 
  //                  with each other and with signal and background templates
  
  double mass = 1.0*iMass + 2.5;

  double AccEE;
  // Zp @ 14 TeV
  // if (model == 0){
  //   if (iMass == 0){
  //     AccEE = 0.75;
  //   }
  //   else if (iMass == 1){
  //     AccEE = 0.76;
  //   }
  //   else if (iMass == 2){
  //     AccEE = 0.78;
  //   }
  //   else if (iMass == 3){
  //     AccEE = 0.78;
  //   }
  //   else if (iMass == 4){
  //     AccEE = 0.78;
  //   }
  //   else if (iMass == 5){
  //     AccEE = 0.78;
  //   }
  //   else if (iMass == 6){
  //     AccEE = 0.77;
  //   }
  //   else if (iMass == 7){
  //     AccEE = 0.77;
  //   }
  //   else if (iMass == 8){
  //     AccEE = 0.78;
  //   }
  //   else if (iMass == 9){
  //     AccEE = 0.78;
  //   }
  //   else if (iMass == 10){
  //     AccEE = 0.78;
  //   }
  //   else if (iMass == 11){
  //     AccEE = 0.78;
  //   }
  //   else if (iMass == 12){
  //     AccEE = 0.79;
  //   }
  // }

  if (model == 0){
    if (iMass == 0){
      AccEE = 0.65;
    }
    else if (iMass == 1){
      AccEE = 0.65;
    }
    else if (iMass == 2){
      AccEE = 0.65;
    }
    else if (iMass == 3){
      AccEE = 0.65;
    }
    else if (iMass == 4){
      AccEE = 0.65;
    }
    else if (iMass == 5){
      AccEE = 0.65;
    }
    else if (iMass == 6){
      AccEE = 0.65;
    }
    else if (iMass == 7){
      AccEE = 0.65;
    }
    else if (iMass == 8){
      AccEE = 0.65;
    }
    else if (iMass == 9){
      AccEE = 0.65;
    }
    else if (iMass == 10){
      AccEE = 0.65;
    }
    else if (iMass == 11){
      AccEE = 0.65;
    }
    else if (iMass == 12){
      AccEE = 0.65;
    }
  }

  // W' @ 14 TeV
  if (model == 1){
    if (iMass == 0){
      AccEE = 0.85;
    }
    else if (iMass == 1){
      AccEE = 0.83;
    }
    else if (iMass == 2){
      AccEE = 0.79;
    }
    else if (iMass == 3){
      AccEE = 0.74;
    }
    else if (iMass == 4){
      AccEE = 0.69;
    }
    else if (iMass == 5){
      AccEE = 0.67;
    }
    else if (iMass == 6){
      AccEE = 0.63;
    }
    else if (iMass == 7){
      AccEE = 0.66;
    }
    else if (iMass == 8){
      AccEE = 0.66;
    }
    else if (iMass == 9){
      AccEE = 0.65;
    }
  }

  double AccMM;
  // Z' @ 14 TeV
  if (model == 0){
    if (iMass == 0){
      AccMM = 0.55;
    }
    else if (iMass == 1){
      AccMM = 0.55;
    }
    else if (iMass == 2){
      AccMM = 0.54;
    }
    else if (iMass == 3){
      AccMM = 0.55;
    }
    else if (iMass == 4){
      AccMM = 0.51;
    }
    else if (iMass == 5){
      AccMM = 0.54;
    }
    else if (iMass == 6){
      AccMM = 0.53;
    }
    else if (iMass == 7){
      AccMM = 0.54;
    }
    else if (iMass == 8){
      AccMM = 0.54;
    }
    else if (iMass == 9){
      AccMM = 0.54;
    }
    else if (iMass == 10){
      AccMM = 0.53;
    }
    else if (iMass == 11){
      AccMM = 0.52;
    }
    else if (iMass == 12){
      AccMM = 0.51;
    }
  }

  // W' @ 14 TeV
  if (model == 1){
    if (iMass == 0){
      AccMM = 0.68;
    }
    else if (iMass == 1){
      AccMM = 0.68;
    }
    else if (iMass == 2){
      AccMM = 0.65;
    }
    else if (iMass == 3){
      AccMM = 0.62;
    }
    else if (iMass == 4){
      AccMM = 0.60;
    }
    else if (iMass == 5){
      AccMM = 0.58;
    }
    else if (iMass == 6){
      AccMM = 0.58;
    }
    else if (iMass == 7){
      AccMM = 0.58;
    }
    else if (iMass == 8){
      AccMM = 0.58;
    }
    else if (iMass == 9){
      AccMM = 0.58;
    }
  }
  
  // Run Parameters
  
  double maxSigmaSig = maxNsig / ( lumi * AccEE );

  cout<<"mass:  "<<mass<<"\n";
  cout<<"accEE: "<<AccEE<<"\n";
  cout<<"accMM: "<<AccMM<<"\n";
  cout<<"maxSigmaSig "<<maxSigmaSig<<endl;

  // Construct the BAT model

  m->AddChannel("ee");
  m->AddChannel("mm");

  m->AddProcess("eeBkg", Neebkg, Neebkg);
  m->AddProcess("mmBkg", Nmmbkg, Nmmbkg);
  if (doXsecLimit)
    m->AddProcess("signal",   0., maxSigmaSig);
  else
    m->AddProcess("signal",   0., maxNsig);

  m->SetData("ee", h_ee_data);
  m->SetData("mm", h_mm_data);

  m->SetTemplate("ee", "eeBkg", h_ee_bkg, 1.0);
  m->SetTemplate("mm", "mmBkg", h_mm_bkg, 1.0);

  if (doXsecLimit){
    m->SetTemplate("ee", "signal", h_ee_sgn, (AccEE * lumi));
    m->SetTemplate("mm", "signal", h_mm_sgn, (AccMM * lumi));
  }
  else {
    m->SetTemplate("ee", "signal", h_ee_sgn, 1.0);
    m->SetTemplate("mm", "signal", h_mm_sgn, 1.0 * lumiRatioMMoEE);
  }

  // ----------------------------------------------------
  // Specify active channels and priors
  // ----------------------------------------------------
  m->GetChannel(0)->SetFlagChannelActive(activateEE);
  m->GetChannel(1)->SetFlagChannelActive(activateMM);

  // set priors
  m->SetPriorGauss("eeBkg", Neebkg, 0.1);
  m->SetPriorGauss("mmBkg", Nmmbkg, 0.1);
  m->SetPriorConstant("signal");
  m->SetFlagDoLogNormal(true);

  //increase number of marginalization bins (higher precision)
  //m->SetNbins("signal",1000);
  //m->GetVariable("signal").SetNbins(1000);//yfu
  m->SetNbins(1000);//yfu

  //Turn on treatment of MC stat. errors in the background estimate
  // Currently use 1 bin (80-120 GeV) as DY smoothing starts at 120 GeV.
  m->GetChannel(0)->SetMaxBinStatErr(1);
  m->GetChannel(1)->SetMaxBinStatErr(1);
  m->SetFlagDoStatErr(true);

  if (discovery && !doSys){
    m->AddSystematic("DummySys",-5,5);     m->SetPriorGauss("DummySys",0.0,1.0);
  }

  if (doSys){

    ePumpHelper* EU = new ePumpHelper("test");
    EU->Initial();
    EU->Update();
    TH1D* OldPDFError;
    EU->ConstructOldPDFErrorHist("test/ZHighMass_CF", "", OldPDFError, "Relative");
    TH1D* NewPDFError;
    EU->ConstructNewPDFErrorHist("test/ZHighMass_CF", "", NewPDFError, "Relative");
    TH1D* PDFError;
    if(isUpdate) PDFError = NewPDFError;
    else if(!isUpdate) PDFError = OldPDFError;

    TF1 *fDummySys = new TF1("fDummySys", "0.065*x",  0.0, 60.0);
    
    for (int i=1; i<=h_DummySys_ee.GetNbinsX();i++){
      double mass = h_DummySys_ee.GetBinCenter(i);
      //h_DummySys_ee.SetBinContent(i,fDummySys->Eval(mass/1000));
      //h_DummySys_mm.SetBinContent(i,fDummySys->Eval(mass/1000));
      h_DummySys_ee.SetBinContent(i, PDFError->GetBinContent(i) * 3.0);
      h_DummySys_mm.SetBinContent(i, PDFError->GetBinContent(i) * 3.0);
      //cout<<"bin: "<<i<<" Error: "<<h_DummySys_mm.GetBinContent(i)<<endl;
    }
    
    m->AddSystematic("DummySys",-5,5);     m->SetPriorGauss("DummySys",0.0,1.0);

    m->SetSystematicVariation("ee", "eeBkg", "DummySys", h_DummySys_ee, h_DummySys_ee);
    m->SetSystematicVariation("ee", "signal", "DummySys", h_DummySys_ee, h_DummySys_ee);

    m->SetSystematicVariation("mm", "mmBkg", "DummySys", h_DummySys_mm, h_DummySys_mm);
    m->SetSystematicVariation("mm", "signal", "DummySys", h_DummySys_mm, h_DummySys_mm);
    
  }
  
  // ----------------------------------------------------
  // Perform analysis
  // ----------------------------------------------------
  if (!doEnsemble){

    // run MCMC
    m->SetData("ee", h_ee_data);
    m->SetData("mm", h_mm_data);

    // Uncomment if extracting sys pulls
    // m->SetParameterRange(0,Neebkg,Neebkg);
    // m->SetParameterRange(1,Nmmbkg,Nmmbkg);
    // m->SetParameterRange(2,0.0,0.0);//set signal to zero here (flat prior would incl signal in PE)
    m->MarginalizeAll();


    // find global mode
    m->FindMode( m->GetBestFitParameters() );

    // // Uncomment if extracting sys pulls
    // vector<double> best_pars = m->GetBestFitParameters();
    // for (unsigned int i=0; i < best_pars.size(); i++){
    //   cout << m->GetParameter(i)->GetName() << " " << best_pars.at(i) << " +/- " << m->GetBestFitParameterError(i) << endl;
    // }

    // print a summary
    m->PrintSummary();

    //cout << "limit " << mass << " " << m->GetMarginalized("signal")->GetLimit(0.95) << endl;
    cout << "limit " << mass << " " << m->GetMarginalized("signal").GetLimit(0.95) << endl;//yfu

    if (discovery){
      cout << "significance " << mass << " " << m->significance(maxSigmaSig) << endl;
    }

    if (doPlots){
      m->PrintAllMarginalized(("model_marginalized_mass"+iMassTxt.str()+labelTxt+".eps").c_str());
      // print all summary plots
      summary->PrintNuisancePlot(("BCMultiTemplateFitter_pull"+iMassTxt.str()+labelTxt+".eps").c_str(),3);
      summary->PrintParameterPlot(("BCMultiTemplateFitter_parameters"+iMassTxt.str()+labelTxt+".eps").c_str());
      summary->PrintCorrelationPlot(("BCMultiTemplateFitter_correlation"+iMassTxt.str()+labelTxt+".eps").c_str());

      // print results of the analysis into a text file
      m->PrintResults(("BCMultiTemplateFitter_results"+iMassTxt.str()+labelTxt+".txt").c_str());
    }

    return 0;
  }

  // ----------------------------------------------------
  // Create prior model for pseudo-experiments
  // ----------------------------------------------------

  // create new prior model
  BCSummaryPriorModel* pm = new BCSummaryPriorModel();
  // set model (and make adjustment suitable for background only pseudo-experiments (PE))
  //m->SetParameterRange(0,Neebkg,Neebkg);//yfu comment out
  //m->SetParameterRange(1,Nmmbkg,Nmmbkg);//yfu comment out
  m->SetParameterRange(2,0.0,0.0);//set signal to zero here (flat prior would incl signal in PE)//yfu comment out
  pm->SetModel(m);

  // ----------------------------------------------------
  // Create output object
  // ----------------------------------------------------
  BCModelOutput* pmout = new BCModelOutput(pm, ("prior"+iMassTxt.str()+labelTxt+".root").c_str());


  // switch writing of Markov Chains on
  pmout->WriteMarkovChain(true);

  // set precision
  pm->SetPrecision(BCEngineMCMC::kMedium);//yfu

  // perform marginalization
  cout<<"First Marginalize:"<<endl;
  pm->MarginalizeAll();

  // get tree
  //TTree* priortree = (TTree*) pmout->GetFile()->Get("MarkovChainTree_0");
  TTree* priortree = (TTree*) pmout->GetMarkovChainTree();

  //undo PE modifications
  //m->SetParameterRange(0,Neebkg,Neebkg);
  //m->SetParameterRange(1,Nmmbkg,Nmmbkg);
  if (doXsecLimit)
    m->SetParameterRange(2,0.0,maxSigmaSig);
  else
    m->SetParameterRange(2,0.0,maxNsig);

  // ----------------------------------------------------------------
  // Perform ensemble test
  // ----------------------------------------------------------------
  // create new analysis facility
  BCMTFAnalysisFacility* facility = new BCMTFAnalysisFacility(m);
  facility->SetFlagMCMC(doMCMC);

  // create ensembles
  cout<<"Start building ensembles"<<endl;
  //TTree* tree = facility->BuildEnsembles( priortree, 10000 );

  //std::vector<double> fitted_parameters = {pm->GetFittedParameter(0), pm->GetFittedParameter(1), pm->GetFittedParameter(2), pm->GetFittedParameter(3)};
  std::vector<double> fitted_parameters = pm->GetFittedParameters();
  std::vector<double> bestfit_parameters = pm->GetBestFitParameters();
  //cout<<fitted_parameters.at(0)<<endl;
  //cout<<fitted_parameters.at(1)<<endl;
  //cout<<fitted_parameters.at(2)<<endl;
  //cout<<fitted_parameters.at(3)<<endl;
  //cout<<"BestFitParameters:"<<endl;
  //cout<<bestfit_parameters.at(0)<<endl;
  //cout<<bestfit_parameters.at(1)<<endl;
  //cout<<bestfit_parameters.at(2)<<endl;
  //cout<<bestfit_parameters.at(3)<<endl;

  //bestfit_parameters = {2957074126.93884, 4142670879.27363, 0.0, 2.61138};

  TTree* tree = facility->BuildEnsembles( bestfit_parameters, 10000 );//yfu

cout<<"Start generating ensemble:"<<endl;
  // run ensemble test
  TTree* tree_out = facility->PerformEnsembleTest(tree, nEnsemble);

  // open new file
  TFile *file = new TFile(("zprime_ensembles_mass"+iMassTxt.str()+labelTxt+".root").c_str(), "RECREATE");
  file->cd();

  // write trees into file
  tree->Write();
  tree_out->Write();

  // close file
  file->Close();

  // free memory
  delete file;

  // -----------

  // close log file
  BCLog::CloseLog();

  // close output file
  pmout->Close();


  // free memory
  delete pmout;
  delete pm;
  delete facility;
  delete m;
  delete summary;


  BCLog::OutSummary("Test program ran successfully");
  BCLog::OutSummary("Exiting");

  // no error
  return 0;

}
