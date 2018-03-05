#include <iostream>
#include <vector>

template <typename Type>
void insertionSort(Type &ar)
{
	for(size_t i = 1; i < ar.size(); i++)
	{
		for(size_t j = i; ar[j] < ar[j - 1] && j > 0 ; j--)
		{
			std::swap(ar[j], ar[j - 1]);
		}
	}
}

int main()
{
	std::vector<int> vector = {9, 5, 1, 2, 23, 34, 8, 0, 9, 68};
	std::cout << "Not sorted array: ";
	for(auto& val : vector)
	{
		std::cout << val << " ";
	}
	insertionSort(vector);
	std::cout << std::endl << "Sorted array: ";
	for(auto& val : vector)
	{
		std::cout << val << " ";
	}
	return 0;
}