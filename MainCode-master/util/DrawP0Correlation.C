#include <iostream>
#include "RootCommon.h"
#include "PDFHelper/PDFReweight.h"

using namespace std;

int main(int argc, char** argv)
{
 vector<TH1D *> D05fbP0u_Theory(59);
 vector<TH1D *> D05fbP0d_Theory(59);
 vector<TH1D *> D05fbP0Delta_Theory(59);

 vector<TH1D *> CMS8TeVP0u_bin1_Theory(59);
 vector<TH1D *> CMS8TeVP0d_bin1_Theory(59);
 vector<TH1D *> CMS8TeVP0Delta_bin1_Theory(59);
 vector<TH1D *> CMS8TeVP0u_bin2_Theory(59);
 vector<TH1D *> CMS8TeVP0d_bin2_Theory(59);
 vector<TH1D *> CMS8TeVP0Delta_bin2_Theory(59);
 vector<TH1D *> CMS8TeVP0u_bin3_Theory(59);
 vector<TH1D *> CMS8TeVP0d_bin3_Theory(59);
 vector<TH1D *> CMS8TeVP0Delta_bin3_Theory(59);
 vector<TH1D *> CMS8TeVP0u_bin4_Theory(59);
 vector<TH1D *> CMS8TeVP0d_bin4_Theory(59);
 vector<TH1D *> CMS8TeVP0Delta_bin4_Theory(59);

 TFile *file = new TFile("save.root");
 for(int i = 0; i < 59; i++){
   D05fbP0u_Theory.at(i) = (TH1D *)file->Get((TString)"D05fbP0u_Theory" + (int)i);
   D05fbP0d_Theory.at(i) = (TH1D *)file->Get((TString)"D05fbP0d_Theory" + (int)i);
   D05fbP0Delta_Theory.at(i) = (TH1D *)file->Get((TString)"D05fbP0Delta_Theory" + (int)i);
   CMS8TeVP0u_bin1_Theory.at(i) = (TH1D *)file->Get((TString)"CMS8TeVP0u_bin1_Theory" + (int)i);
   CMS8TeVP0d_bin1_Theory.at(i) = (TH1D *)file->Get((TString)"CMS8TeVP0d_bin1_Theory" + (int)i);
   CMS8TeVP0Delta_bin1_Theory.at(i) = (TH1D *)file->Get((TString)"CMS8TeVP0Delta_bin1_Theory" + (int)i);
   CMS8TeVP0u_bin2_Theory.at(i) = (TH1D *)file->Get((TString)"CMS8TeVP0u_bin2_Theory" + (int)i);
   CMS8TeVP0d_bin2_Theory.at(i) = (TH1D *)file->Get((TString)"CMS8TeVP0d_bin2_Theory" + (int)i);
   CMS8TeVP0Delta_bin2_Theory.at(i) = (TH1D *)file->Get((TString)"CMS8TeVP0Delta_bin2_Theory" + (int)i);
   CMS8TeVP0u_bin3_Theory.at(i) = (TH1D *)file->Get((TString)"CMS8TeVP0u_bin3_Theory" + (int)i);
   CMS8TeVP0d_bin3_Theory.at(i) = (TH1D *)file->Get((TString)"CMS8TeVP0d_bin3_Theory" + (int)i);
   CMS8TeVP0Delta_bin3_Theory.at(i) = (TH1D *)file->Get((TString)"CMS8TeVP0Delta_bin3_Theory" + (int)i);
   CMS8TeVP0u_bin4_Theory.at(i) = (TH1D *)file->Get((TString)"CMS8TeVP0u_bin4_Theory" + (int)i);
   CMS8TeVP0d_bin4_Theory.at(i) = (TH1D *)file->Get((TString)"CMS8TeVP0d_bin4_Theory" + (int)i);
   CMS8TeVP0Delta_bin4_Theory.at(i) = (TH1D *)file->Get((TString)"CMS8TeVP0Delta_bin4_Theory" + (int)i);
 }

 PDFReweight* PDFPlot = new PDFReweight();
 PDFPlot->openFile("Dilution.root");
 PDFPlot->InitialPDF("CT18NNLO", 0);
 PDFPlot->DrawPartonCorrelation(D05fbP0u_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(D05fbP0d_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(D05fbP0Delta_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0u_bin1_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0d_bin1_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0Delta_bin1_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0u_bin2_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0d_bin2_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0Delta_bin2_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0u_bin3_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0d_bin3_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0Delta_bin3_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0u_bin4_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0d_bin4_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0Delta_bin4_Theory, 41, 58, "Symmetry");
 PDFPlot->SaveFile();

 return 1;
}
