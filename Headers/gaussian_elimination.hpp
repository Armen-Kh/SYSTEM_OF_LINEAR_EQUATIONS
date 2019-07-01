#ifndef GAUSSIAN_ELIMINATION_HPP
#define GAUSSIAN_ELIMINATION_HPP

#include "sle_matrix.hpp"

#include <string>

//solution of a system of linear equations by Gauss elimination
//1st input_parameter: System coefficients matrix (A)
//2nd input_parameter: vector (B)
//3rd output_parameter: solution vector (X)
//4th input_parameter: epsilon. epsilon is necessary to take into account the behavioral deviations of float number.
void Gaussian_Elimination(Matrix&, Matrix&, Result&, float);

#endif
