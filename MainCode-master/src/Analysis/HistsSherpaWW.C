#include "Analysis/HistsSherpaWW.h"

using namespace std;

void HistsSherpaWW::bookHists(int TotalThread)
{
 this->TotalThread = TotalThread;

 Eta_bin = 4;  Eta_left = 0.0;  Eta_right = 5.0;
 double Eta_binning[5] = {0.0, 1.0, 2.0, 3.0, 4.0};

 WY_bin = 6;  WY_left = 0.0;  WY_right = 5.0;
 double WY_binning[7] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};

 BookHist(Wrong_uu, "Wrong_uu", "Wrong_uu", Eta_bin, Eta_binning);
 BookHist(Right_uu, "Right_uu", "Right_uu", Eta_bin, Eta_binning);
 BookHist(Total_uu, "Total_uu", "Total_uu", Eta_bin, Eta_binning);

 BookHist(Wrong_dd, "Wrong_dd", "Wrong_dd", Eta_bin, Eta_binning);
 BookHist(Right_dd, "Right_dd", "Right_dd", Eta_bin, Eta_binning);
 BookHist(Total_dd, "Total_dd", "Total_dd", Eta_bin, Eta_binning);

 BookHist(Wrong_ss, "Wrong_ss", "Wrong_ss", Eta_bin, Eta_binning);
 BookHist(Right_ss, "Right_ss", "Right_ss", Eta_bin, Eta_binning);
 BookHist(Total_ss, "Total_ss", "Total_ss", Eta_bin, Eta_binning);

 BookHist(Wrong_cc, "Wrong_cc", "Wrong_cc", Eta_bin, Eta_binning);
 BookHist(Right_cc, "Right_cc", "Right_cc", Eta_bin, Eta_binning);
 BookHist(Total_cc, "Total_cc", "Total_cc", Eta_bin, Eta_binning);

 BookHist(Wrong_bb, "Wrong_bb", "Wrong_bb", Eta_bin, Eta_binning);
 BookHist(Right_bb, "Right_bb", "Right_bb", Eta_bin, Eta_binning);
 BookHist(Total_bb, "Total_bb", "Total_bb", Eta_bin, Eta_binning);

 BookHist(Wrong_AllFlavor, "Wrong_AllFlavor", "Wrong_AllFlavor", Eta_bin, Eta_binning);
 BookHist(Right_AllFlavor, "Right_AllFlavor", "Right_AllFlavor", Eta_bin, Eta_binning);
 BookHist(Total_AllFlavor, "Total_AllFlavor", "Total_AllFlavor", Eta_bin, Eta_binning);

 BookHist(WrongW_uu, "WrongW_uu", "WrongW_uu", WY_bin, WY_binning);
 BookHist(RightW_uu, "RightW_uu", "RightW_uu", WY_bin, WY_binning);
 BookHist(TotalW_uu, "TotalW_uu", "TotalW_uu", WY_bin, WY_binning);

 BookHist(WrongW_dd, "WrongW_dd", "WrongW_dd", WY_bin, WY_binning);
 BookHist(RightW_dd, "RightW_dd", "RightW_dd", WY_bin, WY_binning);
 BookHist(TotalW_dd, "TotalW_dd", "TotalW_dd", WY_bin, WY_binning);

 BookHist(WrongW_ss, "WrongW_ss", "WrongW_ss", WY_bin, WY_binning);
 BookHist(RightW_ss, "RightW_ss", "RightW_ss", WY_bin, WY_binning);
 BookHist(TotalW_ss, "TotalW_ss", "TotalW_ss", WY_bin, WY_binning);

 BookHist(WrongW_cc, "WrongW_cc", "WrongW_cc", WY_bin, WY_binning);
 BookHist(RightW_cc, "RightW_cc", "RightW_cc", WY_bin, WY_binning);
 BookHist(TotalW_cc, "TotalW_cc", "TotalW_cc", WY_bin, WY_binning);

 BookHist(WrongW_bb, "WrongW_bb", "WrongW_bb", WY_bin, WY_binning);
 BookHist(RightW_bb, "RightW_bb", "RightW_bb", WY_bin, WY_binning);
 BookHist(TotalW_bb, "TotalW_bb", "TotalW_bb", WY_bin, WY_binning);

 BookHist(WrongW_AllFlavor, "WrongW_AllFlavor", "WrongW_AllFlavor", WY_bin, WY_binning);
 BookHist(RightW_AllFlavor, "RightW_AllFlavor", "RightW_AllFlavor", WY_bin, WY_binning);
 BookHist(TotalW_AllFlavor, "TotalW_AllFlavor", "TotalW_AllFlavor", WY_bin, WY_binning);

 BookHist(LeptonEta, "LeptonEta", "LeptonEta", 10, -5, 5);
 BookHist(AntiLeptonEta, "AntiLeptonEta", "AntiLeptonEta", 10, -5, 5);

 BookHist(WPlusRapidity, "WPlusRapidity", "WPlusRapdity", 10, -5, 5);
 BookHist(WMinusRapidity, "WMinusRapidity", "WMinusRapdity", 10, -5, 5);

 BookHist(WWMass, "WWMass", "WWMass", 100, 0, 1000);
 BookHist(WWMass_uu, "WWMass_uu", "WWMass_uu", 100, 0, 1000);
 BookHist(WWMass_dd, "WWMass_dd", "WWMass_dd", 100, 0, 1000);

 BookHist(EtaDiff_uu, "EtaDiff_uu", "EtaDiff_uu", 4, 0, 4);
 BookHist(EtaDiff_dd, "EtaDiff_dd", "EtaDiff_dd", 4, 0, 4);

 BookHist(CosThetaPlusDiff, "CosThetaPlusDiff", "CosThetaPlusDiff", 20, -1, 1);
 BookHist(CosThetaMinusDiff, "CosThetaMinusDiff", "CosThetaMinusDiff", 20, -1, 1);

}

