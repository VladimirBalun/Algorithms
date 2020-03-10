#include <vector>
#include <iostream>

void print_reverse_diagonals(const std::vector<std::vector<int>>& matrix)
{
    const size_t matrix_size = matrix.size();
    for (size_t i = 0u; i < matrix_size; ++i)
    {
        ssize_t k = i;
        size_t j = 0u;
        for (; (k >= 0) && (j < matrix_size); --k, ++j)
        {
            std::cout << matrix[k][j] << " ";
        }
        std::cout << "\n";
    }
    
    for (size_t j = 1u; j < matrix_size; ++j)
    {
        ssize_t k = j;
        size_t i = matrix_size - 1;
        for (; (i >= 0) && (k < matrix_size); --i, ++k)
        {
            std::cout << matrix[i][k] << " ";
        }
        std::cout << "\n";
    }
}

// 2
// 1 4
// 9 0 5
// 9 8 3 1
// 7 2 2
// 8 4
// 6

int main()
{
    const std::vector<std::vector<int>> matrix = {
        { 2, 4, 5, 1 },
        { 1, 0, 3, 2 },
        { 9, 8, 2, 4 },
        { 9, 7, 8, 6 }
    };
    
    print_reverse_diagonals(matrix);
    return EXIT_FAILURE;
}
