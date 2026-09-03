import numpy as np
import tensorflow as tf
import tensorflow_probability as tfp
import PyGlobalFitting as fit

fit_instance = fit.PyGlobalFitting()

fit_instance.Initialize()

initial_parameters = fit_instance.GetInitialParameters()
parameters = tf.Variable(initial_parameters, dtype=tf.float32, name='parameters')

def chi2_fn(parameters):
    param_list = parameters.numpy().tolist()[0]
    chi2_value = fit_instance.Chi2(param_list)
    return tf.convert_to_tensor(chi2_value, dtype=tf.float32)

def objective_fn(parameters):
    return tf.constant(chi2_fn(parameters))

for i in range(fit_instance.GetLFit()):

    print(f"Starting {i + 1} Fit:")

    fit_instance.ResetFit();

    result = tfp.optimizer.nelder_mead_minimize(
        objective_function=objective_fn,
        initial_vertex=tf.convert_to_tensor([initial_parameters]),
        max_iterations=1000,
        func_tolerance=1e-6,
        step_sizes=tf.convert_to_tensor([0.1]*len(initial_parameters)),
    )

    optimized_parameters = result.position.numpy().tolist()[0]
    fit_instance.Finalize(optimized_parameters, optimized_parameters) # this algorithm doesn't return the uncertainty of parameters

    fit_instance.UpdateParameterCentral()

    initial_parameters = fit_instance.GetInitialParameters()

    if abs(fit_instance.DeltaChi2()) < 0.1:
        break

print("Fitting done!")

