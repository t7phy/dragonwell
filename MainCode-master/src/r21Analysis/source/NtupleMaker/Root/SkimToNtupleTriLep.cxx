#include "NtupleMaker/SkimToNtupleTriLep.h"

//////////////////////////////////////////////
//
//  This is another way to store the skimmed ntuple
//
/////////////////////////////////////////////

SkimToNtupleTriLep :: SkimToNtupleTriLep (const std::string& name,
                                  ISvcLocator *pSvcLocator)
    : SelectionWZ (name, pSvcLocator)
{
  // Here you put any code for the base initialization of variables,
  // e.g. init all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // init().
  doDeliver = true;
  m_isTest = 0;
  doOutAOD = 0;
  systemCode = 0;
  declareProperty( "outputName", outputName = "myOutput", "folder name of output ntuples" );
  declareProperty( "maxSys", maxSys = -1, "number of maximum systematics to process" );

  runWZPolarization = true;
  //isBaselined0Sig = true;
}

bool SkimToNtupleTriLep :: init ()
{
  SelectionWZ::init();

  TFile *outputFile = wk()->getOutputFile (outputName);

  metaTree =  new TTree("metaTree","metaTree");
  metaTree->Branch("runNumber", &runNumber);
  metaTree->Branch("mcChannelNumber", &mcChannelNumber);
  metaTree->Branch("totalWeightedEntries", &sumOfWeights);
  metaTree->Branch("crossSection", &crossSection);
  metaTree->Branch("inputFileName", &AODname);
  metaTree->Branch("WeightNames", "vector<string>", &WeightNames);
  metaTree->SetDirectory(outputFile);

  event_CutFlow->SetDirectory(outputFile);
  electron_CutFlow->SetDirectory(outputFile);
  electronFwd_CutFlow->SetDirectory(outputFile);
  muon_CutFlow->SetDirectory(outputFile);
  photon_CutFlow->SetDirectory(outputFile);
  jet_CutFlow->SetDirectory(outputFile);
  event_CutFlow_W->SetDirectory(outputFile);
  truth_CutFlow->SetDirectory(outputFile);

  int n_sys = m_sysList.size();
  std::cout<<"n_sys: "<<n_sys<<std::endl;

  for(int isys=0; isys<n_sys; isys++){
    sysname = m_sysList.at(isys).name();
    std::cout<<"registered "<<sysname<<std::endl;
  }

  treeAna = new TTree("SelectedEvents","SelectedEvents");
  treeAna->SetDirectory(outputFile);
  SetupBranches(treeAna);

  TruthTree = new TTree("TruthEvents", "TruthEvents");
  TruthTree->SetDirectory(outputFile);
  SetupTruthBranches(TruthTree);

  return true;

}

bool SkimToNtupleTriLep :: loop ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  //Clear or init the output branches each loop

