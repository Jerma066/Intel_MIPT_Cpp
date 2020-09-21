#include "cache.hpp"

#include <unordered_map>
#include <map>
#include <utility> 
#include <iostream>
#include <stdexcept>

struct page_t {
	int id;
	double data; 
};

int main() {
	size_t m = 0, n = 0, hits = 0;
	LFUCache<page_t> c;	
	std::cin >> m >> n; 
	c.sz_ = m;

	for (size_t i = 0; i < n; ++i) {
		page_t p;
		std::cin >> p.id; 
		if (c.lookup(p)) hits += 1;
	}

	std::cout << hits << "\n";
	return 0;
}

