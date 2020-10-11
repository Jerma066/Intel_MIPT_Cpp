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

double pageGetter(int id) {
	return double(id);
}

void TestSizeCheck() {
	size_t n = 5;
	Caches::LFU<double> cache(n, pageGetter);
	for(size_t i = 0; i < 1000; i++) {
		page_t p;
		p.id = i;
		cache.lookup(p.id);
		ASSERT_EQUAL(n, cache.getSize());
	}
}

void TestAbsoluteMiss(){
	Caches::LFU<double> cache(5, pageGetter);
	
	for(size_t i = 0; i < 1000; i++) {
		page_t p;
		p.id = i;
		ASSERT_EQUAL(false, cache.lookup(p.id));
	}
}

void TestHit() {
	Caches::LFU<double> cache(4, pageGetter);
	page_t p;
	p.id = 0;
	bool hit = cache.lookup(p.id);
	ASSERT_EQUAL(false, hit);
	
	for(size_t i=0; i < 1000; i++){
		bool hit = cache.lookup(p.id);
		ASSERT_EQUAL(true, hit);
	}
	
	for(size_t i=1; i < 4; i++){
		p.id = i;
		bool hit = cache.lookup(p.id);
		ASSERT_EQUAL(false, hit);
	}
	
	for(size_t i=0; i < 4; i++){
		p.id = i;
		bool hit = cache.lookup(p.id);
		ASSERT_EQUAL(true, hit);
	}
}

void TestRemovingMostRare(){
	Caches::LFU<double> cache(5, pageGetter);
	page_t p;
	
	for(size_t i = 0; i < 4; i++) {
		for(size_t j = 0; j < 200; j++){
			p.id = i;
			cache.lookup(p.id);
		}
	}
	
	p.id = 5;	
	ASSERT_EQUAL(false, cache.lookup(p.id));
	ASSERT_EQUAL(true, cache.lookup(p.id));
	p.id = 6;	
	ASSERT_EQUAL(false, cache.lookup(p.id));
	ASSERT_EQUAL(true, cache.lookup(p.id));
	p.id = 5;	
	ASSERT_EQUAL(false, cache.lookup(p.id));
}

void TestBeladyScore() {
	{
		Caches::BeladyScore bscore(4);
		for(int i = 1; i < 6; i++) {
			bscore.AddToStatistics(i);
		}
		for(int i = 1; i < 5; i++) {
			bscore.AddToStatistics(i);
		}
		
		ASSERT_EQUAL(static_cast<size_t>(4), bscore.GetHitCount());
		
		bscore.AddToStatistics(5);
		
		ASSERT_EQUAL(static_cast<size_t>(4), bscore.GetHitCount());
	}
	
	{
		Caches::BeladyScore bscore(3);
		bscore.AddToStatistics(5);
		bscore.AddToStatistics(3);
		bscore.AddToStatistics(1);
		bscore.AddToStatistics(7);
		bscore.AddToStatistics(8);
		bscore.AddToStatistics(6);
		bscore.AddToStatistics(5);
		bscore.AddToStatistics(2);
		
		ASSERT_EQUAL(static_cast<size_t>(1), bscore.GetHitCount());
	}
}

int main() {
	TestRunner tr;
	
	RUN_TEST(tr, TestSizeCheck);
	RUN_TEST(tr, TestAbsoluteMiss);
	RUN_TEST(tr, TestHit);
	RUN_TEST(tr, TestRemovingMostRare);
	RUN_TEST(tr, TestBeladyScore);

	return 0; 
}

