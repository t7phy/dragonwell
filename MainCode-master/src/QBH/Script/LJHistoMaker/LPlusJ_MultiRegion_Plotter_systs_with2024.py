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
import math
from HistPlotter import HistPlotter
import pandas as pd
import os
import argparse
import numpy as np
import array

def GetLogBinning(nbins, xmin, xmax):  ## use function to construct Logarithmic binning
    logmin  = np.log10(xmin)
    logmax  = np.log10(xmax)
    logbinwidth =  (logmax-logmin)/nbins
    xbins = [xmin,]
    for i in range(1, nbins+1):
        xbins.append(ROOT.TMath.Power( 10,(logmin + i*logbinwidth) ))
    arrxbins = array.array("d", xbins)
    return nbins, arrxbins

def f7(seq):
    seen = set()
    seen_add = seen.add
    return [x for x in seq if not (x in seen or seen_add(x))]

def GetFakeCuts(cuts):
    fake_cuts = []
    for cut in cuts:
        if cut == "lepton1_isSig == 1":
            fake_cut = "lepton1_isIDMedium > 0.5"
        elif cut == "n_signal_lep == 1" or cut == "n_signal_lep >= 1":
            fake_cut = "1"
        else:
            fake_cut = cut
        fake_cuts.append(fake_cut)
    return f7(fake_cuts)


def br_single_flavour_modification(weight):
    return f"(1.0/3.0) * {weight}"


def find_closest_value_blinding_edge(data_tuple, N):
    values = data_tuple[1]
    closest_value = min(values, key=lambda x: abs(x - N))
    return closest_value

print("about to print OMP_NUM_THREADS below: ####################################")
os.system("echo ${OMP_NUM_THREADS}")
# Initialize a plotter instance (specify output directory, cuts (in list format), and string of weights)

# df = pd.read_csv('/srv01/agrp/roybr/LPlusJ/LJHistoMaker/share/lplusj_plotting_config.csv')
# processes = df['Process'].tolist()


# channels = ["el"]
#channels = ["el", "mu"]
#lhc_runs = ["Run2", "Run3"]
# lhc_runs = ["Run3"]

parser = argparse.ArgumentParser(prog='MultiRegion_Plotter')
parser.add_argument('--channel', help='lepton flavour: el or mu')
parser.add_argument('--run', help='LHC run: Run2 or Run3')
parser.add_argument('--variation_name', help='systematic uncertainty name')
parser.add_argument('--variation_weight', help='weight varied by a systematic uncertainty')
parser.add_argument('--variation_type', help='systematics uncertainty type: calib (tree), SF or MC (theory)')

args = parser.parse_args()

name_syst   = args.variation_name
weight_syst = args.variation_weight
type_syst   = args.variation_type

channels = [args.channel]
lhc_runs = [args.run]

include2024 = "yes"  # "yes", "only", "no"

# doFakes (True-fakes, False-dijet) affect "el" channel only, dijet is used in "mu" always
doFakes = True

print ("This is name_syst:   ", name_syst)
print ("This is weight_syst: ", weight_syst)
print ("This is type_syst:   ", type_syst)
print ("include2024:         ", include2024)
print ("doFakes:             ", doFakes)

#print("exiting for now")
#exit()


#base_path = "/storage/agrp/roybr/leptonplusjet_ntuples/LJSkim_v6.0_FullSyst/merged/Run3/"
#path_VV = "/storage/agrp/roybr/leptonplusjet_ntuples/LJSkim_v6.0_nominal/Run3/"

#base_path = "/storage/agrp/roybr/leptonplusjet_ntuples/LJSkim_v7.0_FullSyst/merged/Run3/"

#base_path80 = "/storage/agrp/roybr/leptonplusjet_ntuples/LJSkim_v8.0_nominal/merged/"
#base_path90 = "/storage/agrp/roybr/leptonplusjet_ntuples/LJSkim_v9.0_FullSyst/merged/"

#fakes_path = "/storage/agrp/roybr/leptonplusjet_skimmedtrees/fakes/"

base_path = "/data/projects/exotics/ANA-EXOT-2024-12/LJSkim_v7.0_FullSyst/merged/"
base_path90 = "/data/projects/exotics/ANA-EXOT-2024-32/LJSkim_v9.0_FullSyst/merged/"
fakes_path = "/data/projects/exotics/ANA-EXOT-2024-32/fakes/"

## example of paths to use in af.uchicago
# base_path = "/data/projects/exotics/ANA-EXOT-2024-12/LJSkim_v6.0_FullSyst/merged/"
# path_VV = "/data/dbuchin/Ntuples/LJSkim_v6.0_merged/"

# base_path = "/data/projects/exotics/ANA-EXOT-2024-12/LJSkim_v7.0_FullSyst/merged/"
# fakes_path = "/data/projects/exotics/ANA-EXOT-2024-32/"

# base_path80 = "/data/projects/exotics/ANA-EXOT-2024-32/LJSkim_v8.0/merged/"

n_cores = 4

#exit()



