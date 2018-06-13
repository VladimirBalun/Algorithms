#include <iostream>

int gcdByMod(int&& num1, int&& num2)
{
	while (num1 && num2 != 0)
	{
		if (num1 > num2) 
		{
			num1 %= num2;
		}
		else 
		{
			num2 %= num1;
		}
	}
	return (num1 + num2);
}

int gcdBySub(int&& num1, int&& num2) 
{
	while (num1 != num2)
	{
		if (num1 > num2) 
		{
			num1 -= num2;
		}
		else 
		{
			num2 -= num1;
		}
	}
	return num1;
}

int main()
{
	std::cout << "GCD of 50 and 130 = " << gcdByMod(std::abs(50), std::abs(130)) << std::endl;
	std::cout << "GCD of 990 and 420 = " << gcdBySub(std::abs(990), std::abs(420)) << std::endl;
    return EXIT_SUCCESS;
}