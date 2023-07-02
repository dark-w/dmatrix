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

Matrix Matrix::get_identity() const {
	Matrix identity_matrix(_rows, _rows, 0);

	for (int i = 0; i < _rows; i++) {
		identity_matrix(i, i) = 1;
	}

	return identity_matrix;
}

Matrix& Matrix::exchange_two_rows(int a, int b) {
	for (int i = 0; i < _cols; i++) {
		double t = (*this)(a, i);
		(*this)(a, i) = (*this)(b, i);
		(*this)(b, i) = t;
	}
	
	return *this;
}

// it only works for square matrix now.
Matrix& Matrix::transpose() {
	for (int i = 1; i < _rows; i++) {
		for (int j = 0; j < i; j++) {
			double t = (*this)(i, j);
			(*this)(i, j) = (*this)(j, i);
			(*this)(j, i) = t;
		}
	}

	return *this;
}

Matrix 
Matrix::get_permutation(std::initializer_list<std::pair<int, int>> indices) 
const {
	Matrix p(get_identity());

	for (auto i : indices) {
		p.exchange_two_rows(i.first, i.second);
	}

	return p;
}

Matrix Matrix::get_symmetric() const {
	Matrix symmetric_matrix(*this);
	return *this * symmetric_matrix.transpose();
}

Matrix Matrix::get_inverse_by_Guass_Jordan_elimination() const {
	// Guass-Jordan Enimination
	// E[AI] = [I(A^-1)]
	
	Matrix I(this->get_identity());
	Matrix A(*this);

	for (int i = 0; i < _rows; i++) {
		for (int j = i + 1; j < _rows; j++) {
			double ec = A(j, i) / A(i, i);
			for (int k = 0; k < _cols; k++) {
				A(j, k) = A(j, k) - ec * A(i, k);
				I(j, k) = I(j, k) - ec * I(i, k);
			}
		}
	}

	// A is U now, but i need I, so continue
	for (int i = _rows - 1; i >= 0; i--) {
		// the pivot must be one
		double pivot_to_one = A(i, i) / 1;
		for (int j = 0; j < _cols; j++) {
			A(i, j) = A(i, j) / pivot_to_one;
			I(i, j) = I(i, j) / pivot_to_one;
		}

		for (int j = i - 1; j >= 0 ; j--) {
			double ec = A(j, i) / A(i, i);
			for (int k = 0; k < _cols; k++) {
				A(j, k) = A(j, k) - ec * A(i, k);
				I(j, k) = I(j, k) - ec * I(i, k);
			}
		}
	}

	// the pivot must be one
	double pivot_to_one = A(0, 0) / 1;
	for (int j = 0; j < _cols; j++) {
		A(0, j) = A(0, j) / pivot_to_one;
		I(0, j) = I(0, j) / pivot_to_one;
	}

	return I;
}

// it only works for square matrix
std::pair<Matrix, Matrix> Matrix::get_LU() const {
	Matrix L(get_identity());
	Matrix U(_rows, _cols, 0);
	Matrix A(*this);

	for (int i = 0; i < _rows; i++) {
		for (int j = i; j < _cols; j++) {
			U(i, j) = A(i, j);
		}

		for (int j = i + 1; j < _rows; j++) {
			L(j, i) = A(j, i) / A(i, i);
			for (int k = i + 1; k < _cols; k++) {
				A(j, k) = A(j, k) - L(j, i) * A(i, k);				
			}
		}
	}

	return {L, U};
}
