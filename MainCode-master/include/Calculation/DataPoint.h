#ifndef Calculation_DataPoint_h
#define Calculation_DataPoint_h

#include "RootCommon.h"
#include <Eigen/Dense>

using namespace std;

class DataPoint
{
 public:

 TString DataType;
 TString ColliderType;
 TString CalcMode;
 TString subType;
 int ID;

 TString name;
 double data, theory, StatErr = 0.0, SysErr = 0.0, UnCorrErr = 0.0;
 double theory_lo, theory_nnlo, kfactor_HighOrder = 1.0;
 bool isUseKFactor = false;
 double origindata;
 double variable1 = 0.0, variable2 = 0.0, variable3 = 0.0;
 TString variableTitle = "";
 double x, Q2, y = 0.0, Q;
 int lob;
 Eigen::VectorXd CorrErrs;
 Eigen::VectorXd KFactors;
 int NKFactor;
 vector<int> AppliedKFactorColumns = {};
 double OtherKFactor = 1.0;
 int Jsfn, Jbsn, Jtgt, JBem;

 double BarnFactor = 1.0;
 double Normalization = 1.0;

 // For DIS Data
 int kProc;
 int iLptn1, iLptn2, jPrc, jBn, jHd;
 int iFSflv, jXs;
 int iCmptn, jSf;
 int K_f;

 int iOrdr = 2, iSchm;
 int LdatAdj, LHtg;
 double Q0, ScalFc, achi;

 bool CombinedProcesses;

 vector<double> Param = {0.0, 0.0, 0.0};
 int IorHrd;

 // For Fixed-target Drell-Yan
 int Isfn, Ibsn, IXsc;
 int Ibem, Itgt, Isch, Iscl;
 double tau, Rs, ss, yMx, ptMx, xf;
 double Ptmin, Ptmax, Ymin, Ymax, BR, aMissEtMin;
 double wp_kfac = 1.0, wm_kfac = 1.0;
 double wp_kfac0 = 1.0, wm_kfac0 = 1.0;
 double wp_nlo, wm_nlo, wp_lo, wm_lo;
 double wp_kfac_internal = 1.0, wm_kfac_internal = 1.0;
 double ct_cut;
 map<int, double> Xsec;

 // FastNLO format
 bool isOldFNLOFormat = false;

 // W asymmetry
 bool isAsymmetryData = false;

 // For those pp/pd, W asymmetry (possible) data
 bool noAdditionalKFactor = false;

 // Global
 map<TString, int> DataID;

 map<TString, int> DataJsfn;
 map<TString, int> DataJbsn;
 map<TString, int> DataJtgt;
 map<TString, int> DataJBem;

 DataPoint(){
   Initialize();
 }
 virtual void FindInfo(TString name){
   // DIS
   Jsfn = DataJsfn[name];
   Jbsn = DataJbsn[name];
   Jtgt = DataJtgt[name];
   JBem = DataJBem[name];

   // VBP
   Isfn = DataJsfn[name];
   Ibsn = DataJbsn[name];
   Itgt = DataJtgt[name];
   Ibem = DataJBem[name];

   ID   = DataID[name];
 }

