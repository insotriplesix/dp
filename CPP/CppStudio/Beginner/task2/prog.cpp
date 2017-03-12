#include <iostream>

int equation(int a, int b, int f) {
	return (a + b - f / a) + f * a * a - (a + b);
}

int main()
{
	int a, b, f;

	std::cout << "Input a: ";
	std::cin >> a;

	std::cout << "Input b: ";
	std::cin >> b;

	std::cout << "Input f: ";
	std::cin >> f;

	std::cout << "x = " << equation(a, b, f) << std::endl;

	return 0;
}
