#include "sle_matrix.hpp"

#include <iostream>
#include <algorithm>
#include <iostream>
#include <cstdlib>  //std::fabs() or std::abs()
#include <cstddef>
#include <cassert>
#include <cstdint>  //int64_t
#include <string>

void Create_Augmented_Matrix(Matrix&, Matrix&, Matrix&);
void Variable_Elemination(Matrix&);    //changing to upper triangular matrix besides last column 
void Backward_Substitution(Matrix&, Result&, float);


void Gaussian_Elimination (Matrix& A, Matrix& B, Result& X_out, float epsilon)  //epsilon is necessary to take into account the behavioral deviations of float number..
{
	X_out = Result(" ", 1, A.get_columns());
	X_out.set_number(A.get_number());
	
	assert(A.get_rows() == B.get_rows() && A.get_columns() == X_out.get_size() && "size mismartch!");
	
	std::size_t height = A.get_rows();
	std::size_t width = A.get_columns() + 1;

	Matrix AM(height, width);

	Create_Augmented_Matrix(A, B, AM);
	Variable_Elemination(AM);
	Backward_Substitution(AM, X_out, epsilon);	
}


void Create_Augmented_Matrix(Matrix& A, Matrix& B, Matrix& AM_out) {
	assert(A.get_rows() == B.get_rows() && "size mismatch!");
	assert(AM_out.get_rows() == A.get_rows() && (AM_out.get_columns() == A.get_columns() + 1) && "size mismatch!");

	std::size_t r = A.get_rows();
	std::size_t c = A.get_columns();

	for(std::size_t i = 0; i < r; ++i) {
		for(std::size_t j = 0; j < c; ++j) {
			AM_out(i, j) = A(i, j);
		}
		AM_out(i, c) = B(i, 0);
	}
}


void Variable_Elemination(Matrix& AM) 
{
	std::size_t height = AM.get_rows();
        std::size_t width = AM.get_columns();
	std::size_t m = std::min(height, width - 1);

	for (std::size_t j = 0; j < m; ++j) {
		std::size_t w = j + 1;
		while (0 == AM(j, j) && w < height) {
			if(0 != AM(w, j)) {
				AM.Swap_Rows(j, w);
			}
			else {
				++w;
			}
		}

		if(w == height) {
			continue;
		}

		for (std::size_t i = j + 1; i < height; ++i) {
			float temp = (-1) * AM(i, j) / AM(j, j);
			AM(i, j) = 0;
			for(std::size_t k = j + 1; k < width; ++k) {
				AM(i, k) += temp * AM(j, k);
			}
		}
	}
}


void Backward_Substitution(Matrix& AM, Result& X_out, float epsilon)  //epsilon is necessary to take into account the behavioral deviations of float number..
{
	int count = 0;
	X_out.set_state("SS_The system has a single unique solution!");
	std::size_t height = AM.get_rows();
	std::size_t width = AM.get_columns();

	assert(X_out.get_columns() == width - 1 && "Size mismatch!\n");

      	// case: height >= width
	for (int64_t i = height - 1; i >= width - 1; --i) {
                if(std::abs(0 - AM(i, width - 1)) > epsilon) {        //epsilon accuracy
                        X_out.set_state("NS_The system has no solution!");
                        return;
                }
        }

	// case: height < width
	for(int64_t j = width - 2; j > height - 1; --j) {
		X_out(j) = 0;
		for(int64_t i = height - 1; i >= 0; --i) {
			AM(i, j) = 0;
		}
                X_out.set_state("IS_The system has infinitely many solutions! Here is one of them.");
	}

	std::size_t m = std::min(height - 1, width - 2);
	for(int64_t i = m; i >= 0; --i) {
                float s = 0;
                for(std::size_t j = i + 1; j < width - 1; ++j) {
                        s += AM(i, j);
                }

                if(0 == AM(i, i)) {
                        if(std::abs(s - AM(i, width - 1)) > epsilon) {
                                X_out.set_state("NS_The system has no solution!");
                                return;
                        }
                        else {
                                X_out(i) = 0;
                                for(int64_t k = i - 1; k >= 0; --k) {
                                        AM(k, i) = 0;
                                }
                		X_out.set_state("IS_The system has infinitely many solutions! Here is one of them.");
                        }
                }
                else { 
                        X_out(i) =( AM(i, width - 1) - s)/ AM(i, i);
			for(int64_t k = i - 1; k >= 0; --k) {
                                AM(k, i) *= X_out(i);
                        }
                }
        }
}
