#ifndef LJAlgo_H
#define LJAlgo_H

#include "TTree.h"

#include <LJAlgo/LJTree.h>

// algorithm wrapper
#include "xAODAnaHelpers/Algorithm.h"

// external tools include(s):
#include "AsgTools/AnaToolHandle.h"
#include "TrigConfInterfaces/ITrigConfigTool.h"
#include "TrigDecisionTool/TrigDecisionTool.h"
#include "PMGAnalysisInterfaces/IPMGCrossSectionTool.h"
#include "PMGTools/PMGCrossSectionTool.h"
#include "PMGTools/PMGTruthWeightTool.h"
#include <PathResolver/PathResolver.h>
#include "AsgAnalysisInterfaces/ITruthClassificationTool.h"
#include "TruthClassification/TruthClassificationTool.h"

//yfu add individual scale factors
#include "EgammaAnalysisInterfaces/IAsgElectronEfficiencyCorrectionTool.h"
#include "ElectronEfficiencyCorrection/AsgElectronEfficiencyCorrectionTool.h"

class LJAlgo : public xAH::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
  // Note: EventLoop requires to put "//!" after non-configuration variables,
  //       see https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/EventLoop

public:

  bool m_outHistDir = false;
  bool m_skipNominal = false;
  bool m_sortL1Jets = false;
  bool m_retrievePV = true;

  // cross section file to be read out by PMGCrossSectionTool
  std::string m_crossSectionFile = "";

  // holds booleans that control which branches are filled
  std::string m_evtDetailStr = "";
  std::string m_trigDetailStr = "";
  std::string m_muDetailStr = "";
  std::string m_elDetailStr = "";
  std::string m_tauDetailStr = "";
  std::string m_truthParticlesDetailStr = "";
  std::string m_jetDetailStr = "";
  std::string m_truthJetDetailStr = "";
  std::string m_METDetailStr = "";

  // possibility to store less info for systematics
  std::string m_evtDetailStrSyst = "";
  std::string m_muDetailStrSyst = "";
  std::string m_elDetailStrSyst = "";
  std::string m_jetDetailStrSyst = "";
  std::string m_METDetailStrSyst = "";

  std::string m_truthmuContainerName = "";
  std::string m_truthelContainerName = "";
  std::string m_truthtauContainerName = "";
  std::string m_truthjetContainerName = "";
  
  std::string m_evtContainerName = "";
  std::string m_muContainerName = "";
  std::string m_elContainerName = "";
  std::string m_tauContainerName = "";
  std::string m_jetContainerName = "";
  std::string m_METContainerName = "";

  std::string m_truthmuBranchName = "truth_muon";
  std::string m_truthelBranchName = "truth_el";
  std::string m_truthjetBranchName = "truth_jet";
  std::string m_muBranchName = "muon";
  std::string m_elBranchName = "el";
  std::string m_jetBranchName = "jet";
  std::string m_METBranchName = "met";

  // if these are set, assume systematics are being processed over
  std::string m_muSystsName = "";
  std::string m_elSystsName = "";
  std::string m_tauSystsName = "";
  std::string m_jetSystsName = "";
  std::string m_btagSystsName = "";
  std::string m_metSystsName = "";

  std::string m_triggerList = "";

  // flag to not apply any skimming
  bool m_noSkim = false;

  // threshold of leading jet pT in GeV for LJ skimming
  float m_leadJetPtSkim = 100.0;

  // threshold of leading lep pT in GeV for LJ skimming
  float m_leadLepPtSkim = 50.0;

  // threshold of invariant mass of leading lepton and jet in GeV for LJ skimming
  float m_mLepJetSkim = 10.0;

  // threshold of invariant mass of leading leptons in GeV for LJ skimming
  float m_mLepLepSkim = 70.0;

  /// unit conversion from MeV, default is GeV
  float m_units = 1e3;

  // set to a large negative number, such as -1000000, to ensure that the tree flushes memory after a reasonable amount of time. Otherwise, jobs with a lot of systematics use too much memory.
  int m_autoFlush = 0;

  // set to smaller number e.g. 2000 bytes to reduce memory consumption
  int m_treeBasketSize = -1;

  // If input is MC, as automatically determined from xAOD::EventInfo::IS_SIMULATION
  bool m_isMC;

  // flag to turn of trigger matching and calculation of trigger SFs
  bool m_doTrigMatch = true;

  // needed to access SFs
  
  // Trigger
  std::string m_dielWP_IsoTrig;
  std::string m_dielWP_Trig;
  std::string m_elWP_Trig;
  std::string m_muWP_Trig15;
  std::string m_muWP_Trig;
  
  std::string m_elWP_Reco;
  std::string m_elWP_Iso;
  std::string m_elWP_IsoTrig;
  std::string m_elWP_ID;
  std::string m_muWP_Reco;
  std::string m_muWP_Iso;
  std::string m_muWP_TTVA;

  // needed to access b-tag SFs
  std::string m_BtaggerName;
  std::string m_BtaggerWP;
  // needed to decide on cut for pseudo-continuous WPs
  int m_BtaggerCut; 

  // toggling writing a branch for every efficiency threshold in continuous WP case, not just the one set by m_BtaggerCut
  bool m_writeAllBTagWPs = false;

  // flag to activate vector lepton branches in tree
  bool m_writeLeptonVectorBranches = false;

  // flag to activate vector truth lepton branches in tree
  bool m_writeTruthLeptonBranches = false;

  // flag to activate vector truth jet branches in tree
  bool m_writeTruthJetBranches = false;

  // flag to loosen LepPlusJet Selection to allow baseline leptons
  bool m_writeDiLepton = false;

  // flag to loosen LepPlusJet Selection to allow baseline leptons //yfu combine jetfake
  bool m_writeSingleElectron = false;

  // flag to loosen LepPlusJet Selection to allow baseline leptons
  bool m_writeLeptonJet = false;
  
  // flag to save events with electrons
  bool m_writeEleChannel = true;
  
  // flag to save events with muons
  bool m_writeMuonChannel = true;

  // flag to loosen LepPlusJet Selection to allow baseline leptons
  bool m_writeBaseLeptons = false;

  // flag to activate vector tau branches in tree
  bool m_useTaus = false;

  // flag to propagate decision on doing systematics or not to LJAlgo
  bool m_doSystematics = false;

  // flag to propagate decision on doing weight systematics or not to LJAlgo (is automatically true when m_doSystematics is true)
  bool m_doWeightSystematics = false;


