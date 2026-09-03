#include "Calculation/ApplGridHelper.h"
#include "ReadInRoot/MCFMWWBoost.h"

TString PDFName = "CT14nnlo";
int nSet = 56;

TString GridsDIR = "GridFiles";
TString KFactorDIR = "../precision_0.0001";

TString GridName_ATLAS7TeV_pT =    "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_ATLAS7TeV_pT.root";
TString GridName_ATLAS7TeV_pT_Y1 = "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_ATLAS7TeV_pT_Y1.root";
TString GridName_ATLAS7TeV_pT_Y2 = "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_ATLAS7TeV_pT_Y2.root";
TString GridName_ATLAS7TeV_pT_Y3 = "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_ATLAS7TeV_pT_Y3.root";
TString GridName_ATLAS8TeV_pT =    "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_ATLAS8TeV_pT.root";
TString GridName_ATLAS8TeV_pT_Y1 = "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_ATLAS8TeV_pT_Y1.root";
TString GridName_ATLAS8TeV_pT_Y2 = "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_ATLAS8TeV_pT_Y2.root";
TString GridName_ATLAS8TeV_pT_Y3 = "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_ATLAS8TeV_pT_Y3.root";
TString GridName_ATLAS8TeV_pT_Y4 = "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_ATLAS8TeV_pT_Y4.root";
TString GridName_ATLAS8TeV_pT_Y5 = "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_ATLAS8TeV_pT_Y5.root";
TString GridName_ATLAS8TeV_pT_Y6 = "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_ATLAS8TeV_pT_Y6.root";
TString GridName_ATLAS13TeV_pT =   "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_ATLAS13TeV_pT.root";
TString GridName_CMS7TeV_pT =      "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_CMS7TeV_pT.root";
TString GridName_CMS8TeV_pT =      "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_CMS8TeV_pT.root";
TString GridName_CMS13TeV_pT =     "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_CMS13TeV_pT.root";
TString GridName_CMS13TeV_pT_Y1 =  "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_CMS13TeV_pT_Y1.root";
TString GridName_CMS13TeV_pT_Y2 =  "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_CMS13TeV_pT_Y2.root";
TString GridName_CMS13TeV_pT_Y3 =  "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_CMS13TeV_pT_Y3.root";
TString GridName_CMS13TeV_pT_Y4 =  "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_CMS13TeV_pT_Y4.root";
TString GridName_CMS13TeV_pT_Y5 =  "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_CMS13TeV_pT_Y5.root";
TString GridName_LHCb13TeV_pT =    "/Data/yaofu/ApplCT18DY/" + GridsDIR + "/grid-40-6-15-3-Zjet_LHCb13TeV_pT.root";

