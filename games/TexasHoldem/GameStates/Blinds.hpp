#ifndef _BLINDS_HPP
#define _BLINDS_HPP

#include "GameState.hpp"

class Blinds : public GameState {
public:
	Blinds(std::shared_ptr<Game> _game_data)
		: GameState(_game_data) {}

	void Update();
	void Render(std::shared_ptr<CLI>);
};

#endif
