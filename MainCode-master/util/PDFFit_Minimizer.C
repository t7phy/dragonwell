#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include "CTEQHelper/HoppetInterface.h"
#include "CTEQHelper/PDFEvolve.h"
#include "Calculation/ApplGridHelper.h"
#include "Calculation/FastNLOHelper.h"
#include "Calculation/Dataset.h"
#include "Calculation/DataPoint.h"
#include "Calculation/Config.h"
#include "Calculation/QCDSet.h"
#include "Calculation/ThreadChi2.h"
#include "Calculation/PDFChi2.h"
#include "Minuit2/FunctionMinimum.h"
#include "Minuit2/MnUserParameterState.h"
#include "Minuit2/MnMigrad.h"
#include "Minuit2/MnUserFcn.h"
#include "Minuit2/MnHesse.h"
#include "Minuit2/MnMinos.h"
#include "Minuit2/MnContours.h"
#include "Minuit2/MnPlot.h"

#include "Minuit2/FumiliFCNBase.h"
#include "Minuit2/FumiliMinimizer.h"
#include "Minuit2/MnFumiliMinimize.h"
#include "Minuit2/FumiliStandardChi2FCN.h"

#include "Math/IFunction.h"
#include "Minuit2/Minuit2Minimizer.h"
#include "Math/Functor.h"

#include "Calculation/GlobalFittingCore.h"

using namespace std;

GlobalFittingCore FCN;

double fchi2(const double *par)
{
  vector<double> vpar;
  for(int i = 0; i < FCN.m_setting->GetNPar(); i++){
    //cout<<par[i]<<endl;
    vpar.push_back(par[i]);
  }

  double f = FCN.chi2(vpar);

  cout<<"fchi2 = "<<f<<endl;

  return f;
}
int main(int argc, char** argv)
{
 int MaxCall = 1e9, printLevel = 0;
 double Tolerance = 1e-6;

 FCN.Initialize();

 int Npar = FCN.upar.VariableParameters();
 cout<<"Npar "<<Npar<<endl;

 ROOT::Math::Functor f(&fchi2, Npar);

 string algoname = "minimize";
// ROOT::Math::Minimizer* min = new ROOT::Minuit2::Minuit2Minimizer(algoname.c_str()) ;
 ROOT::Minuit2::Minuit2Minimizer* min = new ROOT::Minuit2::Minuit2Minimizer(algoname.c_str()) ;

 min->SetMaxFunctionCalls(MaxCall);
 min->SetTolerance(Tolerance);
 min->SetPrintLevel(2);
 min->SetFunction(f);

 for(int i = 0; i < Npar; i++){
   cout<<i<<" "<<FCN.upar.Name(i)<<" "<<FCN.upar.Value(i)<<" "<<FCN.upar.Error(i)<<" ";
   cout<<FCN.upar.Parameter(i).LowerLimit()<<" "<<FCN.upar.Parameter(i).UpperLimit()<<endl;

   min->SetLimitedVariable(i, FCN.upar.Name(i),
                              FCN.upar.Value(i),
                              FCN.upar.Error(i),
                              FCN.upar.Parameter(i).LowerLimit(),
                              FCN.upar.Parameter(i).UpperLimit());
 }

 cout<<"Algorithm: "<<algoname<<endl;

 min->Minimize();
 cout<<"Minimum: "<<min->MinValue()<<endl;

 ROOT::Minuit2::MnUserParameters FinalParam = min->State().Parameters();

 vector<double> pars = FinalParam.Params();
 vector<double> parerrs = FinalParam.Errors();
 FCN.Finalize(pars, parerrs);

 return 1;
}

