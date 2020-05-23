#include "network.hpp"
#include "../matrix/matrix.hpp"
#include <vector>
#include <iostream>

int main(void)
{
	Network net {4, std::vector<unsigned> {2, 10, 5, 1}};
	net.print();

	Matrix inputs{2, 1};
	inputs.random_fill();

	std::cout << "\noutputs" << std::endl;
	(net.feed_forward(inputs)).print();
	return 0;
}
