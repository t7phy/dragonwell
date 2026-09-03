#ifndef CTEQHelper_EVsets_h
#define CTEQHelper_EVsets_h

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "CTEQHelper/dtaReader.h"
#include "CTEQHelper/pdsReader.h"
#include "CTEQHelper/FittingHelper.h"
#include "Figure/Graph.h"

class dtaReader;
class pdsReader;

class EVsets
{
 public:

 int NEV = 0;

 vector<double> xValues;
 vector<double> QValues;

 vector<dtaReader *> fData;
 vector<pdsReader *> fPDFs;

 map<tuple<TString, int, double>, TH1D *> L2Sensitivity;

 EVsets();

 virtual void DrawAllL2Sensitivity(int flavor, double Q);
 virtual TH1D* DrawL2Sensitivity(int DataID, int flavor, double Q);
 virtual TH1D* DrawL2Sensitivity(vector<double> Chi2Set, int npt, TString name, int flavor, double Q);

 virtual void DrawAllL2SensitivityQ(int flavor, double x);
 virtual TH1D* DrawL2SensitivityQ(int DataID, int flavor, double x);

 virtual double CalcL2Sensitivity(int DataID, int flavor, double x, double Q);
 virtual double CalcL2Sensitivity(vector<double> Chi2Set, int npt, int flavor, double x, double Q);

 virtual void OutputePumpTheory(TString subName = "");

 double Sorting_x = 0.2;
 virtual void InputSortingX(double x){Sorting_x = x;}

 double Sorting_Q = 3000.0;

 bool isDrawAbsoluteL2 = false;
 virtual void DrawAbsoluteL2(){isDrawAbsoluteL2 = true;}

 vector<TString> L2SensitivityDrawList = {};
 virtual void InputL2SensitivityDrawList(vector<TString> list){this->L2SensitivityDrawList = list;}

 virtual void InitializeData(TString list);
 virtual void InitializePDF(TString list);

 virtual void InitializePDF(vector<pdsReader *> pdfs){this->fPDFs = pdfs;}

 TFile *hf;
 bool isLinkFile = false;
 virtual void openFile(TString name){isLinkFile = true; hf = new TFile(name, "RECREATE"); hf->cd();};
 virtual void SaveFile(){if(isLinkFile){hf->Write(); hf->Close();}};

 map<int, TString> FlavorNameMap;
 map<int, TString> TitleMap;
 map<TString, int> FlavorNameIndex;

 virtual void DefineCombination(){
   FittingHelper* Instance = new FittingHelper();
   Instance->DefineCombination(FlavorNameMap, TitleMap, FlavorNameIndex);
   delete Instance;
 }

 map<TString, TString> DataLegend;
 map<int, Style_t> PlotLineStyle;

 virtual void DefineDataLegend(){
   FittingHelper* Instance = new FittingHelper();
   Instance->DefineCTEQDataLegend(DataLegend);
   delete Instance;

   gStyle->SetLineStyleString(11, "20 12 4 12 4 12");
   gStyle->SetLineStyleString(12, "20 12 4 12 4 12 4 12 4 12");
   gStyle->SetLineStyleString(13, "20 20 12 12");
   gStyle->SetLineStyleString(14, "20 12 20 12 4 12 4 12");
   gStyle->SetLineStyleString(15, "80 20 4 12");
   for(int i = 2; i <= 100; i++){
     PlotLineStyle[i] = i;
   }
 }

};
#endif

