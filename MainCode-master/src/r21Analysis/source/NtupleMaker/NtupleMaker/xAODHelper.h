#ifndef NtupleMaker_xAODHelper_H
#define NtupleMaker_xAODHelper_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <xAODEventInfo/EventInfo.h>
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/TStore.h"
#include "xAODRootAccess/tools/Message.h"

#include "xAODBase/IParticleContainer.h"
#include "xAODBase/IParticleHelpers.h"

#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include "EventLoop/OutputStream.h"
#include <EventLoop/Algorithm.h>

#include <AsgTools/AnaToolHandle.h>
#include "AsgTools/AsgTool.h"
#include "AsgTools/AnaToolHandle.h"

#include <xAODCore/ShallowAuxContainer.h>
#include <xAODCore/ShallowCopy.h>
#include <xAODCore/AuxContainerBase.h>

#include <TSystem.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <vector>
#include "TLorentzVector.h"

#include "PathResolver/PathResolver.h"

#include <PATInterfaces/CorrectionCode.h>



///////////////////
////  Objects  ////
///////////////////



// Electron
#include "xAODEgamma/Electron.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/ElectronAuxContainer.h"
#include "xAODEgamma/Egamma.h"
#include "xAODEgamma/EgammaxAODHelpers.h"

// Muon
#include "xAODMuon/Muon.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODMuon/MuonAuxContainer.h"

// Photon Information
#include "xAODEgamma/PhotonContainer.h"

// Jet Information
#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"
#include "xAODJet/Jet.h"

// Tau Information
#include "xAODTau/TauJetContainer.h"

// track and vertex
#include "xAODTracking/VertexContainer.h"
#include "xAODTracking/TrackParticlexAODHelpers.h"
#include "xAODTracking/TrackParticle.h"

// missing ET
#include "xAODMissingET/MissingETAuxContainer.h"
#include "xAODMissingET/MissingETAssociationMap.h"
#include "xAODMissingET/MissingETContainer.h"

// truth
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthEvent.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthParticleContainer.h"



////////////////////
////  CP Tools  ////
////////////////////



// Electron Calibration
#include "ElectronPhotonFourMomentumCorrection/EgammaCalibrationAndSmearingTool.h"

// Electron ID
#include "ElectronPhotonSelectorTools/AsgElectronIsEMSelector.h"
#include "ElectronPhotonSelectorTools/AsgElectronLikelihoodTool.h"
#include "ElectronPhotonSelectorTools/AsgForwardElectronIsEMSelector.h"
#include "ElectronPhotonSelectorTools/AsgForwardElectronLikelihoodTool.h"
#include "ElectronPhotonSelectorTools/AsgElectronChargeIDSelectorTool.h"

// ElectronEfficiencyCorrections
#include "ElectronEfficiencyCorrection/AsgElectronEfficiencyCorrectionTool.h"
#include "EgammaAnalysisInterfaces/IAsgElectronEfficiencyCorrectionTool.h"

// EGammaAmbiguity
#include "ElectronPhotonSelectorTools/EGammaAmbiguityTool.h"

// Gamma shower shape shift
#include "ElectronPhotonShowerShapeFudgeTool/ElectronPhotonShowerShapeFudgeTool.h"

// Gamma ID
#include "ElectronPhotonSelectorTools/AsgPhotonIsEMSelector.h"


// Muon Corrections and ID
#include <MuonAnalysisInterfaces/IMuonCalibrationAndSmearingTool.h>
//#include "MuonMomentumCorrections/MuonCalibrationAndSmearingTool.h"
#include <MuonAnalysisInterfaces/IMuonSelectionTool.h>
//#include "MuonSelectorTools/MuonSelectionTool.h"

// MuonEfficiencyCorrections
#include "MuonEfficiencyCorrections/MuonEfficiencyScaleFactors.h"

// MuonTriggerCorr
#include "MuonEfficiencyCorrections/MuonTriggerScaleFactors.h"

