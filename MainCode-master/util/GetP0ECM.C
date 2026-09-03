#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Tools/Tools.h"
#include "TMinuitHelper/TMinuitHelper.h"

using namespace std;

TH1D* global_Data;
TH1D* global_Theory;

double MinChi2 = 100000.0;

void ExponentFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 double Chi2 = 0.0;

 TH1D* P0_Data = (TH1D *)global_Data->Clone("P0_Data");
 TH1D* P0_Theory = (TH1D *)global_Data->Clone("P0_Theory");

 P0_Theory->Reset();

 for(int ibin = 1; ibin <= P0_Theory->GetNbinsX(); ibin++){
   double theory = par[0] * exp(par[1] * P0_Theory->GetBinCenter(ibin) + par[2]);
   P0_Theory->SetBinContent(ibin, theory);
   P0_Theory->SetBinError(ibin, P0_Data->GetBinError(ibin));
 }

 global_Theory = (TH1D *)P0_Theory->Clone("global_Theory");

 Chi2 = CalculateChi2(P0_Data, P0_Theory);
 f = Chi2;
 if(f < MinChi2) MinChi2 = f;

 cout<<"Min Chi2 = "<<MinChi2<<endl;
}

int main(int argc, char** argv)
{
 TFile* writefile = new TFile("save.root", "RECREATE");
 writefile->cd();

 int ECM_bin = 7;
 double ECM_binning[8] = {0.5, 3.5, 6.5, 9.5, 16.5, 23.5, 76.5, 123.5};

 TH1D* uuP0Result = new TH1D("uuP0", "uuP0", ECM_bin, ECM_binning);
 TH1D* ddP0Result = new TH1D("ddP0", "ddP0", ECM_bin, ECM_binning);

 vector<TString> RootNames;
 RootNames.push_back("pp_2TeV/MC_results.root");
 RootNames.push_back("pp_5TeV/MC_results.root");
 RootNames.push_back("pp_8TeV/MC_results.root");
 RootNames.push_back("pp_13TeV/MC_results.root");
 RootNames.push_back("pp_20TeV/MC_results.root");
 RootNames.push_back("pp_50TeV/MC_results.root");
 RootNames.push_back("pp_100TeV/MC_results.root");

 for(int i = 0; i < RootNames.size(); i++){
   TFile* file = new TFile(RootNames.at(i));
   TH1D* uuP0 = (TH1D *)file->Get("CoefficientZMass_Full_uu_wrong_Average");
   TH1D* ddP0 = (TH1D *)file->Get("CoefficientZMass_Full_dd_wrong_Average");

   uuP0Result->SetBinContent(i + 1, uuP0->GetBinContent(1));
   uuP0Result->SetBinError(i + 1, uuP0->GetBinError(1));

   ddP0Result->SetBinContent(i + 1, ddP0->GetBinContent(1));
   ddP0Result->SetBinError(i + 1, ddP0->GetBinError(1));

 }

 global_Data = uuP0Result;
 TMinuitHelper *myMinuit_uuP0 = new TMinuitHelper(3);
 myMinuit_uuP0->SetFCN(ExponentFitting);
 myMinuit_uuP0->Input(0, "p1", 0.2, 0.5, -1.0, 1.0);
 myMinuit_uuP0->Input(1, "p2", 0.2, 0.5, -1.0, 1.0);
 myMinuit_uuP0->Input(2, "p3", 0.2, 0.5, -1.0, 1.0);
 myMinuit_uuP0->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
 myMinuit_uuP0->Exec("MIGRAD", 100000, 0.001);
 myMinuit_uuP0->GetParameter();
 double* uuP0_Par = new double[3];
 double* uuP0_ParError = new double[3];
 myMinuit_uuP0->GetParametersAndError(uuP0_Par, uuP0_ParError);
 TH1D* uuP0Theory = (TH1D *)global_Theory->Clone("uuP0Theory");


 global_Data = ddP0Result;
 TMinuitHelper *myMinuit_ddP0 = new TMinuitHelper(3);
 myMinuit_ddP0->SetFCN(ExponentFitting);
 myMinuit_ddP0->Input(0, "p1", 0.2, 0.5, -1.0, 1.0);
 myMinuit_ddP0->Input(1, "p2", 0.2, 0.5, -1.0, 1.0);
 myMinuit_ddP0->Input(2, "p3", 0.2, 0.5, -1.0, 1.0);
 myMinuit_ddP0->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
 myMinuit_ddP0->Exec("MIGRAD", 100000, 0.001);
 myMinuit_ddP0->GetParameter();
 double* ddP0_Par = new double[3];
 double* ddP0_ParError = new double[3];
 myMinuit_ddP0->GetParametersAndError(ddP0_Par, ddP0_ParError);
 TH1D* ddP0Theory = (TH1D *)global_Theory->Clone("ddP0Theory");



 TF1* fitting_uuP0 = new TF1("fitting_uuP0", "[0]*exp(-0.014154*x+0.47683)", 2.0, 100.0);
 TF1* fitting_ddP0 = new TF1("fitting_ddP0", "[0]*exp(-0.0115947*x+0.477649)", 2.0, 100.0);

 double par_uuP0[3];
 double par_ddP0[3];

 cout<<endl;
 myMinuit_uuP0->GetParameter();
 myMinuit_ddP0->GetParameter();


 fitting_uuP0->SetParameters(uuP0_Par[0], uuP0_Par[1], uuP0_Par[2]);
 fitting_ddP0->SetParameters(ddP0_Par[0], ddP0_Par[1], ddP0_Par[2]);

 uuP0Result->Fit(fitting_uuP0,"W");
// uuP0Theory->Fit(fitting_uuP0,"W");
 fitting_uuP0->GetParameters(par_uuP0);

 ddP0Result->Fit(fitting_ddP0,"W");
// ddP0Theory->Fit(fitting_ddP0,"W");
 fitting_ddP0->GetParameters(par_ddP0);


 writefile->cd();

 fitting_uuP0->Write("fitting_uuP0");
 fitting_ddP0->Write("fitting_ddP0");

 writefile->cd();
 writefile->Write();
 writefile->Close();

 return 1;
}