for lhc_run in lhc_runs:
    for channel in channels:

        #################
        #regions massses#
        #################
        CR_mLepJet   = "mLepJet > 1000 && mLepJet < 2000"
        VR_mLepJet   = "mLepJet > 2000 && mLepJet < 3000"
        CRVR_mLepJet = "mLepJet > 1000 && mLepJet < 3000"
        SR_mLepJet   = "mLepJet > 3000"
        Full_mLepJet = "mLepJet > 700"  ## for full spectrum (Spec region)
        cuts_dict = {"1": "No cut", CR_mLepJet: "CR mass range", VR_mLepJet: "VR mass range",
                    CRVR_mLepJet: "CR+VR mass range", SR_mLepJet: "SR mass range",
                    Full_mLepJet: "Full mass range"}

        ##########################
        #channel & lepton flavour#
        ##########################
        if channel == "mu":
            lepton_flavour = "lepton1_isEl == 0"
            cuts_dict[lepton_flavour] = "Leading muon"
        elif channel == "el":
            lepton_flavour = "lepton1_isEl == 1"
            cuts_dict[lepton_flavour] = "Leading electron"

        #########
        #trigger#
        #########
        #if channel == "mu": trig = "((lepton_singleleptrigMatched == 1) && ( (year == 2015 && (HLT_mu20_iloose_L1MU15 == 1 || HLT_mu50 == 1)) || ((year == 2016 || year == 2017 || year == 2018) && (HLT_mu26_ivarmedium == 1 || HLT_mu50 == 1)) || ((year == 2022 || year == 2023) && (HLT_mu24_ivarmedium_L1MU14FCH == 1 || HLT_mu50_L1MU14FCH == 1)) ))"
        #elif channel == "el": trig = "((lepton_singleleptrigMatched == 1) && ( (year == 2015 && (HLT_e24_lhmedium_L1EM20VH == 1 || HLT_e60_lhmedium == 1 || HLT_e120_lhloose == 1)) || ((year == 2016 || year == 2017 || year == 2018) && (HLT_e26_lhtight_nod0_ivarloose == 1 || HLT_e60_lhmedium_nod0 == 1 || HLT_e140_lhloose_nod0 == 1)) || (year == 2022 && (HLT_e26_lhtight_ivarloose_L1EM22VHI == 1 || HLT_e60_lhmedium_L1EM22VHI == 1 || HLT_e140_lhloose_L1EM22VHI == 1 )) || (year == 2023 && (HLT_e26_lhtight_ivarloose_L1eEM26M == 1 || HLT_e60_lhmedium_L1eEM26M == 1 || HLT_e140_lhloose_L1eEM26M == 1)) ))"
        trig = "(lepton_singleleptrigMatched == 1) && (HLT_singleLep == 1)"
        cuts_dict[trig] = "1-lepton trigger"

        ###############
        #signal lepton#
        ###############
        lepton1_signal = "lepton1_isSig == 1"
        cuts_dict[lepton1_signal] = "lepton1 is signal"

        lepton1_noSignal = "lepton1_isSig == 0"
        cuts_dict[lepton1_noSignal] = "lepton1 is no signal"

        nsignalleps = "n_signal_lep == 1"
        cuts_dict[nsignalleps] = "only 1 signal lepton"

        ################
        #leading lepton#
        ################
        leadlepton_pt = "lepton1_pt > 150"
        cuts_dict[leadlepton_pt] = "lepton1 p_{T} > 150"
        if channel == "mu": leadlepton_eta = "abs(lepton1_eta) < 2.5"
        elif channel == "el": leadlepton_eta = "abs(lepton1_eta) < 2.47 && !(abs(lepton1_eta) > 1.37 && abs(lepton1_eta) < 1.52)"

        ################
        #medium lepton##
        ################
        lepton_medium = "lepton1_isIDMedium > 0.5"
        cuts_dict[lepton_medium] = "lepton1 is IDMedium"

        ##################
        #lepton-jet cuts##
        ##################
        dPhiLepJet = "dphiLepJet > 2.8"
        cuts_dict[dPhiLepJet] = "#Delta#phi > 2.8"

        dEtaLepJet = "detaLepJet < 3.25"
        cuts_dict[dEtaLepJet] = "#Delta#eta < 3.25"

        ##################
        #####MET cuts#####
        ##################
        if channel == "mu":
            MET_sig = "metFinalTrkSignificance > 3.5"
            cuts_dict[MET_sig] = "#sigma(E_{T}^{miss}) > 3.5"
        elif channel == "el":
            MET_sig = "metFinalTrkSignificance > 5.0"
            cuts_dict[MET_sig] = "#sigma(E_{T}^{miss}) > 5.0"
        #anti_MET_sig = "metFinalTrkSignificance < 3.5"
        #cuts_dict[anti_MET_sig] = "#sigma(E_{T}^{miss}) < 3.5"

        ##############################
        #####fake validation cuts#####
        ##############################
        #MET = "metFinalTrk > 20 && metFinalTrk < 80"
        #MET = "metFinalTrk > 20"
        #mT  = "mt_lep1 > 20"
        #dR  = "dRLepJet > 1.0"
        #zerosignalleps = "n_signal_lep < 1"
        #noleptoniso = "lepton1_isIso < 1"
        #lepton_not_signal = "lepton1_isSig == 0"

####################################################################

        ##################
        ###dilepton cuts##
        ##################
        if channel == "mu":
            dilepton_flavour = "lepton1_isEl == 0 && lepton2_isEl == 0" 
            cuts_dict[dilepton_flavour] = "2 muons"
        elif channel == "el":
            dilepton_flavour = "lepton1_isEl == 1 && lepton2_isEl == 1"
            cuts_dict[dilepton_flavour] = "2 electrons"

        dilepton_nsignalleps = "n_signal_lep == 2"
        cuts_dict[dilepton_nsignalleps] = "N signal leptons = 2"

        dilepton_mass = "dilepton_m > 60 && dilepton_m < 120"
        cuts_dict[dilepton_mass] = "60 < m_{ll} < 120"

        #anti_dilepton_mass = "(dilepton_m > 120) || (dilepton_m < 0)"
        anti_dilepton_mass = "(dilepton_m > 120 || dilepton_m < 0)"
        cuts_dict[anti_dilepton_mass] = "m_{ll} < 0 || m_{ll} > 120"

        # dilepton_charge = "lepton1_charge == -lepton2_charge"
        # cuts_dict[dilepton_charge] = "OS leptons"

        ###################
        #####fake cuts#####
        ###################
        fakeCR_MET_sig = "metFinalTrkSignificance < 3.0"
        cuts_dict[fakeCR_MET_sig] = "#sigma(E_{T}^{miss}) < 3.0"

        fakeVR_MET_sig = "metFinalTrkSignificance > 3.0 && metFinalTrkSignificance < 5.0"
        cuts_dict[fakeVR_MET_sig] = "3.0 < #sigma(E_{T}^{miss}) < 5.0"

        fake_dR = "dRLepJet > ROOT::Math::Pi()"
        cuts_dict[fake_dR] = "#DeltaR > #pi"

        ##############
        #dijet cuts###
        ##############
        # Rejection of dijet samples with low m_jj to exclude spikes in m_lj spectrum (small number of events with huge weights)
        if   lhc_run == "Run2":
            jjCut_JZ = "(datasetNumber < 364700 || datasetNumber > 364702)"
        elif lhc_run == "Run3":
            # jjCut_JZ = "(datasetNumber < 801165 || datasetNumber > 801167)"
            jjCut_JZ = "(datasetNumber < 801165 || datasetNumber > 801167) && !(datasetNumber == 801168 && eventNumber == 172909902)"
        cuts_dict[jjCut_JZ] = "jj-JZ0-JZ2 excluded"

        # print(f"cuts_dict = {cuts_dict}")
        # exit()


        #############
        #nlepton cuts#
        #############
        n_leptons = "n_lep == 1" #to orthogonalise WCRVR from ZCRVR
        cuts_dict[n_leptons] = "N leptons = 1"
