import os, sys
import ROOT


# [[setups]]
thisdir = os.path.dirname(os.path.abspath(__file__))
sys.path.append(os.path.join(thisdir, ".."))
import Tools.Prepared as prepared
prepared.AddAllVariables()

variables = prepared.variables

from Tools.tools import info, warning, error, show
import Tools.unfoldTool as unfoldTool

inputdir = os.path.join(thisdir, "InputRootFiles")
outputdir = os.path.join(thisdir, "UnfoldingResults")
drawdir = os.path.join(thisdir, "DrawResults")

# METHOD = "Test"
METHOD = "Pseudo"
# METHOD = "Data"

unfold ={} 
draw ={} 

def MakeUnfolding(SignalName, RegionName, VarName, NIters, BestIter):
    info("{}-{}-{}-{}: Begin".format(SignalName, RegionName, VarName, NIters))
    # read-root name
    if METHOD == "Pseudo":
        filename_data = os.path.join(inputdir, "{}-Region{}-{}-pseudodata.root".format(SignalName, RegionName, VarName))
    elif METHOD == "Test":
        filename_data = os.path.join(inputdir, "{}-Region{}-{}-testdata.root".format(SignalName, RegionName, VarName))
    elif METHOD == "Data":
        filename_data = os.path.join(inputdir, "{}-Region{}-{}-data.root".format(SignalName, RegionName, VarName))
    else:
        error("Unknown METHOD: {}".format(METHOD))
    filename_bkg = os.path.join(inputdir, "{}-Region{}-{}-background.root".format(SignalName, RegionName, VarName))
    filename_response = os.path.join(inputdir, "{}-Region{}-{}-response.root".format(SignalName, RegionName, VarName))

    datafile = ROOT.TFile(filename_data)
    bkgfile = ROOT.TFile(filename_bkg)
    responsefile = ROOT.TFile(filename_response)

    tag = "{}-{}-{}-{}".format(SignalName, RegionName, VarName, METHOD)

    unfold[tag] = unfoldTool.BayesUnfoldTool(datafile, bkgfile, responsefile, NIters)
    unfold[tag].AddSystematic("EG_RESOLUTION_ALL__1down", "EG_RESOLUTION_ALL__1up")
    unfold[tag].AddSystematic('EG_SCALE_AF2__1down', 'EG_SCALE_AF2__1up')
    unfold[tag].AddSystematic('EG_SCALE_ALL__1down', 'EG_SCALE_ALL__1up')
    unfold[tag].AddSystematic('EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1down', 'EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1up')
    unfold[tag].AddSystematic('EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down', 'EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up')
    unfold[tag].AddSystematic('EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down', 'EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_B_0__1down', 'FT_EFF_Eigen_B_0__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_B_1__1down', 'FT_EFF_Eigen_B_1__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_B_2__1down', 'FT_EFF_Eigen_B_2__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_B_3__1down', 'FT_EFF_Eigen_B_3__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_B_4__1down', 'FT_EFF_Eigen_B_4__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_B_5__1down', 'FT_EFF_Eigen_B_5__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_B_6__1down', 'FT_EFF_Eigen_B_6__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_B_7__1down', 'FT_EFF_Eigen_B_7__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_B_8__1down', 'FT_EFF_Eigen_B_8__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_C_0__1down', 'FT_EFF_Eigen_C_0__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_C_1__1down', 'FT_EFF_Eigen_C_1__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_C_2__1down', 'FT_EFF_Eigen_C_2__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_C_3__1down', 'FT_EFF_Eigen_C_3__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_Light_0__1down', 'FT_EFF_Eigen_Light_0__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_Light_1__1down', 'FT_EFF_Eigen_Light_1__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_Light_2__1down', 'FT_EFF_Eigen_Light_2__1up')
    unfold[tag].AddSystematic('FT_EFF_Eigen_Light_3__1down', 'FT_EFF_Eigen_Light_3__1up')
    unfold[tag].AddSystematic('FT_EFF_extrapolation__1down', 'FT_EFF_extrapolation__1up')
    unfold[tag].AddSystematic('FT_EFF_extrapolation_from_charm__1down', 'FT_EFF_extrapolation_from_charm__1up')
    unfold[tag].AddSystematic('JET_EtaIntercalibration_NonClosure_2018data__1down', 'JET_EtaIntercalibration_NonClosure_2018data__1up')
    unfold[tag].AddSystematic('JET_EtaIntercalibration_NonClosure_highE__1down', 'JET_EtaIntercalibration_NonClosure_highE__1up')
    unfold[tag].AddSystematic('JET_EtaIntercalibration_NonClosure_negEta__1down', 'JET_EtaIntercalibration_NonClosure_negEta__1up')
    unfold[tag].AddSystematic('JET_EtaIntercalibration_NonClosure_posEta__1down', 'JET_EtaIntercalibration_NonClosure_posEta__1up')
    unfold[tag].AddSystematic('JET_Flavor_Response__1down', 'JET_Flavor_Response__1up')
    unfold[tag].AddSystematic('JET_GroupedNP_1__1down', 'JET_GroupedNP_1__1up')
    unfold[tag].AddSystematic('JET_GroupedNP_2__1down', 'JET_GroupedNP_2__1up')
    unfold[tag].AddSystematic('JET_GroupedNP_3__1down', 'JET_GroupedNP_3__1up')
    unfold[tag].AddSystematic('JET_JER_DataVsMC_MC16__1down', 'JET_JER_DataVsMC_MC16__1up')
    unfold[tag].AddSystematic('JET_JER_EffectiveNP_1__1down', 'JET_JER_EffectiveNP_1__1up')
    unfold[tag].AddSystematic('JET_JER_EffectiveNP_2__1down', 'JET_JER_EffectiveNP_2__1up')
    unfold[tag].AddSystematic('JET_JER_EffectiveNP_3__1down', 'JET_JER_EffectiveNP_3__1up')
    unfold[tag].AddSystematic('JET_JER_EffectiveNP_4__1down', 'JET_JER_EffectiveNP_4__1up')
    unfold[tag].AddSystematic('JET_JER_EffectiveNP_5__1down', 'JET_JER_EffectiveNP_5__1up')
    unfold[tag].AddSystematic('JET_JER_EffectiveNP_6__1down', 'JET_JER_EffectiveNP_6__1up')
    unfold[tag].AddSystematic('JET_JER_EffectiveNP_7restTerm__1down', 'JET_JER_EffectiveNP_7restTerm__1up')
    unfold[tag].AddSystematic('JET_JvtEfficiency__1down', 'JET_JvtEfficiency__1up')
    unfold[tag].AddSystematic('JET_fJvtEfficiency__1down', 'JET_fJvtEfficiency__1up')
    unfold[tag].AddSystematic('MET_SoftTrk_ResoPara__1down', 'MET_SoftTrk_ResoPara__1up')
    unfold[tag].AddSystematic('MET_SoftTrk_ResoPerp__1down', 'MET_SoftTrk_ResoPerp__1up')
    # unfold[tag].AddSystematic('MET_SoftTrk_ScaleDown__1down', 'MET_SoftTrk_ScaleUp__1up')
    unfold[tag].AddSystematic('MUON_EFF_ISO_STAT__1down', 'MUON_EFF_ISO_STAT__1up')
    unfold[tag].AddSystematic('MUON_EFF_ISO_SYS__1down', 'MUON_EFF_ISO_SYS__1up')
    unfold[tag].AddSystematic('MUON_EFF_RECO_STAT_LOWPT__1down', 'MUON_EFF_RECO_STAT_LOWPT__1up')
    unfold[tag].AddSystematic('MUON_EFF_RECO_STAT__1down', 'MUON_EFF_RECO_STAT__1up')
    unfold[tag].AddSystematic('MUON_EFF_RECO_SYS_LOWPT__1down', 'MUON_EFF_RECO_SYS_LOWPT__1up')
    unfold[tag].AddSystematic('MUON_EFF_RECO_SYS__1down', 'MUON_EFF_RECO_SYS__1up')
    unfold[tag].AddSystematic('MUON_EFF_TTVA_STAT__1down', 'MUON_EFF_TTVA_STAT__1up')
    unfold[tag].AddSystematic('MUON_EFF_TTVA_SYS__1down', 'MUON_EFF_TTVA_SYS__1up')
    unfold[tag].AddSystematic('MUON_ID__1down', 'MUON_ID__1up')
    unfold[tag].AddSystematic('MUON_MS__1down', 'MUON_MS__1up')
    unfold[tag].AddSystematic('MUON_SAGITTA_RESBIAS__1down', 'MUON_SAGITTA_RESBIAS__1up')
    unfold[tag].AddSystematic('MUON_SAGITTA_RHO__1down', 'MUON_SAGITTA_RHO__1up')
    unfold[tag].AddSystematic('MUON_SCALE__1down', 'MUON_SCALE__1up')
    unfold[tag].AddSystematic('PRW_DATASF__1down', 'PRW_DATASF__1up')

    if METHOD == "Pseudo":
        filename_pseudodatatruth = os.path.join(inputdir, "{}-Region{}-{}-pseudodatatruth.root".format(SignalName, RegionName, VarName))
        pseudodatatruthfile = ROOT.TFile(filename_pseudodatatruth)
        unfold[tag].AddPseudoDataTruth(pseudodatatruthfile)
        unfold[tag].SetPseudo(True)
    elif METHOD == "Test":
        filename_testdatatruth = os.path.join(inputdir, "{}-Region{}-{}-testdatatruth.root".format(SignalName, RegionName, VarName))
        testdatatruthfile = ROOT.TFile(filename_testdatatruth)
        unfold[tag].AddPseudoDataTruth(testdatatruthfile)
        unfold[tag].SetPseudo(True)
    unfold[tag].SetBestIter(BestIter)
    unfold[tag].SetStatisticErrorNTries(1000)
    unfold[tag].unfold()

    draw[tag] = unfoldTool.BayesUnfoldDraw(unfold[tag], drawdir)
    draw[tag].DefaultPlotAll("{}-{}-{}".format(SignalName, RegionName, VarName), "stat")
    return unfold[tag]
    

