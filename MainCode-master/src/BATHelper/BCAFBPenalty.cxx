#include "BATHelper/BCMultiTemplateFitter.h"
#include "BATHelper/BCChannel.h"
#include "BATHelper/BCProcess.h"
#include "BATHelper/BCTemplate.h"

void BCMultiTemplateFitter::AddAFBPenalty(TString FChannelName, TString BChannelName)
{
 isAddAFBPenalty = true;
 this->FChannelName = FChannelName;
 this->BChannelName = BChannelName;
}

double BCMultiTemplateFitter::CalcAFBPenalty(TString FChannelName, TString BChannelName, const std::vector<double>& parameters)
{
 int FChannelIndex = GetChannelIndex(FChannelName);
 int BChannelIndex = GetChannelIndex(BChannelName);

 BCChannel* FChannel = GetChannel(FChannelIndex);
 BCChannel* BChannel = GetChannel(BChannelIndex);

 // get data
 BCTemplate* FData = FChannel->GetData();
 BCTemplate* BData = BChannel->GetData();

 // get histogram
 TH1D* FHist = FData->GetHistogram();
 TH1D* BHist = BData->GetHistogram();

 TH1D* Forward = FData->GetExpectation();
 TH1D* Backward = BData->GetExpectation();

 TH1D* AFBHist = (TH1D *)FHist->Clone("AFBHist");
 AFBHist->Reset();
 AFBFunction(FHist, BHist, AFBHist);

 TH1D* AFB = (TH1D *)Forward->Clone("AFB");
 AFB->Reset();
 AFBFunction(Forward, Backward, AFB);

 //for(int ibin = 1; ibin <= FHist->GetNbinsX(); ibin++){
 //  cout<<"F = "<<FHist->GetBinContent(ibin)<<" FError = "<<FHist->GetBinError(ibin)<<" B = "<<BHist->GetBinContent(ibin)<<" BError = "<<BHist->GetBinError(ibin)<<endl;
 //}
 //for(int ibin = 1; ibin <= FHist->GetNbinsX(); ibin++){
 //  cout<<"Forward = "<<Forward->GetBinContent(ibin)<<" FError = "<<Forward->GetBinError(ibin)<<" Backward = "<<Backward->GetBinContent(ibin)<<" BError = "<<Backward->GetBinError(ibin)<<endl;
 //}


 double Chi2 = CalculateChi2WithData(AFB, AFBHist);

 delete AFBHist;
 delete AFB;

 return -0.5 * Chi2;
}

