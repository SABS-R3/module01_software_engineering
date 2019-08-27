---
title: Numpy vectorisation and wrapping C++
geometry: margin=3cm
urlcolor: blue
link-citations: true
---

\newcommand{\ud}{\mathrm{d}}
\newcommand{\bfx}{{\bf x}}
\newcommand{\bfp}{{\bf p}}
\newcommand{\bfX}{{\bf X}}


# Cell model

This practical uses a model of cell diffusion and excluded volume interaction. It is not
required that you understand the details of the model, as it is implemented for you in
the file `excluded_volume_diffusion.py`. The purpose of this practical is to profile and
increase the efficiency of the model using numpy vectorisation and C++. The details of
the model are provided below.

The model consists of a set of $N$ cells in a periodic unit square domain. Let
$\bfX_i(t)$ denote the position of the $i$th particle in $\Omega \subset \mathbb R^2$.
For each particle $i$, the motion through space is described by a stochastic
differential equation (SDE).


$$
\ud \bfX_i(t) = \sqrt{2 D_\alpha} \ud {\bf W}_i(t) - \sum_{j\ne i} \nabla_i u(\| \bfX_i(t) - \bfX_j(t) \|) \ud t,
$$

where $D=1$ is the diffusion coefficient of the cells, and $\nabla_i$ denotes the
gradient with respect to $\bfX_i$. The interaction potential $u$ may be a soft potential
incorporating effects such as size exclusion by cells and cell-cell adhesion. In this
case we use the soft exponential potential.

The standard way to numerically integrate the SDE is to use a fixed time-step $\Delta t$
and a Euler--Maruyama discretisation, resulting in the time-stepping scheme:

$$ 
\bfX_i(t+ \Delta t) = \bfX_i(t) + \sqrt{2D_\alpha \Delta t} \xi_i - \sum_{j\ne i} \nabla_i u(\| \bfX_i(t)
  - \bfX_j(t) \|) \Delta t, 
$$

where $\xi_i$ is a two-dimensional normally distributed random variable with zero mean
and unit variance.


# Numpy Vectorisation


1. Examine the python code in `excluded_volume_diffusion.py`. Install the requirements
   for the code using `pip install -r requirements.txt`, and run it using `python
   excluded_volume_diffusion.py`.

1. Vectorise the code in `Simulation.diffusion()`, using only a single call to
   `np.random.randn`. How does this improve the profiled time of this function? What is
   the memory cost of vectorising this code?

1. Vectorise the code in `Simulation.boundaries()`, using the `np.where()` function.
   Again make an estimate of the memory cost involved.

1. Now include interactions in the simulation by setting `sim.calculate_interactions =
   True`. The double loop in `Simulations.interactions()` is now a significant
   computational cost. Vectorise this code so that there are no loops remaining. What is
   the memory cost and how does it scale with the number of cells $N$? How many
   particles can you simulate before your computer runs out of RAM?


# Wrapping C++

Using C++ you can improve the performance of the simulation without the RAM cost of
vectorisation. You can also parallelise your code more easily, and have access to a
wider array of high performance libraries.

Start from the pybind11 template project provided in X. Again we will start with the
non-interacting case and deal with interactions at the end.

1. Write C++ function replacements for `Simulation.diffusion()` and
   `Simulation.boundaries()`, with signatures:

```cpp 
void diffusion(std::vector<double>& xn, std::vector<double>& yn, const double dt);
void boundaries(std::vector<double>& xn, std::vector<double>& yn, const double dt);
```

1. Write pybind11 wrappers for these functions and call them from your python
   simulation. Ensure that the output of the simulation is unchanged. How much speed-up
   can you obtain over your vectorised numpy code? What is the RAM cost?

1. Now write a C++ function replacement for `Simulation.interactions()`
   
```cpp 
void interactions(std::vector<double>& xn, std::vector<double>& yn, 
                  const std::vector<double>& x, const std::vector<double>& y,
                  const double dt, const double size);
```

1. Write a pybind11 wrapper for `interactions` and use it in your python code. Measure
   the speed-up obtained and take a note of the RAM usage scales with larger $N$. 
   
1. Your computational cost is no longer bounded by RAM, but by the cost of evaluating
   $N^2$ interactions. There are many different ways of speeding this up in C++, one of
   which is using a hash map (via the the C++ `std::unordered_map` container) to only
   consider nearby cell interactions. This has been implemented for you in
   `Simulation.cpp`, which reimplements the `Simulations` class in C++. Wrap this C++
   class so that you can use it from Python, and use it in your simulation loop. What is
   the cost of evaluating the interactions now, and how does this scale with $N$?
