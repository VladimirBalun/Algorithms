#include <iostream>
#include <vector>
#include <deque>
#include <map>

template <typename Key, typename Value>
class FifoCache 
{
public:
	FifoCache(size_t maxSize) : maxSize(maxSize) {}
	void putElement(const std::pair<Key, Value>& element);
	Value getElement(const Key& key);
	bool isContains(const Key& key);
private:
	size_t maxSize;
	std::deque<std::pair<Key, Value>> elements;
};

template<typename Key, typename Value>
void FifoCache<Key, Value>::putElement(const std::pair<Key, Value>& element)
{
	if (elements.size() == maxSize) 
	{
		elements.pop_front();
	}
	elements.push_back(element);
}

template<typename Key, typename Value>
Value FifoCache<Key, Value>::getElement(const Key& key)
{
	for (auto it = elements.begin(); it != elements.end(); it++)
	{
		if (it->first == key)
		{
			return it->second;
		}
	}
}

template<typename Key, typename Value>
bool FifoCache<Key, Value>::isContains(const Key& key)
{ 
	for (auto it = elements.begin(); it != elements.end(); it++)
	{
		if (it->first == key) 
		{
			return true;
		}
	}
	return false;
}

int main()
{
	
	std::vector<int> dataKeys = { 100, 102, 107, 101, 100, 102, 105, 104 };
	std::map<int, std::string> dataFromDiskOrDB = { { 100, "Text from database or disk" }, 
												    { 102, "Text from database or disk" },
												    { 107, "Text from database or disk" },
												    { 101, "Text from database or disk" },
												    { 100, "Text from database or disk" },
												    { 102, "Text from database or disk" },
												    { 105, "Text from database or disk" },
												    { 104, "Text from database or disk" } };
	
	std::vector<std::string> buffer;
	FifoCache<int, std::string> cache(5);
	for (const auto& key : dataKeys)
	{
		if (cache.isContains(key)) 
		{
			std::string elementFromFifoCache = cache.getElement(key);
			std::cout << "Element with key: " << key << " was got from cache." << std::endl;
			buffer.push_back(elementFromFifoCache);
		}
		else
		{
			std::string elementFromDiskOrDB = dataFromDiskOrDB[key];
			std::cout << "Element with key: " << key << " was got from disk or database." << std::endl;
			buffer.push_back(elementFromDiskOrDB);
			cache.putElement(std::pair<int, std::string>(key, elementFromDiskOrDB));
		}
	}
	
	return EXIT_SUCCESS;
}