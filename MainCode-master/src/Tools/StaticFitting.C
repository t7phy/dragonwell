#ifndef StaticFitting_cxx
#define StaticFitting_cxx

#include "Tools/Tools.h"

/*       vector<TString> ParNames;
       vector<double> ParCenters;
       vector<double> ParSteps;
       vector<double> ParLowers;
       vector<double> ParUppers;

       ParNames.push_back((TString)"LL");
       ParNames.push_back((TString)"LT");
       ParNames.push_back((TString)"TL");
       ParNames.push_back((TString)"TT");

       for(int i = 0; i < 4; i++){
         ParCenters.push_back(1.0);
         ParSteps.push_back(0.5);
         ParLowers.push_back(0.0);
         ParUppers.push_back(2.0);
       }
       StaticFitting(ScaleFitting, ParNames, ParCenters, ParSteps, ParLowers, ParUppers);
*/

void StaticFitting(void(*fcn)(Int_t &, Double_t *, Double_t &f, Double_t *, Int_t), vector<TString> ParNames, vector<double> ParCenters, vector<double> ParSteps, vector<double> ParLowers, vector<double> ParUppers)
{
   int maxpar = ParNames.size();

   TMinuit *myMinuit = new TMinuit(maxpar);//set the number of parameters you want to fit

   myMinuit->SetMaxIterations(10000);
   myMinuit->SetFCN(fcn);
   myMinuit->SetPrintLevel(3);

//To get the n-sigma contour the error def parameter "up" has to set to n^2
   myMinuit->SetErrorDef(1.0);
///////////////////////////////////////////////////////////////////////////

   myMinuit->mncler();

   Int_t ierflg;
   Double_t arglist[10];

//To get the n-sigma contour the error def parameter "up" has to set to n^2
   arglist[0] = 1.0;
   myMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
///////////////////////////////////////////////////////////////////////////

   for(int i = 0; i < maxpar; i++){
     myMinuit->mnparm(i, ParNames.at(i), ParCenters.at(i), ParSteps.at(i), ParLowers.at(i), ParUppers.at(i), ierflg);
   }

   arglist[0] = 1000; // number of function calls
   arglist[1] = 0.1;  // tolerance(x10^3)
//   myMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);
   myMinuit->mnexcm("SIMPLEX", arglist, 2, ierflg);
   myMinuit->mnexcm("HESSE", arglist, 1, ierflg);

   //get results

   double DataPoint[maxpar];
   double DataError[maxpar];

   for(int i = 0; i < maxpar; i++){
     myMinuit->GetParameter(i, DataPoint[i], DataError[i]);
     cout<<"Parameter "<<i + 1<<": Center: "<<DataPoint[i]<<" Error: "<<DataError[i]<<endl;
   }
}




#endif
