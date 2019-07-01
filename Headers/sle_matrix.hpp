#ifndef SLE_MATRIX_HPP
#define SLE_MATRIX_HPP

#include <cstddef>    //size_t
#include <string>

//Matrix class is used to describe the system's coefficients (A)
class  Matrix {

public:
	Matrix();
	Matrix(std::size_t i, std::size_t j = 0);

	//Matrix(Matrix&&);
	//Matrix& operator=(Matrix&&);

	Matrix(const Matrix&);
	Matrix& operator=(const Matrix&);

	~Matrix();

	void Swap_Rows(std::size_t, std::size_t);

	float& operator()(std::size_t, std::size_t);
	const float& operator()(std::size_t, std::size_t) const;
	
	float& operator()(std::size_t);
	const float& operator()(std::size_t) const;

	std::size_t get_rows() const;
	std::size_t get_columns() const;
	std::size_t get_size() const;
	std::size_t get_number() const;

	void set_rows(std::size_t);
	void set_columns(std::size_t);
	void set_size(std::size_t);
	void set_number(std::size_t);

private:
	std::size_t rows;
	std::size_t columns;
	std::size_t size;
	std::size_t number;
	float ** data;
};

//The class Result describes the solution of a system of linear equations.
class Result : public Matrix
{
public:
        Result();
        Result(std::string s, std::size_t r, std::size_t c);
	
	Result(const Result&);
	Result& operator=(const Result&);

        void set_state(std::string s);
        std::string get_state() const;

private:
        std::string state;
};

#endif
