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
#include "Calculation/Iterate.h"
#include "Minuit2/FunctionMinimum.h"
#include "Minuit2/MnUserParameterState.h"
#include "Minuit2/MnUserCovariance.h"
#include "Minuit2/MnSimplex.h"
#include "Minuit2/MnMigrad.h"
#include "Minuit2/MnMinimize.h"
#include "Minuit2/MnFumiliMinimize.h"
#include "Minuit2/MnHesse.h"
#include "Minuit2/MnMinos.h"
#include "Minuit2/MnContours.h"
#include "Minuit2/MnPlot.h"
#include "Minuit2/MnPrint.h"
#include "Calculation/GlobalFittingCore.h"

using namespace std;

int main(int argc, char** argv)
{
 GlobalFittingCore FCN;
 FCN.Initialize();

 for(int i = 0; i < FCN.setting.LFit; i++){

   cout<<"Starting "<<i + 1<<" Fit: "<<endl;
   FCN.ResetFit();

   ROOT::Minuit2::FunctionMinimum* min = nullptr;

   if(FCN.setting.AlgorithmName == "Simplex"){
     ROOT::Minuit2::MnSimplex migrad(FCN, FCN.upar);
     min = new ROOT::Minuit2::FunctionMinimum(migrad(FCN.setting.MaxCall));
   }
   else if(FCN.setting.AlgorithmName == "Migrad"){
     ROOT::Minuit2::MnMigrad migrad(FCN, FCN.upar);
     min = new ROOT::Minuit2::FunctionMinimum(migrad(FCN.setting.MaxCall));
   }
   else if(FCN.setting.AlgorithmName == "Minimize"){
     ROOT::Minuit2::MnMinimize migrad(FCN, FCN.upar);
     min = new ROOT::Minuit2::FunctionMinimum(migrad(FCN.setting.MaxCall));
   }
   else if(FCN.setting.AlgorithmName == "Fumili"){
     //ROOT::Minuit2::MnFumiliMinimize migrad(FCN, FCN.upar);
     //min = new ROOT::Minuit2::FunctionMinimum(migrad(FCN.setting.MaxCall));
   }

   ROOT::Minuit2::MnUserParameters FinalParam = min->UserParameters();
   vector<double> pars = FinalParam.Params();
   vector<double> parerrs = FinalParam.Errors();
   FCN.Finalize(pars, parerrs);

   FCN.UpdateParameterCentral();

   if(fabs(FCN.DeltaChi2) < 0.1) break;
 }

/*
 cout<<"Produce Hessian Matrix:"<<endl;
 ROOT::Minuit2::MnHesse hesse;
 hesse(FCN, *min);
 ROOT::Minuit2::MnUserCovariance HessianMatrix = min->UserState().Hessian();

 ofstream HessianOutput("Hessian_Minuit2.out");
 for(int i = 0; i < HessianMatrix.Nrow(); i++){
   for(int j = 0; j < HessianMatrix.Nrow(); j++){
     HessianOutput<<fixed<<setprecision(3)<<*right<<setw(15)<<HessianMatrix(i, j);
   }
   HessianOutput<<endl;
 }

 cout<<"Minimum Chi2 = "<<*min<<endl;

 Iterate* PDFErr = new Iterate();
 PDFErr->InputHessian(HessianMatrix);
*/

 return 1;
}

