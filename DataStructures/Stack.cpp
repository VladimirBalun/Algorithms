#include <iostream>
#include <stdexcept>

template<typename Type>
class Stack
{
public:
    explicit Stack() noexcept = default;
    explicit Stack(const Stack& another);
    Stack& operator=(const Stack& another);
    explicit Stack(Stack&& another);
    Stack& operator=(Stack&& another);
    void push(const Type& value) noexcept;
    void pop();
    void clear();
    Type top() const;
    size_t getSize() const noexcept;
    bool isEmpty() const noexcept;
    ~Stack();
private:
    struct Node
    {
        Type value;
        Node* prev;
    };
    Node* copyNode(Node* another) const noexcept;
private:
    Node* mHead = nullptr;
    std::size_t mSize = 0;
};

template<typename  Type>
Stack<Type>::Stack(const Stack& another)
{
    mHead = copyNode(another.mHead);
    mSize = another.mSize;
}

template<typename Type>
Stack<Type>& Stack<Type>::operator=(const Stack& another)
{
    if (this != &another)
    {
        if (!isEmpty())
            clear();
        mHead = copyNode(another.mHead);
        mSize = another.mSize;
    }
    return *this;
}

template<typename Type>
Stack<Type>::Stack(Stack&& another)
{
    mHead = another.mHead;
    mSize = another.mSize;
    another.mHead = nullptr;
    another.mSize = 0;
}

template<typename Type>
Stack<Type>& Stack<Type>::operator=(Stack&& another)
{
    if (this != &another)
    {
        if (!isEmpty())
            clear();
        mHead = another.mHead;
        mSize = another.mSize;
        another.mHead = nullptr;
        another.mSize = 0;
    }
    return *this;
}

template<typename Type>
auto Stack<Type>::copyNode(Node* another) const noexcept -> Node*
{
    if (!another)
        return nullptr;

    Node* newNode = new Node();
    newNode->value = another->value;
    newNode->prev = copyNode(another->prev);
    return newNode;
}

template<typename Type>
void Stack<Type>::push(const Type& value) noexcept
{
    Node* newElem = new Node;
    newElem->value = value;
    newElem->prev = mHead;
    mHead = newElem;
    mSize++;
}

template<typename Type>
void Stack<Type>::pop()
{
    if (!isEmpty())
    {
        Node* tmpPtr = mHead;
        mHead = mHead->prev;
        delete tmpPtr;
        mSize--;
    }
    else
    {
        throw std::runtime_error("Stack is empty. Could not delete the last element.");
    }
}

template<typename Type>
void Stack<Type>::clear()
{
    while (!isEmpty())
        pop();
}

template<typename Type>
Type Stack<Type>::top() const
{
    if (!isEmpty())
        return mHead->value;
    else
        throw std::runtime_error("Stack is empty. Could not give the last element.");
}

template<typename Type>
std::size_t Stack<Type>::getSize() const noexcept
{
    return mSize;
}

template<typename Type>
bool Stack<Type>::isEmpty() const noexcept
{
    return mSize == 0;
}

template<typename Type>
Stack<Type>::~Stack()
{
    clear();
}

int main()
{
    try
    {
        Stack<int> stack;
        const int ar[] = { 4, 6, 7, 2, 8, 8 };

        for (const auto& val : ar)
            stack.push(val);

        while (!stack.isEmpty())
        {
            std::cout << "Value: " << stack.top() << std::endl;
            stack.pop();
        }

        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error! Cause: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
