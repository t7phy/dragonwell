#include "/home/yfu/figure/Figure.h"

void extrapolation()
{
 TString Process = "Wjets_DD";
 TString Function1 = "[0]*pow(x/13000.0,[1])*pow(x/13000.0, [2]*log(x/13000.0))";
 TString Function2 = "[0] / pow(x/1.0 + [1], [2])";
 TString Function3 = "[0]*pow(1 - x/13000.0, [1]) / pow(x/13000.0, [2] + [3]*log(x/13000.0))";

 TString Function4 = "[0]*TMath::Power(1-(x-116)/5000.0,3)+3*[1]*(x-116)/5000.0*TMath::Power(1-(x-116)/5000.0,2)+3*[2]*TMath::Power((x-116)/5000.0,2)*(1-(x-116)/5000.0)+[3]*TMath::Power((x-116)/5000.0,3)";
 TString Function5 = "[0]*TMath::Power(1-(x-116)/5000.0,5)+5*[1]*(x-116)/5000.0*TMath::Power(1-(x-116)/5000.0,4)+10*[2]*TMath::Power((x-116)/5000.0,2)*TMath::Power(1-(x-116)/5000.0,3)+10*[3]*TMath::Power((x-116)/5000.0,3)*TMath::Power(1-(x-116)/5000.0,2)+5*[4]*TMath::Power((x-116)/5000.0,4)*(1-(x-116)/5000.0)+[5]*TMath::Power((x-116)/5000.0,5)";

 TString HistPath = "/data/projects/StandardModel/HMDY_inclusive/results/MuChannel/DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs/Histograms/";

 TString MassFileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_histos.root";
 TString MassCosTheta1FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_0p00_0p20_histos.root";
 TString MassCosTheta2FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_0p20_0p40_histos.root";
 TString MassCosTheta3FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_0p40_0p60_histos.root";
 TString MassCosTheta4FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_0p60_0p80_histos.root";
 TString MassCosTheta5FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_0p80_1p00_histos.root";
 TString MassCosTheta6FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_m0p20_0p00_histos.root";
 TString MassCosTheta7FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_m0p40_m0p20_histos.root";
 TString MassCosTheta8FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_m0p60_m0p40_histos.root";
 TString MassCosTheta9FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_m0p80_m0p60_histos.root";
 TString MassCosTheta10FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_m1p00_m0p80_histos.root";
 TString MassCosTheta11FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_0p00_0p25_histos.root";
 TString MassCosTheta12FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_0p25_0p50_histos.root";
 TString MassCosTheta13FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_0p50_0p75_histos.root";
 TString MassCosTheta14FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_0p75_1p00_histos.root";
 TString MassCosTheta15FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_m0p25_0p00_histos.root";
 TString MassCosTheta16FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_m0p50_m0p25_histos.root";
 TString MassCosTheta17FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_m0p75_m0p50_histos.root";
 TString MassCosTheta18FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_costhetastar_m1p00_m0p75_histos.root";

 TString MassRapidity1FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_0p00_0p20_histos.root";
 TString MassRapidity2FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_0p20_0p40_histos.root";
 TString MassRapidity3FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_0p40_0p60_histos.root";
 TString MassRapidity4FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_0p60_0p80_histos.root";
 TString MassRapidity5FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_0p80_1p00_histos.root";
 TString MassRapidity6FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_1p00_1p20_histos.root";
 TString MassRapidity7FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_1p20_1p40_histos.root";
 TString MassRapidity8FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_1p40_1p60_histos.root";
 TString MassRapidity9FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_1p60_1p80_histos.root";
 TString MassRapidity10FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_1p80_2p00_histos.root";
 TString MassRapidity11FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_2p00_2p20_histos.root";
 TString MassRapidity12FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_2p20_2p40_histos.root";
 TString MassRapidity13FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_0p00_0p30_histos.root";
 TString MassRapidity14FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_0p30_0p60_histos.root";
 TString MassRapidity15FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_0p60_0p90_histos.root";
 TString MassRapidity16FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_0p90_1p20_histos.root";
 TString MassRapidity17FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_1p20_1p50_histos.root";
 TString MassRapidity18FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_1p50_1p80_histos.root";
 TString MassRapidity19FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_1p80_2p10_histos.root";
 TString MassRapidity20FileName = HistPath + "DataMCPlots_mumu_HighMass_mc16ade_Powheg_withsyst_DDFakes_fine_bin_mass_extrapolation_inputs_Mll_HighMass_yll_2p10_2p40_histos.root";

 TString MassHistName = "Mll_HighMass";

 TString MassCosTheta1HistName = "Mll_HighMass_costhetastar_0p00_0p20";
 TString MassCosTheta2HistName = "Mll_HighMass_costhetastar_0p20_0p40";
 TString MassCosTheta3HistName = "Mll_HighMass_costhetastar_0p40_0p60";
 TString MassCosTheta4HistName = "Mll_HighMass_costhetastar_0p60_0p80";
 TString MassCosTheta5HistName = "Mll_HighMass_costhetastar_0p80_1p00";
 TString MassCosTheta6HistName = "Mll_HighMass_costhetastar_m0p20_0p00";
 TString MassCosTheta7HistName = "Mll_HighMass_costhetastar_m0p40_m0p20";
 TString MassCosTheta8HistName = "Mll_HighMass_costhetastar_m0p60_m0p40";
 TString MassCosTheta9HistName = "Mll_HighMass_costhetastar_m0p80_m0p60";
 TString MassCosTheta10HistName = "Mll_HighMass_costhetastar_m1p00_m0p80";
 TString MassCosTheta11HistName = "Mll_HighMass_costhetastar_0p00_0p25";
 TString MassCosTheta12HistName = "Mll_HighMass_costhetastar_0p25_0p50";
 TString MassCosTheta13HistName = "Mll_HighMass_costhetastar_0p50_0p75";
 TString MassCosTheta14HistName = "Mll_HighMass_costhetastar_0p75_1p00";
 TString MassCosTheta15HistName = "Mll_HighMass_costhetastar_m0p25_0p00";
 TString MassCosTheta16HistName = "Mll_HighMass_costhetastar_m0p50_m0p25";
 TString MassCosTheta17HistName = "Mll_HighMass_costhetastar_m0p75_m0p50";
 TString MassCosTheta18HistName = "Mll_HighMass_costhetastar_m1p00_m0p75";

 TString MassRapidity1HistName = "Mll_HighMass_yll_0p00_0p20";
 TString MassRapidity2HistName = "Mll_HighMass_yll_0p20_0p40";
 TString MassRapidity3HistName = "Mll_HighMass_yll_0p40_0p60";
 TString MassRapidity4HistName = "Mll_HighMass_yll_0p60_0p80";
 TString MassRapidity5HistName = "Mll_HighMass_yll_0p80_1p00";
 TString MassRapidity6HistName = "Mll_HighMass_yll_1p00_1p20";
 TString MassRapidity7HistName = "Mll_HighMass_yll_1p20_1p40";
 TString MassRapidity8HistName = "Mll_HighMass_yll_1p40_1p60";
 TString MassRapidity9HistName = "Mll_HighMass_yll_1p60_1p80";
 TString MassRapidity10HistName = "Mll_HighMass_yll_1p80_2p00";
 TString MassRapidity11HistName = "Mll_HighMass_yll_2p00_2p20";
 TString MassRapidity12HistName = "Mll_HighMass_yll_2p20_2p40";
 TString MassRapidity13HistName = "Mll_HighMass_yll_0p00_0p30";
 TString MassRapidity14HistName = "Mll_HighMass_yll_0p30_0p60";
 TString MassRapidity15HistName = "Mll_HighMass_yll_0p60_0p90";
 TString MassRapidity16HistName = "Mll_HighMass_yll_0p90_1p20";
 TString MassRapidity17HistName = "Mll_HighMass_yll_1p20_1p50";
 TString MassRapidity18HistName = "Mll_HighMass_yll_1p50_1p80";
 TString MassRapidity19HistName = "Mll_HighMass_yll_1p80_2p10";
 TString MassRapidity20HistName = "Mll_HighMass_yll_2p10_2p40";

 vector<double> MassBinning = {116.0, 130.0, 150.0, 175.0, 200.0, 230.0, 260.0, 300.0, 380.0, 500.0, 700.0, 1000.0, 1500.0, 5000.0};
 vector<double> MassBinning1 = {116.0, 150.0, 200.0, 300.0, 500.0};
 vector<double> MassBinning2 = {500.0, 1500.0};

 auto Function2Histo = [&](TF1* fit, vector<double> binning){
   TString name = (TString)fit->GetName() + "_Histogram";
   TH1D* h = new TH1D(name, name, binning.size() - 1, &binning[0]);
   for(int ibin = 1; ibin <= h->GetNbinsX(); ibin++){
     double integral = fit->Integral(binning.at(ibin - 1), binning.at(ibin));
     h->SetBinContent(ibin, integral);
     h->SetBinError(ibin, 0.0);
   }
   return h;
 };

 auto FitHist = [&](TString filename, TString histname, TString Process, TFile* outfile, vector<double> Binning){
   cout<<"Fit for "<<histname<<endl;
 
   TFile* file = new TFile(filename);
   TH1D* hist_nominal = (TH1D *)file->Get(histname + "/" + Process + "/nominal/" + histname + "_" + Process + "_orig");
   TH1D* hist_Stat_up = (TH1D *)file->Get(histname + "/" + Process + "/fake_eff_stat/" + histname + "_" + Process + "_fake_eff_stat_Up_orig");
   TH1D* hist_Stat_down = (TH1D *)file->Get(histname + "/" + Process + "/fake_eff_stat/" + histname + "_" + Process + "_fake_eff_stat_Down_orig");
   TH1D* hist_PromptSubtr_up = (TH1D *)file->Get(histname + "/" + Process + "/PromptSubtr/" + histname + "_" + Process + "_PromptSubtr_Up_orig");
   TH1D* hist_PromptSubtr_down = (TH1D *)file->Get(histname + "/" + Process + "/PromptSubtr/" + histname + "_" + Process + "_PromptSubtr_Down_orig");
   TH1D* hist_d0sig_up = (TH1D *)file->Get(histname + "/" + Process + "/d0sig/" + histname + "_" + Process + "_d0sig_Up_orig");
   TH1D* hist_d0sig_down = (TH1D *)file->Get(histname + "/" + Process + "/d0sig/" + histname + "_" + Process + "_d0sig_Down_orig");
   TH1D* hist_RealStat_up = (TH1D *)file->Get(histname + "/" + Process + "/RealStat/" + histname + "_" + Process + "_RealStat_Up_orig");
   TH1D* hist_RealStat_down = (TH1D *)file->Get(histname + "/" + Process + "/RealStat/" + histname + "_" + Process + "_RealStat_Down_orig");

   TString filename_orig_bin = filename;
   filename_orig_bin.ReplaceAll("histos.root", "orig_bin_histos.root");
   TFile* file_orig_bin = new TFile(filename_orig_bin);
   TH1D* hist_nominal_orig_bin = (TH1D *)file_orig_bin->Get(histname + "_orig_bin/" + Process + "/nominal/" + histname + "_orig_bin_" + Process + "_orig");
   TH1D* hist_Stat_up_orig_bin = (TH1D *)file_orig_bin->Get(histname + "_orig_bin/" + Process + "/fake_eff_stat/" + histname + "_orig_bin_" + Process + "_fake_eff_stat_Up_orig");
   TH1D* hist_Stat_down_orig_bin = (TH1D *)file_orig_bin->Get(histname + "_orig_bin/" + Process + "/fake_eff_stat/" + histname + "_orig_bin_" + Process + "_fake_eff_stat_Down_orig");
   TH1D* hist_PromptSubtr_up_orig_bin = (TH1D *)file_orig_bin->Get(histname + "_orig_bin/" + Process + "/PromptSubtr/" + histname + "_orig_bin_" + Process + "_PromptSubtr_Up_orig");
   TH1D* hist_PromptSubtr_down_orig_bin = (TH1D *)file_orig_bin->Get(histname + "_orig_bin/" + Process + "/PromptSubtr/" + histname + "_orig_bin_" + Process + "_PromptSubtr_Down_orig");
   TH1D* hist_d0sig_up_orig_bin = (TH1D *)file_orig_bin->Get(histname + "_orig_bin/" + Process + "/d0sig/" + histname + "_orig_bin_" + Process + "_d0sig_Up_orig");
   TH1D* hist_d0sig_down_orig_bin = (TH1D *)file_orig_bin->Get(histname + "_orig_bin/" + Process + "/d0sig/" + histname + "_orig_bin_" + Process + "_d0sig_Down_orig");
   TH1D* hist_RealStat_up_orig_bin = (TH1D *)file_orig_bin->Get(histname + "_orig_bin/" + Process + "/RealStat/" + histname + "_orig_bin_" + Process + "_RealStat_Up_orig");
   TH1D* hist_RealStat_down_orig_bin = (TH1D *)file_orig_bin->Get(histname + "_orig_bin/" + Process + "/RealStat/" + histname + "_orig_bin_" + Process + "_RealStat_Down_orig");

   TH1D* hist_FakeSys_up_orig_bin = (TH1D *)hist_nominal_orig_bin->Clone(histname + "_FakeSys_up_orig_bin");
   TH1D* hist_FakeSys_down_orig_bin = (TH1D *)hist_nominal_orig_bin->Clone(histname + "_FakeSys_down_orig_bin");

   for(int ibin = 1; ibin <= hist_nominal_orig_bin->GetNbinsX(); ibin++){
     double Central = hist_nominal_orig_bin->GetBinContent(ibin);
     double StatErr = hist_nominal_orig_bin->GetBinError(ibin);

     double PromptSubtr_up = hist_PromptSubtr_up_orig_bin->GetBinContent(ibin);
     double PromptSubtr_down = hist_PromptSubtr_down_orig_bin->GetBinContent(ibin);
     double Stat_up = hist_Stat_up_orig_bin->GetBinContent(ibin);
     double Stat_down = hist_Stat_down_orig_bin->GetBinContent(ibin);
     double d0sig_up = hist_d0sig_up_orig_bin->GetBinContent(ibin);
     double d0sig_down = hist_d0sig_down_orig_bin->GetBinContent(ibin);
     double RealStat_up = hist_RealStat_up_orig_bin->GetBinContent(ibin);
     double RealStat_down = hist_RealStat_down_orig_bin->GetBinContent(ibin);

     if(PromptSubtr_up < 1e-10) PromptSubtr_up = Central;
     if(PromptSubtr_down < 1e-10) PromptSubtr_down = Central;
     if(Stat_up < 1e-10) Stat_up = Central;
     if(Stat_down < 1e-10) Stat_down = Central;
     if(d0sig_up < 1e-10) d0sig_up = Central;
     if(d0sig_down < 1e-10) d0sig_down = Central;
     if(RealStat_up < 1e-10) RealStat_up = Central;
     if(RealStat_down < 1e-10) RealStat_down = Central;

     double CombineError = sqrt(pow(max(fabs(Stat_up - Central), fabs(Central - Stat_down)), 2)
                              + pow(max(fabs(PromptSubtr_down - Central), fabs(Central - PromptSubtr_up)), 2)
                              + pow(max(fabs(Central - d0sig_up), fabs(Central - d0sig_down)), 2)
                              + pow(max(fabs(RealStat_up - Central), fabs(Central - RealStat_down)), 2));

     hist_FakeSys_up_orig_bin->SetBinContent(ibin, Central + CombineError);
     hist_FakeSys_up_orig_bin->SetBinError(ibin, 0.0);
     hist_FakeSys_down_orig_bin->SetBinContent(ibin, Central - CombineError > 0.0 ? Central - CombineError : 1e-10);
     hist_FakeSys_down_orig_bin->SetBinError(ibin, 0.0);
   }

   hist_nominal->Scale(1.0, "width");
   hist_Stat_up->Scale(1.0, "width");
   hist_Stat_down->Scale(1.0, "width");
   hist_PromptSubtr_up->Scale(1.0, "width");
   hist_PromptSubtr_down->Scale(1.0, "width");
   hist_d0sig_up->Scale(1.0, "width");
   hist_d0sig_down->Scale(1.0, "width");
   hist_RealStat_up->Scale(1.0, "width");
   hist_RealStat_down->Scale(1.0, "width");

   TH1D* hist_function2 = (TH1D *)hist_nominal->Clone(histname + "_function2");
   TH1D* hist_stitch_point = (TH1D *)hist_nominal->Clone(histname + "_stitch_point");

   TH1D* hist_withsys = (TH1D *)hist_nominal->Clone(histname + "_withsys");

   for(int ibin = 1; ibin <= hist_nominal->GetNbinsX(); ibin++){
     double Central = hist_nominal->GetBinContent(ibin);
     double StatErr = hist_nominal->GetBinError(ibin);

     double PromptSubtr_up = hist_PromptSubtr_up->GetBinContent(ibin);
     double PromptSubtr_down = hist_PromptSubtr_down->GetBinContent(ibin);
     double Stat_up = hist_Stat_up->GetBinContent(ibin);
     double Stat_down = hist_Stat_down->GetBinContent(ibin);
     double d0sig_up = hist_d0sig_up->GetBinContent(ibin);
     double d0sig_down = hist_d0sig_down->GetBinContent(ibin);
     double RealStat_up = hist_RealStat_up->GetBinContent(ibin);
     double RealStat_down = hist_RealStat_down->GetBinContent(ibin);

     if(PromptSubtr_up < 1e-10) PromptSubtr_up = Central;
     if(PromptSubtr_down < 1e-10) PromptSubtr_down = Central;
     if(Stat_up < 1e-10) Stat_up = Central;
     if(Stat_down < 1e-10) Stat_down = Central;
     if(d0sig_up < 1e-10) d0sig_up = Central;
     if(d0sig_down < 1e-10) d0sig_down = Central;
     if(RealStat_up < 1e-10) RealStat_up = Central;
     if(RealStat_down < 1e-10) RealStat_down = Central;

     double CombineError = sqrt(pow(max(fabs(Stat_up - Central), fabs(Central - Stat_down)), 2)
                              + pow(max(fabs(PromptSubtr_down - Central), fabs(Central - PromptSubtr_up)), 2)
                              + pow(max(fabs(Central - d0sig_up), fabs(Central - d0sig_down)), 2)
                              + pow(max(fabs(RealStat_up - Central), fabs(Central - RealStat_down)), 2)
                              + StatErr * StatErr);

     hist_withsys->SetBinError(ibin, CombineError);
   }

   TF1* fit_nominal = new TF1(histname + "_nominal_fit", Function3, 116.0, 5000.0);
   TF1* fit_Stat_up = new TF1(histname +   "_Stat_up_fit", Function3, 116.0, 5000.0);
   TF1* fit_Stat_down = new TF1(histname + "_Stat_down_fit", Function3, 116.0, 5000.0);
   TF1* fit_PromptSubtr_up = new TF1(histname +   "_PromptSubtr_up_fit", Function3, 116.0, 5000.0);
   TF1* fit_PromptSubtr_down = new TF1(histname + "_PromptSubtr_down_fit", Function3, 116.0, 5000.0);
   TF1* fit_d0sig_up = new TF1(histname +   "_d0sig_up_fit", Function3, 116.0, 5000.0);
   TF1* fit_d0sig_down = new TF1(histname + "_d0sig_down_fit", Function3, 116.0, 5000.0);
   TF1* fit_RealStat_up = new TF1(histname +   "_RealStat_up_fit", Function3, 116.0, 5000.0);
   TF1* fit_RealStat_down = new TF1(histname + "_RealStat_down_fit", Function3, 116.0, 5000.0);
   TF1* fit_function2 = new TF1(histname + "_function2_fit", Function1, 116.0, 5000.0);
   TF1* fit_stitch_point = new TF1(histname + "_stitchpoint_fit", Function3, 116.0, 5000.0);

   ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2", "Migrad");
   ROOT::Math::MinimizerOptions::SetDefaultStrategy(1);
   ROOT::Math::MinimizerOptions::SetDefaultTolerance(1e-6);

   hist_nominal->Fit(fit_nominal, "S R L +", "", 130.0, 400.0);
   hist_Stat_up->Fit(fit_Stat_up, "S R L +", "", 130.0, 400.0);
   hist_Stat_down->Fit(fit_Stat_down, "S R L +", "", 130.0, 400.0);
   hist_PromptSubtr_up->Fit(fit_PromptSubtr_up, "S R L +", "", 130.0, 400.0);
   hist_PromptSubtr_down->Fit(fit_PromptSubtr_down, "S R L +", "", 130.0, 400.0);
   hist_d0sig_up->Fit(fit_d0sig_up, "S R L +", "", 130.0, 400.0);
   hist_d0sig_down->Fit(fit_d0sig_down, "S R L +", "", 130.0, 400.0);
   hist_RealStat_up->Fit(fit_RealStat_up, "S R L +", "", 130.0, 400.0);
   hist_RealStat_down->Fit(fit_RealStat_down, "S R L +", "", 130.0, 400.0);
   hist_function2->Fit(fit_function2, "S R L +", "", 130.0, 400.0);
   hist_stitch_point->Fit(fit_stitch_point, "S R L +", "", 130.0, 300.0);

   TH1D* hist_nominal_integral = Function2Histo(fit_nominal, Binning);
   TH1D* hist_Stat_up_integral =   Function2Histo(fit_Stat_up, Binning);
   TH1D* hist_Stat_down_integral = Function2Histo(fit_Stat_down, Binning);
   TH1D* hist_PromptSubtr_up_integral =   Function2Histo(fit_PromptSubtr_up, Binning);
   TH1D* hist_PromptSubtr_down_integral = Function2Histo(fit_PromptSubtr_down, Binning);
   TH1D* hist_d0sig_up_integral =   Function2Histo(fit_d0sig_up, Binning);
   TH1D* hist_d0sig_down_integral = Function2Histo(fit_d0sig_down, Binning);
   TH1D* hist_RealStat_up_integral =   Function2Histo(fit_RealStat_up, Binning);
   TH1D* hist_RealStat_down_integral = Function2Histo(fit_RealStat_down, Binning);
   TH1D* hist_function2_integral = Function2Histo(fit_function2, Binning);
   TH1D* hist_stitch_point_integral = Function2Histo(fit_stitch_point, Binning);

   TH1D* hist_FakeSys_up_integral = (TH1D *)hist_nominal_integral->Clone(histname + "_FakeSys_up_integral");
   TH1D* hist_FakeSys_down_integral = (TH1D *)hist_nominal_integral->Clone(histname + "_FakeSys_down_integral");

   for(int ibin = 1; ibin <= hist_nominal_integral->GetNbinsX(); ibin++){
     double Central = hist_nominal_integral->GetBinContent(ibin);
     double StatErr = hist_nominal_integral->GetBinError(ibin);

     double PromptSubtr_up = hist_PromptSubtr_up_integral->GetBinContent(ibin);
     double PromptSubtr_down = hist_PromptSubtr_down_integral->GetBinContent(ibin);
     double Stat_up = hist_Stat_up_integral->GetBinContent(ibin);
     double Stat_down = hist_Stat_down_integral->GetBinContent(ibin);
     double d0sig_up = hist_d0sig_up_integral->GetBinContent(ibin);
     double d0sig_down = hist_d0sig_down_integral->GetBinContent(ibin);
     double RealStat_up = hist_RealStat_up_integral->GetBinContent(ibin);
     double RealStat_down = hist_RealStat_down_integral->GetBinContent(ibin);
     double Function2 = hist_function2_integral->GetBinContent(ibin);
     double StitchingPoint = hist_stitch_point_integral->GetBinContent(ibin);

     if(PromptSubtr_up < 1e-10) PromptSubtr_up = Central;
     if(PromptSubtr_down < 1e-10) PromptSubtr_down = Central;
     if(Stat_up < 1e-10) Stat_up = Central;
     if(Stat_down < 1e-10) Stat_down = Central;
     if(d0sig_up < 1e-10) d0sig_up = Central;
     if(d0sig_down < 1e-10) d0sig_down = Central;
     if(RealStat_up < 1e-10) RealStat_up = Central;
     if(RealStat_down < 1e-10) RealStat_down = Central;

     double CombineError = sqrt(pow(max(fabs(Stat_up - Central), fabs(Central - Stat_down)), 2)
                              + pow(max(fabs(PromptSubtr_down - Central), fabs(Central - PromptSubtr_up)), 2)
                              + pow(max(fabs(Central - d0sig_up), fabs(Central - d0sig_down)), 2)
                              + pow(max(fabs(RealStat_up - Central), fabs(Central - RealStat_down)), 2)
                              + pow((Central - Function2), 2)
                              + pow((Central - StitchingPoint), 2));

     hist_FakeSys_up_integral->SetBinContent(ibin, Central + CombineError);
     hist_FakeSys_up_integral->SetBinError(ibin, 0.0);
     hist_FakeSys_down_integral->SetBinContent(ibin, Central - CombineError > 0.0 ? Central - CombineError : 1e-10);
     hist_FakeSys_down_integral->SetBinError(ibin, 0.0);
   }

   TH1D* hist_nominal_final = (TH1D *)hist_nominal_orig_bin->Clone(histname + "_final");
   TH1D* hist_FakeSys_up_final = (TH1D *)hist_FakeSys_up_orig_bin->Clone(histname + "_FakeSys_up_final");
   TH1D* hist_FakeSys_down_final = (TH1D *)hist_FakeSys_down_orig_bin->Clone(histname + "_FakeSys_down_final");
   TH1D* hist_nominal_Stat_up_final = (TH1D *)hist_Stat_up_orig_bin->Clone(histname + "_Stat_up_final");;
   TH1D* hist_nominal_Stat_down_final = (TH1D *)hist_Stat_down_orig_bin->Clone(histname + "_Stat_down_final");
   TH1D* hist_nominal_PromptSubtr_up_final = (TH1D *)hist_PromptSubtr_up_orig_bin->Clone(histname + "_PromptSubtr_up_final");
   TH1D* hist_nominal_PromptSubtr_down_final = (TH1D *)hist_PromptSubtr_down_orig_bin->Clone(histname + "_PromptSubtr_down_final");
   TH1D* hist_nominal_d0sig_up_final = (TH1D *)hist_d0sig_up_orig_bin->Clone(histname + "_d0sig_up_final");
   TH1D* hist_nominal_d0sig_down_final = (TH1D *)hist_d0sig_down_orig_bin->Clone(histname + "_d0sig_down_final");
   TH1D* hist_nominal_RealStat_up_final = (TH1D *)hist_RealStat_up_orig_bin->Clone(histname + "_RealStat_up_final");
   TH1D* hist_nominal_RealStat_down_final = (TH1D *)hist_RealStat_down_orig_bin->Clone(histname + "_RealStat_down_final");
   TH1D* hist_nominal_Function2_up_final = (TH1D *)hist_function2_integral->Clone(histname + "_Function2_up_final");
   TH1D* hist_nominal_Function2_down_final = (TH1D *)hist_function2_integral->Clone(histname + "_Function2_down_final");
   TH1D* hist_nominal_stitch_point_up_final = (TH1D *)hist_stitch_point_integral->Clone(histname + "_StitchingPoint_up_final");
   TH1D* hist_nominal_stitch_point_down_final = (TH1D *)hist_stitch_point_integral->Clone(histname + "_StitchingPoint_down_final");

   for(int ibin = 1; ibin <= hist_nominal_final->GetNbinsX(); ibin++){
     double Origin = hist_nominal_orig_bin->GetBinContent(ibin);
     double Origin_PromptSubtr_up = hist_PromptSubtr_up_orig_bin->GetBinContent(ibin);
     double Origin_PromptSubtr_down = hist_PromptSubtr_down_orig_bin->GetBinContent(ibin);
     double Origin_Stat_up = hist_Stat_up_orig_bin->GetBinContent(ibin);
     double Origin_Stat_down = hist_Stat_down_orig_bin->GetBinContent(ibin);
     double Origin_d0sig_up = hist_d0sig_up_orig_bin->GetBinContent(ibin);
     double Origin_d0sig_down = hist_d0sig_down_orig_bin->GetBinContent(ibin);
     double Origin_RealStat_up = hist_RealStat_up_orig_bin->GetBinContent(ibin);
     double Origin_RealStat_down = hist_RealStat_down_orig_bin->GetBinContent(ibin);

     double Integral = hist_nominal_integral->GetBinContent(ibin);
     double IntegralUp = hist_FakeSys_up_integral->GetBinContent(ibin);
     double IntegralDown = hist_FakeSys_down_integral->GetBinContent(ibin);

     double PromptSubtr_up = hist_PromptSubtr_up_integral->GetBinContent(ibin);
     double PromptSubtr_down = hist_PromptSubtr_down_integral->GetBinContent(ibin);
     double Stat_up = hist_Stat_up_integral->GetBinContent(ibin);
     double Stat_down = hist_Stat_down_integral->GetBinContent(ibin);
     double d0sig_up = hist_d0sig_up_integral->GetBinContent(ibin);
     double d0sig_down = hist_d0sig_down_integral->GetBinContent(ibin);
     double RealStat_up = hist_RealStat_up_integral->GetBinContent(ibin);
     double RealStat_down = hist_RealStat_down_integral->GetBinContent(ibin);
     double Function2 = hist_function2_integral->GetBinContent(ibin);
     double StitchingPoint = hist_stitch_point_integral->GetBinContent(ibin);

     if(Origin < 1e-20){
       hist_nominal_final->SetBinContent(ibin, Integral);
       hist_FakeSys_up_final->SetBinContent(ibin, IntegralUp);
       hist_FakeSys_down_final->SetBinContent(ibin, IntegralDown);

       double DeltaFunction2 = fabs(Integral - Function2);
       double DeltaStitchingPoint = fabs(Integral - StitchingPoint);
       hist_nominal_Function2_up_final->SetBinContent(ibin, Integral + DeltaFunction2);
       hist_nominal_Function2_down_final->SetBinContent(ibin, Integral - DeltaFunction2 > 0.0 ? Integral - DeltaFunction2 : 1e-10);
       hist_nominal_stitch_point_up_final->SetBinContent(ibin, Integral + DeltaStitchingPoint);
       hist_nominal_stitch_point_down_final->SetBinContent(ibin, Integral - DeltaStitchingPoint > 0.0 ? Integral - DeltaStitchingPoint : 1e-10);
     }
     else{
       hist_nominal_Function2_up_final->SetBinContent(ibin, Origin);
       hist_nominal_Function2_down_final->SetBinContent(ibin, Origin);
       hist_nominal_stitch_point_up_final->SetBinContent(ibin, Origin);
       hist_nominal_stitch_point_down_final->SetBinContent(ibin, Origin);
     }

     if(Origin_Stat_up < 1e-20){
       hist_nominal_Stat_up_final->SetBinContent(ibin, Stat_up);
     }

     if(Origin_Stat_down < 1e-20){
       hist_nominal_Stat_down_final->SetBinContent(ibin, Stat_down);
     }

     if(Origin_PromptSubtr_up < 1e-20){
       hist_nominal_PromptSubtr_up_final->SetBinContent(ibin, PromptSubtr_up);
     }

     if(Origin_PromptSubtr_down < 1e-20){
       hist_nominal_PromptSubtr_down_final->SetBinContent(ibin, PromptSubtr_down);
     }

     if(Origin_d0sig_up < 1e-20){
       hist_nominal_d0sig_up_final->SetBinContent(ibin, d0sig_up);
     }

     if(Origin_d0sig_down < 1e-20){
       hist_nominal_d0sig_down_final->SetBinContent(ibin, d0sig_down);
     }

     if(Origin_RealStat_up < 1e-20){
       hist_nominal_RealStat_up_final->SetBinContent(ibin, RealStat_up);
     }

     if(Origin_RealStat_down < 1e-20){
       hist_nominal_RealStat_down_final->SetBinContent(ibin, RealStat_down);
     }
   }

   Figure* f = new Figure(histname + "_Compare.png", "M [GeV]", "Events");
   f->SetMode("CUSTOM");
   f->Input(1, hist_nominal_orig_bin, "nominal origin");
   f->Input(2, hist_FakeSys_up_orig_bin, "up origin");
   f->Input(3, hist_FakeSys_down_orig_bin, "down origin");
   f->Input(4, hist_nominal_integral, "nominal integral");
   f->Input(5, hist_FakeSys_up_integral, "up integral");
   f->Input(6, hist_FakeSys_down_integral, "down integral");
   f->Compare("MultiRatio");
   f->SetLegendPosition(0.7, 0.6, 0.9, 0.9);
   f->SetLogX();
   f->SetLogY();
   f->SetCustomYRange(2, 0.0, 4.0);
   f->Draw();

   outfile->cd();
   hist_nominal->Write(histname + "_nominal");
   hist_Stat_up->Write(histname +   "_Stat_up");
   hist_Stat_down->Write(histname + "_Stat_down");
   hist_PromptSubtr_up->Write(histname +   "_PromptSubtr_up");
   hist_PromptSubtr_down->Write(histname + "_PromptSubtr_down");
   hist_d0sig_up->Write(histname +   "_d0sig_up");
   hist_d0sig_down->Write(histname + "_d0sig_down");
   hist_RealStat_up->Write(histname +   "_RealStat_up");
   hist_RealStat_down->Write(histname + "_RealStat_down");
   hist_function2->Write(histname + "_function2");
   hist_stitch_point->Write(histname + "_stitchpoint");
   hist_withsys->Write(histname + "_withsys");

   hist_nominal_orig_bin->Write(histname + "_nominal_orig_bin");
   hist_Stat_up_orig_bin->Write(histname +   "_Stat_up_orig_bin");
   hist_Stat_down_orig_bin->Write(histname + "_Stat_down_orig_bin");
   hist_PromptSubtr_up_orig_bin->Write(histname +   "_PromptSubtr_up_orig_bin");
   hist_PromptSubtr_down_orig_bin->Write(histname + "_PromptSubtr_down_orig_bin");
   hist_d0sig_up_orig_bin->Write(histname +   "_d0sig_up_orig_bin");
   hist_d0sig_down_orig_bin->Write(histname + "_d0sig_down_orig_bin");
   hist_RealStat_up_orig_bin->Write(histname +   "_RealStat_up_orig_bin");
   hist_RealStat_down_orig_bin->Write(histname + "_RealStat_down_orig_bin");
   hist_FakeSys_up_orig_bin->Write(histname + "_FakeSys_up_orig_bin");
   hist_FakeSys_down_orig_bin->Write(histname + "_FakeSys_down_orig_bin");

   fit_nominal->Write(histname + "_nominal_fit");
   fit_Stat_up->Write(histname +   "_Stat_up_fit");
   fit_Stat_down->Write(histname + "_Stat_down_fit");
   fit_PromptSubtr_up->Write(histname +   "_PromptSubtr_up_fit");
   fit_PromptSubtr_down->Write(histname + "_PromptSubtr_down_fit");
   fit_d0sig_up->Write(histname +   "_d0sig_up_fit");
   fit_d0sig_down->Write(histname + "_d0sig_down_fit");
   fit_RealStat_up->Write(histname +   "_RealStat_up_fit");
   fit_RealStat_down->Write(histname + "_RealStat_down_fit");
   fit_function2->Write(histname + "_function2_fit");
   fit_stitch_point->Write(histname + "_stitchpoint_fit");

   hist_nominal_integral->Write();
   hist_Stat_up_integral->Write();
   hist_Stat_down_integral->Write();
   hist_PromptSubtr_up_integral->Write();
   hist_PromptSubtr_down_integral->Write();
   hist_d0sig_up_integral->Write();
   hist_d0sig_down_integral->Write();
   hist_RealStat_up_integral->Write();
   hist_RealStat_down_integral->Write();
   hist_FakeSys_up_integral->Write();
   hist_FakeSys_down_integral->Write();
   hist_function2_integral->Write();
   hist_stitch_point_integral->Write();

   hist_nominal_final->Write();
   hist_FakeSys_up_final->Write();
   hist_FakeSys_down_final->Write();
   hist_nominal_Stat_up_final->Write();
   hist_nominal_Stat_down_final->Write();
   hist_nominal_PromptSubtr_up_final->Write();
   hist_nominal_PromptSubtr_down_final->Write();
   hist_nominal_d0sig_up_final->Write();
   hist_nominal_d0sig_down_final->Write();
   hist_nominal_RealStat_up_final->Write();
   hist_nominal_RealStat_down_final->Write();
   hist_nominal_Function2_up_final->Write();
   hist_nominal_Function2_down_final->Write();
   hist_nominal_stitch_point_up_final->Write();
   hist_nominal_stitch_point_down_final->Write();
 };

 TFile* MassFile_OriginBinning = new TFile("MC_results_Systematic.root");
 TH1D* MassHist_OriginBinning = (TH1D *)MassFile_OriginBinning->Get("Mll_HighMass_SR_mm_Wjets_DD_Nominal");

 TFile* MassFile = new TFile(MassFileName);
 TH1D* MassHist_nominal = (TH1D *)MassFile->Get(MassHistName + "/" + Process + "/nominal/" + MassHistName + "_" + Process + "_orig");
 MassHist_nominal->Scale(1.0, "width");

 TF1* MassFit1 = new TF1("MassFit1", Function1, 116.0, 5000.0);
 MassFit1->SetLineColor(kRed);
 MassFit1->SetLineWidth(2);
 MassHist_nominal->Fit(MassFit1, "S R L +");
 TH1D* MassFit1_Hist = Function2Histo(MassFit1, MassBinning);

 TF1* MassFit2 = new TF1("MassFit2", Function2, 116.0, 5000.0);
 MassFit2->SetLineColor(kBlue);
 MassFit2->SetLineWidth(2);
 MassHist_nominal->Fit(MassFit2, "W R +");
 TH1D* MassFit2_Hist = Function2Histo(MassFit2, MassBinning);

 TF1* MassFit3 = new TF1("MassFit3", Function3, 116.0, 5000.0);
 MassFit3->SetLineColor(kGreen);
 MassFit3->SetLineWidth(2);
 MassHist_nominal->Fit(MassFit3, "S R L +");
 TH1D* MassFit3_Hist = Function2Histo(MassFit3, MassBinning);

 Figure* f;
 f = new Figure("MuFake_FitCompare.png", "M [GeV]", "Events");
 f->SetMode("CUSTOM");
 f->Input(1, MassHist_OriginBinning, "Origin Histogram");
 f->Input(2, MassFit1_Hist, "Function 1 integration");
 f->Input(3, MassFit2_Hist, "Function 2 integration");
 f->Input(4, MassFit3_Hist, "Function 3 integration");
 f->SetLogX();
 f->SetLogY();
 f->Compare("MultiRatio");
 f->Draw();

 TFile* writefile = new TFile("MuFake_Extrapolation.root", "RECREATE");
 writefile->cd();
 MassHist_nominal->Write();
 MassFit1_Hist->Write();
 MassFit2_Hist->Write();
 MassFit3_Hist->Write();
 MassHist_OriginBinning->Write();

 FitHist(MassFileName, MassHistName, "Wjets_DD", writefile, MassBinning);
 FitHist(MassCosTheta1FileName, MassCosTheta1HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassCosTheta2FileName, MassCosTheta2HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassCosTheta3FileName, MassCosTheta3HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassCosTheta4FileName, MassCosTheta4HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassCosTheta5FileName, MassCosTheta5HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassCosTheta6FileName, MassCosTheta6HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassCosTheta7FileName, MassCosTheta7HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassCosTheta8FileName, MassCosTheta8HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassCosTheta9FileName, MassCosTheta9HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassCosTheta10FileName, MassCosTheta10HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassCosTheta11FileName, MassCosTheta11HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassCosTheta12FileName, MassCosTheta12HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassCosTheta13FileName, MassCosTheta13HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassCosTheta14FileName, MassCosTheta14HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassCosTheta15FileName, MassCosTheta15HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassCosTheta16FileName, MassCosTheta16HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassCosTheta17FileName, MassCosTheta17HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassCosTheta18FileName, MassCosTheta18HistName, "Wjets_DD", writefile, MassBinning2);

 FitHist(MassRapidity1FileName, MassRapidity1HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassRapidity2FileName, MassRapidity2HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassRapidity3FileName, MassRapidity3HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassRapidity4FileName, MassRapidity4HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassRapidity5FileName, MassRapidity5HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassRapidity6FileName, MassRapidity6HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassRapidity7FileName, MassRapidity7HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassRapidity8FileName, MassRapidity8HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassRapidity9FileName, MassRapidity9HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassRapidity10FileName, MassRapidity10HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassRapidity11FileName, MassRapidity11HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassRapidity12FileName, MassRapidity12HistName, "Wjets_DD", writefile, MassBinning1);
 FitHist(MassRapidity13FileName, MassRapidity13HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassRapidity14FileName, MassRapidity14HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassRapidity15FileName, MassRapidity15HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassRapidity16FileName, MassRapidity16HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassRapidity17FileName, MassRapidity17HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassRapidity18FileName, MassRapidity18HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassRapidity19FileName, MassRapidity19HistName, "Wjets_DD", writefile, MassBinning2);
 FitHist(MassRapidity20FileName, MassRapidity20HistName, "Wjets_DD", writefile, MassBinning2);

 writefile->Close();

}
