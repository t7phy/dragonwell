#ifndef ePumpHelper_ePumpHelper_h
#define ePumpHelper_ePumpHelper_h

#include "RootCommon.h"
#include "ePump/ePump.h"
#include "ePump/Cholesky.h"
#include "ePump/Eigen_ePump.h"
#include "CTEQHelper/pdsReader.h"
#include "CTEQHelper/EVsets.h"
#include "ePump/ePumpHists.h"
#include "Figure/Figure.h"
#include "Figure/Graph.h"
#include "Tools/Log.h"
//#include "CTEQHelper/HoppetInterface.h"
#include "CTEQHelper/FittingHelper.h"
#include <Eigen/Dense>

class ePump;

class ePumpHelper
{
 public:

 TString FileName;

 ePump* EU;

 bool isUpdate = false;
 bool isOptimize = false;

 int NEV;
 vector<TString> AllDataNames;

 map<TString, int> DataIndex;
 map<TString, int> DataErrorType;
 map<TString, double> DataWeight;
 map<TString, bool> DataIncluded;

 map<TString, int> DataNPoints;
 map<TString, vector<double>> DataPoint;
 map<TString, vector<double>> DataTotalErr;

 map<TString, vector<vector<double>>> TheoryTemplate;
 map<TString, vector<vector<double>>> NewTheoryTemplate;
 map<TString, vector<vector<double>>> OptimizeTheoryTemplate;

 map<TString, vector<double>> OldTheory;
 map<TString, vector<double>> NewTheory;
 map<TString, vector<double>> OldPDFError;
 map<TString, vector<double>> NewPDFError;
 map<TString, vector<double>> NewPDFErrorTmp;
 map<vector<TString>, vector<vector<double>>> OldPDFCorrelation;
 map<vector<TString>, vector<vector<double>>> NewPDFCorrelation;
 map<vector<TString>, vector<vector<double>>> NewPDFCorrelationTmp;

 map<TString, vector<vector<double>>> FractionalContribution;

 map<TString, double> OldChi2;
 map<TString, double> NewChi2;
 map<TString, double> OldSpartyness;
 map<TString, double> NewSpartyness;

 map<TString, vector<double>> OldChi2Set;
 map<TString, vector<double>> NewChi2Set;

 bool isPrepareOldChi2 = false;

 map<tuple<TString, int, double>, TH1D *> OldL2Sensitivity;
 map<tuple<TString, int, double>, TH1D *> NewL2Sensitivity;

 map<tuple<TString, int, double>, TH1D *> OldL2SensitivityQ;

 map<TString, vector<vector<double>>> NewTheoryWeightFunction;
 map<TString, vector<vector<double>>> NewPDFErrorWeightFunction;
 map<TString, vector<double>> NewChi2WeightFunction;
 map<TString, vector<double>> NewChi2NptWeightFunction;
 map<TString, vector<double>> NewSpartynessWeightFunction;
 map<TString, vector<TH1D *>> NewTheoryWeightHist;
 map<TString, vector<TH1D *>> NewPDFErrorWeightHist;
 map<TString, TH1D *> NewChi2WeightHist;
 map<TString, TH1D *> NewChi2NptWeightHist;
 map<TString, TH1D *> NewSpartynessWeightHist;

 map<TString, vector<TH1D *>> FractionalContributionHist;

 pdsReader* PDFSample;
 vector<pdsReader *> OldPDFSet;
 vector<pdsReader *> NewPDFSet;
 EVsets* OldEVSet;
 EVsets* NewEVSet;

 ePumpHelper(const char* filename);
 virtual void Initial();
 virtual void Update();
 virtual void InitialOptimize();
 virtual void Optimize();
 virtual void InitialUpdatedPDF();
 virtual void CalcL2Sensitivity(int flavor, double x, double Q);
 virtual void DrawL2Sensitivity(TString DataName, int flavor, double Q);
 virtual void DrawL2SensitivityAll(int flavor, double Q);

 bool isDrawAbsoluteL2 = false;
 virtual void DrawAbsoluteL2(){isDrawAbsoluteL2 = true;}

 bool isDrawUpdatedL2 = false;
 virtual void DrawUpdatedL2(){isDrawUpdatedL2 = true;}

 vector<TString> L2SensitivityDrawList;
 virtual void InputL2SensitivityDrawList(vector<TString> list){this->L2SensitivityDrawList = list;}

