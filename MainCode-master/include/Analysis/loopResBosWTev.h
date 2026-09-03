#ifndef loopResBosWTev_h
#define loopResBosWTev_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsResBosWTev.h"
#include "Analysis/TreeForResBos.h"
#include "Analysis/CutForResBos.h"

#include "Tools/Tools.h"

using namespace std;

class loopResBosWTev : public loopMC
{
 public:

 vector<TString> RootTypesForResBosW;

 TLorentzVector Neutrino;
 TLorentzVector Lepton;
 TLorentzVector AntiLepton;
 TLorentzVector WBoson;

 TLorentzVector Lepton_Smear;
 TLorentzVector Neutrino_Smear;
 TLorentzVector Electron_Smear;
 TLorentzVector Positron_Smear;
 TLorentzVector WBoson_Smear;
 TLorentzVector ZBoson_Smear;

 double cos_theta, phi, phi_eta;
 double WMT;
 double ECM = 1960.0;

 bool isLepton = false;
 bool isAntiLepton = false;

 float Weight;

 HistsResBosWTev *myhists;

 TreeForResBos *ResBosTree;

 double myGausRandom = 0.0;
 TRandom3 random_lepton;
 TRandom3 random_neutrino;
 TRandom3 random_electron;
 TRandom3 random_positron;

 bool isCut = false;
 bool isFSR = false;

 Int_t pass_w225 = 0;
 Int_t pass_w227 = 0;
 Int_t pass_w234 = 0;
 Int_t pass_w281 = 0;


 loopResBosWTev(TString RootType);
 virtual void InputHist(HistsResBosWTev* &myhists);
 virtual void InputTree(TreeForResBos *ResBosTree);
 virtual void InputECM(double ECM){this->ECM = ECM;};
 virtual void ReadTree(int ifile);
 virtual void FillWEvents();
 virtual void FillZEvents();
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopResBosWTev();

 ResBosEW* EW;
 double OriginWMass = 80.385;
 double NewWMass = 80.385;
 double WWidth = 2.0895;
 virtual void InputWMass(double OriginWMass, double NewWMass, double WWidth){this->OriginWMass = OriginWMass; this->NewWMass = NewWMass; this->WWidth = WWidth;}
 virtual double GetWMassReweightingFactor(double Q, double OriginWMass, double NewWMass);
 virtual double GetWPtReweightingFactor(double QT, double a);

 double ScaleSlope = 0.0;
 virtual void InputScaleSlope(double a){this->ScaleSlope = a;}

 double LepPara1 = 0.0;
 double LepPara2 = 0.0;
 double LepPara3 = 0.0;
 double NuPara1 = 0.0;
 double NuPara2 = 0.0;
 double NuPara3 = 0.0;
 double LepScale = 1.0;
 double NuScale = 1.0;
 virtual void InputSmearPara(double LepPara1, double LepPara2, double LepPara3, double NuPara1, double NuPara2, double NuPara3){
   this->LepPara1 = LepPara1;
   this->LepPara2 = LepPara2;
   this->LepPara3 = LepPara3;
   this->NuPara1 = NuPara1;
   this->NuPara2 = NuPara2;
   this->NuPara3 = NuPara3;
   if(iThread == 1){
     cout<<"LepPara1 = "<<LepPara1<<endl;
     cout<<"LepPara2 = "<<LepPara2<<endl;
     cout<<"LepPara3 = "<<LepPara3<<endl;
     cout<<"NuPara1 = "<<NuPara1<<endl;
     cout<<"NuPara2 = "<<NuPara2<<endl;
     cout<<"NuPara3 = "<<NuPara3<<endl;
   }
 }
 virtual void InputSmearPara(double LepPara1, double LepPara2, double LepPara3, double NuPara1, double NuPara2, double NuPara3, double LepScale, double NuScale){
   this->LepPara1 = LepPara1;
   this->LepPara2 = LepPara2;
   this->LepPara3 = LepPara3;
   this->NuPara1 = NuPara1;
   this->NuPara2 = NuPara2;
   this->NuPara3 = NuPara3;
   this->LepScale = LepScale;
   this->NuScale = NuScale;
   if(iThread == 1){
     cout<<"LepPara1 = "<<LepPara1<<endl;
     cout<<"LepPara2 = "<<LepPara2<<endl;
     cout<<"LepPara3 = "<<LepPara3<<endl;
     cout<<"NuPara1 = "<<NuPara1<<endl;
     cout<<"NuPara2 = "<<NuPara2<<endl;
     cout<<"NuPara3 = "<<NuPara3<<endl;
     cout<<"LepScale = "<<LepScale<<endl;
     cout<<"NuScale = "<<NuScale<<endl;
   }
 }

};
#endif