//  int isys = -1;
//  for (auto sysVari : m_sysList){
//std::cout<<std::endl;
  for (int isys = 0; isys<m_sysList.size(); isys++){
//  for (int isys = 0; isys<2; isys++){
//    isys++;
//if(isys != 0 && isys != 1) continue;
    sysVari = m_sysList.at(isys);
    sysname = sysVari.name();
    if(!isMC && sysname!="") continue;
    if(maxSys >= 0 && isys > maxSys) continue;
    if(SkipSystematic()) continue;

//std::cout<<sysname<<std::endl;
    ResetEvent();

    if(!doSystematicVariation(sysVari)) Error("loop()", "Systematic Unsupported");

    //doOnce = (sysname=="");
    doOnce = !isys;

/*    if(doOnce && isMC){//save truth information
      if(doTruthSelection){
        for(  auto tPar : *xTruthParticleContainer  ){
          if(!((tPar)->auxdecor<char>("isWZLepton")) && !((tPar)->auxdecor<char>("isHardElectron")) && !((tPar)->auxdecor<char>("isHardMuon"))) continue;
          Record_Object(tPar, "truth");
        }
        TruthTree->Fill();
      }
    }
*/
    if(!SelectionWZ::loop()) continue;

    Systematic = (sysname=="")?"nominal":sysname;

    AverageMu = eventInfo->auxdata<float>("corrected_averageInteractionsPerCrossing");//= eventInfo->averageInteractionsPerCrossing();
    OriginRunNumber = eventInfo->runNumber();
    ChannelNumber = isMC?(eventInfo->mcChannelNumber()):0;
    RunNumber = RunNum;
    EventNumber = EvtNum;
    TriggerPassed = isTriggerPassed;

    float mcEventWeight = 1.;
    float mcWeightPRW = 1.;
    VertexWeight = 1.0;

    if(isMC){
      // Apply MC event weight
      mcEventWeight = eventInfo->mcEventWeight();
      if(doOnce) MCEventWeights = eventInfo->mcEventWeights();

//      std::cout<<"Weight size: "<<eventInfo->mcEventWeights().size()<<std::endl;
//      for(int iweight = 0; iweight < eventInfo->mcEventWeights().size(); iweight++){
//        std::cout<<"No."<<iweight<<": "<<eventInfo->mcEventWeights().at(iweight)<<std::endl;
//      }


      // Apply pile-up reweighting 
//      mcWeightPRW = eventInfo->auxdata< float >("PileupWeight");
      MCPileupWeight = m_prwTool->getCombinedWeight( *eventInfo );

      MCEventWeight = mcEventWeight;

      KFactor = eventInfo->auxdata< float >("KFactor");

      VertexWeight = CalVertexReweight();
    }

    if(doOnce && isMC){//save truth information
      if(doTruthSelection){
        for(  auto tPar : *xTruthParticleContainer  ){
          if(!((tPar)->auxdecor<char>("isWZLepton")) && !((tPar)->auxdecor<char>("isHardElectron")) && !((tPar)->auxdecor<char>("isHardMuon")) && !((tPar)->auxdecor<char>("isBareLepton")) && !((tPar)->auxdecor<char>("isPhoton"))) continue;
          Record_Object(tPar, "truth");
        }
        TruthTree->Fill();
        truth_e.clear() ;
        truth_eta.clear() ;
        truth_phi.clear() ;
        truth_pt.clear() ;
        truth_pid.clear() ;
        truth_mid.clear() ;
        truth_bare_e.clear() ;
        truth_bare_eta.clear() ;
        truth_bare_phi.clear() ;
        truth_bare_pt.clear() ;
        truth_bare_pid.clear() ;
        truth_dressed_e.clear() ;
        truth_dressed_eta.clear() ;
        truth_dressed_phi.clear() ;
        truth_dressed_pt.clear() ;
        truth_dressed_pid.clear() ;
        truth_photon_e.clear() ;
        truth_photon_eta.clear() ;
        truth_photon_phi.clear() ;
        truth_photon_pt.clear() ;
        truth_photon_mid.clear() ;
      }
    }

    met_et = metsCorr->Pt();
    met_px = metsCorr->Px();
    met_py = metsCorr->Py();

    truthPropagator_px = truthPropagator.Px();
    truthPropagator_py = truthPropagator.Py();
    truthPropagator_pz = truthPropagator.Pz();
    truthPropagator_e = truthPropagator.E();

    if(RunNumber == 40833){
      std::cout<<RunNumber<<" "<<met_et<<std::endl;
    }

//std::cout<<Sta_TotalNumber<<" "<<Systematic<<" Before cut"<<std::endl;
    if(ShouldRecord()){
//std::cout<<Sta_TotalNumber<<" "<<Systematic<<" After cut"<<std::endl;

      std::map<double, xAOD::Muon *>::iterator muonIter; //!
      std::map<double, xAOD::Electron *>::iterator electronIter; //!
      std::map<double, xAOD::Electron *>::iterator fwdelectronIter;
      std::map<double, xAOD::Jet *>::iterator jetIter; //!

      for(  electronIter = (*electronMap).begin(); electronIter != (*electronMap).end(); electronIter++  ){

        updateCutFlow(electron_CutFlow, electron_CutNameMap, ">=3 baseline", 1, doOnce);

        if((electronIter->second)->auxdata<char>(OR_outputTag)) continue;
        updateCutFlow(electron_CutFlow, electron_CutNameMap, "overlaps", 1, doOnce);
        if((electronIter->second)->auxdata<char>(Additional_OR_Tag)) continue;
        updateCutFlow(electron_CutFlow, electron_CutNameMap, "AdditionalOverlaps", 1, doOnce);
        nSoftElectrons++;

//        if(!((electronIter->second)->auxdata<char>(OR_outputTag))){
//          updateCutFlow(electron_CutFlow, electron_CutNameMap, "overlaps", 1, doOnce);
//          nSoftElectrons++;
//        }

        if(!((electronIter->second)->auxdata<char>("isHard"))) continue;
        updateCutFlow(electron_CutFlow, electron_CutNameMap, "isHard", 1, doOnce);

        Record_Object((electronIter->second), "elec");

//std::cout<<"el pt:"<<electronIter->second->pt()<<std::endl;
      }

      if(doTruthSelection){
        for(  auto tPar : *xTruthParticleContainer  ){

          if(!((tPar)->auxdecor<char>("isWZLepton")) && !((tPar)->auxdecor<char>("isHardElectron")) && !((tPar)->auxdecor<char>("isHardMuon")) && !((tPar)->auxdecor<char>("isBareLepton")) && !((tPar)->auxdecor<char>("isPhoton"))) continue;

          Record_Object(tPar, "truth");

        }
      }

      for(  muonIter = (*muonMap).begin(); muonIter != (*muonMap).end(); muonIter++  ){

        updateCutFlow(muon_CutFlow, muon_CutNameMap, ">=3 baseline", 1, doOnce);

        if((muonIter->second)->auxdata<char>(OR_outputTag)) continue;
        updateCutFlow(muon_CutFlow, muon_CutNameMap, "overlaps", 1, doOnce);
        if((muonIter->second)->auxdata<char>(Additional_OR_Tag)) continue;
        updateCutFlow(muon_CutFlow, muon_CutNameMap, "AdditionalOverlaps", 1, doOnce);
        nSoftMuons++;

//        if(!((muonIter->second)->auxdata<char>(OR_outputTag))){
//          updateCutFlow(muon_CutFlow, muon_CutNameMap, "overlaps", 1, doOnce);
//          nSoftMuons++;
//        }

        if(!((muonIter->second)->auxdata<char>("isHard"))) continue;
        updateCutFlow(muon_CutFlow, muon_CutNameMap, "isHard", 1, doOnce);

        Record_Object((muonIter->second), "muon");

//std::cout<<"mu pt:"<<muonIter->second->pt()<<std::endl;
      }

      JetWeight = 1.;
      for(  jetIter = (*jetMap).begin(); jetIter != (*jetMap).end(); jetIter++  ){

        updateCutFlow(jet_CutFlow, jet_CutNameMap, ">=3 baseline", 1, doOnce);

        if((jetIter->second)->auxdata<char>(OR_outputTag)) continue;
        updateCutFlow(jet_CutFlow, jet_CutNameMap, "overlaps", 1, doOnce);
        nSoftJets++;
        if(!((jetIter->second)->auxdata<char>("isHard"))) continue;
        updateCutFlow(jet_CutFlow, jet_CutNameMap, "isHard", 1, doOnce);
        if(isMC) JetWeight *= (jetIter->second)->auxdata<double>("btagWeight") * (jetIter->second)->auxdata<double>("jvtWeight");

        Record_Object((jetIter->second), "jet");

      }

      treeAna->Fill();


    }

  }
  return true;
} // end of loop

