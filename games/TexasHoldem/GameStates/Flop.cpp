#include "Flop.hpp"

void Flop::Render(std::shared_ptr<CLI> _ui)
{
	_ui->ClearScreen();
	_ui->ShowBoard(game_data);
	_ui->ShowPlayersInfo(game_data);

	std::cout << "Flop done!"
		<< std::endl << std::endl;

	Sleep(500);
}

void Flop::Update()
{
	auto players = game_data->GetPlayers();
	int bet = 0;

	for (size_t i = 0; i < players.size(); ++i) {
		do {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << players[i].GetNickName() << ", place your bet: ";
			std::cin >> bet;

			if (bet > players[i].GetCash()) {
				std::cout << "Not enough money." << std::endl;
			}
		} while (bet > players[i].GetCash());

		game_data->PlaceBet(i, bet);
	}

	game_data->SetBoardCards(1);
}
