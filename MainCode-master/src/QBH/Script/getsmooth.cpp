#include <iomanip>
#include <set>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TMath.h"
#include "TH1F.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <filesystem>
#include <TH2.h>
#include <TStyle.h>
#include "TColor.h"
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TH3F.h"
#include <TRandom3.h>
#include <TMinuit.h>
#include <TApplication.h>
#include "TEnv.h"
#include <TComplex.h>
#include "TH2D.h"
#include "TH3D.h"
#include "TF1.h"
#include "TF2.h"
#include "TLegend.h"
#include <TProfile.h>
#include "TH1D.h"
#include "TLeaf.h"
#include "TLeafObject.h"
#include "TBranchObject.h"
#include "TBranchElement.h"
#include "TStreamerElement.h"
#include "TLatex.h"
#include "TMathText.h"
#include "TSpectrum.h"

void getsmooth()
{
 function<void(string)> mkdir = [&](string folder){
   try {
       if (std::filesystem::create_directories(folder)) {
           std::cout << "Folder created: " << folder << std::endl;
       } else {
           std::cout << "Folder already exists: " << folder << std::endl;
       }
   } catch (const std::filesystem::filesystem_error& e) {
       std::cerr << "Error creating directory: " << e.what() << std::endl;
   }
 };


 TString InputRootDIR = "/data/projects/exotics/ANA-EXOT-2024-32/Histograms/2025.10.16/";
 TString SaveRootDIR = "Smoothed";
 mkdir(SaveRootDIR.Data());

 vector<TString> Channels = {"Run3_el", "Run3_mu"};
 vector<TString> Regions = {"SR"};

 vector<TString> Samples_el = {"ADDn2_m10.0_combined.histos.root",
                               "ADDn2_m10.5_combined.histos.root",
                               "ADDn2_m8.0_combined.histos.root",
                               "ADDn2_m8.5_combined.histos.root",
                               "ADDn2_m9.0_combined.histos.root",
                               "ADDn2_m9.5_combined.histos.root",
                               "ADDn4_m10.0_combined.histos.root",
                               "ADDn4_m10.5_combined.histos.root",
                               "ADDn4_m8.0_combined.histos.root",
                               "ADDn4_m8.5_combined.histos.root",
                               "ADDn4_m9.0_combined.histos.root",
                               "ADDn4_m9.5_combined.histos.root",
                               "ADDn6_m10.0_combined.histos.root",
                               "ADDn6_m10.5_combined.histos.root",
                               "ADDn6_m8.0_combined.histos.root",
                               "ADDn6_m8.5_combined.histos.root",
                               "ADDn6_m9.0_combined.histos.root",
                               "ADDn6_m9.5_combined.histos.root",
                               "RSn1_m6.0_combined.histos.root",
                               "RSn1_m6.5_combined.histos.root",
                               "RSn1_m7.0_combined.histos.root",
                               "RSn1_m7.5_combined.histos.root",
                               "RSn1_m8.0_combined.histos.root",
                               "RSn1_m8.5_combined.histos.root",
                               "single-t_combined.histos.root",
                               "ttbar_combined.histos.root",
                               "ttV_combined.histos.root",
                               "VV_combined.histos.root",
                               "Wjets_combined.histos.root",
                               "Zjets_combined.histos.root",
                               "fakes_combined.histos.root"};

 vector<TString> Samples_mu = {"ADDn2_m10.0_combined.histos.root",
                               "ADDn2_m10.5_combined.histos.root",
                               "ADDn2_m8.0_combined.histos.root",
                               "ADDn2_m8.5_combined.histos.root",
                               "ADDn2_m9.0_combined.histos.root",
                               "ADDn2_m9.5_combined.histos.root",
                               "ADDn4_m10.0_combined.histos.root",
                               "ADDn4_m10.5_combined.histos.root",
                               "ADDn4_m8.0_combined.histos.root",
                               "ADDn4_m8.5_combined.histos.root",
                               "ADDn4_m9.0_combined.histos.root",
                               "ADDn4_m9.5_combined.histos.root",
                               "ADDn6_m10.0_combined.histos.root",
                               "ADDn6_m10.5_combined.histos.root",
                               "ADDn6_m8.0_combined.histos.root",
                               "ADDn6_m8.5_combined.histos.root",
                               "ADDn6_m9.0_combined.histos.root",
                               "ADDn6_m9.5_combined.histos.root",
                               "RSn1_m6.0_combined.histos.root",
                               "RSn1_m6.5_combined.histos.root",
                               "RSn1_m7.0_combined.histos.root",
                               "RSn1_m7.5_combined.histos.root",
                               "RSn1_m8.0_combined.histos.root",
                               "RSn1_m8.5_combined.histos.root",
                               "single-t_combined.histos.root",
                               "ttbar_combined.histos.root",
                               "ttV_combined.histos.root",
                               "VV_combined.histos.root",
                               "Wjets_combined.histos.root",
                               "Zjets_combined.histos.root",
                               "jj_combined.histos.root"};


 TString skip;
 vector<TString> ElSysList;
 vector<TString> MuSysList;

 ifstream infile_el("el.log");
 while(infile_el >> skip){
   ElSysList.push_back(skip);
 }

 ifstream infile_mu("mu.log");
 while(infile_mu >> skip){
   MuSysList.push_back(skip);
 }

 function<map<TString, tuple<TString, TString, TString>>(vector<TString>)> GetSysList = [&](vector<TString> list){
   map<TString, tuple<TString, TString, TString>> FinalList;
   vector<TString> TwoSideList;
   map<TString, TString> TwoSideSysNames;

   for(int i = 0; i < list.size(); i++){
     if(list.at(i) == "MUR1_MUF1_PDF265000" || list.at(i) == "MUR1_MUF1_PDF266000" || list.at(i) == "MUR1_MUF1_PDF269000" || list.at(i) == "MUR1_MUF1_PDF270000"
     || list.at(i) == "JET_NNJvtEfficiency__1down_JVTEff_SF_FixedEffPt" || list.at(i) == "JET_NNJvtEfficiency__1up_JVTEff_SF_FixedEffPt"){
       if(list.at(i) == "MUR1_MUF1_PDF265000" || list.at(i) == "MUR1_MUF1_PDF266000"){
         FinalList["AlphaS_top"] = make_tuple("MUR1_MUF1_PDF265000", "MUR1_MUF1_PDF266000", "TwoSide");
       }

       if(list.at(i) == "MUR1_MUF1_PDF269000" || list.at(i) == "MUR1_MUF1_PDF270000"){
         FinalList["AlphaS_Sherpa"] = make_tuple("MUR1_MUF1_PDF269000", "MUR1_MUF1_PDF270000", "TwoSide");
       }

       if(list.at(i) == "JET_NNJvtEfficiency__1down_JVTEff_SF_FixedEffPt" || list.at(i) == "JET_NNJvtEfficiency__1up_JVTEff_SF_FixedEffPt"){
         FinalList["JET_NNJvtEfficiency__"] = make_tuple("JET_NNJvtEfficiency__1up_JVTEff_SF_FixedEffPt", "JET_NNJvtEfficiency__1down_JVTEff_SF_FixedEffPt", "TwoSide");
       }

       continue;
     }

     if(!(list.at(i).Contains("up")) && !(list.at(i).Contains("down")) && !(list.at(i).Contains("Up")) && !(list.at(i).Contains("Down"))){
       FinalList[list.at(i)] = make_tuple(list.at(i), list.at(i), "OneSide");
       continue;
     }

     TwoSideList.push_back(list.at(i));
   }

   if(TwoSideList.size() % 2 != 0) cout<<"There is still one side systematic in the list."<<endl;

   for(int i = 0; i < TwoSideList.size(); i++){
     TString RawSysName = TwoSideList.at(i);
     RawSysName.ReplaceAll("1up", "");
     RawSysName.ReplaceAll("1down", "");
     RawSysName.ReplaceAll("Up", "");
     RawSysName.ReplaceAll("Down", "");
     RawSysName.ReplaceAll("_up", "");
     RawSysName.ReplaceAll("_down", "");

     TwoSideSysNames[RawSysName] = "TwoSide";
   }

   if(TwoSideSysNames.size() != TwoSideList.size() / 2) cout<<"Check two side systematic names."<<endl;

   for(auto iter = TwoSideSysNames.begin(); iter != TwoSideSysNames.end(); iter++){
     TString UpName, DownName;

     UpName = "";
     DownName = "";

     for(int i = 0; i < TwoSideList.size(); i++){

       if(TwoSideList.at(i).Contains(iter->first)){
         if(TwoSideList.at(i).Contains("1up") || TwoSideList.at(i).Contains("Up") || TwoSideList.at(i).Contains("_up")) UpName = TwoSideList.at(i);
         if(TwoSideList.at(i).Contains("1down") || TwoSideList.at(i).Contains("Down") || TwoSideList.at(i).Contains("_down")) DownName = TwoSideList.at(i);
       }

       if(UpName != "" && DownName != "") break;
     }

     FinalList[iter->first] = make_tuple(UpName, DownName, "TwoSide");
   }

   for(auto iter = FinalList.begin(); iter != FinalList.end(); iter++){
     cout<<iter->first<<":    "<<get<0>(iter->second)<<"  "<<get<1>(iter->second)<<"  "<<get<2>(iter->second)<<endl;
   }

   return FinalList;
 };

 cout<<endl;
 cout<<"Prepare El Systematic list:"<<endl;
 cout<<endl;
 map<TString, tuple<TString, TString, TString>> ElFinalSysList = GetSysList(ElSysList);

 cout<<endl;
 cout<<"Prepare Mu Systematic list:"<<endl;
 cout<<endl;
 map<TString, tuple<TString, TString, TString>> MuFinalSysList = GetSysList(MuSysList);

 function<void(TH1D*, TH1D*, TH1D* &, TH1D* &)> GetSmoothedHist_OneSide = [&](TH1D* OriginNominalHist, TH1D* OriginUpHist, TH1D* &NominalHist, TH1D* &UpHist){
   NominalHist = (TH1D *)OriginNominalHist->Clone((TString)OriginNominalHist->GetName() + "_Smoothed");
   UpHist = (TH1D *)OriginUpHist->Clone((TString)OriginUpHist->GetName() + "_Smoothed");

   for(int ibin = 1; ibin <= NominalHist->GetNbinsX(); ibin++){
     double OriginNominalValue = OriginNominalHist->GetBinContent(ibin);
     double OriginUpValue = OriginUpHist->GetBinContent(ibin);

     double NominalValue = OriginNominalValue;
     double UpValue = OriginUpValue;

     if(OriginNominalValue <= 0.0){
       NominalValue = OriginNominalHist->GetBinError(ibin);
     }

     if(OriginUpValue <= 0.0){
       double Delta = fabs(OriginNominalValue - OriginUpValue);
       if(OriginUpValue >= OriginNominalValue) UpValue = NominalValue + Delta;
       else if(OriginUpValue < OriginNominalValue) UpValue = NominalValue - Delta;

       if(UpValue <= 0.0) UpValue = 1e-10;
     }

     NominalHist->SetBinContent(ibin, NominalValue);
     UpHist->SetBinContent(ibin, UpValue);
   }
 };

 function<void(TH1D*, TH1D*, TH1D*, TH1D* &, TH1D* &, TH1D* &)> GetSmoothedHist_TwoSide = [&](TH1D* OriginNominalHist, TH1D* OriginUpHist, TH1D* OriginDownHist,
                                                                                              TH1D* &NominalHist, TH1D* &UpHist, TH1D* &DownHist){
   NominalHist = (TH1D *)OriginNominalHist->Clone((TString)OriginNominalHist->GetName() + "_Smoothed");
   UpHist = (TH1D *)OriginUpHist->Clone((TString)OriginUpHist->GetName() + "_Smoothed");
   DownHist = (TH1D *)OriginDownHist->Clone((TString)OriginDownHist->GetName() + "_Smoothed");

   for(int ibin = 1; ibin <= NominalHist->GetNbinsX(); ibin++){
     double OriginNominalValue = OriginNominalHist->GetBinContent(ibin);
     double OriginUpValue = OriginUpHist->GetBinContent(ibin);
     double OriginDownValue = OriginDownHist->GetBinContent(ibin);
     
     double NominalValue = OriginNominalValue;
     double UpValue = OriginUpValue;
     double DownValue = OriginDownValue;

     if(OriginNominalValue <= 0.0){
       NominalValue = OriginNominalHist->GetBinError(ibin);
     }

     if(OriginUpValue <= 0.0){
       double Delta = fabs(OriginNominalValue - OriginUpValue);
       if(OriginUpValue >= OriginNominalValue) UpValue = NominalValue + Delta;
       else if(OriginUpValue < OriginNominalValue) UpValue = NominalValue - Delta;

       if(UpValue <= 0.0) UpValue = 1e-10;
     }

     if(OriginDownValue <= 0.0){
       double Delta = fabs(OriginNominalValue - OriginDownValue);
       if(OriginDownValue >= OriginNominalValue) DownValue = NominalValue + Delta;
       else if(OriginDownValue < OriginNominalValue) DownValue = NominalValue - Delta;

       if(DownValue <= 0.0) DownValue = 1e-10;
     }

     NominalHist->SetBinContent(ibin, NominalValue);
     UpHist->SetBinContent(ibin, UpValue);
     DownHist->SetBinContent(ibin, DownValue);
   }

 };

 vector<TString> Histograms = {"mLepJet",
                               "mLepJet20",
                               "mLepJet40",
                               "mLepJetSR",
                               "mLepJetSR1bin",
                               "mLepJetSR_logX",
                               "mLepJetSR_logX_2"};

 for(int ichannel = 0; ichannel < Channels.size(); ichannel++){
   mkdir((SaveRootDIR + "/" + Channels.at(ichannel)).Data());

   vector<TString> Samples;
   if(Channels.at(ichannel) == "Run3_el") Samples = Samples_el;
   if(Channels.at(ichannel) == "Run3_mu") Samples = Samples_mu;

   for(int iregion = 0; iregion < Regions.size(); iregion++){
     mkdir((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "_NoNegative").Data());

     map<TString, tuple<TString, TString, TString>> FinalList;
     if(Channels.at(ichannel) == "Run3_el") FinalList = ElFinalSysList;
     if(Channels.at(ichannel) == "Run3_mu") FinalList = MuFinalSysList;

     mkdir((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "_NoNegative/nominal").Data());

     for(auto iter = FinalList.begin(); iter != FinalList.end(); iter++){
       mkdir((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "_NoNegative/" + get<0>(iter->second)).Data());
       mkdir((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "_NoNegative/" + get<1>(iter->second)).Data());

       TFile* TotalBackground_nominal;
       TFile* TotalBackground_up;
       TFile* TotalBackground_down;

       TotalBackground_nominal = new TFile((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "_NoNegative/nominal/Total_Background.histos.root").Data(), "RECREATE");

       if(get<2>(iter->second) == "OneSide"){
         TotalBackground_up = new TFile((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "_NoNegative/" + get<0>(iter->second) + "/Total_Background.histos.root").Data(), "RECREATE");
       }

       if(get<2>(iter->second) == "TwoSide"){
         TotalBackground_up = new TFile((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "_NoNegative/" + get<0>(iter->second) + "/Total_Background.histos.root").Data(), "RECREATE");
         TotalBackground_down = new TFile((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "_NoNegative/" + get<1>(iter->second) + "/Total_Background.histos.root").Data(), "RECREATE");
       }

       vector<TH1D *> TotalBackground_Hist_nominal(Histograms.size());
       vector<TH1D *> TotalBackground_Hist_up(Histograms.size());
       vector<TH1D *> TotalBackground_Hist_down(Histograms.size());

       TFile* tmp_nominal = new TFile((InputRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "/nominal/Wjets_combined.histos.root").Data());

       for(int ihist = 0; ihist < Histograms.size(); ihist++){
         TH1D* Hist = (TH1D *)tmp_nominal->Get(Histograms.at(ihist));
         TotalBackground_Hist_nominal.at(ihist) = (TH1D *)Hist->Clone(Histograms.at(ihist) + "_Combined_nominal");
         TotalBackground_Hist_up.at(ihist) = (TH1D *)Hist->Clone(Histograms.at(ihist) + "_Combined_up");
         TotalBackground_Hist_down.at(ihist) = (TH1D *)Hist->Clone(Histograms.at(ihist) + "_Combined_down");

         TotalBackground_Hist_nominal.at(ihist)->Reset();
         TotalBackground_Hist_up.at(ihist)->Reset();
         TotalBackground_Hist_down.at(ihist)->Reset();
       } // end loop histogram

       for(int isample = 0; isample < Samples.size(); isample++){

         cout<<Samples.at(isample)<<endl;

         TFile* OriginNominalFile;
         TFile* OriginUpFile;
         TFile* OriginDownFile;

         TFile* NominalFile;
         TFile* UpFile;
         TFile* DownFile;

         OriginNominalFile = new TFile((InputRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "/nominal/" + Samples.at(isample)).Data());
         NominalFile = new TFile((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "_NoNegative/nominal/" + Samples.at(isample)).Data(), "RECREATE");

         if(get<2>(iter->second) == "OneSide"){
           OriginUpFile = new TFile((InputRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "/" + get<0>(iter->second) + "/" + Samples.at(isample)).Data());
           UpFile = new TFile((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "_NoNegative/" + get<0>(iter->second) + "/" + Samples.at(isample)).Data(), "RECREATE");
         }

         if(get<2>(iter->second) == "TwoSide"){
           OriginUpFile = new TFile((InputRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "/" + get<0>(iter->second) + "/" + Samples.at(isample)).Data());
           OriginDownFile = new TFile((InputRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "/" + get<1>(iter->second) + "/" + Samples.at(isample)).Data());
           UpFile = new TFile((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "_NoNegative/" + get<0>(iter->second) + "/" + Samples.at(isample)).Data(), "RECREATE");
           DownFile = new TFile((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "_NoNegative/" + get<1>(iter->second) + "/" + Samples.at(isample)).Data(), "RECREATE");
         }

         for(int ihist = 0; ihist < Histograms.size(); ihist++){
           TH1D* OriginNominalHist = (TH1D *)OriginNominalFile->Get(Histograms.at(ihist));
           TH1D* OriginUpHist = (TH1D *)OriginUpFile->Get(Histograms.at(ihist));
           TH1D* OriginDownHist;
	   if(get<2>(iter->second) == "TwoSide") OriginDownHist = (TH1D *)OriginDownFile->Get(Histograms.at(ihist));

	   TH1D* NominalHist;
           TH1D* UpHist;
	   TH1D* DownHist;

           if(get<2>(iter->second) == "OneSide") GetSmoothedHist_OneSide(OriginNominalHist, OriginUpHist, NominalHist, UpHist);
           if(get<2>(iter->second) == "TwoSide") GetSmoothedHist_TwoSide(OriginNominalHist, OriginUpHist, OriginDownHist, NominalHist, UpHist, DownHist);

           NominalFile->cd();
           NominalHist->Write(Histograms.at(ihist));
           UpFile->cd();
           UpHist->Write(Histograms.at(ihist));
           if(get<2>(iter->second) == "TwoSide"){
             DownFile->cd();
             DownHist->Write(Histograms.at(ihist));
           }

           if(!(Samples.at(isample).Contains("ADD")) && !(Samples.at(isample).Contains("RS"))){
             TotalBackground_Hist_nominal.at(ihist)->Add(NominalHist);
             TotalBackground_Hist_up.at(ihist)->Add(UpHist);
             if(get<2>(iter->second) == "TwoSide") TotalBackground_Hist_down.at(ihist)->Add(DownHist);
           }
         } // end loop histogram

         OriginNominalFile->Close();
         OriginUpFile->Close();
         if(get<2>(iter->second) == "TwoSide") OriginDownFile->Close();

         NominalFile->Close();
         UpFile->Close();
         if(get<2>(iter->second) == "TwoSide") DownFile->Close();

       } // end loop sample

       TotalBackground_nominal->cd();
       for(int ihist = 0; ihist < Histograms.size(); ihist++){
         TotalBackground_Hist_nominal.at(ihist)->Write(Histograms.at(ihist));
       } // end loop histogram
       TotalBackground_nominal->Close();

       TotalBackground_up->cd();
       for(int ihist = 0; ihist < Histograms.size(); ihist++){
         TotalBackground_Hist_up.at(ihist)->Write(Histograms.at(ihist));
       } // end loop histogram
       TotalBackground_up->Close();

       if(get<2>(iter->second) == "TwoSide"){
         TotalBackground_down->cd();
         for(int ihist = 0; ihist < Histograms.size(); ihist++){
           TotalBackground_Hist_down.at(ihist)->Write(Histograms.at(ihist));
         } // end loop histogram
         TotalBackground_down->Close();
       }

       tmp_nominal->Close();

     } // end loop systematic
   } // end loop region
 } // end loop channel

}


