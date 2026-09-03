#ifndef ReadInRoot_ResBosAngular_h
#define ReadInRoot_ResBosAngular_h

#include "ReadInRoot/ReadInRoot.h"
#include "Analysis/HistsResBos.h"

using namespace std;

class ResBosAngular : public ReadInRoot
{
 public:

 HistsResBos* myhists;

 double DataPoint;
 double StaErr;
 double SysErr;
 double RegBias;

 void LinkHist(HistsResBos* &myhists);
 void WriteIn(TH1D* h1);
};
#endif
