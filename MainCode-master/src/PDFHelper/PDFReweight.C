#ifndef PDFHelper_PDFReweight_cxx
#define PDFHelper_PDFReweight_cxx

#include "PDFHelper/PDFReweight.h"

//using namespace LHAPDF;

//extern pthread_mutex_t LHAPDFmtx;
//pthread_mutex_t LHAPDFmtx = PTHREAD_MUTEX_INITIALIZER;

PDFReweight::PDFReweight()
{
 EW = new ZWidthDep();
// EW = new ResBosEW();

 if(ncall != -1){
   step = -1.0;
   ResetIntegral();
   //InitialPartonName();
   return;
 }
 if(step < 0){
   ncall = -1;
   ResetIntegral();
   //InitialPartonName();
   return;
 }

}


 ///////////////////
 ////  1D Plot  ////
 ///////////////////

void PDFReweight::DrawZY(int bin, double left, double right, int iflag, TString Process)
{
 iZY++;

 TString HistName;
 if(iflag == 0) HistName = "ZYAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "ZYUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "ZYDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 ZYPlot[iZY] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= ZYPlot[iZY]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;
   if(Process == "Integral"){
     double BinLeft = ZYPlot[iZY]->GetXaxis()->GetBinLowEdge(ibin);
     double BinRight = ZYPlot[iZY]->GetXaxis()->GetBinUpEdge(ibin);

     if(iflag == 0){//directly total
       Value = GetMassZYCrossSection(60.0, 130.0, BinLeft, BinRight, 0, (TString)"");
       Error = sqrt(Value) * ErrorLevel;
     }
     if(iflag == 1){//directly uubar
       Value = GetMassZYCrossSection(60.0, 130.0, BinLeft, BinRight, 1, (TString)"");
       Error = sqrt(Value) * ErrorLevel;
     }
     if(iflag == 2){//directly ddbar
       Value = GetMassZYCrossSection(60.0, 130.0, BinLeft, BinRight, 2, (TString)"");
       Error = sqrt(Value) * ErrorLevel;
     }
   }
   if(Process == "NoIntegral"){
     double BinCenter = ZYPlot[iZY]->GetBinCenter(ibin);

     if(iflag == 0){
       Value = GetZYCrossSection(BinCenter, 60.0, 130.0, 0, (TString)"");
       Error = sqrt(Value) * ErrorLevel;
     }
     if(iflag == 1){
       Value = GetZYCrossSection(BinCenter, 60.0, 130.0, 1, (TString)"");
       Error = sqrt(Value) * ErrorLevel;
     }
     if(iflag == 2){
       Value = GetZYCrossSection(BinCenter, 60.0, 130.0, 2, (TString)"");
       Error = sqrt(Value) * ErrorLevel;
     }
   }

   ZYPlot[iZY]->SetBinContent(ibin, Value);
   ZYPlot[iZY]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void PDFReweight::DrawMass(int bin, double left, double right, int iflag, TString Process)
{
 iMass++;

 TString HistName;
 if(iflag == 0) HistName = "ZMassAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "ZMassUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "ZMassDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "ZMassGluon_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 4) HistName = "ZMassUpType_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 5) HistName = "ZMassDownType_" + PDFName + "_" + (int)iSet + "_" + Process;
 MassPlot[iMass] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= MassPlot[iMass]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;
   if(Process == "Integral"){
     double BinLeft = MassPlot[iMass]->GetXaxis()->GetBinLowEdge(ibin);
     double BinRight = MassPlot[iMass]->GetXaxis()->GetBinUpEdge(ibin);

     Value = GetMassZYCrossSection(BinLeft, BinRight, log(BinLeft / ECM), log(ECM / BinLeft), iflag, (TString)"");
     Error = sqrt(Value) * ErrorLevel;
   }
   if(Process == "NoIntegral"){
     double BinCenter = MassPlot[iMass]->GetBinCenter(ibin);

     Value = HadronCrossSection(BinCenter, iflag, (TString)"");
     Error = sqrt(Value) * ErrorLevel;
   }

   MassPlot[iMass]->SetBinContent(ibin, Value);
   MassPlot[iMass]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void PDFReweight::DrawDilutionZY(int bin, double left, double right, int iflag, TString Process)
{
 iDilutionZY++;

 TString HistName;
 if(iflag == 0) HistName = "DilutionZYAll_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionZY;
 if(iflag == 1) HistName = "DilutionZYUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionZY;
 if(iflag == 2) HistName = "DilutionZYDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionZY;
 if(iflag == 3) HistName = "DilutionZYGluon_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionZY;
 if(iflag == 4) HistName = "DilutionZYUpType_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionZY;
 if(iflag == 5) HistName = "DilutionZYDownType_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionZY;
 DilutionZYPlot[iDilutionZY] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= DilutionZYPlot[iDilutionZY]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;
   if(Process == "Integral"){
     double BinLeft = DilutionZYPlot[iDilutionZY]->GetXaxis()->GetBinLowEdge(ibin);
     double BinRight = DilutionZYPlot[iDilutionZY]->GetXaxis()->GetBinUpEdge(ibin);

     double Wrong = GetMassZYCrossSectionWrong(60.0, 130.0, BinLeft, BinRight, iflag, (TString)"");
     double Total = GetMassZYCrossSection(60.0, 130.0, BinLeft, BinRight, iflag, (TString)"");
     double Right = Total - Wrong;
     double WrongError = sqrt(Wrong) * ErrorLevel;
     double RightError = sqrt(Right) * ErrorLevel;

     Value = Wrong / Total;
     Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
   }
   if(Process == "NoIntegral"){
     double BinCenter = DilutionZYPlot[iDilutionZY]->GetXaxis()->GetBinCenter(ibin);

     double Wrong = GetZYCrossSectionWrong(BinCenter, 60.0, 130.0, iflag, (TString)"");
     double Total = GetZYCrossSection(BinCenter, 60.0, 130.0, iflag, (TString)"");
     double Right = Total - Wrong;
     double WrongError = sqrt(Wrong) * ErrorLevel;
     double RightError = sqrt(Right) * ErrorLevel;

     Value = Wrong / Total;
     Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
   }

   DilutionZYPlot[iDilutionZY]->SetBinContent(ibin, Value);
   DilutionZYPlot[iDilutionZY]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void PDFReweight::DrawDilutionMass(int bin, double left, double right, int iflag, TString Process)
{
 iDilutionMass++;

 TString HistName;
 if(iflag == 0) HistName = "DilutionMassAll_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionMass;
 if(iflag == 1) HistName = "DilutionMassUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionMass;
 if(iflag == 2) HistName = "DilutionMassDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionMass;
 if(iflag == 3) HistName = "DilutionMassAllAverage_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionMass;
 if(iflag == 4) HistName = "DilutionMassUpQuarkAverage_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionMass;
 if(iflag == 5) HistName = "DilutionMassDownQuarkAverage_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionMass;
 if(iflag == 6) HistName = "DilutionDiffMassAverage_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iDilutionMass;
 DilutionMassPlot[iDilutionMass] = new TH1D(HistName, HistName, bin, left, right);
 
 for(int ibin = 1; ibin <= DilutionMassPlot[iDilutionMass]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;
   if(Process == "Integral"){
     double BinLeft = DilutionMassPlot[iDilutionMass]->GetXaxis()->GetBinLowEdge(ibin);
     double BinRight = DilutionMassPlot[iDilutionMass]->GetXaxis()->GetBinUpEdge(ibin);

     if(iflag == 0){//directly total
       double Wrong = CfCfIntegral(BinLeft, BinRight, 2, "Wrong") + CfCfIntegral(BinLeft, BinRight, 1, "Wrong") + CfCfIntegral(BinLeft, BinRight, 3, "Wrong")
                   + CfCfIntegral(BinLeft, BinRight, 4, "Wrong") + CfCfIntegral(BinLeft, BinRight, 5, "Wrong") + CfCfIntegral(BinLeft, BinRight, -2, "Wrong")
                   + CfCfIntegral(BinLeft, BinRight, -1, "Wrong") + CfCfIntegral(BinLeft, BinRight, -3, "Wrong") + CfCfIntegral(BinLeft, BinRight, -4, "Wrong")
                   + CfCfIntegral(BinLeft, BinRight, -5, "Wrong");
       double Total = CfCfIntegral(BinLeft, BinRight, 2, "") + CfCfIntegral(BinLeft, BinRight, 1, "") + CfCfIntegral(BinLeft, BinRight, 3, "")
                   + CfCfIntegral(BinLeft, BinRight, 4, "") + CfCfIntegral(BinLeft, BinRight, 5, "") + CfCfIntegral(BinLeft, BinRight, -2, "")
                   + CfCfIntegral(BinLeft, BinRight, -1, "") + CfCfIntegral(BinLeft, BinRight, -3, "") + CfCfIntegral(BinLeft, BinRight, -4, "")
                   + CfCfIntegral(BinLeft, BinRight, -5, "");
       double Right = Total - Wrong;
       double WrongError = sqrt(Wrong) * ErrorLevel;
       double RightError = sqrt(Right) * ErrorLevel;

       Value = Wrong / Total;
       Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
     }
     if(iflag == 1){//directly uubar
       double Wrong = CfCfIntegral(BinLeft, BinRight, 2, "Wrong") + CfCfIntegral(BinLeft, BinRight, -2, "Wrong");
       double Total = CfCfIntegral(BinLeft, BinRight, 2, "") + CfCfIntegral(BinLeft, BinRight, -2, "");
       double Right = Total - Wrong;
       double WrongError = sqrt(Wrong) * ErrorLevel;
       double RightError = sqrt(Right) * ErrorLevel;

       Value = Wrong / Total;
       Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
     }
     if(iflag == 2){//directly ddbar
       double Wrong = CfCfIntegral(BinLeft, BinRight, 1, "Wrong") + CfCfIntegral(BinLeft, BinRight, -1, "Wrong");
       double Total = CfCfIntegral(BinLeft, BinRight, 1, "") + CfCfIntegral(BinLeft, BinRight, -1, "");
       double Right = Total - Wrong;
       double WrongError = sqrt(Wrong) * ErrorLevel;
       double RightError = sqrt(Right) * ErrorLevel;

       Value = Wrong / Total;
       Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
     }
     if(iflag == 3){//hadron cross section average total
       double Wrong = GetHadronWrongCrossSection(BinLeft, BinRight, 0);
       double Total = GetHadronTotalCrossSection(BinLeft, BinRight, 0);
       double Right = Total - Wrong;
       double WrongError = sqrt(Wrong) * ErrorLevel;
       double RightError = sqrt(Right) * ErrorLevel;

       Value = Wrong / Total;
       Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
     }
     if(iflag == 4){//hadron cross section average uubar
       double Wrong = GetHadronWrongCrossSection(BinLeft, BinRight, 1);
       double Total = GetHadronTotalCrossSection(BinLeft, BinRight, 1);
       double Right = Total - Wrong;
       double WrongError = sqrt(Wrong) * ErrorLevel;
       double RightError = sqrt(Right) * ErrorLevel;

       Value = Wrong / Total;
       Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
     }
     if(iflag == 5){//hadron cross section average ddbar
       double Wrong = GetHadronWrongCrossSection(BinLeft, BinRight, 2);
       double Total = GetHadronTotalCrossSection(BinLeft, BinRight, 2);
       double Right = Total - Wrong;
       double WrongError = sqrt(Wrong) * ErrorLevel;
       double RightError = sqrt(Right) * ErrorLevel;

       Value = Wrong / Total;
     }
     if(iflag == 6){//hadron cross section average uubar - ddbar
       double Wrong1 = GetHadronWrongCrossSection(BinLeft, BinRight, 1);
       double Total1 = GetHadronTotalCrossSection(BinLeft, BinRight, 1);
       double Right1 = Total1 - Wrong1;
       double Wrong1Error = sqrt(Wrong1) * ErrorLevel;
       double Right1Error = sqrt(Right1) * ErrorLevel;

       double Value1 = Wrong1 / Total1;
       double Error1 = sqrt(Wrong1 * Wrong1 * Right1Error * Right1Error + Right1 * Right1 * Wrong1Error * Wrong1Error) / (Total1 * Total1);

       double Wrong2 = GetHadronWrongCrossSection(BinLeft, BinRight, 2);
       double Total2 = GetHadronTotalCrossSection(BinLeft, BinRight, 2);
       double Right2 = Total2 - Wrong2;
       double Wrong2Error = sqrt(Wrong2) * ErrorLevel;
       double Right2Error = sqrt(Right2) * ErrorLevel;

       double Value2 = Wrong2 / Total2;
       double Error2 = sqrt(Wrong2 * Wrong2 * Right2Error * Right2Error + Right2 * Right2 * Wrong2Error * Wrong2Error) / (Total2 * Total2);

       Value = Value1 - Value2;
       Error = sqrt(Error1 * Error1 + Error2 * Error2);
     }

   }
   if(Process == "NoIntegral"){
     double BinCenter = DilutionMassPlot[iDilutionMass]->GetBinCenter(ibin);

     if(iflag == 0){
       double Wrong = CfCf(BinCenter, 2, "Wrong") + CfCf(BinCenter, 1, "Wrong") + CfCf(BinCenter, 3, "Wrong") + CfCf(BinCenter, 4, "Wrong") + CfCf(BinCenter, 5, "Wrong")
               + CfCf(BinCenter, -2, "Wrong") + CfCf(BinCenter, -1, "Wrong") + CfCf(BinCenter, -3, "Wrong") + CfCf(BinCenter, -4, "Wrong") + CfCf(BinCenter, -5, "Wrong");
       double Total = CfCf(BinCenter, 2, "") + CfCf(BinCenter, 1, "") + CfCf(BinCenter, 3, "") + CfCf(BinCenter, 4, "") + CfCf(BinCenter, 5, "")     
               + CfCf(BinCenter, -2, "") + CfCf(BinCenter, -1, "") + CfCf(BinCenter, -3, "") + CfCf(BinCenter, -4, "") + CfCf(BinCenter, -5, "");
       double Right = Total - Wrong;
       double WrongError = sqrt(Wrong) * ErrorLevel;
       double RightError = sqrt(Right) * ErrorLevel;

       Value = Wrong / Total;
       Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
     }
     if(iflag == 1){
       double Wrong = CfCf(BinCenter, 2, "Wrong") + CfCf(BinCenter, -2, "Wrong");
       double Total = CfCf(BinCenter, 2, "") + CfCf(BinCenter, -2, "");
       double Right = Total - Wrong;
       double WrongError = sqrt(Wrong) * ErrorLevel;
       double RightError = sqrt(Right) * ErrorLevel;

       Value = Wrong / Total;
       Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
     }
     if(iflag == 2){
       double Wrong = CfCf(BinCenter, 1, "Wrong") + CfCf(BinCenter, -1, "Wrong");
       double Total = CfCf(BinCenter, 1, "") + CfCf(BinCenter, -1, "");
       double Right = Total - Wrong;
       double WrongError = sqrt(Wrong) * ErrorLevel;
       double RightError = sqrt(Right) * ErrorLevel;

       Value = Wrong / Total;
       Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
     }
     if(iflag == 3){
       double Wrong = WrongHadronCrossSection(BinCenter, 0);
       double Total = HadronCrossSection(BinCenter, 0);
       double Right = Total - Wrong;
       double WrongError = sqrt(Wrong) * ErrorLevel;
       double RightError = sqrt(Right) * ErrorLevel;

       Value = Wrong / Total;
       Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
     }
     if(iflag == 4){
       double Wrong = WrongHadronCrossSection(BinCenter, 1);
       double Total = HadronCrossSection(BinCenter, 1);
       double Right = Total - Wrong;
       double WrongError = sqrt(Wrong) * ErrorLevel;
       double RightError = sqrt(Right) * ErrorLevel;

       Value = Wrong / Total;
       Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
     }
     if(iflag == 5){
       double Wrong = WrongHadronCrossSection(BinCenter, 2);
       double Total = HadronCrossSection(BinCenter, 2);
       double Right = Total - Wrong;
       double WrongError = sqrt(Wrong) * ErrorLevel;
       double RightError = sqrt(Right) * ErrorLevel;

       Value = Wrong / Total;
       Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
     }
     if(iflag == 6){//hadron cross section average uubar - ddbar
       double Wrong1 = WrongHadronCrossSection(BinCenter, 1);
       double Total1 = HadronCrossSection(BinCenter, 1);
       double Right1 = Total1 - Wrong1;
       double Wrong1Error = sqrt(Wrong1) * ErrorLevel;
       double Right1Error = sqrt(Right1) * ErrorLevel;

       double Value1 = Wrong1 / Total1;
       double Error1 = sqrt(Wrong1 * Wrong1 * Right1Error * Right1Error + Right1 * Right1 * Wrong1Error * Wrong1Error) / (Total1 * Total1);

       double Wrong2 = WrongHadronCrossSection(BinCenter, 2);
       double Total2 = HadronCrossSection(BinCenter, 2);
       double Right2 = Total2 - Wrong2;
       double Wrong2Error = sqrt(Wrong2) * ErrorLevel;
       double Right2Error = sqrt(Right2) * ErrorLevel;

       double Value2 = Wrong2 / Total2;
       double Error2 = sqrt(Wrong2 * Wrong2 * Right2Error * Right2Error + Right2 * Right2 * Wrong2Error * Wrong2Error) / (Total2 * Total2);

       Value = Value1 - Value2;
       Error = sqrt(Error1 * Error1 + Error2 * Error2);
     }

   }
   DilutionMassPlot[iDilutionMass]->SetBinContent(ibin, Value);
   DilutionMassPlot[iDilutionMass]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void PDFReweight::GetAFBDilutionMass(int iplot)
{
 iAFBDilutionMass = iplot;

 AFBDilutionMassPlot[iplot] = (TH1D *)DilutionMassPlot[iplot]->Clone((TString)"AFB" + DilutionMassPlot[iplot]->GetName());
 AFBDilutionMassPlot[iplot]->Reset();

 for(int ibin = 1; ibin <= DilutionMassPlot[iplot]->GetNbinsX(); ibin++){
   double Value = 1 - 2.0 * DilutionMassPlot[iplot]->GetBinContent(ibin);
   double Error = 2.0 * DilutionMassPlot[iplot]->GetBinError(ibin);
   AFBDilutionMassPlot[iplot]->SetBinContent(ibin, Value);
   AFBDilutionMassPlot[iplot]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void PDFReweight::DrawForwardDilutionMass(int bin, double left, double right, int iflag, TString Process)
{
 iForwardDilutionMass++;

 TString HistName;
 if(iflag == 0) HistName = "ForwardDilutionMassAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "ForwardDilutionMassUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "ForwardDilutionMassDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "ForwardDilutionMassAllAverage_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 4) HistName = "ForwardDilutionMassUpQuarkAverage_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 5) HistName = "ForwardDilutionMassDownQuarkAverage_" + PDFName + "_" + (int)iSet + "_" + Process;
 ForwardDilutionMassPlot[iForwardDilutionMass] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= ForwardDilutionMassPlot[iForwardDilutionMass]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;
   if(Process == "Integral"){
     double BinLeft = ForwardDilutionMassPlot[iForwardDilutionMass]->GetXaxis()->GetBinLowEdge(ibin);
     double BinRight = ForwardDilutionMassPlot[iForwardDilutionMass]->GetXaxis()->GetBinUpEdge(ibin);

     double Wrong = GetMassZYCrossSectionWrong(BinLeft, BinRight, log(BinLeft / ECM), log(ECM / BinLeft), iflag + 6, (TString)"F");
     double Total = GetMassZYCrossSection(BinLeft, BinRight, log(BinLeft / ECM), log(ECM / BinLeft), iflag + 6, (TString)"F");
     double Right = Total - Wrong;
     double WrongError = sqrt(Wrong) * ErrorLevel;
     double RightError = sqrt(Right) * ErrorLevel;

     Value = Wrong / Total;
     Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
   }
   if(Process == "NoIntegral"){
     double BinCenter = ForwardDilutionMassPlot[iForwardDilutionMass]->GetBinCenter(ibin);

     double Wrong = WrongHadronCrossSection(BinCenter, iflag + 6, (TString)"F");
     double Total = HadronCrossSection(BinCenter, iflag + 6, (TString)"F");
     double Right = Total - Wrong;
     double WrongError = sqrt(Wrong) * ErrorLevel;
     double RightError = sqrt(Right) * ErrorLevel;

     Value = Wrong / Total;
     Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
   }
   ForwardDilutionMassPlot[iForwardDilutionMass]->SetBinContent(ibin, Value);
   ForwardDilutionMassPlot[iForwardDilutionMass]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void PDFReweight::DrawBackwardDilutionMass(int bin, double left, double right, int iflag, TString Process)
{
 iBackwardDilutionMass++;

 TString HistName;
 if(iflag == 0) HistName = "BackwardDilutionMassAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "BackwardDilutionMassUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "BackwardDilutionMassDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "BackwardDilutionMassAllAverage_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 4) HistName = "BackwardDilutionMassUpQuarkAverage_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 5) HistName = "BackwardDilutionMassDownQuarkAverage_" + PDFName + "_" + (int)iSet + "_" + Process;
 BackwardDilutionMassPlot[iBackwardDilutionMass] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= BackwardDilutionMassPlot[iBackwardDilutionMass]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;
   if(Process == "Integral"){
     double BinLeft = BackwardDilutionMassPlot[iBackwardDilutionMass]->GetXaxis()->GetBinLowEdge(ibin);
     double BinRight = BackwardDilutionMassPlot[iBackwardDilutionMass]->GetXaxis()->GetBinUpEdge(ibin);

     double Wrong = GetMassZYCrossSectionWrong(BinLeft, BinRight, log(BinLeft / ECM), log(ECM / BinLeft), iflag + 6, (TString)"B");
     double Total = GetMassZYCrossSection(BinLeft, BinRight, log(BinLeft / ECM), log(ECM / BinLeft), iflag + 6, (TString)"B");
     double Right = Total - Wrong;
     double WrongError = sqrt(Wrong) * ErrorLevel;
     double RightError = sqrt(Right) * ErrorLevel;

     Value = Wrong / Total;
     Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
   }
   if(Process == "NoIntegral"){
     double BinCenter = BackwardDilutionMassPlot[iBackwardDilutionMass]->GetBinCenter(ibin);

     double Wrong = WrongHadronCrossSection(BinCenter, iflag + 6, (TString)"B");
     double Total = HadronCrossSection(BinCenter, iflag + 6, (TString)"B");
     double Right = Total - Wrong;
     double WrongError = sqrt(Wrong) * ErrorLevel;
     double RightError = sqrt(Right) * ErrorLevel;

     Value = Wrong / Total;
     Error = sqrt(Wrong * Wrong * RightError * RightError + Right * Right * WrongError * WrongError) / (Total * Total);
   }
   BackwardDilutionMassPlot[iBackwardDilutionMass]->SetBinContent(ibin, Value);
   BackwardDilutionMassPlot[iBackwardDilutionMass]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void PDFReweight::DrawHadronAFB(int bin, double left, double right, int iflag, TString Process)
{
 iHadronAFB++;

 TString HistName;
 if(iflag == 0) HistName = "HadronAFBAll_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iHadronAFB;
 if(iflag == 1) HistName = "HadronAFBUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iHadronAFB;
 if(iflag == 2) HistName = "HadronAFBDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iHadronAFB;
 if(iflag == 3) HistName = "HadronAFBGluon_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iHadronAFB;
 if(iflag == 4) HistName = "HadronAFBUpType_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iHadronAFB;
 if(iflag == 5) HistName = "HadronAFBDownType_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iHadronAFB;
 HadronAFBPlot[iHadronAFB] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= HadronAFBPlot[iHadronAFB]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;
   if(Process == "Integral"){
     double BinLeft = HadronAFBPlot[iHadronAFB]->GetXaxis()->GetBinLowEdge(ibin);
     double BinRight = HadronAFBPlot[iHadronAFB]->GetXaxis()->GetBinUpEdge(ibin);

     double Forward = GetHadronForwardCrossSection(BinLeft, BinRight, iflag);
     double Backward = GetHadronBackwardCrossSection(BinLeft, BinRight, iflag);
     double ForwardError = sqrt(Forward) * ErrorLevel;
     double BackwardError = sqrt(Backward) * ErrorLevel;

     Value = (Forward - Backward) / (Forward + Backward);
     Error = 2 * sqrt((Forward * BackwardError) * (Forward * BackwardError) + (Backward * ForwardError) * (Backward * ForwardError)) / ((Forward + Backward) * (Forward + Backward));
   }
   if(Process == "NoIntegral"){
     double BinCenter = HadronAFBPlot[iHadronAFB]->GetBinCenter(ibin);

     double Forward = HadronCrossSection(BinCenter, iflag, (TString)"F");
     double Backward = HadronCrossSection(BinCenter, iflag, (TString)"B");
     double ForwardError = sqrt(Forward) * ErrorLevel;
     double BackwardError = sqrt(Backward) * ErrorLevel;

     Value = (Forward - Backward) / (Forward + Backward);
     Error = 2 * sqrt((Forward * BackwardError) * (Forward * BackwardError) + (Backward * ForwardError) * (Backward * ForwardError)) / ((Forward + Backward) * (Forward + Backward));
   }

   HadronAFBPlot[iHadronAFB]->SetBinContent(ibin, Value);
   HadronAFBPlot[iHadronAFB]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void PDFReweight::DrawQuarkAFB(int bin, double left, double right, int iflag, TString Process)
{
 iQuarkAFB++;

 TString HistName;
 if(iflag == 0) HistName = "QuarkAFBAll_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iQuarkAFB;
 if(iflag == 1) HistName = "QuarkAFBUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iQuarkAFB;
 if(iflag == 2) HistName = "QuarkAFBDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iQuarkAFB;
 if(iflag == 3) HistName = "QuarkAFBGluon_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iQuarkAFB;
 if(iflag == 4) HistName = "QuarkAFBUpType_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iQuarkAFB;
 if(iflag == 5) HistName = "QuarkAFBDownType_" + PDFName + "_" + (int)iSet + "_" + Process + "_" + (int)iQuarkAFB;
 QuarkAFBPlot[iQuarkAFB] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= QuarkAFBPlot[iQuarkAFB]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;
   if(Process == "Integral"){
     double BinLeft = QuarkAFBPlot[iQuarkAFB]->GetXaxis()->GetBinLowEdge(ibin);
     double BinRight = QuarkAFBPlot[iQuarkAFB]->GetXaxis()->GetBinUpEdge(ibin);

     double Forward = GetHadronForwardCrossSection(BinLeft, BinRight, iflag + 6);
     double Backward = GetHadronBackwardCrossSection(BinLeft, BinRight, iflag + 6);
     double ForwardError = sqrt(Forward) * ErrorLevel;
     double BackwardError = sqrt(Backward) * ErrorLevel;

     Value = (Forward - Backward) / (Forward + Backward);
     Error = 2 * sqrt((Forward * BackwardError) * (Forward * BackwardError) + (Backward * ForwardError) * (Backward * ForwardError)) / ((Forward + Backward) * (Forward + Backward));
   }
   if(Process == "NoIntegral"){
     double BinCenter = QuarkAFBPlot[iQuarkAFB]->GetBinCenter(ibin);

     double Forward = HadronCrossSection(BinCenter, iflag + 6, (TString)"F");
     double Backward = HadronCrossSection(BinCenter, iflag + 6, (TString)"B");
     double ForwardError = sqrt(Forward) * ErrorLevel;
     double BackwardError = sqrt(Backward) * ErrorLevel;

     Value = (Forward - Backward) / (Forward + Backward);
     Error = 2 * sqrt((Forward * BackwardError) * (Forward * BackwardError) + (Backward * ForwardError) * (Backward * ForwardError)) / ((Forward + Backward) * (Forward + Backward));
   }

   QuarkAFBPlot[iQuarkAFB]->SetBinContent(ibin, Value);
   QuarkAFBPlot[iQuarkAFB]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void PDFReweight::DrawHadronAFBZY(int bin, double left, double right, int iflag, TString Process)
{
 iHadronAFBZY++;

 TString HistName;
 if(iflag == 0) HistName = "HadronAFBZYAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "HadronAFBZYUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "HadronAFBZYDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "HadronAFBZYGluon_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 4) HistName = "HadronAFBZYUpType_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 5) HistName = "HadronAFBZYDownType_" + PDFName + "_" + (int)iSet + "_" + Process;
 HadronAFBZYPlot[iHadronAFBZY] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= HadronAFBZYPlot[iHadronAFBZY]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;
   if(Process == "Integral"){
     double BinLeft = HadronAFBZYPlot[iHadronAFBZY]->GetXaxis()->GetBinLowEdge(ibin);
     double BinRight = HadronAFBZYPlot[iHadronAFBZY]->GetXaxis()->GetBinUpEdge(ibin);

     double Forward = GetMassZYCrossSection(60.0, 130.0, BinLeft, BinRight, iflag, "F");
     double Backward = GetMassZYCrossSection(60.0, 130.0, BinLeft, BinRight, iflag, "B");
     double ForwardError = sqrt(Forward) * ErrorLevel;
     double BackwardError = sqrt(Backward) * ErrorLevel;

     Value = (Forward - Backward) / (Forward + Backward);
     Error = 2 * sqrt((Forward * BackwardError) * (Forward * BackwardError) + (Backward * ForwardError) * (Backward * ForwardError)) / ((Forward + Backward) * (Forward + Backward));
   }
   if(Process == "NoIntegral"){
     double BinCenter = HadronAFBZYPlot[iHadronAFBZY]->GetBinCenter(ibin);

     double Forward = GetZYCrossSection(BinCenter, 60.0, 130.0, iflag, "F");
     double Backward = GetZYCrossSection(BinCenter, 60.0, 130.0, iflag, "B");
     double ForwardError = sqrt(Forward) * ErrorLevel;
     double BackwardError = sqrt(Backward) * ErrorLevel;

     Value = (Forward - Backward) / (Forward + Backward);
     Error = 2 * sqrt((Forward * BackwardError) * (Forward * BackwardError) + (Backward * ForwardError) * (Backward * ForwardError)) / ((Forward + Backward) * (Forward + Backward));
   }

   HadronAFBZYPlot[iHadronAFBZY]->SetBinContent(ibin, Value);
   HadronAFBZYPlot[iHadronAFBZY]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void PDFReweight::DrawQuarkAFBZY(int bin, double left, double right, int iflag, TString Process)
{
 iQuarkAFBZY++;

 TString HistName;
 if(iflag == 0) HistName = "QuarkAFBZYAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "QuarkAFBZYUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "QuarkAFBZYDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "QuarkAFBZYGluon_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 4) HistName = "QuarkAFBZYUpType_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 5) HistName = "QuarkAFBZYDownType_" + PDFName + "_" + (int)iSet + "_" + Process;
 QuarkAFBZYPlot[iQuarkAFBZY] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= QuarkAFBZYPlot[iQuarkAFBZY]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;
   if(Process == "Integral"){
     double BinLeft = QuarkAFBZYPlot[iQuarkAFBZY]->GetXaxis()->GetBinLowEdge(ibin);
     double BinRight = QuarkAFBZYPlot[iQuarkAFBZY]->GetXaxis()->GetBinUpEdge(ibin);

     double Forward = GetMassZYCrossSection(60.0, 130.0, BinLeft, BinRight, iflag + 6, "F");
     double Backward = GetMassZYCrossSection(60.0, 130.0, BinLeft, BinRight, iflag + 6, "B");
     double ForwardError = sqrt(Forward) * ErrorLevel;
     double BackwardError = sqrt(Backward) * ErrorLevel;

     Value = (Forward - Backward) / (Forward + Backward);
     Error = 2 * sqrt((Forward * BackwardError) * (Forward * BackwardError) + (Backward * ForwardError) * (Backward * ForwardError)) / ((Forward + Backward) * (Forward + Backward));
   }
   if(Process == "NoIntegral"){
     double BinCenter = QuarkAFBZYPlot[iQuarkAFBZY]->GetBinCenter(ibin);

     double Forward = GetZYCrossSection(BinCenter, 60.0, 130.0, iflag + 6, "F");
     double Backward = GetZYCrossSection(BinCenter, 60.0, 130.0, iflag + 6, "B");
     double ForwardError = sqrt(Forward) * ErrorLevel;
     double BackwardError = sqrt(Backward) * ErrorLevel;

     Value = (Forward - Backward) / (Forward + Backward);
     Error = 2 * sqrt((Forward * BackwardError) * (Forward * BackwardError) + (Backward * ForwardError) * (Backward * ForwardError)) / ((Forward + Backward) * (Forward + Backward));
   }

   QuarkAFBZYPlot[iQuarkAFBZY]->SetBinContent(ibin, Value);
   QuarkAFBZYPlot[iQuarkAFBZY]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void PDFReweight::DrawXsecFraction(int bin, double left, double right, int iflag, TString Process)
{
 iXsecFraction++;

 TString HistName;
 if(iflag == 1) HistName = "XsecFractionDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "XsecFractionUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "XsecFractionStrangeQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 4) HistName = "XsecFractionCharmQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 5) HistName = "XsecFractionBottomQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 10) HistName = "XsecFractionDownQuarkoverUD_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 20) HistName = "XsecFractionUpQuarkoverUD_" + PDFName + "_" + (int)iSet + "_" + Process;

 XsecFractionPlot[iXsecFraction] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= XsecFractionPlot[iXsecFraction]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;
   if(Process == "Integral"){
     double BinLeft = XsecFractionPlot[iXsecFraction]->GetXaxis()->GetBinLowEdge(ibin);
     double BinRight = XsecFractionPlot[iXsecFraction]->GetXaxis()->GetBinUpEdge(ibin);

     if(iflag == 1){
       double Numer = GetHadronTotalCrossSection(BinLeft, BinRight, 8);
       double Total = GetHadronTotalCrossSection(BinLeft, BinRight, 6);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
     if(iflag == 2){
       double Numer = GetHadronTotalCrossSection(BinLeft, BinRight, 7);
       double Total = GetHadronTotalCrossSection(BinLeft, BinRight, 6);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
     if(iflag == 3){
       double Numer = GetHadronTotalCrossSection(BinLeft, BinRight, 300);
       double Total = GetHadronTotalCrossSection(BinLeft, BinRight, 6);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
     if(iflag == 4){
       double Numer = GetHadronTotalCrossSection(BinLeft, BinRight, 400);
       double Total = GetHadronTotalCrossSection(BinLeft, BinRight, 6);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
     if(iflag == 5){
       double Numer = GetHadronTotalCrossSection(BinLeft, BinRight, 500);
       double Total = GetHadronTotalCrossSection(BinLeft, BinRight, 6);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
     if(iflag == 10){
       double Numer = GetHadronTotalCrossSection(BinLeft, BinRight, 8);
       double Total = GetHadronTotalCrossSection(BinLeft, BinRight, 8) + GetHadronTotalCrossSection(BinLeft, BinRight, 7);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
     if(iflag == 20){
       double Numer = GetHadronTotalCrossSection(BinLeft, BinRight, 7);
       double Total = GetHadronTotalCrossSection(BinLeft, BinRight, 8) + GetHadronTotalCrossSection(BinLeft, BinRight, 7);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
   }


   if(Process == "NoIntegral"){
     double BinCenter = XsecFractionPlot[iXsecFraction]->GetBinCenter(ibin);

     if(iflag == 1){
       double Numer = HadronCrossSection(BinCenter, 8);
       double Total = HadronCrossSection(BinCenter, 6);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
     if(iflag == 2){
       double Numer = HadronCrossSection(BinCenter, 7);
       double Total = HadronCrossSection(BinCenter, 6);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
     if(iflag == 3){
       double Numer = HadronCrossSection(BinCenter, 300);
       double Total = HadronCrossSection(BinCenter, 6);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
     if(iflag == 4){
       double Numer = HadronCrossSection(BinCenter, 400);
       double Total = HadronCrossSection(BinCenter, 6);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
     if(iflag == 5){
       double Numer = HadronCrossSection(BinCenter, 500);
       double Total = HadronCrossSection(BinCenter, 6);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
     if(iflag == 10){
       double Numer = HadronCrossSection(BinCenter, 8);
       double Total = HadronCrossSection(BinCenter, 8) + HadronCrossSection(BinCenter, 7);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
     if(iflag == 20){
       double Numer = HadronCrossSection(BinCenter, 7);
       double Total = HadronCrossSection(BinCenter, 8) + HadronCrossSection(BinCenter, 7);
       double Rest = Total - Numer;
       double NumerError = sqrt(Numer) * ErrorLevel;
       double RestError = sqrt(Rest) * ErrorLevel;

       Value = Numer / Total;
       Error = sqrt(Numer * Numer * RestError * RestError + Rest * Rest * NumerError * NumerError) / (Total * Total);
     }
   }
   XsecFractionPlot[iXsecFraction]->SetBinContent(ibin, Value);
   XsecFractionPlot[iXsecFraction]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void PDFReweight::GetAFBDilutionTimesFraction(int iDilut, int iFrac)
{
 iAFBDilutionTimesFraction = iFrac;

 AFBDilutionTimesFractionPlot[iFrac] = (TH1D *)XsecFractionPlot[iFrac]->Clone((TString)"AFBDilutionTimes" + XsecFractionPlot[iFrac]->GetName());
 AFBDilutionTimesFractionPlot[iFrac]->Reset();

 for(int ibin = 1; ibin <= XsecFractionPlot[iFrac]->GetNbinsX(); ibin++){
   double Value = XsecFractionPlot[iFrac]->GetBinContent(ibin) * AFBDilutionMassPlot[iDilut]->GetBinContent(ibin);
   AFBDilutionTimesFractionPlot[iFrac]->SetBinContent(ibin, Value);
   AFBDilutionTimesFractionPlot[iFrac]->SetBinError(ibin, 0.0);
 }

 hf->cd();
}

void PDFReweight::DrawRf(int bin, double left, double right, int iflag, TString Process)
{
 iRf++;

 TString HistName;
 if(iflag == 1) HistName = "RfDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "RfUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "RfStrangeQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 4) HistName = "RfCharmQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 5) HistName = "RfBottomQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 RfPlot[iRf] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= RfPlot[iRf]->GetNbinsX(); ibin++){
   double Value = 0.0;

   double BinLeft = RfPlot[iRf]->GetXaxis()->GetBinLowEdge(ibin);
   double BinRight = RfPlot[iRf]->GetXaxis()->GetBinUpEdge(ibin);

   Value = GetRf(BinLeft, BinRight, iflag, Process);

   RfPlot[iRf]->SetBinContent(ibin, Value);
   RfPlot[iRf]->SetBinError(ibin, 0);
 }

 hf->cd();
}

void PDFReweight::DrawS0Fraction(int bin, double left, double right, TString Process)
{
 iS0Fraction++;

 TString HistName;
 HistName = "S0Fraction_" + PDFName + "_" + (int)iSet;
 S0FractionPlot[iS0Fraction] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= S0FractionPlot[iS0Fraction]->GetNbinsX(); ibin++){
   double Value = 0.0;

   double BinLeft1 = 90 - S0FractionPlot[iS0Fraction]->GetXaxis()->GetBinUpEdge(ibin);
   double BinRight1 = 90 - S0FractionPlot[iS0Fraction]->GetXaxis()->GetBinLowEdge(ibin);
   double BinLeft2 = 90 + S0FractionPlot[iS0Fraction]->GetXaxis()->GetBinLowEdge(ibin);
   double BinRight2 = 90 + S0FractionPlot[iS0Fraction]->GetXaxis()->GetBinUpEdge(ibin);

   double Rd1 = GetRf(BinLeft1, BinRight1, 1, Process);
   double Ru1 = GetRf(BinLeft1, BinRight1, 2, Process);
   double Rs1 = GetRf(BinLeft1, BinRight1, 3, Process);
   double Rc1 = GetRf(BinLeft1, BinRight1, 4, Process);
   double Rb1 = GetRf(BinLeft1, BinRight1, 5, Process);

   double Rd2 = GetRf(BinLeft2, BinRight2, 1, Process);
   double Ru2 = GetRf(BinLeft2, BinRight2, 2, Process);
   double Rs2 = GetRf(BinLeft2, BinRight2, 3, Process);
   double Rc2 = GetRf(BinLeft2, BinRight2, 4, Process);
   double Rb2 = GetRf(BinLeft2, BinRight2, 5, Process);

   Value = (Ru1 + Rd1 - Ru2 - Rd2) / (Ru1 + Rd1 + Rs1 + Rc1 + Rb1 - Ru2 - Rd2 - Rs2 - Rc2 - Rb2);

   S0FractionPlot[iS0Fraction]->SetBinContent(ibin, Value);
   S0FractionPlot[iS0Fraction]->SetBinError(ibin, 0);
 }

 hf->cd();
}


void PDFReweight::DrawXsecDiff(int bin, double left, double right, int iflag, TString Process)
{
 iXsecDiff++;

 TString HistName;
 if(iflag == 0) HistName = "XsecDiff_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "ZMassUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "ZMassDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 XsecDiffPlot[iXsecDiff] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= XsecDiffPlot[iXsecDiff]->GetNbinsX(); ibin++){
   double Value = 0.0;
   if(Process == "Integral"){
     double BinLeft = XsecDiffPlot[iXsecDiff]->GetXaxis()->GetBinLowEdge(ibin);
     double BinRight = XsecDiffPlot[iXsecDiff]->GetXaxis()->GetBinUpEdge(ibin);

     double Value1 = GetMassZYCrossSection(BinLeft, BinRight, log(BinLeft / ECM), log(ECM / BinLeft), 1, (TString)"");
     double Value2 = GetMassZYCrossSection(BinLeft, BinRight, log(BinLeft / ECM), log(ECM / BinLeft), 2, (TString)"");
     Value = (Value1 - Value2) / (Value1 + Value2);
   }
   if(Process == "NoIntegral"){
     double BinCenter = XsecDiffPlot[iXsecDiff]->GetBinCenter(ibin);

     double Value1 = HadronCrossSection(BinCenter, 1, (TString)"");
     double Value2 = HadronCrossSection(BinCenter, 2, (TString)"");
     Value = (Value1 - Value2) / (Value1 + Value2);
   }

   XsecDiffPlot[iXsecDiff]->SetBinContent(ibin, Value);
   XsecDiffPlot[iXsecDiff]->SetBinError(ibin, 0);
 }

 hf->cd();
}

  ////////////////////////////
  ////  PDF related plot  ////
  ////////////////////////////

void PDFReweight::DrawPartonCorrelation(int Parton1, int Parton2, int nSet, TString ErrorType)
{
 InitialPartonName();

 iPartonCorrelation++;

 TString Parton1Name = PartonNameMap[Parton1];
 TString Parton2Name = PartonNameMap[Parton2];

 TString HistName;
 HistName = "PartonCorrelation_" +  Parton1Name + "_" + Parton2Name + "_" + PDFName;

 vector<double> Parton1PDF;
 vector<double> Parton2PDF;
 vector<vector<double>> Parton1PDFs;
 vector<vector<double>> Parton2PDFs;
 vector<double> Parton1ErrorPDF;
 vector<double> Parton2ErrorPDF;
 vector<vector<double>> Parton1ErrorPDFs;
 vector<vector<double>> Parton2ErrorPDFs;

 double LogBin[1000] = {0.0};

 for(int k = 0; k <= nSet; k++){
   InitialPDF(PDFName, k);
   for(int i = 0; i < 1000; i++){
     LogBin[i] = pow(10, (5.0 / 3.0) * log10((i + 1) / 1000.0));
     Parton1PDF.push_back(Getf(Parton1, LogBin[i], 91.1876));
     Parton2PDF.push_back(Getf(Parton2, LogBin[i], 91.1876));
   }
   Parton1PDFs.push_back(Parton1PDF);
   Parton2PDFs.push_back(Parton2PDF);
   Parton1PDF.clear();
   Parton2PDF.clear();
 }


 for(int k = 1; k <= nSet / 2; k++){
   for(int i = 0; i < 1000; i++){
     double Parton1ErrorValue = Parton1PDFs.at(2 * k - 1).at(i) - Parton1PDFs.at(2 * k).at(i);
     double Parton2ErrorValue = Parton2PDFs.at(2 * k - 1).at(i) - Parton2PDFs.at(2 * k).at(i);
     Parton1ErrorPDF.push_back(Parton1ErrorValue);
     Parton2ErrorPDF.push_back(Parton2ErrorValue);
   }
   Parton1ErrorPDFs.push_back(Parton1ErrorPDF);
   Parton2ErrorPDFs.push_back(Parton2ErrorPDF);
   Parton1ErrorPDF.clear();
   Parton2ErrorPDF.clear();
 }

 PartonCorrelationPlot[iPartonCorrelation] = new TH1D(HistName, HistName, 999, LogBin);
 for(int i = 0; i < 1000; i++){
   double Numer = 0.0;
   double Denom = 0.0;
   double DeltaX = 0.0;
   double DeltaY = 0.0;
   double DeltaX2 = 0.0;
   double DeltaY2 = 0.0;
   for(int k = 1; k <= nSet / 2; k++){
     Numer += Parton1ErrorPDFs.at(k - 1).at(i) * Parton2ErrorPDFs.at(k - 1).at(i) / 4.0;
     DeltaX2 += Parton1ErrorPDFs.at(k - 1).at(i) * Parton1ErrorPDFs.at(k - 1).at(i) / 4.0;
     DeltaY2 += Parton2ErrorPDFs.at(k - 1).at(i) * Parton2ErrorPDFs.at(k - 1).at(i) / 4.0;
   }
   DeltaX = sqrt(DeltaX2);
   DeltaY = sqrt(DeltaY2);
   Denom = DeltaX * DeltaY;

   PartonCorrelationPlot[iPartonCorrelation]->SetBinContent(i + 1, Numer / Denom);
   PartonCorrelationPlot[iPartonCorrelation]->SetBinError(i + 1, 0);
 }

 hf->cd();
}

void PDFReweight::DrawPartonCorrelation(vector<TH1D *> Variable, int Parton1, int nSet, TString ErrorType)
{
 InitialPartonName();

 iPartonCorrelation++;

 TString Parton1Name = PartonNameMap[Parton1];

 TString HistName;
 HistName = "PartonCorrelation_" +  (TString)Variable.at(0)->GetName() + "_" + Parton1Name + "_" + PDFName;

 vector<double> Parton1PDF;
 vector<vector<double>> Parton1PDFs;
 vector<double> Parton1ErrorPDF;
 vector<vector<double>> Parton1ErrorPDFs;

 double LogBin[1000] = {0.0};

 for(int k = 0; k <= nSet; k++){
   InitialPDF(PDFName, k);
   for(int i = 0; i < 1000; i++){
     LogBin[i] = pow(10, (5.0 / 3.0) * log10((i + 1) / 1000.0));
     Parton1PDF.push_back(Getf(Parton1, LogBin[i], 100.0));
   }
   Parton1PDFs.push_back(Parton1PDF);
   Parton1PDF.clear();
 }

 for(int k = 1; k <= nSet / 2; k++){
   for(int i = 0; i < 1000; i++){
     double Parton1ErrorValue = Parton1PDFs.at(2 * k - 1).at(i) - Parton1PDFs.at(2 * k).at(i);
     Parton1ErrorPDF.push_back(Parton1ErrorValue);
   }
   Parton1ErrorPDFs.push_back(Parton1ErrorPDF);
   Parton1ErrorPDF.clear();
 }

 PartonCorrelationPlot[iPartonCorrelation] = new TH1D(HistName, HistName, 999, LogBin);
 for(int i = 0; i < 1000; i++){
   double Numer = 0.0;
   double Denom = 0.0;
   double DeltaX = 0.0;
   double DeltaY = 0.0;
   double DeltaX2 = 0.0;
   double DeltaY2 = 0.0;
   for(int k = 1; k <= nSet / 2; k++){
     Numer += (Variable.at(2 * k - 1)->GetBinContent(1) - Variable.at(2 * k)->GetBinContent(1)) * Parton1ErrorPDFs.at(k - 1).at(i) / 4.0;
     DeltaX2 += (Variable.at(2 * k - 1)->GetBinContent(1) - Variable.at(2 * k)->GetBinContent(1)) * (Variable.at(2 * k - 1)->GetBinContent(1) - Variable.at(2 * k)->GetBinContent(1)) / 4.0;
     DeltaY2 += Parton1ErrorPDFs.at(k - 1).at(i) * Parton1ErrorPDFs.at(k - 1).at(i) / 4.0;
   }
   DeltaX = sqrt(DeltaX2);
   DeltaY = sqrt(DeltaY2);
   Denom = DeltaX * DeltaY;

   PartonCorrelationPlot[iPartonCorrelation]->SetBinContent(i + 1, Numer / Denom);
   PartonCorrelationPlot[iPartonCorrelation]->SetBinError(i + 1, 0);
 }

 hf->cd();
}

void PDFReweight::DrawPartonCorrelation(vector<TH1D *> Variable1, vector<TH1D *> Variable2, TGraph* &graph, TGraph* &central, TString ErrorType)
{
 TString HistName;
 HistName = "Correlation_" +  (TString)Variable1.at(0)->GetName() + "_" + (TString)Variable2.at(0)->GetName();

 int nSet = Variable1.size() - 1;
 if(Variable1.size() != Variable2.size()){
   cout<<"ERROR! Variable1 and Variable2 don't match!"<<endl;
 }

 double Corr = 0.0;

 double Numer = 0.0;
 double Denom = 0.0;
 double DeltaX = 0.0;
 double DeltaY = 0.0;
 double DeltaX2 = 0.0;
 double DeltaY2 = 0.0;

 if(ErrorType == "Symmetry" || ErrorType == "Symmetry68"){
   for(int k = 1; k <= nSet / 2; k++){
     Numer += (Variable1.at(2 * k - 1)->GetBinContent(1) - Variable1.at(2 * k)->GetBinContent(1)) * (Variable2.at(2 * k - 1)->GetBinContent(1) - Variable2.at(2 * k)->GetBinContent(1)) / 4.0;
     DeltaX2 += (Variable1.at(2 * k - 1)->GetBinContent(1) - Variable1.at(2 * k)->GetBinContent(1)) * (Variable1.at(2 * k - 1)->GetBinContent(1) - Variable1.at(2 * k)->GetBinContent(1)) / 4.0;
     DeltaY2 += (Variable2.at(2 * k - 1)->GetBinContent(1) - Variable2.at(2 * k)->GetBinContent(1)) * (Variable2.at(2 * k - 1)->GetBinContent(1) - Variable2.at(2 * k)->GetBinContent(1)) / 4.0;
   }
   DeltaX = sqrt(DeltaX2);
   DeltaY = sqrt(DeltaY2);
   Denom = DeltaX * DeltaY;

   if(ErrorType == "Symmetry"){
     DeltaX = DeltaX / 1.645;
     DeltaY = DeltaY / 1.645;
   }
 }

 if(ErrorType == "SymmetryOneSide" || ErrorType == "SymmetryOneSide68"){
   for(int k = 1; k <= nSet; k++){
     Numer += (Variable1.at(k)->GetBinContent(1) - Variable1.at(0)->GetBinContent(1)) * (Variable2.at(k)->GetBinContent(1) - Variable2.at(0)->GetBinContent(1));
     DeltaX2 += (Variable1.at(k)->GetBinContent(1) - Variable1.at(0)->GetBinContent(1)) * (Variable1.at(k)->GetBinContent(1) - Variable1.at(0)->GetBinContent(1));
     DeltaY2 += (Variable2.at(k)->GetBinContent(1) - Variable2.at(0)->GetBinContent(1)) * (Variable2.at(k)->GetBinContent(1) - Variable2.at(0)->GetBinContent(1));
   }
   DeltaX = sqrt(DeltaX2);
   DeltaY = sqrt(DeltaY2);
   Denom = DeltaX * DeltaY;

   if(ErrorType == "SymmetryOneSide"){
     DeltaX = DeltaX / 1.645;
     DeltaY = DeltaY / 1.645;
   }
 }

 Corr = Numer / Denom;

 graph = GenerateEllipse(Variable1.at(0)->GetBinContent(1), Variable2.at(0)->GetBinContent(1), DeltaX, DeltaY, Corr);
 graph->SetName(HistName);
 graph->SetTitle(HistName);

 central = new TGraph(1);
 central->SetPointX(1, Variable1.at(0)->GetBinContent(1));
 central->SetPointY(1, Variable2.at(0)->GetBinContent(1));
 central->RemovePoint(0);
 central->SetName(HistName + (TString)"_Central");
 central->SetTitle(HistName + (TString)"_Central");

}

void PDFReweight::DrawPartonCorrelation(vector<TH1D *> Variable1, TH2D* &Correlation, TString ErrorType)
{
 //PDF Covariance

 TString HistName;
 HistName = "PDFCorrelation_" +  (TString)Variable1.at(0)->GetName();

 int nSet = Variable1.size() - 1;

 int nbinx = Variable1.at(0)->GetNbinsX();
 double* xbinning = new double[nbinx + 1];
 xbinning[0] = Variable1.at(0)->GetXaxis()->GetBinLowEdge(1);
 for(int i = 1; i <= nbinx; i++){
   xbinning[i] = Variable1.at(0)->GetXaxis()->GetBinUpEdge(i);
 }

 Correlation = new TH2D(HistName, HistName, nbinx, xbinning, nbinx, xbinning);

 for(int ibinx = 1; ibinx <= Variable1.at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= Variable1.at(0)->GetNbinsX(); ibiny++){
     double Corr = 0.0;

     double Numer = 0.0;
     double Denom = 0.0;
     double DeltaX = 0.0;
     double DeltaY = 0.0;
     double DeltaX2 = 0.0;
     double DeltaY2 = 0.0;
     for(int k = 1; k <= nSet / 2; k++){
       Numer += (Variable1.at(2 * k - 1)->GetBinContent(ibinx) - Variable1.at(2 * k)->GetBinContent(ibinx)) * (Variable1.at(2 * k - 1)->GetBinContent(ibiny) - Variable1.at(2 * k)->GetBinContent(ibiny))/ 4.0;
       DeltaX2 += (Variable1.at(2 * k - 1)->GetBinContent(ibinx) - Variable1.at(2 * k)->GetBinContent(ibinx)) * (Variable1.at(2 * k - 1)->GetBinContent(ibinx) - Variable1.at(2 * k)->GetBinContent(ibinx)) / 4.0;
       DeltaY2 += (Variable1.at(2 * k - 1)->GetBinContent(ibiny) - Variable1.at(2 * k)->GetBinContent(ibiny)) * (Variable1.at(2 * k - 1)->GetBinContent(ibiny) - Variable1.at(2 * k)->GetBinContent(ibiny)) / 4.0;
     }
     DeltaX = sqrt(DeltaX2);
     DeltaY = sqrt(DeltaY2);
     Denom = DeltaX * DeltaY;

     Corr = Numer / Denom;

     if(ErrorType == "Symmetry"){
       DeltaX = DeltaX / 1.645;
       DeltaY = DeltaY / 1.645;
       Denom = DeltaX * DeltaY;
     }

     Correlation->SetBinContent(ibinx, ibiny, Corr * Denom);
     Correlation->SetBinError(ibinx, ibiny, 0.0);
   }
 }

}

void PDFReweight::DrawCombinationCorrelation(int Parton1, int nSet, TString ErrorType)
{
 iPartonCorrelation++;

 TString Parton1Name;

 if(Parton1 == 1) Parton1Name = "AFBPartonCombination";
 if(Parton1 == 2) Parton1Name = "WasymPartonCombination";

 TString HistName;
 HistName = "CombinationCorrelation_" + Parton1Name + "_" + PDFName;

 vector<double> Parton1PDF;
 vector<vector<double>> Parton1PDFs;
 vector<double> Parton1ErrorPDF;
 vector<vector<double>> Parton1ErrorPDFs;

 vector<double> Variable(nSet + 1);

 double LogBin[1000] = {0.0};

 for(int k = 0; k <= nSet; k++){
   InitialPDF(PDFName, k);
   for(int i = 0; i < 1000; i++){
     LogBin[i] = pow(10, (5.0 / 3.0) * log10((i + 1) / 1000.0));
     Parton1PDF.push_back(Getx1x2Combination(Parton1, LogBin[i], 0.0, 91.1876));
   }
   Parton1PDFs.push_back(Parton1PDF);
   Parton1PDF.clear();
   Variable.at(k) = Getx1x2Combination(1, 0.031, 0.0015, 91.1876);
 }

 for(int k = 1; k <= nSet / 2; k++){
   for(int i = 0; i < 1000; i++){
     double Parton1ErrorValue = Parton1PDFs.at(2 * k - 1).at(i) - Parton1PDFs.at(2 * k).at(i);
     Parton1ErrorPDF.push_back(Parton1ErrorValue);
   }
   Parton1ErrorPDFs.push_back(Parton1ErrorPDF);
   Parton1ErrorPDF.clear();
 }

 PartonCorrelationPlot[iPartonCorrelation] = new TH1D(HistName, HistName, 999, LogBin);

 for(int i = 0; i < 1000; i++){
   double Value = 0.0;
   double Numer = 0.0;
   double Denom = 0.0;
   double DeltaX = 0.0;
   double DeltaY = 0.0;
   double DeltaX2 = 0.0;
   double DeltaY2 = 0.0;
   for(int k = 1; k <= nSet / 2; k++){
     Numer += (Variable.at(2 * k - 1) - Variable.at(2 * k)) * Parton1ErrorPDFs.at(k - 1).at(i) / 4.0;
     DeltaX2 += (Variable.at(2 * k - 1) - Variable.at(2 * k)) * (Variable.at(2 * k - 1) - Variable.at(2 * k)) / 4.0;
     DeltaY2 += Parton1ErrorPDFs.at(k - 1).at(i) * Parton1ErrorPDFs.at(k - 1).at(i) / 4.0;
   }
   DeltaX = sqrt(DeltaX2);
   DeltaY = sqrt(DeltaY2);
   Denom = DeltaX * DeltaY;
   if(fabs(Denom) > 1e-9) Value = Numer / Denom;

   PartonCorrelationPlot[iPartonCorrelation]->SetBinContent(i + 1, Value);
   PartonCorrelationPlot[iPartonCorrelation]->SetBinError(i + 1, 0);
 }

 hf->cd();
}

void PDFReweight::DrawRelativePartonDensity(int bin, double left, double right, int iflag)
{
 iRelativePartonDensity++;

 TString Parton1Name = PartonNameMap[iflag];

 double LogBin[10] = {1e-5, 5e-5, 1e-4, 5e-4, 1e-3, 5e-3, 1e-2, 5e-2, 0.1, 0.5};

 TString HistName;
 HistName = "RelativePartonDensity_" + PDFName + "_" + (int)iSet + "_" + Parton1Name;
 RelativePartonDensityPlot[iRelativePartonDensity] = new TH1D(HistName, HistName, 9, LogBin);

 for(int ibin = 0; ibin < 9; ibin++){
   RelativePartonDensityPlot[iRelativePartonDensity]->SetBinContent(ibin + 1, Getf(iflag, LogBin[ibin], 91.1876) / GetfOrigin(iflag, LogBin[ibin], 91.1876));
   RelativePartonDensityPlot[iRelativePartonDensity]->SetBinError(ibin + 1, ErrorLevel);
 }

 hf->cd();
}


  ///////////////////
  ////  2D Plot  ////
  ///////////////////

void PDFReweight::DrawMassZY(int binx, double leftx, double rightx, int biny, double lefty, double righty, int iflag, TString Process)
{
 iMassZY++;

 TString HistName;
 if(iflag == 0) HistName = "MassZYAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "MassZYUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "MassZYDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "MassZYGluon_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 4) HistName = "MassZYUpType_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 5) HistName = "MassZYDownType_" + PDFName + "_" + (int)iSet + "_" + Process;
 MassZYPlot[iMassZY] = new TH2D(HistName, HistName, binx, leftx, rightx, biny, lefty, righty);

 for(int ibinx = 1; ibinx <= MassZYPlot[iMassZY]->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= MassZYPlot[iMassZY]->GetNbinsY(); ibiny++){
     double Value = 0.0;
     if(Process == "Integral"){
       double BinXLeft = MassZYPlot[iMassZY]->GetXaxis()->GetBinLowEdge(ibinx);
       double BinXRight = MassZYPlot[iMassZY]->GetXaxis()->GetBinUpEdge(ibinx);
       double BinYLeft = MassZYPlot[iMassZY]->GetYaxis()->GetBinLowEdge(ibiny);
       double BinYRight = MassZYPlot[iMassZY]->GetYaxis()->GetBinUpEdge(ibiny);

       Value = GetMassZYCrossSection(BinXLeft, BinXRight, BinYLeft, BinYRight, iflag, (TString)"");
     }
     if(Process == "NoIntegral"){
       double BinXCenter = MassZYPlot[iMassZY]->GetXaxis()->GetBinCenter(ibinx);
       double BinYCenter = MassZYPlot[iMassZY]->GetYaxis()->GetBinCenter(ibiny);

       Value = MassZYCrossSection(BinXCenter, BinYCenter, iflag, (TString)"");
     }
     MassZYPlot[iMassZY]->SetBinContent(ibinx, ibiny, Value);
     MassZYPlot[iMassZY]->SetBinError(ibinx, ibiny, 0);
   }
 }

 hf->cd();
}

void PDFReweight::DrawDilutionMassZY(int binx, double leftx, double rightx, int biny, double lefty, double righty, int iflag, TString Process)
{
 iDilutionMassZY++;

 TString HistName;
 if(iflag == 0) HistName = "DilutionMassZYAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "DilutionMassZYUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "DilutionMassZYDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "DilutionMassZYGluon_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 4) HistName = "DilutionMassZYUpType_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 5) HistName = "DilutionMassZYDownType_" + PDFName + "_" + (int)iSet + "_" + Process;
 DilutionMassZYPlot[iDilutionMassZY] = new TH2D(HistName, HistName, binx, leftx, rightx, biny, lefty, righty);

 for(int ibinx = 1; ibinx <= DilutionMassZYPlot[iDilutionMassZY]->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= DilutionMassZYPlot[iDilutionMassZY]->GetNbinsY(); ibiny++){
     double Value = 0.0;
     if(Process == "Integral"){
       double BinXLeft = DilutionMassZYPlot[iDilutionMassZY]->GetXaxis()->GetBinLowEdge(ibinx);
       double BinXRight = DilutionMassZYPlot[iDilutionMassZY]->GetXaxis()->GetBinUpEdge(ibinx);
       double BinYLeft = DilutionMassZYPlot[iDilutionMassZY]->GetYaxis()->GetBinLowEdge(ibiny);
       double BinYRight = DilutionMassZYPlot[iDilutionMassZY]->GetYaxis()->GetBinUpEdge(ibiny);

       double Wrong = GetMassZYCrossSectionWrong(BinXLeft, BinXRight, BinYLeft, BinYRight, iflag, (TString)"");
       double Total = GetMassZYCrossSection(BinXLeft, BinXRight, BinYLeft, BinYRight, iflag, (TString)"");

       Value = Wrong / Total;
     }
     if(Process == "NoIntegral"){
       double BinXCenter = DilutionMassZYPlot[iDilutionMassZY]->GetXaxis()->GetBinCenter(ibinx);
       double BinYCenter = DilutionMassZYPlot[iDilutionMassZY]->GetYaxis()->GetBinCenter(ibiny);

       double Wrong = MassZYCrossSectionWrong(BinXCenter, BinYCenter, iflag, (TString)"");
       double Total = MassZYCrossSection(BinXCenter, BinYCenter, iflag, (TString)"");

       Value = Wrong / Total;
     }
     DilutionMassZYPlot[iDilutionMassZY]->SetBinContent(ibinx, ibiny, Value);
     DilutionMassZYPlot[iDilutionMassZY]->SetBinError(ibinx, ibiny, 0);
   }
 }

 hf->cd();
}

void PDFReweight::DrawDilutionMassZY(int binx, double* xbins, int biny, double* ybins, int iflag, TString Process)
{
 iDilutionMassZY++;

 TString HistName;
 if(iflag == 0) HistName = "DilutionMassZYAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "DilutionMassZYUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "DilutionMassZYDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "DilutionMassZYGluon_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 4) HistName = "DilutionMassZYUpType_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 5) HistName = "DilutionMassZYDownType_" + PDFName + "_" + (int)iSet + "_" + Process;
 DilutionMassZYPlot[iDilutionMassZY] = new TH2D(HistName, HistName, binx, xbins, biny, ybins);

 for(int ibinx = 1; ibinx <= DilutionMassZYPlot[iDilutionMassZY]->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= DilutionMassZYPlot[iDilutionMassZY]->GetNbinsY(); ibiny++){
     double Value = 0.0;
     if(Process == "Integral"){
       double BinXLeft = DilutionMassZYPlot[iDilutionMassZY]->GetXaxis()->GetBinLowEdge(ibinx);
       double BinXRight = DilutionMassZYPlot[iDilutionMassZY]->GetXaxis()->GetBinUpEdge(ibinx);
       double BinYLeft = DilutionMassZYPlot[iDilutionMassZY]->GetYaxis()->GetBinLowEdge(ibiny);
       double BinYRight = DilutionMassZYPlot[iDilutionMassZY]->GetYaxis()->GetBinUpEdge(ibiny);

       double Wrong = GetMassZYCrossSectionWrong(BinXLeft, BinXRight, BinYLeft, BinYRight, iflag, (TString)"");
       double Total = GetMassZYCrossSection(BinXLeft, BinXRight, BinYLeft, BinYRight, iflag, (TString)"");

       Value = Wrong / Total;
     }
     if(Process == "NoIntegral"){
       double BinXCenter = DilutionMassZYPlot[iDilutionMassZY]->GetXaxis()->GetBinCenter(ibinx);
       double BinYCenter = DilutionMassZYPlot[iDilutionMassZY]->GetYaxis()->GetBinCenter(ibiny);

       double Wrong = MassZYCrossSectionWrong(BinXCenter, BinYCenter, iflag, (TString)"");
       double Total = MassZYCrossSection(BinXCenter, BinYCenter, iflag, (TString)"");

       Value = Wrong / Total;
     }
     DilutionMassZYPlot[iDilutionMassZY]->SetBinContent(ibinx, ibiny, Value);
     DilutionMassZYPlot[iDilutionMassZY]->SetBinError(ibinx, ibiny, 0);
   }
 }

 hf->cd();
}

void PDFReweight::DrawHadronAFBMassZY(int binx, double leftx, double rightx, int biny, double lefty, double righty, int iflag, TString Process)
{
 iHadronAFBMassZY++;

 TString HistName;
 if(iflag == 0) HistName = "HadronAFBMassZYAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "HadronAFBMassZYUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "HadronAFBMassZYDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "HadronAFBMassZYGluon_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 4) HistName = "HadronAFBMassZYUpType_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 5) HistName = "HadronAFBMassZYDownType_" + PDFName + "_" + (int)iSet + "_" + Process;
 HadronAFBMassZYPlot[iHadronAFBMassZY] = new TH2D(HistName, HistName, binx, leftx, rightx, biny, lefty, righty);

 for(int ibinx = 1; ibinx <= HadronAFBMassZYPlot[iHadronAFBMassZY]->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= HadronAFBMassZYPlot[iHadronAFBMassZY]->GetNbinsY(); ibiny++){
     double Value = 0.0;
     if(Process == "Integral"){
       double BinXLeft = HadronAFBMassZYPlot[iHadronAFBMassZY]->GetXaxis()->GetBinLowEdge(ibinx);
       double BinXRight = HadronAFBMassZYPlot[iHadronAFBMassZY]->GetXaxis()->GetBinUpEdge(ibinx);
       double BinYLeft = HadronAFBMassZYPlot[iHadronAFBMassZY]->GetYaxis()->GetBinLowEdge(ibiny);
       double BinYRight = HadronAFBMassZYPlot[iHadronAFBMassZY]->GetYaxis()->GetBinUpEdge(ibiny);

       double Forward = GetMassZYCrossSection(BinXLeft, BinXRight, BinYLeft, BinYRight, iflag, "F");
       double Backward = GetMassZYCrossSection(BinXLeft, BinXRight, BinYLeft, BinYRight, iflag, "B");

       Value = (Forward - Backward) / (Forward + Backward);
     }
     if(Process == "NoIntegral"){
       double BinXCenter = HadronAFBMassZYPlot[iHadronAFBMassZY]->GetXaxis()->GetBinCenter(ibinx);
       double BinYCenter = HadronAFBMassZYPlot[iHadronAFBMassZY]->GetYaxis()->GetBinCenter(ibiny);

       double Forward = MassZYCrossSection(BinXCenter, BinYCenter, iflag, "F");
       double Backward = MassZYCrossSection(BinXCenter, BinYCenter, iflag, "B");

       Value = (Forward - Backward) / (Forward + Backward);
     }
     HadronAFBMassZYPlot[iHadronAFBMassZY]->SetBinContent(ibinx, ibiny, Value);
     HadronAFBMassZYPlot[iHadronAFBMassZY]->SetBinError(ibinx, ibiny, 0);
   }
 }

 hf->cd();
}

void PDFReweight::DrawQuarkForwardMassZY(int binx, double leftx, double rightx, int biny, double lefty, double righty, int iflag, TString Process)
{
 iQuarkForwardMassZY++;

 TString HistName;
 if(iflag == 0) HistName = "QuarkForwardMassZYAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "QuarkForwardMassZYUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "QuarkForwardMassZYDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "QuarkForwardMassZYGluon_" + PDFName + "_" + (int)iSet + "_" + Process;
 QuarkForwardMassZYPlot[iQuarkForwardMassZY] = new TH2D(HistName, HistName, binx, leftx, rightx, biny, lefty, righty);

 for(int ibinx = 1; ibinx <= QuarkForwardMassZYPlot[iQuarkForwardMassZY]->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= QuarkForwardMassZYPlot[iQuarkForwardMassZY]->GetNbinsY(); ibiny++){
     double Value = 0.0;
     if(Process == "Integral"){
       double BinXLeft = QuarkForwardMassZYPlot[iQuarkForwardMassZY]->GetXaxis()->GetBinLowEdge(ibinx);
       double BinXRight = QuarkForwardMassZYPlot[iQuarkForwardMassZY]->GetXaxis()->GetBinUpEdge(ibinx);
       double BinYLeft = QuarkForwardMassZYPlot[iQuarkForwardMassZY]->GetYaxis()->GetBinLowEdge(ibiny);
       double BinYRight = QuarkForwardMassZYPlot[iQuarkForwardMassZY]->GetYaxis()->GetBinUpEdge(ibiny);

       double Forward = GetMassZYCrossSection(BinXLeft, BinXRight, BinYLeft, BinYRight, iflag + 6, "F");

       Value = Forward;
     }
     if(Process == "NoIntegral"){
       double BinXCenter = QuarkForwardMassZYPlot[iQuarkForwardMassZY]->GetXaxis()->GetBinCenter(ibinx);
       double BinYCenter = QuarkForwardMassZYPlot[iQuarkForwardMassZY]->GetYaxis()->GetBinCenter(ibiny);

       double Forward = MassZYCrossSection(BinXCenter, BinYCenter, iflag + 6, "F");

       Value = Forward;
     }
     QuarkForwardMassZYPlot[iQuarkForwardMassZY]->SetBinContent(ibinx, ibiny, Value);
     QuarkForwardMassZYPlot[iQuarkForwardMassZY]->SetBinError(ibinx, ibiny, 0);
   }
 }

 hf->cd();
}

void PDFReweight::DrawQuarkBackwardMassZY(int binx, double leftx, double rightx, int biny, double lefty, double righty, int iflag, TString Process)
{
 iQuarkBackwardMassZY++;

 TString HistName;
 if(iflag == 0) HistName = "QuarkBackwardMassZYAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "QuarkBackwardMassZYUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "QuarkBackwardMassZYDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "QuarkBackwardMassZYGluon_" + PDFName + "_" + (int)iSet + "_" + Process;
 QuarkBackwardMassZYPlot[iQuarkBackwardMassZY] = new TH2D(HistName, HistName, binx, leftx, rightx, biny, lefty, righty);

 for(int ibinx = 1; ibinx <= QuarkBackwardMassZYPlot[iQuarkBackwardMassZY]->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= QuarkBackwardMassZYPlot[iQuarkBackwardMassZY]->GetNbinsY(); ibiny++){
     double Value = 0.0;
     if(Process == "Integral"){
       double BinXLeft = QuarkBackwardMassZYPlot[iQuarkBackwardMassZY]->GetXaxis()->GetBinLowEdge(ibinx);
       double BinXRight = QuarkBackwardMassZYPlot[iQuarkBackwardMassZY]->GetXaxis()->GetBinUpEdge(ibinx);
       double BinYLeft = QuarkBackwardMassZYPlot[iQuarkBackwardMassZY]->GetYaxis()->GetBinLowEdge(ibiny);
       double BinYRight = QuarkBackwardMassZYPlot[iQuarkBackwardMassZY]->GetYaxis()->GetBinUpEdge(ibiny);

       double Forward = GetMassZYCrossSection(BinXLeft, BinXRight, BinYLeft, BinYRight, iflag + 6, "B");

       Value = Forward;
     }
     if(Process == "NoIntegral"){
       double BinXCenter = QuarkBackwardMassZYPlot[iQuarkBackwardMassZY]->GetXaxis()->GetBinCenter(ibinx);
       double BinYCenter = QuarkBackwardMassZYPlot[iQuarkBackwardMassZY]->GetYaxis()->GetBinCenter(ibiny);

       double Forward = MassZYCrossSection(BinXCenter, BinYCenter, iflag + 6, "B");

       Value = Forward;
     }
     QuarkBackwardMassZYPlot[iQuarkBackwardMassZY]->SetBinContent(ibinx, ibiny, Value);
     QuarkBackwardMassZYPlot[iQuarkBackwardMassZY]->SetBinError(ibinx, ibiny, 0);
   }
 }

 hf->cd();
}

void PDFReweight::RetrieveHist(TH1D* &hist, TString HistName, int i)
{
 if(i == 0){
   cout<<"ERROR! Please retrieve histogram from the index 1."<<endl;
   return;
 }

 if(HistName == "ZY") hist = ZYPlot[i];
 else if(HistName == "ZMass") hist = MassPlot[i];
 else if(HistName == "DilutionZY") hist = DilutionZYPlot[i];
 else if(HistName == "DilutionMass") hist = DilutionMassPlot[i];
 else if(HistName == "AFBDilutionMass") hist = AFBDilutionMassPlot[i];
 else if(HistName == "ForwardDilutionMass") hist = ForwardDilutionMassPlot[i];
 else if(HistName == "BackwardDilutionMass") hist = BackwardDilutionMassPlot[i];
 else if(HistName == "HadronAFB") hist = HadronAFBPlot[i];
 else if(HistName == "QuarkAFB") hist = QuarkAFBPlot[i];
 else if(HistName == "HadronAFBZY") hist = HadronAFBZYPlot[i];
 else if(HistName == "QuarkAFBZY") hist = QuarkAFBZYPlot[i];
 else if(HistName == "PartonCorrelation") hist = PartonCorrelationPlot[i];
 else if(HistName == "RelativePartonDensity") hist = RelativePartonDensityPlot[i];
 else if(HistName == "XsecFraction") hist = XsecFractionPlot[i];
 else if(HistName == "AFBDilutionTimesFraction") hist = AFBDilutionTimesFractionPlot[i];
 else if(HistName == "XsecDiff") hist = XsecDiffPlot[i];
 else cout<<"ERROR! Please try other name."<<endl;
}

void PDFReweight::RetrieveHist(TH2D* &hist, TString HistName, int i)
{
 if(i == 0){ 
   cout<<"ERROR! Please retrieve histogram from the index 1."<<endl;
   return;
 }

 if(HistName == "MassZY") hist = MassZYPlot[i];
 else if(HistName == "DilutionMassZY") hist = DilutionMassZYPlot[i];
 else if(HistName == "HadronAFBMassZY") hist = HadronAFBMassZYPlot[i];
 else if(HistName == "QuarkForwardMassZY") hist = QuarkForwardMassZYPlot[i];
 else if(HistName == "QuarkBackwardMassZY") hist = QuarkBackwardMassZYPlot[i];
 else cout<<"ERROR! Please try other name."<<endl;

}

void PDFReweight::GetPDFUncertainty(TString HistName, int bin, double left, double right, int iflag, TString Process)
{
 uncIndex++;

 unc_plot[HistName + (int)uncIndex] = new PDFUncertainty();

 vector<TH1D *> HistVector;
 TH1D *Error;

 for(int i = 0; i <= nSet; i++){
   InitialPDF(PDFName, i);
   if(HistName == "ZY"){
     DrawZY(bin, left, right, iflag, Process);
     HistVector.push_back(ZYPlot[iZY]);
   }
   else if(HistName == "ZMass"){
     DrawMass(bin, left, right, iflag, Process);
     HistVector.push_back(MassPlot[iMass]);
   }
   else if(HistName == "DilutionZY"){
     DrawDilutionZY(bin, left, right, iflag, Process);
     HistVector.push_back(DilutionZYPlot[iDilutionZY]);
   }
   else if(HistName == "DilutionMass"){
     DrawDilutionMass(bin, left, right, iflag, Process);
     HistVector.push_back(DilutionMassPlot[iDilutionMass]);
   }
   else if(HistName == "AFBDilutionMass"){
     DrawDilutionMass(bin, left, right, iflag, Process);
     GetAFBDilutionMass(iDilutionMass);
     HistVector.push_back(AFBDilutionMassPlot[iAFBDilutionMass]);
   }
   else if(HistName == "ForwardDilutionMass"){
     DrawForwardDilutionMass(bin, left, right, iflag, Process);
     HistVector.push_back(ForwardDilutionMassPlot[iForwardDilutionMass]);
   }
   else if(HistName == "BackwardDilutionMass"){
     DrawBackwardDilutionMass(bin, left, right, iflag, Process);
     HistVector.push_back(BackwardDilutionMassPlot[iBackwardDilutionMass]);
   }
   else if(HistName == "HadronAFB"){
     DrawHadronAFB(bin, left, right, iflag, Process);
     HistVector.push_back(HadronAFBPlot[iHadronAFB]);
   }
   else if(HistName == "QuarkAFB"){
     DrawQuarkAFB(bin, left, right, iflag, Process);
     HistVector.push_back(QuarkAFBPlot[iQuarkAFB]);
   }
   else if(HistName == "HadronAFBZY"){
     DrawHadronAFBZY(bin, left, right, iflag, Process);
     HistVector.push_back(HadronAFBZYPlot[iHadronAFBZY]);
   }
   else if(HistName == "QuarkAFBZY"){
     DrawQuarkAFBZY(bin, left, right, iflag, Process);
     HistVector.push_back(QuarkAFBZYPlot[iQuarkAFBZY]);
   }
   else if(HistName == "XsecFraction"){
     DrawXsecFraction(bin, left, right, iflag, Process);
     HistVector.push_back(XsecFractionPlot[iXsecFraction]);
   }
   else if(HistName == "AFBDilutionTimesFraction"){
     DrawDilutionMass(bin, left, right, iflag, Process);
     GetAFBDilutionMass(iDilutionMass);
     if(iflag == 4) DrawXsecFraction(bin, left, right, 20, Process);
     if(iflag == 5) DrawXsecFraction(bin, left, right, 10, Process);
     GetAFBDilutionTimesFraction(iAFBDilutionMass, iXsecFraction);
     HistVector.push_back(AFBDilutionTimesFractionPlot[iAFBDilutionTimesFraction]);
   }
   else if(HistName == "XsecDiff"){
     DrawXsecDiff(bin, left, right, iflag, Process);
     HistVector.push_back(XsecDiffPlot[iXsecDiff]);
   }
   else if(HistName == "RelativePartonDensity"){
     DrawRelativePartonDensity(bin, left, right, iflag);
     HistVector.push_back(RelativePartonDensityPlot[iRelativePartonDensity]);
   }
 }

 central_plot[HistName + (int)uncIndex] = (TH1D *)HistVector.at(0)->Clone((TString)"CentralPlot_" + HistName + (int)uncIndex);
 unc_plot[HistName + (int)uncIndex]->SaveVariBin();
 unc_plot[HistName + (int)uncIndex]->Input1DPlot("Symmetry", HistVector, Error);
}

void PDFReweight::OutputePumpFile(TString HistName, TString FileName, int bin, double left, double right, int iflag, TString Process)
{
 GetPDFUncertainty(HistName, bin, left, right, iflag, Process);

 file_plot[HistName + (int)uncIndex] = new FileForEPUMP(FileName);
 file_plot[HistName + (int)uncIndex]->InputData(central_plot[HistName + (int)uncIndex]);
 file_plot[HistName + (int)uncIndex]->InputTheory(unc_plot[HistName + (int)uncIndex]);
 file_plot[HistName + (int)uncIndex]->writedata();
 file_plot[HistName + (int)uncIndex]->writetheory();
}

  ///////////////////////
  ////  Calculation  ////
  ///////////////////////


//dsigma/dq in hadron level
double PDFReweight::HadronCrossSection(double mass, int iflag, TString Process)
{
 double Value = 0.0;

 double uubar = 0.0;
 double ccbar = 0.0;
 double ubaru = 0.0;
 double cbarc = 0.0;
 double ddbar = 0.0;
 double ssbar = 0.0;
 double bbbar = 0.0;
 double dbard = 0.0;
 double sbars = 0.0;
 double bbarb = 0.0;

 if(iflag == 0){//total
   uubar = CfCfQgtQbar(mass, 2) * ZCrossSection(mass, 1, Process) + CfCfQltQbar(mass, 2) * ZCrossSection(mass, -1, Process);
   ccbar = CfCfQgtQbar(mass, 4) * ZCrossSection(mass, 1, Process) + CfCfQltQbar(mass, 4) * ZCrossSection(mass, -1, Process);
   ubaru = CfCfQgtQbar(mass, -2) * ZCrossSection(mass, 1, Process) + CfCfQltQbar(mass, -2) * ZCrossSection(mass, -1, Process);
   cbarc = CfCfQgtQbar(mass, -4) * ZCrossSection(mass, 1, Process) + CfCfQltQbar(mass, -4) * ZCrossSection(mass, -1, Process);
   ddbar = CfCfQgtQbar(mass, 1) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, 1) * ZCrossSection(mass, -2, Process);
   ssbar = CfCfQgtQbar(mass, 3) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, 3) * ZCrossSection(mass, -2, Process);
   bbbar = CfCfQgtQbar(mass, 5) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, 5) * ZCrossSection(mass, -2, Process);
   dbard = CfCfQgtQbar(mass, -1) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, -1) * ZCrossSection(mass, -2, Process);
   sbars = CfCfQgtQbar(mass, -3) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, -3) * ZCrossSection(mass, -2, Process);
   bbarb = CfCfQgtQbar(mass, -5) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, -5) * ZCrossSection(mass, -2, Process);

   Value = uubar + ubaru + ccbar + cbarc + ddbar + ssbar + bbbar + dbard + sbars + bbarb;
 }
 if(iflag == 1){//uubar
   uubar = CfCfQgtQbar(mass, 2) * ZCrossSection(mass, 1, Process) + CfCfQltQbar(mass, 2) * ZCrossSection(mass, -1, Process);
   ubaru = CfCfQgtQbar(mass, -2) * ZCrossSection(mass, 1, Process) + CfCfQltQbar(mass, -2) * ZCrossSection(mass, -1, Process);

   Value = (uubar + ubaru);
 }
 if(iflag == 2){//ddbar
   ddbar = CfCfQgtQbar(mass, 1) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, 1) * ZCrossSection(mass, -2, Process);
   dbard = CfCfQgtQbar(mass, -1) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, -1) * ZCrossSection(mass, -2, Process);

   Value = (ddbar + dbard);
 }
 if(iflag == 3){//gluon
   ccbar = CfCfQgtQbar(mass, 4) * ZCrossSection(mass, 1, Process) + CfCfQltQbar(mass, 4) * ZCrossSection(mass, -1, Process);
   cbarc = CfCfQgtQbar(mass, -4) * ZCrossSection(mass, 1, Process) + CfCfQltQbar(mass, -4) * ZCrossSection(mass, -1, Process);
   ssbar = CfCfQgtQbar(mass, 3) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, 3) * ZCrossSection(mass, -2, Process);
   bbbar = CfCfQgtQbar(mass, 5) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, 5) * ZCrossSection(mass, -2, Process);
   sbars = CfCfQgtQbar(mass, -3) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, -3) * ZCrossSection(mass, -2, Process);
   bbarb = CfCfQgtQbar(mass, -5) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, -5) * ZCrossSection(mass, -2, Process);

   Value = ccbar + cbarc + ssbar + bbbar + sbars + bbarb;
 }
 if(iflag == 4){//u type
   uubar = CfCfQgtQbar(mass, 2) * ZCrossSection(mass, 1, Process) + CfCfQltQbar(mass, 2) * ZCrossSection(mass, -1, Process);
   ccbar = CfCfQgtQbar(mass, 4) * ZCrossSection(mass, 1, Process) + CfCfQltQbar(mass, 4) * ZCrossSection(mass, -1, Process);
   ubaru = CfCfQgtQbar(mass, -2) * ZCrossSection(mass, 1, Process) + CfCfQltQbar(mass, -2) * ZCrossSection(mass, -1, Process);
   cbarc = CfCfQgtQbar(mass, -4) * ZCrossSection(mass, 1, Process) + CfCfQltQbar(mass, -4) * ZCrossSection(mass, -1, Process);

   Value = (uubar + ccbar + ubaru + cbarc);
 }
 if(iflag == 5){//d type
   ddbar = CfCfQgtQbar(mass, 1) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, 1) * ZCrossSection(mass, -2, Process);
   ssbar = CfCfQgtQbar(mass, 3) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, 3) * ZCrossSection(mass, -2, Process);
   bbbar = CfCfQgtQbar(mass, 5) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, 5) * ZCrossSection(mass, -2, Process);
   dbard = CfCfQgtQbar(mass, -1) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, -1) * ZCrossSection(mass, -2, Process);
   sbars = CfCfQgtQbar(mass, -3) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, -3) * ZCrossSection(mass, -2, Process);
   bbarb = CfCfQgtQbar(mass, -5) * ZCrossSection(mass, 2, Process) + CfCfQltQbar(mass, -5) * ZCrossSection(mass, -2, Process);

   Value = ddbar + ssbar + bbbar + dbard + sbars + bbarb;
 }
 if(iflag == 6){//quark total
   uubar = CfCf(mass, 2) * ZCrossSection(mass, 1, Process);
   ccbar = CfCf(mass, 4) * ZCrossSection(mass, 1, Process);
   ubaru = CfCf(mass, -2) * ZCrossSection(mass, 1, Process);
   cbarc = CfCf(mass, -4) * ZCrossSection(mass, 1, Process);
   ddbar = CfCf(mass, 1) * ZCrossSection(mass, 2, Process);
   ssbar = CfCf(mass, 3) * ZCrossSection(mass, 2, Process);
   bbbar = CfCf(mass, 5) * ZCrossSection(mass, 2, Process);
   dbard = CfCf(mass, -1) * ZCrossSection(mass, 2, Process);
   sbars = CfCf(mass, -3) * ZCrossSection(mass, 2, Process);
   bbarb = CfCf(mass, -5) * ZCrossSection(mass, 2, Process);

   Value = uubar + ubaru + ccbar + cbarc + ddbar + ssbar + bbbar + dbard + sbars + bbarb;
 }
 if(iflag == 7){//quark uubar
   uubar = CfCf(mass, 2) * ZCrossSection(mass, 1, Process);
   ubaru = CfCf(mass, -2) * ZCrossSection(mass, 1, Process);

   Value = (uubar + ubaru);
 }
 if(iflag == 8){//quark ddbar
   ddbar = CfCf(mass, 1) * ZCrossSection(mass, 2, Process);
   dbard = CfCf(mass, -1) * ZCrossSection(mass, 2, Process);

   Value = (ddbar + dbard);
 }
 if(iflag == 9){//quark gluon
   ccbar = CfCf(mass, 4) * ZCrossSection(mass, 1, Process);
   cbarc = CfCf(mass, -4) * ZCrossSection(mass, 1, Process);
   ssbar = CfCf(mass, 3) * ZCrossSection(mass, 2, Process);
   bbbar = CfCf(mass, 5) * ZCrossSection(mass, 2, Process);
   sbars = CfCf(mass, -3) * ZCrossSection(mass, 2, Process);
   bbarb = CfCf(mass, -5) * ZCrossSection(mass, 2, Process);

   Value = ccbar + cbarc + ssbar + bbbar + sbars + bbarb;
 }
 if(iflag == 10){//quark u-type
   uubar = CfCf(mass, 2) * ZCrossSection(mass, 1, Process);
   ccbar = CfCf(mass, 4) * ZCrossSection(mass, 1, Process);
   ubaru = CfCf(mass, -2) * ZCrossSection(mass, 1, Process);
   cbarc = CfCf(mass, -4) * ZCrossSection(mass, 1, Process);

   Value = uubar + ubaru + ccbar + cbarc;
 }
 if(iflag == 11){//quark d-type
   ddbar = CfCf(mass, 1) * ZCrossSection(mass, 2, Process);
   ssbar = CfCf(mass, 3) * ZCrossSection(mass, 2, Process);
   bbbar = CfCf(mass, 5) * ZCrossSection(mass, 2, Process);
   dbard = CfCf(mass, -1) * ZCrossSection(mass, 2, Process);
   sbars = CfCf(mass, -3) * ZCrossSection(mass, 2, Process);
   bbarb = CfCf(mass, -5) * ZCrossSection(mass, 2, Process);

   Value = ddbar + ssbar + bbbar + dbard + sbars + bbarb;
 }
 if(iflag == 300){//quark ssbar
   ssbar = CfCf(mass, 3) * ZCrossSection(mass, 2, Process);
   sbars = CfCf(mass, -3) * ZCrossSection(mass, 2, Process);

   Value = ssbar + sbars;
 }
 if(iflag == 400){//quark ccbar
   ccbar = CfCf(mass, 4) * ZCrossSection(mass, 1, Process);
   cbarc = CfCf(mass, -4) * ZCrossSection(mass, 1, Process);

   Value = ccbar + cbarc;
 }
 if(iflag == 500){//quark bbbar
   bbbar = CfCf(mass, 5) * ZCrossSection(mass, 2, Process);
   bbarb = CfCf(mass, -5) * ZCrossSection(mass, 2, Process);

   Value = bbbar + bbarb;
 }
 if(iflag == 1000){//pure uubar
   Value = ZCrossSection(mass, 1, Process);
 }
 if(iflag == 2000){//pure ddbar
   Value = ZCrossSection(mass, 2, Process);
 }

 return Value;
}

