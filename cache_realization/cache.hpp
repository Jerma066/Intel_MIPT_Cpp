#include <unordered_map>
#include <map>
#include <utility> 
#include <list>


template <typename Data, typename Id = int>
class LFUCache {
public:
	explicit LFUCache(size_t size): 
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
	
	bool lookup(const Data& page) {
		int key = page.id;
		auto elem_it = cache_map.find(key);

		if (elem_it == cache_map.end()) {
			if (isFull()) {
				auto victim = MostRareElement();
				EraseElementInfo(victim);
				cache_map.erase(victim);
			}

			InsertElementInfo(key);
			cache_map.emplace(std::make_pair(key, page));
			return false;
		} 
		else {
			UpdateElement(key);
			cache_map[key] = page;
			return true;
		}
	}
	
	size_t getSize() const {
		return sz_;
	}
	
	void setSize(size_t size) {
		sz_ = size;
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

private:
	using lfu_iter = typename std::multimap<size_t, Id>::iterator;
	
	std::multimap<size_t, Id> lfu_frequency;
    std::unordered_map<Id, lfu_iter> lfu_hash;
    std::unordered_map<Id, Data> cache_map;
    
    size_t sz_;
}; 
