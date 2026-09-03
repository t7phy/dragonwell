#define TMinuitHelper_cxx
#include "TMinuitHelper/TMinuitHelper.h"

using namespace std;

TMinuitHelper::TMinuitHelper(int maxpar)
{
 this->maxpar = maxpar;

 myMinuit = new TMinuit(maxpar);

 myMinuit->SetMaxIterations(10000);
 myMinuit->SetPrintLevel(3);
 myMinuit->SetErrorDef(1.0);
 arglist[0] = 1.0;
 myMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
}

TMinuitHelper::~TMinuitHelper()
{

}

void TMinuitHelper::SetMaxIterations(int MaxIteration)
{
 isSetMaxIterations = true;
 this->MaxIteration = MaxIteration;

 myMinuit->SetMaxIterations(MaxIteration);
}

void TMinuitHelper::SetFCN(void(*fcn)(Int_t &, Double_t *, Double_t &f, Double_t *, Int_t))
{
 ////////////////////////////////////////////////////////////////////////////////
 /// Evaluate the minimisation function
 ///  Input parameters:
 ///   - npar:    number of currently variable parameters
 ///   - par:     array of (constant and variable) parameters
 ///   - flag:    Indicates what is to be calculated (see example below)
 ///   - grad:    array of gradients
 ///  Output parameters:
 ///   - fval:    The calculated function value.
 ///   - grad:    The (optional) vector of first derivatives).
 ///
 /// The meaning of the parameters par is of course defined by the user,
 /// who uses the values of those parameters to calculate their function value.
 /// The starting values must be specified by the user.
 /// Later values are determined by Minuit as it searches for the minimum
 /// or performs whatever analysis is requested by the user.
 ///
 /// Note that this virtual function may be redefined in a class derived from TMinuit.
 /// The default function calls the function specified in SetFCN
 ///
 /// Example of Minimisation function: myMinuit->SetFCN(fcn);
 /// (*fFCN)(npar,grad,fval,par,flag)

 myMinuit->SetFCN(fcn);

 myMinuit->mncler();
}

void TMinuitHelper::SetPrintLevel(int PrintLevel)
{
 isSetPrintLevel = true;
 this->PrintLevel = PrintLevel;

 myMinuit->SetPrintLevel(PrintLevel);
}

void TMinuitHelper::SetErrorDef(double ErrorDef)
{
 isSetErrorDef = true;
 this->ErrorDef = ErrorDef;

 cout<<"Default setting is Chi2,"<<endl;
 cout<<endl;
 cout<<"Chi2 should be set in 1.0"<<endl;
 cout<<"Log likelihood should be set in 0.5"<<endl;

 myMinuit->SetErrorDef(ErrorDef);

 arglist[0] = ErrorDef;
 myMinuit->mnexcm("SET ERR", arglist, 1, ierflg);

}

void TMinuitHelper::Input(int n, TString name, double center, double step, double lower, double upper)
{
 myMinuit->mnparm(n, name, center, step, lower, upper, ierflg);
}

void TMinuitHelper::Input(int n, TString name, double center, double step)
{
 myMinuit->mnparm(n, name, center, step, 0, 0, ierflg);
}

void TMinuitHelper::Exec(TString name, int MaxCall, double Tolerance)
{
 if(name == "SIMPLEX"){
   arglist[0] = MaxCall;
   arglist[1] = Tolerance * 0.001;//To be same as MIGRAD
   myMinuit->mnexcm("SIMPLEX", arglist, 2, ierflg);
 }
 if(name == "MIGRAD"){
   arglist[0] = MaxCall;
   arglist[1] = Tolerance;
   myMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);
 }
 if(name == "MINIMIZE"){
   arglist[0] = MaxCall;
   arglist[1] = Tolerance;
   myMinuit->mnexcm("MINIMIZE", arglist, 2, ierflg);
 }
 if(name == "IMPROVE"){
   arglist[0] = MaxCall;
   arglist[1] = Tolerance;
   myMinuit->mnexcm("IMPROVE", arglist, 2, ierflg);
 }

 if(name != "SIMPLEX" && name != "MIGRAD" && name != "MINIMIZE" && name != "IMPROVE"){
   cout<<"ERROR: Unknown mode was set."<<endl;
   return;
 }
 //myMinuit->mnexcm("HESSE", arglist, 1, ierflg);

}

void TMinuitHelper::GetParameter()
{
 double DataPoint[maxpar];
 double DataError[maxpar];

 for(int i = 0; i < maxpar; i++){
   myMinuit->GetParameter(i, DataPoint[i], DataError[i]);
   //cout<<"Parameter "<<i + 1<<": Center: "<<DataPoint[i]<<" Error: "<<DataError[i]<<endl;
 }
}

void TMinuitHelper::GetParameters(double* &DataPoints)
{
 double *DataPoint = new double[maxpar];
 double *DataError = new double[maxpar];

 for(int i = 0; i < maxpar; i++){
   myMinuit->GetParameter(i, DataPoint[i], DataError[i]);
 }

 DataPoints = DataPoint;
}

void TMinuitHelper::GetParametersAndError(double* &DataPoints, double* &DataErrors)
{
 double *DataPoint = new double[maxpar];
 double *DataError = new double[maxpar];
 
 for(int i = 0; i < maxpar; i++){
   myMinuit->GetParameter(i, DataPoint[i], DataError[i]);
 }
 
 DataPoints = DataPoint;
 DataErrors = DataError;
}

double TMinuitHelper::GetCorrelation(int i, int j)
{
 int ndi = i*(i + 1) / 2;
 int m    = TMath::Max(i,j);
 int n    = TMath::Min(i,j);
 int ndex = m*(m-1) / 2 + n;
 int ndj  = j*(j + 1) / 2;
 double Value = myMinuit->fVhmat[ndex-1] / TMath::Sqrt(TMath::Abs(myMinuit->fVhmat[ndi-1]*myMinuit->fVhmat[ndj-1]));
 return Value;

/*   for (i = 1; i <= fNpar; ++i) {
      ix  = fNexofi[i-1];
      ndi = i*(i + 1) / 2;
      for (j = 1; j <= fNpar; ++j) {
         m    = TMath::Max(i,j);
         n    = TMath::Min(i,j);
         ndex = m*(m-1) / 2 + n;
         ndj  = j*(j + 1) / 2;
         fMATUvline[j-1] = fVhmat[ndex-1] / TMath::Sqrt(TMath::Abs(fVhmat[ndi-1]*fVhmat[ndj-1]));
      }
      nparm = TMath::Min(fNpar,ncoef);
      ctemp.Form("      %3d  %7.5f ",ix,fGlobcc[i-1]);
      for (it = 1; it <= nparm; ++it) {
         ctemp += TString::Format(" %6.3f",fMATUvline[it-1]);
      }
      Printf("%s",(const char*)ctemp);
      if (i <= nparm) continue;
      ctemp = "                   ";
      for (iso = 1; iso <= 10; ++iso) {
         nsofar = nparm;
         nparm  = TMath::Min(fNpar,nsofar + ncoef);
         for (it = nsofar + 1; it <= nparm; ++it) {
            ctemp = ctemp + TString::Format(" %6.3f",fMATUvline[it-1]);
         }
         Printf("%s",(const char*)ctemp);
         if (i <= nparm) break;
      }
   }
*/

}
