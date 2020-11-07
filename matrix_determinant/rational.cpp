#include "rational.h"

namespace numbers {

std::ostream& operator << (std::ostream& stream, const Rational& r) {
	stream << r.Numerator();
	stream << "/";
	stream << r.Denominator();
	return stream;
}

}
