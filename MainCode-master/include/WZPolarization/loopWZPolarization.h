#ifndef loopWZPolarization_h
#define loopWZPolarization_h

#include "Analysis/loopMC.h"

#include "WZPolarization/HistsWZPolarization.h"
#include "WZPolarization/TreeForWZPolarization.h"
#include "WZPolarization/TreeForPreWZPolarization.h"
#include "WZPolarization/CutForWZPolarization.h"

#include "SpecialHist/DataDriven.h"
#include "WZPolarization/TMVAHelper.h"

#include "Tools/LWTNNHelper.h"

class loopWZPolarization;
class HistsWZPolarization;
class TreeForWZPolarization;
class TreeForPreWZPolarization;
class TMVAHelper;

using namespace std;

class Lepton
{
 public:

   TString         Flavor;
   Int_t           pdgID = 0;
   Float_t         Pt;
   Float_t         Eta;
   Float_t         Phi;
   Float_t         E;
   Int_t           Charge;
   Float_t         d0Sig;

   Int_t           Level;
   Int_t           ZLevel;
   Int_t           WLevel;

   Int_t           mediumID;
   Int_t           tightID;
   Int_t           FCLooseIso;
   Int_t           FCTightIso;
   Int_t           FCHighPtIso;
   Int_t           HighPtCaloOnlyIso;
   Int_t           Loose_VarRadIso;
   Int_t           Tight_VarRadIso;
   Int_t           PflowLooseIso;
   Int_t           PflowTightIso;
   Int_t           ZTightIso;
   Int_t           WTightIso;
   Float_t         ZTightIsoWeight = 1.0;
   Float_t         WTightIsoWeight = 1.0;
   Int_t           IPID = 0;
   Float_t         mediumIDWeight = 1.0;
   Float_t         tightIDWeight = 1.0;
   Float_t         FCLooseIsoWeight = 1.0;
   Float_t         FCTightIsoWeight = 1.0;
   Float_t         FCHighPtIsoWeight = 1.0;
   Float_t         HighPtCaloOnly_MediumID_IsoWeight = 1.0;
   Float_t         HighPtCaloOnly_TightID_IsoWeight = 1.0;
   Float_t         Loose_VarRad_MediumID_IsoWeight = 1.0;
   Float_t         Loose_VarRad_TightID_IsoWeight = 1.0;
   Float_t         Tight_VarRad_MediumID_IsoWeight = 1.0;
   Float_t         Tight_VarRad_TightID_IsoWeight = 1.0;
   Float_t         PflowLooseIsoWeight = 1.0;
   Float_t         PflowTightIsoWeight = 1.0;
   Int_t           triggerMatched;
   Int_t           truthMatched;
   Float_t         recoWeight = 1.0;
   Float_t         IPWeight = 1.0;
   Int_t           isBaseline = 0;
   Int_t           isAmbiguity = 0;

   TLorentzVector  P4;

   Lepton(){ P4.SetPtEtaPhiM(0,0,0,0);ResetEvent();}
   virtual void ResetEvent();
   virtual ~Lepton(){ }
};

class EventWZPolarization
{
 public:

