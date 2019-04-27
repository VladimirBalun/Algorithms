#include <vector>
#include <iostream>
#include <algorithm>

template<typename Collection, typename = typename Collection::iterator>
void counting_sorting(Collection& collection) noexcept
{
    static_assert(std::is_unsigned<typename Collection::value_type>::value, "Current implementation works with unsigned types.");
    typename Collection::value_type max_value = *std::max_element(collection.begin(), collection.end());
    Collection counted_collection(max_value + 1);
    
    for (typename Collection::size_type i = 0; i < collection.size(); i++)
        counted_collection.at(collection.at(i))++;

    collection.clear();
    for (typename Collection::size_type i = 0; i < counted_collection.size(); i++)
        for (typename Collection::size_type j = 0; j < counted_collection.at(i); j++)
            collection.push_back(i);
}

int main() 
{
    std::vector<unsigned int> vector = { 7, 9, 1, 5, 8, 1, 8, 3, 7, 3 };

    std::cout << "Not sorted array: ";
    for (const auto& value : vector)
        std::cout << value << " ";

    counting_sorting(vector);

    std::cout << "\nSorted array: ";
    for (const auto& value : vector)
        std::cout << value << " ";

    return EXIT_SUCCESS;
}
