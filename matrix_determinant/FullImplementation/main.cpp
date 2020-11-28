#include <iostream>
#include <iomanip>

#include "matrix.hpp"

int main() {	
	std::cout << std::setprecision(16);
	size_t N;
	std::cin >> N;

	linalg::qMatrix<long double> m(N);
	
	for(size_t i = 0; i < N; i++) {
		for(size_t j = 0; j < N; j++) {
			int num;
			std::cin >> m[i][j];
		}
	}
	
	std::cout << m.GDet() << std::endl;
	return 0;
}
