#include "ZPrime/SysZPrime.h"

void SysZPrime::ReadList(TString ElFileName, TString MuFileName)
{
 TString name;
 vector<TString> ElRootNames;
 vector<TString> MuRootNames;

 ifstream ElList(ElFileName);
 while(ElList>>name){
   ElRootNames.push_back(name);
 }

 ifstream MuList(MuFileName);
 while(MuList>>name){
   MuRootNames.push_back(name);
 }

 Initialize(ElRootNames, MuRootNames);
}

void SysZPrime::Initialize(vector<TString> ElRootNames, vector<TString> MuRootNames)
{
 if(ElRootNames.size() != ElSystematics.size() * 2 + 1){
   cout<<"Input list doesn't match with systematic list for electron."<<endl;
   return;
 }

 if(MuRootNames.size() != MuSystematics.size() * 2 + 1){
   cout<<"Input list doesn't match with systematic list for muon."<<endl;
   return;
 }


 ElRootFiles.resize(ElRootNames.size());
 MuRootFiles.resize(MuRootNames.size());

 for(int i = 0; i < ElRootFiles.size(); i++){
   ElRootFiles.at(i) = new TFile(ElRootNames.at(i));
 }

 for(int i = 0; i < MuRootFiles.size(); i++){
   MuRootFiles.at(i) = new TFile(MuRootNames.at(i));
 }

 for(int ihist = 0; ihist < HistNames.size(); ihist++){

   // Retrieve all systematic plots from root file
   for(int ibkg = 0; ibkg < BkgNames_ee.size(); ibkg++){
     TString HistName = HistNames.at(ihist) + BkgNames_ee.at(ibkg);
     ElSysHist_1d[HistName].resize(ElRootNames.size());

     for(int i = 0; i < ElRootFiles.size(); i++){
       ElSysHist_1d.at(HistName).at(i) = (TH1D *)ElRootFiles.at(i)->Get(HistName);
     }

     // Initialize systematic variation plot
     ElSysVariation[HistName].resize(ElSysHist_1d.at(HistName).at(0)->GetNbinsX());
     for(int ibin = 1; ibin <= ElSysHist_1d.at(HistName).at(0)->GetNbinsX(); ibin++){
       TString SysVarHist = HistName + "_SysVariation_bin" + ibin;
       ElSysVariation.at(HistName).at(ibin - 1) = new TH1D(SysVarHist, SysVarHist, ElSystematics.size(), 1, ElSystematics.size());
     }
   }

   for(int ibkg = 0; ibkg < BkgNames_mm.size(); ibkg++){
     TString HistName = HistNames.at(ihist) + BkgNames_mm.at(ibkg);
     MuSysHist_1d[HistName].resize(MuRootNames.size());

     for(int i = 0; i < MuRootFiles.size(); i++){
       MuSysHist_1d.at(HistName).at(i) = (TH1D *)MuRootFiles.at(i)->Get(HistName);
     }

     // Initialize systematic variation plot
     MuSysVariation[HistName].resize(MuSysHist_1d.at(HistName).at(0)->GetNbinsX());
     for(int ibin = 1; ibin <= MuSysHist_1d.at(HistName).at(0)->GetNbinsX(); ibin++){
       TString SysVarHist = HistName + "_SysVariation_bin" + ibin;
       MuSysVariation.at(HistName).at(ibin - 1) = new TH1D(SysVarHist, SysVarHist, MuSystematics.size(), 1, MuSystematics.size());
     }
   }

 }

 CalculateSysUnc();
}

