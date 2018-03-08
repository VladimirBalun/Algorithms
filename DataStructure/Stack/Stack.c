#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
	int value;
	struct Stack* last;
} Stack;

size_t _size;

#define size() (_size)
#define isEmpty(stack) (stack == NULL)

Stack* init()
{
	_size = 0;
	return NULL;
}

void push(Stack** stack, int value)
{
	if(!isEmpty(*stack))
	{
		Stack* newElem = (Stack*) malloc(sizeof(Stack));
		newElem->value = value;
		newElem->last = *stack;
		*stack = newElem;
	}
	else 
	{
		*stack = (Stack*) malloc(sizeof(Stack));
		(*stack)->value = value;
		(*stack)->last = NULL;
	}	
	_size++;
}

void pop(Stack** stack)
{
	if(!isEmpty(*stack))
	{
		Stack* tmpPtr;
		tmpPtr = *stack;
		*stack = (*stack)->last;
		free(tmpPtr);
		_size--;
	}
	else
	{
		fprintf(stderr, "Queue is empty\n");
	}
}

int top(Stack* stack)
{
	if(!isEmpty(stack))
	{
		return stack->value;
	}
	else
	{
		fprintf(stderr, "Stack is empty\n");
		return -1;
	}
}

void clear(Stack** stack)
{
	while(!isEmpty(*stack))
	{
		pop(stack);	
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
	return EXIT_SUCCESS;
}


