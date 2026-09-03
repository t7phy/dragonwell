# ------------------------------------------------------------------------------
# Config file to steer xAODAnaHelpers for the Lepton+Jet search
# ------------------------------------------------------------------------------

import os
import shlex
import argparse
import logging

from xAODAnaHelpers import Config as xAH_config

xAH_logger = logging.getLogger("xAH.run")
c = xAH_config()


# ------------------------------------------------------------------------------
# Parse options given by the --extraOptions flag of xAH
# ------------------------------------------------------------------------------
parser = argparse.ArgumentParser(description='Extra options of LJConfig')
parser.add_argument('--campaign', dest='campaign', required=True, choices=["mc20a", "mc20d", "mc20e", "mc21", "mc23a", "mc23c", "mc23d", "mc23e", "data15", "data16", "data17", "data18", "data22", "data23", "data24"])
parser.add_argument('--analysis', dest='analysis', default="both", choices=["lj", "ll", "both"])
parser.add_argument('--channel' , dest='channel', default="both", choices=["e", "mu", "both"])
parser.add_argument('--doSystematics', dest='doSystematics', action="store_true", default=False)
parser.add_argument('--doWeightSystematics', dest='doWeightSystematics', action="store_true", default=False)
parser.add_argument('--isPHYSLITE', dest='isPHYSLITE', action="store_true", default=False)
parser.add_argument('--useTaus', dest='useTaus', action="store_true", default=False)
parser.add_argument('--noSkim', dest='noSkim', action="store_true", default=False)

# args comes from xAH_run.py
options = parser.parse_args(shlex.split(args.extra_options))

# have additional flag deciding if weight systematics in nominal tree should be processed
WeightSystematics = options.doWeightSystematics

if ("data" in options.campaign) and options.doSystematics:
    xAH_logger.error("You want to run on data with systematics activated. This is not supported!")
    os.exit(1)
elif options.doSystematics:
    systName = "All"
    systVal = 1.0
    WeightSystematics = True
else:
    systName = "Nominal"
    systVal = 0.0

if WeightSystematics:
    systNameWeight = "All"
    systValWeight = 1.0
else:
    systNameWeight = "Nominal"
    systValWeight = 0.0

# check for which period we have to configure the algorithms for
if options.campaign == "mc20a":
    period = "2015+2016"
elif options.campaign == "data15":
    period = "2015"
elif options.campaign == "data16":
    period = "2016"
elif options.campaign in ["mc20d", "data17"]:
    period = "2017"
elif options.campaign in ["mc20e", "data18"]:
    period = "2018"
elif options.campaign in ["mc21", "mc23a", "data22"]:
    period = "2022"
elif options.campaign in ["mc23c", "mc23d", "data23"]:
    period = "2023"
elif options.campaign in ["mc23e", "data24"]:
    period = "2024"
xAH_logger.info("LJConfig: Configuring algorithms for period {} (running on {}).".format(period, options.campaign))

is_run3 = period in ('2022', '2023', '2024')

do_skim = not options.noSkim


doDilep = False
doLepJet = False
if options.analysis == "both":
    doDilep = True
    doLepJet = True
elif options.analysis == "lj":
    doLepJet = True
elif options.analysis == "ll":
    doDilep = True
xAH_logger.info(f"LJConfig: Configuring analysis preselection to {options.analysis} setting).")
# TODO: can we parse the derivation type from somewhere, e.g. the input file name?
if options.isPHYSLITE:
    xAH_logger.info("LJConfig: Configuring algorithms for running on PHYSLITE.")


doElectrons = True
doMuons     = True
if options.channel == 'both':
    pass
elif options.channel == 'e':
    doMuons = False
elif options.channel == 'mu':
    doElectrons = False
xAH_logger.info(f"LJConfig: Configuring analysis preselection to only retain {options.channel} events).")

# ------------------------------------------------------------------------------
# Define files needed for cross sections
# ------------------------------------------------------------------------------
crossSectionFile = ""
if "mc20" in options.campaign:
  crossSectionFile =  "dev/PMGTools/PMGxsecDB_mc16.txt"
elif "mc21" in options.campaign:
  crossSectionFile =  "dev/PMGTools/PMGxsecDB_mc21.txt"
elif "mc23" in options.campaign:
  crossSectionFile =  "dev/PMGTools/PMGxsecDB_mc23.txt"

# ------------------------------------------------------------------------------
# Define files needed for PRW
# ------------------------------------------------------------------------------
# TODO: put these somewhere different, maybe in an extra python file?
# define the good runs list files (GRLs)
# paths are in /cvmfs/atlas./repo/sw/database/GroupData/
grls = {
  "2015"     : "GoodRunsLists/data15_13TeV/20170619/physics_25ns_21.0.19.xml",
  "2016"     : "GoodRunsLists/data16_13TeV/20180129/physics_25ns_21.0.19.xml",
  "2017"     : "GoodRunsLists/data17_13TeV/20180619/physics_25ns_Triggerno17e33prim.xml",
  "2018"     : "GoodRunsLists/data18_13TeV/20190318/physics_25ns_Triggerno17e33prim.xml",
  "2015+2016": "GoodRunsLists/data15_13TeV/20170619/physics_25ns_21.0.19.xml,GoodRunsLists/data16_13TeV/20180129/physics_25ns_21.0.19.xml",
  # for the moment we use the GRL suitable for muon triggers in 2022
  "2022"     : "GoodRunsLists/data22_13p6TeV/20250321/data22_13p6TeV.periodAllYear_DetStatus-v134-pro28-10_MERGED_PHYS_StandardGRL_All_Good_25ns_ignore_TRIGLAR.xml",
  "2023"     : "GoodRunsLists/data23_13p6TeV/20250321/data23_13p6TeV.periodAllYear_DetStatus-v133-pro31-11_MERGED_PHYS_StandardGRL_All_Good_25ns_ignoreTRIG_JETCTPIN.xml",
  "2024"     : "GoodRunsLists/data24_13p6TeV/20241118/data24_13p6TeV.periodsEtoO_DetStatus-v130-pro36-08_MERGED_PHYS_StandardGRL_All_Good_25ns.xml",
}

