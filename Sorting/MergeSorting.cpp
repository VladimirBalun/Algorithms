#include <vector>
#include <iostream>

template<typename Collection, typename Comparator, typename = typename Collection::iterator>
void merge_sorting(Collection& collection, std::size_t begin, std::size_t end, Comparator comparator) noexcept 
{
    if (end - begin < 2)
        return;

    const std::size_t middle = (begin + end) / 2;
    merge_sorting(collection, begin, middle, comparator);
    merge_sorting(collection, middle, end, comparator);

    Collection buffer{};
    buffer.reserve(end - begin);
    std::size_t left = begin;
    std::size_t right = middle;
    while ( (left < middle) && (right < end) )
    {
        if (comparator(collection.at(left), collection.at(right)))
        {
            buffer.push_back(collection.at(left));
            left++;
        }
        else
        {
            buffer.push_back(collection.at(right));
            right++;
        }
    }

    while (left < middle) 
    {
        buffer.push_back(collection.at(left));
        left++;
    }

    while (right < end)
    {
        buffer.push_back(collection.at(right));
        right++;
    }

    std::copy(buffer.begin(), buffer.end(), collection.begin() + begin);
}

int main()
{
    std::vector<int> vector = { 7, 9, 1, 5, 8, 1, 8, 3, 7, 3 };

    std::cout << "Not sorted array: ";
    for (const auto& value : vector)
        std::cout << value << " ";

    merge_sorting(vector, 0, vector.size(), [](int a, int b) -> bool { return a < b; });

    std::cout << "\nSorted array: ";
    for (const auto& value : vector)
        std::cout << value << " ";

    return EXIT_SUCCESS;
}
