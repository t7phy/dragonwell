#ifndef loopCustom_v1_h
#define loopCustom_v1_h

#include "Analysis/loopMC.h"

#include "CustomVersion/HistsCustom_v1.h"
#include "CustomVersion/TreeForCustom_v1.h"

using namespace std;

class loopCustom_v1 : public loopMC
{
 public:
 TLorentzVector Electron;
 TLorentzVector Positron;
 TLorentzVector ZBoson;

 TLorentzVector Gamma1;
 TLorentzVector Gamma2;

 double cos_theta, phi, phi_eta;

 HistsCustom_v1 *myhists;

 TreeForCustom_v1 *Custom_v1Tree;

 bool isCut = false;

 loopCustom_v1(TString RootType);
 virtual void InputHist(HistsCustom_v1* &myhists);
 virtual void InputTree(TreeForCustom_v1 *Custom_v1Tree);
 virtual void ReadTree(int ifile);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopCustom_v1();

};
#endif
