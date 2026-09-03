#ifndef CTEQHelper_FittingHelper_h
#define CTEQHelper_FittingHelper_h

#include "RootCommon.h"
#include "Figure/Figure.h"
#include "Figure/Graph.h"

class FittingHelper
{
 public:

 FittingHelper();
 virtual void Loading(const char* name);

 map<TString, TString> DataLegend;
 void DefineCTEQDataLegend(std::map<TString, TString> &legend);
 void DefineCombination(std::map<int, TString> &FlavorNameMap, std::map<int, TString> &TitleMap, std::map<TString, int> &FlavorNameIndex);

 vector<TString> LMScanDrawList;
 virtual void InputLMScanDrawList(vector<TString> list){this->LMScanDrawList = list;}

 map<int, Style_t> PlotLineStyle;
 void DrawLMScanPlot(map<TString, TF1 *> FittingResults, TString FigureName, TString XaxisName, TString YaxisName);

};

#endif
