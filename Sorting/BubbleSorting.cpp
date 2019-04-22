#include <vector>
#include <iostream>

template<typename Collection, typename Comparator, typename = typename Collection::size_type>
void bubbleSort(Collection& collection, Comparator comparator) noexcept
{
    bool wasSorted = true;
    for (Collection::size_type i = 0; i < collection.size(); i++) 
    {
        for (Collection::size_type j = 0; j < collection.size() - 1; j++) 
        {
            if (comparator(collection[j], collection[j + 1])) 
            {
                std::swap(collection[j], collection[j + 1]);
                wasSorted = false;
            }
        }

        if (wasSorted)
        {
            return;
        }
    }
}

int main()
{
    std::vector<int> vector = { 7, 9, 1, 5, 8, 1, 8, 3, 7, 3 };

    std::cout << "Not sorted array: ";
    for (const auto& val : vector)
        std::cout << val << " ";

    bubbleSort(vector, [] (int a, int b) -> bool { return a > b; });

    std::cout << std::endl << "Sorted array: ";
    for (const auto& val : vector)
        std::cout << val << " ";

    return EXIT_SUCCESS;
}
