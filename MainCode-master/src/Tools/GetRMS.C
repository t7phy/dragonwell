#ifndef GetRMS_h
#define GetRMS_h

#include "Tools/Tools.h"
#include "TH1D.h"

double CalculateRMS(double* num)
{
 double RMS;

 TH1D *h1 = new TH1D("RMS", "RMS", 1, -10000, 10000);

 int i = 0;
 while(num[i]){
  if(num[i] < 10000.0 && num[i] > -10000.0) h1->Fill(num[i], 1);
  if(num[i] > 10000.0 || num[i] < -10000.0){
    cout<<"ERROR: in GetRMS.C, please enlarge the range for calculate RMS. num["<<i<<"] = "<<num[i]<<endl;
  }
  i++;
 }
// std::cout<<"Total data point is "<<i<<std::endl;
 RMS = h1->GetRMS();

 delete h1;

 return RMS;
}

double CalculateRMS(vector<double> num)
{
 double Mean = 0.0;

 for(int i = 0; i < num.size(); i++){
   Mean += num.at(i);
 }

 Mean = Mean / (double)num.size();

 double RMS = 0.0;
 double RMS2 = 0.0;

 for(int i = 0; i < num.size(); i++){
   RMS2 += (num.at(i) - Mean) * (num.at(i) - Mean);
 }

 RMS = sqrt(RMS2 / (double)num.size());

 return RMS;
}

#endif
