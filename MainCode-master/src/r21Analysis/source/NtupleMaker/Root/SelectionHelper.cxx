#include "NtupleMaker/SelectionHelper.h"

SelectionHelper :: SelectionHelper (const std::string& name,
                                  ISvcLocator *pSvcLocator)
    : FunctionHelper (name, pSvcLocator)
{
  // Here you put any code for the base initialization of variables,
  // e.g. init all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // init().
  doDeliver = false;

  isFlawless = 0;
  recordLevel = "baseline";
  MatrixLevel = "MatrixLepton";
}

bool SelectionHelper :: init ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected
  xAODHelper::doMuonSelection = doMuonSelection;
  xAODHelper::doElecSelection = doElecSelection;
  xAODHelper::doFwdElecSelection = doFwdElecSelection;
  xAODHelper::doPhotonSelection = doPhotonSelection;
  xAODHelper::doTauSelection = doTauSelection;
  xAODHelper::doJetSelection = doJetSelection;
  xAODHelper::doMetCalculation = doMetCalculation;
  xAODHelper::doTruthSelection = doTruthSelection;

  if(doMuonSelection) std::cout<<"muon selection switch on"<<std::endl;
  if(doElecSelection) std::cout<<"elec selection switch on"<<std::endl;
  if(doFwdElecSelection) std::cout<<"fwd elec selection switch on"<<std::endl;
  if(doPhotonSelection) std::cout<<"photon selection switch on"<<std::endl;
  if(doTauSelection) std::cout<<"tau selection switch on"<<std::endl;
  if(doJetSelection) std::cout<<"jet selection switch on"<<std::endl;
  if(doMetCalculation) std::cout<<"missingET selection switch on"<<std::endl;
  if(doTruthSelection) std::cout<<"Truth particle switch on"<<std::endl;

  event_CutFlow = new TH1D("event_CutFlow","event_CutFlow",20,0,20);
  if(!doDeliver) wk()->addOutput(event_CutFlow);
  electron_CutFlow = new TH1D("electron_CutFlow","electron_CutFlow",20,0,20);
  if(!doDeliver) wk()->addOutput(electron_CutFlow);
  electronFwd_CutFlow = new TH1D("electronFwd_CutFlow","electronFwd_CutFlow",20,0,20);
  if(!doDeliver) wk()->addOutput(electronFwd_CutFlow);
  muon_CutFlow = new TH1D("muon_CutFlow","muon_CutFlow",20,0,20);
  if(!doDeliver) wk()->addOutput(muon_CutFlow);
  photon_CutFlow = new TH1D("photon_CutFlow","photon_CutFlow",20,0,20);
  if(!doDeliver) wk()->addOutput(photon_CutFlow);
  jet_CutFlow = new TH1D("jet_CutFlow","jet_CutFlow",20,0,20);
  if(!doDeliver) wk()->addOutput(jet_CutFlow);
  event_CutFlow_W = new TH1D("event_CutFlow_W","event_CutFlow_W",20,0,20);
  if(!doDeliver) wk()->addOutput(event_CutFlow_W);
  truth_CutFlow = new TH1D("truth_CutFlow","truth_CutFlow",20,0,20);
  if(!doDeliver) wk()->addOutput(truth_CutFlow);

  event_CutNameMap = new std::map<std::string, double>();
  electron_CutNameMap = new std::map<std::string, double>();
  electronFwd_CutNameMap = new std::map<std::string, double>();
  muon_CutNameMap = new std::map<std::string, double>();
  photon_CutNameMap = new std::map<std::string, double>();
  jet_CutNameMap = new std::map<std::string, double>();
  truth_CutNameMap = new std::map<std::string, double>();

  return true;

}

bool SelectionHelper :: loop ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  isPassEvent = false;

  EL_RETURN_CHECK("loop()", getObjects() );

