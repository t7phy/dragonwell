#include "Tools/Tools.h"

double Simpson(double(*fcn)(double), double left, double right)
{
 double step = 0.000001;
 int ncall = (right - left) / step;

 double Value = 0.0;

 for(int i = 0; i < ncall; i++){
   double a = left + step * i;
   double b = left + step * (i + 1);
   double x1 = 0.0;
   double f1 = 0.0;

   x1 = a;
   f1 = fcn(x1);
   double term1 = f1;
   Value += f1;

   x1 = (a + b) / 2.0;
   f1 = fcn(x1);
   double term2 = 4.0 * f1;
   Value += 4.0 * f1;

   x1 = b;
   f1 = fcn(x1);
   double term3 = f1;
   Value += f1;
 }
 return (step / 6.0) * Value;
}

template<typename T>
double Simpson(T *t, double(T::*fcn)(double), double left, double right)
{
 double step = 0.000001;
 int ncall = (right - left) / step;

 double Value = 0.0;

 for(int i = 0; i < ncall; i++){
   double a = left + step * i;
   double b = left + step * (i + 1);
   double x1 = 0.0;
   double f1 = 0.0;

   x1 = a;
   f1 = (t->*fcn)(x1);
   double term1 = f1;
   Value += f1;

   x1 = (a + b) / 2.0;
   f1 = (t->*fcn)(x1);
   double term2 = 4.0 * f1;
   Value += 4.0 * f1;

   x1 = b;
   f1 = (t->*fcn)(x1);
   double term3 = f1;
   Value += f1;
 }
 return (step / 6.0) * Value;
}

double SimpsonLog10(double(*fcn)(double), double left, double right)
{
 int ncall = 10000;
 double step = (right - left) / ncall;

 double Value = 0.0;
 
 for(int i = 0; i < ncall; i++){
   double a = left + step * i; 
   double b = left + step * (i + 1);
   double x1 = 0.0;
   double f1 = 0.0;
   
   x1 = a;
   f1 = fcn(pow(10.0, x1)) * log(10) * pow(10.0, x1);
   double term1 = f1;
   Value += f1;
   
   x1 = (a + b) / 2.0;
   f1 = fcn(pow(10.0, x1)) * log(10) * pow(10.0, x1);
   double term2 = 4.0 * f1;
   Value += 4.0 * f1;
   
   x1 = b;
   f1 = fcn(pow(10.0, x1)) * log(10) * pow(10.0, x1);
   double term3 = f1;
   Value += f1;
 }

 double Result = (step / 6.0) * Value;

 return Result;
}

double Simpson(std::function<double(double)> fcn, double left, double right, int ncall, double step, bool isOutput)
{
 if(ncall == -1) ncall = (right - left) / step;
 if(step < 0) step = (right - left) / (double)ncall;

 double Value = 0.0;
 
 for(int i = 0; i < ncall; i++){
   double a = left + step * i; 
   double b = left + step * (i + 1);
   double x1 = 0.0;
   double f1 = 0.0;
   
   x1 = a;
   f1 = fcn(x1);
   double term1 = f1;
   Value += f1;
   
   x1 = (a + b) / 2.0;
   f1 = fcn(x1);
   double term2 = 4.0 * f1;
   Value += 4.0 * f1;
   
   x1 = b;
   f1 = fcn(x1);
   double term3 = f1;
   Value += f1;

   if(ncall >= 10 && i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
 }

 if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
 if(isOutput) cout<<endl;

 return (step / 6.0) * Value;
}


double SimpsonLog10(std::function<double(double)> fcn, double left, double right, int ncall, double step, bool isOutput)
{
 if(ncall == -1) ncall = (right - left) / step;
 if(step < 0) step = (right - left) / (double)ncall;

 double Value = 0.0;

 for(int i = 0; i < ncall; i++){
   double a = left + step * i;
   double b = left + step * (i + 1);
   double x1 = 0.0;
   double f1 = 0.0;

   x1 = a;
   f1 = fcn(pow(10.0, x1)) * log(10) * pow(10.0, x1);
   double term1 = f1;
   Value += f1;

   x1 = (a + b) / 2.0;
   f1 = fcn(pow(10.0, x1)) * log(10) * pow(10.0, x1);
   double term2 = 4.0 * f1;
   Value += 4.0 * f1;

   x1 = b;
   f1 = fcn(pow(10.0, x1)) * log(10) * pow(10.0, x1);
   double term3 = f1;
   Value += f1;

   if(ncall >= 10 && i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
 }

 if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
 if(isOutput) cout<<endl;

 double Result = (step / 6.0) * Value;

 return Result;
}

