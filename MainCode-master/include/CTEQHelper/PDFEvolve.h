#ifndef CTEQHelper_PDFEvolve_h
#define CTEQHelper_PDFEvolve_h

#include "RootCommon.h"
#include "CTEQHelper/gfuns.h"
#include "Fantomas/CToWrapper.h"

using namespace std;
using namespace std::placeholders;

class PDFEvolve
{
 public:

 double Q0 = 1.3;
 double gluonMomentum = 0.3846129;
 double StrangeB0 = 0.5146522;

 double InitialgluonMomentum = 0.3846129;
 double InitialStrangeB0 = 0.5146522;

 vector<double> MomentumList;
 vector<double> B0List;

 double Ga = 3.0;

 gfuns* fun_gluon = 0;
 gfuns* fun_uv = 0;
 gfuns* fun_dv = 0;
 gfuns* fun_ubar = 0;
 gfuns* fun_dbar = 0;
 gfuns* fun_str = 0;
 gfuns* fun_svl = 0;
 gfuns* fun_chm = 0;
 gfuns* fun_dpu = 0;
 gfuns* fun_dmu = 0;

 // For Fantomas saving the flavor index
 int ifl_dv = 0;
 int ifl_uv = 0;
 int ifl_gluon = 0;
 int ifl_ubar = 0;
 int ifl_dbar = 0;
 int ifl_str = 0;

 function<double(double)> Q0_gluon;
 function<double(double)> Q0_u;
 function<double(double)> Q0_d;
 function<double(double)> Q0_uv;
 function<double(double)> Q0_dv;
 function<double(double)> Q0_ubar;
 function<double(double)> Q0_dbar;
 function<double(double)> Q0_s;
 function<double(double)> Q0_sbar;

 double gluonNorm = 1.0, uvNorm = 1.0, dvNorm = 1.0, ubarNorm = 1.0, dbarNorm = 1.0;
 double sNorm = 1.0, cNorm = 1.0, bNorm = 1.0;
 double sbarNorm = 1.0, cbarNorm = 1.0, bbarNorm = 1.0;
 double dpuNorm = 1.0, dmuNorm = 1.0;

 map<tuple<double, double>, double> gluon;
 map<tuple<double, double>, double> uv;
 map<tuple<double, double>, double> dv;
 map<tuple<double, double>, double> u;
 map<tuple<double, double>, double> ubar;
 map<tuple<double, double>, double> d;
 map<tuple<double, double>, double> dbar;
 map<tuple<double, double>, double> s;
 map<tuple<double, double>, double> sbar;
 map<tuple<double, double>, double> c;
 map<tuple<double, double>, double> cbar;
 map<tuple<double, double>, double> b;
 map<tuple<double, double>, double> bbar;

 PDFEvolve();

 /**
  * @brief Initialization function of PDF in Q0 scale
  * @param ifun The index of functional form
  * @param FlavorList List of parton flavors
  * @param FlagList List of gfun numbers
  */
 virtual void Initialize(int ifun, vector<TString> FlavorList, vector<int> FlagList);

 /**
  * @brief
  * @param
  */
 virtual void Normalization(int ifun);

///////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////
 // PDF Parametrization defined here //
 //////////////////////////////////////

 virtual void InitializeCT18(vector<TString> FlavorList, vector<int> FlagList);
 virtual void NormalizationCT18();

 virtual void InitializeCT18As(vector<TString> FlavorList, vector<int> FlagList);
 virtual void NormalizationCT18As();

 virtual void InitializeCT25As(vector<TString> FlavorList, vector<int> FlagList);
 virtual void NormalizationCT25As();

 bool doReadSteer = false;
 virtual void InitializeFantoCT18(vector<TString> FlavorList, vector<int> FlagList);
 virtual void NormalizationFantoCT18();
 virtual void OutputFantoCT18();

 virtual void InitializeFantoMix(vector<TString> FlavorList, vector<int> FlagList);

///////////////////////////////////////////////////////////////////////////////////////////////////

 virtual double NumberIntegral(TString flavor);
 virtual double MomentumIntegral(TString flavor);