//  m_store->clear(); //need to be called here again in case of systematic loops

  isTriggerPassed = false;
  calMet = 0.;
  calMpx = 0.;
  calMpy = 0.;
  hasBadJet = false;

  updateCutFlow(event_CutFlow, event_CutNameMap, "all", 1, doOnce);

  if(!eventDecor(eventInfo)) return false;
  updateCutFlow(event_CutFlow, event_CutNameMap, "PileupReweighting", 1, doOnce);

  if(!passGRL()) return false;
  updateCutFlow(event_CutFlow, event_CutNameMap, "GRL", 1, doOnce);

  if(!passEventCleaning()) return false;
  updateCutFlow(event_CutFlow, event_CutNameMap, "eventCleaning", 1, doOnce);

  isPassEvent = true;

  if(!runFwdReco){
//    if(!passJetCleaning()) return false;
    isPassJetCleaning = true;
    if(!passJetCleaning()) isPassJetCleaning = false;
    if(isPassEvent && isPassJetCleaning) updateCutFlow(event_CutFlow, event_CutNameMap, "JetCleaning", 1, doOnce);
  }

//  if (!passVTX ()) return false;
  isPassVTX = true;
  if (!passVTX ()) isPassVTX = false;
  if(isPassEvent && isPassVTX) updateCutFlow(event_CutFlow, event_CutNameMap, "vertex", 1, doOnce);

  if(!runFwdReco){
    setTriggerList();
    isTriggerPassed = passTrigger("singleEL_OR_singleMU");
//    if(!isTriggerPassed) return false;
    isPassTrigger = true;
    if(!isTriggerPassed) isPassTrigger = false;;
  }

  if(isPassEvent && isPassTrigger) updateCutFlow(event_CutFlow, event_CutNameMap, "trigger", 1, doOnce);

//  std::cout<<std::endl;
//  std::cout<<"Before cut"<<std::endl;
///////////////////////////////////
/////      muon selection     /////
///////////////////////////////////

  if(doMuonSelection && (doOnce || affectedArea[sysVari].find("muon") == 0)){
    muonMap->clear();

    int mu_count = -1;
    for( auto mu : *muonsCorr ){
//      if(!m_muonSelectionLoose->accept(*mu)) continue;
      (mu)->auxdata<float>("chargeQ") = (mu)->charge();
      (mu)->auxdata<float>("z0") = -999.;
      (mu)->auxdata<float>("d0") = -999.;
      (mu)->auxdata<float>("d0Sig") = -999.;
      (mu)->auxdata<float>("chargeQ") = 0.;
      (mu)->auxdata<int>("pdgID") = 13;
      (mu)->auxdata<char>("truthMatched") = 0;
      (mu)->auxdata<float>("truthChargeConsistency") = 0;
      (mu)->auxdata<char>("IPID") = 0;

      mu_count++;

      if(doOnce || affectedArea[sysVari] == "muon_calibration"){
        if(m_muonCalibrationAndSmearingTool->applyCorrection(*mu) == CP::CorrectionCode::Error){
           Error("loop()", "MuonCalibrationAndSmearingTool returns Error CorrectionCode");
        }
        if(isMC){
          for(auto tPar : *xTruthParticleContainer){
            if(!((tPar)->auxdata<char>("isHardMuon"))) continue;
            double tdr = ((mu)->p4()).DeltaR((tPar)->p4());
            if(tdr<0.2){
              (mu)->auxdata<char>("truthMatched") = true;
              (mu)->auxdata<float>("truthChargeConsistency") = (tPar)->charge() * (mu)->charge();
            }
          }
        }
      }

      muonIdentificationDecor(mu);
      muonIsolationDecor(mu);
      muonTriggerDecor(mu);
      muonTTVADecor(mu);

//std::cout<<"mu pt:"<<(mu)->pt()<<std::endl;

      MuonSelection(mu);
//      if(!((mu)->auxdata<char>(recordLevel.c_str()))) continue;
      if(!((mu)->auxdata<char>(MatrixLevel.c_str()))) continue;
      (*muonMap)[(mu)->pt()] = mu;

    }
  }


