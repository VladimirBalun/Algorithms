#include <vector>
#include <iostream>

// Only for ordered sets without doubles
template<typename Type>
std::vector<Type> difference(const std::vector<Type>& firsSet, const std::vector<Type>& secondSet)
{
    std::size_t firstIndex = 0;
    std::size_t secondIndex = 0;
    std::vector<Type> resultDifference{};

    while ( (firstIndex < firsSet.size()) && (secondIndex < secondSet.size()) )
    {
        if (firsSet.at(firstIndex) == secondSet.at(secondIndex))
        {
            firstIndex++;
            secondIndex++;
        }
        else
        {
            if (firsSet.at(firstIndex) < secondSet.at(secondIndex))
            {
                resultDifference.push_back(firsSet.at(firstIndex));
                firstIndex++;
            }
            else
            {
                secondIndex++;
            }
        }
    }

    while (firstIndex < firsSet.size())
    {
        resultDifference.push_back(firsSet.at(firstIndex));
        firstIndex++;
    }

    return resultDifference;
}

int main()
{
    const std::vector<int> firstSet{ 1, 2, 3, 5, 8 };
    const std::vector<int> secondSet{ 3, 6, 8, 12, 24, 47 };
    const std::vector<int> resultDifference(difference(firstSet, secondSet));
    for (const auto& element : resultDifference)
        std::cout << element << "  ";
    return EXIT_SUCCESS;
}
