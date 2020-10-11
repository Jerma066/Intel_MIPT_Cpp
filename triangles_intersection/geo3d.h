#pragma once

#include <tuple>
#include <iostream>
#include <utility>

namespace geo3d {

struct d3Value {
	float d0, d1, d2;

	d3Value(float xx = 0, float yy = 0, float zz = 0) : 
		d0(xx), d1(yy), d2(zz) 
	{
	}
	
};

struct Point {
	float x, y, z;
	
	Point(float xx = 0, float yy = 0, float zz = 0) :
		x(xx), y(yy), z(zz) 
	{
	}
	
};

struct Vector {
	float x, y, z;
	
	Vector(float xx = 0, float yy = 0, float zz = 0) : 
		x(xx), y(yy), z(zz) 
	{
	}
	
	Vector(Point to) :
		x(to.x), y(to.y), z(to.z) 
	{
	}

	Vector(Point from, Point to) : 
		x(to.x - from.x), 
		y(to.y - from.y),
		z(to.z - from.z) 
	{
	}
};

std::ostream& operator << (std::ostream &out, const Point& pt);

namespace Axis{
	const auto X = geo3d::Vector(1, 0, 0);
	const auto Y = geo3d::Vector(0, 1, 0);
	const auto Z = geo3d::Vector(0, 0, 1);
}

Vector operator * (Vector lhs, Vector rhs);
std::ostream& operator << (std::ostream &out, const Vector& vec);
bool operator == (Vector lhs, Vector rhs);
bool operator != (Vector lhs, Vector rhs);
float ScalarProduct(Vector lhs, Vector rhs);

struct Line {
	Vector direction;
	Point startingPt;
};

std::tuple<float, float> Kramer2dOnly (
	std::tuple<float, float, float> equation1, 
	std::tuple<float, float, float> equation2
);

class Plane {
public:
	Plane(float A, float B, float C, float D);
	Plane(Point p1, Point p2, Point p3);
	Plane(std::tuple<Point, Point, Point> points);
	
public:
	static Line IntersectionLine(Plane pl1, Plane pl2);
	float GetCoefficientD() const { 
		return D_; 
	}
	float GetValueFromPoint(Point p) const {
		return ( D_ + ScalarProduct(normal, Vector(p)) );
	}
	Vector getNormal() const { 
		return normal;
	}
	
private:
	Vector normal;
	float D_;
};
	
class Triangle	{
public:
	Triangle(Point p1, Point p2, Point p3);
	
public:
	std::tuple<Point, Point, Point> GetPoints() const;
	bool isIntersect(Triangle tr);
	std::tuple<float, float> FindIntersectionGap(
		Line iLine, int iPos, d3Value dval
	) const;
	
private:
	static float CalculateGapValue(float p0, float p1, float d0, float d1);

private:
	Point p1_, p2_, p3_;
};


std::tuple<int, d3Value> CheckIntersection(Triangle tr, Plane pl);

}

namespace geo2d{

struct Point {
	float x, y;
	
	Point(float xx = 0, float yy = 0):
		x(xx), y(yy)
	{
	}

};

struct Vector {
	float x, y;

	Vector(float xx, float yy) : 
		x(xx), y(yy) 
	{
	}

	Vector(Point from, Point to) : 
		x(to.x - from.x), 
		y(to.y - from.y) 
	{
	}
};

float operator * (Vector lhs, Vector rhs);

struct Segment {
	Point p1, p2;
	
	Segment(Point fp, Point sp):
		p1(fp), p2(sp)
	{	
	}
	
	static bool IsIntersect(Segment seg1, Segment seg2);
};

class Triangle {
public:
	Triangle(Point p1, Point p2, Point p3);
	Triangle() = default;
	
public:
	std::tuple<Point, Point, Point> GetPoints() const;
	bool isPointLiesIn(Point pt) const;
	bool isIntersect(Triangle tr) const;
	
private:
	Point p1_, p2_, p3_;
};

}

namespace Converters{

enum class Mode {
	NO_X,
	NO_Y,
	NO_Z,
};

geo2d::Point From3dTo2d(geo3d::Point pt, Mode mode);
geo2d::Triangle From3dTo2d (geo3d::Triangle tr, Mode mode);

}
