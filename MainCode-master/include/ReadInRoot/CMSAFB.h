#ifndef ReadInRoot_CMSAFB_h
#define ReadInRoot_CMSAFB_h

#include "ReadInRoot/ReadInRoot.h"
#include "Analysis/HistsResBos.h"

using namespace std;

class CMSAFB : public ReadInRoot
{
 public:

 HistsResBos* myhists;

 double BinCenter;
 double BinLeft;
 double BinRight;
 double DataPoint;
 double StaErr;
 double SysErr;
 double RegBias;

 vector<double> BinCenters;
 vector<double> BinLefts;
 vector<double> BinRights;
 vector<double> DataPoints;
 vector<double> StaErrs;
 vector<double> SysErrs;

 void LinkHist(HistsResBos* &myhists);
 void WriteIn(TH1D* &h1);
};
#endif
