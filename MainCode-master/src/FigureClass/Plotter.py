import ROOT
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import AutoMinorLocator, LogLocator, NullFormatter, LogFormatter

class Plotter:
    def __init__(self):
        self.inputs = []              # 
        self.panels = {}              # panel_id -> list of plot objects
        self.n_panels = 0
        self.panel_height_ratios = None

        self.global_xrange = None
        self.panel_yranges = {}

        self.sharex_panels = False
        self.hide_upper_xlabels = False
        self.panel_show_legend = {}

        self.default_panel_ylabels = {}

        self.panel_texts = {}

    # =========================================================
    # Input
    # =========================================================
    def Input(self, filename=None, objname=None, obj=None, x=None, y=None,
              label=None, linestyle="-", color=None, marker=None,
              draw_mode=None, tf1_npoints=400):
        """
          1) filename + objname
          2) obj = TH1 / TGraph / TGraphErrors / TF1 pointer
          3) x + y arrays/lists
        """

        # case 1:
        if filename is not None and objname is not None:
            root_obj = self._get_root_object(filename, objname)
            plot_obj = self._convert_root_object_to_plot(
                root_obj,
                label=label if label is not None else objname,
                linestyle=linestyle,
                color=color,
                marker=marker,
                draw_mode=draw_mode,
                tf1_npoints=tf1_npoints
            )

        # case 2:
        elif obj is not None:
            plot_obj = self._convert_root_object_to_plot(
                obj,
                label=label,
                linestyle=linestyle,
                color=color,
                marker=marker,
                draw_mode=draw_mode,
                tf1_npoints=tf1_npoints
            )

        # case 3:
        elif x is not None and y is not None:
            x_arr = np.array(x, dtype=float)
            y_arr = np.array(y, dtype=float)

            if len(x_arr) != len(y_arr):
                raise ValueError("Input x and y must have the same length.")

            plot_obj = {
                "x": x_arr,
                "y": y_arr,
                "yerr": None,
                "label": label,
                "linestyle": linestyle,
                "color": color,
                "marker": marker,
                "draw_mode": draw_mode if draw_mode is not None else "line",
                "object_kind": "array",
                "source_type": "input",
                "is_function": False,
            }

        else:
            raise ValueError("Input needs either (filename, objname), obj, or (x, y).")

        self.inputs.append(plot_obj)
        return len(self.inputs)

    def DefineHist(self, input_ids, label=None, draw_mode="line_band", hatch=None):
        input_ids = list(input_ids)

        if len(input_ids) < 1:
            raise ValueError("DefineHist requires at least one input.")

        objs = [self._get_input(i) for i in input_ids]

        x0 = objs[0]["x"]

        for input_id, obj in zip(input_ids[1:], objs[1:]):
            if len(obj["x"]) != len(x0) or not np.allclose(obj["x"], x0, rtol=0, atol=1e-12):
                raise ValueError(
                    f"Input {input_id} has different x coordinates from input {input_ids[0]}."
                )

        y_stack = np.array([obj["y"] for obj in objs], dtype=float)

        y_max = np.max(y_stack, axis=0)
        y_min = np.min(y_stack, axis=0)

        y_central = 0.5 * (y_max + y_min)
        y_err = 0.5 * (y_max - y_min)

        new_obj = {
            "x": x0.copy(),
            "y": y_central,
            "yerr": y_err,
            "label": label,
            "linestyle": "-",
            "color": None,
            "marker": None,
            "draw_mode": draw_mode,
            "object_kind": "envelope",
            "source_type": "defined",
            "is_function": False,
            "defined_from": input_ids.copy(),

            "band_alpha": 0.75,
            "band_hatch": hatch,
            "band_edgecolor": None,
            "band_linewidth": 0,
        }

        self.inputs.append(new_obj)

        return len(self.inputs)

    # =========================================================
    # Panel
    # =========================================================
    def CreatePanels(self, n_panels):
        self.n_panels = n_panels
        self.panels = {i: [] for i in range(1, n_panels + 1)}
        self.panel_height_ratios = None
        self.panel_yranges = {}

        self.sharex_panels = False
        self.hide_upper_xlabels = False
        self.panel_show_legend = {}

        self.default_panel_ylabels = {}

        self.panel_texts = {i: [] for i in range(1, n_panels + 1)}

    def SetPanelHeightRatios(self, ratios):
        if self.n_panels == 0:
            raise RuntimeError("CreatePanels must be called first.")
        if len(ratios) != self.n_panels:
            raise ValueError("Length of ratios must equal number of panels.")
        self.panel_height_ratios = list(ratios)

    def SetPanelLegend(self, panel_id, show=True):
        if panel_id < 1 or panel_id > self.n_panels:
            raise KeyError("Panel {} does not exist.".format(panel_id))
        self.panel_show_legend[panel_id] = bool(show)

    def ClearPanelLegend(self, panel_id=None):
        if panel_id is None:
            self.panel_show_legend = {}
        else:
            if panel_id in self.panel_show_legend:
                del self.panel_show_legend[panel_id]

    # =========================================================
    # CustomSetting
    # =========================================================
    def CustomSetting(self, panel_id, input_id_1, input_id_2=None, operation=None):
        if panel_id not in self.panels:
            raise KeyError(f"Panel {panel_id} does not exist.")

        obj1 = self._get_input(input_id_1)

        #
        if input_id_2 is None and operation is None:
            new_obj = self._clone_plot_object(obj1)
            new_obj["source_type"] = "input_copy"

        #
        else:
            if input_id_2 is None or operation is None:
                raise ValueError("For derived plots, both input_id_2 and operation are required.")
            obj2 = self._get_input(input_id_2)
            new_obj = self._operate_objects(obj1, obj2, operation)
            new_obj["label"] = None
            new_obj["source_type"] = "derived"

        self.panels[panel_id].append(new_obj)
        return len(self.panels[panel_id])

    # =========================================================
    # Compare
    # =========================================================
    def Compare(self, option):
        n_inputs = len(self.inputs)
        if n_inputs == 0:
            raise RuntimeError("No input objects available.")

        if option == "MultiSimple":
            self.CreatePanels(1)
            for i in range(1, n_inputs + 1):
                self.CustomSetting(1, i)

        elif option == "MultiRatio":
            self.CreatePanels(2)
            self.SetPanelHeightRatios([7, 3])
            self.sharex_panels = True
            self.hide_upper_xlabels = True
            self.panel_show_legend[2] = False

            for i in range(1, n_inputs + 1):
                self.CustomSetting(1, i)

            for i in range(1, n_inputs + 1):
                idx = self.CustomSetting(2, i, 1, "Divide")
                if i != 1:
                    label_i = self.inputs[i - 1].get("label", str(i))
                    label_1 = self.inputs[0].get("label", "1")
                    if label_i is not None and label_1 is not None:
                        self.SetCustomPlotLegend(2, idx, "{}/{}".format(label_i, label_1))

            self.default_panel_ylabels = {2: "Ratio"}

        elif option == "MultiDelta":
            self.CreatePanels(2)
            self.SetPanelHeightRatios([7, 3])
            self.sharex_panels = True
            self.hide_upper_xlabels = True
            self.panel_show_legend[2] = False

            for i in range(1, n_inputs + 1):
                self.CustomSetting(1, i)

            for i in range(1, n_inputs + 1):
                idx = self.CustomSetting(2, i, 1, "Subtract")
                if i != 1:
                    label_i = self.inputs[i - 1].get("label", str(i))
                    label_1 = self.inputs[0].get("label", "1")
                    if label_i is not None and label_1 is not None:
                        self.SetCustomPlotLegend(2, idx, "{}-{}".format(label_i, label_1))

            self.default_panel_ylabels = {2: "Delta"}

        elif option == "MultiPull":
            self.CreatePanels(2)
            self.SetPanelHeightRatios([7, 3])
            self.sharex_panels = True
            self.hide_upper_xlabels = True
            self.panel_show_legend[2] = False

            for i in range(1, n_inputs + 1):
                self.CustomSetting(1, i)

            for i in range(1, n_inputs + 1):
                pull_obj = self._make_pull_object(self.inputs[i - 1], self.inputs[0])

                if i != 1:
                    label_i = self.inputs[i - 1].get("label", str(i))
                    label_1 = self.inputs[0].get("label", "1")
                    if label_i is not None and label_1 is not None:
                        pull_obj["label"] = "Pull({}-{})".format(label_i, label_1)

                self.panels[2].append(pull_obj)

            self.default_panel_ylabels = {2: "Pull"}

        else:
            raise ValueError("Unsupported Compare option: {}".format(option))


    # =========================================================
    # Per-panel-plot style settings
    # =========================================================
    def SetXRange(self, xmin, xmax):
        if xmin >= xmax:
            raise ValueError("xmin must be smaller than xmax.")
        self.global_xrange = (xmin, xmax)

    def SetCustomYRange(self, panel_id, ymin, ymax):
        if panel_id < 1 or panel_id > self.n_panels:
            raise KeyError("Panel {} does not exist.".format(panel_id))
        if ymin >= ymax:
            raise ValueError("ymin must be smaller than ymax.")
        self.panel_yranges[panel_id] = (ymin, ymax)

    def ClearXRange(self):
        self.global_xrange = None

    def ClearCustomYRange(self, panel_id=None):
        if panel_id is None:
            self.panel_yranges = {}
        else:
            if panel_id in self.panel_yranges:
                del self.panel_yranges[panel_id]

    def SetCustomPlotLegend(self, panel_id, plot_id, legend):
        self._get_panel_plot(panel_id, plot_id)["label"] = legend

    def SetCustomPlotStyle(self, panel_id, plot_id, style):
        self._get_panel_plot(panel_id, plot_id)["linestyle"] = style

    def SetCustomPlotColor(self, panel_id, plot_id, color):
        self._get_panel_plot(panel_id, plot_id)["color"] = color

    def SetCustomPlotMarker(self, panel_id, plot_id, marker):
        self._get_panel_plot(panel_id, plot_id)["marker"] = marker

    def SetCustomPlot(self, panel_id, plot_id, mode):
        obj = self._get_panel_plot(panel_id, plot_id)

        allowed = ["line", "hist", "scatter", "line_band", "band"]

        if mode not in allowed:
            raise ValueError(f"Unsupported mode: {mode}. Allowed: {allowed}")

        if obj.get("is_function", False) and mode != "line":
            raise ValueError("TF1/function objects can only be drawn as 'line'.")

        if mode == "line_band" and obj.get("yerr", None) is None:
            raise ValueError("Mode 'line_band' requires y errors.")

        obj["draw_mode"] = mode

    def AddText(self, panel_id, x, y, text,
                fontsize=12, color=None,
                ha="left", va="top",
                transform="axes"):
        if panel_id < 1 or panel_id > self.n_panels:
            raise KeyError("Panel {} does not exist.".format(panel_id))

        if transform not in ["axes", "data"]:
            raise ValueError("transform must be 'axes' or 'data'.")

        self.panel_texts[panel_id].append({
            "x": x,
            "y": y,
            "text": text,
            "fontsize": fontsize,
            "color": color,
            "ha": ha,
            "va": va,
            "transform": transform,
        })

    def AddTexts(self, panel_id, text_list, x=0.18, y=0.88, dy=0.08, fontsize=12):
        for i, t in enumerate(text_list):
            self.AddText(panel_id, x, y - i * dy, t, fontsize=fontsize)

    def ClearText(self, panel_id=None):
        if panel_id is None:
            self.panel_texts = {i: [] for i in range(1, self.n_panels + 1)}
        else:
            if panel_id < 1 or panel_id > self.n_panels:
                raise KeyError("Panel {} does not exist.".format(panel_id))
            self.panel_texts[panel_id] = []

    # =========================================================
    # Draw
    # =========================================================
    def Draw(self, filename="plot.png", xlabel="x", ylabel="y",
             panel_xlabels=None, panel_ylabels=None,
             logx=False, logy=False, figsize=None, dpi=300):
        if self.n_panels == 0:
            raise RuntimeError("No panels defined. Call CreatePanels or Compare first.")

        if figsize is None:
            if self.sharex_panels and self.n_panels == 2:
                figsize = (6.4, 4.8)
            else:
                figsize = (6.4, 4.8 * self.n_panels)

        gridspec_kw = {}
        if self.panel_height_ratios is not None:
            gridspec_kw["height_ratios"] = self.panel_height_ratios

        fig, axes = plt.subplots(
            self.n_panels, 1,
            figsize=figsize,
            squeeze=False,
            sharex=self.sharex_panels,
            gridspec_kw=gridspec_kw if gridspec_kw else None
        )
        axes = axes.flatten()

        if self.sharex_panels and self.n_panels > 1:
            fig.subplots_adjust(hspace=0.0)

        for i in range(self.n_panels):
            panel_id = i + 1
            ax = axes[i]

            for obj in self.panels[panel_id]:
                self._draw_one(ax, obj)

            if logx:
                ax.set_xscale("log")
            if logy:
                ax.set_yscale("log")

            this_xlabel = xlabel
            this_ylabel = ylabel

            if panel_xlabels is not None and panel_id in panel_xlabels:
                this_xlabel = panel_xlabels[panel_id]

            if panel_id in self.default_panel_ylabels:
                this_ylabel = self.default_panel_ylabels[panel_id]

            if panel_ylabels is not None and panel_id in panel_ylabels:
                this_ylabel = panel_ylabels[panel_id]

            if self.hide_upper_xlabels and panel_id != self.n_panels:
                ax.set_xlabel("")
                ax.tick_params(axis="x", which="both", labelbottom=False)
            else:
                ax.set_xlabel(this_xlabel)

            ax.set_ylabel(this_ylabel)

            # for legend
            force_show = self.panel_show_legend.get(panel_id, None)

            if force_show is True:
                has_legend = any(obj.get("label") is not None for obj in self.panels[panel_id])
                if has_legend:
                    ax.legend()

            elif force_show is False:
                pass

            else:
                has_legend = any(obj.get("label") is not None for obj in self.panels[panel_id])
                if has_legend:
                    ax.legend()

            if self.global_xrange is not None:
                ax.set_xlim(self.global_xrange[0], self.global_xrange[1])

            if panel_id in self.panel_yranges:
                yr = self.panel_yranges[panel_id]
                ax.set_ylim(yr[0], yr[1])

            for txt in self.panel_texts.get(panel_id, []):
                trans = ax.transAxes if txt["transform"] == "axes" else ax.transData

                ax.text(
                    txt["x"], txt["y"], txt["text"],
                    fontsize=txt["fontsize"],
                    color=txt["color"],
                    ha=txt["ha"],
                    va=txt["va"],
                    transform=trans
                )

            if self.sharex_panels and self.n_panels == 2 and panel_id == 1:
                yticklabels = ax.get_yticklabels()
                if len(yticklabels) > 0:
                    yticklabels[0].set_visible(False)

            ax.tick_params(direction="in", which="both", top=True, right=True)

            #if self.sharex_panels and self.n_panels == 2:
            if panel_id == 1:
                ax.tick_params(axis="both", which="major", length=6, width=1.0, labelsize=10)
                ax.tick_params(axis="both", which="minor", length=3, width=0.8)
            else:
                ax.tick_params(axis="both", which="major", length=5, width=1.0, labelsize=8)
                ax.tick_params(axis="both", which="minor", length=3, width=0.8)

            ax.yaxis.set_minor_locator(AutoMinorLocator(2))

            if logx:
                xmin, xmax = ax.get_xlim()
                log_span = np.log10(xmax) - np.log10(xmin)

                if log_span <= 1.2:
                    ax.xaxis.set_major_locator(LogLocator(base=10.0, subs=(1.0, 2.0, 3.0, 4.0, 6.0)))
                else:
                    ax.xaxis.set_major_locator(LogLocator(base=10.0))
                ax.xaxis.set_major_formatter(LogFormatter(base=10))

                ax.xaxis.set_minor_locator(LogLocator(base=10.0, subs=np.arange(2, 10) * 0.1))
                ax.xaxis.set_minor_formatter(NullFormatter())
            else:
                ax.xaxis.set_minor_locator(AutoMinorLocator(4))

            if self.sharex_panels and self.n_panels == 2:
                if panel_id == 1:
                    if self.hide_upper_xlabels:
                        ax.set_xlabel("")
                        ax.tick_params(axis="x", which="both", labelbottom=False)
                    else:
                        ax.set_xlabel(this_xlabel, fontsize=12)
                    ax.set_ylabel(this_ylabel, fontsize=12)
                else:
                    ax.set_xlabel(this_xlabel, fontsize=10)
                    ax.set_ylabel(this_ylabel, fontsize=10)
            else:
                if self.hide_upper_xlabels and panel_id != self.n_panels:
                    ax.set_xlabel("")
                    ax.tick_params(axis="x", which="both", labelbottom=False)
                else:
                    ax.set_xlabel(this_xlabel, fontsize=10)
                ax.set_ylabel(this_ylabel, fontsize=12)


        fig.canvas.draw()

        for ax in axes:
            if logx:
                self._hide_edge_xticks(ax)

        fig.savefig(filename, dpi=dpi, bbox_inches="tight")
        plt.close(fig)

    # =========================================================
    # Info / debug
    # =========================================================
    def ListInputs(self):
        for i, obj in enumerate(self.inputs, start=1):
            print(
                f"Input {i}: "
                f"label={obj.get('label', None)}, "
                f"kind={obj.get('object_kind', None)}, "
                f"mode={obj.get('draw_mode', None)}, "
                f"source={obj.get('source_type', None)}"
            )

    def ListPanels(self):
        for panel_id, objs in self.panels.items():
            print(f"Panel {panel_id}:")
            for i, obj in enumerate(objs, start=1):
                print(
                    f"  Plot {i}: "
                    f"label={obj.get('label', None)}, "
                    f"kind={obj.get('object_kind', None)}, "
                    f"mode={obj.get('draw_mode', None)}, "
                    f"source={obj.get('source_type', None)}"
                )

    def ClearInputs(self):
        self.inputs = []

    def ClearPanels(self):
        self.panels = {}
        self.n_panels = 0
        self.panel_height_ratios = None

    def Reset(self):
        self.ClearInputs()
        self.ClearPanels()

    # =========================================================
    # Internal helpers
    # =========================================================
    def _get_root_object(self, filename, objname):
        f = ROOT.TFile.Open(filename)
        if not f or f.IsZombie():
            raise OSError(f"Cannot open ROOT file: {filename}")

        obj = f.Get(objname)
        if not obj:
            f.Close()
            raise KeyError(f"Cannot find object '{objname}' in file '{filename}'")

        if obj.InheritsFrom("TH1"):
            obj_copy = obj.Clone()
            obj_copy.SetDirectory(0)
        elif obj.InheritsFrom("TGraph") or obj.InheritsFrom("TF1"):
            obj_copy = obj.Clone()
        else:
            f.Close()
            raise TypeError(f"Unsupported ROOT object type: {obj.ClassName()}")

        f.Close()
        return obj_copy

    def _convert_root_object_to_plot(self, obj, label=None, linestyle="-", color=None,
                                     marker=None, draw_mode=None, tf1_npoints=400):
        # TH1 / TH1D
        if obj.InheritsFrom("TH1"):
            nbins = obj.GetNbinsX()
            x = np.array([obj.GetBinCenter(i) for i in range(1, nbins + 1)], dtype=float)
            y = np.array([obj.GetBinContent(i) for i in range(1, nbins + 1)], dtype=float)
            yerr = np.array([obj.GetBinError(i) for i in range(1, nbins + 1)], dtype=float)

            return {
                "x": x,
                "y": y,
                "yerr": yerr,
                "label": label,
                "linestyle": linestyle,
                "color": color,
                "marker": marker,
                "draw_mode": draw_mode if draw_mode is not None else "hist",
                "object_kind": "hist",
                "source_type": "input",
                "is_function": False,
            }

        # TGraphErrors
        elif obj.InheritsFrom("TGraphErrors"):
            n = obj.GetN()
            x = np.array([obj.GetX()[i] for i in range(n)], dtype=float)
            y = np.array([obj.GetY()[i] for i in range(n)], dtype=float)
            yerr = np.array([obj.GetEY()[i] for i in range(n)], dtype=float)

            return {
                "x": x,
                "y": y,
                "yerr": yerr,
                "label": label,
                "linestyle": linestyle,
                "color": color,
                "marker": marker if marker is not None else "o",
                "draw_mode": draw_mode if draw_mode is not None else "hist",
                "object_kind": "graph_errors",
                "source_type": "input",
                "is_function": False,
            }

        #
        elif obj.InheritsFrom("TGraph"):
            n = obj.GetN()
            x = np.array([obj.GetX()[i] for i in range(n)], dtype=float)
            y = np.array([obj.GetY()[i] for i in range(n)], dtype=float)

            return {
                "x": x,
                "y": y,
                "yerr": None,
                "label": label,
                "linestyle": linestyle,
                "color": color,
                "marker": marker,
                "draw_mode": draw_mode if draw_mode is not None else "line",
                "object_kind": "graph",
                "source_type": "input",
                "is_function": False,
            }

        # TF1
        elif obj.InheritsFrom("TF1"):
            xmin = obj.GetXmin()
            xmax = obj.GetXmax()
            x = np.linspace(xmin, xmax, tf1_npoints)
            y = np.array([obj.Eval(xx) for xx in x], dtype=float)

            return {
                "x": x,
                "y": y,
                "yerr": None,
                "label": label,
                "linestyle": linestyle,
                "color": color,
                "marker": None,
                "draw_mode": "line",
                "object_kind": "function",
                "source_type": "input",
                "is_function": True,
            }

        else:
            raise TypeError(f"Unsupported ROOT object type: {obj.ClassName()}")

    def _make_pull_object(self, obj1, obj_ref):
        x1, y1 = obj1["x"], obj1["y"]
        x2, y2 = obj_ref["x"], obj_ref["y"]

        if len(x1) != len(x2) or not np.allclose(x1, x2, rtol=0, atol=1e-12):
            raise ValueError("x coordinates do not match.")

        err1 = obj1.get("yerr", None)
        err2 = obj_ref.get("yerr", None)

        if err1 is None:
            err1 = np.zeros_like(y1, dtype=float)
        else:
            err1 = np.array(err1, dtype=float)

        if err2 is None:
            err2 = np.zeros_like(y2, dtype=float)
        else:
            err2 = np.array(err2, dtype=float)

        delta = y1 - y2
        sigma = np.sqrt(err1**2 + err2**2)

        pull = np.full_like(delta, np.nan, dtype=float)
        mask = (sigma > 0)
        pull[mask] = delta[mask] / sigma[mask]

        return {
            "x": x1.copy(),
            "y": pull,
            "yerr": None,
            "label": None,
            "linestyle": "-",
            "color": None,
            "marker": None,
            "draw_mode": "line",
            "object_kind": "derived",
            "source_type": "derived",
            "is_function": False,
        }

    def _clone_plot_object(self, obj):
        return {
            "x": obj["x"].copy(),
            "y": obj["y"].copy(),
            "yerr": None if obj.get("yerr", None) is None else obj["yerr"].copy(),
            "label": obj.get("label", None),
            "linestyle": obj.get("linestyle", "-"),
            "color": obj.get("color", None),
            "marker": obj.get("marker", None),
            "draw_mode": obj.get("draw_mode", "line"),
            "object_kind": obj.get("object_kind", None),
            "source_type": obj.get("source_type", "input"),
            "is_function": obj.get("is_function", False),
            "band_alpha": obj.get("band_alpha", 0.35),
            "band_hatch": obj.get("band_hatch", None),
            "band_edgecolor": obj.get("band_edgecolor", None),
            "band_linewidth": obj.get("band_linewidth", 0),
        }

    def _operate_objects(self, obj1, obj2, operation):
        x1, y1 = obj1["x"], obj1["y"]
        x2, y2 = obj2["x"], obj2["y"]

        if len(x1) != len(x2) or not np.allclose(x1, x2, rtol=0, atol=1e-12):
            raise ValueError("x coordinates do not match.")

        #
        err1 = obj1.get("yerr", None)
        err2 = obj2.get("yerr", None)

        if err1 is None:
            err1 = np.zeros_like(y1, dtype=float)
        else:
            err1 = np.array(err1, dtype=float)

        if err2 is None:
            err2 = np.zeros_like(y2, dtype=float)
        else:
            err2 = np.array(err2, dtype=float)

        if operation == "Add":
            y = y1 + y2
            yerr = np.sqrt(err1**2 + err2**2)

        elif operation == "Subtract":
            y = y1 - y2
            yerr = np.sqrt(err1**2 + err2**2)

        elif operation == "Multiply":
            y = y1 * y2
            yerr = np.sqrt((y2 * err1)**2 + (y1 * err2)**2)

        elif operation == "Divide":
            y = np.divide(y1, y2, out=np.full_like(y1, np.nan), where=(y2 != 0))

            yerr = np.full_like(y1, np.nan, dtype=float)
            mask = (y2 != 0)
            yerr[mask] = np.sqrt(
                (err1[mask] / y2[mask])**2 +
                ((y1[mask] * err2[mask]) / (y2[mask]**2))**2
            )

        else:
            raise ValueError(f"Unsupported operation: {operation}")

        has_any_error = np.any(np.isfinite(yerr) & (np.abs(yerr) > 0))

        return {
            "x": x1.copy(),
            "y": y,
            "yerr": yerr,
            "label": None,
            "linestyle": "-",
            "color": None,
            "marker": None,
            "draw_mode": "hist" if has_any_error else "line",
            "object_kind": "derived",
            "source_type": "derived",
            "is_function": False,
        }

    def _draw_one(self, ax, obj):
        mode = obj.get("draw_mode", "line")
        kind = obj.get("object_kind", None)

        x = obj["x"]
        y = obj["y"]
        yerr = obj.get("yerr", None)

        label = obj.get("label", None)
        linestyle = obj.get("linestyle", "-")
        color = obj.get("color", None)
        marker = obj.get("marker", None)

        if mode == "line":
            ax.plot(x, y, label=label, linestyle=linestyle, color=color, marker=marker)

        elif mode == "scatter":
            ax.scatter(x, y, label=label, color=color, marker=marker)

        elif mode == "line_band":
            if obj.get("is_function", False):
                raise ValueError("TF1/function objects cannot be drawn as 'line_band'.")

            if yerr is None:
                raise ValueError("Mode 'line_band' requires yerr.")

            #
            tmp_line = ax.plot(x, y, color=color)[0]
            band_color = color if color is not None else tmp_line.get_color()
            band_hatch = obj.get("band_hatch", None)

            #
            ax.fill_between(
                x,
                y - yerr,
                y + yerr,
                color=band_color,
                alpha=0.75,
                linewidth=0.1,
                zorder=1,
                hatch=band_hatch,
                label=label
            )

            #
            #line = ax.plot(
            #    x, y,
            #    label=label,
            #    linestyle=linestyle,
            #    color=color,
            #    marker=marker,
            #    linewidth=0.01,
            #    alpha=0.75
            #)[0]

        elif mode == "band":
            if yerr is None:
                raise ValueError("Mode 'band' requires yerr.")

            tmp_line = ax.plot(x, y, color=color)[0]
            band_color = color if color is not None else tmp_line.get_color()
            tmp_line.remove()

            ax.fill_between(
                x,
                y - yerr,
                y + yerr,
                color=band_color,
                alpha=0.7,
                linewidth=0,
                zorder=1,
                label=label
            )

        elif mode == "hist":
            if obj.get("is_function", False):
                raise ValueError("TF1/function objects can only be drawn as 'line'.")

            # TGraphErrors -> errorbar
            if kind == "graph_errors":
                ax.errorbar(
                    x, y, yerr=yerr,
                    label=label,
                    color=color,
                    linestyle=linestyle,
                    marker=marker if marker is not None else "o",
                    capsize=2
                )

            # 
            elif kind == "hist":
                if yerr is not None and np.any(np.abs(yerr) > 0):
                    ax.errorbar(
                        x, y, yerr=yerr,
                        label=label,
                        color=color,
                        linestyle="none",
                        marker=marker if marker is not None else "o",
                        capsize=2
                    )
                else:
                    ax.step(
                        x, y,
                        where="mid",
                        label=label,
                        linestyle=linestyle,
                        color=color
                    )

            # 
            else:
                ax.step(
                    x, y,
                    where="mid",
                    label=label,
                    linestyle=linestyle,
                    color=color
                )

        else:
            raise ValueError(f"Unsupported draw_mode: {mode}")

    def _get_input(self, input_id):
        if input_id < 1 or input_id > len(self.inputs):
            raise IndexError(f"Input {input_id} does not exist.")
        return self.inputs[input_id - 1]

    def _get_panel_plot(self, panel_id, plot_id):
        if panel_id not in self.panels:
            raise KeyError(f"Panel {panel_id} does not exist.")
        if plot_id < 1 or plot_id > len(self.panels[panel_id]):
            raise IndexError(f"Plot {plot_id} does not exist in panel {panel_id}.")
        return self.panels[panel_id][plot_id - 1]

    def _hide_edge_xticks(self, ax):
        ticks = ax.xaxis.get_major_ticks()
        if len(ticks) >= 2:
            ticks[0].tick1line.set_visible(False)
            ticks[0].tick2line.set_visible(False)
            ticks[0].label1.set_visible(False)
            ticks[0].label2.set_visible(False)

            ticks[-1].tick1line.set_visible(False)
            ticks[-1].tick2line.set_visible(False)
            ticks[-1].label1.set_visible(False)
            ticks[-1].label2.set_visible(False)
