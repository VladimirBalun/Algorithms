#include <memory>
#include <iostream>
#include <stdexcept>

namespace details
{

    template<typename T>
    class StackImpl
    {
    protected:
        StackImpl(size_t size = 0u);
        ~StackImpl();
        StackImpl(const StackImpl& other) = delete;
        StackImpl& operator = (const StackImpl& other) = delete;
        void swap(StackImpl& other) noexcept;
    protected:
        T*     m_data;
        size_t m_size;
        size_t m_used;
    };

    template<typename T>
    StackImpl<T>::StackImpl(size_t size)
        : m_data(static_cast<T*>( (size == 0) ? (nullptr) : (operator new(sizeof(T) * size) ))),
          m_size(size), m_used(0u)
    {
    }

    template<typename T>
    StackImpl<T>::~StackImpl()
    {
        std::destroy(m_data, m_data + m_size);
        operator delete(m_data);
    }

    template<typename T>
    void StackImpl<T>::swap(StackImpl& other) noexcept
    {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
        std::swap(m_used, other.m_used);
    }

}

template<typename T>
class Stack : public details::StackImpl<T>
{
    using super = details::StackImpl<T>;
public:
    Stack(size_t size = 0u);
    Stack(const Stack& other);
    Stack& operator = (Stack other);
    constexpr size_t size() const noexcept;
    constexpr bool empty() const noexcept;
    T& top();
    void push(const T& value);
    void pop();
};

template<typename T>
Stack<T>::Stack(size_t size)
    : details::StackImpl<T>(size)
{
    super::m_used = 0;
}

template<typename T>
Stack<T>::Stack(const Stack& other)
    : details::StackImpl<T>(other.m_used)
{
    while (super::m_used < other.m_used)
    {
        new (super::m_data + super::m_used) T(other.m_data[super::m_used]);
        ++super::m_used;
    }
}

template<typename T>
Stack<T>& Stack<T>::operator = (Stack other)
{
    swap(other);
    return *this;
}

template<typename T>
constexpr size_t Stack<T>::size() const noexcept
{
    return super::m_used;
}

template<typename T>
constexpr bool Stack<T>::empty() const noexcept
{
    return super::m_used == 0u;
}

template<typename T>
T& Stack<T>::top()
{
    if (empty())
    {
        throw std::logic_error("Stack is empty.");
    }
    else
    {
        return super::m_data[super::m_used - 1];
    }
}

template<typename T>
void Stack<T>::push(const T& value)
{
    if (super::m_used == super::m_size)
    {
        Stack temp(super::m_size * 2 + 1);
        while (temp.size() < super::m_used)
        {
            temp.push(super::m_data[temp.size()]);
        }
        temp.push(value);
        super::swap(temp);
    }
    else
    {
        new (super::m_data + super::m_used) T(value);
        ++super::m_used;
    }
}

template<typename T>
void Stack<T>::pop()
{
    if (empty())
    {
        throw std::logic_error("Stack is empty.");
    }
    else
    {
        --super::m_used;
        T* pointer = super::m_data + super::m_used;
        pointer->~T();
    }
}

int main()
{
    try
    {
        Stack<int> stack{};
        int data[] = { 7, 6, 5, 4, 3, 2, 1 };
        
        for (int value : data)
        {
            stack.push(value);
        }
        
        while (!stack.empty())
        {
            stack.top();
            stack.pop();
        }

        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        return EXIT_FAILURE;
    }
}
