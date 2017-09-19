#include <iostream>

int main()
{
	char ch;
	do {
		std::cout << "Input letter in a lower case: ";
		std::cin >> ch;
	} while (ch < 'a' || ch > 'z');

	std::cout << (char)(ch - 32) << std::endl;

	return 0;
}
