#include <iostream>

template<typename Type>
class AutoPtr
{
public:
    explicit AutoPtr(Type* pointer) noexcept : mPointer(pointer) {}
    explicit AutoPtr(AutoPtr& another) noexcept;
    AutoPtr& operator = (AutoPtr& another) noexcept;
    Type operator * () const noexcept;
    Type* operator -> () const noexcept;
    operator bool() const noexcept;
    Type* get() const noexcept;
    Type* release() noexcept;
    void reset(Type* pointer = nullptr) noexcept;
    ~AutoPtr();
private:
    Type* mPointer;
};

template<typename Type>
AutoPtr<Type>::AutoPtr(AutoPtr& another) noexcept
{
    mPointer = another.mPointer;
    another.mPointer = nullptr;
}

template<typename Type>
AutoPtr<Type>& AutoPtr<Type>::operator = (AutoPtr& another) noexcept
{
    if (this != &another) 
    {
        delete mPointer;
        mPointer = another.mPointer;
        another.mPointer = nullptr;
    }
    return *this;
}

template<typename Type>
Type AutoPtr<Type>::operator * () const noexcept
{
    return *mPointer;
}

template<typename Type>
Type* AutoPtr<Type>::operator -> () const noexcept
{
    return mPointer;
}

template<typename Type>
AutoPtr<Type>::operator bool() const noexcept
{
    return mPointer != nullptr;
}

template<typename Type>
Type* AutoPtr<Type>::get() const noexcept
{
    return mPointer;
}

template<typename Type>
Type* AutoPtr<Type>::release() noexcept
{
    Type* tmp = mPointer;
    mPointer = nullptr;
    return tmp;
}

template<typename Type>
void AutoPtr<Type>::reset(Type* pointer) noexcept
{
    delete mPointer;
    mPointer = pointer;
}

template<typename Type>
AutoPtr<Type>::~AutoPtr()
{
    delete mPointer;
}

int main()
{
    // Test structure for testing
    struct Vector2d
    {
        double x, y;
    };

    AutoPtr<Vector2d> ptr1(new Vector2d());
    AutoPtr<Vector2d> ptr2(ptr1);
    std::cout << "x: " << ptr2->x << " y: " << ptr2->y << std::endl;
    return EXIT_SUCCESS;
}
