#Code Coverage

##What is Code Coverage

- Measures which parts of a codebase are covered by automated tests
- Can be used to identify untested code
- Useful to ensure standards of testing are maintained throughout a project

##Types of code coverage

There are several ways to measure code coverage

- Function coverage: how many of the functions defined have been called.
- Statement coverage: how many of the statements in the program have been executed.
- Branches coverage: how many of the branches of the control structures (if statements for instance) have been executed.
- Condition coverage: how many of the boolean sub-expressions have been tested for a true and a false value.
- Line coverage: how many of lines of source code have been tested.

##Gotchas
- Code coverage is not a panacea
- High Coverage alone is not a guarantee of well tested, maintainable code
- 100% is often unattainable and may well not be worth the level of effort required - better to maintain a moderate but consistent level throughout the application
- It is entirely possible to write bad unit tests which have high code coverage - code coverage only tells you that the code was executed, not that it was well tested.

##Code Coverage in Python - coverage.py
###Install It
First, install Coverage.py:

```
pip install coverage
```

###Gather Data
Run your test suite, but replace python blah blah with coverage run blah blah 

For example:

```
coverage run Test.py
```

or, to collect branch coverage data

```
coverage run --branch Test.py
```

Ideally your tests should be outside of your source directory, so that you don't have to configure excludes or package them. It's much neater that way.

###Print Coverage Reports
####Command-Line Report
To print a quick command line report, maximize your command prompt and type:

```
coverage report -m
```
####HTML Report
To print a fancier HTML report:

```
coverage html
open html_cov/index.html
```


##Demo - Person.py

##Exercise

Now try running the test suite you wrote earlier using Coverage.

Since you have been using TDD, you should find high code coverage, 
try adding an extra untested method or an untested branch to your code