StatusCode SkimToNtupleTriLep :: finish ()
{

  SelectionHelper::finish();

  for(int it=0;it<vec_AODname->size();it++){
    runNumber = vec_runNumber->at(it);
    mcChannelNumber = vec_mcChannelNumber->at(it);
    sumOfWeights = vec_sumOfWeights->at(it);
    crossSection = vec_crossSection->at(it);
    AODname = vec_AODname->at(it);
    std::cout<<"bookkeeping "<<AODname<<", "<<sumOfWeights<<std::endl;
    metaTree->Fill();
  }

  return StatusCode::SUCCESS;

}

bool SkimToNtupleTriLep::ShouldRecord(void)
{
   if(!isPassJetCleaning) return false;
   if(!isPassVTX) return false;
   if(!isPassTrigger) return false;

   if((electronMap)->size()+(muonMap)->size()<3) return false;
   updateCutFlow(event_CutFlow, event_CutNameMap, ">=3 baseline leptons", 1, doOnce);

   return true;
}

void SkimToNtupleTriLep::SetupBranches(TTree* tree){

  tree->Branch("Systematic", &Systematic);

  tree->Branch("EventNumber", &EventNumber,"EventNumber/L");
  tree->Branch("RunNumber", &RunNumber,"RunNumber/L");
  tree->Branch("OriginRunNumber", &OriginRunNumber,"OriginRunNumber/L");
  tree->Branch("ChannelNumber", &ChannelNumber,"ChannelNumber/L");
  tree->Branch("AverageMu", &AverageMu,"AverageMu/F");
  tree->Branch("Year", &m_Year,"Year/L");

  tree->Branch("MCEventWeight", &MCEventWeight,"MCEventWeight/F");
  tree->Branch("MCEventWeights", "vector<float>", &MCEventWeights);
  tree->Branch("MCPileupWeight", &MCPileupWeight,"MCPileupWeight/F");
  tree->Branch("JetWeight", &JetWeight,"JetWeight/F");
  tree->Branch("KFactor", &KFactor,"KFactor/F");
  tree->Branch("VertexWeight", &VertexWeight, "VertexWeight/F");
  tree->Branch("met_et", &met_et,"met_et/F");
  tree->Branch("met_px", &met_px,"met_px/F");
  tree->Branch("met_py", &met_py,"met_py/F");

  tree->Branch("nSoftMuons", &nSoftMuons, "nSoftMuons/I");
  tree->Branch("nSoftElectrons", &nSoftElectrons, "nSoftElectrons/I");
  tree->Branch("nSoftJets", &nSoftJets, "nSoftJets/I");

  tree->Branch("el_e", "vector<float>", &el_e);
  tree->Branch("el_eta", "vector<float>", &el_eta);
  tree->Branch("el_phi", "vector<float>", &el_phi);
  tree->Branch("el_pt", "vector<float>", &el_pt);
  tree->Branch("el_charge", "vector<float>", &el_charge);
  tree->Branch("el_d0Sig", "vector<float>", &el_d0Sig);
  tree->Branch("el_mediumID", "vector<int>", &el_mediumID);
  tree->Branch("el_mediumIDWeight", "vector<float>", &el_mediumIDWeight);
  tree->Branch("el_tightID", "vector<int>", &el_tightID);
  tree->Branch("el_tightIDWeight", "vector<float>", &el_tightIDWeight);
  tree->Branch("el_FCLooseIso", "vector<int>", &el_FCLooseIso);
  tree->Branch("el_FCLooseIsoWeight", "vector<float>", &el_FCLooseIsoWeight);
  tree->Branch("el_FCTightIso", "vector<int>", &el_FCTightIso);
  tree->Branch("el_FCTightIsoWeight", "vector<float>", &el_FCTightIsoWeight);
  tree->Branch("el_HighPtCaloOnlyIso", "vector<int>", &el_HighPtCaloOnlyIso);
  tree->Branch("el_HighPtCaloOnly_MediumID_IsoWeight", "vector<float>", &el_HighPtCaloOnly_MediumID_IsoWeight);
  tree->Branch("el_HighPtCaloOnly_TightID_IsoWeight", "vector<float>", &el_HighPtCaloOnly_TightID_IsoWeight);
  tree->Branch("el_Tight_VarRadIso", "vector<int>", &el_Tight_VarRadIso);
  tree->Branch("el_Tight_VarRad_MediumID_IsoWeight", "vector<float>", &el_Tight_VarRad_MediumID_IsoWeight);
  tree->Branch("el_Tight_VarRad_TightID_IsoWeight", "vector<float>", &el_Tight_VarRad_TightID_IsoWeight);
  tree->Branch("el_Loose_VarRadIso", "vector<int>", &el_Loose_VarRadIso);
  tree->Branch("el_Loose_VarRad_MediumID_IsoWeight", "vector<float>", &el_Loose_VarRad_MediumID_IsoWeight);
  tree->Branch("el_Loose_VarRad_TightID_IsoWeight", "vector<float>", &el_Loose_VarRad_TightID_IsoWeight);
  tree->Branch("el_triggerMatched", "vector<int>", &el_triggerMatched);
  tree->Branch("el_truthMatched", "vector<int>", &el_truthMatched);
  tree->Branch("el_recoWeight", "vector<float>", &el_recoWeight);
  tree->Branch("el_isbaseline", "vector<int>", &el_isbaseline);
  tree->Branch("el_isAmbiguity", "vector<int>", &el_isAmbiguity);

  tree->Branch("mu_e", "vector<float>", &mu_e);
  tree->Branch("mu_eta", "vector<float>", &mu_eta);
  tree->Branch("mu_phi", "vector<float>", &mu_phi);
  tree->Branch("mu_pt", "vector<float>", &mu_pt);
  tree->Branch("mu_charge", "vector<float>", &mu_charge);
  tree->Branch("mu_d0Sig", "vector<float>", &mu_d0Sig);
  tree->Branch("mu_mediumID", "vector<int>", &mu_mediumID);
  tree->Branch("mu_mediumIDWeight", "vector<float>", &mu_mediumIDWeight);
  tree->Branch("mu_tightID", "vector<int>", &mu_tightID);
  tree->Branch("mu_tightIDWeight", "vector<float>", &mu_tightIDWeight);
  tree->Branch("mu_FCLooseIso", "vector<int>", &mu_FCLooseIso);
  tree->Branch("mu_FCLooseIsoWeight", "vector<float>", &mu_FCLooseIsoWeight);
  tree->Branch("mu_FCTightIso", "vector<int>", &mu_FCTightIso);
  tree->Branch("mu_FCTightIsoWeight", "vector<float>", &mu_FCTightIsoWeight);
  tree->Branch("mu_PflowLooseIso", "vector<int>", &mu_PflowLooseIso);
  tree->Branch("mu_PflowLooseIsoWeight", "vector<float>", &mu_PflowLooseIsoWeight);
  tree->Branch("mu_PflowTightIso", "vector<int>", &mu_PflowTightIso);
  tree->Branch("mu_PflowTightIsoWeight", "vector<float>", &mu_PflowTightIsoWeight);
  tree->Branch("mu_triggerMatched", "vector<int>", &mu_triggerMatched);
  tree->Branch("mu_truthMatched", "vector<int>", &mu_truthMatched);
  tree->Branch("mu_IPWeight", "vector<float>", &mu_IPWeight);
  tree->Branch("mu_isbaseline", "vector<int>", &mu_isbaseline);

  tree->Branch("jt_e", "vector<float>", &jt_e);
  tree->Branch("jt_eta", "vector<float>", &jt_eta);
  tree->Branch("jt_phi", "vector<float>", &jt_phi);
  tree->Branch("jt_pt", "vector<float>", &jt_pt);
  tree->Branch("jt_passJVT", "vector<int>", &jt_passJVT);
  tree->Branch("jt_passBtag", "vector<int>", &jt_passBtag);

  tree->Branch("truth_e", "vector<float>", &truth_e);
  tree->Branch("truth_eta", "vector<float>", &truth_eta);
  tree->Branch("truth_phi", "vector<float>", &truth_phi);
  tree->Branch("truth_pt", "vector<float>", &truth_pt);
  tree->Branch("truth_pid", "vector<int>", &truth_pid);
  tree->Branch("truth_mid", "vector<int>", &truth_mid);
  tree->Branch("truth_bare_e", "vector<float>",   &truth_bare_e);
  tree->Branch("truth_bare_eta", "vector<float>", &truth_bare_eta);
  tree->Branch("truth_bare_phi", "vector<float>", &truth_bare_phi);
  tree->Branch("truth_bare_pt", "vector<float>",  &truth_bare_pt);
  tree->Branch("truth_bare_pid", "vector<int>",  &truth_bare_pid);
  tree->Branch("truth_dressed_e", "vector<float>",   &truth_dressed_e);
  tree->Branch("truth_dressed_eta", "vector<float>", &truth_dressed_eta);
  tree->Branch("truth_dressed_phi", "vector<float>", &truth_dressed_phi);
  tree->Branch("truth_dressed_pt", "vector<float>",  &truth_dressed_pt);
  tree->Branch("truth_dressed_pid", "vector<int>",   &truth_dressed_pid);
  tree->Branch("truth_photon_e", "vector<float>",   &truth_photon_e);
  tree->Branch("truth_photon_eta", "vector<float>", &truth_photon_eta);
  tree->Branch("truth_photon_phi", "vector<float>", &truth_photon_phi);
  tree->Branch("truth_photon_pt", "vector<float>",  &truth_photon_pt);
  tree->Branch("truth_photon_mid", "vector<int>",   &truth_photon_mid);

  tree->Branch("truthPropagator_px", &truthPropagator_px,"truthPropagator_px/F");
  tree->Branch("truthPropagator_py", &truthPropagator_py,"truthPropagator_py/F");
  tree->Branch("truthPropagator_pz", &truthPropagator_pz,"truthPropagator_pz/F");
  tree->Branch("truthPropagator_e", &truthPropagator_e,"truthPropagator_e/F");
  tree->Branch("pdgSequence", &pdgSequence,"pdgSequence/L");

}

