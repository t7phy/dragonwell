#include <AsgTools/MessageCheck.h>
#include <NtupleMaker/xAODHelper.h>

xAODHelper :: xAODHelper (const std::string& name,
                                  ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm (name, pSvcLocator)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0. Note that things like resetting
  // statistics variables should rather go into the initialize() function.

  declareProperty( "isMC", isMC = 0, "is simulation?" );
  declareProperty( "Region", Region = 0, "Central or Forward" );
  declareProperty( "Year", Year = "1516", "Data year" );
  declareProperty( "mcVersion", mcVersion = "mc16a", "MC version" );
  declareProperty( "SysFilter", SysFilter = "nominal", "systematic filter" );

}

StatusCode xAODHelper :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed

  t_AODname = wk()->inputFile()->GetName();

  bool isDuplicated = false;
  for(auto na : *vec_AODname){
    if(t_AODname==na){isDuplicated = true; break;}
  } 
  if(isDuplicated) return StatusCode::SUCCESS;

  // https://twiki.cern.ch/twiki/bin/view/AtlasProtected/AnalysisMetadata
  // get the MetaData tree once a new file is opened, with
  TTree *MetaData = dynamic_cast<TTree*>(wk()->inputFile()->Get("MetaData"));
  if (!MetaData) {
    Error("fileExecute()", "MetaData not found! Exiting.");
    return StatusCode::FAILURE;
  }
  MetaData->LoadTree(0);

  //check if file is from a DxAOD
  bool m_isDerivation = !MetaData->GetBranch("StreamAOD");

  if(m_isDerivation){
    const xAOD::CutBookkeeperContainer* incompleteCBC = nullptr;
    if(!event->retrieveMetaInput(incompleteCBC, "IncompleteCutBookkeepers").isSuccess()){
      Error("fileExecute()","Failed to retrieve IncompleteCutBookkeepers from MetaData! Exiting.");
      return StatusCode::FAILURE;
    }
    if ( incompleteCBC->size() != 0 ) {
      Warning("fileExecute()","Found incomplete Bookkeepers! Check file for corruption.");
//       return StatusCode::FAILURE;
    }
    // Now, let's find the actual information
    const xAOD::CutBookkeeperContainer* completeCBC = 0;
    if(!event->retrieveMetaInput(completeCBC, "CutBookkeepers").isSuccess()){
      Error("fileExecute()","Failed to retrieve CutBookkeepers from MetaData! Exiting.");
      return StatusCode::FAILURE;
    }

    // First, let's find the smallest cycle number,
    // i.e., the original first processing step/cycle
    int maxCycle = -1;
    const xAOD::CutBookkeeper* allEventsCBK=0;
    for ( auto cbk : *completeCBC ) {
      if(cbk->inputStream()=="StreamAOD" && cbk->name()=="AllExecutedEvents" && cbk->cycle()>maxCycle) { maxCycle=cbk->cycle(); allEventsCBK = cbk; }
    }
    t_nEventsProcessed  = allEventsCBK->nAcceptedEvents();
    t_sumOfWeights        = allEventsCBK->sumOfEventWeights();
    t_sumOfWeightsSquared = allEventsCBK->sumOfEventWeightsSquared();

    t_runNumber = eventInfo->runNumber();
    t_mcChannelNumber = isMC?(eventInfo->mcChannelNumber()):0; 
    //t_crossSection = isMC?(m_PMGCrossSectionTool->getAMIXsection(t_mcChannelNumber) * m_PMGCrossSectionTool->getFilterEff(t_mcChannelNumber)):0;
    //std::cout<<"Checking PMG Tool : "<<m_PMGCrossSectionTool->getAMIXsection(t_mcChannelNumber)<<"   "<<m_PMGCrossSectionTool->getFilterEff(t_mcChannelNumber)<<std::endl;

    vec_runNumber -> push_back(t_runNumber);
    vec_mcChannelNumber -> push_back(t_mcChannelNumber);
    vec_sumOfWeights -> push_back(t_sumOfWeights);
    vec_sumOfEvents -> push_back(t_nEventsProcessed);
    vec_crossSection -> push_back(t_crossSection);

  }
  else{
    vec_runNumber -> push_back(0);
    vec_mcChannelNumber -> push_back(0);
    vec_sumOfWeights -> push_back(0);
    vec_sumOfEvents -> push_back(0);
    vec_crossSection -> push_back(1);
  }
  vec_AODname -> push_back(t_AODname);
  std::cout<<"bookkeeping "<<t_AODname<<std::endl;

  if(isMC) WeightNames = m_weightTool->getWeightNames();
//  for(int i = 0; i < WeightNames.size(); i++){
//    std::cout<<i<<": "<<WeightNames.at(i)<<std::endl;
//  }
  return StatusCode::SUCCESS;
}


StatusCode xAODHelper :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.
  //
  // may be done for each input root file, beware of that...need to be proved
  ANA_MSG_INFO ("in initialize");

  vec_runNumber = new std::vector<uint32_t>();
  vec_mcChannelNumber = new std::vector<uint32_t>();
  vec_sumOfWeights = new std::vector<double>();
  vec_sumOfEvents = new std::vector<double>();
  vec_AODname = new std::vector<std::string>();
  vec_crossSection = new std::vector<double>();

  m_store = new xAOD::TStore();



///////////////////////
////  event level  ////
///////////////////////



  // GRL
  m_grl = asg::AnaToolHandle<IGoodRunsListSelectionTool>("GoodRunsListSelectionTool/grl");
  std::vector<std::string> vecStringGRL;
//  vecStringGRL.push_back(PathResolverFindCalibFile("NtupleMaker/data15_13TeV.periodAllYear_DetStatus-v79-repro20-02_DQDefects-00-02-02_PHYS_StandardGRL_All_Good_25ns.xml"));
//  vecStringGRL.push_back(PathResolverFindCalibFile("NtupleMaker/data16_13TeV.periodAllYear_DetStatus-v88-pro20-21_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml"));
//  vecStringGRL.push_back(PathResolverFindCalibFile("NtupleMaker/data17_13TeV.periodAllYear_DetStatus-v97-pro21-13_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml"));
//  vecStringGRL.push_back(PathResolverFindCalibFile("NtupleMaker/data18_13TeV.periodAllYear_DetStatus-v102-pro22-03_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml"));
  vecStringGRL.push_back(PathResolverFindCalibFile("NtupleMaker/data15_13TeV.periodAllYear_DetStatus-v89-pro21-02_Unknown_PHYS_StandardGRL_All_Good_25ns.xml"));
  vecStringGRL.push_back(PathResolverFindCalibFile("NtupleMaker/data16_13TeV.periodAllYear_DetStatus-v89-pro21-01_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml"));
//  vecStringGRL.push_back(PathResolverFindCalibFile("NtupleMaker/data17_13TeV.periodAllYear_DetStatus-v97-pro21-17_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml"));
  vecStringGRL.push_back(PathResolverFindCalibFile("NtupleMaker/data17_13TeV.periodAllYear_DetStatus-v99-pro22-01_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml"));
  vecStringGRL.push_back(PathResolverFindCalibFile("NtupleMaker/data18_13TeV.periodAllYear_DetStatus-v102-pro22-04_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml"));
  std::cout<<"check the read grl 1: "<<vecStringGRL.at(0)<<std::endl;
  EL_RETURN_CHECK("init()",m_grl.setProperty( "GoodRunsListVec", vecStringGRL));
  EL_RETURN_CHECK("init()",m_grl.setProperty("PassThrough", false)); // if true (default) will ignore result of GRL and will just pass all events
  EL_RETURN_CHECK("init()",m_grl.initialize());


  //pile up reweighting
  m_prwTool = asg::AnaToolHandle<CP::IPileupReweightingTool>("CP::PileupReweightingTool/prwTool");
  std::vector<std::string> confFiles;
  std::vector<std::string> lcalcFiles;
  std::cout<<"mcVersion: "<<mcVersion<<", Year: "<<Year<<std::endl;
  if(mcVersion == "mc16a"){
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.mc16a.merged.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.mc16a.PowhegWZ.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.polarization.mc16a.merged.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.polarization.new.mc16a.merged.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.GMvbf.mc16a.merged.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.HVTqq.mc16a.merged.root"));
     lcalcFiles.push_back(PathResolverFindCalibFile("NtupleMaker/ilumicalc_histograms_None_276262-284484_OflLumi-13TeV-010.root"));
     lcalcFiles.push_back(PathResolverFindCalibFile("NtupleMaker/ilumicalc_histograms_None_297730-311481_OflLumi-13TeV-010.root"));
  }
  if(mcVersion == "mc16d"){
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.mc16d.merged.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.mc16d.PowhegWZ.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.polarization.mc16d.merged.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.polarization.new.mc16d.merged.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.GMvbf.mc16d.merged.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.HVTqq.mc16d.merged.root"));
     lcalcFiles.push_back(PathResolverFindCalibFile("NtupleMaker/ilumicalc_histograms_None_325713-340453_OflLumi-13TeV-010.root"));
  }
  if(mcVersion == "mc16e"){
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.mc16e.merged.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.mc16e.PowhegWZ.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.polarization.mc16e.merged.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.polarization.new.mc16e.merged.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.GMvbf.mc16e.merged.root"));
     confFiles.push_back(PathResolverFindCalibFile("NtupleMaker/NTUP_PILEUP.HVTqq.mc16e.merged.root"));
     lcalcFiles.push_back(PathResolverFindCalibFile("NtupleMaker/ilumicalc_histograms_None_348885-364292_OflLumi-13TeV-001.root"));
  }
  if(Year == "1516") m_Year = 1516;
  if(Year == "17") m_Year = 17;
  if(Year == "18") m_Year = 18;

//  lcalcFiles.push_back(PathResolverFindCalibFile("GoodRunsLists/data17_13TeV/20180309/physics_25ns_Triggerno17e33prim.lumicalc.OflLumi-13TeV-010.root"));
  m_prwTool.setProperty( "ConfigFiles", confFiles);
  m_prwTool.setProperty( "LumiCalcFiles", lcalcFiles);
  m_prwTool.setProperty("UnrepresentedDataAction", 3 );
//  m_prwTool.setProperty("DataScaleFactor", 1.0/1.09 ); //mc15
  m_prwTool.setProperty("DataScaleFactor", 1.0/1.03 ); //mc16
  m_prwTool.setProperty("DataScaleFactorUP", 1.0 );
  m_prwTool.setProperty("DataScaleFactorDOWN", 1.0/1.18 );
  EL_RETURN_CHECK("initialize()",m_prwTool.retrieve());

  ASG_SET_ANA_TOOL_TYPE( m_PMGCrossSectionTool, PMGTools::PMGCrossSectionTool);
  m_PMGCrossSectionTool.setName("myCrossSectionTool");
  m_PMGCrossSectionTool.retrieve();
