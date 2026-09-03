#define HistsQBH_cxx
#include "QBH/HistsQBH.h"

using namespace std;

HistsQBH::HistsQBH()
{
}

void HistsQBH::bookHists(int TotalThread)
{
 this->TotalThread = TotalThread;
 TString tail = "";

 this->subName = "";
}

void HistsQBH::LinkClass(HistsQBH *hist)
{
}

void HistsQBH::outputInformation()
{
}
