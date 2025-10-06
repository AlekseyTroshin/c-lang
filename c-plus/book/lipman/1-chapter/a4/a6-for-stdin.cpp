#include <iostream>

int main()
{
	int num;

	for ( int i = 0; i < 10; i++ ) {
		std::cin >> num;
		std::cout << num;

		if ( num == 100 ) 
		{
			break;
		}
	}

	std::cout << "End";


	return 0;
}