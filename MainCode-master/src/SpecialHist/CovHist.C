#include "SpecialHist/CovHist.h"

using namespace std;

CovHist::CovHist(int length)
{
 this->length = length;

 DataPoint = new double[length];
}

void CovHist::DefineHist(TString name, TString title, int nbin, double left, double right)
{
 for(int i = 0; i < length; i++){
   myHist[i] = new TH1D(name + "_E" + (int)i, title + "_E" + (int)i, nbin, left, right);
   myHist[i]->Sumw2();

   CovHist_1d.push_back(myHist[i]);
 }

 HistCentral = new TH1D(name + (TString)"_Central", title + (TString)"_Central", nbin, left, right);
 HistError = new TH1D(name + (TString)"_Error", title + (TString)"_Error", nbin, left, right);

 CovarianceHist = new TH2D(name + (TString)"_Covariance", title + (TString)"_Covariance", nbin, left, right, nbin, left, right);
 CorrelationHist = new TH2D(name + (TString)"_Correlation", title + (TString)"_Correlation", nbin, left, right, nbin, left, right);
}

void CovHist::InputHist(vector<TH1D *> v_hist, TString name, TString title, int nbin, double left, double right)
{
 for(int i = 0; i < v_hist.size(); i++){
   myHist[i] = (TH1D *)(v_hist.at(i))->Clone(name + "_E" + (int)i);
   CovHist_1d.push_back(myHist[i]);
 }

 HistCentral = new TH1D(name + (TString)"_Central", title + (TString)"_Central", nbin, left, right);
 HistError = new TH1D(name + (TString)"_Error", title + (TString)"_Error", nbin, left, right);

 CovarianceHist = new TH2D(name + (TString)"_Covariance", title + (TString)"_Covariance", nbin, left, right, nbin, left, right);
 CorrelationHist = new TH2D(name + (TString)"_Correlation", title + (TString)"_Correlation", nbin, left, right, nbin, left, right);
}

void CovHist::Fill(double par, double weight, int i)
{
 myHist[i]->Fill(par, weight);
}

void CovHist::GetUncertainty()
{
 for(int ibin = 1; ibin <= myHist[0]->GetNbinsX(); ibin++){
   for(int i = 0; i < length; i++){
     DataPoint[i] = myHist[i]->GetBinContent(ibin);
     v_DataPoint[ibin].push_back(DataPoint[i]);
   }
   DataMean = CalculateMean(v_DataPoint[ibin]);
   DataRMS = CalculateRMS(DataPoint);

   HistCentral->SetBinContent(ibin, DataMean);
   HistCentral->SetBinError(ibin, myHist[0]->GetBinError(ibin));

   HistError->SetBinContent(ibin, DataRMS);
   HistError->SetBinError(ibin, 0);
 }

 for(int ibinx = 1; ibinx <= myHist[0]->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= myHist[0]->GetNbinsX(); ibiny++){
     CovarianceValue = CalculateCovariance(v_DataPoint[ibinx], HistCentral->GetBinContent(ibinx), v_DataPoint[ibiny], HistCentral->GetBinContent(ibiny));
     CovarianceHist->SetBinContent(ibinx, ibiny, CovarianceValue);

     CorrelationHist->SetBinContent(ibinx, ibiny, CovarianceValue / (HistError->GetBinContent(ibinx) * HistError->GetBinContent(ibiny)));
   }
 }
}

void CovHist::DeleteHist()
{
 for(int i = 0; i < length; i++){
   delete myHist[i];
 }

 delete HistCentral;
 delete HistError;
 delete CovarianceHist;
 delete CorrelationHist;

 CovHist_1d.clear();
}

void CovHist::Add(CovHist* hist1)
{
 for(int i = 0; i < CovHist_1d.size(); i++){
   CovHist_1d.at(i)->Add((hist1->CovHist_1d).at(i));
 }
}

void CovHist::Reset()
{
 for(int i = 0; i < length; i++){
   myHist[i]->Reset();
 }

 HistCentral->Reset();
 HistError->Reset();
 CovarianceHist->Reset();
 CorrelationHist->Reset();
}

void CovHist::Write()
{
 for(int i = 0; i < length; i++){
   myHist[i]->Write();
 }
 HistCentral->Write();
 HistError->Write();
 CovarianceHist->Write();
 CorrelationHist->Write();
}

