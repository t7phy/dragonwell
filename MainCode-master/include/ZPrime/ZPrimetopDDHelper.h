#ifndef ZPrime_ZPrimetopDDHelper_h
#define ZPrime_ZPrimetopDDHelper_h

#include "RootCommon.h"

using namespace std;

class ZPrimetopDDHelper
{
 public:

 int Dimension = 1;

 TFile* file;
 TH1D* Transfer1D_ee;
 TH1D* Transfer1D_mm;
 TH2D* Transfer2D_ee;
 TH2D* Transfer2D_mm;

 double Weight_ee = 0.0;
 double Weight_mm = 0.0;

 ZPrimetopDDHelper(){}
 ZPrimetopDDHelper(int n){Dimension = n;}
 virtual void openFile(TString FileName){
   file = new TFile(FileName);
 }
 virtual void RetrieveHist(TString HistName_ee, TString HistName_mm){
   if(Dimension == 1) RetrieveHist1D(HistName_ee, HistName_mm);
   if(Dimension == 2) RetrieveHist2D(HistName_ee, HistName_mm);
 }
 virtual void RetrieveHist1D(TString HistName_ee, TString HistName_mm){
   Transfer1D_ee = (TH1D *)file->Get(HistName_ee);
   Transfer1D_mm = (TH1D *)file->Get(HistName_mm);
 }
 virtual void RetrieveHist2D(TString HistName_ee, TString HistName_mm){
   Transfer2D_ee = (TH2D *)file->Get(HistName_ee);
   Transfer2D_mm = (TH2D *)file->Get(HistName_mm);
 }
 virtual void GetWeight(double par){
   int ibin_ee = Transfer1D_ee->FindBin(par);
   Weight_ee = Transfer1D_ee->GetBinContent(ibin_ee);
   int ibin_mm = Transfer1D_mm->FindBin(par);
   Weight_mm = Transfer1D_mm->GetBinContent(ibin_mm);
 }
 virtual void GetWeight(double par1, double par2){
   int ibin_ee = Transfer2D_ee->FindBin(par1, par2);
   int ibinx_ee = ibin_ee % (Transfer2D_ee->GetNbinsX() + 2);
   int ibiny_ee = ibin_ee / (Transfer2D_ee->GetNbinsX() + 2);
   Weight_ee = Transfer2D_ee->GetBinContent(ibinx_ee, ibiny_ee);
   int ibin_mm = Transfer2D_mm->FindBin(par1, par2);
   int ibinx_mm = ibin_mm % (Transfer2D_mm->GetNbinsX() + 2);
   int ibiny_mm = ibin_mm / (Transfer2D_mm->GetNbinsX() + 2);
   Weight_mm = Transfer2D_mm->GetBinContent(ibinx_mm, ibiny_mm);
 }
 virtual void GetWeightStatUp(double par){
   int ibin_ee = Transfer1D_ee->FindBin(par);
   Weight_ee = Transfer1D_ee->GetBinContent(ibin_ee) + Transfer1D_ee->GetBinError(ibin_ee);
   int ibin_mm = Transfer1D_mm->FindBin(par);
   Weight_mm = Transfer1D_mm->GetBinContent(ibin_mm) + Transfer1D_mm->GetBinError(ibin_mm);
 }
 virtual void GetWeightStatUp(double par1, double par2){
   int ibin_ee = Transfer2D_ee->FindBin(par1, par2);
   int ibinx_ee = ibin_ee % (Transfer2D_ee->GetNbinsX() + 2);
   int ibiny_ee = ibin_ee / (Transfer2D_ee->GetNbinsX() + 2);
   Weight_ee = Transfer2D_ee->GetBinContent(ibinx_ee, ibiny_ee) + Transfer2D_ee->GetBinError(ibinx_ee, ibiny_ee);
   int ibin_mm = Transfer2D_mm->FindBin(par1, par2);
   int ibinx_mm = ibin_mm % (Transfer2D_mm->GetNbinsX() + 2);
   int ibiny_mm = ibin_mm / (Transfer2D_mm->GetNbinsX() + 2);
   Weight_mm = Transfer2D_mm->GetBinContent(ibinx_mm, ibiny_mm) + Transfer2D_mm->GetBinError(ibinx_mm, ibiny_mm);
 }
 virtual void GetWeightStatDown(double par){
   int ibin_ee = Transfer1D_ee->FindBin(par);
   Weight_ee = Transfer1D_ee->GetBinContent(ibin_ee) - Transfer1D_ee->GetBinError(ibin_ee);
   int ibin_mm = Transfer1D_mm->FindBin(par);
   Weight_mm = Transfer1D_mm->GetBinContent(ibin_mm) - Transfer1D_mm->GetBinError(ibin_mm);
 }
 virtual void GetWeightStatDown(double par1, double par2){
   int ibin_ee = Transfer2D_ee->FindBin(par1, par2);
   int ibinx_ee = ibin_ee % (Transfer2D_ee->GetNbinsX() + 2);
   int ibiny_ee = ibin_ee / (Transfer2D_ee->GetNbinsX() + 2);
   Weight_ee = Transfer2D_ee->GetBinContent(ibinx_ee, ibiny_ee) - Transfer2D_ee->GetBinError(ibinx_ee, ibiny_ee);
   int ibin_mm = Transfer2D_mm->FindBin(par1, par2);
   int ibinx_mm = ibin_mm % (Transfer2D_mm->GetNbinsX() + 2);
   int ibiny_mm = ibin_mm / (Transfer2D_mm->GetNbinsX() + 2);
   Weight_mm = Transfer2D_mm->GetBinContent(ibinx_mm, ibiny_mm) - Transfer2D_mm->GetBinError(ibinx_mm, ibiny_mm);
 }

 virtual ZPrimetopDDHelper* Clone(int i){
   ZPrimetopDDHelper* ptr = new ZPrimetopDDHelper();
   if(Dimension == 1){
     ptr->Transfer1D_ee = (TH1D *)this->Transfer1D_ee->Clone((TString)Transfer1D_ee->GetName() + "_" + i);
     ptr->Transfer1D_mm = (TH1D *)this->Transfer1D_mm->Clone((TString)Transfer1D_mm->GetName() + "_" + i);
   }
   if(Dimension == 2){
     ptr->Transfer2D_ee = (TH2D *)this->Transfer2D_ee->Clone((TString)Transfer2D_ee->GetName() + "_" + i);
     ptr->Transfer2D_mm = (TH2D *)this->Transfer2D_mm->Clone((TString)Transfer2D_mm->GetName() + "_" + i);
   }
   return ptr;
 }

};
#endif
