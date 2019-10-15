% Introduction to C++
% Martin Robinson
% Oct 2019

# Administration

- Canvas page for the SABS software engineering module has lecture slides, and practical 
  exercises
- Combination of lectures and practical sessions
  - Practical exercises (`practical.pdf`) give you practice on the material covered in 
    the lectures

# Timetable

- 09:30-12:30 Lecture & practical session
- 12:30-13:30 Break
- 13:30-17:00 Lecture & practical session

# Outline

This course gives you a crash course in C++ programming using C++14, focusing on the
getting you started and the major differences from Python. *This is a small part of C++
as a whole!*

1. **Morning**: compilation, basic types, flow control, pointers, references, functions
1. **Afternoon**: `std::array`, `std::vector`, lambda functions, STL algorithms

This course does **not** cover:

1. Classes and object-oriented programming
1. Templates and generic programming
1. Memory allocation/deallocation and smart pointers
1. Most of the Standard Library and the Standard Template Library
1. Many, many other topics....

# Acknowledgements

Material for this course adapted from:

- Pitt–Francis & Whiteley: Guide to Scientific Computing in C++
- C++ for Scientific Computing course by Joe Pitt–Francis:
  <http://www.cs.ox.ac.uk/people/joe.pitt-francis/C++ScientificComputing/>

# A few introductory remarks

- C++ is a multi-paradigm language with the goal of allowing powerful abstractions with *zero* run-time cost
- It is generally useful to know at least one low-level language (e.g. C++) and
  one high-level language (e.g. Python, Matlab) for your work.
- C++ is useful for:
  - High performance applications. Concurrency, parallelism and compilation to
    efficient, optimised binaries is easier in C++
  - Software libraries. C++ is designed for zero-cost abstraction, so library
    authors can provide their functionality with minimal overhead.
  - Access to a truly vast array of third-party scientific libraries

# Books

- Programming: Principles and Practice Using C++

![Programming: Principles and Practice Using C++](images/bjarne.png)

# Books

- Guide to Scientific Computing in C++

![Guide to Scientific Computing in C++](images/jpf.png)

# Software for the course

- [Compiler explorer](https://gcc.godbolt.org/)

![Compiler explorer](images/compiler_explorer.png)

# Software for the course

- [CLion](https://www.jetbrains.com/clion/)

![CLion](images/create_project.png)

# Software for the course

- [CLion](https://www.jetbrains.com/clion/)

![CLion](images/run.png)


# Lecture 1 — The basics

## General structure of a basic C++ program

~~~Cpp
#include <header1>
#include <header2>
int main() {
  line of code;
  // this is a comment, ignored by the compiler
  more code; // this is a comment as well
  /*
   * Multi-line
   * comment
   */
  return 0;
}
~~~

-----

Things to note

- Header files are listed first. These are files that contain the functions needed for operations such as input, output and mathematical calculations
- There is a section of code that starts `int main()`{.Cpp}
  - or `int main(int argc, char* argv[])`{.Cpp} when command-line input is important
- This section of code is followed by more code enclosed between curly brackets, { and }
- Comments may easily be inserted into the code
- Lines of code that "do something" end with a semicolon `;`
- Just before the closing curly bracket at the end of the code is a statement `return 0;`{.Cpp}

# A first C++ program

~~~Cpp
#include <iostream>
int main()
{
  std::cout << "Hello World\n";
  return 0;
}
~~~

[`[< compiler explorer >]`](https://gcc.godbolt.org/z/2BzBCi)

-----

This program prints the text "Hello World" to the screen

- `iostream`{.Cpp} is a header file that is needed when using input and output
- `std::cout`{.Cpp} is a command that sends output to the console, i.e. the screen
- `'\n'`{.Cpp} is a formatting command that starts a new line
- All statements (lines of the program) inside the curly brackets end with a semicolon `;`{.Cpp}

# Compiling the code

- A key difference between Python and C++ is that before the code can be executed it 
  must be compiled
- When using software such as the Compiler Explorer or CLion, this is often done automatically
- When using the Gnu compiler of Unix/Cygwin this code can be compiled by saving the code and typing

  ~~~bash
  g++ -o hello_world hello_world.cpp
  ~~~

  followed by return.
- This produces an executable called `hello_world` that can be executed by typing

  ~~~bash
  ./hello_world
  ~~~

# Makefiles

- Make is a general-purpose Unix tool that generates *targets* from their *depedencies*
  according to a set of *rules*, or *commands*, that you supply. These targets,
  dependencies and rules are all specified in a file called `Makefile`. For example:

  ~~~make
  hello_world: hello_world.cpp
    g++ -o hello_world hello_world.cpp
  ~~~

- Type `make` in a directory containing a `Makefile`, which by default generates the 
  first target in the `Makefile`.

# CMake

- CMake is a higher-level build system, which takes project definitions written in its 
  own syntax, and generates `Makefiles` (or other, similar tools) that will compile your 
  project, for example:

  ~~~cmake
  cmake_minimum_required(VERSION 3.10)
  project(hello_world)
  set(CMAKE_CXX_STANDARD 14)
  add_executable(hello_world hello_world.cpp)
  ~~~

- Run `cmake` to generate the Makefile, then `make` to do the compilation

  ~~~bash
  $ cmake <path-to-CMakeLists.txt>
  $ make
  ~~~

# Clion

- CLion is a C++ Interactive Development Environment (IDE) that, among other things, can 
  handle compilation of (simple) projects automatically
- It uses CMake to do this, creating a `CMakeLists.txt` within each project
- You can edit the `CMakeLists.txt` directly to specify custom build behaviour
- CLion will be the recommended IDE to use during this course, although you are free to 
  use whatever tool you are most familiar with.
