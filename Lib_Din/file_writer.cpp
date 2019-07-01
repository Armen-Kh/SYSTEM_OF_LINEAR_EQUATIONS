#include "file_writer.hpp"

#include <cassert>
#include <cstddef>
#include <string>
#include <fstream>

File_Writer::File_Writer(const char* fn) : file_name(fn)
{
	fout.open(file_name, std::ios::out);
	assert(fout.is_open() && "File openning failure!");
}

File_Writer::~File_Writer()
{
	fout.close();
}

bool File_Writer::float_writing(const float& f)
{
	if(fout << f) {
		return true;
	}
	return false;
}

bool File_Writer::sizet_writing(const std::size_t& s)
{
	if(fout << s) {
		return true;
	}
	return false;
}

bool File_Writer::char_writing(const char& c)
{
	if(fout << c) {
		return true;
	}
	return false;
}

bool File_Writer::string_writing(const std::string& s)
{
	if(fout << s) {
		return true;
	}
	return false;
}
