#pragma once

#include <iostream>
#include <cmath>
#include <numeric>

namespace numbers {

class Rational{
public:
	Rational (long long numerator=0, long long denumerator=1) :
		_nmr(numerator),
		_dnm(denumerator)
	{
		Sign();
		Gcd();
  	}
  	
public:
	Rational operator * (const Rational mn) const {
		return Rational (_nmr * mn._nmr, _dnm * mn._dnm);
	}

	Rational operator / (const Rational del) const {
		return Rational (_nmr*del._dnm, _dnm*del._nmr);
	}
	
	Rational operator - (const Rational vi) const {
		return( 
			Rational(_nmr * vi._dnm - vi._nmr * _dnm,  _dnm * vi._dnm)
		);
	}
	
	bool operator != (const Rational sr) const {
		if ((_nmr != sr._nmr) || (_dnm != sr._dnm)) 
			return true;
		
		return false;
	}
	
	Rational& operator *= (const Rational& rhs) {
		_nmr *= rhs._nmr;
		_dnm *= rhs._dnm;
		Sign();
		Gcd();
		return *this;
	}
	
	Rational& operator = (const Rational& drob) {
		if (this == &drob)
			return *this;	
		_nmr = drob._nmr;
		_dnm = drob._dnm;
		return *this;
	}
	
	long long Numerator() const {
		return _nmr;
	}

	long long Denominator() const {
		return _dnm;
	}
	
	double res() const {
		return (_nmr / _dnm);
	}
  	
private:
	void Gcd() {
		if ( (_nmr==0) || (_dnm==0))
			return; 
		long long c = std::gcd(_nmr, _dnm);
		_nmr /= c;
		_dnm /= c;
	}
	
	void Sign() {
		if (_nmr == 0) {
			_dnm = 1;
		}
		if ((_dnm < 0) && (_nmr < 0)) { 
			_nmr = abs(_nmr); 
			_dnm = abs(_dnm);
		}
		if ((_dnm < 0) && (_nmr > 0)) { 
			_nmr = -1*_nmr; 
			_dnm = abs (_dnm);
		}
	}
	
private:
	long long _nmr;
	long long _dnm;
};

std::ostream& operator << (std::ostream& stream, const Rational& r);

}
