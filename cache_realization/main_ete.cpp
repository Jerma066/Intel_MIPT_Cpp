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
	Caches::BeladyScore bscore(m);	
	std::cin >> n; 

	for (size_t i = 0; i < n; ++i) {
		page_t p;
		std::cin >> p.id; 
		bscore.AddToStatistics(p.id);
		if (c.lookup(p.id)) hits += 1;
	}

	auto bhits = bscore.GetHitCount();
	
	if(bhits > hits) {
		std::cout << "Beladi gives an advantage in " << bhits - hits << "hits:" << std::endl;
	}
	else if (bhits == hits) {
		std::cout << "In this case, the approaches give an equivalent result" << std::endl;
	}
	else {
		std::cout << "LFU gives an advantage in " << hits - bhits  << "hits:" << std::endl;
	}
	
	std::cout << "LFU Cache result is " << hits << std::endl;
	std::cout << "Belady Cache result is " << bhits << std::endl;
	
	
	
	
	return 0;
}

