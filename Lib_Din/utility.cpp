#include "file_reader.hpp"
#include "file_writer.hpp"
#include "sle_matrix.hpp"

#include <iostream>
#include <cstddef>
#include <cassert>

bool Read_Matrix_Size (File_Reader& fr, Matrix& M) 
{
       	char c;
	std::size_t row, col;
        if(fr.char_reading(c) && fr.char_reading(c) &&
           fr.sizet_reading(row) && fr.char_reading(c) &&
           fr.sizet_reading(col) && fr.char_reading(c)) {
		M = Matrix(row, col);
		return true;
        }
        else {
                return false;
        }
}

bool Read_Matrix_Data(File_Reader& fr, Matrix& M) 
{
	char c;
	for(std::size_t i = 0; i < M.get_rows(); ++i) {
                for(std::size_t j = 0; j < M.get_columns(); ++j) {
                        if(!(fr.float_reading(M(i, j)) && fr.char_reading(c))) {
				return false;
                        }
                }
        }
	return true;
}

bool Read_SLE(File_Reader& fr, Matrix& A, Matrix& B)
{
	char c;
	std::size_t number;

	if(!(fr.char_reading(c) && fr.sizet_reading(number))) {
		return false;
	}
	if(c != '#') {				//This means, that instead of current SLE number there is a other symbol or data.. 
		std::cout << "Possibly incomplete data or data type mismatch.\n"; 
	}
	
	if(!(Read_Matrix_Size(fr, A) && Read_Matrix_Data(fr, A))) {
		return false;
	}

	if(!(Read_Matrix_Size(fr, B) && Read_Matrix_Data(fr, B))) {
                return false;
	}

	A.set_number(number);
	B.set_number(number);

        assert(A.get_rows() == B.get_rows() && "Size mismatch!");
               
	return true;
}


bool Read_Result(File_Reader& fr, Result& R)
{
        std::string s;
        char c;
        std::size_t m, n;
        float f;
        if(!(fr.char_reading(c) && fr.sizet_reading(n))) {
                return false;
        }
        R.set_number(n);

        if(!fr.string_reading(s)) {
                return false;
        }
	//if("NS_The system has no solution!" == s) {
	if('N' == s[0]) {
		return true;
	}

        if(!(fr.char_reading(c) && fr.char_reading(c) && fr.sizet_reading(m) &&
                       fr.char_reading(c) && fr.sizet_reading(n) && fr.char_reading(c))) {
                return false;
        }

        R = Result(s, m, n);

        for(std::size_t i = 0; i < R.get_size(); ++i) {
                if(!(fr.float_reading(f) && fr.char_reading(c))) {
                        return false;
                }
                R(i) = f;
        }

	return true;
}


bool Write_SLE_Solution(File_Writer& fw,const Result& X)
{
	if(!(fw.char_writing('#') && fw.sizet_writing(X.get_number()) && fw.char_writing('\n'))) {
		return false;
	}

	if(!(fw.string_writing(X.get_state()) && fw.char_writing('\n'))) {
		return false;
	}

	if('N' == X.get_state()[0]) {
		if(!fw.string_writing("\n")) {
			return false;
		}
		return true;
	}

	if(!(fw.string_writing("X(") && fw.float_writing(X.get_rows()) &&
	   fw.char_writing('x') && fw.float_writing(X.get_columns()) &&
	   fw.string_writing(")\n"))) {
                return false;
        }

	for(std::size_t i = 0; i < X.get_size(); ++i) { 
		if(!(fw.float_writing(X(i)) && fw.string_writing(", "))) {
			return false;
		}
	}
       
	if(!fw.string_writing("\n\n")) {
                return false;
        }

	return true;
}





