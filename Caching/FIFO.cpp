#include <map>
#include <deque>
#include <vector>
#include <cstdint>
#include <iostream>
#include <stdexcept>

template<typename Key, typename Value>
class FifoCache
{
public:
    explicit FifoCache(std::size_t maxSize) noexcept : mMaxSize(maxSize) {}
    void putElement(const std::pair<Key, Value>& element) noexcept;
    Value getElement(const Key& key);
    bool isContains(const Key& key) const noexcept;
private:
    const std::size_t mMaxSize;
    std::deque<std::pair<Key, Value>> mElements;
};

template<typename Key, typename Value>
void FifoCache<Key, Value>::putElement(const std::pair<Key, Value>& element) noexcept
{
    if (mElements.size() == mMaxSize)
        mElements.pop_front();
    mElements.push_back(element);
}

template<typename Key, typename Value>
Value FifoCache<Key, Value>::getElement(const Key& key)
{
    for (const auto& iterator : mElements)
        if (iterator.first == key)
            return iterator.second;

    throw std::invalid_argument("Cache does not contain current element");
}

template<typename Key, typename Value>
bool FifoCache<Key, Value>::isContains(const Key& key) const noexcept
{
    for (const auto& iterator : mElements)
        if (iterator.first == key)
            return true;

    return false;
}

int main()
{
    const std::vector<std::uint16_t> dataKeys = { 100, 102, 107, 101, 100, 102, 105, 104 };
    const std::map<std::uint16_t, std::string> dataFromDiskOrDB = {
        { 100, "Text from database or disk" },
        { 102, "Text from database or disk" },
        { 107, "Text from database or disk" },
        { 101, "Text from database or disk" },
        { 105, "Text from database or disk" },
        { 104, "Text from database or disk" } 
    };

    std::vector<std::string> buffer;
    FifoCache<std::uint16_t, std::string> cache(5);
    try 
    {
        for (const auto& key : dataKeys)
        {
            if (cache.isContains(key))
            {
                const std::string elementFromFifoCache = cache.getElement(key);
                std::cout << "Element with key: " << key << " was got from cache." << std::endl;
                buffer.push_back(elementFromFifoCache);
            }
            else
            {
                const std::string elementFromDiskOrDB = dataFromDiskOrDB.at(key);
                std::cout << "Element with key: " << key << " was got from disk or database." << std::endl;
                buffer.push_back(elementFromDiskOrDB);
                cache.putElement({ key, elementFromDiskOrDB }); // replace the element in the cache
            }
        }
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error! Cause: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
