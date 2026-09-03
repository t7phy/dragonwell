#include "Tools/Tools.h"
#include "Tools/SimpleIntegral.h"

SimpleIntegral::SimpleIntegral()
{

}

void SimpleIntegral::InputFormula(TString myFormula)
{
 this->myFormula = myFormula;

 fitting = new TF1("fitting", myFormula, -1, 1);
}

void SimpleIntegral::SetParameters(double p0, double p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, double p9, double p10)
{
 fitting->SetParameters(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
}

double SimpleIntegral::GetIntegral(double left, double right)
{
 fitting->SetRange(left, right);

 double Value = fitting->Integral(left, right);

 return Value;
}

double SimpleIntegral::Gaus(double x)
{
 double Value = (1.0 / sqrt(2 * 3.1415926)) * exp((-1) * 0.5 * x * x);

 return Value;
}

double SimpleIntegral::GausPlus(double x, double y)
{
 double Value = (1.0 / sqrt(2 * 3.1415926)) * exp((-1) * 0.5 * x * x) + y;

 return Value;
}

double SimpleIntegral::GausPlus2(double x, double y, double z)
{
 double Value = (1.0 / sqrt(2 * 3.1415926)) * exp((-1) * 0.5 * x * x) + y + z;

 return Value;
}

double SimpleIntegral::Simpson(double(SimpleIntegral::*fcn)(double), double left, double right)
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
   f1 = (this->*fcn)(x1);
   double term1 = f1;
   Value += f1;

   x1 = (a + b) / 2.0;
   f1 = (this->*fcn)(x1);
   double term2 = 4.0 * f1;
   Value += 4.0 * f1;

   x1 = b;
   f1 = (this->*fcn)(x1);
   double term3 = f1;
   Value += f1;
 }
 return (step / 6.0) * Value;
}
