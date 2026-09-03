import ROOT
from .tools import THistToArray, Ratio, Diff, MultiPly, Add
import os, sys
import array

class BayesUnfoldHelper:

    NIters = 1
    fReco = []
    fInput = []
    response = []
    fidcor = []
    effcor = []
    results = []

    # 注：不同的系统误差源会改变fInput, fReco，response, fidcor, effcor

    def __init__(self, NIters, fInput, fReco, response, fidcor, effcor):
        self.NIters = NIters
        self.fInput = fInput
        self.fReco = fReco
        self.response = response
        self.fidcor = fidcor
        self.effcor = effcor
    
    def unfold(self):
        one = self.OneBayesUnfoldIter(self.fInput, self.fReco, self.response, self.fidcor, self.effcor)
        self.results = [one]
        for i in range(self.NIters - 1):
            one = self.OneBayesUnfoldIter(one, self.fReco, self.response, self.fidcor, self.effcor)
            self.results.append(one)
        return self.results

    

    def OneBayesUnfoldIter(self, fTruthInput, fReco, response, fidcor, effcor):
        # 对某个input进行一次迭代
        # response: 对每列归一
        fTR = []

        NBins = len(fTruthInput)
        for i in range(NBins): # Ti
            fTR.append([])
            for j in range(NBins): # Rj
                temp_sum = 0
                for k in range(NBins):
                    temp_sum += response[j][k] * fTruthInput[k] * effcor[k]
                if temp_sum == 0:
                    fTR[i].append(0)
                else:
                    fTR[i].append(response[j][i] * fTruthInput[i] * effcor[i] / temp_sum)

        # 计算下一个迭代结果
        result = []
        for i in range(NBins):
            element = 0
            for j in range(NBins):
                element += fTR[i][j] * fReco[j] * fidcor[j] / effcor[i] if effcor[i] != 0 else 0
            result.append(element)
        return result

