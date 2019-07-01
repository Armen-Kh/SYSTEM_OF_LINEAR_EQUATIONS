#include "sle_matrix.hpp"
#include "jacobi_method.hpp"

#include <sstream>   //std::ostringstream
#include <iostream>
#include <cassert>
#include <cstddef>
#include <cstdlib>  //std::abs()
#include <utility>  //std::swap()

bool Check_Sufficient_Condition(Matrix&, Matrix&, Result&);
bool Iteration_Epsilon_Step(Matrix&, Matrix& B, Result&, Result&, float);

void Jacobi_Method(Matrix& A, Matrix& B, Result& X_out, float epsilon)
{
	assert(A.get_rows() == B.get_rows() && "size mismatch");

	X_out.set_number(A.get_number());
	X_out = Result(" ", 1, A.get_columns());
	Result X_prev(" ", 1, A.get_columns());
	for(std::size_t i = 0; i < X_prev.get_columns(); ++i) {
		X_prev(i) = 0;
	}
	int iteration_step = 1;

	if(!Check_Sufficient_Condition(A, B, X_out)) {
		return;
	}

	while(!Iteration_Epsilon_Step(A, B, X_out, X_prev, epsilon)) {
	       ++iteration_step;
	}

	std::ostringstream oss;
	oss << "Iteration steps: " << iteration_step;
	std::string info = oss.str();
	X_out.set_state(info);
}


bool Check_Sufficient_Condition(Matrix& A, Matrix& B, Result& X)
{
	assert(A.get_rows() == B.get_rows() && A.get_columns() == X.get_columns() && "size mismatch");
	
	std::size_t r = A.get_rows();
	std::size_t c = A.get_columns();
	if(r != c) {
		X.set_state("NSQ_Non-square matrix. (So you can apply another method for this system: for instance Gaussian Elimination.)");
                return false;
	}
	
	std::size_t k = 0;
	for(std::size_t i = 0; i < r && k < r; ++i) {
		float sum = 0; 
		for(std::size_t j = 0; j < c ;++j) {
			sum += std::abs(A(i, j));
		}
		if(std::abs(A(i, i)) <= sum - std::abs(A(i, i))) {
			++k;
			if(k >= r) {
				X.set_state("NSDD_A sufficient condition for the method to converge is not satisfied. The coefficinets matrix(A) is not strictly diagonally dominant. (So you can apply another method for this system: for instance Gaussian Elimination.)");
				return false;
			}	       
			A.Swap_Rows(i, k);
			std::swap(B(i, 0), B(k, 0));
			--i;
		}
		else {
			k = i + 1;
		}
	}

	return true;
}


bool Iteration_Epsilon_Step(Matrix& A, Matrix& B, Result& X, Result& X_prev, float epsilon)
{
	float max = 0;
	for(std::size_t i = 0; i < X.get_columns(); ++i) {
		float sum = 0;
		for(std::size_t j = 0; j < X.get_columns(); ++j) {
			sum += A(i, j) * X_prev(j);
		}
		X(i) = float(B(i, 0) - sum + A(i, i) * X_prev(i)) / A(i, i);

		float t = std::abs(X(i) - X_prev(i));
		max = (max > t) ? max : t;
	}

	if(max < epsilon) {
		return true;
	}

	for(std::size_t i = 0; i < X.get_columns(); ++i) {
		X_prev(i) = X(i);
	}	
	return false;
}

