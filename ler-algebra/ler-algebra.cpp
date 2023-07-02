// ler-algebra.cpp: 定义应用程序的入口点。
//

#include "ler-algebra.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	// Matrix A(3, 3, 1);
	// Matrix X(3, 1, 1);
	// Matrix b = A * X;
	// std::cout << b;

	// Matrix A {{1, 2, 3}, {2, 3, 4}, {3, 4, 6}};
	// Matrix X {{1}, {2}, {3}};
	// std::cout << A * X;
	// std::cout << solve(A, X);

	// Matrix A {{2, 5}, {6, 1}};
	// Matrix b {{3}, {3}};
	// std::cout << A * b;
	// std::cout << solve(A, b);

	Matrix A {{1, 2, 3}, {2, 5, 6}, {1, 6, 1}};
	Matrix b {{1}, {3}, {6}};
	std::cout << A * b;
	std::cout << solve(A, b);
	return 0;
}
