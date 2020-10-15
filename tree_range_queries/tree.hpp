#include <set>


namespace trees {
	
class Standart {
public:
	Standart() = default;
	
public:
	void insertKey(int key) {
		tree.insert(key);
	}
	size_t getRangeQuerieCount(int first, int second) {
		size_t cnt = 0;
		for(auto it = tree.lower_bound(first); it != tree.upper_bound(second); it++) {
			cnt++; 
		}
		return cnt;
	}
	
private:
	std::set<int> tree;
};

}
