#include <iostream>

template <typename T>
class Stack {
public:
	explicit Stack() : size(0) {}
	explicit Stack(const Stack& other);
	explicit Stack(Stack&& other);
	Stack& operator = (const Stack& other);

	void push(const T& value);
	void pop();
	
	T top() const;
	size_t getSize() const;
	bool isEmpty() const;
	
	~Stack();
private:

	struct Node {
		T value;
		Node* last;
	};

	// recursive
	Node* copyNode(Node* other);

	Node* head;
	size_t size;
};

template <typename  T>
Stack<T>::Stack(const Stack& other)
{
	head = copyNode(other.head);
	size = other.size;
}

template <typename T>
Stack<T>::Stack(Stack&& other)
{
	head = other.head;
	size = other.size;
	other.head = nullptr;
	other.size = 0;
}

template <typename T>
Stack<T>& Stack<T>::operator = (const Stack& other)
{
	while (!isEmpty())
	{
		pop();
	}

	head = copyNode(other.head);
	size = other.size;
	return *this;
}

template<typename T>
auto Stack<T>::copyNode(Node* other) -> Node*
{
	if (other == nullptr) 
	{
		return nullptr;
	}

	Node* newNode = new Node;
	newNode->value = other->value;
	newNode->last = copyNode(other->last);
	return newNode;
}

template <typename T>
void Stack<T>::push(const T& value)
{
	Node* newElem = new Node;
	newElem->value = value;
	newElem->last = head;
	head = newElem;
	size++;
}

template <typename T>
void Stack<T>::pop()
{
	if (!isEmpty())
	{
		Node* tmpPtr = head;
		head = head->last;
		delete tmpPtr;
		size--;
	}
	else
	{
		throw std::runtime_error("Stack is empty");
	}
}

template <typename T>
T Stack<T>::top() const
{
	if (!isEmpty())
	{
		return head->value;
	}
	else
	{
		throw std::runtime_error("Stack is empty");
	}
}

template <typename T>
size_t Stack<T>::getSize() const
{
	return size;
}

template <typename T>
bool Stack<T>::isEmpty() const
{
	return size == 0;
}


template <typename T>
Stack<T>::~Stack()
{
	while (!isEmpty())
	{
		pop();
	}
}

int main()
{
	Stack<int> stack;
	Stack<int> stack2;
	int ar[] = { 4, 6, 7, 2, 8, 8 };
	for (const auto& val : ar)
	{
		stack.push(val);
	}
	
	stack2 = stack;
	while (!stack2.isEmpty())
	{
		std::cout << stack2.top() << std::endl;
		stack2.pop();
	}

	return EXIT_SUCCESS;
}