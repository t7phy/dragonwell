#ifndef loopResBos_h
#define loopResBos_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsResBos.h"
#include "Analysis/TreeForResBos.h"
#include "Analysis/CutForResBos.h"

#ifdef loopResBos_cxx
#include "Tools/Tools.h"
#endif

using namespace std;

class loopResBos : public loopMC
{
 public:
 TLorentzVector Electron;
 TLorentzVector Positron;
 TLorentzVector ZBoson;

 TLorentzVector Gamma1;
 TLorentzVector Gamma2;

 double cos_theta, phi, phi_eta;
 float Weight;

 double ECM = 13000.0;

 HistsResBos *myhists;

 TreeForResBos *ResBosTree;

 bool isCut = false;
 bool isFSR = false;
 bool isDilution = false;
 vector<TString> RootTypesForResBos;

 bool isAddEnergyScale = false;
 vector<double> EnergyScaleList;

 int ProblemEventNumber = 0;

 bool doCalibration = false;
 double Scale = 1.0;
 double Smear = 0.0;
 double myGausRandom = 0.0;

 loopResBos(TString RootType);
 virtual void InputHist(HistsResBos* &myhists);
 virtual void InputTree(TreeForResBos *ResBosTree);
 virtual void InputECM(double ECM);
 virtual void InputScaleAndSmear(double Scale, double Smear);
 virtual void ReadTree(int ifile);
 virtual void ConfigEnergyScale(vector<double> EnergyScaleList);
 virtual void AddEnergyScale(TLorentzVector Electron_reco, TLorentzVector Positron_reco);
 virtual double GetPDFReweightingFactor(double x1, double x2, int flavor1, int flavor2, double Q);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopResBos();

};
#endif
