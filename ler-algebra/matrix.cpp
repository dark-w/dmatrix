#include "matrix.h"

#include <iostream>

double EPS = 1e-10;

Matrix::Matrix(int rows, int cols, float init_value)
	: _rows(rows), _cols(cols) {
	_data = new double*[_rows];

	for (int i = 0; i < _rows; i++) {
		_data[i] = new double[_cols];
		for (int j = 0; j < _cols; j++) {
			_data[i][j] = init_value;
		}
	}
}

Matrix::Matrix(const Matrix& m)
	: _rows(m._rows), _cols(m._cols) {
	_data = new double*[_rows];

	for (int i = 0; i < _rows; i++) {
		_data[i] = new double[_cols];
		for (int j = 0; j < _cols; j++) {
			_data[i][j] = m._data[i][j];
		}
	}
}

Matrix::Matrix()
	: _rows(1), _cols(1) {
	_data = new double*[_rows];

	for (int i = 0; i < _rows; i++) {
		_data[i] = new double[_cols];
	}
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> data_list) {
	_rows = data_list.size();
	_cols = data_list.begin()->size();

	_data = new double*[_rows];

	auto itr = data_list.begin();
	for (int i = 0; i < _rows; i++, itr++) {
		_data[i] = new double[_cols];
		std::copy(itr->begin(), itr->end(), _data[i]);
	}
}

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
	for (int i = 0; i < m._rows; i++) {
		for (int j = 0; j < m._cols; j++) {
			out << m._data[i][j] << ' ';
		}
		out << std::endl;
	}

	return out;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
	Matrix temp(lhs);
	return (temp *= rhs);
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
	if (rhs._rows != _cols) {
		std::cout << "rhs._rows != _cols" << std::endl;
		throw "rhs._rows != _cols";
	}

	Matrix ret_matrix(_rows, rhs._cols);
	for (int i = 0; i < ret_matrix._rows; i++) {
		for (int j = 0; j < ret_matrix._cols; j++) {
			for (int k = 0; k < _cols; k++) {
				ret_matrix._data[i][j] += _data[i][k] * rhs._data[k][j];
			}
		}
	}

	return (*this = ret_matrix);
}

Matrix& Matrix::operator=(const Matrix& rhs) {
	if (&rhs == this)
		return *this;

	if (_cols != rhs._cols || _rows != rhs._rows) {
		for (int i = 0; i < _rows; i++) {
			delete[] _data[i];
		}
		delete[] _data;

		_rows = rhs._rows;
		_cols = rhs._cols;
		_data = new double*[_rows];
		for (int i = 0; i < _rows; i++) {
			_data[i] = new double[_cols];
			for (int j = 0; j < _cols; j++) {
				_data[i][j] = rhs._data[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < _rows; i++) {
			for (int j = 0; j < _cols; j++) {
				_data[i][j] = rhs._data[i][j];
			}
		}
	}

	return *this;
}

double& Matrix::operator()(int x, int y) {
	return _data[x][y];
}

const double& Matrix::operator()(int x, int y) const {
	return _data[x][y];
}

// it only works for square matrix
Matrix solve(const Matrix& A, const Matrix& b) {
	// Guassian elimination
	Matrix U(A);
	Matrix B(b);

	for (int i = 0; i < U._rows; i++) {
		if (U(i, i) == 0) {
			std::cout << "pls check the A matrix, it looks not right." << std::endl;
			throw "pls check the A matrix, it looks not right.";
		}

		for (int j = i + 1; j < U._rows; j++) {
			double ec = U(j, i) / U(i, i);
			std::cout << "ec: " << ec << std::endl;
			for (int k = i + 1; k < U._cols; k++) {
				U(j, k) = U(j, k) - ec * U(i, k);
			}

			B(j, 0) = B(j, 0) - ec * B(i, 0);
			U(j, i) = 0;
		}
	}
	// std::cout << B;

	// back substitution
	Matrix X(A._rows, 1);
	X(A._rows - 1, 0) = B(B._rows - 1, 0) / U(A._rows - 1, A._cols - 1);
	
	for (int i = A._rows - 2; i >= 0; i--) {
		double sum = 0;
		for (int j = A._cols - 1; j > i; j--) {
			sum += X(j, 0) * U(i, j);
		}
		X(i, 0) = (B(i, 0) - sum) / U(i, i);
	}

	return X;
}
