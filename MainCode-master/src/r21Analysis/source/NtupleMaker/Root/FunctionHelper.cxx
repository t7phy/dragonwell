#include <AsgTools/MessageCheck.h>
#include <NtupleMaker/FunctionHelper.h>

FunctionHelper :: FunctionHelper (const std::string& name,
                                  ISvcLocator *pSvcLocator)
    : xAODHelper (name, pSvcLocator)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0. Note that things like resetting
  // statistics variables should rather go into the initialize() function.

}

bool FunctionHelper :: passGRL ()
{
  //eventInfo->auxdecor<char>("isGRLPassed") = true;

  //if(doOnce){
    bool goodRun = false;
    if(isMC) goodRun = true;
    else if(m_grl->passRunLB(*eventInfo)) goodRun = true;
    eventInfo->auxdecor<char>("isGRLPassed") = goodRun;
  //}
  return eventInfo->auxdata<char>("isGRLPassed");
}

bool FunctionHelper :: passVTX ()
{
  //eventInfo->auxdecor<char>("isVertexPassed") = true;

//  if(doOnce) std::cout<<"call passVTX"<<std::endl;
  //if(doOnce){
    bool primVtx = false;
    double nVtx = 0;
    for (unsigned int i=0; i<vxContainer->size(); i++){
      const xAOD::Vertex* vxcand = (*vxContainer)[i];
      if ( vxcand->nTrackParticles() > 2 ){
        primVtx = true;
        nVtx++;
      }
    }
    eventInfo->auxdecor<char>("isVertexPassed") = primVtx;
  //}
  return eventInfo->auxdata<char>("isVertexPassed");
}

bool FunctionHelper :: passEventCleaning ()
{
  //if(doOnce){
    bool cleanEvent = true;
    if(!isMC){
      if((eventInfo->errorState(xAOD::EventInfo::LAr)==xAOD::EventInfo::Error)||(eventInfo->errorState(xAOD::EventInfo::Tile)==xAOD::EventInfo::Error)||(eventInfo->errorState(xAOD::EventInfo::SCT)==xAOD::EventInfo::Error)||(eventInfo->isEventFlagBitSet(xAOD::EventInfo::Core, 18))) cleanEvent = false;
    }
    eventInfo->auxdecor<char>("isEventCleaningPassed") = cleanEvent;
  //}
  return eventInfo->auxdata<char>("isEventCleaningPassed");

}

bool FunctionHelper :: passJetCleaning()
{
  return eventInfo->auxdecor<char>("isJetCleaningPassed") = eventInfo->auxdata<char>("DFCommonJets_eventClean_LooseBad");
}

bool FunctionHelper :: passTrigger (std::string trigRequirement)
{
  //if(doOnce){
    setTriggerList();
    bool TriggerDecision = false;
    if(trigRequirement == "singleEL"){
      TriggerDecision = m_TrigDecTool->isPassed(elec_trigger1.c_str()) || m_TrigDecTool->isPassed(elec_trigger2.c_str()) || m_TrigDecTool->isPassed(elec_trigger3.c_str());
    }
    if(trigRequirement == "singleMU"){
      TriggerDecision = m_TrigDecTool->isPassed(muon_trigger1.c_str()) || m_TrigDecTool->isPassed(muon_trigger2.c_str());
    }
    if(trigRequirement == "singleEL_OR_singleMU"){
      TriggerDecision = m_TrigDecTool->isPassed(elec_trigger1.c_str()) || m_TrigDecTool->isPassed(elec_trigger2.c_str()) || m_TrigDecTool->isPassed(elec_trigger3.c_str()) || m_TrigDecTool->isPassed(muon_trigger1.c_str()) || m_TrigDecTool->isPassed(muon_trigger2.c_str());
    }
    eventInfo->auxdecor<char>("isTriggerPassed") = TriggerDecision;
  //}
  return eventInfo->auxdata<char>("isTriggerPassed");

}


void FunctionHelper::computeImpactParameters(const xAOD::TrackParticle* trk, const xAOD::VertexContainer* vxContainer, float &delta_z0, float &d0)
{
    if( trk ){
      for (unsigned int i=0; i<vxContainer->size(); i++){
        const xAOD::Vertex* vtx = (*vxContainer)[i];
        if ( vtx->vertexType() == xAOD::VxType::PriVtx ){
          delta_z0 = fabs((trk->z0() + trk->vz() - vtx->z())*sin(trk->theta()));
        }
      }
      d0 =  fabs((trk->d0()));
    }
}


