#ifndef CalRefWZ_cxx
#define CalRefWZ_cxx

#include "Tools/Tools.h"

void CalRefWZ(TH1D* Wplus, TH1D* Wminus, TH1D* Z, TH1D* &WZRef)
{
 if(!WZRef){
   WZRef = (TH1D *)Wplus->Clone("WZRef");
 }

 for(int ibin = 0; ibin < Wplus->GetNbinsX(); ibin++){
   double WplusPoint = Wplus->GetBinContent(ibin + 1);
   double WminusPoint = Wminus->GetBinContent(ibin + 1);
   double ZPoint = Z->GetBinContent(ibin + 1);

   double WplusError = Wplus->GetBinError(ibin + 1);
   double WminusError = Wminus->GetBinError(ibin + 1);
   double ZError = Z->GetBinError(ibin + 1);

   double DataPoint = (WplusPoint + WminusPoint) / ZPoint;
   double DataError = sqrt((WplusError * WplusError) / (ZPoint * ZPoint) + (WminusError * WminusError) / (ZPoint * ZPoint) + (WplusPoint + WminusPoint) * (WplusPoint + WminusPoint) * ZError * ZError / (ZPoint * ZPoint * ZPoint * ZPoint));

   WZRef->SetBinContent(ibin + 1, DataPoint);
   WZRef->SetBinError(ibin + 1, DataError);
 }

}
#endif
