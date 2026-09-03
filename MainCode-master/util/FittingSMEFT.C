#include "RootCommon.h"
#include "Tools/Tools.h"
#include "TMinuitHelper/TMinuitHelper.h"
#include "ePumpHelper/ePumpHelper.h"

TH1D* global_h_ee_data;
TH1D* global_h_ee_bkg;
TH1D* global_h_ee_signal;
TH1D* global_h_ee_sys;
vector<TF1*>* global_ee_funct_vector;

double Min_Chi2 = 1000000.0;

void FittingSMEFTWrapper(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 TH1D* h_ee_data = (TH1D *)global_h_ee_data->Clone("h_ee_data");
 TH1D* h_ee_bkg = (TH1D *)global_h_ee_bkg->Clone("h_ee_bkg");
 TH1D* h_ee_signal = (TH1D *)global_h_ee_signal->Clone("h_ee_signal");
 TH1D* h_ee_sys = (TH1D *)global_h_ee_sys->Clone("h_ee_sys");
 TH1D* h_ee_np = (TH1D *)h_ee_sys->Clone("h_ee_np");

 vector<TF1*>* ee_funct_vector = global_ee_funct_vector;

 for(int ibin = 1; ibin <= h_ee_signal->GetNbinsX(); ibin++){
   h_ee_signal->SetBinContent(ibin, ee_funct_vector->at(ibin - 1)->Eval(par[1]));
 }

 for(int ibin = 1; ibin <= h_ee_signal->GetNbinsX(); ibin++){
   h_ee_np->SetBinContent(ibin, par[2] * h_ee_bkg->GetBinContent(ibin) * h_ee_sys->GetBinContent(ibin));
 }

 TH1D* h_ee_mc = (TH1D *)h_ee_bkg->Clone("h_ee_mc");
 h_ee_mc->Scale(par[0]);
 h_ee_mc->Add(h_ee_signal);
 h_ee_mc->Add(h_ee_np);

 double Chi2 = CalculateChi2WithData(h_ee_mc, h_ee_data);

 for(int ibin = 1; ibin < h_ee_data->GetNbinsX(); ibin++){
   cout<<"data: "<<h_ee_data->GetBinContent(ibin)<<" bkg: "<<h_ee_bkg->GetBinContent(ibin)<<" signal: "<<h_ee_signal->GetBinContent(ibin)<<" np: "<<h_ee_np->GetBinContent(ibin)<<endl;
 }

 f = Chi2;

 if(f < Min_Chi2) Min_Chi2 = f;

 cout<<"Min Chi2 = "<<Min_Chi2<<endl;

 delete h_ee_data;
 delete h_ee_bkg;
 delete h_ee_signal;
 delete h_ee_sys;
 delete h_ee_np;
 delete h_ee_mc;
}

