#include <conio.h>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

void dump(int val, char c)
{
	std::cout << c << " <= [0";

	int next = 0x40000000, splitter = 4;
	for (int i = sizeof(int) * 8 - 1; i >= 0; --i, next /= 2) {
		if (i && !(i % splitter)) std::cout << " ";
		if (i && (val & next))
			std::cout << "1";
		else if (i)
			std::cout << "0";
	}

	std::cout << "]" << std::endl;
}

int main()
{
	int x, y, m, n, tmp;

	std::cout << "Input x: ";
	std::cin >> x;
	std::cout << "Input y: ";
	std::cin >> y;
	std::cout << "Input m: ";
	std::cin >> m;
	std::cout << "Input n: ";
	std::cin >> n;

	// Dump variables before transformation
	std::cout << "*** BEFORE ***" << std::endl;
	dump(x, 'x');
	dump(y, 'y');

	// Put 'm' high bits from 'y' to 'm' low bits from 'x'
	x >>= m;
	x <<= m;
	tmp = y;
	tmp >>= (sizeof(int) * 8 - m);
	x |= tmp;
	tmp = 0;

	// Inverse 'n' low bits from 'y'
	tmp = ~y;
	y >>= n;
	y <<= n;
	tmp <<= (sizeof(int) * 8 - n);
	tmp >>= (sizeof(int) * 8 - n);
	y |= tmp;

	// Dump variables after transformation
	std::cout << "*** AFTER ***" << std::endl;
	dump(x, 'x');
	dump(y, 'y');

	return 0;
}

