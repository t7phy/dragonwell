#include "/home/yfu/figure/Figure.h"

void getratio()
{
 Figure* f;

 TFile* DYTurbo_mass_file = new TFile("1D_pdf_var.root");
 TFile* DYTurbo_mass_costheta_file = new TFile("2D_pdf_var.root");
 TFile* DYTurbo_mass_rapidity_file = new TFile("2D_rap_pdf_var.root");

 vector<TH1D *> DYTurbo_mass_hists(59);
 vector<TH1D *> DYTurbo_mass_costheta_hists(59);
 vector<TH1D *> DYTurbo_mass_rapidity_hists(59);

 vector<TH1D *> DYTurbo_mass_ratio(59);
 vector<TH1D *> DYTurbo_mass_costheta_ratio(59);
 vector<TH1D *> DYTurbo_mass_rapidity_ratio(59);

 vector<TFile *> ResBos_files(59);

 vector<TH1D *> ResBos_mass_hists(59);
 vector<TH1D *> ResBos_mass_costheta_hists(59);
 vector<TH1D *> ResBos_mass_rapidity_hists(59);

 vector<TH1D *> ResBos_mass_ratio(59);
 vector<TH1D *> ResBos_mass_costheta_ratio(59);
 vector<TH1D *> ResBos_mass_rapidity_ratio(59);

 TFile* writefile = new TFile("PDFEVRatio.root", "RECREATE");

 ResBos_files.at(0) = new TFile("i2Tn3.00/MC_results.root");
 ResBos_mass_hists.at(0) = (TH1D *)ResBos_files.at(0)->Get("ATLAS_Mll_HighMass");
 ResBos_mass_costheta_hists.at(0) = (TH1D *)ResBos_files.at(0)->Get("ATLAS_Mll_HighMass_costheta_NewBinning");
 ResBos_mass_rapidity_hists.at(0) = (TH1D *)ResBos_files.at(0)->Get("ATLAS_Mll_HighMass_DilRapidity_NewBinning");

 for(int i = 1; i <= 58; i++){
   DYTurbo_mass_hists.at(i) = (TH1D *)DYTurbo_mass_file->Get((TString)"uncertainty_EV" + i);
   DYTurbo_mass_costheta_hists.at(i) = (TH1D *)DYTurbo_mass_costheta_file->Get((TString)"uncertainty_EV" + i);
   DYTurbo_mass_rapidity_hists.at(i) = (TH1D *)DYTurbo_mass_rapidity_file->Get((TString)"uncertainty_EV" + i);

   DYTurbo_mass_ratio.at(i) = (TH1D *)DYTurbo_mass_hists.at(i)->Clone((TString)"DYTurbo_mass_ratio_" + i);
   DYTurbo_mass_costheta_ratio.at(i) = (TH1D *)DYTurbo_mass_costheta_hists.at(i)->Clone((TString)"DYTurbo_mass_costheta_ratio_" + i);
   DYTurbo_mass_rapidity_ratio.at(i) = (TH1D *)DYTurbo_mass_rapidity_hists.at(i)->Clone((TString)"DYTurbo_mass_rapidity_ratio_" + i);

   for(int ibin = 1; ibin <= DYTurbo_mass_hists.at(i)->GetNbinsX(); ibin++){
     DYTurbo_mass_ratio.at(i)->SetBinContent(ibin, DYTurbo_mass_hists.at(i)->GetBinContent(ibin) + 1);
   }

   for(int ibin = 1; ibin <= DYTurbo_mass_costheta_hists.at(i)->GetNbinsX(); ibin++){
     DYTurbo_mass_costheta_ratio.at(i)->SetBinContent(ibin, DYTurbo_mass_costheta_hists.at(i)->GetBinContent(ibin) + 1);
   }

   for(int ibin = 1; ibin <= DYTurbo_mass_rapidity_hists.at(i)->GetNbinsX(); ibin++){
     DYTurbo_mass_rapidity_ratio.at(i)->SetBinContent(ibin, DYTurbo_mass_rapidity_hists.at(i)->GetBinContent(ibin) + 1);
   }

   ResBos_files.at(i) = new TFile(TString::Format("i2Tn3.%02d/MC_results.root", i));
   ResBos_mass_hists.at(i) = (TH1D *)ResBos_files.at(i)->Get("ATLAS_Mll_HighMass");
   ResBos_mass_costheta_hists.at(i) = (TH1D *)ResBos_files.at(i)->Get("ATLAS_Mll_HighMass_costheta_NewBinning");
   ResBos_mass_rapidity_hists.at(i) = (TH1D *)ResBos_files.at(i)->Get("ATLAS_Mll_HighMass_DilRapidity_NewBinning");

   ResBos_mass_ratio.at(i) = (TH1D *)ResBos_mass_hists.at(i)->Clone((TString)"ResBos_mass_ratio_" + i);
   ResBos_mass_costheta_ratio.at(i) = (TH1D *)ResBos_mass_costheta_hists.at(i)->Clone((TString)"ResBos_mass_costheta_ratio_" + i);
   ResBos_mass_rapidity_ratio.at(i) = (TH1D *)ResBos_mass_rapidity_hists.at(i)->Clone((TString)"ResBos_mass_rapidity_ratio_" + i);

   ResBos_mass_ratio.at(i)->Divide(ResBos_mass_hists.at(0));
   ResBos_mass_costheta_ratio.at(i)->Divide(ResBos_mass_costheta_hists.at(0));
   ResBos_mass_rapidity_ratio.at(i)->Divide(ResBos_mass_rapidity_hists.at(0));

   writefile->cd();
   DYTurbo_mass_ratio.at(i)->Write();
   DYTurbo_mass_costheta_ratio.at(i)->Write();
   DYTurbo_mass_rapidity_ratio.at(i)->Write();
   ResBos_mass_ratio.at(i)->Write();
   ResBos_mass_costheta_ratio.at(i)->Write();
   ResBos_mass_rapidity_ratio.at(i)->Write();

   f = new Figure((TString)"EVRatio_mass_" + i + ".png", "bin index", "Ratio");
   f->SetMode("CUSTOM");
   f->Input(1, DYTurbo_mass_ratio.at(i), (TString)"DYTurbo EV " + i);
   f->Input(2, ResBos_mass_ratio.at(i), (TString)"ResBos EV " + i);
   f->Compare("MultiRatio");
   f->SetCustomYRange(1, 0.95, 1.05);
   f->SetCustomYRange(2, 0.95, 1.05);
   f->Draw();
   delete f;

   f = new Figure((TString)"EVRatio_mass_costheta_" + i + ".png", "bin index", "Ratio");
   f->SetMode("CUSTOM");
   f->Input(1, DYTurbo_mass_costheta_ratio.at(i), (TString)"DYTurbo EV " + i);
   f->Input(2, ResBos_mass_costheta_ratio.at(i), (TString)"ResBos EV " + i);
   f->Compare("MultiRatio");
   f->SetCustomYRange(1, 0.95, 1.05);
   f->SetCustomYRange(2, 0.95, 1.05);
   f->Draw();
   delete f;

   f = new Figure((TString)"EVRatio_mass_rapidity_" + i + ".png", "bin index", "Ratio");
   f->SetMode("CUSTOM");
   f->Input(1, DYTurbo_mass_rapidity_ratio.at(i), (TString)"DYTurbo EV " + i);
   f->Input(2, ResBos_mass_rapidity_ratio.at(i), (TString)"ResBos EV " + i);
   f->Compare("MultiRatio");
   f->SetCustomYRange(1, 0.95, 1.05);
   f->SetCustomYRange(2, 0.95, 1.05);
   f->Draw();
   delete f;
 }

 writefile->Close();
}
