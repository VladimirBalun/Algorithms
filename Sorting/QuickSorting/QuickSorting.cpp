#include <iostream>
#include <vector>

template <typename Type>
void quickSort(Type& ar, size_t left, size_t right)
{
	size_t l = left;
	size_t r = right;
	int key = ar[(l + r) / 2];
	while(l <= r)
	{
		while(ar[l] < key)
		{
			l++;
		}
		while(ar[r] > key)
		{
			r--;
		}
		if(l <= r)
		{
			std::swap(ar[l++], ar[r--]);
		}
	}
	if(left < r)
	{
		quickSort(ar, left, r);
	}
	if(right > l)
	{
		quickSort(ar, l ,right);
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
	quickSort(vector, 0, vector.size());
	std::cout << std::endl << "Sorted array: ";
	for(auto& val : vector)
	{
		std::cout << val << " ";
	}
	return 0;
}
