#include <stdio.h>

#define SIZE_ARRAY 10

void insertionSort(int *ar)
{
	for(size_t i = 1; i < SIZE_ARRAY; i++)
	{
		for(size_t j = i; ar[j] < ar[j - 1] && j > 0 ; j--)
		{
	    	int tmp = ar[j];    // ar[j] = ar[j] ^ ar[j - 1];
	    	ar[j] = ar[j - 1];  // ar[j - 1] = ar[j] ^ ar[j - 1];
	    	ar[j - 1] = tmp;    // ar[j] = ar[j] ^ ar[j - 1];
		}
	}
}


int main()
{
	int ar[SIZE_ARRAY] = {9, 5, 1, 2, 23, 34, 8, 0, 9, 68};
	printf("Not sorted array: ");
	for(size_t i = 0; i < SIZE_ARRAY; i++)
	{
		printf("%d ", ar[i]);
	}
	insertionSort(ar);
	printf("\nSorted array: ");
	for(size_t i = 0; i < SIZE_ARRAY; i++)
	{
		printf("%d ", ar[i]);
	}
	return 0;
}