#include <iostream>

bool digitСhecker(int number) {
	if (number >= 0 && number <= 9999 || number >= 100000) {
		std::cout << "Incorrect length." << std::endl;
		return false;
	} else
		return true;
}

int main()
{
	int number;

	do {
		std::cout << "Input five-digit number: ";
		std::cin >> number;
		std::cout << number << std::endl;
	} while (!digitСhecker(number));

	std::cout << "[0]: " << number / 10000 % 10 << std::endl;
	std::cout << "[1]: " << number / 1000 % 10 << std::endl;
	std::cout << "[2]: " << number / 100 % 10 << std::endl;
	std::cout << "[3]: " << number / 10 % 10 << std::endl;
	std::cout << "[4]: " << number / 1 % 10 << std::endl;

	return 0;
}
