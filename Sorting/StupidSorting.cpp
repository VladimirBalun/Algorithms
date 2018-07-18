#include <iostream>
#include <vector>

template <typename Collection, typename Comparator>
void stupidSort(Collection& ar, size_t size, Comparator comparator)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (comparator(ar[i + 1], ar[i]))
        {
            std::swap(ar[i], ar[i + 1]);
            i = -1;
        }
    }
}

int main()
{
    std::vector<int> vector = { 7, 9, 1, 5, 8, 1, 8, 3, 7, 3 };

    std::cout << "Not sorted array: ";
    for (const auto& val : vector)
    {
        std::cout << val << " ";
    }

    stupidSort(vector, vector.size(), [](int a, int b) { return a < b; });

    std::cout << std::endl << "Sorted array: ";
    for (const auto& val : vector)
    {
        std::cout << val << " ";
    }

    return EXIT_SUCCESS;
}
