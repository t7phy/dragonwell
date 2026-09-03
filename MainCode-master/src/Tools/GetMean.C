#ifndef GetMean_h
#define GetMean_h

#include "Tools/Tools.h"
#include "TH1D.h"

double CalculateMean(double* num)
{
 double Mean;

 TH1D *h1 = new TH1D("Mean", "Mean", 1, -1000000, 1000000);

 int i = 0;
 while(num[i]){
  if(num[i] < 1000000.0 && num[i] > -1000000.0) h1->Fill(num[i], 1);
  if(num[i] > 1000000.0 || num[i] < -1000000.0) cout<<"ERROR: in GetMean.C, please enlarge the range for calculate mean."<<endl;
  i++;
 }
// std::cout<<"Total data point is "<<i<<std::endl;
 Mean = h1->GetMean();

 delete h1;

 return Mean;
}

double CalculateMean(vector<double> num)
{
 double Mean = 0.0;

 for(int i = 0; i < num.size(); i++){
   Mean += num.at(i);
 }

 Mean = Mean / (double)num.size();

 return Mean;
}

double CalculateMean(vector<double> num, vector<double> error, double &meanError)
{
 double Mean = 0.0;
 double Error = 0.0;
 double Error2 = 0.0;

 for(int i = 0; i < num.size(); i++){
   Mean += num.at(i);
   Error2 += error.at(i) * error.at(i);
 }

 Mean = Mean / (double)num.size();
 Error = sqrt(Error2) / num.size();

 meanError = Error;

 return Mean;
}

double CalculateMean(vector<double> num, vector<double> error, vector<double> width, double &meanError)
{
 double Mean = 0.0;
 double Error = 0.0;
 double Error2 = 0.0;
 double TotalLength = 0.0;

 for(int i = 0; i < num.size(); i++){
   TotalLength += width.at(i);
   Mean += num.at(i) * width.at(i);
   Error2 += error.at(i) * error.at(i) * width.at(i) * width.at(i);
 }

 Mean = Mean / TotalLength;
 Error = sqrt(Error2) / TotalLength;

 meanError = Error;

 return Mean;
}

#endif
