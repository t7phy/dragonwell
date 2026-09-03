#ifndef Calculation_Config_h
#define Calculation_Config_h

#include "RootCommon.h"
#include "CTEQHelper/pdsReader.h"
#ifdef USE_LHAPDF
#include "LHAPDF/LHAPDF.h"
#include "LHAPDF/Reweighting.h"
#endif

#include "Tools/Log.h"

#include <assert.h>
#include <yaml-cpp/yaml.h>

#include "Calculation/FortranArray.h"

using namespace std;

class Config
{
 public:

 vector<int> LDis;
 vector<double> ThDis;
 vector<int> LVbp;
 vector<double> ThVbp;
 int Ipk = 22, IorQCD = 3, Fswitch = 0, Isch = 0, IorHrd = 3, IorEvl = 3, Nflv = 5;
 int imass = 0;
 double mc = 1.3, mb = 4.75, mt = 172.0;
 FortranArray1D<double> Amhat{0, 10};
 double Qini = 1.29;
 double AlphaS = 0.118;
 double AlphaS_Q0 = 91.19;
 TString EvolveType = "Hoppet";
 TString EvolveOption = "Default";
 bool isEvolveQED = false;
 bool isEvolveSmallx = false;
 TString PDFInputType = "None";
 TString PDFInput = "";
 int PDFiSet = 0;
 double dmeasRequirement = 1e-5;
 double Tolerance = 10.0;
 TString Tier2Type = "CTEQ";
 TString CalcLevel = "Full";
 map<int, tuple<TString, vector<int>, vector<double>>> LMPenaltyInput;

 int Jsfn, Jbsn, Jtgt, JBem;
 map<tuple<int, int>, double> CP;

 pdsReader* m_cteqpdf = 0;
#ifdef USE_LHAPDF
 LHAPDF::PDF* m_lhapdf;
#endif

 TString PDFName;
 int iSet;
 TString PDFType;

 int IFun = 1;

 TString AlgorithmName = "Migrad";
 int MaxCall = 1e6;
 double MinTol = 1e-6;
 int LFit = 30;
 int nDISThread = 55;
 int nVBPThread = 15;

 Config(){}

 virtual void ConfigOrder(int Ipk, int IorQCD, int Fswitch, int Isch, int IorHrd, int IorEvl, int Nflv){
   this->Ipk = Ipk;
   this->IorQCD = IorQCD;
   this->Fswitch = Fswitch;
   this->Isch = Isch;
   this->IorHrd = IorHrd;
   this->IorEvl = IorEvl;
   this->Nflv = Nflv;
 }

 virtual void ConfigMcbt(int imass, double mc, double mb, double mt){
   this->imass = imass;
   this->mc = mc;
   this->mb = mb;
   this->mt = mt;
 }

 virtual void ConfigQini(double Qini){
   this->Qini = Qini;
 }

 virtual void ConfigDis(vector<int> LDis, vector<double> ThDis){
   this->LDis = LDis;
   this->ThDis = ThDis;
 }

 virtual void ConfigVbp(vector<int> LVbp, vector<double> ThVbp){
   this->LVbp = LVbp;
   this->ThVbp = ThVbp;
 }

 double DISQminCut = 2.0;
 double DISQmaxCut = 3000.0;
 double DISWCut = 3.55249;
 virtual void ConfigDISCut(double Qmin, double Qmax, double Wmin){
   this->DISQminCut = Qmin;
   this->DISQmaxCut = Qmax;
   this->DISWCut = Wmin;
 }

 double VBPQminCut = 2.0;
 double VBPQmaxCut = 3000.0;
 double VBPQTminCut = 40.0;
 double VBPQTmaxCut = 150.0;
 virtual void ConfigVBPCut(double Qmin, double Qmax, double QTmin, double QTmax){
   this->VBPQminCut = Qmin;
   this->VBPQmaxCut = Qmax;
   this->VBPQTminCut = QTmin;
   this->VBPQTmaxCut = QTmax;
 }

 virtual void InputCP(map<tuple<int, int>, double> CP){
   this->CP = CP;
 }
 virtual void ConfigData(int Jsfn, int Jbsn, int Jtgt, int JBem){
   this->Jsfn = Jsfn;
   this->Jbsn = Jbsn;
   this->Jtgt = Jtgt;
   this->JBem = JBem;
 }

