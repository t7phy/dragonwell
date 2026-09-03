// CalcDIS.h: Calculation of DIS process
// Created on 2024/08/02 by Yao Fu
// Rewrite based on CTEQ global fitting code

#ifndef Calculation_CalcDIS_h
#define Calculation_CalcDIS_h

#include "RootCommon.h"
#include "Calculation/mDisPac.h"
#include "Calculation/CTUtil.h"
#include "Calculation/DataPoint.h"
#include "Calculation/Config.h"

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
#include "hoppet.h"
#include "hoppet_oo.h"
#include "hoppet/base_types.h"
#include "hoppet/fortran_prototypes.h"
#endif

#ifdef USE_LIBOME
#include <ome/ome.h>
#endif

using namespace std;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
extern "C" {
  double hoppet_get_C2LO_clone(void);
  double hoppet_get_CLLO_clone(void);
  double hoppet_get_C3LO_clone(void);
  void* hoppet_get_C2NLO_clone();
  void* hoppet_get_CLNLO_clone();
  void* hoppet_get_C3NLO_clone();
  void* hoppet_get_C2NNLO_clone();
  void* hoppet_get_CLNNLO_clone();
  void* hoppet_get_C3NNLO_clone();
  void* hoppet_get_C2N3LO_clone();
  void* hoppet_get_CLN3LO_clone();
  void* hoppet_get_C3N3LO_clone();
  void* hoppet_get_C2N3LO_fl11_clone();
  void* hoppet_get_CLN3LO_fl11_clone();
  void* hoppet_get_P_LO_clone();
  void* hoppet_get_P_NLO_clone();
  void* hoppet_get_P_NNLO_clone();
  void* hoppet_get_P_N3LO_clone();
}
#endif

class CalcDIS : public mDisPac, public CTUtil
{
 public:

 DataPoint m_disdata;
 vector<DataPoint> m_datatable;

 bool CC = false;
 FortranArray2D<int> Qpdf{-6, 6, -6, 6};

 int iOrdr, iSchm;
 double Q0 = 1.29, ScalFc, achi;       // Q0 is the Qmin below which PDFs are not defined;
                                       // With iFscle = 1, aMu is defined to be always > Q0.
                                       // ScalFc is the (dimensionless) factorization scale;
                                       // With iFscle = 2,3, aMu ~ ScalFc * the physical scale. 
                                       // achi is the shape parameter in the rescaling variable chi

 int kProc;

 CalcDIS();
 virtual void InitializeData(Config setting, vector<DataPoint> DataTable);
 virtual void GetPrediction(vector<double> &result);
 virtual double CalculateDis();
 virtual void CheckFlv(int iflv);
 virtual vector<DataPoint> Output(){return m_datatable;}
 virtual void ResetFit(){
   for(int i = 0; i < m_datatable.size(); i++){
     m_datatable.at(i).isUseKFactor = false;
   }
 }

 virtual void DatAdj(DataPoint &m_data);
 virtual void HtgAdj(DataPoint &m_data);

 function<double(int)> EffXsc;
 virtual double xSecLh(int iLptn1, int iLptn2, int iHadn, double x, double Q, double y, int iFlv, int iXsc);
 virtual double StrFnGm(int iHadn, int iCmptn, double x, double Q, int iSfn, int iFlv);

 virtual double xSecLh_N3LO(int iLptn1, int iLptn2, int iHadn, double x, double Q, double y, int iFlv, int iXsc);
 virtual double StrFnGm_N3LO(int iHadn, int iCmptn, double x, double Q, int iSfn, int iFlv);

 int nHeavy = 4;
 int iFschm = 0, iFscle = 0, mSwtch = 0;
 double W;
 int aPrtn1, aPrtn2;
 int NFAboveThr;
 int nPrtn1 = 3;
 int nPrtn2 = 6;
 double aM1, aM2, Zeta;
 bool SemiInclusiveF2c = true;
 FortranArray2D<int> AboveThreshold{1, 6, 1, 6};
 virtual void SfnGm(int iHadn, int iCmptn, int iFlv, double x, double Q, FortranArray1D<double> &Sfn123, FortranArray1D<double> &SfnHel);
 virtual void SfnGm_N3LO(int iHadn, int iCmptn, int iFlv, double x, double Q, FortranArray1D<double> &Sfn123, FortranArray1D<double> &SfnHel);