   int             MCType;
   long           EventNumber;
   TString         Flavor;
   Int_t           Yields;
   Int_t           DecayChannel;
   Int_t           isMC;
   Int_t           Channel;
   Int_t           Year;
   Int_t           UniqueYear = 0;
   Float_t         NormSF;
   Float_t         WeightSign;
   Float_t         WeightNormalized;
   Float_t         Weight;
   Float_t         TotalWeight;
   Float_t         WeightNormalizedNoKFactor;
   Float_t         WeightNoKFactor;
   Float_t         TotalWeightNoKFactor;
   Float_t         M_WZ;
   Float_t         M_3l;
   Float_t         Mt_WZ;
   Float_t         M_Z;
   Float_t         ZY;
   Float_t         Mt_W;
   Float_t         Met;
   Int_t           Njets;
   Int_t           NBjets;
   Double_t        SumOfWeight;
   Double_t        Luminosity;
   Double_t        CrossSection;
   Float_t         Lep1Pt;
   Float_t         Lep2Pt;
   Float_t         Lep3Pt;
   Float_t         Lep1Eta;
   Float_t         Lep2Eta;
   Float_t         Lep3Eta;
   Float_t         Lep1Phi;
   Float_t         Lep2Phi;
   Float_t         Lep3Phi;
   Float_t         dR_Lep1_Lep2;
   Float_t         dR_Lep1_Lep3;
   Float_t         dR_Lep2_Lep3;
   Int_t           Lep1Flavor;
   Int_t           Lep2Flavor;
   Int_t           Lep3Flavor;
   Int_t           Lep1Charge = 0;
   Int_t           Lep2Charge = 0;
   Int_t           Lep3Charge = 0;
   Int_t           Lep1Ambiguity = 0;
   Int_t           Lep2Ambiguity = 0;
   Int_t           Lep3Ambiguity = 0;
   Float_t         TruthLep1Pt;
   Float_t         TruthLep2Pt;
   Float_t         TruthLep3Pt;
   Float_t         TruthLep1Eta;
   Float_t         TruthLep2Eta;
   Float_t         TruthLep3Eta;
   Float_t         TruthLep1Phi;
   Float_t         TruthLep2Phi;
   Float_t         TruthLep3Phi;
   Int_t           TruthLep1Flavor = 0;
   Int_t           TruthLep2Flavor = 0;
   Int_t           TruthLep3Flavor = 0;
   Float_t         Mpx;
   Float_t         Mpy;
   Float_t         Mpz;
   Float_t         LWTNNNuPz;
   Float_t         TruthNuPz;
   Float_t         LWTNNpLL;
   Float_t         LWTNNpLT;
   Float_t         LWTNNpTL;
   Float_t         LWTNNpTT;
   Float_t         LLNLOWeight = 1.0;
   Float_t         LTNLOWeight = 1.0;
   Float_t         TLNLOWeight = 1.0;
   Float_t         TTNLOWeight = 1.0;
   Float_t         Lep1WeightZ = 1.0;
   Float_t         Lep2WeightZ = 1.0;
   Float_t         Lep3WeightZ = 1.0;
   Float_t         Lep1WeightW = 1.0;
   Float_t         Lep2WeightW = 1.0;
   Float_t         Lep3WeightW = 1.0;
   Float_t         Pt_W;
   Float_t         Pt_Z;
   Float_t         Pt_WZ;
   Float_t         SumJetPt;
   Float_t         CosThetaV;
   Float_t         CosThetaLepW;
   Float_t         CosThetaLepZ;
   Float_t         DY_WZ;
   Float_t         DY_3Z;
   Float_t         DY_3N;
   Float_t         Truth_Pt_WZ;
   Float_t         DeltaPhiLepWLepZ;
   Float_t         DeltaPhiLepWLepZWZFrame;
   Float_t         DeltaPhiZBosonLepW;
   Float_t         R21;
   Float_t         WLepPt;
   Float_t         ZLeadingLepPt;
   Float_t         ZSubleadingLepPt;
   Float_t         WLepEta;
   Float_t         ZLeadingLepEta;
   Float_t         ZSubleadingLepEta;
   Float_t         WLepPhi;
   Float_t         ZLeadingLepPhi;
   Float_t         ZSubleadingLepPhi;
   Float_t         WLepPz;
   Float_t         NeutrinoPz;
   Float_t         ZLep1Pz;
   Float_t         ZLep2Pz;
   Float_t         WDecayStatus;
   Float_t         ZDecayStatus;

   Float_t         Lep1MediumIDWeight = 1.0;
   Float_t         Lep2MediumIDWeight = 1.0;
   Float_t         Lep3MediumIDWeight = 1.0;
   Float_t         Lep1TightIDWeight = 1.0;
   Float_t         Lep2TightIDWeight = 1.0;
   Float_t         Lep3TightIDWeight = 1.0;
   Float_t         Lep1MediumIsoWeight = 1.0;
   Float_t         Lep2MediumIsoWeight = 1.0;
   Float_t         Lep3MediumIsoWeight = 1.0;
   Float_t         Lep1TightIsoWeight = 1.0;
   Float_t         Lep2TightIsoWeight = 1.0;
   Float_t         Lep3TightIsoWeight = 1.0;

