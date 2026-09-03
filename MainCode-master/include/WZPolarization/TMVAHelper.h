#ifndef TMVAHelper_h
#define TMVAHelper_h

#include "RootCommon.h"

#ifdef USE_TMVA
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#endif

#include "WZPolarization/TreeForWZPolarization.h"

class TreeForWZPolarization;

class TMVAHelper
{
 public:

 TreeForWZPolarization *WZPolarizationTree;

#ifdef USE_TMVA
 TMVA::Reader *reader;
#endif

 Float_t       CosThetaVAbs;
 Float_t       logM_WZ;
 Float_t       logM_Z;
 Float_t       logMet;
 Float_t       logMt_W;
 Float_t       logMt_WZ;
 Float_t       logPt_W;
 Float_t       logPt_Z;
 Float_t       R21;
 Float_t       logPt_WZ;
 Float_t       M_Z;
 Float_t       ZRapidityAbs;
 Float_t       Lep1EtaAbs;
 Float_t       Lep1PhiAbs;
 Float_t       logLep1Pt;
 Float_t       Lep2EtaAbs;
 Float_t       Lep2PhiAbs;
 Float_t       logLep2Pt;
 Float_t       Lep3EtaAbs;
 Float_t       Lep3PhiAbs;
 Float_t       logLep3Pt;
 Float_t       CosThetaLepWAbs;
 Float_t       CosThetaLepZAbs;
 Float_t       DeltaPhi_LepW_Met_Abs;
 Float_t       DeltaPhiLepWLepZ_Abs;
 Float_t       DeltaPhiLepWLepZWZFrame_Abs;
 Float_t       DeltaPhi_Lep1_Lep2_Abs;
 Float_t       DY_3Z_Abs;
 Float_t       DY_WZ_Abs;
 Float_t       DY_3N_Abs;

 Float_t       logWLepPt;
 Float_t       logZLeadingLepPt;
 Float_t       logZSubleadingLepPt;
 Float_t       logZSubleadingLepPt2p6;
 Float_t       WLepEta;
 Float_t       ZLeadingLepEta;
 Float_t       ZSubleadingLepEta;
 Float_t       WLepPhi;
 Float_t       ZLeadingLepPhi;
 Float_t       ZSubleadingLepPhi;

 Float_t       TotalWeightNoKFactor;
 Int_t         passHardWZInclusive;

 Int_t         EventNumber;
 Float_t       Weight;

 TMVAHelper();
 virtual void InputTree(TreeForWZPolarization *WZPolarizationTree);
 virtual void BookMVA(TString FileName);
 virtual void CalVariable();
 virtual void AddVariable();
 virtual double EvaluateMVA();

 virtual void AddVariableSR();
 virtual void AddVariableSR_NoPtV();
 virtual void AddVariableSR_OnlyDec();
 virtual void AddVariableSR100();
 virtual void AddVariableSR100_NoPtV();
 virtual void AddVariableSR100_OnlyDec();

};

#endif
