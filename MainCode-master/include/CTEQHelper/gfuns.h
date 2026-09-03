#ifndef CTEQHelper_gfuns_h
#define CTEQHelper_gfuns_h

#include "RootCommon.h"

using namespace std;

class gfuns
{
 public:

 int flag = -999;

 double a1 = 0.0, a2 = 0.0, a3 = 0.0, a4 = 0.0, a5 = 0.0, a6 = 0.0, a7 = 0.0, a8 = 0.0, a9 = 0.0, a10 = 0.0, a11 = 0.0, a12 = 0.0;
 double a13 = 0.0, a14 = 0.0, a15 = 0.0;

 int nPara = 12;

 gfuns();
 gfuns(int flag);

 virtual void SetParameter(vector<double> para){
   a1 = para.at(0);
   a2 = para.at(1);
   a3 = para.at(2);
   a4 = para.at(3);
   a5 = para.at(4);
   a6 = para.at(5);
   a7 = para.at(6);
   a8 = para.at(7);
   a9 = para.at(8);
   a10 = para.at(9);
   a11 = para.at(10);
   a12 = para.at(11);

   if(para.size() >= 13) a13 = para.at(12);

   if(para.size() >= 14) a14 = para.at(13);

   if(para.size() >= 15) a15 = para.at(14);

   nPara = para.size();
 };

 virtual void SetFlag(int flag){this->flag = flag;}

 virtual double fcn(double x);

 virtual double xstretch(double x, double xstrmin, double xstrmax){
   double pstretch = 6.0;

   double base = 1.0 / (1.0 / (pow(x, pstretch) + pow(xstrmin, pstretch)) + (1.0 - pow(xstrmax, pstretch)) / pow(xstrmax, pstretch));

   return pow(base, (1.0 / pstretch));
 }

};
#endif
