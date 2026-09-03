#include "OptimizeHelper/FractionHist.h"

using namespace std;

void FractionHist::openFile(const char* fName)
{
 hf = new TFile(fName, "RECREATE");
}

void FractionHist::DefineHist(TString name, TString title, int nbin, double left, double right)
{
 ObsNumber++;

 for(int iObs = 1; iObs <= EVMax; iObs++){
   Obs[ObsNumber][iObs] = new TH1D(name + (TString)"_EV" + (int)iObs, title + (TString)"_EV" + (int)iObs, nbin, left, right); 
 }
}

void FractionHist::DefineHist(TString name, TString title, int nbin, double* xbins)
{
 ObsNumber++;

 for(int iObs = 1; iObs <= EVMax; iObs++){
   Obs[ObsNumber][iObs] = new TH1D(name + (TString)"_EV" + (int)iObs, title + (TString)"_EV" + (int)iObs, nbin, xbins);
 }
}

void FractionHist::Fill(int iObs, int iEV, int ibin, double Content)
{
 Obs[iObs][iEV]->SetBinContent(ibin, Content);
 Obs[iObs][iEV]->SetBinError(ibin, 0);
}

void FractionHist::saveHist()
{
 hf->cd();
 hf->Write();

 hf->Close();
}
