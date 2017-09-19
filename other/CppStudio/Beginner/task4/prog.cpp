#include <iostream>

int main()
{
	double number;

	std::cout << "Input number of meters: ";
	std::cin >> number;

	std::cout << number << " m = " << number / 1000 << " km." << std::endl;

	return 0;
}
