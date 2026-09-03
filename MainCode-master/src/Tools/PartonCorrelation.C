#ifndef PartonCorrelation_cxx
#define PartonCorrelation_cxx

#include "TH1D.h"
#include "Tools/Tools.h"

void DrawPartonCorrelation(vector<TH1D *> Variable1, TH2D* &Correlation, TString ErrorType)
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
       Numer += (Variable1.at(2 * k - 1)->GetBinContent(ibinx) - Variable1.at(2 * k)->GetBinContent(ibinx)) * (Variable1.at(2 * k - 1)->GetBinContent(ibiny) - Variable1.at(2 * k)->GetBinContent(ibiny)) / 4.0;
       DeltaX2 += (Variable1.at(2 * k - 1)->GetBinContent(ibinx) - Variable1.at(2 * k)->GetBinContent(ibinx)) * (Variable1.at(2 * k - 1)->GetBinContent(ibinx) - Variable1.at(2 * k)->GetBinContent(ibinx)) / 4.0;
       DeltaY2 += (Variable1.at(2 * k - 1)->GetBinContent(ibiny) - Variable1.at(2 * k)->GetBinContent(ibiny)) * (Variable1.at(2 * k - 1)->GetBinContent(ibiny) - Variable1.at(2 * k)->GetBinContent(ibiny)) / 4.0;
     }
     DeltaX = sqrt(DeltaX2);
     DeltaY = sqrt(DeltaY2);
     Denom = DeltaX * DeltaY;

     if(fabs(Denom) > 1e-10) Corr = Numer / Denom;

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

void DrawCorrelationCosine(vector<TH1D *> OneNumber, vector<TH1D *> h1, TH1D* &CorrHist, TString ErrorType, int BinLeft, int BinRight)
{
 TString HistName;
 HistName = "Correlation_" +  (TString)OneNumber.at(0)->GetName() + "_" + (TString)h1.at(0)->GetName();

 int nbinx = h1.at(0)->GetNbinsX();
 double* xbinning = new double[nbinx + 1];
 xbinning[0] = h1.at(0)->GetXaxis()->GetBinLowEdge(1);
 for(int i = 1; i <= nbinx; i++){
   xbinning[i] = h1.at(0)->GetXaxis()->GetBinUpEdge(i);
 }
 CorrHist = new TH1D(HistName, HistName, nbinx, xbinning);

 int nSet = h1.size() - 1;
 if(OneNumber.size() != h1.size()){
   cout<<"ERROR! Variable1 and Variable2 don't match!"<<endl;
   return;
 }

 double Corr = 0.0;
 double Numer = 0.0;
 double Denom = 0.0;
 double DeltaX = 0.0;
 double DeltaY = 0.0;
 double DeltaX2 = 0.0;
 double DeltaY2 = 0.0;

 for(int ibin = 1; ibin <= h1.at(0)->GetNbinsX(); ibin++){
   if(BinLeft != -1 && BinRight != -1){
     if(ibin < BinLeft || ibin > BinRight) continue;
   }

   if(ErrorType == "Symmetry" || ErrorType == "Symmetry68"){
     for(int k = 1; k <= nSet / 2; k++){
       Numer += (OneNumber.at(2 * k - 1)->GetBinContent(1) - OneNumber.at(2 * k)->GetBinContent(1)) * (h1.at(2 * k - 1)->GetBinContent(ibin) - h1.at(2 * k)->GetBinContent(ibin)) / 4.0;
       DeltaX2 += (OneNumber.at(2 * k - 1)->GetBinContent(1) - OneNumber.at(2 * k)->GetBinContent(1)) * (OneNumber.at(2 * k - 1)->GetBinContent(1) - OneNumber.at(2 * k)->GetBinContent(1)) / 4.0;
       DeltaY2 += (h1.at(2 * k - 1)->GetBinContent(ibin) - h1.at(2 * k)->GetBinContent(ibin)) * (h1.at(2 * k - 1)->GetBinContent(ibin) - h1.at(2 * k)->GetBinContent(ibin)) / 4.0;
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
       Numer += (OneNumber.at(k)->GetBinContent(1) - OneNumber.at(0)->GetBinContent(1)) * (h1.at(k)->GetBinContent(ibin) - h1.at(0)->GetBinContent(ibin));
       DeltaX2 += (OneNumber.at(k)->GetBinContent(1) - OneNumber.at(0)->GetBinContent(1)) * (OneNumber.at(k)->GetBinContent(1) - OneNumber.at(0)->GetBinContent(1));
       DeltaY2 += (h1.at(k)->GetBinContent(ibin) - h1.at(0)->GetBinContent(ibin)) * (h1.at(k)->GetBinContent(ibin) - h1.at(0)->GetBinContent(ibin));
     }
     DeltaX = sqrt(DeltaX2);
     DeltaY = sqrt(DeltaY2);
     Denom = DeltaX * DeltaY;
  
     if(ErrorType == "SymmetryOneSide"){
       DeltaX = DeltaX / 1.645;
       DeltaY = DeltaY / 1.645;
     }
   }
  
   if(fabs(Denom) > 1e-10) Corr = Numer / Denom;

   if(fabs(Corr) > 1e-10) CorrHist->SetBinContent(ibin, Corr);
   if(fabs(Corr) > 1e-10) CorrHist->SetBinError(ibin, 0.00001);
 }

}