double PDFReweight::WrongHadronCrossSection(double mass, int iflag, TString Process)
{
 double Value = 0.0;

 double uubar = 0.0;
 double ccbar = 0.0;
 double ubaru = 0.0;
 double cbarc = 0.0;
 double ddbar = 0.0;
 double ssbar = 0.0;
 double bbbar = 0.0;
 double dbard = 0.0;
 double sbars = 0.0;
 double bbarb = 0.0;

 if(iflag == 0){//total
   uubar = CfCfQltQbar(mass, 2) * ZCrossSection(mass, 1, Process);
   ubaru = CfCfQltQbar(mass, -2) * ZCrossSection(mass, 1, Process);
   ddbar = CfCfQltQbar(mass, 1) * ZCrossSection(mass, 2, Process);
   dbard = CfCfQltQbar(mass, -1) * ZCrossSection(mass, 2, Process);
   ccbar = CfCfQltQbar(mass, 4) * ZCrossSection(mass, 1, Process);
   cbarc = CfCfQltQbar(mass, -4) * ZCrossSection(mass, 1, Process);
   ssbar = CfCfQltQbar(mass, 3) * ZCrossSection(mass, 2, Process);
   sbars = CfCfQltQbar(mass, -3) * ZCrossSection(mass, 2, Process);
   bbbar = CfCfQltQbar(mass, 5) * ZCrossSection(mass, 2, Process);
   bbarb = CfCfQltQbar(mass, -5) * ZCrossSection(mass, 2, Process);

   Value = (uubar + ubaru + ddbar + dbard + ccbar + cbarc + ssbar + sbars + bbbar + bbarb);
 }
 if(iflag == 1){//uubar
   uubar = CfCfQltQbar(mass, 2) * ZCrossSection(mass, 1, Process);
   ubaru = CfCfQltQbar(mass, -2) * ZCrossSection(mass, 1, Process);

   Value = uubar + ubaru;
 }
 if(iflag == 2){//ddbar
   ddbar = CfCfQltQbar(mass, 1) * ZCrossSection(mass, 2, Process);
   dbard = CfCfQltQbar(mass, -1) * ZCrossSection(mass, 2, Process);

   Value = ddbar + dbard;
 }
 if(iflag == 3){//gluon
   ccbar = CfCfQltQbar(mass, 4) * ZCrossSection(mass, 1, Process);
   cbarc = CfCfQltQbar(mass, -4) * ZCrossSection(mass, 1, Process);
   ssbar = CfCfQltQbar(mass, 3) * ZCrossSection(mass, 2, Process);
   sbars = CfCfQltQbar(mass, -3) * ZCrossSection(mass, 2, Process);
   bbbar = CfCfQltQbar(mass, 5) * ZCrossSection(mass, 2, Process);
   bbarb = CfCfQltQbar(mass, -5) * ZCrossSection(mass, 2, Process);

   Value = (ccbar + cbarc + ssbar + sbars + bbbar + bbarb);
 }
 if(iflag == 4){//u type
   uubar = CfCfQltQbar(mass, 2) * ZCrossSection(mass, 1, Process);
   ubaru = CfCfQltQbar(mass, -2) * ZCrossSection(mass, 1, Process);
   ccbar = CfCfQltQbar(mass, 4) * ZCrossSection(mass, 1, Process);
   cbarc = CfCfQltQbar(mass, -4) * ZCrossSection(mass, 1, Process);

   Value = (uubar + ubaru + ccbar + cbarc);
 }
 if(iflag == 5){//d type
   ddbar = CfCfQltQbar(mass, 1) * ZCrossSection(mass, 2, Process);
   dbard = CfCfQltQbar(mass, -1) * ZCrossSection(mass, 2, Process);
   ssbar = CfCfQltQbar(mass, 3) * ZCrossSection(mass, 2, Process);
   sbars = CfCfQltQbar(mass, -3) * ZCrossSection(mass, 2, Process);
   bbbar = CfCfQltQbar(mass, 5) * ZCrossSection(mass, 2, Process);
   bbarb = CfCfQltQbar(mass, -5) * ZCrossSection(mass, 2, Process);

   Value = (ddbar + dbard + ssbar + sbars + bbbar + bbarb);
 }
 if(iflag == 6){//quark total
   uubar = CfCfQltQbar(mass, 2) * ZCrossSection(mass, 1, Process);
   ubaru = CfCfQltQbar(mass, -2) * ZCrossSection(mass, 1, Process);
   ddbar = CfCfQltQbar(mass, 1) * ZCrossSection(mass, 2, Process);
   dbard = CfCfQltQbar(mass, -1) * ZCrossSection(mass, 2, Process);
   ccbar = CfCfQltQbar(mass, 4) * ZCrossSection(mass, 1, Process);
   cbarc = CfCfQltQbar(mass, -4) * ZCrossSection(mass, 1, Process);
   ssbar = CfCfQltQbar(mass, 3) * ZCrossSection(mass, 2, Process);
   sbars = CfCfQltQbar(mass, -3) * ZCrossSection(mass, 2, Process);
   bbbar = CfCfQltQbar(mass, 5) * ZCrossSection(mass, 2, Process);
   bbarb = CfCfQltQbar(mass, -5) * ZCrossSection(mass, 2, Process);

   Value = (uubar + ubaru + ddbar + dbard + ccbar + cbarc + ssbar + sbars + bbbar + bbarb);
 }
 if(iflag == 7){//quark uubar
   uubar = CfCfQltQbar(mass, 2) * ZCrossSection(mass, 1, Process);
   ubaru = CfCfQltQbar(mass, -2) * ZCrossSection(mass, 1, Process);

   Value = uubar + ubaru;
 }
 if(iflag == 8){//quark ddbar
   ddbar = CfCfQltQbar(mass, 1) * ZCrossSection(mass, 2, Process);
   dbard = CfCfQltQbar(mass, -1) * ZCrossSection(mass, 2, Process);

   Value = ddbar + dbard;
 }
 if(iflag == 9){//quark gluon
   ccbar = CfCfQltQbar(mass, 4) * ZCrossSection(mass, 1, Process);
   cbarc = CfCfQltQbar(mass, -4) * ZCrossSection(mass, 1, Process);
   ssbar = CfCfQltQbar(mass, 3) * ZCrossSection(mass, 2, Process);
   sbars = CfCfQltQbar(mass, -3) * ZCrossSection(mass, 2, Process);
   bbbar = CfCfQltQbar(mass, 5) * ZCrossSection(mass, 2, Process);
   bbarb = CfCfQltQbar(mass, -5) * ZCrossSection(mass, 2, Process);

   Value = (ccbar + cbarc + ssbar + sbars + bbbar + bbarb);
 }
 if(iflag == 10){//quark u-type
   uubar = CfCfQltQbar(mass, 2) * ZCrossSection(mass, 1, Process);
   ubaru = CfCfQltQbar(mass, -2) * ZCrossSection(mass, 1, Process);
   ccbar = CfCfQltQbar(mass, 4) * ZCrossSection(mass, 1, Process);
   cbarc = CfCfQltQbar(mass, -4) * ZCrossSection(mass, 1, Process);

   Value = (uubar + ubaru + ccbar + cbarc);
 }
 if(iflag == 11){//quark d-type
   ddbar = CfCfQltQbar(mass, 1) * ZCrossSection(mass, 2, Process);
   dbard = CfCfQltQbar(mass, -1) * ZCrossSection(mass, 2, Process);
   ssbar = CfCfQltQbar(mass, 3) * ZCrossSection(mass, 2, Process);
   sbars = CfCfQltQbar(mass, -3) * ZCrossSection(mass, 2, Process);
   bbbar = CfCfQltQbar(mass, 5) * ZCrossSection(mass, 2, Process);
   bbarb = CfCfQltQbar(mass, -5) * ZCrossSection(mass, 2, Process);

   Value = (ddbar + dbard + ssbar + sbars + bbbar + bbarb);
 }
 return Value;
}

