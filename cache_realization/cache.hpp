#include <unordered_map>
#include <map>
#include <utility> 
#include <list>

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

}

