#include "RootCommon.h"
#include "Calculation/ApplGridHelper.h"

using namespace std;

int main(int argc, char** argv)
{
 TString GridNameYP1 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_0.0_1.0/grid-40-6-15-3-Z_y_0.0_1.0.root";
 TString GridNameYP2 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_1.0_1.25/grid-40-6-15-3-Z_y_1.0_1.25.root";
 TString GridNameYP3 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_1.25_1.5/grid-40-6-15-3-Z_y_1.25_1.5.root";
 TString GridNameYP4 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_1.5_2.4/grid-40-6-15-3-Z_y_1.5_2.4.root";

 TString GridNameYM1 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_-1.0_0.0/grid-40-6-15-3-Z_y_-1.0_0.0.root";
 TString GridNameYM2 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_-1.25_-1.0/grid-40-6-15-3-Z_y_-1.25_-1.0.root";
 TString GridNameYM3 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_-1.5_-1.25/grid-40-6-15-3-Z_y_-1.5_-1.25.root";
 TString GridNameYM4 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_-2.4_-1.5/grid-40-6-15-3-Z_y_-2.4_-1.5.root";

 TString GridNameD0 = "/msu/data/t3work5/yfu/MCFM_Dilution/ppbar/grid-40-6-15-3-Z_y_-5.0_5.0.root";

 TFile* CMSFile = new TFile("../CMSDilution/MC_results.root");
 TFile* D0File = new TFile("../D0Dilution/MC_results.root");

 TH3D* CMS_ZMass_ZY_QT_uu_YP_wrong = (TH3D *)CMSFile->Get("ZMass_ZY_QT_uu_YP_wrong");
 TH3D* CMS_ZMass_ZY_QT_uu_YP_right = (TH3D *)CMSFile->Get("ZMass_ZY_QT_uu_YP_right");
 TH3D* CMS_ZMass_ZY_QT_uu_YM_wrong = (TH3D *)CMSFile->Get("ZMass_ZY_QT_uu_YM_wrong");
 TH3D* CMS_ZMass_ZY_QT_uu_YM_right = (TH3D *)CMSFile->Get("ZMass_ZY_QT_uu_YM_right");
 TH3D* CMS_ZMass_ZY_QT_dd_YP_wrong = (TH3D *)CMSFile->Get("ZMass_ZY_QT_dd_YP_wrong");
 TH3D* CMS_ZMass_ZY_QT_dd_YP_right = (TH3D *)CMSFile->Get("ZMass_ZY_QT_dd_YP_right");
 TH3D* CMS_ZMass_ZY_QT_dd_YM_wrong = (TH3D *)CMSFile->Get("ZMass_ZY_QT_dd_YM_wrong");
 TH3D* CMS_ZMass_ZY_QT_dd_YM_right = (TH3D *)CMSFile->Get("ZMass_ZY_QT_dd_YM_right");
 TH3D* CMS_ZMass_ZY_QT_YP = (TH3D *)CMSFile->Get("ZMass_ZY_QT_YP");
 TH3D* CMS_ZMass_ZY_QT_YM = (TH3D *)CMSFile->Get("ZMass_ZY_QT_YM");

 TH3D* D0_ZMass_ZY_QT_uu_wrong = (TH3D *)D0File->Get("ZMass_ZY_QT_uu_wrong");
 TH3D* D0_ZMass_ZY_QT_uu_right = (TH3D *)D0File->Get("ZMass_ZY_QT_uu_right");
 TH3D* D0_ZMass_ZY_QT_dd_wrong = (TH3D *)D0File->Get("ZMass_ZY_QT_dd_wrong");
 TH3D* D0_ZMass_ZY_QT_dd_right = (TH3D *)D0File->Get("ZMass_ZY_QT_dd_right");
 TH3D* D0_ZMass_ZY_QT = (TH3D *)D0File->Get("ZMass_ZY_QT");

 TH1D* CMS_ZMass_ZY_QT_uu_YP_wrong_Y1 = (TH1D *)CMS_ZMass_ZY_QT_uu_YP_wrong->ProjectionX("CMS_ZMass_ZY_QT_uu_YP_wrong_Y1", 1, 1, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_uu_YP_right_Y1 = (TH1D *)CMS_ZMass_ZY_QT_uu_YP_right->ProjectionX("CMS_ZMass_ZY_QT_uu_YP_right_Y1", 1, 1, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_uu_YM_wrong_Y1 = (TH1D *)CMS_ZMass_ZY_QT_uu_YM_wrong->ProjectionX("CMS_ZMass_ZY_QT_uu_YM_wrong_Y1", 1, 1, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_uu_YM_right_Y1 = (TH1D *)CMS_ZMass_ZY_QT_uu_YM_right->ProjectionX("CMS_ZMass_ZY_QT_uu_YM_right_Y1", 1, 1, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YP_wrong_Y1 = (TH1D *)CMS_ZMass_ZY_QT_dd_YP_wrong->ProjectionX("CMS_ZMass_ZY_QT_dd_YP_wrong_Y1", 1, 1, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YP_right_Y1 = (TH1D *)CMS_ZMass_ZY_QT_dd_YP_right->ProjectionX("CMS_ZMass_ZY_QT_dd_YP_right_Y1", 1, 1, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YM_wrong_Y1 = (TH1D *)CMS_ZMass_ZY_QT_dd_YM_wrong->ProjectionX("CMS_ZMass_ZY_QT_dd_YM_wrong_Y1", 1, 1, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YM_right_Y1 = (TH1D *)CMS_ZMass_ZY_QT_dd_YM_right->ProjectionX("CMS_ZMass_ZY_QT_dd_YM_right_Y1", 1, 1, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_YP_Y1 = (TH1D *)CMS_ZMass_ZY_QT_YP->ProjectionX("CMS_ZMass_ZY_QT_YP_Y1", 1, 1, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_YM_Y1 = (TH1D *)CMS_ZMass_ZY_QT_YM->ProjectionX("CMS_ZMass_ZY_QT_YM_Y1", 1, 1, 1, 1);

 TH1D* CMS_ZMass_ZY_QT_uu_YP_wrong_Y2 = (TH1D *)CMS_ZMass_ZY_QT_uu_YP_wrong->ProjectionX("CMS_ZMass_ZY_QT_uu_YP_wrong_Y2", 2, 2, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_uu_YP_right_Y2 = (TH1D *)CMS_ZMass_ZY_QT_uu_YP_right->ProjectionX("CMS_ZMass_ZY_QT_uu_YP_right_Y2", 2, 2, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_uu_YM_wrong_Y2 = (TH1D *)CMS_ZMass_ZY_QT_uu_YM_wrong->ProjectionX("CMS_ZMass_ZY_QT_uu_YM_wrong_Y2", 2, 2, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_uu_YM_right_Y2 = (TH1D *)CMS_ZMass_ZY_QT_uu_YM_right->ProjectionX("CMS_ZMass_ZY_QT_uu_YM_right_Y2", 2, 2, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YP_wrong_Y2 = (TH1D *)CMS_ZMass_ZY_QT_dd_YP_wrong->ProjectionX("CMS_ZMass_ZY_QT_dd_YP_wrong_Y2", 2, 2, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YP_right_Y2 = (TH1D *)CMS_ZMass_ZY_QT_dd_YP_right->ProjectionX("CMS_ZMass_ZY_QT_dd_YP_right_Y2", 2, 2, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YM_wrong_Y2 = (TH1D *)CMS_ZMass_ZY_QT_dd_YM_wrong->ProjectionX("CMS_ZMass_ZY_QT_dd_YM_wrong_Y2", 2, 2, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YM_right_Y2 = (TH1D *)CMS_ZMass_ZY_QT_dd_YM_right->ProjectionX("CMS_ZMass_ZY_QT_dd_YM_right_Y2", 2, 2, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_YP_Y2 = (TH1D *)CMS_ZMass_ZY_QT_YP->ProjectionX("CMS_ZMass_ZY_QT_YP_Y2", 2, 2, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_YM_Y2 = (TH1D *)CMS_ZMass_ZY_QT_YM->ProjectionX("CMS_ZMass_ZY_QT_YM_Y2", 2, 2, 1, 1);

 TH1D* CMS_ZMass_ZY_QT_uu_YP_wrong_Y3 = (TH1D *)CMS_ZMass_ZY_QT_uu_YP_wrong->ProjectionX("CMS_ZMass_ZY_QT_uu_YP_wrong_Y3", 3, 3, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_uu_YP_right_Y3 = (TH1D *)CMS_ZMass_ZY_QT_uu_YP_right->ProjectionX("CMS_ZMass_ZY_QT_uu_YP_right_Y3", 3, 3, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_uu_YM_wrong_Y3 = (TH1D *)CMS_ZMass_ZY_QT_uu_YM_wrong->ProjectionX("CMS_ZMass_ZY_QT_uu_YM_wrong_Y3", 3, 3, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_uu_YM_right_Y3 = (TH1D *)CMS_ZMass_ZY_QT_uu_YM_right->ProjectionX("CMS_ZMass_ZY_QT_uu_YM_right_Y3", 3, 3, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YP_wrong_Y3 = (TH1D *)CMS_ZMass_ZY_QT_dd_YP_wrong->ProjectionX("CMS_ZMass_ZY_QT_dd_YP_wrong_Y3", 3, 3, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YP_right_Y3 = (TH1D *)CMS_ZMass_ZY_QT_dd_YP_right->ProjectionX("CMS_ZMass_ZY_QT_dd_YP_right_Y3", 3, 3, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YM_wrong_Y3 = (TH1D *)CMS_ZMass_ZY_QT_dd_YM_wrong->ProjectionX("CMS_ZMass_ZY_QT_dd_YM_wrong_Y3", 3, 3, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YM_right_Y3 = (TH1D *)CMS_ZMass_ZY_QT_dd_YM_right->ProjectionX("CMS_ZMass_ZY_QT_dd_YM_right_Y3", 3, 3, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_YP_Y3 = (TH1D *)CMS_ZMass_ZY_QT_YP->ProjectionX("CMS_ZMass_ZY_QT_YP_Y3", 3, 3, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_YM_Y3 = (TH1D *)CMS_ZMass_ZY_QT_YM->ProjectionX("CMS_ZMass_ZY_QT_YM_Y3", 3, 3, 1, 1);

 TH1D* CMS_ZMass_ZY_QT_uu_YP_wrong_Y4 = (TH1D *)CMS_ZMass_ZY_QT_uu_YP_wrong->ProjectionX("CMS_ZMass_ZY_QT_uu_YP_wrong_Y4", 4, 4, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_uu_YP_right_Y4 = (TH1D *)CMS_ZMass_ZY_QT_uu_YP_right->ProjectionX("CMS_ZMass_ZY_QT_uu_YP_right_Y4", 4, 4, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_uu_YM_wrong_Y4 = (TH1D *)CMS_ZMass_ZY_QT_uu_YM_wrong->ProjectionX("CMS_ZMass_ZY_QT_uu_YM_wrong_Y4", 4, 4, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_uu_YM_right_Y4 = (TH1D *)CMS_ZMass_ZY_QT_uu_YM_right->ProjectionX("CMS_ZMass_ZY_QT_uu_YM_right_Y4", 4, 4, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YP_wrong_Y4 = (TH1D *)CMS_ZMass_ZY_QT_dd_YP_wrong->ProjectionX("CMS_ZMass_ZY_QT_dd_YP_wrong_Y4", 4, 4, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YP_right_Y4 = (TH1D *)CMS_ZMass_ZY_QT_dd_YP_right->ProjectionX("CMS_ZMass_ZY_QT_dd_YP_right_Y4", 4, 4, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YM_wrong_Y4 = (TH1D *)CMS_ZMass_ZY_QT_dd_YM_wrong->ProjectionX("CMS_ZMass_ZY_QT_dd_YM_wrong_Y4", 4, 4, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_dd_YM_right_Y4 = (TH1D *)CMS_ZMass_ZY_QT_dd_YM_right->ProjectionX("CMS_ZMass_ZY_QT_dd_YM_right_Y4", 4, 4, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_YP_Y4 = (TH1D *)CMS_ZMass_ZY_QT_YP->ProjectionX("CMS_ZMass_ZY_QT_YP_Y4", 4, 4, 1, 1);
 TH1D* CMS_ZMass_ZY_QT_YM_Y4 = (TH1D *)CMS_ZMass_ZY_QT_YM->ProjectionX("CMS_ZMass_ZY_QT_YM_Y4", 4, 4, 1, 1);

 TH1D* D0_ZMass_ZY_QT_uu_wrong_Y1 = (TH1D *)D0_ZMass_ZY_QT_uu_wrong->ProjectionX("D0_ZMass_ZY_QT_uu_wrong", 1, 1, 1, 1);;
 TH1D* D0_ZMass_ZY_QT_uu_right_Y1 = (TH1D *)D0_ZMass_ZY_QT_uu_right->ProjectionX("D0_ZMass_ZY_QT_uu_right", 1, 1, 1, 1);;
 TH1D* D0_ZMass_ZY_QT_dd_wrong_Y1 = (TH1D *)D0_ZMass_ZY_QT_dd_wrong->ProjectionX("D0_ZMass_ZY_QT_dd_wrong", 1, 1, 1, 1);;
 TH1D* D0_ZMass_ZY_QT_dd_right_Y1 = (TH1D *)D0_ZMass_ZY_QT_dd_right->ProjectionX("D0_ZMass_ZY_QT_dd_right", 1, 1, 1, 1);;
 TH1D* D0_ZMass_ZY_QT_Y1 = (TH1D *)D0_ZMass_ZY_QT->ProjectionX("D0_ZMass_ZY_QT", 1, 1, 1, 1);

 ApplGridHelper* grid;
 grid = new ApplGridHelper();
 grid->InitialPDF("CT18NNLO", 0);

 grid->InitialGrid(GridNameYP1);
 grid->InitialGrid(GridNameYP2);
 grid->InitialGrid(GridNameYP3);
 grid->InitialGrid(GridNameYP4);
 grid->InitialGrid(GridNameYM1);
 grid->InitialGrid(GridNameYM2);
 grid->InitialGrid(GridNameYM3);
 grid->InitialGrid(GridNameYM4);
 grid->InitialGrid(GridNameD0);

 vector<TString> uu_YP_right_SubProcs = {"uubar", "ugluon", "gluonubar"};//uubar right
 vector<TString> uu_YM_right_SubProcs = {"ubaru", "ubargluon", "gluonu"};//ubaru right
 vector<TString> uu_YM_wrong_SubProcs = {"uubar", "ugluon", "gluonubar"};//uubar wrong
 vector<TString> uu_YP_wrong_SubProcs = {"ubaru", "ubargluon", "gluonu"};//ubaru wrong
 vector<TString> dd_YP_right_SubProcs = {"ddbar", "dgluon", "gluondbar"};//ddbar right
 vector<TString> dd_YM_right_SubProcs = {"dbard", "dbargluon", "gluond"};//dbard right
 vector<TString> dd_YM_wrong_SubProcs = {"ddbar", "dgluon", "gluondbar"};//ddbar wrong
 vector<TString> dd_YP_wrong_SubProcs = {"dbard", "dbargluon", "gluond"};//dbard wrong

 vector<TString> ppbar_uu_right_SubProcs = {"uubar", "ugluon", "gluonubar"};
 vector<TString> ppbar_uu_wrong_SubProcs = {"ubaru", "ubargluon", "gluonu"};
 vector<TString> ppbar_dd_right_SubProcs = {"ddbar", "dgluon", "gluondbar"};
 vector<TString> ppbar_dd_wrong_SubProcs = {"dbard", "dbargluon", "gluond"};

 grid->GenerateKFactor("CMS_uu_YP_right_Y1.kf", GridNameYP1, CMS_ZMass_ZY_QT_uu_YP_right_Y1, uu_YP_right_SubProcs);
 grid->GenerateKFactor("CMS_uu_YM_right_Y1.kf", GridNameYM1, CMS_ZMass_ZY_QT_uu_YM_right_Y1, uu_YM_right_SubProcs);
 grid->GenerateKFactor("CMS_uu_YM_wrong_Y1.kf", GridNameYM1, CMS_ZMass_ZY_QT_uu_YM_wrong_Y1, uu_YM_wrong_SubProcs);
 grid->GenerateKFactor("CMS_uu_YP_wrong_Y1.kf", GridNameYP1, CMS_ZMass_ZY_QT_uu_YP_wrong_Y1, uu_YP_wrong_SubProcs);
 grid->GenerateKFactor("CMS_dd_YP_right_Y1.kf", GridNameYP1, CMS_ZMass_ZY_QT_dd_YP_right_Y1, dd_YP_right_SubProcs);
 grid->GenerateKFactor("CMS_dd_YM_right_Y1.kf", GridNameYM1, CMS_ZMass_ZY_QT_dd_YM_right_Y1, dd_YM_right_SubProcs);
 grid->GenerateKFactor("CMS_dd_YM_wrong_Y1.kf", GridNameYM1, CMS_ZMass_ZY_QT_dd_YM_wrong_Y1, dd_YM_wrong_SubProcs);
 grid->GenerateKFactor("CMS_dd_YP_wrong_Y1.kf", GridNameYP1, CMS_ZMass_ZY_QT_dd_YP_wrong_Y1, dd_YP_wrong_SubProcs);
 grid->GenerateKFactor("CMS_total_YP_Y1.kf", GridNameYP1, CMS_ZMass_ZY_QT_YP_Y1);
 grid->GenerateKFactor("CMS_total_YM_Y1.kf", GridNameYM1, CMS_ZMass_ZY_QT_YM_Y1);

 grid->GenerateKFactor("CMS_uu_YP_right_Y2.kf", GridNameYP2, CMS_ZMass_ZY_QT_uu_YP_right_Y2, uu_YP_right_SubProcs);
 grid->GenerateKFactor("CMS_uu_YM_right_Y2.kf", GridNameYM2, CMS_ZMass_ZY_QT_uu_YM_right_Y2, uu_YM_right_SubProcs);
 grid->GenerateKFactor("CMS_uu_YM_wrong_Y2.kf", GridNameYM2, CMS_ZMass_ZY_QT_uu_YM_wrong_Y2, uu_YM_wrong_SubProcs);
 grid->GenerateKFactor("CMS_uu_YP_wrong_Y2.kf", GridNameYP2, CMS_ZMass_ZY_QT_uu_YP_wrong_Y2, uu_YP_wrong_SubProcs);
 grid->GenerateKFactor("CMS_dd_YP_right_Y2.kf", GridNameYP2, CMS_ZMass_ZY_QT_dd_YP_right_Y2, dd_YP_right_SubProcs);
 grid->GenerateKFactor("CMS_dd_YM_right_Y2.kf", GridNameYM2, CMS_ZMass_ZY_QT_dd_YM_right_Y2, dd_YM_right_SubProcs);
 grid->GenerateKFactor("CMS_dd_YM_wrong_Y2.kf", GridNameYM2, CMS_ZMass_ZY_QT_dd_YM_wrong_Y2, dd_YM_wrong_SubProcs);
 grid->GenerateKFactor("CMS_dd_YP_wrong_Y2.kf", GridNameYP2, CMS_ZMass_ZY_QT_dd_YP_wrong_Y2, dd_YP_wrong_SubProcs);
 grid->GenerateKFactor("CMS_total_YP_Y2.kf", GridNameYP2, CMS_ZMass_ZY_QT_YP_Y2);
 grid->GenerateKFactor("CMS_total_YM_Y2.kf", GridNameYM2, CMS_ZMass_ZY_QT_YM_Y2);

 grid->GenerateKFactor("CMS_uu_YP_right_Y3.kf", GridNameYP3, CMS_ZMass_ZY_QT_uu_YP_right_Y3, uu_YP_right_SubProcs);
 grid->GenerateKFactor("CMS_uu_YM_right_Y3.kf", GridNameYM3, CMS_ZMass_ZY_QT_uu_YM_right_Y3, uu_YM_right_SubProcs);
 grid->GenerateKFactor("CMS_uu_YM_wrong_Y3.kf", GridNameYM3, CMS_ZMass_ZY_QT_uu_YM_wrong_Y3, uu_YM_wrong_SubProcs);
 grid->GenerateKFactor("CMS_uu_YP_wrong_Y3.kf", GridNameYP3, CMS_ZMass_ZY_QT_uu_YP_wrong_Y3, uu_YP_wrong_SubProcs);
 grid->GenerateKFactor("CMS_dd_YP_right_Y3.kf", GridNameYP3, CMS_ZMass_ZY_QT_dd_YP_right_Y3, dd_YP_right_SubProcs);
 grid->GenerateKFactor("CMS_dd_YM_right_Y3.kf", GridNameYM3, CMS_ZMass_ZY_QT_dd_YM_right_Y3, dd_YM_right_SubProcs);
 grid->GenerateKFactor("CMS_dd_YM_wrong_Y3.kf", GridNameYM3, CMS_ZMass_ZY_QT_dd_YM_wrong_Y3, dd_YM_wrong_SubProcs);
 grid->GenerateKFactor("CMS_dd_YP_wrong_Y3.kf", GridNameYP3, CMS_ZMass_ZY_QT_dd_YP_wrong_Y3, dd_YP_wrong_SubProcs);
 grid->GenerateKFactor("CMS_total_YP_Y3.kf", GridNameYP3, CMS_ZMass_ZY_QT_YP_Y3);
 grid->GenerateKFactor("CMS_total_YM_Y3.kf", GridNameYM3, CMS_ZMass_ZY_QT_YM_Y3);

 grid->GenerateKFactor("CMS_uu_YP_right_Y4.kf", GridNameYP4, CMS_ZMass_ZY_QT_uu_YP_right_Y4, uu_YP_right_SubProcs);
 grid->GenerateKFactor("CMS_uu_YM_right_Y4.kf", GridNameYM4, CMS_ZMass_ZY_QT_uu_YM_right_Y4, uu_YM_right_SubProcs);
 grid->GenerateKFactor("CMS_uu_YM_wrong_Y4.kf", GridNameYM4, CMS_ZMass_ZY_QT_uu_YM_wrong_Y4, uu_YM_wrong_SubProcs);
 grid->GenerateKFactor("CMS_uu_YP_wrong_Y4.kf", GridNameYP4, CMS_ZMass_ZY_QT_uu_YP_wrong_Y4, uu_YP_wrong_SubProcs);
 grid->GenerateKFactor("CMS_dd_YP_right_Y4.kf", GridNameYP4, CMS_ZMass_ZY_QT_dd_YP_right_Y4, dd_YP_right_SubProcs);
 grid->GenerateKFactor("CMS_dd_YM_right_Y4.kf", GridNameYM4, CMS_ZMass_ZY_QT_dd_YM_right_Y4, dd_YM_right_SubProcs);
 grid->GenerateKFactor("CMS_dd_YM_wrong_Y4.kf", GridNameYM4, CMS_ZMass_ZY_QT_dd_YM_wrong_Y4, dd_YM_wrong_SubProcs);
 grid->GenerateKFactor("CMS_dd_YP_wrong_Y4.kf", GridNameYP4, CMS_ZMass_ZY_QT_dd_YP_wrong_Y4, dd_YP_wrong_SubProcs);
 grid->GenerateKFactor("CMS_total_YP_Y4.kf", GridNameYP4, CMS_ZMass_ZY_QT_YP_Y4);
 grid->GenerateKFactor("CMS_total_YM_Y4.kf", GridNameYM4, CMS_ZMass_ZY_QT_YM_Y4);

 grid->GenerateKFactorppbar("D0_uu_right.kf", GridNameD0, D0_ZMass_ZY_QT_uu_right_Y1, ppbar_uu_right_SubProcs);
 grid->GenerateKFactorppbar("D0_uu_wrong.kf", GridNameD0, D0_ZMass_ZY_QT_uu_wrong_Y1, ppbar_uu_wrong_SubProcs);
 grid->GenerateKFactorppbar("D0_dd_right.kf", GridNameD0, D0_ZMass_ZY_QT_dd_right_Y1, ppbar_dd_right_SubProcs);
 grid->GenerateKFactorppbar("D0_dd_wrong.kf", GridNameD0, D0_ZMass_ZY_QT_dd_wrong_Y1, ppbar_dd_wrong_SubProcs);
 grid->GenerateKFactorppbar("D0_total.kf", GridNameD0, D0_ZMass_ZY_QT_Y1);

 return 1;
}
