#include <iostream>

int main() 
{

	int a = 0, b = 0;

	std::cout << ++a << std::endl;
	std::cout << b++ << std::endl;

	int sum = 0, val = 1;
	while ( val <= 10 )
	{
		std::cout << val << std::endl;
		sum += val;
		++val;
	}

	std::cout << "Sum of 1 to 10 inclusive is "
		<< sum << std::endl;

	return 0;
}