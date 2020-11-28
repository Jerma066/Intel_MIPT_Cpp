#include "test_runner.h"
#include "profile.h"
#include "../tree.h"
#include <cstdlib> 	// для функций rand() и srand()
#include <ctime> 	// для функции time()
#include <vector>

void TestCorrectness() {
	{
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
		ASSERT_EQUAL(tree.getRangeQuerieCount(30, 10), 3);
	}
}

void TestSpeedUp() {
	trees::Standart stree;
	trees::AVL atree;
	int N = 1000;
	int border = 347483;
	std::vector<int> ranges;
	
	for (int i = 0; i < border; i++) {
		stree.insertKey(i);
		atree.insertKey(i);
	}
	
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < N; i++) {
		ranges.push_back(1 + rand() % border);
	}
	
	{
		LOG_DURATION("T1: Set based tree");
		for (int i = 0; i < ranges.size() - 2; i++) {
			stree.getRangeQuerieCount(ranges[i], ranges[i+1]);
		}
	}

	{
		LOG_DURATION("T1: AVL algos tree");
		for (int i = 0; i < ranges.size() - 2; i++) {
			atree.getRangeQuerieCount(ranges[i], ranges[i+1]);
		}
	}
}


int main() {
	TestRunner tr;

	RUN_TEST(tr, TestCorrectness);
	RUN_TEST(tr, TestSpeedUp);
		
	return 0;
}
