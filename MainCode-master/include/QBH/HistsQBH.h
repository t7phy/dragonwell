#ifndef QBH_HistsQBH_h
#define QBH_HistsQBH_h
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
#include "QBH/TreeForQBH.h"
#include "QBH/loopQBH.h"
#include "QBH/QBHFakeRate.h"

using namespace std;

class QBHHistGroup;
class HistsQBH;
class EventQBH;
class TreeForQBH;
class loopQBH;

class QBHHistGroup
{
 friend class HistsQBH;

 public:

 ThreadHist<BkgHist *>* Inclusive_bkg;
 ThreadHist<BkgHist *>* FakeCR_bkg;
 ThreadHist<BkgHist *>* WCR_bkg;
 ThreadHist<BkgHist *>* WVR_bkg;
 ThreadHist<BkgHist *>* ZCR_bkg;
 ThreadHist<BkgHist *>* ZVR_bkg;
 ThreadHist<BkgHist *>* TCR_bkg;
 ThreadHist<BkgHist *>* TVR_bkg;
 ThreadHist<BkgHist *>* SR_bkg;
 ThreadHist<BkgHist *>* SVR_bkg;

 ThreadHist<TH1D *>* Inclusive_Fake;
 ThreadHist<TH1D *>* FakeCR_Fake;
 ThreadHist<TH1D *>* WCR_Fake;
 ThreadHist<TH1D *>* WVR_Fake;
 ThreadHist<TH1D *>* ZCR_Fake;
 ThreadHist<TH1D *>* ZVR_Fake;
 ThreadHist<TH1D *>* TCR_Fake;
 ThreadHist<TH1D *>* TVR_Fake;
 ThreadHist<TH1D *>* SR_Fake;
 ThreadHist<TH1D *>* SVR_Fake;

 ThreadHist<BkgHist *>* Inclusive_Loose_bkg;

 HistsQBH *fHist;
 int TotalThread;

 TString HistName = "";
 TString SystematicName = "";

 QBHHistGroup();
 virtual void Initial(int iThread, TString MCType);
 virtual void Fill(int iThread, double par, double weight, EventQBH ProcessEvent);
 virtual void FillFake(int iThread, double par, double weight, EventQBH ProcessEvent);
 virtual void ResetHist();
 virtual void GetFinalData();

 TString MCType[100] = {""};
 bool isData[100] = {false};
 bool isSignal[100] = {false};
};

class HistsQBH : public makeHists
{
 friend class QBHHistGroup;

 TreeForQBH *fTree;

 public:

 QBHHistGroup* LepJetMass;
 QBHHistGroup* LepJetMass_El;
 QBHHistGroup* LepJetMass_Mu;
 QBHHistGroup* LepJetMass_LowBornMass;
 QBHHistGroup* LepJetMass_HighBornMass;
 QBHHistGroup* LepJetMass_LowBornMass_El;
 QBHHistGroup* LepJetMass_HighBornMass_El;
 QBHHistGroup* LepJetMass_LowBornMass_Mu;
 QBHHistGroup* LepJetMass_HighBornMass_Mu;

 QBHHistGroup* LeadingLeptonPt;
 QBHHistGroup* LeadingLeptonEta;
 QBHHistGroup* LeadingJetPt;
 QBHHistGroup* Njets;
 QBHHistGroup* MissingET;
 QBHHistGroup* Mll;
 QBHHistGroup* DeltaRLepJet;
 QBHHistGroup* detaLepJet;
 QBHHistGroup* detaLepJet_El;
 QBHHistGroup* detaLepJet_Mu;
 QBHHistGroup* dphiLepJet;
 QBHHistGroup* dphiLepJet_El;
 QBHHistGroup* dphiLepJet_Mu;
 QBHHistGroup* METSig;
 QBHHistGroup* METSig_El;
 QBHHistGroup* METSig_Mu;
 QBHHistGroup* Lepton1_d0Sig;
 QBHHistGroup* Lepton2_d0Sig;

 QBHHistGroup* BornMass;

 HistsQBH();
 virtual void bookHists(int TotalThread);
 //virtual void bookProcessHists(TString ProcessName, TString subName);
 virtual void outputInformation();
 virtual void bookAllProcessHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double left, double right);
 virtual void bookAllProcessHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double* xbins);
 virtual void DefineHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double left, double right);
 virtual void DefineHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double* xbins);
 virtual void LinkClass(HistsQBH *hist);

 bool doFakeRate = false;
 QBHFakeRate* FakeRate;
 virtual void InputFakeRate(QBHFakeRate* ptr){FakeRate = ptr; doFakeRate = true;}

 TString SystematicName = "";
 void InputSystematicName(TString SystematicName){this->SystematicName = SystematicName;};

 vector<QBHHistGroup *> hist_process;
 vector<TString> HistNames;

};
#endif
