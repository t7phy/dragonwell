#include "NtupleMaker/SkimToNtupleFwdReco.h"

//////////////////////////////////////////////
//
//  This is another way to store the skimmed ntuple
//
/////////////////////////////////////////////

SkimToNtupleFwdReco :: SkimToNtupleFwdReco (const std::string& name,
                                  ISvcLocator *pSvcLocator)
    : SelectionFwdReco (name, pSvcLocator)
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

  runFwdReco = true;
}

bool SkimToNtupleFwdReco :: init ()
{
  SelectionFwdReco::init();

  TFile *outputFile = wk()->getOutputFile (outputName);

  treeAnaSys =  new std::vector<TTree*>();

  metaTree =  new TTree("metaTree","metaTree");
  metaTree->Branch("runNumber", &runNumber);
  metaTree->Branch("mcChannelNumber", &mcChannelNumber);
  metaTree->Branch("totalWeightedEntries", &sumOfWeights);
  metaTree->Branch("crossSection", &crossSection);
  metaTree->Branch("inputFileName", &AODname);
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
  treeAnaSys->resize(n_sys);
  std::cout<<"n_sys: "<<n_sys<<std::endl;

  for(int isys=0; isys<n_sys; isys++){

    std::string sysname = m_sysList.at(isys).name();
    std::string treename = "SelectedEvents_";
    if(sysname == "") treename = treename + "nominal";
    else treename = treename + sysname;
    std::cout<<"registered "<<sysname<<std::endl;
    (treeAnaSys->at(isys)) = new TTree(treename.c_str(),treename.c_str());
    (treeAnaSys->at(isys))->SetDirectory(outputFile);
    SetupBranches(treeAnaSys->at(isys));

  }

  return true;

}

bool SkimToNtupleFwdReco :: loop ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  //Clear or init the output branches each loop
  int isys = -1;
  for (auto sysVari : m_sysList){
    isys++;
    std::string sysname = sysVari.name();
    if(!isMC && sysname!="") continue;
    if(maxSys >= 0 && isys > maxSys) continue;

    ResetEvent();

    if(!doSystematicVariation(sysVari)) Error("loop()", "Systematic Unsupported");

    doOnce = (sysname=="");
    if(!SelectionFwdReco::loop()) continue;

    AverageMu = eventInfo->auxdata<float>("corrected_averageInteractionsPerCrossing");//= eventInfo->averageInteractionsPerCrossing();
    OriginRunNumber = eventInfo->runNumber();
    ChannelNumber = isMC?(eventInfo->mcChannelNumber()):0;
    RunNumber = RunNum;
    EventNumber = EvtNum;
    TriggerPassed = isTriggerPassed;

    float mcEventWeight = 1.;
    float mcWeightPRW = 1.;

    if(isMC){
      // Apply MC event weight
      mcEventWeight = eventInfo->mcEventWeight();

      // Apply pile-up reweighting 
      mcWeightPRW = eventInfo->auxdata< float >("PileupWeight");

      MCEventWeight = mcEventWeight;
      MCPileupWeight = mcWeightPRW;
    }

    met_et = metsCorr->Pt();
    met_px = metsCorr->Px();
    met_py = metsCorr->Py();

    if(1){

      std::map<double, xAOD::Muon *>::iterator muonIter; //!
      std::map<double, xAOD::Electron *>::iterator electronIter; //!
      std::map<double, xAOD::Electron *>::iterator fwdelectronIter;
      std::map<double, xAOD::Jet *>::iterator jetIter; //!

      for(  fwdelectronIter = (*fwdelectronMap).begin(); fwdelectronIter != (*fwdelectronMap).end(); fwdelectronIter++  ){

//        outputCaloInfo(fwdelectronIter->second);
        Record_Object((fwdelectronIter->second), "fwdel");

      }

      for(  electronIter = (*electronMap).begin(); electronIter != (*electronMap).end(); electronIter++  ){

        Record_Object((electronIter->second), "elec");

      }

      for(  auto tPar : *xTruthParticleContainer  ){
        deltaE = 0.0;
        deltaPt = 0.0;
        deltaEt = 0.0;
        if(!((tPar)->auxdecor<char>("isHardElectron"))) continue;

        for(  fwdelectronIter = (*fwdelectronMap).begin(); fwdelectronIter != (*fwdelectronMap).end(); fwdelectronIter++  ){
          double tdr = ((fwdelectronIter->second)->p4()).DeltaR((tPar)->p4());
          if(tdr<0.4){
            (tPar)->auxdecor<char>("fwdtruthMatched") = true;
            deltaE = ((fwdelectronIter->second)->e() - (tPar)->e()) / (tPar)->e();
            deltaPt = ((fwdelectronIter->second)->pt() - (tPar)->pt()) / (tPar)->pt();
            deltaEt = ((fwdelectronIter->second)->caloCluster()->pt() - (tPar)->p4().Et()) / (tPar)->p4().Et();
          }

          if(!(fwdelectronIter->second)->auxdecor<char>("PassPtCut")) continue;
          if(tdr<0.4){
            (tPar)->auxdecor<char>("fwdtruthMatchedAfterCut") = true;
          }
        }

        Record_Object((tPar), "truth");

      }

      for(  muonIter = (*muonMap).begin(); muonIter != (*muonMap).end(); muonIter++  ){

        Record_Object((muonIter->second), "muon");

      }

      for(  jetIter = (*jetMap).begin(); jetIter != (*jetMap).end(); jetIter++  ){

        Record_Object((jetIter->second), "jet");

      }

      if(1){//!hasBadJet
//        updateCutFlow(event_CutFlow, event_CutNameMap, "jet cleaning", 1, doOnce);
        treeAnaSys->at(isys)->Fill();
//        if( (treeAnaSys->at(isys)->GetEntries() % 1000) ==0 ) treeAnaSys->at(isys)->AutoSave("Overwrite");
      }


    }

  }

  return true;
} // end of loop

