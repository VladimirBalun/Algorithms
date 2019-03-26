#include <vector>
#include <iostream>

template<typename Collection, typename ValueType>
int linearSearch(Collection& array, ValueType value)
{
    for (Collection::size_type i = 0; i < array.size(); i++)
        if(array[i] == value)
            return i;

    return -1;
}

int main()
{
    std::vector<int> vector = { 1, 5, 89, 2, 7, 34, 8, 5, 9, 1 };
    std::cout << "Index: " << linearSearch(vector, 5) << std::endl;
    return 0;
}