# define the lumi calc files
lumi_calcs = {
  "2015"     : "GoodRunsLists/data15_13TeV/20170619/PHYS_StandardGRL_All_Good_25ns_276262-284484_OflLumi-13TeV-008.root,GoodRunsLists/data16_13TeV/20180129/PHYS_StandardGRL_All_Good_25ns_297730-311481_OflLumi-13TeV-009.root",
  "2016"     : "GoodRunsLists/data15_13TeV/20170619/PHYS_StandardGRL_All_Good_25ns_276262-284484_OflLumi-13TeV-008.root,GoodRunsLists/data16_13TeV/20180129/PHYS_StandardGRL_All_Good_25ns_297730-311481_OflLumi-13TeV-009.root",
  "2017"     : "GoodRunsLists/data17_13TeV/20180619/physics_25ns_Triggerno17e33prim.lumicalc.OflLumi-13TeV-010.root",
  "2018"     : "GoodRunsLists/data18_13TeV/20190318/ilumicalc_histograms_None_348885-364292_OflLumi-13TeV-010.root",
  "2015+2016": "GoodRunsLists/data15_13TeV/20170619/PHYS_StandardGRL_All_Good_25ns_276262-284484_OflLumi-13TeV-008.root,GoodRunsLists/data16_13TeV/20180129/PHYS_StandardGRL_All_Good_25ns_297730-311481_OflLumi-13TeV-009.root",
  "2022"     : "GoodRunsLists/data22_13p6TeV/20250321/ilumicalc_histograms_None_430536-440613_OflLumi-Run3-004_ignore_TRIGLAR.root",
  "2023"     : "GoodRunsLists/data23_13p6TeV/20250321/ilumicalc_histograms_None_451587-456749_OflLumi-Run3-004_ignoreTRIGJETCTPIN.root",
  "2024"     : "GoodRunsLists/data24_13p6TeV/20241118/ilumicalc_histograms_None_473235-486706_OflLumi-Run3-005.root",
}

# Paths are in /cvmfs/atlas.cern.ch/repo/sw/database/GroupData/
# files with actual mu, used for mc20d, mc20e and mc23
actualMu2017File = "GoodRunsLists/data17_13TeV/20180619/physics_25ns_Triggerno17e33prim.actualMu.OflLumi-13TeV-010.root"
actualMu2018File = "GoodRunsLists/data18_13TeV/20190318/physics_25ns_Triggerno17e33prim.actualMu.OflLumi-13TeV-010.root"
actualMu2022File = "GoodRunsLists/data22_13p6TeV/20250321/purw.actualMu.ignore_TRIGLAR.root"
actualMu2023File = "GoodRunsLists/data23_13p6TeV/20250321/purw.actualMu.ignoreTRIGJETCTPIN.root"
actualMu2024File = "GoodRunsLists/data24_13p6TeV/20241118/purw.actualMu.root"

# Paths are in /cvmfs/atlas.cern.ch/repo/sw/database/GroupData/
# commmon MC PRW files
commonPRWFiles = {
  "mc20a" : "PileupReweighting/mc20_common/mc20a.284500.physlite.prw.v1.root",
  "mc20d" : "PileupReweighting/mc20_common/mc20d.300000.physlite.prw.v1.root",
  "mc20e" : "PileupReweighting/mc20_common/mc20e.310000.physlite.prw.v1.root",
  "mc21"  : "PileupReweighting/mc21_common/mc21a.410000.physlite.prw.v1.root",
  "mc23a" : "PileupReweighting/mc23_common/mc23a.410000.physlite.prw.v2.root",
  "mc23c" : "PileupReweighting/mc23_common/mc23c.450000.physlite.prw.v1.root",
  "mc23d" : "PileupReweighting/mc23_common/mc23d.450000.physlite.prw.v1.root",
  "mc23e" : "PileupReweighting/mc23_common/mc23e.470000.physlite.prw.v1.root",
}


# ------------------------------------------------------------------------------
# Define triggers relevant for analysis
# ------------------------------------------------------------------------------
# TODO: put these somewhere different, maybe in an extra python file?
# TODO: to be cross-checked against https://twiki.cern.ch/twiki/bin/viewauth/Atlas/LowestUnprescaled

# add Run 2 triggers
# triggers_singleMuon = ['HLT_mu20_iloose_L1MU15',
#                        'HLT_mu26_ivarmedium',
#                        'HLT_mu50',
#                        'HLT_mu40']
# triggers_diElec     = ['HLT_2e12_lhloose_L12EM10VH',
#                        'HLT_2e17_lhvloose_nod0',
#                        'HLT_2e24_lhvloose_nod0']

# add Run 3 triggers
triggers_singleMuon = ['HLT_mu24_ivarmedium_L1MU14FCH',
                        'HLT_mu50_L1MU14FCH']
triggers_diElec     = ['HLT_2e24_lhvloose_L12EM20VH',
                        'HLT_2e24_lhvloose_L12eEM24L']


triggers  = triggers_singleMuon
triggers += triggers_diElec


muon_trigger_matching_chains = {
  '2015'      : "HLT_mu20_iloose_L1MU15,HLT_mu40",
  '2016'      : "HLT_mu26_ivarmedium,HLT_mu50",
  '2017'      : "HLT_mu26_ivarmedium,HLT_mu50",
  '2018'      : "HLT_mu26_ivarmedium,HLT_mu50",
  '2015+2016' : "HLT_mu20_iloose_L1MU15,HLT_mu26_ivarmedium,HLT_mu40,HLT_mu50",
  '2022'      : "HLT_mu24_ivarmedium_L1MU14FCH,HLT_mu50_L1MU14FCH",
  '2023'      : "HLT_mu24_ivarmedium_L1MU14FCH,HLT_mu50_L1MU14FCH",
  '2024'      : "HLT_mu24_ivarmedium_L1MU14FCH,HLT_mu50_L1MU14FCH"
}

dielectron_trigger_matching_chains = {
  '2015'      : "HLT_2e12_lhloose_L12EM10VH",
  '2016'      : "HLT_2e17_lhvloose_nod0",
  '2017'      : "HLT_2e24_lhvloose_nod0",
  '2018'      : "HLT_2e24_lhvloose_nod0",
  '2015+2016' : "HLT_2e12_lhloose_L12EM10VH,HLT_2e17_lhvloose_nod0",
  '2022'      : "HLT_2e24_lhvloose_L12EM20VH",
  '2023'      : "HLT_2e24_lhvloose_L12eEM24L",
  '2024'      : "HLT_2e24_lhvloose_L12eEM24L"
}

# check if we need to configure the Run2 or Run3 trigger navigation
doRun3TriggerNav = is_run3
HLTSummary       = "HLTNav_Summary_DAODSlimmed" # if we process a non PHYS/PHYSLITE sample it would be "HLTNav_Summary_AODSlimmed"


# ------------------------------------------------------------------------------
# LEPTON CONFIGURATION
# ------------------------------------------------------------------------------

### ELECTRONS

electrons_reco_wp = "Reconstruction"

# Electrons ID
# options are:
# - LooseBL or LooseAndBLayer
# - Medium
# - Tight
# however this does not guarantee that they are avialable from the map files.
electrons_baseline_id_wp_selector_tool   = "LooseAndBLayer" # options as above
electrons_baseline_id_wp_efficiency_tool = "LooseBLayer"    # options: Tight, Medium, LooseBLayer
electrons_signal_id_wp_selector_tool     = "LooseAndBLayer" # options as above
electrons_signal_id_wp_efficiency_tool   = "LooseBLayer"    # options: Tight, Medium, LooseBLayer

