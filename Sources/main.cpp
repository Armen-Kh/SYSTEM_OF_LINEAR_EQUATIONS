#include "sle_matrix.hpp"
#include "file_reader.hpp"
#include "file_writer.hpp"
#include "utility.hpp"
#include "gaussian_elimination.hpp"
#include "jacobi_method.hpp"
#include "gauss_seidel_method.hpp"

#include <iostream>

int main()
{
	File_Writer FW_G("../Data/SLE_Gauss_Solutions.txt");
	File_Writer FW_J("../Data/SLE_Jacobi_Solutions.txt");
	File_Writer FW_GS("../Data/SLE_Gauss_Seidel_Solutions.txt");
	Matrix A, B;
	Result X;
	float epsilon = 0.0001;          //also for the behavioral deviations of float number..

	{
	File_Reader FR_SLE("../Data/SLE.txt");
	while(Read_SLE(FR_SLE, A, B)) {
		Gaussian_Elimination(A, B, X, epsilon);
		Write_SLE_Solution(FW_G, X);
	}
	std::cout << "The result for Gaussian Elimination is presented in \"SLE_Gauss_Solutions.txt\" file (Data folder)!\n"; 
	}

	{
	File_Reader FR_SLE("../Data/SLE.txt");
	while(Read_SLE(FR_SLE, A, B)) {
		Jacobi_Method(A, B, X, epsilon);
		Write_SLE_Solution(FW_J, X);
	}
	std::cout << "The result for Gauss-Seidel Method is presented in \"SLE_Jacobi_Solutions.txt\" file (Data folder)!\n"; 
	}

	File_Reader FR_SLE("../Data/SLE.txt");
	while(Read_SLE(FR_SLE, A, B)) {
		Gauss_Seidel_Method(A, B, X, epsilon);
		Write_SLE_Solution(FW_GS, X);
	}
	std::cout << "The result for Gauss-Seidel Method is presented in \"SLE_Gauss_Seidel_Solutions.txt\" file (Data folder)!\n"; 
	
	return 0;
}