 double Fnxlo_xold = -1.0, Fnxlo_Qold = -1.0, Fnxlo_amuold = -1.0;
 int Fnxlo_iHadnOld = -1000;
 double F2ZMPSsave, F2ZMGsave, FLZMPSsave, FLZMGsave;
 virtual void Fnxlo(int iHadn, double x, double Q, double aMu, int iPrtn, double &F2out, double &FLout);
 virtual void ExamineMassThresholds();

 double cchi_ax;
 double cchi_achi1;
 double cchi_akappa;
 function<double(double)> zetadiff;
 virtual double fchi(double x, double Q, double am1, double am2);

 // SfZm0Q
 int CSfZm1G_iHadn;
 double CSfZm1G_x;
 double CSfZm1G_aMu;

 int CSfZm1Q_iHadn;
 int CSfZm1Q_iPartn;
 double CSfZm1Q_x;
 double CSfZm1Q_aMu;
 double CSfZm1Q_Pdfnx;

 virtual void SfZm0Q(int iHadn, int iPrtn, double x, double Q, double aMu, FortranArray1D<double> &SfnG);
 virtual void SfZm1G(int iHadn, double x, double Q, double vMu, FortranArray1D<double> &SfnG);
 virtual void SfZm1Q(int iHadn, int iPrtn, double x, double Q, double vMu, FortranArray1D<double> &SfnG);

 function<double(double)> aC2G1;
 function<double(double)> aC2MC1G1;
 function<double(double)> aPgqFx;
 function<double(double)> aC2Q1;
 function<double(double)> aF2Q1;
 function<double(double)> G2M1Q1;
 function<double(double)> G1M3Q1;
 function<double(double)> aPqq;
 function<double(double)> aPqqFx;
 bool isDefineGluonFunctions = false;
 bool isDefineQuarkFunctions = false;
 virtual void DefineFunctions_gluon();
 virtual void DefineFunctions_quark();

 // Acot05
 function<double(double)> xNloG;
 function<double(double)> xActSub;
 virtual void Acot0Q(int iHadn, int iPrtn, double F1M, double F2M, double x, double Q, double aMu, FortranArray1D<double> &SfnG);
 virtual void Omg0(double Q, double F1M, double F2M, FortranArray1D<double> &OmgLo);
 virtual void Acot1G(int iHadn, double M2, double M1, double x, double Q, double vMu, FortranArray1D<double> &SfnG);
 virtual void OmgG1(double x, double Q, double F1M, double F2M, FortranArray1D<double> &OmgNlo);
 virtual void AcotSub(int iHadn, int iPrtn, double F1m, double F2m, double x, double Q, double vMu, FortranArray1D<double> &Subtr);

 // GotSK1Q
 int CxNloSK_iHad;
 int CxNloSK_iPart;
 double CxNloSK_x;
 double CxNloSK_aMu;
 double CxNloSK_F2M;
 double CxNloSK_Q;

 double DL;
 int index_idxi = 0;
 int index_idxj = 0;

 function<double(double)> DKA;
 function<double(double)> HQ0_D;
 function<double(double)> HQ0_N;
 function<double(double)> HQ0_P;
 function<double(double)> HQ0_PM;
 function<double(double)> HQ0_P1;
 function<double(double)> HQA_D;
 function<double(double)> HQB_P;
 function<double(double)> HQB_PM;
 function<double(double)> HQB_P1;
 function<double(double)> aPqqFxSK;
 bool isDefineSK1QFunctions = false;
 virtual void DefineFunctions_SK1Q();

 virtual void GotSK1Q(int iHadx, int iPartx, double F2Mx, double x, double Q, double aMu, FortranArray1D<double> &SfnG);

 // KinForm
 virtual void SFnConv(FortranArray1D<double> SFnIred, FortranArray1D<double> g2chi, FortranArray1D<double> &SFnTen, FortranArray1D<double> &SFnHel);
 virtual void F2LConvNC(double F2o, double FLo, FortranArray1D<double> &SFnTen, FortranArray1D<double> &SFnHel);

