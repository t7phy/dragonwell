#include "/home/yfu/figure/Figure.h"

void combine_extrapolation()
{
 TString MassHistName = "Mll_HighMass";
 vector<TString> MassCosTheta1Names(10);
 vector<TString> MassCosTheta2Names(8);
 vector<TString> MassRapidity1Names(12);
 vector<TString> MassRapidity2Names(8);

 MassCosTheta1Names.at(0) = "Mll_HighMass_costhetastar_0p00_0p20";
 MassCosTheta1Names.at(1) = "Mll_HighMass_costhetastar_0p20_0p40";
 MassCosTheta1Names.at(2) = "Mll_HighMass_costhetastar_0p40_0p60";
 MassCosTheta1Names.at(3) = "Mll_HighMass_costhetastar_0p60_0p80";
 MassCosTheta1Names.at(4) = "Mll_HighMass_costhetastar_0p80_1p00";
 MassCosTheta1Names.at(5) = "Mll_HighMass_costhetastar_m0p20_0p00";
 MassCosTheta1Names.at(6) = "Mll_HighMass_costhetastar_m0p40_m0p20";
 MassCosTheta1Names.at(7) = "Mll_HighMass_costhetastar_m0p60_m0p40";
 MassCosTheta1Names.at(8) = "Mll_HighMass_costhetastar_m0p80_m0p60";
 MassCosTheta1Names.at(9) = "Mll_HighMass_costhetastar_m1p00_m0p80";

 MassCosTheta2Names.at(0) = "Mll_HighMass_costhetastar_0p00_0p25";
 MassCosTheta2Names.at(1) = "Mll_HighMass_costhetastar_0p25_0p50";
 MassCosTheta2Names.at(2) = "Mll_HighMass_costhetastar_0p50_0p75";
 MassCosTheta2Names.at(3) = "Mll_HighMass_costhetastar_0p75_1p00";
 MassCosTheta2Names.at(4) = "Mll_HighMass_costhetastar_m0p25_0p00";
 MassCosTheta2Names.at(5) = "Mll_HighMass_costhetastar_m0p50_m0p25";
 MassCosTheta2Names.at(6) = "Mll_HighMass_costhetastar_m0p75_m0p50";
 MassCosTheta2Names.at(7) = "Mll_HighMass_costhetastar_m1p00_m0p75";

 MassRapidity1Names.at(0) = "Mll_HighMass_yll_0p00_0p20";
 MassRapidity1Names.at(1) = "Mll_HighMass_yll_0p20_0p40";
 MassRapidity1Names.at(2) = "Mll_HighMass_yll_0p40_0p60";
 MassRapidity1Names.at(3) = "Mll_HighMass_yll_0p60_0p80";
 MassRapidity1Names.at(4) = "Mll_HighMass_yll_0p80_1p00";
 MassRapidity1Names.at(5) = "Mll_HighMass_yll_1p00_1p20";
 MassRapidity1Names.at(6) = "Mll_HighMass_yll_1p20_1p40";
 MassRapidity1Names.at(7) = "Mll_HighMass_yll_1p40_1p60";
 MassRapidity1Names.at(8) = "Mll_HighMass_yll_1p60_1p80";
 MassRapidity1Names.at(9) = "Mll_HighMass_yll_1p80_2p00";
 MassRapidity1Names.at(10) = "Mll_HighMass_yll_2p00_2p20";
 MassRapidity1Names.at(11) = "Mll_HighMass_yll_2p20_2p40";

 MassRapidity2Names.at(0) = "Mll_HighMass_yll_0p00_0p30";
 MassRapidity2Names.at(1) = "Mll_HighMass_yll_0p30_0p60";
 MassRapidity2Names.at(2) = "Mll_HighMass_yll_0p60_0p90";
 MassRapidity2Names.at(3) = "Mll_HighMass_yll_0p90_1p20";
 MassRapidity2Names.at(4) = "Mll_HighMass_yll_1p20_1p50";
 MassRapidity2Names.at(5) = "Mll_HighMass_yll_1p50_1p80";
 MassRapidity2Names.at(6) = "Mll_HighMass_yll_1p80_2p10";
 MassRapidity2Names.at(7) = "Mll_HighMass_yll_2p10_2p40";

 vector<TH1D *> MassCosTheta1Hists(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2Hists(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1Hists(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2Hists(MassRapidity2Names.size());

 vector<TH1D *> MassCosTheta1Up(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2Up(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1Up(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2Up(MassRapidity2Names.size());

 vector<TH1D *> MassCosTheta1Down(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2Down(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1Down(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2Down(MassRapidity2Names.size());

 vector<TH1D *> MassCosTheta1_Stat_up(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2_Stat_up(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1_Stat_up(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2_Stat_up(MassRapidity2Names.size());
 vector<TH1D *> MassCosTheta1_Stat_down(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2_Stat_down(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1_Stat_down(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2_Stat_down(MassRapidity2Names.size());

 vector<TH1D *> MassCosTheta1_PromptSubtr_up(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2_PromptSubtr_up(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1_PromptSubtr_up(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2_PromptSubtr_up(MassRapidity2Names.size());
 vector<TH1D *> MassCosTheta1_PromptSubtr_down(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2_PromptSubtr_down(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1_PromptSubtr_down(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2_PromptSubtr_down(MassRapidity2Names.size());

 vector<TH1D *> MassCosTheta1_d0sig_up(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2_d0sig_up(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1_d0sig_up(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2_d0sig_up(MassRapidity2Names.size());
 vector<TH1D *> MassCosTheta1_d0sig_down(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2_d0sig_down(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1_d0sig_down(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2_d0sig_down(MassRapidity2Names.size());

 vector<TH1D *> MassCosTheta1_RealStat_up(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2_RealStat_up(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1_RealStat_up(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2_RealStat_up(MassRapidity2Names.size());
 vector<TH1D *> MassCosTheta1_RealStat_down(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2_RealStat_down(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1_RealStat_down(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2_RealStat_down(MassRapidity2Names.size());

 vector<TH1D *> MassCosTheta1_Function2_up(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2_Function2_up(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1_Function2_up(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2_Function2_up(MassRapidity2Names.size());
 vector<TH1D *> MassCosTheta1_Function2_down(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2_Function2_down(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1_Function2_down(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2_Function2_down(MassRapidity2Names.size());

 vector<TH1D *> MassCosTheta1_StitchingPoint_up(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2_StitchingPoint_up(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1_StitchingPoint_up(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2_StitchingPoint_up(MassRapidity2Names.size());
 vector<TH1D *> MassCosTheta1_StitchingPoint_down(MassCosTheta1Names.size());
 vector<TH1D *> MassCosTheta2_StitchingPoint_down(MassCosTheta2Names.size());
 vector<TH1D *> MassRapidity1_StitchingPoint_down(MassRapidity1Names.size());
 vector<TH1D *> MassRapidity2_StitchingPoint_down(MassRapidity2Names.size());

 TFile* file = new TFile("MuFake_Extrapolation.root");

 TH1D* Mass_nominal = (TH1D *)file->Get(MassHistName + "_final");
 TH1D* Mass_up = (TH1D *)file->Get(MassHistName + "_FakeSys_up_final");
 TH1D* Mass_down = (TH1D *)file->Get(MassHistName + "_FakeSys_down_final");
 TH1D* Mass_Stat_up = (TH1D *)file->Get(MassHistName + "_Stat_up_final");
 TH1D* Mass_Stat_down = (TH1D *)file->Get(MassHistName + "_Stat_down_final");
 TH1D* Mass_PromptSubtr_up = (TH1D *)file->Get(MassHistName + "_PromptSubtr_up_final");
 TH1D* Mass_PromptSubtr_down = (TH1D *)file->Get(MassHistName + "_PromptSubtr_down_final");
 TH1D* Mass_d0sig_up = (TH1D *)file->Get(MassHistName + "_d0sig_up_final");
 TH1D* Mass_d0sig_down = (TH1D *)file->Get(MassHistName + "_d0sig_down_final");
 TH1D* Mass_RealStat_up = (TH1D *)file->Get(MassHistName + "_RealStat_up_final");
 TH1D* Mass_RealStat_down = (TH1D *)file->Get(MassHistName + "_RealStat_down_final");
 TH1D* Mass_Function2_up = (TH1D *)file->Get(MassHistName + "_Function2_up_final");
 TH1D* Mass_Function2_down = (TH1D *)file->Get(MassHistName + "_Function2_down_final");
 TH1D* Mass_StitchingPoint_up = (TH1D *)file->Get(MassHistName + "_StitchingPoint_up_final");
 TH1D* Mass_StitchingPoint_down = (TH1D *)file->Get(MassHistName + "_StitchingPoint_down_final");

 for(int ihist = 0; ihist < MassCosTheta1Names.size(); ihist++){
   MassCosTheta1Hists.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_final");
   MassCosTheta1Up.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_FakeSys_up_final");
   MassCosTheta1Down.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_FakeSys_down_final");
   MassCosTheta1_Stat_up.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_Stat_up_final");
   MassCosTheta1_Stat_down.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_Stat_down_final");
   MassCosTheta1_PromptSubtr_up.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_PromptSubtr_up_final");
   MassCosTheta1_PromptSubtr_down.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_PromptSubtr_down_final");
   MassCosTheta1_d0sig_up.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_d0sig_up_final");
   MassCosTheta1_d0sig_down.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_d0sig_down_final");
   MassCosTheta1_RealStat_up.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_RealStat_up_final");
   MassCosTheta1_RealStat_down.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_RealStat_down_final");
   MassCosTheta1_Function2_up.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_Function2_up_final");
   MassCosTheta1_Function2_down.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_Function2_down_final");
   MassCosTheta1_StitchingPoint_up.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_StitchingPoint_up_final");
   MassCosTheta1_StitchingPoint_down.at(ihist) = (TH1D *)file->Get(MassCosTheta1Names.at(ihist) + "_StitchingPoint_down_final");
 }
 for(int ihist = 0; ihist < MassCosTheta2Names.size(); ihist++){
   MassCosTheta2Hists.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_final");
   MassCosTheta2Up.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_FakeSys_up_final");
   MassCosTheta2Down.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_FakeSys_down_final");
   MassCosTheta2_Stat_up.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_Stat_up_final");
   MassCosTheta2_Stat_down.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_Stat_down_final");
   MassCosTheta2_PromptSubtr_up.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_PromptSubtr_up_final");
   MassCosTheta2_PromptSubtr_down.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_PromptSubtr_down_final");
   MassCosTheta2_d0sig_up.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_d0sig_up_final");
   MassCosTheta2_d0sig_down.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_d0sig_down_final");
   MassCosTheta2_RealStat_up.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_RealStat_up_final");
   MassCosTheta2_RealStat_down.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_RealStat_down_final");
   MassCosTheta2_Function2_up.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_Function2_up_final");
   MassCosTheta2_Function2_down.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_Function2_down_final");
   MassCosTheta2_StitchingPoint_up.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_StitchingPoint_up_final");
   MassCosTheta2_StitchingPoint_down.at(ihist) = (TH1D *)file->Get(MassCosTheta2Names.at(ihist) + "_StitchingPoint_down_final");
 }


 for(int ihist = 0; ihist < MassRapidity1Names.size(); ihist++){
   MassRapidity1Hists.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_final");
   MassRapidity1Up.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_FakeSys_up_final");
   MassRapidity1Down.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_FakeSys_down_final");
   MassRapidity1_Stat_up.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_Stat_up_final");
   MassRapidity1_Stat_down.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_Stat_down_final");
   MassRapidity1_PromptSubtr_up.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_PromptSubtr_up_final");
   MassRapidity1_PromptSubtr_down.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_PromptSubtr_down_final");
   MassRapidity1_d0sig_up.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_d0sig_up_final");
   MassRapidity1_d0sig_down.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_d0sig_down_final");
   MassRapidity1_RealStat_up.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_RealStat_up_final");
   MassRapidity1_RealStat_down.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_RealStat_down_final");
   MassRapidity1_Function2_up.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_Function2_up_final");
   MassRapidity1_Function2_down.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_Function2_down_final");
   MassRapidity1_StitchingPoint_up.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_StitchingPoint_up_final");
   MassRapidity1_StitchingPoint_down.at(ihist) = (TH1D *)file->Get(MassRapidity1Names.at(ihist) + "_StitchingPoint_down_final");
 }
 for(int ihist = 0; ihist < MassRapidity2Names.size(); ihist++){
   MassRapidity2Hists.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_final");
   MassRapidity2Up.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_FakeSys_up_final");
   MassRapidity2Down.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_FakeSys_down_final");
   MassRapidity2_Stat_up.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_Stat_up_final");
   MassRapidity2_Stat_down.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_Stat_down_final");
   MassRapidity2_PromptSubtr_up.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_PromptSubtr_up_final");
   MassRapidity2_PromptSubtr_down.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_PromptSubtr_down_final");
   MassRapidity2_d0sig_up.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_d0sig_up_final");
   MassRapidity2_d0sig_down.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_d0sig_down_final");
   MassRapidity2_RealStat_up.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_RealStat_up_final");
   MassRapidity2_RealStat_down.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_RealStat_down_final");
   MassRapidity2_Function2_up.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_Function2_up_final");
   MassRapidity2_Function2_down.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_Function2_down_final");
   MassRapidity2_StitchingPoint_up.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_StitchingPoint_up_final");
   MassRapidity2_StitchingPoint_down.at(ihist) = (TH1D *)file->Get(MassRapidity2Names.at(ihist) + "_StitchingPoint_down_final");
 }

 TH1D* MassCosTheta2D_nominal = new TH1D("MassCosTheta_nominal", "MassCosTheta_nominal", 49, 0, 49);
 TH1D* MassCosTheta2D_up = new TH1D("MassCosTheta_up", "MassCosTheta_up", 49, 0, 49);
 TH1D* MassCosTheta2D_down = new TH1D("MassCosTheta_down", "MassCosTheta_down", 49, 0, 49);
 TH1D* MassCosTheta2D_Stat_up = new TH1D("MassCosTheta_Stat_up", "MassCosTheta_Stat_up", 49, 0, 49);
 TH1D* MassCosTheta2D_Stat_down = new TH1D("MassCosTheta_Stat_down", "MassCosTheta_Stat_down", 49, 0, 49);
 TH1D* MassCosTheta2D_PromptSubtr_up = new TH1D("MassCosTheta_PromptSubtr_up", "MassCosTheta_PromptSubtr_up", 49, 0, 49);
 TH1D* MassCosTheta2D_PromptSubtr_down = new TH1D("MassCosTheta_PromptSubtr_down", "MassCosTheta_PromptSubtr_down", 49, 0, 49);
 TH1D* MassCosTheta2D_d0sig_up = new TH1D("MassCosTheta_d0sig_up", "MassCosTheta_d0sig_up", 49, 0, 49);
 TH1D* MassCosTheta2D_d0sig_down = new TH1D("MassCosTheta_d0sig_down", "MassCosTheta_d0sig_down", 49, 0, 49);
 TH1D* MassCosTheta2D_RealStat_up = new TH1D("MassCosTheta_RealStat_up", "MassCosTheta_RealStat_up", 49, 0, 49);
 TH1D* MassCosTheta2D_RealStat_down = new TH1D("MassCosTheta_RealStat_down", "MassCosTheta_RealStat_down", 49, 0, 49);
 TH1D* MassCosTheta2D_Function2_up = new TH1D("MassCosTheta_Function2_up", "MassCosTheta_Function2_up", 49, 0, 49);
 TH1D* MassCosTheta2D_Function2_down = new TH1D("MassCosTheta_Function2_down", "MassCosTheta_Function2_down", 49, 0, 49);
 TH1D* MassCosTheta2D_StitchingPoint_up = new TH1D("MassCosTheta_StitchingPoint_up", "MassCosTheta_StitchingPoint_up", 49, 0, 49);
 TH1D* MassCosTheta2D_StitchingPoint_down = new TH1D("MassCosTheta_StitchingPoint_down", "MassCosTheta_StitchingPoint_down", 49, 0, 49);

 TH1D* MassRapidity2D_nominal = new TH1D("MassRapidity_nominal", "MassRapidity_nominal", 57, 0, 57);
 TH1D* MassRapidity2D_up = new TH1D("MassRapidity_up", "MassRapidity_up", 57, 0, 57);
 TH1D* MassRapidity2D_down = new TH1D("MassRapidity_down", "MassRapidity_down", 57, 0, 57);
 TH1D* MassRapidity2D_Stat_up = new TH1D("MassRapidity_Stat_up", "MassRapidity_Stat_up", 57, 0, 57);
 TH1D* MassRapidity2D_Stat_down = new TH1D("MassRapidity_Stat_down", "MassRapidity_Stat_down", 57, 0, 57);
 TH1D* MassRapidity2D_PromptSubtr_up = new TH1D("MassRapidity_PromptSubtr_up", "MassRapidity_PromptSubtr_up", 57, 0, 57);
 TH1D* MassRapidity2D_PromptSubtr_down = new TH1D("MassRapidity_PromptSubtr_down", "MassRapidity_PromptSubtr_down", 57, 0, 57);
 TH1D* MassRapidity2D_d0sig_up = new TH1D("MassRapidity_d0sig_up", "MassRapidity_d0sig_up", 57, 0, 57);
 TH1D* MassRapidity2D_d0sig_down = new TH1D("MassRapidity_d0sig_down", "MassRapidity_d0sig_down", 57, 0, 57);
 TH1D* MassRapidity2D_RealStat_up = new TH1D("MassRapidity_RealStat_up", "MassRapidity_RealStat_up", 57, 0, 57);
 TH1D* MassRapidity2D_RealStat_down = new TH1D("MassRapidity_RealStat_down", "MassRapidity_RealStat_down", 57, 0, 57);
 TH1D* MassRapidity2D_Function2_up = new TH1D("MassRapidity_Function2_up", "MassRapidity_Function2_up", 57, 0, 57);
 TH1D* MassRapidity2D_Function2_down = new TH1D("MassRapidity_Function2_down", "MassRapidity_Function2_down", 57, 0, 57);
 TH1D* MassRapidity2D_StitchingPoint_up = new TH1D("MassRapidity_StitchingPoint_up", "MassRapidity_StitchingPoint_up", 57, 0, 57);
 TH1D* MassRapidity2D_StitchingPoint_down = new TH1D("MassRapidity_StitchingPoint_down", "MassRapidity_StitchingPoint_down", 57, 0, 57);

 int BinIndex = 1;
 for(int ibin = 1; ibin <= MassCosTheta1Hists.at(0)->GetNbinsX(); ibin++){
   for(int ihist = 0; ihist < MassCosTheta1Hists.size(); ihist++){
     double Central = MassCosTheta1Hists.at(ihist)->GetBinContent(ibin);
     double Up = MassCosTheta1Up.at(ihist)->GetBinContent(ibin);
     double Down = MassCosTheta1Down.at(ihist)->GetBinContent(ibin);
     double Stat_up = MassCosTheta1_Stat_up.at(ihist)->GetBinContent(ibin);
     double Stat_down = MassCosTheta1_Stat_down.at(ihist)->GetBinContent(ibin);
     double PromptSubtr_up = MassCosTheta1_PromptSubtr_up.at(ihist)->GetBinContent(ibin);
     double PromptSubtr_down = MassCosTheta1_PromptSubtr_down.at(ihist)->GetBinContent(ibin);
     double d0sig_up = MassCosTheta1_d0sig_up.at(ihist)->GetBinContent(ibin);
     double d0sig_down = MassCosTheta1_d0sig_down.at(ihist)->GetBinContent(ibin);
     double RealStat_up = MassCosTheta1_RealStat_up.at(ihist)->GetBinContent(ibin);
     double RealStat_down = MassCosTheta1_RealStat_down.at(ihist)->GetBinContent(ibin);
     double Function2_up = MassCosTheta1_Function2_up.at(ihist)->GetBinContent(ibin);
     double Function2_down = MassCosTheta1_Function2_down.at(ihist)->GetBinContent(ibin);
     double StitchingPoint_up = MassCosTheta1_StitchingPoint_up.at(ihist)->GetBinContent(ibin);
     double StitchingPoint_down = MassCosTheta1_StitchingPoint_down.at(ihist)->GetBinContent(ibin);

     MassCosTheta2D_nominal->SetBinContent(BinIndex, Central);
     MassCosTheta2D_up->SetBinContent(BinIndex, Up);
     MassCosTheta2D_down->SetBinContent(BinIndex, Down);
     MassCosTheta2D_Stat_up->SetBinContent(BinIndex, Stat_up);
     MassCosTheta2D_Stat_down->SetBinContent(BinIndex, Stat_down);
     MassCosTheta2D_PromptSubtr_up->SetBinContent(BinIndex, PromptSubtr_up);
     MassCosTheta2D_PromptSubtr_down->SetBinContent(BinIndex, PromptSubtr_down);
     MassCosTheta2D_d0sig_up->SetBinContent(BinIndex, d0sig_up);
     MassCosTheta2D_d0sig_down->SetBinContent(BinIndex, d0sig_down);
     MassCosTheta2D_RealStat_up->SetBinContent(BinIndex, RealStat_up);
     MassCosTheta2D_RealStat_down->SetBinContent(BinIndex, RealStat_down);
     MassCosTheta2D_Function2_up->SetBinContent(BinIndex, Function2_up);
     MassCosTheta2D_Function2_down->SetBinContent(BinIndex, Function2_down);
     MassCosTheta2D_StitchingPoint_up->SetBinContent(BinIndex, StitchingPoint_up);
     MassCosTheta2D_StitchingPoint_down->SetBinContent(BinIndex, StitchingPoint_down);
     BinIndex++;
   }
 }

 for(int ibin = 1; ibin <= MassCosTheta2Hists.at(0)->GetNbinsX(); ibin++){
   for(int ihist = 0; ihist < MassCosTheta2Hists.size(); ihist++){
     double Central = MassCosTheta2Hists.at(ihist)->GetBinContent(ibin);
     double Up = MassCosTheta2Up.at(ihist)->GetBinContent(ibin);
     double Down = MassCosTheta2Down.at(ihist)->GetBinContent(ibin);
     double Stat_up = MassCosTheta2_Stat_up.at(ihist)->GetBinContent(ibin);
     double Stat_down = MassCosTheta2_Stat_down.at(ihist)->GetBinContent(ibin);
     double PromptSubtr_up = MassCosTheta2_PromptSubtr_up.at(ihist)->GetBinContent(ibin);
     double PromptSubtr_down = MassCosTheta2_PromptSubtr_down.at(ihist)->GetBinContent(ibin);
     double d0sig_up = MassCosTheta2_d0sig_up.at(ihist)->GetBinContent(ibin);
     double d0sig_down = MassCosTheta2_d0sig_down.at(ihist)->GetBinContent(ibin);
     double RealStat_up = MassCosTheta2_RealStat_up.at(ihist)->GetBinContent(ibin);
     double RealStat_down = MassCosTheta2_RealStat_down.at(ihist)->GetBinContent(ibin);
     double Function2_up = MassCosTheta2_Function2_up.at(ihist)->GetBinContent(ibin);
     double Function2_down = MassCosTheta2_Function2_down.at(ihist)->GetBinContent(ibin);
     double StitchingPoint_up = MassCosTheta2_StitchingPoint_up.at(ihist)->GetBinContent(ibin);
     double StitchingPoint_down = MassCosTheta2_StitchingPoint_down.at(ihist)->GetBinContent(ibin);

     MassCosTheta2D_nominal->SetBinContent(BinIndex, Central);
     MassCosTheta2D_up->SetBinContent(BinIndex, Up);
     MassCosTheta2D_down->SetBinContent(BinIndex, Down);
     MassCosTheta2D_Stat_up->SetBinContent(BinIndex, Stat_up);
     MassCosTheta2D_Stat_down->SetBinContent(BinIndex, Stat_down);
     MassCosTheta2D_PromptSubtr_up->SetBinContent(BinIndex, PromptSubtr_up);
     MassCosTheta2D_PromptSubtr_down->SetBinContent(BinIndex, PromptSubtr_down);
     MassCosTheta2D_d0sig_up->SetBinContent(BinIndex, d0sig_up);
     MassCosTheta2D_d0sig_down->SetBinContent(BinIndex, d0sig_down);
     MassCosTheta2D_RealStat_up->SetBinContent(BinIndex, RealStat_up);
     MassCosTheta2D_RealStat_down->SetBinContent(BinIndex, RealStat_down);
     MassCosTheta2D_Function2_up->SetBinContent(BinIndex, Function2_up);
     MassCosTheta2D_Function2_down->SetBinContent(BinIndex, Function2_down);
     MassCosTheta2D_StitchingPoint_up->SetBinContent(BinIndex, StitchingPoint_up);
     MassCosTheta2D_StitchingPoint_down->SetBinContent(BinIndex, StitchingPoint_down);
     BinIndex++;
   }
 }

 MassCosTheta2D_nominal->SetBinContent(BinIndex, Mass_nominal->GetBinContent(13));
 MassCosTheta2D_up->SetBinContent(BinIndex, Mass_up->GetBinContent(13));
 MassCosTheta2D_down->SetBinContent(BinIndex, Mass_down->GetBinContent(13));
 MassCosTheta2D_Stat_up->SetBinContent(BinIndex, Mass_Stat_up->GetBinContent(13));
 MassCosTheta2D_Stat_down->SetBinContent(BinIndex, Mass_Stat_down->GetBinContent(13));
 MassCosTheta2D_PromptSubtr_up->SetBinContent(BinIndex, Mass_PromptSubtr_up->GetBinContent(13));
 MassCosTheta2D_PromptSubtr_down->SetBinContent(BinIndex, Mass_PromptSubtr_down->GetBinContent(13));
 MassCosTheta2D_d0sig_up->SetBinContent(BinIndex, Mass_d0sig_up->GetBinContent(13));
 MassCosTheta2D_d0sig_down->SetBinContent(BinIndex, Mass_d0sig_down->GetBinContent(13));
 MassCosTheta2D_RealStat_up->SetBinContent(BinIndex, Mass_RealStat_up->GetBinContent(13));
 MassCosTheta2D_RealStat_down->SetBinContent(BinIndex, Mass_RealStat_down->GetBinContent(13));
 MassCosTheta2D_Function2_up->SetBinContent(BinIndex, Mass_Function2_up->GetBinContent(13));
 MassCosTheta2D_Function2_down->SetBinContent(BinIndex, Mass_Function2_down->GetBinContent(13));
 MassCosTheta2D_StitchingPoint_up->SetBinContent(BinIndex, Mass_StitchingPoint_up->GetBinContent(13));
 MassCosTheta2D_StitchingPoint_down->SetBinContent(BinIndex, Mass_StitchingPoint_down->GetBinContent(13));

 BinIndex = 1;
 for(int ibin = 1; ibin <= MassRapidity1Hists.at(0)->GetNbinsX(); ibin++){
   for(int ihist = 0; ihist < MassRapidity1Hists.size(); ihist++){
     double Central = MassRapidity1Hists.at(ihist)->GetBinContent(ibin);
     double Up = MassRapidity1Up.at(ihist)->GetBinContent(ibin);
     double Down = MassRapidity1Down.at(ihist)->GetBinContent(ibin);
     double Stat_up = MassRapidity1_Stat_up.at(ihist)->GetBinContent(ibin);
     double Stat_down = MassRapidity1_Stat_down.at(ihist)->GetBinContent(ibin);
     double PromptSubtr_up = MassRapidity1_PromptSubtr_up.at(ihist)->GetBinContent(ibin);
     double PromptSubtr_down = MassRapidity1_PromptSubtr_down.at(ihist)->GetBinContent(ibin);
     double d0sig_up = MassRapidity1_d0sig_up.at(ihist)->GetBinContent(ibin);
     double d0sig_down = MassRapidity1_d0sig_down.at(ihist)->GetBinContent(ibin);
     double RealStat_up = MassRapidity1_RealStat_up.at(ihist)->GetBinContent(ibin);
     double RealStat_down = MassRapidity1_RealStat_down.at(ihist)->GetBinContent(ibin);
     double Function2_up = MassRapidity1_Function2_up.at(ihist)->GetBinContent(ibin);
     double Function2_down = MassRapidity1_Function2_down.at(ihist)->GetBinContent(ibin);
     double StitchingPoint_up = MassRapidity1_StitchingPoint_up.at(ihist)->GetBinContent(ibin);
     double StitchingPoint_down = MassRapidity1_StitchingPoint_down.at(ihist)->GetBinContent(ibin);

     MassRapidity2D_nominal->SetBinContent(BinIndex, Central);
     MassRapidity2D_up->SetBinContent(BinIndex, Up);
     MassRapidity2D_down->SetBinContent(BinIndex, Down);
     MassRapidity2D_Stat_up->SetBinContent(BinIndex, Stat_up);
     MassRapidity2D_Stat_down->SetBinContent(BinIndex, Stat_down);
     MassRapidity2D_PromptSubtr_up->SetBinContent(BinIndex, PromptSubtr_up);
     MassRapidity2D_PromptSubtr_down->SetBinContent(BinIndex, PromptSubtr_down);
     MassRapidity2D_d0sig_up->SetBinContent(BinIndex, d0sig_up);
     MassRapidity2D_d0sig_down->SetBinContent(BinIndex, d0sig_down);
     MassRapidity2D_RealStat_up->SetBinContent(BinIndex, RealStat_up);
     MassRapidity2D_RealStat_down->SetBinContent(BinIndex, RealStat_down);
     MassRapidity2D_Function2_up->SetBinContent(BinIndex, Function2_up);
     MassRapidity2D_Function2_down->SetBinContent(BinIndex, Function2_down);
     MassRapidity2D_StitchingPoint_up->SetBinContent(BinIndex, StitchingPoint_up);
     MassRapidity2D_StitchingPoint_down->SetBinContent(BinIndex, StitchingPoint_down);
     BinIndex++;
   }
 }

 for(int ibin = 1; ibin <= MassRapidity2Hists.at(0)->GetNbinsX(); ibin++){
   for(int ihist = 0; ihist < MassRapidity2Hists.size(); ihist++){
     double Central = MassRapidity2Hists.at(ihist)->GetBinContent(ibin);
     double Up = MassRapidity2Up.at(ihist)->GetBinContent(ibin);
     double Down = MassRapidity2Down.at(ihist)->GetBinContent(ibin);
     double Stat_up = MassRapidity2_Stat_up.at(ihist)->GetBinContent(ibin);
     double Stat_down = MassRapidity2_Stat_down.at(ihist)->GetBinContent(ibin);
     double PromptSubtr_up = MassRapidity2_PromptSubtr_up.at(ihist)->GetBinContent(ibin);
     double PromptSubtr_down = MassRapidity2_PromptSubtr_down.at(ihist)->GetBinContent(ibin);
     double d0sig_up = MassRapidity2_d0sig_up.at(ihist)->GetBinContent(ibin);
     double d0sig_down = MassRapidity2_d0sig_down.at(ihist)->GetBinContent(ibin);
     double RealStat_up = MassRapidity2_RealStat_up.at(ihist)->GetBinContent(ibin);
     double RealStat_down = MassRapidity2_RealStat_down.at(ihist)->GetBinContent(ibin);
     double Function2_up = MassRapidity2_Function2_up.at(ihist)->GetBinContent(ibin);
     double Function2_down = MassRapidity2_Function2_down.at(ihist)->GetBinContent(ibin);
     double StitchingPoint_up = MassRapidity2_StitchingPoint_up.at(ihist)->GetBinContent(ibin);
     double StitchingPoint_down = MassRapidity2_StitchingPoint_down.at(ihist)->GetBinContent(ibin);

     MassRapidity2D_nominal->SetBinContent(BinIndex, Central);
     MassRapidity2D_up->SetBinContent(BinIndex, Up);
     MassRapidity2D_down->SetBinContent(BinIndex, Down);
     MassRapidity2D_Stat_up->SetBinContent(BinIndex, Stat_up);
     MassRapidity2D_Stat_down->SetBinContent(BinIndex, Stat_down);
     MassRapidity2D_PromptSubtr_up->SetBinContent(BinIndex, PromptSubtr_up);
     MassRapidity2D_PromptSubtr_down->SetBinContent(BinIndex, PromptSubtr_down);
     MassRapidity2D_d0sig_up->SetBinContent(BinIndex, d0sig_up);
     MassRapidity2D_d0sig_down->SetBinContent(BinIndex, d0sig_down);
     MassRapidity2D_RealStat_up->SetBinContent(BinIndex, RealStat_up);
     MassRapidity2D_RealStat_down->SetBinContent(BinIndex, RealStat_down);
     MassRapidity2D_Function2_up->SetBinContent(BinIndex, Function2_up);
     MassRapidity2D_Function2_down->SetBinContent(BinIndex, Function2_down);
     MassRapidity2D_StitchingPoint_up->SetBinContent(BinIndex, StitchingPoint_up);
     MassRapidity2D_StitchingPoint_down->SetBinContent(BinIndex, StitchingPoint_down);
     BinIndex++;
   }
 }

 MassRapidity2D_nominal->SetBinContent(BinIndex, Mass_nominal->GetBinContent(13));
 MassRapidity2D_up->SetBinContent(BinIndex, Mass_up->GetBinContent(13));
 MassRapidity2D_down->SetBinContent(BinIndex, Mass_down->GetBinContent(13));
 MassRapidity2D_Stat_up->SetBinContent(BinIndex, Mass_Stat_up->GetBinContent(13));
 MassRapidity2D_Stat_down->SetBinContent(BinIndex, Mass_Stat_down->GetBinContent(13));
 MassRapidity2D_PromptSubtr_up->SetBinContent(BinIndex, Mass_PromptSubtr_up->GetBinContent(13));
 MassRapidity2D_PromptSubtr_down->SetBinContent(BinIndex, Mass_PromptSubtr_down->GetBinContent(13));
 MassRapidity2D_d0sig_up->SetBinContent(BinIndex, Mass_d0sig_up->GetBinContent(13));
 MassRapidity2D_d0sig_down->SetBinContent(BinIndex, Mass_d0sig_down->GetBinContent(13));
 MassRapidity2D_RealStat_up->SetBinContent(BinIndex, Mass_RealStat_up->GetBinContent(13));
 MassRapidity2D_RealStat_down->SetBinContent(BinIndex, Mass_RealStat_down->GetBinContent(13));
 MassRapidity2D_Function2_up->SetBinContent(BinIndex, Mass_Function2_up->GetBinContent(13));
 MassRapidity2D_Function2_down->SetBinContent(BinIndex, Mass_Function2_down->GetBinContent(13));
 MassRapidity2D_StitchingPoint_up->SetBinContent(BinIndex, Mass_StitchingPoint_up->GetBinContent(13));
 MassRapidity2D_StitchingPoint_down->SetBinContent(BinIndex, Mass_StitchingPoint_down->GetBinContent(13));

 TFile* writefile = new TFile("FinalMuFake.root", "RECREATE");
 writefile->cd();

 Mass_nominal->Write();
 Mass_up->Write();
 Mass_down->Write();
 Mass_Stat_up->Write();
 Mass_Stat_down->Write();
 Mass_PromptSubtr_up->Write();
 Mass_PromptSubtr_down->Write();
 Mass_d0sig_up->Write();
 Mass_d0sig_down->Write();
 Mass_RealStat_up->Write();
 Mass_RealStat_down->Write();
 Mass_Function2_up->Write();
 Mass_Function2_down->Write();
 Mass_StitchingPoint_up->Write();
 Mass_StitchingPoint_down->Write();

 MassCosTheta2D_nominal->Write();
 MassCosTheta2D_up->Write();
 MassCosTheta2D_down->Write();
 MassCosTheta2D_Stat_up->Write();
 MassCosTheta2D_Stat_down->Write();
 MassCosTheta2D_PromptSubtr_up->Write();
 MassCosTheta2D_PromptSubtr_down->Write();
 MassCosTheta2D_d0sig_up->Write();
 MassCosTheta2D_d0sig_down->Write();
 MassCosTheta2D_RealStat_up->Write();
 MassCosTheta2D_RealStat_down->Write();
 MassCosTheta2D_Function2_up->Write();
 MassCosTheta2D_Function2_down->Write();
 MassCosTheta2D_StitchingPoint_up->Write();
 MassCosTheta2D_StitchingPoint_down->Write();

 MassRapidity2D_nominal->Write();
 MassRapidity2D_up->Write();
 MassRapidity2D_down->Write();
 MassRapidity2D_Stat_up->Write();
 MassRapidity2D_Stat_down->Write();
 MassRapidity2D_PromptSubtr_up->Write();
 MassRapidity2D_PromptSubtr_down->Write();
 MassRapidity2D_d0sig_up->Write();
 MassRapidity2D_d0sig_down->Write();
 MassRapidity2D_RealStat_up->Write();
 MassRapidity2D_RealStat_down->Write();
 MassRapidity2D_Function2_up->Write();
 MassRapidity2D_Function2_down->Write();
 MassRapidity2D_StitchingPoint_up->Write();
 MassRapidity2D_StitchingPoint_down->Write();

 Figure* f;

 f = new Figure(MassHistName + "_final_compare.png", "M [GeV]", "Events");
 f->SetMode("CUSTOM");
 f->Input(1, Mass_nominal, "nominal");
 f->Input(2, Mass_up, "up");
 f->Input(3, Mass_down, "down");
 f->Compare("MultiRatio");
 f->SetCustomPlot(1, 2, "HIST");
 f->SetCustomPlot(1, 3, "HIST");
 f->SetCustomPlot(2, 2, "HIST");
 f->SetCustomPlot(2, 3, "HIST");
 f->SetLegendPosition(0.7, 0.6, 0.9, 0.9);
 f->SetLogX();
 f->SetLogY();
 f->SetCustomYRange(2, 0.0, 2.0);
 f->Draw();

 f = new Figure("MassCosTheta_final_compare.png", "Bin Index", "Events");
 f->SetMode("CUSTOM");
 f->Input(1, MassCosTheta2D_nominal, "nominal");
 f->Input(2, MassCosTheta2D_up, "up");
 f->Input(3, MassCosTheta2D_down, "down");
 f->Compare("MultiRatio");
 f->SetCustomPlot(1, 2, "HIST");
 f->SetCustomPlot(1, 3, "HIST");
 f->SetCustomPlot(2, 2, "HIST");
 f->SetCustomPlot(2, 3, "HIST");
 f->SetLegendPosition(0.7, 0.6, 0.9, 0.9);
 f->SetCustomYRange(2, 0.0, 2.0);
 f->Draw();

 f = new Figure("MassRapidity_final_compare.png", "Bin Index", "Events");
 f->SetMode("CUSTOM");
 f->Input(1, MassRapidity2D_nominal, "nominal");
 f->Input(2, MassRapidity2D_up, "up");
 f->Input(3, MassRapidity2D_down, "down");
 f->Compare("MultiRatio");
 f->SetCustomPlot(1, 2, "HIST");
 f->SetCustomPlot(1, 3, "HIST");
 f->SetCustomPlot(2, 2, "HIST");
 f->SetCustomPlot(2, 3, "HIST");
 f->SetLegendPosition(0.7, 0.6, 0.9, 0.9);
 f->SetCustomYRange(2, 0.0, 2.0);
 f->Draw();

 writefile->Close();
}
