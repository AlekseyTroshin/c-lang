#include <iostream>
#include "Sales_item.h"

int main()
{
	int count = 0;

	Sales_item item1, item2, item3, item4;

	std::cin >> item1 >> item2 >> item3 >> item4;

	std::cout << item1 << "\n" 
		<< item2 << "\n" 
		<< item3 << "\n" 
		<< item4 << std::endl;

	return 0;
}