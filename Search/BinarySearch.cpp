#include <vector>
#include <iostream>

template<typename Collection>
using ValType = typename Collection::value_type;

template<typename Collection>
using SizeType = typename Collection::size_type;

template<typename Collection>
int binary_search(const Collection& collection, const ValType<Collection>& value)
{
    SizeType<Collection> begin = 0u;
    SizeType<Collection> end = collection.size();
    SizeType<Collection> middle = collection.size() / 2;

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
            return middle;
        }
    }

    return -1;
}

int main()
{
    const std::vector<int> vector = { 1, 5, 10, 12, 14, 15, 56, 57, 60, 66 };
    std::cout << "Index: " << binary_search(vector, 57) << std::endl;
    return EXIT_SUCCESS;
}
