#include "Calculation/ApplGridHelper.h"

void ApplGridHelper::GenerateKFactor(TString FileName, TH1D* KFactor)
{
 ofstream file;
  file.open(FileName);
 file<<"#     QCD    |     EM ISR    |  gamma-gamma  |"<<endl;
 file<<"#   NNLO/NLO |    NLO/LO(EW) |  Additive     |  bin width factor "<<endl;

 TH1D* KFactorHist = (TH1D *)KFactor->Clone((TString)KFactor->GetName() + "_KFactor");

 for(int ibin = 1; ibin <= KFactorHist->GetNbinsX(); ibin++){
   file<<fixed<<setprecision(5)<<"    "<<KFactorHist->GetBinContent(ibin)<<"      1.0000        0.000E+00"<<"       ";
   double BinWidth = KFactorHist->GetXaxis()->GetBinUpEdge(ibin) - KFactorHist->GetXaxis()->GetBinLowEdge(ibin);
   BinWidth = 1.0;
   file<<fixed<<setprecision(3)<<BinWidth<<endl;
 }

}

void ApplGridHelper::GenerateKFactor(TString FileName, TString GridName, TH1D* HighOrder, vector<TString> subProcs)
{
 ofstream file;
  file.open(FileName);
 file<<"#     QCD    |     EM ISR    |  gamma-gamma  |"<<endl;
 file<<"#   NNLO/NLO |    NLO/LO(EW) |  Additive     |  bin width factor "<<endl;

 TH1D* LowOrder;
 vector<TH1D *> LowOrderSubProcs;

 if(subProcs.size() == 0){
   LowOrder = Convolute(GridName);
   LowOrder->SetName((TString)HighOrder->GetName() + "_LowOrder");
   LowOrder->SetTitle((TString)HighOrder->GetName() + "_LowOrder");
 }
 else if(subProcs.size() > 0){
   LowOrderSubProcs.resize(subProcs.size());
   for(int i = 0; i < LowOrderSubProcs.size(); i++){
     LowOrderSubProcs.at(i) = ConvoluteSubProc(GridName, SubProcIndex[subProcs.at(i)]);
   }
   LowOrder = (TH1D *)LowOrderSubProcs.at(0)->Clone((TString)HighOrder->GetName() + "_LowOrder");
   LowOrder->Reset();
   for(int i = 0; i < LowOrderSubProcs.size(); i++){
     LowOrder->Add(LowOrderSubProcs.at(i));
   }
 }

 TH1D* KFactorHist = (TH1D *)HighOrder->Clone((TString)HighOrder->GetName() + "_KFactor");
 for(int ibin = 1; ibin <= KFactorHist->GetNbinsX(); ibin++){
   double Value = HighOrder->GetBinContent(ibin) / LowOrder->GetBinContent(ibin);

   cout<<"HighOrder: "<<HighOrder->GetBinContent(ibin)<<" LowOrder: "<<LowOrder->GetBinContent(ibin)<<" KFactor: "<<Value<<endl;

   KFactorHist->SetBinContent(ibin, Value);
   KFactorHist->SetBinError(ibin, 0.0);
 }

 for(int ibin = 1; ibin <= KFactorHist->GetNbinsX(); ibin++){
   file<<fixed<<setprecision(5)<<"    "<<KFactorHist->GetBinContent(ibin)<<"      1.0000        0.000E+00"<<"       ";
   double BinWidth = KFactorHist->GetXaxis()->GetBinUpEdge(ibin) - KFactorHist->GetXaxis()->GetBinLowEdge(ibin);
   BinWidth = 1.0;
   file<<fixed<<setprecision(3)<<BinWidth<<endl;
 }

}

void ApplGridHelper::GenerateKFactorppbar(TString FileName, TString GridName, TH1D* HighOrder, vector<TString> subProcs)
{
 ofstream file;
  file.open(FileName);
 file<<"#     QCD    |     EM ISR    |  gamma-gamma  |"<<endl;
 file<<"#   NNLO/NLO |    NLO/LO(EW) |  Additive     |  bin width factor "<<endl;

 TH1D* LowOrder;
 vector<TH1D *> LowOrderSubProcs;

 if(subProcs.size() == 0){
   LowOrder = Convoluteppbar(GridName);
   LowOrder->SetName((TString)HighOrder->GetName() + "_LowOrder");
   LowOrder->SetTitle((TString)HighOrder->GetName() + "_LowOrder");
 }
 else if(subProcs.size() > 0){
   LowOrderSubProcs.resize(subProcs.size());
   for(int i = 0; i < LowOrderSubProcs.size(); i++){
     LowOrderSubProcs.at(i) = ConvoluteppbarSubProc(GridName, SubProcIndex[subProcs.at(i)]);
   }
   LowOrder = (TH1D *)LowOrderSubProcs.at(0)->Clone((TString)HighOrder->GetName() + "_LowOrder");
   LowOrder->Reset();
   for(int i = 0; i < LowOrderSubProcs.size(); i++){
     LowOrder->Add(LowOrderSubProcs.at(i));
   }
 }

 TH1D* KFactorHist = (TH1D *)HighOrder->Clone((TString)HighOrder->GetName() + "_KFactor");
 for(int ibin = 1; ibin <= KFactorHist->GetNbinsX(); ibin++){
   double Value = HighOrder->GetBinContent(ibin) / LowOrder->GetBinContent(ibin);

   cout<<"HighOrder: "<<HighOrder->GetBinContent(ibin)<<" LowOrder: "<<LowOrder->GetBinContent(ibin)<<" KFactor: "<<Value<<endl;

   KFactorHist->SetBinContent(ibin, Value);
   KFactorHist->SetBinError(ibin, 0.0);
 }

 for(int ibin = 1; ibin <= KFactorHist->GetNbinsX(); ibin++){
   file<<fixed<<setprecision(5)<<"    "<<KFactorHist->GetBinContent(ibin)<<"      1.0000        0.000E+00"<<"       ";
   double BinWidth = KFactorHist->GetXaxis()->GetBinUpEdge(ibin) - KFactorHist->GetXaxis()->GetBinLowEdge(ibin);
   BinWidth = 1.0;
   file<<fixed<<setprecision(3)<<BinWidth<<endl;
 }

}

void ApplGridHelper::ReadKFactor(TString FileName)
{
 ifstream file;
  file.open(FileName.Data());

 TString skip;
 double skip_double;
 double KFactor;

 std::string FileLine;

 while(file >> skip){
   if(skip == "#"){
     getline(file, FileLine);
     cout<<FileLine<<endl;
   }
   else{
     KFactor = stod(skip.Data());
     getline(file, FileLine);     
     break;
   }
 }

 KFactorMap[FileName].push_back(KFactor);

 while(file >> skip_double){
   KFactor = skip_double;
   KFactorMap[FileName].push_back(KFactor);
   getline(file, FileLine);
 }

}

