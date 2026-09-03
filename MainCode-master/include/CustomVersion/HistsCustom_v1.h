#ifndef __HISTS_CUSTOM_V1_H_
#define __HISTS_CUSTOM_V1_H_
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TMath.h"
#include "TTree.h"
#include <vector>
#include "Analysis/makeHists.h"

using namespace std;

class HistsCustom_v1 : public makeHists
{
 public:

//member function
 vector<TString> sysName;
 virtual void InitialSysName();
 virtual void bookHists(int TotalThread);

// template<class T>

};
#endif
