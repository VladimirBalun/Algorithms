#include <iostream>
#include <vector>

template <typename Collection, typename Comparator>
void bubbleSort(Collection& ar, size_t size, Comparator comparator)
{
    bool isSorting = false;
    for (size_t i = 0; i < size - 1; i++)
    {
        isSorting = true;
        for (size_t j = 0; j < size - 1; j++)
        {
            if (comparator(ar[j], ar[j + 1]))
            {
                std::swap(ar[j], ar[j + 1]);
                isSorting = false;
            }
        }
        if (isSorting)
        {
            return;
        }
    }
}

int main()
{
    std::vector<int> vector = {7, 9, 1, 5, 8, 1, 8, 3, 7, 3};

    std::cout << "Not sorted array: ";
    for(const auto& val : vector)
    {
        std::cout << val << " ";
    }

    bubbleSort(vector, vector.size(), [](int a, int b) { return a > b; });

    std::cout << std::endl << "Sorted array: ";
    for(const auto& val : vector)
    {
        std::cout << val << " ";
    }

    return EXIT_SUCCESS;
}
