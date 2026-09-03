#ifndef loopFlavorAsym_h
#define loopFlavorAsym_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsFlavorAsym.h"
#include "Analysis/TreeForFlavorAsym.h"

using namespace std;

class loopFlavorAsym : public loopMC
{
 public:

 TLorentzVector Electron;
 TLorentzVector Positron;
 TLorentzVector ZBoson;

 TLorentzVector Gamma1;
 TLorentzVector Gamma2;

 TLorentzVector Neutrino;
 TLorentzVector Lepton;
 TLorentzVector WBoson;

 double cos_theta, phi, phi_eta;
 float Weight;
 double ReweightingFactor;
 double P0uValue, P0dValue, StwValue;
 double WMT;

 double ECM = 13000.0;

 bool isFSR = false;
 bool isDilution = false;

 bool isLepton = false;
 bool isAntiLepton = false;

 HistsFlavorAsym *myhists;

 TreeForFlavorAsym *FlavorAsymTree;

 bool isCut = false;

 bool isZEvents = false;
 bool isWEvents = false;

 double PDFDelta = 1000.0;
 double ZEventPDFWeight = 1.0;
 double WEventPDFWeight = 1.0;

 int QuarkFlavor = 0;
 int Quark1Flavor = 0;
 int Quark2Flavor = 0;

 loopFlavorAsym(TString RootType);
 virtual void InputHist(HistsFlavorAsym* &myhists);
 virtual void InputTree(TreeForFlavorAsym *FlavorAsymTree);
 virtual void InputECM(double ECM){this->ECM = ECM;};
 virtual void ReadTree(int ifile);
 virtual void FillZEvents();
 virtual void FillWEvents();
 virtual double GetPDFReweightingFactor(double x1, double x2, int flavor1, int flavor2, double Q);
 virtual double GetZPDFWeight(double LargeX, double SmallX, int flavor, double Q, double Delta);
 virtual double GetWPDFWeight(double LargeX, double SmallX, int flavor, double Q, double Delta);
 virtual double GetZStrangeWeight(double x1, double x2, int flavor, double Q, double Delta);
 virtual double GetWStrangeWeight(double x1, double x2, int flavor1, int flavor2, double Q, double Delta);
 virtual void InputPDFDelta(double Delta){this->PDFDelta = Delta;};
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopFlavorAsym();

};
#endif
