#include <iostream>

int main()
{
	int a = 50, b = 100;
	int sum = 0;

	while (a < b)
	{
		sum += a;
		++a;
	}

	std::cout << "summ " << sum << std::endl;

	return 0;
}