void SkimToNtupleTriLep::SetupTruthBranches(TTree* tree){

  tree->Branch("EventNumber", &EventNumber,"EventNumber/L");
  tree->Branch("RunNumber", &RunNumber,"RunNumber/L");
  tree->Branch("OriginRunNumber", &OriginRunNumber,"OriginRunNumber/L");
  tree->Branch("ChannelNumber", &ChannelNumber,"ChannelNumber/L");
  tree->Branch("AverageMu", &AverageMu,"AverageMu/F");
  tree->Branch("Year", &m_Year,"Year/L");

  tree->Branch("MCEventWeight", &MCEventWeight,"MCEventWeight/F");
  tree->Branch("MCEventWeights", "vector<float>", &MCEventWeights);
  tree->Branch("MCPileupWeight", &MCPileupWeight,"MCPileupWeight/F");
  tree->Branch("JetWeight", &JetWeight,"JetWeight/F");
  tree->Branch("KFactor", &KFactor,"KFactor/F");
  tree->Branch("VertexWeight", &VertexWeight, "VertexWeight/F");

  tree->Branch("truth_e", "vector<float>", &truth_e);
  tree->Branch("truth_eta", "vector<float>", &truth_eta);
  tree->Branch("truth_phi", "vector<float>", &truth_phi);
  tree->Branch("truth_pt", "vector<float>", &truth_pt);
  tree->Branch("truth_pid", "vector<int>", &truth_pid);
  tree->Branch("truth_mid", "vector<int>", &truth_mid);
  tree->Branch("truth_bare_e", "vector<float>",   &truth_bare_e);
  tree->Branch("truth_bare_eta", "vector<float>", &truth_bare_eta);
  tree->Branch("truth_bare_phi", "vector<float>", &truth_bare_phi);
  tree->Branch("truth_bare_pt", "vector<float>",  &truth_bare_pt);
  tree->Branch("truth_bare_pid", "vector<int>",  &truth_bare_pid);
  tree->Branch("truth_dressed_e", "vector<float>",   &truth_dressed_e);
  tree->Branch("truth_dressed_eta", "vector<float>", &truth_dressed_eta);
  tree->Branch("truth_dressed_phi", "vector<float>", &truth_dressed_phi);
  tree->Branch("truth_dressed_pt", "vector<float>",  &truth_dressed_pt);
  tree->Branch("truth_dressed_pid", "vector<int>",   &truth_dressed_pid);
  tree->Branch("truth_photon_e", "vector<float>",   &truth_photon_e);
  tree->Branch("truth_photon_eta", "vector<float>", &truth_photon_eta);
  tree->Branch("truth_photon_phi", "vector<float>", &truth_photon_phi);
  tree->Branch("truth_photon_pt", "vector<float>",  &truth_photon_pt);
  tree->Branch("truth_photon_mid", "vector<int>",   &truth_photon_mid);
}

