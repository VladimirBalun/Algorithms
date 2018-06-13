#include <iostream>
#include <vector>

template <typename Type, typename TypeValue>
size_t binarySearch(Type &ar, TypeValue val)
{
	size_t begin = 0;
	size_t end = ar.size();
	size_t mid = (begin + end) / 2;
	while(begin <= end) 
	{
	    if(ar[mid] == val)
	    {
	    	return mid;
	    } 
	    if(val < ar[mid])
	    {
	    	end = mid - 1;
	    }
	    if(val > ar[mid])
	    {
	    	begin = mid + 1;
	    }
	    mid = (begin + end) / 2;
	}
	return -1;
}

int main()
{
	std::vector<int> vector = {1, 5, 10, 12, 14, 15, 56, 57, 60, 66};
	std::cout << "Index: " << binarySearch(vector, 57) << std::endl;
	return 0;
}