//////////////////////////////////
////    electron selection    ////
//////////////////////////////////

  if(doElecSelection && (doOnce || affectedArea[sysVari].find("electron") == 0)){
    electronMap->clear();

    int el_count = -1;
    for( auto el : *elsCorr ){
      if(!(el)->auxdata<char>("DFCommonElectronsLHLooseBL")) continue;
      (el)->auxdata<float>("chargeQ") = (el)->charge();
      (el)->auxdata<float>("z0") = -999.;
      (el)->auxdata<float>("d0") = -999.;
      (el)->auxdata<float>("d0Sig") = -999.;
      (el)->auxdata<float>("chargeQ") = 0.;
      (el)->auxdata<int>("pdgID") = 11;
      (el)->auxdata<char>("truthMatched") = 0;
      (el)->auxdata<float>("truthChargeConsistency") = 0;
      (el)->auxdata<char>("IPID") = 0;
      (el)->auxdata<int>("isAmbiguity") = -999;

      (el)->auxdecor<char>("PassPtCut") = 0;
//      (el)->auxdecor<char>("overlaps") = 0;
//      (el)->auxdecor<char>("overlapJet") = 0;

      if((el)->caloCluster()->pt() > 20000){
       (el)->auxdecor<char>("PassPtCut") = true;
      }

      el_count++;
      if(doOnce || affectedArea[sysVari] == "electron_calibration"){
        m_EleCalibTool->setRandomSeed(eventInfo->eventNumber() + 100 * el_count);
        m_EleCalibTool->applyCorrection(*el);
        if(isMC){
          for(auto tPar : *xTruthParticleContainer){
            if(!((tPar)->auxdata<char>("isHardElectron"))) continue;
            double tdr = ((el)->p4()).DeltaR((tPar)->p4());
            if(tdr<0.2){
              (el)->auxdata<char>("truthMatched") = true;
              (el)->auxdata<float>("truthChargeConsistency") = (tPar)->charge() * (el)->charge();
            }
          }
        }
      }


      if(!runFwdReco) electronIdentificationDecor(el);
      if(!runFwdReco) electronIsolationDecor(el);
      if(!runFwdReco) electronTriggerDecor(el);
      if(!runFwdReco) electronTTVADecor(el);

      ElectronSelection(el);
//      if(!((el)->auxdata<char>(recordLevel.c_str()))) continue;
      if(!((el)->auxdata<char>(MatrixLevel.c_str()))) continue;
      (*electronMap)[(el)->pt()] = el;

    }
  }


////////////////////////////////////////
////   forward electron selection   ////
////////////////////////////////////////

  if(doFwdElecSelection && doOnce){
    fwdelectronMap->clear();

    for( auto el : *fwdelsCorr ){
      (el)->auxdata<int>("pdgID") = 11;
      (el)->auxdata<char>("truthMatched") = 0;

      (el)->auxdecor<char>("PassPtCut") = 0;
//      (el)->auxdecor<char>("overlaps") = 0;
//      (el)->auxdecor<char>("overlapJet") = 0;

      if((el)->caloCluster()->pt() > 20000){
        (el)->auxdecor<char>("PassPtCut") = true;
      }

      for( auto fwdel2 : *fwdels ){
        double tdr = ((el)->p4()).DeltaR((fwdel2)->p4());
        if(tdr<0.2){
          if((el)->pt() > (fwdel2)->pt()) (fwdel2)->auxdecor<char>("overlaps") = true;
          if((el)->pt() < (fwdel2)->pt()) (el)->auxdecor<char>("overlaps") = true;
        }
      }

      if(isMC)
      {
        for(auto tPar : *xTruthParticleContainer){
          if(!((tPar)->auxdecor<char>("isHardElectron"))) continue;
          double tdr = ((el)->p4()).DeltaR((tPar)->p4());
          if(tdr<0.4){
            (el)->auxdecor<char>("truthMatched") = true;
          }
        }
      }

      double el_eta = (el)->caloCluster()->eta();

      if(!isMC && RunNum<=311481 ){
        int m_bcid = eventInfo->bcid();
        if(fabs(el_eta)>2.5 && fabs(el_eta)<3.2){
          double distance =  bct->gapBeforeTrain(m_bcid)>500 ? bct->distanceFromFront(m_bcid) : (bct->distanceFromFront(m_bcid)+bct->gapBeforeTrain(m_bcid) + ( bct->distanceFromFront(m_bcid)+bct->distanceFromTail(m_bcid) ));
          if ( distance< 5.5*25) continue;
        }
      }  

      if(!runFwdReco){
        m_EleCalibTool->setRandomSeed(eventInfo->eventNumber());
        m_EleCalibTool->applyCorrection(*el);
      }

      if(!runFwdReco) electronIdentificationDecor(el,1);
      if(!runFwdReco) electronIsolationDecor(el,1);

      FwdElectronSelection(el);
      if(!((el)->auxdata<char>(recordLevel.c_str()))) continue;
      (*fwdelectronMap)[(el)->pt()] = el;
    }
  }


