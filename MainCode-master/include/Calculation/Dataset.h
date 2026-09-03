#ifndef Calculation_Dataset_h
#define Calculation_Dataset_h

#include "RootCommon.h"
#include "DataPoint.h"
#include "Tools/Tools.h"
#include "Tools/Log.h"
#include "Calculation/Prediction.h"
#include "Calculation/ApplGridHelper.h"
#include "Calculation/FastNLOHelper.h"
#include "Calculation/PineAPPLHelper.h"
#include "Calculation/CalcDIS.h"
#include "Calculation/CalcVBP.h"
#include "CTEQHelper/HoppetInterface.h"
#include "CTEQHelper/pdsReader.h"
#include "Calculation/Config.h"
#include "Calculation/ThreadRunAppl.h"
#include <Eigen/Dense>

using namespace std;

class Dataset
{
 public:

 int Irun = 0;

 bool isInitialize = false;
 TString DataType;
 TString ColliderType;
 TString CalcMode;
 TString subType;
 TString PDFType = "";
 int DataID = 0;

 Prediction* m_calculation = 0;
 vector<ApplGridHelper *> m_applgrid;
 vector<FastNLOHelper *> m_fnlo;
 vector<PineAPPLHelper *> m_pineappl;

 map<int, vector<double>> m_appl_xsec;
 map<int, pthread_t> threadAPPL;

 map<int, vector<double>> m_pineappl_xsec;
 map<int, pthread_t> threadPineAPPL;

 vector<double> m_theory;
 vector<double> m_corrected_data;
 vector<double> DataVector;
 HoppetInterface* m_pdf = 0;
 vector<TString> GridNames;

 ifstream datafile;
 string FileLine;

 vector<DataPoint> m_data;
 vector<DataPoint> saved_data;
 vector<vector<double>> FullTable;
 TString m_name;
 double NormErr;
 int NCorr;
 int NPoints;
 int NParam;
 vector<double> Param = {0.0, 0.0, 0.0};

 Eigen::VectorXd UnCorr;
 Eigen::VectorXd Data;
 Eigen::VectorXd Theory;
 Eigen::VectorXd saved_Theory;
 Eigen::VectorXd lambda;
 Eigen::MatrixXd beta;
 Eigen::MatrixXd b;
 Eigen::MatrixXd AMatrix;
 Eigen::VectorXd BVector;

 double FinalChi2 = 0.0;
 bool is_print = false;

 Dataset();
 Dataset(TString name);
 virtual void ReadFile(TString FileName, TString DataType, TString CalcMode, TString ColliderType, TString subType);
 virtual void ReadDYData(TString subType);
 virtual void ReadDISData(TString subType);
 virtual void ReadJetData(TString subType);
 virtual void SetDataID(int id){DataID = id;}

 vector<int> AppliedKFactorColumns = {};
 virtual void InputKFactorColumns(vector<int> columns){
   AppliedKFactorColumns = columns;
   for(int i = 0; i < m_data.size(); i++){
     m_data.at(i).AppliedKFactorColumns = columns;
   }
 }

 enum class KFactorType {Simple, Linear, Quadratic};
 struct OtherKFactor{
   KFactorType type;
   vector<double> parameters;
 };

 vector<vector<OtherKFactor>> OtherKFactorList;
 vector<double> FinalOtherKFactor;

 virtual void InputOtherKFactor(TString path);
 virtual void ApplyOtherKFactor(vector<double> zVec);

 virtual void LinkPDF(HoppetInterface* p){m_pdf = p;}

 bool isInputGrid = false;
 virtual void InputGridName(vector<TString> list){
   GridNames = list;
   isInputGrid = true;
   ApplGridRange.resize(GridNames.size());
   for(int i = 0; i < ApplGridRange.size(); i++){
     ApplGridRange.at(i) = vector<int>{-1, -1};
   }
 }
 vector<vector<int>> ApplGridRange;
 virtual void InputApplGridRange(int igrid, int firstbin, int lastbin){
   if(!isInputGrid){
     cout<<"Please input grid file first."<<endl;
     return;
   }
   if(igrid > GridNames.size()){
     cout<<"ApplGridRange setup out of range."<<endl;
     return;
   }
   if(firstbin > 0 && lastbin > 0){
     if(firstbin > lastbin){
       cout<<"lastbin should be greater than firstbin."<<endl;
       return;
     }
   }
   ApplGridRange.at(igrid - 1).clear();
   ApplGridRange.at(igrid - 1) = vector<int>{firstbin, lastbin};
 }

 vector<string> FNLOTableNames;
 virtual void InputFNLOTableName(vector<string> names){FNLOTableNames = names;}

 vector<string> PineAPPLGridNames;
 vector<tuple<vector<int>, TString>> PineAPPLGridMap;
 virtual void InputPineAPPLGridName(vector<string> names){PineAPPLGridNames = names;}
 virtual void InputPineAPPLGridMap(vector<tuple<vector<int>, TString>> gridmap){PineAPPLGridMap = gridmap;}

