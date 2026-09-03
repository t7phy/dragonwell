//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 12 13:54:03 2020 by ROOT version 6.14/04
// from TTree Zeetree/Zeetree
// found on file: Zeetree.root
//////////////////////////////////////////////////////////

#ifndef TreeForWZPolarization_h
#define TreeForWZPolarization_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "TH1D.h"
#include "WZPolarization/HistsWZPolarization.h"
#include "WZPolarization/loopWZPolarization.h"

class loopWZPolarization;
class HistsWZPolarization;
class TreeForWZPolarization;

using namespace std;

class TreeForWZPolarization
{
 public :

   TFile *rootfile[1000];
   TTree *fChain[1000][200];
   long TotalEntries[1000][200];

   vector<TString> RootNames;

   vector<int> RootTypes;
   vector<double> CrossSections;
   vector<double> SumOfWeights;
   int nchannel;
//   double CrossSection;
//   double SumOfWeight;
   map<TString, int> SysNameIndex;
   TString SystematicName = "";
   TString SavedSystematicName = "";

   loopWZPolarization* fLoop;
   HistsWZPolarization* fHist;

   int FirstFile, EndFile;
   bool OneFilePerJob = false;

   bool doFakeRate = true;

// Define for generate a new Tree
   TFile *hf;
   TTree *GenerateTree[1000];

   TH1D* Event_CutFlow;
   TH1D* Electron_CutFlow;
   TH1D* Muon_CutFlow;

   std::map<std::string, double> *Event_CutNameMap; //!
   std::map<std::string, double> *Electron_CutNameMap; //!
   std::map<std::string, double> *Muon_CutNameMap; //!

   TH1D* Event_WeightedCutFlow;
   TH1D* Electron_WeightedCutFlow;
   TH1D* Muon_WeightedCutFlow;

   std::map<std::string, double> *Event_WeightedCutNameMap; //!
   std::map<std::string, double> *Electron_WeightedCutNameMap; //!
   std::map<std::string, double> *Muon_WeightedCutNameMap; //!

   TTree *TruthTree;
   virtual void GenerateFile(TString FileName);
   virtual void DefineTree(int isys, TString TreeName);
   virtual void FillTree(int isys);
   virtual void DefineTruthTree();
   virtual void FillTruthTree();
   virtual void SaveFile();

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Flavor;
   long           EventNumber;
   Int_t           Yields;
   Int_t           isMC;
   Int_t           Channel;
   Int_t           Year;
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
   Int_t           Lep1Flavor;
   Int_t           Lep2Flavor;
   Int_t           Lep3Flavor;
   Int_t           Lep1Charge;
   Int_t           Lep2Charge;
   Int_t           Lep3Charge;
   Int_t           Lep1Ambiguity;
   Int_t           Lep2Ambiguity;
   Int_t           Lep3Ambiguity;
   Float_t         TruthLep1Pt;
   Float_t         TruthLep2Pt;
   Float_t         TruthLep3Pt;
   Float_t         TruthLep1Eta;
   Float_t         TruthLep2Eta;
   Float_t         TruthLep3Eta;
   Float_t         TruthLep1Phi;
   Float_t         TruthLep2Phi;
   Float_t         TruthLep3Phi;
   Int_t           TruthLep1Flavor;
   Int_t           TruthLep2Flavor;
   Int_t           TruthLep3Flavor;
   Float_t         Mpx;
   Float_t         Mpy;
   Float_t         Mpz;
   Float_t         LWTNNNuPz;
   Float_t         TruthNuPz;
   Float_t         LWTNNpLL;
   Float_t         LWTNNpLT;
   Float_t         LWTNNpTL;
   Float_t         LWTNNpTT;
   Float_t         LLNLOWeight;
   Float_t         LTNLOWeight;
   Float_t         TLNLOWeight;
   Float_t         TTNLOWeight;
   Float_t         Lep1WeightZ;
   Float_t         Lep2WeightZ;
   Float_t         Lep3WeightZ;
   Float_t         Lep1WeightW;
   Float_t         Lep2WeightW;
   Float_t         Lep3WeightW;
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
   Float_t         Lep1D0Sig;
   Float_t         Lep2D0Sig;
   Float_t         Lep3D0Sig;


