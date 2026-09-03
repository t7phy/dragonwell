#ifndef __HISTS_FWDRECO_H_
#define __HISTS_FWDRECO_H_
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

class HistsFwdReco : public makeHists
{
 public:
 ThreadHist<TH1D *>* FwdElectronPt;

 ThreadHist<TH1D *>* FwdElectronEta;

 ThreadHist<TH1D *>* FwdElectronPhi;

 ThreadHist<TH1D *>* FwdElectronEt;

 ThreadHist<TH1D *>* TruthElectronPt;

 ThreadHist<TH1D *>* TruthElectronEta;

 ThreadHist<TH1D *>* TruthElectronPhi;

 ThreadHist<TH1D *>* TruthElectronEt;

 ThreadHist<TH1D *>* TruthElectronEtaAbs;

 ThreadHist<TH1D *>* MatchedElectronPt;

 ThreadHist<TH1D *>* MatchedElectronEta;

 ThreadHist<TH1D *>* MatchedElectronPhi;

 ThreadHist<TH1D *>* MatchedElectronEt;

 ThreadHist<TH1D *>* MatchedElectronEtaAbs;

 ThreadHist<TH1D *>* AverageMu;

 ThreadHist<TH1D *>* TruthSize;

 ThreadHist<TH1D *>* RecoSize;

 ThreadHist<TH2D *>* TruthElectronEtEta;

 ThreadHist<TH2D *>* TruthElectronEtaPhi;

 ThreadHist<TH2D *>* MatchedElectronEtEta;

 ThreadHist<TH2D *>* MatchedElectronEtaPhi;

 ThreadHist<ResolutionHist *>* EResolutionEta;

 ThreadHist<ResolutionHist *>* PtResolutionEta;

 ThreadHist<ResolutionHist *>* EtResolutionEta;

 ThreadHist<ResolutionHist *>* PtResolutionEta_LowMu;

 ThreadHist<ResolutionHist *>* PtResolutionEta_HighMu;

 ThreadHist<ResolutionHist *>* PtResolutionPt;

//member function
 virtual void bookHists(int TotalThread);

// template<class T>

};
#endif
