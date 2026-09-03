#ifndef CTEQHelper_LMScanHelper_h
#define CTEQHelper_LMScanHelper_h

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "CTEQHelper/dtaReader.h"
#include "CTEQHelper/sumReader.h"
#include "CTEQHelper/FittingHelper.h"
#include "Figure/Figure.h"

using namespace std;

class LMScanHelper
{
 public:

 vector<double> LMPara;
 vector<dtaReader *> DataFiles;
 vector<sumReader *> SummaryFiles;

 map<int, TH1D *> Chi2Hist;
 map<int, TF1 *> Chi2Fitting;

 map<int, TH1D *> Chi2ZeroHist;
 map<int, TF1 *> Chi2ZeroFitting;

 map<int, double> BestChi2;

 double PlotXMin;
 double PlotXMax;

 LMScanHelper();
 virtual void InitialParameter(vector<double> Paras){this->LMPara = Paras;};
 virtual void InitialData(vector<dtaReader *> DataFiles){this->DataFiles = DataFiles;};
 virtual void InitialData(vector<TString> DataList);
 virtual void InitialSummary(vector<TString> SummaryList);
 virtual void DrawChi2(TString subName = "");
 virtual void Plotting(TString subName, vector<TString> DataList);

 TFile* hf;
 bool isLinkFile = false;
 virtual void openFile(TString name){hf = new TFile(name, "RECREATE"); hf->cd(); isLinkFile = true;}
 virtual void LinkFile(TFile* file){hf = file; hf->cd(); isLinkFile = true;}
 virtual void SaveFile(){hf->cd(); hf->Write(); hf->Close();}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

 map<int, TString> DataNameMap;
 map<TString, int> DataIndex;

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

