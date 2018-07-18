#include <iostream>
#include <vector>

template <typename Collection>
void quickSort(Collection& ar, size_t left, size_t right)
{
    size_t l = left;
    size_t r = right;
    auto key = ar[(left + right) / 2];

    while (l <= r)
    {
        while (ar[l] < key)
        {
            l++;
        }
        while (ar[r] > key)
        {
            r--;
        }
        if (l <= r)
        {
            std::swap(ar[l++], ar[r--]);
        }
    }

    if (l < right)
    {
        quickSort(ar, l, right);
    }
    if (r > left)
    {
        quickSort(ar, left, r);
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

    quickSort(vector, 0, vector.size());

    std::cout << std::endl << "Sorted array: ";
    for(const auto& val : vector)
    {
        std::cout << val << " ";
    }

    return EXIT_SUCCESS;
}