   Lepton          WLepton;
   Lepton          WNeutrino;
   Lepton          ZLepton1;
   Lepton          ZLepton2;

   Lepton          Lepton1;
   Lepton          Lepton2;
   Lepton          Lepton3;

   Lepton          TruthWLepton;
   Lepton          TruthWNeutrino;
   Lepton          TruthZLepton1;
   Lepton          TruthZLepton2;

   Lepton          TruthLepton1;
   Lepton          TruthLepton2;
   Lepton          TruthLepton3;

   Lepton          CutLepton1;
   Lepton          CutLepton2;
   Lepton          CutLepton3;

   Lepton          WLep;
   Lepton          ZLeadingLep;
   Lepton          ZSubleadingLep;

   Int_t           m_Channel;

   Int_t           passZZCR = 0;
   Int_t           passTopCR = 0;
   Int_t           passZFakeElCR = 0;
   Int_t           passZFakeElCR_UpSys = 0;
   Int_t           passZFakeElCR_DownSys = 0;
   Int_t           passZFakeMuCR = 0;
   Int_t           passTopElCR = 0;
   Int_t           passTopMuCR = 0;
   Int_t           passWZInclusive = 0;
   Int_t           passHardWZInclusive = 0;
   Int_t           passWZInclusiveLoose = 0;
   Int_t           passHardWZInclusiveLoose = 0;
   Int_t           passWZqqSR = 0;
   Int_t           passWZqqCR = 0;
   Int_t           passWZVBSSR = 0;
   Int_t           passWZVBSCR = 0;
   Int_t           passWZInclusiveNoMET = 0;
   Int_t           passTopEnrichCR = 0;
   Int_t           passZjetEnrichCR = 0;
   Int_t           passTTT = 0;
   Int_t           passTTL = 0;
   Int_t           passTLT = 0;
   Int_t           passLTT = 0;
   Int_t           passTLL = 0;
   Int_t           passLTL = 0;
   Int_t           passLLT = 0;
   Int_t           passZCondition = 0;
   Int_t           passWCondition = 0;
   Int_t           passSignalRegion = 0;
   Int_t           pass100SignalRegion = 0;
   Int_t           passHighPtWZCR = 0;
   Int_t           passLowPtZCR = 0;

   Int_t           passTruthMatch1 = 0;
   Int_t           passTruthMatch2 = 0;
   Int_t           passTruthMatch3 = 0;
   Int_t           passZCondition1 = 0;
   Int_t           passZCondition2 = 0;
   Int_t           passZCondition3 = 0;
   Int_t           passWCondition1 = 0;
   Int_t           passWCondition2 = 0;
   Int_t           passWCondition3 = 0;
   Int_t           passMediumID1 = 0;
   Int_t           passMediumID2 = 0;
   Int_t           passMediumID3 = 0;
   Int_t           passTightID1 = 0;
   Int_t           passTightID2 = 0;
   Int_t           passTightID3 = 0;
   Int_t           passIPID1 = 0;
   Int_t           passIPID2 = 0;
   Int_t           passIPID3 = 0;

   Int_t           passDeltaR = 0;
   Int_t           isTauEvent = 0;
   Int_t           passThreeBaseline = 0;

   vector<double>   *PDFWeights;
   vector<double>   *QCDWeights;

   bool isThreeSameCharge = false;

   TString SystematicName;

   virtual void ResetEvent();
};

class loopWZPolarization : public loopMC
{
 public:

 double ZPeakMass = 91.1876;
 double WPeakMass = 80.385;
 double NLOKFactor = 1.0;
 double NLOKFactor_ZZCR = 1.0;
 double NLOKFactor_HighPtZCR = 1.0;
 double NLOKFactor_Signal = 1.0;
 double NLOKFactor_SignalPtWZ = 1.0;
 double NLOKFactor_HighPtWZCR = 1.0;
 double NLOKFactor_LowPtWZCR = 1.0;
 double NLOKFactor_HighR21CR = 1.0;
 double NLOKFactor_LowR21CR = 1.0;

