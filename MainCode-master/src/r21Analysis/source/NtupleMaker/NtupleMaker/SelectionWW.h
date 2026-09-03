#ifndef NtupleMaker_SelectionWW_H
#define NtupleMaker_SelectionWW_H

//xAOD accessor
#include "NtupleMaker/SelectionHelper.h"

class SelectionWW : public SelectionHelper
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  int NumberSoftMuons; //!
  int NumberSoftElectrons; //!

  bool doMuonSelection = false;
  bool doElecSelection = false;
  bool doFwdElecSelection = false;
  bool doPhotonSelection = false;
  bool doTauSelection = false;
  bool doJetSelection = false;
  bool doMetCalculation = false;
  bool doTruthSelection = false;

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)

public:

  // this is a standard constructor
  SelectionWW (const std::string& name, ISvcLocator* pSvcLocator); // constructor for release 21

  virtual bool init(void);
  virtual void MuonSelection(xAOD::Muon *mu);
  virtual void ElectronSelection(xAOD::Electron *el);
  virtual void FwdElectronSelection(xAOD::Electron *el);
  virtual void JetSelection(xAOD::Jet *jt);
  virtual void overlapTag(void);

};
#endif
