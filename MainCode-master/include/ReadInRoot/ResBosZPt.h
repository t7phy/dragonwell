#ifndef ReadInRoot_ResBosZPt_h
#define ReadInRoot_ResBosZPt_h

#include "ReadInRoot/ReadInRoot.h"
#include "Analysis/HistsResBos.h"

using namespace std;

class ResBosZPt : public ReadInRoot
{
 public:

 HistsResBos* myhists;

 TFile* DataFile_y1;
 TFile* DataFile_y2;
 TH1D* Efficiency;
 TH1D* KFactor;

 double BinCenter = 0.0;
 double BinLeft = 0.0;
 double BinRight = 0.0;
 double DataPoint = 0.0;
 double pTPoint = 0.0;
 double StaErr = 0.0;
 double UnCorrSysErr = 0.0;
 double CorrSysErr = 0.0;
 double LumiErr = 0.0;

 double QMin = 66.0;
 double QMax = 116.0;
 double yMin = 0.0;
 double yMax = 2.4;
 bool isOutput = false;

 vector<double> DataPoints;
 vector<double> DataErrors;

 vector<double> StaErrors;
 vector<double> UnCorrErrors;
 vector<double> CorrErrors;

 ResBosZPt();
 ResBosZPt(TString FileName);
 virtual void LinkHist(HistsResBos* &myhists);
 virtual void WriteIn(TH1D* h1, int MaxColumn = 10, bool isPercent = true);
 virtual void ReadKFactor(TH1D* h1, TString NNLOName, TString NLOName);
 virtual void GetTable(int id, TString y);
 virtual void InputDataFile(TString FileName_y1, TString FileName_y2);
 virtual void GetEfficiency(TString histName);
 virtual void GetKFactor(TString histName);
 virtual void GetDataAndErr(vector<double> &DataPoints, vector<double> &DataErrors);
 virtual void GetFullTable(vector<double> &DataPoints, vector<double> &StaErrors, vector<double> &UnCorrErrors, vector<double> &CorrErrors);
 virtual void InputPhaseSpace(double QMin, double QMax, double yMin, double yMax){this->QMin = QMin; this->QMax = QMax; this->yMin = yMin; this->yMax = yMax;isOutput = true;};
};
#endif
