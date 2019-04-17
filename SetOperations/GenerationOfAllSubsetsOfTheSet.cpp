#include <vector>
#include <string>
#include <iterator>
#include <iostream>

void generate_subsets(const std::vector<int>& source_set, std::vector<int>& subset, std::size_t position)
{
    if (position == source_set.size()) 
    {
        std::copy(subset.begin(), subset.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        return;
    }
    else 
    {
        subset.push_back(source_set.at(position));
        generate_subsets(source_set, subset, position + 1);
        subset.pop_back();
        generate_subsets(source_set, subset, position + 1);
    }
}

int main() 
{
    std::vector<int> subset{};
    std::vector<int> source_set = { 1, 2, 3 };
    generate_subsets(source_set, subset, 0);
    return EXIT_SUCCESS;
}
