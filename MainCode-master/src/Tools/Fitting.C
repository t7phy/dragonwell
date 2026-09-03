#ifndef Fitting_cxx
#define Fitting_cxx

#include "Tools/Tools.h"
#include "RootCommon.h"

using namespace std;

void Chi2Fitting(TH1D* h1, TF1* &fitting)
{
 double par[3];
 double Min_chi2;
 double stwError;
 double stw;
 double stw1;
 fitting = new TF1("fitting", "[0]*x*x+[1]*x+[2]", h1->GetBinCenter(1), h1->GetBinCenter(h1->GetNbinsX()));
 h1->Fit(fitting,"W");
 fitting->GetParameters(par);

 Min_chi2 = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);
 cout<<"Min_chi2= "<<Min_chi2<<endl;

 stw1 = sqrt(1 / par[0]) - par[1] / (2 * par[0]);
 stw = -par[1] / (2 * par[0]);
 stwError = stw1 - stw;
 cout<<"stw = "<<stw<<endl;
 cout<<"stwError = "<<stwError<<endl;

}

void Chi2Fitting(TH1D* h1, TF1* &fitting, double &stwResult, double &stwResultErr)
{
 double par[3];
 double Min_chi2;
 double stwError;
 double stw;
 double stw1;
 fitting = new TF1("fitting", "[0]*x*x+[1]*x+[2]", h1->GetBinCenter(1), h1->GetBinCenter(h1->GetNbinsX()));
 h1->Fit(fitting,"WQ");
 fitting->GetParameters(par);
 
 Min_chi2 = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);
 
 stw1 = sqrt(1 / par[0]) - par[1] / (2 * par[0]);
 stw = -par[1] / (2 * par[0]);
 stwError = stw1 - stw;
 cout<<"Min_chi2= "<<Min_chi2<<" Central: "<<stw<<" Error: "<<stwError<<endl;

 stwResult = stw;
 stwResultErr = stwError;
}

void Chi2Fitting(TH1D* h1, TF1* &fitting, double &stwResult, double &stwResultErr, double chi2)
{
 double par[3];
 double Min_chi2;
 double stwError;
 double stw;
 double stw1;
 double stw2;
 double stw3;
 fitting = new TF1("fitting", "[0]*x*x+[1]*x+[2]", h1->GetBinCenter(1), h1->GetBinCenter(h1->GetNbinsX()));
 h1->Fit(fitting,"WQ");
 fitting->GetParameters(par);

 Min_chi2 = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);

 stw1 = sqrt(1 / par[0]) - par[1] / (2 * par[0]);
 stw = -par[1] / (2 * par[0]);
 stw2 = -par[1] / (2 * par[0]) + (sqrt(par[1] * par[1] - 4 * par[0] * par[2] + 4 * par[0] * chi2) / (2 * par[0]));
 stw3 = -par[1] / (2 * par[0]) - (sqrt(par[1] * par[1] - 4 * par[0] * par[2] + 4 * par[0] * chi2) / (2 * par[0]));
 stwError = stw1 - stw;
 cout<<"Min_chi2= "<<Min_chi2<<" Central: "<<stw<<" Error: "<<stwError<<endl;
 cout<<"Chi2 = "<<chi2<<" solution1 "<<stw2<<" solution2 "<<stw3<<endl;

 stwResult = stw;
 stwResultErr = stwError;
}

double Chi2Solution(vector<double> X, vector<double> Y, double Tol)
{
 double Solution = 0.0;
 double Solution1 = 0.0;
 double Solution2 = 0.0;

 if(X.size() != Y.size()){
   cout<<"ERROR! Length of X and Y doesn't match."<<endl;
   return -999.0;
 }

 TGraph* g;
 TF1* f;

 map<double, double> XYmap;
 for(int i = 0; i < X.size(); i++){
   XYmap[Y.at(i)] = X.at(i);
 }

 auto iter = XYmap.begin();
 double Xcentral = iter->second;

 g = new TGraph(X.size());

 for(int ibin = 1; ibin <= X.size(); ibin++){
   g->SetPointX(ibin, X.at(ibin - 1) - Xcentral);
   g->SetPointY(ibin, Y.at(ibin - 1));
 }
 g->RemovePoint(0);

 double xmin = X.at(0) - (X.at(1) - X.at(0));
 double xmax = X.at(X.size() - 1) + (X.at(X.size() - 1) - X.at(X.size() - 2));

 f = new TF1("fitting", "[0]*x*x+[1]*x+[2]", xmin - Xcentral, xmax - Xcentral);
 g->Fit(f, "W");

 double par[3];
 f->GetParameters(par);

 Solution = -par[1] / (2 * par[0]);
 Solution1 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - fabs(Tol)))) / (2 * par[0]);
 Solution2 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - fabs(Tol)))) / (2 * par[0]);

 delete f;
 delete g;

 if(fabs(Tol) < 1e-20) return Solution + Xcentral;//Central
 else if(Tol > 1e-20) return Solution2 + Xcentral;//Right
 else return Solution1 + Xcentral;//Left
}

void LinearFitting(TH1D* h1, TF1* &fitting, double* &ResultsPar, double* &ResultsParErr)
{
 cout<<"Starting linear fitting:"<<endl;

 double par[2];
 double* Results = new double[2];
 double* parErr = new double[2];

 TString HistName = h1->GetName();
 fitting = new TF1(HistName + "_Fitting", "[0]*x+[1]", h1->GetBinCenter(1), h1->GetBinCenter(h1->GetNbinsX()));
 h1->Fit(fitting);
 fitting->GetParameters(par);
 parErr = (double *)fitting->GetParErrors();

 cout<<"k = "<<par[0]<<" b = "<<par[1]<<endl;
 cout<<"k error = "<<parErr[0]<<" b error = "<<parErr[1]<<endl;

 Results[0] = par[0];
 Results[1] = par[1];

 ResultsPar = Results;
 ResultsParErr = parErr;
}

void FunctionFitting(TH1D* h1, TF1* &fitting, TString Function, double* &ResultsPar, double* &ResultsParErr, int NPar, double AddedScale)
{
 cout<<"Starting fitting for function "<<Function<<":"<<endl;

 double par[NPar];
 double* Results = new double[NPar];
 double* parErr = new double[NPar];

 TString HistName = h1->GetName();
 h1->Scale(AddedScale);
 fitting = new TF1(HistName + "_Fitting", Function, h1->GetBinCenter(1), h1->GetBinCenter(h1->GetNbinsX()));
 h1->Fit(fitting, "WQN");
 fitting->GetParameters(par);
 parErr = (double *)fitting->GetParErrors();

 for(int i = 0; i < NPar; i++){
   Results[i] = par[i] / AddedScale;
   parErr[i] = parErr[i] / AddedScale;

   fitting->SetParameter(i, Results[i]);
   fitting->SetParError(i, parErr[i]);
 }

 h1->Scale(1.0 / AddedScale);

 TF1* fitting2 = (TF1 *)fitting->Clone(HistName + "_Fitting2");
 h1->Fit(fitting2, "+WQ");

 ResultsPar = Results;
 ResultsParErr = parErr;
}

#endif
