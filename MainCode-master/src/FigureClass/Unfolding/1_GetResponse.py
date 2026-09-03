import os, sys
import ROOT
from ROOT import TH1F, TH2F, TFile, TList
import array
from time import sleep

sys.path.append(os.path.join(os.path.dirname(__file__), "../"))

# setups
import Tools.Prepared as prepared
prepared.AddAllVariables()
prepared.AddAllSystematics()
variables = prepared.variables
Systematics = prepared.All_Systematics
list_sys = list(Systematics.keys())

# setups
thisdir = os.path.dirname(os.path.abspath(__file__))
workdir = thisdir
outputdir = os.path.join(workdir, "InputRootFiles")

inputfiledir = os.path.join(workdir, "../samples/MadeSelection/splited/signal/")
filenames = [os.path.join(inputfiledir, "signal_{}.root".format(systematic)) for systematic in list_sys]
files = [TFile.Open(filename) for filename in filenames]


# [[set up 多线程]] 
from Tools.tools import MyPoolRun_systematic
from Tools.tools import info, warning, error

# [[--------------BEGIN ANALYSIS--------------]] 
result_hist_names = ["reconstructed", "fidcorrnum", "fidcorrden", "effcorrnum", "effcorrden", "puritynum", "stabilityden", "migration_matrix"]



