#include "Blinds.hpp"

void Blinds::Render(std::shared_ptr<CLI> _ui)
{
	_ui->ClearScreen();
	_ui->ShowBoard(game_data);
	_ui->ShowPlayersInfo(game_data);

	std::cout << "Blinds done!"
		<< std::endl << std::endl;

	Sleep(1000);
}

void Blinds::Update()
{
	game_data->PlaceBlinds();
	game_data->Handout();
}
