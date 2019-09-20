import numpy as np
import cell_model_cpp

class Simulation_cpp:
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
        cell_model_cpp.boundaries(self.xn, self.yn, dt)

    def diffusion(self, dt):
        """
        Perform a diffusion step for all cells

        Updates self.xn and self.yn with the new position of the cells
        """
        cell_model_cpp.diffusion(self.xn, self.yn, dt)

    def interactions(self, dt):
        """
        Calculates the pairwise interactions between cells, using a soft exponential
        repulsive force

        Uses self.x and self.y as the current positions of the cells

        Updates self.xn and self.yn with the new position of the cells
        """
        cell_model_cpp.interactions(self.xn, self.yn, self.x, self.y, dt, self.size)

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
        for i in range(n):
            self.step(self.max_dt)
        final_dt = period - self.max_dt*n
        if final_dt > 0:
            self.step(final_dt)
