#include <iostream>
#include <vector>

template <typename Collection, typename Comparator>
void shellSort(Collection& ar, size_t size, Comparator comparator)
{
    for (int step = size / 2; step > 0; step /= 2)
    {
        for (int i = step; i < size; i++)
        {
            for (int j = i; j > 0 && comparator(ar[j], ar[j - step]); j -= step)
            {
                std::swap(ar[j], ar[j - step]);
            }
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

    shellSort(vector, vector.size(), [](int a, int b) { return a < b; });

    std::cout << std::endl << "Sorted array: ";
    for(const auto& val : vector)
    {
        std::cout << val << " ";
    }

    return EXIT_SUCCESS;
}
