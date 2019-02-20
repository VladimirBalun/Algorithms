#include <iostream>

template<typename Type>
class UniquePtr
{
public:
    explicit UniquePtr(Type* pointer) noexcept : mPointer(pointer) {}
    explicit UniquePtr(const UniquePtr& another) = delete;
    UniquePtr& operator = (const UniquePtr& another) = delete;
    explicit UniquePtr(UniquePtr&& another) noexcept;
    UniquePtr& operator = (UniquePtr&& another) noexcept;
    Type operator * () const noexcept;
    Type* operator -> () const noexcept;
    operator bool() const noexcept;
    Type* get() const noexcept;
    Type* release() noexcept;
    void reset(Type* pointer = nullptr) noexcept;
    ~UniquePtr();
private:
    Type* mPointer;
};

template<typename Type>
UniquePtr<Type>::UniquePtr(UniquePtr&& another) noexcept
{
    mPointer = another.mPointer;
    another.mPointer = nullptr;
}

template<typename Type>
UniquePtr<Type>& UniquePtr<Type>::operator = (UniquePtr&& another) noexcept
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
Type UniquePtr<Type>::operator * () const noexcept
{
    return *mPointer;
}

template<typename Type>
Type* UniquePtr<Type>::operator -> () const noexcept
{
    return mPointer;
}

template<typename Type>
UniquePtr<Type>::operator bool() const noexcept
{
    return mPointer != nullptr;
}

template<typename Type>
Type* UniquePtr<Type>::get() const noexcept
{
    return mPointer;
}

template<typename Type>
Type* UniquePtr<Type>::release() noexcept
{
    Type* tmp = mPointer;
    mPointer = nullptr;
    return tmp;
}

template<typename Type>
void UniquePtr<Type>::reset(Type* pointer) noexcept
{
    delete mPointer;
    mPointer = pointer;
}

template<typename Type>
UniquePtr<Type>::~UniquePtr()
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

    UniquePtr<Vector2d> ptr1(new Vector2d());
    UniquePtr<Vector2d> ptr2(std::move(ptr1));
    std::cout << "x: " << ptr2->x << " y: " << ptr2->y << std::endl;
    return EXIT_SUCCESS;
}
