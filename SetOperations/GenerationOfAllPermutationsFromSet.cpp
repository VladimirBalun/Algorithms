#include <vector>
#include <string>
#include <iterator> 
#include <iostream>

void generate_permutations(const std::vector<int>& source_set, std::vector<int>& permutations, std::vector<bool>& chosen_elements)
{
    if (source_set.size() == permutations.size())
    {
        std::copy(permutations.begin(), permutations.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        return;
    }
    else 
    {
        for (std::size_t i = 0; i < source_set.size(); i++)
        {
            if (!chosen_elements.at(i))
            {
                chosen_elements.at(i) = true;
                permutations.push_back(source_set.at(i));
                generate_permutations(source_set, permutations, chosen_elements);
                chosen_elements.at(i) = false;
                permutations.pop_back();
            }
        }
    }
}

int main()
{
    std::vector<int> permutations{};
    std::vector<int> source_set = { 1, 2, 3 };
    std::vector<bool> chosen_elements(source_set.size());
    generate_permutations(source_set, permutations, chosen_elements);
    return EXIT_SUCCESS;
}