####################################################################

        ##############
        #Regions cuts#
        ##############
        ## The cuts sequences were specified to get more correct regions definition and cutflow:
        # base_cut = [lepton_flavour, trig]
        if doFakes and channel == "el": 
            base_cut = [lepton_flavour, trig]
        else:
            base_cut = [lepton_flavour, trig, jjCut_JZ]

        signal_cut = [lepton1_signal, nsignalleps, leadlepton_pt, leadlepton_eta, dPhiLepJet, dEtaLepJet]  ## signal signature selection

        cuts_WCRVR = base_cut + [CRVR_mLepJet] + signal_cut + [MET_sig] + [n_leptons]
        cuts_ZCRVR = base_cut + [CRVR_mLepJet, lepton1_signal, dilepton_flavour, dilepton_nsignalleps, dilepton_mass]
        cuts_SR    = base_cut + [SR_mLepJet]   + signal_cut + [n_leptons]
        cuts_Spec  = base_cut + [Full_mLepJet] + signal_cut  ## Full spectrum cuts

        cuts_fakeCR = base_cut + [CRVR_mLepJet, leadlepton_pt, fakeCR_MET_sig, anti_dilepton_mass]#, dPhiLepJet, dEtaLepJet]
        cuts_fakeVR = base_cut + [CRVR_mLepJet, lepton1_signal, nsignalleps, leadlepton_pt, leadlepton_eta, fakeVR_MET_sig] #dPhiLepJet, dEtaLepJet]



        Spec_mass_log_binning = GetLogBinning(20, 0.999, 11.5)
        blinding_edge = find_closest_value_blinding_edge(Spec_mass_log_binning, 3.0)
        blinding_edge = blinding_edge*1e3

        #cuts_Spec_data = cuts_Spec + ["mLepJet < 3000"]
        # cuts_Spec_data = cuts_Spec + ["mLepJet < " + str(blinding_edge)]
        cuts_Spec_data = []
        cuts_Spec_data += cuts_Spec
        for i in range(0, len(cuts_Spec_data)):
            if cuts_Spec_data[i] == Full_mLepJet:
                cuts_Spec_data[i] = "mLepJet > 700 && mLepJet < " + str(blinding_edge)
                break



        ## Old regions cuts
        # cuts = [Full_mLepJet, lepton_flavour, trig, lepton1_signal,nsignalleps, leadlepton_pt, dPhiLepJet, dEtaLepJet, MET_sig]
        # cuts_WCRVR=["mLepJet > 1000 && mLepJet <3000"]+cuts[1:-1]+[MET_sig]

        # cuts_SR = cuts_WCRVR[:-1] #SR cuts don't include the MET_sig
        # cuts_SR = ["mLepJet > 3000"]+cuts_SR[1:]

        # cuts_ZCRVR = ["mLepJet > 1000 && mLepJet <3000", dilepton_flavour, trig, dilepton_nsignalleps, dilepton_mass]#, dPhiLepJet, dEtaLepJet]