//  m_PMGCrossSectionTool->readInfosFromFiles({PathResolverFindCalibFile("dev/PMGTools/PMGxsecDB_mc16.txt")});
  m_PMGCrossSectionTool->readInfosFromFiles({PathResolverFindCalibFile("/eos/atlas/atlascerngroupdisk/asg-calib/dev/PMGTools/PMGxsecDB_mc16.txt")});


  // Trigger

  if(!runFwdReco){
    m_TrigDecTool = asg::AnaToolHandle<Trig::TrigDecisionTool>("Trig::TrigDecisionTool/TrigDecisionTool");
    m_TrigConfigTool = asg::AnaToolHandle<TrigConf::ITrigConfigTool>("TrigConf::xAODConfigTool/xAODConfigTool");
    EL_RETURN_CHECK("initialize()", m_TrigConfigTool.initialize() );
    m_TrigDecTool.setProperty("ConfigTool",m_TrigConfigTool.getHandle());
    m_TrigDecTool.setProperty("TrigDecisionKey","xTrigDecision");
    EL_RETURN_CHECK("initialize()", m_TrigDecTool.initialize() );

  // Trigger Match
    m_trigMatch = asg::AnaToolHandle<Trig::IMatchingTool>( "Trig::MatchingTool/MatchingTool" );
//    m_trigMatch = new Trig::MatchingTool( "MatchingTool" );
    m_trigMatch.setProperty("TrigDecisionTool",m_TrigDecTool.getHandle());
    m_trigMatch.initialize();
  }

//////////////////////////
////  Electron Gamma  ////
//////////////////////////



  // Electron Calibration
  m_EleCalibTool = new CP::EgammaCalibrationAndSmearingTool("EgammaCalibrationAndSmearingTool");
//  m_EleCalibTool->setProperty("ResolutionType", "SigmaEff90"); 
//  m_EleCalibTool->setProperty("decorrelationModel", "FULL_v1");
//  m_EleCalibTool->setProperty("decorrelationModel", "FULL_ETACORRELATED_v1");
  m_EleCalibTool->setProperty("ESModel", "es2018_R21_v0");
  m_EleCalibTool->setProperty("decorrelationModel", "1NP_v1");
  if(isMC==2) m_EleCalibTool->setProperty("useAFII", true);
  EL_RETURN_CHECK("initialize()", m_EleCalibTool->initialize() );

  // Likelihood-Based Electron ID
  m_ElectronIDToolLoose = new AsgElectronLikelihoodTool("AsgElectronLikelihoodToolLoose");
  m_ElectronIDToolLoose->setProperty("primaryVertexContainer","PrimaryVertices" );
//  m_ElectronIDToolLoose->setProperty("WorkingPoint", "LooseLHElectron" );
  m_ElectronIDToolLoose->setProperty("WorkingPoint", "LooseBLLHElectron" );
  EL_RETURN_CHECK("initialize()", m_ElectronIDToolLoose->initialize() );

  m_ElectronIDToolMedium = new AsgElectronLikelihoodTool("AsgElectronLikelihoodToolMedium");
  m_ElectronIDToolMedium->setProperty("primaryVertexContainer","PrimaryVertices" );
  m_ElectronIDToolMedium->setProperty("WorkingPoint", "MediumLHElectron" );
  EL_RETURN_CHECK("initialize()", m_ElectronIDToolMedium->initialize() );

  m_ElectronIDToolTight = new AsgElectronLikelihoodTool("AsgElectronLikelihoodToolTight");
  m_ElectronIDToolTight->setProperty("primaryVertexContainer","PrimaryVertices" );
  m_ElectronIDToolTight->setProperty("WorkingPoint", "TightLHElectron" );
  EL_RETURN_CHECK("initialize()", m_ElectronIDToolTight->initialize() );

  //charge flip ID
/*  ECIDSTool = new AsgElectronChargeIDSelectorTool("AsgElectronChargeIDmedium");
//  std::string trainingfile="ElectronPhotonSelectorTools/ChargeID/ECIDS_20161125for2017Moriond.root";
  std::string trainingfile="ElectronPhotonSelectorTools/ChargeID/ECIDS_20180731rel21Summer2018.root";
  float BDT_OP=0; //Set your operating point with the table above.
  EL_RETURN_CHECK("initialize()",ECIDSTool->setProperty("TrainingFile",trainingfile));
  EL_RETURN_CHECK("initialize()",ECIDSTool->setProperty("CutOnBDT",BDT_OP));
  EL_RETURN_CHECK("initialize()",ECIDSTool->initialize());
*/

  // forward electron ID
  m_FwdElectronIDToolLoose = new AsgForwardElectronIsEMSelector("AsgFwdElectronLikelihoodToolLoose");
  m_FwdElectronIDToolLoose->setProperty("ConfigFile","ElectronPhotonSelectorTools/offline/mc15_20150812/ForwardElectronIsEMLooseSelectorCutDefs.conf");
  EL_RETURN_CHECK("initialize()", m_FwdElectronIDToolLoose->initialize() );

  m_FwdElectronIDToolMedium = new AsgForwardElectronIsEMSelector("AsgFwdElectronLikelihoodToolMedium");
  m_FwdElectronIDToolMedium->setProperty("ConfigFile","ElectronPhotonSelectorTools/offline/mc15_20150812/ForwardElectronIsEMMediumSelectorCutDefs.conf");
  EL_RETURN_CHECK("initialize()", m_FwdElectronIDToolMedium->initialize() );

  m_FwdElectronIDToolTight = new AsgForwardElectronIsEMSelector("AsgFwdElectronLikelihoodToolTight");
  m_FwdElectronIDToolTight->setProperty("ConfigFile","ElectronPhotonSelectorTools/offline/mc15_20150812/ForwardElectronIsEMTightSelectorCutDefs.conf");
  EL_RETURN_CHECK("initialize()", m_FwdElectronIDToolTight->initialize() );


  m_FwdElectronLikelihoodToolLoose = new AsgForwardElectronLikelihoodTool("FwdElectronLikelihoodToolLoose");
  m_FwdElectronLikelihoodToolLoose->setProperty("primaryVertexContainer","PrimaryVertices" );
  m_FwdElectronLikelihoodToolLoose->setProperty("WorkingPoint", "LooseLHForwardElectron");
//  m_FwdElectronLikelihoodToolLoose->setProperty("ConfigFile", "ElectronPhotonSelectorTools/offline/mc16_20180716/FwdLHLooseConf.conf");
//  m_FwdElectronLikelihoodToolLoose->setProperty("ConfigFile", "ElectronPhotonSelectorTools/offline/mc16_20180822/FwdLHLooseConf.conf");
  m_FwdElectronLikelihoodToolLoose->msg().setLevel(MSG::ERROR);
  EL_RETURN_CHECK("initialize()", m_FwdElectronLikelihoodToolLoose->initialize() );

  m_FwdElectronLikelihoodToolMedium = new AsgForwardElectronLikelihoodTool("FwdElectronLikelihoodToolMedium");
  m_FwdElectronLikelihoodToolMedium->setProperty("primaryVertexContainer","PrimaryVertices" );
  m_FwdElectronLikelihoodToolMedium->setProperty("WorkingPoint", "MediumLHForwardElectron");
//  m_FwdElectronLikelihoodToolMedium->setProperty("ConfigFile", "ElectronPhotonSelectorTools/offline/mc16_20180716/FwdLHMediumConf.conf");
//  m_FwdElectronLikelihoodToolMedium->setProperty("ConfigFile", "ElectronPhotonSelectorTools/offline/mc16_20180822/FwdLHMediumConf.conf");
  m_FwdElectronLikelihoodToolMedium->msg().setLevel(MSG::ERROR);
  EL_RETURN_CHECK("initialize()", m_FwdElectronLikelihoodToolMedium->initialize() );

  m_FwdElectronLikelihoodToolTight = new AsgForwardElectronLikelihoodTool("FwdElectronLikelihoodToolTight");
  m_FwdElectronLikelihoodToolTight->setProperty("primaryVertexContainer","PrimaryVertices" );
  m_FwdElectronLikelihoodToolTight->setProperty("WorkingPoint", "TightLHForwardElectron");
//  m_FwdElectronLikelihoodToolTight->setProperty("ConfigFile", "ElectronPhotonSelectorTools/offline/mc16_20180716/FwdLHTightConf.conf");
//  m_FwdElectronLikelihoodToolTight->setProperty("ConfigFile", "ElectronPhotonSelectorTools/offline/mc16_20180822/FwdLHTightConf.conf");
  m_FwdElectronLikelihoodToolTight->msg().setLevel(MSG::ERROR);
  EL_RETURN_CHECK("initialize()", m_FwdElectronLikelihoodToolTight->initialize() );

  //ElectronEfficiencyCorrection
  std::string  m_mapFileNew = "ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/map1.txt";//before2021.11.29