# Electron ISO
# options are:
# - Loose_VarRad
# - Tight_VarRad
# - TightTrackOnly_VarRad
# - HighPtCaloOnly
electrons_baseline_iso_wp       = "Loose_VarRad"
electrons_signal_iso_wp         = "Loose_VarRad"
electrons_signal_trigger_iso_wp = "Loose_VarRad"


electrons_es_model                = 'es2024_Run3_v0' if is_run3 else 'es2023_R22_Run2_v0'
electrons_systs_reduction_scheme  = '1NP_v1'

electrons_baseline_ptmin          = 10000.
electrons_baseline_etamax         = 2.47
electrons_baseline_z0sintheta_max = 0.5
electrons_baseline_iso_wp_list    = "Loose_VarRad,Tight_VarRad,HighPtCaloOnly"
electrons_baseline_iso_wp_min     = electrons_baseline_iso_wp
electrons_baseline_ID_wp_min      = electrons_baseline_id_wp_selector_tool

electrons_signal_ptmin          = 30000.
electrons_signal_etamax         = 2.47
electrons_signal_d0_max         = 5
electrons_signal_iso_wp_list    = "Loose_VarRad,Tight_VarRad,HighPtCaloOnly"
electrons_signal_iso_wp_min     = electrons_signal_iso_wp
electrons_signal_ID_wp_min      = electrons_signal_id_wp_selector_tool



dielectron_trigRun2   = "DI_E_2015_e12_lhloose_L1EM10VH_2016_e17_lhvloose_nod0_2017_2018_e24_lhvloose_nod0_L1EM20VH"
dielectron_trigRun3_dict = {
    '2022': '2022_e24_lhvloose',
    '2023': '2023_e24_lhvloose_L1eEM24L',
    '2024': '2023_e24_lhvloose_L1eEM24L', #TODO: update when reco is available
}

dielectron_trig = dielectron_trigRun3_dict[period] if is_run3 else dielectron_trigRun2






### Muons
mu_eff_reco     = "HighPt"
# only PflowTight iso WPs possible in current PHYSLITE derivations (p5631), also: HighPtTrackOnly only experimental, i.e. no SFs atm
mu_eff_iso      = "PflowTight_VarRad"
mu_eff_TTVA     = "TTVA"
mu_eff_trig15   = muon_trigger_matching_chains["2015"].replace(",", "_OR_")
mu_eff_trigRun2 = muon_trigger_matching_chains["2016"].replace(",", "_OR_")
mu_eff_trig     = muon_trigger_matching_chains["2022"].replace(",", "_OR_")

muons_baseline_ptmin          = 10000.
muons_baseline_etamax         = 2.5
muons_baseline_z0sintheta_max = 0.5
muons_baseline_iso_wp_list    = mu_eff_iso #+",PflowTight_VarRad,PflowTight_FixedRad"
muons_baseline_iso_wp_min     = ""
muons_baseline_ID_wp_min      = "LooseBL"

muons_signal_ptmin          = 10000.
muons_signal_etamax         = 2.5
muons_signal_d0_max         = 3
muons_signal_iso_wp_list    = mu_eff_iso #+",PflowTight_VarRad,PflowTight_FixedRad"
muons_signal_iso_wp_min     = ""
muons_signal_ID_wp_min      = "LooseBL"


# ------------------------------------------------------------------------------
# Flavour Tagging Definitions.
# ------------------------------------------------------------------------------

# Name of the tagger, recommended ones: DL1dv01  or  GN2v01
btaggerName    = "GN2v01"
# even when using GN2v01 and continuous WPs, this variable decides the efficiency (see dictionary cuts_from_WP)
btag_WP        = "FixedCutBEff_77"
# set this to True if you want to have branches for each efficiency bin when having a continuous WP
write_all_effs = True
# eigenvector reduction scheme
eigenRed_gen   = "Medium"
# Make sure continuous WP is used for GN2v01
if btaggerName == "GN2v01":
    btag_operatingPt = "Continuous"
    corr_file = "xAODBTaggingEfficiency/13TeV/MC20_2025-06-17_GN2v01_v4.root" if not is_run3 else "xAODBTaggingEfficiency/13p6TeV/MC23_2025-06-17_GN2v01_v4.root"
else:
    btag_operatingPt = btag_WP
    corr_file = "xAODBTaggingEfficiency/13TeV/2023-22-13TeV-MC20-CDI-2023-09-13_v1.root" if not is_run3 else "xAODBTaggingEfficiency/13p6TeV/2023-22-13TeV-MC21-CDI-2023-09-13_v1.root"

eigenRedB     = eigenRed_gen
eigenRedC     = eigenRed_gen
eigenRedLight = eigenRed_gen
# Require "btag_quantile > n" for continuous WP to get similar efficiency to corresponding fixed cut WP
cuts_from_WP = {
    "FixedCutBEff_65": 6,
    "FixedCutBEff_70": 5,
    "FixedCutBEff_77": 4,
    "FixedCutBEff_85": 3,
    "FixedCutBEff_90": 2,
    "FixedCutBEff_100": 1,
}


# ------------------------------------------------------------------------------
# Basic Event Selection.
# ------------------------------------------------------------------------------
# TODO: check individual flags: what do they do and do we need them?
c.algorithm("BasicEventSelection", {
    "m_name"                      : "basicEventSel",
    "m_applyGRLCut"               : True,
    "m_GRLxml"                    : grls[period],
    "m_lumiCalcFileNames"         : lumi_calcs[period],
    "m_doPUreweighting"           : True,
    "m_doPUreweightingSys"        : True,
    "m_autoconfigPRW"             : True,
    "m_useCommonPRWFiles"         : True,
    "m_prwActualMu2017File"       : actualMu2017File,
    "m_prwActualMu2018File"       : actualMu2018File,
    "m_prwActualMu2022File"       : actualMu2022File,
    "m_prwActualMu2023File"       : actualMu2023File,
    "m_prwActualMu2024File"       : actualMu2024File,
    "m_useRun3navigation"         : doRun3TriggerNav,
    "m_HLTSummary"                : HLTSummary,
    "m_triggerSelection"          : ",".join(triggers),
    "m_storeTrigDecisions"        : True,
    "m_storeTrigKeys"             : False,
    "m_storePassL1"               : False,
    "m_storePassHLT"              : False,
    "m_PVNTrack"                  : 2,
    "m_applyTriggerCut"           : do_skim,
    "m_applyPrimaryVertexCut"     : True,
    "m_applyEventCleaningCut"     : do_skim,
    "m_applyJetCleaningEventFlag" : do_skim,
    "m_applyCoreFlagsCut"         : True,
    "m_useMetaData"               : True,
    "m_checkDuplicatesData"       : True,
    "m_checkDuplicatesMC"         : False
})


