#ifndef NtupleMaker_SelectionHelper_H
#define NtupleMaker_SelectionHelper_H

//xAOD accessor
#include "NtupleMaker/FunctionHelper.h"

class SelectionHelper : public FunctionHelper
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  bool doMuonSelection = false;
  bool doElecSelection = false;
  bool doFwdElecSelection = false;
  bool doPhotonSelection = false;
  bool doTauSelection = false;
  bool doJetSelection = false;
  bool doMetCalculation = false;
  bool doTruthSelection = false;

  // these will be put in the same file with output trees
  TH1D *event_CutFlow; //!
  TH1D *electron_CutFlow; //!
  TH1D *electronFwd_CutFlow; //!
  TH1D *muon_CutFlow; //!
  TH1D *photon_CutFlow; //!
  TH1D *jet_CutFlow; //!
  TH1D *event_CutFlow_W; //!
  TH1D *electron_CutFlow_W; //!
  TH1D *electronFwd_CutFlow_W; //!
  TH1D *muon_CutFlow_W; //!
  TH1D *photon_CutFlow_W; //!
  TH1D *jet_CutFlow_W; //!

  TH1D *truth_CutFlow; //!

  std::map<std::string, double> *event_CutNameMap; //!
  std::map<std::string, double> *electron_CutNameMap; //!
  std::map<std::string, double> *electronFwd_CutNameMap; //!
  std::map<std::string, double> *muon_CutNameMap; //!
  std::map<std::string, double> *photon_CutNameMap; //!
  std::map<std::string, double> *jet_CutNameMap; //!
  std::map<std::string, double> *truth_CutNameMap; //!

  bool doDeliver; //!
  bool m_passPreSelection; //!

  int rNum; //!

  double calMet; //!
  double calMpx; //!
  double calMpy; //!
  char hasBadJet; //!
  bool isTriggerPassed; //!
  int NBjet; //!

  std::string recordLevel;
  std::string MatrixLevel;
  std::string recordLevel2;

  SelectionHelper (const std::string& name, ISvcLocator* pSvcLocator); // constructor for release 21

  virtual bool init(void);
  virtual bool loop(void);
  virtual StatusCode finish(void);

  virtual void MuonSelection(xAOD::Muon *mu){ (mu)->auxdata<char>(recordLevel.c_str()) = true;(mu)->auxdata<char>(MatrixLevel.c_str()) = true;(mu)->auxdata<char>(recordLevel2.c_str()) = true;}
  virtual void ElectronSelection(xAOD::Electron *el){ (el)->auxdata<char>(recordLevel.c_str()) = true;(el)->auxdata<char>(MatrixLevel.c_str()) = true;(el)->auxdata<char>(recordLevel2.c_str()) = true;}
  virtual void FwdElectronSelection(xAOD::Electron *el){ (el)->auxdata<char>(recordLevel.c_str()) = true;(el)->auxdata<char>(MatrixLevel.c_str()) = true;(el)->auxdata<char>(recordLevel2.c_str()) = true;}
  virtual void JetSelection(xAOD::Jet *jt){ (jt)->auxdata<char>(recordLevel.c_str()) = true;(jt)->auxdata<char>(MatrixLevel.c_str()) = true;(jt)->auxdata<char>(recordLevel2.c_str()) = true;}
  virtual void overlapTag(void){ return;}

};
#endif
