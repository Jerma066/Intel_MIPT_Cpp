#include "geo3d.h"

void debug(int line) {
	std::cout << "line number: " << line << std::endl;
}


namespace geo3d{
	
std::ostream& operator << (std::ostream &out, const Point& pt)
{
    out << "Point {" << pt.x << ", " << pt.y 
		<< ", " << pt.z << "}";
 
    return out;
}

// Vector module
Vector operator * (Vector lhs, Vector rhs) {
	Vector result;
	result.x = (lhs.y * rhs.z) - (rhs.y * lhs.z);
	result.y = (rhs.x * lhs.z) - (lhs.x * rhs.z);
	result.z = (lhs.x * rhs.y) - (rhs.x * lhs.y);
	
	return result;
}

std::ostream& operator << (std::ostream &out, const Vector& vec)
{
    out << "Vector {" << vec.x << ", " << vec.y 
		<< ", " << vec.z << "}";
 
    return out;
}

bool operator == (Vector lhs, Vector rhs) {
	return (
		std::tie(lhs.x, lhs.y, lhs.z) == 
		std::tie(rhs.x, rhs.y, rhs.z) 
	);
}

bool operator != (Vector lhs, Vector rhs) {
	return !(lhs == rhs);
}

float ScalarProduct(Vector lhs, Vector rhs) {
	return (lhs.x * rhs.x + 
			lhs.y * rhs.y + 
			lhs.z * rhs.z);
}

std::tuple<float, float> Kramer2dOnly (
	std::tuple<float, float, float> equation1, 
	std::tuple<float, float, float> equation2)
{
	auto lambda_yxl = (
		Vector(std::get<0>(equation1), std::get<1>(equation1), std::get<2>(equation1)) * 
		Vector(std::get<0>(equation2), std::get<1>(equation2), std::get<2>(equation2))
	);
	
	return std::make_tuple(
		(-1)*lambda_yxl.x / lambda_yxl.z,
		(-1)*lambda_yxl.y / lambda_yxl.z
	); 
}

// Plane module
Plane::Plane(float A, float B, float C, float D):
	normal(A, B, C), 
	D_(D)
{		
}

Plane::Plane(Point p1, Point p2, Point p3) {
	normal = Vector (p1, p2) * Vector (p1, p3);	
	D_ = -1 * ScalarProduct(normal, Vector(p3));
}

Line Plane::IntersectionLine(Plane pl1, Plane pl2) {
	Line result;
	result.direction = pl1.normal * pl2.normal;
	
	if(ScalarProduct(result.direction, Axis::Z) != 0) { 	
		result.startingPt.z = 0;
		std::tie (result.startingPt.x, result.startingPt.y) = Kramer2dOnly (
			std::make_tuple(pl1.normal.x, pl1.normal.y, -pl1.GetCoefficientD()),  
			std::make_tuple(pl2.normal.x, pl2.normal.y, -pl2.GetCoefficientD())
		); 
	}
	else if(ScalarProduct(result.direction, Axis::Y) != 0) {
		result.startingPt.y = 0;
		std::tie (result.startingPt.x, result.startingPt.z) = Kramer2dOnly (
			std::make_tuple(pl1.normal.x, pl1.normal.z, -pl1.GetCoefficientD()),  
			std::make_tuple(pl2.normal.x, pl2.normal.z, -pl2.GetCoefficientD())
		); 
	}
	else if(ScalarProduct(result.direction, Axis::X) != 0) {
		result.startingPt.x = 0;		
		std::tie(result.startingPt.y, result.startingPt.z) = Kramer2dOnly (
			std::make_tuple(pl1.normal.y, pl1.normal.z, -pl1.GetCoefficientD()),  
			std::make_tuple(pl2.normal.y, pl2.normal.z, -pl2.GetCoefficientD())
		); 
	}		
		
	return result;
}
	
// Triangle module
Triangle::Triangle(Point p1, Point p2, Point p3):
	p1_(p1),
	p2_(p2),
	p3_(p3)
{
}

std::tuple<Point, Point, Point> Triangle::GetPoints() const {
	return std::make_tuple(p1_, p2_, p3_);
}

// Returned value: int - index of the intersecting vertex (-1) - if it does not intersect;
// 															5  - if planes coincide).
std::tuple<int, d3Value> CheckIntersection(Triangle tr, Plane pl) {
	auto [p1, p2, p3] = tr.GetPoints();
	auto dres = d3Value(
		pl.GetValueFromPoint(std::move(p1)), 
		pl.GetValueFromPoint(std::move(p2)), 
		pl.GetValueFromPoint(std::move(p3))
	);
	
	if((dres.d0 == 0) && (dres.d1 == 0) && (dres.d2 == 0)){
		return std::make_tuple(5, dres);
	}
	else{
		int signs;
		
		if(dres.d0 * dres.d1 * dres.d2 == 0){
			signs = 1;
		}
		else {
			signs = (((dres.d0 > 0) ? 1 : 0) +
				((dres.d1 > 0) ? 1 : 0) + 
				((dres.d2 > 0) ? 1 : 0)
			);
		}
		
		switch (signs) {
			case 1:
				if(dres.d0 >= 0) {return std::make_tuple(0, dres);}
				else if(dres.d1 >= 0) {return std::make_tuple(1, dres);}
				else if(dres.d2 >= 0) {return std::make_tuple(2, dres);}
				break;	
			case 2:
				if(dres.d0 <= 0){return std::make_tuple(0, dres);}
				else if(dres.d1 <= 0){return std::make_tuple(1, dres);}
				else if(dres.d2  <= 0){return std::make_tuple(2, dres);}
				break;
			default:
				return std::make_tuple(-1, dres);
				break;
		}
	}
	
	return std::make_tuple(-1, dres);
}

float Triangle::CalculateGapValue(float p0, float p1, float d0, float d1) {
	if(d1 == 0 || d1 == -0) {
		return p1;
	}
	
	return ( p1 + ((p0 - p1)*d1/(d1 - d0)) ) ;
}

std::tuple<float, float> Triangle::FindIntersectionGap (
	Line iLine, int iPos, d3Value dval
) const {
	float p_0 = ScalarProduct(iLine.direction,  Vector(iLine.startingPt, p1_));        	
	float p_1 = ScalarProduct(iLine.direction,  Vector(iLine.startingPt, p2_));
	float p_2 = ScalarProduct(iLine.direction,  Vector(iLine.startingPt, p3_));
	
	//std::cout << "iPosition = " << iPos << std::endl;
	//std::cout << "p_i = { " <<  p_0 << ", " << p_1 << ", " << p_2 << "}" << std::endl;
	//std::cout << "d_i = { " <<  dval.d0 << ", " << dval.d1 << ", " << dval.d2 << "}" << std::endl; 
	
	switch(iPos) {
		case 0:
		{
			float t1 = CalculateGapValue(p_0, p_1, dval.d0, dval.d1);
			float t2 = CalculateGapValue(p_0, p_2, dval.d0, dval.d2);
			return std::make_tuple(std::min(t1, t2), std::max(t1, t2));
			break;
		}
		case 1:
		{
			float t1 = CalculateGapValue(p_1, p_0, dval.d1, dval.d0);
			float t2 = CalculateGapValue(p_1, p_2, dval.d1, dval.d2);
			return std::make_tuple(std::min(t1, t2), std::max(t1, t2));
			break;
		}
		case 2:
		{
			float t1 = CalculateGapValue(p_2, p_0, dval.d2, dval.d0);
			float t2 = CalculateGapValue(p_2, p_1, dval.d2, dval.d1);
			return std::make_tuple(std::min(t1, t2), std::max(t1, t2));
			break;
		}
		default:
			return std::make_tuple(0, 0);
			break;
	}
	
	return std::make_tuple(0, 0);
}

bool Triangle::isIntersect(Triangle tr) {
	bool result = false;
	auto [anotherP1, anotherP2, anotherP3] = tr.GetPoints();
	
	// Plane equations:
	Plane anotherPlane = Plane(anotherP1, anotherP2, anotherP3);
	Plane thisPlane = Plane(this->p1_, this->p2_, this->p3_);
	
	
	
	// Possibility of intersecting
	auto [thisPosition, thisIntnValue] = CheckIntersection(*this, anotherPlane);
	if(thisPosition == -1) {return false;}
	auto [anotherPosition, anotherIntnValue] = CheckIntersection(tr, thisPlane);
	if(anotherPosition == -1) {return false;}
	
	//debug(__LINE__);
	
	// Not coplanar triangles:
	if( ((thisPosition < 5) && (thisPosition >= 0)) && 
	    ((anotherPosition < 5)  && (anotherPosition >= 0)) )  
	{
		Line inLn = Plane::IntersectionLine(anotherPlane, thisPlane);
	
		//std::cout << inLn.direction << std::endl;
		//std::cout << inLn.startingPt << std::endl;
	
		auto [tt1, tt2] = this->FindIntersectionGap(inLn, thisPosition, thisIntnValue);
		auto [at1, at2] = tr.FindIntersectionGap(inLn, anotherPosition, anotherIntnValue);
		
		if( (tt1 > at2 && tt2 > at2) ||  (at1 > tt2 && at2 > tt2) ) {
			//std::cout << "(" << tt1 << "; " << tt2 << ")" << std::endl;
			//std::cout << "(" << at1 << "; " << at2 << ")" << std::endl;
			return false;
		}
		else {
			return true;
		}
	}
	
	//debug(__LINE__);
	
	// Coplanar triangles:
	if(thisPosition == 5 && anotherPosition == 5) {
		// Project the triangles onto a plane that is NOT perpendicular to them:
		bool prlToX = (ScalarProduct(thisPlane.getNormal(), Axis::X) == 0);
		bool prlToY = (ScalarProduct(thisPlane.getNormal(), Axis::Y) == 0);
		bool prlToZ = (ScalarProduct(thisPlane.getNormal(), Axis::Z) == 0);

		geo2d::Triangle ttr, atr;
		if(prlToX && prlToY) {
			//debug(__LINE__);
			ttr = Converters::From3dTo2d(*this, Converters::Mode::NO_Z);
			atr = Converters::From3dTo2d(tr, Converters::Mode::NO_Z);
		}
		else if (prlToX && prlToZ) {
			//debug(__LINE__);
			ttr = Converters::From3dTo2d(*this, Converters::Mode::NO_Y);
			atr = Converters::From3dTo2d(tr, Converters::Mode::NO_Y);
		}
		else if (prlToY && prlToZ) {
			//debug(__LINE__);
			ttr = Converters::From3dTo2d(*this, Converters::Mode::NO_X);
			atr = Converters::From3dTo2d(tr, Converters::Mode::NO_X);
		}
		else if (prlToX) {
			//debug(__LINE__);
			ttr = Converters::From3dTo2d(*this, Converters::Mode::NO_Y);
			atr = Converters::From3dTo2d(tr, Converters::Mode::NO_Y);
		}
		else if (prlToY) {
			//debug(__LINE__);
			ttr = Converters::From3dTo2d(*this, Converters::Mode::NO_Z);
			atr = Converters::From3dTo2d(tr, Converters::Mode::NO_Z);
		}
		else if (prlToZ) {
			//debug(__LINE__);
			ttr = Converters::From3dTo2d(*this, Converters::Mode::NO_X);
			atr = Converters::From3dTo2d(tr, Converters::Mode::NO_X);
		}
	
		return ttr.isIntersect(atr);
	}
	
	//debug(__LINE__);
	
	return result;
}

}

