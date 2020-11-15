#include <tuple>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

namespace linalg {

template <typename dType>
class Matrix final {
public:
	Matrix() = default;
		
	Matrix(size_t n) : 
		_size(n)
	{
		_data = (dType**)std::malloc(_size * sizeof(dType*));
		for (size_t i = 0; i < _size; i++) {
			_data[i] = (dType*)std::calloc(_size, sizeof(dType));
		}
	}
	
	Matrix(const std::vector<std::vector<dType>>& data) :
		_size(data.size())
	{
		_data = (dType**)std::malloc(_size * sizeof(dType*));
		for (size_t i = 0; i < _size; i++) {
			_data[i] = (dType*)std::calloc(_size, sizeof(dType));
			for(size_t j = 0; j < _size; j++) {
				_data[i][j] = data[i][j];
			}
		}
	}
	
	Matrix(const Matrix& mt) :
		_size(mt.size())
	{
		_data = AllocSqMem(_size); 
		mt.CopyDataTo(_data);
	}
	
	
public:
	dType** getData() const { return _data; }
	size_t size() const { return _size; }
	
	static Matrix EMatrix(size_t n) {
		Matrix E(n);
		for(size_t i = 0; i < n; i++) {
			E[i][i] = 1;
		}
		return E;
	}
	
	// Функция аллоцирования памяти под данные для квадратного массива
	static dType** AllocSqMem(size_t sz) {
		dType** res = (dType**)std::malloc(sz * sizeof(dType*));
		for (size_t i = 0; i < sz; i++) {
			res[i] = (dType*)std::calloc(sz, sizeof(dType));
		}
		return res;
	}
	
	// Функция копирования данных по ссылке
	dType** CopyDataTo(dType**& dataSt) const {
		for (size_t i = 0; i < _size; i++) {
			for(size_t j = 0; j < _size; j++) {
				dataSt[i][j] = _data[i][j];
			}
		}
		return dataSt;
	}	
	
	std::tuple<Matrix, int> GaussTriangleReduction() const {
		int swapCnt = 1;
		Matrix C = *this; 

		for (size_t i = 0; i < _size; i++) { 
			size_t row = i;
			for (size_t j = i; j < _size; j++) {
				if(C[j][i] !=  0) { 
					row = j;
					break;
				}
			}
			
			swap(C[i], C[row], _size);
			swapCnt = -swapCnt * (i != row ? 1 : - 1);
			
			//std::cout << std::endl << "Debug 1: " << C << std::endl;
					
			for (size_t j = i+1; j < _size; j++) {
				if (C[j][i] == 0)
					continue;
				dType q = - C[j][i] / C[i][i];
				for (size_t k = i; k < _size; k++) {
					C[j][k] += q * C[i][k]; 
				}
			}
			
			//std::cout << std::endl << "Debug 2: " << C << std::endl;
		}
		
		return std::make_tuple(C, swapCnt);
		
	}
	
	// Поиск детерминанта матрицы методом Гаусса
	dType GDet() const {
		auto[U, cnt] = GaussTriangleReduction();
		//std::cout << U << std::endl;
		dType D(1);		
		for(size_t i = 0; i < _size; i++) {
			D *= U[i][i];
		}
		// Округление до первого знака 
		return (cnt * round(D*10)/10);
	}
	
	dType*& operator [] (size_t i) {
		if(i > _size) {
			throw std::invalid_argument("First index is out of range!");
		}
		return _data[i];
	}
	
	const dType* operator [] (size_t i) const {
		if(i > _size) {
			throw std::invalid_argument("First index is out of range!");
		}
		return _data[i];
	}
	
	static void swap(dType*& mass1, dType*& mass2, size_t sz) {
		dType* tmp = (dType*)std::calloc(sz, sizeof(dType));
		for(size_t i = 0; i < sz; i++) {
			tmp[i] = mass1[i];
			mass1[i] = mass2[i];
			mass2[i] = tmp[i];
		}
	}
		
private:
	dType** _data;
	size_t _size;
};


// Переопределенные операторы для матриц
template <class dType>
std::ostream& operator << (std::ostream& os, const Matrix<dType>& matrix) {
	os << "Matrix {";
	bool fv = true;
	for(size_t i = 0; i < matrix.size(); i++) {	
		if (!fv) {os << " ";}
		os << "(";
		bool first = true;
		for (size_t j = 0; j < matrix.size(); j++) {
			if (!first) {os << ", ";}
			first = false;			
			os << matrix[i][j];
		}
		fv = false;
		os << ")";
	}
	
	return os << "}";
}


template <typename dType>
bool operator == (const Matrix<dType>& lhs, const Matrix<dType>& rhs) {
	if(lhs.size() != rhs.size())
		return false;
	
	for(size_t i = 0; i < lhs.size(); i++){	
		for(size_t j = 0; j < lhs.size(); j++) {
			if(lhs[i][j] != rhs[i][j]) 
				return false;
		}
	}
	
	return true;
}

template <typename dType>
Matrix<dType> operator * (const Matrix<dType>& lhs, const Matrix<dType>& rhs) {
	Matrix<dType> result(lhs.size());
	
	for(size_t rowOflhsM = 0; rowOflhsM < lhs.size(); ++rowOflhsM) {
		for(size_t colOfrhsM = 0; colOfrhsM < rhs.size(); ++colOfrhsM) {
			dType Rij(0);
			for (size_t k = 0; k < rhs.size(); k++) {
				Rij += lhs[rowOflhsM][k] * rhs[k][colOfrhsM];
			}
			result[rowOflhsM][colOfrhsM] = Rij;
		}
	}
	
	return result;
} 

}
