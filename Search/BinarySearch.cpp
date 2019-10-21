#include <vector>
#include <iostream>
#include <functional>

template<typename Collection>
using ValType = typename Collection::value_type;

template<typename Collection>
using SizeType = typename Collection::size_type;

template<typename Collection>
int binary_search_non_recursive(const Collection& collection, const ValType<Collection>& value) noexcept
{
    SizeType<Collection> begin = 0u;
    SizeType<Collection> end = collection.size();
    SizeType<Collection> middle = end / 2;

    while (begin <= end)
    {
        if (collection[middle] < value)
        {
            begin = middle + 1;
            middle = (begin + end) / 2;
        }
        else if (collection[middle] > value)
        {
            end = middle - 1;
            middle = (begin + end) / 2;
        }
        else
        {
            return static_cast<int>(middle);
        }
    }

    return -1;
}

template<typename Collection>
int binary_search_recursive(const Collection& collection, const ValType<Collection>& value) noexcept
{
    std::function<int(const Collection&, const ValType<Collection>&, SizeType<Collection>, SizeType<Collection>)> search_impl;
    search_impl = [&search_impl] (const auto& collection, const auto& value, const auto begin, const auto end) -> int
    {
        const SizeType<Collection> middle = (begin + end) / 2;
        if (begin <= end)
        {
            if (collection[middle] < value)
            {
                return search_impl(collection, value, middle + 1, end);
            }
            else if (collection[middle] > value)
            {
                return search_impl(collection, value, begin, middle - 1);
            }
            else
            {
                return static_cast<int>(middle);
            }
        }

        return -1;
    };

    return search_impl(collection, value, 0u, collection.size());
}

int main()
{
    const std::vector<int> vector = { 1, 5, 15, 22, 46, 57, 67, 78, 98, 101, 123 };
    std::cout << "Index: " << binary_search_non_recursive(vector, 57) << std::endl;
    std::cout << "Index: " << binary_search_recursive(vector, 57) << std::endl;
    return EXIT_SUCCESS;
}