namespace geo2d {
	
float operator * (Vector lhs, Vector rhs) {
	return lhs.x * rhs.y - rhs.x * lhs.y;
}

// Segment module
bool Segment::IsIntersect(Segment seg1, Segment seg2){
	float res1 = Vector(seg1.p1, seg2.p1) * Vector(seg1.p1, seg1.p2);
	float res2 = Vector(seg1.p1, seg2.p2) * Vector(seg1.p1, seg1.p2);
	
	if((res1 * res2) > 0)
		return false;
	
	res1 = Vector(seg2.p2, seg1.p2) * Vector(seg2.p2, seg2.p1);
	res2 = Vector(seg2.p2, seg1.p1) * Vector(seg2.p2, seg2.p1);
	
	if((res1 * res2) > 0)
		return false;
	
	return true;
}


// Triangle module
Triangle::Triangle(Point p1, Point p2, Point p3):
	p1_(p1),
	p2_(p2),
	p3_(p3)
{
}

std::tuple<Point, Point, Point> Triangle::GetPoints() const {
	return std::make_tuple(p1_, p2_, p3_);
}

bool Triangle::isPointLiesIn(Point pt) const {
	float z1 = Vector(p1_, p2_) * Vector(p1_, pt);
	float z2 = Vector(p2_, p3_) * Vector(p2_, pt);
	float z3 = Vector(p3_, p1_) * Vector(p3_, pt);
	
	// Lies on the edge of the triangle;
	if((z1 == 0) && (z2 != 0) && (z3 != 0)) {
		if((((z2 > 0) ? 1 : 0) + ((z3 > 0) ? 1 : 0)) == 1) {
			return false;
		}
		else {
			//debug(__LINE__);
			return true;
		}
	}
	else if ((z1 != 0) && (z2 == 0) && (z3 != 0)) {
		if((((z1 > 0) ? 1 : 0) + ((z3 > 0) ? 1 : 0)) == 1) {
			return false;
		}
		else {
			//debug(__LINE__);
			return true;
		}
	}
	else if ((z1 != 0) && (z2 != 0) && (z3 == 0)) {
		if((((z1 > 0) ? 1 : 0) + ((z2 > 0) ? 1 : 0)) == 1) {
			return false;
		}
		else {
			//debug(__LINE__);
			return true;
		}
	}
	
	// Lies inside the triangle
	//std::cout << "signs: " << z1 << ", " << z2 << ", " << z3 << std::endl;
	int signs = (
		((z1 > 0) ? 1 : 0) + 
		((z2 > 0) ? 1 : 0) + 
		((z3 > 0)? 1 : 0)
	);
	
	if(signs == 0 || signs == 3) {
		//debug(__LINE__);
		return true;
	}
	
	return false;
}

bool Triangle::isIntersect(Triangle tr) const {
	// Сhecking if any vertex of one triangle lies in another
	//debug(__LINE__);
	if(tr.isPointLiesIn(p1_)){ 
		//debug(__LINE__);
		return true; 
	}
	//debug(__LINE__);
	if(tr.isPointLiesIn(p2_)){ return true; }
	//debug(__LINE__);
	if(tr.isPointLiesIn(p3_)){ return true; }
	
	auto [ap1, ap2, ap3] = tr.GetPoints();
	if(this->isPointLiesIn(ap1)){ return true; }
	//debug(__LINE__);
	if(this->isPointLiesIn(ap2)){ return true; }
	//debug(__LINE__);
	if(this->isPointLiesIn(ap3)){ return true; }
	//debug(__LINE__);
	
	// Edge intersection check
	if(Segment::IsIntersect(Segment(p1_, p2_), Segment(ap1, ap2))) { return true; }
	//debug(__LINE__);
	if(Segment::IsIntersect(Segment(p1_, p2_), Segment(ap1, ap3))) { return true; }
	//debug(__LINE__);
	if(Segment::IsIntersect(Segment(p1_, p2_), Segment(ap2, ap3))) { return true; }
	
	if(Segment::IsIntersect(Segment(p1_, p3_), Segment(ap1, ap2))) { return true; }
	//debug(__LINE__);
	if(Segment::IsIntersect(Segment(p1_, p3_), Segment(ap1, ap3))) { return true; }
	//debug(__LINE__);
	if(Segment::IsIntersect(Segment(p1_, p3_), Segment(ap2, ap3))) { return true; }
	//debug(__LINE__);
	
	if(Segment::IsIntersect(Segment(p2_, p3_), Segment(ap1, ap2))) { return true; }
	//debug(__LINE__);
	if(Segment::IsIntersect(Segment(p2_, p3_), Segment(ap1, ap3))) { return true; }
	//debug(__LINE__);
	if(Segment::IsIntersect(Segment(p2_, p3_), Segment(ap2, ap3))) { return true; }
	//debug(__LINE__);
	
	return false;
}

}

namespace Converters {
	
geo2d::Point From3dTo2d (geo3d::Point pt, Mode mode) {
	switch(mode) {
		case Mode::NO_X :
			return geo2d::Point(pt.y, pt.z);
			break;
		case Mode::NO_Y :
			return geo2d::Point(pt.x, pt.z);
			break;
		case Mode::NO_Z :
			return geo2d::Point(pt.x, pt.y);
			break;
		default :
			return geo2d::Point();
	}
}

geo2d::Triangle From3dTo2d (geo3d::Triangle tr, Mode mode) {
	auto [pt1, pt2, pt3] = tr.GetPoints();
	return geo2d::Triangle(
		From3dTo2d(std::move(pt1), mode), 
		From3dTo2d(std::move(pt2), mode),
		From3dTo2d(std::move(pt3), mode)
	);
}

}

