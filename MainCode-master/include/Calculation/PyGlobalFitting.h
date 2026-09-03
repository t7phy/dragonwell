#ifndef Calculation_PyGlobalFitting_h
#define Calculation_PyGlobalFitting_h

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

class PyGlobalFitting
{
 public:

 GlobalFittingCore* m_instance;

 PyGlobalFitting();

 ~PyGlobalFitting();

 void Initialize();

 double Chi2(const std::vector<double>& pars);

 void Finalize(std::vector<double> pars, std::vector<double> parerrs);

 void ResetFit();
 void UpdateParameterCentral();
 double GetDeltaChi2();
 int GetLFit();
 int GetMaxCall();
 double GetMinTol();

 std::vector<double> GetInitialParameters();

 std::vector<double> GetTheoryPrediction(std::string name);
};

#endif
