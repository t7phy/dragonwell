#!/usr/bin/env python3
import ROOT
from ROOT import (TFile, TTree, TH1, TH1F, TH1D, TH2, TH2F, TH2D, TH3F, 
                  TCanvas, TLegend, TPad, TGraph, TGraphErrors, TGraphAsymmErrors,
                  TF1, TF2, TF3, TMath, TVector2, TVector3, TLorentzVector,
                  TChain, TNtuple, TBranch, TLeaf, TCut, TTreeReader, TTreeReaderValue,
                  gROOT, gStyle, gPad, gDirectory, gSystem, gApplication,
                  TStyle, TColor, TPaveText, TLatex, TText, TLine, TBox, TArrow,
                  TRandom3, TStopwatch, TDatime, TString, TObjArray, TObjString,
                  kRed, kBlue, kGreen, kYellow, kMagenta, kCyan, kOrange, kViolet,
                  kBlack, kWhite, kGray, kTRUE, kFALSE)
import os
import numpy as np
import subprocess
import os
from get_systematics import SystematicsCollector
import argparse
import sys


def lepton_flavour_systematic(channel, name_syst):
    """
    function to avoid redundant runs --- over mu systs in el channel or over el systs in mu channel
    """
    if channel == "el":
        if ( ("MUON_" in name_syst) or ("weight_lepton" in name_syst and "MUON" in name_syst) or ("weight_singleleptonTrigSF" in name_syst and "MUON" in name_syst) ):
            print("skipping systematic (muon syst; el run")
            skip_run_flag = True
        else:
            skip_run_flag = False
    elif channel == "mu":
        if ( ("EL_" in name_syst) or ("EG_" in name_syst) or ("weight_lepton" in name_syst and "EL" in name_syst) or ("weight_singleleptonTrigSF" in name_syst and "EL" in name_syst) ):
            print("skipping systematic (el syst; mu run")
            skip_run_flag = True
        else:
            skip_run_flag = False

    return skip_run_flag




#############################
####unload user arguments####
#############################
allowed_systs_modes = ['nominal_only', 'SF', 'MC_Sherpa', 'MC_Top', 'calib', 'all']

parser = argparse.ArgumentParser(prog='myprogram')
parser.add_argument(
    '--systs_mode',
    help=f"Allowed options: {', '.join(allowed_systs_modes)}",
)
parser.add_argument('--run_pbs', action='store_true', help='if yes, submit jobs to PBS')
parser.add_argument('--run_condor', action='store_true', help='if yes, submit jobs to HTCondor')
args = parser.parse_args()

systs_mode  = args.systs_mode
run_pbs   = args.run_pbs
run_condor   = args.run_condor

# Check if the provided systs_mode is valid
if systs_mode and systs_mode not in allowed_systs_modes:
    print(f"Error: Invalid argument '{systs_mode}' for --systs_mode.")
    print(f"Allowed options are: {', '.join(allowed_systs_modes)}")
    sys.exit(1)

# Check if the batch mode is valid                  
if run_pbs and run_condor:
    print(f"Error: You can't run both on PBS and HTCondor!")
    sys.exit(1)


print("Executing steer_systs.py w/ the following args")
print(f"Running mode: {systs_mode}")
print(f"Batch mode (PBS): {'Yes' if run_pbs else 'No'}")
print(f"Batch mode (HTCondor): {'Yes' if run_condor else 'No'}")

#############################
#############################
#############################

def find_missing(expected, actual):
    missing = []
    for e in expected:
        if not any(a in e for a in actual):  # 文件里某个元素是 e 的子串，就算匹配
            missing.append(e)
    return missing


def run_script(script_name, *args):
    # Get the directory of the current script
    current_directory = os.path.dirname(os.path.abspath(__file__))
    
    # Construct the full path to the script to be run
    script_path = os.path.join(current_directory, script_name)
    
    try:
        # Run the script using subprocess with separated arguments        
        if ".sh" in script_name:
            subprocess.run(['/bin/bash', script_path] + list(args), check=True)
        else:
            subprocess.run(['python3', script_path] + list(args), check=True)
        print(f"{script_name} finished executing with arguments: {args}")
    except subprocess.CalledProcessError as e:
        print(f"Error while executing {script_name}: {e}")


## Roy's paths
#base_path = "/storage/agrp/roybr/leptonplusjet_ntuples/LJSkim_v6.0_fullSyst_merged/"
#base_path = "/storage/agrp/roybr/leptonplusjet_ntuples/LJSkim_v6.0_FullSyst/merged/Run3/"
base_path = "/data/projects/exotics/ANA-EXOT-2024-12/LJSkim_v7.0_FullSyst/merged/"

## path to use in af.uchicago
# base_path = "/data/projects/exotics/ANA-EXOT-2024-12/LJSkim_v6.0_FullSyst/merged/"
# base_path = "/data/projects/exotics/ANA-EXOT-2024-12/LJSkim_v7.0_FullSyst/merged/"

ntuples = [    
    "Run3_dijet_Pythia_merged.root",    
    #"Run3_QBHPy8EG_QBH_jetel_merged.root",
    #"Run3_QBHPy8EG_QBH_jetmu_merged.root",
    "Run3_singletop_schan_merged.root",
    #"Run3_singletop_tchan_merged.root",
    #"Run3_singletop_Wt_dilep_merged.root",
    #"Run3_singletop_Wt_incl_merged.root",
    "Run3_ttbar_merged.root",
    "Run3_ttV_merged.root",
    "Run3_Wenu_Sherpa2214_mc23a_merged.root",
    #"Run3_Wenu_Sherpa2214_mc23d_merged.root",
    "Run3_Wmnu_Sherpa2214_mc23a_merged.root",
    #"Run3_Wmnu_Sherpa2214_mc23d_merged.root",
    "Run3_Wtnu_Sherpa2214_merged.root",
    "Run3_Zee_Sherpa2214_mc23a_merged.root",
    #"Run3_Zee_Sherpa2214_mc23d_merged.root",
    "Run3_Zmm_Sherpa2214_mc23a_merged.root",
    #"Run3_Zmm_Sherpa2214_mc23d_merged.root",
    "Run3_Ztt_Sherpa2214_merged.root"
]


systematics_collector = SystematicsCollector(base_path, ntuples)

sf_systs     = systematics_collector.sf_systematics
calib_systs  = systematics_collector.calibration_systematics
theory_systs = systematics_collector.theory_systematics

sherpa_systs = systematics_collector.sherpa_systematics
top_systs    = systematics_collector.top_systematics

print(sf_systs)
print(calib_systs)
print(theory_systs)
print(sherpa_systs)
print(top_systs)

expected = sf_systs + calib_systs + theory_systs + sherpa_systs + top_systs

with open("mu.log") as f:
    actual = [line.strip() for line in f if line.strip()]

missing = find_missing(sf_systs, actual)

print("sf_systs:")
print(missing)
#for m in sorted(missing):
#    print("  ", m)

missing = find_missing(calib_systs, actual)

print("calib_systs:")
print(missing)

#for m in sorted(missing):
#    print("  ", m)

missing = find_missing(sherpa_systs, actual)

print("sherpa_systs:")
print(missing)
#for m in sorted(missing):
#    print("  ", m)

missing = find_missing(top_systs, actual)

print("top_systs:")
print(missing)
#for m in sorted(missing):
#    print("  ", m)

