#include "test_runner.h"
#include "../matrix.hpp"

void TestMatrixMultiplicaion() {
	using namespace linalg;
	{
		Matrix<double> A({
			{3, 21, 5}, 
			{1, 8, 7}, 
			{9, 47, 54}
		});
		
		Matrix<double> B({
			{1, 2, 1}, 
			{2, 1, 1}, 
			{1, -1, 2}
		});	
		
		Matrix<double> res({
			{50, 22, 34}, 
			{24, 3, 23}, 
			{157, 11, 164}
		});	
				
		ASSERT_EQUAL(A*B, res);
	}
	
}

void TestDeterminant() {
	using namespace linalg;
	{
		Matrix<double> A({
			{3, 21, 5}, 
			{1, 8, 7}, 
			{9, 47, 54}
		});
		
		ASSERT_EQUAL(A.GDet(), 373);
	}
	
	{
		Matrix<int> A({
			{1, 1}, 
			{1, 1}, 
		});
		
		ASSERT_EQUAL(A.GDet(), 0);
		
	}
	
	{
		Matrix<int> A({
			{1, 0}, 
			{0, 1}, 
		});
		
		ASSERT_EQUAL(A.GDet(), 1);
		
	}
}

int main() {
	TestRunner tr;

	//RUN_TEST(tr, TestLUDecomposition);
	RUN_TEST(tr, TestDeterminant);
	RUN_TEST(tr, TestMatrixMultiplicaion);
		
	return 0;
}
