#include <iostream>

template <class Type>
class Queue {
public:
	Queue() : _size(0) {}
	void push(Type& value);
	void pop();
	Type front();
	inline size_t size();
	inline bool isEmpty();
	~Queue();
private:
	struct Node {
		Type value;
		Node* next;
	};
	Node* frontElem;
	Node* topElem;
	size_t _size;	
};

template <class Type>
void Queue<Type>::push(Type& value)
{
	if(isEmpty())
	{
		frontElem = new Node;
		frontElem->value = value;
		topElem = frontElem;		
	}
	else
	{
		topElem->next = new Node;
		topElem = topElem->next;
		topElem->value = value;
	}
	_size++;
}

template <class Type>
void Queue<Type>::pop()
{
	if(!isEmpty())
	{
		Node* tmpPtr = frontElem;
		frontElem = frontElem->next;
		delete tmpPtr;
		_size--;
	}
	else
 	{
		throw std::runtime_error("Queue is empty");
	}
}

template <class Type>
Type Queue<Type>::front()
{
	if(!isEmpty())
	{
		return frontElem->value;
	}
	else
	{
		throw std::runtime_error("Queue is empty");
	}
}


template <class Type>
size_t Queue<Type>::size()
{
	return _size;
}

template <class Type>
bool Queue<Type>::isEmpty()
{
	return _size == 0; 
}

template <class Type>
Queue<Type>::~Queue()
{	
	while(!isEmpty())
	{
		pop();
	}
}

int main()
{
	Queue<int> queue;
	int ar[] = {4, 6, 7, 2, 8, 8};
	for(auto &val : ar)
	{
		queue.push(val);
	}
	std::cout << "Size queue: " << queue.size() << std::endl;
	while(!queue.isEmpty())
	{
		std::cout << queue.front() << std::endl;
		queue.pop();
	}
	std::cout << (queue.isEmpty() ? "Queue is empty" : "Queue isn' empty") << std::endl;
	return 0;
}