NIters = 20


# # [[test]] 
# METHOD="Pseudo"
# a = MakeUnfolding("LL", "HPT", "abs_deltaYWZ", 20, 1)
# pass


# [[1.TT-70]] 
# METHOD = "Pseudo"
# a = MakeUnfolding("TT", "70", "abs_deltaYWZ", 20, 3)
# b = MakeUnfolding("TT", "70", "abs_deltaY3Z", 20, 1)
METHOD = "Data"
c = MakeUnfolding("TT", "70", "abs_deltaYWZ", 20, 3)
d = MakeUnfolding("TT", "70", "abs_deltaY3Z", 20, 1)


# # # # [[2.WZ-HPT]] 
# METHOD = "Pseudo"
# MakeUnfolding("WZ", "HPT", "abs_deltaYWZ", 20, 1)
# MakeUnfolding("WZ", "HPT", "abs_deltaY3Z", 20, 1)
# MakeUnfolding("WZ", "HPT", "W_pt", 20, 1)
# MakeUnfolding("WZ", "HPT", "WZ_m", 20, 1)
# MakeUnfolding("WZ", "HPT", "Z_pt", 20, 1)
# MakeUnfolding("WZ", "HPT", "WZ_pt", 20, 1)

METHOD = "Data"
MakeUnfolding("WZ", "HPT", "abs_deltaYWZ", 20, 1)
MakeUnfolding("WZ", "HPT", "abs_deltaY3Z", 20, 1)
MakeUnfolding("WZ", "HPT", "W_pt", 20, 1)
MakeUnfolding("WZ", "HPT", "WZ_m", 20, 1)
MakeUnfolding("WZ", "HPT", "Z_pt", 20, 1)
MakeUnfolding("WZ", "HPT", "WZ_pt", 20, 1)

