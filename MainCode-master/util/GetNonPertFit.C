#include <iostream>
#include "RootCommon.h"
#include "ReadInRoot/ResBosNonPertFit.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "Analysis/HistsResBos.h"
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 1){
   cout<<"usage: ./GetNonPertFit"<<endl;
   return 0;
 }

 ResBosNonPertFit* Run_ATLAS = new ResBosNonPertFit();
 ResBosNonPertFit* Run_D01 = new ResBosNonPertFit();
 ResBosNonPertFit* Run_D02 = new ResBosNonPertFit();
 ResBosNonPertFit* Run_CDF1 = new ResBosNonPertFit();
 ResBosNonPertFit* Run_CDF2 = new ResBosNonPertFit();
 ResBosNonPertFit* Run_R209 = new ResBosNonPertFit();
 ResBosNonPertFit* Run_E605 = new ResBosNonPertFit();
 ResBosNonPertFit* Run_E288200 = new ResBosNonPertFit();
 ResBosNonPertFit* Run_E288300 = new ResBosNonPertFit();
 ResBosNonPertFit* Run_E288400 = new ResBosNonPertFit();

 HistsResBos* myhists = new HistsResBos();
 myhists->openFile("save.root");

 Run_ATLAS->LinkHist(myhists);
 Run_D01->LinkHist(myhists);
 Run_D02->LinkHist(myhists);
 Run_CDF1->LinkHist(myhists);
 Run_CDF2->LinkHist(myhists);
 Run_R209->LinkHist(myhists);
 Run_E605->LinkHist(myhists);
 Run_E288200->LinkHist(myhists);
 Run_E288300->LinkHist(myhists);
 Run_E288400->LinkHist(myhists);

 int D01Bin = 15;
 double D01Binning[16] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0};

 int D02Bin = 8;
 double D02Binning[9] = {0.0, 2.2, 5.8, 6.8, 9.6, 13.0, 14.4, 18.0, 19.4};

 int CDF1Bin = 32;
 double CDF1Binning[33] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 
                          10.0, 10.5, 11.0, 11.5, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};

 int CDF2Bin = 41;
 double CDF2Binning[42] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 
                          10.0, 10.5, 11.0, 11.5, 12.0, 12.5, 13.0, 13.5, 14.0, 14.5, 15.0, 15.5, 16.0, 16.5, 17.0, 17.5, 18.0, 18.5, 19.0, 19.5, 20.0, 20.5};

 int E288200Bin = 7;
 double E288200Binning[8] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4};

 int R209Bin = 5;
 double R209Binning[6] = {0.0, 0.4, 0.8, 1.2, 1.6, 2.0};

 int ATLASBin = 8;
 double ATLASBinning[9] = {0.0, 2, 4, 6, 8, 10, 13, 16, 20};

 double rangeZPt[9] = {0.0, 2, 4, 6, 8, 10, 13, 16, 20};
 TH1D *ATLASy1 = new TH1D("ATLASy1", "ATLASy1", 8, rangeZPt);
 TH1D *ATLASy2 = new TH1D("ATLASy2", "ATLASy2", 8, rangeZPt);
 TH1D *ATLASy3 = new TH1D("ATLASy3", "ATLASy3", 8, rangeZPt);
 TH1D *ATLASy4 = new TH1D("ATLASy4", "ATLASy4", 8, rangeZPt);
 TH1D *ATLASy5 = new TH1D("ATLASy5", "ATLASy5", 8, rangeZPt);
 TH1D *ATLASy6 = new TH1D("ATLASy6", "ATLASy6", 8, rangeZPt);

 TH1D* D01Hist = new TH1D("D01", "D01", D01Bin, D01Binning);
 TH1D* D02Hist = new TH1D("D02", "D02", D02Bin, D02Binning);
 TH1D* CDF1Hist = new TH1D("CDF1", "CDF1", CDF1Bin, CDF1Binning);
 TH1D* CDF2Hist = new TH1D("CDF2", "CDF2", CDF2Bin, CDF2Binning);
 TH1D* E288200Hist = new TH1D("E288200", "E288200", E288200Bin, E288200Binning);
 TH1D* R209Hist = new TH1D("R209", "R209", R209Bin, R209Binning);
 TH1D* ATLASHist = new TH1D("ATLAS", "ATLAS", ATLASBin, ATLASBinning);

 TF1* Gaus = new TF1("Gaus", "gaus(0)", -3, 3);
 Gaus->SetParameter(0, 1.0 / sqrt(2.0 * TMath::Pi()));
 Gaus->SetParameter(1, 0.0);
 Gaus->SetParameter(2, 1.0);
 Gaus->Write();

 TH1D* ReducedChi2 = new TH1D("ReducedChi2", "ReducedChi2", 20, -3, 3);

 Run_ATLAS->openFile("ATLAS_Rapidity_results.dat");
// Run_ATLAS->GetBinning("ATLAS_Rapidity_results.dat");
 Run_ATLAS->CopyHist("ATLAS_Rapidity", ATLASHist, 6);
 Run_ATLAS->WriteIn();
 for(int iplot = 1; iplot <= Run_ATLAS->TotalPlot; iplot++){
   for(int ibin = 1; ibin <= Run_ATLAS->Nbin; ibin++){
     ReducedChi2->Fill(Run_ATLAS->ReducedChi2[iplot]->GetBinContent(ibin), 1.0);
   }
 }

 Run_ATLAS->Get2DPlot();

 Run_D01->openFile("D01_results.dat");
