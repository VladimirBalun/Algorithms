#include <iostream>

template <typename T>
class UniquePtr
{
public:
    explicit UniquePtr(T* element) : elem(element) {}
    UniquePtr(UniquePtr&& other);
    UniquePtr& operator = (UniquePtr&& other);
    T operator * () const;
    T* operator -> () const;
    T* release();
    void reset(T* element);
    T* get() const;
    ~UniquePtr();
private:
    T* elem;
};

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other)
{
    elem = other.elem;
    other.elem = nullptr;
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator = (UniquePtr&& other)
{
    if (elem)
    {
        delete elem;
    }
    elem = other.elem;
    other.elem = nullptr;
    return *this;
}

template <typename T>
T UniquePtr<T>::operator * () const
{
    return *elem;
}

template <typename T>
T* UniquePtr<T>::operator -> () const
{
    return elem;
}

template <typename T>
T* UniquePtr<T>::release()
{
    T* tmpPtr = elem;
    elem = nullptr;
    return tmpPtr;
}

template <typename T>
void UniquePtr<T>::reset(T* element)
{
    if (elem)
    {
        delete elem;
    }
    elem = element;
}

template <typename T>
T* UniquePtr<T>::get() const
{
    return elem;
}

template <typename T>
UniquePtr<T>::~UniquePtr()
{
    if (elem)
    {
        delete elem;
    }
}

int main()
{
    std::string* str = new std::string("Hello world");
    UniquePtr<std::string> ptr1(str);
    UniquePtr<std::string> ptr2 = std::move(ptr1);
    std::cout << *ptr2 << std::endl;
    return EXIT_SUCCESS;
}