//  std::string  m_mapFileNew = "ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/map1.txt";
  std::string  m_mapFileOld = "ElectronEfficiencyCorrection/2015_2017/rel21.2/Moriond_February2018_v1/map1.txt";
  std::string  m_recoKey = "Reconstruction";
  std::string  m_idKey1 = "LooseBLayer";
  std::string  m_idKey2 = "Medium";
  std::string  m_idKey3 = "Tight";
  std::string  m_idFwdKey1 = "FwdLoose";
  std::string  m_idFwdKey2 = "FwdMedium";
  std::string  m_idFwdKey3 = "FwdTight";
  std::string  m_isoKey3 = "FCLoose";
  std::string  m_isoKey4 = "FCTight";
  std::string  m_trigKey = "SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0";

  m_recoEgCorrections = new AsgElectronEfficiencyCorrectionTool("m_recoEgCorrections");
  m_recoEgCorrections->setProperty("MapFilePath",m_mapFileOld);
  m_recoEgCorrections->setProperty("RecoKey",m_recoKey);
  m_recoEgCorrections->setProperty("ForceDataType",1);
  m_recoEgCorrections->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_recoEgCorrections->initialize());

  m_idEgCorrections2 = new AsgElectronEfficiencyCorrectionTool("m_idEgCorrections2");
  m_idEgCorrections2->setProperty("MapFilePath",m_mapFileNew);
  m_idEgCorrections2->setProperty("IdKey",m_idKey2);
  m_idEgCorrections2->setProperty("ForceDataType",1);
  m_idEgCorrections2->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_idEgCorrections2->initialize());

  m_idEgCorrections3 = new AsgElectronEfficiencyCorrectionTool("m_idEgCorrections3");
  m_idEgCorrections3->setProperty("MapFilePath",m_mapFileNew);
  m_idEgCorrections3->setProperty("IdKey",m_idKey3);
  m_idEgCorrections3->setProperty("ForceDataType",1);
  m_idEgCorrections3->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_idEgCorrections3->initialize());

  m_idFwdEgCorrections1 = new AsgElectronEfficiencyCorrectionTool("m_idFwdEgCorrections1");
  m_idFwdEgCorrections1->setProperty("MapFilePath",m_mapFileNew);
  m_idFwdEgCorrections1->setProperty("IdKey",m_idFwdKey1);
  m_idFwdEgCorrections1->setProperty("ForceDataType",1);
  m_idFwdEgCorrections1->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_idFwdEgCorrections1->initialize());

  m_idFwdEgCorrections2 = new AsgElectronEfficiencyCorrectionTool("m_idFwdEgCorrections2");
  m_idFwdEgCorrections2->setProperty("MapFilePath",m_mapFileNew);
  m_idFwdEgCorrections2->setProperty("IdKey",m_idFwdKey2);
  m_idFwdEgCorrections2->setProperty("ForceDataType",1);
  m_idFwdEgCorrections2->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_idFwdEgCorrections2->initialize());

  m_idFwdEgCorrections3 = new AsgElectronEfficiencyCorrectionTool("m_idFwdEgCorrections3");
  m_idFwdEgCorrections3->setProperty("MapFilePath",m_mapFileNew);
  m_idFwdEgCorrections3->setProperty("IdKey",m_idFwdKey3);
  m_idFwdEgCorrections3->setProperty("ForceDataType",1);
  m_idFwdEgCorrections3->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_idFwdEgCorrections3->initialize());


  m_isoEgCorrections2 = new AsgElectronEfficiencyCorrectionTool("m_isoEgCorrections2");
  m_isoEgCorrections2->setProperty("MapFilePath",m_mapFileNew);
  m_isoEgCorrections2->setProperty("IdKey",m_idKey2);
  m_isoEgCorrections2->setProperty("IsoKey",m_isoKey3);
  m_isoEgCorrections2->setProperty("ForceDataType",1);
  m_isoEgCorrections2->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_isoEgCorrections2->initialize());

  m_isoEgCorrections3 = new AsgElectronEfficiencyCorrectionTool("m_isoEgCorrections3");
  m_isoEgCorrections3->setProperty("MapFilePath",m_mapFileNew);
  m_isoEgCorrections3->setProperty("IdKey",m_idKey2);
  m_isoEgCorrections3->setProperty("IsoKey",m_isoKey4);
  m_isoEgCorrections3->setProperty("ForceDataType",1);
  m_isoEgCorrections3->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_isoEgCorrections3->initialize());

  m_isoEgCorrections4 = new AsgElectronEfficiencyCorrectionTool("m_isoEgCorrections4");
  m_isoEgCorrections4->setProperty("MapFilePath",m_mapFileNew);
  m_isoEgCorrections4->setProperty("IdKey",m_idKey3);
  m_isoEgCorrections4->setProperty("IsoKey",m_isoKey4);
  m_isoEgCorrections4->setProperty("ForceDataType",1);
  m_isoEgCorrections4->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_isoEgCorrections4->initialize());

  m_isoEgCorrections5 = new AsgElectronEfficiencyCorrectionTool("m_isoEgCorrections5");
  m_isoEgCorrections5->setProperty("CorrectionFileNameList",std::vector{"ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/isolation/efficiencySF.Isolation.MediumLLH_d0z0_v13_isolHighPtCaloOnly.root"});
  m_isoEgCorrections5->setProperty("IdKey","Medium");
  m_isoEgCorrections5->setProperty("IsoKey","HighPtCaloOnly");
  m_isoEgCorrections5->setProperty("ForceDataType",1);
  m_isoEgCorrections5->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_isoEgCorrections5->initialize());

  m_isoEgCorrections6 = new AsgElectronEfficiencyCorrectionTool("m_isoEgCorrections6");
  m_isoEgCorrections6->setProperty("CorrectionFileNameList",std::vector{"ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/isolation/efficiencySF.Isolation.MediumLLH_d0z0_v13_isolTight.root"});
  m_isoEgCorrections6->setProperty("IdKey","Medium");
  m_isoEgCorrections6->setProperty("IsoKey","Tight");
  m_isoEgCorrections6->setProperty("ForceDataType",1);
  m_isoEgCorrections6->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_isoEgCorrections6->initialize());

  m_isoEgCorrections7 = new AsgElectronEfficiencyCorrectionTool("m_isoEgCorrections7");
  m_isoEgCorrections7->setProperty("CorrectionFileNameList",std::vector{"ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/isolation/efficiencySF.Isolation.MediumLLH_d0z0_v13_isolLoose.root"});
  m_isoEgCorrections7->setProperty("IdKey","Medium");
  m_isoEgCorrections7->setProperty("IsoKey","Loose");
  m_isoEgCorrections7->setProperty("ForceDataType",1);
  m_isoEgCorrections7->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_isoEgCorrections7->initialize());

  m_isoEgCorrections8 = new AsgElectronEfficiencyCorrectionTool("m_isoEgCorrections8");
  m_isoEgCorrections8->setProperty("CorrectionFileNameList",std::vector{"ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/isolation/efficiencySF.Isolation.TightLLH_d0z0_v13_isolHighPtCaloOnly.root"});
  m_isoEgCorrections8->setProperty("IdKey","Tight");
  m_isoEgCorrections8->setProperty("IsoKey","HighPtCaloOnly");
  m_isoEgCorrections8->setProperty("ForceDataType",1);
  m_isoEgCorrections8->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_isoEgCorrections8->initialize());

  m_isoEgCorrections9 = new AsgElectronEfficiencyCorrectionTool("m_isoEgCorrections9");
  m_isoEgCorrections9->setProperty("CorrectionFileNameList",std::vector{"ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/isolation/efficiencySF.Isolation.TightLLH_d0z0_v13_isolTight.root"});
  m_isoEgCorrections9->setProperty("IdKey","Tight");
  m_isoEgCorrections9->setProperty("IsoKey","Tight");
  m_isoEgCorrections9->setProperty("ForceDataType",1);
  m_isoEgCorrections9->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_isoEgCorrections9->initialize());

  m_isoEgCorrections10 = new AsgElectronEfficiencyCorrectionTool("m_isoEgCorrections10");
  m_isoEgCorrections10->setProperty("CorrectionFileNameList",std::vector{"ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/isolation/efficiencySF.Isolation.TightLLH_d0z0_v13_isolLoose.root"});
  m_isoEgCorrections10->setProperty("IdKey","Tight");
  m_isoEgCorrections10->setProperty("IsoKey","Loose");
  m_isoEgCorrections10->setProperty("ForceDataType",1);
  m_isoEgCorrections10->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_isoEgCorrections10->initialize());


  std::vector<std::string> chargeSF_configFiles{"ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/charge_misID/chargeEfficiencySF.MediumLLH_d0z0_v13_FCTight.root"};
//  std::vector<std::string> trigSF_configFiles1{"ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/trigger/efficiencySF.SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0.MediumLLH_d0z0_v13_isolFCHighPtCaloOnly.root"};
  std::vector<std::string> trigSF_configFiles1{"ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/trigger/efficiencySF.SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0.MediumLLH_d0z0_v13_isolFCLoose.root"};
  std::vector<std::string> trigSF_configFiles2{"ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/trigger/efficiencySF.SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0.MediumLLH_d0z0_v13_isolFCTight.root"};
  std::vector<std::string> trigSF_configFiles3{"ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/trigger/efficiencySF.SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0.TightLLH_d0z0_v13_isolFCTight.root"};
  std::vector<std::string> trigSF_configFiles4{"ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/trigger/efficiencySF.SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0.TightLLH_d0z0_v13_isolGradient.root"};
  std::vector<std::string> trigEff_configFiles1{"ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/trigger/efficiency.SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0.MediumLLH_d0z0_v13_isolFCLoose.root"};
//  std::vector<std::string> trigEff_configFiles1{"ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/trigger/efficiency.SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0.MediumLLH_d0z0_v13_isolFCHighPtCaloOnly.root"};
  std::vector<std::string> trigEff_configFiles2{"ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/trigger/efficiency.SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0.MediumLLH_d0z0_v13_isolFCTight.root"};
  std::vector<std::string> trigEff_configFiles3{"ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/trigger/efficiency.SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0.TightLLH_d0z0_v13_isolFCTight.root"};
  std::vector<std::string> trigEff_configFiles4{"ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/trigger/efficiency.SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0.TightLLH_d0z0_v13_isolGradient.root"};

//  m_chargeEgCorrections = asg::AnaToolHandle<IAsgElectronEfficiencyCorrectionTool>("IAsgElectronEfficiencyCorrectionTool/chargeEgCorrections");
//  m_chargeEgCorrections.setProperty( "CorrectionFileName", "ElectronEfficiencyCorrection/2015_2017/rel21.2/Consolidation_September2018_v1/charge_misID/chargeEfficiencySF.TightLLH_d0z0_v13_Gradient.root" );
//  m_chargeEgCorrections.retrieve();

