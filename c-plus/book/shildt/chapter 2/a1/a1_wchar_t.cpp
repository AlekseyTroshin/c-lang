#include <iostream>
#include <filesystem>
#include <sstream>
#include <locale>

using namespace std;

int main()
{
	string str = "Привет";

	ostringstream test_str;
	test_str << str;
	
	cout << "one" << endl;
	cout << "Здоровье " + test_str.str() << endl;
	
	return 0;
}