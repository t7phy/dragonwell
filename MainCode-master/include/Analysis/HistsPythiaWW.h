#ifndef __HISTS_PYTHIAWW_H_
#define __HISTS_PYTHIAWW_H_
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

class HistsPythiaWW : public makeHists
{
 public:

 ThreadHist<TH1D *>* Wrong_uu;

 ThreadHist<TH1D *>* Right_uu;

 ThreadHist<TH1D *>* Total_uu;

 ThreadHist<TH1D *>* Wrong_dd;

 ThreadHist<TH1D *>* Right_dd;

 ThreadHist<TH1D *>* Total_dd;

 ThreadHist<TH1D *>* Wrong_ss;

 ThreadHist<TH1D *>* Right_ss;

 ThreadHist<TH1D *>* Total_ss;

 ThreadHist<TH1D *>* Wrong_cc;

 ThreadHist<TH1D *>* Right_cc;

 ThreadHist<TH1D *>* Total_cc;

 ThreadHist<TH1D *>* Wrong_bb;

 ThreadHist<TH1D *>* Right_bb;

 ThreadHist<TH1D *>* Total_bb;

 ThreadHist<TH1D *>* Wrong_AllFlavor;

 ThreadHist<TH1D *>* Right_AllFlavor;

 ThreadHist<TH1D *>* Total_AllFlavor;

 ThreadHist<TH1D *>* WrongW_uu;

 ThreadHist<TH1D *>* RightW_uu;

 ThreadHist<TH1D *>* TotalW_uu;

 ThreadHist<TH1D *>* WrongW_dd;

 ThreadHist<TH1D *>* RightW_dd;

 ThreadHist<TH1D *>* TotalW_dd;

 ThreadHist<TH1D *>* WrongW_ss;

 ThreadHist<TH1D *>* RightW_ss;

 ThreadHist<TH1D *>* TotalW_ss;

 ThreadHist<TH1D *>* WrongW_cc;

 ThreadHist<TH1D *>* RightW_cc;

 ThreadHist<TH1D *>* TotalW_cc;

 ThreadHist<TH1D *>* WrongW_bb;

 ThreadHist<TH1D *>* RightW_bb;

 ThreadHist<TH1D *>* TotalW_bb;

 ThreadHist<TH1D *>* WrongW_AllFlavor;

 ThreadHist<TH1D *>* RightW_AllFlavor;

 ThreadHist<TH1D *>* TotalW_AllFlavor;

 ThreadHist<TH1D *>* WrongLepE_AllFlavor;

 ThreadHist<TH1D *>* RightLepE_AllFlavor;

 ThreadHist<TH1D *>* TotalLepE_AllFlavor;

 ThreadHist<TH1D *>* LeptonEta;

 ThreadHist<TH1D *>* AntiLeptonEta;

 ThreadHist<TH1D *>* WPlusRapidity;

 ThreadHist<TH1D *>* WMinusRapidity;

 ThreadHist<TH1D *>* WPlusPt;

 ThreadHist<TH1D *>* WMinusPt;

 ThreadHist<TH1D *>* WWMass;

 ThreadHist<TH1D *>* WWMass_uu;

 ThreadHist<TH1D *>* WWMass_dd;

 ThreadHist<TH1D *>* EtaDiff_uu;

 ThreadHist<TH1D *>* EtaDiff_dd;

 ThreadHist<TH1D *>* CosThetaPlusDiff;

 ThreadHist<TH1D *>* CosThetaMinusDiff;

 ThreadHist<TH1D *>* CosThetaPositiveLeptonNu;

 ThreadHist<TH1D *>* CosThetaNegativeLeptonNu;

 ThreadHist<TH1D *>* WPlusDecayStatus;

 ThreadHist<TH1D *>* WMinusDecayStatus;

 ThreadHist<TH1D *>* WPlusRapidity_CMS;

 ThreadHist<TH1D *>* WMinusRapidity_CMS;


 int Eta_bin = 1;  double Eta_left = 0.0;  double Eta_right = 10.0;
 int WY_bin = 1;   double WY_left = 0.0;   double WY_right = 10.0;
 int LepE_bin = 4; double LepE_left = 0.0; double LepE_right = 1000.0;

 TH1D* Ratio_uu;
 TH1D* Ratio_dd;
 TH1D* Ratio_ss;
 TH1D* Ratio_cc;
 TH1D* Ratio_bb;
 TH1D* Ratio_AllFlavor;
 TH1D* Ratio_AllFlavor_Overall;

 TH1D* RatioW_uu;
 TH1D* RatioW_dd;
 TH1D* RatioW_ss;
 TH1D* RatioW_cc;
 TH1D* RatioW_bb;
 TH1D* RatioW_AllFlavor;
 TH1D* RatioW_AllFlavor_Overall;

 TH1D* BoostAsymmetry_uu;
 TH1D* BoostAsymmetry_dd;
 TH1D* BoostAsymmetry_ss;
 TH1D* BoostAsymmetry_cc;
 TH1D* BoostAsymmetry_bb;
 TH1D* BoostAsymmetry_AllFlavor;

 TH1D* BoostAsymmetryW_uu;
 TH1D* BoostAsymmetryW_dd;
 TH1D* BoostAsymmetryW_ss;
 TH1D* BoostAsymmetryW_cc;
 TH1D* BoostAsymmetryW_bb;
 TH1D* BoostAsymmetryW_AllFlavor;

 TH1D* BoostAsymmetryLepE_AllFlavor;

//member function
 vector<TString> sysName;
 virtual void InitialSysName(){};
 virtual void bookHists(int TotalThread);
 virtual void outputInformation();

// template<class T>

};
#endif