 HistsWZPolarization *myhists;

 TreeForWZPolarization *WZPolarizationTree;
 TreeForPreWZPolarization *PreWZPolarizationTree;

 EventWZPolarization DefaultEvent;
 EventWZPolarization ProcessEvent;
 EventWZPolarization SelectedEvent;
 EventWZPolarization TruthEvent;

 TLorentzVector WBoson;
 TLorentzVector ZBoson;
 TLorentzVector WZPropagator;

 TLorentzVector TruthWBoson;
 TLorentzVector TruthZBoson;
 TLorentzVector TruthWZPropagator;
 TLorentzVector TruthWLepton;
 TLorentzVector TruthWNeutrino;
 TLorentzVector TruthZLepton1;
 TLorentzVector TruthZLepton2;

 int WLeptonCharge;
 int ZLepton1Charge;
 int ZLepton2Charge;

 bool PassID = false;
 bool PassIso = false;
 bool PassTrig = false;
 bool PassTruth = false;
 bool Passd0Sig = false;

 bool passSFOS = false;
 bool passNuPt = false;
 bool passLeadingLepPt = false;
 bool passZZVeto = false;
 bool passMassWindow1 = false;
 bool passMassWindow2 = false;
 bool passMassWindow3 = false;
 bool passMassWindow4 = false;
 bool passZZCR = false;
 bool passTopCR = false;
 bool passZFakeElCR = false;
 bool passZFakeMuCR = false;
 bool passTopElCR = false;
 bool passTopMuCR = false;
 bool passWZInclusive = false;
 bool passHardWZInclusive = false;
 bool passWZInclusiveLoose = false;
 bool passHardWZInclusiveLoose = false;
 bool passWZqqSR = false;
 bool passWZqqCR = false;
 bool passWZVBSSR = false;
 bool passWZVBSCR = false;
 bool passWZInclusiveNoMET = false;
 bool passTopEnrichCR = false;
 bool passTTT = false;
 bool passTTL = false;
 bool passTLT = false;
 bool passLTT = false;
 bool passTLL = false;
 bool passLTL = false;
 bool passLLT = false;
 bool passZCondition = false;
 bool passWCondition = false;

 bool passTruthMatch1 = false;
 bool passTruthMatch2 = false;
 bool passTruthMatch3 = false;
 bool passZCondition1 = false;
 bool passZCondition2 = false;
 bool passZCondition3 = false;
 bool passWCondition1 = false;
 bool passWCondition2 = false;
 bool passWCondition3 = false;
 bool passMediumID1 = false;
 bool passMediumID2 = false;
 bool passMediumID3 = false;
 bool passTightID1 = false;
 bool passTightID2 = false;
 bool passTightID3 = false;
 bool passIPID1 = false;
 bool passIPID2 = false;
 bool passIPID3 = false;

 bool isTauEvent = false;

 vector<int> RootTypes;
 vector<double> CrossSections;
 vector<double> SumOfWeights;
 vector<int> Years;
 map<pair<int, int>, double> SumOfWeightsMap;

 vector<int> UniqueYears;

 TString Flavor = "Unknown";

 map<pair<int, int>, TString> TheoryErrorType;
 vector<double> PDFWeights;
 vector<double> QCDWeights;

 bool doRunPDFAndQCDUnc = false;
 TString ErrorType = "";
 int ErrorSet = 0;

 DataDriven *myFakeRate;
 DataDriven *myFakeRate_ValidationZ;
 DataDriven *myFakeRate_ValidationW;

 TMVAHelper *reader;
 TMVAHelper *readerSR;
 TMVAHelper *readerSR100;

 LWTNNHelper *LwtnnNuPz;
 LWTNNHelper *LwtnnPolClassifier;
 LWTNNHelper *LwtnnNLOPol;


 bool isCut = false;
 bool isRunReweightingFactor = false;

 bool isHaveReweightingFactor = false;
 bool isHaveFakeRate = false;

