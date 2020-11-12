#include "test_runner.h"
#include "../geo3d.h"

void TestVectorMultiplication() {
	// 3d Vectors
	{
		geo3d::Vector a;
		geo3d::Vector b;
		ASSERT_EQUAL(a*b, geo3d::Vector(0, 0, 0));
	}
	
	{
		geo3d::Vector a(2, 25, 8);
		geo3d::Vector b(11, 0, 3);
		ASSERT_EQUAL(a*b, geo3d::Vector(75, 82, -275));
	}
	
	{
		geo3d::Vector a(1, 5, 0);
		geo3d::Vector b(2, 10, 0);
		ASSERT_EQUAL(a*b, geo3d::Vector(0, 0, 0));
	}
	
	{
		geo3d::Vector a(1, 5, -0.5);
		geo3d::Vector b(-2, -10, 1);
		ASSERT_EQUAL(a*b, geo3d::Vector(0, 0, 0));
	}
	
	// Scalar Products
	{
		geo3d::Vector a(1, 5, 0);
		geo3d::Vector b(2, 10, 0);
		ASSERT_EQUAL(geo3d::ScalarProduct(a, b), geo3d::Vector(52));
	}
	
	{
		geo3d::Vector a(1, 5, 0);
		geo3d::Vector b(-5, 1, 0);
		ASSERT_EQUAL(geo3d::ScalarProduct(a, b), geo3d::Vector(0));
	}
	
	// 2d Vectors
	{
		geo3d::Vector a(1, 5);
		geo3d::Vector b(2, 10);
		ASSERT_EQUAL(a*b, geo3d::Vector(0, 0));
	}
}

void TestKramerMethod2dOnly() {
	{
		bool res = (
			geo3d::Kramer2dOnly(
				std::make_tuple(1, 0, 3),
				std::make_tuple(0, 2, 8)
			) == std::make_tuple(3, 4)
		);
		ASSERT_EQUAL(res, true);
	}
	
	{
		bool res = (
			geo3d::Kramer2dOnly(
				std::make_tuple(1, 6, 4),
				std::make_tuple(7, 2, 8)
			) == std::make_tuple(1, 0.5)
		);
		ASSERT_EQUAL(res, true);
	}

}

void TesIntersectionLinetFinding() {
	using namespace geo3d;	
	{
		Plane fplane(2, 3, 0, 1);
		Plane splane(1, -2, 1, -3);
		Line res = Plane::IntersectionLine(fplane, splane);
		ASSERT_EQUAL(res.direction, Vector(3, -2, -7));
		ASSERT_EQUAL(res.startingPt, Point(1, -1, 0));
	}
	
	{
		Plane fplane(1, 0, 3, 7);
		Plane splane(2, 3, 3, 2);
		Line res = Plane::IntersectionLine(fplane, splane);
		ASSERT_EQUAL(res.direction, Vector(-9, 3, 3));
		ASSERT_EQUAL(res.startingPt, Point(-7, 4, 0));
	}
	
	{
		Plane fplane(1, 2, -3, -2);
		Plane splane(1, 0, -1, 4);
		Line res = Plane::IntersectionLine(fplane, splane);
		ASSERT_EQUAL(res.direction, Vector(-2, -2, -2));
		ASSERT_EQUAL(res.startingPt, Point(-4, 3, 0));
	}
	
	{
		Plane fplane(2, 1, -1, -1);
		Plane splane(1, 3, -2, 0);
		Line res = Plane::IntersectionLine(fplane, splane);
		ASSERT_EQUAL(res.direction, Vector(1, 3, 5));
		ASSERT_EQUAL(res.startingPt, Point(0.6, -0.2, 0));
	}	
	
	{
		Plane fplane(0, 1, 0, 0);
		Plane splane(0, 0, 1, 0);
		Line res = Plane::IntersectionLine(fplane, splane);
		ASSERT_EQUAL(res.direction, Vector(1, 0, 0));
		ASSERT_EQUAL(res.startingPt, Point(0, 0, 0));
	}	
	
	{
		Plane fplane(0, 0, 1, 0);
		Plane splane(1, 0, 0, 0);
		Line res = Plane::IntersectionLine(fplane, splane);
		ASSERT_EQUAL(res.direction, Vector(0, 1, 0));
		ASSERT_EQUAL(res.startingPt, Point(0, 0, 0));
	}	
	
	{
		Plane fplane(1, 0, 0, 0);
		Plane splane(0, 1, 0, 0);
		Line res = Plane::IntersectionLine(fplane, splane);
		ASSERT_EQUAL(res.direction, Vector(0, 0, 1));
		ASSERT_EQUAL(res.startingPt, Point(0, 0, 0));
	}	
}

