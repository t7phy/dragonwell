import matplotlib as mpl
mpl.use('cairo')

import uproot
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.gridspec import GridSpec
import warnings
warnings.filterwarnings("ignore")


SCALES = [str(x) for x in range(1051, 1066)]
DATASETS = ["ATLAS8TeV_A0_pT",
            "ATLAS8TeV_A1_pT",
            "ATLAS8TeV_A2_pT",
            "ATLAS8TeV_A3_pT",
            "ATLAS8TeV_A4_pT",
            "ATLAS8TeV_A02_pT",
            ]


def pad_vals(array):
    array = np.insert(array, 0, array[0])
    array = np.append(array, 0)
    return array


def pad_all(arrays):
    results = []
    for array in arrays:
        results.append(pad_vals(array))
    return results


def plot(dataset, rootfile, **options):
    gs = GridSpec(2, 1, height_ratios=[0.75, 0.25], hspace=0)

    ax = plt.subplot(gs[0])
    bx = plt.subplot(gs[1], sharex=ax)


    Tlabel = "ResBos2"
    Dlabel = options["datalabel"]

    data = rootfile[f"{dataset}_Data"].to_hist()
    data_vals, data_err = data.values(), np.sqrt(data.variances())
#    data.plot1d(ax=ax, color='tab:red', label=Dlabel)

    data_unreg = rootfile[f"{dataset}_Data_UnReg"].to_hist()
    data_unreg_vals, data_unreg_err = data_unreg.values(), np.sqrt(data_unreg.variances())
#    data_unreg.plot1d(ax=ax, color='tab:purple', label=Dlabel+' unreg')

    theory = rootfile[f"{dataset}_Theory_Final"].to_hist()
    theory_err = np.sqrt(theory.variances())

    theory_wgt, edges = rootfile[f"{dataset}_Theory_Final"].to_numpy()

    edges = np.append(edges, edges[-1]*3)

    # Plot everything
    theory_wgt = pad_vals(theory_wgt)
    theory_err = pad_vals(theory_err)

    theory_up = theory_wgt + theory_err;
    theory_dw = theory_wgt - theory_err;

    data_vals = pad_vals(data_vals)
    data_err = pad_vals(data_err)
    data_unreg_vals = pad_vals(data_unreg_vals)
    data_unreg_err = pad_vals(data_unreg_err)
    centers = (edges[1:] + edges[:-1])/2
    errors = (edges[1:] - edges[:-1])/2

    ax.fill_between(edges, theory_up, theory_dw, step='pre',
                    color='tab:blue',
                    alpha=0.7, label=Tlabel)

    ax.errorbar(centers, data_vals[1:], yerr=data_err[1:], xerr=errors, 
                color='tab:red', ls='none', label=Dlabel)
    ax.errorbar(centers, data_unreg_vals[1:], yerr=data_unreg_err[1:], xerr=errors,
                color='tab:purple', ls='none', label=Dlabel+' unreg')

#    ax.step(edges, theory_wgt, where='pre', color='tab:blue',
#            label=Tlabel)

#    plt.subplot(gs[0])
#    plt.ylim((1e-5,5))

    # Fill out ratio plot
    theory_ratio = theory_wgt / data_vals
    theory_up_ratio = theory_up / data_vals
    theory_dw_ratio = theory_dw / data_vals
    data_err_ratio = data_err / abs(data_vals)
    data_ratio = data_vals / data_vals
    data_unreg_ratio = data_unreg_vals / data_vals
    data_unreg_err_ratio = data_unreg_err / abs(data_vals)

#    bx.step(edges, theory_ratio, where='pre', color='tab:blue',
#            label="ResBos2")

    bx.fill_between(edges, theory_up_ratio, theory_dw_ratio, step='pre',
                    color='tab:blue',
                    alpha=0.7, label=Tlabel)

    bx.errorbar(centers, data_ratio[1:], data_err_ratio[1:], errors,
                color='tab:red')
    bx.errorbar(centers, data_unreg_ratio[1:], data_unreg_err_ratio[1:], errors, 
                color='tab:purple', ls='none')

    # Set options
    ax.legend(frameon=False)
    ax.set_xscale('log')
    #ax.set_yscale('log')

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

    plt.xlim([edges[0], edges[-2]])
    ax.set_ylabel(options['ylabel'], horizontalalignment='right', y=1.0)
    bx.set_xlabel(options['xlabel'], horizontalalignment='right', x=1.0)
    bx.set_ylabel("Ratio to Data")

    plt.savefig(f"{dataset}.pdf", bbox_inches='tight')
    plt.close()


def Stringify(dataset):
    name = dataset.split('_')[0]
    return r"ATLAS $\sqrt{s} = 8$ TeV"


def main():
    # Load files
    rootfile = uproot.open("MC_results.root")
    for dataset in DATASETS:
        xlabel = r"$p_T$ [GeV]"
        if 'A0_' in dataset: ylabel = r"A0"
        elif 'A1' in dataset: ylabel = r"A1"
        elif 'A2' in dataset: ylabel = r"A2"
        elif 'A3' in dataset: ylabel = r"A3"
        elif 'A4' in dataset: ylabel = r"A4"
        elif 'A02' in dataset: ylabel = r"A0-A2"

        datalabel = Stringify(dataset)
        plot(dataset, rootfile,
             xlabel=xlabel,
             ylabel=ylabel,
             datalabel=datalabel)


if __name__ == '__main__':
    main()
