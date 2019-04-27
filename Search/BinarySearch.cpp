#include <vector>
#include <iostream>

template<typename Collection, typename ValueType>
int binarySearch(Collection& array, ValueType value)
{
    typename Collection::size_type begin = 0;
    typename Collection::size_type end = array.size();
    typename Collection::size_type mid = (begin + end) / 2;
    while(begin <= end) 
    {
        if(array[mid] == value)
            return mid;
        if(value < array[mid])
            end = mid - 1;
        if(value > array[mid])
            begin = mid + 1;
        mid = (begin + end) / 2;
    }

    return -1;
}

int main()
{
    std::vector<int> vector = { 1, 5, 10, 12, 14, 15, 56, 57, 60, 66 };
    std::cout << "Index: " << binarySearch(vector, 57) << std::endl;
    return 0;
}
