#ifndef _RIVER_HPP
#define _RIVER_HPP

#include "GameState.hpp"

class River : public GameState {
public:
	River(std::shared_ptr<Game> _game_data)
		: GameState(_game_data) {}

	void Update();
	void Render(std::shared_ptr<CLI>);
};

#endif
