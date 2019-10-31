---
title: Optimisation 4 - Parallel execution
author: Martin Robinson
date: Oct 2019
urlcolor: blue
---

# Levels of parallelism

Can execute code in parallel at many different levels:

1. At the instruction level- Single Instruction Multiple Data (SIMD)
1. Within the same process/program - Shared memory parallism - e.g. OpenMP
1. Between different processes on the same computer - Non-shared memory - e.g. Python 
   multiprocessing 
1. Between separate machines - Distributed computing - e.g. Message Passing Interface 
   (MPI)

This lecture will focus on the middle two.


# OpenMP

- OpenMP is a set of compiler directives (`#pragma omp ...`) that make writing a shared 
  memory parallel program significantly easier
- Supported by most modern compilers (GCC $\ge$ v6.1, Clang++ $\ge$ 3.9, Intel $\ge$ 
  17.0, Microsoft Visual C++ $\ge$ 2005) 
- OpenMP uses fork and join model:

![](lectures/figs/Fork_join.svg)

# Core elements

![](lectures/figs/OpenMP_language_extensions.svg)

# creating threads - parallel regions

- Use the `parallel` directive to create a parallel region

```cpp
#pragma omp parallel
```

- program flow splits into $N$ threads ($N$ set by environment variable OMP_NUM_THREADS, 
  `omp_set_num_threads()` function, or `num_threads` directive)
- compile using `-fopenmp` for GCC or Clang++, `/openmp` for Visual Studio, or `-openmp` 
  for intel

---------------------

```cpp
#include <iostream>
#include <omp.h>

int main(void)
{
    #pragma omp parallel num_threads(2)
    {
      const int id = omp_get_thread_num();
      const int n = omp_get_num_threads();
      std::cout << "Hello world. I am thread "<< id
                << " of "<< n <<std::endl;
    }
    return 0;
}
```

# Shared versus private variables

- variables declared before parallel region are shared
- those declared within parallel regions are private

```cpp
int a; // a is shared between threads

#pragma omp parallel
{
    int b; // b is private to each thread
}
```

# Shared versus private variables

- can be explicitly specified using `shared`, `private` directives

```cpp
int a; // a is shared between threads
int b; // b is private to each thread

#pragma omp parallel default(none) shared(a) private(b)
{
}
```

# Syncronisation - critical

- Critical regions are executed by one thread at a time

```cpp
#pragma omp parallel
```

--------------------------


```cpp
#include <iostream>
#include <omp.h>

int main(void)
{
    #pragma omp parallel
    {
      const int id = omp_get_thread_num();
      const int n = omp_get_num_threads();
      #progam omp critical
      {
      std::cout << "Hello world. I am thread "<< id <<" of "<< n <<std::endl;
      }
    }
    return 0;
}
```

# Syncronisation - atomic

- `atomic` directives enable you to serialise a single instruction

```cpp
int counter = 0;
#pragma omp parallel 
{
    ...
    #pragma omp atomic
    counter++
}
std::cout << counter << " threads in total"<<std::endl;
```

# Loop constructs

- Often you are looking to run a specific for loop in parallel
- OpenMP provides the `omp parallel for` directive to do this automatically

```cpp
std::vector<double> a(n), b(n);

#pragma omp parallel for
for (int i = 0; i < n; ++i) {
  a[i] += b[i];
}
```

# Loop constructs

- Up to the programmer to ensure that loop iterations are **independent**
- This will fail, why?

```cpp
const int stride = 5;
std::vector<double> a(n), b(stride*n);
int j = 0;
#pragma omp parallel for
for (int i = 0; i < n; ++i) {
  j += stride
  a[i] += b[j];
}
```

# Reductions

- The atomic counter above was an example of a reduction, these is a commonly used 
  pattern in programming, and easily parallelised (faster than using atomics).
- OpenMP provides reductions for these operators: `+, -, *, &, |, ^, &&, ||`
- If `op` is the operator and `x` the variable, then must use `x = x op expr`, `x = expr 
  op x` or `x op= expr` within the parallel region

```cpp
std::vector<double> a(n);
double sum = 0;
#pragma omp parallel for reduction(+: sum)
for (int i = 0; i < n; ++i) {
  sum += a[i];
}
```

# More information on OpenMP

- OpenMP specificiation <https://www.openmp.org/>
- Many online tutorials, books etc. See resources tab in link above for examples