class BayesUnfoldTool:
    # 用于对多个系统误差源进行unfold
    NTries = 100   # 计算统计误差时做高斯扰动的次数
    NIters = 1   # 迭代次数

    all_sys = []  # 所有的系统误差源
    data = []
    pseudodatatruth = []
    data_minus_bkg = {}
    bkg = {}
    migration_matrix = {}
    migration_matrix_norm = {}
    fidcorrnum = {}
    fidcorrden = {}
    fidcorr = {}
    effcorrnum = {}
    effcorrden = {}
    effcorr = {}
    truth = {}
    reco = {}

    unfold_results = {}
    unfold_results_norm = {}
    unfold_results_stat = []
    unfold_results_stat_norm = []

    UnfoldMethodAndAllSys = []
    UnfoldMethodAndStatSys = []

    IsPseudo = False

    BestIter = 1

    def __init__(self, datafile, bkgfile, responsefile, NIters = 1):
        """
        datafile、bkgfile、responsefile需要是ROOT文件
        nominal会自动加入
        """
        self.ClearAll()
        
        self.NIters = NIters

        self.datafile = datafile
        self.bkgfile = bkgfile
        self.responsefile = responsefile
        self.all_sys.append(["nominal", "nominal", "average"])
        hdata = datafile.Get("nominal/reconstructed")
        self.data = THistToArray(hdata)
        self.AddOneThing("nominal")

        self.bins = []
        for i in range(len(self.data)):
            self.bins.append(hdata.GetXaxis().GetBinLowEdge(i + 1))
        self.bins.append(hdata.GetXaxis().GetBinUpEdge(len(self.data)))

    def ClearAll(self):
        self.all_sys = []
        self.data = []
        self.data_minus_bkg = {}
        self.bkg = {}
        self.migration_matrix = {}
        self.migration_matrix_norm = {}
        self.fidcorrnum = {}
        self.fidcorrden = {}
        self.fidcorr = {}
        self.effcorrnum = {}
        self.effcorrden = {}
        self.effcorr = {}
        self.truth = {}

        self.unfold_results = {}
        self.unfold_results_norm = {}
        self.unfold_results_stat = []
        self.unfold_results_stat_norm = []

        self.UnfoldMethodAndAllSys = []
        self.UnfoldMethodAndStatSys = []

        self.stat_err = []
        self.stat_err_combine = []
        self.stat_err_cov = []
        self.stat_err_corr = []
        self.sys_err = []
        self.sys_err_ratio = []
        self.sys_err_total = []
        self.sys_err_total_combine = []

        self.truth = {}

    def AddOneThing(self, sysname):
        hbkg = self.bkgfile.Get("{}/reconstructed".format(sysname))
        hReco = self.responsefile.Get("{}/reconstructed".format(sysname))
        hmigration_matrix = self.responsefile.Get("{}/migration_matrix".format(sysname))
        hfidcorrnum = self.responsefile.Get("{}/fidcorrnum".format(sysname))
        hfidcorrden = self.responsefile.Get("{}/fidcorrden".format(sysname))
        heffcorrnum = self.responsefile.Get("{}/effcorrnum".format(sysname))
        heffcorrden = self.responsefile.Get("{}/effcorrden".format(sysname))

        self.bkg[sysname] = THistToArray(hbkg)
        self.data_minus_bkg[sysname] = [self.data[i] - self.bkg[sysname][i] for i in range(len(self.data))]
        self.reco[sysname] = THistToArray(hReco)
        temp_migration = THistToArray(hmigration_matrix)
        # response: 对每列归一
        for j in range(len(temp_migration)):
            temp_sum = 0
            for i in range(len(temp_migration)):
                temp_sum += temp_migration[i][j]
            if temp_sum == 0:
                continue
            for i in range(len(temp_migration)):
                temp_migration[i][j] /= temp_sum
        self.migration_matrix[sysname] = THistToArray(hmigration_matrix)
        self.migration_matrix_norm[sysname] = temp_migration
        self.fidcorrnum[sysname] = THistToArray(hfidcorrnum)
        self.fidcorrden[sysname] = THistToArray(hfidcorrden)
        self.fidcorr[sysname] = []
        for i in range(len(self.fidcorrnum[sysname])):
            if self.fidcorrden[sysname][i] == 0:
                self.fidcorr[sysname].append(0)
            else:
                self.fidcorr[sysname].append(self.fidcorrnum[sysname][i]/self.fidcorrden[sysname][i])
        self.effcorrnum[sysname] = THistToArray(heffcorrnum)
        self.effcorrden[sysname] = THistToArray(heffcorrden)
        self.effcorr[sysname] = []
        for i in range(len(self.effcorrnum[sysname])):
            if self.effcorrden[sysname][i] == 0:
                self.effcorr[sysname].append(0)
            else:
                self.effcorr[sysname].append(self.effcorrnum[sysname][i]/self.effcorrden[sysname][i])
        self.truth[sysname] = self.effcorrden[sysname]

    def normalize(self, hist):
        result = []
        for ihist in hist:
            temp_sum = sum(ihist)
            result.append([i / temp_sum for i in ihist])
        return result
    
    def AddSystematic(self, downname, upname, strategy="average"):
        '''
        upname, downname: 上下误差源的名字
        strategy: 误差源的处理策略("average":取平均值, "max":取最大值)
        nominal会自动加入
        '''
        self.all_sys.append([downname, upname, strategy])
        self.AddOneThing(downname)
        self.AddOneThing(upname)


    def SetStatisticErrorNTries(self, NTries=100):
        self.NTries = NTries
    
    def AddPseudoDataTruth(self, pseudodatatruthfile):
        self.pseudodatatruthfile = pseudodatatruthfile

    def SetPseudo(self, IsPseudo):
        self.IsPseudo = IsPseudo

    def unfold(self):
        # [[1.unfold-nominal]] 
        tool = BayesUnfoldHelper(self.NIters, 
                                 self.truth["nominal"],
                                 self.data_minus_bkg["nominal"],
                                 self.migration_matrix_norm["nominal"],
                                 self.fidcorr["nominal"],
                                 self.effcorr["nominal"])
        result = tool.unfold()
        self.unfold_results["nominal"] = result
        self.unfold_results_norm["nominal"] = self.normalize(result)
        # [[2.unfold-systematic]] 
        for sys in self.all_sys:
            tool = BayesUnfoldHelper(self.NIters, 
                                     self.truth[sys[0]],
                                     self.data_minus_bkg[sys[0]],
                                     self.migration_matrix_norm[sys[0]],
                                     self.fidcorr[sys[0]],
                                     self.effcorr[sys[0]])
            result = tool.unfold()
            self.unfold_results[sys[0]] = result
            self.unfold_results_norm[sys[0]] = self.normalize(result)
            tool = BayesUnfoldHelper(self.NIters, 
                                     self.truth[sys[1]],
                                     self.data_minus_bkg[sys[1]],
                                     self.migration_matrix_norm[sys[1]],
                                     self.fidcorr[sys[1]],
                                     self.effcorr[sys[1]])
            result = tool.unfold()
            self.unfold_results[sys[1]] = result
            self.unfold_results_norm[sys[1]] = self.normalize(result)
        # [[3.unfold-for-statistic]] 
        truth = self.truth["nominal"]
        migration_matrix_norm = self.migration_matrix_norm["nominal"]
        fidcorr = self.fidcorr["nominal"]
        effcorr = self.effcorr["nominal"]
        for i in range(self.NTries):
            data_fluctuated = []
            data_fluctuated_minus_bkg = []
            for i in range(len(self.data)):
                fluc_data = self.data[i] + ROOT.gRandom.Gaus(0, (self.data[i] ** 0.5))
                temp_bkg = self.bkg["nominal"][i]
                if fluc_data < temp_bkg:
                    fluc_data = temp_bkg
                data_fluctuated.append(fluc_data)
                data_fluctuated_minus_bkg.append(fluc_data - temp_bkg)
            tool = BayesUnfoldHelper(self.NIters, 
                                     truth,
                                     data_fluctuated_minus_bkg,
                                     migration_matrix_norm, 
                                     fidcorr,
                                     effcorr)
            
            result = tool.unfold()
            self.unfold_results_stat.append(result)
            self.unfold_results_stat_norm.append(self.normalize(result))

        # [[4.计算统计误差]] 
        # unfold_results_stat: [NTries][NIters][NBins]   a,b,c
        self.stat_err_combine = []       # [NIters] a
        self.stat_err = []       # [NIters][NBins] a, c
        self.stat_err_cov = []   # [NIters][NBins][NBins]  b, i, j
        self.stat_err_corr = []  # [NIters][NBins][NBins]  b, i, j
        for b in range(self.NIters):
            # 每一个iter都要分别计算一次
            # 1.准备：求偏差矩阵
            # 把data对应的结果当做均值，求deviation
            deviations = []  # [NTries][NBins]
            means_data = self.unfold_results["nominal"][b]
            for a in range(self.NTries):
                result_certain = self.unfold_results_stat[a][b]
                deviations.append(
                    [result_certain[c] - means_data[c] for c in range(len(means_data))]
                    )

            # 2.计算协方差矩阵
            # deviations*deviations转置
            cov_matrix = []  # 本次iter的计算结果，是一个N*N的矩阵
            for i in range(len(self.data)):
                cov_matrix.append([])
                for j in range(len(self.data)):
                    temp = [deviations[k][i] * deviations[k][j] for k in range(len(deviations))]
                    cov_matrix[i].append(
                        sum(temp)
                        )
            for i in range(len(self.data)):
                for j in range(len(self.data)):
                    cov_matrix[i][j] /= self.NTries
            self.stat_err_cov.append(cov_matrix)
            # 2.5.计算标准误差
            self.stat_err.append([cov_matrix[i][i] ** 0.5 for i in range(len(self.data))])
            # 3.计算相关系数矩阵
            # corr_matrix = cov_matrix / (sigma_i * sigma_j)
            corr_matrix = []
            for i in range(len(self.data)):
                corr_matrix.append([])
                for j in range(len(self.data)):
                    nom = cov_matrix[i][j]
                    den = (cov_matrix[i][i] * cov_matrix[j][j]) ** 0.5
                    if den == 0:
                        corr_matrix[i].append(0)
                    else:
                        corr_matrix[i].append(
                            cov_matrix[i][j] / (cov_matrix[i][i] * cov_matrix[j][j]) ** 0.5
                            )
            self.stat_err_corr.append(corr_matrix)
            # 4.计算总系统误差
            temp = 0
            for i in range(len(self.data)):
                temp += cov_matrix[i][i]
            self.stat_err_combine.append(temp ** 0.5)



        # [[5.计算系统误差]] 
        self.sys_err = []   # [NIters][sysname][NBins] a, b, c
        for a in range(self.NIters):
            self.sys_err.append({})
            for sys in self.all_sys:
                # 提取sys[0]和sys[1]两个字符串共同的部分，作为名字
                name = ""
                for i in range(min(len(sys[0]), len(sys[1]))):
                    if sys[0][i] == sys[1][i]:
                        name += sys[0][i]
                    else:
                        break
                self.sys_err[a][name] = []
                for i in range(len(self.data)):
                    deviation_down = self.unfold_results[sys[0]][a][i] - self.unfold_results["nominal"][a][i]
                    deviation_up = self.unfold_results[sys[1]][a][i] - self.unfold_results["nominal"][a][i]
                    self.sys_err[a][name].append(self.calc_sys_err(deviation_down, deviation_up, sys[2]))
        self.sys_err_total = []  # [NIters][NBins] a, c
        self.sys_err_total_combine = []  # [NIters] a
        for a in range(self.NIters):
            self.sys_err_total.append([])
            for c in range(len(self.data)):
                temp = 0
                for b_key in self.sys_err[a].keys():
                    temp += self.sys_err[a][b_key][c] ** 2
                self.sys_err_total[a].append(temp ** 0.5)
            temp = 0
            for c in range(len(self.data)):
                temp += self.sys_err_total[a][c] ** 2
            self.sys_err_total_combine.append(temp ** 0.5)


        # [[6.计算总误差]] 
        self.all_err = []  # [NIters][NBins] a, c
        self.all_err_combine = []  # [NIters] a
        for a in range(self.NIters):
            self.all_err.append([])
            for c in range(len(self.data)):
                temp = 0
                temp += self.stat_err_cov[a][c][c]
                temp += self.sys_err_total[a][c] ** 2
                self.all_err[a].append(temp ** 0.5)

            self.all_err_combine.append(
                (self.stat_err_combine[a] ** 2 + self.sys_err_total_combine[a] ** 2) ** 0.5
            )

        # [[7.计算不同误差源对总误差的影响]] 
        self.sys_err_ratio = [] # [NIters][sysname]   a, b
        self.sys_err_ratio_result = {}  # (sorted) sysname: result
        for a in range(self.NIters):
            self.sys_err_ratio.append({})
            sum_all = 0
            for c in range(len(self.data)):
                sum_all += self.sys_err_total[a][c] ** 2
            sum_all = sum_all ** 0.5
            for sysname in self.sys_err[0].keys():
                temp = [self.sys_err[a][sysname][i] ** 2 for i in range(len(self.data))]
                self.sys_err_ratio[a][sysname] = sum(temp) ** 0.5 / sum_all
            
            if a == self.BestIter:
                temp = self.sys_err_ratio[a]
                # sort
                temp = sorted(temp.items(), key=lambda item: item[1], reverse=True)
                self.sys_err_ratio_result = temp

        # [[8.计算方法误差]] 
        if self.IsPseudo:
            self.pseudodatatruth = THistToArray(
                self.pseudodatatruthfile.Get("nominal/reconstructed")
                )
            self.UnfoldMethodSys = [] # [NIters] a
            for a in range(self.NIters):
                temp1 = 0
                temp2 = 0
                temp3 = 0
                ref = self.pseudodatatruth
                for c in range(len(self.data)):
                    temp1 += abs(self.unfold_results["nominal"][a][c] - ref[c]) ** 2
                    temp2 += self.all_err[a][c] ** 2
                    temp3 += self.stat_err_cov[a][c][c]
                self.UnfoldMethodSys.append(temp1 ** 0.5)
                self.UnfoldMethodAndAllSys.append((temp1 + temp2)** 0.5)
                self.UnfoldMethodAndStatSys.append((temp1 + temp3)** 0.5)


    def calc_sys_err(self, down_deviation, up_deviation, strategy="average"):
        if strategy == "average": # default
            return (abs(down_deviation) + abs(up_deviation)) / 2
        elif strategy == "max":
            return max(abs(down_deviation), abs(up_deviation))
        else:
            raise Exception("calc_sys_err: Unknown strategy")

    def SetBestIter(self, BestIter):
        self.BestIter = BestIter