// Jet Combined Performance
//#include "JetCalibTools/JetCalibrationTool.h"
#include "JetCalibTools/IJetCalibrationTool.h"
//#include "JetMomentTools/JetVertexTaggerTool.h"
//#include "JetMomentTools/IJetUpdateJvt.h"
#include "JetInterface/IJetUpdateJvt.h"
#include "JetInterface/IJetModifier.h"
#include "JetSelectorTools/JetCleaningTool.h"
#include "JetSelectorTools/EventCleaningTool.h"
#include "JetResolution/JERTool.h"
#include "JetResolution/JERSmearingTool.h"
#include <JetResolution/IJERTool.h>
#include "JetUncertainties/JetUncertaintiesTool.h"
#include <JetInterface/IJetSelector.h>

// jvt efficiency
#include "JetJvtEfficiency/JetJvtEfficiency.h"

// B-tagging
#include "xAODBTaggingEfficiency/BTaggingSelectionTool.h"
#include "xAODBTaggingEfficiency/BTaggingEfficiencyTool.h"
#include "xAODBTagging/BTagging.h"

// Missing Et
#include "METUtilities/METSystematicsTool.h"
#include "METUtilities/METMaker.h"
#include "METUtilities/CutsMETMaker.h"
#include "METUtilities/METHelpers.h"
#include "METInterface/IMETSystematicsTool.h"
#include "METInterface/IMETMaker.h"

// Isolation
#include "IsolationSelection/IsolationSelectionTool.h"



///////////////////////
////  event level  ////
///////////////////////



// GRL
//#include "GoodRunsLists/GoodRunsListSelectionTool.h"
#include <AsgAnalysisInterfaces/IGoodRunsListSelectionTool.h>

// pileup reweighting
//#include "PileupReweighting/PileupReweightingTool.h"
#include "AsgAnalysisInterfaces/IPileupReweightingTool.h"

// Trigger
#include "TrigConfxAOD/xAODConfigTool.h"
#include <TrigConfInterfaces/ITrigConfigTool.h>
#include "TrigDecisionTool/TrigDecisionTool.h"
#include "TriggerMatchingTool/IMatchingTool.h"
#include "TriggerMatchingTool/MatchingTool.h"

// CrossSection
#include "PMGAnalysisInterfaces/IPMGCrossSectionTool.h"
#include "PMGTools/PMGCrossSectionTool.h"
#include "PMGTools/PMGTruthWeightTool.h"


//////////////////
////  others  ////
//////////////////



//systematics
#include "PATInterfaces/ISystematicsTool.h"
#include "PATInterfaces/SystematicVariation.h"
#include <PATInterfaces/SystematicsUtil.h>
#include "PATInterfaces/SystematicRegistry.h"

//OverLap removal
//#include "AssociationUtils/ORToolBox.h"
//#include "AssociationUtils/OverlapRemovalInit.h"
//#include "AssociationUtils/OverlapRemovalTool.h"
//#include "AssociationUtils/EleJetOverlapTool.h"
//#include "AssociationUtils/MuJetOverlapTool.h"
#include "AssociationUtils/OverlapRemovalInit.h"
#include "AssociationUtils/OverlapRemovalDefs.h"
#include "AssociationUtils/IOverlapRemovalTool.h"

// calo info
#include <CaloGeoHelpers/CaloSampling.h>

//cut book keeper
#include "xAODCutFlow/CutBookkeeperContainer.h"
#include "xAODCutFlow/CutBookkeeper.h"

//I don't know what the hell it is
#include "TrigBunchCrossingTool/WebBunchCrossingTool.h"
#include "TrigBunchCrossingTool/StaticBunchCrossingTool.h"

// moximoxi?
#include "MCUtils/PIDUtils.h"

