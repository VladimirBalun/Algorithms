#include <iostream>

template <class Type>
class Stack {
public:
	Stack() : size(0) {}
	bool isEmpty();
	void push(Type& value);
	void pop();
	Type top();
	~Stack();
private:
	struct Node {
		Type value;
		Node* last;
	};
	Node* topElem;
	size_t size;	
};

template <class Type>
bool Stack<Type>::isEmpty()
{
	return size == 0; 
}

template <class Type>
void Stack<Type>::push(Type& value)
{
	Node* newElem = new Node;
	newElem->value = value;
	newElem->last = topElem;
	topElem = newElem;
	size++;
}

template <class Type>
void Stack<Type>::pop()
{
	Node* tmpPtr = topElem;	
	topElem = topElem->last;
	delete tmpPtr;
	size--;
}

template <class Type>
Type Stack<Type>::top()
{
	return topElem->value;
}

template <class Type>
Stack<Type>::~Stack()
{	
	while(!isEmpty())
	{
		pop();
	}
}

int main()
{
	Stack<int> stack;
	int ar[] = {4, 6, 7, 2, 8, 8};
	for(auto &val : ar)
	{
		stack.push(val);
	}
	while(!stack.isEmpty())
	{
		std::cout << stack.top() << std::endl;
		stack.pop();
	}
	std::cout << (stack.isEmpty() ? "Stack is empty" : "Stack isn' empty") << std::endl;
	return 0;
}



