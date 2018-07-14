#include <iostream>

template <typename T>
class AutoPtr
{
public:
    explicit AutoPtr(T* element) : elem(element) {}
    AutoPtr(AutoPtr<T>& other);
    T operator * ();
    T* operator -> ();
    T* release();
    void reset(T* element);
    T* get();
    ~AutoPtr();
private:
    T* elem;
};

template <typename T>
AutoPtr<T>::AutoPtr(AutoPtr<T>& other)
{
    delete elem;
    elem = other.elem;
    other.elem = nullptr;
}

template <typename T>
T AutoPtr<T>::operator * ()
{
    return *elem;
}

template <typename T>
T* AutoPtr<T>::operator -> ()
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
    if (!elem)
    {
        delete elem;
    }
    elem = element;
}

template <typename T>
T* AutoPtr<T>::get()
{
    return elem;
}

template <typename T>
AutoPtr<T>::~AutoPtr()
{
    if (!elem)
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
