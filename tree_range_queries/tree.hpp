#include <set>
#include <iostream>

namespace trees {
	
class Standart {
public:
	Standart() = default;
	
public:
	void insertKey(int key) {
		tree.insert(key);
	}
	
	size_t getRangeQuerieCount(int first, int second) {
		size_t surplus = 0; 
		
		tree_iter fi = tree.lower_bound(first);
		if(*fi == first) {surplus++;}
		
		tree_iter si = tree.upper_bound(second);
		if(*(--si) == second) {surplus++;}
		
		return (std::distance(fi, ++si) - surplus);
	}
	
private:
	using tree_iter = typename std::set<int>::iterator;
	std::set<int> tree;
};

}