# # [[3.LL-HPT]] 
# METHOD = "Pseudo"
# MakeUnfolding("LL", "HPT", "abs_deltaYWZ", 20, 1)
# MakeUnfolding("LL", "HPT", "abs_deltaY3Z", 20, 1)
# MakeUnfolding("LL", "HPT", "W_pt", 20, 1)
# MakeUnfolding("LL", "HPT", "WZ_m", 20, 1)
# MakeUnfolding("LL", "HPT", "Z_pt", 20, 1)
# MakeUnfolding("LL", "HPT", "WZ_pt", 20, 1)

METHOD = "Data"
MakeUnfolding("LL", "HPT", "abs_deltaYWZ", 20, 1)
MakeUnfolding("LL", "HPT", "abs_deltaY3Z", 20, 1)
MakeUnfolding("LL", "HPT", "W_pt", 20, 1)
MakeUnfolding("LL", "HPT", "WZ_m", 20, 1)
MakeUnfolding("LL", "HPT", "Z_pt", 20, 1)
MakeUnfolding("LL", "HPT", "WZ_pt", 20, 1)


# [[4.LL-200]] 
# METHOD = "Pseudo"
# MakeUnfolding("LL", "200", "abs_deltaYWZ", 20, 1)
# MakeUnfolding("LL", "200", "abs_deltaY3Z", 20, 1)
# MakeUnfolding("LL", "200", "W_pt", 20, 2)
# MakeUnfolding("LL", "200", "WZ_m", 20, 1)
# MakeUnfolding("LL", "200", "Z_pt", 20, 1)
# MakeUnfolding("LL", "200", "WZ_pt", 20, 2)

# METHOD = "Data"
# MakeUnfolding("LL", "200", "abs_deltaYWZ", 20, 1)
# MakeUnfolding("LL", "200", "abs_deltaY3Z", 20, 1)
# MakeUnfolding("LL", "200", "W_pt", 20, 2)
# MakeUnfolding("LL", "200", "WZ_m", 20, 1)
# MakeUnfolding("LL", "200", "Z_pt", 20, 1)
# MakeUnfolding("LL", "200", "WZ_pt", 20, 2)



# for VarName in variables.keys():
#     for RegionName in prepared.RegionNames:
#         for SignalName in prepared.SignalNames:
#             MakeUnfolding(SignalName, RegionName, VarName, NIters, 1)
#             METHOD = "Data"
#             MakeUnfolding(SignalName, RegionName, VarName, NIters, 1)