void Test2DTrianglesIntersection() {
	using namespace geo2d;
	{
		Triangle tr1(Point(-267.7, 267.7), Point(-227.215, 267.7), Point(-267.7, 361.065));
		Triangle tr2(Point(366.365, 198.868), Point(406.85, 198.868), Point(366.365, 292.233));
		ASSERT_EQUAL(tr1.isIntersect(tr2), false);
		ASSERT_EQUAL(tr2.isIntersect(tr1), false);		
	}
	
	{
		Triangle tr1(Point(2, 5), Point(8, 12), Point(8, 5));
		Triangle tr2(Point(3, 3), Point(3, 10), Point(9, 3));	
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}	
	
	{
		Triangle tr1(Point(-267.7, 267.7), Point(-227.215, 267.7), Point(-267.7, 361.065));
		Triangle tr2(Point(0, 0), Point(40.4847, 0), Point(0, 93.3652));
		ASSERT_EQUAL(tr1.isIntersect(tr2), false);
		ASSERT_EQUAL(tr2.isIntersect(tr1), false);
	}
	
	{
		Triangle tr1(Point(0, 0), Point(1, 1), Point(1, 0));
		Triangle tr2(Point(1, 0), Point(0, 0), Point(1, 1));	
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}
	
	{
		Triangle tr1(Point(2, 3), Point(4, 3), Point(2, 5));
		Triangle tr2(Point(3, 4), Point(5, 4), Point(5, 6));	
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}
	
    {
		Triangle tr1(Point(2, 2), Point(2, 8), Point(8, 2));
		Triangle tr2(Point(2, 4), Point(2, 6), Point(6, 4));	
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}	
	
	{
		Triangle tr1(Point(2, 2), Point(2, 8), Point(-4, 2));
		Triangle tr2(Point(2, 3), Point(2, 7), Point(6, 4));	
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}	
	
	{
		Triangle tr1(Point(3, 3), Point(6, 3), Point(6, 7));
		Triangle tr2(Point(6, 3), Point(3, 4.5), Point(6, 7));	
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}
	
	{
		Triangle tr1(Point(2, 3), Point(2, 1), Point(4, 1));
		Triangle tr2(Point(3, 1), Point(5, 1), Point(5, 3));	
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}	
	
	{
		Triangle tr1(Point(2, 2), Point(2, 9), Point(8, 2));
		Triangle tr2(Point(4, 2), Point(4, 6), Point(2, 6));	
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}	

	{
		Triangle tr1(Point(2, 2), Point(2, 9), Point(8, 2));
		Triangle tr2(Point(3, 3), Point(3, 10), Point(9, 3));	
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}	
	
	{
		Triangle tr2(Point(3, 3), Point(3, 10), Point(9, 3));
		Triangle tr1(Point(3, 3), Point(6, 7), Point(10, 5));
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}	
	
	{
		Triangle tr2(Point(7, 7), Point(7, 14), Point(13, 7));
		Triangle tr1(Point(9, 9), Point(9, -3), Point(-3, 9));
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}	
	
	{
		Triangle tr1(Point(3, 3), Point(3, 10), Point(9, 3));
		Triangle tr2(Point(1, 5), Point(5, 1), Point(7, 8));
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}	
}

