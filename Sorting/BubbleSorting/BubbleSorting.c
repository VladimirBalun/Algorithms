#include <stdio.h>

typedef int bool;
#define true 1
#define false 0

#define SIZE_ARRAY 10

void bubbleSort(int* ar)
{
	bool isSorting = false;
	while(!isSorting) 
	{
	    isSorting = true;
	    for(size_t i = 0; i < SIZE_ARRAY - 1; i++)
	    {
	    	if(ar[i] > ar[i + 1])
	    	{
	    		int tmp = ar[i];    // ar[i] = ar[i] ^ ar[i + 1];
	    		ar[i] = ar[i + 1];  // ar[i + 1] = ar[i] ^ ar[i + 1];
	    		ar[i + 1] = tmp;    // ar[i] = ar[i] ^ ar[i + 1];
	    		isSorting = false;
	    	}
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
	bubbleSort(ar);
	printf("\nSorted array: ");
	for(size_t i = 0; i < SIZE_ARRAY; i++)
	{
		printf("%d ", ar[i]);
	}
	return 0;
}
