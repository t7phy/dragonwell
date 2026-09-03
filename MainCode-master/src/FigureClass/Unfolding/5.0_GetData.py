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
datafilename = os.path.join(workdir, "../samples/MadeSelection/data/data.root")

datafile = TFile(datafilename, "read")

from Tools.tools import info, warning, error


# [[--------------BEGIN ANALYSIS--------------]] 
def GetData(VarName, RegionName):
    tree = datafile.Get("evtTree")
    info("VarName: ", VarName)
    info("RegionName: ", RegionName)

    if RegionName == "100":
        RegionCut = "(isWZInclusive && PassZPtGT100 && (!PassZPtGT200) && PassPtWZLS70)"
    elif RegionName == "200":
        RegionCut = "(isWZInclusive && PassZPtGT200 && PassPtWZLS70)"
    elif RegionName == "70":
        RegionCut = "(isWZInclusive && PassPtWZLS70)"
    elif RegionName == "HPT":
        RegionCut = "(isWZInclusive && PassZPtGT100 && PassPtWZLS70)"


    if len(VarName) > 4 and VarName[:4] == "abs_":
        tempVarName = "abs({})".format(VarName[4:])
    else:
        tempVarName = VarName

    name = "hist_data_{}_{}".format(RegionName, VarName)
    hist = variables[VarName][0].Clone(name)
    hist.Reset()
    hist.Sumw2()
    tempname1 = "{}>>{}".format(tempVarName, name)
    tempname2 = "{} * (LeptonTightType==\"TTT\")".format(RegionCut)
    tree.Draw(tempname1, tempname2, "goff")

    return hist


# 注：不同的SignalName是一样的（SignalName是WZ/LL，用来表明signal是所有WZ事例还是只有LL事例）
# 注：但是可能分bin不一样。。。
for VarName in variables:
    for RegionName in prepared.RegionNames:
        for SignalName in prepared.SignalNames:
            hist = GetData(VarName, RegionName)
            outfilename = os.path.join(outputdir, "{}-Region{}-{}-data.root".format(SignalName, RegionName, VarName))
            outfile = TFile(outfilename, "recreate")
            outfile.mkdir("nominal")
            outfile.cd("nominal")
            hist.Write("reconstructed")
            outfile.Close()
