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

 pdf->ParameterOutput();

 pdf->Initialize(1, FlavorList, FlagList);

 HoppetInterface* hoppet = new HoppetInterface();
 hoppet->SetAlphaSQ0(0.118, 91.19);
 hoppet->Initialize(pdf, 1.29);
 hoppet->Evolution(0.01, 100.0);
 hoppet->Evolution(0.00806, 17.3205);

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

 vector<Dataset *> AllData(3);

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

/* AllData.at(0) = new Dataset("LHCb7ZWrap");
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
*/

 for(int i = 0; i < AllData.size(); i++){
   AllData.at(i)->InitialPrediction(setting);
 }

 for(int i = 0; i < AllData.size(); i++){
   cout<<endl;
   AllData.at(i)->GetPrediction();
 }
 for(int i = 0; i < AllData.size(); i++){
   AllData.at(i)->PrepareChi2();
   AllData.at(i)->Chi2(true);
 }


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
