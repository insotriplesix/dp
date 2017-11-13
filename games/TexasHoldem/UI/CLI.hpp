#ifndef _CLI_HPP
#define _CLI_HPP

#include <iostream>
#include <memory>
#include "Game.hpp"

class CLI {
public:
	void ClearScreen();
	void ShowBoard(std::shared_ptr<Game>);
	void ShowDeck(std::shared_ptr<Game>);
	void ShowLogo();
	void ShowMenu();
	void ShowPlayersInfo(std::shared_ptr<Game>);
	void ShowPlayerStatus(Player);
};

#endif
