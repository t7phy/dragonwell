#include "RootCommon.h"
#include "Tools/Tools.h"
#include "SpecialHist/CovHist.h"

using namespace std;

int main(int argc, char** argv)
{
 TFile *file = new TFile("MC_results.root");
 TH1D* FZmass_CC[1000];
 TH1D* BZmass_CC[1000];

 TH1D* FZmass_CF[1000];
 TH1D* BZmass_CF[1000];

 TH1D* AFB_CC[1000];
 TH1D* AFB_CF[1000];

 vector<TH1D *> v_AFB_CC;
 vector<TH1D *> v_AFB_CF;

 for(int i = 0; i < 1000; i++){
   FZmass_CC[i] = (TH1D *)file->Get((TString)"FZmass_CC_E" + (int)i);
   BZmass_CC[i] = (TH1D *)file->Get((TString)"BZmass_CC_E" + (int)i);
   FZmass_CF[i] = (TH1D *)file->Get((TString)"FZmass_CF_E" + (int)i);
   BZmass_CF[i] = (TH1D *)file->Get((TString)"BZmass_CF_E" + (int)i);

   FZmass_CC[i]->Rebin(2);
   BZmass_CC[i]->Rebin(2);
   FZmass_CF[i]->Rebin(2);
   BZmass_CF[i]->Rebin(2);

   AFB_CC[i] = (TH1D *)FZmass_CC[i]->Clone((TString)"AFB_CC" + (int)i);
   AFB_CC[i]->Reset();
   AFB_CF[i] = (TH1D *)FZmass_CF[i]->Clone((TString)"AFB_CF" + (int)i);
   AFB_CF[i]->Reset();

   AFBFunction(FZmass_CC[i], BZmass_CC[i], AFB_CC[i]);
   AFBFunction(FZmass_CF[i], BZmass_CF[i], AFB_CF[i]);

   v_AFB_CC.push_back(AFB_CC[i]);
   v_AFB_CF.push_back(AFB_CF[i]);
 }

 TFile *writefile = new TFile("AFB_EnergyScale.root", "RECREATE");
 CovHist* AFB_CC_cov = new CovHist(1000);
 AFB_CC_cov->InputHist(v_AFB_CC, "AFB_CC", "AFB_CC", 35, 60, 130);
 CovHist* AFB_CF_cov = new CovHist(1000);
 AFB_CF_cov->InputHist(v_AFB_CF, "AFB_CF", "AFB_CF", 35, 60, 130);

 AFB_CC_cov->GetUncertainty();
 AFB_CF_cov->GetUncertainty();

 writefile->cd();
 writefile->Write();
 writefile->Close();

 return 1;
}
