#include "NtupleMaker/SelectionWW.h"

SelectionWW :: SelectionWW (const std::string& name,
                                  ISvcLocator *pSvcLocator)
    : SelectionHelper (name, pSvcLocator)
{
  // Here you put any code for the base initialization of variables,
  // e.g. init all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // init().

  recordLevel = "baseline";
  MatrixLevel = "MatrixLepton";
  recordLevel2 = "baselineWithD0Sig";
}

bool SelectionWW :: init()
{
  doMuonSelection = true;
  doElecSelection = true;
  doFwdElecSelection = false;
  doPhotonSelection = false;
  doTauSelection = false;
  doJetSelection = true;
  doMetCalculation = true;
  if(isMC) doTruthSelection = true;

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

void SelectionWW :: MuonSelection(xAOD::Muon *mu){

    if(!doOnce && affectedArea[sysVari] != "muon_calibration") return;

    (mu)->auxdata<char>("baseline") = false;
    (mu)->auxdata<char>("MatrixLepton") = false;
    (mu)->auxdata<char>("baselineWithD0Sig") = false;

    updateCutFlow(muon_CutFlow, muon_CutNameMap, "all", 1, doOnce);

//    (mu)->auxdata<char>("isHard") = ((mu)->pt()/GeV  > 25.0);
    (mu)->auxdata<char>("isHard") = ((mu)->pt()/GeV  > 15.0);

    if( !((mu)->auxdata<char>("looseID")) )  return;
    updateCutFlow(muon_CutFlow, muon_CutNameMap, "looseID", 1, doOnce);

    //if( !((mu)->auxdata<char>("PflowLooseIso")) )  return;
    //updateCutFlow(muon_CutFlow, muon_CutNameMap, "PflowLooseIso", 1, doOnce);

    if((mu)->pt()/GeV  < 5.0) return;
    updateCutFlow(muon_CutFlow, muon_CutNameMap, "pt>5", 1, doOnce);

//    if((mu)->pt()/GeV < 15.0) return;
    if(xAOD::Muon::CaloTag == (mu)->author() && ((mu)->pt()/GeV < 15.0)) return;
    updateCutFlow(muon_CutFlow, muon_CutNameMap, "extra pt cut", 1, doOnce);

    if(isBaselined0Sig){
      if(!(mu)->auxdata<char>("IPID")) return;
      updateCutFlow(muon_CutFlow, muon_CutNameMap, "fabs(d0Sig)<3", 1, doOnce);
    }

    if(fabs((mu)->auxdata<float>("z0")) > 0.5) return;
    updateCutFlow(muon_CutFlow, muon_CutNameMap, "z0<0.5", 1, doOnce);

    if(((mu)->auxdata<char>("PflowLooseIso"))) (mu)->auxdata<char>("baseline") = true;
    if((mu)->auxdata<char>("IPID") && ((mu)->auxdata<char>("PflowLooseIso"))) (mu)->auxdata<char>("baselineWithD0Sig") = true;
    (mu)->auxdata<char>("MatrixLepton") = true;
}

void SelectionWW :: ElectronSelection(xAOD::Electron *el){

    if(!doOnce && affectedArea[sysVari] != "electron_calibration") return;

    (el)->auxdata<char>("baseline") = false;
    (el)->auxdata<char>("MatrixLepton") = false;
    (el)->auxdata<char>("baselineWithD0Sig") = false;

    updateCutFlow(electron_CutFlow, electron_CutNameMap, "all", 1, doOnce);

    double el_eta = (el)->caloCluster()->etaBE(2);
//    (el)->auxdata<char>("isHard") = ((el)->pt()/GeV > 25.0 && fabs(el_eta) < 2.47 && !(fabs(el_eta)<1.52 && fabs(el_eta)>1.37));
    (el)->auxdata<char>("isHard") = ((el)->pt()/GeV > 15.0 && fabs(el_eta) < 2.47 && !(fabs(el_eta)<1.52 && fabs(el_eta)>1.37));

    if( !((el)->auxdata<char>("looseID")) )  return;
    updateCutFlow(electron_CutFlow, electron_CutNameMap, "looseID", 1, doOnce);

    //if( !((el)->auxdata<char>("FCLooseIso")) )  return;
    //updateCutFlow(electron_CutFlow, electron_CutNameMap, "FCLooseIso", 1, doOnce);

    if((el)->pt()/GeV < 5.0) return;
    updateCutFlow(electron_CutFlow, electron_CutNameMap, "pt>5", 1, doOnce);

    if(fabs(el_eta) > 2.47) return;
    updateCutFlow(electron_CutFlow, electron_CutNameMap, "eta<2.47", 1, doOnce);

    if( !((el)->isGoodOQ(xAOD::EgammaParameters::BADCLUSELECTRON)) ) return;
    updateCutFlow(electron_CutFlow, electron_CutNameMap, "OQ", 1, doOnce);

    if(isBaselined0Sig){
      if(!(el)->auxdata<char>("IPID")) return;
      updateCutFlow(electron_CutFlow, electron_CutNameMap, "fabs(d0Sig)<5", 1, doOnce);
    }

    if(fabs((el)->auxdata<float>("z0")) > 0.5) return;
    updateCutFlow(electron_CutFlow, electron_CutNameMap, "z0<0.5", 1, doOnce);

    if(((el)->auxdata<char>("FCLooseIso"))) (el)->auxdata<char>("baseline") = true;
    if((el)->auxdata<char>("IPID") && ((el)->auxdata<char>("FCLooseIso"))) (el)->auxdata<char>("baselineWithD0Sig") = true;

    (el)->auxdata<char>("MatrixLepton") = true;

}

void SelectionWW :: FwdElectronSelection(xAOD::Electron *el){

    (el)->auxdata<char>("baseline") = false;
    (el)->auxdata<char>("MatrixLepton") = false;
    (el)->auxdata<char>("baselineWithD0Sig") = false;

    return;
}

void SelectionWW :: JetSelection(xAOD::Jet *jt){

    if(!doOnce && affectedArea[sysVari] != "jet_calibration") return;

    (jt)->auxdata<char>("baseline") = false;
    (jt)->auxdata<char>("MatrixLepton") = false;
    (jt)->auxdata<char>("baselineWithD0Sig") = false;

    double JEMeta = jt->eta();
    double JEMpt = jt->pt();

    updateCutFlow(jet_CutFlow, jet_CutNameMap, "all", 1, doOnce);

    if (!(fabs(JEMeta) < 4.5 && JEMpt/GeV > 30)) return;
    updateCutFlow(jet_CutFlow, jet_CutNameMap, "pt>30, eta<4.5", 1, doOnce);

    (jt)->auxdata<char>("isHard") = true;
    (jt)->auxdata<char>("baseline") = true;
    (jt)->auxdata<char>("MatrixLepton") = true;

}

void SelectionWW :: overlapTag(void){
//  overlapDecision(elsCorr, 0, muonsCorr, jetsCorr, "baseline", "overlaps", true);
  overlapDecision(elsCorr, 0, muonsCorr, jetsCorr, "MatrixLepton", "overlaps", true);
  //MatrixoverlapDecision(elsCorr, 0, muonsCorr, jetsCorr, "MatrixLepton", "overlaps", true);
}
