#ifndef IDX_HEADER_H
#define IDX_HEADER_H
#include <string_view>
#include <vector>
#include <iostream>

struct Idx_header {
	const char *file_path{};
	// type of the data usualy unsigned char
	unsigned char data_type{};
	// number of dimensions of the data
	unsigned char number_of_dims{};
	// exemple for 10,000 28 by 28 images:
	// number of dims = 3
	// dims = {10000, 28, 28}
	// list of the dimensions
	std::vector<int32_t> dims;
};

class Idx_file {
	// header of the file, kept in struct because easier to pass around
	Idx_header hdr;
	// where the actual data is kept without the header
	unsigned char *byte_stream;
	std::vector<unsigned char> data;

	// opens the idx file and reuturn the stream of bytes
	static unsigned char *open_file(const char *);

	// used by the constructor to parse the file given in parameter of the
	// constructor
	std::streampos parse_header(unsigned char *);

public:
	//construct for Idx_file arg is the file path to the idx file
	Idx_file(const char *file_path);

	// deconstructor
	~Idx_file();

	// print the header info of the file
	void print_header();

	//getters
	Idx_header get_header() { return hdr; };
	std::vector<unsigned char> get_data() { return data; };
};

#endif
