#include "test_runner.h"
#include "profile.h"
#include "../tree.h"

void TestCorrectness() {
	trees::AVL tree;

	tree.insertKey(10);
	//tree.printFromNode(tree.find(10));
	tree.insertKey(20);
	//tree.printFromNode(tree.find(10));
	tree.insertKey(30);
	//tree.printFromNode(tree.find(10));
	tree.insertKey(40);
	//tree.printFromNode(tree.find(10));
	tree.insertKey(50);	
	//tree.printFromNode(tree.find(10));
	
	ASSERT_EQUAL(tree.getRangeQuerieCount(29, 41), 2);
	ASSERT_EQUAL(tree.getRangeQuerieCount(40, 50), 2);
	ASSERT_EQUAL(tree.getRangeQuerieCount(40, 41), 1);
	ASSERT_EQUAL(tree.getRangeQuerieCount(50, 51), 1);
	ASSERT_EQUAL(tree.getRangeQuerieCount(10, 20), 2);
	ASSERT_EQUAL(tree.getRangeQuerieCount(20, 30), 2);
	ASSERT_EQUAL(tree.getRangeQuerieCount(29, 31), 1);
	ASSERT_EQUAL(tree.getRangeQuerieCount(49, 51), 1);
	ASSERT_EQUAL(tree.getRangeQuerieCount(9, 11), 1);	
	
	ASSERT_EQUAL(tree.getRangeQuerieCount(10, 10), 1);
	ASSERT_EQUAL(tree.getRangeQuerieCount(20, 20), 1);
	ASSERT_EQUAL(tree.getRangeQuerieCount(30, 30), 1);
	ASSERT_EQUAL(tree.getRangeQuerieCount(40, 40), 1);
	
	ASSERT_EQUAL(tree.getRangeQuerieCount(7, 7), 0);
	ASSERT_EQUAL(tree.getRangeQuerieCount(31, 31), 0);
	ASSERT_EQUAL(tree.getRangeQuerieCount(101, 101), 0);
}

void TestSpeedUp() {
	trees::Standart stree;
	trees::AVL atree;
	for(int i = 0; i < 147483; i++) {
		stree.insertKey(i);
		atree.insertKey(i);
	}
	
	{
		LOG_DURATION("T1: Set based tree");
		stree.getRangeQuerieCount(100, 100000);
	}
	
	{
		LOG_DURATION("T1: AVL algos tree");
		atree.getRangeQuerieCount(100, 100000);
	}
}


int main() {
	TestRunner tr;

	RUN_TEST(tr, TestCorrectness);
	RUN_TEST(tr, TestSpeedUp);
		
	return 0;
}
