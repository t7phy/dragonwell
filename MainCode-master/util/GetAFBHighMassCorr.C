#include <iostream>
#include "RootCommon.h"
#include "Tools/Tools.h"
#include "PDFHelper/PDFReweight.h"

int main(int argc, char** argv)
{
 vector<TString> TheoryList;

 TString rootName;

 ifstream infile;
  infile.open("theory.list", ios::in);
 while(infile>>rootName){
   TheoryList.push_back(rootName);
 }
 infile.close();

 vector<TH1D *> AFB_CC(TheoryList.size());
 vector<TH1D *> AFB_CF(TheoryList.size());
 vector<TH1D *> ZHighMass_CC(TheoryList.size());
 vector<TH1D *> ZHighMass_CF(TheoryList.size());
 vector<TH1D *> ZRapidity_CC(TheoryList.size());
 vector<TH1D *> ZRapidity_CF(TheoryList.size());
 vector<TH1D *> ZRapidity_CF_Low(TheoryList.size());
 vector<TH1D *> WPlusXsec(TheoryList.size());
 vector<TH1D *> WMinusXsec(TheoryList.size());
 vector<TH1D *> WXsecAsymmetry(TheoryList.size());
 vector<TH2D *> Xsec_2D_CC(TheoryList.size());
 vector<TH2D *> Xsec_2D_CF(TheoryList.size());
 vector<TH2D *> AFB_Mass_ZY_CC(TheoryList.size());
 vector<TH2D *> AFB_Mass_ZY_CF(TheoryList.size());

 vector<TH1D *> AFB_HighMass2(TheoryList.size());
 vector<TH2D *> AFB_LowMass_ZY(TheoryList.size());

 vector<TH1D *> AFB_LowMass_ZY1(TheoryList.size());
 vector<TH1D *> AFB_LowMass_ZY2(TheoryList.size());
 vector<TH1D *> AFB_LowMass_ZY3(TheoryList.size());
 vector<TH1D *> AFB_LowMass_ZY4(TheoryList.size());
 vector<TH1D *> AFB_LowMass_ZY5(TheoryList.size());


 for(int i = 0; i < TheoryList.size(); i++){
   TFile* file = new TFile(TheoryList.at(i));
   AFB_CC.at(i) = (TH1D *)file->Get("AFB_Delta_CC");
   AFB_CF.at(i) = (TH1D *)file->Get("AFB_Delta_CF");
   ZHighMass_CC.at(i) = (TH1D *)file->Get("ZHighMass_CC");
   ZHighMass_CF.at(i) = (TH1D *)file->Get("ZHighMass_CF");
   ZRapidity_CC.at(i) = (TH1D *)file->Get("ZRapidity_CC");
   ZRapidity_CF.at(i) = (TH1D *)file->Get("ZRapidity_CF");
   ZRapidity_CF_Low.at(i) = (TH1D *)file->Get("ZRapidity_CF_Low");
   WPlusXsec.at(i) = (TH1D *)file->Get("WPlusXsec");
   WMinusXsec.at(i) = (TH1D *)file->Get("WMinusXsec");
   WXsecAsymmetry.at(i) = (TH1D *)file->Get("WBosonXsecAsymmetry");
   Xsec_2D_CC.at(i) = (TH2D *)file->Get("Xsec_2D_CC");
   Xsec_2D_CF.at(i) = (TH2D *)file->Get("Xsec_2D_CF");
   AFB_Mass_ZY_CC.at(i) = (TH2D *)file->Get("AFB_Mass_ZY_CC");
   AFB_Mass_ZY_CF.at(i) = (TH2D *)file->Get("AFB_Mass_ZY_CF");

   AFB_HighMass2.at(i) = (TH1D *)file->Get("AFB_HighMass2");
   AFB_LowMass_ZY.at(i) = (TH2D *)file->Get("AFB_LowMass1_ZY");

   AFB_LowMass_ZY1.at(i) = ((TH2D *)file->Get("AFB_LowMass1_ZY"))->ProjectionX((TString)"AFB_LowMass1_ZY1_PDF" + (int)i, 1, 1);
   AFB_LowMass_ZY2.at(i) = ((TH2D *)file->Get("AFB_LowMass1_ZY"))->ProjectionX((TString)"AFB_LowMass1_ZY2_PDF" + (int)i, 2, 2);
   AFB_LowMass_ZY3.at(i) = ((TH2D *)file->Get("AFB_LowMass1_ZY"))->ProjectionX((TString)"AFB_LowMass1_ZY3_PDF" + (int)i, 3, 3);
   AFB_LowMass_ZY4.at(i) = ((TH2D *)file->Get("AFB_LowMass1_ZY"))->ProjectionX((TString)"AFB_LowMass1_ZY4_PDF" + (int)i, 4, 4);
   AFB_LowMass_ZY5.at(i) = ((TH2D *)file->Get("AFB_LowMass1_ZY"))->ProjectionX((TString)"AFB_LowMass1_ZY5_PDF" + (int)i, 5, 5);
 }

 TFile* writefile = new TFile("Correlation.root", "RECREATE");
 writefile->cd();

////////////////////////////////////////////////////////////////////////////
 TH1D* Corr_CC;
 TH1D* Corr_CF;
 DrawCorrelationCosine(AFB_CC, ZHighMass_CC, Corr_CC, "Symmetry");
 DrawCorrelationCosine(AFB_CF, ZHighMass_CF, Corr_CF, "Symmetry");

////////////////////////////////////////////////////////////////////////////
 TH1D* Corr_ZRapidity_CC;
 TH1D* Corr_ZRapidity_CF;
 TH1D* Corr_ZRapidity_CF_Low;

 DrawIntegralCorrelationCosine(ZRapidity_CC, ZHighMass_CF, Corr_ZRapidity_CC, "Symmetry");
 DrawIntegralCorrelationCosine(ZRapidity_CF, ZHighMass_CF, Corr_ZRapidity_CF, "Symmetry");
 DrawIntegralCorrelationCosine(ZRapidity_CF_Low, ZHighMass_CF, Corr_ZRapidity_CF_Low, "Symmetry");

////////////////////////////////////////////////////////////////////////////
 TH1D* Corr_WPlus_CC;
 TH1D* Corr_WMinus_CC;
 TH1D* Corr_Wasymmetry_CC;
 DrawCorrelationCosine(WPlusXsec, ZHighMass_CC, Corr_WPlus_CC, "Symmetry");
 DrawCorrelationCosine(WMinusXsec, ZHighMass_CC, Corr_WMinus_CC, "Symmetry");
 DrawCorrelationCosine(WXsecAsymmetry, ZHighMass_CC, Corr_Wasymmetry_CC, "Symmetry");

 TH1D* Corr_WPlus_CF;
 TH1D* Corr_WMinus_CF;
 TH1D* Corr_Wasymmetry_CF;
 DrawCorrelationCosine(WPlusXsec, ZHighMass_CF, Corr_WPlus_CF, "Symmetry");
 DrawCorrelationCosine(WMinusXsec, ZHighMass_CF, Corr_WMinus_CF, "Symmetry");
 DrawCorrelationCosine(WXsecAsymmetry, ZHighMass_CF, Corr_Wasymmetry_CF, "Symmetry");

////////////////////////////////////////////////////////////////////////////

 vector<vector<TH1D *>> Corr_Xsec_2D_CC;
 vector<vector<TH1D *>> Corr_Xsec_2D_CF;
 vector<vector<TH1D *>> Corr_AFB_Mass_ZY_CC;
 vector<vector<TH1D *>> Corr_AFB_Mass_ZY_CF;

 Draw2DCorrelationCosine(Xsec_2D_CC, ZHighMass_CF, Corr_Xsec_2D_CC, "Symmetry");
 Draw2DCorrelationCosine(Xsec_2D_CF, ZHighMass_CF, Corr_Xsec_2D_CF, "Symmetry");
 Draw2DCorrelationCosine(AFB_Mass_ZY_CC, ZHighMass_CF, Corr_AFB_Mass_ZY_CC, "Symmetry");
 Draw2DCorrelationCosine(AFB_Mass_ZY_CF, ZHighMass_CF, Corr_AFB_Mass_ZY_CF, "Symmetry");

////////////////////////////////////////////////////////////////////////////

// vector<vector<TH1D *>> Corr_AFB_LowMass_ZY;
// Draw2DCorrelationCosine(AFB_LowMass_ZY, AFB_HighMass2, Corr_AFB_LowMass_ZY, "Symmetry");
 TH1D* Corr_AFB_LowMass_ZY1;
 TH1D* Corr_AFB_LowMass_ZY2;
 TH1D* Corr_AFB_LowMass_ZY3;
 TH1D* Corr_AFB_LowMass_ZY4;
 TH1D* Corr_AFB_LowMass_ZY5;
 DrawCorrelationCosine(AFB_HighMass2, AFB_LowMass_ZY1, Corr_AFB_LowMass_ZY1, "Symmetry");
 DrawCorrelationCosine(AFB_HighMass2, AFB_LowMass_ZY2, Corr_AFB_LowMass_ZY2, "Symmetry");
 DrawCorrelationCosine(AFB_HighMass2, AFB_LowMass_ZY3, Corr_AFB_LowMass_ZY3, "Symmetry");
 DrawCorrelationCosine(AFB_HighMass2, AFB_LowMass_ZY4, Corr_AFB_LowMass_ZY4, "Symmetry", 1, 15);
 DrawCorrelationCosine(AFB_HighMass2, AFB_LowMass_ZY5, Corr_AFB_LowMass_ZY5, "Symmetry", 1, 6);


 PDFReweight* data = new PDFReweight();
 data->LinkFile(writefile);
 data->InitialPDF("CT18NNLO", 0);
/* data->DrawPartonCorrelation(AFB_CC, 2, 58, "Symmetry");
 data->DrawPartonCorrelation(AFB_CC, 1, 58, "Symmetry");
 data->DrawPartonCorrelation(AFB_CC, 33, 58, "Symmetry");
 data->DrawPartonCorrelation(AFB_CC, 34, 58, "Symmetry");
 data->DrawPartonCorrelation(AFB_CF, 2, 58, "Symmetry");
 data->DrawPartonCorrelation(AFB_CF, 1, 58, "Symmetry");
 data->DrawPartonCorrelation(AFB_CF, 33, 58, "Symmetry");
 data->DrawPartonCorrelation(AFB_CF, 34, 58, "Symmetry");
 data->DrawPartonCorrelation(WPlusXsec, 2, 58, "Symmetry");
 data->DrawPartonCorrelation(WPlusXsec, 1, 58, "Symmetry");
 data->DrawPartonCorrelation(WPlusXsec, 33, 58, "Symmetry");
 data->DrawPartonCorrelation(WPlusXsec, 34, 58, "Symmetry");
 data->DrawPartonCorrelation(WPlusXsec, -2, 58, "Symmetry");
 data->DrawPartonCorrelation(WPlusXsec, -1, 58, "Symmetry");
 data->DrawPartonCorrelation(WMinusXsec, 2, 58, "Symmetry");
 data->DrawPartonCorrelation(WMinusXsec, 1, 58, "Symmetry");
 data->DrawPartonCorrelation(WMinusXsec, 33, 58, "Symmetry");
 data->DrawPartonCorrelation(WMinusXsec, 34, 58, "Symmetry");
 data->DrawPartonCorrelation(WMinusXsec, -2, 58, "Symmetry");
 data->DrawPartonCorrelation(WMinusXsec, -1, 58, "Symmetry");
 data->DrawPartonCorrelation(WXsecAsymmetry, 2, 58, "Symmetry");
 data->DrawPartonCorrelation(WXsecAsymmetry, 1, 58, "Symmetry");
 data->DrawPartonCorrelation(WXsecAsymmetry, 33, 58, "Symmetry");
 data->DrawPartonCorrelation(WXsecAsymmetry, 34, 58, "Symmetry");
 data->DrawPartonCorrelation(WXsecAsymmetry, -2, 58, "Symmetry");
 data->DrawPartonCorrelation(WXsecAsymmetry, -1, 58, "Symmetry");
*/
 Corr_CC->Write();
 Corr_CF->Write();

 Corr_ZRapidity_CC->Write();
 Corr_ZRapidity_CF->Write();
 Corr_ZRapidity_CF_Low->Write();

 Corr_WPlus_CC->Write();
 Corr_WMinus_CC->Write();
 Corr_Wasymmetry_CC->Write();

 Corr_WPlus_CF->Write();
 Corr_WMinus_CF->Write();
 Corr_Wasymmetry_CF->Write();

 writefile->Write();
 writefile->Close();

 return 1;
}
