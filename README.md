#Solving a system of linear equations using Gaussian elimination, Gauss-Seidel, and Jacobi methods.

The project consists of three parts.
1. The first part generates two shared libraries (libdinsle.so, libdinsle_gsj.so) wich will be in Libs folder.
	The first one provides File_Reader, File_Writer, Matrix and Result classes, also Read_Sle, Read_Result, Write_Sle_Solution Functions.
	The second library provides Gaussian elimination, Gauss-Seidel, and Jacobi methods implementation units.
2. The second part creates Bin folder executable files, the execution of which generates output files containing appropriate solution of the system of linear equations read from input files.
3. The third part is testing. In this phase a comparative analysis of Golden output and result files is provided.

Each part has its own "makefile" which runs from ./Lib_Din, ./Lib_SLE_GSJ_Din, SYSTEM_OF_LINEAR_EQUATIONS, ./Test folders for creation of the appropriate execution files.
And after generation of the needed program units execution files they can be run just by running "execution.sh" bash script file following message instructions.
All input and output (also test results) data files are in Data folder. 


##folder/Lib_Din: (libdinsle.so prerequisites)
	file_reader.cpp:
		class File_Reader  //read info from file

	file_writer.cpp:
		class File_Writer  //write information to file

	sle_matrix.cpp:
		class Matrix  //Matrix class is used to describe the system's coefficients (A) and free members (B) 
			
		class Result   //The class Result describes the solution (X) of the system of linear equations.

	utility.cpp:
		//The function reads the coefficients(A) and b vector as matrices. 
		bool Read_SLE(File_Reader&, Matrix&, Matrix&);
		
		//The function simply reads the solution data and assigns it to the corresponding class Result object methods.e
		bool Read_Result(File_Reader&, Result&);
	
		// writes solutions in the file
		bool Write_SLE_Solution(File_Writer&, const Matrix&);

##folder/Lib_SLE_GSJ_Din: (libdinsle_gsj.so prerequisites)
	gaussian_elimination.cpp:
		
	gauss_seidel_method.cpp:
		
	jacobi_method.cpp:
		

##folder/Sources:
	main.cpp:
		Reads the system of linear equations as a matrix from "SLE.txt", and writes appropriate solutions for each method in the appropriate output files ("SLE_Gauss_Solutions.txt", "SLE_Jacobi_Solutions.txt", "SLE_Gauss_Seidel_Solutions.txt").

	
##folder/Test:
	test_gauss_comparator.cpp, test_jacobi_gauss-seidel_comparator.cpp
		Here is the comparative analysis(used epsilon precision) of the following files:
			Golden_Gauss_Methodhe․cpp --->  SLE_Gauss_Solutions.cpp (test results are represented in "test_gauss_comparator.cpp" file (Data folder)),
			Golden_Gauss-Seidel_Jacobi_Methods․cpp --->  SLE_Gauss_Seidel_Solutions.cpp (test results are represented in "test_gauss-seidel_comparator.cpp" file (Data folder)),
			Golden_Gauss-Seidel_Jacobi_Methods․cpp --->  SLE_Jacobi_Solutions.cpp (test results are represented in "test_jacobi_comparator.cpp" file (Data folder)),