 vector<double> xvec, wvec;
 virtual void PrepareIntegral();
 virtual double PDFIntegral(std::function<double(double)> fcn);

 virtual double GetQ0Function(double z, TString flavor);
 virtual double GetQ0xFunction(double z, TString flavor);

 virtual double Getgluon(double x, double Q){return gluon[make_tuple(x, Q)];};
 virtual double Getuv(double x, double Q){return uv[make_tuple(x, Q)];};
 virtual double Getdv(double x, double Q){return dv[make_tuple(x, Q)];};
 virtual double Getu(double x, double Q){return u[make_tuple(x, Q)];};
 virtual double Getd(double x, double Q){return d[make_tuple(x, Q)];};
 virtual double Getubar(double x, double Q){return ubar[make_tuple(x, Q)];};
 virtual double Getdbar(double x, double Q){return dbar[make_tuple(x, Q)];};
 virtual double Gets(double x, double Q){return s[make_tuple(x, Q)];};
 virtual double Getsbar(double x, double Q){return sbar[make_tuple(x, Q)];};

 virtual double GetPDFQ0(double x, int flavor){
   if(flavor == 0) return Q0_gluon(x);
   else if(flavor == 1) return Q0_u(x);
   else if(flavor == -1) return Q0_ubar(x);
   else if(flavor == 2) return Q0_d(x);
   else if(flavor == -2) return Q0_dbar(x);
   else if(flavor == 3) return Q0_s(x);
   else if(flavor == -3) return Q0_sbar(x);
   else return 0.0;
 }

 virtual void SetQ0(double Q){this->Q0 = Q;}
 virtual void SetInitialgluonMomentum(double p){InitialgluonMomentum = p; gluonMomentum = p;}
 virtual void SetInitialStrangeB0(double p){InitialStrangeB0 = p; StrangeB0 = p;}

 map<TString, vector<double>> Parameter;
 vector<TString> FlavorNameList;
 virtual void SetParameter(TString flavor, vector<double> para){
   if(Parameter[flavor].size() != 0) Parameter[flavor].clear();
   Parameter[flavor] = para;
   auto it = std::find(FlavorNameList.begin(), FlavorNameList.end(), flavor);
   if(it == FlavorNameList.end()){
     FlavorNameList.push_back(flavor);
   }
 }

 virtual void SetgluonMomentumPar(double pa){gluonMomentum = InitialgluonMomentum * exp(pa);}
 virtual void SetStrangeB0Par(double pa){StrangeB0 = InitialStrangeB0 * exp(0.1 * pa);}
 virtual double GetgluonMomentum(){return gluonMomentum;}
 virtual double GetStrangeB0(){return StrangeB0;}

 virtual void Setgluon(double x, double Q, double pdf){gluon[make_tuple(x, Q)] = pdf;}
 virtual void Setu(double x, double Q, double pdf){u[make_tuple(x, Q)] = pdf;}
 virtual void Setubar(double x, double Q, double pdf){ubar[make_tuple(x, Q)] = pdf;}
 virtual void Setd(double x, double Q, double pdf){d[make_tuple(x, Q)] = pdf;}
 virtual void Setdbar(double x, double Q, double pdf){dbar[make_tuple(x, Q)] = pdf;}
 virtual void Sets(double x, double Q, double pdf){s[make_tuple(x, Q)] = pdf;}
 virtual void Setsbar(double x, double Q, double pdf){sbar[make_tuple(x, Q)] = pdf;}
 virtual void Setc(double x, double Q, double pdf){c[make_tuple(x, Q)] = pdf;}
 virtual void Setcbar(double x, double Q, double pdf){cbar[make_tuple(x, Q)] = pdf;}
 virtual void Setb(double x, double Q, double pdf){b[make_tuple(x, Q)] = pdf;}
 virtual void Setbbar(double x, double Q, double pdf){bbar[make_tuple(x, Q)] = pdf;}
 virtual void Setuv(double x, double Q, double pdf){uv[make_tuple(x, Q)] = pdf;}
 virtual void Setdv(double x, double Q, double pdf){dv[make_tuple(x, Q)] = pdf;}

 virtual void ParameterOutput();
 virtual void pdsOutput();

};
#endif
