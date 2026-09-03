import numpy as np
import tensorflow as tf
import tensorflow_probability as tfp
import PyGlobalFitting as fit

fit_instance = fit.PyGlobalFitting()

fit_instance.Initialize()

initial_parameters = fit_instance.GetInitialParameters()
parameters = tf.Variable(initial_parameters, dtype=tf.float64, name='parameters')

def chi2_wrapper(params):
    return tf.numpy_function(lambda x: fit_instance.Chi2(x.tolist()), [params], tf.float64)

def value_and_gradients_fn(x):
    with tf.GradientTape() as tape:
        tape.watch(x)
        loss = chi2_wrapper(x)

    def numerical_grad(x_val, epsilon=0.005):
        grads = []
        x_val = x_val.numpy()
        for i in range(len(x_val)):
            x1 = x_val.copy()
            x2 = x_val.copy()
            x1[i] += epsilon
            x2[i] -= epsilon
            f1 = fit_instance.Chi2(x1.tolist())
            f2 = fit_instance.Chi2(x2.tolist())
            grads.append((f1 - f2) / (2 * epsilon))
        return tf.convert_to_tensor(grads, dtype=tf.float64)

    grad = tf.py_function(func=numerical_grad, inp=[x], Tout=tf.float64)
    grad.set_shape(x.shape)

    return loss, grad

for i in range(fit_instance.GetLFit()):

    print(f"Starting {i + 1} Fit:")

    fit_instance.ResetFit();

    results = tfp.optimizer.lbfgs_minimize(
        value_and_gradients_function=value_and_gradients_fn,
        initial_position=tf.convert_to_tensor(initial_parameters, dtype=tf.float64),
        max_iterations=1000
    )

    optimized_parameters = result.position.numpy().tolist()[0]
    fit_instance.Finalize(optimized_parameters, optimized_parameters) # this algorithm doesn't return the uncertainty of parameters

    fit_instance.UpdateParameterCentral()

    initial_parameters = fit_instance.GetInitialParameters()

    if abs(fit_instance.DeltaChi2()) < 0.1:
        break

print("Fitting done!")

