#include <iostream>
#include "ReadInRoot/ResBosAngular.h"
#include "Analysis/HistsResBos.h"

using namespace std;

int main(int argc, char** argv)
{
 ResBosAngular* Run = new ResBosAngular();
 HistsResBos* myhists = new HistsResBos();
 myhists->openFile("save.root");
 myhists->bookHists(1);

 Run->LinkHist(myhists);

 Run->openFile("A0_data.txt");
 Run->WriteIn(myhists->A0_ZPt->at(0)->AngularHist1D);

 Run->openFile("A1_data.txt");
 Run->WriteIn(myhists->A1_ZPt->at(0)->AngularHist1D);

 Run->openFile("A2_data.txt");
 Run->WriteIn(myhists->A2_ZPt->at(0)->AngularHist1D);

 Run->openFile("A3_data.txt");
 Run->WriteIn(myhists->A3_ZPt->at(0)->AngularHist1D);

 Run->openFile("A4_data.txt");
 Run->WriteIn(myhists->A4_ZPt->at(0)->AngularHist1D);

 myhists->MergeHists();
 myhists->saveHists();
// delete Run;
 cout<<"Master thread is end."<<endl;
 return 0;
}
