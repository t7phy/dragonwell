#ifndef Chi2_cxx
#define Chi2_cxx

#include "Tools/Tools.h"
#include <iostream>

using namespace std;

double CalculateChi2(TH1D* h1, TH1D* h2)
{
 bool isOutput = false;

 double Chi2 = 0;
 double N1, N2, N1Error, N2Error;

 for(int ibinx = 0; ibinx < h1->GetNbinsX(); ibinx++)
 {
  N1 = h1->GetBinContent(ibinx + 1);
  N2 = h2->GetBinContent(ibinx + 1);

  N1Error = h1->GetBinError(ibinx + 1);
  N2Error = h2->GetBinError(ibinx + 1);

  if(isOutput) cout<<"bin "<<ibinx + 1<<" Ratio: "<<N1 / N2<<" : Difference: "<<(N1 - N2) * (N1 - N2)<<" Error: "<<(N1Error * N1Error + N2Error * N2Error)<<endl;

  if((N1Error * N1Error + N2Error * N2Error) < 0.00000000001){
    if(isOutput) cout<<"INFO: The denomenator is zero, skip this point."<<endl;
    continue;
  }

  Chi2 += (N1 - N2) * (N1 - N2) / (N1Error * N1Error + N2Error * N2Error);
 }

 if(isOutput) cout<<"Chi2: "<<Chi2<<endl;
 return Chi2;

}

double CalculateChi2(TH2D* h1, TH2D* h2)
{
 bool isOutput = false;

 double Chi2 = 0;
 double N1, N2, N1Error, N2Error;

 for(int ibinx = 0; ibinx < h1->GetNbinsX(); ibinx++){
   for(int ibiny = 0; ibiny < h1->GetNbinsY(); ibiny++){
     N1 = h1->GetBinContent(ibinx + 1, ibiny + 1);
     N2 = h2->GetBinContent(ibinx + 1, ibiny + 1);

     N1Error = h1->GetBinError(ibinx + 1, ibiny + 1);
     N2Error = h2->GetBinError(ibinx + 1, ibiny + 1);

     if(isOutput) cout<<"bin "<<ibinx + 1<<" Ratio: "<<N1 / N2<<" : Difference: "<<(N1 - N2) * (N1 - N2)<<" Error: "<<(N1Error * N1Error + N2Error * N2Error)<<endl;

     if((N1Error * N1Error + N2Error * N2Error) < 0.00000000001){
       if(isOutput) cout<<"INFO: The denomenator is zero, skip this point."<<endl;
       continue;
     }

     Chi2 += (N1 - N2) * (N1 - N2) / (N1Error * N1Error + N2Error * N2Error);
   }
 }

 if(isOutput) cout<<"Chi2: "<<Chi2<<endl;
 return Chi2;

}

double CalculateChi2(TH3D* h1, TH3D* h2)
{
 bool isOutput = false;

 double Chi2 = 0;
 double N1, N2, N1Error, N2Error;

 for(int ibinx = 1; ibinx <= h1->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= h1->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= h1->GetNbinsZ(); ibinz++){
       N1 = h1->GetBinContent(ibinx, ibiny, ibinz);
       N2 = h2->GetBinContent(ibinx, ibiny, ibinz);

       N1Error = h1->GetBinError(ibinx, ibiny, ibinz);
       N2Error = h2->GetBinError(ibinx, ibiny, ibinz);

       if(isOutput) cout<<"bin "<<ibinx<<" Ratio: "<<N1 / N2<<" : Difference: "<<(N1 - N2) * (N1 - N2)<<" Error: "<<(N1Error * N1Error + N2Error * N2Error)<<endl;

       if((N1Error * N1Error + N2Error * N2Error) < 0.00000000001){
         if(isOutput) cout<<"INFO: The denomenator is zero, skip this point."<<endl;
         continue;
       }

       Chi2 += (N1 - N2) * (N1 - N2) / (N1Error * N1Error + N2Error * N2Error);
     }
   }
 }

 if(isOutput) cout<<"Chi2: "<<Chi2<<endl;
 return Chi2;

}

