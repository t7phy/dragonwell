#include <iostream>
#include "ReadInRoot/ResBosNonPertFit.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "Analysis/HistsResBos.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 3){
   cout<<"usage: ./GetNonPertFit log.txt ptData.txt"<<endl;
   return 0;
 }

 ResBosNonPertFit* Run = new ResBosNonPertFit();
 HistsResBos* myhists = new HistsResBos();
 myhists->openFile("save.root");

 Run->LinkHist(myhists);

 double rangeZPt[9] = {0.0, 2, 4, 6, 8, 10, 13, 16, 20};
 TH1D *ATLASy1 = new TH1D("ATLASy1", "ATLASy1", 8, rangeZPt);
 TH1D *ATLASy2 = new TH1D("ATLASy2", "ATLASy2", 8, rangeZPt);
 TH1D *ATLASy3 = new TH1D("ATLASy3", "ATLASy3", 8, rangeZPt);
 TH1D *ATLASy4 = new TH1D("ATLASy4", "ATLASy4", 8, rangeZPt);
 TH1D *ATLASy5 = new TH1D("ATLASy5", "ATLASy5", 8, rangeZPt);
 TH1D *ATLASy6 = new TH1D("ATLASy6", "ATLASy6", 8, rangeZPt);
 FileForEPUMP *Tabley1 = new FileForEPUMP("ATLASy1");
 FileForEPUMP *Tabley2 = new FileForEPUMP("ATLASy2");
 FileForEPUMP *Tabley3 = new FileForEPUMP("ATLASy3");
 FileForEPUMP *Tabley4 = new FileForEPUMP("ATLASy4");
 FileForEPUMP *Tabley5 = new FileForEPUMP("ATLASy5");
 FileForEPUMP *Tabley6 = new FileForEPUMP("ATLASy6");

 Run->openFile(argv[1]);
 Run->GetBinning(argv[2], 18, "ATLASy1");
 Run->WriteIn("ATLASy1");
 Run->RetrieveHist("Theory", 1, ATLASy1);
 Tabley1->InputTheory(ATLASy1, 56);
 Tabley1->writetheory();

 Run->openFile(argv[1]);
 Run->GetBinning(argv[2], 19, "ATLASy2");
 Run->WriteIn("ATLASy2");
 Run->RetrieveHist("Theory", 2, ATLASy2);
 Tabley2->InputTheory(ATLASy2, 56);
 Tabley2->writetheory();

 Run->openFile(argv[1]);
 Run->GetBinning(argv[2], 20, "ATLASy3");
 Run->WriteIn("ATLASy3");
 Run->RetrieveHist("Theory", 3, ATLASy3);
 Tabley3->InputTheory(ATLASy3, 56);
 Tabley3->writetheory();

 Run->openFile(argv[1]);
 Run->GetBinning(argv[2], 21, "ATLASy4");
 Run->WriteIn("ATLASy4");
 Run->RetrieveHist("Theory", 4, ATLASy4);
 Tabley4->InputTheory(ATLASy4, 56);
 Tabley4->writetheory();

 Run->openFile(argv[1]);
 Run->GetBinning(argv[2], 22, "ATLASy5");
 Run->WriteIn("ATLASy5");
 Run->RetrieveHist("Theory", 5, ATLASy5);
 Tabley5->InputTheory(ATLASy5, 56);
 Tabley5->writetheory();

 Run->openFile(argv[1]);
 Run->GetBinning(argv[2], 23, "ATLASy6");
 Run->WriteIn("ATLASy6");
 Run->RetrieveHist("Theory", 6, ATLASy6);
 Tabley6->InputTheory(ATLASy6, 56);
 Tabley6->writetheory();

 Run->Get2DPlot();

 Run->openFile(argv[1]);
 Run->GetBinning(argv[2], 4, "CDF1");
 Run->WriteIn("CDF1");

 Run->openFile(argv[1]);
 Run->GetBinning(argv[2], 5, "CDF2");
 Run->WriteIn("CDF2");

 Run->openFile(argv[1]);
 Run->GetBinning(argv[2], 10, "D01");
 Run->WriteIn("D01");

 Run->openFile(argv[1]);
 Run->GetBinning(argv[2], 11, "D02");
 Run->WriteIn("D02");

 myhists->saveHists();
// delete Run;
 cout<<"Master thread is end."<<endl;
 return 0;
}
