#ifndef _MENU_HPP
#define _MENU_HPP

#include "GameState.hpp"

class Menu : public GameState {
public:
	Menu(std::shared_ptr<Game> _game_data)
		: GameState(_game_data) {}

	void Update();
	void Render(std::shared_ptr<CLI>);
};

#endif
