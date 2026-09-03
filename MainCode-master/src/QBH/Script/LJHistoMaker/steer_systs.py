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
            print("skipping systematic (muon syst; el run)")
            skip_run_flag = True
        else:
            skip_run_flag = False
    elif channel == "mu":
        if ( ("EL_" in name_syst) or ("EG_" in name_syst) or ("weight_lepton" in name_syst and "EL" in name_syst) or ("weight_singleleptonTrigSF" in name_syst and "EL" in name_syst) or ("fake") in name_syst):
            print("skipping systematic (el syst; mu run)")
            skip_run_flag = True
        else:
            skip_run_flag = False

    return skip_run_flag




#############################
####unload user arguments####
#############################
allowed_systs_modes = ['nominal_only', 'SF', 'MC_Sherpa', 'MC_Top', 'calib', 'fakes', 'all']

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
#base_path = "/storage/agrp/roybr/leptonplusjet_ntuples/LJSkim_v7.0_FullSyst/merged/Run3/"
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

fakes_systs = ["fakeweight_statup", "fakeweight_statdown", "fakeweight_systup", "fakeweight_systdown"]




nominal_weight = "weight_gen * weight_lumi * mcEventWeight * weight_norm * weight_jvt * weight_btag * weight_lepton * weight_singleleptonTrigSF * weight_pileup * beamSpotWeight"

sf_variation_weights  = []
sf_variation_names    = []

sf_variation_names_weights     = {}
sherpa_variation_names_weights = {}
top_variation_names_weights    = {}

fakes_variation_names_weights  = {}

for sf_syst in sf_systs:
    if "weight_lepton" in sf_syst:
        variation_weight = nominal_weight.replace("weight_lepton", sf_syst)
        variation_name   = sf_syst.replace("weight_lepton_", "")
    elif "weight_singleleptonTrigSF" in sf_syst:
        variation_weight = nominal_weight.replace("weight_singleleptonTrigSF", sf_syst)
        variation_name   = sf_syst.replace("weight_singleleptonTrigSF_", "")
    elif "weight_jvt" in sf_syst:
        variation_weight = nominal_weight.replace("weight_jvt", sf_syst)
        variation_name   = sf_syst.replace("weight_jvt_", "")
    else:
        continue
    sf_variation_weights.append(variation_weight)
    sf_variation_names.append(variation_name)
    sf_variation_names_weights[variation_name] = variation_weight ##dict assigning weight to name for SF systematics

#for calib syst in calib_systs:
#    variation_weight = nominal_weight
#    calib_variation_names.append(calib_syst)
calib_variation_names = calib_systs



for sherpa_syst in sherpa_systs:
    variation_weight = nominal_weight.replace("mcEventWeight", sherpa_syst)
    variation_name   = sherpa_syst.replace("mcEventWeight_", "")
    sherpa_variation_names_weights[variation_name] = variation_weight

for top_syst in top_systs:
    variation_weight = nominal_weight.replace("mcEventWeight", top_syst)
    variation_name   = top_syst.replace("mcEventWeight_", "")
    top_variation_names_weights[variation_name] = variation_weight

for fakes_syst in fakes_systs:
    variation_weight = fakes_syst
    variation_name   = fakes_syst
    fakes_variation_names_weights[variation_name] = variation_weight


##################################################################################################
############################## up until here, variations were collected###########################
##################################################################################################


channels    = ['el']

run         = 'Run3'


run_counter = 1
run_nominal = False




