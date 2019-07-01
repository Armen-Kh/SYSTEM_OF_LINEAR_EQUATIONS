#include "file_reader.hpp"

#include <fstream>
#include <cassert>
#include <cstddef>
#include <iostream>

File_Reader::File_Reader(const char* fn) :file_name(fn)
{
	fin.open(file_name, std::ios::in);
	assert(fin.is_open() && "File opening failure!");
}

File_Reader::~File_Reader()
{
	fin.close();
}

bool File_Reader::float_reading(float& f_out)
{
	if(fin >> f_out) {
		return true;
	}
	std::cout << "Unable to read a floating point number, possibly incomplete data or data type mismatch.\n";
	return false;
}

bool File_Reader::sizet_reading(std::size_t& s_out)
{
	if(fin >> s_out) {
		return true;
	}
	std::cout << "Unable to read a size_t data, possibly incomplete data or data type mismatch.\n";
	return false;
}

bool File_Reader::char_reading(char& c_out)
{
	if(fin >> c_out) {
		return true;
	}
	
	return false;
}

bool File_Reader::string_reading(std::string& s_out)
{
	if(!std::getline(fin, s_out)) {  //just reading '\n' symbol before line
	       	return false;
        }

	if(std::getline(fin, s_out)) {
		return true;
	}
	
	return false;
}