class BayesUnfoldDraw:
    def __init__(self, unfoldTool, outputdir,
                 ATLASLabel="ATLAS Internal",
                 cmsEnergy="13", lumi="140.1"):
        self.unfoldTool = unfoldTool
        self.outputdir = outputdir
        self.ATLASLabel = ATLASLabel
        self.cmsEnergy = cmsEnergy
        self.lumi = lumi
        ROOT.gROOT.SetBatch(True)
        # self.SetAtlasStyle()

    def DefaultPlotAll(self, prefix_tag, mode="stat"):
        if not self.unfoldTool.IsPseudo:
            self.PlotUnfoldedResult(prefix_tag)
            self.PlotSystematicsSourceContribution(prefix_tag)
        if self.unfoldTool.IsPseudo:
            self.PlotPseudoDataIteration(prefix_tag, mode)
            self.PlotUnfoldedResult(prefix_tag)

    def PlotUnfoldedResult(self, prefix_tag):
        # prefix_tag: "SignalName-RegionName-VarName"
        self.SetMyStyle()
        # 取消grid
        ROOT.gStyle.SetPadGridX(False)
        ROOT.gStyle.SetPadGridY(False)
        outputfilename = "{}-UnfoldedResult.pdf".format(prefix_tag)
        c = ROOT.TCanvas("c", "c", 800, 600)
        bins = self.unfoldTool.bins

        # MainPad
        h_truth = ROOT.TH1F("h_truth", "h_truth", len(bins) - 1, array.array('d', bins))
        h_result = ROOT.TH1F("h_result", "h_result", len(bins) - 1, array.array('d', bins))
        h_stat_err = ROOT.TH1F("h_stat_err", "h_stat_err", len(bins) - 1, array.array('d', bins))
        h_total_err = ROOT.TH1F("h_total_err", "h_total_err", len(bins) - 1, array.array('d', bins))
        # SubPad
        h_ratio = ROOT.TH1F("h_ratio", "h_ratio", len(bins) - 1, array.array('d', bins))
        h_truth_ratio = ROOT.TH1F("h_truth_ratio", "h_truth_ratio", len(bins) - 1, array.array('d', bins))
        h_stat_err_ratio = ROOT.TH1F("h_stat_err_ratio", "h_stat_err_ratio", len(bins) - 1, array.array('d', bins))
        h_total_err_ratio = ROOT.TH1F("h_total_err_ratio", "h_total_err_ratio", len(bins) - 1, array.array('d', bins))

        if not self.unfoldTool.IsPseudo:
            truth_sum = sum(self.unfoldTool.effcorrden["nominal"])
            truth = [i / truth_sum for i in self.unfoldTool.effcorrden["nominal"]]
        else:
            truth_sum = sum(self.unfoldTool.pseudodatatruth)
            truth = [i / truth_sum for i in self.unfoldTool.pseudodatatruth]

        unfold_sum = sum(self.unfoldTool.unfold_results["nominal"][self.unfoldTool.BestIter - 1])
        
        for i in range(len(bins) - 1):
            truth_num = truth[i]
            unfold_result = self.unfoldTool.unfold_results_norm["nominal"][self.unfoldTool.BestIter - 1][i]
            stat_err = self.unfoldTool.stat_err[self.unfoldTool.BestIter][i] / unfold_sum
            total_err = self.unfoldTool.all_err[self.unfoldTool.BestIter][i] / unfold_sum

            bin_width = bins[i + 1] - bins[i]
            # bin_width = 1

            truth_num /= bin_width
            unfold_result /= bin_width
            stat_err /= bin_width
            total_err /= bin_width

            h_truth.SetBinContent(i + 1, truth_num)
            h_result.SetBinContent(i + 1, unfold_result)
            h_stat_err.SetBinContent(i + 1, unfold_result)
            h_total_err.SetBinContent(i + 1, unfold_result)
            
            h_truth.SetBinError(i + 1, 1e-5)
            h_result.SetBinError(i + 1, 0)
            h_stat_err.SetBinError(i + 1, stat_err)
            h_total_err.SetBinError(i + 1, total_err)

            h_ratio.SetBinContent(i + 1, 1)
            h_stat_err_ratio.SetBinContent(i + 1, 1)
            h_total_err_ratio.SetBinContent(i + 1, 1)

            h_ratio.SetBinError(i + 1, 0)


            if unfold_result == 0:
                h_stat_err_ratio.SetBinError(i + 1, 0)
                h_total_err_ratio.SetBinError(i + 1, 0)
            else:
                h_stat_err_ratio.SetBinError(i + 1, stat_err * truth_num / unfold_result ** 2)
                h_total_err_ratio.SetBinError(i + 1, total_err * truth_num / unfold_result ** 2)

        h_truth_ratio = Ratio(h_truth, h_result)
        for i in range(len(bins) - 1):
            h_truth_ratio.SetBinError(i + 1, 1e-5)

        # 画图样式设置
        h_truth.SetMarkerStyle(22)
        h_truth_ratio.SetMarkerStyle(22)
        h_result.SetMarkerStyle(20)
        h_ratio.SetMarkerStyle(20)


        total_err_color = ROOT.TColor.GetColor("#66ccff")
        stat_err_color = ROOT.TColor.GetColor("#0066cc")
        truth_color = ROOT.TColor.GetColor("#ca0000")

        h_truth.SetMarkerColor(truth_color)
        h_truth_ratio.SetMarkerColor(truth_color)
        h_result.SetMarkerColor(1)
        h_ratio.SetMarkerColor(1)


        markersize =  1

        h_truth.SetMarkerSize(markersize)
        h_result.SetMarkerSize(markersize)
        h_truth_ratio.SetMarkerSize(markersize)
        h_ratio.SetMarkerSize(markersize)

        h_truth.SetLineColor(truth_color)
        h_truth_ratio.SetLineColor(truth_color)
        h_truth.SetLineWidth(1)
        h_truth_ratio.SetLineWidth(1)


        h_stat_err.SetFillColor(stat_err_color)
        h_stat_err_ratio.SetFillColor(stat_err_color)
        h_total_err.SetFillColor(total_err_color)
        h_total_err_ratio.SetFillColor(total_err_color)
        h_stat_err.SetFillStyle(1001)
        h_stat_err_ratio.SetFillStyle(1001)
        h_total_err.SetFillStyle(1001)
        h_total_err_ratio.SetFillStyle(1001)



        # 设置坐标轴
        h_total_err.GetYaxis().SetTitle("Results")
        h_total_err.GetXaxis().SetTitle("")
        h_total_err_ratio.GetYaxis().SetTitle("Pred./Data")
        h_total_err_ratio.GetXaxis().SetTitle(prefix_tag)

        main_min_y = min([h_result.GetMinimum(), h_truth.GetMinimum()])
        main_max_y = max([h_result.GetMaximum(), h_truth.GetMaximum()])

        h_total_err.GetYaxis().SetRangeUser(0, main_max_y * 2)
        h_total_err_ratio.GetYaxis().SetRangeUser(0.5, 1.5)


        # 画图
        MainPad = ROOT.TPad("MainPad", "MainPad", 0, 0.3, 1, 1)
        SubPad = ROOT.TPad("SubPad", "SubPad", 0, 0, 1, 0.3)
        MainPad.SetBottomMargin(0.05)
        MainPad.SetTopMargin(0.1)
        SubPad.SetBottomMargin(0.4)
        SubPad.SetTopMargin(0.05)

        MainPad.SetLeftMargin(0.08)
        SubPad.SetLeftMargin(0.08)
        MainPad.SetRightMargin(0.08)
        SubPad.SetRightMargin(0.08)

        MainPad.Draw()
        SubPad.Draw()


        self.SetTwoPadStyle(MainPad, SubPad, h_total_err, h_total_err_ratio)


        MainPad.cd()
        h_total_err.SetStats(0)
        h_total_err.Draw("e2")
        h_stat_err.Draw("same e2")
        h_result.Draw("same pe")
        h_truth.Draw("same pe")

        l = ROOT.TLegend(0.6, 0.7, 0.9, 0.88)
        l.AddEntry(h_result, "Unfolded Data", "p")
        l.AddEntry(h_stat_err, "Statistical Uncertainty", "f")
        l.AddEntry(h_total_err, "Total Uncertainty", "f")
        l.AddEntry(h_truth, "Truth", "p")
        l.SetFillStyle(0)
        l.SetMargin(0.2)
        h_result.SetStats(0)
        l.Draw()

        SubPad.cd()
        h_total_err_ratio.SetStats(0)
        h_total_err_ratio.Draw("e2")
        h_stat_err_ratio.Draw("same e2")
        h_ratio.Draw("same pe")
        h_truth_ratio.Draw("same pe")



        c.cd()

        title = prefix_tag
        if self.unfoldTool.IsPseudo:
            title += "-PseudoData-Iter{}".format(self.unfoldTool.BestIter)
        else:
            title += "-Iter{}".format(self.unfoldTool.BestIter)
        self.DrawATLASLabel(title=title)

        if self.unfoldTool.IsPseudo:
            c.SaveAs(os.path.join(self.outputdir, outputfilename.replace(".pdf", "-Pseudo.pdf")))
        else:
            c.SaveAs(os.path.join(self.outputdir, outputfilename))


    def PlotPseudoDataIteration(self, prefix_tag, mode="stat"):
        # prefix_tag: "SignalName-RegionName-VarName"
        # mode: stat/all 表示计算误差的时候只考虑统计误差还是要考虑总误差
        self.SetMyStyle()
        outputfilename = "{}-IterComparison.pdf".format(prefix_tag)
        outputfilename = os.path.join(self.outputdir, outputfilename)
        c = ROOT.TCanvas("c", "c", 800, 600)
        h_shift = ROOT.TH1F("h_shift", "h_shift", self.unfoldTool.NIters, 0, self.unfoldTool.NIters)
        h_unc = ROOT.TH1F("h_unc", "h_unc", self.unfoldTool.NIters, 0, self.unfoldTool.NIters)
        h_total = ROOT.TH1F("h_total", "h_total", self.unfoldTool.NIters, 0, self.unfoldTool.NIters)

        h_shift.SetMarkerStyle(26)
        h_unc.SetMarkerStyle(24)
        h_total.SetMarkerStyle(21)
        h_shift.SetMarkerColor(9)
        h_unc.SetMarkerColor(9)
        h_total.SetMarkerColor(9)
        size = 1.8
        h_shift.SetMarkerSize(size)
        h_unc.SetMarkerSize(size)
        h_total.SetMarkerSize(size)


        ymin = 99999
        ymax = 0

        shifts = []
        uncs = []
        totals = []

        scale = 1e3

        for i in range(self.unfoldTool.NIters):
            temp_sum = sum(self.unfoldTool.unfold_results["nominal"][i])
            temp_sum = temp_sum / scale
            shift = self.unfoldTool.UnfoldMethodSys[i] / temp_sum
            if mode == "all":
                unc = self.unfoldTool.all_err_combine[i] / temp_sum
            elif mode == "stat":
                unc = self.unfoldTool.stat_err_combine[i] / temp_sum
            else:
                raise("PlotPseudoDataIteration: Unknown mode: " + mode)
            total = (shift ** 2 + unc ** 2) ** 0.5

            h_shift.SetBinContent(i + 1, shift)
            h_unc.SetBinContent(i + 1, unc)
            h_total.SetBinContent(i + 1, total)

            h_shift.GetXaxis().SetBinLabel(i + 1, "Bayes{}".format(i + 1))
            h_unc.GetXaxis().SetBinLabel(i + 1, "Bayes{}".format(i + 1))
            h_total.GetXaxis().SetBinLabel(i + 1, "Bayes{}".format(i + 1))

            # 设置y的误差为0
            h_shift.SetBinError(i + 1, 1e-6)
            h_unc.SetBinError(i + 1, 1e-6)
            h_total.SetBinError(i + 1, 1e-6)
            # # 设置x的误差为0.5
            # h_shift.GetXaxis().SetBinError(i + 1, 0.5)
            # h_unc.GetXaxis().SetBinError(i + 1, 0.5)
            # h_total.GetXaxis().SetBinError(i + 1, 0.5)

            if shift < ymin:
                ymin = shift
            if unc < ymin:
                ymin = unc
            if total > ymax:
                ymax = total

            shifts.append(shift)
            uncs.append(unc)
            totals.append(total)
        
        h_shift.GetXaxis().SetTitle("Iterations")
        h_shift.GetYaxis().SetTitle("Uncertainty")

        l = ROOT.TLegend(0.6, 0.73, 0.9, 0.92)
        l.AddEntry(h_shift, "#sqrt{#Sigma_{bins}(Unfolded-Truth)^{2}}  ", "p")
        if mode == "stat":
            l.AddEntry(h_unc, "#sqrt{#Sigma_{bins}(Statistical Uncertainty)^{2}}  ", "p")
            l.AddEntry(h_total, "#sqrt{#Sigma_{bins}(Stat.Unc.)^{2}+#Sigma_{bins}(Shift)^{2}}  ", "p")
        elif mode == "all":
            l.AddEntry(h_unc, "#sqrt{#Sigma_{bins}(Combined Uncertainty)^{2}}  ", "p")
            l.AddEntry(h_total, "#sqrt{#Sigma_{bins}(Comb.Unc.)^{2}+#Sigma_{bins}(Shift)^{2}}  ", "p")
        else:
            raise("PlotPseudoDataIteration: Unknown mode: " + mode)
        l.SetFillStyle(0)
        l.SetMargin(0.2)
        h_shift.SetStats(0)


        delta = ymax - ymin
        h_shift.SetMinimum(0)
        h_shift.SetMaximum(1.4 * ymax)

        # 先画一个框架
        h_shift.Draw("pe")
        # 在此基础上画顶部的线
        line1 = []
        line2 = []
        line3 = []
        for i in range(self.unfoldTool.NIters):
            x1 = h_shift.GetBinLowEdge(i+1)
            x2 = h_shift.GetBinLowEdge(i+2)
            y_1 = h_shift.GetBinContent(i+1)
            y_2 = h_unc.GetBinContent(i+1)
            y_3 = h_total.GetBinContent(i+1)
            # 画顶线
            color = ROOT.kBlack
            line_width = 1
            line1.append(ROOT.TLine(x1, y_1, x2, y_1))
            line2.append(ROOT.TLine(x1, y_2, x2, y_2))
            line3.append(ROOT.TLine(x1, y_3, x2, y_3))
            line1[i].SetLineColor(color)
            line2[i].SetLineColor(color)
            line3[i].SetLineColor(color)
            line1[i].SetLineWidth(line_width)
            line2[i].SetLineWidth(line_width)
            line3[i].SetLineWidth(line_width)
            line1[i].Draw("same")
            line2[i].Draw("same")
            line3[i].Draw("same")

        h_shift.SetTitle(prefix_tag)
        h_shift.Draw("pe same")
        h_unc.Draw("pe same")
        h_total.Draw("pe same")
        l.Draw()
        self.DrawATLASLabel(title=prefix_tag)

        if scale == 1:
            c.SaveAs(outputfilename)
        elif scale == 1e3:
            txt = ROOT.TLatex()
            txt.SetNDC()
            txt.SetTextFont(42)
            # txt.SetTextFont(22)
            txt.SetTextSize(0.045)
            txt.DrawLatex(0.1, 0.945, "x10^{-3}")
            c.SaveAs(outputfilename)
        else:
            raise("PlotPseudoDataIteration: Unknown scale")

        

    def PlotSystematicsSourceContribution(self, prefix_tag, PlotNum=15):
        self.SetMyStyle()
        outputfilename = "{}-SysSource.pdf".format(prefix_tag)
        outputfilename = os.path.join(self.outputdir, outputfilename)
        c = ROOT.TCanvas("c", "c", 800, 600)

        h_sys = ROOT.TH1F("h_sys", "h_sys", PlotNum + 1, 0, PlotNum + 1)
        h_sys.SetStats(0)
        for item in self.unfoldTool.sys_err_ratio_result[:PlotNum]:
            index = self.unfoldTool.sys_err_ratio_result.index(item)
            h_sys.GetXaxis().SetBinLabel(PlotNum + 1 - index, item[0])
            h_sys.SetBinContent(PlotNum + 1 - index, item[1] * 100)

        
        others = 0
        for item in self.unfoldTool.sys_err_ratio_result[PlotNum:]:
            others += item[1] ** 2
        others = others ** 0.5
        h_sys.GetXaxis().SetBinLabel(1, "Others Combined")
        h_sys.SetBinContent(1, others * 100)

        h_sys.GetXaxis().SetTitle("")
        h_sys.GetXaxis().SetTitleOffset(1.2)
        h_sys.GetYaxis().SetTitle("Contributions of each sys. sources (in %)")
        h_sys.GetYaxis().SetRangeUser(0, 100)
        # set precision
        ROOT.gStyle.SetPaintTextFormat(".2f")

        h_sys.SetFillColor(ROOT.TColor.GetColor("#6a9944"))
        h_sys.SetFillColor(ROOT.TColor.GetColor("#007ad8"))
        h_sys.SetBarWidth(0.5)
        h_sys.SetBarOffset(0.25)

        h_sys.Draw("hbar")

        boxes = []
        txts = []
        for i in range(1, h_sys.GetNbinsX() + 1):
            xlow = 0
            xhigh = h_sys.GetBinContent(i)
            ylow = h_sys.GetBinLowEdge(i) + 0.25
            yhigh = ylow + 0.5
            box = ROOT.TBox(xlow, ylow, xhigh, yhigh)
            box.SetLineWidth(2)
            box.SetLineColor(ROOT.TColor.GetColor("#000000"))
            box.SetFillStyle(0)  # 只绘制边框
            box.Draw()
            boxes.append(box)

            txt = ROOT.TLatex()
            txt.SetTextFont(62)
            txt.SetTextSize(0.03)
            txt.SetTextAlign(12)
            txt.DrawLatex(xhigh + 3, ylow + 0.25, "{:.2f}%".format(xhigh))
            txts.append(txt)


        # c.Update()

        ROOT.gPad.SetLeftMargin(0.5)
        # self.DrawATLASLabel(title=prefix_tag, position="top-right")
        txt = ROOT.TLatex()
        txt.SetNDC()
        txt.SetTextFont(42)
        txt.SetTextAlign(31)
        txt.SetTextSize(0.035)
        txt.DrawLatex(0.925, 0.945, prefix_tag)
        c.SaveAs(outputfilename)


    def SetAtlasStyle(self):
        atlasStyle = ROOT.TStyle("ATLAS","Atlas style")

        # use plain black on white colors
        icol=0
        atlasStyle.SetFrameBorderMode(icol)
        atlasStyle.SetFrameFillColor(icol)
        atlasStyle.SetCanvasBorderMode(icol)
        atlasStyle.SetCanvasColor(icol)
        atlasStyle.SetPadBorderMode(icol)
        atlasStyle.SetPadColor(icol)
        atlasStyle.SetStatColor(icol)
        # set the paper & margin sizes
        atlasStyle.SetPaperSize(20,26)
        atlasStyle.SetPadTopMargin(0.05)
        atlasStyle.SetPadRightMargin(0.05)
        atlasStyle.SetPadBottomMargin(0.16)
        atlasStyle.SetPadLeftMargin(0.16)

        # set title offsets (for axis label)
        atlasStyle.SetTitleXOffset(1.4)
        atlasStyle.SetTitleYOffset(1.4)

        # use large fonts
        font=72 # Helvetica italics
        # font=42 # Helvetica
        tsize=0.05
        atlasStyle.SetTextFont(font)

        atlasStyle.SetTextSize(tsize)
        atlasStyle.SetLabelFont(font,"x")
        atlasStyle.SetTitleFont(font,"x")
        atlasStyle.SetLabelFont(font,"y")
        atlasStyle.SetTitleFont(font,"y")
        atlasStyle.SetLabelFont(font,"z")
        atlasStyle.SetTitleFont(font,"z")

        atlasStyle.SetLabelSize(tsize,"x")
        atlasStyle.SetTitleSize(tsize,"x")
        atlasStyle.SetLabelSize(tsize,"y")
        atlasStyle.SetTitleSize(tsize,"y")
        atlasStyle.SetLabelSize(tsize,"z")
        atlasStyle.SetTitleSize(tsize,"z")

        # use bold lines and markers
        atlasStyle.SetMarkerStyle(20)
        atlasStyle.SetMarkerSize(1.2)
        atlasStyle.SetHistLineWidth(2)
        atlasStyle.SetLineStyleString(2,"[12 12]") # postscript dashes

        # get rid of X error bars and y error bar caps (as recommended in ATLAS figure guidelines)
        # atlasStyle.SetErrorX(0.001)
        # get rid of error bar caps
        atlasStyle.SetEndErrorSize(0.)

        # do not display any of the standard histogram decorations
        atlasStyle.SetOptTitle(0)
        # atlasStyle.SetOptStat(1111)
        atlasStyle.SetOptStat(0)
        # atlasStyle.SetOptFit(1111)
        atlasStyle.SetOptFit(0)

        # put tick marks on top and RHS of plots
        atlasStyle.SetPadTickX(1)
        atlasStyle.SetPadTickY(1)


        ROOT.gROOT.SetStyle("ATLAS")
        ROOT.gROOT.ForceStyle()

    def SetMyStyle(self):
        ROOT.gStyle.SetPadTopMargin(0.06)
        ROOT.gStyle.SetPadRightMargin(0.07)
        ROOT.gStyle.SetPadBottomMargin(0.11)
        ROOT.gStyle.SetPadLeftMargin(0.1)

        ROOT.gStyle.SetPadGridX(True)
        ROOT.gStyle.SetPadGridY(True)
        ROOT.gStyle.SetGridColor(16)
        ROOT.gStyle.SetGridStyle(3)
        ROOT.gStyle.SetGridWidth(1)

        # # 整体标题字体大小
        # ROOT.gStyle.SetTitleSize(0.06, "T")
        # ROOT.gStyle.SetTitleFont(22, "T")
        # # 标题位置
        # ROOT.gStyle.SetTitleX(0.5)
        # ROOT.gStyle.SetTitleY(0.98)
        
        # 不显示标题
        ROOT.gStyle.SetOptTitle(0)

        # 坐标轴标题大字体和粗斜体
        ROOT.gStyle.SetTitleSize(0.05, "XYZ")
        ROOT.gStyle.SetTitleFont(22, "XYZ")
        ROOT.gStyle.SetTitleOffset(0.8, "XYZ")

        ROOT.gStyle.SetLabelSize(0.04, "XYZ")
        ROOT.gStyle.SetLabelFont(22, "XYZ")

        ROOT.gStyle.SetLegendBorderSize(0)
        # # legend去掉背景色
        # ROOT.gStyle.SetLegendFillColor(0)

        ROOT.gStyle.SetLegendFont(42)

    def SetTwoPadStyle(self, MainPad, SubPad, h_main, h_sub):
        MainPad.SetBottomMargin(0.03)
        MainPad.SetLeftMargin(0.1)
        MainPad.SetRightMargin(0.07)
        SubPad.SetTopMargin(0)
        SubPad.SetBottomMargin(0.3)
        SubPad.SetLeftMargin(0.1)
        SubPad.SetRightMargin(0.07)

        # x轴设置
        h_main.GetXaxis().SetLabelSize(0)
        h_main.GetXaxis().SetTitleSize(0)
        h_sub.GetXaxis().SetLabelSize(0.12)
        h_sub.GetXaxis().SetTitleSize(0.12)
        h_sub.GetXaxis().SetTitleOffset(1)

        # y轴设置
        h_main.GetYaxis().SetTitleSize(0.06)
        h_main.GetYaxis().SetLabelSize(0.05)
        h_main.GetYaxis().SetTitleOffset(0.6)
        h_sub.GetYaxis().SetTitleSize(0.13)
        h_sub.GetYaxis().SetLabelSize(0.1)
        h_sub.GetYaxis().SetTitleOffset(0.3)

        h_sub.GetYaxis().SetNdivisions(505)



    def DrawATLASLabel(self, position="top-left", title=""):
        txt = ROOT.TLatex()
        txt.SetNDC()
        txt.SetTextFont(72)
        txt.SetTextSize(0.06)
        txt1 = "Lumi=" + str(self.lumi) + " fb^{-1}, "
        txt2 = "#sqrt{s}=" + str((self.cmsEnergy)) + "TeV"
        txt3 = txt1 + txt2
        if position == "top-left":
            txt.DrawLatex(0.14, 0.87, self.ATLASLabel)

            txt.SetTextSize(0.04)
            txt.SetTextFont(22)
            txt.DrawLatex(0.14, 0.81, txt3)

            # 获取标题内容
            if len(title):
                txt.SetTextSize(0.04)
                txt.SetTextFont(62)
                title = "Title: " + title
                txt.DrawLatex(0.14, 0.73, title)
        elif position == "top-right":
            txt.SetTextAlign(31)
            txt.DrawLatex(0.92, 0.87, self.ATLASLabel)
            
            txt.SetTextSize(0.04)
            txt.SetTextFont(22)
            txt.DrawLatex(0.92, 0.81, txt3)

            if len(title):
                txt.SetTextSize(0.04)
                txt.SetTextFont(62)
                title = "Title: " + title
                txt.DrawLatex(0.92, 0.73, title)




        elif position == "top-right":
            txt.DrawLatex(0.7, 0.85, self.ATLASLabel)
            # todo 

        