/// Helper macro for checking xAOD::TReturnCode return values
#define EL_RETURN_CHECK( CONTEXT, EXP )                     \
  do {                                                     \
  if( ! EXP.isSuccess() ) {                             \
  Error( CONTEXT,                                    \
    XAOD_MESSAGE( "Failed to execute: %s" ),    \
         #EXP );                                     \
  return StatusCode::FAILURE;                    \
  }                                                     \
  } while( false )

#define AFFECT_CHECK( TOOL, VARI )                     \
  VARI.empty()?true:TOOL->isAffectedBySystematic(*(VARI.begin())) \


class xAODHelper : public EL::AnaAlgorithm
{
public:

  std::ofstream look; //!

  int m_eventCounter; //!
  uint32_t t_runNumber; //!
  uint32_t t_mcChannelNumber; //!
  uint64_t t_nEventsProcessed  ; //!
  double t_sumOfWeights        ; //!
  double t_sumOfWeightsSquared ; //!
  double t_crossSection ; //!
  std::string t_AODname ; //!
//  std::string t_filename ; //!

  std::vector<uint32_t> *vec_runNumber; //!
  std::vector<uint32_t> *vec_mcChannelNumber; //!
  std::vector<double> *vec_sumOfWeights; //!
  std::vector<double> *vec_sumOfEvents; //!
  std::vector<double> *vec_crossSection; //!
  std::vector<std::string> *vec_AODname; //!

  TH1D *totalWeightedEntries; //!

  //==========xAOD objects============
  xAOD::TEvent* event; //!
  xAOD::TStore* m_store; //!
  const xAOD::EventInfo* eventInfo; //!
  const xAOD::VertexContainer* vxContainer; //!

  const xAOD::ElectronContainer* els; //!
  const xAOD::ElectronContainer* fwdels; //!
  const xAOD::MuonContainer* muons; //!
  const xAOD::JetContainer* jets; //!
  const xAOD::JetContainer* jetsBdecor; //!
  const xAOD::TruthParticleContainer* xTruthParticleContainer; //!
  const xAOD::JetContainer* Tjets; //!

  TLorentzVector truthPropagator; //!
  std::vector<TLorentzVector> truthParticleList; //!
  unsigned long long pdgSequence; //!


  xAOD::ElectronContainer* elsCorr = 0; //!
  xAOD::ElectronContainer* fwdelsCorr = 0; //!
  xAOD::MuonContainer* muonsCorr = 0; //!
  xAOD::JetContainer* jetsCorr = 0; //!
  TLorentzVector* metsCorr; //!

  xAOD::ElectronContainer* elsNominal = 0; //!
  xAOD::ElectronContainer* fwdelsNominal = 0; //!
  xAOD::MuonContainer* muonsNominal = 0; //!
  xAOD::JetContainer* jetsNominal = 0; //!
  TLorentzVector* metsNominal; //!

  std::map<double, xAOD::Muon *> *muonMap; //!
  std::map<double, xAOD::Electron *> *electronMap; //!
  std::map<double, xAOD::Electron *> *fwdelectronMap; //!
  std::map<double, xAOD::Jet *> *jetMap; //!

  std::map<double, xAOD::Muon *> *muonMapNominal; //!
  std::map<double, xAOD::Electron *> *electronMapNominal; //!
  std::map<double, xAOD::Electron *> *fwdelectronMapNominal; //!
  std::map<double, xAOD::Jet *> *jetMapNominal; //!


  uint32_t RunNum = 0; //!
//  unsigned int RunNum = 0; //!
  unsigned long long EvtNum = 0; //!

  int nRecoEl; //!
  int nRecoFwdEl; //!
  int nRecoMu; //!
  int nRecoJet; //!

  bool isPassEvent = true;
  bool isPassJetCleaning = true;
  bool isPassVTX = true;
  bool isPassTrigger = true;
  std::vector<std::string> WeightNames;

  //==========xAOD tools==============

  std::string jetType = "AntiKt4EMPFlowJets"; //!
//  std::string jetType = "AntiKt4EMTopoJets";
  std::string jetTypeBtag = "AntiKt4EMPFlowJets_BTagging201903"; //!
//  std::string jetTypeBtag = "AntiKt4EMTopoJets";
  std::string jetKey = "AntiKt4EMPFlow"; //!
  std::string coreMetKey = "MET_Core_AntiKt4EMPFlow"; //!
  std::string metAssocKey = "METAssoc_AntiKt4EMPFlow"; //!

  const xAOD::MissingETContainer* coreMet  = nullptr;//!
  const xAOD::MissingETAssociationMap* metMap = nullptr;//!

  const double GeV = 1000.; //!
  const double MuonPDGMass = 105.658367e-3; //!
  const double pi = 3.14159; //!

  int isMC;
  int Region;
  int isFlawless;
  std::string mcVersion;
  std::string Year;
  std::string SysFilter;
  bool doOnce; //!
  Long64_t m_Year; //!


  const std::string m_inputTag = "preORselected";
  const std::string m_outputTag = "isOR";

//  const std::string OR_inputTag = "baseline"; //!
  const std::string OR_inputTag = "MatrixLepton"; //!
  const std::string OR_outputTag = "overlaps";  //!
  const std::string Additional_OR_Tag = "AdditionalOverlaps";  //!

  int Sta_TotalNumber = 0;


///////////////////////
////  event level  ////
///////////////////////



//  GoodRunsListSelectionTool *m_grl; //!
  asg::AnaToolHandle<IGoodRunsListSelectionTool> m_grl; //!

  //pileup reweighting
//  CP::PileupReweightingTool *m_prwTool; //!
//  ToolHandle<CP::IPileupReweightingTool> m_prwTool; //!
  asg::AnaToolHandle<CP::IPileupReweightingTool> m_prwTool; //!

  //triggers
  asg::AnaToolHandle<Trig::TrigDecisionTool> m_TrigDecTool; //!
  asg::AnaToolHandle<TrigConf::ITrigConfigTool> m_TrigConfigTool; //!
//  TrigConf::xAODConfigTool *m_TrigConfigTool; //!
//  Trig::TrigDecisionTool *m_TrigDecTool; //!

  //trigger matching
//  Trig::MatchingTool *m_trigMatch; //!
  asg::AnaToolHandle<Trig::IMatchingTool> m_trigMatch; //!
//  ToolHandle<Trig::IMatchingTool> m_trigMatch; //!



//////////////////////////
////  Electron Gamma  ////
//////////////////////////



  // Electron ID 
  AsgElectronLikelihoodTool *m_ElectronIDToolTight; //!
  AsgElectronLikelihoodTool *m_ElectronIDToolMedium; //!
  AsgElectronLikelihoodTool *m_ElectronIDToolLoose; //!

  //Forward Electron ID
  AsgForwardElectronIsEMSelector *m_FwdElectronIDToolTight; //!
  AsgForwardElectronIsEMSelector *m_FwdElectronIDToolMedium; //!
  AsgForwardElectronIsEMSelector *m_FwdElectronIDToolLoose; //!
  AsgForwardElectronLikelihoodTool *m_FwdElectronLikelihoodToolTight; //!
  AsgForwardElectronLikelihoodTool *m_FwdElectronLikelihoodToolMedium; //!
  AsgForwardElectronLikelihoodTool *m_FwdElectronLikelihoodToolLoose; //!

  //charge flip ID
  AsgElectronChargeIDSelectorTool* ECIDSTool; //!

  // Egamma calibration
  CP::EgammaCalibrationAndSmearingTool *m_EleCalibTool; //!
  CP::EgammaCalibrationAndSmearingTool *m_PhoCalibTool; //!

  //egammaAmbiguity
  EGammaAmbiguityTool *m_egammaAmbiguityTool; //!

  //gamma shower shape
  ElectronPhotonShowerShapeFudgeTool* m_fudgeMCTool; //!

  //Gamma ID
  AsgPhotonIsEMSelector* m_photonTightIsEMSelector; //!

  //ElectronEfficiencyCorrection
  AsgElectronEfficiencyCorrectionTool* m_recoEgCorrections; //!
  AsgElectronEfficiencyCorrectionTool* m_idEgCorrections2; //!
  AsgElectronEfficiencyCorrectionTool* m_idEgCorrections3; //!
  AsgElectronEfficiencyCorrectionTool* m_idFwdEgCorrections1; //!
  AsgElectronEfficiencyCorrectionTool* m_idFwdEgCorrections2; //!
  AsgElectronEfficiencyCorrectionTool* m_idFwdEgCorrections3; //!
  AsgElectronEfficiencyCorrectionTool* m_trigEgCorrections1; //!
  AsgElectronEfficiencyCorrectionTool* m_trigEgEfficienciesMC1; //!
  AsgElectronEfficiencyCorrectionTool* m_trigEgCorrections2; //!
  AsgElectronEfficiencyCorrectionTool* m_trigEgEfficienciesMC2; //!
  AsgElectronEfficiencyCorrectionTool* m_trigEgCorrections3; //!
  AsgElectronEfficiencyCorrectionTool* m_trigEgEfficienciesMC3; //!
  AsgElectronEfficiencyCorrectionTool* m_trigEgCorrections4; //!
  AsgElectronEfficiencyCorrectionTool* m_trigEgEfficienciesMC4; //!
  AsgElectronEfficiencyCorrectionTool* m_isoEgCorrections0; //!
  AsgElectronEfficiencyCorrectionTool* m_isoEgCorrections1; //!
  AsgElectronEfficiencyCorrectionTool* m_isoEgCorrections2; //!
  AsgElectronEfficiencyCorrectionTool* m_isoEgCorrections3; //!
  AsgElectronEfficiencyCorrectionTool* m_isoEgCorrections4; //!
  AsgElectronEfficiencyCorrectionTool* m_isoEgCorrections5; //!
  AsgElectronEfficiencyCorrectionTool* m_isoEgCorrections6; //!
  AsgElectronEfficiencyCorrectionTool* m_isoEgCorrections7; //!
  AsgElectronEfficiencyCorrectionTool* m_isoEgCorrections8; //!
  AsgElectronEfficiencyCorrectionTool* m_isoEgCorrections9; //!
  AsgElectronEfficiencyCorrectionTool* m_isoEgCorrections10; //!
  AsgElectronEfficiencyCorrectionTool* m_chargeEgCorrections; //!
//  asg::AnaToolHandle<IAsgElectronEfficiencyCorrectionTool> m_chargeEgCorrections; //!



////////////////
////  Muon  ////
////////////////



  // MuonCalibrationAndSmearing and Selection
//  CP::MuonCalibrationAndSmearingTool *m_muonCalibrationAndSmearingTool; //! 
  asg::AnaToolHandle<CP::IMuonCalibrationAndSmearingTool> m_muonCalibrationAndSmearingTool; //!
  asg::AnaToolHandle<CP::IMuonSelectionTool> m_muonSelectionTight; //! 
  asg::AnaToolHandle<CP::IMuonSelectionTool> m_muonSelectionMedium; //! 
  asg::AnaToolHandle<CP::IMuonSelectionTool> m_muonSelectionLoose; //! 
  asg::AnaToolHandle<CP::IMuonSelectionTool> m_muonSelectionHighPt; //! 
//  CP::MuonSelectionTool *m_muonSelectionTight; //!
//  CP::MuonSelectionTool *m_muonSelectionMedium; //!
//  CP::MuonSelectionTool *m_muonSelectionLoose; //!

  //MuonEfficiencyScaleFactors
  CP::MuonEfficiencyScaleFactors* m_effi_corr1; //!
  CP::MuonEfficiencyScaleFactors* m_effi_corr2; //!
  CP::MuonEfficiencyScaleFactors* m_effi_corr3; //!

  //MuonIsolationScaleFactor
  CP::MuonEfficiencyScaleFactors* m_iso_effi_corr1; //!
  CP::MuonEfficiencyScaleFactors* m_iso_effi_corr2; //!
  CP::MuonEfficiencyScaleFactors* m_iso_effi_corr3; //!
  CP::MuonEfficiencyScaleFactors* m_iso_effi_corr4; //!
  CP::MuonEfficiencyScaleFactors* m_iso_effi_corr5; //!
  CP::MuonEfficiencyScaleFactors* m_iso_effi_corr6; //!
  CP::MuonEfficiencyScaleFactors* m_iso_effi_corr7; //!

  //MuonIpScaleFactor
  CP::MuonEfficiencyScaleFactors* m_ip_effi_corr; //!

  //MuonTriggerScaleFactors
  CP::MuonTriggerScaleFactors* m_mutrig_sf; //!  
  CP::MuonTriggerScaleFactors* m_mutrig_sf_m; //! 



////////////////
////  jets  ////
////////////////



  //JetCalibration
//  JetCalibrationTool *m_jetCalibration; //!
  asg::AnaToolHandle<IJetCalibrationTool> m_jetCalibration; //!

  //JetUncertainty
  JetUncertaintiesTool *m_jesUncert; //!

  //JER
  JERTool *m_jerTool; //!
  JERSmearingTool *m_smearTool; //!
//  asg::AnaToolHandle<IJERTool> m_JERTool; //! 

  //JetVertexTagger
//  JetVertexTaggerTool* m_pjvtag; //!
//  ToolHandle<IJetUpdateJvt>* m_hjvtagup; //!
  asg::AnaToolHandle<IJetUpdateJvt> m_pjvtag; //!
  asg::AnaToolHandle<IJetModifier> m_jetmod; //!

  //JetCleaning
//  JetCleaningTool* m_cleaningTool; //! 
  asg::AnaToolHandle<IJetSelector> m_cleaningTool; //!
  JetCleaningTool *jcTool; //!
  ECUtils::EventCleaningTool *m_EventCleaningTool; //!

  //jvt efficiency
  CP::JetJvtEfficiency *jvtsf; //!
  CP::JetJvtEfficiency *fjvtsf; //!

  //B-tagging
  BTaggingSelectionTool* btagtool; //!
  BTaggingEfficiencyTool * btagefftool; //!


//////////////////////
////  missing ET  ////
//////////////////////



  //MetMaker
//  met::METMaker* metMaker; //!
  asg::AnaToolHandle<IMETMaker> metMaker; //!

  //MetSystematic
//  met::METSystematicsTool* metSystTool; //!
  asg::AnaToolHandle<IMETSystematicsTool> metSystTool; //!



//////////////////
////  others  ////
//////////////////



  //isolation
  CP::IsolationSelectionTool *iso_0; //!
  CP::IsolationSelectionTool *iso_1; //!
  CP::IsolationSelectionTool *iso_2; //!
  CP::IsolationSelectionTool *iso_3; //!
  CP::IsolationSelectionTool *iso_4; //!
  CP::IsolationSelectionTool *iso_5; //!
  CP::IsolationSelectionTool *iso_6; //!
  CP::IsolationSelectionTool *iso_7; //!
  CP::IsolationSelectionTool *iso_8; //!
  CP::IsolationSelectionTool *iso_9; //!


  //OverLap Removal
  asg::AnaToolHandle<ORUtils::IOverlapRemovalTool> m_overlapRemovalTool; //!
  ORUtils::ToolBox *toolBox; //!


  //cross section renormalization
  asg::AnaToolHandle<PMGTools::IPMGCrossSectionTool> m_PMGCrossSectionTool; //!

  //truth weight tool
  asg::AnaToolHandle<PMGTools::IPMGTruthWeightTool> m_weightTool; //!

  //remove unwanted bunches
  Trig::WebBunchCrossingTool *bct; //!


  //Systematics
  std::vector<CP::SystematicSet> full_sysList; //!
  std::vector<CP::SystematicSet> m_sysList; //!
  std::set<std::string> nameSysList; //!
  std::string sysname; //!
  CP::SystematicSet sysVari; //!
  TH1D *systematicList; //!
  std::map<CP::SystematicSet, std::string> affectedArea; //!


  bool doMuonSelection = false;
  bool doElecSelection = false;
  bool doFwdElecSelection = false;
  bool doPhotonSelection = false;
  bool doTauSelection = false;
  bool doJetSelection = false;
  bool doMetCalculation = false;
  bool doTruthSelection = false;

  bool runFwdReco = false;
  bool runWZPolarization = false;

  bool isBaselined0Sig = false;

  // this is a standard algorithm constructor
  xAODHelper (const std::string& name, ISvcLocator* pSvcLocator);

  // these functions need to be overriden in inherited functions
  virtual bool init(void){return true;};
  virtual bool loop(void){return true;};
  virtual StatusCode finish(void){return StatusCode::SUCCESS;}

  void assignVariationAffected(CP::SystematicSet sysVari);
  StatusCode getObjects();

  StatusCode fileExecute () override;
  // these are the functions inherited from Algorithm
  virtual StatusCode initialize () override;
  virtual StatusCode execute () override;
  virtual StatusCode finalize () override;
  ~xAODHelper () override;
};

#endif
