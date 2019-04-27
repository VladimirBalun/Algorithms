#include <vector>
#include <iostream>

template<typename Collection, typename Comparator, typename = typename Collection::size_type>
void bubble_sorting(Collection& collection, Comparator comparator) noexcept
{
    bool was_sorted = true;
    for (typename Collection::size_type i = 0; i < collection.size(); i++)
    {
        for (typename Collection::size_type j = 0; j < collection.size() - 1; j++)
        {
            if (comparator(collection[j], collection[j + 1])) 
            {
                std::swap(collection[j], collection[j + 1]);
                was_sorted = false;
            }
        }

        if (was_sorted)
            return;
    }
}

int main()
{
    std::vector<int> vector = { 7, 9, 1, 5, 8, 1, 8, 3, 7, 3 };

    std::cout << "Not sorted array: ";
    for (const auto& value : vector)
        std::cout << value << " ";

    bubble_sorting(vector, [] (int a, int b) -> bool { return a > b; });

    std::cout << "\nSorted array: ";
    for (const auto& value : vector)
        std::cout << value << " ";

    return EXIT_SUCCESS;
}