bool FunctionHelper :: eventDecor(const xAOD::EventInfo* evtInfo){

  double MCPileupWeight = 1.0;

  if(doOnce){
    m_prwTool->apply( *evtInfo);
  }
//    if(isMC) RunNum = m_prwTool->getRandomRunNumber(*evtInfo);
    if(isMC) MCPileupWeight = m_prwTool->getCombinedWeight( *eventInfo );
    if(isMC) RunNum = evtInfo->auxdecor<unsigned int>("RandomRunNumber");
    else RunNum = evtInfo->runNumber();
    EvtNum = evtInfo->eventNumber();
  //}

  evtInfo->auxdecor<float>("KFactor") = 1.0;
/*  if(isMC && runWZPolarization){
    if(eventInfo->mcChannelNumber()==364991) evtInfo->auxdecor<float>("KFactor") = 1.34;
    if(eventInfo->mcChannelNumber()==364992) evtInfo->auxdecor<float>("KFactor") = 2.05;
    if(eventInfo->mcChannelNumber()==364993) evtInfo->auxdecor<float>("KFactor") = 2.10;
    if(eventInfo->mcChannelNumber()==364994) evtInfo->auxdecor<float>("KFactor") = 1.51;
    if(truthParticleList[1].Pt()>200000 && truthParticleList[2].Pt()>200000){
      if(eventInfo->mcChannelNumber()==364991) evtInfo->auxdecor<float>("KFactor") = 1.01;
      if(eventInfo->mcChannelNumber()==364992) evtInfo->auxdecor<float>("KFactor") = 1.71;
      if(eventInfo->mcChannelNumber()==364993) evtInfo->auxdecor<float>("KFactor") = 1.84;
      if(eventInfo->mcChannelNumber()==364994) evtInfo->auxdecor<float>("KFactor") = 1.72;
    }
  }
*/

  if(!isfinite(MCPileupWeight) || fabs(MCPileupWeight) < 1e-10) return false;

  return true;
}

////////////////////
////  Electron  ////
////////////////////

//m_idEgCorrections2: Medium
//m_idEgCorrections3: Tight

void FunctionHelper :: electronIdentificationDecor(xAOD::Electron *el, int region){

//  if((el)->caloCluster() == nullptr) return;
  if(region == 0){
    if( doOnce || affectedArea[sysVari].find("electron") == 0){
      if((el)->isAvailable<char>("DFCommonElectronsLHLooseBL")) (el)->auxdata<char>("looseID") = (el)->auxdata<char>("DFCommonElectronsLHLooseBL");
      else (el)->auxdata<char>("looseID") = m_ElectronIDToolLoose->accept(el);
      if((el)->isAvailable<char>("DFCommonElectronsLHMediumBL")) (el)->auxdata<char>("mediumID") = (el)->auxdata<char>("DFCommonElectronsLHMediumBL");
      else (el)->auxdata<char>("mediumID") = m_ElectronIDToolMedium->accept(el);
      if((el)->isAvailable<char>("DFCommonElectronsLHTightBL")) (el)->auxdata<char>("tightID") = (el)->auxdata<char>("DFCommonElectronsLHTightBL");
      else (el)->auxdata<char>("tightID") = m_ElectronIDToolTight->accept(el);

//      if(isMC){
        if((el)->isAvailable<int>("DFCommonAddAmbiguity")) (el)->auxdata<int>("isAmbiguity") = (el)->auxdata<int>("DFCommonAddAmbiguity");
//      }
    }

    if(isMC){
      if( doOnce || affectedArea[sysVari] == "electron_reco_efficiency" || affectedArea[sysVari] == "electron_calibration"){
        double elRecoSF = 1;
        m_recoEgCorrections->getEfficiencyScaleFactor(*el,elRecoSF);
        (el)->auxdata<double>("weightRECO") = elRecoSF;
      }
      if( doOnce || affectedArea[sysVari] == "electron_ID_efficiency" || affectedArea[sysVari] == "electron_calibration"){
        double elMediumIDSF = 1;
        m_idEgCorrections2->getEfficiencyScaleFactor(*el,elMediumIDSF);
        (el)->auxdata<double>("weightMediumID") = elMediumIDSF;
        double elTightIDSF = 1;
        m_idEgCorrections3->getEfficiencyScaleFactor(*el,elTightIDSF);
        (el)->auxdata<double>("weightTightID") = elTightIDSF;
      }
    }

  }

  else{
    (el)->auxdata<char>("looseIDcbs") = false;
    (el)->auxdata<char>("mediumIDcbs") = false;
    (el)->auxdata<char>("tightIDcbs") = false;
    (el)->auxdata<char>("looseID") = false;
    (el)->auxdata<char>("mediumID") = false;
    (el)->auxdata<char>("tightID") = false;
    if ( ( m_FwdElectronIDToolLoose->accept(el) ) ) (el)->auxdata<char>("looseIDcbs") = true;
    if ( ( m_FwdElectronIDToolMedium->accept(el) ) ) (el)->auxdata<char>("mediumIDcbs") = true;
    if ( ( m_FwdElectronIDToolTight->accept(el) ) ) (el)->auxdata<char>("tightIDcbs") = true;
//    (el)->auxdata<char>("looseID") = (el)->auxdata<char>("DFCommonForwardElectronsLHLoose");
//    (el)->auxdata<char>("mediumID") = (el)->auxdata<char>("DFCommonForwardElectronsLHMedium");
//    (el)->auxdata<char>("tightID") = (el)->auxdata<char>("DFCommonForwardElectronsLHTight");
    if ( ( m_FwdElectronLikelihoodToolLoose->accept(el) ) ) (el)->auxdata<char>("looseID") = true;
    if ( ( m_FwdElectronLikelihoodToolMedium->accept(el) ) ) (el)->auxdata<char>("mediumID") = true;
    if ( ( m_FwdElectronLikelihoodToolTight->accept(el) ) ) (el)->auxdata<char>("tightID") = true;
    if(isMC){
      double elLooseIDSF = 1;
      m_idFwdEgCorrections1->getEfficiencyScaleFactor(*el,elLooseIDSF);
      double elMediumIDSF = 1;
      m_idFwdEgCorrections2->getEfficiencyScaleFactor(*el,elMediumIDSF);
      double elTightIDSF = 1;
      m_idFwdEgCorrections3->getEfficiencyScaleFactor(*el,elTightIDSF);
      (el)->auxdata<double>("weightLooseID") = elLooseIDSF;
      (el)->auxdata<double>("weightMediumID") = elMediumIDSF;
      (el)->auxdata<double>("weightTightID") = elTightIDSF;
    }
  }

}