 virtual void CombineDataset(TString NewDataName, vector<TString> DataNames){
   if(!isPrepareOldChi2){
     EU->PrepareOldChi2();
     for(int i = 0; i < EU->dataset.size(); i++){
       OldChi2Set[(TString)(EU->dataset.at(i).c_str())] = EU->dChi2Set.at(i);
     }
     isPrepareOldChi2 = true;
   }

   OldChi2Set[NewDataName] = {};
   NewChi2Set[NewDataName] = {};

   OldChi2Set.at(NewDataName).resize(2 * NEV + 1);
   NewChi2Set.at(NewDataName).resize(2 * NEV + 1);
   for(int iEV = 0; iEV < 2 * NEV + 1; iEV++){
     OldChi2Set.at(NewDataName).at(iEV) = 0.0;
     NewChi2Set.at(NewDataName).at(iEV) = 0.0;
     for(int i = 0; i < DataNames.size(); i++){
       OldChi2Set.at(NewDataName).at(iEV) += OldChi2Set.at(DataNames.at(i)).at(iEV);
       NewChi2Set.at(NewDataName).at(iEV) += NewChi2Set.at(DataNames.at(i)).at(iEV);
     }
   }

   DataNPoints[NewDataName] = 0;
   for(int i = 0; i < DataNames.size(); i++){
     DataNPoints.at(NewDataName) += DataNPoints.at(DataNames.at(i));
   }
 }

 virtual void CalNewPDFUnc();
 virtual void CalNewPDFCorr();

 virtual void ProcessWeightFunction(vector<TString> DataNames);

 inline double GetTheoryTemplate(TString DataName, int i, int iPDF){
   return TheoryTemplate[DataName].at(i).at(iPDF);
 }
 inline double GetNewTheoryTemplate(TString DataName, int i, int iPDF){
   return NewTheoryTemplate[DataName].at(i).at(iPDF);
 }
 inline double GetOptimizeTheoryTemplate(TString DataName, int i, int iPDF){
   return OptimizeTheoryTemplate[DataName].at(i).at(iPDF);
 }
 inline double GetOldTheory(TString DataName, int i){
   return OldTheory[DataName].at(i);
 }
 inline double GetNewTheory(TString DataName, int i){
   return NewTheory[DataName].at(i);
 }
 inline double GetOldPDFError(TString DataName, int i){
   return OldPDFError[DataName].at(i);
 }
 inline double GetNewPDFError(TString DataName, int i){
   return NewPDFError[DataName].at(i);
 }
 inline double GetOldRelativePDFError(TString DataName, int i){
   return OldPDFError[DataName].at(i) / OldTheory[DataName].at(i);
 }
 inline double GetNewRelativePDFError(TString DataName, int i){
   return NewPDFError[DataName].at(i) / NewTheory[DataName].at(i);
 }
 inline double GetOldPDFCorrelation(TString DataName1, TString DataName2, int i, int j){
   if(!doCorrelationCosine) return 0.0;
   return OldPDFCorrelation[(vector<TString>{DataName1, DataName2})].at(i).at(j);
 }
 inline double GetNewPDFCorrelation(TString DataName1, TString DataName2, int i, int j){
   if(!doCorrelationCosine) return 0.0;
   return NewPDFCorrelation[(vector<TString>{DataName1, DataName2})].at(i).at(j);
 }
 inline double GetOldChi2(TString DataName){
   return OldChi2[DataName];
 }
 inline double GetNewChi2(TString DataName){
   return NewChi2[DataName];
 }
 inline vector<double> GetNewTheoryWeightFunction(TString DataName, int i){
   return NewTheoryWeightFunction[DataName].at(i);
 }
 inline vector<double> GetNewPDFErrorWeightFunction(TString DataName, int i){
   return NewPDFErrorWeightFunction[DataName].at(i);
 }

 virtual void ConstructDataHist(TString DataName, TH1D* &Data);
 virtual void ConstructTheoryHist(TString DataName, vector<TH1D *> &Theory);
 virtual void ConstructOldPDFErrorHist(TString DataName, TString subName, TH1D* &Hist, TString type = "");
 virtual void ConstructNewPDFErrorHist(TString DataName, TString subName, TH1D* &Hist, TString type = "");

