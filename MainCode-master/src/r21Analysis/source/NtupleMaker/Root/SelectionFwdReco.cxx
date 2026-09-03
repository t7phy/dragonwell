#include "NtupleMaker/SelectionFwdReco.h"

SelectionFwdReco :: SelectionFwdReco (const std::string& name,
                                  ISvcLocator *pSvcLocator)
    : SelectionHelper (name, pSvcLocator)
{
  // Here you put any code for the base initialization of variables,
  // e.g. init all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // init().

  recordLevel = "baselineSoft";

}

bool SelectionFwdReco :: init()
{
  doMuonSelection = false;
  doElecSelection = true;
  doFwdElecSelection = true;
  doPhotonSelection = false;
  doTauSelection = false;
  doJetSelection = false;
  doMetCalculation = false;
  doTruthSelection = true;

  SelectionHelper::doMuonSelection = doMuonSelection;
  SelectionHelper::doElecSelection = doElecSelection;
  SelectionHelper::doFwdElecSelection = doFwdElecSelection;
  SelectionHelper::doPhotonSelection = doPhotonSelection;
  SelectionHelper::doTauSelection = doTauSelection;
  SelectionHelper::doJetSelection = doJetSelection;
  SelectionHelper::doMetCalculation = doMetCalculation;
  SelectionHelper::doTruthSelection = doTruthSelection;

  SelectionHelper::init();

  return true;
}

void SelectionFwdReco :: MuonSelection(xAOD::Muon *mu){

}

void SelectionFwdReco :: ElectronSelection(xAOD::Electron *el){

}

void SelectionFwdReco :: FwdElectronSelection(xAOD::Electron *el){
    updateCutFlow(electronFwd_CutFlow, electronFwd_CutNameMap, "all", 1, doOnce);

//    if(!(el)->auxdecor<char>("PassPtCut")) return;
//    updateCutFlow(electronFwd_CutFlow, electronFwd_CutNameMap, "PassPtCut", 1, doOnce);

    if((el)->auxdecor<char>("overlaps")) return;
    updateCutFlow(electronFwd_CutFlow, electronFwd_CutNameMap, "overlaps", 1, doOnce);

//    if((el)->auxdecor<char>("overlapJet")) return;
    updateCutFlow(electronFwd_CutFlow, electronFwd_CutNameMap, "overlapJet", 1, doOnce);

//    if(!(el)->auxdecor<char>("truthMatched")) return;
//    updateCutFlow(electronFwd_CutFlow, electronFwd_CutNameMap, "truthMatched", 1, doOnce);

    (el)->auxdata<char>("baselineSoft") = true;

    return;
}

void SelectionFwdReco :: JetSelection(xAOD::Jet *jt){

}

void SelectionFwdReco :: overlapTag(void){
//  overlapDecision(elsCorr, 0, muonsCorr, jetsCorr, "baselineSoft", "overlaps", false);
}
