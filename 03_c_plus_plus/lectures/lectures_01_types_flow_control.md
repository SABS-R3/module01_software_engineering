% Introduction to C++ - types and flow control
% Martin Robinson
% Oct 2019


# Numerical variables

Before a variable is used the type of variable must be declared. For example if the variables i and j are integers and a is a double precision floating point number the statements

~~~Cpp
int i, j;
double a;
~~~

must be included in the program before these variables are used.

It is advisable to use `double`{.Cpp} rather than `float`{.Cpp} in scientific computing applications.

Some names, such as `int`{.Cpp}, `for`{.Cpp}, `return`{.Cpp} may not be used as variable names because they are used by the language.

- These words are known as reserved words or keywords

-----

The following code adds two integers and print the answer to screen:

~~~Cpp
int integer1 = 5;
int integer2 = 10;
int answer = integer1 + integer2;

std::cout << "The sum of " << integer1 << " and "
          << integer2 << " is " << answer << '\n';
~~~

The details of the `std::cout` statement will be explained later

# More on built-in types

A variable may be initialised when defining the variable type, for example

~~~Cpp
int i = 5;
~~~

The value of more than one variable may be assigned in each statement:

~~~Cpp
int i, j;
i = j = 3;
~~~

This will cause confusion because it means

~~~Cpp
i = ( j = 3 );
~~~

and not

~~~Cpp
( i = j ) = 3;
~~~

