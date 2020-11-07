#include <tuple>
#include <iostream>
#include <cstdlib>
#include <vector>

namespace linalg {

template <typename dType>
class Matrix {
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
	
	// Функция копирования данных матрицы в память по указателю
	dType** CopyDataTo(dType**& dataSt) const {
		dataSt = (dType**)std::malloc(_size * sizeof(dType*));
		for (size_t i = 0; i < _size; i++) {
			dataSt[i] = (dType*)std::calloc(_size, sizeof(dType));
			for(size_t j = 0; j < _size; j++) {
				dataSt[i][j] = _data[i][j];
			}
		}

		return dataSt;
	}	
	
	// Функция LU-декомпозиции матрицы
	std::tuple<Matrix, Matrix> LUDecomposition() const {
		Matrix L = EMatrix(_size);
		Matrix U(_size);
		dType** A; 
		CopyDataTo(A);

		for(size_t k = 0; k < _size; k++) {
			U[k][k] = A[k][k];
			for(size_t i = (k+1); i < _size; i++) { 
				L[i][k]=A[i][k]/U[k][k];
				U[k][i]=A[k][i];
			}
			for(size_t i = (k+1); i < _size; i++) { 
				for(size_t j=k+1; j < _size; j++) {
					A[i][j]=A[i][j]-L[i][k]*U[k][j];
				}
			}
		}

		return std::make_tuple(L, U);
	}
	
	// Поиск детерминанта матрицы по средства LU-декомпозиции
	dType LUDet() const {
		auto[L, U] = LUDecomposition();
		dType D(1);		
		for(size_t i = 0; i < _size; i++) {
			D *= U[i][i];
		}
		return D;
	}
	
	dType* operator [] (size_t i) {
		if(i > _size) {
			throw std::invalid_argument("First index is out of range!");
		}
		return _data[i];
	}
		
private:
	dType** _data;
	size_t _size;
};


// Переопределенные операторы для матриц
template <class dType>
std::ostream& operator << (std::ostream& os, const Matrix<dType>& matrix) {
	os << "Matrix {";
	dType** mt; matrix.CopyDataTo(mt);
	bool fv = true;
	for(size_t i = 0; i < matrix.size(); i++) {	
		if (!fv) {os << " ";}
		os << "(";
		bool first = true;
		for (size_t j = 0; j < matrix.size(); j++) {
			if (!first) {os << ", ";}
			first = false;			
			os << mt[i][j];
		}
		fv = false;
		os << ")";
	}
	
	return os << "}";
}


template <typename dType>
bool operator == (const Matrix<dType>& leftM, const Matrix<dType>& rightM) {
	dType** lhs; leftM.CopyDataTo(lhs);
	dType** rhs; rightM.CopyDataTo(rhs);
	 	
	if(leftM.size() != rightM.size())
		return false;
	
	for(size_t i = 0; i < leftM.size(); i++){	
		for(size_t j = 0; j < leftM.size(); j++) {
			if(lhs[i][j] != rhs[i][j]) 
				return false;
		}
	}
	return true;
}

}
