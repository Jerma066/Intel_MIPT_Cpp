#include <unordered_map>
#include <map>
#include <utility> 

using namespace std;

template <typename Data, typename Id = int>
class LFUCache {
public:
	explicit LFUCache(const size_t& size): 
		cache_size(size)
	{
	}
	
public:
	bool isFull() {
		return (lfu_hash.size() == cache_size);
	}
	
	const Id& MostRareElement() {
		return lfu_frequency.begin()->second;
	}
	
	bool Lookup(const Id &key, const Data &value){
		auto elem_it = cache_map.find(key);

		if (elem_it == cache_map.end()) {
			if (isFull()) {
				auto victim = MostRareElement();
				EraseElementInfo(victim);
				cache_map.erase(victim);
			}

			InsertElementInfo(key);
			cache_map.emplace(std::make_pair(key, value));
			return false;
		}
		else{
			UpdateElement(key);
			cache_map[key] = value;
			
			return true;
		}
	}
	
private:
	void InsertElementInfo(const Id& element){
		lfu_hash[element] = lfu_frequency.emplace_hint(
			lfu_frequency.begin(), 1, element
		);
	}
	
	void EraseElementInfo(const Id& element){
		lfu_frequency.erase(lfu_hash[element]);
		lfu_hash.erase(element);
	}
	
	void UpdateElement(const Id& id){
		auto element = lfu_hash[id];
		auto updated_elem = make_pair(element->first + 1, element->second);

		lfu_frequency.erase(element);
		lfu_hash[id] = lfu_frequency.emplace_hint(lfu_frequency.end(), 
											  move(updated_elem));
	}

private:
	using lfu_iter = typename multimap<size_t, Id>::iterator;
	
	size_t cache_size;
	std::multimap<size_t, Id> lfu_frequency;
    std::unordered_map<Id, lfu_iter> lfu_hash;
    std::unordered_map<Id, Data> cache_map;
}; 
