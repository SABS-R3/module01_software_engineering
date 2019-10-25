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

#### In Python
```python
class MyClass(object):

    def __init__(self, injectedObject):
        self.injected = injectedObject
    
    def do_something(self):
        self.injected.calculate()
```
#### in C++
Interface
```c++ 
class InjectionInterface {
    public:
        virtual int addNumbers(int n, int m) = 0;
};

```
Implementation class
```c++
class InjectionImplementation: public  InjectionInterface{
    public:
        int addNumbers(int n, int m){
            return n + m;
        }
};

```

Class injected to:
```c++
class MyClass {
    public:
        MyClass(InjectionInterface &dependecy) {
            dep = dependecy;
        }

    private:
        InjectionInterface &dep;
};
```
Injection
```c++
int main() {
    InjectionImplementation myDep;
    MyClass mc(myDep);
}
```

### Method/variable injection
In Python:
```python
class MyClass(object):
    
    def do_something(self):
        self.injected.calculate()

```

A hybrid approach of default instance which may be useful to get started with
```python
class MyClass(object):

    def __init__(self):
        self.injected = MyCalculator()
    
    def do_something(self):
        self.injected.calculate()

```

## Mocking in Python

Example of Python file being tested:
```python
from temperature_sensor import TemperatureSensor


class TemperatureTracker:

    def __init__(self) -> None:
        self.sensor = TemperatureSensor()
        self.start_temp = 0

    def record_initial_temperature(self):
        self.start_temp = self.sensor.check_temperature()

    def find_temperature_change(self):
        return self.sensor.check_temperature() - self.start_temp
```

## Mocking with Mock class
```python
import unittest
from temperature_tracker import TemperatureTracker
from unittest.mock import Mock


class TestWithMock(unittest.TestCase):

    def test_tracks_temperature_change(self):
        tracker = TemperatureTracker()
        mock_sensor = Mock()
        tracker.sensor = mock_sensor

        mock_sensor.configure_mock(**{'check_temperature.return_value': 12})

        tracker.record_initial_temperature()
        mock_sensor.configure_mock(**{'check_temperature.return_value': 22})
        self.assertEqual(10, tracker.find_temperature_change())


if __name__ == '__main__':
    unittest.main()

```

## Mock with patch
```python
import unittest
from temperature_tracker import TemperatureTracker
from temperature_sensor import TemperatureSensor
from unittest.mock import patch

results = [12, 22]


class TestWithPatch(unittest.TestCase):

    @patch.object(TemperatureSensor, 'check_temperature', side_effect=results)
    def test_tracks_temperature_change(self, mock):
        tracker = TemperatureTracker()
        tracker.record_initial_temperature()
        self.assertEqual(10, tracker.find_temperature_change())


if __name__ == '__main__':
    unittest.main()

```

## Using patch with built in function
Python file under test:
```python
import time


def whats_the_time():
    return time.time()
```
Test code:
```python
import unittest
import clock
from unittest.mock import patch


class MyTestCase(unittest.TestCase):

    @patch('time.time', return_value=1571871846.8861961)
    def test_the_time(self, mock):
        self.assertEqual(clock.whats_the_time(), 1571871846.8861961)


if __name__ == '__main__':
    unittest.main()
```
## Exercise
Name picker:
Implement a function that can provides a random name from the top 100 list of baby names in the UK in 2018