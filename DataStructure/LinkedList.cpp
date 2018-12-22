#include <iostream>

template <typename T>
class LinkedList 
{
	struct Node
	{
		T value;
		Node* next;
		Node* prev;
	};
public:
	class Iterator 
	{
	public:
		Iterator() {}
		Iterator(Node* node) : current(node) {}
		inline Iterator& operator = (const Iterator& other) {  current = other.current; return *this; }
		inline T& operator * () { return current->value; }
		inline Iterator& operator ++ (int) { current = current->next; return *this; }
		inline bool operator != (const Iterator& other) const { return current != other.current; }
		friend void LinkedList<T>::insert(const Iterator& iterator, const T& value);
		friend void LinkedList<T>::erase(Iterator& iterator);
	private:
		Node* current;
	};

	Iterator getBeginList() const;
	Iterator getEndList() const;
	void insert(const Iterator& iterator, const T& value);
	void erase(Iterator& iterator);

	explicit LinkedList() : size(0), begin(nullptr), end(nullptr) {}
	explicit LinkedList(const LinkedList& other);
	explicit LinkedList(LinkedList&& other);
	LinkedList& operator = (const LinkedList& other);

	void pushBack(const T& value);
	void pushFront(const T& value);
	void popBack();
	void popFront();

	void clear();

	T back() const;
	T front() const;
	bool isEmpty() const;

	~LinkedList();
private:
	void copyLinkedList(const LinkedList& other);
	void pushFirstElement(const T& value);

	Node* begin;
	Node* end;
	size_t size;
};

template<typename T>
auto LinkedList<T>::getBeginList() const -> Iterator
{
	if (isEmpty())
	{
		throw std::runtime_error("List is empty.");
	}
	return Iterator(begin);
}

template<typename T>
auto LinkedList<T>::getEndList() const -> Iterator
{
	return Iterator(end->next);
}

template<typename T>
void LinkedList<T>::insert(const Iterator& iterator, const T& value)
{
	Node* tmpPrev = iterator.current;
	Node* tmpNext = iterator.current->next;
	Node* newNode = new Node;
	
	newNode->value = value;
	newNode->prev = tmpPrev;
	newNode->next = tmpNext;

	if (tmpNext == nullptr) 
	{
		end->next = newNode;
		end = end->next;
	}
	else 
	{
		tmpNext->prev = newNode;
		tmpPrev->next = newNode;
	}
	size++;
}

template<typename T>
void LinkedList<T>::erase(Iterator& iterator)
{
	Node* tmpNext = iterator.current->next;
	Node* tmpPrev = iterator.current->prev;
	Node* tmpCurr = iterator.current;
	
	if (tmpPrev == nullptr && tmpNext == nullptr)
	{
		clear();
	}
	else if (tmpPrev == nullptr) 
	{
		iterator.current = iterator.current->next;
		popFront();
	}
	else if (tmpNext == nullptr)
	{
		iterator.current = iterator.current->prev;
		popBack();
	}
	else 
	{
		tmpPrev->next = tmpNext;
		tmpNext->prev = tmpPrev;
		iterator.current = iterator.current->next;
		delete tmpCurr;
		size--;
	}
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
{
	copyLinkedList(other);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other)
{
	if (isEmpty())
		clear();

	copyLinkedList(other);
	return *this;
}

template<typename T>
void LinkedList<T>::copyLinkedList(const LinkedList& other)
{
	Node* tmpOther = other.begin;
	begin = new Node;
	begin->value = tmpOther->value;
	begin->prev = nullptr;
	begin->next = nullptr;
	end = begin;
	tmpOther = tmpOther->next;

	while (tmpOther != nullptr)
	{
		Node* tmpPtr = end;
		end->next = new Node;
		end = end->next;
		end->prev = tmpPtr;
		end->next = nullptr;
		end->value = tmpOther->value;
		tmpOther = tmpOther->next;
	}
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList&& other)
{
	begin = other.begin;
	end = other.end;
	size = other.size;
	other.begin = nullptr;
	other.end = nullptr;
	other.size = 0;
}

template<typename T>
void LinkedList<T>::pushBack(const T& value)
{
	if (isEmpty()) 
	{
		pushFirstElement(value);
	}
	else 
	{
		Node* tmpPtr = end;
		end->next = new Node;
		end = end->next;
		end->prev = tmpPtr;
		end->next = nullptr;
		end->value = value;
	}
	size++;
}

template<typename T>
void LinkedList<T>::pushFront(const T & value)
{
	if (isEmpty())
	{
		pushFirstElement(value);
	}
	else
	{
		Node* tmpPtr = begin;
		begin->prev = new Node;
		begin = begin->prev;
		begin->next = tmpPtr;
		begin->prev = nullptr;
		begin->value = value;
	}
	size++;
}

template<typename T>
void LinkedList<T>::pushFirstElement(const T& value)
{
	Node* head = new Node;
	head->value = value;
	head->prev = nullptr;
	head->next = nullptr;
	begin = head;
	end = head;
}

template<typename T>
void LinkedList<T>::popBack()
{
	if (isEmpty()) 
	{
		throw std::runtime_error("List is empty.");
	}

	Node* tmpPtr = end;
	end = end->prev;
	delete tmpPtr;
	size--;
}

template<typename T>
void LinkedList<T>::popFront()
{
	if (isEmpty())
		throw std::runtime_error("List is empty.");

	Node* tmpPtr = begin;
	begin = begin->next;
	delete tmpPtr;
	size--;
}

template<typename T>
void LinkedList<T>::clear()
{
	if (isEmpty()) 
		return;

	while (begin != end)
	{
		begin = begin->next;
		delete begin->prev;
	}
	
	delete end;
	size = 0;
}

template<typename T>
T LinkedList<T>::back() const
{
	return end->value;
}

template<typename T>
T LinkedList<T>::front() const
{
	return begin->value;
}

template<typename T>
bool LinkedList<T>::isEmpty() const
{
	return size == 0;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	clear();
}

int main()
{
	LinkedList<int> list;
	list.pushBack(10);
	list.pushFront(5);
	list.pushBack(20);

	for (LinkedList<int>::Iterator it = list.getBeginList(); it != list.getEndList(); it++)
	{
		if (*it == 5) 
			list.erase(it);
		if (*it == 10)
			list.insert(it, 15);
	}

	while (!list.isEmpty())
	{
		std::cout << list.front() << std::endl;
		list.popFront();
	}

	return EXIT_SUCCESS;
}
