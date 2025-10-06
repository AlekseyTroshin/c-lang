#include <iostream>

int main()
{
	int a, b;

	std::cin >> a >> b;

	while ( a < b - 1 ) {
		a++;
		std::cout << a << std::endl;
	}

	return 0;
}