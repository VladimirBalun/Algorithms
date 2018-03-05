#include <stdio.h>

#define SIZE_ARRAY 10

size_t linearSearch(int* ar, int val)
{
	for (size_t i = 0; i < SIZE_ARRAY; i++)
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
	int ar[SIZE_ARRAY] = {1, 5, 89, 2, 7, 34, 8, 5, 9, 1};
	printf("Index: %ld \n", linearSearch(ar, 5));
	return 0;
}
