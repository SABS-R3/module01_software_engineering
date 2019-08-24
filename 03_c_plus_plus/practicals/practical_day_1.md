---
title:  Introduction to C++
geometry: margin=3cm
urlcolor: blue
link-citations: true
---


# Practical 1 (Lectures 1-2)

Unless specified, either use Compiler Explorer (https://gcc.godbolt.org/), CLion
(https://www.jetbrains.com/clion/), or your preferred C++ toolchain.

When you are completing these questions, you may prefer:

- one function per question, with the `main()` function only calling the 
  function you are testing (when you are used to writing functions)
- every question in one `main()` function, perhaps commenting out what you are 
  not currently working on.


# Compilation

1. Create a "hello world" program, and check that it compiles and runs:
  - On Compiler Explorer
  - Using CLion

# Types and Flow Control

1. Create and assign values to at least one variable of type `int`, `unsigned`, `float`, `double`, `char` and `std::string`.
1. See what happens when you assign the value `-1` to a variable of type `unsigned`.
1. See what happens when you assign the value `1.23` to a variable of type `int`.
1. Generate a uniformly-distributed random number between -1 and 1.
1. Create two `double` variables $x$ and $y$. Set $x=0.3$ and $y=0.4$ and calculate 
   $r = \sqrt{x^2 + y^2}$. Write the result $r$ to the console using `std::cout`.
1. Code up another estimator for $\pi$ by calculating the sum of the reciprocals 
   of square numbers (The Basel problem) for $N$ terms, which converges to 
   $\pi^2/6$ for large enough $N$.

   $$
   S = \sum_{n=1}^{n=N} \frac{1}{n^2} \rightarrow \frac{\pi^2}{6}
   $$
1. Generate $N$ uniform random numbers $x_i$ and $y_i$ between -1 and 1. Count 
   the number of points where $\sqrt{x_i^2 + y_i^2} < 1$, and use this to 
   estimate the value of $\pi$.
1. Code up the [Gauss-Legendre algorithm
   ](https://en.wikipedia.org/wiki/Gauss%E2%80%93Legendre_algorithm)  for 
   estimating $\pi$, which has quadratic convergence.

# Pointers, references and functions

1. Getting used to pointers and references:
    (a) Declare a `double` called `d` with the value `5.0`
    (a) Create a pointer to a double (`double*`) called `p_d` and assign it the address of `d`
    (a) Print out `d` and `p_d`. What does the value of `p_d` mean?
    (a) Create a new double and assign it the value `1.0 + d`
    (a) Create a new double and assign it the value `1.0 + *p_d`
    (a) Print out those two new variables

1. Writing a function:
    (a) Write a function that does anything you like. Declare the function prototype above `main`, and define the function below `main`.
    (a) Delete the prototype, and move the definition above `main`. It should still work as expected.

1. Write code that sends the address of an integer to a function that prints out the value of the integer. Change the value of the integer and verify that the original integer is updated outside your function.

1. Write a function that accepts two floating point numbers, and swaps the values of these numbers.
    (a) Write this function using pointers
    (a) Write this function using references


# Array and Vectors

1. The $p$-norm of a vector $\mathbf{v}$ of length $n$ is given by

   $$
   \|\mathbf{v}\|_p = \left( \sum_{i=1}^n |v_i|^p \right)^{1/p}
   $$

   where $p$ is a positive integer. Write a function to calculate the $p$-norm of a given `std::array<double,3>`, where $p$ takes the default value 2. Print the
   result to `std::cout` in a nicely formatted way, for example: `result = [1, 2, 3]`.

1. Now write the same $p$-norm function as a C++ lambda function for the specific case of a `std::array<double,3>`. Try inputting $p$ to the lambda function as
   (a) an argument, or
   (b) a capture variable.

1. Overload the $p$-norm function in Q4 to take a `std::vector<double>`. Loop over the vector using
   (a) an index-based loop,
   (b) a range-based loop,
   (c) an iterator-based loop,
   (d) the `std::accumulate` STL algorithm (in the `<numeric>` header)

1. Write a function multiply that may be used to multiply two matrices, given their sizes. You are free to choose any type to represent your matrices, but you might want to try either a `std::vector<double>` or a `std::vector<std::vector<double>>`

# Extension (for those with previous C++ experience)

1. Implement the same matrix multiply in Eigen (<http://eigen.tuxfamily.org>) and time how long your function takes compared with Eigen for a relatively large matrix (hint: look up `std::chrono::high_resolution_clock`, <http://www.cplusplus.com/reference/chrono/high_resolution_clock/now>). Try to improve the speed of your function as much as you can in the allotted time (hint: google ''matrix multiply optimisation", and try tiling or blocking techniques)