void DrawIntegralCorrelationCosine(vector<TH1D *> OneNumber, vector<TH1D *> h1, TH1D* &CorrHist, TString ErrorType)
{
 TString HistName;
 HistName = "Correlation_" +  (TString)OneNumber.at(0)->GetName() + "_" + (TString)h1.at(0)->GetName();

 int nbinx = h1.at(0)->GetNbinsX();
 double* xbinning = new double[nbinx + 1];
 xbinning[0] = h1.at(0)->GetXaxis()->GetBinLowEdge(1);
 for(int i = 1; i <= nbinx; i++){
   xbinning[i] = h1.at(0)->GetXaxis()->GetBinUpEdge(i);
 }
 CorrHist = new TH1D(HistName, HistName, nbinx, xbinning);

 int nSet = h1.size() - 1;
 if(OneNumber.size() != h1.size()){
   cout<<"ERROR! Variable1 and Variable2 don't match!"<<endl;
   return;
 }

 double Corr = 0.0;
 double Numer = 0.0;
 double Denom = 0.0;
 double DeltaX = 0.0;
 double DeltaY = 0.0;
 double DeltaX2 = 0.0;
 double DeltaY2 = 0.0;

 for(int ibin = 1; ibin <= h1.at(0)->GetNbinsX(); ibin++){
   if(ErrorType == "Symmetry" || ErrorType == "Symmetry68"){
     for(int k = 1; k <= nSet / 2; k++){
       Numer += (OneNumber.at(2 * k - 1)->Integral() - OneNumber.at(2 * k)->Integral()) * (h1.at(2 * k - 1)->GetBinContent(ibin) - h1.at(2 * k)->GetBinContent(ibin)) / 4.0;
       DeltaX2 += (OneNumber.at(2 * k - 1)->Integral() - OneNumber.at(2 * k)->Integral()) * (OneNumber.at(2 * k - 1)->Integral() - OneNumber.at(2 * k)->Integral()) / 4.0;
       DeltaY2 += (h1.at(2 * k - 1)->GetBinContent(ibin) - h1.at(2 * k)->GetBinContent(ibin)) * (h1.at(2 * k - 1)->GetBinContent(ibin) - h1.at(2 * k)->GetBinContent(ibin)) / 4.0;
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
       Numer += (OneNumber.at(k)->Integral() - OneNumber.at(0)->Integral()) * (h1.at(k)->GetBinContent(ibin) - h1.at(0)->GetBinContent(ibin));
       DeltaX2 += (OneNumber.at(k)->Integral() - OneNumber.at(0)->Integral()) * (OneNumber.at(k)->Integral() - OneNumber.at(0)->Integral());
       DeltaY2 += (h1.at(k)->GetBinContent(ibin) - h1.at(0)->GetBinContent(ibin)) * (h1.at(k)->GetBinContent(ibin) - h1.at(0)->GetBinContent(ibin));
     }
     DeltaX = sqrt(DeltaX2);
     DeltaY = sqrt(DeltaY2);
     Denom = DeltaX * DeltaY;
  
     if(ErrorType == "SymmetryOneSide"){
       DeltaX = DeltaX / 1.645;
       DeltaY = DeltaY / 1.645;
     }
   }
  
   if(fabs(Denom) > 1e-10) Corr = Numer / Denom;

   if(fabs(Corr) > 1e-10) CorrHist->SetBinContent(ibin, Corr);
   if(fabs(Corr) > 1e-10) CorrHist->SetBinError(ibin, 0.0);
 }

}

