#include <conio.h>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

int FLG = 0;

void setFlags(char c)
{
	if (c >= 'a' && c <= 'z' && !(FLG & 0x1))
		FLG |= 0x1;
	else if (c >= 'A' && c <= 'Z' && !(FLG & 0x2))
		FLG |= 0x2;
	else if (c >= '0' && c <= '9' && !(FLG & 0x4))
		FLG |= 0x4;
}

int main()
{
	const char RET = 13;	// enter key
	char c;

	std::string pass, charset;

	/* Init password */
	std::cout << "Enter password: ";
	while ((c = _getch()) != RET) {
		setFlags(c);
		pass += c;
		std::cout << "*";
	}
	
	std::cout << std::endl << std::endl;

	/* Init charset */
	if (FLG & 0x1) charset += "qwertyuiopasdfghjklzxcvbnm";
	if (FLG & 0x2) charset += "QWERTYUIOPASDFGHJKLZXCVBNM";
	if (FLG & 0x4) charset += "0123456789";

	/* Bruteforce info */
	std::cout << " [LENGTH]: " << pass.size() << std::endl;
	std::cout << " [CHARSET]: " << charset << std::endl;
	std::cout << " [SIZE]: " << charset.size() << std::endl;
	std::cout << " [POSSIBILITIES]: " << (uint64_t)std::pow(charset.size(), pass.size())
		<< std::endl;

	std::cout << std::endl << "Bruteforcing . . ." << std::endl << std::endl;

	double start = clock() / 1000.0;

	int passlen = pass.size();
	int charsetlen = charset.size();

	int *idx = new int[passlen];
	memset(idx, 0, sizeof(int) * passlen);

	std::string result;
	result.resize(passlen);

	/* Bruteforce routine*/
	while (1) {

		// Set indices
		for (int i = passlen - 1; i >= 0; --i) {
			if (i != 0) {
				if (idx[i] == charsetlen) {
					idx[i] = 0;
					idx[i - 1]++;
				}
			}
		}

		// Copy iteration result into output string
		for (int i = 0; i < passlen; ++i) result[i] = charset[idx[i]];

		if (result == pass) break;

		idx[passlen - 1]++;
	}

	double end = clock() / 1000.0;

	std::cout << " > " << result << " <" << std::endl;

	std::cout << std::endl << "Elapsed time: " << std::setprecision(3)
		<< end - start << " seconds." << std::endl;

	return 0;
}

