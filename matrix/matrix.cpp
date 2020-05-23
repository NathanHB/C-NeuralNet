#include "matrix.hpp"
#include <cstdio>
#include <iostream>
#include <random>
#include <vector>

Matrix::~Matrix(){}

Matrix::Matrix()
{
	rows = 0;
	cols = 0;
	data = {};
}

Matrix::Matrix(unsigned rows, unsigned cols)
	:rows{rows},
	cols{cols},
	length{ rows * cols },
	data (length)
{
}

Matrix::Matrix(unsigned rows, unsigned cols, std::vector<double> data)
	:rows{rows },
	cols{cols},
	length{ rows * cols },
	data{data}
{
}

Matrix::Matrix(const Matrix &m)
{
	rows = m.rows;
	cols = m.cols;
	length = m.length;
	data = m.data;
}

void Matrix::random_fill()
// fills the Matrix with normaliy distributed random numbers
{
	// generate a random device used by the mt19937 algorithm
	std::random_device rd;
	// instantiate the algorithm used to generate random numbers
	std::mt19937 mt(rd());
	// setup dist wich has a random distribution of mean 0 and variation 1
	std::normal_distribution<double> dist(0.0, 1.0);

	for (double& e : data)
		e = dist(mt);
}

void Matrix::print()
// prints the content of the Matrix using scientific notation
{
	std::printf("-----\n");
	for (unsigned i{0}; i < rows; ++i) {
		for(unsigned j{0};j < cols; ++j)
			std::printf("%11.4e", data[j + i * cols]);

		std::printf("\n");
	}

	std::printf("-----\n");
}

inline bool same_size(Matrix a, Matrix b)
// return true if the matrices have the same dimensions false otherwise
{
	return (a.cols == b.cols) && (a.rows == b.rows);
}

Matrix& Matrix::operator=(const Matrix& m)
{
	rows = m.rows;
	cols = m.cols;
	data = m.data;
	length = m.length;

	return *this;
}

Matrix& Matrix::operator+=(const Matrix &a)
// add the content of a to the this matrix and returns this
{
	if (!same_size(*this, a)) {
		throw "+: a and b are different sizes";
	}

	for (unsigned i = 0; i < a.length; ++i)
		data[i] += a.data[i];

	return *this;
}

Matrix& Matrix::operator-=(const Matrix &a)
{
	if (!same_size(*this, a)) {
		throw "+: a and b are different sizes";
	}

	for (unsigned i = 0; i < a.length; ++i)
		data[i] -= a.data[i];

	return *this;
}

Matrix& Matrix::operator/=(int k)
{
// TODO: verify if k == 0

	for (unsigned i = 0; i < length; ++i)
		data[i] /= k;

	return *this;
}

Matrix& Matrix::operator*=(int k)
{
	for (unsigned i = 0; i < length; ++i)
		data[i] *= k;

	return *this;
}

Matrix& Matrix::operator+=(int k)
{
	for (unsigned i = 0; i < length; ++i)
		data[i] += k;

	return *this;
}

Matrix& Matrix::operator-=(int k)
{
	for (unsigned i = 0; i < length; ++i)
		data[i] -= k;
	return *this;
}

Matrix& Matrix::operator%=(const Matrix &a)
// multiply element-wise the content of a to the this matrix and returns this
{
	if (!same_size(*this, a)) {
		throw "+: a and b are different sizes";
	}

	for (unsigned i = 0; i < a.length; ++i)
		data[i] *= a.data[i];

	return *this;
}

Matrix &Matrix::operator*=(const Matrix &a)
{
	std::vector<double> res(rows * a.cols);

	for (unsigned i = 0; i < rows; ++i)
		for (unsigned j = 0; j < a.cols; ++j)
			for (unsigned z = 0; z < cols; ++z)
				res[j + i * a.cols] += data[i * cols + z] * a.data[z * a.cols + j];

	cols = a.cols;
	length = rows * cols;
	data = res;
	return *this;
}

Matrix &Matrix::apply(double func(double))
{
	for (auto &e: data)
		e = func(e);

	return *this;
}

Matrix &operator+(Matrix a, Matrix b) {return (a += b);}
Matrix &operator-(Matrix a, Matrix b) {return (a -= b);}
Matrix &operator%(Matrix a, Matrix b) {return (a %= b);}
Matrix &operator*(Matrix a, Matrix b) {return (a *= b);}

Matrix &operator+(Matrix a, int k) {return (a += k);}
Matrix &operator-(Matrix a, int k) {return (a -= k);}
Matrix &operator*(Matrix a, int k) {return (a *= k);}
Matrix &operator/(Matrix a, int k) {return (a /= k);}

Matrix Matrix::t()
{
	Matrix transpose{cols, rows};

	for (unsigned i = 0; i < rows; ++i)
		for (unsigned j = 0; j < cols; ++j)
			transpose.data[i + j * rows] = data[j + i * cols];

	return transpose;
}

bool Matrix::operator==(const Matrix &m)
{
	return (same_size(*this, m) && data == m.data);
}

bool Matrix::operator!=(const Matrix &m)
{
	return !(*this == m);
}
