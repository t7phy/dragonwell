#include <iostream>
#include "Tools/Tools.h"
#include "Tools/SimpleIntegral.h"

using namespace std;

int main(int argc, char** argv)
{
 SimpleIntegral *run;

 run = new SimpleIntegral();
 run->InputFormula("gaus(0)");
 run->SetParameters(1.0 / sqrt(2.0 * M_PI), 0, 1);

 //double Integral1 = run->GetIntegral(-1, 1);
 //double Integral2 = run->GetIntegral(-2, 2);
 //double Integral3 = run->GetIntegral(-100, 100);

 double Integral1 = run->Simpson(&SimpleIntegral::Gaus, -1, 1);
 double Integral2 = run->Simpson(&SimpleIntegral::Gaus, -2, 2);
 double Integral3 = run->Simpson(&SimpleIntegral::Gaus, -100, 100);
 double Integral4 = run->Simpson(&SimpleIntegral::Gaus, -5, 5);


 cout<<"1sigma: "<<Integral1<<" 2sigma: "<<Integral2<<" 100sigma: "<<Integral3<<endl;
 cout<<Integral4<<endl;

 return 1;
}
