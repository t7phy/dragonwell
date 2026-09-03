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
#include "Calculation/GlobalFitting_BAT.h"
#include <BAT/BCLog.h>
#include <BAT/BCAux.h>

using namespace std;

int main(int argc, char** argv)
{
 TString fitting_config = "Config.yml";
 BCLog::OpenLog("log.txt", BCLog::detail, BCLog::detail);
 BCLog::OutSummary(TString::Format("Using %s as config file", fitting_config).Data());

 GlobalFitting_BAT m("CT18xx");
 m.SetRandomSeed(1234);

 m.Initialize();

 std::string precision = "Medium";
 if(precision == "Quick") m.SetPrecision(BCEngineMCMC::kQuick);
 else if(precision == "Medium") m.SetPrecision(BCEngineMCMC::kMedium);
 else if(precision == "High") m.SetPrecision(BCEngineMCMC::kHigh);
 else if(precision == "VeryHigh") m.SetPrecision(BCEngineMCMC::kVeryHigh);

 BCLog::OutSummary("Test model created");

 // run MCMC, marginalizing posterior
 m.MarginalizeAll(BCIntegrate::kMargMetropolis);

 // run mode finding; by default using Minuit
 m.SetOptimizationMethod(BCIntegrate::kOptMinuit);
 m.FindMode(m.GetBestFitParameters());

 // draw all marginalized distributions into a PDF file
 m.PrintAllMarginalized(m.GetSafeName() + "_plots.pdf");

 // print summary plots
 m.PrintParameterPlot(m.GetSafeName() + "_parameters.pdf");
 m.PrintCorrelationPlot(m.GetSafeName() + "_correlation.pdf");
 m.PrintCorrelationMatrix(m.GetSafeName() + "_correlationMatrix.pdf");
 m.PrintKnowledgeUpdatePlots(m.GetSafeName() + "_update.pdf");

 // print results of the analysis into a text file
 m.PrintSummary();
 m.CalculateCorrelationMatrix();

 m.Finalize();

 // close log file
 BCLog::OutSummary("Exiting");
 BCLog::CloseLog();

 return 1;
}
