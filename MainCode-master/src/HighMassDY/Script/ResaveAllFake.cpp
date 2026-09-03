#include "/home/yaofu/figure/Figure.h"

void ResaveAllFake()
{
 TString histName[100];
 histName[0] = "Mll_HighMass";
 histName[1] = "pTll";
 histName[2] = "costheta";
 histName[3] = "DilRapidity";
 histName[4] = "LeadingLepEta";
 histName[5] = "SubleadingLepEta";
 histName[6] = "DilRapidity_HighMass";
 histName[7] = "DilRapidity_LowMass";

 TFile* ElFake_MM_file = new TFile("Analysis/MC_results_Systematic.root");
 TFile* ElFake_FF_file = new TFile("../ElFakeRate/Analysis/MC_results.root");
 TFile* MuFake_MM_file = new TFile("Analysis_Muon/MC_results_Systematic.root");

 TFile* writefile = new TFile("FinalFakeHistogram.root", "RECREATE");
 writefile->cd();

 for(int ihist = 0; ihist <= 7; ihist++){
   TH1D* ElFakeHist_Nominal = (TH1D *)ElFake_MM_file->Get(histName[ihist] + "_SR_ee_Wjets_DD_Nominal");
   TH1D* ElFakeHist_Stat_up = (TH1D *)ElFake_MM_file->Get(histName[ihist] + "_Fake_El_Stat_up");
   TH1D* ElFakeHist_Stat_down = (TH1D *)ElFake_MM_file->Get(histName[ihist] + "_Fake_El_Stat_down");
   TH1D* ElFakeHist_PromptSubtr_up = (TH1D *)ElFake_MM_file->Get(histName[ihist] + "_Fake_El_PromptSubtr_up");
   TH1D* ElFakeHist_PromptSubtr_down = (TH1D *)ElFake_MM_file->Get(histName[ihist] + "_Fake_El_PromptSubtr_down");
   TH1D* ElFakeHist_RealStat_up = (TH1D *)ElFake_MM_file->Get(histName[ihist] + "_Fake_El_RealStat_up");
   TH1D* ElFakeHist_RealStat_down = (TH1D *)ElFake_MM_file->Get(histName[ihist] + "_Fake_El_RealStat_down");

   TH1D* ElFakeHist_FakeRate = (TH1D *)ElFake_FF_file->Get(histName[ihist] + "_Wjets_FakeRate");
   TH1D* ElFakeHist_FakeRate_Stat_up = (TH1D *)ElFake_FF_file->Get(histName[ihist] + "_Wjets_FakeRate_Stat_up");
   TH1D* ElFakeHist_FakeRate_Stat_down = (TH1D *)ElFake_FF_file->Get(histName[ihist] + "_Wjets_FakeRate_Stat_down");
   TH1D* ElFakeHist_FakeRate_PromptSubtr_up = (TH1D *)ElFake_FF_file->Get(histName[ihist] + "_Wjets_FakeRate_PromptSubtr_up");
   TH1D* ElFakeHist_FakeRate_PromptSubtr_down = (TH1D *)ElFake_FF_file->Get(histName[ihist] + "_Wjets_FakeRate_PromptSubtr_down");

   TH1D* ElFakeHist_StressTest = (TH1D *)ElFakeHist_Nominal->Clone(histName[ihist] + "_StressTest");
   ElFakeHist_StressTest->Reset();
   for(int ibin = 1; ibin <= ElFakeHist_Nominal->GetNbinsX(); ibin++){
     double MM_Nominal = ElFakeHist_Nominal->GetBinContent(ibin);
     double FF_Nominal = ElFakeHist_FakeRate->GetBinContent(ibin);

     double MM_StatErr = ElFakeHist_Nominal->GetBinError(ibin);

     double MM_PromptSubtr_up = ElFakeHist_PromptSubtr_up->GetBinContent(ibin);
     double MM_PromptSubtr_down = ElFakeHist_PromptSubtr_down->GetBinContent(ibin);
     double MM_Stat_up = ElFakeHist_Stat_up->GetBinContent(ibin);
     double MM_Stat_down = ElFakeHist_Stat_down->GetBinContent(ibin);
     double MM_RealStat_up = ElFakeHist_RealStat_up->GetBinContent(ibin);
     double MM_RealStat_down = ElFakeHist_RealStat_down->GetBinContent(ibin);

     double FF_PromptSubtr_up = ElFakeHist_FakeRate_PromptSubtr_up->GetBinContent(ibin);
     double FF_PromptSubtr_down = ElFakeHist_FakeRate_PromptSubtr_down->GetBinContent(ibin);
     double FF_Stat_up = ElFakeHist_FakeRate_Stat_up->GetBinContent(ibin);
     double FF_Stat_down = ElFakeHist_FakeRate_Stat_down->GetBinContent(ibin);

     double CombineError = 0.0;

     if(MM_Nominal > FF_Nominal){
       CombineError = sqrt(pow(max(fabs(MM_Nominal - MM_PromptSubtr_up), fabs(MM_Nominal - MM_PromptSubtr_down)), 2)
                              + pow(max(fabs(MM_Nominal - MM_Stat_up), fabs(MM_Nominal - MM_Stat_down)), 2)
                              + pow(max(fabs(MM_Nominal - MM_RealStat_up), fabs(MM_Nominal - MM_RealStat_down)), 2));
     }
     else{
       CombineError = sqrt(pow(max(fabs(FF_Nominal - FF_PromptSubtr_up), fabs(FF_Nominal - FF_PromptSubtr_down)), 2)
                              + pow(max(fabs(FF_Nominal - FF_Stat_up), fabs(FF_Nominal - FF_Stat_down)), 2));

     }

     double Value = max(MM_Nominal, FF_Nominal);
     ElFakeHist_StressTest->SetBinContent(ibin, Value);
     ElFakeHist_StressTest->SetBinError(ibin, CombineError);
   }

   TH1D* MuFakeHist_Nominal = (TH1D *)MuFake_MM_file->Get(histName[ihist] + "_SR_mm_Wjets_DD_Nominal");
   TH1D* MuFakeHist_Stat_up = (TH1D *)MuFake_MM_file->Get(histName[ihist] + "_Fake_Mu_Stat_up");
   TH1D* MuFakeHist_Stat_down = (TH1D *)MuFake_MM_file->Get(histName[ihist] + "_Fake_Mu_Stat_down");
   TH1D* MuFakeHist_d0sig_up = (TH1D *)MuFake_MM_file->Get(histName[ihist] + "_Fake_Mu_d0sig_up");
   TH1D* MuFakeHist_d0sig_down = (TH1D *)MuFake_MM_file->Get(histName[ihist] + "_Fake_Mu_d0sig_down");
   TH1D* MuFakeHist_PromptSubtr_up = (TH1D *)MuFake_MM_file->Get(histName[ihist] + "_Fake_Mu_PromptSubtr_up");
   TH1D* MuFakeHist_PromptSubtr_down = (TH1D *)MuFake_MM_file->Get(histName[ihist] + "_Fake_Mu_PromptSubtr_down");
   TH1D* MuFakeHist_RealStat_up = (TH1D *)MuFake_MM_file->Get(histName[ihist] + "_Fake_Mu_RealStat_up");
   TH1D* MuFakeHist_RealStat_down = (TH1D *)MuFake_MM_file->Get(histName[ihist] + "_Fake_Mu_RealStat_down");

   ElFakeHist_Nominal->Write();
   ElFakeHist_Stat_up->Write();
   ElFakeHist_Stat_down->Write();
   ElFakeHist_PromptSubtr_up->Write();
   ElFakeHist_PromptSubtr_down->Write();
   ElFakeHist_RealStat_up->Write();
   ElFakeHist_RealStat_down->Write();
   ElFakeHist_FakeRate->Write();
   ElFakeHist_FakeRate_Stat_up->Write();
   ElFakeHist_FakeRate_Stat_down->Write();
   ElFakeHist_FakeRate_PromptSubtr_up->Write();
   ElFakeHist_FakeRate_PromptSubtr_down->Write();
   ElFakeHist_StressTest->Write();

   MuFakeHist_Nominal->Write();
   MuFakeHist_Stat_up->Write();
   MuFakeHist_Stat_down->Write();
   MuFakeHist_d0sig_up->Write();
   MuFakeHist_d0sig_down->Write();
   MuFakeHist_PromptSubtr_up->Write();
   MuFakeHist_PromptSubtr_down->Write();
   MuFakeHist_RealStat_up->Write();
   MuFakeHist_RealStat_down->Write();
 }

 writefile->Close();
}
