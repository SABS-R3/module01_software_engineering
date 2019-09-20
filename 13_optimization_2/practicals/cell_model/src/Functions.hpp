#ifndef CELL_MODEL_FUNCTIONS
#define CELL_MODEL_FUNCTIONS

#include <vector>
#include <pybind11/numpy.h>
namespace py = pybind11;

void diffusion(py::array_t<double> xn, py::array_t<double> yn, const double dt);
void boundaries(py::array_t<double> xn, py::array_t<double> yn, const double dt);
void interactions(py::array_t<double> xn, py::array_t<double> yn, 
                  const py::array_t<double> x, const py::array_t<double> y,
                  const double dt, const double size);


#endif
