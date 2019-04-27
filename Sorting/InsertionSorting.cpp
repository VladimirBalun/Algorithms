#include <vector>
#include <iostream>

template<typename Collection, typename Comparator, typename = typename Collection::size_type>
void insertion_sorting(Collection& collection, Comparator comparator) noexcept
{
    for (typename Collection::size_type i = 1; i < collection.size(); i++)
        for (typename Collection::size_type j = i; (j > 0) && (comparator(collection[j], collection[j - 1])); j--)
            std::swap(collection[j], collection[j - 1]);
}

int main()
{
    std::vector<int> vector = { 7, 2, 9, 1, 7, 2, 7, 2, 6, 0, 5, 6 };

    std::cout << "Not sorted array: ";
    for(const auto& value : vector)
        std::cout << value << " ";

    insertion_sorting(vector, [](int a, int b) { return a < b; });

    std::cout << "\nSorted array: ";
    for(const auto& value : vector)
        std::cout << value << " ";

    return EXIT_SUCCESS;
}
