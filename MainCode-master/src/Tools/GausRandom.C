#ifndef GausRandom_cxx
#define GausRandom_cxx

#include "Tools/Tools.h"
#include <iostream>
#include "TRandom3.h"

using namespace std;

void GenGausRandomList(double mean, double rms, vector<double>& list, int length)
{
 TRandom3 random(0);

 for(int ibin = 0; ibin < length; ibin++){
   double myR = random.Gaus(mean, rms);

   list.push_back(myR);
 }

 cout<<length<<" random number list has been generated."<<endl;
}

#endif