double CalculateChi2(TH1D* h1, TH1D* h2, TH2D* CovarianceMatrix)
{
 bool isOutput = false;

 double Chi2 = 0;
 double N1, N2, X1m, Amn, Xn1;

 if(isOutput) cout<<"h1 bin number: "<<h1->GetNbinsX()<<endl;
 if(isOutput) cout<<"h2 bin number: "<<h2->GetNbinsX()<<endl;

 for(int ibinx = 0; ibinx < h1->GetNbinsX(); ibinx++){
   N1 = h1->GetBinContent(ibinx + 1);
   N2 = h2->GetBinContent(ibinx + 1);
   X1m = N1 - N2;
//if(ibinx == 6 || ibinx == 7) continue;
   for(int ibiny = 0; ibiny < h2->GetNbinsX(); ibiny++){
     N1 = h1->GetBinContent(ibiny + 1);
     N2 = h2->GetBinContent(ibiny + 1);
     Xn1 = N1 - N2;
//if(ibiny == 6 || ibiny == 7) continue;

     Amn = CovarianceMatrix->GetBinContent(ibinx + 1, ibiny + 1);
     if(isOutput) cout<<Amn<<" ";
     Chi2 += X1m * Amn * Xn1;
   }
   if(isOutput) cout<<endl;
 }

 return Chi2;

}

double CalculateChi2WithData(TH1D* h1, TH1D* h2)
{
 bool isOutput = false;

 if(isOutput) cout<<"NOTE: h2 should be data."<<endl;

 double Chi2 = 0;
 double N1, N2, N1Error, N2Error;

 for(int ibinx = 0; ibinx < h1->GetNbinsX(); ibinx++)
 {
  N1 = h1->GetBinContent(ibinx + 1);
  N2 = h2->GetBinContent(ibinx + 1);

  N1Error = h1->GetBinError(ibinx + 1);
  N2Error = h2->GetBinError(ibinx + 1);
  //N2Error = sqrt(h2->GetBinContent(ibinx + 1));

  if(isOutput) cout<<"bin "<<ibinx + 1<<" : Difference: "<<(N1 - N2) * (N1 - N2)<<" Error: "<<(N1Error * N1Error + N2Error * N2Error)<<endl;
  if(isOutput) cout<<"bin "<<ibinx + 1<<" N1 = "<<N1<<" N2 = "<<N2<<" N1Error = "<<N1Error<<" N2Error = "<<N2Error<<endl;

  if((N2Error * N2Error) < 1e-10){
    if(isOutput) cout<<"INFO: The denomenator is zero, skip this point."<<endl;
    continue;
  }

  Chi2 += (N1 - N2) * (N1 - N2) / (N2Error * N2Error);
 }

 if(isOutput) cout<<"Chi2: "<<Chi2<<endl;
 return Chi2;

}

double CalculateChi2(TH1D* h1, TH1D* h2, int FirstBin, int LastBin)
{
 bool isOutput = false;

 double Chi2 = 0;
 double N1, N2, N1Error, N2Error;

 for(int ibinx = FirstBin; ibinx <= LastBin; ibinx++)
 {
  N1 = h1->GetBinContent(ibinx);
  N2 = h2->GetBinContent(ibinx);

  N1Error = h1->GetBinError(ibinx);
  N2Error = h2->GetBinError(ibinx);

  if(isOutput) cout<<"bin "<<ibinx<<" Ratio: "<<N1 / N2<<" : Difference: "<<(N1 - N2) * (N1 - N2)<<" Error: "<<(N1Error * N1Error + N2Error * N2Error)<<endl;

  if((N1Error * N1Error + N2Error * N2Error) < 0.00000000001){
    if(isOutput) cout<<"INFO: The denomenator is zero, skip this point."<<endl;
    continue;
  }

  Chi2 += (N1 - N2) * (N1 - N2) / (N1Error * N1Error + N2Error * N2Error);
 }

 if(isOutput) cout<<"Chi2: "<<Chi2<<endl;
 return Chi2;

}

