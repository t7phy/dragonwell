#ifndef loopHerwig_h
#define loopHerwig_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsHerwig.h"
#include "Analysis/TreeForHerwig.h"

using namespace std;

class loopHerwig : public loopMC
{
 public:
 TLorentzVector Electron;
 TLorentzVector Positron;
 TLorentzVector ZBoson;

 TLorentzVector Gamma1;
 TLorentzVector Gamma2;

 double cos_theta, phi, phi_eta;

 HistsHerwig *myhists;

 TreeForHerwig *HerwigTree;

 bool isCut = false;

 loopHerwig(TString RootType);
 virtual void InputHist(HistsHerwig* &myhists);
 virtual void InputTree(TreeForHerwig *HerwigTree);
 virtual void ReadTree(int ifile);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopHerwig();

};
#endif
