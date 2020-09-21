#include "cache.hpp"
#include "test_runner.h"

#include <unordered_map>
#include <map>
#include <utility> 
#include <iostream>
#include <stdexcept>

struct page_t {
	int id;
	double data; 
};

void TestSizeCheck() {
	size_t n = 5;
	LFUCache<page_t> cache(n);
	for(size_t i = 0; i < 1000; i++) {
		page_t p;
		p.id = i;
		cache.lookup(p);
		ASSERT_EQUAL(n, cache.getSize());
	}
}

void TestAbsoluteMiss(){
	LFUCache<page_t> cache(5);
	
	for(size_t i = 0; i < 1000; i++) {
		page_t p;
		p.id = i;
		ASSERT_EQUAL(false, cache.lookup(p));
	}
}

void TestHit() {
	LFUCache<page_t> cache(4);
	page_t p;
	p.id = 0;
	bool hit = cache.lookup(p);
	ASSERT_EQUAL(false, hit);
	
	for(size_t i=0; i < 1000; i++){
		bool hit = cache.lookup(p);
		ASSERT_EQUAL(true, hit);
	}
	
	for(size_t i=1; i < 4; i++){
		p.id = i;
		bool hit = cache.lookup(p);
		ASSERT_EQUAL(false, hit);
	}
	
	for(size_t i=0; i < 4; i++){
		p.id = i;
		bool hit = cache.lookup(p);
		ASSERT_EQUAL(true, hit);
	}
}

void TestRemovingMostRare(){
	LFUCache<page_t> cache(5);
	page_t p;
	
	for(size_t i = 0; i < 4; i++) {
		for(size_t j = 0; j < 200; j++){
			p.id = i;
			cache.lookup(p);
		}
	}
	
	p.id = 5;	
	ASSERT_EQUAL(false, cache.lookup(p));
	ASSERT_EQUAL(true, cache.lookup(p));
	p.id = 6;	
	ASSERT_EQUAL(false, cache.lookup(p));
	ASSERT_EQUAL(true, cache.lookup(p));
	p.id = 5;	
	ASSERT_EQUAL(false, cache.lookup(p));
}

int main() {
	TestRunner tr;
	
	RUN_TEST(tr, TestSizeCheck);
	RUN_TEST(tr, TestAbsoluteMiss);
	RUN_TEST(tr, TestHit);
	RUN_TEST(tr, TestRemovingMostRare);

	return 0; 
}