void ApplConvolute(ApplGridHelper* grid)
{
 TH1D* ATLAS7TeV_pT = grid->ConvoluteBasic(GridName_ATLAS7TeV_pT, "ATLAS7TeV_pT");
 TH1D* ATLAS7TeV_pT_Y1 = grid->ConvoluteBasic(GridName_ATLAS7TeV_pT_Y1, "ATLAS7TeV_pT_Y1");
 TH1D* ATLAS7TeV_pT_Y2 = grid->ConvoluteBasic(GridName_ATLAS7TeV_pT_Y2, "ATLAS7TeV_pT_Y2");
 TH1D* ATLAS7TeV_pT_Y3 = grid->ConvoluteBasic(GridName_ATLAS7TeV_pT_Y3, "ATLAS7TeV_pT_Y3");
 TH1D* ATLAS8TeV_pT = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT, "ATLAS8TeV_pT");
 TH1D* ATLAS8TeV_pT_Y1 = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT_Y1, "ATLAS8TeV_pT_Y1");
 TH1D* ATLAS8TeV_pT_Y2 = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT_Y2, "ATLAS8TeV_pT_Y2");
 TH1D* ATLAS8TeV_pT_Y3 = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT_Y3, "ATLAS8TeV_pT_Y3");
 TH1D* ATLAS8TeV_pT_Y4 = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT_Y4, "ATLAS8TeV_pT_Y4");
 TH1D* ATLAS8TeV_pT_Y5 = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT_Y5, "ATLAS8TeV_pT_Y5");
 TH1D* ATLAS8TeV_pT_Y6 = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT_Y6, "ATLAS8TeV_pT_Y6");
 TH1D* ATLAS13TeV_pT = grid->ConvoluteBasic(GridName_ATLAS13TeV_pT, "ATLAS13TeV_pT");
 TH1D* CMS7TeV_pT = grid->ConvoluteBasic(GridName_CMS7TeV_pT, "CMS7TeV_pT");
 TH1D* CMS8TeV_pT = grid->ConvoluteBasic(GridName_CMS8TeV_pT, "CMS8TeV_pT");
 TH1D* CMS13TeV_pT = grid->ConvoluteBasic(GridName_CMS13TeV_pT, "CMS13TeV_pT");
 TH1D* CMS13TeV_pT_Y1 = grid->ConvoluteBasic(GridName_CMS13TeV_pT_Y1, "CMS13TeV_pT_Y1");
 TH1D* CMS13TeV_pT_Y2 = grid->ConvoluteBasic(GridName_CMS13TeV_pT_Y2, "CMS13TeV_pT_Y2");
 TH1D* CMS13TeV_pT_Y3 = grid->ConvoluteBasic(GridName_CMS13TeV_pT_Y3, "CMS13TeV_pT_Y3");
 TH1D* CMS13TeV_pT_Y4 = grid->ConvoluteBasic(GridName_CMS13TeV_pT_Y4, "CMS13TeV_pT_Y4");
 TH1D* CMS13TeV_pT_Y5 = grid->ConvoluteBasic(GridName_CMS13TeV_pT_Y5, "CMS13TeV_pT_Y5");
 TH1D* LHCb13TeV_pT = grid->ConvoluteBasic(GridName_LHCb13TeV_pT, "LHCb13TeV_pT");

 TH1D* ATLAS7TeV_pT_NNLO = grid->ConvoluteBasic(GridName_ATLAS7TeV_pT, "ATLAS7TeV_pT_NNLO",          KFactorDIR + "/KFactor_ATLAS7TeV_pT.txt");
 TH1D* ATLAS7TeV_pT_Y1_NNLO = grid->ConvoluteBasic(GridName_ATLAS7TeV_pT_Y1, "ATLAS7TeV_pT_Y1_NNLO", KFactorDIR + "/KFactor_ATLAS7TeV_pT_Y1.txt");
 TH1D* ATLAS7TeV_pT_Y2_NNLO = grid->ConvoluteBasic(GridName_ATLAS7TeV_pT_Y2, "ATLAS7TeV_pT_Y2_NNLO", KFactorDIR + "/KFactor_ATLAS7TeV_pT_Y2.txt");
 TH1D* ATLAS7TeV_pT_Y3_NNLO = grid->ConvoluteBasic(GridName_ATLAS7TeV_pT_Y3, "ATLAS7TeV_pT_Y3_NNLO", KFactorDIR + "/KFactor_ATLAS7TeV_pT_Y3.txt");
 TH1D* ATLAS8TeV_pT_NNLO = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT, "ATLAS8TeV_pT_NNLO",          KFactorDIR + "/KFactor_ATLAS8TeV_pT.txt");
 TH1D* ATLAS8TeV_pT_Y1_NNLO = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT_Y1, "ATLAS8TeV_pT_Y1_NNLO", KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y1.txt");
 TH1D* ATLAS8TeV_pT_Y2_NNLO = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT_Y2, "ATLAS8TeV_pT_Y2_NNLO", KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y2.txt");
 TH1D* ATLAS8TeV_pT_Y3_NNLO = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT_Y3, "ATLAS8TeV_pT_Y3_NNLO", KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y3.txt");
 TH1D* ATLAS8TeV_pT_Y4_NNLO = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT_Y4, "ATLAS8TeV_pT_Y4_NNLO", KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y4.txt");
 TH1D* ATLAS8TeV_pT_Y5_NNLO = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT_Y5, "ATLAS8TeV_pT_Y5_NNLO", KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y5.txt");
 TH1D* ATLAS8TeV_pT_Y6_NNLO = grid->ConvoluteBasic(GridName_ATLAS8TeV_pT_Y6, "ATLAS8TeV_pT_Y6_NNLO", KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y6.txt");
 TH1D* ATLAS13TeV_pT_NNLO = grid->ConvoluteBasic(GridName_ATLAS13TeV_pT, "ATLAS13TeV_pT_NNLO",       KFactorDIR + "/KFactor_ATLAS13TeV_pT.txt");
 TH1D* CMS7TeV_pT_NNLO = grid->ConvoluteBasic(GridName_CMS7TeV_pT, "CMS7TeV_pT_NNLO",                KFactorDIR + "/KFactor_CMS7TeV_pT.txt");
 TH1D* CMS8TeV_pT_NNLO = grid->ConvoluteBasic(GridName_CMS8TeV_pT, "CMS8TeV_pT_NNLO",                KFactorDIR + "/KFactor_CMS8TeV_pT.txt");
 TH1D* CMS13TeV_pT_NNLO = grid->ConvoluteBasic(GridName_CMS13TeV_pT, "CMS13TeV_pT_NNLO",             KFactorDIR + "/KFactor_CMS13TeV_pT.txt");
 TH1D* CMS13TeV_pT_Y1_NNLO = grid->ConvoluteBasic(GridName_CMS13TeV_pT_Y1, "CMS13TeV_pT_Y1_NNLO",    KFactorDIR + "/KFactor_CMS13TeV_pT_Y1.txt");
 TH1D* CMS13TeV_pT_Y2_NNLO = grid->ConvoluteBasic(GridName_CMS13TeV_pT_Y2, "CMS13TeV_pT_Y2_NNLO",    KFactorDIR + "/KFactor_CMS13TeV_pT_Y2.txt");
 TH1D* CMS13TeV_pT_Y3_NNLO = grid->ConvoluteBasic(GridName_CMS13TeV_pT_Y3, "CMS13TeV_pT_Y3_NNLO",    KFactorDIR + "/KFactor_CMS13TeV_pT_Y3.txt");
 TH1D* CMS13TeV_pT_Y4_NNLO = grid->ConvoluteBasic(GridName_CMS13TeV_pT_Y4, "CMS13TeV_pT_Y4_NNLO",    KFactorDIR + "/KFactor_CMS13TeV_pT_Y4.txt");
 TH1D* CMS13TeV_pT_Y5_NNLO = grid->ConvoluteBasic(GridName_CMS13TeV_pT_Y5, "CMS13TeV_pT_Y5_NNLO",    KFactorDIR + "/KFactor_CMS13TeV_pT_Y5.txt");
 TH1D* LHCb13TeV_pT_NNLO = grid->ConvoluteBasic(GridName_LHCb13TeV_pT, "LHCb13TeV_pT_NNLO",          KFactorDIR + "/KFactor_LHCb13TeV_pT.txt");

 grid->CalcPDFUnc(GridName_ATLAS7TeV_pT, "ATLAS7TeV_pT"      , PDFName, nSet, "", 11, 26);
 grid->CalcPDFUnc(GridName_ATLAS7TeV_pT_Y1, "ATLAS7TeV_pT_Y1", PDFName, nSet, "", 11, 26);
 grid->CalcPDFUnc(GridName_ATLAS7TeV_pT_Y2, "ATLAS7TeV_pT_Y2", PDFName, nSet, "", 11, 26);
 grid->CalcPDFUnc(GridName_ATLAS7TeV_pT_Y3, "ATLAS7TeV_pT_Y3", PDFName, nSet, "", 11, 26);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT, "ATLAS8TeV_pT"      , PDFName, nSet, "", 11, 43);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT_Y1, "ATLAS8TeV_pT_Y1", PDFName, nSet, "", 9, 20);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT_Y2, "ATLAS8TeV_pT_Y2", PDFName, nSet, "", 9, 20);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT_Y3, "ATLAS8TeV_pT_Y3", PDFName, nSet, "", 9, 20);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT_Y4, "ATLAS8TeV_pT_Y4", PDFName, nSet, "", 9, 20);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT_Y5, "ATLAS8TeV_pT_Y5", PDFName, nSet, "", 9, 20);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT_Y6, "ATLAS8TeV_pT_Y6", PDFName, nSet, "", 9, 20);
 grid->CalcPDFUnc(GridName_ATLAS13TeV_pT, "ATLAS13TeV_pT"    , PDFName, nSet, "", 11, 43);
 grid->CalcPDFUnc(GridName_CMS7TeV_pT, "CMS7TeV_pT"          , PDFName, nSet, "", 9, 18);
 grid->CalcPDFUnc(GridName_CMS8TeV_pT, "CMS8TeV_pT"          , PDFName, nSet, "", 9, 18);
 grid->CalcPDFUnc(GridName_CMS13TeV_pT, "CMS13TeV_pT"        , PDFName, nSet, "", 17, 35);
 grid->CalcPDFUnc(GridName_CMS13TeV_pT_Y1, "CMS13TeV_pT_Y1"  , PDFName, nSet, "", 17, 33);
 grid->CalcPDFUnc(GridName_CMS13TeV_pT_Y2, "CMS13TeV_pT_Y2"  , PDFName, nSet, "", 17, 33);
 grid->CalcPDFUnc(GridName_CMS13TeV_pT_Y3, "CMS13TeV_pT_Y3"  , PDFName, nSet, "", 17, 33);
 grid->CalcPDFUnc(GridName_CMS13TeV_pT_Y4, "CMS13TeV_pT_Y4"  , PDFName, nSet, "", 17, 33);
 grid->CalcPDFUnc(GridName_CMS13TeV_pT_Y5, "CMS13TeV_pT_Y5"  , PDFName, nSet, "", 17, 33);
 grid->CalcPDFUnc(GridName_LHCb13TeV_pT, "LHCb13TeV_pT"      , PDFName, nSet, "", 11, 14);

 grid->CalcPDFUnc(GridName_ATLAS7TeV_pT, "ATLAS7TeV_pT_NNLO"      , PDFName, nSet, KFactorDIR + "/KFactor_ATLAS7TeV_pT.txt",    11, 26);
 grid->CalcPDFUnc(GridName_ATLAS7TeV_pT_Y1, "ATLAS7TeV_pT_Y1_NNLO", PDFName, nSet, KFactorDIR + "/KFactor_ATLAS7TeV_pT_Y1.txt", 11, 26);
 grid->CalcPDFUnc(GridName_ATLAS7TeV_pT_Y2, "ATLAS7TeV_pT_Y2_NNLO", PDFName, nSet, KFactorDIR + "/KFactor_ATLAS7TeV_pT_Y2.txt", 11, 26);
 grid->CalcPDFUnc(GridName_ATLAS7TeV_pT_Y3, "ATLAS7TeV_pT_Y3_NNLO", PDFName, nSet, KFactorDIR + "/KFactor_ATLAS7TeV_pT_Y3.txt", 11, 26);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT, "ATLAS8TeV_pT_NNLO"      , PDFName, nSet, KFactorDIR + "/KFactor_ATLAS8TeV_pT.txt",    11, 43);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT_Y1, "ATLAS8TeV_pT_Y1_NNLO", PDFName, nSet, KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y1.txt", 9, 20);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT_Y2, "ATLAS8TeV_pT_Y2_NNLO", PDFName, nSet, KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y2.txt", 9, 20);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT_Y3, "ATLAS8TeV_pT_Y3_NNLO", PDFName, nSet, KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y3.txt", 9, 20);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT_Y4, "ATLAS8TeV_pT_Y4_NNLO", PDFName, nSet, KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y4.txt", 9, 20);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT_Y5, "ATLAS8TeV_pT_Y5_NNLO", PDFName, nSet, KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y5.txt", 9, 20);
 grid->CalcPDFUnc(GridName_ATLAS8TeV_pT_Y6, "ATLAS8TeV_pT_Y6_NNLO", PDFName, nSet, KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y6.txt", 9, 20);
 grid->CalcPDFUnc(GridName_ATLAS13TeV_pT, "ATLAS13TeV_pT_NNLO"    , PDFName, nSet, KFactorDIR + "/KFactor_ATLAS13TeV_pT.txt",   11, 43);
 grid->CalcPDFUnc(GridName_CMS7TeV_pT, "CMS7TeV_pT_NNLO"          , PDFName, nSet, KFactorDIR + "/KFactor_CMS7TeV_pT.txt",      9, 18);
 grid->CalcPDFUnc(GridName_CMS8TeV_pT, "CMS8TeV_pT_NNLO"          , PDFName, nSet, KFactorDIR + "/KFactor_CMS8TeV_pT.txt",      9, 18);
 grid->CalcPDFUnc(GridName_CMS13TeV_pT, "CMS13TeV_pT_NNLO"        , PDFName, nSet, KFactorDIR + "/KFactor_CMS13TeV_pT.txt",     17, 35);
 grid->CalcPDFUnc(GridName_CMS13TeV_pT_Y1, "CMS13TeV_pT_Y1_NNLO"  , PDFName, nSet, KFactorDIR + "/KFactor_CMS13TeV_pT_Y1.txt",  17, 33);
 grid->CalcPDFUnc(GridName_CMS13TeV_pT_Y2, "CMS13TeV_pT_Y2_NNLO"  , PDFName, nSet, KFactorDIR + "/KFactor_CMS13TeV_pT_Y2.txt",  17, 33);
 grid->CalcPDFUnc(GridName_CMS13TeV_pT_Y3, "CMS13TeV_pT_Y3_NNLO"  , PDFName, nSet, KFactorDIR + "/KFactor_CMS13TeV_pT_Y3.txt",  17, 33);
 grid->CalcPDFUnc(GridName_CMS13TeV_pT_Y4, "CMS13TeV_pT_Y4_NNLO"  , PDFName, nSet, KFactorDIR + "/KFactor_CMS13TeV_pT_Y4.txt",  17, 33);
 grid->CalcPDFUnc(GridName_CMS13TeV_pT_Y5, "CMS13TeV_pT_Y5_NNLO"  , PDFName, nSet, KFactorDIR + "/KFactor_CMS13TeV_pT_Y5.txt",  17, 33);
 grid->CalcPDFUnc(GridName_LHCb13TeV_pT, "LHCb13TeV_pT_NNLO"      , PDFName, nSet, KFactorDIR + "/KFactor_LHCb13TeV_pT.txt",    11, 14);

}

