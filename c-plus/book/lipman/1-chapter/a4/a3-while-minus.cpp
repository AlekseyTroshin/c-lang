#include <iostream>

int main()
{
	int sum = 0, a = 10;

	while ( a > 0 )
	{
		sum += a;
		a--;
	}

	std::cout << "summ " << sum << std::endl;

	return 0;
}