//  m_chargeEgCorrections = new AsgElectronEfficiencyCorrectionTool("m_chargeEgCorrections");
//  m_chargeEgCorrections->setProperty("CorrectionFileNameList",chargeSF_configFiles);
//  m_chargeEgCorrections->setProperty("ForceDataType",1);
//  m_chargeEgCorrections->setProperty("CorrelationModel", "TOTAL" );
//  EL_RETURN_CHECK("initialize()",m_chargeEgCorrections->initialize());

  m_trigEgCorrections1 = new AsgElectronEfficiencyCorrectionTool("m_trigEgCorrections1");
  m_trigEgCorrections1->setProperty("CorrectionFileNameList",trigSF_configFiles1);
  m_trigEgCorrections1->setProperty("ForceDataType",1);
  m_trigEgCorrections1->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_trigEgCorrections1->initialize());

  m_trigEgEfficienciesMC1 = new AsgElectronEfficiencyCorrectionTool("m_trigEgEfficienciesMC1");
  m_trigEgEfficienciesMC1->setProperty("CorrectionFileNameList",trigEff_configFiles1);
  m_trigEgEfficienciesMC1->setProperty("ForceDataType",1);
  m_trigEgEfficienciesMC1->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_trigEgEfficienciesMC1->initialize());

  m_trigEgCorrections2 = new AsgElectronEfficiencyCorrectionTool("m_trigEgCorrections2");
  m_trigEgCorrections2->setProperty("CorrectionFileNameList",trigSF_configFiles2);
  m_trigEgCorrections2->setProperty("ForceDataType",1);
  m_trigEgCorrections2->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_trigEgCorrections2->initialize());

  m_trigEgEfficienciesMC2 = new AsgElectronEfficiencyCorrectionTool("m_trigEgEfficienciesMC2");
  m_trigEgEfficienciesMC2->setProperty("CorrectionFileNameList",trigEff_configFiles2);
  m_trigEgEfficienciesMC2->setProperty("ForceDataType",1);
  m_trigEgEfficienciesMC2->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_trigEgEfficienciesMC2->initialize());

  m_trigEgCorrections3 = new AsgElectronEfficiencyCorrectionTool("m_trigEgCorrections3");
  m_trigEgCorrections3->setProperty("CorrectionFileNameList",trigSF_configFiles3);
  m_trigEgCorrections3->setProperty("ForceDataType",1);
  m_trigEgCorrections3->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_trigEgCorrections3->initialize());

  m_trigEgEfficienciesMC3 = new AsgElectronEfficiencyCorrectionTool("m_trigEgEfficienciesMC3");
  m_trigEgEfficienciesMC3->setProperty("CorrectionFileNameList",trigEff_configFiles3);
  m_trigEgEfficienciesMC3->setProperty("ForceDataType",1);
  m_trigEgEfficienciesMC3->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("initialize()",m_trigEgEfficienciesMC3->initialize());

  m_trigEgCorrections4 = new AsgElectronEfficiencyCorrectionTool("m_trigEgCorrections4");
  m_trigEgCorrections4->setProperty("CorrectionFileNameList",trigSF_configFiles4);
  m_trigEgCorrections4->setProperty("ForceDataType",1);
  m_trigEgCorrections4->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("init()",m_trigEgCorrections4->initialize());

  m_trigEgEfficienciesMC4 = new AsgElectronEfficiencyCorrectionTool("m_trigEgEfficienciesMC4");
  m_trigEgEfficienciesMC4->setProperty("CorrectionFileNameList",trigEff_configFiles4);
  m_trigEgEfficienciesMC4->setProperty("ForceDataType",1);
  m_trigEgEfficienciesMC4->setProperty("CorrelationModel", "TOTAL" );
  EL_RETURN_CHECK("init()",m_trigEgEfficienciesMC4->initialize());


////////////////
////  Muon  ////
////////////////



  // initialize the muon calibration and smearing tool
  m_muonCalibrationAndSmearingTool = asg::AnaToolHandle<CP::IMuonCalibrationAndSmearingTool>("CP::MuonCalibrationAndSmearingTool/MuonCorrectionTool");
  if(Year.find("15")!=std::string::npos){
    m_muonCalibrationAndSmearingTool.setProperty( "Year", "Data15" );
    m_muonCalibrationAndSmearingTool.setProperty( "SagittaCorr", true );
    m_muonCalibrationAndSmearingTool.setProperty( "SagittaCorrPhaseSpace", true );
    m_muonCalibrationAndSmearingTool.setProperty( "SagittaRelease", "sagittaBiasDataAll_03_02_19_Data16" );
  }
  if(Year.find("16")!=std::string::npos){
    m_muonCalibrationAndSmearingTool.setProperty( "Year", "Data16" );
    m_muonCalibrationAndSmearingTool.setProperty( "SagittaCorr", true );
    m_muonCalibrationAndSmearingTool.setProperty( "SagittaCorrPhaseSpace", true );
    m_muonCalibrationAndSmearingTool.setProperty( "SagittaRelease", "sagittaBiasDataAll_03_02_19_Data16" );
  }
  if(Year.find("17")!=std::string::npos){
    m_muonCalibrationAndSmearingTool.setProperty( "Year", "Data17" );
    m_muonCalibrationAndSmearingTool.setProperty( "SagittaCorr", true );
    m_muonCalibrationAndSmearingTool.setProperty( "SagittaCorrPhaseSpace", true );
    m_muonCalibrationAndSmearingTool.setProperty( "SagittaRelease", "sagittaBiasDataAll_03_02_19_Data17" );
  }
  if(Year.find("18")!=std::string::npos){
    m_muonCalibrationAndSmearingTool.setProperty( "Year", "Data18" );
    m_muonCalibrationAndSmearingTool.setProperty( "SagittaCorr", true );
    m_muonCalibrationAndSmearingTool.setProperty( "SagittaCorrPhaseSpace", true );
    m_muonCalibrationAndSmearingTool.setProperty( "SagittaRelease", "sagittaBiasDataAll_03_02_19_Data18" );
  }
  EL_RETURN_CHECK("initialize()",m_muonCalibrationAndSmearingTool.initialize());

  // muon selection
  m_muonSelectionLoose = asg::AnaToolHandle<CP::IMuonSelectionTool>("CP::MuonSelectionTool/muonSelToolLoose");
//  m_muonSelectionLoose.setProperty( "MaxEta", 2.5 );
  m_muonSelectionLoose.setProperty( "MuQuality", 2);
  EL_RETURN_CHECK("initialize()",m_muonSelectionLoose.initialize() );

  m_muonSelectionMedium = asg::AnaToolHandle<CP::IMuonSelectionTool>("CP::MuonSelectionTool/muonSelToolMedium");
//  m_muonSelectionMedium.setProperty( "MaxEta", 2.5 );
  m_muonSelectionMedium.setProperty( "MuQuality", 1);
  EL_RETURN_CHECK("initialize()",m_muonSelectionMedium.initialize() );

  m_muonSelectionTight = asg::AnaToolHandle<CP::IMuonSelectionTool>("CP::MuonSelectionTool/muonSelToolTight");
//  m_muonSelectionTight.setProperty( "MaxEta", 2.5 );
  m_muonSelectionTight.setProperty( "MuQuality", 0);
  EL_RETURN_CHECK("initialize()",m_muonSelectionTight.initialize() );

  //MuonEfficiencyScaleFactors
  m_effi_corr1 = new CP::MuonEfficiencyScaleFactors("muEffSF1");
  m_effi_corr1->setProperty("WorkingPoint","Medium");
  EL_RETURN_CHECK("initialize()",m_effi_corr1->initialize());

  m_effi_corr2 = new CP::MuonEfficiencyScaleFactors("muEffSF2");
  m_effi_corr2->setProperty("WorkingPoint","Tight");
  EL_RETURN_CHECK("initialize()",m_effi_corr2->initialize());

  //MuonIsolationScaleFactor
//  m_iso_effi_corr1 = new CP::MuonEfficiencyScaleFactors("muIsoSF1");
//  m_iso_effi_corr1->setProperty("WorkingPoint","LooseTrackOnlyIso");
//  EL_RETURN_CHECK("initialize()",m_iso_effi_corr1->initialize());

//  m_iso_effi_corr2 = new CP::MuonEfficiencyScaleFactors("muIsoSF2");
//  m_iso_effi_corr2->setProperty("WorkingPoint","GradientIso");
//  EL_RETURN_CHECK("initialize()",m_iso_effi_corr2->initialize());

//  m_iso_effi_corr3 = new CP::MuonEfficiencyScaleFactors("muIsoSF3");
//  m_iso_effi_corr3->setProperty("WorkingPoint","FixedCutHighPtTrackOnlyIso");
//  EL_RETURN_CHECK("initialize()",m_iso_effi_corr3->initialize());

// m_iso_effi_corr4 = new CP::MuonEfficiencyScaleFactors("muIsoSF4");
// m_iso_effi_corr4->setProperty("WorkingPoint","FCTightIso");
// EL_RETURN_CHECK("initialize()",m_iso_effi_corr4->initialize());

  m_iso_effi_corr5 = new CP::MuonEfficiencyScaleFactors("muIsoSF5");
  m_iso_effi_corr5->setProperty("WorkingPoint","FCLooseIso");
  EL_RETURN_CHECK("init()",m_iso_effi_corr5->initialize());

  m_iso_effi_corr6 = new CP::MuonEfficiencyScaleFactors("muIsoSF6");
  m_iso_effi_corr6->setProperty("WorkingPoint","PflowLoose_FixedRadIso");
  EL_RETURN_CHECK("init()",m_iso_effi_corr6->initialize());

  m_iso_effi_corr7 = new CP::MuonEfficiencyScaleFactors("muIsoSF7");
  m_iso_effi_corr7->setProperty("WorkingPoint","PflowTight_FixedRadIso");
  EL_RETURN_CHECK("init()",m_iso_effi_corr7->initialize());

  //MuonIPSF
  m_ip_effi_corr = new CP::MuonEfficiencyScaleFactors("muIpSF");
  m_ip_effi_corr->setProperty("WorkingPoint","TTVA");
  EL_RETURN_CHECK("initialize()",m_ip_effi_corr->initialize());

  //MuonTrigSF
  m_mutrig_sf = new CP::MuonTriggerScaleFactors("TrigSF");
  m_mutrig_sf->setProperty("MuonQuality", "Tight" );
  EL_RETURN_CHECK("initialize()", m_mutrig_sf->initialize() );

  m_mutrig_sf_m = new CP::MuonTriggerScaleFactors("TrigSF");
  m_mutrig_sf_m->setProperty("MuonQuality", "Medium" );
  EL_RETURN_CHECK("initialize()", m_mutrig_sf_m->initialize() );



////////////////
////  jets  ////
////////////////



  //JetCalibration
  m_jetCalibration = asg::AnaToolHandle<IJetCalibrationTool>("JetCalibrationTool/JetCalibTool");
  m_jetCalibration.setProperty("JetCollection",jetKey.c_str());
  if(isMC==2) m_jetCalibration.setProperty("ConfigFile","JES_MC16Recommendation_AFII_PFlow_Apr2019_Rel21.config");
  else m_jetCalibration.setProperty("ConfigFile","JES_MC16Recommendation_Consolidated_PFlow_Apr2019_Rel21.config");
  m_jetCalibration.setProperty("CalibArea","00-04-82");
  if(isMC){
    m_jetCalibration.setProperty("CalibSequence","JetArea_Residual_EtaJES_GSC_Smear");
  }
  else{
    m_jetCalibration.setProperty("CalibSequence","JetArea_Residual_EtaJES_GSC_Insitu");
  }
  m_jetCalibration.setProperty("IsData",!isMC);
  EL_RETURN_CHECK("initialize()", m_jetCalibration.retrieve() );

  //JetUncertainty
  m_jesUncert = new JetUncertaintiesTool("jesUncert");
  m_jesUncert->setProperty("JetDefinition",jetKey.c_str());
  if(isMC==2) m_jesUncert->setProperty("MCType","AFII");
  else m_jesUncert->setProperty("MCType","MC16");
