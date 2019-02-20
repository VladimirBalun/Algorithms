#include <cstdint>
#include <iostream>

template<typename Type>
class SharedPtr
{
public:
    explicit SharedPtr(Type* pointer) noexcept
        : mPointer(pointer), mReferencesCount(new std::uint16_t(1)) {}
    explicit SharedPtr(const SharedPtr& another) noexcept;
    SharedPtr& operator = (const SharedPtr& another) noexcept;
    Type operator * () const noexcept;
    Type* operator -> () const noexcept;
    operator bool() const noexcept;
    Type* get() const noexcept;
    bool isUnique() const noexcept;
    std::uint16_t getReferencesCount() const noexcept;
    void reset(Type* pointer = nullptr) noexcept;
    ~SharedPtr();
private:
    Type* mPointer;
    std::uint16_t* mReferencesCount;
};

template<typename Type>
SharedPtr<Type>::SharedPtr(const SharedPtr& another) noexcept
{
    mPointer = another.mPointer;
    mReferencesCount = another.mReferencesCount;
    (*mReferencesCount)++;
}

template<typename Type>
SharedPtr<Type>& SharedPtr<Type>::operator = (const SharedPtr& another) noexcept
{
    if (this != &another)
    {
        (*mReferencesCount)--;
        if (*mReferencesCount == 0)
            delete mPointer;
        mPointer = another.mPointer;
        (*mReferencesCount)++;
    }
    return *this;
}

template<typename Type>
Type SharedPtr<Type>::operator * () const noexcept
{
    return *mPointer;
}

template<typename Type>
Type* SharedPtr<Type>::operator -> () const noexcept
{
    return mPointer;
}

template<typename Type>
SharedPtr<Type>::operator bool() const noexcept
{
    return mPointer != nullptr;
}

template<typename Type>
Type* SharedPtr<Type>::get() const noexcept
{
    return mPointer;
}

template<typename Type>
bool SharedPtr<Type>::isUnique() const noexcept
{
    return *mReferencesCount == 1;
}

template<typename Type>
std::uint16_t SharedPtr<Type>::getReferencesCount() const noexcept
{
    return *mReferencesCount;
}

template<typename Type>
void SharedPtr<Type>::reset(Type* pointer) noexcept
{
    (*mReferencesCount)--;
    if (*mReferencesCount == 0)
    {
        delete mPointer;
        delete mReferencesCount;
    }  

    if (mPointer) 
    {
        mPointer = pointer;
        mReferencesCount = new std::uint16_t(1);
    }
}

template<typename Type>
SharedPtr<Type>::~SharedPtr()
{
    (*mReferencesCount)--;
    if (*mReferencesCount == 0) 
    {
        delete mPointer;
        delete mReferencesCount;
    }
}

int main()
{
    // Test structure for testing
    struct Vector2d
    {
        double x, y;
    };

    SharedPtr<Vector2d> ptr1(new Vector2d());
    SharedPtr<Vector2d> ptr2(ptr1);
    std::cout << "x: " << ptr2->x << " y: " << ptr2->y << std::endl;
    return EXIT_SUCCESS;
}
