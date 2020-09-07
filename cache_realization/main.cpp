#include "test_runner.h"
#include "cache.hpp"

#include <unordered_map>
#include <map>
#include <utility> 
#include <iostream>

using namespace std;

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void TestAbsoluteMiss(){
	LFUCache<double, int> cache(5);
	
	for(size_t i = 0; i < 1000; i++) {
		ASSERT_EQUAL(false, cache.Lookup(i, fRand(-1000, 1000)));
	}
}

void TestHit() {
	LFUCache<double, int> cache(4);
	bool hit = cache.Lookup(0, fRand(-1000, 1000));
	ASSERT_EQUAL(false, hit);
	
	for(size_t i=0; i<1000; i++){
		bool hit = cache.Lookup(0, fRand(-1000, 1000));
		ASSERT_EQUAL(true, hit);
	}
	
	for(size_t i=1; i<4; i++){
		bool hit = cache.Lookup(i, fRand(-1000, 1000));
		ASSERT_EQUAL(false, hit);
	}
	
	for(size_t i=0; i<4; i++){
		bool hit = cache.Lookup(i, fRand(-1000, 1000));
		ASSERT_EQUAL(true, hit);
	}
}

void TestRemovingMostRare(){
	LFUCache<double, int> cache(5);
	
	for(size_t i = 0; i < 4; i++) {
		for(size_t j = 0; j < 200; j++){
			cache.Lookup(i, fRand(-1000, 1000));
		}
	}
		
	ASSERT_EQUAL(false, cache.Lookup(5, fRand(-1000, 1000)));
	ASSERT_EQUAL(true, cache.Lookup(5, fRand(-1000, 1000)));
	ASSERT_EQUAL(false, cache.Lookup(6, fRand(-1000, 1000)));
	ASSERT_EQUAL(true, cache.Lookup(6, fRand(-1000, 1000)));
	ASSERT_EQUAL(false, cache.Lookup(5, fRand(-1000, 1000)));
}

int main() {
	TestRunner tr;
	
	RUN_TEST(tr, TestAbsoluteMiss);
	RUN_TEST(tr, TestHit);
	RUN_TEST(tr, TestRemovingMostRare);


	return 0;
}

