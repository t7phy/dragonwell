#ifndef CTEQHelper_dtaReader_h
#define CTEQHelper_dtaReader_h

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "CTEQHelper/pdsReader.h"

using namespace std;

class dtaReader
{
 public:

 ifstream data;
 TFile* hf;

 string FileLine;

 int DataID = -999;
 double NormFac = 0.0;
 int Npt = 0;
 double Chi2 = 0.0;
 double Spartyness = 0.0;
 double Chi2N = 0.0;
 double R2 = 0.0;
 vector<double> rk;

 map<int, TString> DataNameMap;

 map<int, int> DataNpt;
 map<int, TH1D *> DataNormFac;
 map<int, TH1D *> DataChi2;
 map<int, TH1D *> DataSpartyness;
 map<int, TH1D *> DataChi2N;

 map<int, TH1D *> Y;
 map<int, TH1D *> Q;
 map<int, TH1D *> Rs;
 map<int, TH1D *> Exp;
 map<int, TH1D *> Theory;
 map<int, TH1D *> TotErr;
 map<int, TH1D *> ExpOverFit;
 map<int, TH1D *> ErrOverFit;
 map<int, TH1D *> ChiSq;
 map<int, TH1D *> Shift;
 map<int, TH1D *> ShiftedData;
 map<int, TH1D *> UnCorErr;
 map<int, TH1D *> ReducedChi2;
 map<int, TH1D *> lob;

 double SumOfChi2 = 0.0;
 map<int, double> SumOfReducedChi2;

 map<int, TH1D *> DataR2;
 map<int, TH1D *> Datark;
 map<int, bool> HasR2;

 vector<int> DataSet;

 map<TString, vector<pair<double, double>>> xQpair;
 map<TString, TGraphErrors*> xQplot;

 pdsReader* fPDF;

 TString subName = "";

 dtaReader(TString FileName);
 dtaReader(TString FileName, TString subName);

 virtual double GetSumOfReducedChi2(int id);
 virtual double GetAveReducedChi2(int id);
 virtual double GetChi2(int id);
 virtual double GetSumOfChi2();

 virtual int GetDataSize(){return DataSet.size();}
 virtual vector<int> GetDataSet(){return DataSet;}
 virtual int GetDataID(int i){return DataSet.at(i);}
 virtual int GetDataNpt(int i){return DataNpt[DataSet.at(i)];}
 virtual double GetTheoryPoint(int i, int ibin){return Theory[DataSet.at(i)]->GetBinContent(ibin);}
 virtual double GetYPoint(int i, int ibin){return Y[DataSet.at(i)]->GetBinContent(ibin);}
 virtual double GetQPoint(int i, int ibin){return Q[DataSet.at(i)]->GetBinContent(ibin);}
 virtual double GetRsPoint(int i, int ibin){return Rs[DataSet.at(i)]->GetBinContent(ibin);}
 virtual double GetExpPoint(int i, int ibin){return Exp[DataSet.at(i)]->GetBinContent(ibin);}
 virtual TString GetDataName(int i){return DataNameMap.at(GetDataID(i));}

 virtual void ReadFile();
 virtual void FillData();
 virtual void InitializePDF(TString name){fPDF = new pdsReader();fPDF->Initialize(name);};

 bool isLinkFile = false;
 virtual void openFile(TString name){isLinkFile = true; hf = new TFile(name, "RECREATE"); hf->cd();};
 virtual void SaveFile(){if(isLinkFile){hf->Write(); hf->Close();}};

};

#endif