//iso_3: FCLoose
//iso_4: FCTight
//iso_5: Baseline
//       Muon: PflowLoose_FixedRad
//       Electron: FCLoose
//iso_6: Z selection
//       Muon: PflowLoose_FixedRad
//       Electron: HighPtCaloOnly
//iso_7: W selection
//       Muon: PflowTight_FixedRad
//       Electron: FCTight
//iso_8: Tight_VarRad
//iso_9: Loose_VarRad
//m_isoEgCorrections2: FCLoose
//m_isoEgCorrections3: FCTight
//m_isoEgCorrections4: FCTight
//m_isoEgCorrections5: MediumID HighPtCaloOnly
//m_isoEgCorrections6: MediumID Tight_VarRad
//m_isoEgCorrections7: MediumID Loose_VarRad
//m_isoEgCorrections8: TightID HighPtCaloOnly
//m_isoEgCorrections9: TightID Tight_VarRad
//m_isoEgCorrections10: TightID Loose_VarRad

void FunctionHelper :: electronIsolationDecor(xAOD::Electron *el, int region){

  if(region == 0){
    if( doOnce  || affectedArea[sysVari] == "electron_calibration"){
      (el)->auxdata<char>("FCLooseIso") = (iso_5->accept(*el));
      (el)->auxdata<char>("HighPtCaloOnlyIso") = (iso_6->accept(*el));
      (el)->auxdata<char>("FCTightIso") = (iso_7->accept(*el));
      (el)->auxdata<char>("Tight_VarRadIso") = (iso_8->accept(*el));
      (el)->auxdata<char>("Loose_VarRadIso") = (iso_9->accept(*el));
    }
    if(isMC){
      if( doOnce || affectedArea[sysVari] == "electron_iso_efficiency" || affectedArea[sysVari] == "electron_calibration"){
        double Value = 1.0;
        double elFCLIsoSF = 1;
        m_isoEgCorrections3->getEfficiencyScaleFactor(*el,elFCLIsoSF);
        (el)->auxdata<double>("weightFCLooseIso") = elFCLIsoSF;
        double elFCTIsoSF = 1;
        m_isoEgCorrections4->getEfficiencyScaleFactor(*el,elFCTIsoSF);
        (el)->auxdata<double>("weightFCTightIso") = elFCTIsoSF;

        m_isoEgCorrections5->getEfficiencyScaleFactor(*el,Value);
        (el)->auxdata<double>("weightHighPtCaloOnlyIso_MediumID") = Value;

        m_isoEgCorrections6->getEfficiencyScaleFactor(*el,Value);
        (el)->auxdata<double>("weightTight_VarRadIso_MediumID") = Value;

        m_isoEgCorrections7->getEfficiencyScaleFactor(*el,Value);
        (el)->auxdata<double>("weightLoose_VarRadIso_MediumID") = Value;

        m_isoEgCorrections8->getEfficiencyScaleFactor(*el,Value);
        (el)->auxdata<double>("weightHighPtCaloOnlyIso_TightID") = Value;
        
        m_isoEgCorrections9->getEfficiencyScaleFactor(*el,Value);
        (el)->auxdata<double>("weightTight_VarRadIso_TightID") = Value;
        
        m_isoEgCorrections10->getEfficiencyScaleFactor(*el,Value);
        (el)->auxdata<double>("weightLoose_VarRadIso_TightID") = Value;
      }
    }

  }
}

void FunctionHelper :: electronTriggerDecor(xAOD::Electron *el){

  if(doOnce || affectedArea[sysVari] == "electron_calibration"){
    std::vector<const xAOD::IParticle*> myParticles;
    myParticles.clear();
    myParticles.push_back( el );
    bool trigMatched = (m_trigMatch->match(myParticles,elec_trigger1.c_str(),0.07)) || (m_trigMatch->match(myParticles,elec_trigger2.c_str(),0.07)) || (m_trigMatch->match(myParticles,elec_trigger3.c_str(),0.07));
    (el)->auxdata<char>("triggerMatched") = trigMatched;


    if(isMC){
      double trigEff1 = 0, trigEff2 = 0, trigEff3 = 0;
      m_trigEgEfficienciesMC1->getEfficiencyScaleFactor(*el,trigEff1);
      m_trigEgEfficienciesMC2->getEfficiencyScaleFactor(*el,trigEff2);
      m_trigEgEfficienciesMC3->getEfficiencyScaleFactor(*el,trigEff3);
      double trigSF1 = 1, trigSF2 = 1, trigSF3 = 1;
      m_trigEgCorrections1->getEfficiencyScaleFactor(*el,trigSF1);
      m_trigEgCorrections2->getEfficiencyScaleFactor(*el,trigSF2);
      m_trigEgCorrections3->getEfficiencyScaleFactor(*el,trigSF3);
      std::vector<double> trigSF;
      if(trigMatched){
        trigSF.push_back(trigSF1);
        trigSF.push_back(trigSF2);
        trigSF.push_back(trigSF3);
      }
      else{
        trigSF.push_back((1-trigSF1*trigEff1)/(1-trigEff1));
        trigSF.push_back((1-trigSF2*trigEff2)/(1-trigEff2));
        trigSF.push_back((1-trigSF3*trigEff3)/(1-trigEff3));
      } //store inefficiency
      (el)->auxdata<std::vector<double>>("triggerEfficiencySF") = trigSF;
    }

  }
}

