#include <chrono>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <thread>
#include <windows.h>
#include "MMSystem.h"

#define DELAY	 1.2
#define DURATION 140

/* Colors */
#define _G 10
#define _R 12
#define _W 15

void gotoxy(int x, int y);
void printCross(int left_x, int left_y, int up_x, int up_y,
	int right_x, int right_y, int down_x, int down_y);

int main()
{
	srand((unsigned)time(NULL));

	/* Window size */
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left + 600, r.top + 300, 180, 200, true);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	/* Change the screen buffer size for hide scrollbars */
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	GetConsoleScreenBufferInfo(hConsole, &SBInfo);
	SBInfo.dwSize.X = SBInfo.dwMaximumWindowSize.X;
	SBInfo.dwSize.Y = SBInfo.dwMaximumWindowSize.Y;
	SetConsoleScreenBufferSize(hConsole, SBInfo.dwSize);
	HWND scrb = GetConsoleWindow();
	ShowScrollBar(scrb, SB_BOTH, FALSE);

	/* Set cursor invisible */
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &info);

	/* Change font parameters */
	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(font);
	font.nFont = 0;
	font.dwFontSize.X = 20;
	font.dwFontSize.Y = 28;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	std::wcscpy(font.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hConsole, false, &font);

	/* Play music */
	PlaySound(TEXT("slutts.wav"), NULL, SND_ASYNC | SND_LOOP);

	/* Change text color */
	SetConsoleTextAttribute(hConsole, _W);

	gotoxy(1, 1);
	std::cout << "PREPARE UR FINGAZ";

	/* Preparatory stage */
	auto start = std::chrono::steady_clock::now();
	while (1) {
		auto end = std::chrono::steady_clock::now();
		auto dif = std::chrono::duration_cast<std::chrono::seconds>(end - start);
		if (dif.count() == 0) {
			gotoxy(9, 5);
			std::cout << "3";
		}
		else if (dif.count() == 1) {
			gotoxy(9, 5);
			std::cout << "2";
		}
		else if (dif.count() == 2) {
			gotoxy(9, 5);
			std::cout << "1";
		}
		else if (dif.count() == 3) {
			gotoxy(8, 5);
			std::cout << "GO!";
		}
		if (dif.count() > 3) break;
	}

	system("cls");

	printCross(7, 5, 9, 3, 11, 5, 9, 7);

	int attempts = 5, score = 0;

	/* Main routine */
	while (1) {
		SetConsoleTextAttribute(hConsole, _W);

		auto finish = std::chrono::steady_clock::now();
		auto dif = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

		/* Time is over */
		if (dif.count() > DURATION) break;

		printCross(7, 5, 9, 3, 11, 5, 9, 7);
		gotoxy(9, 5);
		char r = (char)(65 + rand() % 25);	// Generate random character

		std::cout << r << std::endl;

		gotoxy(9, 5);

		auto start = std::chrono::steady_clock::now();

		/* Buttons press handling */
		while (1) {
			if (_kbhit()) {
				char c = _getch();
				if (c == r || c == r + 32) {	// r + 32 for CapsLock
					++score;
					SetConsoleTextAttribute(hConsole, _G);
					printCross(7, 5, 9, 3, 11, 5, 9, 7);
					std::this_thread::sleep_for(std::chrono::milliseconds(75));
				}
				else {
					--attempts;
					SetConsoleTextAttribute(hConsole, _R);
					printCross(7, 5, 9, 3, 11, 5, 9, 7);
					std::this_thread::sleep_for(std::chrono::milliseconds(75));
				}
				break;
			}
			auto end = std::chrono::steady_clock::now();
			auto dif = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			gotoxy(4, 1);
			std::cout << "score: " << score;

			/* You`re slow */
			if (dif.count() / 1000.0 > DELAY) {
				--attempts;
				SetConsoleTextAttribute(hConsole, _R);
				printCross(7, 5, 9, 3, 11, 5, 9, 7);
				std::this_thread::sleep_for(std::chrono::milliseconds(75));
				break;
			}
		}

		/* Game over */
		if (attempts <= 0) {
			gotoxy(5, 10);
			std::cout << "NEBLYADI!" << std::endl << std::endl << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
			return 0;
		}
	}

	/* That was ez ain`t it? */
	gotoxy(6, 8);
	SetConsoleTextAttribute(hConsole, _G);
	std::cout << "BLYADI!" << std::endl;
	SetConsoleTextAttribute(hConsole, _W);

	std::this_thread::sleep_for(std::chrono::seconds(5));

	return 0;
}

void printCross(int left_x, int left_y, int up_x, int up_y,
	int right_x, int right_y, int down_x, int down_y)
{
	gotoxy(left_x, left_y);
	std::cout << ">";
	gotoxy(up_x, up_y);
	std::cout << "v";
	gotoxy(right_x, right_y);
	std::cout << "<";
	gotoxy(down_x, down_y);
	std::cout << "^";
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
