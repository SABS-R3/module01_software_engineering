---
title: Optimisation 3 - Wrapping C++ with pybind11
author: Martin Robinson
date: Oct 2019
urlcolor: blue
---

# Why wrap C++

- compiling python code into a lower-level language typically involves writing a 
  restricted/modified version of Python
- might be easier to simply write in a standard language (e.g. C++) and "wrap" this for 
  use in Python.
- difficulty moves from "rewriting slow code in modified Python" to "writing the 
  wrapper", good if the interface is small and well defined
- easier to use existing C/C++/Fortran libraries using this approach

# Libraries

There are many libraries to help you write this wrapper:

- standard Cpython implementation of Python has a C API you can use directly
- Simplified Wrapper and Interface Generator (SWIG) generates wrappers for C/C++ code in 
  for Lua, Perl, PHP, Python, R, Ruby, Tcl, C#, Java, JavaScript, Go, Modula-3, OCaml, 
  Octave, Scilab and Scheme.
- Main libraries for wrapping C++ code are Boost Python and PyBind11, write interface 
  code in an embedded C++ domain specific language
- F2PY generates a wrapper for calling Fortran code from Python, part of Numpy

# PyBind11

- <https://github.com/pybind/pybind11>
- Developers goal was to create a lightweight alternative for Boost Python using C++11
- Header-only project and small, easy to bundle with your own library
- Wrappers can be compiled manually or using CMake
- No-copy data transfer of STL containers, Eigen matrices and Numpy arrays between 
  Python and C++

# Wrapping functions

```cpp
#include <pybind11/pybind11.h>
namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");
}
```

# Compiling

- This example can be compiled manually, but for a bigger project it is more useful to 
  use the CMake build system

```bash
$ c++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` 
example.cpp -o example`python3-config --extension-suffix`
```

# Using from Python

- Assuming your compiled module is available in the current directory, can be imported 
  as a normal python module

```python
import example
example.add(1, 2)
```

# Keyword arguments

- Can give python more information about the arguments and documentation

```cpp
m.def("add", &add, "A function which adds two numbers",
      py::arg("i"), py::arg("j"));
```

- Then you can use keyword arguments in python

```python
import example
example.add(i=1, j=2)
help(example)
```

# Compiling with CMake

- PyBind11 supplies an easy-to-use CMake macro to compile your wrapper

```cmake
cmake_minimum_required(VERSION 2.8.12)
project(example)

add_subdirectory(pybind11)
pybind11_add_module(example example.cpp)
```

- Many existing C++ projects use CMake, so easy to integrate their build systems into 
  PyBind11

# Integrating into `setup.py`

1. Write a build extension `cmdclass` that uses the C++ projects CMake infrastrucure
1. Add your C++ code to the `ext_modules`

\[show example code here\]


# Introduction to C++ Classes

- Lets wrap the following C++ class

```cpp
class Pet {
public:
    std::string name;
};
```

This class might be used like so:

```cpp
Pet cat;
cat.name = "whiskers";
```

# Writing class function

We want to be able to write functions that are associated with
this class.

We will write a function `printSummary()` that prints out a nicely
formatted summary of the information held in the class.

A function on an object is known as a **method** of the
object.

-----------------------

```cpp
class Pet {
public:
  void printSummary();
  std::string name;
};

