#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <xAODJet/JetContainer.h>
#include <xAODTruth/TruthEventContainer.h>
#include <xAODTracking/VertexContainer.h>
#include <xAODEventInfo/EventInfo.h>
#include "AthContainers/ConstDataVector.h"
#include "AthContainers/DataVector.h"
#include <xAODEgamma/PhotonContainer.h>
#include <xAODCaloEvent/CaloClusterContainer.h>
#include "xAODCutFlow/CutBookkeeperContainer.h"

#include <LJAlgo/LJAlgo.h>
#include <LJAlgo/ConstAccessors.h>

#include <xAODAnaHelpers/HelperFunctions.h>
#include <xAODAnaHelpers/HelperClasses.h>

// c++ includes(s):
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>

// this is needed to distribute the algorithm to the workers
ClassImp(LJAlgo)






// ---------------------------------------------------------------------------//
LJAlgo :: LJAlgo () :
    Algorithm("LJAlgo")
{
}





// ---------------------------------------------------------------------------//
LJAlgo :: ~LJAlgo()
{
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo :: setupJob (EL::Job& job)
{
    job.useXAOD();
    xAOD::Init("LJAlgo").ignore();

    EL::OutputStream outForTree("tree");
    job.outputAdd (outForTree);

    return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo :: histInitialize ()
{
    ANA_MSG_INFO( m_name );
    ANA_CHECK( xAH::Algorithm::algInitialize());

    // extra cutflow histograms to track preselections
    m_AlgoCutflow_LJ = new TH1F(TString("LJAlgo_LJcutflow"),"LJAlgo LJ preselections cutflow", 1, 1., 2.);
    m_AlgoCutflow_LJ->SetCanExtend(TH1::kAllAxes);
    m_AlgoCutflow_LJ_weighted = new TH1F(TString("LJAlgo_LJcutflow_weighted"),"LJAlgo LJ preselections cutflow", 1, 1., 2.);
    m_AlgoCutflow_LJ_weighted->SetCanExtend(TH1::kAllAxes);

    m_AlgoCutflow_LL = new TH1F(TString("LJAlgo_LLcutflow"),"LJAlgo LL preselections cutflow", 1, 1., 2.);
    m_AlgoCutflow_LL->SetCanExtend(TH1::kAllAxes);
    m_AlgoCutflow_LL_weighted = new TH1F(TString("LJAlgo_LLcutflow_weighted"),"LJAlgo LL preselections cutflow", 1, 1., 2.);
    m_AlgoCutflow_LL_weighted->SetCanExtend(TH1::kAllAxes);

    m_AlgoCutflow_EL = new TH1F(TString("LJAlgo_ELcutflow"),"LJAlgo EL preselections cutflow", 1, 1., 2.);
    m_AlgoCutflow_EL->SetCanExtend(TH1::kAllAxes);
    m_AlgoCutflow_EL_weighted = new TH1F(TString("LJAlgo_ELcutflow_weighted"),"LJAlgo EL preselections cutflow", 1, 1., 2.);
    m_AlgoCutflow_EL_weighted->SetCanExtend(TH1::kAllAxes);

    m_histVariationsSumW = new TH1D("MetaData_VariationsSumW", "MetaData_VariationsSumW", 1, 0, 1);

    // wk()->addOutput(m_AlgoCutflow);
    // wk()->addOutput(m_AlgoCutflow_weighted);

    ANA_MSG_INFO("Finished initialising LJAlgo histograms");

    return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo :: initialize ()
{

    ANA_MSG_INFO( m_name );
    m_event = wk()->xaodEvent();
    m_store = wk()->xaodStore();

    // get the file we created already
    TFile* treeFile = wk()->getOutputFile ("tree");
    // TODO: this creates a new TDirectory; do we want/need that?
    treeFile->mkdir(m_name.c_str());
    treeFile->cd(m_name.c_str());

    // set up TriggerDecisionTool
    ANA_CHECK( m_trigConfTool_handle.setProperty("OutputLevel", msg().level()));
    ANA_CHECK( m_trigConfTool_handle.retrieve());
    ANA_MSG_DEBUG("Retrieved tool: " << m_trigConfTool_handle);

    ANA_CHECK( m_trigDecTool_handle.setProperty( "ConfigTool", m_trigConfTool_handle ));
    ANA_CHECK( m_trigDecTool_handle.setProperty( "TrigDecisionKey", "xTrigDecision" ));
    ANA_CHECK( m_trigDecTool_handle.setProperty( "OutputLevel", msg().level() ));
    ANA_CHECK( m_trigDecTool_handle.retrieve());
    ANA_MSG_DEBUG("Retrieved tool: " << m_trigDecTool_handle);

    // set up PMGCrossSectionTool when running on MC
    if (isMC()) {
      ANA_MSG_INFO("Initializing PMGCrossSectionTool");
      // check if we have set a cross section file
      if (m_crossSectionFile.empty()){
        ANA_MSG_ERROR("Please specify a valid cross section file!");
        return EL::StatusCode::FAILURE;
      }
      ASG_SET_ANA_TOOL_TYPE( m_PMGCrossSectionTool, PMGTools::PMGCrossSectionTool);
      m_PMGCrossSectionTool.setName("CrossSectionTool");
      ANA_CHECK(m_PMGCrossSectionTool.retrieve());
      ANA_MSG_DEBUG("Retrieved tool: " << m_PMGCrossSectionTool);
      m_PMGCrossSectionTool->readInfosFromFiles({PathResolverFindCalibFile(m_crossSectionFile)});
    

      // initialize PMG tool for reading syst-names when running on MC. Must be done here (before) initialize()
      ANA_MSG_INFO("Initializing PMGTruthWeightTool");
      ASG_SET_ANA_TOOL_TYPE( m_PMGTruthWeightTool, PMGTools::PMGTruthWeightTool);
      m_PMGTruthWeightTool.setName("TruthWeightTool");
      ANA_CHECK(m_PMGTruthWeightTool.retrieve());
      ANA_MSG_DEBUG("Retrieved tool: " << m_PMGTruthWeightTool);
    }

    // set up TruthClassificationTool when running on MC
    if (isMC()) {
      ASG_SET_ANA_TOOL_TYPE( m_truthClassificationTool, TruthClassificationTool);
      m_truthClassificationTool.setName("TruthClassificationTool");
      ANA_CHECK(m_truthClassificationTool.setProperty("separateChargeFlipElectrons", true));
      ANA_CHECK(m_truthClassificationTool.setProperty("separateChargeFlipMuons", true));
      // for some of our samples like l-j scattering the classification doesn't work and throws out a lot of warnings
      ANA_CHECK( m_truthClassificationTool.setProperty("OutputLevel",  MSG::Level::ERROR ));
      ANA_CHECK(m_truthClassificationTool.retrieve());
    }
    
    // convert trigger list to std::vector
    std::string token;
    std::istringstream ss_triggers(m_triggerList);
    while ( std::getline(ss_triggers, token, ',') ){
      ANA_MSG_INFO("Adding trigger " << token);
      m_triggerListVec.push_back(token);
    }

    // notify about event skimming applied
    if (m_leadJetPtSkim > 0.0){
      ANA_MSG_INFO("Applying event skimming for LJ analysis: at least one jet with pT > " << m_leadJetPtSkim << " GeV" );
    }
    
    // notify about event skimming applied
    if (m_leadLepPtSkim > 0.0){
      ANA_MSG_INFO("Applying event skimming for both analysis: at least one lepton with pT > " << m_leadLepPtSkim << " GeV" );
    }

    // notify about event skimming applied
    if (m_mLepJetSkim > 0.0){
      ANA_MSG_INFO("Applying event skimming for LJ analysis: invariant mass of lepton+jet of m_lj > " << m_mLepJetSkim << " GeV" );
    }

    // notify about event skimming applied
    if (m_mLepLepSkim > 0.0){
      ANA_MSG_INFO("Applying event skimming for LL analysis: invariant mass of dilepton of m_ll > " << m_mLepLepSkim << " GeV" );
    }



    // yfu add individual scale factors
    /*
    std::string m_overrideMapFilePath = "";


    m_asgElEffCorrTool_elSF_Reco = new AsgElectronEfficiencyCorrectionTool(m_pidEffSF_tool_name);
    m_asgElEffCorrTool_elSF_Reco->msg().setLevel( MSG::ERROR ); // DEBUG, VERBOSE, INFO
    if ( !m_overrideMapFilePath.empty() ) {
      ANA_MSG_WARNING( "Overriding MapFilePath to " << m_overrideMapFilePath );
      ANA_CHECK( m_asgElEffCorrTool_elSF_Reco->setProperty("MapFilePath", m_overrideMapFilePath));
    }
    ANA_CHECK( m_asgElEffCorrTool_elSF_Reco->setProperty("ForceDataType", 1));
    ANA_CHECK( m_asgElEffCorrTool_elSF_Reco->setProperty("IdKey", "Reconstruction"));
    ANA_CHECK( m_asgElEffCorrTool_elSF_Reco->setProperty("CorrelationModel","TOTAL"));
    ANA_CHECK( m_asgElEffCorrTool_elSF_Reco->initialize());
    */


    return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo :: fileExecute ()
{
    ANA_MSG_INFO( "Calling fileExecute");

    // format and fill the SoW hist for MC
    if (isMC()) {
      // get TEvent and TStore which are needed to retrieve CutBookkeepers
      m_event = wk()->xaodEvent();
      m_store = wk()->xaodStore();



      // get weight names with PMGTruthWeightTool and confirm that the first one is 'Default'
      m_weightNames = m_PMGTruthWeightTool->getWeightNames();

      // set binning for the meta-data histogram storing theory variation sum of weights
      m_histVariationsSumW->SetBins(m_weightNames.size(), 0.5, m_weightNames.size() + 0.5);

      // get the MetaData tree to retrieve CutBookkeepers
      TTree* MetaData = dynamic_cast<TTree*>( wk()->inputFile()->Get("MetaData") );
      if ( !MetaData ) {
        ANA_MSG_ERROR( "MetaData tree not found! Exiting.");
        return EL::StatusCode::FAILURE;
      }
      MetaData->LoadTree(0);

      // TODO: add a few checks to mirror BasicEventSelection.cxx from AnaHelpers?
      // TODO: implement a check that confirms m_weightNames() - 1 == number of CBCs?

      // Loop over CutBookkeeper containers for different SoW variations
      for (unsigned int i = 0; i < m_weightNames.size(); i++) {

        // match the CBC naming syntax: 'Default' - CutBookkeeper, i-th - CutBookkeeper_weight_i 
        std::string cbcName = "CutBookkeepers";
        if (i != 0) {
          cbcName += "_weight_" + std::to_string(i);
        }

        // retrieve the CBC
        const xAOD::CutBookkeeperContainer* cbc;
        if (!m_event->retrieveMetaInput(cbc, cbcName.c_str()).isSuccess() ) {
          ANA_MSG_ERROR("Failed to retrieve an alternate-weight CutBookepersContainer from MetaData! Exiting.");
          return EL::StatusCode::FAILURE;
        }

        // TODO: add a few more checks to mirror BasicEventSelection.cxx from AnaHelpers? specifically on the "cycle"/size of container
        
        // retrieve the correct CutBookkeeper from the container and fill m_histVariationsSumW
        bool foundWeight = false;
        for( const xAOD::CutBookkeeper* cbk: *cbc){
          if (cbk->name() != "AllExecutedEvents") {continue;}
          else {
            m_histVariationsSumW->GetXaxis()->SetBinLabel(i + 1, m_weightNames.at(i).c_str());
            m_histVariationsSumW->Fill(i + 1, cbk->sumOfEventWeights());
            foundWeight = true;
          }
        }
        if (!foundWeight) {
          ANA_MSG_ERROR( "'AllExecutedEvents' CutBookkeeper not found! Exiting.");
          return EL::StatusCode::FAILURE;
        }
      }
    
    }
    ANA_MSG_INFO( "Finished fileExecute");

    return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo :: changeInput (bool /*firstFile*/){ return EL::StatusCode::SUCCESS; }





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo :: execute ()
{

  // what systematics do we need to process for this event?
  // handle the nominal case (merge all) on every event, always
  std::vector<std::string> event_systNames({""});
  std::vector<std::string> muSystNames;
  std::vector<std::string> elSystNames;
  std::vector<std::string> tauSystNames;
  std::vector<std::string> jetSystNames;
  std::vector<std::string> btagSystNames;
  std::vector<std::string> metSystNames;

  // this is a temporary pointer that gets switched around to check each of the systematics
  std::vector<std::string>* systNames(nullptr);

  // note that the way we set this up, none of the below ##SystNames vectors contain the nominal case
  if(!m_muSystsName.empty()){
    ANA_MSG_DEBUG( "Muon systematic tree names: " );
    ANA_CHECK( HelperFunctions::retrieve(systNames, m_muSystsName, 0, m_store, msg()) );
    for(const auto& systName: *systNames){
      muSystNames.push_back(systName);
      ANA_MSG_DEBUG( systName.c_str() );
      if (std::find(event_systNames.begin(), event_systNames.end(), systName) != event_systNames.end())
        continue;
      event_systNames.push_back(systName);
    }
  }

  if(!m_elSystsName.empty()){
    ANA_MSG_DEBUG( "Electron systematic tree names: " );
    ANA_CHECK( HelperFunctions::retrieve(systNames, m_elSystsName, 0, m_store, msg()) );
    for(const auto& systName: *systNames){
      elSystNames.push_back(systName);
      ANA_MSG_DEBUG( systName.c_str() );
      if (std::find(event_systNames.begin(), event_systNames.end(), systName) != event_systNames.end())
        continue;
      event_systNames.push_back(systName);
    }
  }

  if(!m_tauSystsName.empty()){
    ANA_MSG_DEBUG( "Tau systematic tree names: " );
    ANA_CHECK( HelperFunctions::retrieve(systNames, m_tauSystsName, 0, m_store, msg()) );
    for(const auto& systName: *systNames){
      tauSystNames.push_back(systName);
      ANA_MSG_DEBUG( systName.c_str() );
      if (std::find(event_systNames.begin(), event_systNames.end(), systName) != event_systNames.end())
        continue;
      event_systNames.push_back(systName);
    }
  }

  if(!m_jetSystsName.empty()){
    ANA_MSG_DEBUG( "Jet systematic tree names: " );
    ANA_CHECK( HelperFunctions::retrieve(systNames, m_jetSystsName, 0, m_store, msg()) );
    for(const auto& systName: *systNames){
      jetSystNames.push_back(systName);
      ANA_MSG_DEBUG( systName.c_str() );
      if (std::find(event_systNames.begin(), event_systNames.end(), systName) != event_systNames.end())
        continue;
      event_systNames.push_back(systName);
    }
  }
  if(!m_btagSystsName.empty()){
    ANA_MSG_DEBUG( "B-tag systematic tree names: " );
    ANA_CHECK( HelperFunctions::retrieve(systNames, m_btagSystsName, 0, m_store, msg()) );
    for(const auto& systName: *systNames){
      btagSystNames.push_back(systName);
      if (std::find(event_systNames.begin(), event_systNames.end(), systName) != event_systNames.end())
        continue;
      event_systNames.push_back(systName);
    }
  }
  if(!m_metSystsName.empty()){
    ANA_MSG_DEBUG( "MET systematic tree names: " );
    ANA_CHECK( HelperFunctions::retrieve(systNames, m_metSystsName, 0, m_store, msg()) );
    for(const auto& systName: *systNames){
      metSystNames.push_back(systName);
      ANA_MSG_DEBUG( systName.c_str() );
      if (std::find(event_systNames.begin(), event_systNames.end(), systName) != event_systNames.end())
        continue;
      event_systNames.push_back(systName);
    }
  }

  if (m_firstEvent) {
    ANA_MSG_INFO( "Full list of systematics to consider: " );
    for (const std::string & systName: event_systNames) {
      ANA_MSG_INFO( "  " << systName);
    }
  }



  // store the names of the systematic in internal member
  // TODO: can this be done more elegant?
  m_allSystVec = event_systNames;
  
  

  TFile* treeFile = wk()->getOutputFile ("tree");





  // let's make the TDirectory and TTrees
  // TODO: Why isn't this done in initialize()?
  for(const auto& systName: event_systNames){
    
    // check if we have already created the tree
    if(m_trees.find(systName) != m_trees.end()) {
      continue;
    }
    
    std::string treeName = systName;
    
    if(systName.empty()) {
      treeName = "nominal";
    }

    
    ANA_MSG_INFO( "Making tree " << m_name << "/" << treeName );
    
    
    TTree * outTree = new TTree(treeName.c_str(),treeName.c_str());
    if ( !outTree ) {
      ANA_MSG_ERROR("Failed to instantiate output tree!");
      return EL::StatusCode::FAILURE;
    }

    m_trees[systName] = createTree( m_event, outTree, treeFile, m_units, msgLvl(MSG::DEBUG), m_store );
    const auto& helpTree = m_trees[systName];

    // tell the tree to go into the file
    outTree->SetDirectory( treeFile->GetDirectory(m_name.c_str()) );
    
    if(m_autoFlush != 0) {
      outTree->SetAutoFlush(m_autoFlush);
    }
    
    // choose if want to add tree to same directory as ouput histograms
    if ( m_outHistDir ) {
      if(m_trees.size() > 1)
        ANA_MSG_WARNING( "You're running systematics! You may find issues in writing all of the output TTrees to the output histogram file... Set `m_outHistDir = false` if you run into issues!");
      wk()->addOutput( outTree );
    }

    
    
    
    
    // initialize all branch addresses since we just added this tree
    // write the theory systematic weights only in the nominal tree
    // TODO: also skim away truth particle vector branches in syst trees?
    if (systName.empty()) {
      helpTree->AddEvent( m_evtDetailStr );
    } else {
      helpTree->AddEvent( m_evtDetailStrSyst );
    }

    if (!m_trigDetailStr.empty() ){
      helpTree->AddTrigger(m_trigDetailStr);
    }
    
    if (m_writeTruthLeptonBranches) {
      if (!m_truthmuContainerName.empty() ) {
        helpTree->AddTruthParts(m_truthParticlesDetailStr, "truth_muon");
      };
      if (!m_truthelContainerName.empty() ) {
        helpTree->AddTruthParts(m_truthParticlesDetailStr, "truth_el");
      };
    }
    
    if (m_writeTruthJetBranches) {
      if (!m_truthjetContainerName.empty() ) {
        helpTree->AddJets(m_truthJetDetailStr, "truth_jet");
      };
    }
    
    if (m_writeLeptonVectorBranches) {
      if (!m_muContainerName.empty() ) {
        helpTree->AddMuons(m_muDetailStr);
      };
      if (!m_elContainerName.empty() ) {
        helpTree->AddElectrons(m_elDetailStr);
      };
    }
    
    if (m_useTaus) {
      if (!m_tauContainerName.empty() )     {
        helpTree->AddTaus(m_tauDetailStr);
      };
      if (!m_truthtauContainerName.empty() ){
        helpTree->AddTruthParts(m_truthParticlesDetailStr, "truth_tau");
      };
    }
    
    if (!m_jetContainerName.empty()){
      helpTree->AddJets(m_jetDetailStr);
    }
    
    if (!m_METContainerName.empty()){
      helpTree->AddMET(m_METDetailStr);
    }
  }

  // add branches only when at first event
  // not possible to have this in initialize --> systematic trees are not available at that stage!
  if (m_firstEvent){
    // add decisions of requested triggers
    for (std::string trig : m_triggerListVec){
        addBoolVariable(trig, false);
        if(m_writeSingleElectron) addFloatVariable("prescale_" + trig, -999);//yfu combine jetfake
    }
    addBoolVariable("HLT_singleLep", false);
    addBoolVariable("HLT_singleJet", false);

    // note: this is already written out in some way by AddEvent(), but defining
    // them in the following way is helpful to easily split between periods after merging
    // randomRunNumber - MC: the RRN assigned by the PRW tool; Data: the real Run number
    // datasetNumber   - MC: the dataset ID; Data: a dummy value like -999
    addIntVariable("randomRunNumber", -999);
    addIntVariable("datasetNumber", -999);
    addIntVariable("year", -999);

    // xAH doesn't write out an MC event branch for data which can be a bit inconvenient
    // during plotting, so we add it for data ourselves here
    if (!isMC()) {
      addFloatVariable("mcEventWeight", 1.0);
    }

    // event metadata
    addFloatVariable("sample_xSec", -999);
    addFloatVariable("sample_xSec_up_rel", -999);
    addFloatVariable("sample_xSec_down_rel", -999);
    addFloatVariable("sample_kFactor", -999);
    addFloatVariable("sample_filterEff", -999);

    // global weights containing e.g. total xsec, lepton, JVT & b-tagging SFs ..
    addFloatVariable("weight_gen", 1);
    addFloatVariable("weight_lepton", 1);
    addFloatVariable("weight_jvt", 1);
    addFloatVariable("weight_btag", 1);
    addFloatVariable("weight_singleleptonTrigSF", 1);
    addFloatVariable("weight_dileptonTrigSF", 1);

    // add branch to carry weight of fake-lepton estimate
    // will be filled in a post-processing step
    addFloatVariable("fakeweight", 1);

    // scalar leading lepton branches
    addIntVariable("n_truth_el", -999);
    addIntVariable("n_truth_mu", -999);
    addIntVariable("n_truth_lep", -999);
    addIntVariable("n_el", -999);
    addIntVariable("n_mu", -999);
    addIntVariable("n_lep", -999);
    addIntVariable("n_signal_el", -999);
    addIntVariable("n_signal_mu", -999);
    addIntVariable("n_signal_lep", -999);
    
    if ((m_BtaggerWP == "Continuous") && m_writeAllBTagWPs) {
      addIntVariable("n_bjets_65", -999);
      addIntVariable("n_bjets_70", -999);
      addIntVariable("n_bjets_77", -999);
      addIntVariable("n_bjets_85", -999);
      addIntVariable("n_bjets_90", -999);
    }
    addIntVariable("n_bjets", -999);
    
    addLeptonVariables("lepton1");
    addLeptonVariables("lepton2");
    
    addBoolVariable("lepton_singleleptrigMatched", 0);
    addBoolVariable("lepton_dileptrigMatched", 0);

    // scalar leading jet branches
    addFloatVariable("jet1_pt", -999);
    addFloatVariable("jet1_phi", -999);
    addFloatVariable("jet1_eta", -999);
    addFloatVariable("jet1_E", -999);
    addIntVariable("jet1_PartonTruthLabelID", -999);
    addIntVariable("jet1_ConeTruthLabelID", -999);
    addFloatVariable("jet1_Jvt", -999);
    
    if ((m_BtaggerWP == "Continuous") && m_writeAllBTagWPs) {
      addBoolVariable("jet1_btag_65", false);
      addBoolVariable("jet1_btag_70", false);
      addBoolVariable("jet1_btag_77", false);
      addBoolVariable("jet1_btag_85", false);
      addBoolVariable("jet1_btag_90", false);
    }
    addBoolVariable("jet1_btag", false);

    // additional per-jet variables
    addVecCharVariable("jet_isJvtHS", std::vector<char>(), true);

    // Variables concerning the Lepton+Jet System
    if (m_writeLeptonJet) {
      addFloatVariable("mLepJet", -999);
      addFloatVariable("dRLepJet", -999);
      addFloatVariable("detaLepJet", -999);
      addFloatVariable("dphiLepJet", -999);
      addFloatVariable("LepOvermLepJet", -999);
      addFloatVariable("matched_mLepJet", -999);
      addFloatVariable("truth_mLepJet", -999);
      addFloatVariable("truth_dRLepJet", -999);
      addFloatVariable("mindphiJetMet", -999);
      addFloatVariable("dphiLepMet", -999);
    }

    if (m_writeDiLepton || m_writeSingleElectron) {
      // Variables concerning the Born lepton Dilepton System
      addFloatVariable("born_lepton1_E", -999);
      addFloatVariable("born_lepton1_pt", -999);
      addFloatVariable("born_lepton1_eta", -999);
      addFloatVariable("born_lepton1_phi", -999);
      addFloatVariable("born_lepton2_E", -999);
      addFloatVariable("born_lepton2_pt", -999);
      addFloatVariable("born_lepton2_eta", -999);
      addFloatVariable("born_lepton2_phi", -999);
      addFloatVariable("born_dilepton_m", -999);
      
      addIntVariable("n_born_lepton", -999);
      addIntVariable("n_truth_boson", -999);
      addFloatVariable("truth_boson_m", -999);
      
  
      addFloatVariable("hardscatter_W_m", -999);
      addFloatVariable("dilepton_m", -999);
      addFloatVariable("dilepton_pt", -999);
      addFloatVariable("dilepton_phi", -999);
      addFloatVariable("dilepton_eta", -999);
      addFloatVariable("dilepton_DeltaR", -999);
      addFloatVariable("dilepton_DeltaEta", -999);
      addFloatVariable("dilepton_DeltaPhi", -999);
      addFloatVariable("dilepton_CosThetaStar", -999);
    }



    // further analysis variables
    addFloatVariable("mt_lep1", -999);
    addFloatVariable("mt_lep2", -999);
    addFloatVariable("jets_HT", -999);
    addFloatVariable("meff", -999);

    // manually set basket sizes
    if (m_treeBasketSize > 0) {
      for(auto& item: m_trees){
          ANA_MSG_DEBUG("Setting basket size of " << item.first << " tree to " << m_treeBasketSize);
          item.second->GetTree()->SetBasketSize("*", m_treeBasketSize);
      }
    }
  }




  /* THIS IS WHERE WE START PROCESSING THE EVENT */
  const xAOD::EventInfo* eventInfo(nullptr);
  ANA_CHECK( HelperFunctions::retrieve(eventInfo, m_eventInfoContainerName, m_event, m_store, msg()) );

  const xAOD::VertexContainer* vertices(nullptr);
  if (m_retrievePV) {
    ANA_CHECK( HelperFunctions::retrieve(vertices, "PrimaryVertices", m_event, m_store, msg()) );
  }


  // determine if input is MC
  m_isMC = ( eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) ) ? true : false;


  const xAOD::Vertex* primaryVertex(nullptr);
  if (m_writeLeptonVectorBranches) {
    primaryVertex = m_retrievePV ? HelperFunctions::getPrimaryVertex( vertices , msg() ) : nullptr;
  }




  // retrieve metadata variables such as cross section before the systematics loop
  // TODO: should we cache this?
  uint32_t dsid = -1;
  double   xSec = -1.0, xSecUnc = -1.0, kFactor = -1.0, filterEff = -1.0;
  if (m_isMC){
    dsid = eventInfo->mcChannelNumber();
    xSec = m_PMGCrossSectionTool->getAMIXsection(dsid);
    xSecUnc = m_PMGCrossSectionTool->getXsectionUncertainty(dsid);
    kFactor = m_PMGCrossSectionTool->getKfactor(dsid);
    filterEff = m_PMGCrossSectionTool->getFilterEff(dsid);
  }


  //Get Event Weight
  float eventWeight   = 1.0;
  float weight_pileup = 1.0;

  if( eventInfo->isAvailable< float >( "mcEventWeight" ) ) {
    eventWeight = eventInfo->auxdecor< float >( "mcEventWeight" );
  }


  if ( weight_pileup_Acc.isAvailable( *eventInfo ) ){
    weight_pileup = weight_pileup_Acc( *eventInfo );
  } else {
    weight_pileup = 1.0;
  }

  std::vector<float> trigger_prescales;
  std::vector<std::string>   passed_triggers;
  if(m_writeSingleElectron){//yfu combine jetfake
    if( eventInfo->isAvailable< std::vector<float> >( "triggerPrescales" ) ) {
      trigger_prescales = eventInfo->auxdecor< std::vector<float> >( "triggerPrescales" );
    }
    if( eventInfo->isAvailable< std::vector<std::string> >( "passedTriggers" ) ) {
      passed_triggers = eventInfo->auxdecor< std::vector<std::string> >( "passedTriggers" );
    }
  }

  // start filling algo-internal cutflow
  double scalingFactor = 1.; // change back to -1 to enable error checking
  if (m_isMC){
    scalingFactor = eventWeight*weight_pileup;
  }


  // weighted cutflow histo includes event weight and pileup weight
  m_AlgoCutflow_LJ->Fill("Initial", 1.);
  m_AlgoCutflow_LJ_weighted->Fill("Initial", scalingFactor);
  m_AlgoCutflow_LL->Fill("Initial", 1.);
  m_AlgoCutflow_LL_weighted->Fill("Initial", scalingFactor);
  m_AlgoCutflow_EL->Fill("Initial", 1.);//yfu combine jetfake
  m_AlgoCutflow_EL_weighted->Fill("Initial", scalingFactor);






  for(const auto& systName: event_systNames){
    ANA_MSG_DEBUG( "Processing systematic:  " << systName );
    
    
    // don't want to process weight systematics when already in a systematics tree or when doSystematics flag wasn't used
    bool doSys = ((systName == "") && (m_doWeightSystematics));
    // flag used to not fill cutflow histos during systematics trees
    bool isNominal = (systName == "");
    
    // define runnumber here already to add the right trigger syst branches
    unsigned int randomRunNumber = m_isMC ? randomRunNumberAcc(*eventInfo) : eventInfo->runNumber();

    if (m_firstEvent and doSys) {
      ANA_MSG_DEBUG( "Adding weight syst branches in systematic tree:  " << systName );
      ANA_CHECK(addLeptonSystWeights("weight_lepton"));
      if (m_doTrigMatch)                   
        ANA_CHECK(addSingleLeptonTrigSystWeights(randomRunNumber, "weight_singleleptonTrigSF"));
      if (m_doTrigMatch && m_writeDiLepton)
        ANA_CHECK(addDiElectronTrigSystWeights  (randomRunNumber, "weight_dileptonTrigSF"));
      ANA_CHECK(addJvtSystWeights("weight_jvt"));
      ANA_CHECK(addBtagSystWeights("weight_btag"));
    }
    m_currentSyst = systName;
    
    
    auto& helpTree = m_trees[systName];

    
    
    // assume the nominal container by default
    std::string muSuffix("");
    std::string elSuffix("");
    std::string tauSuffix("");
    std::string jetSuffix("");
    std::string btagSuffix("");
    std::string metSuffix("");
    /*
      if we find the systematic in the corresponding vector, we will use that container's systematic version instead of nominal version
      NB: since none of these contain the "" (nominal) case because of how I filter it, we handle the merging.. why?
      - in each loop to make the ##systNames vectors, we check to see if the systName exists in event_systNames which is initialized
      -   to {""} - the nominal case. If the systName exists, we do not add it to the corresponding ##systNames vector, otherwise, we do.
      -   This precludes the nominal case in all of the ##systNames vectors, which means the default will always be to run nominal.
    */
    // el, mu and jet systNames are only object specific calibration systematics; MET systematics include the systematics from el, mu, jet?
    if (std::find(muSystNames.begin()   , muSystNames.end()  , systName) != muSystNames.end())   muSuffix = systName;
    if (std::find(elSystNames.begin()   , elSystNames.end()  , systName) != elSystNames.end())   elSuffix = systName;
    if (std::find(tauSystNames.begin()  , tauSystNames.end() , systName) != tauSystNames.end())  tauSuffix = systName;
    if (std::find(jetSystNames.begin()  , jetSystNames.end() , systName) != jetSystNames.end())  jetSuffix = systName;
    if (std::find(btagSystNames.begin() , btagSystNames.end(), systName) != btagSystNames.end()) btagSuffix = systName;
    if (std::find(metSystNames.begin()  , metSystNames.end() , systName) != metSystNames.end())  metSuffix = systName;

    
    


    // retrieve the object containers filled be the algorithms that ran before
    // note we call the FillX() method only for some of them to have finer control of the output,
    // eventually we may drop this functionality of the HelpTree class completely ...

    const xAOD::ElectronContainer * electrons(nullptr);
    const xAOD::MuonContainer     * muons(nullptr);
    const xAOD::TauJetContainer   * taus(nullptr);
    const xAOD::JetContainer      * jets(nullptr);
    const xAOD::MissingETContainer* metCont(nullptr);
    
    
    if ( !m_elContainerName.empty() ) {
      if ( !HelperFunctions::isAvailable<xAOD::ElectronContainer>(m_elContainerName + elSuffix, m_event, m_store, msg()) ) {
        continue;
      }
      ANA_CHECK( HelperFunctions::retrieve(electrons, m_elContainerName+elSuffix, m_event, m_store, msg()) );
    }
    if (m_writeLeptonVectorBranches) {
      helpTree->FillElectrons( electrons, primaryVertex );
    }
    
    
    if ( !m_muContainerName.empty() ) {
      if ( !HelperFunctions::isAvailable<xAOD::MuonContainer>(m_muContainerName + muSuffix, m_event, m_store, msg()) ) {
        continue;
      }
      ANA_CHECK( HelperFunctions::retrieve(muons, m_muContainerName+muSuffix, m_event, m_store, msg()) );
    }
    if (m_writeLeptonVectorBranches) {
      helpTree->FillMuons( muons, primaryVertex );
    }

    
    if (m_useTaus) {
      if ( !m_tauContainerName.empty() ) {
        if ( !HelperFunctions::isAvailable<xAOD::TauJetContainer>(m_tauContainerName + tauSuffix, m_event, m_store, msg()) ){
          continue;
        }
        ANA_CHECK( HelperFunctions::retrieve(taus, m_tauContainerName+tauSuffix, m_event, m_store, msg()) );
      }
      helpTree->FillTaus( taus );
    }

    
    
    if ( !m_jetContainerName.empty() ) {
      if ( !HelperFunctions::isAvailable<xAOD::JetContainer>(m_jetContainerName + jetSuffix, m_event, m_store, msg()) ) {
        continue;
      }
      ANA_CHECK( HelperFunctions::retrieve(jets, m_jetContainerName+jetSuffix, m_event, m_store, msg()) );
    }
    helpTree->FillJets( jets, HelperFunctions::getPrimaryVertexLocation(vertices, msg()));

    
    
    if ( !m_METContainerName.empty() ) {
      if ( !HelperFunctions::isAvailable<xAOD::MissingETContainer>(m_METContainerName + metSuffix, m_event, m_store, msg()) ) {
        continue;
      }
      ANA_CHECK( HelperFunctions::retrieve(metCont, m_METContainerName+metSuffix, m_event, m_store, msg()) );
    }
    helpTree->FillMET( metCont );










    const xAOD::TruthEventContainer   * truthEvents(nullptr);
    const xAOD::TruthParticleContainer* truth_electrons_ini(nullptr);
    const xAOD::TruthParticleContainer* truth_muons_ini(nullptr);
    const xAOD::TruthParticleContainer* truth_taus_ini(nullptr);
    const xAOD::JetContainer          * truth_jets(nullptr);
    
    const xAOD::TruthParticleContainer truth_electrons;
    const xAOD::TruthParticleContainer truth_muons;
    const xAOD::TruthParticleContainer truth_taus; 
    
    
    
    if(m_isMC) {
      ANA_CHECK( HelperFunctions::retrieve(truthEvents, "TruthEvents", m_event, 0, msg()) );
    
      // truthEvent = truthEvents->at(0);
      if ( !m_truthelContainerName.empty() ) {
        if ( !HelperFunctions::isAvailable<xAOD::TruthParticleContainer>(m_truthelContainerName, m_event, m_store, msg()) ) {
          continue;
        }
        ANA_CHECK( HelperFunctions::retrieve(truth_electrons_ini, m_truthelContainerName, m_event, m_store, msg()) );
      }
    
      if ( !m_truthmuContainerName.empty() ) {
        if ( !HelperFunctions::isAvailable<xAOD::TruthParticleContainer>(m_truthmuContainerName, m_event, m_store, msg()) ){
          continue;
        }
        ANA_CHECK( HelperFunctions::retrieve(truth_muons_ini, m_truthmuContainerName, m_event, m_store, msg()) );
      }
    
      if ( !m_truthtauContainerName.empty() ) {
        if ( !HelperFunctions::isAvailable<xAOD::TruthParticleContainer>(m_truthtauContainerName, m_event, m_store, msg()) ) {
          continue;
        }
        ANA_CHECK( HelperFunctions::retrieve(truth_taus_ini, m_truthtauContainerName, m_event, m_store, msg()) );
      }
    
      if ( !m_truthjetContainerName.empty() ) {
        if ( !HelperFunctions::isAvailable<xAOD::JetContainer>(m_truthjetContainerName, m_event, m_store, msg()) ){
          continue;
        }
        ANA_CHECK( HelperFunctions::retrieve(truth_jets, m_truthjetContainerName, m_event, m_store, msg()) );
      }
    
      const xAOD::TruthParticleContainer truth_electrons = HelperFunctions::sort_container_pt( truth_electrons_ini );
      const xAOD::TruthParticleContainer truth_muons     = HelperFunctions::sort_container_pt( truth_muons_ini );
      const xAOD::TruthParticleContainer truth_taus      = HelperFunctions::sort_container_pt( truth_taus_ini );
    
      if (m_writeTruthLeptonBranches) {
        helpTree->FillTruth( &truth_electrons, "truth_el" );
        helpTree->FillTruth( &truth_muons    , "truth_muon" );
      }
      
      if (m_useTaus)               helpTree->FillTruth( &truth_taus, "truth_tau" );
      if (m_writeTruthJetBranches) helpTree->FillJets ( truth_jets, -1, "truth_jet");
    }

    
    
    
    
    



    // object multiplicities (required for event skimming below)
    u_int n_elecs         = electrons->size();
    u_int n_muons         = muons->size();
    u_int n_leptons       = n_elecs + n_muons;
    u_int n_jets          = jets->size();
    u_int n_truth_elecs   = 0;
    u_int n_truth_muons   = 0;
    u_int n_truth_jets    = 0;
    u_int n_truth_leptons = 0;
    
    if (m_isMC) {
      n_truth_jets = truth_jets->size();
      n_truth_muons = truth_muons.size();
      n_truth_elecs = truth_electrons.size();
      n_truth_leptons = n_truth_elecs + n_truth_muons;
    }

    
    
    
    
    
    
    
    
    
    // signal leptons, fill baseline_leptons and signal_leptons containers
    // "passSelDecor" defined in ConstAccessors.h, uses signal selector decoration
    std::vector<const xAOD::Electron*> signal_electrons;
    std::vector<const xAOD::Muon*>     signal_muons;
    
    ConstDataVector<xAOD::IParticleContainer>* signal_leptonsCDV(nullptr);
    ConstDataVector<xAOD::IParticleContainer>* baseline_leptonsCDV(nullptr);
    signal_leptonsCDV   =  new ConstDataVector<xAOD::IParticleContainer>(SG::VIEW_ELEMENTS);
    baseline_leptonsCDV =  new ConstDataVector<xAOD::IParticleContainer>(SG::VIEW_ELEMENTS);
    
    
    
    
    u_int n_signal_elecs = 0;
    u_int n_signal_muons = 0;
    
    for ( auto iEl : *electrons ) {
      baseline_leptonsCDV->push_back(iEl);
      if (passSelDecor.isAvailable( *iEl ) && bool(passSelDecor(*iEl))) {
        n_signal_elecs = n_signal_elecs + 1;
        signal_electrons.push_back(iEl);
        signal_leptonsCDV->push_back(iEl);
      }
    }
    
    for ( auto iMu : *muons ) {
      baseline_leptonsCDV->push_back(iMu);
      if (passSelDecor.isAvailable( *iMu ) && bool(passSelDecor(*iMu))) {
        n_signal_muons = n_signal_muons + 1;
        signal_muons.push_back(iMu);
        signal_leptonsCDV->push_back(iMu);
      }
    }
    
    u_int n_signal_leptons = n_signal_elecs + n_signal_muons;

    
    
    
    // pt sorting to revert el-than-mu sorting from push-back loops
    xAOD::IParticleContainer signal_leptons   = HelperFunctions::sort_container_pt( signal_leptonsCDV->asDataVector() );
    xAOD::IParticleContainer baseline_leptons = HelperFunctions::sort_container_pt( baseline_leptonsCDV->asDataVector() );
    delete signal_leptonsCDV;
    delete baseline_leptonsCDV;


    
    
    
    
    // determine number of b-jets
    const SG::AuxElement::ConstAccessor< int >   BTagAccCont("BTag_Quantile_"+m_BtaggerName+"_"+m_BtaggerWP);
    const SG::AuxElement::ConstAccessor< char >  BTagAcc("BTag_"+m_BtaggerName+"_"+m_BtaggerWP);
    
    u_int n_bjets    = 0;
    u_int n_bjets_65 = 0;
    u_int n_bjets_70 = 0;
    u_int n_bjets_77 = 0;
    u_int n_bjets_85 = 0;
    u_int n_bjets_90 = 0;
    
    for ( auto iJet : *jets ) {
      if (m_BtaggerWP == "Continuous") {
        if (m_writeAllBTagWPs) {
          if (BTagAccCont.isAvailable( *iJet ) && (int(BTagAccCont(*iJet)) > 5)) {
            n_bjets_65 = n_bjets_65 + 1;
          }
          if (BTagAccCont.isAvailable( *iJet ) && (int(BTagAccCont(*iJet)) > 4)) {
            n_bjets_70 = n_bjets_70 + 1;
          }
          if (BTagAccCont.isAvailable( *iJet ) && (int(BTagAccCont(*iJet)) > 3)) {
            n_bjets_77 = n_bjets_77 + 1;
          }
          if (BTagAccCont.isAvailable( *iJet ) && (int(BTagAccCont(*iJet)) > 2)) {
            n_bjets_85 = n_bjets_85 + 1;
          }
          if (BTagAccCont.isAvailable( *iJet ) && (int(BTagAccCont(*iJet)) > 1)) {
            n_bjets_90 = n_bjets_90 + 1;
          }
        }
        if (BTagAccCont.isAvailable( *iJet ) && (int(BTagAccCont(*iJet)) > m_BtaggerCut)) {
          n_bjets = n_bjets + 1;
        }
      } else {
        if (BTagAcc.isAvailable( *iJet ) && bool(BTagAcc(*iJet))) {
          n_bjets = n_bjets + 1;
        }
      }
    }











    // event skimming: do this as early as possible to speed up the code



    // --------------- LEPTON + JET
    // require at least one baseline/signal lepton with pT > m_leadLepPtSkim GeV 
    // and require at least one jet with pT > m_leadJetPtSkim GeV
    // write out loose leptons only for the nominal tree, i.e. for isNominal == true
    
    bool passLepPlusJet = true;
    
    if (m_writeBaseLeptons && isNominal) {
      if ( n_leptons == 0 || n_leptons > 2 ) {
        passLepPlusJet = false;
      } else { // how many events survive nlep cut
        m_AlgoCutflow_LJ->Fill("Nlep", 1.);
        m_AlgoCutflow_LJ_weighted->Fill("Nlep", scalingFactor);
      }
      
      if ( n_leptons == 0 || (m_leadLepPtSkim > 0.0 && baseline_leptons[0]->pt()/m_units < m_leadLepPtSkim) )
        passLepPlusJet = false;

    } else {
      
      if ( n_signal_leptons == 0 || n_signal_leptons > 2 || n_signal_leptons != n_leptons ) {
        passLepPlusJet = false;
      } else { // how many events survive nsiglep cut
        if (isNominal) {
          m_AlgoCutflow_LJ->Fill("Nsiglep", 1.);
          m_AlgoCutflow_LJ_weighted->Fill("Nsiglep", scalingFactor);
        }
      }
      
      if ( n_signal_leptons == 0 || (m_leadLepPtSkim > 0.0 && signal_leptons[0]->pt()/m_units < m_leadLepPtSkim) )
        passLepPlusJet = false;
    }
    
    
    // how many events survive leppt skim cut
    if (passLepPlusJet && isNominal) {
      m_AlgoCutflow_LJ->Fill("LepPt", 1.);
      m_AlgoCutflow_LJ_weighted->Fill("LepPt", scalingFactor);
    }

    if ( n_jets == 0 || (m_leadJetPtSkim > 0.0 && jets->at(0)->pt()/m_units < m_leadJetPtSkim) ) {
      passLepPlusJet = false;
    }
    
      // how many events survive jet pt cut
    if (passLepPlusJet && isNominal) {
      m_AlgoCutflow_LJ->Fill("JetPt", 1.);
      m_AlgoCutflow_LJ_weighted->Fill("JetPt", scalingFactor);
    }

    // calculate invariant mass of lepton and jet and require at least m_mLepJetSkim
    if (passLepPlusJet) {
      
      TLorentzVector lj_cut;
      if (m_writeBaseLeptons && isNominal) {
        lj_cut = baseline_leptons[0]->p4() + jets->at(0)->p4();
      } else {
        lj_cut = signal_leptons[0]->p4() + jets->at(0)->p4();
      }
      
      if ( m_mLepJetSkim > 0.0 && (lj_cut.M()/m_units < m_mLepJetSkim) )
        passLepPlusJet = false;
    }
    
    // how many events survive mlj cut
    if (passLepPlusJet && isNominal) {
      m_AlgoCutflow_LJ->Fill("mLepJet", 1.);
      m_AlgoCutflow_LJ_weighted->Fill("mLepJet", scalingFactor);
    }



    // calculate invariant mass of both leptons and require at least m_mLepLepSkim [GeV] in 2lep+jet events
    if (passLepPlusJet) {
      
      TLorentzVector ll_cut;
      
      if (m_writeBaseLeptons && isNominal) {
        if (n_leptons == 2) {
          
          ll_cut = baseline_leptons[0]->p4() + baseline_leptons[1]->p4();
          
          if ( m_mLepLepSkim > 0.0 && (ll_cut.M()/m_units < m_mLepLepSkim) )
            passLepPlusJet = false;
        }
      } else {
        
        if (n_signal_leptons == 2){
          
          ll_cut = signal_leptons[0]->p4() + signal_leptons[1]->p4();
          
          if ( m_mLepLepSkim > 0.0 && (ll_cut.M()/m_units < m_mLepLepSkim) )
            passLepPlusJet = false;
        }
      }
    }


    // how many events survive mll cut
    if (passLepPlusJet && isNominal) {
      m_AlgoCutflow_LJ->Fill("dilepton_m", 1.);
      m_AlgoCutflow_LJ_weighted->Fill("dilepton_m", scalingFactor);
    }







    // --------------- DILEPTON
    // require at least two same-flavour leptons
    // opposite charge (required for dimuon channel)
    
    bool passDilepton = true;

    // leading lepton pt is low, or we do not have enough leptons
    if ((n_signal_elecs < 2 && n_signal_muons < 2) || (m_leadLepPtSkim > 0.0 && signal_leptons[0]->pt()/m_units < m_leadLepPtSkim)  ) {
      passDilepton = false;
    } else {
      if (isNominal) {
        m_AlgoCutflow_LL->Fill("Nsiglep", 1.);
        m_AlgoCutflow_LL_weighted->Fill("Nsiglep", scalingFactor);
      }
    }


    // select to write a specific channel
    if (passDilepton) {

      if (!m_writeMuonChannel) {
        // we want to remove muon events
        if (n_signal_muons >= 2 && n_signal_elecs < 2) {
          // we have muons
          passDilepton = false;
        } else if (isNominal ){
          // we don't have muons, so we fill the cutflow
          m_AlgoCutflow_LL->Fill("Remove_muons", 1.);
          m_AlgoCutflow_LL_weighted->Fill("Remove_muons", scalingFactor);
        }
      }
      
      if (!m_writeEleChannel) {
        // we want to remove electron events
        if (n_signal_elecs >= 2) {
          // we have electrons
          passDilepton = false;
        } else if (isNominal ){
          // we don't have electrons, so we fill the cutflow
            m_AlgoCutflow_LL->Fill("Remove_elecs", 1.);
            m_AlgoCutflow_LL_weighted->Fill("Remove_elecs", scalingFactor);
        }
      }
    }




    // leading lepton skim //yfu combine jetfake
    if (passDilepton) {
      if (m_leadLepPtSkim > 0.0 && signal_leptons[0]->pt()/m_units < m_leadLepPtSkim) {
        passDilepton = false;
      } else {
        if (isNominal) {
          m_AlgoCutflow_LL->Fill("leading_lepton_pt", 1.);
          m_AlgoCutflow_LL_weighted->Fill("leading_lepton_pt", scalingFactor);
        }
      }
    }


    // charge of muons
    if ( n_signal_muons >= 2 && n_signal_elecs < 2 ) {
      if ( !(chargeAcc.isAvailable(*signal_muons[0]) && chargeAcc.isAvailable(*signal_muons[1])) ) {
        // doesnt have the charge stored
        passDilepton = false;
      }
      if ( chargeAcc(*signal_muons[0]) * chargeAcc(*signal_muons[1]) != -1 ){
        // have the same charge
        passDilepton = false;
      }
    }

    if (passDilepton && isNominal) { // how many events pass signal muon OS cut
      m_AlgoCutflow_LL->Fill("muon_OS", 1.);
      m_AlgoCutflow_LL_weighted->Fill("muon_OS", scalingFactor);
    }



    if (passDilepton) {
      
      TLorentzVector dilep_cut;
      
      if (n_signal_muons >= 2){
        
        dilep_cut = signal_muons[0]->p4() + signal_muons[1]->p4();
        
        if ( m_mLepLepSkim > 0.0 && (dilep_cut.M()/m_units < m_mLepLepSkim) ) {
          passDilepton = false;
        }
      }
      
      if (n_signal_elecs >= 2){
        
        dilep_cut = signal_electrons[0]->p4() + signal_electrons[1]->p4();
        
        if ( m_mLepLepSkim > 0.0 && (dilep_cut.M()/m_units < m_mLepLepSkim) ) {
          passDilepton = false;
        }
      }
    }

    // how many events survive mll cut
    if (passDilepton) {
      m_AlgoCutflow_LL->Fill("dilepton_m", 1.);
      m_AlgoCutflow_LL_weighted->Fill("dilepton_m", scalingFactor);
    }






    // --------------- SINGLE ELECTRON //yfu combine jetfake
    // require at least one electron, for fake electron studies

    bool passSingleEl = true;

    // leading lepton pt is low, or we do not have enough leptons
    if ((n_signal_elecs < 1)) {
      passSingleEl = false;
    } else {
      if (isNominal) {
        m_AlgoCutflow_EL->Fill("Nsiglep", 1.);
        m_AlgoCutflow_EL_weighted->Fill("Nsiglep", scalingFactor);
      }
    }


    // leading lepton skim
    if (passSingleEl) {
      if (m_leadLepPtSkim > 0.0 && signal_leptons[0]->pt()/m_units < m_leadLepPtSkim) {
        passSingleEl = false;
      } else {
        if (isNominal) {
          m_AlgoCutflow_EL->Fill("leading_lepton_pt", 1.);
          m_AlgoCutflow_EL_weighted->Fill("leading_lepton_pt", scalingFactor);
        }
      }
    }





    if (passSingleEl) {
      TLorentzVector dilep_cut;

      if (n_signal_elecs >= 2){

        dilep_cut = signal_electrons[0]->p4() + signal_electrons[1]->p4();

        if ( m_mLepLepSkim > 0.0 && (dilep_cut.M()/m_units < m_mLepLepSkim) ) {
          passSingleEl = false;
        }
      }
    }

    // how many events survive mll cut
    if (passSingleEl) {
      m_AlgoCutflow_EL->Fill("dilepton_m", 1.);
      m_AlgoCutflow_EL_weighted->Fill("dilepton_m", scalingFactor);
    }











    // do the actual skimming here! Depending on what kind of events you want to write out
    if (m_writeDiLepton && m_writeLeptonJet) {
      if ( (!passLepPlusJet) && (!passDilepton) )
        continue;
    } else if (m_writeDiLepton && !m_writeLeptonJet) {
      if (!passDilepton)
        continue;
    } else if (!m_writeDiLepton && m_writeLeptonJet) {
      if (!passLepPlusJet)
        continue;
    } else if (m_writeSingleElectron) {//yfu combine jetfake
      if (!passSingleEl)
        continue;
    } else {
      continue;
    }















    // get final MET to calcuate variables with
    const xAOD::MissingET* met = (*metCont)["FinalTrk"];

    // fill branches for run numbers, etc.
    unsigned int datasetNumber = m_isMC ? eventInfo->mcChannelNumber() : -1;
    int year = get_year(randomRunNumber);
    setIntVariable("randomRunNumber", randomRunNumber);
    setIntVariable("datasetNumber"  , datasetNumber);
    setIntVariable("year"           , year);

    // fill MC-only branches such as weights, for data these will have a default value of
    if (m_isMC) {
      // Set branches containing metadata information
      setFloatVariable("sample_xSec", xSec);
      setFloatVariable("sample_xSec_up_rel", xSec*(1+xSecUnc));
      setFloatVariable("sample_xSec_down_rel", xSec*(1-xSecUnc));
      setFloatVariable("sample_kFactor", kFactor);
      setFloatVariable("sample_filterEff", filterEff);
      setFloatVariable("weight_gen", xSec*kFactor*filterEff);

      // Get Jvt & b-tagging SFs
      ANA_CHECK(computeEventJvtSF(jets, "weight_jvt", doSys));
      ANA_CHECK(computeEventBTagSF(jets, "weight_btag", doSys));
    }

    // Set lepton observables
    if (m_isMC) {
      setIntVariable("n_truth_el", n_truth_elecs);
      setIntVariable("n_truth_mu", n_truth_muons);
      setIntVariable("n_truth_lep", n_truth_leptons);
    }
    setIntVariable("n_el", n_elecs);
    setIntVariable("n_mu", n_muons);
    setIntVariable("n_lep", n_leptons);
    setIntVariable("n_signal_el", n_signal_elecs);
    setIntVariable("n_signal_mu", n_signal_muons);
    setIntVariable("n_signal_lep", n_signal_leptons);
    
    if ((m_BtaggerWP == "Continuous") && m_writeAllBTagWPs) {
      setIntVariable("n_bjets_65", n_bjets_65);
      setIntVariable("n_bjets_70", n_bjets_70);
      setIntVariable("n_bjets_77", n_bjets_77);
      setIntVariable("n_bjets_85", n_bjets_85);
      setIntVariable("n_bjets_90", n_bjets_90);
    }
    setIntVariable("n_bjets", n_bjets);

    // fill trigger decisions
    for (std::string trig : m_triggerListVec){
      bool passed_trigger = m_trigDecTool_handle->isPassed(trig);//yfu combine jetfake
      setBoolVariable(trig, m_trigDecTool_handle->isPassed(trig));
      if (passed_trigger) {//yfu combine jetfake
        auto trigChain = m_trigDecTool_handle->getChainGroup( trig );
        if(m_writeSingleElectron) setFloatVariable("prescale_" + trig, trigChain->getPrescale());
      }
    }

    // HT, the sum of all jet pTs
    float jets_HT = std::accumulate(jets->begin(), jets->end(), 0.0, [](int sum, const xAOD::Jet* jet) {return sum + jet->pt();})/m_units;
    setFloatVariable("jets_HT", jets_HT);







    // fill common lepton branches before continuing with dilepton/lepton-jet specific branches
    std::vector<const xAOD::IParticle*> leps;
    bool el_channel = false;
    bool twoleps    = false;
    bool OFleps     = false;
    
    if ( n_signal_elecs >= 2 ) {
      leps.push_back(signal_electrons[0]);
      leps.push_back(signal_electrons[1]);
      el_channel = true;
      twoleps    = true;

    } else if ( n_signal_muons >= 2 && n_signal_elecs < 2 ) {
      leps.push_back(signal_muons[0]);
      leps.push_back(signal_muons[1]);
      el_channel = false;
      twoleps    = true;
    
    } else if ( n_signal_leptons == 2 ) {
      leps.push_back(signal_leptons[0]);
      leps.push_back(signal_leptons[1]);
      
      if (leps[0]->type() == xAOD::Type::Electron) {
        el_channel = true;
      }
      
      twoleps = true;
      OFleps  = true;
    
    } else if (n_signal_leptons == 1) {
      
      leps.push_back(signal_leptons[0]);
      twoleps = false;
      
      if (leps[0]->type() == xAOD::Type::Electron) {
        el_channel = true;
      }
    } else if (!m_noSkim) {
      continue;
    }




    // check if any events got discarded in the lepton assignment
    if (passLepPlusJet && isNominal) {
      m_AlgoCutflow_LJ->Fill("lepAssign", 1.);
      m_AlgoCutflow_LJ_weighted->Fill("lepAssign", scalingFactor);
    }
    if (passDilepton && isNominal) {
      m_AlgoCutflow_LL->Fill("lepAssign", 1.);
      m_AlgoCutflow_LL_weighted->Fill("lepAssign", scalingFactor);
    }
    if (passSingleEl && isNominal) {//yfu combine jetfake
      m_AlgoCutflow_EL->Fill("lepAssign", 1.);
      m_AlgoCutflow_EL_weighted->Fill("lepAssign", scalingFactor);
    }





    // fill lepton branches
    if (leps.size() > 0) ANA_CHECK( fillLeptonVariables("lepton1", *leps[0]) );
    if (twoleps)         ANA_CHECK( fillLeptonVariables("lepton2", *leps[1]) );





    // transverse mass of leptons
    if (leps.size() > 0) {
      float mt_lep1 = TMath::Sqrt(2.0 * leps[0]->pt()/m_units * met->met()/m_units * (1.0 - TMath::Cos( TVector2::Phi_mpi_pi(leps[0]->phi() - met->phi()) ) ));
      setFloatVariable("mt_lep1", mt_lep1);
    }
    if (twoleps) {
      float mt_lep2 = TMath::Sqrt(2.0 * leps[1]->pt()/m_units * met->met()/m_units * (1.0 - TMath::Cos( TVector2::Phi_mpi_pi(leps[1]->phi() - met->phi()) ) ));
      setFloatVariable("mt_lep2", mt_lep2);
    }




    if (twoleps && m_writeDiLepton) {//yfu combine jetfake
      double dilep_pt = -99.0, dilep_eta = -99.0, dilep_phi = -99.0, dilep_m = -99.0;
      TLorentzVector v_dilep = leps[0]->p4() + leps[1]->p4();
      dilep_pt = v_dilep.Pt()/1000.;
      dilep_eta = v_dilep.Eta();
      dilep_phi = v_dilep.Phi();
      dilep_m = v_dilep.M()/1000.;

      setFloatVariable("dilepton_pt", dilep_pt);
      setFloatVariable("dilepton_eta", dilep_eta);
      setFloatVariable("dilepton_phi", dilep_phi);
      setFloatVariable("dilepton_m", dilep_m);

      setFloatVariable("dilepton_DeltaR", leps[0]->p4().DeltaR(leps[1]->p4()));
      setFloatVariable("dilepton_DeltaEta", fabs(leps[0]->p4().Eta() - leps[1]->p4().Eta()));
      setFloatVariable("dilepton_DeltaPhi", leps[0]->p4().DeltaPhi(leps[1]->p4()));

      TLorentzVector v_2lep = leps[0]->p4() + leps[1]->p4();
      float dir = v_2lep.Pz()/TMath::Abs(v_2lep.Pz());
      float num = ((leps[0]->p4().E()+leps[0]->p4().Pz())*(leps[1]->p4().E()-leps[1]->p4().Pz()))-((leps[0]->p4().E()-leps[0]->p4().Pz())*(leps[1]->p4().E()+leps[1]->p4().Pz()));
      float den = (v_2lep.M())*TMath::Sqrt((v_2lep.M())*(v_2lep.M())+(v_2lep.Pt())*(v_2lep.Pt()));
      float cts = dir*(num/den);
      setFloatVariable("dilepton_CosThetaStar", cts);
    }







    if (m_writeDiLepton) {//yfu combine jetfake
      // add born lepton branches
      const xAOD::TruthParticleContainer* born_leptons_ini = nullptr;
      const xAOD::TruthParticleContainer* truth_bosons_ini = nullptr;
      
      int numlep = 0.;
      float born_dilep_mass = 0;
      float truth_Z_mass = 0;
      
      if (m_isMC)// && m_writeDiLepton) yfu comment out
      {
        if ( !m_event->retrieve( born_leptons_ini, "BornLeptons" ).isSuccess() )
        {
          Error("execute()", "Failed to retrieve BornLeptons container. Exiting." );
          return EL::StatusCode::FAILURE;
        }
        const xAOD::TruthParticleContainer born_leptons = HelperFunctions::sort_container_pt( born_leptons_ini );
        //numlep = bornLeptons->size();
        TLorentzVector born_dilep;
        int bornlep_iter = 0;
        
        for( auto born_lepton: born_leptons ) 
        {
          if(born_lepton) {
            bornlep_iter = bornlep_iter + 1;
            born_dilep = born_dilep + born_lepton->p4(); 
            if (bornlep_iter == 1) {
              setFloatVariable("born_lepton1_E", born_lepton->e()/m_units);
              setFloatVariable("born_lepton1_pt", born_lepton->pt()/m_units);
              setFloatVariable("born_lepton1_eta", born_lepton->eta());
              setFloatVariable("born_lepton1_phi", born_lepton->phi());
            } else if (bornlep_iter == 2) {
              setFloatVariable("born_lepton2_E", born_lepton->e()/m_units);
              setFloatVariable("born_lepton2_pt", born_lepton->pt()/m_units);
              setFloatVariable("born_lepton2_eta", born_lepton->eta());
              setFloatVariable("born_lepton2_phi", born_lepton->phi());
            }       
            numlep++;
          }
        }
  
        setIntVariable("n_born_lepton", numlep);
        if (numlep == 2) {
          born_dilep_mass = born_dilep.M()/m_units;
          setFloatVariable("born_dilepton_m", born_dilep_mass);
        }
  
        // 
        if ( !m_event->retrieve( truth_bosons_ini, "TruthBoson" ).isSuccess() )
        {
          Error("execute()", "Failed to retrieve TruthBosons container. Exiting." );
          return EL::StatusCode::FAILURE;
        }
  
        const xAOD::TruthParticleContainer truth_bosons = HelperFunctions::sort_container_pt( truth_bosons_ini );
        
        Int_t numboson = truth_bosons.size();
        Int_t num_Z = 0;
  
        for( auto truth_boson: truth_bosons ) 
        {
          if(truth_boson) {
            if(truth_boson->m() < 130) continue;
            if(TMath::Abs(truth_boson->pdgId()) != 23) continue;
            num_Z += 1;
            truth_Z_mass = truth_boson->m();
          }
        }
  
        setIntVariable("n_truth_boson", num_Z);
  
        if (num_Z == 2){
          setFloatVariable("truth_boson_m", truth_Z_mass/m_units);
        }
      }
    }






    // add mW
    const xAOD::TruthParticleContainer* hardScatterParts = NULL;
    bool gotLep = false;
    bool gotNeut = false;
    Float_t w_mass = 0;
    if (m_isMC) 
    {
      // new derivations don't include HardScatterParticles anymore (buggy?), so this needs to be revisited
      // see https://gitlab.cern.ch/atlas/athena/-/merge_requests/72044
      if ( m_event->contains<xAOD::TruthParticleContainer>("HardScatterParticles") && 
           m_event->retrieve( hardScatterParts, "HardScatterParticles" ).isSuccess() ) {
        TLorentzVector w_vec;
        
        for( auto hardScatterPart: *hardScatterParts ) {
          // pick a charged lepton with W origin && (hardScatterPart->auxdata<unsigned int>("classifierParticleOrigin") == 12)
          if ((!gotLep)  && 
              ( (TMath::Abs(hardScatterPart->pdgId()) == 11) ||
                (TMath::Abs(hardScatterPart->pdgId()) == 13) ||
                (TMath::Abs(hardScatterPart->pdgId()) == 15) 
              ) )
          {
            w_vec = w_vec + hardScatterPart->p4();
            ANA_MSG_DEBUG("Found hardscatter charged lepton");
            ANA_MSG_DEBUG("Particle Origin: " << hardScatterPart->auxdata<unsigned int>("classifierParticleOrigin"));
            gotLep = true;
          }
          
          // pick a neutrino
          if( (!gotNeut) && 
              ( (TMath::Abs(hardScatterPart->pdgId()) == 12) ||
                (TMath::Abs(hardScatterPart->pdgId()) == 14) ||
                (TMath::Abs(hardScatterPart->pdgId()) == 16) 
              ) )
          {
            w_vec = w_vec + hardScatterPart->p4();
            ANA_MSG_DEBUG("Found hardscatter neutrino");
            gotNeut = true;
          }
        }
        
        if (gotLep && gotNeut) {
          w_mass = w_vec.M()/m_units;
          setFloatVariable("hardscatter_W_m", w_mass);
        }
      }
    }




    // fill MC-only branches such as weights, for data these will have a default value of 1
    if (m_isMC) {
      // Get lepton SFs
      ANA_CHECK(computeEventLepSF(signal_leptons, "weight_lepton", doSys));
    }






    // Now to the analysis specific branches
    if (passLepPlusJet && m_writeLeptonJet) {

      // define lepton and jet to be used to calculate analysis variables with
      // define matched truth lep
      // define leading truth jet
      const xAOD::Jet* jet = jets->at(0);
      const xAOD::TruthParticle* truth_lep = 0;
      const xAOD::IParticle* truth_jet     = 0;
      if (m_isMC) truth_lep = getTruthMatchedParticle( *leps[0] );
      if (n_truth_jets > 0) truth_jet = truth_jets->at(0);

      // add easily accessible singleLep trigger
      if (el_channel) {
          
        if (year == 2015 && 
            (bool(m_trigDecTool_handle->isPassed("HLT_e120_lhloose")) ||
              bool(m_trigDecTool_handle->isPassed("HLT_e24_lhmedium_L1EM20VH")) ||
              bool(m_trigDecTool_handle->isPassed("HLT_e60_lhmedium"))
            )) {
            setBoolVariable("HLT_singleLep", true);
          }
          
          if ((year == 2016 || 
               year == 2017 ||
               year == 2018
              ) &&
              (bool(m_trigDecTool_handle->isPassed("HLT_e140_lhloose_nod0")) ||
              bool(m_trigDecTool_handle->isPassed("HLT_e26_lhtight_nod0_ivarloose")) ||
              bool(m_trigDecTool_handle->isPassed("HLT_e60_lhmedium_nod0"))
              )) {
            setBoolVariable("HLT_singleLep", true);
          }
          
          if ((year == 2022) &&
              (bool(m_trigDecTool_handle->isPassed("HLT_e26_lhtight_ivarloose_L1EM22VHI")) ||
               bool(m_trigDecTool_handle->isPassed("HLT_e60_lhmedium_L1EM22VHI")) ||
               bool(m_trigDecTool_handle->isPassed("HLT_e140_lhloose_L1EM22VHI"))
              )) {
            setBoolVariable("HLT_singleLep", true);
          }
          if ((year == 2023 ||
               year == 2024
              ) &&
              (bool(m_trigDecTool_handle->isPassed("HLT_e26_lhtight_ivarloose_L1eEM26M")) ||
               bool(m_trigDecTool_handle->isPassed("HLT_e60_lhmedium_L1eEM26M")) ||
               bool(m_trigDecTool_handle->isPassed("HLT_e140_lhloose_L1eEM26M"))
              )) {
            setBoolVariable("HLT_singleLep", true);
          } // yfu add 2024
      
      } else {
          if (year == 2015 &&
              (bool(m_trigDecTool_handle->isPassed("HLT_mu20_iloose_L1MU15")) ||
               bool(m_trigDecTool_handle->isPassed("HLT_mu40"))
              )) {
            setBoolVariable("HLT_singleLep", true);
          }
          
          if ((year == 2016 ||
               year == 2017 ||
               year == 2018
              ) &&
              (bool(m_trigDecTool_handle->isPassed("HLT_mu26_ivarmedium")) ||
               bool(m_trigDecTool_handle->isPassed("HLT_mu50"))
              )) {
            setBoolVariable("HLT_singleLep", true);
          }
          
          if ((year == 2022 ||
               year == 2023 ||
               year == 2024
              ) &&
              (bool(m_trigDecTool_handle->isPassed("HLT_mu24_ivarmedium_L1MU14FCH")) ||
               bool(m_trigDecTool_handle->isPassed("HLT_mu50_L1MU14FCH"))
              )) {
            setBoolVariable("HLT_singleLep", true);
          } // yfu add 2024
      }
      // add easily accessible singleJet trigger
      if (year == 2015 ||
          year == 2016 ||
          year == 2017 ||
          year == 2018) {
        if (bool(m_trigDecTool_handle->isPassed("HLT_j420"))) {
          setBoolVariable("HLT_singleJet", true);
        }
      
      } else if (year == 2022 ||
                  year == 2023 ||
                  year == 2024) { // yfu add 2024
        if (bool(m_trigDecTool_handle->isPassed("HLT_j420_pf_ftf_preselj225_L1J100"))) {
          setBoolVariable("HLT_singleJet", true);
        }
      }
      

      // Set lepton observables
      if (m_doTrigMatch) {
        if (twoleps && !OFleps) {
          setBoolVariable("lepton_singleleptrigMatched",
                          isTrigMatched(leps[0], randomRunNumber) || isTrigMatched(leps[1], randomRunNumber)
                         );
          ANA_CHECK(getSingleLepTrigSF(leps, randomRunNumber, "weight_singleleptonTrigSF", doSys));
        } else {
          setBoolVariable("lepton_singleleptrigMatched", isTrigMatched(leps[0], randomRunNumber));
          ANA_CHECK(getSingleLepTrigSF(leps[0], randomRunNumber, "weight_singleleptonTrigSF", doSys));
        }
      }
      else {
        setBoolVariable("lepton_singleleptrigMatched", true);
        setFloatVariable("weight_singleleptonTrigSF", 1.0);
      }

      // set leading jet variables
      setFloatVariable("jet1_E", jet->e()/m_units);
      setFloatVariable("jet1_pt", jet->pt()/m_units);
      setFloatVariable("jet1_phi", jet->phi());
      setFloatVariable("jet1_eta", jet->eta());
      
      if (JvtAcc.isAvailable( *jet )) {
        setFloatVariable("jet1_Jvt", JvtAcc( *jet));
      }
      
      if (PartonTruthLabelIDAcc.isAvailable( *jet )) {
        setIntVariable("jet1_PartonTruthLabelID", PartonTruthLabelIDAcc( *jet ));
      }
      
      if (ConeTruthLabelIDAcc.isAvailable( *jet )) {
        setIntVariable("jet1_ConeTruthLabelID", ConeTruthLabelIDAcc( *jet ));
      }
      
      if (m_BtaggerWP == "Continuous") {
        if (m_writeAllBTagWPs) {
          
          if (BTagAccCont.isAvailable( *jet )) {
            setBoolVariable("jet1_btag_65", bool(BTagAccCont(*jet) > 5) );
          }
          
          if (BTagAccCont.isAvailable( *jet )) {
            setBoolVariable("jet1_btag_70", bool(BTagAccCont(*jet) > 4) );
          }
          
          if (BTagAccCont.isAvailable( *jet )) {
            setBoolVariable("jet1_btag_77", bool(BTagAccCont(*jet) > 3) );
          }
          
          if (BTagAccCont.isAvailable( *jet )) {
            setBoolVariable("jet1_btag_85", bool(BTagAccCont(*jet) > 2) );
          }
          
          if (BTagAccCont.isAvailable( *jet )) {
            setBoolVariable("jet1_btag_90", bool(BTagAccCont(*jet) > 1) );
          }
        }
        if (BTagAccCont.isAvailable( *jet )) {
          setBoolVariable("jet1_btag", bool(BTagAccCont(*jet) > m_BtaggerCut) );
        }
      
      } else {
        if (BTagAcc.isAvailable( *jet )) {
          setBoolVariable("jet1_btag", bool(BTagAcc(*jet)));
        }
      }

      // fill per-jet branches (only for nominal tree)
      if (doSys) {
        static SG::AuxElement::ConstAccessor< char > isJvtHSAcc("isJvtHS");
        std::vector<char> vec_isJvtHS;
        for ( const xAOD::Jet* jet : *jets ) {
          // decorator only available for MC, set to 1 for data
          vec_isJvtHS.push_back( m_isMC ? isJvtHSAcc(*jet) : 1);
        }
        setVecCharVariable("jet_isJvtHS",vec_isJvtHS);
      }


      // fill lepton-jet branches
      if (leps[0] && jet){
        TLorentzVector lj = leps[0]->p4() + jet->p4();
        setFloatVariable("mLepJet", lj.M()/1000.);
        setFloatVariable("dRLepJet", jet->p4().DeltaR(leps[0]->p4()));
        setFloatVariable("detaLepJet", TMath::Abs(jet->eta() - leps[0]->eta()));
        setFloatVariable("dphiLepJet", TMath::Abs(TVector2::Phi_mpi_pi(jet->phi() - leps[0]->phi())));
        setFloatVariable("LepOvermLepJet", leps[0]->pt()/lj.M());
        if (truth_jet) {
          if (jet->p4().DeltaR(truth_jet->p4()) < 0.4) {
            setFloatVariable("matched_mLepJet", lj.M()/1000.);
          }
        }
      }

      if (truth_lep && truth_jet){
        TLorentzVector truth_lj = truth_lep->p4() + truth_jet->p4();
        setFloatVariable("truth_mLepJet", truth_lj.M()/1000.);
        setFloatVariable("truth_dRLepJet", truth_jet->p4().DeltaR(truth_lep->p4()));
      }

      // calculate and fill further analysis variables
      // effective mass, sum of lep pT, jet pTs and MET
      float meff = leps[0]->pt()/m_units + jets_HT + met->met()/m_units;

      setFloatVariable("meff", meff);

      // additional angular variables
      // minDphi(jets, MET)
      if (n_jets > 0){
        float mindphi_jMET = 9.;
        for ( auto iJet : *jets ) {
          double dphi_jMET = TMath::Abs(TVector2::Phi_mpi_pi(iJet->phi() - met->phi()));
          if (dphi_jMET < mindphi_jMET) {
            mindphi_jMET = dphi_jMET;
          }
        }
        setFloatVariable("mindphiJetMet", mindphi_jMET);
      }
      // dphi(lep, MET)
      setFloatVariable("dphiLepMet", TMath::Abs(TVector2::Phi_mpi_pi(leps[0]->phi() - met->phi())));
    }

    


    if (passDilepton && m_writeDiLepton) {
      
      if (m_doTrigMatch) {
        // di-electron triggers for electron channel
        if ( (n_signal_elecs >= 2)) {

          if (m_triggerList.find("HLT_2e") != std::string::npos) {//yfu combine jetfake
            // di-electron triggers for electron channel
            setBoolVariable("lepton_dileptrigMatched",
                            isTrigMatched_diLep(*eventInfo, *leps[0], *leps[1], randomRunNumber));
          } else {
            setBoolVariable("lepton_dileptrigMatched", isTrigMatched(leps[0], randomRunNumber) || isTrigMatched(leps[1], randomRunNumber));
          }

          if (!m_dielWP_Trig.empty()) {//yfu combine jetfake
            ANA_CHECK(getElectronTrigSFTwoLeptons(eventInfo, leps, randomRunNumber, "weight_dileptonTrigSF", doSys));
          }
        }
        // single-muon triggers for muon channel
        else {
          setBoolVariable("lepton_dileptrigMatched", isTrigMatched(leps[0], randomRunNumber) || isTrigMatched(leps[1], randomRunNumber));
          if (!m_muWP_Trig.empty() || !m_elWP_Trig.empty()) {//yfu combine jetfake
            if (el_channel && !m_elWP_Trig.empty()) {
              ANA_CHECK(getSingleLepTrigSF(leps, randomRunNumber, "weight_dileptonTrigSF", doSys, true));
            } else if (!el_channel && !m_muWP_Trig.empty()){
              ANA_CHECK(getSingleLepTrigSF(leps, randomRunNumber, "weight_dileptonTrigSF", doSys, false));
            }
          }

        }
      } else {
        setBoolVariable("lepton_dileptrigMatched", true);
        setFloatVariable("weight_dileptonTrigSF", 1.0);
      }
    }
    
    // Finally, fill EventInfo
    helpTree->FillEvent( eventInfo, m_event, vertices );
    
    // Fill trigger information
    if ( !m_trigDetailStr.empty() )    {
      helpTree->FillTrigger( eventInfo );
    }

    // fill the tree
    helpTree->Fill();

  }

  // reset variables to defaults after branches have been filled
  resetVariables(m_branchDict_bool);
  resetVariables(m_branchDict_int);
  resetVariables(m_branchDict_float);
  resetVariables(m_branchDict_char);
  resetVariables(m_branchDict_vecBool);
  resetVariables(m_branchDict_vecInt);
  resetVariables(m_branchDict_vecFloat);
  resetVariables(m_branchDict_vecChar);

  if (m_firstEvent){
    m_firstEvent = false;
  }


  return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo :: postExecute (){ return EL::StatusCode::SUCCESS; }





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo :: finalize ()
{
  ANA_MSG_INFO( "Deleting tree instances...");

  for(auto& item: m_trees){
    if(item.second) {delete item.second; item.second = nullptr; }
  }
  m_trees.clear();

  return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo :: histFinalize ()
{
  ANA_MSG_INFO("Calling histFinalize");

  // Copy histogram with Metadata to our main output file
  TFile * treeFile = wk()->getOutputFile("tree");
  TFile *fileMD = wk()->getOutputFile("metadata");
  if (fileMD){
    TH1D* h_histEventCount = (TH1D*)fileMD->Get("MetaData_EventCount");
    TH1F* h_histEventCountCopy = (TH1F*) h_histEventCount->Clone();
    h_histEventCountCopy->SetDirectory(treeFile);
  }

  TH1F* AlgoCutflow_LJ =static_cast<TH1F*>(m_AlgoCutflow_LJ ->Clone());
  AlgoCutflow_LJ ->SetName("LJAlgo_LJcutflow" );
  AlgoCutflow_LJ ->SetDirectory(treeFile);
  TH1F* AlgoCutflow_LJ_weighted =static_cast<TH1F*>(m_AlgoCutflow_LJ_weighted ->Clone());
  AlgoCutflow_LJ_weighted ->SetName("LJAlgo_LJcutflow_weighted" );
  AlgoCutflow_LJ_weighted ->SetDirectory(treeFile);
  TH1F* AlgoCutflow_LL =static_cast<TH1F*>(m_AlgoCutflow_LL ->Clone());
  AlgoCutflow_LL ->SetName("LJAlgo_LLcutflow" );
  AlgoCutflow_LL ->SetDirectory(treeFile);
  TH1F* AlgoCutflow_LL_weighted =static_cast<TH1F*>(m_AlgoCutflow_LL_weighted ->Clone());
  AlgoCutflow_LL_weighted ->SetName("LJAlgo_LLcutflow_weighted" );
  AlgoCutflow_LL_weighted ->SetDirectory(treeFile);
  TH1F* AlgoCutflow_EL =static_cast<TH1F*>(m_AlgoCutflow_EL ->Clone());//yfu combine jetfake
  AlgoCutflow_EL ->SetName("LJAlgo_ELcutflow" );
  AlgoCutflow_EL ->SetDirectory(treeFile);
  TH1F* AlgoCutflow_EL_weighted =static_cast<TH1F*>(m_AlgoCutflow_EL_weighted ->Clone());
  AlgoCutflow_EL_weighted ->SetName("LJAlgo_ELcutflow_weighted" );
  AlgoCutflow_EL_weighted ->SetDirectory(treeFile);
  TH1D* histVariationsSumW =static_cast<TH1D*>(m_histVariationsSumW ->Clone());
  histVariationsSumW ->SetName("MetaData_VariationsSumW" );
  histVariationsSumW ->SetDirectory(treeFile);

  delete m_AlgoCutflow_LJ;
  delete m_AlgoCutflow_LJ_weighted;
  delete m_AlgoCutflow_LL;
  delete m_AlgoCutflow_LL_weighted;
  delete m_AlgoCutflow_EL;//yfu combine jetfake
  delete m_AlgoCutflow_EL_weighted;
  delete m_histVariationsSumW;

  // Copy all cutflow histograms to our main output file
  TFile *fileCF = wk()->getOutputFile("cutflow");
  if (fileCF){

    // for whatever reason GetListOfKeys() doesn't return anything so we have to
    // explicitly retrieve them one-by-one ...
    TH1D* h_cutflow = (TH1D*)fileCF->Get("cutflow");
    TH1D* h_cutflowWeighted = (TH1D*)fileCF->Get("cutflow_weighted");
    TH1D* h_cutflowCopy = (TH1D*)h_cutflow->Clone();
    TH1D* h_cutflowWeightedCopy = (TH1D*)h_cutflowWeighted->Clone();
    h_cutflowCopy->SetDirectory(treeFile);
    h_cutflowWeightedCopy->SetDirectory(treeFile);

    // maybe someone finds out why this doesn't work here ....
    // for(const auto&& obj: *fileCF->GetListOfKeys()) {
    //   TString name = TString(obj->GetName());
    //   ANA_MSG_INFO("found object: " << name);
    //   if (name.BeginsWith("cutflow")) {
    //     ANA_MSG_INFO("found cutflow!");
    //     TH1D* h_cutflow = (TH1D*)fileCF->Get(name);
    //     TH1D* h_cutflowCopy = (TH1D*)h_cutflow->Clone();
    //     h_cutflowCopy->SetDirectory(treeFile);
    //   }
    // }
  }

  return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo :: getLumiWeights(const xAOD::EventInfo* /*eventInfo*/){ return EL::StatusCode::SUCCESS; }





// ---------------------------------------------------------------------------//
LJTree* LJAlgo :: createTree(xAOD::TEvent *event, TTree* tree, TFile* file, const float units, bool debug, xAOD::TStore* store) {
    return new LJTree( event, tree, file, units, debug, store, m_BtaggerName, m_BtaggerWP, m_BtaggerCut, m_writeAllBTagWPs );
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo::addLeptonSystWeights(std::string weightName) {
  ANA_MSG_DEBUG("Starting addLeptonSystWeights");
  // bookkeep the constituent SFs of the lepton weight
  std::vector< std::string > SF_names{"Reco", "Iso", "PID", "TTVA"};
  // used as dummy for PID/TTVA
  std::vector< std::string > emptyList{};

  // go through the different types of SFs and add all available systematic variations as additional weight branches
  for( unsigned int SF_i=0; SF_i < 4; ++SF_i){
    //// Get list of systematic variations ////
    std::vector< std::string >* el_sysVariationNames(nullptr);
    std::vector< std::string >* mu_sysVariationNames(nullptr);
    // strings to pass to CP tools to retrieve list of systematic names
    std::string systNames_mu, systNames_el;

    if (SF_i == 0) { // first do Reco
      systNames_mu      = "MuonEfficiencyCorrector_RecoSyst_Reco"+m_muWP_Reco;
      systNames_el      = "EleEffCorr_RecoSyst_"+m_elWP_Reco;
      ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store) );
      ANA_CHECK( HelperFunctions::retrieve(mu_sysVariationNames, systNames_mu, m_event, m_store) );
    } else if (SF_i == 1) { // second do Iso
      systNames_mu      = "MuonEfficiencyCorrector_IsoSyst_Iso"+m_muWP_Iso;
      systNames_el      = "EleEffCorr_IsoSyst_"+m_elWP_ID+"_isol"+m_elWP_Iso;
      ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store) );
      ANA_CHECK( HelperFunctions::retrieve(mu_sysVariationNames, systNames_mu, m_event, m_store) );
    } else if (SF_i == 2) { // third do PID
      systNames_mu      = "";
      systNames_el      = "EleEffCorr_PIDSyst_"+m_elWP_ID;
      ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store) );
      mu_sysVariationNames = &emptyList;
    } else if (SF_i == 3) { // fourth do TTVA
      systNames_mu      = "MuonEfficiencyCorrector_TTVASyst_"+m_muWP_TTVA;
      systNames_el      = "";
      ANA_CHECK( HelperFunctions::retrieve(mu_sysVariationNames, systNames_mu, m_event, m_store) );
      el_sysVariationNames = &emptyList;
    }
    if (el_sysVariationNames->size() < 2) {
      if (SF_i != 3) ANA_MSG_WARNING("Electron systematics list for " << SF_names[SF_i] << " only contains nominal! Cross-check the accessor string with the ElectronEfficiencyCorrector config...");
    } else {
      for (unsigned int iS=1; iS<el_sysVariationNames->size(); ++iS) {
        std::string systInfoName = el_sysVariationNames->at(iS);
        addFloatVariable(weightName + "_" + systInfoName, 1.0, true);
      }
    }
    if (mu_sysVariationNames->size() < 2) {
      if (SF_i != 2) ANA_MSG_WARNING("Muon systematics list for " << SF_names[SF_i] << " only contains nominal! Cross-check the accessor string with the MuonEfficiencyCorrector config...");
    } else {
      for (unsigned int iS=1; iS<mu_sysVariationNames->size(); ++iS) {
        std::string systInfoName = mu_sysVariationNames->at(iS);
        addFloatVariable(weightName + "_" + systInfoName, 1.0, true);
      }
    }
  }

  return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
// doSys decides if systematics are processed, weightName is the prefix used for the branches produced in this function
EL::StatusCode LJAlgo::computeEventLepSF(const xAOD::IParticleContainer& leptons, std::string weightName, bool doSys) {
  
  ANA_MSG_DEBUG("Starting computeEventLepSF");
  
  
  // bookkeep the constituent SFs of the lepton weight
  std::vector< std::string > SF_names{"Reco", "Iso", "PID", "TTVA"};
  // used as dummy for PID/TTVA
  std::vector< std::string > emptyList{};

  
  // save all names of sytematic variations in one matrix, add nominal for every SF type already
  std::vector< std::vector< std::string > > all_sysVariationNames{{""}, {""}, {""}, {""}};
  
  // initialise SF matrix with one entry per SF type for now (nominal)
  std::vector< std::vector< float > > leptonSFs{{1.0}, {1.0}, {1.0}, {1.0}};

  




  // go through the different types of SFs and fill the list of all systematic weights
  if (doSys) {

    for( unsigned int SF_i=0; SF_i < 4; ++SF_i){
      //// Get list of systematic variations ////
      std::vector< std::string >* el_sysVariationNames(nullptr);
      std::vector< std::string >* mu_sysVariationNames(nullptr);

      // strings to pass to CP tools to retrieve list of systematic names
      std::string systNames_mu, systNames_el;

      if (SF_i == 0) { // first do Reco
        systNames_mu      = "MuonEfficiencyCorrector_RecoSyst_Reco"+m_muWP_Reco;
        systNames_el      = "EleEffCorr_RecoSyst_"+m_elWP_Reco;
	ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store) );
        ANA_CHECK( HelperFunctions::retrieve(mu_sysVariationNames, systNames_mu, m_event, m_store) );
      
      } else if (SF_i == 1) { // second do Iso
        systNames_mu      = "MuonEfficiencyCorrector_IsoSyst_Iso"+m_muWP_Iso;
        systNames_el      = "EleEffCorr_IsoSyst_"+m_elWP_ID+"_isol"+m_elWP_Iso;
	ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store) );
        ANA_CHECK( HelperFunctions::retrieve(mu_sysVariationNames, systNames_mu, m_event, m_store) );
      
      } else if (SF_i == 2) { // third do PID
        systNames_mu      = "";
        systNames_el      = "EleEffCorr_PIDSyst_"+m_elWP_ID;
	ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store) );
        mu_sysVariationNames = &emptyList;
      
      } else if (SF_i == 3) { // fourth do TTVA
        systNames_mu      = "MuonEfficiencyCorrector_TTVASyst_"+m_muWP_TTVA;
        systNames_el      = "";
	ANA_CHECK( HelperFunctions::retrieve(mu_sysVariationNames, systNames_mu, m_event, m_store) );
        el_sysVariationNames = &emptyList;
      }
      
      
      if (el_sysVariationNames->size() < 2) {
        if (SF_i != 3)
          ANA_MSG_WARNING("Electron systematics list for " << SF_names[SF_i] << 
                          " only contains nominal! Cross-check the accessor string with the ElectronEfficiencyCorrector config...");
      } else {
        for (unsigned int iS=1; iS<el_sysVariationNames->size(); ++iS) {
          std::string systInfoName = el_sysVariationNames->at(iS);
          leptonSFs[SF_i].push_back(1.0);
          all_sysVariationNames[SF_i].push_back(systInfoName);
        }
      }
      
      
      if (mu_sysVariationNames->size() < 2) {
        if (SF_i != 2)
          ANA_MSG_WARNING("Muon systematics list for " << SF_names[SF_i] << 
                          " only contains nominal! Cross-check the accessor string with the MuonEfficiencyCorrector config...");
      } else {
        for (unsigned int iS=1; iS<mu_sysVariationNames->size(); ++iS) {
          std::string systInfoName = mu_sysVariationNames->at(iS);
          leptonSFs[SF_i].push_back(1.0);
          all_sysVariationNames[SF_i].push_back(systInfoName);
        }
      }
    }
  }





  // Now that we have all_sysVariationNames and leptonSFs with the correct size, calculate the actual SFs
  for( unsigned int SF_i=0; SF_i < 4; ++SF_i){

    //// Get list of systematic variations ////
    std::vector< std::string >* el_sysVariationNames(nullptr);
    std::vector< std::string >* mu_sysVariationNames(nullptr);

    // names of lepton decorators to retrieve SF values
    std::string decorNames_SF_mu, decorNames_SF_el;
    // strings to pass to CP tools to retrieve list of systematic names
    std::string systNames_mu, systNames_el;



    if (SF_i == 0) {
      systNames_mu     = "MuonEfficiencyCorrector_RecoSyst_Reco"+m_muWP_Reco;
      systNames_el     = "EleEffCorr_RecoSyst_"+m_elWP_Reco;
      decorNames_SF_mu = "MuRecoEff_SF_syst_Reco"+m_muWP_Reco;
      decorNames_SF_el = "ElRecoEff_SF_syst_"+m_elWP_Reco;
      if( doSys ){
        ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store) );
        ANA_CHECK( HelperFunctions::retrieve(mu_sysVariationNames, systNames_mu, m_event, m_store) );
      }
    
    
    } else if (SF_i == 1) {
      systNames_mu     = "MuonEfficiencyCorrector_IsoSyst_Iso"+m_muWP_Iso;
      systNames_el     = "EleEffCorr_IsoSyst_"+m_elWP_ID+"_isol"+m_elWP_Iso;
      decorNames_SF_mu = "MuIsoEff_SF_syst_Iso"+m_muWP_Iso;
      decorNames_SF_el = "ElIsoEff_SF_syst_"+m_elWP_ID+"_isol"+m_elWP_Iso;
      if( doSys ){
        ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store) );
        ANA_CHECK( HelperFunctions::retrieve(mu_sysVariationNames, systNames_mu, m_event, m_store) );
      }
    
    
    } else if (SF_i == 2) {
      systNames_mu      = "";
      systNames_el      = "EleEffCorr_PIDSyst_"+m_elWP_ID;
      decorNames_SF_el  = "ElPIDEff_SF_syst_"+m_elWP_ID;
      if( doSys ){
        ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store) );
        mu_sysVariationNames = &emptyList;
      }
    
    
    } else if (SF_i == 3) {
      systNames_mu     = "MuonEfficiencyCorrector_TTVASyst_"+m_muWP_TTVA;
      systNames_el     = "";
      decorNames_SF_mu = "MuTTVAEff_SF_syst_"+m_muWP_TTVA;
      if( doSys ){
        ANA_CHECK( HelperFunctions::retrieve(mu_sysVariationNames, systNames_mu, m_event, m_store) );
        el_sysVariationNames = &emptyList;
      }
    }




    ANA_MSG_DEBUG("--------------------------------------");
    ANA_MSG_DEBUG("SF type = " << SF_names[SF_i] );

    //// Loop over each *signal* lepton and multiply its SFs
    for ( auto lep_itr : leptons ) {
      
      if (passSelDecor.isAvailable( *lep_itr )){
        if (!passSelDecor( *lep_itr )) continue;
      }

      std::vector < float > thisLepSF;
      std::string decor_name_SF;

      //yfu combine jetfake
      bool is_electron = lep_itr->type() == xAOD::Type::Electron;
      bool is_muon     = lep_itr->type() == xAOD::Type::Muon;

      if( is_electron ){
        decor_name_SF = decorNames_SF_el;
      }
      if( is_muon ){
        decor_name_SF = decorNames_SF_mu;
      }
      
      
      
      
      // Skip to next lepton when this is empty, i.e. for muon ID or electron TTVA
      if( decor_name_SF.size() == 0 )
        continue;


      // Skip to next lepton when the WP hasn't been set for the current SF type //yfu combine jetfake
      if (SF_i == 0) {
        if (is_electron && m_elWP_Reco.empty()) continue;
        if (is_muon     && m_muWP_Reco.empty()) continue;
      } else if (SF_i == 1) {
        if (is_electron && m_elWP_Iso.empty()) continue;
        if (is_muon     && m_muWP_Iso.empty()) continue;
      } else if (SF_i == 2) {
        if (is_electron && m_elWP_ID.empty()) continue;
      } else if (SF_i == 3) {
        if (is_muon     && m_muWP_TTVA.empty()) continue;
      }


      if ( lep_itr->isAvailable< std::vector< float > >( decor_name_SF ) ) {
        thisLepSF  = lep_itr->auxdecor< std::vector< float > >( decor_name_SF );
      } else {
        ANA_MSG_ERROR("Can't find SF working point "<< decor_name_SF.c_str());
        return EL::StatusCode::FAILURE;
      }



      ANA_MSG_DEBUG("SF is " << thisLepSF.at(0) );
      leptonSFs[SF_i][0] *= thisLepSF.at(0);

      if ( lep_itr->type() == xAOD::Type::Electron ){
        
        
        if( doSys ){
          if (el_sysVariationNames->size() > 1) { // avoid out of range error
            for( unsigned int iS=1; iS < el_sysVariationNames->size(); ++iS){
              std::string sys_infoName = el_sysVariationNames->at(iS);
              ANA_MSG_DEBUG("Electron SF with systematic variation " << sys_infoName << " is " << thisLepSF.at(iS) );
              leptonSFs[SF_i][iS] *= thisLepSF.at(iS);
            }
          }
          
          // next multiply the muon systematic variations (if available for this SF type) with the nominal weight
          if (mu_sysVariationNames->size() > 1) { // avoid out of range error
            for( unsigned int iS=1; iS < mu_sysVariationNames->size(); ++iS){
              std::string sys_infoName = mu_sysVariationNames->at(iS);
              ANA_MSG_DEBUG("Muon SF with systematic variation " << sys_infoName << " is set to nominal for current electron: " << thisLepSF.at(0) );
              leptonSFs[SF_i][iS+el_sysVariationNames->size()-1] *= thisLepSF.at(0);
            }
          }
        }
        
        
        for( unsigned int SF_alt=0; SF_alt < 4; ++SF_alt){
          // nominal and syst variations of current SF type SF_i are already done, fill syst variations of remaining SF types SF_alt with nominal SF
          if (SF_alt == SF_i) continue;
          ANA_MSG_DEBUG("Filling syst variations of " << SF_names[SF_alt] << " for this electron with the nominal of current SF type " << SF_names[SF_i] );
          for( unsigned int iS=0; iS < all_sysVariationNames[SF_alt].size(); ++iS){
            leptonSFs[SF_alt][iS] *= thisLepSF.at(0);
          }
        }
      
      
      } else if ( lep_itr->type() == xAOD::Type::Muon ){
        
        
        if( doSys ){
          // multiply the electron systematic variations (if available for this SF type) with the nominal weight
          if (el_sysVariationNames->size() > 1) { // avoid out of range error
            for( unsigned int iS=1; iS < el_sysVariationNames->size(); ++iS){
              std::string sys_infoName = el_sysVariationNames->at(iS);
              ANA_MSG_DEBUG("Electron SF with systematic variation " << sys_infoName << " is set to nominal for current muon: " << thisLepSF.at(0) );
              leptonSFs[SF_i][iS] *= thisLepSF.at(0);
            }
          }
          
          if (mu_sysVariationNames->size() > 1) { // avoid out of range error
            for( unsigned int iS=1; iS < mu_sysVariationNames->size(); ++iS){
              std::string sys_infoName = mu_sysVariationNames->at(iS);
              ANA_MSG_DEBUG("Muon SF with systematic variation " << sys_infoName << " is " << thisLepSF.at(iS) );
              leptonSFs[SF_i][iS+el_sysVariationNames->size()-1] *= thisLepSF.at(iS);
            }
          }
        }
        
        for( unsigned int SF_alt=0; SF_alt < 4; ++SF_alt){
          // nominal and syst variations of current SF type SF_i are already done, fill syst variations of remaining SF types SF_alt with nominal SF
          if (SF_alt == SF_i) continue;
          ANA_MSG_DEBUG("Filling syst variations of " << SF_names[SF_alt] << " for this muon with the nominal of current SF type " << SF_names[SF_i] );
          for( unsigned int iS=0; iS < all_sysVariationNames[SF_alt].size(); ++iS){
            leptonSFs[SF_alt][iS] *= thisLepSF.at(0);
          }
        }
      }
    } // lep loop
  }

  // finally set the lepton weight branch for nominal (just use the first entry of the first vector, even though the first entries of the other vectors would also contain the same value)
  setFloatVariable(weightName, leptonSFs[0][0]);
  ANA_MSG_DEBUG("Final nominal scale factor value = " << leptonSFs[0][0]);

  if( doSys ){
    for( unsigned int SF_i=0; SF_i < 4; ++SF_i){
      if (all_sysVariationNames[SF_i].size() > 1) {
        for( unsigned int iS=1; iS < all_sysVariationNames[SF_i].size(); ++iS){
          setFloatVariable(weightName+"_"+all_sysVariationNames[SF_i][iS], leptonSFs[SF_i][iS]);
        }
      }
    }
  }
  
  return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo::addJvtSystWeights(std::string weightName) {
  // create vector of syst names
  std::vector< std::string >* systNamesJVT(nullptr);
  ANA_CHECK( HelperFunctions::retrieve(systNamesJVT, "JetJvtEfficiency_JVTSyst_JVT_FixedEffPt", 0, m_store));

  // start at second entry as we only want to add the systematic variation branches
  ANA_MSG_DEBUG("List Jvt systematics: ");
  for (unsigned int iS=1; iS<systNamesJVT->size(); ++iS){
    std::string systInfoName = systNamesJVT->at(iS);
    ANA_MSG_DEBUG("Systematic at " << iS << " is " << systInfoName);
    addFloatVariable(weightName + "_" + systInfoName, 1.0, true);
  }
  return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
// doSys decides if systematics are processed, weightName is the prefix used for the branches produced in this function
EL::StatusCode LJAlgo::computeEventJvtSF(const xAOD::JetContainer* jets, std::string weightName, bool doSys) {

  // create vector of syst names
  std::vector< std::string >* systNamesJVT(nullptr);
  // initialise SF vector with one entry for now (nominal)
  std::vector< float > jvtSF(1,1.0);
  if (doSys) {
    ANA_CHECK( HelperFunctions::retrieve(systNamesJVT, "JetJvtEfficiency_JVTSyst_JVT_FixedEffPt", 0, m_store));
    // nominal SF and syst variations
    jvtSF.resize(systNamesJVT->size(),1.0);
  }

  for (const xAOD::Jet* jet : *jets){
    // the nominal SF is the first one in the vector
    if (JvtSFAcc.isAvailable( *jet ) && JvtHSAcc.isAvailable( *jet )){
      ANA_MSG_DEBUG( "Found Jet JVT nominal: " << JvtSFAcc(*jet)[0]);
      if (JvtHSAcc(*jet)) {
        jvtSF.at(0) *= JvtSFAcc(*jet).at(0);
        if (doSys){
          if (JvtSFAcc(*jet).size() != 3) {
            ANA_MSG_WARNING("Unexpected number of systematic jvt variations (should be 2+nominal=3): " << JvtSFAcc(*jet).size());
            ANA_MSG_WARNING("Number of entries in syst list by xAH: " << systNamesJVT->size());
          }
          // for systematics, start at the second entry as the first is nominal
          for (unsigned int iS=1; iS<systNamesJVT->size(); ++iS){
            jvtSF.at(iS) *= JvtSFAcc(*jet).at(iS);
          }
        }
      }
    } else {
      ANA_MSG_ERROR("Cannot access the decoration which stores the JVT SFs or jet is not hard-scatter.");
      return EL::StatusCode::FAILURE;
    }
  }

  setFloatVariable(weightName, jvtSF.at(0));
  if (doSys){
    if (systNamesJVT->size() > 1) {
      for (unsigned int iS=1; iS<systNamesJVT->size(); ++iS){
        std::string systInfoName = systNamesJVT->at(iS);
        setFloatVariable(weightName + "_" + systInfoName, jvtSF.at(iS));
      }
    } else {
      ANA_MSG_ERROR("Only nominal syst available in jvt systematics list by xAH! Check the decorator name!");
      return EL::StatusCode::FAILURE;
    }
  }
  return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo::addBtagSystWeights(std::string weightName) {
  // create vector of syst names
  std::vector< std::string >* systNamesBTag(nullptr);
  ANA_CHECK( HelperFunctions::retrieve(systNamesBTag, "BJetEfficiency_Algo_"+m_BtaggerName+"_"+m_BtaggerWP, 0, m_store));

  // start at second entry as we only want to add the systematic variation branches
  ANA_MSG_DEBUG("List B-tag systematics: ");
  for (unsigned int iS=1; iS<systNamesBTag->size(); ++iS){
    std::string systInfoName = systNamesBTag->at(iS);
    ANA_MSG_DEBUG("Systematic at " << iS << " is " << systInfoName);
    addFloatVariable(weightName + "_" + systInfoName, 1.0, true);
  }
  return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
// doSys decides if systematics are processed, weightName is the prefix used for the branches produced in this function
EL::StatusCode LJAlgo::computeEventBTagSF(const xAOD::JetContainer* jets, std::string weightName, bool doSys) {

  // Accessor to get b-tag SFs+systs
  const SG::AuxElement::ConstAccessor< std::vector<float> >  BTagSFAcc("BTag_SF_"+m_BtaggerName+"_"+m_BtaggerWP);
  // create vector of syst names
  std::vector< std::string >* systNamesBTag(nullptr);
  // initialise SF vector with one entry for now (nominal)
  std::vector< float > BTagSF(1,1.0);
  
  
  if (doSys) {
    ANA_CHECK( HelperFunctions::retrieve(systNamesBTag, "BJetEfficiency_Algo_"+m_BtaggerName+"_"+m_BtaggerWP, 0, m_store));
    // nominal SF and syst variations
    BTagSF.resize(systNamesBTag->size(),1.0);
  }

  for (const xAOD::Jet* jet : *jets){
    // the nominal SF is the first one in the vector
    if (BTagSFAcc.isAvailable( *jet )){
      
      BTagSF.at(0) *= BTagSFAcc(*jet).at(0);
      ANA_MSG_DEBUG( "Found Jet Btag SF nominal: " << BTagSF.at(0));
      
      if (doSys) {
        if (systNamesBTag->size() != BTagSFAcc(*jet).size()) {
          ANA_MSG_ERROR("List of systematic names from xAH does not agree with list of SF variations!");
          ANA_MSG_ERROR("Syst list size: " << systNamesBTag->size());
          ANA_MSG_ERROR("SF list size: " << BTagSFAcc(*jet).size());
        }
        
        // for systematics, start at the second entry as the first is nominal
        for (unsigned int iS=1; iS<systNamesBTag->size(); ++iS){
          BTagSF.at(iS) *= BTagSFAcc(*jet).at(iS);
        }
      }
    
    } else {
      ANA_MSG_ERROR("Cannot access the decoration which stores the b-tag SFs: " << "BTag_SF_" << m_BtaggerName << "_" << m_BtaggerWP);
      return EL::StatusCode::FAILURE;
    }
  }

  setFloatVariable(weightName, BTagSF.at(0));
  
  if (doSys){
    if (systNamesBTag->size() > 1) {
      for (unsigned int iS=1; iS<systNamesBTag->size(); ++iS){
        std::string systInfoName = systNamesBTag->at(iS);
        setFloatVariable(weightName + "_" + systInfoName, BTagSF.at(iS));
      }
    } else {
      ANA_MSG_ERROR("Only nominal syst available in b-tag systematics list by xAH! Check the decorator name!");
      return EL::StatusCode::FAILURE;
    }
  }
  return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
bool LJAlgo::isTrigMatched(const xAOD::IParticle* lepton, unsigned int runNumber) {

  std::map<std::string, char> isTrigMatchedMap;
  int year = get_year(runNumber);

  // recommendation for plateau cut is online threshold + 1 GeV
  if (lepton->type() == xAOD::Type::Electron) {
    isTrigMatchedMap = isTrigMatchedMapElAcc(*lepton);
    if (year== 2015) {
      if (isTrigMatchedMap["HLT_e24_lhmedium_L1EM20VH"] && lepton->pt()/m_units > 25.0)
        return true;
      else if (isTrigMatchedMap["HLT_e60_lhmedium"] && lepton->pt()/m_units > 61.0)
        return true;
      else if (isTrigMatchedMap["HLT_e120_lhloose"] && lepton->pt()/m_units > 121.0)
        return true;
      else
        return false;
    }
    else if (year == 2016 || year == 2017 || year == 2018) {
      if (isTrigMatchedMap["HLT_e26_lhtight_nod0_ivarloose"] && lepton->pt()/m_units > 27.0)
        return true;
      else if (isTrigMatchedMap["HLT_e60_lhmedium_nod0"] && lepton->pt()/m_units > 61.0)
        return true;
      else if (isTrigMatchedMap["HLT_e140_lhloose_nod0"] && lepton->pt()/m_units > 141.0)
        return true;
      else
        return false;
    }
    else if (year == 2022) {
      if (isTrigMatchedMap["HLT_e26_lhtight_ivarloose_L1EM22VHI"] && lepton->pt()/m_units > 27.0)
        return true;
      else if (isTrigMatchedMap["HLT_e60_lhmedium_L1EM22VHI"] && lepton->pt()/m_units > 61.0)
        return true;
      else if (isTrigMatchedMap["HLT_e140_lhloose_L1EM22VHI"] && lepton->pt()/m_units > 141.0)
        return true;
      else
        return false;
    }
    else if (year == 2023 || year == 2024) { // yfu add 2024
      if (isTrigMatchedMap["HLT_e26_lhtight_ivarloose_L1eEM26M"] && lepton->pt()/m_units > 27.0)
        return true;
      else if (isTrigMatchedMap["HLT_e60_lhmedium_L1eEM26M"] && lepton->pt()/m_units > 61.0)
        return true;
      else if (isTrigMatchedMap["HLT_e140_lhloose_L1eEM26M"] && lepton->pt()/m_units > 141.0)
        return true;
      else
        return false;
    }
    else {
      ANA_MSG_ERROR("Unkown year " << year << ", can't perform trigger matching!");
      return false;
    }
  }
  // recommendation for plateau cut is online threshold * 1.05 GeV
  else if (lepton->type() == xAOD::Type::Muon) {
    isTrigMatchedMap = isTrigMatchedMapMuAcc(*lepton);
    if ( year== 2015) {
      if (isTrigMatchedMap["HLT_mu20_iloose_L1MU15"] && lepton->pt()/m_units > 21.0)
        return true;
      else if (isTrigMatchedMap["HLT_mu40"] && lepton->pt()/m_units > 42.0)
        return true;
      else
        return false;
    }
    else if (year == 2016 || year == 2017 || year == 2018) {
      if (isTrigMatchedMap["HLT_mu26_ivarmedium"] && lepton->pt()/m_units > 27.3)
        return true;
      else if (isTrigMatchedMap["HLT_mu50"] && lepton->pt()/m_units > 52.5)
        return true;
      else
        return false;
    }
    else if (year == 2022 || year == 2023 || year == 2024) { // yfu add 2024
      if (isTrigMatchedMap["HLT_mu24_ivarmedium_L1MU14FCH"] && lepton->pt()/m_units > 25.2)
        return true;
      else if (isTrigMatchedMap["HLT_mu50_L1MU14FCH"] && lepton->pt()/m_units > 52.5)
        return true;
      else
        return false;
    }
    else {
      ANA_MSG_ERROR("Unkown year " << year << ", can't perform trigger matching!");
      return false;
    }
  }
  else {
    ANA_MSG_ERROR("Unkown type for trigger matching, implementation only for electrons and muons!");
    return false;
  }
}





// ---------------------------------------------------------------------------//
std::string LJAlgo::getTriggerAccName(unsigned int runNumber, bool isEl, bool isDiEl) {
  // Figure out correct accessor name for trigger systematics first
  int year = get_year(runNumber);
  std::string el_WP_trig_string, el_WP_ID_string, el_WP_iso_string, mu_WP_trig_string, mu_WP_reco_string;

  el_WP_ID_string   = m_elWP_ID;
  mu_WP_reco_string = m_muWP_Reco;


  // Trigger WP
  if (year == 2015 || year == 2016 || year == 2017 || year == 2018) {
    
    if (year == 2015) {
      mu_WP_trig_string = m_muWP_Trig15;
    } else {
      mu_WP_trig_string = m_muWP_Trig;
    }
    
    if (isDiEl) {
      el_WP_trig_string = m_dielWP_Trig;
      el_WP_iso_string  = m_dielWP_IsoTrig;
    } else {
      el_WP_trig_string = m_elWP_Trig;
      el_WP_iso_string  = m_elWP_Iso;
    }

  } else if (year == 2022 || year == 2023 || year == 2024) {

    // both the trigger expressions as well as the el iso WP for the SFs change (HighPtCaloOnly is not available in the Run3 el trigger maps)
    if (isDiEl) {
      el_WP_trig_string = m_dielWP_Trig;
    } else {
      el_WP_trig_string = m_elWP_Trig;
    }
    el_WP_iso_string  = m_elWP_IsoTrig;
    mu_WP_trig_string = m_muWP_Trig;
  
  } else {
    ANA_MSG_ERROR("Unkown year " << year << ", readout of trigger SFs only implemented for 2015-2018 & 2022-2023!");
    return "";
  }
  
  std::string Names_el = el_WP_trig_string+"_"+el_WP_ID_string+"_isol"+el_WP_iso_string;
  std::string Names_mu = mu_WP_trig_string+"_Reco"+mu_WP_reco_string;
  
  if (isEl) {
    return Names_el;
  } else {
    return Names_mu;
  }
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo::addSingleLeptonTrigSystWeights(unsigned int runNumber, std::string weightName) {
  ANA_MSG_DEBUG("Starting addSingleLeptonTrigSystWeights");

  // strings to pass to xAH to retrieve list of systematic names
  std::string systNames_mu = "MuonEfficiencyCorrector_TrigSyst_" + getTriggerAccName(runNumber, false, false);
  std::string systNames_el = "";
  
  if (!m_writeDiLepton) {
    systNames_el = "EleEffCorr_TrigSyst_" + getTriggerAccName(runNumber, true, false);
  }
  
  //// Get list of systematic variations ////
  std::vector< std::string >* el_sysVariationNames(nullptr);
  std::vector< std::string >* mu_sysVariationNames(nullptr);
  
  ANA_CHECK( HelperFunctions::retrieve(mu_sysVariationNames, systNames_mu, m_event, m_store, msg()) );
  
  if (!m_writeDiLepton) {
    ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store, msg()) );
  }
  if (!m_writeDiLepton){
    if ((el_sysVariationNames->size() < 2) || (mu_sysVariationNames->size() < 2)) {
      ANA_MSG_ERROR("Only nominal syst available in el/mu trigger systematics list by xAH! Check the decorator names!");
      return EL::StatusCode::FAILURE;
    }
  } else {
    if (mu_sysVariationNames->size() < 2) {
      ANA_MSG_ERROR("Only nominal syst available in mu trigger systematics list by xAH! Check the decorator names!");
      return EL::StatusCode::FAILURE;
    }
  }
  // start at second entry as we only want to add the systematic variation branches
  
  if (!m_writeDiLepton) {
    ANA_MSG_DEBUG("List electron trigger systematics: ");
    for (unsigned int iS=1; iS<el_sysVariationNames->size(); ++iS){
      std::string systInfoName = el_sysVariationNames->at(iS);
      ANA_MSG_DEBUG("Systematic at " << iS << " is " << systInfoName);
      addFloatVariable(weightName + "_" + systInfoName, 1.0, true);
    }
  }
  
  ANA_MSG_DEBUG("List muon trigger systematics: ");
  for (unsigned int iS=1; iS<mu_sysVariationNames->size(); ++iS){
    std::string systInfoName = mu_sysVariationNames->at(iS);
    ANA_MSG_DEBUG("Systematic at " << iS << " is " << systInfoName);
    addFloatVariable(weightName + "_" + systInfoName, 1.0, true);
  }

  ANA_MSG_DEBUG("Finished addSingleLeptonTrigSystWeights successfully");
  return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo::getSingleLepTrigSF(const xAOD::IParticle* lepton, unsigned int runNumber, std::string weightName, bool doSys) {

  const std::vector<const xAOD::IParticle*> leptons = {lepton};

  return getSingleLepTrigSF(leptons, runNumber, weightName, doSys);

}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo::getSingleLepTrigSF(const std::vector<const xAOD::IParticle*> leptons, unsigned int runNumber, std::string weightName, bool doSys, bool doElectrons) {
  // dummy SF of 1 is added to the branches if something goes wrong
  bool do_dummy_sf = false;

  // return a SF of 1 for data
  if (!m_isMC)
    do_dummy_sf = true;

  int trigmatched_leptons = 0;

  // the name of the decorator set by xAH depends on the reco and isolation WPs hence we don't define it in ConstAccessors.h for now
  SG::AuxElement::ConstAccessor< std::vector<float> > muonTrigSFAcc("MuTrigEff_SF_syst_" + getTriggerAccName(runNumber, false, false));
  SG::AuxElement::ConstAccessor< std::vector<float> > muonTrigEffAcc("MuTrigMCEff_syst_" + getTriggerAccName(runNumber, false, false));
  SG::AuxElement::ConstAccessor< std::vector<float> > elecTrigSFAcc("ElTrigEff_SF_syst_" + getTriggerAccName(runNumber, true, false));
  SG::AuxElement::ConstAccessor< std::vector<float> > elecTrigEffAcc("ElTrigMCEff_syst_" + getTriggerAccName(runNumber, true, false));


  // strings to pass to xAH to retrieve list of systematic names
  std::string systNames_el;
  if (doElectrons) systNames_el = "EleEffCorr_TrigSyst_" + getTriggerAccName(runNumber, true, false);
  std::string systNames_mu = "MuonEfficiencyCorrector_TrigSyst_" + getTriggerAccName(runNumber, false, false);

  //// Get list of systematic variations ////
  std::vector< std::string >* el_sysVariationNames(nullptr);
  std::vector< std::string >* mu_sysVariationNames(nullptr);

  // initialise SF vector with one entry for now (nominal)
  std::vector< float > total_ineff(1,1.0);
  std::vector< float > total_ineff_scaled(1,1.0);
  std::vector< std::string > all_sysVariationNames = {};
  if (doSys) {
    if (doElectrons) {
      ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store) );
    }
    ANA_CHECK( HelperFunctions::retrieve(mu_sysVariationNames, systNames_mu, m_event, m_store) );

    if (doElectrons) {
      if ((el_sysVariationNames->size() < 2) || (mu_sysVariationNames->size() < 2)) {
        ANA_MSG_ERROR("Only nominal syst available in el/mu trigger systematics list by xAH! Check the decorator names!");
        return EL::StatusCode::FAILURE;
      }
    } else {
      if (mu_sysVariationNames->size() < 2) {
        ANA_MSG_ERROR("Only nominal syst available in el/mu trigger systematics list by xAH! Check the decorator names!");
        return EL::StatusCode::FAILURE;
      }
    }

    // nominal Eff/SF plus syst variations, don't double count nominal from both string vectors
    int new_size = mu_sysVariationNames->size()-1;
    if (doElectrons) new_size += el_sysVariationNames->size();
    total_ineff.resize(new_size,1.0);
    total_ineff_scaled.resize(new_size,1.0);


    // fill one vector with all the systematics names (without double counting nominal!)
    if (doElectrons) {
      for (unsigned int iS=0; iS<el_sysVariationNames->size(); ++iS) {
        std::string systInfoName = el_sysVariationNames->at(iS);
        all_sysVariationNames.push_back(systInfoName);
      }
    }
    for (unsigned int iS=1; iS<mu_sysVariationNames->size(); ++iS) {
      std::string systInfoName = mu_sysVariationNames->at(iS);
      all_sysVariationNames.push_back(systInfoName);
    }
  }
  
  // loop over all leptons supplied - note that the following implementation is only valid if the vector contains leptons of the same type
  for (const xAOD::IParticle* lepton : leptons){
    
    // consider only trigger-matched leptons
    if (!isTrigMatched(lepton, runNumber)) continue;
    trigmatched_leptons = trigmatched_leptons + 1;

    std::vector<float> trigSFs;
    std::vector<float> trigEffs;

    // for electrons the SF expression is the same for 2015-2018 but different for 2022
    if (lepton->type() == xAOD::Type::Electron and doElectrons) {
      if (!elecTrigSFAcc.isAvailable(*lepton)) {
        ANA_MSG_WARNING("Cannot access the decoration which stores the electron trigger SFs. Did you change the electron Reco or Iso WP in LJConfig.py? Returning a dummy SF of 1 ...");
        do_dummy_sf = true;
        break;
      }
      trigSFs = elecTrigSFAcc(*lepton);
      trigEffs = elecTrigEffAcc(*lepton);
      if (trigSFs.size() == 0) {
        ANA_MSG_WARNING("Size of vector with electron trigger SFs is 0! Returning a dummy SF of 1 ...");
        do_dummy_sf = true;
        break;
      }
    } else if (lepton->type() == xAOD::Type::Muon) {
      if (!muonTrigSFAcc.isAvailable(*lepton)) {
        ANA_MSG_WARNING("Cannot access the decoration which stores the muon trigger SFs. Did you change the muon Reco or Iso WP in LJConfig.py? Returning a dummy SF of 1 ...");
        do_dummy_sf = true;
        break;
      }
      trigSFs = muonTrigSFAcc(*lepton);
      trigEffs = muonTrigEffAcc(*lepton);
      // note that the size of the vector here is actually 3 due to some awkward implementation
      // within the MuonEfficiencyCorrector, but all three values are the same (we could adjust the setup in our LJ config though)
      // this duplication carries on to the systematics: the nominal + 4 systematic variations are repeated twice so one gets a vector of size 15 ...
      // But if we only loop over the systematic name list, we ignore the duplicates afterwards
      if (trigSFs.size() == 0) {
        ANA_MSG_WARNING("Size of vector with muon trigger SFs is 0! Returning a dummy SF of 1 ...");
        do_dummy_sf = true;
        break;
      }
    } else {
      ANA_MSG_ERROR("Unkown type to retrieve trigger SFs, implementation only for electrons and muons! Returning a dummy SF of 1.0 ...");
      do_dummy_sf = true;
      break;
    }

    // if something went wrong beforehand, don't do this calculation
    if (!do_dummy_sf) {
      ANA_MSG_DEBUG("Single-lepton trigger calucation: considering lepton with trigger efficiency of " << trigEffs[0] << " and SF of " << trigSFs[0]);
      total_ineff[0] *= (1 - trigEffs[0]);
      total_ineff_scaled[0] *= (1 - trigSFs[0] * trigEffs[0]);
      // Now calculate the systematic variations
      // Note that we start filling up the total SF vectors with the electron systematics and THEN the muon systematics
      if (doSys) {
        if (lepton->type() == xAOD::Type::Electron and doElectrons) {
          for (unsigned int iS=1; iS<el_sysVariationNames->size(); ++iS){
            total_ineff[iS] *= (1 - trigEffs[iS]);
            total_ineff_scaled[iS] *= (1 - trigSFs[iS] * trigEffs[iS]);
          }
        } else if (lepton->type() == xAOD::Type::Muon) {
          for (unsigned int iS=1; iS<mu_sysVariationNames->size(); ++iS){
            int index = iS-1;
            if (doElectrons){
              index += el_sysVariationNames->size();
            }
            total_ineff[index] *= (1 - trigEffs[iS]);
            total_ineff_scaled[index] *= (1 - trigSFs[iS] * trigEffs[iS]);
          }
        }
      }
    }
  } // end loop over leptons

  
  if (trigmatched_leptons < 1) {
    ANA_MSG_DEBUG("No leptons trigger matched in this event! Returning a dummy SF of 1 ...");
    do_dummy_sf = true;
  }
  
  // check if event had at least one trigger matched lepton
  if (!do_dummy_sf) {
    float final_SF;
    if (total_ineff[0] == 1) {
      ANA_MSG_DEBUG("Final trigger efficiency is zero! SF is set to dummy value 1...");
      setFloatVariable(weightName, 1);
    } else {
      final_SF = (1 - total_ineff_scaled[0]) / (1 - total_ineff[0]);
      ANA_MSG_DEBUG("Final single-lepton trigger SF: " << final_SF);
      setFloatVariable(weightName, final_SF);
    }
    if (doSys) {
      for (unsigned int iS=1; iS<all_sysVariationNames.size(); ++iS){
        std::string systInfoName = all_sysVariationNames.at(iS);
        if (total_ineff[iS] == 1) {
          ANA_MSG_DEBUG("Final trigger efficiency is zero! SF of syst" << systInfoName << " is set to dummy value 1...");
          setFloatVariable(weightName + "_" + systInfoName, 1);
        } else {
          float final_SF_syst = (1 - total_ineff_scaled[iS]) / (1 - total_ineff[iS]);
          ANA_MSG_DEBUG("Final single-lepton trigger SF for systematic " << systInfoName << ": " << final_SF_syst);
          setFloatVariable(weightName + "_" + systInfoName, final_SF_syst);
        }
      }
    }
  } else { // something went wrong, just fill the branches with 1
    setFloatVariable(weightName, 1);
    if (doSys) {
      for (unsigned int iS=1; iS<all_sysVariationNames.size(); ++iS){
        std::string systInfoName = all_sysVariationNames.at(iS);
        setFloatVariable(weightName + "_" + systInfoName, 1);
      }
    }
  }
  return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
int LJAlgo::get_year(unsigned int runNumber) {
  if (runNumber < 293572)
    return 2015;
  else if (runNumber < 320000)
    return 2016;
  else if (runNumber < 348885)
    return 2017;
  else if (runNumber < 428648)
    return 2018;
  else if (runNumber < 450000) 
    return 2022;
  else if (runNumber < 473235)
    return 2023;
  else
    return 2024;
}





// ---------------------------------------------------------------------------//
void LJAlgo::addLeptonVariables(std::string prefix) {
  addIntVariable(prefix+"_"+"isEl", -999);
  addFloatVariable(prefix+"_"+"m", -999);
  addFloatVariable(prefix+"_"+"E", -999);
  addFloatVariable(prefix+"_"+"pt", -999);
  addFloatVariable(prefix+"_"+"phi", -999);
  addFloatVariable(prefix+"_"+"eta", -999);
  addFloatVariable(prefix+"_"+"caloeta", -999);
  addFloatVariable(prefix+"_"+"charge", -999);
  addIntVariable(prefix+"_"+"truthType", -999);
  addIntVariable(prefix+"_"+"truthOrigin", -999);
  addIntVariable(prefix+"_"+"IFFType", -999);
  addBoolVariable(prefix+"_"+"isPromptIFF", false);
  addBoolVariable(prefix+"_"+"isIsoHighPtCaloOnly", false, true);
  addBoolVariable(prefix+"_"+"isIsoLoose_VarRad", false, true);
  addBoolVariable(prefix+"_"+"isIsoTight_VarRad", false, true);
  addBoolVariable(prefix+"_"+"isIDLoose", false, true);
  addBoolVariable(prefix+"_"+"isIDMedium", false, true);
  addBoolVariable(prefix+"_"+"isIDTight", false, true);

  //yfu add individual scale factors
  addFloatVariable(prefix+"_"+"RecoWeight", -999);
  addFloatVariable(prefix+"_"+"IsoHighPtCaloOnlyWeight", -999);
  addFloatVariable(prefix+"_"+"IsoLoose_VarRadWeight", -999);
  addFloatVariable(prefix+"_"+"IsoTight_VarRadWeight", -999);
  addFloatVariable(prefix+"_"+"IDLooseWeight", -999);
  addFloatVariable(prefix+"_"+"IDMediumWeight", -999);
  addFloatVariable(prefix+"_"+"IDTightWeight", -999);

  addIntVariable(prefix+"_"+"ambiguityType", -999, true);
  addIntVariable(prefix+"_"+"addAmbiguity", -999, true);
  addFloatVariable(prefix+"_"+"d0sig", -999);
  addFloatVariable(prefix+"_"+"z0sinTheta", -999);
  addFloatVariable(prefix+"_"+"d0", -999);
  addFloatVariable(prefix+"_"+"z0", -999);
  addIntVariable(prefix+"_"+"isSig", -999);
  addIntVariable(prefix+"_"+"isIso", -999);
  addBoolVariable(prefix+"_"+"isMatched", false);
  addBoolVariable(prefix+"_"+"isTruthMatched", false);//yfu combine jetfake
  addFloatVariable(prefix+"_"+"truthE", -999);
  addFloatVariable(prefix+"_"+"truthpt", -999);
  addFloatVariable(prefix+"_"+"truthphi", -999);
  addFloatVariable(prefix+"_"+"trutheta", -999);
  addIntVariable(prefix+"_"+"truthpdgid", 0);
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo::fillLeptonVariables(std::string prefix, const xAOD::IParticle &lepton) {
  setFloatVariable(prefix+"_"+"m"  , lepton.m()/m_units);
  setFloatVariable(prefix+"_"+"E"  , lepton.e()/m_units);
  setFloatVariable(prefix+"_"+"pt" , lepton.pt()/m_units);
  setFloatVariable(prefix+"_"+"phi", lepton.phi());
  setFloatVariable(prefix+"_"+"eta", lepton.eta());
  
  if (chargeAcc.isAvailable( lepton )) {
    setFloatVariable(prefix+"_"+"charge", chargeAcc( lepton ));
  }
  
  if (truthTypeAcc.isAvailable( lepton )) {
    setIntVariable(prefix+"_"+"truthType", truthTypeAcc( lepton ));
  }
  
  if (truthOriginAcc.isAvailable( lepton )) {
    setIntVariable(prefix+"_"+"truthOrigin", truthOriginAcc( lepton ));
  }
  
  if (d0SigAcc.isAvailable( lepton )) {
    setFloatVariable(prefix+"_"+"d0sig", d0SigAcc( lepton ));
  }
  
  if (z0sinthetaAcc.isAvailable( lepton )) {
    setFloatVariable(prefix+"_"+"z0sinTheta", z0sinthetaAcc( lepton ));
  }
  
  if (passSelDecor.isAvailable( lepton )) {
    setIntVariable(prefix+"_"+"isSig", passSelDecor( lepton ));
  }
  
  // retrieve categorization from IFF
  // see https://gitlab.cern.ch/atlas/athena/-/blob/main/PhysicsAnalysis/AnalysisCommon/TruthClassification/README.md
  unsigned int IFFtype(0);
  
  if (m_isMC) {
    ANA_CHECK(m_truthClassificationTool->classify(lepton, IFFtype));
    setIntVariable(prefix+"_"+"IFFType", IFFtype);
  }

  if (lepton.type() == xAOD::Type::Electron) {
    
    setIntVariable(prefix+"_"+"isEl", 1);
    
    if (isoDecorWP_HighPtCaloOnly.isAvailable( lepton )) {
      setIntVariable(prefix+"_"+"isIso", isoDecorWP_HighPtCaloOnly( lepton ));
    }
    
    const xAOD::Electron* electron = dynamic_cast<const xAOD::Electron*>(&lepton);
    const xAOD::TrackParticle* tp_lep = electron->trackParticle();
    float calo_eta   = ( electron->caloCluster() ) ? electron->caloCluster()->etaBE(2) : -999.0;
    
    
    setFloatVariable(prefix+"_"+"caloeta", calo_eta);
    if (tp_lep) {
      setFloatVariable(prefix+"_"+"d0", tp_lep->d0());
    }
    if (tp_lep) {
      setFloatVariable(prefix+"_"+"z0", tp_lep->z0());
    }
    
    setBoolVariable(prefix+"_"+"isPromptIFF", (!m_isMC || IFFtype == 2) ? true : false);
    
    // write additional information only into nominal tree
    if (m_currentSyst == "") {
      if (isoDecorWP_Loose_VarRad.isAvailable( lepton )) {
        setBoolVariable(prefix+"_"+"isIsoLoose_VarRad", isoDecorWP_Loose_VarRad( lepton ));
      }
      
      if (isoDecorWP_Tight_VarRad.isAvailable( lepton )) {
        setBoolVariable(prefix+"_"+"isIsoTight_VarRad", isoDecorWP_Tight_VarRad( lepton ));
      }
      
      if (isoDecorWP_HighPtCaloOnly.isAvailable( lepton )) {
        setBoolVariable(prefix+"_"+"isIsoHighPtCaloOnly", isoDecorWP_HighPtCaloOnly( lepton ));
      }
      
      if (looseIDAcc.isAvailable( lepton )) {
        setBoolVariable(prefix+"_"+"isIDLoose", looseIDAcc( lepton ));
      }
      
      if (mediumIDAcc.isAvailable( lepton )) {
        setBoolVariable(prefix+"_"+"isIDMedium", mediumIDAcc( lepton ));
      }
      
      if (tightIDAcc.isAvailable( lepton )) {
        setBoolVariable(prefix+"_"+"isIDTight", tightIDAcc( lepton ));
      }

      // yfu add individual scale factors
      if (m_isMC) {
        float RecoWeight = -999.0;
        float IsoHighPtCaloOnlyWeight = -999.0;
        float IsoLoose_VarRadWeight = -999.0;
        float IsoTight_VarRadWeight = -999.0;
        float IDLooseWeight = -999.0;
        float IDMediumWeight = -999.0;
        float IDTightWeight = -999.0;

        std::string decor_Reco = "ElRecoEff_SF_syst_Reconstruction";
        std::string decor_Iso_HighPtCaloOnly = "ElIsoEff_SF_syst_Tight_isolHighPtCaloOnly";
        std::string decor_Iso_Loose_VarRad = "ElIsoEff_SF_syst_LooseBLayer_isolLoose_VarRad";
        std::string decor_Iso_Tight_VarRad = "ElIsoEff_SF_syst_Tight_isolTight_VarRad";
        std::string decor_ID_Loose = "ElPIDEff_SF_syst_LooseBLayer";
        std::string decor_ID_Medium = "ElPIDEff_SF_syst_Medium";
        std::string decor_ID_Tight = "ElPIDEff_SF_syst_Tight";

        std::vector < float > thisLepSF = {-999.0};

	std::function<EL::StatusCode(std::string, std::vector<float> &)> GetIndividualSFs = [&](std::string decor_name_SF, std::vector<float> &sf){
          if (passSelDecor.isAvailable( *electron )){
            if (!passSelDecor( *electron )) return EL::StatusCode::SUCCESS;
          }

          if ( electron->isAvailable< std::vector< float > >( decor_name_SF ) ) {
            sf  = electron->auxdecor< std::vector< float > >( decor_name_SF );
            return EL::StatusCode::SUCCESS;
          } else {
            ANA_MSG_ERROR("Can't find SF working point "<< decor_name_SF.c_str());
            return EL::StatusCode::FAILURE;
          }
        };

        EL::StatusCode status;

        status = GetIndividualSFs(decor_Reco, thisLepSF);
        if(status == EL::StatusCode::SUCCESS) RecoWeight = thisLepSF.at(0);
        else return status;

        status = GetIndividualSFs(decor_Iso_HighPtCaloOnly, thisLepSF);
        if(status == EL::StatusCode::SUCCESS) IsoHighPtCaloOnlyWeight = thisLepSF.at(0);
        else return status;

        status = GetIndividualSFs(decor_Iso_Loose_VarRad, thisLepSF);
        if(status == EL::StatusCode::SUCCESS) IsoLoose_VarRadWeight = thisLepSF.at(0);
        else return status;

        status = GetIndividualSFs(decor_Iso_Tight_VarRad, thisLepSF);
        if(status == EL::StatusCode::SUCCESS) IsoTight_VarRadWeight = thisLepSF.at(0);
        else return status;

        status = GetIndividualSFs(decor_ID_Loose, thisLepSF);
        if(status == EL::StatusCode::SUCCESS) IDLooseWeight = thisLepSF.at(0);
        else return status;

        status = GetIndividualSFs(decor_ID_Medium, thisLepSF);
        if(status == EL::StatusCode::SUCCESS) IDMediumWeight = thisLepSF.at(0);
        else return status;

        status = GetIndividualSFs(decor_ID_Tight, thisLepSF);
        if(status == EL::StatusCode::SUCCESS) IDTightWeight = thisLepSF.at(0);
        else return status;

        setFloatVariable(prefix+"_"+"RecoWeight", RecoWeight);
        setFloatVariable(prefix+"_"+"IsoHighPtCaloOnlyWeight", IsoHighPtCaloOnlyWeight);
        setFloatVariable(prefix+"_"+"IsoLoose_VarRadWeight", IsoLoose_VarRadWeight);
        setFloatVariable(prefix+"_"+"IsoTight_VarRadWeight", IsoTight_VarRadWeight);
        setFloatVariable(prefix+"_"+"IDLooseWeight", IDLooseWeight);
        setFloatVariable(prefix+"_"+"IDMediumWeight", IDMediumWeight);
        setFloatVariable(prefix+"_"+"IDTightWeight", IDTightWeight);
      }
      else {
        setFloatVariable(prefix+"_"+"RecoWeight", 1.0);
        setFloatVariable(prefix+"_"+"IsoHighPtCaloOnlyWeight", 1.0);
        setFloatVariable(prefix+"_"+"IsoLoose_VarRadWeight", 1.0);
        setFloatVariable(prefix+"_"+"IsoTight_VarRadWeight", 1.0);
        setFloatVariable(prefix+"_"+"IDLooseWeight", 1.0);
        setFloatVariable(prefix+"_"+"IDMediumWeight", 1.0);
        setFloatVariable(prefix+"_"+"IDTightWeight", 1.0);
      }

      if (ambiguityTypeAcc.isAvailable( lepton )) {
        setIntVariable(prefix+"_"+"ambiguityType", ambiguityTypeAcc( lepton ));
      }
      
      if (addAmbiguityAcc.isAvailable( lepton )) {
        setIntVariable(prefix+"_"+"addAmbiguity", addAmbiguityAcc( lepton ));
      }
    }

  }
  
  
  
  if (lepton.type() == xAOD::Type::Muon) {
    setIntVariable(prefix+"_"+"isEl", 0);
    
    if (isoDecorWP_PflowTight_VarRad.isAvailable( lepton )) {
      setIntVariable(prefix+"_"+"isIso", isoDecorWP_PflowTight_VarRad( lepton ));
    }
    
    const xAOD::Muon* muon = dynamic_cast<const xAOD::Muon*>(&lepton);
    const xAOD::TrackParticle* tp_lep = muon->primaryTrackParticle();
    
    if (tp_lep) {
      setFloatVariable(prefix+"_"+"d0", tp_lep->d0());
    }
    if (tp_lep) {
      setFloatVariable(prefix+"_"+"z0", tp_lep->z0());
    }
    setBoolVariable(prefix+"_"+"isPromptIFF", (!m_isMC || IFFtype == 4) ? true : false);
  }
  
  
  
  const xAOD::TruthParticle* truth_lep = 0;
  
  if (m_isMC){
    truth_lep = getTruthMatchedParticle( lepton );
  
    if (truth_lep) {
      setBoolVariable(prefix+"_"+"isMatched", true);
      setBoolVariable(prefix+"_"+"isTruthMatched", true);//yfu combine jetfake
      setFloatVariable(prefix+"_"+"truthE", truth_lep->e()/m_units);
      setFloatVariable(prefix+"_"+"truthpt", truth_lep->pt()/m_units);
      setFloatVariable(prefix+"_"+"truthphi", truth_lep->phi());
      setFloatVariable(prefix+"_"+"trutheta", truth_lep->eta());
      setIntVariable(prefix+"_"+"truthpdgid", truth_lep->pdgId());
    }
  }

  return EL::StatusCode::SUCCESS;
}





// ---------------------------------------------------------------------------//
bool LJAlgo::isTrigMatched_diLep(const xAOD::EventInfo &eventInfo, const xAOD::IParticle &lepton1, const xAOD::IParticle &lepton2, unsigned int runNumber) {
  

  
  std::map<std::string, char> isTrigMatchedMap1;
  std::map<std::string, char> isTrigMatchedMap2;
  std::multimap< std::string, std::pair< std::pair<unsigned int,unsigned int>, char > > diElectronTrigMatchPairMap;
  
  int year = get_year(runNumber);
  
  
  
  // recommendation for plateau cut is online threshold + 1 GeV
  if (lepton1.type() == xAOD::Type::Electron) {
    
    diElectronTrigMatchPairMap = diElectronTrigMatchPairMapAcc(eventInfo);
    
    std::pair<unsigned int,unsigned int> targetPair = {0, 1};
    
    if (year == 2015) {
      bool diElIsMatched = checkDiElIsMatched(diElectronTrigMatchPairMap, targetPair, "HLT_2e12_lhloose_L12EM10VH");
      
      if ( diElIsMatched && lepton1.pt()/m_units > 13.0 && lepton2.pt()/m_units > 13.0 )
        return true;
      else
        return false;
    }
    else if (year == 2016) {
      bool diElIsMatched = checkDiElIsMatched(diElectronTrigMatchPairMap, targetPair, "HLT_2e17_lhvloose_nod0");
      
      if ( diElIsMatched && lepton1.pt()/m_units > 18.0 && lepton2.pt()/m_units > 18.0 )
        return true;
      else
        return false;
    }
    else if (year == 2017 || year == 2018) {
      bool diElIsMatched = checkDiElIsMatched(diElectronTrigMatchPairMap, targetPair, "HLT_2e24_lhvloose_nod0");
      
      if ( diElIsMatched && lepton1.pt()/m_units > 25.0 && lepton2.pt()/m_units > 25.0 )
        return true;
      else
        return false;
    }
    else if (year == 2022) {
      bool diElIsMatched = checkDiElIsMatched(diElectronTrigMatchPairMap, targetPair, "HLT_2e24_lhvloose_L12EM20VH");
      
      if ( diElIsMatched && lepton1.pt()/m_units > 25.0 && lepton2.pt()/m_units > 25.0 )
        return true;
      else
        return false;
    }
    else if (year == 2023 || year == 2024) { // yfu add 2024
      bool diElIsMatched = checkDiElIsMatched(diElectronTrigMatchPairMap, targetPair, "HLT_2e24_lhvloose_L12eEM24L");
      
      if ( diElIsMatched && lepton1.pt()/m_units > 25.0 && lepton2.pt()/m_units > 25.0 )
        return true;
      else
        return false;
    }
    else {
      ANA_MSG_ERROR("Unkown year " << year << ", can't perform trigger matching!");
      return false;
    }
    
  }
  // recommendation for plateau cut is online threshold * 1.05 GeV
  else if (lepton1.type() == xAOD::Type::Muon) {
    isTrigMatchedMap1 = isTrigMatchedMapMuAcc(lepton1);
    isTrigMatchedMap2 = isTrigMatchedMapMuAcc(lepton2);
    
    
    if ( year== 2015) {
      if ( (isTrigMatchedMap1["HLT_mu20_iloose_L1MU15"] && lepton1.pt()/m_units > 21.0) || (isTrigMatchedMap2["HLT_mu20_iloose_L1MU15"] && lepton2.pt()/m_units > 21.0) )
        return true;
      else if ( (isTrigMatchedMap1["HLT_mu50"] && lepton1.pt()/m_units > 52.5) || (isTrigMatchedMap2["HLT_mu50"] && lepton2.pt()/m_units > 52.5) )
        return true;
      else
        return false;
    }
    else if (year == 2016 || year == 2017 || year == 2018) {
      if ( (isTrigMatchedMap1["HLT_mu26_ivarmedium"] && lepton1.pt()/m_units > 27.3) || (isTrigMatchedMap2["HLT_mu26_ivarmedium"] && lepton2.pt()/m_units > 27.3) )
        return true;
      else if ( (isTrigMatchedMap1["HLT_mu50"] && lepton1.pt()/m_units > 52.5) || (isTrigMatchedMap2["HLT_mu50"] && lepton2.pt()/m_units > 52.5) )
        return true;
      else
        return false;
    }
    else if (year == 2022 || year == 2023 || year == 2024) { // yfu add 2024
      if ( (isTrigMatchedMap1["HLT_mu24_ivarmedium_L1MU14FCH"] && lepton1.pt()/m_units > 25.2) || (isTrigMatchedMap2["HLT_mu24_ivarmedium_L1MU14FCH"] && lepton2.pt()/m_units > 25.2) )
        return true;
      else if ( (isTrigMatchedMap1["HLT_mu50_L1MU14FCH"] && lepton1.pt()/m_units > 52.5) || (isTrigMatchedMap2["HLT_mu50_L1MU14FCH"] && lepton2.pt()/m_units > 52.5) )
        return true;
      else
        return false;
    }
    else {
      ANA_MSG_ERROR("Unkown year " << year << ", can't perform trigger matching!");
      return false;
    }
  }

  else {
    ANA_MSG_ERROR("Unkown type for trigger matching, implementation only for electrons and muons!");
    return false;
  }
}





// ---------------------------------------------------------------------------//
bool LJAlgo::checkDiElIsMatched(const std::multimap< std::string, std::pair< std::pair<unsigned int,unsigned int>, char > > & diElTrigMatchPairMap, const std::pair<unsigned int,unsigned int>& targetPair, const std::string& targetKey) {
  auto range = diElTrigMatchPairMap.equal_range(targetKey);
  for (auto it = range.first; it != range.second; ++it) {
    if (it->second.first == targetPair) {
      return (it->second.second == 1);
    }
  }
  return false;
}





// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo::addDiElectronTrigSystWeights(unsigned int runNumber, std::string weightName) {
  ANA_MSG_DEBUG("Starting addDiElectronTrigSystWeights");

  // string to pass to xAH to retrieve list of diel trig systematic names
  std::string systNames_el = "EleEffCorr_TrigSyst_" + getTriggerAccName(runNumber, true, true);
  std::string systNames_mu = "MuonEfficiencyCorrector_TrigSyst_" + getTriggerAccName(runNumber, false, false);

  //// Get list of systematic variations ////
  std::vector< std::string >* el_sysVariationNames(nullptr);
  std::vector< std::string >* mu_sysVariationNames(nullptr);

  ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store) );
  ANA_CHECK( HelperFunctions::retrieve(mu_sysVariationNames, systNames_mu, m_event, m_store) );

  if ((el_sysVariationNames->size() < 2) || (mu_sysVariationNames->size() < 2)) {
    ANA_MSG_ERROR("Only nominal syst available in di-el/mu trigger systematics list by xAH! Check the decorator names!");
    return EL::StatusCode::FAILURE;
  }
  // start at second entry as we only want to add the systematic variation branches
  ANA_MSG_DEBUG("List electron trigger systematics: ");
  for (unsigned int iS=1; iS<el_sysVariationNames->size(); ++iS){
    std::string systInfoName = el_sysVariationNames->at(iS);
    ANA_MSG_DEBUG("Systematic at " << iS << " is " << systInfoName);
    addFloatVariable(weightName + "_" + systInfoName, 1.0, true);
  }
  // Need to add the muon trigger systs to the dilepton trigger weights!
  ANA_MSG_DEBUG("List muon trigger systematics: ");
  for (unsigned int iS=1; iS<mu_sysVariationNames->size(); ++iS){
    std::string systInfoName = mu_sysVariationNames->at(iS);
    ANA_MSG_DEBUG("Systematic at " << iS << " is " << systInfoName);
    addFloatVariable(weightName + "_" + systInfoName, 1.0, true);
  }

  ANA_MSG_DEBUG("Finished addDiElectronTrigSystWeights successfully");
  return EL::StatusCode::SUCCESS;
}









// ---------------------------------------------------------------------------//
EL::StatusCode LJAlgo::getElectronTrigSFTwoLeptons(const xAOD::EventInfo* eventInfo, const std::vector<const xAOD::IParticle*> leptons, unsigned int runNumber, std::string weightName, bool doSys) {

  // dummy SF of 1 is added to the branches if something goes wrong
  bool do_dummy_sf = false;

  // return a SF of 1 for data
  if (!m_isMC) {
    do_dummy_sf = true;
  }
  
  // for electrons the SF expression is the same for 2015-2018 but different for 2022
  // the name of the decorator set by xAH depends on the reco and isolation WPs hence we don't define it in ConstAccessors.h for now
  std::string acc_name = getTriggerAccName(runNumber, true, true);
  SG::AuxElement::ConstAccessor< std::vector<float> > diElTrigEffSFAcc("ElTrigEff_SF_syst_" + acc_name);
  SG::AuxElement::ConstAccessor< std::vector<float> > diElTrigEffAcc  ("ElTrigMCEff_syst_"  + acc_name);
  
  ANA_MSG_DEBUG("Accessor name = " << acc_name);


  // string to pass to xAH to retrieve list of diel trig systematic names
  std::string systNames_el = "EleEffCorr_TrigSyst_" + acc_name;

  //// Get list of systematic variations ////
  std::vector< std::string >* el_sysVariationNames(nullptr);

  
  
  // initialise SF vector with one entry for now (nominal)
  std::vector< float > total_ineff       (1, 1.0);
  std::vector< float > total_ineff_scaled(1, 1.0);
  
  if (doSys) {
    ANA_CHECK( HelperFunctions::retrieve(el_sysVariationNames, systNames_el, m_event, m_store) );
  
    if (el_sysVariationNames->size() < 2) {
      ANA_MSG_ERROR("Only nominal syst available in di-el trigger systematics list by xAH! Check the decorator names!");
      return EL::StatusCode::FAILURE;
    }
  
    // nominal Eff/SF plus syst variations
    total_ineff       .resize(el_sysVariationNames->size(),1.0);
    total_ineff_scaled.resize(el_sysVariationNames->size(),1.0);
  }

  
  
  // consider only trigger-matched leptons
  if (isTrigMatched_diLep(*eventInfo, *leptons[0], *leptons[1], runNumber)) {

    // loop over all leptons supplied
    // - note that the following implementation is only valid if the vector contains leptons of the same type
    // - note that the following implementation is implemented for symmetric di-e triggers, applied to exactly 2 leptons, only.
    for (const xAOD::IParticle* lepton : leptons){
      if (!(lepton->type() == xAOD::Type::Electron)) {
        ANA_MSG_ERROR("Di-electron trigger SFs can only be calculated using electrons! Objects of non-electron type given, failing...");
        return EL::StatusCode::SUCCESS;
      }
      
      std::vector<float> trigSFs;
      std::vector<float> trigEffs;

      if (!diElTrigEffSFAcc.isAvailable(*lepton)) {
        ANA_MSG_WARNING("Cannot access the decoration which stores the di-electron trigger SFs. Did you change the electron Reco or Iso WP in LJConfig.py? Returning a dummy SF of 1 ...");
        do_dummy_sf = true;
        break;
      }
  
      if (!diElTrigEffAcc.isAvailable(*lepton)) {
        ANA_MSG_WARNING("Cannot access the decoration which stores the di-electron trigger Efficiencies. Did you change the electron Reco or Iso WP in LJConfig.py? Returning a dummy SF of 1 ...");
        do_dummy_sf = true;
        break;
      }
  
      trigSFs = diElTrigEffSFAcc(*lepton);
      trigEffs = diElTrigEffAcc(*lepton);
  
      if (trigSFs.size() == 0) {
        ANA_MSG_WARNING("Size of vector with di-electron trigger SFs is 0! Returning a dummy SF of 1 ...");
        do_dummy_sf = true;
        break;
      }
      
      ANA_MSG_DEBUG("Di-electron trigger calculation: considering electron with trigger efficiency of " << trigEffs[0] << " and SF of " << trigSFs[0]);
      
      total_ineff[0]        *= (1 - trigEffs[0]);
      total_ineff_scaled[0] *= (1 - trigSFs[0] * trigEffs[0]);
  
      // Now calculate the systematics, start at second entry as nominal is already done
      if (doSys) {
        for (unsigned int iS=1; iS<el_sysVariationNames->size(); ++iS){
          total_ineff[iS]        *= (1 - trigEffs[iS]);
          total_ineff_scaled[iS] *= (1 - trigSFs[iS] * trigEffs[iS]);
        }
      }
    } // end loop over leptons

  
    if (!do_dummy_sf) {
      
      float final_SF;
      
      if (total_ineff[0] == 1) {
        ANA_MSG_DEBUG("Final trigger efficiency is zero! SF is set to dummy value 1...");
        setFloatVariable(weightName, 1);
      } else {
        final_SF = (1 - total_ineff_scaled[0]) / (1 - total_ineff[0]);
        ANA_MSG_DEBUG("Final di-electron trigger SF: " << final_SF);
        setFloatVariable(weightName, final_SF);
      }
      
      if (doSys) {
        for (unsigned int iS=1; iS<el_sysVariationNames->size(); ++iS){
          std::string systInfoName = el_sysVariationNames->at(iS);
          
          if (total_ineff[iS] == 1) {
            ANA_MSG_DEBUG("Final trigger efficiency is zero! SF of syst" << systInfoName << " is set to dummy value 1...");
            setFloatVariable(weightName + "_" + systInfoName, 1);
          } else {
            float final_SF_syst = (1 - total_ineff_scaled[iS]) / (1 - total_ineff[iS]);
            ANA_MSG_DEBUG("Final di-electron trigger SF for systematic " << systInfoName << ": " << final_SF_syst);
            setFloatVariable(weightName + "_" + systInfoName, final_SF_syst);
          }
        }
      }

    } else { // something went wrong, just fill the branches with 1
      
      setFloatVariable(weightName, 1);
      
      if (doSys) {
        for (unsigned int iS=1; iS<el_sysVariationNames->size(); ++iS){
          std::string systInfoName = el_sysVariationNames->at(iS);
          setFloatVariable(weightName + "_" + systInfoName, 1);
        }
      }
    }

  } else {
    
    ANA_MSG_DEBUG("Couldn't trigger match two electrons for the di-electron trigger! SF is set to dummy value of 1...");
    setFloatVariable(weightName, 1);
    
    if (doSys) {
      for (unsigned int iS=1; iS<el_sysVariationNames->size(); ++iS){
        std::string systInfoName = el_sysVariationNames->at(iS);
        setFloatVariable(weightName + "_" + systInfoName, 1);
      }
    }
  }

  return EL::StatusCode::SUCCESS;
}









// ---------------------------------------------------------------------------//
const xAOD::TruthParticle* LJAlgo::getTruthMatchedParticle(const xAOD::IParticle& lepton) {
  
  static const SG::AuxElement::ConstAccessor< Link_t > acc( "truthParticleLink" );
  if ( acc.isAvailable( lepton ) ) {
    const Link_t& link = acc( lepton );
    if ( link.isValid() ) {
      
      return *link;
    }
  }

  // For TRUTH3 info
  static const SG::AuxElement::ConstAccessor< Link_t > acc_alt( "TruthLink" );
  if ( acc_alt.isAvailable( lepton ) ) {
    const Link_t& link_alt = acc_alt( lepton );
    if ( link_alt.isValid() ) {
      return *link_alt;
    }
  }

  ANA_MSG_DEBUG("Link to truth match for this reco lepton is invalid. This can occur if the lepton comes from minbias (pile-up) events. Continuing");

  return nullptr;
}
