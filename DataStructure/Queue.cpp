#include <iostream>

template <typename T>
class Queue 
{
	struct Node 
	{
        T value;
        Node* next;
    };
public:
    explicit Queue() : size(0) {}
    explicit Queue(const Queue& other);
    explicit Queue(Queue&& other);
    Queue& operator = (const Queue& other);
    Queue& operator = (Queue&& other);

    void push(const T& value);
    void pop();
    void clear();

    T front() const;
    inline size_t getSize() const;
    inline bool isEmpty() const;

    ~Queue();
private:
    //recursive
    Node* copyNode(Node* other);

    Node* head;
    size_t size;
};

template <typename T>
Queue<T>::Queue(const Queue& other)
{
    head = copyNode(other.head);
    size = other.size;
}

template <typename T>
Queue<T>::Queue(Queue&& other)
{
    head = other.head;
    other.head = nullptr;
    size = other.size;
    other.size = 0;
}

template <typename T>
Queue<T>& Queue<T>::operator = (const Queue& other)
{
    if (!isEmpty())
    {
        clear();
    }

    head = copyNode(other.head);
    size = other.size;
	return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator = (Queue&& other)
{
    if (!isEmpty())
    {
        clear();
    }

    head = other.head;
    other.head = nullptr;
    size = other.size;
    other.size = 0;
	return *this;
}

template <typename T>
auto Queue<T>::copyNode(Node* other) -> Node*
{
    if (!other)
    {
        return nullptr;
    }

    Node* newNode = new Node;
    newNode->value = other->value;
    newNode->next = copyNode(other->next);
    return newNode;
}

template <typename T>
void Queue<T>::push(const T& value)
{
    if(isEmpty())
    {
        head = new Node;
        head->value = value;
    }
    else
    {
        Node* newHead = new Node;
        newHead->value = value;
        newHead->next = head;
        head = newHead;
    }
    size++;
}

template <typename T>
void Queue<T>::pop()
{
    if(!isEmpty())
    {
        Node* tmpPtr = head;
        head = head->next;
        delete tmpPtr;
        size--;
    }
    else
    {
        throw std::runtime_error("Queue is empty");
    }
}

template <typename T>
void Queue<T>::clear()
{
    while(!isEmpty())
        pop();
}

template <typename T>
T Queue<T>::front() const
{
    if(!isEmpty())
        return head->value;
    else
        throw std::runtime_error("Queue is empty");
}


template <typename T>
size_t Queue<T>::getSize() const
{
    return size;
}

template <typename T>
bool Queue<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
Queue<T>::~Queue()
{
    clear();
}

int main()
{
    Queue<int> queue1;
    Queue<int> queue2;
    int ar[] = {4, 6, 7, 2, 8, 8};
	
    for(auto &val : ar)
        queue1.push(val);

    queue2 = std::move(queue1);
    while(!queue2.isEmpty())
    {
        std::cout << queue2.front() << std::endl;
        queue2.pop();
    }

    return EXIT_SUCCESS;
}

