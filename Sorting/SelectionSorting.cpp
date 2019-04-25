#include <vector>
#include <iostream>

template<typename Collection, typename Comparator, typename = typename Collection::iterator>
void selection_sorting(Collection& collection, Comparator comparator) noexcept
{
    for (Collection::size_type i = 0; i < collection.size() - 1; i++) 
    {
        Collection::size_type key_element_index = i;
        for (Collection::size_type j = i + 1; j < collection.size(); j++)
            if (comparator(collection[j], collection[key_element_index]))
                key_element_index = j;
    
        if (key_element_index != i)
            std::swap(collection[i], collection[key_element_index]);
    }
}

int main()
{
    std::vector<int> vector = { 4, 7, 1, 5, 2, 9, 4, 7, 2, 9, 4 };

    std::cout << "Not sorted array: ";
    for (const auto& value : vector)
        std::cout << value << " ";

    selection_sorting(vector, [](int a, int b) { return a > b; });

    std::cout << "\nSorted array: ";
    for (const auto& value : vector)
        std::cout << value << " ";

    return EXIT_SUCCESS;
}
