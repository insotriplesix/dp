#include "CLI.hpp"
#include "Menu.hpp"

void Menu::Render(std::shared_ptr<CLI> _ui)
{
	_ui->ClearScreen();
	_ui->ShowLogo();
	_ui->ShowMenu();
}

void Menu::Update()
{
	bool invalid_input = true;
	int choice;

	do {
		std::cin >> choice;

		switch (choice) {
		case 1:
			invalid_input = false;
			break;
		case 2:
			std::cout << std::endl << "Some helpful information." <<
				std::endl << std::endl;
			break;
		case 3:
			std::cout << std::endl << "Made by 5aboteur, 2017." <<
				std::endl << std::endl;
			break;
		case 0:
			std::cout << std::endl << "Goodbye!" << std::endl;;
			Sleep(1000); // need to change this in the future
			exit(EXIT_SUCCESS);
		default:
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << std::endl << "Invalid input value." <<
				std::endl << std::endl;
			break;
		}

		std::cout << " > ";

	} while (invalid_input);
}