// Run_D01->GetBinning("D01_results.dat");
 Run_D01->CopyHist("D01", D01Hist, 1);
 Run_D01->WriteIn();
 for(int iplot = 1; iplot <= Run_D01->TotalPlot; iplot++){
   for(int ibin = 1; ibin <= Run_D01->Nbin; ibin++){
     ReducedChi2->Fill(Run_D01->ReducedChi2[iplot]->GetBinContent(ibin), 1.0);
   }
 }

 Run_D02->openFile("D02_results.dat");
// Run_D02->GetBinning("D02_results.dat");
 Run_D02->CopyHist("D02", D02Hist, 1);
 Run_D02->WriteIn();
 for(int iplot = 1; iplot <= Run_D02->TotalPlot; iplot++){
   for(int ibin = 1; ibin <= Run_D02->Nbin; ibin++){
     ReducedChi2->Fill(Run_D02->ReducedChi2[iplot]->GetBinContent(ibin), 1.0);
   }
 }

 Run_CDF1->openFile("CDF1_results.dat");
// Run_CDF1->GetBinning("CDF1_results.dat");
 Run_CDF1->CopyHist("CDF1", CDF1Hist, 1);
 Run_CDF1->WriteIn();
 for(int iplot = 1; iplot <= Run_CDF1->TotalPlot; iplot++){
   for(int ibin = 1; ibin <= Run_CDF1->Nbin; ibin++){
     ReducedChi2->Fill(Run_CDF1->ReducedChi2[iplot]->GetBinContent(ibin), 1.0);
   }
 }

 Run_CDF2->openFile("CDF2_results.dat");
// Run_CDF2->GetBinning("CDF2_results.dat");
 Run_CDF2->CopyHist("CDF2", CDF2Hist, 1);
 Run_CDF2->WriteIn();
 for(int iplot = 1; iplot <= Run_CDF2->TotalPlot; iplot++){
   for(int ibin = 1; ibin <= Run_CDF2->Nbin; ibin++){
     ReducedChi2->Fill(Run_CDF2->ReducedChi2[iplot]->GetBinContent(ibin), 1.0);
   }
 }

 Run_R209->openFile("R209_results.dat");
// Run_R209->GetBinning("R209_results.dat");
 Run_R209->CopyHist("R209", R209Hist, 2);
 Run_R209->WriteIn();
 for(int iplot = 1; iplot <= Run_R209->TotalPlot; iplot++){
   for(int ibin = 1; ibin <= Run_R209->Nbin; ibin++){
     ReducedChi2->Fill(Run_R209->ReducedChi2[iplot]->GetBinContent(ibin), 1.0);
   }
 }

 Run_E605->openFile("E605_results.dat");
// Run_E605->GetBinning("E605_results.dat");
 Run_E605->CopyHist("E605", E288200Hist, 5);
 Run_E605->WriteIn();
 for(int iplot = 1; iplot <= Run_E605->TotalPlot; iplot++){
   for(int ibin = 1; ibin <= Run_E605->Nbin; ibin++){
     ReducedChi2->Fill(Run_E605->ReducedChi2[iplot]->GetBinContent(ibin), 1.0);
   }
 }

 Run_E288200->openFile("E288200_results.dat");
// Run_E288200->GetBinning("E288200_results.dat");
 Run_E288200->CopyHist("E288200", E288200Hist, 4);
 Run_E288200->WriteIn();
 for(int iplot = 1; iplot <= Run_E288200->TotalPlot; iplot++){
   for(int ibin = 1; ibin <= Run_E288200->Nbin; ibin++){
     ReducedChi2->Fill(Run_E288200->ReducedChi2[iplot]->GetBinContent(ibin), 1.0);
   }
 }

 Run_E288300->openFile("E288300_results.dat");
// Run_E288300->GetBinning("E288300_results.dat");
 Run_E288300->CopyHist("E288300", E288200Hist, 5);
 Run_E288300->WriteIn();
 for(int iplot = 1; iplot <= Run_E288300->TotalPlot; iplot++){
   for(int ibin = 1; ibin <= Run_E288300->Nbin; ibin++){
     ReducedChi2->Fill(Run_E288300->ReducedChi2[iplot]->GetBinContent(ibin), 1.0);
   }
 }

 Run_E288400->openFile("E288400_results.dat");
// Run_E288400->GetBinning("E288400_results.dat");
 Run_E288400->CopyHist("E288400", E288200Hist, 6);
 Run_E288400->WriteIn();
 for(int iplot = 1; iplot <= Run_E288400->TotalPlot; iplot++){
   for(int ibin = 1; ibin <= Run_E288400->Nbin; ibin++){
     ReducedChi2->Fill(Run_E288400->ReducedChi2[iplot]->GetBinContent(ibin), 1.0);
   }
 }

 ReducedChi2->Scale(1.0 / ReducedChi2->Integral());
 TH1D* ReducedChi2_Final;
 HistDivideBinWidth(ReducedChi2, ReducedChi2_Final);

 ReducedChi2->Write();
 ReducedChi2_Final->Write();

 myhists->saveHists();

 cout<<"Master thread is end."<<endl;
 return 0;
}
