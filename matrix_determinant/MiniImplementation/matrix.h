#pragma once

#include "rational.h"

#include <vector>
#include <tuple>
#include <stdexcept>
#include <iostream>

typedef std::vector<std::vector<numbers::Rational>>  MDataType;

namespace linalg {

class Matrix {
public:
	Matrix() = default;
	Matrix(size_t n) :
		_size(n)
	{
		_data.resize(n);
		for(size_t i = 0; i < n; i++) 
			_data[i].resize(n);
	}
	Matrix(const MDataType& data) :
		_size(data.size()) 
	{
		_data.resize(data.size());
		for(size_t i = 0; i < data.size(); i++) 
			_data[i].resize(data.size());	
		_data = data;
	}
	
public:
	MDataType getData() const { return _data; }
	size_t size() const {return _size;}
	
	static Matrix EMatrix(size_t n) {
		Matrix E(n);
		for(size_t i = 0; i < n; i++) {
			E[i][i] = 1;
		}
		return E;
	}
	
	std::tuple<Matrix, Matrix> LUDecomposition() const;
	
	std::vector<numbers::Rational>& operator [] (size_t i) {
		if(i > _data.size()) {
			throw std::invalid_argument("First index is out of range!");
		}
		return _data[i];
	}
	
	double LUDet() const;
	//double det();
	
private:
	//Matrix getCofactor(size_t p, size_t q);
	
	
private:
	MDataType _data;
	size_t _size;
};

std::ostream& operator << (std::ostream& os, const Matrix& s);
bool operator == (const Matrix& leftM, const Matrix& rightM);

}
