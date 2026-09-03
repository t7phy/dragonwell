#ifndef loopResBosHighMassZ_h
#define loopResBosHighMassZ_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsResBosHighMassZ.h"
#include "Analysis/TreeForResBosHighMassZ.h"

using namespace std;

class loopResBosHighMassZ : public loopMC
{
 public:

 TLorentzVector Electron;
 TLorentzVector Positron;
 TLorentzVector ZBoson;

 TLorentzVector Neutrino;
 TLorentzVector Lepton;
 TLorentzVector WBoson;

 TLorentzVector Gamma1;
 TLorentzVector Gamma2;

 double cos_theta, phi, phi_eta;
 double WMT;
 float Weight;

 double ECM = 13000.0;
 bool isDilution = false;

 HistsResBosHighMassZ *myhists;

 TreeForResBosHighMassZ *ResBosHighMassZTree;

 bool isCut = false;

 bool isZU = false;
 bool isZD = false;
 bool isWP = false;
 bool isWM = false;

 bool isZEvents = false;
 bool isWEvents = false;

 loopResBosHighMassZ(TString RootType);
 virtual void InputHist(HistsResBosHighMassZ* &myhists);
 virtual void InputTree(TreeForResBosHighMassZ *ResBosHighMassZTree);
 virtual void ReadTree(int ifile);
 virtual void FillZEvents();
 virtual void FillWEvents();
 virtual double GetPDFReweightingFactor(double x1, double x2, int flavor1, int flavor2, double Q);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopResBosHighMassZ();

};
#endif