/////////////////////////////
/////   jet selection   /////
/////////////////////////////

  if(doJetSelection && (doOnce || affectedArea[sysVari].find("jet") == 0)){
    jetMap->clear();

    int jt_count = -1;
    for( auto jt : *jetsCorr ){
      //if(jt->pt()/GeV < 20) continue;

      (jt)->auxdata<int>("pdgID") = 0;
      (jt)->auxdata<char>("truthMatched") = 0;

      jt_count++;

      //if(EvtNum == 35183){
      //  std::cout<<"Jet: E: "<<jt->e() / GeV<<" Pt: "<<jt->pt() / GeV<<" eta: "<<jt->eta()<<" phi: "<<jt->phi()<<std::endl;
      //}
 
      if(doOnce || affectedArea[sysVari] == "jet_calibration"){
        m_jetCalibration->applyCalibration(*jt);
        if(m_jesUncert->applyCorrection(*jt) != CP::CorrectionCode::Ok)  Error("loop()","Cannot apply systematic variation to the jet");
        float newjvt = m_pjvtag->updateJvt(*jt);
        (jt)->auxdecor<float>("Jvt") = newjvt;

        //if(isMC){
          //for( auto Tjt : *Tjets){
            //if( Tjt->pt()/GeV < 10 ) continue;
          //  if( (jt->p4()).DeltaR(Tjt->p4()) < 0.4 ) (jt)->auxdata<char>("truthMatched") = true;
          //}
        //}
      }

      //if(EvtNum == 35183){
      //  std::cout<<"(Calib)Jet: E: "<<jt->e() / GeV<<" Pt: "<<jt->pt() / GeV<<" eta: "<<jt->eta()<<" phi: "<<jt->phi()<<std::endl;
      //}

      jetBtaggingDecor(jt);

      JetSelection(jt);
      if(!((jt)->auxdata<char>(recordLevel.c_str()))) continue;
      (*jetMap)[(jt)->pt()] = jt;

    }
    jetConJvtDecor(jetsCorr);
  }

  if(doElecSelection && doMuonSelection && doJetSelection){  
    overlapTag();
  }

///////////////////////////////
/////   truth selection   /////
///////////////////////////////


