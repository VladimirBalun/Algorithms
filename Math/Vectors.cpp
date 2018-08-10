#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
int getVectorLength(const T& vector)
{
    int length = 0;
    for (const auto& elem : vector)
    {
        length += elem * elem;
    }
    return static_cast<int>(sqrt(length));
}

template <typename T>
void normalizeVector(T& vector)
{
    int length = getVectorLength(vector);
    for (auto& elem : vector)
    {
        elem /= length;
    }
}

template <typename T>
T addVectors(const T& vec1, const T& vec2)
{
    if (vec1.size() != vec2.size())
    {
        throw std::invalid_argument("Size vectors isn't equals.");
    }

    T newVector(vec1.size());
    for (size_t i = 0; i < vec1.size(); i++)
    {
        newVector[i] = vec1[i] + vec2[i];
    }
    return newVector;
}

template <typename T>
T subVectors(const T& vec1, const T& vec2)
{
    if (vec1.size() != vec2.size())
    {
        throw std::invalid_argument("Size vectors isn't equals.");
    }

    T newVector(vec1.size());
    for (size_t i = 0; i < vec1.size(); i++)
    {
        newVector[i] = vec1[i] - vec2[i];
    }
    return newVector;
}

template <typename T>
void mulVectorOnScalar(T &vector, int value)
{
    for (auto& elem : vector)
    {
        elem *= value;
    }
}

template <typename T>
auto scalarMulVectors(const T& vec1, const T& vec2)
{
    if (vec1.size() != vec2.size())
    {
        throw std::invalid_argument("Size vectors isn't equals.");
    }

    auto scalarMultiplication = 0;
    for (size_t i = 0; i < vec1.size(); i++)
    {
        scalarMultiplication += vec1[i] * vec2[i];
    }
    return scalarMultiplication;
}

int main()
{
    std::vector<int> vec1 = { 3, 2, 0 };
    std::vector<int> vec2 = { 1, 4, -7 };

    std::cout << "Length: " << getVectorLength(vec1) << std::endl;
    std::cout << "Scalar multiplication: " << scalarMulVectors(vec1, vec2) << std::endl;

    std::vector<int> vec3 = addVectors(vec1, vec2);
    std::vector<int> vec4 = subVectors(vec1, vec2);

    normalizeVector(vec1);
    mulVectorOnScalar(vec2, 5);

    return EXIT_SUCCESS;
}