void Test3DTrianglesIntersection() {
	using namespace geo3d;
	{
		Triangle tr1(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0));
		Triangle tr2(Point(0, 0, 0.01), Point(5, 5, 0.01), Point(5, 5, -0.09));
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}
	{
		Triangle tr1(Point(5, 0, 2), Point(0, 3, 2), Point(0, -3, 2));
		Triangle tr2(Point(0, 0, 7), Point(0, 2.57, -2), Point(0, -2.57, -2));
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}
	
	{
		Triangle tr1(Point(5, 0, 2), Point(0, 3, 2), Point(0, -3, 2));
		Triangle tr2(Point(4, 2, 0), Point(4, 6, 0), Point(4, 2, 8));
		ASSERT_EQUAL(tr1.isIntersect(tr2), false);
		ASSERT_EQUAL(tr2.isIntersect(tr1), false);
	}
	
	{
		Triangle tr1(Point(1, 1, 3), Point(1, 7, 3), Point(7, 4, 3));
		Triangle tr2(Point(2, 4, 0), Point(5, 4, 0), Point(7, 4, 3));
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}	
	
	{
		Triangle tr1(Point(4, 6, 3), Point(4, 6, 0), Point(0, 5, 1));
		Triangle tr2(Point(4, 2, 0), Point(4, 6, 0), Point(4, 2, 8));
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}
	
	{
		Triangle tr1(Point(-267.7, 267.7, 0), Point(-227.215, 267.7, 0), Point(-267.7, 361.065, 0));
		Triangle tr2(Point(366.365, 198.868, 0), Point(406.85, 198.868, 0), Point(366.365, 292.233, 0));
		ASSERT_EQUAL(tr1.isIntersect(tr2), false);
		ASSERT_EQUAL(tr2.isIntersect(tr1), false);		
	}
	
	{
		Triangle tr1(Point(-267.7, 267.7, 0), Point(-227.215, 267.7, 0), Point(-267.7, 361.065, 0));
		Triangle tr2(Point(0, 0, 0), Point(40.4847, 0, 0), Point(0, 93.3652, 0));
		ASSERT_EQUAL(tr1.isIntersect(tr2), false);
		ASSERT_EQUAL(tr2.isIntersect(tr1), false);
	}

	{
		Triangle tr1(Point(0, 0, 3), Point(1, 1, 3), Point(1, 0, 3));
		Triangle tr2(Point(0, 0, 4), Point(1, 1, 4), Point(1, 0, 4));
		ASSERT_EQUAL(tr1.isIntersect(tr2), false);
		ASSERT_EQUAL(tr2.isIntersect(tr1), false);
	}	
	
	{
		Triangle tr1(Point(1, 1, 3), Point(1, 7, 3), Point(7, 4, 3));
		Triangle tr2(Point(2, 4, 0), Point(5, 4, 0), Point(3, 4, 6));
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}	
	
	{
		Triangle tr1(Point(1, 0, 0), Point(0, 1, 0), Point(0, 0, 0));
		Triangle tr2(Point(0.5, -0.5, 0), Point(-0.5, 0.5, 0), Point(0, 0, 2));
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}
	
	{
		Triangle tr1(Point(1, 1, 3), Point(1, 7, 3), Point(7, 4, 3));
		Triangle tr2(Point(9, 4, 0), Point(13, 4, 0), Point(10, 4, 6));
		ASSERT_EQUAL(tr1.isIntersect(tr2), false);
		ASSERT_EQUAL(tr2.isIntersect(tr1), false);
	}	
	
	{
		Triangle tr1(Point(0, 1, 3), Point(2, 3, 1), Point(-0.3, 0.5, -0.5));
		Triangle tr2(Point(4, 0.7, 1), Point(0, 1.5, 0), Point(3, 0, -0.5));
		ASSERT_EQUAL(tr1.isIntersect(tr2), true);
		ASSERT_EQUAL(tr2.isIntersect(tr1), true);
	}
}

int main() {
	TestRunner tr;

	RUN_TEST(tr, TestVectorMultiplication);
	RUN_TEST(tr, TestKramerMethod2dOnly);
	RUN_TEST(tr, TesIntersectionLinetFinding);
	RUN_TEST(tr, Test2DTrianglesIntersection);
	RUN_TEST(tr, Test3DTrianglesIntersection);
		
	return 0;
}
