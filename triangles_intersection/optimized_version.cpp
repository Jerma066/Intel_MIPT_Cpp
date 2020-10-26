#include "geo3d.h"

#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <utility>

bool operator < (const geo3d::Triangle& l_tr, const geo3d::Triangle& r_tr) {
	geo3d::Point max_l_val;
	max_l_val.x = std::max(std::max(l_tr.p1_.x, l_tr.p2_.x), l_tr.p3_.x);
	max_l_val.y = std::max(std::max(l_tr.p1_.y, l_tr.p2_.y), l_tr.p3_.y);
	max_l_val.z = std::max(std::max(l_tr.p1_.z, l_tr.p2_.z), l_tr.p3_.z);
	
	geo3d::Point min_r_val;
	min_r_val.x = std::min(std::min(r_tr.p1_.x, r_tr.p2_.x), r_tr.p3_.x);
	min_r_val.y = std::min(std::min(r_tr.p1_.y, r_tr.p2_.y), r_tr.p3_.y);
	min_r_val.z = std::min(std::min(r_tr.p1_.z, r_tr.p2_.z), r_tr.p3_.z);
	
	if(max_l_val.x < min_r_val.x) {return true;}
	if(max_l_val.y < min_r_val.y) {return true;}
	if(max_l_val.z < min_r_val.z) {return true;}

	return false;
}

bool operator > (const geo3d::Triangle& l_tr, const  geo3d::Triangle& r_tr) {
	return (r_tr < l_tr);
}

bool operator == (const geo3d::Triangle& l_tr, const geo3d::Triangle& r_tr) {
	if(!(l_tr < r_tr) && !(l_tr > r_tr) )
		return true;
		
	return false;
}

struct tr_less {
    bool operator() (const geo3d::Triangle& lhs, const geo3d::Triangle& rhs) const{
        return lhs < rhs;
    }
};

int main() {
	int n;
	std::cin >> n;
	std::multimap<geo3d::Triangle, int, tr_less> triangles;
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
		
		triangles.insert(std::make_pair(geo3d::Triangle(p1, p2, p3), i));
	}
	
	std::multimap<geo3d::Triangle, int>::iterator cur_tr = triangles.begin();
	std::multimap<geo3d::Triangle, int>::iterator next_cur_tr = triangles.begin();
	
	while(cur_tr != triangles.end()) {
		int chunk_size = triangles.count(cur_tr->first);
		
		//std::cout << "Chunk size: " << chunk_size << "\n";
		
		if(chunk_size ==0) {
			cur_tr++;
			continue;
		}
		else {
			for(int i = 0; i < chunk_size; i++) {
				next_cur_tr++;
			}
		}
		
		
		auto chunk_start_elem = triangles.find(cur_tr->first);
		for(int i = 0; i < chunk_size; i++) {
			if(result.find(cur_tr->second) != result.end()) {
				cur_tr++;
				continue;
			}
			
			auto intersec_tr = chunk_start_elem; 
			
			for(int j = 0; j < chunk_size; j++) {
				if(intersec_tr == triangles.end() || cur_tr == triangles.end())
					break;
				
				if(geo3d::Triangle(cur_tr->first).isIntersect(intersec_tr->first) 
				   && (intersec_tr != cur_tr)) 
				{
					result.insert(cur_tr->second);
					result.insert(intersec_tr->second);
					break;
				}
				intersec_tr++;
			}
			
			intersec_tr = chunk_start_elem;
			cur_tr++;
		}
		cur_tr = next_cur_tr;	
	}
	
	for(auto it = result.begin(); it != result.end(); it++) {
		std::cout << *it << " ";
	} 
	std::cout << std::endl;
	
	return 0;
}


