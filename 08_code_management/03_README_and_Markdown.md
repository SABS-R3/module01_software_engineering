# Living Documentation

## README
- Plain text file traditionally distributed with source to provide documentation on the software
- GitHub will display README files to the root of the project and any directories that contain them
- README files written in markdown (README.md) will be display as formatted HTML in GitHub
- These form part living documentation of the code as it can be update alongside the code the in code repository

## Markdown
A plain text readable format that can also be converted to HTML or displayed in other rich format

Headings
```markdown
 # Top level heading
 
 ## Level two heading
 
 ### Level three heading
 
```


Bullets lists and numbered lists
```markdown
- Point 1
- Another point

1. The first item
2. Yet other item
```
- Point 1
- Another point

1. The first item
2. Yet other item

Note: Number list that are non-sequential will be displayed sequentially

Code blocks
````markdown
```python
def add_one(n):
    return n + 1
```
````
```python
def add_one(n):
    return n + 1
```
Tables
```markdown
|Name of Fruit |Price of Fruit|
|:-------------|-------------:|
|Orange        |40p           |
|Apple         |20p           |
|Banana        |50p           |
```
|Name of Fruit |Price of Fruit|
|:-------------|-------------:|
|Orange        |40p           |
|Apple         |20p           |
|Banana        |50p           |

*_Plus more!!!_*

## Exercise
Create a README file for your assignment providing a description of what the software will be written in markdown. 

## Documentation comments
Many languages have built in support or tools for generating documentation or for provide help in IDEs.

Python has docstrings

```python
def add_one(n):
    """
    Adds one to a number    
    :param n: The number one will be added to
    :return: the number with one added
    """
    return n + 1
```

Doxygen can be used to generate documentation for  C and C++ (as well as many other languages)
### Exercise
Experiment with creating Doxygen (http://www.doxygen.nl) comments in C++ 