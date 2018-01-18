#include "CLI.hpp"

void CLI::ClearScreen()
{
	system("CLS");
}

void CLI::ShowBoard(std::shared_ptr<Game> _game)
{
	auto current_pot = _game->GetPot();
	auto board_cards = _game->GetBoardCards();

	std::cout << " -> POT: $" << current_pot <<
		std::endl << std::endl;

	std::cout << " -> BOARD:" << std::endl << std::endl;
	for (auto card : board_cards) {
		std::cout << card << " ";
	}
	std::cout << std::endl;
	std::cout << "______________________________\n\n";
}

void CLI::ShowDeck(std::shared_ptr<Game> _game)
{
	auto deck = _game->GetDeck().GetCards();

	std::cout << "DECK:" << std::endl;
	for (auto card : deck) {
		std::cout << card << " ";
	}
	std::cout << std::endl;
}

void CLI::ShowLogo()
{
	std::string line = 
"________________________________________________________________________\n";

	std::string logo = 
"    ______                        __  __      __    ___               \n"
"   /_  __/__  _  ______ ______   / / / /___  / /___/ ( )___  ____ ___ \n"
"    / / / _ \\| |/_/ __ `/ ___/  / /_/ / __ \\/ / __  /|// _ \\/ __ `__ \\\n"
"   / / /  __/>  </ /_/ (__  )  / __  / /_/ / / /_/ /  /  __/ / / / / /\n"
"  /_/  \\___/_/|_|\\__,_/____/  /_/ /_/\\____/_/\\__,_/   \\___/_/ /_/ /_/ \n"
"                                                                      \n";

	std::cout << std::endl << line << logo << line << std::endl;
}

void CLI::ShowMenu()
{
	std::string menu =
		" 1. Start\n"
		" 2. Help\n"
		" 3. About\n"
		" 0. Quit\n"
		"__________\n\n"
		" > ";

	std::cout << menu;
}

void CLI::ShowPlayersInfo(std::shared_ptr<Game> _game)
{
	auto players = _game->GetPlayers();

	for (auto player : players) {
		ShowPlayerStatus(player);
	}
}

void CLI::ShowPlayerStatus(Player _player)
{
	 std::cout << " ID: " << _player.GetID() << std::endl <<
		" Nickname: " << _player.GetNickName() << std::endl <<
		" Cash: $" << _player.GetCash() << std::endl <<
		" Hand: " << _player.GetHand() << std::endl <<
		"______________________________\n\n";
}
