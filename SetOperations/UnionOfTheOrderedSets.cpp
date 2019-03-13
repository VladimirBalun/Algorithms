#include <vector>
#include <iostream>

// Only for ordered sets without doubles
template<typename Type>
std::vector<Type> setsUnion(const std::vector<Type>& firsSet, const std::vector<Type>& secondSet) 
{
    std::size_t firstIndex = 0;
    std::size_t secondIndex = 0;
    std::vector<Type> resultUnion{};

    while ( (firstIndex < firsSet.size()) && (secondIndex < secondSet.size()) )
    {
        if (firsSet.at(firstIndex) == secondSet.at(secondIndex)) 
        {
            resultUnion.push_back(firsSet.at(firstIndex));
            firstIndex++;
            secondIndex++;
        }
        else if (firsSet.at(firstIndex) < secondSet.at(secondIndex)) 
        {
            resultUnion.push_back(firsSet.at(firstIndex));
            firstIndex++;
        }
        else 
        {
            resultUnion.push_back(secondSet.at(secondIndex));
            secondIndex++;
        }
    }

    while (firstIndex < firsSet.size())
    {
        resultUnion.push_back(firsSet.at(firstIndex));
        firstIndex++;
    }

    while (secondIndex < secondSet.size())
    {
        resultUnion.push_back(secondSet.at(secondIndex));
        secondIndex++;
    }

    return resultUnion;
}

int main()
{
    const std::vector<int> firstSet{ 1, 2, 3, 5, 8 };
    const std::vector<int> secondSet{ 3, 6, 8, 12, 24, 47 };
    const std::vector<int> resultUnion(setsUnion(firstSet, secondSet));
    for (const auto& element : resultUnion)
        std::cout << element << "  ";
    return EXIT_SUCCESS;
}
