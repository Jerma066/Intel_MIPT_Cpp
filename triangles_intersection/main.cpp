#include "geo3d.h"

#include <vector>
#include <set>
#include <iostream>

int main() {
	int n;
	std::cin >> n;
	std::vector<geo3d::Triangle> trianglesVector;
	std::set<int> result;
	
	for(int i = 0; i < n; i++) {
		geo3d::Point p1;
		std::cin >> p1.x;
		std::cin >> p1.y;
		std::cin >> p1.z;
		
		geo3d::Point p2;
		std::cin >> p2.x;
		std::cin >> p2.y;
		std::cin >> p2.z;
		
		geo3d::Point p3;
		std::cin >> p3.x;
		std::cin >> p3.y;
		std::cin >> p3.z;
		
		trianglesVector.push_back(geo3d::Triangle(p1, p2, p3));
	}
	
	for(int i = 0; i < n; i++) {
		if(result.find(i) != result.end()) {
			continue;
		}
		
		for(int j = 0; j < n; j++) {		
			if( i != j && 
				trianglesVector[i].isIntersect(trianglesVector[j]) 
			) {
				result.insert(i);
				result.insert(j);
				break;
			}
		}
	}
	
	for(auto it = result.begin(); it != result.end(); it++) {
		std::cout << *it << " ";
	} 
	std::cout << std::endl;
	
	return 0;
}