   Float_t         Lep1MediumIDWeight;
   Float_t         Lep2MediumIDWeight;
   Float_t         Lep3MediumIDWeight;
   Float_t         Lep1TightIDWeight;
   Float_t         Lep2TightIDWeight;
   Float_t         Lep3TightIDWeight;
   Float_t         Lep1MediumIsoWeight;
   Float_t         Lep2MediumIsoWeight;
   Float_t         Lep3MediumIsoWeight;
   Float_t         Lep1TightIsoWeight;
   Float_t         Lep2TightIsoWeight;
   Float_t         Lep3TightIsoWeight;

   Int_t           passZZCR;
   Int_t           passTopCR;
   Int_t           passZFakeElCR;
   Int_t           passZFakeElCR_UpSys;
   Int_t           passZFakeElCR_DownSys;
   Int_t           passZFakeMuCR;
   Int_t           passTopElCR;
   Int_t           passTopMuCR;
   Int_t           passWZInclusive;
   Int_t           passHardWZInclusive;
   Int_t           passWZInclusiveLoose;
   Int_t           passHardWZInclusiveLoose;
   Int_t           passWZqqSR;
   Int_t           passWZqqCR;
   Int_t           passWZVBSSR;
   Int_t           passWZVBSCR;
   Int_t           passWZInclusiveNoMET;
   Int_t           passTopEnrichCR;
   Int_t           passTTT;
   Int_t           passTTL;
   Int_t           passTLT;
   Int_t           passLTT;
   Int_t           passTLL;
   Int_t           passLTL;
   Int_t           passLLT;
   Int_t           passZCondition;
   Int_t           passWCondition;
   Int_t           passSignalRegion;
   Int_t           pass100SignalRegion;
   Int_t           passHighPtWZCR;
   Int_t           passLowPtZCR;
   Int_t           isTauEvent;
   Int_t           passTruthMatch1;
   Int_t           passTruthMatch2;
   Int_t           passTruthMatch3;
   Int_t           passZCondition1;
   Int_t           passZCondition2;
   Int_t           passZCondition3;
   Int_t           passWCondition1;
   Int_t           passWCondition2;
   Int_t           passWCondition3;
   Int_t           passMediumID1;
   Int_t           passMediumID2;
   Int_t           passMediumID3;
   Int_t           passTightID1;
   Int_t           passTightID2;
   Int_t           passTightID3;
   Int_t           passIPID1;
   Int_t           passIPID2;
   Int_t           passIPID3;
   Int_t           passDeltaR;
   Int_t           passThreeBaseline;
   Int_t           passZZVeto;
   vector<double>   *PDFWeights;
   vector<double>   *QCDWeights;
   vector<double>   vPDFWeights;
   vector<double>   vQCDWeights;

