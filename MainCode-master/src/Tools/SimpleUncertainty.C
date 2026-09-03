#include "Tools/Tools.h"

double DivideUncertainty(TH1D* h1, TH1D* h2, int bin)
{
 double Value1 = h1->GetBinContent(bin);
 double Value2 = h2->GetBinContent(bin);
 double Error1 = h1->GetBinError(bin);
 double Error2 = h2->GetBinError(bin);
 double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2) / (Value2 * Value2);

 return Error;
}

double DivideUncertainty(double Value1, double Value2, double Error1, double Error2)// A/B A and B are independent
{
 double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2) / (Value2 * Value2);

 return Error;
}

double DivideUncertainty2(double Value1, double Value2, double Error1, double Error2)// (A-B)/A, A and B are independent
{
 //Value1 = A - B
 //Value2 = A
 //Error1 = Delta(A-B)
 //Error2 = Delta(A)

 double A = Value2;
 double B = Value2 - Value1;
 double AError = Error2;
 double BError = sqrt(Error1 * Error1 - Error2 * Error2);

 double Error = sqrt(B * B * AError * AError + A * A * BError * BError) / (A * A);

 return Error;
}

double EfficiencyUncertainty(double Value1, double Value2, double Error1, double Error2)// A/(A+B), A and B are independent
{
 //Value1 = A(Tight);
 //Value2 = A(Tight) + B(UnTight);
 //Error1 = Delta(A);
 //Error2 = Delta(A + B);
 double Tight = Value1;
 double Loose = Value2;
 double UnTight = Value2 - Value1;

 double TightError = Error1;
 double UnTightError2 = Error2 * Error2 - Error1 * Error1;

 double Error = sqrt(Tight * Tight * UnTightError2 + UnTight * UnTight * TightError * TightError) / (Loose * Loose);

 if(fabs(Loose) < 1e-20) Error = 0.0;

 return Error;
}

/*double BinomialEfficiencyUncertainty(double Value1, double Value2, double Error1, double Error2)// A/(A+B), A and B are independent
{
 //Value1 = A(Tight);
 //Value2 = A(Tight) + B(UnTight);
 //Error1 = Delta(A);
 //Error2 = Delta(A + B);
 double Tight = Value1;
 double Loose = Value2;
 double UnTight = Value2 - Value1;

 double Error = sqrt((Tight / Loose / Loose) * (1.0 - Tight / Loose));
}*/


