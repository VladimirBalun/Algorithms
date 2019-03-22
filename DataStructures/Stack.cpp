#include <iostream>
#include <stdexcept>

template<typename Type>
class Stack
{
public:
    using value_type = Type;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
public:
    explicit Stack() = default;
    explicit Stack(const Stack& another) noexcept
        : m_head(copy_node(another.m_head)), m_size(another.m_size) {}
    explicit Stack(Stack&& another) noexcept;
    Stack& operator=(const Stack& another) noexcept;
    Stack& operator=(Stack&& another) noexcept;
    void swap(Stack& another) noexcept;
    template<typename... Args>
    void emplace(Args&&... args) noexcept;
    void push(const Type& value) noexcept;
    void push(Type&& value) noexcept;
    void pop();
    void clear() noexcept;
    reference top();
    const_reference top() const;
    constexpr size_type size() const noexcept;
    constexpr bool empty() const noexcept;
    ~Stack();
private:
    struct Node
    {
        Type value = Type();
        Node* prev = nullptr;
    };
    Node* copy_node(Node* another) const noexcept;
private:
    Node* m_head = nullptr;
    size_type m_size = 0;
};

template<typename Type>
Stack<Type>::Stack(Stack&& another) noexcept
    : m_head(another.m_head), m_size(another.m_size)
{
    another.m_size = 0;
    another.m_head = nullptr;
}

template<typename Type>
Stack<Type>& Stack<Type>::operator=(const Stack& another) noexcept
{
    if (this != &another)
    {
        if (!empty())
            clear();
        m_head = copy_node(another.m_head);
        m_size = another.m_size;
    }
    return *this;
}

template<typename Type>
Stack<Type>& Stack<Type>::operator=(Stack&& another) noexcept
{
    if (this != &another)
    {
        if (!empty())
            clear();
        m_head = another.m_head;
        m_size = another.m_size;
        another.m_head = nullptr;
        another.m_size = 0;
    }
    return *this;
}

template<typename Type>
auto Stack<Type>::copy_node(Node* another) const noexcept -> Node*
{
    if (!another)
        return nullptr;

    return new Node{ another->value, copy_node(another->next) };
}

template<typename Type>
void Stack<Type>::swap(Stack& another) noexcept
{
    if (this != &another)
    {
        Node* another_head = another.m_head;
        std::size_t another_size = another.m_size;
        another.m_head = m_head;
        another.m_size = m_size;
        m_head = another_head;
        m_size = another_size;
    }
}

template<typename Type>
template<typename... Args>
void Stack<Type>::emplace(Args&&... args) noexcept
{
    m_head = new Node{ { std::forward<Args>(args)... }, m_head };
    m_size++;
}

template<typename Type>
void Stack<Type>::push(const Type& value) noexcept
{
    m_head = new Node{ value, m_head };
    m_size++;
}

template<typename Type>
void Stack<Type>::push(Type&& value) noexcept
{
    m_head = new Node{ value, m_head };
    m_size++;
}

template<typename Type>
void Stack<Type>::pop()
{
    if (!empty())
    {
        Node* temp = m_head;
        m_head = m_head->prev;
        delete temp;
        m_size--;
    }
    else
    {
        throw std::runtime_error("Stack is empty. Could not delete the last element.");
    }
}

template<typename Type>
void Stack<Type>::clear() noexcept
{
    Node* iterator = m_head;
    while (iterator)
    {
        Node* temp = iterator;
        iterator = iterator->prev;
        delete temp;
    }

    m_size = 0;
    m_head = nullptr;
}

template<typename Type>
typename Stack<Type>::reference Stack<Type>::top()
{
    if (!empty())
        return m_head->value;
    else
        throw std::runtime_error("Stack is empty. Could not give the last element.");
}

template<typename Type>
typename Stack<Type>::const_reference Stack<Type>::top() const
{
    if (!empty())
        return m_head->value;
    else
        throw std::runtime_error("Stack is empty. Could not give the last element.");
}

template<typename Type>
constexpr typename Stack<Type>::size_type Stack<Type>::size() const noexcept
{
    return m_size;
}

template<typename Type>
constexpr bool Stack<Type>::empty() const noexcept
{
    return m_size == 0;
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
        for (const auto& val : { 4, 6, 7, 2, 8, 8 })
            stack.push(val);

        while (!stack.empty())
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
