#ifndef Calculation_GlobalFittingCore_h
#define Calculation_GlobalFittingCore_h

#include <filesystem>
#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Tools/Log.h"
#include "Calculation/PDFChi2.h"
#include "CTEQHelper/HoppetInterface.h"
#include "CTEQHelper/PDFEvolve.h"
#include "CTEQHelper/FittingHelper.h"
#include "Calculation/ApplGridHelper.h"
#include "Calculation/FastNLOHelper.h"
#include "Calculation/Dataset.h"
#include "Calculation/DataPoint.h"
#include "Calculation/Config.h"
#include "Calculation/QCDSet.h"
#include <Minuit2/FCNBase.h>
#include "Minuit2/FunctionMinimum.h"
#include "Minuit2/MnUserParameterState.h"
#include "Minuit2/MnSimplex.h"
#include "Minuit2/MnMigrad.h"
#include "Minuit2/MnMinimize.h"
#include "Minuit2/MnFumiliMinimize.h"
#include "Minuit2/MnHesse.h"
#include "Minuit2/MnMinos.h"
#include "Minuit2/MnContours.h"
#include "Minuit2/MnPlot.h"

class GlobalFittingCore : public ROOT::Minuit2::FCNBase
{
 public:

 double Min_Chi2 = 10000000.0;

 PDFEvolve* m_pdf_Q0 = 0;
 HoppetInterface* m_hoppet = 0;
 Config* m_setting = 0;
 vector<Dataset *>* m_AllData = 0;
 PDFChi2* m_fcn = 0;
 double DeltaChi2 = 0.0;

 Config setting;
 Config newsetting;
 vector<Dataset *> AllData;

 TString InputParaFileName = "Parameters.yml";
 TString NewParaFileName = "NewParameters.yml";

 GlobalFittingCore();
 virtual double Up() const {return theErrorDef;}

 virtual void Initialize();
 virtual double operator()(const std::vector<double>&) const;
 virtual void Finalize(std::vector<double> pars, std::vector<double> parerrs);

 void setErrorDef(double def) {theErrorDef = def;}

 ROOT::Minuit2::MnUserParameters upar;
 vector<double> InitialParameters = {};
 virtual void Input(TString name, double central, double step, double left, double right){
   upar.Add(name.Data(), central, step);
   //upar.SetLimits(name.Data(), left, right);

   InitialParameters.push_back(central);
 }

 vector<double> GetInitialParameters(){return InitialParameters;}

 double chi2(const std::vector<double>& par);

 virtual double GetChi2(bool print, bool isBestFit = false){
   return m_fcn->GetChi2(print, isBestFit);
 }

 virtual void ResetFit(){
   m_fcn->ResetFit();
 }

 virtual void UpdateParameterCentral(){
   InitialParameters.clear(); // For Python script, after UpdatedParameterCentral(), the InitialParameters should be updated again

   for(int i = 0; i < setting.GetNPar(); i++){
     upar.SetValue(setting.GetParName(i).Data(), setting.GetParCentral(i));
     InitialParameters.push_back(setting.GetParCentral(i));
   }

   m_pdf_Q0->SetInitialgluonMomentum(setting.InitialgluonMomentum);
   m_pdf_Q0->SetInitialStrangeB0(setting.InitialStrangeB0);
 }

 virtual void InitialPDF();
 virtual void UpdateIterateParameters(std::vector<double> pars);
 virtual void ReadingNewParaFile(TString FileName);

 // For LMScan
 map<TString, TGraph *> PDFLMScanResult;
 map<TString, TF1 *> PDFLMScanFitting;
 map<TString, TGraph *> PDFLMScanPoint;
 map<TString, TGraph *> PDFLMScanOriginResult;
 map<TString, TF1 *> PDFLMScanOriginFitting;
 map<TString, TGraph *> PDFLMScanOriginPoint;
 virtual void PDFLMScan(int flavor, double x, double Q);

 map<TString, TGraph *> AlphaSLMScanResult;
 map<TString, TF1 *> AlphaSLMScanFitting;
 map<TString, TGraph *> AlphaSLMScanPoint;
 map<TString, TGraph *> AlphaSLMScanOriginResult;
 map<TString, TF1 *> AlphaSLMScanOriginFitting;
 map<TString, TGraph *> AlphaSLMScanOriginPoint;
 virtual void AlphaSLMScan();

 map<TString, TGraph *> ParameterLMScanResult;
 map<TString, TF1 *> ParameterLMScanFitting;
 map<TString, TGraph *> ParameterLMScanPoint;
 map<TString, TGraph *> ParameterLMScanOriginResult;
 map<TString, TF1 *> ParameterLMScanOriginFitting;
 map<TString, TGraph *> ParameterLMScanOriginPoint;
 virtual void ParameterScan();

 map<int, TString> FlavorNameMap;
 map<int, TString> TitleMap;
 map<TString, int> FlavorNameIndex;

 virtual void DefineCombination(){
   FittingHelper* Instance = new FittingHelper();
   Instance->DefineCombination(FlavorNameMap, TitleMap, FlavorNameIndex);
   delete Instance;
 }

 private:

 double theErrorDef = 1.0;
};

double fchi2(const double* par);
#endif
