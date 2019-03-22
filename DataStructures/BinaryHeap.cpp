#include <cmath>
#include <iostream>

#define INITIAL_COUNT_ELEMENTS 5

template<typename Type>
class BinaryHeap
{
public:
    explicit BinaryHeap() = default;
    explicit BinaryHeap(const BinaryHeap& another) noexcept;
    explicit BinaryHeap(BinaryHeap&& another) noexcept;
    BinaryHeap& operator = (const BinaryHeap& another) noexcept;
    BinaryHeap& operator = (BinaryHeap&& another) noexcept;
    void push(const Type& element) noexcept;
    void pop() noexcept;
    void clear() noexcept;
    Type top() const noexcept;
    constexpr std::size_t getSize() const noexcept;
    constexpr std::size_t getDepth() const noexcept;
    constexpr bool isEmpty() const noexcept;
    ~BinaryHeap();
private:
    std::size_t getIndexLeftChild(std::size_t curIndex) const noexcept;
    std::size_t getIndexRightChild(std::size_t curIndex) const noexcept;
    std::size_t getIndexParent(std::size_t curIndex) const noexcept;
    void expandArray(std::size_t size = 0) noexcept;
    void heapify(std::size_t index) noexcept;
private:
    std::size_t mSize = 0;
    std::size_t mMaxSize = INITIAL_COUNT_ELEMENTS;
    Type* mElements = new Type[INITIAL_COUNT_ELEMENTS];
};

template<typename Type>
BinaryHeap<Type>::BinaryHeap(const BinaryHeap& another) noexcept
{
    if (another.mMaxSize > mMaxSize)
        expandArray(another.mMaxSize);
    std::copy(another.mElements, another.mElements + another.mMaxSize, mElements);
    mSize = another.mSize;
}

template<typename Type>
BinaryHeap<Type>::BinaryHeap(BinaryHeap&& another) noexcept
    : mElements(another.mElements), mSize(another.mSize)
{
    another.mElements = nullptr;
    another.mSize = 0;
}

template<typename Type>
BinaryHeap<Type>& BinaryHeap<Type>::operator = (const BinaryHeap& another) noexcept
{
    if (this != &another)
    {
        if (another.mMaxSize > mMaxSize)
            expandArray(another.mMaxSize);
        std::copy(another.mElements, another.mElements + another.mMaxSize, mElements);
        mSize = another.mSize;
    }
    return *this;
}

template<typename Type>
BinaryHeap<Type>& BinaryHeap<Type>::operator = (BinaryHeap&& another) noexcept
{
    if (this != &another) 
    {
        mElements = another.mElements;
        mSize = another.mSize;
        another.mElements = nullptr;
        another.mSize = 0;
    }
    return *this;
}

template<typename Type>
size_t BinaryHeap<Type>::getIndexLeftChild(size_t curIndex) const noexcept
{
    return curIndex * 2 + 1;
}

template<typename Type>
size_t BinaryHeap<Type>::getIndexRightChild(size_t curIndex) const noexcept
{
    return curIndex * 2 + 2;
}

template<typename Type>
size_t BinaryHeap<Type>::getIndexParent(size_t curIndex) const noexcept
{
    return curIndex == 0 ? 0 : (curIndex - 1) / 2;
}

template<typename Type>
void BinaryHeap<Type>::expandArray(std::size_t size) noexcept
{
    if (size == 0)
        mMaxSize = (mMaxSize * 2) - (mMaxSize / 3);
    else
        mMaxSize = size;

    Type* newArray = new Type[mMaxSize];
    std::copy(mElements, mElements + mMaxSize, newArray);
    delete[] mElements;
    mElements = newArray;
}

template<typename Type>
void BinaryHeap<Type>::heapify(size_t index) noexcept
{
    std::size_t leftChild;
    std::size_t rightChild;
    std::size_t largestChild;

    while(true)
    {
        leftChild = getIndexLeftChild(index);
        rightChild = getIndexRightChild(index);
        largestChild = index;

        if (mElements[leftChild] > mElements[largestChild] && leftChild < mSize)
            largestChild = leftChild;

        if (mElements[rightChild] > mElements[largestChild] && rightChild < mSize)
            largestChild = rightChild;

        if (largestChild == index)
            break;

        std::swap(mElements[index], mElements[largestChild]);
        index = largestChild;
    }
}

template<typename Type>
void BinaryHeap<Type>::push(const Type& element) noexcept
{
    if (mSize == mMaxSize)
        expandArray();

    mElements[mSize] = element;
    std::size_t current = mSize;
    std::size_t parent = getIndexParent(current);
    mSize++;

    while (current > 0 && mElements[current] > mElements[parent])
    {
        std::swap(mElements[current], mElements[parent]);
        current = parent;
        parent = getIndexParent(current);
    }
}

template<typename Type>
void BinaryHeap<Type>::pop() noexcept
{
    if (isEmpty())
        return;

    std::swap(mElements[0], mElements[mSize - 1]);
    mElements[mSize - 1] = NULL;
    mSize--;

    heapify(0);
}

template<typename Type>
void BinaryHeap<Type>::clear() noexcept
{
    for (std::size_t i = 0; i < mSize; i++)
        mElements[i] = NULL;
    mSize = 0;
}

template<typename Type>
Type BinaryHeap<Type>::top() const noexcept
{
    return mElements[0];
}

template<typename Type>
constexpr std::size_t BinaryHeap<Type>::getSize() const noexcept
{
    return mSize;
}

template<typename Type>
constexpr std::size_t BinaryHeap<Type>::getDepth() const noexcept
{
    return static_cast<std::size_t>(round((log2(mSize)) + 0.5));
}

template<typename Type>
constexpr bool BinaryHeap<Type>::isEmpty() const noexcept
{
    return mSize == 0;
}

template<typename Type>
BinaryHeap<Type>::~BinaryHeap()
{
    delete[] mElements;
}

int main()
{
    BinaryHeap<int> heap;

    heap.push(1);
    heap.push(2);
    heap.push(3);
    heap.push(4);
    heap.push(5);
    heap.push(6);

    heap.pop();
    heap.pop();
    heap.pop();

    std::cout << "Heap size: " << heap.getSize() << std::endl;
    std::cout << "Heap depth: " << heap.getDepth() << std::endl;

    return EXIT_SUCCESS;
}
