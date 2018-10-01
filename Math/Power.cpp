#include <iostream>

int slowPower(int value, size_t power) 
{
	int result = value;
	for (size_t i = 1; i < power; i++)
	{
		result *= value;
	}
	return result;
}

long fastPower(long value, size_t power) {
	long result = 1;
	while (power)//in C++, everything that is not 0 is considered true (and 0 is false) 
	{
		if (power&1)//fast way to know if number is odd 
		{
			result *= value;
		}
		value *= value;
		power >>=1;//fast way to divide by 2
	}
	return result;
}

int main()
{
	std::cout << "2^7 = " << slowPower(2, 7) << std::endl;
	std::cout << "2^10 = " << fastPower(2, 10) << std::endl;
    return EXIT_SUCCESS;
}
