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

void combinepdf()
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

 function<void(vector<TH1D *>, TH1D* &, TH1D* &)> GetPDFUnc_Hessian = [&](vector<TH1D *> Hists, TH1D* &PDF_up, TH1D* &PDF_down){
   // Input is from 0 to nEV set
   TString name = Hists.at(0)->GetName();

   PDF_up = (TH1D *)Hists.at(0)->Clone(name + "_PDF_up");
   PDF_up->Reset();

   PDF_down = (TH1D *)Hists.at(0)->Clone(name + "_PDF_down");
   PDF_down->Reset();

   int nErrorSet = Hists.size() - 1;

   for(int ibin = 1; ibin <= Hists.at(0)->GetNbinsX(); ibin++){
     double Unc2 = 0.0;
     double Central = Hists.at(0)->GetBinContent(ibin);
     double Error = Hists.at(0)->GetBinError(ibin);
     for(int i = 1; i < nErrorSet / 2 + 1; i++){
       double up = Hists.at(2 * i - 1)->GetBinContent(ibin);
       double down = Hists.at(2 * i)->GetBinContent(ibin);
       Unc2 += (up - down) * (up - down) / 4.0;
     }
     PDF_up->SetBinContent(ibin, Central + sqrt(Unc2));
     PDF_up->SetBinError(ibin, Error);
     PDF_down->SetBinContent(ibin, Central - sqrt(Unc2));
     PDF_down->SetBinError(ibin, Error);
   }
 };

 function<double(vector<double>)> CalculateStdDev = [&](vector<double> num){
   double Mean = 0.0;

   for(int i = 0; i < num.size(); i++){
     Mean += num.at(i);
   }

   Mean = Mean / (double)num.size();

   double StdDev = 0.0;
   double StdDev2 = 0.0;

   for(int i = 0; i < num.size(); i++){
     StdDev2 += (num.at(i) - Mean) * (num.at(i) - Mean);
   }

   StdDev = sqrt(StdDev2 / (double)num.size());
 
   return StdDev;
 };

 function<void(vector<TH1D *>, TH1D* &, TH1D* &)> GetPDFUnc_MonteCarlo = [&](vector<TH1D *> Hists, TH1D* &PDF_up, TH1D* &PDF_down){
   // Input is from 0 to nMC set
   TString name = Hists.at(0)->GetName();

   PDF_up = (TH1D *)Hists.at(0)->Clone(name + "_PDF_up");
   PDF_up->Reset();

   PDF_down = (TH1D *)Hists.at(0)->Clone(name + "_PDF_down");
   PDF_down->Reset();

   for(int ibin = 1; ibin <= Hists.at(0)->GetNbinsX(); ibin++){
     double Unc = 0.0;
     double Central = Hists.at(0)->GetBinContent(ibin);
     double Error = Hists.at(0)->GetBinError(ibin);

     vector<double> PDF_mc;
     for(int i = 1; i < Hists.size(); i++){
       PDF_mc.push_back(Hists.at(i)->GetBinContent(ibin));
       Unc = CalculateStdDev(PDF_mc);
     }
     PDF_mc.clear();

     PDF_up->SetBinContent(ibin, Central + Unc);
     PDF_up->SetBinError(ibin, Error);
     PDF_down->SetBinContent(ibin, Central - Unc);
     PDF_down->SetBinError(ibin, Error);
   }
 };

 TString InputRootDIR = "run";
 TString SaveRootDIR = "PDFVariation";
 mkdir(SaveRootDIR.Data());

 vector<TString> Channels = {"Run3_el", "Run3_mu"};
 vector<TString> Regions = {"SR", "SRspec", "WCRVR", "ZCRVR"};

 vector<TString> PDFNames_Sherpa;
 vector<TString> PDFNames_Top;

 PDFNames_Sherpa.push_back("nominal");
 for(int i = 1; i <= 100; i++){
   TString DirName = TString::Format("MUR1_MUF1_PDF303%03d", 200 + i);
   PDFNames_Sherpa.push_back(DirName);
   cout<<DirName<<endl;
 }

 PDFNames_Top.push_back("nominal");
 for(int i = 1; i <= 100; i++){
   TString DirName = TString::Format("MUR1_MUF1_PDF260%03d", + i);
   PDFNames_Top.push_back(DirName);
   cout<<DirName<<endl;
 }

 vector<TString> Samples_Sherpa = {"Wjets_combined.histos.root", "Zjets_combined.histos.root"};
 vector<TString> Samples_Top = {"ttbar_combined.histos.root", "single-t_combined.histos.root"};

 vector<TString> Histograms_WCRVR = {"LeadingLeptonPt",
                                     "LeadingJetPt",
                                     "LeadingLeptonEta",
                                     "LeadingLeptonPhi",
                                     "LeadingLeptonP",
                                     "LeadingLeptonE",
                                     "LeadingJetEta",
                                     "LeadingJetPhi",
                                     "LeadingJetY",
                                     "LeadingJetE",
                                     "LeadingJetP",
                                     "detaLepJet",
                                     "dphiLepJet",
                                     "dRLepJet",
                                     "metFinalTrkSumEt",
                                     "metFinalTrkSignificance",
                                     "njet",
                                     "mLepJet",
                                     "mLepJetCR",
                                     "mLepJetVR",
				     "mLepJetCRVRCombine",
                                     "mLepJetCRVR",
                                     "mLepJetCRVR_logX",
                                     "mt_lep1",
                                    };

 vector<TString> Histograms_ZCRVR = {"LeadingLeptonPt",
                                     "LeadingJetPt",
                                     "LeadingLeptonEta",
                                     "LeadingLeptonPhi",
                                     "LeadingLeptonP",
                                     "LeadingLeptonE",
                                     "LeadingJetEta",
                                     "LeadingJetPhi",
                                     "LeadingJetY",
                                     "LeadingJetE",
                                     "LeadingJetP",
                                     "detaLepJet",
                                     "dphiLepJet",
                                     "dRLepJet",
                                     "metFinalTrkSumEt",
                                     "metFinalTrkSignificance",
                                     "njet",
                                     "mLepJet",
                                     "mLepJetCR",
                                     "mLepJetVR",
				     "mLepJetCRVRCombine",
                                     "mLepJetCRVR",
                                     "mLepJetCRVR_logX",
                                     "m_ll",
                                    };


 vector<TString> Histograms_SR = {"LeadingLeptonPt",
                                  "LeadingLeptonEta",
                                  "LeadingLeptonPhi",
                                  "LeadingJetPt",
                                  "LeadingJetEta",
                                  "LeadingJetPhi",
                                  "metFinalTrkSignificance",
                                  "mLepJet",
                                  "mLepJet20",
                                  "mLepJet40",
                                  "mLepJetSR",
                                  "mLepJetSR1bin",
                                  "mLepJetSR_logX",
				  "mLepJetSR_logX_2"
                                 };

 vector<TString> Histograms_SRspec = {"LeadingLeptonPt",
                                      "LeadingLeptonEta",
                                      "LeadingLeptonPhi",
                                      "LeadingJetPt",
                                      "LeadingJetEta",
                                      "LeadingJetPhi",
                                      "metFinalTrkSignificance",
                                      "mLepJet",
                                      "mLepJet_pad1",
                                      "mLepJet_logX",
                                     };

 map<tuple<TString, TString>, double> nominal_SR_Norm;
 map<tuple<TString, TString>, double> nominal_WCRVR_Norm;
 map<tuple<TString, TString>, double> nominal_ZCRVR_Norm;

 map<tuple<TString, TString>, double> Sherpa_PDF_up_SR_Norm;
 map<tuple<TString, TString>, double> Sherpa_PDF_up_WCRVR_Norm;
 map<tuple<TString, TString>, double> Sherpa_PDF_up_ZCRVR_Norm;

 map<tuple<TString, TString>, double> Sherpa_PDF_down_SR_Norm;
 map<tuple<TString, TString>, double> Sherpa_PDF_down_WCRVR_Norm;
 map<tuple<TString, TString>, double> Sherpa_PDF_down_ZCRVR_Norm;

 map<tuple<TString, TString>, double> Top_PDF_up_SR_Norm;
 map<tuple<TString, TString>, double> Top_PDF_up_WCRVR_Norm;
 map<tuple<TString, TString>, double> Top_PDF_up_ZCRVR_Norm;

 map<tuple<TString, TString>, double> Top_PDF_down_SR_Norm;
 map<tuple<TString, TString>, double> Top_PDF_down_WCRVR_Norm;
 map<tuple<TString, TString>, double> Top_PDF_down_ZCRVR_Norm;

 map<tuple<TString, TString>, double> Normalization_Sherpa_PDF_up;
 map<tuple<TString, TString>, double> Normalization_Sherpa_PDF_down;
 map<tuple<TString, TString>, double> Normalization_Top_PDF_up;
 map<tuple<TString, TString>, double> Normalization_Top_PDF_down;

 function<void(vector<TString>, vector<TString>, vector<TString>, TString, TString, TString, TString, TString, bool, map<tuple<TString, TString>, double>, map<tuple<TString, TString>, double>)> GetPDFUncertainty = [&](vector<TString> Samples,
                                                                                                                                                     vector<TString> PDFNames,
                                                                                                                                                     vector<TString> Histograms,
                                                                                                                                                     TString InputDIR,
                                                                                                                                                     TString SaveDIR,
                                                                                                                                                     TString UncType,
                                                                                                                                                     TString Region,
                                                                                                                                                     TString Channel,
                                                                                                                                                     bool isNormalized,
                                                                                                                                                     map<tuple<TString, TString>, double> upNorm,
                                                                                                                                                     map<tuple<TString, TString>, double> downNorm){
   TString PDF_up_Name;
   TString PDF_down_Name;

   if(!isNormalized){
     PDF_up_Name = SaveDIR + "PDF_up";
     PDF_down_Name = SaveDIR + "PDF_down";
   }
   else{
     PDF_up_Name = SaveDIR + "PDF_Normalized_up";
     PDF_down_Name = SaveDIR + "PDF_Normalized_down";
   }

   mkdir(PDF_up_Name.Data());
   mkdir(PDF_down_Name.Data());

   map<TString, vector<TFile*>> Files;
   map<TString, TFile*> File_PDF_up;
   map<TString, TFile*> File_PDF_down;
   for(int isample = 0; isample < Samples.size(); isample++){
     Files[Samples.at(isample)] = {};
     Files.at(Samples.at(isample)).resize(PDFNames.size());
     for(int ipdf = 0; ipdf < PDFNames.size(); ipdf++){
       Files.at(Samples.at(isample)).at(ipdf) = new TFile(InputDIR + "/" + PDFNames.at(ipdf) + "/" + Samples.at(isample));
     }

     File_PDF_up[Samples.at(isample)] = new TFile(PDF_up_Name + "/" + Samples.at(isample), "RECREATE");
     File_PDF_down[Samples.at(isample)] = new TFile(PDF_down_Name + "/" + Samples.at(isample), "RECREATE");
   }

   for(int isample = 0; isample < Samples.size(); isample++){
     for(int ihist = 0; ihist < Histograms.size(); ihist++){
       cout<<Histograms.at(ihist)<<":"<<endl;
       vector<TH1D *> hists(PDFNames.size());
       TH1D* PDF_up;
       TH1D* PDF_down;
       for(int ipdf = 0; ipdf < PDFNames.size(); ipdf++){
         hists.at(ipdf) = (TH1D *)Files.at(Samples.at(isample)).at(ipdf)->Get(Histograms.at(ihist));
       }
       if(UncType == "Hessian") GetPDFUnc_Hessian(hists, PDF_up, PDF_down);
       else if(UncType == "MonteCarlo") GetPDFUnc_MonteCarlo(hists, PDF_up, PDF_down);

       if(!isNormalized){
         if(Histograms.at(ihist) == "LeadingLeptonPt"){
           if(Region == "SR"){
             nominal_SR_Norm[make_tuple(Samples.at(isample), Channel)] = hists.at(0)->Integral();
             if(UncType == "Hessian"){
               Sherpa_PDF_up_SR_Norm[make_tuple(Samples.at(isample), Channel)] = PDF_up->Integral();
               Sherpa_PDF_down_SR_Norm[make_tuple(Samples.at(isample), Channel)] = PDF_down->Integral();
             }
             if(UncType == "MonteCarlo"){
               Top_PDF_up_SR_Norm[make_tuple(Samples.at(isample), Channel)] = PDF_up->Integral();
               Top_PDF_down_SR_Norm[make_tuple(Samples.at(isample), Channel)] = PDF_down->Integral();
             }
           }
  
           if(Region == "WCRVR"){
             nominal_WCRVR_Norm[make_tuple(Samples.at(isample), Channel)] = hists.at(0)->Integral();
             if(UncType == "Hessian"){
               Sherpa_PDF_up_WCRVR_Norm[make_tuple(Samples.at(isample), Channel)] = PDF_up->Integral();
               Sherpa_PDF_down_WCRVR_Norm[make_tuple(Samples.at(isample), Channel)] = PDF_down->Integral();
             }
             if(UncType == "MonteCarlo"){
               Top_PDF_up_WCRVR_Norm[make_tuple(Samples.at(isample), Channel)] = PDF_up->Integral();
               Top_PDF_down_WCRVR_Norm[make_tuple(Samples.at(isample), Channel)] = PDF_down->Integral();
             }
           }
  
           if(Region == "ZCRVR"){
             nominal_ZCRVR_Norm[make_tuple(Samples.at(isample), Channel)] = hists.at(0)->Integral();
             if(UncType == "Hessian"){
               Sherpa_PDF_up_ZCRVR_Norm[make_tuple(Samples.at(isample), Channel)] = PDF_up->Integral();
               Sherpa_PDF_down_ZCRVR_Norm[make_tuple(Samples.at(isample), Channel)] = PDF_down->Integral();
             }
             if(UncType == "MonteCarlo"){
               Top_PDF_up_ZCRVR_Norm[make_tuple(Samples.at(isample), Channel)] = PDF_up->Integral();
               Top_PDF_down_ZCRVR_Norm[make_tuple(Samples.at(isample), Channel)] = PDF_down->Integral();
             }
           }
         }
       }

       if(isNormalized){
         PDF_up->Scale(upNorm.at(make_tuple(Samples.at(isample), Channel)));
         PDF_down->Scale(downNorm.at(make_tuple(Samples.at(isample), Channel)));
       }

       File_PDF_up.at(Samples.at(isample))->cd();
       PDF_up->Write(Histograms.at(ihist));

       File_PDF_down.at(Samples.at(isample))->cd();
       PDF_down->Write(Histograms.at(ihist));
     }
   }

   for(int isample = 0; isample < Samples.size(); isample++){
     Files.at(Samples.at(isample)).resize(PDFNames.size());
     for(int ipdf = 0; ipdf < PDFNames.size(); ipdf++){
       Files.at(Samples.at(isample)).at(ipdf)->Close();
     }

     File_PDF_up.at(Samples.at(isample))->Close();
     File_PDF_down.at(Samples.at(isample))->Close();
   }

 };

 for(int ichannel = 0; ichannel < Channels.size(); ichannel++){
   mkdir((SaveRootDIR + "/" + Channels.at(ichannel)).Data());

   for(int iregion = 0; iregion < Regions.size(); iregion++){
     mkdir((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion)).Data());

     TString InputDIR = InputRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion);
     TString SaveDIR;

     vector<TString> Histograms;

     if(Regions.at(iregion) == "SR") Histograms = Histograms_SR;
     else if(Regions.at(iregion) == "SRspec") Histograms = Histograms_SRspec;
     else if(Regions.at(iregion) == "WCRVR") Histograms = Histograms_WCRVR;
     else if(Regions.at(iregion) == "ZCRVR") Histograms = Histograms_ZCRVR;

     SaveDIR = SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "/Sherpa_";
     GetPDFUncertainty(Samples_Sherpa, PDFNames_Sherpa, Histograms, InputDIR, SaveDIR, "Hessian", Regions.at(iregion), Channels.at(ichannel),
                false, Normalization_Sherpa_PDF_up, Normalization_Sherpa_PDF_down);

     SaveDIR = SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "/Top_";
     GetPDFUncertainty(Samples_Top, PDFNames_Top, Histograms, InputDIR, SaveDIR, "MonteCarlo", Regions.at(iregion), Channels.at(ichannel),
                false, Normalization_Top_PDF_up, Normalization_Top_PDF_down);

   }
 }

 for(int ichannel = 0; ichannel < Channels.size(); ichannel++){

   vector<TString> Samples;

   Samples = Samples_Sherpa;

   for(int isample = 0; isample < Samples.size(); isample++){

     Normalization_Sherpa_PDF_up[make_tuple(Samples.at(isample), Channels.at(ichannel))] = (nominal_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                                                          + nominal_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                                                          + nominal_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))])
                                                                                          /(Sherpa_PDF_up_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                                                          + Sherpa_PDF_up_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                                                          + Sherpa_PDF_up_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]);

     Normalization_Sherpa_PDF_down[make_tuple(Samples.at(isample), Channels.at(ichannel))] = (nominal_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                                                            + nominal_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                                                            + nominal_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))])
                                                                                          / (Sherpa_PDF_down_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                                                            + Sherpa_PDF_down_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                                                            + Sherpa_PDF_down_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]);

     cout<<"For channel "<<Channels.at(ichannel)<<" sample "<<Samples.at(isample)<<":"<<endl;
     cout<<"nominal  SR = "<<setw(10)<<fixed<<setprecision(3)<<nominal_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))];
     cout<<"  WCRVR = "<<setw(10)<<fixed<<setprecision(3)<<nominal_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))];
     cout<<"  ZCRVR = "<<setw(10)<<fixed<<setprecision(3)<<nominal_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]<<endl;
     cout<<"PDF up   SR = "<<setw(10)<<fixed<<setprecision(3)<<Sherpa_PDF_up_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))];
     cout<<"  WCRVR = "<<setw(10)<<fixed<<setprecision(3)<<Sherpa_PDF_up_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))];
     cout<<"  ZCRVR = "<<setw(10)<<fixed<<setprecision(3)<<Sherpa_PDF_up_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]<<endl;
     cout<<"PDF down SR = "<<setw(10)<<fixed<<setprecision(3)<<Sherpa_PDF_down_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))];
     cout<<"  WCRVR = "<<setw(10)<<fixed<<setprecision(3)<<Sherpa_PDF_down_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))];
     cout<<"  ZCRVR = "<<setw(10)<<fixed<<setprecision(3)<<Sherpa_PDF_down_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]<<endl;
     cout<<"Normalization Sherpa PDF up: "<<setw(10)<<fixed<<setprecision(3)<<Normalization_Sherpa_PDF_up[make_tuple(Samples.at(isample), Channels.at(ichannel))]<<endl;
     cout<<"Normalization Sherpa PDF down: "<<setw(10)<<fixed<<setprecision(3)<<Normalization_Sherpa_PDF_down[make_tuple(Samples.at(isample), Channels.at(ichannel))]<<endl;
   }

   Samples = Samples_Top;

   for(int isample = 0; isample < Samples.size(); isample++){

     Normalization_Top_PDF_up[make_tuple(Samples.at(isample), Channels.at(ichannel))] = (nominal_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                    + nominal_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                    + nominal_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))])
                                                   / (Top_PDF_up_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                    + Top_PDF_up_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                    + Top_PDF_up_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]);

     Normalization_Top_PDF_down[make_tuple(Samples.at(isample), Channels.at(ichannel))] = (nominal_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                      + nominal_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                      + nominal_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))])
                                                     / (Top_PDF_down_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                      + Top_PDF_down_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]
                                                      + Top_PDF_down_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]);

     cout<<"For channel "<<Channels.at(ichannel)<<" sample "<<Samples.at(isample)<<":"<<endl;
     cout<<"nominal  SR = "<<setw(10)<<fixed<<setprecision(3)<<nominal_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))];
     cout<<"  WCRVR = "<<setw(10)<<fixed<<setprecision(3)<<nominal_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))];
     cout<<"  ZCRVR = "<<setw(10)<<fixed<<setprecision(3)<<nominal_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]<<endl;
     cout<<"PDF up   SR = "<<setw(10)<<fixed<<setprecision(3)<<Top_PDF_up_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))];
     cout<<"  WCRVR = "<<setw(10)<<fixed<<setprecision(3)<<Top_PDF_up_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))];
     cout<<"  ZCRVR = "<<setw(10)<<fixed<<setprecision(3)<<Top_PDF_up_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]<<endl;
     cout<<"PDF down SR = "<<setw(10)<<fixed<<setprecision(3)<<Top_PDF_down_SR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))];
     cout<<"  WCRVR = "<<setw(10)<<fixed<<setprecision(3)<<Top_PDF_down_WCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))];
     cout<<"  ZCRVR = "<<setw(10)<<fixed<<setprecision(3)<<Top_PDF_down_ZCRVR_Norm[make_tuple(Samples.at(isample), Channels.at(ichannel))]<<endl;
     cout<<"Normalization Top PDF up: "<<setw(10)<<fixed<<setprecision(3)<<Normalization_Top_PDF_up[make_tuple(Samples.at(isample), Channels.at(ichannel))]<<endl;
     cout<<"Normalization Top PDF down: "<<setw(10)<<fixed<<setprecision(3)<<Normalization_Top_PDF_down[make_tuple(Samples.at(isample), Channels.at(ichannel))]<<endl;
   }

 }




 for(int ichannel = 0; ichannel < Channels.size(); ichannel++){
   mkdir((SaveRootDIR + "/" + Channels.at(ichannel)).Data());

   for(int iregion = 0; iregion < Regions.size(); iregion++){
     mkdir((SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion)).Data());

     TString InputDIR = InputRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion);
     TString SaveDIR;

     vector<TString> Histograms;

     if(Regions.at(iregion) == "SR") Histograms = Histograms_SR;
     else if(Regions.at(iregion) == "SRspec") Histograms = Histograms_SRspec;
     else if(Regions.at(iregion) == "WCRVR") Histograms = Histograms_WCRVR;
     else if(Regions.at(iregion) == "ZCRVR") Histograms = Histograms_ZCRVR;

     SaveDIR = SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "/Sherpa_";
     GetPDFUncertainty(Samples_Sherpa, PDFNames_Sherpa, Histograms, InputDIR, SaveDIR, "Hessian", Regions.at(iregion), Channels.at(ichannel),
                 true, Normalization_Sherpa_PDF_up, Normalization_Sherpa_PDF_down);

     SaveDIR = SaveRootDIR + "/" + Channels.at(ichannel) + "/" + Regions.at(iregion) + "/Top_";
     GetPDFUncertainty(Samples_Top, PDFNames_Top, Histograms, InputDIR, SaveDIR, "MonteCarlo", Regions.at(iregion), Channels.at(ichannel),
                 true, Normalization_Top_PDF_up, Normalization_Top_PDF_down);

   }
 }


}