void FunctionHelper :: electronTTVADecor(xAOD::Electron *el){

  if(doOnce || affectedArea[sysVari].find("electron") == 0){
    const xAOD::TrackParticle* trk = (el)->trackParticle();
    float delta_z0 = -999.;
    float d0 = -999., d0_significance = -999.;
    if(trk && trk->definingParametersCovMatrixVec().size() > 0){
      computeImpactParameters(trk,vxContainer,delta_z0,d0);
      if((trk->definingParametersCovMatrixVec())[0] > 0.)  d0_significance = xAOD::TrackingHelpers::d0significance( trk, eventInfo->beamPosSigmaX(), eventInfo->beamPosSigmaY(), eventInfo->beamPosSigmaXY());
    }
    (el)->auxdata<float>("z0") = delta_z0;
    (el)->auxdata<float>("d0") = d0;
    (el)->auxdata<float>("d0Sig") = d0_significance;
    (el)->auxdata<char>("IPID") = (fabs(d0_significance) < 5.0);
  }
}

////////////////
////  Muon  ////
////////////////

void FunctionHelper :: muonIdentificationDecor(xAOD::Muon *mu){

    if(doOnce || affectedArea[sysVari].find("muon") == 0){
      (mu)->auxdata<char>("looseID") = m_muonSelectionLoose->accept(*mu);
      (mu)->auxdata<char>("mediumID") = m_muonSelectionMedium->accept(*mu);
      (mu)->auxdata<char>("tightID") = m_muonSelectionTight->accept(*mu);
    }
    if(isMC){
      if( doOnce || affectedArea[sysVari] == "muon_ID_efficiency" || affectedArea[sysVari] == "muon_calibration"){
        float muMediumIDSF = 1;
        m_effi_corr1->getEfficiencyScaleFactor(*mu,muMediumIDSF);
        (mu)->auxdata<double>("weightMediumID") = muMediumIDSF;
        float muTightIDSF = 1;
        m_effi_corr2->getEfficiencyScaleFactor(*mu,muTightIDSF);
        (mu)->auxdata<double>("weightTightID") = muTightIDSF;
      }

    }

}


//iso_3: FCLoose
//iso_4: FCTight
//iso_5: Baseline
//       Muon: PflowLoose_FixedRad
//       Electron: FCLoose
//iso_6: Z selection
//       Muon: PflowLoose_FixedRad
//       Electron: HighPtCaloOnly
//iso_7: W selection
//       Muon: PflowTight_FixedRad
//       Electron: FCTight
//m_iso_effi_corr1: LooseTrackOnlyIso
//m_iso_effi_corr2: GradientIso
//m_iso_effi_corr3: FixedCutHighPtTrackOnlyIso
//m_iso_effi_corr4: FCTightIso
//m_iso_effi_corr5: FCLooseIso
//m_iso_effi_corr6: PflowLoose_FixedRadIso
//m_iso_effi_corr7: PflowTight_FixedRadIso

void FunctionHelper :: muonIsolationDecor(xAOD::Muon *mu){
    if( doOnce || affectedArea[sysVari] == "muon_calibration" ){
      (mu)->auxdata<char>("FCLooseIso") = (iso_3->accept(*mu));
      (mu)->auxdata<char>("PflowLooseIso") = (iso_5->accept(*mu));
      (mu)->auxdata<char>("PflowTightIso") = (iso_7->accept(*mu));
    }
    if(isMC){
      if( doOnce || affectedArea[sysVari] == "muon_iso_efficiency" || affectedArea[sysVari] == "muon_calibration"){
        float muFCLooseIsoSF = 1;
        if(m_muonSelectionLoose->accept(*mu)) m_iso_effi_corr5->getEfficiencyScaleFactor(*mu,muFCLooseIsoSF);
        (mu)->auxdata<double>("weightFCLooseIso") = muFCLooseIsoSF;
        float muFCLIsoSF = 1;
        if(m_muonSelectionLoose->accept(*mu)) m_iso_effi_corr6->getEfficiencyScaleFactor(*mu,muFCLIsoSF);
        (mu)->auxdata<double>("weightPflowLooseIso") = muFCLIsoSF;
        float muFCTIsoSF = 1;
        if(m_muonSelectionLoose->accept(*mu)) m_iso_effi_corr7->getEfficiencyScaleFactor(*mu,muFCTIsoSF);
        (mu)->auxdata<double>("weightPflowTightIso") = muFCTIsoSF;
      }
    }
}

//m_mutrig_sf: Tight
//m_mutrig_sf_m: Medium