int main(int argc, char** argv)
{
 if(argc != 3){
   cout<<"usage: ./ApplCT18DY PDFName nSet"<<endl;
   return 0;
 }

 TString InputPDFName = (TString)argv[1];
 int InputnSet = stoi(argv[2]);

 PDFName = InputPDFName;
 nSet = InputnSet;

 ApplGridHelper* grid;

 grid = new ApplGridHelper();
 grid->openFile("save.root");

 grid->InitialPDF(PDFName, 0);

 grid->InitialGrid(GridName_ATLAS7TeV_pT);
 grid->InitialGrid(GridName_ATLAS7TeV_pT_Y1);
 grid->InitialGrid(GridName_ATLAS7TeV_pT_Y2);
 grid->InitialGrid(GridName_ATLAS7TeV_pT_Y3);
 grid->InitialGrid(GridName_ATLAS8TeV_pT);
 grid->InitialGrid(GridName_ATLAS8TeV_pT_Y1);
 grid->InitialGrid(GridName_ATLAS8TeV_pT_Y2);
 grid->InitialGrid(GridName_ATLAS8TeV_pT_Y3);
 grid->InitialGrid(GridName_ATLAS8TeV_pT_Y4);
 grid->InitialGrid(GridName_ATLAS8TeV_pT_Y5);
 grid->InitialGrid(GridName_ATLAS8TeV_pT_Y6);
 grid->InitialGrid(GridName_ATLAS13TeV_pT);
 grid->InitialGrid(GridName_CMS7TeV_pT);
 grid->InitialGrid(GridName_CMS8TeV_pT);
 grid->InitialGrid(GridName_CMS13TeV_pT);
 grid->InitialGrid(GridName_CMS13TeV_pT_Y1);
 grid->InitialGrid(GridName_CMS13TeV_pT_Y2);
 grid->InitialGrid(GridName_CMS13TeV_pT_Y3);
 grid->InitialGrid(GridName_CMS13TeV_pT_Y4);
 grid->InitialGrid(GridName_CMS13TeV_pT_Y5);
 grid->InitialGrid(GridName_LHCb13TeV_pT);

 grid->ReadKFactor(KFactorDIR + "/KFactor_ATLAS7TeV_pT.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_ATLAS7TeV_pT_Y1.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_ATLAS7TeV_pT_Y2.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_ATLAS7TeV_pT_Y3.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_ATLAS8TeV_pT.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y1.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y2.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y3.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y4.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y5.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_ATLAS8TeV_pT_Y6.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_ATLAS13TeV_pT.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_CMS7TeV_pT.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_CMS8TeV_pT.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_CMS13TeV_pT.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_CMS13TeV_pT_Y1.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_CMS13TeV_pT_Y2.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_CMS13TeV_pT_Y3.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_CMS13TeV_pT_Y4.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_CMS13TeV_pT_Y5.txt");
 grid->ReadKFactor(KFactorDIR + "/KFactor_LHCb13TeV_pT.txt");

 ApplConvolute(grid);

 grid->SaveFile();

 return 1;
}

