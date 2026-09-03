#ifndef vector_cxx
#define vector_cxx

#include "Tools/Tools.h"

double DeltaPhi(double Phi1, double Phi2)
{
 double Pi = TMath::Pi();

 double Value = Phi1 - Phi2;

 while (Value >= Pi) Value -= 2.0 * Pi;
 while (Value < Pi * (-1.0)) Value += 2.0 * Pi;

 return Value;
}

double CosPhi(vector<double> v1, vector<double> v2)
{
 double Value = 0.0;

 if(v1.size() != v2.size()){
   cout<<"ERROR! The length doesn't match."<<endl;
   return Value;
 }

 double xy = 0.0;
 double x2 = 0.0;
 double y2 = 0.0;
 double x = 0.0;
 double y = 0.0;
 double Numer = 0.0;
 double Denom = 0.0;

 for(int i = 0; i < v1.size(); i++){
   xy += v1.at(i) * v2.at(i);
   x2 += v1.at(i) * v1.at(i);
   y2 += v2.at(i) * v2.at(i);
 }

 x = sqrt(x2);
 y = sqrt(y2);

 Numer = xy;
 Denom = x * y;

 if(fabs(Denom) > 1e-20) Value = Numer / Denom;

 return Value;
}

#endif
