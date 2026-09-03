#ifndef Wasymmetry_cxx
#define Wasymmetry_cxx

#include "TH1D.h"

void GetWasymmetry(TH1D* AntiLeptonEta, TH1D* LeptonEta, TH1D* &plot_Wasymmetry)
{
 if(!plot_Wasymmetry){
   plot_Wasymmetry = (TH1D *)AntiLeptonEta->Clone("h1");
   plot_Wasymmetry->Reset();
 }

 double WPlus, WMinus, WPlusError, WMinusError, Wasymmetry, WasymmetryError;

 for(int ibin = 0; ibin < LeptonEta->GetNbinsX(); ibin++){
   WPlus = AntiLeptonEta->GetBinContent(ibin + 1);
   WMinus = LeptonEta->GetBinContent(ibin + 1);
   Wasymmetry = (WPlus - WMinus) / (WPlus + WMinus);

   WPlusError = AntiLeptonEta->GetBinError(ibin + 1);
   WMinusError = LeptonEta->GetBinError(ibin + 1);
   WasymmetryError = 2 * sqrt((WPlus * WMinusError) * (WPlus * WMinusError) + (WMinus * WPlusError) * (WMinus * WPlusError)) / ((WPlus + WMinus) * (WPlus + WMinus));

   plot_Wasymmetry->SetBinContent(ibin + 1, Wasymmetry);
   plot_Wasymmetry->SetBinError(ibin + 1, WasymmetryError);
 }

}

#endif
