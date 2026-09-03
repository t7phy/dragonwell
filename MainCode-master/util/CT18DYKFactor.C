#include "Tools/Tools.h"
#include "ReadInRoot/MCFMWWBoost.h"
#include "Calculation/ApplGridHelper.h"

int main(int argc, char** argv)
{
 if(argc != 1){
   cout<<"usage: ./CT18DYKFactor"<<endl;
   return 0;
 }

 TString ResultDIR = "Result2024.3.20";

 TString ATLAS7TeV_pT_NLO_Name =    "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS7TeV_pT_NLO.txt";
 TString ATLAS7TeV_pT_Y1_NLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS7TeV_pT_Y1_NLO.txt";
 TString ATLAS7TeV_pT_Y2_NLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS7TeV_pT_Y2_NLO.txt";
 TString ATLAS7TeV_pT_Y3_NLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS7TeV_pT_Y3_NLO.txt";
 TString ATLAS8TeV_pT_NLO_Name =    "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_NLO.txt";
 TString ATLAS8TeV_pT_Y1_NLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_Y1_NLO.txt";
 TString ATLAS8TeV_pT_Y2_NLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_Y2_NLO.txt";
 TString ATLAS8TeV_pT_Y3_NLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_Y3_NLO.txt";
 TString ATLAS8TeV_pT_Y4_NLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_Y4_NLO.txt";
 TString ATLAS8TeV_pT_Y5_NLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_Y5_NLO.txt";
 TString ATLAS8TeV_pT_Y6_NLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_Y6_NLO.txt";
 TString ATLAS13TeV_pT_NLO_Name =   "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS13TeV_pT_NLO.txt";
 TString CMS7TeV_pT_NLO_Name =      "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS7TeV_pT_NLO.txt";
 TString CMS8TeV_pT_NLO_Name =      "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS8TeV_pT_NLO.txt";
 TString CMS13TeV_pT_NLO_Name =     "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS13TeV_pT_NLO.txt";
 TString CMS13TeV_pT_Y1_NLO_Name =  "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS13TeV_pT_Y1_NLO.txt";
 TString CMS13TeV_pT_Y2_NLO_Name =  "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS13TeV_pT_Y2_NLO.txt";
 TString CMS13TeV_pT_Y3_NLO_Name =  "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS13TeV_pT_Y3_NLO.txt";
 TString CMS13TeV_pT_Y4_NLO_Name =  "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS13TeV_pT_Y4_NLO.txt";
 TString CMS13TeV_pT_Y5_NLO_Name =  "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS13TeV_pT_Y5_NLO.txt";
 TString LHCb13TeV_pT_NLO_Name =    "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/LHCb13TeV_pT_NLO.txt";

 TString ATLAS7TeV_pT_NNLO_Name =    "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS7TeV_pT_NNLO.txt";
 TString ATLAS7TeV_pT_Y1_NNLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS7TeV_pT_Y1_NNLO.txt";
 TString ATLAS7TeV_pT_Y2_NNLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS7TeV_pT_Y2_NNLO.txt";
 TString ATLAS7TeV_pT_Y3_NNLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS7TeV_pT_Y3_NNLO.txt";
 TString ATLAS8TeV_pT_NNLO_Name =    "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_NNLO.txt";
 TString ATLAS8TeV_pT_Y1_NNLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_Y1_NNLO.txt";
 TString ATLAS8TeV_pT_Y2_NNLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_Y2_NNLO.txt";
 TString ATLAS8TeV_pT_Y3_NNLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_Y3_NNLO.txt";
 TString ATLAS8TeV_pT_Y4_NNLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_Y4_NNLO.txt";
 TString ATLAS8TeV_pT_Y5_NNLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_Y5_NNLO.txt";
 TString ATLAS8TeV_pT_Y6_NNLO_Name = "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS8TeV_pT_Y6_NNLO.txt";
 TString ATLAS13TeV_pT_NNLO_Name =   "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/ATLAS13TeV_pT_NNLO.txt";
 TString CMS7TeV_pT_NNLO_Name =      "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS7TeV_pT_NNLO.txt";
 TString CMS8TeV_pT_NNLO_Name =      "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS8TeV_pT_NNLO.txt";
 TString CMS13TeV_pT_NNLO_Name =     "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS13TeV_pT_NNLO.txt";
 TString CMS13TeV_pT_Y1_NNLO_Name =  "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS13TeV_pT_Y1_NNLO.txt";
 TString CMS13TeV_pT_Y2_NNLO_Name =  "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS13TeV_pT_Y2_NNLO.txt";
 TString CMS13TeV_pT_Y3_NNLO_Name =  "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS13TeV_pT_Y3_NNLO.txt";
 TString CMS13TeV_pT_Y4_NNLO_Name =  "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS13TeV_pT_Y4_NNLO.txt";
 TString CMS13TeV_pT_Y5_NNLO_Name =  "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/CMS13TeV_pT_Y5_NNLO.txt";
 TString LHCb13TeV_pT_NNLO_Name =    "/ustcfs2/yfu/MainCode/run/CT18DYRes/" + ResultDIR + "/LHCb13TeV_pT_NNLO.txt";

 int ATLAS7TeVZPtBin = 26;
 double ATLAS7TeVZPtBinning[27] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 22.0, 26.0, 30.0, 34.0, 38.0, 42.0, 46.0,
                             50.0, 54.0, 60.0, 70.0, 80.0, 100.0, 150.0, 200.0, 300.0, 800.0};

 int ATLAS8TeVZPtBin2 = 20;
 double ATLAS8TeVZPtBinning2[21] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 13.0, 16.0, 20.0, 25.0, 30.0, 37.0, 45.0, 55.0, 65.0, 75.0, 85.0,
                                105.0, 150.0, 200.0, 900.0};

 int ATLAS8TeVZPtBin3 = 43;
 double ATLAS8TeVZPtBinning3[44] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.5, 25.0, 27.5, 30.0, 33.0,
                                 36.0, 39.0, 42.0, 45.0, 48.0, 51.0, 54.0, 57.0, 61.0, 65.0, 70.0, 75.0, 80.0, 85.0, 95.0, 105.0,
                                 125.0, 150.0, 175.0, 200.0, 250.0, 300.0, 350.0, 400.0, 470.0, 550.0, 650.0, 900.0};

 int ATLAS13TeVZPtBin = 43;
 double ATLAS13TeVZPtBinning[44] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.5, 25.0, 27.5, 30.0, 33.0,
                                 36.0, 39.0, 42.0, 45.0, 48.0, 51.0, 54.0, 57.0, 61.0, 65.0, 70.0, 75.0, 80.0, 85.0, 95.0, 105.0,
                                 125.0, 150.0, 175.0, 200.0, 250.0, 300.0, 350.0, 400.0, 470.0, 550.0, 650.0, 900.0};

 int CMS7TeVZPtBin = 18;
 double CMS7TeVZPtBinning[19] = {0.0, 2.5, 5.0, 7.5, 10.0, 12.5, 15.0, 17.5, 20.0, 30.0, 40.0, 50.0, 70.0, 90.0, 110.0, 150.0, 190.0, 250.0, 600.0};

 int CMS8TeVZPtBin = 18;
 double CMS8TeVZPtBinning[19] = {0.0, 2.5, 5.0, 7.5, 10.0, 12.5, 15.0, 17.5, 20.0, 30.0, 40.0, 50.0, 70.0, 90.0, 110.0, 150.0, 190.0, 250.0, 600.0};

 int CMS13TeVZPtBin = 35;
 double CMS13TeVZPtBinning[36] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 16.0, 18.0, 20.0, 22.0,
                               25.0, 28.0, 32.0, 37.0, 43.0, 52.0, 65.0, 85.0, 120.0, 160.0, 190.0, 220.0, 250.0, 300.0, 400.0, 500.0,
                               800.0, 1500.0};

 int CMS13TeVZPtBin1 = 33;
 double CMS13TeVZPtBinning1[34] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 16.0, 18.0, 20.0, 22.0,
                               25.0, 28.0, 32.0, 37.0, 43.0, 52.0, 65.0, 85.0, 120.0, 160.0, 190.0, 220.0, 250.0, 300.0, 400.0, 1500.0};

 int LHCb13TeVZPtBin = 14;
 double LHCb13TeVZPtBinning[15] = {0.0, 2.2, 3.4, 4.6, 5.8, 7.2, 8.7, 10.5, 12.8, 15.4, 19.0, 24.5, 34.0, 63.0, 270.0};

 TFile* file = new TFile("KFactor.root", "RECREATE");
 file->cd();

 TH1D* ATLAS7TeV_pT_NLO = new TH1D("ATLAS7TeV_pT_NLO", "ATLAS7TeV_pT_NLO", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);
 TH1D* ATLAS7TeV_pT_NNLO = new TH1D("ATLAS7TeV_pT_NNLO", "ATLAS7TeV_pT_NNLO", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);
 TH1D* ATLAS7TeV_pT_KFactor = new TH1D("ATLAS7TeV_pT_KFactor", "ATLAS7TeV_pT_KFactor", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);

 TH1D* ATLAS7TeV_pT_Y1_NLO = new TH1D("ATLAS7TeV_pT_Y1_NLO", "ATLAS7TeV_pT_Y1_NLO", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);
 TH1D* ATLAS7TeV_pT_Y1_NNLO = new TH1D("ATLAS7TeV_pT_Y1_NNLO", "ATLAS7TeV_pT_Y1_NNLO", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);
 TH1D* ATLAS7TeV_pT_Y1_KFactor = new TH1D("ATLAS7TeV_pT_Y1_KFactor", "ATLAS7TeV_pT_Y1_KFactor", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);

 TH1D* ATLAS7TeV_pT_Y2_NLO = new TH1D("ATLAS7TeV_pT_Y2_NLO", "ATLAS7TeV_pT_Y2_NLO", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);
 TH1D* ATLAS7TeV_pT_Y2_NNLO = new TH1D("ATLAS7TeV_pT_Y2_NNLO", "ATLAS7TeV_pT_Y2_NNLO", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);
 TH1D* ATLAS7TeV_pT_Y2_KFactor = new TH1D("ATLAS7TeV_pT_Y2_KFactor", "ATLAS7TeV_pT_Y2_KFactor", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);

 TH1D* ATLAS7TeV_pT_Y3_NLO = new TH1D("ATLAS7TeV_pT_Y3_NLO", "ATLAS7TeV_pT_Y3_NLO", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);
 TH1D* ATLAS7TeV_pT_Y3_NNLO = new TH1D("ATLAS7TeV_pT_Y3_NNLO", "ATLAS7TeV_pT_Y3_NNLO", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);
 TH1D* ATLAS7TeV_pT_Y3_KFactor = new TH1D("ATLAS7TeV_pT_Y3_KFactor", "ATLAS7TeV_pT_Y3_KFactor", ATLAS7TeVZPtBin, ATLAS7TeVZPtBinning);

 TH1D* ATLAS8TeV_pT_NLO = new TH1D("ATLAS8TeV_pT_NLO", "ATLAS8TeV_pT_NLO", ATLAS8TeVZPtBin3, ATLAS8TeVZPtBinning3);
 TH1D* ATLAS8TeV_pT_NNLO = new TH1D("ATLAS8TeV_pT_NNLO", "ATLAS8TeV_pT_NNLO", ATLAS8TeVZPtBin3, ATLAS8TeVZPtBinning3);
 TH1D* ATLAS8TeV_pT_KFactor = new TH1D("ATLAS8TeV_pT_KFactor", "ATLAS8TeV_pT_KFactor", ATLAS8TeVZPtBin3, ATLAS8TeVZPtBinning3);

 TH1D* ATLAS8TeV_pT_Y1_NLO = new TH1D("ATLAS8TeV_pT_Y1_NLO", "ATLAS8TeV_pT_Y1_NLO", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 TH1D* ATLAS8TeV_pT_Y1_NNLO = new TH1D("ATLAS8TeV_pT_Y1_NNLO", "ATLAS8TeV_pT_Y1_NNLO", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 TH1D* ATLAS8TeV_pT_Y1_KFactor = new TH1D("ATLAS8TeV_pT_Y1_KFactor", "ATLAS8TeV_pT_Y1_KFactor", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);

 TH1D* ATLAS8TeV_pT_Y2_NLO = new TH1D("ATLAS8TeV_pT_Y2_NLO", "ATLAS8TeV_pT_Y2_NLO", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 TH1D* ATLAS8TeV_pT_Y2_NNLO = new TH1D("ATLAS8TeV_pT_Y2_NNLO", "ATLAS8TeV_pT_Y2_NNLO", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 TH1D* ATLAS8TeV_pT_Y2_KFactor = new TH1D("ATLAS8TeV_pT_Y2_KFactor", "ATLAS8TeV_pT_Y2_KFactor", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);

 TH1D* ATLAS8TeV_pT_Y3_NLO = new TH1D("ATLAS8TeV_pT_Y3_NLO", "ATLAS8TeV_pT_Y3_NLO", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 TH1D* ATLAS8TeV_pT_Y3_NNLO = new TH1D("ATLAS8TeV_pT_Y3_NNLO", "ATLAS8TeV_pT_Y3_NNLO", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 TH1D* ATLAS8TeV_pT_Y3_KFactor = new TH1D("ATLAS8TeV_pT_Y3_KFactor", "ATLAS8TeV_pT_Y3_KFactor", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);

 TH1D* ATLAS8TeV_pT_Y4_NLO = new TH1D("ATLAS8TeV_pT_Y4_NLO", "ATLAS8TeV_pT_Y4_NLO", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 TH1D* ATLAS8TeV_pT_Y4_NNLO = new TH1D("ATLAS8TeV_pT_Y4_NNLO", "ATLAS8TeV_pT_Y4_NNLO", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 TH1D* ATLAS8TeV_pT_Y4_KFactor = new TH1D("ATLAS8TeV_pT_Y4_KFactor", "ATLAS8TeV_pT_Y4_KFactor", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);

 TH1D* ATLAS8TeV_pT_Y5_NLO = new TH1D("ATLAS8TeV_pT_Y5_NLO", "ATLAS8TeV_pT_Y5_NLO", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 TH1D* ATLAS8TeV_pT_Y5_NNLO = new TH1D("ATLAS8TeV_pT_Y5_NNLO", "ATLAS8TeV_pT_Y5_NNLO", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 TH1D* ATLAS8TeV_pT_Y5_KFactor = new TH1D("ATLAS8TeV_pT_Y5_KFactor", "ATLAS8TeV_pT_Y5_KFactor", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);

 TH1D* ATLAS8TeV_pT_Y6_NLO = new TH1D("ATLAS8TeV_pT_Y6_NLO", "ATLAS8TeV_pT_Y6_NLO", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 TH1D* ATLAS8TeV_pT_Y6_NNLO = new TH1D("ATLAS8TeV_pT_Y6_NNLO", "ATLAS8TeV_pT_Y6_NNLO", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);
 TH1D* ATLAS8TeV_pT_Y6_KFactor = new TH1D("ATLAS8TeV_pT_Y6_KFactor", "ATLAS8TeV_pT_Y6_KFactor", ATLAS8TeVZPtBin2, ATLAS8TeVZPtBinning2);

 TH1D* ATLAS13TeV_pT_NLO = new TH1D("ATLAS13TeV_pT_NLO", "ATLAS13TeV_pT_NLO", ATLAS13TeVZPtBin, ATLAS13TeVZPtBinning);
 TH1D* ATLAS13TeV_pT_NNLO = new TH1D("ATLAS13TeV_pT_NNLO", "ATLAS13TeV_pT_NNLO", ATLAS13TeVZPtBin, ATLAS13TeVZPtBinning);
 TH1D* ATLAS13TeV_pT_KFactor = new TH1D("ATLAS13TeV_pT_KFactor", "ATLAS13TeV_pT_KFactor", ATLAS13TeVZPtBin, ATLAS13TeVZPtBinning);

 TH1D* CMS7TeV_pT_NLO = new TH1D("CMS7TeV_pT_NLO", "CMS7TeV_pT_NLO", CMS7TeVZPtBin, CMS7TeVZPtBinning);
 TH1D* CMS7TeV_pT_NNLO = new TH1D("CMS7TeV_pT_NNLO", "CMS7TeV_pT_NNLO", CMS7TeVZPtBin, CMS7TeVZPtBinning);
 TH1D* CMS7TeV_pT_KFactor = new TH1D("CMS7TeV_pT_KFactor", "CMS7TeV_pT_KFactor", CMS7TeVZPtBin, CMS7TeVZPtBinning);

 TH1D* CMS8TeV_pT_NLO = new TH1D("CMS8TeV_pT_NLO", "CMS8TeV_pT_NLO", CMS8TeVZPtBin, CMS8TeVZPtBinning);
 TH1D* CMS8TeV_pT_NNLO = new TH1D("CMS8TeV_pT_NNLO", "CMS8TeV_pT_NNLO", CMS8TeVZPtBin, CMS8TeVZPtBinning);
 TH1D* CMS8TeV_pT_KFactor = new TH1D("CMS8TeV_pT_KFactor", "CMS8TeV_pT_KFactor", CMS8TeVZPtBin, CMS8TeVZPtBinning);

 TH1D* CMS13TeV_pT_NLO = new TH1D("CMS13TeV_pT_NLO", "CMS13TeV_pT_NLO", CMS13TeVZPtBin, CMS13TeVZPtBinning);
 TH1D* CMS13TeV_pT_NNLO = new TH1D("CMS13TeV_pT_NNLO", "CMS13TeV_pT_NNLO", CMS13TeVZPtBin, CMS13TeVZPtBinning);
 TH1D* CMS13TeV_pT_KFactor = new TH1D("CMS13TeV_pT_KFactor", "CMS13TeV_pT_KFactor", CMS13TeVZPtBin, CMS13TeVZPtBinning);

 TH1D* CMS13TeV_pT_Y1_NLO = new TH1D("CMS13TeV_pT_Y1_NLO", "CMS13TeV_pT_Y1_NLO", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 TH1D* CMS13TeV_pT_Y1_NNLO = new TH1D("CMS13TeV_pT_Y1_NNLO", "CMS13TeV_pT_Y1_NNLO", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 TH1D* CMS13TeV_pT_Y1_KFactor = new TH1D("CMS13TeV_pT_Y1_KFactor", "CMS13TeV_pT_Y1_KFactor", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);

 TH1D* CMS13TeV_pT_Y2_NLO = new TH1D("CMS13TeV_pT_Y2_NLO", "CMS13TeV_pT_Y2_NLO", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 TH1D* CMS13TeV_pT_Y2_NNLO = new TH1D("CMS13TeV_pT_Y2_NNLO", "CMS13TeV_pT_Y2_NNLO", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 TH1D* CMS13TeV_pT_Y2_KFactor = new TH1D("CMS13TeV_pT_Y2_KFactor", "CMS13TeV_pT_Y2_KFactor", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);

 TH1D* CMS13TeV_pT_Y3_NLO = new TH1D("CMS13TeV_pT_Y3_NLO", "CMS13TeV_pT_Y3_NLO", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 TH1D* CMS13TeV_pT_Y3_NNLO = new TH1D("CMS13TeV_pT_Y3_NNLO", "CMS13TeV_pT_Y3_NNLO", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 TH1D* CMS13TeV_pT_Y3_KFactor = new TH1D("CMS13TeV_pT_Y3_KFactor", "CMS13TeV_pT_Y3_KFactor", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);

 TH1D* CMS13TeV_pT_Y4_NLO = new TH1D("CMS13TeV_pT_Y4_NLO", "CMS13TeV_pT_Y4_NLO", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 TH1D* CMS13TeV_pT_Y4_NNLO = new TH1D("CMS13TeV_pT_Y4_NNLO", "CMS13TeV_pT_Y4_NNLO", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 TH1D* CMS13TeV_pT_Y4_KFactor = new TH1D("CMS13TeV_pT_Y4_KFactor", "CMS13TeV_pT_Y4_KFactor", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);

 TH1D* CMS13TeV_pT_Y5_NLO = new TH1D("CMS13TeV_pT_Y5_NLO", "CMS13TeV_pT_Y5_NLO", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 TH1D* CMS13TeV_pT_Y5_NNLO = new TH1D("CMS13TeV_pT_Y5_NNLO", "CMS13TeV_pT_Y5_NNLO", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);
 TH1D* CMS13TeV_pT_Y5_KFactor = new TH1D("CMS13TeV_pT_Y5_KFactor", "CMS13TeV_pT_Y5_KFactor", CMS13TeVZPtBin1, CMS13TeVZPtBinning1);

 TH1D* LHCb13TeV_pT_NLO = new TH1D("LHCb13TeV_pT_NLO", "LHCb13TeV_pT_NLO", LHCb13TeVZPtBin, LHCb13TeVZPtBinning);
 TH1D* LHCb13TeV_pT_NNLO = new TH1D("LHCb13TeV_pT_NNLO", "LHCb13TeV_pT_NNLO", LHCb13TeVZPtBin, LHCb13TeVZPtBinning);
 TH1D* LHCb13TeV_pT_KFactor = new TH1D("LHCb13TeV_pT_KFactor", "LHCb13TeV_pT_KFactor", LHCb13TeVZPtBin, LHCb13TeVZPtBinning);


 MCFMWWBoost* Run = new MCFMWWBoost();

 Run->ReadInMCFM_10_3(ATLAS7TeV_pT_NLO_Name, ATLAS7TeV_pT_NLO, 10);
 Run->ReadInMCFM_10_3(ATLAS7TeV_pT_NNLO_Name, ATLAS7TeV_pT_NNLO, 10);
 DivideHist(ATLAS7TeV_pT_NNLO, ATLAS7TeV_pT_NLO, ATLAS7TeV_pT_KFactor);

 Run->ReadInMCFM_10_3(ATLAS7TeV_pT_Y1_NLO_Name, ATLAS7TeV_pT_Y1_NLO, 10);
 Run->ReadInMCFM_10_3(ATLAS7TeV_pT_Y1_NNLO_Name, ATLAS7TeV_pT_Y1_NNLO, 10);
 DivideHist(ATLAS7TeV_pT_Y1_NNLO, ATLAS7TeV_pT_Y1_NLO, ATLAS7TeV_pT_Y1_KFactor);

 Run->ReadInMCFM_10_3(ATLAS7TeV_pT_Y2_NLO_Name, ATLAS7TeV_pT_Y2_NLO, 10);
 Run->ReadInMCFM_10_3(ATLAS7TeV_pT_Y2_NNLO_Name, ATLAS7TeV_pT_Y2_NNLO, 10);
 DivideHist(ATLAS7TeV_pT_Y2_NNLO, ATLAS7TeV_pT_Y2_NLO, ATLAS7TeV_pT_Y2_KFactor);

 Run->ReadInMCFM_10_3(ATLAS7TeV_pT_Y3_NLO_Name, ATLAS7TeV_pT_Y3_NLO, 10);
 Run->ReadInMCFM_10_3(ATLAS7TeV_pT_Y3_NNLO_Name, ATLAS7TeV_pT_Y3_NNLO, 10);
 DivideHist(ATLAS7TeV_pT_Y3_NNLO, ATLAS7TeV_pT_Y3_NLO, ATLAS7TeV_pT_Y3_KFactor);

 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_NLO_Name, ATLAS8TeV_pT_NLO, 10);
 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_NNLO_Name, ATLAS8TeV_pT_NNLO, 10);
 DivideHist(ATLAS8TeV_pT_NNLO, ATLAS8TeV_pT_NLO, ATLAS8TeV_pT_KFactor);

 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_Y1_NLO_Name, ATLAS8TeV_pT_Y1_NLO, 8);
 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_Y1_NNLO_Name, ATLAS8TeV_pT_Y1_NNLO, 8);
 DivideHist(ATLAS8TeV_pT_Y1_NNLO, ATLAS8TeV_pT_Y1_NLO, ATLAS8TeV_pT_Y1_KFactor);

 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_Y2_NLO_Name, ATLAS8TeV_pT_Y2_NLO, 8);
 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_Y2_NNLO_Name, ATLAS8TeV_pT_Y2_NNLO, 8);
 DivideHist(ATLAS8TeV_pT_Y2_NNLO, ATLAS8TeV_pT_Y2_NLO, ATLAS8TeV_pT_Y2_KFactor);

 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_Y3_NLO_Name, ATLAS8TeV_pT_Y3_NLO, 8);
 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_Y3_NNLO_Name, ATLAS8TeV_pT_Y3_NNLO, 8);
 DivideHist(ATLAS8TeV_pT_Y3_NNLO, ATLAS8TeV_pT_Y3_NLO, ATLAS8TeV_pT_Y3_KFactor);

 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_Y4_NLO_Name, ATLAS8TeV_pT_Y4_NLO, 8);
 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_Y4_NNLO_Name, ATLAS8TeV_pT_Y4_NNLO, 8);
 DivideHist(ATLAS8TeV_pT_Y4_NNLO, ATLAS8TeV_pT_Y4_NLO, ATLAS8TeV_pT_Y4_KFactor);

 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_Y5_NLO_Name, ATLAS8TeV_pT_Y5_NLO, 8);
 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_Y5_NNLO_Name, ATLAS8TeV_pT_Y5_NNLO, 8);
 DivideHist(ATLAS8TeV_pT_Y5_NNLO, ATLAS8TeV_pT_Y5_NLO, ATLAS8TeV_pT_Y5_KFactor);

 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_Y6_NLO_Name, ATLAS8TeV_pT_Y6_NLO, 8);
 Run->ReadInMCFM_10_3(ATLAS8TeV_pT_Y6_NNLO_Name, ATLAS8TeV_pT_Y6_NNLO, 8);
 DivideHist(ATLAS8TeV_pT_Y6_NNLO, ATLAS8TeV_pT_Y6_NLO, ATLAS8TeV_pT_Y6_KFactor);

 Run->ReadInMCFM_10_3(ATLAS13TeV_pT_NLO_Name, ATLAS13TeV_pT_NLO, 10);
 Run->ReadInMCFM_10_3(ATLAS13TeV_pT_NNLO_Name, ATLAS13TeV_pT_NNLO, 10);
 DivideHist(ATLAS13TeV_pT_NNLO, ATLAS13TeV_pT_NLO, ATLAS13TeV_pT_KFactor);

 Run->ReadInMCFM_10_3(CMS7TeV_pT_NLO_Name, CMS7TeV_pT_NLO, 8);
 Run->ReadInMCFM_10_3(CMS7TeV_pT_NNLO_Name, CMS7TeV_pT_NNLO, 8);
 DivideHist(CMS7TeV_pT_NNLO, CMS7TeV_pT_NLO, CMS7TeV_pT_KFactor);

 Run->ReadInMCFM_10_3(CMS8TeV_pT_NLO_Name, CMS8TeV_pT_NLO, 8);
 Run->ReadInMCFM_10_3(CMS8TeV_pT_NNLO_Name, CMS8TeV_pT_NNLO, 8);
 DivideHist(CMS8TeV_pT_NNLO, CMS8TeV_pT_NLO, CMS8TeV_pT_KFactor);

 Run->ReadInMCFM_10_3(CMS13TeV_pT_NLO_Name, CMS13TeV_pT_NLO, 16);
 Run->ReadInMCFM_10_3(CMS13TeV_pT_NNLO_Name, CMS13TeV_pT_NNLO, 16);
 DivideHist(CMS13TeV_pT_NNLO, CMS13TeV_pT_NLO, CMS13TeV_pT_KFactor);

 Run->ReadInMCFM_10_3(CMS13TeV_pT_Y1_NLO_Name, CMS13TeV_pT_Y1_NLO, 16);
 Run->ReadInMCFM_10_3(CMS13TeV_pT_Y1_NNLO_Name, CMS13TeV_pT_Y1_NNLO, 16);
 DivideHist(CMS13TeV_pT_Y1_NNLO, CMS13TeV_pT_Y1_NLO, CMS13TeV_pT_Y1_KFactor);

 Run->ReadInMCFM_10_3(CMS13TeV_pT_Y2_NLO_Name, CMS13TeV_pT_Y2_NLO, 16);
 Run->ReadInMCFM_10_3(CMS13TeV_pT_Y2_NNLO_Name, CMS13TeV_pT_Y2_NNLO, 16);
 DivideHist(CMS13TeV_pT_Y2_NNLO, CMS13TeV_pT_Y2_NLO, CMS13TeV_pT_Y2_KFactor);

 Run->ReadInMCFM_10_3(CMS13TeV_pT_Y3_NLO_Name, CMS13TeV_pT_Y3_NLO, 16);
 Run->ReadInMCFM_10_3(CMS13TeV_pT_Y3_NNLO_Name, CMS13TeV_pT_Y3_NNLO, 16);
 DivideHist(CMS13TeV_pT_Y3_NNLO, CMS13TeV_pT_Y3_NLO, CMS13TeV_pT_Y3_KFactor);

 Run->ReadInMCFM_10_3(CMS13TeV_pT_Y4_NLO_Name, CMS13TeV_pT_Y4_NLO, 16);
 Run->ReadInMCFM_10_3(CMS13TeV_pT_Y4_NNLO_Name, CMS13TeV_pT_Y4_NNLO, 16);
 DivideHist(CMS13TeV_pT_Y4_NNLO, CMS13TeV_pT_Y4_NLO, CMS13TeV_pT_Y4_KFactor);

 Run->ReadInMCFM_10_3(CMS13TeV_pT_Y5_NLO_Name, CMS13TeV_pT_Y5_NLO, 16);
 Run->ReadInMCFM_10_3(CMS13TeV_pT_Y5_NNLO_Name, CMS13TeV_pT_Y5_NNLO, 16);
 DivideHist(CMS13TeV_pT_Y5_NNLO, CMS13TeV_pT_Y5_NLO, CMS13TeV_pT_Y5_KFactor);

 Run->ReadInMCFM_10_3(LHCb13TeV_pT_NLO_Name, LHCb13TeV_pT_NLO, 10);
 Run->ReadInMCFM_10_3(LHCb13TeV_pT_NNLO_Name, LHCb13TeV_pT_NNLO, 10);
 DivideHist(LHCb13TeV_pT_NNLO, LHCb13TeV_pT_NLO, LHCb13TeV_pT_KFactor);


 ApplGridHelper* kfactor = new ApplGridHelper();
 kfactor->GenerateKFactor("KFactor_ATLAS7TeV_pT.txt", ATLAS7TeV_pT_KFactor);
 kfactor->GenerateKFactor("KFactor_ATLAS7TeV_pT_Y1.txt", ATLAS7TeV_pT_Y1_KFactor);
 kfactor->GenerateKFactor("KFactor_ATLAS7TeV_pT_Y2.txt", ATLAS7TeV_pT_Y2_KFactor);
 kfactor->GenerateKFactor("KFactor_ATLAS7TeV_pT_Y3.txt", ATLAS7TeV_pT_Y3_KFactor);
 kfactor->GenerateKFactor("KFactor_ATLAS8TeV_pT.txt", ATLAS8TeV_pT_KFactor);
 kfactor->GenerateKFactor("KFactor_ATLAS8TeV_pT_Y1.txt", ATLAS8TeV_pT_Y1_KFactor);
 kfactor->GenerateKFactor("KFactor_ATLAS8TeV_pT_Y2.txt", ATLAS8TeV_pT_Y2_KFactor);
 kfactor->GenerateKFactor("KFactor_ATLAS8TeV_pT_Y3.txt", ATLAS8TeV_pT_Y3_KFactor);
 kfactor->GenerateKFactor("KFactor_ATLAS8TeV_pT_Y4.txt", ATLAS8TeV_pT_Y4_KFactor);
 kfactor->GenerateKFactor("KFactor_ATLAS8TeV_pT_Y5.txt", ATLAS8TeV_pT_Y5_KFactor);
 kfactor->GenerateKFactor("KFactor_ATLAS8TeV_pT_Y6.txt", ATLAS8TeV_pT_Y6_KFactor);
 kfactor->GenerateKFactor("KFactor_ATLAS13TeV_pT.txt", ATLAS13TeV_pT_KFactor);
 kfactor->GenerateKFactor("KFactor_CMS7TeV_pT.txt", CMS7TeV_pT_KFactor);
 kfactor->GenerateKFactor("KFactor_CMS8TeV_pT.txt", CMS8TeV_pT_KFactor);
 kfactor->GenerateKFactor("KFactor_CMS13TeV_pT.txt", CMS13TeV_pT_KFactor);
 kfactor->GenerateKFactor("KFactor_CMS13TeV_pT_Y1.txt", CMS13TeV_pT_Y1_KFactor);
 kfactor->GenerateKFactor("KFactor_CMS13TeV_pT_Y2.txt", CMS13TeV_pT_Y2_KFactor);
 kfactor->GenerateKFactor("KFactor_CMS13TeV_pT_Y3.txt", CMS13TeV_pT_Y3_KFactor);
 kfactor->GenerateKFactor("KFactor_CMS13TeV_pT_Y4.txt", CMS13TeV_pT_Y4_KFactor);
 kfactor->GenerateKFactor("KFactor_CMS13TeV_pT_Y5.txt", CMS13TeV_pT_Y5_KFactor);
 kfactor->GenerateKFactor("KFactor_LHCb13TeV_pT.txt", LHCb13TeV_pT_KFactor);

 file->Write();
 file->Close();
// myhists->saveHists();

 return 1;
}
