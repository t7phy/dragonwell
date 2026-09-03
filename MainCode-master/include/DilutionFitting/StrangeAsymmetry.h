#ifndef DilutionFitting_StrangeAsymmetry_h
#define DilutionFitting_StrangeAsymmetry_h

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Uncertainty/PDFUncertainty.h"
#include "Uncertainty/FitAFBStw.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "TMinuitHelper/TMinuitHelper.h"
#include "ePumpHelper/ePumpHelper.h"
#include <iostream>

using namespace std;

TH1D *global_Data_WPlusAFC_MT;
TH1D *global_Data_WMinusAFC_MT;

map<vector<int>, TH1D *> *global_WPlusRelativeXsec_MT_ud_Ensemble;
map<vector<int>, TH1D *> *global_WPlusRelativeXsec_MT_cs_Ensemble;
map<vector<int>, TH1D *> *global_WPlusRelativeXsec_MT_other_Ensemble;

map<vector<int>, TH1D *> *global_WMinusRelativeXsec_MT_ud_Ensemble;
map<vector<int>, TH1D *> *global_WMinusRelativeXsec_MT_cs_Ensemble;
map<vector<int>, TH1D *> *global_WMinusRelativeXsec_MT_other_Ensemble;

map<vector<int>, TH1D *> *global_WPlusAFC_MT_ud_Residual_Ensemble;
map<vector<int>, TH1D *> *global_WPlusAFC_MT_cs_Residual_Ensemble;

map<vector<int>, TH1D *> *global_WMinusAFC_MT_ud_Residual_Ensemble;
map<vector<int>, TH1D *> *global_WMinusAFC_MT_cs_Residual_Ensemble;

map<vector<int>, TH1D *> *global_WPlusAFC_MT_ud_Average_Ensemble;
map<vector<int>, TH1D *> *global_WPlusAFC_MT_cs_Average_Ensemble;

map<vector<int>, TH1D *> *global_WMinusAFC_MT_ud_Average_Ensemble;
map<vector<int>, TH1D *> *global_WMinusAFC_MT_cs_Average_Ensemble;

map<vector<int>, TH1D *> *global_WPlusAFC_MT_other_Ensemble;
map<vector<int>, TH1D *> *global_WMinusAFC_MT_other_Ensemble;

TH1D *global_Data_PositiveAFC;
TH1D *global_Data_NegativeAFC;

map<vector<int>, TH1D *> *global_PositiveAFC_uu_Residual_Ensemble;
map<vector<int>, TH1D *> *global_NegativeAFC_uu_Residual_Ensemble;
map<vector<int>, TH1D *> *global_PositiveAFC_dd_Residual_Ensemble;
map<vector<int>, TH1D *> *global_NegativeAFC_dd_Residual_Ensemble;
map<vector<int>, TH1D *> *global_PositiveAFC_ss_Residual_Ensemble;
map<vector<int>, TH1D *> *global_NegativeAFC_ss_Residual_Ensemble;
map<vector<int>, TH1D *> *global_PositiveAFC_other_Ensemble;
map<vector<int>, TH1D *> *global_NegativeAFC_other_Ensemble;

map<vector<int>, TH1D *> *global_RelativeXsec_uu_Ensemble;
map<vector<int>, TH1D *> *global_RelativeXsec_dd_Ensemble;
map<vector<int>, TH1D *> *global_RelativeXsec_ss_Ensemble;
map<vector<int>, TH1D *> *global_RelativeXsec_other_Ensemble;


int global_iPDF_as;

double MinChi2_as = 100000.0;

void WStrangeAsymmetryFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 double Chi2 = 0.0;
 double Chi2_WPlus = 0.0;
 double Chi2_WMinus = 0.0;

 TH1D* WPlusAFC_MT = (TH1D *)global_Data_WPlusAFC_MT->Clone("WPlusAFC_MT");
 WPlusAFC_MT->Reset();
 TH1D* WMinusAFC_MT = (TH1D *)global_Data_WMinusAFC_MT->Clone("WMinusAFC_MT");
 WMinusAFC_MT->Reset();

 TH1D* WPlusRelativeXsec_MT_ud = (TH1D *)(*global_WPlusRelativeXsec_MT_ud_Ensemble)[(vector<int>{global_iPDF_as})]->Clone("WPlusRelativeXsec_MT_ud");
 TH1D* WPlusRelativeXsec_MT_cs = (TH1D *)(*global_WPlusRelativeXsec_MT_cs_Ensemble)[(vector<int>{global_iPDF_as})]->Clone("WPlusRelativeXsec_MT_cs");

 TH1D* WMinusRelativeXsec_MT_ud = (TH1D *)(*global_WMinusRelativeXsec_MT_ud_Ensemble)[(vector<int>{global_iPDF_as})]->Clone("WMinusRelativeXsec_MT_ud");
 TH1D* WMinusRelativeXsec_MT_cs = (TH1D *)(*global_WMinusRelativeXsec_MT_cs_Ensemble)[(vector<int>{global_iPDF_as})]->Clone("WMinusRelativeXsec_MT_cs");

 WPlusRelativeXsec_MT_ud->Scale(par[0]);
 WPlusRelativeXsec_MT_cs->Scale(par[1]);

 WMinusRelativeXsec_MT_ud->Scale(par[4]);
 WMinusRelativeXsec_MT_cs->Scale(par[5]);

 for(int ibin = 1; ibin <= WPlusAFC_MT->GetNbinsX(); ibin++){
   double WPlusAFC_ud = (*global_WPlusAFC_MT_ud_Residual_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) + par[2];
   double WPlusAFC_cs = (*global_WPlusAFC_MT_cs_Residual_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) + par[3];

   double WMinusAFC_ud = (*global_WMinusAFC_MT_ud_Residual_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) + par[6];
   double WMinusAFC_cs = (*global_WMinusAFC_MT_cs_Residual_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) + par[7];

   double WPlusOther = (*global_WPlusAFC_MT_other_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) * (*global_WPlusRelativeXsec_MT_other_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin);
   double WMinusOther = (*global_WMinusAFC_MT_other_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) * (*global_WMinusRelativeXsec_MT_other_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin);

   double WPlusXsec_ud = WPlusRelativeXsec_MT_ud->GetBinContent(ibin);
   double WPlusXsec_cs = WPlusRelativeXsec_MT_cs->GetBinContent(ibin);
   double WMinusXsec_ud = WMinusRelativeXsec_MT_ud->GetBinContent(ibin);
   double WMinusXsec_cs = WMinusRelativeXsec_MT_cs->GetBinContent(ibin);

   double WPlusValue = WPlusXsec_ud * WPlusAFC_ud + WPlusXsec_cs * WPlusAFC_cs + WPlusOther;
   double WMinusValue = WMinusXsec_ud * WMinusAFC_ud + WMinusXsec_cs * WMinusAFC_cs + WMinusOther;

   WPlusAFC_MT->SetBinContent(ibin, WPlusValue);
   WMinusAFC_MT->SetBinContent(ibin, WMinusValue);
 }

 Chi2_WPlus = CalculateChi2(global_Data_WPlusAFC_MT, WPlusAFC_MT);
 Chi2_WMinus = CalculateChi2(global_Data_WMinusAFC_MT, WMinusAFC_MT);
 Chi2 = Chi2_WPlus + Chi2_WMinus;

 f = Chi2;
 if(f < MinChi2_as) MinChi2_as = f;

 delete WPlusAFC_MT;
 delete WMinusAFC_MT;
 delete WPlusRelativeXsec_MT_ud;
 delete WPlusRelativeXsec_MT_cs;
 delete WMinusRelativeXsec_MT_ud;
 delete WMinusRelativeXsec_MT_cs;

 cout<<"Min Chi2 = "<<MinChi2_as<<endl;

}

void ZStrangeAsymmetryFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 double Chi2 = 0.0;
 double Chi2_Positive = 0.0;
 double Chi2_Negative = 0.0;

 TH1D* PositiveAFC = (TH1D *)global_Data_PositiveAFC->Clone("PositiveAFC");
 PositiveAFC->Reset();
 TH1D* NegativeAFC = (TH1D *)global_Data_NegativeAFC->Clone("NegativeAFC");
 NegativeAFC->Reset();

 TH1D* RelativeXsec_uu = (TH1D *)(*global_RelativeXsec_uu_Ensemble)[(vector<int>{global_iPDF_as})]->Clone("RelativeXsec_uu");
 TH1D* RelativeXsec_dd = (TH1D *)(*global_RelativeXsec_dd_Ensemble)[(vector<int>{global_iPDF_as})]->Clone("RelativeXsec_dd");
 TH1D* RelativeXsec_ss = (TH1D *)(*global_RelativeXsec_ss_Ensemble)[(vector<int>{global_iPDF_as})]->Clone("RelativeXsec_ss");

 RelativeXsec_uu->Scale(par[0]);
 RelativeXsec_dd->Scale(par[1]);
 RelativeXsec_ss->Scale(par[2]);

 for(int ibin = 1; ibin <= PositiveAFC->GetNbinsX(); ibin++){
   double PositiveAFC_uu = (*global_PositiveAFC_uu_Residual_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) + par[3];
   double PositiveAFC_dd = (*global_PositiveAFC_dd_Residual_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) + par[4];
   double PositiveAFC_ss = (*global_PositiveAFC_ss_Residual_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) + par[5];

   double NegativeAFC_uu = (*global_NegativeAFC_uu_Residual_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) + par[6];
   double NegativeAFC_dd = (*global_NegativeAFC_dd_Residual_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) + par[7];
   double NegativeAFC_ss = (*global_NegativeAFC_ss_Residual_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) + par[8];

   double PositiveOther = (*global_PositiveAFC_other_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) * (*global_RelativeXsec_other_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin);
   double NegativeOther = (*global_NegativeAFC_other_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin) * (*global_RelativeXsec_other_Ensemble)[(vector<int>{global_iPDF_as})]->GetBinContent(ibin);

   double Xsec_uu = RelativeXsec_uu->GetBinContent(ibin);
   double Xsec_dd = RelativeXsec_dd->GetBinContent(ibin);
   double Xsec_ss = RelativeXsec_ss->GetBinContent(ibin);

   double PositiveValue = Xsec_uu * PositiveAFC_uu + Xsec_dd * PositiveAFC_dd + Xsec_ss * PositiveAFC_ss + PositiveOther;
   double NegativeValue = Xsec_uu * NegativeAFC_uu + Xsec_dd * NegativeAFC_dd + Xsec_ss * NegativeAFC_ss + NegativeOther;

   PositiveAFC->SetBinContent(ibin, PositiveValue);
   NegativeAFC->SetBinContent(ibin, NegativeValue);
 }

 Chi2_Positive = CalculateChi2(global_Data_PositiveAFC, PositiveAFC);
 Chi2_Negative = CalculateChi2(global_Data_NegativeAFC, NegativeAFC);
 Chi2 = Chi2_Positive + Chi2_Negative;

 f = Chi2;
 if(f < MinChi2_as) MinChi2_as = f;

 delete PositiveAFC;
 delete NegativeAFC;
 delete RelativeXsec_uu;
 delete RelativeXsec_dd;
 delete RelativeXsec_ss;

 cout<<"Min Chi2 = "<<MinChi2_as<<endl;

}

class StrangeAsymmetry
{
 public:

