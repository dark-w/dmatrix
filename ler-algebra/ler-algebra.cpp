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

	// Matrix A {{1, 2, 3}, {2, 5, 6}, {1, 6, 1}};
	// Matrix b {{1}, {3}, {6}};
	// std::cout << A * b;
	// std::cout << solve(A, b);

	// Matrix A {{1, 3}, {2, 7}};
	// Matrix A_inverse(A.inverse_by_Guass_Jordan_elimination());
	// std::cout << A_inverse;
	// std::cout << A * A_inverse;
	// std::cout << A_inverse * A;
	
	Matrix A {{1, 2, 3}, {2, 5, 6}, {1, 6, 1}};
	Matrix b {{1, 2, 3}, {2, 5, 6}, {1, 6, 1}};
	// std::cout << A * b;
	// std::cout << (A * b).inverse_by_Guass_Jordan_elimination() << std::endl;
	// std::cout << b.inverse_by_Guass_Jordan_elimination() * 
	// 	A.inverse_by_Guass_Jordan_elimination();
	// std::cout << (A * b) * (A * b).inverse_by_Guass_Jordan_elimination() << std::endl;
	std::cout << "L" << std::endl;
	std::cout << A.get_LU().first; 
	std::cout << "U" << std::endl;
	std::cout << A.get_LU().second;
	std::cout << "L * U" << std::endl;
	std::cout << A.get_LU().first * A.get_LU().second;

	// std::cout << A.exchange_two_rows(0, 1);
	std::cout << A.get_permutation({{1, 2}});
	std::cout << A.transpose();
	return 0;
}
