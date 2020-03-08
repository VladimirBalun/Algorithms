#include <vector>
#include <iostream>

// $ - start position
// * - target position

// $ 0 0 0
// 0 0 0 0
// 0 0 * 0
// 0 0 0 0

struct Position
{
    size_t x = 0u;
    size_t y = 0u;
};

size_t find_path(const Position& end_position, const size_t field_size)
{
    std::vector<std::vector<size_t>> field(field_size);
    for (size_t i = 0u; i < field_size; ++i)
    {
        field.at(i).resize(field_size);
        field[i][0] = 1u;
        field[0][i] = 1u;
    }
    
    for (size_t i = 1u; i < field_size; ++i)
    {
        for (size_t j = 1u; j < field_size; ++j)
        {
            const size_t res_x = i - 1;
            const size_t res_y = j - 1;
            field[i][j] = field[i][res_y] + field[res_x][j];
            if ( (end_position.x == i) && (end_position.y == j) )
            {
                return field[i][j];
            }
        }
    }
    
    return 0u;
}


int main(int argc, const char * argv[])
{
    const size_t field_size = 4u;
    const Position end_position{ 3, 2 };
    const size_t result = find_path(end_position, field_size);
    
    std::cout << "Result: " << result << "\n";
    
    return EXIT_SUCCESS;
}