void FunctionHelper :: muonTriggerDecor(xAOD::Muon *mu){
  if( doOnce || affectedArea[sysVari] == "muon_calibration" ){
    (mu)->auxdata<std::string>("matchedTrigger") = "None";
    std::vector<const xAOD::IParticle*> myParticles;
    myParticles.clear();
    myParticles.push_back( mu );
    bool trigMatched = (m_trigMatch->match(myParticles,muon_trigger1.c_str(),0.1)) || (m_trigMatch->match(myParticles,muon_trigger2.c_str(),0.1));
    (mu)->auxdata<char>("triggerMatched") = trigMatched;

    if(isMC){
        double muTrigEffMC1 = 1, muTrigEffMC2 = 1;
        double muTrigEffData1 = 1, muTrigEffData2 = 1;
        if((mu)->auxdata<char>("looseID") && RunNum > 200000){
          m_mutrig_sf_m->getTriggerEfficiency(*mu,muTrigEffMC1,m_muTMstring,false);
          m_mutrig_sf_m->getTriggerEfficiency(*mu,muTrigEffData1,m_muTMstring,true);
          m_mutrig_sf->getTriggerEfficiency(*mu,muTrigEffMC2,m_muTMstring,false);
          m_mutrig_sf->getTriggerEfficiency(*mu,muTrigEffData2,m_muTMstring,true);
        }
        std::vector<double> trigSF;
        if(trigMatched){
          trigSF.push_back(muTrigEffData1/muTrigEffMC1);
          trigSF.push_back(muTrigEffData2/muTrigEffMC2);
        }
        else{
          trigSF.push_back((1-muTrigEffData1)/(1-muTrigEffMC1));
          trigSF.push_back((1-muTrigEffData2)/(1-muTrigEffMC2));
        } //store inefficiency
        (mu)->auxdata<std::vector<double>>("triggerEfficiencySF") = trigSF;
    }

  }
}

void FunctionHelper :: muonTTVADecor(xAOD::Muon *mu){

      if(doOnce || affectedArea[sysVari].find("muon") == 0){
        const xAOD::TrackParticle* trk = (mu)->primaryTrackParticle();
        float delta_z0=-999.;
        float d0 = -999., d0_significance=-999.;
        if(trk && trk->definingParametersCovMatrixVec().size() > 0 && (mu)->muonType()!=xAOD::Muon_v1::MuonStandAlone){
          computeImpactParameters(trk,vxContainer,delta_z0,d0);
          if((trk->definingParametersCovMatrixVec())[0] > 0.) d0_significance = xAOD::TrackingHelpers::d0significance( trk, eventInfo->beamPosSigmaX(), eventInfo->beamPosSigmaY(), eventInfo->beamPosSigmaXY());
        }
        (mu)->auxdata<float>("z0") = delta_z0;
        (mu)->auxdata<float>("d0") = d0;
        (mu)->auxdata<float>("d0Sig") = d0_significance;
        (mu)->auxdata<char>("IPID") = (fabs(d0_significance) < 3.0);
      }

      if(isMC){
        if( doOnce || affectedArea[sysVari] == "muon_TTVA_efficiency" || affectedArea[sysVari] == "muon_calibration"){
          float muIPSF = 1;
          if( (m_muonSelectionLoose->accept(*mu)) && fabs((mu)->eta())<2.5) m_ip_effi_corr->getEfficiencyScaleFactor(*mu,muIPSF);
          (mu)->auxdata<double>("weightIP") = muIPSF;
        }
      }

}
///////////////
////  Jet  ////
///////////////

void FunctionHelper :: jetBtaggingDecor(xAOD::Jet *jt){
  if( doOnce || affectedArea[sysVari] == "jet_calibration"){
    (jt)->auxdata<char>("bTagged") = (fabs(jt->eta())<2.5 && btagtool->accept( *jt ));
  }
  if(isMC && (doOnce || affectedArea[sysVari] == "jet_btag_efficiency" || affectedArea[sysVari] == "jet_calibration")){
    float btsf = 1.;
    if(fabs(jt->eta())<2.5 && (jt)->auxdata<char>("bTagged")) btagefftool->getScaleFactor(*jt,btsf);
    if(fabs(jt->eta())<2.5 && !((jt)->auxdata<char>("bTagged"))) btagefftool->getInefficiencyScaleFactor(*jt,btsf);
    (jt)->auxdata<double>("btagWeight") = btsf;
  }
}

void FunctionHelper :: jetConJvtDecor(xAOD::JetContainer *jetsCorr){

//  if(doOnce) std::cout<<"call jetConJvtDecor"<<std::endl;
  if(doOnce || affectedArea[sysVari] == "jet_calibration"){
    m_jetmod->modify(*jetsCorr); //decorate passFJVT
    if(isMC) jvtsf->tagTruth(jetsCorr, Tjets);
  }
  for( auto jt : *jetsCorr ){
    if(doOnce || affectedArea[sysVari] == "jet_calibration"){
      (jt)->auxdata<char>("passCJVT") = jvtsf->passesJvtCut(*jt);
      (jt)->auxdata<char>("passJVT") = (jt)->auxdata<char>("passCJVT") && (jt)->auxdata<char>("passFJVT"); //fjvt tool marks all the central as passed and jvt tool marks all the forward as passed
    }
    if(isMC){
      if(doOnce || affectedArea[sysVari] == "jet_calibration" || affectedArea[sysVari] == "jet_jvt_efficiency"){
        float current_sf = 1.;
        if((jt)->auxdata<char>("passCJVT")) jvtsf->getEfficiencyScaleFactor(*jt,current_sf);
        else jvtsf->getInefficiencyScaleFactor(*jt,current_sf);
        (jt)->auxdata<double>("cjvtWeight") = current_sf;
      }
      if(doOnce || affectedArea[sysVari] == "jet_calibration" || affectedArea[sysVari] == "jet_fjvt_efficiency"){
        float current_sf = 1.;
        if((jt)->auxdata<char>("passFJVT")) fjvtsf->getEfficiencyScaleFactor(*jt,current_sf);
        else fjvtsf->getInefficiencyScaleFactor(*jt,current_sf);
        (jt)->auxdata<double>("fjvtWeight") = current_sf;
      }
      (jt)->auxdata<double>("jvtWeight") = (jt)->auxdata<double>("cjvtWeight") * (jt)->auxdata<double>("fjvtWeight");
    }

  }

}



