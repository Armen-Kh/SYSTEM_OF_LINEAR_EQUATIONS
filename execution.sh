#!/bin/bash
export LD_LIBRARY_PATH=./Libs
if [ -z $1 ]; then
	echo "To generate output result files, use the "g" key."
	echo "To generate test result file for Gauss-Elimination, use the "t1" key."
	echo "To generate test result files for Gauss-Seidel and Jacobi methods, use the "t2" key."
elif [ $1 = "g" ]; then
	Bin/sle_solution.exe
elif [ $1 = "t1" ]; then
	Bin/test_gauss_comparator.exe
elif [ $1 = "t2" ]; then
	Bin/test_jacobi_gauss-seidel_comparator.exe
else
	echo "Error: Incorrect key!"
fi
