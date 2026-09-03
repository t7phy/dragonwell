#ifndef CTEQHelper_ClusterPDF_h
#define CTEQHelper_ClusterPDF_h

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "CTEQHelper/pdsReader.h"
#include "CTEQHelper/sumReader.h"
#include <Eigen/Dense>

using namespace std;

class ClusterPDF
{
 public:

 pdsReader* reference;

 vector<pdsReader *> PDFList;
 vector<sumReader *> SummaryList;

 vector<TString> PDFFileNames;

 vector<double> QVector;
 vector<double> xVector;
 vector<TString> FlavorVector;
 vector<tuple<int, double, double>> xFlavorVector;
 vector<tuple<double, double>> xQVector;

 bool isPrepareGaussPoints = false;

 ClusterPDF();
 virtual void OutputTSV(TString name);
 virtual void OutputRenyiEntropy(TString name, int alpha);
 virtual vector<double> CalculateRenyiEntropy(int ipdf, int alpha);
 virtual void InputReferencePDF(TString name);
 virtual void InputPDFList(vector<TString> list);
 virtual void InputSummaryList(vector<TString> list);
 virtual void PreparexFlavorVector();
 virtual void PrepareGaussPoints(int n, double alpha, int nStripStart, int nStripEnd);
 virtual void DefineMetaData();

 map<int, TString> FlavorNameMap;
 map<int, TString> TitleMap;
 map<TString, int> FlavorNameIndex;

 virtual void DefineCombination(){
   FlavorNameMap[0] = "gluon";
   FlavorNameMap[1] = "d";
   FlavorNameMap[2] = "u";
   FlavorNameMap[3] = "s";
   FlavorNameMap[4] = "c";
   FlavorNameMap[5] = "b";
   FlavorNameMap[-1] = "dbar";
   FlavorNameMap[-2] = "ubar";
   FlavorNameMap[-3] = "sbar";
   FlavorNameMap[-4] = "cbar";
   FlavorNameMap[-5] = "bbar";
   FlavorNameMap[6] = "uv";
   FlavorNameMap[7] = "dv";
   FlavorNameMap[8] = "sv";
   FlavorNameMap[9] = "ubouv";
   FlavorNameMap[10] = "dbodv";
   FlavorNameMap[11] = "ubou";
   FlavorNameMap[12] = "dbod";
   FlavorNameMap[13] = "gluon5";
   FlavorNameMap[14] = "uod";
   FlavorNameMap[15] = "ubodb";
   FlavorNameMap[16] = "uvodv";
   FlavorNameMap[17] = "dbou";
   FlavorNameMap[18] = "ubod";
   FlavorNameMap[19] = "dboub";
   FlavorNameMap[20] = "dou";
   TitleMap[0] = "g";
   TitleMap[1] = "d";
   TitleMap[2] = "u";
   TitleMap[3] = "s";
   TitleMap[4] = "c";
   TitleMap[5] = "b";
   TitleMap[-1] = "#bar{d}";
   TitleMap[-2] = "#bar{u}";
   TitleMap[-3] = "#bar{s}";
   TitleMap[-4] = "#bar{c}";
   TitleMap[-5] = "#bar{b}";
   TitleMap[6] = "u_{v}";
   TitleMap[7] = "d_{v}";
   TitleMap[8] = "s-#bar{s}";
   TitleMap[9] = "#bar{u}/u_{v}";
   TitleMap[10] = "#bar{d}/d_{v}";
   TitleMap[11] = "#bar{u}/u";
   TitleMap[12] = "#bar{d}/d";
   TitleMap[13] = "g/5";
   TitleMap[14] = "u/d";
   TitleMap[15] = "#bar{u}/#bar{d}";
   TitleMap[16] = "u_{v}/d_{v}";
   TitleMap[17] = "#bar{d}/u";
   TitleMap[18] = "#bar{u}/d";
   TitleMap[19] = "#bar{d}/#bar{u}";
   TitleMap[20] = "d/u";

   for(auto iter = FlavorNameMap.begin(); iter != FlavorNameMap.end(); iter++){
     FlavorNameIndex[iter->second] = iter->first;
   }

 }
};
#endif
