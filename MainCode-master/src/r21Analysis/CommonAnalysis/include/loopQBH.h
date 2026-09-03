#ifndef QBH_loopQBH_h
#define QBH_loopQBH_h

#include "Analysis/loopMC.h"

#include "QBH/HistsQBH.h"
#include "QBH/TreeForQBH.h"
#include "QBH/TreeForPreQBH.h"
#include "QBH/CutForQBH.h"

#include "SpecialHist/DataDriven.h"

class loopQBH;
class HistsQBH;
class TreeForQBH;
class TreeForPreQBH;

using namespace std;

class QBHLepton
{
 public:

   TLorentzVector  P4;

   QBHLepton(){ P4.SetPtEtaPhiM(0,0,0,0);ResetEvent();}
   virtual void ResetEvent();
   virtual ~QBHLepton(){ }
};

class EventQBH
{
 public:
   virtual void ResetEvent();
};

class loopQBH : public loopMC
{
 public:

 double ZPeakMass = 91.1876;
 double WPeakMass = 80.385;

 HistsQBH *myhists;

 TreeForQBH *QBHTree;
 TreeForPreQBH *PreQBHTree;

 EventQBH DefaultEvent;
 EventQBH ProcessEvent;
 EventQBH SelectedEvent;
 EventQBH TruthEvent;

 vector<int> RootTypes;

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
