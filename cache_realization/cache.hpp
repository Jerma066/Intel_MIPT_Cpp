#include <unordered_map>
#include <map>
#include <utility> 
#include <list>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <map>
#include <iostream>

namespace Caches{
	
template <typename Data, typename Id = int>
class LFU {
public:
	explicit LFU(size_t size): 
		sz_(size)
	{
	}
	
public:
	bool isFull() const {
		return (lfu_hash.size() == sz_);
	}
	
	const Id& MostRareElement() const {
		return lfu_frequency.begin()->second;
	}
	
	bool lookup(const Id& id) {
		auto elem_it = cache_map.find(id);

		if (elem_it == cache_map.end()) {
			if (isFull()) {
				auto victim = MostRareElement();
				EraseElementInfo(victim);
				cache_map.erase(victim);
			}

			InsertElementInfo(id);
			auto page = GetPageFromId(id);
			cache_map.emplace(std::make_pair(id, page));
			return false;
		} 
		else {
			UpdateElement(id);
			return true;
		}
	}
	
	size_t getSize() const {
		return sz_;
	}
	
private:
	void InsertElementInfo(const Id& element) {
		lfu_hash[element] = lfu_frequency.emplace_hint(
			lfu_frequency.begin(), 1, element
		);
	}
	
	void EraseElementInfo(const Id& element) {
		lfu_frequency.erase(lfu_hash[element]);
		lfu_hash.erase(element);
	}
	
	void UpdateElement(const Id& id) {
		auto element = lfu_hash[id];
		
		lfu_frequency.erase(element);
		lfu_hash[id] = lfu_frequency.emplace_hint(
			lfu_frequency.end(), 
			std::make_pair(element->first + 1, element->second)
		);
	}
	
	Data GetPageFromId(const Id& id) const {
		//TODO: Сделать нормальную реализацию этой 
		//функции, если понадобиться
		Data result;
		return result;
	}

private:
	using lfu_iter = typename std::multimap<size_t, Id>::iterator;
	
	std::multimap<size_t, Id> lfu_frequency;
    std::unordered_map<Id, lfu_iter> lfu_hash;
    std::unordered_map<Id, Data> cache_map;
    
    size_t sz_;
}; 

template <typename Id = int>
class BeladyScore {
public:
	explicit BeladyScore(size_t size): 
		sz_(size),
		currentStateWasChanged(false),
		hc_(0)
	{
	}

public:
	void AddToStatistics(Id id) {
		input_data.push_back(id);
		currentStateWasChanged = true;
	}
	
	size_t GetHitCount() {
		if(!currentStateWasChanged)
			return hc_;
		
		hc_ = 0;
		cache.clear();
		belady_remoteness.clear();
		for(size_t i = 0; i < input_data.size(); i++) {
			if (lookup(input_data[i], i)) 
				hc_ += 1;
		}
		
		return hc_;
	}
	
private:
	bool isFull() {
		return (cache.size() == sz_);
	}
	
	void EraseMostRemoteElement() {
		auto iter = belady_remoteness.end();
		iter--;
		belady_remoteness.erase(iter);
		cache.erase(iter->second);
	}
	
	void InsertElement(const Id& id, int distance){		
		auto [cache_id_iter, flg] = cache.insert(id);
		if(flg) {
			belady_remoteness[distance] = cache_id_iter;
		}
		else {
			std::cout << "We have problems!\nPlease report to me on my mail: ragimov.ib@phystech.edu!";
		}
	}

	bool lookup(const Id& id, int current_state) {
		auto elem_it = cache.find(id);
		
		if (elem_it == cache.end()) {
			auto next_entry = find(
				input_data.begin() + current_state + 1,
				input_data.end(), id
			);
			if(isFull()) {
				if(next_entry != input_data.end()) {
					auto distance = next_entry - input_data.begin();
					auto mostRemote = belady_remoteness.rbegin()->first;
					if(distance < mostRemote) {
						EraseMostRemoteElement();
						InsertElement(id, distance);
					}
				}
				return false;
			}
			else {
				InsertElement(id, next_entry - input_data.begin());
				return false;
			}
		}
		
		return true;
	}
	
private:
	size_t sz_;
	bool currentStateWasChanged;
	size_t hc_;
	std::vector<Id> input_data;
	

	using id_iter = typename std::unordered_set<Id>::iterator;
	std::map<int, id_iter> belady_remoteness;
	std::unordered_set<Id> cache;
};

}