//  m_jesUncert->setProperty("ConfigFile","rel21/Summer2019/R4_SR_Scenario1_SimpleJER.config");
  m_jesUncert->setProperty("ConfigFile","rel21/Summer2019/R4_GlobalReduction_SimpleJER.config");
  m_jesUncert->setProperty("CalibArea","CalibArea-08");
  EL_RETURN_CHECK("initialize()", m_jesUncert->initialize() );

  //JER
//  m_JERTool = asg::AnaToolHandle<IJERTool>("JERTool/m_JERTool");
//  EL_RETURN_CHECK("initialize()", m_JERTool.initialize() );

/*
  m_jerTool = new JERTool("JERTool");
  m_smearTool = new JERSmearingTool("JERSmearingTool");
  m_jerTool->setProperty("PlotFileName", "JetResolution/Prerec2015_xCalib_2012JER_ReducedTo9NP_Plots_v2.root");
  m_jerTool->setProperty("CollectionName", jetType.c_str());
  EL_RETURN_CHECK("initialize()", m_jerTool->initialize() );
  ToolHandle<IJERTool> jerHandle(m_jerTool->name());

  m_smearTool->setProperty("JERTool", jerHandle);
  m_smearTool->setProperty("ApplyNominalSmearing", false);
  m_smearTool->setProperty("isMC", isMC);
  m_smearTool->setProperty("SystematicMode", "Simple"); //"Simple" provides one NP (smearing only in MC), "Full" provides 10NPs (smearing both on data and MC)
  EL_RETURN_CHECK("initialize()", m_smearTool->initialize() );
*/

  //JetVertexTagger
  m_pjvtag = asg::AnaToolHandle<IJetUpdateJvt>("JetVertexTaggerTool/UpdateJVT");
  EL_RETURN_CHECK("initialize()", m_pjvtag.initialize() );

  //fjvt calculator
  m_jetmod = asg::AnaToolHandle<IJetModifier>("JetForwardJvtTool/fJvt");
  m_jetmod.setProperty("CentralMaxPt",60e3);
  EL_RETURN_CHECK("initialize()", m_jetmod.initialize() );


// new version
  //B-tagging
  btagtool = new BTaggingSelectionTool("BTaggingSelectionTool");
//  btagtool->setProperty("MaxEta", 2.5);
  btagtool->setProperty("MinPt", 20000.);
  btagtool->setProperty("JetAuthor", jetTypeBtag.c_str());
//  btagtool->setProperty("TaggerName", "DL1");
  btagtool->setProperty("TaggerName", "DL1r");
//  btagtool->setProperty("FlvTagCutDefinitionsFileName", "xAODBTaggingEfficiency/13TeV/2020-21-13TeV-MC16-CDI-2020-03-11_v1.root" );
//  btagtool->setProperty("FlvTagCutDefinitionsFileName", "xAODBTaggingEfficiency/13TeV/2020-21-13TeV-MC16-CDI-2020-03-11_v2.root" );
//  btagtool->setProperty("FlvTagCutDefinitionsFileName", "xAODBTaggingEfficiency/13TeV/2020-21-13TeV-MC16-CDI-2020-03-11_v3.root" );
  btagtool->setProperty("FlvTagCutDefinitionsFileName", "xAODBTaggingEfficiency/13TeV/2020-21-13TeV-MC16-CDI-2021-04-16_v1.root" );
  btagtool->setProperty("OperatingPoint", "FixedCutBEff_85");
  EL_RETURN_CHECK("init()",btagtool->initialize() );



/*
//old version
  //B-tagging
  btagtool = new BTaggingSelectionTool("BTaggingSelectionTool");
//  btagtool->setProperty("MaxEta", 2.5);
//  btagtool->setProperty("MinPt", 20000.);
  btagtool->setProperty("JetAuthor", "AntiKt4EMTopoJets");
  btagtool->setProperty("TaggerName", "MV2c10");
  btagtool->setProperty("FlvTagCutDefinitionsFileName", "xAODBTaggingEfficiency/13TeV/2017-21-13TeV-MC16-CDI-2018-02-09_v1.root" );
//  btagtool->setProperty("FlvTagCutDefinitionsFileName", "xAODBTaggingEfficiency/13TeV/2016-20_7-13TeV-MC15-CDI-2016-11-25_v1.root" );
  btagtool->setProperty("OperatingPoint", "FixedCutBEff_85");
  EL_RETURN_CHECK("initialize()",btagtool->initialize() );
*/

  //JetCleaning
  m_cleaningTool = asg::AnaToolHandle<IJetSelector>("JetCleaningTool/JetCleaning");
  m_cleaningTool.setProperty("CutLevel", "LooseBad");
  m_cleaningTool.setProperty("DoUgly", false);
  EL_RETURN_CHECK("initialize()", m_cleaningTool.initialize() );


//new version
  jcTool = new JetCleaningTool( "JetCleaningTool" );
  jcTool->setProperty("CutLevel", "LooseBad");
  jcTool->setProperty("DoUgly", false);
  EL_RETURN_CHECK("init()", jcTool->initialize() );
  m_EventCleaningTool = new ECUtils::EventCleaningTool("JetEventCleaningTool");
  m_EventCleaningTool->setProperty("JetCleaningTool", ToolHandle< IJetSelector >( jcTool ) );
//  m_EventCleaningTool->setProperty("PtCut" , 20 );
//  m_EventCleaningTool->setProperty("EtaCut" , 4.5 );
  m_EventCleaningTool->setProperty("JvtDecorator" , "passJVT" );
  m_EventCleaningTool->setProperty("OrDecorator" , OR_outputTag );
//  m_EventCleaningTool->setProperty("CleaningLevel" , "LooseBad" );
  EL_RETURN_CHECK("init()",m_EventCleaningTool->initialize());

  //jvtEfficiency
  jvtsf = new CP::JetJvtEfficiency("jvtsf");
  jvtsf->setProperty("WorkingPoint","Medium");
  jvtsf->setProperty("SFFile","JetJvtEfficiency/Moriond2018/JvtSFFile_EMPFlow.root");
  jvtsf->setProperty("MaxPtForJvt",60e3);
  EL_RETURN_CHECK("init()",jvtsf->initialize());
  fjvtsf = new CP::JetJvtEfficiency("fjvtsf");
//  fjvtsf->setProperty("SFFile","JetJvtEfficiency/Nov2019/fJvtSFFile.EMtopo.root");
  fjvtsf->setProperty("SFFile","JetJvtEfficiency/May2020/fJvtSFFile.EMPFlow.root");
  fjvtsf->setProperty("UseMuSFFormat",true); // To account for new SF binning
  fjvtsf->setProperty("ScaleFactorDecorationName","fJVTSF");
  fjvtsf->setProperty("MaxPtForJvt",60e3);
  EL_RETURN_CHECK("initialize()",fjvtsf->initialize() );

  //btag efficiency
  btagefftool = new BTaggingEfficiencyTool("BTagEfficiency");
  btagefftool->setProperty("MinPt", 20000.);
  btagefftool->setProperty("TaggerName",          "DL1r");
  btagefftool->setProperty("OperatingPoint",      "FixedCutBEff_85");
  btagefftool->setProperty("JetAuthor",           jetTypeBtag.c_str());
//  btagefftool->setProperty("ScaleFactorFileName", "13TeV/2020-21-13TeV-MC16-CDI-2020-03-11_v1.root");
//  btagefftool->setProperty("ScaleFactorFileName", "13TeV/2020-21-13TeV-MC16-CDI-2020-03-11_v2.root");
//  btagefftool->setProperty("ScaleFactorFileName", "13TeV/2020-21-13TeV-MC16-CDI-2020-03-11_v3.root");
  btagefftool->setProperty("ScaleFactorFileName", "xAODBTaggingEfficiency/13TeV/2020-21-13TeV-MC16-CDI-2021-04-16_v1.root");
  btagefftool->setProperty("ConeFlavourLabel", true);
  EL_RETURN_CHECK("init()",btagefftool->initialize());

/*
//old version
  //jvtEfficiency
  jvtsf = new CP::JetJvtEfficiency("jvtsf");
  jvtsf->setProperty("WorkingPoint","Medium");
  jvtsf->setProperty("SFFile","JetJvtEfficiency/Moriond2018/JvtSFFile_EMTopoJets.root");
  EL_RETURN_CHECK("initialize()",jvtsf->initialize());
  fjvtsf = new CP::JetJvtEfficiency("fjvtsf");
  fjvtsf->setProperty("SFFile","JetJvtEfficiency/Moriond2018/fJvtSFFile.root");
  fjvtsf->setProperty("ScaleFactorDecorationName","fJVTSF");
  EL_RETURN_CHECK("initialize()",fjvtsf->initialize() );

  //btag efficiency
  btagefftool = new BTaggingEfficiencyTool("BTagEfficiency");
  btagefftool->setProperty("TaggerName",          "MV2c10");
  btagefftool->setProperty("OperatingPoint",      "FixedCutBEff_85");
  btagefftool->setProperty("JetAuthor",           "AntiKt4EMTopoJets");
//  btagefftool->setProperty("ScaleFactorFileName", "13TeV/2016-20_7-13TeV-MC15-CDI-May31_v1.root");
//  btagefftool->setProperty("ScaleFactorFileName", "13TeV/2017-21-13TeV-MC16-CDI-2018-02-09_v1.root");
  btagefftool->setProperty("ScaleFactorFileName", "13TeV/2017-21-13TeV-MC16-CDI-2018-10-19_v1.root");
  btagefftool->setProperty("ConeFlavourLabel", true);
  EL_RETURN_CHECK("initialize()",btagefftool->initialize());
*/


//////////////////
////  others  ////
//////////////////



  //isolation