void FunctionHelper::setTriggerList(){

  if(RunNum<=284484){//2015
    if(isMC) elec_trigger1 = "HLT_e24_lhmedium_L1EM18VH";
    if(!isMC) elec_trigger1 = "HLT_e24_lhmedium_L1EM20VH";
    elec_trigger2 = "HLT_e60_lhmedium";
    elec_trigger3 = "HLT_e120_lhloose";
  }
  if(RunNum>284484 && RunNum<=302872){//2016 period1
    elec_trigger1 = "HLT_e26_lhtight_nod0_ivarloose";
    elec_trigger2 = "HLT_e60_lhmedium_nod0";
    elec_trigger3 = "HLT_e140_lhloose_nod0";
  }
  if(RunNum>302872){//2016 period2 2017 2018
    elec_trigger1 = "HLT_e26_lhtight_nod0_ivarloose";
    elec_trigger2 = "HLT_e60_lhmedium_nod0";
    elec_trigger3 = "HLT_e140_lhloose_nod0";
  }

  if(RunNum<=284484){//2015
    muon_trigger1 = "HLT_mu20_iloose_L1MU15";
    muon_trigger2 = "HLT_mu50";
    m_muTMstring = "HLT_mu20_iloose_L1MU15_OR_HLT_mu50";
  }
  if(RunNum>284484){//2016 2017 2018
    muon_trigger1 = "HLT_mu26_ivarmedium";
    muon_trigger2 = "HLT_mu50";
    m_muTMstring = "HLT_mu26_ivarmedium_OR_HLT_mu50";
  }

}

float FunctionHelper::CalVertexReweight()
{
  float Value = 0.0;

  for (unsigned int i=0; i<vxContainer->size(); i++){
    const xAOD::Vertex* vtx = (*vxContainer)[i];
    if ( vtx->vertexType() == xAOD::VxType::PriVtx ){
      Value = GetVertexReweight(vtx->z());
    }
  }

  return Value;
}

/*****************************************************************/
float FunctionHelper::GetVertexReweight(float z)
/*****************************************************************/
{
//---- reweight the z-vertex distribution

   if(!isMC) return 1.; //---- only for MC
//   return 1.;//---- needs to be adapted to rel 21. analysis

   // Calculate the vertex reweight, for 2005: reweight all MC using generated vertex !
   Double_t zvtxData[6]; //--- reweight coefficients for Data BH
   Double_t zvtxMC[6];   //--- reweight coefficients for Montecarlo BH

     //--- reweight coefficients for Data and MC

  zvtxData[0]= 0.0;
  zvtxData[1]= 0.0;
  zvtxData[2]= 0.0;

  zvtxMC[0]= 0.0;
  zvtxMC[1]= 0.0;
  zvtxMC[2]= 0.0;

  if( m_Year == 1516 ) {

     zvtxData[0]= 8.68286e+02;
     zvtxData[1]= -1.96805e+00;
     zvtxData[2]= 3.50109e+01;

     zvtxMC[0]= 6.52401e+02;
     zvtxMC[1]= -4.90833e-01;
     zvtxMC[2]= 4.08416e+01;

   }else if( m_Year == 17 ) {

     zvtxData[0]= 9.14535e+02 ;
     zvtxData[1]= -8.20289e-01;
     zvtxData[2]= 3.70448e+01;

     zvtxMC[0]= 8.18176e+02;
     zvtxMC[1]= -2.18801e+00;
     zvtxMC[2]= 3.74505e+01;

   }else if( m_Year == 18 ) {

     zvtxData[0]= 1.16830e+03;
     zvtxData[1]= -4.61993e+00;
     zvtxData[2]= 3.40101e+01;

     zvtxMC[0]=  9.83735e+02;
     zvtxMC[1]=  7.18463e-02;
     zvtxMC[2]=  4.11641e+01 ;

   }


//---- we use a simple Gaussian parametrisation
     zvtxData[3]= 0.0;
     zvtxData[4]= 0.0;
     zvtxData[5]= 0.0;

     zvtxMC[3]=  0.0;
     zvtxMC[4]=  0.0;
     zvtxMC[5]=  0.0;

     Float_t fZvtxWeight=1.; //--- init to 1
 

     double z1= -230.;
     double z2= 230.;

       
       
     const Double_t C1=1.253314137;
     const Double_t C2=0.7071067810;

     double sda=1.,zda=1.;
 
     zda=zvtxData[0]*TMath::Exp(-0.5*pow((z-zvtxData[1])/zvtxData[2],2))+zvtxData[3]+z*zvtxData[4]+pow(z,2)*zvtxData[5];
 
     sda=C1*zvtxData[0]*zvtxData[2]*(TMath::Erf(C2*(zvtxData[1]-z1)/zvtxData[2])
             -TMath::Erf(C2*(zvtxData[1]-z2)/zvtxData[2]))
         +zvtxData[3]*(z2-z1)
         +zvtxData[4]*(z2*z2-z1*z1)/2.
         +zvtxData[5]*(pow(z2,3)-pow(z1,3))/3.;

     zda= (zda/sda);


     double zmc=1;
     double smc=1;
 
     zmc=zvtxMC[0]*TMath::Exp(-0.5*pow((z-zvtxMC[1])/zvtxMC[2],2))+zvtxMC[3]+z*zvtxMC[4]+pow(z,2)*zvtxMC[5];
     smc=C1*zvtxMC[0]*zvtxMC[2]*(TMath::Erf(C2*(zvtxMC[1]-z1)/zvtxMC[2])
             -TMath::Erf(C2*(zvtxMC[1]-z2)/zvtxMC[2]))
         +zvtxMC[3]*(z2-z1)
         +zvtxMC[4]*(z2*z2-z1*z1)/2.
         +zvtxMC[5]*(pow(z2,3)-pow(z1,3))/3.;

     zmc=(zmc/smc);

     if (zmc>0.00001)
     {
         double zweight=zda/zmc;
        if(zweight==0) zweight=1.;
//      if(z>220.||z<-230.) zweight=0.;
         fZvtxWeight=zweight;
       
     }
       
//       printf("zvtx=%f Weight =%f \n",z,fZvtxWeight);
        return fZvtxWeight;

}

