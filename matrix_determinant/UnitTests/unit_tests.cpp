#include "test_runner.h"
#include "../matrix.h"


void TestLUDecomposition() {
	using namespace linalg;
	{
		Matrix A({
			{1, 2, 1}, 
			{2, 1, 1}, 
			{1, -1, 2}
		});		
		auto[L, U] = A.LUDecomposition();
		
		Matrix resL({
			{1, 0, 0},
			{2, 1, 0},
			{1, 1, 1}
		}); 
		ASSERT_EQUAL(resL, L);
		
		Matrix resU({
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
		Matrix A({
			{3, 21, 5}, 
			{1, 8, 7}, 
			{9, 47, 54}
		});
		
		//ASSERT_EQUAL(A.det(), 373);
		ASSERT_EQUAL(A.LUDet(), 373);
	}
	
	{
		Matrix A({
			{1, 1}, 
			{1, 1}, 
		});
		
		//ASSERT_EQUAL(A.det(), 0);
		ASSERT_EQUAL(A.LUDet(), 0)
	}
	
	{
		Matrix A({
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