/*  iso_0 = new CP::IsolationSelectionTool("iso_0");
  iso_0->setProperty("MuonWP","LooseTrackOnly");
  iso_0->setProperty("ElectronWP","LooseTrackOnly");
  EL_RETURN_CHECK( "initialize()" , iso_0->initialize() );

  iso_1 = new CP::IsolationSelectionTool("iso_1");
  iso_1->setProperty("MuonWP","GradientLoose");
  iso_1->setProperty("ElectronWP","GradientLoose");
  EL_RETURN_CHECK( "initialize()" , iso_1->initialize() );

  iso_2 = new CP::IsolationSelectionTool("iso_2");
  iso_2->setProperty("MuonWP","Gradient");
  iso_2->setProperty("ElectronWP","Gradient");
  EL_RETURN_CHECK( "initialize()" , iso_2->initialize() );
*/
  iso_3 = new CP::IsolationSelectionTool("iso_3");
  iso_3->setProperty("MuonWP","FCLoose");
  iso_3->setProperty("ElectronWP","FCLoose");
  EL_RETURN_CHECK( "initialize()" , iso_3->initialize() );

  iso_4 = new CP::IsolationSelectionTool("iso_4");
  iso_4->setProperty("MuonWP","FCTight");
  iso_4->setProperty("ElectronWP","FCTight");
  EL_RETURN_CHECK( "initialize()" , iso_4->initialize() );

  iso_5 = new CP::IsolationSelectionTool("iso_5");
  iso_5->setProperty("MuonWP","PflowLoose_FixedRad");
  iso_5->setProperty("ElectronWP","FCLoose");
  EL_RETURN_CHECK( "initialize()" , iso_5->initialize() );

  iso_6 = new CP::IsolationSelectionTool("iso_6");
  iso_6->setProperty("MuonWP","PflowLoose_FixedRad");
  iso_6->setProperty("ElectronWP","HighPtCaloOnly");
  EL_RETURN_CHECK( "initialize()" , iso_6->initialize() );

  iso_7 = new CP::IsolationSelectionTool("iso_7");
  iso_7->setProperty("MuonWP","PflowTight_FixedRad");
  iso_7->setProperty("ElectronWP","FCTight");
  EL_RETURN_CHECK( "initialize()" , iso_7->initialize() );

  iso_8 = new CP::IsolationSelectionTool("iso_8");
  iso_8->setProperty("MuonWP","Tight_VarRad");
  iso_8->setProperty("ElectronWP","Tight_VarRad");
  EL_RETURN_CHECK( "initialize()" , iso_8->initialize() );

  iso_9 = new CP::IsolationSelectionTool("iso_9");
  iso_9->setProperty("MuonWP","Loose_VarRad");
  iso_9->setProperty("ElectronWP","Loose_VarRad");
  EL_RETURN_CHECK( "initialize()" , iso_9->initialize() );


  // MetMaker
  metSystTool = asg::AnaToolHandle<IMETSystematicsTool>("met::METSystematicsTool/metSystTool");
  EL_RETURN_CHECK("init()",metSystTool.retrieve());

  metMaker = asg::AnaToolHandle<IMETMaker>("met::METMaker/metMaker");
  metMaker.setProperty("DoMuonEloss", false) ;
  metMaker.setProperty("DoRemoveMuonJets", true) ;
  metMaker.setProperty("DoSetMuonJetEMScale", true) ;
  metMaker.setProperty("DoPFlow", true) ;
  metMaker.setProperty("JetRejectionDec","passFJVT");
  EL_RETURN_CHECK("init()",metMaker.retrieve());


  // bunch crossing removal
  if(!isMC && Region==1){
    bct = new Trig::WebBunchCrossingTool("WebBunchCrossingTool");
    bct->setProperty("OutputLevel", MSG::INFO);
    bct->setProperty("ServerAddress", "atlas-trigconf.cern.ch");
    EL_RETURN_CHECK("initialize()",bct->initialize() );
  }

  //truth weight tool
  m_weightTool.setTypeAndName("PMGTools::PMGTruthWeightTool/PMGTruthWeightTool");

  // overlap removal
  m_overlapRemovalTool = asg::AnaToolHandle<ORUtils::IOverlapRemovalTool>("ORUtils::OverlapRemovalTool/ORTool");
  m_overlapRemovalTool.setProperty("InputLabel", OR_inputTag);
  m_overlapRemovalTool.setProperty("OutputLabel",OR_outputTag);
  m_overlapRemovalTool.retrieve();

  ORUtils::ORFlags orFlags("OverlapRemovalTool", OR_inputTag, OR_outputTag);
  orFlags.doElectrons = true;
  orFlags.doMuons = true;
  orFlags.doJets = true;
  orFlags.doTaus = false;
  orFlags.doPhotons = false;
  orFlags.doMuPFJetOR = true;
  toolBox = new ORUtils::ToolBox();
  ORUtils::recommendedTools(orFlags, *toolBox);
//  toolBox->eleEleORT.setProperty("UseClusterMatch", true);
//  toolBox->eleJetORT.setProperty("OuterDR", 0.);
//  toolBox->muJetORT.setProperty("OuterDR", 0.);
  toolBox->initialize();


  // Systematic Variations
  const CP::SystematicRegistry& registry = CP::SystematicRegistry::getInstance();
  const CP::SystematicSet& recommendedSystematics = registry.recommendedSystematics(); // get list of recommended systematics
  full_sysList = CP::make_systematics_vector(recommendedSystematics);
//  auto sys = m_sysList[2]; std::cout<<*(sys.getBaseNames().begin())<<std::endl;
  for(auto sys : full_sysList){
//    nameSysList.merge(sys.getBaseNames()); // not compatible with c++11, shit...
    if(!sys.getBaseNames().empty()){
      if(*(sys.getBaseNames().begin()) != "MET_SoftTrk_Scale") nameSysList.insert(*(sys.getBaseNames().begin()));
      if(*(sys.getBaseNames().begin()) == "MET_SoftTrk_Scale") {nameSysList.insert("MET_SoftTrk_ScaleUp");nameSysList.insert("MET_SoftTrk_ScaleDown");}
    }
    //if(!sys.getBaseNames().empty()) std::cout<<"Full sysList: "<<(sys.name())<<std::endl;
  }

  // this is the nominal set, no systematic
  if(SysFilter.find("nominal")!=std::string::npos || SysFilter == "all") m_sysList.push_back(CP::SystematicSet());
  for(std::set<std::string>::const_iterator sysbaseItr = nameSysList.begin(); sysbaseItr != nameSysList.end(); ++sysbaseItr){

    bool shouldAdd = false;
    if(SysFilter.find("electron")!=std::string::npos && (sysbaseItr->find("EG_")!=std::string::npos || sysbaseItr->find("EL_")!=std::string::npos)) shouldAdd = true;
    if(SysFilter.find("muon")!=std::string::npos && (sysbaseItr->find("MUON_")!=std::string::npos)) shouldAdd = true;
    if(SysFilter.find("jet")!=std::string::npos && (sysbaseItr->find("JET_")!=std::string::npos)) shouldAdd = true;
    if(SysFilter.find("btag")!=std::string::npos && (sysbaseItr->find("FT_")!=std::string::npos)) shouldAdd = true;
    if(SysFilter.find("other")!=std::string::npos && (sysbaseItr->find("MET_")!=std::string::npos || sysbaseItr->find("PRW_")!=std::string::npos)) shouldAdd = true;
    if(SysFilter.find("all")!=std::string::npos) shouldAdd = true;
    if(!shouldAdd) continue;

/*
    if(SysFilter == "nominal") break;
    if(SysFilter == "lepton" && sysbaseItr->find("EG_")==std::string::npos && sysbaseItr->find("EL_")==std::string::npos && sysbaseItr->find("MUON_")==std::string::npos && sysbaseItr->find("MET_")==std::string::npos && sysbaseItr->find("PRW_")==std::string::npos) continue;
    if(SysFilter == "hadron" && sysbaseItr->find("JET_")==std::string::npos && sysbaseItr->find("FT_")==std::string::npos) continue;
    if(SysFilter == "electron" && sysbaseItr->find("EG_")==std::string::npos && sysbaseItr->find("EL_")==std::string::npos) continue;
    if(SysFilter == "muon" && sysbaseItr->find("MUON_")==std::string::npos) continue;
    if(SysFilter == "jet" && sysbaseItr->find("JET_")==std::string::npos) continue; 
    if(SysFilter == "btag" && sysbaseItr->find("FT_")==std::string::npos) continue;
    if(SysFilter == "other" && sysbaseItr->find("MET_")==std::string::npos && sysbaseItr->find("PRW_")==std::string::npos) continue;
*/

    CP::SystematicSet shiftSetUp;
    CP::SystematicSet shiftSetDown;
    shiftSetUp.insert(CP::SystematicVariation(*sysbaseItr,1));
    shiftSetDown.insert(CP::SystematicVariation(*sysbaseItr,-1));
    m_sysList.push_back( CP::SystematicSet() );
    m_sysList.back().insert(shiftSetDown);
    if((shiftSetDown).name() == "MET_SoftTrk_ScaleUp__1down") m_sysList.pop_back();
    m_sysList.push_back( CP::SystematicSet() );
    m_sysList.back().insert(shiftSetUp);
    if((shiftSetUp).name() == "MET_SoftTrk_ScaleDown__1up") m_sysList.pop_back();
    std::cout<<"systematic registered: "<<(shiftSetDown).name()<<std::endl;
    std::cout<<"systematic registered: "<<(shiftSetUp).name()<<std::endl;
  }

  for (int isys = 0; isys<m_sysList.size(); isys++){
    sysVari = m_sysList.at(isys);
    assignVariationAffected(sysVari);
  }

  systematicList = new TH1D("systematicList","systematicList",m_sysList.size(),0,m_sysList.size());
  for(int ibs = 1; ibs <= systematicList->GetNbinsX(); ibs++){
    std::string sn = (m_sysList.at(ibs-1)).name();
    std::cout<<sn<<" registered"<<std::endl;
    systematicList->GetXaxis()->SetBinLabel(ibs,sn.c_str());
  }

  init();

  return StatusCode::SUCCESS;
}

StatusCode xAODHelper :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
  Sta_TotalNumber++;
  if(Sta_TotalNumber % 2000 == 0){
     std::cout<<Sta_TotalNumber<<" events have finished."<<std::endl;
   }
//  ANA_MSG_INFO ("in execute");
  event = wk()->xaodEvent();

  ANA_CHECK (event->retrieve (eventInfo, "EventInfo"));
  fileExecute();
  ANA_CHECK (event->retrieve (vxContainer, "PrimaryVertices" ));
 