protected:

  // flag to check if we start processing events
  bool m_firstEvent = true;

  std::map<std::string, LJTree*> m_trees;             //!

  // will contain all names of the systematic that are processed
  std::vector<std::string> m_allSystVec;              //!

  // will contain systematic that is currently processed
  std::string m_currentSyst;

  // maps to store variables and their default values for branches
  std::map<std::string, std::pair<bool,bool> > m_branchDict_bool;      //!
  std::map<std::string, std::pair<int,int> > m_branchDict_int;         //!
  std::map<std::string, std::pair<float,float> > m_branchDict_float;   //!
  std::map<std::string, std::pair<char,char> > m_branchDict_char;   //!
  std::map<std::string, std::pair<std::vector<bool>,std::vector<bool>> > m_branchDict_vecBool;   //!
  std::map<std::string, std::pair<std::vector<int>,std::vector<int>> > m_branchDict_vecInt;    //!
  std::map<std::string, std::pair<std::vector<float>,std::vector<float>> > m_branchDict_vecFloat;  //!
  std::map<std::string, std::pair<std::vector<char>,std::vector<char>> > m_branchDict_vecChar;    //!

  // TriggerDecisionTool
  asg::AnaToolHandle<TrigConf::ITrigConfigTool> m_trigConfTool_handle {"TrigConf::xAODConfigTool/xAODConfigTool", this}; //!
  asg::AnaToolHandle<Trig::TrigDecisionTool> m_trigDecTool_handle {"Trig::TrigDecisionTool/TrigDecisionTool"}; //!

  // PMGCrossSectionTool
  asg::AnaToolHandle<PMGTools::IPMGCrossSectionTool> m_PMGCrossSectionTool; //!

  // PMGTruthWeightTool
  asg::AnaToolHandle<PMGTools::IPMGTruthWeightTool> m_PMGTruthWeightTool; //!

  // TruthClassificationTool from IFF
  asg::AnaToolHandle<CP::IClassificationTool> m_truthClassificationTool; //!


  // stores trigger names as vector for convenience
  std::vector<std::string> m_triggerListVec = {}; //!

  // cutflow histograms for the LJAlgo
  TH1F * m_AlgoCutflow_LJ; //!
  TH1F * m_AlgoCutflow_LJ_weighted; //!
  TH1F * m_AlgoCutflow_LL; //!
  TH1F * m_AlgoCutflow_LL_weighted; //!
  TH1F * m_AlgoCutflow_EL; //! //yfu combine jetfake
  TH1F * m_AlgoCutflow_EL_weighted; //!

  // theory weight-variation names
  std::vector<std::string> m_weightNames; //!

  // histogram with SoW for theory variations
  TH1D * m_histVariationsSumW; //!