# ------------------------------------------------------------------------------
# Electron Calibration.
# ------------------------------------------------------------------------------
c.algorithm("ElectronCalibrator", {
    "m_name"                     : "ElectronCalibrator",
    "m_inContainerName"          : "Electrons" if not options.isPHYSLITE  else "AnalysisElectrons",
    "m_outContainerName"         : "Electrons_Calib",
    "m_outputAlgoSystNames"      : "ElectronCalibrator_Syst",
    "m_esModel"                  : electrons_es_model,
    "m_decorrelationModel"       : electrons_systs_reduction_scheme,
    "m_applyIsolationCorrection" : False,
    "m_forceFullSim"             : True, # need to circumvent intended crash from Egamma tool for AF3 mc23
    "m_systName"                 : systName,
})

# ------------------------------------------------------------------------------
# Electron Preselection.
# ------------------------------------------------------------------------------
c.algorithm("ElectronSelector", {
    "m_name"                      : "ElectronPreSelector",
    "m_inContainerName"           : "Electrons_Calib",
    "m_outContainerName"          : "Electrons_PreSelected",
    "m_createSelectedContainer"   : True,
    "m_decorateSelectedObjects"   : False,
    "m_readIDFlagsFromDerivation" : True,
    # cuts
    "m_pT_min"                    : electrons_baseline_ptmin,
    "m_eta_max"                   : electrons_baseline_etamax,
    "m_z0sintheta_max"            : electrons_baseline_z0sintheta_max, # do z0 cut here, d0 cut in signal selector?
    "m_doOQCut"                   : True,
    "m_applyDeadHVCellVeto"       : True,
    "m_vetoCrack"                 : True,
    # WPs
    "m_IsoWPList"                 : electrons_baseline_iso_wp_list,
    "m_MinIsoWPCut"               : electrons_baseline_iso_wp_min, # but don't cut on iso
    "m_doLHPID"                   : True,
    "m_doLHPIDcut"                : True,
    "m_LHOperatingPoint"          : electrons_baseline_ID_wp_min,
    # systs
    "m_inputAlgoSystNames"        : "ElectronCalibrator_Syst",
    "m_outputAlgoSystNames"       : "ElectronPreSelector_Syst",
    # trigger
    "m_diElTrigChains"            : dielectron_trigger_matching_chains[period],
    "m_useRun3navigation"         : doRun3TriggerNav,
    "m_trigInputPrefix"           : "AnalysisTrigMatch_" if options.isPHYSLITE else "",
})







# ------------------------------------------------------------------------------
# Muon Calibration.
# ------------------------------------------------------------------------------
c.algorithm("MuonCalibrator", {
    "m_name"                : "MuonCalibrator",
    "m_inContainerName"     : "Muons" if not options.isPHYSLITE else "AnalysisMuons",
    "m_outContainerName"    : "Muons_Calib",
    "m_outputAlgoSystNames" : "MuonCalibrator_Syst",
    "m_forceDataCalib"      : True,
    "m_systName"            : systName,
    "m_calibrationMode"     : "notCorrectData_IDMS" if not is_run3 else "notCorrectData_CB",
    "m_do2StationsHighPt"   : True,
    "m_isRun3Geo"           : is_run3,
})

# ------------------------------------------------------------------------------
# Muon Preselection.
# ------------------------------------------------------------------------------
c.algorithm("MuonSelector", {
    "m_name"                    : "MuonPreSelector",
    "m_inContainerName"         : "Muons_Calib",
    "m_outContainerName"        : "Muons_PreSelected",
    "m_createSelectedContainer" : True,
    "m_decorateSelectedObjects" : False,
    # cuts
    "m_pT_NaNcheck"             : True,
    "m_pT_min"                  : muons_baseline_ptmin,
    "m_eta_max"                 : muons_baseline_etamax,
    "m_z0sintheta_max"          : muons_baseline_z0sintheta_max,
    # WPs
    "m_muonQualityStr"          : mu_eff_reco,  # Medium
    "m_doIsolation"             : True,
    "m_MinIsoWPCut"             : muons_baseline_iso_wp_min,
    "m_IsoWPList"               : muons_baseline_iso_wp_list,
    # systs
    "m_inputAlgoSystNames"      : "MuonCalibrator_Syst",
    "m_outputAlgoSystNames"     : "MuonPreSelector_Syst",
    # triggers
    "m_singleMuTrigChains"      : muon_trigger_matching_chains[period],
    "m_useRun3navigation"       : doRun3TriggerNav,
    "m_trigInputPrefix"         : "AnalysisTrigMatch_" if options.isPHYSLITE else "",
    # others
    "m_isRun3Geo"               : is_run3,
    "m_removeCosmicMuon"        : True,
    "m_removeEventBadMuon"      : do_skim,
})


# ------------------------------------------------------------------------------
# Hadronic Tau Calibration.
# ------------------------------------------------------------------------------
c.algorithm("TauCalibrator", {
    "m_name"                : "TauCalibrator",
    "m_inContainerName"     : "TauJets" if not options.isPHYSLITE else "AnalysisTauJets",
    "m_outContainerName"    : "TauJets_Calib",
    "m_RecommendationTag"   : "2022-prerec",
    "m_campaign"            : "mc21" if period=="2022" else "mc20",
    "m_skipTruthMatchCheck" : True
})


# ------------------------------------------------------------------------------
# Hadronic Tau Preselection.
# ------------------------------------------------------------------------------
c.algorithm("TauSelector", {
    "m_name"                    : "TauPreSelector",
    "m_inContainerName"         : "TauJets_Calib",
    "m_outContainerName"        : "TauJets_PreSelected",
    "m_createSelectedContainer" : True,
    "m_decorateSelectedObjects" : False,
    "m_ConfigPath"              : "LJAlgo/tau_selection_veryloose.conf"
})


# ------------------------------------------------------------------------------
# Jet Calibration.
# ------------------------------------------------------------------------------
c.algorithm("JetCalibrator", {
    "m_name"                   : "JetCalibrator",
    "m_inContainerName"        : "AntiKt4EMPFlowJets" if not options.isPHYSLITE else"AnalysisJets",
    "m_outContainerName"       : "AntiKt4EMPFlowJets_Calib",
    "m_outputAlgo"             : "AntiKt4EMPFlowJets_Calib_Algo",
    "m_jetAlgo"                : "AntiKt4EMPFlow",
    "m_doCleaning"             : False,
    "m_sort"                   : True,
    "m_saveAllCleanDecisions"  : False,
    "m_calibSequence"          : "JetArea_Residual_EtaJES_GSC" if args.is_MC else "JetArea_Residual_EtaJES_GSC_Insitu",
    # please note that the configs below for Run3 will cause a crash in current PHYSLITE samples, need to switch to PHYS ..
    "m_calibConfigFullSim"     : "AntiKt4EMPFlow_MC23a_PreRecR22_Phase2_CalibConfig_ResPU_EtaJES_GSC_241208_InSitu.config" if is_run3 else "PreRec_R22_PFlow_ResPU_EtaJES_GSC_February23_230215.config",
    "m_calibConfigData"        : "AntiKt4EMPFlow_MC23a_PreRecR22_Phase2_CalibConfig_ResPU_EtaJES_GSC_241208_InSitu.config" if is_run3 else "PreRec_R22_PFlow_ResPU_EtaJES_GSC_February23_230215.config",
    "m_calibConfigAFII"        : "AntiKt4EMPFlow_MC23a_PreRecR22_Phase2_CalibConfig_ResPU_EtaJES_GSC_241208_InSitu.config" if is_run3 else "PreRec_R22_PFlow_ResPU_EtaJES_GSC_February23_230215.config",
    "m_uncertConfig"           : "rel22/Spring2025_PreRec/R4_CategoryReduction_FullJER_MC23.config" if is_run3 else "rel22/Summer2023_PreRec/R4_CategoryReduction_FullJER.config",
    "m_overrideCalibArea"      : "00-04-83" if is_run3 else "00-04-82",
    "m_uncertMCType"           : "MC23" if is_run3 else "MC20",
    "m_mcAndPseudoData"        : options.doSystematics,
    "m_systName"               : systName,
    "m_systVal"                : systVal,
})


