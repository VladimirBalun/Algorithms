#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

template<typename Collection, typename = typename Collection::iterator>
typename Collection::value_type find_max_subarrays_amound(Collection& collection) noexcept
{
    static_assert(!std::is_unsigned<typename Collection::value_type>::value, "Current implementation works only with signed types.");
    
    typename Collection::value_type current_amound = 0;
    typename Collection::value_type max_amound = std::numeric_limits<typename Collection::value_type>::min();
    for (typename Collection::size_type i = 0; i < collection.size(); i++)
    {
        current_amound = std::max(collection.at(i), current_amound + collection.at(i));
        max_amound = std::max(max_amound, current_amound);
    }

    return max_amound;
}

int main() 
{
    const std::vector<int> vector = { -1, 2, 4, -3, 5, 2, -5, 2 };
    const int max_amound = find_max_subarrays_amound(vector);
    std::cout << "Max amound of subarrays: " << max_amound << std::endl;

    return EXIT_SUCCESS;
}