public:

  // this is a standard constructor
  LJAlgo ();
  ~LJAlgo ();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);           //!
  virtual EL::StatusCode fileExecute ();                    //!
  virtual EL::StatusCode histInitialize ();                 //!
  virtual EL::StatusCode changeInput (bool firstFile);      //!
  virtual EL::StatusCode initialize ();                     //!
  virtual EL::StatusCode execute ();                        //!
  virtual EL::StatusCode postExecute ();                    //!
  virtual EL::StatusCode finalize ();                       //!
  virtual EL::StatusCode histFinalize ();                   //!
  virtual EL::StatusCode getLumiWeights(const xAOD::EventInfo* eventInfo);  //!

  // helper function for adding lepton systematic weights
  virtual EL::StatusCode addLeptonSystWeights( std::string weightName);
  // helper function for adding lepton trigger systematic weights
  virtual EL::StatusCode addSingleLeptonTrigSystWeights( unsigned int runNumber, std::string weightName);
  // helper function for adding jvt systematic weights
  virtual EL::StatusCode addJvtSystWeights( std::string weightName);
  // helper function for adding btag systematic weights
  virtual EL::StatusCode addBtagSystWeights( std::string weightName);
  // calculate lepton SFs
  virtual EL::StatusCode computeEventLepSF( const xAOD::IParticleContainer& leptons, std::string weightName, bool doSys); //!
  // calculate JVT SF
  virtual EL::StatusCode computeEventJvtSF( const xAOD::JetContainer* jets, std::string weightName, bool doSys); //!
  // calculate b-tagging SF
  virtual EL::StatusCode computeEventBTagSF( const xAOD::JetContainer* jets, std::string weightName, bool doSys); //!

  // check if lepton is trigger matched & satisfies plateau cuts
  virtual bool isTrigMatched(const xAOD::IParticle* lepton, unsigned int runNumber);
  // get lepton trigger SF
  virtual EL::StatusCode getSingleLepTrigSF( const xAOD::IParticle* lepton, unsigned int runNumber, std::string weightName, bool doSys); //!
  virtual EL::StatusCode getSingleLepTrigSF( const std::vector<const xAOD::IParticle*> leptons, unsigned int runNumber, std::string weightName, bool doSys, bool doElectrons=true); //!

  // return the accessor name for the trigger SFs/systs
  inline std::string getTriggerAccName(unsigned int runNumber, bool isEl, bool isDiEl);

  // return the data-taking period
  inline int get_year(unsigned int runNumber);

  // match truth lepton
  inline const xAOD::TruthParticle* getTruthMatchedParticle(const xAOD::IParticle& lepton); //!

  // helper function for adding lep1 and lep2 variables to avoid code duplication
  inline void addLeptonVariables(std::string prefix);

  // helper function for filling lep1 and lep2 variables to avoid code duplication
  virtual EL::StatusCode fillLeptonVariables(std::string prefix, const xAOD::IParticle &lepton);

  // check if di-lepton is trigger matched & satisfies plateau cuts
  virtual bool isTrigMatched_diLep(const xAOD::EventInfo &eventInfo, const xAOD::IParticle &lepton1, const xAOD::IParticle &lepton2, unsigned int runNumber);
  virtual bool checkDiElIsMatched(const std::multimap< std::string, std::pair< std::pair<unsigned int,unsigned int>, char > > & diElTrigMatchPairMap, const std::pair<unsigned int,unsigned int>& targetPair, const std::string& targetKey);

  // helper function for adding di-electron trigger systematic weights
  virtual EL::StatusCode addDiElectronTrigSystWeights( unsigned int runNumber, std::string weightName);
  // get di-electron trigger SF
  virtual EL::StatusCode getElectronTrigSFTwoLeptons(const xAOD::EventInfo* eventInfo, const std::vector<const xAOD::IParticle*> leptons, unsigned int runNumber, std::string weightName, bool doSys);

  // Help tree creator function
  virtual LJTree* createTree(xAOD::TEvent *event, TTree* tree, TFile* file, const float units, bool debug, xAOD::TStore* store); //!

  // Helpers to add variables to output trees
  template <class T>
    inline void addVariable(std::string branchName, T defaultValue, std::map<std::string,std::pair<T,T> > &branchDict, bool nominalOnly=false)
    {
    for(std::string syst : m_allSystVec){
      if(nominalOnly && !(syst=="")) continue;
       // Get corresponding tree
      std::map<std::string,LJTree*>::iterator it = m_trees.find(syst);
       if(it==m_trees.end()){
          ANA_MSG_WARNING("Could not find tree for systematic: " << syst);
        continue;
        }

      // Insert into map
        // TODO: could we alo just have one variable and not one for each systematic?
        std::string name = branchName+syst;
       branchDict.insert( std::pair<std::string,std::pair<T,T> >(name, std::pair<T,T>(defaultValue,defaultValue)) );

      // Get what we just inserted above
      typename std::map<std::string,std::pair<T,T> >::iterator content;
      content = branchDict.find(name);

      // Link to corresponding tree
      it->second->GetTree()->Branch(branchName.c_str(),&content->second.first);
    }
    }

  // add "scalar" variables
  inline void addFloatVariable(std::string branchName, float defaultValue, bool nominalOnly=false){
    addVariable(branchName, defaultValue, m_branchDict_float, nominalOnly);
  }
  inline void addIntVariable(std::string branchName, int defaultValue, bool nominalOnly=false){
    addVariable(branchName, defaultValue, m_branchDict_int, nominalOnly);
  }
  inline void addBoolVariable(std::string branchName, bool defaultValue, bool nominalOnly=false){
    addVariable(branchName, defaultValue, m_branchDict_bool, nominalOnly);
  }
  inline void addCharVariable(std::string branchName, char defaultValue, char nominalOnly=false){
    addVariable(branchName, defaultValue, m_branchDict_char, nominalOnly);
  }

  // add "vector" variables
  inline void addVecFloatVariable(std::string branchName, std::vector<float> defaultValue, bool nominalOnly=false){
    addVariable(branchName, defaultValue, m_branchDict_vecFloat, nominalOnly);
  }
  inline void addVecIntVariable(std::string branchName, std::vector<int> defaultValue, bool nominalOnly=false){
    addVariable(branchName, defaultValue, m_branchDict_vecInt, nominalOnly);
  }
  inline void addVecBoolVariable(std::string branchName, std::vector<bool> defaultValue, bool nominalOnly=false){
    addVariable(branchName, defaultValue, m_branchDict_vecBool, nominalOnly);
  }
  inline void addVecCharVariable(std::string branchName, std::vector<char> defaultValue, char nominalOnly=false){
    addVariable(branchName, defaultValue, m_branchDict_vecChar, nominalOnly);
  }

  template <class T>
    inline void setVariable(std::string &branchName, T value, std::map<std::string, std::pair<T,T> > &branchDict)
    {
      // Find variable in map
      typename std::map<std::string, std::pair<T,T> >::iterator it;
      std::string name = branchName+m_currentSyst;
      it = branchDict.find(name);

      // Set variable to given value
      if( it != branchDict.end() ){
          it->second.first = value;
      }
      else{
          ANA_MSG_WARNING("Unknown branch name to set " << name );
      }
    }

  inline void setFloatVariable(std::string branchName, float value){
    setVariable(branchName, value, m_branchDict_float);
  }
  inline void setIntVariable(std::string branchName, int value){
    setVariable(branchName, value, m_branchDict_int);
  }
  inline void setBoolVariable(std::string branchName, bool value){
    setVariable(branchName, value, m_branchDict_bool);
  }
  inline void setCharVariable(std::string branchName, char value){
    setVariable(branchName, value, m_branchDict_char);
  }

  inline void setVecFloatVariable(std::string branchName, std::vector<float> value){
    setVariable(branchName, value, m_branchDict_vecFloat);
  }
  inline void setVecIntVariable(std::string branchName, std::vector<int> value){
    setVariable(branchName, value, m_branchDict_vecInt);
  }
  inline void setVecBoolVariable(std::string branchName, std::vector<bool> value){
    setVariable(branchName, value, m_branchDict_vecBool);
  }
  inline void setVecCharVariable(std::string branchName, std::vector<char> value){
    setVariable(branchName, value, m_branchDict_vecChar);
  }

  // Reset values in map to default values
  template <class T>
    inline void resetVariables(std::map<std::string, std::pair<T,T> > &branchDic){
    typename std::map<std::string, std::pair<T,T> >::iterator it;
    for(it = branchDic.begin(); it != branchDic.end(); it++) it->second.first = it->second.second;
  }

  // not sure for what these are needed, commenting out for now
  // void AddTree( std::string );
  // bool executeAnalysis( const xAOD::EventInfo* eventInfo, const xAOD::JetContainer* signalJets, const xAOD::JetContainer* truthJets, const xAOD::VertexContainer* vertices, bool count, std::string systName = "");  //!



  // yfu add individual scale factors
  AsgElectronEfficiencyCorrectionTool  *m_asgElEffCorrTool_elSF_Reco = nullptr;  //!
  AsgElectronEfficiencyCorrectionTool  *m_asgElEffCorrTool_elSF_Iso_HighPtCaloOnly = nullptr;  //!
  AsgElectronEfficiencyCorrectionTool  *m_asgElEffCorrTool_elSF_Iso_Loose_VarRad = nullptr;  //!
  AsgElectronEfficiencyCorrectionTool  *m_asgElEffCorrTool_elSF_Iso_Tight_VarRad = nullptr;  //!
  AsgElectronEfficiencyCorrectionTool  *m_asgElEffCorrTool_elSF_ID_Loose = nullptr;  //!
  AsgElectronEfficiencyCorrectionTool  *m_asgElEffCorrTool_elSF_ID_Medium = nullptr;  //!
  AsgElectronEfficiencyCorrectionTool  *m_asgElEffCorrTool_elSF_ID_Tight = nullptr;  //!


  // this is needed to distribute the algorithm to the workers
  ClassDef(LJAlgo, 1);                                 //!

};

#endif
