#include <vector>
#include <iostream>

std::size_t fibonacci_non_recursive(std::size_t number) noexcept
{
    std::vector<std::size_t> numbers(number, 0u);
    numbers.at(0) = 1u;
    numbers.at(1) = 1u;

    for (std::size_t i = 2u; i < numbers.size(); i++)
        numbers.at(i) = numbers.at(i - 1u) + numbers.at(i - 2u);
    
    return numbers.back();
}

std::size_t fibonacci_sub_function(std::vector<std::size_t>& numbers, std::size_t number) noexcept
{
    if (numbers.at(number) != 0u)
        return numbers.at(number);
    else if (number == 0)
        return 0u;
    else if (number == 1)
        return 1u;
    else
        return numbers.at(number) = fibonacci_sub_function(numbers, number - 1) + fibonacci_sub_function(numbers, number - 2);
}

std::size_t fibonacci_recursive(std::size_t number) noexcept 
{
    std::vector<std::size_t> numbers(number + 1, 0u);
    return fibonacci_sub_function(numbers, number);
}

int main()
{
    std::size_t number_recursive = fibonacci_recursive(5u);
    std::size_t number_non_recursive = fibonacci_non_recursive(5u);

    return EXIT_SUCCESS;
}
