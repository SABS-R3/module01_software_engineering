#include <iostream>
#include <complex>

int main() {
  const double max = 2.0;
  const int n = 100;
  const double incr = max / n;
  const int max_iterations = 2000;

  int counter = 0;
  for (int i = -n; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      const std::complex<double> c(incr*i, incr*j);
      auto z = c;
      for (int k = 0; k < max_iterations; ++k) {
        z = std::pow(z,2) + c;
      }
      if (std::abs(z) <= 2.0) {
        counter++;
      }
    }
  }
  const double area = 2 * counter * std::pow(incr,2);
  std::cout << "mandelbrot area is " << area << std::endl;
}