# ------------------------------------------------------------------------------
# Jet Selection.
# ------------------------------------------------------------------------------
c.algorithm("JetSelector", {
    "m_name"                    : "JetSelector",
    # "m_msgLevel"                : "DEBUG",
    "m_inContainerName"         : "AntiKt4EMPFlowJets_Calib",
    "m_inputAlgo"               : "AntiKt4EMPFlowJets_Calib_Algo",
    "m_outContainerName"        : "AntiKt4EMPFlowJets_Selected",
    "m_outputAlgo"              : "AntiKt4EMPFlowJets_Selected_Algo",
    "m_truthJetContainer"       : "AntiKt4TruthDressedWZJets",
    "m_decorateSelectedObjects" : True,
    "m_createSelectedContainer" : True,
    # cuts
    "m_cleanJets"               : True,
    "m_pT_min"                  : 20e3,
    "m_eta_max"                 : 2.5,
    "m_useCutFlow"              : True,
    "m_doJVT"                   : True,
    "m_noJVTVeto"               : False,
    "m_dofJVT"                  : False,
    "m_dofJVTVeto"              : False,
    "m_WorkingPointJVT"         : "FixedEffPt",
    "m_SFFileJVT"               : "JetJvtEfficiency/May2024/NNJvtSFFile_Run3_EMPFlow.root" if is_run3 else "JetJvtEfficiency/May2024/NNJvtSFFile_Run2_EMPFlow.root",
    # systs
    "m_systNameJVT"             : systNameWeight,
    #"m_systValJVT "             : systVal,
})


# ------------------------------------------------------------------------------
# Flavor Tagging.
# ------------------------------------------------------------------------------
c.algorithm("BJetEfficiencyCorrector", {
    "m_name"                      : "BJetEffCor",
    "m_inContainerName"           : "AntiKt4EMPFlowJets_Selected",
    "m_inputAlgo"                 : "AntiKt4EMPFlowJets_Selected_Algo",
    "m_systName"                  : systNameWeight,
    "m_outputSystName"            : "BJetEfficiency_Algo",
    "m_operatingPt"               : btag_operatingPt,
    "m_useContinuous"             : "Continuous" in btag_operatingPt,
    "m_corrFileName"              : corr_file,
    "m_systematicsStrategy"       : "SFEigen",
    "m_EigenvectorReductionB"     : eigenRedB,
    "m_EigenvectorReductionC"     : eigenRedC,
    "m_EigenvectorReductionLight" : eigenRedLight,
    "m_minPt"                     : 20e3,
    "m_writeSystToMetadata"       : True,
    "m_taggerName"                : btaggerName,
    "m_decor"                     : "BTag",
    "m_EfficiencyCalibration"     : "auto",
    "m_allowCalibrationFallback"  : True,
    "m_errorOnTagWeightFailure"   : False,
    "m_isRun3"                    : is_run3,
})


# ------------------------------------------------------------------------------
# Truth Selection.
# ------------------------------------------------------------------------------
if args.is_MC:
    c.algorithm("TruthSelector", {
        "m_name"                      : "TruthElectronSelector",
        "m_inContainerName"           : "TruthElectrons",
        "m_outContainerName"          : "TruthElectrons_Selected",
        "m_createSelectedContainer"   : True,
        "m_pT_min"                    : 10000.,
        "m_eta_max"                   : 4.
    })

    c.algorithm("TruthSelector", {
        "m_name"                      : "TruthMuonSelector",
        "m_inContainerName"           : "TruthMuons",
        "m_outContainerName"          : "TruthMuons_Selected",
        "m_createSelectedContainer"   : True,
        "m_pT_min"                    : 10000.,
        "m_eta_max"                   : 4.
    })

    c.algorithm("TruthSelector", {
        "m_name"                      : "TruthTauSelector",
        "m_inContainerName"           : "TruthTaus",
        "m_outContainerName"          : "TruthTaus_Selected",
        "m_createSelectedContainer"   : True,
        "m_pT_min"                    : 20000.,
        "m_eta_max"                   : 2.5
    })

    c.algorithm("JetSelector", {
        "m_name"                    : "TruthJetSelector",
        "m_inContainerName"         : "AntiKt4TruthDressedWZJets",
        "m_outContainerName"        : "AntiKt4TruthDressedWZJets_Selected",
        "m_createSelectedContainer" : True,
        "m_pT_min"                  : 20e3,
        "m_eta_max"                 : 4.5
    })


# ------------------------------------------------------------------------------
# Overlap removal, takes preselected leptons and signal jets/taus.
# ------------------------------------------------------------------------------
# Note: OR must not be applied to the containers passed to METmaker.
c.algorithm("OverlapRemover", {
    "m_name"                       : "OverlapRemover",
    "m_useCutFlow"                 : True,
    "m_decorateSelectedObjects"    : True,
    "m_inContainerName_Jets"       : "AntiKt4EMPFlowJets_Selected",
    "m_inContainerName_Taus"       : "TauJets_PreSelected" if options.useTaus else "",
    # "m_inContainerName_Photons"    : "Photons_Selected",
    "m_inContainerName_Electrons"  : "Electrons_PreSelected",
    "m_inContainerName_Muons"      : "Muons_PreSelected",
    "m_inputAlgoJets"              : "AntiKt4EMPFlowJets_Selected_Algo",
    "m_inputAlgoMuons"             : "MuonPreSelector_Syst",
    "m_inputAlgoElectrons"         : "ElectronPreSelector_Syst",
    "m_outContainerName_Jets"      : "AntiKt4EMPFlowJets_PassedOR",
    "m_outContainerName_Taus"      : "TauJets_Baseline" if options.useTaus else "",
    # "m_outContainerName_Photons"   : "Photons_PassedOR",
    "m_outContainerName_Electrons" : "Electrons_Baseline",
    "m_outContainerName_Muons"     : "Muons_Baseline",
    "m_outputAlgoSystNames"        : "OverlapRemovalAlgo_Syst",
})






