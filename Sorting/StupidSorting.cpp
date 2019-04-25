#include <vector>
#include <iostream>

template <typename Collection, typename Comparator, typename = typename Collection::iterator>
void stupid_sorting(Collection& collection, Comparator comparator) noexcept
{
    for (int i = 0; i < static_cast<int>(collection.size() - 1); ++i)
    {
        if (comparator(collection[i], collection[i + 1]))
        {
            std::swap(collection[i], collection[i + 1]);
            i = -1;
        }
    }
}

int main()
{
    std::vector<int> vector = { 7, 9, 1, 5, 8, 1, 8, 3, 7, 3 };

    std::cout << "Not sorted array: ";
    for (const auto& value : vector)
        std::cout << value << " ";

    stupid_sorting(vector, [](int a, int b) { return a < b; });

    std::cout << "\nSorted array: ";
    for (const auto& value : vector)
        std::cout << value << " ";

    return EXIT_SUCCESS;
}
