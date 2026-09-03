#ifndef loopMadGraph_h
#define loopMadGraph_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsMadGraph.h"
#include "Analysis/TreeForMadGraph.h"

using namespace std;

class loopMadGraph : public loopMC
{
 public:

 int ThisFile;

 TLorentzVector Electron;
 TLorentzVector Positron;
 TLorentzVector ZBoson;

 TLorentzVector Neutrino;
 TLorentzVector Lepton;
 TLorentzVector WBoson;

 double CrossSection = 0.0;
 int MadGraphNEvent = 0;

 double cos_theta, phi, phi_eta;
 double WMT;
 double ECM = 13000.0;

 HistsMadGraph *myhists;

 TreeForMadGraph *MadGraphTree;

 bool isCut = false;

 bool isZ = false;
 bool isWPlus = false;
 bool isWMinus = false;
 bool isZEvents = false;
 bool isWEvents = false;

 loopMadGraph(TString RootType);
 virtual void InputHist(HistsMadGraph* &myhists);
 virtual void InputTree(TreeForMadGraph *MadGraphTree);
 virtual void ReadTree(int ifile);
 virtual void FillZEvents();
 virtual void FillWEvents();
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopMadGraph();

 int ReweightID = 0;
 virtual void SetReweightFactor(int id){ReweightID = id;}

};
#endif
