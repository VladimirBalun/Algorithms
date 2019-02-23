#include <list>
#include <array>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

template<typename KeyType, typename ValueType>
class LRUCache 
{
    typedef typename std::pair<KeyType, ValueType> KeyValuePair;
    typedef typename std::list<KeyValuePair>::iterator ListIterator;
public:
    explicit LRUCache(std::size_t maxSize) : mMaxSize(maxSize) {}
    void put(const KeyType& key, const ValueType& value) noexcept;
    const ValueType& get(const KeyType& key);
    bool tryGet(const KeyType& key, const ValueType& value) noexcept;
    bool exists(const KeyType& key) const noexcept;
    std::size_t size() const noexcept;
private:
    const std::size_t mMaxSize;
    std::list<KeyValuePair> mElements;
    std::unordered_map<KeyType, ListIterator> mSearchTable;
};

template<typename KeyType, typename ValueType>
void LRUCache<KeyType, ValueType>::put(const KeyType& key, const ValueType& value) noexcept
{
    auto iterator = mSearchTable.find(key);
    if (iterator == mSearchTable.end()) 
    {
        if (mElements.size() == mMaxSize) 
        {
            KeyValuePair tpmElement = mElements.back();
            mElements.pop_back();
            mSearchTable.erase(tpmElement.first);
        }
    }
    else 
    {
        mElements.erase(mSearchTable[key]);
    }

    mElements.push_front(KeyValuePair(key, value));
    mSearchTable[key] = mElements.begin();
}

template<typename KeyType, typename ValueType>
const ValueType& LRUCache<KeyType, ValueType>::get(const KeyType& key)
{
    auto iterator = mSearchTable.find(key);
    if (iterator == mSearchTable.end())
        throw std::invalid_argument("Cache does not contain element with current key.");

    mElements.splice(mElements.begin(), mElements, iterator->second);
    return iterator->second->second;
}

template<typename KeyType, typename ValueType>
bool LRUCache<KeyType, ValueType>::tryGet(const KeyType& key, const ValueType& value) noexcept
{
    auto iterator = mSearchTable.find(key);
    if (iterator == mSearchTable.end())
        return false;

    mElements.splice(mElements.begin(), mElements, iterator->second);
    value = iterator->second->second;
    return true;
}

template<typename KeyType, typename ValueType>
bool LRUCache<KeyType, ValueType>::exists(const KeyType& key) const noexcept
{
    return mSearchTable.find(key) != mSearchTable.end();
}

template<typename KeyType, typename ValueType>
std::size_t LRUCache<KeyType, ValueType>::size() const noexcept
{
    return mElements.size();
}

int main()
{
    std::uint8_t cacheSize = 5;
    std::array<int, 10> testKeys = { 1, 2, 3, 4, 1, 5, 6, 4, 4, 2 };
    LRUCache<int, std::string> cache(cacheSize);
    for (auto key : testKeys)
    {
        if (cache.exists(key))
        {
            const std::string& element = cache.get(key);
            std::cout << "Element with key: " << key << " was got from the cache" << std::endl;
        }
        else
        {
            cache.put(key, "Some data");
            std::cout << "Element with key: " << key << " is absent in the cache." << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
