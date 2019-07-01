#ifndef FILE_WRITER_HPP
#define FILE_WRITER_HPP

#include <cstddef>
#include <fstream>
#include <string>

//write information to file
class File_Writer {

public:
	File_Writer(const char *);
	~File_Writer();

	bool float_writing(const float&);
	bool sizet_writing(const std::size_t&);
	bool char_writing(const char&);
	bool string_writing(const std::string&);
public:
	const char* file_name;
	std::ofstream fout;
};

#endif
