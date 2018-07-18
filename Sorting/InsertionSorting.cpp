#include <iostream>
#include <vector>

template <typename Collection, typename Comparator>
void insertionSort(Collection& ar, size_t size, Comparator comparator)
{
    for (size_t i = 1; i < size; i++)
    {
        for (size_t j = i; j > 0 && comparator(ar[j], ar[j - 1]) ; j--)
        {
            std::swap(ar[j], ar[j - 1]);
        }
    }
}

int main()
{
    std::vector<int> vector = { 7, 2, 9, 1, 7, 2, 7, 2, 6, 0, 5, 6 };

    std::cout << "Not sorted array: ";
    for(const auto& val : vector)
    {
        std::cout << val << " ";
    }

    insertionSort(vector, vector.size(), [](int a, int b) { return a < b; });

    std::cout << std::endl << "Sorted array: ";
    for(const auto& val : vector)
    {
        std::cout << val << " ";
    }

    return EXIT_SUCCESS;
}
