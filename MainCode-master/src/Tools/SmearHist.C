#ifndef SmearHist_cxx
#define SmearHist_cxx

#include "Tools/Tools.h"
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TRandom3.h"

void SmearHist(TH1D* h1, double* smear)
{
 TRandom3 random(0);

 double HistPoint, HistError;

 for(int ibin = 0; ibin < h1->GetNbinsX(); ibin++){
   double myR = random.Gaus(0, 1);
   HistPoint = h1->GetBinContent(ibin + 1) * (1 + smear[ibin] * myR);
   HistError = h1->GetBinError(ibin + 1);

   h1->SetBinContent(ibin + 1, HistPoint);
   h1->SetBinError(ibin + 1, HistError);
 }

}

void Smear2DHist(TH2D* h1, vector<vector<double>> smear)
{
 TRandom3 random(0);
 
 double HistPoint, HistError;
 
 for(int ibinx = 0; ibinx < h1->GetNbinsX(); ibinx++){
   for(int ibiny = 0; ibiny < h1->GetNbinsY(); ibiny++){

     double myR = random.Gaus(0, 1);
     HistPoint = h1->GetBinContent(ibinx + 1, ibiny + 1) * (1 + smear.at(ibinx).at(ibiny) * myR);
     HistError = h1->GetBinError(ibinx + 1, ibiny + 1);
   
     h1->SetBinContent(ibinx + 1, ibiny + 1, HistPoint);
     h1->SetBinError(ibinx + 1, ibiny + 1, HistError);
   }
 }

}

void Smear3DHist(TH3D* &h1)
{
 TRandom3 random(0);

 double HistPoint, HistError, OriginPoint;

 for(int ibinx = 1; ibinx <= h1->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= h1->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= h1->GetNbinsZ(); ibinz++){
       double myR = random.Gaus(0, 1);
       HistError = h1->GetBinError(ibinx, ibiny, ibinz);
       OriginPoint = h1->GetBinContent(ibinx, ibiny, ibinz);
       HistPoint = h1->GetBinContent(ibinx, ibiny, ibinz) * (1 + (HistError / OriginPoint) * myR);

       h1->SetBinContent(ibinx, ibiny, ibinz, HistPoint);
       h1->SetBinError(ibinx, ibiny, ibinz, HistError);
     }
   }
 }

}

#endif
