#include <vector>
#include <iostream>

std::size_t search_options_number(std::size_t position, std::vector<bool>& cols, std::vector<bool>& main_diagonals, std::vector<bool>& side_diagonals) noexcept
{
    if (position == cols.size()) 
    {
        return 1;
    }
    else 
    {
        std::size_t count_options = 0;
        for (std::size_t i = 0; i < cols.size(); i++)
        {
            if ( (!cols.at(i)) && (!side_diagonals.at(position + i)) && (!main_diagonals.at(i - position + cols.size() - 1)))
            {
                cols.at(i) = side_diagonals.at(position + i) = main_diagonals.at(i - position + cols.size() - 1) = true;
                count_options += search_options_number(position + 1, cols, main_diagonals, side_diagonals);
                cols.at(i) = side_diagonals.at(position + i) = main_diagonals.at(i - position + cols.size() - 1) = false;
            }
        }
        return count_options;
    }
}

int main()
{
    const std::size_t count_queens = 8u;
    std::vector<bool> cols(count_queens);
    std::vector<bool> main_diagonals(count_queens * 2u);
    std::vector<bool> side_diagonals(count_queens * 2u);
    std::cout << "Options number: " << search_options_number(0u, cols, main_diagonals, side_diagonals) << std::endl;
    return EXIT_SUCCESS;
}
