#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include "TMinuitHelper/TMinuitHelper.h"
#include <Minuit2/FCNBase.h>
#include "Minuit2/FunctionMinimum.h"
#include "Minuit2/MnUserParameterState.h"
#include "Minuit2/MnUserCovariance.h"
#include "Minuit2/MnMigrad.h"
#include "Minuit2/MnMinimize.h"
#include "Minuit2/MnHesse.h"
#include "Minuit2/MnMinos.h"
#include "Minuit2/MnContours.h"
#include "Minuit2/MnPlot.h"
#include "Minuit2/MnPrint.h"
#include "Minuit2/MnUserParameters.h"

using namespace std;

void TestFCN(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 double x1 = par[0];
 double x2 = par[1];
 double x3 = par[2];

 double Value = (pow(x1 - 1.0, 2) + pow(x2 - 1.0, 2) + pow(x3 - 1.0, 2));

 cout<<"Minuit1: x1 = "<<x1<<" x2 = "<<x2<<" x3 = "<<x3<<" Value = "<<Value<<endl;

 f = Value;
}

class FitFCN : public ROOT::Minuit2::FCNBase
{
 public:

 virtual double operator()(const std::vector<double>&) const;
 virtual double Up() const {return theErrorDef;}
 void setErrorDef(double def) {theErrorDef = def;}

 ROOT::Minuit2::MnUserParameters upar;
 virtual void Input(TString name, double central, double step, double left, double right){
   upar.Add(name.Data(), central, step);
   upar.SetLimits(name.Data(), left, right);
 }

 private:

 double theErrorDef = 1.0;

};

double FitFCN::operator()(const std::vector<double>& par) const
{
 double x1 = par[0];
 double x2 = par[1];
 double x3 = par[2];

 double Value = (pow(x1 - 1.0, 2) + pow(x2 - 1.0, 2) + pow(x3 - 1.0, 2));

 cout<<"x1 = "<<x1<<" x2 = "<<x2<<" x3 = "<<x3<<" Value = "<<Value<<endl;

 return Value;
}

int main(int argc, char** argv)
{
 FitFCN FCN;
 FCN.Input("x1", 1.0, 0.5, -5.0, 5.0);
 FCN.Input("x2", 1.0, 0.5, -5.0, 5.0);
 FCN.Input("x3", 1.0, 0.5, -5.0, 5.0);

 ROOT::Minuit2::MnMigrad migrad(FCN, FCN.upar, 1.0);
// ROOT::Minuit2::MnMinimize migrad(FCN, FCN.upar);
 ROOT::Minuit2::FunctionMinimum min = migrad(100000);

 ROOT::Minuit2::MnUserParameters results = min.UserState().Parameters();
 ROOT::Minuit2::MnUserCovariance cov = min.UserState().Covariance();

// cout<<"run Minos:"<<endl;
// ROOT::Minuit2::MnMinos minos(FCN, min);
// for (unsigned int i = 0; i < results.Params().size(); ++i) {
//     double lower = minos.Lower(i);
//     double upper = minos.Upper(i);
//     std::cout << "Asymmetric Errors for " << results.Name(i)
//               << ": -" << lower << ", +" << upper << std::endl;
// }
 cout<<min<<endl;

 for(int i = 0; i < cov.Nrow(); i++){
   for(int j = 0; j < cov.Nrow(); j++){
     cout<<fixed<<setprecision(3)<<*right<<setw(10)<<cov(i, j);
   }
   cout<<endl;
 }


// ROOT::Minuit2::MnPrint::PrintUserParameters(results);
// ROOT::Minuit2::MnPrint::PrintCovariance(cov);

 FCN.upar.Fix("x3");

 cout<<"Produce Hessian Matrix:"<<endl;
 ROOT::Minuit2::MnHesse hesse;
 hesse(FCN, min, 100000);
 ROOT::Minuit2::MnUserCovariance HessianMatrix = min.UserState().Covariance();

 ROOT::Minuit2::MnUserParameters FinalParam = min.UserParameters();

 ofstream HessianOutput("Hessian_Minuit2.out");
 for(int i = 0; i < HessianMatrix.Nrow(); i++){
   for(int j = 0; j < HessianMatrix.Nrow(); j++){
     HessianOutput<<fixed<<setprecision(3)<<*right<<setw(10)<<HessianMatrix(i, j);
   }
   HessianOutput<<endl;
 }


 cout<<min<<endl;

 TMinuitHelper* run = new TMinuitHelper(3);
 run->SetFCN(TestFCN);
 run->Input(0, "x1", 3.0, 0.5, -5.0, 5.0);
 run->Input(1, "x2", 3.0, 0.5, -5.0, 5.0);
 run->Input(2, "x3", 3.0, 0.5, -5.0, 5.0);
// run->Exec("MIGRAD", 100000, 1.0);

 return 1;
}
