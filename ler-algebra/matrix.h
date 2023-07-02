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

	Matrix identity() const;
	Matrix inverse_by_Guass_Jordan_elimination() const;
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
