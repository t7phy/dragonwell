from ROOT import TFile, TTree, TH1F, TCanvas, TList, gPad, THStack, TPad, TLegend
import ROOT
import time
import array
import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), "../"))
thisdir = os.path.dirname(os.path.abspath(__file__))
workdir = thisdir
outputdir = os.path.join(workdir, "InputRootFiles")

# [[setups]] 
import Tools.Prepared as prepared
prepared.AddAllVariables()
prepared.AddAllSystematics()
variables = prepared.variables
Systematics = prepared.All_Systematics
list_sys = list(Systematics.keys())


# [[set up 输入]] 
samplefiledir = os.path.join(workdir, "../samples/MadeSelection/splited/all_withsys")
filenames = [os.path.join(samplefiledir, "all_withsys_{}.root".format(systematic)) for systematic in list_sys]
files = [TFile(filename, "read") for filename in filenames]

datafiledir = os.path.join(workdir, "../samples/MadeSelection/splited/data")
datafilenames = [os.path.join(datafiledir, "data_{}.root".format(systematic)) for systematic in list_sys]
datafiles = [TFile(filename, "read") for filename in datafilenames]

# [[set up 多线程]] 
from Tools.tools import MyPoolRun_systematic
from Tools.tools import info, warning, error

# [[--------------BEGIN ANALYSIS--------------]] 

def GetBackgrounds(systematic, VarName, RegionName, SignalName):
    # info("systematic: ", systematic)
    file = files[list_sys.index(systematic)]
    tree = file.Get("evtTree")
    tree.AddFriend("FakeWeightTree", filenames[list_sys.index(systematic)])

    datafile = datafiles[list_sys.index(systematic)]
    datatree = datafile.Get("evtTree")
    datatree.AddFriend("FakeWeightTree", filenames[list_sys.index(systematic)])

    if RegionName == "100":
        RegionCut = "(isWZInclusive && PassZPtGT100 && (!PassZPtGT200) && PassPtWZLS70)"
    elif RegionName == "200":
        RegionCut = "(isWZInclusive && PassZPtGT200 && PassPtWZLS70)"
    elif RegionName == "70":
        RegionCut = "(isWZInclusive && PassPtWZLS70)"
    elif RegionName == "HPT":
        RegionCut = "(isWZInclusive && PassZPtGT100 && PassPtWZLS70)"

    # EventCatagoryType:1(data), 2(WZ), 3(other_irreducible), 4(ZFake), 5(ttbar), 6(polarized), 7(polarized_WithTau)
    if SignalName == "WZ":
        # 所有的成分包括：EventCatagoryType == 3 和 All * FakeWeight
        SignalCut = "(EventCatagoryType == 3 || EventCatagoryType == 7)"
    elif SignalName == "LL":
        SignalCut = "(EventCatagoryType == 3 || EventCatagoryType == 7 || (EventCatagoryType == 6 && EventCatagory != \"WLZL\"))"
    elif SignalName == "TT":
        SignalCut = "(EventCatagoryType == 3 || EventCatagoryType == 7 || (EventCatagoryType == 6 && EventCatagory != \"WTZT\"))"

    if len(VarName) > 4 and VarName[:4] == "abs_":
        tempVarName = "abs({})".format(VarName[4:])
    else:
        tempVarName = VarName

    # [[1.得到Fake成分]] 
    # [[1.1在oldsys文件中的那部分]] 
    # info("Begin to get fake component: ", systematic)
    name_fake = "hist_fake_{}_{}_{}_{}".format(SignalName, RegionName, VarName, systematic)
    hist_fake = variables[VarName][0].Clone(name_fake)
    hist_fake.Reset()
    hist_fake.Sumw2()
    tempname1 = "{}>>{}".format(tempVarName, name_fake)
    tempname2_1 = "({})".format(RegionCut)
    tempname2_2 = "(EventTotalWeight * FakeWeight * AdditionalKFactor)"
    tree.Draw(tempname1, "{} * {}".format(tempname2_1, tempname2_2), "goff")
    # [[1.2在datafile中的那部分]] 
    name_data = "hist_data_{}_{}_{}_{}".format(SignalName, RegionName, VarName, systematic)
    hist_fake_data = variables[VarName][0].Clone(name_data)
    hist_fake_data.Reset()
    hist_fake_data.Sumw2()
    tempname1 = "{}>>{}".format(tempVarName, name_data)
    tempname2_1 = "({})".format(RegionCut)
    tempname2_2 = "(FakeWeight * AdditionalKFactor)"
    datatree.Draw(tempname1, "{} * {}".format(tempname2_1, tempname2_2), "goff")

    # [[2.得到其他成分（irreducible and WithTau and something）]] 
    # info("Begin to get other component: ", systematic)
    name_other = "hist_other_{}_{}_{}_{}".format(SignalName, RegionName, VarName, systematic)
    hist_other = variables[VarName][0].Clone(name_other)
    hist_other.Reset()
    hist_other.Sumw2()
    tempname1 = "{}>>{}".format(tempVarName, name_other)
    tempname2_1 = "{} * {}".format(RegionCut, SignalCut)
    tempname2_2 = "(LeptonTightType==\"TTT\")"
    tempname2_3 = "EventTotalWeight*AdditionalKFactor"
    tree.Draw(tempname1, "{} * {} * {}".format(tempname2_1, tempname2_2, tempname2_3), "goff")

    # [[3.合并]] 
    hist_fake.Add(hist_other)
    hist_fake.Add(hist_fake_data)
    hist = hist_fake.Clone("hist_{}_{}_{}".format(RegionName, SignalName, systematic))
    # hist = hist_other.Clone("hist_{}_{}_{}".format(RegionName, SignalName, systematic))

    # [[4.检查bkg是否比data还大]] 
    hist_data = hist_fake_data.Clone("hist_data_{}_{}".format(RegionName, VarName))
    hist_data.Reset()
    hist_data.Sumw2()
    tempname1 = "{}>>hist_data_{}_{}".format(tempVarName, RegionName, VarName)
    tempname2 = "{} * (LeptonTightType==\"TTT\")".format(RegionCut)
    datatree.Draw(tempname1, tempname2, "goff")
    for i in range(hist.GetNbinsX()):
        data = hist_data.GetBinContent(i+1)
        if hist.GetBinContent(i+1) > data:
            warning("{}-{}-{}-{}-bin{}--Background is bigger than data: (-{}%)".format(SignalName, RegionName, VarName, systematic, i+1, (hist.GetBinContent(i+1) - data)/data*100))
            hist.SetBinContent(i+1, data)
    return hist




for RegionName in prepared.RegionNames:
    for SignalName in prepared.SignalNames:
        print("")
        info("RegionName: ", RegionName)
        info("SignalName: ", SignalName)
        print("")
        for VarName in variables.keys():
            info("Begin to process: ", VarName)
            result = MyPoolRun_systematic(list_sys, GetBackgrounds, [VarName, RegionName, SignalName])
            info("End of process: ", VarName, "begin to write to file")
            outfilename = os.path.join(outputdir, "{}-Region{}-{}-background.root".format(SignalName, RegionName, VarName))
            file = TFile(outfilename, "recreate")
            for systematic in list_sys:
                file.mkdir(systematic)
                file.cd(systematic)
                result[list_sys.index(systematic)].Write("reconstructed")
            file.Close()

