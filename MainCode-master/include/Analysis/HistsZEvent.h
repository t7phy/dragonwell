#ifndef __HistsZEvent_H_
#define __HistsZEvent_H_
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

class HistsZEvent : public makeHists
{
 public:

  ////////////////////////////////////////
  //  Define histograms:                //
  //                                    //
  //  1d histogram example:             //
  //  ThreadHist<TH1D *>* ZMass;        //
  //                                    //
  //  2d histogram example:             //
  //  ThreadHist<TH2D *>* ZMass_ZY;     //
  //                                    //
  //  3d histogram example:             //
  //  ThreadHist<TH3D *>* ZMass_ZY_QT;  //
  ////////////////////////////////////////



//member function
 HistsZEvent(int TotalThread){this->TotalThread = TotalThread;};
 vector<TString> sysName;
 virtual void InitialSysName();
 virtual void bookHists(int TotalThread);

// template<class T>

};
#endif
