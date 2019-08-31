#include "Functions.hpp"
#include "Simulation.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<double>);
PYBIND11_MAKE_OPAQUE(std::vector<Point>);

PYBIND11_MODULE(cell_model_cpp, m) {

  py::bind_vector<std::vector<double>>(m, "VectorDouble");
  py::bind_vector<std::vector<Point>>(m, "VectorPoint");

  py::class_<Point>(m, "Point")
      .def(py::init<>())
      .def(py::init<const double, const double>())
      .def_readwrite("x", &Point::x)
      .def_readwrite("y", &Point::y);

  py::class_<Simulation>(m, "Simulation")
      .def(py::init<const std::vector<double> &, const std::vector<double> &,
                    const double, const double>())
      .def("integrate", &Simulation::integrate)
      .def("get_positions", &Simulation::get_positions);
}
