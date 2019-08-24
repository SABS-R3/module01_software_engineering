import numpy as np
import matplotlib.pyplot as plt
import time
import cProfile

class Simulation:
    def __init__(self, x, y, size, max_dt):
        self.x = x
        self.y = y
        self.max_dt = max_dt

        self.xn = np.empty_like(x)
        self.yn = np.empty_like(y)

        self.size = size

        self.calculate_interactions = False


    def boundaries(self, dt):
        # (b) vectorise using np.where
        #for i in range(len(self.x)):
        #    if self.xn[i] < 0.0:
        #        self.xn[i] = 0.0 - self.xn[i]
        #    elif self.xn[i] > 1.0:
        #        self.xn[i] = self.xn[i] - 1.0
        #    if self.yn[i] < 0.0:
        #        self.yn[i] = 0.0 - self.yn[i]
        #    elif self.yn[i] > 1.0:
        #        self.yn[i] = self.yn[i] - 1.0

        self.xn = np.where(self.xn < 0.0, - self.xn, self.xn)
        self.xn = np.where(self.xn > 1.0, self.xn - 1.0, self.xn)
        self.yn = np.where(self.yn < 0.0, - self.yn, self.yn)
        self.yn = np.where(self.yn > 1.0, self.yn - 1.0, self.yn)

    def diffusion(self, dt):
        # (a) trivial vectorise
        #for i in range(len(self.x)):
        #    self.xn[i] += np.sqrt(2.0 * dt) * np.random.randn()
        #    self.yn[i] += np.sqrt(2.0 * dt) * np.random.randn()

        r = np.random.randn(2,len(self.xn))
        self.xn += np.sqrt(2.0 * dt) * r[0,:]
        self.yn += np.sqrt(2.0 * dt) * r[1,:]

    def interactions(self, dt):
        # (c) vectorise with a n^2 dx matrix
        #for i in range(len(self.x)):
        #    for j in range(len(self.y)):
        #        dx = np.array([self.x[i] - self.x[j], self.y[i] - self.y[j]])
        #        r = np.sqrt(np.sum(dx**2))
        #        if r > 0.0:
        #            dp = -(dt/self.size) * np.exp(-r/self.size) * dx / r
        #            self.xn[i] += dp[0]
        #            self.yn[i] += dp[1]

        #for i in range(len(self.x)):
        #    dx = np.array([self.x[i] - self.x, self.y[i] - self.y])
        #    r = np.sqrt(np.sum(dx**2, axis=0))
        #    dp = -(dt/self.size) * np.exp(-r/self.size) * dx / r
        #    step = np.sum(np.nan_to_num(dp, copy=False), axis=1)
        #    self.xn[i] += step[0]
        #    self.yn[i] += step[1]

        n = len(self.x)
        dx = self.x.reshape((1, n)) - self.x.reshape((n, 1))
        dy = self.y.reshape((1, n)) - self.y.reshape((n, 1))
        r = np.sqrt(dx**2 + dy**2)
        self.xn += np.nansum(-(dt/self.size) * np.exp(-r/self.size) * dx / r, axis=1)
        self.yn += np.nansum(-(dt/self.size) * np.exp(-r/self.size) * dy / r, axis=1)


    def step(self, dt):
        """ single time step """

        self.xn[:] = self.x
        self.yn[:] = self.y

        if self.calculate_interactions:
            self.interactions(dt)
        self.diffusion(dt)
        self.boundaries(dt)

        self.x[:] = self.xn
        self.y[:] = self.yn

    def integrate(self, period):
        """ integrate over a time period """

        n = int(np.floor(period / self.max_dt))
        print('integrating for {} steps'.format(n+1))
        for i in range(n):
            self.step(self.max_dt)
        final_dt = period - self.max_dt*n
        if final_dt > 0:
            self.step(final_dt)


if __name__ == "__main__":

    # np.seterr(divide='ignore', invalid='ignore')

    # setup
    n = 100
    mu, sigma = 0.5, 0.1  # mean and standard deviation
    x = np.random.normal(mu, sigma, n)
    y = np.random.normal(mu, sigma, n)
    timestep_ratio = 0.23
    size = 0.02
    max_dt = (0.23 * size)**2 / 4.0
    end_time = 0.01
    nout = 10
    integrate_time = end_time/nout
    max_dt
    sim = Simulation(x, y, size, max_dt)
    sim.calculate_interactions = True

    # profile the simulation
    cProfile.run('sim.integrate(integrate_time)', sort='cumulative')

    # run the main simulation loop
    time_for_simulation = 0.0
    f = plt.figure()
    for i in range(nout):
        start_time = time.perf_counter()
        sim.integrate(integrate_time)
        end_time = time.perf_counter()
        time_for_simulation += end_time - start_time
        f.clear()
        plt.scatter(sim.x, sim.y, sim.size)
        f.savefig('excluded_volume_visualisation{}.pdf'.format(i))
    print('finished simulation, time taken (excluding plotting) was {}'.format(time_for_simulation))