 virtual void ConfigPDF(TString PDFName, int iSet){
   LHAPDF::setPaths(getenv("LHAPDF_PDF_DIR"));//set PDF path
   m_lhapdf = LHAPDF::mkPDF(PDFName.Data(), iSet);
   this->PDFName = PDFName;
   this->iSet = iSet;
   PDFType = "LHAPDF";
 }
 virtual void ConfigPDF(TString PDFName){
   m_cteqpdf = new pdsReader();
   m_cteqpdf->Initialize(PDFName);
   PDFType = "CTEQ";
 }
 virtual void ConfigPDF(pdsReader* pdf){
   if(m_cteqpdf) delete m_cteqpdf;

   m_cteqpdf = new pdsReader();
   m_cteqpdf->CopyHeader(pdf);
   m_cteqpdf->InputAlphaS(pdf->AlsCTEQ);
   m_cteqpdf->InputUPD(pdf->UPD);

   PDFType = "CTEQ";
 }
 virtual double GetPDF(int flavor, double x, double Q){
   if(x >= 1.0 || x < 0.0){
     cout<<"Config GetPDF: x out of range"<<endl;
     return 0.0;
   }
   if(PDFType == "LHAPDF") return m_lhapdf->xfxQ(flavor, x, Q) / x;
   else if(PDFType == "CTEQ") return m_cteqpdf->Getf(flavor, x, Q);
   //else if(PDFType == "CTEQ") return m_cteqpdf->xfxQ(flavor, x, Q) / x;
   else return 0.0;
 }

 map<TString, double> FittingParameter;
 map<int, double> IDtoParam;
 map<TString, int> ParIndex;
 map<int, int> IDtoIndex;

// map<int, int> IDIndex;
// vector<TString> ParameterList;
// vector<int> IDList;

// vector<TString> IterateParList;

// map<int, TString> ParName;
// map<int, int> ParID;
// map<int, double> ParCentral;
// map<int, double> ParStep;
// map<int, double> ParLeft;
// map<int, double> ParRight;
// map<int, TString> IDtoName;
// map<TString, int> NametoID;

 struct ParInformation{
   int index;
   int id;
   TString name;
   double central;
   double step;
   double left;
   double right;
   double FittingError;
 };
 vector<ParInformation> ParameterList;
 vector<ParInformation> IterateParList;

 virtual void ConfigParameter(int i, int id, TString name, double central, double step, double left, double right){
   ParInformation par;
   par.index = i;
   par.id = id;
   par.name = name;
   par.central = central;
   par.step = step;
   par.left = left;
   par.right = right;

   ParameterList.push_back(par);
   if(fabs(step) > 1e-16) IterateParList.push_back(par);

   FittingParameter[name] = central;
   IDtoParam[id] = central;
   ParIndex[name] = i;
   IDtoIndex[id] = i;

//   ParName[i] = name;
//   ParID[i] = id;
//   ParCentral[i] = central;
//   ParStep[i] = step;
//   ParLeft[i] = left;
//   ParRight[i] = right;

//   ParIndex[name] = i;
//   IDIndex[id] = i;

//   IDtoName[id] = name;
//   NametoID[name] = id;

//   ParameterList.push_back(name);
//   IDList.push_back(id);

//   if(fabs(step) > 1e-16) IterateParList.push_back(name);
 }

 virtual int GetNPar() {return ParameterList.size();}
 virtual TString GetParName(int i){return ParameterList.at(i).name;}
 virtual int GetParID(int i){return ParameterList.at(i).id;}
 virtual double GetParCentral(int i){return ParameterList.at(i).central;}
 virtual double GetParStep(int i){return ParameterList.at(i).step;}
 virtual double GetParLeft(int i){return ParameterList.at(i).left;}
 virtual double GetParRight(int i){return ParameterList.at(i).right;}
 virtual double GetParError(int i){return ParameterList.at(i).FittingError;}
 virtual int GetParIndex(int id){return IDtoIndex.at(id);}

