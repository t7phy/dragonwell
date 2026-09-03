#ifndef NtupleMaker_SkimToNtupleFwdReco_H
#define NtupleMaker_SkimToNtupleFwdReco_H

//xAOD accessor
#include "NtupleMaker/SelectionFwdReco.h"

class SkimToNtupleFwdReco : public SelectionFwdReco
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  int detectorRegion;
  int m_isTest;
  int systemCode;
  int doOutAOD;

  std::string jetType = "AntiKt4EMTopoJets";

  TFile *outputFile;
  TTree* tree;

  std::string outputName;
  int maxSys;

  TTree *metaTree; //!
  std::ofstream vlook; //!

  std::vector<TTree*> *treeAnaSys; //!

  // meta branches
  Long64_t runNumber; //!
  Long64_t mcChannelNumber; //!
  std::string AODname; //!
  double sumOfWeights; //!
  double crossSection; //!

  // event branches
  Long64_t EventNumber; //!
  Long64_t RunNumber; //!
  Long64_t OriginRunNumber; //!
  Long64_t ChannelNumber; //!
  int isTrigMatched; //!
  int TriggerPassed; //!

  int nSoftMuons; //!
  int nSoftElectrons; //!

  int nGoodMuons; //!
  int nGoodElectrons; //!
  int nGoodPhotons; //!
  int nGoodJets; //!
  int nGoodFwdJets; //!
  int nGoodFwdElectrons; //!

  int nBaselineMuons; //!
  int nBaselineElectrons; //!
  int nBaselinePhotons; //!
  int nBaselineJets; //!
  int nBaselineFwdElectrons; //!

  float AverageMu; //! 
  float MCEventWeight; //!
  float MCPileupWeight; //!
  float Weight; //!
  float JetWeight; //!
  float TrigWeight; //!

  float met_et; //!
  float met_px; //!
  float met_py; //!

  int Sta_TotalNumber = 0;

  int EventRegion;

  TLorentzVector RecoElectron;
  TLorentzVector RecoFwdElectron;

  bool isRecoElectron = false;
  bool isRecoFwdElectron = false;

  bool isTruthElectron = false;

  std::vector<float> fwdel_e; //!
  std::vector<float> fwdel_eta; //!
  std::vector<float> fwdel_phi; //!
  std::vector<float> fwdel_pt; //!
  std::vector<float> fwdel_clpt; //!
  std::vector<int> fwdel_PassPtCut;
  std::vector<int> fwdel_truthMatched; //!

  std::vector<float> fwdel_corrected_e; //!
  std::vector<float> fwdel_corrected_eta; //!
  std::vector<float> fwdel_corrected_phi; //!
  std::vector<float> fwdel_corrected_pt; //!
  std::vector<float> fwdel_corrected_clpt; //!
  std::vector<int> fwdel_corrected_PassPtCut;
  std::vector<int> fwdel_corrected_truthMatched; //!

  std::vector<float> el_e; //!
  std::vector<float> el_eta; //!
  std::vector<float> el_phi; //!
  std::vector<float> el_pt; //!
  std::vector<float> el_clpt; //!

  std::vector<float> truthel_e; //!
  std::vector<float> truthel_eta; //!
  std::vector<float> truthel_phi; //!
  std::vector<float> truthel_pt; //!
  std::vector<float> truthel_et; //!
  std::vector<float> truthel_deltaE;
  std::vector<float> truthel_deltaPt;
  std::vector<float> truthel_deltaEt;
  std::vector<int> truthel_Region; //!
  std::vector<int> truthel_truthMatched; //!
  std::vector<int> truthel_truthMatchedAfterCut; //!

  double deltaE;
  double deltaPt;
  double deltaEt;

  void SetupBranches(TTree* tree); //!
  void ResetEvent(void); //!
  void Record_Object(const xAOD::IParticle* par,  std::string flavor); //!
  void outputCaloInfo(xAOD::Electron *fwdel); //!

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:
  // this is a standard constructor
  SkimToNtupleFwdReco (const std::string& name, ISvcLocator* pSvcLocator); // constructor for release 21

  virtual bool init(void);
  virtual bool loop(void);
  virtual StatusCode finish(void);

};
#endif
