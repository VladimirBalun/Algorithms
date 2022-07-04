#include <iostream>
#include <vector>

std::vector<int> generate_prime_numbers(int max_number)
{
	if (max_number <= 1)
		return std::vector<int>{};

	std::vector<int> result;
	std::vector<bool> sieve(max_number + 1, true);
	for (int i = 2; i * i <= max_number; ++i) {
		for (int j = i * i; j <= max_number; j += i) {
			sieve[j] = false;
		}
	}

	for (size_t i = 2u; i < sieve.size(); ++i) {
		if (sieve[i])
			result.push_back(i);
	}

	return result;
}

int main(int argc, char** argv)
{
	auto prime_numbers = generate_prime_numbers(40);
	for (auto number : prime_numbers) {
		std::cout << number << " ";
	}

	return EXIT_SUCCESS;
}