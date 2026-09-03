#ifndef QBH_loopQBH_h
#define QBH_loopQBH_h

#include "Analysis/loopMC.h"

#include "QBH/HistsQBH.h"
#include "QBH/TreeForQBH.h"
#include "QBH/TreeForPreQBH.h"
#include "QBH/CutForQBH.h"

#include "QBH/QBHFakeRate.h"
#include "SpecialHist/DataDriven.h"

class loopQBH;
class HistsQBH;
class TreeForQBH;
class TreeForPreQBH;

using namespace std;

class QBHLepton
{
 public:

   double d0Sig;
   TLorentzVector  P4;

   QBHLepton(){ P4.SetPtEtaPhiM(0,0,0,0);ResetEvent();}
   virtual void ResetEvent();
   virtual ~QBHLepton(){ }
};

class EventQBH
{
 public:

   Int_t           passTrig;

   Float_t         JetWeight;
   Float_t         NormSF;
   Float_t         TotalWeight;
   Float_t         TotalWeightLoose;
   Float_t         LeptonTightWeight;

   Float_t         LeadingLepWeight;
   Float_t         SubleadingLepWeight;

   Int_t           passLeadingLepTight;

   QBHLepton       LeadingLepton;
   QBHLepton       SubleadingLepton;
   QBHLepton       LeadingJet;

   Float_t         LepJetMass;
   Float_t         LeadingLeptonPt;
   Float_t         LeadingLeptonEta;
   Float_t         SubleadingLeptonPt;
   Float_t         LeadingJetPt;
   Float_t         SubleadingJetPt;
   Int_t           Njets;
   Int_t           NBjets;
   Float_t         MissingET;
   Float_t         Mll;
   Int_t           isSFOS;
   Float_t         DeltaRLepJet;
   Float_t         detaLepJet;
   Float_t         dphiLepJet;
   Float_t         METSig;
   Int_t           LeptonFlavor;
   Float_t         Lepton1_d0Sig;
   Float_t         Lepton2_d0Sig;
   Float_t         BornMass;

   Float_t         FakeEff = 0.0;
   Float_t         RealEff = 0.0;

   Int_t           passInclusive;
   Int_t           passFakeCR;
   Int_t           passWCR;
   Int_t           passWVR;
   Int_t           passZCR;
   Int_t           passZVR;
   Int_t           passTCR;
   Int_t           passTVR;
   Int_t           passSR;
   Int_t           passSVR;

   virtual void ResetEvent();
};

class loopQBH : public loopMC
{
 public:

 double ZPeakMass = 91.1876;
 double WPeakMass = 80.385;

 bool isData = false;

 HistsQBH *myhists;

 TreeForQBH *QBHTree;
 TreeForPreQBH *PreQBHTree;

 EventQBH DefaultEvent;
 EventQBH ProcessEvent;
 EventQBH SelectedEvent;
 EventQBH TruthEvent;

 vector<TString> RootTypes;
 TString BkgShortName = "";

 bool doFakeRate = false;
 QBHFakeRate* FakeRate;
 DataDriven* FakeInstance;

 loopQBH(TString RootType);
 virtual void InputHist(HistsQBH* &myhists);
 virtual void InputTree(TreeForQBH *QBHTree);
 virtual void InputTree(TreeForPreQBH *PreQBHTree);
 virtual void ReadTree(int ifile);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopQBH();

 bool isInputPreTree = false;
 TString NtupleName;

 virtual void InputNtupleName(TString NtupleName);
 virtual void PreLoop(int ifile);
 virtual bool FillEvents();

 virtual void FillHist(EventQBH ProcessEvent);

 virtual void GetCutInformation();
 virtual void FillCutFlow();
 virtual void FillWeightedCutFlow();

 ///////////////
 //  Control  //
 ///////////////

 bool JustGenerateTree = false;
 bool FinishProcess = false;
 virtual void ProcessOption(int iflag){
   if(iflag == 1){
     JustGenerateTree = true;
     FinishProcess = false;
   }
   if(iflag == 2){
     JustGenerateTree = false;
     FinishProcess = true;
   }
 }

};
#endif
