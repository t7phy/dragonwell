#include "CustomVersion/HistsCustom_v1.h"

using namespace std;

void HistsCustom_v1::bookHists(int TotalThread)
{
 double rangeZPt[24] = {0,2.5,5,8,11.4,14.9,18.5,22,25.5,29,32.6,36.4,40.4,44.9,50.2,56.4,63.9,73.4,85.4,105,132,173,253,600};

 this->TotalThread = TotalThread;

}

void HistsCustom_v1::InitialSysName()
{

}
