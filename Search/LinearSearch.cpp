#include <vector>
#include <iostream>

template<typename Collection>
int linear_search(const Collection& collection, const typename Collection::value_type& value) noexcept
{
    for (typename Collection::size_type i = 0; i < collection.size(); ++i)
    {
        if (collection[i] == value)
        {
            return i;
        }
    }

    return -1;
}

int main()
{
    std::vector<int> vector = { 1, 5, 89, 2, 7, 34, 8, 5, 9, 1 };
    std::cout << "Index: " << linear_search(vector, 5) << std::endl;
    return EXIT_SUCCESS;
}
