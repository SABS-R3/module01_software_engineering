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

This practical uses the same model of cell diffusion and excluded volume interaction as 
the previous day. Please see the previous problem sheet if you need a reminder of the 
model.

# Wrapping C++

In the previous practical you used Cython to improve the performance of the simulation, 
which generates optimised C or C++ code from Python-like syntax. An alternative approach 
is to write C++ code directly, and use a wrapper to call this from Python. Below you 
will use `pybind11` to re-implement the `Simulation` class in C++.

The `cell_model` module already has a template `pybind11` project for you to use. Again
we will start with the non-interacting case and deal with interactions at the end.

1. In the provided files `src/Functions.cpp`, write C++ function replacements for
   `Simulation.diffusion()` and `Simulation.boundaries()`, with signatures:

```cpp 
void diffusion(std::vector<double>& xn, std::vector<double>& yn, const double dt);
void boundaries(std::vector<double>& xn, std::vector<double>& yn, const double dt);
```

1. Write pybind11 wrappers for these functions in the files `src/python_wrapper.cpp` and
   call them from your python simulation. Ensure that the output of the simulation is
   unchanged. How much speed-up can you obtain over your vectorised numpy code? What is
   the RAM cost?

1. Now write a C++ function replacement for `Simulation.interactions()`
   
```cpp 
void interactions(std::vector<double>& xn, std::vector<double>& yn, 
                  const std::vector<double>& x, const std::vector<double>& y,
                  const double dt, const double size);
```

1. Write a pybind11 wrapper for `interactions` and use it in your python code. Measure
   the speed-up obtained (plot the time taken versus $N$) and take a note of how the RAM
   usage scales with larger $N$. 
   
1. Your computational cost is no longer bounded by RAM, but by the cost of evaluating
   the cell-cell interactions. There are many different ways of speeding this up in C++,
   one of which is using a hash map (via the the C++ `std::unordered_map` container) to
   only consider nearby cell interactions. This has been implemented for you in
   `src/Simulation.cpp`, which reimplements the `Simulations` class in C++. Wrap this
   C++ class so that you can use it from Python, and use it in your simulation loop. How
   will you get the cell positions from this class back to python? What is the cost of
   evaluating the interactions now, and how does this scale with $N$ (plot this)?


# Python parallel programming

The cell model provided is a stochastic model, and running it provides a single sample 
from the probability distribution defined over its outputs (i.e. the entire set of cell 
positions). In order to get access to this distribution, it is required to take many 
independent samples 

1. 


