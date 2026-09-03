#include <iostream>
#include "ReadInRoot/ResBosZPt.h"
#include "Analysis/HistsResBos.h"

using namespace std;

int main(int argc, char** argv)
{
 ResBosZPt* Run = new ResBosZPt();
 HistsResBos* myhists = new HistsResBos();
 myhists->openFile("save_PhiEta.root");
 myhists->bookHists(1);

 Run->LinkHist(myhists);

 Run->openFile("PhiEta_data.txt");
 Run->WriteIn(myhists->plot_phi_eta->at(0));

 myhists->MergeHists();
 myhists->saveHists();
// delete Run;
 cout<<"Master thread is end."<<endl;
 return 0;
}
