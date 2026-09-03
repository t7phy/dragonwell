#ifndef Calculation_GlobalFitting_BAT_h
#define Calculation_GlobalFitting_BAT_h

#include <BAT/BCModel.h>
#include <filesystem>
#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Calculation/PDFChi2.h"
#include "CTEQHelper/HoppetInterface.h"
#include "CTEQHelper/PDFEvolve.h"
#include "Calculation/ApplGridHelper.h"
#include "Calculation/FastNLOHelper.h"
#include "Calculation/Dataset.h"
#include "Calculation/DataPoint.h"
#include "Calculation/Config.h"
#include "Calculation/QCDSet.h"
#include "Calculation/GlobalFittingCore.h"

class GlobalFitting_BAT : public BCModel
{
 public:

 GlobalFittingCore* m_instance;

 GlobalFitting_BAT(const std::string& name);

 ~GlobalFitting_BAT();

 virtual void Initialize();

 // Overload LogLikelihood to implement model
 double LogLikelihood(const std::vector<double>& pars);

 virtual void Finalize();

 virtual void Input(TString name, double central, double step, double left, double right){
   AddParameter(name.Data(), left, right, name.Data(), "");
   GetParameters().Back().SetPriorConstant();
 }

 // Overload CalculateObservables if using observables
 void CalculateObservables(const std::vector<double>&) {};
 void CalculateCorrelationMatrix() const;


};
#endif