StatusCode SkimToNtupleFwdReco :: finish ()
{

  SelectionHelper::finish();

  for(int it=0;it<vec_AODname->size();it++){
    runNumber = vec_runNumber->at(it);
    mcChannelNumber = vec_mcChannelNumber->at(it);
    sumOfWeights = vec_sumOfWeights->at(it);
    AODname = vec_AODname->at(it);
    std::cout<<"bookkeeping "<<AODname<<", "<<sumOfWeights<<std::endl;
    metaTree->Fill();
  }

  return StatusCode::SUCCESS;

}

void SkimToNtupleFwdReco::SetupBranches(TTree* tree)
{
  tree->Branch("fwdel_e", "vector<float>", &fwdel_e);
  tree->Branch("fwdel_eta", "vector<float>", &fwdel_eta);
  tree->Branch("fwdel_phi", "vector<float>", &fwdel_phi);
  tree->Branch("fwdel_pt", "vector<float>", &fwdel_pt);
  tree->Branch("fwdel_clpt", "vector<float>", &fwdel_clpt);
  tree->Branch("fwdel_PassPtCut", "vector<int>", &fwdel_PassPtCut);
  tree->Branch("fwdel_truthMatched", "vector<int>", &fwdel_truthMatched);

  tree->Branch("fwdel_corrected_e", "vector<float>", &fwdel_corrected_e);
  tree->Branch("fwdel_corrected_eta", "vector<float>", &fwdel_corrected_eta);
  tree->Branch("fwdel_corrected_phi", "vector<float>", &fwdel_corrected_phi);
  tree->Branch("fwdel_corrected_pt", "vector<float>", &fwdel_corrected_pt);
  tree->Branch("fwdel_corrected_clpt", "vector<float>", &fwdel_corrected_clpt);
  tree->Branch("fwdel_corrected_PassPtCut", "vector<int>", &fwdel_corrected_PassPtCut);
  tree->Branch("fwdel_corrected_truthMatched", "vector<int>", &fwdel_corrected_truthMatched);

  tree->Branch("truthel_e", "vector<float>", &truthel_e);
  tree->Branch("truthel_eta", "vector<float>", &truthel_eta);
  tree->Branch("truthel_phi", "vector<float>", &truthel_phi);
  tree->Branch("truthel_pt", "vector<float>", &truthel_pt);
  tree->Branch("truthel_et", "vector<float>", &truthel_et);
  tree->Branch("truthel_deltaE", "vector<float>", &truthel_deltaE);
  tree->Branch("truthel_deltaPt", "vector<float>", &truthel_deltaPt);
  tree->Branch("truthel_deltaEt", "vector<float>", &truthel_deltaEt);
  tree->Branch("truthel_Region", "vector<int>", &truthel_Region);
  tree->Branch("truthel_truthMatched", "vector<int>", &truthel_truthMatched);
  tree->Branch("truthel_truthMatchedAfterCut", "vector<int>", &truthel_truthMatchedAfterCut);

  tree->Branch("EventNumber", &EventNumber, "EventNumber/I");
  tree->Branch("AverageMu", &AverageMu, "AverageMu/F");
  tree->Branch("EventRegion", &EventRegion, "EventRegion/I");


}

