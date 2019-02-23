#include <iostream>
#include <vector>

template<typename Type, typename TypeValue>
size_t linearSearch(Type &ar, TypeValue val)
{
	for (size_t i = 0; i < ar.size(); i++)
	{
		if(ar[i] == val)
		{
			return i;
		}
	}
	return -1;
}

int main()
{
	std::vector<int> vector = { 1, 5, 89, 2, 7, 34, 8, 5, 9, 1 };
	std::cout << "Index: " << linearSearch(vector, 5) << std::endl;
	return 0;
}