 TMinuitHelper* myMinuit;

/////////////////////////////////////////////////////
 TString WPlusRelativeXsec_MT_ud_Name = "WPlusRelativeXsec_MT_ud";
 TString WPlusRelativeXsec_MT_cs_Name = "WPlusRelativeXsec_MT_cs";
 TString WPlusRelativeXsec_MT_other_Name = "WPlusRelativeXsec_MT_other";
 TString WMinusRelativeXsec_MT_ud_Name = "WMinusRelativeXsec_MT_ud";
 TString WMinusRelativeXsec_MT_cs_Name = "WMinusRelativeXsec_MT_cs";
 TString WMinusRelativeXsec_MT_other_Name = "WMinusRelativeXsec_MT_other";
 TString WPlusAFC_MT_ud_Name = "WPlusAFC_MT_ud";
 TString WPlusAFC_MT_cs_Name = "WPlusAFC_MT_cs";
 TString WPlusAFC_MT_other_Name = "WPlusAFC_MT_other";
 TString WMinusAFC_MT_ud_Name = "WMinusAFC_MT_ud";
 TString WMinusAFC_MT_cs_Name = "WMinusAFC_MT_cs";
 TString WMinusAFC_MT_other_Name = "WMinusAFC_MT_other";

 TString WPlusAFC_MT_ud_Residual_Name = "WPlusAFC_MT_ud_Residual";
 TString WPlusAFC_MT_cs_Residual_Name = "WPlusAFC_MT_cs_Residual";
 TString WMinusAFC_MT_ud_Residual_Name = "WMinusAFC_MT_ud_Residual";
 TString WMinusAFC_MT_cs_Residual_Name = "WMinusAFC_MT_cs_Residual";
 TString WPlusAFC_MT_ud_Average_Name = "WPlusAFC_MT_ud_Average";
 TString WPlusAFC_MT_cs_Average_Name = "WPlusAFC_MT_cs_Average";
 TString WMinusAFC_MT_ud_Average_Name = "WMinusAFC_MT_ud_Average";
 TString WMinusAFC_MT_cs_Average_Name = "WMinusAFC_MT_cs_Average";

//////////////////////////////////////////////////////
 TString RelativeXsec_uu_Name = "RelativeXsec_uu";
 TString RelativeXsec_dd_Name = "RelativeXsec_dd";
 TString RelativeXsec_ss_Name = "RelativeXsec_ss";
 TString RelativeXsec_other_Name = "RelativeXsec_other";

 TString PositiveAFC_uu_Name = "PositiveAFC_uu";
 TString PositiveAFC_dd_Name = "PositiveAFC_dd";
 TString PositiveAFC_ss_Name = "PositiveAFC_ss";
 TString PositiveAFC_other_Name = "PositiveAFC_other";
 TString NegativeAFC_uu_Name = "NegativeAFC_uu";
 TString NegativeAFC_dd_Name = "NegativeAFC_dd";
 TString NegativeAFC_ss_Name = "NegativeAFC_ss";
 TString NegativeAFC_other_Name = "NegativeAFC_other";

 TString PositiveAFC_uu_Residual_Name = "PositiveAFC_uu_Residual";
 TString PositiveAFC_dd_Residual_Name = "PositiveAFC_dd_Residual";
 TString PositiveAFC_ss_Residual_Name = "PositiveAFC_ss_Residual";
 TString NegativeAFC_uu_Residual_Name = "NegativeAFC_uu_Residual";
 TString NegativeAFC_dd_Residual_Name = "NegativeAFC_dd_Residual";
 TString NegativeAFC_ss_Residual_Name = "NegativeAFC_ss_Residual";

 TString PositiveAFC_uu_Average_Name = "PositiveAFC_uu_Average";
 TString PositiveAFC_dd_Average_Name = "PositiveAFC_dd_Average";
 TString PositiveAFC_ss_Average_Name = "PositiveAFC_ss_Average";
 TString NegativeAFC_uu_Average_Name = "NegativeAFC_uu_Average";
 TString NegativeAFC_dd_Average_Name = "NegativeAFC_dd_Average";
 TString NegativeAFC_ss_Average_Name = "NegativeAFC_ss_Average";

