#include <iostream>

template <typename T>
class AutoPtr
{
public:
    explicit AutoPtr(T* element) : elem(element) {}
    AutoPtr(AutoPtr& other);
    AutoPtr& operator = (AutoPtr& other);
    T operator * () const;
    T* operator -> () const;
    T* release();
    void reset(T* element);
    T* get() const;
    ~AutoPtr();
private:
    T* elem;
};

template <typename T>
AutoPtr<T>::AutoPtr(AutoPtr& other)
{
    elem = other.elem;
    other.elem = nullptr;
}

template <typename T>
AutoPtr<T>& AutoPtr<T>::operator = (AutoPtr& other)
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
T AutoPtr<T>::operator * () const
{
    return *elem;
}

template <typename T>
T* AutoPtr<T>::operator -> () const
{
    return elem;
}

template <typename T>
T* AutoPtr<T>::release()
{
    T* tmpPtr = elem;
    elem = nullptr;
    return tmpPtr;
}

template <typename T>
void AutoPtr<T>::reset(T* element)
{
    if (elem)
    {
        delete elem;
    }
    elem = element;
}

template <typename T>
T* AutoPtr<T>::get() const
{
    return elem;
}

template <typename T>
AutoPtr<T>::~AutoPtr()
{
    if (elem)
    {
        delete elem;
    }
}

int main()
{
    std::string* str = new std::string("Hello world");
    AutoPtr<std::string> ptr1(str);
    AutoPtr<std::string> ptr2 = ptr1;
    std::cout << *ptr2 << std::endl;
    return EXIT_SUCCESS;
}