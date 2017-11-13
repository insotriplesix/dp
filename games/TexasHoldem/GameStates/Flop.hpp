#ifndef _FLOP_HPP
#define _FLOP_HPP

#include "GameState.hpp"

class Flop : public GameState {
public:
	Flop(std::shared_ptr<Game> _game_data)
		: GameState(_game_data) {}

	void Update();
	void Render(std::shared_ptr<CLI>);
};

#endif
