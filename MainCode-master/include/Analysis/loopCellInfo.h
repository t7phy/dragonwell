#ifndef loopCellInfo_h
#define loopCellInfo_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsCellInfo.h"
#include "Analysis/TreeForCellInfo.h"

using namespace std;

class loopCellInfo : public loopMC
{
 public:
 TLorentzVector Electron;
 TLorentzVector Positron;
 TLorentzVector ZBoson;

 TLorentzVector Gamma1;
 TLorentzVector Gamma2;

 double cos_theta, phi, phi_eta;

 HistsCellInfo *myhists;

 TreeForCellInfo *CellInfoTree;

 bool isCut = false;

 loopCellInfo(TString RootType);
 virtual void InputHist(HistsCellInfo* &myhists);
 virtual void InputTree(TreeForCellInfo *CellInfoTree);
 virtual void ReadTree(int ifile);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopCellInfo();

};
#endif
