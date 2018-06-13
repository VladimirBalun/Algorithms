#include <iostream>

template <class Type>
class Stack {
public:
	Stack() : _size(0) {}
	void push(Type& value);
	void pop();
	Type top();
	size_t size();
	bool isEmpty();
	~Stack();
private:
	struct Node {
		Type value;
		Node* last;
	};
	Node* topElem;
	size_t _size;	
};

template <class Type>
void Stack<Type>::push(Type& value)
{
	Node* newElem = new Node;
	newElem->value = value;
	newElem->last = topElem;
	topElem = newElem;
	_size++;
}

template <class Type>
void Stack<Type>::pop()
{
	if(!isEmpty())
	{
		Node* tmpPtr = topElem;	
		topElem = topElem->last;
		delete tmpPtr;
		_size--;
	}
	else
	{
		throw std::runtime_error("Stack is empty");
	}
}

template <class Type>
Type Stack<Type>::top()
{
	if(!isEmpty())
	{
		return topElem->value;
	}
	else
	{
		throw std::runtime_error("Stack is empty");
	}
}

template <class Type>
size_t Stack<Type>::size()
{
	return _size;
}

template <class Type>
bool Stack<Type>::isEmpty()
{
	return _size == 0; 
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



