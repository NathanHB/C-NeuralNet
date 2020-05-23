#ifndef MATRIX_H
#define MATRIX_H
#include <cstddef>
#include <vector>

class Matrix {
	unsigned rows{}, cols{}, length{};
	std::vector<double> data;

	public:

	// constructors
	// if only two args are given the matrice is initialized with 0s
	Matrix();
	Matrix(unsigned rows, unsigned cols);
	Matrix(unsigned rows, unsigned cols, std::vector<double> data);
	Matrix(const Matrix &);

	virtual ~Matrix();

	// deconstructor
	//~Matrix();

	//getter
	unsigned get_rows() {return rows;};
	unsigned get_cols() {return cols;};
	unsigned get_length() {return length;};
	std::vector<double> get_data() { return data; };

	void print();

	// fill the Matrix with random normalized values
	void random_fill();

	//verify that the matrices are the same size
	friend inline bool same_size(Matrix, Matrix);

	bool operator==(const Matrix&);
	bool operator!=(const Matrix&);

	Matrix& operator=(const Matrix&);

	Matrix& operator+=(const Matrix &);
	Matrix& operator-=(const Matrix &);
	Matrix& operator*=(const Matrix &); // does Matrix dot product
	Matrix& operator%=(const Matrix &);// element-wise multiplication

	Matrix& operator+=(int);
	Matrix& operator-=(int);
	Matrix& operator/=(int);
	Matrix& operator*=(int); // does Matrix product with scalar

	friend Matrix &operator+(Matrix a, Matrix b);
	friend Matrix &operator-(Matrix a, Matrix b);
	friend Matrix &operator%(Matrix a, Matrix b);
	friend Matrix &operator*(Matrix a, Matrix b);

	friend Matrix &operator+(Matrix a, int);
	friend Matrix &operator-(Matrix a, int);
	friend Matrix &operator/(Matrix a, int);
	friend Matrix &operator*(Matrix a, int);

	// return transpose of the Matrix
	Matrix t();

	// apply func element-wise to the Matrix and returns a new one
	Matrix& apply(double func (double));
};

#endif
