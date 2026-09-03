#ifndef loopResBosCMS_h
#define loopResBosCMS_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsResBosCMS.h"
#include "Analysis/TreeForResBosCMS.h"

#include "Tools/Tools.h"
#include "Tools/DilutionReweighting.h"

using namespace std;

class loopResBosCMS : public loopMC
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
 double ReweightingFactor;
 double P0uValue, P0dValue, StwValue;

 DilutionReweighting* myReweighting;

 double ECM = 13000.0;

 bool isFSR = false;
 bool isDilution = false;

 HistsResBosCMS *myhists;

 TreeForResBosCMS *ResBosCMSTree;

 bool isCut = false;

 bool isZU = false;
 bool isZD = false;
 bool isWPlus = false;
 bool isWMinus = false;
 bool isZEvents = false;
 bool isWEvents = false;

 loopResBosCMS(TString RootType);
 virtual void InputHist(HistsResBosCMS* &myhists);
 virtual void InputTree(TreeForResBosCMS *ResBosCMSTree);
 virtual void InputECM(double ECM){this->ECM = ECM;};
 virtual void InputP0STW(double P0u, double P0d, double stw){
   this->P0uValue = P0u;
   this->P0dValue = P0d;
   this->StwValue = stw;
   if(iThread == 1){
     cout<<"Input parameters:"<<endl;
     cout<<"P0u = "<<P0u<<endl;
     cout<<"P0d = "<<P0d<<endl;
     cout<<"stw = "<<stw<<endl;
   }
 }

 virtual void InitialReweight(){myReweighting->Initial();};
 virtual void ReadTree(int ifile);
 virtual void FillZEvents();
 virtual void FillWEvents();
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopResBosCMS();

};
#endif
