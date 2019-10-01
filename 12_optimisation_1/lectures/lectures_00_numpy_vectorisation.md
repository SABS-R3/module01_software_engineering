% Optimisation - speeding up your code
% Martin Robinson
% Nov 2019

# Optimisation

- The Zen of Python (PEP 20):
  - Beautiful is better than ugly.
  - Explicit is better than implicit.
  - Simple is better than complex.
  - Complex is better than complicated.

- Python's design philisophy emphasises code readability and simplicity over performance

- Often in scientific computing we wish to improve the performance of our code

# What to optimise - profiling

Donald Knuth (1974)
"We should forget about small efficiencies, say about 97% of the time: premature 
optimization is the root of all evil. Yet we should not pass up our opportunities in 
that critical 3%"

- Design and implement your code first! Then you can measure where the program spends 
  most of its time (i.e. "that critical 3%") and optimise them accordingly.

# The cProfile module

- part of the standard library 
  - <https://docs.python.org/3.2/library/profile.html>
- Implements *Deterministic Profiling*. Monitors the entry and exit from each function. 
  Gathers statistics on, e.g., number of times called and time spent in every function 
  called

-----------------------------


```python
import time
import cProfile

def slow_function():
  time.sleep(1)

def fast_function():
  time.sleep(0.1)

def profiled_program():
  slow_function()
  fast_function()

cProfile.run('profiled_program()')
```

----------------------------

```python 
%%prun -s cumulative
profiled_program()
```

# The timeit module

- Deterministic profiling adds overhead to the code being profiled, not useful for 
  benchmarking
- Use a timer instead. Python has the `timeit` module
  - <https://docs.python.org/3.6/library/timeit.html>
- `timeit` uses the `time.perf_counter` timer internally
  - <https://docs.python.org/3.6/library/time.html#time.perf_counter>

--------------------

```python
import timeit

timeit.timeit('fast_function()')
timeit.timeit('slow_function()')
```

```python
import time
start_time = time.perf_counter()
fast_function()
end_time = time.perf_counter()
print('fast function took {} seconds'.format(end_time-start_time))
```

---------------------

```python
%%timeit
fast_function()
```

# Methods for optimising Python code 

1. Rewrite using data structures / algorithms
  - most of the (time-consuming) code you write has already been implemented as commonly 
    used data structures and algorithms, take the time to know these and how to use 
    them.
1. Use a high-performance library
  - Many (most?) python libraries are written in a faster compiled language (e.g. 
    C/C++/fortran), offering significant speed-up
  - For scientific programming, [`numpy`](https://numpy.org/) and 
    [`scipy`](https://www.scipy.org/) offer many possibilities
1. "Compile" Python code to a low-level language (usually C/C++).
  - [`cython`](https://cython.org/): add static type declarations to your code and 
    compile to C or C++
  - [`numba`](https://numba.pydata.org/): automatically compiles python code directly to 
    machine code.
  - [`theano`](http://deeplearning.net/software/theano/): compiles mathematical 
    expressions involving numpy-like arrays to C. Largely replaced now by 
    [`tensorflow`](https://www.tensorflow.org/) and [`pytorch`](https://pytorch.org/).
1. Write your code in a low-level language and call it from Python
  - Many "wrapper" libraries exist, such as [`boost 
    python`](https://www.boost.org/doc/libs/1_70_0/libs/python/doc/html/index.html) or 
    [`pybind11`](https://github.com/pybind/pybind11) for C++, or 
    [`swig`](http://www.swig.org) for C/C++, and 
    [`f2py`](https://docs.scipy.org/doc/numpy/f2py/) for fortran
1. Parallise your Python code
  - Python is difficult to run in parallel due to the Global Interpreter Lock (GIL). 
    Within a single process different python threads are restricted to run in serial.
  - However, it is possible to run many communicating python processes using the 
    `multiprocessing` module
    
# Numpy vectorisation

- each numpy operation is written in optimised C, and compiled to machine code. 
- speed up your python loops by converting them to numpy operations where possible
- this process is known as *vectorisation*, also a big issue in Matlab

----------------------

```python
def python_sum(array):
  s = 0
  for i in range(len(array)):
    s += array[i]
  return s

def numpy_sum(array):
  return np.sum(array)

n = 1000
%timeit python_sum(np.ones(n))
%timeit numpy_sum(np.ones(n))
```

# examples - array creation

- numpy has many functions for generating arrays

```python
def python_create():
  return [i**2 for i in range(n)]

def numpy_create():
  return np.arange(0,n,1)**2

%timeit python_create()
%timeit numpy_create()
%memit python_create()
%memit numpy_create()

```

# examples - v_i + a * exp(v_i)

- replace single loops over arrays into the equivilent number operations

```python
a = 1.5
def python_expr(array):
  for i, x in enumerate(array):
    array[i] += a * math.exp(x)
  return array

def numpy_expr(array):
  return array + a * np.exp(array)

%timeit python_expr()
%timeit numpy_expr()
%memit python_expr()
%memit numpy_expr()
```

# examples - broadcasting

- Using the numpy broadcasting rules can help when vectorising

```python
a = [1.5, 2.5]

def python_2d_expr(array):
  for i in range(array.shape[0]):
    for j in range(array.shape[1]):
      array[i, j] += a[j] * math.exp(array[i, j])
  return array

np_a = np.array(a)

def numpy_2d_expr(array):
  return array + np_a * np.exp(array)

%timeit python_2d_expr()
%timeit numpy_2d_expr()
%memit python_2d_expr()
%memit numpy_2d_expr()
```

# examples - more broadcasting - double loops

- Even double loops can be vectorised with appropriate broadcasting

```python
a = [1.5, 2.5, 3.5, 4.5]
b = [4.5, 3.5, 2.5, 1.5]

def python_dbl_loop(array):
  for i in range(array.shape[0]):
    for j in range(array.shape[1]):
      array[i, j] += math.exp(- (a[i] + b[j])) 
      
  return array

np_a = np.array(a)
np_b = np.array(b)

def numpy_dbl_loop(array):
  return array + np.exp(a + np.transpose(b))

%timeit python_dbl_loop()
%timeit numpy_dbl_loop()
%memit python_dbl_loop()
%memit numpy_dbl_loop()
```

# The practical - speeding up a cell model

The practical exercises over the next 2 days revolve around speeding up a Python 
implementation of a individual-based model of diffusing and interacting cells.

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

----------------------------

The simple method to numerically integrate the SDE is to use a fixed time-step $\Delta 
t$ and a Euler--Maruyama discretisation, resulting in the time-stepping scheme:

$$ 
\bfX_i(t+ \Delta t) = \bfX_i(t) + \sqrt{2D_\alpha \Delta t} \xi_i - \sum_{j\ne i} \nabla_i u(\| \bfX_i(t)
  - \bfX_j(t) \|) \Delta t, 
$$

where $\xi_i$ is a two-dimensional normally distributed random variable with zero mean
and unit variance.


# Implementation

[walk through code here]