# ------------------------------------------------------------------------------
# Electron Signal Selection. Add isSig decorator to baseline objects.
# ------------------------------------------------------------------------------
c.algorithm("ElectronSelector", {
    "m_name"                      : "ElectronSelector",
    "m_inContainerName"           : "Electrons_Baseline", # OR uses preselected objects, signal selector takes baseline objects from OR
    "m_outContainerName"          : "Electrons_Selected",
    "m_useCutFlow"                : True,
    "m_createSelectedContainer"   : False,
    "m_decorateSelectedObjects"   : True,
    "m_readIDFlagsFromDerivation" : True,
    # cuts
    "m_pT_min"                    : electrons_signal_ptmin,
    "m_eta_max"                   : electrons_signal_etamax,
    "m_d0sig_max"                 : electrons_signal_d0_max,
    "m_doOQCut"                   : True,
    "m_vetoCrack"                 : True,
    "m_doAuthorCut"               : True,
    # WPs
    "m_IsoWPList"                 : electrons_signal_iso_wp_list,
    "m_MinIsoWPCut"               : electrons_signal_iso_wp_min,
    "m_doLHPID"                   : True,
    "m_doLHPIDcut"                : True,
    "m_LHOperatingPoint"          : electrons_signal_ID_wp_min,
    # systs
    "m_inputAlgoSystNames"        : "OverlapRemovalAlgo_Syst",
    "m_outputAlgoSystNames"       : "ElectronSelector_Syst",
    "m_systName"                  : systName,
    # trigger
    "m_diElTrigChains"            : dielectron_trigger_matching_chains[period],
    "m_useRun3navigation"         : doRun3TriggerNav,
    "m_trigInputPrefix"           : "AnalysisTrigMatch_" if options.isPHYSLITE else "",
})

# ------------------------------------------------------------------------------
# Electron Efficiency Corrector.
# ------------------------------------------------------------------------------
# Takes preselected electrons as input -> all preselected (and baseline in the shallow container copy after OR) electrons have SF decorators.
# SF weight calculation only takes signal selected leptons into account, hence we use the signal WPs in this EfficiencyCorrector.

# Currently there are no R22 electron trigger SF for Run2 so we have to hack a bit and use the ones from R21 in that case...
# Configure this algorithm to do everything except the trigger SFs ...
c.algorithm("ElectronEfficiencyCorrector", {
    "m_name"                      : "ElectronEfficiencyCorrector",
    "m_inContainerName"           : "Electrons_PreSelected",
    "m_WorkingPointReco"          : electrons_reco_wp,
    "m_WorkingPointPID"           : electrons_signal_id_wp_efficiency_tool,
    "m_WorkingPointIso"           : electrons_signal_iso_wp,
    "m_WorkingPointTrig"          : "",
    "m_inputSystNamesElectrons"   : "ElectronPreSelector_Syst",
    "m_correlationModel"          : "TOTAL",
    "m_systNamePID"               : systNameWeight,
    "m_systNameIso"               : systNameWeight,
    "m_systNameReco"              : systNameWeight,
    "m_systValPID"                : systValWeight,
    "m_systValIso"                : systValWeight,
    "m_systValReco"               : systValWeight,
    "m_overrideMapFilePath"       : "ElectronEfficiencyCorrection/2015_2025/rel22.2/2025_Run3_Consolidated_Prerecom_v3/map1.txt" if is_run3 else "ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/map4.txt"
})

# ------------------------------------------------------------------------------
# Di-Electron Efficiency Corrector.
# ------------------------------------------------------------------------------

# yfu add configuration for other working points
c.algorithm("ElectronEfficiencyCorrector", {
    "m_name"                      : "ElectronEfficiencyCorrector_Weight1",
    # "m_msgLevel"                  : "DEBUG",
    "m_inContainerName"           : "Electrons_PreSelected",
    "m_WorkingPointReco"          : "",
    "m_WorkingPointPID"           : "Tight",
    "m_WorkingPointIso"           : "Tight_VarRad", # R22 trigger SFs for HighPtCaloOnly iso WP not available...
    "m_WorkingPointTrig"          : "",
    "m_inputSystNamesElectrons"   : "ElectronPreSelector_Syst",
    "m_correlationModel"          : "TOTAL",
    "m_systNameTrig"              : systNameWeight,
    "m_systValTrig"               : systValWeight,
    "m_overrideMapFilePath"       : "ElectronEfficiencyCorrection/2015_2025/rel22.2/2025_Run3_Consolidated_Prerecom_v3/map1.txt" if is_run3 else "ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/map4.txt"
})

c.algorithm("ElectronEfficiencyCorrector", {
    "m_name"                      : "ElectronEfficiencyCorrector_Weight2",
    # "m_msgLevel"                  : "DEBUG",
    "m_inContainerName"           : "Electrons_PreSelected",
    "m_WorkingPointReco"          : "",
    "m_WorkingPointPID"           : "Tight",
    "m_WorkingPointIso"           : "HighPtCaloOnly", # R22 trigger SFs for HighPtCaloOnly iso WP not available...
    "m_WorkingPointTrig"          : "",
    "m_inputSystNamesElectrons"   : "ElectronPreSelector_Syst",
    "m_correlationModel"          : "TOTAL",
    "m_systNameTrig"              : systNameWeight,
    "m_systValTrig"               : systValWeight,
    "m_overrideMapFilePath"       : "ElectronEfficiencyCorrection/2015_2025/rel22.2/2025_Run3_Consolidated_Prerecom_v3/map1.txt" if is_run3 else "ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/map4.txt"
})

c.algorithm("ElectronEfficiencyCorrector", {
    "m_name"                      : "ElectronEfficiencyCorrector_Weight3",
    # "m_msgLevel"                  : "DEBUG",
    "m_inContainerName"           : "Electrons_PreSelected",
    "m_WorkingPointReco"          : "",
    "m_WorkingPointPID"           : "Medium",
    "m_WorkingPointIso"           : "Loose_VarRad", # R22 trigger SFs for HighPtCaloOnly iso WP not available...
    "m_WorkingPointTrig"          : "",
    "m_inputSystNamesElectrons"   : "ElectronPreSelector_Syst",
    "m_correlationModel"          : "TOTAL",
    "m_systNameTrig"              : systNameWeight,
    "m_systValTrig"               : systValWeight,
    "m_overrideMapFilePath"       : "ElectronEfficiencyCorrection/2015_2025/rel22.2/2025_Run3_Consolidated_Prerecom_v3/map1.txt" if is_run3 else "ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/map4.txt"
})

