#ifndef loopResBosD0_h
#define loopResBosD0_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsResBosD0.h"
#include "Analysis/TreeForResBosD0.h"

using namespace std;

class loopResBosD0 : public loopMC
{
 public:

 TLorentzVector Electron;
 TLorentzVector Positron;
 TLorentzVector ZBoson;

 TLorentzVector Gamma1;
 TLorentzVector Gamma2;

 double cos_theta, phi, phi_eta;
 float Weight;
 double ReweightingFactor;
 double P0uValue, P0dValue, StwValue;

 double ECM = 13000.0;

 bool isFSR = false;
 bool isDilution = false;

 HistsResBosD0 *myhists;

 TreeForResBosD0 *ResBosD0Tree;

 bool isCut = false;

 loopResBosD0(TString RootType);
 virtual void InputHist(HistsResBosD0* &myhists);
 virtual void InputTree(TreeForResBosD0 *ResBosD0Tree);
 virtual void ReadTree(int ifile);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopResBosD0();

 virtual void InputECM(double ECM){this->ECM = ECM;};

};
#endif
