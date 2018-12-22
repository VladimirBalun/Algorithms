#include <iostream>
#include <cstdlib>
#include <limits>  

class LinearAllocator
{
public:
    explicit LinearAllocator(std::size_t memorySize, std::size_t memoryAlignment);
    void* allocate(std::size_t allocatedSize);
    void free();
    ~LinearAllocator();
private:
    std::size_t size = 0;
    std::size_t offset = 0;
    std::size_t alignment = 0;
    void* memoryPointer = nullptr;
};

LinearAllocator::LinearAllocator(std::size_t memorySize, std::size_t memoryAlignment)
    : size(memorySize), alignment(memoryAlignment)
{
    if (size == 0)
        throw std::runtime_error("Can not allocate 0 byte of the memory.");

    if ( (alignment == 0) && (size % alignment == 0) )
        throw std::runtime_error("Incorrect alignment for memory allocating.");

    memoryPointer = malloc(size);
    if (!memoryPointer)
        throw std::runtime_error("Memory was not allocated");
}

void* LinearAllocator::allocate(std::size_t allocatedSize)
{
    if (offset + alignment > size)
        return nullptr;

    std::size_t allocatedPointer = reinterpret_cast<std::size_t>(memoryPointer) + offset;
    offset += alignment;
    return reinterpret_cast<void*>(allocatedPointer);
}

void LinearAllocator::free()
{
    size = offset = 0;
}

LinearAllocator::~LinearAllocator()
{
    if (memoryPointer)
        ::free(memoryPointer);
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
        LinearAllocator allocator(sizeof(Vector4d) * 100, sizeof(Vector4d));
        for (std::int32_t i = 0; i < 100; i++)
        {
            Vector4d* vector = static_cast<Vector4d*>(allocator.allocate(sizeof(Vector4d)));
            vector->x = vector->y = vector->z = vector->w = i;
            std::cout << " Address: " << vector 
                      << " x: " << vector->x
                      << " y: " << vector->y
                      << " z: " << vector->z
                      << " w: " << vector->w << std::endl;
        }
        allocator.free();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error! Cause: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
