#include <iostream>
#include <iomanip>

#include "matrix.h"

int main() {	
	std::cout << std::setprecision(16);
	size_t N;
	std::cin >> N;
	linalg::Matrix m(N);
	
	for(size_t i = 0; i < N; i++) {
		for(size_t j = 0; j < N; j++) {
			int num;
			std::cin >> num;
			
			m[i][j] = numbers::Rational(num);
		}
	}
	
	std::cout << m.LUDet() << std::endl;
	return 0;
}
