#include "test_runner.h"
#include "../matrix.hpp"

void TestLUDecomposition() {
	using namespace linalg;
	{
		Matrix<double> B({
			{1, 2, 1}, 
			{2, 1, 1}, 
			{1, -1, 2}
		});	
		
		Matrix<double> A({
			{1, 2, 1}, 
			{2, 1, 1}, 
			{1, -1, 2}
		});		
		
		auto[L, U] = A.LUDecomposition();
		
		Matrix<double> resL({
			{1, 0, 0},
			{2, 1, 0},
			{1, 1, 1}
		}); 
		ASSERT_EQUAL(resL, L);
		
		Matrix<double> resU({
			{1, 2, 1},
			{0, -3, -1},
			{0, 0, 2}
		});
		ASSERT_EQUAL(resU, U);
	}
}

void TestPureDeterminant() {
	using namespace linalg;
	{
		Matrix<double> A({
			{3, 21, 5}, 
			{1, 8, 7}, 
			{9, 47, 54}
		});
		
		//ASSERT_EQUAL(A.det(), 373);
		ASSERT_EQUAL(A.LUDet(), 373);
	}
	
	{
		Matrix<int> A({
			{1, 1}, 
			{1, 1}, 
		});
		
		//ASSERT_EQUAL(A.det(), 0);
		ASSERT_EQUAL(A.LUDet(), 0)
	}
	
	{
		Matrix<int> A({
			{1, 0}, 
			{0, 1}, 
		});
		
		//ASSERT_EQUAL(A.det(), 1);
		ASSERT_EQUAL(A.LUDet(), 1)
	}
}

int main() {
	TestRunner tr;

	RUN_TEST(tr, TestLUDecomposition);
	RUN_TEST(tr, TestPureDeterminant);
		
	return 0;
}
