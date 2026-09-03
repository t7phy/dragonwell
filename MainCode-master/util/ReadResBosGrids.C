#include "ReadResBosGrid/ReadResBosGrid.h"
#include "Analysis/HistsGrids.h"

using namespace std;

int main(int argc, char** argv)
{
// if(argc != 5){
//   cout<<"usage ./ReadResBosGrid gridfileW gridfileY gridfileMatch savefile"<<endl;
//   return 0;
// }

 if(argc != 3){
   cout<<"usage ./ReadResBosGrid gridfileW savefile"<<endl;
   return 0;
 }

 HistsGrids* myhists = new HistsGrids();
 myhists->PtCut(0, 900);
 myhists->openFile(argv[2]);

 ReadResBosGrid* RunW = new ReadResBosGrid();
 RunW->openFile(argv[1]);
 RunW->LinkHist(myhists);
 RunW->LoadW(1);
 RunW->SaveW(100.0, 2.5);
 RunW->SaveW(100.0, -2.5);


/* ReadResBosGrid* RunW = new ReadResBosGrid();
 ReadResBosGrid* RunY = new ReadResBosGrid();
 ReadResBosGrid* RunMatch = new ReadResBosGrid();

 myhists->openFile(argv[4]);

 RunW->openFile(argv[1]);
 RunW->LinkHist(myhists);
 RunW->LoadW();

 RunY->openFile(argv[2]);
 RunY->LinkHist(myhists);
 RunY->LoadY();

 RunMatch->openFile(argv[3]);
 RunMatch->LinkHist(myhists);
 RunMatch->LoadMatch();

 RunW->SaveW(90.0, 0.0);
 RunY->SaveY(90.0, 0.0);
 RunMatch->SaveMatch(90.0, 0.0);
*/


 myhists->saveHists();

 return 1;
}