//  std::cout<<"evtStore pass"<<std::endl;

  if(doTruthSelection) ANA_CHECK (evtStore()->retrieve (xTruthParticleContainer, "TruthParticles"));
  if(doTruthSelection && doJetSelection && !runFwdReco) EL_RETURN_CHECK("loop()",evtStore()->retrieve( Tjets, "AntiKt4TruthJets" ));

  if(doTruthSelection){
    truthPropagator.SetPxPyPzE(0,0,0,0);
    truthParticleList.clear();
    truthParticleList.resize(7);
    truthParticleList[0].SetPxPyPzE(0, 0, 0, 0);
    truthParticleList[1].SetPxPyPzE(0, 0, 0, 0);
    truthParticleList[2].SetPxPyPzE(0, 0, 0, 0);
    pdgSequence = 0;
    std::cout<<"Event:"<<std::endl;
    for(auto tPar : *xTruthParticleContainer){
      (tPar)->auxdecor<char>("isHardElectron") = 0;
      (tPar)->auxdecor<char>("isHardMuon") = 0;
      (tPar)->auxdecor<char>("fwdtruthMatched") = 0;
      (tPar)->auxdecor<char>("fwdtruthMatchedAfterCut") = 0;
      (tPar)->auxdecor<char>("truthMatched") = 0;
      (tPar)->auxdecor<char>("truthMatchedAfterCut") = 0;
      (tPar)->auxdecor<int>("Region") = 0;
      (tPar)->auxdecor<char>("isWZLepton") = 0;
      (tPar)->auxdecor<char>("isBareLepton") = 0;
      (tPar)->auxdecor<char>("isPhoton") = 0;
      (tPar)->auxdecor<float>("dressed_e") = 0.0;
      (tPar)->auxdecor<float>("dressed_eta") = 0.0;
      (tPar)->auxdecor<float>("dressed_phi") = 0.0;
      (tPar)->auxdecor<float>("dressed_pt") = 0.0;
      int pid = (tPar)->pdgId();
      int bcd = (tPar)->barcode();
      int sts = (tPar)->status();
      double energy = (tPar)->e();
      size_t ndada = (tPar)->nParents();
      if(ndada<1) continue;
      if(!((tPar)->parent(0))) continue;
      int mid =(tPar)->parent(0)->pdgId();
      //if(abs(pid)==11 || abs(pid)==13 || abs(pid)==12 || abs(pid)==14 || abs(pid)==22) std::cout<<"pid "<<pid<<", bcd "<<bcd<<", sts "<<sts<<", mid "<<mid<<", dressed pt "<<tPar->auxdata<float>("pt_dressed")<<", dressed e "<<tPar->auxdata<float>("e_dressed")<<", dressed eta "<<tPar->auxdata<float>("eta_dressed")<<", dressed phi "<<tPar->auxdata<float>("phi_dressed")<<std::endl;
      if((eventInfo->mcChannelNumber() >= 364991 && eventInfo->mcChannelNumber() <= 364994)
      || (eventInfo->mcChannelNumber() >= 500290 && eventInfo->mcChannelNumber() <= 501800)
      || (eventInfo->mcChannelNumber() >= 507019)){
//        if(sts==22 && (abs(pid)==24 || abs(pid)==23)) truthPropagator = truthPropagator + (tPar)->p4();
        if((abs(pid)==11 || abs(pid)==13) && sts == 1 && (abs(mid) == 11 || abs(mid) == 13 || abs(mid) == 23 || abs(mid) == 24)){
          (tPar)->auxdecor<char>("isBareLepton") = 1;
          //std::cout<<"bare: pid "<<pid<<", bcd "<<bcd<<", sts "<<sts<<", mid "<<mid<<", dressed pt "<<tPar->auxdata<float>("pt_dressed")<<", dressed e "<<tPar->auxdata<float>("e_dressed")<<", dressed eta "<<tPar->auxdata<float>("eta_dressed")<<", dressed phi "<<tPar->auxdata<float>("phi_dressed")<<std::endl;
          (tPar)->auxdecor<float>("dressed_e") = (tPar)->auxdata<float>("e_dressed");
          (tPar)->auxdecor<float>("dressed_eta") = (tPar)->auxdata<float>("eta_dressed");
          (tPar)->auxdecor<float>("dressed_phi") = (tPar)->auxdata<float>("phi_dressed");
          (tPar)->auxdecor<float>("dressed_pt") = (tPar)->auxdata<float>("pt_dressed");
        }
        if(abs(pid) == 22 && (abs(mid) == 11 || abs(mid) == 13)){
          (tPar)->auxdecor<char>("isPhoton") = 1;
        }
        if(!(abs(mid)==24 || abs(mid)==23)) continue;
        if(abs(pid)>=11 && abs(pid)<=16){
          truthPropagator = truthPropagator + (tPar)->p4();
          truthParticleList[0] = truthParticleList[0]+(tPar)->p4();
          if(abs(mid)==24) truthParticleList[1] = truthParticleList[1]+(tPar)->p4();
          if(abs(mid)==23) truthParticleList[2] = truthParticleList[2]+(tPar)->p4();
          pdgSequence = pdgSequence*1000 + abs(pid);
          (tPar)->auxdecor<char>("isWZLepton") = 1;
        }
//        if(abs(pid)>=11 && abs(pid)<=16) std::cout<<"Event: "<<Sta_TotalNumber<<" pid "<<pid<<", bcd "<<bcd<<", sts "<<sts<<", mid "<<mid<<std::endl;
      }
      if(eventInfo->mcChannelNumber() == 364253){
//        if(sts!=3) continue;
        if(sts!=11) continue;
        if(abs(pid)>=11 && abs(pid)<=16 && ((fabs(mid) >= 1 && fabs(mid) <= 6) || fabs(mid) == 21)){
          truthPropagator = truthPropagator + (tPar)->p4();
          truthParticleList[0] = truthParticleList[0]+(tPar)->p4();
          pdgSequence = pdgSequence*1000 + abs(pid);
          (tPar)->auxdecor<char>("isWZLepton") = 1;
        }
//        if(abs(pid)==11 || abs(pid)==13) std::cout<<"Event: "<<Sta_TotalNumber<<" pid "<<pid<<", bcd "<<bcd<<", sts "<<sts<<", mid "<<mid<<std::endl;
//        if(abs(pid)>=11 && abs(pid)<=16 && ((fabs(mid) >= 1 && fabs(mid) <= 6) || fabs(mid) == 21)) std::cout<<"Event: "<<Sta_TotalNumber<<" pid "<<pid<<", bcd "<<bcd<<", sts "<<sts<<", mid "<<mid<<std::endl;
      }

      else if(!(abs(mid)==24 || abs(mid)==23)) continue;

      if(eventInfo->mcChannelNumber() == 410000 && sts!=3) continue;
      if(eventInfo->mcChannelNumber() <= 361106 && eventInfo->mcChannelNumber() >= 361100 && sts!=3) continue;

      if(abs(pid)==11) {
        (tPar)->auxdecor<char>("isHardElectron") = true;
      }
      if(abs(pid)==13) {
        (tPar)->auxdecor<char>("isHardMuon") = true;
      }

      if(!((tPar)->auxdecor<char>("isHardElectron"))) continue;
      if(fabs((tPar)->eta()) < 2.5){
        (tPar)->auxdecor<int>("Region") = 1;
      }
      if(fabs((tPar)->eta()) > 2.5 && fabs((tPar)->eta()) < 4.9){
       (tPar)->auxdecor<int>("Region") = 2;
      }

    }
  }

  loop();

  m_store->clear();

  return StatusCode::SUCCESS;
}

StatusCode xAODHelper :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.

  finish();

  return StatusCode::SUCCESS;
}