void Draw1DCorrelationCosine(vector<TH1D *> h1, vector<TH1D *> h2, vector<TH1D *> &CorrHist, TString ErrorType)
{
 TString HistName;
 HistName = "Correlation_" +  (TString)h1.at(0)->GetName() + "_" + (TString)h2.at(0)->GetName();

 int nbinx = h2.at(0)->GetNbinsX();
 double* xbinning = new double[nbinx + 1];
 xbinning[0] = h2.at(0)->GetXaxis()->GetBinLowEdge(1);
 for(int i = 1; i <= nbinx; i++){
   xbinning[i] = h2.at(0)->GetXaxis()->GetBinUpEdge(i);
 }

 CorrHist.resize(h1.at(0)->GetNbinsX());
 for(int i = 0; i < CorrHist.size(); i++){
   CorrHist.at(i) = new TH1D(HistName + (TString)"_bin_" + (int)(i + 1), HistName + (TString)"_bin_" + (int)(i + 1), nbinx, xbinning);
 }

 int nSet = h2.size() - 1;
 if(h1.size() != h2.size()){
   cout<<"ERROR! Variable1 and Variable2 don't match!"<<endl;
   return;
 }

 double Corr = 0.0;
 double Numer = 0.0;
 double Denom = 0.0;
 double DeltaX = 0.0;
 double DeltaY = 0.0;
 double DeltaX2 = 0.0;
 double DeltaY2 = 0.0;

 for(int ihist = 0; ihist < CorrHist.size(); ihist++){
   for(int ibin = 1; ibin <= h2.at(0)->GetNbinsX(); ibin++){
     if(ErrorType == "Symmetry" || ErrorType == "Symmetry68"){
       for(int k = 1; k <= nSet / 2; k++){
         Numer += (h1.at(2 * k - 1)->GetBinContent(ihist + 1) - h1.at(2 * k)->GetBinContent(ihist + 1)) * (h2.at(2 * k - 1)->GetBinContent(ibin) - h2.at(2 * k)->GetBinContent(ibin)) / 4.0;
         DeltaX2 += (h1.at(2 * k - 1)->GetBinContent(ihist + 1) - h1.at(2 * k)->GetBinContent(ihist + 1)) * (h1.at(2 * k - 1)->GetBinContent(ihist + 1) - h1.at(2 * k)->GetBinContent(ihist + 1)) / 4.0;
         DeltaY2 += (h2.at(2 * k - 1)->GetBinContent(ibin) - h2.at(2 * k)->GetBinContent(ibin)) * (h2.at(2 * k - 1)->GetBinContent(ibin) - h2.at(2 * k)->GetBinContent(ibin)) / 4.0;
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
         Numer += (h1.at(k)->GetBinContent(ihist + 1) - h1.at(0)->GetBinContent(ihist + 1)) * (h2.at(k)->GetBinContent(ibin) - h2.at(0)->GetBinContent(ibin));
         DeltaX2 += (h1.at(k)->GetBinContent(ihist + 1) - h1.at(0)->GetBinContent(ihist + 1)) * (h1.at(k)->GetBinContent(ihist + 1) - h1.at(0)->GetBinContent(ihist + 1));
         DeltaY2 += (h2.at(k)->GetBinContent(ibin) - h2.at(0)->GetBinContent(ibin)) * (h2.at(k)->GetBinContent(ibin) - h2.at(0)->GetBinContent(ibin));
       }
       DeltaX = sqrt(DeltaX2);
       DeltaY = sqrt(DeltaY2);
       Denom = DeltaX * DeltaY;
    
       if(ErrorType == "SymmetryOneSide"){
         DeltaX = DeltaX / 1.645;
         DeltaY = DeltaY / 1.645;
       }
     }
    
     if(fabs(Denom) > 1e-10) Corr = Numer / Denom;
  
     if(fabs(Corr) > 1e-10) CorrHist.at(ihist)->SetBinContent(ibin, Corr);
     if(fabs(Corr) > 1e-10) CorrHist.at(ihist)->SetBinError(ibin, 0.0);
   }
 }
}

