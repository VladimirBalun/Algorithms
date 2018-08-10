#include <iostream>
#include <vector>
#include <cmath>

typedef std::vector<std::vector<int>> IntMatrix;
typedef std::vector<int> IntRow;

bool isEqualSizeMatrices(const IntMatrix& matrix1, const IntMatrix& matrix2)
{
    if (matrix1.size() != matrix2.size())
    {
        return false;
    }

    for (size_t i = 0; i < matrix1.size(); i++)
    {
        if (matrix1[i].size() != matrix2[i].size())
        {
            return false;
        }
    }

    return true;
}

void mulMatrixOnScalar(IntMatrix& matrix, int value)
{
    for (auto& row : matrix)
    {
        for (auto& elem : row)
        {
            elem *= value;
        }
    }
}

IntMatrix mulMatrices(const IntMatrix& matrix1, const IntMatrix& matrix2)
{
    size_t countRowsMatrix1 = matrix1.size();
    size_t countColsMatrix2 = matrix2.front().size();
    if (countRowsMatrix1 != countColsMatrix2)
    {
        throw std::invalid_argument("Count rows of the first matrix isn't equal count cols of trhe second matrix...");
    }

    IntMatrix newMatrix;
    for (size_t i = 0; i < countRowsMatrix1; i++)
    {
        newMatrix.push_back(IntRow(countColsMatrix2));
    }

    for (size_t row = 0; row < countRowsMatrix1; row++)
    {
        for (size_t col = 0; col < countColsMatrix2; col++)
        {
            for (size_t i = 0; i < matrix2.size(); i++)
            {
                newMatrix[row][col] += matrix1[row][i] * matrix2[i][col];
            }
        }
    }

    return std::move(newMatrix);
}

void addMatrices(IntMatrix& matrix1, const IntMatrix& matrix2)
{
    if (!isEqualSizeMatrices(matrix1, matrix2))
    {
        throw std::invalid_argument("Size of matrices isn't equal...");
    }

    for (size_t i = 0; i < matrix1.size(); i++)
    {
        for (size_t j = 0; j < matrix1[i].size(); j++)
        {
            matrix1[i][j] += matrix2[i][j];
        }
    }
}

void subMatrices(IntMatrix& matrix1, const IntMatrix& matrix2)
{
    if (!isEqualSizeMatrices(matrix1, matrix2))
    {
        throw std::invalid_argument("Size of matrices isn't equal...");
    }

    for (size_t i = 0; i < matrix1.size(); i++)
    {
        for (size_t j = 0; j < matrix1[i].size(); j++)
        {
            matrix1[i][j] -= matrix2[i][j];
        }
    }
}

int main()
{

    IntMatrix matrix1 = { std::vector<int> { 4, 5, 7},
                          std::vector<int> { 6, 9, 0},
                          std::vector<int> { 1, 0, 1} };
    IntMatrix matrix2 = { std::vector<int> { 8, 9, 0},
                          std::vector<int> { 2, 0, 3},
                          std::vector<int> { 3, 0, 5} };

    addMatrices(matrix1, matrix2);
    subMatrices(matrix1, matrix2);
    mulMatrixOnScalar(matrix1, 10);
    IntMatrix matrix3 = mulMatrices(matrix1, matrix2);
    
    return EXIT_SUCCESS;
}