 TH1D* ConstructDataHist(TString DataName);
 vector<TH1D *> ConstructTheoryHist(TString DataName);
 vector<TH1D *> ConstructNewTheoryHist(TString DataName);
 vector<TH1D *> ConstructOptimizeTheoryHist(TString DataName);
 TH1D* ConstructOldPDFErrorHist(TString DataName, TString subName, TString type = "");
 TH1D* ConstructOldPDFErrorHist(TString DataName, TString subName, TString type, int FirstBin, int LastBin);
 TH1D* ConstructNewPDFErrorHist(TString DataName, TString subName, TString type = "");
 TH1D* ConstructNewPDFErrorHist(TString DataName, TString subName, TString type, int FirstBin, int LastBin);

 TH1D* ConstructOldTheoryWithPDFError(TString DataName, TString subName);
 TH1D* ConstructNewTheoryWithPDFError(TString DataName, TString subName);

 virtual void SaveAllHist();
 virtual void SaveOptimizeHist();

 virtual void OutputResult(TString DataName);
 virtual void OutputCorrelation(TString Data1, TString Data2);

 virtual void SetDataWeight(TString DataName, double w);
 virtual void ResetWeight();

 virtual void TurnOnData(TString DataName);
 virtual void ResetData();

 virtual void ResetUpdate();

 bool DoSaveHist = false;
 virtual void SaveHist();

 bool isTurnOffUpdatePDF = false;
 virtual void TurnOffUpdatePDF();

 bool doCorrelationCosine = true;
 virtual void TurnOffCorrelationCosine();

 TFile* hf;
 bool isLinkFile = false;
 virtual void LinkFile(TFile* file){isLinkFile = true; this->hf = file;}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 map<tuple<TString, TString>, TH1D *> CorrHistChi2AndData;
 map<tuple<vector<TString>, TString>, TH1D *> CorrHistSumChi2AndData;

 virtual void DrawCorrChi2AndData(TString Data1, TString Data2);
 virtual void DrawCorrChi2AndData(vector<TString> DataNames, TString Data2);
 virtual double CalcCorrelation(vector<double> A, vector<double> B);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 bool isUpdateExtendPara = false;

 vector<vector<vector<double>>> Xdyn;
 vector<vector<vector<double>>> XXdyn;
 vector<vector<vector<double>>> Cm;
 vector<vector<double>> XE;
 vector<vector<double>> X0;
 vector<double> weight;
 double Tsq;
 vector<double> A;
 vector<vector<double>> M;

 int NExtendedPara = 0;

 vector<vector<vector<double>>> ExtendedXmat;
 vector<vector<vector<double>>> ExtendedXmatNew;
 vector<double> ExtendedTdynRMS;
 vector<double> ExtendedTdynP;
 vector<double> ExtendedTdynM;
 vector<double> ExtendedTdynBar;

 vector<vector<vector<double>>> ExtendedXdyn;
 vector<vector<vector<double>>> ExtendedXXdyn;
 vector<double> ExtendedA;
 vector<vector<double>> ExtendedM;

 vector<double> Extendedz0;  // z0[Ni]
 vector<double> Extendedz0sqr;    // z0sqr[Ni]

 vector<vector<double>> ExtendedX0new;
 vector<double> ExtendeddChi2new;
 vector<vector<double>> ExtendeddChi2newSet;
 double ExtendedChi2;
 double ExtendedChi2new;
 double ExtendedChi20new;

 vector<vector<double>> ExtendedU;
 vector<double> Extendedd;

 vector<TString> ExtendedParaName;
 vector<double> ExtendedParaCentral;
 vector<double> ExtendedParaPlus;
 vector<double> ExtendedParaMinus;

 ePump* ExtendedEU;

 virtual void GetUpdateParameter();
 virtual void ReadParameterList();
 virtual void ExtendXdyn(int k);
 virtual void InputExtendedParameter();

 virtual void PrepareAMlinearExtended(int k);
 virtual double NewBestFitLinearExtended(void);
 virtual void ConstructUpdateMatrixExtended(void);
 virtual void ConstructX0newChi2newExtended(void);
 virtual void Meig(void);
 virtual void UpdateObservablesExtended(void);

 ePumpHists* myhistsExtended;

/////////////////////////////////////////////////////////////////////////////
 ePump* AlphaSEU;

 //HoppetInterface* m_hoppet;
 Logstream myLog;

 Eigen::MatrixXd IplusM_inv;
 Eigen::MatrixXd IplusM_sub_inv;
 Eigen::VectorXd New_BestFit_Par; //z'

