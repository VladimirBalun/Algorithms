#include <vector>
#include <limits>
#include <algorithm>

template<typename T>
T exchange_sub_recursive_function(std::vector<T>& intermediate_values, const std::vector<T>& coins, const T coins_amount) noexcept
{
    if (coins_amount < 0)
        return std::numeric_limits<T>::max() - 1;
    if (coins_amount == 0)
        return 0;
    if (intermediate_values.at(coins_amount) != 0)
        return intermediate_values.at(coins_amount);

    T min_count = std::numeric_limits<T>::max() - 1;
    for (const auto coin : coins)
        min_count = std::min(min_count, exchange_sub_recursive_function(intermediate_values, coins, coins_amount - coin) + 1);

    intermediate_values.at(coins_amount) = min_count;
    return min_count;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
T exchange_by_min_count_coins_recursive(const std::vector<T>& coins, const T coins_amount) noexcept
{
    std::vector<T> intermediate_values(coins_amount + 1, 0);
    return exchange_sub_recursive_function(intermediate_values, coins, coins_amount);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
T exchange_by_min_count_coins_non_recursive(const std::vector<T>& coins, const T coins_amount) noexcept
{
    std::vector<T> intermediate_values(coins_amount + 1, 0);
    for (typename std::vector<T>::size_type i = 1; i < intermediate_values.size(); ++i)
    {
        intermediate_values.at(i) = std::numeric_limits<T>::max() - 1;
        for (const auto coin : coins)
            if (intermediate_values.at(i) - coin >= 0)
                intermediate_values.at(i) = std::min(intermediate_values.at(i), intermediate_values.at(i - coin) + 1);
    }
    return intermediate_values.at(coins_amount);
}

int main()
{
    const std::vector<int> coins = { 1, 3, 4 };
    const int min_count_coins_recursive = exchange_by_min_count_coins_recursive(coins, 10);
    const int min_count_coins_non_recursive = exchange_by_min_count_coins_non_recursive(coins, 10);

    return EXIT_SUCCESS;
}