c.algorithm("ElectronEfficiencyCorrector", {
    "m_name"                      : "ElectronEfficiencyCorrector_Weight4",
    # "m_msgLevel"                  : "DEBUG",
    "m_inContainerName"           : "Electrons_PreSelected",
    "m_WorkingPointReco"          : "",
    "m_WorkingPointPID"           : "Tight",
    "m_WorkingPointIso"           : "Loose_VarRad", # R22 trigger SFs for HighPtCaloOnly iso WP not available...
    "m_WorkingPointTrig"          : "",
    "m_inputSystNamesElectrons"   : "ElectronPreSelector_Syst",
    "m_correlationModel"          : "TOTAL",
    "m_systNameTrig"              : systNameWeight,
    "m_systValTrig"               : systValWeight,
    "m_overrideMapFilePath"       : "ElectronEfficiencyCorrection/2015_2025/rel22.2/2025_Run3_Consolidated_Prerecom_v3/map1.txt" if is_run3 else "ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/map4.txt"
})
############################################################################################ end yfu

# Configure this algorithm to do only the di-electron trigger SFs ...
c.algorithm("ElectronEfficiencyCorrector", {
    "m_name"                      : "ElectronEfficiencyCorrector_DiElTRIG",
    # "m_msgLevel"                  : "DEBUG",
    "m_inContainerName"           : "Electrons_PreSelected",
    "m_WorkingPointReco"          : "",
    "m_WorkingPointPID"           : electrons_signal_id_wp_efficiency_tool,
    "m_WorkingPointIso"           : electrons_signal_trigger_iso_wp, # R22 trigger SFs for HighPtCaloOnly iso WP not available...
    "m_WorkingPointTrig"          : dielectron_trig,
    "m_inputSystNamesElectrons"   : "ElectronPreSelector_Syst",
    "m_correlationModel"          : "TOTAL",
    "m_systNameTrig"              : systNameWeight,
    "m_systValTrig"               : systValWeight,
    "m_overrideMapFilePath"       : "ElectronEfficiencyCorrection/2015_2025/rel22.2/2025_Run3_Consolidated_Prerecom_v3/map1.txt" if is_run3 else "ElectronEfficiencyCorrection/2015_2018/rel21.2/Precision_Summer2020_v1/map4.txt"
})



# ------------------------------------------------------------------------------
# Muon Signal Selection. Add isSig decorator to baseline objects.
# ------------------------------------------------------------------------------
c.algorithm("MuonSelector", {
    "m_name"                    : "MuonSelector",
    "m_inContainerName"         : "Muons_Baseline",
    "m_outContainerName"        : "Muons_Selected",
    "m_useCutFlow"              : True,
    "m_createSelectedContainer" : False,
    "m_decorateSelectedObjects" : True,
    # cuts
    "m_pT_NaNcheck"             : True,
    "m_pT_min"                  : muons_signal_ptmin,
    "m_eta_max"                 : muons_signal_etamax,
    "m_d0sig_max"               : muons_signal_d0_max,
    # WPs
    "m_muonQualityStr"          : mu_eff_reco,
    "m_doIsolation"             : True,
    "m_MinIsoWPCut"             : mu_eff_iso,
    "m_IsoWPList"               : mu_eff_iso, #+",PflowTight_VarRad,PflowTight_FixedRad"
    # systs
    "m_inputAlgoSystNames"      : "OverlapRemovalAlgo_Syst",
    "m_outputAlgoSystNames"     : "MuonSelector_Syst",
    "m_systName"                : systName,
    # trigger
    "m_singleMuTrigChains"      : muon_trigger_matching_chains[period],
    "m_useRun3navigation"       : doRun3TriggerNav,
    "m_trigInputPrefix"         : "AnalysisTrigMatch_" if options.isPHYSLITE else "",
    # others
    "m_isRun3Geo"               : is_run3,
    "m_removeCosmicMuon"        : True,
    "m_removeEventBadMuon"      : do_skim,
})


# ------------------------------------------------------------------------------
# Muon Efficiency Calculator.
# ------------------------------------------------------------------------------
# Takes preselected muons as input -> all preselected (and baseline in the shallow container copy after OR) muons have SF decorators.
# SF weight calculation only takes signal selected leptons into account, hence we use the signal WPs in this EfficiencyCorrector.

#code to get relative path for m_custom_dir_muon_trigger_SF
pwd = os.getcwd()
# Go up one level from 'run' to repo root (adjust number of '..' as needed)
repo_root = os.path.abspath(os.path.join(pwd, ".."))
#m_custom_dir_muon_trigger_SF = os.path.join(repo_root, "tmp_2024_mu_trig_SF")
m_custom_dir_muon_trigger_SF = os.path.join(repo_root, "source/LJAlgo/data/tmp_mu_trig_SF")


c.algorithm("MuonEfficiencyCorrector", {
    "m_name"                     : "MuonEfficiencyCorrector",
    # "m_msgLevel"                 : "DEBUG",
    "m_inContainerName"          : "Muons_PreSelected",
    "m_WorkingPointReco"         : mu_eff_reco,
    "m_WorkingPointIso"          : mu_eff_iso,
    "m_WorkingPointTTVA"         : mu_eff_TTVA,
    "m_AllowZeroSF"              : False,
    "m_MuTrigLegs"               : "2022:HLT_mu24_ivarmedium_L1MU14FCH_OR_HLT_mu50_L1MU14FCH,2023:HLT_mu24_ivarmedium_L1MU14FCH_OR_HLT_mu50_L1MU14FCH,2024:HLT_mu24_ivarmedium_L1MU14FCH_OR_HLT_mu50_L1MU14FCH",
    "m_custom_dir"               : "root://eosatlas.cern.ch:1094//eos/atlas/atlascerngroupdisk/phys-exotics/lpx/ANA-EXOT-2024-32", 
#    "m_custom_dir"               : "../tmp_2024_mu_trig_SF",#for local test
    "m_inputSystNamesMuons"      : "MuonPreSelector_Syst",
    "m_systNameReco"             : systNameWeight, #,MUON_EFF_RECO_SYS_LOWPT,MUON_EFF_RECO_STAT_LOWPT
    "m_systNameIso"              : systNameWeight,
    "m_systNameTTVA"             : systNameWeight,
    "m_systValReco"              : systValWeight,
    "m_systValIso"               : systValWeight,
    "m_systValTTVA"              : systValWeight,
    "m_systNameTrig"             : systNameWeight,
    "m_systValTrig"              : systValWeight,
    "m_overrideCalibRelease"     : "250418_Preliminary_r24run3" if is_run3 else "230213_Preliminary_r22run2", #release 25.2.53
})


# ------------------------------------------------------------------------------
# Hadronic Tau Signal Selection.
# ------------------------------------------------------------------------------
c.algorithm("TauSelector", {
    "m_name"                    : "TauSelector",
    "m_inContainerName"         : "TauJets_Baseline" if options.useTaus else "TauJets_PreSelected",
    "m_outContainerName"        : "TauJets_Selected",
    "m_createSelectedContainer" : False,
    "m_decorateSelectedObjects" : True,
    "m_ConfigPath"              : "LJAlgo/tau_selection_medium.conf"
})


