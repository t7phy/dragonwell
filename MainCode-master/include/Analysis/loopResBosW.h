#ifndef loopResBosW_h
#define loopResBosW_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsResBosW.h"
#include "Analysis/TreeForResBos.h"
#include "Analysis/CutForResBos.h"

#include "Tools/Tools.h"

using namespace std;

class loopResBosW : public loopMC
{
 public:

 vector<TString> RootTypesForResBosW;

 TLorentzVector Neutrino;
 TLorentzVector Lepton;
 TLorentzVector WBoson;

 double WMT;

 bool isLepton = false;
 bool isAntiLepton = false;

 HistsResBosW *myhists;

 TreeForResBos *ResBosTree;

 bool isCut = false;
 bool isFSR = false;

 loopResBosW(TString RootType);
 virtual void InputHist(HistsResBosW* &myhists);
 virtual void InputTree(TreeForResBos *ResBosTree);
 virtual void ReadTree(int ifile);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopResBosW();

};
#endif