void Draw2DCorrelationCosine(vector<TH2D *> h1, vector<TH1D *> h2, vector<vector<TH1D *>> &CorrHist, TString ErrorType)
{
 TString HistName;
 HistName = "Correlation_" +  (TString)h1.at(0)->GetName() + "_" + (TString)h2.at(0)->GetName();

 int nbinx = h2.at(0)->GetNbinsX();
 double* xbinning = new double[nbinx + 1];
 xbinning[0] = h2.at(0)->GetXaxis()->GetBinLowEdge(1);
 for(int i = 1; i <= nbinx; i++){
   xbinning[i] = h2.at(0)->GetXaxis()->GetBinUpEdge(i);
 }

 CorrHist.resize(h1.at(0)->GetNbinsX());
 for(int i = 0; i < CorrHist.size(); i++){
   CorrHist.at(i).resize(h1.at(0)->GetNbinsY());
   for(int j = 0; j < CorrHist.at(i).size(); j++){
     CorrHist.at(i).at(j) = new TH1D(HistName + (TString)"_binx_" + (int)(i + 1) + (TString)"_biny_" + (int)(j + 1), HistName + (TString)"_binx_" + (int)(i + 1) + (TString)"_biny_" + (int)(j + 1), nbinx, xbinning);
   }
 }

 int nSet = h2.size() - 1;
 if(h1.size() != h2.size()){
   cout<<"ERROR! Variable1 and Variable2 don't match!"<<endl;
   return;
 }

 double Corr = 0.0;
 double Numer = 0.0;
 double Denom = 0.0;
 double DeltaX = 0.0;
 double DeltaY = 0.0;
 double DeltaX2 = 0.0;
 double DeltaY2 = 0.0;

 for(int ihistX = 0; ihistX < CorrHist.size(); ihistX++){
   for(int ihistY = 0; ihistY < CorrHist.at(ihistX).size(); ihistY++){
     for(int ibin = 1; ibin <= h2.at(0)->GetNbinsX(); ibin++){
       if(ErrorType == "Symmetry" || ErrorType == "Symmetry68"){
         for(int k = 1; k <= nSet / 2; k++){
           Numer += (h1.at(2 * k - 1)->GetBinContent(ihistX + 1, ihistY + 1) - h1.at(2 * k)->GetBinContent(ihistX + 1, ihistY + 1)) * (h2.at(2 * k - 1)->GetBinContent(ibin) - h2.at(2 * k)->GetBinContent(ibin)) / 4.0;
           DeltaX2 += (h1.at(2 * k - 1)->GetBinContent(ihistX + 1, ihistY + 1) - h1.at(2 * k)->GetBinContent(ihistX + 1, ihistY + 1)) * (h1.at(2 * k - 1)->GetBinContent(ihistX + 1, ihistY + 1) - h1.at(2 * k)->GetBinContent(ihistX + 1, ihistY + 1)) / 4.0;
           DeltaY2 += (h2.at(2 * k - 1)->GetBinContent(ibin) - h2.at(2 * k)->GetBinContent(ibin)) * (h2.at(2 * k - 1)->GetBinContent(ibin) - h2.at(2 * k)->GetBinContent(ibin)) / 4.0;
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
           Numer += (h1.at(k)->GetBinContent(ihistX + 1, ihistY + 1) - h1.at(0)->GetBinContent(ihistX + 1, ihistY + 1)) * (h2.at(k)->GetBinContent(ibin) - h2.at(0)->GetBinContent(ibin));
           DeltaX2 += (h1.at(k)->GetBinContent(ihistX + 1, ihistY + 1) - h1.at(0)->GetBinContent(ihistX + 1, ihistY + 1)) * (h1.at(k)->GetBinContent(ihistX + 1, ihistY + 1) - h1.at(0)->GetBinContent(ihistX + 1, ihistY + 1));
           DeltaY2 += (h2.at(k)->GetBinContent(ibin) - h2.at(0)->GetBinContent(ibin)) * (h2.at(k)->GetBinContent(ibin) - h2.at(0)->GetBinContent(ibin));
         }
         DeltaX = sqrt(DeltaX2);
         DeltaY = sqrt(DeltaY2);
         Denom = DeltaX * DeltaY;
      
         if(ErrorType == "SymmetryOneSide"){
           DeltaX = DeltaX / 1.645;
           DeltaY = DeltaY / 1.645;
         }
       }
      
       if(fabs(Denom) > 1e-10) Corr = Numer / Denom;
    
       if(fabs(Corr) > 1e-10) CorrHist.at(ihistX).at(ihistY)->SetBinContent(ibin, Corr);
       if(fabs(Corr) > 1e-10) CorrHist.at(ihistX).at(ihistY)->SetBinError(ibin, 0.0);
     }
   }
 }
}

#endif
