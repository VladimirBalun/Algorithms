#include <iostream>
#include <iterator>
#include <cmath>
#include <set>

// slow algorithm O(N)
std::set<size_t> findFactors1(size_t number) 
{
	std::set<size_t> factors;
	for (size_t i = 2; i < number; i++)
	{
		while (number % i == 0) 
		{
			factors.insert(i);
			number /= i;
		}
	}
	if (number > 1) 
	{
		factors.insert(number);
	}
	return factors;
}

// fast algorithm O(Sqrt(n))
std::set<size_t> findFactors2(size_t number) 
{
	std::set<size_t> factors;
	while (number % 2 == 0)
	{
		factors.insert(2);
		number /= 2;
	}
	size_t maxFactor = sqrt(number);
	for (size_t i = 3; i <= number; i += 2)
	{
		while (number % i == 0)
		{
			factors.insert(i);
			number /= i;
			maxFactor = sqrt(number);
		}
	}
	if (number > 1)
	{
		factors.insert(number);
	}
	return factors;
}

int main()
{
	std::set<size_t> factors1 = findFactors1(50);
	std::cout << "Factors for 250 = ";
	std::copy(factors1.begin(), factors1.end(), std::ostream_iterator<size_t>(std::cout, " "));
	std::set<size_t> factors2 = findFactors2(21);
	std::cout << std::endl << "Factors for 21 = ";
	std::copy(factors2.begin(), factors2.end(), std::ostream_iterator<size_t>(std::cout, " "));
	return EXIT_SUCCESS;
}