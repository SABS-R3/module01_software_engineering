---
title: Optimisation 2 - Wrapping C++ and Python parallel programming
geometry: margin=3cm
urlcolor: blue
link-citations: true
---

\newcommand{\ud}{\mathrm{d}}
\newcommand{\bfx}{{\bf x}}
\newcommand{\bfp}{{\bf p}}
\newcommand{\bfX}{{\bf X}}


# Cell model

This practical uses the same model of cell diffusion and excluded volume interaction as 
the previous day. Please see the previous problem sheet if you need a reminder of the 
model.

# Wrapping C++

In the previous practical you used Cython to improve the performance of the simulation, 
which generates optimised C or C++ code from Python-like syntax. An alternative approach 
is to write C++ code directly, and use a wrapper to call this from Python. Below you 
will use `pybind11` to re-implement the `Simulation` class in C++.

The `cell_model` module already has a template `pybind11` project for you to use.

1. In the provided files `src/Functions.cpp`, write C++ function replacements for
   `Simulation.diffusion()` and `Simulation.boundaries()`, with signatures:

```cpp 
void diffusion(py::array_t<double> xn, py::array_t<double> yn, const double dt);
void boundaries(py::array_t<double> xn, py::array_t<double> yn, const double dt);
```

1. Write pybind11 wrappers for these functions in the files `src/python_wrapper.cpp` and
   call them from your python simulation. Ensure that the output of the simulation is
   unchanged. How much speed-up can you obtain over your vectorised numpy code? What is
   the RAM cost?

1. Now write a C++ function replacement for `Simulation.interactions()`
   
```cpp 
void interactions(py::array_t<double> xn, py::array_t<double> yn,
                  const py::array_t<double> x, const py::array_t<double> y,
                  const double dt, const double size);
```

1. Write a pybind11 wrapper for `interactions` and use it in your python code. Measure
   the speed-up obtained (plot the time taken versus $N$).
   
1. Your computational cost is no longer bounded by RAM, as was the case for the 
   vectorised code, but by the cost of evaluating the cell-cell interactions. There are 
   many different ways of speeding this up in C++, one of which is using a hash map (via 
   the the C++ `std::unordered_map` container) to only consider nearby cell 
   interactions. This has been implemented for you in `src/Simulation.cpp`, which 
   reimplements the `Simulations` class in C++. Wrap this C++ class so that you can use 
   it from Python, and use it in your simulation loop. How
   will you get the cell positions from this class back to python? What is the cost of
   evaluating the interactions now, and how does this scale with $N$ (plot this)?


# Python parallel programming

The cell model provided is a stochastic model, and running it only provides a single 
sample from the probability distribution defined over its outputs (i.e. the entire set 
of cell positions). In order to get access to this distribution, we can take many 
independent samples (i.e. run many simulations) in order to build up statistics of the 
quantities of interest. We can easily run these in parallel using the Python 
multiprocessing library.

Your goal is to use the multiprocessing library to run, in parallel, $N$ simulations of 
the cell model, each with a different random seed $s_i$ for all $i=1..N$. 

1. Write a function that takes two integer arguments $a$ and $b$, which are integers 
   representing a range of seed values $s_i$ for all $i=a..b$. This function will run 
   $b-a$ simulations, and calculate 2D histograms at each output time point of the 
   number of cells within each spatial bin. These histograms are then averaged over the 
   $b-a$ simulations that are run.
1. Using this function, and the `map` function from the multiprocessing library, run all 
   the simulations from $i=1..N$ in parallel using $m$ different processes. Calculate 
   the average histogram over all $N$ random realisations of your model.
1. Plot the averaged histograms at each time point using Matplotlib. You might find it 
   useful to save the results from the previous step to a file using the `pickle` 
   library, and then load this to generate your plot in order to avoid re-running the 
   simulations each time.
