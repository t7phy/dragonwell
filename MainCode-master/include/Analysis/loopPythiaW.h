#ifndef loopPythiaW_h
#define loopPythiaW_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsPythiaW.h"
#include "Analysis/TreeForPythiaW.h"

using namespace std;

class loopPythiaW : public loopMC
{
 public:
 TLorentzVector Muon;
 TLorentzVector Neutrino;
 TLorentzVector WBoson;

 TLorentzVector Gamma1;
 TLorentzVector Gamma2;

 double cos_theta, phi, phi_eta;

 HistsPythiaW *myhists;

 TreeForPythiaW *PythiaWTree;

 bool isCut = false;

 loopPythiaW(TString RootType);
 virtual void InputHist(HistsPythiaW* &myhists);
 virtual void InputTree(TreeForPythiaW *PythiaWTree);
 virtual void ReadTree(int ifile);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopPythiaW();

};
#endif
