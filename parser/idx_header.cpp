#include "idx_header.hpp"
#include <iostream>
#include <fstream>

int32_t int32_from_chars(unsigned char *byte_stream) {
	int32_t result{};

	for (size_t i{}; i < 4; ++i) {
		int32_t tmp = (int32_t)(byte_stream[i] << (8 * (3 - i)));
		result += tmp;
	}
	return result;
}

std::streampos Idx_file::parse_header(unsigned char *byte_stream) {

	hdr.data_type = byte_stream[2];
	hdr.number_of_dims = byte_stream[3];

	hdr.dims = new int32_t[hdr.number_of_dims]{};

	for (size_t i{4}, j{}; i < (size_t)(4 + (4 * hdr.number_of_dims)); i += 4, ++j){
		int32_t tmp {int32_from_chars(byte_stream + i)};
		hdr.dims[j] = tmp;
	}

	return (4 + (4 * hdr.number_of_dims));
}

char *Idx_file::open_file(const char *file_path) {
	std::streampos p{};
	std::ifstream file (file_path, std::ios::binary | std::ios::in | std::ios::ate);

	if (file.is_open()) {
		p = file.tellg();
		char *byte_stream = new char[p]{};
		file.seekg(0, std::ios::beg);
		file.read(byte_stream, p);
		file.close();
		return byte_stream;
	}

	std::cerr << "Error while reading the file.\n";
	exit(EXIT_FAILURE);
}

Idx_file::Idx_file(const char *file_path){
	// open it
	char *byte_stream = open_file(file_path);
	// parse the header
	hdr.file_path = file_path;
	std::streampos p = parse_header((unsigned char *)byte_stream);
	// put data in
	data = (unsigned char *)(byte_stream + p);
	delete[] byte_stream;
	print_header();
}

Idx_file::~Idx_file() {
	delete[] hdr.dims;
}

void Idx_file::print_header() {
	std::cout << "---- File Header ----\n";
	std::cout << hdr.file_path << "\n";
	std::cout << "Data Type: " << +hdr.data_type << "\n";
	std::cout << "Number of dims: " << +hdr.number_of_dims << "\n";

	for (size_t i{}; i < hdr.number_of_dims; ++i)
		std::cout << "Dim " << i << ": " << hdr.dims[i] << "\n";
	std::cout << std::endl;
}
