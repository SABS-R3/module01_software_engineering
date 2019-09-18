from setuptools import setup, find_packages

setup(
    name='cell_model',
    version='0.0.1',
    description='cell diffusion and excluded volume model',
    license='BSD 3-clause license',
    maintainer='Martin Robinson',
    maintainer_email='martin.robinson@cs.ox.ac.uk',
    packages=find_packages(include=('cell_model')),
    install_requires=[
        'numpy',
        'matplotlib',
    ],
)

