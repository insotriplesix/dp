#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <omp.h>
#include <windows.h>

#define NCLIENTS	1000000U

#define IDWIDTH		8
#define AGEWIDTH	3
#define CASHWIDTH	8

typedef struct account {
	int id;
	int age;
	int gender;
	int cash;
} TACC;

typedef struct filter {
	int id_from, id_to;
	int age_from, age_to;
	int gender;
	int cash_from, cash_to;
} TFIL;

TACC accgen(int i);
int non_opt_search(TACC *a, TACC *fa, TFIL f, int flag);
int opt_search(TACC * __restrict a, TACC * __restrict fa, TFIL f, int flag);
void dump(TACC * __restrict a, int sz);
void gotoxy(int x, int y);
int getx();
int gety();

int main()
{
	srand((int)time(NULL));

	TACC *accounts = (TACC *)calloc(NCLIENTS, sizeof(TACC));

	if (accounts == NULL) {
		fprintf(stderr, "Allocation memory.");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < NCLIENTS; ++i)
		accounts[i] = accgen(i);

	int x, y;
	int choice = 0, flag = 0;
	TFIL filter;

	std::cout << "Select filters (input 1 or 0):" << std::endl;

	std::cout << " cash > ";
	std::cin >> choice;
	if (choice) {
		flag |= 0x1;
		std::cout << " range [";
		x = getx();
		y = gety();
		std::cin >> filter.cash_from;
		gotoxy(x + CASHWIDTH, y);
		std::cout << ", ";
		x = getx();
		y = gety();
		std::cin >> filter.cash_to;
		gotoxy(x + CASHWIDTH, y);
		std::cout << "]" << std::endl;
	}
	else {
		filter.cash_from = filter.cash_to = -1;
	}

	std::cout << " id > ";
	std::cin >> choice;
	if (choice) {
		flag |= 0x2;
		std::cout << " range [";
		x = getx();
		y = gety();
		std::cin >> filter.id_from;
		gotoxy(x + IDWIDTH, y);
		std::cout << ", ";
		x = getx();
		y = gety();
		std::cin >> filter.id_to;
		gotoxy(x + IDWIDTH, y);
		std::cout << "]" << std::endl;
	}
	else {
		filter.id_from = filter.id_to = -1;
	}

	std::cout << " age > ";
	std::cin >> choice;
	if (choice) {
		flag |= 0x4;
		std::cout << " range [";
		x = getx();
		y = gety();
		std::cin >> filter.age_from;
		gotoxy(x + AGEWIDTH, y);
		std::cout << ", ";
		x = getx();
		y = gety();
		std::cin >> filter.age_to;
		gotoxy(x + AGEWIDTH, y);
		std::cout << "]" << std::endl;
	}
	else {
		filter.age_from = filter.age_to = -1;
	}

	std::cout << " gender > ";
	std::cin >> choice;
	if (choice) {
		flag |= 0x8;
		std::cout << " male(1)/female(0): ";
		std::cin >> filter.gender;
	}
	else filter.gender = -1;

	TACC *filtered = (TACC *)calloc(NCLIENTS, sizeof(TACC));

	if (filtered == NULL) {
		fprintf(stderr, "Allocation memory.");
		exit(EXIT_FAILURE);
	}

	int size;

	auto start = std::chrono::steady_clock::now();
	size = non_opt_search(accounts, filtered, filter, flag);
	std::cout << "size: " << size << std::endl;
	auto end = std::chrono::steady_clock::now();
	auto elapsed1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "[Non-optimized search]" << std::endl << "Elapsed time: " << elapsed1.count() << " ms." << std::endl;

	start = std::chrono::steady_clock::now();
	size = opt_search(accounts, filtered, filter, flag);
	std::cout << "size: " << size << std::endl;
	end = std::chrono::steady_clock::now();
	auto elapsed2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "[Optimized search]" << std::endl << "Elapsed time: "<< elapsed2.count() << " ms." << std::endl;

	std::cout << std::endl << "Speedup: " << std::fixed << std::setprecision(3) << elapsed1 * 1.0f / elapsed2 << std::endl;

	/*
	std::cout << std::endl;
	std::cout << "*** ALL CLIENTS ***" << std::endl;
	dump(accounts, NCLIENTS);
	std::cout << std::endl;
	std::cout << "*** FILTERED ***" << std::endl;
	std::cout << "size: " << size << std::endl;
	if (flag) dump(filtered, size);
	else std::cout << " nothing to search ..." << std::endl;
	*/

	return 0;
}


TACC accgen(int i)
{
	TACC a;

	a.id = i;
	a.age = 18 + rand() % 82;
	a.gender = rand() % 2;
	a.cash = rand() % 1000000;

	return a;
}

int non_opt_search(TACC *a, TACC *fa, TFIL f, int flag)
{
	bool add = false;
	int sz = 0;

	for (int i = 0; i < NCLIENTS; ++i) {
		if (flag & 0x1) {
			if (a[i].cash >= f.cash_from && a[i].cash <= f.cash_to)
				add = true;	 
		}

		if (flag & 0x2) {
			if (a[i].id >= f.id_from && a[i].id <= f.id_to)
				add = true;
		}

		if (flag & 0x4) {
			if (a[i].age >= f.age_from && a[i].age <= f.age_to)
				add = true;
		}

		if (flag & 0x8) {
			if (a[i].gender == f.gender)
				add = true;
		}

		if (add) {
			fa[sz++] = a[i];
			add = false;
		}
	}

	return sz;
}

int opt_search(TACC * __restrict a, TACC * __restrict fa, TFIL f, int flag)
{
	int sz = 0;

	if (flag) {
		TACC *p = a;
		for (int i = 0; i < NCLIENTS; ++i, ++p) {
			if ((p->cash <= f.cash_to && p->cash >= f.cash_from) ||
				(p->id <= f.id_to && p->id >= f.id_from) ||
				(p->age <= f.age_to && p->age >= f.age_from) ||
				(p->gender == f.gender)) {
				fa[sz++] = a[i];
			}
		}
	}

	return sz;
}

void dump(TACC * __restrict a, int sz)
{
	std::cout << "========================" << std::endl;
	for (int i = 0; i < sz; ++i) {
		std::cout << " ID:		" << a[i].id << std::endl;
		std::cout << " AGE:		" << a[i].age << std::endl;
		std::cout << " GENDER:	";
		if (a[i].gender) std::cout << "MALE" << std::endl;
		else std::cout << "FEMALE" << std::endl;
		std::cout << " CASH:		" << a[i].cash << std::endl;
		std::cout << " ---------------------- " << std::endl;
	}
	std::cout << "========================" << std::endl;

}

void gotoxy(int x, int y)
{
	HANDLE hConsole;
	COORD cursorLoc;

	std::cout.flush();

	cursorLoc.X = x;
	cursorLoc.Y = y;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, cursorLoc);
}

int getx()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	return csbi.dwCursorPosition.X;
}

int gety()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	return csbi.dwCursorPosition.Y;
}