void HistsSherpaWW::outputInformation()
{
 Ratio_uu = (TH1D *)Right_uu->at(0)->Clone("Ratio_uu");
 Ratio_uu->Divide(Wrong_uu->at(0));

 Ratio_dd = (TH1D *)Right_dd->at(0)->Clone("Ratio_dd");
 Ratio_dd->Divide(Wrong_dd->at(0));

 Ratio_ss = (TH1D *)Right_ss->at(0)->Clone("Ratio_ss");
 Ratio_ss->Divide(Wrong_ss->at(0));

 Ratio_cc = (TH1D *)Right_cc->at(0)->Clone("Ratio_cc");
 Ratio_cc->Divide(Wrong_cc->at(0));

 Ratio_bb = (TH1D *)Right_bb->at(0)->Clone("Ratio_bb");
 Ratio_bb->Divide(Wrong_bb->at(0));

 Ratio_AllFlavor = (TH1D *)Right_AllFlavor->at(0)->Clone("Ratio_AllFlavor");
 Ratio_AllFlavor->Divide(Wrong_AllFlavor->at(0));

 RatioW_uu = (TH1D *)RightW_uu->at(0)->Clone("RatioW_uu");
 RatioW_uu->Divide(WrongW_uu->at(0));

 RatioW_dd = (TH1D *)RightW_dd->at(0)->Clone("RatioW_dd");
 RatioW_dd->Divide(WrongW_dd->at(0));

 RatioW_ss = (TH1D *)RightW_ss->at(0)->Clone("RatioW_ss");
 RatioW_ss->Divide(WrongW_ss->at(0));

 RatioW_cc = (TH1D *)RightW_cc->at(0)->Clone("RatioW_cc");
 RatioW_cc->Divide(WrongW_cc->at(0));

 RatioW_bb = (TH1D *)RightW_bb->at(0)->Clone("RatioW_bb");
 RatioW_bb->Divide(WrongW_bb->at(0));

 RatioW_AllFlavor = (TH1D *)RightW_AllFlavor->at(0)->Clone("RatioW_AllFlavor");
 RatioW_AllFlavor->Divide(WrongW_AllFlavor->at(0));

 cout<<endl;
 cout<<"Lepton case: "<<endl;
 cout<<endl;

 cout<<"Ratio uu:"<<endl;
 for(int ibin = 1; ibin <= Ratio_uu->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<Ratio_uu->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<Ratio_uu->GetBinError(ibin)<<"  ";
 }
 double OverallRight_uu = Right_uu->at(0)->Integral();
 double OverallWrong_uu = Wrong_uu->at(0)->Integral();
 double OverallRight_uu_error = 0.0;
 double OverallWrong_uu_error = 0.0;
 Right_uu->at(0)->IntegralAndError(1, Right_uu->at(0)->GetNbinsX(), OverallRight_uu_error);
 Wrong_uu->at(0)->IntegralAndError(1, Wrong_uu->at(0)->GetNbinsX(), OverallWrong_uu_error);
 double Overall_uu = OverallRight_uu / OverallWrong_uu;
 double Overall_uu_error = sqrt(OverallWrong_uu * OverallWrong_uu * OverallRight_uu_error * OverallRight_uu_error + OverallRight_uu * OverallRight_uu * OverallWrong_uu_error * OverallWrong_uu_error) / (OverallWrong_uu * OverallWrong_uu);
 cout<<"Overall: "<<fixed<<setprecision(3)<<Overall_uu<<" +- "<<Overall_uu_error<<endl;
 cout<<endl;

 cout<<"Ratio dd:"<<endl;
 for(int ibin = 1; ibin <= Ratio_dd->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<Ratio_dd->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<Ratio_dd->GetBinError(ibin)<<"  ";
 }
 double OverallRight_dd = Right_dd->at(0)->Integral();
 double OverallWrong_dd = Wrong_dd->at(0)->Integral();
 double OverallRight_dd_error = 0.0;
 double OverallWrong_dd_error = 0.0;
 Right_dd->at(0)->IntegralAndError(1, Right_dd->at(0)->GetNbinsX(), OverallRight_dd_error);
 Wrong_dd->at(0)->IntegralAndError(1, Wrong_dd->at(0)->GetNbinsX(), OverallWrong_dd_error);
 double Overall_dd = OverallRight_dd / OverallWrong_dd;
 double Overall_dd_error = sqrt(OverallWrong_dd * OverallWrong_dd * OverallRight_dd_error * OverallRight_dd_error + OverallRight_dd * OverallRight_dd * OverallWrong_dd_error * OverallWrong_dd_error) / (OverallWrong_dd * OverallWrong_dd);
 cout<<"Overall: "<<fixed<<setprecision(3)<<Overall_dd<<" +- "<<Overall_dd_error<<endl;
 cout<<endl;

 cout<<"Ratio ss:"<<endl;
 for(int ibin = 1; ibin <= Ratio_ss->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<Ratio_ss->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<Ratio_ss->GetBinError(ibin)<<"  ";
 }
 double OverallRight_ss = Right_ss->at(0)->Integral();
 double OverallWrong_ss = Wrong_ss->at(0)->Integral();
 double OverallRight_ss_error = 0.0;
 double OverallWrong_ss_error = 0.0;
 Right_ss->at(0)->IntegralAndError(1, Right_ss->at(0)->GetNbinsX(), OverallRight_ss_error);
 Wrong_ss->at(0)->IntegralAndError(1, Wrong_ss->at(0)->GetNbinsX(), OverallWrong_ss_error);
 double Overall_ss = OverallRight_ss / OverallWrong_ss;
 double Overall_ss_error = sqrt(OverallWrong_ss * OverallWrong_ss * OverallRight_ss_error * OverallRight_ss_error + OverallRight_ss * OverallRight_ss * OverallWrong_ss_error * OverallWrong_ss_error) / (OverallWrong_ss * OverallWrong_ss);
 cout<<"Overall: "<<fixed<<setprecision(3)<<Overall_ss<<" +- "<<Overall_ss_error<<endl;
 cout<<endl;

 cout<<"Ratio cc:"<<endl;
 for(int ibin = 1; ibin <= Ratio_cc->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<Ratio_cc->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<Ratio_cc->GetBinError(ibin)<<"  ";
 }
 double OverallRight_cc = Right_cc->at(0)->Integral();
 double OverallWrong_cc = Wrong_cc->at(0)->Integral();
 double OverallRight_cc_error = 0.0;
 double OverallWrong_cc_error = 0.0;
 Right_cc->at(0)->IntegralAndError(1, Right_cc->at(0)->GetNbinsX(), OverallRight_cc_error);
 Wrong_cc->at(0)->IntegralAndError(1, Wrong_cc->at(0)->GetNbinsX(), OverallWrong_cc_error);
 double Overall_cc = OverallRight_cc / OverallWrong_cc;
 double Overall_cc_error = sqrt(OverallWrong_cc * OverallWrong_cc * OverallRight_cc_error * OverallRight_cc_error + OverallRight_cc * OverallRight_cc * OverallWrong_cc_error * OverallWrong_cc_error) / (OverallWrong_cc * OverallWrong_cc);
 cout<<"Overall: "<<fixed<<setprecision(3)<<Overall_cc<<" +- "<<Overall_cc_error<<endl;
 cout<<endl;

 cout<<"Ratio bb:"<<endl;
 for(int ibin = 1; ibin <= Ratio_bb->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<Ratio_bb->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<Ratio_bb->GetBinError(ibin)<<"  ";
 }
 double OverallRight_bb = Right_bb->at(0)->Integral();
 double OverallWrong_bb = Wrong_bb->at(0)->Integral();
 double OverallRight_bb_error = 0.0;
 double OverallWrong_bb_error = 0.0;
 Right_bb->at(0)->IntegralAndError(1, Right_bb->at(0)->GetNbinsX(), OverallRight_bb_error);
 Wrong_bb->at(0)->IntegralAndError(1, Wrong_bb->at(0)->GetNbinsX(), OverallWrong_bb_error);
 double Overall_bb = OverallRight_bb / OverallWrong_bb;
 double Overall_bb_error = sqrt(OverallWrong_bb * OverallWrong_bb * OverallRight_bb_error * OverallRight_bb_error + OverallRight_bb * OverallRight_bb * OverallWrong_bb_error * OverallWrong_bb_error) / (OverallWrong_bb * OverallWrong_bb);
 cout<<"Overall: "<<fixed<<setprecision(3)<<Overall_bb<<" +- "<<Overall_bb_error<<endl;
 cout<<endl;

 cout<<"Ratio All Flavor:"<<endl;
 for(int ibin = 1; ibin <= Ratio_AllFlavor->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<Ratio_AllFlavor->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<Ratio_AllFlavor->GetBinError(ibin)<<"  ";
 }
 double OverallRight_AllFlavor = Right_AllFlavor->at(0)->Integral();
 double OverallWrong_AllFlavor = Wrong_AllFlavor->at(0)->Integral();
 double OverallRight_AllFlavor_error = 0.0;
 double OverallWrong_AllFlavor_error = 0.0;
 Right_AllFlavor->at(0)->IntegralAndError(1, Right_AllFlavor->at(0)->GetNbinsX(), OverallRight_AllFlavor_error);
 Wrong_AllFlavor->at(0)->IntegralAndError(1, Wrong_AllFlavor->at(0)->GetNbinsX(), OverallWrong_AllFlavor_error);
 double Overall_AllFlavor = OverallRight_AllFlavor / OverallWrong_AllFlavor;
 double Overall_AllFlavor_error = sqrt(OverallWrong_AllFlavor * OverallWrong_AllFlavor * OverallRight_AllFlavor_error * OverallRight_AllFlavor_error + OverallRight_AllFlavor * OverallRight_AllFlavor * OverallWrong_AllFlavor_error * OverallWrong_AllFlavor_error) / (OverallWrong_AllFlavor * OverallWrong_AllFlavor);
 cout<<"Overall: "<<fixed<<setprecision(3)<<Overall_AllFlavor<<" +- "<<Overall_AllFlavor_error<<endl;
 cout<<endl;

 Ratio_AllFlavor_Overall = new TH1D("Ratio_AllFlavor_Overall", "Ratio_AllFlavor_Overall", 1, 0, 1);
 Ratio_AllFlavor_Overall->SetBinContent(1, Overall_AllFlavor);
 Ratio_AllFlavor_Overall->SetBinError(1, Overall_AllFlavor_error);


 cout<<"WRapidity case: "<<endl;
 cout<<endl;

 cout<<"RatioW uu:"<<endl;
 for(int ibin = 1; ibin <= RatioW_uu->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<RatioW_uu->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<RatioW_uu->GetBinError(ibin)<<"  ";
 }
 double OverallRightW_uu = RightW_uu->at(0)->Integral();
 double OverallWrongW_uu = WrongW_uu->at(0)->Integral();
 double OverallRightW_uu_error = 0.0;
 double OverallWrongW_uu_error = 0.0;
 RightW_uu->at(0)->IntegralAndError(1, RightW_uu->at(0)->GetNbinsX(), OverallRightW_uu_error);
 WrongW_uu->at(0)->IntegralAndError(1, WrongW_uu->at(0)->GetNbinsX(), OverallWrongW_uu_error);
 double OverallW_uu = OverallRightW_uu / OverallWrongW_uu;
 double OverallW_uu_error = sqrt(OverallWrongW_uu * OverallWrongW_uu * OverallRightW_uu_error * OverallRightW_uu_error + OverallRightW_uu * OverallRightW_uu * OverallWrongW_uu_error * OverallWrongW_uu_error) / (OverallWrongW_uu * OverallWrongW_uu);
 cout<<"Overall: "<<fixed<<setprecision(3)<<OverallW_uu<<" +- "<<OverallW_uu_error<<endl;
 cout<<endl;

 cout<<"RatioW dd:"<<endl;
 for(int ibin = 1; ibin <= RatioW_dd->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<RatioW_dd->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<RatioW_dd->GetBinError(ibin)<<"  ";
 }
 double OverallRightW_dd = RightW_dd->at(0)->Integral();
 double OverallWrongW_dd = WrongW_dd->at(0)->Integral();
 double OverallRightW_dd_error = 0.0;
 double OverallWrongW_dd_error = 0.0;
 RightW_dd->at(0)->IntegralAndError(1, RightW_dd->at(0)->GetNbinsX(), OverallRightW_dd_error);
 WrongW_dd->at(0)->IntegralAndError(1, WrongW_dd->at(0)->GetNbinsX(), OverallWrongW_dd_error);
 double OverallW_dd = OverallRightW_dd / OverallWrongW_dd;
 double OverallW_dd_error = sqrt(OverallWrongW_dd * OverallWrongW_dd * OverallRightW_dd_error * OverallRightW_dd_error + OverallRightW_dd * OverallRightW_dd * OverallWrongW_dd_error * OverallWrongW_dd_error) / (OverallWrongW_dd * OverallWrongW_dd);
 cout<<"Overall: "<<fixed<<setprecision(3)<<OverallW_dd<<" +- "<<OverallW_dd_error<<endl;
 cout<<endl;

 cout<<"RatioW ss:"<<endl;
 for(int ibin = 1; ibin <= RatioW_ss->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<RatioW_ss->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<RatioW_ss->GetBinError(ibin)<<"  ";
 }
 double OverallRightW_ss = RightW_ss->at(0)->Integral();
 double OverallWrongW_ss = WrongW_ss->at(0)->Integral();
 double OverallRightW_ss_error = 0.0;
 double OverallWrongW_ss_error = 0.0;
 RightW_ss->at(0)->IntegralAndError(1, RightW_ss->at(0)->GetNbinsX(), OverallRightW_ss_error);
 WrongW_ss->at(0)->IntegralAndError(1, WrongW_ss->at(0)->GetNbinsX(), OverallWrongW_ss_error);
 double OverallW_ss = OverallRightW_ss / OverallWrongW_ss;
 double OverallW_ss_error = sqrt(OverallWrongW_ss * OverallWrongW_ss * OverallRightW_ss_error * OverallRightW_ss_error + OverallRightW_ss * OverallRightW_ss * OverallWrongW_ss_error * OverallWrongW_ss_error) / (OverallWrongW_ss * OverallWrongW_ss);
 cout<<"Overall: "<<fixed<<setprecision(3)<<OverallW_ss<<" +- "<<OverallW_ss_error<<endl;
 cout<<endl;

 cout<<"RatioW cc:"<<endl;
 for(int ibin = 1; ibin <= RatioW_cc->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<RatioW_cc->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<RatioW_cc->GetBinError(ibin)<<"  ";
 }
 double OverallRightW_cc = RightW_cc->at(0)->Integral();
 double OverallWrongW_cc = WrongW_cc->at(0)->Integral();
 double OverallRightW_cc_error = 0.0;
 double OverallWrongW_cc_error = 0.0;
 RightW_cc->at(0)->IntegralAndError(1, RightW_cc->at(0)->GetNbinsX(), OverallRightW_cc_error);
 WrongW_cc->at(0)->IntegralAndError(1, WrongW_cc->at(0)->GetNbinsX(), OverallWrongW_cc_error);
 double OverallW_cc = OverallRightW_cc / OverallWrongW_cc;
 double OverallW_cc_error = sqrt(OverallWrongW_cc * OverallWrongW_cc * OverallRightW_cc_error * OverallRightW_cc_error + OverallRightW_cc * OverallRightW_cc * OverallWrongW_cc_error * OverallWrongW_cc_error) / (OverallWrongW_cc * OverallWrongW_cc);
 cout<<"Overall: "<<fixed<<setprecision(3)<<OverallW_cc<<" +- "<<OverallW_cc_error<<endl;
 cout<<endl;

 cout<<"RatioW bb:"<<endl;
 for(int ibin = 1; ibin <= RatioW_bb->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<RatioW_bb->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<RatioW_bb->GetBinError(ibin)<<"  ";
 }
 double OverallRightW_bb = RightW_bb->at(0)->Integral();
 double OverallWrongW_bb = WrongW_bb->at(0)->Integral();
 double OverallRightW_bb_error = 0.0;
 double OverallWrongW_bb_error = 0.0;
 RightW_bb->at(0)->IntegralAndError(1, RightW_bb->at(0)->GetNbinsX(), OverallRightW_bb_error);
 WrongW_bb->at(0)->IntegralAndError(1, WrongW_bb->at(0)->GetNbinsX(), OverallWrongW_bb_error);
 double OverallW_bb = OverallRightW_bb / OverallWrongW_bb;
 double OverallW_bb_error = sqrt(OverallWrongW_bb * OverallWrongW_bb * OverallRightW_bb_error * OverallRightW_bb_error + OverallRightW_bb * OverallRightW_bb * OverallWrongW_bb_error * OverallWrongW_bb_error) / (OverallWrongW_bb * OverallWrongW_bb);
 cout<<"Overall: "<<fixed<<setprecision(3)<<OverallW_bb<<" +- "<<OverallW_bb_error<<endl;
 cout<<endl;

 cout<<"RatioW All Flavor:"<<endl;
 for(int ibin = 1; ibin <= RatioW_AllFlavor->GetNbinsX(); ibin++){
   cout<<fixed<<setprecision(3)<<RatioW_AllFlavor->GetBinContent(ibin);
   cout<<" +- ";
   cout<<fixed<<setprecision(3)<<RatioW_AllFlavor->GetBinError(ibin)<<"  ";
 }
 double OverallRightW_AllFlavor = RightW_AllFlavor->at(0)->Integral();
 double OverallWrongW_AllFlavor = WrongW_AllFlavor->at(0)->Integral();
 double OverallRightW_AllFlavor_error = 0.0;
 double OverallWrongW_AllFlavor_error = 0.0;
 RightW_AllFlavor->at(0)->IntegralAndError(1, RightW_AllFlavor->at(0)->GetNbinsX(), OverallRightW_AllFlavor_error);
 WrongW_AllFlavor->at(0)->IntegralAndError(1, WrongW_AllFlavor->at(0)->GetNbinsX(), OverallWrongW_AllFlavor_error);
 double OverallW_AllFlavor = OverallRightW_AllFlavor / OverallWrongW_AllFlavor;
 double OverallW_AllFlavor_error = sqrt(OverallWrongW_AllFlavor * OverallWrongW_AllFlavor * OverallRightW_AllFlavor_error * OverallRightW_AllFlavor_error + OverallRightW_AllFlavor * OverallRightW_AllFlavor * OverallWrongW_AllFlavor_error * OverallWrongW_AllFlavor_error) / (OverallWrongW_AllFlavor * OverallWrongW_AllFlavor);
 cout<<"Overall: "<<fixed<<setprecision(3)<<OverallW_AllFlavor<<" +- "<<OverallW_AllFlavor_error<<endl;
 cout<<endl;

 RatioW_AllFlavor_Overall = new TH1D("RatioW_AllFlavor_Overall", "RatioW_AllFlavor_Overall", 1, 0, 1);
 RatioW_AllFlavor_Overall->SetBinContent(1, OverallW_AllFlavor);
 RatioW_AllFlavor_Overall->SetBinError(1, OverallW_AllFlavor_error);


 Ratio_uu->Write();
 Ratio_dd->Write();
 Ratio_ss->Write();
 Ratio_cc->Write();
 Ratio_bb->Write();
 Ratio_AllFlavor->Write();
 Ratio_AllFlavor_Overall->Write();

 RatioW_uu->Write();
 RatioW_dd->Write();
 RatioW_ss->Write();
 RatioW_cc->Write();
 RatioW_bb->Write();
 RatioW_AllFlavor->Write();
 RatioW_AllFlavor_Overall->Write();

 BoostAsymmetry_uu = (TH1D *)Right_uu->at(0)->Clone("BoostAsymmetry_uu");
 BoostAsymmetry_uu->Reset();
 AFBFunction(Right_uu->at(0), Wrong_uu->at(0), BoostAsymmetry_uu);

 BoostAsymmetry_dd = (TH1D *)Right_dd->at(0)->Clone("BoostAsymmetry_dd");
 BoostAsymmetry_dd->Reset();
 AFBFunction(Right_dd->at(0), Wrong_dd->at(0), BoostAsymmetry_dd);

 BoostAsymmetry_ss = (TH1D *)Right_ss->at(0)->Clone("BoostAsymmetry_ss");
 BoostAsymmetry_ss->Reset();
 AFBFunction(Right_ss->at(0), Wrong_ss->at(0), BoostAsymmetry_ss);

 BoostAsymmetry_cc = (TH1D *)Right_cc->at(0)->Clone("BoostAsymmetry_cc");
 BoostAsymmetry_cc->Reset();
 AFBFunction(Right_cc->at(0), Wrong_cc->at(0), BoostAsymmetry_cc);

 BoostAsymmetry_bb = (TH1D *)Right_bb->at(0)->Clone("BoostAsymmetry_bb");
 BoostAsymmetry_bb->Reset();
 AFBFunction(Right_bb->at(0), Wrong_bb->at(0), BoostAsymmetry_bb);

 BoostAsymmetry_AllFlavor = (TH1D *)Right_AllFlavor->at(0)->Clone("BoostAsymmetry_AllFlavor");
 BoostAsymmetry_AllFlavor->Reset();
 AFBFunction(Right_AllFlavor->at(0), Wrong_AllFlavor->at(0), BoostAsymmetry_AllFlavor);

 BoostAsymmetryW_uu = (TH1D *)RightW_uu->at(0)->Clone("BoostAsymmetryW_uu");
 BoostAsymmetryW_uu->Reset();
 AFBFunction(RightW_uu->at(0), WrongW_uu->at(0), BoostAsymmetryW_uu);

 BoostAsymmetryW_dd = (TH1D *)RightW_dd->at(0)->Clone("BoostAsymmetryW_dd");
 BoostAsymmetryW_dd->Reset();
 AFBFunction(RightW_dd->at(0), WrongW_dd->at(0), BoostAsymmetryW_dd);

 BoostAsymmetryW_ss = (TH1D *)RightW_ss->at(0)->Clone("BoostAsymmetryW_ss");
 BoostAsymmetryW_ss->Reset();
 AFBFunction(RightW_ss->at(0), WrongW_ss->at(0), BoostAsymmetryW_ss);
 
 BoostAsymmetryW_cc = (TH1D *)RightW_cc->at(0)->Clone("BoostAsymmetryW_cc");
 BoostAsymmetryW_cc->Reset();
 AFBFunction(RightW_cc->at(0), WrongW_cc->at(0), BoostAsymmetryW_cc);

 BoostAsymmetryW_bb = (TH1D *)RightW_bb->at(0)->Clone("BoostAsymmetryW_bb");
 BoostAsymmetryW_bb->Reset();
 AFBFunction(RightW_bb->at(0), WrongW_bb->at(0), BoostAsymmetryW_bb);

 BoostAsymmetryW_AllFlavor = (TH1D *)RightW_AllFlavor->at(0)->Clone("BoostAsymmetryW_AllFlavor");
 BoostAsymmetryW_AllFlavor->Reset();
 AFBFunction(RightW_AllFlavor->at(0), WrongW_AllFlavor->at(0), BoostAsymmetryW_AllFlavor);

 BoostAsymmetry_uu->Write();
 BoostAsymmetry_dd->Write();
 BoostAsymmetry_ss->Write();
 BoostAsymmetry_cc->Write();
 BoostAsymmetry_bb->Write();
 BoostAsymmetry_AllFlavor->Write();
 BoostAsymmetryW_uu->Write();
 BoostAsymmetryW_dd->Write();
 BoostAsymmetryW_ss->Write();
 BoostAsymmetryW_cc->Write();
 BoostAsymmetryW_bb->Write();
 BoostAsymmetryW_AllFlavor->Write();

 cout<<"AntiLeptonEta width: "<<AntiLeptonEta->at(0)->GetRMS()<<endl;
 cout<<"LeptonEta width: "<<LeptonEta->at(0)->GetRMS()<<endl;
 cout<<"WPlusRapidity width: "<<WPlusRapidity->at(0)->GetRMS()<<endl;
 cout<<"WMinusRapidity width: "<<WMinusRapidity->at(0)->GetRMS()<<endl;
 cout<<endl;


}

void HistsSherpaWW::InitialSysName()
{

}
