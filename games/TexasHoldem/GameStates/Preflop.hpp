#ifndef _PREFLOP_HPP
#define _PREFLOP_HPP

#include "GameState.hpp"

class Preflop : public GameState {
public:
	Preflop(std::shared_ptr<Game> _game_data)
		: GameState(_game_data) {}

	void Update();
	void Render(std::shared_ptr<CLI>);
};

#endif
