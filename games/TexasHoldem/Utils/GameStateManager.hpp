#ifndef _GAME_STATE_MANAGER_HPP
#define _GAME_STATE_MANAGER_HPP

#include "GameState.hpp"

class GameStateManager {
public:
	enum state_t {
		MENU, BLINDS, PREFLOP, FLOP,
		TURN, RIVER, ENDROUND, S_COUNT
	};

	GameStateManager(const std::vector<std::shared_ptr<GameState>>&);

	void SetCurrentState(state_t);

	void Render(std::shared_ptr<CLI> _ui)
	{
		current_state->Render(_ui);
	}

	void Update()
	{
		current_state->Update();
		SetCurrentState(next_state);
	}

private:
	std::vector<std::shared_ptr<GameState>> game_states;
	std::shared_ptr<GameState> current_state;
	state_t next_state;
};

#endif
