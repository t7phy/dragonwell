import uproot
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.gridspec import GridSpec
import warnings
warnings.filterwarnings("ignore")


SCALES = [str(x) for x in range(1051, 1066)]
DATASETS = ["ATLAS13TeV_pT", "ATLAS13TeV_Phi",
            "CMS13TeV_pT", "CMS13TeV_Phi",
            "CMS13TeV_pT_Y1",
            "CMS13TeV_pT_Y2",
            "CMS13TeV_pT_Y3",
            "CMS13TeV_pT_Y4",
            "CMS13TeV_pT_Y5",
            "LHCb13TeV_pT", "LHCb13TeV_Phi"]


def pad_vals(array):
    array = np.insert(array, 0, array[0])
    array = np.append(array, 0)
    return array


def pad_all(arrays):
    results = []
    for array in arrays:
        results.append(pad_vals(array))
    return results


def plot(dataset, scales, pdf, **options):
    gs = GridSpec(2, 1, height_ratios=[0.75, 0.25], hspace=0)

    ax = plt.subplot(gs[0])
    bx = plt.subplot(gs[1], sharex=ax)

    data = scales[0][f"{dataset}_Data"].to_hist()
    data_vals, data_err = data.values(), np.sqrt(data.variances())
    data.plot1d(ax=ax, color='tab:red', label=options["datalabel"])
    theory_wgt, edges = scales[0][f"{dataset}_Theory_Final"].to_numpy()

    # Handle scale variations
    scale_up = np.empty(())
    scale_dw = np.ones(())*np.inf
    for scale in scales[1:]:
        scale_var, _ = scale[f"{dataset}_Theory_Final"].to_numpy()
        scale_up = np.maximum(scale_up, scale_var)
        scale_dw = np.minimum(scale_dw, scale_var)

    # Handle PDF uncertainty
    pdf_err, _ = pdf[f"{dataset}_Theory_Final_PDFError"].to_numpy()
    pdf_up = theory_wgt + pdf_err
    pdf_dw = theory_wgt - pdf_err
    edges = np.append(edges, edges[-1]*3)
    scale_up = np.sqrt((scale_up-theory_wgt)**2 + pdf_err**2) + theory_wgt
    scale_dw = theory_wgt - np.sqrt((scale_dw-theory_wgt)**2 + pdf_err**2)

    # Plot everything
    theory_wgt, pdf_up, pdf_dw, scale_up, scale_dw = pad_all([theory_wgt,
                                                              pdf_up, pdf_dw,
                                                              scale_up,
                                                              scale_dw])
    ax.step(edges, theory_wgt, where='pre', color='tab:blue',
            label="ResBos2")
    ax.fill_between(edges, pdf_up, pdf_dw, step='pre', color='tab:blue',
                    alpha=0.7, label="PDF Uncertainty")
    ax.fill_between(edges, scale_up, scale_dw, step='pre', color='tab:blue',
                    alpha=0.5, label="Scale Uncertainty")

    ax.legend(frameon=False)
    ax.set_xscale('log')
    ax.set_yscale('log')

    ax.legend(frameon=False, borderaxespad=1)
    ax.tick_params(axis='both', direction='in', reset=True,
                   which='both')
    ax.tick_params(which='major', length=5)
    ax.tick_params(which='minor', length=2)
    bx.tick_params(axis='both', direction='in', reset=True,
                   which='both')
    bx.tick_params(which='major', length=5)
    bx.tick_params(which='minor', length=2)
    plt.setp(ax.get_xticklabels(), visible=False)

    # Fill out ratio plot
    data_vals = pad_vals(data_vals)
    data_err = pad_vals(data_err)
    theory_ratio = theory_wgt / data_vals
    pdf_up_ratio = pdf_up / data_vals
    pdf_dw_ratio = pdf_dw / data_vals
    scale_up_ratio = scale_up / data_vals
    scale_dw_ratio = scale_dw / data_vals
    data_err_ratio = data_err / data_vals
    data_ratio = data_vals / data_vals
    bx.step(edges, theory_ratio, where='pre', color='tab:blue',
            label="ResBos2")
    bx.fill_between(edges, pdf_up_ratio, pdf_dw_ratio, step='pre', color='tab:blue',
                    alpha=0.7, label="PDF Uncertainty")
    bx.fill_between(edges, scale_up_ratio, scale_dw_ratio, step='pre', color='tab:blue',
                    alpha=0.5, label="Scale Uncertainty")
    centers = (edges[1:] + edges[:-1])/2
    errors = (edges[1:] - edges[:-1])/2
    bx.errorbar(centers, data_ratio[1:], data_err_ratio[1:], errors, color='tab:red')

    plt.xlim([edges[0], edges[-2]])
    ax.set_ylabel(options['ylabel'], horizontalalignment='right', y=1.0)
    bx.set_xlabel(options['xlabel'], horizontalalignment='right', x=1.0)
    bx.set_ylabel("Ratio to Data")
    plt.savefig(f"{dataset}.pdf", bbox_inches='tight')
    plt.close()


def Stringify(dataset):
    name = dataset.split('_')[0]
    if '8' in name:
        return name.split('8')[0] + r" $\sqrt{s} = 8$ TeV"
    elif '13' in name:
        return name.split('13')[0] + r" $\sqrt{s} = 13$ TeV"


def main():
    # Load files
    pdf = uproot.open("PDFUnc_Symmetry.root")
    scales = [uproot.open(f"Scale{scale}/MC_results.root") for scale in SCALES]
    for dataset in DATASETS:
        if "pT" in dataset:
            xlabel = r"$p_T$ [GeV]"
            ylabel = r"$\frac{{\rm d}\sigma}{{\rm d} p_T}$ [pb/GeV]"
        elif "Phi" in dataset:
            xlabel = r"$\phi^{*}_{\eta}$"
            ylabel = r"$\frac{{\rm d}\sigma}{{\rm d} \phi^{*}_{\eta}}$ [pb]"
        datalabel = Stringify(dataset)
        plot(dataset, scales, pdf, xlabel=xlabel,
             ylabel=ylabel,
             datalabel=datalabel)


if __name__ == '__main__':
    main()
