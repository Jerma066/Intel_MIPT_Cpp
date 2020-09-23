#include "cache.hpp"

#include <unordered_map>
#include <map>
#include <utility> 
#include <iostream>
#include <stdexcept>

using namespace Caches;

struct page_t {
	int id;
	double data; 
};

int main() {
	size_t m = 0, n = 0, hits = 0;
	LFU<page_t> c(4);	
	std::cin >> n; 

	for (size_t i = 0; i < n; ++i) {
		page_t p;
		std::cin >> p.id; 
		if (c.lookup(p)) hits += 1;
	}

	std::cout << hits << "\n";
	return 0;
}

