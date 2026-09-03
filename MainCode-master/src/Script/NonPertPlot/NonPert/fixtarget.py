import matplotlib as mpl
mpl.use('cairo')

import uproot
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.gridspec import GridSpec
import warnings
warnings.filterwarnings("ignore")


SCALES = [str(x) for x in range(1051, 1066)]
DATASETS = [
            "R209",
            "E605",
            "E288200",
            "E288300",
            "E288400",
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


def plot(dataset, rootfile, nplot, **options):
    gs = GridSpec(1, 1, height_ratios=[1.0], hspace=0)

    ax = plt.subplot(gs[0])

    for iplot in range(1, nplot, 1):

        Tlabel = ""
        Dlabel = ""
        if iplot == 1: Tlabel = "ResBos2"
        else : Tlabel = ""

        if iplot == 1: Dlabel = options["datalabel"]
        else : Dlabel = ""

        data = rootfile[f"{dataset}_{iplot}_Data"].to_hist()
        data_vals, data_err = data.values(), np.sqrt(data.variances())

#        data.plot1d(ax=ax, color='tab:red', label=Dlabel)

        theory_wgt, edges = rootfile[f"{dataset}_{iplot}_Theory"].to_numpy()

        theory = rootfile[f"{dataset}_{iplot}_Theory"].to_hist()
        theory_err = np.sqrt(theory.variances())
    
        edges = np.append(edges, edges[-1]*3)

        # Plot everything
        theory_wgt = pad_vals(theory_wgt)
        theory_err = pad_vals(theory_err)

        theory_up = theory_wgt + theory_err;
        theory_dw = theory_wgt - theory_err;

        data_vals = pad_vals(data_vals)
        data_err = pad_vals(data_err)
        centers = (edges[1:] + edges[:-1])/2
        errors = (edges[1:] - edges[:-1])/2

        ax.step(edges, theory_wgt, where='pre', color='tab:blue',
                    label=Tlabel)

        ax.errorbar(centers, data_vals[1:], yerr=data_err[1:], xerr=errors,
                    color='tab:red', ls='none', label=Dlabel)

        if iplot == 1:
           if dataset == "E288400":
               plt.subplot(gs[0])
               plt.ylim((1e-5,5))
           elif dataset == "E288300":
               plt.subplot(gs[0])
               plt.ylim((1e-4,12))
           elif dataset == "E605":
               plt.subplot(gs[0])
               plt.ylim((1e-3,1))

        # Fill out ratio plot
    
        # Set options
        ax.legend(frameon=False)
        #ax.set_xscale('log')
        ax.set_yscale('log')
    
        ax.legend(frameon=False, borderaxespad=1)
        ax.tick_params(axis='both', direction='in', reset=True,
                       which='both')
        ax.tick_params(which='major', length=5)
        ax.tick_params(which='minor', length=2)
        plt.setp(ax.get_xticklabels(), visible=False)
    
        plt.xlim([edges[0], edges[-2]])
        ax.set_ylabel(options['ylabel'], horizontalalignment='right', y=1.0)

    plt.savefig(f"{dataset}.pdf", bbox_inches='tight')
    plt.close()


def Stringify(dataset):
    name = dataset.split('_')[0]
    if 'ATLAS' in name:
        return r"ATLAS $\sqrt{s} = 8$ TeV"
    elif 'D01' in name:
        return r"D0 $\sqrt{s} = 1.8$ TeV"
    elif 'D02' in name:
        return r"D0 $\sqrt{s} = 1.96$ TeV"
    elif 'CDF1' in name:
        return r"CDF $\sqrt{s} = 1.8$ TeV"
    elif 'CDF2' in name:
        return r"CDF $\sqrt{s} = 1.96$ TeV"
    elif 'E288200' in name:
        return r"E288200 $\sqrt{s} = 19.4$ GeV"
    elif 'E288300' in name:
        return r"E288300 $\sqrt{s} = 23.8$ GeV"
    elif 'E288400' in name:
        return r"E288400 $\sqrt{s} = 27.4$ GeV"
    elif 'E605' in name:
        return r"E605 $\sqrt{s} = 38.8$ GeV"
    elif 'R209' in name:
        return r"R209 $\sqrt{s} = 62.0$ GeV"


def main():
    # Load files
    rootfile = uproot.open("save.root")
    for dataset in DATASETS:
        if "E288200" in dataset: nplot = 5
        elif "E288300" in dataset: nplot = 6
        elif "E288400" in dataset: nplot = 7
        elif "E605" in dataset: nplot = 6
        elif "R209" in dataset: nplot = 3

        xlabel = r"$p_T$ [GeV]"
        ylabel = r"$\frac{{\rm d}\sigma}{{\rm d} p_T}$ [pb/GeV]"
        datalabel = Stringify(dataset)
        plot(dataset, rootfile, nplot, 
             xlabel=xlabel,
             ylabel=ylabel,
             datalabel=datalabel)


if __name__ == '__main__':
    main()
