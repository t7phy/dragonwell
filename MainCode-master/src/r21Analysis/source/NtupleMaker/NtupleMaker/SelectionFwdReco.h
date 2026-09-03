#ifndef NtupleMaker_SelectionFwdReco_H
#define NtupleMaker_SelectionFwdReco_H

//xAOD accessor
#include "NtupleMaker/SelectionHelper.h"

class SelectionFwdReco : public SelectionHelper
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

  SelectionFwdReco (const std::string& name, ISvcLocator* pSvcLocator); // constructor for release 21

  virtual void MuonSelection(xAOD::Muon *mu);
  virtual void ElectronSelection(xAOD::Electron *el);
  virtual void FwdElectronSelection(xAOD::Electron *el);
  virtual void JetSelection(xAOD::Jet *jt);
  virtual void overlapTag(void);

  virtual bool init(void);

};
#endif
