#include "matrix.h"

namespace linalg {

// Функция LU-декомпозиции матрицы
std::tuple<Matrix, Matrix> Matrix::LUDecomposition() const {
	Matrix L = EMatrix(_data.size());
	Matrix U(_data.size());
	MDataType A = _data;
	
	for(size_t k = 0; k < A.size(); k++) {
		U[k][k] = A[k][k];
		for(size_t i = (k+1); i < A.size(); i++) { 
			L[i][k]=A[i][k]/U[k][k];
            U[k][i]=A[k][i];
		}
		for(size_t i = (k+1); i < A.size(); i++) { 
			for(size_t j=k+1; j < A.size(); j++) {
				A[i][j]=A[i][j]-L[i][k]*U[k][j];
			}
		}
	}

	return std::make_tuple(L, U);
}


/* Функиця копирования элементов матрицы без строки p и столбца q 
 * в матрицу меньшей размерности.
 */
/* 
Matrix Matrix::getCofactor(size_t p, size_t q) {
	size_t i = 0;
	size_t j = 0;

	Matrix temp(_data.size() - 1);
	for (size_t row = 0; row < _data.size(); row++) {
        for (size_t col = 0; col < _data.size(); col++) {
			if (row != p && col != q) {
                temp[i][j++] = _data[row][col];
                if (j == _data.size() - 1) {
                    j = 0;
                    i++;
                }
            }
		}
	}
	
	return temp;
}
*/


// Тривиальная функция вычисления определителя матрицы
/*
double Matrix::det() {
	double D = 0;  
	int sign = 1;
	size_t n = _data.size();
	
    if (_data.size() == 1)
		return _data[0][0];
		
	for (size_t f = 0; f < _data.size(); f++) {
        auto temp = getCofactor(0, f);
        //std::cout << "temp: " << temp << std::endl;
        D += sign * _data[0][f] * temp.det();
        sign = -sign;
    }
		
	return D;
}
*/

// Поиск детерминанта матрицы по средства LU-декомпозиции
double Matrix::LUDet() const {
	auto[L, U] = LUDecomposition();
	numbers::Rational D(1);
	
	//std::cout << "U: " << U << std::endl;
	
	for(size_t i = 0; i < _size; i++) {
		D *= U[i][i];
		//std::cout << D << std::endl;
	}
		
	return D.res();
}

// Переопределенные операторы для матриц
std::ostream& operator << (std::ostream& os, const Matrix& matrix) {
	os << "Matrix {";
	
	auto mt = matrix.getData();
	bool fv = true;
	for(size_t i = 0; i < mt.size(); i++) {	
		if (!fv) {os << " ";}
		os << "(";
		bool first = true;
		for (const auto& elem : mt[i]) {
			if (!first) {os << ", ";}
			first = false;			
			os << elem;
		}
		fv = false;
		os << ")";
	}
	
	return os << "}";
}

bool operator == (const Matrix& leftM , const Matrix& rightM) {
	MDataType lhs = leftM.getData();
	MDataType rhs = rightM.getData();
	
	if(lhs.size() != rhs.size())
		return false;
	
	for(size_t i = 0; i < lhs.size(); i++){
		if(lhs[i].size() != rhs[i].size())
			return false;
		
		for(size_t j = 0; j < lhs[i].size(); j++) {
			if(lhs[i][j] !=  rhs[i][j]) 
				return false;
		}
	}
	return true;
}

}