 double Old_AlphaS_WA = 0.0;
 double Old_AlphaS_GA = 0.0;
 double New_AlphaS_WA = 0.0;
 double New_AlphaS_GA = 0.0;
 double Old_Delta_AlphaS = 0.0;
 double New_Delta_AlphaS = 0.0;
 double Old_Delta_AlphaS_up = 0.0;
 double New_Delta_AlphaS_up = 0.0;
 double Old_Delta_AlphaS_down = 0.0;
 double New_Delta_AlphaS_down = 0.0;

 double AlphaS_Q = 91.19;

 vector<pdsReader *> NewAlphaSPDF;
 pdsReader* NewAlphaSOnlyPDF; // only update the alphas parameter, other parameters are keeping zero

 virtual void ReadAlphaSInput(TString FileName);
 virtual void UpdateAlphaS();
 virtual void UpdateAlphaSPDFs();
 virtual void UpdateAlphaSObservables();
 virtual void UpdateAlphaSLMScan();
 virtual void UpdateAlphaSLMScanPDF(int flavor, double x, double Q);
 virtual void UpdateAlphaSLMScanObservable(TString DataName, int ipoint, TString TitleName);
 virtual void AlphaSObservableCorrelation(TString DataName, int ipoint, TString TitleName);

 vector<vector<vector<double>>> NewObservableSet;
 vector<vector<double>> ObservableDeltaAlphaS;
 vector<vector<double>> ObservableDeltaAlphaSPlus;
 vector<vector<double>> ObservableDeltaAlphaSMinus;
 vector<vector<double>> NewObservableAlphaSOnly; // only update the alphas parameter, other parameters are keeping zero

/////////////////////////////////////////////////////////////////////////////
 ePump* ParameterEU;

 double Old_Parameter = 0.0;
 double New_Parameter = 0.0;
 double Old_Parameter_up = 0.0;
 double New_Parameter_up = 0.0;
 double Old_Parameter_down = 0.0;
 double New_Parameter_down = 0.0;

 vector<double> ParameterUpdate_K;
 double ParameterUpdate_R = 0.0;
 double ParameterUpdate_L = 0.0;

 vector<pdsReader *> NewParameterPDF;
 pdsReader* NewParameterOnlyPDF; // only update the alphas parameter, other parameters are keeping zero

 virtual void ReadParameterInput(TString FileName);
 virtual void UpdateParameter();
 virtual void UpdateParameterPDFs();
 virtual void UpdateParameterObservables();

 vector<vector<double>> ObservableDeltaParameter;
 vector<vector<double>> ObservableDeltaParameterPlus;
 vector<vector<double>> ObservableDeltaParameterMinus;
 vector<vector<double>> NewObservableParameterOnly; // only update the alphas parameter, other parameters are keeping zero

/////////////////////////////////////////////////////////////////////////////

 virtual void AddHistogram(TH1D* DataHist, vector<TH1D *> TheoryHist, TString DataName, double weight);
 virtual void ResizeNData(int npt, double weight);
 virtual double GetNewParaError(){
   EU->ConstructUpdateMatrix();
   return EU->NewParaError;
 }

/////////////////////////////////////////////////////////////////////////////

 ePump* LMScan;
 map<tuple<TString, int, int>, TGraph *> LMScanResult;
 map<tuple<TString, int, int>, TF1 *> LMScanFitting;
 map<tuple<TString, int, int>, TGraph *> LMScanPoint;

 map<tuple<TString, int, double, double, int>, TGraph *> PDFLMScanResult;
 map<tuple<TString, int, double, double, int>, TF1 *> PDFLMScanFitting;
 map<tuple<TString, int, double, double, int>, TGraph *> PDFLMScanPoint;
 map<tuple<TString, int, double, double, int>, TGraph *> PDFLMScanOriginResult;
 map<tuple<TString, int, double, double, int>, TF1 *> PDFLMScanOriginFitting;
 map<tuple<TString, int, double, double, int>, TGraph *> PDFLMScanOriginPoint;

 map<tuple<int, double, double, int>, double> PDFLMScanPlotXMin;
 map<tuple<int, double, double, int>, double> PDFLMScanPlotXMax;

 map<tuple<TString>, TGraph *> AlphaSLMScanResult;
 map<tuple<TString>, TF1 *> AlphaSLMScanFitting;
 map<tuple<TString>, TGraph *> AlphaSLMScanPoint;
 map<tuple<TString>, TGraph *> AlphaSLMScanOriginResult;
 map<tuple<TString>, TF1 *> AlphaSLMScanOriginFitting;
 map<tuple<TString>, TGraph *> AlphaSLMScanOriginPoint;

