#include "ReadInRoot/MCFMWWBoost.h"

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"usage: ./GetMCFMWWBoost results.dat"<<endl;
   return 0;
 }

 MCFMWWBoost* Run = new MCFMWWBoost();
 HistsResBos* myhists = new HistsResBos();
 myhists->openFile("save.root");

 Run->LinkHist(myhists);

 Run->openFile(argv[1]);
 Run->GetBinning(argv[1], "ElectronEta");
 Run->WriteIn("ElectronEta");

 Run->openFile(argv[1]);
 Run->GetBinning(argv[1], "PositronEta");
 Run->WriteIn("PositronEta");

 Run->openFile(argv[1]);
 Run->GetBinning(argv[1], "WPlusRapidity");
 Run->WriteIn("WPlusRapidity");
 
 Run->openFile(argv[1]);
 Run->GetBinning(argv[1], "WMinusRapidity");
 Run->WriteIn("WMinusRapidity");

 Run->openFile(argv[1]);
 Run->GetBinning(argv[1], "Right");
 Run->WriteIn("Right");

 Run->openFile(argv[1]);
 Run->GetBinning(argv[1], "Wrong");
 Run->WriteIn("Wrong");

 Run->openFile(argv[1]);
 Run->GetBinning(argv[1], "RightW");
 Run->WriteIn("RightW");
 
 Run->openFile(argv[1]);
 Run->GetBinning(argv[1], "WrongW");
 Run->WriteIn("WrongW");

 Run->GetAdditionalPlot();

 myhists->saveHists();

 return 1;
}
