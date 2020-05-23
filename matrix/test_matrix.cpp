#include "matrix.hpp"
#include <iostream>

std::vector<double> data1 {2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};
unsigned row1 = 4;
unsigned col1 = 2;

std::vector<double> data2 {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
unsigned row2 = 2;
unsigned col2 = 3;

int main(void)
{
	Matrix m1{row1, col1, data1};
	Matrix m2{row2, col2, data2};
	m1.print();
	m2.print();

	m1 *= m2;
	m1.print();
	m1.t().print();

	return 0;
}