 bool isNormalizedNLO = true;

 loopWZPolarization(TString RootType);
 virtual void InputHist(HistsWZPolarization* &myhists);
 virtual void InputTree(TreeForWZPolarization *WZPolarizationTree);
 virtual void InputTree(TreeForPreWZPolarization *PreWZPolarizationTree);
 virtual void GetFullFakeMatrix();
 virtual void ReadTree(int ifile);
 virtual void FillHist(EventWZPolarization ProcessEvent);
 virtual void FillTruthHist(EventWZPolarization ProcessEvent);
 virtual void PreRunReweightingFactor(){isRunReweightingFactor = true;}
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopWZPolarization();


 bool isInputPreTree = false;
 map<TString, int> SysNameIndex;
 TString NtupleName;
 int BkgIndex;
 const double GeV = 1000.; //!
 bool OnlyNominal = true;
 bool isNominal = true;
 bool doBkg = false;
 int doFakeRate = 0;
 bool doControlRegion = false;
 bool doTruthSelection = false;

 bool isBDT = false;
 bool isBDTSR = false;
 bool isBDTSR100 = false;
 double BDTScore;
 double BDTScoreSR;
 double BDTScoreSR100;

 bool isLWTNNNuPz = false;
 bool isLWTNNPolClassifier = false;
 bool isLWTNNNLOPol = false;
 double LWTNN_NuPz;

 TString SystematicName = "";
 TString SavedSystematicName = "";
 TString BkgShortName = "";

 double Lumi1516 = 0.0;
 double Lumi17 = 0.0;
 double Lumi18 = 0.0;

 virtual void InputNtupleName(TString NtupleName);
 virtual void PreLoop(int ifile);
 virtual bool FillEvents();
 virtual int FindSysIndex(const char* sysname);
 virtual void DefineSysName();
 virtual void RunAllSystematic();
 virtual void InitialTMVA(TString FileName);
 virtual void InitialTMVASR(TString FileName);
 virtual void InitialTMVASR_NoPtV(TString FileName);
 virtual void InitialTMVASR_OnlyDec(TString FileName);
 virtual void InitialTMVASR100(TString FileName);
 virtual void InitialTMVASR100_NoPtV(TString FileName);
 virtual void InitialTMVASR100_OnlyDec(TString FileName);
 virtual void InitialLWTNNNuPz(TString EvenFile, TString OddFile);
 virtual void InitialLWTNNPolClassifier(TString EvenFile, TString OddFile);
 virtual void InitialLWTNNNLOPol(TString LLFile, TString LTFile, TString TLFile, TString TTFile);

 virtual void GetCutInformation();
 virtual bool PassZZControlRegion(Lepton Lepton1, Lepton Lepton2, Lepton Lepton3, TLorentzVector Neutrino, TString Flavor);
 virtual void FillZLepton1CutFlow();
 virtual void FillZLepton2CutFlow();
 virtual void FillWLeptonCutFlow();
 virtual void FillCutFlow();
 virtual void FillZLepton1WeightedCutFlow();
 virtual void FillZLepton2WeightedCutFlow();
 virtual void FillWLeptonWeightedCutFlow();
 virtual void FillWeightedCutFlow();

 virtual bool TruthSelection();

 virtual bool genTruthLepton(TLorentzVector &ZLepton1, TLorentzVector &ZLepton2, TLorentzVector &WLepton, TLorentzVector &Neutrino);

 ///////////////
 //  Control  //
 ///////////////

 bool JustGenerateTree = false;
 bool FinishProcess = false;
 virtual void ProcessOption(int iflag){
   if(iflag == 1){
     JustGenerateTree = true;
     FinishProcess = false;
   }
   if(iflag == 2){
     JustGenerateTree = false;
     FinishProcess = true;
   }
 }

 long TotalEntriesSys[1000][200];
 long InitialEntrySys[200];
 long NentriesSys[200];
 int RunningSys = 0;
 virtual void InitialSys(int ifile);

 int nFFF = 0;
 set<int> EventNumber;
};
#endif
