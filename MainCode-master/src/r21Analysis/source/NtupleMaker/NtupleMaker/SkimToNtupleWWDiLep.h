#ifndef NtupleMaker_SkimToNtupleWWDiLep_H
#define NtupleMaker_SkimToNtupleWWDiLep_H

//xAOD accessor
#include "NtupleMaker/SelectionWW.h"

class SkimToNtupleWWDiLep : public SelectionWW
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:

  int detectorRegion;
  int m_isTest;
  int systemCode;
  int doOutAOD;

  TFile *outputFile;
  TTree* tree;

  std::string outputName;
  int maxSys;

  TTree *metaTree; //!
  TTree *treeAna; //!
  TTree *TruthTree; //!
  std::ofstream vlook; //!


  // meta branches
  Long64_t runNumber; //!
  Long64_t mcChannelNumber; //!
  std::string AODname; //!
  double sumOfWeights; //!
  double crossSection; //!


  // event branches
  std::string Systematic; //!
  Long64_t EventNumber; //!
  Long64_t RunNumber; //!
  Long64_t OriginRunNumber; //!
  Long64_t ChannelNumber; //!
  int isTrigMatched; //!
  int TriggerPassed; //!

  float AverageMu; //! 
  float MCEventWeight; //!
  std::vector<float> MCEventWeights; //!
  float MCPileupWeight; //!
  float JetWeight; //!
  float KFactor; //!

  float met_et; //!
  float met_px; //!
  float met_py; //!

  int nSoftMuons; //!
  int nSoftElectrons; //!
  int nSoftJets; //!

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

  std::vector<float> el_e; //!
  std::vector<float> el_eta; //!
  std::vector<float> el_cl_eta; //!
  std::vector<float> el_phi; //!
  std::vector<float> el_pt; //!
  std::vector<float> el_charge; //!
  std::vector<float> el_d0Sig; //!
  std::vector<int> el_truthMatched; //!
  std::vector<int> el_mediumID; //!
  std::vector<float> el_mediumIDWeight; //!
  std::vector<int> el_tightID; //!
  std::vector<float> el_tightIDWeight; //!
  std::vector<int> el_FCLooseIso; //!
  std::vector<float> el_FCLooseIsoWeight; //!
  std::vector<int> el_FCTightIso; //!
  std::vector<float> el_FCTightIsoWeight; //!
  std::vector<int> el_FCHighPtIso; //!
  std::vector<float> el_FCHighPtIsoWeight; //!
  std::vector<int> el_triggerMatched; //!
  std::vector<float> el_recoWeight; //!
  std::vector<int> el_isbaseline; //!
  std::vector<int> el_isAmbiguity; //!

  std::vector<float> mu_e; //!
  std::vector<float> mu_eta; //!
  std::vector<float> mu_phi; //!
  std::vector<float> mu_pt; //!
  std::vector<float> mu_charge; //!
  std::vector<float> mu_d0Sig; //!
  std::vector<int> mu_truthMatched; //!
  std::vector<int> mu_mediumID; //!
  std::vector<float> mu_mediumIDWeight; //!
  std::vector<int> mu_tightID; //!
  std::vector<float> mu_tightIDWeight; //!
  std::vector<int> mu_FCLooseIso; //!
  std::vector<float> mu_FCLooseIsoWeight; //!
  std::vector<int> mu_FCTightIso; //!
  std::vector<float> mu_FCTightIsoWeight; //!
  std::vector<int> mu_PflowLooseIso; //!
  std::vector<float> mu_PflowLooseIsoWeight; //!
  std::vector<int> mu_PflowTightIso; //!
  std::vector<float> mu_PflowTightIsoWeight; //!
  std::vector<int> mu_triggerMatched; //!
  std::vector<float> mu_IPWeight; //!
  std::vector<int> mu_isbaseline; //!

  std::vector<float> jt_e; //!
  std::vector<float> jt_eta; //!
  std::vector<float> jt_phi; //!
  std::vector<float> jt_pt; //!
  std::vector<int> jt_passJVT; //!
  std::vector<int> jt_passBtag; //!

  std::vector<float> truth_e;
  std::vector<float> truth_eta;
  std::vector<float> truth_phi;
  std::vector<float> truth_pt;
  std::vector<int> truth_pid;
  std::vector<int> truth_mid;

  std::vector<float> full_truth_e;
  std::vector<float> full_truth_eta;
  std::vector<float> full_truth_phi;
  std::vector<float> full_truth_pt;
  std::vector<int> full_truth_pid;
  std::vector<int> full_truth_mid;

  float truthPropagator_px = 0;
  float truthPropagator_py = 0;
  float truthPropagator_pz = 0;
  float truthPropagator_e = 0;

  bool ShouldRecord(void); //!
  void SetupBranches(TTree* tree); //!
  void SetupTruthBranches(TTree* tree); //!
  void ResetEvent(void); //!
  void Record_Object(const xAOD::IParticle* par,  std::string flavor); //!
  bool SkipSystematic(void);

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:
  // this is a standard constructor
  SkimToNtupleWWDiLep (const std::string& name, ISvcLocator* pSvcLocator); // constructor for release 21

  virtual bool init(void);
  virtual bool loop(void);
  virtual StatusCode finish(void);

};
#endif
