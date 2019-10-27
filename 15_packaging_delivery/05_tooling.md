
# Tooling

## CI/CD Server

Hosted only. Many more available if you install and run yourself.

* [Travis CI](https://travis-ci.com)
  * Free for open source projects
  * Links to GitHub
* [Circle CI](https://circleci.com/)
  * Free for open source (up to a limit per week)
  * Links to GitHub
* [Codefresh](https://codefresh.io/)
  * More limited in free offering
  
## Code analysis

* [SonarCloud](https://sonarcloud.io)
  * SonarQube hosted
  * Free for public projects
* [Lint](https://realpython.com/python-code-quality/)
  * Review article for Python solutions
* [PyCharm code inspections](https://www.jetbrains.com/help/pycharm/code-inspection.html)

## Build and package

* Pip: described in [Packaging for Python](https://packaging.python.org/overview/) and [Packaging and distributing Python projects](https://packaging.python.org/guides/distributing-packages-using-setuptools/)
* Conda:cross platform and linked to [Anaconda](https://docs.conda.io/en/latest/)
* [Pip vs Conda](https://www.anaconda.com/understanding-conda-and-pip/)

## Testing
* Which Python testing framework?
* Is it friendly for CI/CD execution?

\newpage

# Example
* [Python project example](https://realpython.com/python-continuous-integration/)
* Uses CircleCI 

```
# Python CircleCI 2.0 configuration file
version: 2
jobs:
  build:
    docker:
      - image: circleci/python:3.7

    working_directory: ~/repo

    steps:
      # Step 1: obtain repo from GitHub
      - checkout
      # Step 2: create virtual env and install dependencies
      - run:
          name: install dependencies
          command: |
            python3 -m venv venv
            . venv/bin/activate
            pip install -r requirements.txt
      # Step 3: run linter and tests
      - run:
          name: run tests
          command: |
            . venv/bin/activate
            flake8 --exclude=venv* --statistics
            pytest -v --cov=calculator
```

\newpage