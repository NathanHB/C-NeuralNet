#include "idx_header.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cerr << "Usage: ./parser <idx file> <idx file>\n";
		exit(EXIT_FAILURE);
	}

	Idx_file file1 {argv[1]};
	Idx_file file2 {argv[2]};

	return 0;
}