void SkimToNtupleFwdReco::ResetEvent(void)
{
  AverageMu = -999;
  EventRegion = -999;

  fwdel_e.clear() ;
  fwdel_eta.clear() ;
  fwdel_phi.clear() ;
  fwdel_pt.clear() ;
  fwdel_clpt.clear() ;
  fwdel_PassPtCut.clear();
  fwdel_truthMatched.clear() ;

  fwdel_corrected_e.clear() ;
  fwdel_corrected_eta.clear() ;
  fwdel_corrected_phi.clear() ;
  fwdel_corrected_pt.clear() ;
  fwdel_corrected_clpt.clear() ;
  fwdel_corrected_PassPtCut.clear();
  fwdel_corrected_truthMatched.clear() ;

  el_e.clear() ;
  el_eta.clear() ;
  el_phi.clear() ;
  el_pt.clear() ;
  el_clpt.clear() ;

  truthel_e.clear() ;
  truthel_eta.clear() ;
  truthel_phi.clear() ;
  truthel_pt.clear() ;
  truthel_et.clear() ;
  truthel_deltaE.clear() ;
  truthel_deltaPt.clear() ;
  truthel_deltaEt.clear() ;
  truthel_Region.clear();
  truthel_truthMatched.clear() ;
  truthel_truthMatchedAfterCut.clear();

}

void SkimToNtupleFwdReco::Record_Object(const xAOD::IParticle* par, std::string flavor)
{
  if(flavor == "fwdel"){
    xAOD::Electron* fwdel = (xAOD::Electron *)par;

    fwdel_e.push_back( (fwdel)->e() );
    fwdel_eta.push_back( (fwdel)->eta() );
    fwdel_phi.push_back( (fwdel)->phi() );
    fwdel_pt.push_back( (fwdel)->pt() );
    fwdel_clpt.push_back( (fwdel)->caloCluster()->pt() );
    fwdel_PassPtCut.push_back( (fwdel)->auxdecor<char>("PassPtCut") );
    fwdel_truthMatched.push_back( (fwdel)->auxdecor<char>("truthMatched") );

  }

  if(flavor == "elec"){
    xAOD::Electron* el = (xAOD::Electron*)par;

    el_e.push_back( (el)->e() );
    el_eta.push_back( (el)->eta() );
    el_phi.push_back( (el)->phi() );
    el_pt.push_back( (el)->pt() );
    el_clpt.push_back( (el)->caloCluster()->pt() );

  }

  if(flavor == "muon"){
    xAOD::Muon* mu = (xAOD::Muon*)par;


  }

  if(flavor == "truth"){
    xAOD::TruthParticle* tPar = (xAOD::TruthParticle *)par;

    truthel_e.push_back( (tPar)->e() );
    truthel_eta.push_back( (tPar)->eta() );
    truthel_phi.push_back( (tPar)->phi() );
    truthel_pt.push_back( (tPar)->pt() );
    truthel_et.push_back( (tPar)->p4().Et() );
    truthel_deltaE.push_back( deltaE );
    truthel_deltaPt.push_back( deltaPt );
    truthel_deltaEt.push_back( deltaEt );
    truthel_Region.push_back( (tPar)->auxdecor<int>("Region"));
    truthel_truthMatched.push_back( (tPar)->auxdecor<char>("fwdtruthMatched") );
    truthel_truthMatchedAfterCut.push_back( (tPar)->auxdecor<char>("fwdtruthMatchedAfterCut") );

  }


  if(flavor == "jet"){
    xAOD::Jet* jt = (xAOD::Jet*)par;


  }

}