void SkimToNtupleTriLep::ResetEvent(void){

  Systematic = "unknown";

  EventNumber = -999;
  RunNumber = -999;
  OriginRunNumber = -999;
  ChannelNumber = -999;
  AverageMu = -999;
  isTrigMatched = 0;
  TriggerPassed = 0;

  MCEventWeight = 1;
  MCPileupWeight = 1;
  JetWeight = 1;
  KFactor = 1;

  met_et = 0;
  met_px = 0;
  met_py = 0;

  nSoftMuons = 0;
  nSoftElectrons = 0;
  nSoftJets = 0;

  met_et = 0;
  met_px = 0;
  met_py = 0;

  el_e.clear() ;
  el_eta.clear() ;
  el_cl_eta.clear() ;
  el_phi.clear() ;
  el_pt.clear() ;
  el_charge.clear() ;
  el_d0Sig.clear() ;
  el_truthMatched.clear() ;
  el_mediumID.clear() ;
  el_mediumIDWeight.clear() ;
  el_tightID.clear() ;
  el_tightIDWeight.clear() ;
  el_FCLooseIso.clear() ;
  el_FCLooseIsoWeight.clear() ;
  el_FCTightIso.clear() ;
  el_FCTightIsoWeight.clear() ;
  el_HighPtCaloOnlyIso.clear() ;
  el_HighPtCaloOnly_MediumID_IsoWeight.clear() ;
  el_HighPtCaloOnly_TightID_IsoWeight.clear() ;
  el_Tight_VarRadIso.clear() ;
  el_Tight_VarRad_MediumID_IsoWeight.clear() ;
  el_Tight_VarRad_TightID_IsoWeight.clear() ;
  el_Loose_VarRadIso.clear() ;
  el_Loose_VarRad_MediumID_IsoWeight.clear() ;
  el_Loose_VarRad_TightID_IsoWeight.clear() ;
  el_triggerMatched.clear() ;
  el_recoWeight.clear() ;
  el_isbaseline.clear() ;
  el_isAmbiguity.clear() ;

  mu_e.clear() ;
  mu_eta.clear() ;
  mu_phi.clear() ;
  mu_pt.clear() ;
  mu_charge.clear() ;
  mu_d0Sig.clear() ;
  mu_truthMatched.clear() ;
  mu_mediumID.clear() ;
  mu_mediumIDWeight.clear() ;
  mu_tightID.clear() ;
  mu_tightIDWeight.clear() ;
  mu_FCLooseIso.clear() ;
  mu_FCLooseIsoWeight.clear() ;
  mu_FCTightIso.clear() ;
  mu_FCTightIsoWeight.clear() ;
  mu_PflowLooseIso.clear() ;
  mu_PflowLooseIsoWeight.clear() ;
  mu_PflowTightIso.clear() ;
  mu_PflowTightIsoWeight.clear() ;
  mu_triggerMatched.clear() ;
  mu_IPWeight.clear() ;
  mu_isbaseline.clear() ;

  jt_e.clear() ;
  jt_eta.clear() ;
  jt_phi.clear() ;
  jt_pt.clear() ;
  jt_passJVT.clear() ;
  jt_passBtag.clear() ;

  truth_e.clear() ;
  truth_eta.clear() ;
  truth_phi.clear() ;
  truth_pt.clear() ;
  truth_pid.clear() ;
  truth_mid.clear() ;
  truth_bare_e.clear() ;
  truth_bare_eta.clear() ;
  truth_bare_phi.clear() ;
  truth_bare_pt.clear() ;
  truth_bare_pid.clear() ;
  truth_dressed_e.clear() ;
  truth_dressed_eta.clear() ;
  truth_dressed_phi.clear() ;
  truth_dressed_pt.clear() ;
  truth_dressed_pid.clear() ;
  truth_photon_e.clear() ;
  truth_photon_eta.clear() ;
  truth_photon_phi.clear() ;
  truth_photon_pt.clear() ;
  truth_photon_mid.clear() ;

  full_truth_e.clear() ;
  full_truth_eta.clear() ;
  full_truth_phi.clear() ;
  full_truth_pt.clear() ;
  full_truth_pid.clear() ;
  full_truth_mid.clear() ;

  truthPropagator_px = 0;
  truthPropagator_py = 0;
  truthPropagator_pz = 0;
  truthPropagator_e = 0;

  MCEventWeights.clear();
}