void Pet::printSummary() {
  std::cout << "This pet is called \""<< name << "\"" << std::endl;
}
```

----------------------------

On the previous slide the compiler knows that the function definition
is associated with the class `Pet` through the statement

~~~Cpp
void Pet::printSummary()
~~~

Where `Pet::` associates the definition with the declaration inside
the class. This function may used outside the class by using statements
such as:

~~~Cpp
cat.printSummary();
~~~


# Constructors

Each time an object of the class of `Pet` is created,
the program calls a function that allocates space in memory for all
the variables used.

This function is called a **constructor** and is automatically generated.

This default constructor can be overridden if desired – for example in
our class we may want to allow the user to set the pet name when a new object is 
created.

A **constructor** has the same name as the class, has no return type,
and must be `public`{.Cpp}.

----------------------------

An overridden default constructor function is included in the class
shown below

~~~Cpp
class Pet {
public:
  Pet(const std::string& _name);
...
~~~

and the function is written

~~~Cpp
Pet::Pet(const std::string& _name) {
    name = _name;
}
~~~


----------------------------

or more compactly as:

~~~Cpp
Pet::Pet(const std::string& _name): name(_name) {}
~~~

# Access privileges

An instance of a class is known as an **object**. In the previous slide,
for example, `cat` is an object of type `Pet`.

Variables and functions associated with a class - for example
`name` and `printSummary()` - are known as class
**members** and **methods**.

There are three degrees of access to class members and methods:

- `private`{.Cpp} - only accessible to other class members and methods
- `public`{.Cpp} - accessible to everyone
- `protected`{.Cpp} - accessible to other class members and to derived classes

----------------------------

It is often useful to restrict access to internal variables of a class and only make 
available a specific public API. For example, here we will make the variable `name` a 
`private`{.Cpp} class member and provide access using a pair of functions traditionally 
called *getter* and *setter* functions

```cpp
class Pet {
public:
    Pet(const std::string &_name);
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }
    void printSummary();
private:
    std::string name;
};
```


# Wrapping C++ classes

- Back to PyBind11...
- the binding code for our `Pet` class is

```cpp
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(example, m) {
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName);
}
```

# Access to class variables

- Could provide direct access to the `name` field using pybind11

```cpp
    .def_readwrite("name", &Pet::name)
```

- Alternativly, Python uses properties instead of C++ getters/setters, this can be 
  emulated like so

```cpp
    .def_property("name", &Pet::getName, &Pet::setName)
```

# Wrapping lambda function

- its often neccessary to write small snippits of C++ to wrap your code, pybind11 
  thankfully support wrapping lambda functions

```cpp
    .def("__repr__",
        [](const Pet &a) {
          return "This pet is called \"" + name + "\"";
        }
    );
```

# Using Python types in C++

- PyBind11 provides C++ wrappers for the standard data structures in Python, e.g.

```cpp
void print_dict(py::dict dict) {
    /* Easily interact with Python types */
    for (auto item : dict) {
        std::cout << "key=" << std::string(py::str(item.first)) << ", "
                  << "value=" << std::string(py::str(item.second)) 
                  << std::endl;
    }
}
```

# Using Numpy arrays in C++

- This includes numpy arrays!

```cpp
double norm(py::array_t<double> input, const int p) {
    py::buffer_info buf = input.request();
    double result = 0.0;
    for (size_t i = 0; i < buf.shape[0]; ++i) {
      result += std::pow(buf[i],p);
    }
    return std::pow(result, 1.0/p);
}
```

# Using Numpy arrays in C++

- Can turn off normal Python bounds checking as well...

```cpp
double norm(py::array_t<double> input, const int p) {
    // input must have ndim = 1; can be non-writeable
    // use input.mutable_unchecked for writeable access
    auto buf = input.unchecked<1>(); 
    double result = 0.0;
    for (size_t i = 0; i < buf.shape[0]; ++i) {
      result += std::pow(buf[i],p);
    }
    return std::pow(result, 1.0/p);
}
```


# Type conversions

- Many basic C++ types are automatically converted for you, see the [conversion 
  table](https://pybind11.readthedocs.io/en/master/advanced/cast/overview.html#conversion-table)
- STL containers can be automatically converted (remember to include `pybind11/stl.h`), 
  but this uses a **copy**
- If you don't want a copy, need to make the STL type *opaque*

# Opaque types

- Use `PyBIND11_MAKE_OPAQUE` to turn off automatic conversion of STL type. Then, either 
  wrap it as normal, or use PyBind11's pre-build wrappers:

```cpp
#include <pybind11/stl_bind.h>

PYBIND11_MAKE_OPAQUE(std::vector<int>);

// ...
// in PYBIND11_MODULE: 

  py::bind_vector<std::vector<int>>(m, "VectorInt");
```

# More information

- This has been a summary of the PyBind11 features you will need for the exercies
- See the [documentation](https://pybind11.readthedocs.io/en/master/index.html) for many 
  more details, exaplanation and additional features