 TString PositiveAFC_Name = "PositiveAFC";
 TString NegativeAFC_Name = "NegativeAFC";


//////////////////////////////////////////////////////

 TFile* writefile;

 TString DataName = "/ustcfs2/yfu/MainCode/run/WDilution/CT18As.00/MC_results.root";

 TString WPlusAFC_MT_Name = "WPlusAFC_MT";
 TString WMinusAFC_MT_Name = "WMinusAFC_MT";

 TString ErrorType = "Symmetry";

 vector<TString> rootNames;

//////////////////////////////////////////////////////

 TH1D *Data_WPlusAFC_MT;
 TH1D *Data_WMinusAFC_MT;
 TH1D *Data_WPlusAFC_MT_ud_Average;
 TH1D *Data_WPlusAFC_MT_cs_Average;
 TH1D *Data_WMinusAFC_MT_ud_Average;
 TH1D *Data_WMinusAFC_MT_cs_Average;

 map<vector<int>, TH1D *> WPlusRelativeXsec_MT_ud_Ensemble;
 map<vector<int>, TH1D *> WPlusRelativeXsec_MT_cs_Ensemble;
 map<vector<int>, TH1D *> WPlusRelativeXsec_MT_other_Ensemble;
 
 map<vector<int>, TH1D *> WMinusRelativeXsec_MT_ud_Ensemble;
 map<vector<int>, TH1D *> WMinusRelativeXsec_MT_cs_Ensemble;
 map<vector<int>, TH1D *> WMinusRelativeXsec_MT_other_Ensemble;
 
 map<vector<int>, TH1D *> WPlusAFC_MT_ud_Residual_Ensemble;
 map<vector<int>, TH1D *> WPlusAFC_MT_cs_Residual_Ensemble;
 
 map<vector<int>, TH1D *> WMinusAFC_MT_ud_Residual_Ensemble;
 map<vector<int>, TH1D *> WMinusAFC_MT_cs_Residual_Ensemble;
 
 map<vector<int>, TH1D *> WPlusAFC_MT_ud_Average_Ensemble;
 map<vector<int>, TH1D *> WPlusAFC_MT_cs_Average_Ensemble;
 
 map<vector<int>, TH1D *> WMinusAFC_MT_ud_Average_Ensemble;
 map<vector<int>, TH1D *> WMinusAFC_MT_cs_Average_Ensemble;
 
 map<vector<int>, TH1D *> WPlusAFC_MT_other_Ensemble;
 map<vector<int>, TH1D *> WMinusAFC_MT_other_Ensemble;

 map<vector<int>, TH1D *> Result_WPlusXsecStrength_ud;
 map<vector<int>, TH1D *> Result_WPlusXsecStrength_cs;
 map<vector<int>, TH1D *> Result_WPlusAFC_MT_ud_Average;
 map<vector<int>, TH1D *> Result_WPlusAFC_MT_cs_Average;
 map<vector<int>, TH1D *> Result_WMinusXsecStrength_ud;
 map<vector<int>, TH1D *> Result_WMinusXsecStrength_cs;
 map<vector<int>, TH1D *> Result_WMinusAFC_MT_ud_Average;
 map<vector<int>, TH1D *> Result_WMinusAFC_MT_cs_Average;

 map<vector<int>, TH1D *> Result_WPlusAFC_MT;
 map<vector<int>, TH1D *> Result_WMinusAFC_MT;

//////////////////////////////////////////////////////////////////////

 TH1D *Data_PositiveAFC;
 TH1D *Data_NegativeAFC;
 TH1D *Data_PositiveAFC_uu_Average;
 TH1D *Data_NegativeAFC_uu_Average;
 TH1D *Data_PositiveAFC_dd_Average;
 TH1D *Data_NegativeAFC_dd_Average;
 TH1D *Data_PositiveAFC_ss_Average;
 TH1D *Data_NegativeAFC_ss_Average;