///////////////////////////////
/////   Met calculation   /////
///////////////////////////////

  if(doMetCalculation && (doOnce || affectedArea[sysVari] == "met_calibration" || affectedArea[sysVari] == "electron_calibration" || affectedArea[sysVari] == "muon_calibration" || affectedArea[sysVari] == "jet_calibration")){

    met::addGhostMuonsToJets(*muons, *jetsCorr);

        // Create a MissingETContainer with its aux store for each systematic
        xAOD::MissingETContainer*    newMetContainer    = new xAOD::MissingETContainer();
        xAOD::MissingETAuxContainer* newMetAuxContainer = new xAOD::MissingETAuxContainer();
        newMetContainer->setStore(newMetAuxContainer);

        // It is necessary to reset the selected objects before every MET calculation
        metMap->resetObjSelectionFlags();

        //here we apply some basic cuts and rebuild the met at each step
        //Electrons
        ConstDataVector<xAOD::ElectronContainer> metElectrons(SG::VIEW_ELEMENTS);
        for(const auto& m_el : *elsCorr) {
          if((m_el)->auxdata<char>(recordLevel2.c_str()))  metElectrons.push_back(m_el);
          //if(EvtNum == 35183){
          //  if((m_el)->auxdata<char>(recordLevel2.c_str())) std::cout<<"Electron: E: "<<m_el->e() / GeV<<" Pt: "<<m_el->pt() / GeV<<" eta: "<<m_el->eta()<<" phi: "<<m_el->phi()<<std::endl;
          //}
        }
//        for(const auto& m_el : *fwdelsCorr) {
//          if((m_el)->pt()>10*GeV && m_FwdElectronIDToolLoose->accept(m_el))  metElectrons.push_back(m_el);
//        }
        (metMaker)->rebuildMET("RefEle",                   //name of metElectrons in metContainer
                                   xAOD::Type::Electron,       //telling the rebuilder that this is electron met
                                   newMetContainer,            //filling this met container
                                   metElectrons.asDataVector(),//using these metElectrons that accepted our cuts
                                   metMap)                     //and this association map
               ;

        //Muons
        ConstDataVector<xAOD::MuonContainer> metMuons(SG::VIEW_ELEMENTS);
        for(const auto& m_mu : *muonsCorr) {
          if((m_mu)->auxdata<char>(recordLevel2.c_str()))  metMuons.push_back(m_mu);
          //if(EvtNum == 35183){
          //  if((m_mu)->auxdata<char>(recordLevel2.c_str())) std::cout<<"Muon: E: "<<m_mu->e() / GeV<<" Pt: "<<m_mu->pt() / GeV<<" eta: "<<m_mu->eta()<<" phi: "<<m_mu->phi()<<std::endl;
          //}
        }
        (metMaker)->rebuildMET("RefMuon",
                                   xAOD::Type::Muon,
                                   newMetContainer,
                                   metMuons.asDataVector(),
                                   metMap)
               ;
        //Now time to rebuild jetMet and get the soft term
        //This adds the necessary soft term for both CST and TST
        //these functions create an xAODMissingET object with the given names inside the container

        (metMaker)->rebuildJetMET("RefJet",        //name of jet met
                                        "SoftClus",      //name of soft cluster term met
                                        "PVSoftTrk",     //name of soft track term met
                                        newMetContainer, //adding to this new met container
                                        jetsCorr,       //using this jet collection to calculate jet met
                                        coreMet,         //core met container
                                        metMap,          //with this association map
                                        true            //apply jet jvt cut
                                        )
                 ;


        if(isMC){
          xAOD::MissingET * softTrkMet = (*newMetContainer)["PVSoftTrk"];
          (metSystTool)->applyCorrection(*softTrkMet);           //"This tool should be applied to MC only.  Return without changing the input MET object"
        }
        //this builds the final track met sums, using systematic varied container
        (metMaker)->buildMETSum("FinalTrk" , newMetContainer, MissingETBase::Source::Track );

        xAOD::MissingET* metFinal = 0;
        if(!(metFinal=(*newMetContainer)["FinalTrk"])) std::cout<<"met retrieve failed"<<std::endl;
        calMet = metFinal->met()/GeV;
        calMpx = metFinal->mpx()/GeV;
        calMpy = metFinal->mpy()/GeV;
        metsCorr->SetPxPyPzE( metFinal->mpx()/GeV, metFinal->mpy()/GeV, 0, metFinal->met()/GeV );

     delete newMetContainer;
     delete newMetAuxContainer;

  }


/*  if(doJetSelection){
    for( auto jt : *jetsCorr ){
      double JEMpt = jt->pt();
      if(JEMpt/GeV > 20 && (jt)->auxdata<char>("passJVT") && !((jt)->auxdata<char>("overlaps")) && !m_cleaningTool->keep(*jt)) hasBadJet = true;
    }
  }
*/

  return true;

}

StatusCode SelectionHelper :: finish ()
{
  // This method is the mirror image of init(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // init() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.

  return StatusCode::SUCCESS;

}

