import matplotlib.pyplot as plt
import matplotlib
import numpy as np
import time
import cell_model
import cell_model_cpp

def run_model(n):
    print('running with n = {}'.format(n))

    # mean and standard deviation of the initial positions of the cells
    mu, sigma = 0.5, 0.05

    # set the maximum timestep allowed as fraction of the average diffusion step
    timestep_ratio = 0.23
    size = 0.02
    max_dt = (0.23 * size)**2 / 4.0

    # end time for the simulation
    end_time = 0.01

    # number of output steps
    nout = 10
    integrate_time = end_time/nout

    # create vectorised simulation
    x = np.random.normal(mu, sigma, n)
    y = np.random.normal(mu, sigma, n)
    sim = cell_model.Simulation(x, y, size, max_dt)
    sim.calculate_interactions = True

    # create wrapped cpp functions simulation
    sim_cpp1 = cell_model.Simulation_cpp(x, y, size, max_dt)
    sim_cpp1.calculate_interactions = True

    # create wrapped cpp class simulation
    x = cell_model_cpp.VectorDouble(x)
    y = cell_model_cpp.VectorDouble(y)
    sim_cpp2 = cell_model_cpp.Simulation(x, y, size, max_dt, 0)


    start_time = time.perf_counter()
    sim.integrate(integrate_time)
    end_time = time.perf_counter()
    sim_time = end_time - start_time

    start_time = time.perf_counter()
    sim_cpp1.integrate(integrate_time)
    end_time = time.perf_counter()
    sim_cpp1_time = end_time - start_time

    start_time = time.perf_counter()
    sim_cpp2.integrate(integrate_time)
    end_time = time.perf_counter()
    sim_cpp2_time = end_time - start_time

    return sim_time, sim_cpp1_time, sim_cpp2_time


if __name__ == "__main__":


    number_of_cells = np.array([10**i for i in np.linspace(2,3.5,10)])
    time_vectorised = np.empty(len(number_of_cells))
    time_cpp_function = np.empty(len(number_of_cells))
    time_cpp_class = np.empty(len(number_of_cells))
    for i,n in enumerate(number_of_cells):
        (time_vectorised[i], time_cpp_function[i], time_cpp_class[i]) = run_model(int(n))

    plt.figure()
    plt.loglog(number_of_cells, time_vectorised, label='vectorised')
    plt.loglog(number_of_cells, time_cpp_function, label='cpp functions')
    plt.loglog(number_of_cells, time_cpp_class, label='cpp class')
    plt.loglog(number_of_cells, 1e-5*number_of_cells**(3.0/2.0), label='N', ls='--')
    plt.loglog(number_of_cells, 1e-5*number_of_cells**2, label='N^2', ls='--')
    plt.xlabel('N')
    plt.ylabel('Execution time')
    plt.legend()
    plt.savefig('timing.png')