StatusCode xAODHelper::getObjects(){

  if(doOnce){
    if(doFwdElecSelection) ANA_CHECK (evtStore()->retrieve (fwdels, "ForwardElectrons"));
    if(doElecSelection) ANA_CHECK (evtStore()->retrieve (els, "Electrons"));
    if(doMuonSelection) ANA_CHECK (evtStore()->retrieve (muons, "Muons" ));
    if(doJetSelection) ANA_CHECK (evtStore()->retrieve (jets, jetType.c_str() ));
    if(doJetSelection) ANA_CHECK (evtStore()->retrieve (jetsBdecor, jetTypeBtag.c_str()));
    if(doMetCalculation) ANA_CHECK (evtStore()->retrieve(coreMet, coreMetKey));
    if(doMetCalculation) ANA_CHECK (evtStore()->retrieve(metMap, metAssocKey));

    std::pair< xAOD::MuonContainer*, xAOD::ShallowAuxContainer* > muons_shallowCopy;
    std::pair< xAOD::ElectronContainer*, xAOD::ShallowAuxContainer* > els_shallowCopy;
    std::pair< xAOD::ElectronContainer*, xAOD::ShallowAuxContainer* > fwdels_shallowCopy;
    std::pair< xAOD::JetContainer*, xAOD::ShallowAuxContainer* > jets_shallowCopy;

    if(doMuonSelection){
      muons_shallowCopy = xAOD::shallowCopyContainer( *muons );
      m_store->record( muons_shallowCopy.first,  "CalibMuons"    );
      m_store->record( muons_shallowCopy.second, "CalibMuonsAux.");
      muonsCorr = muons_shallowCopy.first;
    }

    if(doElecSelection){
      els_shallowCopy = xAOD::shallowCopyContainer( *els );
      m_store->record( els_shallowCopy.first,  "CalibElectrons"    );
      m_store->record( els_shallowCopy.second, "CalibElectronsAux.");
      elsCorr = els_shallowCopy.first;
    }

    if(doFwdElecSelection){
      fwdels_shallowCopy = xAOD::shallowCopyContainer( *fwdels );
      m_store->record( fwdels_shallowCopy.first,  "CalibFwdElectrons"    );
      m_store->record( fwdels_shallowCopy.second, "CalibFwdElectronsAux.");
      fwdelsCorr = fwdels_shallowCopy.first;
    }

    if(doJetSelection){
      jets_shallowCopy = xAOD::shallowCopyContainer( *jetsBdecor );
      m_store->record( jets_shallowCopy.first,  "CalibJets"    );
      m_store->record( jets_shallowCopy.second, "CalibJetsAux.");
      jetsCorr = jets_shallowCopy.first;
    }

    metsCorr = new TLorentzVector();
    m_store->record( metsCorr, "CalibMets" );

    fwdelectronMap = new std::map<double, xAOD::Electron *>();
    electronMap = new std::map<double, xAOD::Electron *>();
    muonMap = new std::map<double, xAOD::Muon *>();
    jetMap = new std::map<double, xAOD::Jet *>();

    m_store->record( fwdelectronMap,  "SelectFwdElectrons"    );
    m_store->record( electronMap,  "SelectElectrons"    );
    m_store->record( muonMap,  "SelectMuons"    );
    m_store->record( jetMap,  "SelectJets"    );
  }
  else{
    if(doFwdElecSelection) EL_RETURN_CHECK("loop()",m_store->retrieve( fwdelsNominal,  "CalibFwdElectrons"    ));
    if(doElecSelection) EL_RETURN_CHECK("loop()",m_store->retrieve( elsNominal,  "CalibElectrons"    ));
    if(doMuonSelection) EL_RETURN_CHECK("loop()",m_store->retrieve( muonsNominal,  "CalibMuons"    ));
    if(doJetSelection) EL_RETURN_CHECK("loop()",m_store->retrieve( jetsNominal,  "CalibJets"    ));
    if(doMetCalculation) EL_RETURN_CHECK("loop()",m_store->retrieve( metsNominal,  "CalibMets"    ));
    if(doFwdElecSelection) EL_RETURN_CHECK("loop()",m_store->retrieve( fwdelectronMapNominal,  "SelectFwdElectrons"    ));
    if(doElecSelection) EL_RETURN_CHECK("loop()",m_store->retrieve( electronMapNominal,  "SelectElectrons"    ));
    if(doMuonSelection) EL_RETURN_CHECK("loop()",m_store->retrieve( muonMapNominal,  "SelectMuons"    ));
    if(doJetSelection) EL_RETURN_CHECK("loop()",m_store->retrieve( jetMapNominal,  "SelectJets"    ));

    std::pair< xAOD::MuonContainer*, xAOD::ShallowAuxContainer* > muons_shallowCopy;
    std::pair< xAOD::ElectronContainer*, xAOD::ShallowAuxContainer* > els_shallowCopy;
    std::pair< xAOD::ElectronContainer*, xAOD::ShallowAuxContainer* > fwdels_shallowCopy;
    std::pair< xAOD::JetContainer*, xAOD::ShallowAuxContainer* > jets_shallowCopy;

    if(doMuonSelection){
      muons_shallowCopy = xAOD::shallowCopyContainer( *muonsNominal );
      m_store->record( muons_shallowCopy.first,  sysname+"CalibMuons"    );
      m_store->record( muons_shallowCopy.second, sysname+"CalibMuonsAux.");
      muonsCorr = muons_shallowCopy.first;
    }

    if(doElecSelection){
      els_shallowCopy = xAOD::shallowCopyContainer( *elsNominal );
      m_store->record( els_shallowCopy.first,  sysname+"CalibElectrons"    );
      m_store->record( els_shallowCopy.second, sysname+"CalibElectronsAux.");
      elsCorr = els_shallowCopy.first;
    }

    if(doFwdElecSelection){
      fwdels_shallowCopy = xAOD::shallowCopyContainer( *fwdelsNominal );
      m_store->record( fwdels_shallowCopy.first,  sysname+"CalibFwdElectrons"    );
      m_store->record( fwdels_shallowCopy.second, sysname+"CalibFwdElectronsAux.");
      fwdelsCorr = fwdels_shallowCopy.first;
    }

    if(doJetSelection){
      jets_shallowCopy = xAOD::shallowCopyContainer( *jetsNominal );
      m_store->record( jets_shallowCopy.first,  sysname+"CalibJets"    );
      m_store->record( jets_shallowCopy.second, sysname+"CalibJetsAux.");
      jetsCorr = jets_shallowCopy.first;
    }

    metsCorr = new TLorentzVector();
    if(doMetCalculation) *metsCorr = *metsNominal;
    m_store->record( metsCorr, sysname+"CalibMets" );

    fwdelectronMap = new std::map<double, xAOD::Electron *>();
    electronMap = new std::map<double, xAOD::Electron *>();
    muonMap = new std::map<double, xAOD::Muon *>();
    jetMap = new std::map<double, xAOD::Jet *>();

    if(doFwdElecSelection) *fwdelectronMap = *fwdelectronMapNominal;
    if(doElecSelection) *electronMap = *electronMapNominal;
    if(doMuonSelection) *muonMap = *muonMapNominal;
    if(doJetSelection) *jetMap = *jetMapNominal;

    m_store->record( fwdelectronMap,  sysname+"SelectFwdElectrons"    );
    m_store->record( electronMap,  sysname+"SelectElectrons"    );
    m_store->record( muonMap,  sysname+"SelectMuons"    );
    m_store->record( jetMap,  sysname+"SelectJets"    );


  }

  if(doMuonSelection){
    if(!xAOD::setOriginalObjectLink(*muons, *muonsCorr)) std::cout << "Failed to set the original object links" << std::endl;
  }
  if(doFwdElecSelection){
    if(!xAOD::setOriginalObjectLink(*fwdels, *fwdelsCorr)) std::cout << "Failed to set the original object links" << std::endl;
  }
  if(doElecSelection){
    if(!xAOD::setOriginalObjectLink(*els, *elsCorr)) std::cout << "Failed to set the original object links" << std::endl;
  }
  if(doJetSelection){
    if(!xAOD::setOriginalObjectLink(*jets, *jetsCorr)) std::cout << "Failed to set the original object links" << std::endl;
  }

  return StatusCode::SUCCESS;
}

void xAODHelper::assignVariationAffected(CP::SystematicSet sysVari){
    affectedArea[sysVari]="None";
    CP::SystematicSet sysVariBase;
    if(!sysVari.getBaseNames().empty()) sysVariBase.insert(CP::SystematicVariation(*(sysVari.getBaseNames().begin())));
    if(AFFECT_CHECK( m_muonCalibrationAndSmearingTool, sysVari )) affectedArea[sysVari] = "muon_calibration";
    if(AFFECT_CHECK( m_EleCalibTool, sysVari )) affectedArea[sysVari] = "electron_calibration";
    if(AFFECT_CHECK( m_jesUncert, sysVari )) affectedArea[sysVari] = "jet_calibration";
    if(AFFECT_CHECK( metSystTool, sysVariBase )) affectedArea[sysVari] = "met_calibration";
    if(AFFECT_CHECK( m_effi_corr1, sysVari )) affectedArea[sysVari] = "muon_ID_efficiency";
    if(AFFECT_CHECK( m_effi_corr2, sysVari )) affectedArea[sysVari] = "muon_ID_efficiency";
    //if(AFFECT_CHECK( m_iso_effi_corr1, sysVari )) affectedArea[sysVari] = "muon_iso_efficiency";
    //if(AFFECT_CHECK( m_iso_effi_corr2, sysVari )) affectedArea[sysVari] = "muon_iso_efficiency";
    //if(AFFECT_CHECK( m_iso_effi_corr3, sysVari )) affectedArea[sysVari] = "muon_iso_efficiency";
    //if(AFFECT_CHECK( m_iso_effi_corr4, sysVari )) affectedArea[sysVari] = "muon_iso_efficiency";
    if(AFFECT_CHECK( m_iso_effi_corr5, sysVari )) affectedArea[sysVari] = "muon_iso_efficiency";
    if(AFFECT_CHECK( m_iso_effi_corr6, sysVari )) affectedArea[sysVari] = "muon_iso_efficiency";
    if(AFFECT_CHECK( m_iso_effi_corr7, sysVari )) affectedArea[sysVari] = "muon_iso_efficiency";
    if(AFFECT_CHECK( m_ip_effi_corr, sysVari )) affectedArea[sysVari] = "muon_TTVA_efficiency";
    if(AFFECT_CHECK( m_recoEgCorrections, sysVari )) affectedArea[sysVari] = "electron_reco_efficiency";
    if(AFFECT_CHECK( m_idEgCorrections2, sysVari )) affectedArea[sysVari] = "electron_ID_efficiency";
    if(AFFECT_CHECK( m_idEgCorrections3, sysVari )) affectedArea[sysVari] = "electron_ID_efficiency";
    if(AFFECT_CHECK( m_idFwdEgCorrections1, sysVari )) affectedArea[sysVari] = "electron_fwdID_efficiency";
    if(AFFECT_CHECK( m_idFwdEgCorrections2, sysVari )) affectedArea[sysVari] = "electron_fwdID_efficiency";
    if(AFFECT_CHECK( m_idFwdEgCorrections3, sysVari )) affectedArea[sysVari] = "electron_fwdID_efficiency";
    if(AFFECT_CHECK( m_isoEgCorrections2, sysVari )) affectedArea[sysVari] = "electron_iso_efficiency";
    if(AFFECT_CHECK( m_isoEgCorrections3, sysVari )) affectedArea[sysVari] = "electron_iso_efficiency";
    if(AFFECT_CHECK( m_isoEgCorrections4, sysVari )) affectedArea[sysVari] = "electron_iso_efficiency";
    if(AFFECT_CHECK( m_isoEgCorrections5, sysVari )) affectedArea[sysVari] = "electron_iso_efficiency";
    if(AFFECT_CHECK( m_isoEgCorrections6, sysVari )) affectedArea[sysVari] = "electron_iso_efficiency";
    if(AFFECT_CHECK( m_isoEgCorrections7, sysVari )) affectedArea[sysVari] = "electron_iso_efficiency";
    if(AFFECT_CHECK( m_isoEgCorrections8, sysVari )) affectedArea[sysVari] = "electron_iso_efficiency";
    if(AFFECT_CHECK( m_isoEgCorrections9, sysVari )) affectedArea[sysVari] = "electron_iso_efficiency";
    if(AFFECT_CHECK( m_isoEgCorrections10, sysVari )) affectedArea[sysVari] = "electron_iso_efficiency";
    if(AFFECT_CHECK( m_trigEgEfficienciesMC1, sysVari )) affectedArea[sysVari] = "electron_trig_efficiency";
    if(AFFECT_CHECK( m_trigEgCorrections1, sysVari )) affectedArea[sysVari] = "electron_trig_efficiency";
    if(AFFECT_CHECK( m_trigEgEfficienciesMC2, sysVari )) affectedArea[sysVari] = "electron_trig_efficiency";
    if(AFFECT_CHECK( m_trigEgCorrections2, sysVari )) affectedArea[sysVari] = "electron_trig_efficiency";
    if(AFFECT_CHECK( m_trigEgEfficienciesMC3, sysVari )) affectedArea[sysVari] = "electron_trig_efficiency";
    if(AFFECT_CHECK( m_trigEgCorrections3, sysVari )) affectedArea[sysVari] = "electron_trig_efficiency";
    if(AFFECT_CHECK( m_trigEgEfficienciesMC4, sysVari )) affectedArea[sysVari] = "electron_trig_efficiency";
    if(AFFECT_CHECK( m_trigEgCorrections4, sysVari )) affectedArea[sysVari] = "electron_trig_efficiency";
    if(AFFECT_CHECK( m_mutrig_sf, sysVari )) affectedArea[sysVari] = "muon_trig_efficiency";
    if(AFFECT_CHECK( m_mutrig_sf_m, sysVari )) affectedArea[sysVari] = "muon_trig_efficiency";
    if(AFFECT_CHECK( m_prwTool, sysVari )) affectedArea[sysVari] = "pileup";
    if(AFFECT_CHECK( jvtsf, sysVari )) affectedArea[sysVari] = "jet_jvt_efficiency";
    if(AFFECT_CHECK( fjvtsf, sysVari )) affectedArea[sysVari] = "jet_fjvt_efficiency";
    if(AFFECT_CHECK( btagefftool, sysVari )) affectedArea[sysVari] = "jet_btag_efficiency";
}

xAODHelper::~xAODHelper()
{

}
