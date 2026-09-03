// CalcVBP.h: Calculation of Drell-Yan process
// Created on 2024/8/20 by Yao Fu
// Rewrite based on CTEQ global fitting code

#ifndef Calculation_CalcVBP_h
#define Calculation_CalcVBP_h

#include "RootCommon.h"
#include "Calculation/mDisPac.h"
#include "Calculation/CTUtil.h"
#include "Calculation/DataPoint.h"
#include "Calculation/Config.h"

using namespace std;

class CalcVBP : public CTUtil, public EwkSet, public QCDSet
{
 public:

 DataPoint m_vbpdata;
 vector<DataPoint> m_datatable;

 int Nbm = -1, Ntg = 1, IBsn = 2, IOrd = 2, Ischm = 0, Iscal = 0;
 bool LM = true, LL = false;
 double Rts = 1800.0, aMu = 10.0, Q = 10.0, Rer = 1e-4, aer = 0.0;
 double Pi = 3.1415926535898;

 double xa, xb;
 map<int, double> fa0;
 map<int, double> fb0;
 int ia, ib;

 int ixfx = 0;

 double qq4_ta, qq4_fa;
 double gq2_ta, gq2_tb;

 CalcVBP();

 virtual void InitializeData(Config setting, vector<DataPoint> DataTable);
 virtual void UpdateDataTable(vector<DataPoint> DataTable){
   if(DataTable.size() != m_datatable.size()) cout<<"ERROR! check data size."<<endl;

   for(int i = 0; i < DataTable.size(); i++){
     m_datatable.at(i).wp_kfac = DataTable.at(i).wp_kfac;
     m_datatable.at(i).wm_kfac = DataTable.at(i).wm_kfac;
   }
 }
 virtual void GetPrediction(vector<double> &result);
 virtual double CalculateVbp();
 virtual double Wprodint(double Y1, double Y2);
 virtual vector<DataPoint> Output(){return m_datatable;}
 virtual void ResetFit(){
   for(int i = 0; i < m_datatable.size(); i++){
     m_datatable.at(i).isUseKFactor = false;
   }
 }

 virtual void SetVBPPar(int Ihd1, int Ihd2, int Jbsn, int Jord, int Jschm, int Jscal);
 virtual void SetVBPVar(double Rs, double Qq, double Scle, double Rerr);
 virtual double VBPdy1(double y);

 function<double(double)> FMSQ;
 function<double(double)> FMSG;
 function<double(double)> QQ2;
 function<double(double)> QQ3;
 function<double(double, double, double, double, double)> GASTOT;
 function<double(double, double, double, double, double)> HASTOT;
 function<double(double)> QQ4B;
 function<double(double)> QQ4A;
 function<double(double)> GQ1;
 function<double(double)> QG1;
 function<double(double, double, double, double, double)> GCSTOT;
 function<double(double, double, double, double, double)> HCSTOT;
 function<double(double)> GQ2B;
 function<double(double)> QG2B;
 function<double(double)> GQ2A;
 function<double(double)> QG2A;
 bool isDefineVBPFunctions = false;
 virtual void DefineFunctions_VBP();

 // WlepY
 virtual void WlepY(int Ibsn, int Ibem, int Itgt, double rs, double y, double ptmin, double &xsec);
 virtual void WlepAsymK(int Ird, int Ibsn, int Ibem, int Itgt, double rs, double y, double ptmin, double ptmax, double wp_kfac, double wm_kfac, double &asym);
 virtual void ComputeBorn(int Ibem, int Itgt, double xamin, double xamax, double rtau, double Q, double y, double &tp, double &tm);

 int gq11_NSAVE;
 double gq11_D;
 vector<double> gq11_V = {0.0, 0.03376524,0.16939531,0.38069041,0.61930959,0.83060469,0.96623476};
 vector<double> gq11_R = {0.0, 0.08566225,0.18038079,0.23395697,0.23395697,0.18038079,0.08566225};
 virtual void gq11(double XMIN, double XMAX, int N, FortranArray1D<double> &X, FortranArray1D<double> Y, double &W);
 virtual void dist(double x, double q, FortranArray1D<double> &pd);

 // XsFact
 virtual void XsFact(int IXsec, int Ibsn, double &FAC0, double &FAC01, map<int, double> &FAC1, int N1);
 virtual void KineLmt(double Rs, double p1m, double p2m, double &yMx, double &ptMx);

 // Input
 map<tuple<int, int>, double> CP;
};
#endif