int main(int argc, char** argv)
{
  double DummyPDFUnc = stod(argv[1]);

  TFile* file_ee = new TFile("MC_results.root");
  TFile* file_data = new TFile("MC_results_SMEFT_cqlm1_c_0.0.root");

  TFile* file_function = new TFile("save.root");

  TH1D* h_ee_bkg = (TH1D*) file_ee->Get("CrossSection_Pseudodata");

  TH1D* h_ee_data = (TH1D*) file_data->Get("CrossSection_Pseudodata");

///////////////////////////////////////////////////////////////////////////////////////////

  bool doSys = true;
  bool isUpdate = false;

  TH1D* h_ee_sys = (TH1D*) h_ee_data->Clone("h_ee_sys");

  ePumpHelper* EU = new ePumpHelper("test");
  EU->TurnOffCorrelationCosine();
  EU->Initial();
  EU->Update();
  TH1D* OldPDFError = EU->ConstructOldPDFErrorHist("test/CrossSection", "", "Relative", 3, 8);
  TH1D* NewPDFError = EU->ConstructNewPDFErrorHist("test/CrossSection", "", "Relative", 3, 8);
  TH1D* PDFError;
  if(isUpdate) PDFError = NewPDFError;
  else if(!isUpdate) PDFError = OldPDFError;

  for (int i = 1; i <= h_ee_sys->GetNbinsX(); i++){
    h_ee_sys->SetBinContent(i, PDFError->GetBinContent(i) * DummyPDFUnc);
//    h_ee_sys.SetBinContent(i, DummyPDFUnc * i);
    cout<<"ibin "<<i<<": OldPDFError = "<<OldPDFError->GetBinContent(i)<<" NewPDFError = "<<NewPDFError->GetBinContent(i)<<" CurrentPDFError = "<<PDFError->GetBinContent(i)<<endl;
  }

///////////////////////////////////////////////////////////////////////////////////////////

  double LumiFactor = 1.0;

  vector<TF1*>* ee_funct_vector=new vector<TF1*>(h_ee_bkg->GetNbinsX());

  ee_funct_vector->at(0) = (TF1 *)file_function->Get("CrossSection_700_900_cqlm1_Fitting");
  ee_funct_vector->at(1) = (TF1 *)file_function->Get("CrossSection_900_1200_cqlm1_Fitting");
  ee_funct_vector->at(2) = (TF1 *)file_function->Get("CrossSection_1200_1800_cqlm1_Fitting");
  ee_funct_vector->at(3) = (TF1 *)file_function->Get("CrossSection_1800_3000_cqlm1_Fitting");
  ee_funct_vector->at(4) = (TF1 *)file_function->Get("CrossSection_3000_4500_cqlm1_Fitting");
  ee_funct_vector->at(5) = (TF1 *)file_function->Get("CrossSection_4500_6000_cqlm1_Fitting");

  for(int i = 0; i < ee_funct_vector->size(); i++){
    ee_funct_vector->at(i)->SetParameter(0, ee_funct_vector->at(i)->GetParameter(0) * LumiFactor);
    ee_funct_vector->at(i)->SetParameter(1, ee_funct_vector->at(i)->GetParameter(1) * LumiFactor);
    ee_funct_vector->at(i)->SetParameter(2, ee_funct_vector->at(i)->GetParameter(2) * LumiFactor);
    cout<<"ibin: "<<i + 1<<" Parameter 1: "<<ee_funct_vector->at(i)->GetParameter(0)<<" Parameter 2: "<<ee_funct_vector->at(i)->GetParameter(1)<<" Parameter 3: "<<ee_funct_vector->at(i)->GetParameter(2)<<endl;
  }

  TH1D* h_ee_signal = (TH1D*) h_ee_bkg->Clone("signal");
  h_ee_signal->Reset();

  global_h_ee_data = h_ee_data;
  global_h_ee_bkg = h_ee_bkg;
  global_h_ee_signal = h_ee_signal;
  global_h_ee_sys = h_ee_sys;
  global_ee_funct_vector = ee_funct_vector;

  TMinuitHelper *myMinuit = new TMinuitHelper(3);
  myMinuit->SetFCN(FittingSMEFTWrapper);

  myMinuit->Input(0, "bkg", 1.0, 0.0, 0.9, 1.1);
  myMinuit->Input(1, "signal", 0.1, 0.2, 0.0, 0.5);
  myMinuit->Input(2, "PDF", 1.0, 1.0, -5.0, 5.0);

  myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
  myMinuit->Exec("MIGRAD", 100000, 0.001);
  double* SPar = new double[3];
  double* SParError = new double[3];
  myMinuit->GetParametersAndError(SPar, SParError);
  cout<<"bkg: "<<SPar[0]<<" +- "<<SParError[0]<<endl;
  cout<<"signal: "<<SPar[1]<<" +- "<<SParError[1]<<endl;
  cout<<"PDF: "<<SPar[2]<<" +- "<<SParError[2]<<endl;

  return 1.0;
}

