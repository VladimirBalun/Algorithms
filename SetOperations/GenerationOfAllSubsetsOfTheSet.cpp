#include <vector>
#include <string>
#include <iostream>

void setGeneration(const std::vector<int>& set, std::size_t position, std::string&& output) 
{
    if (position == set.size()) 
    {
        std::cout << output << '\n';
        return;
    }

    setGeneration(set, position + 1, std::move(output));
    setGeneration(set, position + 1, output + std::to_string(set.at(position)) + ' ') ;
}

int main() 
{
    std::vector<int> set = { 1, 2, 3, 4 };
    setGeneration(set, 0, "");
    return EXIT_SUCCESS;
}