void SysZPrime::CalculateSysUnc()
{
 for(auto iter = ElSysHist_1d.begin(); iter != ElSysHist_1d.end(); iter++){
   cout<<"Calculate Systematic Uncertainty for "<<iter->first<<endl;

   if(iter->first.Contains("_Data") || iter->first.Contains("_SumMC")) continue;

   TH1D* nominal = iter->second.at(0);
   ElFinalHist[iter->first] = (TH1D *)nominal->Clone(iter->first + "_Final");
   ElUncHist[iter->first] = (TH1D *)nominal->Clone(iter->first + "_SysUnc");

   // first make one side systematics to be two sides
   for(int i = 0; i < ElSystematics.size(); i++){
     TH1D* hist_up = iter->second.at(2 * i + 1);
     TH1D* hist_down = iter->second.at(2 * i + 2);
     if(fabs(hist_up->Integral() - hist_down->Integral()) < 1e-10){
       for(int ibin = 1; ibin <= nominal->GetNbinsX(); ibin++){
         double Delta = hist_up->GetBinContent(ibin) - nominal->GetBinContent(ibin);
         double Down = nominal->GetBinContent(ibin) - Delta;
         iter->second.at(2 * i + 2)->SetBinContent(ibin, Down);
       }
     }
   }

   for(int ibin = 1; ibin <= nominal->GetNbinsX(); ibin++){
     double SysUnc2 = 0.0;
     for(int i = 0; i < ElSystematics.size(); i++){
       double Up = fabs(iter->second.at(2 * i + 1)->GetBinContent(ibin) - nominal->GetBinContent(ibin));
       double Down = fabs(iter->second.at(2 * i + 2)->GetBinContent(ibin) - nominal->GetBinContent(ibin));
       double Delta = Up > Down ? Up : Down;
       SysUnc2 += Delta * Delta;

       ElSysVariation.at(iter->first).at(ibin - 1)->SetBinContent(i + 1, fabs(Delta));
       ElSysVariation.at(iter->first).at(ibin - 1)->SetBinError(i + 1, 0.0);
       ElSysVariation.at(iter->first).at(ibin - 1)->GetXaxis()->SetBinLabel(i + 1, ElSystematics.at(i));
     }
     double StatUnc2 = nominal->GetBinError(ibin) * nominal->GetBinError(ibin);
     ElFinalHist.at(iter->first)->SetBinError(ibin, sqrt(SysUnc2 + StatUnc2));
     ElUncHist.at(iter->first)->SetBinContent(ibin, sqrt(SysUnc2));
     ElUncHist.at(iter->first)->SetBinError(ibin, 0.0);
   }
 }

 for(auto iter = MuSysHist_1d.begin(); iter != MuSysHist_1d.end(); iter++){
   cout<<"Calculate Systematic Uncertainty for "<<iter->first<<endl;
  
   if(iter->first.Contains("_Data") || iter->first.Contains("_SumMC")) continue;
 
   TH1D* nominal = iter->second.at(0);
   MuFinalHist[iter->first] = (TH1D *)nominal->Clone(iter->first + "_Final");
   MuUncHist[iter->first] = (TH1D *)nominal->Clone(iter->first + "_SysUnc");

   // first make one side systematics to be two sides
   for(int i = 0; i < MuSystematics.size(); i++){
     TH1D* hist_up = iter->second.at(2 * i + 1);
     TH1D* hist_down = iter->second.at(2 * i + 2);
     if(fabs(hist_up->Integral() - hist_down->Integral()) < 1e-10){
       for(int ibin = 1; ibin <= nominal->GetNbinsX(); ibin++){
         double Delta = hist_up->GetBinContent(ibin) - nominal->GetBinContent(ibin);
         double Down = nominal->GetBinContent(ibin) - Delta;
         iter->second.at(2 * i + 2)->SetBinContent(ibin, Down);
       }
     }
   }
   
   for(int ibin = 1; ibin <= nominal->GetNbinsX(); ibin++){
     double SysUnc2 = 0.0;
     for(int i = 0; i < MuSystematics.size(); i++){
       double Up = fabs(iter->second.at(2 * i + 1)->GetBinContent(ibin) - nominal->GetBinContent(ibin));
       double Down = fabs(iter->second.at(2 * i + 2)->GetBinContent(ibin) - nominal->GetBinContent(ibin));
       double Delta = Up > Down ? Up : Down;
       SysUnc2 += Delta * Delta;

       MuSysVariation.at(iter->first).at(ibin - 1)->SetBinContent(i + 1, fabs(Delta));
       MuSysVariation.at(iter->first).at(ibin - 1)->SetBinError(i + 1, 0.0);
       MuSysVariation.at(iter->first).at(ibin - 1)->GetXaxis()->SetBinLabel(i + 1, MuSystematics.at(i));
     }
     double StatUnc2 = nominal->GetBinError(ibin) * nominal->GetBinError(ibin);
     MuFinalHist.at(iter->first)->SetBinError(ibin, sqrt(SysUnc2 + StatUnc2));
     MuUncHist.at(iter->first)->SetBinContent(ibin, sqrt(SysUnc2));
     MuUncHist.at(iter->first)->SetBinError(ibin, 0.0);
   }
 }

 SaveFile("MC_results_AllSys.root");
}

