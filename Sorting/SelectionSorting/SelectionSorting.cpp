#include <iostream>
#include <vector>

template <typename Type>
void selectionSort(Type &ar)
{
	size_t tmp = 0;
	for (size_t i = 0; i < ar.size(); i++)
	{
		tmp = i;
		for (size_t j = i; j < ar.size(); j++)
		{
			if(ar[tmp] > ar[j])
			{
				tmp = j;
			}
		}
		if(tmp != i)
		{
			std::swap(ar[i], ar[tmp]);
		}
	}
}

int main()
{
	std::vector<int> vector = {56, 65, 89, 0, 0, 34, 23, 5, 2, 7};
	std::cout << "Not sorted array: ";
	for(auto& val : vector)
	{
		std::cout << val << " ";
	}
	selectionSort(vector);
	std::cout << std::endl << "Sorted array: ";
	for(auto& val : vector)
	{
		std::cout << val << " ";
	}
	return 0;
}