double CalculateChi2(TH3D* h1, TH3D* h2, int FirstYBin, int LastYBin, int FirstZBin, int LastZBin)
{
 bool isOutput = false;

 double Chi2 = 0;
 double N1, N2, N1Error, N2Error;

 for(int ibinx = 1; ibinx <= h1->GetNbinsX(); ibinx++){
   for(int ibiny = FirstYBin; ibiny <= LastYBin; ibiny++){
     for(int ibinz = FirstZBin; ibinz <= LastZBin; ibinz++){
       N1 = h1->GetBinContent(ibinx, ibiny, ibinz);
       N2 = h2->GetBinContent(ibinx, ibiny, ibinz);

       N1Error = h1->GetBinError(ibinx, ibiny, ibinz);
       N2Error = h2->GetBinError(ibinx, ibiny, ibinz);

       if(isOutput) cout<<"bin "<<ibinx<<" Ratio: "<<N1 / N2<<" : Difference: "<<(N1 - N2) * (N1 - N2)<<" Error: "<<(N1Error * N1Error + N2Error * N2Error)<<endl;

       if((N1Error * N1Error + N2Error * N2Error) < 0.00000000001){
         if(isOutput) cout<<"INFO: The denomenator is zero, skip this point."<<endl;
         continue;
       }

       Chi2 += (N1 - N2) * (N1 - N2) / (N1Error * N1Error + N2Error * N2Error);
     }
   }
 }

 if(isOutput) cout<<"Chi2: "<<Chi2<<endl;
 return Chi2;

}

double CalculateLLH(TH1D* Data, TH1D* MC)
{
 double LLH = 0.0;

 for(int ibin = 1; ibin <= Data->GetNbinsX(); ibin++){
   double x = Data->GetBinContent(ibin);
   double mu = MC->GetBinContent(ibin);

   LLH += (-1.0) * (x * log(mu) - mu);
 }

 return LLH;
}

double CalculateLLH(TH1D* Data, TH1D* MC, vector<double> DataFactorial)
{
 double LLH = 0.0;

 for(int ibin = 1; ibin <= Data->GetNbinsX(); ibin++){
   double x = Data->GetBinContent(ibin);
   double mu = MC->GetBinContent(ibin);

   LLH += (-1.0) * (x * log(mu) - mu - DataFactorial.at(ibin - 1));

   //cout<<"ibin "<<ibin<<": "<<x*log(mu)<<" "<<mu<<" "<<DataFactorial.at(ibin - 1)<<" "<<x * log(mu) - mu - DataFactorial.at(ibin - 1)<<endl;
 }

 return LLH;
}

double TranslateChi2ToPValue(double chi2, int ndf)
{  
   return 1 - ROOT::Math::chisquared_cdf(ndf, chi2);
}

double TranslateChi2ToSpartyness(double chi2, int ndf)
{
 // to be consistent with CT fortran code (9 * npt - 1) / (9 * npt) (not inverse)

 return (pow(18.0 * ndf, 1.5) / (18.0 * ndf + 1.0)) * ((6.0 / (6.0 - log(chi2 / (double)ndf))) - ((9.0 * ndf - 1.0) / (9.0 * ndf)));
}

double TLewisChi2(double S, int Npts)
{
 double xNpts = (double)Npts;
 double sigchi2 = sqrt(2.0 * xNpts);
 double S2 = S * S;

 double Value = xNpts + sigchi2 * S + 2.0 * (S2 - 1.0) / 3.0 + S * (S2 - 1.0) / (9.0 * sigchi2) - (S2 * S2 + 2.0 * S2 - 8.0) / (54.0 * xNpts);

 return Value;
}

double TranslateGaussSigmaToPValue(double sigma)
{        
   return 2 * (1 - ROOT::Math::gaussian_cdf(sigma, 1, 0));
}           
         
