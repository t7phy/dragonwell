#ifndef loopFwdReco_h
#define loopFwdReco_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsFwdReco.h"
#include "Analysis/TreeForFwdReco.h"

using namespace std;

class loopFwdReco : public loopMC
{
 public:
 TLorentzVector FwdElectron;
 TLorentzVector TruthElectron;

 int isfwdMatched;
 int isMatched;

 double deltaE, deltaPt, deltaEt;
 double recoFwdClusterPt;

 HistsFwdReco *myhists;

 TreeForFwdReco *FwdRecoTree;

 bool isCut = false;

 loopFwdReco(TString RootType);
 virtual void InputHist(HistsFwdReco* &myhists);
 virtual void InputTree(TreeForFwdReco *FwdRecoTree);
 virtual void ReadTree(int ifile);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopFwdReco();

};
#endif
