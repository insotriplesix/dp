#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

/* Leet alphabet. */
const std::map<char, std::string> alphabet =
{
	{ 'a', "4" },{ 'b', "8" },{ 'c', "(" },
	{ 'd', "[)" },{ 'e', "3" },{ 'f', "|=" },
	{ 'g', "6" },{ 'h', "|-|" },{ 'i', "!" },
	{ 'j', "]" },{ 'k', "|<" },{ 'l', "1" },
	{ 'm', "|Y|" },{ 'n', "/\\/" },{ 'o', "0" },
	{ 'p', "|>" },{ 'q', "0," },{ 'r', "|2" },
	{ 's', "5" },{ 't', "7" },{ 'u', "[_]" },
	{ 'v', "\\/" },{ 'w', "\\v/" },{ 'x', "}{" },
	{ 'y', "`/" },{ 'z', "2" }
};

/* Takes a string of text and leetilize every symbol from A(a) to Z(z). */
std::string leetilize(std::string buf)
{
	std::string lbuf;
	auto nil = alphabet.end();

	/* Use length() - 1 cuz of EOF. */
	for (size_t i = 0; i < buf.length() - 1; ++i) {
		auto item = alphabet.find(buf[i]);
		if (item != nil)
			lbuf += item->second;
		else
			lbuf += buf[i];
	}

	return lbuf;
}

/* Prints main menu. */
void menu()
{
	std::cout << '\n';
	std::cout << "*** Leetilizer v1.0 ***\n";
	std::cout << " 1. leet\n";
	std::cout << " 2. deleet\n";
	std::cout << " 3. quit\n";
	std::cout << "***********************\n";
	std::cout << " > ";
}

int main(int argc, char **argv)
{
	while (0x1) {
		menu();

		std::string filename;
		std::ifstream fin;
		std::ofstream fout;

		std::string buf;
		std::string lbuf;

		char choice;

		std::cin >> choice;

		switch (choice) {
		case '1':
			std::cout << "\nInput filename: ";
			std::cin >> filename;

			/* Open your file. */
			fin.open(filename, std::ios::in);

			if (fin.is_open()) {
				/* Get all text from it. */
				while (!fin.eof())
					buf += fin.get();

				/* Transform the string to lowercase characters. */
				std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);

				/* Leetilized it. */
				std::cout << "Leetilizing . . .\n";
				lbuf = leetilize(buf);

				/* Open the output file. */
				fout.open("leetilized_" + filename, std::ios::out);

				if (fout.is_open()) {
					/* Drop the leetilized text to that file. */
					fout << lbuf;

					/* ??? PROFIT */
					std::cout << "Complete.\n";
				}
				else {
					std::cout << "Error opening file '" << "leetilized_" + filename << "'.\n";
				}
			}
			else {
				std::cout << "Error opening file '" << filename << "'.\n";
			}

			fin.close();
			fout.close();

			break;
		case '2':
			std::cout << "\nUnavailable in this version.\n";
			break;
		case '3':
			exit(EXIT_SUCCESS);
		default:
			std::cout << "\nUnrecognized value. Try another one.\n";
		}
	}

	return 0;
}
