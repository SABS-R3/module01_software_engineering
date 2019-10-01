# Mocking
Mocking is the practice of using mock implementation of classes called by the class under test.

## Why mock
- Separation of Concerns
- External dependencies
- Predictable behaviour

## Dependency Injection 
In Dependency Injection classes do not instantiate the objects they use, they are injected by an injector. 
- Supports Separation of concerns
- Supports Modularisation
- Supports mocking in testing

Ways of achieving
### Constructor injection

In Python
```python
class MyClass(object):

    def __init__(self, injectedObject):
        self.injected = injectedObject
    
    def do_something(self):
        self.injected.calculate()
```
in C++
```c++

```
### Method/variable injection
In Python:
```$xslt
class MyClass(object):
    
    def do_something(self):
        self.injected.calculate()

```
In C++
- Injection framework 

A hybrid approach of default instance which may be useful to get started with
```$xslt
class MyClass(object):

    def __init__(self):
        self.injected = MyCalculator()
    
    def do_something(self):
        self.injected.calculate()

```



In unit testing the test can be the injector to inject mock objects. Test injection frameworks are available.

## Exercise
Name picker:
Implement a function that can provides a random name from the top 100 list of baby names in the UK in 2018