# ------------------------------------------------------------------------------
# MET Reconstruction, takes preselected leptons and calibrated jets.
# ------------------------------------------------------------------------------
c.algorithm("METConstructor", {
    "m_name"                      : "METConstructor",
    "m_mapName"                   : "METAssoc_AntiKt4EMPFlow" if not options.isPHYSLITE else "METAssoc_AnalysisMET",
    "m_coreName"                  : "MET_Core_AntiKt4EMPFlow" if not options.isPHYSLITE else "MET_Core_AnalysisMET",
    "m_outputContainer"           : "MET_Final",
    "m_inputJets"                 : "AntiKt4EMPFlowJets_Calib",
    "m_inputTaus"                 : "TauJets_PreSelected" if options.useTaus else "",
    # "m_inputPhotons"              : "Photons_Selected",
    "m_inputElectrons"            : "Electrons_PreSelected",
    "m_inputMuons"                : "Muons_PreSelected",
    "m_doPFlow"                   : True,
    "m_jetSystematics"            : "AntiKt4EMPFlowJets_Calib_Algo",
    "m_calculateSignificance"     : True,
    "m_significanceTreatPUJets"   : False,
    "m_significanceSoftTermReso"  : 10.0,
    "m_dofJVTCut"                 : False,
    "m_doJVTCut"                  : True,
    "m_rebuildUsingTracksInJets"  : False, # True would mean to calculate TrackMET
    "m_systName"                  : systName,
    "m_systVal"                   : systVal,
    "m_runNominal"                : systVal == 0,
    "m_outputAlgoSystNames"       : "MET_Final_Syst",
    "m_eleSystematics"            : "ElectronPreSelector_Syst",
    "m_muonSystematics"           : "MuonPreSelector_Syst",
})













# ------------------------------------------------------------------------------
# LJ Ntuple Making.
# ------------------------------------------------------------------------------
c.algorithm("LJAlgo", {
    "m_name"                      : "LJAlgo",
    "m_msgLevel"                  : "INFO",
    "m_crossSectionFile"          : crossSectionFile,

    # containers to use
    "m_truthmuContainerName"      : "TruthMuons_Selected",
    "m_truthelContainerName"      : "TruthElectrons_Selected",
    "m_truthtauContainerName"     : "TruthTaus_Selected",
    "m_truthjetContainerName"     : "AntiKt4TruthDressedWZJets_Selected",
    "m_muContainerName"           : "Muons_Baseline",
    "m_elContainerName"           : "Electrons_Baseline",
    "m_tauContainerName"          : "TauJets_Baseline" if options.useTaus else "",
    "m_jetContainerName"          : "AntiKt4EMPFlowJets_PassedOR",
    "m_METContainerName"          : "MET_Final",

    # skimming
    # "m_leadJetPtSkim"             : -1.0  if do_skim else -1.0,
    # "m_leadLepPtSkim"             : 130.0 if do_skim else -1.0,
    # "m_mLepJetSkim"               : 700.0 if do_skim else -1.0,
    "m_mLepLepSkim"               : 130.0 if do_skim else -1.0,

    # which skimming to use
    "m_writeEleChannel"           : doElectrons, # use this flag to have events with electrons
    "m_writeMuonChannel"          : doMuons, # use this flag to have events with muons
    "m_writeDiLepton"             : doDilep, # use this flag to have dilepton events in your tree
    "m_writeLeptonJet"            : doLepJet, # use this flag to have lepton+jet events in your tree

    # what to save from each object
    "m_evtDetailStr"              : "pileup pileupsys beamspotweight weightsSys",
    "m_evtDetailStrSyst"          : "pileup beamspotweight",
    "m_trigDetailStr"             : "", # basic passTriggers
    "m_muDetailStr"               : "kinematic",
    "m_elDetailStr"               : "kinematic",
    "m_tauDetailStr"              : "kinematic",
    "m_jetDetailStr"              : "kinematic", # jetBTag_DL1dv01_FixedCutBEff_77
    "m_METDetailStr"              : "metTrk sigTrk" if options.doSystematics else "metTrk sigTrk refEle refMuons refJet softTrk",
    "m_truthParticlesDetailStr"   : "kinematic",
    "m_truthJetDetailStr"         : "kinematic",

    # what extra branches to save
    "m_writeLeptonVectorBranches" : False, # use this flag to write out the vector electron_* and muon_* branches
    "m_writeTruthLeptonBranches"  : False, # use this flag to write out the vector truth_el_* and truth_mu_* branches
    "m_writeTruthJetBranches"     : True, # use this flag to write out the vector truth_jet_* branches
    "m_writeBaseLeptons"          : True, # use this flag if you want to have baseline leptons in the LepPlusJet part of the tree

    "m_useTaus"                   : True if options.useTaus else False,

    # triggers
    "m_doTrigMatch"               : True, #false means all leps are trig matched;
    "m_triggerList"               : "" if options.doSystematics else ",".join(triggers), # xAH can't deal with vectors of strings here yet, unfortunately ...
    
    # ------------- Scale Factors
    # electrons
    "m_elWP_Reco"                 : electrons_reco_wp,
    "m_elWP_ID"                   : electrons_signal_id_wp_efficiency_tool,
    "m_elWP_Iso"                  : electrons_signal_iso_wp,
    "m_elWP_IsoTrig"              : electrons_signal_trigger_iso_wp, # Special case: Run 3 trigger SFs are not available with HighPtCaloOnly iso WP
    "m_dielWP_Trig"               : dielectron_trig,
    
    # muons
    "m_muWP_Reco"                 : mu_eff_reco,
    "m_muWP_Iso"                  : mu_eff_iso,
    "m_muWP_TTVA"                 : mu_eff_TTVA,
    "m_muWP_Trig15"               : mu_eff_trig15,
    "m_muWP_Trig"                 : mu_eff_trig,
    
    # b-tagging
    "m_BtaggerName"               : btaggerName,
    "m_BtaggerWP"                 : btag_operatingPt,
    "m_BtaggerCut"                : cuts_from_WP[btag_WP],
    "m_writeAllBTagWPs"           : write_all_effs,
    
    # systs
    "m_muSystsName"               : "OverlapRemovalAlgo_Syst" if options.doSystematics else "", # before OR: MuonPreSelector_Syst
    "m_elSystsName"               : "OverlapRemovalAlgo_Syst" if options.doSystematics else "", # before OR: ElectronPreSelector_Syst
    "m_jetSystsName"              : "OverlapRemovalAlgo_Syst" if options.doSystematics else "", # before OR: AntiKt4EMPFlowJets_Selected_Algo
    "m_metSystsName"              : "MET_Final_Syst" if options.doSystematics else "",
    # "m_btagSystsName"             : "BJetEfficiency_Algo" if options.doSystematics else "", # b-tag systematics are weight systematics!
    "m_doSystematics"             : options.doSystematics,
    "m_doWeightSystematics"       : WeightSystematics,
    
    # others
    "m_treeBasketSize"            : 2000 if options.doSystematics else -1, # use 2kB buffers when processing systematics; TODO: optimize this ...
    "m_noSkim"                    : options.noSkim,
})