void SkimToNtupleTriLep::Record_Object(const xAOD::IParticle* par, std::string flavor)
{
  if(flavor == "fwdel"){
    xAOD::Electron* fwdel = (xAOD::Electron *)par;

  }

  if(flavor == "elec"){
    xAOD::Electron* el = (xAOD::Electron*)par;
    el_e.push_back( (el)->e() );
    el_eta.push_back( (el)->eta() );
    el_cl_eta.push_back( (el)->eta() );
    el_phi.push_back( (el)->phi() );
    el_pt.push_back( (el)->pt() );
    el_charge.push_back( (el)->charge() );
    el_truthMatched.push_back( (el)->auxdata<char>("truthMatched") );
    el_d0Sig.push_back( (el)->auxdata<float>("d0Sig") );
    el_mediumID.push_back( (el)->auxdata<char>("mediumID") );
    el_tightID.push_back( (el)->auxdata<char>("tightID") );
    el_FCLooseIso.push_back( (el)->auxdata<char>("FCLooseIso") );
    el_FCTightIso.push_back( (el)->auxdata<char>("FCTightIso") );
    el_HighPtCaloOnlyIso.push_back( (el)->auxdata<char>("HighPtCaloOnlyIso") );
    el_Tight_VarRadIso.push_back( (el)->auxdata<char>("Tight_VarRadIso") );
    el_Loose_VarRadIso.push_back( (el)->auxdata<char>("Loose_VarRadIso") );
    el_triggerMatched.push_back( (el)->auxdata<char>("triggerMatched") );
    el_isbaseline.push_back( (el)->auxdata<char>("baseline") );
    el_isAmbiguity.push_back( (el)->auxdata<int>("isAmbiguity") );
    if(isMC){
      el_mediumIDWeight.push_back( (el)->auxdata<double>("weightMediumID") );
      el_tightIDWeight.push_back( (el)->auxdata<double>("weightTightID") );
      el_FCLooseIsoWeight.push_back( (el)->auxdata<double>("weightFCLooseIso") );
      el_FCTightIsoWeight.push_back( (el)->auxdata<double>("weightFCTightIso") );
      el_HighPtCaloOnly_MediumID_IsoWeight.push_back( (el)->auxdata<double>("weightHighPtCaloOnlyIso_MediumID") );
      el_HighPtCaloOnly_TightID_IsoWeight.push_back( (el)->auxdata<double>("weightHighPtCaloOnlyIso_TightID") );
      el_Tight_VarRad_MediumID_IsoWeight.push_back( (el)->auxdata<double>("weightTight_VarRadIso_MediumID") );
      el_Tight_VarRad_TightID_IsoWeight.push_back( (el)->auxdata<double>("weightTight_VarRadIso_TightID") );
      el_Loose_VarRad_MediumID_IsoWeight.push_back( (el)->auxdata<double>("weightLoose_VarRadIso_MediumID") );
      el_Loose_VarRad_TightID_IsoWeight.push_back( (el)->auxdata<double>("weightLoose_VarRadIso_TightID") );
      el_recoWeight.push_back( (el)->auxdata<double>("weightRECO") );
    }

  }

  if(flavor == "muon"){
    xAOD::Muon* mu = (xAOD::Muon*)par;
    mu_e.push_back( (mu)->e() );
    mu_eta.push_back( (mu)->eta() );
    mu_phi.push_back( (mu)->phi() );
    mu_pt.push_back( (mu)->pt() );
    mu_charge.push_back( (mu)->charge() );
    mu_truthMatched.push_back( (mu)->auxdata<char>("truthMatched") );
    mu_d0Sig.push_back( (mu)->auxdata<float>("d0Sig") );
    mu_mediumID.push_back( (mu)->auxdata<char>("mediumID") );
    mu_tightID.push_back( (mu)->auxdata<char>("tightID") );
    mu_FCLooseIso.push_back( (mu)->auxdata<char>("FCLooseIso") );
//    mu_FCTightIso.push_back( (mu)->auxdata<char>("FCTightIso") );
    mu_PflowLooseIso.push_back( (mu)->auxdata<char>("PflowLooseIso") );
    mu_PflowTightIso.push_back( (mu)->auxdata<char>("PflowTightIso") );
    mu_triggerMatched.push_back( (mu)->auxdata<char>("triggerMatched") );
    mu_isbaseline.push_back( (mu)->auxdata<char>("baseline") );
    if(isMC){
      mu_mediumIDWeight.push_back( (mu)->auxdata<double>("weightMediumID") );
      mu_tightIDWeight.push_back( (mu)->auxdata<double>("weightTightID") );
      mu_FCLooseIsoWeight.push_back( (mu)->auxdata<double>("weightFCLooseIso") );
//      mu_FCTightIsoWeight.push_back( (mu)->auxdata<double>("weightFCTightIso") );
      mu_PflowLooseIsoWeight.push_back( (mu)->auxdata<double>("weightPflowLooseIso") );
      mu_PflowTightIsoWeight.push_back( (mu)->auxdata<double>("weightPflowTightIso") );
      mu_IPWeight.push_back( (mu)->auxdata<double>("weightIP") );
    }


  }

  if(flavor == "truth"){
    xAOD::TruthParticle* tPar = (xAOD::TruthParticle *)par;

    if(((tPar)->auxdecor<char>("isWZLepton")) || ((tPar)->auxdecor<char>("isHardElectron")) || ((tPar)->auxdecor<char>("isHardMuon"))){
      truth_e.push_back( (tPar)->e() );
      truth_eta.push_back( (tPar)->eta() );
      truth_phi.push_back( (tPar)->phi() );
      truth_pt.push_back( (tPar)->pt() );
      truth_pid.push_back( (tPar)->pdgId() );
      truth_mid.push_back( (tPar)->parent(0)->pdgId() );
    }
    if( (tPar)->auxdecor<char>("isBareLepton") ){
      truth_bare_e.push_back( (tPar)->e() );
      truth_bare_eta.push_back( (tPar)->eta() );
      truth_bare_phi.push_back( (tPar)->phi() );
      truth_bare_pt.push_back( (tPar)->pt() );
      truth_bare_pid.push_back( (tPar)->pdgId() );
    }
    if( (tPar)->auxdecor<char>("isPhoton") ){
      truth_photon_e.push_back( (tPar)->e() );
      truth_photon_eta.push_back( (tPar)->eta() );
      truth_photon_phi.push_back( (tPar)->phi() );
      truth_photon_pt.push_back( (tPar)->pt() );
      truth_photon_mid.push_back( (tPar)->parent(0)->pdgId() );
    }

//    if( abs((tPar)->pdgId()) >= 11 && abs((tPar)->pdgId()) <= 14){
    if( (tPar)->auxdecor<char>("isBareLepton") ){
      const float e = (tPar)->auxdecor<float>("dressed_e");
      const float eta = (tPar)->auxdecor<float>("dressed_eta");
      const float phi = (tPar)->auxdecor<float>("dressed_phi");
      const float pt = (tPar)->auxdecor<float>("dressed_pt");
      truth_dressed_e.push_back( e );
      truth_dressed_eta.push_back( eta );
      truth_dressed_phi.push_back( phi );
      truth_dressed_pt.push_back( pt );
      truth_dressed_pid.push_back( (tPar)->pdgId() );
    }
  }

  if(flavor == "full_truth"){
    xAOD::TruthParticle* tPar = (xAOD::TruthParticle *)par;

    full_truth_e.push_back( (tPar)->e() );
    full_truth_eta.push_back( (tPar)->eta() );
    full_truth_phi.push_back( (tPar)->phi() );
    full_truth_pt.push_back( (tPar)->pt() );
    full_truth_pid.push_back( (tPar)->pdgId() );
    full_truth_mid.push_back( (tPar)->parent(0)->pdgId() );

  }

  if(flavor == "jet"){
    xAOD::Jet* jt = (xAOD::Jet*)par;
    jt_e.push_back( (jt)->e() );
    jt_eta.push_back( (jt)->eta() );
    jt_phi.push_back( (jt)->phi() );
    jt_pt.push_back( (jt)->pt() );
    jt_passJVT.push_back( (jt)->auxdata<char>("passJVT") );
    jt_passBtag.push_back( (jt)->auxdata<char>("bTagged") );


  }

}

bool SkimToNtupleTriLep::SkipSystematic(void)
{
  if(sysname=="EL_EFF_FwdID_TOTAL_1NPCOR_PLUS_UNCOR__1down") return true;
  if(sysname=="EL_EFF_FwdID_TOTAL_1NPCOR_PLUS_UNCOR__1up") return true;
  if(sysname=="EL_EFF_TriggerEff_TOTAL_1NPCOR_PLUS_UNCOR__1down") return true;
  if(sysname=="EL_EFF_TriggerEff_TOTAL_1NPCOR_PLUS_UNCOR__1up") return true;
  if(sysname=="EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1down") return true;
  if(sysname=="EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1up") return true;
  if(sysname=="MUON_EFF_TrigStatUncertainty__1down") return true;
  if(sysname=="MUON_EFF_TrigStatUncertainty__1up") return true;
  if(sysname=="MUON_EFF_TrigSystUncertainty__1down") return true;
  if(sysname=="MUON_EFF_TrigSystUncertainty__1up") return true;
  return false;
}

