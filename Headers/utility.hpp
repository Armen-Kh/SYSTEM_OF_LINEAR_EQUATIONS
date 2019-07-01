#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "sle_matrix.hpp"
#include "file_reader.hpp"
#include "file_writer.hpp"

#include <string>

bool Read_SLE(File_Reader&, Matrix&, Matrix&);

//The class Result describes the solution of a system of linear equations.
//The function simply reads the solution data and assigns it to the corresponding class Result object.
bool Read_Result(File_Reader&, Result&);

bool Write_SLE_Solution(File_Writer&, const Result&);

#endif

