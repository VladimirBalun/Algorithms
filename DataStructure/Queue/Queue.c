#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
	int value;
	struct Queue* next;
} Queue;

size_t _size;
Queue* first;

#define size() (_size)
#define isEmpty() (first == NULL)

Queue* init()
{
	_size = 0;
	first = NULL;
	return NULL;
}

void push(Queue** queue, int value)
{
	if(!isEmpty())
	{
		Queue* newElem = (Queue*) malloc(sizeof(Queue));
		newElem->value = value;
		newElem->next = NULL;
		(*queue)->next = newElem;
		*queue = (*queue)->next;
	} 
	else
	{
		*queue = (Queue*) malloc(sizeof(Queue));
		(*queue)->value = value;		
		(*queue)->next = NULL;
		first = *queue;
		
	}
	_size++;
}

void pop()
{
	if(!isEmpty())
	{
		Queue* tmpPtr;
		tmpPtr = first;
		first = first->next;
		free(tmpPtr);	
		_size--;
	}
	else
	{
		fprintf(stderr, "Queue is empty\n");
	}
}

int front()
{
	if(!isEmpty())
	{
		return first->value;
	}
	else
	{
		fprintf(stderr, "Queue is empty\n");
		return -1;
	}
}

void clear()
{
	while(!isEmpty())
	{
		pop();
	}
}

int main()
{
	Queue* queue = init();
	#define SIZE_AR 5
	int ar[SIZE_AR] = {1, 2, 3, 4, 5};
	for(size_t i = 0; i < SIZE_AR; i++)
	{
		push(&queue, ar[i]);
	}
	for(size_t i = 0; i < SIZE_AR; i++)
	{
		printf("%d\n", front(queue));
		pop();
	}
	printf(isEmpty() ? "Queue is empty\n" : "Queue isn't empty\n");
	return EXIT_SUCCESS;
}
