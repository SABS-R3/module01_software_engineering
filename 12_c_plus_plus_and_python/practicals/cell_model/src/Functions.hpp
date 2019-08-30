#ifndef CELL_MODEL_FUNCTIONS
#define CELL_MODEL_FUNCTIONS

#include <vector>

void diffusion(std::vector<double>& xn, std::vector<double>& yn, const double dt);
void boundaries(std::vector<double>& xn, std::vector<double>& yn, const double dt);
void interactions(std::vector<double>& xn, std::vector<double>& yn, 
                  const std::vector<double>& x, const std::vector<double>& y,
                  const double dt, const double size);


#endif