 // GmJS
 function<double(double)> F2HQgint;
 function<double(double)> F2hint;
 function<double(double)> F2lint;
 function<double(double)> FLhint;
 function<double(double)> FLlint;
 function<double(double)> F2lNSSubint;
 function<double(double)> F2HQS1;
 function<double(double)> AnalyticF2HQS1;
 function<double(double)> F2HQS2;
 function<double(double)> F2HQS3;
 function<double(double)> F2HQS4;
 function<double(double)> F2HQg0int;
 function<double(double)> F2HQS0int;
 function<double(double)> FLHQgint;
 function<double(double, int)> clnp1a;
 function<double(double)> FLsub1;
 function<double(double)> FLHQSint;
 function<double(double)> FLHQg0int;
 function<double(double)> FLLNS2int;
 function<double(double)> FLLNS2int0;
 function<double(double)> cL1llint;
 function<double(double)> F2LNS2int;
 function<double(double)> F2LNS2int0;
 function<double(double)> c1llint;
 virtual double F2hg2(double x, double Q, double aMu, double aMs, int iHad);
 virtual double F2hlPS2(double x, double Q, double aMu, double aMs, int iHad);
 virtual double SiF2l(double x, double Q, double aMu, double aMs, int iHad, int iPrtn);
 virtual double FLhlPS2(double x, double Q, double aMu, double aMs, int iHad);
 virtual double SiFLl(double x, double Q, double aMu, double aMs, int iHad, int iPrtn);
 virtual double F2lNSSub(double x, double Q, double aMu, double aMs, int iHad, int iPrtn);
 virtual double F2HQSub2(double x, double Q, double aMu, double aMs, int iHad);
 virtual double F2HQg0(double x, double Q, double aMu, double aMs, int iHad, int Nptn);
 virtual double F2HQSub0(double x, double Q, double aMu, double aMs, int iHad, int Nptn);
 virtual double FLhg2(double x, double Q, double aMu, double aMs, int iHad);
 virtual double FLHQSub2(double x, double Q, double aMu, double aMs, int iHad);
 virtual double FLHQg0(double x, double Q, double aMu, double aMs, int iHad, int Nptn);
 virtual double FLLNS2(double x, double Q, double aMu, double aMs, int iHad, int iPrtn);
 virtual double F2LNS2(double x, double Q, double aMu, double aMs, int iHad, int iPrtn);

 // GmJSa
 double fgtcorr = 0.0;
 double xsctca = 0.0;
 double xsctcf = 0.0;
 double xsctba = 0.0;
 double xctca = 0.0;
 double xctcf = 0.0;
 double xctbar = 0.0;

 double fhqtcorr = 0.0;
 double xschqt = 0.0;
 double xchqt = 0.0;
 double xsqtbar = 0.0;
 double xqtbar = 0.0;

 double flqtcorr = 0.0;
 double xsclqt = 0.0;
 double xclqt = 0.0;

 virtual double LLNSqr(double z, double xi);
 virtual double L2NSqr(double z, double xi);
 virtual double L2NSqr0(double z, double xi);
 virtual double AsyLLNSq(double z, double xi);
 virtual double AsyL2NSq(double z, double xi);
 virtual double A1Hg(double z, double eps);
 virtual double A2PSHq(double z, double eps);
 virtual double A2NSqqPlus(double z, double eps);
 virtual double A2NSqqFinite(double z, double eps);
 virtual double A2Hg(double z, double eps);
 virtual double HQcoef(int iFn, double z, double Q, double amu, double ams);
 virtual double HQhqlcoef(int iFn, double z, double Q, double amu, double ams);
 virtual double HQlqcoef(int iFn, double z, double Q, double amu, double ams);
 virtual double HQcoef0(int iFn, double z, double Q, double amu, double ams);
 virtual double HQcoef0A(int iFn, double z, double Q, double amu, double ams);
 virtual void sclca(double eta, double xi, double &Value);
 virtual void sclcf(double eta, double xi, double &Value);
 virtual void sclbar(double eta, double xi, double &Value);
 virtual void sctbar(double eta, double xi, double &Value);
 virtual void sctca(double eta, double xi, double &Value);
 virtual void sctcf(double eta, double xi, double &Value);
 virtual void schql(double eta, double xi, double &Value);
 virtual void schqt(double eta, double xi, double &Value);
 virtual void sqlbar(double eta, double xi, double &Value);
 virtual void sqtbar(double eta, double xi, double &Value);
 virtual void sclql(double eta, double xi, double &Value);
 virtual void sclqt(double eta, double xi, double &Value);

 virtual void locate(FortranArray1D<double> xx, int n, double x, int &j);

 function<double(double)> fii;
 function<double(double)> fjj;
 function<double(double)> asymp_l;
 function<double(double)> asymp_t;
 function<double(double)> asympbar_l;
 function<double(double)> asympbar_t;
 function<double(double, double)> threshf_l;
 function<double(double, double)> threshf_t;
 function<double(double, double)> thresha_t;
 function<double(double, double)> thresha_l;
 function<double(double, double)> threshbar_l;
 function<double(double, double)> threshbar_t;
 function<double(double, double)> born_t;
 function<double(double, double)> bora_t;
 function<double(double, double)> born_l;
 function<double(double, double)> bora_l;
 bool isDefineGmJSaFunctions = false;
 virtual void DefineFunctions_GmJSa();

