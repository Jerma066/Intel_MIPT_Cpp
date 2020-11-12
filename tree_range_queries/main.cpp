#include "tree.h"

#include <iostream>
#include <vector>


int main() { 
	size_t N;
	std::cin >> N;
	trees::AVL tree;
	
	for(size_t i = 0; i < N; i++) {
		int key;
		std::cin >> key;
		tree.insertKey(key);
	}
	
	size_t M;
	std::cin >> M;
	std::vector<size_t> result;
	result.reserve(M+1);
	
	for(size_t i = 0; i < M; i++) {
		int lb; std::cin >> lb;
		int ub; std::cin >> ub;
		//std::cout << lb << "; " << ub << std::endl;
		result.push_back(tree.getRangeQuerieCount(lb, ub));
	}

	for(auto it = result.begin(); it != result.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