void FunctionHelper::overlapDecision(xAOD::ElectronContainer* elsCands, xAOD::ElectronContainer* fwdelsCands, xAOD::MuonContainer* muonsCands, xAOD::JetContainer* jetsCands, std::string inFlag, std::string outFlag, bool doCustomOR){

  if(doOnce || affectedArea[sysVari] == "electron_calibration" || affectedArea[sysVari] == "muon_calibration" || affectedArea[sysVari] == "jet_calibration"){

    if(!elsCands || !muonsCands || !jetsCands) return;

    const ort::inputDecorator_t selectDec(OR_inputTag);
    const ort::outputDecorator_t overlapDec(OR_outputTag);
    const ort::outputAccessor_t overlapAcc(OR_outputTag);

    for( auto el : *elsCands ) {
      if((el)->auxdata<char>(inFlag.c_str())) selectDec(*el) = true;
      else selectDec(*el) = false;
//      (el)->auxdata<double>("closestJetDR") = 999;
    }
    for( auto mu : *muonsCands ) {
      if((mu)->auxdata<char>(inFlag.c_str())) selectDec(*mu) = true;
      else selectDec(*mu) = false;
    }
    for( auto jt : *jetsCands ) {
      if((jt)->auxdata<char>(inFlag.c_str())) selectDec(*jt) = true;
      else selectDec(*jt) = false;
    }

    toolBox->masterTool->removeOverlaps(elsCands, muonsCands, jetsCands);

/*    for( auto mu : *muonsCands ){
      if(overlapAcc(*mu) == true) (mu)->auxdata<char>(outFlag.c_str()) = true;
      else (mu)->auxdata<char>(outFlag.c_str()) = false;
      selectDec(*mu) = false;
      overlapDec(*mu) = false;
    }
    for( auto el : *elsCands ){
      if(overlapAcc(*el) == true) (el)->auxdata<char>(outFlag.c_str()) = true;
      else (el)->auxdata<char>(outFlag.c_str()) = false;
      selectDec(*el) = false;
      overlapDec(*el) = false;
    }
    for( auto jt : *jetsCands ){
      if(overlapAcc(*jt) == true) (jt)->auxdata<char>(outFlag.c_str()) = true;
      else (jt)->auxdata<char>(outFlag.c_str()) = false;
      selectDec(*jt) = false;
      overlapDec(*jt) = false;
    }
*/

    if(!doCustomOR) return;

//e-e OR
    for( auto el : *elsCands ) {
      if(!((el)->auxdata<char>(inFlag.c_str()))) continue;
      if(((el)->auxdata<char>(outFlag.c_str()))) continue;
      for( auto orel : *elsCands ) {
        if(el == orel) continue;
        if(!((orel)->auxdata<char>(inFlag.c_str()))) continue;
        if(((orel)->auxdata<char>(outFlag.c_str()))) continue;
        double delta_cl_eta = el->caloCluster()->eta() - orel->caloCluster()->eta();
//        double delta_cl_phi = fabs(remainder(fabs(el->caloCluster()->phi() - orel->caloCluster()->phi()),2*TMath::Pi()));
        double delta_cl_phi = fabs(DeltaPhi(el->caloCluster()->phi(), orel->caloCluster()->phi()));
        if(xAOD::EgammaHelpers::getOriginalTrackParticleFromGSF(el->trackParticle()) == xAOD::EgammaHelpers::getOriginalTrackParticleFromGSF(orel->trackParticle())){
          if((el->pt()) < (orel->pt())){
//            (el)->auxdata<char>(outFlag.c_str()) = 1;
            (el)->auxdata<char>(Additional_OR_Tag.c_str()) = 1;
          }
        }
        if(fabs(delta_cl_eta)<3*0.025 && fabs(delta_cl_phi)<5*0.025){
          if((el->caloCluster()->pt()) < (orel->caloCluster()->pt())){
//            (el)->auxdata<char>(outFlag.c_str()) = 1;
            (el)->auxdata<char>(Additional_OR_Tag.c_str()) = 1;
          }
        }
      }
    }

//e-mu OR
    for( auto mu : *muonsCands ) {
      if(!((mu)->auxdata<char>(inFlag.c_str()))) continue;
      if(((mu)->auxdata<char>(outFlag.c_str()))) continue;
      for( auto orel : *elsCands ) {
        if(!((orel)->auxdata<char>(inFlag.c_str()))) continue;
        if(((orel)->auxdata<char>(outFlag.c_str()))) continue;
        if(xAOD::Muon::CaloTagged == mu->muonType()){
          if(xAOD::EgammaHelpers::getOriginalTrackParticleFromGSF(orel->trackParticle()) == (mu->trackParticle(xAOD::Muon::InnerDetectorTrackParticle))){
//            (mu)->auxdata<char>(outFlag.c_str()) = 1;
            (mu)->auxdata<char>(Additional_OR_Tag.c_str()) = 1;
          }
        }
      }
    }

  }//end if

}

