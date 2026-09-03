#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include "PDFHelper/PDFHelper.h"
#include "CTEQHelper/HoppetInterface.h"
#include "CTEQHelper/PDFEvolve.h"
#include "Calculation/ApplGridHelper.h"
#include "Calculation/FastNLOHelper.h"
#include "Calculation/Dataset.h"
#include "Calculation/DataPoint.h"
#include "Calculation/Config.h"
#include "Calculation/QCDSet.h"
#include "Calculation/ThreadChi2.h"
#include "Calculation/PDFChi2.h"
#include "TMinuitHelper/TMinuitHelper.h"

using namespace std;

int main(int argc, char** argv)
{
 vector<TString> FlavorList = {"dv", "uv", "gluon", "dmu", "dpu", "str"};
 vector<int> FlagList = {981, 981, 848, 219, 218, 220};

 PDFEvolve* pdf = new PDFEvolve();

 pdf->SetParameter("dv",    vector<double>{ 0.76317,  3.03609, 2.61407,  1.82746,  2.72032,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetParameter("uv",    vector<double>{ 0.76317,  3.03609, 1.50192, -0.14666,  1.67108,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetParameter("gluon", vector<double>{ 0.53101,  3.14810, 3.03140, -1.70494,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetParameter("dmu",   vector<double>{-0.02194,  7.73657, 4.00000,  0.29223,  0.64695,  0.47492,  0.74137,  0.61791,  0.19493,  0.87087,  0.26669,  0.73317});
 pdf->SetParameter("dpu",   vector<double>{-0.02194,  7.73657, 4.00000,  0.29223,  0.64695,  0.47492,  0.74137,  0.61791,  0.19493,  0.87087,  0.26669,  0.73317});
 pdf->SetParameter("str",   vector<double>{-0.02194, 10.30986, 4.00000,  0.46599,  0.46599,  0.22525,  0.22525,  1.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetInitialgluonMomentum(0.3846129);
 pdf->SetInitialStrangeB0(0.5146522);


/* pdf->SetParameter("dv",     vector<double>{  0.76997,  3.05403,  2.71782,  2.03820,  2.88216,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetParameter("uv",     vector<double>{  0.76997,  3.05403,  1.49299, -0.11015,  1.69426,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetParameter("gluon",  vector<double>{  0.51867,  2.80394,  3.29970, -1.86091,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetParameter("dmu",    vector<double>{ -0.03027,  7.65300,  4.00000,  0.30536,  0.67864,  0.51644,  0.81901,  0.69248,  0.22200,  0.87672,  0.32786,  0.74724});
 pdf->SetParameter("dpu",    vector<double>{ -0.03027,  7.65300,  4.00000,  0.30536,  0.67864,  0.51644,  0.81901,  0.69248,  0.22200,  0.87672,  0.32786,  0.74724});
 pdf->SetParameter("str",    vector<double>{ -0.03027, 10.27454,  4.00000,  0.46486,  0.46486,  0.29253,  0.29253,  1.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetInitialgluonMomentum(0.38301);
 pdf->SetInitialStrangeB0(0.51728);
*/
 pdf->ParameterOutput();

 pdf->Initialize(1, FlavorList, FlagList);

 HoppetInterface* hoppet = new HoppetInterface();
 hoppet->SetAlphaSQ0(0.118, 91.19);
 hoppet->Initialize(pdf, 1.29);
 hoppet->Evolution(0.01, 100.0);
 hoppet->Evolution(0.00806, 17.3205);



 hoppet->InitializeAPFEL(pdf, 1.29);

 vector<double> pdf_q(13);
 cout<<"APFEL"<<endl;
 hoppet->EvolveAPFEL(0.01, 100.0, &pdf_q[0]);
 cout<<"Hoppet"<<endl;
 hoppet->Evolve(0.01, 100.0, &pdf_q[0]);
 for(int i = -5; i <= 5; i++){
   cout<<"x = "<<0.01<<" Q = "<<100.0<<" flavor = "<<i<<" pdf = "<<pdf_q[i + 6]<<endl;
 }
 cout<<"APFEL"<<endl;
 hoppet->EvolveAPFEL(0.00806, 17.3205, &pdf_q[0]);
 cout<<"Hoppet"<<endl;
 hoppet->Evolve(0.00806, 17.3205, &pdf_q[0]);
 for(int i = -5; i <= 5; i++){
   cout<<"x = "<<0.00806<<" Q = "<<17.3205<<" flavor = "<<i<<" pdf = "<<pdf_q[i + 6]<<endl;
 }
 cout<<"APFEL"<<endl;
 hoppet->EvolveAPFEL(0.5, 100.0, &pdf_q[0]);
 cout<<"Hoppet"<<endl;
 hoppet->Evolve(0.5, 100.0, &pdf_q[0]);
 for(int i = -5; i <= 5; i++){
   cout<<"x = "<<0.5<<" Q = "<<100.0<<" flavor = "<<i<<" pdf = "<<pdf_q[i + 6]<<endl;
 }


 cout<<"Q = 10.0 "<<hoppet->EvolveAlphaS(10.0)<<"  "<<hoppet->EvolveAlphaSAPFEL(10.0)<<endl;
 cout<<"Q = 90.0 "<<hoppet->EvolveAlphaS(90.0)<<"  "<<hoppet->EvolveAlphaSAPFEL(90.0)<<endl;
 cout<<"Q = 130.0 "<<hoppet->EvolveAlphaS(130.0)<<"  "<<hoppet->EvolveAlphaSAPFEL(130.0)<<endl;
 cout<<"Q = 200.0 "<<hoppet->EvolveAlphaS(200.0)<<"  "<<hoppet->EvolveAlphaSAPFEL(200.0)<<endl;



 PDFHelper* lha = new PDFHelper();
 lha->InitialPDF("CT18NNLO", 0);
 cout<<"Q = 100.0 u     LHAPDF: "<<lha->Getf(2, 0.01, 100.0)<<" Mine: "<<pdf->Getu(0.01, 100.0)<<endl;
 cout<<"Q = 100.0 d     LHAPDF: "<<lha->Getf(1, 0.01, 100.0)<<" Mine: "<<pdf->Getd(0.01, 100.0)<<endl;
 cout<<"Q = 100.0 ubar  LHAPDF: "<<lha->Getf(-2, 0.01, 100.0)<<" Mine: "<<pdf->Getubar(0.01, 100.0)<<endl;
 cout<<"Q = 100.0 dbar  LHAPDF: "<<lha->Getf(-1, 0.01, 100.0)<<" Mine: "<<pdf->Getdbar(0.01, 100.0)<<endl;
 cout<<"Q = 100.0 gluon LHAPDF: "<<lha->Getf(0, 0.01, 100.0)<<" Mine: "<<pdf->Getgluon(0.01, 100.0)<<" LHAPDF(21): "<<lha->Getf(21, 0.01, 100.0)<<endl;
 cout<<"Q = 100.0 s     LHAPDF: "<<lha->Getf(3, 0.01, 100.0)<<" Mine: "<<pdf->Gets(0.01, 100.0)<<endl;
 cout<<"Q = 100.0 sbar  LHAPDF: "<<lha->Getf(-3, 0.01, 100.0)<<" Mine: "<<pdf->Getsbar(0.01, 100.0)<<endl;

 cout<<endl;
 cout<<"Q = 1.295 u     LHAPDF: "<<lha->Getf(2, 0.01, 1.295)<<" Mine: "<<pdf->GetPDFQ0(0.01, 1)<<endl;
 cout<<"Q = 1.295 d     LHAPDF: "<<lha->Getf(1, 0.01, 1.295)<<" Mine: "<<pdf->GetPDFQ0(0.01, 2)<<endl;
 cout<<"Q = 1.295 ubar  LHAPDF: "<<lha->Getf(-2, 0.01, 1.295)<<" Mine: "<<pdf->GetPDFQ0(0.01, -1)<<endl;
 cout<<"Q = 1.295 dbar  LHAPDF: "<<lha->Getf(-1, 0.01, 1.295)<<" Mine: "<<pdf->GetPDFQ0(0.01, -2)<<endl;
 cout<<"Q = 1.295 s     LHAPDF: "<<lha->Getf(3, 0.01, 1.295)<<" Mine: "<<pdf->GetPDFQ0(0.01, 3)<<endl;
 cout<<"Q = 1.295 sbar  LHAPDF: "<<lha->Getf(-3, 0.01, 1.295)<<" Mine: "<<pdf->GetPDFQ0(0.01, -3)<<endl;
 cout<<"Q = 1.295 gluon LHAPDF: "<<lha->Getf(0, 0.01, 1.295)<<" Mine: "<<pdf->GetPDFQ0(0.01, 0)<<" LHAPDF(21): "<<lha->Getf(21, 0.01, 1.295)<<endl;

 cout<<endl;
 cout<<"x = "<<6.14421e-06<<endl;
 cout<<"Q = 1.295 u     LHAPDF: "<<lha->Getf(2,  6.14421e-06, 1.295)<<" Mine: "<<pdf->GetPDFQ0(6.14421e-06, 1)<<endl;
 cout<<"Q = 1.295 d     LHAPDF: "<<lha->Getf(1,  6.14421e-06, 1.295)<<" Mine: "<<pdf->GetPDFQ0(6.14421e-06, 2)<<endl;
 cout<<"Q = 1.295 ubar  LHAPDF: "<<lha->Getf(-2, 6.14421e-06, 1.295)<<" Mine: "<<pdf->GetPDFQ0(6.14421e-06, -1)<<endl;
 cout<<"Q = 1.295 dbar  LHAPDF: "<<lha->Getf(-1, 6.14421e-06, 1.295)<<" Mine: "<<pdf->GetPDFQ0(6.14421e-06, -2)<<endl;
 cout<<"Q = 1.295 s     LHAPDF: "<<lha->Getf(3,  6.14421e-06, 1.295)<<" Mine: "<<pdf->GetPDFQ0(6.14421e-06, 3)<<endl;
 cout<<"Q = 1.295 sbar  LHAPDF: "<<lha->Getf(-3, 6.14421e-06, 1.295)<<" Mine: "<<pdf->GetPDFQ0(6.14421e-06, -3)<<endl;
 cout<<"Q = 1.295 gluon LHAPDF: "<<lha->Getf(0,  6.14421e-06, 1.295)<<" Mine: "<<pdf->GetPDFQ0(6.14421e-06, 0)<<" LHAPDF(21): "<<lha->Getf(21, 6.14421e-06, 1.295)<<endl;


 cout<<"Q = 17.3205 x = 0.00806 LHAPDF: "<<lha->Getf(-3, 0.00806, 17.3205)<<" Mine: "<<pdf->Getsbar(0.00806, 17.3205)<<endl;

 hoppet->SetQArray();
 hoppet->SetXArray();

 pdsReader* mypdf = hoppet->PrepareCTEQTable();
 mypdf->OutputPDF("mypdf.pds");
 hoppet->OutputLHAPDFTable("mypdf", 0);

// ApplGridHelper* grid = new ApplGridHelper();
// grid->InitialPDFbyHand(hoppet);
// grid->DefaultConvolute("/ustcfs2/yfu/MainCode/run/TryDIS/../../../FittingCode/ApplGridtables/grid-40-6-15-3-Z_y_0.0_1.0.root");

 Config setting;
 setting.ConfigPDF(mypdf);
 //setting.ConfigPDF("CT18NNLO", 0);
 setting.ConfigOrder(22, 3, 0, 0, 3, 3, 5);
 setting.ConfigDis(
  {99, 1, 230},
  {1.0, 0.0, 0.0}
 );
 setting.ConfigVbp(
  {99, 0, 0},
  {0.0, 0.0, 0.0}
 );

 map<tuple<int, int>, double> CPpara = {
   {make_tuple(1, 1), 0.01000}, {make_tuple(2, 1), 0.3}, {make_tuple(3, 1), 0.3}, {make_tuple(4, 1), 0.8}, {make_tuple(5, 1), 1.0}, {make_tuple(6, 1), 0.0},  {make_tuple(7, 1), 0.0},
   {make_tuple(1, 2), 0.00000}, {make_tuple(2, 2), 0.0}, {make_tuple(3, 2), 0.0}, {make_tuple(4, 2), 0.0}, {make_tuple(5, 2), 0.0}, {make_tuple(6, 2), 0.0},  {make_tuple(7, 2), 0.0},
   {make_tuple(1, 3), 0.00000}, {make_tuple(2, 3), 0.0}, {make_tuple(3, 3), 0.0}, {make_tuple(4, 3), 0.0}, {make_tuple(5, 3), 1.0}, {make_tuple(6, 3), 16.0}, {make_tuple(7, 3), 0.9},
   {make_tuple(1, 4), 0.00000}, {make_tuple(2, 4), 0.0}, {make_tuple(3, 4), 0.0}, {make_tuple(4, 4), 0.0}, {make_tuple(5, 4), 0.0}, {make_tuple(6, 4), 0.0},  {make_tuple(7, 4), 0.0},
   {make_tuple(1, 5), 0.00000}, {make_tuple(2, 5), 0.0}, {make_tuple(3, 5), 0.0}, {make_tuple(4, 5), 0.0}, {make_tuple(5, 5), 0.0}, {make_tuple(6, 5), 0.0},  {make_tuple(7, 5), 0.0}
 };

 setting.InputCP(CPpara);

/* vector<Dataset *> AllData(39);

 AllData.at(0) = new Dataset("LHCb7ZWrap");
 AllData.at(0)->SetCut(setting);
 AllData.at(0)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/LHCb7ZWrap", "DrellYan", "ApplGrid", "LHC", "LHCb7ZWrap");
 AllData.at(0)->InputGridName(vector<TString>{"/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/245_1.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/245_2.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/245_3.root"});
 AllData.at(0)->InputApplGridRange(1, 1, 17);
 AllData.at(0)->InputKFactorColumns(vector<int>{5, 8});

 AllData.at(1) = new Dataset("LHCb8Zeer");
 AllData.at(1)->SetCut(setting);
 AllData.at(1)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/LHCb8Zeer", "DrellYan", "ApplGrid", "LHC", "LHCb8Zeer");
 AllData.at(1)->InputGridName(vector<TString>{"/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/246_1_KP_2018.1010.root"});
 AllData.at(1)->InputApplGridRange(1, 1, 17);
 AllData.at(1)->InputKFactorColumns(vector<int>{6, 8});

 AllData.at(2) = new Dataset("CMS8Wxa");
 AllData.at(2)->SetCut(setting);
 AllData.at(2)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS8Wxa", "DrellYan", "ApplGrid", "LHC", "CMS8Wxa");
 AllData.at(2)->InputGridName(vector<TString>{"/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/249_Wplus_applgrid_Pt25_xfitter_2018.0618.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/249_Wminus_applgrid_Pt25_xfitter_2018.0618.root"});
 AllData.at(2)->InputKFactorColumns(vector<int>{9});

 AllData.at(3) = new Dataset("LHCb8WZ");
 AllData.at(3)->SetCut(setting);
 AllData.at(3)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/LHCb8WZ", "DrellYan", "ApplGrid", "LHC", "LHCb8WZ");
 AllData.at(3)->InputGridName(vector<TString>{"/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/250_1.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/250_2.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/250_3.root"});
 AllData.at(3)->InputKFactorColumns(vector<int>{5, 10});

 AllData.at(4) = new Dataset("ATL8ZpT");
 AllData.at(4)->SetCut(setting);
 AllData.at(4)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ATL8ZpT", "DrellYan", "ApplGrid", "LHC", "ATL8ZpT");
 AllData.at(4)->InputGridName(vector<TString>{"/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/253_4.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/253_5.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/253_6.root"});
 AllData.at(4)->InputSystematicMethod(map<tuple<int, int>, int>{{make_tuple(0, 0), 0}, {make_tuple(1, 100), 1}});
 AllData.at(4)->InputKFactorColumns(vector<int>{6});

 AllData.at(5) = new Dataset("ATL7jtR6u");
 AllData.at(5)->SetCut(setting);
 AllData.at(5)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ATL7jtR6u", "Jet", "ApplGrid", "LHC", "ATL7jtR6u");
 AllData.at(5)->InputGridName(vector<TString>{"/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/510_1.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/510_2.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/510_3.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/510_4.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/510_5.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/510_6.root"});
 AllData.at(5)->InputSystematicMethod(map<tuple<int, int>, int>{{make_tuple(0, 0), 0}, {make_tuple(1, 73), 1}});
 AllData.at(5)->InputKFactorColumns(vector<int>{5});

 AllData.at(6) = new Dataset("CMS7jtR7y6");
 AllData.at(6)->SetCut(setting);
 AllData.at(6)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS7jtR7y6", "Jet", "FastNLO", "LHC", "CMS7jtR7y6");
 AllData.at(6)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/fnl2332e_v23_fix_I1298810.tab"});
 AllData.at(6)->InputSystematicMethod(map<tuple<int, int>, int>{{make_tuple(0, 0), 0}, {make_tuple(1, 24), 1}});
 AllData.at(6)->InputKFactorColumns(vector<int>{6});

 AllData.at(7) = new Dataset("CMS8jtR7");
 AllData.at(7)->SetCut(setting);
 AllData.at(7)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS8jtR7", "Jet", "FastNLO", "LHC", "CMS8jtR7");
 AllData.at(7)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/fnl3332_I1487277.tab"});
 AllData.at(7)->InputSystematicMethod(map<tuple<int, int>, int>{{make_tuple(0, 0), 0}, {make_tuple(1, 27), 1}});
 AllData.at(7)->InputKFactorColumns(vector<int>{3});

 AllData.at(8) = new Dataset("CMS8pTtyt");
 AllData.at(8)->SetCut(setting);
 AllData.at(8)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS8pTtyt", "Jet", "FastNLO", "LHC", "CMS8pTtyt");
 AllData.at(8)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-173.3-PTavt_Yavt-0.00-0.35-nnlo.tab", "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-173.3-PTavt_Yavt-0.35-0.85-nnlo.tab", "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-173.3-PTavt_Yavt-0.85-1.45-nnlo.tab", "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-173.3-PTavt_Yavt-1.45-2.50-nnlo.tab"});

 AllData.at(9) = new Dataset("ATL8ttcoma");
 AllData.at(9)->SetCut(setting);
 AllData.at(9)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ATL8ttcoma", "Jet", "FastNLO", "LHC", "ATL8ttcoma");
 AllData.at(9)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-PTavt-MT2-173_3-bin1.tab", "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-Mtt-HT4-173_3-bin1.tab"});

 AllData.at(10) = new Dataset("cdf2jtCor2");
 AllData.at(10)->SetCut(setting);
 AllData.at(10)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdf2jtCor2", "Jet", "FastNLO", "Tev", "cdf2jtCor2");
 AllData.at(10)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/fnt2007midp.tab"});

 AllData.at(11) = new Dataset("d02jtCor2");
 AllData.at(11)->SetCut(setting);
 AllData.at(11)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/d02jtCor2", "Jet", "FastNLO", "Tev", "d02jtCor2");
 AllData.at(11)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/fnt2009midp.tab"});

 AllData.at(12) = new Dataset("HERAIpII");
 AllData.at(12)->SetCut(setting);
 AllData.at(12)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/HERAIpII", "DIS", "CTEQ", "", "HERAIpII");

 AllData.at(13) = new Dataset("BcdF2pCor");
 AllData.at(13)->SetCut(setting);
 AllData.at(13)->InputNormalization(0.9676, 0.1, 1.0);
 AllData.at(13)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/BcdF2pCor", "DIS", "CTEQ", "", "BcdF2pCor");

 AllData.at(14) = new Dataset("BcdF2dCor");
 AllData.at(14)->SetCut(setting);
 AllData.at(14)->InputNormalization(0.9676, 1.0, 0.0);
 AllData.at(14)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/BcdF2dCor", "DIS", "CTEQ", "", "BcdF2dCor");

 AllData.at(15) = new Dataset("NmcRatCor");
 AllData.at(15)->SetCut(setting);
 AllData.at(15)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/NmcRatCor", "DIS", "CTEQ", "", "NmcRatCor");

 AllData.at(16) = new Dataset("cdhswf2");
 AllData.at(16)->SetCut(setting);
 AllData.at(16)->InputNormalization(1.0137, 0.1, 1.0);
 AllData.at(16)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdhswf2", "DIS", "CTEQ", "", "cdhswf2");

 AllData.at(17) = new Dataset("cdhswf3");
 AllData.at(17)->SetCut(setting);
 AllData.at(17)->InputNormalization(1.0137, 1.0, 0.0);
 AllData.at(17)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdhswf3", "DIS", "CTEQ", "", "cdhswf3");

 AllData.at(18) = new Dataset("ccfrf2.mi");
 AllData.at(18)->SetCut(setting);
 AllData.at(18)->InputNormalization(1.0290, 0.1, 1.0);
 AllData.at(18)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ccfrf2.mi", "DIS", "CTEQ", "", "ccfrf2.mi");

 AllData.at(19) = new Dataset("ccfrf3.md");
 AllData.at(19)->SetCut(setting);
 AllData.at(19)->InputNormalization(1.0290, 1.0, 0.0);
 AllData.at(19)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ccfrf3.md", "DIS", "CTEQ", "", "ccfrf3.md");

 AllData.at(20) = new Dataset("NuTvNuChXN");
 AllData.at(20)->SetCut(setting);
 AllData.at(20)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/NuTvNuChXN", "DIS", "CTEQ", "", "NuTvNuChXN");

 AllData.at(21) = new Dataset("NuTvNbChXN");
 AllData.at(21)->SetCut(setting);
 AllData.at(21)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/NuTvNbChXN", "DIS", "CTEQ", "", "NuTvNbChXN");

 AllData.at(22) = new Dataset("CcfrNuChXN");
 AllData.at(22)->SetCut(setting);
 AllData.at(22)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CcfrNuChXN", "DIS", "CTEQ", "", "CcfrNuChXN");

 AllData.at(23) = new Dataset("CcfrNbChXN");
 AllData.at(23)->SetCut(setting);
 AllData.at(23)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CcfrNbChXN", "DIS", "CTEQ", "", "CcfrNbChXN");

 AllData.at(24) = new Dataset("Hn+9900x0b");
 AllData.at(24)->SetCut(setting);
 AllData.at(24)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/Hn+9900x0b", "DIS", "CTEQ", "", "Hn+9900x0b");

 AllData.at(25) = new Dataset("Hn1X0c");
 AllData.at(25)->SetCut(setting);
 AllData.at(25)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/Hn1X0c", "DIS", "CTEQ", "", "Hn1X0c");

 AllData.at(26) = new Dataset("H1FL10");
 AllData.at(26)->SetCut(setting);
 AllData.at(26)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/H1FL10", "DIS", "CTEQ", "", "H1FL10");

 AllData.at(27) = new Dataset("e605");
 AllData.at(27)->SetCut(setting);
 AllData.at(27)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/e605", "DrellYan", "CTEQ_DY", "", "e605");
 AllData.at(27)->InputKFactorColumns(vector<int>{2});

 AllData.at(28) = new Dataset("e866f");
 AllData.at(28)->SetCut(setting);
 AllData.at(28)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/e866f", "DrellYan", "CTEQ_DY", "", "e866f");
 AllData.at(28)->InputKFactorColumns(vector<int>{2});

 AllData.at(29) = new Dataset("e866ppxf");
 AllData.at(29)->SetCut(setting);
 AllData.at(29)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/e866ppxf", "DrellYan", "CTEQ_DY", "", "e866ppxf");
 AllData.at(29)->InputKFactorColumns(vector<int>{2});

 AllData.at(30) = new Dataset("cdfLasy");
 AllData.at(30)->SetCut(setting);
 AllData.at(30)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdfLasy", "DrellYan", "CTEQ_DY", "", "cdfLasy");

 AllData.at(31) = new Dataset("cdfLasy2");
 AllData.at(31)->SetCut(setting);
 AllData.at(31)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdfLasy2", "DrellYan", "CTEQ_DY", "", "cdfLasy2");

 AllData.at(32) = new Dataset("d02Masy1");
 AllData.at(32)->SetCut(setting);
 AllData.at(32)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/d02Masy1", "DrellYan", "CTEQ_DY", "", "d02Masy1");

 AllData.at(33) = new Dataset("ZyD02a");
 AllData.at(33)->SetCut(setting);
 AllData.at(33)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ZyD02a", "DrellYan", "CTEQ_DY", "", "ZyD02a");
 AllData.at(33)->InputKFactorColumns(vector<int>{2});

 AllData.at(34) = new Dataset("ZyCDF2");
 AllData.at(34)->SetCut(setting);
 AllData.at(34)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ZyCDF2", "DrellYan", "CTEQ_DY", "", "ZyCDF2");
 AllData.at(34)->InputKFactorColumns(vector<int>{2});

 AllData.at(35) = new Dataset("CMS7Masy2");
 AllData.at(35)->SetCut(setting);
 AllData.at(35)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS7Masy2", "DrellYan", "CTEQ_DY", "", "CMS7Masy2");

 AllData.at(36) = new Dataset("CMS7Easy");
 AllData.at(36)->SetCut(setting);
 AllData.at(36)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS7Easy", "DrellYan", "CTEQ_DY", "", "CMS7Easy");

 AllData.at(37) = new Dataset("ATL7_WZ");
 AllData.at(37)->SetCut(setting);
 AllData.at(37)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ATL7_WZ", "DrellYan", "CTEQ_DY", "", "ATL7_WZ");
 AllData.at(37)->InputKFactorColumns(vector<int>{3});

 AllData.at(38) = new Dataset("d02Easy5");
 AllData.at(38)->SetCut(setting);
 AllData.at(38)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/d02Easy5", "DrellYan", "CTEQ_DY", "", "d02Easy5");
*/

/*
 vector<Dataset *> AllData(1);

 AllData.at(0) = new Dataset("HERAIpII");
 AllData.at(0)->SetCut(setting);
 AllData.at(0)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/HERAIpII", "DIS", "CTEQ", "", "HERAIpII");
*/

/*
 vector<Dataset *> AllData(4);

 AllData.at(0) = new Dataset("CMS7jtR7y6");
 AllData.at(0)->SetCut(setting);
 AllData.at(0)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS7jtR7y6", "Jet", "FastNLO", "LHC", "CMS7jtR7y6");
 AllData.at(0)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/fnl2332e_v23_fix_I1298810.tab"});
 AllData.at(0)->InputSystematicMethod(map<tuple<int, int>, int>{{make_tuple(0, 0), 0}, {make_tuple(1, 24), 1}});
 AllData.at(0)->InputKFactorColumns(vector<int>{6});

 AllData.at(1) = new Dataset("CMS8jtR7");
 AllData.at(1)->SetCut(setting);
 AllData.at(1)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS8jtR7", "Jet", "FastNLO", "LHC", "CMS8jtR7");
 AllData.at(1)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/fnl3332_I1487277.tab"});
 AllData.at(1)->InputSystematicMethod(map<tuple<int, int>, int>{{make_tuple(0, 0), 0}, {make_tuple(1, 27), 1}});
 AllData.at(1)->InputKFactorColumns(vector<int>{3});

 AllData.at(2) = new Dataset("CMS8pTtyt");
 AllData.at(2)->SetCut(setting);
 AllData.at(2)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS8pTtyt", "Jet", "FastNLO", "LHC", "CMS8pTtyt");
 AllData.at(2)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-173.3-PTavt_Yavt-0.00-0.35-nnlo.tab", "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-173.3-PTavt_Yavt-0.35-0.85-nnlo.tab", "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-173.3-PTavt_Yavt-0.85-1.45-nnlo.tab", "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-173.3-PTavt_Yavt-1.45-2.50-nnlo.tab"});

 AllData.at(3) = new Dataset("ATL8ttcoma");
 AllData.at(3)->SetCut(setting);
 AllData.at(3)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ATL8ttcoma", "Jet", "FastNLO", "LHC", "ATL8ttcoma");
 AllData.at(3)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-PTavt-MT2-173_3-bin1.tab", "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-Mtt-HT4-173_3-bin1.tab"});
*/
/*
 vector<Dataset *> AllData(12);

 AllData.at(0) = new Dataset("LHCb7ZWrap");
 AllData.at(0)->SetCut(setting);
 AllData.at(0)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/LHCb7ZWrap", "DrellYan", "ApplGrid", "LHC", "LHCb7ZWrap");
 AllData.at(0)->InputGridName(vector<TString>{"/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/245_1.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/245_2.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/245_3.root"});
 AllData.at(0)->InputApplGridRange(1, 1, 17);
 AllData.at(0)->InputKFactorColumns(vector<int>{5, 8});

 AllData.at(1) = new Dataset("LHCb8Zeer");
 AllData.at(1)->SetCut(setting);
 AllData.at(1)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/LHCb8Zeer", "DrellYan", "ApplGrid", "LHC", "LHCb8Zeer");
 AllData.at(1)->InputGridName(vector<TString>{"/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/246_1_KP_2018.1010.root"});
 AllData.at(1)->InputApplGridRange(1, 1, 17);
 AllData.at(1)->InputKFactorColumns(vector<int>{6, 8});

 AllData.at(2) = new Dataset("CMS8Wxa");
 AllData.at(2)->SetCut(setting);
 AllData.at(2)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS8Wxa", "DrellYan", "ApplGrid", "LHC", "CMS8Wxa");
 AllData.at(2)->InputGridName(vector<TString>{"/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/249_Wplus_applgrid_Pt25_xfitter_2018.0618.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/249_Wminus_applgrid_Pt25_xfitter_2018.0618.root"});
 AllData.at(2)->InputKFactorColumns(vector<int>{9});

 AllData.at(3) = new Dataset("LHCb8WZ");
 AllData.at(3)->SetCut(setting);
 AllData.at(3)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/LHCb8WZ", "DrellYan", "ApplGrid", "LHC", "LHCb8WZ");
 AllData.at(3)->InputGridName(vector<TString>{"/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/250_1.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/250_2.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/250_3.root"});
 AllData.at(3)->InputKFactorColumns(vector<int>{5, 10});

 AllData.at(4) = new Dataset("ATL8ZpT");
 AllData.at(4)->SetCut(setting);
 AllData.at(4)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ATL8ZpT", "DrellYan", "ApplGrid", "LHC", "ATL8ZpT");
 AllData.at(4)->InputGridName(vector<TString>{"/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/253_4.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/253_5.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/253_6.root"});
 AllData.at(4)->InputSystematicMethod(map<tuple<int, int>, int>{{make_tuple(0, 0), 0}, {make_tuple(1, 100), 1}});
 AllData.at(4)->InputKFactorColumns(vector<int>{6});

 AllData.at(5) = new Dataset("ATL7jtR6u");
 AllData.at(5)->SetCut(setting);
 AllData.at(5)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ATL7jtR6u", "Jet", "ApplGrid", "LHC", "ATL7jtR6u");
 AllData.at(5)->InputGridName(vector<TString>{"/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/510_1.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/510_2.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/510_3.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/510_4.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/510_5.root", "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/510_6.root"});
 AllData.at(5)->InputSystematicMethod(map<tuple<int, int>, int>{{make_tuple(0, 0), 0}, {make_tuple(1, 73), 1}});
 AllData.at(5)->InputKFactorColumns(vector<int>{5});

 AllData.at(6) = new Dataset("CMS7jtR7y6");
 AllData.at(6)->SetCut(setting);
 AllData.at(6)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS7jtR7y6", "Jet", "FastNLO", "LHC", "CMS7jtR7y6");
 AllData.at(6)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/fnl2332e_v23_fix_I1298810.tab"});
 AllData.at(6)->InputSystematicMethod(map<tuple<int, int>, int>{{make_tuple(0, 0), 0}, {make_tuple(1, 24), 1}});
 AllData.at(6)->InputKFactorColumns(vector<int>{6});

 AllData.at(7) = new Dataset("CMS8jtR7");
 AllData.at(7)->SetCut(setting);
 AllData.at(7)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS8jtR7", "Jet", "FastNLO", "LHC", "CMS8jtR7");
 AllData.at(7)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/fnl3332_I1487277.tab"});
 AllData.at(7)->InputSystematicMethod(map<tuple<int, int>, int>{{make_tuple(0, 0), 0}, {make_tuple(1, 27), 1}});
 AllData.at(7)->InputKFactorColumns(vector<int>{3});

 AllData.at(8) = new Dataset("CMS8pTtyt");
 AllData.at(8)->SetCut(setting);
 AllData.at(8)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS8pTtyt", "Jet", "FastNLO", "LHC", "CMS8pTtyt");
 AllData.at(8)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-173.3-PTavt_Yavt-0.00-0.35-nnlo.tab", "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-173.3-PTavt_Yavt-0.35-0.85-nnlo.tab", "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-173.3-PTavt_Yavt-0.85-1.45-nnlo.tab", "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-173.3-PTavt_Yavt-1.45-2.50-nnlo.tab"});

 AllData.at(9) = new Dataset("ATL8ttcoma");
 AllData.at(9)->SetCut(setting);
 AllData.at(9)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ATL8ttcoma", "Jet", "FastNLO", "LHC", "ATL8ttcoma");
 AllData.at(9)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-PTavt-MT2-173_3-bin1.tab", "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/LHC8-Mtt-HT4-173_3-bin1.tab"});

 AllData.at(10) = new Dataset("cdf2jtCor2");
 AllData.at(10)->SetCut(setting);
 AllData.at(10)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdf2jtCor2", "Jet", "FastNLO", "Tev", "cdf2jtCor2");
 AllData.at(10)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/fnt2007midp.tab"});

 AllData.at(11) = new Dataset("d02jtCor2");
 AllData.at(11)->SetCut(setting);
 AllData.at(11)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/d02jtCor2", "Jet", "FastNLO", "Tev", "d02jtCor2");
 AllData.at(11)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/fnt2009midp.tab"});
*/


/*
 vector<Dataset *> AllData(27);

 AllData.at(0) = new Dataset("HERAIpII");
 AllData.at(0)->SetCut(setting);
 AllData.at(0)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/HERAIpII", "DIS", "CTEQ", "", "HERAIpII");

 AllData.at(1) = new Dataset("BcdF2pCor");
 AllData.at(1)->SetCut(setting);
 AllData.at(1)->InputNormalization(0.9676, 0.1, 1.0);
 AllData.at(1)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/BcdF2pCor", "DIS", "CTEQ", "", "BcdF2pCor");

 AllData.at(2) = new Dataset("BcdF2dCor");
 AllData.at(2)->SetCut(setting);
 AllData.at(2)->InputNormalization(0.9676, 1.0, 0.0);
 AllData.at(2)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/BcdF2dCor", "DIS", "CTEQ", "", "BcdF2dCor");

 AllData.at(3) = new Dataset("NmcRatCor");
 AllData.at(3)->SetCut(setting);
 AllData.at(3)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/NmcRatCor", "DIS", "CTEQ", "", "NmcRatCor");

 AllData.at(4) = new Dataset("cdhswf2");
 AllData.at(4)->SetCut(setting);
 AllData.at(4)->InputNormalization(1.0137, 0.1, 1.0);
 AllData.at(4)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdhswf2", "DIS", "CTEQ", "", "cdhswf2");

 AllData.at(5) = new Dataset("cdhswf3");
 AllData.at(5)->SetCut(setting);
 AllData.at(5)->InputNormalization(1.0137, 1.0, 0.0);
 AllData.at(5)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdhswf3", "DIS", "CTEQ", "", "cdhswf3");

 AllData.at(6) = new Dataset("ccfrf2.mi");
 AllData.at(6)->SetCut(setting);
 AllData.at(6)->InputNormalization(1.0290, 0.1, 1.0);
 AllData.at(6)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ccfrf2.mi", "DIS", "CTEQ", "", "ccfrf2.mi");

 AllData.at(7) = new Dataset("ccfrf3.md");
 AllData.at(7)->SetCut(setting);
 AllData.at(7)->InputNormalization(1.0290, 1.0, 0.0);
 AllData.at(7)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ccfrf3.md", "DIS", "CTEQ", "", "ccfrf3.md");

 AllData.at(8) = new Dataset("NuTvNuChXN");
 AllData.at(8)->SetCut(setting);
 AllData.at(8)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/NuTvNuChXN", "DIS", "CTEQ", "", "NuTvNuChXN");

 AllData.at(9) = new Dataset("NuTvNbChXN");
 AllData.at(9)->SetCut(setting);
 AllData.at(9)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/NuTvNbChXN", "DIS", "CTEQ", "", "NuTvNbChXN");

 AllData.at(10) = new Dataset("CcfrNuChXN");
 AllData.at(10)->SetCut(setting);
 AllData.at(10)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CcfrNuChXN", "DIS", "CTEQ", "", "CcfrNuChXN");

 AllData.at(11) = new Dataset("CcfrNbChXN");
 AllData.at(11)->SetCut(setting);
 AllData.at(11)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CcfrNbChXN", "DIS", "CTEQ", "", "CcfrNbChXN");

 AllData.at(12) = new Dataset("Hn+9900x0b");
 AllData.at(12)->SetCut(setting);
 AllData.at(12)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/Hn+9900x0b", "DIS", "CTEQ", "", "Hn+9900x0b");

 AllData.at(13) = new Dataset("Hn1X0c");
 AllData.at(13)->SetCut(setting);
 AllData.at(13)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/Hn1X0c", "DIS", "CTEQ", "", "Hn1X0c");

 AllData.at(14) = new Dataset("H1FL10");
 AllData.at(14)->SetCut(setting);
 AllData.at(14)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/H1FL10", "DIS", "CTEQ", "", "H1FL10");

 AllData.at(15) = new Dataset("e605");
 AllData.at(15)->SetCut(setting);
 AllData.at(15)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/e605", "DrellYan", "CTEQ_DY", "", "e605");
 AllData.at(15)->InputKFactorColumns(vector<int>{2});

 AllData.at(16) = new Dataset("e866f");
 AllData.at(16)->SetCut(setting);
 AllData.at(16)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/e866f", "DrellYan", "CTEQ_DY", "", "e866f");
 AllData.at(16)->InputKFactorColumns(vector<int>{2});

 AllData.at(17) = new Dataset("e866ppxf");
 AllData.at(17)->SetCut(setting);
 AllData.at(17)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/e866ppxf", "DrellYan", "CTEQ_DY", "", "e866ppxf");
 AllData.at(17)->InputKFactorColumns(vector<int>{2});

 AllData.at(18) = new Dataset("cdfLasy");
 AllData.at(18)->SetCut(setting);
 AllData.at(18)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdfLasy", "DrellYan", "CTEQ_DY", "", "cdfLasy");

 AllData.at(19) = new Dataset("cdfLasy2");
 AllData.at(19)->SetCut(setting);
 AllData.at(19)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdfLasy2", "DrellYan", "CTEQ_DY", "", "cdfLasy2");

 AllData.at(20) = new Dataset("d02Masy1");
 AllData.at(20)->SetCut(setting);
 AllData.at(20)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/d02Masy1", "DrellYan", "CTEQ_DY", "", "d02Masy1");

 AllData.at(21) = new Dataset("ZyD02a");
 AllData.at(21)->SetCut(setting);
 AllData.at(21)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ZyD02a", "DrellYan", "CTEQ_DY", "", "ZyD02a");
 AllData.at(21)->InputKFactorColumns(vector<int>{2});

 AllData.at(22) = new Dataset("ZyCDF2");
 AllData.at(22)->SetCut(setting);
 AllData.at(22)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ZyCDF2", "DrellYan", "CTEQ_DY", "", "ZyCDF2");
 AllData.at(22)->InputKFactorColumns(vector<int>{2});

 AllData.at(23) = new Dataset("CMS7Masy2");
 AllData.at(23)->SetCut(setting);
 AllData.at(23)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS7Masy2", "DrellYan", "CTEQ_DY", "", "CMS7Masy2");

 AllData.at(24) = new Dataset("CMS7Easy");
 AllData.at(24)->SetCut(setting);
 AllData.at(24)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS7Easy", "DrellYan", "CTEQ_DY", "", "CMS7Easy");

 AllData.at(25) = new Dataset("ATL7_WZ");
 AllData.at(25)->SetCut(setting);
 AllData.at(25)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ATL7_WZ", "DrellYan", "CTEQ_DY", "", "ATL7_WZ");
 AllData.at(25)->InputKFactorColumns(vector<int>{3});

 AllData.at(26) = new Dataset("d02Easy5");
 AllData.at(26)->SetCut(setting);
 AllData.at(26)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/d02Easy5", "DrellYan", "CTEQ_DY", "", "d02Easy5");
*/

/*
 vector<Dataset *> AllData(12);

 AllData.at(0) = new Dataset("e605");
 AllData.at(0)->SetCut(setting);
 AllData.at(0)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/e605", "DrellYan", "CTEQ_DY", "", "e605");
 AllData.at(0)->InputKFactorColumns(vector<int>{2});

 AllData.at(1) = new Dataset("e866f");
 AllData.at(1)->SetCut(setting);
 AllData.at(1)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/e866f", "DrellYan", "CTEQ_DY", "", "e866f");
 AllData.at(1)->InputKFactorColumns(vector<int>{2});

 AllData.at(2) = new Dataset("e866ppxf");
 AllData.at(2)->SetCut(setting);
 AllData.at(2)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/e866ppxf", "DrellYan", "CTEQ_DY", "", "e866ppxf");
 AllData.at(2)->InputKFactorColumns(vector<int>{2});

 AllData.at(3) = new Dataset("cdfLasy");
 AllData.at(3)->SetCut(setting);
 AllData.at(3)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdfLasy", "DrellYan", "CTEQ_DY", "", "cdfLasy");

 AllData.at(4) = new Dataset("cdfLasy2");
 AllData.at(4)->SetCut(setting);
 AllData.at(4)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdfLasy2", "DrellYan", "CTEQ_DY", "", "cdfLasy2");

 AllData.at(5) = new Dataset("d02Masy1");
 AllData.at(5)->SetCut(setting);
 AllData.at(5)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/d02Masy1", "DrellYan", "CTEQ_DY", "", "d02Masy1");

 AllData.at(6) = new Dataset("ZyD02a");
 AllData.at(6)->SetCut(setting);
 AllData.at(6)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ZyD02a", "DrellYan", "CTEQ_DY", "", "ZyD02a");
 AllData.at(6)->InputKFactorColumns(vector<int>{2});

 AllData.at(7) = new Dataset("ZyCDF2");
 AllData.at(7)->SetCut(setting);
 AllData.at(7)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ZyCDF2", "DrellYan", "CTEQ_DY", "", "ZyCDF2");
 AllData.at(7)->InputKFactorColumns(vector<int>{2});

 AllData.at(8) = new Dataset("CMS7Masy2");
 AllData.at(8)->SetCut(setting);
 AllData.at(8)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS7Masy2", "DrellYan", "CTEQ_DY", "", "CMS7Masy2");

 AllData.at(9) = new Dataset("CMS7Easy");
 AllData.at(9)->SetCut(setting);
 AllData.at(9)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/CMS7Easy", "DrellYan", "CTEQ_DY", "", "CMS7Easy");

 AllData.at(10) = new Dataset("ATL7_WZ");
 AllData.at(10)->SetCut(setting);
 AllData.at(10)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/ATL7_WZ", "DrellYan", "CTEQ_DY", "", "ATL7_WZ");
 AllData.at(10)->InputKFactorColumns(vector<int>{3});

 AllData.at(11) = new Dataset("d02Easy5");
 AllData.at(11)->SetCut(setting);
 AllData.at(11)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/d02Easy5", "DrellYan", "CTEQ_DY", "", "d02Easy5");
*/
/*
 vector<Dataset *> AllData(2);

 AllData.at(0) = new Dataset("cdf2jtCor2");
 AllData.at(0)->SetCut(setting);
 AllData.at(0)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/cdf2jtCor2", "Jet", "FastNLO", "Tev", "cdf2jtCor2");
 AllData.at(0)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/fnt2007midp.tab"});

 AllData.at(1) = new Dataset("d02jtCor2");
 AllData.at(1)->SetCut(setting);
 AllData.at(1)->ReadFile("/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/d02jtCor2", "Jet", "FastNLO", "Tev", "d02jtCor2");
 AllData.at(1)->InputFNLOTableName(vector<string>{"/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/fnt2009midp.tab"});


 PDFChi2* run = new PDFChi2();
 run->BookLMPenalty(1, "ratioPDF", vector<int>{1}, vector<double>{10.0, 2.0, 0.2, 1e-8});
 run->BookLMPenalty(2, "ratioPDF", vector<int>{1}, vector<double>{10.0, 1.8, 0.4, 1e-5});
 run->BookLMPenalty(3, "LargeCoefficient", vector<int>{1}, vector<double>{0.01});
 run->BookLMPenalty(4, "SystematicShift", vector<int>{504, 25, 514, 23}, vector<double>{0.5, 0.5});

 run->Initialize(AllData, setting);
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
*/

/*
 setting.ConfigPDF("i2Tn3.30.pds");
 run->InitialPDF(setting);
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;

 setting.ConfigPDF("i2Tn3.50.pds");
 run->InitialPDF(setting);
 cout<<"Total Chi2 = "<<run->GetChi2(true)<<endl;
*/

 return 1;
}
