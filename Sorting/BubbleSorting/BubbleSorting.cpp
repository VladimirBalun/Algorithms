#include <iostream>
#include <vector>

template <typename Type>
void bubbleSort(Type &ar)
{
	bool isSorting = false;
	while(!isSorting) 
	{
	    isSorting = true;
	    for(size_t i = 0; i < ar.size() - 1; i++)
	    {
	    	if(ar[i] > ar[i + 1])
	    	{
	    		std::swap(ar[i], ar[i + 1]);
	    		isSorting = false;
	    	}
	    }
	}
}

int main()
{
	std::vector<int> vector = {1, 5, 89, 2, 7, 34, 8, 5, 9, 1};
	std::cout << "Not sorted array: ";
	for(auto& val : vector)
	{
		std::cout << val << " ";
	}
	bubbleSort(vector);
	std::cout << std::endl << "Sorted array: ";
	for(auto& val : vector)
	{
		std::cout << val << " ";
	}
	return 0;
}

