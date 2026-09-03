#ifndef Covariance_cxx
#define Covariance_cxx

#include "Tools/Tools.h"

using namespace std;

double CalculateCovariance(vector<double> X, double Xmean, vector<double> Y, double Ymean)
{
 double Covariance = 0;
 double par;

 TH1D* h1 = new TH1D("tool", "tool", 1, -100000.0, 100000.0);
 for(int i = 0; i < X.size(); i++){
   par = (X.at(i) - Xmean) * (Y.at(i) - Ymean);

   if(par < 100000.0 && par > -100000.0) h1->Fill(par, 1);
   if(par > 100000.0 || par < -100000.0) cout<<"ERROR: in Covariance.C, please enlarge the range for calculate mean."<<endl;
 }

 Covariance = h1->GetMean();
 delete h1;

 return Covariance;
}

#endif
