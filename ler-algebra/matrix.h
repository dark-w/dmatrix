#pragma once

#include <vector>

#include <iostream>

class Matrix {
public:
	Matrix(int rows, int cols, float init_value = 0);
	Matrix(const Matrix&);
	Matrix(std::initializer_list<std::initializer_list<double>>);
	Matrix();

	Matrix& operator=(const Matrix& rhs);
	Matrix& operator*=(const Matrix& rhs);
	double& operator()(int x, int y);
	const double& operator()(int x, int y) const;

	int get_rows() const { return _rows; }
	int get_cols() const { return _cols; }

	Matrix get_identity() const;
	Matrix get_permutation(std::initializer_list<std::pair<int, int>>) const;
	Matrix get_inverse_by_Guass_Jordan_elimination() const;
	std::pair<Matrix, Matrix> get_LU() const;

	Matrix& exchange_two_rows(int, int);
	Matrix& transpose();

	friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
	friend Matrix solve(const Matrix& A, const Matrix& X);

	~Matrix() {
		for (int i = 0; i < _rows; i++)
			delete[] _data[i];
		
		delete[] _data;
	}

private:
	int _rows;
	int _cols;
	double** _data;
};

std::ostream& operator<<(std::ostream& out, const Matrix& m);
Matrix operator*(const Matrix&, const Matrix&);

Matrix solve(const Matrix& A, const Matrix& X);

//class MatrixCompute {
//	
//};
