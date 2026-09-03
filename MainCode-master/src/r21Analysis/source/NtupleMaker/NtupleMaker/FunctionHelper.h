#ifndef NtupleMaker_FunctionHelper_H
#define NtupleMaker_FunctionHelper_H

//xAOD accessor
#include "NtupleMaker/xAODHelper.h"

class FunctionHelper : public xAODHelper
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:

  std::string m_muTMstring; //!
  std::string elec_trigger1; //!
  std::string elec_trigger2; //!
  std::string elec_trigger3; //!
  std::string muon_trigger1; //!
  std::string muon_trigger2; //!

  bool passGRL(); //!
  bool passVTX(); //!
  bool passEventCleaning(); //!
  bool passJetCleaning();
  bool passTrigger(std::string trigRequirement); //!

  void electronIdentificationDecor(xAOD::Electron *el, int region = 0); //!
  void electronIsolationDecor(xAOD::Electron *el, int region = 0); //!
  void electronTriggerDecor(xAOD::Electron *el); //!
  void electronTTVADecor(xAOD::Electron *el); //!

  void muonIdentificationDecor(xAOD::Muon *mu); //!
  void muonIsolationDecor(xAOD::Muon *mu); //!
  void muonTriggerDecor(xAOD::Muon *mu); //!
  void muonTTVADecor(xAOD::Muon *mu); //!

  void jetBtaggingDecor(xAOD::Jet *jt); //!
  void jetConJvtDecor(xAOD::JetContainer *jetsCorr); //!

  void computeImpactParameters(const xAOD::TrackParticle* trk, const xAOD::VertexContainer* vxContainer, float &delta_z0, float &d0); //!

  bool eventDecor(const xAOD::EventInfo* evtInfo); //!

  void setTriggerList(); //!

  float CalVertexReweight(); //!
  float GetVertexReweight(float z); //!

  void overlapDecision(xAOD::ElectronContainer* elsCands = 0, xAOD::ElectronContainer* fwdelsCands = 0, xAOD::MuonContainer* muonsCands = 0, xAOD::JetContainer* jetsCands = 0, std::string inFlag = "baselineHard", std::string outFlag = "overlaps", bool doCustomOR = false); //!
  void MatrixoverlapDecision(xAOD::ElectronContainer* elsCands = 0, xAOD::ElectronContainer* fwdelsCands = 0, xAOD::MuonContainer* muonsCands = 0, xAOD::JetContainer* jetsCands = 0, std::string inFlag = "baselineHard", std::string outFlag = "overlaps", bool doCustomOR = false); //!

  bool doSystematicVariation(CP::SystematicSet sysVari); //!
  void updateCutFlow(TH1D *inCutFlow, std::map<std::string, double> *inLabelMap, std::string cutName, double step = 1, bool doUpdate = true); //!

  double DeltaPhi(double Phi1, double Phi2);

  // this is a standard constructor
  FunctionHelper (const std::string& name, ISvcLocator* pSvcLocator); // constructor for release 21

};
#endif
