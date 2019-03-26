#include <vector>
#include <iostream>

// Only for ordered sets without doubles
template<typename Type>
std::vector<Type> symmetricDifference(const std::vector<Type>& firsSet, const std::vector<Type>& secondSet)
{
    std::size_t firstIndex = 0;
    std::size_t secondIndex = 0;
    std::vector<Type> resultSymmetricDifference{};

    while ( (firstIndex < firsSet.size()) && (secondIndex < secondSet.size()) )
    {
        if (firsSet.at(firstIndex) < secondSet.at(secondIndex)) 
        {
            resultSymmetricDifference.push_back(firsSet.at(firstIndex));
            firstIndex++;
        }
        else if (firsSet.at(firstIndex) > secondSet.at(secondIndex))
        {
            resultSymmetricDifference.push_back(secondSet.at(secondIndex));
            secondIndex++;
        }
        else 
        {
            firstIndex++;
            secondIndex++;
        }
    }

    while (firstIndex < firsSet.size())
    {
        resultSymmetricDifference.push_back(firsSet.at(firstIndex));
        firstIndex++;
    }

    while (secondIndex < secondSet.size())
    {
        resultSymmetricDifference.push_back(secondSet.at(secondIndex));
        secondIndex++;
    }

    return resultSymmetricDifference;
}

int main()
{
    const std::vector<int> firstSet{ 1, 2, 3, 5, 8 };
    const std::vector<int> secondSet{ 3, 6, 8, 12, 24, 47 };
    const std::vector<int> resultUnion(symmetricDifference(firstSet, secondSet));
    for (const auto& element : resultUnion)
        std::cout << element << "  ";
    return EXIT_SUCCESS;
}
