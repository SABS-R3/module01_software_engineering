import matplotlib.pyplot as plt
import matplotlib
import numpy as np
import time
import cProfile
import cell_model_cpp
from multiprocessing import Pool
import pickle
import os


# number of output steps
nout = 10

# number of histogram bins
bins = (20, 20)

def model(start_end):
    (start, end) = start_end
    print('running samples {} to {}'.format(start, end))

    # create histogram
    hist = np.zeros(bins + (nout,))

    # number of cells
    n = 100

    # mean and standard deviation of the initial positions of the cells
    mu, sigma = 0.5, 0.05

    # set the maximum timestep allowed as fraction of the average diffusion step
    timestep_ratio = 0.23
    size = 0.02
    max_dt = (0.23 * size)**2 / 4.0

    # end time for the simulation
    end_time = 0.01

    for seed in range(start, end):
        print('running sample {}'.format(seed))

        # number of output steps
        integrate_time = end_time/nout

        # create simulation
        np.random.seed(seed)
        x = cell_model_cpp.VectorDouble(np.random.normal(mu, sigma, n))
        y = cell_model_cpp.VectorDouble(np.random.normal(mu, sigma, n))
        sim = cell_model_cpp.Simulation(x, y, size, max_dt, seed)

        # now run the main simulation loop and visualise the positions of the cells at each
        # output step
        samples = np.empty((n, 2))
        for i in range(nout):
            # increment simulation
            sim.integrate(integrate_time)

            # extract cell positions
            for j, p in enumerate(sim.get_positions()):
                samples[j, :] = [p.x, p.y]

            # update histogram
            hist[:, :, i] += np.histogramdd(samples, bins)[0]

        print('finished sample {}'.format(seed))

    return hist / (end-start)


if __name__ == "__main__":
    n_processes = 5
    n_samples = 100

    # Note: n_samples should be evenly divisible by n_processes
    n_samples_per_process = n_samples // n_processes

    # cache simulation results using pickle
    pickle_filename = 'result.pickle'
    if os.path.exists(pickle_filename):
        print('reading from {}'.format(pickle_filename))
        result = pickle.load(open(pickle_filename, 'rb'))
    else:
        # run all samples, accumulate the result
        with Pool(n_processes) as p:
            ranges = [(start, start + n_samples_per_process)
                      for start in range(0, n_samples, n_samples_per_process)
                      ]
            result = sum(p.map(model,ranges), np.zeros(bins + (nout,))) / n_processes


        pickle.dump(result, open(pickle_filename, 'wb'))


    f = plt.figure()
    vmin = np.min(result, axis=(0, 1, 2))
    vmax = np.max(result, axis=(0, 1, 2))
    for i in range(nout):
        f.clear()
        plt.imshow(result[:, :, i], vmin=vmin, vmax=vmax)
        f.savefig('histogram_{}.png'.format(i))


