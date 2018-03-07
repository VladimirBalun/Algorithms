#include <stdio.h>

#define SIZE_ARRAY 10

size_t binarySearch(int *ar, int val)
{
	size_t begin = 0;
	size_t end = SIZE_ARRAY;
	size_t mid = (begin + end) / 2;
	while(begin <= end) 
	{
	    if(ar[mid] == val)
	    {
	    	return mid;
	    } 
	    if(val < ar[mid])
	    {
	    	end = mid - 1;
	    }
	    if(val > ar[mid])
	    {
	    	begin = mid + 1;
	    }
	    mid = (begin + end) / 2;
	}
	return -1;
}

int main()
{
	int ar[SIZE_ARRAY] = {1, 5, 89, 2, 7, 34, 8, 5, 9, 1};
	printf("Index: %ld \n", binarySearch(ar, 5));
	return 0;
}
