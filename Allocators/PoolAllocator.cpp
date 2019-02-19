#include <iostream>

class PoolAllocator
{

public:
    explicit PoolAllocator(std::size_t memorySize, std::size_t chunkSize);
    explicit PoolAllocator(PoolAllocator&& another) noexcept;
    PoolAllocator& operator = (PoolAllocator&& another) noexcept;
    explicit PoolAllocator(const PoolAllocator& another) = delete;
    PoolAllocator& operator = (const PoolAllocator& another) = delete;
    void* allocate(std::size_t chunkSize);
    void deallocate(void* pointer) noexcept;
    ~PoolAllocator();
private:
    std::size_t mTotalSize = 0;
    std::size_t mChunkSize = 0;
    std::size_t mMemoryUsed = 0;
    void* mBasePointer = nullptr;
    // Stack linked list for free chunks
    struct Chunk { Chunk* next; };
    Chunk *mChunksHead = nullptr;
};

PoolAllocator::PoolAllocator(std::size_t memorySize, std::size_t chunkSize)
    : mTotalSize(memorySize), mChunkSize(chunkSize)
{
    if (mTotalSize == 0 || chunkSize == 0)
        throw std::runtime_error("Could not allocate 0 byte of the memory.");

    mBasePointer = malloc(mTotalSize);
    if (!mBasePointer)
        throw std::runtime_error("Memory was not allocated for allocator.");

    for (std::size_t i = 0; i < memorySize / chunkSize; i++)
    {
        const std::size_t chunkAddress = reinterpret_cast<std::size_t>(mBasePointer) + i * mChunkSize;
        Chunk* newFreeChunk = reinterpret_cast<Chunk*>(chunkAddress);
        newFreeChunk->next = mChunksHead;
        mChunksHead = newFreeChunk;
    }
}

PoolAllocator::PoolAllocator(PoolAllocator&& another) noexcept
{
    mTotalSize = another.mTotalSize;
    mChunkSize = another.mChunkSize;
    mMemoryUsed = another.mMemoryUsed;
    mBasePointer = another.mBasePointer;
    another.mBasePointer = nullptr;
    another.mMemoryUsed = another.mChunkSize = another.mTotalSize = 0;
}

PoolAllocator& PoolAllocator::operator = (PoolAllocator&& another) noexcept
{
    if (this != &another)
    {
        mTotalSize = another.mTotalSize;
        mChunkSize = another.mChunkSize;
        mMemoryUsed = another.mMemoryUsed;
        mBasePointer = another.mBasePointer;
        another.mBasePointer = nullptr;
        another.mMemoryUsed = another.mChunkSize = another.mTotalSize = 0;
    }
    return *this;
}

void* PoolAllocator::allocate(std::size_t chunkSize)
{
    if (mChunkSize != chunkSize)
        throw std::invalid_argument("Incorrect chuck size for allocation");

    if (mMemoryUsed + mChunkSize > mTotalSize)
        return nullptr; // Allocator is full

    mMemoryUsed += mChunkSize;
    Chunk* freeChunk = mChunksHead;
    mChunksHead = mChunksHead->next;
    return reinterpret_cast<void*>(freeChunk);
}

void PoolAllocator::deallocate(void* pointer) noexcept
{
    if (mMemoryUsed == 0)
        return; // Allocator is empty

    mMemoryUsed -= mChunkSize;
    Chunk* newFreeChunk = reinterpret_cast<Chunk*>(pointer);
    newFreeChunk->next = mChunksHead;
    mChunksHead = newFreeChunk;
}

PoolAllocator::~PoolAllocator()
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
        PoolAllocator allocator(sizeof(Vector4d) * 3, sizeof(Vector4d));
        Vector4d* vector1 = static_cast<Vector4d*>(allocator.allocate(sizeof(Vector4d)));
        Vector4d* vector2 = static_cast<Vector4d*>(allocator.allocate(sizeof(Vector4d)));
        Vector4d* vector3 = static_cast<Vector4d*>(allocator.allocate(sizeof(Vector4d)));
        allocator.deallocate(vector2);
        allocator.deallocate(vector3);
        allocator.deallocate(vector1);
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error! Cause: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
