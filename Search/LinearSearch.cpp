#include <vector>
#include <iostream>

template<typename Collection>
using ValType = typename Collection::value_type;

template<typename Collection>
using SizeType = typename Collection::size_type;

template<typename Collection>
int linear_search_non_recursive(const Collection& collection, const ValType<Collection>& value) noexcept
{
    for (SizeType<Collection> i = 0; i < collection.size(); ++i)
    {
        if (collection[i] == value)
        {
            return i;
        }
    }

    return -1;
}

template<typename Collection>
int linear_search_recursive(const Collection& collection, const ValType<Collection>& value, SizeType<Collection> index) noexcept
{
    if (collection.size() == index)
    {
        return -1;
    }
    else if (collection[index] == value)
    {
        return index;
    }
    else
    {
        return linear_search_recursive(collection, value, index + 1);
    }
}

int main()
{
    const std::vector<int> vector = { 1, 5, 89, 2, 7, 34, 8, 5, 9, 1 };
    std::cout << "Index: " << linear_search_recursive(vector, 34, 0u) << std::endl;
    std::cout << "Index: " << linear_search_non_recursive(vector, 5) << std::endl;
    return EXIT_SUCCESS;
}
