#ifndef loopPythiaWW_h
#define loopPythiaWW_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsPythiaWW.h"
#include "Analysis/TreeForPythiaWW.h"

using namespace std;

class loopPythiaWW : public loopMC
{
 public:
 TLorentzVector Electron;
 TLorentzVector eNeutrino;
 TLorentzVector Muon;
 TLorentzVector mNeutrino;

 TLorentzVector PositiveLepton;
 TLorentzVector NegativeLepton;
 TLorentzVector Neutrino;
 TLorentzVector AntiNeutrino;
 TLorentzVector DiNeutrino;

 TLorentzVector WPlus;
 TLorentzVector WMinus;
 TLorentzVector WW;

 TLorentzVector WPlus_CMS;
 TLorentzVector WMinus_CMS;

 TLorentzVector PositiveLepton_WPlusFrame;
 TLorentzVector NegativeLepton_WMinusFrame;

 TLorentzVector Gamma1;
 TLorentzVector Gamma2;

 double cos_theta, phi, phi_eta;

 HistsPythiaWW *myhists;

 TreeForPythiaWW *PythiaWWTree;

 bool isCut = false;

 loopPythiaWW(TString RootType);
 virtual void InputHist(HistsPythiaWW* &myhists);
 virtual void InputTree(TreeForPythiaWW *PythiaWWTree);
 virtual void ReadTree(int ifile);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopPythiaWW();

};
#endif