double TranslateChi2ToGaussSigma(double chi2, int ndf)
{
   double pvalue = TranslateChi2ToPValue(chi2, ndf);
   double min = 10;
   double max = 11;

   do
   {
      double max_p = TranslateGaussSigmaToPValue(max);
      double min_p = TranslateGaussSigmaToPValue(min);
      double mid_p = TranslateGaussSigmaToPValue((max + min) / 2);
      if (pvalue < max_p)
          max = max * 10;
      else if (pvalue > max_p && pvalue < mid_p)
          min = (max + min) / 2;
      else if (pvalue > mid_p && pvalue < min_p)
          max = (max + min) / 2;
      else if (pvalue > min_p)
          min = min / 10;
      else
          return (max + min) / 2;

      if ((max - min) < 1e-4)
         break;

   } while (1);

   return (max + min) / 2;
}

double TranslatePValueToZ(double PValue)
{
 return ROOT::Math::gaussian_quantile_c(PValue, 1.0);
}

double CalLogFactorial(double x)
{
 double Value = 0.0;
 for(int i = 1; i <= x - 1; i++){
   Value += log(i);
 }
 return Value;
}

double CalculateNormChi2(TH1D* h1, TH1D* h2)
{
 bool isOutput = false;
 
 double Chi2 = 0;
 double N1, N2, N1Error, N2Error;

 h1->Scale(1.0 / h1->Integral());
 h2->Scale(1.0 / h2->Integral());

 for(int ibinx = 0; ibinx < h1->GetNbinsX(); ibinx++)
 {
  N1 = h1->GetBinContent(ibinx + 1);
  N2 = h2->GetBinContent(ibinx + 1);
  
  N1Error = h1->GetBinError(ibinx + 1);
  N2Error = h2->GetBinError(ibinx + 1);
  
  if(isOutput) cout<<"bin "<<ibinx + 1<<" Ratio: "<<N1 / N2<<" : Difference: "<<(N1 - N2) * (N1 - N2)<<" Error: "<<(N1Error * N1Error + N2Error * N2Error)<<endl;
  
  if((N1Error * N1Error + N2Error * N2Error) < 0.00000000001){
    if(isOutput) cout<<"INFO: The denomenator is zero, skip this point."<<endl;
    continue;
  }
  
  Chi2 += (N1 - N2) * (N1 - N2) / (N1Error * N1Error + N2Error * N2Error);
 }
 
 if(isOutput) cout<<"Chi2: "<<Chi2<<endl;
 return Chi2;

}

double CalculateNormChi2(TH1D* h1, TH1D* h2, int FirstBin, int LastBin)
{
 bool isOutput = false;

 double Chi2 = 0;
 double N1, N2, N1Error, N2Error;

 h1->Scale(1.0 / h1->Integral(FirstBin, LastBin));
 h2->Scale(1.0 / h2->Integral(FirstBin, LastBin));

 for(int ibinx = FirstBin; ibinx <= LastBin; ibinx++){
   N1 = h1->GetBinContent(ibinx);
   N2 = h2->GetBinContent(ibinx);

   N1Error = h1->GetBinError(ibinx);
   N2Error = h2->GetBinError(ibinx);

   if(isOutput) cout<<"bin "<<ibinx<<" Ratio: "<<N1 / N2<<" : Difference: "<<(N1 - N2) * (N1 - N2)<<" Error: "<<(N1Error * N1Error + N2Error * N2Error)<<endl;

   if((N1Error * N1Error + N2Error * N2Error) < 0.00000000001){
     if(isOutput) cout<<"INFO: The denomenator is zero, skip this point."<<endl;
     continue;
   }

   Chi2 += (N1 - N2) * (N1 - N2) / (N1Error * N1Error + N2Error * N2Error);
 }

 if(isOutput) cout<<"Chi2: "<<Chi2<<endl;
 return Chi2;

}

double CalculateChi2(TH1D* Theory, TH1D* Data, TH1D* StaErr, TH1D* SysErr, vector<TH1D*> CorrErr)
{
 double Chi2 = 0;

 return Chi2;
}

#endif