void SysZPrime::SaveFile(TString FileName)
{
 writefile = new TFile(FileName, "RECREATE");
 writefile->cd();

 // Save the Systematic Variation first
 for(auto iter = ElSysHist_1d.begin(); iter != ElSysHist_1d.end(); iter++){
   TH1D* nominal = iter->second.at(0);
   for(int ibin = 1; ibin <= nominal->GetNbinsX(); ibin++){
     ElSysVariation.at(iter->first).at(ibin - 1)->Write();
   }
 }

 for(auto iter = MuSysHist_1d.begin(); iter != MuSysHist_1d.end(); iter++){
   TH1D* nominal = iter->second.at(0);
   for(int ibin = 1; ibin <= nominal->GetNbinsX(); ibin++){
     MuSysVariation.at(iter->first).at(ibin - 1)->Write();
   }
 }

 for(auto iter = ElSysHist_1d.begin(); iter != ElSysHist_1d.end(); iter++){
   if(iter->first.Contains("_Data") || iter->first.Contains("_SumMC")){
     iter->second.at(0)->Write();
     continue;
   }

   TH1D* nominal = iter->second.at(0);
   nominal->Write(iter->first + "_nominal");
   for(int i = 0; i < ElSystematics.size(); i++){
     TH1D* hist_up = iter->second.at(2 * i + 1);
     TH1D* hist_down = iter->second.at(2 * i + 2);
     hist_up->Write(iter->first + "_" + ElSystematics.at(i) + "__1up");
     hist_down->Write(iter->first + "_" + ElSystematics.at(i) + "__1down");
   }
   ElFinalHist.at(iter->first)->Write();
   ElUncHist.at(iter->first)->Write();
 }

 for(auto iter = MuSysHist_1d.begin(); iter != MuSysHist_1d.end(); iter++){
   if(iter->first.Contains("_Data") || iter->first.Contains("_SumMC")){ 
     iter->second.at(0)->Write();
     continue;
   }

   TH1D* nominal = iter->second.at(0);
   nominal->Write(iter->first + "_nominal");
   for(int i = 0; i < MuSystematics.size(); i++){
     TH1D* hist_up = iter->second.at(2 * i + 1);
     TH1D* hist_down = iter->second.at(2 * i + 2);
     hist_up->Write(iter->first + "_" + MuSystematics.at(i) + "__1up");
     hist_down->Write(iter->first + "_" + MuSystematics.at(i) + "__1down");
   }
   MuFinalHist.at(iter->first)->Write();
   MuUncHist.at(iter->first)->Write();
 }

 writefile->Close();
}