 map<vector<int>, TH1D *> PositiveAFC_uu_Residual_Ensemble;
 map<vector<int>, TH1D *> NegativeAFC_uu_Residual_Ensemble;
 map<vector<int>, TH1D *> PositiveAFC_dd_Residual_Ensemble;
 map<vector<int>, TH1D *> NegativeAFC_dd_Residual_Ensemble;
 map<vector<int>, TH1D *> PositiveAFC_ss_Residual_Ensemble;
 map<vector<int>, TH1D *> NegativeAFC_ss_Residual_Ensemble;
 map<vector<int>, TH1D *> PositiveAFC_other_Ensemble;
 map<vector<int>, TH1D *> NegativeAFC_other_Ensemble;
 
 map<vector<int>, TH1D *> RelativeXsec_uu_Ensemble;
 map<vector<int>, TH1D *> RelativeXsec_dd_Ensemble;
 map<vector<int>, TH1D *> RelativeXsec_ss_Ensemble;
 map<vector<int>, TH1D *> RelativeXsec_other_Ensemble;

 map<vector<int>, TH1D *> Result_XsecStrength_uu;
 map<vector<int>, TH1D *> Result_XsecStrength_dd;
 map<vector<int>, TH1D *> Result_XsecStrength_ss;

 map<vector<int>, TH1D *> Result_PositiveAFC_uu_Average;
 map<vector<int>, TH1D *> Result_NegativeAFC_uu_Average;
 map<vector<int>, TH1D *> Result_PositiveAFC_dd_Average;
 map<vector<int>, TH1D *> Result_NegativeAFC_dd_Average;
 map<vector<int>, TH1D *> Result_PositiveAFC_ss_Average;
 map<vector<int>, TH1D *> Result_NegativeAFC_ss_Average;

 map<vector<int>, TH1D *> Result_PositiveAFC;
 map<vector<int>, TH1D *> Result_NegativeAFC;

 bool onlyCentral = false;

 StrangeAsymmetry();
 virtual void InitialData(TString DataName);
 virtual void OpenFile();
 virtual void Save(){
   writefile->cd();

   for(int i = 0; i < rootNames.size(); i++){
/*
     Result_WPlusXsecStrength_ud[(vector<int>{i})]->Write();
     Result_WPlusXsecStrength_cs[(vector<int>{i})]->Write();
     Result_WPlusAFC_MT_ud_Average[(vector<int>{i})]->Write();
     Result_WPlusAFC_MT_cs_Average[(vector<int>{i})]->Write();
     Result_WMinusXsecStrength_ud[(vector<int>{i})]->Write();
     Result_WMinusXsecStrength_cs[(vector<int>{i})]->Write();
     Result_WMinusAFC_MT_ud_Average[(vector<int>{i})]->Write();
     Result_WMinusAFC_MT_cs_Average[(vector<int>{i})]->Write();
*/
     Result_XsecStrength_uu[(vector<int>{i})]->Write();
     Result_XsecStrength_dd[(vector<int>{i})]->Write();
     Result_XsecStrength_ss[(vector<int>{i})]->Write();
  
     Result_PositiveAFC_uu_Average[(vector<int>{i})]->Write();
     Result_NegativeAFC_uu_Average[(vector<int>{i})]->Write();
     Result_PositiveAFC_dd_Average[(vector<int>{i})]->Write();
     Result_NegativeAFC_dd_Average[(vector<int>{i})]->Write();
     Result_PositiveAFC_ss_Average[(vector<int>{i})]->Write();
     Result_NegativeAFC_ss_Average[(vector<int>{i})]->Write();
  
     Result_PositiveAFC[(vector<int>{i})]->Write();
     Result_NegativeAFC[(vector<int>{i})]->Write();
   }

//   writefile->Write();
   writefile->Close();
   cout<<"File closed."<<endl;
 }

 virtual void InitialTheory();
 virtual void InitialResult();



 virtual void Fitting(int iPDF);
 virtual void FittingZ(int iPDF);
 virtual void OnlyCentral(){onlyCentral = true;}

};

#endif


