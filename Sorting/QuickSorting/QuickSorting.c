#include <stdio.h>

#define SIZE_ARRAY 10

void quickSort(int* ar, size_t left, size_t right)
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
			int tmp = ar[l];    
	    	ar[l] = ar[r];  	
	    	ar[r] = tmp;    
	    	l++;
	    	r--;	
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
	int ar[SIZE_ARRAY] = {1, 5, 89, 2, 7, 34, 8, 5, 9, 1};
	printf("Not sorted array: ");
	for(size_t i = 0; i < SIZE_ARRAY; i++)
	{
		printf("%d ", ar[i]);
	}
	quickSort(ar, 0, SIZE_ARRAY - 1);
	printf("\nSorted array: ");
	for(size_t i = 0; i < SIZE_ARRAY; i++)
	{
		printf("%d ", ar[i]);
	}
	return 0;
}