 virtual void Initialize(){
   DataJsfn["HERAIpII"] =   25;  DataJbsn["HERAIpII"] = 235;  DataJtgt["HERAIpII"] =   1;  DataJBem["HERAIpII"] =    0;  DataID["HERAIpII"] =   160; // 160
   DataJsfn["BcdF2pCor"] =   2;  DataJbsn["BcdF2pCor"] =  1;  DataJtgt["BcdF2pCor"] =  1;  DataJBem["BcdF2pCor"] =   0;  DataID["BcdF2pCor"] =  101; // 101
   DataJsfn["BcdF2dCor"] =   2;  DataJbsn["BcdF2dCor"] =  1;  DataJtgt["BcdF2dCor"] =  2;  DataJBem["BcdF2dCor"] =   0;  DataID["BcdF2dCor"] =  102; // 102
   DataJsfn["NmcF2pCor"] =   2;  DataJbsn["NmcF2pCor"] =  1;  DataJtgt["NmcF2pCor"] =  1;  DataJBem["NmcF2pCor"] =   0;  DataID["NmcF2pCor"] =  103;
   DataJsfn["NmcRatCor"] =   2;  DataJbsn["NmcRatCor"] =  1;  DataJtgt["NmcRatCor"] = 12;  DataJBem["NmcRatCor"] =   0;  DataID["NmcRatCor"] =  104; // 104
   DataJsfn["NmcF2rX"] =     2;  DataJbsn["NmcF2rX"] =    1;  DataJtgt["NmcF2rX"] =   12;  DataJBem["NmcF2rX"] =     0;  DataID["NmcF2rX"] =    105;
   DataJsfn["NmcX0pCor"] =  23;  DataJbsn["NmcX0pCor"] =  1;  DataJtgt["NmcX0pCor"] =  1;  DataJBem["NmcX0pCor"] =   2;  DataID["NmcX0pCor"] =  106;
   DataJsfn["BcdX0pCor"] =  26;  DataJbsn["BcdX0pCor"] =  1;  DataJtgt["BcdX0pCor"] =  1;  DataJBem["BcdX0pCor"] =   2;  DataID["BcdX0pCor"] =  115;
   DataJsfn["BcdX0dCor"] =  26;  DataJbsn["BcdX0dCor"] =  1;  DataJtgt["BcdX0dCor"] =  2;  DataJBem["BcdX0dCor"] =   0;  DataID["BcdX0dCor"] =  116;
   DataJsfn["cdhswf2"] =     2;  DataJbsn["cdhswf2"] =    0;  DataJtgt["cdhswf2"] =    5;  DataJBem["cdhswf2"] =     0;  DataID["cdhswf2"] =    108; // 108
   DataJsfn["cdhswf3"] =     3;  DataJbsn["cdhswf3"] =   -1;  DataJtgt["cdhswf3"] =    5;  DataJBem["cdhswf3"] =     0;  DataID["cdhswf3"] =    109; // 109
   DataJsfn["ccfrf2.mi"] =   2;  DataJbsn["ccfrf2.mi"] =  0;  DataJtgt["ccfrf2.mi"] =  5;  DataJBem["ccfrf2.mi"] =   0;  DataID["ccfrf2.mi"] =  110; // 110
   DataJsfn["ccfrf3.md"] =   3;  DataJbsn["ccfrf3.md"] = -1;  DataJtgt["ccfrf3.md"] =  5;  DataJBem["ccfrf3.md"] =   0;  DataID["ccfrf3.md"] =  111; // 111
   DataJsfn["ChorusNuX0"] = 20;  DataJbsn["ChorusNuX0"] = 2;  DataJtgt["ChorusNuX0"] = 5;  DataJBem["ChorusNuX0"] =  1;  DataID["ChorusNuX0"] = 122;
   DataJsfn["ChorusNbX0"] = 20;  DataJbsn["ChorusNbX0"] = 3;  DataJtgt["ChorusNbX0"] = 5;  DataJBem["ChorusNbX0"] = -1;  DataID["ChorusNbX0"] = 123;
   DataJsfn["NuTvNuChXN"] = 30;  DataJbsn["NuTvNuChXN"] = 2;  DataJtgt["NuTvNuChXN"] = 5;  DataJBem["NuTvNuChXN"] =  1;  DataID["NuTvNuChXN"] = 124; // 124
   DataJsfn["NuTvNbChXN"] = 30;  DataJbsn["NuTvNbChXN"] = 3;  DataJtgt["NuTvNbChXN"] = 5;  DataJBem["NuTvNbChXN"] = -1;  DataID["NuTvNbChXN"] = 125; // 125
   DataJsfn["CcfrNuChXN"] = 30;  DataJbsn["CcfrNuChXN"] = 2;  DataJtgt["CcfrNuChXN"] = 5;  DataJBem["CcfrNuChXN"] =  1;  DataID["CcfrNuChXN"] = 126; // 126
   DataJsfn["CcfrNbChXN"] = 30;  DataJbsn["CcfrNbChXN"] = 3;  DataJtgt["CcfrNbChXN"] = 5;  DataJBem["CcfrNbChXN"] =  1;  DataID["CcfrNbChXN"] = 127; // 127
   DataJsfn["Hn+9697f2c"] = 12;  DataJbsn["Hn+9697f2c"] = 1;  DataJtgt["Hn+9697f2c"] = 1;  DataJBem["Hn+9697f2c"] =  0;  DataID["Hn+9697f2c"] = 140;
   DataJsfn["Hn+9900x0c"] = 30;  DataJbsn["Hn+9900x0c"] = 1;  DataJtgt["Hn+9900x0c"] = 1;  DataJBem["Hn+9900x0c"] = -2;  DataID["Hn+9900x0c"] = 143;
   DataJsfn["Hn+9900x0b"] = 30;  DataJbsn["Hn+9900x0b"] = 1;  DataJtgt["Hn+9900x0b"] = 1;  DataJBem["Hn+9900x0b"] = -2;  DataID["Hn+9900x0b"] = 145; // 145
   DataJsfn["Hn0407f2c"] =  12;  DataJbsn["Hn0407f2c"] =  1;  DataJtgt["Hn0407f2c"] =  1;  DataJBem["Hn0407f2c"] =   0;  DataID["Hn0407f2c"] =  146;
   DataJsfn["Hn1X0c"] =     30;  DataJbsn["Hn1X0c"] =     1;  DataJtgt["Hn1X0c"] =     1;  DataJBem["Hn1X0c"] =     -2;  DataID["Hn1X0c"] =     147; // 147
   DataJsfn["Hn1X0ccom"] =  30;  DataJbsn["Hn1X0ccom"] =  1;  DataJtgt["Hn1X0ccom"] =  1;  DataJBem["Hn1X0ccom"] =  -2;  DataID["Hn1X0ccom"] =  148;
   DataJsfn["Hn1X0bcom"] =  30;  DataJbsn["Hn1X0bcom"] =  1;  DataJtgt["Hn1X0bcom"] =  1;  DataJBem["Hn1X0bcom"] =  -2;  DataID["Hn1X0bcom"] =  149;
   DataJsfn["Zn+9697f2c"] = 12;  DataJbsn["Zn+9697f2c"] = 1;  DataJtgt["Zn+9697f2c"] = 1;  DataJBem["Zn+9697f2c"] =  0;  DataID["Zn+9697f2c"] = 156;
   DataJsfn["Zn+9800f2c"] = 12;  DataJbsn["Zn+9800f2c"] = 1;  DataJtgt["Zn+9800f2c"] = 1;  DataJBem["Zn+9800f2c"] =  0;  DataID["Zn+9800f2c"] = 157;
   DataJsfn["HERA1X0"] =    25;  DataJbsn["HERA1X0"] =  235;  DataJtgt["HERA1X0"] =    1;  DataJBem["HERA1X0"] =     0;  DataID["HERA1X0"] =    159;
   DataJsfn["e140Rd"] =      4;  DataJbsn["e140Rd"] =     1;  DataJtgt["e140Rd"] =     2;  DataJBem["e140Rd"] =      0;  DataID["e140Rd"] =     164;
   DataJsfn["e143RC"] =      4;  DataJbsn["e143RC"] =     1;  DataJtgt["e143RC"] =     4;  DataJBem["e143RC"] =      0;  DataID["e143RC"] =     165;
   DataJsfn["H1FL00"] =      0;  DataJbsn["H1FL00"] =     1;  DataJtgt["H1FL00"] =     1;  DataJBem["H1FL00"] =      0;  DataID["H1FL00"] =     166;
   DataJsfn["H1FL03a"] =     0;  DataJbsn["H1FL03a"] =    1;  DataJtgt["H1FL03a"] =    1;  DataJBem["H1FL03a"] =     0;  DataID["H1FL03a"] =    167;
   DataJsfn["H1FL03b"] =     0;  DataJbsn["H1FL03b"] =    1;  DataJtgt["H1FL03b"] =    1;  DataJBem["H1FL03b"] =     0;  DataID["H1FL03b"] =    168;
   DataJsfn["H1FL10"] =      0;  DataJbsn["H1FL10"] =     1;  DataJtgt["H1FL10"] =     1;  DataJBem["H1FL10"] =      0;  DataID["H1FL10"] =     169; // 169
   DataJsfn["EMCF2c"] =     12;  DataJbsn["EMCF2c"] =     1;  DataJtgt["EMCF2c"] =     5;  DataJBem["EMCF2c"] =      0;  DataID["EMCF2c"] =     170;
   DataJsfn["EMCX0c"] =     30;  DataJbsn["EMCX0c"] =     1;  DataJtgt["EMCX0c"] =     5;  DataJBem["EMCX0c"] =      0;  DataID["EMCX0c"] =     171;
   DataJsfn["e605"] =        2;  DataJbsn["e605"] =       1;  DataJtgt["e605"] =       3;  DataJBem["e605"] =        1;  DataID["e605"] =       201; // 201
   DataJsfn["e866f"] =       4;  DataJbsn["e866f"] =      1;  DataJtgt["e866f"] =      1;  DataJBem["e866f"] =       1;  DataID["e866f"] =      203; // 203
   DataJsfn["e866f_up2025"] =4;  DataJbsn["e866f_up2025"] = 1;  DataJtgt["e866f_up2025"] = 1;  DataJBem["e866f_up2025"] = 1;  DataID["e866f_up2025"] = 203; // 203
   DataJsfn["e866ppxf"] =    1;  DataJbsn["e866ppxf"] =   1;  DataJtgt["e866ppxf"] =   1;  DataJBem["e866ppxf"] =    1;  DataID["e866ppxf"] =   204; // 204
   DataJsfn["e906aF"] =      4;  DataJbsn["e906aF"] =     1;  DataJtgt["e906aF"] =     1;  DataJBem["e906aF"] =      1;  DataID["e906aF"] =     206; // 206
   DataJsfn["e906aF_up2025"] = 4;  DataJbsn["e906aF_up2025"] = 1;  DataJtgt["e906aF_up2025"] = 1;  DataJBem["e906aF_up2025"] = 1;  DataID["e906aF_up2025"] = 206; // 206
   DataJsfn["cdfLasy"] =    -3;  DataJbsn["cdfLasy"] =    3;  DataJtgt["cdfLasy"] =    1;  DataJBem["cdfLasy"] =    -1;  DataID["cdfLasy"] =    225; // 225
   DataJsfn["cdfLasy2"] =   -3;  DataJbsn["cdfLasy2"] =   3;  DataJtgt["cdfLasy2"] =   1;  DataJBem["cdfLasy2"] =   -1;  DataID["cdfLasy2"] =   227; // 227
   DataJsfn["d02Masy1"] =   -3;  DataJbsn["d02Masy1"] =   3;  DataJtgt["d02Masy1"] =   1;  DataJBem["d02Masy1"] =   -1;  DataID["d02Masy1"] =   234; // 234
   DataJsfn["ZyD02a"] =     -6;  DataJbsn["ZyD02a"] =     4;  DataJtgt["ZyD02a"] =     1;  DataJBem["ZyD02a"] =     -1;  DataID["ZyD02a"] =     260; // 260
   DataJsfn["ZyCDF2"] =     -6;  DataJbsn["ZyCDF2"] =     4;  DataJtgt["ZyCDF2"] =     1;  DataJBem["ZyCDF2"] =     -1;  DataID["ZyCDF2"] =     261; // 261
   DataJsfn["CMS7Masy2"] =  -9;  DataJbsn["CMS7Masy2"] = 23;  DataJtgt["CMS7Masy2"] =  1;  DataJBem["CMS7Masy2"] =   1;  DataID["CMS7Masy2"] =  266; // 266
   DataJsfn["CMS7Easy"] =   -3;  DataJbsn["CMS7Easy"] =   3;  DataJtgt["CMS7Easy"] =   1;  DataJBem["CMS7Easy"] =    1;  DataID["CMS7Easy"] =   267; // 267
   DataJsfn["ATL7_WZ"] =    -9;  DataJbsn["ATL7_WZ"] =  234;  DataJtgt["ATL7_WZ"] =    1;  DataJBem["ATL7_WZ"] =     1;  DataID["ATL7_WZ"] =    268; // 268
   DataJsfn["d02Easy5"] =   -9;  DataJbsn["d02Easy5"] =   3;  DataJtgt["d02Easy5"] =   1;  DataJBem["d02Easy5"] =   -1;  DataID["d02Easy5"] =   281; // 281
   DataJsfn["cdf2jtCor2"] =  6;  DataJbsn["cdf2jtCor2"] = 0;  DataJtgt["cdf2jtCor2"] = 1;  DataJBem["cdf2jtCor2"] = -1;  DataID["cdf2jtCor2"] = 504; // 504
   DataJsfn["d02jtCor2"] =   6;  DataJbsn["d02jtCor2"] =  0;  DataJtgt["d02jtCor2"] =  1;  DataJBem["d02jtCor2"] =  -1;  DataID["d02jtCor2"] =  514; // 514
   DataJsfn["CommonF2"] =    2;  DataJbsn["CommonF2"] =   1;  DataJtgt["CommonF2"] =   1;  DataJBem["CommonF2"] =    0;  DataID["CommonF2"] =   191; // 191
   DataJsfn["CommonFL"] =    2;  DataJbsn["CommonFL"] =   1;  DataJtgt["CommonFL"] =   1;  DataJBem["CommonFL"] =    0;  DataID["CommonFL"] =   192; // 192
 }

};
#endif
