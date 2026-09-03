#ifndef loopSherpaWW_h
#define loopSherpaWW_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsSherpaWW.h"
#include "Analysis/TreeForSherpaWW.h"

using namespace std;

class loopSherpaWW : public loopMC
{
 public:

 TLorentzVector Electron;
 TLorentzVector eNeutrino;
 TLorentzVector Muon;
 TLorentzVector mNeutrino;

 TLorentzVector PositiveLepton;
 TLorentzVector NegativeLepton;
 TLorentzVector DiNeutrino;

 TLorentzVector WPlus;
 TLorentzVector WMinus;
 TLorentzVector WW;

 TLorentzVector Gamma1;
 TLorentzVector Gamma2;

 HistsSherpaWW *myhists;

 TreeForSherpaWW *SherpaWWTree;

 bool isCut = false;

 int PDFErrorSet;

 vector<float> *PDFWeights;

 loopSherpaWW(TString RootType);
 virtual void InputHist(HistsSherpaWW* &myhists);
 virtual void InputTree(TreeForSherpaWW *SherpaWWTree);
 virtual void ReadTree(int ifile);
 virtual void InputErrorSet(int ErrorSet){this->PDFErrorSet = (int)ErrorSet;};
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopSherpaWW();

};
#endif
