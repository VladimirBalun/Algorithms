#include <stdio.h>

#define SIZE_ARRAY 10

void selectionSort(int* ar)
{
	size_t tmp = 0;
	for (size_t i = 0; i < SIZE_ARRAY; i++)
	{
		tmp = i;
		for (size_t j = i; j < SIZE_ARRAY; j++)
		{
			if(ar[tmp] > ar[j])
			{
				tmp = j;
			}
		}
		if(tmp != i)
		{
			int tmpVar = ar[i];  // ar[i] = ar[i] ^ ar[tmp];
	    	ar[i] = ar[tmp];  	 // ar[tmp] = ar[i] ^ ar[tmp];
	    	ar[tmp] = tmpVar;    // ar[i] = ar[i] ^ ar[tmp];
		}
	}
}

int main()
{
	int ar[SIZE_ARRAY] = {1, 5, 89, 2, 7, 34, 8, 5, 9, 1};
	printf("Not sorted array: ");
	for(size_t i = 0; i < SIZE_ARRAY; i++)
	{
		printf("%d ", ar[i]);
	}
	selectionSort(ar);
	printf("\nSorted array: ");
	for(size_t i = 0; i < SIZE_ARRAY; i++)
	{
		printf("%d ", ar[i]);
	}
	return 0;
}
