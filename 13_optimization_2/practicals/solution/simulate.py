import matplotlib.pyplot as plt
import matplotlib
import numpy as np
import time
import cProfile
import cell_model

if __name__ == "__main__":

    # np.seterr(divide='ignore', invalid='ignore')

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

    # number of output steps
    nout = 10
    integrate_time = end_time/nout

    # create simulation
    x = np.random.normal(mu, sigma, n)
    y = np.random.normal(mu, sigma, n)
    sim = cell_model.Simulation(x, y, size, max_dt, 0)

    # Set to True to include excluded volume interactions
    sim.calculate_interactions = True

    # profile a single call to integrate
    cProfile.run('sim.integrate(integrate_time)', sort='cumulative')

    # now run the main simulation loop and visualise the positions of the cells at each
    # output step
    time_for_simulation = 0.0
    f = plt.figure()
    for i in range(nout):
        # increment simulation
        start_time = time.perf_counter()
        sim.integrate(integrate_time)
        end_time = time.perf_counter()
        time_for_simulation += end_time - start_time

        # plot
        f.clear()
        circles = [plt.Circle((xi,yi), radius=size) for xi,yi in
                zip(sim.x,sim.y)]
        c = matplotlib.collections.PatchCollection(circles)
        f.gca().add_collection(c)
        f.savefig('cells_{}.png'.format(i))

    print('finished simulation, time taken (excluding plotting) was {}'.format(
        time_for_simulation))
