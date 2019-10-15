% Introduction to C++ - pointers, references, functions
% Martin Robinson
% Oct 2019

# Pointers

A pointer that points to an object **represents the address** of the first byte in memory occupied by the object.

If a variable has been declared by

~~~Cpp
int total_sum;
~~~

then the address of total sum is given by `&total_sum`

`&total_sum` takes a constant value, because the address of total sum in the computer's memory was allocated when it was declared.

`&total_sum` is therefore a **constant pointer**.

-------------------

Variable pointers may be declared as follows

~~~Cpp
double* p_x;
int* p_i;
~~~

`p_x` is a variable pointer to a variable of type `double`{.Cpp}, `p_i` is a variable pointer to an integer.

Note that spacing can vary: `double* p_x`{.Cpp} and `double *p_x`{.Cpp} are equivalent.

If `p_x` and `p_y` are both to be declared as pointers this is done by

~~~Cpp
double *p_x, *p_y;
~~~

In the declaration

~~~Cpp
int *p_i, j;
~~~

`p_i` is a pointer to an integer, and `j` is an integer. It is generally clearer to declare each new pointer on a separate line.

-------------------

The contents of the memory that a pointer `p_x` points to is given by `*p_x`. For example,

~~~Cpp
double z = 3.0;
double* p_z = &z;      // store the address of z

double y = *p_z + 1.0; // *p_z is the contents of the memory that
                       // p_z points to, i.e., z
~~~

Note here that `*p_z` means two different things, depending on where it is

[`[< compiler explorer >]`](https://gcc.godbolt.org/z/txA_mz)

# Functions

The following **function prototypes** declare two functions: one called `my_func` that takes two parameters of type `double`{.Cpp} and returns a variable of type `double`{.Cpp}, and one called `main` that takes no parameters and returns an `int`{.Cpp}:

~~~Cpp
double my_func(double x, double y);
int main();
~~~

The function prototype tells the compiler about function's name, return type, and parameters.

-------------------

~~~Cpp
#include <iostream>
double multiply(double x, double y); // function prototype

int main() {
  double a = 1.0, b = 2.0, z;
  z = multiply(a, b);
  std::cout << a << " times " << b << " equals " << z << '\n';
  return 0;
}

double multiply(double x, double y) { // function definition
  return x * y;
}
~~~

[`[< compiler explorer >]`](https://gcc.godbolt.org/z/zIof6z)

-------------------


A function may also return no value, and be declared as `void`{.Cpp}.

An example of a `void`{.Cpp} function is shown on the next slide.

The pass mark for an exam is 30 marks. This function prints out a message informing a candidate whether or not they have passed the exam:

-------------------

~~~Cpp
#include <iostream>
void output(int score, int passMark);

int main() {
  int score = 29, pass_mark = 30;
  output(score, pass_mark);
  return 0;
}

void output(int score, int passMark) {
  if (score >= passMark)
    std::cout << "Pass - congratulations!\n";
  else
    std::cout << "Fail - better luck next time\n";
}
~~~

-------------------

Any variables that are used in the function must be declared as normal.

For example:

~~~Cpp
double multiply_by_5(double x) {
  double y = 5.0;
  return x * y;
}
~~~

# Pass by value

A function can only change the value of a variable inside the function, and not in the 
main program.

This is because, by default, variables are **passed by value**, and the function only sees a **copy**.

Changes in this copied variable have no effect on the original variable:

-------------------

~~~Cpp
#include <iostream>

void no_effect(double x) {
  x += 1.0;
}

int main() {
  double x = 2.0;
  no_effect(x);
  std::cout << x << '\n';
}
~~~

[`[< compiler explorer >]`](https://gcc.godbolt.org/z/F1MBsS)

-------------------

One method of allowing a function to change the value of a variable is to send the **address** of the variable to the function:

~~~Cpp
#include <iostream>

void add(double x, double y, double* pz) {
  *pz = x + y;
}

int main() {
  double a = 1.0, b = 2.0, z;
  add(a, b, &z);
  std::cout << a << " plus " << b << " equals " << z << '\n';
  return 0;
}

~~~

-------------------

On the previous slide, the variables `x` and `y` are copies of the variables `a` and `b`. The original `a` and `b` cannot be changed by the function.

But, we also send the address of `z` to the function and we **can** change the value that `pz` points to.

The contents of `pz` are changed in the function by the line of code:

~~~Cpp
*pz = x + y;
~~~

-------------------

# References

Another way of allowing a function to change the value of a variable outside the function is to use **references**.

These are much easier to use: all that has to be done is the inclusion of the symbol `&` before the variable name in the declaration of the
function and the prototype.

For example, see the code on the next slide:

-------------------

~~~Cpp
#include <iostream>
void add(double x, double y, double& rz);

int main() {
  double x = 1.0, y = 2.0, z;
  add(x, y, z);
  std::cout << x <<" plus "<< y <<" equals "<< z <<'\n';
  return 0;
}

void add(double x, double y, double& rz) {
  rz = x + y;
}
~~~

# Default values for function parameters

It is possible to allow a function to be called without specifying all
the parameters needed.

Default parameters will be used for the other parameters.

These parameters should be declared in the function prototype.

The arguments with default parameters must be the last parameters
in the parameter list.

This should be used with care: it is easy to forget that default
parameters exist.

-------------------

For example, a solver may be written

~~~Cpp
void solver(float x, float epsilon, int maxiter)
{
  ...
}
~~~

The function prototype may be written

~~~Cpp
void solver(float x, float epsilon = 0.0001, int maxiter = 100);
~~~

This solver may be called using any of the following:

~~~Cpp
solver(x, 0.01, 10000);
solver(x, 0.01); // default value used for maxiter
solver(x); // default value used for epsilon and maxiter
~~~

# Function overloading

When a function is declared, the return type and parameter type
must be specified.

If a function `mult` is to be written that multiplies two numbers, we
would like it to work for floating point numbers and for integers.

This can be achieved by **function overloading**.

More than one function `mult` can be written - one that takes two
integers and returns an integer, one that takes two floating point
numbers and returns a floating point number, etc.

-------------------

~~~Cpp
float mult(float x, float y) {
  return x * y;
}

int mult(int x, int y) {
  return x * y;
}

int main() {
  int i = mult(7, 10);
  float f = mult(21.5f, 14.5f);
}
~~~
