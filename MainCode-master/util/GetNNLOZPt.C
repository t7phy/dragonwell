#include "ReadInRoot/MCFMWWBoost.h"

int main(int argc, char** argv)
{
 MCFMWWBoost* Run = new MCFMWWBoost();
 HistsResBos* myhists = new HistsResBos();
 myhists->openFile("save.root");

 Run->LinkHist(myhists);

 Run->openFile("ZPt_nlo.txt");
 Run->InputSubName("_nlo");
 Run->GetBinning("ZPt_nlo.txt", "ZPt");
 Run->WriteIn("ZPt");

 Run->openFile("ZPt_nnlo.txt");
 Run->InputSubName("_nnlo");
 Run->GetBinning("ZPt_nnlo.txt", "ZPt");
 Run->WriteIn("ZPt");

 myhists->saveHists();

 return 1;
}