 double AlphaSLMScanPlotXMin;
 double AlphaSLMScanPlotXMax;

 virtual ePump* Clone(ePump* inputEU, TString MainName, int isNewPDF = 0);
 virtual ePump* Clone(ePump* inputEU);
 virtual void AddLMScanConstrain(ePump* &LMScan);
 virtual void AddLMData(TString DataName, int ipoint);
 virtual void AddLMPDF(int flavor, double x, double Q, int isNewPDF = 0);
 virtual void AddLMAlphaS(double Q = 91.19);
 virtual void ScanLambda(TString DataName, int ipoint, int isNewPDF, TString TitleName);
 virtual void ScanLambdaPDF(int flavor, double x, double Q, int isNewPDF = 0);
 virtual void ScanLambdaAlphaS(double Q = 91.19);

 virtual void PDFLMScanPlotting(int flavor, double x, double Q, TString subName, vector<TString> DataList, int isNewPDF = 0);
 virtual void AlphaSLMScanPlotting(double Q, TString subName, vector<TString> DataList);

 virtual void LMScanModule(TString DataName, int ipoint, int isNewPDF, TString TitleName);
 virtual void PDFLMScanModule(int flavor, double x, double Q, int isNewPDF = 0);
 virtual void AlphaSLMScanModule(double Q = 91.19);

 vector<TString> LMScanDrawList;
 virtual void InputLMScanDrawList(vector<TString> list){this->LMScanDrawList = list;}

 map<tuple<int, double, double>, bool> isSetPDFLMScanXRange;
 virtual void SetPDFLMScanXRange(int flavor, double x, double Q, double xmin, double xmax){
   PDFLMScanPlotXMin[make_tuple(flavor, x, Q, 0)] = xmin;
   PDFLMScanPlotXMax[make_tuple(flavor, x, Q, 0)] = xmax;
   PDFLMScanPlotXMin[make_tuple(flavor, x, Q, 1)] = xmin;
   PDFLMScanPlotXMax[make_tuple(flavor, x, Q, 1)] = xmax;

   isSetPDFLMScanXRange[make_tuple(flavor, x, Q)] = true;
 }

 map<int, TString> FlavorNameMap;
 map<int, TString> TitleMap;
 map<TString, int> FlavorNameIndex;

 virtual void DefineCombination(){
   FittingHelper* Instance = new FittingHelper();
   Instance->DefineCombination(FlavorNameMap, TitleMap, FlavorNameIndex);
   delete Instance;

   /*FlavorNameMap[0] = "gluon";
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
   FlavorNameMap[19] = "uubar";
   FlavorNameMap[20] = "ddbar";

   TitleMap[0] = "gluon";
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
   TitleMap[18] = "#bar{u}/d";*/
 }

 map<TString, TString> DataLegend;
 map<int, Style_t> PlotLineStyle;

 virtual void SetLegend(TString name, TString legend){
   DataLegend[name] = legend;
   NickNameMap[name] = name;
 }