   // List of branches
   TBranch        *b_Flavor;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_Yields;   //!
   TBranch        *b_isMC;   //!
   TBranch        *b_Channel;   //!
   TBranch        *b_Year;   //!
   TBranch        *b_NormSF;   //!
   TBranch        *b_WeightSign;   //!
   TBranch        *b_WeightNormalized;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_TotalWeight;   //!
   TBranch        *b_WeightNormalizedNoKFactor;   //!
   TBranch        *b_WeightNoKFactor;   //!
   TBranch        *b_TotalWeightNoKFactor;   //!
   TBranch        *b_M_WZ;   //!
   TBranch        *b_M_3l;   //!
   TBranch        *b_Mt_WZ;   //!
   TBranch        *b_M_Z;   //!
   TBranch        *b_Mt_W;   //!
   TBranch        *b_Met;   //!
   TBranch        *b_Njets;   //!
   TBranch        *b_NBjets;   //!
   TBranch        *b_SumOfWeight;   //!
   TBranch        *b_Luminosity;   //!
   TBranch        *b_CrossSection;   //!
   TBranch        *b_Lep1Pt;   //!
   TBranch        *b_Lep2Pt;   //!
   TBranch        *b_Lep3Pt;   //!
   TBranch        *b_Lep1Eta;   //!
   TBranch        *b_Lep2Eta;   //!
   TBranch        *b_Lep3Eta;   //!
   TBranch        *b_Lep1Phi;   //!
   TBranch        *b_Lep2Phi;   //!
   TBranch        *b_Lep3Phi;   //!
   TBranch        *b_Lep1Flavor;   //!
   TBranch        *b_Lep2Flavor;   //!
   TBranch        *b_Lep3Flavor;   //!
   TBranch        *b_Lep1Charge;   //!
   TBranch        *b_Lep2Charge;   //!
   TBranch        *b_Lep3Charge;   //!
   TBranch        *b_Lep1Ambiguity;   //!
   TBranch        *b_Lep2Ambiguity;   //!
   TBranch        *b_Lep3Ambiguity;   //!
   TBranch        *b_TruthLep1Pt;   //!
   TBranch        *b_TruthLep2Pt;   //!
   TBranch        *b_TruthLep3Pt;   //!
   TBranch        *b_TruthLep1Eta;   //!
   TBranch        *b_TruthLep2Eta;   //!
   TBranch        *b_TruthLep3Eta;   //!
   TBranch        *b_TruthLep1Phi;   //!
   TBranch        *b_TruthLep2Phi;   //!
   TBranch        *b_TruthLep3Phi;   //!
   TBranch        *b_TruthLep1Flavor;   //!
   TBranch        *b_TruthLep2Flavor;   //!
   TBranch        *b_TruthLep3Flavor;   //!
   TBranch        *b_Mpx;   //!
   TBranch        *b_Mpy;   //!
   TBranch        *b_Mpz;   //!
   TBranch        *b_LWTNNNuPz;   //!
   TBranch        *b_TruthNuPz;   //!
   TBranch        *b_LWTNNpLL;   //!
   TBranch        *b_LWTNNpLT;   //!
   TBranch        *b_LWTNNpTL;   //!
   TBranch        *b_LWTNNpTT;   //!
   TBranch        *b_LLNLOWeight;   //!
   TBranch        *b_LTNLOWeight;   //!
   TBranch        *b_TLNLOWeight;   //!
   TBranch        *b_TTNLOWeight;   //!
   TBranch        *b_Lep1WeightZ;   //!
   TBranch        *b_Lep2WeightZ;   //!
   TBranch        *b_Lep3WeightZ;   //!
   TBranch        *b_Lep1WeightW;   //!
   TBranch        *b_Lep2WeightW;   //!
   TBranch        *b_Lep3WeightW;   //!
   TBranch        *b_Pt_W;   //!
   TBranch        *b_Pt_Z;   //!
   TBranch        *b_Pt_WZ;   //!
   TBranch        *b_SumJetPt;   //!
   TBranch        *b_CosThetaV;   //!
   TBranch        *b_CosThetaLepW;   //!
   TBranch        *b_CosThetaLepZ;   //!
   TBranch        *b_DY_WZ;   //!
   TBranch        *b_DY_3Z;   //!
   TBranch        *b_DY_3N;   //!
   TBranch        *b_Truth_Pt_WZ;   //!
   TBranch        *b_DeltaPhiLepWLepZ;   //!
   TBranch        *b_DeltaPhiLepWLepZWZFrame;   //!
   TBranch        *b_R21;   //!
   TBranch        *b_WLepPt;   //!
   TBranch        *b_ZLeadingLepPt;   //!
   TBranch        *b_ZSubleadingLepPt;   //!
   TBranch        *b_WLepEta;   //!
   TBranch        *b_ZLeadingLepEta;   //!
   TBranch        *b_ZSubleadingLepEta;   //!
   TBranch        *b_WLepPhi;   //!
   TBranch        *b_ZLeadingLepPhi;   //!
   TBranch        *b_ZSubleadingLepPhi;   //!
   TBranch        *b_Lep1D0Sig;   //!
   TBranch        *b_Lep2D0Sig;   //!
   TBranch        *b_Lep3D0Sig;   //!


