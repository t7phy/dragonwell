import numpy as np
from scipy.optimize import least_squares
import PyGlobalFitting as fit

fit_instance = fit.PyGlobalFitting()

fit_instance.Initialize()

initial_params = np.asarray(fit_instance.GetInitialParameters(),
                             dtype=np.float64)

def residuals(params: np.ndarray) -> np.ndarray:
    chi2_val = fit_instance.Chi2(params.tolist())
    return np.sqrt(chi2_val) * np.ones(1, dtype=np.float64)

for i in range(fit_instance.GetLFit()):

    print(f"Starting {i + 1} Fit:")

    fit_instance.ResetFit();

    result = least_squares(
        residuals,
        initial_params,
        method='trf',
        xtol=1e-9,
        ftol=fit_instance.GetMinTol(),
        gtol=1e-9,
        max_nfev=fit_instance.GetMaxCall(),
        verbose=2
    )

    optimized_parameters = result.x.tolist()
    fit_instance.Finalize(optimized_parameters, optimized_parameters) # this algorithm doesn't return the uncertainty of parameters

    fit_instance.UpdateParameterCentral()

    initial_params = np.asarray(fit_instance.GetInitialParameters(),
                                 dtype=np.float64)

    if abs(fit_instance.DeltaChi2()) < 0.1:
        break

print("Fitting done!")