 virtual void DefineDataLegend(){
   FittingHelper* Instance = new FittingHelper();
   Instance->DefineCTEQDataLegend(DataLegend);
   delete Instance;

   /*DataLegend[(TString)"E245"] = "LHCb 7 TeV W/Z";
   DataLegend[(TString)"E246"] = "LHCb 8 TeV Z rapidity";
   DataLegend[(TString)"E249"] = "CMS 8 TeV A_{ch}";
   DataLegend[(TString)"E250"] = "LHCb 8 TeV W/Z";
   DataLegend[(TString)"E253"] = "ATLAS 8 TeV Z p_{T}";
   DataLegend[(TString)"E542"] = "CMS 7 TeV jet";
   DataLegend[(TString)"E544"] = "ATLAS 7 TeV jet";
   DataLegend[(TString)"E545"] = "CMS 8 TeV jet";
   DataLegend[(TString)"E573"] = "CMS 8 TeV Top";
   DataLegend[(TString)"E580"] = "ATLAS 8 TeV Top";
   DataLegend[(TString)"E160"] = "HERA I + II";
   DataLegend[(TString)"E101"] = "BCDMS F^{p}_{2}";
   DataLegend[(TString)"E102"] = "BCDMS F^{d}_{2}";
   DataLegend[(TString)"E104"] = "NMC F^{d}_{2}/F^{p}_{2}";
   DataLegend[(TString)"E108"] = "CDHSW F^{p}_{2}";
   DataLegend[(TString)"E109"] = "CDHSW x_{B}F^{p}_{3}";
   DataLegend[(TString)"E110"] = "CCFR F_{2}";
   DataLegend[(TString)"E111"] = "CCFR F_{3}";
   DataLegend[(TString)"E124"] = "NuTeV #nu#mu#mu SIDIS";
   DataLegend[(TString)"E125"] = "NuTeV #bar{#nu}#mu#mu SIDIS";
   DataLegend[(TString)"E126"] = "CCFR #nu#mu#mu SIDIS";
   DataLegend[(TString)"E127"] = "CCFR #bar{#nu}#mu#mu SIDIS";
   DataLegend[(TString)"E145"] = "H1";
   DataLegend[(TString)"E147"] = "HERA charm";
   DataLegend[(TString)"E169"] = "H1 F_{L}";
   DataLegend[(TString)"E201"] = "E605";
   DataLegend[(TString)"E203"] = "E866 pd/2pp";
   DataLegend[(TString)"E204"] = "E866 pp xf";
   DataLegend[(TString)"E206"] = "E906";
   DataLegend[(TString)"E225"] = "CDF run-1 A_{ch}";
   DataLegend[(TString)"E227"] = "CDF run-2 A_{ch}";
   DataLegend[(TString)"E234"] = "D0 run-2 A_{ch}";
   DataLegend[(TString)"E260"] = "D0 run-2 Z rapidity";
   DataLegend[(TString)"E261"] = "CDF run-2 Z rapidity";
   DataLegend[(TString)"E266"] = "CMS 7 TeV e A_{ch}";
   DataLegend[(TString)"E267"] = "CMS 7 TeV #mu A_{ch}";
   DataLegend[(TString)"E268"] = "ATLAS 7 TeV W/Z";
   DataLegend[(TString)"E281"] = "D0 run-2 A_{ch}";
   DataLegend[(TString)"E504"] = "CDF run-2 jet";
   DataLegend[(TString)"E514"] = "D0 run-2 jet";*/

   gStyle->SetLineStyleString(11, "20 12 4 12 4 12");
   gStyle->SetLineStyleString(12, "20 12 4 12 4 12 4 12 4 12");
   gStyle->SetLineStyleString(13, "20 20 12 12");
   gStyle->SetLineStyleString(14, "20 12 20 12 4 12 4 12");
   gStyle->SetLineStyleString(15, "80 20 4 12");
   for(int i = 2; i <= 100; i++){
     PlotLineStyle[i] = i;
   }
 }

 map<TString, TString> NickNameMap;
 map<TString, TString> FullNameMap;

 virtual void NameTransfer(){

   cout<<"Define nicknames..."<<endl;

   for(int i = 0; i < AllDataNames.size(); i++){

     for(auto iter = DataLegend.begin(); iter != DataLegend.end(); iter++){

       if(AllDataNames.at(i).Contains(iter->first)){
         NickNameMap[AllDataNames.at(i)] = iter->first;//long -> short
         break;
       }

     }
   }

   for(int i = 0; i < AllDataNames.size(); i++){//for those which the nickname is not defined
     if(NickNameMap.count(AllDataNames.at(i)) <= 0){
       TString legend = AllDataNames.at(i);
       int pos = legend.Last('/');
       if(pos >= 0){
         legend.Remove(0, pos + 1);
       }
       NickNameMap[AllDataNames.at(i)] = legend;
       DataLegend[legend] = legend;
     }
   }

   for(auto iter = NickNameMap.begin(); iter != NickNameMap.end(); iter++){
     FullNameMap[iter->second] = iter->first;//short -> long
   }

   for(auto iter = FullNameMap.begin(); iter != FullNameMap.end(); iter++){
     cout<<iter->first<<"  "<<iter->second<<endl;
   }

   cout<<"Nicknames defined finish."<<endl;
 }

 virtual double zbrnt(function<double(double)> func, double x1, double x2, double tolin, int &irt);
};

std::string ltrim(const std::string &s);
std::string rtrim(const std::string &s);
std::string trim(const std::string &s);

void TaylorCoeffs(double &dX, double &ddX,
                const double &X0, const double &Xp, const double &Xm,
                const double &Tp, const double &Tm, const double &Tbar);

#endif
