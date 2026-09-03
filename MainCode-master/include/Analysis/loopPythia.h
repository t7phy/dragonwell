#ifndef loopPythia_h
#define loopPythia_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsPythia.h"
#include "Analysis/TreeForPythia.h"
#include "Analysis/CutForPythia.h"

using namespace std;

class loopPythia : public loopMC
{
 public:
 TLorentzVector Electron;
 TLorentzVector Positron;
 TLorentzVector ZBoson;

 TLorentzVector Gamma1;
 TLorentzVector Gamma2;

 double cos_theta, phi, phi_eta;

 HistsPythia *myhists;

 TreeForPythia *PythiaTree;

 bool isCut = false;

 loopPythia(TString RootType);
 virtual void InputHist(HistsPythia* &myhists);
 virtual void InputTree(TreeForPythia *PythiaTree);
 virtual void ReadTree(int ifile);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopPythia();


 double DilutionWeight_FZRapidity = 1.0;
 double DilutionWeight_BZRapidity = 1.0;
 double DilutionWeight_FZRapidity_CC = 1.0;
 double DilutionWeight_BZRapidity_CC = 1.0;
 double DilutionWeight_FZRapidity_CF = 1.0;
 double DilutionWeight_BZRapidity_CF = 1.0;

 bool isRunReweightingFactor = false;
 bool isHaveReweightingFactor = false;
 virtual void PreRunReweightingFactor(){
   isRunReweightingFactor = true;
 }
 virtual void PostRunReweightingFactor(){isHaveReweightingFactor = true;}

 bool isPPbar = false;
 virtual void PPbarRun(){isPPbar = true;}

 double ECM = 13000.0;
 virtual void InputECM(double ECM){this->ECM = ECM;};

};
#endif