 FortranArray2D<double> sclca_calcpts;
 FortranArray1D<double> sclca_dlaeta;
 FortranArray1D<double> sclca_dlaxi;
 FortranArray2D<double> sclcf_calcpts;
 FortranArray1D<double> sclcf_dlaeta;
 FortranArray1D<double> sclcf_dlaxi;
 FortranArray2D<double> sclbar_calcpts;
 FortranArray1D<double> sclbar_dlaeta;
 FortranArray1D<double> sclbar_dlaxi;
 FortranArray2D<double> sctbar_calcpts;
 FortranArray1D<double> sctbar_dlaeta;
 FortranArray1D<double> sctbar_dlaxi;
 FortranArray2D<double> sctca_calcpts;
 FortranArray1D<double> sctca_dlaeta;
 FortranArray1D<double> sctca_dlaxi;
 FortranArray2D<double> sctcf_calcpts;
 FortranArray1D<double> sctcf_dlaeta;
 FortranArray1D<double> sctcf_dlaxi;
 FortranArray2D<double> schql_calcpts;
 FortranArray1D<double> schql_dlaeta;
 FortranArray1D<double> schql_dlaxi;
 FortranArray2D<double> schqt_calcpts;
 FortranArray1D<double> schqt_dlaeta;
 FortranArray1D<double> schqt_dlaxi;
 FortranArray2D<double> sqlbar_calcpts;
 FortranArray1D<double> sqlbar_dlaeta;
 FortranArray1D<double> sqlbar_dlaxi;
 FortranArray2D<double> sqtbar_calcpts;
 FortranArray1D<double> sqtbar_dlaeta;
 FortranArray1D<double> sqtbar_dlaxi;
 FortranArray2D<double> sclql_calcpts;
 FortranArray1D<double> sclql_dlaeta;
 FortranArray1D<double> sclql_dlaxi;
 FortranArray2D<double> sclqt_calcpts;
 FortranArray1D<double> sclqt_dlaeta;
 FortranArray1D<double> sclqt_dlaxi;
 bool isInitialGmJSaMatrix = false;
 virtual void InitialGmJSaMatrix();

 // hqnnlocoef
 virtual void c2hqg20a_xfitter(double eta, double xi, double &Value);
 virtual void c2hqg20b_xfitter(double eta, double xi, double &Value);
 virtual void c2hqg20p_xfitter(double eta, double xi, double &Value);
 virtual void c2hqg20m_xfitter(double eta, double xi, double &Value);
 virtual void c2hqg21_xfitter(double eta, double xi, double &Value);
 virtual void c2hqg22_xfitter(double eta, double xi, double &Value);
 bool isInitialhqnnloMatrix = false;
 virtual void InitialhqnnloMatrix();

 FortranArray2D<double> c2hqg20a_xfitter_calcpts;
 FortranArray1D<double> c2hqg20a_xfitter_dlaeta;
 FortranArray1D<double> c2hqg20a_xfitter_dlaxi;
 FortranArray2D<double> c2hqg20b_xfitter_calcpts;
 FortranArray1D<double> c2hqg20b_xfitter_dlaeta;
 FortranArray1D<double> c2hqg20b_xfitter_dlaxi;
 FortranArray2D<double> c2hqg20p_xfitter_calcpts;
 FortranArray1D<double> c2hqg20p_xfitter_dlaeta;
 FortranArray1D<double> c2hqg20p_xfitter_dlaxi;
 FortranArray2D<double> c2hqg20m_xfitter_calcpts;
 FortranArray1D<double> c2hqg20m_xfitter_dlaeta;
 FortranArray1D<double> c2hqg20m_xfitter_dlaxi;
 FortranArray2D<double> c2hqg21_xfitter_calcpts;
 FortranArray1D<double> c2hqg21_xfitter_dlaeta;
 FortranArray1D<double> c2hqg21_xfitter_dlaxi;
 FortranArray2D<double> c2hqg22_xfitter_calcpts;
 FortranArray1D<double> c2hqg22_xfitter_dlaeta;
 FortranArray1D<double> c2hqg22_xfitter_dlaxi;

