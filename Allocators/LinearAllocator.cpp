#include <iostream>
#include <stdexcept>

class LinearAllocator
{
public:
    explicit LinearAllocator(std::size_t memorySize);
    explicit LinearAllocator(LinearAllocator&& another) noexcept;
    LinearAllocator& operator = (LinearAllocator&& another) noexcept;
    explicit LinearAllocator(const LinearAllocator& another) = delete;
    LinearAllocator& operator = (const LinearAllocator& another) = delete;
    void* allocate(std::size_t allocatedSize) noexcept;
    void deallocate() noexcept;
    ~LinearAllocator();
private:
    std::size_t mMemorySize = 0;
    std::size_t mMemoryOffset = 0;
    void* mBasePointer = nullptr;
};

LinearAllocator::LinearAllocator(std::size_t memorySize) : mMemorySize(memorySize)
{
    if (mMemorySize == 0)
        throw std::runtime_error("Could not allocate 0 byte of the memory.");

    mBasePointer = malloc(mMemorySize);
    if (!mBasePointer)
        throw std::runtime_error("Memory was not allocated for allocator.");
}

LinearAllocator::LinearAllocator(LinearAllocator&& another) noexcept
{
    mMemorySize = another.mMemorySize;
    mMemoryOffset = another.mMemoryOffset;
    mBasePointer = another.mBasePointer;
    another.mBasePointer = nullptr;
    another.deallocate();
}

LinearAllocator& LinearAllocator::operator = (LinearAllocator&& another) noexcept
{
    if (this != &another)
    {
        mMemorySize = another.mMemorySize;
        mMemoryOffset = another.mMemoryOffset;
        mBasePointer = another.mBasePointer;
        another.mBasePointer = nullptr;
        another.deallocate();
    }
    return *this;
}

void* LinearAllocator::allocate(std::size_t allocatedSize) noexcept
{
    if (mMemoryOffset + allocatedSize > mMemorySize)
        return nullptr; // Allocator is full

    const std::size_t allocatedAddress = reinterpret_cast<std::size_t>(mBasePointer) + mMemoryOffset;
    mMemoryOffset += allocatedSize;
    return reinterpret_cast<void*>(allocatedAddress);
}

void LinearAllocator::deallocate() noexcept
{
    mMemorySize = mMemoryOffset = 0;
}

LinearAllocator::~LinearAllocator()
{
    free(mBasePointer);
}

int main()
{
    // Test structure for checking allocator
    struct Vector4d
    {
        double x, y, z, w;
    };

    try
    {
        LinearAllocator allocator(sizeof(Vector4d) * 3);
        Vector4d* vector1 = static_cast<Vector4d*>(allocator.allocate(sizeof(Vector4d)));
        Vector4d* vector2 = static_cast<Vector4d*>(allocator.allocate(sizeof(Vector4d)));
        Vector4d* vector3 = static_cast<Vector4d*>(allocator.allocate(sizeof(Vector4d)));
        allocator.deallocate();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error! Cause: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