for channel in channels:
    print (f"in steer_systs.py; running channel {channel}")

    if run_nominal or systs_mode=="nominal_only" or systs_mode=="all":
        variation_name, variation_weight, variation_type = "nominal", nominal_weight, "nominal"
        print ("First, nominal run (no systematics)")
        if __name__ == "__main__":
            if run_pbs:
                run_script('pbs/submitter_wrapper.sh', channel, run, variation_name, variation_weight, variation_type)
            elif run_condor:
                run_script('condor/submit_to_condor.sh', channel, run, variation_name, variation_weight, variation_type)
            else:
                run_script('LPlusJ_MultiRegion_Plotter_systs_with2024.py', '--channel', channel, '--run', run, '--variation_name', variation_name, '--variation_weight', variation_weight, '--variation_type', variation_type)


    ########################################
    #######finished submitting nominal######
    ########################################


    ########################################
    ############running on SF systs#########
    ########################################


    if (systs_mode=="SF" or systs_mode=="all"):
        print ("about to run on SF systs")
        run_counter = 0
        for variation_name in sf_variation_names_weights:
            if lepton_flavour_systematic(channel,variation_name): continue
            variation_type = "SF"
            variation_weight = sf_variation_names_weights[variation_name]        
            if __name__ == "__main__":
                if run_pbs:
                    run_script('pbs/submitter_wrapper.sh', channel, run, variation_name, variation_weight, variation_type)
                elif run_condor:
                    run_script('condor/submit_to_condor.sh', channel, run, variation_name, variation_weight, variation_type)
                else:
                    run_script('LPlusJ_MultiRegion_Plotter_systs_with2024.py', '--channel', channel, '--run', run, '--variation_name', variation_name, '--variation_weight', variation_weight, '--variation_type', variation_type)
                run_counter += 1
            if run_counter>20000:
                break

    if (systs_mode=="calib" or systs_mode=="all"):
        print ("about to run on calib systs")
        run_counter = 0
        for variation_name in calib_variation_names:            
            if lepton_flavour_systematic(channel,variation_name): continue
            variation_type   = "calib"
            variation_weight = nominal_weight
            if __name__ == "__main__":
                run_counter += 1
                if run_counter>30000:
                    break
                if run_pbs:
                    run_script('pbs/submitter_wrapper.sh', channel, run, variation_name, variation_weight, variation_type)
                elif run_condor:
                    run_script('condor/submit_to_condor.sh', channel, run, variation_name, variation_weight, variation_type)
                else:
                    run_script('LPlusJ_MultiRegion_Plotter_systs_with2024.py', '--channel', channel, '--run', run, '--variation_name', variation_name, '--variation_weight', variation_weight, '--variation_type', variation_type)



    if ("MC" in systs_mode or systs_mode=="all"):
        print ("about to run on MC systs")
        run_counter = 0
        if "Sherpa" in systs_mode or systs_mode=="all":
            for variation_name in sherpa_variation_names_weights:
                print ("about to run on sherpa systs")
                variation_type   = "MC_Sherpa"
                variation_weight = sherpa_variation_names_weights[variation_name]
                if __name__ == "__main__":
                    run_counter += 1
                    if run_counter>10000:
                        break
                    if run_pbs:
                        run_script('pbs/submitter_wrapper.sh', channel, run, variation_name, variation_weight, variation_type)
                    elif run_condor:
                        run_script('condor/submit_to_condor.sh', channel, run, variation_name, variation_weight, variation_type)
                    else:
                        run_script('LPlusJ_MultiRegion_Plotter_systs_with2024.py', '--channel', channel, '--run', run, '--variation_name', variation_name, '--variation_weight', variation_weight, '--variation_type', variation_type)

        if "Top" in systs_mode or systs_mode=="all":
            for variation_name in top_variation_names_weights:
                    print ("about to run on top systs")
                    variation_type   = "MC_Top"
                    variation_weight = top_variation_names_weights[variation_name]
                    if __name__ == "__main__":
                        run_counter += 1
                        if run_counter>20000:
                            break
                        if run_pbs:
                            run_script('pbs/submitter_wrapper.sh', channel, run, variation_name, variation_weight, variation_type)
                        elif run_condor:
                            run_script('condor/submit_to_condor.sh', channel, run, variation_name, variation_weight, variation_type)
                        else:
                            run_script('LPlusJ_MultiRegion_Plotter_systs_with2024.py', '--channel', channel, '--run', run, '--variation_name', variation_name, '--variation_weight', variation_weight, '--variation_type', variation_type)

    if (systs_mode=="fakes" or systs_mode=="all"):
        print ("about to run on fakes systs")
        run_counter = 0
        for variation_name in fakes_variation_names_weights:
            if lepton_flavour_systematic(channel,variation_name): continue
            variation_type = "fakes"
            variation_weight = fakes_variation_names_weights[variation_name]
            #variation_weight = sf_variation_names_weights[variation_name]                    
            if __name__ == "__main__":
                run_counter += 1
                if run_counter>20000: break
                if run_pbs:
                    run_script('pbs/submitter_wrapper.sh', channel, run, variation_name, variation_weight, variation_type)
                elif run_condor:
                    run_script('condor/submit_to_condor.sh', channel, run, variation_name, variation_weight, variation_type)
                else:
                    run_script('LPlusJ_MultiRegion_Plotter_systs_with2024.py', '--channel', channel, '--run', run, '--variation_name', variation_name, '--variation_weight', variation_weight, '--variation_type', variation_type)