 virtual void c2hqg20a_newasym(double eta, double xi, double &Value);
 FortranArray2D<double> c2hqg20a_newasym_calcpts;
 FortranArray1D<double> c2hqg20a_newasym_dlaeta;
 FortranArray1D<double> c2hqg20a_newasym_dlaxi;
 virtual void c2hqg21_newasym(double eta, double xi, double &Value);
 FortranArray2D<double> c2hqg21_newasym_calcpts;
 FortranArray1D<double> c2hqg21_newasym_dlaeta;
 FortranArray1D<double> c2hqg21_newasym_dlaxi;
 virtual void c2hqg21(double eta, double xi, double &Value);
 FortranArray2D<double> c2hqg21_calcpts;
 FortranArray1D<double> c2hqg21_dlaeta;
 FortranArray1D<double> c2hqg21_dlaxi;
 virtual void c2hqg22(double eta, double xi, double &Value);
 FortranArray2D<double> c2hqg22_calcpts;
 FortranArray1D<double> c2hqg22_dlaeta;
 FortranArray1D<double> c2hqg22_dlaxi;

 virtual void c2hqps20a(double eta, double xi, double &Value);
 FortranArray2D<double> c2hqps20a_calcpts;
 FortranArray1D<double> c2hqps20a_dlaeta;
 FortranArray1D<double> c2hqps20a_dlaxi;
 virtual void c2hqps20b(double eta, double xi, double &Value);
 FortranArray2D<double> c2hqps20b_calcpts;
 FortranArray1D<double> c2hqps20b_dlaeta;
 FortranArray1D<double> c2hqps20b_dlaxi;
 virtual void c2hqps21(double eta, double xi, double &Value);
 FortranArray2D<double> c2hqps21_calcpts;
 FortranArray1D<double> c2hqps21_dlaeta;
 FortranArray1D<double> c2hqps21_dlaxi;
 virtual void c2hqps22(double eta, double xi, double &Value);
 FortranArray2D<double> c2hqps22_calcpts;
 FortranArray1D<double> c2hqps22_dlaeta;
 FortranArray1D<double> c2hqps22_dlaxi;

 // ZmNNLO
 function<double(double)> F2CnsQns2;
 function<double(double)> FLCnsQns2;
 function<double(double)> F2CqQPS;
 function<double(double)> F2CgG;
 function<double(double)> FLCqQPS;
 function<double(double)> FLCgG;

 function<double(int, double, double, double)> Dkfun;
 function<double(vector<double>, int)> c2np2Dk0;
 function<double(double, int)> c2np2a0;
 function<double(double, double, double, int)> c2np2Dk;
 function<double(double, int)> c2s2aL;
 function<double(double, int)> c2g2aL;
 function<double(double, int)> c2mnp2a2;
 function<double(double, int)> c2mnp2a1;
 function<double(double, int)> c2ms2a2;
 function<double(double, int)> c2ms2a1;
 function<double(double, int)> c2mg2a2;
 function<double(double, int)> c2mg2a1;
 function<double(vector<double>, int)> c2mnp2Dk2a;
 function<double(vector<double>, int)> c2mnp2Dk1a;
 function<double(double, double, double, int)> c2mnp2Dk2;
 function<double(double, double, double, int)> c2mnp2Dk1;
 function<double(double, int)> clnp2a;
 function<double(double, int)> cls2aL;
 function<double(double, int)> clg2aL;
 function<double(double, int)> clmnp2a;
 function<double(double, int)> clms2a;
 function<double(double, int)> clmg2a;

 bool isDefineNNLOFunctions = false;
 virtual void DefineFunctions_nnlo();
 virtual double F2ZMNS2(double x, double Q, double aMu, int iHad, int iPrtn, int Nptn1);
 virtual double FLZMNS2(double x, double Q, double aMu, int iHad, int iPrtn, int Nptn1);
 virtual double F2ZMPS2(double x, double Q, double aMu, int iHad);
 virtual double F2ZMG2(double x, double Q, double aMu, int iHad);
 virtual double FLZMPS2(double x, double Q, double aMu, int iHad);
 virtual double FLZMG2(double x, double Q, double aMu, int iHad);

 // N3LO
 virtual double xCahi(int iFn, int igq, int ord, int iAB, int nf, double z, double q, double mu, double mh);
 virtual double xC2hi20AB(int igq, int iAB, double x, double q, double mu, double mh, int nf);
 virtual double FahiNNLO(double x, double Q, int iFn, int igq, int ord, int iAB, int nf, double mu, double mh);

