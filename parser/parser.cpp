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

	auto data {file1.get_data()};

	for (unsigned i = 0; i < 28; ++i) {
		for (unsigned j = 0; j < 28; ++j)
			printf("%s ", (data[j + i * 28] == 0 ? "." : "0"));
		printf("\n");
	}

	return 0;
}