# [[get response matrix]] 
def get_response_matrix(systematic, VarName, RegionName, SignalName):
    info("systematic: ", systematic)
    
    file = files[list_sys.index(systematic)]
    tree = file.Get("evtTree")
    NEntries = tree.GetEntries()

    # [[get hists]] 

    # weight = EventTotalWeight * AdditionalKFactor
    EventCatagory = ROOT.string()
    LeptonTightType = ROOT.string()
    EventTotalWeight = array.array('f', [0])
    EventTotalWeight_truth = array.array('f', [0])
    AdditionalKFactor = array.array('f', [0])
    isWZInclusive = array.array('b', [0])
    isWZInclusive_truth = array.array('b', [0])
    PassZPtGT100 = array.array('b', [0])
    PassZPtGT100_truth = array.array('b', [0])
    PassZPtGT200 = array.array('b', [0])
    PassZPtGT200_truth = array.array('b', [0])
    PassPtWZLS70 = array.array('b', [0])
    PassPtWZLS70_truth = array.array('b', [0])

    EventCatagoryType = array.array('i', [0])


    tree.SetBranchAddress("EventCatagory", ROOT.AddressOf(EventCatagory))
    tree.SetBranchAddress("LeptonTightType", ROOT.AddressOf(LeptonTightType))
    tree.SetBranchAddress("EventTotalWeight", EventTotalWeight)
    tree.SetBranchAddress("EventTotalWeight_truth", EventTotalWeight_truth)
    tree.SetBranchAddress("AdditionalKFactor", AdditionalKFactor)
    tree.SetBranchAddress("isWZInclusive", isWZInclusive)
    tree.SetBranchAddress("isWZInclusive_truth", isWZInclusive_truth)
    tree.SetBranchAddress("PassZPtGT100", PassZPtGT100)
    tree.SetBranchAddress("PassZPtGT100_truth", PassZPtGT100_truth)
    tree.SetBranchAddress("PassZPtGT200", PassZPtGT200)
    tree.SetBranchAddress("PassZPtGT200_truth", PassZPtGT200_truth)
    tree.SetBranchAddress("PassPtWZLS70", PassPtWZLS70)
    tree.SetBranchAddress("PassPtWZLS70_truth", PassPtWZLS70_truth)

    tree.SetBranchAddress("EventCatagoryType", EventCatagoryType)

    variable = array.array("f", [0])
    variable_truth = array.array("f", [0])

    if len(VarName) > 4 and VarName[:4] == "abs_":
        MakeAbs = True
        temp_VarName = VarName[4:]
    else:
        MakeAbs = False
        temp_VarName = VarName

    tree.SetBranchAddress(temp_VarName, variable)
    tree.SetBranchAddress(temp_VarName + "_truth", variable_truth)

    template_hist1d = variables[VarName][0]
    template_hist2d = variables[VarName][1]

    hReconstructed = template_hist1d.Clone("reconstructed_" + systematic)
    hFidcorrnum = template_hist1d.Clone("fidcorrnum_" + systematic)
    hFidcorrden = template_hist1d.Clone("fidcorrden_" + systematic)
    hEffcorrnum = template_hist1d.Clone("effcorrnum_" + systematic)
    hEffcorrden = template_hist1d.Clone("effcorrden_" + systematic)
    hPuritynum = template_hist1d.Clone("puritynum_" + systematic)
    hStabilityden = template_hist1d.Clone("stabilityden_" + systematic)
    hMigration_matrix = template_hist2d.Clone("migration_matrix_" + systematic)
    
    hReconstructed.Reset()
    hFidcorrnum.Reset()
    hFidcorrden.Reset()
    hEffcorrnum.Reset()
    hEffcorrden.Reset()
    hPuritynum.Reset()
    hStabilityden.Reset()
    hMigration_matrix.Reset()

    hReconstructed.Sumw2()
    hFidcorrnum.Sumw2()
    hFidcorrden.Sumw2()
    hEffcorrnum.Sumw2()
    hEffcorrden.Sumw2()
    hPuritynum.Sumw2()
    hStabilityden.Sumw2()
    hMigration_matrix.Sumw2()

    for entry in range(NEntries):
        tree.GetEntry(entry)

        if entry % 100000 == 0:
            info(systematic, ": ", entry, "/", NEntries, "(%.2f%%)" % (entry/NEntries*100))

        # [[get variables]] 
        if RegionName == "100":
            passRegion = isWZInclusive[0] * PassPtWZLS70[0] * (PassZPtGT100[0])
            passRegion_truth = isWZInclusive_truth[0] * PassPtWZLS70_truth[0] * (PassZPtGT100_truth[0]) * (not PassZPtGT200_truth[0])
        elif RegionName == "200":
            passRegion = isWZInclusive[0] * PassPtWZLS70[0] * PassZPtGT200[0]
            passRegion_truth = isWZInclusive_truth[0] * PassPtWZLS70_truth[0] * PassZPtGT200_truth[0]
        elif RegionName == "70":
            passRegion = isWZInclusive[0] * PassPtWZLS70[0]
            passRegion_truth = isWZInclusive_truth[0] * PassPtWZLS70_truth[0]
        elif RegionName == "HPT":
            passRegion = isWZInclusive[0] * PassPtWZLS70[0] * PassZPtGT100[0]
            passRegion_truth = isWZInclusive_truth[0] * PassPtWZLS70_truth[0] * PassZPtGT100_truth[0]

        if SignalName == "WZ":
            passSignal = (EventCatagoryType[0] == 6) and (LeptonTightType == "TTT")
        elif SignalName == "LL":
            passSignal = (EventCatagoryType[0] == 6) and (EventCatagory == "WLZL") and (LeptonTightType == "TTT")
        elif SignalName == "TT":
            passSignal = (EventCatagoryType[0] == 6) and (EventCatagory == "WTZT") and (LeptonTightType == "TTT")



        # [[1.Reco]] 
        value1 = variable[0] if not MakeAbs else abs(variable[0])
        weight1 = EventTotalWeight[0] * AdditionalKFactor[0]
        pass1 = passRegion * passSignal
        # [[2.Truth]] 
        value2 = variable_truth[0] if not MakeAbs else abs(variable_truth[0])
        weight2 = EventTotalWeight_truth[0] * AdditionalKFactor[0]
        pass2 = passRegion_truth * passSignal

        # [[fill hists]] 
        hReconstructed.Fill(value1, weight1 * pass1) # instruction
        # hReconstructed.Fill(value1, weight1 * pass1 * pass2)

        hFidcorrnum.Fill(value1, weight1 * pass1 * pass2)
        hFidcorrden.Fill(value1, weight1 * pass1)
        # hEffcorrnum.Fill(value2, weight2 * pass1 * pass2)    # try to fix the bug
        hEffcorrnum.Fill(value2, weight1 * pass1 * pass2)    # "instruction"
        hEffcorrden.Fill(value2, weight2 * pass2)     # "instruction"
        # hEffcorrden.Fill(value2, weight1 * pass2)     # try to fix the bug
        
        hPuritynum.Fill(value2, weight2 * pass1 * pass2)
        hStabilityden.Fill(value2, weight1 * pass1)
        hMigration_matrix.Fill(value1, value2, weight1 * pass1 * pass2) # instruction
        # hMigration_matrix.Fill(value2, value1, weight1 * pass1 * pass2) # try to fix the bug
    del tree
    return [hReconstructed, hFidcorrnum, hFidcorrden, hEffcorrnum, hEffcorrden, hPuritynum, hStabilityden, hMigration_matrix]


for RegionName in prepared.RegionNames:
    for SignalName in prepared.SignalNames:
        print("")
        info("RegionName: ", RegionName)
        info("SignalName: ", SignalName)
        print("")
        for VarName in variables.keys():
            info("Begin to process: ", VarName)
            result = MyPoolRun_systematic(list_sys, get_response_matrix, [VarName, RegionName, SignalName])
            info("End of process: ", VarName, "begin to write to file")
            outfilename = os.path.join(outputdir, "{}-Region{}-{}-response.root".format(SignalName, RegionName, VarName))
            file = TFile(outfilename, "recreate")
            for systematic in list_sys:
                file.mkdir(systematic)
                file.cd(systematic)
                for result_tag in result_hist_names:
                    result[list_sys.index(systematic)][result_hist_names.index(result_tag)].Write(result_tag)
            file.Close()

    