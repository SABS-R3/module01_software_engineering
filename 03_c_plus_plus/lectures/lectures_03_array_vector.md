% Numerical Computing in C++ - lectures 3-4
% Fergus Cooper
% 2019

# Fixed sized arrays

If the size of the array is known in advance (i.e. at compile-time) then it is
better to use the fixed size array `std::array<T,N>`{.Cpp}, where `T` is the type that
the array will hold (e.g. `int`{.Cpp}, `double`{.Cpp}), and `N` is the length of the array.

~~~Cpp
#include <array>
std::array<int, 4> x; // x holds 4 int
std::array<double, 5> y; // y holds 5 double

// a 5 by 5 array
std::array<std::array<double,5>,5> z;
~~~

In contrast to Matlab and FORTRAN the indices of an array of length `n` start at 0 and end at `n-1`

-----

Elements of the array are accessed by placing the indices in separate square brackets, for example

~~~Cpp
x[0] = 1;
z[1][2] = 3.0;
~~~

Arrays can be initialised when they are declared, for example

~~~Cpp
std::array<double,3> array1 = {0.0, 1.0, 2.0};
std::array<std::array<double,3>,2> array2 =
                            {{{0.0, 1.0, 2.0},
                              {3.0, 4.0, 5.0}}};
~~~

-----

Note that the values of arrays may only be set using the curly bracket notation when they are declared - for example the code

~~~Cpp
std::array<int,3> array = {0, 1, 2};
~~~

is correct, but the code

~~~Cpp
std::array<int,3> array;
array = {0, 1, 2};
~~~

is not correct.





# Vectors - dynamic arrays

We have already covered a fixed-sized array, `std::array<T, N>`, but a more
flexible container is provided by `std::vector<T>`, which is a dynamically-sized
vector holding elements of type `T`.

~~~cpp
std::vector<double> x = {1.0, 2.0, 3.0};
x.push_back(4.0);  // x now holds 4 values

std::vector<std::string> y;
y.push_back("one");
y.push_back("two");
~~~

# Adding and removing elements

Add elements to the *end* of the vector using `push_back`, remove elements from
the *end* of the vector using `pop_back`. You can resize the vector using
`resize`. Get the current size of the vector using `size`

~~~cpp
std::vector<double> x;
x.push_back(1.0);
x.push_back(2.0); // x holds {1.0, 2.0}
x.pop_back();     // x holds {1.0}
x.resize(3);      // x holds {1.0, ?, ?}

std::cout << x.size() << std::endl; // 3
~~~

# Read/write individual values

You can access individual elements for reading or writing using `operator[]`{.Cpp}

~~~cpp
std::vector<int> x = {1, 2, 3};
std::cout << x[1] << std::endl; // print 2
x[1] = 5;
std::cout << x[1] << std::endl; // print 5
~~~

# Read/write multiple values - loops revisited

You often want to loop through a vector to perform some operation,
for example printing each element of a vector:

~~~cpp
std::vector<double> x = {1.0, 2.0, 3.0, 4.0};
for (int i = 0; i < x.size(); ++i)
{
   std:cout << x[i] << std::endl;
}
~~~

You could call this an index-based for loop. Other methods of looping
through a vector (or any other container in C++) include **range-based** loops,
**iterator-based** loops, and standard library algorithms:

# Iterator-based loops

`std::vector` is a container in the Standard Template Library (STL).
Every container defines its own **iterators**, which can be used to iterate
over the container.

~~~cpp
for (std::vector<double>::iterator i = x.begin();
     i != x.end(); ++i) {
   std:cout << *i << std::endl;
}
~~~

An iterator acts like a pointer to each element of the vector

# Iterator-based loops using `auto`

The keyword `auto`{.Cpp} is used to tell the compiler to infer the
correct type (i.e. what is returned from `x.begin()`, this can be used to
simplify this syntax:

~~~cpp
for (auto i = x.begin(); i != x.end(); ++i)
{
   std:cout << *i << std::endl;
}
~~~

# Range-based loops

Range-based loops have the most compact syntax, and work with any
container that has `begin` and `end` methods.

~~~cpp
std::vector<double> x = {1.0, 2.0, 3.0, 4.0};
for (double i: x)
{
   std:cout << i << std::endl;
}
~~~

# Range-based loops using `auto`{.Cpp}

You can use `auto`{.Cpp} here to simplify things...

~~~cpp
for (auto i: x)
{
   std:cout << i << std::endl;
}
~~~

# Range-based loops using `auto&`

The code on the previous slide could not alter the contents of the vector
because `i` was a *copy* of each element of x. You can instead make `i` a
reference to edit values.

~~~cpp
for (auto& i: x)
{
    i = 1.0; // set each element to 1.0
}

for (const auto& i: x)
{
    std::cout << i << std::endl; // print each element to the console
}
~~~

# Lambda functions

You can define a **lambda function** within the current scope:

~~~cpp
auto empty_lambda = [](){};

auto hello_world = []() {
      std::cout << "hello world" << std::endl;
    };

hello_world();
~~~

The `auto`{.Cpp} keyword allows the compiler to determine the correct type for
the lambda, rather than you declaring it manually (impossible for lambda
functions!)

# Lambda functions

The square brackets **capture** variables from the outside scope, for example

~~~cpp
int i = 1;
auto add_i_to_arg = [i](int arg) { return arg + i; }
std::cout << add_i_to_arg(3) << std::endl; // prints 4
~~~

This captures `i` by value. To capture by reference use `&`:

~~~cpp
int i = 1;
auto add_arg_to_i = [&i](int arg) { i += arg; }
add_arg_to_i(3);
std::cout << i << std::endl; // prints 4
~~~

# Lambda functions

You can capture all variables used in the lambda function using either `[=]`,
which captures everything by value, or `[&]`, which captures everything by
reference:

~~~cpp
int i = 1;
auto add_i_to_arg = [=](int arg) { return arg + i; }
std::cout << add_i_to_arg(3) << std::endl; // prints 4

auto add_arg_to_i = [&](int arg) { i += arg; }
add_arg_to_i(3);
std::cout << i << std::endl; // prints 4
~~~

# STL algorithms

The STL is vast, and we won't be covering even a small portion of it during this
course, but there are many **algorithms** that operate on containers. For example,
the `std::transform` algorithm

~~~cpp
std::transform(x.begin(), x.end(), x.begin()
    [](double i) { return 2*i; });
~~~

You could also define the lambda function on its own as

~~~cpp
auto f = [](double i) { return 2*i; };
std::tranform(x.begin(), x.end(), x.begin(), f)
~~~

[`[< cpp reference >]`](https://en.cppreference.com/w/cpp/algorithm)


