# The name of the package:
atlas_subdir (NtupleMaker)

# Add the shared library:
atlas_add_library (NtupleMakerLib
  NtupleMaker/*.h Root/*.cxx
  PUBLIC_HEADERS NtupleMaker
  LINK_LIBRARIES   AnaAlgorithmLib 
                   EventLoop EventLoopAlgs AsgTools
                   xAODBase xAODRootAccess AsgAnalysisInterfaces
                   xAODEventInfo xAODCore
                   xAODJet JetInterface JetResolutionLib 
                   JetCalibToolsLib JetSelectorToolsLib JetUncertaintiesLib JetMomentToolsLib
                   JetRecLib JetEDM JetJvtEfficiencyLib
                   xAODMuon MuonAnalysisInterfacesLib 
                   MuonSelectorToolsLib MuonAnalysisInterfacesLib
                   MuonEfficiencyCorrectionsLib
                   xAODEgamma ElectronPhotonSelectorToolsLib
                   ElectronPhotonFourMomentumCorrectionLib
                   ElectronEfficiencyCorrectionLib
                   ElectronPhotonShowerShapeFudgeToolLib
                   xAODTracking TrackVertexAssociationToolLib
                   xAODTruth TruthUtils
                   xAODTau
                   xAODEventShape xAODCutFlow
                   xAODAssociations AssociationUtilsLib
                   IsolationSelectionLib IsolationCorrectionsLib
                   METUtilitiesLib METInterface
                   TrigDecisionToolLib TrigConfInterfaces TrigConfxAODLib
                   TriggerMatchingToolLib TrigSteeringEvent TrigBunchCrossingTool
                   xAODBTaggingEfficiencyLib xAODBTagging
                   PMGAnalysisInterfacesLib PMGToolsLib
                   PATCoreLib
                   PathResolver
                   CaloGeoHelpers
                   EventLoopGrid)

if (XAOD_STANDALONE)
 # Add the dictionary (for AnalysisBase only):
 atlas_install_data( ../../config/* )

 atlas_add_dictionary (NtupleMakerDict
  NtupleMaker/NtupleMakerDict.h
  NtupleMaker/selection.xml
  LINK_LIBRARIES NtupleMakerLib)
endif ()

if (NOT XAOD_STANDALONE)
  # Add a component library for AthAnalysis only:
  atlas_add_component (NtupleMaker
    src/components/*.cxx
    LINK_LIBRARIES NtupleMakerLib)
endif ()

# Install files from the package:
atlas_install_joboptions( share/*.py )
atlas_install_scripts( share/*.py )