####################################################################


        ## needed region can be excluded/added into regions dictionary by comment/uncomment
        regions = {}
        regions["WCRVR"] = cuts_WCRVR
        regions["ZCRVR"] = cuts_ZCRVR

        regions["SR"] = cuts_SR
        regions["SRspec"] = cuts_Spec

        #regions["fakeCR"] = cuts_fakeCR
        #regions["fakeVR"] = cuts_fakeVR


        for region in regions:
            if channel=="mu" and "fake" in region: continue
            cuts = regions[region]
            fake_cuts = GetFakeCuts(cuts)
            Ncuts = len(cuts)

            #cuts_ttbarCorrectionAttempt = cuts + ["weight_gen<1000"]

            #cuts_jjCorrectionAttempt = cuts + ["weight_gen<339744"]

            print ("This is channel:     ", channel)
            print ("This is region:      ", region)
            print ("Nuber of cuts =      ", Ncuts)
            print ("These are the cuts:  ", cuts)
            print ("Nuber of fake_cuts = ", len(fake_cuts))
            print ("These are fake cuts: ", fake_cuts)
            #continue


            #weight="mcEventWeight*beamSpotWeight*weight_gen*weight_lumi*weight_norm*weight_singleleptonTrigSF*weight_lepton*weight_pileup"
            #myPlotter = HistPlotter(outputDirectory = "./plotterTest_DataMC/", cuts = ["lepton1_isEl == 0", "mLepJet > 0"], weight=weight)

            weight = "weight_gen * weight_lumi * mcEventWeight * weight_norm * weight_jvt * weight_btag * weight_lepton * weight_singleleptonTrigSF * weight_pileup * beamSpotWeight"
            fake_weight = "fakeweight"

            if "fakes" in type_syst:
                fake_weight = weight_syst
                weight_syst = weight

            tree_name_nominal = "LJAlgo/nominal"
            if "calib" in type_syst:
                tree_name = "LJAlgo/"+name_syst
            else:
                tree_name = "LJAlgo/nominal"

            ## Roy's output path
            #outputDirectory = "./LPLUSJ_Plots/Validation/" + lhc_run + "/" + channel+"_v6.0_test_syst_"+name_syst
            print("=============================")
            print ("this is name_syst: ", name_syst)
            print("=============================")
            
            if "nominal" not in name_syst:
                if include2024 == "yes" or include2024 == "only":
                    outputDirectory = "/storage/agrp/roybr/leptonplusjet_histos/2022_2024/Systematics/" + lhc_run + "/" + channel + "/" + region + "/" + name_syst
                else:
                    outputDirectory = "/storage/agrp/roybr/leptonplusjet_histos/Systematics/" + lhc_run + "/" + channel + "/" + region + "/" + name_syst
            else:
                if include2024 == "yes" or include2024 == "only":
                    outputDirectory = "/storage/agrp/roybr/leptonplusjet_histos/2022_2024/Systematics/" + lhc_run + "/" + channel + "/" + region
                else:
                    outputDirectory = "/storage/agrp/roybr/leptonplusjet_histos/Systematics/" + lhc_run + "/" + channel + "/" + region

            ## examples of output path in af.uchicago; "name_syst" includs "nominal" directory
            outputDirectory = "/data/yfu/QBHRepository/LJHistoMaker/share/run/" + lhc_run + "_" + channel + "/" + region + "/" + name_syst

            myPlotter = HistPlotter(outputDirectory=outputDirectory, cuts=cuts, weight=weight, regions=regions)

            if lhc_run=="Run2":
                Sherpa_version = "2211"
                mc             = "20"
            elif lhc_run=="Run3":
                Sherpa_version = "2214"
                mc             = "23"

            if not type_syst == "MC_Top": thisWeight = weight_syst
            else:  thisWeight = weight

            print ("printing the weight to be used w/ V+jets:")
            print ("thisWeight:   ", thisWeight)


            if include2024 == "yes" or include2024 == "only":
                myPlotter.AddNewProcess("Wjets", base_path90+lhc_run+"_Wenu_Sherpa"+Sherpa_version+"_mc"+mc+"e_merged.root", tree_name, True, color = ROOT.kCyan, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Wjets", base_path90+lhc_run+"_Wmnu_Sherpa"+Sherpa_version+"_mc"+mc+"e_merged.root", tree_name, True, color = ROOT.kCyan, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Wjets", base_path90+lhc_run+"_Wtnu_Sherpa"+Sherpa_version+"_mc"+mc+"e_merged.root", tree_name, True, color = ROOT.kCyan, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Zjets", base_path90+lhc_run+"_Zee_Sherpa"+Sherpa_version+"_mc"+mc+"e_merged.root", tree_name, True, color = ROOT.kGreen, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Zjets", base_path90+lhc_run+"_Zmm_Sherpa"+Sherpa_version+"_mc"+mc+"e_merged.root", tree_name, True, color = ROOT.kGreen, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Zjets", base_path90+lhc_run+"_Ztt_Sherpa"+Sherpa_version+"_mc"+mc+"e_merged.root", tree_name, True, color = ROOT.kGreen, style = "background",weight=thisWeight)
            if include2024 != "only":
                myPlotter.AddNewProcess("Wjets", base_path+lhc_run+"_Wenu_Sherpa"+Sherpa_version+"_mc"+mc+"a_merged.root", tree_name, True, color = ROOT.kCyan, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Wjets", base_path+lhc_run+"_Wenu_Sherpa"+Sherpa_version+"_mc"+mc+"d_merged.root", tree_name, True, color = ROOT.kCyan, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Wjets", base_path+lhc_run+"_Wmnu_Sherpa"+Sherpa_version+"_mc"+mc+"a_merged.root", tree_name, True, color = ROOT.kCyan, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Wjets", base_path+lhc_run+"_Wmnu_Sherpa"+Sherpa_version+"_mc"+mc+"d_merged.root", tree_name, True, color = ROOT.kCyan, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Wjets", base_path+lhc_run+"_Wtnu_Sherpa"+Sherpa_version+"_merged.root", tree_name, True, color = ROOT.kCyan, style = "background",weight=thisWeight)
                #myPlotter.AddNewProcess("Wjets", base_path+lhc_run+"_Wtnu_Sherpa"+Sherpa_version+"_mc"+mc+"d_merged.root", tree_name, True, color = ROOT.kCyan, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Zjets", base_path+lhc_run+"_Zee_Sherpa"+Sherpa_version+"_mc"+mc+"a_merged.root", tree_name, True, color = ROOT.kGreen, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Zjets", base_path+lhc_run+"_Zee_Sherpa"+Sherpa_version+"_mc"+mc+"d_merged.root", tree_name, True, color = ROOT.kGreen, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Zjets", base_path+lhc_run+"_Zmm_Sherpa"+Sherpa_version+"_mc"+mc+"a_merged.root", tree_name, True, color = ROOT.kGreen, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Zjets", base_path+lhc_run+"_Zmm_Sherpa"+Sherpa_version+"_mc"+mc+"d_merged.root", tree_name, True, color = ROOT.kGreen, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("Zjets", base_path+lhc_run+"_Ztt_Sherpa"+Sherpa_version+"_merged.root", tree_name, True, color = ROOT.kGreen, style = "background",weight=thisWeight)


            print ("about to add top processes")
            print ("weight:       ", weight)
            print ("weight_syst:  ", weight_syst)            

            if not type_syst == "MC_Sherpa": thisWeight = weight_syst
            else:  thisWeight = weight
            if include2024 == "yes" or include2024 == "only":
                myPlotter.AddNewProcess("ttbar", base_path90+lhc_run+"_ttbar_mc23e_merged.root", tree_name, True, color = ROOT.kRed +1, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("single-t", base_path90+lhc_run+"_singletop_schan_mc23e_merged.root", tree_name, True, color = ROOT.kGreen +2, style = "background",weight=thisWeight)
                #myPlotter.AddNewProcess("single-t", base_path90+lhc_run+"_singletop_tchan_mc23e_merged.root", tree_name, True, color = ROOT.kGreen +2, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("single-t", base_path90+lhc_run+"_singletop_Wt_incl_mc23e_merged.root", tree_name, True, color = ROOT.kGreen +2, style = "background",weight=thisWeight)
            if include2024 != "only":
                myPlotter.AddNewProcess("ttbar", base_path+lhc_run+"_ttbar_merged.root", tree_name, True, color = ROOT.kRed +1, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("single-t", base_path+lhc_run+"_singletop_schan_merged.root", tree_name, True, color = ROOT.kGreen +2, style = "background",weight=thisWeight)
                #myPlotter.AddNewProcess("single-t", base_path+lhc_run+"_singletop_tchan_merged.root", tree_name, True, color = ROOT.kGreen +2, style = "background",weight=thisWeight)
                myPlotter.AddNewProcess("single-t", base_path+lhc_run+"_singletop_Wt_incl_merged.root", tree_name, True, color = ROOT.kGreen +2, style = "background",weight=thisWeight)


            if type_syst == "SF": thisWeight = weight_syst ##VV only has SF systs
            else: thisWeight = weight
            if include2024 == "yes" or include2024 == "only":
                myPlotter.AddNewProcess("VV", base_path90+lhc_run+"_diboson_mc23e_merged.root", tree_name, True, color = ROOT.kOrange, style = "background", weight=thisWeight)
            if include2024 != "only":
                myPlotter.AddNewProcess("VV", base_path+lhc_run+"_diboson_merged.root", tree_name_nominal, True, color = ROOT.kOrange, style = "background", weight=thisWeight)

            ## ttV and jj only have SF and calib systs; 
            ## single-t tchannel has different PDF set than rest of top bkgs. so not varying it (small xs)
            if "MC" not in type_syst: thisWeight = weight_syst
            else:  thisWeight = weight
            if include2024 == "yes" or include2024 == "only":
                myPlotter.AddNewProcess("ttV", base_path90+lhc_run+"_ttV_mc23e_merged.root", tree_name, True, color = ROOT.kBlue, style = "background", weight=thisWeight)
                myPlotter.AddNewProcess("single-t", base_path90+lhc_run+"_singletop_tchan_mc23e_merged.root", tree_name, True, color = ROOT.kGreen +2, style = "background",weight=thisWeight)
            if include2024 != "only":
                myPlotter.AddNewProcess("ttV", base_path+lhc_run+"_ttV_merged.root", tree_name, True, color = ROOT.kBlue, style = "background", weight=thisWeight)
                myPlotter.AddNewProcess("single-t", base_path+lhc_run+"_singletop_tchan_merged.root", tree_name, True, color = ROOT.kGreen +2, style = "background",weight=thisWeight)


            #if doFakes and channel == "el" and include2024 != "only":
            #    myPlotter.AddNewProcess("fakes", fakes_path+lhc_run+"_fakes_datadriven_inclusive_HLT_singleLep_120125_MediumBaseline.root", "LJAlgo/nominal", True, color = ROOT.kMagenta, style = "background", weight="weight_gen", cuts=fake_cuts)
            if doFakes and channel == "el" and include2024=="yes":
                #myPlotter.AddNewProcess("fakes", fakes_path+lhc_run+"_2022_2024_fakes_datadriven_inclusive_HLT_singleLep_060725_MediumBaseline.root", "LJAlgo/nominal", True, color = ROOT.kMagenta, style = "background", weight="weight_gen", cuts=fake_cuts)            
                myPlotter.AddNewProcess("fakes", fakes_path+lhc_run+"_2022_2024_fakes_datadriven_inclusive_HLT_singleLep_160925_MediumBaseline_STAT_SYST_UNCERT_ATTEMPT.root", "LJAlgo/nominal", True, color = ROOT.kMagenta, style = "background", weight=fake_weight, cuts=fake_cuts)

            else:
                if type_syst == "SF": thisWeight = weight_syst
                else: thisWeight = weight
                if include2024 == "yes" or include2024 == "only":
                    myPlotter.AddNewProcess("jj", base_path90+lhc_run+"_dijet_Pythia_mc23e_merged.root", tree_name, True, color = ROOT.kMagenta, style = "background",weight=thisWeight)
                if include2024 != "only" and include2024 != "no":
                    myPlotter.AddNewProcess("jj", base_path+lhc_run+"_dijet_Pythia_merged.root", tree_name, True, color = ROOT.kMagenta, style = "background",weight=thisWeight)
                    #myPlotter.AddNewProcess("jj", base_path90+lhc_run+"_dijet_mc23e_merged.root", tree_name, True, color = ROOT.kMagenta, style = "background",weight=thisWeight)




            if "spec" in region: data_cuts = cuts_Spec_data
            else:                data_cuts = cuts

            #if "SR" not in region:
            if include2024 == "only":
                #myPlotter.AddNewProcess("data", base_path90+lhc_run+"_data24_merged.root", "LJAlgo/nominal", False, cuts=data_cuts, style="data")                    
                myPlotter.AddNewProcess("data", base_path90+lhc_run+"_data24_merged.root", "LJAlgo/nominal", False, style="data")
            elif include2024 == "yes":
                #myPlotter.AddNewProcess("data", base_path90+lhc_run+"_data_merged.root", "LJAlgo/nominal", False, cuts=data_cuts, style="data")
                #myPlotter.AddNewProcess("data", base_path+lhc_run+"_data_merged.root", "LJAlgo/nominal", False, style="data")
                myPlotter.AddNewProcess("data", base_path90+lhc_run+"_data_merged.root", "LJAlgo/nominal", False, style="data")
            else:
                #myPlotter.AddNewProcess("data", base_path+lhc_run+"_data_merged.root", "LJAlgo/nominal", False, cuts=data_cuts, style="data")
                myPlotter.AddNewProcess("data", base_path+lhc_run+"_data_merged.root", "LJAlgo/nominal", False, style="data")


            if "SR" in region or  "Spec" in region:
                if "MC" not in type_syst: #no theory systs for signals
                    weight_signal = weight_syst
                    weight_signal = br_single_flavour_modification(weight_signal) #temporary 'till fixed upstream
                else:
                    weight_signal = weight
                    weight_signal = br_single_flavour_modification(weight_signal) #temporary 'till fixed upstream

                sig_channel = channel
                if include2024 == "yes":
                    sig_path = base_path90 + "/QBHSignal_Yao/"
                    sig_mc = ""
                elif include2024 == "no":
                    sig_path = base_path
                    sig_mc = ""
                elif include2024 == "only":
                    sig_channel = "no"
                    # sig_path = base_path90
                    # sig_mc = "mc23e_"

                if sig_channel == "el":
                    myPlotter.AddNewProcess("ADDn6_m8.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901972"), True, style="signal", color = ROOT.kMagenta, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn6_m8.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901973"), True, style="signal", color = ROOT.kOrange, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn6_m9.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901974"), True, style="signal", color = ROOT.kCyan, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn6_m9.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901975"), True, style="signal", color = ROOT.kSpring, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn6_m10.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901976"), True, style="signal", color = ROOT.kBlue, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn6_m10.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901977"), True, style="signal", color = ROOT.kRed, weight=weight_signal)

                    myPlotter.AddNewProcess("ADDn4_m8.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901978"), True, style="signal", color = ROOT.kMagenta+1, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn4_m8.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901979"), True, style="signal", color = ROOT.kOrange+1, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn4_m9.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901980"), True, style="signal", color = ROOT.kCyan+1, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn4_m9.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901981"), True, style="signal", color = ROOT.kSpring+1, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn4_m10.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901982"), True, style="signal", color = ROOT.kBlue+1, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn4_m10.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901983"), True, style="signal", color = ROOT.kRed+1, weight=weight_signal)

                    myPlotter.AddNewProcess("ADDn2_m8.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901984"), True, style="signal", color = ROOT.kMagenta+2, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn2_m8.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901985"), True, style="signal", color = ROOT.kOrange+2, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn2_m9.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901986"), True, style="signal", color = ROOT.kCyan+2, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn2_m9.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901987"), True, style="signal", color = ROOT.kSpring+2, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn2_m10.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901988"), True, style="signal", color = ROOT.kBlue+2, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn2_m10.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901989"), True, style="signal", color = ROOT.kRed+2, weight=weight_signal)

                    myPlotter.AddNewProcess("RSn1_m6.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901990"), True, style="signal", color = ROOT.kMagenta+3, weight=weight_signal)
                    myPlotter.AddNewProcess("RSn1_m6.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901991"), True, style="signal", color = ROOT.kOrange+3, weight=weight_signal)
                    myPlotter.AddNewProcess("RSn1_m7.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901992"), True, style="signal", color = ROOT.kCyan+3, weight=weight_signal)
                    myPlotter.AddNewProcess("RSn1_m7.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901993"), True, style="signal", color = ROOT.kSpring+3, weight=weight_signal)
                    myPlotter.AddNewProcess("RSn1_m8.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901994"), True, style="signal", color = ROOT.kBlue+3, weight=weight_signal)
                    myPlotter.AddNewProcess("RSn1_m8.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetel_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901995"), True, style="signal", color = ROOT.kRed+3, weight=weight_signal)
                    pass
                elif sig_channel == "mu":
                    myPlotter.AddNewProcess("ADDn6_m8.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901996"), True, style="signal", color = ROOT.kMagenta, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn6_m8.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901997"), True, style="signal", color = ROOT.kOrange, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn6_m9.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901998"), True, style="signal", color = ROOT.kCyan, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn6_m9.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_901999"), True, style="signal", color = ROOT.kSpring, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn6_m10.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902000"), True, style="signal", color = ROOT.kBlue, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn6_m10.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902001"), True, style="signal", color = ROOT.kRed, weight=weight_signal)

                    myPlotter.AddNewProcess("ADDn4_m8.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902002"), True, style="signal", color = ROOT.kMagenta+1, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn4_m8.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902003"), True, style="signal", color = ROOT.kOrange+1, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn4_m9.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902004"), True, style="signal", color = ROOT.kCyan+1, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn4_m9.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902005"), True, style="signal", color = ROOT.kSpring+1, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn4_m10.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902006"), True, style="signal", color = ROOT.kBlue+1, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn4_m10.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902007"), True, style="signal", color = ROOT.kRed+1, weight=weight_signal)

                    myPlotter.AddNewProcess("ADDn2_m8.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902008"), True, style="signal", color = ROOT.kMagenta+2, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn2_m8.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902009"), True, style="signal", color = ROOT.kOrange+2, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn2_m9.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902010"), True, style="signal", color = ROOT.kCyan+2, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn2_m9.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902011"), True, style="signal", color = ROOT.kSpring+2, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn2_m10.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902012"), True, style="signal", color = ROOT.kBlue+2, weight=weight_signal)
                    myPlotter.AddNewProcess("ADDn2_m10.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902013"), True, style="signal", color = ROOT.kRed+2, weight=weight_signal)

                    myPlotter.AddNewProcess("RSn1_m6.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902014"), True, style="signal", color = ROOT.kMagenta+3, weight=weight_signal)
                    myPlotter.AddNewProcess("RSn1_m6.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902015"), True, style="signal", color = ROOT.kOrange+3, weight=weight_signal)
                    myPlotter.AddNewProcess("RSn1_m7.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902016"), True, style="signal", color = ROOT.kCyan+3, weight=weight_signal)
                    myPlotter.AddNewProcess("RSn1_m7.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902017"), True, style="signal", color = ROOT.kSpring+3, weight=weight_signal)
                    myPlotter.AddNewProcess("RSn1_m8.0", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902018"), True, style="signal", color = ROOT.kBlue+3, weight=weight_signal)
                    myPlotter.AddNewProcess("RSn1_m8.5", sig_path+lhc_run+"_QBHPy8EG_QBH_jetmu_"+sig_mc+"merged.root", tree_name.replace("LJAlgo","LJAlgo_902019"), True, style="signal", color = ROOT.kRed+3, weight=weight_signal)



            ###################################################################
            ###plotting###
            ###################################################################

            if   channel == "el": lep_string, lepjet_string, dilep_string = "e1", "ej", "ee"
            elif channel == "mu": lep_string, lepjet_string, dilep_string = "#mu1", "#muj", "#mu#mu"

            isRun3=True if lhc_run=="Run3" else False

            if "CR" in region or "VR" in region:
                ## R_min is Y axis minimum of Ratio panel in "DataMC" plots; upper bound will be (2.0 - R_min)
                ## by default R_min = 0.7; recommeded values: -0.2, 0.25, 0.4, 0.7, 0.75, 0.85, 0.94, 0.97
                if "fake" in region: R_min = 0.4
                else:                R_min = 0.7
                nLogBins,xLogBins = GetLogBinning(20,150,1500)
                myPlotter.AddNewPlot("LeadingLeptonPt.pdf", ["lepton1_pt"], [nLogBins, xLogBins], xTitle='p^{'+lep_string+'}_{T} [GeV]',logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)
                myPlotter.AddNewPlot("LeadingJetPt.pdf", ["jet1_pt"], [nLogBins, xLogBins], xTitle='p^{j1}_{T} [GeV]',logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)

                if channel == "el": eta_bins = [70, -2.47, 2.47]
                elif channel == "mu": eta_bins = [70, -2.5, 2.5]
                myPlotter.AddNewPlot("LeadingLeptonEta.pdf", ["lepton1_eta"], eta_bins, xTitle='#eta_{'+lep_string+'}', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=R_min)
                myPlotter.AddNewPlot("LeadingLeptonPhi.pdf", ["lepton1_phi"], [20, -3.5, 3.5], xTitle='#phi_{'+lep_string+'}', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=R_min)
                # myPlotter.AddNewPlot("LeadingLeptonP.pdf", ["ROOT::Math::PtEtaPhiMVector(lepton1_pt, lepton1_eta, lepton1_phi, lepton1_m).P()/1000"], [35, 0, 3.5], xTitle='p_{'+lep_string+'} [TeV]',logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=R_min)
                # myPlotter.AddNewPlot("LeadingLeptonE.pdf", ["ROOT::Math::PtEtaPhiMVector(lepton1_pt, lepton1_eta, lepton1_phi, lepton1_m).E()/1000"], [35, 0, 3.5], xTitle='E_{'+lep_string+'} [TeV]',logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=R_min)
                nLogBins,xLogBins = GetLogBinning(35, 0.1, 3.5)
                myPlotter.AddNewPlot("LeadingLeptonP.pdf", ["ROOT::Math::PtEtaPhiMVector(lepton1_pt, lepton1_eta, lepton1_phi, lepton1_m).P()/1000"], [nLogBins, xLogBins], xTitle='p_{'+lep_string+'} [TeV]',logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)
                myPlotter.AddNewPlot("LeadingLeptonE.pdf", ["ROOT::Math::PtEtaPhiMVector(lepton1_pt, lepton1_eta, lepton1_phi, lepton1_m).E()/1000"], [nLogBins, xLogBins], xTitle='E_{'+lep_string+'} [TeV]',logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)

                myPlotter.AddNewPlot("LeadingJetEta.pdf", ["jet1_eta"], [70, -2.4, 2.4], xTitle='#eta_{j1}', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=R_min)
                myPlotter.AddNewPlot("LeadingJetPhi.pdf", ["jet1_phi"], [20, -3.5, 3.5], xTitle='#phi_{j1}', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=R_min)
                # myPlotter.AddNewPlot("LeadingJetE.pdf", ["jet1_E/1000"], [45, 0, 4.5], xTitle='E_{j1} [TeV]',logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)
                # myPlotter.AddNewPlot("LeadingJetP.pdf", ["ROOT::Math::PtEtaPhiEVector(jet1_pt, jet1_eta, jet1_phi, jet1_E).P()/1000"], [45, 0, 4.5], xTitle='p_{j1} [TeV]',logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)
                myPlotter.AddNewPlot("LeadingJetY.pdf", ["ROOT::Math::PtEtaPhiEVector(jet1_pt, jet1_eta, jet1_phi, jet1_E).y()"], [20, -10.0, 10.0], xTitle='y_{j1}',logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=-0.2)
                nLogBins,xLogBins = GetLogBinning(45, 0.1, 4.5)
                myPlotter.AddNewPlot("LeadingJetE.pdf", ["jet1_E/1000"], [nLogBins, xLogBins], xTitle='E_{j1} [TeV]',logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)
                myPlotter.AddNewPlot("LeadingJetP.pdf", ["ROOT::Math::PtEtaPhiEVector(jet1_pt, jet1_eta, jet1_phi, jet1_E).P()/1000"], [nLogBins, xLogBins], xTitle='p_{j1} [TeV]',logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)

                myPlotter.AddNewPlot("detaLepJet.pdf", ["detaLepJet"], [26, 0, 5.2], xTitle='#Delta#eta_{'+lepjet_string+'}', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=R_min)
                myPlotter.AddNewPlot("dphiLepJet.pdf", ["dphiLepJet"], [22, 0, 3.3], xTitle='#Delta#phi_{'+lepjet_string+'}', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=R_min)
                myPlotter.AddNewPlot("dRLepJet.pdf", ["dRLepJet"], [31, 0, 6.2], xTitle='#DeltaR_{'+lepjet_string+'}', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=R_min)
                # myPlotter.AddNewPlot("dphiLepJet27.pdf", ["dphiLepJet"], [20, 2.7, 3.2], xTitle='#Delta#phi_{'+lepjet_string+'}', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024)
                # myPlotter.AddNewPlot("dRLepJet25.pdf", ["dRLepJet"], [25, 2.5, 5], xTitle='#DeltaR_{'+lepjet_string+'}', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024)

                myPlotter.AddNewPlot("metFinalTrkSumEt.pdf", ["metFinalTrkSumEt/1000"], [42, 0, 4.2], xTitle='Sum(E_{T}) [TeV]', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)
                #myPlotter.AddNewPlot("metFinalTrk.pdf", ["metFinalTrk"], [30, 0, 1500], xTitle='E^{miss}_{T} [GeV]', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)
                myPlotter.AddNewPlot("metFinalTrkSignificance.pdf", ["metFinalTrkSignificance"], [35, 0, 35], xTitle='#sigma(E^{miss}_{T})', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)
                myPlotter.AddNewPlot("njet.pdf", ["njet"], [15, 0, 15], xTitle='n_{jet}', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)
                # myPlotter.AddNewPlot("mt_lep1.pdf",["mt_lep1"],[25,0,250], xTitle='m^{#ell 1}_{T}', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)


                myPlotter.AddNewPlot("mLepJet.pdf", ["mLepJet/1000"], [2, 1, 3], xTitle='m_{'+lepjet_string+'} [TeV]', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("mLepJetCR.pdf", ["mLepJet/1000"], [20, 1, 2], xTitle='m_{'+lepjet_string+'} [TeV]', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=R_min)
                myPlotter.AddNewPlot("mLepJetVR.pdf", ["mLepJet/1000"], [20, 2, 3], xTitle='m_{'+lepjet_string+'} [TeV]', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=-0.2)
                myPlotter.AddNewPlot("mLepJetCRVRCombine.pdf", ["mLepJet/1000"], [40, 1, 3], xTitle='m_{'+lepjet_string+'} [TeV]', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=-0.2)

                nLogBins, xLogBins = GetLogBinning(20, 1.0, 3.)
                myPlotter.AddNewPlot("mLepJetCRVR.pdf", ["mLepJet/1000"], [nLogBins, xLogBins], xTitle='m_{'+lepjet_string+'} [TeV]', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=-0.2)

                # Add a second output plot for the above process. Show functionality of custom binning and logscale.
                #nLogBins, xLogBins = GetLogBinning(10, 0.999, 3.)
                nLogBins, xLogBins = GetLogBinning(10, 1.0, 3.)
                myPlotter.AddNewPlot("mLepJetCRVR_logX.pdf", ["mLepJet/1000"], [nLogBins, xLogBins], xTitle="m_{"+lepjet_string+"} [TeV]", logX=True, logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.7)

                ## style="none" by default - "total_bkg" and "data" will only plot in this case:
                myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], [25, 0, 5, 25, 0, 5], xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", isRun3=isRun3, include2024=include2024)

                ## Draw of all backgrounds, if style="all_bkg":
                # myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], [25, 0, 5, 25, 0, 5], xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", style="all_bkg", isRun3=isRun3, include2024=include2024)


                if region=="WCRVR":
                    myPlotter.AddNewPlot("mt_lep1.pdf",["mt_lep1"],[25,0,250], xTitle='m^{#ell 1}_{T}', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)
                    #myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], [25, 0, 5, 25, 0, 5], xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", style="Wjets", isRun3=isRun3, include2024=include2024)

                if region=="ZCRVR":
                    myPlotter.AddNewPlot("m_ll.pdf", ["dilepton_m"], [24, 60, 120], xTitle='m_{'+dilep_string+'} [GeV]', logY=True, style="DataMC", isRun3=isRun3, include2024=include2024, R_min=0.4)
                    #myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], [25, 0, 5, 25, 0, 5], xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", style="Zjets", isRun3=isRun3, include2024=include2024)

                if "fake" in region:
                    if doFakes:
                        myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], [25, 0, 5, 25, 0, 5], xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", style="fakes", isRun3=isRun3, include2024=include2024)
                    else:
                        myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], [25, 0, 5, 25, 0, 5], xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", style="jj", isRun3=isRun3, include2024=include2024)

            elif region=="SR":
                R_min = -0.2
                nLogBins,xLogBins = GetLogBinning(20, 100, 4000)
                myPlotter.AddNewPlot("LeadingLeptonPt.pdf", ["lepton1_pt"], [nLogBins, xLogBins], xTitle='p^{'+lep_string+'}_{T} [GeV]',logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("LeadingLeptonEta.pdf", ["lepton1_eta"], [10, -3.0, 3.0], xTitle='#eta_{'+lep_string+'}', logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("LeadingLeptonPhi.pdf", ["lepton1_phi"], [10, -3.5, 3.5], xTitle='#phi_{'+lep_string+'}', logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)

                myPlotter.AddNewPlot("LeadingJetPt.pdf", ["jet1_pt"], [nLogBins, xLogBins], xTitle='p^{j1}_{T} [GeV]',logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("LeadingJetEta.pdf", ["jet1_eta"], [10, -3.0, 3.0], xTitle='#eta_{j1}', logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("LeadingJetPhi.pdf", ["jet1_phi"], [10, -3.5, 3.5], xTitle='#phi_{j1}', logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)

                myPlotter.AddNewPlot("mLepJet.pdf", ["mLepJet/1000"], [10, 3, 13], xTitle="m_{"+lepjet_string+"} [TeV]", logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("mLepJet20.pdf", ["mLepJet/1000"], [20, 3, 13], xTitle="m_{"+lepjet_string+"} [TeV]", logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("mLepJet40.pdf", ["mLepJet/1000"], [40, 3, 13], xTitle="m_{"+lepjet_string+"} [TeV]", logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("mLepJetSR.pdf", ["mLepJet/1000"], [14, 3, 17], xTitle="m_{"+lepjet_string+"} [TeV]", logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("mLepJetSR1bin.pdf", ["mLepJet/1000"], [1, 3, 17], xTitle="m_{"+lepjet_string+"} [TeV]", logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)
                nLogBins, xLogBins = GetLogBinning(8, 2.999, 11.)
                myPlotter.AddNewPlot("mLepJetSR_logX.pdf", ["mLepJet/1000"], [nLogBins, xLogBins], xTitle="m_{"+lepjet_string+"} [TeV]", logX=True, logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("metFinalTrkSignificance.pdf", ["metFinalTrkSignificance"], [10, 0, 30], xTitle='#sigma(E^{miss}_{T})', logY=True, style="SigVsBkg", isRun3=isRun3, include2024=include2024)

                if   channel == "el": binning = [35, 0, 7, 35, 0, 7]
                elif channel == "mu": binning = [35, 0, 14, 35, 0, 7]
                myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], binning, xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], binning, xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", style="Wjets", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], binning, xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", style="Zjets", isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], binning, xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", style="ADDn6_m8.0", isRun3=isRun3, include2024=include2024)
                if doFakes and channel == "el":
                    myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], binning, xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", style="fakes", isRun3=isRun3, include2024=include2024)
                else:
                    myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], binning, xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", style="jj", isRun3=isRun3, include2024=include2024)

                ## Draw of all backgrounds and/or all signals (style= "all_bkg" or "all_sig"):
                # myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], binning, xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", style="all_bkg", isRun3=isRun3, include2024=include2024)
                # myPlotter.AddNewPlot("lep1pt_jet1pt.pdf", ["lepton1_pt/1000", "jet1_pt/1000"], binning, xTitle="Leading lepton p_{T} [TeV]", yTitle="Leading jet p_{T} [TeV]", style="all_sig", isRun3=isRun3, include2024=include2024)


            elif "spec" in region:
                R_min = 0.4
                nLogBins,xLogBins = GetLogBinning(20,100,4000)
                myPlotter.AddNewPlot("LeadingLeptonPt.pdf", ["lepton1_pt"], [nLogBins, xLogBins], xTitle='p^{'+lep_string+'}_{T} [GeV]',logY=True, isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("LeadingLeptonEta.pdf", ["lepton1_eta"], [20, -3.0, 3.0], xTitle='#eta_{'+lep_string+'}', logY=True, isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("LeadingLeptonPhi.pdf", ["lepton1_phi"], [20, -3.5, 3.5], xTitle='#phi_{'+lep_string+'}', logY=True, isRun3=isRun3, include2024=include2024)

                myPlotter.AddNewPlot("LeadingJetPt.pdf", ["jet1_pt"], [nLogBins, xLogBins], xTitle='p^{j1}_{T} [GeV]',logY=True, isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("LeadingJetEta.pdf", ["jet1_eta"], [20, -3.0, 3.0], xTitle='#eta_{j1}', logY=True, isRun3=isRun3, include2024=include2024)
                myPlotter.AddNewPlot("LeadingJetPhi.pdf", ["jet1_phi"], [20, -3.5, 3.5], xTitle='#phi_{j1}', logY=True, isRun3=isRun3, include2024=include2024)

                myPlotter.AddNewPlot("mLepJet.pdf", ["mLepJet/1000"], [30,0,15], xTitle="m_{"+lepjet_string+"} [TeV]", logY=True, isRun3=isRun3, include2024=include2024)
                nLogBins, xLogBins = GetLogBinning(25, 0.7, 15.)
                myPlotter.AddNewPlot("mLepJet_pad1.pdf", ["mLepJet/1000"], [nLogBins, xLogBins], xTitle="m_{"+lepjet_string+"} [TeV]", logX=True, logY=True, isRun3=isRun3, include2024=include2024)
                nLogBins, xLogBins = Spec_mass_log_binning
                myPlotter.AddNewPlot("mLepJet_logX.pdf", ["mLepJet/1000"], [nLogBins, xLogBins], xTitle="m_{"+lepjet_string+"} [TeV]", logX=True, logY=True, isRun3=isRun3, include2024=include2024)

                myPlotter.AddNewPlot("metFinalTrkSignificance.pdf", ["metFinalTrkSignificance"], [20, 0, 40], xTitle='#sigma(E^{miss}_{T})', logY=True, isRun3=isRun3, include2024=include2024, R_min=R_min)

            myPlotter.AddNewPlot("Cutflow_e.pdf", ["cutflow_e"], [Ncuts, 0, Ncuts], xTitle="Cutflow", yTitle="Number of Events", logY=True, style="cutflow", cutDict=cuts_dict, isRun3=isRun3, include2024=include2024)
            myPlotter.AddNewPlot("Cutflow_w.pdf", ["cutflow_w"], [Ncuts, 0, Ncuts], xTitle="Cutflow", yTitle="Weighted Events",  logY=True, style="cutflow", cutDict=cuts_dict, isRun3=isRun3, include2024=include2024)

            myPlotter.AddNewPlot("lepton1_IFFType.pdf", ["lepton1_IFFType"], [12, 0, 12], xTitle='IFFType_{'+lep_string+'}', logY=True, isRun3=isRun3, include2024=include2024)

            myPlotter.Launch(n_cores)
