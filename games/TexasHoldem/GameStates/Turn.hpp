#ifndef _TURN_HPP
#define _TURN_HPP

#include "GameState.hpp"

class Turn : public GameState {
public:
	Turn(std::shared_ptr<Game> _game_data)
		: GameState(_game_data) {}

	void Update();
	void Render(std::shared_ptr<CLI>);
};

#endif
