#include "EndRound.hpp"

void EndRound::Render(std::shared_ptr<CLI> _ui)
{
	_ui->ClearScreen();
	_ui->ShowBoard(game_data);
	_ui->ShowPlayersInfo(game_data);

	auto winners_count = game_data->GetWinners().size();

	if (winners_count == 1) {
		std::cout << "Player " << game_data->GetWinners()[0].first.GetNickName() <<
			" win with combination: " << game_data->GetWinners()[0].second.cards;
	}
	else {
		std::cout << std::endl << "Draw!" << std::endl << std::endl;
		auto winners = game_data->GetWinners();
		for (const auto& winner : winners) {
			std::cout << "Player " << winner.first.GetNickName() <<
				" win with combination: " << winner.second.cards;
		}
	}

	game_data->Reset();

	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	std::cin.get();
}

void EndRound::Update(){}