 virtual double GetxC2Hg3Lmu1(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxC2Hg3Lmu2(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxC2Hq3Lmu1(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxC2Hq3Lmu2(int ihadron, double x, double Q, double QMu, double MQ);

 // cgt2
 virtual double cgt2(double eta, double xi, int nf);
 virtual double cgt2br1(double eta, double xi);
 virtual double cgt2br2(double eta, double xi);
 virtual double nlotconst(double xi);
 virtual double nlotbarconst(double xi);
 virtual double cgt2pade(double eta, double xi);

 // high-energy-c2g
 virtual double chx0g2(double x, double xi);
 virtual double chxbg2(double x, double xi);
 virtual double chxbbg2(double x, double xi);

 // hq-asy
 virtual double H2g1L0(double x, double q2, double m2, int nf);
 virtual double H2g2L0(double x, double q2, double m2, int nf);
 virtual double H2g3L0(double x, double q2, double m2, int nf);
 virtual double H2g2L1(double x, double q2, double m2, int nf);
 virtual double H2g3L1(double x, double q2, double m2, int nf);
 virtual double H2g3L2(double x, double q2, double m2, int nf);
 virtual double H2q2L0(double x, double q2, double m2, int nf);
 virtual double H2q3L0(double x, double q2, double m2, int nf);
 virtual double H2q2L1(double x, double q2, double m2, int nf);
 virtual double H2q3L1(double x, double q2, double m2, int nf);
 virtual double H2q3L2(double x, double q2, double m2, int nf);

 // afit
 virtual double aQg30(double x);
 virtual double aQgA30(double x);
 virtual double aQgB30(double x);
 virtual double aQg30new(double x);
 virtual double aQqPS30(double x);
 virtual double aQqPSA30(double x);
 virtual double aQqPSB30(double x);
 virtual double aQqPS30new(double x);

 // hoppet N3LO
 double Hoppet_C2LO;
 double Hoppet_CLLO;
 double Hoppet_C3LO;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 hoppet::split_mat Hoppet_C2NLO;
 hoppet::split_mat Hoppet_CLNLO;
 hoppet::split_mat Hoppet_C3NLO;

 hoppet::split_mat Hoppet_C2NNLO;
 hoppet::split_mat Hoppet_CLNNLO;
 hoppet::split_mat Hoppet_C3NNLO;

 hoppet::split_mat Hoppet_C2N3LO;
 hoppet::split_mat Hoppet_CLN3LO;
 hoppet::split_mat Hoppet_C3N3LO;
 hoppet::split_mat Hoppet_C2N3LO_fl11;
 hoppet::split_mat Hoppet_CLN3LO_fl11;

 hoppet::split_mat Hoppet_P_LO;
 hoppet::split_mat Hoppet_P_NLO;
 hoppet::split_mat Hoppet_P_NNLO;
 hoppet::split_mat Hoppet_P_N3LO;

 hoppet::grid_def Hoppet_grid;
 hoppet::grid_quant_2d Hoppet_xpdf;
 hoppet::grid_quant_2d Hoppet_xpdf_onlyquark;
 hoppet::grid_quant_2d Hoppet_xpdf_onlygluon;
 hoppet::grid_quant Hoppet_xgluon;
 hoppet::grid_quant Hoppet_xquark;

 hoppet::grid_conv xC2Hg0;
 hoppet::grid_conv xCLHg0;
 hoppet::grid_conv xC2Hg;
 hoppet::grid_conv xCLHg;
 hoppet::grid_conv xC2Hq;
 hoppet::grid_conv xCLHq;
 hoppet::grid_conv xC2Hg3;
 hoppet::grid_conv xC2Hq3;

 hoppet::grid_conv xPqg;
 hoppet::grid_conv xA1Hg;
 hoppet::grid_conv xA2HgL0;
 hoppet::grid_conv xA2HgL1;
 hoppet::grid_conv xA2HgL2;
 hoppet::grid_conv xA2HqL0;
 hoppet::grid_conv xA2HqL1;
 hoppet::grid_conv xA2HqL2;
 hoppet::grid_conv xA3HgL0;
 hoppet::grid_conv xA3HgLL;
 hoppet::grid_conv xA3HqL0;
 hoppet::grid_conv xA3HqLL;

 hoppet::grid_conv xA2Hg_vogt;
 hoppet::grid_conv xA2Hg_hpt;
 hoppet::grid_conv xA2Hq_hpt;
 hoppet::grid_conv xA2Hg_CTEQ;
 hoppet::grid_conv xA2Hq_CTEQ;


#endif

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 hoppet::split_mat split_mat_clone(void* ptr){
   auto p = static_cast<split_mat_f*>(ptr);
   if (!p) {
     throw std::runtime_error("input function pointer returned null");
   }
   return hoppet::split_mat(p);
 }
#endif

 bool doCalcN3LODIS = false;
 bool isInitializeHoppetSF = false;
 virtual void InitializeHoppetSF();

 int EvolveOrder = 3;
 int AlphaSOrder = 3;
 virtual void SetEvolveOrder(int order){this->EvolveOrder = order;}
 virtual void SetAlphaSOrder(int order){this->AlphaSOrder = order;}

 virtual void CloneHoppetSF();
 virtual double GetHoppetF2LO(int ihadron, int iparton, double x, double Q);
 virtual double GetHoppetFLLO(int ihadron, int iparton, double x, double Q);
 virtual double GetHoppetF3LO(int ihadron, int iparton, double x, double Q);
 virtual double GetHoppetF2NLO(int ihadron, int iparton, double x, double Q);
 virtual double GetHoppetF2NLO_OnlyQuark(int ihadron, int iparton, double x, double Q);
 virtual double GetHoppetFLNLO(int ihadron, int iparton, double x, double Q);
 virtual double GetHoppetF3NLO(int ihadron, int iparton, double x, double Q);
 virtual double GetHoppetF2NNLO(int ihadron, int iparton, double x, double Q);
 virtual double GetHoppetFLNNLO(int ihadron, int iparton, double x, double Q);
 virtual double GetHoppetF3NNLO(int ihadron, int iparton, double x, double Q);
 virtual double GetHoppetF2N3LO(int ihadron, int iparton, double x, double Q);
 virtual double GetHoppetFLN3LO(int ihadron, int iparton, double x, double Q);
 virtual double GetHoppetF3N3LO(int ihadron, int iparton, double x, double Q);

 virtual void FillHoppetPDFTable(int ihadron, double Q);

 virtual double GetxF2Hg0(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxFLHg0(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxF2Hg(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxFLHg(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxF2Hq(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxFLHq(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxF2Hg3A(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxF2Hg3B(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxF2Hq3A(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxF2Hq3B(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA2HgL0Xg(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA2HgL1Xg(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA2HgL2Xg(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA3HgL0Xg(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA3HgLLXg(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA2HqL0Xq(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA2HqL1Xq(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA2HqL2Xq(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA3HqL0Xq(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA3HqLLXq(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA2HgXg_vogt(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA2HgXg_hpt(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA2HqXq_hpt(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA2HgXg_cteq(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA2HqXq_cteq(int ihadron, double x, double Q, double QMu, double MQ);

 virtual double GetxA2HgXg(int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetxA2HqXq(int ihadron, double x, double Q, double QMu, double MQ);

 virtual double GetxF2ZMNS2(int ihadron, int iparton, double x, double Q, double QMu, double MQ, int nf);
 virtual double GetxFLZMNS2(int ihadron, int iparton, double x, double Q, double QMu, double MQ, int nf);

 virtual double GetSubtraction(int order, int f2fl, int hflv, int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetSubtractionXg(int order1, int order2, int f2fl, int hflv, int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetSubtractionXq(int order1, int order2, int f2fl, int hflv, int ihadron, double x, double Q, double QMu, double MQ);
 virtual double GetSubtractionPDF(int order1, int order2, int f2fl, int hflv, int ihadron, double x, double Q, double QMu, double MQ);

 // VFNSmod
 virtual double VFNSmod_QG(double z, double nf, double as, double LL);
 virtual double VFNSmod_AQG(double z, double nf, double as, double LL);
 virtual double VFNSmod_PS(double z, double nf, double as, double LL);
 virtual double VFNSmod_APS1(double z, double nf, double as, double LL);
 virtual double VFNSmod_APS2(double z, double nf, double as, double LL);

 // OME
 virtual double AnalyticC1A1(double z);
 virtual double A2HgL0(double z);
 virtual double A2HgL1(double z);
 virtual double A2HgL2(double z);
 virtual double A2HqPSL0(double z);
 virtual double A2HqPSL1(double z);
 virtual double A2HqPSL2(double z);

 bool isDefineFunctions_OME = false;
 virtual void DefineFunctions_OME();
 function<double(double, int)> sf_Pqg;
 function<double(double, int)> sf_Pgq;
 function<double(double, int)> sf_Pgg;
 function<double(double, int)> sf_Pqq;
 function<double(double, int)> sf_P1gg;
 function<double(double, int)> sf_P1gq;

 function<double(double, int)> sf_A1Hg;
 function<double(double, int)> sf_a1bhg;
 function<double(double, int)> sf_AnalyticC1A1;
 function<double(double, int)> sf_A2HgL0;
 function<double(double, int)> sf_A2HgL1;
 function<double(double, int)> sf_A2HgL2;
 function<double(double, int)> sf_A2HqPSL0;
 function<double(double, int)> sf_A2HqPSL1;
 function<double(double, int)> sf_A2HqPSL2;
 function<double(double, int)> sf_A3HgLL;
 function<double(double, int)> sf_A3HqPSLL;
 function<double(double, int)> sf_A3HgL0;
 function<double(double, int)> sf_A3HqPSL0;
 function<double(double, int)> sf_A3Hg_ome;
 function<double(double, int)> sf_A3HqPS_ome;

 // SFHQ
 double SFHQ_QQ, SFHQ_Mu, SFHQ_MQ;
 int SFHQ_nfl;
 double SFHQ_asA3;
 double SFHQ_LL;
 virtual void SetQQMuMQ(double Qin, double Muin, double MQin, int nflin, double alfaso2pi);

 bool isDefineFunctions_SFHQ = false;
 virtual void DefineFunctions_SFHQ();
 function<double(double, int)> sf_C2Hg0;
 function<double(double, int)> sf_C2Hg0A;
 function<double(double, int)> sf_CLHg0;
 function<double(double, int)> sf_CLHg0A;
 function<double(double, int)> sf_C2Hg;
 function<double(double, int)> sf_CLHg;
 function<double(double, int)> sf_C2Hq;
 function<double(double, int)> sf_CLHq;
 function<double(double, int)> sf_C2HgL0;
 function<double(double, int)> sf_CLHgL0;
 function<double(double, int)> sf_C2HqL0;
 function<double(double, int)> sf_CLHqL0;
 function<double(double, int)> sf_C2HgL1;
 function<double(double, int)> sf_CLHgL1;
 function<double(double, int)> sf_C2HqL1;
 function<double(double, int)> sf_CLHqL1;
 function<double(double, int)> sf_C2Hg3A;
 function<double(double, int)> sf_C2Hg3B;
 function<double(double, int)> sf_C2Hq3A;
 function<double(double, int)> sf_C2Hq3B;
 function<double(double, int)> sf_C2ZMNS2;
 function<double(double, int)> sf_CLZMNS2;

 // HoppetFunctions
 virtual double A2HGA(double Y);
 virtual double A2HGC(double Y);
 virtual double A2Hg_CTEQ(double z, double eps);
 virtual double A2HqPS_CTEQ(double z, double eps);


 bool isDefineFunctions_HoppetSF = false;
 virtual void DefineFunctions_HoppetSF();
 function<double(double, int)> sf_A2PShg_vogt;
 function<double(double, int)> sf_A2PShg;
 function<double(double, int)> sf_A2PShq;
 function<double(double, int)> sf_A2Hg_CTEQ;
 function<double(double, int)> sf_A2HqPS_CTEQ;
 function<double(double, int)> cf_CqF2MSbar;
 function<double(double, int)> cf_CgF2MSbar;
 function<double(double, int)> cf_CqFL;
 function<double(double, int)> cf_CgFL;
 function<double(double, int)> cf_CqF3minusF2;
 function<double(double, int)> cf_CqF3;

 // WILS3HQ
 virtual double WILS3HQ_REGH2gS(int iorder, double x, double as, double LM, double LQm, double nf, double flav);
 virtual double WILS3HQ_REGH2qPS(int iorder, double x, double as, double LM, double LQm, double nf, double flav);
 virtual double WILS3HQ_SXH2gS(int iorder, double x, double as, double LM, double LQ, double nf, double flav);
 virtual double WILS3HQ_LXH2gS(int iorder, double x, double as, double LM, double LQ, double nf, double flav);
 virtual double WILS3HQ_SXH2qPS(int iorder, double x, double as, double LM, double LQ, double nf, double flav);
 virtual double WILS3HQ_GRH2gS(int iorder, double x, double as, double LM, double LQ, double nf, double flav);
 virtual double WILS3HQ_GRH2qPS(int iorder, double x, double as, double LM, double LQ, double nf, double flav);
 FortranArray1D<double> WILS3HQ_XXV;
 FortranArray3D<double> WILS3HQ_H2gS_Grid;
 FortranArray3D<double> WILS3HQ_H2qPS_Grid;
 bool isInitialWILS3HQGrid = false;
 virtual void InitialWILS3HQGrid();

 // MakeCoeffTable
 void MakeCoeffTable(TString FunctionName);

 // Input
 map<tuple<int, int>, double> CP;
};
#endif