 virtual void InitialPrediction(Config setting);
 virtual void InitialPDF(Config setting);
 virtual void SubmitApplGridJobs();
 virtual void WaitApplGridJobs();
 virtual void SubmitPineAPPLJobs();
 virtual void WaitPineAPPLJobs();
 virtual void GetPrediction();

 virtual void PrepareChi2();
 virtual double Chi2(bool print);
 virtual void SetPrint(){is_print = true;}

 Logstream output;
 ostringstream savedta;
 std::string OutputLog() const{
   return savedta.str();
 }

 //Cut
 double VBPQminCut = 2.0, VBPQmaxCut = 130.0, VBPQTminCut = 40.0, VBPQTmaxCut = 110.0;
 virtual void SetDYCut(double Qmin, double Qmax, double QTmin, double QTmax){VBPQminCut = Qmin; VBPQmaxCut = Qmax; VBPQTminCut = QTmin; VBPQTmaxCut = QTmax;};

 double DISQminCut = 2.0, DISQmaxCut = 3000.0, DISWCut = 3.55249;
 virtual void SetDISCut(double Qmin, double Qmax, double Wmin){DISQminCut = Qmin; DISQmaxCut = Qmax; DISWCut = Wmin;}

 virtual void SetCut(Config setting){
   VBPQminCut = setting.VBPQminCut;
   VBPQmaxCut = setting.VBPQmaxCut;
   VBPQTminCut = setting.VBPQTminCut;
   VBPQTmaxCut = setting.VBPQTmaxCut;

   DISQminCut = setting.DISQminCut;
   DISQmaxCut = setting.DISQmaxCut;
   DISWCut = setting.DISWCut;
 }

 double Normalization = 1.0;
 bool isNormFit = false;
 double FacNor;
 double FacNor4;
 virtual void InputNormalization(double norm, double facnor, double facnor4){
   isNormFit = true;
   Normalization = norm;
   FacNor = facnor;
   FacNor4 = facnor4;
 }
 virtual void InputNormalization(double norm){
   isNormFit = true;
   Normalization = norm;
 }


 map<int, int> kSysMethod;
 virtual void InputSystematicMethod(map<tuple<int, int>, int> method){
   if(!isInitialize){
     cout<<"Please read data file first."<<endl;
     return;
   }
   for(auto iter = method.begin(); iter != method.end(); iter++){
     if(std::get<0>(iter->first) >= NCorr || std::get<1>(iter->first) >= NCorr){
       cout<<"Correlated systematic out of range."<<endl;
       return;
     }
     for(int i = std::get<0>(iter->first); i <= std::get<1>(iter->first); i++){
       kSysMethod[i] = iter->second;
     }
   }
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 bool isAdditionalCovariance = false;
 Eigen::MatrixXd AdditionalCovariance;

 map<TString, vector<vector<double>>> AdditionalCovMatrixMap;

 bool isPrepareLLT = false;
 Eigen::MatrixXd WMatrix;
 Eigen::MatrixXd LMatrix;
 Eigen::VectorXd zVector;

 vector<TString> AdditionalCorrMatrixNames;
 virtual void InputAdditionalCorrMatrix(vector<TString> names);

 virtual void ReadCovarianceMatrix(TString name);
 virtual void GetCovarianceMatrix();
 virtual void PrepareLLT();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 virtual vector<DataPoint> GetDataTable(){return m_data;}
 virtual DataPoint GetDataPoint(int ipoint){return m_data.at(ipoint);}

 virtual vector<double> GetTheoryTable(){return m_theory;}
 virtual double GetFinalData(int ipoint){return m_corrected_data.at(ipoint);}
 virtual double GetFinalTheory(int ipoint){return m_theory.at(ipoint);}

 virtual void SetDataTable(vector<DataPoint> data){
   m_data = data;
   if(data.size() > 0) CalcMode = data.at(0).CalcMode;
   if(data.size() == 0) CalcMode = "NULL";// When DataList doesn't have any of ApplGrid/FastNLO/PineAPPL/CTEQ/CTEQ_DY, give it a NULL.
 }

 bool isReorganize = false;
 virtual void PushTheoryPoint(double theory){m_theory.push_back(theory); isReorganize = true;}
 virtual void PushDataPoint(double data){DataVector.push_back(data); isReorganize = true;}

 virtual void ResetFit(){
   // Make the isUseKFactor being false in DIS and VBP calculation
   // Refresh the k-factor of DIS and VBP calculation

   if(m_data.size() > 0) CalcMode = m_data.at(0).CalcMode;

   if(CalcMode == "CTEQ"){
     m_calculation->CalcDIS::ResetFit();
   }

   if(CalcMode == "CTEQ_DY"){
     m_calculation->CalcVBP::ResetFit();
   }
 }
};
#endif