void SysZPrime::InitSysName()
{
 ElSystematics.push_back("LepSF_EL_ChargeMisID_SYST");
 ElSystematics.push_back("LepSF_EL_ChargeMisID_STAT");

/* ElSystematics.push_back("Luminosity");
 ElSystematics.push_back("PIVariation");
 ElSystematics.push_back("Di-boson");
 ElSystematics.push_back("LepSF_EL_Reco");
 ElSystematics.push_back("LepSF_EL_Isol");
 ElSystematics.push_back("LepSF_EL_Trigger");
 ElSystematics.push_back("LepSF_EL_ID_1");
 ElSystematics.push_back("LepSF_EL_ID_2");
 ElSystematics.push_back("LepSF_EL_ID_3");
 ElSystematics.push_back("LepSF_EL_ID_4");
 ElSystematics.push_back("LepSF_EL_ID_5");
 ElSystematics.push_back("LepSF_EL_ID_6");
 ElSystematics.push_back("LepSF_EL_ID_7");
 ElSystematics.push_back("LepSF_EL_ID_8");
 ElSystematics.push_back("LepSF_EL_ID_9");
 ElSystematics.push_back("LepSF_EL_ID_10");
 ElSystematics.push_back("LepSF_EL_ID_11");
 ElSystematics.push_back("LepSF_EL_ID_12");
 ElSystematics.push_back("LepSF_EL_ID_13");
 ElSystematics.push_back("LepSF_EL_ID_14");
 ElSystematics.push_back("LepSF_EL_ID_15");
 ElSystematics.push_back("LepSF_EL_ID_16");
 ElSystematics.push_back("LepSF_EL_ID_17");
 ElSystematics.push_back("LepSF_EL_ID_18");
 ElSystematics.push_back("LepSF_EL_ID_19");
 ElSystematics.push_back("LepSF_EL_ID_20");
 ElSystematics.push_back("LepSF_EL_ID_21");
 ElSystematics.push_back("LepSF_EL_ID_22");
 ElSystematics.push_back("LepSF_EL_ID_23");
 ElSystematics.push_back("LepSF_EL_ID_24");
 ElSystematics.push_back("LepSF_EL_ID_25");
 ElSystematics.push_back("LepSF_EL_ID_26");
 ElSystematics.push_back("LepSF_EL_ID_27");
 ElSystematics.push_back("LepSF_EL_ID_28");
 ElSystematics.push_back("LepSF_EL_ID_29");
 ElSystematics.push_back("LepSF_EL_ID_30");
 ElSystematics.push_back("LepSF_EL_ID_31");
 ElSystematics.push_back("LepSF_EL_ID_32");
 ElSystematics.push_back("LepSF_EL_ID_33");
 ElSystematics.push_back("LepSF_EL_ID_34");
 ElSystematics.push_back("LepSF_EL_ChargeMisID_SYST");
 ElSystematics.push_back("LepSF_EL_ChargeMisID_STAT");
 ElSystematics.push_back("HardScatterMCAdNlo");
 ElSystematics.push_back("FragHadModelHerwig7");
 ElSystematics.push_back("ISRVariationNtuple");
 ElSystematics.push_back("TopMassVariation");
 ElSystematics.push_back("EG_RESOLUTION_AF2");
 ElSystematics.push_back("EG_RESOLUTION_MATERIALCALO");
 ElSystematics.push_back("EG_RESOLUTION_MATERIALCRYO");
 ElSystematics.push_back("EG_RESOLUTION_MATERIALGAP");
 ElSystematics.push_back("EG_RESOLUTION_MATERIALIBL");
 ElSystematics.push_back("EG_RESOLUTION_MATERIALPP0");
 ElSystematics.push_back("EG_RESOLUTION_PILEUP");
 ElSystematics.push_back("EG_RESOLUTION_SAMPLINGTERM");
 ElSystematics.push_back("EG_RESOLUTION_ZSMEARING");
 ElSystematics.push_back("EG_SCALE_E4SCINTILLATOR");
 ElSystematics.push_back("EG_SCALE_G4");
 ElSystematics.push_back("EG_SCALE_L1GAIN");
 ElSystematics.push_back("EG_SCALE_L2GAIN");
 ElSystematics.push_back("EG_SCALE_LARCALIB");
 ElSystematics.push_back("EG_SCALE_LARELECCALIB");
 ElSystematics.push_back("EG_SCALE_LARELECUNCONV");
 ElSystematics.push_back("EG_SCALE_LARUNCONVCALIB");
 ElSystematics.push_back("EG_SCALE_MATCALO");
 ElSystematics.push_back("EG_SCALE_MATCRYO");
 ElSystematics.push_back("EG_SCALE_MATID");
 ElSystematics.push_back("EG_SCALE_MATPP0");
 ElSystematics.push_back("EG_SCALE_PEDESTAL");
 ElSystematics.push_back("EG_SCALE_PS_BARREL_B12");
 ElSystematics.push_back("EG_SCALE_TOPOCLUSTER_THRES");
 ElSystematics.push_back("EG_SCALE_WTOTS1");
 ElSystematics.push_back("EG_SCALE_ZEESYST");
 ElSystematics.push_back("EG_SCALE_PS");
 ElSystematics.push_back("EG_SCALE_S12");
 ElSystematics.push_back("TopDD_Mass_Stat");
 ElSystematics.push_back("TopDD_Mass_CosTheta_Stat");
 ElSystematics.push_back("TopDD_Mass_Rapidity_Stat");
 ElSystematics.push_back("Fake_Matrix_Electron");

 MuSystematics.push_back("Luminosity");
 MuSystematics.push_back("PIVariation");
 MuSystematics.push_back("Di-boson");
 MuSystematics.push_back("HardScatterMCAdNlo");
 MuSystematics.push_back("FragHadModelHerwig7");
 MuSystematics.push_back("ISRVariationNtuple");
 MuSystematics.push_back("TopMassVariation");
 MuSystematics.push_back("LepSF_MU_TTVA");
 MuSystematics.push_back("LepSF_MU_TTVA_STAT");
 MuSystematics.push_back("LepSF_MU_ID_STAT");
 MuSystematics.push_back("LepSF_MU_ID_STAT_LOWPT");
 MuSystematics.push_back("LepSF_MU_ID_SYST");
 MuSystematics.push_back("LepSF_MU_ID_SYST_LOWPT");
 MuSystematics.push_back("LepSF_MU_Trigger");
 MuSystematics.push_back("LepSF_MU_Isol");
 MuSystematics.push_back("LepSF_MU_ID_BAD_MUON_VETO");
 MuSystematics.push_back("MUON_SAGITTA_RESBIAS");
 MuSystematics.push_back("MUON_ID");
 MuSystematics.push_back("MUON_MS");
 MuSystematics.push_back("MUON_SCALE");
 MuSystematics.push_back("MUON_CB");
 MuSystematics.push_back("TopDD_Mass_Stat");
 MuSystematics.push_back("TopDD_Mass_CosTheta_Stat");
 MuSystematics.push_back("TopDD_Mass_Rapidity_Stat");
 MuSystematics.push_back("Fake_Matrix_Muon");
*/
}

