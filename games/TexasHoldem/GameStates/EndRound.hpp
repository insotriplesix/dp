#ifndef _CALCULATE_HPP
#define _CALCULATE_HPP

#include "GameState.hpp"

class EndRound : public GameState {
public:
	EndRound(std::shared_ptr<Game> _game_data)
		: GameState(_game_data) {}

	void Update();
	void Render(std::shared_ptr<CLI>);
};

#endif
