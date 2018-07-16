##include <iostream>
#include <vector>

template <typename Collection, typename Comparator>
void selectionSort(Collection& ar, size_t size, Comparator comparator)
{
    size_t key;
    for (size_t i = 0; i < size - 1; i++)
    {
        key = i;
        for (size_t j = i; j < size; j++)
        {
           if (comparator(ar[key], ar[j]))
           {
               key = j;
           }
        }

        if (key != i)
        {
            std::swap(ar[i], ar[key]);
        }
    }
}

int main()
{
    std::vector<int> vector = { 4, 7, 1, 5, 2, 9, 4, 7, 2, 9, 4 };

    std::cout << "Not sorted array: ";
    for (const auto& val : vector)
    {
        std::cout << val << " ";
    }

    selectionSort(vector, vector.size(), [](int a, int b) { return a > b; });

    std::cout << std::endl << "Sorted array: ";
    for (const auto& val : vector)
    {
        std::cout << val << " ";
    }

    return EXIT_SUCCESS;
}
