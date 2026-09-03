#ifndef CTEQHelper_pdsReader_h
#define CTEQHelper_pdsReader_h

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cmath>
#include <cstring>

#ifdef USE_LHAPDF
#include "LHAPDF/LHAPDF.h"
#include "LHAPDF/Reweighting.h"
#endif

class pdsReader
{
 public:

 std::ifstream pdf;

 std::string FileLine;

 int isetch = 0;
 int ipdsset = 0;
 int ipdsformat = 0;

 int ipk = 22;
 double Dr = 3.0, Iorder = 3.0;
 double Qalfa = 91.1870;
 double AlfaQ = 0.1180;
 double Alambda = 0.0;
 std::map<int, double> amass;

 int IPD0 = 1;
 int IHDN = 1;
 int IKNL = 3;
 int JT = 1;
 int NTL = 0;

 int aimass = 0;
 double fswitch = 0.0;
 int N0 = 0;
 int Nfmx = 0, Nfl = 0, fl = 0;
 int MxVal = 0;

 int NX = 0, NT = 0, NG = 0;

 double QINI = 1.29, QMAX = 100000.0;
 std::vector<double> qv;
 std::vector<double> TV;
 std::vector<double> AlsCTEQ;

 double qbase = 0.1, qbase1 = 0.1, qbase2 = 0.1;

 double XMIN = 1e-9, aa = 2.0;
 std::vector<double> XV;

 int Nblk = 0;
 int Npts = 0;

 std::vector<double> UPD;

 int MXX = 310, MXQ = 40, MXF = 6, MaxVal = 5;
 int MXPQX = 0;

 double OneP = 1.00001;
 double xpow = 1.0 / 3.0;
 int nqvec = 4;
 int ientry = 0;
 double X = -1.0, Q = -1.0;
 int JX = 0, JQ = 0;

 std::vector<double> fvec;
 std::vector<double> fij;
 std::vector<double> xvpow;
 int JLX = 0, JLQ = 0;
 double ss = 0.0, const1 = 0.0, const2 = 0.0, const3 = 0.0, const4 = 0.0, const5 = 0.0, const6 = 0.0;
 double sy2 = 0.0, sy3 = 0.0, s23 = 0.0;
 double tt = 0.0;
 double t12 = 0.0, t13 = 0.0, t23 = 0.0, t24 = 0.0, t34 = 0.0, ty2 = 0.0, ty3 = 0.0;
 double tmp1 = 0.0, tmp2 = 0.0, tdet = 0.0;

 int JU = 0, JM = 0;

 double muF = 1.0;

 pdsReader();
 virtual void Initialize(const char* name);
 virtual void Initialize(int Nfmx, int MxVal, int NX, int NT, std::vector<double> XV, std::vector<double> qv, std::vector<double> TV, std::vector<double> AlsCTEQ, std::vector<double> UPD);
 virtual void OutputPDF(const char* name);
 virtual void CopyHeader(pdsReader* pdf);
 virtual void InputAlphaS(std::vector<double> AlsCTEQ);
 virtual void InputUPD(std::vector<double> UPD);
 virtual void FromLHAtoUPD(const char* PDFName, int PDFset);
 virtual void l2pFullSet(const char* PDFName, int nSet);
 virtual double CT14PDF(int iparton, double x, double Q);
 virtual double PartonX12(int iparton, double xx, double QQ);
 virtual double CT14Alphas(double QQ);
 virtual void Polint4F(std::vector<double> XA, std::vector<double> YA, double X, double& Y);
 virtual double xfxQ(int flavor, double x, double Q);
 virtual double Getf(int flavor, double x, double Q);

 virtual bool CheckGridConsistency(pdsReader* pdf);
 virtual pdsReader* Average(std::vector<pdsReader *> PDFs);

 std::vector<double> Input_x;
 std::vector<double> Input_Q;
 virtual void InputxQVector(std::vector<double> x_vec, std::vector<double> Q_vec){Input_x = x_vec; Input_Q = Q_vec;};
};

#endif
