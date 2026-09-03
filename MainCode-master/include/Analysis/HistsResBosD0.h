#ifndef __HistsResBosD0_H_
#define __HistsResBosD0_H_
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

class HistsResBosD0 : public makeHists
{
 public:

 //Forward and backward vs Mass ZY QT
 ThreadHist<TH3D *>* FZMass_ZY_QT;

 ThreadHist<TH3D *>* BZMass_ZY_QT;

 //ZMass ZY QT 3D plot
 ThreadHist<TH3D *>* ZMass_ZY_QT;

 ThreadHist<TH3D *>* FZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* BZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* FZMass_ZY_QT_dd;

 ThreadHist<TH3D *>* BZMass_ZY_QT_dd;

 ThreadHist<TH3D *>* ZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* ZMass_ZY_QT_dd;

 ThreadHist<TH3D *>* ZMass_ZY_QT_ss;

 ThreadHist<TH3D *>* ZMass_ZY_QT_cc;

 ThreadHist<TH3D *>* ZMass_ZY_QT_bb;

 /////////////////////
 //  dilution plot  //
 /////////////////////

 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_wrong;
 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_total;
 TH3D *Dilution_ZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_wrong;
 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_total;
 TH3D *Dilution_ZMass_ZY_QT_dd;

 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_right;

 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_right;

 TH3D *AFB_Mass_ZY_ZPt;

 TH3D *AFB_Mass_ZY_ZPt_uu;
 TH3D *AFB_Mass_ZY_ZPt_dd;

 TH3D *CoefficientDilution_ZMass_ZY_QT_uu;
 TH3D *CoefficientDilution_ZMass_ZY_QT_dd;
 TH3D *ResidualDilution_ZMass_ZY_QT_uu;
 TH3D *ResidualDilution_ZMass_ZY_QT_dd;
 TH3D *DilutionAverage_ZMass_ZY_QT_uu;
 TH3D *DilutionAverage_ZMass_ZY_QT_dd;

 TH3D *OneMinusTwoD_uu;
 TH3D *OneMinusTwoD_dd;
 TH3D *RelativeCrossSection_uu;
 TH3D *RelativeCrossSection_dd;


//member function
 vector<TString> sysName;
 virtual void InitialSysName();
 virtual void bookHists(int TotalThread);
 virtual void outputInformation();

// template<class T>

};
#endif