 vector<double> GetInitialParameters(){
   vector<double> InitialParameters;
   for(int i = 0; i < ParameterList.size(); i++){
     InitialParameters.push_back(ParameterList.at(i).central);
   }
   return InitialParameters;
 }

// virtual void SetParName(int i, TString name){ParameterList.at(i).name = name; ParIndex[name] = i;}
// virtual void SetParID(int i, int id){ParameterList.at(i).id = id;}
 virtual void SetParCentral(int i, double central){ParameterList.at(i).central = central; FittingParameter[ParameterList.at(i).name] = central; IDtoParam[ParameterList.at(i).id] = central;}
// virtual void SetParStep(int i, double step){ParameterList.at(i).step = step;}
// virtual void SetParLeft(int i, double left){ParameterList.at(i).left = left;}
// virtual void SetParRight(int i, double right){ParameterList.at(i).right = right;}
// virtual void SetParError(int i, double error){ParameterList.at(i).FittingError = error;}

 virtual void OutputParameters(){
   for(int i = 0; i < ParameterList.size(); i++){
     cout<<i<<"  "<<ParameterList.at(i).id<<"  "<<ParameterList.at(i).name<<"  "<<ParameterList.at(i).central<<"  "<<ParameterList.at(i).step<<"  "<<ParameterList.at(i).left<<"  "<<ParameterList.at(i).right<<endl;
   }
 }

 map<TString, vector<int>> ShapeParameter;
 map<TString, vector<double>> ShapeParameterValue;
 virtual void MatchShapeParameter(TString flavor, vector<int> ParamID, vector<double> ParamValue){
   ShapeParameter[flavor] = ParamID;
   ShapeParameterValue[flavor] = ParamValue;
   if(ShapeParameter[flavor].size() != ShapeParameterValue[flavor].size()){
     cout<<"ERROR! Parameters and Values don't match!"<<endl;
     return;
   }
   //for(int i = 0; i < ShapeParameter[flavor].size(); i++){
   //  if(ShapeParameter[flavor].at(i) == 0) continue;
   //  IDtoParam.at(ShapeParameter[flavor].at(i)) = ShapeParameterValue[flavor].at(i);
   //}
 }
 virtual void RefreshShapeParameter(){
   for(auto iter = ShapeParameter.begin(); iter != ShapeParameter.end(); iter++){
     for(int i = 0; i < iter->second.size(); i++){
       if(iter->second.at(i) == 0) continue;
       ShapeParameterValue.at(iter->first).at(i) = IDtoParam.at(iter->second.at(i));
     }
   }
 }

 struct OtherParameter{
   int id = -999;
   TString name = "";
   TString type = "";
   double central = 0.0;
   bool isFit = false;
 };

 vector<OtherParameter> OtherParameterList;
 map<TString, double> OtherParameterCentral;
 map<TString, int> OtherParameterID;
 map<TString, int> OtherParameter_isFit;

 TString DataGlobalPath;
 TString ApplGlobalPath;
 TString FNLOGlobalPath;
 TString PineGlobalPath;

 struct DataInformation{
   TString DataName = "";
   TString DataPath = "";
   TString DataType = "";
   TString CalcMode = "";
   TString Collider = "";
   TString subType = "";
   int DataID = 0;
   vector<TString> ApplGrids = {};
   vector<vector<int>> ApplRange = {};
   vector<string> FastNLOGrids = {};
   vector<string> PineAPPLGrids = {};
   vector<tuple<vector<int>, TString>> PineAPPLGridMap = {};
   vector<int> KFactors = {};
   vector<vector<TString>> OtherKFactors = {};
   vector<vector<int>> SystematicMethod = {};
   map<tuple<int, int>, int> SystematicMethodMap;
   vector<double> Normalization = {};
   TString NormParName = "";
   vector<TString> AdditionalCorrMatrix = {};
 };

 vector<DataInformation> DataList;
 map<TString, int> NametoIndex;

 map<TString, vector<int>> NormParDataList;

 virtual void ParseDataList(TString filename);

 vector<TString> FlavorList = {};
 vector<int> FlagList = {};
 vector<double> MomentumList = {};
 vector<double> B0List = {};
 double InitialgluonMomentum = 0.0;
 double InitialStrangeB0 = 0.0;
 virtual void ParseParameter(TString filename);
 virtual void CloneParameter(Config setting);
 virtual void ParseConfig(TString filename);
 virtual void OutputNewParameterFile(TString filename);
};
#endif
