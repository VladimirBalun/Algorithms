#include <iostream>
#include <cmath>

template <typename T>
class BinaryHeap
{
public:
    explicit BinaryHeap() : size(0), array(new T[2]) {}
    explicit BinaryHeap(const BinaryHeap& other);
    explicit BinaryHeap(BinaryHeap&& other);
    BinaryHeap& operator = (const BinaryHeap& other);
    BinaryHeap& operator = (BinaryHeap&& other);

    void push(const T& element);
    void pop();
    void clear();

    T top() const;
    size_t getSize() const;
    size_t getDepth() const;
    bool isEmpty() const;

    ~BinaryHeap();
private:
    size_t indexLeftChild(size_t curIndex);
    size_t indexRightChild(size_t curIndex);
    size_t indexParent(size_t curIndex);
    void expandArray();
    void heapify(size_t index);
private:
    T* array;
    size_t size;
    size_t maxSize = 3;
};

template <typename T>
BinaryHeap<T>::BinaryHeap(const BinaryHeap& other)
{
    std::copy(other.array, &other.array[size], array);
    size = other.size;
}

template <typename T>
BinaryHeap<T>::BinaryHeap(BinaryHeap&& other)
{
    array = other.array;
    size = other.size;
    other.array = nullptr;
    other.size = 0;
}

template <typename T>
BinaryHeap<T>& BinaryHeap<T>::operator = (const BinaryHeap& other)
{
    std::copy(other.array, &other.array[size], array);
    size = other.size;
    return *this;
}

template <typename T>
BinaryHeap<T>& BinaryHeap<T>::operator = (BinaryHeap&& other)
{
    array = other.array;
    size = other.size;
    other.array = nullptr;
    other.size = 0;
    return *this;
}

template <typename T>
size_t BinaryHeap<T>::indexLeftChild(size_t curIndex)
{
    return curIndex * 2 + 1;
}

template <typename T>
size_t BinaryHeap<T>::indexRightChild(size_t curIndex)
{
    return curIndex * 2 + 2;
}

template <typename T>
size_t BinaryHeap<T>::indexParent(size_t curIndex)
{
    return curIndex == 0 ? 0 : (curIndex - 1) / 2;
}

template <typename T>
void BinaryHeap<T>::expandArray()
{
    maxSize = (maxSize * 2) - (maxSize / 3);
    T* newArray = new T[maxSize];
    std::copy(array, &array[size], newArray);
    delete[] array;
    array = newArray;
}

template <typename T>
void BinaryHeap<T>::heapify(size_t index)
{
    size_t leftChild;
    size_t rightChild;
    size_t largestChild;

    while(true)
    {
        leftChild = indexLeftChild(index);
        rightChild = indexRightChild(index);
        largestChild = index;

        if (array[leftChild] > array[largestChild] && leftChild < size)
        {
            largestChild = leftChild;
        }

        if (array[rightChild] > array[largestChild] && rightChild < size)
        {
            largestChild = rightChild;
        }

        if (largestChild == index)
        {
            break;
        }

        std::swap(array[index], array[largestChild]);
        index = largestChild;
    }
}

template <typename T>
void BinaryHeap<T>::push(const T& element)
{
    if (size == maxSize)
    {
        expandArray();
    }

    array[size] = element;
    size_t current = size;
    size_t parent = indexParent(current);
    size++;

    while (current > 0 && array[current] > array[parent])
    {
        std::swap(array[current], array[parent]);
        current = parent;
        parent = indexParent(current);
    }
}

template <typename T>
void BinaryHeap<T>::pop()
{
    if (isEmpty())
    {
        return;
    }

    std::swap(array[0], array[size - 1]);
    array[size - 1] = NULL;
    size--;

    heapify(0);
}

template <typename T>
void BinaryHeap<T>::clear()
{
    for (size_t i = 0; i < size; i++)
    {
        array[i] = NULL;
    }
    size = 0;
}

template <typename T>
T BinaryHeap<T>::top() const
{
    return array[0];
}

template <typename T>
size_t BinaryHeap<T>::getSize() const
{
    return size;
}

template <typename T>
size_t BinaryHeap<T>::getDepth() const
{
    return log2(size);
}

template <typename T>
bool BinaryHeap<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
BinaryHeap<T>::~BinaryHeap()
{
    if (array)
    {
        delete[] array;
    }
}

int main(int argc, char *argv[])
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

    std::cout << heap.getSize() << " " << heap.getDepth() << std::endl;

    return EXIT_SUCCESS;
}