void FunctionHelper::MatrixoverlapDecision(xAOD::ElectronContainer* elsCands, xAOD::ElectronContainer* fwdelsCands, xAOD::MuonContainer* muonsCands, xAOD::JetContainer* jetsCands, std::string inFlag, std::string outFlag, bool doCustomOR){
  if(doOnce || affectedArea[sysVari] == "electron_calibration" || affectedArea[sysVari] == "muon_calibration" || affectedArea[sysVari] == "jet_calibration"){

    if(!elsCands || !muonsCands || !jetsCands) return;

    for( auto el : *elsCands ) {
      if(!((el)->auxdata<char>(inFlag.c_str()))) continue;
      for( auto jt : *jetsCands) {
        if(!((jt)->auxdata<char>(inFlag.c_str()))) continue;
        if(((el)->p4()).DeltaR((jt)->p4()) < 0.4){
          (el)->auxdata<char>(outFlag.c_str()) = 1;
        }
      }
    }

    for( auto mu : *muonsCands ) {
      if(!((mu)->auxdata<char>(inFlag.c_str()))) continue;
      for( auto jt : *jetsCands) {
        if(!((jt)->auxdata<char>(inFlag.c_str()))) continue;
        if(((mu)->p4()).DeltaR((jt)->p4()) < 0.4){
          (mu)->auxdata<char>(outFlag.c_str()) = 1;
        }
      }
    }

  }


}

bool FunctionHelper::doSystematicVariation(CP::SystematicSet sysVari){
    bool isSysOK = false;
    CP::SystematicSet sysVariBase;
    if(!sysVari.getBaseNames().empty()) sysVariBase.insert(CP::SystematicVariation(*(sysVari.getBaseNames().begin())));  //fuck you met sys tool, seriously, fuck you
    if(m_muonCalibrationAndSmearingTool->applySystematicVariation(sysVari) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_EleCalibTool->applySystematicVariation(sysVari) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_jesUncert->applySystematicVariation(sysVari) == CP::SystematicCode::Ok) isSysOK = true;
    if(metSystTool->applySystematicVariation(sysVariBase) == CP::SystematicCode::Ok) isSysOK = true;  //look how special you are!
    if(m_effi_corr1->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_effi_corr2->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    //if(m_iso_effi_corr1->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    //if(m_iso_effi_corr2->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    //if(m_iso_effi_corr3->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    //if(m_iso_effi_corr4->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_iso_effi_corr5->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_iso_effi_corr6->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_iso_effi_corr7->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_ip_effi_corr->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_recoEgCorrections->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_idEgCorrections2->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_idEgCorrections3->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_idFwdEgCorrections1->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_idFwdEgCorrections2->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_idFwdEgCorrections3->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_isoEgCorrections2->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_isoEgCorrections3->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_isoEgCorrections4->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_isoEgCorrections5->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_isoEgCorrections6->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_isoEgCorrections7->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_isoEgCorrections8->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_isoEgCorrections9->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_isoEgCorrections10->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_trigEgEfficienciesMC1->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_trigEgCorrections1->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_trigEgEfficienciesMC2->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_trigEgCorrections2->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_trigEgEfficienciesMC3->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_trigEgCorrections3->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_trigEgEfficienciesMC4->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_trigEgCorrections4->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_mutrig_sf->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_mutrig_sf_m->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(m_prwTool->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(jvtsf->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(fjvtsf->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    if(btagefftool->applySystematicVariation( sysVari ) == CP::SystematicCode::Ok) isSysOK = true;
    return isSysOK;
}

void FunctionHelper::updateCutFlow(TH1D *inCutFlow, std::map<std::string, double> *inLabelMap, std::string cutName, double step, bool doUpdate){
  if(!doUpdate) return;
  double Xpos = -1;
  if(inLabelMap->count(cutName)){
    Xpos = (*inLabelMap)[cutName];
  }
  else{
    (*inLabelMap)[cutName] = inLabelMap->size() * 1.; //this will gives 1 when first call, strange ... doesn't happen with stand alone root run
    std::cout<<"registering new cut "<<cutName<<" at position "<<(*inLabelMap)[cutName]<<std::endl;
    inCutFlow->GetXaxis()->SetBinLabel(inLabelMap->size()+1, cutName.c_str());
    Xpos = (*inLabelMap)[cutName];
  }
  inCutFlow->Fill(Xpos,step);
}

double FunctionHelper::DeltaPhi(double Phi1, double Phi2)
{
 double Pi = TMath::Pi();

 double Value = Phi1 - Phi2;

 while (Value >= Pi) Value -= 2.0 * Pi;
 while (Value < Pi * (-1.0)) Value += 2.0 * Pi;

 return Value;
}