[`[< compiler explorer >]`](https://gcc.godbolt.org/z/yM3VpW)


#

When assigning values to floating point variables it is good programming practice to write numbers with decimal points, i.e.

~~~Cpp
double x = 5.0;
float y = 7.0f;
~~~

rather than

~~~Cpp
double x = 5;
float y = 7;
~~~

If a quantity is a constant throughout the program it may be declared as such

~~~Cpp
const double density = 45.621;
~~~

# Fundamental types

- Boolean type
  - `true`{.Cpp} or `false`{.Cpp}
- Integer types
  - `signed`{.Cpp} or `unsigned`{.Cpp}
  - `short`{.Cpp}, `long`{.Cpp}, `long long`{.Cpp}
  - e.g. `short int`{.Cpp}; `int`{.Cpp}; `long int`{.Cpp}; `unsigned short`{.Cpp}; `unsigned long long`{.Cpp}
- Floating point types
  - `float`{.Cpp}
  - `double`{.Cpp}
  - `long double`{.Cpp}

# Representable values

Some variable types and ranges are given below. Note the these are operating system dependent:

~~~
Variable type     C++ name       Range
-------------     ------------   -----------------
integer           int            -2^31 to 2^31 - 1
integer           long int       -2^63 to 2^63 - 1
unsigned integer  unsigned int    0 to 2^32 - 1
floating point    float          -3.4 x 10^38 to 3.4 x 10^38
floating point    double         -1.8 x 10^308 to 1.8 x 10^308
floating point    long double    -1.2 x 10^4932 to 1.2 x 10^4932
~~~

The values on your specific system can be found in `std::numeric_limits`:

[`[< compiler explorer >]`](https://gcc.godbolt.org/z/mLZuDP)

# Mathematical operations

There is a shorthand for some mathematical operations

~~~
 Longhand   Shorthand
----------  ---------
a = a + b;   a += b;
a = a - b;   a -= b;
a = a * b;   a *= b;
a = a / b;   a /= b;
a = a + 1;   a++; if a is an integer
a = a - 1;   a--; if a is an integer
~~~

-----

Some example lines of code

~~~Cpp
float a, b;
double d, e;
a = 3.0;
b = ( a * std::pow(a, 3) ) / 2.0;
d = 4.0;
e = 2.0 * std::sqrt(d);
~~~

`std::pow(x,y)`{.Cpp} gives the value of $x^y$. The `std::`{.Cpp} indicates the standard
namespace.

`std::sqrt(d)`{.Cpp} gives the square root of the variable `d`

When using mathematical functions such as `std::pow`{.Cpp}, you need to

~~~Cpp
#include <cmath>
~~~

-----

Division of an integer by another integer will almost certainly cause problems

An example is given in the following piece of code

~~~Cpp
int i = 5, j = 2, k;
k = i / j;
std::cout << k << '\n';
~~~

The variable `k` is an integer and so cannot store the true value, 2.5

Instead, it will store the value 2

-----

Suppose an integer is divided by a variable of type `double`{.Cpp} - or vice versa -
and that the result returned is stored in a variable of type `int`{.Cpp}, as shown in
the code below.

The variable `k` in this code is unable to store the mathematically correct answer

~~~Cpp
double i = 5.0;
int j = 2, k;
k = i / j;
std::cout << k << '\n';
~~~

Only construct mathematical operations that are on elements of the same type

An integer can be converted, or cast, to a different data type – see the next
slide

-----

Variables can be converted from one type to another, for example:

~~~Cpp
double i = 5.0;
double k;
int j = 2;
k = i / static_cast<double>(j);
std::cout << k << '\n';
~~~

In this example, `static_cast<double>(j)`{.Cpp} makes the variable `j` behave as
if it were a `double`{.Cpp} variable.

# ASCII characters

ASCII characters are numbers, uppercase letters, lowercase letters and some other symbols

These characters may be represented using the data type `char`{.Cpp}

~~~Cpp
#include <iostream>
int main() {
  char letter;
  letter = 'a'; // note the single quotation marks

  std::cout << "The character is " << letter << '\n';

  return 0;
}
~~~

# Boolean variables

These variables take the values `true`{.Cpp} or `false`{.Cpp}, and are of use when using `if`{.Cpp} conditionals and `while`{.Cpp} loops

They are used as follows:

~~~Cpp
bool flag = true;
~~~

# Strings

A character is one letter or number, a string is an ordered collection of characters

For example, "C++" is a string consisting of the ordered list of characters "C", "+", and "+"

To use strings in C++ requires an extra header, as shown below:

~~~Cpp
#include <iostream>
#include <string>

int main() {
  std::string city = "Oxford"; // note the std:: and the " marks
  std::cout << city << '\n';
}
~~~

# Lecture 2 — Flow of control

# The if statement

Suppose you want to execute some code only if the condition `p > q`{.Cpp} is met

This is achieved using the following code:

~~~Cpp
if (p > q) {
  statement1;
  statement2;
}
~~~

Note the indentation. This makes it clear which statements are executed in the body of the `if`{.Cpp} statement.

-----

If only one statement is to be executed curly brackets aren't strictly necessary.

For example, the following code will execute statement1 if the condition `p > q`{.Cpp} is met

~~~Cpp
if (p > q)
  statement1;
~~~

but this is considered poor software engineering practice, and instead you should write this code as

~~~Cpp
if (p > q) {
  statement1;
}
~~~

The use of curly brackets makes it clear which statement(s) are to be
executed.

-----

Third example – more than one condition

~~~Cpp
if (p == 0) {
  statement1;
} else if (p < 0) {
  statement2;
  statement3;
} else {
  // p > 0
  statement4;
}
~~~

-----

Fourth example – nested `if`{.Cpp} statements

~~~Cpp
if (p < q) {
  if (x >= y) {
    statement1;
  }
}
~~~

Fifth example – more than one condition

~~~Cpp
if (p < q || x < y) {
  statement1;
}
~~~

`statement1` is executed only if one or both of `p < q` and `x < y` is true - i.e. `||` is the logical `OR` operator.

# Relational and logical operators

~~~
   relation                  operator
---------------          ---------------
equal to                 == (note: not "=" which is assignment)
not equal to             !=
greater than             >
less than                <
greater than or equal to >=
less than or equal to    <=
~~~

-----

~~~
logical condition operator
----------------- --------
      AND           &&
      OR            ||
      NOT           !
~~~

#

Boolean variables may be used in `if`{.Cpp} statements as follows

~~~Cpp
bool flag1 = true, flag2 = false;
if (flag1) {
  std::cout << "Does print something" << '\n';
}
if (flag2) {
  std::cout << "Doesn't print anything" << '\n';
}
if (!flag2) {
  std::cout << "Does print something" << '\n';
}
~~~

# The while loop

~~~Cpp
while ( x < 100.0 && i < 10 ) {
  x += x;
  i++;
}
~~~

The condition `x < 100.0 && i < 10`{.Cpp} is tested only at the beginning of the statements in the loop, and not after every statement.

For example if the loop is entered when $x = 99.0$ and $i = 1$, the loop will be executed completely once.

Loop won't be entered when $x \ge 100$: `x` and `i` will be unchanged.

If you need a loop to execute at least once, with a test at the end, use:

- `do { ... } while (condition)`{.Cpp}

# The for loop

The following loop executes the statements inside the loop 10 times.

~~~Cpp
for (int i=0; i<10; i++) {
  statement1;
  statement2;
}
~~~

Note that `i` can be previously declared, or declared in the loop statement.

# The for loop

`for` loops can be nested and run over variable indices:

~~~Cpp
for (int i=0; i<5; i++) {
  for (int j=0; j<10; j++) {
    std::cout << "i = " << i << " j = " << j << '\n';
  }
}
~~~

# Random Number generation

You can generate random numbers using the standard library

~~~Cpp
#include <iostream>
#include <random>
int main() {

    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(0,1);

    double my_rand = dist(generator);
    return 0;
}
~~~

[`[< compiler explorer >]`](https://gcc.godbolt.org/z/CcHE57); [`[< cpp reference >]`](https://en.cppreference.com/w/cpp/numeric/random)

# Console output

Console output may be achieved by using `std::cout`

We have already seen that the statement

~~~Cpp
std::cout << "Hello World\n";
~~~

prints the text "Hello World" to the screen, followed by a newline.

The statements

~~~Cpp
int x = 1, y = 2;
std::cout << "x = " << x << " and y = " << y << '\n';
~~~

give the following output:

~~~
x = 1 and y = 2
~~~

-----

Note that any spaces required in the output must be included within quotation marks.

Some useful formatting commands are:

~~~
 Command    Symbol
---------  --------
 newline      \n
 tab          \t
  '           \'
  "           \"
 (bell)       \a
~~~

-----

Sometimes, for example if the computer is busy doing a large volume of computation, the program may not print the output to the screen immediately. If immediate output is desirable then use `std::cout.flush()` after any `std::cout` commands

~~~Cpp
std::cout << "Hello World\n";
std::cout.flush();
~~~

or use `std::endl`, which combines a newline with a flush:

~~~Cpp
std::cout << "Hello World" << std::endl;
~~~

# Writing to file

When writing to file, an additional header function `fstream` is needed.

~~~Cpp
#include <iostream>
#include <fstream>
#include <string>
~~~

The file `output.dat` may be opened using the statement

~~~Cpp
std::ofstream out("output.dat");
~~~

We can then write to this file in a similar manner as writing to the screen, with the exception that `cout` is replaced by `out`

-----

There are a number of formatting options available. The following prints data in scientific format:

~~~Cpp
#include <iostream>
#include <fstream>
int main() {
  double x = -1.0, y = 45.3275893627129, z = 0.00000001;
  std::ofstream out("output.dat");
  out.setf(std::ios::scientific|std::ios::showpos);
  out << x << " " << y << " " << z << '\n';
  out.close();
  return 0;
}
~~~

[`[< compiler explorer >]`](https://gcc.godbolt.org/z/HYgcPg); [`[< cpp reference >]`](https://en.cppreference.com/w/cpp/io/ios_base/fmtflags)

# Reading from file

Suppose the file `numbers.dat` has 3 columns of numbers.
This file can be opened using the following code

~~~Cpp
#include <fstream>

double x, y, z;
std::string line;
std::ifstream input("numbers.dat");
assert(input.is_open());
~~~

`input.is_open()` returns `true`{.Cpp} if the file was successfully opened

-----

We can read the file like so:

~~~Cpp
#include <sstream>

while(std::getline(input, line)) {
    std::istringstream s(line);
    s >> x >> y >> z;
}
input.close();
~~~

`std::getline` gets the next line of the file and returns `false`{.Cpp} if we are at the
end of the file.

`std::istringstream` converts the `std::string line` to a stream (like
`std::cin`) which can be used to separate out the three columns.

