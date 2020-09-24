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
	std::cin >> m;
	Caches::LFU<page_t> c(m);	
	std::cin >> n; 

	for (size_t i = 0; i < n; ++i) {
		page_t p;
		std::cin >> p.id; 
		if (c.lookup(p.id)) hits += 1;
	}

	std::cout << hits << "\n";
	return 0;
}