   TBranch        *b_Lep1MediumIDWeight;   //!
   TBranch        *b_Lep2MediumIDWeight;   //!
   TBranch        *b_Lep3MediumIDWeight;   //!
   TBranch        *b_Lep1TightIDWeight;   //!
   TBranch        *b_Lep2TightIDWeight;   //!
   TBranch        *b_Lep3TightIDWeight;   //!
   TBranch        *b_Lep1MediumIsoWeight;   //!
   TBranch        *b_Lep2MediumIsoWeight;   //!
   TBranch        *b_Lep3MediumIsoWeight;   //!
   TBranch        *b_Lep1TightIsoWeight;   //!
   TBranch        *b_Lep2TightIsoWeight;   //!
   TBranch        *b_Lep3TightIsoWeight;   //!

   TBranch        *b_passZZCR;   //!
   TBranch        *b_passTopCR;   //!
   TBranch        *b_passZFakeElCR;   //!
   TBranch        *b_passZFakeElCR_UpSys;   //!
   TBranch        *b_passZFakeElCR_DownSys;   //!
   TBranch        *b_passZFakeMuCR;   //!
   TBranch        *b_passTopElCR;   //!
   TBranch        *b_passTopMuCR;   //!
   TBranch        *b_passWZInclusive;   //!
   TBranch        *b_passHardWZInclusive;   //!
   TBranch        *b_passWZInclusiveLoose;   //!
   TBranch        *b_passHardWZInclusiveLoose;   //!
   TBranch        *b_passWZqqSR;   //!
   TBranch        *b_passWZqqCR;   //!
   TBranch        *b_passWZVBSSR;   //!
   TBranch        *b_passWZVBSCR;   //!
   TBranch        *b_passWZInclusiveNoMET;   //!
   TBranch        *b_passTopEnrichCR;   //!
   TBranch        *b_passTTT;   //!
   TBranch        *b_passTTL;   //!
   TBranch        *b_passTLT;   //!
   TBranch        *b_passLTT;   //!
   TBranch        *b_passTLL;   //!
   TBranch        *b_passLTL;   //!
   TBranch        *b_passLLT;   //!
   TBranch        *b_passZCondition;   //!
   TBranch        *b_passWCondition;   //!
   TBranch        *b_passSignalRegion;   //!
   TBranch        *b_pass100SignalRegion;   //!
   TBranch        *b_passHighPtWZCR;   //!
   TBranch        *b_passLowPtZCR;   //!
   TBranch        *b_isTauEvent;   //!
   TBranch        *b_passTruthMatch1;   //!
   TBranch        *b_passTruthMatch2;   //!
   TBranch        *b_passTruthMatch3;   //!
   TBranch        *b_passZCondition1;   //!
   TBranch        *b_passZCondition2;   //!
   TBranch        *b_passZCondition3;   //!
   TBranch        *b_passWCondition1;   //!
   TBranch        *b_passWCondition2;   //!
   TBranch        *b_passWCondition3;   //!
   TBranch        *b_passMediumID1;   //!
   TBranch        *b_passMediumID2;   //!
   TBranch        *b_passMediumID3;   //!
   TBranch        *b_passTightID1;   //!
   TBranch        *b_passTightID2;   //!
   TBranch        *b_passTightID3;   //!
   TBranch        *b_passIPID1;   //!
   TBranch        *b_passIPID2;   //!
   TBranch        *b_passIPID3;   //!
   TBranch        *b_passDeltaR;   //!
   TBranch        *b_passThreeBaseline;   //!
   TBranch        *b_passZZVeto;   //!
   TBranch        *b_PDFWeights;   //!
   TBranch        *b_QCDWeights;   //!

   TreeForWZPolarization();
   virtual ~TreeForWZPolarization();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void CloseFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual int GetRootType(TString RootName);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, int isys, long i);
   virtual void LinkHist(HistsWZPolarization* myhists);
   virtual void Init();

   bool doRunPDFAndQCDUnc = false;
   TString ErrorType = "";
   int ErrorSet = 0;
   virtual void RunPDFAndQCDUnc(TString ErrorType, int ErrorSet){
     doRunPDFAndQCDUnc = true;
     this->ErrorType = ErrorType;
     this->ErrorSet = ErrorSet;
   }

   virtual void updateCutFlow(TH1D *inCutFlow, std::map<std::string, double> *inLabelMap, std::string cutName, double step = 1, bool doUpdate = true); //!

};

#endif
