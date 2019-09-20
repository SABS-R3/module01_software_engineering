#include "Functions.hpp"
#include <random>

std::default_random_engine generator;

void diffusion(py::array_t<double> xn_arg, py::array_t<double> yn_arg,
               const double dt) {

  auto xn = xn_arg.mutable_unchecked<1>();
  auto yn = yn_arg.mutable_unchecked<1>();

  std::normal_distribution<double> normal;

  const double c = std::sqrt(2.0 * dt);

  for (size_t i = 0; i < xn.size(); ++i) {
    xn[i] += c * normal(generator);
    yn[i] += c * normal(generator);
  }
}
void boundaries(py::array_t<double> xn_arg, py::array_t<double> yn_arg,
                const double dt) {

  auto xn = xn_arg.mutable_unchecked<1>();
  auto yn = yn_arg.mutable_unchecked<1>();
  for (size_t i = 0; i < xn.size(); ++i) {
    if (xn[i] < 0.0) {
      xn[i] = 1.0 + xn[i];
    } else if (xn[i] > 1.0) {
      xn[i] = xn[i] - 1.0;
    }
    if (yn[i] < 0.0) {
      yn[i] = 1.0 + yn[i];
    } else if (yn[i] > 1.0) {
      yn[i] = yn[i] - 1.0;
    }
  }
}
void interactions(py::array_t<double> xn_arg, py::array_t<double> yn_arg,
                  py::array_t<double> x_arg, py::array_t<double> y_arg,
                  const double dt, const double size) {
  auto x = x_arg.unchecked<1>();
  auto y = y_arg.unchecked<1>();
  auto xn = xn_arg.mutable_unchecked<1>();
  auto yn = yn_arg.mutable_unchecked<1>();
  for (size_t i = 0; i < xn.size(); ++i) {
    for (size_t j = 0; j < xn.size(); ++j) {
      const double dx_x = x[i] - x[j];
      const double dx_y = y[i] - y[j];
      const double r = std::sqrt(std::pow(dx_x, 2) + std::pow(dx_y, 2));
      if (r > 0.0) {
        const double tmp = (dt / size) * std::exp(-r / size) / r;
        xn[i] += tmp * dx_x;
        yn[i] += tmp * dx_y;
      }
    }
  }
}
