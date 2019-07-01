#include "sle_matrix.hpp"

#include <iostream>
#include <cstddef>
#include <cassert>
#include <utility>   //std::swap


Matrix::Matrix()
	:rows(0), columns(0), size(0), number(0), data(nullptr)
{
}

Matrix::Matrix(std::size_t r, std::size_t c)
	:rows(r), columns(c), size(r * c)
{
	if(0 == columns) {
		columns = rows;
		rows = 1;
		size = columns;
	}

	data = new float*[rows];
	for(std::size_t i = 0; i < rows; ++i) {
		data[i] = new float[columns];
	}
}	

Matrix::Matrix(const Matrix& M)
	:rows(M.rows), columns(M.columns), size(M.size), number(M.number), data(new float*[M.rows])
{
	for(std::size_t i = 0; i < rows; ++i) {
		data[i] = new float[columns];
		for(std::size_t j = 0; j < columns; ++j) {
			data[i][j] = M.data[i][j];
		}	
	}
}

Matrix& Matrix::operator=(const Matrix& M)
{
	if(&M == this) {
		return *this;
	}

	for(std::size_t i = 0; i < rows; ++i) {
                delete[] data[i];
        }
        delete[] data;

	rows = M.rows;
	columns = M.columns;
	size = M.size;

	data = new float*[rows];
	for(std::size_t i = 0; i < rows; ++i) {
                data[i] = new float[columns];
                for(std::size_t j = 0; j < columns; ++j) {
                        data[i][j] = M.data[i][j];
                }
        }

	return *this;
}

Matrix::~Matrix()
{
	for(std::size_t i = 0; i < rows; ++i) {
		delete[] data[i];
	}
	delete[] data;
}

void Matrix::Swap_Rows(std::size_t i, std::size_t j)
{
	assert(i >= 0 && i < rows && "The Row index is out of range!\n");
	assert(j >= 0 && j < rows && "The row index is out of range!\n");

	if(i == j) { return; }

	std::swap(data[i], data[j]);
}

float& Matrix::operator()(std::size_t i, std::size_t j)
{
	return data[i][j];
}

const float& Matrix::operator()(std::size_t i, std::size_t j) const
{
	return data[i][j];
}

//vector represented as 1xn matrix, thus operator(with single parameter) returns elements from first row when we use it with mxn (m!=1) matrix
float& Matrix::operator()(std::size_t i)  
{
	return data[0][i];
}

//vector represented as 1xn matrix, thus operator(with single parameter) returns elements from first row when we use it with mxn (m!=1) matrix
const float& Matrix::operator()(std::size_t i) const
{
	return data[0][i];
}

std::size_t Matrix::get_rows() const { return rows; }
std::size_t Matrix::get_columns() const { return columns; }
std::size_t Matrix::get_size() const { return size; }
std::size_t Matrix::get_number() const {return number; }

void Matrix::set_rows(std::size_t r) { rows = r; }
void Matrix::set_columns(std::size_t c) { columns = c; }
void Matrix::set_size(std::size_t s) { size = s; }
void Matrix::set_number(std::size_t n) { number = n; }


Result::Result () : Matrix(), state("")
        {
        }

Result::Result(std::string s, std::size_t r, std::size_t c)
                : Matrix(r, c), state(s)
        {
	}

Result::Result(const Result& R) 
	:Matrix(R) , state(R.state) 
{
}

Result& Result::operator=(const Result& R)
{
	Matrix::operator=(R);
	state = R.state;

	return *this;
}


void Result::set_state(std::string s) { state = s; }
std::string Result::get_state() const { return state; }

