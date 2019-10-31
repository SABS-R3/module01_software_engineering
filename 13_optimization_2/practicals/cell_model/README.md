# Instructions

This code requires pybind11. Change directories to the root folder (i.e. `cell_model/`), 
and clone the pybind11 repository using 

```bash 
git clone https://github.com/pybind/pybind11.git
```

Once this is done, you can install the code by typing:

```bash
python3 -m venv env
source env/bin/activate
pip install -e .
python simulate.py
```