void SkimToNtupleFwdReco::outputCaloInfo(xAOD::Electron *fwdel)
{
    std::cout<<"fwd electron e = "<<(fwdel)->e()<<"  pt = "<<(fwdel)->pt()<<std::endl;
    std::cout<<"nCaloClusters: "<<(fwdel)->nCaloClusters()<<" caloCluster: "<<(fwdel)->caloCluster()<<std::endl;
    std::cout<<"cluster e: "<<(fwdel)->caloCluster()->e()<<" cluster pt: "<<(fwdel)->caloCluster()->pt()<<" cluster eta: "<<(fwdel)->caloCluster()->eta()<<" cluster phi: "<<(fwdel)->caloCluster()->phi()<<std::endl;
    std::cout<<"calibrated cluster e: "<<(fwdel)->caloCluster()->calE()<<" calibrated cluster eta: "<<(fwdel)->caloCluster()->calEta()<<" calibrated cluster phi: "<<(fwdel)->caloCluster()->calPhi()<<std::endl;
    std::cout<<"raw cluster e: "<<(fwdel)->caloCluster()->rawE()<<" raw cluster eta: "<<(fwdel)->caloCluster()->rawEta()<<" raw cluster phi: "<<(fwdel)->caloCluster()->rawPhi()<<std::endl;
    std::cout<<"alt cluster e: "<<(fwdel)->caloCluster()->altE()<<" alt cluster eta: "<<(fwdel)->caloCluster()->altEta()<<" alt cluster phi: "<<(fwdel)->caloCluster()->altPhi()<<std::endl;
    std::cout<<"Cluster energy in presampler: "<<(fwdel)->caloCluster()->energyBE(0)<<" Cluster energy in sampling 1: "<<(fwdel)->caloCluster()->energyBE(1)<<" Cluster energy in sampling 2: "<<(fwdel)->caloCluster()->energyBE(2)<<" Cluster energy in sampling 3: "<<(fwdel)->caloCluster()->energyBE(3)<<std::endl;
    std::cout<<"Cluster eta in presampler: "<<(fwdel)->caloCluster()->etaBE(0)<<" Cluster eta in sampling 1: "<<(fwdel)->caloCluster()->etaBE(1)<<" Cluster eta in sampling 2: "<<(fwdel)->caloCluster()->etaBE(2)<<" Cluster eta in sampling 3: "<<(fwdel)->caloCluster()->etaBE(3)<<std::endl;
    std::cout<<"Cluster phi in presampler: "<<(fwdel)->caloCluster()->phiBE(0)<<" Cluster phi in sampling 1: "<<(fwdel)->caloCluster()->phiBE(1)<<" Cluster phi in sampling 2: "<<(fwdel)->caloCluster()->phiBE(2)<<" Cluster phi in sampling 3: "<<(fwdel)->caloCluster()->phiBE(3)<<std::endl;
    std::cout<<"Cluster eta in calorimeter frame: "<<(fwdel)->caloCluster()->getMomentValue(xAOD::CaloCluster::ETACALOFRAME)<<" Cluster phi in calorimeter frame: "<<(fwdel)->caloCluster()->getMomentValue(xAOD::CaloCluster::PHICALOFRAME)<<std::endl;
    std::cout<<"Cluster eta in sampling 1: "<<(fwdel)->caloCluster()->getMomentValue(xAOD::CaloCluster::ETA1CALOFRAME)<<" Cluster phi in sampling 1: "<<(fwdel)->caloCluster()->getMomentValue(xAOD::CaloCluster::PHI1CALOFRAME)<<std::endl;
    std::cout<<"Cluster eta in sampling 2: "<<(fwdel)->caloCluster()->getMomentValue(xAOD::CaloCluster::ETA2CALOFRAME)<<" Cluster phi in sampling 2: "<<(fwdel)->caloCluster()->getMomentValue(xAOD::CaloCluster::PHI2CALOFRAME)<<std::endl;

    std::cout<<"eta size in PreSamplerB: "<<(fwdel)->caloCluster()->etasize(CaloSampling::PreSamplerB)<<" phi size in PreSamplerB: "<<(fwdel)->caloCluster()->phisize(CaloSampling::PreSamplerB)<<std::endl;
    std::cout<<"eta size in EMB1: "<<(fwdel)->caloCluster()->etasize(CaloSampling::EMB1)<<" phi size in EMB1: "<<(fwdel)->caloCluster()->phisize(CaloSampling::EMB1)<<std::endl;
    std::cout<<"eta size in EMB2: "<<(fwdel)->caloCluster()->etasize(CaloSampling::EMB2)<<" phi size in EMB2: "<<(fwdel)->caloCluster()->phisize(CaloSampling::EMB2)<<std::endl;
    std::cout<<"eta size in EMB3: "<<(fwdel)->caloCluster()->etasize(CaloSampling::EMB3)<<" phi size in EMB3: "<<(fwdel)->caloCluster()->phisize(CaloSampling::EMB3)<<std::endl;
    std::cout<<"eta size in PreSamplerE: "<<(fwdel)->caloCluster()->etasize(CaloSampling::PreSamplerE)<<" phi size in PreSamplerE: "<<(fwdel)->caloCluster()->phisize(CaloSampling::PreSamplerE)<<std::endl;
    std::cout<<"eta size in EME1: "<<(fwdel)->caloCluster()->etasize(CaloSampling::EME1)<<" phi size in EME1: "<<(fwdel)->caloCluster()->phisize(CaloSampling::EME1)<<std::endl;
    std::cout<<"eta size in EME2: "<<(fwdel)->caloCluster()->etasize(CaloSampling::EME2)<<" phi size in EME2: "<<(fwdel)->caloCluster()->phisize(CaloSampling::EME2)<<std::endl;
    std::cout<<"eta size in EME3: "<<(fwdel)->caloCluster()->etasize(CaloSampling::EME3)<<" phi size in EME3: "<<(fwdel)->caloCluster()->phisize(CaloSampling::EME3)<<std::endl;
    std::cout<<"eta size in FCAL0: "<<(fwdel)->caloCluster()->etasize(CaloSampling::FCAL0)<<" phi size in FCAL0: "<<(fwdel)->caloCluster()->phisize(CaloSampling::FCAL0)<<std::endl;
    std::cout<<"eta size in FCAL1: "<<(fwdel)->caloCluster()->etasize(CaloSampling::FCAL1)<<" phi size in FCAL1: "<<(fwdel)->caloCluster()->phisize(CaloSampling::FCAL1)<<std::endl;
    std::cout<<"eta size in FCAL2: "<<(fwdel)->caloCluster()->etasize(CaloSampling::FCAL2)<<" phi size in FCAL2: "<<(fwdel)->caloCluster()->phisize(CaloSampling::FCAL2)<<std::endl;
    std::cout<<"Cluster size: "<<(fwdel)->caloCluster()->clusterSize()<<" Cluster eta size: "<<(fwdel)->caloCluster()->getClusterEtaSize()<<" Cluster phi size: "<<(fwdel)->caloCluster()->getClusterPhiSize()<<std::endl;

    std::cout<<std::endl;

}