//dsigma/dq in quark level
double PDFReweight::ZCrossSection(double mass, int iflag, TString Process)
{
 double Value = EW->ZCrossSection(mass, iflag, Process);

 return Value;
}

//dsigma/dqdZY
double PDFReweight::MassZYCrossSection(double Q, double ZY, int iflag, TString Process)
{
 double x1 = (Q / ECM) * exp(ZY);
 double x2 = (Q / ECM) * exp(ZY * (-1));

 double Value = 0.0;
 if(iflag == 0){//hadron total
   Value = GetF1F2dYRight(2, x1, Q) * ZCrossSection(Q, 1, Process) + GetF1F2dYWrong(2, x1, Q) * ZCrossSection(Q, -1, Process)
         + GetF1F2dYRight(1, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(1, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(3, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(3, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(4, x1, Q) * ZCrossSection(Q, 1, Process) + GetF1F2dYWrong(4, x1, Q) * ZCrossSection(Q, -1, Process)
         + GetF1F2dYRight(5, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(5, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(-2, x1, Q) * ZCrossSection(Q, 1, Process) + GetF1F2dYWrong(-2, x1, Q) * ZCrossSection(Q, -1, Process)
         + GetF1F2dYRight(-1, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(-1, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(-3, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(-3, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(-4, x1, Q) * ZCrossSection(Q, 1, Process) + GetF1F2dYWrong(-4, x1, Q) * ZCrossSection(Q, -1, Process)
         + GetF1F2dYRight(-5, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(-5, x1, Q) * ZCrossSection(Q, -2, Process);
 }
 if(iflag == 1){//hadron uubar
   Value = GetF1F2dYRight(2, x1, Q) * ZCrossSection(Q, 1, Process) + GetF1F2dYWrong(2, x1, Q) * ZCrossSection(Q, -1, Process)
         + GetF1F2dYRight(-2, x1, Q) * ZCrossSection(Q, 1, Process) + GetF1F2dYWrong(-2, x1, Q) * ZCrossSection(Q, -1, Process);
 }
 if(iflag == 2){//hadron ddbar
   Value = GetF1F2dYRight(1, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(1, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(-1, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(-1, x1, Q) * ZCrossSection(Q, -2, Process);
 }
 if(iflag == 3){//hadron gluon
   Value = GetF1F2dYRight(3, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(3, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(4, x1, Q) * ZCrossSection(Q, 1, Process) + GetF1F2dYWrong(4, x1, Q) * ZCrossSection(Q, -1, Process)
         + GetF1F2dYRight(5, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(5, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(-3, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(-3, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(-4, x1, Q) * ZCrossSection(Q, 1, Process) + GetF1F2dYWrong(-4, x1, Q) * ZCrossSection(Q, -1, Process)
         + GetF1F2dYRight(-5, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(-5, x1, Q) * ZCrossSection(Q, -2, Process);
 }
 if(iflag == 4){//hadron u-type
   Value = GetF1F2dYRight(2, x1, Q) * ZCrossSection(Q, 1, Process) + GetF1F2dYWrong(2, x1, Q) * ZCrossSection(Q, -1, Process)
         + GetF1F2dYRight(4, x1, Q) * ZCrossSection(Q, 1, Process) + GetF1F2dYWrong(4, x1, Q) * ZCrossSection(Q, -1, Process)
         + GetF1F2dYRight(-2, x1, Q) * ZCrossSection(Q, 1, Process) + GetF1F2dYWrong(-2, x1, Q) * ZCrossSection(Q, -1, Process)
         + GetF1F2dYRight(-4, x1, Q) * ZCrossSection(Q, 1, Process) + GetF1F2dYWrong(-4, x1, Q) * ZCrossSection(Q, -1, Process);
 }
 if(iflag == 5){//hadron d-type
   Value = GetF1F2dYRight(1, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(1, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(3, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(3, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(5, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(5, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(-1, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(-1, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(-3, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(-3, x1, Q) * ZCrossSection(Q, -2, Process)
         + GetF1F2dYRight(-5, x1, Q) * ZCrossSection(Q, 2, Process) + GetF1F2dYWrong(-5, x1, Q) * ZCrossSection(Q, -2, Process);
 }
 if(iflag == 6){//quark total
   Value = GetF1F2dY(2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dY(1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dY(5, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(-2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dY(-1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(-3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(-4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dY(-5, x1, Q) * ZCrossSection(Q, 2, Process);
 }
 if(iflag == 7){//quark uubar
   Value = GetF1F2dY(2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dY(-2, x1, Q) * ZCrossSection(Q, 1, Process);
 }
 if(iflag == 8){//quark ddbar
   Value = GetF1F2dY(1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(-1, x1, Q) * ZCrossSection(Q, 2, Process);
 }
 if(iflag == 9){//quark gluon
   Value = GetF1F2dY(3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dY(5, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(-3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(-4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dY(-5, x1, Q) * ZCrossSection(Q, 2, Process);
 }
 if(iflag == 10){//quark u-type
   Value = GetF1F2dY(2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dY(4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dY(-2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dY(-4, x1, Q) * ZCrossSection(Q, 1, Process);
 }
 if(iflag == 11){//quark d-type
   Value = GetF1F2dY(1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(5, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(-1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(-3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dY(-5, x1, Q) * ZCrossSection(Q, 2, Process);
 }

 return Value;
}

double PDFReweight::MassZYCrossSectionWrong(double Q, double ZY, int iflag, TString Process)
{
 double x1 = (Q / ECM) * exp(ZY);
 double x2 = (Q / ECM) * exp(ZY * (-1));

 double Value = 0.0;
 if(iflag == 0){//total
   Value = GetF1F2dYWrong(2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(5, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(-1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(-5, x1, Q) * ZCrossSection(Q, 2, Process);
 }
 if(iflag == 1){//uubar
   Value = GetF1F2dYWrong(2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(-2, x1, Q) * ZCrossSection(Q, 1, Process);
 }
 if(iflag == 2){//ddbar
   Value = GetF1F2dYWrong(1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-1, x1, Q) * ZCrossSection(Q, 2, Process);
 }
 if(iflag == 3){//gluon
   Value = GetF1F2dYWrong(3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(5, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(-5, x1, Q) * ZCrossSection(Q, 2, Process);
 }
 if(iflag == 4){//u-type
   Value = GetF1F2dYWrong(2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(-2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(-4, x1, Q) * ZCrossSection(Q, 1, Process);
 }
 if(iflag == 5){//d-type
   Value = GetF1F2dYWrong(1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(5, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-5, x1, Q) * ZCrossSection(Q, 2, Process);
 }
 if(iflag == 6){//quark total
   Value = GetF1F2dYWrong(2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(5, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(-1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(-5, x1, Q) * ZCrossSection(Q, 2, Process);
 }
 if(iflag == 7){//quark uubar
   Value = GetF1F2dYWrong(2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(-2, x1, Q) * ZCrossSection(Q, 1, Process);
 }
 if(iflag == 8){//quark ddbar
   Value = GetF1F2dYWrong(1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-1, x1, Q) * ZCrossSection(Q, 2, Process);
 }
 if(iflag == 9){//quark gluon
   Value = GetF1F2dYWrong(3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(5, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(-5, x1, Q) * ZCrossSection(Q, 2, Process);
 }
 if(iflag == 10){//quark u-type
   Value = GetF1F2dYWrong(2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(4, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(-2, x1, Q) * ZCrossSection(Q, 1, Process)
         + GetF1F2dYWrong(-4, x1, Q) * ZCrossSection(Q, 1, Process);
 }
 if(iflag == 11){//quark d-type
   Value = GetF1F2dYWrong(1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(5, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-1, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-3, x1, Q) * ZCrossSection(Q, 2, Process)
         + GetF1F2dYWrong(-5, x1, Q) * ZCrossSection(Q, 2, Process);
 }

 return Value;
}

double PDFReweight::GetQuarkAFB(double left, double right, int iflag)
{
 double Value = 0.0;

 if(iflag == 1){
   double Forward = GetHadronForwardCrossSection(left, right, 10);
   double Backward = GetHadronBackwardCrossSection(left, right, 10);

   Value = (Forward - Backward) / (Forward + Backward);
 }
 if(iflag == 2){
   double Forward = GetHadronForwardCrossSection(left, right, 11);
   double Backward = GetHadronBackwardCrossSection(left, right, 11);
 
   Value = (Forward - Backward) / (Forward + Backward);
 }
 if(iflag == 1000){//pure uubar
   double Forward = GetHadronForwardCrossSection(left, right, 1000);
   double Backward = GetHadronBackwardCrossSection(left, right, 1000);

   Value = (Forward - Backward) / (Forward + Backward);
 }
 if(iflag == 2000){//pure ddbar
   double Forward = GetHadronForwardCrossSection(left, right, 2000);
   double Backward = GetHadronBackwardCrossSection(left, right, 2000);

   Value = (Forward - Backward) / (Forward + Backward);
 }

 return Value;
}

double PDFReweight::GetQuarkAFBFraction(double left, double right, int iflag)
{
 double uuForward = GetHadronForwardCrossSection(left, right, 10);
 double uuBackward = GetHadronBackwardCrossSection(left, right, 10);

 double ddForward = GetHadronForwardCrossSection(left, right, 11);
 double ddBackward = GetHadronBackwardCrossSection(left, right, 11);

 double uuValue = (uuForward - uuBackward) / (uuForward + uuBackward);
 double ddValue = (ddForward - ddBackward) / (ddForward + ddBackward);

 double Value = 0.0;

 if(iflag == 1) Value = uuValue / (uuValue + ddValue);
 if(iflag == 2) Value = ddValue / (uuValue + ddValue);

 return Value;
}

double PDFReweight::GetRf(double left, double right, int iflag, TString Process)
{
 double Value = 0.0;

 if(Process == "Integral"){
   double uuForward = GetHadronForwardCrossSection(left, right, 7);
   double uuBackward = GetHadronBackwardCrossSection(left, right, 7);
   double uuAFB = (uuForward - uuBackward) / (uuForward + uuBackward);
   double ccAFB = uuAFB;

   double ddForward = GetHadronForwardCrossSection(left, right, 8);
   double ddBackward = GetHadronBackwardCrossSection(left, right, 8);
   double ddAFB = (ddForward - ddBackward) / (ddForward + ddBackward);
   double ssAFB = ddAFB;
   double bbAFB = ddAFB;

   double uuXsec = GetHadronTotalCrossSection(left, right, 7);
   double ddXsec = GetHadronTotalCrossSection(left, right, 8);
   double ssXsec = GetHadronTotalCrossSection(left, right, 300);
   double ccXsec = GetHadronTotalCrossSection(left, right, 400);
   double bbXsec = GetHadronTotalCrossSection(left, right, 500);
   double Total = GetHadronTotalCrossSection(left, right, 6);

   double uuFrac = uuXsec / Total;
   double ddFrac = ddXsec / Total;
   double ssFrac = ssXsec / Total;
   double ccFrac = ccXsec / Total;
   double bbFrac = bbXsec / Total;

   if(iflag == 1) Value = ddAFB * ddFrac;
   if(iflag == 2) Value = uuAFB * uuFrac;
   if(iflag == 3) Value = ssAFB * ssFrac;
   if(iflag == 4) Value = ccAFB * ccFrac;
   if(iflag == 5) Value = bbAFB * bbFrac;
 }
 if(Process == "NoIntegral"){
   double BinCenter = (left + right) / 2.0;

   double uuForward = HadronCrossSection(BinCenter, 7, (TString)"F");
   double uuBackward = HadronCrossSection(BinCenter, 7, (TString)"B");
   double uuAFB = (uuForward - uuBackward) / (uuForward + uuBackward);
   double ccAFB = uuAFB;

   double ddForward = HadronCrossSection(BinCenter, 8, (TString)"F");
   double ddBackward = HadronCrossSection(BinCenter, 8, (TString)"B");
   double ddAFB = (ddForward - ddBackward) / (ddForward + ddBackward);
   double ssAFB = ddAFB;
   double bbAFB = ddAFB;

   double uuXsec = HadronCrossSection(BinCenter, 7);
   double ddXsec = HadronCrossSection(BinCenter, 8);
   double ssXsec = HadronCrossSection(BinCenter, 300);
   double ccXsec = HadronCrossSection(BinCenter, 400);
   double bbXsec = HadronCrossSection(BinCenter, 500);
   double Total = HadronCrossSection(BinCenter, 6);

   double uuFrac = uuXsec / Total;
   double ddFrac = ddXsec / Total;
   double ssFrac = ssXsec / Total;
   double ccFrac = ccXsec / Total;
   double bbFrac = bbXsec / Total;

   if(iflag == 1) Value = ddAFB * ddFrac;
   if(iflag == 2) Value = uuAFB * uuFrac;
   if(iflag == 3) Value = ssAFB * ssFrac;
   if(iflag == 4) Value = ccAFB * ccFrac;
   if(iflag == 5) Value = bbAFB * bbFrac;
 }

 return Value;
}



  ////////////////////
  ////  Integral  ////
  ////////////////////


//dsigma in mass range in quark level
double PDFReweight::GetTotalCrossSection(double left, double right, int iflag)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 cout<<"Start Integral Quark CrossSection: ["<<left<<", "<<right<<"]"<<endl;
 double Value = Simpson(&PDFHelper::ZCrossSection, left, right, iflag, (TString)"");

 return Value;
}

double PDFReweight::GetForwardCrossSection(double left, double right, int iflag)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 cout<<"Start Integral Forward Quark CrossSection: ["<<left<<", "<<right<<"]"<<endl;
 double Value = Simpson(&PDFHelper::ZCrossSection, left, right, iflag, (TString)"F");

 return Value;
}

double PDFReweight::GetBackwardCrossSection(double left, double right, int iflag)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 cout<<"Start Integral Backward Quark CrossSection: ["<<left<<", "<<right<<"]"<<endl;
 double Value = Simpson(&PDFHelper::ZCrossSection, left, right, iflag, (TString)"B");

 return Value;
}

//dsigma in mass range in hadron level
double PDFReweight::GetHadronTotalCrossSection(double left, double right, int iflag, TString Process)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 cout<<"Start Integral Hadron CrossSection: ["<<left<<", "<<right<<"]"<<endl;
 double Value = Simpson(&PDFHelper::HadronCrossSection, left, right, iflag, (TString)Process);

 return Value;
}

double PDFReweight::GetHadronForwardCrossSection(double left, double right, int iflag)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 cout<<"Start Integral Forward Hadron CrossSection: ["<<left<<", "<<right<<"]"<<endl;
 double Value = Simpson(&PDFHelper::HadronCrossSection, left, right, iflag, (TString)"F");

 return Value;
}

double PDFReweight::GetHadronBackwardCrossSection(double left, double right, int iflag)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
// cout<<"Start Integral Backward Hadron CrossSection: ["<<left<<", "<<right<<"]"<<endl;
 double Value = Simpson(&PDFHelper::HadronCrossSection, left, right, iflag, (TString)"B");

 return Value;
}

double PDFReweight::GetHadronWrongCrossSection(double left, double right, int iflag, TString Process)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 cout<<"Start Integral Wrong Hadron CrossSection: ["<<left<<", "<<right<<"]"<<endl;
 double Value = Simpson(&PDFHelper::WrongHadronCrossSection, left, right, iflag, (TString)Process);

 return Value;
}

//dsigma/dZY in a mass range
double PDFReweight::GetZYCrossSection(double ZY, double massleft, double massright, int iflag, TString Process)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;

 double Value = Simpson(&PDFHelper::MassZYCrossSection, massleft, massright, ZY, iflag, Process);

 return Value;
}

double PDFReweight::GetZYCrossSectionWrong(double ZY, double massleft, double massright, int iflag, TString Process)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 
 double Value = Simpson(&PDFHelper::MassZYCrossSectionWrong, massleft, massright, ZY, iflag, Process);

 return Value;
}

//dsigma in ZY range and mass range
double PDFReweight::GetMassZYCrossSection(double massleft, double massright, double zyleft, double zyright, int iflag, TString Process)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 cout<<"Start Integral Hadron CrossSection: Mass["<<massleft<<", "<<massright<<"], ZY["<<zyleft<<", "<<zyright<<"]"<<endl;
 double Value = Simpson(&PDFHelper::GetZYCrossSection, zyleft, zyright, massleft, massright, iflag, (TString)Process);

 return Value;
}

double PDFReweight::GetMassZYCrossSectionWrong(double massleft, double massright, double zyleft, double zyright, int iflag, TString Process)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 cout<<"Start Integral Wrong Hadron CrossSection: Mass["<<massleft<<", "<<massright<<"], ZY["<<zyleft<<", "<<zyright<<"]"<<endl;
 double Value = Simpson(&PDFHelper::GetZYCrossSectionWrong, zyleft, zyright, massleft, massright, iflag, (TString)Process);

 return Value;
}



#endif
