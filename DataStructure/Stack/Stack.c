#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
	int value;
	struct Stack* last;
} Stack;

#define isEmpty(topElem) (topElem == NULL)

Stack* init()
{
	return NULL;
}

void push(Stack** topElem, int value)
{
	if(topElem)
	{
		Stack* newElem = (Stack*) malloc(sizeof(Stack));
		newElem->value = value;
		newElem->last = *topElem;
		*topElem = newElem;
	}
	else 
	{
		*topElem = (Stack*) malloc(sizeof(Stack));
		(*topElem)->value = value;
		(*topElem)->last = NULL;
	}	
}

void pop(Stack** topElem)
{
	Stack* tmpPtr;
	tmpPtr = *topElem;
	*topElem = (*topElem)->last;
	free(tmpPtr);
}

int top(Stack* topElem)
{
	return topElem->value;
}

void clear(Stack** topElem)
{
	while(!isEmpty(*topElem))
	{
		pop(topElem);	
	}
}

int main()
{
	Stack* stack = init();
	#define SIZE_AR 5
	int ar[SIZE_AR] = {1, 2, 3, 4, 5};
	for(size_t i = 0; i < SIZE_AR; i++)
	{
		push(&stack, ar[i]);
	}
	for(size_t i = 0; i < SIZE_AR; i++)
	{
		printf("%d\n", top(stack));
		pop(&stack);
	}
	printf(isEmpty(stack) ? "Stack is empty\n" : "Stack isn't empty\n");
	return 0;
}


