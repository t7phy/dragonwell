#ifndef Generator_VegasSimple_h
#define Generator_VegasSimple_h

#include <iostream>
#include "RootCommon.h"

using namespace std;

class VegasSimple
{
 public:

 int NDimension = 5;
 int Ng = 50;

 int It1 = 10;
 int Ncall1 = 100;
 int It2 = 10;
 int Ncall2 = 100;
 int RandomSeed = 1234;

 bool isFirstCall = false;

 double alpha = 0.2;

 map<int, double> XLower;
 map<int, double> XUpper;
 map<int, double> DeltaX;

 double (*fcn)(vector<double> Y, double WGT);
 double (VegasSimple::*InnerFCN)(vector<double> Y, double WGT);

 map<int, int> YPosition;

 map<vector<int>, double> Xi;
 map<vector<int>, double> IntegrationValue;
 map<vector<int>, double> IntegrationError;
 map<vector<int>, double> IntegrationSigma;

 double FinalIntegrationValue = 0.0;
 double FinalIntegrationError = 0.0;

 double SIntegrationValue = 0.0;
 double SIntegrationValue2 = 0.0;
 double SWeight = 0.0;
 double SChi2 = 0.0;

 VegasSimple();
 VegasSimple(int it1, int ncall1, int it2, int ncall2, int RandomSeed, int Ndim);
 VegasSimple(int it1, int ncall1, int it2, int ncall2, int RandomSeed, int Ndim, vector<double> lower, vector<double> upper);

 virtual void InitialXi();
 virtual void Integration(bool isFirstCall = true);
 virtual void ResetXi();


 bool isSimpleFCN = false;
 virtual void SetFCN(double (*fcn)(vector<double> Y, double WGT)){this->isSimpleFCN = true;this->fcn = fcn;}

 enum class FunctionType{Constant, Constant2D};
 FunctionType myFunction;
 bool isInnerFCN = false;
 virtual void SetInnerFCN(TString FunctionName){
   this->isInnerFCN = true;

   if(FunctionName == "Constant") myFunction = FunctionType::Constant;
   if(FunctionName == "Constant2D") myFunction = FunctionType::Constant2D;

   switch(myFunction){
     case FunctionType::Constant:
         this->InnerFCN = &VegasSimple::ConstantFunction;
         break;
     case FunctionType::Constant2D:
         this->InnerFCN = &VegasSimple::Constant2DFunction;
         break;
   }
 }


 virtual void SetIntegrationRange(vector<double> lower, vector<double> upper){
   if(lower.size() != NDimension || upper.size() != NDimension){
     cout<<"ERROR! Please set the correct dimension of the integration."<<endl;
     return;
   }
   for(int i = 1; i <= NDimension; i++){
     XLower[i] = lower.at(i - 1);
     XUpper[i] = upper.at(i - 1);
     DeltaX[i] = XUpper[i] - XLower[i];
   }
 }

 virtual void DimensionSetting(int Ndim){this->NDimension = Ndim;}
 virtual void NgSetting(int Ng){this->Ng = Ng;}
 virtual void IterationSetting(int it1, int ncall1, int it2, int ncall2, int RandomSeed){
   this->It1 = it1;
   this->Ncall1 = ncall1;
   this->It2 = it2;
   this->Ncall2 = ncall2;
   this->RandomSeed = RandomSeed;
 }

 bool initRandom = true;
 double DS[2] = {16651885.0, 2868876.0};
 double DM[2] = {15184245.0, 2651554.0};
 double DX24 = 16777216.0;
 double DX48 = 281474976710656.0;
 map<int, double> Random;
 virtual void GenerateRandom();


 virtual double ConstantFunction(vector<double> Y, double WGT){return 0.0;};
 virtual double Constant2DFunction(vector<double> Y, double WGT){return 0.0;};

};
#endif
