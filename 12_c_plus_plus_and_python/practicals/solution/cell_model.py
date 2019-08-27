import numpy as np
import matplotlib.pyplot as plt
import matplotlib
import time
import cProfile


class Simulation:
    def __init__(self, x, y, size, max_dt):
        """
        Creates a new simulation objects that implements the cell model with diffusion
        and excluded volume interactions. Cells are defined on a unit square domain and
        periodic boundary condtions are implemented

        Parameters
        ----------

        x: np.ndarray
            array of x positions of the cells

        y: np.ndarray
            array of y positions of the cells. Must be same length as x

        size: float
            size of cells

        max_dt: float
            maximum timestep for the simulation

        """
        self.x = x
        self.y = y
        self.max_dt = max_dt

        self.xn = np.empty_like(x)
        self.yn = np.empty_like(y)

        self.size = size

        self.calculate_interactions = False

    def boundaries(self, dt):
        """
        Any cells that are over the boundary of the domain are translated to the
        opposite side of the domain

        Updates self.xn and self.yn with the new position of the cells
        """
        self.xn = np.where(self.xn < 0.0, - self.xn, self.xn)
        self.xn = np.where(self.xn > 1.0, self.xn - 1.0, self.xn)
        self.yn = np.where(self.yn < 0.0, - self.yn, self.yn)
        self.yn = np.where(self.yn > 1.0, self.yn - 1.0, self.yn)

    def diffusion(self, dt):
        """
        Perform a diffusion step for all cells

        Updates self.xn and self.yn with the new position of the cells
        """
        r = np.random.randn(2, len(self.xn))
        self.xn += np.sqrt(2.0 * dt) * r[0, :]
        self.yn += np.sqrt(2.0 * dt) * r[1, :]

    def interactions(self, dt):
        """
        Calculates the pairwise interactions between cells, using a soft exponential
        repulsive force

        Uses self.x and self.y as the current positions of the cells

        Updates self.xn and self.yn with the new position of the cells
        """
        n = len(self.x)
        dx = self.x.reshape((1, n)) - self.x.reshape((n, 1))
        dy = self.y.reshape((1, n)) - self.y.reshape((n, 1))
        r = np.sqrt(dx**2 + dy**2)
        self.xn += np.nansum((dt/self.size) * np.exp(-r/self.size) * dx / r, axis=1)
        self.yn += np.nansum((dt/self.size) * np.exp(-r/self.size) * dy / r, axis=1)

    def step(self, dt):
        """
        Perform a single time step for the simulation

        First the current positions of the cells are written to self.xn and self.yn,
        which will now represent the "next" position of the cells after the current
        time-step

        The self.interactions, self.diffusion and self.boundaries functions update the
        "next" position of the cells according to the cell-cell excluded volume
        interactions, the diffusion step and the boundaries respectivly

        Finally, the current position of the cells is set to the calculated "next"
        position, and the simulation is ready for a new time-step.

        """
        self.xn[:] = self.x
        self.yn[:] = self.y

        if self.calculate_interactions:
            self.interactions(dt)
        self.diffusion(dt)
        self.boundaries(dt)

        self.x[:] = self.xn
        self.y[:] = self.yn

    def integrate(self, period):
        """
        integrate over a time period given by period (float).
        """

        n = int(np.floor(period / self.max_dt))
        print('integrating for {} steps'.format(n+1))
        for i in range(n):
            self.step(self.max_dt)
        final_dt = period - self.max_dt*n
        if final_dt > 0:
            self.step(final_dt)

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
    sim = Simulation(x, y, size, max_dt)

    # Set to True to include excluded volume interactions
    sim.calculate_interactions = False

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

