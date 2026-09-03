#include "ReadInRoot/MCFMWWBoost.h"

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"usage: ./GetRAi results.dat"<<endl;
   return 0;
 }

 MCFMWWBoost* Run = new MCFMWWBoost();
 HistsResBos* myhists = new HistsResBos();
 myhists->openFile("save.root");

 Run->LinkHist(myhists);

 Run->openFile(argv[1]);
 Run->GetBinning(argv[1], "A4YAL");
 Run->WriteIn("A4YAL");

 Run->openFile(argv[1]);
 Run->GetBinning(argv[1], "DSYAL");
 Run->WriteIn("DSYAL");

 myhists->saveHists();

 return 1;

}
