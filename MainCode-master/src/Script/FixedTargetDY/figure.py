from Plotter import Plotter
import numpy as np

p = Plotter()

xlist = np.array([0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1])
#ylist = np.array([0.810445, 0.509889, 0.529769, 0.473729, 0.488844, 0.463317, 0.473709, 0.458489, 0.466009, 0.455623])
#intlist= np.array([1.38381, 0.799066, 0.674592, 0.525942, 0.474843, 0.398873, 0.369194, 0.321184, 0.301268, 0.267568])
intlist = np.array([1.02247, 0.738321, 0.594, 0.501409, 0.435196, 0.384733, 0.344618, 0.311759, 0.28423, 0.26076])
ylist = np.array([0.449108, 0.449144, 0.449177, 0.449196, 0.449197, 0.449177, 0.449133, 0.449063, 0.44897, 0.448815])

#p.Input("file_nlo.root", "pert", label="pert", linestyle="--")
p.Input("file_nlo.root", "delsig", label="delsig", linestyle=":")
p.Input(x=xlist, y=ylist, label="integration_pert+delsig")
p.Input(x=xlist, y=intlist, label="intgration_pert")
p.Compare("MultiSimple")

p.Draw(
    xlabel=r"$p_T$",
    ylabel=r"xSec",
    filename="pT_delsig.png",
    logx=True
)

